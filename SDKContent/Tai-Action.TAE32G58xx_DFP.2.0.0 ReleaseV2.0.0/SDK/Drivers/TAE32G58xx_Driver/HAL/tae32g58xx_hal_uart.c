/**
  ******************************************************************************
  * @file    tae32g58xx_hal_uart.c
  * @author  Tai-Action SD Team
  * @brief   UART HAL module driver.
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

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @defgroup UART_HAL UART HAL
  * @brief UART HAL module driver
  * @{
  */

#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_UART_MODULE_ENABLED) && (HAL_UART_MODULE_ENABLED == 1)

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup UART_HAL_Private_Macros UART HAL Private Macros
  * @{
  */

#define IS_UART_BAUDRATE(BAUD)          ((BAUD) != 0U)
#define IS_UART_WORDLENGTH(LEN)         (((LEN) == HAL_UART_WORDLENGTH_5B) || ((LEN) == HAL_UART_WORDLENGTH_6B) || \
                                         ((LEN) == HAL_UART_WORDLENGTH_7B) || ((LEN) == HAL_UART_WORDLENGTH_8B))
#define IS_UART_STOPBITS(STOP)          (((STOP) == HAL_UART_STOPBITS_1) || ((STOP) == HAL_UART_STOPBITS_2))
#define IS_UART_PARITY(PARITY)          (((PARITY) == HAL_UART_PARITY_NONE) || ((PARITY) == HAL_UART_PARITY_EVEN) || \
                                            ((PARITY) == HAL_UART_PARITY_ODD))
#define IS_UART_MODE(MODE)              (((MODE) == HAL_UART_MODE_RX) || \
                                                 ((MODE) == HAL_UART_MODE_TX) || \
                                                 ((MODE) == HAL_UART_MODE_TX_RX))
#define IS_UART_OVERSAMPLING(SAMP)      (((SAMP) == HAL_UART_OVERSAMPLING_16) || ((SAMP) == HAL_UART_OVERSAMPLING_8))
#define IS_UART_ADVFEATURE_INIT(INIT)   (((INIT) == HAL_UART_ADVFEATURE_NO_INIT) || \
                                                  ((INIT) == HAL_UART_ADVFEATURE_INIT))
#define IS_UART_ADVFEATURE_OPTION(OPT)  (((OPT) == HAL_UART_ADVFEATURE_DISABLE) || \
                                                  ((OPT) == HAL_UART_ADVFEATURE_ENABLE))
#define IS_UART_DEPOLARITY(POL)         (((POL) == HAL_UART_DE_POLARITY_HIGH) || \
                                                  ((POL) == HAL_UART_DE_POLARITY_LOW))
#define IS_UART_AUTOBAUD_MODE(MODE)     (((MODE) == HAL_UART_AUTOBAUD_MODE_1FALLING) || \
                                                  ((MODE) == HAL_UART_AUTOBAUD_MODE_1RISING) || \
                                                  ((MODE) == HAL_UART_AUTOBAUD_MODE_2FALLING) || \
                                                  ((MODE) == HAL_UART_AUTOBAUD_MODE_2RISING))

/**
 * @}
 */ /* UART_HAL_Private_Macros */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup UART_HAL_Private_Functions UART HAL Private Functions
  * @{
  */
static void UART_TxISR_8BIT(HAL_UART_HandleTypeDef *huart);
static void UART_RxISR_8BIT(HAL_UART_HandleTypeDef *huart);
static void UART_TxDone_ISR(HAL_UART_HandleTypeDef *huart);
static void UART_EndRxTransfer(HAL_UART_HandleTypeDef *huart);
static void UART_DMATransmitCplt(HAL_DMA_HandleTypeDef *hdma);
static void UART_DMAReceiveCplt(HAL_DMA_HandleTypeDef *hdma);
static void UART_DMATxHalfCplt(HAL_DMA_HandleTypeDef *hdma);
static void UART_DMARxHalfCplt(HAL_DMA_HandleTypeDef *hdma);
static void UART_DMAError(HAL_DMA_HandleTypeDef *hdma);
static void UART_EndTxTransfer(HAL_UART_HandleTypeDef *huart);
/**
  * @}
  */ /* UART_HAL_Private_Functions */

/* Exported functions --------------------------------------------------------*/
/** @defgroup UART_HAL_Exported_Functions UART HAL Exported Functions
  * @{
  */

/** @defgroup UART_HAL_EF_Init Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
  * @verbatim
  * ===============================================================================
  *            ##### Initialization and Configuration functions #####
  * ===============================================================================
  * [..]
  *   This subsection provides a set of functions allowing to initialize the UART.
  *   (+) HAL_UART_Init(): the Instance is carried by the handle.
  *   (+) HAL_UART_DeInit(): de-initialize the UART peripheral.
  * @endverbatim
  * @{
  */

/**
  * @brief  Initialize the UART peripheral according to the specified parameters
  *         in the HAL_UART_InitTypeDef and create the associated handle.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  *         the configuration information for the specified UART module.
  * @param  UARTx Pointer to the UART peripheral instance.
  * @param  Init  Pointer to a HAL_UART_InitTypeDef structure that contains
  *         the configuration parameters for the UART peripheral.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Init(HAL_UART_HandleTypeDef *huart, UART_TypeDef *UARTx,
                                HAL_UART_InitTypeDef *Init)
{
    uint32_t tmpreg;

    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_FUNC_PARAM(Init != NULL);
    ASSERT_FUNC_PARAM(IS_UART_BAUDRATE(Init->BaudRate));
    ASSERT_FUNC_PARAM(IS_UART_WORDLENGTH(Init->WordLength));
    ASSERT_FUNC_PARAM(IS_UART_STOPBITS(Init->StopBits));
    ASSERT_FUNC_PARAM(IS_UART_PARITY(Init->Parity));
    ASSERT_FUNC_PARAM(IS_UART_MODE(Init->Mode));
    ASSERT_FUNC_PARAM(IS_UART_OVERSAMPLING(Init->OverSampling));
    ASSERT_FUNC_PARAM(IS_UART_ADVFEATURE_INIT(Init->AdvFeatureInit));

    HAL_UART_PARAM_CHECK({ 
        if (IS_UART_BAUDRATE(Init->BaudRate) == 0U) { 
            return HAL_INVALID; 
        } 

        if (IS_UART_WORDLENGTH(Init->WordLength) == 0U) { 
            return HAL_INVALID; 
        }

        if (IS_UART_STOPBITS(Init->StopBits) == 0U) { 
            return HAL_INVALID; 
        }

        if (IS_UART_PARITY(Init->Parity) == 0U) { 
            return HAL_INVALID; 
        }

        if (IS_UART_MODE(Init->Mode) == 0U) { 
            return HAL_INVALID; 
        }

        if (IS_UART_OVERSAMPLING(Init->OverSampling) == 0U) { 
            return HAL_INVALID; 
        }

        if (IS_UART_ADVFEATURE_INIT(Init->AdvFeatureInit) == 0U) { 
            return HAL_INVALID; 
        }
    });

    if ((huart == NULL) || (IS_UART_ALL_INSTANCE(UARTx) == 0U) || (Init == NULL)) {
        return HAL_INVALID;
    }

    /* Bind the instance passed by the caller. This allows HAL_UART_Init to be
       called even when the user has not pre-initialised the handle variable. */
    huart->Instance = UARTx;

    huart->gState = HAL_UART_STATE_BUSY;
    huart->RxState = HAL_UART_STATE_BUSY;

    /* Init the low level hardware: GPIO, CLOCK, NVIC */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->MspInitCallback == NULL) {
        huart->MspInitCallback = HAL_UART_MspInit;
    }
    huart->MspInitCallback(huart);
#else
    HAL_UART_MspInit(huart);
#endif

#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
    huart->hTxDMA = (HAL_DMA_HandleTypeDef *) NULL;            
    huart->hRxDMA = (HAL_DMA_HandleTypeDef *) NULL;             
