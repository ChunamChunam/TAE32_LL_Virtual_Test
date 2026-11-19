/**
  ******************************************************************************
  * @file    tae32f561x_ll_conf.h
  * @author  Tai-Action SD Team
  * @brief   LL configuration file.
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
#ifndef _TAE32F561X_LL_CONF_H_
#define _TAE32F561X_LL_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @addtogroup TAE32F561x_Examples
  * @{
  */

/** @addtogroup TAE32F561x_Template_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup CONFIG_LL_Exported_Constants CONFIG LL Exported Constants
  * @brief    CONFIG LL Exported Constants
  * @{
  */


/** @defgroup CONFIG_LL_Common_Configuration CONFIG LL Common Configuration
  * @brief    CONFIG LL Common Configuration
  * @{
  */


/**
  * @}
  */ /* CONFIG_LL_System_Configuration */


/**
  * @}
  */ /* CONFIG_LL_Exported_Constants */


/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_ll_sysctrl.h"
#include "tae32f561x_ll_rcu.h"

/* Internal Class Peripheral */
#include "tae32f561x_ll_cortex.h"
#include "tae32f561x_ll_dma.h"
#include "tae32f561x_ll_eflash.h"
// #include "tae32f561x_ll_gptmrx.h"
#include "tae32f561x_ll_bstmr.h"

// #include "tae32f561x_ll_qei.h"
// #include "tae32f561x_ll_iqdiv.h"
#include "tae32f561x_ll_iwdg.h"
#include "tae32f561x_ll_wwdg.h"

/* Interface Class Peripheral */
#include "tae32f561x_ll_gpio.h"
#include "tae32f561x_ll_uart.h"
// #include "tae32f561x_ll_i2c.h"
// #include "tae32f561x_ll_spi.h"
// #include "tae32f561x_ll_can.h"

/* Analog Class Peripheral */
// #include "tae32f561x_ll_adc.h"
// #include "tae32f561x_ll_dac.h"
// #include "tae32f561x_ll_cmp.h"
// #include "tae32f561x_ll_hrpwm.h"


/* Exported Types ------------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CONFIG_LL_Exported_Macros CONFIG LL Exported Macros
  * @brief    CONFIG LL Exported Macros
  * @{
  */


/**
  * @}
  */ /* CONFIG_LL_Exported_Macros */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F561X_LL_CONF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

