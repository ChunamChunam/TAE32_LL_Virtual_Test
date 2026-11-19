/**
  ******************************************************************************
  * @file    tae32f561x_hal_dma.h
  * @author  Tai-Action SD Team
  * @brief   Header file of DMA HAL module.
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
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F561X_HAL_DMA_H_
#define _TAE32F561X_HAL_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_hal_def.h"
#include "tae32f561x_ll_dma.h"

/** @addtogroup TAE32F561x_HAL_Driver
  * @{
  */

/** @addtogroup DMA_HAL
  * @brief DMA HAL module driver
  * @{
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA_HAL_Exported_Constants DMA HAL Exported Constants
  * @{
  */


/** @defgroup DMA_HAL_EC_PARAM_CHECK DMA HAL Parameter Check Switch
  * @{
  */
#ifndef TAE32_USE_HAL_DMA_CHECK_PARAM
#define TAE32_USE_HAL_DMA_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_DMA_CHECK_PARAM != 1) && (TAE32_USE_HAL_DMA_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_DMA_CHECK_PARAM
#define TAE32_USE_HAL_DMA_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_DMA_CHECK_PARAM */

#define HAL_DMA_PARAM_CHECK(expression)       \
        if (TAE32_USE_HAL_DMA_CHECK_PARAM) {  \
            expression;                       \
        }
/**
  * @}
  */


/**
 * @brief Updates a DMA HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the DMA process
 * state check feature is enabled (TAE32_USE_HAL_DMA_CHECK_PROCESS_STATE == 1),
 * it validates that the current value of @p upd_parm equals @p check_value
 * before updating; if validation fails, @p failed_expression is executed.
 * If the feature is disabled, the parameter is directly assigned.
 *
 * @param upd_parm          Variable to be updated.
 * @param check_value       Expected current value for validation (used only when
 *                          the check feature is enabled).
 * @param new_value         New value to assign to @p upd_parm.
 * @param failed_expression Expression to evaluate if validation fails (used only
 *                          when the check feature is enabled).
 *
 * @note When TAE32_USE_HAL_DMA_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_DMA_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_DMA_CHECK_PROCESS_STATE == 1)
#define HAL_DMA_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_DMA_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        do {                                                                      \
            if ((upd_parm) != (check_value)) {                                    \
                failed_expression;                                                \
                break;                                                            \
            } else {                                                              \
                (upd_parm) = (new_value);                                         \
            }                                                                     \
        } while(0)    
#endif


/**
  * @brief DMA State definition
  */
#define HAL_DMA_StateMaskTypeDef                            uint32_t

#define HAL_DMA_STATE_MASK_RESET                            (0U)            /*!< DMA not initialized / released */
#define HAL_DMA_STATE_MASK_READY                            (1U << 30U)     /*!< DMA initialized and ready       */
#define HAL_DMA_STATE_MASK_BUSY                             (1U << 29U)     /*!< DMA transfer in progress         */
#define HAL_DMA_STATE_MASK_ERROR                            (1U << 21U)     /*!< DMA transfer error               */



/** @defgroup DMA_HAL_EC_ERROR DMA Error Code
  * @{
  */
