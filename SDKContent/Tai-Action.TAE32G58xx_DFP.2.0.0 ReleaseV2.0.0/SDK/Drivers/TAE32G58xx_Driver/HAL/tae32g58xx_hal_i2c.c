/**
  ******************************************************************************
  * @file    tae32g58xx_hal_i2c.c
  * @author  Tai-Action SD Team
  * @brief   I2C HAL module driver.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 Tai-Action.
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

/* Private macros ------------------------------------------------------------*/

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_I2C_MODULE_ENABLED) && (HAL_I2C_MODULE_ENABLED == 1)

/** @defgroup I2C_HAL I2C Hardware Abstraction Layer
  * @brief HAL layer driver for I2C module.
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/** @defgroup I2C_HAL_Private_Constants I2C HAL Private Constants
  * @{
  */

/* Default SPIKE suppression when the user leaves SpikeSuppressionLimit at 0. */
#define I2C_SPIKE_SUPPRESSION_DEFAULT   0x0AU
#define I2C_MAX_DATA_COUNT_PER_TRANS  255UL       /*!< Max data bytes per single transfer   */

#if defined (USE_HAL_I2C_DMA) && (USE_HAL_I2C_DMA == 1)
#define I2C_DMA_TX_HANDLE(hi2c)               ((hi2c)->hTxDMA)
#define I2C_DMA_RX_HANDLE(hi2c)               ((hi2c)->hRxDMA)
#else
#define I2C_DMA_TX_HANDLE(hi2c)               NULL
#define I2C_DMA_RX_HANDLE(hi2c)               NULL
#endif /* USE_HAL_I2C_DMA */

/**
  * @}
  */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup I2C_HAL_Private_Functions I2C HAL Private Functions
  * @{
  */

#if defined (USE_HAL_I2C_DMA) && (USE_HAL_I2C_DMA == 1)
static void I2C_DMATxCplt(HAL_DMA_HandleTypeDef *hdma);
static void I2C_DMATxDoneCplt(HAL_DMA_HandleTypeDef *hdma);
static void I2C_DMARxCplt(HAL_DMA_HandleTypeDef *hdma);
static void I2C_DMAErrorCplt(HAL_DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef I2C_Master_ISR_DMA(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources);
static HAL_StatusTypeDef I2C_Slave_ISR_DMA(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources);
#endif /* USE_HAL_I2C_DMA */
static HAL_StatusTypeDef I2C_Master_ISR_IT(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources);
static HAL_StatusTypeDef I2C_Slave_ISR_IT(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources);
static void I2C_ITMasterSeqCplt(HAL_I2C_HandleTypeDef *hi2c, uint32_t use_dma);
static HAL_StatusTypeDef I2C_Master_ISR_Core(HAL_I2C_HandleTypeDef *hi2c, uint32_t use_dma,
                                             uint32_t ITFlags, uint32_t ITSources);
static void I2C_ITMasterTxAddrDone(HAL_I2C_HandleTypeDef *hi2c);
static void I2C_FlushTxFIFO(HAL_I2C_HandleTypeDef *hi2c);
static void I2C_SlaveReadRxFIFO(HAL_I2C_HandleTypeDef *hi2c);
static void I2C_EndXfer(HAL_I2C_HandleTypeDef *hi2c, HAL_DMA_HandleTypeDef *hdmatx,
                        HAL_DMA_HandleTypeDef *hdmarx, HAL_I2C_StateTypeDef final_state);

static HAL_StatusTypeDef I2C_IsErrorOccurred(HAL_I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_WaitOnBusBusyUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnMTXAddrDoneUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnMasterDoneUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnTxFIFOFullUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout);

/**
  * @}
  */

/**
  * @brief  Flush the I2C TX FIFO by resetting it.
  * @param[in,out]  hi2c Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  */
static void I2C_FlushTxFIFO(HAL_I2C_HandleTypeDef *hi2c)
{
    LL_I2C_ResetTxFIFO(hi2c->Instance);
}

/**
  * @brief  Drain the slave RX FIFO into the reception buffer.
  * @param[in,out]  hi2c Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   Used by the RX threshold branch and again by the STOP / error
  *         completion paths, so that bytes still sitting in the FIFO when the
  *         master closes the transfer are not lost before the transfer is
  *         reported as complete.
  */
static void I2C_SlaveReadRxFIFO(HAL_I2C_HandleTypeDef *hi2c)
{
    while (LL_I2C_IsRxFIFOEmpty(hi2c->Instance) == 0UL) {
        if (hi2c->XferCount > 0UL) {
            *hi2c->pBuffPtr++ = LL_I2C_ReceiveData8(hi2c->Instance);
            hi2c->XferCount--;
        }
        else {
            /* Dummy read to prevent FIFO overflow */
            (void)LL_I2C_ReceiveData8(hi2c->Instance);
        }
    }
}

/**
  * @brief  Common transfer-termination helper.
  *         Single funnel for every terminal path of the I2C state machine: it stops
  *         the DMA side, stops the I2C side and resets the handle, so the
  *         State / Mode / XferISR triple can never be left half-reset.
  * @param[in,out]  hi2c         Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]      hdmatx       TX DMA channel bound to the running transfer, or NULL
  *                              when the transfer is not carried by the TX DMA.
  * @param[in]      hdmarx       RX DMA channel bound to the running transfer, or NULL
  *                              when the transfer is not carried by the RX DMA.
  * @param[in]      final_state  State to leave the handle in. Every (slave and
  *                              master) transfer is one-shot, so this is always
  *                              HAL_I2C_STATE_READY and the handle is fully idle.
  * @return None
  * @note   Call this BEFORE invoking the completion callback, so that a new transfer
  *         started from within the callback is not clobbered (this was previously
  *         honoured only by I2C_ITMasterSeqCplt and the ER error branch).
  * @ref    I2C_ITMasterSeqCplt I2C_DMATxCplt I2C_DMARxCplt I2C_Slave_ISR_IT
  */
static void I2C_EndXfer(HAL_I2C_HandleTypeDef *hi2c, HAL_DMA_HandleTypeDef *hdmatx,
                        HAL_DMA_HandleTypeDef *hdmarx, HAL_I2C_StateTypeDef final_state)
{
    if (hi2c == NULL) {
        return;
    }

    /* 1) Stop the DMA side, but only when this transfer actually used it. The channels
       belong to the caller (they are the ones handed to the *_DMA transfer function);
       a polling transfer never enables a DMA request, so it must not touch the DMA
       enable bits either. */
    if (hdmatx != NULL) {
        LL_I2C_DisableDMAReq_TX(hi2c->Instance);
        (void)HAL_DMA_Abort(hdmatx);
    }
    if (hdmarx != NULL) {
        LL_I2C_DisableDMAReq_RX(hi2c->Instance);
        (void)HAL_DMA_Abort(hdmarx);
    }

    /* 2) Stop the I2C side, but only for a transfer that was driven by interrupts or
       DMA: a polling transfer polls the status flags and never arms INTREN, so there
       is nothing to turn off for it. XferISR is still set at this point (it is
       cleared further down) and is only non-NULL for an interrupt/DMA transfer. */
    if (hi2c->XferISR != NULL) {
        LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_EVT_MASK | LL_I2C_IT_ERR_MASK);
    }

    /* 3) Reset the handle so a transfer started from the callback starts clean. */
    hi2c->Mode    = HAL_I2C_MODE_NONE;
    hi2c->State   = final_state;
    hi2c->XferISR = NULL;

    /* 4) Restore the default transfer option. Every terminal path of a transfer
       funnels through here, so a stale sequential option (which would make the
       next one-shot transfer look like an intermediate frame and therefore never
       generate STOP) cannot survive the end of a transaction. */
    hi2c->XferOptions = HAL_I2C_FIRST_AND_LAST_FRAME;
}

/**
  * @brief  Abort a blocking master transfer and return the handle to READY.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  */
static void I2C_BlockingAbort(HAL_I2C_HandleTypeDef *hi2c)
{
    if (hi2c == NULL) {
        return;
    }

    LL_I2C_GenerateStopCondition(hi2c->Instance);

    I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);
}

/**
  * @brief  Check and latch blocking-mode bus errors (bus error / arbitration lost).
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return HAL_OK when no bus error is pending, HAL_ERROR otherwise.
  */
static HAL_StatusTypeDef I2C_IsErrorOccurred(HAL_I2C_HandleTypeDef *hi2c)
{
    if (LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) != 0UL) {

        uint32_t frame_end = 0UL;

        if (hi2c->XferCount == 0UL) {
            if ((hi2c->Mode == HAL_I2C_MODE_SLAVE) &&
                (hi2c->State == HAL_I2C_STATE_BUSY_TX)) {
                frame_end = 1UL;
            }
            else if ((hi2c->Mode == HAL_I2C_MODE_MASTER) &&
                     (hi2c->State == HAL_I2C_STATE_BUSY_RX)) {
                frame_end = 1UL;
            }
        }

        LL_I2C_ClearFlag_NACKI(hi2c->Instance);
        if (frame_end == 0UL) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
            return HAL_ERROR;
        }
        return HAL_OK;
    }

    if (LL_I2C_IsActiveFlag_BUSEI(hi2c->Instance) != 0UL) {
        LL_I2C_ClearFlag_BUSEI(hi2c->Instance);
        hi2c->ErrorCode |= HAL_I2C_ERROR_BERR;
        return HAL_ERROR;
    }

    if (LL_I2C_IsActiveFlag_ARBFI(hi2c->Instance) != 0UL) {
        LL_I2C_ClearFlag_ARBFI(hi2c->Instance);
        hi2c->ErrorCode |= HAL_I2C_ERROR_ARLO;
        return HAL_ERROR;
    }

    if (LL_I2C_IsActiveFlag_RXOFI(hi2c->Instance) != 0UL) {
        LL_I2C_ClearFlag_RXOFI(hi2c->Instance);
        hi2c->ErrorCode |= HAL_I2C_ERROR_RXOVR | HAL_I2C_ERROR_OVR;
        return HAL_ERROR;
    }

    if (LL_I2C_IsActiveFlag_RXUFI(hi2c->Instance) != 0UL) {
        LL_I2C_ClearFlag_RXUFI(hi2c->Instance);
        hi2c->ErrorCode |= HAL_I2C_ERROR_RXUNF | HAL_I2C_ERROR_OVR;
        return HAL_ERROR;
    }

    if (LL_I2C_IsActiveFlag_TXOFI(hi2c->Instance) != 0UL) {
        LL_I2C_ClearFlag_TXOFI(hi2c->Instance);
        hi2c->ErrorCode |= HAL_I2C_ERROR_TXOVR | HAL_I2C_ERROR_OVR;
        return HAL_ERROR;
    }

    if (LL_I2C_IsActiveFlag_TXUFI(hi2c->Instance) != 0UL) {
        LL_I2C_ClearFlag_TXUFI(hi2c->Instance);
        hi2c->ErrorCode |= HAL_I2C_ERROR_TXUNF | HAL_I2C_ERROR_OVR;
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Wait for the I2C bus to become idle.
  * @param[in,out]  hi2c    Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  Timeout Timeout duration in milliseconds.
  * @return HAL status
  */
static HAL_StatusTypeDef I2C_WaitOnBusBusyUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout)
{
    uint32_t tickstart = HAL_GetTick();

    while (LL_I2C_IsActiveFlag_BUSY(hi2c->Instance) != 0UL) {
        if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
            return HAL_ERROR;
        }


        if (HAL_GetTick() - tickstart >= Timeout) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Wait for the I2C master TX address done flag.
  * @param[in,out]  hi2c    Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  Timeout Timeout duration in milliseconds.
  * @return HAL status
  */
static HAL_StatusTypeDef I2C_WaitOnMTXAddrDoneUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout)
{
    uint32_t tickstart = HAL_GetTick();

    while (LL_I2C_IsActiveFlag_MTXAI(hi2c->Instance) == 0UL) {
        if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
            return HAL_ERROR;
        }


        /* Check for NACK */
        if (LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) != 0UL) {
            LL_I2C_ClearFlag_NACKI(hi2c->Instance);
            LL_I2C_GenerateStopCondition(hi2c->Instance);
        
            hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_ERROR;
        }

        /* Check for timeout */
        if (HAL_GetTick() - tickstart >= Timeout) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Wait for the I2C master transfer done flag.
  * @param[in,out]  hi2c    Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  Timeout Timeout duration in milliseconds.
  * @return HAL status
  */
static HAL_StatusTypeDef I2C_WaitOnMasterDoneUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout)
{
    uint32_t tickstart = HAL_GetTick();

    while (LL_I2C_IsActiveFlag_MDEI(hi2c->Instance) == 0UL) {
        if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
            return HAL_ERROR;
        }


        /* Check for NACK */
        if (LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) != 0UL) {
            LL_I2C_ClearFlag_NACKI(hi2c->Instance);
            LL_I2C_GenerateStopCondition(hi2c->Instance);
       
            hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_ERROR;
        }

        /* Check for timeout */
        if (HAL_GetTick() - tickstart >= Timeout) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Wait until the I2C TX FIFO is not full (has space).
  * @param[in,out]  hi2c    Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  Timeout Timeout duration in milliseconds.
  * @return HAL status
  */
