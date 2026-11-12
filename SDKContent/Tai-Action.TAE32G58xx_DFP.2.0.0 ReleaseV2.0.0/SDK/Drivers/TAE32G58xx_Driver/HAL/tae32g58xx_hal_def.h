/**
  ******************************************************************************
  * @file    tae32g58xx_hal_def.h
  * @author  Tai-Action SD Team
  * @brief   This file contains HAL common defines, enumeration, macros and
  *          structures definitions.
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
#ifndef _TAE32G58XX_HAL_DEF_H_
#define _TAE32G58XX_HAL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @defgroup DEFINE_HAL DEFINE HAL
  * @brief    DEFINE HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup DEFINE_HAL_Exported_Constants DEFINE HAL Exported Constants
  * @brief    DEFINE HAL Exported Constants
  * @{
  */

/**
  * @brief HAL wait forever time definition
  */
#define HAL_WAIT_FOREVER                    (0xFFFFFFFFUL)

/**
  * @brief HAL wait max delay time definition
  */
#define HAL_MAX_DELAY                       (0xFFFFFFFEUL)

/**
  * @brief HAL SysTick lowest priority definition
  */
#define HAL_TICK_INT_LOWEST_PRIORITY        ((1UL << __NVIC_PRIO_BITS) - 1UL)

/**
  * @brief HAL EFlash prefetch feature definition
  */
#define HAL_EFLASH_PREFETCH_DISABLE         (0UL)
#define HAL_EFLASH_PREFETCH_ENABLE          (1UL)
#define HAL_EFLASH_PREFETCH_DEFAULT         (2UL)

/**
  * @brief HAL parameter check default setting definition
  */
#ifndef HAL_PERI_PARAM_CHECK_DEFAULT
#define HAL_PERI_PARAM_CHECK_DEFAULT        (0)
#endif

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup DEFINE_HAL_Exported_Types DEFINE HAL Exported Types
  * @brief    DEFINE HAL Exported Types
  * @{
  */

/**
  * @brief HAL Status type definition
  */
typedef enum {
    HAL_OK      = 0x00U,    /*! HAL status OK        */
    HAL_ERROR   = 0x01U,    /*! HAL status Error     */
    HAL_BUSY    = 0x02U,    /*! HAL status Busy      */
    HAL_TIMEOUT = 0x03U,    /*! HAL status Timeout   */
    HAL_FAILED  = 0x04U,    /*! HAL status Failed    */
    HAL_INVALID = 0x05U,    /*! HAL status Invalid   */
} HAL_StatusTypeDef;

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup DEFINE_HAL_Exported_Macros DEFINE HAL Exported Macros
  * @brief    DEFINE HAL Exported Macros
  * @{
  */



/**
  * @brief  Return the Minimum Value between Two Input Params
  * @param  a One Input Parameter
  * @param  b The other Input Parameter
  * @return The Minimum Value between Two Input Params
  */
#define HAL_MIN(a, b)                         (((a) < (b)) ? (a) : (b))

/**
  * @brief  Return the Maximum Value between Two Input Params
  * @param  a One Input Parameter
  * @param  b The other Input Parameter
  * @return The Maximum Value between Two Input Params
  */
#define HAL_MAX(a, b)                         (((a) > (b)) ? (a) : (b))

/**
  * @brief  Return the Absolute value for integer data
  * @param  x Input Parameter
  * @return Return the Absolute value
  */
#define HAL_ABS(x)                            (((x) < (int32_t)0) ? (-(x)) : (x))

/**
  * @brief  Return the Absolute value for float data
  * @param  x Input Parameter
  * @return Return the Absolute value
  */
#define HAL_ABSF(x)                           (((x) < (float)0) ? (-(x)) : (x))

/**
  * @brief  HAL Function Alternative
  * @param  flag Condition Flag
  * @param  func_t True Funciton
  * @param  func_f False Function
  * @return None
  */
#define HAL_FUNC_ALTER(flag, func_t, func_f)  \
        do{                                   \
            if((flag)) {                      \
                func_t;                       \
            } else {                          \
                func_f;                       \
            }                                 \
        } while(0)

/**
  * @brief  Check if the two values are equal
  * @param  val Values being compared
  * @param  cmp Comparison value
  * @retval 0: Unequal
  * @retval 1: Equal
  */
#define HAL_JUDGE_IS(val, cmp)                (((val) == (cmp)) ? ((uint32_t)1) : ((uint32_t)0))

/**
  * @brief  To avoid gcc/g++ warnings
  * @param  X avoid warning param
  * @return None
  */
#define HAL_UNUSED(X)                         (void)(X)


/**
  * @}
  */


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


#endif /* _TAE32G58XX_HAL_DEF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

