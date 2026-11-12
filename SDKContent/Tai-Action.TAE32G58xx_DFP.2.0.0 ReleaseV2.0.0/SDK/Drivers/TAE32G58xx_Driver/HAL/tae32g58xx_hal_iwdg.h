/**
  ******************************************************************************
  * @file    tae32g58xx_hal_iwdg.h
  * @author  Tai-Action SD Team
  * @brief   Header file of IWDG HAL module.
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
#ifndef _TAE32G58XX_HAL_IWDG_H_
#define _TAE32G58XX_HAL_IWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_iwdg.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @defgroup IWDG_HAL IWDG Hardware Abstraction Layer
  * @brief HAL layer driver for IWDG module.
  * @{
  */

/** @defgroup IWDG_HAL_Assert IWDG HAL Assert
  * @brief    IWDG HAL Assert
  * @{
  */
/** @brief  The HAL_IWDG_PARAM_CHECK function is off by default */
#ifndef TAE32_USE_HAL_IWDG_CHECK_PARAM
#define TAE32_USE_HAL_IWDG_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_IWDG_CHECK_PARAM != 1) && (TAE32_USE_HAL_IWDG_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_IWDG_CHECK_PARAM
#define TAE32_USE_HAL_IWDG_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif

#define HAL_IWDG_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_IWDG_CHECK_PARAM) { \
            expression;                       \
        }
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup IWDG_HAL_Exported_Types IWDG HAL Exported Types
  * @{
  */



/* Exported constants --------------------------------------------------------*/
/** @defgroup IWDG_HAL_Exported_Constants IWDG HAL Exported Constants
  * @{
  */

/** @defgroup IWDG_HAL_EC_PRESCALER IWDG Prescaler
  * @brief Re-exported from LL layer for HAL API compatibility.
  * @{
  */
typedef enum { 
    HAL_IWDG_PRESCALER_4              = LL_IWDG_PRESCALER_4,                 /*!< IWDG prescaler set to 4   */
    HAL_IWDG_PRESCALER_8              = LL_IWDG_PRESCALER_8,                 /*!< IWDG prescaler set to 8   */
    HAL_IWDG_PRESCALER_16             = LL_IWDG_PRESCALER_16,                /*!< IWDG prescaler set to 16  */
    HAL_IWDG_PRESCALER_32             = LL_IWDG_PRESCALER_32,                /*!< IWDG prescaler set to 32  */  
    HAL_IWDG_PRESCALER_64             = LL_IWDG_PRESCALER_64,                /*!< IWDG prescaler set to 64  */    
    HAL_IWDG_PRESCALER_128            = LL_IWDG_PRESCALER_128,               /*!< IWDG prescaler set to 128 */
    HAL_IWDG_PRESCALER_256            = LL_IWDG_PRESCALER_256,               /*!< IWDG prescaler set to 256 */
    HAL_IWDG_PRESCALER_512            = LL_IWDG_PRESCALER_512                /*!< IWDG prescaler set to 512 */
} HAL_IWDG_PrescalerTypeDef;
/**
  * @}
  */

/** @defgroup IWDG_HAL_EC_MODE IWDG Timeout Mode
  * @brief Re-exported from LL layer for HAL API compatibility.
  * @{
  */
typedef enum { 
    HAL_IWDG_MODE_RESET               = LL_IWDG_MODE_RESET,                 /*!< Reset mode on timeout        */
    HAL_IWDG_MODE_INTERRUPT           = LL_IWDG_MODE_INTERRUPT              /*!< Interrupt mode on timeout    */
} HAL_IWDG_ModeTypeDef;


/**
  * @brief  IWDG Init structure definition
  */
typedef struct
{
  HAL_IWDG_PrescalerTypeDef Prescaler;  /*!< Select the prescaler of the IWDG.
                            This parameter can be a value of @ref IWDG_HAL_EC_PRESCALER */
  uint32_t Reload;     /*!< Specifies the IWDG down-counter reload value.
                           This parameter must be a number between 0 and 0xFFFF */
  HAL_IWDG_ModeTypeDef       Mode;       /*!< Specifies the IWDG timeout behavior.
                            This parameter can be a value of @ref IWDG_HAL_EC_MODE */

} HAL_IWDG_InitTypeDef;

typedef struct HAL_IWDG_HandleStructDef HAL_IWDG_HandleTypeDef; /*!< HAL IWDG handle structure type */

typedef void (*HAL_IWDG_CallbackTypeDef)(HAL_IWDG_HandleTypeDef *Handle); /*!< HAL IWDG Callback pointer definition */

/**
  * @brief IWDG Handle Structure definition
  */
struct HAL_IWDG_HandleStructDef
{
    IWDG_TypeDef                         *Instance;          /*!< Register base address      */
    HAL_IWDG_CallbackTypeDef             TimeoutCallback;    /*!< Timeout Callback             */
    const void                           *pUserData;         /*!< User data pointer          */

};

/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup IWDG_HAL_Exported_Macros IWDG HAL Exported Macros
  * @{
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup IWDG_HAL_Exported_Functions IWDG HAL Exported Functions
  * @{
  */

/** @defgroup IWDG_HAL_Exported_Functions_Group1 Initialization and Start functions
  * @{
  */

HAL_StatusTypeDef HAL_IWDG_Init(HAL_IWDG_HandleTypeDef *Handle, IWDG_TypeDef *IWDGx,
                                HAL_IWDG_InitTypeDef *pInit);

HAL_StatusTypeDef HAL_IWDG_DeInit(HAL_IWDG_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_IWDG_Refresh(HAL_IWDG_HandleTypeDef *Handle);

void HAL_IWDG_MspInit(HAL_IWDG_HandleTypeDef *Handle);
void HAL_IWDG_MspDeInit(HAL_IWDG_HandleTypeDef *Handle);

void HAL_IWDG_IRQHandler(HAL_IWDG_HandleTypeDef *Handle);

void HAL_IWDG_TimeoutCallback(HAL_IWDG_HandleTypeDef *Handle);

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

#endif /* _TAE32G58XX_HAL_IWDG_H_ */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/
