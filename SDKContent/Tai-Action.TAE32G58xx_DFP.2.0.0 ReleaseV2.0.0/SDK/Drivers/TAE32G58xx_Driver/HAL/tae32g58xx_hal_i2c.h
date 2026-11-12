/**
  ******************************************************************************
  * @file    tae32g58xx_hal_i2c.h
  * @author  Tai-Action SD Team
  * @brief   Header file of I2C HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_HAL_I2C_H_
#define _TAE32G58XX_HAL_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_i2c.h"

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined (I2C0) || defined (I2C1) || defined (I2C2)
  /** @defgroup I2C I2C
  * @{
  */

/** @defgroup I2C_HAL I2C HAL
  * @brief    I2C HAL Module Driver
  * @{
  */


/** @defgroup I2C_HAL_Private_Configuration I2C HAL Private Configuration
  * @brief    I2C HAL Private Configuration
  * @{
  */

/**
  * @}
  */ /* I2C_HAL_Private_Configuration */

/* Exported Macros -----------------------------------------------------------*/
/** @defgroup I2C_HAL_Exported_Macros I2C HAL Exported Macros
  * @brief    I2C HAL Exported Macros
  * @{
  */

/** @defgroup I2C_HAL_EM_Assert I2C HAL Assert
  * @brief    I2C HAL Assert
  * @{
  */
/** @brief  The HAL_I2C_PARAM_CHECK function is off by default */
#ifndef TAE32_USE_HAL_I2C_CHECK_PARAM
#define TAE32_USE_HAL_I2C_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_I2C_CHECK_PARAM != 1) && (TAE32_USE_HAL_I2C_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_I2C_CHECK_PARAM
#define TAE32_USE_HAL_I2C_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif

#define HAL_I2C_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_I2C_CHECK_PARAM) { \
            expression;                      \
        }

#if defined(TAE32_USE_HAL_I2C_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_I2C_CHECK_PROCESS_STATE == 1)
#define HAL_I2C_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_I2C_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        do {                                                                      \
            if ((upd_parm) != (check_value)) {                                    \
                failed_expression;                                                \
                break;                                                            \
            } else {                                                              \
                (upd_parm) = (new_value);                                         \
            }                                                                     \
        } while (0)
#endif
/**
  * @}
  */ /* I2C_HAL_EM_Assert */
/**
  * @}
  */ /* I2C_HAL_Exported_Macros */



/* Exported Types ------------------------------------------------------------*/
/** @defgroup I2C_HAL_Exported_Types I2C HAL Exported Types
  * @{
  */

/**
  * @brief  I2C Addressing Mode enumeration
  */
typedef enum
{
    HAL_I2C_ADDRESSINGMODE_7BIT = 0x00000000UL,  /*!< 7-bit addressing mode  */
    HAL_I2C_ADDRESSINGMODE_10BIT = 0x00000001UL,  /*!< 10-bit addressing mode */
} HAL_I2C_AddressingModeTypeDef;

/**
  * @brief  I2C Dual Addressing Mode enumeration
  */
typedef enum
{
    HAL_I2C_DUALADDRESS_DISABLE = 0x00000000UL,  /*!< Dual addressing disabled */
    HAL_I2C_DUALADDRESS_ENABLE  = 0x00000001UL,  /*!< Dual addressing enabled  */
} HAL_I2C_DualAddressTypeDef;

/**
  * @brief  I2C General Call Mode enumeration
  */
typedef enum
{
    HAL_I2C_GENERALCALL_DISABLE = 0x00000000UL,  /*!< General call disabled */
    HAL_I2C_GENERALCALL_ENABLE  = 0x00000001UL,  /*!< General call enabled  */
} HAL_I2C_GeneralCallTypeDef;

/**
  * @brief  I2C No Stretch Mode enumeration
  */
typedef enum
{
    HAL_I2C_NOSTRETCH_DISABLE = 0x00000000UL,  /*!< Clock stretching enabled   */
    HAL_I2C_NOSTRETCH_ENABLE  = 0x00000001UL,  /*!< Clock stretching disabled  */
} HAL_I2C_NoStretchTypeDef;

/**
  * @brief  I2C Memory Address Size enumeration
  */
typedef enum
{
    HAL_I2C_MEMADD_SIZE_8BIT  = 0x00000001UL,  /*!< 8-bit memory address  */
    HAL_I2C_MEMADD_SIZE_16BIT = 0x00000002UL,  /*!< 16-bit memory address */
} HAL_I2C_MemAddSizeTypeDef;

/**
  * @brief  I2C Init structure definition
  */
