/**
  ******************************************************************************
  * @file    tae32g58xx_hal_can.h
  * @author  Tai-Action SD Team
  * @brief   Header file for CAN HAL module
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
#ifndef _TAE32G58XX_HAL_CAN_H_
#define _TAE32G58XX_HAL_CAN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_can.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(CAN0) || defined(CAN1)

/** @addtogroup CAN_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup CAN_HAL_Exported_Constants CAN HAL Exported Constants
  * @brief    CAN HAL Exported Constants
  * @{
  */

/** @defgroup HAL_CAN_EC_Information HAL CAN Information
  * @brief    CAN HAL Information
  * @{
  */
/**
  * @brief CAN 2.0 Max Data Length Definition
  */
#define HAL_CAN_20_DAT_LEN_MAX      LL_CAN_20_DAT_LEN_MAX

/**
  * @brief CAN FD Max Data Length Definition
  */
#define HAL_CAN_FD_DAT_LEN_MAX      LL_CAN_FD_DAT_LEN_MAX

/**
  * @brief CAN Data Length Range Definition
  */
#define HAL_CAN_DAT_LEN_RANGE       (LL_CAN_FD_DAT_LEN_MAX + 1)

/**
  * @}
  */ /* HAL_CAN_EC_Information */


/** @defgroup HAL_CAN_EC_Error_Code HAL CAN Error Code
  * @brief    CAN HAL Error Code
  * @{
  */

/** @name HAL_CAN_ErrCodeMskTypeDef
  * @brief  HAL CAN Error Code Mask definition.
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_CAN_ErrCodeMskTypeDef                           uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_CAN_ErrCodeMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_CAN_ERROR_NONE                                  (0U)                                               /*!< No error                 */
#define HAL_CAN_ERROR_BUS_OFF                               (LL_CAN_INTRST_EIF)                                /*!< Bus-off                  */
#define HAL_CAN_ERROR_PASSIVE                               (LL_CAN_INTRST_EPIF)                               /*!< Error Passive            */
#define HAL_CAN_ERROR_ARB_LOST                              (LL_CAN_INTRST_ALIF)                               /*!< Arbitration Lost         */
#define HAL_CAN_ERROR_BUS                                   (LL_CAN_INTRST_BEIF)                               /*!< Bus Error                */
#define HAL_CAN_ERROR_COUNTER                               (LL_CAN_INTRST_ECIF)                               /*!< Error Counter            */
/** @} */

/**
  * @}
  */ /* HAL_CAN_EC_Error_Code */


/** @defgroup CAN_HAL_EM_Mask CAN HAL Mask
  * @brief    CAN HAL Mask
  * @{
  */

/** @name HAL_CAN_ITEnMskTypeDef
  * @brief CAN Interrupt Enable Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_CAN_ITEnMskTypeDef                              LL_CAN_INTREN_ITEnMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_CAN_INTREN_ITEnMskTypeDef HAL_CAN_ITEnMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_CAN_INTREN_STB_EMPTY_IT_EN                      LL_CAN_INTREN_TEIE                                 /*!< TEIE Mask                */
#define HAL_CAN_INTREN_STB_ALMOST_EMPTY_IT_EN               LL_CAN_INTREN_TAEIE                                /*!< TAEIE Mask               */
#define HAL_CAN_INTREN_PRIORITY_MESSAGE_IT_EN               LL_CAN_INTREN_PMIE                                 /*!< PMIE Mask                */
#define HAL_CAN_INTREN_TIMESTAMP_IT_EN                      LL_CAN_INTREN_TSCIE                                /*!< TSCIE Mask               */
#define HAL_CAN_INTREN_PRB_TIMEOUT_IT_EN                    LL_CAN_INTREN_RTOIE                                /*!< RTOIE Mask               */
#define HAL_CAN_INTREN_SRB_TIMEOUT_IT_EN                    LL_CAN_INTREN_STOIE                                /*!< STOIE Mask               */
#define HAL_CAN_INTREN_ETB_TIMEOUT_IT_EN                    LL_CAN_INTREN_ETOIE                                /*!< ETOIE Mask               */
#define HAL_CAN_INTREN_CONTINUE_TIMEOUT_IT_EN               LL_CAN_INTREN_CTOIE                                /*!< CTOIE Mask               */
#define HAL_CAN_INTREN_SRB_OVERRUN_IT_EN                    LL_CAN_INTREN_SOIE                                 /*!< SOIE Mask                */
#define HAL_CAN_INTREN_SRB_FULL_IT_EN                       LL_CAN_INTREN_SFIE                                 /*!< SFIE Mask                */
#define HAL_CAN_INTREN_SRB_ALMOST_FULL_IT_EN                LL_CAN_INTREN_SAFIE                                /*!< SAFIE Mask               */
#define HAL_CAN_INTREN_ETB_OVERRUN_IT_EN                    LL_CAN_INTREN_EOIE                                 /*!< EOIE Mask                */
#define HAL_CAN_INTREN_ETB_FULL_IT_EN                       LL_CAN_INTREN_EFIE                                 /*!< EFIE Mask                */
#define HAL_CAN_INTREN_ETB_ALMOST_FULL_IT_EN                LL_CAN_INTREN_EAFIE                                /*!< EAFIE Mask               */
#define HAL_CAN_INTREN_ABORT_IT_EN_SP                       LL_CAN_INTREN_AIE_SP                               /*!< AIE Mask                 */
#define HAL_CAN_INTREN_SRB_RX_IT_EN                         LL_CAN_INTREN_SRIE                                 /*!< SRIE Mask                */
#define HAL_CAN_INTREN_ETB_RX_IT_EN                         LL_CAN_INTREN_ERIE                                 /*!< ERIE Mask                */
#define HAL_CAN_INTREN_ERROR_COUNTER_IT_EN                  LL_CAN_INTREN_ECIE                                 /*!< ECIE Mask                */
#define HAL_CAN_INTREN_ERROR_PASSIVE_IT_EN                  LL_CAN_INTREN_EPIE                                 /*!< EPIE Mask                */
#define HAL_CAN_INTREN_ARBITRATION_LOST_IT_EN               LL_CAN_INTREN_ALIE                                 /*!< ALIE Mask                */
#define HAL_CAN_INTREN_BUS_ERROR_IT_EN                      LL_CAN_INTREN_BEIE                                 /*!< BEIE Mask                */
#define HAL_CAN_INTREN_PRB_RX_IT_EN                         LL_CAN_INTREN_RIE                                  /*!< RIE Mask                 */
#define HAL_CAN_INTREN_PRB_OVERRUN_IT_EN                    LL_CAN_INTREN_ROIE                                 /*!< ROIE Mask                */
#define HAL_CAN_INTREN_PRB_FULL_IT_EN                       LL_CAN_INTREN_RFIE                                 /*!< RFIE Mask                */
#define HAL_CAN_INTREN_PRB_ALMOST_FULL_IT_EN                LL_CAN_INTREN_RAFIE                                /*!< RAFIE Mask               */
#define HAL_CAN_INTREN_PTB_TX_IT_EN                         LL_CAN_INTREN_TPIE                                 /*!< TPIE Mask                */
#define HAL_CAN_INTREN_STB_TX_IT_EN                         LL_CAN_INTREN_TSIE                                 /*!< TSIE Mask                */
#define HAL_CAN_INTREN_BUS_OFF_IT_EN                        LL_CAN_INTREN_EIE                                  /*!< EIE Mask                 */
/** @} */

/** @name HAL_CAN_ITPendingMskTypeDef
  * @brief CAN Interrupt Pending Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_CAN_ITPendingMskTypeDef                         LL_CAN_INTRST_ITPendingMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_CAN_INTRST_ITPendingMskTypeDef HAL_CAN_ITPendingMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_CAN_INTRST_STB_EMPTY_IT_FLAG                    LL_CAN_INTRST_TEIF                                 /*!< TEIF Mask                */
#define HAL_CAN_INTRST_STB_ALMOST_EMPTY_IT_FLAG             LL_CAN_INTRST_TAEIF                                /*!< TAEIF Mask               */
#define HAL_CAN_INTRST_PRIORITY_MESSAGE_IT_FLAG             LL_CAN_INTRST_PMIF                                 /*!< PMIF Mask                */
#define HAL_CAN_INTRST_TIMESTAMP_IT_FLAG                    LL_CAN_INTRST_TSCIF                                /*!< TSCIF Mask               */
#define HAL_CAN_INTRST_PRB_TIMEOUT_IT_FLAG                  LL_CAN_INTRST_RTOIF                                /*!< RTOIF Mask               */
#define HAL_CAN_INTRST_SRB_TIMEOUT_IT_FLAG                  LL_CAN_INTRST_STOIF                                /*!< STOIF Mask               */
#define HAL_CAN_INTRST_ETB_TIMEOUT_IT_FLAG                  LL_CAN_INTRST_ETOIF                                /*!< ETOIF Mask               */
#define HAL_CAN_INTRST_CONTINUE_TIMEOUT_IT_FLAG             LL_CAN_INTRST_CTOIF                                /*!< CTOIF Mask               */
#define HAL_CAN_INTRST_SRB_OVERRUN_IT_FLAG                  LL_CAN_INTRST_SOIF                                 /*!< SOIF Mask                */
#define HAL_CAN_INTRST_SRB_FULL_IT_FLAG                     LL_CAN_INTRST_SFIF                                 /*!< SFIF Mask                */
#define HAL_CAN_INTRST_SRB_ALMOST_FULL_IT_FLAG              LL_CAN_INTRST_SAFIF                                /*!< SAFIF Mask               */
#define HAL_CAN_INTRST_ETB_OVERRUN_IT_FLAG                  LL_CAN_INTRST_EOIF                                 /*!< EOIF Mask                */
#define HAL_CAN_INTRST_ETB_FULL_IT_FLAG                     LL_CAN_INTRST_EFIF                                 /*!< EFIF Mask                */
#define HAL_CAN_INTRST_ETB_ALMOST_FULL_IT_FLAG              LL_CAN_INTRST_EAFIF                                /*!< EAFIF Mask               */
#define HAL_CAN_INTRST_ERROR_WARNING_LIMIT_STATE_FLAG       LL_CAN_INTRST_EWARN_SP                             /*!< EWARN Mask               */
#define HAL_CAN_INTRST_ERROR_PASSIVE_ACTIVE_STATE_FLAG      LL_CAN_INTRST_EPASS_SP                             /*!< EPASS Mask               */
#define HAL_CAN_INTRST_SRB_RX_IT_FLAG                       LL_CAN_INTRST_SRIF                                 /*!< SRIF Mask                */
#define HAL_CAN_INTRST_ETB_RX_IT_FLAG                       LL_CAN_INTRST_ERIF                                 /*!< ERIF Mask                */
#define HAL_CAN_INTRST_ERROR_COUNTER_IT_FLAG                LL_CAN_INTRST_ECIF                                 /*!< ECIF Mask                */
#define HAL_CAN_INTRST_ERROR_PASSIVE_IT_FLAG                LL_CAN_INTRST_EPIF                                 /*!< EPIF Mask                */
#define HAL_CAN_INTRST_ARBITRATION_LOST_IT_FLAG             LL_CAN_INTRST_ALIF                                 /*!< ALIF Mask                */
#define HAL_CAN_INTRST_BUS_ERROR_IT_FLAG                    LL_CAN_INTRST_BEIF                                 /*!< BEIF Mask                */
#define HAL_CAN_INTRST_PRB_RX_IT_FLAG                       LL_CAN_INTRST_RIF                                  /*!< RIF Mask                 */
#define HAL_CAN_INTRST_PRB_OVERRUN_IT_FLAG                  LL_CAN_INTRST_ROIF                                 /*!< ROIF Mask                */
#define HAL_CAN_INTRST_PRB_FULL_IT_FLAG                     LL_CAN_INTRST_RFIF                                 /*!< RFIF Mask                */
#define HAL_CAN_INTRST_PRB_ALMOST_FULL_IT_FLAG              LL_CAN_INTRST_RAFIF                                /*!< RAFIF Mask               */
#define HAL_CAN_INTRST_PTB_TX_IT_FLAG                       LL_CAN_INTRST_TPIF                                 /*!< TPIF Mask                */
#define HAL_CAN_INTRST_STB_TX_IT_FLAG                       LL_CAN_INTRST_TSIF                                 /*!< TSIF Mask                */
#define HAL_CAN_INTRST_BUS_OFF_IT_FLAG                      LL_CAN_INTRST_EIF                                  /*!< EIF Mask                 */
#define HAL_CAN_INTRST_ABORT_IT_FLAG_SP                     LL_CAN_INTRST_AIF_SP                               /*!< AIF Mask                 */
/** @} */

