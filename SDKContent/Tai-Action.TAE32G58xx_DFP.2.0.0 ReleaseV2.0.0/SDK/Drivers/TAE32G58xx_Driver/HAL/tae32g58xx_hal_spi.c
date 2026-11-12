/**
  ******************************************************************************
  * @file    tae32g58xx_hal_spi.c
  * @author  Tai-Action SD Team
  * @brief   SPI HAL module driver.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal.h"

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */
#if defined(SPI0) || defined(SPI1) 
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_SPI_MODULE_ENABLED) && (HAL_SPI_MODULE_ENABLED == 1)

/** @defgroup SPI_HAL SPI HAL
  * @brief    SPI HAL module driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/** @defgroup SPI_HAL_Private_Constants SPI HAL Private Constants
  * @{
  */
#define SPI_DEFAULT_TIMEOUT           (100U)      /*!< SPI default timeout (ms) for blocking loops */
/**
  * @brief  IT mode TX FIFO empty threshold (TXFTLR), unit: bytes
  * @note   TXFTLR has only 4 bits (0..15, FIFO depth is 16). TXEI fires when the
  *         remaining TX FIFO depth <= this value, so the value is the CPU refill
  *         margin: 2 -> about 2.8us, 8 -> about 11.4us (PCLK 90MHz, DIV_16).
  *         A slave has no clock of its own; if the master's ISR blocks the
  *         slave's ISR longer than this margin the slave underflows and the
  *         hardware sends CTRL.UDRCFG's fill value (default UDRDR = 0x0000),
  *         which shows up as the peer receiving a stream shifted by one byte.
  *         DMA mode is refilled by hardware and keeps 2, see HAL_SPI_Transmit_DMA.
  */
#ifndef SPI_TX_FIFO_EMPTY_THRES
#define SPI_FIFO_DEPTH                (16U)   /*!< TX/RX FIFO depth, used to bound preload/refill loops */
#define SPI_TX_FIFO_EMPTY_THRES       (8U)
#endif /* SPI_TX_FIFO_EMPTY_THRES */


/* Private Functions ---------------------------------------------------------*/
/** @defgroup SPI_HAL_Private_Functions SPI HAL Private Functions
  * @{
  */

__STATIC_FORCEINLINE HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(HAL_SPI_HandleTypeDef *hspi,
                                                        uint32_t Flag, uint32_t Status,
                                                        uint32_t Timeout, uint32_t Tickstart);

__STATIC_FORCEINLINE HAL_StatusTypeDef SPI_WaitOnBusyUntilTimeout(HAL_SPI_HandleTypeDef *hspi,
                                                     uint32_t Timeout, uint32_t Tickstart);

__STATIC_FORCEINLINE void SPI_CloseTransfer(HAL_SPI_HandleTypeDef *hspi);
__STATIC_FORCEINLINE void SPI_ConfigTxFifoThresholdIT(HAL_SPI_HandleTypeDef *hspi);
__STATIC_FORCEINLINE void SPI_PreloadTxFifo(HAL_SPI_HandleTypeDef *hspi, uint32_t MaxCount);
__STATIC_FORCEINLINE void SPI_CompleteTransferFromDMA(HAL_SPI_HandleTypeDef *hspi);

__STATIC_FORCEINLINE void SPI_DMATransmitCplt(HAL_DMA_HandleTypeDef *hdma);
__STATIC_FORCEINLINE void SPI_DMAReceiveCplt(HAL_DMA_HandleTypeDef *hdma);
__STATIC_FORCEINLINE void SPI_DMATxHalfCplt(HAL_DMA_HandleTypeDef *hdma);
__STATIC_FORCEINLINE void SPI_DMARxHalfCplt(HAL_DMA_HandleTypeDef *hdma);
__STATIC_FORCEINLINE void SPI_DMATxRxHalfCplt(HAL_DMA_HandleTypeDef *hdma);
__STATIC_FORCEINLINE void SPI_DMAError(HAL_DMA_HandleTypeDef *hdma);

__STATIC_FORCEINLINE void SPI_DMATxAbortCallback(HAL_DMA_HandleTypeDef *hdma);
__STATIC_FORCEINLINE void SPI_DMARxAbortCallback(HAL_DMA_HandleTypeDef *hdma);
__STATIC_FORCEINLINE void SPI_AbortTransfer(HAL_SPI_HandleTypeDef *hspi);

/**
  * @}
  */

/**
  * @brief  Wait for a flag state until timeout.
  * @param[in,out]  hspi      SPI handle.
  * @param[in]  Flag      Flag to check.
  * @param[in]  Status    Expected flag status (0UL for RESET or 1UL for SET).
  * @param[in]  Timeout   Timeout duration in milliseconds.
  * @param[in]  Tickstart Tick start value for timeout calculation.
  * @return HAL status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(HAL_SPI_HandleTypeDef *hspi,
                                                        uint32_t Flag, uint32_t Status,
                                                        uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t status;

    while (1UL) {
        /* Check flag */
        if (Flag == HAL_SPI_FLAG_BUSY) {
            status = LL_SPI_IsActiveFlag_BSY(hspi->Instance);
        } else {
            status = ((hspi->Instance->INT & Flag) == Flag) ? 1UL : 0UL;
        }

        /* Check result */
        if (Status == 0UL) {
            if (status == 0UL) { return HAL_OK; }
        } else { /* Status == 1UL */
            if (status != 0UL) { return HAL_OK; }
        }

        /* Check timeout */
        if (Timeout != HAL_MAX_DELAY) {
            if ((Timeout == 0U) || ((HAL_GetTick() - Tickstart) > Timeout)) {
                hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
                return HAL_TIMEOUT;
            }
        }

        if ((hspi->ErrorCode & HAL_SPI_ERROR_ABORT) != 0UL) {
            return HAL_ERROR;
        }
    }
}

__STATIC_FORCEINLINE void SPI_AbortTransfer(HAL_SPI_HandleTypeDef *hspi)
{
  
    LL_SPI_Disable(hspi->Instance);
    LL_SPI_ResetTxFIFO(hspi->Instance);
    LL_SPI_ResetRxFIFO(hspi->Instance);

    SPI_CloseTransfer(hspi);
    hspi->TxXferCount = 0U;
    hspi->RxXferCount = 0U;
    hspi->ErrorCode |= HAL_SPI_ERROR_ABORT;
    hspi->State = HAL_SPI_STATE_READY;
}

__STATIC_FORCEINLINE void SPI_DMATxAbortCallback(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if ((hspi == NULL) || (hspi->State != HAL_SPI_STATE_ABORT)) {
        return;
    }

    hspi->TxXferCount = 0U;
    SPI_AbortTransfer(hspi);
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    hspi->AbortCpltCallback(hspi);
#else
    HAL_SPI_AbortCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
}

__STATIC_FORCEINLINE void SPI_DMARxAbortCallback(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if ((hspi == NULL) || (hspi->State != HAL_SPI_STATE_ABORT)) {
        return;
    }

    hspi->RxXferCount = 0U;
    SPI_AbortTransfer(hspi);
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    hspi->AbortCpltCallback(hspi);
#else
    HAL_SPI_AbortCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
}

/**
  * @brief  Wait until SPI is not busy or timeout occurs.
  * @param[in,out]  hspi      SPI handle.
  * @param[in]  Timeout   Timeout duration in milliseconds.
  * @param[in]  Tickstart Tick start value for timeout calculation.
  * @return HAL status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef SPI_WaitOnBusyUntilTimeout(HAL_SPI_HandleTypeDef *hspi,
                                                     uint32_t Timeout, uint32_t Tickstart)
{
    while (LL_SPI_IsActiveFlag_BSY(hspi->Instance) != 0UL) {
        /* Drain RX FIFO to prevent overflow stall in loopback mode */
        while (LL_SPI_IsActiveFlag_RFE(hspi->Instance) == 0UL) {
            (void)LL_SPI_ReadData(hspi->Instance);
        }
        if (Timeout != HAL_MAX_DELAY) {
            if ((Timeout == 0U) || ((HAL_GetTick() - Tickstart) > Timeout)) {
                hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
                return HAL_TIMEOUT;
            }
        }
    }
    return HAL_OK;
}

/**
  * @brief  Close the transfer and restore SPI to ready state.
  * @param[in,out]  hspi SPI handle.
  * @return None
  */
__STATIC_FORCEINLINE void SPI_CloseTransfer(HAL_SPI_HandleTypeDef *hspi)
{
    /* Disable all data interrupts */
    LL_SPI_DisableIT_RXCI(hspi->Instance);
    LL_SPI_DisableIT_TXCI(hspi->Instance);
    LL_SPI_DisableIT_TXEI(hspi->Instance);
    LL_SPI_DisableIT_RXFI(hspi->Instance);
    LL_SPI_DisableIT_RXDEI(hspi->Instance);
    LL_SPI_DisableIT_TXDEI(hspi->Instance);

    /* Disable error interrupts */
    LL_SPI_DisableIT_MDFI(hspi->Instance);
    LL_SPI_DisableIT_OPFI(hspi->Instance);
    LL_SPI_DisableIT_TXOFI(hspi->Instance);
    LL_SPI_DisableIT_RXOFI(hspi->Instance);
    LL_SPI_DisableIT_RXUFI(hspi->Instance);

    /* Disable DMA requests */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    LL_SPI_DisableDMAReq_RX(hspi->Instance);

    /* Reset transfer pointers */
    hspi->pTxBuffPtr  = NULL;
    hspi->TxXferSize  = 0U;
    hspi->TxXferCount = 0U;
    hspi->pRxBuffPtr  = NULL;
    hspi->RxXferSize  = 0U;
    hspi->RxXferCount = 0U;

    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    /* Clear all pending interrupts */
    LL_SPI_ClearFlag_AllIntPnd(hspi->Instance);
    LL_SPI_ClearFlag_RXOFI(hspi->Instance);
    LL_SPI_ClearFlag_TXOFI(hspi->Instance);
}

/**
  * @brief  Configure the TX FIFO empty threshold (TXFTLR) for IT mode.
  * @param[in,out]  hspi SPI handle.
  * @return None
  * @note   Priority of the value:
  *           1) hspi->DefaultCfg.TxFifoEmptyThres when it is not 0, so that the value
  *              programmed in HAL_SPI_Init() is not silently overwritten by *_IT();
  *           2) SPI_TX_FIFO_EMPTY_THRES (default 8).
  *         TXFTLR is only 4 bits wide (0..15, FIFO depth is 16); 16 would be masked
  *         to 0, so it is clamped to 15 here.
  * @ref    SPI_TX_FIFO_EMPTY_THRES
  */
__STATIC_FORCEINLINE void SPI_ConfigTxFifoThresholdIT(HAL_SPI_HandleTypeDef *hspi)
{
    uint32_t thres;

    thres = (hspi->DefaultCfg.TxFifoEmptyThres != 0U)
            ? (uint32_t)hspi->DefaultCfg.TxFifoEmptyThres
            : (uint32_t)SPI_TX_FIFO_EMPTY_THRES;

    if (thres > 15U) {
        thres = 15U;
    }

    LL_SPI_SetTxFIFOEmptyThreshold(hspi->Instance, thres);
}

