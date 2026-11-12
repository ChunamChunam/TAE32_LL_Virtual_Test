/**
  ******************************************************************************
  * @file    tae32g58xx_hal_can.c
  * @author  Tai-Action SD Team
  * @brief   CAN HAL module driver
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

/** @defgroup CAN_HAL CAN HAL
  * @brief    CAN HAL Module Driver
  * @{
  */

#if defined(CAN0) || defined(CAN1) 
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_CAN_MODULE_ENABLED) && (HAL_CAN_MODULE_ENABLED == 1)

#include <string.h>

/* Private Macros ------------------------------------------------------------*/
#define IS_CAN_OP_MODE(__VAL__)                             (((HAL_CAN_OpModeTypeDef)(__VAL__) == HAL_CAN_OP_MODE_NORMAL)          || \
                                                             ((HAL_CAN_OpModeTypeDef)(__VAL__) == HAL_CAN_OP_MODE_LISTEN_ONLY)     || \
                                                             ((HAL_CAN_OpModeTypeDef)(__VAL__) == HAL_CAN_OP_MODE_EXTERNAL_LOOP)   || \
                                                             ((HAL_CAN_OpModeTypeDef)(__VAL__) == HAL_CAN_OP_MODE_INTERNAL_LOOP)   )                  

#define IS_CAN_SS_SYNC_JUMP_WIDTH(__VAL__)                  (((uint32_t)(__VAL__) >= (uint32_t)1))   
#define IS_CAN_SS_TIME_SEG_1(__VAL__)                       (((uint32_t)(__VAL__) >= (uint32_t)1))   
#define IS_CAN_SS_TIME_SEG_2(__VAL__)                       (((uint32_t)(__VAL__) >= (uint32_t)1))   

#define IS_CAN_FS_SYNC_JUMP_WIDTH(__VAL__)                  (((uint32_t)(__VAL__) >= (uint32_t)1))   
#define IS_CAN_FS_TIME_SEG_1(__VAL__)                       (((uint32_t)(__VAL__) >= (uint32_t)1))   
#define IS_CAN_FS_TIME_SEG_2(__VAL__)                       (((uint32_t)(__VAL__) >= (uint32_t)1))   

/* Private Constants ---------------------------------------------------------*/
/** @defgroup CAN_HAL_Private_Constants CAN HAL Private Constants
  * @brief    CAN HAL Private Constants
  * @{
  */

/**
  * @brief  Default timeout value used by blocking CAN operations.
  * @note   The timeout is expressed in milliseconds and is used, for example,
  *         when waiting for a transmit buffer to become available or for the
  *         bus to leave the Bus-Off state.
  */
#define CAN_DEFAULT_TIMEOUT                 (25)

/**
  * @}
  */

/* Private Types -------------------------------------------------------------*/
/** @defgroup CAN_HAL_Private_Types CAN HAL Private Types
  * @brief    CAN HAL Private Types
  * @{
  */


