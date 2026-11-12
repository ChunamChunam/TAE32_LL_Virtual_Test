/**
  ******************************************************************************
  * @file    tae32g58xx_ll_cortex.h
  * @author  Tai-Action SD Team
  * @brief   Header file for CORTEX LL module
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
#ifndef _TAE32G58XX_LL_CORTEX_H_
#define _TAE32G58XX_LL_CORTEX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup CORTEX_LL
  * @{
  */


/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Constants CORTEX LL Exported Constants
  * @brief    CORTEX LL Exported Constants
  * @{
  */

/** @defgroup CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group
  * @{
  */
#define LL_NVIC_PRIORITYGROUP_0             0x00000007U     /*!< 0 bit  for pre-emption priority, 4 bits for subpriority    */
#define LL_NVIC_PRIORITYGROUP_1             0x00000006U     /*!< 1 bit  for pre-emption priority, 3 bits for subpriority    */
#define LL_NVIC_PRIORITYGROUP_2             0x00000005U     /*!< 2 bits for pre-emption priority, 2 bit  for subpriority    */
#define LL_NVIC_PRIORITYGROUP_3             0x00000004U     /*!< 3 bits for pre-emption priority, 1 bit  for subpriority    */
#define LL_NVIC_PRIORITYGROUP_4             0x00000003U     /*!< 4 bits for pre-emption priority, 0 bit  for subpriority    */
/**
  * @}
  */


/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Macros CORTEX LL Exported Macros
  * @brief    CORTEX LL Exported Macros
  * @{
  */

/**
  * @brief  Judge is NVIC priority group or not
  * @param  GROUP priority group to judge
  * @retval 0 isn't NVIC priority group
  * @retval 1 is NVIC priority group
  */
#define IS_LL_NVIC_PRIORITY_GROUP(GROUP)        (((GROUP) == LL_NVIC_PRIORITYGROUP_0) || \
                                                 ((GROUP) == LL_NVIC_PRIORITYGROUP_1) || \
                                                 ((GROUP) == LL_NVIC_PRIORITYGROUP_2) || \
                                                 ((GROUP) == LL_NVIC_PRIORITYGROUP_3) || \
                                                 ((GROUP) == LL_NVIC_PRIORITYGROUP_4))

/**
  * @brief  Judge is NVIC preemption priority or not
  * @param  PRIORITY preemption priority to judge
  * @retval 0 isn't NVIC preemption priority
  * @retval 1 is NVIC preemption priority
  */
#define IS_LL_NVIC_PREEMPTION_PRIORITY(PRIORITY)   ((PRIORITY) < BIT(__NVIC_PRIO_BITS))

/**
  * @brief  Judge is NVIC SubPriority or not
  * @param  PRIORITY SubPriority to judge
  * @retval 0 isn't NVIC SubPriority
  * @retval 1 is NVIC SubPriority
  */
#define IS_LL_NVIC_SUB_PRIORITY(PRIORITY)          ((PRIORITY) < BIT(__NVIC_PRIO_BITS))

/**
  * @brief  Judge is NVIC device IRQ or not
  * @param  IRQ IRQ to judge
  * @retval 0 isn't NVIC device IRQ
  * @retval 1 is NVIC device IRQ
  */
#define IS_LL_NVIC_DEVICE_IRQ(IRQ)                 ((IRQ) >= (IRQn_Type)0x00U)

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Functions CORTEX LL Exported Functions
  * @brief    CORTEX LL Exported Functions
  * @{
  */

/** @defgroup CORTEX_LL_EF_NVIC_Configuration NVIC Priority Configuration
 *  @brief    NVIC Priority Configuration
 *  @{
 */

/** @brief  Sets the priority grouping field (preemption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup: The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg LL_NVIC_PRIORITYGROUP_0: 0 bit  for pre-emption priority,
  *                                       4 bits for subpriority
  *         @arg LL_NVIC_PRIORITYGROUP_1: 1 bit  for pre-emption priority,
  *                                       3 bits for subpriority
  *         @arg LL_NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority,
  *                                       2 bits for subpriority
  *         @arg LL_NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority,
  *                                       1 bit  for subpriority
  *         @arg LL_NVIC_PRIORITYGROUP_4: 4 bits for pre-emption priority,
  *                                       0 bit  for subpriority
  * @note   When the LL_NVIC_PRIORITYGROUP_0 is selected, IRQ preemption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @return None
  */
__STATIC_INLINE void LL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    ASSERT_INLINE_PARAM(IS_LL_NVIC_PRIORITY_GROUP(PriorityGroup));

    NVIC_SetPriorityGrouping(PriorityGroup);
}

/**
  * @brief  Gets the priority grouping field from the NVIC Interrupt Controller.
  * @return Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
  */
__STATIC_INLINE uint32_t LL_NVIC_GetPriorityGrouping(void)
{
    return (uint32_t)NVIC_GetPriorityGrouping();
}

/**
  * @brief  Sets the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of @ref IRQn_Type enumeration
  * @param  PreemptPriority: The preemption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority
  * @param  SubPriority: the subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority.
  * @note   The table below gives the allowed values of the pre-emption priority and subpriority according
  *         to the Priority Grouping configuration performed by @ref LL_NVIC_SetPriorityGrouping() function.
  * @return None
  */
__STATIC_INLINE void LL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    uint32_t priority_group = 0x00U;

    ASSERT_INLINE_PARAM(IS_LL_NVIC_SUB_PRIORITY(SubPriority));
    ASSERT_INLINE_PARAM(IS_LL_NVIC_PREEMPTION_PRIORITY(PreemptPriority));

    priority_group = NVIC_GetPriorityGrouping();

    /* Set the priority according to the PriorityGroup parameter value */
    NVIC_SetPriority(IRQn, NVIC_EncodePriority(priority_group, PreemptPriority, SubPriority));
}