/**
  * @brief  Preload the TX FIFO before the shifter is started.
  * @param[in,out]  hspi      Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]      MaxCount  Upper bound of entries to write (FIFO depth guard).
  * @retval None
  * @note   HAL_SPI_Transmit_IT() / TransmitReceive_IT() used to do
  *         LL_SPI_Enable() then LL_SPI_StartMasterTxRx() while the TX FIFO was
  *         still empty, enabling TXEI only afterwards.  The shifter therefore
  *         started clocking with nothing to send and put the idle level
  *         (0xFFFF) on MOSI for however many bytes it took the ISR to run - a
  *         pure timing race that showed up as "the first N bytes are 0xFF".
  *         Writing a few entries before starting removes the window, so the
  *         first bit shifted out always carries real data.
  *         The loop is bounded: LL_SPI_IsActiveFlag_TFF() must never be able to
  *         spin here forever (an unbounded dummy loop in the IRQ handler would
  *         hang the whole application).
  */
__STATIC_FORCEINLINE void SPI_PreloadTxFifo(HAL_SPI_HandleTypeDef *hspi, uint32_t MaxCount)
{
    uint32_t dat;
    uint32_t n = 0U;

    while ((n < MaxCount) && (LL_SPI_IsActiveFlag_TFF(hspi->Instance) == 0UL)) {
        if (hspi->pTxBuffPtr == NULL) {
            dat = 0xFFFFU;                      /* receive-only: dummy payload */
        } else {
            if (hspi->TxXferCount == 0U) {
                break;
            }
            if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
                dat  = (uint32_t)(*(hspi->pTxBuffPtr));
                hspi->pTxBuffPtr++;
                dat |= ((uint32_t)(*(hspi->pTxBuffPtr))) << 8U;
                hspi->pTxBuffPtr++;
            } else {
                dat = (uint32_t)(*(hspi->pTxBuffPtr));
                hspi->pTxBuffPtr++;
            }
            hspi->TxXferCount--;
        }
        LL_SPI_WriteData(hspi->Instance, (dat & 0xFFFFU));
        n++;
    }
}

/**
  * @brief  Complete a DMA transfer from the DMA completion callback.
  * @param[in,out]  hspi SPI handle.
  * @return None
  * @note   Full duplex (BUSY_TX_RX) only: the SPI IRQ handler cannot close this
  *         transfer by itself. Its TXCI branch requires State == BUSY_TX and its
  *         RXCI branch requires State == BUSY_RX, so in BUSY_TX_RX neither branch
  *         matches; the only path left is the fallback block at the end of
  *         HAL_SPI_IRQHandler(), and that block needs *another* SPI interrupt to
  *         run. When both DMA channels have already finished, no such interrupt
  *         arrives any more, so the transfer stays BUSY_TX_RX forever and the
  *         completion callback is never called.
  *
  *         Caller must guarantee TxXferCount == 0 && RxXferCount == 0.
  *         Pure TX (BUSY_TX) is deliberately NOT completed here: the DMA only
  *         proves the bytes reached TDR, so that path still waits for TXCI to
  *         make sure the last frame really left the shifter.
  */
__STATIC_FORCEINLINE void SPI_CompleteTransferFromDMA(HAL_SPI_HandleTypeDef *hspi)
{
    HAL_SPI_StateTypeDef done_state = hspi->State;

    hspi->State = HAL_SPI_STATE_READY;
    SPI_CloseTransfer(hspi);

    if (done_state == HAL_SPI_STATE_BUSY_RX) {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
        hspi->RxCpltCallback(hspi);
#else
        HAL_SPI_RxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
    } else if (done_state == HAL_SPI_STATE_BUSY_TX) {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
        hspi->TxCpltCallback(hspi);
#else
        HAL_SPI_TxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
    } else {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
        hspi->TxRxCpltCallback(hspi);
#else
        HAL_SPI_TxRxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
    }
}

/* Exported functions --------------------------------------------------------*/

/** @defgroup SPI_HAL_Exported_Functions_Group1 Initialization and De-initialization functions
  * @{
  */

/**
  * @brief  Initialize the SPI according to the specified parameters in the
  *         HAL_SPI_InitTypeDef and initialize the associated handle.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       Init success; peripheral is in READY state.
  * @retval HAL_INVALID    Invalid handle or invalid Init parameters.
  * @retval HAL_BUSY     Peripheral is already initialized or busy.
  * @note   Must be called once before any transfer (blocking / IT / DMA).
  *         After return, the handle state is HAL_SPI_STATE_READY and
  *         the SPI peripheral is enabled.
  * @ref    HAL_SPI_DeInit HAL_SPI_MspInit
  */
