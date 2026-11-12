/**
  ******************************************************************************
  * @file    tae32g58xx_hal_gptmrx.h
  * @author  Tai-Action SD Team
  * @brief   Header file for GPTMRX HAL module.
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
#ifndef _TAE32G58XX_HAL_GPTMRX_H_
#define _TAE32G58XX_HAL_GPTMRX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_gptmrx.h"

#if defined(TMR0) || defined(TMR1) || defined(TMR2)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_GPTMRX_MODULE_ENABLED) && (HAL_GPTMRX_MODULE_ENABLED == 1)


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPTMRX_HAL_Exported_Macros GPTMRX HAL Exported Macros
  * @{
  */

/** @defgroup GPTMRX_HAL_EM_Assert GPTMRX HAL Assert 
  * @brief    GPTMRX HAL Assert
  * @{
  */

#ifndef TAE32_USE_HAL_GPTMRX_CHECK_PARAM
#define TAE32_USE_HAL_GPTMRX_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_GPTMRX_CHECK_PARAM != 1) && (TAE32_USE_HAL_GPTMRX_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_GPTMRX_CHECK_PARAM
#define TAE32_USE_HAL_GPTMRX_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_GPTMRX_CHECK_PARAM */

#define HAL_GPTMRX_PARAM_CHECK(expression)     \
        if (TAE32_USE_HAL_GPTMRX_CHECK_PARAM) { \
            expression;                        \
        }
/**
  * @}
  */ /* GPTMRX_HAL_EM_Assert */


/**
 * @brief Updates a GPTMRX HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the GPTMRX process
 * state check feature is enabled (TAE32_USE_HAL_GPTMRX_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_GPTMRX_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_GPTMRX_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_GPTMRX_CHECK_PROCESS_STATE == 1)
#define HAL_GPTMRX_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_GPTMRX_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        do {                                                                      \
            if ((upd_parm) != (check_value)) {                                    \
                failed_expression;                                                \
                break;                                                            \
            } else {                                                              \
                (upd_parm) = (new_value);                                         \
            }                                                                     \
        } while(0)    
#endif



/** @defgroup GPTMRX_HAL_EM_Mask GPTMRX HAL Mask
  * @brief    GPTMRX HAL State / Error / Interrupt mask definitions
  * @{
  */

/** @name   HAL_GPTMRX_StateMaskTypeDef 
  * @brief  HAL GPTMRX global state mask definition. 
  * @{
  */
#define HAL_GPTMRX_StateMaskTypeDef                          uint32_t

#define HAL_GPTMRX_STATE_MASK_RESET                          (0U)         /*!< GPTMRX not yet initialized                     */
#define HAL_GPTMRX_STATE_MASK_CONFIGURABLE                   (1U << 30U)  /*!< GPTMRX is configurable                         */
#define HAL_GPTMRX_STATE_MASK_BUSY                           (1U << 29U)  /*!< An internal process is ongoing                */
#define HAL_GPTMRX_STATE_MASK_TIMEOUT                        (1U << 28U)  /*!< Timeout state                                 */
#define HAL_GPTMRX_STATE_MASK_ERROR                          (1U << 27U)  /*!< Error state                                   */
/** @} */

/** @name   HAL_GPTMRX_ErrCodeMskTypeDef
  * @brief  HAL GPTMRX Error Code Mask definition.
  * @{
  */
#define HAL_GPTMRX_ErrCodeMskTypeDef                         uint32_t

#define HAL_GPTMRX_ERROR_NONE                                (0U)         /*!< No error                     */
#define HAL_GPTMRX_ERROR_INVALID_INSTANCE                    (1U << 30U)  /*!< Invalid instance error       */
/** @} */

/** @name   HAL_GPTMRX_ITEnMskTypeDef
  * @brief  HAL GPTMRX Interrupt Enable Mask Definition
  * @{
  */
#define HAL_GPTMRX_ITEnMskTypeDef                            LL_GPTMRX_IER_ITEnMskTypeDef

#define HAL_GPTMRX_IER_BREAK_IT_EN                           LL_GPTMRX_IER_BIE     /*!< Break interrupt enable mask               */
#define HAL_GPTMRX_IER_TRIGGER_IT_EN                         LL_GPTMRX_IER_TIE     /*!< Trigger interrupt enable mask             */
#define HAL_GPTMRX_IER_OVERFLOW_IT_EN                        LL_GPTMRX_IER_OVIE    /*!< Overflow interrupt enable mask            */
#define HAL_GPTMRX_IER_UPDATE_IT_EN                          LL_GPTMRX_IER_UIE     /*!< Update interrupt enable mask              */
#define HAL_GPTMRX_IER_CH1_CAPTURE_OR_COMPARE_IT_EN          LL_GPTMRX_IER_C1MIE   /*!< CH1 Capture/Compare interrupt enable mask */
#define HAL_GPTMRX_IER_CH1_OVER_CAPTURE_IT_EN                LL_GPTMRX_IER_C1OIE   /*!< CH1 OverCapture interrupt enable mask     */
#define HAL_GPTMRX_IER_CH0_CAPTURE_OR_COMPARE_IT_EN          LL_GPTMRX_IER_C0MIE   /*!< CH0 Capture/Compare interrupt enable mask */
#define HAL_GPTMRX_IER_CH0_OVER_CAPTURE_IT_EN                LL_GPTMRX_IER_C0OIE   /*!< CH0 OverCapture interrupt enable mask     */
/** @} */

