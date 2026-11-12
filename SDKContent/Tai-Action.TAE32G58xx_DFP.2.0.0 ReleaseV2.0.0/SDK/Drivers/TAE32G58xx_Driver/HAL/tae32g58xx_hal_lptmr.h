/**
  ******************************************************************************
  * @file    tae32g58xx_hal_lptmr.h
  * @author  Tai-Action SD Team
  * @brief   Header file for LPTMR HAL module.
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
#ifndef _TAE32G58XX_HAL_LPTMR_H_
#define _TAE32G58XX_HAL_LPTMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_lptmr.h"

#if defined(TMR6)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_LPTMR_MODULE_ENABLED) && (HAL_LPTMR_MODULE_ENABLED == 1)


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup LPTMR_HAL_Exported_Macros LPTMR HAL Exported Macros
  * @{
  */

/** @defgroup LPTMR_HAL_EM_Assert LPTMR HAL Assert 
  * @brief    LPTMR HAL Assert
  * @{
  */

#ifndef TAE32_USE_HAL_LPTMR_CHECK_PARAM
#define TAE32_USE_HAL_LPTMR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_LPTMR_CHECK_PARAM != 1) && (TAE32_USE_HAL_LPTMR_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_LPTMR_CHECK_PARAM
#define TAE32_USE_HAL_LPTMR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_LPTMR_CHECK_PARAM */

#define HAL_LPTMR_PARAM_CHECK(expression)     \
        if (TAE32_USE_HAL_LPTMR_CHECK_PARAM) { \
            expression;                        \
        }
/**
  * @}
  */ /* LPTMR_HAL_EM_Assert */


/**
 * @brief Updates a LPTMR HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the LPTMR process
 * state check feature is enabled (TAE32_USE_HAL_LPTMR_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_LPTMR_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_LPTMR_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_LPTMR_CHECK_PROCESS_STATE == 1)
#define HAL_LPTMR_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_LPTMR_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        do {                                                                      \
            if ((upd_parm) != (check_value)) {                                    \
                failed_expression;                                                \
                break;                                                            \
            } else {                                                              \
                (upd_parm) = (new_value);                                         \
            }                                                                     \
        } while(0)    
#endif



/** @defgroup LPTMR_HAL_EM_Mask LPTMR HAL Mask
  * @brief    LPTMR HAL State / Error / Interrupt mask definitions
  * @{
  */

/** @name   HAL_LPTMR_StateMaskTypeDef 
  * @brief  HAL LPTMR global state mask definition. 
  * @{
  */
#define HAL_LPTMR_StateMaskTypeDef                          uint32_t

#define HAL_LPTMR_STATE_MASK_RESET                          (0U)         /*!< LPTMR not yet initialized                     */
#define HAL_LPTMR_STATE_MASK_CONFIGURABLE                   (1U << 30U)  /*!< LPTMR is configurable                         */
#define HAL_LPTMR_STATE_MASK_BUSY                           (1U << 29U)  /*!< An internal process is ongoing                */
#define HAL_LPTMR_STATE_MASK_TIMEOUT                        (1U << 28U)  /*!< Timeout state                                 */
#define HAL_LPTMR_STATE_MASK_ERROR                          (1U << 27U)  /*!< Error state                                   */
/** @} */

/** @name   HAL_LPTMR_ErrCodeMskTypeDef
  * @brief  HAL LPTMR Error Code Mask definition.
  * @{
  */
#define HAL_LPTMR_ErrCodeMskTypeDef                         uint32_t

#define HAL_LPTMR_ERROR_NONE                                (0U)         /*!< No error                     */
#define HAL_LPTMR_ERROR_INVALID_INSTANCE                    (1U << 30U)  /*!< Invalid instance error       */
#define HAL_LPTMR_ERROR_BASE_CONFIG                         (1U << 29U)  /*!< Basic config error           */
/** @} */

/** @name   HAL_LPTMR_ITEnMskTypeDef
  * @brief  HAL LPTMR Interrupt Enable Mask Definition
  * @{
  */