/**
  * @brief  Gets the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of @ref IRQn_Type enumeration
  * @param  PriorityGroup: the priority grouping bits length.
  * @note   The Priority Grouping configuration is performed by @ref LL_NVIC_SetPriorityGrouping() function.
  * @return The Preemptive priority value (starting from 0).
  */
__STATIC_INLINE uint32_t LL_NVIC_GetPreemptPriority(IRQn_Type IRQn, uint32_t PriorityGroup)
{
    uint32_t preempt_priority;
    uint32_t sub_priority;

    ASSERT_INLINE_PARAM(IS_LL_NVIC_PRIORITY_GROUP(PriorityGroup));

    /* Get priority for Cortex-M system or device specific interrupts */
    NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, &preempt_priority, &sub_priority);

    /* Add this code to indicate that the local variable is not used. */
    PARAM_UNUSED(sub_priority);

    return preempt_priority;
}

/**
  * @brief  Gets the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of @ref IRQn_Type enumeration
  * @param  PriorityGroup: the priority grouping bits length. 
  * @note   The Priority Grouping configuration is performed by @ref LL_NVIC_SetPriorityGrouping() function.
  * @return The Subpriority value (starting from 0).
  */
__STATIC_INLINE uint32_t LL_NVIC_GetSubPriority(IRQn_Type IRQn, uint32_t PriorityGroup)
{
    uint32_t preempt_priority;
    uint32_t sub_priority;

    ASSERT_INLINE_PARAM(IS_LL_NVIC_PRIORITY_GROUP(PriorityGroup));

    /* Get priority for Cortex-M system or device specific interrupts */
    NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, &preempt_priority, &sub_priority);

    /* Add this code to indicate that the local variable is not used. */
    PARAM_UNUSED(preempt_priority);

    return sub_priority;
}

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_SYSTICK_Configuration SysTick Configuration and Delay Management
 *  @brief    SysTick Configuration and Delay Management
 *  @{
 */

/**
  * @brief   Configure the Cortex-M SysTick source of the time base.
  * @param   CPU_Clk_Freq CPU clock frequency in Hz
  * @param   Ticks Ticks frequency in Hz, must be > 0
  */
__STATIC_INLINE void LL_InitTick(uint32_t CPU_Clk_Freq, uint32_t Ticks)
{
    ASSERT_INLINE_PARAM(Ticks > 0);

    /* Set reload register. */
    SysTick->LOAD = (uint32_t)((CPU_Clk_Freq / Ticks) - 1U);  
    
    /* Load the SysTick counter value. */
    SysTick->VAL = 0U;                            
    
    /* Enable the SysTick timer. */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;  
}

/**
  * @brief  Configure the Cortex-M SysTick source to have a 1 milliseconds time base.
  * @param  CPU_Clk_Freq CPU clock frequency in Hz
  * @note   When a RTOS is used, it is recommended to not use this function to modify the SysTick.
  */
__STATIC_INLINE void LL_Init1msTick(uint32_t CPU_Clk_Freq)
{
    ASSERT_INLINE_PARAM(CPU_Clk_Freq > 0);

    /* Use the frequency provided in argument. */
    LL_InitTick(CPU_Clk_Freq, 1000U);
}

/**
  * @brief   Provide a delay based on the SysTick counter flag.
  * @param   Milliseconds Delay duration in milliseconds
  * @note    Delay accuracy on the requested value is [0; +1 ms] due to uncertainty of the initial SysTick counter value
  *          compared to the reload value.
  * @note    To respect a 1 ms time base, call the @ref LL_Init1msTick function which
  *          applies the appropriate SysTick configuration.
  * @note   When a RTOS is used, it is recommended to not use this function to modify the SysTick.
  */
__STATIC_INLINE void LL_Delay_NoISR(uint32_t Milliseconds)
{
    uint32_t wait = Milliseconds;

    /* Clear the SysTick counter reload flag. */
    volatile uint32_t read_ctrl = SysTick->CTRL;  

    /* Add this code to indicate that the local variable is not used. */
    PARAM_UNUSED(read_ctrl);
  
    /* Add a period to guarantee minimum wait */
    if (!wait) {
        wait ++;
    }

    while (wait != 0U) {
        if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U) {
            wait--;
        }
    }
}

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


#endif /* _TAE32G58XX_LL_CORTEX_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