static HAL_StatusTypeDef I2C_WaitOnTxFIFOFullUntilTimeout(HAL_I2C_HandleTypeDef *hi2c, uint32_t Timeout)
{
    uint32_t tickstart = HAL_GetTick();

    while (LL_I2C_IsTxFIFOFull(hi2c->Instance) != 0UL) {
        if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
            return HAL_ERROR;
        }


        if (HAL_GetTick() - tickstart >= Timeout) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Handle I2C master TX address done event in interrupt mode.
  *         Load data into TX FIFO for master TX transfers.
  * @param[in,out]  hi2c Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  */
static void I2C_ITMasterTxAddrDone(HAL_I2C_HandleTypeDef *hi2c)
{
    LL_I2C_ClearFlag_MTXAI(hi2c->Instance);

    while ((hi2c->XferCount > 0UL) && (hi2c->XferSize > 0UL) &&
           (LL_I2C_IsTxFIFOFull(hi2c->Instance) == 0UL)) {
        LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
        hi2c->XferCount--;
        hi2c->XferSize--;
    }
}


/**
  * @brief  Handle I2C master transfer completion in interrupt mode.
  *         Receive remaining data from RX FIFO for master RX transfers.
  *         Also handles the MEM mode phase transition from address to data.
  * @param[in,out]  hi2c Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  use_dma 1 when the running transfer hands its data phase over to DMA,
  *                     0 when every phase is served by the CPU.
  * @return None
  * @note   Frame aware: STOP is generated ONLY when the completed frame is the
  *         final one of the transaction. A frame
  *         armed with AUTOEND = 0 leaves the master on hold and the bus owned by
  *         this master; the handle still goes back to READY and the completion
  *         callback is used to chain the next frame, while PreviousState records
  *         that the bus is still owned by this master.
  */
static void I2C_ITMasterSeqCplt(HAL_I2C_HandleTypeDef *hi2c, uint32_t use_dma)
{
    uint32_t direction;
    uint32_t nextCount;
    uint32_t last_chunk;
    uint32_t autoend;

    (void)use_dma;
    LL_I2C_ClearFlag_MDEI(hi2c->Instance);

    if (hi2c->State == HAL_I2C_STATE_BUSY_RX) {
        while ((LL_I2C_IsRxFIFOEmpty(hi2c->Instance) == 0UL) &&
               (hi2c->XferCount > 0UL) && (hi2c->XferSize > 0UL)) {
            *hi2c->pBuffPtr++ = LL_I2C_ReceiveData8(hi2c->Instance);
            hi2c->XferCount--;
            hi2c->XferSize--;
        }
    }

    if (hi2c->XferCount == 0UL) {
        direction = LL_I2C_GetTransferRequest(hi2c->Instance);
        if (LL_I2C_IsEnabledAutoEndMode(hi2c->Instance) == 0UL) {
            LL_I2C_GenerateStopCondition(hi2c->Instance);
        
        }
        I2C_EndXfer(hi2c, I2C_DMA_TX_HANDLE(hi2c), I2C_DMA_RX_HANDLE(hi2c), HAL_I2C_STATE_READY);
        if (direction == LL_I2C_DIRECTION_TRANSMIT) {
            HAL_I2C_MasterTxCpltCallback(hi2c);
        }
        else {
            HAL_I2C_MasterRxCpltCallback(hi2c);
        }
        return;
    }

    if (use_dma != 0UL) {
        hi2c->pBuffPtr += hi2c->XferSize;
        nextCount = (hi2c->XferCount > I2C_MAX_DATA_COUNT_PER_TRANS)
                    ? I2C_MAX_DATA_COUNT_PER_TRANS : hi2c->XferCount;
        hi2c->XferCount -= nextCount;
        hi2c->XferSize = nextCount;
        last_chunk = (hi2c->XferCount == 0UL) ? 1UL : 0UL;
        autoend = last_chunk;
        direction = LL_I2C_GetTransferRequest(hi2c->Instance);

        LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)hi2c->Devaddress);
        LL_I2C_SetTransferRequest(hi2c->Instance, direction);
        LL_I2C_SetTransferSize(hi2c->Instance, nextCount);
        if (autoend != 0UL) {
            LL_I2C_EnableAutoEndMode(hi2c->Instance);
        }
        else {
            LL_I2C_DisableAutoEndMode(hi2c->Instance);
					
        }

        if (direction == LL_I2C_DIRECTION_TRANSMIT) {
            LL_I2C_ReleaseCommand(hi2c->Instance);
            LL_I2C_EnableDMAReq_TX(hi2c->Instance);
            (void)HAL_DMA_Start_IT(I2C_DMA_TX_HANDLE(hi2c),
                                   (uint32_t)hi2c->pBuffPtr,
                                   (uint32_t)&hi2c->Instance->TXDATA,
                                   (uint32_t)nextCount);
        }
        else {
            LL_I2C_ReleaseCommand(hi2c->Instance);
            LL_I2C_EnableDMAReq_RX(hi2c->Instance);
            (void)HAL_DMA_Start_IT(I2C_DMA_RX_HANDLE(hi2c),
                                   (uint32_t)&hi2c->Instance->RXDATA,
                                   (uint32_t)hi2c->pBuffPtr,
                                   (uint32_t)nextCount);
        }
        return;
    }

    nextCount = (hi2c->XferCount > I2C_MAX_DATA_COUNT_PER_TRANS)
                ? I2C_MAX_DATA_COUNT_PER_TRANS : hi2c->XferCount;
    last_chunk = (nextCount == hi2c->XferCount) ? 1UL : 0UL;
    autoend = last_chunk;

    hi2c->XferSize = nextCount;
    direction = LL_I2C_GetTransferRequest(hi2c->Instance);

    LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)hi2c->Devaddress);
    LL_I2C_SetTransferRequest(hi2c->Instance, direction);
    LL_I2C_SetTransferSize(hi2c->Instance, nextCount);
    if (autoend != 0UL) {
        LL_I2C_EnableAutoEndMode(hi2c->Instance);
    }
    else {
        LL_I2C_DisableAutoEndMode(hi2c->Instance);
    }

    if (direction == LL_I2C_DIRECTION_TRANSMIT) {
        LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
        hi2c->XferCount--;
        hi2c->XferSize--;
        if (hi2c->XferCount > 0UL) {
            LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_TXEIE);
        }
    }
    LL_I2C_ReleaseCommand(hi2c->Instance);
}


/* Exported functions --------------------------------------------------------*/

/** @defgroup I2C_HAL_Exported_Functions_Group1 Initialization and De-initialization functions
  * @{
  */

/**
  * @brief  Initialize the I2C according to the specified parameters in the
  *         HAL_I2C_InitTypeDef and initialize the associated handle.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  I2Cx  I2C peripheral instance (I2C0 or I2C1).
  * @param[in]  Init  Pointer to a HAL_I2C_InitTypeDef structure that holds the configuration.
  *               The configuration is taken from this parameter, not from a field stored in the
  *               handle (HAL2 style: no global Init in the handle).
  * @return HAL status
  * @retval HAL_OK       Init success; peripheral is in READY state.
  * @retval HAL_INVALID    Invalid handle, invalid instance or invalid Init parameters.
  * @retval HAL_BUSY     Peripheral is already initialized or busy.
  * @note   Must be called once before any transfer (blocking / IT / DMA).
  *         After return, the handle state is HAL_I2C_STATE_READY and
  *         the I2C peripheral is enabled. The DMA handles are cleared;
  *         call HAL_I2C_SetTxDMA()/HAL_I2C_SetRxDMA() before DMA transfers.
  * @ref    HAL_I2C_DeInit HAL_I2C_MspInit
  */
HAL_StatusTypeDef HAL_I2C_Init(HAL_I2C_HandleTypeDef *hi2c, I2C_TypeDef *I2Cx, HAL_I2C_InitTypeDef *Init)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(I2Cx));
    ASSERT_FUNC_PARAM(Init != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ADDRESSING_MODE(Init->AddressingMode));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_OWN_ADDRESS1(Init->OwnAddress1));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DUALADDRESS(Init->DualAddressMode));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_GENERAL_CALL(Init->GeneralCallMode));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_NO_STRETCH(Init->NoStretchMode));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_OWN_ADDRESS2(Init->OwnAddress2));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_OWN_ADDRESS2_MASK(Init->OwnAddress2Masks));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_TXFIFO_THRESHOLD(Init->TxFifoThreshold));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_RXFIFO_THRESHOLD(Init->RxFifoThreshold));

    /* Configurable parameter checks */
    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(I2Cx)) || (Init == NULL)) {
            return HAL_INVALID;
        }

        if (!IS_HAL_I2C_ADDRESSING_MODE(Init->AddressingMode)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_OWN_ADDRESS1(Init->OwnAddress1)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_DUALADDRESS(Init->DualAddressMode)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_GENERAL_CALL(Init->GeneralCallMode)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_NO_STRETCH(Init->NoStretchMode)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_OWN_ADDRESS2(Init->OwnAddress2)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_OWN_ADDRESS2_MASK(Init->OwnAddress2Masks)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_TXFIFO_THRESHOLD(Init->TxFifoThreshold)) {
            return HAL_INVALID;
        }
        if (!IS_HAL_I2C_RXFIFO_THRESHOLD(Init->RxFifoThreshold)) {
            return HAL_INVALID;
        }
        if ((Init->SpikeSuppressionLimit > LL_I2C_SPIKE_SUPPR_MAX) ||
            (Init->SlaveTxSetupDelay > LL_I2C_TIMING_DELAY_MAX) ||
            (Init->RxCaptureDelay > LL_I2C_TIMING_DELAY_MAX) ||
            (Init->TxHoldDelay > LL_I2C_TIMING_DELAY_MAX)) {
            return HAL_INVALID;
        }

        /* SCL counts are optional (slave), but must be a valid pair when used. */
        if (((Init->SCLHigh == 0U) && (Init->SCLLow != 0U)) ||
            ((Init->SCLHigh != 0U) && (Init->SCLLow == 0U)) ||
            (Init->SCLHigh > LL_I2C_SCL_CNT_MAX) ||
            (Init->SCLLow > LL_I2C_SCL_CNT_MAX)) {
            return HAL_INVALID;
        }
    });

    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_RESET, HAL_I2C_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Bind the instance passed by the caller */
    hi2c->Instance = I2Cx;

#if defined (USE_HAL_I2C_DMA) && (USE_HAL_I2C_DMA == 1)
    hi2c->hTxDMA = NULL;
    hi2c->hRxDMA = NULL;
#endif /* USE_HAL_I2C_DMA */

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)    /* Init the I2C Callback settings with legacy weak functions */
    hi2c->MasterTxCpltCallback = HAL_I2C_MasterTxCpltCallback;
    hi2c->MasterRxCpltCallback = HAL_I2C_MasterRxCpltCallback;
    hi2c->SlaveTxCpltCallback  = HAL_I2C_SlaveTxCpltCallback;
    hi2c->SlaveRxCpltCallback  = HAL_I2C_SlaveRxCpltCallback;
    hi2c->ListenCpltCallback   = HAL_I2C_ListenCpltCallback;
    hi2c->MemTxCpltCallback    = HAL_I2C_MemTxCpltCallback;
    hi2c->MemRxCpltCallback    = HAL_I2C_MemRxCpltCallback;
    hi2c->ErrorCallback        = HAL_I2C_ErrorCallback;
    hi2c->AbortCpltCallback    = HAL_I2C_AbortCpltCallback;
    /* Address-match callback must be defaulted here as well: with the registration
       API enabled the address branches invoke it through the handle and skip a NULL
       one instead of falling back to the weak function, so a handle that was never
       registered would silently drop every address match. */
    hi2c->AddrCallback         = HAL_I2C_AddrCallback;

    if (hi2c->MspInitCallback == NULL) {
        hi2c->MspInitCallback = HAL_I2C_MspInit;
    }

    /* Init the low level hardware: GPIO, CLOCK, NVIC */
    hi2c->MspInitCallback(hi2c);
#else
    /* Initialize the low level hardware: GPIO, CLOCK, NVIC */
    HAL_I2C_MspInit(hi2c);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

    /* Disable the I2C peripheral before configuration */
    LL_I2C_Disable(hi2c->Instance);

    /* Configure I2C addressing mode */
    if (Init->AddressingMode == HAL_I2C_ADDRESSINGMODE_7BIT) {
        LL_I2C_SetMasterAddressingMode(hi2c->Instance, LL_I2C_ADDRESSINGMODE_7BIT);
    }
    else {
        LL_I2C_SetMasterAddressingMode(hi2c->Instance, LL_I2C_ADDRESSINGMODE_10BIT);
    }

    /* Configure own address 1 */
    LL_I2C_SetOwnAddress1(hi2c->Instance, Init->OwnAddress1);

    /* Configure dual addressing mode */
    if (Init->DualAddressMode == HAL_I2C_DUALADDRESS_ENABLE) {
        LL_I2C_EnableOwnAddress2(hi2c->Instance);
        LL_I2C_SetOwnAddress2(hi2c->Instance, Init->OwnAddress2, Init->OwnAddress2Masks);
    }
    else {
        LL_I2C_DisableOwnAddress2(hi2c->Instance);
    }

    /* Configure General Call mode */
    if (Init->GeneralCallMode == HAL_I2C_GENERALCALL_ENABLE) {
        LL_I2C_EnableGeneralCall(hi2c->Instance);
    }
    else {
        LL_I2C_DisableGeneralCall(hi2c->Instance);
    }

    /* Configure No Stretch mode. NSTCH affects slave reception; MSTCH/RFHSEN
       only matter when the master drives the clock, so they are configured
       when SCL counts are supplied. */
    if (Init->NoStretchMode == HAL_I2C_NOSTRETCH_ENABLE) {
        LL_I2C_DisableClockStretching(hi2c->Instance);
    }
    else {
        LL_I2C_EnableClockStretching(hi2c->Instance);
    }

    if ((Init->SCLHigh != 0U) && (Init->SCLLow != 0U)) {
        if (Init->NoStretchMode == HAL_I2C_NOSTRETCH_ENABLE) {
            LL_I2C_DisableMasterClockStretching(hi2c->Instance);
        }
        else {
            LL_I2C_EnableMasterClockStretching(hi2c->Instance);
            LL_I2C_SetRxSCLStretchMode(hi2c->Instance, LL_I2C_RX_SCL_STRETCH_WHEN_NOT_EMPTY);
        }
    }

    /* Flush TX and RX FIFO */
    LL_I2C_ResetTxFIFO(hi2c->Instance);
    LL_I2C_ResetRxFIFO(hi2c->Instance);

    /* Configure BAUD register (SCL clock) when master counts are supplied. */
    if ((Init->SCLHigh != 0U) && (Init->SCLLow != 0U)) {
        LL_I2C_SetSCLHighLowCount(hi2c->Instance, Init->SCLHigh, Init->SCLLow);
    }

    /* Configure FIFO thresholds from the init structure. The RX threshold is
       programmed as Threshold-1 by the LL, so 0 is not a legal value and falls
       back to the documented default of 1. */
    LL_I2C_SetTxFIFOThreshold(hi2c->Instance, Init->TxFifoThreshold);
    LL_I2C_SetRxFIFOThreshold(hi2c->Instance,
                              (Init->RxFifoThreshold == 0UL) ? 1UL : Init->RxFifoThreshold);

    /* Configure each TIMING field separately, never by overwriting the whole
       register. */
    LL_I2C_SetSpikeSuppressionLimit(
        hi2c->Instance,
        (Init->SpikeSuppressionLimit == 0U)
            ? I2C_SPIKE_SUPPRESSION_DEFAULT
            : Init->SpikeSuppressionLimit);
    LL_I2C_SetSlaveTxSetupDelay(hi2c->Instance, Init->SlaveTxSetupDelay);
    LL_I2C_SetRxCaptureDelay(hi2c->Instance, Init->RxCaptureDelay);
    LL_I2C_SetTxHoldDelay(hi2c->Instance, Init->TxHoldDelay);

    /* Timeout thresholds reset to 0, which makes the peripheral report a timeout on
       the very first SCL stretch and lets the error handler abort a healthy transfer.
       Program the maximum period so a real bus hang is still detected; the bus
       timeout watches SCL low so an idle bus never expires. */
    LL_I2C_SetMasterTmextTimeout(hi2c->Instance, LL_I2C_TIMEOUT_TIMING_MAX);
    LL_I2C_SetSlaveTsextTimeout(hi2c->Instance, LL_I2C_TIMEOUT_TIMING_MAX);
    LL_I2C_SetBTOMode_SCLLow(hi2c->Instance);
    LL_I2C_SetBusTimeout(hi2c->Instance, LL_I2C_TIMEOUT_TIMING_MAX);

    /* Clear all interrupt pending flags via LL function */
    LL_I2C_ClearAllIntrFlags(hi2c->Instance);

    /* AUTOEND on, NACK asserted for the next byte.
       Slave receive paths clear NACK to ACK the bytes they receive. */
    LL_I2C_EnableAutoEndMode(hi2c->Instance);
    LL_I2C_AcknowledgeNextData(hi2c->Instance, LL_I2C_NACK);

    /* Enable the I2C peripheral */
    LL_I2C_Enable(hi2c->Instance);

    /* Initialize the error code */
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /* Initialize the I2C state */
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_BUSY, HAL_I2C_STATE_READY, {
        return HAL_ERROR;
    });
    hi2c->Mode = HAL_I2C_MODE_NONE;


    /* Return function status */

    return HAL_OK;
}

