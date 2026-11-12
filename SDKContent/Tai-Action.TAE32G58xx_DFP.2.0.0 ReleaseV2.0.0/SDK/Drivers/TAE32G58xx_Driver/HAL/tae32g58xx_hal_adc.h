/**
  ******************************************************************************
  * @file    tae32g58xx_hal_adc.h
  * @author  Tai-Action SD Team
  * @brief   Header file for ADC HAL module
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
#ifndef _TAE32G58XX_HAL_ADC_H_
#define _TAE32G58XX_HAL_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_adc.h"

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(ADC0) || defined(ADC1) || defined(ADC2) || defined(ADC3)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_ADC_MODULE_ENABLED) && (HAL_ADC_MODULE_ENABLED == 1)

/** @addtogroup ADC_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup ADC_HAL_Exported_Macros ADC HAL Exported Macros
  * @brief    ADC HAL Exported Macros
  * @{
  */

/** @defgroup ADC_HAL_EM_Assert ADC HAL Assert 
  * @brief    ADC HAL Assert
  * @{
  */

/**
  * @brief  The HAL_ADC_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_ADC_CHECK_PARAM
#define TAE32_USE_HAL_ADC_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_ADC_CHECK_PARAM != 1) && (TAE32_USE_HAL_ADC_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_ADC_CHECK_PARAM
#define TAE32_USE_HAL_ADC_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_ADC_CHECK_PARAM */

/**
  * @brief  The HAL_ADC_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_ADC_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_ADC_CHECK_PARAM) { \
            expression;                      \
        }

/**
 * @brief Updates a ADC HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the ADC process
 * state check feature is enabled (TAE32_USE_HAL_ADC_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_ADC_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_ADC_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_ADC_CHECK_PROCESS_STATE == 1)
#define HAL_ADC_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_ADC_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
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
  * @}
  */ /* ADC_HAL_EM_Assert */

/** @defgroup ADC_HAL_EM_Discriminant ADC HAL Discriminant
  * @brief    ADC HAL Discriminant
  * @{
  */


/**
  * @}
  */ /* ADC_HAL_EM_Discriminant */

/** @defgroup HAL_ADC_EC_Error_Code HAL ADC Error Code
  * @brief    ADC HAL Error Code
  * @{
  */

/** @name HAL_ADC_ErrCodeMskTypeDef
  * @brief  HAL ADC Error Code Mask definition.
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_ADC_ErrCodeMskTypeDef                           uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_ADC_ErrCodeMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_ADC_ERROR_NONE                                  (0U)                                              /*!< No error                 */
#define HAL_ADC_ERROR_OVERRUN                               (1U << 30U)                                       /*!< Overrun                  */
/** @} */

/**
  * @}
  */ /* HAL_ADC_EC_Error_Code */


/** @defgroup ADC_HAL_EM_Mask ADC HAL Mask
  * @brief    ADC HAL Mask
  * @{
  */

/** @name HAL_ADC_StateMaskTypeDef
  * @brief  HAL ADC Global States definition.
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_ADC_StateMaskTypeDef                            uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_ADC_StateMaskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_ADC_STATE_MASK_RESET                            (0U)            /*!< ADC not yet initialized                    */
#define HAL_ADC_STATE_MASK_INIT                             (1U << 30U)     /*!< ADC initialized but not yet configured      \
                                                                              (transition stage)                            */
#define HAL_ADC_STATE_MASK_CONFIGURING                      (1U << 29U)     /*!< ADC configuration ongoing                  */
#define HAL_ADC_STATE_MASK_READY                            (1U << 28U)     /*!< ADC configured and ready to be activated    \
                                                                              (transition stage)                            */
#define HAL_ADC_STATE_MASK_ACTIVE                           (1U << 27U)     /*!< ADC activated, ready to operate            */
#define HAL_ADC_STATE_MASK_CALIB                            (1U << 26U)     /*!< ADC calibration ongoing                    */
/** @} */

/** @name HAL_ADC_GrpStateMaskTypeDef
  * @brief HAL ADC Group State definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_ADC_GrpStateMaskTypeDef                         uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_ADC_GrpStateMaskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_ADC_GRP_STATE_MASK_RESET                        (0U)            /*!< ADC group not yet initialized              */
#define HAL_ADC_GRP_STATE_MASK_CONFIG                       (1U << 30U)     /*!< ADC group configuration ongoing            */
#define HAL_ADC_GRP_STATE_MASK_IDLE                         (1U << 29U)     /*!< ADC group initialized and ready to operate */
#define HAL_ADC_GRP_STATE_MASK_ACTIVE                       (1U << 28U)     /*!< ADC group operating                        */
/** @} */

/** @name HAL_ADC_GrpConvMaskTypeDef
  * @brief HAL ADC Group Conversions Tyoe Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_ADC_GrpConvMaskTypeDef                          uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_ADC_GrpConvMaskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_ADC_GRP_CONV_MASK_ONCE                          (0U)            /*!< ADC group once conversion                  */
#define HAL_ADC_GRP_CONV_MASK_CONTINUOUS                    (1U << 30U)     /*!< ADC group continuous conversions           */
/** @} */

/** @name HAL_ADC_ITEnMskTypeDef
  * @brief HAL ADC IER Interrupt Enable Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_ADC_ITEnMskTypeDef                              LL_ADC_IER_ITEnMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_ADC_IER_ITEnMskTypeDef HAL_ADC_ITEnMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_ADC_IER_SAMPLING_END_IT_EN                      LL_ADC_IER_EOSMPIE                                /*!< EOSMPIE Mask             */
#define HAL_ADC_IER_ADC_READY_IT_EN                         LL_ADC_IER_ADRDYIE                                /*!< ADRDYIE Mask             */
#define HAL_ADC_IER_ANALOG_WATCHDOG_2_IT_EN                 LL_ADC_IER_AWD2IE                                 /*!< AWD2IE Mask              */
#define HAL_ADC_IER_ANALOG_WATCHDOG_1_IT_EN                 LL_ADC_IER_AWD1IE                                 /*!< AWD1IE Mask              */
#define HAL_ADC_IER_ANALOG_WATCHDOG_0_IT_EN                 LL_ADC_IER_AWD0IE                                 /*!< AWD0IE Mask              */
#define HAL_ADC_IER_OVERRUN_IT_EN                           LL_ADC_IER_OVRIE                                  /*!< OVRIE Mask               */
#define HAL_ADC_IER_INJECTED_SEQUENCE_END_IT_EN             LL_ADC_IER_JEOSIE                                 /*!< JEOSIE Mask              */
#define HAL_ADC_IER_INJECTED_CONVERT_END_IT_EN              LL_ADC_IER_JEOCIE                                 /*!< JEOCIE Mask              */
#define HAL_ADC_IER_REGULAR_SEQUENCE_END_IT_EN              LL_ADC_IER_EOSIE                                  /*!< EOSIE Mask               */
#define HAL_ADC_IER_REGULAR_CONVERT_END_IT_EN               LL_ADC_IER_EOCIE                                  /*!< EOCIE Mask               */
/** @} */

/** @name HAL_ADC_ITPendingMskTypeDef
  * @brief HAL ADC ISR Interrupt Flag Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_ADC_ITPendingMskTypeDef                         LL_ADC_ISR_ITPendingMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_ADC_ISR_ITPendingMskTypeDef HAL_ADC_ITPendingMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_ADC_ISR_SAMPLING_END_IT_FLAG                    LL_ADC_ISR_EOSMP                                  /*!< EOSMP Mask               */
#define HAL_ADC_ISR_ADC_READY_IT_FLAG                       LL_ADC_ISR_ADRDY                                  /*!< ADRDY Mask               */
#define HAL_ADC_ISR_ANALOG_WATCHDOG_2_IT_FLAG               LL_ADC_ISR_AWD2                                   /*!< AWD2 Mask                */
#define HAL_ADC_ISR_ANALOG_WATCHDOG_1_IT_FLAG               LL_ADC_ISR_AWD1                                   /*!< AWD1 Mask                */
#define HAL_ADC_ISR_ANALOG_WATCHDOG_0_IT_FLAG               LL_ADC_ISR_AWD0                                   /*!< AWD0 Mask                */
#define HAL_ADC_ISR_OVERRUN_IT_FLAG                         LL_ADC_ISR_OVR                                    /*!< OVR Mask                 */
#define HAL_ADC_ISR_INJECTED_SEQUENCE_END_IT_FLAG           LL_ADC_ISR_JEOS                                   /*!< JEOS Mask                */
#define HAL_ADC_ISR_INJECTED_CONVERT_END_IT_FLAG            LL_ADC_ISR_JEOC                                   /*!< JEOC Mask                */
#define HAL_ADC_ISR_REGULAR_SEQUENCE_END_IT_FLAG            LL_ADC_ISR_EOS                                    /*!< EOS Mask                 */
#define HAL_ADC_ISR_REGULAR_CONVERT_END_IT_FLAG             LL_ADC_ISR_EOC                                    /*!< EOC Mask                 */
/** @} */