/** @name HAL_CAN_ITLineMskTypeDef
  * @brief HAL CAN Interrupt Line Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_CAN_ITLineMskTypeDef                            LL_CAN_INTRLS_ITLineMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_CAN_INTRLS_ITLineMskTypeDef HAL_CAN_ITLineMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_CAN_INTRLS_STB_EMPTY_IT_LINE                    LL_CAN_INTRLS_TEILS                                /*!< TEILS Mask               */
#define HAL_CAN_INTRLS_STB_ALMOST_EMPTY_IT_LINE             LL_CAN_INTRLS_TAEILS                               /*!< TAEILS Mask              */
#define HAL_CAN_INTRLS_PRIORITY_MESSAGE_IT_LINE             LL_CAN_INTRLS_PMILS                                /*!< PMILS Mask               */
#define HAL_CAN_INTRLS_TIMESTAMP_IT_LINE                    LL_CAN_INTRLS_TSCILS                               /*!< TSCILS Mask              */
#define HAL_CAN_INTRLS_PRB_TIMEOUT_IT_LINE                  LL_CAN_INTRLS_RTOILS                               /*!< RTOILS Mask              */
#define HAL_CAN_INTRLS_SRB_TIMEOUT_IT_LINE                  LL_CAN_INTRLS_STOILS                               /*!< STOILS Mask              */
#define HAL_CAN_INTRLS_ETB_TIMEOUT_IT_LINE                  LL_CAN_INTRLS_ETOILS                               /*!< ETOILS Mask              */
#define HAL_CAN_INTRLS_CONTINUE_TIMEOUT_IT_LINE             LL_CAN_INTRLS_CTOILS                               /*!< CTOILS Mask              */
#define HAL_CAN_INTRLS_SRB_OVERRUN_IT_LINE                  LL_CAN_INTRLS_SOILS                                /*!< SOILS Mask               */
#define HAL_CAN_INTRLS_SRB_FULL_IT_LINE                     LL_CAN_INTRLS_SFILS                                /*!< SFILS Mask               */
#define HAL_CAN_INTRLS_SRB_ALMOST_FULL_IT_LINE              LL_CAN_INTRLS_SAFILS                               /*!< SAFILS Mask              */
#define HAL_CAN_INTRLS_ETB_OVERRUN_IT_LINE                  LL_CAN_INTRLS_EOILS                                /*!< EOILS Mask               */
#define HAL_CAN_INTRLS_ETB_FULL_IT_LINE                     LL_CAN_INTRLS_EFILS                                /*!< EFILS Mask               */
#define HAL_CAN_INTRLS_ETB_ALMOST_FULL_IT_LINE              LL_CAN_INTRLS_EAFILS                               /*!< EAFILS Mask              */
#define HAL_CAN_INTRLS_SRB_RX_IT_LINE                       LL_CAN_INTRLS_SRILS                                /*!< SRILS Mask               */
#define HAL_CAN_INTRLS_ETB_RX_IT_LINE                       LL_CAN_INTRLS_ERILS                                /*!< ERILS Mask               */
#define HAL_CAN_INTRLS_ERROR_COUNTER_IT_LINE                LL_CAN_INTRLS_ECILS                                /*!< ECILS Mask               */
#define HAL_CAN_INTRLS_ERROR_PASSIVE_IT_LINE                LL_CAN_INTRLS_EPILS                                /*!< EPILS Mask               */
#define HAL_CAN_INTRLS_ARBITRATION_LOST_IT_LINE             LL_CAN_INTRLS_ALILS                                /*!< ALILS Mask               */
#define HAL_CAN_INTRLS_BUS_ERROR_IT_LINE                    LL_CAN_INTRLS_BEILS                                /*!< BEILS Mask               */
#define HAL_CAN_INTRLS_PRB_RX_IT_LINE                       LL_CAN_INTRLS_RILS                                 /*!< RILS Mask                */
#define HAL_CAN_INTRLS_PRB_OVERRUN_IT_LINE                  LL_CAN_INTRLS_ROILS                                /*!< ROILS Mask               */
#define HAL_CAN_INTRLS_PRB_FULL_IT_LINE                     LL_CAN_INTRLS_RFILS                                /*!< RFILS Mask               */
#define HAL_CAN_INTRLS_PRB_ALMOST_FULL_IT_LINE              LL_CAN_INTRLS_RAFILS                               /*!< RAFILS Mask              */
#define HAL_CAN_INTRLS_PTB_TX_IT_LINE                       LL_CAN_INTRLS_TPILS                                /*!< TPILS Mask               */
#define HAL_CAN_INTRLS_STB_TX_IT_LINE                       LL_CAN_INTRLS_TSILS                                /*!< TSILS Mask               */
#define HAL_CAN_INTRLS_BUS_OFF_IT_LINE                      LL_CAN_INTRLS_EILS                                 /*!< EILS Mask                */
#define HAL_CAN_INTRLS_ABORT_IT_LINE_SP                     LL_CAN_INTRLS_AILS                                 /*!< AILS Mask                */
/** @} */

/** @name HAL_CAN_StateMaskTypeDef
  * @brief CAN State definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_CAN_StateMaskTypeDef                            uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_CAN_StateMaskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_CAN_STATE_MASK_RESET                            (0U)            /*!< CAN Not yet initialized                      */
#define HAL_CAN_STATE_MASK_INIT                             (1U << 30U)     /*!< CAN Initialized but not yet configured       */
#define HAL_CAN_STATE_MASK_READY                            (1U << 29U)     /*!< CAN configured and ready to be activated     */
#define HAL_CAN_STATE_MASK_ACTIVE                           (1U << 28U)     /*!< CAN operating                                */
#define HAL_CAN_STATE_MASK_ERROR                            (1U << 27U)     /*!< CAN error state                              */
/** @} */

/** @name HAL_CAN_TsfStateMaskTypeDef
  * @brief CAN Transfer State definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_CAN_TsfStateMaskTypeDef                         uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_CAN_TsfStateMaskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_CAN_TSF_STATE_MASK_IDLE                         (1U << 30U)     /*!< CAN Ready to transfer data                   */
#define HAL_CAN_TSF_STATE_MASK_BUSY                         (1U << 29U)     /*!< CAN tansfer process is ongoing or no ready   */
/** @} */

/**
  * @}
  */ /* CAN_HAL_EM_Mask */


/**
  * @}
  */ /* CAN_HAL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CAN_HAL_EM_Assert CAN HAL Assert 
  * @brief    CAN HAL Assert
  * @{
  */

/**
  * @brief  The HAL_CAN_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_CAN_CHECK_PARAM
#define TAE32_USE_HAL_CAN_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_CAN_CHECK_PARAM != 1) && (TAE32_USE_HAL_CAN_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_CAN_CHECK_PARAM
#define TAE32_USE_HAL_CAN_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_CAN_CHECK_PARAM */

/**
  * @brief  The HAL_CAN_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_CAN_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_CAN_CHECK_PARAM) { \
            expression;                      \
        }

/**
 * @brief Updates a CAN HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the CAN process
 * state check feature is enabled (TAE32_USE_HAL_CAN_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_CAN_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_CAN_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_CAN_CHECK_PROCESS_STATE == 1)
#define HAL_CAN_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_CAN_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
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
  */ /* CAN_HAL_EM_Assert */



/** @defgroup CAN_HAL_Exported_Macros CAN HAL Exported Macros
  * @brief    CAN HAL Exported Macros
  * @{
  */

//...

/**
  * @}
  */ /* CAN_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup CAN_HAL_Exported_Types CAN HAL Exported Types
  * @brief    CAN HAL Exported Types
  * @{
  */


/**
  * @brief CAN State definition
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_CAN_STATE_RESET     = HAL_CAN_STATE_MASK_RESET,     /*!< CAN Not yet initialized                              */
    HAL_CAN_STATE_INIT      = HAL_CAN_STATE_MASK_INIT,      /*!< CAN Initialized but not yet configured               */
    HAL_CAN_STATE_READY     = HAL_CAN_STATE_MASK_READY,     /*!< CAN configured and ready to be activated             */
    HAL_CAN_STATE_ACTIVE    = HAL_CAN_STATE_MASK_ACTIVE,    /*!< CAN operating                                        */
    HAL_CAN_STATE_ERROR     = HAL_CAN_STATE_MASK_ERROR,     /*!< CAN error state                                      */
} HAL_CAN_StateTypeDef;

