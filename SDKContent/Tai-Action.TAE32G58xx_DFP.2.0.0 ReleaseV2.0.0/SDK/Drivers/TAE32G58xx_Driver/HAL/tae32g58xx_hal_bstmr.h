/**
  ******************************************************************************
  * @file    tae32g58xx_hal_bstmr.h
  * @author  Tai-Action SD Team
  * @brief   Header file for BSTMR HAL module.
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
#ifndef _TAE32G58XX_HAL_BSTMR_H_
#define _TAE32G58XX_HAL_BSTMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_bstmr.h"

#if defined(TMR7) || defined(TMR8)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_BSTMR_MODULE_ENABLED) && (HAL_BSTMR_MODULE_ENABLED == 1)


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup BSTMR_HAL_Exported_Macros BSTMR HAL Exported Macros
  * @{
  */

/** @defgroup BSTMR_HAL_EM_Assert BSTMR HAL Assert 
  * @brief    BSTMR HAL Assert
  * @{
  */

#ifndef TAE32_USE_HAL_BSTMR_CHECK_PARAM
#define TAE32_USE_HAL_BSTMR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_BSTMR_CHECK_PARAM != 1) && (TAE32_USE_HAL_BSTMR_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_BSTMR_CHECK_PARAM
#define TAE32_USE_HAL_BSTMR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_BSTMR_CHECK_PARAM */

#define HAL_BSTMR_PARAM_CHECK(expression)     \
        if (TAE32_USE_HAL_BSTMR_CHECK_PARAM) { \
            expression;                        \
        }
/**
  * @}
  */ /* BSTMR_HAL_EM_Assert */


/**
 * @brief Updates a BSTMR HAL parameter with optional validation.
 *
 * This macro assigns @p new_value to @p upd_parm. When the BSTMR process
 * state check feature is enabled (TAE32_USE_HAL_BSTMR_CHECK_PROCESS_STATE == 1),
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
 * @note When TAE32_USE_HAL_BSTMR_CHECK_PROCESS_STATE is not defined or set to 0,
 *       the macro checks whether @p upd_parm equals @p check_value before
 *       assigning @p new_value. If they are not equal, @p failed_expression
 *       is executed and @p upd_parm remains unchanged.
 */
#if defined(TAE32_USE_HAL_BSTMR_CHECK_PROCESS_STATE) && (TAE32_USE_HAL_BSTMR_CHECK_PROCESS_STATE == 1)
#define HAL_BSTMR_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)
#else
#define HAL_BSTMR_PARAM_UPDATE(upd_parm, check_value, new_value, failed_expression) \
        do {                                                                      \
            if ((upd_parm) != (check_value)) {                                    \
                failed_expression;                                                \
                break;                                                            \
            } else {                                                              \
                (upd_parm) = (new_value);                                         \
            }                                                                     \
        } while(0)    
#endif



/** @defgroup BSTMR_HAL_EM_Mask BSTMR HAL Mask
  * @brief    BSTMR HAL State / Error / Interrupt mask definitions
  * @{
  */

/** @name   HAL_BSTMR_StateMaskTypeDef 
  * @brief  HAL BSTMR global state mask definition. 
  * @{
  */
#define HAL_BSTMR_StateMaskTypeDef                          uint32_t

#define HAL_BSTMR_STATE_MASK_RESET                          (0U)         /*!< BSTMR not yet initialized                     */
#define HAL_BSTMR_STATE_MASK_CONFIGURABLE                   (1U << 30U)  /*!< BSTMR is configurable                         */
#define HAL_BSTMR_STATE_MASK_BUSY                           (1U << 29U)  /*!< An internal process is ongoing                */
#define HAL_BSTMR_STATE_MASK_TIMEOUT                        (1U << 28U)  /*!< Timeout state                                 */
#define HAL_BSTMR_STATE_MASK_ERROR                          (1U << 27U)  /*!< Error state                                   */
/** @} */

/** @name   HAL_BSTMR_ErrCodeMskTypeDef
  * @brief  HAL BSTMR Error Code Mask definition.
  * @{
  */
#define HAL_BSTMR_ErrCodeMskTypeDef                         uint32_t

#define HAL_BSTMR_ERROR_NONE                                (0U)         /*!< No error                     */
#define HAL_BSTMR_ERROR_INVALID_INSTANCE                    (1U << 30U)  /*!< Invalid instance error       */
/** @} */

/** @name   HAL_BSTMR_ITEnMskTypeDef
  * @brief  HAL BSTMR Interrupt Enable Mask Definition
  * @{
  */
#define HAL_BSTMR_ITEnMskTypeDef                            LL_BSTMR_IER_ITEnMskTypeDef

#define HAL_BSTMR_IER_OVERFLOW_IT_EN                        LL_BSTMR_IER_OVIE    /*!< Overflow interrupt enable mask            */
#define HAL_BSTMR_IER_UPDATE_IT_EN                          LL_BSTMR_IER_UIE     /*!< Update interrupt enable mask              */
/** @} */

/** @name   HAL_BSTMR_ITPendingMskTypeDef
  * @brief  HAL BSTMR Interrupt Flag Mask Definition
  * @{
  */