/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup CAN_HAL_Private_Variables CAN HAL Private Variables
  * @brief    CAN HAL Private Variables
  * @{
  */

/**
  * @brief  Look-up table that maps a Data Length Code (DLC) to the corresponding
  *         payload length expressed in bytes.
  * @note   For CAN FD frames, DLC values above 8 correspond to the physical
  *         payload sizes mandated by the CAN FD protocol: 12, 16, 20, 24, 32,
  *         48 and 64 bytes. The DLC numbering follows the register encoding of
  *         the CAN controller.
  */
static const uint8_t DLC2LengthTable[HAL_CAN_DAT_LEN_CODE_NUMS] = {
    LL_CAN_DAT_LEN_BYTES_CODE_0,
    LL_CAN_DAT_LEN_BYTES_CODE_1,
    LL_CAN_DAT_LEN_BYTES_CODE_2,
    LL_CAN_DAT_LEN_BYTES_CODE_3,
    LL_CAN_DAT_LEN_BYTES_CODE_4,
    LL_CAN_DAT_LEN_BYTES_CODE_5,
    LL_CAN_DAT_LEN_BYTES_CODE_6,
    LL_CAN_DAT_LEN_BYTES_CODE_7,
    LL_CAN_DAT_LEN_BYTES_CODE_8,
    LL_CAN_DAT_LEN_BYTES_CODE_9,
    LL_CAN_DAT_LEN_BYTES_CODE_10,
    LL_CAN_DAT_LEN_BYTES_CODE_11,
    LL_CAN_DAT_LEN_BYTES_CODE_12,
    LL_CAN_DAT_LEN_BYTES_CODE_13,
    LL_CAN_DAT_LEN_BYTES_CODE_14,
    LL_CAN_DAT_LEN_BYTES_CODE_15
};

/**
  * @brief  Look-up table that maps a requested payload length in bytes to the
  *         closest supported Data Length Code (DLC).
  * @note   When the requested number of bytes is not exactly reachable in one
  *         of the CAN FD core lengths, the table selects the next larger DLC so
  *         that the frame can carry the requested data. This ensures that the
  *         DLC always provides enough physical payload space.
  */
static const uint8_t Length2DLCTable[HAL_CAN_DAT_LEN_RANGE] = {
    /* BYTE 0~8 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTE_0,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTE_1,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_2,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_3,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_4,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_5,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_6,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_7,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_8,

    /* BYTE 9~12 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_12,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_12,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_12,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_12,

    /* BYTE 13~16 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_16,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_16,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_16,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_16,

    /* BYTE 17~20 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_20,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_20,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_20,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_20,

    /* BYTE 21~24 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_24,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_24,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_24,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_24,

    /* BYTE 25~32 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_32,

    /* BYTE 33~40 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,

    /* BYTE 41~48 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_48,

    /* BYTE 49~56 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,

    /* BYTE 57~64 */
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
    (uint8_t)LL_CAN_DAT_LEN_CODE_BYTES_64,
};


/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @addtogroup CAN_HAL_Private_Functions
  * @{
  */

__STATIC_FORCEINLINE uint8_t CAN_DatLen_Get(HAL_CAN_HandleTypeDef *Handle, 
                                            HAL_CAN_DatLenCodeTypeDef Code);

__STATIC_FORCEINLINE void CAN_TxISR_PTB(HAL_CAN_HandleTypeDef *Handle);
__STATIC_FORCEINLINE void CAN_TxISR_STB(HAL_CAN_HandleTypeDef *Handle);
__STATIC_FORCEINLINE void CAN_RxISR_PRB(HAL_CAN_HandleTypeDef *Handle);
__STATIC_FORCEINLINE void CAN_RxISR_SRB(HAL_CAN_HandleTypeDef *Handle);
__STATIC_FORCEINLINE void CAN_GetTxEvtISR_ETB(HAL_CAN_HandleTypeDef *Handle);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AcceptFilRst(HAL_CAN_HandleTypeDef *Handle, 
                                                        HAL_CAN_AcceptFilSlotTypeDef Slot);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AcceptFilCfg(HAL_CAN_HandleTypeDef *Handle, 
                                                        const  HAL_CAN_FilterTypeDef *pCfg);

__STATIC_FORCEINLINE void CAN_ResetFilter(HAL_CAN_HandleTypeDef *Handle);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_GlobalFilRst(HAL_CAN_HandleTypeDef *Handle);
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_GlobalFilCfg(HAL_CAN_HandleTypeDef *Handle, 
                                                        const  HAL_CAN_GlobalFilCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_TimeoutCntrEnable(HAL_CAN_HandleTypeDef *Handle, 
                                                             HAL_CAN_TimeoutCntrTypeDef TimeoutCounter, 
                                                             HAL_CAN_EnableTypeDef IsEnable);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_TimeoutCntrCfg(HAL_CAN_HandleTypeDef *Handle, 
                                                          HAL_CAN_TimeoutCntrTypeDef TimeoutCounter, 
                                                          uint16_t TimeoutPeriod);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AlmostEmptyWarnLimitCfg(HAL_CAN_HandleTypeDef *Handle,
                                                                   HAL_CAN_MsgBufTypeDef BufferType, 
                                                                   HAL_CAN_BufAlmostEmptyLimitTypeDef WarningLimit);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AlmostFullWarnLimitCfg(HAL_CAN_HandleTypeDef *Handle,
                                                                  HAL_CAN_MsgBufTypeDef BufferType, 
                                                                  HAL_CAN_BufAlmostFullLimitTypeDef WarningLimit);

__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_OpModeCtrl(HAL_CAN_HandleTypeDef *Handle, 
                                                      HAL_CAN_OpModeTypeDef OpMode);

__STATIC_FORCEINLINE void CAN_PRB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_SRB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_PTB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_STB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_ETB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_ERR_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_TMS_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_TMO_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void CAN_HPM_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask);

/**
  * @}
  */

/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CAN_HAL_Exported_Functions CAN HAL Exported Functions
  * @brief    CAN HAL Exported Functions
  * @{
  */

/** @defgroup CAN_HAL_EF_Initialization CAN Init and DeInit Functions
  * @brief    CAN Init and DeInit Functions
  * @{
  */

/**
  * @brief  Initialize the CAN peripheral according to the parameters specified
  *         in @p pInit.
  * @note   The low-level hardware interface (clock, NVIC) is initialized
  *         first through HAL_CAN_MspInit(). Afterwards the CAN controller is
  *         placed in reset state to allow configuration of registers that are
  *         locked once the controller is active.
  * @param  Handle Pointer to a HAL_CAN_HandleTypeDef structure that contains
  *         the configuration information for the CAN module.
  * @param  CANx Pointer to the base address of the CAN peripheral.
  * @param  pInit Pointer to a HAL_CAN_InitTypeDef structure that contains the
  *         configuration information for the CAN peripheral.
  * @retval HAL_OK      - Initialization completed successfully.
  * @retval HAL_INVALID - At least one input parameter is invalid.
  */
HAL_StatusTypeDef HAL_CAN_Init(HAL_CAN_HandleTypeDef *Handle, 
                               CAN_TypeDef *CANx, 
                               const HAL_CAN_InitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(CANx));
    ASSERT_FUNC_PARAM(pInit != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_SS_SYNC_JUMP_WIDTH(pInit->NominalSyncJumpWidth));
    ASSERT_FUNC_PARAM(IS_CAN_SS_TIME_SEG_1(pInit->NominalTimeSeg1));
    ASSERT_FUNC_PARAM(IS_CAN_SS_TIME_SEG_2(pInit->NominalTimeSeg2));
    ASSERT_FUNC_PARAM(IS_CAN_FS_SYNC_JUMP_WIDTH(pInit->DataSyncJumpWidth));
    ASSERT_FUNC_PARAM(IS_CAN_FS_TIME_SEG_1(pInit->DataTimeSeg1));
    ASSERT_FUNC_PARAM(IS_CAN_FS_TIME_SEG_2(pInit->DataTimeSeg2));
    
    HAL_CAN_PARAM_CHECK({
        if (pInit == NULL) {
            return HAL_INVALID;
        }

        if (!pInit->NominalBaudrate) {
            return HAL_INVALID;
        }

        if ((pInit->FrameFormat == HAL_CAN_FRAME_FORMAT_FD_CAN) && (!pInit->DataBaudrate)) {
            return HAL_INVALID;
        }

        if ((!IS_CAN_SS_SYNC_JUMP_WIDTH(pInit->NominalSyncJumpWidth)) ||
            (!IS_CAN_SS_TIME_SEG_1(pInit->NominalTimeSeg1)) || (!IS_CAN_SS_TIME_SEG_2(pInit->NominalTimeSeg2))) {
            return HAL_INVALID;
        }

        if ((!IS_CAN_FS_SYNC_JUMP_WIDTH(pInit->DataSyncJumpWidth)) ||
            (!IS_CAN_FS_TIME_SEG_1(pInit->DataTimeSeg1)) || (!IS_CAN_FS_TIME_SEG_2(pInit->DataTimeSeg2))) {
            return HAL_INVALID;
        }
    });

    if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(CANx)) || (pInit == NULL)) {
        return HAL_INVALID;
    }

    /* Bind the peripheral instance to the handle. */
    Handle->Instance = CANx;

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Initialize the low-level hardware (clock, NVIC, etc.). */
    HAL_CAN_MspInit(Handle);

    /* Put the CAN core in reset state so that registers which are only
       writable during reset can be configured. */
    LL_CAN_SetReset(p_instance);

    /* Configure the nominal (slow speed) baudrate prescaler and bit timing.
       The bit time is divided into Sync segment, Time segment 1 and Time
       segment 2; the total bit time determines the slow-speed baudrate. */
    LL_CAN_SS_SetPrescaler(p_instance,
                            ( pInit->FunctionClockFrequency / ( pInit->NominalTimeSeg1 +  pInit->NominalTimeSeg2 + 3) /  pInit->NominalBaudrate - 1));
    LL_CAN_SS_SetBitTimingSeg1(p_instance,  pInit->NominalTimeSeg1);
    LL_CAN_SS_SetBitTimingSeg2(p_instance,  pInit->NominalTimeSeg2);
    LL_CAN_SS_SetSyncJumpWidth(p_instance,  pInit->NominalSyncJumpWidth);

    /* Configure the CAN FD extension if requested. */
    if (pInit->FrameFormat == HAL_CAN_FRAME_FORMAT_FD_CAN) {
        LL_CAN_EnableFD(p_instance);

        /* Select the ISO protocol adaptation mode for CAN FD. */
        HAL_FUNC_ALTER(pInit->ISOMode,  LL_CAN_EnableFD_ISO(p_instance), 
                                        LL_CAN_DisableFD_ISO(p_instance));
        
        /* Configure the data (fast speed) baudrate prescaler and bit timing.
           The data phase timing is used only for the payload and CRC segment
           of CAN FD frames when the Bit Rate Switch (BRS) option is active. */
        LL_CAN_FS_SetPrescaler(p_instance,
                                (pInit->FunctionClockFrequency / ( pInit->DataTimeSeg1 +  pInit->DataTimeSeg2 + 3) /  pInit->DataBaudrate - 1));
        LL_CAN_FS_SetBitTimingSeg1(p_instance,  pInit->DataTimeSeg1);
        LL_CAN_FS_SetBitTimingSeg2(p_instance,  pInit->DataTimeSeg2);
        LL_CAN_FS_SetSyncJumpWidth(p_instance,  pInit->DataSyncJumpWidth);

        /* Configure the protocol exception handling feature. */
        HAL_FUNC_ALTER(pInit->ProtocolException,    LL_CAN_ReleaseProtocolExceptionDetectDisable(p_instance), 
                                                    LL_CAN_AssertProtocolExceptionDetectDisable(p_instance));

    } else {
        /* Disable the CAN FD extension for classic CAN 2.0 operation. */
        LL_CAN_AssertProtocolExceptionDetectDisable(p_instance);
        LL_CAN_DisableFD(p_instance);
    }

    /* Leave the reset state so that the CAN core can synchronize to the bus. */
    LL_CAN_ClearReset(p_instance);

    /* Reset all acceptance filter slots to their default disabled state. */
    CAN_ResetFilter(Handle);

    /* Clear all pending interrupt flags to start from a clean state. */
    LL_CAN_ClearAllITPending(p_instance);

    /* Reset the software state of the handle. */
    Handle->ErrorCode             = HAL_CAN_ERROR_NONE;

    Handle->TxTsf.TxState         = HAL_CAN_TSF_STATE_BUSY;
    Handle->TxTsf.TxEvtState      = HAL_CAN_TSF_STATE_BUSY;
    Handle->TxTsf.TxCallback      = NULL;
    Handle->TxTsf.pTxEvtMsgInfo   = NULL;   
    Handle->TxTsf.TxEvtCallback   = NULL;

    Handle->RxTsfPRB.RxState      = HAL_CAN_TSF_STATE_BUSY;
    Handle->RxTsfPRB.pMsgInfo     = NULL;
    Handle->RxTsfPRB.pDatBuf      = NULL;
    Handle->RxTsfPRB.RxCallback   = NULL;

    Handle->RxTsfSRB.RxState      = HAL_CAN_TSF_STATE_BUSY;
    Handle->RxTsfSRB.pMsgInfo     = NULL;
    Handle->RxTsfSRB.pDatBuf      = NULL;
    Handle->RxTsfSRB.RxCallback   = NULL;

    Handle->State = HAL_CAN_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  De-initialize the CAN peripheral.
  * @note   This function disables the CAN interrupt lines, clears all pending
  *         interrupt flags, and calls HAL_CAN_MspDeInit() to release the
  *         low-level hardware resources.
  * @param  Handle CAN handle
  * @retval HAL_OK      - De-initialization completed successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The IRQ lookup failed.
  */
HAL_StatusTypeDef HAL_CAN_DeInit(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Disable all CAN interrupt sources and clear any pending flags. */
    LL_CAN_DisableAllInterrupts(p_instance);
    LL_CAN_ClearAllITPending(p_instance);

    /* Release the low-level hardware resources. */
    HAL_CAN_MspDeInit(Handle);

    Handle->State = HAL_CAN_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Abort all pending transmit operations on the CAN peripheral.
  * @note   This function disables the transmit interrupts, clears their pending
  *         flags, asserts the abort requests for both the PTB and STB transmit
  *         buffers, and finally resets the software transmit state.
  * @param  Handle CAN handle
  * @retval HAL_OK      - Abort request successfully issued.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_CAN_TxAbort(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    /* Retrieve the CAN peripheral base address. */
    CAN_TypeDef *p_instance = Handle->Instance;
	
    /* Disable the transmit-related interrupts and clear their pending flags. */
    LL_CAN_DisableIT(p_instance, LL_CAN_INTREN_TX_IT_EN_MSK);
    LL_CAN_ClearFlag(p_instance, LL_CAN_INTRST_TX_IT_FLAG_MSK);
	
    /* Request an abort of any frame waiting in the PTB and STB transmit buffers. */
    LL_CAN_STB_SetTransmissionAbort(p_instance);
    LL_CAN_PTB_SetTransmissionAbort(p_instance);

    /* Reset the software transmit state to idle and clear the callback pointers. */
    Handle->TxTsf.TxCallback      = NULL;
    Handle->TxTsf.TxEvtCallback   = NULL;
    Handle->TxTsf.pTxEvtMsgInfo   = NULL;
    Handle->TxTsf.TxState         = HAL_CAN_TSF_STATE_IDLE;
    Handle->TxTsf.TxEvtState      = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Abort all pending receive operations on the CAN peripheral.
  * @note   This function disables the receive interrupts, clears their pending
  *         flags, and resets the software receive state for both the PRB and
  *         the SRB.
  * @param  Handle CAN handle
  * @retval HAL_OK      - Receive abort successfully issued.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_CAN_RxAbort(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    /* Retrieve the CAN peripheral base address. */
    CAN_TypeDef *p_instance = Handle->Instance;
	
    /* Disable the receive-related interrupts and clear their pending flags. */
    LL_CAN_DisableIT(p_instance, LL_CAN_INTREN_RX_IT_EN_MSK);
    LL_CAN_ClearFlag(p_instance, LL_CAN_INTRST_RX_IT_FLAG_MSK);
	
    /* Reset the PRB software receive state. */
    Handle->RxTsfPRB.RxCallback   = NULL;
    Handle->RxTsfPRB.pMsgInfo     = NULL;    
    Handle->RxTsfPRB.pDatBuf      = NULL;    
    Handle->RxTsfPRB.RxState      = HAL_CAN_TSF_STATE_IDLE;        

    /* Reset the SRB software receive state. */
    Handle->RxTsfSRB.RxCallback   = NULL;   
    Handle->RxTsfSRB.pMsgInfo     = NULL;
    Handle->RxTsfSRB.pDatBuf      = NULL;
    Handle->RxTsfSRB.RxState      = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Initialize the CAN MSP (MCU Support Package).
  * @note   This weak function is intended to be overridden by the application.
  *         It should configure the peripheral clock, GPIO pins, and NVIC
  *         settings required by the CAN peripheral.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_MspInit(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_MspInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the CAN MSP.
  * @note   This weak function is intended to be overridden by the application.
  *         It should disable the CAN clocks, release the GPIO pins and remove
  *         the NVIC settings.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_MspDeInit(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Initialize the CAN IO (input/output) interface.
  * @note   This weak function is intended to be overridden by the application.
  *         It may be used to configure multiplexed pins or external transceiver
  *         control lines (such as a standby pin for a CAN transceiver).
  * @param  CANx Pointer to the base address of the CAN peripheral.
  * @retval None
  */
__WEAK void HAL_CAN_IoInit(CAN_TypeDef *CANx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(CANx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the CAN IO interface.
  * @note   This weak function is intended to be overridden by the application.
  *         It should release any resources acquired by HAL_CAN_IoInit().
  * @param  CANx Pointer to the base address of the CAN peripheral.
  * @retval None
  */
__WEAK void HAL_CAN_IoDeInit(CAN_TypeDef *CANx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(CANx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_IoDeInit could be implemented in the user file
     */
}

/**
  * @brief  Register a user callback for a specific CAN interrupt event.
  * @note   The callback can only be registered when the CAN handle is in the
  *         READY state (i.e. not active and no transfer is ongoing).
  * @param  Handle CAN handle
  * @param  CallbackID ID of the callback to be registered.
  * @param  pCallback Pointer to the callback function.
  * @retval HAL_OK      - Callback registered successfully.
  * @retval HAL_INVALID - Callback pointer or callback ID is invalid.
  * @retval HAL_BUSY    - The CAN is not in a state that allows callback
  *                       registration.
  */
HAL_StatusTypeDef HAL_CAN_RegisterCallback(HAL_CAN_HandleTypeDef *Handle, 
                                           HAL_CAN_UsrCbIdTypeDef CallbackID, 
                                           HAL_CAN_IRQCallback pCallback)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    
    /* Check the callback pointer validity. */
    if (pCallback == NULL) {
        return HAL_INVALID;
    }

    /* Register the user callback according to its identifier. */
    switch (CallbackID) {
        case HAL_CAN_PTB_TX_CPLT_CB_ID:
            if (Handle->TxTsf.TxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.TxCpltPTBCallback = pCallback;
            break;

        case HAL_CAN_STB_TX_CPLT_CB_ID:
            if (Handle->TxTsf.TxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.TxCpltSTBCallback = pCallback;
            break;

        case HAL_CAN_PRB_RX_CPLT_CB_ID:
            if (Handle->RxTsfPRB.RxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.RxCpltPRBCallback = pCallback;
            break;

        case HAL_CAN_SRB_RX_CPLT_CB_ID:
            if (Handle->RxTsfSRB.RxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.RxCpltSRBCallback = pCallback;
            break;

        case HAL_CAN_ETB_EVT_CPLT_CB_ID:
            if (Handle->TxTsf.TxEvtState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.TxEvtCpltCallback = pCallback;
            break;

        case HAL_CAN_ERROR_CB_ID:
            if (Handle->State & HAL_CAN_STATE_ACTIVE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.ErrorCallback = pCallback;
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Un-register a user callback.
  * @note   The callback can only be unregistered when the CAN handle is in the
  *         READY state (i.e. not active and no transfer is ongoing).
  * @param  Handle CAN handle
  * @param  CallbackID ID of the callback to be unregistered.
  * @retval HAL_OK      - Callback unregistered successfully.
  * @retval HAL_INVALID - Callback ID is invalid.
  * @retval HAL_BUSY    - The CAN is not in a state that allows callback
  *                       unregistration.
  */
HAL_StatusTypeDef HAL_CAN_UnRegisterCallback(HAL_CAN_HandleTypeDef *Handle, 
                                             HAL_CAN_UsrCbIdTypeDef CallbackID)
{
    ASSERT_FUNC_PARAM(Handle != NULL);

    /* Un-register the user callback according to its identifier. */
    switch (CallbackID) {
        case HAL_CAN_PTB_TX_CPLT_CB_ID:
            if (Handle->TxTsf.TxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.TxCpltPTBCallback = NULL;
            break;

        case HAL_CAN_STB_TX_CPLT_CB_ID:
            if (Handle->TxTsf.TxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.TxCpltSTBCallback = NULL;
            break;

        case HAL_CAN_PRB_RX_CPLT_CB_ID:
            if (Handle->RxTsfPRB.RxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.RxCpltPRBCallback = NULL;
            break;

        case HAL_CAN_SRB_RX_CPLT_CB_ID:
            if (Handle->RxTsfSRB.RxState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.RxCpltSRBCallback = NULL;
            break;

        case HAL_CAN_ETB_EVT_CPLT_CB_ID:
            if (Handle->TxTsf.TxEvtState != HAL_CAN_TSF_STATE_IDLE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.TxEvtCpltCallback = NULL;
            break;

        case HAL_CAN_ERROR_CB_ID:
            if (Handle->State & HAL_CAN_STATE_ACTIVE) {
                return HAL_BUSY;
            }

            Handle->UserCallback.ErrorCallback = NULL;
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @}
  */ /* CAN_HAL_EF_Initialization */

/** @defgroup CAN_HAL_EF_Configuration CAN Configuration Functions
  * @brief    CAN Configuration Functions
  * @{
  */

/**
  * @brief  Switch the CAN peripheral operating mode.
  * @note   This function is used to change the CAN operating mode (normal, listen-only,
  *          external loopback, internal loopback). It first checks that the CAN state and
  *          the Tx/Rx transfer states are idle. If a transfer is ongoing, it returns HAL_BUSY.
  * @param  Handle CAN handle
  * @param  OpMode CAN operating mode to configure
  * @retval HAL_OK      - Operating mode changed successfully.
  * @retval HAL_BUSY    - A transmit or receive transfer is ongoing, mode cannot be changed.
  * @retval HAL_ERROR   - Invalid CAN state (not in READY or ACTIVE state).
  * @retval HAL_INVALID - Parameter error (invalid handle, instance, or operating mode).
  */
HAL_StatusTypeDef HAL_CAN_OperatingModeCtrl(HAL_CAN_HandleTypeDef *Handle, 
                                            HAL_CAN_OpModeTypeDef OpMode)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_CAN_OP_MODE(OpMode));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance)) || (!IS_CAN_OP_MODE(OpMode))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);

    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        return CAN_OpModeCtrl(Handle, OpMode);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure one acceptance filter slot.
  * @note   The filter must be configured when the CAN is in READY or ACTIVE
  *         state. This function only writes the filter registers; it does not
  *         affect the receive buffer contents.
  * @param  Handle CAN handle
  * @param  pCfg Pointer to a HAL_CAN_FilterTypeDef structure containing the
  *         filter configuration.
  * @retval HAL_OK      - Filter configured successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in a configurable state.
  */
HAL_StatusTypeDef HAL_CAN_ConfigFilter(HAL_CAN_HandleTypeDef *Handle, 
                                       const HAL_CAN_FilterTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);
    
    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        return CAN_AcceptFilCfg(Handle, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Reset all acceptance filter slots to their default disabled state.
  * @param  Handle CAN handle
  * @retval HAL_OK      - All filters were reset.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_CAN_ResetFilter(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    /* Reset every acceptance filter slot one by one. */
    CAN_ResetFilter(Handle);

    return HAL_OK;
}

/**
  * @brief  Configure the global filter behavior without resetting the handle or
  *         the bus state.
  * @note   This interface can only be called when the CAN bus is idle.
  * @param  Handle CAN handle
  * @param  pCfg Pointer to a HAL_CAN_GlobalFilCfgTypeDef structure containing
  *         the global filter settings.
  * @retval HAL_OK      - Global filter configured successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in a configurable state.
  */
HAL_StatusTypeDef HAL_CAN_ConfigGlobalFilter(HAL_CAN_HandleTypeDef *Handle, 
                                             const HAL_CAN_GlobalFilCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);
    
    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        return CAN_GlobalFilCfg(Handle, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Reset the global filter configuration to its default value.
  * @param  Handle CAN handle
  * @retval HAL_OK      - Global filter was reset.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_CAN_ResetGlobalFilter(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    /* Restore the default global filter settings. */
    return CAN_GlobalFilRst(Handle);
}

/**
  * @brief  Configure the timestamp counter prescaler.
  * @note   The CAN handle must be in READY state; the CAN must not be active.
  * @param  Handle CAN handle
  * @param  TimestampPrescaler Prescaler value for the timestamp counter.
  * @retval HAL_OK      - Prescaler configured successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY state.
  */
HAL_StatusTypeDef HAL_CAN_ConfigTimestampCounter(HAL_CAN_HandleTypeDef *Handle, 
                                                 HAL_CAN_TimestampPrescalerTypeDef TimestampPrescaler)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY);

    if (Handle->State & HAL_CAN_STATE_READY) {
        /* Write the timestamp prescaler value. */
        LL_CAN_SetTimestampPrescaler(Handle->Instance, TimestampPrescaler);

        return HAL_OK;
    } else {
        /* The CAN is not in the expected configuration state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Enable the timestamp counter and select its timebase.
  * @param  Handle CAN handle
  * @param  Timebase Timebase source for the timestamp counter.
  * @retval HAL_OK      - Timestamp counter enabled.
  * @retval HAL_INVALID - A parameter is invalid or the timebase is "close".
  * @retval HAL_ERROR   - The CAN is not in READY state.
  */
HAL_StatusTypeDef HAL_CAN_EnableTimestampCounter(HAL_CAN_HandleTypeDef *Handle, 
                                                 HAL_CAN_TimestampTimebaseTypeDef Timebase)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY);

    if (Timebase == HAL_CAN_TIMESTAMP_TIMEBASE_CLOSE) {
        return HAL_INVALID;
    }

    if (Handle->State & HAL_CAN_STATE_READY) {
        /* Select the timestamp counter timebase. */
        LL_CAN_SetTimestampTimebase(Handle->Instance, Timebase);

        return HAL_OK;
    } else {
        /* The CAN is not in the expected configuration state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Disable the timestamp counter.
  * @param  Handle CAN handle
  * @retval HAL_OK      - Timestamp counter disabled.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY or ACTIVE state.
  */
HAL_StatusTypeDef HAL_CAN_DisableTimestampCounter(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);
    
    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        /* Disable the timestamp counter by setting the timebase to "close". */
        LL_CAN_SetTimestampTimebase(Handle->Instance, LL_CAN_TIMESTAMP_TIMEBASE_CLOSE);
        return HAL_OK;
    } else {
        /* The CAN is not in a configurable state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the period of one timeout counter.
  * @param  Handle CAN handle
  * @param  TimeoutCounter Selection of the timeout counter (PRB, SRB, ETB, or
  *         continuous).
  * @param  TimeoutPeriod Start value of the timeout down-counter.
  * @retval HAL_OK      - Timeout counter configured.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY state.
  */
HAL_StatusTypeDef HAL_CAN_ConfigTimeoutCounter(HAL_CAN_HandleTypeDef *Handle, 
                                               HAL_CAN_TimeoutCntrTypeDef TimeoutCounter, 
                                               uint16_t TimeoutPeriod)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY);

    if (Handle->State & HAL_CAN_STATE_READY) {
        return CAN_TimeoutCntrCfg(Handle, TimeoutCounter, TimeoutPeriod);
    } else {
        /* The CAN is not in the expected configuration state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Enable one timeout counter.
  * @param  Handle CAN handle
  * @param  TimeoutCounter Selection of the timeout counter.
  * @retval HAL_OK      - Timeout counter enabled.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY or ACTIVE state.
  */
HAL_StatusTypeDef HAL_CAN_EnableTimeoutCounter(HAL_CAN_HandleTypeDef *Handle, 
                                               HAL_CAN_TimeoutCntrTypeDef TimeoutCounter)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);
    
    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        /* Enable the selected timeout counter. */
        return CAN_TimeoutCntrEnable(Handle, TimeoutCounter, HAL_CAN_FUNC_ENABLE);
    } else {
        /* The CAN is not in a configurable state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Disable one timeout counter.
  * @param  Handle CAN handle
  * @param  TimeoutCounter Selection of the timeout counter.
  * @retval HAL_OK      - Timeout counter disabled.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY or ACTIVE state.
  */
HAL_StatusTypeDef HAL_CAN_DisableTimeoutCounter(HAL_CAN_HandleTypeDef *Handle, 
                                                HAL_CAN_TimeoutCntrTypeDef TimeoutCounter)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);
    
    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        /* Disable the selected timeout counter. */
        return CAN_TimeoutCntrEnable(Handle, TimeoutCounter, HAL_CAN_FUNC_DISABLE);
    } else {
        /* The CAN is not in a configurable state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure automatic retransmission for the PTB transmit buffer.
  * @note   When retransmission is disabled, the PTB operates in single-shot
  *         mode: a frame is transmitted only once and no retry is attempted
  *         after an error or arbitration loss.
  * @param  Handle CAN handle
  * @param  IsEnable Set to HAL_CAN_FUNC_ENABLE to enable automatic
  *         retransmission, or HAL_CAN_FUNC_DISABLE to enable single-shot mode.
  * @retval HAL_OK      - Configuration performed.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY state.
  */
HAL_StatusTypeDef HAL_CAN_PTBAutoRetransmissionConfig(HAL_CAN_HandleTypeDef *Handle, 
                                                      HAL_CAN_EnableTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY);
    
    if (Handle->State & HAL_CAN_STATE_READY) {
        /* Enable retransmission by disabling single-shot mode, or vice versa. */
        HAL_FUNC_ALTER(IsEnable,    LL_CAN_PTB_DisableSingleShotMode(Handle->Instance), 
                                    LL_CAN_PTB_EnableSingleShotMode(Handle->Instance));
        return HAL_OK;
    } else {
        /* The CAN is not in the expected configuration state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure automatic retransmission for the STB transmit buffer.
  * @note   When retransmission is disabled, the STB operates in single-shot
  *         mode: a frame is transmitted only once and no retry is attempted
  *         after an error or arbitration loss.
  * @param  Handle CAN handle
  * @param  IsEnable Set to HAL_CAN_FUNC_ENABLE to enable automatic
  *         retransmission, or HAL_CAN_FUNC_DISABLE to enable single-shot mode.
  * @retval HAL_OK      - Configuration performed.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY state.
  */
HAL_StatusTypeDef HAL_CAN_STBAutoRetransmissionConfig(HAL_CAN_HandleTypeDef *Handle, 
                                                      HAL_CAN_EnableTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY);
    
    if (Handle->State & HAL_CAN_STATE_READY) {
        /* Enable retransmission by disabling single-shot mode, or vice versa. */
        HAL_FUNC_ALTER(IsEnable,    LL_CAN_STB_DisableSingleShotMode(Handle->Instance), 
                                    LL_CAN_STB_EnableSingleShotMode(Handle->Instance));
        return HAL_OK;
    } else {
        /* The CAN is not in the expected configuration state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the extended ID mask used by the acceptance filters.
  * @param  Handle CAN handle
  * @param  Mask Extended ID mask value.
  *         This parameter must be a number between 0 and 0x1FFFFFFF.
  * @retval HAL_OK      - Mask configured.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY state.
  */
HAL_StatusTypeDef HAL_CAN_ConfigExtendedIdMask(HAL_CAN_HandleTypeDef *Handle, 
                                               uint32_t Mask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY);
    
    if (Handle->State & HAL_CAN_STATE_READY) {
        /* Update the extended ID mask register. */
        LL_CAN_SetExtendedIdMask(Handle->Instance, Mask);
        return HAL_OK;
    } else {
        /* The CAN is not in the expected configuration state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the "almost empty" warning limit of a transmit buffer.
  * @note   The warning limit indicates the fill level below which an empty
  *         warning is generated for the selected buffer.
  * @param  Handle CAN handle
  * @param  BufferType Message buffer type (currently only STB is supported).
  * @param  WarningLimit Almost-empty warning limit value.
  * @retval HAL_OK      - Limit configured.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY or ACTIVE state.
  */
HAL_StatusTypeDef HAL_CAN_AlmostEmptyWarnLimitConfig(HAL_CAN_HandleTypeDef *Handle,
                                                     HAL_CAN_MsgBufTypeDef BufferType, 
                                                     HAL_CAN_BufAlmostEmptyLimitTypeDef WarningLimit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);
    
    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        /* Configure the almost-empty warning limit. */
        CAN_AlmostEmptyWarnLimitCfg(Handle, BufferType, WarningLimit);
        return HAL_OK;
    } else {
        /* The CAN is not in a configurable state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the "almost full" warning limit of a receive buffer.
  * @note   The warning limit indicates the fill level above which a full
  *         warning is generated for the selected buffer.
  * @param  Handle CAN handle
  * @param  BufferType Message buffer type (PRB, SRB, or ETB).
  * @param  WarningLimit Almost-full warning limit value.
  * @retval HAL_OK      - Limit configured.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY or ACTIVE state.
  */
HAL_StatusTypeDef HAL_CAN_AlmostFullWarnLimitConfig(HAL_CAN_HandleTypeDef *Handle,
                                                    HAL_CAN_MsgBufTypeDef BufferType, 
                                                    HAL_CAN_BufAlmostFullLimitTypeDef WarningLimit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE);
    
    if (Handle->State & (HAL_CAN_STATE_READY | HAL_CAN_STATE_ACTIVE)) {
        /* Configure the almost-full warning limit. */
        CAN_AlmostFullWarnLimitCfg(Handle, BufferType, WarningLimit);
        return HAL_OK;
    } else {
        /* The CAN is not in a configurable state. */
        return HAL_ERROR;
    }
}

/**
  * @brief  Assign interrupt groups to either interrupt line 0 or line 1.
  * @param  Handle CAN handle
  * @param  ITList Bitmask of the interrupt groups to be assigned.
  * @param  InterruptLine Target interrupt line (0 or 1).
  * @retval HAL_OK      - Interrupt lines configured.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The CAN is not in READY state.
  */
HAL_StatusTypeDef HAL_CAN_ConfigInterruptLines(HAL_CAN_HandleTypeDef *Handle, 
                                               HAL_CAN_ITLineMskTypeDef ITList, 
                                               HAL_CAN_ITLineTypeDef InterruptLine)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    HAL_CAN_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_CAN_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_READY);
    
    if (Handle->State & HAL_CAN_STATE_READY) {
        if (InterruptLine == HAL_CAN_INTERRUPT_LINE_0) {
            /* Clear the corresponding bits to route the group to line 0. */
            LL_CAN_IntLine_Clr(Handle->Instance, ITList);
        } else if (InterruptLine == HAL_CAN_INTERRUPT_LINE_1) {
            /* Set the corresponding bits to route the group to line 1. */
            LL_CAN_SetInterruptLines(Handle->Instance, ITList);
        } else {
            return HAL_INVALID;
        }

        return HAL_OK;
    } else {
        /* The CAN is not in the expected configuration state. */
        return HAL_ERROR;
    }
}

/**
  * @}
  */ /* CAN_HAL_EF_Configuration */

/** @defgroup CAN_HAL_EF_Operation CAN Operation Functions
  * @brief    CAN Operation Functions
  * @{
  */

/**
  * @brief  Start the CAN peripheral and place it in the ACTIVE state.
  * @note   Before transitioning to the ACTIVE state, the function waits for
  *         the CAN to leave the Bus-Off state (if it was in Bus-Off). Once
  *         this completes, the CAN reset flag is cleared so that normal
  *         communication can begin.
  * @param  Handle CAN handle
  * @retval HAL_OK      - CAN started successfully.
  * @retval HAL_ERROR   - The CAN is not in the READY state.
  * @retval HAL_TIMEOUT - The CAN did not leave the Bus-Off state within the
  *                       configured timeout period.
  */
HAL_StatusTypeDef HAL_CAN_Start(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    if (Handle->State != HAL_CAN_STATE_READY) {
        return HAL_ERROR;
    }

    CAN_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart = HAL_GetTick();

    /* Wait until the CAN leaves the Bus-Off state, if it is currently off. */
    while (LL_CAN_IsBusOffState(p_instance) == LL_CAN_BUS_STATE_BUSOFF) {
        if ((HAL_GetTick() - tickstart) > CAN_DEFAULT_TIMEOUT) {
            Handle->State = HAL_CAN_STATE_ERROR;
            return HAL_TIMEOUT;
        }
    }

    /* Clear the error code and initialize the software states to ACTIVE/IDLE. */
    Handle->ErrorCode           = HAL_CAN_ERROR_NONE;
    Handle->State               = HAL_CAN_STATE_ACTIVE;
    Handle->TxTsf.TxState       = HAL_CAN_TSF_STATE_IDLE;
    Handle->TxTsf.TxEvtState    = HAL_CAN_TSF_STATE_IDLE;
    Handle->RxTsfPRB.RxState    = HAL_CAN_TSF_STATE_IDLE;
    Handle->RxTsfSRB.RxState    = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Stop the CAN peripheral and return it to the READY state.
  * @note   This function places the CAN in the reset state, disables all
  *         interrupt sources, aborts any pending transmission, and clears all
  *         pending interrupt flags. The software transfer states are then
  *         reset so that a subsequent HAL_CAN_Start() can reinitialize
  *         communication from a clean state.
  * @param  Handle CAN handle
  * @retval HAL_OK      - CAN stopped successfully.
  * @retval HAL_ERROR   - The CAN is not in the ACTIVE state.
  * @retval HAL_TIMEOUT - The CAN did not leave the Bus-Off state within the
  *                       configured timeout period (only possible if the
  *                       peripheral was already in the reset state).
  */
HAL_StatusTypeDef HAL_CAN_Stop(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    if (Handle->State != HAL_CAN_STATE_ACTIVE) {
        return HAL_ERROR;
    }

    CAN_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart = HAL_GetTick();

    /* Put the CAN core into the reset state. */
    if (LL_CAN_GetResetState(p_instance) == LL_CAN_RST_STATE_NOT_RESET) {
        LL_CAN_SetReset(p_instance);     
    } else {
        /* If the core is already in the reset state, wait for Bus-Off to clear. */
        while (LL_CAN_IsBusOffState(p_instance) == LL_CAN_BUS_STATE_BUSOFF) {
            if ((HAL_GetTick() - tickstart) > CAN_DEFAULT_TIMEOUT) {
                Handle->State = HAL_CAN_STATE_ERROR;
                return HAL_TIMEOUT;
            }
        }
    }

    /* Disable all CAN interrupt sources. */
    LL_CAN_DisableAllInterrupts(p_instance);
    
    /* Abort any frames still pending in the PTB and STB transmit buffers. */
    LL_CAN_STB_SetTransmissionAbort(p_instance);
    LL_CAN_PTB_SetTransmissionAbort(p_instance);

    /* Clear all pending interrupt flags. */
    LL_CAN_ClearAllITPending(p_instance);

    /* Reset the transmit software state (PTB/STB/ETB). */
    Handle->TxTsf.TxCallback      = NULL;
    Handle->TxTsf.TxEvtCallback   = NULL;
    Handle->TxTsf.pTxEvtMsgInfo   = NULL;
    Handle->TxTsf.TxState         = HAL_CAN_TSF_STATE_IDLE;

    /* Reset the PRB receive software state. */
    Handle->RxTsfPRB.RxCallback   = NULL;
    Handle->RxTsfPRB.pMsgInfo     = NULL;    
    Handle->RxTsfPRB.pDatBuf      = NULL;    
    Handle->RxTsfPRB.RxState      = HAL_CAN_TSF_STATE_IDLE;        

    /* Reset the SRB receive software state. */
    Handle->RxTsfSRB.RxCallback   = NULL;   
    Handle->RxTsfSRB.pMsgInfo     = NULL;
    Handle->RxTsfSRB.pDatBuf      = NULL;
    Handle->RxTsfSRB.RxState      = HAL_CAN_TSF_STATE_IDLE;

    /* Move the CAN handle back to the READY state. */
    Handle->State = HAL_CAN_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Convert a Data Length Code (DLC) into the corresponding payload
  *         length expressed in bytes.
  * @note   The conversion uses the internal lookup table which covers both
  *         CAN 2.0 and CAN FD DLC values. If the CAN FD extension is disabled,
  *         the resulting length is clamped to 8 bytes.
  * @param  Handle CAN handle
  * @param  DatLenCode Data Length Code to be converted.
  * @retval The payload length in bytes, or 0 if @p DatLenCode is out of range.
  */
uint8_t HAL_CAN_DataCode2Length(HAL_CAN_HandleTypeDef *Handle, 
                                uint8_t DatLenCode)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(DatLenCode < HAL_CAN_DAT_LEN_CODE_NUMS);

    HAL_CAN_PARAM_CHECK({
        if (DatLenCode >= HAL_CAN_DAT_LEN_CODE_NUMS) {
            return 0;
        }    
    });

    /* Delegate the conversion to the internal helper. */
    return CAN_DatLen_Get(Handle, DatLenCode);
}

/**
  * @brief  Convert a requested payload length in bytes into the closest
  *         supported Data Length Code (DLC).
  * @note   If the requested length does not exactly match one of the CAN FD
  *         physical lengths (12, 16, 20, 24, 32, 48, 64), the next larger
  *         DLC is selected to guarantee that the frame can carry all data.
  *         The valid range of @p DatLen depends on whether the CAN FD mode is
  *         enabled in the peripheral.
  * @param  Handle CAN handle
  * @param  DatLen Desired payload length in bytes (0 to 64).
  * @retval The corresponding Data Length Code. If the length is not valid for
  *         the current mode, HAL_CAN_DAT_LEN_CODE_BYTE_0 is returned.
  */
HAL_CAN_DatLenCodeTypeDef HAL_CAN_DataLength2Code(HAL_CAN_HandleTypeDef *Handle, 
                                                  uint8_t DatLen)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(DatLen <= HAL_CAN_FD_DAT_LEN_MAX);

    /* Determine whether the CAN FD mode is currently enabled. */
    const uint32_t is_fd = LL_CAN_IsFDEnabled(Handle->Instance);

    /* Validate the requested length against the current mode. */
    if (((is_fd)  && (DatLen <= HAL_CAN_FD_DAT_LEN_MAX)) ||
        ((!is_fd) && (DatLen <= HAL_CAN_20_DAT_LEN_MAX))) {
        /* Use the modulo of the table size to safely index the lookup table. */
        return Length2DLCTable[DatLen % HAL_CAN_DAT_LEN_RANGE];
    } else {
        return HAL_CAN_DAT_LEN_CODE_BYTE_0;
    }
}

/**
  * @brief  Retrieve the current protocol status of the CAN peripheral.
  * @note   Reading the protocol status register may clear some status flags
  *         (such as the ESI flag and the last error code), so this function
  *         should be called by the user to obtain the status after a
  *         reception or error event. The ESI flag is only valid for CAN FD
  *         frames and is kept at reset for CAN 2.0 frames.
  * @param  Handle CAN handle
  * @param  Status Pointer to a HAL_CAN_ProtocolStatusTypeDef structure that
  *         will be filled with the current protocol information.
  * @retval HAL_OK      - Protocol status read successfully.
  * @retval HAL_INVALID - The @p Status pointer is NULL.
  */
HAL_StatusTypeDef HAL_CAN_GetProtocolStatus(HAL_CAN_HandleTypeDef *Handle, 
                                            HAL_CAN_ProtocolStatusTypeDef *Status)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Status != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((Status == NULL)) {
            return HAL_INVALID;
        }        
    });

    uint32_t sta_msk_tmp;
    uint32_t fd_frm_type_msk;
    uint32_t prot_sta;

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Read the last error code and the protocol status register. */
    Status->LastErrorCode = (HAL_CAN_ErrStatusTypeDef)LL_CAN_GetErrorCode(p_instance);
    sta_msk_tmp = LL_CAN_GetAllITPending(p_instance) & (LL_CAN_INTRST_EWARN_SP | LL_CAN_INTRST_EPASS_SP);
    prot_sta = LL_CAN_ReadProtocolStatusRegister(p_instance);    

    /* Check the Bus-Off state. */
    if (LL_CAN_IsBusOffState(p_instance)) {
        Status->BusOff = HAL_CAN_FLAG_SET;
    } else {
        Status->BusOff = HAL_CAN_FLAG_RESET;
    }

    /* Extract the receive frame store mode. */
    Status->RxFrameStore = (HAL_CAN_FrmStoreModeTypeDef)LL_CAN_ExtractRxFrameStoreMode(prot_sta);

    /* Check the Error Passive state. */
    if (sta_msk_tmp & LL_CAN_INTRST_EPASS_SP) {
        Status->ErrorPassive = HAL_CAN_FLAG_SET;
    } else {
        Status->ErrorPassive = HAL_CAN_FLAG_RESET;
    }
    
    /* Check the Error Warning state. */
    if (sta_msk_tmp & LL_CAN_INTRST_EWARN_SP) {
        Status->Warning = HAL_CAN_FLAG_SET;
    } else {
        Status->Warning = HAL_CAN_FLAG_RESET;
    }

    /* Extract the data phase last error code. */
    Status->DataLastErrorCode = (HAL_CAN_DatFieldErrTypeDef)LL_CAN_ExtractDataErrorType(prot_sta);

    /* Extract the current node activity state. */
    Status->Activity = (HAL_CAN_NodeStaTypeDef)LL_CAN_ExtractNodeStatus(prot_sta);

    /* Read the CAN FD receive frame status field. */
    sta_msk_tmp = LL_CAN_ExtractRxFDDatFrameType(prot_sta);
    
    /* Check for a protocol exception event. */
    if (sta_msk_tmp & LL_CAN_RX_FD_STATUS_DATA_FRAME_PROT_MISMATCH) {
        Status->ProtocolException = HAL_CAN_FLAG_SET;
    } else {
        Status->ProtocolException = HAL_CAN_FLAG_RESET; 
    }  

    /* Isolate the normal frame-type status bits from the FD status field. */
    fd_frm_type_msk = sta_msk_tmp & (LL_CAN_RX_FD_STATUS_DATA_FRAME | LL_CAN_RX_FD_STATUS_ACC_FRAME | LL_CAN_RX_FD_STATUS_EXT_FRAME);

    /* FDF flag: indicates a CAN FD frame was received. */
    if (fd_frm_type_msk & LL_CAN_RX_FD_STATUS_DATA_FRAME) {
        Status->RxFDFflag = HAL_CAN_FLAG_SET;
    } else {
        Status->RxFDFflag = HAL_CAN_FLAG_RESET;
    } 

    /* BRS flag: indicates the received frame used the data phase bit rate. */
    if (fd_frm_type_msk & LL_CAN_RX_FD_STATUS_ACC_FRAME) {
        Status->RxBRSflag = HAL_CAN_FLAG_SET;
    } else {
        Status->RxBRSflag = HAL_CAN_FLAG_RESET;
    }

    /* IDE flag: indicates an extended identifier was used in the received frame. */
    if (fd_frm_type_msk & LL_CAN_RX_FD_STATUS_EXT_FRAME) {
        Status->RxIDEflag = HAL_CAN_FLAG_SET;
    } else {
        Status->RxIDEflag = HAL_CAN_FLAG_RESET;
    }

    return HAL_OK;
}

/**
  * @brief  Retrieve the status of the last high-priority message matched by
  *         the acceptance filter.
  * @note   The high-priority message status provides information about the
  *         filter that matched the highest-priority message, along with the
  *         frame format and the destination receive buffer.
  * @param  Handle CAN handle
  * @param  Status Pointer to a HAL_CAN_HpMsgStatusTypeDef structure that
  *         will be filled with the high-priority message information.
  * @retval HAL_OK      - High-priority message status read successfully.
  * @retval HAL_INVALID - The @p Status pointer is NULL.
  */
HAL_StatusTypeDef HAL_CAN_GetHighPriorityMessageStatus(HAL_CAN_HandleTypeDef *Handle, 
                                                       HAL_CAN_HpMsgStatusTypeDef *Status)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Status != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((Status == NULL)) {
            return HAL_INVALID;
        }        
    });

    /* Read the high-priority message status register. */
    uint32_t msg_sta = LL_CAN_ReadPriorityMessageStatus(Handle->Instance);

    /* Extract the IDE flag to determine whether the message was standard
       or extended. */
    if (LL_CAN_ExtractPriorityMessageIDEStatus(msg_sta)) {
        Status->FilterList = HAL_CAN_ID_EXT_EXTENDED;
    } else {
        Status->FilterList = HAL_CAN_ID_EXT_STANDARD;
    }
    
    /* Extract the index of the matching acceptance filter. */
    Status->FilterIndex = (HAL_CAN_AcceptFilSlotTypeDef)LL_CAN_ExtractPriorityMessageAcceptStatus(msg_sta);

    /* Extract the destination message storage (PRB or SRB). */
    Status->MessageStorage = (HAL_CAN_FrmStoreModeTypeDef)LL_CAN_ExtractPriorityMessageBufferStatus(msg_sta);

    return HAL_OK;
}

/**
  * @}
  */ /* CAN_HAL_EF_Operation */

/** @defgroup CAN_HAL_EF_Transfer CAN Transfer Functions
  * @brief    CAN Transfer Functions
  * @{
  */

/**
  * @brief  Transmit one frame using the Primary Transmit Buffer (PTB) in CPU
  *         blocking mode.
  * @note   This function writes the message information and data into the PTB,
  *         then requests the transmission. It returns after the frame has been
  *         successfully queued into the TX buffer. The function does not wait
  *         for the actual acknowledgment on the CAN bus.
  *         The calling context must ensure that the CAN is in the ACTIVE state
  *         and that the PTB is not already busy with a previous transmission.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_TxBufFormatTypeDef structure
  *         containing the identifier, DLC, and frame attributes.
  * @param  pDataBuff Pointer to a buffer containing the payload data to be
  *         transmitted. The number of bytes written is derived from the DLC
  *         field in @p pMesgInfo.
  * @retval HAL_OK      - Frame successfully written to the PTB and transmission
  *                       requested.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_FAILED  - The PTB is already busy with a previous frame.
  * @retval HAL_BUSY    - The transmit state machine is not idle (if the
  *                       process-state checking is enabled).
  */
HAL_StatusTypeDef HAL_CAN_AddMessageToPTB(HAL_CAN_HandleTypeDef *Handle, 
                                          HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                          uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

    uint8_t dat_len;

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Check whether a previous PTB transmission is still in progress. */
    if (LL_CAN_PTB_IsTransmissionStarted(p_instance) || LL_CAN_IsListenOnlyModeEnabled(p_instance)) {
        return HAL_FAILED;
    }

    /* Transition the transmit state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Clear the transmit callback for this CPU-controlled transfer. */
    Handle->TxTsf.TxCallback = NULL;

    /* Select the PTB as the active transmit buffer. */
    LL_CAN_SelectTxBufferPTB(p_instance);

    /* Write the identifier word and the control word of the message into
       the PTB register space. */
    LL_CAN_WriteTxBufferRegisterID(p_instance, *((uint32_t *)pMesgInfo));
    LL_CAN_WriteTxBufferRegisterControl(p_instance, *(((uint32_t *)pMesgInfo) + 1));

    /* Write the payload data into the PTB data registers, padding to a
       multiple of four bytes. */
    if (pDataBuff != NULL) {
        dat_len = CAN_DatLen_Get(Handle, pMesgInfo->DataLengthCode);

        for (uint32_t i = 0; i < (dat_len + 3) / 4; i++) {
            LL_CAN_WriteTxBufferRegisterData(p_instance, i, *pDataBuff++);
        }
    }

    /* Start the transmission process on the PTB. */
    LL_CAN_PTB_StartTransmission(p_instance);

    /* The transmit operation is complete from the software perspective;
       return the state to IDLE. */
    Handle->TxTsf.TxState = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Transmit one frame using the Secondary Transmit Buffer (STB) in CPU
  *         blocking mode.
  * @note   This function writes the message into the STB, advances the buffer
  *         pointer, and then requests transmission of a single frame. It
  *         returns after the frame is queued and the STB buffer pointer has
  *         been updated. The function does not wait for the actual bus
  *         acknowledgment.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_TxBufFormatTypeDef structure
  *         containing the identifier, DLC, and frame attributes.
  * @param  pDataBuff Pointer to a buffer containing the payload data.
  * @retval HAL_OK      - Frame successfully written to the STB and transmission
  *                       requested.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_FAILED  - The STB buffer is already full or the previous frame
  *                       has not completed yet.
  * @retval HAL_BUSY    - The transmit state machine is not idle.
  * @retval HAL_TIMEOUT - The STB buffer pointer did not advance within the
  *                       configured timeout period.
  */
HAL_StatusTypeDef HAL_CAN_AddMessageToSTB(HAL_CAN_HandleTypeDef *Handle, 
                                          HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                          uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

    uint8_t dat_len;
    uint32_t tickstart;

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Check whether a previous frame transmission is still being processed. */
    if (LL_CAN_STB_IsTransmitOneFrameComplete(p_instance) || LL_CAN_IsListenOnlyModeEnabled(p_instance)) {
        return HAL_FAILED;
    }

    /* Transition the transmit state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Clear the transmit callback for this CPU-controlled transfer. */
    Handle->TxTsf.TxCallback = NULL;

    /* Select the STB as the active transmit buffer. */
    LL_CAN_SelectTxBufferSTB(p_instance);

    /* Write the message identifier and control words into the STB. */
    LL_CAN_WriteTxBufferRegisterID(p_instance, *((uint32_t *)pMesgInfo));
    LL_CAN_WriteTxBufferRegisterControl(p_instance, *(((uint32_t *)pMesgInfo) + 1));

    /* Write the payload data into the STB data registers, padding to a
       multiple of four bytes. */
    if (pDataBuff != NULL) {
        dat_len = CAN_DatLen_Get(Handle, pMesgInfo->DataLengthCode);

        for (uint32_t i = 0; i < (dat_len + 3) / 4; i++) {
            LL_CAN_WriteTxBufferRegisterData(p_instance, i, *pDataBuff++);
        }
    }

    /* Advance the STB write pointer to the next available buffer slot. */
    LL_CAN_STB_SetBufferNext(p_instance);

    /* Wait until the buffer pointer move is acknowledged by the hardware. */
    tickstart = HAL_GetTick();
    while (LL_CAN_STB_GetBufferNext(p_instance)) {
        if ((HAL_GetTick() - tickstart) > CAN_DEFAULT_TIMEOUT) {
            HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxState, HAL_CAN_TSF_STATE_BUSY, HAL_CAN_TSF_STATE_IDLE, {
                return HAL_ERROR;
            });

            return HAL_TIMEOUT;
        }
    }    

    /* Request the transmission of the frame currently stored in the STB. */
    LL_CAN_STB_StartTransmitOneFrame(p_instance);

    /* The transmit operation has been acknowledged by the hardware;
       return the state to IDLE. */
    Handle->TxTsf.TxState = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Receive one frame from the Primary Receive Buffer (PRB) in CPU
  *         blocking mode.
  * @note   The function first checks whether a new message is available in the
  *         PRB. The release operation must be confirmed by the hardware before 
  *         the next message can be accessed.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_RxBufFormatTypeDef structure where
  *         the message information (identifier, DLC, flags, timestamp, etc.)
  *         will be stored.
  * @param  pDataBuff Pointer to a buffer where the received payload data will
  *         be copied. The number of bytes copied is derived from the DLC field
  *         of the received message.
  * @retval HAL_OK      - Frame successfully received.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_FAILED  - No message in the PRB which is empty.
  * @retval HAL_BUSY    - The receive state machine is not idle.
  */
HAL_StatusTypeDef HAL_CAN_GetPRBMessage(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

#if LL_CAN_PRB_DEPTH_MAX > 0
    uint32_t buf_depth;
#endif

    uint32_t tickstart;

    CAN_TypeDef *p_instance = Handle->Instance;
    const uint32_t data_reg_addr = LL_CAN_PRB_GetDataBufferAddress(Handle->Instance);

    /* Check whether a new frame is available in the PRB. */
    if (!LL_CAN_PRB_GetRxBufferStatus(p_instance)) {
        return HAL_FAILED;
    }

    /* Transition the PRB receive state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->RxTsfPRB.RxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Store the user pointers and clear the callback for CPU mode. */
    Handle->RxTsfPRB.RxCallback     = NULL;
    Handle->RxTsfPRB.pDatBuf        = pDataBuff;
    Handle->RxTsfPRB.pMsgInfo       = pMesgInfo;

    /* Read the message information and the payload data from the PRB. */
    if (pMesgInfo != NULL) {
        *((uint32_t *)pMesgInfo + 0) = LL_CAN_PRB_ReadBufferRegisterID(p_instance);
        *((uint32_t *)pMesgInfo + 1) = LL_CAN_PRB_ReadBufferRegisterControl(p_instance);

        if (pDataBuff != NULL) {
            /* Copy only the number of bytes indicated by the DLC. */
            memcpy((void *)pDataBuff, (void *)data_reg_addr, CAN_DatLen_Get(Handle, pMesgInfo->DataLengthCode));
        }

        /* Release the PRB slot so that the hardware can overwrite it with the
        next received frame. */
        LL_CAN_PRB_ReleaseBuffer(p_instance);    
        
        /* Wait until the hardware confirms that the buffer slot has been
           released and the pointer has advanced. */
        tickstart = HAL_GetTick();
        while (!LL_CAN_PRB_IsBufferReleaseDone(p_instance)) {
            if ((HAL_GetTick() - tickstart) > CAN_DEFAULT_TIMEOUT) {
                HAL_CAN_PARAM_UPDATE(Handle->RxTsfPRB.RxState, HAL_CAN_TSF_STATE_BUSY, HAL_CAN_TSF_STATE_IDLE, {
                    return HAL_ERROR;
                });

                return HAL_TIMEOUT;
            }
        };

    }

#if LL_CAN_PRB_DEPTH_MAX > 0
    /* Obtain the current fill level of the PRB. */
    buf_depth = LL_CAN_PRB_GetRxBufferStatus(p_instance);
#endif

#if LL_CAN_PRB_DEPTH_MAX == 3
    /* Clear the buffer status interrupt flags that are no longer valid
       according to the current fill level. */
    if (buf_depth < LL_CAN_RX_BUF_STA_FULL) {
        if (LL_CAN_IsActiveFlag_RFIF(p_instance)) {
            LL_CAN_ClearFlag_RFIF(p_instance); 
        }
    }

    if (buf_depth < LL_CAN_RX_BUF_STA_ALMOST_FULL) {
        if (LL_CAN_IsActiveFlag_RAFIF(p_instance)) {
            LL_CAN_ClearFlag_RAFIF(p_instance);  
        }        
    } 

    if (buf_depth == LL_CAN_RX_BUF_STA_EMPTY) {
        if (LL_CAN_IsActiveFlag_RIF(p_instance)) {
            LL_CAN_ClearFlag_RIF(p_instance); 
        }
    }
#endif

    /* Return the receive state to IDLE. */
    Handle->RxTsfPRB.RxState = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;     
}

/**
  * @brief  Receive one frame from the Secondary Receive Buffer (SRB) in CPU
  *         blocking mode.
  * @note   This function reads a single frame at a time from the SRB, if any
  *         is available. The release operation must be confirmed by the 
  *         hardware before the next message can be accessed.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_RxBufFormatTypeDef structure where
  *         the received message information will be stored.
  * @param  pDataBuff Pointer to a buffer where the received payload data will
  *         be copied.
  * @retval HAL_OK      - Frame successfully received.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_FAILED  - No message in the SRB which is empty.
  * @retval HAL_BUSY    - The receive state machine is not idle.
  * @retval HAL_TIMEOUT - The SRB release operation was not acknowledged by the
  *                       hardware within the configured timeout period.
  */
HAL_StatusTypeDef HAL_CAN_GetSRBMessage(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

#if LL_CAN_SRB_DEPTH_MAX > 0
    uint32_t buf_depth;
#endif

    uint32_t tickstart;

    CAN_TypeDef *p_instance = Handle->Instance;
    const uint32_t data_reg_addr = LL_CAN_SRB_GetDataBufferAddress(Handle->Instance);

    /* Check whether a new frame is available in the SRB. */
    if (!LL_CAN_SRB_GetRxBufferStatus(p_instance)) {
        return HAL_FAILED;
    }  

    /* Transition the SRB receive state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->RxTsfSRB.RxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Store the user pointers and clear the callback for CPU mode. */
    Handle->RxTsfSRB.RxCallback     = NULL;
    Handle->RxTsfSRB.pDatBuf        = pDataBuff;
    Handle->RxTsfSRB.pMsgInfo       = pMesgInfo;

    if (pMesgInfo != NULL) { 
        /* Read the message information and the payload data from the SRB. */
        *((uint32_t *)pMesgInfo + 0) = LL_CAN_SRB_ReadBufferRegisterID(p_instance);
        *((uint32_t *)pMesgInfo + 1) = LL_CAN_SRB_ReadBufferRegisterControl(p_instance);

        if (pDataBuff != NULL) {
            memcpy((void *)pDataBuff, (void *)data_reg_addr, CAN_DatLen_Get(Handle, pMesgInfo->DataLengthCode));
        }    

        /* Release the SRB slot currently read. */
        LL_CAN_SRB_ReleaseBuffer(p_instance);

        /* Wait until the hardware confirms that the buffer slot has been
           released and the pointer has advanced. */
        tickstart = HAL_GetTick();
        while (!LL_CAN_SRB_IsBufferReleaseDone(p_instance)) {
            if ((HAL_GetTick() - tickstart) > CAN_DEFAULT_TIMEOUT) {
                HAL_CAN_PARAM_UPDATE(Handle->RxTsfSRB.RxState, HAL_CAN_TSF_STATE_BUSY, HAL_CAN_TSF_STATE_IDLE, {
                    return HAL_ERROR;
                });

                return HAL_TIMEOUT;
            }
        };
    }

#if LL_CAN_SRB_DEPTH_MAX > 0
    /* Obtain the current fill level of the SRB. */
    buf_depth = LL_CAN_SRB_GetRxBufferStatus(p_instance);
#endif

#if LL_CAN_SRB_DEPTH_MAX == 3
    /* Clear the buffer status interrupt flags that are no longer valid
       according to the current fill level. */
    if (buf_depth < LL_CAN_RX_BUF_STA_FULL) {
        if (LL_CAN_IsActiveFlag_SFIF(p_instance)) {
            LL_CAN_ClearFlag_SFIF(p_instance); 
        }
    }

    if (buf_depth < LL_CAN_RX_BUF_STA_ALMOST_FULL) {
        if (LL_CAN_IsActiveFlag_SAFIF(p_instance)) {
            LL_CAN_ClearFlag_SAFIF(p_instance);  
        }        
    } 

    if (buf_depth == LL_CAN_RX_BUF_STA_EMPTY) {
        if (LL_CAN_IsActiveFlag_SRIF(p_instance)) {
            LL_CAN_ClearFlag_SRIF(p_instance); 
        }
    }
#endif

    /* Return the SRB receive state to IDLE. */
    Handle->RxTsfSRB.RxState = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Get one transmit-event frame from the Event Transmit Buffer (ETB)
  *         in CPU blocking mode.
  * @note   The ETB stores transmit-event information for frames that were sent
  *         with the EventType bit set in the transmit buffer format. The user
  *         must ensure that the bus does not enter the transmission state
  *         while this function is reading the ETB, otherwise the ETB contents
  *         may be modified by a new event.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_TxEvtBufFormatTypeDef structure where
  *         the transmit-event information will be stored.
  * @retval HAL_OK      - Transmit-event frame successfully read.
  * @retval HAL_INVALID - The @p pMesgInfo pointer is NULL.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_FAILED  - A transmit operation is still in progress or the ETB
  *                       is empty.
  * @retval HAL_BUSY    - The transmit state machine is not idle.
  * @retval HAL_TIMEOUT - The ETB release operation was not acknowledged within
  *                       the configured timeout period.
  */
HAL_StatusTypeDef HAL_CAN_GetTxEvent(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_TxEvtBufFormatTypeDef *pMesgInfo)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

#if LL_CAN_ETB_DEPTH_MAX > 0
    uint32_t buf_depth;
#endif

    uint32_t tickstart;

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Ensure that no transmission is currently being processed and that an
       event is available in the ETB. */
    if ((LL_CAN_STB_IsTransmitOneFrameComplete(p_instance)) || (LL_CAN_PTB_IsTransmissionStarted(p_instance)) || (!LL_CAN_ETB_GetRxBufferStatus(p_instance))) {
        return HAL_FAILED;
    }

    /* Transition the transmit state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxEvtState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        Handle->TxTsf.TxEvtState = HAL_CAN_TSF_STATE_IDLE;
        return HAL_BUSY;
    });

    /* Store the destination pointer and clear the event callback. */
    Handle->TxTsf.TxEvtCallback = NULL;
    Handle->TxTsf.pTxEvtMsgInfo = pMesgInfo;

    /* Read the event message information from the ETB. */
    if (pMesgInfo != NULL) {
        *((uint32_t *)pMesgInfo + 0) = LL_CAN_ETB_ReadBufferRegisterID(p_instance);
        *((uint32_t *)pMesgInfo + 1) = LL_CAN_ETB_ReadBufferRegisterData(p_instance);
    }

    /* Release the ETB slot that was read. */
    LL_CAN_ETB_ReleaseBuffer(p_instance); 

    /* Wait until the hardware acknowledges the ETB release operation. */
    tickstart = HAL_GetTick();  
    while (!LL_CAN_ETB_IsBufferReleaseDone(p_instance)) {
        if ((HAL_GetTick() - tickstart) > CAN_DEFAULT_TIMEOUT) {
            Handle->TxTsf.TxState       = HAL_CAN_TSF_STATE_IDLE;
            Handle->TxTsf.TxEvtState    = HAL_CAN_TSF_STATE_IDLE;
            return HAL_TIMEOUT;
        }
    }

#if LL_CAN_ETB_DEPTH_MAX > 0
    /* Obtain the current fill level of the ETB. */
    buf_depth = LL_CAN_ETB_GetRxBufferStatus(p_instance);
#endif

#if LL_CAN_ETB_DEPTH_MAX == 3
    /* Clear the buffer status interrupt flags that are no longer valid. */
    if (buf_depth < LL_CAN_RX_BUF_STA_FULL) {
        if (LL_CAN_IsActiveFlag_EFIF(p_instance)) {
            LL_CAN_ClearFlag_EFIF(p_instance); 
        }
    }

    if (buf_depth < LL_CAN_RX_BUF_STA_ALMOST_FULL) {
        if (LL_CAN_IsActiveFlag_EAFIF(p_instance)) {
            LL_CAN_ClearFlag_EAFIF(p_instance);  
        }        
    } 

    if (buf_depth == LL_CAN_RX_BUF_STA_EMPTY) {
        if (LL_CAN_IsActiveFlag_ERIF(p_instance)) {
            LL_CAN_ClearFlag_ERIF(p_instance); 
        }
    }
#endif

    /* The TX path can now be used again by the application. */
    Handle->TxTsf.TxState       = HAL_CAN_TSF_STATE_IDLE;
    Handle->TxTsf.TxEvtState    = HAL_CAN_TSF_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Transmit one frame using the Primary Transmit Buffer (PTB) in
  *         non-blocking mode with interrupt.
  * @note   The message information and payload are written into the PTB, then
  *         the transmission is started. When the frame has been successfully
  *         transmitted on the bus, the PTB transmit-complete interrupt is
  *         generated and the associated callback is invoked from the IRQ
  *         handler.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_TxBufFormatTypeDef structure
  *         containing the message information.
  * @param  pDataBuff Pointer to a buffer containing the payload data.
  * @retval HAL_OK      - Frame successfully queued for transmission.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_FAILED  - The PTB is already busy with a previous frame.
  * @retval HAL_BUSY    - The transmit state machine is not idle.
  */
HAL_StatusTypeDef HAL_CAN_AddMessageToPTB_IT(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

    uint8_t dat_len;

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Check whether a previous PTB transmission is still in progress. */
    if (LL_CAN_PTB_IsTransmissionStarted(p_instance) || LL_CAN_IsListenOnlyModeEnabled(p_instance)) {
        return HAL_FAILED;
    }

    /* Transition the transmit state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Register the interrupt service routine for transmit completion. */
    Handle->TxTsf.TxCallback = CAN_TxISR_PTB;

    /* Clear the PTB transmit-complete pending flag. */
    LL_CAN_ClearFlag_TPIF(p_instance);

    /* Select the PTB as the active transmit buffer. */
    LL_CAN_SelectTxBufferPTB(p_instance);

    /* Write the message identifier and control words. */
    LL_CAN_WriteTxBufferRegisterID(p_instance, *((uint32_t *)pMesgInfo));
    LL_CAN_WriteTxBufferRegisterControl(p_instance, *(((uint32_t *)pMesgInfo) + 1));

    /* Write the payload data into the PTB data registers. */
    if (pDataBuff != NULL) {
        dat_len = CAN_DatLen_Get(Handle, pMesgInfo->DataLengthCode);

        for (uint32_t i = 0; i < (dat_len + 3) / 4; i++) {
            LL_CAN_WriteTxBufferRegisterData(p_instance, i, *pDataBuff++);
        }
    }

    /* Start the PTB transmission. */
    LL_CAN_PTB_StartTransmission(p_instance);

    /* Enable the PTB transmit-complete interrupt. */
    LL_CAN_EnableIT_TPIE(p_instance);

    return HAL_OK;
}

/**
  * @brief  Transmit one frame using the Secondary Transmit Buffer (STB) in
  *         non-blocking mode with interrupt.
  * @note   This function writes the frame into the STB, advances the STB
  *         pointer, and starts the transmission of a single frame. The
  *         transmit-complete interrupt invokes the registered callback after
  *         the frame is sent on the bus.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_TxBufFormatTypeDef structure
  *         containing the message information.
  * @param  pDataBuff Pointer to a buffer containing the payload data.
  * @retval HAL_OK      - Frame successfully queued for transmission.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_FAILED  - The STB is already busy with a previous frame.
  * @retval HAL_BUSY    - The transmit state machine is not idle.
  * @retval HAL_TIMEOUT - The STB buffer pointer did not advance within the
  *                       configured timeout period.
  */
HAL_StatusTypeDef HAL_CAN_AddMessageToSTB_IT(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

    uint8_t dat_len;
    uint32_t tickstart;

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Check whether the STB is still busy with the previous frame. */
    if (LL_CAN_STB_IsTransmitOneFrameComplete(p_instance) || LL_CAN_IsListenOnlyModeEnabled(p_instance)) {
        return HAL_FAILED;
    }

    /* Transition the transmit state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Register the interrupt service routine for transmit completion. */
    Handle->TxTsf.TxCallback  = CAN_TxISR_STB;

    /* Clear the STB transmit pending flag. */
    LL_CAN_ClearFlag_TSIF(p_instance);

    /* Select the STB as the active transmit buffer. */
    LL_CAN_SelectTxBufferSTB(p_instance);

    /* Write the message identifier and control words. */
    LL_CAN_WriteTxBufferRegisterID(p_instance, *((uint32_t *)pMesgInfo));
    LL_CAN_WriteTxBufferRegisterControl(p_instance, *(((uint32_t *)pMesgInfo) + 1));

    /* Write the payload data into the STB data registers. */
    if (pDataBuff != NULL) {
        dat_len = CAN_DatLen_Get(Handle, pMesgInfo->DataLengthCode);

        for (uint32_t i = 0; i < (dat_len + 3) / 4; i++) {
            LL_CAN_WriteTxBufferRegisterData(p_instance, i, *pDataBuff++);
        }
    }

    /* Advance the STB pointer to the next available buffer slot. */
    LL_CAN_STB_SetBufferNext(p_instance);

    /* Wait until the buffer pointer move is acknowledged by the hardware. */
    tickstart = HAL_GetTick();
    while (LL_CAN_STB_GetBufferNext(p_instance)) {
        if ((HAL_GetTick() - tickstart) > CAN_DEFAULT_TIMEOUT) {
            HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxState, HAL_CAN_TSF_STATE_BUSY, HAL_CAN_TSF_STATE_IDLE, {
                return HAL_ERROR;
            });

            return HAL_TIMEOUT;
        }
    }    

    /* Start the transmission of the frame currently stored in the STB. */
    LL_CAN_STB_StartTransmitOneFrame(p_instance);

    /* Enable the STB transmit-complete interrupt. */
    LL_CAN_EnableIT_TSIE(p_instance);

    return HAL_OK;
}

/**
  * @brief  Receive one frame from the Primary Receive Buffer (PRB) in
  *         non-blocking mode with interrupt.
  * @note   The receive interrupt is enabled and, when a new frame arrives, the
  *         interrupt handler will read the message information and payload
  *         into the buffers provided by the application, release the PRB slot,
  *         and invoke the receive-complete callback.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_RxBufFormatTypeDef structure where
  *         the received message information will be stored.
  * @param  pDataBuff Pointer to a buffer where the received payload data will
  *         be copied.
  * @retval HAL_OK      - Reception armed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_BUSY    - The PRB receive state machine is not idle.
  */
HAL_StatusTypeDef HAL_CAN_GetPRBMessage_IT(HAL_CAN_HandleTypeDef *Handle,
                                        HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                        uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Transition the PRB receive state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->RxTsfPRB.RxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Store the user buffer pointers and register the ISR callback. */
    Handle->RxTsfPRB.RxCallback = CAN_RxISR_PRB;
    Handle->RxTsfPRB.pDatBuf    = pDataBuff;
    Handle->RxTsfPRB.pMsgInfo   = pMesgInfo;

    /* Enable the PRB receive interrupt. */
    LL_CAN_EnableIT_RIE(p_instance);

    return HAL_OK;
}

/**
  * @brief  Receive one frame from the Secondary Receive Buffer (SRB) in
  *         non-blocking mode with interrupt.
  * @note   The SRB receive interrupt is enabled. When a frame arrives, the
  *         interrupt handler reads the message information and payload into
  *         the provided buffers, releases the SRB slot, and invokes the
  *         receive-complete callback.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_RxBufFormatTypeDef structure where
  *         the received message information will be stored.
  * @param  pDataBuff Pointer to a buffer where the received payload data will
  *         be copied.
  * @retval HAL_OK      - Reception armed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state.
  * @retval HAL_BUSY    - The SRB receive state machine is not idle.
  */
HAL_StatusTypeDef HAL_CAN_GetSRBMessage_IT(HAL_CAN_HandleTypeDef *Handle, 
                                        HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                        uint32_t *pDataBuff)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);
    ASSERT_FUNC_PARAM(pDataBuff != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL) || (pDataBuff == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Transition the SRB receive state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->RxTsfSRB.RxState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Store the user buffer pointers and register the ISR callback. */
    Handle->RxTsfSRB.RxCallback = CAN_RxISR_SRB;
    Handle->RxTsfSRB.pDatBuf    = pDataBuff;
    Handle->RxTsfSRB.pMsgInfo   = pMesgInfo;

    /* Enable the SRB receive interrupt. */
    LL_CAN_EnableIT_SRIE(p_instance);

    return HAL_OK;
}

/**
  * @brief  Get one transmit-event frame from the Event Transmit Buffer (ETB)
  *         in non-blocking mode with interrupt.
  * @note   This function arms the ETB receive interrupt. When a transmit-event
  *         is available, the interrupt handler reads the event information into
  *         the provided buffer, releases the ETB slot, and invokes the event
  *         callback. The user must ensure that the bus does not enter the
  *         transmission state while the event read is pending.
  * @param  Handle CAN handle
  * @param  pMesgInfo Pointer to a HAL_CAN_TxEvtBufFormatTypeDef structure where
  *         the transmit-event information will be stored.
  * @retval HAL_OK      - Event reception armed successfully.
  * @retval HAL_INVALID - The @p pMesgInfo pointer is NULL.
  * @retval HAL_ERROR   - The CAN handle is not in the ACTIVE state or a
  *                       transmission is still in progress.
  * @retval HAL_BUSY    - The transmit state machine is not idle.
  */
HAL_StatusTypeDef HAL_CAN_GetTxEvent_IT(HAL_CAN_HandleTypeDef *Handle, 
                                        HAL_CAN_TxEvtBufFormatTypeDef *pMesgInfo)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pMesgInfo != NULL);

    HAL_CAN_PARAM_CHECK({
        if ((pMesgInfo == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_CAN_STATE_ACTIVE);

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Ensure that no transmission is currently being processed. */
    if ((LL_CAN_STB_IsTransmitOneFrameComplete(p_instance)) || (LL_CAN_PTB_IsTransmissionStarted(p_instance))) {
        return HAL_ERROR;
    }

    /* Transition the Tx event state from IDLE to BUSY. */
    HAL_CAN_PARAM_UPDATE(Handle->TxTsf.TxEvtState, HAL_CAN_TSF_STATE_IDLE, HAL_CAN_TSF_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Register the event ISR callback and store the destination pointer. */
    Handle->TxTsf.TxEvtCallback = CAN_GetTxEvtISR_ETB;
    Handle->TxTsf.pTxEvtMsgInfo = pMesgInfo;

    /* Enable the ETB receive interrupt. */
    LL_CAN_EnableIT_ERIE(p_instance);

    return HAL_OK;
}

/**
  * @}
  */ /* CAN_HAL_EF_Transfer */

/** @defgroup CAN_HAL_EF_Interrupt CAN Interrupt Handler and Callback
  * @brief    CAN Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  Enable one or more CAN interrupt sources.
  * @param  Handle CAN handle
  * @param  InterruptRequests Bitmask of the interrupt sources to enable. This
  *         parameter can be any combination of @ref HAL_CAN_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully enabled.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_CAN_InterruptRequestEnable(HAL_CAN_HandleTypeDef *Handle,
                                                 HAL_CAN_ITEnMskTypeDef InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    LL_CAN_EnableIT(Handle->Instance, InterruptRequests);

    return HAL_OK;
}

/**
  * @brief  Disable one or more CAN interrupt sources.
  * @param  Handle CAN handle
  * @param  InterruptRequests Bitmask of the interrupt sources to disable. This
  *         parameter can be any combination of @ref HAL_CAN_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully disabled.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_CAN_InterruptRequestDisable(HAL_CAN_HandleTypeDef *Handle,
                                                  HAL_CAN_ITEnMskTypeDef InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    LL_CAN_DisableIT(Handle->Instance, InterruptRequests);

    return HAL_OK;
}

/**
  * @brief  CAN IRQ Handler
  * @note   The pending interrupt flags are cleared automatically by a read or
  *         write access according to the hardware behaviour. This function
  *         masks the pending flags with the enabled interrupt sources and then
  *         dispatches to the individual buffer/event handlers.
  * @param  Handle CAN handle
  * @retval None
  */
void HAL_CAN_IRQHandler(HAL_CAN_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    CAN_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_CAN_GetAllInterruptEnable(p_instance);
    const uint32_t int_pending = LL_CAN_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled in the
       corresponding interrupt-enable registers, excluding the AIE,AIF bits*/
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_CAN_INTRST_IT_FLAG_MSK; 

    /* Dispatch to the individual interrupt handlers for the different
       hardware resources. */
    CAN_HPM_IRQHandler(Handle, flag_status_masked);
    CAN_PRB_IRQHandler(Handle, flag_status_masked);
    CAN_SRB_IRQHandler(Handle, flag_status_masked);
    CAN_PTB_IRQHandler(Handle, flag_status_masked);
    CAN_STB_IRQHandler(Handle, flag_status_masked);
    CAN_ETB_IRQHandler(Handle, flag_status_masked);
    CAN_ERR_IRQHandler(Handle, flag_status_masked);
    CAN_TMS_IRQHandler(Handle, flag_status_masked);
    CAN_TMO_IRQHandler(Handle, flag_status_masked);

    /* Handle the transmit-abort interrupt separately. */
    if ((int_en & LL_CAN_INTREN_AIE_SP) && (int_pending & LL_CAN_INTRST_AIF_SP)) {
        /* Clear the abort interrupt pending flag. */
        LL_CAN_ClearFlag_AIF(p_instance);
        
        /* Invoke the abort completion callback. */
        HAL_CAN_AbortCallback(Handle);
    }  
}

/**
  * @brief  Callback invoked when the Secondary Transmit Buffer (STB) becomes
  *         completely empty.
  * @note   The application can override this weak function to react to an
  *         empty STB, for example to enqueue additional frames.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_STBEmptyCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_STBEmptyCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Secondary Transmit Buffer (STB) reaches
  *         the almost-empty warning level.
  * @note   The application can override this weak function to prepare new
  *         transmit messages before the STB runs completely empty.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_STBAlmostEmptyCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_STBAlmostEmptyCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a high-priority message is detected by the
  *         acceptance filter.
  * @note   The application can override this weak function to inspect the
  *         high-priority message status.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_HighPriorityMessageCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_HighPriorityMessageCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the timestamp counter wraps around or reaches
  *         the configured compare value.
  * @note   The application can override this weak function to timestamp events
  *         or perform periodic actions synchronized to the CAN timestamp.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_TimestampWraparoundCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_TimestampWraparoundCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Primary Receive Buffer (PRB) timeout
  *         counter reaches zero.
  * @note   The application can override this weak function to detect that the
  *         PRB has not been read within the expected time period.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_PRBTimeoutCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_PRBTimeoutCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Secondary Receive Buffer (SRB) timeout
  *         counter reaches zero.
  * @note   The application can override this weak function to detect that the
  *         SRB has not been read within the expected time period.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_SRBTimeoutCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_SRBTimeoutCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Event Transmit Buffer (ETB) timeout
  *         counter reaches zero.
  * @note   The application can override this weak function to detect that the
  *         ETB has not been read within the expected time period.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ETBTimeoutCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ETBTimeoutCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the continuous timeout counter reaches zero.
  * @note   The application can override this weak function to perform periodic
  *         actions with a period defined by the continuous timeout counter.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ContCntTimeoutCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ContCntTimeoutCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Secondary Receive Buffer (SRB) overflows.
  * @note   The application can override this weak function to handle a lost
  *         message due to an SRB overflow.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_SRBOverCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_SRBOverCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Secondary Receive Buffer (SRB) is full.
  * @note   The application can override this weak function to handle a full
  *         SRB, for example by reading out all pending messages.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_SRBFullCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_SRBFullCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Secondary Receive Buffer (SRB) reaches
  *         the almost-full warning level.
  * @note   The application can override this weak function to read messages
  *         before the SRB becomes completely full.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_SRBAlmostFullCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_SRBAlmostFullCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Event Transmit Buffer (ETB) overflows.
  * @note   The application can override this weak function to handle a lost
  *         transmit-event entry due to an ETB overflow.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ETBOverCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ETBOverCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Event Transmit Buffer (ETB) is full.
  * @note   The application can override this weak function to handle a full
  *         ETB, for example by reading out all pending events.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ETBFullCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ETBFullCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Event Transmit Buffer (ETB) reaches the
  *         almost-full warning level.
  * @note   The application can override this weak function to read the event
  *         entries before the ETB becomes completely full.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ETBAlmostFullCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ETBAlmostFullCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a new message is available in the Secondary
  *         Receive Buffer (SRB).
  * @note   The application can override this weak function to be notified of
  *         an SRB receive event.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_SRBRxCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_SRBRxCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a new transmit-event entry is available in
  *         the Event Transmit Buffer (ETB).
  * @note   The application can override this weak function to be notified of
  *         an ETB receive event.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ETBRxCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ETBRxCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the error counter reaches the configured
  *         error warning limit.
  * @note   The application can override this weak function to track the CAN
  *         error counter status.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_CounterErrorCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_CounterErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a new message is available in the Primary
  *         Receive Buffer (PRB).
  * @note   The application can override this weak function to be notified of
  *         a PRB receive event.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_PRBRxCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_PRBRxCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Primary Receive Buffer (PRB) overflows.
  * @note   The application can override this weak function to handle a lost
  *         message due to a PRB overflow.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_PRBOverCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_PRBOverCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Primary Receive Buffer (PRB) is full.
  * @note   The application can override this weak function to handle a full
  *         PRB, for example by reading out all pending messages.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_PRBFullCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_PRBFullCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the Primary Receive Buffer (PRB) reaches the
  *         almost-full warning level.
  * @note   The application can override this weak function to read messages
  *         before the PRB becomes completely full.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_PRBAlmostFullCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_PRBAlmostFullCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a frame transmitted through the Primary
  *         Transmit Buffer (PTB) has completed.
  * @note   The application can override this weak function to be notified of
  *         a successful PTB transmission.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_PTBTxCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_PTBTxCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a frame transmitted through the Secondary
  *         Transmit Buffer (STB) has completed.
  * @note   The application can override this weak function to be notified of
  *         a successful STB transmission.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_STBTxCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_STBTxCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a generic CAN error event occurs.
  * @note   The application can override this weak function to handle error
  *         conditions such as bus-off, error passive, arbitration loss, or
  *         bus errors.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ErrorCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a transmit abort has been completed.
  * @note   The application can override this weak function to be notified when
  *         an abort request is finalized by the hardware.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_AbortCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_AbortCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the CAN controller enters the Error Passive
  *         state.
  * @note   The application can override this weak function to handle the error
  *         passive condition, for example by increasing monitoring or
  *         adjusting the application behavior.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_PassiveErrorCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_PassiveErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the CAN controller detects an arbitration
  *         loss.
  * @note   The application can override this weak function to keep track of
  *         arbitration losses or to implement special retransmission logic.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_ArbitrationLostErrorCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_ArbitrationLostErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a bus error is detected on the CAN bus.
  * @note   The application can override this weak function to handle bus
  *         errors and to take corrective action.
  * @param  Handle CAN handle
  * @retval None
  */
__WEAK void HAL_CAN_BusErrorCallback(HAL_CAN_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CAN_BusErrorCallback could be implemented in the user file
     */
}

/**
  * @}
  */ /* CAN_HAL_EF_Interrupt */

/**
  * @}
  */ /* CAN_HAL_Exported_Functions */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup CAN_HAL_Private_Functions CAN HAL Private Functions
  * @brief    CAN HAL Private Functions
  * @{
  */

/**
  * @brief  Convert a Data Length Code (DLC) into the corresponding payload
  *         length in bytes.
  * @note   This function uses the DLC2LengthTable to obtain the nominal length.
  *         If the CAN FD extension is disabled in the peripheral, the returned
  *         length is clamped to the maximum classic CAN payload of 8 bytes.
  * @param  Handle CAN handle
  * @param  Code Data Length Code to be converted.
  * @return The payload length in bytes. Returns 0 if @p Code is out of range.
  */
__STATIC_FORCEINLINE uint8_t CAN_DatLen_Get(HAL_CAN_HandleTypeDef *Handle, 
                                            HAL_CAN_DatLenCodeTypeDef Code)
{
    if (Code >= HAL_CAN_DAT_LEN_CODE_NUMS) {
        return 0;
    }

    /* Fetch the nominal data length from the DLC lookup table. */
    uint8_t dat_len = DLC2LengthTable[Code];
    
    /* If CAN FD is not enabled, clamp the length to the classic CAN maximum. */
    return LL_CAN_IsFDEnabled(Handle->Instance) ? dat_len : 
                            (dat_len > HAL_CAN_20_DAT_LEN_MAX ? HAL_CAN_20_DAT_LEN_MAX : dat_len);
}

/**
  * @brief  Handle the PTB transmit-complete interrupt.
  * @note   This callback is invoked from the IRQ handler when a frame queued
  *         on the Primary Transmit Buffer has been successfully transmitted.
  *         It disables the transmit interrupt, clears the transfer state, and
  *         invokes the user-defined PTB transmit callback.
  * @param  Handle CAN handle
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_TxISR_PTB(HAL_CAN_HandleTypeDef *Handle)
{
    /* Disable the PTB transmit-complete interrupt to prevent re-entry. */
    LL_CAN_DisableIT_TPIE(Handle->Instance);

    /* Clear the callback and set the transfer state back to IDLE. */
    Handle->TxTsf.TxCallback    = NULL;
    Handle->TxTsf.TxState       = HAL_CAN_TSF_STATE_IDLE;

    /* Invoke the user registered callback for PTB transmission completion. */
    if (Handle->UserCallback.TxCpltPTBCallback) {
        Handle->UserCallback.TxCpltPTBCallback(Handle);
    }
}

/**
  * @brief  Handle the STB transmit-complete interrupt.
  * @note   This callback is invoked from the IRQ handler when a frame queued
  *         on the Secondary Transmit Buffer has been successfully transmitted.
  *         It disables the transmit interrupt, clears the transfer state, and
  *         invokes the user-defined STB transmit callback.
  * @param  Handle CAN handle
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_TxISR_STB(HAL_CAN_HandleTypeDef *Handle)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Disable the STB transmit-complete interrupt to prevent re-entry. */
    LL_CAN_DisableIT_TSIE(p_instance);

    /* Clear the callback and set the transfer state back to IDLE. */
    Handle->TxTsf.TxCallback    = NULL;
    Handle->TxTsf.TxState       = HAL_CAN_TSF_STATE_IDLE;

    /* Invoke the user registered callback for STB transmission completion. */
    if (Handle->UserCallback.TxCpltSTBCallback) {
        Handle->UserCallback.TxCpltSTBCallback(Handle);
    }
}

/**
  * @brief  Handle the PRB receive-complete interrupt.
  * @note   This callback is invoked from the IRQ handler when a new frame has
  *         been stored in the Primary Receive Buffer. It reads the message
  *         information and payload into the user-provided buffers, releases
  *         the corresponding PRB slot, and invokes the receive callback.
  * @param  Handle CAN handle
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_RxISR_PRB(HAL_CAN_HandleTypeDef *Handle)
{
    uint8_t data_len;
    CAN_TypeDef *p_instance = Handle->Instance;
    const uint32_t data_reg_addr = LL_CAN_PRB_GetDataBufferAddress(Handle->Instance);

    /* Disable the PRB receive interrupt to prevent re-entry. */
    LL_CAN_DisableIT_RIE(p_instance);

    /* Read the message information and payload data from the PRB. */
    if (Handle->RxTsfPRB.pMsgInfo != NULL) {
        *((uint32_t *)Handle->RxTsfPRB.pMsgInfo + 0) = LL_CAN_PRB_ReadBufferRegisterID(p_instance);
        *((uint32_t *)Handle->RxTsfPRB.pMsgInfo + 1) = LL_CAN_PRB_ReadBufferRegisterControl(p_instance);

        if (Handle->RxTsfPRB.pDatBuf != NULL) {
            data_len = CAN_DatLen_Get(Handle, Handle->RxTsfPRB.pMsgInfo->DataLengthCode);
            memcpy((void *)Handle->RxTsfPRB.pDatBuf, (void *)data_reg_addr, data_len);
        }
    }

    /* Release the current PRB slot so the hardware can accept the next frame. */
    LL_CAN_PRB_ReleaseBuffer(p_instance);

    /* Clear the callback and set the receive state back to IDLE. */
    Handle->RxTsfPRB.RxCallback = NULL;
    Handle->RxTsfPRB.RxState    = HAL_CAN_TSF_STATE_IDLE;

    /* Invoke the user registered callback for PRB reception completion. */
    if (Handle->UserCallback.RxCpltPRBCallback) {
        Handle->UserCallback.RxCpltPRBCallback(Handle);
    }
}

/**
  * @brief  Handle the SRB receive-complete interrupt.
  * @note   This callback is invoked from the IRQ handler when a new frame has
  *         been stored in the Secondary Receive Buffer. It reads the message
  *         information and payload into the user-provided buffers, releases
  *         the corresponding SRB slot, and invokes the receive callback.
  * @param  Handle CAN handle
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_RxISR_SRB(HAL_CAN_HandleTypeDef *Handle)
{
    uint8_t data_len;
    CAN_TypeDef *p_instance = Handle->Instance;
    const uint32_t data_reg_addr = LL_CAN_SRB_GetDataBufferAddress(Handle->Instance);

    if (Handle->RxTsfSRB.pMsgInfo != NULL) { 
        /* Disable the SRB receive interrupt to prevent re-entry during the copy. */
        LL_CAN_DisableIT_SRIE(p_instance);

        /* Read the message information and payload data from the SRB. */
        *((uint32_t *)Handle->RxTsfSRB.pMsgInfo + 0) = LL_CAN_SRB_ReadBufferRegisterID(p_instance);
        *((uint32_t *)Handle->RxTsfSRB.pMsgInfo + 1) = LL_CAN_SRB_ReadBufferRegisterControl(p_instance);
        
        if (Handle->RxTsfSRB.pDatBuf != NULL) {
            data_len = CAN_DatLen_Get(Handle, Handle->RxTsfSRB.pMsgInfo->DataLengthCode);
            memcpy((void *)Handle->RxTsfSRB.pDatBuf, (void *)data_reg_addr, data_len);
        }

        /* Release the current SRB slot so the hardware can overwrite it. */
        LL_CAN_SRB_ReleaseBuffer(p_instance);            
    }

    /* Clear the callback and set the receive state back to IDLE. */
    Handle->RxTsfSRB.RxCallback = NULL;
    Handle->RxTsfSRB.RxState    = HAL_CAN_TSF_STATE_IDLE;

    /* Invoke the user registered callback for SRB reception completion. */
    if (Handle->UserCallback.RxCpltSRBCallback) {
        Handle->UserCallback.RxCpltSRBCallback(Handle);
    }
}

/**
  * @brief  Handle the ETB event-complete interrupt.
  * @note   This callback is invoked from the IRQ handler when a new
  *         transmit-event entry is available in the Event Transmit Buffer. It
  *         reads the event information into the user-provided buffer, releases
  *         the ETB slot, and invokes the transmit-event callback.
  * @param  Handle CAN handle
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_GetTxEvtISR_ETB(HAL_CAN_HandleTypeDef *Handle)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Disable the ETB receive interrupt to prevent re-entry. */
    LL_CAN_DisableIT_ERIE(p_instance);

    /* Read the transmit-event information from the ETB. */
    if (Handle->TxTsf.pTxEvtMsgInfo != NULL) {
        *((uint32_t *)Handle->TxTsf.pTxEvtMsgInfo + 0) = LL_CAN_ETB_ReadBufferRegisterID(p_instance);
        *((uint32_t *)Handle->TxTsf.pTxEvtMsgInfo + 1) = LL_CAN_ETB_ReadBufferRegisterData(p_instance);
    }

    /* Release the current ETB slot so the hardware can store the next event. */
    LL_CAN_ETB_ReleaseBuffer(p_instance);
    
    /* Clear the event callback and set the transmit state back to IDLE. */
    Handle->TxTsf.TxEvtCallback = NULL;
    Handle->TxTsf.TxEvtState    = HAL_CAN_TSF_STATE_IDLE;

    /* Invoke the user registered callback for ETB event completion. */
    if (Handle->UserCallback.TxEvtCpltCallback) {
        Handle->UserCallback.TxEvtCpltCallback(Handle);
    }
}

/**
  * @brief  Reset a single acceptance filter slot to its default disabled state.
  * @note   The default state configures the filter to accept both standard and
  *         extended frames, with code and mask values set to zero, the
  *         acceptance mode set to AND, and the filter slot disabled.
  * @param  Handle CAN handle
  * @param  Slot Acceptance filter slot to be reset.
  * @return HAL status (always HAL_OK if the slot is valid).
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AcceptFilRst(HAL_CAN_HandleTypeDef *Handle, 
                                                        HAL_CAN_AcceptFilSlotTypeDef Slot)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Select the acceptance filter address for the given slot. */
    LL_CAN_SetAcceptanceFilterAddress(p_instance, Slot);

    /* First configure the mask value. */
    LL_CAN_SelectAcceptanceFilterContentMask(p_instance);
    LL_CAN_SetAcceptanceFilterCodeOrMaskValue(p_instance, 0);

    /* Configure the filter to accept both standard and extended frames. */
    LL_CAN_SetAcceptanceFilterRxFrame(p_instance, LL_CAN_ACCEPT_FILT_FRM_STD_EXT);

    /* Then configure the code value. */
    LL_CAN_SelectAcceptanceFilterContentCode(p_instance);
    LL_CAN_SetAcceptanceFilterCodeOrMaskValue(p_instance, 0);

    /* Set the acceptance mode to AND. */
    LL_CAN_SetAcceptanceMode(p_instance, LL_CAN_ACCEPT_MODE_AND);

    /* Configure the matching rule to store the frame in the PRB. */
    LL_CAN_SetAcceptanceControl(p_instance, LL_CAN_ACCEPT_CTRL_STORE_PRB);

    /* Disable the acceptance filter slot. */
    LL_CAN_DisableAcceptanceFilter(p_instance, ((uint8_t)Slot));

    return HAL_OK;
}

/**
  * @brief  Configure a single acceptance filter slot according to the provided
  *         configuration structure.
  * @param  Handle CAN handle
  * @param  pCfg Pointer to the filter configuration structure.
  * @return HAL status (always HAL_OK if the configuration is valid).
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AcceptFilCfg(HAL_CAN_HandleTypeDef *Handle, 
                                                        const HAL_CAN_FilterTypeDef *pCfg)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Select the acceptance filter address for the configured slot. */
    LL_CAN_SetAcceptanceFilterAddress(p_instance, pCfg->FilterIndex);

    /* Configure the mask value. */
    LL_CAN_SelectAcceptanceFilterContentMask(p_instance);
    LL_CAN_SetAcceptanceFilterCodeOrMaskValue(p_instance, pCfg->MaskID);

    /* Configure the frame type accepted by this filter. */
    LL_CAN_SetAcceptanceFilterRxFrame(p_instance, pCfg->IdType);

    /* Configure the code value. */
    LL_CAN_SelectAcceptanceFilterContentCode(p_instance);
    LL_CAN_SetAcceptanceFilterCodeOrMaskValue(p_instance, pCfg->CodeID);

    /* Set the acceptance mode (AND, OR, or Range). */
    LL_CAN_SetAcceptanceMode(p_instance, pCfg->FilterType);

    /* Configure the matching rule (where to store the message). */
    LL_CAN_SetAcceptanceControl(p_instance, pCfg->FilterConfig);

    /* Enable the acceptance filter slot. */
    LL_CAN_EnableAcceptanceFilter(p_instance, pCfg->FilterIndex);

    return HAL_OK;
}

/**
  * @brief  Reset all acceptance filter slots to their default disabled state.
  * @param  Handle CAN handle
  * @retval None
  */
__STATIC_FORCEINLINE void CAN_ResetFilter(HAL_CAN_HandleTypeDef *Handle)
{
    /* Reset every acceptance filter slot one by one. */
    for (uint8_t i = 0; i < HAL_CAN_ACCEPT_FILT_SLOT_NUMS; i++) {
        CAN_AcceptFilRst(Handle, (HAL_CAN_AcceptFilSlotTypeDef)i);
    }
}

/**
  * @brief  Reset the global filter configuration to its default state.
  * @note   The default state sets the PRB and SRB work modes to "overwrite",
  *         and enables reception of both standard and extended remote frames.
  * @param  Handle CAN handle
  * @return HAL status (always HAL_OK).
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_GlobalFilRst(HAL_CAN_HandleTypeDef *Handle)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Set the PRB and SRB work modes to overwrite. */
    LL_CAN_PRB_SetWorkMode(p_instance, LL_CAN_RX_BUF_WORK_MODE_COVER);
    LL_CAN_SRB_SetWorkMode(p_instance, LL_CAN_RX_BUF_WORK_MODE_COVER);

    /* Allow standard and extended remote frames to be received. */
    LL_CAN_DisableStandardRemoteFrameReject(p_instance);
    LL_CAN_DisableExtendedRemoteFrameReject(p_instance);
    
    return HAL_OK;
}

/**
  * @brief  Apply the global filter configuration.
  * @param  Handle CAN handle
  * @param  pCfg Pointer to the global filter configuration structure.
  * @return HAL status (always HAL_OK).
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_GlobalFilCfg(HAL_CAN_HandleTypeDef *Handle, 
                                                        const HAL_CAN_GlobalFilCfgTypeDef *pCfg)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Apply the PRB and SRB work modes. */
    LL_CAN_PRB_SetWorkMode(p_instance, pCfg->WorkModePRB);
    LL_CAN_SRB_SetWorkMode(p_instance, pCfg->WorkModeSRB);

    /* Configure the rejection of standard and extended remote frames. */
    HAL_FUNC_ALTER(pCfg->RejectRemoteStd,   LL_CAN_EnableStandardRemoteFrameReject(p_instance), 
                                            LL_CAN_DisableStandardRemoteFrameReject(p_instance));
    HAL_FUNC_ALTER(pCfg->RejectRemoteExt,   LL_CAN_EnableExtendedRemoteFrameReject(p_instance), 
                                            LL_CAN_DisableExtendedRemoteFrameReject(p_instance));

    return HAL_OK;
}

/**
  * @brief  Enable or disable the selected timeout counter.
  * @param  Handle CAN handle
  * @param  TimeoutCounter Identifier of the timeout counter (PRB, SRB, ETB,
  *         or continuous).
  * @param  IsEnable Set to HAL_CAN_FUNC_ENABLE to enable the counter, or
  *         HAL_CAN_FUNC_DISABLE to disable it.
  * @return HAL_OK on success, or HAL_INVALID if the parameter is incorrect.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_TimeoutCntrEnable(HAL_CAN_HandleTypeDef *Handle, 
                                                             HAL_CAN_TimeoutCntrTypeDef TimeoutCounter, 
                                                             HAL_CAN_EnableTypeDef IsEnable)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Enable or disable the timeout counter based on the counter type. */
    switch (TimeoutCounter) {
        case HAL_CAN_TIMEOUT_CNTR_PRB:
            HAL_FUNC_ALTER(IsEnable,    LL_CAN_PRB_EnableTimeout(p_instance), 
                                        LL_CAN_PRB_DisableTimeout(p_instance));
            break;

        case HAL_CAN_TIMEOUT_CNTR_SRB:
            HAL_FUNC_ALTER(IsEnable,    LL_CAN_SRB_EnableTimeout(p_instance), 
                                        LL_CAN_SRB_DisableTimeout(p_instance));
            break;

        case HAL_CAN_TIMEOUT_CNTR_ETB:
            HAL_FUNC_ALTER(IsEnable,    LL_CAN_ETB_EnableTimeout(p_instance), 
                                        LL_CAN_ETB_DisableTimeout(p_instance));
            break;

        case HAL_CAN_TIMEOUT_CNTR_CONT:
            HAL_FUNC_ALTER(IsEnable,    LL_CAN_EnableContinuousCountTimeout(p_instance), 
                                        LL_CAN_DisableContinuousCountTimeout(p_instance));
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the start period of the selected timeout down-counter.
  * @param  Handle CAN handle
  * @param  TimeoutCounter Identifier of the timeout counter.
  * @param  TimeoutPeriod Start value of the timeout down-counter.
  * @return HAL_OK on success, or HAL_INVALID if the parameter is incorrect.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_TimeoutCntrCfg(HAL_CAN_HandleTypeDef *Handle, 
                                                          HAL_CAN_TimeoutCntrTypeDef TimeoutCounter, 
                                                          uint16_t TimeoutPeriod)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Configure the down-counter period for the selected timeout counter. */
    switch (TimeoutCounter) {
        case HAL_CAN_TIMEOUT_CNTR_PRB:
            LL_CAN_PRB_SetTimeoutPeriod(p_instance, TimeoutPeriod); 
            break;

        case HAL_CAN_TIMEOUT_CNTR_SRB:
            LL_CAN_SRB_SetTimeoutPeriod(p_instance, TimeoutPeriod);
            break;

        case HAL_CAN_TIMEOUT_CNTR_ETB:
            LL_CAN_ETB_SetTimeoutPeriod(p_instance, TimeoutPeriod);
            break;

        case HAL_CAN_TIMEOUT_CNTR_CONT:
            LL_CAN_SetContinuousTimeoutPeriod(p_instance, TimeoutPeriod); 
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the "almost empty" warning limit of a transmit buffer.
  * @note   The almost-empty limit is used to generate an interrupt before the
  *         buffer becomes completely empty, allowing the application to refill
  *         the buffer in time. Currently, only the STB supports this feature.
  * @param  Handle CAN handle
  * @param  BufferType Message buffer type (currently only STB is supported).
  * @param  WarningLimit Almost-empty warning limit value.
  * @return HAL_OK on success, or HAL_INVALID if the buffer type is unsupported.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AlmostEmptyWarnLimitCfg(HAL_CAN_HandleTypeDef *Handle,
                                                                   HAL_CAN_MsgBufTypeDef BufferType, 
                                                                   HAL_CAN_BufAlmostEmptyLimitTypeDef WarningLimit)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    switch (BufferType) {
        case HAL_CAN_MESG_BUFFER_STB:
            LL_CAN_STB_SetAlmostEmptyWarningLimit(p_instance, WarningLimit);
            break;
        
        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the "almost full" warning limit of a receive buffer.
  * @note   The almost-full limit is used to generate an interrupt before the
  *         buffer becomes completely full, allowing the application to read
  *         out messages in time.
  * @param  Handle CAN handle
  * @param  BufferType Message buffer type (PRB, SRB, or ETB).
  * @param  WarningLimit Almost-full warning limit value.
  * @return HAL_OK on success, or HAL_INVALID if the buffer type is unsupported.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_AlmostFullWarnLimitCfg(HAL_CAN_HandleTypeDef *Handle,
                                                                  HAL_CAN_MsgBufTypeDef BufferType, 
                                                                  HAL_CAN_BufAlmostFullLimitTypeDef WarningLimit)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    switch (BufferType) {
        case HAL_CAN_MESG_BUFFER_PRB:
            LL_CAN_PRB_SetAlmostFullWarningLimit(p_instance, WarningLimit);
            break;

        case HAL_CAN_MESG_BUFFER_SRB:
            LL_CAN_SRB_SetAlmostFullWarningLimit(p_instance, WarningLimit);
            break;

        case HAL_CAN_MESG_BUFFER_ETB:
            LL_CAN_ETB_SetAlmostFullWarningLimit(p_instance, WarningLimit);
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}


/**
  * @brief  Configure the CAN operating mode.
  * @details This function resets the CAN operating mode registers and then applies
  *          the requested operating mode. It is called by HAL_CAN_OperatingModeCtrl.
  * @param  Handle CAN handle
  * @param  OpMode CAN operating mode to configure.
  * @retval HAL_OK  Operating mode configured successfully.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef CAN_OpModeCtrl(HAL_CAN_HandleTypeDef *Handle, 
                                                      HAL_CAN_OpModeTypeDef OpMode)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    /* Reset operating  mode */
    LL_CAN_ResetOperationMode(p_instance);

    switch (OpMode) {
        case HAL_CAN_OP_MODE_LISTEN_ONLY:
            LL_CAN_EnableListenOnlyMode(p_instance);
            break;
        case HAL_CAN_OP_MODE_EXTERNAL_LOOP:
            LL_CAN_EnableLoopBackModeExternal(p_instance);
            break;
        case HAL_CAN_OP_MODE_INTERNAL_LOOP:
            LL_CAN_EnableLoopBackModeInternal(p_instance);
            break;
        
        case HAL_CAN_OP_MODE_NORMAL:
        default:
            break;
    }

    return HAL_OK;
}

/**
  * @brief  Handle the Primary Receive Buffer (PRB) interrupt events.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for the PRB.
  * @note   The flags are cleared by reading the corresponding registers.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_PRB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_CAN_INTRST_PRB_IT_FLAG_MSK; 

    /* If there are no PRB interrupts to handle, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle the PRB receive-complete flag. */
    if ((flag_status_masked & LL_CAN_INTRST_RIF)) {
        /* Clear the receive pending flag. */
        LL_CAN_ClearFlag_RIF(p_instance);

        /* Invoke the internal ISR callback if one is armed for a non-blocking
           transfer. */
        if (Handle->RxTsfPRB.RxCallback) {
            Handle->RxTsfPRB.RxCallback(Handle);
        }

        /* Invoke the corresponding user callback. */
        HAL_CAN_PRBRxCallback(Handle);
    }

    /* Handle the PRB overrun flag. */
    if ((flag_status_masked & LL_CAN_INTRST_ROIF)) {
        /* Clear the overrun pending flag. */
        LL_CAN_ClearFlag_ROIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_PRBOverCallback(Handle);
    }

    /* Handle the PRB full flag. */
    if ((flag_status_masked & LL_CAN_INTRST_RFIF)) {
        /* Clear the full pending flag. */
        LL_CAN_ClearFlag_RFIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_PRBFullCallback(Handle);
    }

    /* Handle the PRB almost-full flag. */
    if ((flag_status_masked & LL_CAN_INTRST_RAFIF)) {
        /* Clear the almost-full pending flag. */
        LL_CAN_ClearFlag_RAFIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_PRBAlmostFullCallback(Handle);
    }
}

/**
  * @brief  Handle the Secondary Receive Buffer (SRB) interrupt events.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for the SRB.
  * @note   The flags are cleared by reading the corresponding registers.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_SRB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_CAN_INTRST_SRB_IT_FLAG_MSK; 

    /* If there are no SRB interrupts to handle, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle the SRB receive-complete flag. */
    if ((flag_status_masked & LL_CAN_INTRST_SRIF)) {
        /* Clear the receive pending flag. */
        LL_CAN_ClearFlag_SRIF(p_instance);

        /* Invoke the internal ISR callback if one is armed. */
        if (Handle->RxTsfSRB.RxCallback) {
            Handle->RxTsfSRB.RxCallback(Handle);
        }

        /* Invoke the corresponding user callback. */
        HAL_CAN_SRBRxCallback(Handle);
    }

    /* Handle the SRB almost-full flag. */
    if ((flag_status_masked & LL_CAN_INTRST_SAFIF)) {
        /* Clear the almost-full pending flag. */
        LL_CAN_ClearFlag_SAFIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_SRBAlmostFullCallback(Handle);
    }

    /* Handle the SRB full flag. */
    if ((flag_status_masked & LL_CAN_INTRST_SFIF)) {
        /* Clear the full pending flag. */
        LL_CAN_ClearFlag_SFIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_SRBFullCallback(Handle);
    }

    /* Handle the SRB overflow flag. */
    if ((flag_status_masked & LL_CAN_INTRST_SOIF)) {
        /* Clear the overflow pending flag. */
        LL_CAN_ClearFlag_SOIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_SRBOverCallback(Handle);
    }
}

/**
  * @brief  Handle the Primary Transmit Buffer (PTB) interrupt events.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for the PTB.
  * @note   The flags are cleared by reading the corresponding registers.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_PTB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    /* Handle the PTB transmit-complete flag. */
    if ((FlagMask & LL_CAN_INTRST_TPIF)) {
        /* Clear the transmit pending flag. */
        LL_CAN_ClearFlag_TPIF(Handle->Instance);

        /* Invoke the internal ISR callback if one is armed. */
        if (Handle->TxTsf.TxCallback) {
            Handle->TxTsf.TxCallback(Handle);
        }

        /* Invoke the corresponding user callback. */
        HAL_CAN_PTBTxCallback(Handle);
    }
}

/**
  * @brief  Handle the Secondary Transmit Buffer (STB) interrupt events.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for the STB.
  * @note   The empty and almost-empty flags are cleared automatically by
  *         writing new messages to the STB.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_STB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_CAN_INTRST_STB_IT_FLAG_MSK; 

    /* If there are no STB interrupts to handle, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle the STB transmit-complete flag. */
    if ((flag_status_masked & LL_CAN_INTRST_TSIF)) {
        /* Clear the transmit pending flag. */
        LL_CAN_ClearFlag_TSIF(p_instance);

        /* Invoke the internal ISR callback if one is armed. */
        if (Handle->TxTsf.TxCallback) {
            Handle->TxTsf.TxCallback(Handle);
        }

        /* Invoke the corresponding user callback. */
        HAL_CAN_STBTxCallback(Handle);
    }

    /* Handle the STB almost-empty flag. */
    if ((flag_status_masked & LL_CAN_INTRST_TAEIF)) {
        /* Note: This flag is not cleared here. The user should write new
           messages to the STB to clear this pending flag. */

        /* Invoke the corresponding user callback. */
        HAL_CAN_STBAlmostEmptyCallback(Handle);
    }

    /* Handle the STB empty flag. */
    if ((flag_status_masked & LL_CAN_INTRST_TEIF)) {
        /* Note: This flag is not cleared here. The user should write new
           messages to the STB to clear this pending flag. */

        /* Invoke the corresponding user callback. */
        HAL_CAN_STBEmptyCallback(Handle);
    }
}

/**
  * @brief  Handle the Event Transmit Buffer (ETB) interrupt events.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for the ETB.
  * @note   The flags are cleared by reading the corresponding registers.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_ETB_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_CAN_INTRST_ETB_IT_FLAG_MSK; 

    /* If there are no ETB interrupts to handle, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle the ETB receive-complete flag. */
    if ((flag_status_masked & LL_CAN_INTRST_ERIF)) {
        /* Clear the receive pending flag. */
        LL_CAN_ClearFlag_ERIF(p_instance);

        /* Invoke the internal ISR callback if one is armed. */
        if (Handle->TxTsf.TxEvtCallback) {
            Handle->TxTsf.TxEvtCallback(Handle);
        }

        /* Invoke the corresponding user callback. */
        HAL_CAN_ETBRxCallback(Handle);
    }

    /* Handle the ETB almost-full flag. */
    if ((flag_status_masked & LL_CAN_INTRST_EAFIF)) {
        /* Clear the almost-full pending flag. */
        LL_CAN_ClearFlag_EAFIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_ETBAlmostFullCallback(Handle);
    }

    /* Handle the ETB full flag. */
    if ((flag_status_masked & LL_CAN_INTRST_EFIF)) {
        /* Clear the full pending flag. */
        LL_CAN_ClearFlag_EFIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_ETBFullCallback(Handle);
    }

    /* Handle the ETB overflow flag. */
    if ((flag_status_masked & LL_CAN_INTRST_EOIF)) {
        /* Clear the overflow pending flag. */
        LL_CAN_ClearFlag_EOIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_ETBOverCallback(Handle);
    }
}

/**
  * @brief  Handle the CAN error-related interrupt events.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for error events.
  * @note   The error code field in the handle is updated with the masked flags.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_ERR_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_CAN_INTRST_ERR_IT_FLAG_MSK; 

    if (flag_status_masked) {
        /* Accumulate the error flags into the handle error code. */
        Handle->ErrorCode |= flag_status_masked;
    } else {
        return;
    }

    /* Handle the bus-off/error interrupt flag. */
    if ((flag_status_masked & LL_CAN_INTRST_EIF)) {
        /* If the CAN is in the reset state, clear the reset flag. */
        if (LL_CAN_GetResetState(p_instance)) {
            LL_CAN_ClearReset(p_instance);
        }

        /* Clear the error pending flag. */
        LL_CAN_ClearFlag_EIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_ErrorCallback(Handle);
    }

    /* Handle the error passive flag. */
    if ((flag_status_masked & LL_CAN_INTRST_EPIF)) {
        /* Clear the error passive pending flag. */
        LL_CAN_ClearFlag_EPIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_PassiveErrorCallback(Handle);
    }

    /* Handle the arbitration lost flag. */
    if ((flag_status_masked & LL_CAN_INTRST_ALIF)) {
        /* Clear the arbitration lost pending flag. */
        LL_CAN_ClearFlag_ALIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_ArbitrationLostErrorCallback(Handle);
    }

    /* Handle the bus error flag. */
    if ((flag_status_masked & LL_CAN_INTRST_BEIF)) {
        /* Clear the bus error pending flag. */
        LL_CAN_ClearFlag_BEIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_BusErrorCallback(Handle);
    }

    /* Handle the error counter flag. */
    if ((flag_status_masked & LL_CAN_INTRST_ECIF)) {
        /* Clear the error counter pending flag. */
        LL_CAN_ClearFlag_ECIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_CounterErrorCallback(Handle);
    }
}