typedef struct
{
    uint32_t SCLHigh;             /*!< SCL high-level count, written to BAUD.SCLHCNT[9:0].
                                       Must be non-zero for Master role (Range: 0x0000~0x03FF,
                                       Default Value: 0) */

    uint32_t SCLLow;              /*!< SCL low-level count, written to BAUD.SCLLCNT[9:0].
                                       Must be non-zero for Master role (Range: 0x0000~0x03FF,
                                       Default Value: 0) */

    uint32_t SpikeSuppressionLimit; /*!< Digital filter spike suppression, TIMING.SPKLEN[31:24]
                                         (Range: @ref LL_I2C_SPIKE_SUPPR_MIN ~
                                         @ref LL_I2C_SPIKE_SUPPR_MAX, Default Value: 0;
                                         when 0, HAL programs 0x05) */

    uint32_t SlaveTxSetupDelay;     /*!< Slave TX setup delay, TIMING.SLVSUDAT[23:16]
                                         (Range: @ref LL_I2C_TIMING_DELAY_MIN ~
                                         @ref LL_I2C_TIMING_DELAY_MAX, Default Value: 0) */

    uint32_t RxCaptureDelay;        /*!< RX capture delay, TIMING.SUDAT[15:8]
                                         (Range: @ref LL_I2C_TIMING_DELAY_MIN ~
                                         @ref LL_I2C_TIMING_DELAY_MAX, Default Value: 0) */

    uint32_t TxHoldDelay;           /*!< TX data hold delay, TIMING.HDDAT[7:0]
                                         (Range: @ref LL_I2C_TIMING_DELAY_MIN ~
                                         @ref LL_I2C_TIMING_DELAY_MAX, Default Value: 0) */

    uint32_t TxFifoThreshold;     /*!< TX FIFO empty threshold, written to FIFOCTRL.TXFTLR
                                       (Range: 0x00~0x0F, Default Value: 0x0) */

    uint32_t RxFifoThreshold;     /*!< RX FIFO full threshold, written to FIFOCTRL.RXFTLR
                                       (Range: 0x00~0x10, Default Value: 0x0; 0 is accepted
                                       for compatibility and programmed as 1) */

    uint32_t OwnAddress1;         /*!< First own address, 7-bit or 10-bit depending on
                                       AddressingMode (Range: 0x00~LL_I2C_OWN_ADDRESS_MAX,
                                       Default Value: 0x00) */

    HAL_I2C_AddressingModeTypeDef AddressingMode;      /*!< 7-bit or 10-bit addressing, value of
                                                       @ref I2C_HAL_EC_ADDRESSING_MODE
                                                       (Default Value: HAL_I2C_ADDRESSINGMODE_7BIT) */

    HAL_I2C_DualAddressTypeDef DualAddressMode;     /*!< Dual addressing enable, value of
                                                       @ref I2C_HAL_EC_DUALADDR_MODE
                                                       (Default Value: HAL_I2C_DUALADDRESS_DISABLE) */

    uint32_t OwnAddress2;         /*!< Second own address, used when dual addressing is enabled
                                       (Range: 0x00~LL_I2C_OWN_ADDRESS2_MAX, Default Value: 0x00) */

    uint32_t OwnAddress2Masks;    /*!< Own address 2 acknowledge mask (Range: 0x00~0x07,
                                       Default Value: 0x00) */

    HAL_I2C_GeneralCallTypeDef GeneralCallMode;     /*!< General call enable, value of
                                                       @ref I2C_HAL_EC_GENERALCALL_MODE
                                                       (Default Value: HAL_I2C_GENERALCALL_DISABLE) */

    HAL_I2C_NoStretchTypeDef NoStretchMode;       /*!< Clock stretching disable (No Stretch),
                                                       value of @ref I2C_HAL_EC_NOSTRETCH_MODE;
                                                       Master role also disables MSTCH
                                                       (Default Value: HAL_I2C_NOSTRETCH_DISABLE) */

} HAL_I2C_InitTypeDef;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL I2C Callback ID enumeration definition
  */
typedef enum
{
    HAL_I2C_MASTER_TX_COMPLETE_CB_ID      = 0x00UL,  /*!< Master Tx Transfer completed callback ID  */
    HAL_I2C_MASTER_RX_COMPLETE_CB_ID      = 0x01UL,  /*!< Master Rx Transfer completed callback ID  */
    HAL_I2C_SLAVE_TX_COMPLETE_CB_ID       = 0x02UL,  /*!< Slave Tx Transfer completed callback ID   */
    HAL_I2C_SLAVE_RX_COMPLETE_CB_ID       = 0x03UL,  /*!< Slave Rx Transfer completed callback ID   */
    HAL_I2C_LISTEN_COMPLETE_CB_ID         = 0x04UL,  /*!< Listen Complete callback ID               */
    HAL_I2C_MEM_TX_COMPLETE_CB_ID         = 0x05UL,  /*!< Memory Tx Transfer callback ID            */
    HAL_I2C_MEM_RX_COMPLETE_CB_ID         = 0x06UL,  /*!< Memory Rx Transfer completed callback ID  */
    HAL_I2C_ERROR_CB_ID                   = 0x07UL,  /*!< Error callback ID                         */
    HAL_I2C_ABORT_CB_ID                   = 0x08UL,  /*!< Abort callback ID                         */

    HAL_I2C_MSPINIT_CB_ID                 = 0x09UL,  /*!< Msp Init callback ID                      */
    HAL_I2C_MSPDEINIT_CB_ID               = 0x0AUL   /*!< Msp DeInit callback ID                    */

} HAL_I2C_CallbackIDTypeDef;
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

/**
  * @brief  HAL I2C State definition
  * @note   Each state is a distinct bit; HAL_I2C_STATE_RESET is 0.
  *         Use HAL_I2C_PARAM_UPDATE for exact state transitions.
  */
#define HAL_I2C_StateMaskTypeDef                            uint32_t

