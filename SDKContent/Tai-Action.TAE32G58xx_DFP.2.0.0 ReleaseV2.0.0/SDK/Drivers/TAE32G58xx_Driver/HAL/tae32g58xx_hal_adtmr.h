/**
  ******************************************************************************
  * @file    tae32g58xx_hal_adtmr.h
  * @author  Tai-Action SD Team
  * @brief   Header file for ADTMR HAL module.
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
#ifndef _TAE32G58XX_HAL_ADTMR_H_
#define _TAE32G58XX_HAL_ADTMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_adtmr.h"

#if defined(TMR9) || defined(TMR10)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_ADTMR_MODULE_ENABLED) && (HAL_ADTMR_MODULE_ENABLED == 1)


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup ADTMR_HAL_Exported_Macros ADTMR HAL Exported Macros
  * @{
  */

/** @defgroup ADTMR_HAL_EM_Assert ADTMR HAL Assert 
  * @brief    ADTMR HAL Assert
  * @{
  */

#ifndef TAE32_USE_HAL_ADTMR_CHECK_PARAM
#define TAE32_USE_HAL_ADTMR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_ADTMR_CHECK_PARAM != 1) && (TAE32_USE_HAL_ADTMR_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_ADTMR_CHECK_PARAM
#define TAE32_USE_HAL_ADTMR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_ADTMR_CHECK_PARAM */

#define HAL_ADTMR_PARAM_CHECK(expression)     \
        if (TAE32_USE_HAL_ADTMR_CHECK_PARAM) { \
            expression;                        \
        }
/**
  * @}
  */ /* ADTMR_HAL_EM_Assert */


/**
 * @brief Updates a ADTMR HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the ADTMR process
 * state check feature is enabled (TAE32_USE_HAL_ADTMR_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_ADTMR_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_ADTMR_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_ADTMR_CHECK_PROCESS_STATE == 1)
#define HAL_ADTMR_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_ADTMR_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        do {                                                                      \
            if ((upd_parm) != (check_value)) {                                    \
                failed_expression;                                                \
                break;                                                            \
            } else {                                                              \
                (upd_parm) = (new_value);                                         \
            }                                                                     \
        } while(0)    
#endif



/** @defgroup ADTMR_HAL_EM_Mask ADTMR HAL Mask
  * @brief    ADTMR HAL State / Error / Interrupt mask definitions
  * @{
  */

/** @name   HAL_ADTMR_StateMaskTypeDef 
  * @brief  HAL ADTMR global state mask definition. 
  * @{
  */
#define HAL_ADTMR_StateMaskTypeDef                          uint32_t

#define HAL_ADTMR_STATE_MASK_RESET                          (0U)         /*!< ADTMR not yet initialized                     */
#define HAL_ADTMR_STATE_MASK_CONFIGURABLE                   (1U << 30U)  /*!< ADTMR is configurable                         */
#define HAL_ADTMR_STATE_MASK_BUSY                           (1U << 29U)  /*!< An internal process is ongoing                */
#define HAL_ADTMR_STATE_MASK_TIMEOUT                        (1U << 28U)  /*!< Timeout state                                 */
#define HAL_ADTMR_STATE_MASK_ERROR                          (1U << 27U)  /*!< Error state                                   */
/** @} */

/** @name   HAL_ADTMR_ErrCodeMskTypeDef
  * @brief  HAL ADTMR Error Code Mask definition.
  * @{
  */
#define HAL_ADTMR_ErrCodeMskTypeDef                         uint32_t

#define HAL_ADTMR_ERROR_NONE                                (0U)         /*!< No error                     */
#define HAL_ADTMR_ERROR_INVALID_INSTANCE                    (1U << 30U)  /*!< Invalid instance error       */
/** @} */

/** @name   HAL_ADTMR_ITEnMskTypeDef
  * @brief  HAL ADTMR Interrupt Enable Mask Definition
  * @{
  */
#define HAL_ADTMR_ITEnMskTypeDef                            LL_ADTMR_IER_ITEnMskTypeDef

#define HAL_ADTMR_IER_BREAK_IT_EN                           LL_ADTMR_IER_BIE     /*!< Break interrupt enable mask               */
#define HAL_ADTMR_IER_TRIGGER_IT_EN                         LL_ADTMR_IER_TIE     /*!< Trigger interrupt enable mask             */
#define HAL_ADTMR_IER_OVERFLOW_IT_EN                        LL_ADTMR_IER_OVIE    /*!< Overflow interrupt enable mask            */
#define HAL_ADTMR_IER_UPDATE_IT_EN                          LL_ADTMR_IER_UIE     /*!< Update interrupt enable mask              */
#define HAL_ADTMR_IER_CH3_CAPTURE_OR_COMPARE_IT_EN          LL_ADTMR_IER_C3MIE   /*!< CH3 Capture/Compare interrupt enable mask */
#define HAL_ADTMR_IER_CH3_OVER_CAPTURE_IT_EN                LL_ADTMR_IER_C3OIE   /*!< CH3 OverCapture interrupt enable mask     */
#define HAL_ADTMR_IER_CH2_CAPTURE_OR_COMPARE_IT_EN          LL_ADTMR_IER_C2MIE   /*!< CH2 Capture/Compare interrupt enable mask */
#define HAL_ADTMR_IER_CH2_OVER_CAPTURE_IT_EN                LL_ADTMR_IER_C2OIE   /*!< CH2 OverCapture interrupt enable mask     */
#define HAL_ADTMR_IER_CH1_CAPTURE_OR_COMPARE_IT_EN          LL_ADTMR_IER_C1MIE   /*!< CH1 Capture/Compare interrupt enable mask */
#define HAL_ADTMR_IER_CH1_OVER_CAPTURE_IT_EN                LL_ADTMR_IER_C1OIE   /*!< CH1 OverCapture interrupt enable mask     */
#define HAL_ADTMR_IER_CH0_CAPTURE_OR_COMPARE_IT_EN          LL_ADTMR_IER_C0MIE   /*!< CH0 Capture/Compare interrupt enable mask */
#define HAL_ADTMR_IER_CH0_OVER_CAPTURE_IT_EN                LL_ADTMR_IER_C0OIE   /*!< CH0 OverCapture interrupt enable mask     */
/** @} */

/** @name   HAL_ADTMR_ITPendingMskTypeDef
  * @brief  HAL ADTMR Interrupt Flag Mask Definition
  * @{
  */
