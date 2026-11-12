/**
  ******************************************************************************
  * @file    tae32g58xx_hal_conf.h
  * @author  Tai-Action SD Team
  * @brief   HAL configuration file.
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
#ifndef _TAE32G58XX_HAL_CONF_H_
#define _TAE32G58XX_HAL_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @addtogroup TAE32G58xx_Examples
  * @{
  */

/** @addtogroup TAE32G58xx_Template_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup CONFIG_HAL_Exported_Constants CONFIG HAL Exported Constants
  * @brief    CONFIG HAL Exported Constants
  * @{
  */

/** @defgroup CONFIG_HAL_Common_Configuration CONFIG HAL Common Configuration
* @brief    CONFIG HAL Common Configuration
* @{
*/

#define TAE32_USE_FULL_ASSERT
#define TAE32_USE_ASSERT_FUNC_PARAM
#define TAE32_USE_ASSERT_FUNC_STATE

/**
  * @}
  */ /* CONFIG_HAL_System_Configuration */


/** @defgroup CONFIG_HAL_Module_Selection CONFIG HAL Module Selection
  * @brief    CONFIG HAL Module Selection
  * @note     This is the list of modules to be used in the HAL driver
  * @{
  */


/* Internal Class Peripheral */
#define HAL_MODULE_ENABLED           (1)  /*!< HAL Global Switch      */
#define HAL_SYSCTRL_MODULE_ENABLED   (1)  /*!< SYSCTRL Module Enable  */
#define HAL_RCU_MODULE_ENABLED       (1)  /*!< RCU Module Enable      */
#define HAL_CORTEX_MODULE_ENABLED    (1)  /*!< Cortex Module Enable   */
#define HAL_DMA_MODULE_ENABLED       (1)  /*!< DMA Module Enable      */
#define HAL_EFLASH_MODULE_ENABLED    (1)  /*!< EFLASH Module Enable   */
#define HAL_ADTMR_MODULE_ENABLED     (1)  /*!< ADTMR Module Enable    */
#define HAL_GPTMRX_MODULE_ENABLED    (1)  /*!< GPTMRx Module Enable   */
#define HAL_GPTMRY_MODULE_ENABLED    (1)  /*!< GPTMRy Module Enable   */
#define HAL_BSTMR_MODULE_ENABLED     (1)  /*!< BSTMR Module Enable    */
#define HAL_LPTMR_MODULE_ENABLED     (1)  /*!< LPTMR Module Enable    */
#define HAL_QEI_MODULE_ENABLED       (1)  /*!< QEI Module Enable      */
#define HAL_IIR_MODULE_ENABLED       (1)  /*!< IIR Module Enable      */
#define HAL_IWDG_MODULE_ENABLED      (1)  /*!< IWDG Module Enable     */
#define HAL_WWDG_MODULE_ENABLED      (1)  /*!< WWDG Module Enable     */

/* Interface Class Peripheral */
#define HAL_GPIO_MODULE_ENABLED      (1)  /*!< GPIO Module Enable     */
#define HAL_UART_MODULE_ENABLED      (1)  /*!< UART Module Enable     */
#define HAL_I2C_MODULE_ENABLED       (1)  /*!< I2C Module Enable      */
#define HAL_SPI_MODULE_ENABLED       (1)  /*!< SPI Module Enable      */
#define HAL_CAN_MODULE_ENABLED       (1)  /*!< CAN Module Enable      */

/* Analog Class Peripheral */
#define HAL_ADC_MODULE_ENABLED       (1)  /*!< ADC Module Enable      */
#define HAL_DAC_MODULE_ENABLED       (1)  /*!< DAC Module Enable      */
#define HAL_CMP_MODULE_ENABLED       (1)  /*!< CMP Module Enable      */
#define HAL_HRPWM_MODULE_ENABLED     (1)  /*!< HRPWM Module Enable    */


/**
  * @}
  */ /* CONFIG_HAL_Module_Selection */

/** @defgroup CONFIG_HAL_Module_Configuration CONFIG HAL Module Configuration
  * @brief    CONFIG HAL Module Configuration
  * @{
  */

/** @defgroup HAL_Config HAL Configuration
  * @{
  */
#define TAE32_USE_HAL_BOOL_TYPE_DEFINE                      (1)
/**
  * @}
  */ /* HAL_Config */