#define HAL_LPTMR_ITEnMskTypeDef                            LL_LPTMR_IER_ITEnMskTypeDef

#define HAL_LPTMR_IER_TRIGGER_IT_EN                         LL_LPTMR_IER_TIE     /*!< Trigger interrupt enable mask             */
#define HAL_LPTMR_IER_UPDATE_IT_EN                          LL_LPTMR_IER_UIE     /*!< Update interrupt enable mask              */
#define HAL_LPTMR_IER_CH0_COMPARE_IT_EN                     LL_LPTMR_IER_CIE     /*!< CH0 Compare interrupt enable mask         */

/** @} */

/** @name   HAL_LPTMR_ITPendingMskTypeDef
  * @brief  HAL LPTMR Interrupt Flag Mask Definition
  * @{
  */
#define HAL_LPTMR_ITPendingMskTypeDef                       LL_LPTMR_SR_ITPendingMskTypeDef

#define HAL_LPTMR_SR_TRIGGER_IT_FLAG                        LL_LPTMR_SR_TIF      /*!< Trigger interrupt flag mask               */
#define HAL_LPTMR_SR_UPDATE_IT_FLAG                         LL_LPTMR_SR_UIF      /*!< Update interrupt flag mask                */
#define HAL_LPTMR_SR_CH0_COMPARE_IT_FLAG                    LL_LPTMR_SR_CIF      /*!< CH0 Compare interrupt flag mask           */
/** @} */


/**
  * @}
  */ /* LPTMR_HAL_EM_Mask */

/**
  * @}
  */ /* LPTMR_HAL_Exported_Macros */