/** @name   HAL_GPTMRX_ITPendingMskTypeDef
  * @brief  HAL GPTMRX Interrupt Flag Mask Definition
  * @{
  */
#define HAL_GPTMRX_ITPendingMskTypeDef                       LL_GPTMRX_SR_ITPendingMskTypeDef

#define HAL_GPTMRX_SR_SYSFAULT_BREAK_IT_FLAG                 LL_GPTMRX_SR_SBIF     /*!< System fault break interrupt flag mask    */
#define HAL_GPTMRX_SR_BREAK0_IT_FLAG                         LL_GPTMRX_SR_B0IF     /*!< Break input 0 interrupt flag mask         */
#define HAL_GPTMRX_SR_TRIGGER_IT_FLAG                        LL_GPTMRX_SR_TIF      /*!< Trigger interrupt flag mask               */
#define HAL_GPTMRX_SR_OVERFLOW_IT_FLAG                       LL_GPTMRX_SR_OVIF     /*!< Overflow interrupt flag mask              */
#define HAL_GPTMRX_SR_UPDATE_IT_FLAG                         LL_GPTMRX_SR_UIF      /*!< Update interrupt flag mask                */
#define HAL_GPTMRX_SR_CH1_CAPTURE_OR_COMPARE_IT_FLAG         LL_GPTMRX_SR_CC1MIF   /*!< CH1 Capture/Compare interrupt flag mask   */
#define HAL_GPTMRX_SR_CH1_OVER_CAPTURE_IT_FLAG               LL_GPTMRX_SR_CC1OIF   /*!< CH1 OverCapture interrupt flag mask       */
#define HAL_GPTMRX_SR_CH0_CAPTURE_OR_COMPARE_IT_FLAG         LL_GPTMRX_SR_CC0MIF   /*!< CH0 Capture/Compare interrupt flag mask   */
#define HAL_GPTMRX_SR_CH0_OVER_CAPTURE_IT_FLAG               LL_GPTMRX_SR_CC0OIF   /*!< CH0 OverCapture interrupt flag mask       */
/** @} */


/** @name   HAL_GPTMRX_TrigOutChMskTypeDef
  * @brief  HAL GPTMRX TRGO Channel Mask Definition
  * @{
  */
#define HAL_GPTMRX_TrigOutChMskTypeDef                       LL_GPTMRX_TTCR_TrigOutChMskTypeDef

#define HAL_GPTMRX_TRGI_OUT_SELECT_CH1_MASK                  LL_GPTMRX_TTCR_TRGI_OUT_SELECT_CH1
#define HAL_GPTMRX_TRGI_OUT_SELECT_CH0_MASK                  LL_GPTMRX_TTCR_TRGI_OUT_SELECT_CH0
/** @} */

/**
  * @}
  */ /* GPTMRX_HAL_EM_Mask */

/**
  * @}
  */ /* GPTMRX_HAL_Exported_Macros */