#define HAL_I2C_STATE_MASK_RESET                            (0U)            /*!< Peripheral is not yet initialized        */
#define HAL_I2C_STATE_MASK_READY                            (1U << 30U)     /*!< Peripheral initialized and ready for use */
#define HAL_I2C_STATE_MASK_BUSY                             (1U << 29U)     /*!< An internal process is ongoing           */
#define HAL_I2C_STATE_MASK_BUSY_TX                          (1U << 28U)     /*!< Data Transmission process is ongoing     */
#define HAL_I2C_STATE_MASK_BUSY_RX                          (1U << 27U)     /*!< Data Reception process is ongoing        */
#define HAL_I2C_STATE_MASK_LISTEN                           (1U << 26U)     /*!< Address Listen Mode is ongoing           */
#define HAL_I2C_STATE_MASK_BUSY_TX_LISTEN                   (1U << 25U)     /*!< Listen Mode and TX ongoing               */
#define HAL_I2C_STATE_MASK_BUSY_RX_LISTEN                   (1U << 24U)     /*!< Listen Mode and RX ongoing               */
#define HAL_I2C_STATE_MASK_ABORT                            (1U << 23U)     /*!< Abort user request ongoing               */
#define HAL_I2C_STATE_MASK_TIMEOUT                          (1U << 22U)     /*!< Timeout state                            */
#define HAL_I2C_STATE_MASK_ERROR                            (1U << 21U)     /*!< Error state                              */

#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_I2C_STATE_RESET          = HAL_I2C_STATE_MASK_RESET,          /*!< Peripheral is not yet initialized        */
    HAL_I2C_STATE_READY          = HAL_I2C_STATE_MASK_READY,          /*!< Peripheral initialized and ready for use */
    HAL_I2C_STATE_BUSY           = HAL_I2C_STATE_MASK_BUSY,           /*!< An internal process is ongoing           */
    HAL_I2C_STATE_BUSY_TX        = HAL_I2C_STATE_MASK_BUSY_TX,        /*!< Data Transmission process is ongoing     */
    HAL_I2C_STATE_BUSY_RX        = HAL_I2C_STATE_MASK_BUSY_RX,        /*!< Data Reception process is ongoing        */
    HAL_I2C_STATE_LISTEN         = HAL_I2C_STATE_MASK_LISTEN,         /*!< Address Listen Mode is ongoing           */
    HAL_I2C_STATE_BUSY_TX_LISTEN = HAL_I2C_STATE_MASK_BUSY_TX_LISTEN, /*!< Listen Mode and TX ongoing               */
    HAL_I2C_STATE_BUSY_RX_LISTEN = HAL_I2C_STATE_MASK_BUSY_RX_LISTEN, /*!< Listen Mode and RX ongoing               */
    HAL_I2C_STATE_ABORT          = HAL_I2C_STATE_MASK_ABORT,          /*!< Abort user request ongoing               */
    HAL_I2C_STATE_TIMEOUT        = HAL_I2C_STATE_MASK_TIMEOUT,        /*!< Timeout state                            */
    HAL_I2C_STATE_ERROR          = HAL_I2C_STATE_MASK_ERROR           /*!< Error state                              */
} HAL_I2C_StateTypeDef;