#endif /* USE_HAL_UART_DMA */

    /* It must disable the UART while configuring certain registers */
    LL_UART_Disable(UARTx);

    /* Reset UART FIFO */
    LL_UART_ResetTxFIFO(UARTx);
    LL_UART_ResetRxFIFO(UARTx);

    /* Advanced features (RS485 / auto-baud / timeout / polarity / pin options) */
    if (Init->AdvFeatureInit == HAL_UART_ADVFEATURE_INIT) {
        HAL_UART_AdvFeatureTypeDef *pAdv = &Init->Init;

        if (pAdv->RS485Mode == HAL_UART_ADVFEATURE_RS485_ENABLE) {
            LL_UART_EnableRS485(UARTx);
            LL_UART_SetDESignalPolarity(UARTx, pAdv->DEPolarity);
            LL_UART_SetDEAssertionTime(UARTx, pAdv->DEAssertionTime);
            LL_UART_SetDEDeassertionTime(UARTx, pAdv->DEDeassertionTime);
        } else {
            LL_UART_DisableRS485(UARTx);
        }

        if (pAdv->AutoBaudRateMode != 0U) {
            LL_UART_SetAutoBaudRateMode(UARTx, pAdv->AutoBaudRateMode);
            LL_UART_EnableAutoBaudRate(UARTx);
        } else {
            LL_UART_DisableAutoBaudRate(UARTx);
        }

        if (pAdv->ReceiverTimeout == HAL_UART_ADVFEATURE_RX_TIMEOUT_ENABLE) {
            LL_UART_SetRxTimeout(UARTx, pAdv->RxTimeoutValue);
            LL_UART_EnableRxTimeout(UARTx);
        } else {
            LL_UART_DisableRxTimeout(UARTx);
        }

        if (pAdv->TxPinInv == HAL_UART_ADVFEATURE_TXINV_ENABLE) {
            LL_UART_SetTXPinLevel(UARTx, LL_UART_TXPIN_LEVEL_INVERTED);
        } else {
            LL_UART_SetTXPinLevel(UARTx, LL_UART_TXPIN_LEVEL_STANDARD);
        }

        if (pAdv->RxPinInv == HAL_UART_ADVFEATURE_RXINV_ENABLE) {
            LL_UART_SetRXPinLevel(UARTx, LL_UART_RXPIN_LEVEL_INVERTED);
        } else {
            LL_UART_SetRXPinLevel(UARTx, LL_UART_RXPIN_LEVEL_STANDARD);
        }

        if (pAdv->PinSwap == HAL_UART_ADVFEATURE_SWAP_ENABLE) {
            LL_UART_SetTXRXSwap(UARTx, LL_UART_TXRX_SWAPPED);
        } else {
            LL_UART_SetTXRXSwap(UARTx, LL_UART_TXRX_STANDARD);
        }

        if (pAdv->Loopback == HAL_UART_ADVFEATURE_LOOPBACK_ENABLE) {
            LL_UART_EnableLoopback(UARTx);
        } else {
            LL_UART_DisableLoopback(UARTx);
        }

        if (pAdv->MSBFirst == HAL_UART_ADVFEATURE_MSBFIRST_ENABLE) {
            LL_UART_SetTransferBitOrder(UARTx, LL_UART_TRANSFER_BIT_ORDER_MSB);
        } else {
            LL_UART_SetTransferBitOrder(UARTx, LL_UART_TRANSFER_BIT_ORDER_LSB);
        }
    } else {
        LL_UART_DisableRS485(UARTx);
        LL_UART_DisableAutoBaudRate(UARTx);
        LL_UART_DisableRxTimeout(UARTx);
        LL_UART_SetTXPinLevel(UARTx, LL_UART_TXPIN_LEVEL_STANDARD);
        LL_UART_SetRXPinLevel(UARTx, LL_UART_RXPIN_LEVEL_STANDARD);
        LL_UART_SetTXRXSwap(UARTx, LL_UART_TXRX_STANDARD);
        LL_UART_DisableLoopback(UARTx);
        LL_UART_SetTransferBitOrder(UARTx, LL_UART_TRANSFER_BIT_ORDER_LSB);
    }

    /* Parity configuration (LL_UART_SetParity handles PEN/PSEL, NONE included) */
    LL_UART_SetParity(UARTx, Init->Parity);

    /* Data length and stop bits */
    LL_UART_SetDataWidth(UARTx, Init->WordLength);
    LL_UART_SetStopBitsLength(UARTx, Init->StopBits);

    /* Oversampling */
    LL_UART_SetOverSampling(UARTx, Init->OverSampling);

    /* Baudrate configuration (hardware basis: baud_rate = (apb_clk + baud/2) / baud) */
    tmpreg = HAL_UART_IsOnAPB1(UARTx) ? HAL_RCU_GetPCLK1Freq() : HAL_RCU_GetPCLK0Freq();
    tmpreg = (tmpreg + (Init->BaudRate / 2U)) / Init->BaudRate;
    LL_UART_SetBaudRate(UARTx, tmpreg);

    /* Transmitter / Receiver enable */
    if ((Init->Mode & HAL_UART_MODE_TX) != 0U) {
        LL_UART_EnableDirectionTx(UARTx);
    } else {
        LL_UART_DisableDirectionTx(UARTx);
    }

    if ((Init->Mode & HAL_UART_MODE_RX) != 0U) {
        LL_UART_EnableDirectionRx(UARTx);
    } else {
        LL_UART_DisableDirectionRx(UARTx);
    }

    /* Initialize transfer state machine and ISR handlers (8-bit data path) */
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->pTxBuffPtr = NULL;
    huart->TxXferSize = 0U;
    huart->TxXferCount = 0U;
    huart->pRxBuffPtr = NULL;
    huart->RxXferSize = 0U;
    huart->RxXferCount = 0U;
    huart->TxISR = UART_TxISR_8BIT;
    huart->RxISR = UART_RxISR_8BIT;

    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
    huart->RxEventType = HAL_UART_RXEVENT_IDLE;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    /* Bind default (weak) callbacks so an unregistered handle falls back safely */
    huart->TxCpltCallback = HAL_UART_TxCpltCallback;
    huart->TxHalfCpltCallback = HAL_UART_TxHalfCpltCallback;
    huart->RxCpltCallback = HAL_UART_RxCpltCallback;
    huart->RxHalfCpltCallback = HAL_UART_RxHalfCpltCallback;
    huart->ErrorCallback = HAL_UART_ErrorCallback;
    huart->AbortCpltCallback = HAL_UART_AbortCpltCallback;
    huart->AbortTransmitCpltCallback = HAL_UART_AbortTransmitCpltCallback;
    huart->AbortReceiveCpltCallback = HAL_UART_AbortReceiveCpltCallback;
    huart->RxEventCallback = HAL_UART_RxEventCallback;
    huart->RxFifoFullCallback = HAL_UART_RxFifoFullCallback;
    huart->TxFifoEmptyCallback = HAL_UART_TxFifoEmptyCallback;
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

    huart->gState = HAL_UART_STATE_READY;
    huart->RxState = HAL_UART_STATE_READY;

    /* Enable the UART peripheral */
    LL_UART_Enable(UARTx);

    return HAL_OK;
}

/**
  * @brief  De-initialize the UART peripheral.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  *         the configuration information for the specified UART module.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_DeInit(HAL_UART_HandleTypeDef *huart)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    if ((huart == NULL) || (!IS_UART_ALL_INSTANCE(huart->Instance))) {
        return HAL_INVALID;
    }

    huart->gState = HAL_UART_STATE_BUSY;

    /* Disable the UART peripheral */
    LL_UART_Disable(huart->Instance);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->MspDeInitCallback == NULL) {
        huart->MspDeInitCallback = HAL_UART_MspDeInit;
    }
    huart->MspDeInitCallback(huart);
#else
    HAL_UART_MspDeInit(huart);
#endif

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_RESET;
    huart->RxState = HAL_UART_STATE_RESET;

    /* Reset handle to default values */
    huart->Instance = NULL;
    huart->TxXferSize = 0U;
    huart->TxXferCount = 0U;
    huart->RxXferSize = 0U;
    huart->RxXferCount = 0U;

    return HAL_OK;
}


