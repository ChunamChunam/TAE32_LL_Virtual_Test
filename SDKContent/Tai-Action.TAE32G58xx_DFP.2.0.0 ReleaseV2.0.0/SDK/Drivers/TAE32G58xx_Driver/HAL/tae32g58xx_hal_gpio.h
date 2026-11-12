/**
  ******************************************************************************
  * @file    tae32g58xx_hal_gpio.h
  * @author  Tai-Action SD Team
  * @brief   Header file of GPIO HAL module.
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

#ifndef _TAE32G58XX_HAL_GPIO_H_
#define _TAE32G58XX_HAL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_gpio.h"

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(GPIOA) || defined(GPIOB) || defined(GPIOC)  || defined(GPIOD)  || defined(GPIOE) || defined(GPIOF) 

/** @defgroup GPIO_HAL GPIO HAL
  * @brief    GPIO HAL Module Driver
  * @{
  */

/* Exported Constants --------------------------------------------------------*/
/** @defgroup GPIO_HAL_Exported_Constants GPIO HAL Exported Constants
  * @brief    GPIO HAL Exported Constants
  * @{
  */

/** @defgroup HAL_GPIO_EC_PIN Pin
  * @brief    Defines the GPIO pin identifiers for HAL layer.
  * @{
  */
#define HAL_GPIO_PIN_0                   LL_GPIO_PIN_0     /*!< Pin 0 selected */
#define HAL_GPIO_PIN_1                   LL_GPIO_PIN_1     /*!< Pin 1 selected */
#define HAL_GPIO_PIN_2                   LL_GPIO_PIN_2     /*!< Pin 2 selected */
#define HAL_GPIO_PIN_3                   LL_GPIO_PIN_3     /*!< Pin 3 selected */
#define HAL_GPIO_PIN_4                   LL_GPIO_PIN_4     /*!< Pin 4 selected */
#define HAL_GPIO_PIN_5                   LL_GPIO_PIN_5     /*!< Pin 5 selected */
#define HAL_GPIO_PIN_6                   LL_GPIO_PIN_6     /*!< Pin 6 selected */
#define HAL_GPIO_PIN_7                   LL_GPIO_PIN_7     /*!< Pin 7 selected */
#define HAL_GPIO_PIN_8                   LL_GPIO_PIN_8     /*!< Pin 8 selected */
#define HAL_GPIO_PIN_9                   LL_GPIO_PIN_9     /*!< Pin 9 selected */
#define HAL_GPIO_PIN_10                  LL_GPIO_PIN_10    /*!< Pin 10 selected */
#define HAL_GPIO_PIN_11                  LL_GPIO_PIN_11    /*!< Pin 11 selected */
#define HAL_GPIO_PIN_12                  LL_GPIO_PIN_12    /*!< Pin 12 selected */
#define HAL_GPIO_PIN_13                  LL_GPIO_PIN_13    /*!< Pin 13 selected */
#define HAL_GPIO_PIN_14                  LL_GPIO_PIN_14    /*!< Pin 14 selected */
#define HAL_GPIO_PIN_15                  LL_GPIO_PIN_15    /*!< Pin 15 selected */
#define HAL_GPIO_PIN_ALL                 LL_GPIO_PIN_ALL   /*!< All pins selected */
/**
  * @}
  */ /* HAL_GPIO_EC_PIN */

/** @defgroup HAL_GPIO_EC_MODE Mode Type
  * @brief    Defines the output type for HAL layer.
  * @{
  */
#define HAL_GPIO_ModeTypeDef                    uint32_t            

#define HAL_GPIO_MODE_OUTPUT_POS                (0U)                                
#define HAL_GPIO_MODE_OUTPUT_MASK               (0x1UL  << HAL_GPIO_MODE_OUTPUT_POS) 
#define HAL_GPIO_MODE_OUTPUT_PP                 (0U     << HAL_GPIO_MODE_OUTPUT_POS)                                
#define HAL_GPIO_MODE_OUTPUT_OD                 (1U     << HAL_GPIO_MODE_OUTPUT_POS)                               

