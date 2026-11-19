/**
  ******************************************************************************
  * @file    tae32f561x_hal_gpio.c
  * @author  Tai-Action SD Team
  * @brief   GPIO HAL module driver.
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

/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_hal.h"

/** @addtogroup TAE32F561x_HAL_Driver
  * @{
  */

#if defined(GPIOA) || defined(GPIOB) || defined(GPIOC)  || defined(GPIOD)  || defined(GPIOE)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_GPIO_MODULE_ENABLED) && (HAL_GPIO_MODULE_ENABLED == 1)

/** @defgroup GPIO_HAL GPIO Hardware Abstraction Layer
  * @brief HAL layer driver for GPIO module.
  * @{
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup GPIO_HAL_EF_Init Initialization and De-initialization Functions
  * @{
  */

/**
  * @brief  Initialize GPIO pins according to the specified parameters.
  * @param  GPIOx GPIO port
  * @param  pInit Pointer to HAL_GPIO_InitTypeDef structure
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPIO_Init(GPIO_TypeDef *GPIOx, const HAL_GPIO_InitTypeDef *pInit)
{
    uint32_t pinpos = 0U;
    uint32_t currentpin;
    uint32_t alternate;

    /* Check NULL pointers (always returns error code, independent of assert config) */
    if ((!IS_HAL_GPIO_ALL_INSTANCE(GPIOx)) || (pInit == NULL)) {
        return HAL_INVALID;
    }
    
    if (!IS_HAL_GPIO_PIN(pInit->Pin)) {
        return HAL_INVALID;
    }

    if (pInit->Alternate > 15U) {
        return HAL_INVALID;
    }

    uint32_t exti_cfg = (pInit->Mode & HAL_GPIO_MODE_EXTI_MASK) >> HAL_GPIO_MODE_EXTI_POS;
    if (exti_cfg != HAL_GPIO_MODE_IT_CLOSE) {
        if (pInit->Alternate != HAL_GPIO_AF_0) {
            return HAL_INVALID;
        }
        if ((pInit->Mode & HAL_GPIO_MODE_OUTPUT_OD) != 0U) {
            return HAL_INVALID;
        }
    }

    alternate = pInit->Alternate;

    while ((pInit->Pin >> pinpos) != 0U) {
        currentpin = pInit->Pin & (1UL << pinpos);

        if (currentpin != 0U) {
            LL_GPIO_SetAFPin(GPIOx, currentpin, alternate);

            LL_GPIO_SetPinSpeed(GPIOx, currentpin, pInit->Speed);
            LL_GPIO_SetPinOutputType(GPIOx, currentpin,
                                     (pInit->Mode & HAL_GPIO_MODE_OUTPUT_MASK) >> HAL_GPIO_MODE_OUTPUT_POS);

            LL_GPIO_SetPinPull(GPIOx, currentpin, pInit->Pull);

            LL_GPIO_SetIntMode(GPIOx, pinpos, exti_cfg);  
            LL_GPIO_ClearIntPending(GPIOx, currentpin); 

            if (exti_cfg == HAL_GPIO_MODE_IT_CLOSE) {
                LL_GPIO_DisableIT(GPIOx, currentpin);    
            } else {
                LL_GPIO_EnableIT(GPIOx, currentpin);
            }
        }

        pinpos++;
    }

    return HAL_OK;
}

/**
  * @brief  De-initialize GPIO pins to default state (analog mode).
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_HAL_EC_PIN
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    uint32_t currentpin;
    uint32_t pin_num;

    /* Check NULL pointers (always returns error code, independent of assert config) */
    if ((!IS_HAL_GPIO_ALL_INSTANCE(GPIOx))) {
        return HAL_INVALID;
    }

    if (!IS_HAL_GPIO_PIN(Pin)) {
        return HAL_INVALID;
    }

    for (pin_num = 0U; pin_num < 16U; pin_num++) {
        currentpin = 1UL << pin_num;

        if ((Pin & currentpin) != 0U) {
            LL_GPIO_SetAFPin(GPIOx, currentpin, HAL_GPIO_AF_15);

            LL_GPIO_SetPinPull(GPIOx, currentpin, HAL_GPIO_PULL_NO);
            LL_GPIO_SetPinOutputType(GPIOx, currentpin, HAL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_SetPinSpeed(GPIOx, currentpin, HAL_GPIO_SPEED_FREQ_LOW);
            LL_GPIO_ResetOutputPin(GPIOx, currentpin);

            LL_GPIO_SetIntMode(GPIOx, pin_num, LL_GPIO_INT_MODE_CLOSE);
            LL_GPIO_DisableIT(GPIOx, currentpin);
            LL_GPIO_DisableSync(GPIOx, currentpin);
            LL_GPIO_DisableDebounce(GPIOx, currentpin);
            LL_GPIO_DisableInputHyst(GPIOx, currentpin);
            LL_GPIO_SetDrvCap(GPIOx, currentpin, LL_GPIO_DRV_CAP_LOW);
        }
    }

    return HAL_OK;
}