#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
/**
  * @brief Set DMA handle for transmission.
  * @param huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  * @param hdma Pointer to a HAL_DMA_HandleTypeDef structure that contains the DMA instance
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_SetTxDMA(HAL_UART_HandleTypeDef *huart, HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM((uint32_t)hdma->Channel < (uint32_t)LL_DMA_CHANNEL_NUMS);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (!IS_UART_ALL_INSTANCE(huart->Instance))) { 
            return HAL_INVALID; 
        } 

        if ((hdma == NULL) || (!IS_DMA_ALL_INSTANCE(hdma->Instance)) || (hdma->Channel >= LL_DMA_CHANNEL_NUMS)) { 
            return HAL_INVALID; 
        } 
    });

    huart->hTxDMA = hdma;
    huart->hTxDMA->Parent = huart;

    return HAL_OK;
}

/**
  * @brief Set DMA handle for reception.
  * @param huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  * @param hdma Pointer to a HAL_DMA_HandleTypeDef structure that contains the DMA instance
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_SetRxDMA(HAL_UART_HandleTypeDef *huart, HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM((uint32_t)hdma->Channel < (uint32_t)LL_DMA_CHANNEL_NUMS);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (!IS_UART_ALL_INSTANCE(huart->Instance))) { 
            return HAL_INVALID; 
        } 

        if ((hdma == NULL) || (!IS_DMA_ALL_INSTANCE(hdma->Instance)) || (hdma->Channel >= LL_DMA_CHANNEL_NUMS)) { 
            return HAL_INVALID; 
        } 
    });

    huart->hRxDMA = hdma;
    huart->hRxDMA->Parent = huart;

    return HAL_OK;
}


#endif /* USE_HAL_UART_DMA */

/**
  * @brief  Initialize the UART MSP.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  *         the configuration information for the specified UART module.
  * @return None
  */
__WEAK void HAL_UART_MspInit(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_UART_MspInit could be implemented in the user file. */
}

/**
  * @brief  De-initialize the UART MSP.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  *         the configuration information for the specified UART module.
  * @return None
  */
__WEAK void HAL_UART_MspDeInit(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_UART_MspDeInit could be implemented in the user file. */
}

/**
  * @}
  */ /* UART_HAL_EF_Init */

/** @defgroup UART_HAL_EF_IO IO operation functions
  *  @brief   UART Transmit/Receive functions
  *
  * @verbatim
  * ===============================================================================
  *                      ##### IO operation functions #####
  * ===============================================================================
  * [..]
  *   This subsection provides a set of functions allowing to manage the UART
  *   data transfers.
  * @endverbatim
  * @{
  */

/**
  * @brief  Send an amount of data in blocking mode.
  * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured
  *         as 8 bits, the transmitted data is handled as a set of u8.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  *         the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Amount of data elements (u8) to be sent.
  * @param  Timeout Timeout duration in ms (HAL_MAX_DELAY waits forever).
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit(HAL_UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    UART_TypeDef *UARTx;
    uint32_t tickstart = 0U;

    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    if ((pData == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    if (huart->gState != HAL_UART_STATE_READY) {

        return HAL_BUSY;
    }

    UARTx = huart->Instance;
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;
    huart->TxXferCount = 0U;

    tickstart = HAL_GetTick();

    /* Reset Tx FIFO */
    LL_UART_ResetTxFIFO(UARTx);
    LL_UART_EnableDirectionTx(UARTx);
    LL_UART_ClearFlag_All(UARTx);

    /* Transfer loop */
    while (huart->TxXferCount < Size) {
        /* Wait for TX FIFO not full */
        while (LL_UART_IsTxFIFOFull(UARTx)) {
            if ((Timeout != HAL_MAX_DELAY) && (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))) {
                huart->gState = HAL_UART_STATE_READY;

                return HAL_TIMEOUT;
            }
        }
        LL_UART_TransmitData8(UARTx, (uint32_t)(*pData++));
        huart->TxXferCount++;
    }

    /* Wait for transfer complete (TX done flag) */
    while (!LL_UART_IsActiveFlag(UARTx, LL_UART_FLAG_TDIF)) {
        if ((Timeout != HAL_MAX_DELAY) && (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))) {
            huart->gState = HAL_UART_STATE_READY;

            return HAL_TIMEOUT;
        }
    }
    LL_UART_ClearFlag(UARTx, LL_UART_FLAG_TDIF);

    huart->gState = HAL_UART_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  *         the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Amount of data elements (u8) to be received.
  * @param  Timeout Timeout duration in ms (HAL_MAX_DELAY waits forever).
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    UART_TypeDef *UARTx;
    uint32_t tickstart = 0U;

    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    if ((pData == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    if (huart->RxState != HAL_UART_STATE_READY) {

        return HAL_BUSY;
    }

    UARTx = huart->Instance;
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;
    huart->RxXferCount = 0U;

    tickstart = HAL_GetTick();

    LL_UART_EnableDirectionRx(UARTx);

    /* Transfer loop */
    while (huart->RxXferCount < Size) {
        /* Wait for RX FIFO not empty */
        while (LL_UART_IsRxFIFOEmpty(UARTx)) {
            if ((Timeout != HAL_MAX_DELAY) && (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))) {
                huart->RxState = HAL_UART_STATE_READY;

                return HAL_TIMEOUT;
            }
        }
        *pData++ = (uint8_t)LL_UART_ReceiveData8(UARTx);
        huart->RxXferCount++;
    }

    huart->RxState = HAL_UART_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Send an amount of data in non-blocking mode with Interrupt.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Amount of data elements (u8) to be sent.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit_IT(HAL_UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
    UART_TypeDef *UARTx;

    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    if ((pData == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    if (huart->gState != HAL_UART_STATE_READY) {

        return HAL_BUSY;
    }

    UARTx = huart->Instance;
    huart->pTxBuffPtr = pData;
    huart->TxXferSize = Size;
    huart->TxXferCount = 0U;
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    /* Reset Tx FIFO and clear pending, then enable transmitter */
    LL_UART_ResetTxFIFO(UARTx);
    LL_UART_ClearFlag(UARTx, LL_UART_FLAG_TDIF);
    LL_UART_EnableDirectionTx(UARTx);

    /* Enable TX empty interrupt */
    LL_UART_EnableIT(UARTx, LL_UART_IT_TEIE);

    return HAL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Amount of data elements (u8) to be received.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive_IT(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    UART_TypeDef *UARTx;

    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    if ((pData == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    if (huart->RxState != HAL_UART_STATE_READY) {

        return HAL_BUSY;
    }

    UARTx = huart->Instance;
    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;
    huart->RxXferCount = 0U;
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;

    /* Enable receiver */
    LL_UART_EnableDirectionRx(UARTx);

    /* Enable RX not-empty interrupt */
    LL_UART_EnableIT(UARTx, LL_UART_IT_RFIE);

    return HAL_OK;
}

#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
/**
  * @brief  Send an amount of data in non-blocking mode with DMA.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Amount of data elements (u8) to be sent.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit_DMA(HAL_UART_HandleTypeDef *huart, 
                                        const uint8_t *pData, 
                                        uint16_t Size)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(huart->hTxDMA != NULL);
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    if ((huart->hTxDMA == NULL) ||(pData == NULL) || (Size == 0U)) {
        return HAL_ERROR;
    }

    if (huart->gState != HAL_UART_STATE_READY) {
        return HAL_BUSY;
    }
    
    UART_TypeDef *UARTx = huart->Instance;
    HAL_DMA_HandleTypeDef *hdma = huart->hTxDMA;

    huart->pTxBuffPtr = pData;
    huart->TxXferSize = Size;
    huart->TxXferCount = 0U;
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    /* Reset Tx FIFO and enable transmitter via LL layer */
    LL_UART_ResetTxFIFO(UARTx);
    LL_UART_ClearFlag(UARTx, LL_UART_FLAG_TDIF);
    LL_UART_EnableDirectionTx(UARTx);

    /* Route the DMA events to the UART DMA Tx callbacks */
    hdma->XferCpltCallback = UART_DMATransmitCplt;
    hdma->XferHalfCpltCallback = UART_DMATxHalfCplt;
    hdma->XferErrorCallback = UART_DMAError;
    hdma->Parent = (void *)huart;

    /* Enable UART TX DMA request via LL layer (no hard-coded register) */
    LL_UART_EnableDMAReq_TX(UARTx);

    /* Kick off the DMA transfer through the DMA HAL driver */
    return HAL_DMA_Start_IT(hdma, (uint32_t)pData, LL_UART_DMA_GetRegAddr(UARTx, LL_UART_DMA_REG_DATA_TRANSMIT), (uint32_t)Size);
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Amount of data elements (u8) to be received.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive_DMA(HAL_UART_HandleTypeDef *huart,
                                       uint8_t *pData, 
                                       uint16_t Size)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(huart->hRxDMA != NULL);
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    if ((huart->hRxDMA == NULL) ||(pData == NULL) || (Size == 0U)) {
        return HAL_ERROR;
    }

    if (huart->RxState != HAL_UART_STATE_READY) {
        return HAL_BUSY;
    }

    UART_TypeDef *UARTx = huart->Instance;
    HAL_DMA_HandleTypeDef *hdma = huart->hRxDMA;

    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;
    huart->RxXferCount = 0U;
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;

    /* Enable receiver via LL layer */
    LL_UART_EnableDirectionRx(UARTx);

    /* Route the DMA events to the UART DMA Rx callbacks */
    hdma->XferCpltCallback = UART_DMAReceiveCplt;
    hdma->XferHalfCpltCallback = UART_DMARxHalfCplt;
    hdma->XferErrorCallback = UART_DMAError;
    hdma->Parent = (void *)huart;

    /* Enable UART RX DMA request via LL layer (no hard-coded register) */
    LL_UART_EnableDMAReq_RX(UARTx);

    /* Kick off the DMA transfer through the DMA HAL driver */
    return HAL_DMA_Start_IT(hdma, LL_UART_DMA_GetRegAddr(UARTx, LL_UART_DMA_REG_DATA_RECEIVE), (uint32_t)pData, (uint32_t)Size);
}
#endif /* USE_HAL_UART_DMA */

/**
  * @brief  Flush the UART RX FIFO, discarding the data already buffered.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  * @note   Bytes already pushed into the RX FIFO are discarded and the related
  *         pending flags are cleared, so that a glitch captured while the
  *         receiver was enabled but not yet serviced (e.g. between
  *         HAL_UART_Init() and HAL_UART_Receive_IT()) is not treated as the
  *         first received byte.
  */
HAL_StatusTypeDef HAL_UART_FlushRx(HAL_UART_HandleTypeDef *huart)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    HAL_UART_PARAM_CHECK({
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) {
            return HAL_INVALID;
        }
    });

    LL_UART_ResetRxFIFO(huart->Instance);
    LL_UART_ClearFlag(huart->Instance,
                      (LL_UART_FLAG_RXFI | LL_UART_FLAG_IDIF | LL_UART_FLAG_RTOI |
                       LL_UART_FLAG_PEIF | LL_UART_FLAG_FEIF | LL_UART_FLAG_ROIF |
                       LL_UART_FLAG_NOIF));

    /* The discarded bytes may have set PE/FE/ORE; those records are meaningless
       once the data is dropped, otherwise GetError() keeps reporting them. */
    huart->ErrorCode = HAL_UART_ERROR_NONE;

    return HAL_OK;
}

/**
  * @brief  Flush the UART TX FIFO, discarding the data not yet shifted out.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_FlushTx(HAL_UART_HandleTypeDef *huart)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    HAL_UART_PARAM_CHECK({
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) {
            return HAL_INVALID;
        }
    });

    LL_UART_ResetTxFIFO(huart->Instance);
    LL_UART_ClearFlag(huart->Instance,
                      (LL_UART_FLAG_TXEI | LL_UART_FLAG_TDIF | LL_UART_FLAG_TOIF));

    return HAL_OK;
}

/**
  * @brief  Check whether the given UART status flag is active.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  Flag Status flag to check, one of the HAL_UART_INT_*_IT_FLAG masks.
  * @return 1 when the flag is active, 0 otherwise
  * @note   Wraps LL_UART_IsActiveFlag() so that upper layers do not have to call
  *         the LL layer directly.
  */
uint32_t HAL_UART_GetFlag(const HAL_UART_HandleTypeDef *huart, uint32_t Flag)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    HAL_UART_PARAM_CHECK({
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) {
            return 0U;
        }
    });

    return LL_UART_IsActiveFlag(huart->Instance, Flag);
}

/**
  * @brief  Abort ongoing transfers (blocking).
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_Abort(HAL_UART_HandleTypeDef *huart)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    /* Disable all UART interrupts and both DMA requests */
    LL_UART_DisableIT(huart->Instance, (LL_UART_IT_RFIE | LL_UART_IT_TEIE | LL_UART_IT_TDIE |
                                         LL_UART_IT_IDIE | LL_UART_IT_PEIE | LL_UART_IT_FEIE | LL_UART_IT_ROIE));
    LL_UART_DisableDMAReq_TX(huart->Instance);
    LL_UART_DisableDMAReq_RX(huart->Instance);

    huart->TxXferCount = 0U;
    huart->RxXferCount = 0U;
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
    huart->gState = HAL_UART_STATE_READY;
    huart->RxState = HAL_UART_STATE_READY;

    LL_UART_ResetTxFIFO(huart->Instance);
    LL_UART_ResetRxFIFO(huart->Instance);

    huart->ErrorCode |= HAL_UART_ERROR_ABORT;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->AbortCpltCallback != NULL) {
        huart->AbortCpltCallback(huart);
    } else {
        HAL_UART_AbortCpltCallback(huart);
    }
