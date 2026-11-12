/**
  ******************************************************************************
  * @file    tae32g58xx_hal.h
  * @author  Tai-Action SD Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef _TAE32G58XX_HAL_H_
#define _TAE32G58XX_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @addtogroup TAE32G58xx_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup TAE32G58xx_HAL_Exported_Constants TAE32G58xx HAL Exported Constants
  * @brief    TAE32G58xx HAL Exported Constants
  * @{
  */

/**
  * @brief TAE32G58xx HAL Driver version number V2.0.0
  */
#define __TAE32G58xx_HAL_VERSION_MAIN    (0x02U)     /*!< [31:24] main version       */
#define __TAE32G58xx_HAL_VERSION_SUB1    (0x00U)     /*!< [23:16] sub1 version       */
#define __TAE32G58xx_HAL_VERSION_SUB2    (0x00U)     /*!< [15:8]  sub2 version       */
#define __TAE32G58xx_HAL_VERSION_RC      (0x00U)     /*!< [7:0]  release candidate   */
#define __TAE32G58xx_HAL_VERSION         ((__TAE32G58xx_HAL_VERSION_MAIN << 24) |\
                                          (__TAE32G58xx_HAL_VERSION_SUB1 << 16) |\
                                          (__TAE32G58xx_HAL_VERSION_SUB2 << 8 ) |\
                                          (__TAE32G58xx_HAL_VERSION_RC))

/**
  * @brief TAE32G58xx SDK Stage String definition
  * @note  Value range: "Alpha" "Beta" "RC" "Trial" "Release"
  */
#define __SDK_HAL_STAGE_STR              "Alpha"

/**
  * @}
  */


/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_hal_conf.h"

/* Exported Types ------------------------------------------------------------*/
/** @defgroup TAE32G58xx_HAL_Exported_Types TAE32G58xx HAL Exported Types
  * @brief    TAE32G58xx HAL Exported Types
  * @{
  */

/**
  * HAL Tick Freq Enum Type Definition
  */
typedef enum {
    HAL_TICK_FREQ_10HZ      = 100U,                 /*!< Tick Frequency 10Hz    */
    HAL_TICK_FREQ_100HZ     = 10U,                  /*!< Tick Frequency 100Hz   */
    HAL_TICK_FREQ_1KHZ      = 1U,                   /*!< Tick Frequency 1KHz    */
    HAL_TICK_FREQ_DEFAULT   = HAL_TICK_FREQ_1KHZ,   /*!< Tick Frequency default */
} HAL_TickFreqTypeDef;


/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup TAE32G58xx_HAL_Exported_Functions
  * @{
  */

/** @addtogroup TAE32G58xx_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
/**
  * @}
  */ /* TAE32G58xx_HAL_EF_Initialization */


/** @addtogroup TAE32G58xx_HAL_EF_Control
  * @{
  */
void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetHalVersion(void);
HAL_StatusTypeDef HAL_GetUID(uint32_t UID[]);
/**
  * @}
  */ /* TAE32G58xx_HAL_EF_Control */

/**
  * @}
  */ /* TAE32G58xx_HAL_Exported_Functions */

/**
  * @}
  */ /* TAE32G58xx_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

