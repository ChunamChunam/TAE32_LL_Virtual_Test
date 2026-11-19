/**
  ******************************************************************************
  * @file    tae32f561x_hal_cortex.c
  * @author  Tai-Action SD Team
  * @brief   CORTEX HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORTEX:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================

    [..]
    *** How to configure Interrupts using CORTEX HAL driver ***
    ===========================================================
    [..]
    This section provides functions allowing to configure the NVIC interrupts (IRQ).
    The Cortex-M4 exceptions are managed by CMSIS functions.

    (#) Configure the NVIC Priority Grouping using HAL_NVIC_SetPriorityGrouping()
        function according to the following table.
    (#) Configure the priority of the selected IRQ Channels using HAL_NVIC_SetPriority().
    (#) Enable the selected IRQ Channels using HAL_NVIC_EnableIRQ().
    (#) please refer to programming manual for details in how to configure priority.

     -@- When the NVIC_PRIORITYGROUP_0 is selected, IRQ preemption is no more possible.
         The pending IRQ priority will be managed only by the sub priority.

     -@- IRQ priority order (sorted by highest to lowest priority):
        (+@) Lowest preemption priority
        (+@) Lowest sub priority
        (+@) Lowest hardware priority (IRQ number)

    [..]
    *** How to configure Systick using CORTEX HAL driver ***
    ========================================================
    [..]
    Setup SysTick Timer for time base.

   (+) The HAL_SYSTICK_Config()function calls the SysTick_Config() function which
       is a CMSIS function that:
        (++) Configures the SysTick Reload register with value passed as function parameter.
        (++) Configures the SysTick IRQ priority to the lowest value 0x0F.
        (++) Resets the SysTick Counter register.
        (++) Configures the SysTick Counter clock source to be Core Clock Source (HCLK).
        (++) Enables the SysTick Interrupt.
        (++) Starts the SysTick Counter.

   (+) You can change the SysTick Clock source to be HCLK_Div8 by calling the function
       HAL_SYSTICK_CLKSOURCEConfig(HAL_SYSTICK_CLKSOURCE_HCLK_DIV8) just after the
       HAL_SYSTICK_Config() function call. The HAL_SYSTICK_CLKSOURCEConfig() function is defined below.

   (+) You can change the SysTick IRQ priority by calling the
       HAL_NVIC_SetPriority(SysTick_IRQn,...) function just after the HAL_SYSTICK_Config() function
       call. The HAL_NVIC_SetPriority() call the NVIC_SetPriority() function which is a CMSIS function.

   (+) To adjust the SysTick time base, use the following formula:

       Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
       (++) Reload Value is the parameter to be passed for HAL_SYSTICK_Config() function
       (++) Reload Value should not exceed 0xFFFFFF

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


/**
  * @addtogroup TAE32F561x_HAL_Driver
  * @{
  */

#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_CORTEX_MODULE_ENABLED) && (HAL_CORTEX_MODULE_ENABLED == 1)

/** @defgroup CORTEX_HAL CORTEX HAL
  * @brief    CORTEX HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup CORTEX_HAL_Private_Macros CORTEX HAL Private Macros
  * @brief    CORTEX HAL Private Macros
  * @{
  */

/**
  * @brief  Judge is SYSTICK clock source or not
  * @param  SOURCE clock source to judge
  * @retval 0 isn't SYSTICK clock source
  * @retval 1 is SYSTICK clock source
  */
#define IS_SYSTICK_CLK_SOURCE(SOURCE)           (((SOURCE) == HAL_SYSTICK_CLKSOURCE_HCLK_DIV8) || ((SOURCE) == HAL_SYSTICK_CLKSOURCE_HCLK))

/**
  * @}
  */ /* CORTEX_HAL_Private_Macros */



/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CORTEX_HAL_Exported_Functions CORTEX HAL Exported Functions
  * @brief    CORTEX HAL Exported Functions
  * @{
  */

/** @defgroup CORTEX_HAL_EF_NVIC_Configuration NVIC Priority Configuration Functions
 *  @brief    NVIC Priority Configuration Functions
 *  @{
 */

/** @brief  Sets the priority grouping field (preemption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup: The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0: 0 bit  for pre-emption priority,
  *                                    4 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1: 1 bit  for pre-emption priority,
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority,
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority,
  *                                    1 bit  for subpriority
  *         @arg NVIC_PRIORITYGROUP_4: 4 bits for pre-emption priority,
  *                                    0 bit  for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ preemption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @return None
  */
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_PRIORITY_GROUP(PriorityGroup));

    if (!IS_HAL_NVIC_PRIORITY_GROUP(PriorityGroup)) {
        return;
    }

    /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
    NVIC_SetPriorityGrouping(PriorityGroup);
}

