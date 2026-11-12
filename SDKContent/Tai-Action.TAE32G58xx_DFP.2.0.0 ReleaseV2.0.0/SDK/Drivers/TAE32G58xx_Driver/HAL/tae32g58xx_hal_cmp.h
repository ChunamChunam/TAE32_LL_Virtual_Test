/**
  ******************************************************************************
  * @file    tae32g58xx_hal_cmp.h
  * @author  Tai-Action SD Team
  * @brief   Header file for CMP HAL module
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
#ifndef _TAE32G58XX_HAL_CMP_H_
#define _TAE32G58XX_HAL_CMP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_cmp.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(CMP0) || defined(CMP1) || defined(CMP2) || defined(CMP3) || defined(CMP4) || \
    defined(CMP5) || defined(CMP6) || defined(CMP7) || defined(CMP8)

/** @addtogroup CMP_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CMP_HAL_Exported_Macros CMP HAL Exported Macros
  * @brief    CMP HAL Exported Macros
  * @{
  */

/** @defgroup CMP_HAL_EM_Assert CMP HAL Assert 
  * @brief    CMP HAL Assert
  * @{
  */

/**
  * @brief  The HAL_CMP_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_CMP_CHECK_PARAM
#define TAE32_USE_HAL_CMP_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_CMP_CHECK_PARAM != 1) && (TAE32_USE_HAL_CMP_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_CMP_CHECK_PARAM
#define TAE32_USE_HAL_CMP_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_CMP_CHECK_PARAM */

/**
  * @brief  The HAL_CMP_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_CMP_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_CMP_CHECK_PARAM) { \
            expression;                      \
        }

/**
 * @brief Updates a CMP HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the CMP process
 * state check feature is enabled (TAE32_USE_HAL_CMP_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_CMP_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_CMP_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_CMP_CHECK_PROCESS_STATE == 1)
#define HAL_CMP_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_CMP_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
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
  */ /* CMP_HAL_EM_Assert */

/** @defgroup CMP_HAL_EM_Mask CMP HAL Mask
  * @brief    CMP HAL Mask
  * @{
  */

/** @name HAL_CMP_StateMaskTypeDef
  * @brief CMP State Mask definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_CMP_StateMaskTypeDef                            uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_CMP_StateMaskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_CMP_STATE_MASK_RESET                            (0U)            /*!< CMP not yet initialized                   */
#define HAL_CMP_STATE_MASK_INIT                             (1UL << 30U)    /*!< CMP initialized but not yet configured    */
#define HAL_CMP_STATE_MASK_CONFIGURABLE                     (1UL << 29U)    /*!< CMP is configurable                       */
#define HAL_CMP_STATE_MASK_BUSY                             (1UL << 28U)    /*!< CMP internal process is ongoing           */
/** @} */

/**
  * @}
  */ /* CMP_HAL_EM_Mask */

/**
  * @}
  */ /* CMP_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup CMP_HAL_Exported_Types CMP HAL Exported Types
  * @brief    CMP HAL Exported Types
  * @{
  */

/**
  * @brief CMP Global state definition
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_CMP_STATE_RESET         = HAL_CMP_STATE_MASK_RESET,         /*!< CMP not yet initialized                   */
    HAL_CMP_STATE_INIT          = HAL_CMP_STATE_MASK_INIT,          /*!< CMP initialized but not yet configured    */
    HAL_CMP_STATE_CONFIGURABLE  = HAL_CMP_STATE_MASK_CONFIGURABLE,  /*!< CMP is configurable                       */
    HAL_CMP_STATE_BUSY          = HAL_CMP_STATE_MASK_BUSY,          /*!< CMP internal process is ongoing           */
} HAL_CMP_StateTypeDef;