/**
  * @brief  DeInitialize the I2C peripheral.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return HAL status
  * @retval HAL_OK       DeInit success; handle state is RESET.
  * @retval HAL_INVALID    Invalid handle or invalid instance.
  * @note   After this call, the handle cannot be used for transfer until
  *         HAL_I2C_Init() is called again.
  * @ref    HAL_I2C_Init HAL_I2C_MspDeInit
  */
HAL_StatusTypeDef HAL_I2C_DeInit(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Check the I2C handle allocation */
    /* Check NULL pointers */
    if (hi2c == NULL) {
        return HAL_INVALID;
    }

    /* Check the parameter - return HAL_ERROR instead of assert */
    HAL_I2C_PARAM_CHECK({
        if (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance)) {
            hi2c->ErrorCode = HAL_I2C_ERROR_INVALID_PARAM;
            return HAL_INVALID;
        }
    });


    /* Change I2C peripheral state */
    hi2c->State = HAL_I2C_STATE_BUSY;

    /* Disable all interrupts */
    LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_ERR_MASK | LL_I2C_IT_EVT_MASK);

    /* Disable the I2C peripheral */
    LL_I2C_Disable(hi2c->Instance);

    /* Reset TX and RX FIFO */
    LL_I2C_ResetTxFIFO(hi2c->Instance);
    LL_I2C_ResetRxFIFO(hi2c->Instance);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    if (hi2c->MspDeInitCallback == NULL) {
        hi2c->MspDeInitCallback = HAL_I2C_MspDeInit;
    }
    hi2c->MspDeInitCallback(hi2c);
#else
    HAL_I2C_MspDeInit(hi2c);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

    /* Reset ErrorCode */
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /* Change I2C peripheral state */
    hi2c->State = HAL_I2C_STATE_RESET;
    hi2c->Mode  = HAL_I2C_MODE_NONE;


    return HAL_OK;
}

/**
  * @brief  Reset both I2C FIFOs and clear pending interrupt flags.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return HAL status
  * @retval HAL_OK      FIFOs and interrupt flags were reset.
  * @retval HAL_INVALID Invalid handle or instance.
  * @retval HAL_BUSY    A transfer is still ongoing.
  */
HAL_StatusTypeDef HAL_I2C_ResetFIFO(HAL_I2C_HandleTypeDef *hi2c)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }
    });

    if (hi2c->State != HAL_I2C_STATE_READY) {
        return HAL_BUSY;
    }

    LL_I2C_ResetTxFIFO(hi2c->Instance);
    LL_I2C_ResetRxFIFO(hi2c->Instance);
    LL_I2C_ClearAllIntrFlags(hi2c->Instance);
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    return HAL_OK;
}

/**
  * @brief  I2C MSP Init.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   This is a weak callback; user should override it to configure
  *         GPIO, CLOCK and NVIC for the I2C peripheral. Called by
  *         HAL_I2C_Init().
  * @ref    HAL_I2C_Init HAL_I2C_MspDeInit
  */
__WEAK void HAL_I2C_MspInit(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_MspInit could be implemented in the user file
     */
}

/**
  * @brief  I2C MSP DeInit.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   This is a weak callback; user should override it to release
  *         GPIO, CLOCK and NVIC. Called by HAL_I2C_DeInit().
  * @ref    HAL_I2C_DeInit HAL_I2C_MspInit
  */
__WEAK void HAL_I2C_MspDeInit(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group2 IO operation functions
  * @{
  */

/**
  * @brief  Transmit in master mode an amount of data in blocking mode.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  DevAddress  Target device address (7-bit or 10-bit depending on init).
  * @param[in]  pData       Pointer to data buffer (uint8_t*).
  * @param[in]  Size        Amount of data to be sent (bytes).
  * @param[in]  Timeout     Timeout duration in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Transmit success.
  * @retval HAL_INVALID  Invalid parameter.
  * @retval HAL_ERROR    Bus error.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  Timeout occurred waiting for bus or completion.
  * @note   Blocking call: returns only after the transfer completes or fails.
  *         HAL_I2C_Init() must have been called first.
  * @ref    HAL_I2C_Master_Receive HAL_I2C_MasterTxCpltCallback
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                          uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint16_t offset;
    uint16_t remaining;
    uint16_t chunk;
    uint16_t sent;
    uint32_t first_chunk;

    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if (!IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress)) {
            return HAL_INVALID;
        }

        if ((pData == NULL) || (Size == 0UL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_TX, {
        return HAL_BUSY;
    });

    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /* Wait until the bus is free */
    status = I2C_WaitOnBusBusyUntilTimeout(hi2c, Timeout);
    if (status != HAL_OK) {
        I2C_BlockingAbort(hi2c);
        return status;
    }

    /* Set target address once; continuation chunks keep the bus and address. */
    LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)DevAddress);

    offset      = 0U;
    remaining   = Size;
    first_chunk = 1U;

    while (remaining > 0U) {
        uint32_t last_chunk = (remaining <= 255U);
        chunk = last_chunk ? remaining : 255U;

        if (first_chunk) {
            LL_I2C_HandleTransfer(hi2c->Instance, LL_I2C_DIRECTION_TRANSMIT,
                                  (uint32_t)chunk, last_chunk ? 1UL : 0UL);
            LL_I2C_TransmitData8(hi2c->Instance, pData[offset]);
            offset++;
            remaining--;
            LL_I2C_ReleaseCommand(hi2c->Instance);

            status = I2C_WaitOnMTXAddrDoneUntilTimeout(hi2c, Timeout);
            if (status != HAL_OK) {
                I2C_BlockingAbort(hi2c);
                return status;
            }
            first_chunk = 0U;
        } else {
            LL_I2C_SetTransferRequest(hi2c->Instance, LL_I2C_DIRECTION_TRANSMIT);
            LL_I2C_SetTransferSize(hi2c->Instance, (uint32_t)chunk);
            if (last_chunk) {
                LL_I2C_EnableAutoEndMode(hi2c->Instance);
            } else {
                LL_I2C_DisableAutoEndMode(hi2c->Instance);
            }
            LL_I2C_TransmitData8(hi2c->Instance, pData[offset]);
            offset++;
            remaining--;
            LL_I2C_ReleaseCommand(hi2c->Instance);
        }

        /* First byte of this chunk is already in the TX FIFO. */
        sent = 1U;
        while (sent < chunk) {
            status = I2C_WaitOnTxFIFOFullUntilTimeout(hi2c, Timeout);
            if (status != HAL_OK) {
                I2C_BlockingAbort(hi2c);
                return status;
            }
            LL_I2C_TransmitData8(hi2c->Instance, pData[offset]);
            offset++;
            remaining--;
            sent++;
        }

        status = I2C_WaitOnMasterDoneUntilTimeout(hi2c, Timeout);
        if (status != HAL_OK) {
            I2C_BlockingAbort(hi2c);
            return status;
        }
        LL_I2C_ClearFlag_MDEI(hi2c->Instance);
    }

    I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);


    return HAL_OK;
}

/**
  * @brief  Receive in master mode an amount of data in blocking mode.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  DevAddress  Target device address (7-bit or 10-bit depending on init).
  * @param[out]  pData       Pointer to data buffer (uint8_t*).
  * @param[in]  Size        Amount of data to be received (bytes).
  * @param[in]  Timeout     Timeout duration in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Receive success.
  * @retval HAL_INVALID  Invalid parameter.
  * @retval HAL_ERROR    Bus error.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @note   Blocking call: returns only after the transfer completes or fails.
  *         HAL_I2C_Init() must have been called first.
  * @ref    HAL_I2C_Master_Transmit HAL_I2C_MasterRxCpltCallback
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                         uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint16_t offset;
    uint16_t remaining;
    uint16_t chunk;
    uint16_t received;
    uint32_t tickstart;
    uint32_t first_chunk;

    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if (!IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress)) {
            return HAL_INVALID;
        }

        if ((pData == NULL) || (Size == 0UL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_RX, {
        return HAL_BUSY;
    });

    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /* Wait until the bus is free */
    status = I2C_WaitOnBusBusyUntilTimeout(hi2c, Timeout);
    if (status != HAL_OK) {
        I2C_BlockingAbort(hi2c);
        return status;
    }

    /* Set target address once; continuation chunks keep the bus and address. */
    LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)DevAddress);

    offset      = 0U;
    remaining   = Size;
    first_chunk = 1U;

    while (remaining > 0U) {
        uint32_t last_chunk = (remaining <= 255U);
        chunk = last_chunk ? remaining : 255U;

        if (first_chunk) {
            LL_I2C_HandleTransfer(hi2c->Instance, LL_I2C_DIRECTION_RECEIVE,
                                  (uint32_t)chunk, last_chunk ? 1UL : 0UL);
            LL_I2C_ReleaseCommand(hi2c->Instance);
            first_chunk = 0U;
        } else {
            LL_I2C_SetTransferRequest(hi2c->Instance, LL_I2C_DIRECTION_RECEIVE);
            LL_I2C_SetTransferSize(hi2c->Instance, (uint32_t)chunk);
            if (last_chunk) {
                LL_I2C_EnableAutoEndMode(hi2c->Instance);
            } else {
                LL_I2C_DisableAutoEndMode(hi2c->Instance);
            }
            LL_I2C_ReleaseCommand(hi2c->Instance);
        }

        /* Drain this chunk while it arrives; do not wait for MDEI first,
           otherwise a chunk larger than the RX FIFO would block. */
        tickstart = HAL_GetTick();
        for (received = 0U; received < chunk; received++) {
            while (LL_I2C_IsRxFIFOEmpty(hi2c->Instance) != 0UL) {
                if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
                    I2C_BlockingAbort(hi2c);
                    return HAL_ERROR;
                }
                if (LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) != 0UL) {
                    LL_I2C_ClearFlag_NACKI(hi2c->Instance);
                    hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
                    I2C_BlockingAbort(hi2c);
                    return HAL_ERROR;
                }
                if ((HAL_GetTick() - tickstart) >= Timeout) {
                    hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
                    I2C_BlockingAbort(hi2c);
                    return HAL_TIMEOUT;
                }
            }
            pData[offset + received] = LL_I2C_ReceiveData8(hi2c->Instance);
        }

        status = I2C_WaitOnMasterDoneUntilTimeout(hi2c, Timeout);
        if (status != HAL_OK) {
            I2C_BlockingAbort(hi2c);
            return status;
        }
        LL_I2C_ClearFlag_MDEI(hi2c->Instance);

        offset    += chunk;
        remaining -= chunk;
    }

    I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);


    return HAL_OK;
}

/**
  * @brief  Transmit in slave mode an amount of data in blocking mode.
  * @param[in,out]  hi2c     Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  pData    Pointer to data buffer (uint8_t*).
  * @param[in]  Size     Amount of data to be sent (bytes).
  * @param[in]  Timeout  Timeout duration in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Transmit success.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @note   Blocking call from the slave perspective; master must clock the SCL.
  *         It returns as soon as the master ends this frame, which it signals either
  *         by NACKing the byte after the last one it wants (the master still owns the
  *         bus - an intermediate frame of a sequential transfer sends no STOP) or by
  *         closing the transaction with STOP. Both endings are accepted, so waiting
  *         for STOP alone is NOT required and would stall multi-frame transfers.
  *         The call ends with the frame, hence nothing that this same frame still
  *         depends on may run after it returns (e.g. the next frame's data): for a
  *         sequential master use HAL_I2C_Slave_Transmit_IT() instead. An IT/DMA
  *         master on the same core keeps running through its ISR while this call
  *         waits, so that combination is allowed.
  *         A NACK that arrives with payload still pending is reported as HAL_ERROR.
  *         Timeout must be a finite value; HAL_MAX_DELAY is rejected.
  * @ref    HAL_I2C_Slave_Receive HAL_I2C_SlaveTxCpltCallback
  */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                         uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart;

    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if ((pData == NULL) || (Size == 0UL) || (Timeout == HAL_MAX_DELAY)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_TX, {
        return HAL_BUSY;
    });

    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    LL_I2C_AcknowledgeNextData(hi2c->Instance, LL_I2C_ACK);
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr  = pData;
    hi2c->XferSize  = Size;
    hi2c->XferCount = Size;

    /* Set slave role */

    /* Reset TX FIFO and clear stale flags before waiting for the address match.
       NACK must be cleared too: it is part of the frame-end detection below. */
    LL_I2C_ResetTxFIFO(hi2c->Instance);
    LL_I2C_ClearFlag_TXADI(hi2c->Instance);
    LL_I2C_ClearFlag_SPETI(hi2c->Instance);
    LL_I2C_ClearFlag_NACKI(hi2c->Instance);

    /* Wait until the master addresses this slave for a read (TXADI) */
    tickstart = HAL_GetTick();

    while (LL_I2C_IsActiveFlag_TXADI(hi2c->Instance) == 0UL) {
        if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);
            return HAL_ERROR;
        }
        if ((HAL_GetTick() - tickstart) >= Timeout) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_TIMEOUT;
        }
    }

    /* Acknowledge the address match, then queue the payload. The peripheral
       holds SCL low while the TX FIFO is empty, so the master waits until the
       data is available and then clocks it out. */
    LL_I2C_ClearFlag_TXADI(hi2c->Instance);

    while (hi2c->XferCount > 0UL) {
        if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);
            return HAL_ERROR;
        }
        /* A NACK that arrives while payload is still pending means the master
           ended the read earlier than this frame promised: that is a real failure,
           not a frame boundary (a frame-boundary NACK arrives only after every
           byte this frame had to give was taken). */
        if (LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) != 0UL) {
            LL_I2C_ClearFlag_NACKI(hi2c->Instance);
            hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_ERROR;
        }

        if (LL_I2C_IsTxFIFOFull(hi2c->Instance) == 0UL) {
            LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
            hi2c->XferCount--;
        }

        if ((HAL_GetTick() - tickstart) >= Timeout) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_TIMEOUT;
        }
    }

    /* Wait for the end of this frame. Two endings are legal and neither implies
       the other, so both must be accepted here:
         - NACK: the master took every byte it wanted and refused the next one,
           yet still owns the bus (an intermediate frame of a sequential transfer
           keeps it open and sends no STOP). Completing on NACK is what makes a
           multi-frame transaction possible; waiting for STOP alone would hold the
           caller until the timeout and dead-lock the sequence.
         - STOP: the master closed the transaction. */
    while ((LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) == 0UL) &&
           (LL_I2C_IsActiveFlag_SPETI(hi2c->Instance) == 0UL)) {
        if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);
            return HAL_ERROR;
        }
        if ((HAL_GetTick() - tickstart) >= Timeout) {
            hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
            I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

            return HAL_TIMEOUT;
        }
    }

    if (LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) != 0UL) {
        LL_I2C_ClearFlag_NACKI(hi2c->Instance);
    } else {
        LL_I2C_ClearFlag_SPETI(hi2c->Instance);
    }

    I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);


    return HAL_OK;
}