#define HAL_ADTMR_ITPendingMskTypeDef                       LL_ADTMR_SR_ITPendingMskTypeDef

#define HAL_ADTMR_SR_BREAK1_IT_FLAG                         LL_ADTMR_SR_B1IF     /*!< Break input 1 interrupt flag mask         */
#define HAL_ADTMR_SR_SYSFAULT_BREAK_IT_FLAG                 LL_ADTMR_SR_SBIF     /*!< System fault break interrupt flag mask    */
#define HAL_ADTMR_SR_BREAK0_IT_FLAG                         LL_ADTMR_SR_B0IF     /*!< Break input 0 interrupt flag mask         */
#define HAL_ADTMR_SR_TRIGGER_IT_FLAG                        LL_ADTMR_SR_TIF      /*!< Trigger interrupt flag mask               */
#define HAL_ADTMR_SR_OVERFLOW_IT_FLAG                       LL_ADTMR_SR_OVIF     /*!< Overflow interrupt flag mask              */
#define HAL_ADTMR_SR_UPDATE_IT_FLAG                         LL_ADTMR_SR_UIF      /*!< Update interrupt flag mask                */
#define HAL_ADTMR_SR_CH3_CAPTURE_OR_COMPARE_IT_FLAG         LL_ADTMR_SR_CC3MIF   /*!< CH3 Capture/Compare interrupt flag mask   */
#define HAL_ADTMR_SR_CH3_OVER_CAPTURE_IT_FLAG               LL_ADTMR_SR_CC3OIF   /*!< CH3 OverCapture interrupt flag mask       */
#define HAL_ADTMR_SR_CH2_CAPTURE_OR_COMPARE_IT_FLAG         LL_ADTMR_SR_CC2MIF   /*!< CH2 Capture/Compare interrupt flag mask   */
#define HAL_ADTMR_SR_CH2_OVER_CAPTURE_IT_FLAG               LL_ADTMR_SR_CC2OIF   /*!< CH2 OverCapture interrupt flag mask       */
#define HAL_ADTMR_SR_CH1_CAPTURE_OR_COMPARE_IT_FLAG         LL_ADTMR_SR_CC1MIF   /*!< CH1 Capture/Compare interrupt flag mask   */
#define HAL_ADTMR_SR_CH1_OVER_CAPTURE_IT_FLAG               LL_ADTMR_SR_CC1OIF   /*!< CH1 OverCapture interrupt flag mask       */
#define HAL_ADTMR_SR_CH0_CAPTURE_OR_COMPARE_IT_FLAG         LL_ADTMR_SR_CC0MIF   /*!< CH0 Capture/Compare interrupt flag mask   */
#define HAL_ADTMR_SR_CH0_OVER_CAPTURE_IT_FLAG               LL_ADTMR_SR_CC0OIF   /*!< CH0 OverCapture interrupt flag mask       */
/** @} */


/** @name   HAL_ADTMR_TrigOutChMskTypeDef
  * @brief  HAL ADTMR TRGO Channel Mask Definition
  * @{
  */
#define HAL_ADTMR_TrigOutChMskTypeDef                       LL_ADTMR_TTCR_TrigOutChMskTypeDef

#define HAL_ADTMR_TRGI_OUT_SELECT_CH3_MASK                  LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH3
#define HAL_ADTMR_TRGI_OUT_SELECT_CH2_MASK                  LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH2
#define HAL_ADTMR_TRGI_OUT_SELECT_CH1_MASK                  LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH1
#define HAL_ADTMR_TRGI_OUT_SELECT_CH0_MASK                  LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH0
/** @} */

/**
  * @}
  */ /* ADTMR_HAL_EM_Mask */

/**
  * @}
  */ /* ADTMR_HAL_Exported_Macros */