_Static_assert(sizeof(HAL_CMP_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else
typedef HAL_CMP_StateMaskTypeDef        HAL_CMP_StateTypeDef;
#define HAL_CMP_STATE_RESET             HAL_CMP_STATE_MASK_RESET
#define HAL_CMP_STATE_INIT              HAL_CMP_STATE_MASK_INIT
#define HAL_CMP_STATE_CONFIGURABLE      HAL_CMP_STATE_MASK_CONFIGURABLE
#define HAL_CMP_STATE_BUSY              HAL_CMP_STATE_MASK_BUSY
#endif

/**
  * @brief CMP Blank Event Definition
  */
typedef enum
{
    HAL_CMP_BLK_EVT_SOFTWARE   = LL_CMP_BLK_EVT_NONE,       /*!< CMP Blank Event None        */
    HAL_CMP_BLK_EVT_TMR0_OC0   = LL_CMP_BLK_EVT_TMR0_OC0,   /*!< CMP Blank Event TMR0 OC0    */
    HAL_CMP_BLK_EVT_TMR1_OC0   = LL_CMP_BLK_EVT_TMR1_OC0,   /*!< CMP Blank Event TMR1 OC0    */
    HAL_CMP_BLK_EVT_TMR2_OC0   = LL_CMP_BLK_EVT_TMR2_OC0,   /*!< CMP Blank Event TMR2 OC0    */
    HAL_CMP_BLK_EVT_TMR3_OC0   = LL_CMP_BLK_EVT_TMR3_OC0,   /*!< CMP Blank Event TMR3 OC0    */
    HAL_CMP_BLK_EVT_TMR4_OC0   = LL_CMP_BLK_EVT_TMR4_OC0,   /*!< CMP Blank Event TMR4 OC0    */
    HAL_CMP_BLK_EVT_TMR9_OC0   = LL_CMP_BLK_EVT_TMR9_OC0,   /*!< CMP Blank Event TMR9 OC0    */
    HAL_CMP_BLK_EVT_TMR10_OC0  = LL_CMP_BLK_EVT_TMR10_OC0,  /*!< CMP Blank Event TMR10 OC0   */
    HAL_CMP_BLK_EVT_ENUM_END                                /*!< CMP Blank Event Enum End    */                           
} HAL_CMP_BlkEvtTypeDef;  

/**
  * @brief CMP Positive IN Source Definition
  */
typedef enum
{
    HAL_CMP_POSI_IN_SRC_CMP_INP0  = LL_CMP_POSI_IN_SRC_CMP_INP0,   /*!< CMP Positive IN Source CMP_INP0   */
    HAL_CMP_POSI_IN_SRC_CMP_INP1  = LL_CMP_POSI_IN_SRC_CMP_INP1,   /*!< CMP Positive IN Source CMP_INP1   */
    HAL_CMP_POSI_IN_SRC_ENUM_END                                   /*!< CMP Positive IN Source Enum End   */ 
} HAL_CMP_PosiInSrcTypeDef;

/**
  * @brief CMP Negative IN Source Definition
  */
typedef enum
{
    HAL_CMP_NEG_IN_SRC_CMP_INM0  = LL_CMP_NEG_IN_SRC_CMP_INM0,   /*!< CMP Negative IN Source CMP_INM0   */
    HAL_CMP_NEG_IN_SRC_CMP_INM1  = LL_CMP_NEG_IN_SRC_CMP_INM1,   /*!< CMP Negative IN Source CMP_INM1   */
    HAL_CMP_NEG_IN_SRC_DACy_OUT  = LL_CMP_NEG_IN_SRC_DACy_OUT,   /*!< CMP Negative IN Source DACy_OUT   */
    HAL_CMP_NEG_IN_SRC_DACz_OUT  = LL_CMP_NEG_IN_SRC_DACz_OUT,   /*!< CMP Negative IN Source DACz_OUT   */
    HAL_CMP_NEG_IN_SRC_ENUM_END                                  /*!< CMP Negative IN Source Enum End   */
} HAL_CMP_NegInSrcTypeDef;

/**
  * @brief CMP Hysteresis Definition
  */
typedef enum
{
    HAL_CMP_HYST_0mv      = LL_CMP_HYST_0mv,    /*!< CMP Hysteresis 0mv       */
    HAL_CMP_HYST_10mv     = LL_CMP_HYST_10mv,   /*!< CMP Hysteresis 10mv      */
    HAL_CMP_HYST_20mv     = LL_CMP_HYST_20mv,   /*!< CMP Hysteresis 20mv      */
    HAL_CMP_HYST_30mv     = LL_CMP_HYST_30mv,   /*!< CMP Hysteresis 30mv      */
    HAL_CMP_HYST_ENUM_END                       /*!< CMP Hysteresis Enum End  */
} HAL_CMP_HystTypeDef;

/**
  * @brief CMP Output polarity Invert Definition
  */
typedef enum
{
    HAL_CMP_OUT_POL_INV_DISABLE    = 0U,     /*!< CMP Output polarity Invert Disable  */
    HAL_CMP_OUT_POL_INV_ENABLE     = 1U,     /*!< CMP Output polarity Invert Enable   */
} HAL_CMP_OutPolInvEnTypeDef;

/**
  * @brief CMP Trigger Mode Definition
  */
typedef enum
{
    HAL_CMP_EDGE_IT_MODE_NO               = 0UL,    /*!< CMP No Edge interrupt                      */
    HAL_CMP_EDGE_IT_MODE_RISING           = 1UL,    /*!< CMP Rising Edge interrupt Mode             */
    HAL_CMP_EDGE_IT_MODE_FALLING          = 2UL,    /*!< CMP Falling Edge interrupt Mode            */
    HAL_CMP_EDGE_IT_MODE_RISING_FALLING   = 3UL,    /*!< CMP Rising and Falling Edge interrupt Mode */
    HAL_CMP_EDGE_IT_MODE_ENUM_END                   /*!< CMP interrupt Mode Enum End                */
} HAL_CMP_EdgeITModeTypeDef;

/**
  * @brief CMP Initialization Structure Definition
  */
typedef struct 
{
    HAL_CMP_PosiInSrcTypeDef    InputPlus;    /*!< Set comparator input plus (non-inverting input)                      */
    HAL_CMP_NegInSrcTypeDef     InputMinus;   /*!< Set comparator input minus (inverting input)                         */
    HAL_CMP_HystTypeDef         Hysteresis;   /*!< Set comparator hysteresis mode of the input minus                    */
    HAL_CMP_OutPolInvEnTypeDef  OutputPol;    /*!< Set comparator output polarity                                       */
    HAL_CMP_BlkEvtTypeDef       BlankingSrce; /*!< Set comparator blanking source                                       */
    HAL_CMP_EdgeITModeTypeDef   TriggerMode;  /*!< Set the comparator output triggering External Interrupt Line (EXTI)  */
} HAL_CMP_InitTypeDef;

typedef struct HAL_CMP_HandleStructDef HAL_CMP_HandleTypeDef; /*!< HAL CMP handle structure type */

/**
  * @brief  CMP Handle Structure definition
  */
struct HAL_CMP_HandleStructDef
{
    CMP_TypeDef                     *Instance;          /*!< Register base address    */
    volatile HAL_CMP_StateTypeDef   State;              /*!< Global state             */
    volatile uint32_t               ErrorCode;          /*!< CMP error code           */
    const void                      *pUserData;         /*!< User data pointer        */
};

/**
  * @}
  */ /* CMP_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup CMP_HAL_Exported_Functions
  * @{
  */

/** @addtogroup CMP_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_CMP_Init(HAL_CMP_HandleTypeDef *Handle, CMP_TypeDef *CMPx, HAL_CMP_InitTypeDef *pInit);
HAL_StatusTypeDef HAL_CMP_DeInit(HAL_CMP_HandleTypeDef *Handle);
void HAL_CMP_MspInit(HAL_CMP_HandleTypeDef *Handle);
void HAL_CMP_MspDeInit(HAL_CMP_HandleTypeDef *Handle);
void HAL_CMP_IoInit(CMP_TypeDef *CMPx);
void HAL_CMP_IoDeInit(CMP_TypeDef *CMPx);
/**
  * @}
  */ /* CMP_HAL_EF_Initialization */

/** @addtogroup CMP_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_CMP_BlankingConfig(HAL_CMP_HandleTypeDef *Handle, HAL_CMP_BlkEvtTypeDef BlankingSrce);
/**
  * @}
  */ /* CMP_HAL_EF_Configuration */
  
/** @addtogroup CMP_HAL_EF_Operation
  * @{
  */
HAL_StatusTypeDef HAL_CMP_Start(HAL_CMP_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CMP_Stop(HAL_CMP_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CMP_EnableSwBlanking(HAL_CMP_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CMP_DisableSwBlanking(HAL_CMP_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CMP_EnableOutputSync(HAL_CMP_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CMP_DisableOutputSync(HAL_CMP_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_CMP_OutputDebounce(HAL_CMP_HandleTypeDef *Handle, uint32_t Debounce);
/**
  * @}
  */ /* CMP_HAL_EF_Operation */

/** @addtogroup CMP_HAL_EF_Interrupt
  * @{
  */
void HAL_CMP_IRQHandler(HAL_CMP_HandleTypeDef *Handle);
void HAL_CMP_RisingEdgeCallback(HAL_CMP_HandleTypeDef *Handle);
void HAL_CMP_FallingEdgeCallback(HAL_CMP_HandleTypeDef *Handle);
/**
  * @}
  */ /* CMP_HAL_EF_Interrupt */

/**
  * @}
  */ /* CMP_HAL_Exported_Functions */


/**
  * @}
  */ /* CMP_HAL */

#endif /* CMP */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_CMP_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

