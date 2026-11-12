/**
  ******************************************************************************
  * @file    tae32g58xx_ll_gpio.h
  * @author  Tai-Action SD Team
  * @brief   Header file of GPIO LL module.
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

#ifndef _TAE32G58XX_LL_GPIO_H_
#define _TAE32G58XX_LL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


#if defined (GPIOA) || defined (GPIOB) || defined (GPIOC) || defined (GPIOD) || defined (GPIOE) || defined (GPIOF)

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup GPIO_LL GPIO LL
  * @brief    GPIO LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Constants GPIO LL Exported Constants
  * @brief    GPIO LL Exported Constants
  * @{
  */

/** @defgroup GPIO_LL_EC_PIN Pin
  * @brief    Defines the GPIO pin identifiers.
  * @{
  */
#define LL_GPIO_PIN_0                  0x0001UL  /*!< Pin 0 selected */
#define LL_GPIO_PIN_1                  0x0002UL  /*!< Pin 1 selected */
#define LL_GPIO_PIN_2                  0x0004UL  /*!< Pin 2 selected */
#define LL_GPIO_PIN_3                  0x0008UL  /*!< Pin 3 selected */
#define LL_GPIO_PIN_4                  0x0010UL  /*!< Pin 4 selected */
#define LL_GPIO_PIN_5                  0x0020UL  /*!< Pin 5 selected */
#define LL_GPIO_PIN_6                  0x0040UL  /*!< Pin 6 selected */
#define LL_GPIO_PIN_7                  0x0080UL  /*!< Pin 7 selected */
#define LL_GPIO_PIN_8                  0x0100UL  /*!< Pin 8 selected */
#define LL_GPIO_PIN_9                  0x0200UL  /*!< Pin 9 selected */
#define LL_GPIO_PIN_10                 0x0400UL  /*!< Pin 10 selected */
#define LL_GPIO_PIN_11                 0x0800UL  /*!< Pin 11 selected */
#define LL_GPIO_PIN_12                 0x1000UL  /*!< Pin 12 selected */
#define LL_GPIO_PIN_13                 0x2000UL  /*!< Pin 13 selected */
#define LL_GPIO_PIN_14                 0x4000UL  /*!< Pin 14 selected */
#define LL_GPIO_PIN_15                 0x8000UL  /*!< Pin 15 selected */
#define LL_GPIO_PIN_ALL                0xFFFFUL  /*!< All pins selected */
/**
  * @}
  */ /* GPIO_LL_EC_PIN */

/** @defgroup GPIO_LL_EC_AF Alternate Function
  * @brief    Defines the alternate function selection values.
  * @{
  */
#define LL_GPIO_AF_0                   0x00000000UL  /*!< Input mode */
#define LL_GPIO_AF_1                   0x00000001UL  /*!< Output mode */
#define LL_GPIO_AF_2                   0x00000002UL  /*!< Alternate function 2 */
#define LL_GPIO_AF_3                   0x00000003UL  /*!< Alternate function 3 */
#define LL_GPIO_AF_4                   0x00000004UL  /*!< Alternate function 4 */
#define LL_GPIO_AF_5                   0x00000005UL  /*!< Alternate function 5 */
#define LL_GPIO_AF_6                   0x00000006UL  /*!< Alternate function 6 */
#define LL_GPIO_AF_7                   0x00000007UL  /*!< Alternate function 7 */
#define LL_GPIO_AF_8                   0x00000008UL  /*!< Alternate function 8 */
#define LL_GPIO_AF_9                   0x00000009UL  /*!< Alternate function 9 */
#define LL_GPIO_AF_10                  0x0000000AUL  /*!< Alternate function 10 */
#define LL_GPIO_AF_11                  0x0000000BUL  /*!< Alternate function 11 */
#define LL_GPIO_AF_12                  0x0000000CUL  /*!< Alternate function 12 */
#define LL_GPIO_AF_13                  0x0000000DUL  /*!< Alternate function 13 */
#define LL_GPIO_AF_14                  0x0000000EUL  /*!< Alternate function 14 */
#define LL_GPIO_AF_15                  0x0000000FUL  /*!< Analog mode */
/**
  * @}
  */ /* GPIO_LL_EC_AF */