/* Exported types ------------------------------------------------------------*/


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @addtogroup LPTMR_HAL
  * @brief    LPTMR HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup LPTMR_HAL_Exported_Types LPTMR HAL Exported Types
  * @brief    LPTMR HAL Exported Types
  * @{
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
/**
  * @brief  HAL LPTMR State definition
  */
typedef enum
{
    HAL_LPTMR_STATE_RESET           = HAL_LPTMR_STATE_MASK_RESET,         /*!< LPTMR not yet initialized           */
    HAL_LPTMR_STATE_CONFIGURABLE    = HAL_LPTMR_STATE_MASK_CONFIGURABLE,  /*!< LPTMR is configurable  */
    HAL_LPTMR_STATE_BUSY            = HAL_LPTMR_STATE_MASK_BUSY,          /*!< An internal process is ongoing      */
    HAL_LPTMR_STATE_TIMEOUT         = HAL_LPTMR_STATE_MASK_TIMEOUT,       /*!< Timeout state                       */
    HAL_LPTMR_STATE_ERROR           = HAL_LPTMR_STATE_MASK_ERROR          /*!< Error state                         */
} HAL_LPTMR_StateTypeDef;

_Static_assert(sizeof(HAL_LPTMR_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else /* TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

typedef HAL_LPTMR_StateMaskTypeDef      HAL_LPTMR_StateTypeDef;
#define HAL_LPTMR_STATE_RESET           HAL_LPTMR_STATE_MASK_RESET
#define HAL_LPTMR_STATE_CONFIGURABLE    HAL_LPTMR_STATE_MASK_CONFIGURABLE
#define HAL_LPTMR_STATE_BUSY            HAL_LPTMR_STATE_MASK_BUSY
#define HAL_LPTMR_STATE_TIMEOUT         HAL_LPTMR_STATE_MASK_TIMEOUT
#define HAL_LPTMR_STATE_ERROR           HAL_LPTMR_STATE_MASK_ERROR
#endif /* !TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

/**
 * @brief 
 */
typedef enum
{
    HAL_LPTMR_FUNC_DISABLE  = 0U,    /*!< LPTMR Function Disable  */
    HAL_LPTMR_FUNC_ENABLE   = 1U     /*!< LPTMR Function Enable   */
} HAL_LPTMR_EnableTypeDef;

/**
 * @brief HAL LPTMR Channel Index Enumeration 
 */
typedef enum
{
    HAL_LPTMR_BREAK_INPUT_BK0 = 0U, /*!< LPTMR Break input BK0  */
    HAL_LPTMR_BREAK_INPUT_BK1 = 1U  /*!< LPTMR Break input BK1  */
} HAL_LPTMR_BreakInputTypeDef;

/**
  * @brief HAL LPTMR Channel Index Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_CHANNEL_0     = LL_LPTMR_CAP_CMP_CH_0,
    HAL_LPTMR_CHANNEL_NUMS  = LL_LPTMR_CAP_CMP_CH_NUMS
} HAL_LPTMR_ChannelIdxTypeDef;

/**
  * @brief HAL LPTMR Work Mode Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_WORK_MODE_CONTINUE  = LL_LPTMR_WORK_MODE_CONTINUE,
    HAL_LPTMR_WORK_MODE_SINGLE    = LL_LPTMR_WORK_MODE_SINGLE,
} HAL_LPTMR_WorkModeTypeDef;

/**
  * @brief HAL LPTMR Update Event Disable Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_UPDATE_EVT_RELEASE  = 0UL,
    HAL_LPTMR_UPDATE_EVT_ASSERT   = 1UL,
} HAL_LPTMR_UpdateEvtDisTypeDef;

/**
  * @brief Timer Output Idle State Definition
  */
typedef enum 
{
    HAL_LPTMR_OUTPUT_IDLE_STA_LOW   = LL_LPTMR_OUTPUT_IDLE_STA_LOW,    /*!<  Output Idle State Low     */
    HAL_LPTMR_OUTPUT_IDLE_STA_HIGH  = LL_LPTMR_OUTPUT_IDLE_STA_HIGH,       /*!<  Output Idle State High    */
} HAL_LPTMR_IdleStaTypeDef;

/**
  * @brief HAL LPTMR Compare Output Polarity Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_CMP_POL_HIGH  = LL_LPTMR_CMP_POL_HIGH,
    HAL_LPTMR_CMP_POL_LOW   = LL_LPTMR_CMP_POL_LOW,
} HAL_LPTMR_CmpPolTypeDef;

/**
  * @brief HAL LPTMR ETR Filter
  */
typedef enum 
{
    HAL_LPTMR_ETR_FILTER_NONE     = LL_LPTMR_ETR_FILTER_NONE,
    HAL_LPTMR_ETR_FILTER_TDS_X1   = LL_LPTMR_ETR_FILTER_TDS_X1,
    HAL_LPTMR_ETR_FILTER_TDS_X2   = LL_LPTMR_ETR_FILTER_TDS_X2,
    HAL_LPTMR_ETR_FILTER_TDS_X3   = LL_LPTMR_ETR_FILTER_TDS_X3,
    HAL_LPTMR_ETR_FILTER_TDS_X4   = LL_LPTMR_ETR_FILTER_TDS_X4,
    HAL_LPTMR_ETR_FILTER_TDS_X5   = LL_LPTMR_ETR_FILTER_TDS_X5,
    HAL_LPTMR_ETR_FILTER_TDS_X6   = LL_LPTMR_ETR_FILTER_TDS_X6,
    HAL_LPTMR_ETR_FILTER_TDS_X7   = LL_LPTMR_ETR_FILTER_TDS_X7,
    HAL_LPTMR_ETR_FILTER_TDS_X8   = LL_LPTMR_ETR_FILTER_TDS_X8,
    HAL_LPTMR_ETR_FILTER_TDS_X9   = LL_LPTMR_ETR_FILTER_TDS_X9,
    HAL_LPTMR_ETR_FILTER_TDS_X10  = LL_LPTMR_ETR_FILTER_TDS_X10,
    HAL_LPTMR_ETR_FILTER_TDS_X11  = LL_LPTMR_ETR_FILTER_TDS_X11,
    HAL_LPTMR_ETR_FILTER_TDS_X12  = LL_LPTMR_ETR_FILTER_TDS_X12,
    HAL_LPTMR_ETR_FILTER_TDS_X13  = LL_LPTMR_ETR_FILTER_TDS_X13,
    HAL_LPTMR_ETR_FILTER_TDS_X14  = LL_LPTMR_ETR_FILTER_TDS_X14,
    HAL_LPTMR_ETR_FILTER_TDS_X15  = LL_LPTMR_ETR_FILTER_TDS_X15,
} HAL_LPTMR_ETRFilTypeDef;

/**
  * @brief HAL LPTMR ETR Mode Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_ETR_MODE_INT_CLK = LL_LPTMR_ETR_MODE_INT_CLK,
    HAL_LPTMR_ETR_MODE_EXT_CLK = LL_LPTMR_ETR_MODE_EXT_CLK,
} HAL_LPTMR_ETRModeTypeDef;

/**
  * @brief HAL LPTMR ETR Edge Mode Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_ETR_EDGE_MODE_CLOSE           = LL_LPTMR_ETR_EDGE_MODE_CLOSE,
    HAL_LPTMR_ETR_EDGE_MODE_RISING          = LL_LPTMR_ETR_EDGE_MODE_RISING,
    HAL_LPTMR_ETR_EDGE_MODE_FALLING         = LL_LPTMR_ETR_EDGE_MODE_FALLING,
    HAL_LPTMR_ETR_EDGE_MODE_RISING_FALLING  = LL_LPTMR_ETR_EDGE_MODE_RISING_FALLING,
} HAL_LPTMR_ETREdgeTypeDef;

/**
  * @brief HAL LPTMR Slave Mode Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_SLV_MODE_DIS        = LL_LPTMR_SLV_MODE_DIS,
    HAL_LPTMR_SLV_MODE_RST        = LL_LPTMR_SLV_MODE_RST,
    HAL_LPTMR_SLV_MODE_GATING     = LL_LPTMR_SLV_MODE_GATING,
    HAL_LPTMR_SLV_MODE_TRIG       = LL_LPTMR_SLV_MODE_TRIG,
    HAL_LPTMR_SLV_MODE_EXTCLK     = LL_LPTMR_SLV_MODE_EXTCLK,
    HAL_LPTMR_SLV_MODE_RST_TRIG   = LL_LPTMR_SLV_MODE_RST_TRIG,
    HAL_LPTMR_SLV_MODE_RST_GATING = LL_LPTMR_SLV_MODE_RST_GATING,
} HAL_LPTMR_SlvModeTypeDef;

/**
  * @brief HAL LPTMR Trigger Input Signal Enumeration 
  */
typedef enum 
{
    HAL_LPTMR_TRIG_ITR0  = LL_LPTMR_TRIG_ITR0,
    HAL_LPTMR_TRIG_ITR1  = LL_LPTMR_TRIG_ITR1,
    HAL_LPTMR_TRIG_ITR2  = LL_LPTMR_TRIG_ITR2,
    HAL_LPTMR_TRIG_ITR3  = LL_LPTMR_TRIG_ITR3,
    HAL_LPTMR_TRIG_ITR4  = LL_LPTMR_TRIG_ITR4,
    HAL_LPTMR_TRIG_ITR5  = LL_LPTMR_TRIG_ITR5,
    HAL_LPTMR_TRIG_ITR6  = LL_LPTMR_TRIG_ITR6,
    HAL_LPTMR_TRIG_ITR7  = LL_LPTMR_TRIG_ITR7,
    HAL_LPTMR_TRIG_ITR8  = LL_LPTMR_TRIG_ITR8,
    HAL_LPTMR_TRIG_ITR9  = LL_LPTMR_TRIG_ITR9,
    HAL_LPTMR_TRIG_ITR10 = LL_LPTMR_TRIG_ITR10,
    HAL_LPTMR_TRIG_ITR11 = LL_LPTMR_TRIG_ITR11,
    HAL_LPTMR_TRIG_ITR12 = LL_LPTMR_TRIG_ITR12,
    HAL_LPTMR_TRIG_ITR13 = LL_LPTMR_TRIG_ITR13,
    HAL_LPTMR_TRIG_ITR14 = LL_LPTMR_TRIG_ITR14,
    HAL_LPTMR_TRIG_ITR15 = LL_LPTMR_TRIG_ITR15,
    HAL_LPTMR_TRIG_ETR_FE = LL_LPTMR_TRIG_ETR_FE,
    HAL_LPTMR_TRIG_ETR_F = LL_LPTMR_TRIG_ETR_F,
} HAL_LPTMR_TrigTypeDef;

/**
  * @brief HAL LPTMR Event Source Enumeration 
  */
typedef enum
{
    HAL_LPTMR_EVENTSOURCE_UPDATE      =   LL_LPTMR_EVT_GEN_UPDATE,
    HAL_LPTMR_EVENTSOURCE_TRIG        =   LL_LPTMR_EVT_GEN_TRIGGER,
    HAL_LPTMR_EVENTSOURCE_CMP_UPD     =   LL_LPTMR_EVT_GEN_COMPARE_UPDATE,
    HAL_LPTMR_EVENTSOURCE_CNTR_START  =   LL_LPTMR_EVT_GEN_COUNTER_START,
} HAL_LPTMR_EvtSrcTypeDef;


/**
  * @brief  LPTMR Base Initialization Structure Definition
  */
typedef struct
{
    HAL_LPTMR_EnableTypeDef         AutoReloadPreload;      /*!< Auto Preload Enable                        */
    HAL_LPTMR_WorkModeTypeDef       WorkMode;               /*!< Work Mode: Continue/Single                 */
    uint16_t                        Period;                 /*!< Period Value                               */
    uint16_t                        Prescaler;              /*!< Clock Prescaler                            */
} HAL_LPTMR_BaseInitTypeDef;

/**
  * @brief  LPTMR Output Compare Initialization Structure Definition
  */
typedef struct
{
    HAL_LPTMR_EnableTypeDef         CompareAutoReload;  /*!< Output Compare Auto Preload Enable */
    uint16_t                        CompareValue;       /*!< Output Compare Match Value         */
    HAL_LPTMR_CmpPolTypeDef         OCPolarity;         /*!< Output Compare Polarity            */
} HAL_LPTMR_OutputCmpInitTypeDef;

/**
  * @brief  LPTMR Slave / ETR Initialization Structure Definition
  */
typedef struct
{
    HAL_LPTMR_SlvModeTypeDef        SlaveMode;          /*!< Slave Mode                         */
    HAL_LPTMR_TrigTypeDef           InputTrigger;       /*!< Trigger Selection                  */
    HAL_LPTMR_ETREdgeTypeDef        TriggerPolarity;    /*!< ETR Edge Mode                      */
    HAL_LPTMR_ETRFilTypeDef         TriggerFilter;      /*!< ETR Filter                         */
    HAL_LPTMR_ETRModeTypeDef        ClokMode;           /*!< ETR Mode                           */
} HAL_LPTMR_SlvInitTypeDef;

/**
  * @brief HAL LPTMR handle structure type
  */
typedef struct HAL_LPTMR_HandleStructDef HAL_LPTMR_HandleTypeDef;

/**
  * @brief LPTMR IRQ callback function type definition
  */
typedef void (*HAL_LPTMR_IRQCallback)(HAL_LPTMR_HandleTypeDef *Handle);

/**
  * @brief  LPTMR Handle Structure definition
  */
struct HAL_LPTMR_HandleStructDef
{
    LPTMR_TypeDef                           *Instance;        /*!< Register base address      */
    volatile HAL_LPTMR_StateTypeDef         State;            /*!< LPTMR operation state      */
    uint32_t                                UpdateInterval;   /*!< Operation update interval  */
    volatile HAL_LPTMR_ErrCodeMskTypeDef    LastErrorCodes;   /*!< Last error codes           */
    const void                              *pUserData;       /*!< User data pointer          */
};
/**
  * @}
  */ /* LPTMR_HAL_Exported_Types */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPTMR_HAL_Exported_Functions LPTMR HAL Exported Functions
  * @{
  */

/** @defgroup LPTMR_HAL_EF_Initialization LPTMR HAL Initialization
  * @{
  */

HAL_StatusTypeDef HAL_LPTMR_Base_Init(HAL_LPTMR_HandleTypeDef *Handle, 
                                      LPTMR_TypeDef *LPTMRx,
                                      const HAL_LPTMR_BaseInitTypeDef *pInit);
                              
HAL_StatusTypeDef HAL_LPTMR_Base_DeInit(HAL_LPTMR_HandleTypeDef *Handle);

void HAL_LPTMR_Base_MspInit(HAL_LPTMR_HandleTypeDef *Handle);
void HAL_LPTMR_Base_MspDeInit(HAL_LPTMR_HandleTypeDef *Handle);
void HAL_LPTMR_IoInit(LPTMR_TypeDef *LPTMRx);
void HAL_LPTMR_IoDeInit(LPTMR_TypeDef *LPTMRx);
/**
  * @}
  */

/** @defgroup LPTMR_HAL_EF_Configuration LPTMR HAL Configuration
  * @{
  */

HAL_StatusTypeDef HAL_LPTMR_OC_Init(HAL_LPTMR_HandleTypeDef *Handle, 
                                    const HAL_LPTMR_OutputCmpInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_LPTMR_InitSlave(HAL_LPTMR_HandleTypeDef *Handle,
                                      const HAL_LPTMR_SlvInitTypeDef *pCfg);

/**
  * @}
  */

/** @defgroup LPTMR_HAL_EF_IO_Operation LPTMR HAL IO Operation
  * @{
  */
HAL_StatusTypeDef HAL_LPTMR_Counter_Start(HAL_LPTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_LPTMR_Counter_Stop(HAL_LPTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_LPTMR_Counter_Start_IT(HAL_LPTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_LPTMR_Counter_Stop_IT(HAL_LPTMR_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_LPTMR_OC_Start(HAL_LPTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_LPTMR_OC_Stop(HAL_LPTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_LPTMR_OC_StartIT(HAL_LPTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_LPTMR_OC_StopIT(HAL_LPTMR_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_LPTMR_GenerateEvent(HAL_LPTMR_HandleTypeDef *Handle, HAL_LPTMR_EvtSrcTypeDef EventSource);

uint16_t HAL_LPTMR_ReadCounter(const HAL_LPTMR_HandleTypeDef *Handle);
uint16_t HAL_LPTMR_ReadCompare(const HAL_LPTMR_HandleTypeDef *Handle);
/**
  * @}
  */

/** @defgroup LPTMR_HAL_EF_IRQ_Handler LPTMR HAL IRQ Handler and Callbacks
  * @{
  */

HAL_StatusTypeDef HAL_LPTMR_InterruptRequestEnable(HAL_LPTMR_HandleTypeDef *Handle, 
                                                   HAL_LPTMR_ITEnMskTypeDef ITMask);

HAL_StatusTypeDef HAL_LPTMR_InterruptRequestDisable(HAL_LPTMR_HandleTypeDef *Handle, 
                                                    HAL_LPTMR_ITEnMskTypeDef ITMask);

void HAL_LPTMR_IRQHandler(HAL_LPTMR_HandleTypeDef *Handle);

void HAL_LPTMR_UpdateCallback(HAL_LPTMR_HandleTypeDef *Handle);
void HAL_LPTMR_TriggerCallback(HAL_LPTMR_HandleTypeDef *Handle);
void HAL_LPTMR_CompareMatchCallback(HAL_LPTMR_HandleTypeDef *Handle);

/**
  * @}
  */

/**
  * @}
  */ /* LPTMR_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

#endif /* HAL_LPTMR_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* LPTMR */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_LPTMR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