#define HAL_DMA_ERROR_NONE                  (0x00000000UL)  /*!< No error                   */
#define HAL_DMA_ERROR_TE                    (0x00000001UL)  /*!< Transfer error             */
#define HAL_DMA_ERROR_TIMEOUT               (0x00000002UL)  /*!< Timeout error              */
/**
  * @}
  */

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup DMA_HAL_Exported_Types DMA HAL Exported Types
  * @{
  */


/** @defgroup DMA_HAL_EC_PERIPH_BUS DMA Peripheral Bus
  * @{
  */
typedef enum 
{
    HAL_DMA_PERIPH_BUS_AHB_MST1 = LL_DMA_PERIPH_BUS_AHB_MST1,  /*!< AHB master bus 1 */
    HAL_DMA_PERIPH_BUS_AHB_MST2 = LL_DMA_PERIPH_BUS_AHB_MST2,  /*!< AHB master bus 2 */
} HAL_DMA_PeriphBusTypeDef;
/**
  * @}
  */

/** @defgroup DMA_HAL_EC_BURST_LEN DMA Burst Length
  * @{
  */
typedef enum 
{
    HAL_DMA_BURST_LEN_1   = LL_DMA_BURST_LEN_1,    /*!< 1-beat burst */
    HAL_DMA_BURST_LEN_4   = LL_DMA_BURST_LEN_4,    /*!< 4-beat burst */
    HAL_DMA_BURST_LEN_8   = LL_DMA_BURST_LEN_8,    /*!< 8-beat burst */
    HAL_DMA_BURST_LEN_16  = LL_DMA_BURST_LEN_16,   /*!< 16-beat burst */
} HAL_DMA_BurstLenTypeDef;
/**
  * @}
  */

/** @defgroup DMA_HAL_EC_TRANS_TYPE DMA Transfer Type
  * @{
  */
typedef enum 
{
    HAL_DMA_TRANS_TYPE_M2M = LL_DMA_TRANS_TYPE_M2M,  /*!< Memory to Memory */
    HAL_DMA_TRANS_TYPE_M2P = LL_DMA_TRANS_TYPE_M2P,  /*!< Memory to Peripheral */
    HAL_DMA_TRANS_TYPE_P2M = LL_DMA_TRANS_TYPE_P2M,  /*!< Peripheral to Memory */
    HAL_DMA_TRANS_TYPE_P2P = LL_DMA_TRANS_TYPE_P2P,  /*!< Peripheral to Peripheral */
} HAL_DMA_TransTypeTypeDef;
/**
  * @}
  */

/** @defgroup DMA_HAL_EC_TRANS_MODE DMA Transfer Mode
  * @{
  */
typedef enum 
{
    HAL_DMA_TRANS_MODE_SINGLE   = LL_DMA_TRANS_MODE_SINGLE,    /*!< Single transfer */
    HAL_DMA_TRANS_MODE_CONTINUE = LL_DMA_TRANS_MODE_CONTINUE,  /*!< Continuous transfer */
} HAL_DMA_TransModeTypeDef;
/**
  * @}
  */

/** @defgroup DMA_HAL_EC_ADDR_MODE DMA Address Mode
  * @{
  */
typedef enum 
{
    HAL_DMA_ADDR_MODE_INC = LL_DMA_ADDR_MODE_INC,  /*!< Address increment */
    HAL_DMA_ADDR_MODE_FIX = LL_DMA_ADDR_MODE_FIX,  /*!< Address fixed */
} HAL_DMA_AddrModeTypeDef;
/**
  * @}
  */

/** @defgroup DMA_HAL_EC_DATA_WIDTH DMA Data Width
  * @{
  */
typedef enum 
{
    HAL_DMA_DATA_WIDTH_BYTE     = LL_DMA_DATA_WIDTH_BYTE,       /*!< 8-bit  transfer width */
    HAL_DMA_DATA_WIDTH_HALFWORD = LL_DMA_DATA_WIDTH_HALFWORD,   /*!< 16-bit transfer width */
    HAL_DMA_DATA_WIDTH_WORD     = LL_DMA_DATA_WIDTH_WORD,       /*!< 32-bit transfer width */
} HAL_DMA_DataWidthTypeDef;
/**
  * @}
  */

/** @defgroup DMA_HAL_EC_PRIORITY DMA Priority
  * @{
  */

typedef enum 
{
    HAL_DMA_PRIORITY_LEVEL_0    = LL_DMA_PRIORITY_LEVEL_0,      /*!< Priority level 0 */
    HAL_DMA_PRIORITY_LEVEL_1    = LL_DMA_PRIORITY_LEVEL_1,      /*!< Priority level 1 */
    HAL_DMA_PRIORITY_LEVEL_2    = LL_DMA_PRIORITY_LEVEL_2,      /*!< Priority level 2 */
    HAL_DMA_PRIORITY_LEVEL_3    = LL_DMA_PRIORITY_LEVEL_3,      /*!< Priority level 3 */
    HAL_DMA_PRIORITY_LEVEL_4    = LL_DMA_PRIORITY_LEVEL_4,      /*!< Priority level 4 */
    HAL_DMA_PRIORITY_LEVEL_5    = LL_DMA_PRIORITY_LEVEL_5,      /*!< Priority level 5 */
    HAL_DMA_PRIORITY_LEVEL_6    = LL_DMA_PRIORITY_LEVEL_6,      /*!< Priority level 6 */
    HAL_DMA_PRIORITY_LEVEL_7    = LL_DMA_PRIORITY_LEVEL_7,      /*!< Priority level 7 */
} HAL_DMA_PriorityTypeDef;

/**
  * @}
  */


/** @defgroup DMA_HAL_EC_CHANNEL DMA Channel
  * @{
  */
typedef enum 
{
    HAL_DMA_CHANNEL_0       = LL_DMA_CHANNEL_0,       /*!< DMA Channel 0 */
    HAL_DMA_CHANNEL_1       = LL_DMA_CHANNEL_1,       /*!< DMA Channel 1 */
    HAL_DMA_CHANNEL_2       = LL_DMA_CHANNEL_2,       /*!< DMA Channel 2 */
    HAL_DMA_CHANNEL_3       = LL_DMA_CHANNEL_3,       /*!< DMA Channel 3 */
    HAL_DMA_CHANNEL_4       = LL_DMA_CHANNEL_4,       /*!< DMA Channel 4 */
    HAL_DMA_CHANNEL_5       = LL_DMA_CHANNEL_5,       /*!< DMA Channel 5 */
    HAL_DMA_CHANNEL_NUMS    = LL_DMA_CHANNEL_NUMS,
    HAL_DMA_CHANNEL_INVALID = HAL_DMA_CHANNEL_NUMS,    /*!< Invalid (If there are available channels, they will be auto-allocated) */
} HAL_DMA_ChannelTypeDef;
/**
  * @}
  */

#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_DMA_STATE_RESET     = HAL_DMA_STATE_MASK_RESET,     /*!< DMA not initialized / released */
    HAL_DMA_STATE_READY     = HAL_DMA_STATE_MASK_READY,     /*!< DMA initialized and ready       */
    HAL_DMA_STATE_BUSY      = HAL_DMA_STATE_MASK_BUSY,      /*!< DMA transfer in progress         */
    HAL_DMA_STATE_ERROR     = HAL_DMA_STATE_MASK_ERROR,     /*!< DMA transfer error               */
} HAL_DMA_StateTypeDef;