/* Exported types ------------------------------------------------------------*/


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @addtogroup GPTMRX_HAL
  * @brief    GPTMRX HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup GPTMRX_HAL_Exported_Types GPTMRX HAL Exported Types
  * @brief    GPTMRX HAL Exported Types
  * @{
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
/**
  * @brief  HAL GPTMRX State definition
  */
typedef enum
{
    HAL_GPTMRX_STATE_RESET           = HAL_GPTMRX_STATE_MASK_RESET,         /*!< GPTMRX not yet initialized           */
    HAL_GPTMRX_STATE_CONFIGURABLE    = HAL_GPTMRX_STATE_MASK_CONFIGURABLE,  /*!< GPTMRX is configurable  */
    HAL_GPTMRX_STATE_BUSY            = HAL_GPTMRX_STATE_MASK_BUSY,          /*!< An internal process is ongoing      */
    HAL_GPTMRX_STATE_TIMEOUT         = HAL_GPTMRX_STATE_MASK_TIMEOUT,       /*!< Timeout state                       */
    HAL_GPTMRX_STATE_ERROR           = HAL_GPTMRX_STATE_MASK_ERROR          /*!< Error state                         */
} HAL_GPTMRX_StateTypeDef;

_Static_assert(sizeof(HAL_GPTMRX_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else /* TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

typedef HAL_GPTMRX_StateMaskTypeDef      HAL_GPTMRX_StateTypeDef;
#define HAL_GPTMRX_STATE_RESET           HAL_GPTMRX_STATE_MASK_RESET
#define HAL_GPTMRX_STATE_CONFIGURABLE    HAL_GPTMRX_STATE_MASK_CONFIGURABLE
#define HAL_GPTMRX_STATE_BUSY            HAL_GPTMRX_STATE_MASK_BUSY
#define HAL_GPTMRX_STATE_TIMEOUT         HAL_GPTMRX_STATE_MASK_TIMEOUT
#define HAL_GPTMRX_STATE_ERROR           HAL_GPTMRX_STATE_MASK_ERROR
#endif /* !TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

/**
 * @brief 
 */
typedef enum
{
    HAL_GPTMRX_FUNC_DISABLE  = 0U,    /*!< GPTMRX Function Disable  */
    HAL_GPTMRX_FUNC_ENABLE   = 1U     /*!< GPTMRX Function Enable   */
} HAL_GPTMRX_EnableTypeDef;

/**
 * @brief HAL GPTMRX Channel Index Enumeration 
 */
typedef enum
{
    HAL_GPTMRX_BREAK_INPUT_BK0 = 0U, /*!< GPTMRX Break input BK0  */
} HAL_GPTMRX_BreakInputTypeDef;

/**
  * @brief HAL GPTMRX Channel Index Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_CHANNEL_0     = LL_GPTMRX_CAP_CMP_CH_0,
    HAL_GPTMRX_CHANNEL_1     = LL_GPTMRX_CAP_CMP_CH_1,
    HAL_GPTMRX_CHANNEL_NUMS  = LL_GPTMRX_CAP_CMP_CH_NUMS
} HAL_GPTMRX_ChannelIdxTypeDef;

/**
  * @brief HAL GPTMRX Work Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_WORK_MODE_CONTINUE  = LL_GPTMRX_WORK_MODE_CONTINUE,
    HAL_GPTMRX_WORK_MODE_SINGLE    = LL_GPTMRX_WORK_MODE_SINGLE,
} HAL_GPTMRX_WorkModeTypeDef;

/**
  * @brief HAL GPTMRX Update Event Disable Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_UPDATE_EVT_RELEASE  = 0UL,
    HAL_GPTMRX_UPDATE_EVT_ASSERT   = 1UL,
} HAL_GPTMRX_UpdateEvtDisTypeDef;

/**
  * @brief HAL GPTMRX Update Event Source Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_UPDATE_EVT_SRC_OV_UG  = LL_GPTMRX_UPDATE_EVT_SRC_OV_UG,
    HAL_GPTMRX_UPDATE_EVT_SRC_OV     = LL_GPTMRX_UPDATE_EVT_SRC_OV,
} HAL_GPTMRX_UpdateEvtSrcTypeDef;

/**
  * @brief Timer Output Idle State Definition
  */
typedef enum 
{
    HAL_GPTMRX_OUTPUT_IDLE_STA_LOW   = LL_GPTMRX_OUTPUT_IDLE_STA_LOW, 
    HAL_GPTMRX_OUTPUT_IDLE_STA_HIGH  = LL_GPTMRX_OUTPUT_IDLE_STA_HIGH, 
} HAL_GPTMRX_IdleStaTypeDef;

/**
  * @brief HAL GPTMRX Master Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_MST_MODE_RESET        = LL_GPTMRX_MST_MODE_RESET,
    HAL_GPTMRX_MST_MODE_ENABLE       = LL_GPTMRX_MST_MODE_ENABLE,
    HAL_GPTMRX_MST_MODE_UPDATE       = LL_GPTMRX_MST_MODE_UPDATE,
    HAL_GPTMRX_MST_MODE_CAP_CMP_EVT  = LL_GPTMRX_MST_MODE_CAP_CMP_EVT,
    HAL_GPTMRX_MST_MODE_CMP_OUT0     = LL_GPTMRX_MST_MODE_OC0REF,
    HAL_GPTMRX_MST_MODE_CMP_OUT1     = LL_GPTMRX_MST_MODE_OC1REF,
} HAL_GPTMRX_MstModeTypeDef;

/**
  * @brief HAL GPTMRX Clock Division Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_1 = LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_1,
    HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_2 = LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_2,
    HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_4 = LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_4,
    HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_8 = LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_8,
} HAL_GPTMRX_DzDigFilClkDivTypeDef;

/**
  * @brief HAL GPTMRX Capture Polarity Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_CAP_POL_CLOSE     = LL_GPTMRX_CAP_POL_CLOSE,
    HAL_GPTMRX_CAP_POL_RISING    = LL_GPTMRX_CAP_POL_RISING,
    HAL_GPTMRX_CAP_POL_FALLING   = LL_GPTMRX_CAP_POL_FALLING,
    HAL_GPTMRX_CAP_POL_BOTH_EDGE = LL_GPTMRX_CAP_POL_BOTH_EDGE,
} HAL_GPTMRX_CapPolTypeDef;

/**
  * @brief HAL GPTMRX Capture Filter
  */
typedef enum 
{
    HAL_GPTMRX_CAP_FILTER_NONE     = LL_GPTMRX_CAP_FILTER_NONE,
    HAL_GPTMRX_CAP_FILTER_TDS_X1   = LL_GPTMRX_CAP_FILTER_TDS_X1,
    HAL_GPTMRX_CAP_FILTER_TDS_X2   = LL_GPTMRX_CAP_FILTER_TDS_X2,
    HAL_GPTMRX_CAP_FILTER_TDS_X3   = LL_GPTMRX_CAP_FILTER_TDS_X3,
    HAL_GPTMRX_CAP_FILTER_TDS_X4   = LL_GPTMRX_CAP_FILTER_TDS_X4,
    HAL_GPTMRX_CAP_FILTER_TDS_X5   = LL_GPTMRX_CAP_FILTER_TDS_X5,
    HAL_GPTMRX_CAP_FILTER_TDS_X6   = LL_GPTMRX_CAP_FILTER_TDS_X6,
    HAL_GPTMRX_CAP_FILTER_TDS_X7   = LL_GPTMRX_CAP_FILTER_TDS_X7,
    HAL_GPTMRX_CAP_FILTER_TDS_X8   = LL_GPTMRX_CAP_FILTER_TDS_X8,
    HAL_GPTMRX_CAP_FILTER_TDS_X9   = LL_GPTMRX_CAP_FILTER_TDS_X9,
    HAL_GPTMRX_CAP_FILTER_TDS_X10  = LL_GPTMRX_CAP_FILTER_TDS_X10,
    HAL_GPTMRX_CAP_FILTER_TDS_X11  = LL_GPTMRX_CAP_FILTER_TDS_X11,
    HAL_GPTMRX_CAP_FILTER_TDS_X12  = LL_GPTMRX_CAP_FILTER_TDS_X12,
    HAL_GPTMRX_CAP_FILTER_TDS_X13  = LL_GPTMRX_CAP_FILTER_TDS_X13,
    HAL_GPTMRX_CAP_FILTER_TDS_X14  = LL_GPTMRX_CAP_FILTER_TDS_X14,
    HAL_GPTMRX_CAP_FILTER_TDS_X15  = LL_GPTMRX_CAP_FILTER_TDS_X15,
} HAL_GPTMRX_CapFilTypeDef;

/**
  * @brief HAL GPTMRX Capture Prescaler Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_CAP_PRESCALER_1 = LL_GPTMRX_CAP_PRESCALER_1,
    HAL_GPTMRX_CAP_PRESCALER_2 = LL_GPTMRX_CAP_PRESCALER_2,
    HAL_GPTMRX_CAP_PRESCALER_4 = LL_GPTMRX_CAP_PRESCALER_4,
    HAL_GPTMRX_CAP_PRESCALER_8 = LL_GPTMRX_CAP_PRESCALER_8,
} HAL_GPTMRX_CapPrescalerTypeDef;


/**
  * @brief HAL GPTMRX Capture Input Map Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_CAP_INPUT_MAP_0     = LL_GPTMRX_CAP_INPUT_MAP_0,
    HAL_GPTMRX_CAP_INPUT_MAP_1     = LL_GPTMRX_CAP_INPUT_MAP_1,
    HAL_GPTMRX_CAP_INPUT_MAP_TRGI  = LL_GPTMRX_CAP_INPUT_MAP_TRGI,
} HAL_GPTMRX_CapInputMapTypeDef;

/**
  * @brief HAL GPTMRX Capture Input Source Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_CAP_INPUT_SRC_IN0  = LL_GPTMRX_CAP_INPUT_SRC_IN0,
    HAL_GPTMRX_CAP_INPUT_SRC_IN1  = LL_GPTMRX_CAP_INPUT_SRC_IN1,
    HAL_GPTMRX_CAP_INPUT_SRC_IN2  = LL_GPTMRX_CAP_INPUT_SRC_IN2,
    HAL_GPTMRX_CAP_INPUT_SRC_IN3  = LL_GPTMRX_CAP_INPUT_SRC_IN3,
    HAL_GPTMRX_CAP_INPUT_SRC_IN4  = LL_GPTMRX_CAP_INPUT_SRC_IN4,
    HAL_GPTMRX_CAP_INPUT_SRC_IN5  = LL_GPTMRX_CAP_INPUT_SRC_IN5,
    HAL_GPTMRX_CAP_INPUT_SRC_IN6  = LL_GPTMRX_CAP_INPUT_SRC_IN6,
    HAL_GPTMRX_CAP_INPUT_SRC_IN7  = LL_GPTMRX_CAP_INPUT_SRC_IN7,
    HAL_GPTMRX_CAP_INPUT_SRC_IN8  = LL_GPTMRX_CAP_INPUT_SRC_IN8,
    HAL_GPTMRX_CAP_INPUT_SRC_IN9  = LL_GPTMRX_CAP_INPUT_SRC_IN9,
    HAL_GPTMRX_CAP_INPUT_SRC_IN10 = LL_GPTMRX_CAP_INPUT_SRC_IN10,
    HAL_GPTMRX_CAP_INPUT_SRC_IN11 = LL_GPTMRX_CAP_INPUT_SRC_IN11,
    HAL_GPTMRX_CAP_INPUT_SRC_IN12 = LL_GPTMRX_CAP_INPUT_SRC_IN12,
    HAL_GPTMRX_CAP_INPUT_SRC_IN13 = LL_GPTMRX_CAP_INPUT_SRC_IN13,
    HAL_GPTMRX_CAP_INPUT_SRC_IN14 = LL_GPTMRX_CAP_INPUT_SRC_IN14,
    HAL_GPTMRX_CAP_INPUT_SRC_IN15 = LL_GPTMRX_CAP_INPUT_SRC_IN15,
} HAL_GPTMRX_CapInputSrcTypeDef;

/**
  * @brief HAL GPTMRX Compare Output Polarity Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_CMP_POL_HIGH  = LL_GPTMRX_CMP_POL_HIGH,
    HAL_GPTMRX_CMP_POL_LOW   = LL_GPTMRX_CMP_POL_LOW,
} HAL_GPTMRX_CmpPolTypeDef;

/**
  * @brief HAL GPTMRX Compare Output Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_CMP_MODE_FREEZE         = LL_GPTMRX_CMP_MODE_FREEZE,
    HAL_GPTMRX_CMP_MODE_ACTIVE         = LL_GPTMRX_CMP_MODE_ACTIVE,
    HAL_GPTMRX_CMP_MODE_INACTIVE       = LL_GPTMRX_CMP_MODE_INACTIVE,
    HAL_GPTMRX_CMP_MODE_TOGGLE         = LL_GPTMRX_CMP_MODE_TOGGLE,
    HAL_GPTMRX_CMP_MODE_FORCE_INACTIVE = LL_GPTMRX_CMP_MODE_FORCE_INACTIVE,
    HAL_GPTMRX_CMP_MODE_FORCE_ACTIVE   = LL_GPTMRX_CMP_MODE_FORCE_ACTIVE,
    HAL_GPTMRX_CMP_MODE_PWM1           = LL_GPTMRX_CMP_MODE_PWM1,
    HAL_GPTMRX_CMP_MODE_PWM2           = LL_GPTMRX_CMP_MODE_PWM2,
    HAL_GPTMRX_CMP_MODE_RETRIG_OPM1    = LL_GPTMRX_CMP_MODE_RETRIG_OPM1,
    HAL_GPTMRX_CMP_MODE_RETRIG_OPM2    = LL_GPTMRX_CMP_MODE_RETRIG_OPM2,
    HAL_GPTMRX_CMP_MODE_COMB_PWM1      = LL_GPTMRX_CMP_MODE_COMB_PWM1,
    HAL_GPTMRX_CMP_MODE_COMB_PWM2      = LL_GPTMRX_CMP_MODE_COMB_PWM2,
    HAL_GPTMRX_CMP_MODE_ASYM_PWM1      = LL_GPTMRX_CMP_MODE_ASYM_PWM1,
    HAL_GPTMRX_CMP_MODE_ASYM_PWM2      = LL_GPTMRX_CMP_MODE_ASYM_PWM2,
} HAL_GPTMRX_OCModeTypeDef;

/**
  * @brief HAL GPTMRX TI0 Input Source Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_TI0_IN_SRC_CH0          = LL_GPTMRX_TI0_IN_SRC_CH0, 
    HAL_GPTMRX_TI0_IN_SRC_CH0_1_XOR    = LL_GPTMRX_TI0_IN_SRC_CH0_1_XOR
} HAL_GPTMRX_TI0InSrcTypeDef;

/**
  * @brief HAL GPTMRX Slave Mode Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_SLV_MODE_DIS        = LL_GPTMRX_SLV_MODE_DIS,
    HAL_GPTMRX_SLV_MODE_RST        = LL_GPTMRX_SLV_MODE_RST,
    HAL_GPTMRX_SLV_MODE_GATING     = LL_GPTMRX_SLV_MODE_GATING,
    HAL_GPTMRX_SLV_MODE_TRIG       = LL_GPTMRX_SLV_MODE_TRIG,
    HAL_GPTMRX_SLV_MODE_EXTCLK     = LL_GPTMRX_SLV_MODE_EXTCLK,
    HAL_GPTMRX_SLV_MODE_RST_TRIG   = LL_GPTMRX_SLV_MODE_RST_TRIG,
    HAL_GPTMRX_SLV_MODE_RST_GATING = LL_GPTMRX_SLV_MODE_RST_GATING,
} HAL_GPTMRX_SlvModeTypeDef;

/**
  * @brief HAL GPTMRX Break Polarity Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_BRK_POL_HIGH  = LL_GPTMRX_BRK_POL_HIGH,
    HAL_GPTMRX_BRK_POL_LOW   = LL_GPTMRX_BRK_POL_LOW,
} HAL_GPTMRX_BrkPolTypeDef;

/**
  * @brief HAL GPTMRX Break Input Polarity Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_BRK_IN_VALID_POL_HIGH  = LL_GPTMRX_BRK_IN_POL_VALID_HIGH,
    HAL_GPTMRX_BRK_IN_VALID_POL_LOW   = LL_GPTMRX_BRK_IN_POL_VALID_LOW,
} HAL_GPTMRX_BrkInputPolTypeDef;

typedef enum
{
    HAL_GPTMRX_BRK_IN_SRC_CMP0_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP0_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP1_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP1_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP2_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP2_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP3_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP3_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP4_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP4_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP5_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP5_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP6_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP6_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP7_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP7_OUT,
    HAL_GPTMRX_BRK_IN_SRC_CMP8_OUT     = LL_GPTMRX_BRK_IN_SRC_MASK_CMP8_OUT,
    HAL_GPTMRX_BRK_IN_SRC_TMRx_BKy     = LL_GPTMRX_BRK_IN_SRC_MASK_TMRx_BKy,
    HAL_GPTMRX_BRK_IN_SRC_ADC0_AWD0    = LL_GPTMRX_BRK_IN_SRC_MASK_ADC0_AWD0,
    HAL_GPTMRX_BRK_IN_SRC_ADC1_AWD0    = LL_GPTMRX_BRK_IN_SRC_MASK_ADC1_AWD0,
    HAL_GPTMRX_BRK_IN_SRC_PDM0_CMPH    = LL_GPTMRX_BRK_IN_SRC_MASK_PDM0_CMPH,
    HAL_GPTMRX_BRK_IN_SRC_PDM1_CMPH    = LL_GPTMRX_BRK_IN_SRC_MASK_PDM1_CMPH,
    HAL_GPTMRX_BRK_IN_SRC_PDM2_CMPH    = LL_GPTMRX_BRK_IN_SRC_MASK_PDM2_CMPH,
    HAL_GPTMRX_BRK_IN_SRC_PDM3_CMPH    = LL_GPTMRX_BRK_IN_SRC_MASK_PDM3_CMPH
} HAL_GPTMRX_BrkInputTypeDef;

/**
  * @brief HAL GPTMRX Idle Off-State Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_IDLE_OFF_STA_COMP_CLOSE = LL_GPTMRX_IDLE_OFF_STA_COMP_CLOSE,
    HAL_GPTMRX_IDLE_OFF_STA_COMP_IDLE   = LL_GPTMRX_IDLE_OFF_STA_COMP_IDLE,
} HAL_GPTMRX_IdleOffStaTypeDef;

/**
  * @brief HAL GPTMRX Run Off-State Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_RUN_OFF_STA_COMP_CLOSE = LL_GPTMRX_RUN_OFF_STA_COMP_CLOSE,
    HAL_GPTMRX_RUN_OFF_STA_COMP_IVD   = LL_GPTMRX_RUN_OFF_STA_COMP_IVD,
} HAL_GPTMRX_RunOffStaTypeDef;


/**
  * @brief HAL GPTMRX Trig Enumeration 
  */
typedef enum 
{
    HAL_GPTMRX_TRIG_ITR0  = LL_GPTMRX_TRIG_ITR0,
    HAL_GPTMRX_TRIG_ITR1  = LL_GPTMRX_TRIG_ITR1,
    HAL_GPTMRX_TRIG_ITR2  = LL_GPTMRX_TRIG_ITR2,
    HAL_GPTMRX_TRIG_ITR3  = LL_GPTMRX_TRIG_ITR3,
    HAL_GPTMRX_TRIG_ITR4  = LL_GPTMRX_TRIG_ITR4,
    HAL_GPTMRX_TRIG_ITR5  = LL_GPTMRX_TRIG_ITR5,
    HAL_GPTMRX_TRIG_ITR6  = LL_GPTMRX_TRIG_ITR6,
    HAL_GPTMRX_TRIG_ITR7  = LL_GPTMRX_TRIG_ITR7,
    HAL_GPTMRX_TRIG_ITR8  = LL_GPTMRX_TRIG_ITR8,
    HAL_GPTMRX_TRIG_ITR9  = LL_GPTMRX_TRIG_ITR9,
    HAL_GPTMRX_TRIG_ITR10 = LL_GPTMRX_TRIG_ITR10,
    HAL_GPTMRX_TRIG_ITR11 = LL_GPTMRX_TRIG_ITR11,
    HAL_GPTMRX_TRIG_ITR12 = LL_GPTMRX_TRIG_ITR12,
    HAL_GPTMRX_TRIG_ITR13 = LL_GPTMRX_TRIG_ITR13,
    HAL_GPTMRX_TRIG_ITR14 = LL_GPTMRX_TRIG_ITR14,
    HAL_GPTMRX_TRIG_ITR15 = LL_GPTMRX_TRIG_ITR15,
    HAL_GPTMRX_TRIG_CH0_FE = LL_GPTMRX_TRIG_CH0_FE,
    HAL_GPTMRX_TRIG_CH0_F = LL_GPTMRX_TRIG_CH0_F,
    HAL_GPTMRX_TRIG_CH1_F = LL_GPTMRX_TRIG_CH1_F,
} HAL_GPTMRX_TrigTypeDef;

/**
  * @brief HAL GPTMRX Event Source Enumeration 
  */
typedef enum
{
    HAL_GPTMRX_EVENTSOURCE_UPDATE  =   LL_GPTMRX_EVT_GEN_UPDATE,
    HAL_GPTMRX_EVENTSOURCE_TRIG    =   LL_GPTMRX_EVT_GEN_TRIGGER,
    HAL_GPTMRX_EVENTSOURCE_BRK0    =   LL_GPTMRX_EVT_GEN_BREAK0,
    HAL_GPTMRX_EVENTSOURCE_CC0     =   LL_GPTMRX_EVT_GEN_CAP_CMP_0,
    HAL_GPTMRX_EVENTSOURCE_CC1     =   LL_GPTMRX_EVT_GEN_CAP_CMP_1,
} HAL_GPTMRX_EvtSrcTypeDef;


/**
  * @brief  GPTMRX Base Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRX_EnableTypeDef          AutoReloadPreload;      /*!< Auto Preload Enable                        */
    HAL_GPTMRX_WorkModeTypeDef        WorkMode;               /*!< Work Mode: Continue/Single                 */
    uint16_t                          Period;                 /*!< Period Value                               */
    uint16_t                          Prescaler;              /*!< Clock Prescaler                            */
    HAL_GPTMRX_UpdateEvtDisTypeDef    UpdateEvent;            /*!< Update Event Enable                        */
    HAL_GPTMRX_UpdateEvtSrcTypeDef    UpdateSource;           /*!< Update Event Source                        */
    uint8_t                           RepetitionCounter;      /*!< Repeat Counter                             */
    HAL_GPTMRX_DzDigFilClkDivTypeDef  DzFilterClockDivision;  /*!< Dead Zone Digital Filter Clock Division    */
} HAL_GPTMRX_BaseInitTypeDef;

/**
  * @brief  GPTMRX Master Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRX_MstModeTypeDef         MasterMode;         /*!< Master Mode (TRGO source)          */
    uint8_t                           TRGCCWidth;         /*!< TRGCC Output Width                 */
    uint8_t                           TRGOWidth;          /*!< TRGO Output Width                  */
    HAL_GPTMRX_TrigOutChMskTypeDef    TRGOSelection;      /*!< Trigger Output Channel Selection   */
} HAL_GPTMRX_MstInitTypeDef;

/**
  * @brief  GPTMRX Input Capture Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRX_CapFilTypeDef          ICFilter;           /*!< Input Capture Filter               */
    HAL_GPTMRX_CapPolTypeDef          ICPolarity;         /*!< Input Capture Polarity             */
    HAL_GPTMRX_CapInputMapTypeDef     ICSelection;        /*!< Input Capture Map                  */
    HAL_GPTMRX_CapPrescalerTypeDef    ICPrescaler;        /*!< Input Capture Prescaler            */
    HAL_GPTMRX_CapInputSrcTypeDef     ICTriggerSource;    /*!< Input Capture Trigger Input Source */
} HAL_GPTMRX_InputCapInitTypeDef;