#else
    HAL_UART_AbortCpltCallback(huart);
#endif

    return HAL_OK;
}

/**
  * @brief  Abort ongoing transfers (non-blocking).
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_AbortTransmit(HAL_UART_HandleTypeDef *huart)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    LL_UART_DisableIT(huart->Instance, (LL_UART_IT_TEIE | LL_UART_IT_TDIE));
    LL_UART_DisableDMAReq_TX(huart->Instance);

    huart->TxXferCount = 0U;
    huart->gState = HAL_UART_STATE_READY;

    LL_UART_ResetTxFIFO(huart->Instance);

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->AbortTransmitCpltCallback != NULL) {
        huart->AbortTransmitCpltCallback(huart);
    } else {
        HAL_UART_AbortTransmitCpltCallback(huart);
    }
#else
    HAL_UART_AbortTransmitCpltCallback(huart);
#endif

    return HAL_OK;
}

/**
  * @brief  Abort Receive transfer (non-blocking).
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_AbortReceive(HAL_UART_HandleTypeDef *huart)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    LL_UART_DisableIT(huart->Instance, (LL_UART_IT_RFIE | LL_UART_IT_IDIE | LL_UART_IT_RTIE |
                                        LL_UART_IT_PEIE | LL_UART_IT_FEIE | LL_UART_IT_ROIE));
    LL_UART_DisableDMAReq_RX(huart->Instance);

    huart->RxXferCount = 0U;
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
    huart->RxState = HAL_UART_STATE_READY;

    LL_UART_ResetRxFIFO(huart->Instance);

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->AbortReceiveCpltCallback != NULL) {
        huart->AbortReceiveCpltCallback(huart);
    } else {
        HAL_UART_AbortReceiveCpltCallback(huart);
    }
#else
    HAL_UART_AbortReceiveCpltCallback(huart);
#endif

    return HAL_OK;
}

/**
  * @brief  Abort ongoing transfers.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  * @note   The transfer is stopped and the recovery callback is issued before this
  *         function returns: no interrupt is left pending on the abort sequence.
  */
HAL_StatusTypeDef HAL_UART_Abort_IT(HAL_UART_HandleTypeDef *huart)
{
    return HAL_UART_Abort(huart);
}

/**
  * @brief  Abort ongoing transmit transfer.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(HAL_UART_HandleTypeDef *huart)
{
    return HAL_UART_AbortTransmit(huart);
}

/**
  * @brief  Abort ongoing receive transfer.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(HAL_UART_HandleTypeDef *huart)
{
    return HAL_UART_AbortReceive(huart);
}

/**
  * @brief  Handle UART interrupt request.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure that contains
  *         the configuration information for the specified UART module.
  * @return None
  */