_Static_assert(sizeof(HAL_I2C_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");
#else
typedef HAL_I2C_StateMaskTypeDef HAL_I2C_StateTypeDef;
#define HAL_I2C_STATE_RESET          HAL_I2C_STATE_MASK_RESET
#define HAL_I2C_STATE_READY          HAL_I2C_STATE_MASK_READY
#define HAL_I2C_STATE_BUSY           HAL_I2C_STATE_MASK_BUSY
#define HAL_I2C_STATE_BUSY_TX        HAL_I2C_STATE_MASK_BUSY_TX
#define HAL_I2C_STATE_BUSY_RX        HAL_I2C_STATE_MASK_BUSY_RX
#define HAL_I2C_STATE_LISTEN         HAL_I2C_STATE_MASK_LISTEN
#define HAL_I2C_STATE_BUSY_TX_LISTEN HAL_I2C_STATE_MASK_BUSY_TX_LISTEN
#define HAL_I2C_STATE_BUSY_RX_LISTEN HAL_I2C_STATE_MASK_BUSY_RX_LISTEN
#define HAL_I2C_STATE_ABORT          HAL_I2C_STATE_MASK_ABORT
#define HAL_I2C_STATE_TIMEOUT        HAL_I2C_STATE_MASK_TIMEOUT
#define HAL_I2C_STATE_ERROR          HAL_I2C_STATE_MASK_ERROR
#endif

/**
  * @brief  HAL I2C Mode structure definition
  */
typedef enum
{
    HAL_I2C_MODE_NONE               = 0x00UL,  /*!< No I2C communication ongoing             */
    HAL_I2C_MODE_MASTER             = 0x10UL,  /*!< I2C communication is in Master Mode      */
    HAL_I2C_MODE_SLAVE              = 0x20UL,  /*!< I2C communication is in Slave Mode       */
    HAL_I2C_MODE_MEM                = 0x40UL   /*!< I2C communication is in Memory Mode      */
} HAL_I2C_ModeTypeDef;


typedef struct HAL_I2C_HandleStructDef HAL_I2C_HandleTypeDef; /*!< HAL I2C handle structure type */

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
typedef void (*HAL_I2C_CallbackTypeDef)(HAL_I2C_HandleTypeDef *hi2c); /*!< HAL I2C Callback pointer definition */
typedef void (*HAL_I2C_AddrCallbackTypeDef)(HAL_I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */


/**
 * @brief  I2C Handle Structure definition
 */
struct HAL_I2C_HandleStructDef
{
    I2C_TypeDef                 *Instance;      /*!< I2C registers base address.
                                                    This parameter can be a value of @ref I2C_HAL_EC_INSTANCE */

    uint8_t                     *pBuffPtr;      /*!< Pointer to I2C transfer buffer.
                                                    This pointer is used internally to track the current position in the data buffer. */

    uint16_t                    XferSize;       /*!< I2C transfer size.
                                                    Total number of data to be transferred (1 to @ref I2C_MAX_DATA_COUNT_PER_TRANS). */

    volatile uint16_t           XferCount;      /*!< I2C transfer counter.
                                                    Remaining number of data to be transferred. Decremented by the HAL during transfer. */

    volatile uint32_t           XferOptions;    /*!< I2C sequential transfer options.
                                                    This parameter can be a value of @ref I2C_HAL_EC_XFEROPTIONS.
                                                    Used for sequential transfers (multiple frames in one transaction). */

    volatile uint32_t           PreviousState;  /*!< I2C communication Previous state.
                                                    Used internally to save the previous state before starting a new transfer. */

    HAL_StatusTypeDef (*XferISR)(HAL_I2C_HandleTypeDef *hi2c,
                                 uint32_t ITFlags, uint32_t ITSources);
    /*!< I2C transfer IRQ handler function pointer.
         The DMA channels are taken from hTxDMA/hRxDMA; they are NULL when the
         transfer does not run over DMA (and for the direction not using DMA).
         This function pointer is set internally when using DMA mode. */

    volatile HAL_I2C_StateTypeDef  State;          /*!< I2C communication state.
                                                    This parameter can be a value of @ref HAL_I2C_StateTypeDef.
                                                    @ref HAL_I2C_GetState can be used to get this value. */

    volatile HAL_I2C_ModeTypeDef   Mode;           /*!< I2C communication mode.
                                                    This parameter can be a value of @ref HAL_I2C_ModeTypeDef.
                                                    @ref HAL_I2C_GetMode can be used to get this value. */

    volatile uint32_t              ErrorCode;      /*!< I2C Error code.
                                                    This parameter can be a combination of @ref I2C_HAL_EC_ERROR_CODE.
                                                    @ref HAL_I2C_GetError can be used to get this value. */

    volatile uint32_t              Devaddress;     /*!< I2C Target device address.
                                                    7-bit addressing: 0x00-0x7F, 10-bit addressing: 0x000-0x3FF. */

    volatile uint32_t              Memaddress;     /*!< I2C Target memory address.
                                                    Range depends on @ref MemaddSize. For 8-bit: 0x00-0xFF, for 16-bit: 0x0000-0xFFFF. */

    volatile uint32_t              MemaddSize;     /*!< I2C Target memory address size.
                                                    This parameter can be a value of@ref HAL_I2C_MemAddSizeTypeDef. */

    volatile uint32_t              EventCount;     /*!< I2C Event counter.
                                                    Used internally to track the number of events processed. */

    volatile uint32_t              AddrEventCount; /*!< I2C Address Event counter.
                                                    Used internally to track the number of address match events. */

    const void                 *pUserData;     /*!< Pointer to user data. */
#if defined (USE_HAL_I2C_DMA) && (USE_HAL_I2C_DMA == 1)
    HAL_DMA_HandleTypeDef      *hTxDMA;        /*!< Tx DMA handle */
    HAL_DMA_HandleTypeDef      *hRxDMA;        /*!< Rx DMA handle */
#endif /* USE_HAL_I2C_DMA */


#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    HAL_I2C_CallbackTypeDef MasterTxCpltCallback;
    HAL_I2C_CallbackTypeDef MasterRxCpltCallback;
    HAL_I2C_CallbackTypeDef SlaveTxCpltCallback;
    HAL_I2C_CallbackTypeDef SlaveRxCpltCallback;
    HAL_I2C_CallbackTypeDef ListenCpltCallback;
    HAL_I2C_CallbackTypeDef MemTxCpltCallback;
    HAL_I2C_CallbackTypeDef MemRxCpltCallback;
    HAL_I2C_CallbackTypeDef ErrorCallback;
    HAL_I2C_CallbackTypeDef AbortCpltCallback;
    HAL_I2C_AddrCallbackTypeDef AddrCallback;
    HAL_I2C_CallbackTypeDef MspInitCallback;
    HAL_I2C_CallbackTypeDef MspDeInitCallback;
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

};

/**
  * @}
  */



/* Exported constants --------------------------------------------------------*/
/** @defgroup I2C_HAL_Exported_Constants I2C HAL Exported Constants
  * @{
  */

/** @defgroup I2C_HAL_EC_XFEROPTIONS I2C Sequential Transfer Options
  * @{
  */
/* The HAL sequential transfer options map directly to the LL layer definitions */
#define HAL_I2C_FIRST_FRAME                     LL_I2C_FIRST_FRAME           /*!< First frame of a sequence     */
#define HAL_I2C_FIRST_AND_NEXT_FRAME            LL_I2C_FIRST_AND_NEXT_FRAME  /*!< First and next frame          */
#define HAL_I2C_NEXT_FRAME                      LL_I2C_NEXT_FRAME            /*!< Next frame                    */
#define HAL_I2C_FIRST_AND_LAST_FRAME            LL_I2C_FIRST_AND_LAST_FRAME  /*!< First and last frame          */
#define HAL_I2C_LAST_FRAME                      LL_I2C_LAST_FRAME            /*!< Last frame with STOP          */
#define HAL_I2C_LAST_FRAME_NO_STOP              LL_I2C_LAST_FRAME_NO_STOP    /*!< Last frame without STOP       */
#define HAL_I2C_OTHER_FRAME                     LL_I2C_OTHER_FRAME           /*!< Intermediate frame in sequence*/
#define HAL_I2C_OTHER_AND_LAST_FRAME            LL_I2C_OTHER_AND_LAST_FRAME  /*!< Intermediate and last frame   */
/**
  * @}
  */

/** @defgroup I2C_HAL_EC_IT I2C Interrupt Mask
  * @{
  */
#define HAL_I2C_IT_RXFIE      LL_I2C_IT_RXFIE     /*!< RX FIFO threshold interrupt */
#define HAL_I2C_IT_TXEIE      LL_I2C_IT_TXEIE     /*!< TX FIFO empty interrupt */
#define HAL_I2C_IT_RXOFIE     LL_I2C_IT_RXOFIE    /*!< RX FIFO overflow interrupt */
#define HAL_I2C_IT_RXUFIE     LL_I2C_IT_RXUFIE    /*!< RX FIFO underflow interrupt */
#define HAL_I2C_IT_TXOFIE     LL_I2C_IT_TXOFIE    /*!< TX FIFO overflow interrupt */
#define HAL_I2C_IT_TXUFIE     LL_I2C_IT_TXUFIE    /*!< slave TX FIFO underflow interrupt */
#define HAL_I2C_IT_ARBFIE     LL_I2C_IT_ARBFIE    /*!< arbitration fail interrupt */
#define HAL_I2C_IT_BUSEIE     LL_I2C_IT_BUSEIE    /*!< bus error interrupt */
#define HAL_I2C_IT_MDEIE      LL_I2C_IT_MDEIE     /*!< transmission done interrupt */
#define HAL_I2C_IT_TXADIE     LL_I2C_IT_TXADIE    /*!< slave TX address matching interrupt */
#define HAL_I2C_IT_RXADIE     LL_I2C_IT_RXADIE    /*!< slave RX address matching interrupt */
#define HAL_I2C_IT_STDETIE    LL_I2C_IT_STDETIE   /*!< detected START/RESTART interrupt */
#define HAL_I2C_IT_SPDETIE    LL_I2C_IT_SPDETIE   /*!< detected STOP interrupt */
#define HAL_I2C_IT_RSDETIE    LL_I2C_IT_RSDETIE   /*!< detected RESTART interrupt */
#define HAL_I2C_IT_NACKIE     LL_I2C_IT_NACKIE    /*!< detected NACK interrupt */
#define HAL_I2C_IT_ALDETIE    LL_I2C_IT_ALDETIE   /*!< detected SBA signal interrupt */
#define HAL_I2C_IT_MEXTOIE    LL_I2C_IT_MEXTOIE   /*!< master detected timeout interrupt */
#define HAL_I2C_IT_SEXTOIE    LL_I2C_IT_SEXTOIE   /*!< slave detected timeout interrupt */
#define HAL_I2C_IT_PECRXIE    LL_I2C_IT_PECRXIE   /*!< received PEC with checksum error interrupt */
#define HAL_I2C_IT_RXGCIE     LL_I2C_IT_RXGCIE    /*!< slave RX general call interrupt */
#define HAL_I2C_IT_MTXAIE     LL_I2C_IT_MTXAIE    /*!< master TX address done interrupt */
#define HAL_I2C_IT_SWTXIE     LL_I2C_IT_SWTXIE    /*!< slave hold SCL low for waiting data interrupt */
#define HAL_I2C_IT_MOHIE      LL_I2C_IT_MOHIE     /*!< master hold SCL low interrupt */
#define HAL_I2C_IT_BTOIE      LL_I2C_IT_BTOIE     /*!< bus timeout interrupt */
/**
  * @}
  */ /* I2C_HAL_EC_IT */

/** @defgroup I2C_HAL_EC_FLAG I2C Interrupt Pending Flag
  * @{
  */
#define HAL_I2C_FLAG_RXFI     LL_I2C_FLAG_RXFI    /*!< RX FIFO threshold reached */
#define HAL_I2C_FLAG_TXEI     LL_I2C_FLAG_TXEI    /*!< TX FIFO empty */
#define HAL_I2C_FLAG_RXOFI    LL_I2C_FLAG_RXOFI   /*!< RX FIFO overflow */
#define HAL_I2C_FLAG_RXUFI    LL_I2C_FLAG_RXUFI   /*!< RX FIFO underflow */
#define HAL_I2C_FLAG_TXOFI    LL_I2C_FLAG_TXOFI   /*!< TX FIFO overflow */
#define HAL_I2C_FLAG_TXUFI    LL_I2C_FLAG_TXUFI   /*!< slave TX FIFO underflow */
#define HAL_I2C_FLAG_ARBFI    LL_I2C_FLAG_ARBFI   /*!< arbitration fail */
#define HAL_I2C_FLAG_BUSEI    LL_I2C_FLAG_BUSEI   /*!< bus error */
#define HAL_I2C_FLAG_MDEI     LL_I2C_FLAG_MDEI    /*!< transmission done */
#define HAL_I2C_FLAG_TXADI    LL_I2C_FLAG_TXADI   /*!< slave TX address matching */
#define HAL_I2C_FLAG_RXADI    LL_I2C_FLAG_RXADI   /*!< slave RX address matching */
#define HAL_I2C_FLAG_STDETI   LL_I2C_FLAG_STDETI  /*!< START/RESTART detected */
#define HAL_I2C_FLAG_SPETI    LL_I2C_FLAG_SPETI   /*!< STOP detected */
#define HAL_I2C_FLAG_RSDETI   LL_I2C_FLAG_RSDETI  /*!< RESTART detected */
#define HAL_I2C_FLAG_NACKI    LL_I2C_FLAG_NACKI   /*!< NACK detected */
#define HAL_I2C_FLAG_ALDETI   LL_I2C_FLAG_ALDETI  /*!< SBA signal detected */
#define HAL_I2C_FLAG_MEXTOI   LL_I2C_FLAG_MEXTOI  /*!< master detected timeout */
#define HAL_I2C_FLAG_SEXTOI   LL_I2C_FLAG_SEXTOI  /*!< slave detected timeout */
#define HAL_I2C_FLAG_PECRXI   LL_I2C_FLAG_PECRXI  /*!< received PEC with checksum error */
#define HAL_I2C_FLAG_RXGCI    LL_I2C_FLAG_RXGCI   /*!< slave RX general call */
#define HAL_I2C_FLAG_MTXAI    LL_I2C_FLAG_MTXAI   /*!< master TX address done */
#define HAL_I2C_FLAG_SWTXI    LL_I2C_FLAG_SWTXI   /*!< slave hold SCL low for waiting data */
#define HAL_I2C_FLAG_MOHI     LL_I2C_FLAG_MOHI    /*!< master hold SCL low */
#define HAL_I2C_FLAG_BTOI     LL_I2C_FLAG_BTOI    /*!< bus timeout */
/**
  * @}
  */ /* I2C_HAL_EC_FLAG */

/** @defgroup I2C_HAL_EC_ERROR_CODE I2C Error Code Definition
  * @{
  */
#define HAL_I2C_ERROR_NONE                  (0x00000000UL)  /*!< No error                    */
#define HAL_I2C_ERROR_BERR                  (0x00000001UL)  /*!< Bus error                   */
#define HAL_I2C_ERROR_ARLO                  (0x00000002UL)  /*!< Arbitration lost error      */
#define HAL_I2C_ERROR_AF                    (0x00000004UL)  /*!< Acknowledge failure error   */
#define HAL_I2C_ERROR_OVR                   (0x00000008UL)  /*!< Overrun/Underrun error      */
#define HAL_I2C_ERROR_DMA                   (0x00000010UL)  /*!< DMA transfer error          */
#define HAL_I2C_ERROR_TIMEOUT               (0x00000020UL)  /*!< Timeout error               */
#define HAL_I2C_ERROR_SIZE                  (0x00000040UL)  /*!< Size management error       */
#define HAL_I2C_ERROR_DMA_PARAM             (0x00000080UL)  /*!< DMA Parameter Error         */
#define HAL_I2C_ERROR_INVALID_PARAM         (0x00000200UL)  /*!< Invalid parameter error     */
#define HAL_I2C_ERROR_ALERT                 (0x00000400UL)  /*!< SMBus alert error           */
#define HAL_I2C_ERROR_BUSTIMEOUT            (0x00000800UL)  /*!< Bus timeout error           */
#define HAL_I2C_ERROR_PECERR                (0x00001000UL)  /*!< PEC error                   */
#define HAL_I2C_ERROR_RXOVR                 (0x00002000UL)  /*!< RX FIFO overflow            */
#define HAL_I2C_ERROR_RXUNF                 (0x00004000UL)  /*!< RX FIFO underflow           */
#define HAL_I2C_ERROR_TXOVR                 (0x00008000UL)  /*!< TX FIFO overflow            */
#define HAL_I2C_ERROR_TXUNF                 (0x00010000UL)  /*!< TX FIFO underflow           */


#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#define HAL_I2C_ERROR_INVALID_CALLBACK      (0x00000100UL)  /*!< Invalid Callback error      */
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup I2C_HAL_EC_OWN_ADDRESS I2C Own Address Boundary
  * @{
  */
/**
  * @}
  */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup I2C_HAL_Private_Macros I2C HAL Private Macros
  * @{
  */

/**
  * @brief  Check I2C addressing mode.
  * @param[in]  mode  I2C addressing mode.
  * @retval 0: Invalid, 1: Valid
  * @note   Use only with @ref HAL_I2C_ADDRESSINGMODE_7BIT or
  *         @ref HAL_I2C_ADDRESSINGMODE_10BIT.
  */
#define IS_HAL_I2C_ADDRESSING_MODE(mode)      (((mode) == HAL_I2C_ADDRESSINGMODE_7BIT) || \
                                                    ((mode) == HAL_I2C_ADDRESSINGMODE_10BIT))

/**
  * @brief  Check I2C dual addressing mode.
  * @param[in]  address  I2C dual addressing mode.
  * @retval 0: Invalid, 1: Valid
  * @note   Use only with @ref HAL_I2C_DUALADDRESS_DISABLE or
  *         @ref HAL_I2C_DUALADDRESS_ENABLE.
  */
#define IS_HAL_I2C_DUAL_ADDRESS(address)      (((address) == HAL_I2C_DUALADDRESS_DISABLE) || \
                                                    ((address) == HAL_I2C_DUALADDRESS_ENABLE))

/**
  * @brief  Check I2C own address 1 value.
  * @param[in]  address1  I2C own address 1.
  * @retval 0: Invalid, 1: Valid
 * @note   Valid range: 0x00 to @ref LL_I2C_OWN_ADDRESS_MAX (10-bit).
 * @note   This HAL-level check forwards to the LL-layer validation macro.
 */
#define IS_HAL_I2C_OWN_ADDRESS1(address1)      IS_LL_I2C_OWN_ADDRESS1(address1)

/**
 * @brief  Check I2C own address 2 value.
 * @param[in]  address2  I2C own address 2.
 * @retval 0: Invalid, 1: Valid
 * @note   Valid range: 0x00 to @ref LL_I2C_OWN_ADDRESS2_MAX (7-bit).
 * @note   This HAL-level check forwards to the LL-layer validation macro.
 */
#define IS_HAL_I2C_OWN_ADDRESS2(address2)      IS_LL_I2C_OWN_ADDRESS2(address2)

/**
 * @brief  Check I2C own address 2 acknowledge mask.
 * @param[in]  mask  Own address 2 mask.
 * @retval 0: Invalid, 1: Valid
 * @note   Valid range: 0x00 to 0x07.
 */
#define IS_HAL_I2C_OWN_ADDRESS2_MASK(mask)      ((mask) <= 0x07U)

/**
 * @brief  Check I2C TX FIFO threshold.
 * @param[in]  threshold  TX FIFO empty threshold.
 * @retval 0: Invalid, 1: Valid
 * @note   Valid range: 0x00 to 0x0F.
 */
#define IS_HAL_I2C_TXFIFO_THRESHOLD(threshold)  ((threshold) <= 0x0FU)

/**
 * @brief  Check I2C RX FIFO threshold.
 * @param[in]  threshold  RX FIFO full threshold.
 * @retval 0: Invalid, 1: Valid
 * @note   Valid range: 0x00 to 0x10; 0 is accepted for compatibility and maps to 1.
 */
#define IS_HAL_I2C_RXFIFO_THRESHOLD(threshold)  ((threshold) <= 0x10U)

/**
  * @brief  Check I2C general call mode.
  * @param[in]  call  I2C general call mode.
  * @retval 0: Invalid, 1: Valid
  * @note   Use only with @ref HAL_I2C_GENERALCALL_DISABLE or
  *         @ref HAL_I2C_GENERALCALL_ENABLE.
  */
#define IS_HAL_I2C_GENERAL_CALL(call)         (((call) == HAL_I2C_GENERALCALL_DISABLE) || \
                                                    ((call) == HAL_I2C_GENERALCALL_ENABLE))

/**
  * @brief  Check I2C dual addressing mode (alias).
  * @param[in]  mode  I2C dual addressing mode.
  * @retval 0: Invalid, 1: Valid
  * @note   Alias of @ref IS_HAL_I2C_DUAL_ADDRESS.
  */
#define IS_HAL_I2C_DUALADDRESS(mode)          IS_HAL_I2C_DUAL_ADDRESS(mode)

/**
  * @brief  Check I2C No Stretch mode.
  * @param[in]  stretch  I2C No Stretch mode.
  * @retval 0: Invalid, 1: Valid
  * @note   Use only with @ref HAL_I2C_NOSTRETCH_DISABLE or
  *         @ref HAL_I2C_NOSTRETCH_ENABLE.
  */
#define IS_HAL_I2C_NO_STRETCH(stretch)        (((stretch) == HAL_I2C_NOSTRETCH_DISABLE) || \
                                                    ((stretch) == HAL_I2C_NOSTRETCH_ENABLE))

/**
  * @brief  Check I2C memory address size.
  * @param[in]  size  I2C memory address size.
  * @retval 0: Invalid, 1: Valid
  * @note   Use only with @ref HAL_I2C_MEMADD_SIZE_8BIT or
  *         @ref HAL_I2C_MEMADD_SIZE_16BIT.
  */
#define IS_HAL_I2C_MEMADD_SIZE(size)          (((size) == HAL_I2C_MEMADD_SIZE_8BIT) || \
                                                    ((size) == HAL_I2C_MEMADD_SIZE_16BIT))

