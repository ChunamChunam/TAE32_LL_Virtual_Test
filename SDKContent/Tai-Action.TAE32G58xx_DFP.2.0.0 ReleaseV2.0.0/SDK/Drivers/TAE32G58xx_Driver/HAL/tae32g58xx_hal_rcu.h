/**
  ******************************************************************************
  * @file    tae32g58xx_hal_rcu.h
  * @author  Tai-Action Team
  * @brief   Header file for RCU HAL module
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
#ifndef _TAE32G58XX_HAL_RCU_H_
#define _TAE32G58XX_HAL_RCU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_rcu.h"

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @defgroup RCU_HAL RCU HAL
  * @brief    RCU HAL Module Driver
  * @{
  */

/* Exported Macros -----------------------------------------------------------*/
/** @defgroup RCU_HAL_Exported_Macros RCU HAL Exported Macros
  * @brief    RCU HAL Exported Macros
  * @{
  */

/** @defgroup RCU_HAL_EM_Assert RCU HAL Assert
  * @brief    RCU HAL Assert
  * @{
  */

/**
  * @brief  The HAL_RCU_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_RCU_CHECK_PARAM
#define TAE32_USE_HAL_RCU_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_RCU_CHECK_PARAM != 1) && (TAE32_USE_HAL_RCU_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_RCU_CHECK_PARAM
#define TAE32_USE_HAL_RCU_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_RCU_CHECK_PARAM */

/**
  * @brief  The HAL_RCU_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_RCU_PARAM_CHECK(expression)       \
        if (TAE32_USE_HAL_RCU_CHECK_PARAM) {  \
            expression;                       \
        }

/**
  * @}
  */ /* RCU_HAL_EM_Assert */



/**
  * @}
  */ /* RCU_HAL_Exported_Macros */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup RCU_HAL_Exported_Constants RCU HAL Exported Constants
  * @brief    RCU HAL Exported Constants
  * @{
  */

/** @name RCU_SYSCLK_Freq_Range
  * @brief RCU_SYSCLK_Freq_Range SYSCLK Frequency Range
  * @{
  */
#define HAL_RCU_SYSCLK_FREQ_MIN                   (32000UL)                        /*!< Min SYSCLK freq (LSI) */
#define HAL_RCU_SYSCLK_FREQ_MAX                   (200000000UL)                    /*!< Max SYSCLK freq */
/** @} */

/** @name HAL_RCU_RstPendingMskTypeDef
  * @brief System reset source flags mask
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_RCU_RstSrcPendingMskTypeDef           LL_RCU_SRSR_RstSrcMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_RCU_SRSR_RstSrcMskTypeDef HAL_RCU_RstSrcPendingMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_RCU_RESETSOURCE_FLAG_MCLR             (LL_RCU_SRSR_MCR)   /*!< NRST (MCLR) pin reset      */
#define HAL_RCU_RESETSOURCE_FLAG_LVD              (LL_RCU_SRSR_LPR)   /*!< LVD low voltage reset      */
#define HAL_RCU_RESETSOURCE_FLAG_SYSREQ           (LL_RCU_SRSR_SQR)   /*!< SYSRESETREQ software reset */
#define HAL_RCU_RESETSOURCE_FLAG_LOCKUP           (LL_RCU_SRSR_LKR)   /*!< Cortex LOCKUP reset        */
#define HAL_RCU_RESETSOURCE_FLAG_IWDG             (LL_RCU_SRSR_IWR)   /*!< IWDG reset                 */
#define HAL_RCU_RESETSOURCE_FLAG_WWDG             (LL_RCU_SRSR_WWR)   /*!< WWDG reset                 */

#define HAL_RCU_RESETSOURCE_FLAG_ALL              (HAL_RCU_RESETSOURCE_FLAG_MCLR   | HAL_RCU_RESETSOURCE_FLAG_LVD    | \
                                                   HAL_RCU_RESETSOURCE_FLAG_SYSREQ | HAL_RCU_RESETSOURCE_FLAG_LOCKUP | \
                                                   HAL_RCU_RESETSOURCE_FLAG_IWDG   | HAL_RCU_RESETSOURCE_FLAG_WWDG)
/** @} */

/** @name HAL_RCU_RstSrcEnMskTypeDef
  * @brief System reset source enable mask
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_RCU_RstSrcEnMskTypeDef                LL_RCU_SRSR_RstSrcMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_RCU_SRSR_RstSrcMskTypeDef HAL_RCU_RstSrcEnMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_RCU_RESETSOURCE_EN_SYSREQ             (LL_RCU_SRSR_SQR)   /*!< SYSRESETREQ software reset */
#define HAL_RCU_RESETSOURCE_EN_LOCKUP             (LL_RCU_SRSR_LKR)   /*!< Cortex LOCKUP reset        */
#define HAL_RCU_RESETSOURCE_EN_IWDG               (LL_RCU_SRSR_IWR)   /*!< IWDG reset                 */
#define HAL_RCU_RESETSOURCE_EN_WWDG               (LL_RCU_SRSR_WWR)   /*!< WWDG reset                 */

#define HAL_RCU_RESETSOURCE_EN_ALL                (HAL_RCU_RESETSOURCE_EN_SYSREQ | HAL_RCU_RESETSOURCE_EN_LOCKUP | \
                                                   HAL_RCU_RESETSOURCE_EN_IWDG   | HAL_RCU_RESETSOURCE_EN_WWDG)
/** @} */

/** @name HAL_RCU_OscillatorMskTypeDef 
  * @brief RCU HAL Oscillator Type
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_RCU_OscillatorMskTypeDef              uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_RCU_OscillatorMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_RCU_OSCILLATORTYPE_NONE               (0UL)             /*!< No oscillator  */
#define HAL_RCU_OSCILLATORTYPE_HSE                (1UL << 0U)       /*!< HSE oscillator */
#define HAL_RCU_OSCILLATORTYPE_HSI                (1UL << 1U)       /*!< HSI oscillator */
#define HAL_RCU_OSCILLATORTYPE_LSE                (1UL << 2U)       /*!< LSE oscillator */
#define HAL_RCU_OSCILLATORTYPE_LSI                (1UL << 3U)       /*!< LSI oscillator */
/** @} */


/** @name HAL_RCU_ClockMskTypeDef
  * @brief RCU HAL System Clock Type
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_RCU_ClockMskTypeDef                   uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_RCU_ClockMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_RCU_CLOCKTYPE_SYSCLK                  (1UL << 0U)       /*!< System clock selection */
#define HAL_RCU_CLOCKTYPE_HCLK                    (1UL << 1U)       /*!< AHB clock divider      */
#define HAL_RCU_CLOCKTYPE_PCLK0                   (1UL << 2U)       /*!< APB0 clock divider     */
#define HAL_RCU_CLOCKTYPE_PCLK1                   (1UL << 3U)       /*!< APB1 clock divider     */
/** @} */