/** @defgroup GPIO_LL_EC_OUTPUT Output Type
  * @brief    Defines the output type (push-pull or open-drain).
  * @{
  */
#define LL_GPIO_OUTPUT_PUSHPULL        0x00000000UL  /*!< Push-pull output */
#define LL_GPIO_OUTPUT_OPENDRAIN       0x00000001UL  /*!< Open-drain output */
/**
  * @}
  */ /* GPIO_LL_EC_OUTPUT */

/** @defgroup GPIO_LL_EC_SPEED Output Speed
  * @brief    Defines the output speed.
  * @{
  */
#define LL_GPIO_SPEED_FREQ_LOW         0x00000000UL  /*!< Low speed */
#define LL_GPIO_SPEED_FREQ_HIGH        0x00000001UL  /*!< High speed */
/**
  * @}
  */ /* GPIO_LL_EC_SPEED */

/** @defgroup GPIO_LL_EC_PULL Pull-up/Pull-down
  * @brief    Defines the pull-up/pull-down configuration.
  * @{
  */
#define LL_GPIO_PULL_NO                0x00000000UL  /*!< No pull */
#define LL_GPIO_PULL_UP                0x00000002UL  /*!< Pull-up */
#define LL_GPIO_PULL_DOWN              0x00000001UL  /*!< Pull-down */
/**
  * @}
  */ /* GPIO_LL_EC_PULL */

/** @defgroup GPIO_LL_EC_INT_MODE Interrupt Mode
  * @brief    Defines the interrupt trigger mode.
  * @{
  */
#define LL_GPIO_INT_MODE_CLOSE         0x00000000UL  /*!< Interrupt disabled */
#define LL_GPIO_INT_MODE_FALLING       0x00000001UL  /*!< Falling edge trigger */
#define LL_GPIO_INT_MODE_RISING        0x00000002UL  /*!< Rising edge trigger */
#define LL_GPIO_INT_MODE_RISING_FALLING 0x00000003UL /*!< Both edges trigger */
/**
  * @}
  */ /* GPIO_LL_EC_INT_MODE */

/** @defgroup GPIO_LL_EC_DRV_CAP Drive Capability
  * @brief    Defines the output drive capability.
  * @{
  */
#define LL_GPIO_DRV_CAP_LOW            0x00000000UL  /*!< Low drive capability */
#define LL_GPIO_DRV_CAP_MED            0x00000001UL  /*!< Medium drive capability */
#define LL_GPIO_DRV_CAP_HIGH           0x00000002UL  /*!< High drive capability */
#define LL_GPIO_DRV_CAP_VERY_HIGH      0x00000003UL  /*!< Very high drive capability */
/**
  * @}
  */ /* GPIO_LL_EC_DRV_CAP */

/** @defgroup GPIO_LL_EC_PIN_STATE Pin State
  * @brief    Defines the pin state values.
  * @{
  */
#define LL_GPIO_PIN_RESET              0x00000000UL  /*!< Pin reset (low level) */
#define LL_GPIO_PIN_SET                0x00000001UL  /*!< Pin set (high level) */
/**
  * @}
  */ /* GPIO_LL_EC_PIN_STATE */

/**
  * @}
  */ /* GPIO_LL_Exported_Constants */


/* Exported Functions --------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Functions GPIO LL Exported Functions
  * @brief    GPIO LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_GPIO_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_GPIO_ASSERT_INLINE_PARAM == 1)
extern void LL_GPIO_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_GPIO_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_GPIO_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_GPIO_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup GPIO_LL_EF_Configuration Configuration Functions
  * @brief    Functions to configure GPIO pins.
  * @{
  */

/**
  * @brief  Set GPIO pin output type.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @param  OutputType Output type @ref GPIO_LL_EC_OUTPUT
  * @return None
  */
__STATIC_INLINE void LL_GPIO_SetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t PinMask, uint32_t OutputType)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    if (OutputType == LL_GPIO_OUTPUT_OPENDRAIN) {
        SET_BIT(GPIOx->ODR, PinMask);
    } else {
        CLEAR_BIT(GPIOx->ODR, PinMask);
    }
}