HAL_StatusTypeDef HAL_SPI_Init(HAL_SPI_HandleTypeDef *hspi, SPI_TypeDef *SPIx, HAL_SPI_InitTypeDef *Init)
{
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_FUNC_PARAM(Init != NULL);
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(SPIx)) || (Init == NULL)) {
            return HAL_INVALID;
        }
    });

    /* Configurable parameter checks */
    HAL_SPI_PARAM_CHECK({
        if (!IS_HAL_SPI_MODE(Init->Mode)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_SPI_DIRECTION(Init->Direction)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_SPI_DATASIZE(Init->DataSize)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_SPI_CPOL(Init->CLKPolarity)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_SPI_CPHA(Init->CLKPhase)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_SPI_CS(Init->CS)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_SPI_BAUDRATE_PRESCALER(Init->BaudRatePrescaler)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_SPI_FIRST_BIT(Init->FirstBit)) {
            return HAL_INVALID;
        }
    });

    /* Bind the instance passed by the caller */
    hspi->Instance = SPIx;

    if (hspi->State == HAL_SPI_STATE_RESET) {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
        /* Initialize callbacks to weak functions if callbacks are enabled */
        hspi->TxCpltCallback       = HAL_SPI_TxCpltCallback;
        hspi->RxCpltCallback       = HAL_SPI_RxCpltCallback;
        hspi->TxRxCpltCallback     = HAL_SPI_TxRxCpltCallback;
        hspi->TxHalfCpltCallback   = HAL_SPI_TxHalfCpltCallback;
        hspi->RxHalfCpltCallback   = HAL_SPI_RxHalfCpltCallback;
        hspi->TxRxHalfCpltCallback = HAL_SPI_TxRxHalfCpltCallback;
        hspi->ErrorCallback        = HAL_SPI_ErrorCallback;
        hspi->AbortCpltCallback    = HAL_SPI_AbortCpltCallback;
        hspi->MspInitCallback      = HAL_SPI_MspInit;
        hspi->MspDeInitCallback    = HAL_SPI_MspDeInit;

        /* Init the low level hardware : GPIO, CLOCK, NVIC... */
        hspi->MspInitCallback(hspi);
#else
        /* Init the low level hardware : GPIO, CLOCK, NVIC... */
        HAL_SPI_MspInit(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
    } else {
        /* Disable the SPI to reconfigure */
        LL_SPI_Disable(hspi->Instance);
    }

    /* Initialize error code */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    /* Disable all interrupt sources */
    LL_SPI_ClearFlag_AllIntPnd(hspi->Instance);

    /* Reset FIFOs */
    LL_SPI_ResetTxFIFO(hspi->Instance);
    LL_SPI_ResetRxFIFO(hspi->Instance);

    /* Configure SPI Direction (Wire Mode) */
    if (Init->Direction == HAL_SPI_DIRECTION_1LINE) {
        /* 3-wire mode (bidirectional) */
        LL_SPI_SetStandard(hspi->Instance, LL_SPI_WIRE_MODE_3);
    } else {
        /* 4-wire mode (full duplex or unidirectional) */
        LL_SPI_SetStandard(hspi->Instance, LL_SPI_WIRE_MODE_4);
    }

    /* Configure SPI Role (Master/Slave) */
    if (Init->Mode == HAL_SPI_MODE_MASTER) {
        LL_SPI_SetMode(hspi->Instance, LL_SPI_ROLE_MASTER);
    } else {
        LL_SPI_SetMode(hspi->Instance, LL_SPI_ROLE_SLAVE);
    }

    /* Configure Clock Polarity and Phase */
    LL_SPI_SetClockPolarity(hspi->Instance, Init->CLKPolarity);
    LL_SPI_SetClockPhase(hspi->Instance, Init->CLKPhase);

    /* Configure Data Size (register format: 0x03-0x0F maps to 4-16 bit) */
    LL_SPI_SetDataWidth(hspi->Instance, Init->DataSize);

    /* Configure Bit Order */
    LL_SPI_SetTransferBitOrder(hspi->Instance, Init->FirstBit);

    /* Configure Baud Rate (set the 11-bit divider value) */
    LL_SPI_SetBaudRatePrescaler(hspi->Instance, Init->BaudRatePrescaler - 1U);

    /* Configure CS management */
    if (Init->CS == HAL_SPI_CS_SOFT) {
        /* Software CS: enable software CS output */
        LL_SPI_EnableCSSwOut(hspi->Instance);
        LL_SPI_CSSwOutInactive(hspi->Instance);
    } else { /* HAL_SPI_CS_HARD */
        /* Hardware CS: disable software CS output */
        LL_SPI_DisableCSSwOut(hspi->Instance);
    }

    /* Configure CS pulse management and polarity from DefaultCfg defaults or user settings */
    if (hspi->DefaultCfg.CSMode == HAL_SPI_CS_MODE_CONTINUE) {
        LL_SPI_DisableCSPulseMgt(hspi->Instance);
    } else {
        LL_SPI_EnableCSPulseMgt(hspi->Instance);
    }

    LL_SPI_SetCSPolarity(hspi->Instance, hspi->DefaultCfg.CSPolarity);

    /* Configure CS Input Mode */
    LL_SPI_SetCSSlaveInputMode(hspi->Instance, hspi->DefaultCfg.CSInputMode);

    /* Configure FIFO thresholds */
    if (hspi->DefaultCfg.TxFifoEmptyThres != 0U) {
        LL_SPI_SetTxFIFOEmptyThreshold(hspi->Instance, hspi->DefaultCfg.TxFifoEmptyThres);
    }
    if (hspi->DefaultCfg.RxFifoFullThres != 0U) {
        LL_SPI_SetRxFIFOThreshold(hspi->Instance, hspi->DefaultCfg.RxFifoFullThres);
    }

    /* Configure Master RX Delay and Timing */
    if (hspi->DefaultCfg.MstRxDelay != 0U) {
        LL_SPI_SetMasterRxDelay(hspi->Instance, hspi->DefaultCfg.MstRxDelay);
    }
    if (hspi->DefaultCfg.MstSSIdleness != 0U) {
        LL_SPI_SetMasterSSIdleness(hspi->Instance, hspi->DefaultCfg.MstSSIdleness);
    }
    if (hspi->DefaultCfg.MstInterDatIdleness != 0U) {
        LL_SPI_SetMasterInterDatIdleness(hspi->Instance, hspi->DefaultCfg.MstInterDatIdleness);
    }

    /* Configure Pin Swap */
    if (hspi->DefaultCfg.MOSIMISOSwap) {
        LL_SPI_EnableMOSIMISOSwap(hspi->Instance);
    } else {
        LL_SPI_DisableMOSIMISOSwap(hspi->Instance);
    }

    /* Configure Loopback */
    if (hspi->LoopbackEnable == HAL_SPI_FUNC_ENABLE) {
        LL_SPI_EnableLoopback(hspi->Instance);
    } else {
        LL_SPI_DisableLoopback(hspi->Instance);
    }

    /* Enable TX and RX */
    if (Init->Direction != HAL_SPI_DIRECTION_1LINE) {
        /* Full duplex or RX only: enable both TX and RX */
        if (IS_HAL_SPI_HAS_TX_PHASE(Init)) {
            LL_SPI_EnableTx(hspi->Instance);
        }
        if (IS_HAL_SPI_HAS_RX_PHASE(Init)) {
            LL_SPI_EnableRx(hspi->Instance);
        }
    } else {
        /* Bidirectional 1-line: only TX enabled, RX direction controlled by transfer */
        LL_SPI_EnableTx(hspi->Instance);
    }

    /* Clear all pending interrupt flags */
    LL_SPI_ClearFlag_AllIntPnd(hspi->Instance);

    /* Initialize DMA flags */
    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    /* Set state to READY */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    hspi->State     = HAL_SPI_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  DeInitialize the SPI peripheral.
  *         Reset registers to default values, disable the peripheral,
  *         and call the MSP DeInit callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       DeInit success.
  * @retval HAL_INVALID    Invalid handle.
  * @note   After this function, the SPI peripheral is disabled and needs
  *         re-initialization via HAL_SPI_Init.
  * @ref    HAL_SPI_Init HAL_SPI_MspDeInit
  */
HAL_StatusTypeDef HAL_SPI_DeInit(HAL_SPI_HandleTypeDef *hspi)
{
    /* Check the SPI handle allocation */
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    /* Configure handle state to reset */
    hspi->State = HAL_SPI_STATE_RESET;

    /* Disable the SPI peripheral */
    LL_SPI_Disable(hspi->Instance);

    /* Reset FIFOs */
    LL_SPI_ResetTxFIFO(hspi->Instance);
    LL_SPI_ResetRxFIFO(hspi->Instance);

    /* Clear all pending interrupts */
    LL_SPI_ClearFlag_AllIntPnd(hspi->Instance);

    /* Disable all DMA requests */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    LL_SPI_DisableDMAReq_RX(hspi->Instance);

    /* Reset ErrorCode */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    /* Reset transfer pointers */
    hspi->pTxBuffPtr  = NULL;
    hspi->TxXferSize  = 0U;
    hspi->TxXferCount = 0U;
    hspi->pRxBuffPtr  = NULL;
    hspi->RxXferSize  = 0U;
    hspi->RxXferCount = 0U;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    /* DeInit the low level hardware (with NULL guard for early-fail Init paths) */
    if (hspi->MspDeInitCallback != NULL) {
        hspi->MspDeInitCallback(hspi);
    }
#else
    /* DeInit the low level hardware */
    HAL_SPI_MspDeInit(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

    return HAL_OK;
}

/**
  * @brief  SPI MSP Initialization.
  *         This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO configuration
  *           - NVIC configuration for IT mode
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   This is a weak function that can be overridden by the user.
  * @ref    HAL_SPI_MspDeInit HAL_SPI_Init
  */
__WEAK void HAL_SPI_MspInit(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_MspInit could be implemented in the user file
     */
}

/**
  * @brief  SPI MSP De-Initialization.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   This is a weak function that can be overridden by the user.
  * @ref    HAL_SPI_MspInit HAL_SPI_DeInit
  */
__WEAK void HAL_SPI_MspDeInit(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_MspDeInit could be implemented in the user file
     */
}

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User SPI Callback.
  * @param[in,out]  hspi        Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  CallbackID  ID of the callback to register, value of @ref HAL_SPI_CallbackIDTypeDef.
  * @param[in]  pCallback   Pointer to the callback function.
  * @return HAL status
  * @retval HAL_OK       Callback registered.
  * @retval HAL_INVALID    Invalid parameter.
  * @note   Only available when USE_HAL_SPI_REGISTER_CALLBACKS = 1.
  * @ref    HAL_SPI_UnRegisterCallback
  */
HAL_StatusTypeDef HAL_SPI_RegisterCallback(HAL_SPI_HandleTypeDef *hspi,
                                            HAL_SPI_CallbackIDTypeDef CallbackID,
                                            HAL_SPI_UserCallbackTypeDef pCallback)
{
    HAL_StatusTypeDef status = HAL_OK;

    if (hspi == NULL) {
        return HAL_ERROR;
    }
    ASSERT_FUNC_PARAM(pCallback != NULL);
    if (pCallback == NULL) {
        status = HAL_ERROR;
    } else {
        switch (CallbackID) {
        case HAL_SPI_TX_COMPLETE_CB_ID:
            hspi->TxCpltCallback = pCallback;
            break;
        case HAL_SPI_RX_COMPLETE_CB_ID:
            hspi->RxCpltCallback = pCallback;
            break;
        case HAL_SPI_TX_RX_COMPLETE_CB_ID:
            hspi->TxRxCpltCallback = pCallback;
            break;
        case HAL_SPI_TX_HALF_COMPLETE_CB_ID:
            hspi->TxHalfCpltCallback = pCallback;
            break;
        case HAL_SPI_RX_HALF_COMPLETE_CB_ID:
            hspi->RxHalfCpltCallback = pCallback;
            break;
        case HAL_SPI_TX_RX_HALF_COMPLETE_CB_ID:
            hspi->TxRxHalfCpltCallback = pCallback;
            break;
        case HAL_SPI_ERROR_CB_ID:
            hspi->ErrorCallback = pCallback;
            break;
        case HAL_SPI_ABORT_CB_ID:
            hspi->AbortCpltCallback = pCallback;
            break;
        case HAL_SPI_MSPINIT_CB_ID:
            hspi->MspInitCallback = pCallback;
            break;
        case HAL_SPI_MSPDEINIT_CB_ID:
            hspi->MspDeInitCallback = pCallback;
            break;
        default:
            status = HAL_ERROR;
            break;
        }
    }
    return status;
}

/**
  * @brief  Unregister an SPI Callback.
  * @param[in,out]  hspi        Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  CallbackID  ID of the callback to unregister, value of @ref HAL_SPI_CallbackIDTypeDef.
  * @return HAL status
  * @retval HAL_OK       Callback unregistered.
  * @retval HAL_INVALID    Invalid parameter.
  * @note   After unregistering, the default weak callback function will be used.
  * @ref    HAL_SPI_RegisterCallback
  */
HAL_StatusTypeDef HAL_SPI_UnRegisterCallback(HAL_SPI_HandleTypeDef *hspi,
                                              HAL_SPI_CallbackIDTypeDef CallbackID)
{
    HAL_StatusTypeDef status = HAL_OK;

    switch (CallbackID) {
    case HAL_SPI_TX_COMPLETE_CB_ID:
        hspi->TxCpltCallback = HAL_SPI_TxCpltCallback;
        break;
    case HAL_SPI_RX_COMPLETE_CB_ID:
        hspi->RxCpltCallback = HAL_SPI_RxCpltCallback;
        break;
    case HAL_SPI_TX_RX_COMPLETE_CB_ID:
        hspi->TxRxCpltCallback = HAL_SPI_TxRxCpltCallback;
        break;
    case HAL_SPI_TX_HALF_COMPLETE_CB_ID:
        hspi->TxHalfCpltCallback = HAL_SPI_TxHalfCpltCallback;
        break;
    case HAL_SPI_RX_HALF_COMPLETE_CB_ID:
        hspi->RxHalfCpltCallback = HAL_SPI_RxHalfCpltCallback;
        break;
    case HAL_SPI_TX_RX_HALF_COMPLETE_CB_ID:
        hspi->TxRxHalfCpltCallback = HAL_SPI_TxRxHalfCpltCallback;
        break;
    case HAL_SPI_ERROR_CB_ID:
        hspi->ErrorCallback = HAL_SPI_ErrorCallback;
        break;
    case HAL_SPI_ABORT_CB_ID:
        hspi->AbortCpltCallback = HAL_SPI_AbortCpltCallback;
        break;
    case HAL_SPI_MSPINIT_CB_ID:
        hspi->MspInitCallback = HAL_SPI_MspInit;
        break;
    case HAL_SPI_MSPDEINIT_CB_ID:
        hspi->MspDeInitCallback = HAL_SPI_MspDeInit;
        break;
    default:
        status = HAL_ERROR;
        break;
    }
    return status;
}
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup SPI_HAL_Exported_Functions_Group2 IO operation functions
  * @{
  */

/**
  * @brief  Transmit an amount of data in blocking mode.
  * @param[in,out]  hspi    Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  pData   Pointer to data buffer.
  * @param[in]  Size    Amount of data to be sent.
  * @param[in]  Timeout Timeout duration in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Transfer completed successfully.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @note   Blocking call; returns only after transfer is complete or timeout.
  * @ref    HAL_SPI_Receive HAL_SPI_Transmit_IT
  */
HAL_StatusTypeDef HAL_SPI_Transmit(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size,
                                    uint32_t Timeout)
{
    uint32_t tickstart;
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t tmpreg;

    /* Check the handle and parameters */
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    HAL_SPI_PARAM_CHECK({
        if ((pData == NULL) || (Size == 0U)) {
            return HAL_INVALID;
        }
    });

    /* Initialize tickstart */
    tickstart = HAL_GetTick();

    /* Reset error code and set state */
    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_TX;

    /* Set the transaction information */
    hspi->pTxBuffPtr  = pData;
    hspi->TxXferSize  = Size;
    hspi->TxXferCount = Size;
    hspi->pRxBuffPtr  = NULL;
    hspi->RxXferSize  = 0U;
    hspi->RxXferCount = 0U;

    /* Disable DMA */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    /* Enable TX */
    LL_SPI_EnableTx(hspi->Instance);

    /* Enable SPI peripheral */
    LL_SPI_Enable(hspi->Instance);

    /* In master mode, set transfer count and start the transfer */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)hspi->TxXferCount);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Transmit data */
    while (hspi->TxXferCount > 0U) {
        /* Wait until TX FIFO is not full (space available to write) */
        while (LL_SPI_IsActiveFlag_TFF(hspi->Instance) != 0UL) {
            /* Check for the Timeout */
            if (Timeout != HAL_MAX_DELAY) {
                if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout)) {
                    hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
                    status = HAL_TIMEOUT;
                    break;
                }
            }
        }

        if (status != HAL_OK) {
            break;
        }

        /* Write data to TX FIFO (pack as 16-bit for register width) */
        if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
            tmpreg = (uint32_t)(*(hspi->pTxBuffPtr));
            hspi->pTxBuffPtr++;
            tmpreg |= ((uint32_t)(*(hspi->pTxBuffPtr))) << 8U;
            hspi->pTxBuffPtr++;
        } else {
            tmpreg = (uint32_t)(*(hspi->pTxBuffPtr));
            hspi->pTxBuffPtr++;
        }
        hspi->TxXferCount--;

        LL_SPI_WriteData(hspi->Instance, (uint32_t)(tmpreg & 0xFFFFU));
    }

    /* If the transfer is still ongoing, wait for TX complete */
    if (status == HAL_OK) {
        if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
            /* Wait for BUSY flag to be cleared (all bits shifted out) */
            status = SPI_WaitOnBusyUntilTimeout(hspi, Timeout, tickstart);
        }
    }

    /* If error or timeout occurred, set error state */
    if (status != HAL_OK) {
        if (hspi->ErrorCode != HAL_SPI_ERROR_NONE) {
            hspi->State = HAL_SPI_STATE_ERROR;
        }
        return HAL_TIMEOUT;
    }

    /* Check for errors */
    if (LL_SPI_IsActiveFlag(hspi->Instance, LL_SPI_INT_OPFI) != 0UL) {
        hspi->ErrorCode |= HAL_SPI_ERROR_OPF;
        hspi->State = HAL_SPI_STATE_ERROR;
    }

    /* Clean up */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_SLAVE) {
        /* In slave mode, just wait for BUSY clear */
        SPI_WaitOnBusyUntilTimeout(hspi, Timeout, tickstart);
    }

    /* Set state */
    if (hspi->State == HAL_SPI_STATE_BUSY_TX) {
        hspi->State = HAL_SPI_STATE_READY;
    }

    return HAL_OK;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param[in,out]  hspi    Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[out]  pData   Pointer to data buffer.
  * @param[in]  Size    Amount of data to be received.
  * @param[in]  Timeout Timeout duration in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Transfer completed successfully.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @note   Blocking call; returns only after transfer is complete or timeout.
  * @ref    HAL_SPI_Transmit HAL_SPI_Receive_IT
  */