/**
  * @brief  Receive in slave mode an amount of data in blocking mode.
  * @param[in,out]  hi2c     Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[out]  pData    Pointer to data buffer (uint8_t*).
  * @param[in]  Size     Amount of data to be received (bytes).
  * @param[in]  Timeout  Timeout duration in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Receive success.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @note   Blocking call from the slave perspective; master must clock the SCL.
  *         It returns as soon as Size bytes have been read: a slave receiver gets no
  *         NACK and, for an intermediate frame of a sequential transfer, no STOP, so
  *         the byte count - not STOP - is what delimits the frame. An IT/DMA master on
  *         the same core keeps running through its ISR while this call waits, so that
  *         combination is allowed; what must not happen is work that this same frame
  *         still depends on running after the call returns.
  *         Timeout must be a finite value; HAL_MAX_DELAY is rejected.
  * @ref    HAL_I2C_Slave_Transmit HAL_I2C_SlaveRxCpltCallback
  */
HAL_StatusTypeDef HAL_I2C_Slave_Receive(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                        uint16_t Size, uint32_t Timeout)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if ((pData == NULL) || (Size == 0UL) || (Timeout == HAL_MAX_DELAY)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_RX, {
        return HAL_BUSY;
    });

    hi2c->Mode = HAL_I2C_MODE_SLAVE;
    LL_I2C_AcknowledgeNextData(hi2c->Instance, LL_I2C_ACK);
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /* Set slave role */

    /* Wait for data in RX FIFO */
    uint32_t tickstart = HAL_GetTick();
    for (uint32_t i = 0UL; i < Size; i++) {
        while (LL_I2C_IsRxFIFOEmpty(hi2c->Instance) != 0UL) {
            if (I2C_IsErrorOccurred(hi2c) != HAL_OK) {
                I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);
                return HAL_ERROR;
            }
            if (HAL_GetTick() - tickstart >= Timeout) {
                hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
                I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);

                return HAL_TIMEOUT;
            }
        }
        pData[i] = LL_I2C_ReceiveData8(hi2c->Instance);
    }

    I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);


    return HAL_OK;
}


/**
  * @brief  Check if target device is ready for communication.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  DevAddress  Target device address (7-bit or 10-bit).
  * @param[in]  Trials      Number of trials to attempt.
  * @param[in]  Timeout     Per-trial timeout in milliseconds.
  * @return HAL status
  * @retval HAL_OK       Target device acknowledged (ready).
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     Peripheral is busy.
  * @retval HAL_TIMEOUT  All trials exhausted without ACK.
  * @note   Blocking call; used to probe a bus/device before a real transfer.
  * @ref    HAL_I2C_Master_Transmit HAL_I2C_Master_Receive
  */
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                        uint32_t Trials, uint32_t Timeout)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t trial;
    uint32_t tickstart;

    /* Check NULL pointers */
    if (hi2c == NULL) {
        return HAL_INVALID;
    }

    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress));
    ASSERT_FUNC_PARAM(Trials != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if (!IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress)) {
            return HAL_INVALID;
        }

        if (Trials == 0U) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Try to get ACK from target device */
    for (trial = 0UL; trial < Trials; trial++) {
        /* Wait until the bus is free */
        status = I2C_WaitOnBusBusyUntilTimeout(hi2c, Timeout);
        if (status != HAL_OK) {
            break;
        }

        /* Clear stale flags from a previous trial */
        LL_I2C_ClearFlag_MTXAI(hi2c->Instance);
        LL_I2C_ClearFlag_NACKI(hi2c->Instance);

        /* Configure a 1-byte TX transfer to check ACK (I2CCNT must be >= 1) */
        LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)DevAddress);
        LL_I2C_HandleTransfer(hi2c->Instance, LL_I2C_DIRECTION_TRANSMIT, 1UL, 1UL);
        /* Preload dummy byte into TX FIFO before RLSCMD */
        LL_I2C_TransmitData8(hi2c->Instance, 0x00U);
        LL_I2C_ReleaseCommand(hi2c->Instance);

        /* Wait for TX address done or NACK */
        tickstart = HAL_GetTick();
        while (LL_I2C_IsActiveFlag_MTXAI(hi2c->Instance) == 0UL) {
            /* Check for NACK */
            if (LL_I2C_IsActiveFlag_NACKI(hi2c->Instance) != 0UL) {
                LL_I2C_ClearFlag_NACKI(hi2c->Instance);
                LL_I2C_GenerateStopCondition(hi2c->Instance);
                LL_I2C_ReleaseCommand(hi2c->Instance);
                status = HAL_ERROR;
                break;
            }

            /* Check for timeout */
            if (HAL_GetTick() - tickstart >= Timeout) {
                /* Release the bus */
                LL_I2C_GenerateStopCondition(hi2c->Instance);
                LL_I2C_ReleaseCommand(hi2c->Instance);
                status = HAL_TIMEOUT;
                break;
            }
        }

        if (status == HAL_OK) {
            /* Wait for the byte and the AUTOEND STOP to complete */
            while (LL_I2C_IsActiveFlag_MDEI(hi2c->Instance) == 0UL) {
                if ((HAL_GetTick() - tickstart) >= Timeout) {
                    status = HAL_TIMEOUT;
                    break;
                }
            }
            LL_I2C_ClearFlag_MDEI(hi2c->Instance);
            LL_I2C_ClearFlag_MTXAI(hi2c->Instance);
            if (status == HAL_OK) {
                break;
            }
        }
    }

    I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);


    return status;
}

/* Non-Blocking mode: Interrupt */

/**
  * @brief  Transmit in master mode in interrupt mode.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  DevAddress  Target device address (7-bit or 10-bit).
  * @param[in]  pData       Pointer to data buffer (uint8_t*).
  * @param[in]  Size        Amount of data to be sent (bytes).
  * @return HAL status
  * @retval HAL_OK       Transfer started; result delivered via MasterTxCpltCallback.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking; callback HAL_I2C_MasterTxCpltCallback is invoked on
  *         completion. HAL_I2C_Init() and NVIC configuration required.
  * @ref    HAL_I2C_Master_Transmit HAL_I2C_Master_Transmit_DMA HAL_I2C_MasterTxCpltCallback
  */

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                             uint8_t *pData, uint16_t Size)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if (!IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress)) {
            return HAL_INVALID;
        }

        if ((pData == NULL) || (Size == 0UL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_TX, {
        return HAL_BUSY;
    });

    hi2c->Mode       = HAL_I2C_MODE_MASTER;
    hi2c->XferISR      = I2C_Master_ISR_IT;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr   = pData;
    hi2c->XferSize   = (Size > I2C_MAX_DATA_COUNT_PER_TRANS)
                       ? I2C_MAX_DATA_COUNT_PER_TRANS : Size;
    hi2c->XferCount  = Size;
    hi2c->XferOptions = HAL_I2C_FIRST_AND_LAST_FRAME;
    hi2c->Devaddress = DevAddress;

    /* Set target address. */
    LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)DevAddress);

    /* Configure the first chunk (START + DIR + COUNT + AUTOEND). */
    LL_I2C_HandleTransfer(hi2c->Instance, LL_I2C_DIRECTION_TRANSMIT,
                          hi2c->XferSize,
                          (hi2c->XferSize == Size) ? 1UL : 0UL);

    /* Preload first data byte into TX FIFO. */
    LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
    hi2c->XferCount--;
    hi2c->XferSize--;

    /* Trigger the transfer. */
    LL_I2C_ReleaseCommand(hi2c->Instance);

    /* Clear stale master TX address-done flag. */
    LL_I2C_ClearFlag_MTXAI(hi2c->Instance);

    /* Enable interrupts: TX address done, master done, error */
    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_MTXAIE | LL_I2C_IT_MDEIE |
                    LL_I2C_IT_TXEIE | LL_I2C_IT_ERR_MASK);


    return HAL_OK;
}

/**
  * @brief  Receive in master mode in interrupt mode.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  DevAddress  Target device address (7-bit or 10-bit).
  * @param[out]  pData       Pointer to data buffer (uint8_t*).
  * @param[in]  Size        Amount of data to be received (bytes).
  * @return HAL status
  * @retval HAL_OK       Transfer started; result delivered via MasterRxCpltCallback.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking; callback HAL_I2C_MasterRxCpltCallback is invoked on
  *         completion. HAL_I2C_Init() and NVIC configuration required.
  * @ref    HAL_I2C_Master_Receive HAL_I2C_Master_Receive_DMA HAL_I2C_MasterRxCpltCallback
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                            uint8_t *pData, uint16_t Size)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if (!IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress)) {
            return HAL_INVALID;
        }

        if ((pData == NULL) || (Size == 0UL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_RX, {
        return HAL_BUSY;
    });


    hi2c->Mode       = HAL_I2C_MODE_MASTER;
    hi2c->XferISR      = I2C_Master_ISR_IT;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr   = pData;
    hi2c->XferSize   = (Size > I2C_MAX_DATA_COUNT_PER_TRANS)
                       ? I2C_MAX_DATA_COUNT_PER_TRANS : Size;
    hi2c->XferCount  = Size;
    hi2c->XferOptions = HAL_I2C_FIRST_AND_LAST_FRAME;
    hi2c->Devaddress = DevAddress;

    /* Configure the first chunk (START + DIR + COUNT + AUTOEND). */
    LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)DevAddress);
    LL_I2C_HandleTransfer(hi2c->Instance, LL_I2C_DIRECTION_RECEIVE,
                          hi2c->XferSize,
                          (hi2c->XferSize == Size) ? 1UL : 0UL);
    LL_I2C_ReleaseCommand(hi2c->Instance);

    /* Enable interrupts: RX FIFO full, master done, error */
    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_RXFIE | LL_I2C_IT_MDEIE |
                    LL_I2C_IT_ERR_MASK);


    return HAL_OK;
}

/**
  * @brief  Transmit in slave mode in interrupt mode.
  * @param[in,out]  hi2c   Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  pData  Pointer to data buffer (uint8_t*).
  * @param[in]  Size   Amount of data to be sent (bytes).
  * @return HAL status
  * @retval HAL_OK       Transfer started; result delivered via SlaveTxCpltCallback.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking; callback HAL_I2C_SlaveTxCpltCallback is invoked on
  *         completion. HAL_I2C_Init() and NVIC configuration required.
  * @ref    HAL_I2C_Slave_Transmit HAL_I2C_Slave_Transmit_DMA HAL_I2C_SlaveTxCpltCallback
  */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                            uint16_t Size)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if ((pData == NULL) || (Size == 0UL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_TX, {
        return HAL_BUSY;
    });

    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    LL_I2C_AcknowledgeNextData(hi2c->Instance, LL_I2C_ACK);
    hi2c->XferISR      = I2C_Slave_ISR_IT;
    hi2c->ErrorCode  = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr  = pData;
    hi2c->XferSize  = Size;
    hi2c->XferCount = Size;
    /* No address match yet: a STOP is only accepted as end-of-transfer once this
       slave was really addressed (see I2C_Slave_ISR_IT Detect-Stop branch). */
    hi2c->AddrEventCount = 0U;
    hi2c->XferOptions = HAL_I2C_FIRST_AND_LAST_FRAME;

    /* Set slave role */

  

   
    /* Flush any residual TX data left by a previous transfer so the master
       never reads stale bytes. */
    I2C_FlushTxFIFO(hi2c);

    /* Clear pending interrupt flags from a previous transfer. */
    LL_I2C_ClearAllIntrFlags(hi2c->Instance);

    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_SWTXIE | LL_I2C_IT_TXADIE |
                    LL_I2C_IT_STDETIE  | LL_I2C_IT_SPDETIE| LL_I2C_IT_ERR_MASK);


    return HAL_OK;
}

/**
  * @brief  Receive in slave mode in interrupt mode.
  * @param[in,out]  hi2c   Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[out]  pData  Pointer to data buffer (uint8_t*); may be NULL when Size is 0.
  * @param[in]  Size   Amount of data to be received (bytes). Size 0 arms the slave
  *                    to acknowledge its address and wait for the master STOP only;
  *                    bytes received in that case are discarded.
  * @return HAL status
  * @retval HAL_OK       Transfer started; result delivered via SlaveRxCpltCallback.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   Non-blocking; callback HAL_I2C_SlaveRxCpltCallback is invoked on
  *         completion. HAL_I2C_Init() and NVIC configuration required.
  *         Size 0 is accepted by this interrupt variant only, to answer a command
  *         without data phase (SMBus Quick Command); HAL_I2C_Slave_Receive() and
  *         HAL_I2C_Slave_Receive_DMA() require a non-zero Size.
  * @ref    HAL_I2C_Slave_Receive HAL_I2C_Slave_Receive_DMA HAL_I2C_SlaveRxCpltCallback
  */
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                           uint16_t Size)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM((pData != NULL) || (Size == 0U));

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if ((pData == NULL) && (Size > 0U)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hi2c->State, HAL_I2C_STATE_READY);
    HAL_I2C_PARAM_UPDATE(hi2c->State, HAL_I2C_STATE_READY, HAL_I2C_STATE_BUSY_RX, {
        return HAL_BUSY;
    });

    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    LL_I2C_AcknowledgeNextData(hi2c->Instance, LL_I2C_ACK);
    hi2c->XferISR      = I2C_Slave_ISR_IT;
    hi2c->ErrorCode  = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr  = pData;
    hi2c->XferSize  = Size;
    hi2c->XferCount = Size;
    /* No address match yet: a STOP is only accepted as end-of-transfer once this
       slave was really addressed (see I2C_Slave_ISR_IT Detect-Stop branch). */
    hi2c->AddrEventCount = 0U;
    hi2c->XferOptions = HAL_I2C_FIRST_AND_LAST_FRAME;

    /* Set slave role */

    /* Clear pending interrupt flags from a previous transfer. */
    LL_I2C_ClearAllIntrFlags(hi2c->Instance);

    /* Enable RX FIFO, address match, and Start/Stop detection interrupts for slave RX */
    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_RXFIE  | LL_I2C_IT_RXADIE |
                    LL_I2C_IT_RXGCIE | LL_I2C_IT_STDETIE  | LL_I2C_IT_SPDETIE  |
                    LL_I2C_IT_ERR_MASK);

    return HAL_OK;
}