/**
  * @brief  Get GPIO pin output type.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return Output type @ref GPIO_LL_EC_OUTPUT
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinOutputType(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return (READ_BIT(GPIOx->ODR, Pin) != 0U) ? LL_GPIO_OUTPUT_OPENDRAIN : LL_GPIO_OUTPUT_PUSHPULL;
}

/**
  * @brief  Set GPIO pin speed.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @param  Speed Speed value @ref GPIO_LL_EC_SPEED
  * @return None
  */
__STATIC_INLINE void LL_GPIO_SetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Speed)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    if (Speed == LL_GPIO_SPEED_FREQ_HIGH) {
        SET_BIT(GPIOx->OSR, Pin);
    } else {
        CLEAR_BIT(GPIOx->OSR, Pin);
    }
}

/**
  * @brief  Get GPIO pin speed.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return Speed value @ref GPIO_LL_EC_SPEED
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinSpeed(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return (READ_BIT(GPIOx->OSR, Pin) != 0U) ? LL_GPIO_SPEED_FREQ_HIGH : LL_GPIO_SPEED_FREQ_LOW;
}

/**
  * @brief  Set GPIO pin pull-up/pull-down.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @param  Pull Pull configuration @ref GPIO_LL_EC_PULL
  * @return None
  */
__STATIC_INLINE void LL_GPIO_SetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    uint32_t pin_num = POSITION_VAL(Pin);
    MODIFY_REG(GPIOx->UDR, 0x3UL << (2 * pin_num), (Pull & 0x3UL) << (2 * pin_num));
}

/**
  * @brief  Get GPIO pin pull-up/pull-down.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return Pull configuration @ref GPIO_LL_EC_PULL
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinPull(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    uint32_t pin_num = POSITION_VAL(Pin);
    return (READ_REG(GPIOx->UDR) >> (2 * pin_num)) & 0x3UL;
}

/**
  * @brief  Set alternate function for the selected pin.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @param  Alternate Alternate function @ref GPIO_LL_EC_AF
  * @return None
  */
__STATIC_INLINE void LL_GPIO_SetAFPin(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    uint32_t pin_num = POSITION_VAL(Pin);
    if (pin_num < 8UL) {
        MODIFY_REG(GPIOx->MR0, 0xFUL << (4UL * pin_num),
                   (Alternate & 0xFUL) << (4UL * pin_num));
}
    else {
        MODIFY_REG(GPIOx->MR1, 0xFUL << (4UL * (pin_num % 8UL)),
                   (Alternate & 0xFUL) << (4UL * (pin_num % 8UL)));
}
}

/**
  * @brief  Get alternate function for the selected pin.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return Alternate function @ref GPIO_LL_EC_AF
  */
__STATIC_INLINE uint32_t LL_GPIO_GetAFPin(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    uint32_t pin_num = POSITION_VAL(Pin);
    if (pin_num < 8UL) {
        return (READ_REG(GPIOx->MR0) >> (4UL * pin_num)) & 0xFUL;
}
    else {
        return (READ_REG(GPIOx->MR1) >> (4UL * (pin_num % 8UL))) & 0xFUL;
}
}

/**
  * @brief  Enable pin synchronization.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_EnableSync(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    SET_BIT(GPIOx->SER, Pin);
}

/**
  * @brief  Disable pin synchronization.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_DisableSync(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    CLEAR_BIT(GPIOx->SER, Pin);
}

/**
  * @brief  Enable pin debounce.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_EnableDebounce(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    SET_BIT(GPIOx->DER, Pin);
}

/**
  * @brief  Disable pin debounce.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_DisableDebounce(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    CLEAR_BIT(GPIOx->DER, Pin);
}

/**
  * @brief  Enable input hysteresis.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_EnableInputHyst(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    SET_BIT(GPIOx->IHR, Pin);
}

/**
  * @brief  Disable input hysteresis.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_DisableInputHyst(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    CLEAR_BIT(GPIOx->IHR, Pin);
}

/**
  * @brief  Set pin drive capability.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @param  DrvCap Drive capability @ref GPIO_LL_EC_DRV_CAP
  * @return None
  */