/**
  * @}
  */ /* ADC_HAL_EM_Mask */


/**
  * @}
  */ /* ADC_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup ADC_HAL_Exported_Types ADC HAL Exported Types
  * @brief    ADC HAL Exported Types
  * @{
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
/**
  * @brief  HAL ADC Global States Definition
  */
typedef enum
{
  HAL_ADC_STATE_RESET           = HAL_ADC_STATE_MASK_RESET,          /*!< ADC not yet initialized                                     */
  HAL_ADC_STATE_INIT            = HAL_ADC_STATE_MASK_INIT,           /*!< ADC initialized but not yet configured (transition stage)   */
  HAL_ADC_STATE_CONFIGURING     = HAL_ADC_STATE_MASK_CONFIGURING,    /*!< ADC configuration ongoing                                   */
  HAL_ADC_STATE_READY           = HAL_ADC_STATE_MASK_READY,          /*!< ADC configured and ready to be activated (transition stage) */
  HAL_ADC_STATE_ACTIVE          = HAL_ADC_STATE_MASK_ACTIVE,         /*!< ADC activated, ready to operate                             */
  HAL_ADC_STATE_CALIB           = HAL_ADC_STATE_MASK_CALIB,          /*!< ADC calibration ongoing                                     */
} HAL_ADC_StateTypeDef;