/**
  * @brief  Gets the priority grouping field from the NVIC Interrupt Controller.
  * @return Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
  */
uint32_t HAL_NVIC_GetPriorityGrouping(void)
{
    /* Get the PRIGROUP[10:8] field value */
    return NVIC_GetPriorityGrouping();
}

/**
  * @brief  Sets the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file tae32f561x.h)
  * @param  PreemptPriority: The preemption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority
  * @param  SubPriority: the subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority.
  * @note   The table below gives the allowed values of the pre-emption priority and subpriority according
  *         to the Priority Grouping configuration performed by HAL_NVIC_SetPriorityGrouping() function.
  *           =========================================================================================
  *             NVIC_PriorityGroup   | PreemptPriority | SubPriority |          Description
  *           =========================================================================================
  *            NVIC_PRIORITYGROUP_0  |        0        |     0-15    | 0 bit for pre-emption priority
  *                                  |                 |             | 4 bits for subpriority
  *           -----------------------------------------------------------------------------------------
  *            NVIC_PRIORITYGROUP_1  |       0-1       |     0-7     | 1 bit for pre-emption priority
  *                                  |                 |             | 3 bits for subpriority
  *           -----------------------------------------------------------------------------------------
  *            NVIC_PRIORITYGROUP_2  |       0-3       |     0-3     | 2 bits for pre-emption priority
  *                                  |                 |             | 2 bits for subpriority
  *           -----------------------------------------------------------------------------------------
  *            NVIC_PRIORITYGROUP_3  |       0-7       |     0-1     | 3 bits for pre-emption priority
  *                                  |                 |             | 1 bit for subpriority
  *           -----------------------------------------------------------------------------------------
  *            NVIC_PRIORITYGROUP_4  |       0-15      |      0      | 4 bits for pre-emption priority
  *                                  |                 |             | 0 bit for subpriority
  *           =========================================================================================
  * @return None
  */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    uint32_t prioritygroup = 0x00U;

    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_SUB_PRIORITY(SubPriority));
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_PREEMPTION_PRIORITY(PreemptPriority));

    if (!IS_HAL_NVIC_SUB_PRIORITY(SubPriority) || !IS_HAL_NVIC_PREEMPTION_PRIORITY(PreemptPriority)) {
        return;
    }

    prioritygroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

/**
  * @brief  Gets the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f561x.h))
  * @param  PriorityGroup: the priority grouping bits length.
  *         This parameter can be one of the following values:
  *           @arg NVIC_PRIORITYGROUP_0: 0 bits for preemption priority
  *                                      4 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_1: 1 bits for preemption priority
  *                                      3 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_2: 2 bits for preemption priority
  *                                      2 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_3: 3 bits for preemption priority
  *                                      1 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_4: 4 bits for preemption priority
  *                                      0 bits for subpriority
  * @param  pPreemptPriority: Pointer on the Preemptive priority value (starting from 0).
  * @param  pSubPriority: Pointer on the Subpriority value (starting from 0).
  * @return None
  */
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_PRIORITY_GROUP(PriorityGroup));
    ASSERT_FUNC_PARAM(pPreemptPriority != NULL);
    ASSERT_FUNC_PARAM(pSubPriority != NULL);

    if (!IS_HAL_NVIC_PRIORITY_GROUP(PriorityGroup) || pPreemptPriority == NULL || pSubPriority == NULL) {
        return;
    }

    /* Get priority for Cortex-M system or device specific interrupts */
    NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, pPreemptPriority, pSubPriority);
}
/**
  * @}
  */ /* CORTEX_HAL_EF_NVIC_Configuration */


/** @defgroup CORTEX_HAL_EF_MVIC_Enable NVIC Enable and Pending Config Functions
  * @brief    NVIC Enable and Pending Config Functions
  * @{
  */

/**
  * @brief  Enables a device specific interrupt in the NVIC interrupt controller.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f561x.h))
  * @return None
  */
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_DEVICE_IRQ(IRQn));

    HAL_CORTEX_PARAM_CHECK({
        if (!IS_HAL_NVIC_DEVICE_IRQ(IRQn)) {
            return;
        }        
    })

    /* Enable interrupt */
    NVIC_EnableIRQ(IRQn);
}