_Static_assert(sizeof(HAL_CAN_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

/**
  * @brief CAN Transfer State definition
  */
typedef enum
{
    HAL_CAN_TSF_STATE_IDLE  = HAL_CAN_TSF_STATE_MASK_IDLE,  /*!< CAN Ready to transfer data                           */
    HAL_CAN_TSF_STATE_BUSY  = HAL_CAN_TSF_STATE_MASK_BUSY   /*!< CAN tansfer process is ongoing or no ready           */
} HAL_CAN_TsfStateTypeDef;

_Static_assert(sizeof(HAL_CAN_TsfStateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else
typedef HAL_CAN_StateMaskTypeDef        HAL_CAN_StateTypeDef;
#define HAL_CAN_STATE_RESET             HAL_CAN_STATE_MASK_RESET
#define HAL_CAN_STATE_INIT              HAL_CAN_STATE_MASK_INIT
#define HAL_CAN_STATE_READY             HAL_CAN_STATE_MASK_READY
#define HAL_CAN_STATE_ACTIVE            HAL_CAN_STATE_MASK_ACTIVE
#define HAL_CAN_STATE_ERROR             HAL_CAN_STATE_MASK_ERROR

typedef HAL_CAN_TsfStateMaskTypeDef     HAL_CAN_TsfStateTypeDef;
#define HAL_CAN_TSF_STATE_IDLE          HAL_CAN_TSF_STATE_MASK_IDLE
#define HAL_CAN_TSF_STATE_BUSY          HAL_CAN_TSF_STATE_MASK_BUSY
#endif

/**
  * @brief CAN Function Enable Definition
  */
typedef enum
{
    HAL_CAN_FUNC_DISABLE  = 0U,    /*!< CAN Function Disable  */
    HAL_CAN_FUNC_ENABLE   = 1U     /*!< CAN Function Enable   */
} HAL_CAN_EnableTypeDef;

/**
  * @brief CAN Flag Status Definition
  */
typedef enum
{
    HAL_CAN_FLAG_RESET   = 0U,    /*!< CAN Flag Reset   */
    HAL_CAN_FLAG_SET     = 1U     /*!< CAN Flag Set     */
} HAL_CAN_FlagStatusTypeDef;

/**
 * @brief CAN IRQ Callback ID definition
 */
typedef enum 
{
    HAL_CAN_PTB_TX_CPLT_CB_ID   = 0U,       /*!< CAN PTB Tx Completed callback ID   */
    HAL_CAN_STB_TX_CPLT_CB_ID   = 1U,       /*!< CAN STB Tx Completed callback ID   */
    HAL_CAN_PRB_RX_CPLT_CB_ID   = 2U,       /*!< CAN Rx Completed callback ID       */
    HAL_CAN_SRB_RX_CPLT_CB_ID   = 3U,       /*!< CAN SRB Completed callback ID      */
    HAL_CAN_ETB_EVT_CPLT_CB_ID  = 4U,       /*!< CAN ETB Completed callback ID      */
    HAL_CAN_ERROR_CB_ID         = 5U,       /*!< CAN Error callback ID              */
    HAL_CAN_CB_ID_ENUM_END                  /*!< CAN callback ID enum end           */
} HAL_CAN_UsrCbIdTypeDef;

/**
  * @brief CAN Message Buffer Type Definition
  */
typedef enum
{
    HAL_CAN_MESG_BUFFER_PTB     = 0U,       /*!< CAN Message Buffer PTB */
    HAL_CAN_MESG_BUFFER_STB     = 1U,       /*!< CAN Message Buffer STB */
    HAL_CAN_MESG_BUFFER_PRB     = 2U,       /*!< CAN Message Buffer PRB */
    HAL_CAN_MESG_BUFFER_SRB     = 3U,       /*!< CAN Message Buffer SRB */
    HAL_CAN_MESG_BUFFER_ETB     = 4U        /*!< CAN Message Buffer ETB */
} HAL_CAN_MsgBufTypeDef;

/**
  * @brief CAN Interrupt Line Definition
  */
typedef enum
{
    HAL_CAN_INTERRUPT_LINE_0    = 0U,    /*!< CAN Interrupt Line 0  */
    HAL_CAN_INTERRUPT_LINE_1    = 1U     /*!< CAN Interrupt Line 1  */
} HAL_CAN_ITLineTypeDef;

/**
  * @brief CAN Rx Receive Multiplexer definition
  */
typedef enum
{
    HAL_CAN_RX_MUXSEL_DISABLE  = LL_CAN_RX_MUXSEL_DISABLE,   /*!< CAN RX Receive Multiplexer Disabled: For CAN0 :  \
                                                                  CAN0_RX used as the receive signal source. For   \
                                                                  CAN1 : CAN1_RX used as the receive signal        \
                                                                  source.                                          */
    HAL_CAN_RX_MUXSEL_ENABLE   = LL_CAN_RX_MUXSEL_ENABLE     /*!< CAN RX Receive Multiplexer Enabled: For CAN0 :   \
                                                                  CAN1_RX used as the receive signal source. For   \
                                                                  CAN1 : CAN0_RX used as the receive signal        \
                                                                  source. Note: When CAN is configured in          \
                                                                  listen-only mode(LOM=1), the CAN RX Receive      \
                                                                  Multiplexer can be enabled.                      */
} HAL_CAN_RxMuxSelTypeDef;

/**
  *@brief CAN RX buffer status enum type define
  */
typedef enum
{
    HAL_CAN_RX_BUF_STA_EMPTY        = LL_CAN_RX_BUF_STA_EMPTY,         /*!< CAN RX buffer empty         */
    HAL_CAN_RX_BUF_STA_FEW          = LL_CAN_RX_BUF_STA_FEW,           /*!< CAN RX buffer few           */
    HAL_CAN_RX_BUF_STA_ALMOST_FULL  = LL_CAN_RX_BUF_STA_ALMOST_FULL,   /*!< CAN RX buffer almost full   */
    HAL_CAN_RX_BUF_STA_FULL         = LL_CAN_RX_BUF_STA_FULL           /*!< CAN RX buffer full          */
} HAL_CAN_RxBufStaTypeDef;

/**
  * @brief CAN acceptance filter slot definition.
  */
typedef enum
{
    HAL_CAN_ACCEPT_FILT_SLOT_0     = LL_CAN_ACCEPT_FILT_SLOT_0,     /*!< CAN acceptance filter slot 0         */
    HAL_CAN_ACCEPT_FILT_SLOT_1     = LL_CAN_ACCEPT_FILT_SLOT_1,     /*!< CAN acceptance filter slot 1         */
    HAL_CAN_ACCEPT_FILT_SLOT_2     = LL_CAN_ACCEPT_FILT_SLOT_2,     /*!< CAN acceptance filter slot 2         */
    HAL_CAN_ACCEPT_FILT_SLOT_3     = LL_CAN_ACCEPT_FILT_SLOT_3,     /*!< CAN acceptance filter slot 3         */
    HAL_CAN_ACCEPT_FILT_SLOT_4     = LL_CAN_ACCEPT_FILT_SLOT_4,     /*!< CAN acceptance filter slot 4         */
    HAL_CAN_ACCEPT_FILT_SLOT_5     = LL_CAN_ACCEPT_FILT_SLOT_5,     /*!< CAN acceptance filter slot 5         */
    HAL_CAN_ACCEPT_FILT_SLOT_6     = LL_CAN_ACCEPT_FILT_SLOT_6,     /*!< CAN acceptance filter slot 6         */
    HAL_CAN_ACCEPT_FILT_SLOT_7     = LL_CAN_ACCEPT_FILT_SLOT_7,     /*!< CAN acceptance filter slot 7         */
    HAL_CAN_ACCEPT_FILT_SLOT_8     = LL_CAN_ACCEPT_FILT_SLOT_8,     /*!< CAN acceptance filter slot 8         */
    HAL_CAN_ACCEPT_FILT_SLOT_9     = LL_CAN_ACCEPT_FILT_SLOT_9,     /*!< CAN acceptance filter slot 9         */
    HAL_CAN_ACCEPT_FILT_SLOT_10    = LL_CAN_ACCEPT_FILT_SLOT_10,    /*!< CAN acceptance filter slot 10        */
    HAL_CAN_ACCEPT_FILT_SLOT_11    = LL_CAN_ACCEPT_FILT_SLOT_11,    /*!< CAN acceptance filter slot 11        */
    HAL_CAN_ACCEPT_FILT_SLOT_12    = LL_CAN_ACCEPT_FILT_SLOT_12,    /*!< CAN acceptance filter slot 12        */
    HAL_CAN_ACCEPT_FILT_SLOT_13    = LL_CAN_ACCEPT_FILT_SLOT_13,    /*!< CAN acceptance filter slot 13        */
    HAL_CAN_ACCEPT_FILT_SLOT_14    = LL_CAN_ACCEPT_FILT_SLOT_14,    /*!< CAN acceptance filter slot 14        */
    HAL_CAN_ACCEPT_FILT_SLOT_15    = LL_CAN_ACCEPT_FILT_SLOT_15,    /*!< CAN acceptance filter slot 15        */
    HAL_CAN_ACCEPT_FILT_SLOT_NUMS  = LL_CAN_ACCEPT_FILT_SLOT_NUMS   /*!< CAN acceptance filter slot Numbers   */
} HAL_CAN_AcceptFilSlotTypeDef;

/**
  * @brief CAN acceptance filter Rx frame type definition.
  */
typedef enum
{
    HAL_CAN_ACCEPT_FILT_FRM_STD_EXT  = LL_CAN_ACCEPT_FILT_FRM_STD_EXT,   /*!< CAN acceptance filter Rx frame type Standard and \
                                                                              Extended                                        */
    HAL_CAN_ACCEPT_FILT_FRM_STD      = LL_CAN_ACCEPT_FILT_FRM_STD,       /*!< CAN acceptance filter Rx frame type Standard    */
    HAL_CAN_ACCEPT_FILT_FRM_EXT      = LL_CAN_ACCEPT_FILT_FRM_EXT        /*!< CAN acceptance filter Rx frame type Extended    */
} HAL_CAN_AcceptFilRxFrmTypeDef;

/**
  * @brief CAN buffer almost full warnning limit definition
  */
typedef enum
{
    HAL_CAN_BUF_ALMOST_FULL_LIMIT_0     = LL_CAN_BUF_ALMOST_FULL_LIMIT_0,   /*!< CAN buffer almost full warnning limit: 0 Frame     */
    HAL_CAN_BUF_ALMOST_FULL_LIMIT_1     = LL_CAN_BUF_ALMOST_FULL_LIMIT_1,   /*!< CAN buffer almost full warnning limit: 1 Frame     */
    HAL_CAN_BUF_ALMOST_FULL_LIMIT_2     = LL_CAN_BUF_ALMOST_FULL_LIMIT_2,   /*!< CAN buffer almost full warnning limit: 2 Frame     */
    HAL_CAN_BUF_ALMOST_FULL_LIMIT_3     = LL_CAN_BUF_ALMOST_FULL_LIMIT_3,   /*!< CAN buffer almost full warnning limit: 3 Frame     */
    HAL_CAN_BUF_ALMOST_FULL_LIMIT_MAX   = HAL_CAN_BUF_ALMOST_FULL_LIMIT_3   /*!< CAN buffer almost full warnning limit max numbers  */
} HAL_CAN_BufAlmostFullLimitTypeDef;

/**
  * @brief CAN buffer almost empty warnning limit definition
  */
typedef enum
{
    HAL_CAN_BUF_ALMOST_EMPTY_LIMIT_0    = LL_CAN_BUF_ALMOST_EMPTY_LIMIT_0,  /*!< CAN buffer almost empty warnning limit: 0 Frame    */
    HAL_CAN_BUF_ALMOST_EMPTY_LIMIT_1    = LL_CAN_BUF_ALMOST_EMPTY_LIMIT_1,  /*!< CAN buffer almost empty warnning limit: 1 Frame    */
    HAL_CAN_BUF_ALMOST_EMPTY_LIMIT_2    = LL_CAN_BUF_ALMOST_EMPTY_LIMIT_2,  /*!< CAN buffer almost empty warnning limit: 2 Frame    */
    HAL_CAN_BUF_ALMOST_EMPTY_LIMIT_MAX  = HAL_CAN_BUF_ALMOST_EMPTY_LIMIT_2  /*!< CAN buffer almost empty warnning limit max numbers */
} HAL_CAN_BufAlmostEmptyLimitTypeDef;

/**
  * @brief CAN programmable error warning limit definition
  */
typedef enum
{
    HAL_CAN_ERR_WARN_LIMIT_8    = LL_CAN_ERR_WARN_LIMIT_8,     /*!< CAN programmable error warning limit: 8 bytes    */
    HAL_CAN_ERR_WARN_LIMIT_16   = LL_CAN_ERR_WARN_LIMIT_16,    /*!< CAN programmable error warning limit: 16 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_24   = LL_CAN_ERR_WARN_LIMIT_24,    /*!< CAN programmable error warning limit: 24 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_32   = LL_CAN_ERR_WARN_LIMIT_32,    /*!< CAN programmable error warning limit: 32 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_40   = LL_CAN_ERR_WARN_LIMIT_40,    /*!< CAN programmable error warning limit: 40 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_48   = LL_CAN_ERR_WARN_LIMIT_48,    /*!< CAN programmable error warning limit: 48 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_56   = LL_CAN_ERR_WARN_LIMIT_56,    /*!< CAN programmable error warning limit: 56 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_64   = LL_CAN_ERR_WARN_LIMIT_64,    /*!< CAN programmable error warning limit: 64 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_72   = LL_CAN_ERR_WARN_LIMIT_72,    /*!< CAN programmable error warning limit: 72 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_80   = LL_CAN_ERR_WARN_LIMIT_80,    /*!< CAN programmable error warning limit: 80 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_88   = LL_CAN_ERR_WARN_LIMIT_88,    /*!< CAN programmable error warning limit: 88 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_96   = LL_CAN_ERR_WARN_LIMIT_96,    /*!< CAN programmable error warning limit: 96 bytes   */
    HAL_CAN_ERR_WARN_LIMIT_104  = LL_CAN_ERR_WARN_LIMIT_104,   /*!< CAN programmable error warning limit: 104 bytes  */
    HAL_CAN_ERR_WARN_LIMIT_112  = LL_CAN_ERR_WARN_LIMIT_112,   /*!< CAN programmable error warning limit: 112 bytes  */
    HAL_CAN_ERR_WARN_LIMIT_120  = LL_CAN_ERR_WARN_LIMIT_120,   /*!< CAN programmable error warning limit: 120 bytes  */
    HAL_CAN_ERR_WARN_LIMIT_128  = LL_CAN_ERR_WARN_LIMIT_128    /*!< CAN programmable error warning limit: 128 bytes  */
} HAL_CAN_ErrWarnLimitTypeDef;

/**
  * @brief CAN Data Length Code definition
  * @note  data_len_code > 8 is only valid with FD Enable
  */
typedef enum
{
    HAL_CAN_DAT_LEN_CODE_BYTE_0     = LL_CAN_DAT_LEN_CODE_BYTE_0,     /*!< CAN Data Length 0 Byte Code    */
    HAL_CAN_DAT_LEN_CODE_BYTE_1     = LL_CAN_DAT_LEN_CODE_BYTE_1,     /*!< CAN Data Length 1 Byte Code    */
    HAL_CAN_DAT_LEN_CODE_BYTES_2    = LL_CAN_DAT_LEN_CODE_BYTES_2,    /*!< CAN Data Length 2 Bytes Code   */
    HAL_CAN_DAT_LEN_CODE_BYTES_3    = LL_CAN_DAT_LEN_CODE_BYTES_3,    /*!< CAN Data Length 3 Bytes Code   */
    HAL_CAN_DAT_LEN_CODE_BYTES_4    = LL_CAN_DAT_LEN_CODE_BYTES_4,    /*!< CAN Data Length 4 Bytes Code   */
    HAL_CAN_DAT_LEN_CODE_BYTES_5    = LL_CAN_DAT_LEN_CODE_BYTES_5,    /*!< CAN Data Length 5 Bytes Code   */
    HAL_CAN_DAT_LEN_CODE_BYTES_6    = LL_CAN_DAT_LEN_CODE_BYTES_6,    /*!< CAN Data Length 6 Bytes Code   */
    HAL_CAN_DAT_LEN_CODE_BYTES_7    = LL_CAN_DAT_LEN_CODE_BYTES_7,    /*!< CAN Data Length 7 Bytes Code   */
    HAL_CAN_DAT_LEN_CODE_BYTES_8    = LL_CAN_DAT_LEN_CODE_BYTES_8,    /*!< CAN Data Length 8 Bytes Code   */
    HAL_CAN_DAT_LEN_CODE_20_ENUM_MAX = HAL_CAN_DAT_LEN_CODE_BYTES_8,  /*!< CAN 2.0 Max Data Length Code   */
    HAL_CAN_DAT_LEN_CODE_BYTES_12    = LL_CAN_DAT_LEN_CODE_BYTES_12,  /*!< CAN Data Length 12 Bytes Code  */
    HAL_CAN_DAT_LEN_CODE_BYTES_16    = LL_CAN_DAT_LEN_CODE_BYTES_16,  /*!< CAN Data Length 16 Bytes Code  */
    HAL_CAN_DAT_LEN_CODE_BYTES_20    = LL_CAN_DAT_LEN_CODE_BYTES_20,  /*!< CAN Data Length 20 Bytes Code  */
    HAL_CAN_DAT_LEN_CODE_BYTES_24    = LL_CAN_DAT_LEN_CODE_BYTES_24,  /*!< CAN Data Length 24 Bytes Code  */
    HAL_CAN_DAT_LEN_CODE_BYTES_32    = LL_CAN_DAT_LEN_CODE_BYTES_32,  /*!< CAN Data Length 32 Bytes Code  */
    HAL_CAN_DAT_LEN_CODE_BYTES_48    = LL_CAN_DAT_LEN_CODE_BYTES_48,  /*!< CAN Data Length 48 Bytes Code  */
    HAL_CAN_DAT_LEN_CODE_BYTES_64    = LL_CAN_DAT_LEN_CODE_BYTES_64,  /*!< CAN Data Length 64 Bytes Code  */
    HAL_CAN_DAT_LEN_CODE_FD_ENUM_MAX = HAL_CAN_DAT_LEN_CODE_BYTES_64, /*!< CAN FD Max Data Length Code    */
    HAL_CAN_DAT_LEN_CODE_NUMS                                         /*!<CAN Data Length Code Numbers    */
} HAL_CAN_DatLenCodeTypeDef;

/**
  * @brief CAN frame store mode definition.
  */
typedef enum
{
    HAL_CAN_FRAME_STORE_MODE_NONE  = LL_CAN_FRAME_STORE_MODE_NONE,   /*!< CAN frame store none       */
    HAL_CAN_FRAME_STORE_MODE_PRB   = LL_CAN_FRAME_STORE_MODE_PRB,    /*!< CAN frame store with PRB   */
    HAL_CAN_FRAME_STORE_MODE_SRB   = LL_CAN_FRAME_STORE_MODE_SRB     /*!< CAN frame store with SRB   */
} HAL_CAN_FrmStoreModeTypeDef;

/**
  * @brief CAN node status definition.
  */
typedef enum
{
    HAL_CAN_NODE_STA_SYNC  = LL_CAN_NODE_STA_SYNC,   /*!< CAN node Synchronization status   */
    HAL_CAN_NODE_STA_IDLE  = LL_CAN_NODE_STA_IDLE,   /*!< CAN node Idle status              */
    HAL_CAN_NODE_STA_RECV  = LL_CAN_NODE_STA_RECV,   /*!< CAN node Receive status           */
    HAL_CAN_NODE_STA_SEND  = LL_CAN_NODE_STA_SEND    /*!< CAN node Transmission status      */
} HAL_CAN_NodeStaTypeDef;

/**
  * @brief CAN Data Field Error definition.
  */
typedef enum
{
    HAL_CAN_DATA_FIELD_ERR_NONE                       = LL_CAN_DATA_FIELD_ERR_NONE,                       /*!< CAN data field no error                          */
    HAL_CAN_DATA_FIELD_ERR_BIT                        = LL_CAN_DATA_FIELD_ERR_BIT,                        /*!< CAN data field Bit error                         */
    HAL_CAN_DATA_FIELD_ERR_BIT_STUFFING               = LL_CAN_DATA_FIELD_ERR_BIT_STUFFING,               /*!< CAN data field Bit Stuffing error                */
    HAL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT           = LL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT,           /*!< CAN data field Acc Accelerated Frame Bit error   */
    HAL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT_STUFFING  = LL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT_STUFFING   /*!< CAN data field Acc Accelerated Frame Bit         \
                                                                                                               Stuffing error                                   */
} HAL_CAN_DatFieldErrTypeDef;

/**
  * @brief CAN Error Status definition.
  */
typedef enum
{
    HAL_CAN_ERROR_STATUS_NONE                           = LL_CAN_ERROR_STATUS_NONE,                         /*!< CAN no error                                     */
    HAL_CAN_ERROR_STATUS_BIT_NOT_DAT_FIELD              = LL_CAN_ERROR_STATUS_BIT_NOT_DAT_FIELD,            /*!< CAN bit error of not data field                  */
    HAL_CAN_ERROR_STATUS_FORMAT_NOT_DAT_FIELD           = LL_CAN_ERROR_STATUS_FORMAT_NOT_DAT_FIELD,         /*!< CAN format error of not data field               */
    HAL_CAN_ERROR_STATUS_BIT_STUFFING_NOT_DAT_FIELD     = LL_CAN_ERROR_STATUS_BIT_STUFFING_NOT_DAT_FIELD,   /*!< CAN bit stuffing error of not data field         */
    HAL_CAN_ERROR_STATUS_ACK                            = LL_CAN_ERROR_STATUS_ACK,                          /*!< CAN acknowledgement error                        */
    HAL_CAN_ERROR_STATUS_CRC                            = LL_CAN_ERROR_STATUS_CRC,                          /*!< CAN CRC error                                    */
    HAL_CAN_ERROR_STATUS_OTHER                          = LL_CAN_ERROR_STATUS_OTHER                         /*!< CAN other error                                  */
} HAL_CAN_ErrStatusTypeDef;

/**
  * @brief CAN Interrupt Line definition.
  */
typedef enum
{
    HAL_CAN_INT_LINE_0    = LL_CAN_INT_LINE_0,   /*!< CAN Interrupt Line CANx_INT0   */
    HAL_CAN_INT_LINE_1    = LL_CAN_INT_LINE_1    /*!< CAN Interrupt Line CANx_INT1   */
} HAL_CAN_IntLineTypeDef;

/**
  * @brief CAN Acceptance Mode definition.
  */
typedef enum
{
    HAL_CAN_ACCEPT_MODE_AND         = LL_CAN_ACCEPT_MODE_AND,         /*!< Range of CAN filter matching is ID=ACODE_X &     \
                                                                           ~AMASK_X                                         */
    HAL_CAN_ACCEPT_MODE_OR          = LL_CAN_ACCEPT_MODE_OR,          /*!< Range of CAN filter matching is ID=ACODE_X or    \
                                                                           ID=AMASK_X                                       */
    HAL_CAN_ACCEPT_MODE_RANGE       = LL_CAN_ACCEPT_MODE_RANGE,       /*!< Range of CAN filter matching is ACODE_X <= ID <= \
                                                                           AMASK_X                                          */
    HAL_CAN_ACCEPT_MODE_AND_EIDM    = LL_CAN_ACCEPT_MODE_AND_EIDM,    /*!< Range of CAN filter matching is ID=(ACODE_X &    \
                                                                           ~AMASK_X) and support EIDM                       */
    HAL_CAN_ACCEPT_MODE_OR_EIDM     = LL_CAN_ACCEPT_MODE_OR_EIDM,     /*!< Range of CAN filter matching is ID=ACODE_X or    \
                                                                           ID=AMASK_X and support EIDM                      */
    HAL_CAN_ACCEPT_MODE_RANGE_EIDM  = LL_CAN_ACCEPT_MODE_RANGE_EIDM   /*!< Range of CAN filter matching is ACODE_X <= ID <= \
                                                                           AMASK_X and support EIDM                         */
} HAL_CAN_AcceptModeTypeDef;

/**
  * @brief CAN Acceptance Control definition.
  */
typedef enum
{
    HAL_CAN_ACCEPT_CTRL_NONE                        = LL_CAN_ACCEPT_CTRL_NONE,                         /*!< CAN filter match, no action                      */
    HAL_CAN_ACCEPT_CTRL_STORE_PRB                   = LL_CAN_ACCEPT_CTRL_STORE_PRB,                    /*!< CAN filter match, data store in PRB              */
    HAL_CAN_ACCEPT_CTRL_STORE_SRB                   = LL_CAN_ACCEPT_CTRL_STORE_SRB,                    /*!< CAN filter match, data store in SRB              */
    HAL_CAN_ACCEPT_CTRL_UPD_PRIO_STA_REG            = LL_CAN_ACCEPT_CTRL_UPD_PRIO_STA_REG,             /*!< CAN filter match, update priority status         \
                                                                                                            register                                         */
    HAL_CAN_ACCEPT_CTRL_STORE_PRB_UPD_PRIO_STA_REG  = LL_CAN_ACCEPT_CTRL_STORE_PRB_UPD_PRIO_STA_REG,   /*!< CAN filter match, data store in PRB and update   \
                                                                                                            priority status register                         */
    HAL_CAN_ACCEPT_CTRL_STORE_SRB_UPD_PRIO_STA_REG  = LL_CAN_ACCEPT_CTRL_STORE_SRB_UPD_PRIO_STA_REG    /*!< CAN filter match, data store in SRB and update   \
                                                                                                            priority status register                         */
} HAL_CAN_AcceptCtrlTypeDef;

/**
  * @brief CAN Timestamp Timebase definition.
  */
typedef enum
{
    HAL_CAN_TIMESTAMP_TIMEBASE_CLOSE     = LL_CAN_TIMESTAMP_TIMEBASE_CLOSE,      /*!< CAN Timestamp Timebase close              */
    HAL_CAN_TIMESTAMP_TIMEBASE_INT_TSC   = LL_CAN_TIMESTAMP_TIMEBASE_INT_TSC,    /*!< CAN Timestamp Timebase interior TSC       */
    HAL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR0  = LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR0,   /*!< CAN Timestamp Timebase external timer 0   */
    HAL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR1  = LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR1,   /*!< CAN Timestamp Timebase external timer 1   */
    HAL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR2  = LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR2    /*!< CAN Timestamp Timebase external timer 2   */
} HAL_CAN_TimestampTimebaseTypeDef;

/**
  * @brief CAN Timestamp Prescaler definition.
  */
typedef enum
{
    HAL_CAN_TIMESTAMP_PRESCALER_1     = LL_CAN_TIMESTAMP_PRESCALER_1,   /*!< Timestamp Prescaler 1   */
    HAL_CAN_TIMESTAMP_PRESCALER_2     = LL_CAN_TIMESTAMP_PRESCALER_2,   /*!< Timestamp Prescaler 2   */
    HAL_CAN_TIMESTAMP_PRESCALER_3     = LL_CAN_TIMESTAMP_PRESCALER_3,   /*!< Timestamp Prescaler 3   */
    HAL_CAN_TIMESTAMP_PRESCALER_4     = LL_CAN_TIMESTAMP_PRESCALER_4,   /*!< Timestamp Prescaler 4   */
    HAL_CAN_TIMESTAMP_PRESCALER_5     = LL_CAN_TIMESTAMP_PRESCALER_5,   /*!< Timestamp Prescaler 5   */
    HAL_CAN_TIMESTAMP_PRESCALER_6     = LL_CAN_TIMESTAMP_PRESCALER_6,   /*!< Timestamp Prescaler 6   */
    HAL_CAN_TIMESTAMP_PRESCALER_7     = LL_CAN_TIMESTAMP_PRESCALER_7,   /*!< Timestamp Prescaler 7   */
    HAL_CAN_TIMESTAMP_PRESCALER_8     = LL_CAN_TIMESTAMP_PRESCALER_8,   /*!< Timestamp Prescaler 8   */
    HAL_CAN_TIMESTAMP_PRESCALER_9     = LL_CAN_TIMESTAMP_PRESCALER_9,   /*!< Timestamp Prescaler 9   */
    HAL_CAN_TIMESTAMP_PRESCALER_10    = LL_CAN_TIMESTAMP_PRESCALER_10,  /*!< Timestamp Prescaler 10  */
    HAL_CAN_TIMESTAMP_PRESCALER_11    = LL_CAN_TIMESTAMP_PRESCALER_11,  /*!< Timestamp Prescaler 11  */
    HAL_CAN_TIMESTAMP_PRESCALER_12    = LL_CAN_TIMESTAMP_PRESCALER_12,  /*!< Timestamp Prescaler 12  */
    HAL_CAN_TIMESTAMP_PRESCALER_13    = LL_CAN_TIMESTAMP_PRESCALER_13,  /*!< Timestamp Prescaler 13  */
    HAL_CAN_TIMESTAMP_PRESCALER_14    = LL_CAN_TIMESTAMP_PRESCALER_14,  /*!< Timestamp Prescaler 14  */
    HAL_CAN_TIMESTAMP_PRESCALER_15    = LL_CAN_TIMESTAMP_PRESCALER_15,  /*!< Timestamp Prescaler 15  */
    HAL_CAN_TIMESTAMP_PRESCALER_16    = LL_CAN_TIMESTAMP_PRESCALER_16   /*!< Timestamp Prescaler 16  */
} HAL_CAN_TimestampPrescalerTypeDef;

/**
  * @brief CAN Timeout Counter definition.
  */
typedef enum
{
    HAL_CAN_TIMEOUT_CNTR_PRB    = LL_CAN_TIMEOUT_CNTR_PRB,  /*!< CAN Timeout Counter PRB        */
    HAL_CAN_TIMEOUT_CNTR_SRB    = LL_CAN_TIMEOUT_CNTR_SRB,  /*!< CAN Timeout Counter SRB        */
    HAL_CAN_TIMEOUT_CNTR_ETB    = LL_CAN_TIMEOUT_CNTR_ETB,  /*!< CAN Timeout Counter Tx Event   */
    HAL_CAN_TIMEOUT_CNTR_CONT   = LL_CAN_TIMEOUT_CNTR_CONT  /*!< CAN Timeout Counter Continuous */
} HAL_CAN_TimeoutCntrTypeDef;

/**
  * @brief CAN Rx Buffer Work Mode definition.
  */
typedef enum
{
    HAL_CAN_RX_BUF_WORK_MODE_COVER  = LL_CAN_RX_BUF_WORK_MODE_COVER,   /*!< Rx buffer work mode Cover   */
    HAL_CAN_RX_BUF_WORK_MODE_BLOCK  = LL_CAN_RX_BUF_WORK_MODE_BLOCK    /*!< Rx buffer work mode Block   */
} HAL_CAN_RxBufWorkModeTypeDef;

/**
  * @brief CAN Frame Format definition.
  */
typedef enum
{
    HAL_CAN_FRAME_FORMAT_STD_CAN    = 0U,   /*!< CAN 2.0 Frame Format   */
    HAL_CAN_FRAME_FORMAT_FD_CAN     = 1U    /*!< CAN FD Frame Format    */
} HAL_CAN_FrmFmtTypeDef;

/**
  * @brief CAN ID Extension type definition.
  */
typedef enum
{
    HAL_CAN_ID_EXT_STANDARD     = 0U,   /*!< CAN Standard Frame */
    HAL_CAN_ID_EXT_EXTENDED     = 1U    /*!< CAN Extended Frame */
} HAL_CAN_IdExtTypeDef;

/**
  * @brief CAN Transmission Request type definition.
  */
typedef enum
{
    HAL_CAN_TRANS_REQ_DATA      = 0U,   /*!< CAN Data Frame     */
    HAL_CAN_TRANS_REQ_REMOTE    = 1U    /*!< CAN Remote Frame   */
} HAL_CAN_TransReqTypeDef;

/**
  * @brief CAN Bit Rate Switch type definition.
  */
typedef enum
{
    HAL_CAN_BIT_RATE_SWITCH_OFF = 0U,   /*!< CAN FD Bit Rate Switch Off */
    HAL_CAN_BIT_RATE_SWITCH_ON  = 1U    /*!< CAN FD Bit Rate Switch On  */
} HAL_CAN_BitRateSwTypeDef;

/**
  * @brief CAN Tx Event type definition.
  */
typedef enum
{
    HAL_CAN_TX_EVT_NO       = 0U,   /*!< CAN Do not store Tx events */
    HAL_CAN_TX_EVT_STORE    = 1U    /*!< CAN Store Tx events        */
} HAL_CAN_TxEvtTypeDef;

/**
  * @brief CAN Error State Indicator definition.
  */
typedef enum
{
    HAL_CAN_ERR_STATE_IND_ACTIVE    = 0U,   /*!< CAN FD Error State Indicator Active    */
    HAL_CAN_ERR_STATE_IND_PASSIVE   = 1U    /*!< CAN FD Error State Indicator Passive   */
} HAL_CAN_ErrStaIndTypeDef;

/**
  * @brief CAN Operating Mode definition.
  */
typedef enum
{
    HAL_CAN_OP_MODE_NORMAL          = 0U,   /*!< Operating Mode - Normal        */
    HAL_CAN_OP_MODE_LISTEN_ONLY     = 1U,   /*!< Operating Mode - Listen Only   */
    HAL_CAN_OP_MODE_EXTERNAL_LOOP   = 2U,   /*!< Operating Mode - External Loop */
    HAL_CAN_OP_MODE_INTERNAL_LOOP   = 4U,   /*!< Operating Mode - Internal Loop */
} HAL_CAN_OpModeTypeDef;


/**
  * @brief CAN RX buffer format type definition
  */
typedef struct 
{
    /*! Standard/Extended iDentifier value
     */
    uint32_t Identifier             : 29,

             /*! Reserved bit.
              */
             reserved1              : 2,

             /*! Error State Indicator. This is a read-only status bit for RBUF and is not available
              *  in TBUF. The protocol machine automatically embeds the correct value of ESI into
              *  transmitted frames. ESI is only included in CAN FD frames and does not exist in CAN
              *  2.0 frames.
              */
             ErrorStateIndicator    : 1;    /*! @ref HAL_CAN_ErrStaIndTypeDef */

    /*! The Data Length Code (DLC) in RBUF and TBUF defines the length of the payload(the
     *  number of payload bytes in a frame). 
     */
    uint32_t DataLengthCode         : 4,    /*! @ref HAL_CAN_DatLenCodeTypeDef */

             /*! Bit Rate Switch
              *  0: nominal / slow bit rate for the complete frame.
              *  1: switch to data / fast bit rate for the data payload and the CRC
              *  Only CAN FD frames can switch the bitrate. Therefore BRS is forced to 0 if EDL=0
              */
             BitRateSwitch          : 1,    /*! @ref HAL_CAN_BitRateSwTypeDef */

             /*! Frame Format Type
              *  0: CAN 2.0 frame (up to 8 bytes payload)
              *  1: CAN FD frame (up to 64 bytes payload)
              */
             FDFormat               : 1,    /*! @ref HAL_CAN_FrmFmtTypeDef */

             /*! Remote Transmission Request
              *  0: data frame
              *  1: remote frame
              *  Only CAN 2.0 frames can be remote frames. There is no remote frame for CAN FD.
              *  Therefore RTR is forced to 0 if EDL=1 in the TBUF.
              */
             RemoteTransRequest     : 1,    /*! @ref HAL_CAN_TransReqTypeDef */

             /*! IDentifier Extension
              *  0: Standard Format: ID(10:0)
              *  1: Extended Format: ID(28:0)
              */
             IdExtension            : 1,    /*! @ref HAL_CAN_IdExtTypeDef */

             /*! Data Timestamp
              */
             RxTimestamp            : 16,

             /*! Acceptance Data
              */
             AcceptanceData         : 4,

             /*! Reserved bit.
              */
             reserved2              : 4;
} HAL_CAN_RxBufFormatTypeDef;

/**
  * @brief CAN TX buffer format type definition
  */
typedef struct 
{
    /*! Standard/Extended iDentifier value
     */
    uint32_t Identifier             : 29,

             /*! Reserved bit.
              */
             reserved1              : 3;

    /*! The Data Length Code (DLC) in RBUF and TBUF defines the length of the payload(the
     *  number of payload bytes in a frame). 
     */
    uint32_t DataLengthCode         : 4,    /*! @ref HAL_CAN_DatLenCodeTypeDef */

             /*! Bit Rate Switch
              *  0: nominal / slow bit rate for the complete frame.
              *  1: switch to data / fast bit rate for the data payload and the CRC
              *  Only CAN FD frames can switch the bitrate. Therefore BRS is forced to 0 if EDL=0
              */
             BitRateSwitch          : 1,    /*! @ref HAL_CAN_BitRateSwTypeDef */

             /*! Extended Data Length
              *  0: CAN 2.0 frame (up to 8 bytes payload)
              *  1: CAN FD frame (up to 64 bytes payload)
              */
             FDFormat               : 1,    /*! @ref HAL_CAN_FrmFmtTypeDef */

             /*! Remote Transmission Request
              *  0: data frame
              *  1: remote frame
              *  Only CAN 2.0 frames can be remote frames. There is no remote frame for CAN FD.
              *  Therefore RTR is forced to 0 if EDL=1 in the TBUF.
              */
             RemoteTransRequest     : 1,    /*! @ref HAL_CAN_TransReqTypeDef */

             /*! IDentifier Extension
              *  0: Standard Format: ID(10:0)
              *  1: Extended Format: ID(28:0)
              */
             IdExtension            : 1,    /*! @ref HAL_CAN_IdExtTypeDef */

             /*! Data Message Marker
              */
             MessageMarker          : 8,

             /*! Reserved bit.
              */
             reserved2              : 15,

             /*! Event Buffer
              *  0: Message not write to ETB
              *  1: Message write to ETB
              */
             EventType              : 1;    /*! @ref HAL_CAN_TxEvtTypeDef */
} HAL_CAN_TxBufFormatTypeDef;

/**
  * @brief CAN ETB buffer format type definition
  */
typedef struct 
{
    /*! Standard/Extended iDentifier value
     */
    uint32_t Identifier             : 29,

             /*! Reserved bit.
              */
             reserved1              : 2,

             /*! Error State Indicator. This is a read-only status bit for RBUF and is not available
              *  in TBUF. The protocol machine automatically embeds the correct value of ESI into
              *  transmitted frames. ESI is only included in CAN FD frames and does not exist in CAN
              *  2.0 frames.
              */
             ErrorStateIndicator    : 1;    /*! @ref HAL_CAN_ErrStaIndTypeDef */

    /*! The Data Length Code (DLC) in RBUF and TBUF defines the length of the payload(the
     *  number of payload bytes in a frame). 
     */
    uint32_t DataLengthCode         : 4,    /*! @ref HAL_CAN_DatLenCodeTypeDef */

             /*! Bit Rate Switch
              *  0: nominal / slow bit rate for the complete frame.
              *  1: switch to data / fast bit rate for the data payload and the CRC
              *  Only CAN FD frames can switch the bitrate. Therefore BRS is forced to 0 if EDL=0
              */
             BitRateSwitch          : 1,    /*! @ref HAL_CAN_BitRateSwTypeDef */

             /*! Extended Data Length
              *  0: CAN 2.0 frame (up to 8 bytes payload)
              *  1: CAN FD frame (up to 64 bytes payload)
              */
             FDFormat               : 1,    /*! @ref HAL_CAN_FrmFmtTypeDef */

             /*! Remote Transmission Request
              *  0: data frame
              *  1: remote frame
              *  Only CAN 2.0 frames can be remote frames. There is no remote frame for CAN FD.
              *  Therefore RTR is forced to 0 if EDL=1 in the TBUF.
              */
             RemoteTransRequest     : 1,    /*! @ref HAL_CAN_TransReqTypeDef */

             /*! IDentifier Extension
              *  0: Standard Format: ID(10:0)
              *  1: Extended Format: ID(28:0)
              */
             IdExtension            : 1,    /*! @ref HAL_CAN_IdExtTypeDef */

             /*! Tx Data Timestamp
              */
             TxTimestamp            : 16,

             /*! Tx Buffer Frame Message Marker
              */
             MessageMarker          : 8;
} HAL_CAN_TxEvtBufFormatTypeDef;

/**
  * @brief  CAN filter structure definition
  */
typedef struct
{
    HAL_CAN_AcceptFilRxFrmTypeDef   IdType;             /*!< Specifies the identifier type.                     */
    HAL_CAN_AcceptFilSlotTypeDef    FilterIndex;        /*!< Specifies the filter which will be initialized.    */
    HAL_CAN_AcceptModeTypeDef       FilterType;         /*!< Specifies the filter type.                         */
    HAL_CAN_AcceptCtrlTypeDef       FilterConfig;       /*!< Specifies the filter configuration.                */
    uint32_t                        CodeID;             /*!< Specifies the filter identification Acceptance CODE.
                                                            This parameter must be a number between:
                                                            - 0 and 0x7FF, if IdType is Standard ID
                                                            - 0 and 0x1FFFFFFF, if IdType is Extended ID        */
    uint32_t                        MaskID;             /*!< Specifies the filter identification Acceptance MASK.
                                                            This parameter must be a number between:
                                                            - 0 and 0x7FF, if IdType is Standard ID
                                                            - 0 and 0x1FFFFFFF, if IdType is Extended ID        */
} HAL_CAN_FilterTypeDef;

/**
  * @brief CAN Protocol Status structure definition
  */
typedef struct
{
    HAL_CAN_ErrStatusTypeDef        LastErrorCode;      /*!< Specifies the type of the last error that occurred on the CAN bus.         */
    HAL_CAN_DatFieldErrTypeDef      DataLastErrorCode;  /*!< Specifies the type of the last error that occurred in the data phase
                                                            of a CAN FD format frame with its BRS flag set.                             */
    HAL_CAN_NodeStaTypeDef          Activity;           /*!< Specifies the CAN module communication state.                              */
    HAL_CAN_FlagStatusTypeDef       ErrorPassive;       /*!< Specifies the CAN module error status.
                                                            This parameter can be:
                                                            - 0 : The CAN is in Error_Active state
                                                            - 1 : The CAN is in Error_Passive state                                     */
    HAL_CAN_FlagStatusTypeDef       Warning;            /*!< Specifies the CAN module warning status.
                                                            This parameter can be:
                                                            - 0 : error counters (RxErrorCnt and TxErrorCnt) are below the
                                                                    Error Warning limit
                                                            - 1 : at least one of error counters has reached the Error Warning limit    */
    HAL_CAN_FlagStatusTypeDef       BusOff;             /*!< Specifies the CAN module Bus-Off status.
                                                            This parameter can be:
                                                            - 0 : The CAN is not in Bus_Off state
                                                            - 1 : The CAN is in Bus_Off state                                           */

    HAL_CAN_FrmStoreModeTypeDef     RxFrameStore;       /*!< CAN Rx buffer frame store type                                             */

    HAL_CAN_FlagStatusTypeDef       RxIDEflag;          /*!< Specifies IDE flag of last received CAN FD message.
                                                            This parameter can be:
                                                            - 0 : Last received CAN FD message did not have its IDE flag set
                                                            - 1 : Last received CAN FD message had its IDE flag set                     */
#if 0///TODO FOR FUTURE
    HAL_CAN_FlagStatusTypeDef       RxESIflag;          /*!< Specifies ESI flag of last received CAN FD message.
                                                            This parameter can be:
                                                            - 0 : Last received CAN FD message did not have its ESI flag set
                                                            - 1 : Last received CAN FD message had its ESI flag set                     */
#endif
    HAL_CAN_FlagStatusTypeDef       RxBRSflag;          /*!< Specifies BRS flag of last received CAN FD message.
                                                            This parameter can be:
                                                            - 0 : Last received CAN FD message did not have its BRS flag set
                                                            - 1 : Last received CAN FD message had its BRS flag set                     */
    HAL_CAN_FlagStatusTypeDef       RxFDFflag;          /*!< Specifies if CAN FD message (FDF flag set) has been received
                                                            since last protocol status.
                                                            This parameter can be:
                                                            - 0 : No CAN FD message received
                                                            - 1 : CAN FD message received                                               */
    HAL_CAN_FlagStatusTypeDef       ProtocolException;  /*!< Specifies the CAN module Protocol Exception status.
                                                            This parameter can be:
                                                            - 0 : No protocol exception event occurred since last read access
                                                            - 1 : Protocol exception event occurred                                     */
#if 0///TODO FOR FUTURE
    uint32_t TDCvalue;                                  /*!< Specifies the Transmitter Delay Compensation Value.
                                                            This parameter can be a number between 0 and 127                                */
#endif
} HAL_CAN_ProtocolStatusTypeDef;

/**
  * @brief  CAN High Priority Message Status structure definition
  */
typedef struct
{
    HAL_CAN_IdExtTypeDef            FilterList;         /*!< Specifies the filter list of the matching filter element. */
    HAL_CAN_AcceptFilSlotTypeDef    FilterIndex;        /*!< Specifies the index of matching filter element. */
    HAL_CAN_FrmStoreModeTypeDef     MessageStorage;     /*!< Specifies the HP Message Storage. */
} HAL_CAN_HpMsgStatusTypeDef;


/**
  * @brief CAN global filter config type definition
  */
typedef struct 
{
    HAL_CAN_EnableTypeDef           RejectRemoteStd;    /*!< Reject Standard remote frames      */
    HAL_CAN_EnableTypeDef           RejectRemoteExt;    /*!< Reject Extended remote frames      */
#if 0///TODO FOR FUTURE
    HAL_CAN_FrmStoreModeTypeDef     NonMatchingStd;
    HAL_CAN_FrmStoreModeTypeDef     NonMatchingExt;
#endif
    HAL_CAN_RxBufWorkModeTypeDef    WorkModePRB;        /*!< PRB Working Mode                   */
    HAL_CAN_RxBufWorkModeTypeDef    WorkModeSRB;        /*!< SRB Working Mode                   */
} HAL_CAN_GlobalFilCfgTypeDef;

/**
  * @brief CAN Init structure definition
  */
typedef struct
{
    uint32_t                        FunctionClockFrequency;     /*!< Specifies the Function Clock Frequency                     */
    HAL_CAN_FrmFmtTypeDef           FrameFormat;                /*!< Specifies the protocol frame format.                       */

#if 0///TODO FOR FUTURE
    HAL_CAN_EnableTypeDef           TransmitPause;              /*!< Enable or disable the Transmit Pause feature.              */
#endif

    HAL_CAN_EnableTypeDef           ISOMode;                    /*!< Enable or disable the ISO protocol adaptation.             */
    HAL_CAN_EnableTypeDef           ProtocolException;          /*!< Enable or disable the Protocol Exception Handling.         */
    uint32_t                        NominalBaudrate;            /*!< Specifies the CAN 2.0/FD bus baudrate in slow speed mode   */
    uint8_t                         NominalSyncJumpWidth;       /*!< Specifies the maximum number of time quanta the CAN
                                                                    hardware is allowed to lengthen or shorten a bit to perform */

    uint8_t                         NominalTimeSeg1;            /*!< Specifies the number of time quanta in Bit Segment 1.      */
    uint8_t                         NominalTimeSeg2;            /*!< Specifies the number of time quanta in Bit Segment 2.      */
    uint32_t                        DataBaudrate;               /*!< Specifies the CAN FD baudrate in fast speed mode           */
    uint8_t                         DataSyncJumpWidth;          /*!< Specifies the maximum number of time quanta the CAN FD
                                                                    hardware is allowed to lengthen or shorten a data bit to
                                                                    perform resynchronization.                                  */
    uint8_t                         DataTimeSeg1;               /*!< Specifies the number of time quanta in Data Bit Segment 1. */
    uint8_t                         DataTimeSeg2;               /*!< Specifies the number of time quanta in Data Bit Segment 2. */
} HAL_CAN_InitTypeDef;


/** @brief HAL CAN handle structure type */
typedef struct HAL_CAN_HandleStructDef HAL_CAN_HandleTypeDef; 

/** @brief CAN IRQ callback function type definition */
typedef void (*HAL_CAN_IRQCallback)(HAL_CAN_HandleTypeDef *Handle);

/**
  * @brief CAN IRQ Callback structure definition
  */
typedef struct 
{
    HAL_CAN_IRQCallback TxCpltPTBCallback;  /*!< CAN PTB Tx completed callback        */
    HAL_CAN_IRQCallback TxCpltSTBCallback;  /*!< CAN STB Tx completed callback        */
    HAL_CAN_IRQCallback RxCpltPRBCallback;  /*!< CAN PRB completed callback           */
    HAL_CAN_IRQCallback RxCpltSRBCallback;  /*!< CAN SRB completed callback           */
    HAL_CAN_IRQCallback TxEvtCpltCallback;  /*!< CAN ETB Tx Event completed callback  */
    HAL_CAN_IRQCallback ErrorCallback;      /*!< CAN Error callback                   */
} HAL_CAN_UserCallbackTypeDef;

/**
  * @brief CAN Transmission Tx definition
  */
typedef struct 
{
    volatile HAL_CAN_TsfStateTypeDef    TxState;            /*!< CAN Transfer Data State                    */
    volatile HAL_CAN_TsfStateTypeDef    TxEvtState;         /*!< CAN Tx Event State                         */
    HAL_CAN_IRQCallback                 TxCallback;         /*!< CAN Transmission Interrupt Service Routine */
    HAL_CAN_IRQCallback                 TxEvtCallback;      /*!< CAN Tx Event Interrupt Service Routine     */
    HAL_CAN_TxEvtBufFormatTypeDef       *pTxEvtMsgInfo;     /*!< CAN Tx Event Format Pointer                */
} HAL_CAN_TransTxTypeDef;

/**
  * @brief CAN Transmission Rx definition
  */
typedef struct 
{
    volatile HAL_CAN_TsfStateTypeDef    RxState;            /*!< CAN Transfer Data State                    */
    HAL_CAN_IRQCallback                 RxCallback;         /*!< CAN Transmission Interrupt Service Routine */
    HAL_CAN_RxBufFormatTypeDef          *pMsgInfo;          /*!< CAN Rx Buffer Format Pointer               */
    uint32_t                            *pDatBuf;           /*!< CAN Rx Buffer Pointer                      */
} HAL_CAN_TransRxTypeDef;


/**
  * @brief CAN Handle Structure definition
  */
struct HAL_CAN_HandleStructDef
{
    CAN_TypeDef                         *Instance;          /*!< Register base address      */
    volatile HAL_CAN_StateTypeDef       State;              /*!< Global state               */
    HAL_CAN_TransTxTypeDef              TxTsf;              /*!< Tx transmission state      */
    HAL_CAN_TransRxTypeDef              RxTsfPRB;           /*!< PRB transmission state     */
    HAL_CAN_TransRxTypeDef              RxTsfSRB;           /*!< SRB transmission state     */
    volatile HAL_CAN_ErrCodeMskTypeDef  ErrorCode;          /*!< Error code                 */
    const void                          *pUserData;         /*!< User data pointer          */

    HAL_CAN_UserCallbackTypeDef         UserCallback;       /*!<  User Callback             */
};

/**
  * @}
  */ /* CAN_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup CAN_HAL_Exported_Functions
  * @{
  */

/** @addtogroup CAN_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_CAN_Init(HAL_CAN_HandleTypeDef *Handle, 
                               CAN_TypeDef *CANx, 
                               const HAL_CAN_InitTypeDef *pInit);

HAL_StatusTypeDef HAL_CAN_DeInit(HAL_CAN_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_CAN_TxAbort(HAL_CAN_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CAN_RxAbort(HAL_CAN_HandleTypeDef *Handle);

void HAL_CAN_MspInit(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_MspDeInit(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_IoInit(CAN_TypeDef *CANx);
void HAL_CAN_IoDeInit(CAN_TypeDef *CANx);

HAL_StatusTypeDef HAL_CAN_RegisterCallback(HAL_CAN_HandleTypeDef *Handle, 
                                           HAL_CAN_UsrCbIdTypeDef CallbackID, 
                                           HAL_CAN_IRQCallback pCallback);

HAL_StatusTypeDef HAL_CAN_UnRegisterCallback(HAL_CAN_HandleTypeDef *Handle, 
                                             HAL_CAN_UsrCbIdTypeDef CallbackID);

/**
  * @}
  */ /* CAN_HAL_EF_Initialization */


/** @addtogroup CAN_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_CAN_OperatingModeCtrl(HAL_CAN_HandleTypeDef *Handle, 
                                            HAL_CAN_OpModeTypeDef OpMode);

HAL_StatusTypeDef HAL_CAN_ConfigFilter(HAL_CAN_HandleTypeDef *Handle, 
                                       const HAL_CAN_FilterTypeDef *pCfg);

HAL_StatusTypeDef HAL_CAN_ResetFilter(HAL_CAN_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_CAN_ConfigGlobalFilter(HAL_CAN_HandleTypeDef *Handle, 
                                             const HAL_CAN_GlobalFilCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_CAN_ResetGlobalFilter(HAL_CAN_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_CAN_ConfigTimestampCounter(HAL_CAN_HandleTypeDef *Handle, 
                                                 HAL_CAN_TimestampPrescalerTypeDef TimestampPrescaler);

HAL_StatusTypeDef HAL_CAN_EnableTimestampCounter(HAL_CAN_HandleTypeDef *Handle, 
                                                 HAL_CAN_TimestampTimebaseTypeDef Timebase);

HAL_StatusTypeDef HAL_CAN_DisableTimestampCounter(HAL_CAN_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_CAN_ConfigTimeoutCounter(HAL_CAN_HandleTypeDef *Handle, 
                                               HAL_CAN_TimeoutCntrTypeDef TimeoutCounter, 
                                               uint16_t TimeoutPeriod);

HAL_StatusTypeDef HAL_CAN_EnableTimeoutCounter(HAL_CAN_HandleTypeDef *Handle, 
                                               HAL_CAN_TimeoutCntrTypeDef TimeoutCounter);

HAL_StatusTypeDef HAL_CAN_DisableTimeoutCounter(HAL_CAN_HandleTypeDef *Handle, 
                                                HAL_CAN_TimeoutCntrTypeDef TimeoutCounter);

HAL_StatusTypeDef HAL_CAN_PTBAutoRetransmissionConfig(HAL_CAN_HandleTypeDef *Handle, 
                                                      HAL_CAN_EnableTypeDef IsEnable);

HAL_StatusTypeDef HAL_CAN_STBAutoRetransmissionConfig(HAL_CAN_HandleTypeDef *Handle, 
                                                      HAL_CAN_EnableTypeDef IsEnable);

HAL_StatusTypeDef HAL_CAN_ConfigExtendedIdMask(HAL_CAN_HandleTypeDef *Handle, 
                                               uint32_t Mask);

HAL_StatusTypeDef HAL_CAN_AlmostEmptyWarnLimitConfig(HAL_CAN_HandleTypeDef *Handle,
                                                     HAL_CAN_MsgBufTypeDef BufferType, 
                                                     HAL_CAN_BufAlmostEmptyLimitTypeDef WarningLimit);

HAL_StatusTypeDef HAL_CAN_AlmostFullWarnLimitConfig(HAL_CAN_HandleTypeDef *Handle,
                                                    HAL_CAN_MsgBufTypeDef BufferType, 
                                                    HAL_CAN_BufAlmostFullLimitTypeDef WarningLimit);

HAL_StatusTypeDef HAL_CAN_ConfigInterruptLines(HAL_CAN_HandleTypeDef *Handle, 
                                               HAL_CAN_ITLineMskTypeDef ITList, 
                                               HAL_CAN_ITLineTypeDef InterruptLine);


/**
  * @}
  */ /* CAN_HAL_EF_Configuration */


/** @addtogroup CAN_HAL_EF_Operation
  * @{
  */

HAL_StatusTypeDef HAL_CAN_Start(HAL_CAN_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CAN_Stop(HAL_CAN_HandleTypeDef *Handle);

uint8_t HAL_CAN_DataCode2Length(HAL_CAN_HandleTypeDef *Handle, 
                                uint8_t DatLenCode);

HAL_CAN_DatLenCodeTypeDef HAL_CAN_DataLength2Code(HAL_CAN_HandleTypeDef *Handle, 
                                                  uint8_t DatLen);

HAL_StatusTypeDef HAL_CAN_GetProtocolStatus(HAL_CAN_HandleTypeDef *Handle, 
                                            HAL_CAN_ProtocolStatusTypeDef *Status);

HAL_StatusTypeDef HAL_CAN_GetHighPriorityMessageStatus(HAL_CAN_HandleTypeDef *Handle, 
                                                       HAL_CAN_HpMsgStatusTypeDef *Status);

/**
  * @}
  */ /* CAN_HAL_EF_Operation */



/** @addtogroup CAN_HAL_EF_Transfer
  * @{
  */

HAL_StatusTypeDef HAL_CAN_AddMessageToPTB(HAL_CAN_HandleTypeDef *Handle, 
                                          HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                          uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_AddMessageToSTB(HAL_CAN_HandleTypeDef *Handle, 
                                          HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                          uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_GetPRBMessage(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_GetSRBMessage(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_GetTxEvent(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_TxEvtBufFormatTypeDef *pMesgInfo);

HAL_StatusTypeDef HAL_CAN_AddMessageToPTB_IT(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_AddMessageToSTB_IT(HAL_CAN_HandleTypeDef *Handle, 
                                         HAL_CAN_TxBufFormatTypeDef *pMesgInfo, 
                                         uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_GetPRBMessage_IT(HAL_CAN_HandleTypeDef *Handle,
                                        HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                        uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_GetSRBMessage_IT(HAL_CAN_HandleTypeDef *Handle, 
                                        HAL_CAN_RxBufFormatTypeDef *pMesgInfo, 
                                        uint32_t *pDataBuff);

HAL_StatusTypeDef HAL_CAN_GetTxEvent_IT(HAL_CAN_HandleTypeDef *Handle, 
                                        HAL_CAN_TxEvtBufFormatTypeDef *pMesgInfo);


/**
  * @}
  */ /* CAN_HAL_EF_Transfer */


/** @addtogroup CAN_HAL_EF_Interrupt
  * @{
  */

HAL_StatusTypeDef HAL_CAN_InterruptRequestEnable(HAL_CAN_HandleTypeDef *Handle,
                                                 HAL_CAN_ITEnMskTypeDef InterruptRequests);

HAL_StatusTypeDef HAL_CAN_InterruptRequestDisable(HAL_CAN_HandleTypeDef *Handle,
                                                   HAL_CAN_ITEnMskTypeDef InterruptRequests);

/* IRQ Handler*/
void HAL_CAN_IRQHandler(HAL_CAN_HandleTypeDef *Handle);

/* PRB INTERRUPT */
void HAL_CAN_PRBRxCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_PRBOverCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_PRBFullCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_PRBAlmostFullCallback(HAL_CAN_HandleTypeDef *Handle);

/* SRB INTERRUPT */
void HAL_CAN_SRBRxCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_SRBAlmostFullCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_SRBFullCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_SRBOverCallback(HAL_CAN_HandleTypeDef *Handle);

/* PTB INTERRUPT */
void HAL_CAN_PTBTxCallback(HAL_CAN_HandleTypeDef *Handle);

/* STB INTERRUPT */
void HAL_CAN_STBTxCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_STBAlmostEmptyCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_STBEmptyCallback(HAL_CAN_HandleTypeDef *Handle);

/* ETB INTERRUPT */
void HAL_CAN_ETBRxCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_ETBAlmostFullCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_ETBFullCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_ETBOverCallback(HAL_CAN_HandleTypeDef *Handle);

/* ERR INTERRUPT */
void HAL_CAN_ErrorCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_PassiveErrorCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_ArbitrationLostErrorCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_BusErrorCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_CounterErrorCallback(HAL_CAN_HandleTypeDef *Handle);

/* TMS INTERRUPT */
void HAL_CAN_ContCntTimeoutCallback(HAL_CAN_HandleTypeDef *Handle);

/* TMO INTERRUPT */
void HAL_CAN_ETBTimeoutCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_SRBTimeoutCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_PRBTimeoutCallback(HAL_CAN_HandleTypeDef *Handle);
void HAL_CAN_TimestampWraparoundCallback(HAL_CAN_HandleTypeDef *Handle);

/* ART INTERRUPT */
void HAL_CAN_AbortCallback(HAL_CAN_HandleTypeDef *Handle);

/* HPM INTERRUPT */
void HAL_CAN_HighPriorityMessageCallback(HAL_CAN_HandleTypeDef *Handle);


/**
  * @}
  */ /* CAN_HAL_Exported_Functions_Interrupt */

/**
  * @}
  */ /* CAN_HAL_Exported_Functions */


/**
  * @}
  */ /* CAN_HAL */

#endif /* CAN */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_CAN_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