/**
  * @brief  GPTMRX Output Compare Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRX_EnableTypeDef          CompareAutoReload;  /*!< Output Compare Auto Preload Enable */
    uint16_t                          CompareValue;       /*!< Output Compare Match Value         */
    HAL_GPTMRX_OCModeTypeDef          OCMode;             /*!< Output Compare Mode                */
    HAL_GPTMRX_CmpPolTypeDef          OCPolarity;         /*!< OC Polarity                        */
    HAL_GPTMRX_CmpPolTypeDef          OCNPolarity;        /*!< OCN Polarity                       */
    HAL_GPTMRX_IdleStaTypeDef         OCIdleState;        /*!< OC idle state                      */
    HAL_GPTMRX_IdleStaTypeDef         OCNIdleState;       /*!< OCN idle state                     */
} HAL_GPTMRX_OutputCmpInitTypeDef;

/**
  * @brief  GPTMRX Slave / ETR Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRX_SlvModeTypeDef         SlaveMode;          /*!< Slave Mode                         */
    HAL_GPTMRX_TrigTypeDef            InputTrigger;       /*!< Trigger Selection                  */
    HAL_GPTMRX_EnableTypeDef          FastSync;           /*!< Mst/Slv Fast Sync Enable           */
} HAL_GPTMRX_SlvInitTypeDef;

