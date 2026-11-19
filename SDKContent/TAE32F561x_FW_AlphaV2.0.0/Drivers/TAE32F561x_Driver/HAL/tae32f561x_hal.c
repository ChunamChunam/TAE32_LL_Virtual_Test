/**
  ******************************************************************************
  * @file    tae32f561x_hal.c
  * @author  Tai-Action SD Team
  * @brief   HAL module driver.
  *          This is the common part of the HAL initialization
  *
  @verbatim
    ==============================================================================
                     ##### How to use this driver #####
    ==============================================================================
      [..]
      The common HAL driver contains a set of generic and common APIs that can be
      used by the PPP peripheral drivers and the user to start using the HAL.
      [..]
      The HAL contains two APIs' categories:
           (+) Common HAL APIs
           (+) Services HAL APIs
  @endverbatim
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


/** @defgroup TAE32F561x_HAL_Driver
  * @{
  */

#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
  
/** @defgroup TAE32F561x_HAL
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup TAE32F561x_HAL_Private_Macros TAE32F561x HAL Private Macros
  * @brief    TAE32F561x HAL Private Macros
  * @{
  */

/**
  * @brief  Judge is Tick frequency or not
  * @param  FREQ Freq to be judged
  * @retval 0 isn't Tick frequency
  * @retval 1 is Tick frequency
  */
#define IS_TICKFREQ(FREQ)   (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                             ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                             ((FREQ) == HAL_TICK_FREQ_1KHZ))

/**
  * @}
  */


/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/** @defgroup TAE32F561x_HAL_Private_Variables TAE32F561x HAL Private Variables
  * @brief    TAE32F561x HAL Private Variables
  * @{
  */

/**
  * @brief SysTick counter
  */
volatile uint32_t uwTick;

#ifndef TAE32_USE_HAL_TICK_INT_PRIORITY
#define TAE32_USE_HAL_TICK_INT_PRIORITY HAL_TICK_INT_LOWEST_PRIORITY
#endif /* TAE32_USE_HAL_TICK_INT_PRIORITY */

/**
  * @brief SysTick interrupt priority
  */
uint32_t uwTickPrio = TAE32_USE_HAL_TICK_INT_PRIORITY;

/**
  * @brief SysTick interrupt frequency
  */
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup TAE32F561x_HAL_Exported_Functions TAE32F561x HAL Exported Functions
  * @brief    TAE32F561x HAL Exported Functions
  * @{
  */

/** @defgroup TAE32F561x_HAL_EF_Initialization TAE32F561x Initialization and de-initialization Functions
 *  @brief    Initialization and de-initialization functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..]  This section provides functions allowing to:
      (+) Initializes the EFlash interface, the NVIC allocation and initial clock
          configuration. It initializes the systick also when timeout is needed
          and the backup domain when enabled.
      (+) de-Initializes common part of the HAL.
      (+) Configure The time base source to have 1ms time base with a dedicated
          Tick interrupt priority.
        (++) SysTick timer is used by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
        (++) Time base configuration function (HAL_InitTick ()) is called automatically
             at the beginning of the program after reset by HAL_Init()
        (++) Source of time base is configured to generate interrupts at regular
             time intervals. Care must be taken if HAL_Delay() is called from a
             peripheral ISR process, the Tick interrupt line must have higher priority
            (numerically lower) than the peripheral interrupt. Otherwise the caller
            ISR process will be blocked.
        (++) functions affecting time base configurations are declared as __WEAK
             to make override possible in case of other implementations in user file.
@endverbatim
  * @{
  */

/**
  * @brief  This function is used to initialize the HAL Library; it must be the first
  *         instruction to be executed in the main program (before to call any other
  *         HAL function), it performs the following:
  *           Configure the EFlash prefetch.
  *           Configures the SysTick to generate an interrupt each 1 millisecond,
  *           which is clocked by the LSI (at this stage, the clock is not yet
  *           configured and thus the system is running from the internal LSI at 32 KHz).
  *           Set NVIC Group Priority to 4.
  *           Calls the HAL_MspInit() callback function defined in user file
  *           "tae32f561x_hal_msp.c" to do the global low level hardware initialization
  *
  * @note   SysTick is used as time base for the HAL_Delay() function, the application
  *         need to ensure that the SysTick time base is always set to 1 millisecond
  *         to have correct HAL operation.
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_Init(void)
{
    HAL_StatusTypeDef ret;

#if defined(TAE32_USE_HAL_EFLASH_PREFETCH_CONFIG) && (TAE32_USE_HAL_EFLASH_PREFETCH_CONFIG == 1)
    /* Prefetch enable */
    LL_EFLASH_EnableIBusPrefetch(EFLASH);
    LL_EFLASH_DisableDBusPrefetch(EFLASH);
#elif (defined(TAE32_USE_HAL_EFLASH_PREFETCH_CONFIG) && (TAE32_USE_HAL_EFLASH_PREFETCH_CONFIG == 2))
    /* Prefetch disable */
    LL_EFLASH_DisableIBusPrefetch(EFLASH);
    LL_EFLASH_DisableDBusPrefetch(EFLASH);
#else
    /* Default */
#endif  /* TAE32_USE_HAL_FLASH_PREFETCH_CONFIG */

    /* Set Interrupt Group Priority */
    HAL_NVIC_SetPriorityGrouping(HAL_NVIC_PRIORITYGROUP_4);

    /* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
    ret = HAL_InitTick(TAE32_USE_HAL_TICK_INT_PRIORITY);

    /* Init the low level hardware */
    HAL_MspInit();

    /* Return function status */
    return ret;
}

