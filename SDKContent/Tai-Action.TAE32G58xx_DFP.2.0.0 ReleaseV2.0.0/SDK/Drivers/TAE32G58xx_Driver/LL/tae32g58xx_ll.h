/**
  ******************************************************************************
  * @file    tae32g58xx_ll.h
  * @author  Tai-Action SD Team
  * @brief   This file contains all the functions prototypes for the LL
  *          module driver.
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
#ifndef _TAE32G58XX_LL_H_
#define _TAE32G58XX_LL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup TAE32G58xx_LL
  * @{
  */

/* Exported Constants --------------------------------------------------------*/
/** @defgroup TAE32G58xx_LL_Exported_Constants TAE32G58xx LL Exported Constants
  * @brief    TAE32G58xx LL Exported Constants
  * @{
  */

/**
  * @brief TAE32G58xx LL Driver version number V2.0.0
  */
#define __TAE32G58xx_LL_VERSION_MAIN    (0x02U)     /*!< [31:24] main version       */
#define __TAE32G58xx_LL_VERSION_SUB1    (0x00U)     /*!< [23:16] sub1 version       */
#define __TAE32G58xx_LL_VERSION_SUB2    (0x00U)     /*!< [15:8]  sub2 version       */
#define __TAE32G58xx_LL_VERSION_RC      (0x00U)     /*!< [7:0]  release candidate   */
#define __TAE32G58xx_LL_VERSION         ((__TAE32G58xx_LL_VERSION_MAIN << 24) |\
                                         (__TAE32G58xx_LL_VERSION_SUB1 << 16) |\
                                         (__TAE32G58xx_LL_VERSION_SUB2 << 8 ) |\
                                         (__TAE32G58xx_LL_VERSION_RC))

/**
  * @brief TAE32G58xx SDK Stage String definition
  * @note  Value range: "Alpha" "Beta" "RC" "Trial" "Release"
  */
#define __SDK_LL_STAGE_STR              "Alpha"

/**
  * @}
  */


/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_conf.h"

/* Exported Types ------------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
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

#endif /* _TAE32G58XX_LL_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