/**
  * @brief  GPTMRX Break and Dead-Time Initialization Structure Definition
  */
typedef struct
{
    HAL_GPTMRX_EnableTypeDef          Break0State;        /*!< Break 0 enable                     */
    HAL_GPTMRX_BrkPolTypeDef          Break0Polarity;     /*!< Break 0 polarity                   */
    uint8_t                           Break0Filter;       /*!< Break 0 filter                     */
    HAL_GPTMRX_EnableTypeDef          BreakIT;            /*!< Break interrupt enable             */
    uint8_t                           DeadTime;           /*!< Dead-time generator value          */
    HAL_GPTMRX_EnableTypeDef          AutomaticOutput;    /*!< Automatic output enable            */
    HAL_GPTMRX_RunOffStaTypeDef       OffStateRunMode;    /*!< Off-state in run mode              */
    HAL_GPTMRX_IdleOffStaTypeDef      OffStateIdleMode;   /*!< Off-state in idle mode             */
} HAL_GPTMRX_BreakDeadTimeConfigTypeDef;

/**
  * @brief  TIM Break/Break2 input configuration
  */
typedef struct
{
    HAL_GPTMRX_BrkInputTypeDef        Source;   /*!< Specifies the source of the timer break input.             */
    HAL_GPTMRX_EnableTypeDef          Enable;   /*!< Specifies whether or not the break input source is enabled.*/
    HAL_GPTMRX_BrkInputPolTypeDef     Polarity; /*!< Specifies the break input source polarity.                 */
} HAL_GPTMRX_BreakInputConfigTypeDef;