__STATIC_INLINE void LL_GPIO_SetDrvCap(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t DrvCap)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    if (DrvCap & 0x1UL) {
        SET_BIT(GPIOx->DHR, Pin);
    } else {
        CLEAR_BIT(GPIOx->DHR, Pin);
    }
    if (DrvCap & 0x2UL) {
        SET_BIT(GPIOx->DHR, (Pin << 16UL));
    } else {
        CLEAR_BIT(GPIOx->DHR, (Pin << 16UL));
    }
}

/**
  * @brief  Set interrupt mode.
  * @param  GPIOx GPIO port
  * @param  PinNum Pin number (0-15)
  * @param  Mode Interrupt mode @ref GPIO_LL_EC_INT_MODE
  * @return None
  */
__STATIC_INLINE void LL_GPIO_SetIntMode(GPIO_TypeDef *GPIOx, uint32_t PinNum, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    MODIFY_REG(GPIOx->IMR, 0x3UL << (2 * PinNum), (Mode & 0x3UL) << (2 * PinNum));
}

/**
  * @brief  Enable GPIO interrupt.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_EnableIT(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    SET_BIT(GPIOx->IER, Pin);
}

/**
  * @brief  Disable GPIO interrupt.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_DisableIT(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    CLEAR_BIT(GPIOx->IER, Pin);
}

/**
  * @brief  Clear GPIO interrupt pending flag.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @return None
  */
__STATIC_INLINE void LL_GPIO_ClearIntPending(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    WRITE_REG(GPIOx->ISR, Pin);
}

/**
  * @brief  Check GPIO interrupt pending flag.
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @retval 0: No pending, 1: Pending
  */
__STATIC_INLINE uint32_t LL_GPIO_IsIntPending(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return (READ_BIT(GPIOx->ISR, Pin) != 0U) ? 1UL : 0UL;
}

/**
  * @brief  Check if GPIO pin interrupt is enabled
  * @param  GPIOx GPIO port
  * @param  Pin GPIO pin @ref GPIO_LL_EC_PIN
  * @retval 0: Interrupt disabled, 1: Interrupt enabled
  */
__STATIC_INLINE uint32_t LL_GPIO_IsIntEnable(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return (READ_BIT(GPIOx->IER, Pin) != 0U) ? 1UL : 0UL;
}

/**
  * @brief  Read GPIO interrupt enable register.
  * @param  GPIOx GPIO port
  * @return Value of IER register
  */
__STATIC_INLINE uint32_t LL_GPIO_ReadIER(const GPIO_TypeDef *GPIOx)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return READ_REG(GPIOx->IER);
}

/**
  * @brief  Read GPIO interrupt status register.
  * @param  GPIOx GPIO port
  * @return Value of ISR register
  */
__STATIC_INLINE uint32_t LL_GPIO_ReadISR(const GPIO_TypeDef *GPIOx)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return READ_REG(GPIOx->ISR);
}

/**
  * @}
  */ /* GPIO_LL_EF_Configuration */

/** @defgroup GPIO_LL_EF_Data Data Access Functions
  * @brief    Functions to read/write GPIO data.
  * @{
  */

/**
  * @brief  Read input port.
  * @param  GPIOx GPIO port
  * @return Input port value
  */
__STATIC_INLINE uint32_t LL_GPIO_ReadInputPort(const GPIO_TypeDef *GPIOx)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return READ_REG(GPIOx->DIR);
}

/**
  * @brief  Check if input pin is set.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @retval 0: Pin low, 1: Pin high
  */
__STATIC_INLINE uint32_t LL_GPIO_IsInputPinSet(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return (READ_BIT(GPIOx->DIR, PinMask) != 0U) ? 1UL : 0UL;
}

/**
  * @brief  Write output port.
  * @param  GPIOx GPIO port
  * @param  PortValue Value to write
  * @return None
  */
__STATIC_INLINE void LL_GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    WRITE_REG(GPIOx->DOR, PortValue);
}