/* Exported types ------------------------------------------------------------*/


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @addtogroup ADTMR_HAL
  * @brief    ADTMR HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADTMR_HAL_Exported_Types ADTMR HAL Exported Types
  * @brief    ADTMR HAL Exported Types
  * @{
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
/**
  * @brief  HAL ADTMR State definition
  */
typedef enum
{
    HAL_ADTMR_STATE_RESET           = HAL_ADTMR_STATE_MASK_RESET,         /*!< ADTMR not yet initialized           */
    HAL_ADTMR_STATE_CONFIGURABLE    = HAL_ADTMR_STATE_MASK_CONFIGURABLE,  /*!< ADTMR is configurable  */
    HAL_ADTMR_STATE_BUSY            = HAL_ADTMR_STATE_MASK_BUSY,          /*!< An internal process is ongoing      */
    HAL_ADTMR_STATE_TIMEOUT         = HAL_ADTMR_STATE_MASK_TIMEOUT,       /*!< Timeout state                       */
    HAL_ADTMR_STATE_ERROR           = HAL_ADTMR_STATE_MASK_ERROR          /*!< Error state                         */
} HAL_ADTMR_StateTypeDef;

_Static_assert(sizeof(HAL_ADTMR_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else /* TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

typedef HAL_ADTMR_StateMaskTypeDef      HAL_ADTMR_StateTypeDef;
#define HAL_ADTMR_STATE_RESET           HAL_ADTMR_STATE_MASK_RESET
#define HAL_ADTMR_STATE_CONFIGURABLE    HAL_ADTMR_STATE_MASK_CONFIGURABLE
#define HAL_ADTMR_STATE_BUSY            HAL_ADTMR_STATE_MASK_BUSY
#define HAL_ADTMR_STATE_TIMEOUT         HAL_ADTMR_STATE_MASK_TIMEOUT
#define HAL_ADTMR_STATE_ERROR           HAL_ADTMR_STATE_MASK_ERROR
#endif /* !TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

/**
 * @brief 
 */
typedef enum
{
    HAL_ADTMR_FUNC_DISABLE  = 0U,    /*!< ADTMR Function Disable  */
    HAL_ADTMR_FUNC_ENABLE   = 1U     /*!< ADTMR Function Enable   */
} HAL_ADTMR_EnableTypeDef;

/**
 * @brief HAL ADTMR Channel Index Enumeration 
 */
typedef enum
{
    HAL_ADTMR_BREAK_INPUT_BK0 = 0U, /*!< ADTMR Break input BK0  */
    HAL_ADTMR_BREAK_INPUT_BK1 = 1U  /*!< ADTMR Break input BK1  */
} HAL_ADTMR_BreakInputTypeDef;

/**
  * @brief HAL ADTMR Channel Index Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_CHANNEL_0     = LL_ADTMR_CAP_CMP_CH_0,
    HAL_ADTMR_CHANNEL_1     = LL_ADTMR_CAP_CMP_CH_1,
    HAL_ADTMR_CHANNEL_2     = LL_ADTMR_CAP_CMP_CH_2,
    HAL_ADTMR_CHANNEL_3     = LL_ADTMR_CAP_CMP_CH_3,
    HAL_ADTMR_CHANNEL_NUMS  = LL_ADTMR_CAP_CMP_CH_NUMS
} HAL_ADTMR_ChannelIdxTypeDef;

/**
  * @brief HAL ADTMR Work Mode Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_WORK_MODE_CONTINUE  = LL_ADTMR_WORK_MODE_CONTINUE,
    HAL_ADTMR_WORK_MODE_SINGLE    = LL_ADTMR_WORK_MODE_SINGLE,
} HAL_ADTMR_WorkModeTypeDef;

/**
  * @brief HAL ADTMR Update Event Disable Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_UPDATE_EVT_RELEASE  = 0UL,
    HAL_ADTMR_UPDATE_EVT_ASSERT   = 1UL,
} HAL_ADTMR_UpdateEvtDisTypeDef;

/**
  * @brief HAL ADTMR Update Event Source Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_UPDATE_EVT_SRC_OV_UG  = LL_ADTMR_UPDATE_EVT_SRC_OV_UG,
    HAL_ADTMR_UPDATE_EVT_SRC_OV     = LL_ADTMR_UPDATE_EVT_SRC_OV,
} HAL_ADTMR_UpdateEvtSrcTypeDef;

/**
  * @brief Timer Output Idle State Definition
  */
typedef enum 
{
    HAL_ADTMR_OUTPUT_IDLE_STA_LOW   = LL_ADTMR_OUTPUT_IDLE_STA_LOW,    /*!<  Output Idle State Low     */
    HAL_ADTMR_OUTPUT_IDLE_STA_HIGH  = LL_ADTMR_OUTPUT_IDLE_STA_HIGH,       /*!<  Output Idle State High    */
} HAL_ADTMR_IdleStaTypeDef;

/**
  * @brief HAL ADTMR Master Mode Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_MST_MODE_RESET        = LL_ADTMR_MST_MODE_RESET,
    HAL_ADTMR_MST_MODE_ENABLE       = LL_ADTMR_MST_MODE_ENABLE,
    HAL_ADTMR_MST_MODE_UPDATE       = LL_ADTMR_MST_MODE_UPDATE,
    HAL_ADTMR_MST_MODE_CAP_CMP_EVT  = LL_ADTMR_MST_MODE_CAP_CMP_EVT,
    HAL_ADTMR_MST_MODE_CMP_OUT0     = LL_ADTMR_MST_MODE_OC0REF,
    HAL_ADTMR_MST_MODE_CMP_OUT1     = LL_ADTMR_MST_MODE_OC1REF,
    HAL_ADTMR_MST_MODE_CMP_OUT2     = LL_ADTMR_MST_MODE_OC2REF,
    HAL_ADTMR_MST_MODE_CMP_OUT3     = LL_ADTMR_MST_MODE_OC3REF,
} HAL_ADTMR_MstModeTypeDef;

/**
  * @brief HAL ADTMR Counter Mode Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_COUNTER_MODE_UP               = 0UL,
    HAL_ADTMR_COUNTER_MODE_DOWN             = 1UL,
    HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED1  = 2UL,
    HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED2  = 3UL,
    HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED3  = 4UL,
} HAL_ADTMR_CounterModeTypeDef;

/**
  * @brief HAL ADTMR Clock Division Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_1 = LL_ADTMR_DZ_DIG_FIL_CLK_DIV_1,
    HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_2 = LL_ADTMR_DZ_DIG_FIL_CLK_DIV_2,
    HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_4 = LL_ADTMR_DZ_DIG_FIL_CLK_DIV_4,
    HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_8 = LL_ADTMR_DZ_DIG_FIL_CLK_DIV_8,
} HAL_ADTMR_DzDigFilClkDivTypeDef;

/**
  * @brief HAL ADTMR Capture Polarity Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_CAP_POL_CLOSE     = LL_ADTMR_CAP_POL_CLOSE,
    HAL_ADTMR_CAP_POL_RISING    = LL_ADTMR_CAP_POL_RISING,
    HAL_ADTMR_CAP_POL_FALLING   = LL_ADTMR_CAP_POL_FALLING,
    HAL_ADTMR_CAP_POL_BOTH_EDGE = LL_ADTMR_CAP_POL_BOTH_EDGE,
} HAL_ADTMR_CapPolTypeDef;

/**
  * @brief HAL ADTMR Capture Filter
  */
typedef enum 
{
    HAL_ADTMR_CAP_FILTER_NONE     = LL_ADTMR_CAP_FILTER_NONE,
    HAL_ADTMR_CAP_FILTER_TDS_X1   = LL_ADTMR_CAP_FILTER_TDS_X1,
    HAL_ADTMR_CAP_FILTER_TDS_X2   = LL_ADTMR_CAP_FILTER_TDS_X2,
    HAL_ADTMR_CAP_FILTER_TDS_X3   = LL_ADTMR_CAP_FILTER_TDS_X3,
    HAL_ADTMR_CAP_FILTER_TDS_X4   = LL_ADTMR_CAP_FILTER_TDS_X4,
    HAL_ADTMR_CAP_FILTER_TDS_X5   = LL_ADTMR_CAP_FILTER_TDS_X5,
    HAL_ADTMR_CAP_FILTER_TDS_X6   = LL_ADTMR_CAP_FILTER_TDS_X6,
    HAL_ADTMR_CAP_FILTER_TDS_X7   = LL_ADTMR_CAP_FILTER_TDS_X7,
    HAL_ADTMR_CAP_FILTER_TDS_X8   = LL_ADTMR_CAP_FILTER_TDS_X8,
    HAL_ADTMR_CAP_FILTER_TDS_X9   = LL_ADTMR_CAP_FILTER_TDS_X9,
    HAL_ADTMR_CAP_FILTER_TDS_X10  = LL_ADTMR_CAP_FILTER_TDS_X10,
    HAL_ADTMR_CAP_FILTER_TDS_X11  = LL_ADTMR_CAP_FILTER_TDS_X11,
    HAL_ADTMR_CAP_FILTER_TDS_X12  = LL_ADTMR_CAP_FILTER_TDS_X12,
    HAL_ADTMR_CAP_FILTER_TDS_X13  = LL_ADTMR_CAP_FILTER_TDS_X13,
    HAL_ADTMR_CAP_FILTER_TDS_X14  = LL_ADTMR_CAP_FILTER_TDS_X14,
    HAL_ADTMR_CAP_FILTER_TDS_X15  = LL_ADTMR_CAP_FILTER_TDS_X15,
} HAL_ADTMR_CapFilTypeDef;

/**
  * @brief HAL ADTMR Capture Prescaler Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_CAP_PRESCALER_1 = LL_ADTMR_CAP_PRESCALER_1,
    HAL_ADTMR_CAP_PRESCALER_2 = LL_ADTMR_CAP_PRESCALER_2,
    HAL_ADTMR_CAP_PRESCALER_4 = LL_ADTMR_CAP_PRESCALER_4,
    HAL_ADTMR_CAP_PRESCALER_8 = LL_ADTMR_CAP_PRESCALER_8,
} HAL_ADTMR_CapPrescalerTypeDef;

/**
  * @brief HAL ADTMR Capture Input Map Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_CAP_INPUT_MAP_0     = LL_ADTMR_CAP_INPUT_MAP_0,
    HAL_ADTMR_CAP_INPUT_MAP_1     = LL_ADTMR_CAP_INPUT_MAP_1,
    HAL_ADTMR_CAP_INPUT_MAP_TRGI  = LL_ADTMR_CAP_INPUT_MAP_TRGI,
} HAL_ADTMR_CapInputMapTypeDef;

/**
  * @brief HAL ADTMR Capture Input Source Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_CAP_INPUT_SRC_IN0  = LL_ADTMR_CAP_INPUT_SRC_IN0,
    HAL_ADTMR_CAP_INPUT_SRC_IN1  = LL_ADTMR_CAP_INPUT_SRC_IN1,
    HAL_ADTMR_CAP_INPUT_SRC_IN2  = LL_ADTMR_CAP_INPUT_SRC_IN2,
    HAL_ADTMR_CAP_INPUT_SRC_IN3  = LL_ADTMR_CAP_INPUT_SRC_IN3,
    HAL_ADTMR_CAP_INPUT_SRC_IN4  = LL_ADTMR_CAP_INPUT_SRC_IN4,
    HAL_ADTMR_CAP_INPUT_SRC_IN5  = LL_ADTMR_CAP_INPUT_SRC_IN5,
    HAL_ADTMR_CAP_INPUT_SRC_IN6  = LL_ADTMR_CAP_INPUT_SRC_IN6,
    HAL_ADTMR_CAP_INPUT_SRC_IN7  = LL_ADTMR_CAP_INPUT_SRC_IN7,
    HAL_ADTMR_CAP_INPUT_SRC_IN8  = LL_ADTMR_CAP_INPUT_SRC_IN8,
    HAL_ADTMR_CAP_INPUT_SRC_IN9  = LL_ADTMR_CAP_INPUT_SRC_IN9,
    HAL_ADTMR_CAP_INPUT_SRC_IN10 = LL_ADTMR_CAP_INPUT_SRC_IN10,
    HAL_ADTMR_CAP_INPUT_SRC_IN11 = LL_ADTMR_CAP_INPUT_SRC_IN11,
    HAL_ADTMR_CAP_INPUT_SRC_IN12 = LL_ADTMR_CAP_INPUT_SRC_IN12,
    HAL_ADTMR_CAP_INPUT_SRC_IN13 = LL_ADTMR_CAP_INPUT_SRC_IN13,
    HAL_ADTMR_CAP_INPUT_SRC_IN14 = LL_ADTMR_CAP_INPUT_SRC_IN14,
    HAL_ADTMR_CAP_INPUT_SRC_IN15 = LL_ADTMR_CAP_INPUT_SRC_IN15,
} HAL_ADTMR_CapInputSrcTypeDef;

/**
  * @brief HAL ADTMR Compare Output Polarity Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_CMP_POL_HIGH  = LL_ADTMR_CMP_POL_HIGH,
    HAL_ADTMR_CMP_POL_LOW   = LL_ADTMR_CMP_POL_LOW,
} HAL_ADTMR_CmpPolTypeDef;

/**
  * @brief HAL ADTMR Compare Output Mode Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_CMP_MODE_FREEZE         = LL_ADTMR_CMP_MODE_FREEZE,
    HAL_ADTMR_CMP_MODE_ACTIVE         = LL_ADTMR_CMP_MODE_ACTIVE,
    HAL_ADTMR_CMP_MODE_INACTIVE       = LL_ADTMR_CMP_MODE_INACTIVE,
    HAL_ADTMR_CMP_MODE_TOGGLE         = LL_ADTMR_CMP_MODE_TOGGLE,
    HAL_ADTMR_CMP_MODE_FORCE_INACTIVE = LL_ADTMR_CMP_MODE_FORCE_INACTIVE,
    HAL_ADTMR_CMP_MODE_FORCE_ACTIVE   = LL_ADTMR_CMP_MODE_FORCE_ACTIVE,
    HAL_ADTMR_CMP_MODE_PWM1           = LL_ADTMR_CMP_MODE_PWM1,
    HAL_ADTMR_CMP_MODE_PWM2           = LL_ADTMR_CMP_MODE_PWM2,
    HAL_ADTMR_CMP_MODE_RETRIG_OPM1    = LL_ADTMR_CMP_MODE_RETRIG_OPM1,
    HAL_ADTMR_CMP_MODE_RETRIG_OPM2    = LL_ADTMR_CMP_MODE_RETRIG_OPM2,
    HAL_ADTMR_CMP_MODE_COMB_PWM1      = LL_ADTMR_CMP_MODE_COMB_PWM1,
    HAL_ADTMR_CMP_MODE_COMB_PWM2      = LL_ADTMR_CMP_MODE_COMB_PWM2,
    HAL_ADTMR_CMP_MODE_ASYM_PWM1      = LL_ADTMR_CMP_MODE_ASYM_PWM1,
    HAL_ADTMR_CMP_MODE_ASYM_PWM2      = LL_ADTMR_CMP_MODE_ASYM_PWM2,
} HAL_ADTMR_OCModeTypeDef;

/**
  * @brief HAL ADTMR ETR Filter
  */
typedef enum 
{
    HAL_ADTMR_ETR_FILTER_NONE     = LL_ADTMR_ETR_FILTER_NONE,
    HAL_ADTMR_ETR_FILTER_TDS_X1   = LL_ADTMR_ETR_FILTER_TDS_X1,
    HAL_ADTMR_ETR_FILTER_TDS_X2   = LL_ADTMR_ETR_FILTER_TDS_X2,
    HAL_ADTMR_ETR_FILTER_TDS_X3   = LL_ADTMR_ETR_FILTER_TDS_X3,
    HAL_ADTMR_ETR_FILTER_TDS_X4   = LL_ADTMR_ETR_FILTER_TDS_X4,
    HAL_ADTMR_ETR_FILTER_TDS_X5   = LL_ADTMR_ETR_FILTER_TDS_X5,
    HAL_ADTMR_ETR_FILTER_TDS_X6   = LL_ADTMR_ETR_FILTER_TDS_X6,
    HAL_ADTMR_ETR_FILTER_TDS_X7   = LL_ADTMR_ETR_FILTER_TDS_X7,
    HAL_ADTMR_ETR_FILTER_TDS_X8   = LL_ADTMR_ETR_FILTER_TDS_X8,
    HAL_ADTMR_ETR_FILTER_TDS_X9   = LL_ADTMR_ETR_FILTER_TDS_X9,
    HAL_ADTMR_ETR_FILTER_TDS_X10  = LL_ADTMR_ETR_FILTER_TDS_X10,
    HAL_ADTMR_ETR_FILTER_TDS_X11  = LL_ADTMR_ETR_FILTER_TDS_X11,
    HAL_ADTMR_ETR_FILTER_TDS_X12  = LL_ADTMR_ETR_FILTER_TDS_X12,
    HAL_ADTMR_ETR_FILTER_TDS_X13  = LL_ADTMR_ETR_FILTER_TDS_X13,
    HAL_ADTMR_ETR_FILTER_TDS_X14  = LL_ADTMR_ETR_FILTER_TDS_X14,
    HAL_ADTMR_ETR_FILTER_TDS_X15  = LL_ADTMR_ETR_FILTER_TDS_X15,
} HAL_ADTMR_ETRFilTypeDef;

/**
  * @brief HAL ADTMR ETR Mode Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_ETR_MODE_EXT_CLK_1 = LL_ADTMR_ETR_MODE_EXT_CLK_1,
    HAL_ADTMR_ETR_MODE_EXT_CLK_2 = LL_ADTMR_ETR_MODE_EXT_CLK_2,
} HAL_ADTMR_ETRModeTypeDef;

/**
  * @brief HAL ADTMR ETR Edge Mode Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_ETR_EDGE_MODE_CLOSE           = LL_ADTMR_ETR_EDGE_MODE_CLOSE,
    HAL_ADTMR_ETR_EDGE_MODE_RISING          = LL_ADTMR_ETR_EDGE_MODE_RISING,
    HAL_ADTMR_ETR_EDGE_MODE_FALLING         = LL_ADTMR_ETR_EDGE_MODE_FALLING,
    HAL_ADTMR_ETR_EDGE_MODE_RISING_FALLING  = LL_ADTMR_ETR_EDGE_MODE_RISING_FALLING,
} HAL_ADTMR_ETREdgeTypeDef;

/**
  * @brief HAL ADTMR ETR Input Source Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_ETR_INPUT_SRC_ETR0  = LL_ADTMR_ETR_INPUT_SRC_ETR0,
    HAL_ADTMR_ETR_INPUT_SRC_ETR1  = LL_ADTMR_ETR_INPUT_SRC_ETR1,
    HAL_ADTMR_ETR_INPUT_SRC_ETR2  = LL_ADTMR_ETR_INPUT_SRC_ETR2,
    HAL_ADTMR_ETR_INPUT_SRC_ETR3  = LL_ADTMR_ETR_INPUT_SRC_ETR3,
    HAL_ADTMR_ETR_INPUT_SRC_ETR4  = LL_ADTMR_ETR_INPUT_SRC_ETR4,
    HAL_ADTMR_ETR_INPUT_SRC_ETR5  = LL_ADTMR_ETR_INPUT_SRC_ETR5,
    HAL_ADTMR_ETR_INPUT_SRC_ETR6  = LL_ADTMR_ETR_INPUT_SRC_ETR6,
    HAL_ADTMR_ETR_INPUT_SRC_ETR7  = LL_ADTMR_ETR_INPUT_SRC_ETR7,
    HAL_ADTMR_ETR_INPUT_SRC_ETR8  = LL_ADTMR_ETR_INPUT_SRC_ETR8,
    HAL_ADTMR_ETR_INPUT_SRC_ETR9  = LL_ADTMR_ETR_INPUT_SRC_ETR9,
    HAL_ADTMR_ETR_INPUT_SRC_ETR10 = LL_ADTMR_ETR_INPUT_SRC_ETR10,
    HAL_ADTMR_ETR_INPUT_SRC_ETR11 = LL_ADTMR_ETR_INPUT_SRC_ETR11,
    HAL_ADTMR_ETR_INPUT_SRC_ETR12 = LL_ADTMR_ETR_INPUT_SRC_ETR12,
    HAL_ADTMR_ETR_INPUT_SRC_ETR13 = LL_ADTMR_ETR_INPUT_SRC_ETR13,
    HAL_ADTMR_ETR_INPUT_SRC_ETR14 = LL_ADTMR_ETR_INPUT_SRC_ETR14,
    HAL_ADTMR_ETR_INPUT_SRC_ETR15 = LL_ADTMR_ETR_INPUT_SRC_ETR15,
} HAL_ADTMR_ETRInputSrcTypeDef;

/**
  * @brief HAL TI0 Input Source Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_TI0_IN_SRC_CH0          = LL_ADTMR_TI0_IN_SRC_CH0, 
    HAL_ADTMR_TI0_IN_SRC_CH0_1_2_XOR  = LL_ADTMR_TI0_IN_SRC_CH0_1_2_XOR
} HAL_ADTMR_TI0InSrcTypeDef;

/**
  * @brief HAL ADTMR Slave Mode Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_SLV_MODE_DIS        = LL_ADTMR_SLV_MODE_DIS,
    HAL_ADTMR_SLV_MODE_RST        = LL_ADTMR_SLV_MODE_RST,
    HAL_ADTMR_SLV_MODE_GATING     = LL_ADTMR_SLV_MODE_GATING,
    HAL_ADTMR_SLV_MODE_TRIG       = LL_ADTMR_SLV_MODE_TRIG,
    HAL_ADTMR_SLV_MODE_EXTCLK     = LL_ADTMR_SLV_MODE_EXTCLK,
    HAL_ADTMR_SLV_MODE_RST_TRIG   = LL_ADTMR_SLV_MODE_RST_TRIG,
    HAL_ADTMR_SLV_MODE_RST_GATING = LL_ADTMR_SLV_MODE_RST_GATING,
} HAL_ADTMR_SlvModeTypeDef;

/**
  * @brief HAL ADTMR Break Polarity Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_BRK_POL_HIGH  = LL_ADTMR_BRK_POL_HIGH,
    HAL_ADTMR_BRK_POL_LOW   = LL_ADTMR_BRK_POL_LOW,
} HAL_ADTMR_BrkPolTypeDef;

/**
  * @brief HAL ADTMR Break Input Polarity Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_BRK_IN_VALID_POL_HIGH  = LL_ADTMR_BRK_IN_POL_VALID_HIGH,
    HAL_ADTMR_BRK_IN_VALID_POL_LOW   = LL_ADTMR_BRK_IN_POL_VALID_LOW,
} HAL_ADTMR_BrkInputPolTypeDef;

/**
  * @brief HAL ADTMR Break Input Signal Enumeration 
  */
typedef enum
{
    HAL_ADTMR_BRK_IN_SRC_CMP0_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP0_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP1_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP1_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP2_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP2_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP3_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP3_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP4_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP4_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP5_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP5_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP6_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP6_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP7_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP7_OUT,
    HAL_ADTMR_BRK_IN_SRC_CMP8_OUT     = LL_ADTMR_BRK_IN_SRC_MASK_CMP8_OUT,
    HAL_ADTMR_BRK_IN_SRC_TMRx_BKy     = LL_ADTMR_BRK_IN_SRC_MASK_TMRx_BKy,
    HAL_ADTMR_BRK_IN_SRC_ADC0_AWD0    = LL_ADTMR_BRK_IN_SRC_MASK_ADC0_AWD0,
    HAL_ADTMR_BRK_IN_SRC_ADC1_AWD0    = LL_ADTMR_BRK_IN_SRC_MASK_ADC1_AWD0,
    HAL_ADTMR_BRK_IN_SRC_PDM0_CMPH    = LL_ADTMR_BRK_IN_SRC_MASK_PDM0_CMPH,
    HAL_ADTMR_BRK_IN_SRC_PDM1_CMPH    = LL_ADTMR_BRK_IN_SRC_MASK_PDM1_CMPH,
    HAL_ADTMR_BRK_IN_SRC_PDM2_CMPH    = LL_ADTMR_BRK_IN_SRC_MASK_PDM2_CMPH,
    HAL_ADTMR_BRK_IN_SRC_PDM3_CMPH    = LL_ADTMR_BRK_IN_SRC_MASK_PDM3_CMPH
} HAL_ADTMR_BrkInputTypeDef;

/**
  * @brief HAL ADTMR Idle Off-State Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_IDLE_OFF_STA_COMP_CLOSE = LL_ADTMR_IDLE_OFF_STA_COMP_CLOSE,
    HAL_ADTMR_IDLE_OFF_STA_COMP_IDLE   = LL_ADTMR_IDLE_OFF_STA_COMP_IDLE,
} HAL_ADTMR_IdleOffStaTypeDef;

/**
  * @brief HAL ADTMR Run Off-State Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_RUN_OFF_STA_COMP_CLOSE = LL_ADTMR_RUN_OFF_STA_COMP_CLOSE,
    HAL_ADTMR_RUN_OFF_STA_COMP_IVD   = LL_ADTMR_RUN_OFF_STA_COMP_IVD,
} HAL_ADTMR_RunOffStaTypeDef;


/**
  * @brief HAL ADTMR Trigger Input Signal Enumeration 
  */
typedef enum 
{
    HAL_ADTMR_TRIG_ITR0  = LL_ADTMR_TRIG_ITR0,
    HAL_ADTMR_TRIG_ITR1  = LL_ADTMR_TRIG_ITR1,
    HAL_ADTMR_TRIG_ITR2  = LL_ADTMR_TRIG_ITR2,
    HAL_ADTMR_TRIG_ITR3  = LL_ADTMR_TRIG_ITR3,
    HAL_ADTMR_TRIG_ITR4  = LL_ADTMR_TRIG_ITR4,
    HAL_ADTMR_TRIG_ITR5  = LL_ADTMR_TRIG_ITR5,
    HAL_ADTMR_TRIG_ITR6  = LL_ADTMR_TRIG_ITR6,
    HAL_ADTMR_TRIG_ITR7  = LL_ADTMR_TRIG_ITR7,
    HAL_ADTMR_TRIG_ITR8  = LL_ADTMR_TRIG_ITR8,
    HAL_ADTMR_TRIG_ITR9  = LL_ADTMR_TRIG_ITR9,
    HAL_ADTMR_TRIG_ITR10 = LL_ADTMR_TRIG_ITR10,
    HAL_ADTMR_TRIG_ITR11 = LL_ADTMR_TRIG_ITR11,
    HAL_ADTMR_TRIG_ITR12 = LL_ADTMR_TRIG_ITR12,
    HAL_ADTMR_TRIG_ITR13 = LL_ADTMR_TRIG_ITR13,
    HAL_ADTMR_TRIG_ITR14 = LL_ADTMR_TRIG_ITR14,
    HAL_ADTMR_TRIG_ITR15 = LL_ADTMR_TRIG_ITR15,
    HAL_ADTMR_TRIG_CH0_FE = LL_ADTMR_TRIG_CH0_FE,
    HAL_ADTMR_TRIG_CH0_F = LL_ADTMR_TRIG_CH0_F,
    HAL_ADTMR_TRIG_CH1_F = LL_ADTMR_TRIG_CH1_F,
    HAL_ADTMR_TRIG_CH2_F = LL_ADTMR_TRIG_CH2_F,
    HAL_ADTMR_TRIG_CH3_F = LL_ADTMR_TRIG_CH3_F,
    HAL_ADTMR_TRIG_ETR_FE = LL_ADTMR_TRIG_ETR_FE,
    HAL_ADTMR_TRIG_ETR_F = LL_ADTMR_TRIG_ETR_F,
} HAL_ADTMR_TrigTypeDef;

/**
  * @brief HAL ADTMR Event Source Enumeration 
  */
typedef enum
{
    HAL_ADTMR_EVENTSOURCE_UPDATE  =   LL_ADTMR_EVT_GEN_UPDATE,
    HAL_ADTMR_EVENTSOURCE_TRIG    =   LL_ADTMR_EVT_GEN_TRIGGER,
    HAL_ADTMR_EVENTSOURCE_BRK0    =   LL_ADTMR_EVT_GEN_BREAK0,
    HAL_ADTMR_EVENTSOURCE_BRK1    =   LL_ADTMR_EVT_GEN_BREAK1,
    HAL_ADTMR_EVENTSOURCE_CC0     =   LL_ADTMR_EVT_GEN_CAP_CMP_0,
    HAL_ADTMR_EVENTSOURCE_CC1     =   LL_ADTMR_EVT_GEN_CAP_CMP_1,
    HAL_ADTMR_EVENTSOURCE_CC2     =   LL_ADTMR_EVT_GEN_CAP_CMP_2,
    HAL_ADTMR_EVENTSOURCE_CC3     =   LL_ADTMR_EVT_GEN_CAP_CMP_3,
} HAL_ADTMR_EvtSrcTypeDef;


/**
  * @brief  ADTMR Base Initialization Structure Definition
  */
typedef struct
{
    /* Base Config */
    HAL_ADTMR_EnableTypeDef         AutoReloadPreload;      /*!< Auto Preload Enable                        */
    HAL_ADTMR_WorkModeTypeDef       WorkMode;               /*!< Work Mode: Continue/Single                 */
    uint16_t                        Period;                 /*!< Period Value                               */
    uint16_t                        Prescaler;              /*!< Clock Prescaler                            */

    /* Event Config */
    HAL_ADTMR_UpdateEvtDisTypeDef   UpdateEvent;            /*!< Update Event Enable                        */
    HAL_ADTMR_UpdateEvtSrcTypeDef   UpdateSource;           /*!< Update Event Source                        */

    /* Advance Config */
    uint8_t                         RepetitionCounter;      /*!< Repeat Counter                             */
    HAL_ADTMR_CounterModeTypeDef    CounterMode;            /*!< Counter Mode                               */
    HAL_ADTMR_DzDigFilClkDivTypeDef DzFilterClockDivision;  /*!< Dead Zone Digital Filter Clock Division    */
    
} HAL_ADTMR_BaseInitTypeDef;

/**
  * @brief  ADTMR Master Initialization Structure Definition
  */
typedef struct
{
    HAL_ADTMR_MstModeTypeDef        MasterMode;         /*!< Master Mode (TRGO source)          */
    uint8_t                         TRGCCWidth;         /*!< TRGCC Output Width                 */
    uint8_t                         TRGOWidth;          /*!< TRGO Output Width                  */
    HAL_ADTMR_TrigOutChMskTypeDef   TRGOSelection;      /*!< Trigger Output Channel Selection   */
} HAL_ADTMR_MstInitTypeDef;

/**
  * @brief  ADTMR Input Capture Initialization Structure Definition
  */
typedef struct
{
    HAL_ADTMR_CapFilTypeDef         ICFilter;           /*!< Input Capture Filter               */
    HAL_ADTMR_CapPolTypeDef         ICPolarity;         /*!< Input Capture Polarity             */
    HAL_ADTMR_CapInputMapTypeDef    ICSelection;        /*!< Input Capture Map                  */
    HAL_ADTMR_CapPrescalerTypeDef   ICPrescaler;        /*!< Input Capture Prescaler            */
    HAL_ADTMR_CapInputSrcTypeDef    ICTriggerSource;    /*!< Input Capture Trigger Input Source */
} HAL_ADTMR_InputCapInitTypeDef;

/**
  * @brief  ADTMR Output Compare Initialization Structure Definition
  */
typedef struct
{
    HAL_ADTMR_EnableTypeDef         CompareAutoReload;  /*!< Output Compare Auto Preload Enable */
    uint16_t                        CompareValue;       /*!< Output Compare Match Value         */
    HAL_ADTMR_OCModeTypeDef         OCMode;             /*!< Output Compare Mode                */
    HAL_ADTMR_CmpPolTypeDef         OCPolarity;         /*!< OC Polarity                        */
    HAL_ADTMR_CmpPolTypeDef         OCNPolarity;        /*!< OCN Polarity                       */
    HAL_ADTMR_IdleStaTypeDef        OCIdleState;        /*!< OC idle state                      */
    HAL_ADTMR_IdleStaTypeDef        OCNIdleState;       /*!< OCN idle state                     */
} HAL_ADTMR_OutputCmpInitTypeDef;

/**
  * @brief  ADTMR Slave / ETR Initialization Structure Definition
  */
typedef struct
{
    HAL_ADTMR_SlvModeTypeDef        SlaveMode;          /*!< Slave Mode                         */
    HAL_ADTMR_TrigTypeDef           InputTrigger;       /*!< Trigger Selection                  */
    HAL_ADTMR_ETRInputSrcTypeDef    InputSource;        /*!< ETR Input Source                   */
    HAL_ADTMR_ETREdgeTypeDef        TriggerPolarity;    /*!< ETR Edge Mode                      */
    HAL_ADTMR_ETRFilTypeDef         TriggerFilter;      /*!< ETR Filter                         */
    HAL_ADTMR_ETRModeTypeDef        ExtClokMode;        /*!< ETR Mode                           */
    HAL_ADTMR_EnableTypeDef         FastSync;           /*!< Mst/Slv Fast Sync Enable           */
} HAL_ADTMR_SlvInitTypeDef;

/**
  * @brief  ADTMR Break and Dead-Time Initialization Structure Definition
  */
typedef struct
{
    /* Break input 0 */
    HAL_ADTMR_EnableTypeDef         Break0State;        /*!< Break 0 enable                     */
    HAL_ADTMR_BrkPolTypeDef         Break0Polarity;     /*!< Break 0 polarity                   */
    uint8_t                         Break0Filter;       /*!< Break 0 filter                     */

    /* Break input 1 */
    HAL_ADTMR_EnableTypeDef         Break1State;        /*!< Break 1 enable                     */
    HAL_ADTMR_BrkPolTypeDef         Break1Polarity;     /*!< Break 1 polarity                   */
    uint8_t                         Break1Filter;       /*!< Break 1 filter                     */

    /* Break interrupt */
    HAL_ADTMR_EnableTypeDef         BreakIT;            /*!< Break interrupt enable             */

    /* Dead-Time Config */
    uint8_t                         DeadTime;           /*!< Dead-time generator value          */

    /* Output Control */
    HAL_ADTMR_EnableTypeDef         AutomaticOutput;    /*!< Automatic output enable            */
    HAL_ADTMR_RunOffStaTypeDef      OffStateRunMode;    /*!< Off-state in run mode              */
    HAL_ADTMR_IdleOffStaTypeDef     OffStateIdleMode;   /*!< Off-state in idle mode             */
} HAL_ADTMR_BreakDeadTimeConfigTypeDef;

/**
  * @brief  TIM Break/Break2 input configuration
  */
typedef struct
{
    HAL_ADTMR_BrkInputTypeDef       Source;   /*!< Specifies the source of the timer break input.             */
    HAL_ADTMR_EnableTypeDef         Enable;   /*!< Specifies whether or not the break input source is enabled.*/
    HAL_ADTMR_BrkInputPolTypeDef    Polarity; /*!< Specifies the break input source polarity.                 */
} HAL_ADTMR_BreakInputConfigTypeDef;


/**
  * @brief HAL ADTMR handle structure type
  */
typedef struct HAL_ADTMR_HandleStructDef HAL_ADTMR_HandleTypeDef;

/**
  * @brief ADTMR IRQ callback function type definition
  */
typedef void (*HAL_ADTMR_IRQCallback)(HAL_ADTMR_HandleTypeDef *Handle);

/**
  * @brief  ADTMR Handle Structure definition
  */
struct HAL_ADTMR_HandleStructDef
{
    ADTMR_TypeDef                           *Instance;        /*!< Register base address      */
    volatile HAL_ADTMR_StateTypeDef         State;            /*!< ADTMR operation state      */
    volatile HAL_ADTMR_ErrCodeMskTypeDef    LastErrorCodes;   /*!< Last error codes           */
    const void                              *pUserData;       /*!< User data pointer          */
};
/**
  * @}
  */ /* ADTMR_HAL_Exported_Types */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADTMR_HAL_Exported_Functions ADTMR HAL Exported Functions
  * @{
  */

/** @defgroup ADTMR_HAL_EF_Initialization ADTMR HAL Initialization
  * @{
  */

HAL_StatusTypeDef HAL_ADTMR_Base_Init(HAL_ADTMR_HandleTypeDef *Handle, 
                                      ADTMR_TypeDef *ADTMRx,
                                      const HAL_ADTMR_BaseInitTypeDef *pInit);
                              
HAL_StatusTypeDef HAL_ADTMR_Base_DeInit(HAL_ADTMR_HandleTypeDef *Handle);

void HAL_ADTMR_Base_MspInit(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_Base_MspDeInit(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_IoInit(ADTMR_TypeDef *ADTMRx);
void HAL_ADTMR_IoDeInit(ADTMR_TypeDef *ADTMRx);
/**
  * @}
  */

/** @defgroup ADTMR_HAL_EF_Configuration ADTMR HAL Configuration
  * @{
  */

HAL_StatusTypeDef HAL_ADTMR_IC_Init(HAL_ADTMR_HandleTypeDef *Handle, 
                                    HAL_ADTMR_ChannelIdxTypeDef Channel,
                                    const HAL_ADTMR_InputCapInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADTMR_OC_Init(HAL_ADTMR_HandleTypeDef *Handle, 
                                    HAL_ADTMR_ChannelIdxTypeDef Channel,
                                    const HAL_ADTMR_OutputCmpInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADTMR_InitMaster(HAL_ADTMR_HandleTypeDef *Handle,
                                       const HAL_ADTMR_MstInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADTMR_InitSlave(HAL_ADTMR_HandleTypeDef *Handle,
                                      const HAL_ADTMR_SlvInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADTMR_ConfigBreakDeadTime(HAL_ADTMR_HandleTypeDef *Handle,
                                      const HAL_ADTMR_BreakDeadTimeConfigTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADTMR_ConfigBreakInput(HAL_ADTMR_HandleTypeDef *Handle,
                                             HAL_ADTMR_BreakInputTypeDef BreakInput,
                                             const HAL_ADTMR_BreakInputConfigTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADTMR_ConfigTI0InputSource(HAL_ADTMR_HandleTypeDef *Handle, 
                                                 HAL_ADTMR_TI0InSrcTypeDef Source);
/**
  * @}
  */

/** @defgroup ADTMR_HAL_EF_IO_Operation ADTMR HAL IO Operation
  * @{
  */
HAL_StatusTypeDef HAL_ADTMR_Base_Start(HAL_ADTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADTMR_Base_Stop(HAL_ADTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADTMR_Base_Start_IT(HAL_ADTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADTMR_Base_Stop_IT(HAL_ADTMR_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_ADTMR_OC_Start(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_OC_Stop(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_OC_StartIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_OC_StopIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_ADTMR_OCN_Start(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_OCN_Stop(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_OCN_StartIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_OCN_StopIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_ADTMR_IC_Start(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_IC_Stop(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_IC_StartIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_ADTMR_IC_StopIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_ADTMR_GenerateEvent(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_EvtSrcTypeDef EventSource);


uint16_t HAL_ADTMR_ReadCounter(const HAL_ADTMR_HandleTypeDef *Handle);
uint16_t HAL_ADTMR_ReadCapturedValue(const HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
/**
  * @}
  */

/** @defgroup ADTMR_HAL_EF_IRQ_Handler ADTMR HAL IRQ Handler and Callbacks
  * @{
  */

HAL_StatusTypeDef HAL_ADTMR_InterruptRequestEnable(HAL_ADTMR_HandleTypeDef *Handle, 
                                                   HAL_ADTMR_ITEnMskTypeDef ITMask);

HAL_StatusTypeDef HAL_ADTMR_InterruptRequestDisable(HAL_ADTMR_HandleTypeDef *Handle, 
                                                    HAL_ADTMR_ITEnMskTypeDef ITMask);

void HAL_ADTMR_BRK_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_UPD_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_TRG_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_CC_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_CCx_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);

void HAL_ADTMR_OverflowCallback(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_PeriodElapsedCallback(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_TriggerCallback(HAL_ADTMR_HandleTypeDef *Handle);
void HAL_ADTMR_BreakCallback(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ITPendingMskTypeDef BreakEvent);
void HAL_ADTMR_OC_DelayElapsedCallback(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
void HAL_ADTMR_IC_CaptureCallback(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
void HAL_ADTMR_IC_OverCaptureCallback(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel);
/**
  * @}
  */

/**
  * @}
  */ /* ADTMR_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

#endif /* HAL_ADTMR_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* ADTMR */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_ADTMR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