/**
  * @brief HAL GPTMRX handle structure type
  */
typedef struct HAL_GPTMRX_HandleStructDef HAL_GPTMRX_HandleTypeDef;

/**
  * @brief GPTMRX IRQ callback function type definition
  */
typedef void (*HAL_GPTMRX_IRQCallback)(HAL_GPTMRX_HandleTypeDef *Handle);

/**
  * @brief  GPTMRX Handle Structure definition
  */
struct HAL_GPTMRX_HandleStructDef
{
    GPTMRx_TypeDef                           *Instance;        /*!< Register base address      */
    volatile HAL_GPTMRX_StateTypeDef         State;            /*!< GPTMRX operation state      */
    volatile HAL_GPTMRX_ErrCodeMskTypeDef    LastErrorCodes;   /*!< Last error codes           */
    const void                              *pUserData;       /*!< User data pointer          */
};
/**
  * @}
  */ /* GPTMRX_HAL_Exported_Types */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPTMRX_HAL_Exported_Functions GPTMRX HAL Exported Functions
  * @{
  */

/** @defgroup GPTMRX_HAL_EF_Initialization GPTMRX HAL Initialization
  * @{
  */

HAL_StatusTypeDef HAL_GPTMRX_Base_Init(HAL_GPTMRX_HandleTypeDef *Handle, 
                                      GPTMRx_TypeDef *GPTMRx,
                                      const HAL_GPTMRX_BaseInitTypeDef *pInit);
                              
HAL_StatusTypeDef HAL_GPTMRX_Base_DeInit(HAL_GPTMRX_HandleTypeDef *Handle);

void HAL_GPTMRX_Base_MspInit(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_Base_MspDeInit(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_IoInit(GPTMRx_TypeDef *GPTMRx);
void HAL_GPTMRX_IoDeInit(GPTMRx_TypeDef *GPTMRx);
/**
  * @}
  */

/** @defgroup GPTMRX_HAL_EF_Configuration GPTMRX HAL Configuration
  * @{
  */

HAL_StatusTypeDef HAL_GPTMRX_IC_Init(HAL_GPTMRX_HandleTypeDef *Handle, 
                                    HAL_GPTMRX_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRX_InputCapInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRX_OC_Init(HAL_GPTMRX_HandleTypeDef *Handle, 
                                    HAL_GPTMRX_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRX_OutputCmpInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRX_InitMaster(HAL_GPTMRX_HandleTypeDef *Handle,
                                       const HAL_GPTMRX_MstInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRX_InitSlave(HAL_GPTMRX_HandleTypeDef *Handle,
                                      const HAL_GPTMRX_SlvInitTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRX_ConfigBreakDeadTime(HAL_GPTMRX_HandleTypeDef *Handle,
                                      const HAL_GPTMRX_BreakDeadTimeConfigTypeDef *pCfg);

HAL_StatusTypeDef HAL_GPTMRX_ConfigBreakInput(HAL_GPTMRX_HandleTypeDef *Handle,
                                             HAL_GPTMRX_BreakInputTypeDef BreakInput,
                                             const HAL_GPTMRX_BreakInputConfigTypeDef *pCfg);

/**
  * @}
  */

/** @defgroup GPTMRX_HAL_EF_IO_Operation GPTMRX HAL IO Operation
  * @{
  */
HAL_StatusTypeDef HAL_GPTMRX_Base_Start(HAL_GPTMRX_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_GPTMRX_Base_Stop(HAL_GPTMRX_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_GPTMRX_Base_Start_IT(HAL_GPTMRX_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_GPTMRX_Base_Stop_IT(HAL_GPTMRX_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_GPTMRX_OC_Start(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_OC_Stop(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_OC_StartIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_OC_StopIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_GPTMRX_OCN_Start(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_OCN_Stop(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_OCN_StartIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_OCN_StopIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_GPTMRX_IC_Start(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_IC_Stop(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_IC_StartIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
HAL_StatusTypeDef HAL_GPTMRX_IC_StopIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);

HAL_StatusTypeDef HAL_GPTMRX_InterruptRequestEnable(HAL_GPTMRX_HandleTypeDef *Handle, 
                                                   HAL_GPTMRX_ITEnMskTypeDef ITMask);

HAL_StatusTypeDef HAL_GPTMRX_InterruptRequestDisable(HAL_GPTMRX_HandleTypeDef *Handle, 
                                                    HAL_GPTMRX_ITEnMskTypeDef ITMask);

HAL_StatusTypeDef HAL_GPTMRX_GenerateEvent(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_EvtSrcTypeDef EventSource);

uint16_t HAL_GPTMRX_ReadCounter(const HAL_GPTMRX_HandleTypeDef *Handle);
uint16_t HAL_GPTMRX_ReadCapturedValue(const HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
/**
  * @}
  */

/** @defgroup GPTMRX_HAL_EF_IRQ_Handler GPTMRX HAL IRQ Handler and Callbacks
  * @{
  */

void HAL_GPTMRX_BRK_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_UPD_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_TRG_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_CC_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_CCx_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);

void HAL_GPTMRX_OverflowCallback(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_PeriodElapsedCallback(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_TriggerCallback(HAL_GPTMRX_HandleTypeDef *Handle);
void HAL_GPTMRX_BreakCallback(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ITPendingMskTypeDef BreakEvent);
void HAL_GPTMRX_OC_DelayElapsedCallback(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
void HAL_GPTMRX_IC_CaptureCallback(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
void HAL_GPTMRX_IC_OverCaptureCallback(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel);
/**
  * @}
  */

/**
  * @}
  */ /* GPTMRX_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

#endif /* GPTMRX */
#endif /* HAL_MODULE_ENABLED */
#endif /* HAL_GPTMRX_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_GPTMRX_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