HAL_StatusTypeDef HAL_SPI_Receive(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size,
                                   uint32_t Timeout)
{
    uint32_t tickstart;
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t tmpreg;

    /* Check the handle and parameters */
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    HAL_SPI_PARAM_CHECK({
        if ((pData == NULL) || (Size == 0U)) {
            return HAL_INVALID;
        }
    });

    /* Initialize tickstart */
    tickstart = HAL_GetTick();

    /* Reset error code and set state */
    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_RX;

    /* Set the transaction information */
    hspi->pRxBuffPtr  = pData;
    hspi->RxXferSize  = Size;
    hspi->RxXferCount = Size;
    hspi->pTxBuffPtr  = NULL;
    hspi->TxXferSize  = 0U;
    hspi->TxXferCount = 0U;

    /* Disable DMA */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    /* Enable RX */
    LL_SPI_EnableRx(hspi->Instance);

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);

    /* In master mode, we need to generate SCLK by writing dummy data
       while simultaneously reading received data.
       Set the transfer count. */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)hspi->RxXferCount);
        LL_SPI_EnableTx(hspi->Instance);  /* Need TX enabled for clock generation */

        /* Start transfer */
        LL_SPI_StartMasterTxRx(hspi->Instance);

        /* Write dummy data to generate clock and read simultaneously */
        while (hspi->RxXferCount > 0U) {
            /* Wait until TX FIFO is not full (space for dummy write) */
            while (LL_SPI_IsActiveFlag_TFF(hspi->Instance) != 0UL) {
                /* Check for the Timeout */
                if (Timeout != HAL_MAX_DELAY) {
                    if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout)) {
                        hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
                        status = HAL_TIMEOUT;
                        break;
                    }
                }
            }
            if (status != HAL_OK) { break; }

            /* Write dummy data to generate clock */
            LL_SPI_WriteData(hspi->Instance, 0xFFFFU);

            /* Wait for RX data available */
            if (LL_SPI_IsActiveFlag_RFE(hspi->Instance) == 0UL) {
                tmpreg = LL_SPI_ReadData(hspi->Instance);

                if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
                    *(hspi->pRxBuffPtr) = (uint8_t)(tmpreg & 0xFFU);
                    hspi->pRxBuffPtr++;
                    *(hspi->pRxBuffPtr) = (uint8_t)((tmpreg >> 8U) & 0xFFU);
                    hspi->pRxBuffPtr++;
                } else {
                    *(hspi->pRxBuffPtr) = (uint8_t)(tmpreg & 0xFFU);
                    hspi->pRxBuffPtr++;
                }
                hspi->RxXferCount--;
            }

            if (status != HAL_OK) { break; }
        }

        /* Wait for BUSY clear */
        SPI_WaitOnBusyUntilTimeout(hspi, Timeout, tickstart);
    } else { /* Slave mode */
        /* In slave mode, just wait for data from master */
        while (hspi->RxXferCount > 0U) {
            status = SPI_WaitFlagStateUntilTimeout(hspi, HAL_SPI_FLAG_RXNE, 1UL, Timeout, tickstart);
            if (status != HAL_OK) { break; }

            tmpreg = LL_SPI_ReadData(hspi->Instance);
            if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
                *(hspi->pRxBuffPtr) = (uint8_t)(tmpreg & 0xFFU);
                hspi->pRxBuffPtr++;
                *(hspi->pRxBuffPtr) = (uint8_t)((tmpreg >> 8U) & 0xFFU);
                hspi->pRxBuffPtr++;
            } else {
                *(hspi->pRxBuffPtr) = (uint8_t)(tmpreg & 0xFFU);
                hspi->pRxBuffPtr++;
            }
            hspi->RxXferCount--;
        }
    }

    if (status != HAL_OK) {
        if (hspi->ErrorCode != HAL_SPI_ERROR_NONE) {
            hspi->State = HAL_SPI_STATE_ERROR;
        }
        return HAL_TIMEOUT;
    }

    hspi->State = HAL_SPI_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in blocking mode.
  * @param[in,out]  hspi    Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  pTxData Pointer to transmission data buffer.
  * @param[out]  pRxData Pointer to reception data buffer.
  * @param[in]  Size    Amount of data to be sent and received.
  * @param[in]  Timeout Timeout duration in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Transfer completed successfully.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @note   Full-duplex: TX and RX occur simultaneously. Blocking call.
  * @ref    HAL_SPI_Transmit HAL_SPI_Receive HAL_SPI_TransmitReceive_IT
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive(HAL_SPI_HandleTypeDef *hspi, uint8_t *pTxData,
                                           uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart;
    uint32_t tmpreg;

    /* Check the handle and parameters */
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    /* Check transmit/receive parameters */
    if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    tickstart = HAL_GetTick();

    /* Reset error code and set state */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    if (((LL_SPI_GetStandard(hspi->Instance) == LL_SPI_WIRE_MODE_4) && (LL_SPI_IsEnabledTx(hspi->Instance) != 0U))) {
        hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
    } else {
        hspi->State = HAL_SPI_STATE_BUSY;
    }

    /* Set transaction information */
    hspi->pTxBuffPtr  = pTxData;
    hspi->TxXferSize  = Size;
    hspi->TxXferCount = Size;
    hspi->pRxBuffPtr  = pRxData;
    hspi->RxXferSize  = Size;
    hspi->RxXferCount = Size;

    /* Disable DMA */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    /* Enable both TX and RX */
    LL_SPI_EnableTx(hspi->Instance);
    LL_SPI_EnableRx(hspi->Instance);

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);

    /* In master mode, set count and start transfer */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)Size);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Main transfer loop: TX data while reading RX data */
    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U)) {
        /* Check for TX space (TX FIFO not full) */
        if ((hspi->TxXferCount > 0U) && (LL_SPI_IsActiveFlag_TFF(hspi->Instance) == 0UL)) {
            /* Pack two bytes into one 16-bit access only when the data size is wider than 8 bits */
            if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
                tmpreg = (uint32_t)(*(hspi->pTxBuffPtr));
                hspi->pTxBuffPtr++;
                tmpreg |= ((uint32_t)(*(hspi->pTxBuffPtr))) << 8U;
                hspi->pTxBuffPtr++;
            } else {
                tmpreg = (uint32_t)(*(hspi->pTxBuffPtr));
                hspi->pTxBuffPtr++;
            }
            hspi->TxXferCount--;
            LL_SPI_WriteData(hspi->Instance, (tmpreg & 0xFFFFU));
        }

        /* Check for RX data available */
        if ((hspi->RxXferCount > 0U) && (LL_SPI_IsActiveFlag_RFE(hspi->Instance) == 0UL)) {
            tmpreg = LL_SPI_ReadData(hspi->Instance);

            if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
                *(hspi->pRxBuffPtr) = (uint8_t)(tmpreg & 0xFFU);
                hspi->pRxBuffPtr++;
                *(hspi->pRxBuffPtr) = (uint8_t)((tmpreg >> 8U) & 0xFFU);
                hspi->pRxBuffPtr++;
            } else {
                *(hspi->pRxBuffPtr) = (uint8_t)(tmpreg & 0xFFU);
                hspi->pRxBuffPtr++;
            }
            hspi->RxXferCount--;
        }

        /* Timeout check */
        if (Timeout != HAL_MAX_DELAY) {
            if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout)) {
                hspi->ErrorCode |= HAL_SPI_ERROR_TIMEOUT;
                hspi->State = HAL_SPI_STATE_READY;
                return HAL_TIMEOUT;
            }
        }
    }

    /* Wait for BUSY flag to clear if master */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        SPI_WaitOnBusyUntilTimeout(hspi, Timeout, tickstart);
    }

    /* Check for operation fault */
    if (LL_SPI_IsActiveFlag(hspi->Instance, LL_SPI_INT_OPFI) != 0UL) {
        hspi->ErrorCode |= HAL_SPI_ERROR_OPF;
        hspi->State = HAL_SPI_STATE_ERROR;
        return HAL_ERROR;
    }

    hspi->State = HAL_SPI_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Transmit an amount of data in non-blocking mode with Interrupt.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @param[in]  pData Pointer to data buffer.
  * @param[in]  Size  Amount of data to be sent.
  * @return HAL status
  * @retval HAL_OK       Transfer started.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking. Completion via HAL_SPI_TxCpltCallback.
  * @ref    HAL_SPI_Receive_IT HAL_SPI_Transmit_DMA
  */
HAL_StatusTypeDef HAL_SPI_Transmit_IT(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    HAL_SPI_PARAM_CHECK({
        if ((pData == NULL) || (Size == 0U)) {
            return HAL_INVALID;
        }
    });

    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_TX;
    hspi->pTxBuffPtr  = pData;
    hspi->TxXferSize  = Size;
    hspi->TxXferCount = Size;
    hspi->pRxBuffPtr  = NULL;
    hspi->RxXferSize  = 0U;
    hspi->RxXferCount = 0U;

    /* Disable DMA */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    SPI_ConfigTxFifoThresholdIT(hspi);

    /* Enable TX */
    LL_SPI_EnableTx(hspi->Instance);

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);
    /* Preload the TX FIFO before the shifter is started, otherwise the first
       bytes are shifted out as the idle level (0xFFFF): see SPI_PreloadTxFifo(). */
    SPI_PreloadTxFifo(hspi, SPI_FIFO_DEPTH);
    /* In master mode, set count and start */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)Size);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Enable interrupts */
    LL_SPI_EnableIT_TXEI(hspi->Instance);   /* Fill FIFO when empty */
    LL_SPI_EnableIT_TXCI(hspi->Instance);        /* TX complete notification */
    LL_SPI_EnableIT_OPFI(hspi->Instance);  /* Error detection */

    return HAL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @param[out]  pData Pointer to data buffer.
  * @param[in]  Size  Amount of data to be received.
  * @return HAL status
  * @retval HAL_OK       Transfer started.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking. Completion via HAL_SPI_RxCpltCallback.
  * @ref    HAL_SPI_Transmit_IT HAL_SPI_Receive_DMA
  */