/**
  * @brief  Check I2C 7-bit device address.
  * @param[in]  address  Target device address.
  * @retval 0: Invalid, 1: Valid
  */
#define IS_HAL_I2C_DEV_ADDRESS_7BIT(address)  ((address) <= 0x7FU)

/**
  * @brief  Check I2C 10-bit device address.
  * @param[in]  address  Target device address.
  * @retval 0: Invalid, 1: Valid
  */
#define IS_HAL_I2C_DEV_ADDRESS_10BIT(address) ((address) <= 0x3FFU)

/**
  * @brief  Check I2C device address against the master addressing mode.
  * @param[in]  hi2c     Pointer to a HAL_I2C_HandleTypeDef structure.
  * @param[in]  address  Target device address.
  * @retval 0: Invalid, 1: Valid
  */
#define IS_HAL_I2C_DEV_ADDRESS(hi2c, address) \
    (((LL_I2C_GetMasterAddressingMode((hi2c)->Instance) == LL_I2C_ADDRESSINGMODE_7BIT) ? \
      IS_HAL_I2C_DEV_ADDRESS_7BIT(address) : IS_HAL_I2C_DEV_ADDRESS_10BIT(address)))

/**
  * @brief  Check I2C transfer options.
  * @param[in]  request  I2C transfer options.
  * @retval 0: Invalid, 1: Valid
  * @note   Use only with values from @ref I2C_HAL_EC_XFEROPTIONS.
  */