void HAL_UART_IRQHandler(HAL_UART_HandleTypeDef *huart)
{
    UART_TypeDef *UARTx = huart->Instance;
    uint32_t isrflags;
    uint32_t cr1its;
    uint32_t errorflags;
    uint32_t served = 0U;

    isrflags = LL_UART_ReadInterruptPending(UARTx);
    cr1its = LL_UART_ReadInterruptMask(UARTx);

    /* If no interrupt is enabled, exit */
    if ((isrflags & cr1its) == 0U) {
        return;
    }

    /* Error flags: parity / framing / overrun */
    errorflags = isrflags & (LL_UART_FLAG_PEIF | LL_UART_FLAG_FEIF | LL_UART_FLAG_ROIF);
    if (errorflags != 0U) {
        huart->ErrorCode |= (errorflags & LL_UART_FLAG_PEIF) ? HAL_UART_ERROR_PE : 0U;
        huart->ErrorCode |= (errorflags & LL_UART_FLAG_FEIF) ? HAL_UART_ERROR_FE : 0U;
        huart->ErrorCode |= (errorflags & LL_UART_FLAG_ROIF) ? HAL_UART_ERROR_ORE : 0U;

        served |= (LL_UART_FLAG_PEIF | LL_UART_FLAG_FEIF | LL_UART_FLAG_ROIF);

        /* Disable erroneous transfer */
        LL_UART_DisableIT(UARTx, (LL_UART_IT_RFIE | LL_UART_IT_TEIE | LL_UART_IT_TDIE));

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        if (huart->ErrorCallback != NULL) {
            huart->ErrorCallback(huart);
        } else {
            HAL_UART_ErrorCallback(huart);
        }
#else
        HAL_UART_ErrorCallback(huart);
#endif
    }

    /* Transfer complete (TX done) */
    if (((isrflags & LL_UART_FLAG_TDIF) != 0U) && ((cr1its & LL_UART_IT_TDIE) != 0U)) {
        served |= LL_UART_FLAG_TDIF;
        UART_TxDone_ISR(huart);
    }

    /* TX empty: transmit next data */
    if (((isrflags & LL_UART_FLAG_TXEI) != 0U) && ((cr1its & LL_UART_IT_TEIE) != 0U)) {
        served |= LL_UART_FLAG_TXEI;
        if (huart->TxISR != NULL) {
            huart->TxISR(huart);
        }

        /* TX FIFO empty event. This device has no dedicated TX FIFO empty interrupt
           (CR1.TXFEIE); the event is derived from the TX FIFO threshold interrupt
           (INTEN.TEIE) and qualified by STATUS.TFE (TX FIFO completely empty). */
        if (LL_UART_IsTxFIFOEmpty(UARTx) != 0U) {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
            if (huart->TxFifoEmptyCallback != NULL) {
                huart->TxFifoEmptyCallback(huart);
            } else {
                HAL_UART_TxFifoEmptyCallback(huart);
            }
#else
            HAL_UART_TxFifoEmptyCallback(huart);
#endif
        }
    }

    /* RX FIFO full event. This device has no dedicated RX FIFO full interrupt
       (CR1.RXFFIE); the event is derived from the RX FIFO threshold interrupt
       (INTEN.RFIE) and qualified by STATUS.RFF (RX FIFO completely full). */
    if (((isrflags & LL_UART_FLAG_RXFI) != 0U) && ((cr1its & LL_UART_IT_RFIE) != 0U) &&
        (LL_UART_IsRxFIFOFull(UARTx) != 0U)) {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        if (huart->RxFifoFullCallback != NULL) {
            huart->RxFifoFullCallback(huart);
        } else {
            HAL_UART_RxFifoFullCallback(huart);
        }
#else
        HAL_UART_RxFifoFullCallback(huart);
#endif
    }

    /* RX not empty: receive next data (or idle/timeout end) */
    if (((isrflags & (LL_UART_FLAG_RXFI | LL_UART_FLAG_IDIF | LL_UART_FLAG_RTOI)) != 0U) &&
        ((cr1its & (LL_UART_IT_RFIE | LL_UART_IT_IDIE | LL_UART_IT_RTIE)) != 0U)) {
        served |= (LL_UART_FLAG_RXFI | LL_UART_FLAG_IDIF | LL_UART_FLAG_RTOI);
        if ((isrflags & (LL_UART_FLAG_IDIF | LL_UART_FLAG_RTOI)) != 0U) {
            /* Idle / timeout: end of reception with current count */
            huart->RxEventType = HAL_UART_RXEVENT_IDLE;
            UART_EndRxTransfer(huart);

            if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
                huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
                if (huart->RxEventCallback != NULL) {
                    huart->RxEventCallback(huart);
                } else {
                    HAL_UART_RxEventCallback(huart);
                }
#else
                HAL_UART_RxEventCallback(huart);
#endif
            } else {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
                if (huart->RxCpltCallback != NULL) {
                    huart->RxCpltCallback(huart);
                } else {
                    HAL_UART_RxCpltCallback(huart);
                }
#else
                HAL_UART_RxCpltCallback(huart);
#endif
            }
        } else if (huart->RxISR != NULL) {
            huart->RxISR(huart);
        }
    }

    /* Clear all served pending bits */
    if (served != 0U) {
        LL_UART_ClearFlag(UARTx, served);
    }
}

/**
  * @}
  */ /* UART_HAL_EF_IO */

/** @defgroup UART_HAL_EF_State Peripheral state and error functions
  *  @brief   UART Peripheral State functions
  *
  * @verbatim
  * ===============================================================================
  *                       ##### Peripheral State functions #####
  * ===============================================================================
  * [..]
  *   This subsection provides a set of functions allowing to return the state
  *   and the error number of the UART peripheral.
  * @endverbatim
  * @{
  */

/**
  * @brief  Return the UART handle state.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return The UART handle state (gState | RxState)
  */
HAL_UART_StateTypeDef HAL_UART_GetState(const HAL_UART_HandleTypeDef *huart)
{
    uint32_t tmp;

    ASSERT_FUNC_PARAM(huart != NULL);

    if (huart == NULL) {
        return HAL_UART_STATE_RESET;
    }


    tmp = (uint32_t)huart->gState | (uint32_t)huart->RxState;
    return (HAL_UART_StateTypeDef)tmp;
}

/**
  * @brief  Return the UART error code.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return UART Error Code
  */
uint32_t HAL_UART_GetError(const HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_UART_ERROR_NONE;
    }
    ASSERT_FUNC_PARAM(huart != NULL);

    return huart->ErrorCode;
}

/**
  * @}
  */ /* UART_HAL_EF_State */

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
/** @defgroup UART_HAL_EF_Callback Callback registration
  * @{
  */

/**
  * @brief  Register a user UART callback.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  CallbackID ID of the callback to register.
  * @param  pCallback pointer to the callback function.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_RegisterCallback(HAL_UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
                                            HAL_UART_CallbackTypeDef pCallback)
{
    HAL_StatusTypeDef status = HAL_OK;

    if ((huart == NULL) || (pCallback == NULL)) {
        return HAL_INVALID;
    }

    switch (CallbackID) {
        case HAL_UART_TX_COMPLETE_CB_ID:
            huart->TxCpltCallback = pCallback;
            break;
        case HAL_UART_TX_HALFCOMPLETE_CB_ID:
            huart->TxHalfCpltCallback = pCallback;
            break;
        case HAL_UART_RX_COMPLETE_CB_ID:
            huart->RxCpltCallback = pCallback;
            break;
        case HAL_UART_RX_HALFCOMPLETE_CB_ID:
            huart->RxHalfCpltCallback = pCallback;
            break;
        case HAL_UART_ERROR_CB_ID:
            huart->ErrorCallback = pCallback;
            break;
        case HAL_UART_ABORT_COMPLETE_CB_ID:
            huart->AbortCpltCallback = pCallback;
            break;
        case HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID:
            huart->AbortTransmitCpltCallback = pCallback;
            break;
        case HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID:
            huart->AbortReceiveCpltCallback = pCallback;
            break;
        case HAL_UART_RX_FIFO_FULL_CB_ID:
            huart->RxFifoFullCallback = pCallback;
            break;
        case HAL_UART_TX_FIFO_EMPTY_CB_ID:
            huart->TxFifoEmptyCallback = pCallback;
            break;
        case HAL_UART_MSPINIT_CB_ID:
            huart->MspInitCallback = pCallback;
            break;
        case HAL_UART_MSPDEINIT_CB_ID:
            huart->MspDeInitCallback = pCallback;
            break;
        default:
            status = HAL_ERROR;
            break;
    }

    return status;
}

/**
  * @brief  Unregister a UART callback.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  CallbackID ID of the callback to unregister.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_UnRegisterCallback(HAL_UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID)
{
    HAL_StatusTypeDef status = HAL_OK;

    if (huart == NULL) {
        return HAL_INVALID;
    }

    switch (CallbackID) {
        case HAL_UART_TX_COMPLETE_CB_ID:
            huart->TxCpltCallback = HAL_UART_TxCpltCallback;
            break;
        case HAL_UART_TX_HALFCOMPLETE_CB_ID:
            huart->TxHalfCpltCallback = HAL_UART_TxHalfCpltCallback;
            break;
        case HAL_UART_RX_COMPLETE_CB_ID:
            huart->RxCpltCallback = HAL_UART_RxCpltCallback;
            break;
        case HAL_UART_RX_HALFCOMPLETE_CB_ID:
            huart->RxHalfCpltCallback = HAL_UART_RxHalfCpltCallback;
            break;
        case HAL_UART_ERROR_CB_ID:
            huart->ErrorCallback = HAL_UART_ErrorCallback;
            break;
        case HAL_UART_ABORT_COMPLETE_CB_ID:
            huart->AbortCpltCallback = HAL_UART_AbortCpltCallback;
            break;
        case HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID:
            huart->AbortTransmitCpltCallback = HAL_UART_AbortTransmitCpltCallback;
            break;
        case HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID:
            huart->AbortReceiveCpltCallback = HAL_UART_AbortReceiveCpltCallback;
            break;
        case HAL_UART_RX_FIFO_FULL_CB_ID:
            huart->RxFifoFullCallback = HAL_UART_RxFifoFullCallback;
            break;
        case HAL_UART_TX_FIFO_EMPTY_CB_ID:
            huart->TxFifoEmptyCallback = HAL_UART_TxFifoEmptyCallback;
            break;
        case HAL_UART_MSPINIT_CB_ID:
            huart->MspInitCallback = HAL_UART_MspInit;
            break;
        case HAL_UART_MSPDEINIT_CB_ID:
            huart->MspDeInitCallback = HAL_UART_MspDeInit;
            break;
        default:
            status = HAL_ERROR;
            break;
    }

    return status;
}

/**
  * @brief  Register the UART Rx Event callback.
  * @param  huart UART handle.
  * @param  pCallback pointer to the callback function.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_RegisterRxEventCallback(HAL_UART_HandleTypeDef *huart, HAL_UART_CallbackTypeDef pCallback)
{
    if ((huart == NULL) || (pCallback == NULL)) {
        return HAL_INVALID;
    }

    huart->RxEventCallback = pCallback;

    return HAL_OK;
}

/**
  * @brief  Unregister the UART Rx Event callback and restore the default.
  * @param  huart UART handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_UnRegisterRxEventCallback(HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    huart->RxEventCallback = HAL_UART_RxEventCallback;

    return HAL_OK;
}

/**
 * @}
 */ /* UART_HAL_EF_Callback */
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