/**
  * @}
  */ /* RCU_HAL_Exported_Constants */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup RCU_HAL_Exported_Types RCU HAL Exported Types
  * @brief    RCU HAL Exported Types
  * @{
  */

/**
  * @brief RCU PLL Band Definition
  */
typedef enum
{
    HAL_RCU_PLL_BAND_0  = LL_RCU_PLL_BAND_0,   /*!< RCU PLL Band 0 */
    HAL_RCU_PLL_BAND_1  = LL_RCU_PLL_BAND_1,   /*!< RCU PLL Band 1 */
    HAL_RCU_PLL_BAND_2  = LL_RCU_PLL_BAND_2,   /*!< RCU PLL Band 2 */
    HAL_RCU_PLL_BAND_3  = LL_RCU_PLL_BAND_3    /*!< RCU PLL Band 3 */
} HAL_RCU_PllBandTypeDef;

/**
  * @brief RCU HSE State Definition
  */
typedef enum
{
    HAL_RCU_HSE_OFF    = LL_RCU_HSE_OFF,  /*!< HSE clock deactivation */
    HAL_RCU_HSE_ON     = LL_RCU_HSE_ON,   /*!< HSE clock activation */
} HAL_RCU_HSEStateTypeDef;

/**
  * @brief RCU HSI State Definition
  */
typedef enum
{
    HAL_RCU_HSI_OFF   = LL_RCU_HSI_OFF,   /*!< HSI clock deactivation */
    HAL_RCU_HSI_ON    = LL_RCU_HSI_ON     /*!< HSI clock activation */
} HAL_RCU_HSIStateTypeDef;

/**
  * @brief RCU PLL State Definition
  */
typedef enum
{
    HAL_RCU_PLL_NONE  = 0UL,  /*!< No PLL */
    HAL_RCU_PLL_OFF   = 1UL,  /*!< PLL clock deactivation */
    HAL_RCU_PLL_ON    = 2UL   /*!< PLL clock activation */
} HAL_RCU_PLLStateTypeDef;


/** @defgroup HAL_RCU_EC_System_Clock_Source RCU HAL System Clock Source
  * @{
  */

/**
  * @brief RCU HAL AHB Clock Divider
  */
typedef enum
{
    HAL_RCU_AHB_DIV1  = LL_RCU_AHB_DIV1,
    HAL_RCU_AHB_DIV2  = LL_RCU_AHB_DIV2,
    HAL_RCU_AHB_DIV3  = LL_RCU_AHB_DIV3,
    HAL_RCU_AHB_DIV4  = LL_RCU_AHB_DIV4,
    HAL_RCU_AHB_DIV5  = LL_RCU_AHB_DIV5,
    HAL_RCU_AHB_DIV6  = LL_RCU_AHB_DIV6,
    HAL_RCU_AHB_DIV7  = LL_RCU_AHB_DIV7,
    HAL_RCU_AHB_DIV8  = LL_RCU_AHB_DIV8,
    HAL_RCU_AHB_DIV9  = LL_RCU_AHB_DIV9,
    HAL_RCU_AHB_DIV10 = LL_RCU_AHB_DIV10,
    HAL_RCU_AHB_DIV11 = LL_RCU_AHB_DIV11,
    HAL_RCU_AHB_DIV12 = LL_RCU_AHB_DIV12,
    HAL_RCU_AHB_DIV13 = LL_RCU_AHB_DIV13,
    HAL_RCU_AHB_DIV14 = LL_RCU_AHB_DIV14,
    HAL_RCU_AHB_DIV15 = LL_RCU_AHB_DIV15,
    HAL_RCU_AHB_DIV16 = LL_RCU_AHB_DIV16,
    HAL_RCU_AHB_DIV17 = LL_RCU_AHB_DIV17,
    HAL_RCU_AHB_DIV18 = LL_RCU_AHB_DIV18,
    HAL_RCU_AHB_DIV19 = LL_RCU_AHB_DIV19,
    HAL_RCU_AHB_DIV20 = LL_RCU_AHB_DIV20,
    HAL_RCU_AHB_DIV21 = LL_RCU_AHB_DIV21,
    HAL_RCU_AHB_DIV22 = LL_RCU_AHB_DIV22,
    HAL_RCU_AHB_DIV23 = LL_RCU_AHB_DIV23,
    HAL_RCU_AHB_DIV24 = LL_RCU_AHB_DIV24,
    HAL_RCU_AHB_DIV25 = LL_RCU_AHB_DIV25,
    HAL_RCU_AHB_DIV26 = LL_RCU_AHB_DIV26,
    HAL_RCU_AHB_DIV27 = LL_RCU_AHB_DIV27,
    HAL_RCU_AHB_DIV28 = LL_RCU_AHB_DIV28,
    HAL_RCU_AHB_DIV29 = LL_RCU_AHB_DIV29,
    HAL_RCU_AHB_DIV30 = LL_RCU_AHB_DIV30,
    HAL_RCU_AHB_DIV31 = LL_RCU_AHB_DIV31,
    HAL_RCU_AHB_DIV32 = LL_RCU_AHB_DIV32,
    HAL_RCU_AHB_DIV33 = LL_RCU_AHB_DIV33,
    HAL_RCU_AHB_DIV34 = LL_RCU_AHB_DIV34,
    HAL_RCU_AHB_DIV35 = LL_RCU_AHB_DIV35,
    HAL_RCU_AHB_DIV36 = LL_RCU_AHB_DIV36,
    HAL_RCU_AHB_DIV37 = LL_RCU_AHB_DIV37,
    HAL_RCU_AHB_DIV38 = LL_RCU_AHB_DIV38,
    HAL_RCU_AHB_DIV39 = LL_RCU_AHB_DIV39,
    HAL_RCU_AHB_DIV40 = LL_RCU_AHB_DIV40,
    HAL_RCU_AHB_DIV41 = LL_RCU_AHB_DIV41,
    HAL_RCU_AHB_DIV42 = LL_RCU_AHB_DIV42,
    HAL_RCU_AHB_DIV43 = LL_RCU_AHB_DIV43,
    HAL_RCU_AHB_DIV44 = LL_RCU_AHB_DIV44,
    HAL_RCU_AHB_DIV45 = LL_RCU_AHB_DIV45,
    HAL_RCU_AHB_DIV46 = LL_RCU_AHB_DIV46,
    HAL_RCU_AHB_DIV47 = LL_RCU_AHB_DIV47,
    HAL_RCU_AHB_DIV48 = LL_RCU_AHB_DIV48,
    HAL_RCU_AHB_DIV49 = LL_RCU_AHB_DIV49,
    HAL_RCU_AHB_DIV50 = LL_RCU_AHB_DIV50,
    HAL_RCU_AHB_DIV51 = LL_RCU_AHB_DIV51,
    HAL_RCU_AHB_DIV52 = LL_RCU_AHB_DIV52,
    HAL_RCU_AHB_DIV53 = LL_RCU_AHB_DIV53,
    HAL_RCU_AHB_DIV54 = LL_RCU_AHB_DIV54,
    HAL_RCU_AHB_DIV55 = LL_RCU_AHB_DIV55,
    HAL_RCU_AHB_DIV56 = LL_RCU_AHB_DIV56,
    HAL_RCU_AHB_DIV57 = LL_RCU_AHB_DIV57,
    HAL_RCU_AHB_DIV58 = LL_RCU_AHB_DIV58,
    HAL_RCU_AHB_DIV59 = LL_RCU_AHB_DIV59,
    HAL_RCU_AHB_DIV60 = LL_RCU_AHB_DIV60,
    HAL_RCU_AHB_DIV61 = LL_RCU_AHB_DIV61,
    HAL_RCU_AHB_DIV62 = LL_RCU_AHB_DIV62,
    HAL_RCU_AHB_DIV63 = LL_RCU_AHB_DIV63,
    HAL_RCU_AHB_DIV64 = LL_RCU_AHB_DIV64
} HAL_RCU_AHBClkDivTypeDef;


/**
  * @brief RCU HAL APB0 Clock Divider
  */
typedef enum
{
    HAL_RCU_APB0_DIV1  = LL_RCU_APB0_DIV1,
    HAL_RCU_APB0_DIV2  = LL_RCU_APB0_DIV2,
    HAL_RCU_APB0_DIV3  = LL_RCU_APB0_DIV3,
    HAL_RCU_APB0_DIV4  = LL_RCU_APB0_DIV4,
    HAL_RCU_APB0_DIV5  = LL_RCU_APB0_DIV5,
    HAL_RCU_APB0_DIV6  = LL_RCU_APB0_DIV6,
    HAL_RCU_APB0_DIV7  = LL_RCU_APB0_DIV7,
    HAL_RCU_APB0_DIV8  = LL_RCU_APB0_DIV8,
    HAL_RCU_APB0_DIV9  = LL_RCU_APB0_DIV9,
    HAL_RCU_APB0_DIV10 = LL_RCU_APB0_DIV10,
    HAL_RCU_APB0_DIV11 = LL_RCU_APB0_DIV11,
    HAL_RCU_APB0_DIV12 = LL_RCU_APB0_DIV12,
    HAL_RCU_APB0_DIV13 = LL_RCU_APB0_DIV13,
    HAL_RCU_APB0_DIV14 = LL_RCU_APB0_DIV14,
    HAL_RCU_APB0_DIV15 = LL_RCU_APB0_DIV15,
    HAL_RCU_APB0_DIV16 = LL_RCU_APB0_DIV16
} HAL_RCU_APB0ClkDivTypeDef;


/**
  * @brief RCU HAL APB1 Clock Divider
  */
typedef enum
{
    HAL_RCU_APB1_DIV1  = LL_RCU_APB1_DIV1,
    HAL_RCU_APB1_DIV2  = LL_RCU_APB1_DIV2,
    HAL_RCU_APB1_DIV3  = LL_RCU_APB1_DIV3,
    HAL_RCU_APB1_DIV4  = LL_RCU_APB1_DIV4,
    HAL_RCU_APB1_DIV5  = LL_RCU_APB1_DIV5,
    HAL_RCU_APB1_DIV6  = LL_RCU_APB1_DIV6,
    HAL_RCU_APB1_DIV7  = LL_RCU_APB1_DIV7,
    HAL_RCU_APB1_DIV8  = LL_RCU_APB1_DIV8,
    HAL_RCU_APB1_DIV9  = LL_RCU_APB1_DIV9,
    HAL_RCU_APB1_DIV10 = LL_RCU_APB1_DIV10,
    HAL_RCU_APB1_DIV11 = LL_RCU_APB1_DIV11,
    HAL_RCU_APB1_DIV12 = LL_RCU_APB1_DIV12,
    HAL_RCU_APB1_DIV13 = LL_RCU_APB1_DIV13,
    HAL_RCU_APB1_DIV14 = LL_RCU_APB1_DIV14,
    HAL_RCU_APB1_DIV15 = LL_RCU_APB1_DIV15,
    HAL_RCU_APB1_DIV16 = LL_RCU_APB1_DIV16
} HAL_RCU_APB1ClkDivTypeDef;

/**
  * @brief RCU HAL Function Clock Divider
  */
typedef enum
{
    HAL_RCU_FUNC_CLK_DIV1  = LL_RCU_FUNC_CLK_DIV1,
    HAL_RCU_FUNC_CLK_DIV2  = LL_RCU_FUNC_CLK_DIV2,
    HAL_RCU_FUNC_CLK_DIV3  = LL_RCU_FUNC_CLK_DIV3,
    HAL_RCU_FUNC_CLK_DIV4  = LL_RCU_FUNC_CLK_DIV4,
    HAL_RCU_FUNC_CLK_DIV5  = LL_RCU_FUNC_CLK_DIV5,
    HAL_RCU_FUNC_CLK_DIV6  = LL_RCU_FUNC_CLK_DIV6,
    HAL_RCU_FUNC_CLK_DIV7  = LL_RCU_FUNC_CLK_DIV7,
    HAL_RCU_FUNC_CLK_DIV8  = LL_RCU_FUNC_CLK_DIV8,
    HAL_RCU_FUNC_CLK_DIV9  = LL_RCU_FUNC_CLK_DIV9,
    HAL_RCU_FUNC_CLK_DIV10 = LL_RCU_FUNC_CLK_DIV10,
    HAL_RCU_FUNC_CLK_DIV11 = LL_RCU_FUNC_CLK_DIV11,
    HAL_RCU_FUNC_CLK_DIV12 = LL_RCU_FUNC_CLK_DIV12,
    HAL_RCU_FUNC_CLK_DIV13 = LL_RCU_FUNC_CLK_DIV13,
    HAL_RCU_FUNC_CLK_DIV14 = LL_RCU_FUNC_CLK_DIV14,
    HAL_RCU_FUNC_CLK_DIV15 = LL_RCU_FUNC_CLK_DIV15,
    HAL_RCU_FUNC_CLK_DIV16 = LL_RCU_FUNC_CLK_DIV16
} HAL_RCU_FuncClkDivTypeDef;

/**
  * @brief GPIO Debounce Clock Divider Definition
  */
typedef enum
{
    HAL_RCU_GPIO_DBC_CLK_DIV1     = LL_RCU_GPIO_DBC_CLK_DIV1,     /*!< GPIO Debounce Clock Divider 1     */
    HAL_RCU_GPIO_DBC_CLK_DIV2     = LL_RCU_GPIO_DBC_CLK_DIV2,     /*!< GPIO Debounce Clock Divider 2     */
    HAL_RCU_GPIO_DBC_CLK_DIV3     = LL_RCU_GPIO_DBC_CLK_DIV3,     /*!< GPIO Debounce Clock Divider 3     */
    HAL_RCU_GPIO_DBC_CLK_DIV4     = LL_RCU_GPIO_DBC_CLK_DIV4,     /*!< GPIO Debounce Clock Divider 4     */
    HAL_RCU_GPIO_DBC_CLK_DIV5     = LL_RCU_GPIO_DBC_CLK_DIV5,     /*!< GPIO Debounce Clock Divider 5     */
    HAL_RCU_GPIO_DBC_CLK_DIV6     = LL_RCU_GPIO_DBC_CLK_DIV6,     /*!< GPIO Debounce Clock Divider 6     */
    HAL_RCU_GPIO_DBC_CLK_DIV7     = LL_RCU_GPIO_DBC_CLK_DIV7,     /*!< GPIO Debounce Clock Divider 7     */
    HAL_RCU_GPIO_DBC_CLK_DIV8     = LL_RCU_GPIO_DBC_CLK_DIV8,     /*!< GPIO Debounce Clock Divider 8     */
    HAL_RCU_GPIO_DBC_CLK_DIV9     = LL_RCU_GPIO_DBC_CLK_DIV9,     /*!< GPIO Debounce Clock Divider 9     */
    HAL_RCU_GPIO_DBC_CLK_DIV10    = LL_RCU_GPIO_DBC_CLK_DIV10,    /*!< GPIO Debounce Clock Divider 10    */
    HAL_RCU_GPIO_DBC_CLK_DIV11    = LL_RCU_GPIO_DBC_CLK_DIV11,    /*!< GPIO Debounce Clock Divider 11    */
    HAL_RCU_GPIO_DBC_CLK_DIV12    = LL_RCU_GPIO_DBC_CLK_DIV12,    /*!< GPIO Debounce Clock Divider 12    */
    HAL_RCU_GPIO_DBC_CLK_DIV13    = LL_RCU_GPIO_DBC_CLK_DIV13,    /*!< GPIO Debounce Clock Divider 13    */
    HAL_RCU_GPIO_DBC_CLK_DIV14    = LL_RCU_GPIO_DBC_CLK_DIV14,    /*!< GPIO Debounce Clock Divider 14    */
    HAL_RCU_GPIO_DBC_CLK_DIV15    = LL_RCU_GPIO_DBC_CLK_DIV15,    /*!< GPIO Debounce Clock Divider 15    */
    HAL_RCU_GPIO_DBC_CLK_DIV16    = LL_RCU_GPIO_DBC_CLK_DIV16,    /*!< GPIO Debounce Clock Divider 16    */
    HAL_RCU_GPIO_DBC_CLK_DIV17    = LL_RCU_GPIO_DBC_CLK_DIV17,    /*!< GPIO Debounce Clock Divider 17    */
    HAL_RCU_GPIO_DBC_CLK_DIV18    = LL_RCU_GPIO_DBC_CLK_DIV18,    /*!< GPIO Debounce Clock Divider 18    */
    HAL_RCU_GPIO_DBC_CLK_DIV19    = LL_RCU_GPIO_DBC_CLK_DIV19,    /*!< GPIO Debounce Clock Divider 19    */
    HAL_RCU_GPIO_DBC_CLK_DIV20    = LL_RCU_GPIO_DBC_CLK_DIV20,    /*!< GPIO Debounce Clock Divider 20    */
    HAL_RCU_GPIO_DBC_CLK_DIV21    = LL_RCU_GPIO_DBC_CLK_DIV21,    /*!< GPIO Debounce Clock Divider 21    */
    HAL_RCU_GPIO_DBC_CLK_DIV22    = LL_RCU_GPIO_DBC_CLK_DIV22,    /*!< GPIO Debounce Clock Divider 22    */
    HAL_RCU_GPIO_DBC_CLK_DIV23    = LL_RCU_GPIO_DBC_CLK_DIV23,    /*!< GPIO Debounce Clock Divider 23    */
    HAL_RCU_GPIO_DBC_CLK_DIV24    = LL_RCU_GPIO_DBC_CLK_DIV24,    /*!< GPIO Debounce Clock Divider 24    */
    HAL_RCU_GPIO_DBC_CLK_DIV25    = LL_RCU_GPIO_DBC_CLK_DIV25,    /*!< GPIO Debounce Clock Divider 25    */
    HAL_RCU_GPIO_DBC_CLK_DIV26    = LL_RCU_GPIO_DBC_CLK_DIV26,    /*!< GPIO Debounce Clock Divider 26    */
    HAL_RCU_GPIO_DBC_CLK_DIV27    = LL_RCU_GPIO_DBC_CLK_DIV27,    /*!< GPIO Debounce Clock Divider 27    */
    HAL_RCU_GPIO_DBC_CLK_DIV28    = LL_RCU_GPIO_DBC_CLK_DIV28,    /*!< GPIO Debounce Clock Divider 28    */
    HAL_RCU_GPIO_DBC_CLK_DIV29    = LL_RCU_GPIO_DBC_CLK_DIV29,    /*!< GPIO Debounce Clock Divider 29    */
    HAL_RCU_GPIO_DBC_CLK_DIV30    = LL_RCU_GPIO_DBC_CLK_DIV30,    /*!< GPIO Debounce Clock Divider 30    */
    HAL_RCU_GPIO_DBC_CLK_DIV31    = LL_RCU_GPIO_DBC_CLK_DIV31,    /*!< GPIO Debounce Clock Divider 31    */
    HAL_RCU_GPIO_DBC_CLK_DIV32    = LL_RCU_GPIO_DBC_CLK_DIV32,    /*!< GPIO Debounce Clock Divider 32    */
    HAL_RCU_GPIO_DBC_CLK_DIV33    = LL_RCU_GPIO_DBC_CLK_DIV33,    /*!< GPIO Debounce Clock Divider 33    */
    HAL_RCU_GPIO_DBC_CLK_DIV34    = LL_RCU_GPIO_DBC_CLK_DIV34,    /*!< GPIO Debounce Clock Divider 34    */
    HAL_RCU_GPIO_DBC_CLK_DIV35    = LL_RCU_GPIO_DBC_CLK_DIV35,    /*!< GPIO Debounce Clock Divider 35    */
    HAL_RCU_GPIO_DBC_CLK_DIV36    = LL_RCU_GPIO_DBC_CLK_DIV36,    /*!< GPIO Debounce Clock Divider 36    */
    HAL_RCU_GPIO_DBC_CLK_DIV37    = LL_RCU_GPIO_DBC_CLK_DIV37,    /*!< GPIO Debounce Clock Divider 37    */
    HAL_RCU_GPIO_DBC_CLK_DIV38    = LL_RCU_GPIO_DBC_CLK_DIV38,    /*!< GPIO Debounce Clock Divider 38    */
    HAL_RCU_GPIO_DBC_CLK_DIV39    = LL_RCU_GPIO_DBC_CLK_DIV39,    /*!< GPIO Debounce Clock Divider 39    */
    HAL_RCU_GPIO_DBC_CLK_DIV40    = LL_RCU_GPIO_DBC_CLK_DIV40,    /*!< GPIO Debounce Clock Divider 40    */
    HAL_RCU_GPIO_DBC_CLK_DIV41    = LL_RCU_GPIO_DBC_CLK_DIV41,    /*!< GPIO Debounce Clock Divider 41    */
    HAL_RCU_GPIO_DBC_CLK_DIV42    = LL_RCU_GPIO_DBC_CLK_DIV42,    /*!< GPIO Debounce Clock Divider 42    */
    HAL_RCU_GPIO_DBC_CLK_DIV43    = LL_RCU_GPIO_DBC_CLK_DIV43,    /*!< GPIO Debounce Clock Divider 43    */
    HAL_RCU_GPIO_DBC_CLK_DIV44    = LL_RCU_GPIO_DBC_CLK_DIV44,    /*!< GPIO Debounce Clock Divider 44    */
    HAL_RCU_GPIO_DBC_CLK_DIV45    = LL_RCU_GPIO_DBC_CLK_DIV45,    /*!< GPIO Debounce Clock Divider 45    */
    HAL_RCU_GPIO_DBC_CLK_DIV46    = LL_RCU_GPIO_DBC_CLK_DIV46,    /*!< GPIO Debounce Clock Divider 46    */
    HAL_RCU_GPIO_DBC_CLK_DIV47    = LL_RCU_GPIO_DBC_CLK_DIV47,    /*!< GPIO Debounce Clock Divider 47    */
    HAL_RCU_GPIO_DBC_CLK_DIV48    = LL_RCU_GPIO_DBC_CLK_DIV48,    /*!< GPIO Debounce Clock Divider 48    */
    HAL_RCU_GPIO_DBC_CLK_DIV49    = LL_RCU_GPIO_DBC_CLK_DIV49,    /*!< GPIO Debounce Clock Divider 49    */
    HAL_RCU_GPIO_DBC_CLK_DIV50    = LL_RCU_GPIO_DBC_CLK_DIV50,    /*!< GPIO Debounce Clock Divider 50    */
    HAL_RCU_GPIO_DBC_CLK_DIV51    = LL_RCU_GPIO_DBC_CLK_DIV51,    /*!< GPIO Debounce Clock Divider 51    */
    HAL_RCU_GPIO_DBC_CLK_DIV52    = LL_RCU_GPIO_DBC_CLK_DIV52,    /*!< GPIO Debounce Clock Divider 52    */
    HAL_RCU_GPIO_DBC_CLK_DIV53    = LL_RCU_GPIO_DBC_CLK_DIV53,    /*!< GPIO Debounce Clock Divider 53    */
    HAL_RCU_GPIO_DBC_CLK_DIV54    = LL_RCU_GPIO_DBC_CLK_DIV54,    /*!< GPIO Debounce Clock Divider 54    */
    HAL_RCU_GPIO_DBC_CLK_DIV55    = LL_RCU_GPIO_DBC_CLK_DIV55,    /*!< GPIO Debounce Clock Divider 55    */
    HAL_RCU_GPIO_DBC_CLK_DIV56    = LL_RCU_GPIO_DBC_CLK_DIV56,    /*!< GPIO Debounce Clock Divider 56    */
    HAL_RCU_GPIO_DBC_CLK_DIV57    = LL_RCU_GPIO_DBC_CLK_DIV57,    /*!< GPIO Debounce Clock Divider 57    */
    HAL_RCU_GPIO_DBC_CLK_DIV58    = LL_RCU_GPIO_DBC_CLK_DIV58,    /*!< GPIO Debounce Clock Divider 58    */
    HAL_RCU_GPIO_DBC_CLK_DIV59    = LL_RCU_GPIO_DBC_CLK_DIV59,    /*!< GPIO Debounce Clock Divider 59    */
    HAL_RCU_GPIO_DBC_CLK_DIV60    = LL_RCU_GPIO_DBC_CLK_DIV60,    /*!< GPIO Debounce Clock Divider 60    */
    HAL_RCU_GPIO_DBC_CLK_DIV61    = LL_RCU_GPIO_DBC_CLK_DIV61,    /*!< GPIO Debounce Clock Divider 61    */
    HAL_RCU_GPIO_DBC_CLK_DIV62    = LL_RCU_GPIO_DBC_CLK_DIV62,    /*!< GPIO Debounce Clock Divider 62    */
    HAL_RCU_GPIO_DBC_CLK_DIV63    = LL_RCU_GPIO_DBC_CLK_DIV63,    /*!< GPIO Debounce Clock Divider 63    */
    HAL_RCU_GPIO_DBC_CLK_DIV64    = LL_RCU_GPIO_DBC_CLK_DIV64,    /*!< GPIO Debounce Clock Divider 64    */
    HAL_RCU_GPIO_DBC_CLK_DIV65    = LL_RCU_GPIO_DBC_CLK_DIV65,    /*!< GPIO Debounce Clock Divider 65    */
    HAL_RCU_GPIO_DBC_CLK_DIV66    = LL_RCU_GPIO_DBC_CLK_DIV66,    /*!< GPIO Debounce Clock Divider 66    */
    HAL_RCU_GPIO_DBC_CLK_DIV67    = LL_RCU_GPIO_DBC_CLK_DIV67,    /*!< GPIO Debounce Clock Divider 67    */
    HAL_RCU_GPIO_DBC_CLK_DIV68    = LL_RCU_GPIO_DBC_CLK_DIV68,    /*!< GPIO Debounce Clock Divider 68    */
    HAL_RCU_GPIO_DBC_CLK_DIV69    = LL_RCU_GPIO_DBC_CLK_DIV69,    /*!< GPIO Debounce Clock Divider 69    */
    HAL_RCU_GPIO_DBC_CLK_DIV70    = LL_RCU_GPIO_DBC_CLK_DIV70,    /*!< GPIO Debounce Clock Divider 70    */
    HAL_RCU_GPIO_DBC_CLK_DIV71    = LL_RCU_GPIO_DBC_CLK_DIV71,    /*!< GPIO Debounce Clock Divider 71    */
    HAL_RCU_GPIO_DBC_CLK_DIV72    = LL_RCU_GPIO_DBC_CLK_DIV72,    /*!< GPIO Debounce Clock Divider 72    */
    HAL_RCU_GPIO_DBC_CLK_DIV73    = LL_RCU_GPIO_DBC_CLK_DIV73,    /*!< GPIO Debounce Clock Divider 73    */
    HAL_RCU_GPIO_DBC_CLK_DIV74    = LL_RCU_GPIO_DBC_CLK_DIV74,    /*!< GPIO Debounce Clock Divider 74    */
    HAL_RCU_GPIO_DBC_CLK_DIV75    = LL_RCU_GPIO_DBC_CLK_DIV75,    /*!< GPIO Debounce Clock Divider 75    */
    HAL_RCU_GPIO_DBC_CLK_DIV76    = LL_RCU_GPIO_DBC_CLK_DIV76,    /*!< GPIO Debounce Clock Divider 76    */
    HAL_RCU_GPIO_DBC_CLK_DIV77    = LL_RCU_GPIO_DBC_CLK_DIV77,    /*!< GPIO Debounce Clock Divider 77    */
    HAL_RCU_GPIO_DBC_CLK_DIV78    = LL_RCU_GPIO_DBC_CLK_DIV78,    /*!< GPIO Debounce Clock Divider 78    */
    HAL_RCU_GPIO_DBC_CLK_DIV79    = LL_RCU_GPIO_DBC_CLK_DIV79,    /*!< GPIO Debounce Clock Divider 79    */
    HAL_RCU_GPIO_DBC_CLK_DIV80    = LL_RCU_GPIO_DBC_CLK_DIV80,    /*!< GPIO Debounce Clock Divider 80    */
    HAL_RCU_GPIO_DBC_CLK_DIV81    = LL_RCU_GPIO_DBC_CLK_DIV81,    /*!< GPIO Debounce Clock Divider 81    */
    HAL_RCU_GPIO_DBC_CLK_DIV82    = LL_RCU_GPIO_DBC_CLK_DIV82,    /*!< GPIO Debounce Clock Divider 82    */
    HAL_RCU_GPIO_DBC_CLK_DIV83    = LL_RCU_GPIO_DBC_CLK_DIV83,    /*!< GPIO Debounce Clock Divider 83    */
    HAL_RCU_GPIO_DBC_CLK_DIV84    = LL_RCU_GPIO_DBC_CLK_DIV84,    /*!< GPIO Debounce Clock Divider 84    */
    HAL_RCU_GPIO_DBC_CLK_DIV85    = LL_RCU_GPIO_DBC_CLK_DIV85,    /*!< GPIO Debounce Clock Divider 85    */
    HAL_RCU_GPIO_DBC_CLK_DIV86    = LL_RCU_GPIO_DBC_CLK_DIV86,    /*!< GPIO Debounce Clock Divider 86    */
    HAL_RCU_GPIO_DBC_CLK_DIV87    = LL_RCU_GPIO_DBC_CLK_DIV87,    /*!< GPIO Debounce Clock Divider 87    */
    HAL_RCU_GPIO_DBC_CLK_DIV88    = LL_RCU_GPIO_DBC_CLK_DIV88,    /*!< GPIO Debounce Clock Divider 88    */
    HAL_RCU_GPIO_DBC_CLK_DIV89    = LL_RCU_GPIO_DBC_CLK_DIV89,    /*!< GPIO Debounce Clock Divider 89    */
    HAL_RCU_GPIO_DBC_CLK_DIV90    = LL_RCU_GPIO_DBC_CLK_DIV90,    /*!< GPIO Debounce Clock Divider 90    */
    HAL_RCU_GPIO_DBC_CLK_DIV91    = LL_RCU_GPIO_DBC_CLK_DIV91,    /*!< GPIO Debounce Clock Divider 91    */
    HAL_RCU_GPIO_DBC_CLK_DIV92    = LL_RCU_GPIO_DBC_CLK_DIV92,    /*!< GPIO Debounce Clock Divider 92    */
    HAL_RCU_GPIO_DBC_CLK_DIV93    = LL_RCU_GPIO_DBC_CLK_DIV93,    /*!< GPIO Debounce Clock Divider 93    */
    HAL_RCU_GPIO_DBC_CLK_DIV94    = LL_RCU_GPIO_DBC_CLK_DIV94,    /*!< GPIO Debounce Clock Divider 94    */
    HAL_RCU_GPIO_DBC_CLK_DIV95    = LL_RCU_GPIO_DBC_CLK_DIV95,    /*!< GPIO Debounce Clock Divider 95    */
    HAL_RCU_GPIO_DBC_CLK_DIV96    = LL_RCU_GPIO_DBC_CLK_DIV96,    /*!< GPIO Debounce Clock Divider 96    */
    HAL_RCU_GPIO_DBC_CLK_DIV97    = LL_RCU_GPIO_DBC_CLK_DIV97,    /*!< GPIO Debounce Clock Divider 97    */
    HAL_RCU_GPIO_DBC_CLK_DIV98    = LL_RCU_GPIO_DBC_CLK_DIV98,    /*!< GPIO Debounce Clock Divider 98    */
    HAL_RCU_GPIO_DBC_CLK_DIV99    = LL_RCU_GPIO_DBC_CLK_DIV99,    /*!< GPIO Debounce Clock Divider 99    */
    HAL_RCU_GPIO_DBC_CLK_DIV100   = LL_RCU_GPIO_DBC_CLK_DIV100,   /*!< GPIO Debounce Clock Divider 100   */
    HAL_RCU_GPIO_DBC_CLK_DIV101   = LL_RCU_GPIO_DBC_CLK_DIV101,   /*!< GPIO Debounce Clock Divider 101   */
    HAL_RCU_GPIO_DBC_CLK_DIV102   = LL_RCU_GPIO_DBC_CLK_DIV102,   /*!< GPIO Debounce Clock Divider 102   */
    HAL_RCU_GPIO_DBC_CLK_DIV103   = LL_RCU_GPIO_DBC_CLK_DIV103,   /*!< GPIO Debounce Clock Divider 103   */
    HAL_RCU_GPIO_DBC_CLK_DIV104   = LL_RCU_GPIO_DBC_CLK_DIV104,   /*!< GPIO Debounce Clock Divider 104   */
    HAL_RCU_GPIO_DBC_CLK_DIV105   = LL_RCU_GPIO_DBC_CLK_DIV105,   /*!< GPIO Debounce Clock Divider 105   */
    HAL_RCU_GPIO_DBC_CLK_DIV106   = LL_RCU_GPIO_DBC_CLK_DIV106,   /*!< GPIO Debounce Clock Divider 106   */
    HAL_RCU_GPIO_DBC_CLK_DIV107   = LL_RCU_GPIO_DBC_CLK_DIV107,   /*!< GPIO Debounce Clock Divider 107   */
    HAL_RCU_GPIO_DBC_CLK_DIV108   = LL_RCU_GPIO_DBC_CLK_DIV108,   /*!< GPIO Debounce Clock Divider 108   */
    HAL_RCU_GPIO_DBC_CLK_DIV109   = LL_RCU_GPIO_DBC_CLK_DIV109,   /*!< GPIO Debounce Clock Divider 109   */
    HAL_RCU_GPIO_DBC_CLK_DIV110   = LL_RCU_GPIO_DBC_CLK_DIV110,   /*!< GPIO Debounce Clock Divider 110   */
    HAL_RCU_GPIO_DBC_CLK_DIV111   = LL_RCU_GPIO_DBC_CLK_DIV111,   /*!< GPIO Debounce Clock Divider 111   */
    HAL_RCU_GPIO_DBC_CLK_DIV112   = LL_RCU_GPIO_DBC_CLK_DIV112,   /*!< GPIO Debounce Clock Divider 112   */
    HAL_RCU_GPIO_DBC_CLK_DIV113   = LL_RCU_GPIO_DBC_CLK_DIV113,   /*!< GPIO Debounce Clock Divider 113   */
    HAL_RCU_GPIO_DBC_CLK_DIV114   = LL_RCU_GPIO_DBC_CLK_DIV114,   /*!< GPIO Debounce Clock Divider 114   */
    HAL_RCU_GPIO_DBC_CLK_DIV115   = LL_RCU_GPIO_DBC_CLK_DIV115,   /*!< GPIO Debounce Clock Divider 115   */
    HAL_RCU_GPIO_DBC_CLK_DIV116   = LL_RCU_GPIO_DBC_CLK_DIV116,   /*!< GPIO Debounce Clock Divider 116   */
    HAL_RCU_GPIO_DBC_CLK_DIV117   = LL_RCU_GPIO_DBC_CLK_DIV117,   /*!< GPIO Debounce Clock Divider 117   */
    HAL_RCU_GPIO_DBC_CLK_DIV118   = LL_RCU_GPIO_DBC_CLK_DIV118,   /*!< GPIO Debounce Clock Divider 118   */
    HAL_RCU_GPIO_DBC_CLK_DIV119   = LL_RCU_GPIO_DBC_CLK_DIV119,   /*!< GPIO Debounce Clock Divider 119   */
    HAL_RCU_GPIO_DBC_CLK_DIV120   = LL_RCU_GPIO_DBC_CLK_DIV120,   /*!< GPIO Debounce Clock Divider 120   */
    HAL_RCU_GPIO_DBC_CLK_DIV121   = LL_RCU_GPIO_DBC_CLK_DIV121,   /*!< GPIO Debounce Clock Divider 121   */
    HAL_RCU_GPIO_DBC_CLK_DIV122   = LL_RCU_GPIO_DBC_CLK_DIV122,   /*!< GPIO Debounce Clock Divider 122   */
    HAL_RCU_GPIO_DBC_CLK_DIV123   = LL_RCU_GPIO_DBC_CLK_DIV123,   /*!< GPIO Debounce Clock Divider 123   */
    HAL_RCU_GPIO_DBC_CLK_DIV124   = LL_RCU_GPIO_DBC_CLK_DIV124,   /*!< GPIO Debounce Clock Divider 124   */
    HAL_RCU_GPIO_DBC_CLK_DIV125   = LL_RCU_GPIO_DBC_CLK_DIV125,   /*!< GPIO Debounce Clock Divider 125   */
    HAL_RCU_GPIO_DBC_CLK_DIV126   = LL_RCU_GPIO_DBC_CLK_DIV126,   /*!< GPIO Debounce Clock Divider 126   */
    HAL_RCU_GPIO_DBC_CLK_DIV127   = LL_RCU_GPIO_DBC_CLK_DIV127,   /*!< GPIO Debounce Clock Divider 127   */
    HAL_RCU_GPIO_DBC_CLK_DIV128   = LL_RCU_GPIO_DBC_CLK_DIV128,   /*!< GPIO Debounce Clock Divider 128   */
    HAL_RCU_GPIO_DBC_CLK_DIV129   = LL_RCU_GPIO_DBC_CLK_DIV129,   /*!< GPIO Debounce Clock Divider 129   */
    HAL_RCU_GPIO_DBC_CLK_DIV130   = LL_RCU_GPIO_DBC_CLK_DIV130,   /*!< GPIO Debounce Clock Divider 130   */
    HAL_RCU_GPIO_DBC_CLK_DIV131   = LL_RCU_GPIO_DBC_CLK_DIV131,   /*!< GPIO Debounce Clock Divider 131   */
    HAL_RCU_GPIO_DBC_CLK_DIV132   = LL_RCU_GPIO_DBC_CLK_DIV132,   /*!< GPIO Debounce Clock Divider 132   */
    HAL_RCU_GPIO_DBC_CLK_DIV133   = LL_RCU_GPIO_DBC_CLK_DIV133,   /*!< GPIO Debounce Clock Divider 133   */
    HAL_RCU_GPIO_DBC_CLK_DIV134   = LL_RCU_GPIO_DBC_CLK_DIV134,   /*!< GPIO Debounce Clock Divider 134   */
    HAL_RCU_GPIO_DBC_CLK_DIV135   = LL_RCU_GPIO_DBC_CLK_DIV135,   /*!< GPIO Debounce Clock Divider 135   */
    HAL_RCU_GPIO_DBC_CLK_DIV136   = LL_RCU_GPIO_DBC_CLK_DIV136,   /*!< GPIO Debounce Clock Divider 136   */
    HAL_RCU_GPIO_DBC_CLK_DIV137   = LL_RCU_GPIO_DBC_CLK_DIV137,   /*!< GPIO Debounce Clock Divider 137   */
    HAL_RCU_GPIO_DBC_CLK_DIV138   = LL_RCU_GPIO_DBC_CLK_DIV138,   /*!< GPIO Debounce Clock Divider 138   */
    HAL_RCU_GPIO_DBC_CLK_DIV139   = LL_RCU_GPIO_DBC_CLK_DIV139,   /*!< GPIO Debounce Clock Divider 139   */
    HAL_RCU_GPIO_DBC_CLK_DIV140   = LL_RCU_GPIO_DBC_CLK_DIV140,   /*!< GPIO Debounce Clock Divider 140   */
    HAL_RCU_GPIO_DBC_CLK_DIV141   = LL_RCU_GPIO_DBC_CLK_DIV141,   /*!< GPIO Debounce Clock Divider 141   */
    HAL_RCU_GPIO_DBC_CLK_DIV142   = LL_RCU_GPIO_DBC_CLK_DIV142,   /*!< GPIO Debounce Clock Divider 142   */
    HAL_RCU_GPIO_DBC_CLK_DIV143   = LL_RCU_GPIO_DBC_CLK_DIV143,   /*!< GPIO Debounce Clock Divider 143   */
    HAL_RCU_GPIO_DBC_CLK_DIV144   = LL_RCU_GPIO_DBC_CLK_DIV144,   /*!< GPIO Debounce Clock Divider 144   */
    HAL_RCU_GPIO_DBC_CLK_DIV145   = LL_RCU_GPIO_DBC_CLK_DIV145,   /*!< GPIO Debounce Clock Divider 145   */
    HAL_RCU_GPIO_DBC_CLK_DIV146   = LL_RCU_GPIO_DBC_CLK_DIV146,   /*!< GPIO Debounce Clock Divider 146   */
    HAL_RCU_GPIO_DBC_CLK_DIV147   = LL_RCU_GPIO_DBC_CLK_DIV147,   /*!< GPIO Debounce Clock Divider 147   */
    HAL_RCU_GPIO_DBC_CLK_DIV148   = LL_RCU_GPIO_DBC_CLK_DIV148,   /*!< GPIO Debounce Clock Divider 148   */
    HAL_RCU_GPIO_DBC_CLK_DIV149   = LL_RCU_GPIO_DBC_CLK_DIV149,   /*!< GPIO Debounce Clock Divider 149   */
    HAL_RCU_GPIO_DBC_CLK_DIV150   = LL_RCU_GPIO_DBC_CLK_DIV150,   /*!< GPIO Debounce Clock Divider 150   */
    HAL_RCU_GPIO_DBC_CLK_DIV151   = LL_RCU_GPIO_DBC_CLK_DIV151,   /*!< GPIO Debounce Clock Divider 151   */
    HAL_RCU_GPIO_DBC_CLK_DIV152   = LL_RCU_GPIO_DBC_CLK_DIV152,   /*!< GPIO Debounce Clock Divider 152   */
    HAL_RCU_GPIO_DBC_CLK_DIV153   = LL_RCU_GPIO_DBC_CLK_DIV153,   /*!< GPIO Debounce Clock Divider 153   */
    HAL_RCU_GPIO_DBC_CLK_DIV154   = LL_RCU_GPIO_DBC_CLK_DIV154,   /*!< GPIO Debounce Clock Divider 154   */
    HAL_RCU_GPIO_DBC_CLK_DIV155   = LL_RCU_GPIO_DBC_CLK_DIV155,   /*!< GPIO Debounce Clock Divider 155   */
    HAL_RCU_GPIO_DBC_CLK_DIV156   = LL_RCU_GPIO_DBC_CLK_DIV156,   /*!< GPIO Debounce Clock Divider 156   */
    HAL_RCU_GPIO_DBC_CLK_DIV157   = LL_RCU_GPIO_DBC_CLK_DIV157,   /*!< GPIO Debounce Clock Divider 157   */
    HAL_RCU_GPIO_DBC_CLK_DIV158   = LL_RCU_GPIO_DBC_CLK_DIV158,   /*!< GPIO Debounce Clock Divider 158   */
    HAL_RCU_GPIO_DBC_CLK_DIV159   = LL_RCU_GPIO_DBC_CLK_DIV159,   /*!< GPIO Debounce Clock Divider 159   */
    HAL_RCU_GPIO_DBC_CLK_DIV160   = LL_RCU_GPIO_DBC_CLK_DIV160,   /*!< GPIO Debounce Clock Divider 160   */
    HAL_RCU_GPIO_DBC_CLK_DIV161   = LL_RCU_GPIO_DBC_CLK_DIV161,   /*!< GPIO Debounce Clock Divider 161   */
    HAL_RCU_GPIO_DBC_CLK_DIV162   = LL_RCU_GPIO_DBC_CLK_DIV162,   /*!< GPIO Debounce Clock Divider 162   */
    HAL_RCU_GPIO_DBC_CLK_DIV163   = LL_RCU_GPIO_DBC_CLK_DIV163,   /*!< GPIO Debounce Clock Divider 163   */
    HAL_RCU_GPIO_DBC_CLK_DIV164   = LL_RCU_GPIO_DBC_CLK_DIV164,   /*!< GPIO Debounce Clock Divider 164   */
    HAL_RCU_GPIO_DBC_CLK_DIV165   = LL_RCU_GPIO_DBC_CLK_DIV165,   /*!< GPIO Debounce Clock Divider 165   */
    HAL_RCU_GPIO_DBC_CLK_DIV166   = LL_RCU_GPIO_DBC_CLK_DIV166,   /*!< GPIO Debounce Clock Divider 166   */
    HAL_RCU_GPIO_DBC_CLK_DIV167   = LL_RCU_GPIO_DBC_CLK_DIV167,   /*!< GPIO Debounce Clock Divider 167   */
    HAL_RCU_GPIO_DBC_CLK_DIV168   = LL_RCU_GPIO_DBC_CLK_DIV168,   /*!< GPIO Debounce Clock Divider 168   */
    HAL_RCU_GPIO_DBC_CLK_DIV169   = LL_RCU_GPIO_DBC_CLK_DIV169,   /*!< GPIO Debounce Clock Divider 169   */
    HAL_RCU_GPIO_DBC_CLK_DIV170   = LL_RCU_GPIO_DBC_CLK_DIV170,   /*!< GPIO Debounce Clock Divider 170   */
    HAL_RCU_GPIO_DBC_CLK_DIV171   = LL_RCU_GPIO_DBC_CLK_DIV171,   /*!< GPIO Debounce Clock Divider 171   */
    HAL_RCU_GPIO_DBC_CLK_DIV172   = LL_RCU_GPIO_DBC_CLK_DIV172,   /*!< GPIO Debounce Clock Divider 172   */
    HAL_RCU_GPIO_DBC_CLK_DIV173   = LL_RCU_GPIO_DBC_CLK_DIV173,   /*!< GPIO Debounce Clock Divider 173   */
    HAL_RCU_GPIO_DBC_CLK_DIV174   = LL_RCU_GPIO_DBC_CLK_DIV174,   /*!< GPIO Debounce Clock Divider 174   */
    HAL_RCU_GPIO_DBC_CLK_DIV175   = LL_RCU_GPIO_DBC_CLK_DIV175,   /*!< GPIO Debounce Clock Divider 175   */
    HAL_RCU_GPIO_DBC_CLK_DIV176   = LL_RCU_GPIO_DBC_CLK_DIV176,   /*!< GPIO Debounce Clock Divider 176   */
    HAL_RCU_GPIO_DBC_CLK_DIV177   = LL_RCU_GPIO_DBC_CLK_DIV177,   /*!< GPIO Debounce Clock Divider 177   */
    HAL_RCU_GPIO_DBC_CLK_DIV178   = LL_RCU_GPIO_DBC_CLK_DIV178,   /*!< GPIO Debounce Clock Divider 178   */
    HAL_RCU_GPIO_DBC_CLK_DIV179   = LL_RCU_GPIO_DBC_CLK_DIV179,   /*!< GPIO Debounce Clock Divider 179   */
    HAL_RCU_GPIO_DBC_CLK_DIV180   = LL_RCU_GPIO_DBC_CLK_DIV180,   /*!< GPIO Debounce Clock Divider 180   */
    HAL_RCU_GPIO_DBC_CLK_DIV181   = LL_RCU_GPIO_DBC_CLK_DIV181,   /*!< GPIO Debounce Clock Divider 181   */
    HAL_RCU_GPIO_DBC_CLK_DIV182   = LL_RCU_GPIO_DBC_CLK_DIV182,   /*!< GPIO Debounce Clock Divider 182   */
    HAL_RCU_GPIO_DBC_CLK_DIV183   = LL_RCU_GPIO_DBC_CLK_DIV183,   /*!< GPIO Debounce Clock Divider 183   */
    HAL_RCU_GPIO_DBC_CLK_DIV184   = LL_RCU_GPIO_DBC_CLK_DIV184,   /*!< GPIO Debounce Clock Divider 184   */
    HAL_RCU_GPIO_DBC_CLK_DIV185   = LL_RCU_GPIO_DBC_CLK_DIV185,   /*!< GPIO Debounce Clock Divider 185   */
    HAL_RCU_GPIO_DBC_CLK_DIV186   = LL_RCU_GPIO_DBC_CLK_DIV186,   /*!< GPIO Debounce Clock Divider 186   */
    HAL_RCU_GPIO_DBC_CLK_DIV187   = LL_RCU_GPIO_DBC_CLK_DIV187,   /*!< GPIO Debounce Clock Divider 187   */
    HAL_RCU_GPIO_DBC_CLK_DIV188   = LL_RCU_GPIO_DBC_CLK_DIV188,   /*!< GPIO Debounce Clock Divider 188   */
    HAL_RCU_GPIO_DBC_CLK_DIV189   = LL_RCU_GPIO_DBC_CLK_DIV189,   /*!< GPIO Debounce Clock Divider 189   */
    HAL_RCU_GPIO_DBC_CLK_DIV190   = LL_RCU_GPIO_DBC_CLK_DIV190,   /*!< GPIO Debounce Clock Divider 190   */
    HAL_RCU_GPIO_DBC_CLK_DIV191   = LL_RCU_GPIO_DBC_CLK_DIV191,   /*!< GPIO Debounce Clock Divider 191   */
    HAL_RCU_GPIO_DBC_CLK_DIV192   = LL_RCU_GPIO_DBC_CLK_DIV192,   /*!< GPIO Debounce Clock Divider 192   */
    HAL_RCU_GPIO_DBC_CLK_DIV193   = LL_RCU_GPIO_DBC_CLK_DIV193,   /*!< GPIO Debounce Clock Divider 193   */
    HAL_RCU_GPIO_DBC_CLK_DIV194   = LL_RCU_GPIO_DBC_CLK_DIV194,   /*!< GPIO Debounce Clock Divider 194   */
    HAL_RCU_GPIO_DBC_CLK_DIV195   = LL_RCU_GPIO_DBC_CLK_DIV195,   /*!< GPIO Debounce Clock Divider 195   */
    HAL_RCU_GPIO_DBC_CLK_DIV196   = LL_RCU_GPIO_DBC_CLK_DIV196,   /*!< GPIO Debounce Clock Divider 196   */
    HAL_RCU_GPIO_DBC_CLK_DIV197   = LL_RCU_GPIO_DBC_CLK_DIV197,   /*!< GPIO Debounce Clock Divider 197   */
    HAL_RCU_GPIO_DBC_CLK_DIV198   = LL_RCU_GPIO_DBC_CLK_DIV198,   /*!< GPIO Debounce Clock Divider 198   */
    HAL_RCU_GPIO_DBC_CLK_DIV199   = LL_RCU_GPIO_DBC_CLK_DIV199,   /*!< GPIO Debounce Clock Divider 199   */
    HAL_RCU_GPIO_DBC_CLK_DIV200   = LL_RCU_GPIO_DBC_CLK_DIV200,   /*!< GPIO Debounce Clock Divider 200   */
    HAL_RCU_GPIO_DBC_CLK_DIV201   = LL_RCU_GPIO_DBC_CLK_DIV201,   /*!< GPIO Debounce Clock Divider 201   */
    HAL_RCU_GPIO_DBC_CLK_DIV202   = LL_RCU_GPIO_DBC_CLK_DIV202,   /*!< GPIO Debounce Clock Divider 202   */
    HAL_RCU_GPIO_DBC_CLK_DIV203   = LL_RCU_GPIO_DBC_CLK_DIV203,   /*!< GPIO Debounce Clock Divider 203   */
    HAL_RCU_GPIO_DBC_CLK_DIV204   = LL_RCU_GPIO_DBC_CLK_DIV204,   /*!< GPIO Debounce Clock Divider 204   */
    HAL_RCU_GPIO_DBC_CLK_DIV205   = LL_RCU_GPIO_DBC_CLK_DIV205,   /*!< GPIO Debounce Clock Divider 205   */
    HAL_RCU_GPIO_DBC_CLK_DIV206   = LL_RCU_GPIO_DBC_CLK_DIV206,   /*!< GPIO Debounce Clock Divider 206   */
    HAL_RCU_GPIO_DBC_CLK_DIV207   = LL_RCU_GPIO_DBC_CLK_DIV207,   /*!< GPIO Debounce Clock Divider 207   */
    HAL_RCU_GPIO_DBC_CLK_DIV208   = LL_RCU_GPIO_DBC_CLK_DIV208,   /*!< GPIO Debounce Clock Divider 208   */
    HAL_RCU_GPIO_DBC_CLK_DIV209   = LL_RCU_GPIO_DBC_CLK_DIV209,   /*!< GPIO Debounce Clock Divider 209   */
    HAL_RCU_GPIO_DBC_CLK_DIV210   = LL_RCU_GPIO_DBC_CLK_DIV210,   /*!< GPIO Debounce Clock Divider 210   */
    HAL_RCU_GPIO_DBC_CLK_DIV211   = LL_RCU_GPIO_DBC_CLK_DIV211,   /*!< GPIO Debounce Clock Divider 211   */
    HAL_RCU_GPIO_DBC_CLK_DIV212   = LL_RCU_GPIO_DBC_CLK_DIV212,   /*!< GPIO Debounce Clock Divider 212   */
    HAL_RCU_GPIO_DBC_CLK_DIV213   = LL_RCU_GPIO_DBC_CLK_DIV213,   /*!< GPIO Debounce Clock Divider 213   */
    HAL_RCU_GPIO_DBC_CLK_DIV214   = LL_RCU_GPIO_DBC_CLK_DIV214,   /*!< GPIO Debounce Clock Divider 214   */
    HAL_RCU_GPIO_DBC_CLK_DIV215   = LL_RCU_GPIO_DBC_CLK_DIV215,   /*!< GPIO Debounce Clock Divider 215   */
    HAL_RCU_GPIO_DBC_CLK_DIV216   = LL_RCU_GPIO_DBC_CLK_DIV216,   /*!< GPIO Debounce Clock Divider 216   */
    HAL_RCU_GPIO_DBC_CLK_DIV217   = LL_RCU_GPIO_DBC_CLK_DIV217,   /*!< GPIO Debounce Clock Divider 217   */
    HAL_RCU_GPIO_DBC_CLK_DIV218   = LL_RCU_GPIO_DBC_CLK_DIV218,   /*!< GPIO Debounce Clock Divider 218   */
    HAL_RCU_GPIO_DBC_CLK_DIV219   = LL_RCU_GPIO_DBC_CLK_DIV219,   /*!< GPIO Debounce Clock Divider 219   */
    HAL_RCU_GPIO_DBC_CLK_DIV220   = LL_RCU_GPIO_DBC_CLK_DIV220,   /*!< GPIO Debounce Clock Divider 220   */
    HAL_RCU_GPIO_DBC_CLK_DIV221   = LL_RCU_GPIO_DBC_CLK_DIV221,   /*!< GPIO Debounce Clock Divider 221   */
    HAL_RCU_GPIO_DBC_CLK_DIV222   = LL_RCU_GPIO_DBC_CLK_DIV222,   /*!< GPIO Debounce Clock Divider 222   */
    HAL_RCU_GPIO_DBC_CLK_DIV223   = LL_RCU_GPIO_DBC_CLK_DIV223,   /*!< GPIO Debounce Clock Divider 223   */
    HAL_RCU_GPIO_DBC_CLK_DIV224   = LL_RCU_GPIO_DBC_CLK_DIV224,   /*!< GPIO Debounce Clock Divider 224   */
    HAL_RCU_GPIO_DBC_CLK_DIV225   = LL_RCU_GPIO_DBC_CLK_DIV225,   /*!< GPIO Debounce Clock Divider 225   */
    HAL_RCU_GPIO_DBC_CLK_DIV226   = LL_RCU_GPIO_DBC_CLK_DIV226,   /*!< GPIO Debounce Clock Divider 226   */
    HAL_RCU_GPIO_DBC_CLK_DIV227   = LL_RCU_GPIO_DBC_CLK_DIV227,   /*!< GPIO Debounce Clock Divider 227   */
    HAL_RCU_GPIO_DBC_CLK_DIV228   = LL_RCU_GPIO_DBC_CLK_DIV228,   /*!< GPIO Debounce Clock Divider 228   */
    HAL_RCU_GPIO_DBC_CLK_DIV229   = LL_RCU_GPIO_DBC_CLK_DIV229,   /*!< GPIO Debounce Clock Divider 229   */
    HAL_RCU_GPIO_DBC_CLK_DIV230   = LL_RCU_GPIO_DBC_CLK_DIV230,   /*!< GPIO Debounce Clock Divider 230   */
    HAL_RCU_GPIO_DBC_CLK_DIV231   = LL_RCU_GPIO_DBC_CLK_DIV231,   /*!< GPIO Debounce Clock Divider 231   */
    HAL_RCU_GPIO_DBC_CLK_DIV232   = LL_RCU_GPIO_DBC_CLK_DIV232,   /*!< GPIO Debounce Clock Divider 232   */
    HAL_RCU_GPIO_DBC_CLK_DIV233   = LL_RCU_GPIO_DBC_CLK_DIV233,   /*!< GPIO Debounce Clock Divider 233   */
    HAL_RCU_GPIO_DBC_CLK_DIV234   = LL_RCU_GPIO_DBC_CLK_DIV234,   /*!< GPIO Debounce Clock Divider 234   */
    HAL_RCU_GPIO_DBC_CLK_DIV235   = LL_RCU_GPIO_DBC_CLK_DIV235,   /*!< GPIO Debounce Clock Divider 235   */
    HAL_RCU_GPIO_DBC_CLK_DIV236   = LL_RCU_GPIO_DBC_CLK_DIV236,   /*!< GPIO Debounce Clock Divider 236   */
    HAL_RCU_GPIO_DBC_CLK_DIV237   = LL_RCU_GPIO_DBC_CLK_DIV237,   /*!< GPIO Debounce Clock Divider 237   */
    HAL_RCU_GPIO_DBC_CLK_DIV238   = LL_RCU_GPIO_DBC_CLK_DIV238,   /*!< GPIO Debounce Clock Divider 238   */
    HAL_RCU_GPIO_DBC_CLK_DIV239   = LL_RCU_GPIO_DBC_CLK_DIV239,   /*!< GPIO Debounce Clock Divider 239   */
    HAL_RCU_GPIO_DBC_CLK_DIV240   = LL_RCU_GPIO_DBC_CLK_DIV240,   /*!< GPIO Debounce Clock Divider 240   */
    HAL_RCU_GPIO_DBC_CLK_DIV241   = LL_RCU_GPIO_DBC_CLK_DIV241,   /*!< GPIO Debounce Clock Divider 241   */
    HAL_RCU_GPIO_DBC_CLK_DIV242   = LL_RCU_GPIO_DBC_CLK_DIV242,   /*!< GPIO Debounce Clock Divider 242   */
    HAL_RCU_GPIO_DBC_CLK_DIV243   = LL_RCU_GPIO_DBC_CLK_DIV243,   /*!< GPIO Debounce Clock Divider 243   */
    HAL_RCU_GPIO_DBC_CLK_DIV244   = LL_RCU_GPIO_DBC_CLK_DIV244,   /*!< GPIO Debounce Clock Divider 244   */
    HAL_RCU_GPIO_DBC_CLK_DIV245   = LL_RCU_GPIO_DBC_CLK_DIV245,   /*!< GPIO Debounce Clock Divider 245   */
    HAL_RCU_GPIO_DBC_CLK_DIV246   = LL_RCU_GPIO_DBC_CLK_DIV246,   /*!< GPIO Debounce Clock Divider 246   */
    HAL_RCU_GPIO_DBC_CLK_DIV247   = LL_RCU_GPIO_DBC_CLK_DIV247,   /*!< GPIO Debounce Clock Divider 247   */
    HAL_RCU_GPIO_DBC_CLK_DIV248   = LL_RCU_GPIO_DBC_CLK_DIV248,   /*!< GPIO Debounce Clock Divider 248   */
    HAL_RCU_GPIO_DBC_CLK_DIV249   = LL_RCU_GPIO_DBC_CLK_DIV249,   /*!< GPIO Debounce Clock Divider 249   */
    HAL_RCU_GPIO_DBC_CLK_DIV250   = LL_RCU_GPIO_DBC_CLK_DIV250,   /*!< GPIO Debounce Clock Divider 250   */
    HAL_RCU_GPIO_DBC_CLK_DIV251   = LL_RCU_GPIO_DBC_CLK_DIV251,   /*!< GPIO Debounce Clock Divider 251   */
    HAL_RCU_GPIO_DBC_CLK_DIV252   = LL_RCU_GPIO_DBC_CLK_DIV252,   /*!< GPIO Debounce Clock Divider 252   */
    HAL_RCU_GPIO_DBC_CLK_DIV253   = LL_RCU_GPIO_DBC_CLK_DIV253,   /*!< GPIO Debounce Clock Divider 253   */
    HAL_RCU_GPIO_DBC_CLK_DIV254   = LL_RCU_GPIO_DBC_CLK_DIV254,   /*!< GPIO Debounce Clock Divider 254   */
    HAL_RCU_GPIO_DBC_CLK_DIV255   = LL_RCU_GPIO_DBC_CLK_DIV255,   /*!< GPIO Debounce Clock Divider 255   */
    HAL_RCU_GPIO_DBC_CLK_DIV256   = LL_RCU_GPIO_DBC_CLK_DIV256    /*!< GPIO Debounce Clock Divider 256   */
} HAL_RCU_GpioDbcClkDivTypeDef;

/**
  * @brief RCU HAL 
  */
typedef enum 
{
    HAL_RCU_DBC_CFG_GPIOA = 0U,   
    HAL_RCU_DBC_CFG_GPIOB = 1U,
    HAL_RCU_DBC_CFG_GPIOC = 2U,    
    HAL_RCU_DBC_CFG_GPIOD = 3U,    
    HAL_RCU_DBC_CFG_GPIOE = 4U,    
    HAL_RCU_DBC_CFG_GPIOF = 5U
} HAL_RCU_DbcCfgIdxTypeDef;

/**
  * @brief RCU HAL Function Enable/Disable
  */
typedef enum 
{
    HAL_RCU_FUNC_DISABLE = 0U,    /*!< Function disabled */
    HAL_RCU_FUNC_ENABLE  = 1U     /*!< Function enabled  */
} HAL_RCU_EnableTypeDef;

/**
  * @brief RCU ADC Function Clock Source Definition 
  */
typedef enum
{
    HAL_RCU_ADCCLK_SRC_SYSCLK = LL_RCU_FUNC_CLK_SRC_SYSCLK,  /*!< SYSCLK as ADC clock */
    HAL_RCU_ADCCLK_SRC_PLLCLK = LL_RCU_FUNC_CLK_SRC_PLL0     /*!< PLLCLK as ADC clock */
} HAL_RCU_ADCCLKSourceTypeDef;

/**
  * @brief RCU USB Function Clock Source Definition 
  */
typedef enum
{
    HAL_RCU_USBCLK_SRC_SYSCLK = LL_RCU_FUNC_CLK_SRC_SYSCLK,  /*!< SYSCLK as USB clock */
    HAL_RCU_USBCLK_SRC_PLLCLK = LL_RCU_FUNC_CLK_SRC_PLL0     /*!< PLLCLK as USB clock */
} HAL_RCU_USBCLKSourceTypeDef;

/**
  * @brief RCU CAN Function Clock Source Definition 
  */
typedef enum
{
    HAL_RCU_CANCLK_SRC_SYSCLK = LL_RCU_FUNC_CLK_SRC_SYSCLK,  /*!< SYSCLK as CAN clock */
    HAL_RCU_CANCLK_SRC_PLLCLK = LL_RCU_FUNC_CLK_SRC_PLL0     /*!< PLLCLK as CAN clock */
} HAL_RCU_CANCLKSourceTypeDef;

/**
  * @brief RCU CAN Function Clock Source Definition 
  */
typedef enum
{
    HAL_RCU_LPTMRCLK_SRC_HSI     = LL_RCU_FUNC_CLK_SRC_EX_HSI,      /*!< HSI as LPTMR clock */
    HAL_RCU_LPTMRCLK_SRC_APB0CLK = LL_RCU_FUNC_CLK_SRC_EX_APB0CLK,  /*!< APB0CLK as LPTMR clock */
    HAL_RCU_LPTMRCLK_SRC_HSE     = LL_RCU_FUNC_CLK_SRC_EX_HSE,      /*!< HSE as LPTMR clock */
    HAL_RCU_LPTMRCLK_SRC_LSI     = LL_RCU_FUNC_CLK_SRC_EX_LSI       /*!< LSI as LPTMR clock */
} HAL_RCU_LPTMRCLKSourceTypeDef;

/** @defgroup HAL_RCU_EC_Periph_Function_Clock RCU HAL Peripheral Function Clock Domain
  * @brief    Clock domains with an individual source/divider (RCU_PCSR / RCU_PCDR2)
  * @{
  */
typedef enum
{
    HAL_RCU_PERIPHCLK_ADC   = 1UL,  /*!< ADC clock domain   */
    HAL_RCU_PERIPHCLK_CAN   = 2UL,  /*!< CAN clock domain   */
    HAL_RCU_PERIPHCLK_USB   = 3UL,  /*!< USB clock domain   */
    HAL_RCU_PERIPHCLK_LPTMR = 4UL   /*!< LPTMR clock domain */
} HAL_RCU_PeriphClkTypeDef;

/**
  * @}
  */ /* HAL_RCU_EC_Periph_Function_Clock */

/** @defgroup HAL_RCU_EC_CSS_Config RCU HAL Clock Security System Config
  * @brief    Clock security system (XOSC/HSE monitor) window config 
  * @{
  */

/** 
  * @brief RCU HAL CSS Limit Window
  */
typedef enum
{
    HAL_RCU_CSS_LIMIT_WINDOW_2CYCLE = LL_RCU_XOSC_LIMIT_WINDOW_2CYCLE,  /*!< Compare threshold +-2 Cycle */
    HAL_RCU_CSS_LIMIT_WINDOW_4CYCLE = LL_RCU_XOSC_LIMIT_WINDOW_4CYCLE,  /*!< Compare threshold +-4 Cycle */
    HAL_RCU_CSS_LIMIT_WINDOW_6CYCLE = LL_RCU_XOSC_LIMIT_WINDOW_6CYCLE,  /*!< Compare threshold +-6 Cycle */
    HAL_RCU_CSS_LIMIT_WINDOW_8CYCLE = LL_RCU_XOSC_LIMIT_WINDOW_8CYCLE   /*!< Compare threshold +-8 Cycle */
} HAL_RCU_CSSLimitWindowTypeDef;

/** 
  * @brief RCU HAL CSS Switch Window
  */
typedef enum
{
    HAL_RCU_CSS_SWITCH_WINDOW_3US  = LL_RCU_XOSC_SWITCH_WINDOW_3US,   /*!< Auto switch window 3us  */
    HAL_RCU_CSS_SWITCH_WINDOW_6US  = LL_RCU_XOSC_SWITCH_WINDOW_6US,   /*!< Auto switch window 6us  */
    HAL_RCU_CSS_SWITCH_WINDOW_9US  = LL_RCU_XOSC_SWITCH_WINDOW_9US,   /*!< Auto switch window 9us  */
    HAL_RCU_CSS_SWITCH_WINDOW_12US = LL_RCU_XOSC_SWITCH_WINDOW_12US   /*!< Auto switch window 12us */
} HAL_RCU_CSSSwitchWindowTypeDef;
/**
  * @}
  */ /* HAL_RCU_EC_CSS_Config */

/**
  * @brief RCU SYSCLK Source Definition
  */
typedef enum {
    HAL_RCU_SYSCLK_SRC_RC8M        = LL_RCU_SYSCLK_SRC_RC8M,       /*!< RC8M (HSI) as system clock   */
    HAL_RCU_SYSCLK_SRC_RC32K       = LL_RCU_SYSCLK_SRC_RC32K,      /*!< RC32K as system clock        */
    HAL_RCU_SYSCLK_SRC_PLL0DivClk  = LL_RCU_SYSCLK_SRC_PLL0DivClk, /*!< PLL0 divided clock as sysclk */
    HAL_RCU_SYSCLK_SRC_XOSC        = LL_RCU_SYSCLK_SRC_XOSC,       /*!< XOSC (HSE) as system clock   */
} HAL_RCU_SYSCLKSourceTypeDef;

/**
  * @brief RCU PLL Clock Source Definition 
  */
typedef enum {
    HAL_RCU_PLLCLK_SRC_HSE    = LL_RCU_PLLCLK_SRC_HSE,      /*!< HSE as PLL clock source  */
    HAL_RCU_PLLCLK_SRC_HSI    = LL_RCU_PLLCLK_SRC_HSI,      /*!< HSI as PLL clock source  */
    HAL_RCU_PLLCLK_SRC_CLOSE  = LL_RCU_PLLCLK_SRC_CLOSE,    /*!< PLL clock close          */
} HAL_RCU_PLLSourceTypeDef;

/**
  * @brief RCU Internal Clock Fanout Source
  */
typedef enum
{
    HAL_RCU_MCO_SRC_LSI       = LL_RCU_INT_CLK_FANOUT_SRC_LSI,          /*!< LSI Clock as FANOUT source         */
    HAL_RCU_MCO_SRC_HSI       = LL_RCU_INT_CLK_FANOUT_SRC_HSI,          /*!< HSI Clock as FANOUT source         */
    HAL_RCU_MCO_SRC_HSE       = LL_RCU_INT_CLK_FANOUT_SRC_HSE,          /*!< HSE Clock as FANOUT source         */
    HAL_RCU_MCO_SRC_FCLK      = LL_RCU_INT_CLK_FANOUT_SRC_FCLK,         /*!< FCLK Clock as FANOUT source        */
    HAL_RCU_MCO_SRC_PLL_DIV32 = LL_RCU_INT_CLK_FANOUT_SRC_PLL_DIV32,    /*!< PLL0Div32 Clock as FANOUT source   */
} HAL_RCU_MCOSourceTypeDef;

/**
  * @defgroup RCU_Config_Structures RCU Configuration Structures
  * @{
  */

/**
  * @brief RCU SYSCLK Config Definition
  */
typedef struct {
    HAL_RCU_SYSCLKSourceTypeDef   SYSCLKSource;         /*!< SYSCLK Clock Source      */
    HAL_RCU_PLLSourceTypeDef      PLL0Source;           /*!< PLLCLK Clock Source      */
    uint32_t                      SYSCLKFrequency;      /*!< SYSCLK Frequency         */
    uint32_t                      PLL0SourceFrequency;  /*!< PLLCLK Source Frequency  */
    HAL_RCU_APB0ClkDivTypeDef     APB0CLKDivider;       /*!< APB0 clock Divider       */
    HAL_RCU_APB1ClkDivTypeDef     APB1CLKDivider;       /*!< APB1 clock Divider       */
    HAL_RCU_AHBClkDivTypeDef      AHBCLKDivider;        /*!< AHB0&1 clock Divider     */
} HAL_RCU_SYSCLKUserCfgTypeDef;

/**
  * @brief RCU PLL Config Definition
  */
typedef struct {
    HAL_RCU_PLLSourceTypeDef      PLLSource;            /*!< PLLCLK Source            */
    uint32_t                      PLLInFrequency;       /*!< PLLCLK Input Frequency   */
    uint32_t                      PLLUserFrequency;     /*!< PLLCLK User Frequency    */
} HAL_RCU_PLLUserCfgTypeDef;

/**
  * @brief RCU Oscillator Init Structure Definition
  */
typedef struct {
    HAL_RCU_OscillatorMskTypeDef  OscillatorType;       /*!< Oscillator Type Selection            */
    HAL_RCU_HSEStateTypeDef       HSEState;             /*!< HSE State                            */
    HAL_RCU_HSIStateTypeDef       HSIState;             /*!< HSI State                            */
    HAL_RCU_PLLStateTypeDef       PLLState;             /*!< PLL State                            */
    HAL_RCU_PLLSourceTypeDef      PLLSource;            /*!< PLL Source                           */
    uint16_t                      PLLFraction;          /*!< PLL Multiplication Factor (Fraction) */
    uint16_t                      PLLInteger;           /*!< PLL Multiplication Factor (Integer)  */
    HAL_RCU_PllBandTypeDef        PLLBand;              /*!< PLL VCO Band                         */
} HAL_RCU_OscInitTypeDef;

/**
  * @brief RCU Clock Init Structure Definition
  */
typedef struct {
    HAL_RCU_ClockMskTypeDef       ClockType;            /*!< Clock Type Selection     */
    HAL_RCU_SYSCLKSourceTypeDef   SYSCLKSource;         /*!< SYSCLK Source Selection  */
    HAL_RCU_AHBClkDivTypeDef      AHBCLKDivider;        /*!< AHB Clock Divider        */
    HAL_RCU_APB0ClkDivTypeDef     APB0CLKDivider;       /*!< APB0 Clock Divider       */
    HAL_RCU_APB1ClkDivTypeDef     APB1CLKDivider;       /*!< APB1 Clock Divider       */
} HAL_RCU_ClkInitTypeDef;

/**
  * @brief RCU Clocks Structure Definition
  */
typedef struct {
    uint32_t SYSCLKFrequency;         /*!< SYSCLK Frequency */
    uint32_t HCLKFrequency;           /*!< HCLK Frequency */
    uint32_t PCLK0Frequency;          /*!< PCLK0 Frequency */
    uint32_t PCLK1Frequency;          /*!< PCLK1 Frequency */
} HAL_RCU_ClocksTypeDef;

/**
  * @}
  */ /* RCU_Config_Structures */

/**
  * @}
  */ /* RCU_HAL_Exported_Types */


/* Exported Functions --------------------------------------------------------*/
/** @defgroup RCU_HAL_Exported_Functions RCU HAL Exported Functions
  * @brief    RCU HAL Exported Functions
  * @brief    RCU Exported Functions
  * @{
  */

/** @defgroup RCU_HAL_EF_Init RCU HAL Initialization and Configuration Functions
  * @brief    Initialization and Configuration Functions
  * @{
  */


HAL_StatusTypeDef HAL_RCU_OscConfig(HAL_RCU_OscInitTypeDef *pOscInit);
HAL_StatusTypeDef HAL_RCU_ClockConfig(HAL_RCU_ClkInitTypeDef *pClkInit);

HAL_StatusTypeDef HAL_RCU_SYSCLKInit(HAL_RCU_SYSCLKUserCfgTypeDef *pSYSCLKCfg);
HAL_StatusTypeDef HAL_RCU_PLL0Config(HAL_RCU_PLLUserCfgTypeDef *pPLL0Config);

HAL_StatusTypeDef HAL_RCU_MCOConfig(HAL_RCU_MCOSourceTypeDef Source);
HAL_StatusTypeDef HAL_RCU_GPIODebounceConfig(HAL_RCU_DbcCfgIdxTypeDef Index, 
                                             HAL_RCU_GpioDbcClkDivTypeDef ClockDivider);

void HAL_RCU_GetClockConfig(HAL_RCU_ClkInitTypeDef *pClkInit);
void HAL_RCU_GetOscConfig(HAL_RCU_OscInitTypeDef *pOscInit);

/**
  * @}
  */ /* RCU_HAL_EF_Init */


/** @defgroup RCU_HAL_EF_ClockFreq RCU HAL Clock Frequency Functions
  * @brief    Clock Frequency Functions
  * @{
  */


void HAL_RCU_GetClockFreq(HAL_RCU_ClocksTypeDef *pClocks);
uint32_t HAL_RCU_GetSysClockFreq(void);
uint32_t HAL_RCU_GetHCLKFreq(void);
uint32_t HAL_RCU_GetPCLK0Freq(void);
uint32_t HAL_RCU_GetPCLK1Freq(void);
uint32_t HAL_RCU_GetPeriphCLKFreq(HAL_RCU_PeriphClkTypeDef PeriphClock);
void HAL_RCU_UpdateSystemCoreClock(void);
/**
  * @}
  */ /* RCU_HAL_EF_ClockFreq */

/** @defgroup RCU_HAL_EF_Status RCU HAL Status and Flag Functions
  * @brief    Status and Flag Functions
  * @{
  */


uint32_t HAL_RCU_PLL0_IsReady(void);
uint32_t HAL_RCU_IsActiveFlag_CSS(void);
uint32_t HAL_RCU_GetResetSource(void);

HAL_StatusTypeDef HAL_RCU_ClearResetSource(uint32_t ResetSource);
HAL_StatusTypeDef HAL_RCU_EnableResetSource(uint32_t ResetSource);
HAL_StatusTypeDef HAL_RCU_DisableResetSource(uint32_t ResetSource);

/**
  * @}
  */ /* RCU_HAL_EF_Status */

/** @defgroup RCU_HAL_EF_CSS RCU HAL Clock Security System Functions
  * @brief    Clock Security System Functions (XOSC/HSE monitor, RCU_CSSCR, manual 7.2.6)
  * @{
  */

HAL_StatusTypeDef HAL_RCU_EnableCSS(void);
HAL_StatusTypeDef HAL_RCU_DisableCSS(void);

HAL_StatusTypeDef HAL_RCU_EnableCSS_IT(void);
HAL_StatusTypeDef HAL_RCU_DisableCSS_IT(void);

HAL_StatusTypeDef HAL_RCU_SetCSSLimitWindow(HAL_RCU_CSSLimitWindowTypeDef Lmt);
HAL_StatusTypeDef HAL_RCU_SetCSSAutoSwitchWindow(HAL_RCU_CSSSwitchWindowTypeDef Win);

HAL_RCU_CSSLimitWindowTypeDef HAL_RCU_GetCSSLimitWindow(void);
HAL_RCU_CSSSwitchWindowTypeDef HAL_RCU_GetCSSAutoSwitchWindow(void);

HAL_StatusTypeDef HAL_RCU_EnableSysClkSwitch(void);
HAL_StatusTypeDef HAL_RCU_DisableSysClkSwitch(void);

HAL_StatusTypeDef HAL_RCU_EnablePLL0AutoReload(void);
HAL_StatusTypeDef HAL_RCU_DisablePLL0AutoReload(void);

void HAL_RCU_NMI_IRQHandler(void);
void HAL_RCU_CSSCallback(void);

/**
  * @}
  */ /* RCU_HAL_EF_CSS */

/** @defgroup RCU_HAL_EF_PeriphClkConfig RCU HAL Peripheral Function Clock Config Functions
  * @brief    Peripheral Function Clock Config Functions (RCU_PCSR / RCU_PCDR2)
  * @{
  */

HAL_StatusTypeDef HAL_RCU_SetADCClockSource(HAL_RCU_ADCCLKSourceTypeDef Src);
HAL_RCU_ADCCLKSourceTypeDef HAL_RCU_GetADCClockSource(void);

HAL_StatusTypeDef HAL_RCU_SetADCClockDivider(HAL_RCU_FuncClkDivTypeDef Div);
HAL_RCU_FuncClkDivTypeDef HAL_RCU_GetADCClockDivider(void);

HAL_StatusTypeDef HAL_RCU_SetCANClockSource(HAL_RCU_CANCLKSourceTypeDef Src);
HAL_RCU_CANCLKSourceTypeDef HAL_RCU_GetCANClockSource(void);

HAL_StatusTypeDef HAL_RCU_SetCANClockDivider(HAL_RCU_FuncClkDivTypeDef Div);
HAL_RCU_FuncClkDivTypeDef HAL_RCU_GetCANClockDivider(void);

HAL_StatusTypeDef HAL_RCU_SetUSBClockSource(HAL_RCU_USBCLKSourceTypeDef Src);
HAL_RCU_USBCLKSourceTypeDef HAL_RCU_GetUSBClockSource(void);

HAL_StatusTypeDef HAL_RCU_SetUSBClockDivider(HAL_RCU_FuncClkDivTypeDef Div);
HAL_RCU_FuncClkDivTypeDef HAL_RCU_GetUSBClockDivider(void);

HAL_StatusTypeDef HAL_RCU_SetTMR6ClockSource(HAL_RCU_LPTMRCLKSourceTypeDef Src);
HAL_RCU_LPTMRCLKSourceTypeDef HAL_RCU_GetTMR6ClockSource(void);

/**
  * @}
  */ /* RCU_HAL_EF_PeriphClkConfig */

/**
  * @}
  */ /* RCU_HAL_Exported_Functions */

/* Exported Macros -----------------------------------------------------------*/
/** @addtogroup RCU_HAL_Exported_Macros
  * @{
  */

/** @defgroup RCU_HAL_EM_PeriphClkEx RCU HAL Fine-grained Peripheral Clock Control
  * @brief    Fine-grained Peripheral Clock Control
  * @{
  */
/**
 * @brief  Enable the ADC0 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableADC0Clock(RCU);                          \
    LL_RCU_PC_EnableADC0FunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the ADC0 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableADC0Clock(RCU);                         \
    LL_RCU_PC_DisableADC0FunClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the ADC1 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableADC1Clock(RCU);                          \
    LL_RCU_PC_EnableADC1FunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the ADC1 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableADC1Clock(RCU);                         \
    LL_RCU_PC_DisableADC1FunClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the ADC2 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC2_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableADC2Clock(RCU);                          \
    LL_RCU_PC_EnableADC2FunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the ADC2 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC2_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableADC2Clock(RCU);                         \
    LL_RCU_PC_DisableADC2FunClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the ADC3 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC3_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableADC3Clock(RCU);                          \
    LL_RCU_PC_EnableADC3FunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the ADC3 peripheral clock.
 * @return None
 */
#define HAL_RCU_ADC3_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableADC3Clock(RCU);                         \
    LL_RCU_PC_DisableADC3FunClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the reset of all ADC instances.
 * @note   Hardware provides a single reset bit (AHB1RSTR.ADCRST) for ADC0..ADC3
 *         (manual 7.3.2.17 p83).
 * @return None
 */
#define HAL_RCU_ADC_FORCE_RESET()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetADC(RCU);                            \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the reset of all ADC instances.
 * @return None
 */
#define HAL_RCU_ADC_RELEASE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetADC(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the CAN0 peripheral clock.
 * @return None
 */
#define HAL_RCU_CAN0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableCAN0Clock(RCU);                          \
    LL_RCU_PC_EnableCAN0FunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the CAN0 peripheral clock.
 * @return None
 */
#define HAL_RCU_CAN0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableCAN0Clock(RCU);                         \
    LL_RCU_PC_DisableCAN0FunClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the CAN0 peripheral reset.
 * @return None
 */
#define HAL_RCU_CAN0_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetCAN0(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the CAN0 peripheral reset.
 * @return None
 */
#define HAL_RCU_CAN0_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetCAN0(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the CAN1 peripheral clock.
 * @return None
 */
#define HAL_RCU_CAN1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableCAN1Clock(RCU);                          \
    LL_RCU_PC_EnableCAN1FunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the CAN1 peripheral clock.
 * @return None
 */
#define HAL_RCU_CAN1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableCAN1Clock(RCU);                         \
    LL_RCU_PC_DisableCAN1FunClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the CAN1 peripheral reset.
 * @return None
 */
#define HAL_RCU_CAN1_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetCAN1(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the CAN1 peripheral reset.
 * @return None
 */
#define HAL_RCU_CAN1_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetCAN1(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the CMP peripheral clock.
 * @return None
 */
#define HAL_RCU_CMP_CLK_ENABLE()                               \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableCMPClock(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the CMP peripheral clock.
 * @return None
 */
#define HAL_RCU_CMP_CLK_DISABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableCMPClock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the CMP peripheral reset.
 * @return None
 */
#define HAL_RCU_CMP_FORCE_RESET()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetCMP(RCU);                            \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the CMP peripheral reset.
 * @return None
 */
#define HAL_RCU_CMP_RELEASE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetCMP(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the CORDIC peripheral clock.
 * @return None
 */
#define HAL_RCU_CORDIC_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableCORDICClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the CORDIC peripheral clock.
 * @return None
 */
#define HAL_RCU_CORDIC_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableCORDICClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the CORDIC peripheral reset.
 * @return None
 */
#define HAL_RCU_CORDIC_FORCE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetCORDIC(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the CORDIC peripheral reset.
 * @return None
 */
#define HAL_RCU_CORDIC_RELEASE_RESET()                         \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetCORDIC(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the DAC peripheral clock.
 * @return None
 */
#define HAL_RCU_DAC_CLK_ENABLE()                               \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableDACClock(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the DAC peripheral clock.
 * @return None
 */
#define HAL_RCU_DAC_CLK_DISABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableDACClock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the DAC peripheral reset.
 * @return None
 */
#define HAL_RCU_DAC_FORCE_RESET()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetDAC(RCU);                            \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the DAC peripheral reset.
 * @return None
 */
#define HAL_RCU_DAC_RELEASE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetDAC(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the DMA peripheral clock.
 * @return None
 */
#define HAL_RCU_DMA_CLK_ENABLE()                               \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableDMAClock(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the DMA peripheral clock.
 * @return None
 */
#define HAL_RCU_DMA_CLK_DISABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableDMAClock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the DMA peripheral reset.
 * @return None
 */
#define HAL_RCU_DMA_FORCE_RESET()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetDMA(RCU);                            \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the DMA peripheral reset.
 * @return None
 */
#define HAL_RCU_DMA_RELEASE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetDMA(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the EFLASH peripheral clock.
 * @return None
 */
#define HAL_RCU_EFLASH_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableEFLASHClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the EFLASH peripheral clock.
 * @return None
 */
#define HAL_RCU_EFLASH_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableEFLASHClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the EFLASH peripheral reset.
 * @return None
 */
#define HAL_RCU_EFLASH_FORCE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetEFLASH(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the EFLASH peripheral reset.
 * @return None
 */
#define HAL_RCU_EFLASH_RELEASE_RESET()                         \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetEFLASH(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the GPIOA peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOA_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableGPIOAClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the GPIOA peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOA_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableGPIOAClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the GPIOA peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOA_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetGPIOA(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the GPIOA peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOA_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetGPIOA(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the GPIOB peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOB_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableGPIOBClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the GPIOB peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOB_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableGPIOBClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the GPIOB peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOB_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetGPIOB(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the GPIOB peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOB_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetGPIOB(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the GPIOC peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOC_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableGPIOCClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the GPIOC peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOC_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableGPIOCClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the GPIOC peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOC_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetGPIOC(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the GPIOC peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOC_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetGPIOC(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the GPIOD peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOD_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableGPIODClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the GPIOD peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOD_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableGPIODClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the GPIOD peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOD_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetGPIOD(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the GPIOD peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOD_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetGPIOD(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the GPIOE peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOE_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableGPIOEClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the GPIOE peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOE_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableGPIOEClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the GPIOE peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOE_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetGPIOE(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the GPIOE peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOE_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetGPIOE(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the GPIOF peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOF_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableGPIOFClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the GPIOF peripheral clock.
 * @return None
 */
#define HAL_RCU_GPIOF_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableGPIOFClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the GPIOF peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOF_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetGPIOF(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the GPIOF peripheral reset.
 * @return None
 */
#define HAL_RCU_GPIOF_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetGPIOF(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the clock of all HRPWM instances.
 * @return None
 */
#define HAL_RCU_HRPWM_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM0Clock(RCU);                        \
    LL_RCU_AHB1_EnableHRPWM1Clock(RCU);                        \
    LL_RCU_AHB1_EnableHRPWM2Clock(RCU);                        \
    LL_RCU_AHB1_EnableHRPWM3Clock(RCU);                        \
    LL_RCU_AHB1_EnableHRPWM4Clock(RCU);                        \
    LL_RCU_AHB1_EnableHRPWM5Clock(RCU);                        \
    LL_RCU_AHB1_EnableHRPWM6Clock(RCU);                        \
    LL_RCU_AHB1_EnableHRPWM7Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM0FunClock(RCU);                       \
    LL_RCU_PC_EnableHRPWM1FunClock(RCU);                       \
    LL_RCU_PC_EnableHRPWM2FunClock(RCU);                       \
    LL_RCU_PC_EnableHRPWM3FunClock(RCU);                       \
    LL_RCU_PC_EnableHRPWM4FunClock(RCU);                       \
    LL_RCU_PC_EnableHRPWM5FunClock(RCU);                       \
    LL_RCU_PC_EnableHRPWM6FunClock(RCU);                       \
    LL_RCU_PC_EnableHRPWM7FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the clock of all HRPWM instances.
 * @return None
 */
#define HAL_RCU_HRPWM_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM0Clock(RCU);                       \
    LL_RCU_AHB1_DisableHRPWM1Clock(RCU);                       \
    LL_RCU_AHB1_DisableHRPWM2Clock(RCU);                       \
    LL_RCU_AHB1_DisableHRPWM3Clock(RCU);                       \
    LL_RCU_AHB1_DisableHRPWM4Clock(RCU);                       \
    LL_RCU_AHB1_DisableHRPWM5Clock(RCU);                       \
    LL_RCU_AHB1_DisableHRPWM6Clock(RCU);                       \
    LL_RCU_AHB1_DisableHRPWM7Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM0FunClock(RCU);                      \
    LL_RCU_PC_DisableHRPWM1FunClock(RCU);                      \
    LL_RCU_PC_DisableHRPWM2FunClock(RCU);                      \
    LL_RCU_PC_DisableHRPWM3FunClock(RCU);                      \
    LL_RCU_PC_DisableHRPWM4FunClock(RCU);                      \
    LL_RCU_PC_DisableHRPWM5FunClock(RCU);                      \
    LL_RCU_PC_DisableHRPWM6FunClock(RCU);                      \
    LL_RCU_PC_DisableHRPWM7FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the reset of all HRPWM instances.
 * @return None
 */
#define HAL_RCU_HRPWM_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetHRPWM(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the reset of all HRPWM instances.
 * @return None
 */
#define HAL_RCU_HRPWM_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetHRPWM(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM0 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM0_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM0Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM0FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM0 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM0_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM0Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM0FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM1 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM1_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM1Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM1FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM1 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM1_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM1Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM1FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM2 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM2_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM2Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM2FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM2 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM2_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM2Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM2FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM3 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM3_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM3Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM3FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM3 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM3_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM3Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM3FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM4 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM4_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM4Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM4FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM4 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM4_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM4Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM4FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM5 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM5_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM5Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM5FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM5 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM5_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM5Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM5FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM6 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM6_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM6Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM6FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM6 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM6_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM6Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM6FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the HRPWM7 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM7_CLK_ENABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableHRPWM7Clock(RCU);                        \
    LL_RCU_PC_EnableHRPWM7FunClock(RCU);                       \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the HRPWM7 peripheral clock.
 * @return None
 */
#define HAL_RCU_HRPWM7_CLK_DISABLE()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableHRPWM7Clock(RCU);                       \
    LL_RCU_PC_DisableHRPWM7FunClock(RCU);                      \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the I2C0 peripheral clock.
 * @return None
 */
#define HAL_RCU_I2C0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableI2C0Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the I2C0 peripheral clock.
 * @return None
 */
#define HAL_RCU_I2C0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableI2C0Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the I2C0 peripheral reset.
 * @return None
 */
#define HAL_RCU_I2C0_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetI2C0(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the I2C0 peripheral reset.
 * @return None
 */
#define HAL_RCU_I2C0_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetI2C0(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the I2C1 peripheral clock.
 * @return None
 */
#define HAL_RCU_I2C1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableI2C1Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the I2C1 peripheral clock.
 * @return None
 */
#define HAL_RCU_I2C1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableI2C1Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the I2C1 peripheral reset.
 * @return None
 */
#define HAL_RCU_I2C1_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetI2C1(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the I2C1 peripheral reset.
 * @return None
 */
#define HAL_RCU_I2C1_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetI2C1(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the I2C2 peripheral clock.
 * @return None
 */
#define HAL_RCU_I2C2_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableI2C2Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the I2C2 peripheral clock.
 * @return None
 */
#define HAL_RCU_I2C2_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableI2C2Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the I2C2 peripheral reset.
 * @return None
 */
#define HAL_RCU_I2C2_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetI2C2(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the I2C2 peripheral reset.
 * @return None
 */
#define HAL_RCU_I2C2_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetI2C2(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the IIR0 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableIIR0Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the IIR0 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableIIR0Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the IIR0 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR0_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetIIR0(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the IIR0 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR0_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetIIR0(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the IIR1 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableIIR1Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the IIR1 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableIIR1Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the IIR1 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR1_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetIIR1(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the IIR1 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR1_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetIIR1(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the IIR2 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR2_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableIIR2Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the IIR2 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR2_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableIIR2Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the IIR2 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR2_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetIIR2(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the IIR2 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR2_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetIIR2(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the IIR3 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR3_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableIIR3Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the IIR3 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR3_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableIIR3Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the IIR3 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR3_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetIIR3(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the IIR3 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR3_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetIIR3(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the IIR4 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR4_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableIIR4Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the IIR4 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR4_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableIIR4Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the IIR4 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR4_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetIIR4(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the IIR4 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR4_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetIIR4(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the IIR5 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR5_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableIIR5Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the IIR5 peripheral clock.
 * @return None
 */
#define HAL_RCU_IIR5_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableIIR5Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the IIR5 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR5_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetIIR5(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the IIR5 peripheral reset.
 * @return None
 */
#define HAL_RCU_IIR5_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetIIR5(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the LPTMR peripheral clock.
 * @return None
 */
#define HAL_RCU_LPTMR_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableLPTMRClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the LPTMR peripheral clock.
 * @return None
 */
#define HAL_RCU_LPTMR_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableLPTMRClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the LPTMR peripheral reset.
 * @return None
 */
#define HAL_RCU_LPTMR_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetLPTMR(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the LPTMR peripheral reset.
 * @return None
 */
#define HAL_RCU_LPTMR_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetLPTMR(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the PDM0 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnablePDM0Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the PDM0 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisablePDM0Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the PDM0 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM0_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetPDM0(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the PDM0 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM0_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetPDM0(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the PDM1 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnablePDM1Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the PDM1 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisablePDM1Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the PDM1 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM1_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetPDM1(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the PDM1 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM1_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetPDM1(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the PDM2 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM2_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnablePDM2Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the PDM2 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM2_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisablePDM2Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the PDM2 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM2_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetPDM2(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the PDM2 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM2_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetPDM2(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the PDM3 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM3_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnablePDM3Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the PDM3 peripheral clock.
 * @return None
 */
#define HAL_RCU_PDM3_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisablePDM3Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the PDM3 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM3_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetPDM3(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the PDM3 peripheral reset.
 * @return None
 */
#define HAL_RCU_PDM3_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetPDM3(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the QEI0 peripheral clock.
 * @return None
 */
#define HAL_RCU_QEI0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableQEI0Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the QEI0 peripheral clock.
 * @return None
 */
#define HAL_RCU_QEI0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableQEI0Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the QEI0 peripheral reset.
 * @return None
 */
#define HAL_RCU_QEI0_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetQEI0(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the QEI0 peripheral reset.
 * @return None
 */
#define HAL_RCU_QEI0_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetQEI0(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the QEI1 peripheral clock.
 * @return None
 */
#define HAL_RCU_QEI1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableQEI1Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the QEI1 peripheral clock.
 * @return None
 */
#define HAL_RCU_QEI1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableQEI1Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the QEI1 peripheral reset.
 * @return None
 */
#define HAL_RCU_QEI1_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetQEI1(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the QEI1 peripheral reset.
 * @return None
 */
#define HAL_RCU_QEI1_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetQEI1(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the QEI2 peripheral clock.
 * @return None
 */
#define HAL_RCU_QEI2_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableQEI2Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the QEI2 peripheral clock.
 * @return None
 */
#define HAL_RCU_QEI2_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableQEI2Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the QEI2 peripheral reset.
 * @return None
 */
#define HAL_RCU_QEI2_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetQEI2(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the QEI2 peripheral reset.
 * @return None
 */
#define HAL_RCU_QEI2_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetQEI2(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the SPI0 peripheral clock.
 * @return None
 */
#define HAL_RCU_SPI0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableSPI0Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the SPI0 peripheral clock.
 * @return None
 */
#define HAL_RCU_SPI0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableSPI0Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the SPI0 peripheral reset.
 * @return None
 */
#define HAL_RCU_SPI0_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetSPI0(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the SPI0 peripheral reset.
 * @return None
 */
#define HAL_RCU_SPI0_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetSPI0(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the SPI1 peripheral clock.
 * @return None
 */
#define HAL_RCU_SPI1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableSPI1Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the SPI1 peripheral clock.
 * @return None
 */
#define HAL_RCU_SPI1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableSPI1Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the SPI1 peripheral reset.
 * @return None
 */
#define HAL_RCU_SPI1_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetSPI1(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the SPI1 peripheral reset.
 * @return None
 */
#define HAL_RCU_SPI1_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetSPI1(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR0 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR0_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableTMR0Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR0 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR0_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableTMR0Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR0 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR0_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetTMR0(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR0 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR0_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetTMR0(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR1 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR1_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableTMR1Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR1 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR1_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableTMR1Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR1 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR1_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetTMR1(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR1 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR1_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetTMR1(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR10 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR10_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableTMR10Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR10 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR10_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableTMR10Clock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR10 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR10_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetTMR10(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR10 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR10_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetTMR10(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR2 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR2_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableTMR2Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR2 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR2_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableTMR2Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR2 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR2_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetTMR2(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR2 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR2_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetTMR2(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR3 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR3_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableTMR3Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR3 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR3_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableTMR3Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR3 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR3_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetTMR3(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR3 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR3_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetTMR3(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR4 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR4_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_EnableTMR4Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR4 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR4_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_DisableTMR4Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR4 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR4_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ForceResetTMR4(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR4 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR4_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB0_ReleaseResetTMR4(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR6 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR6_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableLPTMRClock(RCU);                         \
    LL_RCU_PC_EnableTMR6FunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR6 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR6_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableLPTMRClock(RCU);                        \
    LL_RCU_PC_DisableTMR6FunClock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR6 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR6_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetLPTMR(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR6 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR6_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetLPTMR(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR7 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR7_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableTMR7Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR7 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR7_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableTMR7Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR7 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR7_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetTMR7(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR7 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR7_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetTMR7(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR8 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR8_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableTMR8Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR8 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR8_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableTMR8Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR8 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR8_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetTMR8(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR8 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR8_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetTMR8(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the TMR9 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR9_CLK_ENABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableTMR9Clock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the TMR9 peripheral clock.
 * @return None
 */
#define HAL_RCU_TMR9_CLK_DISABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableTMR9Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the TMR9 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR9_FORCE_RESET()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetTMR9(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the TMR9 peripheral reset.
 * @return None
 */
#define HAL_RCU_TMR9_RELEASE_RESET()                           \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetTMR9(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the UART0 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART0_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableUART0Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the UART0 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART0_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableUART0Clock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the UART0 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART0_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetUART0(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the UART0 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART0_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetUART0(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the UART1 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART1_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableUART1Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the UART1 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART1_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableUART1Clock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the UART1 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART1_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetUART1(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the UART1 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART1_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetUART1(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the UART2 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART2_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_EnableUART2Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the UART2 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART2_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_DisableUART2Clock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the UART2 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART2_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ForceResetUART2(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the UART2 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART2_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB0_ReleaseResetUART2(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the UART3 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART3_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableUART3Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the UART3 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART3_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableUART3Clock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the UART3 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART3_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetUART3(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the UART3 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART3_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetUART3(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the UART4 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART4_CLK_ENABLE()                             \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableUART4Clock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the UART4 peripheral clock.
 * @return None
 */
#define HAL_RCU_UART4_CLK_DISABLE()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableUART4Clock(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the UART4 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART4_FORCE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetUART4(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the UART4 peripheral reset.
 * @return None
 */
#define HAL_RCU_UART4_RELEASE_RESET()                          \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetUART4(RCU);                        \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the USB peripheral clock.
 * @return None
 */
#define HAL_RCU_USB_CLK_ENABLE()                               \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_EnableUSBClock(RCU);                           \
    LL_RCU_PC_EnableUSBFunClock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the USB peripheral clock.
 * @return None
 */
#define HAL_RCU_USB_CLK_DISABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_DisableUSBClock(RCU);                          \
    LL_RCU_PC_DisableUSBFunClock(RCU);                         \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the USB peripheral reset.
 * @return None
 */
#define HAL_RCU_USB_FORCE_RESET()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ForceResetUSB(RCU);                            \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the USB peripheral reset.
 * @return None
 */
#define HAL_RCU_USB_RELEASE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_AHB1_ReleaseResetUSB(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Enable the XIF peripheral clock.
 * @return None
 */
#define HAL_RCU_XIF_CLK_ENABLE()                               \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_EnableXIFClock(RCU);                           \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Disable the XIF peripheral clock.
 * @return None
 */
#define HAL_RCU_XIF_CLK_DISABLE()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_DisableXIFClock(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Assert the XIF peripheral reset.
 * @return None
 */
#define HAL_RCU_XIF_FORCE_RESET()                              \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ForceResetXIF(RCU);                            \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
 * @brief  Release the XIF peripheral reset.
 * @return None
 */
#define HAL_RCU_XIF_RELEASE_RESET()                            \
do {                                                           \
    LL_RCU_RegWrite_Unlock(RCU);                               \
    LL_RCU_APB1_ReleaseResetXIF(RCU);                          \
    LL_RCU_RegWrite_Lock(RCU);                                 \
} while (0)

/**
  * @}
  */ /* RCU_HAL_EM_PeriphClkEx */

/**
  * @}
  */ /* RCU_HAL_Exported_Macros */

/**
  * @}
  */ /* RCU_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_RCU_H_ */


/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/