#define IS_HAL_I2C_TRANSFER_OPTIONS(request)  (((request) == HAL_I2C_FIRST_FRAME)          || \
                                                    ((request) == HAL_I2C_FIRST_AND_NEXT_FRAME) || \
                                                    ((request) == HAL_I2C_NEXT_FRAME)           || \
                                                    ((request) == HAL_I2C_FIRST_AND_LAST_FRAME) || \
                                                    ((request) == HAL_I2C_LAST_FRAME)           || \
                                                    ((request) == HAL_I2C_LAST_FRAME_NO_STOP)   || \
                                                    ((request) == HAL_I2C_OTHER_FRAME)          || \
                                                    ((request) == HAL_I2C_OTHER_AND_LAST_FRAME))

/**
  * @brief  Check I2C instance.
  * @param[in]  instance  I2C instance.
  * @retval 0: Invalid, 1: Valid
  * @note   Use only with one of @ref I2C0, @ref I2C1, @ref I2C2.
  */
#define IS_HAL_I2C_ALL_INSTANCE(instance)     (((instance) == I2C0) || \
                                                    ((instance) == I2C1) || \
                                                    ((instance) == I2C2))

/**
  * @brief  Reset I2C handle state.
  * @param[in]  hi2c  I2C Handle.
  * @return None
  * @note   Resets State, MspInitCallback, and MspDeInitCallback (when
  *         USE_HAL_I2C_REGISTER_CALLBACKS = 1). Use to fully tear down
  *         a handle before re-Init.
  */
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#define HAL_I2C_RESET_HANDLE_STATE(hi2c)  do{                                             \
                                                        (hi2c)->State = HAL_I2C_STATE_RESET; \
                                                        (hi2c)->MspInitCallback = NULL;      \
                                                        (hi2c)->MspDeInitCallback = NULL;    \
                                                      } while(0)