/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group4 IRQ Handler and Callbacks
  * @{
  */


/**
  * @brief  Master interrupt-mode dispatcher.
  * @param[in,out]  hi2c   Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  ITFlags    Pending interrupt flags.
  * @param[in]  ITSources  Enabled interrupt sources.
  * @return HAL status
  */
static HAL_StatusTypeDef I2C_Master_ISR_IT(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags,
                                        uint32_t ITSources)
{
    /* Interrupt-mode entry: every phase is served by the CPU. */
    return I2C_Master_ISR_Core(hi2c, 0UL, ITFlags, ITSources);
}


/**
  * @brief  Shared master interrupt dispatcher used by both master entries.
  * @param[in,out]  hi2c   Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  use_dma   1 when the running transfer hands its data phase over to DMA,
  *                      0 when every phase is served by the CPU.
  * @param[in]  ITFlags    Pending interrupt flags.
  * @param[in]  ITSources  Enabled interrupt sources.
  * @return HAL status
  */
static HAL_StatusTypeDef I2C_Master_ISR_Core(HAL_I2C_HandleTypeDef *hi2c, uint32_t use_dma,
                                             uint32_t ITFlags, uint32_t ITSources)
{
    /* One priority-ordered if/else-if chain: only the pending source with the
       highest priority is handled per entry and the NVIC re-enters while other
       flags are still pending. The data-feeding branches come before the
       completion branch: I2C_ITMasterSeqCplt() disables the event interrupts and
       resets the handle state, so any FIFO work must be finished first. */

    /* === Check if master TX address done interrupt === */
    if (((ITSources & LL_I2C_IT_MTXAIE) != 0UL) &&
        ((ITFlags   & LL_I2C_FLAG_MTXAI)  != 0UL)) {
        I2C_ITMasterTxAddrDone(hi2c);
    }

    /* === Check if TX FIFO empty interrupt === */
    else if (((ITSources & LL_I2C_IT_TXEIE) != 0UL) &&
             (LL_I2C_IsTxFIFOEmpty(hi2c->Instance) != 0UL)) {
        /* Load more TX data in interrupt mode */
        while ((LL_I2C_IsTxFIFOFull(hi2c->Instance) == 0UL) &&
               (hi2c->XferCount > 0UL) && (hi2c->XferSize > 0UL)) {
            LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
            hi2c->XferCount--;
            hi2c->XferSize--;
        }

        if ((hi2c->XferCount == 0UL) || (hi2c->XferSize == 0UL)) {
            LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_TXEIE);
        }
    }

    /* === Check if RX FIFO threshold interrupt === */
    /* RXFIE triggers when FIFO reaches threshold (default 1 byte), not when physically full.
       Using IsRxFIFOFull() (STATUS.RFF) would miss data when count < FIFO depth. */
    else if (((ITSources & LL_I2C_IT_RXFIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_RXFI)   != 0UL)) {
        while ((LL_I2C_IsRxFIFOEmpty(hi2c->Instance) == 0UL) &&
               (hi2c->XferCount > 0UL) && (hi2c->XferSize > 0UL)) {
            *hi2c->pBuffPtr++ = LL_I2C_ReceiveData8(hi2c->Instance);
            hi2c->XferCount--;
            hi2c->XferSize--;
        }
    }

    /* === Check if master TX/RX done interrupt === */
    else if (((ITSources & LL_I2C_IT_MDEIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_MDEI)  != 0UL)) {
        I2C_ITMasterSeqCplt(hi2c, use_dma);
    }

    return HAL_OK;
}

static HAL_StatusTypeDef I2C_Slave_ISR_IT(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags,
                                       uint32_t ITSources)
{
    /* One priority-ordered if/else-if chain: only the pending source with the
       highest priority is handled per entry and the NVIC re-enters while other
       flags are still pending. The STOP completion runs first and drains the RX
       FIFO before completing, then follow the address / data / status sources. */

    /* === Check if Detect Stop interrupt === */
    if (((ITSources & LL_I2C_IT_SPDETIE) != 0UL) &&
        ((ITFlags   & LL_I2C_FLAG_SPETI)  != 0UL)) {
        LL_I2C_ClearFlag_SPETI(hi2c->Instance);

        /* STOP detected means the master finished the transfer. I2C_EndXfer()
           performs the full teardown (it disables both the event and the error
           sources), so no explicit masking is needed here. A slave transfer is
           one-shot: it always returns to READY and never stays addressable.

           Guard: a STOP can also be latched when the bus merely goes idle without
           this slave ever being addressed for the armed transfer (the tail of a
           previous transfer, or a re-arm right after an error). Completing then
           fires the callback with the RX FIFO still empty, tears the transfer down
           (State/Mode/XferISR reset + INTREN disabled) and leaves the bytes that
           arrive afterwards stranded in the FIFO. Only accept the STOP once this
           slave was really addressed (RXADI/TXADI seen since arming, tracked in
           AddrEventCount) or some data has already been moved. */
        if ((hi2c->AddrEventCount == 0UL) && (hi2c->XferCount == hi2c->XferSize)) {
            /* Spurious / not-yet-started STOP: stay armed and keep listening. */
        }
        else if (hi2c->State == HAL_I2C_STATE_BUSY_TX) {
            I2C_EndXfer(hi2c, I2C_DMA_TX_HANDLE(hi2c), I2C_DMA_RX_HANDLE(hi2c), HAL_I2C_STATE_READY);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
            hi2c->SlaveTxCpltCallback(hi2c);
#else
            HAL_I2C_SlaveTxCpltCallback(hi2c);
#endif
        }
        else if (hi2c->State == HAL_I2C_STATE_BUSY_RX) {
            /* Abort the DMA side BEFORE touching the RX FIFO: on the DMA slave path
               the channel and the CPU must never read the same byte (the DMA must be
               aborted before reading the FIFO tail). EndXfer
               also sets the terminal state in a single shot. */
            I2C_EndXfer(hi2c, I2C_DMA_TX_HANDLE(hi2c), I2C_DMA_RX_HANDLE(hi2c), HAL_I2C_STATE_READY);
            /* Move the tail still sitting in the RX FIFO into the buffer, so the end
               of the write is not lost. */
            I2C_SlaveReadRxFIFO(hi2c);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
            hi2c->SlaveRxCpltCallback(hi2c);
#else
            HAL_I2C_SlaveRxCpltCallback(hi2c);
#endif
        }
    }

    /* === Check if Slave RX Address Done (slave addressed for RX by master write) === */
    else if (((ITSources & LL_I2C_IT_RXADIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_RXADI)  != 0UL)) {
        LL_I2C_ClearFlag_RXADI(hi2c->Instance);
        /* Record that this slave was addressed: the Detect-Stop branch only accepts
           a STOP as end-of-transfer after a real address match (see there). */
        hi2c->AddrEventCount++;

        /* Notify user via address match callback */
        uint32_t rxAddr = LL_I2C_GetAddressMatchCode(hi2c->Instance);
        uint8_t transferDir = 0x00U; /* 0=Write (master writes, slave receives) */
        uint16_t addrMatchCode = (uint16_t)(rxAddr & 0x3FFUL);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        if (hi2c->AddrCallback != NULL) {
            hi2c->AddrCallback(hi2c, transferDir, addrMatchCode);
        }
#else
        HAL_I2C_AddrCallback(hi2c, transferDir, addrMatchCode);
#endif
    }

    /* === Check if Slave TX Address Done (slave addressed for TX by master read) === */
    else if (((ITSources & LL_I2C_IT_TXADIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_TXADI)  != 0UL)) {
        /* Fill the TX FIFO before clearing TXADI to release SCL. */
        if (hi2c->State == HAL_I2C_STATE_BUSY_TX) {
            while ((hi2c->XferCount > 0UL) &&
                   (LL_I2C_IsTxFIFOFull(hi2c->Instance) == 0UL)) {
                LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
                hi2c->XferCount--;
            }

            /* Transfer is now running: let TX-empty keep the FIFO filled. */
            if (hi2c->XferCount > 0UL) {
                LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_TXEIE);
            }

            if ((ITFlags & LL_I2C_FLAG_SWTXI) != 0UL) {
                LL_I2C_ClearFlag(hi2c->Instance, LL_I2C_FLAG_SWTXI);
            }
        }

        /* Release the address-match clock stretch only NOW, after the payload is
           queued in the TX FIFO, so the master always reads real data. */
        LL_I2C_ClearFlag_TXADI(hi2c->Instance);
        /* Record that this slave was addressed: the Detect-Stop branch only accepts
           a STOP as end-of-transfer after a real address match (see there). */
        hi2c->AddrEventCount++;

        /* Notify user via address match callback */
        uint32_t rxAddr = LL_I2C_GetAddressMatchCode(hi2c->Instance);
        uint8_t transferDir = 0x01U; /* 1=Read (master reads, slave transmits) */
        uint16_t addrMatchCode = (uint16_t)(rxAddr & 0x3FFUL);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        if (hi2c->AddrCallback != NULL) {
            hi2c->AddrCallback(hi2c, transferDir, addrMatchCode);
        }
#else
        HAL_I2C_AddrCallback(hi2c, transferDir, addrMatchCode);
#endif
    }

    /* === Check if RX FIFO threshold interrupt === */
    /* RXFIE triggers when FIFO reaches threshold (default 1 byte), not when physically full.
       Using IsRxFIFOFull() (STATUS.RFF) would miss data when count < FIFO depth. */
    else if (((ITSources & LL_I2C_IT_RXFIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_RXFI)   != 0UL)) {
        /* Only move received bytes into the application buffer. Completion (terminal
           state + callback) is signalled by the Detect-Stop event, so RX and TX
           share ONE completion path and their terminal states can no longer drift apart. */
        I2C_SlaveReadRxFIFO(hi2c);

    }

    /* === Check if TX FIFO empty interrupt === */
    else if (((ITSources & LL_I2C_IT_TXEIE) != 0UL) &&
             (LL_I2C_IsTxFIFOEmpty(hi2c->Instance) != 0UL)) {
        /* Fill the TX FIFO up completely.
           In slave TX the peripheral holds SCL low (stretch) until the FIFO is
           filled, so feeding a single byte leaves the clock stretched forever and
           the master times out (BTOI) - the stale TXEI then never fires again. */
        while ((hi2c->XferCount > 0UL) &&
               (LL_I2C_IsTxFIFOFull(hi2c->Instance) == 0UL)) {
            LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
            hi2c->XferCount--;
        }

        if (hi2c->XferCount == 0UL) {
            /* Nothing left to queue: stop the TX-empty source once the FIFO drains. */
            if (LL_I2C_IsTxFIFOEmpty(hi2c->Instance) != 0UL) {
                LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_TXEIE);
            }
        }
    }

    /* === Check if Slave Wait TX Data interrupt === */
    else if (((ITSources & LL_I2C_IT_SWTXIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_SWTXI)  != 0UL)) {
        if (hi2c->State == HAL_I2C_STATE_BUSY_TX) {
            while ((hi2c->XferCount > 0UL) &&
                   (LL_I2C_IsTxFIFOFull(hi2c->Instance) == 0UL)) {
                LL_I2C_TransmitData8(hi2c->Instance, *hi2c->pBuffPtr++);
                hi2c->XferCount--;
            }

            if (hi2c->XferCount == 0UL) {
                LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_SWTXIE);
            }
        }

        LL_I2C_ClearFlag(hi2c->Instance, LL_I2C_FLAG_SWTXI);
    }

    /* === Check if Detect Start interrupt === */
    else if (((ITSources & LL_I2C_IT_STDETIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_STDETI)  != 0UL)) {
        LL_I2C_ClearFlag_STDETI(hi2c->Instance);
        hi2c->EventCount++;
    }

    /* === Check if Slave RX General Call interrupt === */
    else if (((ITSources & LL_I2C_IT_RXGCIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_RXGCI)  != 0UL)) {
        LL_I2C_ClearFlag_RXGCI(hi2c->Instance);
        /* A general call also addresses this slave: count it as "addressed" so the
           Detect-Stop guard accepts the end-of-transfer STOP. */
        hi2c->AddrEventCount++;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        if (hi2c->AddrCallback != NULL) {
            hi2c->AddrCallback(hi2c, 0x00U, 0x0000U);
        }
#else
        HAL_I2C_AddrCallback(hi2c, 0x00U, 0x0000U);
#endif
    }

    return HAL_OK;
}


/**
  * @brief  Handle I2C event interrupt request.
  *         Process all event-type interrupts: master TX address done, master
  *         transfer done, TX FIFO empty, RX FIFO full, slave address match,
  *         start/stop detection, slave wait TX data, and general call.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   Place this handler in the I2C event IRQ vector (e.g. I2C0_IRQHandler).
  *         NULL handle is silently ignored (programming error).
  * @ref    HAL_I2C_ER_IRQHandler HAL_I2C_Init
  */
void HAL_I2C_EV_IRQHandler(HAL_I2C_HandleTypeDef *hi2c)
{
    if (hi2c == NULL) {
        return;
    }

    if (hi2c->XferISR != NULL) {
        /* Read enable + pending flags once, then dispatch via XferISR: the ISR
           body only performs cheap bit tests instead of hitting I2C registers in
           every branch (previously each branch re-read INTREN/INTR). */
        uint32_t itsources = LL_I2C_GetITEnables(hi2c->Instance);
        uint32_t itflags   = LL_I2C_GetITFlags(hi2c->Instance);

        (void)hi2c->XferISR(hi2c, itflags, itsources);
    }
}

/**
  * @brief  Handle I2C error interrupt request.
  *         Process all error-type interrupts: bus error, arbitration lost,
  *         NACK, TX/RX overflow, RX underflow, PEC error, SMBus alert,
  *         master/slave timeout, and bus timeout.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   Place this handler in the I2C error IRQ vector.
  *         On error, HAL_I2C_ErrorCallback() is invoked and the handle
  *         state is set to READY. An SMBus alert reports
  *         HAL_I2C_ERROR_ALERT through the same callback but does not
  *         tear down or reset the ongoing transfer.
  * @ref    HAL_I2C_EV_IRQHandler HAL_I2C_ErrorCallback HAL_I2C_GetError
  */