/** @defgroup UART_HAL_EF_Timeout_Fifo Receiver Timeout and FIFO Threshold functions
  * @brief    Receiver timeout (RTO) and FIFO threshold configuration functions.
  * @{
  */

/**
  * @brief  Configure the UART receiver timeout value on the fly.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  TimeoutValue Receiver timeout value (RTO.RTO[15:0]).
  * @return None
  */
void HAL_UART_ReceiverTimeout_Config(HAL_UART_HandleTypeDef *huart, uint32_t TimeoutValue)
{
    if (huart == NULL) {
        return;
    }

    LL_UART_SetRxTimeout(huart->Instance, TimeoutValue);
}

/**
  * @brief  Enable the UART receiver timeout feature.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_EnableReceiverTimeout(HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_READY) {
        huart->gState = HAL_UART_STATE_BUSY;

        LL_UART_EnableRxTimeout(huart->Instance);

        huart->gState = HAL_UART_STATE_READY;
        return HAL_OK;
    }

    return HAL_BUSY;
}

/**
  * @brief  Disable the UART receiver timeout feature.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_DisableReceiverTimeout(HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_READY) {
        huart->gState = HAL_UART_STATE_BUSY;

        LL_UART_DisableRxTimeout(huart->Instance);

        huart->gState = HAL_UART_STATE_READY;
        return HAL_OK;
    }

    return HAL_BUSY;
}

/**
  * @brief  Set the TX FIFO threshold.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  Threshold TX FIFO threshold.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_SetTxFifoThreshold(HAL_UART_HandleTypeDef *huart, uint32_t Threshold)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_READY) {
        huart->gState = HAL_UART_STATE_BUSY;

        /* The threshold can only be updated while the peripheral is disabled */
        LL_UART_Disable(huart->Instance);
        LL_UART_SetTXFIFOThreshold(huart->Instance, Threshold);
        LL_UART_Enable(huart->Instance);

        huart->gState = HAL_UART_STATE_READY;
        return HAL_OK;
    }

    return HAL_BUSY;
}

/**
  * @brief  Set the RX FIFO threshold.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @param  Threshold RX FIFO threshold.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_SetRxFifoThreshold(HAL_UART_HandleTypeDef *huart, uint32_t Threshold)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_READY) {
        huart->gState = HAL_UART_STATE_BUSY;

        /* The threshold can only be updated while the peripheral is disabled */
        LL_UART_Disable(huart->Instance);
        LL_UART_SetRXFIFOThreshold(huart->Instance, Threshold);
        LL_UART_Enable(huart->Instance);

        huart->gState = HAL_UART_STATE_READY;
        return HAL_OK;
    }

    return HAL_BUSY;
}

/**
  * @brief  Enable the UART FIFO mode.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_EnableFifoMode(HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_READY) {
        huart->gState = HAL_UART_STATE_BUSY;

        /* The FIFO mode can only be updated while the peripheral is disabled */
        LL_UART_Disable(huart->Instance);
        LL_UART_EnableFIFO(huart->Instance);
        LL_UART_Enable(huart->Instance);

        huart->gState = HAL_UART_STATE_READY;
        return HAL_OK;
    }

    return HAL_BUSY;
}

/**
  * @brief  Disable the UART FIFO mode (switch to non-FIFO mode, CR0.NFE).
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_DisableFifoMode(HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_READY) {
        huart->gState = HAL_UART_STATE_BUSY;

        /* The FIFO mode can only be updated while the peripheral is disabled */
        LL_UART_Disable(huart->Instance);
        LL_UART_DisableFIFO(huart->Instance);
        LL_UART_Enable(huart->Instance);

        huart->gState = HAL_UART_STATE_READY;
        return HAL_OK;
    }

    return HAL_BUSY;
}

/**
  * @}
  */ /* UART_HAL_EF_Timeout_Fifo */

/** @defgroup UART_HAL_EF_DMA DMA transfer control functions
  * @brief    DMA transfer control functions.
  * @{
  */
#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
/**
  * @brief  Pause the DMA transfer.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_DMAPause(HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_BUSY_TX) {
        /* Disable the UART DMA Tx request (CR0.DTE[6]) */
        LL_UART_DisableDMAReq_TX(huart->Instance);
    }

    if (huart->RxState == HAL_UART_STATE_BUSY_RX) {
        /* Disable the parity / framing / overrun error interrupts */
        LL_UART_DisableIT(huart->Instance, (LL_UART_IT_PEIE | LL_UART_IT_FEIE | LL_UART_IT_ROIE));
        /* Disable the UART DMA Rx request (CR0.DRE[5]) */
        LL_UART_DisableDMAReq_RX(huart->Instance);
    }

    return HAL_OK;
}

/**
  * @brief  Resume the DMA transfer.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_DMAResume(HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_INVALID;
    }

    if (huart->gState == HAL_UART_STATE_BUSY_TX) {
        /* Enable the UART DMA Tx request (CR0.DTE[6]) */
        LL_UART_EnableDMAReq_TX(huart->Instance);
    }

    if (huart->RxState == HAL_UART_STATE_BUSY_RX) {
        /* Clear the overrun flag before resuming the Rx transfer */
        LL_UART_ClearFlag(huart->Instance, LL_UART_FLAG_ROIF);
        /* Re-enable the parity / framing / overrun error interrupts */
        LL_UART_EnableIT(huart->Instance, (LL_UART_IT_PEIE | LL_UART_IT_FEIE | LL_UART_IT_ROIE));
        /* Enable the UART DMA Rx request (CR0.DRE[5]) */
        LL_UART_EnableDMAReq_RX(huart->Instance);
    }

    return HAL_OK;
}