#else
#define HAL_I2C_RESET_HANDLE_STATE(hi2c)  ((hi2c)->State = HAL_I2C_STATE_RESET)
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

/**
  * @brief  Enable the specified I2C interrupt.
  * @param[in]  hi2c     I2C Handle.
  * @param[in]  interrupt  I2C interrupt source to enable
  *                            (combination of @ref I2C_LL_EC_INT).
  * @return None
  */
#define HAL_I2C_ENABLE_IT(hi2c, interrupt)      \
        LL_I2C_EnableIT((hi2c)->Instance, (interrupt))

/**
  * @brief  Disable the specified I2C interrupt.
  * @param[in]  hi2c     I2C Handle.
  * @param[in]  interrupt  I2C interrupt source to disable
  *                            (combination of @ref I2C_LL_EC_INT).
  * @return None
  */
#define HAL_I2C_DISABLE_IT(hi2c, interrupt)     \
        LL_I2C_DisableIT((hi2c)->Instance, (interrupt))

/**
  * @brief  Enable the I2C peripheral.
  * @param[in]  hi2c  I2C Handle.
  * @return None
  * @note   Must be called after the peripheral is configured; the bus
  *         starts participating in I2C traffic once enabled.
  */
#define HAL_I2C_ENABLE(hi2c)                        LL_I2C_Enable((hi2c)->Instance)