/** @defgroup HAL_SYSCTRL_Config HAL SYSCTRL Configuration
  * @{
  */
#define TAE32_USE_HAL_SYSCTRL_CHECK_PARAM                   (1)
/**
  * @}
  */ /* HAL_SYSCTRL_Config */

/** @defgroup HAL_EFLASH_Config HAL EFLASH Configuration
  * @{
  */
#define TAE32_USE_HAL_EFLASH_CHECK_PARAM                    (1)
/**
  * @}
  */ /* HAL_EFLASH_Config */

/** @defgroup HAL_DAC_Config HAL DAC Configuration
  * @{
  */
#define TAE32_USE_HAL_DAC_CHECK_PARAM                       (1)
/**
  * @}
  */ /* HAL_DAC_Config */

/** @defgroup HAL_CMP_Config HAL CMP Configuration
  * @{
  */
#define TAE32_USE_HAL_CMP_CHECK_PARAM                       (1)
/**
  * @}
  */ /* HAL_CMP_Config */

/** @defgroup HAL_HRPWM_Config HAL HRPWM Configuration
  * @{
  */
#define TAE32_USE_HAL_HRPWM_CHECK_PARAM                     (1)
/**
  * @}
  */ /* HAL_HRPWM_Config */

/** @defgroup HAL_ADC_Config HAL ADC Configuration
  * @{
  */
#define TAE32_USE_HAL_ADC_CHECK_PARAM                       (1)
#define TAE32_USE_HAL_ADC_CHECK_PROCESS_STATE               (1)
/**
  * @}
  */ /* HAL_ADC_Config */

/** @defgroup HAL_CAN_Config HAL CAN Configuration
  * @{
  */
#define TAE32_USE_HAL_CAN_CHECK_PARAM                       (1)
#define TAE32_USE_HAL_CAN_CHECK_PROCESS_STATE               (1)
/**
  * @}
  */ /* HAL_CAN_Config */

/** @defgroup HAL_DMA_Config HAL DMA Configuration
  * @{
  */
#define TAE32_USE_HAL_DMA_CHECK_PARAM                       (1)
#define TAE32_USE_HAL_DMA_CHECK_PROCESS_STATE               (1)
/**
  * @}
  */ /* HAL_DMA_Config */

/** @defgroup HAL_SPI_Config HAL SPI Configuration
  * @{
  */
#define TAE32_USE_HAL_SPI_CHECK_PARAM                       (1)
#define USE_HAL_SPI_REGISTER_CALLBACKS                      (1)
#define USE_HAL_SPI_DMA                                     (1)
/**
  * @}
  */ /* HAL_SPI_Config */

/** @defgroup HAL_I2C_Config HAL I2C Configuration
  * @{
  */
#define TAE32_USE_HAL_I2C_CHECK_PARAM                       (1)
#define TAE32_USE_HAL_I2C_CHECK_PROCESS_STATE               (1)
#define USE_HAL_I2C_REGISTER_CALLBACKS                      (1)
#define USE_HAL_I2C_DMA                                     (1)
/**
  * @}
  */ /* HAL_I2C_Config */

/** @defgroup HAL_UART_Config HAL UART Configuration
  * @{
  */
#define TAE32_USE_HAL_UART_CHECK_PARAM                      (1)
#define USE_HAL_UART_REGISTER_CALLBACKS                     (1)
#define USE_HAL_UART_DMA                                    (1)
/**
  * @}
  */ /* HAL_UART_Config */

/** @defgroup HAL_ADTMR_Config HAL ADTMR Configuration
  * @{
  */
#define TAE32_USE_HAL_ADTMR_CHECK_PARAM                     (1)
/**
  * @}
  */ /* HAL_ADTMR_Config */

/** @defgroup HAL_GPTMRX_Config HAL GPTMRX Configuration
  * @{
  */
#define TAE32_USE_HAL_GPTMRX_CHECK_PARAM                    (1)
/**
  * @}
  */ /* HAL_GPTMRX_Config */

/** @defgroup HAL_GPTMRY_Config HAL GPTMRY Configuration
  * @{
  */
#define TAE32_USE_HAL_GPTMRY_CHECK_PARAM                    (1)
/**
  * @}
  */ /* HAL_GPTMRY_Config */

/** @defgroup HAL_BSTMR_Config HAL BSTMR Configuration
  * @{
  */