#define HAL_BSTMR_ITPendingMskTypeDef                       LL_BSTMR_SR_ITPendingMskTypeDef

#define HAL_BSTMR_SR_OVERFLOW_IT_FLAG                       LL_BSTMR_SR_OVIF     /*!< Overflow interrupt flag mask              */
#define HAL_BSTMR_SR_UPDATE_IT_FLAG                         LL_BSTMR_SR_UIF      /*!< Update interrupt flag mask                */

/** @} */



/**
  * @}
  */ /* BSTMR_HAL_EM_Mask */

/**
  * @}
  */ /* BSTMR_HAL_Exported_Macros */

/* Exported types ------------------------------------------------------------*/


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @addtogroup BSTMR_HAL
  * @brief    BSTMR HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup BSTMR_HAL_Exported_Types BSTMR HAL Exported Types
  * @brief    BSTMR HAL Exported Types
  * @{
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
/**
  * @brief  HAL BSTMR State definition
  */
typedef enum
{
    HAL_BSTMR_STATE_RESET           = HAL_BSTMR_STATE_MASK_RESET,         /*!< BSTMR not yet initialized           */
    HAL_BSTMR_STATE_CONFIGURABLE    = HAL_BSTMR_STATE_MASK_CONFIGURABLE,  /*!< BSTMR is configurable  */
    HAL_BSTMR_STATE_BUSY            = HAL_BSTMR_STATE_MASK_BUSY,          /*!< An internal process is ongoing      */
    HAL_BSTMR_STATE_TIMEOUT         = HAL_BSTMR_STATE_MASK_TIMEOUT,       /*!< Timeout state                       */
    HAL_BSTMR_STATE_ERROR           = HAL_BSTMR_STATE_MASK_ERROR          /*!< Error state                         */
} HAL_BSTMR_StateTypeDef;

_Static_assert(sizeof(HAL_BSTMR_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else /* TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

typedef HAL_BSTMR_StateMaskTypeDef      HAL_BSTMR_StateTypeDef;
#define HAL_BSTMR_STATE_RESET           HAL_BSTMR_STATE_MASK_RESET
#define HAL_BSTMR_STATE_CONFIGURABLE    HAL_BSTMR_STATE_MASK_CONFIGURABLE
#define HAL_BSTMR_STATE_BUSY            HAL_BSTMR_STATE_MASK_BUSY
#define HAL_BSTMR_STATE_TIMEOUT         HAL_BSTMR_STATE_MASK_TIMEOUT
#define HAL_BSTMR_STATE_ERROR           HAL_BSTMR_STATE_MASK_ERROR
#endif /* !TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

/**
 * @brief 
 */
typedef enum
{
    HAL_BSTMR_FUNC_DISABLE  = 0U,    /*!< BSTMR Function Disable  */
    HAL_BSTMR_FUNC_ENABLE   = 1U     /*!< BSTMR Function Enable   */
} HAL_BSTMR_EnableTypeDef;


/**
  * @brief HAL BSTMR WorkMode Enumeration 
  */
typedef enum 
{
    HAL_BSTMR_WORK_MODE_CONTINUE  = LL_BSTMR_WORK_MODE_CONTINUE,
    HAL_BSTMR_WORK_MODE_SINGLE    = LL_BSTMR_WORK_MODE_SINGLE,
} HAL_BSTMR_WorkModeTypeDef;

/**
  * @brief HAL BSTMR Update Event Disable Enumeration 
  */
typedef enum 
{
    HAL_BSTMR_UPDATE_EVT_RELEASE  = 0UL,
    HAL_BSTMR_UPDATE_EVT_ASSERT   = 1UL,
} HAL_BSTMR_UpdateEvtDisTypeDef;

/**
  * @brief HAL BSTMR Update Event Source Enumeration 
  */
typedef enum 
{
    HAL_BSTMR_UPDATE_EVT_SRC_OV_UG  = LL_BSTMR_UPDATE_EVT_SRC_OV_UG,
    HAL_BSTMR_UPDATE_EVT_SRC_OV     = LL_BSTMR_UPDATE_EVT_SRC_OV,
} HAL_BSTMR_UpdateEvtSrcTypeDef;


/**
  * @brief HAL BSTMR Master Mode Enumeration 
  */
typedef enum 
{
    HAL_BSTMR_MST_MODE_RESET        = LL_BSTMR_MST_MODE_RESET,
    HAL_BSTMR_MST_MODE_ENABLE       = LL_BSTMR_MST_MODE_ENABLE,
    HAL_BSTMR_MST_MODE_UPDATE       = LL_BSTMR_MST_MODE_UPDATE,
} HAL_BSTMR_MstModeTypeDef;

/**
  * @brief HAL BSTMR Event Source Enumeration 
  */
typedef enum
{
    HAL_BSTMR_EVENTSOURCE_UPDATE  =   LL_BSTMR_EVT_GEN_UPDATE,
} HAL_BSTMR_EvtSrcTypeDef;


/**
  * @brief  BSTMR Base Initialization Structure Definition
  */
typedef struct
{
    HAL_BSTMR_EnableTypeDef         AutoReloadPreload;  /*!< Auto Preload Enable                        */
    HAL_BSTMR_WorkModeTypeDef       WorkMode;           /*!< Work Mode: Continue/Single                 */
    uint16_t                        Period;             /*!< Period Value                               */
    uint16_t                        Prescaler;          /*!< Clock Prescaler                            */
    HAL_BSTMR_UpdateEvtDisTypeDef   UpdateEvent;        /*!< Update Event Enable                        */
    HAL_BSTMR_UpdateEvtSrcTypeDef   UpdateSource;       /*!< Update Event Source                        */
} HAL_BSTMR_BaseInitTypeDef;

/**
  * @brief  BSTMR Master Initialization Structure Definition
  */
typedef struct
{
    HAL_BSTMR_MstModeTypeDef        MasterMode;         /*!< Master Mode (TRGO source)                  */
    uint8_t                         TRGOWidth;          /*!< TRGO Output Width                          */
} HAL_BSTMR_MstInitTypeDef;

/**
  * @brief HAL BSTMR handle structure type
  */
typedef struct HAL_BSTMR_HandleStructDef HAL_BSTMR_HandleTypeDef;

/**
  * @brief BSTMR IRQ callback function type definition
  */
typedef void (*HAL_BSTMR_IRQCallback)(HAL_BSTMR_HandleTypeDef *Handle);

/**
  * @brief  BSTMR Handle Structure definition
  */
struct HAL_BSTMR_HandleStructDef
{
    BSTMR_TypeDef                           *Instance;        /*!< Register base address      */
    volatile HAL_BSTMR_StateTypeDef         State;            /*!< BSTMR operation state      */
    volatile HAL_BSTMR_ErrCodeMskTypeDef    LastErrorCodes;   /*!< Last error codes           */
    const void                              *pUserData;       /*!< User data pointer          */
};
/**
  * @}
  */ /* BSTMR_HAL_Exported_Types */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup BSTMR_HAL_Exported_Functions BSTMR HAL Exported Functions
  * @{
  */

/** @defgroup BSTMR_HAL_EF_Initialization BSTMR HAL Initialization
  * @{
  */

HAL_StatusTypeDef HAL_BSTMR_Base_Init(HAL_BSTMR_HandleTypeDef *Handle, 
                                      BSTMR_TypeDef *BSTMRx,
                                      const HAL_BSTMR_BaseInitTypeDef *pInit);
                              
HAL_StatusTypeDef HAL_BSTMR_Base_DeInit(HAL_BSTMR_HandleTypeDef *Handle);

void HAL_BSTMR_Base_MspInit(HAL_BSTMR_HandleTypeDef *Handle);
void HAL_BSTMR_Base_MspDeInit(HAL_BSTMR_HandleTypeDef *Handle);
/**
  * @}
  */

/** @defgroup BSTMR_HAL_EF_Configuration BSTMR HAL Configuration
  * @{
  */

HAL_StatusTypeDef HAL_BSTMR_InitMaster(HAL_BSTMR_HandleTypeDef *Handle,
                                       const HAL_BSTMR_MstInitTypeDef *pCfg);

/**
  * @}
  */

/** @defgroup BSTMR_HAL_EF_IO_Operation BSTMR HAL IO Operation
  * @{
  */
HAL_StatusTypeDef HAL_BSTMR_Base_Start(HAL_BSTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_BSTMR_Base_Stop(HAL_BSTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_BSTMR_Base_Start_IT(HAL_BSTMR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_BSTMR_Base_Stop_IT(HAL_BSTMR_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_BSTMR_InterruptRequestEnable(HAL_BSTMR_HandleTypeDef *Handle, 
                                                   HAL_BSTMR_ITEnMskTypeDef ITMask);

HAL_StatusTypeDef HAL_BSTMR_InterruptRequestDisable(HAL_BSTMR_HandleTypeDef *Handle, 
                                                    HAL_BSTMR_ITEnMskTypeDef ITMask);

HAL_StatusTypeDef HAL_BSTMR_GenerateEvent(HAL_BSTMR_HandleTypeDef *Handle, 
                                          HAL_BSTMR_EvtSrcTypeDef EventSource);

uint16_t HAL_BSTMR_ReadCounter(const HAL_BSTMR_HandleTypeDef *Handle);
/**
  * @}
  */

/** @defgroup BSTMR_HAL_EF_IRQ_Handler BSTMR HAL IRQ Handler and Callbacks
  * @{
  */

void HAL_BSTMR_IRQHandler(HAL_BSTMR_HandleTypeDef *Handle);

void HAL_BSTMR_OverflowCallback(HAL_BSTMR_HandleTypeDef *Handle);
void HAL_BSTMR_PeriodElapsedCallback(HAL_BSTMR_HandleTypeDef *Handle);
/**
  * @}
  */


/**
  * @}
  */ /* BSTMR_HAL_Exported_Functions */

/**
  * @}
  */ /* BSTMR_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

#endif /* BSTMR */
#endif /* HAL_MODULE_ENABLED */
#endif /* HAL_BSTMR_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_BSTMR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