/**
  * @brief  Disable the I2C peripheral.
  * @param[in]  hi2c  I2C Handle.
  * @return None
  * @note   Disconnects the peripheral from the bus. Use for safe
  *         re-configuration or low-power entry.
  */
#define HAL_I2C_DISABLE(hi2c)                       LL_I2C_Disable((hi2c)->Instance)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup I2C_HAL_Exported_Functions I2C HAL Exported Functions
  * @{
  */

/** @defgroup I2C_HAL_Exported_Functions_Group1 Initialization and De-initialization functions
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_I2C_Init(HAL_I2C_HandleTypeDef *hi2c, I2C_TypeDef *I2Cx, HAL_I2C_InitTypeDef *Init);
HAL_StatusTypeDef HAL_I2C_DeInit(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspInit(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(HAL_I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef HAL_I2C_ResetFIFO(HAL_I2C_HandleTypeDef *hi2c);



#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_I2C_RegisterCallback(HAL_I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID,
                                            HAL_I2C_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_I2C_UnRegisterCallback(HAL_I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_I2C_RegisterAddrCallback(HAL_I2C_HandleTypeDef *hi2c, HAL_I2C_AddrCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_I2C_UnRegisterAddrCallback(HAL_I2C_HandleTypeDef *hi2c);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */


/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group2 IO operation functions
  * @{
  */
/* IO operation functions *****************************************************/
/******* Blocking mode: Polling */
HAL_StatusTypeDef HAL_I2C_Master_Transmit(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                           uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                          uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                          uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                         uint16_t Size, uint32_t Timeout);

/******* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                        uint32_t Trials, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                              uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(HAL_I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                            uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                             uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(HAL_I2C_HandleTypeDef *hi2c, uint8_t *pData,
                                            uint16_t Size);
											
/******* Non-Blocking mode: DMA */
#if defined (USE_HAL_I2C_DMA) && (USE_HAL_I2C_DMA == 1)
HAL_StatusTypeDef HAL_I2C_SetTxDMA(HAL_I2C_HandleTypeDef *hi2c, HAL_DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_I2C_SetRxDMA(HAL_I2C_HandleTypeDef *hi2c, HAL_DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                              uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                             uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                             uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(HAL_I2C_HandleTypeDef *hi2c,
                                            uint8_t *pData, uint16_t Size);
#endif




/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/


/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group4 IRQ Handler and Callbacks
  * @{
  */
/* IRQ Handler and Callbacks **************************************************/
void HAL_I2C_EV_IRQHandler(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_ER_IRQHandler(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_IRQHandler(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterTxCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveTxCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveRxCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_AddrCallback(HAL_I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
void HAL_I2C_ListenCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemTxCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemRxCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_AbortCpltCallback(HAL_I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(HAL_I2C_HandleTypeDef *hi2c);
/**
  * @}
  */

/** @defgroup I2C_HAL_Exported_Functions_Group5 Peripheral State, Mode and Error functions
  * @{
  */
/* Peripheral State, Mode and Error functions *********************************/
HAL_I2C_StateTypeDef HAL_I2C_GetState(const HAL_I2C_HandleTypeDef *hi2c);
HAL_I2C_ModeTypeDef  HAL_I2C_GetMode(const HAL_I2C_HandleTypeDef *hi2c);
uint32_t             HAL_I2C_GetError(const HAL_I2C_HandleTypeDef *hi2c);
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
  * @}
  */

#endif /* defined (I2C0) || defined (I2C1) || defined (I2C2) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_I2C_H_ */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE***********/