HAL_StatusTypeDef HAL_SPI_Receive_IT(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    HAL_SPI_PARAM_CHECK({
        if ((pData == NULL) || (Size == 0U)) {
            return HAL_INVALID;
        }
    });

    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_RX;
    hspi->pRxBuffPtr  = pData;
    hspi->RxXferSize  = Size;
    hspi->RxXferCount = Size;
    hspi->pTxBuffPtr  = NULL;
    hspi->TxXferSize  = 0U;
    hspi->TxXferCount = 0U;

    /* Disable DMA */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    SPI_ConfigTxFifoThresholdIT(hspi);

    /* Enable RX */
    LL_SPI_EnableRx(hspi->Instance);

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);

    /* In master mode, set count and start (need TX for clock generation) */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_EnableTx(hspi->Instance);

        /* Preload dummy payload BEFORE starting: starting with an empty FIFO
           makes the shifter put the idle level on MOSI for the first bytes. */
        SPI_PreloadTxFifo(hspi, SPI_FIFO_DEPTH);

        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)Size);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Enable interrupts: RX FIFO full for data, TX empty for dummy clock in master */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_EnableIT_TXEI(hspi->Instance);  /* Send dummy when TX empty */
    }
    LL_SPI_EnableIT_RXFI(hspi->Instance);       /* Read data when RX available */
    LL_SPI_EnableIT_RXCI(hspi->Instance);           /* RX complete notification */
    LL_SPI_EnableIT_OPFI(hspi->Instance);    /* Error detection */

    return HAL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with Interrupt.
  * @param[in,out]  hspi    Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  pTxData Pointer to transmission data buffer.
  * @param[out]  pRxData Pointer to reception data buffer.
  * @param[in]  Size    Amount of data to be sent and received.
  * @return HAL status
  * @retval HAL_OK       Transfer started.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking. Completion via HAL_SPI_TxRxCpltCallback.
  * @ref    HAL_SPI_Transmit_IT HAL_SPI_Receive_IT HAL_SPI_TransmitReceive_DMA
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(HAL_SPI_HandleTypeDef *hspi, uint8_t *pTxData,
                                              uint8_t *pRxData, uint16_t Size)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    /* Check transmit/receive parameters */
    if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_TX_RX;

    hspi->pTxBuffPtr  = pTxData;
    hspi->TxXferSize  = Size;
    hspi->TxXferCount = Size;

    hspi->pRxBuffPtr  = pRxData;
    hspi->RxXferSize  = Size;
    hspi->RxXferCount = Size;

    /* Disable DMA */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_DISABLE;
    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->RxDMAEnable = HAL_SPI_FUNC_DISABLE;

    SPI_ConfigTxFifoThresholdIT(hspi);

    /* Enable TX and RX */
    LL_SPI_EnableTx(hspi->Instance);
    LL_SPI_EnableRx(hspi->Instance);

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);
    /* Preload the TX FIFO before the shifter is started, otherwise the first
       bytes are shifted out as the idle level (0xFFFF): see SPI_PreloadTxFifo(). */
    SPI_PreloadTxFifo(hspi, SPI_FIFO_DEPTH);
    /* In master mode, set count and start */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)Size);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Enable interrupts */
    LL_SPI_EnableIT_TXEI(hspi->Instance);  /* TX FIFO empty: feed more data */
    LL_SPI_EnableIT_RXFI(hspi->Instance);   /* RX FIFO full: read data */
    LL_SPI_EnableIT_TXCI(hspi->Instance);       /* TX complete */
    LL_SPI_EnableIT_RXCI(hspi->Instance);       /* RX complete */
    LL_SPI_EnableIT_OPFI(hspi->Instance);/* Error detection */

    return HAL_OK;
}

/**
  * @brief  Transmit an amount of data in non-blocking mode with DMA.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @param[in]  pData Pointer to data buffer.
  * @param[in]  Size  Amount of data to be sent.
  * @return HAL status
  * @retval HAL_OK       Transfer started.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking. The library binds the transfer callbacks and starts the DMA
  *         channel itself, so the DMA handle passed in must be initialized beforehand.
  *         Completion via HAL_SPI_TxCpltCallback.
  * @ref    HAL_SPI_Receive_DMA HAL_SPI_Transmit_IT
  */
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdma,
                                       uint8_t *pData, uint16_t Size)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    HAL_SPI_PARAM_CHECK({
        if ((pData == NULL) || (Size == 0U) || (hdma == NULL)) {
            return HAL_INVALID;
        }
    });

    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_TX;

    hspi->pTxBuffPtr  = pData;
    hspi->TxXferSize  = Size;
    hspi->TxXferCount = Size;
    hspi->pRxBuffPtr  = NULL;
    hspi->RxXferSize  = 0U;
    hspi->RxXferCount = 0U;

    /* Set the SPI in TX-only mode */
    LL_SPI_EnableTx(hspi->Instance);
    LL_SPI_DisableRx(hspi->Instance);

    /* Enable TX DMA */
    LL_SPI_EnableDMAReq_TX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_ENABLE;

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);

    /* In master mode, set count and start */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)Size);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Enable TX complete interrupt for DMA completion */
    LL_SPI_EnableIT_TXCI(hspi->Instance);
    LL_SPI_EnableIT_OPFI(hspi->Instance);


    LL_SPI_SetTxFIFOEmptyThreshold(hspi->Instance, 0x2U);

    hdma->XferCpltCallback     = SPI_DMATransmitCplt;
    hdma->XferHalfCpltCallback = SPI_DMATxHalfCplt;
    hdma->XferErrorCallback    = SPI_DMAError;
    hdma->Parent               = (void *)hspi;
    if (HAL_DMA_Start_IT(hdma, (uint32_t)(pData), (uint32_t)(&hspi->Instance->TDR), (uint32_t)Size) != HAL_OK) {
        SPI_CloseTransfer(hspi);
        hspi->State = HAL_SPI_STATE_READY;
        return HAL_ERROR;
    }
    return HAL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @param[out]  pData Pointer to data buffer.
  * @param[in]  Size  Amount of data to be received.
  * @return HAL status
  * @retval HAL_OK       Transfer started.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking. The library binds the transfer callbacks and starts the DMA
  *         channel itself, so the DMA handle passed in must be initialized beforehand.
  *         Completion via HAL_SPI_RxCpltCallback.
  * @ref    HAL_SPI_Transmit_DMA HAL_SPI_Receive_IT
  */
HAL_StatusTypeDef HAL_SPI_Receive_DMA(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdma,
                                      uint8_t *pData, uint16_t Size)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    HAL_SPI_PARAM_CHECK({
        if ((pData == NULL) || (Size == 0U) || (hdma == NULL)) {
            return HAL_INVALID;
        }
    });

    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_RX;

    hspi->pRxBuffPtr  = pData;
    hspi->RxXferSize  = Size;
    hspi->RxXferCount = Size;
    hspi->pTxBuffPtr  = NULL;
    hspi->TxXferSize  = 0U;
    hspi->TxXferCount = 0U;

    /* Enable RX, enable TX for master clock generation */
    LL_SPI_EnableRx(hspi->Instance);

    /* Enable RX DMA */
    LL_SPI_EnableDMAReq_RX(hspi->Instance);
    hspi->RxDMAEnable = HAL_SPI_FUNC_ENABLE;

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);

    /* In master mode, set count and start */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_EnableTx(hspi->Instance);
        LL_SPI_EnableDMAReq_TX(hspi->Instance);
        hspi->TxDMAEnable = HAL_SPI_FUNC_ENABLE;

        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)Size);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Enable RX complete interrupt */
    LL_SPI_EnableIT_RXCI(hspi->Instance);
    LL_SPI_EnableIT_OPFI(hspi->Instance);


    LL_SPI_SetTxFIFOEmptyThreshold(hspi->Instance, 0x2U);

    hdma->XferCpltCallback     = SPI_DMAReceiveCplt;
    hdma->XferHalfCpltCallback = SPI_DMARxHalfCplt;
    hdma->XferErrorCallback    = SPI_DMAError;
    hdma->Parent               = (void *)hspi;
    /* Source = RDR (peripheral), destination = pData (memory).
       Fix: the two arguments used to be swapped here, so the DMA read *from*
       pData and wrote *into* RDR. Result: the receive buffer was never written
       (it kept whatever the caller had memset it to) while the channel still
       reported "transfer complete" and RxCplt fired, and the RX FIFO was never
       drained (silent RXOFI, because the HAL does not check it).
       Compare HAL_SPI_Transmit_DMA (buf -> TDR) and
       HAL_SPI_TransmitReceive_DMA (RDR -> pRxData), which are both correct. */
    if (HAL_DMA_Start_IT(hdma, (uint32_t)(&hspi->Instance->RDR), (uint32_t)(pData), (uint32_t)Size) != HAL_OK) {
        SPI_CloseTransfer(hspi);
        hspi->State = HAL_SPI_STATE_READY;
        return HAL_ERROR;
    }
    return HAL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with DMA.
  * @param[in,out]  hspi    Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  pTxData Pointer to transmission data buffer.
  * @param[out]  pRxData Pointer to reception data buffer.
  * @param[in]  Size    Amount of data to be sent and received.
  * @return HAL status
  * @retval HAL_OK       Transfer started.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking. The library binds the transfer callbacks and starts the DMA
  *         channel itself, so the DMA handle passed in must be initialized beforehand.
  *         Completion via HAL_SPI_TxRxCpltCallback.
  * @ref    HAL_SPI_Transmit_DMA HAL_SPI_Receive_DMA HAL_SPI_TransmitReceive_IT
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdmatx,
                                              HAL_DMA_HandleTypeDef *hdmarx, uint8_t *pTxData,
                                              uint8_t *pRxData, uint16_t Size)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    /* Check transmit/receive parameters */
        if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U) || (hdmatx == NULL) || (hdmarx == NULL)) {
        return HAL_INVALID;
    }

    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
    hspi->State       = HAL_SPI_STATE_BUSY_TX_RX;

    hspi->pTxBuffPtr  = pTxData;
    hspi->TxXferSize  = Size;
    hspi->TxXferCount = Size;

    hspi->pRxBuffPtr  = pRxData;
    hspi->RxXferSize  = Size;
    hspi->RxXferCount = Size;

    /* Enable TX and RX */
    LL_SPI_EnableTx(hspi->Instance);
    LL_SPI_EnableRx(hspi->Instance);

    /* Enable TX and RX DMA */
    LL_SPI_EnableDMAReq_TX(hspi->Instance);
    LL_SPI_EnableDMAReq_RX(hspi->Instance);
    hspi->TxDMAEnable = HAL_SPI_FUNC_ENABLE;
    hspi->RxDMAEnable = HAL_SPI_FUNC_ENABLE;

    /* Enable SPI */
    LL_SPI_Enable(hspi->Instance);

    /* In master mode, set count and start */
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_SetMasterTxRxCount(hspi->Instance, (uint32_t)Size);
        LL_SPI_StartMasterTxRx(hspi->Instance);
    }

    /* Enable TX and RX complete interrupts for DMA completion */
    LL_SPI_EnableIT_TXCI(hspi->Instance);
    LL_SPI_EnableIT_RXCI(hspi->Instance);
    LL_SPI_EnableIT_OPFI(hspi->Instance);


    LL_SPI_SetTxFIFOEmptyThreshold(hspi->Instance, 0x2U);

    hdmatx->XferCpltCallback     = SPI_DMATransmitCplt;
    hdmatx->XferHalfCpltCallback = SPI_DMATxHalfCplt;
    hdmatx->XferErrorCallback    = SPI_DMAError;
    hdmatx->Parent               = (void *)hspi;
    hdmarx->XferCpltCallback     = SPI_DMAReceiveCplt;
    hdmarx->XferHalfCpltCallback = SPI_DMATxRxHalfCplt;
    hdmarx->XferErrorCallback    = SPI_DMAError;
    hdmarx->Parent               = (void *)hspi;
    if (HAL_DMA_Start_IT(hdmarx, (uint32_t)(&hspi->Instance->RDR), (uint32_t)(pRxData), (uint32_t)Size) != HAL_OK) {
        SPI_CloseTransfer(hspi);
        hspi->State = HAL_SPI_STATE_READY;
        return HAL_ERROR;
    }
    if (HAL_DMA_Start_IT(hdmatx, (uint32_t)(pTxData), (uint32_t)(&hspi->Instance->TDR), (uint32_t)Size) != HAL_OK) {
        SPI_CloseTransfer(hspi);
        hspi->State = HAL_SPI_STATE_READY;
        return HAL_ERROR;
    }
    return HAL_OK;
}

/**
  * @brief  Pause the DMA Transfer.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       DMA paused.
  * @note   Temporarily disables SPI DMA requests without stopping the transfer.
  * @ref    HAL_SPI_DMAResume HAL_SPI_DMAStop
  */