/**
  * @brief  Stop the DMA transfer.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_DMAStop(HAL_UART_HandleTypeDef *huart)
{
    HAL_UART_StateTypeDef gstate;
    HAL_UART_StateTypeDef rxstate;

    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 
    });

    if (((huart->hTxDMA == NULL) && (huart->hRxDMA == NULL))) {
        return HAL_INVALID;
    }

    gstate  = huart->gState;
    rxstate = huart->RxState;

    /* Stop the UART DMA Tx request if ongoing */
    if ((huart->hTxDMA != NULL) && (gstate == HAL_UART_STATE_BUSY_TX)) {
        if (LL_UART_IsEnabledDMAReq_TX(huart->Instance)) {
            LL_UART_DisableDMAReq_TX(huart->Instance);
            if (HAL_DMA_Abort(huart->hTxDMA) != HAL_OK) {
                if (HAL_DMA_GetError(huart->hTxDMA) == HAL_DMA_ERROR_TIMEOUT) {
                    huart->ErrorCode = HAL_UART_ERROR_DMA;
                    return HAL_TIMEOUT;
                }
            }
            UART_EndTxTransfer(huart);            
        }
    }

    /* Stop the UART DMA Rx request if ongoing */
    if ((huart->hRxDMA != NULL)  && (rxstate == HAL_UART_STATE_BUSY_RX)) {
        if (LL_UART_IsEnabledDMAReq_TX(huart->Instance)) {
            LL_UART_DisableDMAReq_RX(huart->Instance);
            if (HAL_DMA_Abort(huart->hRxDMA ) != HAL_OK) {
                if (HAL_DMA_GetError(huart->hRxDMA ) == HAL_DMA_ERROR_TIMEOUT) {
                    huart->ErrorCode = HAL_UART_ERROR_DMA;
                    return HAL_TIMEOUT;
                }
            }
            UART_EndRxTransfer(huart);
        }
    }

    return HAL_OK;
}
#endif /* USE_HAL_UART_DMA */
/**
  * @}
  */ /* UART_HAL_EF_DMA */

/** @defgroup UART_HAL_EF_RxEvent Reception event functions
  * @brief    Reception event functions.
  * @{
  */

/**
  * @brief  Receive an amount of data until the expected amount of data is received
  *         or the reception is completed by an Idle line detection.
  * @param  huart UART handle.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Maximum amount of data elements (u8) to be received.
  * @param  RxLen Number of data elements received.
  * @param  Timeout Timeout duration.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_UART_ReceiveToIdle(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size,
                                           uint16_t *RxLen, uint32_t Timeout)
{
    UART_TypeDef *UARTx;
    uint32_t tickstart;

    if ((huart == NULL) || (pData == NULL) || (RxLen == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    HAL_UART_PARAM_CHECK({
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) {
            return HAL_INVALID;
        }
    });

    if (huart->RxState != HAL_UART_STATE_READY) {
        return HAL_BUSY;
    }

    UARTx = huart->Instance;

    huart->pRxBuffPtr    = pData;
    huart->RxXferSize    = Size;
    huart->RxXferCount   = Size;
    huart->ErrorCode     = HAL_UART_ERROR_NONE;
    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
    huart->RxEventType   = HAL_UART_RXEVENT_IDLE;
    huart->RxState       = HAL_UART_STATE_BUSY_RX;

    LL_UART_ClearFlag(UARTx, LL_UART_FLAG_IDIF);
    LL_UART_EnableDirectionRx(UARTx);

    tickstart = HAL_GetTick();

    while (huart->RxXferCount > 0U) {
        if (LL_UART_IsActiveFlag(UARTx, LL_UART_FLAG_RXFI) != 0U) {
            *pData = (uint8_t)LL_UART_ReceiveData8(UARTx);
            pData++;
            huart->RxXferCount--;
        } else if (LL_UART_IsActiveFlag(UARTx, LL_UART_FLAG_IDIF) != 0U) {
            /* Idle line detected: end of the reception, with the current count */
            LL_UART_ClearFlag(UARTx, LL_UART_FLAG_IDIF);
            break;
        } else {
            /* No data available yet */
        }

        if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) > Timeout)) {
            huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
            huart->RxState       = HAL_UART_STATE_READY;
            return HAL_TIMEOUT;
        }
    }

    *RxLen = (uint16_t)(huart->RxXferSize - huart->RxXferCount);

    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
    huart->RxState       = HAL_UART_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Receive an amount of data in interrupt mode until the expected amount of
  *         data is received or the reception is completed by an Idle line detection.
  * @param  huart UART handle.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Maximum amount of data elements (u8) to be received.
  * @return HAL status
  * @note   The reception completion is reported through the @ref HAL_UART_RxEventCallback
  *         callback, and the amount of data received is available through
  *         @ref HAL_UART_GetRxEventType and the handle RxXferCount field.
  */
HAL_StatusTypeDef HAL_UART_ReceiveToIdle_IT(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_StatusTypeDef status;

    if ((huart == NULL) || (pData == NULL) || (Size == 0U)) {
        return HAL_INVALID;
    }

    status = HAL_UART_Receive_IT(huart, pData, Size);
    if (status == HAL_OK) {
        huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
        huart->RxEventType   = HAL_UART_RXEVENT_IDLE;
    }

    return status;
}

#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
/**
  * @brief  Receive an amount of data in DMA mode until the expected amount of
  *         data is received or the reception is completed by an Idle line detection.
  * @param  huart UART handle.
  * @param  pData Pointer to data buffer (u8).
  * @param  Size Maximum amount of data elements (u8) to be received.
  * @return HAL status
  * @note   The Idle line detection ends the reception before the programmed size is
  *         reached, but does not release the DMA channel: call @ref HAL_UART_DMAStop
  *         once the reception is completed.
  */
HAL_StatusTypeDef HAL_UART_ReceiveToIdle_DMA(HAL_UART_HandleTypeDef *huart,
                                               uint8_t *pData, 
                                               uint16_t Size)
{
    ASSERT_FUNC_PARAM(huart != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(huart->Instance));
    ASSERT_FUNC_PARAM(huart->hRxDMA != NULL);
    ASSERT_FUNC_PARAM(pData != NULL);
    ASSERT_FUNC_PARAM(Size != 0U);

    HAL_UART_PARAM_CHECK({ 
        if ((huart == NULL) || (IS_UART_ALL_INSTANCE(huart->Instance) == 0U)) { 
            return HAL_INVALID; 
        } 

        if ((huart->hRxDMA == NULL) || (pData == NULL) || (Size == 0U)) {
            return HAL_INVALID;
        }        
    });

    HAL_StatusTypeDef status = HAL_UART_Receive_DMA(huart, pData, Size);
    if (status == HAL_OK) {
        huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
        huart->RxEventType   = HAL_UART_RXEVENT_IDLE;

        /* Arm the Idle line detection so that the reception can end before Size is reached */
        LL_UART_EnableIT(huart->Instance, LL_UART_IT_IDIE);
    }

    return status;
}
#endif /* USE_HAL_UART_DMA */

/**
  * @brief  Return the Rx event type of the last completed reception.
  * @param  huart UART handle.
  * @return Rx event type. @ref HAL_UART_RXEVENT_TC / _HT / _IDLE
  */
uint32_t HAL_UART_GetRxEventType(const HAL_UART_HandleTypeDef *huart)
{
    if (huart == NULL) {
        return HAL_UART_RXEVENT_IDLE;
    }

    return huart->RxEventType;
}

/**
  * @}
  */ /* UART_HAL_EF_RxEvent */

/** @defgroup UART_HAL_EF_ITCallback Interrupt Callback functions
  * @{
  */

/**
  * @brief  Tx Transfer completed callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_TxCpltCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_TxCpltCallback can be implemented in the user file.
     */
}

/**
  * @brief  Tx Half Transfer completed callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_TxHalfCpltCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_TxHalfCpltCallback can be implemented in the user file.
     */
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @return None
  */
/**
  * @brief  Reception event callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_RxEventCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
             the HAL_UART_RxEventCallback can be implemented in the user file.
     */
}

/**
  * @brief  Rx FIFO full callback.
  * @note   Called from HAL_UART_IRQHandler() when the RX FIFO threshold interrupt
  *         (INTEN.RFIE) is enabled and the RX FIFO is actually full (STATUS.RFF).
  *         The threshold is configured with HAL_UART_SetRxFifoThreshold()
  *         (0xF means "16 data received = full").
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_RxFifoFullCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
             the HAL_UART_RxFifoFullCallback can be implemented in the user file.
     */
}

/**
  * @brief  Tx FIFO empty callback.
  * @note   Called from HAL_UART_IRQHandler() when the TX FIFO threshold interrupt
  *         (INTEN.TEIE) is enabled and the TX FIFO is actually empty (STATUS.TFE).
  *         The threshold is configured with HAL_UART_SetTxFifoThreshold()
  *         (0x0 means "no data left = empty").
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_TxFifoEmptyCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
             the HAL_UART_TxFifoEmptyCallback can be implemented in the user file.
     */
}


/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_RxCpltCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_RxCpltCallback can be implemented in the user file.
     */
}

/**
  * @brief  Rx Half Transfer completed callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_RxHalfCpltCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_RxHalfCpltCallback can be implemented in the user file.
     */
}

/**
  * @brief  UART error callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_ErrorCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_ErrorCallback can be implemented in the user file.
     */
}

