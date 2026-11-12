/**
  ******************************************************************************
  * @file    tae32g58xx_it.h
  * @author  Tai-Action SD Team
  * @brief   Header file for Main Interrupt Service Routines.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
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
#ifndef _TAE32G58xx_IT_H_
#define _TAE32G58xx_IT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/


/** @addtogroup TAE32G58xx_Examples
  * @{
  */

/** @addtogroup TAE32G58xx_Template_LL
  * @{
  */


/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup TAE32G58xx_IT_Exported_Functions
  * @{
  */

/** @addtogroup TAE32G58xx_IT_EF_Processor
  * @{
  */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
/**
  * @}
  */


/** @addtogroup TAE32G58xx_IT_EF_Peripherals
  * @{
  */
///...
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


#endif /* _TAE32G58xx_IT_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