#define HAL_GPIO_MODE_EXTI_POS                  (8U)                               
#define HAL_GPIO_MODE_EXTI_MASK                 (0x3UL  << HAL_GPIO_MODE_EXTI_POS)  
#define HAL_GPIO_MODE_IT_CLOSE                  (0x0UL  << HAL_GPIO_MODE_EXTI_POS)    
#define HAL_GPIO_MODE_IT_FALLING                (0x1UL  << HAL_GPIO_MODE_EXTI_POS)   
#define HAL_GPIO_MODE_IT_RISING                 (0x2UL  << HAL_GPIO_MODE_EXTI_POS)    
#define HAL_GPIO_MODE_IT_RISING_FALLING         (0x3UL  << HAL_GPIO_MODE_EXTI_POS)    
/**
  * @}
  */ /* HAL_GPIO_EC_MODE */

/** @defgroup HAL_GPIO_EC_AF Alternate Function
  * @brief    Defines the alternate function selection for HAL layer.
  * @{
  */
typedef enum {
    HAL_GPIO_AF_0  = LL_GPIO_AF_0,  /*!< Input mode */
    HAL_GPIO_AF_1  = LL_GPIO_AF_1,  /*!< Output mode */
    HAL_GPIO_AF_2  = LL_GPIO_AF_2,  /*!< Alternate function 2 */
    HAL_GPIO_AF_3  = LL_GPIO_AF_3,  /*!< Alternate function 3 */
    HAL_GPIO_AF_4  = LL_GPIO_AF_4,  /*!< Alternate function 4 */
    HAL_GPIO_AF_5  = LL_GPIO_AF_5,  /*!< Alternate function 5 */
    HAL_GPIO_AF_6  = LL_GPIO_AF_6,  /*!< Alternate function 6 */
    HAL_GPIO_AF_7  = LL_GPIO_AF_7,  /*!< Alternate function 7 */
    HAL_GPIO_AF_8  = LL_GPIO_AF_8,  /*!< Alternate function 8 */
    HAL_GPIO_AF_9  = LL_GPIO_AF_9,  /*!< Alternate function 9 */
    HAL_GPIO_AF_10 = LL_GPIO_AF_10, /*!< Alternate function 10 */
    HAL_GPIO_AF_11 = LL_GPIO_AF_11, /*!< Alternate function 11 */
    HAL_GPIO_AF_12 = LL_GPIO_AF_12, /*!< Alternate function 12 */
    HAL_GPIO_AF_13 = LL_GPIO_AF_13, /*!< Alternate function 13 */
    HAL_GPIO_AF_14 = LL_GPIO_AF_14, /*!< Alternate function 14 */
    HAL_GPIO_AF_15 = LL_GPIO_AF_15  /*!< Analog mode */
} HAL_GPIO_AFTypeDef;
/**
  * @}
  */ /* HAL_GPIO_EC_AF */

/** @defgroup HAL_GPIO_EC_OUTPUT Output Type
  * @brief    Defines the output type for HAL layer.
  * @{
  */
typedef enum {
    HAL_GPIO_OUTPUT_PUSHPULL  = LL_GPIO_OUTPUT_PUSHPULL,  /*!< Push-pull output */
    HAL_GPIO_OUTPUT_OPENDRAIN = LL_GPIO_OUTPUT_OPENDRAIN  /*!< Open-drain output */
} HAL_GPIO_OutputTypeDef;
/**
  * @}
  */ /* HAL_GPIO_EC_OUTPUT */

/** @defgroup HAL_GPIO_EC_SPEED Output Speed
  * @brief    Defines the output speed for HAL layer.
  * @{
  */