HAL_StatusTypeDef HAL_SPI_DMAPause(HAL_SPI_HandleTypeDef *hspi)
{

    /* Disable SPI DMA requests */
    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    LL_SPI_DisableDMAReq_RX(hspi->Instance);

    return HAL_OK;
}

/**
  * @brief  Resume the DMA Transfer.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       DMA resumed.
  * @note   Re-enables SPI DMA requests after HAL_SPI_DMAPause.
  * @ref    HAL_SPI_DMAPause HAL_SPI_DMAStop
  */
HAL_StatusTypeDef HAL_SPI_DMAResume(HAL_SPI_HandleTypeDef *hspi)
{

    /* Enable SPI DMA requests */
    if (hspi->TxDMAEnable == HAL_SPI_FUNC_ENABLE) {
        LL_SPI_EnableDMAReq_TX(hspi->Instance);
    }

    if (hspi->RxDMAEnable == HAL_SPI_FUNC_ENABLE) {
        LL_SPI_EnableDMAReq_RX(hspi->Instance);
    }

    return HAL_OK;
}

/**
  * @brief  Stop the DMA Transfer.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       DMA stopped.
  * @note   Disables SPI DMA requests and closes the transfer, restoring
  *         the SPI handle to READY state.
  * @ref    HAL_SPI_DMAPause
  */
HAL_StatusTypeDef HAL_SPI_DMAStop(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdmatx,
                             HAL_DMA_HandleTypeDef *hdmarx)
{
    if (hspi == NULL) {
        return HAL_INVALID;
    }

    if ((hdmatx != NULL) &&
        ((hspi->State == HAL_SPI_STATE_BUSY_TX) || (hspi->State == HAL_SPI_STATE_BUSY_TX_RX))) {
        LL_SPI_DisableDMAReq_TX(hspi->Instance);
        if (HAL_DMA_Abort(hdmatx) != HAL_OK) {
            hspi->ErrorCode |= HAL_SPI_ERROR_DMA;
        }
        hspi->TxXferCount = 0U;
    }

    if ((hdmarx != NULL) &&
        ((hspi->State == HAL_SPI_STATE_BUSY_RX) || (hspi->State == HAL_SPI_STATE_BUSY_TX_RX))) {
        LL_SPI_DisableDMAReq_RX(hspi->Instance);
        if (HAL_DMA_Abort(hdmarx) != HAL_OK) {
            hspi->ErrorCode |= HAL_SPI_ERROR_DMA;
        }
        hspi->RxXferCount = 0U;
    }

    SPI_CloseTransfer(hspi);
    hspi->State = HAL_SPI_STATE_READY;

    return HAL_OK;
}

/* Abort functions ***********************************************************/

/**
  * @brief  Abort the ongoing transfer (blocking mode).
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       Abort completed.
  * @ref    HAL_SPI_Abort_IT
  */
HAL_StatusTypeDef HAL_SPI_Abort(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdmatx,
                                HAL_DMA_HandleTypeDef *hdmarx)
{
    if (hspi == NULL) {
        return HAL_INVALID;
    }
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_SPI_DisableIT_OPFI(hspi->Instance);

    if ((hdmatx != NULL) &&
        ((hspi->State == HAL_SPI_STATE_BUSY_TX) || (hspi->State == HAL_SPI_STATE_BUSY_TX_RX))) {
        LL_SPI_DisableDMAReq_TX(hspi->Instance);
        hdmatx->XferAbortCallback = NULL;
        if (HAL_DMA_Abort(hdmatx) != HAL_OK) {
            hspi->ErrorCode |= HAL_SPI_ERROR_DMA;
        }
        hspi->TxXferCount = 0U;
    }

    if ((hdmarx != NULL) &&
        ((hspi->State == HAL_SPI_STATE_BUSY_RX) || (hspi->State == HAL_SPI_STATE_BUSY_TX_RX))) {
        LL_SPI_DisableDMAReq_RX(hspi->Instance);
        hdmarx->XferAbortCallback = NULL;
        if (HAL_DMA_Abort(hdmarx) != HAL_OK) {
            hspi->ErrorCode |= HAL_SPI_ERROR_DMA;
        }
        hspi->RxXferCount = 0U;
    }

    SPI_AbortTransfer(hspi);


    return (((hspi->ErrorCode & HAL_SPI_ERROR_ABORT) != 0UL) ? HAL_ERROR : HAL_OK);
}

/**
  * @brief  Abort the ongoing transfer (interrupt mode).
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       Abort started/completed.
  * @ref    HAL_SPI_Abort
  */
HAL_StatusTypeDef HAL_SPI_Abort_IT(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdmatx,
                                   HAL_DMA_HandleTypeDef *hdmarx)
{
    uint32_t tx_act;
    uint32_t rx_act;

    if (hspi == NULL) {
        return HAL_INVALID;
    }
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    tx_act = ((hdmatx != NULL) &&
              ((hspi->State == HAL_SPI_STATE_BUSY_TX) || (hspi->State == HAL_SPI_STATE_BUSY_TX_RX))) ? 1U : 0U;
    rx_act = ((hdmarx != NULL) &&
              ((hspi->State == HAL_SPI_STATE_BUSY_RX) || (hspi->State == HAL_SPI_STATE_BUSY_TX_RX))) ? 1U : 0U;

    hspi->State = ((tx_act != 0U) || (rx_act != 0U)) ? HAL_SPI_STATE_ABORT : HAL_SPI_STATE_READY;

    LL_SPI_DisableIT_OPFI(hspi->Instance);
    if (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_MASTER) {
        LL_SPI_StopMasterTxRx(hspi->Instance);
    }

    if (tx_act != 0U) {
        LL_SPI_DisableDMAReq_TX(hspi->Instance);
        hdmatx->XferAbortCallback = SPI_DMATxAbortCallback;
        hspi->TxXferCount = 0U;
        if (HAL_DMA_Abort_IT(hdmatx) != HAL_OK) {
            hdmatx->XferAbortCallback = NULL;
            SPI_DMATxAbortCallback(hdmatx);
        }
    }

    if (rx_act != 0U) {
        LL_SPI_DisableDMAReq_RX(hspi->Instance);
        hdmarx->XferAbortCallback = SPI_DMARxAbortCallback;
        hspi->RxXferCount = 0U;
        if (HAL_DMA_Abort_IT(hdmarx) != HAL_OK) {
            hdmarx->XferAbortCallback = NULL;
            SPI_DMARxAbortCallback(hdmarx);
        }
    }

    if ((tx_act == 0U) && (rx_act == 0U)) {
        SPI_AbortTransfer(hspi);
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
        hspi->AbortCpltCallback(hspi);
#else
        HAL_SPI_AbortCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
    }

    return HAL_OK;
}

/* IRQ handler ***************************************************************/

/**
  * @brief  Handle SPI interrupt request.
  *         Process all interrupt types: TX FIFO empty, RX FIFO full,
  *         TX complete, RX complete, mode fault, and operation fault.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   Place this handler in the SPI IRQ vector (e.g. SPI0_IRQHandler).
  *         NULL handle is silently ignored (programming error).
  * @ref    HAL_SPI_Transmit_IT HAL_SPI_Receive_IT HAL_SPI_TransmitReceive_IT
  */
void HAL_SPI_IRQHandler(HAL_SPI_HandleTypeDef *hspi)
{
    uint32_t it_source;
    uint32_t it_status;
    uint32_t int_flag;
    uint32_t dat;

    if (hspi == NULL) {
        return;
    }
    ASSERT_FUNC_PARAM(hspi != NULL);

    it_source = LL_SPI_GetAllIntEn(hspi->Instance);
    it_status = LL_SPI_IsActiveFlag_AllIntPnd(hspi->Instance);
    int_flag = it_source & it_status;

    /* Check for operation fault */
    if ((int_flag & LL_SPI_INT_OPFI) != 0UL) {
        LL_SPI_ClearFlag_OPFI(hspi->Instance);
        hspi->ErrorCode |= HAL_SPI_ERROR_OPF;

        if (hspi->ErrorCode != HAL_SPI_ERROR_NONE) {
            SPI_CloseTransfer(hspi);
            hspi->State = HAL_SPI_STATE_ERROR;
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
            hspi->ErrorCallback(hspi);
#else
            HAL_SPI_ErrorCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
        }
        return;
    }

    /* Check for mode fault */
    if ((int_flag & LL_SPI_INT_MDFI) != 0UL) {
        LL_SPI_ClearFlag_MDFI(hspi->Instance);
        hspi->ErrorCode |= HAL_SPI_ERROR_MODF;

        if (hspi->ErrorCode != HAL_SPI_ERROR_NONE) {
            SPI_CloseTransfer(hspi);
            hspi->State = HAL_SPI_STATE_ERROR;
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
            hspi->ErrorCallback(hspi);
#else
            HAL_SPI_ErrorCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
        }
        return;
    }

    /* TX FIFO Empty: feed more data */
    if ((int_flag & LL_SPI_INT_TXEI) != 0UL) {
        if (hspi->pTxBuffPtr == NULL) {
            while (LL_SPI_IsActiveFlag_TFF(hspi->Instance) == 0UL) {
                LL_SPI_WriteData(hspi->Instance, 0xFFFFU);
            }
        } else {
            /* Fill TX FIFO while not full and data remains */
            while ((hspi->TxXferCount > 0U) && (LL_SPI_IsActiveFlag_TFF(hspi->Instance) == 0UL)) {
                if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
                    dat = (uint32_t)(*(hspi->pTxBuffPtr));
                    hspi->pTxBuffPtr++;
                    dat |= ((uint32_t)(*(hspi->pTxBuffPtr))) << 8U;
                    hspi->pTxBuffPtr++;
                } else {
                    dat = (uint32_t)(*(hspi->pTxBuffPtr));
                    hspi->pTxBuffPtr++;
                }
                hspi->TxXferCount--;
                LL_SPI_WriteData(hspi->Instance, (dat & 0xFFFFU));
            }

            /* If all data fed, disable TX FIFO empty interrupt */
            if (hspi->TxXferCount == 0U) {
                LL_SPI_DisableIT_TXEI(hspi->Instance);
            }

                if ((hspi->TxXferSize > 1U) &&
                (hspi->TxXferCount == (uint16_t)(hspi->TxXferSize - (hspi->TxXferSize >> 1U)))) {
                if (hspi->State == HAL_SPI_STATE_BUSY_TX_RX) {
                    if (hspi->RxXferCount == (uint16_t)(hspi->RxXferSize - (hspi->RxXferSize >> 1U))) {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
                        hspi->TxRxHalfCpltCallback(hspi);
#else
                        HAL_SPI_TxRxHalfCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
                    }
                } else if (hspi->State == HAL_SPI_STATE_BUSY_TX) {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
                    hspi->TxHalfCpltCallback(hspi);
#else
                    HAL_SPI_TxHalfCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
                }
            }
        }
    }

    /* RX FIFO Full: read received data */
    if ((int_flag & LL_SPI_INT_RXFI) != 0UL) {
        /* Read RX FIFO while not empty and buffer space available */
        while ((hspi->RxXferCount > 0U) && (LL_SPI_IsActiveFlag_RFE(hspi->Instance) == 0UL)) {
            dat = LL_SPI_ReadData(hspi->Instance);

            if (LL_SPI_GetDataWidth(hspi->Instance) >= HAL_SPI_DATASIZE_9BIT) {
                *(hspi->pRxBuffPtr) = (uint8_t)(dat & 0xFFU);
                hspi->pRxBuffPtr++;
                *(hspi->pRxBuffPtr) = (uint8_t)((dat >> 8U) & 0xFFU);
                hspi->pRxBuffPtr++;
            } else {
                *(hspi->pRxBuffPtr) = (uint8_t)(dat & 0xFFU);
                hspi->pRxBuffPtr++;
            }
            hspi->RxXferCount--;
        }

        /* If all data received, disable RX FIFO full interrupt */
        if (hspi->RxXferCount == 0U) {
            LL_SPI_DisableIT_RXFI(hspi->Instance);
        }

        if ((hspi->State == HAL_SPI_STATE_BUSY_RX) && (hspi->RxXferSize > 1U) &&
            (hspi->RxXferCount == (uint16_t)(hspi->RxXferSize - (hspi->RxXferSize >> 1U)))) {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
            hspi->RxHalfCpltCallback(hspi);
#else
            HAL_SPI_RxHalfCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
        }

    }

    /* TX Complete */
    if ((int_flag & LL_SPI_INT_TXCI) != 0UL) {
        LL_SPI_ClearFlag_TXCI(hspi->Instance);

        /* Call the TX complete callback when all data has been sent */
        if ((hspi->TxXferCount == 0U) && (hspi->State == HAL_SPI_STATE_BUSY_TX)) {
            hspi->State = HAL_SPI_STATE_READY;
            SPI_CloseTransfer(hspi);
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
            hspi->TxCpltCallback(hspi);
#else
            HAL_SPI_TxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
        }
    }

    /* RX Complete */
    if ((int_flag & LL_SPI_INT_RXCI) != 0UL) {
        LL_SPI_ClearFlag_RXCI(hspi->Instance);

        if ((hspi->RxXferCount == 0U) && (hspi->State == HAL_SPI_STATE_BUSY_RX)) {
            hspi->State = HAL_SPI_STATE_READY;
            SPI_CloseTransfer(hspi);
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
            hspi->RxCpltCallback(hspi);
#else
            HAL_SPI_RxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
        }
    }

    /* TX Done / RX Done for all busy states.
     * This is the fallback completion path used when the transfer counters already
     * reached 0 but TXCI / RXCI never came. The typical case is a SLAVE:
     * HAL_SPI_*_IT() only calls LL_SPI_SetMasterTxRxCount() on the master branch, so
     * a slave never has its hardware transfer counter programmed and TXCI / RXCI are
     * never asserted. (Same for DMA: SPI_DMATransmitCplt / SPI_DMAReceiveCplt only
     * clear XferCount and rely on this block or on TXCI / RXCI to finish.)
     *
     * The callback must be dispatched according to the state the transfer was
     * started with:
     *   BUSY_TX    -> TxCplt    (HAL_SPI_Transmit_IT        / Transmit_DMA)
     *   BUSY_RX    -> RxCplt    (HAL_SPI_Receive_IT         / Receive_DMA)
     *   BUSY_TX_RX -> TxRxCplt  (HAL_SPI_TransmitReceive_IT / TransmitReceive_DMA)
     * Previously this block always called TxRxCpltCallback, so a slave doing pure TX
     * or pure RX never got TxCplt / RxCplt, contradicting the "Completion via
     * HAL_SPI_TxCpltCallback" note of those APIs.
     */
    if ((hspi->TxXferCount == 0U) && (hspi->RxXferCount == 0U)) {
        HAL_SPI_StateTypeDef done_state = hspi->State;

        if ((done_state == HAL_SPI_STATE_BUSY_TX_RX) || (done_state == HAL_SPI_STATE_BUSY) ||
            (done_state == HAL_SPI_STATE_BUSY_TX) || (done_state == HAL_SPI_STATE_BUSY_RX)) {
            hspi->State = HAL_SPI_STATE_READY;
   
            SPI_CloseTransfer(hspi);


            if (done_state == HAL_SPI_STATE_BUSY_TX) {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
                hspi->TxCpltCallback(hspi);
#else
                HAL_SPI_TxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
            } else if (done_state == HAL_SPI_STATE_BUSY_RX) {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
                hspi->RxCpltCallback(hspi);
#else
                HAL_SPI_RxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
            } else {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
                hspi->TxRxCpltCallback(hspi);
#else
                HAL_SPI_TxRxCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
            }
        }
    }
}