_Static_assert(sizeof(HAL_ADC_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

/**
  * @brief HAL ADC Group State Definition
  */
typedef enum
{
    HAL_ADC_GRP_STATE_RESET     = HAL_ADC_GRP_STATE_MASK_RESET,     /*!< ADC group not yet initialized                */
    HAL_ADC_GRP_STATE_CONFIG    = HAL_ADC_GRP_STATE_MASK_CONFIG,    /*!< ADC group configuration ongoing              */
    HAL_ADC_GRP_STATE_IDLE      = HAL_ADC_GRP_STATE_MASK_IDLE,      /*!< ADC ready to convert data                    */
    HAL_ADC_GRP_STATE_ACTIVE    = HAL_ADC_GRP_STATE_MASK_ACTIVE     /*!< ADC group operating                          */
} HAL_ADC_GrpStateTypeDef;

_Static_assert(sizeof(HAL_ADC_GrpStateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

/**
  * @brief HAL ADC Group Conversions Tyoe Definition
  */
typedef enum
{
  HAL_ADC_GRP_CONV_ONCE         = HAL_ADC_GRP_CONV_MASK_ONCE,       /*!< ADC group configured to single conversion      */
  HAL_ADC_GRP_CONV_CONTINUOUS   = HAL_ADC_GRP_CONV_MASK_CONTINUOUS  /*!< ADC group configured to continuous conversions */
} HAL_ADC_GrpConvTypeDef;

_Static_assert(sizeof(HAL_ADC_GrpConvTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else /* TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

typedef HAL_ADC_StateMaskTypeDef        HAL_ADC_StateTypeDef;
#define HAL_ADC_STATE_RESET             HAL_ADC_STATE_MASK_RESET
#define HAL_ADC_STATE_INIT              HAL_ADC_STATE_MASK_INIT
#define HAL_ADC_STATE_CONFIGURING       HAL_ADC_STATE_MASK_CONFIGURING
#define HAL_ADC_STATE_READY             HAL_ADC_STATE_MASK_READY
#define HAL_ADC_STATE_ACTIVE            HAL_ADC_STATE_MASK_ACTIVE
#define HAL_ADC_STATE_CALIB             HAL_ADC_STATE_MASK_CALIB

typedef HAL_ADC_GrpStateMaskTypeDef     HAL_ADC_GrpStateTypeDef;
#define HAL_ADC_GRP_STATE_RESET         HAL_ADC_GRP_STATE_MASK_RESET
#define HAL_ADC_GRP_STATE_CONFIG        HAL_ADC_GRP_STATE_MASK_CONFIG
#define HAL_ADC_GRP_STATE_IDLE          HAL_ADC_GRP_STATE_MASK_IDLE
#define HAL_ADC_GRP_STATE_ACTIVE        HAL_ADC_GRP_STATE_MASK_ACTIVE

typedef HAL_ADC_GrpConvMaskTypeDef      HAL_ADC_GrpConvTypeDef;
#define HAL_ADC_GRP_CONV_ONCE           HAL_ADC_GRP_CONV_MASK_ONCE
#define HAL_ADC_GRP_CONV_CONTINUOUS     HAL_ADC_GRP_CONV_MASK_CONTINUOUS
#endif /* !TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */


/**
  * @brief ADC Function Enable Definition
  */
typedef enum
{
    HAL_ADC_FUNC_DISABLE  = 0U,    /*!< ADC Function Disable  */
    HAL_ADC_FUNC_ENABLE   = 1U     /*!< ADC Function Enable   */
} HAL_ADC_EnableTypeDef;

/**
  * @brief ADC Sampling Group Definition
  */
typedef enum
{
    HAL_ADC_GROUP_REGULAR   = 0U,   /*!< ADC group regular  */
    HAL_ADC_GROUP_INJECTED  = 1U,   /*!< ADC group injected */
} HAL_ADC_SampGrpTypeDef;

/**
  * @brief ADC Channel Definition
  */
typedef enum
{
    HAL_ADC_CH_0          = LL_ADC_CH_0,     /*!< ADC Channel 0    */
    HAL_ADC_CH_1          = LL_ADC_CH_1,     /*!< ADC Channel 1    */
    HAL_ADC_CH_2          = LL_ADC_CH_2,     /*!< ADC Channel 2    */
    HAL_ADC_CH_3          = LL_ADC_CH_3,     /*!< ADC Channel 3    */
    HAL_ADC_CH_4          = LL_ADC_CH_4,     /*!< ADC Channel 4    */
    HAL_ADC_CH_5          = LL_ADC_CH_5,     /*!< ADC Channel 5    */
    HAL_ADC_CH_6          = LL_ADC_CH_6,     /*!< ADC Channel 6    */
    HAL_ADC_CH_7          = LL_ADC_CH_7,     /*!< ADC Channel 7    */
    HAL_ADC_CH_8          = LL_ADC_CH_8,     /*!< ADC Channel 8    */
    HAL_ADC_CH_9          = LL_ADC_CH_9,     /*!< ADC Channel 9    */
    HAL_ADC_CH_10         = LL_ADC_CH_10,    /*!< ADC Channel 10   */
    HAL_ADC_CH_11         = LL_ADC_CH_11,    /*!< ADC Channel 11   */
    HAL_ADC_CH_12         = LL_ADC_CH_12,    /*!< ADC Channel 12   */
    HAL_ADC_CH_13         = LL_ADC_CH_13,    /*!< ADC Channel 13   */
    HAL_ADC_CH_14         = LL_ADC_CH_14,    /*!< ADC Channel 14   */
    HAL_ADC_CH_15         = LL_ADC_CH_15,    /*!< ADC Channel 15   */
    HAL_ADC_CH_16         = LL_ADC_CH_16,    /*!< ADC Channel 16   */
    HAL_ADC_CH_17         = LL_ADC_CH_17,    /*!< ADC Channel 17   */
    HAL_ADC_CH_18         = LL_ADC_CH_18,    /*!< ADC Channel 18   */
    HAL_ADC_CH_19         = LL_ADC_CH_19,    /*!< ADC Channel 19   */
    HAL_ADC_CH_NUMS       = LL_ADC_CH_NUMS   /*!< ADC Ch Nums      */
} HAL_ADC_ChTypeDef;

/**
  * @brief ADC Regular Sequence Number Definition
  */
typedef enum
{
    HAL_ADC_REG_SEQ_NUM_1   = LL_ADC_REG_SEQ_NUM_1,    /*!< ADC Regular Sequence Number 1    */
    HAL_ADC_REG_SEQ_NUM_2   = LL_ADC_REG_SEQ_NUM_2,    /*!< ADC Regular Sequence Number 2    */
    HAL_ADC_REG_SEQ_NUM_3   = LL_ADC_REG_SEQ_NUM_3,    /*!< ADC Regular Sequence Number 3    */
    HAL_ADC_REG_SEQ_NUM_4   = LL_ADC_REG_SEQ_NUM_4,    /*!< ADC Regular Sequence Number 4    */
    HAL_ADC_REG_SEQ_NUM_5   = LL_ADC_REG_SEQ_NUM_5,    /*!< ADC Regular Sequence Number 5    */
    HAL_ADC_REG_SEQ_NUM_6   = LL_ADC_REG_SEQ_NUM_6,    /*!< ADC Regular Sequence Number 6    */
    HAL_ADC_REG_SEQ_NUM_7   = LL_ADC_REG_SEQ_NUM_7,    /*!< ADC Regular Sequence Number 7    */
    HAL_ADC_REG_SEQ_NUM_8   = LL_ADC_REG_SEQ_NUM_8,    /*!< ADC Regular Sequence Number 8    */
    HAL_ADC_REG_SEQ_NUM_9   = LL_ADC_REG_SEQ_NUM_9,    /*!< ADC Regular Sequence Number 9    */
    HAL_ADC_REG_SEQ_NUM_10  = LL_ADC_REG_SEQ_NUM_10,   /*!< ADC Regular Sequence Number 10   */
    HAL_ADC_REG_SEQ_NUM_11  = LL_ADC_REG_SEQ_NUM_11,   /*!< ADC Regular Sequence Number 11   */
    HAL_ADC_REG_SEQ_NUM_12  = LL_ADC_REG_SEQ_NUM_12,   /*!< ADC Regular Sequence Number 12   */
    HAL_ADC_REG_SEQ_NUM_13  = LL_ADC_REG_SEQ_NUM_13,   /*!< ADC Regular Sequence Number 13   */
    HAL_ADC_REG_SEQ_NUM_14  = LL_ADC_REG_SEQ_NUM_14,   /*!< ADC Regular Sequence Number 14   */
    HAL_ADC_REG_SEQ_NUM_15  = LL_ADC_REG_SEQ_NUM_15,   /*!< ADC Regular Sequence Number 15   */
    HAL_ADC_REG_SEQ_NUM_16  = LL_ADC_REG_SEQ_NUM_16,   /*!< ADC Regular Sequence Number 16   */
    HAL_ADC_REG_SEQ_NUMS    = LL_ADC_REG_SEQ_NUMS      /*!< ADC Regular Sequence Numbers     */
} HAL_ADC_REG_SeqNumTypeDef;

/**
  * @brief ADC Injected Sequence Number Definition
  */
typedef enum
{
    HAL_ADC_INJ_SEQ_NUM_1  = LL_ADC_INJ_SEQ_NUM_1,   /*!< ADC Injected Sequence Number 1   */
    HAL_ADC_INJ_SEQ_NUM_2  = LL_ADC_INJ_SEQ_NUM_2,   /*!< ADC Injected Sequence Number 2   */
    HAL_ADC_INJ_SEQ_NUM_3  = LL_ADC_INJ_SEQ_NUM_3,   /*!< ADC Injected Sequence Number 3   */
    HAL_ADC_INJ_SEQ_NUM_4  = LL_ADC_INJ_SEQ_NUM_4,   /*!< ADC Injected Sequence Number 4   */
    HAL_ADC_INJ_SEQ_NUMS   = LL_ADC_INJ_SEQ_NUMS     /*!< ADC Injected Sequence Numbers    */
} HAL_ADC_INJ_SeqNumTypeDef;

/**
  * @brief ADC AWDG Number Definition
  */
typedef enum
{
    HAL_ADC_AWDG_NUM_0    = LL_ADC_AWDG_NUM_0,   /*!< ADC AWDG Number 0   */
    HAL_ADC_AWDG_NUM_1    = LL_ADC_AWDG_NUM_1,   /*!< ADC AWDG Number 1   */
    HAL_ADC_AWDG_NUM_2    = LL_ADC_AWDG_NUM_2,   /*!< ADC AWDG Number 2   */
    HAL_ADC_AWDG_NUMS     = LL_ADC_AWDG_NUMS     /*!< ADC AWDG Numbers    */
} HAL_ADC_AWDG_NumTypeDef;

/**
  * @brief ADC Channel Calibration Coefficient Group Definition
  */
typedef enum
{
    HAL_ADC_CAL_COEF_GRP_0     = LL_ADC_CAL_COEF_GRP_0,     /*!< ADC Channel Calibration Coefficient Group 0      */
    HAL_ADC_CAL_COEF_GRP_1     = LL_ADC_CAL_COEF_GRP_1,     /*!< ADC Channel Calibration Coefficient Group 1      */
    HAL_ADC_CAL_COEF_GRP_2     = LL_ADC_CAL_COEF_GRP_2,     /*!< ADC Channel Calibration Coefficient Group 2      */
    HAL_ADC_CAL_COEF_GRP_3     = LL_ADC_CAL_COEF_GRP_3,     /*!< ADC Channel Calibration Coefficient Group 3      */
    HAL_ADC_CAL_COEF_GRP_NUMS  = LL_ADC_CAL_COEF_GRP_NUMS   /*!< ADC Channel Calibration Coefficient Group Nums   */
} HAL_ADC_CalCoefGrpTypeDef;

/**
  * @brief Regular Discontinuous Conversion Numbers Definition
  */
typedef enum
{
    HAL_ADC_REG_DISCONT_CONV_NUM_1  = LL_ADC_REG_DISCONT_CONV_NUM_1,   /*!< Regular Discontinuous Conversion Numbers 1   */
    HAL_ADC_REG_DISCONT_CONV_NUM_2  = LL_ADC_REG_DISCONT_CONV_NUM_2,   /*!< Regular Discontinuous Conversion Numbers 2   */
    HAL_ADC_REG_DISCONT_CONV_NUM_3  = LL_ADC_REG_DISCONT_CONV_NUM_3,   /*!< Regular Discontinuous Conversion Numbers 3   */
    HAL_ADC_REG_DISCONT_CONV_NUM_4  = LL_ADC_REG_DISCONT_CONV_NUM_4,   /*!< Regular Discontinuous Conversion Numbers 4   */
    HAL_ADC_REG_DISCONT_CONV_NUM_5  = LL_ADC_REG_DISCONT_CONV_NUM_5,   /*!< Regular Discontinuous Conversion Numbers 5   */
    HAL_ADC_REG_DISCONT_CONV_NUM_6  = LL_ADC_REG_DISCONT_CONV_NUM_6,   /*!< Regular Discontinuous Conversion Numbers 6   */
    HAL_ADC_REG_DISCONT_CONV_NUM_7  = LL_ADC_REG_DISCONT_CONV_NUM_7,   /*!< Regular Discontinuous Conversion Numbers 7   */
    HAL_ADC_REG_DISCONT_CONV_NUM_8  = LL_ADC_REG_DISCONT_CONV_NUM_8    /*!< Regular Discontinuous Conversion Numbers 8   */
} HAL_ADC_REG_DisContConvNumTypeDef;

/**
  * @brief ADC Regular Sequence Length Definition
  */
typedef enum
{
    HAL_ADC_REG_SEQ_LEN_1   = LL_ADC_REG_SEQ_LEN_1,    /*!< ADC Regular Sequence Length 1    */
    HAL_ADC_REG_SEQ_LEN_2   = LL_ADC_REG_SEQ_LEN_2,    /*!< ADC Regular Sequence Length 2    */
    HAL_ADC_REG_SEQ_LEN_3   = LL_ADC_REG_SEQ_LEN_3,    /*!< ADC Regular Sequence Length 3    */
    HAL_ADC_REG_SEQ_LEN_4   = LL_ADC_REG_SEQ_LEN_4,    /*!< ADC Regular Sequence Length 4    */
    HAL_ADC_REG_SEQ_LEN_5   = LL_ADC_REG_SEQ_LEN_5,    /*!< ADC Regular Sequence Length 5    */
    HAL_ADC_REG_SEQ_LEN_6   = LL_ADC_REG_SEQ_LEN_6,    /*!< ADC Regular Sequence Length 6    */
    HAL_ADC_REG_SEQ_LEN_7   = LL_ADC_REG_SEQ_LEN_7,    /*!< ADC Regular Sequence Length 7    */
    HAL_ADC_REG_SEQ_LEN_8   = LL_ADC_REG_SEQ_LEN_8,    /*!< ADC Regular Sequence Length 8    */
    HAL_ADC_REG_SEQ_LEN_9   = LL_ADC_REG_SEQ_LEN_9,    /*!< ADC Regular Sequence Length 9    */
    HAL_ADC_REG_SEQ_LEN_10  = LL_ADC_REG_SEQ_LEN_10,   /*!< ADC Regular Sequence Length 10   */
    HAL_ADC_REG_SEQ_LEN_11  = LL_ADC_REG_SEQ_LEN_11,   /*!< ADC Regular Sequence Length 11   */
    HAL_ADC_REG_SEQ_LEN_12  = LL_ADC_REG_SEQ_LEN_12,   /*!< ADC Regular Sequence Length 12   */
    HAL_ADC_REG_SEQ_LEN_13  = LL_ADC_REG_SEQ_LEN_13,   /*!< ADC Regular Sequence Length 13   */
    HAL_ADC_REG_SEQ_LEN_14  = LL_ADC_REG_SEQ_LEN_14,   /*!< ADC Regular Sequence Length 14   */
    HAL_ADC_REG_SEQ_LEN_15  = LL_ADC_REG_SEQ_LEN_15,   /*!< ADC Regular Sequence Length 15   */
    HAL_ADC_REG_SEQ_LEN_16  = LL_ADC_REG_SEQ_LEN_16    /*!< ADC Regular Sequence Length 16   */
} HAL_ADC_REG_SeqLenTypeDef;

/**
  * @brief Regular Conversion Mode Definition
  */
typedef enum
{
    HAL_ADC_REG_CONV_SINGLE      = LL_ADC_REG_CONV_SINGLE,      /*!< Regular Conversion Mode Single       */
    HAL_ADC_REG_CONV_CONTINUOUS  = LL_ADC_REG_CONV_CONTINUOUS   /*!< Regular Conversion Mode Continuous   */
} HAL_ADC_REG_ConvModeTypeDef;

/**
  * @brief Regular Conversion Mode Definition
  */
typedef enum
{
    HAL_ADC_DISCONTINUE_CONV_DISABLE = 0U,  /*!< Discontinuous Conversion Mode Disable  */
    HAL_ADC_DISCONTINUE_CONV_ENABLE  = 1U   /*!< Discontinuous Conversion Mode Enable   */
} HAL_ADC_DiscontConvTypeDef;

/**
  * @brief ADC Channel Input Mode Definition
  */
typedef enum
{
    HAL_ADC_INPUT_MODE_SINGLE_END  = LL_ADC_INPUT_MODE_SINGLE_END,   /*!< ADC Channel Input Mode Single-End     */
    HAL_ADC_INPUT_MODE_DIFF        = LL_ADC_INPUT_MODE_DIFF          /*!< ADC Channel Input Mode Differential   */
} HAL_ADC_InputModeTypeDef;

/**
  * @brief ADC Channel Sample Time Definition
  */
typedef enum
{
    HAL_ADC_SAMP_TIME_2_CYCLES    = LL_ADC_SAMP_TIME_2_CYCLES,     /*!< ADC Channel Sample Time 2 Cycles     */
    HAL_ADC_SAMP_TIME_6_CYCLES    = LL_ADC_SAMP_TIME_6_CYCLES,     /*!< ADC Channel Sample Time 6 Cycles     */
    HAL_ADC_SAMP_TIME_14_CYCLES   = LL_ADC_SAMP_TIME_14_CYCLES,    /*!< ADC Channel Sample Time 14 Cycles    */
    HAL_ADC_SAMP_TIME_30_CYCLES   = LL_ADC_SAMP_TIME_30_CYCLES,    /*!< ADC Channel Sample Time 30 Cycles    */
    HAL_ADC_SAMP_TIME_62_CYCLES   = LL_ADC_SAMP_TIME_62_CYCLES,    /*!< ADC Channel Sample Time 62 Cycles    */
    HAL_ADC_SAMP_TIME_126_CYCLES  = LL_ADC_SAMP_TIME_126_CYCLES,   /*!< ADC Channel Sample Time 126 Cycles   */
    HAL_ADC_SAMP_TIME_254_CYCLES  = LL_ADC_SAMP_TIME_254_CYCLES,   /*!< ADC Channel Sample Time 254 Cycles   */
    HAL_ADC_SAMP_TIME_510_CYCLES  = LL_ADC_SAMP_TIME_510_CYCLES    /*!< ADC Channel Sample Time 510 Cycles   */
} HAL_ADC_SampTimeTypeDef;

/**
  * @brief ADC Injected Sequence Length Definition
  */
typedef enum
{
    HAL_ADC_INJ_SEQ_LEN_1  = LL_ADC_INJ_SEQ_LEN_1,   /*!< ADC Injected Sequence Length 1   */
    HAL_ADC_INJ_SEQ_LEN_2  = LL_ADC_INJ_SEQ_LEN_2,   /*!< ADC Injected Sequence Length 2   */
    HAL_ADC_INJ_SEQ_LEN_3  = LL_ADC_INJ_SEQ_LEN_3,   /*!< ADC Injected Sequence Length 3   */
    HAL_ADC_INJ_SEQ_LEN_4  = LL_ADC_INJ_SEQ_LEN_4    /*!< ADC Injected Sequence Length 4   */
} HAL_ADC_INJ_SeqLenTypeDef;

/**
  * @brief ADC Injected Conversion Mode Definition
  */
typedef enum
{
    HAL_ADC_INJ_AUTO_CONV_DISABLE = 0U,  /*!< Injected Auto-conversion Mode Disable  */
    HAL_ADC_INJ_AUTO_CONV_ENABLE  = 1U   /*!< Injected Auto-conversion Mode Enable   */
} HAL_ADC_INJ_ConvModeTypeDef;

/**
  * @brief Normal Channel Oversample Mode Definition
  */
typedef enum
{
    HAL_ADC_NORM_OVER_SAMP_CONTINUE  = LL_ADC_NORM_OVER_SAMP_CONTINUE,   /*!< Normal Channel Oversample Mode Continue   */
    HAL_ADC_NORM_OVER_SAMP_RESUME    = LL_ADC_NORM_OVER_SAMP_RESUME      /*!< Normal Channel Oversample Mode Resume     */
} HAL_ADC_NormChnlOverSampModeTypeDef;

/**
  * @brief Triggered Oversampling Mode Definition
  */
typedef enum
{
    HAL_ADC_TRIGGERED_OVER_SAMP_CONTINUE    = 0U,   /*!< Triggered Oversampling Continuous Mode     */
    HAL_ADC_TRIGGERED_OVER_SAMP_DISCONTINUE = 1U    /*!< Triggered Oversampling Discontinuous Mode  */
} HAL_ADC_TriggeredlOverSampModeTypeDef;

/**
  * @brief Overrun Mode Definition
  */
typedef enum
{
    HAL_ADC_OVERRUN_DATA_PRESERVED    = LL_ADC_OVERRUN_DATA_PRESERVED,    /*!< Overrun Mode Preserved    */
    HAL_ADC_OVERRUN_DATA_OVERWRITTEN  = LL_ADC_OVERRUN_DATA_OVERWRITTEN   /*!< Overrun Mode Overwriten   */
} HAL_ADC_OverRunModeTypeDef;

/**
  * @brief Over Sample Data Shift Definition
  */
typedef enum
{
    HAL_ADC_OVER_SAMP_SHIFT_NONE     = LL_ADC_OVER_SAMP_SHIFT_NONE,      /*!< Over Sample Data Shift None      */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_1  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_1,   /*!< Over Sample Data Shift Right 1   */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_2  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_2,   /*!< Over Sample Data Shift Right 2   */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_3  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_3,   /*!< Over Sample Data Shift Right 3   */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_4  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_4,   /*!< Over Sample Data Shift Right 4   */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_5  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_5,   /*!< Over Sample Data Shift Right 5   */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_6  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_6,   /*!< Over Sample Data Shift Right 6   */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_7  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_7,   /*!< Over Sample Data Shift Right 7   */
    HAL_ADC_OVER_SAMP_SHIFT_RIGHT_8  = LL_ADC_OVER_SAMP_SHIFT_RIGHT_8    /*!< Over Sample Data Shift Right 8   */
} HAL_ADC_OverSampShiftTypeDef;

/**
  * @brief Over Sample Ratio Definition
  */
typedef enum
{
    HAL_ADC_OVER_SAMP_RATIO_2    = LL_ADC_OVER_SAMP_RATIO_2,     /*!< Over Sample Ratio 2     */
    HAL_ADC_OVER_SAMP_RATIO_4    = LL_ADC_OVER_SAMP_RATIO_4,     /*!< Over Sample Ratio 4     */
    HAL_ADC_OVER_SAMP_RATIO_8    = LL_ADC_OVER_SAMP_RATIO_8,     /*!< Over Sample Ratio 8     */
    HAL_ADC_OVER_SAMP_RATIO_16   = LL_ADC_OVER_SAMP_RATIO_16,    /*!< Over Sample Ratio 16    */
    HAL_ADC_OVER_SAMP_RATIO_32   = LL_ADC_OVER_SAMP_RATIO_32,    /*!< Over Sample Ratio 32    */
    HAL_ADC_OVER_SAMP_RATIO_64   = LL_ADC_OVER_SAMP_RATIO_64,    /*!< Over Sample Ratio 64    */
    HAL_ADC_OVER_SAMP_RATIO_128  = LL_ADC_OVER_SAMP_RATIO_128,   /*!< Over Sample Ratio 128   */
    HAL_ADC_OVER_SAMP_RATIO_256  = LL_ADC_OVER_SAMP_RATIO_256    /*!< Over Sample Ratio 256   */
} HAL_ADC_OverSampRatioTypeDef;

/**
  * @brief ADC Bias Current Definition
  */
typedef enum
{
    HAL_ADC_BIAS_CUR_10uA  = LL_ADC_BIAS_CUR_10uA,   /*!< ADC Bias Current 10uA   */
    HAL_ADC_BIAS_CUR_12uA  = LL_ADC_BIAS_CUR_12uA,   /*!< ADC Bias Current 12uA   */
    HAL_ADC_BIAS_CUR_14uA  = LL_ADC_BIAS_CUR_14uA,   /*!< ADC Bias Current 14uA   */
    HAL_ADC_BIAS_CUR_8uA   = LL_ADC_BIAS_CUR_8uA     /*!< ADC Bias Current 8uA    */
} HAL_ADC_BiasCurTypeDef;

/**
  * @brief ADC Daul Mode Definition
  * @note  Dual mode Only Master ADC Valid
  *        Quad mode Only Master ADC0/2 Valid
  */
typedef enum
{
    HAL_ADC_MODE_INDEPEND                = LL_ADC_DUAL_MODE_INDEPEND,            /*!< ADC Mode Independent                             */
    HAL_ADC_DUAL_MODE_REG_INJ_SYNC       = LL_ADC_DUAL_MODE_REG_INJ_SYNC,        /*!< ADC Dual Mode Regular and Injected Sync          */
    HAL_ADC_DUAL_MODE_REG_SYNC_INJ_TRIG  = LL_ADC_DUAL_MODE_REG_SYNC_INJ_TRIG,   /*!< ADC Dual Mode Regular Sync and Injected Trigger  */
    HAL_ADC_DUAL_MODE_REG_TRIG_INJ_SYNC  = LL_ADC_DUAL_MODE_REG_TRIG_INJ_SYNC,   /*!< ADC Dual Mode Regular Trigger and Injected Sync  */
    HAL_ADC_DUAL_MODE_INJ_SYNC           = LL_ADC_DUAL_MODE_INJ_SYNC,            /*!< ADC Dual Mode Injected Sync                      */
    HAL_ADC_DUAL_MODE_REG_SYNC           = LL_ADC_DUAL_MODE_REG_SYNC,            /*!< ADC Dual Mode Regular Sync                       */
    HAL_ADC_DUAL_MODE_REG_INTERLEAVED    = LL_ADC_DUAL_MODE_REG_INTERLEAVED,     /*!< ADC Dual Mode Regular InterleaveD                */
    HAL_ADC_DUAL_MODE_INJ_TRIG           = LL_ADC_DUAL_MODE_INJ_TRIG,            /*!< ADC Dual Mode Injected Trigger                   */
    HAL_ADC_QUAD_MODE_INJ_SYNC           = LL_ADC_QUAD_MODE_INJ_SYNC,            /*!< ADC Quad Mode Injected Sync                      */
    HAL_ADC_QUAD_MODE_REG_SYNC           = LL_ADC_QUAD_MODE_REG_SYNC             /*!< ADC Quad Mode Regular Sync                       */
} HAL_ADC_DualModeTypeDef;

/**
  * @brief ADC Sequence Trigger Polarity Definition
  */
typedef enum
{
    HAL_ADC_SEQ_TRIG_POL_SW            = LL_ADC_SEQ_TRIG_POL_SW,            /*!< ADC Sequence Trigger Polarity Software           */
    HAL_ADC_SEQ_TRIG_POL_HW_RISING     = LL_ADC_SEQ_TRIG_POL_HW_RISING,     /*!< ADC Sequence Trigger Polarity Hardware Rising    */
    HAL_ADC_SEQ_TRIG_POL_HW_FALLING    = LL_ADC_SEQ_TRIG_POL_HW_FALLING,    /*!< ADC Sequence Trigger Polarity Hardware Falling   */
    HAL_ADC_SEQ_TRIG_POL_HW_BOTH_EDGE  = LL_ADC_SEQ_TRIG_POL_HW_BOTH_EDGE   /*!< ADC Sequence Trigger Polarity Hardware Both Edge */
} HAL_ADC_SeqTrigPolTypeDef;

/**
  * @brief ADC Sequence Trigger Event Definition
  */
typedef enum
{
    HAL_ADC_SEQ_TRIG_EVT_SOFTWARE        = LL_ADC_SEQ_TRIG_EVT_SOFTWARE,        /*!< ADC Sequence Trigger Event Software          */
    HAL_ADC_SEQ_TRIG_EVT_TMR7_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR7_TRGO,       /*!< ADC Sequence Trigger Event TMR7_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR8_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR8_TRGO,       /*!< ADC Sequence Trigger Event TMR8_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR0_CC0        = LL_ADC_SEQ_TRIG_EVT_TMR0_CC0,        /*!< ADC Sequence Trigger Event TMR0_CC0          */
    HAL_ADC_SEQ_TRIG_EVT_TMR1_CC0        = LL_ADC_SEQ_TRIG_EVT_TMR1_CC0,        /*!< ADC Sequence Trigger Event TMR1_CC0          */
    HAL_ADC_SEQ_TRIG_EVT_TMR2_CC0        = LL_ADC_SEQ_TRIG_EVT_TMR2_CC0,        /*!< ADC Sequence Trigger Event TMR2_CC0          */
    HAL_ADC_SEQ_TRIG_EVT_TMR0_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR0_TRGO,       /*!< ADC Sequence Trigger Event TMR0_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR1_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR1_TRGO,       /*!< ADC Sequence Trigger Event TMR1_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR2_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR2_TRGO,       /*!< ADC Sequence Trigger Event TMR2_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR3_CC0        = LL_ADC_SEQ_TRIG_EVT_TMR3_CC0,        /*!< ADC Sequence Trigger Event TMR3_CC0          */
    HAL_ADC_SEQ_TRIG_EVT_TMR3_CC1        = LL_ADC_SEQ_TRIG_EVT_TMR3_CC1,        /*!< ADC Sequence Trigger Event TMR3_CC1          */
    HAL_ADC_SEQ_TRIG_EVT_TMR3_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR3_TRGO,       /*!< ADC Sequence Trigger Event TMR3_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR4_CC0        = LL_ADC_SEQ_TRIG_EVT_TMR4_CC0,        /*!< ADC Sequence Trigger Event TMR4_CC0          */
    HAL_ADC_SEQ_TRIG_EVT_TMR4_CC1        = LL_ADC_SEQ_TRIG_EVT_TMR4_CC1,        /*!< ADC Sequence Trigger Event TMR4_CC1          */
    HAL_ADC_SEQ_TRIG_EVT_TMR4_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR4_TRGO,       /*!< ADC Sequence Trigger Event TMR4_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR9_CC0        = LL_ADC_SEQ_TRIG_EVT_TMR9_CC0,        /*!< ADC Sequence Trigger Event TMR9_CC0          */
    HAL_ADC_SEQ_TRIG_EVT_TMR9_CC1        = LL_ADC_SEQ_TRIG_EVT_TMR9_CC1,        /*!< ADC Sequence Trigger Event TMR9_CC1          */
    HAL_ADC_SEQ_TRIG_EVT_TMR9_TRGO       = LL_ADC_SEQ_TRIG_EVT_TMR9_TRGO,       /*!< ADC Sequence Trigger Event TMR9_TRGO         */
    HAL_ADC_SEQ_TRIG_EVT_TMR10_CC0       = LL_ADC_SEQ_TRIG_EVT_TMR10_CC0,       /*!< ADC Sequence Trigger Event TMR10_CC0         */
    HAL_ADC_SEQ_TRIG_EVT_TMR10_CC1       = LL_ADC_SEQ_TRIG_EVT_TMR10_CC1,       /*!< ADC Sequence Trigger Event TMR10_CC1         */
    HAL_ADC_SEQ_TRIG_EVT_TMR10_CC2       = LL_ADC_SEQ_TRIG_EVT_TMR10_CC2,       /*!< ADC Sequence Trigger Event TMR10_CC2         */
    HAL_ADC_SEQ_TRIG_EVT_TMR10_TRGO      = LL_ADC_SEQ_TRIG_EVT_TMR10_TRGO,      /*!< ADC Sequence Trigger Event TMR10_TRGO        */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG0   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG0,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG0     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG1   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG1,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG1     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG2   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG2,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG2     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG3   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG3,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG3     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG4   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG4,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG4     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG5   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG5,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG5     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG6   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG6,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG6     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG7   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG7,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG7     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG8   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG8,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG8     */
    HAL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG9   = LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG9,   /*!< ADC Sequence Trigger Event HRPWM_ADCTRG9     */
    HAL_ADC_SEQ_TRIG_EVT_REG_PA8         = LL_ADC_SEQ_TRIG_EVT_REG_PA8,         /*!< ADC Sequence Trigger Event PA8 (Regular)     */
    HAL_ADC_SEQ_TRIG_EVT_INJ_PA9         = LL_ADC_SEQ_TRIG_EVT_INJ_PA9          /*!< ADC Sequence Trigger Event PA9 (Injected)    */
} HAL_ADC_SeqTrigEvtTypeDef;

/**
  * @brief ADC Calibration Mode Definition
  */
typedef enum
{
    HAL_ADC_CAL_MODE_SINGLE_END  = LL_ADC_CAL_MODE_SINGLE_END,   /*!< ADC Calibration Mode Single-End     */
    HAL_ADC_CAL_MODE_DIFF        = LL_ADC_CAL_MODE_DIFF          /*!< ADC Calibration Mode Differential   */
} HAL_ADC_CalModeTypeDef;

/**
  * @brief ADC Channel Saturation Arithmetic Mode Definition
  */
typedef enum
{
    HAL_ADC_CH_SATURATION_SUPPORT       = LL_ADC_CH_SATURATION_SUPPORT,       /*!< Channel Saturation Arithmetic Support      */
    HAL_ADC_CH_SATURATION_NOT_SUPPORT   = LL_ADC_CH_SATURATION_NOT_SUPPORT    /*!< Channel Saturation Arithmetic Not Support  */
} HAL_ADC_ChSaturationTypeDef;

/**
  * @brief ADC DMA Address Mode Definition Definition
  */
typedef enum
{
    HAL_ADC_DMA_ADDRESS_MODE_FIXED_DISABLE  = 0U,   /*!< DMA Address No Fixed   */
    HAL_ADC_DMA_ADDRESS_MODE_FIXED_ENABLE   = 1U,   /*!< DMA Address Fixed      */
} HAL_ADC_DMAAddrModeTypeDef;

/**
  * @brief ADC DMA Circulation Mode Definition Definition
  */
typedef enum
{
    HAL_ADC_DMA_CIRC_MODE_DISABLE = 0U,   /*!< DMA Circulation Mode Disable */
    HAL_ADC_DMA_CIRC_MODE_ENABLE  = 1U,   /*!< DMA Circulation Mode Enable  */
} HAL_ADC_DMACircModeTypeDef;

/**
  * @brief ADC AWDG Filter Point Numbers Definition
  */
typedef enum
{
    HAL_ADC_AWDG_FILTER_POINT_NONE      = LL_ADC_AWDG_FILTER_POINT_NONE,    /*!< ADC AWDG Filter Point None         */
    HAL_ADC_AWDG_FILTER_POINT_NUM_2     = LL_ADC_AWDG_FILTER_POINT_NUM_2,   /*!< ADC AWDG Filter Point Numbers 2    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_3     = LL_ADC_AWDG_FILTER_POINT_NUM_3,   /*!< ADC AWDG Filter Point Numbers 3    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_4     = LL_ADC_AWDG_FILTER_POINT_NUM_4,   /*!< ADC AWDG Filter Point Numbers 4    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_5     = LL_ADC_AWDG_FILTER_POINT_NUM_5,   /*!< ADC AWDG Filter Point Numbers 5    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_6     = LL_ADC_AWDG_FILTER_POINT_NUM_6,   /*!< ADC AWDG Filter Point Numbers 6    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_7     = LL_ADC_AWDG_FILTER_POINT_NUM_7,   /*!< ADC AWDG Filter Point Numbers 7    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_8     = LL_ADC_AWDG_FILTER_POINT_NUM_8,   /*!< ADC AWDG Filter Point Numbers 8    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_9     = LL_ADC_AWDG_FILTER_POINT_NUM_9,   /*!< ADC AWDG Filter Point Numbers 9    */
    HAL_ADC_AWDG_FILTER_POINT_NUM_10    = LL_ADC_AWDG_FILTER_POINT_NUM_10,  /*!< ADC AWDG Filter Point Numbers 10   */
    HAL_ADC_AWDG_FILTER_POINT_NUM_11    = LL_ADC_AWDG_FILTER_POINT_NUM_11,  /*!< ADC AWDG Filter Point Numbers 11   */
    HAL_ADC_AWDG_FILTER_POINT_NUM_12    = LL_ADC_AWDG_FILTER_POINT_NUM_12,  /*!< ADC AWDG Filter Point Numbers 12   */
    HAL_ADC_AWDG_FILTER_POINT_NUM_13    = LL_ADC_AWDG_FILTER_POINT_NUM_13,  /*!< ADC AWDG Filter Point Numbers 13   */
    HAL_ADC_AWDG_FILTER_POINT_NUM_14    = LL_ADC_AWDG_FILTER_POINT_NUM_14,  /*!< ADC AWDG Filter Point Numbers 14   */
    HAL_ADC_AWDG_FILTER_POINT_NUM_15    = LL_ADC_AWDG_FILTER_POINT_NUM_15,  /*!< ADC AWDG Filter Point Numbers 15   */
    HAL_ADC_AWDG_FILTER_POINT_NUM_16    = LL_ADC_AWDG_FILTER_POINT_NUM_16,  /*!< ADC AWDG Filter Point Numbers 16   */
} HAL_ADC_AWDG_FilterPointNumsTypeDef;

/**
  * @brief ADC AWDG Monitor Mode Definition
  */
typedef enum
{
    HAL_ADC_AWDG_MONITOR_MODE_DISABLE                   = 0U,   /*!< ADC AWDG Monitor Mode Disable                                 */
    HAL_ADC_AWDG_MONITOR_MODE_SINGLE_REGULAR            = 1U,   /*!< ADC AWDG monitor regular group single channel                 */
    HAL_ADC_AWDG_MONITOR_MODE_SINGLE_INJECTED           = 2U,   /*!< ADC AWDG monitor injected group single channel                */
    HAL_ADC_AWDG_MONITOR_MODE_SINGLE_REGULAR_INJECTED   = 3U,   /*!< ADC AWDG monitor regular and injected group single channel    */
    HAL_ADC_AWDG_MONITOR_MODE_ALL_REGULAR               = 4U,   /*!< ADC AWDG monitor regular group all channel                    */
    HAL_ADC_AWDG_MONITOR_MODE_ALL_INJECTED              = 5U,   /*!< ADC AWDG monitor injected group all channel                   */
    HAL_ADC_AWDG_MONITOR_MODE_ALL_REGULAR_INJECTED      = 6U,   /*!< ADC AWDG monitor regular and injected group all channel       */
    HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_REGULAR            = 7U,   /*!< ADC AWDG monitor regular and injected group multiple channel  */
    HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_INJECTED           = 8U,   /*!< ADC AWDG monitor regular and injected group multiple channel  */
    HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_REGULAR_INJECTED   = 9U    /*!< ADC AWDG monitor regular and injected group multiple channel  */
} HAL_ADC_AWDG_MonitorModeTypeDef;

/**
  * @brief HAL ADC Sampling Mode
  */
typedef enum
{
    HAL_ADC_SAMP_MODE_OVER_SAMP_DISABLE        = 0U,   /*!< ADC oversampling disabled.                                             */
    HAL_ADC_SAMP_MODE_REG_CONTINUED            = 1U,   /*!< ADC oversampling on conversions of ADC group regular in continued mode */
    HAL_ADC_SAMP_MODE_REG_RESUMED              = 2U,   /*!< ADC oversampling on conversions of ADC group regular in resumed mode.  */
    HAL_ADC_SAMP_MODE_TRIGGERED_REG_RESUMED    = 3U,   /*!< ADC oversampling on conversions of ADC group regular in triggered.     */
    HAL_ADC_SAMP_MODE_INJ_REG_RESUMED          = 4U,   /*!< ADC oversampling on conversions of ADC groups regular and injected.    */
    HAL_ADC_SAMP_MODE_INJ                      = 5U    /*!< ADC oversampling on conversions of ADC group injected.                 */
} HAL_SamplingModeTypeDef;


/**
  * @brief  Structure definition of ADC instance and ADC group regular.
  */
typedef struct
{
#if 0///TODO: FOR FUTURE
    int16_t                 CalibFactorOffset;  /*!< [RESERVED] Calibration Factor Offset (Default Value: 0x0000) */
    uint16_t                CalibFactorGain;    /*!< [RESERVED] Calibration Factor Gain   (Default Value: 0x2000) */
#endif
    HAL_ADC_DualModeTypeDef DualMode;           /*!< ADC Dual Mode (Default Value: HAL_ADC_MODE_INDEPEND)         */
    uint16_t                DualPhaseDelay;     /*!< ADC Dual Sample Phase Delay (Range: 0~1023,Default Value: 0) */
} HAL_ADC_InitTypeDef;

/**
  * @brief  ADC group regular and ADC channel affected to ADC group regular configuration definition
  */
typedef struct
{
  HAL_ADC_SeqTrigEvtTypeDef           ExternalTrigConv;       /*!< Select the external event source used to trigger ADC group regular conversion start.*/
  HAL_ADC_SeqTrigPolTypeDef           ExternalTrigConvEdge;   /*!< Select the external event edge used to trigger ADC group regular conversion start */
  HAL_ADC_REG_SeqLenTypeDef           NbrOfConversion;        /*!< Specify the number of ranks that will be converted within the regular group sequencer. */
  HAL_ADC_REG_DisContConvNumTypeDef   NbrOfDiscConversion;    /*!< Specifies the number of discontinuous conversions in which the main sequence
                                                                  of ADC group regular (parameter NbrOfConversion) will be subdivided. */
  HAL_ADC_REG_ConvModeTypeDef         ContinuousConvMode;     /*!< Specify whether the conversion is performed in single mode (one conversion)
                                                                  or continuous mode for ADC group regular, after the first ADC conversion
                                                                  start trigger occurred (software start or external trigger). */
  HAL_ADC_DiscontConvTypeDef          DiscontinuousConvMode;  /*!< Specify whether the conversions sequence of ADC group regular is performed
                                                                  in Complete-sequence/Discontinuous-sequence (main sequence subdivided in
                                                                  successive parts). */
  HAL_ADC_OverRunModeTypeDef          Overrun;                /*!< Select the behavior in case of overrun: data overwritten or preserved (default). */

} HAL_ADC_RegularConfTypeDef;


/**
  * @brief  ADC group injected and ADC channel affected to ADC group injected configuration definition
  */
typedef struct
{
  HAL_ADC_SeqTrigEvtTypeDef     ExternalTrigInjecConv;          /*!< Selects the external event used to trigger the conversion start of
                                                                    injected group. */

  HAL_ADC_SeqTrigPolTypeDef     ExternalTrigInjecConvEdge;      /*!< Selects the external trigger edge of injected group.*/

  HAL_ADC_INJ_SeqLenTypeDef     InjectedNbrOfConversion;        /*!< Specifies the number of ranks that will be converted within the ADC group
                                                                    injected sequencer.*/
  HAL_ADC_DiscontConvTypeDef    InjectedDiscontinuousConvMode;  /*!< Specifies whether the conversions sequence of ADC group injected
                                                                    is performed in Complete-sequence/Discontinuous-sequence . */
  HAL_ADC_INJ_ConvModeTypeDef   AutoInjectedConv;               /*!< Enables or disables the selected ADC group injected automatic conversion
                                                                    after regular one  */

} HAL_ADC_InjectionConfTypeDef;

/**
  * @brief  ADC group regular/injected oversampling configuration definition
  */
typedef struct
{
    HAL_ADC_OverSampRatioTypeDef    Ratio;              /*!< Configures the oversampling ratio.                         */
    HAL_ADC_OverSampShiftTypeDef    RightBitShift;      /*!< Configures the division coefficient for the Oversampler.   */
    HAL_SamplingModeTypeDef         OversamplingMode;   /*!< Selects the regular/injected oversampling mode.            */
} HAL_ADC_OversampConfTypeDef;

/**
  * @brief  ADC channel for regular/injected group configuration definition
  */
typedef struct
{
    HAL_ADC_ChTypeDef               Channel;                /*!< Specify the channel to configure into ADC regular/injected group. */
    uint8_t                         Rank;                   /*!< Specify the rank in the regular/injected group sequencer. */
    HAL_ADC_SampTimeTypeDef         SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                                                Unit: ADC clock cycles */
    HAL_ADC_InputModeTypeDef        SingleDiff;             /*!< Select single-ended or differential input. */
    HAL_ADC_EnableTypeDef           AssignDiffChannel1;     /*!< Set channel[i+1] as the paired differential input.
                                                                    In differential mode, the voltage difference between channel 'i'
                                                                (positive input) and channel 'i+1' (negative input) is measured.
                                                                Only channel 'i' needs to be programmed; channel 'i+1' is configured
                                                                automatically.
                                                                Caution: This parameter applies to a channel that may be used in the
                                                                    regular and/or injected group. It overrides the previous setting.
                                                                Note: Consult the Reference Manual to confirm the selected channel is
                                                                    available for differential operation.
                                                                Note: When channel 'i' is configured for differential mode, channel 'i+1'
                                                                    cannot be used as an independent channel.
                                                                Note: This parameter must be changed while the ADC is disabled (i.e.,
                                                                    before starting a conversion or after stopping it). */
    HAL_ADC_EnableTypeDef           SamplingCompleteIT;     /*!< Channel Data Sampling Interrupt Enable */

} HAL_ADC_ChannelConfTypeDef;

/**
  * @brief  ADC analog watchdog configuration definition
  */
typedef struct
{
    HAL_ADC_AWDG_NumTypeDef                 WatchdogNumber;    /*!< Select which ADC analog watchdog is monitoring the selected channel. */
    HAL_ADC_AWDG_MonitorModeTypeDef         WatchdogMode;      /*!< Configure the ADC analog watchdog mode: none/single/all/any channels. */
    HAL_ADC_ChTypeDef                       Channel;           /*!< Select which ADC channel to monitor by analog watchdog.  */
    int16_t                                 HighThreshold;     /*!< Configure the ADC analog watchdog High threshold value. */
    int16_t                                 LowThreshold;      /*!< Configures the ADC analog watchdog Low threshold value. */
    HAL_ADC_AWDG_FilterPointNumsTypeDef     FilteringConfig;   /*!< Specify whether filtering should be use and the number of samples to consider.
                                                                    Before setting flag or raising interrupt, analog watchdog can wait to have several
                                                                    consecutive out-of-window samples. */
} HAL_ADC_AnalogWDGConfTypeDef;


/**
  * @brief ADC Independent DMA Configuration Definition
  */
typedef struct
{
    HAL_ADC_ChTypeDef           Channel;            /*!< Specify the channel to configure into ADC Independent DMA. */
    HAL_ADC_DMACircModeTypeDef  Circulation;        /*!< Specify the DMA circulation Enable                         */
    HAL_ADC_DMAAddrModeTypeDef  FixAddress;         /*!< DMA Fix Address Enable                                     */
    uint32_t                    BufferAddress;      /*!< DMA Transfer Buffer Address                                */
    uint16_t                    BufferInHalfWords;  /*!< DMA Transfer Buffer/Sequence Length (Unit: Half Word)      */
    HAL_ADC_EnableTypeDef       HalfCompleteIT;     /*!< DMA Half Complete Interrupt Enable                         */
    HAL_ADC_EnableTypeDef       CompleteIT;         /*!< DMA Complete Interrupt Enable                              */
} HAL_ADC_IndepDMAConfTypeDef;

/**
  * @brief ADC Calibration Configuration Definition
  */
typedef struct 
{
    HAL_ADC_ChTypeDef             Channel;            /*!< ADC channel with related conversion data to be processed */
    HAL_ADC_CalCoefGrpTypeDef     CoefficientGroup;   /*!< Calibration Coefficient Group */
    int16_t                       OffsetCompensation; /*!< Specify the offset compensation to be applied on the raw converted data. */
    uint16_t                      GainCompensation;   /*!< Specify the gain compensation to be applied to raw conversion data */
    HAL_ADC_ChSaturationTypeDef   Saturation;         /*!< Define if the offset should be saturated upon under or over flow.  */
} HAL_ADC_CalibrationConfTypeDef;

/**
  * @brief ADC Calibration Coefficient Group Definition
  */
typedef struct 
{
    int16_t                       OffsetCompensation; /*!< Specify the offset compensation to be applied on the raw converted data. */
    uint16_t                      GainCompensation;   /*!< Specify the gain compensation to be applied to raw conversion data */
} HAL_ADC_CaliCoefGrpConfTypeDef;

/**
  * @brief ADC Calibration Channel Definition
  */
typedef struct 
{
    HAL_ADC_CalCoefGrpTypeDef     CoefficientGroup;   /*!< Calibration Coefficient Group */
    HAL_ADC_ChSaturationTypeDef   Saturation;         /*!< Define if the offset should be saturated upon under or over flow.  */
} HAL_ADC_ChannelCaliConfTypeDef;

/**
  * @brief ADC Auto-calibration Configuration Definition
  */
typedef struct 
{
    HAL_ADC_CalModeTypeDef        Mode;               /*!< Auto-calibration Mode                */
    HAL_ADC_OverSampRatioTypeDef  OversamplingRatio;  /*!< Auto-calibration oversampling Ratio  */
} HAL_ADC_AutoCaliConfTypeDef;



/** @brief HAL ADC handle structure type */
typedef struct HAL_ADC_HandleStructDef HAL_ADC_HandleTypeDef; 

/** @brief ADC IRQ callback function type definition */
typedef void (*HAL_ADC_IRQCallback)(HAL_ADC_HandleTypeDef *Handle);

/**
  * @brief  ADC Handle Structure definition
  */
struct HAL_ADC_HandleStructDef
{
    ADC_TypeDef                         *Instance;          /*!< Register base address      */
    volatile HAL_ADC_StateTypeDef       State;              /*!< Global state               */
    volatile HAL_ADC_GrpStateTypeDef    RegGrpState;        /*!< Regular group state        */
    volatile HAL_ADC_GrpStateTypeDef    InjGrpState;        /*!< Injected group state       */
    volatile HAL_ADC_GrpConvTypeDef     RegGrpConv;         /*!< Regular group conversions  */
    volatile HAL_ADC_GrpConvTypeDef     InjGrpConv;         /*!< Injected group conversions */
    volatile HAL_ADC_ErrCodeMskTypeDef  LastErrorCodes;     /*!< Last error codes           */
    const void                          *pUserData;         /*!< User data pointer          */
};


/**
  * @}
  */ /* ADC_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup ADC_HAL_Exported_Functions
  * @{
  */

/** @addtogroup ADC_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_ADC_Init(HAL_ADC_HandleTypeDef *Handle, 
                               ADC_TypeDef *ADCx, 
                               HAL_ADC_InitTypeDef *pInit);

HAL_StatusTypeDef HAL_ADC_DeInit(HAL_ADC_HandleTypeDef *Handle);

void HAL_ADC_MspInit(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_MspDeInit(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_IoInit(ADC_TypeDef *ADCx);
void HAL_ADC_IoDeInit(ADC_TypeDef *ADCx);
/**
  * @}
  */ /* ADC_HAL_EF_Initialization */


/** @addtogroup ADC_HAL_EF_Configuration
  * @{
  */

HAL_StatusTypeDef HAL_ADC_OverSamplingConfig(HAL_ADC_HandleTypeDef *Handle, 
                                             const HAL_ADC_OversampConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_RegularConfig(HAL_ADC_HandleTypeDef *Handle, 
                                        const HAL_ADC_RegularConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_InjectedConfig(HAL_ADC_HandleTypeDef *Handle, 
                                         const HAL_ADC_InjectionConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_ChannelConfig(HAL_ADC_HandleTypeDef *Handle, 
                                        HAL_ADC_SampGrpTypeDef Group, 
                                        const HAL_ADC_ChannelConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_IndependentDMAConfig(HAL_ADC_HandleTypeDef *Handle, 
                                               const HAL_ADC_IndepDMAConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_CalibrationConfig(HAL_ADC_HandleTypeDef *Handle, 
                                            const HAL_ADC_CalibrationConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_CalibrationCoefficientGroupConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                            HAL_ADC_CalCoefGrpTypeDef Group,
                                                            const HAL_ADC_CaliCoefGrpConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_ChannelCalibrationConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                   HAL_ADC_ChTypeDef Channel,
                                                   const HAL_ADC_ChannelCaliConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_AutoCalibrationConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                const HAL_ADC_AutoCaliConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(HAL_ADC_HandleTypeDef *Handle, 
                                          const HAL_ADC_AnalogWDGConfTypeDef *pCfg);

HAL_StatusTypeDef HAL_ADC_BiasCurrentConfig(HAL_ADC_HandleTypeDef *Handle, 
                                            HAL_ADC_BiasCurTypeDef Current);

HAL_StatusTypeDef HAL_ADC_SaturationThresholdsConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                     HAL_ADC_SampGrpTypeDef Group,
                                                     int16_t Minimum, 
                                                     int16_t Maximum);
/**
  * @}
  */ /* ADC_HAL_EF_Configuration */

/** @addtogroup ADC_HAL_EF_Operation
  * @{
  */
HAL_StatusTypeDef HAL_ADC_Start(HAL_ADC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADC_Stop(HAL_ADC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_ADC_RegularStartConv(HAL_ADC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADC_RegularStartNextConv(HAL_ADC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADC_RegularStopConv(HAL_ADC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_ADC_RegularStartConv_IT(HAL_ADC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADC_RegularStopConv_IT(HAL_ADC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_ADC_InjectedStartConv(HAL_ADC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADC_InjectedStartNextConv(HAL_ADC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADC_InjectedStopConv(HAL_ADC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_ADC_InjectedStartConv_IT(HAL_ADC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_ADC_InjectedStopConv_IT(HAL_ADC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_ADC_AutoCalibration(HAL_ADC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_ADC_PollForEvent(HAL_ADC_HandleTypeDef *Handle,
                                       HAL_ADC_ITPendingMskTypeDef EventType,
                                       uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_PollForRegularConversion(HAL_ADC_HandleTypeDef *Handle, 
                                                   uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_PollForInjectedConversion(HAL_ADC_HandleTypeDef *Handle, 
                                                    uint32_t Timeout);

uint16_t HAL_ADC_GetValue(const HAL_ADC_HandleTypeDef *Handle);
uint16_t HAL_ADC_RegularGetValue(const HAL_ADC_HandleTypeDef *Handle, 
                                 HAL_ADC_ChTypeDef Channel);

uint16_t HAL_ADC_InjectedGetValue(const HAL_ADC_HandleTypeDef *Handle, 
                                  HAL_ADC_INJ_SeqNumTypeDef Number);

HAL_StatusTypeDef HAL_ADC_ChannelDMAStart(HAL_ADC_HandleTypeDef *Handle, 
                                          HAL_ADC_ChTypeDef Channel);

HAL_StatusTypeDef HAL_ADC_ChannelDMAStop(HAL_ADC_HandleTypeDef *Handle, 
                                         HAL_ADC_ChTypeDef Channel);

HAL_StatusTypeDef HAL_ADC_GetDMAStatus(HAL_ADC_HandleTypeDef *Handle, 
                                       HAL_ADC_ChTypeDef Channel);

uint16_t HAL_ADC_GetMasterChannelValue(const HAL_ADC_HandleTypeDef *Handle);
uint16_t HAL_ADC_GetSlaveChannelValue(const HAL_ADC_HandleTypeDef *Handle);
/**
  * @}
  */ /* ADC_HAL_EF_Operation */


/** @addtogroup ADC_HAL_EF_Interrupt
  * @{
  */

HAL_StatusTypeDef HAL_ADC_InterruptRequestEnable(HAL_ADC_HandleTypeDef *Handle,
                                                 HAL_ADC_ITEnMskTypeDef InterruptRequests);

HAL_StatusTypeDef HAL_ADC_InterruptRequestDisable(HAL_ADC_HandleTypeDef *Handle,
                                                  HAL_ADC_ITEnMskTypeDef InterruptRequests);

HAL_StatusTypeDef HAL_ADC_InterruptFlagClear(HAL_ADC_HandleTypeDef *Handle,
                                             HAL_ADC_ITPendingMskTypeDef InterruptFlag);

/** NORM ISR */
void HAL_ADC_NORM_IRQHandler(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_EndOfSamplingCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_ReadyCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_AWDG2Callback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_AWDG1Callback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_AWDG0Callback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_OverflowCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_EndOfInjectedSeqCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_EndOfInjectedConvCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_EndOfRegularSeqCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_NORM_EndOfRegularConvCallback(HAL_ADC_HandleTypeDef *Handle);

/** SAMP ISR */
void HAL_ADC_SAMP_ChannelIRQHandler(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel);
void HAL_ADC_SAMP_ChConvDoneCallback(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel);

/** HALF ISR */
void HAL_ADC_DMA_ChHalfCpltIRQHandler(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel);
void HAL_ADC_DMA_ChHalfCpltCallback(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel);

/** FULL ISR */
void HAL_ADC_DMA_ChCpltIRQHandler(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel);
void HAL_ADC_DMA_ChCpltCallback(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel);

/** SAMP ISR : CHANNEL SCAN */
void HAL_ADC_SAMP_IRQHandler(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch0ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch1ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch2ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch3ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch4ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch5ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch6ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch7ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch8ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch9ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch10ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch11ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch12ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch13ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch14ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch15ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch16ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch17ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch18ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_SAMP_Ch19ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle);

/** HALF ISR : CHANNEL SCAN */
void HAL_ADC_DMA_HalfCpltIRQHandler(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch0HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch1HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch2HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch3HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch4HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch5HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch6HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch7HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch8HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch9HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch10HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch11HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch12HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch13HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch14HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch15HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch16HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch17HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch18HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch19HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle);

/** FULL ISR : CHANNEL SCAN  */
void HAL_ADC_DMA_CpltIRQHandler(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch0CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch1CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch2CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch3CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch4CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch5CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch6CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch7CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch8CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch9CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch10CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch11CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch12CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch13CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch14CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch15CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch16CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch17CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch18CpltCallback(HAL_ADC_HandleTypeDef *Handle);
void HAL_ADC_DMA_Ch19CpltCallback(HAL_ADC_HandleTypeDef *Handle);
/**
  * @}
  */ /* ADC_HAL_EF_Interrupt */

/**
  * @}
  */ /* ADC_HAL_Exported_Functions */


/**
  * @}
  */ /* ADC_HAL */

#endif /* HAL_ADC_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* ADC */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_ADC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