typedef enum {
    HAL_GPIO_SPEED_FREQ_LOW  = LL_GPIO_SPEED_FREQ_LOW,  /*!< Low speed */
    HAL_GPIO_SPEED_FREQ_HIGH = LL_GPIO_SPEED_FREQ_HIGH  /*!< High speed */
} HAL_GPIO_SpeedTypeDef;
/**
  * @}
  */ /* HAL_GPIO_EC_SPEED */

/** @defgroup HAL_GPIO_EC_PULL Pull-up/Pull-down
  * @brief    Defines the pull-up/pull-down configuration for HAL layer.
  * @{
  */
typedef enum {
    HAL_GPIO_PULL_NO   = LL_GPIO_PULL_NO,  /*!< No pull */
    HAL_GPIO_PULL_UP   = LL_GPIO_PULL_UP,  /*!< Pull-up */
    HAL_GPIO_PULL_DOWN = LL_GPIO_PULL_DOWN /*!< Pull-down */
} HAL_GPIO_PullTypeDef;
/**
  * @}
  */ /* HAL_GPIO_EC_PULL */

/** @defgroup HAL_GPIO_EC_INT_MODE Interrupt Mode
  * @brief    Defines the interrupt trigger mode for HAL layer.
  * @{
  */
typedef enum {
    HAL_GPIO_INT_MODE_CLOSE           = LL_GPIO_INT_MODE_CLOSE,          /*!< Interrupt disabled */
    HAL_GPIO_INT_MODE_FALLING         = LL_GPIO_INT_MODE_FALLING,        /*!< Falling edge trigger */
    HAL_GPIO_INT_MODE_RISING          = LL_GPIO_INT_MODE_RISING,         /*!< Rising edge trigger */
    HAL_GPIO_INT_MODE_RISING_FALLING  = LL_GPIO_INT_MODE_RISING_FALLING  /*!< Both edges trigger */
} HAL_GPIO_IntModeTypeDef;
/**
  * @}
  */ /* HAL_GPIO_EC_INT_MODE */

/** @defgroup HAL_GPIO_EC_DRV_CAP Drive Capability
  * @brief    Defines the output drive capability for HAL layer.
  * @{
  */
typedef enum {
    HAL_GPIO_DRV_CAP_LOW       = LL_GPIO_DRV_CAP_LOW,       /*!< Low drive capability */
    HAL_GPIO_DRV_CAP_MED       = LL_GPIO_DRV_CAP_MED,       /*!< Medium drive capability */
    HAL_GPIO_DRV_CAP_HIGH      = LL_GPIO_DRV_CAP_HIGH,      /*!< High drive capability */
    HAL_GPIO_DRV_CAP_VERY_HIGH = LL_GPIO_DRV_CAP_VERY_HIGH  /*!< Very high drive capability */
} HAL_GPIO_DrvSpdTypeDef;
/**
  * @}
  */ /* HAL_GPIO_EC_DRV_CAP */

/** @defgroup HAL_GPIO_EC_PIN_STATE Pin State
  * @brief    Defines the pin state for HAL layer.
  * @{
  */
typedef enum {
    HAL_GPIO_PIN_RESET = LL_GPIO_PIN_RESET,   /*!< Pin reset (low level) */
    HAL_GPIO_PIN_SET   = LL_GPIO_PIN_SET      /*!< Pin set (high level) */
} HAL_GPIO_PinStateTypeDef;
/**
  * @}
  */ /* HAL_GPIO_EC_PIN_STATE */

/**
  * @}
  */ /* GPIO_HAL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPIO_HAL_Exported_Macros GPIO HAL Exported Macros
  * @brief    GPIO HAL Exported Macros
  * @{
  */

/** @defgroup GPIO_HAL_EM_Assert GPIO HAL Assert
  * @brief    GPIO HAL Assert
  * @{
  */

/**
  * @brief  The HAL_GPIO_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_GPIO_CHECK_PARAM
#define TAE32_USE_HAL_GPIO_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_GPIO_CHECK_PARAM != 1) && (TAE32_USE_HAL_GPIO_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_GPIO_CHECK_PARAM
#define TAE32_USE_HAL_GPIO_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_GPIO_CHECK_PARAM */