/**
  * @brief  DMA TX transfer complete callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__STATIC_FORCEINLINE void SPI_DMATransmitCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if (hspi == NULL) {
        return;
    }

    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    hspi->TxXferCount = 0U;

    /* Full duplex: if the RX side is also done, this is the only chance to close
       the transfer (the TXCI / RXCI branches do not match in BUSY_TX_RX, see the
       note in SPI_CompleteTransferFromDMA). */
    if (hspi->State == HAL_SPI_STATE_BUSY_TX_RX) {
        if (hspi->RxXferCount == 0U) {
            SPI_CompleteTransferFromDMA(hspi);
        }
    } else if ((hspi->State == HAL_SPI_STATE_BUSY_TX) &&
               (LL_SPI_GetMode(hspi->Instance) == LL_SPI_ROLE_SLAVE)) {
        /* Slave TX-only: the hardware transfer counter is only programmed on the
           master branch, so TXCI is never asserted on a slave. Without closing
           here the handle would stay BUSY_TX forever. (A master keeps waiting for
           TXCI on purpose, so that the last frame really left the shifter.) */
        SPI_CompleteTransferFromDMA(hspi);
    }
}

/**
  * @brief  DMA RX transfer complete callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__STATIC_FORCEINLINE void SPI_DMAReceiveCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if (hspi == NULL) {
        return;
    }

    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->RxXferCount = 0U;

    /* RX side fully received (the data is already in RAM) and nothing left on the
       TX side:
       - BUSY_RX    : pure receive (the master still needs a dummy TX DMA to have SCK) -> RxCplt
       - BUSY_TX_RX : full duplex, TX also done -> TxRxCplt
       Do not close while TX is still pending, otherwise in-flight bytes are lost. */
    if (((hspi->State == HAL_SPI_STATE_BUSY_RX) || (hspi->State == HAL_SPI_STATE_BUSY_TX_RX)) &&
        (hspi->TxXferCount == 0U)) {
        SPI_CompleteTransferFromDMA(hspi);
    }
}

/**
  * @brief  DMA TX half transfer callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__STATIC_FORCEINLINE void SPI_DMATxHalfCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if ((hspi == NULL) || (hspi->State != HAL_SPI_STATE_BUSY_TX)) {
        return;
    }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    hspi->TxHalfCpltCallback(hspi);
#else
    HAL_SPI_TxHalfCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA RX half transfer callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__STATIC_FORCEINLINE void SPI_DMARxHalfCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if ((hspi == NULL) || (hspi->State != HAL_SPI_STATE_BUSY_RX)) {
        return;
    }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    hspi->RxHalfCpltCallback(hspi);
#else
    HAL_SPI_RxHalfCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA TxRx half transfer callback (full duplex).
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__STATIC_FORCEINLINE void SPI_DMATxRxHalfCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if ((hspi == NULL) || (hspi->State != HAL_SPI_STATE_BUSY_TX_RX)) {
        return;
    }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    hspi->TxRxHalfCpltCallback(hspi);
#else
    HAL_SPI_TxRxHalfCpltCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA transfer error callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__STATIC_FORCEINLINE void SPI_DMAError(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_SPI_HandleTypeDef *hspi = (HAL_SPI_HandleTypeDef *)(hdma->Parent);

    if (hspi == NULL) {
        return;
    }

    LL_SPI_DisableDMAReq_TX(hspi->Instance);
    LL_SPI_DisableDMAReq_RX(hspi->Instance);
    hspi->ErrorCode |= HAL_SPI_ERROR_DMA;
    hspi->State = HAL_SPI_STATE_ERROR;
    SPI_CloseTransfer(hspi);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    hspi->ErrorCallback(hspi);
#else
    HAL_SPI_ErrorCallback(hspi);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
}

/**
  * @}
  */

/** @defgroup SPI_HAL_Exported_Functions_Group3 Peripheral State and Error functions
  * @{
  */

/**
  * @brief  Return the SPI handle state.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL SPI state (@ref HAL_SPI_StateTypeDef).
  * @note   Used to query whether the peripheral is READY/BUSY in a non-blocking
  *         transfer. The handle must be non-NULL (asserted in debug builds).
  * @ref    HAL_SPI_GetError
  */
HAL_SPI_StateTypeDef HAL_SPI_GetState(HAL_SPI_HandleTypeDef *hspi)
{
    if (hspi == NULL) {
        return HAL_SPI_STATE_RESET;
    }
    ASSERT_FUNC_PARAM(hspi != NULL);

    return (HAL_SPI_StateTypeDef)(hspi->State);
}

/**
  * @brief  Return the SPI error code.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return SPI Error code (bitmask of @ref HAL_SPI_ErrorTypeDef).
  * @note   Cleared automatically when a new transfer is started.
  * @ref    HAL_SPI_GetState HAL_SPI_ErrorCallback
  */
uint32_t HAL_SPI_GetError(HAL_SPI_HandleTypeDef *hspi)
{
    if (hspi == NULL) {
        return HAL_SPI_ERROR_NONE;
    }
    ASSERT_FUNC_PARAM(hspi != NULL);

    return hspi->ErrorCode;
}

/**
  * @}
  */

/* Callback functions --------------------------------------------------------*/
/** @defgroup SPI_HAL_Exported_Functions_Group4 Callbacks SPI HAL Callbacks
  * @{
  */

/**
  * @brief  Tx Transfer completed callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked by IT/DMA on
  *         transmit completion.
  * @ref    HAL_SPI_Transmit_IT HAL_SPI_Transmit_DMA
  */
__WEAK void HAL_SPI_TxCpltCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_TxCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Rx Transfer completed callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked by IT/DMA on
  *         receive completion.
  * @ref    HAL_SPI_Receive_IT HAL_SPI_Receive_DMA
  */
__WEAK void HAL_SPI_RxCpltCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_RxCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  TxRx Transfer completed callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked by IT/DMA on
  *         full-duplex transmit/receive completion.
  * @ref    HAL_SPI_TransmitReceive_IT HAL_SPI_TransmitReceive_DMA
  */
__WEAK void HAL_SPI_TxRxCpltCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_TxRxCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Tx Half Transfer completed callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked when half of the
  *         TX data has been transferred.
  * @ref    HAL_SPI_Transmit_IT HAL_SPI_Transmit_DMA
  */
__WEAK void HAL_SPI_TxHalfCpltCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_TxHalfCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Rx Half Transfer completed callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked when half of the
  *         RX data has been transferred.
  * @ref    HAL_SPI_Receive_IT HAL_SPI_Receive_DMA
  */
__WEAK void HAL_SPI_RxHalfCpltCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_RxHalfCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  TxRx Half Transfer completed callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked when half of the
  *         TxRx data has been transferred.
  * @ref    HAL_SPI_TransmitReceive_IT HAL_SPI_TransmitReceive_DMA
  */
__WEAK void HAL_SPI_TxRxHalfCpltCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_TxRxHalfCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI error callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked on mode fault, overrun,
  *         underrun, or operation fault. Use HAL_SPI_GetError to get the
  *         error code.
  * @ref    HAL_SPI_GetError HAL_SPI_ErrorCallback
  */
__WEAK void HAL_SPI_ErrorCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_ErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI Abort completed callback.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return None
  * @note   User-overridable weak callback; invoked on abort completion.
  * @ref    HAL_SPI_Abort HAL_SPI_Abort_IT
  */