/**
  * @brief  Handle the timestamp-related interrupt flag.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for timeout events.
  * @note   The flags are cleared by writing to the corresponding interrupt
  *         pending clear registers.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_TMS_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    /* Handle the timestamp over-zero flag. */
    if ((FlagMask & LL_CAN_INTRST_TSCIF)) {
        /* Clear the timestamp over-zero pending flag. */
        LL_CAN_ClearFlag_TSCIF(Handle->Instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_TimestampWraparoundCallback(Handle);
    }
}

/**
  * @brief  Handle the CAN timeout-related interrupt events.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending
  *         for timeout events.
  * @note   The flags are cleared by writing to the corresponding interrupt
  *         pending clear registers.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_TMO_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    CAN_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_CAN_INTRST_TMO_IT_FLAG_MSK; 

    /* If there are no timeout interrupts to handle, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle the continuous count timeout flag. */
    if ((flag_status_masked & LL_CAN_INTRST_CTOIF)) {
        /* Clear the continuous count timeout pending flag. */
        LL_CAN_ClearFlag_CTOIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_ContCntTimeoutCallback(Handle);
    }

    /* Handle the ETB timeout flag. */
    if ((flag_status_masked & LL_CAN_INTRST_ETOIF)) {
        /* Clear the ETB timeout pending flag. */
        LL_CAN_ClearFlag_ETOIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_ETBTimeoutCallback(Handle);
    }
    
    /* Handle the SRB timeout flag. */
    if ((flag_status_masked & LL_CAN_INTRST_STOIF)) {
        /* Clear the SRB timeout pending flag. */
        LL_CAN_ClearFlag_STOIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_SRBTimeoutCallback(Handle);
    }  

    /* Handle the PRB timeout flag. */
    if ((flag_status_masked & LL_CAN_INTRST_RTOIF)) {
        /* Clear the PRB timeout pending flag. */
        LL_CAN_ClearFlag_RTOIF(p_instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_PRBTimeoutCallback(Handle);
    }
}

/**
  * @brief  Handle the high-priority message interrupt flag.
  * @param  Handle CAN handle
  * @param  FlagMask Mask of interrupt flags that are both enabled and pending.
  * @note   A high-priority message is a message that matches a filter slot
  *         configured with the "update priority status register" control bit.
  * @return None.
  */
__STATIC_FORCEINLINE void CAN_HPM_IRQHandler(HAL_CAN_HandleTypeDef *Handle, uint32_t FlagMask)
{
    /* Handle the high-priority message interrupt flag. */
    if ((FlagMask & LL_CAN_INTRST_PMIF)) {
        /* Clear the high-priority message pending flag. */
        LL_CAN_ClearFlag_PMIF(Handle->Instance);

        /* Invoke the corresponding user callback. */
        HAL_CAN_HighPriorityMessageCallback(Handle);
    }
}

/**
  * @}
  */ /* CAN_HAL_Private_Functions */


#endif /* HAL_CAN_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* CAN */

/**
  * @}
  */ /* CAN_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