void HAL_I2C_ER_IRQHandler(HAL_I2C_HandleTypeDef *hi2c)
{
    uint32_t itsources;
    uint32_t itflags;

    if (hi2c == NULL) {
        return;
    }

    /* Read enable + pending flags once: each branch below just tests bits instead
       of re-reading INTREN/INTR per error source. */
    itsources = LL_I2C_GetITEnables(hi2c->Instance);  /* INTREN */
    itflags   = LL_I2C_GetITFlags(hi2c->Instance);    /* INTR  */

    /* Check for Bus Error */
    if (((itsources & LL_I2C_IT_BUSEIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_BUSEI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_BERR;
        LL_I2C_ClearFlag_BUSEI(hi2c->Instance);
    }

    /* Check for Arbitration Lost */
    if (((itsources & LL_I2C_IT_ARBFIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_ARBFI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_ARLO;
        LL_I2C_ClearFlag_ARBFI(hi2c->Instance);
    }

    /* Check for NACK. */
    if (((itsources & LL_I2C_IT_NACKIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_NACKI)  != 0UL)) {
        if (hi2c->XferCount == 0UL) {
            LL_I2C_ClearFlag_NACKI(hi2c->Instance);

            /* Slave TX finished: complete it here, since the master may NACK the
               last byte without generating a STOP.
               Mode MUST be checked as well: BUSY_TX is also used by master TX and by
               Mem_Write, so a State-only test reports SlaveTxCplt on a master handle. */
            if ((hi2c->Mode == HAL_I2C_MODE_SLAVE) &&
                (hi2c->State == HAL_I2C_STATE_BUSY_TX)) {
                hi2c->PreviousState = (uint32_t)hi2c->State;
                /* One-shot slave transfer: it always returns to READY, the SAME rule
                   as the Detect-Stop path. I2C_EndXfer() performs the full
                   teardown. */
                I2C_EndXfer(hi2c, I2C_DMA_TX_HANDLE(hi2c), I2C_DMA_RX_HANDLE(hi2c), HAL_I2C_STATE_READY);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
                hi2c->SlaveTxCpltCallback(hi2c);
#else
                HAL_I2C_SlaveTxCpltCallback(hi2c);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
            }
            else if (hi2c->State == HAL_I2C_STATE_BUSY_TX) {
                /* Master TX / Mem write: the target did not answer, so this is a real
                   failure. Without this branch the handle would stay BUSY_TX forever. */
                LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_EVT_MASK);
                hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
            }
            else if ((hi2c->Mode == HAL_I2C_MODE_SLAVE) &&
                     (hi2c->State == HAL_I2C_STATE_BUSY_RX)) {
                /* Slave RX: the NACK was generated by this slave itself (its address
                   was not matched). The armed transfer is untouched and keeps
                   listening for the STOP, which is the only delimiter this
                   direction has. */
            }
            else {
                /* Master read: the NACK is the one the master generated itself to
                   close the reception, so it is not an error. */
                LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_EVT_MASK);
            }
        }
        else {
            hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
            LL_I2C_ClearFlag_NACKI(hi2c->Instance);
        }
    }

    /* Check for TX Overflow */
    if (((itsources & LL_I2C_IT_TXOFIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_TXOFI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_TXOVR | HAL_I2C_ERROR_OVR;
        LL_I2C_ClearFlag_TXOFI(hi2c->Instance);
    }

    /* Check for RX Overflow */
    if (((itsources & LL_I2C_IT_RXOFIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_RXOFI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_RXOVR | HAL_I2C_ERROR_OVR;
        LL_I2C_ClearFlag_RXOFI(hi2c->Instance);
    }

    /* Check for RX Underflow */
    if (((itsources & LL_I2C_IT_RXUFIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_RXUFI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_RXUNF | HAL_I2C_ERROR_OVR;
        LL_I2C_ClearFlag_RXUFI(hi2c->Instance);
    }

    /* Check for TX Underflow (slave TX FIFO underrun) */
    if (((itsources & LL_I2C_IT_TXUFIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_TXUFI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_TXUNF | HAL_I2C_ERROR_OVR;
        LL_I2C_ClearFlag(hi2c->Instance, LL_I2C_FLAG_TXUFI);
    }

    /* Check for PEC Error (SMBus) */
    if (((itsources & LL_I2C_IT_PECRXIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_PECRXI)  != 0UL)) {
        hi2c->ErrorCode |=HAL_I2C_ERROR_PECERR;
        LL_I2C_ClearFlag_PECRXI(hi2c->Instance);
    }

    /* Check for Master Tmext Timeout */
    if (((itsources & LL_I2C_IT_MEXTOIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_MEXTOI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
        LL_I2C_ClearFlag_MEXTOI(hi2c->Instance);
    }

    /* Check for Slave Tsext Timeout */
    if (((itsources & LL_I2C_IT_SEXTOIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_SEXTOI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
        LL_I2C_ClearFlag_SEXTOI(hi2c->Instance);
    }

    /* Check for Bus Timeout */
    if (((itsources & LL_I2C_IT_BTOIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_BTOI)  != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_BUSTIMEOUT;
        LL_I2C_ClearFlag_BTOI(hi2c->Instance);
    }

    /* Check for SMBus Alert (routed through the error interrupt) */
    if (((itsources & LL_I2C_IT_ALDETIE) != 0UL) &&
        ((itflags   & LL_I2C_FLAG_ALDETI) != 0UL)) {
        hi2c->ErrorCode |= HAL_I2C_ERROR_ALERT;
        LL_I2C_ClearFlag_ALDETI(hi2c->Instance);
    }

    /* If an error occurred, call error callback */
    if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE) {
        /* Snapshot the reception state before teardown: the RX FIFO tail is only
           recovered for a receive, and I2C_EndXfer() resets State to READY. */
        uint32_t was_busy_rx = (hi2c->State == HAL_I2C_STATE_BUSY_RX) ? 1UL : 0UL;

        /* Snapshot the master/mem mode before I2C_EndXfer() resets it: the
           post-STOP wait below only applies when the abort came from a
           master/mem transfer (where GenerateStop()+ReleaseCommand() commits a
           CTRL command into the master's command register that must drain
           before the next transfer is issued). */
        uint32_t was_master  = ((hi2c->Mode == HAL_I2C_MODE_MASTER) ||
                                (hi2c->Mode == HAL_I2C_MODE_MEM)) ? 1UL : 0UL;

        /* SMBus Alert is reported through ErrorCallback, but it must not
           abort/tear down an ongoing transfer. */
        if ((hi2c->ErrorCode & HAL_I2C_ERROR_ALERT) == 0UL) {
            /* Disable all interrupts */
            LL_I2C_DisableIT(hi2c->Instance, LL_I2C_IT_ERR_MASK | LL_I2C_IT_EVT_MASK);

            /* Generate STOP */
            LL_I2C_GenerateStopCondition(hi2c->Instance);
           

            /* Bounded wait for the master to truly return to idle. GenerateStop()
               is a read-modify-write on CTRL: on a NACK/master-abort path the
               hardware has already decremented CTRL.I2CCNT during the address
               phase, so the command we just committed may carry a smaller I2CCNT
               than the application intended. RLSCMD stays asserted until that
               stale command drains; the next HAL_I2C_Master_Transmit_IT() then
               calls ReleaseCommand() while RLSCMD is still set (SET_BIT is a
               no-op), so the master ends up executing the stale, short-by-one
               command on the bus (observed on the logic analyzer: 7 data bytes
               instead of 8 after an address-phase NACK). A pure loop-counter bound
               keeps this ISR-safe regardless of the SysTick priority vs. the I2C
               IRQ. */
            if (was_master != 0UL) {
                uint32_t wait_guard = 0x10000UL;
                while ((LL_I2C_IsActiveFlag_BUSY(hi2c->Instance) != 0UL) ||
                       (LL_I2C_IsTransferInProgress(hi2c->Instance) != 0UL)) {
                    if (wait_guard == 0UL) {
                        break;
                    }
                    wait_guard--;
                }
            }

            /* Reset the handle and stop the DMA side before invoking the callback,
               so a new transfer started from within the callback is not clobbered.
               The DMA is aborted BEFORE the FIFO is read: on the DMA path the
               channel and the CPU must never read the same byte. */
            I2C_EndXfer(hi2c, I2C_DMA_TX_HANDLE(hi2c), I2C_DMA_RX_HANDLE(hi2c), HAL_I2C_STATE_READY);

            /* Keep whatever the master already pushed into the RX FIFO so the
               application can still see it. */
            if (was_busy_rx != 0UL) {
                I2C_SlaveReadRxFIFO(hi2c);
            }
        }

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->ErrorCallback(hi2c);
#else
        HAL_I2C_ErrorCallback(hi2c);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
    }
}

/**
  * @brief  Handle I2C interrupt request (single combined IRQ entry).
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   Event and error sources share the same interrupt vector; the error
  *         handler runs only when an error flag is pending.
  * @ref    HAL_I2C_EV_IRQHandler HAL_I2C_ER_IRQHandler
  */
void HAL_I2C_IRQHandler(HAL_I2C_HandleTypeDef *hi2c)
{
    uint32_t itsources;
    uint32_t itflags;
    uint32_t pending;

    if (hi2c == NULL) {
        return;
    }

    itsources = LL_I2C_GetITEnables(hi2c->Instance);
    itflags   = LL_I2C_GetITFlags(hi2c->Instance);
    pending   = itflags & itsources;

    /* Dispatch EVENTS FIRST, then errors - never let an error flag starve the
       event handler.
       On this device the slave TX payload is loaded from the EVENT handlers
       (TXADI / SWTXI / TXE). NACKI is part of LL_I2C_IT_ERR_MASK, so with the
       old "if error then ER(); return;" order a slave that was read while its
       TX FIFO was still empty would NACK, and every following interrupt took the
       error branch and returned: the event handlers never ran, the FIFO stayed
       empty and the master kept NACKing -> the transfer dead-locked with the
       symptom "only ER runs, EV never runs, data stuck in the FIFO".
       Running the event handler first lets the payload be loaded before the
       error is evaluated, and only then are errors handled. */
    if ((pending & LL_I2C_IT_EVT_MASK) != 0UL) {
        HAL_I2C_EV_IRQHandler(hi2c);
    }

    /* Re-read after the event handler: it may have cleared flags or changed state. */
    itsources = LL_I2C_GetITEnables(hi2c->Instance);
    itflags   = LL_I2C_GetITFlags(hi2c->Instance);
    pending   = itflags & itsources;

    if ((pending & LL_I2C_IT_ERR_MASK) != 0UL) {
        HAL_I2C_ER_IRQHandler(hi2c);
    }
}

/**
  * @brief  Master Tx Transfer completed callback.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   User-overridable weak callback; invoked by IT/DMA on master
  *         transmit completion.
  * @ref    HAL_I2C_Master_Transmit_IT HAL_I2C_Master_Transmit_DMA
  */
__WEAK void HAL_I2C_MasterTxCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_MasterTxCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Master Rx Transfer completed callback.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   User-overridable weak callback; invoked by IT/DMA on master
  *         receive completion.
  * @ref    HAL_I2C_Master_Receive_IT HAL_I2C_Master_Receive_DMA
  */
__WEAK void HAL_I2C_MasterRxCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_MasterRxCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Slave Tx Transfer completed callback.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   User-overridable weak callback; invoked by IT/DMA on slave
  *         transmit completion.

  * @ref    HAL_I2C_Slave_Transmit_IT HAL_I2C_Slave_Transmit_DMA
  */
__WEAK void HAL_I2C_SlaveTxCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_SlaveTxCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Slave Rx Transfer completed callback.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   User-overridable weak callback; invoked by IT/DMA on slave
  *         receive completion.

  * @ref    HAL_I2C_Slave_Receive_IT HAL_I2C_Slave_Receive_DMA
  */
__WEAK void HAL_I2C_SlaveRxCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_SlaveRxCpltCallback could be implemented in the user file
     */
}


__WEAK void HAL_I2C_ListenCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    HAL_UNUSED(hi2c);
}

__WEAK void HAL_I2C_MemTxCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    HAL_UNUSED(hi2c);
}

__WEAK void HAL_I2C_MemRxCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    HAL_UNUSED(hi2c);
}

__WEAK void HAL_I2C_AbortCpltCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    HAL_UNUSED(hi2c);
}


/**
  * @brief  I2C error callback.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return None
  * @note   User-overridable weak callback; invoked on bus error, NACK,
  *         arbitration lost, overrun, or PEC error. Use HAL_I2C_GetError()
  *         to inspect the specific cause.
  *         This callback runs in interrupt context (called from
  *         HAL_I2C_ER_IRQHandler). Keep the body short and non-blocking: do not
  *         call blocking HAL functions or do heavy processing here. In bare-metal
  *         code, only set a flag for the main loop; under an RTOS, release a
  *         semaphore / set a thread flag so the real work runs in a task.
  * @ref    HAL_I2C_GetError HAL_I2C_EV_IRQHandler HAL_I2C_ER_IRQHandler
  */
__WEAK void HAL_I2C_ErrorCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_ErrorCallback could be implemented in the user file
     */
}


/**
  * @brief  I2C slave address match callback.
  * @param[in,out]  hi2c               Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  TransferDirection  Master request transfer direction
  *                            (0 = WRITE, 1 = READ).
  * @param[in]  AddrMatchCode      Address match code (10-bit mode: high byte 0x11110).
  * @return None
  * @note   User-overridable weak callback; invoked when the slave matches
  *         its address. Override to provide custom matching/handling.

  * @ref    HAL_I2C_RegisterAddrCallback
  */
__WEAK void HAL_I2C_AddrCallback(HAL_I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hi2c);
    HAL_UNUSED(TransferDirection);
    HAL_UNUSED(AddrMatchCode);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_I2C_AddrCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group6 Callback Registration
  * @{
  */

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)

/**
  * @brief  Register a User I2C Callback.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  CallbackID  ID of the callback to register, value of @ref HAL_I2C_CallbackIDTypeDef.
  * @param[in]  pCallback   Pointer to the callback function.
  * @return HAL status
  * @retval HAL_OK       Callback registered.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     A transfer is ongoing; cannot register now.
  * @note   Available only when USE_HAL_I2C_REGISTER_CALLBACKS = 1. Replaces
  *         the corresponding weak default callback.
  * @ref    HAL_I2C_UnRegisterCallback
  */
HAL_StatusTypeDef HAL_I2C_RegisterCallback(HAL_I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID,
                                            HAL_I2C_CallbackTypeDef pCallback)
{
    HAL_StatusTypeDef status = HAL_OK;

    if ((hi2c == NULL) || (pCallback == NULL)) {
        return HAL_INVALID;
    }


    if (hi2c->State == HAL_I2C_STATE_READY) {
        switch (CallbackID) {
            case HAL_I2C_MASTER_TX_COMPLETE_CB_ID:
                hi2c->MasterTxCpltCallback = pCallback;
                break;

            case HAL_I2C_MASTER_RX_COMPLETE_CB_ID:
                hi2c->MasterRxCpltCallback = pCallback;
                break;

            case HAL_I2C_SLAVE_TX_COMPLETE_CB_ID:
                hi2c->SlaveTxCpltCallback = pCallback;
                break;

            case HAL_I2C_SLAVE_RX_COMPLETE_CB_ID:
                hi2c->SlaveRxCpltCallback = pCallback;
                break;

            case HAL_I2C_LISTEN_COMPLETE_CB_ID:
                hi2c->ListenCpltCallback = pCallback;
                break;

            case HAL_I2C_MEM_TX_COMPLETE_CB_ID:
                hi2c->MemTxCpltCallback = pCallback;
                break;

            case HAL_I2C_MEM_RX_COMPLETE_CB_ID:
                hi2c->MemRxCpltCallback = pCallback;
                break;

            case HAL_I2C_ERROR_CB_ID:
                hi2c->ErrorCallback = pCallback;
                break;

            case HAL_I2C_ABORT_CB_ID:
                hi2c->AbortCpltCallback = pCallback;
                break;

            case HAL_I2C_MSPINIT_CB_ID:
                hi2c->MspInitCallback = pCallback;
                break;

            case HAL_I2C_MSPDEINIT_CB_ID:
                hi2c->MspDeInitCallback = pCallback;
                break;

            default:
                status = HAL_INVALID;
                break;
        }
    }
    else {
        status = HAL_BUSY;
    }


    return status;
}

/**
  * @brief  Unregister an I2C Callback.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  CallbackID  ID of the callback to unregister, value of @ref HAL_I2C_CallbackIDTypeDef.
  * @return HAL status
  * @retval HAL_OK       Callback restored to default weak implementation.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     A transfer is ongoing.
  * @note   Available only when USE_HAL_I2C_REGISTER_CALLBACKS = 1.
  * @ref    HAL_I2C_RegisterCallback
  */
HAL_StatusTypeDef HAL_I2C_UnRegisterCallback(HAL_I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Check NULL pointers */
    if (hi2c == NULL) {
        return HAL_INVALID;
    }


    if (hi2c->State == HAL_I2C_STATE_READY) {
        switch (CallbackID) {
            case HAL_I2C_MASTER_TX_COMPLETE_CB_ID:
                hi2c->MasterTxCpltCallback = HAL_I2C_MasterTxCpltCallback;
                break;

            case HAL_I2C_MASTER_RX_COMPLETE_CB_ID:
                hi2c->MasterRxCpltCallback = HAL_I2C_MasterRxCpltCallback;
                break;

            case HAL_I2C_SLAVE_TX_COMPLETE_CB_ID:
                hi2c->SlaveTxCpltCallback = HAL_I2C_SlaveTxCpltCallback;
                break;

            case HAL_I2C_SLAVE_RX_COMPLETE_CB_ID:
                hi2c->SlaveRxCpltCallback = HAL_I2C_SlaveRxCpltCallback;
                break;

            case HAL_I2C_LISTEN_COMPLETE_CB_ID:
                hi2c->ListenCpltCallback = HAL_I2C_ListenCpltCallback;
                break;

            case HAL_I2C_MEM_TX_COMPLETE_CB_ID:
                hi2c->MemTxCpltCallback = HAL_I2C_MemTxCpltCallback;
                break;

            case HAL_I2C_MEM_RX_COMPLETE_CB_ID:
                hi2c->MemRxCpltCallback = HAL_I2C_MemRxCpltCallback;
                break;

            case HAL_I2C_ERROR_CB_ID:
                hi2c->ErrorCallback = HAL_I2C_ErrorCallback;
                break;

            case HAL_I2C_ABORT_CB_ID:
                hi2c->AbortCpltCallback = HAL_I2C_AbortCpltCallback;
                break;

            case HAL_I2C_MSPINIT_CB_ID:
                hi2c->MspInitCallback = HAL_I2C_MspInit;
                break;

            case HAL_I2C_MSPDEINIT_CB_ID:
                hi2c->MspDeInitCallback = HAL_I2C_MspDeInit;
                break;

            default:
                status = HAL_INVALID;
                break;
        }
    }
    else {
        status = HAL_BUSY;
    }


    return status;
}

/**
  * @brief  Register the Slave Address Match I2C Callback.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  pCallback   Pointer to the Address Match Callback function.
  * @return HAL status
  * @retval HAL_OK       Callback registered.
  * @retval HAL_INVALID    Invalid parameter.
  * @retval HAL_BUSY     A transfer is ongoing.
  * @note   Use to override the default HAL_I2C_AddrCallback() implementation.
  * @ref    HAL_I2C_AddrCallback
  */
HAL_StatusTypeDef HAL_I2C_RegisterAddrCallback(HAL_I2C_HandleTypeDef *hi2c, HAL_I2C_AddrCallbackTypeDef pCallback)
{
    HAL_StatusTypeDef status = HAL_OK;

    if ((hi2c == NULL) || (pCallback == NULL)) {
        return HAL_INVALID;
    }


    if (hi2c->State == HAL_I2C_STATE_READY) {
        hi2c->AddrCallback = pCallback;
    }
    else {
        status = HAL_BUSY;
    }


    return status;
}

/**
 * @brief  Unregister the I2C Address Match Callback.
 * @param[in,out]  hi2c        Pointer to a @ref HAL_I2C_HandleTypeDef structure.
 * @return HAL status
 * @retval HAL_OK       Callback unregistered.
 * @retval HAL_INVALID    Invalid parameter.
 * @retval HAL_BUSY     A transfer is ongoing.
 * @note   This function is only available when USE_HAL_I2C_REGISTER_CALLBACKS is set to 1.
 *         After unregistering, the default weak callback function will be used.
 * @ref    HAL_I2C_RegisterAddrCallback
 */
HAL_StatusTypeDef HAL_I2C_UnRegisterAddrCallback(HAL_I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status = HAL_OK;

    if (hi2c == NULL) {
        return HAL_INVALID;
    }


    if (hi2c->State == HAL_I2C_STATE_READY) {
        hi2c->AddrCallback = HAL_I2C_AddrCallback;
    }
    else {
        status = HAL_BUSY;
    }


    return status;
}

#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group5 Peripheral State, Mode and Error functions
  * @{
  */

/**
  * @brief  Return the I2C handle state.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return HAL I2C state (@ref HAL_I2C_StateTypeDef).
  * @note   Used to query whether the peripheral is READY/BUSY in a non-blocking
  *         transfer. The handle must be non-NULL (asserted in debug builds).
  * @ref    HAL_I2C_GetMode HAL_I2C_GetError
  */
HAL_I2C_StateTypeDef HAL_I2C_GetState(const HAL_I2C_HandleTypeDef *hi2c)
{
    if (hi2c == NULL) {
        return (HAL_I2C_StateTypeDef)HAL_INVALID;
    }

    return (HAL_I2C_StateTypeDef)(hi2c->State);
}

/**
  * @brief  Return the I2C handle mode.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return HAL I2C mode (@ref HAL_I2C_ModeTypeDef).
  * @note   Indicates the current transfer role (NONE / MASTER / SLAVE / MEM).
  * @ref    HAL_I2C_GetState HAL_I2C_GetError
  */
HAL_I2C_ModeTypeDef HAL_I2C_GetMode(const HAL_I2C_HandleTypeDef *hi2c)
{
    if (hi2c == NULL) {
        return (HAL_I2C_ModeTypeDef)HAL_INVALID;
    }

    return (HAL_I2C_ModeTypeDef)(hi2c->Mode);
}

/**
  * @brief  Return the I2C error code.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @return I2C Error code (bitmask of @ref HAL_I2C_ErrorTypeDef).
  * @note   Cleared automatically when a new transfer is started.
  * @ref    HAL_I2C_GetState HAL_I2C_GetMode HAL_I2C_ErrorCallback
  */
uint32_t HAL_I2C_GetError(const HAL_I2C_HandleTypeDef *hi2c)
{
    if (hi2c == NULL) {
        return HAL_INVALID;
    }

    return hi2c->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */


#if defined (USE_HAL_I2C_DMA) && (USE_HAL_I2C_DMA == 1)
/* DMA support. */
/**
  * @brief  Bind the DMA handle used for I2C TX.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  hdma      Pointer to the TX DMA handle.
  * @return HAL status
  * @retval HAL_OK       DMA handle bound to the I2C handle.
  * @retval HAL_INVALID  Invalid I2C handle, instance or DMA channel.
  * @note   Must be called before HAL_I2C_Master_Transmit_DMA() or
  *         HAL_I2C_Slave_Transmit_DMA().
  */
HAL_StatusTypeDef HAL_I2C_SetTxDMA(HAL_I2C_HandleTypeDef *hi2c, HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if ((hdma == NULL) || (!IS_DMA_ALL_INSTANCE(hdma->Instance)) ||
            (hdma->Channel >= LL_DMA_CHANNEL_NUMS)) {
            return HAL_INVALID;
        }
    });

    hi2c->hTxDMA = hdma;
    hdma->Parent = (void *)hi2c;

    return HAL_OK;
}

/**
  * @brief  Bind the DMA handle used for I2C RX.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  hdma      Pointer to the RX DMA handle.
  * @return HAL status
  * @retval HAL_OK       DMA handle bound to the I2C handle.
  * @retval HAL_INVALID  Invalid I2C handle, instance or DMA channel.
  * @note   Must be called before HAL_I2C_Master_Receive_DMA() or
  *         HAL_I2C_Slave_Receive_DMA().
  */
HAL_StatusTypeDef HAL_I2C_SetRxDMA(HAL_I2C_HandleTypeDef *hi2c, HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }

        if ((hdma == NULL) || (!IS_DMA_ALL_INSTANCE(hdma->Instance)) ||
            (hdma->Channel >= LL_DMA_CHANNEL_NUMS)) {
            return HAL_INVALID;
        }
    });

    hi2c->hRxDMA = hdma;
    hdma->Parent = (void *)hi2c;

    return HAL_OK;
}

/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with DMA.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  DevAddress      Target device address.
  * @param[in]  pData           Pointer to the data buffer.
  * @param[in]  Size            Number of bytes to transmit.
  * @return HAL status
  * @retval HAL_OK       DMA transfer started; result via MasterTxCpltCallback.
  * @retval HAL_INVALID  Invalid parameter.
  * @retval HAL_ERROR    DMA handle missing or DMA start failed.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   pData must stay valid until the transfer completes. The TX DMA handle
  *         must be bound with HAL_I2C_SetTxDMA() beforehand.
  * @ref    HAL_I2C_Master_Transmit HAL_I2C_Master_Transmit_IT
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                               uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_HandleTypeDef *hdma = (hi2c != NULL) ? I2C_DMA_TX_HANDLE(hi2c) : NULL;
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }
    });

    if ((pData == NULL) || (Size == 0UL)) {
        return HAL_ERROR;
    }

    /* Reject re-entrant calls while a transfer is already in progress. */
    if (hi2c->State != HAL_I2C_STATE_READY) {
        return HAL_BUSY;
    }

    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->XferISR      = I2C_Master_ISR_DMA;
    hi2c->ErrorCode    = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr    = pData;
    hi2c->XferSize    = (Size > I2C_MAX_DATA_COUNT_PER_TRANS)
                        ? I2C_MAX_DATA_COUNT_PER_TRANS : Size;
    hi2c->XferCount   = Size - hi2c->XferSize;
    hi2c->Devaddress  = DevAddress;

    /* Start a DMA transfer from pData into the I2C TX FIFO.
       AUTOEND is set so the I2C generates STOP after all bytes are sent.
       The DMA callback only moves data into the FIFO; final completion is
       signalled by the I2C master-done (MDEIE) interrupt (DMA moves data, the
       I2C TC interrupt ends the transfer). */
    if (hdma == NULL) {
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }

    /* A channel left enabled by an aborted transfer would make the
       HAL_DMA_Start_IT() below return HAL_BUSY, so release it first. */
    if (hdma->State != HAL_DMA_STATE_READY) {
        (void)HAL_DMA_Abort(hdma);
    }

    hdma->XferCpltCallback = I2C_DMATxDoneCplt;
    hdma->XferErrorCallback = I2C_DMAErrorCplt;
    hdma->Parent = (void *)hi2c;

    LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)DevAddress);
    LL_I2C_HandleTransfer(hi2c->Instance, LL_I2C_DIRECTION_TRANSMIT,
                          hi2c->XferSize,
                          (hi2c->XferCount == 0UL) ? 1UL : 0UL);
    LL_I2C_EnableDMAReq_TX(hi2c->Instance);

    /* Enable the I2C master-done interrupt so completion is signalled only after
       the full transfer (including STOP) finishes on the bus, not when the DMA
       merely finishes loading the TX FIFO. Clear any stale flag first. */
    LL_I2C_ClearFlag_MDEI(hi2c->Instance);
    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_MDEIE | LL_I2C_IT_ERR_MASK);

    if (HAL_DMA_Start_IT(hdma, (uint32_t)pData,
                         (uint32_t)&hi2c->Instance->TXDATA,
                         (uint32_t)hi2c->XferSize) != HAL_OK) {
        LL_I2C_DisableDMAReq_TX(hi2c->Instance);
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }

    /* Trigger the transfer. */
    LL_I2C_ReleaseCommand(hi2c->Instance);


    return HAL_OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with DMA.
  * @param[in,out]  hi2c        Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  DevAddress      Target device address.
  * @param[out]  pData          Pointer to the receive buffer.
  * @param[in]  Size            Number of bytes to receive.
  * @return HAL status
  * @retval HAL_OK       DMA transfer started; result via MasterRxCpltCallback.
  * @retval HAL_INVALID  Invalid parameter.
  * @retval HAL_ERROR    DMA handle missing or DMA start failed.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   pData must stay valid until the transfer completes. The RX DMA handle
  *         must be bound with HAL_I2C_SetRxDMA() beforehand.
  * @ref    HAL_I2C_Master_Receive HAL_I2C_Master_Receive_IT
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                              uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_HandleTypeDef *hdma = (hi2c != NULL) ? I2C_DMA_RX_HANDLE(hi2c) : NULL;
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(IS_HAL_I2C_DEV_ADDRESS(hi2c, DevAddress));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }
    });

    if ((pData == NULL) || (Size == 0UL)) {
        return HAL_ERROR;
    }


    /* Reject re-entrant calls while a transfer is already in progress. */
    if (hi2c->State != HAL_I2C_STATE_READY) {
        return HAL_BUSY;
    }

    hi2c->State       = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->XferISR      = I2C_Master_ISR_DMA;
    hi2c->ErrorCode    = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr    = pData;
    hi2c->XferSize    = (Size > I2C_MAX_DATA_COUNT_PER_TRANS)
                        ? I2C_MAX_DATA_COUNT_PER_TRANS : Size;
    hi2c->XferCount   = Size - hi2c->XferSize;
    hi2c->Devaddress  = DevAddress;

    /* Start a DMA transfer from the I2C RX FIFO into pData.
       AUTOEND is set so the I2C generates STOP after Size bytes are received. */
    if (hdma == NULL) {
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }

    /* A channel left enabled by an aborted transfer would make the
       HAL_DMA_Start_IT() below return HAL_BUSY, so release it first. */
    if (hdma->State != HAL_DMA_STATE_READY) {
        (void)HAL_DMA_Abort(hdma);
    }

    hdma->XferCpltCallback = I2C_DMARxCplt;
    hdma->XferErrorCallback = I2C_DMAErrorCplt;
    hdma->Parent = (void *)hi2c;

    LL_I2C_SetSlaveAddr(hi2c->Instance, (uint32_t)DevAddress);

    /* Enable the I2C master-done interrupt so completion is signalled only after
       the full read (including STOP) finishes on the bus; the DMA callback only
       marks data received. Clear any stale flag first. Mirrors master TX DMA. */
    LL_I2C_ClearFlag_MDEI(hi2c->Instance);
    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_MDEIE | LL_I2C_IT_ERR_MASK);


    LL_I2C_HandleTransfer(hi2c->Instance, LL_I2C_DIRECTION_RECEIVE,
                          hi2c->XferSize,
                          (hi2c->XferCount == 0UL) ? 1UL : 0UL);
    LL_I2C_ReleaseCommand(hi2c->Instance);

    /* Now enable the RX DMA request and arm the channel. */
    LL_I2C_EnableDMAReq_RX(hi2c->Instance);

    if (HAL_DMA_Start_IT(hdma, (uint32_t)&hi2c->Instance->RXDATA,
                         (uint32_t)pData, (uint32_t)hi2c->XferSize) != HAL_OK) {
        LL_I2C_DisableDMAReq_RX(hi2c->Instance);
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Transmit in slave mode an amount of data in non-blocking mode with DMA.
  * @param[in,out]  hi2c    Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  pData       Pointer to the data buffer.
  * @param[in]  Size        Number of bytes to transmit.
  * @return HAL status
  * @retval HAL_OK       DMA transfer started; result via SlaveTxCpltCallback.
  * @retval HAL_INVALID  Invalid parameter.
  * @retval HAL_ERROR    DMA handle missing or DMA start failed.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   pData must stay valid until the master closes the transaction. The TX
  *         DMA handle must be bound with HAL_I2C_SetTxDMA() beforehand.
  * @ref    HAL_I2C_Slave_Transmit HAL_I2C_Slave_Transmit_IT
  */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                             uint8_t *pData, uint16_t Size)
{
    HAL_DMA_HandleTypeDef *hdma = (hi2c != NULL) ? I2C_DMA_TX_HANDLE(hi2c) : NULL;
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }
    });

    if ((pData == NULL) || (Size == 0UL)) {
        return HAL_ERROR;
    }


    /* Reject re-entrant calls while a transfer is already in progress. */
    if (hi2c->State != HAL_I2C_STATE_READY) {
        return HAL_BUSY;
    }

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    LL_I2C_AcknowledgeNextData(hi2c->Instance, LL_I2C_ACK);
    hi2c->XferISR   = I2C_Slave_ISR_DMA;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr  = pData;
    hi2c->XferSize  = Size;
    hi2c->XferCount = Size;
    /* No address match yet: a STOP is only accepted as end-of-transfer once this
       slave was really addressed (see I2C_Slave_ISR_DMA Detect-Stop branch). */
    hi2c->AddrEventCount = 0U;

    /* Prime the TX DMA so data is fed into the TX FIFO when the master
       addresses this slave and clocks the bus. Completion is signalled by the
       I2C interrupt (Detect-Stop), not by the DMA callback. */
    if (hdma == NULL) {
        /* DMA not configured: roll back to idle. */
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }

    /* A channel left enabled by an aborted transfer would make the
       HAL_DMA_Start_IT() below return HAL_BUSY, so release it first. */
    if (hdma->State != HAL_DMA_STATE_READY) {
        (void)HAL_DMA_Abort(hdma);
    }

    hdma->XferCpltCallback = I2C_DMATxCplt;
    hdma->XferErrorCallback = I2C_DMAErrorCplt;
    hdma->Parent = (void *)hi2c;


    /* Flush residual TX data and clear stale flags from a previous transfer. */
    I2C_FlushTxFIFO(hi2c);
    LL_I2C_ClearAllIntrFlags(hi2c->Instance);


    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_SPDETIE | LL_I2C_IT_RXADIE |
                    LL_I2C_IT_TXADIE | LL_I2C_IT_STDETIE | LL_I2C_IT_ERR_MASK);

    LL_I2C_EnableDMAReq_TX(hi2c->Instance);

    if (HAL_DMA_Start_IT(hdma, (uint32_t)pData,
                         (uint32_t)&hi2c->Instance->TXDATA, (uint32_t)Size) != HAL_OK) {
        LL_I2C_DisableDMAReq_TX(hi2c->Instance);
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }


    return HAL_OK;
}