#define TAE32_USE_HAL_BSTMR_CHECK_PARAM                     (1)
/**
  * @}
  */ /* HAL_BSTMR_Config */

/** @defgroup HAL_LPTMR_Config HAL LPTMR Configuration
  * @{
  */
#define TAE32_USE_HAL_LPTMR_CHECK_PARAM                     (1)
/**
  * @}
  */ /* HAL_LPTMR_Config */

/** @defgroup HAL_IWDG_Config HAL IWDG Configuration
  * @{
  */
#define TAE32_USE_HAL_IWDG_CHECK_PARAM                      (1)
/**
  * @}
  */ /* HAL_IWDG_Config */

/** @defgroup HAL_WWDG_Config HAL WWDG Configuration
  * @{
  */
#define TAE32_USE_HAL_WWDG_CHECK_PARAM                      (1)
/**
  * @}
  */ /* HAL_WWDG_Config */

/** @defgroup HAL_GPIO_Config HAL GPIO Configuration
  * @{
  */
#define TAE32_USE_HAL_GPIO_CHECK_PARAM                      (1)
/**
  * @}
  */ /* HAL_GPIO_Config */

/** @defgroup HAL_XXX_Config HAL XXX Configuration
  * @{
  */
#define TAE32_USE_HAL_XXX_CHECK_PARAM                       (1)
/**
  * @}
  */ /* HAL_XXX_Config */


/**
  * @}
  */ /* CONFIG_HAL_Module_Configuration */

/** @defgroup CONFIG_HAL_Oscillator_Values_Adaptation CONFIG HAL Oscillator Values Adaptation
  * @brief    CONFIG HAL Oscillator Values Adaptation
  * @{
  */

/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the PHAL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PHAL).
  */
#ifndef HSE_VALUE
#define HSE_VALUE               (8000000U)
#endif /* HSE_VALUE */
/**
  * @}
  */ /* CONFIG_HAL_Oscillator_Values_Adaptation */


/** @defgroup CONFIG_HAL_System_Configuration CONFIG HAL System Configuration
  * @brief    CONFIG HAL System Configuration
  * @note     This is the HAL system configuration section
  * @{
  */

/**
  * @brief SysTick interrupt priority, set to lowest    
  */
#ifndef TAE32_USE_HAL_TICK_INT_PRIORITY
#define TAE32_USE_HAL_TICK_INT_PRIORITY           (HAL_TICK_INT_LOWEST_PRIORITY)     
#endif /* TAE32_USE_HAL_TICK_INT_PRIORITY */

/**
  * @brief EFlash prefetch feature   
  */
#ifndef TAE32_USE_HAL_FLASH_PREFETCH_CONFIG
#define TAE32_USE_HAL_FLASH_PREFETCH_CONFIG       (HAL_EFLASH_PREFETCH_DEFAULT)
#endif /* TAE32_USE_HAL_FLASH_PREFETCH_CONFIG */
/**
  * @}
  */ /* CONFIG_HAL_System_Configuration */

/**
  * @}
  */


/* Includes ------------------------------------------------------------------*/

/* Internal Class Peripheral */
#if defined(HAL_SYSCTRL_MODULE_ENABLED) && (HAL_SYSCTRL_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_sysctrl.h"
#endif

#if defined(HAL_RCU_MODULE_ENABLED) && (HAL_RCU_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_rcu.h"
#endif

#if defined(HAL_CORTEX_MODULE_ENABLED) && (HAL_CORTEX_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_cortex.h"
#endif

#if defined(HAL_DMA_MODULE_ENABLED) && (HAL_DMA_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_dma.h"
#endif

#if defined(HAL_EFLASH_MODULE_ENABLED) && (HAL_EFLASH_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_eflash.h"
#endif

#if defined(HAL_ADTMR_MODULE_ENABLED) && (HAL_ADTMR_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_adtmr.h"
#endif

#if defined(HAL_GPTMRX_MODULE_ENABLED) && (HAL_GPTMRX_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_gptmrx.h"
#endif

#if defined(HAL_GPTMRY_MODULE_ENABLED) && (HAL_GPTMRY_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_gptmry.h"
#endif

#if defined(HAL_BSTMR_MODULE_ENABLED) && (HAL_BSTMR_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_bstmr.h"
#endif

