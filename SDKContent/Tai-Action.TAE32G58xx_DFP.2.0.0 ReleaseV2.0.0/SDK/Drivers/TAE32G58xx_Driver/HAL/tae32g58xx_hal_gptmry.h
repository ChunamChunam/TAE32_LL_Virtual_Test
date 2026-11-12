/**
  ******************************************************************************
  * @file    tae32g58xx_hal_gptmry.h
  * @author  Tai-Action SD Team
  * @brief   Header file for GPTMRY HAL module.
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
#ifndef _TAE32G58XX_HAL_GPTMRY_H_
#define _TAE32G58XX_HAL_GPTMRY_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_gptmry.h"

#if defined(TMR3) || defined(TMR4)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_GPTMRY_MODULE_ENABLED) && (HAL_GPTMRY_MODULE_ENABLED == 1)


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPTMRY_HAL_Exported_Macros GPTMRY HAL Exported Macros
  * @{
  */

/** @defgroup GPTMRY_HAL_EM_Assert GPTMRY HAL Assert 
  * @brief    GPTMRY HAL Assert
  * @{
  */

#ifndef TAE32_USE_HAL_GPTMRY_CHECK_PARAM
#define TAE32_USE_HAL_GPTMRY_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_GPTMRY_CHECK_PARAM != 1) && (TAE32_USE_HAL_GPTMRY_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_GPTMRY_CHECK_PARAM
#define TAE32_USE_HAL_GPTMRY_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_GPTMRY_CHECK_PARAM */

#define HAL_GPTMRY_PARAM_CHECK(expression)     \
        if (TAE32_USE_HAL_GPTMRY_CHECK_PARAM) { \
            expression;                        \
        }
/**
  * @}
  */ /* GPTMRY_HAL_EM_Assert */


/**
 * @brief Updates a GPTMRY HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the GPTMRY process
 * state check feature is enabled (TAE32_USE_HAL_GPTMRY_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_GPTMRY_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_GPTMRY_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_GPTMRY_CHECK_PROCESS_STATE == 1)
#define HAL_GPTMRY_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_GPTMRY_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        do {                                                                      \
            if ((upd_parm) != (check_value)) {                                    \
                failed_expression;                                                \
                break;                                                            \
            } else {                                                              \
                (upd_parm) = (new_value);                                         \
            }                                                                     \
        } while(0)    
#endif



/** @defgroup GPTMRY_HAL_EM_Mask GPTMRY HAL Mask
  * @brief    GPTMRY HAL State / Error / Interrupt mask definitions
  * @{
  */

/** @name   HAL_GPTMRY_StateMaskTypeDef 
  * @brief  HAL GPTMRY global state mask definition. 
  * @{
  */
#define HAL_GPTMRY_StateMaskTypeDef                          uint32_t

#define HAL_GPTMRY_STATE_MASK_RESET                          (0U)         /*!< GPTMRY not yet initialized                     */
#define HAL_GPTMRY_STATE_MASK_CONFIGURABLE                   (1U << 30U)  /*!< GPTMRY is configurable                         */
#define HAL_GPTMRY_STATE_MASK_BUSY                           (1U << 29U)  /*!< An internal process is ongoing                */
#define HAL_GPTMRY_STATE_MASK_TIMEOUT                        (1U << 28U)  /*!< Timeout state                                 */
#define HAL_GPTMRY_STATE_MASK_ERROR                          (1U << 27U)  /*!< Error state                                   */
/** @} */

/** @name   HAL_GPTMRY_ErrCodeMskTypeDef
  * @brief  HAL GPTMRY Error Code Mask definition.
  * @{
  */
#define HAL_GPTMRY_ErrCodeMskTypeDef                         uint32_t

#define HAL_GPTMRY_ERROR_NONE                                (0U)         /*!< No error                     */
#define HAL_GPTMRY_ERROR_INVALID_INSTANCE                    (1U << 30U)  /*!< Invalid instance error       */
/** @} */

/** @name   HAL_GPTMRY_ITEnMskTypeDef
  * @brief  HAL GPTMRY Interrupt Enable Mask Definition
  * @{
  */
#define HAL_GPTMRY_ITEnMskTypeDef                            LL_GPTMRY_IER_ITEnMskTypeDef