/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with DMA.
  * @param[in,out]  hi2c    Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[out]  pData      Pointer to the receive buffer.
  * @param[in]  Size        Number of bytes to receive.
  * @return HAL status
  * @retval HAL_OK       DMA transfer started; result via SlaveRxCpltCallback.
  * @retval HAL_INVALID  Invalid parameter.
  * @retval HAL_ERROR    DMA handle missing or DMA start failed.
  * @retval HAL_BUSY     A transfer is already ongoing.
  * @note   pData must stay valid until the master closes the transaction. The RX
  *         DMA handle must be bound with HAL_I2C_SetRxDMA() beforehand.
  * @ref    HAL_I2C_Slave_Receive HAL_I2C_Slave_Receive_IT
  */
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                            uint8_t *pData, uint16_t Size)
{
    HAL_DMA_HandleTypeDef *hdma = (hi2c != NULL) ? I2C_DMA_RX_HANDLE(hi2c) : NULL;
    ASSERT_FUNC_PARAM(hi2c != NULL);
    ASSERT_FUNC_PARAM(IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_I2C_PARAM_CHECK({
        if ((hi2c == NULL) || (!IS_HAL_I2C_ALL_INSTANCE(hi2c->Instance))) {
            return HAL_INVALID;
        }
    });

    if ((pData == NULL) || (Size == 0UL)) {
        return HAL_ERROR;
    }


    /* Reject re-entrant calls while a transfer is already in progress. */
    if (hi2c->State != HAL_I2C_STATE_READY) {
        return HAL_BUSY;
    }

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    LL_I2C_AcknowledgeNextData(hi2c->Instance, LL_I2C_ACK);
    hi2c->XferISR   = I2C_Slave_ISR_DMA;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->pBuffPtr  = pData;
    hi2c->XferSize  = Size;
    hi2c->XferCount = Size;
    /* No address match yet: a STOP is only accepted as end-of-transfer once this
       slave was really addressed (see I2C_Slave_ISR_DMA Detect-Stop branch). */
    hi2c->AddrEventCount = 0U;

    /* Prime the RX DMA so received data is moved from the RX FIFO into pData
       when the master addresses this slave. Completion is signalled by the I2C
       interrupt (Detect-Stop), not by the DMA callback. */
    if (hdma == NULL) {
        /* DMA not configured: roll back to idle. */
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }

    /* A channel left enabled by an aborted transfer would make the
       HAL_DMA_Start_IT() below return HAL_BUSY, so release it first. */
    if (hdma->State != HAL_DMA_STATE_READY) {
        (void)HAL_DMA_Abort(hdma);
    }

    hdma->XferCpltCallback = I2C_DMARxCplt;
    hdma->XferErrorCallback = I2C_DMAErrorCplt;
    hdma->Parent = (void *)hi2c;


    /* Clear stale flags from a previous transfer. */
    LL_I2C_ClearAllIntrFlags(hi2c->Instance);

    /* In DMA mode the DMA channel only moves the data; the I2C interrupt reports
       the transfer lifecycle. ERR + Detect-Stop end and abort a transfer, and the
       address-match sources release the SCL stretch. The data-phase sources stay
       OFF so the CPU never races the DMA on the FIFO. */
    LL_I2C_EnableIT(hi2c->Instance, LL_I2C_IT_SPDETIE | LL_I2C_IT_RXADIE |
                    LL_I2C_IT_TXADIE | LL_I2C_IT_RXGCIE | LL_I2C_IT_STDETIE |
                    LL_I2C_IT_ERR_MASK);

    LL_I2C_EnableDMAReq_RX(hi2c->Instance);

    if (HAL_DMA_Start_IT(hdma, (uint32_t)&hi2c->Instance->RXDATA,
                         (uint32_t)pData, (uint32_t)Size) != HAL_OK) {
        LL_I2C_DisableDMAReq_RX(hi2c->Instance);
        hi2c->State   = HAL_I2C_STATE_READY;
        hi2c->Mode    = HAL_I2C_MODE_NONE;
        hi2c->XferISR = NULL;
        return HAL_ERROR;
    }


    return HAL_OK;
}

static void I2C_DMATxCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_I2C_HandleTypeDef *hi2c = (HAL_I2C_HandleTypeDef *)(hdma->Parent);

    if (hi2c == NULL) {
        return;
    }

    /* Disable the I2C TX DMA request; every byte is now queued in the TX FIFO. */
    LL_I2C_DisableDMAReq_TX(hi2c->Instance);
    hi2c->XferCount = 0U;
}