__WEAK void HAL_SPI_AbortCpltCallback(HAL_SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hspi);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SPI_AbortCpltCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/* TAE-specific Extended Configuration APIs ---------------------------------*/

/** @defgroup SPI_HAL_Extended_Functions TAE-specific Extended Functions
  * @{
  */

/**
  * @brief  Configure the SPI TX/RX FIFO threshold values.
  * @param[in,out]  hspi        Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  TxThreshold TX FIFO empty threshold (0~15).
  * @param[in]  RxThreshold RX FIFO full threshold (1~16).
  * @return HAL status
  * @retval HAL_OK       FIFO thresholds configured.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @note   Call after HAL_SPI_Init(). The FIFO threshold controls when
  *         TX_EMPTY and RX_FULL interrupts are generated.
  * @ref    HAL_SPI_Init
  */
HAL_StatusTypeDef HAL_SPI_ConfigFIFOThreshold(HAL_SPI_HandleTypeDef *hspi, uint8_t TxThreshold,
                                                 uint8_t RxThreshold)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if ((hspi->State != HAL_SPI_STATE_READY) && (hspi->State != HAL_SPI_STATE_RESET)) {
        return HAL_BUSY;
    }

    ASSERT_FUNC_PARAM((TxThreshold <= 15U) && (RxThreshold >= 1U) && (RxThreshold <= 16U));
    if ((TxThreshold > 15U) || (RxThreshold == 0U) || (RxThreshold > 16U)) {
        return HAL_INVALID;
    }

    LL_SPI_SetTxFIFOEmptyThreshold(hspi->Instance, TxThreshold);
    LL_SPI_SetRxFIFOThreshold(hspi->Instance, RxThreshold);

    hspi->DefaultCfg.TxFifoEmptyThres = TxThreshold;
    hspi->DefaultCfg.RxFifoFullThres  = RxThreshold;

    return HAL_OK;
}

/**
  * @brief  Enable or disable the SPI loopback mode.
  * @param[in,out]  hspi     Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  NewState HAL_SPI_FUNC_ENABLE or HAL_SPI_FUNC_DISABLE.
  * @return HAL status
  * @retval HAL_OK       Loopback configured.
  * @retval HAL_INVALID    Invalid handle.
  * @retval HAL_BUSY     Peripheral is busy.
  * @note   In loopback mode, the SPI TX path is internally connected to the
  *         RX path, allowing self-test without external connections.
  * @ref    HAL_SPI_ConfigPinSwap
  */
HAL_StatusTypeDef HAL_SPI_ConfigLoopback(HAL_SPI_HandleTypeDef *hspi, HAL_SPI_EnableTypeDef NewState)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    if (NewState == HAL_SPI_FUNC_ENABLE) {
        LL_SPI_EnableLoopback(hspi->Instance);
    } else {
        LL_SPI_DisableLoopback(hspi->Instance);
    }

    hspi->LoopbackEnable = NewState;

    return HAL_OK;
}

/**
  * @brief  Enable or disable the SPI MOSI/MISO pin swap.
  * @param[in,out]  hspi     Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  NewState HAL_SPI_FUNC_ENABLE or HAL_SPI_FUNC_DISABLE.
  * @return HAL status
  * @retval HAL_OK       Pin swap configured.
  * @retval HAL_INVALID    Invalid handle.
  * @retval HAL_BUSY     Peripheral is busy.
  * @note   When enabled, MOSI and MISO pins are swapped internally.
  * @ref    HAL_SPI_ConfigLoopback
  */
HAL_StatusTypeDef HAL_SPI_ConfigPinSwap(HAL_SPI_HandleTypeDef *hspi, HAL_SPI_EnableTypeDef NewState)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    if (NewState == HAL_SPI_FUNC_ENABLE) {
        LL_SPI_EnableMOSIMISOSwap(hspi->Instance);
    } else {
        LL_SPI_DisableMOSIMISOSwap(hspi->Instance);
    }

    hspi->PinSwapEnable = NewState;

    return HAL_OK;
}

/**
  * @brief  Configure the SPI CS mode and polarity.
  * @param[in,out]  hspi       Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  CSMode     CS mode: HAL_SPI_CS_MODE_CONTINUE or HAL_SPI_CS_MODE_ONE.
  * @param[in]  CSPolarity CS polarity: HAL_SPI_CS_POL_INACT_HIGH or HAL_SPI_CS_POL_INACT_LOW.
  * @return HAL status
  * @retval HAL_OK       CS mode configured.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @note   CS mode controls whether CS is kept active between data frames.
  * @ref    HAL_SPI_Init
  */
HAL_StatusTypeDef HAL_SPI_ConfigCSMode(HAL_SPI_HandleTypeDef *hspi, uint32_t CSMode,
                                          uint32_t CSPolarity)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    if ((CSMode != HAL_SPI_CS_MODE_CONTINUE) && (CSMode != HAL_SPI_CS_MODE_ONE)) {
        return HAL_INVALID;
    }

    if ((CSPolarity != HAL_SPI_CS_POL_INACT_HIGH) && (CSPolarity != HAL_SPI_CS_POL_INACT_LOW)) {
        return HAL_INVALID;
    }

    if (CSMode == HAL_SPI_CS_MODE_ONE) {
        LL_SPI_EnableCSPulseMgt(hspi->Instance);
    } else {
        LL_SPI_DisableCSPulseMgt(hspi->Instance);
    }
    LL_SPI_SetCSPolarity(hspi->Instance, CSPolarity);

    hspi->DefaultCfg.CSMode = CSMode;
    hspi->DefaultCfg.CSPolarity  = CSPolarity;

    return HAL_OK;
}

/**
  * @brief  Configure the SPI master timing parameters.
  * @param[in,out]  hspi             Pointer to a HAL_SPI_HandleTypeDef structure.
  * @param[in]  MstRxDelay       Master RX data capture delay (0~7 PCLK cycles).
  * @param[in]  SSIdleness       SS idleness time between frames (0 or 1~32 PCLK cycles).
  * @param[in]  InterDataIdleness Inter-data idleness time (0 or 1~32 PCLK cycles).
  * @return HAL status
  * @retval HAL_OK       Timing configured.
  * @retval HAL_INVALID    Invalid handle or parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @note   These parameters control inter-frame and inter-data spacing in
  *         master mode. Set to 0 to keep the current value unchanged.
  * @ref    HAL_SPI_Init
  */
HAL_StatusTypeDef HAL_SPI_ConfigTiming(HAL_SPI_HandleTypeDef *hspi, uint8_t MstRxDelay,
                                          uint16_t SSIdleness, uint16_t InterDataIdleness)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hspi->State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }

    if (MstRxDelay > 7U) {
        return HAL_INVALID;
    }

    LL_SPI_SetMasterRxDelay(hspi->Instance, MstRxDelay);
    hspi->DefaultCfg.MstRxDelay = MstRxDelay;

    if ((SSIdleness >= 1U) && (SSIdleness <= 32U)) {
        LL_SPI_SetMasterSSIdleness(hspi->Instance, SSIdleness);
        hspi->DefaultCfg.MstSSIdleness = SSIdleness;
    }

    if ((InterDataIdleness >= 1U) && (InterDataIdleness <= 32U)) {
        LL_SPI_SetMasterInterDatIdleness(hspi->Instance, InterDataIdleness);
        hspi->DefaultCfg.MstInterDatIdleness = InterDataIdleness;
    }

    return HAL_OK;
}

/**
  * @brief  Flush the SPI TX FIFO.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       TX FIFO flushed.
  * @retval HAL_INVALID    Invalid handle.
  * @note   Resets the TX FIFO to empty state. Useful for error recovery.
  * @ref    HAL_SPI_FlushRxFifo
  */
HAL_StatusTypeDef HAL_SPI_FlushTxFifo(HAL_SPI_HandleTypeDef *hspi)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_SPI_ResetTxFIFO(hspi->Instance);
    LL_SPI_ClearFlag(hspi->Instance,
                     ( LL_SPI_INT_TXCI | LL_SPI_INT_TXDEI |
                      LL_SPI_INT_TXOFI | LL_SPI_INT_TXUFI));

    /* The discarded bytes may have set TXUFI/TXOFI; those records are meaningless
       once the data is dropped.  Leaving them pending also re-enters the IRQ
       immediately, and an empty FIFO reads back 0xFF/0xFFFF which is easily
       mistaken for real payload. */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    return HAL_OK;
}

/**
  * @brief  Flush the SPI RX FIFO.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return HAL status
  * @retval HAL_OK       RX FIFO flushed.
  * @retval HAL_INVALID    Invalid handle.
  * @note   Resets the RX FIFO to empty state. Useful for error recovery.
  * @ref    HAL_SPI_FlushTxFifo
  */
HAL_StatusTypeDef HAL_SPI_FlushRxFifo(HAL_SPI_HandleTypeDef *hspi)
{
    /* Check NULL pointers */
    ASSERT_FUNC_PARAM(hspi != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(hspi->Instance));
    HAL_SPI_PARAM_CHECK({
        if ((hspi == NULL) || (!IS_SPI_ALL_INSTANCE(hspi->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_SPI_ResetRxFIFO(hspi->Instance);
    LL_SPI_ClearFlag(hspi->Instance,
                     ( LL_SPI_INT_RXCI | LL_SPI_INT_RXDEI |
                      LL_SPI_INT_RXOFI | LL_SPI_INT_RXUFI));

    /* The discarded bytes may have set RXOFI.  Besides being meaningless once the
       data is dropped, a latched RXOFI keeps the hardware from re-asserting RXFI,
       which shows up as "RX stops halfway, handle stuck in BUSY_xxx, ErrorCode
       still NONE" - exactly the second-run failure seen in the ComIT case. */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    return HAL_OK;
}

/**
  * @brief  Get the current RX FIFO fill level.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return RX FIFO data count (0~16); 0 if handle is NULL.
  * @ref    HAL_SPI_GetTxFifoLevel
  */
uint16_t HAL_SPI_GetRxFifoLevel(HAL_SPI_HandleTypeDef *hspi)
{
    if (hspi == NULL) {
        return 0U;
    }
    ASSERT_FUNC_PARAM(hspi != NULL);

    return LL_SPI_GetRxFIFOLevel(hspi->Instance);
}

/**
  * @brief  Get the current TX FIFO fill level.
  * @param[in,out]  hspi  Pointer to a HAL_SPI_HandleTypeDef structure.
 * @param[in]      SPIx  Pointer to a SPI_TypeDef instance.
 * @param[in]      Init  Pointer to a HAL_SPI_InitTypeDef structure that contains
 *                        the configuration information for the SPI module.
  * @return TX FIFO data count (0~16); 0 if handle is NULL.
  * @ref    HAL_SPI_GetRxFifoLevel
  */
uint16_t HAL_SPI_GetTxFifoLevel(HAL_SPI_HandleTypeDef *hspi)
{
    if (hspi == NULL) {
        return 0U;
    }
    ASSERT_FUNC_PARAM(hspi != NULL);

    return LL_SPI_GetTxFIFOLevel(hspi->Instance);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @brief  [Weak] SPI MSP Init — override in user code
  * @param  Instance SPI peripheral
  */
__WEAK void LL_SPI_MspInit(SPI_TypeDef *Instance)
{
    (void)Instance;
}

/**
  * @brief  [Weak] SPI MSP DeInit — override in user code
  * @param  Instance SPI peripheral
  */
__WEAK void LL_SPI_MspDeInit(SPI_TypeDef *Instance)
{
    (void)Instance;
}

#endif /* HAL_SPI_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* SPI */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/