/**
  * @}
  */

/** @defgroup GPIO_HAL_EF_Configuration Configuration Functions
  * @{
  */



/**
 * @}
 */

/** @defgroup GPIO_HAL_EF_Data Data Access Functions
  * @{
  */

/**
  * @brief  Toggle output pin.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @return None
  */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
    ASSERT_FUNC_PARAM(IS_HAL_GPIO_ALL_INSTANCE(GPIOx));
    ASSERT_FUNC_PARAM(IS_HAL_GPIO_PIN(PinMask));

    HAL_GPIO_PARAM_CHECK({
        if (!IS_HAL_GPIO_ALL_INSTANCE(GPIOx) || !IS_HAL_GPIO_PIN(PinMask)) {
            return;
        }
    });

    LL_GPIO_TogglePin(GPIOx, PinMask);
}

/**
  * @brief  Check if input pin is set.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @return Pin state
  */
HAL_GPIO_PinStateTypeDef HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
    ASSERT_FUNC_PARAM(IS_HAL_GPIO_ALL_INSTANCE(GPIOx));
    ASSERT_FUNC_PARAM(IS_HAL_GPIO_PIN(PinMask));

    HAL_GPIO_PARAM_CHECK({
        if (!IS_HAL_GPIO_ALL_INSTANCE(GPIOx) || !IS_HAL_GPIO_PIN(PinMask)) {
            return HAL_GPIO_PIN_RESET;
        }
    });

    uint32_t cur_af = LL_GPIO_GetAFPin(GPIOx, PinMask);

    if (cur_af == LL_GPIO_AF_1) {
        if (LL_GPIO_IsOutputPinSet(GPIOx, PinMask) != 0U) {
            return HAL_GPIO_PIN_SET;
        }
        else {
            return HAL_GPIO_PIN_RESET;
        }
    }
    else {
        if (LL_GPIO_IsInputPinSet(GPIOx, PinMask) != 0U) {
            return HAL_GPIO_PIN_SET;
        }
        else {
            return HAL_GPIO_PIN_RESET;
        }
    }
}

/**
  * @brief  Write output pin.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @param  PinState Pin state
  * @return None
  */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t PinMask, HAL_GPIO_PinStateTypeDef PinState)
{
        ASSERT_FUNC_PARAM(IS_HAL_GPIO_ALL_INSTANCE(GPIOx));
        ASSERT_FUNC_PARAM(IS_HAL_GPIO_PIN(PinMask));

        HAL_GPIO_PARAM_CHECK({
            if (!IS_HAL_GPIO_ALL_INSTANCE(GPIOx) || !IS_HAL_GPIO_PIN(PinMask)) {
                return;
            }
        });

    if (PinState == HAL_GPIO_PIN_SET) {
        LL_GPIO_SetOutputPin(GPIOx, PinMask);
    }
    else {
        LL_GPIO_ResetOutputPin(GPIOx, PinMask);
    }
}



/**
  * @}
  */

/** @defgroup GPIO_HAL_EF_IRQ Interrupt Control Functions
  * @{
  */



/**
  * @brief  Handle GPIO interrupt request.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref HAL_GPIO_EC_PIN
  * @return None
  * @note   This function should be called from the GPIO interrupt service routine.
  */
void HAL_GPIO_EXTI_IRQHandler(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_FUNC_PARAM(IS_HAL_GPIO_ALL_INSTANCE(GPIOx));

    HAL_GPIO_PARAM_CHECK({
        if (!IS_HAL_GPIO_ALL_INSTANCE(GPIOx)) {
            return;
        }
    });

    if ((LL_GPIO_IsIntEnable(GPIOx, Pin) != 0U) &&
        (LL_GPIO_IsIntPending(GPIOx, Pin) != 0U)) {
        LL_GPIO_ClearIntPending(GPIOx, Pin);
        HAL_GPIO_EXTI_Callback(GPIOx, Pin);
    }
}


/**
  * @brief  GPIO external trigger callback (weak).
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin
  * @return None
  */
__WEAK void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    /* Prevent unused argument(s) compilation warning */
    (void)(GPIOx);
    (void)(Pin);
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_GPIO_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* GPIO */

/**
  * @}
  */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/