#define HAL_GPTMRY_IER_TRIGGER_IT_EN                         LL_GPTMRY_IER_TIE     /*!< Trigger interrupt enable mask             */
#define HAL_GPTMRY_IER_OVERFLOW_IT_EN                        LL_GPTMRY_IER_OVIE    /*!< Overflow interrupt enable mask            */
#define HAL_GPTMRY_IER_UPDATE_IT_EN                          LL_GPTMRY_IER_UIE     /*!< Update interrupt enable mask              */
#define HAL_GPTMRY_IER_CH3_CAPTURE_OR_COMPARE_IT_EN          LL_GPTMRY_IER_C3MIE   /*!< CH3 Capture/Compare interrupt enable mask */
#define HAL_GPTMRY_IER_CH3_OVER_CAPTURE_IT_EN                LL_GPTMRY_IER_C3OIE   /*!< CH3 OverCapture interrupt enable mask     */
#define HAL_GPTMRY_IER_CH2_CAPTURE_OR_COMPARE_IT_EN          LL_GPTMRY_IER_C2MIE   /*!< CH2 Capture/Compare interrupt enable mask */
#define HAL_GPTMRY_IER_CH2_OVER_CAPTURE_IT_EN                LL_GPTMRY_IER_C2OIE   /*!< CH2 OverCapture interrupt enable mask     */
#define HAL_GPTMRY_IER_CH1_CAPTURE_OR_COMPARE_IT_EN          LL_GPTMRY_IER_C1MIE   /*!< CH1 Capture/Compare interrupt enable mask */
#define HAL_GPTMRY_IER_CH1_OVER_CAPTURE_IT_EN                LL_GPTMRY_IER_C1OIE   /*!< CH1 OverCapture interrupt enable mask     */
#define HAL_GPTMRY_IER_CH0_CAPTURE_OR_COMPARE_IT_EN          LL_GPTMRY_IER_C0MIE   /*!< CH0 Capture/Compare interrupt enable mask */
#define HAL_GPTMRY_IER_CH0_OVER_CAPTURE_IT_EN                LL_GPTMRY_IER_C0OIE   /*!< CH0 OverCapture interrupt enable mask     */
/** @} */

/** @name   HAL_GPTMRY_ITPendingMskTypeDef
  * @brief  HAL GPTMRY Interrupt Flag Mask Definition
  * @{
  */
#define HAL_GPTMRY_ITPendingMskTypeDef                       LL_GPTMRY_SR_ITPendingMskTypeDef

#define HAL_GPTMRY_SR_TRIGGER_IT_FLAG                        LL_GPTMRY_SR_TIF      /*!< Trigger interrupt flag mask               */
#define HAL_GPTMRY_SR_OVERFLOW_IT_FLAG                       LL_GPTMRY_SR_OVIF     /*!< Overflow interrupt flag mask              */
#define HAL_GPTMRY_SR_UPDATE_IT_FLAG                         LL_GPTMRY_SR_UIF      /*!< Update interrupt flag mask                */
#define HAL_GPTMRY_SR_CH3_CAPTURE_OR_COMPARE_IT_FLAG         LL_GPTMRY_SR_CC3MIF   /*!< CH3 Capture/Compare interrupt flag mask   */
#define HAL_GPTMRY_SR_CH3_OVER_CAPTURE_IT_FLAG               LL_GPTMRY_SR_CC3OIF   /*!< CH3 OverCapture interrupt flag mask       */
#define HAL_GPTMRY_SR_CH2_CAPTURE_OR_COMPARE_IT_FLAG         LL_GPTMRY_SR_CC2MIF   /*!< CH2 Capture/Compare interrupt flag mask   */
#define HAL_GPTMRY_SR_CH2_OVER_CAPTURE_IT_FLAG               LL_GPTMRY_SR_CC2OIF   /*!< CH2 OverCapture interrupt flag mask       */
#define HAL_GPTMRY_SR_CH1_CAPTURE_OR_COMPARE_IT_FLAG         LL_GPTMRY_SR_CC1MIF   /*!< CH1 Capture/Compare interrupt flag mask   */
#define HAL_GPTMRY_SR_CH1_OVER_CAPTURE_IT_FLAG               LL_GPTMRY_SR_CC1OIF   /*!< CH1 OverCapture interrupt flag mask       */
#define HAL_GPTMRY_SR_CH0_CAPTURE_OR_COMPARE_IT_FLAG         LL_GPTMRY_SR_CC0MIF   /*!< CH0 Capture/Compare interrupt flag mask   */
#define HAL_GPTMRY_SR_CH0_OVER_CAPTURE_IT_FLAG               LL_GPTMRY_SR_CC0OIF   /*!< CH0 OverCapture interrupt flag mask       */
/** @} */


/** @name   HAL_GPTMRY_TrigOutChMskTypeDef
  * @brief  HAL GPTMRY TRGO Channel Mask Definition
  * @{
  */
#define HAL_GPTMRY_TrigOutChMskTypeDef                       LL_GPTMRY_TTCR_TrigOutChMskTypeDef

#define HAL_GPTMRY_TRGI_OUT_SELECT_CH3_MASK                  LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH3
#define HAL_GPTMRY_TRGI_OUT_SELECT_CH2_MASK                  LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH2
#define HAL_GPTMRY_TRGI_OUT_SELECT_CH1_MASK                  LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH1
#define HAL_GPTMRY_TRGI_OUT_SELECT_CH0_MASK                  LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH0
/** @} */

/**
  * @}
  */ /* GPTMRY_HAL_EM_Mask */

/**
  * @}
  */ /* GPTMRY_HAL_Exported_Macros */