#if defined(HAL_LPTMR_MODULE_ENABLED) && (HAL_LPTMR_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_lptmr.h"
#endif

#if defined(HAL_QEI_MODULE_ENABLED) && (HAL_QEI_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_qei.h"
#endif

#if defined(HAL_IIR_MODULE_ENABLED) && (HAL_IIR_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_iir.h"
#endif

#if defined(HAL_IWDG_MODULE_ENABLED) && (HAL_IWDG_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_iwdg.h"
#endif

#if defined(HAL_WWDG_MODULE_ENABLED) && (HAL_WWDG_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_wwdg.h"
#endif


/* Interface Class Peripheral */
#if defined(HAL_GPIO_MODULE_ENABLED) && (HAL_GPIO_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_gpio.h"
#endif

#if defined(HAL_UART_MODULE_ENABLED) && (HAL_UART_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_uart.h"
#endif

#if defined(HAL_I2C_MODULE_ENABLED) && (HAL_I2C_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_i2c.h"
#endif

#if defined(HAL_SPI_MODULE_ENABLED) && (HAL_SPI_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_spi.h"
#endif

#if defined(HAL_CAN_MODULE_ENABLED) && (HAL_CAN_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_can.h"
#endif


/* Analog Class Peripheral */
#if defined(HAL_ADC_MODULE_ENABLED) && (HAL_ADC_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_adc.h"
#endif

#if defined(HAL_DAC_MODULE_ENABLED) && (HAL_DAC_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_dac.h"
#endif

#if defined(HAL_CMP_MODULE_ENABLED) && (HAL_CMP_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_cmp.h"
#endif

#if defined(HAL_HRPWM_MODULE_ENABLED) && (HAL_HRPWM_MODULE_ENABLED == 1)
#include "tae32g58xx_hal_hrpwm.h"
#endif


/* Exported Types ------------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CONFIG_HAL_Exported_Macros CONFIG HAL Exported Macros
  * @brief    CONFIG HAL Exported Macros
  * @{
  */

/** @defgroup CONFIG_HAL_Assert_Selection CONFIG HAL Assert Selection
  * @brief    CONFIG HAL Assert Selection
  * @{
  */

/**
  * @brief Uncomment the line below to expanse the assert macro in the HAL drivers code
  */
#ifdef TAE32_USE_FULL_ASSERT
#if defined(TAE32_USE_ASSERT_FUNC_PARAM)
extern void assert_func_failed(uint8_t *File, uint32_t Line);

/**
  * @brief  The ASSERT_FUNC_PARAM macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_func_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define ASSERT_FUNC_PARAM(expr)       ((expr) ? (void)0U : assert_func_failed((uint8_t *)__FILE__, __LINE__))
#else
#define ASSERT_FUNC_PARAM(expr)       ((void)0U)
#endif

#if defined(TAE32_USE_ASSERT_FUNC_STATE)
extern void assert_state_failed(uint8_t *File, uint32_t Line);

/**
  * @brief  The ASSERT_FUNC_STATE macro is used for function state checks.
  * @param  state the state field within the PPP handle
  * @param  state_value the authorized state value(s) to be checked
  *                 can be a combination of states
  * @note   If state & state_value is zero (unauthorized state), then
  *         the assert_dbg_state_failed function is called which reports
  *         the name of the source file and the source line number of the call that failed.
  *         If state & state_value is zero (unauthorized state), then the ASSERT_FUNC_STATE macro returns no value.
  */
#define ASSERT_FUNC_STATE(state, state_value)   \
                                      (((((uint32_t)(state)) &  ((uint32_t)(state_value))) != 0U) ? (void)0U :  \
                                             assert_state_failed((uint8_t *)__FILE__, __LINE__))
#else
#define ASSERT_FUNC_STATE(state, state_value)   ((void)0U)
#endif

#else
#define ASSERT_FUNC_PARAM(expr)                 ((void)0U)
#define ASSERT_FUNC_STATE(state, state_value)   ((void)0U)
#endif /* TAE32_USE_FULL_ASSERT */


/**
  * @}
  */ /* CONFIG_HAL_Assert_Selection */

/**
  * @}
  */ /* CONFIG_HAL_Exported_Macros */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/**
  * @}
  */ /* TAE32G58xx_Template */

/**
  * @}
  */ /* TAE32G58xx_Examples */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32G58XX_HAL_CONF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

