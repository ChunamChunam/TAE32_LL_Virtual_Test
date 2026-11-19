/**
  ******************************************************************************
  * @file    tae32f561x_hal_wwdg.h
  * @author  Tai-Action SD Team
  * @brief   Header file of WWDG HAL module.

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
#ifndef _TAE32F561X_HAL_WWDG_H_
#define _TAE32F561X_HAL_WWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_hal_def.h"
#include "tae32f561x_ll_wwdg.h"


/** @addtogroup TAE32F561x_HAL_Driver
  * @{
  */

/** @defgroup WWDG_HAL WWDG Hardware Abstraction Layer
  * @brief HAL layer driver for WWDG module.
  * @{
  */

/** @defgroup WWDG_HAL_Assert WWDG HAL Assert
  * @brief    WWDG HAL Assert
  * @{
  */
/** @brief  The HAL_WWDG_PARAM_CHECK function is off by default */
#ifndef TAE32_USE_HAL_WWDG_CHECK_PARAM
#define TAE32_USE_HAL_WWDG_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_WWDG_CHECK_PARAM != 1) && (TAE32_USE_HAL_WWDG_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_WWDG_CHECK_PARAM
#define TAE32_USE_HAL_WWDG_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif

#define HAL_WWDG_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_WWDG_CHECK_PARAM) { \
            expression;                       \
        }
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup WWDG_HAL_Exported_Constants WWDG HAL Exported Constants
  * @{
  */


/** @defgroup WWDG_HAL_EC_PRESCALER WWDG Prescaler
  * @brief Re-exported from LL layer for HAL API compatibility.
  * @{
  */

/** @defgroup HAL_WWDG_EC_EWI_MODE WWDG Early Wakeup Interrupt Mode
  * @{
  */
typedef enum { 
    HAL_WWDG_EWI_DISABLE           = LL_WWDG_EWI_DISABLE,                 /*!< Reset mode on timeout        */
    HAL_WWDG_EWI_ENABLE           = LL_WWDG_EWI_ENABLE              /*!< Interrupt mode on timeout    */
} HAL_WWDG_EWIModeTypeDef;



/**
  * @brief  WWDG Init structure definition
  */
typedef struct
{
    uint32_t Prescaler;  /*!< Specifies the prescaler value of the WWDG.
                              This parameter must be a number between 0x00
                              and @ref LL_WWDG_PRESCALER_MAX */

    uint32_t Window;     /*!< Specifies the WWDG window value to be compared to
                              the downcounter. This parameter must be a number
                              between @ref LL_WWDG_WINDOW_MIN and
                              @ref LL_WWDG_WINDOW_MAX */

    uint32_t Counter;    /*!< Specifies the WWDG free-running downcounter value.
                              This parameter must be a number between
                              @ref LL_WWDG_COUNTER_MIN and
                              @ref LL_WWDG_COUNTER_MAX */

    HAL_WWDG_EWIModeTypeDef       EWIMode;    /*!< Specifies if WWDG Early Wakeup Interrupt is
                              enabled or not. This parameter can be a value of
                              @ref HAL_WWDG_EC_EWI_MODE */

} HAL_WWDG_InitTypeDef;


/**
  * @brief  WWDG Handle Structure definition
  */
typedef struct HAL_WWDG_HandleStructDef HAL_WWDG_HandleTypeDef; /*!< HAL WWDG handle structure type */

typedef void (*HAL_WWDG_CallbackTypeDef)(HAL_WWDG_HandleTypeDef *Handle); /*!< HAL WWDG Callback pointer definition */

/**
  * @brief WWDG Handle Structure definition
  */
struct HAL_WWDG_HandleStructDef
{
    WWDG_TypeDef                 *Instance;   /*!< Register base address    */
    HAL_WWDG_CallbackTypeDef      EarlyWakeupCallback;    /*!< Early Wakeup Callback */
    const void                   *pUserData; /*!< User data pointer        */
};

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup WWDG_HAL_Exported_Constants WWDG HAL Exported Constants
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup WWDG_HAL_Exported_Functions WWDG HAL Exported Functions
  * @{
  */
HAL_StatusTypeDef HAL_WWDG_Init(HAL_WWDG_HandleTypeDef *Handle, WWDG_TypeDef *WWDGx,
                                HAL_WWDG_InitTypeDef *pInit);
HAL_StatusTypeDef HAL_WWDG_DeInit(HAL_WWDG_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_WWDG_Refresh(HAL_WWDG_HandleTypeDef *Handle,uint16_t Counter);

void HAL_WWDG_MspInit(HAL_WWDG_HandleTypeDef *Handle);
void HAL_WWDG_MspDeInit(HAL_WWDG_HandleTypeDef *Handle);

void HAL_WWDG_IRQHandler(HAL_WWDG_HandleTypeDef *Handle);

void HAL_WWDG_EarlyWakeupCallback(HAL_WWDG_HandleTypeDef *Handle);
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

#endif /* _TAE32F561X_HAL_WWDG_H_ */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/