/* Exported types ------------------------------------------------------------*/


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @addtogroup GPTMRY_HAL
  * @brief    GPTMRY HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup GPTMRY_HAL_Exported_Types GPTMRY HAL Exported Types
  * @brief    GPTMRY HAL Exported Types
  * @{
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
/**
  * @brief  HAL GPTMRY State definition
  */
typedef enum
{
    HAL_GPTMRY_STATE_RESET           = HAL_GPTMRY_STATE_MASK_RESET,         /*!< GPTMRY not yet initialized           */
    HAL_GPTMRY_STATE_CONFIGURABLE    = HAL_GPTMRY_STATE_MASK_CONFIGURABLE,  /*!< GPTMRY is configurable  */
    HAL_GPTMRY_STATE_BUSY            = HAL_GPTMRY_STATE_MASK_BUSY,          /*!< An internal process is ongoing      */
    HAL_GPTMRY_STATE_TIMEOUT         = HAL_GPTMRY_STATE_MASK_TIMEOUT,       /*!< Timeout state                       */
    HAL_GPTMRY_STATE_ERROR           = HAL_GPTMRY_STATE_MASK_ERROR          /*!< Error state                         */
} HAL_GPTMRY_StateTypeDef;

_Static_assert(sizeof(HAL_GPTMRY_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else /* TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

typedef HAL_GPTMRY_StateMaskTypeDef      HAL_GPTMRY_StateTypeDef;
#define HAL_GPTMRY_STATE_RESET           HAL_GPTMRY_STATE_MASK_RESET
#define HAL_GPTMRY_STATE_CONFIGURABLE    HAL_GPTMRY_STATE_MASK_CONFIGURABLE
#define HAL_GPTMRY_STATE_BUSY            HAL_GPTMRY_STATE_MASK_BUSY
#define HAL_GPTMRY_STATE_TIMEOUT         HAL_GPTMRY_STATE_MASK_TIMEOUT
#define HAL_GPTMRY_STATE_ERROR           HAL_GPTMRY_STATE_MASK_ERROR
#endif /* !TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

/**
 * @brief 
 */
typedef enum
{
    HAL_GPTMRY_FUNC_DISABLE  = 0U,    /*!< GPTMRY Function Disable  */
    HAL_GPTMRY_FUNC_ENABLE   = 1U     /*!< GPTMRY Function Enable   */
} HAL_GPTMRY_EnableTypeDef;

/**
 * @brief HAL GPTMRY Channel Index Enumeration 
 */
typedef enum
{
    HAL_GPTMRY_BREAK_INPUT_BK0 = 0U, /*!< GPTMRY Break input BK0  */
    HAL_GPTMRY_BREAK_INPUT_BK1 = 1U  /*!< GPTMRY Break input BK1  */
} HAL_GPTMRY_BreakInputTypeDef;

/**
  * @brief HAL GPTMRY Channel Index Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_CHANNEL_0     = LL_GPTMRY_CAP_CMP_CH_0,
    HAL_GPTMRY_CHANNEL_1     = LL_GPTMRY_CAP_CMP_CH_1,
    HAL_GPTMRY_CHANNEL_2     = LL_GPTMRY_CAP_CMP_CH_2,
    HAL_GPTMRY_CHANNEL_3     = LL_GPTMRY_CAP_CMP_CH_3,
    HAL_GPTMRY_CHANNEL_NUMS  = LL_GPTMRY_CAP_CMP_CH_NUMS
} HAL_GPTMRY_ChannelIdxTypeDef;

/**
  * @brief HAL GPTMRY Work Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_WORK_MODE_CONTINUE  = LL_GPTMRY_WORK_MODE_CONTINUE,
    HAL_GPTMRY_WORK_MODE_SINGLE    = LL_GPTMRY_WORK_MODE_SINGLE,
} HAL_GPTMRY_WorkModeTypeDef;

/**
  * @brief HAL GPTMRY Update Event Disable Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_UPDATE_EVT_RELEASE  = 0UL,
    HAL_GPTMRY_UPDATE_EVT_ASSERT   = 1UL,
} HAL_GPTMRY_UpdateEvtDisTypeDef;

/**
  * @brief HAL GPTMRY Update Event Source Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_UPDATE_EVT_SRC_OV_UG  = LL_GPTMRY_UPDATE_EVT_SRC_OV_UG,
    HAL_GPTMRY_UPDATE_EVT_SRC_OV     = LL_GPTMRY_UPDATE_EVT_SRC_OV,
} HAL_GPTMRY_UpdateEvtSrcTypeDef;

/**
  * @brief Timer Output Idle State Definition
  */
typedef enum 
{
    HAL_GPTMRY_OUTPUT_IDLE_STA_LOW   = LL_GPTMRY_OUTPUT_IDLE_STA_LOW,    /*!<  Output Idle State Low     */
    HAL_GPTMRY_OUTPUT_IDLE_STA_HIGH  = LL_GPTMRY_OUTPUT_IDLE_STA_HIGH,       /*!<  Output Idle State High    */
} HAL_GPTMRY_IdleStaTypeDef;

/**
  * @brief HAL GPTMRY Master Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_MST_MODE_RESET        = LL_GPTMRY_MST_MODE_RESET,
    HAL_GPTMRY_MST_MODE_ENABLE       = LL_GPTMRY_MST_MODE_ENABLE,
    HAL_GPTMRY_MST_MODE_UPDATE       = LL_GPTMRY_MST_MODE_UPDATE,
    HAL_GPTMRY_MST_MODE_CAP_CMP_EVT  = LL_GPTMRY_MST_MODE_CAP_CMP_EVT,
    HAL_GPTMRY_MST_MODE_CMP_OUT0     = LL_GPTMRY_MST_MODE_OC0REF,
    HAL_GPTMRY_MST_MODE_CMP_OUT1     = LL_GPTMRY_MST_MODE_OC1REF,
    HAL_GPTMRY_MST_MODE_CMP_OUT2     = LL_GPTMRY_MST_MODE_OC2REF,
    HAL_GPTMRY_MST_MODE_CMP_OUT3     = LL_GPTMRY_MST_MODE_OC3REF,
} HAL_GPTMRY_MstModeTypeDef;

/**
  * @brief HAL GPTMRY Counter Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_COUNTER_MODE_UP               = 0UL,
    HAL_GPTMRY_COUNTER_MODE_DOWN             = 1UL,
    HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED1  = 2UL,
    HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED2  = 3UL,
    HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED3  = 4UL,
} HAL_GPTMRY_CounterModeTypeDef;

/**
  * @brief HAL GPTMRY Capture Polarity Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_CAP_POL_CLOSE     = LL_GPTMRY_CAP_POL_CLOSE,
    HAL_GPTMRY_CAP_POL_RISING    = LL_GPTMRY_CAP_POL_RISING,
    HAL_GPTMRY_CAP_POL_FALLING   = LL_GPTMRY_CAP_POL_FALLING,
    HAL_GPTMRY_CAP_POL_BOTH_EDGE = LL_GPTMRY_CAP_POL_BOTH_EDGE,
} HAL_GPTMRY_CapPolTypeDef;

/**
  * @brief HAL GPTMRY Capture Filter
  */
typedef enum 
{
    HAL_GPTMRY_CAP_FILTER_NONE     = LL_GPTMRY_CAP_FILTER_NONE,
    HAL_GPTMRY_CAP_FILTER_TDS_X1   = LL_GPTMRY_CAP_FILTER_TDS_X1,
    HAL_GPTMRY_CAP_FILTER_TDS_X2   = LL_GPTMRY_CAP_FILTER_TDS_X2,
    HAL_GPTMRY_CAP_FILTER_TDS_X3   = LL_GPTMRY_CAP_FILTER_TDS_X3,
    HAL_GPTMRY_CAP_FILTER_TDS_X4   = LL_GPTMRY_CAP_FILTER_TDS_X4,
    HAL_GPTMRY_CAP_FILTER_TDS_X5   = LL_GPTMRY_CAP_FILTER_TDS_X5,
    HAL_GPTMRY_CAP_FILTER_TDS_X6   = LL_GPTMRY_CAP_FILTER_TDS_X6,
    HAL_GPTMRY_CAP_FILTER_TDS_X7   = LL_GPTMRY_CAP_FILTER_TDS_X7,
    HAL_GPTMRY_CAP_FILTER_TDS_X8   = LL_GPTMRY_CAP_FILTER_TDS_X8,
    HAL_GPTMRY_CAP_FILTER_TDS_X9   = LL_GPTMRY_CAP_FILTER_TDS_X9,
    HAL_GPTMRY_CAP_FILTER_TDS_X10  = LL_GPTMRY_CAP_FILTER_TDS_X10,
    HAL_GPTMRY_CAP_FILTER_TDS_X11  = LL_GPTMRY_CAP_FILTER_TDS_X11,
    HAL_GPTMRY_CAP_FILTER_TDS_X12  = LL_GPTMRY_CAP_FILTER_TDS_X12,
    HAL_GPTMRY_CAP_FILTER_TDS_X13  = LL_GPTMRY_CAP_FILTER_TDS_X13,
    HAL_GPTMRY_CAP_FILTER_TDS_X14  = LL_GPTMRY_CAP_FILTER_TDS_X14,
    HAL_GPTMRY_CAP_FILTER_TDS_X15  = LL_GPTMRY_CAP_FILTER_TDS_X15,
} HAL_GPTMRY_CapFilTypeDef;

/**
  * @brief HAL GPTMRY Capture Prescaler Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_CAP_PRESCALER_1 = LL_GPTMRY_CAP_PRESCALER_1,
    HAL_GPTMRY_CAP_PRESCALER_2 = LL_GPTMRY_CAP_PRESCALER_2,
    HAL_GPTMRY_CAP_PRESCALER_4 = LL_GPTMRY_CAP_PRESCALER_4,
    HAL_GPTMRY_CAP_PRESCALER_8 = LL_GPTMRY_CAP_PRESCALER_8,
} HAL_GPTMRY_CapPrescalerTypeDef;


/**
  * @brief HAL GPTMRY Capture Input Map Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_CAP_INPUT_MAP_0     = LL_GPTMRY_CAP_INPUT_MAP_0,
    HAL_GPTMRY_CAP_INPUT_MAP_1     = LL_GPTMRY_CAP_INPUT_MAP_1,
    HAL_GPTMRY_CAP_INPUT_MAP_TRGI  = LL_GPTMRY_CAP_INPUT_MAP_TRGI,
} HAL_GPTMRY_CapInputMapTypeDef;

/**
  * @brief HAL GPTMRY Capture Input Source Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_CAP_INPUT_SRC_IN0  = LL_GPTMRY_CAP_INPUT_SRC_IN0,
    HAL_GPTMRY_CAP_INPUT_SRC_IN1  = LL_GPTMRY_CAP_INPUT_SRC_IN1,
    HAL_GPTMRY_CAP_INPUT_SRC_IN2  = LL_GPTMRY_CAP_INPUT_SRC_IN2,
    HAL_GPTMRY_CAP_INPUT_SRC_IN3  = LL_GPTMRY_CAP_INPUT_SRC_IN3,
    HAL_GPTMRY_CAP_INPUT_SRC_IN4  = LL_GPTMRY_CAP_INPUT_SRC_IN4,
    HAL_GPTMRY_CAP_INPUT_SRC_IN5  = LL_GPTMRY_CAP_INPUT_SRC_IN5,
    HAL_GPTMRY_CAP_INPUT_SRC_IN6  = LL_GPTMRY_CAP_INPUT_SRC_IN6,
    HAL_GPTMRY_CAP_INPUT_SRC_IN7  = LL_GPTMRY_CAP_INPUT_SRC_IN7,
    HAL_GPTMRY_CAP_INPUT_SRC_IN8  = LL_GPTMRY_CAP_INPUT_SRC_IN8,
    HAL_GPTMRY_CAP_INPUT_SRC_IN9  = LL_GPTMRY_CAP_INPUT_SRC_IN9,
    HAL_GPTMRY_CAP_INPUT_SRC_IN10 = LL_GPTMRY_CAP_INPUT_SRC_IN10,
    HAL_GPTMRY_CAP_INPUT_SRC_IN11 = LL_GPTMRY_CAP_INPUT_SRC_IN11,
    HAL_GPTMRY_CAP_INPUT_SRC_IN12 = LL_GPTMRY_CAP_INPUT_SRC_IN12,
    HAL_GPTMRY_CAP_INPUT_SRC_IN13 = LL_GPTMRY_CAP_INPUT_SRC_IN13,
    HAL_GPTMRY_CAP_INPUT_SRC_IN14 = LL_GPTMRY_CAP_INPUT_SRC_IN14,
    HAL_GPTMRY_CAP_INPUT_SRC_IN15 = LL_GPTMRY_CAP_INPUT_SRC_IN15,
} HAL_GPTMRY_CapInputSrcTypeDef;

/**
  * @brief HAL GPTMRY Compare Output Polarity Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_CMP_POL_HIGH  = LL_GPTMRY_CMP_POL_HIGH,
    HAL_GPTMRY_CMP_POL_LOW   = LL_GPTMRY_CMP_POL_LOW,
} HAL_GPTMRY_CmpPolTypeDef;

/**
  * @brief HAL GPTMRY Compare Output Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_CMP_MODE_FREEZE         = LL_GPTMRY_CMP_MODE_FREEZE,
    HAL_GPTMRY_CMP_MODE_ACTIVE         = LL_GPTMRY_CMP_MODE_ACTIVE,
    HAL_GPTMRY_CMP_MODE_INACTIVE       = LL_GPTMRY_CMP_MODE_INACTIVE,
    HAL_GPTMRY_CMP_MODE_TOGGLE         = LL_GPTMRY_CMP_MODE_TOGGLE,
    HAL_GPTMRY_CMP_MODE_FORCE_INACTIVE = LL_GPTMRY_CMP_MODE_FORCE_INACTIVE,
    HAL_GPTMRY_CMP_MODE_FORCE_ACTIVE   = LL_GPTMRY_CMP_MODE_FORCE_ACTIVE,
    HAL_GPTMRY_CMP_MODE_PWM1           = LL_GPTMRY_CMP_MODE_PWM1,
    HAL_GPTMRY_CMP_MODE_PWM2           = LL_GPTMRY_CMP_MODE_PWM2,
    HAL_GPTMRY_CMP_MODE_RETRIG_OPM1    = LL_GPTMRY_CMP_MODE_RETRIG_OPM1,
    HAL_GPTMRY_CMP_MODE_RETRIG_OPM2    = LL_GPTMRY_CMP_MODE_RETRIG_OPM2,
    HAL_GPTMRY_CMP_MODE_COMB_PWM1      = LL_GPTMRY_CMP_MODE_COMB_PWM1,
    HAL_GPTMRY_CMP_MODE_COMB_PWM2      = LL_GPTMRY_CMP_MODE_COMB_PWM2,
    HAL_GPTMRY_CMP_MODE_ASYM_PWM1      = LL_GPTMRY_CMP_MODE_ASYM_PWM1,
    HAL_GPTMRY_CMP_MODE_ASYM_PWM2      = LL_GPTMRY_CMP_MODE_ASYM_PWM2,
} HAL_GPTMRY_OCModeTypeDef;

/**
  * @brief HAL GPTMRY ETR Filter
  */
typedef enum 
{
    HAL_GPTMRY_ETR_FILTER_NONE     = LL_GPTMRY_ETR_FILTER_NONE,
    HAL_GPTMRY_ETR_FILTER_TDS_X1   = LL_GPTMRY_ETR_FILTER_TDS_X1,
    HAL_GPTMRY_ETR_FILTER_TDS_X2   = LL_GPTMRY_ETR_FILTER_TDS_X2,
    HAL_GPTMRY_ETR_FILTER_TDS_X3   = LL_GPTMRY_ETR_FILTER_TDS_X3,
    HAL_GPTMRY_ETR_FILTER_TDS_X4   = LL_GPTMRY_ETR_FILTER_TDS_X4,
    HAL_GPTMRY_ETR_FILTER_TDS_X5   = LL_GPTMRY_ETR_FILTER_TDS_X5,
    HAL_GPTMRY_ETR_FILTER_TDS_X6   = LL_GPTMRY_ETR_FILTER_TDS_X6,
    HAL_GPTMRY_ETR_FILTER_TDS_X7   = LL_GPTMRY_ETR_FILTER_TDS_X7,
    HAL_GPTMRY_ETR_FILTER_TDS_X8   = LL_GPTMRY_ETR_FILTER_TDS_X8,
    HAL_GPTMRY_ETR_FILTER_TDS_X9   = LL_GPTMRY_ETR_FILTER_TDS_X9,
    HAL_GPTMRY_ETR_FILTER_TDS_X10  = LL_GPTMRY_ETR_FILTER_TDS_X10,
    HAL_GPTMRY_ETR_FILTER_TDS_X11  = LL_GPTMRY_ETR_FILTER_TDS_X11,
    HAL_GPTMRY_ETR_FILTER_TDS_X12  = LL_GPTMRY_ETR_FILTER_TDS_X12,
    HAL_GPTMRY_ETR_FILTER_TDS_X13  = LL_GPTMRY_ETR_FILTER_TDS_X13,
    HAL_GPTMRY_ETR_FILTER_TDS_X14  = LL_GPTMRY_ETR_FILTER_TDS_X14,
    HAL_GPTMRY_ETR_FILTER_TDS_X15  = LL_GPTMRY_ETR_FILTER_TDS_X15,
} HAL_GPTMRY_ETRFilTypeDef;

/**
  * @brief HAL GPTMRY ETR Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_ETR_MODE_EXT_CLK_1 = LL_GPTMRY_ETR_MODE_EXT_CLK_1,
    HAL_GPTMRY_ETR_MODE_EXT_CLK_2 = LL_GPTMRY_ETR_MODE_EXT_CLK_2,
} HAL_GPTMRY_ETRModeTypeDef;


/**
  * @brief HAL GPTMRY ETR Edge Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_ETR_EDGE_MODE_CLOSE           = LL_GPTMRY_ETR_EDGE_MODE_CLOSE,
    HAL_GPTMRY_ETR_EDGE_MODE_RISING          = LL_GPTMRY_ETR_EDGE_MODE_RISING,
    HAL_GPTMRY_ETR_EDGE_MODE_FALLING         = LL_GPTMRY_ETR_EDGE_MODE_FALLING,
    HAL_GPTMRY_ETR_EDGE_MODE_RISING_FALLING  = LL_GPTMRY_ETR_EDGE_MODE_RISING_FALLING,
} HAL_GPTMRY_ETREdgeTypeDef;

/**
  * @brief HAL TI0 Input Source Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_TI0_IN_SRC_CH0          = LL_GPTMRY_TI0_IN_SRC_CH0, 
    HAL_GPTMRY_TI0_IN_SRC_CH0_1_2_XOR  = LL_GPTMRY_TI0_IN_SRC_CH0_1_2_XOR
} HAL_GPTMRY_TI0InSrcTypeDef;

/**
  * @brief HAL GPTMRY Slave Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_SLV_MODE_DIS        = LL_GPTMRY_SLV_MODE_DIS,
    HAL_GPTMRY_SLV_MODE_RST        = LL_GPTMRY_SLV_MODE_RST,
    HAL_GPTMRY_SLV_MODE_GATING     = LL_GPTMRY_SLV_MODE_GATING,
    HAL_GPTMRY_SLV_MODE_TRIG       = LL_GPTMRY_SLV_MODE_TRIG,
    HAL_GPTMRY_SLV_MODE_EXTCLK     = LL_GPTMRY_SLV_MODE_EXTCLK,
    HAL_GPTMRY_SLV_MODE_RST_TRIG   = LL_GPTMRY_SLV_MODE_RST_TRIG,
    HAL_GPTMRY_SLV_MODE_RST_GATING = LL_GPTMRY_SLV_MODE_RST_GATING,
} HAL_GPTMRY_SlvModeTypeDef;

/**
  * @brief HAL GPTMRY Trig Enumeration 
  */
typedef enum 
{
    HAL_GPTMRY_TRIG_ITR0  = LL_GPTMRY_TRIG_ITR0,
    HAL_GPTMRY_TRIG_ITR1  = LL_GPTMRY_TRIG_ITR1,
    HAL_GPTMRY_TRIG_ITR2  = LL_GPTMRY_TRIG_ITR2,
    HAL_GPTMRY_TRIG_ITR3  = LL_GPTMRY_TRIG_ITR3,
    HAL_GPTMRY_TRIG_ITR4  = LL_GPTMRY_TRIG_ITR4,
    HAL_GPTMRY_TRIG_ITR5  = LL_GPTMRY_TRIG_ITR5,
    HAL_GPTMRY_TRIG_ITR6  = LL_GPTMRY_TRIG_ITR6,
    HAL_GPTMRY_TRIG_ITR7  = LL_GPTMRY_TRIG_ITR7,
    HAL_GPTMRY_TRIG_ITR8  = LL_GPTMRY_TRIG_ITR8,
    HAL_GPTMRY_TRIG_ITR9  = LL_GPTMRY_TRIG_ITR9,
    HAL_GPTMRY_TRIG_ITR10 = LL_GPTMRY_TRIG_ITR10,
    HAL_GPTMRY_TRIG_ITR11 = LL_GPTMRY_TRIG_ITR11,
    HAL_GPTMRY_TRIG_ITR12 = LL_GPTMRY_TRIG_ITR12,
    HAL_GPTMRY_TRIG_ITR13 = LL_GPTMRY_TRIG_ITR13,
    HAL_GPTMRY_TRIG_ITR14 = LL_GPTMRY_TRIG_ITR14,
    HAL_GPTMRY_TRIG_ITR15 = LL_GPTMRY_TRIG_ITR15,
    HAL_GPTMRY_TRIG_CH0_FE = LL_GPTMRY_TRIG_CH0_FE,
    HAL_GPTMRY_TRIG_CH0_F = LL_GPTMRY_TRIG_CH0_F,
    HAL_GPTMRY_TRIG_CH1_F = LL_GPTMRY_TRIG_CH1_F,
    HAL_GPTMRY_TRIG_CH2_F = LL_GPTMRY_TRIG_CH2_F,
    HAL_GPTMRY_TRIG_CH3_F = LL_GPTMRY_TRIG_CH3_F,
    HAL_GPTMRY_TRIG_ETR_FE = LL_GPTMRY_TRIG_ETR_FE,
    HAL_GPTMRY_TRIG_ETR_F = LL_GPTMRY_TRIG_ETR_F,
} HAL_GPTMRY_TrigTypeDef;

/**
  * @brief HAL GPTMRY Event Source Enumeration 
  */
typedef enum
{
    HAL_GPTMRY_EVENTSOURCE_UPDATE  =   LL_GPTMRY_EVT_GEN_UPDATE,
    HAL_GPTMRY_EVENTSOURCE_TRIG    =   LL_GPTMRY_EVT_GEN_TRIGGER,
    HAL_GPTMRY_EVENTSOURCE_CC0     =   LL_GPTMRY_EVT_GEN_CAP_CMP_0,
    HAL_GPTMRY_EVENTSOURCE_CC1     =   LL_GPTMRY_EVT_GEN_CAP_CMP_1,
    HAL_GPTMRY_EVENTSOURCE_CC2     =   LL_GPTMRY_EVT_GEN_CAP_CMP_2,
    HAL_GPTMRY_EVENTSOURCE_CC3     =   LL_GPTMRY_EVT_GEN_CAP_CMP_3,
} HAL_GPTMRY_EvtSrcTypeDef;


/**
  * @brief  GPTMRY Base Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRY_EnableTypeDef          AutoReloadPreload;      /*!< Auto Preload Enable                        */
    HAL_GPTMRY_WorkModeTypeDef        WorkMode;               /*!< Work Mode: Continue/Single                 */
    uint32_t                          Period;                 /*!< Period Value                               */
    uint16_t                          Prescaler;              /*!< Clock Prescaler                            */
    HAL_GPTMRY_UpdateEvtDisTypeDef    UpdateEvent;            /*!< Update Event Enable                        */
    HAL_GPTMRY_UpdateEvtSrcTypeDef    UpdateSource;           /*!< Update Event Source                        */
    HAL_GPTMRY_CounterModeTypeDef     CounterMode;            /*!< Counter Mode                               */
} HAL_GPTMRY_BaseInitTypeDef;

/**
  * @brief  GPTMRY Master Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRY_MstModeTypeDef         MasterMode;             /*!< Master Mode (TRGO source)          */
    uint8_t                           TRGCCWidth;             /*!< TRGCC Output Width                 */
    uint8_t                           TRGOWidth;              /*!< TRGO Output Width                  */
    HAL_GPTMRY_TrigOutChMskTypeDef    TRGOSelection;          /*!< Trigger Output Channel Selection   */
} HAL_GPTMRY_MstInitTypeDef;

/**
  * @brief  GPTMRY Input Capture Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRY_CapFilTypeDef          ICFilter;               /*!< Input Capture Filter               */
    HAL_GPTMRY_CapPolTypeDef          ICPolarity;             /*!< Input Capture Polarity             */
    HAL_GPTMRY_CapInputMapTypeDef     ICSelection;            /*!< Input Capture Map                  */
    HAL_GPTMRY_CapPrescalerTypeDef    ICPrescaler;            /*!< Input Capture Prescaler            */
    HAL_GPTMRY_CapInputSrcTypeDef     ICTriggerSource;        /*!< Input Capture Trigger Input Source */
} HAL_GPTMRY_InputCapInitTypeDef;