/**
  * @brief  Read output port.
  * @param  GPIOx GPIO port
  * @return Output port value
  */
__STATIC_INLINE uint32_t LL_GPIO_ReadOutputPort(const GPIO_TypeDef *GPIOx)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return READ_REG(GPIOx->DOR);
}

/**
  * @brief  Check if output pin is set.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @retval 0: Pin low, 1: Pin high
  */
__STATIC_INLINE uint32_t LL_GPIO_IsOutputPinSet(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return (READ_BIT(GPIOx->DOR, PinMask) != 0U) ? 1UL : 0UL;
}

/**
  * @brief  Set output pin.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @return None
  */
__STATIC_INLINE void LL_GPIO_SetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    WRITE_REG(GPIOx->BSR, (PinMask << GPIOA_BSR_BSn_Pos));
}

/**
  * @brief  Reset output pin.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @return None
  */
__STATIC_INLINE void LL_GPIO_ResetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    WRITE_REG(GPIOx->BSR, ((uint32_t)(PinMask) << GPIOA_BSR_BRn_Pos));
}

/**
  * @brief  Toggle output pin.
  * @param  GPIOx GPIO port
  * @param  PinMask Pin mask
  * @return None
  */
__STATIC_INLINE void LL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    uint32_t dor = READ_REG(GPIOx->DOR);
    WRITE_REG(GPIOx->BSR, (((dor & PinMask) << GPIOA_BSR_BRn_Pos) |
                           ((~dor & PinMask) << GPIOA_BSR_BSn_Pos)));
}

/**
  * @brief  Get pin driving capability level (
  * @param  GPIOx GPIO port
  * @param  Pin Pin mask @ref GPIO_LL_EC_PIN
  * @retval Level @ref GPIO_LL_EC_DRV_CAP
  *         0=LOW, 1=MED, 2=HIGH, 3=VERY_HIGH
  */
__STATIC_INLINE uint32_t LL_GPIO_GetDrvCap(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    uint32_t drv = 0UL;

    if ((READ_REG(GPIOx->DHR) & Pin) != 0UL) {
        drv |= 0x1UL;                       /* DRx field (low 16 bits) -> level bit0 */
    }
    if ((READ_REG(GPIOx->DHR) & (Pin << 16UL)) != 0UL) {
        drv |= 0x2UL;                       /* DRy field (high 16 bits) -> level bit1 */
    }
    return drv;
}

/**
  * @brief  Get pin input hysteresis enable status.
  * @param  GPIOx GPIO port
  * @param  Pin Pin mask @ref GPIO_LL_EC_PIN
  * @retval 1=Hysteresis enabled, 0=Hysteresis disabled
  */
__STATIC_INLINE uint32_t LL_GPIO_GetInputHyst(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return ((READ_REG(GPIOx->IHR) & Pin) != 0UL) ? 1UL : 0UL;
}

/**
  * @brief  Get pin synchronization enable status.
  * @param  GPIOx GPIO port
  * @param  Pin Pin mask @ref GPIO_LL_EC_PIN
  * @retval 1=Synchronization enabled, 0=Synchronization disabled
  */
__STATIC_INLINE uint32_t LL_GPIO_GetSync(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return ((READ_REG(GPIOx->SER) & Pin) != 0UL) ? 1UL : 0UL;
}

/**
  * @brief  Get pin debounce enable status.
  * @param  GPIOx GPIO port
  * @param  Pin Pin mask @ref GPIO_LL_EC_PIN
  * @retval 1=Debounce enabled, 0=Debounce disabled
  */
__STATIC_INLINE uint32_t LL_GPIO_GetDebounce(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    ASSERT_INLINE_PARAM(IS_GPIO_ALL_INSTANCE(GPIOx));

    return ((READ_REG(GPIOx->DER) & Pin) != 0UL) ? 1UL : 0UL;
}

/**
  * @}
  */ /* GPIO_LL_EF_Data */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* GPIO_LL_Exported_Functions */

/**
  * @}
  */ /* GPIO_LL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */

#endif /* GPIO */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_GPIO_H_ */