/**
  * @brief  The HAL_GPIO_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_GPIO_PARAM_CHECK(expression)       \
        if (TAE32_USE_HAL_GPIO_CHECK_PARAM) {  \
            expression;                       \
        }

/**
  * @brief  Check GPIO instance.
  * @param  instance  GPIO instance
  * @return None
  */
#define IS_HAL_GPIO_ALL_INSTANCE(instance)    IS_GPIO_ALL_INSTANCE(instance)

/**
  * @brief  Check GPIO pin mask.
  * @param  val  GPIO pin mask
  * @return None
  */
#define IS_HAL_GPIO_PIN(val)                  (((val) & 0xFFFFUL) != 0U)

/**
  * @}
  */ /* GPIO_HAL_EM_Assert */
/**
  * @}
  */ /* GPIO_HAL_Exported_Macros */

/* Exported Types ------------------------------------------------------------*/
/** @defgroup GPIO_HAL_Exported_Types GPIO HAL Exported Types
  * @brief    GPIO HAL module exported types.
  * @{
  */

/**
  * @brief  GPIO Init structure definition
  * @note   This structure is used to configure GPIO pins.
  */
typedef struct
{
    uint32_t                Pin;        /*!< Specifies the GPIO pins to be configured.
                                          @ref HAL_GPIO_EC_PIN */
    HAL_GPIO_ModeTypeDef    Mode;       /*!< Specifies the output/interrupt mode for the selected pins.
                                          @ref HAL_GPIO_EC_OUTPUT @ref HAL_GPIO_EC_INT_MODE */
    HAL_GPIO_PullTypeDef    Pull;       /*!< Specifies the pull-up/pull-down for the selected pins.
                                          @ref HAL_GPIO_EC_PULL */
    HAL_GPIO_SpeedTypeDef   Speed;      /*!< Specifies the speed for the selected pins.
                                          @ref HAL_GPIO_EC_SPEED */
    HAL_GPIO_AFTypeDef      Alternate;  /*!< Specifies the alternate function to be connected.
                                          @ref HAL_GPIO_EC_AF */
} HAL_GPIO_InitTypeDef;

/**
  * @}
  */ /* GPIO_HAL_Exported_Types */

/* Exported Functions --------------------------------------------------------*/
/** @defgroup GPIO_HAL_Exported_Functions GPIO HAL Exported Functions
  * @brief    GPIO HAL Exported Functions
  * @{
  */

/** @defgroup GPIO_HAL_EF_Init Initialization and De-initialization Functions
  * @brief Functions to initialize and de-initialize GPIO.
  * @{
  */


HAL_StatusTypeDef HAL_GPIO_Init(GPIO_TypeDef *GPIOx, const HAL_GPIO_InitTypeDef *pInit);
HAL_StatusTypeDef HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t Pin);

/**
  * @}
  */ /* GPIO_HAL_EF_Init */

/** @defgroup GPIO_HAL_EF_Data Data Access Functions
  * @brief    Functions to read/write GPIO data.
  * @{
  */


void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t PinMask);
HAL_GPIO_PinStateTypeDef HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t PinMask);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t PinMask, HAL_GPIO_PinStateTypeDef PinState);



/**
  * @}
  */ /* GPIO_HAL_EF_Data */

/** @defgroup GPIO_HAL_EF_IRQ Interrupt Control Functions
  * @brief    Functions to control GPIO interrupts.
  * @{
  */

void HAL_GPIO_EXTI_IRQHandler(GPIO_TypeDef *GPIOx, uint32_t Pin);
void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint32_t Pin);

/**
  * @}
  */ /* GPIO_HAL_EF_IRQ */

/**
  * @}
  */ /* GPIO_HAL_Exported_Functions */

/**
  * @}
  */ /* GPIO_HAL */

#endif /* GPIO */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_GPIO_H_ */