/**
  * @brief  GPTMRY Output Compare Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRY_EnableTypeDef          CompareAutoReload;      /*!< Output Compare Auto Preload Enable */
    uint32_t                          CompareValue;           /*!< Output Compare Match Value         */
    HAL_GPTMRY_OCModeTypeDef          OCMode;                 /*!< Output Compare Mode                */
    HAL_GPTMRY_CmpPolTypeDef          OCPolarity;             /*!< OC Polarity                        */
    HAL_GPTMRY_CmpPolTypeDef          OCNPolarity;            /*!< OCN Polarity                       */
} HAL_GPTMRY_OutputCmpInitTypeDef;

/**
  * @brief  GPTMRY Slave / ETR Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRY_SlvModeTypeDef         SlaveMode;              /*!< Slave Mode                         */
    HAL_GPTMRY_TrigTypeDef            InputTrigger;           /*!< Trigger Selection                  */
    HAL_GPTMRY_ETREdgeTypeDef         TriggerPolarity;        /*!< ETR Edge Mode                      */
    HAL_GPTMRY_ETRFilTypeDef          TriggerFilter;          /*!< ETR Filter                         */
    HAL_GPTMRY_ETRModeTypeDef         ExtClokMode;            /*!< ETR Mode                           */
} HAL_GPTMRY_SlvInitTypeDef;