/**
  * @brief  Disables a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f561x.h))
  * @return None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_DEVICE_IRQ(IRQn));

    if (!IS_HAL_NVIC_DEVICE_IRQ(IRQn)) {
        return;
    }

    /* Disable interrupt */
    NVIC_DisableIRQ(IRQn);
}

/**
  * @brief  Sets Pending bit of an external interrupt.
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f561x.h))
  * @return None
  */
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_DEVICE_IRQ(IRQn));

    if (!IS_HAL_NVIC_DEVICE_IRQ(IRQn)) {
        return;
    }

    /* Set interrupt pending */
    NVIC_SetPendingIRQ(IRQn);
}

/**
  * @brief  Gets Pending Interrupt (reads the pending register in the NVIC
  *         and returns the pending bit for the specified interrupt).
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f561x.h))
  * @return pending status
  *   @retval 0  Interrupt status is not pending.
  *   @retval 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_DEVICE_IRQ(IRQn));

    if (!IS_HAL_NVIC_DEVICE_IRQ(IRQn)) {
        return 0;
    }

    /* Return 1 if pending else 0 */
    return NVIC_GetPendingIRQ(IRQn);
}

/**
  * @brief  Clears the pending bit of an external interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f561x.h))
  * @return None
  */
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_DEVICE_IRQ(IRQn));

    if (!IS_HAL_NVIC_DEVICE_IRQ(IRQn)) {
        return;
    }

    /* Clear pending interrupt */
    NVIC_ClearPendingIRQ(IRQn);
}

/**
  * @brief Gets active interrupt ( reads the active register in NVIC and returns the active bit).
  * @param IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F561x Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f561x.h))
  * @return status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_HAL_NVIC_DEVICE_IRQ(IRQn));

    if (!IS_HAL_NVIC_DEVICE_IRQ(IRQn)) {
        return 0;
    }

    /* Return 1 if active else 0 */
    return NVIC_GetActive(IRQn);
}

/**
  * @brief  Initiates a system reset request to reset the MCU.
  * @param  None
  * @return None
  */
void HAL_NVIC_SystemReset(void)
{
    /* System Reset */
    NVIC_SystemReset();
}
/**
  * @}
  */ /* CORTEX_HAL_EF_MVIC_Enable */


/** @defgroup CORTEX_HAL_EF_SYSTICK_Configuration SYSTICK Configuration Functions
  * @brief    SYSTICK Configuration Functions
  * @{
  */

/**
  * @brief  Configures the SysTick clock source.
  * @param  CLKSource: specifies the SysTick clock source.
  *         This parameter can be one of the following values:
  *             @arg HAL_SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
  *             @arg HAL_SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
  * @return None
  */
void HAL_SYSTICK_CLKSOURCEConfig(uint32_t CLKSource)
{
    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_SYSTICK_CLK_SOURCE(CLKSource));

    if (!IS_SYSTICK_CLK_SOURCE(CLKSource)) {
        return;
    }

    if (CLKSource == HAL_SYSTICK_CLKSOURCE_HCLK) {
        SysTick->CTRL |= HAL_SYSTICK_CLKSOURCE_HCLK;
    } else {
        SysTick->CTRL &= ~HAL_SYSTICK_CLKSOURCE_HCLK;
    }
}

/**
  * @brief  Initializes the System Timer and its interrupt, and starts the System Tick Timer.
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  TicksNumb: Specifies the ticks Number of ticks between two interrupts.
  * @retval status:  - 0  Function succeeded.
  *                  - 1  Function failed.
  */
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb)
{
    return SysTick_Config(TicksNumb);
}
/**
  * @}
  */ /* CORTEX_HAL_EF_SYSTICK_Configuration */


/** @defgroup CORTEX_HAL_EF_Interrupt CORTEX Interrupt Handler and Callback
  * @brief    CORTEX Interrupt Handler and Callback
  *
@verbatim
  ==============================================================================
                        ##### Interrupt Management #####
  ==============================================================================
  [..]
    This section provides CORTEX interrupt handler functions.
@endverbatim
  * @{
  */

/**
  * @brief  This function handles SYSTICK interrupts requests.
  * @param  None
  * @return None
  */
void HAL_SYSTICK_IRQHandler(void)
{
    HAL_SYSTICK_Callback();
}

/**
  * @brief  SYSTICK callback.
  * @param  None
  * @retval None
  */
__WEAK void HAL_SYSTICK_Callback(void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_SYSTICK_Callback could be implemented in the user file
     */
}
/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/

/**
  * @}
  */

#endif /* HAL_CORTEX_MODULE_ENABLE */
#endif /* HAL_MODULE_ENABLED */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