/**
  * @brief  UART Abort Complete callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_AbortCpltCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_AbortCpltCallback can be implemented in the user file.
     */
}

/**
  * @brief  UART Abort Transmit Complete callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_AbortTransmitCpltCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_AbortTransmitCpltCallback can be implemented in the user file.
     */
}

/**
  * @brief  UART Abort Receive Complete callback.
  * @param  huart UART handle.
  * @return None
  */
__WEAK void HAL_UART_AbortReceiveCpltCallback(HAL_UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(huart);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_AbortReceiveCpltCallback can be implemented in the user file.
     */
}

/**
  * @}
  */ /* UART_HAL_EF_ITCallback */

/**
  * @}
  */ /* UART_HAL_Exported_Functions */

/* Private functions ---------------------------------------------------------*/
/** @defgroup UART_HAL_Private_Functions UART HAL Private Functions
  * @{
  */

/**
  * @brief  End ongoing Tx transfer.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return None
  */
static void UART_EndTxTransfer(HAL_UART_HandleTypeDef *huart)
{
    LL_UART_DisableIT(huart->Instance, (LL_UART_IT_TEIE | LL_UART_IT_TDIE));
    huart->TxXferCount = 0U;
    huart->gState = HAL_UART_STATE_READY;
}

/**
  * @brief  End ongoing Rx transfer.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return None
  */
static void UART_EndRxTransfer(HAL_UART_HandleTypeDef *huart)
{
    LL_UART_DisableIT(huart->Instance, (LL_UART_IT_RFIE | LL_UART_IT_IDIE | LL_UART_IT_RTIE));
    huart->RxXferCount = 0U;
    huart->RxState = HAL_UART_STATE_READY;
}

/**
  * @brief  TX interrupt handler (8-bit data path).
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return None
  */
static void UART_TxISR_8BIT(HAL_UART_HandleTypeDef *huart)
{
    UART_TypeDef *UARTx = huart->Instance;

    LL_UART_TransmitData8(UARTx, (uint32_t)(*huart->pTxBuffPtr++));
    huart->TxXferCount++;

    if (huart->TxXferCount >= huart->TxXferSize) {
        /* All data sent: stop the TX-empty interrupt, enable TX-done */
        LL_UART_DisableIT(UARTx, LL_UART_IT_TEIE);
        LL_UART_EnableIT(UARTx, LL_UART_IT_TDIE);
    }
}

/**
  * @brief  RX interrupt handler (8-bit data path).
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return None
  */
static void UART_RxISR_8BIT(HAL_UART_HandleTypeDef *huart)
{
    UART_TypeDef *UARTx = huart->Instance;

    *huart->pRxBuffPtr++ = (uint8_t)LL_UART_ReceiveData8(UARTx);
    huart->RxXferCount++;

    if (huart->RxXferCount >= huart->RxXferSize) {
        LL_UART_DisableIT(UARTx, LL_UART_IT_RFIE);
        huart->RxState = HAL_UART_STATE_READY;

        if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
            huart->RxEventType   = HAL_UART_RXEVENT_TC;
            huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
            if (huart->RxEventCallback != NULL) {
                huart->RxEventCallback(huart);
            } else {
                HAL_UART_RxEventCallback(huart);
            }
#else
            HAL_UART_RxEventCallback(huart);
#endif
        } else {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
            if (huart->RxCpltCallback != NULL) {
                huart->RxCpltCallback(huart);
            } else {
                HAL_UART_RxCpltCallback(huart);
            }
#else
            HAL_UART_RxCpltCallback(huart);
#endif
        }
    }
}

/**
  * @brief  TX-done interrupt handler.
  * @param  huart Pointer to a HAL_UART_HandleTypeDef structure.
  * @return None
  */
static void UART_TxDone_ISR(HAL_UART_HandleTypeDef *huart)
{
    UART_TypeDef *UARTx = huart->Instance;

    LL_UART_DisableIT(UARTx, LL_UART_IT_TDIE);
    LL_UART_DisableDirectionTx(UARTx);
    huart->gState = HAL_UART_STATE_READY;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->TxCpltCallback != NULL) {
        huart->TxCpltCallback(huart);
    } else {
        HAL_UART_TxCpltCallback(huart);
    }
#else
    HAL_UART_TxCpltCallback(huart);
#endif
}

/**
  * @brief  DMA TX transfer-complete callback.
  * @note   Invoked by the DMA HAL driver. The UART TX DMA request is closed here and
  *         the completion is deferred to the TX-done interrupt, which fires once the
  *         last frame has been shifted out by the UART.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
static void UART_DMATransmitCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UART_HandleTypeDef *huart = (HAL_UART_HandleTypeDef *)(hdma->Parent);

    if (huart == NULL) {
        return;
    }

    /* Disable UART TX DMA request via LL layer */
    LL_UART_DisableDMAReq_TX(huart->Instance);

    huart->TxXferCount = huart->TxXferSize;

    LL_UART_EnableIT(huart->Instance, LL_UART_IT_TDIE);
}

/**
  * @brief  DMA RX transfer-complete callback.
  * @note   Invoked by the DMA HAL driver. The UART RX DMA request is closed here and
  *         the HAL state is restored; the receiver itself stays enabled.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
static void UART_DMAReceiveCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UART_HandleTypeDef *huart = (HAL_UART_HandleTypeDef *)(hdma->Parent);

    if (huart == NULL) {
        return;
    }

    /* Disable UART RX DMA request via LL layer */
    LL_UART_DisableDMAReq_RX(huart->Instance);

    huart->RxXferCount = huart->RxXferSize;
    huart->RxState = HAL_UART_STATE_READY;

    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
        huart->RxEventType   = HAL_UART_RXEVENT_TC;
        huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        if (huart->RxEventCallback != NULL) {
            huart->RxEventCallback(huart);
        } else {
            HAL_UART_RxEventCallback(huart);
        }
#else
        HAL_UART_RxEventCallback(huart);
#endif
    } else {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        if (huart->RxCpltCallback != NULL) {
            huart->RxCpltCallback(huart);
        } else {
            HAL_UART_RxCpltCallback(huart);
        }
#else
        HAL_UART_RxCpltCallback(huart);
#endif
    }
}

/**
  * @brief  DMA TX half-transfer callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
static void UART_DMATxHalfCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UART_HandleTypeDef *huart = (HAL_UART_HandleTypeDef *)(hdma->Parent);

    if (huart == NULL) {
        return;
    }

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->TxHalfCpltCallback != NULL) {
        huart->TxHalfCpltCallback(huart);
    } else {
        HAL_UART_TxHalfCpltCallback(huart);
    }
#else
    HAL_UART_TxHalfCpltCallback(huart);
#endif
}

/**
  * @brief  DMA RX half-transfer callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
static void UART_DMARxHalfCplt(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UART_HandleTypeDef *huart = (HAL_UART_HandleTypeDef *)(hdma->Parent);

    if (huart == NULL) {
        return;
    }

    huart->RxEventType = HAL_UART_RXEVENT_HT;

    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        if (huart->RxEventCallback != NULL) {
            huart->RxEventCallback(huart);
        } else {
            HAL_UART_RxEventCallback(huart);
        }
#else
        HAL_UART_RxEventCallback(huart);
#endif
    } else {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        if (huart->RxHalfCpltCallback != NULL) {
            huart->RxHalfCpltCallback(huart);
        } else {
            HAL_UART_RxHalfCpltCallback(huart);
        }
#else
        HAL_UART_RxHalfCpltCallback(huart);
#endif
    }
}

/**
  * @brief  DMA transfer-error callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
static void UART_DMAError(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UART_HandleTypeDef *huart = (HAL_UART_HandleTypeDef *)(hdma->Parent);

    if (huart == NULL) {
        return;
    }

    huart->ErrorCode |= HAL_UART_ERROR_DMA;
    huart->gState = HAL_UART_STATE_READY;
    huart->RxState = HAL_UART_STATE_READY;

    LL_UART_DisableDMAReq_TX(huart->Instance);
    LL_UART_DisableDMAReq_RX(huart->Instance);

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (huart->ErrorCallback != NULL) {
        huart->ErrorCallback(huart);
    } else {
        HAL_UART_ErrorCallback(huart);
    }
#else
    HAL_UART_ErrorCallback(huart);
#endif
}

/**
  * @}
  */ /* UART_HAL_Private_Functions */

#endif /* HAL_UART_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */

/**
  * @}
  */ /* UART_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