/**
  * @brief HAL GPTMRY handle structure type
  */
typedef struct HAL_GPTMRY_HandleStructDef HAL_GPTMRY_HandleTypeDef;

/**
  * @brief GPTMRY IRQ callback function type definition
  */
typedef void (*HAL_GPTMRY_IRQCallback)(HAL_GPTMRY_HandleTypeDef *Handle);

/**
  * @brief  GPTMRY Handle Structure definition
  */
struct HAL_GPTMRY_HandleStructDef
{
    GPTMRy_TypeDef                           *Instance;       /*!< Register base address      */
    volatile HAL_GPTMRY_StateTypeDef         State;           /*!< GPTMRY operation state     */
    volatile HAL_GPTMRY_ErrCodeMskTypeDef    LastErrorCodes;  /*!< Last error codes           */
    const void                              *pUserData;       /*!< User data pointer          */
};
/**
  * @}
  */ /* GPTMRY_HAL_Exported_Types */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPTMRY_HAL_Exported_Functions GPTMRY HAL Exported Functions
  * @{
  */

/** @defgroup GPTMRY_HAL_EF_Initialization GPTMRY HAL Initialization
  * @{
  */

HAL_StatusTypeDef HAL_GPTMRY_Base_Init(HAL_GPTMRY_HandleTypeDef *Handle, 
                                      GPTMRy_TypeDef *GPTMRy,
                                      const HAL_GPTMRY_BaseInitTypeDef *pInit);
                              
HAL_StatusTypeDef HAL_GPTMRY_Base_DeInit(HAL_GPTMRY_HandleTypeDef *Handle);

void HAL_GPTMRY_Base_MspInit(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_Base_MspDeInit(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_IoInit(GPTMRy_TypeDef *GPTMRy);
void HAL_GPTMRY_IoDeInit(GPTMRy_TypeDef *GPTMRy);
/**
  * @}
  */

/** @defgroup GPTMRY_HAL_EF_Configuration GPTMRY HAL Configuration
  * @{
  */

HAL_StatusTypeDef HAL_GPTMRY_IC_Init(HAL_GPTMRY_HandleTypeDef *Handle, 
                                    HAL_GPTMRY_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRY_InputCapInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRY_OC_Init(HAL_GPTMRY_HandleTypeDef *Handle, 
                                    HAL_GPTMRY_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRY_OutputCmpInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRY_InitMaster(HAL_GPTMRY_HandleTypeDef *Handle,
                                       const HAL_GPTMRY_MstInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRY_InitSlave(HAL_GPTMRY_HandleTypeDef *Handle,
                                      const HAL_GPTMRY_SlvInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRY_ConfigTI0InputSource(HAL_GPTMRY_HandleTypeDef *Handle, 
                                                 HAL_GPTMRY_TI0InSrcTypeDef Source);
/**
  * @}
  */

/** @defgroup GPTMRY_HAL_EF_IO_Operation GPTMRY HAL IO Operation
  * @{
  */
HAL_StatusTypeDef HAL_GPTMRY_Base_Start(HAL_GPTMRY_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_GPTMRY_Base_Stop(HAL_GPTMRY_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_GPTMRY_Base_Start_IT(HAL_GPTMRY_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_GPTMRY_Base_Stop_IT(HAL_GPTMRY_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_GPTMRY_OC_Start(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRY_OC_Stop(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRY_OC_StartIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRY_OC_StopIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_GPTMRY_IC_Start(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRY_IC_Stop(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRY_IC_StartIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRY_IC_StopIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_GPTMRY_GenerateEvent(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_EvtSrcTypeDef EventSource);

uint32_t HAL_GPTMRY_ReadCounter(const HAL_GPTMRY_HandleTypeDef *Handle);
uint32_t HAL_GPTMRY_ReadCapturedValue(const HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
/**
  * @}
  */

/** @defgroup GPTMRY_HAL_EF_IRQ_Handler GPTMRY HAL IRQ Handler and Callbacks
  * @{
  */

HAL_StatusTypeDef HAL_GPTMRY_InterruptRequestEnable(HAL_GPTMRY_HandleTypeDef *Handle, 
                                                   HAL_GPTMRY_ITEnMskTypeDef ITMask);

HAL_StatusTypeDef HAL_GPTMRY_InterruptRequestDisable(HAL_GPTMRY_HandleTypeDef *Handle, 
                                                    HAL_GPTMRY_ITEnMskTypeDef ITMask);

void HAL_GPTMRY_UPD_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_TRG_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_CC_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_CCx_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);

void HAL_GPTMRY_OverflowCallback(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_PeriodElapsedCallback(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_TriggerCallback(HAL_GPTMRY_HandleTypeDef *Handle);
void HAL_GPTMRY_OC_DelayElapsedCallback(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
void HAL_GPTMRY_IC_CaptureCallback(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
void HAL_GPTMRY_IC_OverCaptureCallback(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel);
/**
  * @}
  */

/**
  * @}
  */ /* GPTMRY_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

#endif /* HAL_GPTMRY_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* GPTMRY */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_GPTMRY_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