/**
  * @brief This function de-Initializes common part of the HAL and stops the systick of time base.
  * @note This function is optional.
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DeInit(void)
{
    /* Reset of all peripherals */
    // HAL_RCU_AllPeriphRstAssert();///TODO:move to HAL_MspDeInit

    /* De-Init the low level hardware */
    HAL_MspDeInit();

    /* Return function status */
    return HAL_OK;
}

/**
  * @brief  Initialize the MSP
  * @param  None
  * @retval None
  */
__WEAK void HAL_MspInit(void)
{
    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the MSP
  * @param  None
  * @retval None
  */
__WEAK void HAL_MspDeInit(void)
{
    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_MspDeInit could be implemented in the user file
     */
}


/**
  * @brief This function configures the source of the time base.
  *        The time source is configured to have 1ms time base with a dedicated
  *        Tick interrupt priority.
  * @note This function is called automatically at the beginning of program after
  *       reset by HAL_Init().
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals.
  *       Care must be taken if HAL_Delay() is called from a peripheral ISR process,
  *       The SysTick interrupt must have higher priority (numerically lower)
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __WEAK to be overwritten in case of other
  *       implementation  in user file.
  * @param TickPriority Tick interrupt priority.
  * @retval HAL status
  */
__WEAK HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    /* Configure the SysTick to have interrupt in 1ms time basis*/
    if (!(uint32_t)uwTickFreq || HAL_SYSTICK_Config(SystemCoreClockGet() / (1000U / uwTickFreq)) != 0U) {
        return HAL_FAILED;
    }

    /* Configure the SysTick IRQ priority */
    if (TickPriority < (1UL << __NVIC_PRIO_BITS)) {
        HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);
        uwTickPrio = TickPriority;
    } else {
        return HAL_ERROR;
    }

    /* Return function status */
    return HAL_OK;
}

/**
  * @}
  */ /* TAE32F561x_HAL_EF_Initialization */


/** @defgroup TAE32F561x_HAL_EF_Control TAE32F561x HAL Control functions
  * @brief    TAE32F561x HAL Control functions
  *
@verbatim
 ===============================================================================
                      ##### HAL Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the HAL API driver version
      (+) Get the unique device identifier
@endverbatim
  * @{
  */

/**
  * @brief This function is called to increment a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *      implementations in user file.
  * @param  None
  * @retval None
  */
__WEAK void HAL_IncTick(void)
{
    uwTick += uwTickFreq;
}

/**
  * @brief Provides a tick value in millisecond
  * @note  This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param  None
  * @retval tick value
  */
__WEAK uint32_t HAL_GetTick(void)
{
    return uwTick;
}

/**
  * @brief This function returns a tick priority
  * @param  None
  * @retval tick priority
  */
uint32_t HAL_GetTickPrio(void)
{
    return uwTickPrio;
}

/**
  * @brief  Set new tick frequency
  * @param  Freq New tick frequency
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq)
{
    HAL_StatusTypeDef status = HAL_OK;
    HAL_TickFreqTypeDef prevTickFreq;

    ASSERT_FUNC_PARAM(IS_TICKFREQ(Freq));

    if (!IS_TICKFREQ(Freq)) {
        return HAL_INVALID;
    }

    if (uwTickFreq != Freq) {
        /* Back up uwTickFreq frequency */
        prevTickFreq = uwTickFreq;

        /* pdate uwTickFreq global variable used by HAL_InitTick() */
        uwTickFreq = Freq;

        /* Apply the new tick frequency  */
        status = HAL_InitTick(uwTickPrio);

        if (status == HAL_FAILED) {
            /* Restore previous tick frequency */
            uwTickFreq = prevTickFreq;
        }
    }

    return status;
}

/**
  * @brief  Get tick frequency
  * @param  None
  * @retval tick period in Hz
  */
HAL_TickFreqTypeDef HAL_GetTickFreq(void)
{
    return uwTickFreq;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
__WEAK void HAL_Delay(uint32_t Delay)
{
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = Delay;

    /* Add a freq to guarantee minimum wait */
    if (!wait) {
        wait += (uint32_t)(uwTickFreq);
    }

    while ((HAL_GetTick() - tickstart) < wait) {
    }
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param  None
  * @retval None
  */
__WEAK void HAL_SuspendTick(void)
{
    /* Disable SysTick Interrupt */
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param  None
  * @retval None
  */
__WEAK void HAL_ResumeTick(void)
{
    /* Enable SysTick Interrupt */
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Get the HAL revision
  * @param  None
  * @retval version 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t HAL_GetHalVersion(void)
{
    return __TAE32F561x_HAL_VERSION;
}

/**
  * @}
  */ /* TAE32F561x_HAL_EF_Control */


/* Private Functions ---------------------------------------------------------*/


/**
  * @}
  */ /* TAE32F561x_HAL */

#endif /* HAL_MODULE_ENABLED */

/**
  * @}
  */ /* TAE32F561x_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