_Static_assert(sizeof(HAL_DMA_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else
typedef HAL_DMA_StateMaskTypeDef        HAL_DMA_StateTypeDef;
#define HAL_DMA_STATE_RESET             HAL_DMA_STATE_MASK_RESET
#define HAL_DMA_STATE_READY             HAL_DMA_STATE_MASK_READY
#define HAL_DMA_STATE_BUSY              HAL_DMA_STATE_MASK_BUSY
#define HAL_DMA_STATE_ERROR             HAL_DMA_STATE_MASK_ERROR
#endif



/** @defgroup DMA_HAL_EC_HANDSHAKE_IFC DMA Handshake Interface
  * @{
  */
typedef enum 
{
    HAL_DMA_HS_IFC_MEM           = LL_DMA_HS_IFC_MEM,
    HAL_DMA_HS_IFC_I2C0_TX       = LL_DMA_HS_IFC_I2C0_TX,
    HAL_DMA_HS_IFC_I2C0_RX       = LL_DMA_HS_IFC_I2C0_RX,
    HAL_DMA_HS_IFC_I2C1_TX       = LL_DMA_HS_IFC_I2C1_TX,
    HAL_DMA_HS_IFC_I2C1_RX       = LL_DMA_HS_IFC_I2C1_RX,
    HAL_DMA_HS_IFC_I2C2_TX       = LL_DMA_HS_IFC_I2C2_TX,
    HAL_DMA_HS_IFC_I2C2_RX       = LL_DMA_HS_IFC_I2C2_RX,
    HAL_DMA_HS_IFC_UART0_TX      = LL_DMA_HS_IFC_UART0_TX,
    HAL_DMA_HS_IFC_UART0_RX      = LL_DMA_HS_IFC_UART0_RX,
    HAL_DMA_HS_IFC_UART1_TX      = LL_DMA_HS_IFC_UART1_TX,
    HAL_DMA_HS_IFC_UART1_RX      = LL_DMA_HS_IFC_UART1_RX,
    HAL_DMA_HS_IFC_UART2_TX      = LL_DMA_HS_IFC_UART2_TX,
    HAL_DMA_HS_IFC_UART2_RX      = LL_DMA_HS_IFC_UART2_RX,
    HAL_DMA_HS_IFC_UART3_TX      = LL_DMA_HS_IFC_UART3_TX,
    HAL_DMA_HS_IFC_UART3_RX      = LL_DMA_HS_IFC_UART3_RX,
    HAL_DMA_HS_IFC_UART4_TX      = LL_DMA_HS_IFC_UART4_TX,
    HAL_DMA_HS_IFC_UART4_RX      = LL_DMA_HS_IFC_UART4_RX,
    HAL_DMA_HS_IFC_SPI0_TX       = LL_DMA_HS_IFC_SPI0_TX,
    HAL_DMA_HS_IFC_SPI0_RX       = LL_DMA_HS_IFC_SPI0_RX,
    HAL_DMA_HS_IFC_SPI1_TX       = LL_DMA_HS_IFC_SPI1_TX,
    HAL_DMA_HS_IFC_SPI1_RX       = LL_DMA_HS_IFC_SPI1_RX,
    HAL_DMA_HS_IFC_XIF_TX        = LL_DMA_HS_IFC_XIF_TX,
    HAL_DMA_HS_IFC_XIF_RX        = LL_DMA_HS_IFC_XIF_RX,
    HAL_DMA_HS_IFC_HRPWM_SLV7    = LL_DMA_HS_IFC_HRPWM_SLV7,
    HAL_DMA_HS_IFC_HRPWM_SLV6    = LL_DMA_HS_IFC_HRPWM_SLV6,
    HAL_DMA_HS_IFC_HRPWM_SLV5    = LL_DMA_HS_IFC_HRPWM_SLV5,
    HAL_DMA_HS_IFC_HRPWM_SLV4    = LL_DMA_HS_IFC_HRPWM_SLV4,
    HAL_DMA_HS_IFC_HRPWM_SLV3    = LL_DMA_HS_IFC_HRPWM_SLV3,
    HAL_DMA_HS_IFC_HRPWM_SLV2    = LL_DMA_HS_IFC_HRPWM_SLV2,
    HAL_DMA_HS_IFC_HRPWM_SLV1    = LL_DMA_HS_IFC_HRPWM_SLV1,
    HAL_DMA_HS_IFC_HRPWM_SLV0    = LL_DMA_HS_IFC_HRPWM_SLV0,
    HAL_DMA_HS_IFC_HRPWM_MST     = LL_DMA_HS_IFC_HRPWM_MST,

    HAL_DMA_HS_IFC_MUX_ADC3      = LL_DMA_HS_IFC_MUX_ADC3,
    HAL_DMA_HS_IFC_MUX_ADC2      = LL_DMA_HS_IFC_MUX_ADC2,
    HAL_DMA_HS_IFC_MUX_ADC1      = LL_DMA_HS_IFC_MUX_ADC1,
    HAL_DMA_HS_IFC_MUX_ADC0      = LL_DMA_HS_IFC_MUX_ADC0,
    HAL_DMA_HS_IFC_MUX_PDM0_RX   = LL_DMA_HS_IFC_MUX_PDM0_RX,
    HAL_DMA_HS_IFC_MUX_PDM1_RX   = LL_DMA_HS_IFC_MUX_PDM1_RX,
    HAL_DMA_HS_IFC_MUX_PDM2_RX   = LL_DMA_HS_IFC_MUX_PDM2_RX,
    HAL_DMA_HS_IFC_MUX_PDM3_RX   = LL_DMA_HS_IFC_MUX_PDM3_RX,
} HAL_DMA_HandshakeIfcTypeDef;


typedef enum 
{
    HAL_DMA_IFS_MUX_DISABLE   = 0x00UL, 
    HAL_DMA_IFS_MUX_ENABLE    = 0x01UL
} HAL_DMA_IfcMuxEnTypeDef;

/**
  * @}
  */

/** @defgroup DMA_HAL_EC_COMPLETE_LEVEL DMA Complete Level
  * @{
  */
typedef enum
{
    HAL_DMA_FULL_TRANSFER      = 0x00UL,    /*!< Full transfer complete */
    HAL_DMA_HALF_TRANSFER      = 0x01UL     /*!< Half Transfer complete */
} HAL_DMA_LevelCompleteTypeDef;

/**
  * @}
  */

/** @defgroup DMA_HAL_EC_CALLBACK_ID DMA Callback ID
  * @{
  */
typedef enum 
{
    HAL_DMA_XFER_CPLT_CB_ID     = 0x00UL,  /*!< Transfer complete callback */
    HAL_DMA_XFER_HALFCPLT_CB_ID = 0x01UL,  /*!< Transfer half-complete callback */
    HAL_DMA_XFER_ERROR_CB_ID    = 0x02UL,  /*!< Transfer error callback */
    HAL_DMA_XFER_ABORT_CB_ID    = 0x03UL,  /*!< Transfer abort callback  */
    HAL_DMA_XFER_ALL_CB_ID      = 0x04UL,  /*!< All callbacks            */
} HAL_DMA_CallbackIDTypeDef;
/**
  * @}
  */



/**
  * @brief  DMA Init Structure definition
  * @note   The structure keeps the standard fields (Direction, PeriphInc,
  *         MemInc, PeriphDataAlignment, MemDataAlignment, Mode, Priority) plus
  *         TAE-specific fields (Src/Dst burst, peripheral bus and handshake
  *         interface) exposed by this device.
  */
typedef struct 
{
    HAL_DMA_ChannelTypeDef        Channel;                 /*!< DMA channel: HAL_DMA_CHANNEL_0..5 or HAL_DMA_CHANNEL_INVALID (auto) */
    HAL_DMA_TransTypeTypeDef      Direction;               /*!< Transfer direction: HAL_DMA_TRANS_TYPE_* */
    HAL_DMA_AddrModeTypeDef       PeriphInc;               /*!< Peripheral address mode: HAL_DMA_ADDR_MODE_* */
    HAL_DMA_AddrModeTypeDef       MemInc;                  /*!< Memory address mode: HAL_DMA_ADDR_MODE_* */
    HAL_DMA_DataWidthTypeDef      PeriphDataAlignment;     /*!< Peripheral data width: HAL_DMA_DATA_WIDTH_* */
    HAL_DMA_DataWidthTypeDef      MemDataAlignment;        /*!< Memory data width: HAL_DMA_DATA_WIDTH_* */
    HAL_DMA_TransModeTypeDef      Mode;                    /*!< Transfer mode: HAL_DMA_TRANS_MODE_* */
    HAL_DMA_PriorityTypeDef       Priority;                /*!< Transfer priority: HAL_DMA_PRIORITY_* (see note) */
    HAL_DMA_BurstLenTypeDef       SrcBurstLen;             /*!< Source burst length: HAL_DMA_BURST_LEN_* */
    HAL_DMA_BurstLenTypeDef       DstBurstLen;             /*!< Destination burst length: HAL_DMA_BURST_LEN_* */
    HAL_DMA_PeriphBusTypeDef      SrcPeriphBus;            /*!< Source peripheral bus: HAL_DMA_PERIPH_BUS_* */
    HAL_DMA_PeriphBusTypeDef      DstPeriphBus;            /*!< Destination peripheral bus: HAL_DMA_PERIPH_BUS_* */
    HAL_DMA_HandshakeIfcTypeDef   SrcHandshakeIfc;         /*!< Source handshake interface: HAL_DMA_HS_IFC_* */
    HAL_DMA_HandshakeIfcTypeDef   DstHandshakeIfc;         /*!< Destination handshake interface: HAL_DMA_HS_IFC_* */
} HAL_DMA_InitTypeDef;

typedef struct HAL_DMA_HandleStructDef HAL_DMA_HandleTypeDef; /*!< HAL DMA handle structure type */

typedef void (*HAL_DMA_CallbackTypeDef)(HAL_DMA_HandleTypeDef *hdma); /*!< HAL DMA Callback pointer definition */

/**
  * @brief  DMA Handle Structure definition
  */
struct HAL_DMA_HandleStructDef 
{
    DMA_TypeDef                   *Instance;        /*!< DMA peripheral instance */
    uint32_t                      Channel;          /*!< Allocated channel, retained for Start/Abort/IRQ lookup */
    volatile HAL_DMA_StateTypeDef State;            /*!< DMA transfer state */
    volatile uint32_t             ErrorCode;        /*!< DMA error code */
    HAL_DMA_CallbackTypeDef       XferCpltCallback;     /*!< Transfer complete callback */
    HAL_DMA_CallbackTypeDef       XferHalfCpltCallback; /*!< Half-complete callback, used when registered */
    HAL_DMA_CallbackTypeDef       XferErrorCallback;    /*!< Transfer error callback */
    HAL_DMA_CallbackTypeDef       XferAbortCallback;    /*!< Transfer abort callback, used when registered */
    void                          *Parent;          /*!< Parent peripheral handle */
    const void                    *pUserData;       /*!< User data field */
};

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMA_HAL_Exported_Functions DMA HAL Exported Functions
  * @{
  */

/** @addtogroup DMA_HAL_EF_Configuration DMA HAL Configuration Functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_Init(HAL_DMA_HandleTypeDef *hdma, DMA_TypeDef *DMAx,
                               HAL_DMA_InitTypeDef *pInit);
HAL_StatusTypeDef HAL_DMA_DeInit(HAL_DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Start(HAL_DMA_HandleTypeDef *hdma, uint32_t SrcAddress,
                                uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(HAL_DMA_HandleTypeDef *hdma, uint32_t SrcAddress,
                                   uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(HAL_DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(HAL_DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(HAL_DMA_HandleTypeDef *hdma, uint32_t CompleteLevel,
                                          uint32_t Timeout);
void HAL_DMA_IRQHandler(HAL_DMA_HandleTypeDef *hdma);

HAL_StatusTypeDef HAL_DMA_RegisterCallback(HAL_DMA_HandleTypeDef *hdma,
                                           HAL_DMA_CallbackIDTypeDef CallbackID,
                                           void (*pCallback)(HAL_DMA_HandleTypeDef *));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(HAL_DMA_HandleTypeDef *hdma,
                                             HAL_DMA_CallbackIDTypeDef CallbackID);
HAL_DMA_StateTypeDef HAL_DMA_GetState(HAL_DMA_HandleTypeDef *hdma);
uint32_t HAL_DMA_GetError(HAL_DMA_HandleTypeDef *hdma);
HAL_DMA_HandleTypeDef *HAL_DMA_GetHandleByChannel(uint32_t Channel);
/**
  * @}
  */

/** @addtogroup DMA_HAL_EF_Callbacks DMA HAL Callbacks
  * @{
  */
void HAL_DMA_MspInit(HAL_DMA_HandleTypeDef *hdma);
void HAL_DMA_MspDeInit(HAL_DMA_HandleTypeDef *hdma);
void HAL_DMA_XferCpltCallback(HAL_DMA_HandleTypeDef *hdma);
void HAL_DMA_XferHalfCpltCallback(HAL_DMA_HandleTypeDef *hdma);
void HAL_DMA_XferErrorCallback(HAL_DMA_HandleTypeDef *hdma);
void HAL_DMA_XferAbortCallback(HAL_DMA_HandleTypeDef *hdma);
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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32F561X_HAL_DMA_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