static void I2C_DMATxDoneCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_I2C_HandleTypeDef *hi2c = (HAL_I2C_HandleTypeDef *)(hdma->Parent);

    if (hi2c == NULL) {
        return;
    }

    LL_I2C_DisableDMAReq_TX(hi2c->Instance);
}

static void I2C_DMARxCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_I2C_HandleTypeDef *hi2c = (HAL_I2C_HandleTypeDef *)(hdma->Parent);

    if (hi2c == NULL) {
        return;
    }

    /* Disable the I2C RX DMA request; every byte is already in the buffer. */
    LL_I2C_DisableDMAReq_RX(hi2c->Instance);
    if (hi2c->Mode == HAL_I2C_MODE_SLAVE) {
        hi2c->XferCount = 0U;
    }
}

static void I2C_DMAErrorCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_I2C_HandleTypeDef *hi2c = (HAL_I2C_HandleTypeDef *)(hdma->Parent);

    if (hi2c == NULL) {
        return;
    }

    /* The failing channel is the one this callback was invoked for, so it is
       released here. The opposite direction, when used, is released by its own
       callback or by the next *_DMA transfer. */
    hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;
    (void)HAL_DMA_Abort(hdma);
    I2C_EndXfer(hi2c, NULL, NULL, HAL_I2C_STATE_READY);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->ErrorCallback(hi2c);
#else
    HAL_I2C_ErrorCallback(hi2c);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
}

static HAL_StatusTypeDef I2C_Master_ISR_DMA(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags,
                                            uint32_t ITSources)
{
    return I2C_Master_ISR_Core(hi2c, 1UL, ITFlags, ITSources);
}

/**
  * @brief  Slave-mode interrupt sub-routine for DMA transfers.
  * @note   In DMA mode the FIFO is serviced by the DMA, so this handler only
  *         deals with the control events - the
  *         address match (release the clock stretch and report the address), the
  *         Detect-Stop that ends the transfer and the Start condition. It never
  *         loads the TX FIFO itself, unlike the interrupt-mode I2C_Slave_ISR_IT.
  * @param[in,out]  hi2c  Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  ITFlags    Pending interrupt flags.
  * @param[in]  ITSources  Enabled interrupt sources.
  * @return HAL status
  */

static HAL_StatusTypeDef I2C_Slave_ISR_DMA(HAL_I2C_HandleTypeDef *hi2c, uint32_t ITFlags,
                                           uint32_t ITSources)
{
    /* === Check if Detect Stop interrupt === */
    if (((ITSources & LL_I2C_IT_SPDETIE) != 0UL) &&
        ((ITFlags   & LL_I2C_FLAG_SPETI)  != 0UL)) {
        LL_I2C_ClearFlag_SPETI(hi2c->Instance);


        if ((hi2c->AddrEventCount == 0UL) && (hi2c->XferCount == hi2c->XferSize)) {
            /* Spurious / not-yet-started STOP: stay armed and keep listening. */
        }
        else if (hi2c->State == HAL_I2C_STATE_BUSY_TX) {
            I2C_EndXfer(hi2c, I2C_DMA_TX_HANDLE(hi2c), I2C_DMA_RX_HANDLE(hi2c), HAL_I2C_STATE_READY);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
            hi2c->SlaveTxCpltCallback(hi2c);
#else
            HAL_I2C_SlaveTxCpltCallback(hi2c);
#endif
        }
        else if (hi2c->State == HAL_I2C_STATE_BUSY_RX) {

            I2C_EndXfer(hi2c, I2C_DMA_TX_HANDLE(hi2c), I2C_DMA_RX_HANDLE(hi2c), HAL_I2C_STATE_READY);
            /* Move the tail still sitting in the RX FIFO into the buffer, so the end
               of the write is not lost. */
            I2C_SlaveReadRxFIFO(hi2c);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
            hi2c->SlaveRxCpltCallback(hi2c);
#else
            HAL_I2C_SlaveRxCpltCallback(hi2c);
#endif
        }
        else {
            /* Nothing to do */
        }
    }

    /* === Check if Slave RX Address Done (slave addressed for RX by master write) === */
    else if (((ITSources & LL_I2C_IT_RXADIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_RXADI)  != 0UL)) {
        LL_I2C_ClearFlag_RXADI(hi2c->Instance);
        /* Record that this slave was addressed: the Detect-Stop branch only accepts
           a STOP as end-of-transfer after a real address match (see there). */
        hi2c->AddrEventCount++;

        /* Notify user via address match callback */
        uint32_t rxAddr = LL_I2C_GetAddressMatchCode(hi2c->Instance);
        uint8_t transferDir = 0x00U; /* 0=Write (master writes, slave receives) */
        uint16_t addrMatchCode = (uint16_t)(rxAddr & 0x3FFUL);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        if (hi2c->AddrCallback != NULL) {
            hi2c->AddrCallback(hi2c, transferDir, addrMatchCode);
        }
#else
        HAL_I2C_AddrCallback(hi2c, transferDir, addrMatchCode);
#endif
    }

    /* === Check if Slave TX Address Done (slave addressed for TX by master read) === */
    else if (((ITSources & LL_I2C_IT_TXADIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_TXADI)  != 0UL)) {
        /* DMA mode: the TX FIFO is fed by the DMA, so here we only release the
           address-match clock stretch by clearing the flag - no manual FIFO load. */
        LL_I2C_ClearFlag_TXADI(hi2c->Instance);
        /* Record that this slave was addressed: the Detect-Stop branch only accepts
           a STOP as end-of-transfer after a real address match (see there). */
        hi2c->AddrEventCount++;

        /* Notify user via address match callback */
        uint32_t rxAddr = LL_I2C_GetAddressMatchCode(hi2c->Instance);
        uint8_t transferDir = 0x01U; /* 1=Read (master reads, slave transmits) */
        uint16_t addrMatchCode = (uint16_t)(rxAddr & 0x3FFUL);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        if (hi2c->AddrCallback != NULL) {
            hi2c->AddrCallback(hi2c, transferDir, addrMatchCode);
        }
#else
        HAL_I2C_AddrCallback(hi2c, transferDir, addrMatchCode);
#endif
    }

    /* === Check if Slave RX General Call interrupt === */
    else if (((ITSources & LL_I2C_IT_RXGCIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_RXGCI)  != 0UL)) {
        LL_I2C_ClearFlag_RXGCI(hi2c->Instance);
        hi2c->AddrEventCount++;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        if (hi2c->AddrCallback != NULL) {
            hi2c->AddrCallback(hi2c, 0x00U, 0x0000U);
        }
#else
        HAL_I2C_AddrCallback(hi2c, 0x00U, 0x0000U);
#endif
    }

    /* === Check if Detect Start interrupt === */
    else if (((ITSources & LL_I2C_IT_STDETIE) != 0UL) &&
             ((ITFlags   & LL_I2C_FLAG_STDETI)  != 0UL)) {
        LL_I2C_ClearFlag_STDETI(hi2c->Instance);
        hi2c->EventCount++;
    }

    else {
        /* Nothing to do */
    }

    return HAL_OK;
}
#endif /* USE_HAL_I2C_DMA */

#endif /* HAL_I2C_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/
