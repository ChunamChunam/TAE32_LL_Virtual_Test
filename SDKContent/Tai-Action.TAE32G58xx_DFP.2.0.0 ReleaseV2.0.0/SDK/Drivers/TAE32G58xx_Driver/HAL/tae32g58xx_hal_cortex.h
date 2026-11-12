/**
  ******************************************************************************
  * @file    tae32g58xx_hal_cortex.h
  * @author  Tai-Action SD Team
  * @brief   Header file for CORTEX HAL module
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
#ifndef _TAE32G58XX_HAL_CORTEX_H_
#define _TAE32G58XX_HAL_CORTEX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_cortex.h"

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)

/** @addtogroup CORTEX_HAL
  * @{
  */


/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/** @defgroup CORTEX_HAL_Exported_Constants CORTEX HAL Exported Constants
  * @brief    CORTEX HAL Exported Constants
  * @{
  */

/** @defgroup CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group
  * @{
  */
#define HAL_NVIC_PRIORITYGROUP_0            0x00000007U     /*!< 0 bit  for pre-emption priority, 4 bits for subpriority    */
#define HAL_NVIC_PRIORITYGROUP_1            0x00000006U     /*!< 1 bit  for pre-emption priority, 3 bits for subpriority    */
#define HAL_NVIC_PRIORITYGROUP_2            0x00000005U     /*!< 2 bits for pre-emption priority, 2 bit  for subpriority    */
#define HAL_NVIC_PRIORITYGROUP_3            0x00000004U     /*!< 3 bits for pre-emption priority, 1 bit  for subpriority    */
#define HAL_NVIC_PRIORITYGROUP_4            0x00000003U     /*!< 4 bits for pre-emption priority, 0 bit  for subpriority    */
/**
  * @}
  */ /* CORTEX_Preemption_Priority_Group */

/** @defgroup CORTEX_SysTick_Clock_Source CORTEX SysTick Clock Source
  * @brief    CORTEX SysTick Clock Source
  * @{
  */
#define HAL_SYSTICK_CLKSOURCE_HCLK_DIV8     0x00000000U     /*!< SYSTICK Clock Source HCLK Div8 */
#define HAL_SYSTICK_CLKSOURCE_HCLK          0x00000004U     /*!< SYSTICK Clock Source HCLK      */
/**
  * @}
  */ /* CORTEX_SysTick_Clock_Source */

/**
  * @}
  */ /* CORTEX_HAL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CORTEX_HAL_Exported_Macros CORTEX HAL Exported Macros
  * @brief    CORTEX HAL Exported Macros
  * @{
  */

/**
  * @brief  Judge is NVIC priority group or not
  * @param  GROUP priority group to judge
  * @retval 0 isn't NVIC priority group
  * @retval 1 is NVIC priority group
  */
#define IS_HAL_NVIC_PRIORITY_GROUP(GROUP)       (((GROUP) == HAL_NVIC_PRIORITYGROUP_0) || \
                                                 ((GROUP) == HAL_NVIC_PRIORITYGROUP_1) || \
                                                 ((GROUP) == HAL_NVIC_PRIORITYGROUP_2) || \
                                                 ((GROUP) == HAL_NVIC_PRIORITYGROUP_3) || \
                                                 ((GROUP) == HAL_NVIC_PRIORITYGROUP_4))

/**
  * @brief  Judge is NVIC preemption priority or not
  * @param  PRIORITY preemption priority to judge
  * @retval 0 isn't NVIC preemption priority
  * @retval 1 is NVIC preemption priority
  */
#define IS_HAL_NVIC_PREEMPTION_PRIORITY(PRIORITY)   ((PRIORITY) < BIT(__NVIC_PRIO_BITS))

/**
  * @brief  Judge is NVIC SubPriority or not
  * @param  PRIORITY SubPriority to judge
  * @retval 0 isn't NVIC SubPriority
  * @retval 1 is NVIC SubPriority
  */
#define IS_HAL_NVIC_SUB_PRIORITY(PRIORITY)          ((PRIORITY) < BIT(__NVIC_PRIO_BITS))

/**
  * @brief  Judge is NVIC device IRQ or not
  * @param  IRQ IRQ to judge
  * @retval 0 isn't NVIC device IRQ
  * @retval 1 is NVIC device IRQ
  */
#define IS_HAL_NVIC_DEVICE_IRQ(IRQ)                 ((IRQ) >= (IRQn_Type)0x00U)


/**
  * @brief  The HAL_CORTEX_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_CORTEX_CHECK_PARAM
#define TAE32_USE_HAL_CORTEX_CHECK_PARAM  HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_CORTEX_CHECK_PARAM != 1) && (TAE32_USE_HAL_CORTEX_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_CORTEX_CHECK_PARAM
#define TAE32_USE_HAL_CORTEX_CHECK_PARAM  HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_CORTEX_CHECK_PARAM */

/**
  * @brief  The HAL_CORTEX_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_CORTEX_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_CORTEX_CHECK_PARAM) { \
            expression;                         \
        }
/**
  * @}
  */ /* CORTEX_HAL_Exported_Macros */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup CORTEX_HAL_Exported_Functions
  * @{
  */

/** @addtogroup CORTEX_HAL_EF_NVIC_Configuration
  * @{
  */
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority);
/**
  * @}
  */ /* CORTEX_HAL_EF_NVIC_Configuration */


/** @addtogroup CORTEX_HAL_EF_MVIC_Enable
  * @{
  */
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
/**
  * @}
  */ /* CORTEX_HAL_EF_MVIC_Enable */


/** @addtogroup CORTEX_HAL_EF_SYSTICK_Configuration
  * @{
  */
void HAL_SYSTICK_CLKSOURCEConfig(uint32_t CLKSource);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
/**
  * @}
  */ /* CORTEX_HAL_EF_SYSTICK_Configuration */


/** @addtogroup CORTEX_HAL_EF_Interrupt
  * @{
  */
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);
/**
  * @}
  */ /* CORTEX_HAL_EF_Interrupt */

/**
  * @}
  */ /* CORTEX_HAL_Exported_Functions */

/**
  * @}
  */ /* CORTEX_HAL */

#endif /* HAL_MODULE_ENABLED */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32G58XX_HAL_CORTEX_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

