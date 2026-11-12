/**
  ******************************************************************************
  * @file    tae32g58xx_ll_rcu.h
  * @author  Tai-Action SD Team
  * @brief   Header file for RCU LL module
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
#ifndef _TAE32G58XX_LL_RCU_H_
#define _TAE32G58XX_LL_RCU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

#if defined (RCU)

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup RCU_LL RCU LL
  * @brief    RCU LL Module Driver
  * @{
  */

/* Exported Macros -----------------------------------------------------------*/
/** @defgroup RCU_LL_Exported_Macros RCU LL Exported Macros
  * @brief    RCU LL Exported Macros
  * @{
  */

/**
  * @brief  RCU Register Write Operation
  * @param  EXPRESSION RCU Register Read/Write Operation
  * @note   Only Write Operation need Unlock before Operation
  * @return None
  */
#define LL_RCU_REG_WRITE_OPT(EXPRESSION)    \
        do {                                \
            LL_RCU_RegWrite_Unlock(RCU);    \
            EXPRESSION;                     \
            LL_RCU_RegWrite_Lock(RCU);      \
        } while(0)

/**
  * @}
  */ /* RCU_LL_Exported_Macros */

/* Exported Constants --------------------------------------------------------*/
/** @defgroup RCU_LL_Exported_Constants RCU LL Exported Constants
  * @brief    RCU LL Exported Constants
  * @{
  */

/** @defgroup RCU_LL_EC_Information LL RCU Information
  * @brief LL RCU Information
  * @{
  */

#define LL_RCU_PLL0CR_VCO_DET                 (BIT(17))

/**
* @brief LL RCU SRSR Reset Source Mask Definition
*/
#define LL_RCU_SRSR_RstSrcMskTypeDef                         uint32_t

#define LL_RCU_SRSR_WWR                      (RCU_SRSR_WWR_Msk)                   /*!< WWR Mask                 */
#define LL_RCU_SRSR_IWR                      (RCU_SRSR_IWR_Msk)                   /*!< IWR Mask                 */
#define LL_RCU_SRSR_LKR                      (RCU_SRSR_LKR_Msk)                   /*!< LKR Mask                 */
#define LL_RCU_SRSR_SQR                      (RCU_SRSR_SQR_Msk)                   /*!< SQR Mask                 */
#define LL_RCU_SRSR_LPR                      (RCU_SRSR_LPR_Msk)                   /*!< LPR Mask                 */
#define LL_RCU_SRSR_MCR                      (RCU_SRSR_MCR_Msk)                   /*!< MCR Mask                 */

#define LL_RCU_SRSR_RST_SRC_MSK                             ((RCU_SRSR_WWR_Msk                | RCU_SRSR_IWR_Msk                | \
                                                              RCU_SRSR_LKR_Msk                | RCU_SRSR_SQR_Msk                | \
                                                              RCU_SRSR_LPR_Msk                | RCU_SRSR_MCR_Msk                ))

#define LL_RCU_SRSR_RST_SRC_FLAG_MSK                        ((RCU_SRSR_WWR_Msk                | RCU_SRSR_IWR_Msk                | \
                                                              RCU_SRSR_LKR_Msk                | RCU_SRSR_SQR_Msk                | \
                                                              RCU_SRSR_LPR_Msk                | RCU_SRSR_MCR_Msk                ))

#define LL_RCU_SRSR_RST_SRC_EN_MSK                          ((RCU_SRSR_WWR_Msk                | RCU_SRSR_IWR_Msk                | \
                                                              RCU_SRSR_LKR_Msk                | RCU_SRSR_SQR_Msk                ))
/**
  * @}
  */ /* RCU_LL_EC_Information */


/** @defgroup RCU_LL_EC_HSE_Config LL RCU HSE Config
  * @{
  */
#define LL_RCU_HSEEnTypedef              uint32_t

#define LL_RCU_HSE_OFF                   0x00000000UL
#define LL_RCU_HSE_ON                    0x00000001UL
/**
  * @}
  */ /* RCU_LL_EC_HSE_Config */

/** @defgroup RCU_LL_EC_HSI_Config LL RCU HSI Config
  * @{
  */
#define LL_RCU_HSIEnTypedef              uint32_t

#define LL_RCU_HSI_OFF                   0x00000000UL
#define LL_RCU_HSI_ON                    0x00000001UL
/**
  * @}
  */ /* RCU_LL_EC_HSI_Config */

/** @defgroup RCU_LL_EC_PLL_Clock_Source LL RCU PLL Clock Source
  * @{
  */
#define LL_RCU_PllClkSrcTypeDef                   uint32_t

#define LL_RCU_PLLCLK_SRC_HSE                     0x00000000UL
#define LL_RCU_PLLCLK_SRC_HSI                     0x00000001UL
#define LL_RCU_PLLCLK_SRC_CLOSE                   0x00000002UL

#define IS_LL_RCU_PLLCLK_SRC(__VAL__)             (((__VAL__) == LL_RCU_PLLCLK_SRC_HSE) || \
                                                   ((__VAL__) == LL_RCU_PLLCLK_SRC_HSI) || \
                                                   ((__VAL__) == LL_RCU_PLLCLK_SRC_CLOSE))
/**
  * @}
  */ /* RCU_LL_EC_PLL_Clock_Source */




/** @defgroup RCU_LL_EC_System_Clock_Source LL RCU System Clock Source
  * @{
  */
#define LL_RCU_SysclkSrcTypeDef                   uint32_t

#define LL_RCU_SYSCLK_SRC_RC8M                    0x00000000UL
#define LL_RCU_SYSCLK_SRC_RC32K                   0x00000001UL
#define LL_RCU_SYSCLK_SRC_PLL0DivClk              0x00000002UL
#define LL_RCU_SYSCLK_SRC_XOSC                    0x00000003UL

#define IS_LL_RCU_SYSCLK_SRC(__VAL__)             (((__VAL__) == LL_RCU_SYSCLK_SRC_RC8M)       || \
                                                   ((__VAL__) == LL_RCU_SYSCLK_SRC_RC32K)      || \
                                                   ((__VAL__) == LL_RCU_SYSCLK_SRC_PLL0DivClk) || \
                                                   ((__VAL__) == LL_RCU_SYSCLK_SRC_XOSC))
/**
  * @}
  */ /* RCU_LL_EC_System_Clock_Source */

/** @defgroup RCU_LL_EC_LPTMR_Clock_Source LL RCU LPTMR (TMR6) Clock Source
  * @{
  */
#define LL_RCU_LPTMR_CLK_SRC_APB0CLK              0x00000000UL   /*!< APB0CLK as LPTMR clock source */
#define LL_RCU_LPTMR_CLK_SRC_HSI                  0x00000001UL   /*!< HSI as LPTMR clock source     */
#define LL_RCU_LPTMR_CLK_SRC_HSE                  0x00000002UL   /*!< HSE as LPTMR clock source     */
#define LL_RCU_LPTMR_CLK_SRC_LSI                  0x00000003UL   /*!< LSI as LPTMR clock source     */

#define IS_LL_RCU_LPTMR_CLK_SRC(__VAL__)          (((__VAL__) == LL_RCU_LPTMR_CLK_SRC_APB0CLK) || \
                                                   ((__VAL__) == LL_RCU_LPTMR_CLK_SRC_HSI)     || \
                                                   ((__VAL__) == LL_RCU_LPTMR_CLK_SRC_HSE)     || \
                                                   ((__VAL__) == LL_RCU_LPTMR_CLK_SRC_LSI))
/**
  * @}
  */ /* RCU_LL_EC_LPTMR_Clock_Source */


/** @defgroup RCU_LL_EC_AHB_Clock_Divider LL RCU AHB Clock Divider
  * @{
  */
#define LL_RCU_AHBClkDivTypeDef          LL_RSV_DATA_TYPE

#define LL_RCU_AHB_DIV1                  1UL
#define LL_RCU_AHB_DIV2                  2UL
#define LL_RCU_AHB_DIV3                  3UL
#define LL_RCU_AHB_DIV4                  4UL
#define LL_RCU_AHB_DIV5                  5UL
#define LL_RCU_AHB_DIV6                  6UL
#define LL_RCU_AHB_DIV7                  7UL
#define LL_RCU_AHB_DIV8                  8UL
#define LL_RCU_AHB_DIV9                  9UL
#define LL_RCU_AHB_DIV10                 10UL
#define LL_RCU_AHB_DIV11                 11UL
#define LL_RCU_AHB_DIV12                 12UL
#define LL_RCU_AHB_DIV13                 13UL
#define LL_RCU_AHB_DIV14                 14UL
#define LL_RCU_AHB_DIV15                 15UL
#define LL_RCU_AHB_DIV16                 16UL
#define LL_RCU_AHB_DIV17                 17UL
#define LL_RCU_AHB_DIV18                 18UL
#define LL_RCU_AHB_DIV19                 19UL
#define LL_RCU_AHB_DIV20                 20UL
#define LL_RCU_AHB_DIV21                 21UL
#define LL_RCU_AHB_DIV22                 22UL
#define LL_RCU_AHB_DIV23                 23UL
#define LL_RCU_AHB_DIV24                 24UL
#define LL_RCU_AHB_DIV25                 25UL
#define LL_RCU_AHB_DIV26                 26UL
#define LL_RCU_AHB_DIV27                 27UL
#define LL_RCU_AHB_DIV28                 28UL
#define LL_RCU_AHB_DIV29                 29UL
#define LL_RCU_AHB_DIV30                 30UL
#define LL_RCU_AHB_DIV31                 31UL
#define LL_RCU_AHB_DIV32                 32UL
#define LL_RCU_AHB_DIV33                  33UL
#define LL_RCU_AHB_DIV34                  34UL
#define LL_RCU_AHB_DIV35                  35UL
#define LL_RCU_AHB_DIV36                  36UL
#define LL_RCU_AHB_DIV37                  37UL
#define LL_RCU_AHB_DIV38                  38UL
#define LL_RCU_AHB_DIV39                  39UL
#define LL_RCU_AHB_DIV40                  40UL
#define LL_RCU_AHB_DIV41                  41UL
#define LL_RCU_AHB_DIV42                  42UL
#define LL_RCU_AHB_DIV43                  43UL
#define LL_RCU_AHB_DIV44                  44UL
#define LL_RCU_AHB_DIV45                  45UL
#define LL_RCU_AHB_DIV46                  46UL
#define LL_RCU_AHB_DIV47                  47UL
#define LL_RCU_AHB_DIV48                  48UL
#define LL_RCU_AHB_DIV49                  49UL
#define LL_RCU_AHB_DIV50                  50UL
#define LL_RCU_AHB_DIV51                  51UL
#define LL_RCU_AHB_DIV52                  52UL
#define LL_RCU_AHB_DIV53                  53UL
#define LL_RCU_AHB_DIV54                  54UL
#define LL_RCU_AHB_DIV55                  55UL
#define LL_RCU_AHB_DIV56                  56UL
#define LL_RCU_AHB_DIV57                  57UL
#define LL_RCU_AHB_DIV58                  58UL
#define LL_RCU_AHB_DIV59                  59UL
#define LL_RCU_AHB_DIV60                  60UL
#define LL_RCU_AHB_DIV61                  61UL
#define LL_RCU_AHB_DIV62                  62UL
#define LL_RCU_AHB_DIV63                  63UL
#define LL_RCU_AHB_DIV64                  64UL

#define IS_LL_RCU_AHB_DIV(__VAL__)            (((__VAL__) >= LL_RCU_AHB_DIV1) && \
                                                   ((__VAL__) <= LL_RCU_AHB_DIV64))

/**
  * @}
  */ /* RCU_LL_EC_AHB_Clock_Divider */

/** @defgroup RCU_LL_EC_APB_Clock_Divider LL RCU APB Clock Divider
  * @{
  */
#define LL_RCU_APB0ClkDivTypeDef          LL_RSV_DATA_TYPE

#define LL_RCU_APB0_DIV1                 1UL
#define LL_RCU_APB0_DIV2                 2UL
#define LL_RCU_APB0_DIV3                 3UL
#define LL_RCU_APB0_DIV4                 4UL
#define LL_RCU_APB0_DIV5                 5UL
#define LL_RCU_APB0_DIV6                 6UL
#define LL_RCU_APB0_DIV7                 7UL
#define LL_RCU_APB0_DIV8                 8UL
#define LL_RCU_APB0_DIV9                 9UL
#define LL_RCU_APB0_DIV10                10UL
#define LL_RCU_APB0_DIV11                11UL
#define LL_RCU_APB0_DIV12                12UL
#define LL_RCU_APB0_DIV13                13UL
#define LL_RCU_APB0_DIV14                14UL
#define LL_RCU_APB0_DIV15                15UL
#define LL_RCU_APB0_DIV16                16UL

#define IS_LL_RCU_APB0_DIV(__VAL__)            (((__VAL__) >= LL_RCU_APB0_DIV1) && \
                                                   ((__VAL__) <= LL_RCU_APB0_DIV16))

#define LL_RCU_APB1ClkDivTypeDef          LL_RSV_DATA_TYPE

#define LL_RCU_APB1_DIV1                 1UL
#define LL_RCU_APB1_DIV2                 2UL
#define LL_RCU_APB1_DIV3                 3UL
#define LL_RCU_APB1_DIV4                 4UL
#define LL_RCU_APB1_DIV5                 5UL
#define LL_RCU_APB1_DIV6                 6UL
#define LL_RCU_APB1_DIV7                 7UL
#define LL_RCU_APB1_DIV8                 8UL
#define LL_RCU_APB1_DIV9                 9UL
#define LL_RCU_APB1_DIV10                10UL
#define LL_RCU_APB1_DIV11                11UL
#define LL_RCU_APB1_DIV12                12UL
#define LL_RCU_APB1_DIV13                13UL
#define LL_RCU_APB1_DIV14                14UL
#define LL_RCU_APB1_DIV15                15UL
#define LL_RCU_APB1_DIV16                16UL

#define IS_LL_RCU_APB1_DIV(__VAL__)            (((__VAL__) >= LL_RCU_APB1_DIV1) && \
                                                   ((__VAL__) <= LL_RCU_APB1_DIV16))
/**
  * @}
  */ /* RCU_LL_EC_APB_Clock_Divider */

/** @defgroup RCU_LL_EC_GPIO_Clock_Divider LL RCU GPIO Debounce Clock Divider
  * @{
  */
#define LL_RCU_GpioDbcClkDivTypeDef             LL_RSV_DATA_TYPE

#define LL_RCU_GPIO_DBC_CLK_DIV1                        (1UL)       /*!< GPIO Debounce Clock Divider 1                    */
#define LL_RCU_GPIO_DBC_CLK_DIV2                        (2UL)       /*!< GPIO Debounce Clock Divider 2                    */
#define LL_RCU_GPIO_DBC_CLK_DIV3                        (3UL)       /*!< GPIO Debounce Clock Divider 3                    */
#define LL_RCU_GPIO_DBC_CLK_DIV4                        (4UL)       /*!< GPIO Debounce Clock Divider 4                    */
#define LL_RCU_GPIO_DBC_CLK_DIV5                        (5UL)       /*!< GPIO Debounce Clock Divider 5                    */
#define LL_RCU_GPIO_DBC_CLK_DIV6                        (6UL)       /*!< GPIO Debounce Clock Divider 6                    */
#define LL_RCU_GPIO_DBC_CLK_DIV7                        (7UL)       /*!< GPIO Debounce Clock Divider 7                    */
#define LL_RCU_GPIO_DBC_CLK_DIV8                        (8UL)       /*!< GPIO Debounce Clock Divider 8                    */
#define LL_RCU_GPIO_DBC_CLK_DIV9                        (9UL)       /*!< GPIO Debounce Clock Divider 9                    */
#define LL_RCU_GPIO_DBC_CLK_DIV10                       (10UL)      /*!< GPIO Debounce Clock Divider 10                   */
#define LL_RCU_GPIO_DBC_CLK_DIV11                       (11UL)      /*!< GPIO Debounce Clock Divider 11                   */
#define LL_RCU_GPIO_DBC_CLK_DIV12                       (12UL)      /*!< GPIO Debounce Clock Divider 12                   */
#define LL_RCU_GPIO_DBC_CLK_DIV13                       (13UL)      /*!< GPIO Debounce Clock Divider 13                   */
#define LL_RCU_GPIO_DBC_CLK_DIV14                       (14UL)      /*!< GPIO Debounce Clock Divider 14                   */
#define LL_RCU_GPIO_DBC_CLK_DIV15                       (15UL)      /*!< GPIO Debounce Clock Divider 15                   */
#define LL_RCU_GPIO_DBC_CLK_DIV16                       (16UL)      /*!< GPIO Debounce Clock Divider 16                   */
#define LL_RCU_GPIO_DBC_CLK_DIV17                       (17UL)      /*!< GPIO Debounce Clock Divider 17                   */
#define LL_RCU_GPIO_DBC_CLK_DIV18                       (18UL)      /*!< GPIO Debounce Clock Divider 18                   */
#define LL_RCU_GPIO_DBC_CLK_DIV19                       (19UL)      /*!< GPIO Debounce Clock Divider 19                   */
#define LL_RCU_GPIO_DBC_CLK_DIV20                       (20UL)      /*!< GPIO Debounce Clock Divider 20                   */
#define LL_RCU_GPIO_DBC_CLK_DIV21                       (21UL)      /*!< GPIO Debounce Clock Divider 21                   */
#define LL_RCU_GPIO_DBC_CLK_DIV22                       (22UL)      /*!< GPIO Debounce Clock Divider 22                   */
#define LL_RCU_GPIO_DBC_CLK_DIV23                       (23UL)      /*!< GPIO Debounce Clock Divider 23                   */
#define LL_RCU_GPIO_DBC_CLK_DIV24                       (24UL)      /*!< GPIO Debounce Clock Divider 24                   */
#define LL_RCU_GPIO_DBC_CLK_DIV25                       (25UL)      /*!< GPIO Debounce Clock Divider 25                   */
#define LL_RCU_GPIO_DBC_CLK_DIV26                       (26UL)      /*!< GPIO Debounce Clock Divider 26                   */
#define LL_RCU_GPIO_DBC_CLK_DIV27                       (27UL)      /*!< GPIO Debounce Clock Divider 27                   */
#define LL_RCU_GPIO_DBC_CLK_DIV28                       (28UL)      /*!< GPIO Debounce Clock Divider 28                   */
#define LL_RCU_GPIO_DBC_CLK_DIV29                       (29UL)      /*!< GPIO Debounce Clock Divider 29                   */
#define LL_RCU_GPIO_DBC_CLK_DIV30                       (30UL)      /*!< GPIO Debounce Clock Divider 30                   */
#define LL_RCU_GPIO_DBC_CLK_DIV31                       (31UL)      /*!< GPIO Debounce Clock Divider 31                   */
#define LL_RCU_GPIO_DBC_CLK_DIV32                       (32UL)      /*!< GPIO Debounce Clock Divider 32                   */
#define LL_RCU_GPIO_DBC_CLK_DIV33                       (33UL)      /*!< GPIO Debounce Clock Divider 33                   */
#define LL_RCU_GPIO_DBC_CLK_DIV34                       (34UL)      /*!< GPIO Debounce Clock Divider 34                   */
#define LL_RCU_GPIO_DBC_CLK_DIV35                       (35UL)      /*!< GPIO Debounce Clock Divider 35                   */
#define LL_RCU_GPIO_DBC_CLK_DIV36                       (36UL)      /*!< GPIO Debounce Clock Divider 36                   */
#define LL_RCU_GPIO_DBC_CLK_DIV37                       (37UL)      /*!< GPIO Debounce Clock Divider 37                   */
#define LL_RCU_GPIO_DBC_CLK_DIV38                       (38UL)      /*!< GPIO Debounce Clock Divider 38                   */
#define LL_RCU_GPIO_DBC_CLK_DIV39                       (39UL)      /*!< GPIO Debounce Clock Divider 39                   */
#define LL_RCU_GPIO_DBC_CLK_DIV40                       (40UL)      /*!< GPIO Debounce Clock Divider 40                   */
#define LL_RCU_GPIO_DBC_CLK_DIV41                       (41UL)      /*!< GPIO Debounce Clock Divider 41                   */
#define LL_RCU_GPIO_DBC_CLK_DIV42                       (42UL)      /*!< GPIO Debounce Clock Divider 42                   */
#define LL_RCU_GPIO_DBC_CLK_DIV43                       (43UL)      /*!< GPIO Debounce Clock Divider 43                   */
#define LL_RCU_GPIO_DBC_CLK_DIV44                       (44UL)      /*!< GPIO Debounce Clock Divider 44                   */
#define LL_RCU_GPIO_DBC_CLK_DIV45                       (45UL)      /*!< GPIO Debounce Clock Divider 45                   */
#define LL_RCU_GPIO_DBC_CLK_DIV46                       (46UL)      /*!< GPIO Debounce Clock Divider 46                   */
#define LL_RCU_GPIO_DBC_CLK_DIV47                       (47UL)      /*!< GPIO Debounce Clock Divider 47                   */
#define LL_RCU_GPIO_DBC_CLK_DIV48                       (48UL)      /*!< GPIO Debounce Clock Divider 48                   */
#define LL_RCU_GPIO_DBC_CLK_DIV49                       (49UL)      /*!< GPIO Debounce Clock Divider 49                   */
#define LL_RCU_GPIO_DBC_CLK_DIV50                       (50UL)      /*!< GPIO Debounce Clock Divider 50                   */
#define LL_RCU_GPIO_DBC_CLK_DIV51                       (51UL)      /*!< GPIO Debounce Clock Divider 51                   */
#define LL_RCU_GPIO_DBC_CLK_DIV52                       (52UL)      /*!< GPIO Debounce Clock Divider 52                   */
#define LL_RCU_GPIO_DBC_CLK_DIV53                       (53UL)      /*!< GPIO Debounce Clock Divider 53                   */
#define LL_RCU_GPIO_DBC_CLK_DIV54                       (54UL)      /*!< GPIO Debounce Clock Divider 54                   */
#define LL_RCU_GPIO_DBC_CLK_DIV55                       (55UL)      /*!< GPIO Debounce Clock Divider 55                   */
#define LL_RCU_GPIO_DBC_CLK_DIV56                       (56UL)      /*!< GPIO Debounce Clock Divider 56                   */
#define LL_RCU_GPIO_DBC_CLK_DIV57                       (57UL)      /*!< GPIO Debounce Clock Divider 57                   */
#define LL_RCU_GPIO_DBC_CLK_DIV58                       (58UL)      /*!< GPIO Debounce Clock Divider 58                   */
#define LL_RCU_GPIO_DBC_CLK_DIV59                       (59UL)      /*!< GPIO Debounce Clock Divider 59                   */
#define LL_RCU_GPIO_DBC_CLK_DIV60                       (60UL)      /*!< GPIO Debounce Clock Divider 60                   */
#define LL_RCU_GPIO_DBC_CLK_DIV61                       (61UL)      /*!< GPIO Debounce Clock Divider 61                   */
#define LL_RCU_GPIO_DBC_CLK_DIV62                       (62UL)      /*!< GPIO Debounce Clock Divider 62                   */
#define LL_RCU_GPIO_DBC_CLK_DIV63                       (63UL)      /*!< GPIO Debounce Clock Divider 63                   */
#define LL_RCU_GPIO_DBC_CLK_DIV64                       (64UL)      /*!< GPIO Debounce Clock Divider 64                   */
#define LL_RCU_GPIO_DBC_CLK_DIV65                       (65UL)      /*!< GPIO Debounce Clock Divider 65                   */
#define LL_RCU_GPIO_DBC_CLK_DIV66                       (66UL)      /*!< GPIO Debounce Clock Divider 66                   */
#define LL_RCU_GPIO_DBC_CLK_DIV67                       (67UL)      /*!< GPIO Debounce Clock Divider 67                   */
#define LL_RCU_GPIO_DBC_CLK_DIV68                       (68UL)      /*!< GPIO Debounce Clock Divider 68                   */
#define LL_RCU_GPIO_DBC_CLK_DIV69                       (69UL)      /*!< GPIO Debounce Clock Divider 69                   */
#define LL_RCU_GPIO_DBC_CLK_DIV70                       (70UL)      /*!< GPIO Debounce Clock Divider 70                   */
#define LL_RCU_GPIO_DBC_CLK_DIV71                       (71UL)      /*!< GPIO Debounce Clock Divider 71                   */
#define LL_RCU_GPIO_DBC_CLK_DIV72                       (72UL)      /*!< GPIO Debounce Clock Divider 72                   */
#define LL_RCU_GPIO_DBC_CLK_DIV73                       (73UL)      /*!< GPIO Debounce Clock Divider 73                   */
#define LL_RCU_GPIO_DBC_CLK_DIV74                       (74UL)      /*!< GPIO Debounce Clock Divider 74                   */
#define LL_RCU_GPIO_DBC_CLK_DIV75                       (75UL)      /*!< GPIO Debounce Clock Divider 75                   */
#define LL_RCU_GPIO_DBC_CLK_DIV76                       (76UL)      /*!< GPIO Debounce Clock Divider 76                   */
#define LL_RCU_GPIO_DBC_CLK_DIV77                       (77UL)      /*!< GPIO Debounce Clock Divider 77                   */
#define LL_RCU_GPIO_DBC_CLK_DIV78                       (78UL)      /*!< GPIO Debounce Clock Divider 78                   */
#define LL_RCU_GPIO_DBC_CLK_DIV79                       (79UL)      /*!< GPIO Debounce Clock Divider 79                   */
#define LL_RCU_GPIO_DBC_CLK_DIV80                       (80UL)      /*!< GPIO Debounce Clock Divider 80                   */
#define LL_RCU_GPIO_DBC_CLK_DIV81                       (81UL)      /*!< GPIO Debounce Clock Divider 81                   */
#define LL_RCU_GPIO_DBC_CLK_DIV82                       (82UL)      /*!< GPIO Debounce Clock Divider 82                   */
#define LL_RCU_GPIO_DBC_CLK_DIV83                       (83UL)      /*!< GPIO Debounce Clock Divider 83                   */
#define LL_RCU_GPIO_DBC_CLK_DIV84                       (84UL)      /*!< GPIO Debounce Clock Divider 84                   */
#define LL_RCU_GPIO_DBC_CLK_DIV85                       (85UL)      /*!< GPIO Debounce Clock Divider 85                   */
#define LL_RCU_GPIO_DBC_CLK_DIV86                       (86UL)      /*!< GPIO Debounce Clock Divider 86                   */
#define LL_RCU_GPIO_DBC_CLK_DIV87                       (87UL)      /*!< GPIO Debounce Clock Divider 87                   */
#define LL_RCU_GPIO_DBC_CLK_DIV88                       (88UL)      /*!< GPIO Debounce Clock Divider 88                   */
#define LL_RCU_GPIO_DBC_CLK_DIV89                       (89UL)      /*!< GPIO Debounce Clock Divider 89                   */
#define LL_RCU_GPIO_DBC_CLK_DIV90                       (90UL)      /*!< GPIO Debounce Clock Divider 90                   */
#define LL_RCU_GPIO_DBC_CLK_DIV91                       (91UL)      /*!< GPIO Debounce Clock Divider 91                   */
#define LL_RCU_GPIO_DBC_CLK_DIV92                       (92UL)      /*!< GPIO Debounce Clock Divider 92                   */
#define LL_RCU_GPIO_DBC_CLK_DIV93                       (93UL)      /*!< GPIO Debounce Clock Divider 93                   */
#define LL_RCU_GPIO_DBC_CLK_DIV94                       (94UL)      /*!< GPIO Debounce Clock Divider 94                   */
#define LL_RCU_GPIO_DBC_CLK_DIV95                       (95UL)      /*!< GPIO Debounce Clock Divider 95                   */
#define LL_RCU_GPIO_DBC_CLK_DIV96                       (96UL)      /*!< GPIO Debounce Clock Divider 96                   */
#define LL_RCU_GPIO_DBC_CLK_DIV97                       (97UL)      /*!< GPIO Debounce Clock Divider 97                   */
#define LL_RCU_GPIO_DBC_CLK_DIV98                       (98UL)      /*!< GPIO Debounce Clock Divider 98                   */
#define LL_RCU_GPIO_DBC_CLK_DIV99                       (99UL)      /*!< GPIO Debounce Clock Divider 99                   */
#define LL_RCU_GPIO_DBC_CLK_DIV100                      (100UL)     /*!< GPIO Debounce Clock Divider 100                  */
#define LL_RCU_GPIO_DBC_CLK_DIV101                      (101UL)     /*!< GPIO Debounce Clock Divider 101                  */
#define LL_RCU_GPIO_DBC_CLK_DIV102                      (102UL)     /*!< GPIO Debounce Clock Divider 102                  */
#define LL_RCU_GPIO_DBC_CLK_DIV103                      (103UL)     /*!< GPIO Debounce Clock Divider 103                  */
#define LL_RCU_GPIO_DBC_CLK_DIV104                      (104UL)     /*!< GPIO Debounce Clock Divider 104                  */
#define LL_RCU_GPIO_DBC_CLK_DIV105                      (105UL)     /*!< GPIO Debounce Clock Divider 105                  */
#define LL_RCU_GPIO_DBC_CLK_DIV106                      (106UL)     /*!< GPIO Debounce Clock Divider 106                  */
#define LL_RCU_GPIO_DBC_CLK_DIV107                      (107UL)     /*!< GPIO Debounce Clock Divider 107                  */
#define LL_RCU_GPIO_DBC_CLK_DIV108                      (108UL)     /*!< GPIO Debounce Clock Divider 108                  */
#define LL_RCU_GPIO_DBC_CLK_DIV109                      (109UL)     /*!< GPIO Debounce Clock Divider 109                  */
#define LL_RCU_GPIO_DBC_CLK_DIV110                      (110UL)     /*!< GPIO Debounce Clock Divider 110                  */
#define LL_RCU_GPIO_DBC_CLK_DIV111                      (111UL)     /*!< GPIO Debounce Clock Divider 111                  */
#define LL_RCU_GPIO_DBC_CLK_DIV112                      (112UL)     /*!< GPIO Debounce Clock Divider 112                  */
#define LL_RCU_GPIO_DBC_CLK_DIV113                      (113UL)     /*!< GPIO Debounce Clock Divider 113                  */
#define LL_RCU_GPIO_DBC_CLK_DIV114                      (114UL)     /*!< GPIO Debounce Clock Divider 114                  */
#define LL_RCU_GPIO_DBC_CLK_DIV115                      (115UL)     /*!< GPIO Debounce Clock Divider 115                  */
#define LL_RCU_GPIO_DBC_CLK_DIV116                      (116UL)     /*!< GPIO Debounce Clock Divider 116                  */
#define LL_RCU_GPIO_DBC_CLK_DIV117                      (117UL)     /*!< GPIO Debounce Clock Divider 117                  */
#define LL_RCU_GPIO_DBC_CLK_DIV118                      (118UL)     /*!< GPIO Debounce Clock Divider 118                  */
#define LL_RCU_GPIO_DBC_CLK_DIV119                      (119UL)     /*!< GPIO Debounce Clock Divider 119                  */
#define LL_RCU_GPIO_DBC_CLK_DIV120                      (120UL)     /*!< GPIO Debounce Clock Divider 120                  */
#define LL_RCU_GPIO_DBC_CLK_DIV121                      (121UL)     /*!< GPIO Debounce Clock Divider 121                  */
#define LL_RCU_GPIO_DBC_CLK_DIV122                      (122UL)     /*!< GPIO Debounce Clock Divider 122                  */
#define LL_RCU_GPIO_DBC_CLK_DIV123                      (123UL)     /*!< GPIO Debounce Clock Divider 123                  */
#define LL_RCU_GPIO_DBC_CLK_DIV124                      (124UL)     /*!< GPIO Debounce Clock Divider 124                  */
#define LL_RCU_GPIO_DBC_CLK_DIV125                      (125UL)     /*!< GPIO Debounce Clock Divider 125                  */
#define LL_RCU_GPIO_DBC_CLK_DIV126                      (126UL)     /*!< GPIO Debounce Clock Divider 126                  */
#define LL_RCU_GPIO_DBC_CLK_DIV127                      (127UL)     /*!< GPIO Debounce Clock Divider 127                  */
#define LL_RCU_GPIO_DBC_CLK_DIV128                      (128UL)     /*!< GPIO Debounce Clock Divider 128                  */
#define LL_RCU_GPIO_DBC_CLK_DIV129                      (129UL)     /*!< GPIO Debounce Clock Divider 129                  */
#define LL_RCU_GPIO_DBC_CLK_DIV130                      (130UL)     /*!< GPIO Debounce Clock Divider 130                  */
#define LL_RCU_GPIO_DBC_CLK_DIV131                      (131UL)     /*!< GPIO Debounce Clock Divider 131                  */
#define LL_RCU_GPIO_DBC_CLK_DIV132                      (132UL)     /*!< GPIO Debounce Clock Divider 132                  */
#define LL_RCU_GPIO_DBC_CLK_DIV133                      (133UL)     /*!< GPIO Debounce Clock Divider 133                  */
#define LL_RCU_GPIO_DBC_CLK_DIV134                      (134UL)     /*!< GPIO Debounce Clock Divider 134                  */
#define LL_RCU_GPIO_DBC_CLK_DIV135                      (135UL)     /*!< GPIO Debounce Clock Divider 135                  */
#define LL_RCU_GPIO_DBC_CLK_DIV136                      (136UL)     /*!< GPIO Debounce Clock Divider 136                  */
#define LL_RCU_GPIO_DBC_CLK_DIV137                      (137UL)     /*!< GPIO Debounce Clock Divider 137                  */
#define LL_RCU_GPIO_DBC_CLK_DIV138                      (138UL)     /*!< GPIO Debounce Clock Divider 138                  */
#define LL_RCU_GPIO_DBC_CLK_DIV139                      (139UL)     /*!< GPIO Debounce Clock Divider 139                  */
#define LL_RCU_GPIO_DBC_CLK_DIV140                      (140UL)     /*!< GPIO Debounce Clock Divider 140                  */
#define LL_RCU_GPIO_DBC_CLK_DIV141                      (141UL)     /*!< GPIO Debounce Clock Divider 141                  */
#define LL_RCU_GPIO_DBC_CLK_DIV142                      (142UL)     /*!< GPIO Debounce Clock Divider 142                  */
#define LL_RCU_GPIO_DBC_CLK_DIV143                      (143UL)     /*!< GPIO Debounce Clock Divider 143                  */
#define LL_RCU_GPIO_DBC_CLK_DIV144                      (144UL)     /*!< GPIO Debounce Clock Divider 144                  */
#define LL_RCU_GPIO_DBC_CLK_DIV145                      (145UL)     /*!< GPIO Debounce Clock Divider 145                  */
#define LL_RCU_GPIO_DBC_CLK_DIV146                      (146UL)     /*!< GPIO Debounce Clock Divider 146                  */
#define LL_RCU_GPIO_DBC_CLK_DIV147                      (147UL)     /*!< GPIO Debounce Clock Divider 147                  */
#define LL_RCU_GPIO_DBC_CLK_DIV148                      (148UL)     /*!< GPIO Debounce Clock Divider 148                  */
#define LL_RCU_GPIO_DBC_CLK_DIV149                      (149UL)     /*!< GPIO Debounce Clock Divider 149                  */
#define LL_RCU_GPIO_DBC_CLK_DIV150                      (150UL)     /*!< GPIO Debounce Clock Divider 150                  */
#define LL_RCU_GPIO_DBC_CLK_DIV151                      (151UL)     /*!< GPIO Debounce Clock Divider 151                  */
#define LL_RCU_GPIO_DBC_CLK_DIV152                      (152UL)     /*!< GPIO Debounce Clock Divider 152                  */
#define LL_RCU_GPIO_DBC_CLK_DIV153                      (153UL)     /*!< GPIO Debounce Clock Divider 153                  */
#define LL_RCU_GPIO_DBC_CLK_DIV154                      (154UL)     /*!< GPIO Debounce Clock Divider 154                  */
#define LL_RCU_GPIO_DBC_CLK_DIV155                      (155UL)     /*!< GPIO Debounce Clock Divider 155                  */
#define LL_RCU_GPIO_DBC_CLK_DIV156                      (156UL)     /*!< GPIO Debounce Clock Divider 156                  */
#define LL_RCU_GPIO_DBC_CLK_DIV157                      (157UL)     /*!< GPIO Debounce Clock Divider 157                  */
#define LL_RCU_GPIO_DBC_CLK_DIV158                      (158UL)     /*!< GPIO Debounce Clock Divider 158                  */
#define LL_RCU_GPIO_DBC_CLK_DIV159                      (159UL)     /*!< GPIO Debounce Clock Divider 159                  */
#define LL_RCU_GPIO_DBC_CLK_DIV160                      (160UL)     /*!< GPIO Debounce Clock Divider 160                  */
#define LL_RCU_GPIO_DBC_CLK_DIV161                      (161UL)     /*!< GPIO Debounce Clock Divider 161                  */
#define LL_RCU_GPIO_DBC_CLK_DIV162                      (162UL)     /*!< GPIO Debounce Clock Divider 162                  */
#define LL_RCU_GPIO_DBC_CLK_DIV163                      (163UL)     /*!< GPIO Debounce Clock Divider 163                  */
#define LL_RCU_GPIO_DBC_CLK_DIV164                      (164UL)     /*!< GPIO Debounce Clock Divider 164                  */
#define LL_RCU_GPIO_DBC_CLK_DIV165                      (165UL)     /*!< GPIO Debounce Clock Divider 165                  */
#define LL_RCU_GPIO_DBC_CLK_DIV166                      (166UL)     /*!< GPIO Debounce Clock Divider 166                  */
#define LL_RCU_GPIO_DBC_CLK_DIV167                      (167UL)     /*!< GPIO Debounce Clock Divider 167                  */
#define LL_RCU_GPIO_DBC_CLK_DIV168                      (168UL)     /*!< GPIO Debounce Clock Divider 168                  */
#define LL_RCU_GPIO_DBC_CLK_DIV169                      (169UL)     /*!< GPIO Debounce Clock Divider 169                  */
#define LL_RCU_GPIO_DBC_CLK_DIV170                      (170UL)     /*!< GPIO Debounce Clock Divider 170                  */
#define LL_RCU_GPIO_DBC_CLK_DIV171                      (171UL)     /*!< GPIO Debounce Clock Divider 171                  */
#define LL_RCU_GPIO_DBC_CLK_DIV172                      (172UL)     /*!< GPIO Debounce Clock Divider 172                  */
#define LL_RCU_GPIO_DBC_CLK_DIV173                      (173UL)     /*!< GPIO Debounce Clock Divider 173                  */
#define LL_RCU_GPIO_DBC_CLK_DIV174                      (174UL)     /*!< GPIO Debounce Clock Divider 174                  */
#define LL_RCU_GPIO_DBC_CLK_DIV175                      (175UL)     /*!< GPIO Debounce Clock Divider 175                  */
#define LL_RCU_GPIO_DBC_CLK_DIV176                      (176UL)     /*!< GPIO Debounce Clock Divider 176                  */
#define LL_RCU_GPIO_DBC_CLK_DIV177                      (177UL)     /*!< GPIO Debounce Clock Divider 177                  */
#define LL_RCU_GPIO_DBC_CLK_DIV178                      (178UL)     /*!< GPIO Debounce Clock Divider 178                  */
#define LL_RCU_GPIO_DBC_CLK_DIV179                      (179UL)     /*!< GPIO Debounce Clock Divider 179                  */
#define LL_RCU_GPIO_DBC_CLK_DIV180                      (180UL)     /*!< GPIO Debounce Clock Divider 180                  */
#define LL_RCU_GPIO_DBC_CLK_DIV181                      (181UL)     /*!< GPIO Debounce Clock Divider 181                  */
#define LL_RCU_GPIO_DBC_CLK_DIV182                      (182UL)     /*!< GPIO Debounce Clock Divider 182                  */
#define LL_RCU_GPIO_DBC_CLK_DIV183                      (183UL)     /*!< GPIO Debounce Clock Divider 183                  */
#define LL_RCU_GPIO_DBC_CLK_DIV184                      (184UL)     /*!< GPIO Debounce Clock Divider 184                  */
#define LL_RCU_GPIO_DBC_CLK_DIV185                      (185UL)     /*!< GPIO Debounce Clock Divider 185                  */
#define LL_RCU_GPIO_DBC_CLK_DIV186                      (186UL)     /*!< GPIO Debounce Clock Divider 186                  */
#define LL_RCU_GPIO_DBC_CLK_DIV187                      (187UL)     /*!< GPIO Debounce Clock Divider 187                  */
#define LL_RCU_GPIO_DBC_CLK_DIV188                      (188UL)     /*!< GPIO Debounce Clock Divider 188                  */
#define LL_RCU_GPIO_DBC_CLK_DIV189                      (189UL)     /*!< GPIO Debounce Clock Divider 189                  */
#define LL_RCU_GPIO_DBC_CLK_DIV190                      (190UL)     /*!< GPIO Debounce Clock Divider 190                  */
#define LL_RCU_GPIO_DBC_CLK_DIV191                      (191UL)     /*!< GPIO Debounce Clock Divider 191                  */
#define LL_RCU_GPIO_DBC_CLK_DIV192                      (192UL)     /*!< GPIO Debounce Clock Divider 192                  */
#define LL_RCU_GPIO_DBC_CLK_DIV193                      (193UL)     /*!< GPIO Debounce Clock Divider 193                  */
#define LL_RCU_GPIO_DBC_CLK_DIV194                      (194UL)     /*!< GPIO Debounce Clock Divider 194                  */
#define LL_RCU_GPIO_DBC_CLK_DIV195                      (195UL)     /*!< GPIO Debounce Clock Divider 195                  */
#define LL_RCU_GPIO_DBC_CLK_DIV196                      (196UL)     /*!< GPIO Debounce Clock Divider 196                  */
#define LL_RCU_GPIO_DBC_CLK_DIV197                      (197UL)     /*!< GPIO Debounce Clock Divider 197                  */
#define LL_RCU_GPIO_DBC_CLK_DIV198                      (198UL)     /*!< GPIO Debounce Clock Divider 198                  */
#define LL_RCU_GPIO_DBC_CLK_DIV199                      (199UL)     /*!< GPIO Debounce Clock Divider 199                  */
#define LL_RCU_GPIO_DBC_CLK_DIV200                      (200UL)     /*!< GPIO Debounce Clock Divider 200                  */
#define LL_RCU_GPIO_DBC_CLK_DIV201                      (201UL)     /*!< GPIO Debounce Clock Divider 201                  */
#define LL_RCU_GPIO_DBC_CLK_DIV202                      (202UL)     /*!< GPIO Debounce Clock Divider 202                  */
#define LL_RCU_GPIO_DBC_CLK_DIV203                      (203UL)     /*!< GPIO Debounce Clock Divider 203                  */
#define LL_RCU_GPIO_DBC_CLK_DIV204                      (204UL)     /*!< GPIO Debounce Clock Divider 204                  */
#define LL_RCU_GPIO_DBC_CLK_DIV205                      (205UL)     /*!< GPIO Debounce Clock Divider 205                  */
#define LL_RCU_GPIO_DBC_CLK_DIV206                      (206UL)     /*!< GPIO Debounce Clock Divider 206                  */
#define LL_RCU_GPIO_DBC_CLK_DIV207                      (207UL)     /*!< GPIO Debounce Clock Divider 207                  */
#define LL_RCU_GPIO_DBC_CLK_DIV208                      (208UL)     /*!< GPIO Debounce Clock Divider 208                  */
#define LL_RCU_GPIO_DBC_CLK_DIV209                      (209UL)     /*!< GPIO Debounce Clock Divider 209                  */
#define LL_RCU_GPIO_DBC_CLK_DIV210                      (210UL)     /*!< GPIO Debounce Clock Divider 210                  */
#define LL_RCU_GPIO_DBC_CLK_DIV211                      (211UL)     /*!< GPIO Debounce Clock Divider 211                  */
#define LL_RCU_GPIO_DBC_CLK_DIV212                      (212UL)     /*!< GPIO Debounce Clock Divider 212                  */
#define LL_RCU_GPIO_DBC_CLK_DIV213                      (213UL)     /*!< GPIO Debounce Clock Divider 213                  */
#define LL_RCU_GPIO_DBC_CLK_DIV214                      (214UL)     /*!< GPIO Debounce Clock Divider 214                  */
#define LL_RCU_GPIO_DBC_CLK_DIV215                      (215UL)     /*!< GPIO Debounce Clock Divider 215                  */
#define LL_RCU_GPIO_DBC_CLK_DIV216                      (216UL)     /*!< GPIO Debounce Clock Divider 216                  */
#define LL_RCU_GPIO_DBC_CLK_DIV217                      (217UL)     /*!< GPIO Debounce Clock Divider 217                  */
#define LL_RCU_GPIO_DBC_CLK_DIV218                      (218UL)     /*!< GPIO Debounce Clock Divider 218                  */
#define LL_RCU_GPIO_DBC_CLK_DIV219                      (219UL)     /*!< GPIO Debounce Clock Divider 219                  */
#define LL_RCU_GPIO_DBC_CLK_DIV220                      (220UL)     /*!< GPIO Debounce Clock Divider 220                  */
#define LL_RCU_GPIO_DBC_CLK_DIV221                      (221UL)     /*!< GPIO Debounce Clock Divider 221                  */
#define LL_RCU_GPIO_DBC_CLK_DIV222                      (222UL)     /*!< GPIO Debounce Clock Divider 222                  */
#define LL_RCU_GPIO_DBC_CLK_DIV223                      (223UL)     /*!< GPIO Debounce Clock Divider 223                  */
#define LL_RCU_GPIO_DBC_CLK_DIV224                      (224UL)     /*!< GPIO Debounce Clock Divider 224                  */
#define LL_RCU_GPIO_DBC_CLK_DIV225                      (225UL)     /*!< GPIO Debounce Clock Divider 225                  */
#define LL_RCU_GPIO_DBC_CLK_DIV226                      (226UL)     /*!< GPIO Debounce Clock Divider 226                  */
#define LL_RCU_GPIO_DBC_CLK_DIV227                      (227UL)     /*!< GPIO Debounce Clock Divider 227                  */
#define LL_RCU_GPIO_DBC_CLK_DIV228                      (228UL)     /*!< GPIO Debounce Clock Divider 228                  */
#define LL_RCU_GPIO_DBC_CLK_DIV229                      (229UL)     /*!< GPIO Debounce Clock Divider 229                  */
#define LL_RCU_GPIO_DBC_CLK_DIV230                      (230UL)     /*!< GPIO Debounce Clock Divider 230                  */
#define LL_RCU_GPIO_DBC_CLK_DIV231                      (231UL)     /*!< GPIO Debounce Clock Divider 231                  */
#define LL_RCU_GPIO_DBC_CLK_DIV232                      (232UL)     /*!< GPIO Debounce Clock Divider 232                  */
#define LL_RCU_GPIO_DBC_CLK_DIV233                      (233UL)     /*!< GPIO Debounce Clock Divider 233                  */
#define LL_RCU_GPIO_DBC_CLK_DIV234                      (234UL)     /*!< GPIO Debounce Clock Divider 234                  */
#define LL_RCU_GPIO_DBC_CLK_DIV235                      (235UL)     /*!< GPIO Debounce Clock Divider 235                  */
#define LL_RCU_GPIO_DBC_CLK_DIV236                      (236UL)     /*!< GPIO Debounce Clock Divider 236                  */
#define LL_RCU_GPIO_DBC_CLK_DIV237                      (237UL)     /*!< GPIO Debounce Clock Divider 237                  */
#define LL_RCU_GPIO_DBC_CLK_DIV238                      (238UL)     /*!< GPIO Debounce Clock Divider 238                  */
#define LL_RCU_GPIO_DBC_CLK_DIV239                      (239UL)     /*!< GPIO Debounce Clock Divider 239                  */
#define LL_RCU_GPIO_DBC_CLK_DIV240                      (240UL)     /*!< GPIO Debounce Clock Divider 240                  */
#define LL_RCU_GPIO_DBC_CLK_DIV241                      (241UL)     /*!< GPIO Debounce Clock Divider 241                  */
#define LL_RCU_GPIO_DBC_CLK_DIV242                      (242UL)     /*!< GPIO Debounce Clock Divider 242                  */
#define LL_RCU_GPIO_DBC_CLK_DIV243                      (243UL)     /*!< GPIO Debounce Clock Divider 243                  */
#define LL_RCU_GPIO_DBC_CLK_DIV244                      (244UL)     /*!< GPIO Debounce Clock Divider 244                  */
#define LL_RCU_GPIO_DBC_CLK_DIV245                      (245UL)     /*!< GPIO Debounce Clock Divider 245                  */
#define LL_RCU_GPIO_DBC_CLK_DIV246                      (246UL)     /*!< GPIO Debounce Clock Divider 246                  */
#define LL_RCU_GPIO_DBC_CLK_DIV247                      (247UL)     /*!< GPIO Debounce Clock Divider 247                  */
#define LL_RCU_GPIO_DBC_CLK_DIV248                      (248UL)     /*!< GPIO Debounce Clock Divider 248                  */
#define LL_RCU_GPIO_DBC_CLK_DIV249                      (249UL)     /*!< GPIO Debounce Clock Divider 249                  */
#define LL_RCU_GPIO_DBC_CLK_DIV250                      (250UL)     /*!< GPIO Debounce Clock Divider 250                  */
#define LL_RCU_GPIO_DBC_CLK_DIV251                      (251UL)     /*!< GPIO Debounce Clock Divider 251                  */
#define LL_RCU_GPIO_DBC_CLK_DIV252                      (252UL)     /*!< GPIO Debounce Clock Divider 252                  */
#define LL_RCU_GPIO_DBC_CLK_DIV253                      (253UL)     /*!< GPIO Debounce Clock Divider 253                  */
#define LL_RCU_GPIO_DBC_CLK_DIV254                      (254UL)     /*!< GPIO Debounce Clock Divider 254                  */
#define LL_RCU_GPIO_DBC_CLK_DIV255                      (255UL)     /*!< GPIO Debounce Clock Divider 255                  */
#define LL_RCU_GPIO_DBC_CLK_DIV256                      (256UL)     /*!< GPIO Debounce Clock Divider 256                  */
/**
  * @}
  */ /* RCU_LL_EC_GPIO_Clock_Divider */

/**
  * @brief RCU PLL Refer Clock Division Definition
  */
#define LL_RCU_PllPreDivTypeDef                   uint32_t

#define LL_RCU_PLL_PRE_DIV_IVD                    0UL
#define LL_RCU_PLL_PRE_DIV_1                      1UL
#define LL_RCU_PLL_PRE_DIV_2                      2UL

#define IS_LL_RCU_PLL_PRE_DIV(__VAL__)            (((__VAL__) >= LL_RCU_PLL_PRE_DIV_1) && \
                                                   ((__VAL__) <= LL_RCU_PLL_PRE_DIV_2))

/**
  * @brief RCU Function Clock Divider Definition
  */
#define LL_RCU_FuncClkDivTypeDef                  uint32_t

#define LL_RCU_FUNC_CLK_DIV1                      1UL
#define LL_RCU_FUNC_CLK_DIV2                      2UL
#define LL_RCU_FUNC_CLK_DIV3                      3UL
#define LL_RCU_FUNC_CLK_DIV4                      4UL
#define LL_RCU_FUNC_CLK_DIV5                      5UL
#define LL_RCU_FUNC_CLK_DIV6                      6UL
#define LL_RCU_FUNC_CLK_DIV7                      7UL
#define LL_RCU_FUNC_CLK_DIV8                      8UL
#define LL_RCU_FUNC_CLK_DIV9                      9UL
#define LL_RCU_FUNC_CLK_DIV10                     10UL
#define LL_RCU_FUNC_CLK_DIV11                     11UL
#define LL_RCU_FUNC_CLK_DIV12                     12UL
#define LL_RCU_FUNC_CLK_DIV13                     13UL
#define LL_RCU_FUNC_CLK_DIV14                     14UL
#define LL_RCU_FUNC_CLK_DIV15                     15UL
#define LL_RCU_FUNC_CLK_DIV16                     16UL

#define IS_LL_RCU_FUNC_CLK_DIV(__VAL__)           (((__VAL__) >= LL_RCU_FUNC_CLK_DIV1) && \
                                                   ((__VAL__) <= LL_RCU_FUNC_CLK_DIV16))

/**
  * @}
  */ /* RCU_LL_Exported_Constants */

/* Exported Types ------------------------------------------------------------*/
/** @defgroup RCU_LL_Exported_Types RCU LL Exported Types
  * @brief    RCU LL Exported Types
  * @{
  */


/**
  * @brief RCU PLL Band Definition
  */
#define LL_RCU_PllBandTypeDef                     uint32_t

#define LL_RCU_PLL_BAND_0                         0UL
#define LL_RCU_PLL_BAND_1                         1UL
#define LL_RCU_PLL_BAND_2                         2UL
#define LL_RCU_PLL_BAND_3                         3UL

#define IS_LL_RCU_PLL_BAND(__VAL__)               (((__VAL__) == LL_RCU_PLL_BAND_0) || \
                                                   ((__VAL__) == LL_RCU_PLL_BAND_1) || \
                                                   ((__VAL__) == LL_RCU_PLL_BAND_2) || \
                                                   ((__VAL__) == LL_RCU_PLL_BAND_3))


/**
  * @brief RCU Peripheral Function Clock Source Definition
  */
#define LL_RCU_FuncClkSrcTypeDef                  uint32_t

#define LL_RCU_FUNC_CLK_SRC_SYSCLK                0UL
#define LL_RCU_FUNC_CLK_SRC_PLL0                  1UL

#define IS_LL_RCU_FUNC_CLK_SRC(__VAL__)           (((__VAL__) == LL_RCU_FUNC_CLK_SRC_SYSCLK) || \
                                                   ((__VAL__) == LL_RCU_FUNC_CLK_SRC_PLL0))

/**
  * @brief RCU Peripheral Function Clock Source Extend Definition
  */
#define LL_RCU_FuncClkSrcExTypeDef                uint32_t

#define LL_RCU_FUNC_CLK_SRC_EX_HSI                0UL
#define LL_RCU_FUNC_CLK_SRC_EX_APB0CLK            1UL
#define LL_RCU_FUNC_CLK_SRC_EX_HSE                2UL
#define LL_RCU_FUNC_CLK_SRC_EX_LSI                3UL

#define IS_LL_RCU_CLK_SRC_EX(__VAL__)             (((__VAL__) == LL_RCU_FUNC_CLK_SRC_EX_HSI)     || \
                                                   ((__VAL__) == LL_RCU_FUNC_CLK_SRC_EX_APB0CLK) || \
                                                   ((__VAL__) == LL_RCU_FUNC_CLK_SRC_EX_HSE)     || \
                                                   ((__VAL__) == LL_RCU_FUNC_CLK_SRC_EX_LSI))

/**
  * @brief RCU Internal Clock Fanout Source Definition
  */
#define LL_RCU_IntClkFanoutSrcTypeDef             uint32_t

#define LL_RCU_INT_CLK_FANOUT_SRC_LSI             0UL
#define LL_RCU_INT_CLK_FANOUT_SRC_HSI             1UL
#define LL_RCU_INT_CLK_FANOUT_SRC_HSE             2UL
#define LL_RCU_INT_CLK_FANOUT_SRC_FCLK            3UL
#define LL_RCU_INT_CLK_FANOUT_SRC_PLL_DIV32       4UL

#define IS_LL_RCU_INT_CLK_FANOUT_SRC(__VAL__)     (((__VAL__) == LL_RCU_INT_CLK_FANOUT_SRC_LSI)    || \
                                                   ((__VAL__) == LL_RCU_INT_CLK_FANOUT_SRC_HSI)    || \
                                                   ((__VAL__) == LL_RCU_INT_CLK_FANOUT_SRC_HSE)    || \
                                                   ((__VAL__) == LL_RCU_INT_CLK_FANOUT_SRC_FCLK)   || \
                                                   ((__VAL__) == LL_RCU_INT_CLK_FANOUT_SRC_PLL_DIV32))

/** 
  * @brief RCU XOSC Limit Window Width
  */
#define LL_RCU_XOSCLimitWinTypeDef                uint32_t

#define LL_RCU_XOSC_LIMIT_WINDOW_2CYCLE           (0UL)  /*!< XOSC Limit Window Width -2 ~ +2 Cycle */
#define LL_RCU_XOSC_LIMIT_WINDOW_4CYCLE           (1UL)  /*!< XOSC Limit Window Width -4 ~ +4 Cycle */
#define LL_RCU_XOSC_LIMIT_WINDOW_6CYCLE           (2UL)  /*!< XOSC Limit Window Width -6 ~ +6 Cycle */
#define LL_RCU_XOSC_LIMIT_WINDOW_8CYCLE           (3UL)  /*!< XOSC Limit Window Width -8 ~ +8 Cycle */

#define IS_LL_RCU_XOSC_LIMIT_WINDOW(__VAL__)      (((__VAL__) == LL_RCU_XOSC_LIMIT_WINDOW_2CYCLE) || \
                                                   ((__VAL__) == LL_RCU_XOSC_LIMIT_WINDOW_4CYCLE) || \
                                                   ((__VAL__) == LL_RCU_XOSC_LIMIT_WINDOW_6CYCLE) || \
                                                   ((__VAL__) == LL_RCU_XOSC_LIMIT_WINDOW_8CYCLE))

/** 
  * @brief RCU XOSC AutoSwitch Switch Window Width
  */
#define LL_RCU_XOSCSwitchWinTypeDef               uint32_t

#define LL_RCU_XOSC_SWITCH_WINDOW_3US             (0UL)  /*!< XOSC AutoSwitch Window Width 3us  */
#define LL_RCU_XOSC_SWITCH_WINDOW_6US             (1UL)  /*!< XOSC AutoSwitch Window Width 6us  */
#define LL_RCU_XOSC_SWITCH_WINDOW_9US             (2UL)  /*!< XOSC AutoSwitch Window Width 9us  */
#define LL_RCU_XOSC_SWITCH_WINDOW_12US            (3UL)  /*!< XOSC AutoSwitch Window Width 12us */

#define IS_LL_RCU_XOSC_SWITCH_WINDOW(__VAL__)     (((__VAL__) == LL_RCU_XOSC_SWITCH_WINDOW_3US)  || \
                                                   ((__VAL__) == LL_RCU_XOSC_SWITCH_WINDOW_6US)  || \
                                                   ((__VAL__) == LL_RCU_XOSC_SWITCH_WINDOW_9US)  || \
                                                   ((__VAL__) == LL_RCU_XOSC_SWITCH_WINDOW_12US))

/**
  * @}
  */ /* RCU_LL_Exported_Types */

/* Exported Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
/** @defgroup RCU_LL_Exported_Functions RCU LL Exported Functions
  * @brief    RCU LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_RCU_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_RCU_ASSERT_INLINE_PARAM == 1)
extern void LL_RCU_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_RCU_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_RCU_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_RCU_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @brief  LPTMR (TMR6) CLK Enable
  * @param  RCUx Specifies RCU peripheral
  * @return None
 */
__STATIC_INLINE void LL_RCU_APB0_EnableLPTMRClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk);
}

/**
  * @brief  TMR6 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableLPTMRClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk);
}

/**
  * @brief  TMR6 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetLPTMR(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk);
}

/**
  * @brief  TMR6 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetLPTMR(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk);
}

/**
  * @brief  TMR6 (Low Power Timer) CLK Enable
  * @note   Same hardware as LL_RCU_APB0_EnableLPTMRClock(): the low power timer is TMR6
  *         (manual chapter 31, Low Power Timer), bit APB0ENR.TMR6EN
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableTMR6Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk);
}

/**
  * @brief  TMR6 (Low Power Timer) CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableTMR6Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk);
}

/**
  * @brief  TMR6 (Low Power Timer) Soft Reset Assert
  * @note   APB0RSTR.TMR6RST: 0 = reset, 1 = release (manual 7.3.2.13 p80)
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetTMR6(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk);
}

/**
  * @brief  TMR6 (Low Power Timer) Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetTMR6(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk);
}

/**
  * @brief  Get AHB Clock Divider
  * @param  RCUx Specifies RCU peripheral
  * @return AHB clock divider value (1..32)
  */
__STATIC_INLINE uint32_t LL_RCU_GetAHBPrescaler(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->CCR, RCU_CCR_HPSC_Msk, RCU_CCR_HPSC_Pos) + 1);
}

/**
  * @brief  Get APB0 Clock Divider
  * @param  RCUx Specifies RCU peripheral
  * @return APB0 clock divider value (1..16)
  */
__STATIC_INLINE uint32_t LL_RCU_GetAPB0Prescaler(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->CCR, RCU_CCR_P0PSC_Msk, RCU_CCR_P0PSC_Pos) + 1);
}

/**
  * @brief  Get APB1 Clock Divider
  * @param  RCUx Specifies RCU peripheral
  * @return APB1 clock divider value (1..16)
  */
__STATIC_INLINE uint32_t LL_RCU_GetAPB1Prescaler(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->CCR, RCU_CCR_P1PSC_Msk, RCU_CCR_P1PSC_Pos) + 1);
}

/**
  * @brief  PLL0 Pre Div Set to 1
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_PreDivider_1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PLL0CR, RCU_PLL0CR_RFD_Msk);
}

/**
  * @brief  PLL0 Pre Div Set to 2
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_PreDivider_2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PLL0CR, RCU_PLL0CR_RFD_Msk);
}

/**
  * @brief  PLL0 LPF 12M High Set
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_Set12MHigh(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PLL0CR, RCU_PLL0CR_LPF_Msk);
}

/**
  * @brief  PLL0 LPF 12M Low Set
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_Set12MLow(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PLL0CR, RCU_PLL0CR_LPF_Msk);
}

/**
  * @brief  PLL0 Band Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  band PLL0 Band
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_SetBand(RCU_TypeDef *RCUx, uint32_t Band)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PLL0CR, RCU_PLL0CR_BDS_Msk, (((Band) & RCU_PLL0CR_BDS_Val) << RCU_PLL0CR_BDS_Pos));
}

/**
  * @brief  PLL0 Band Get
  * @param  RCUx Specifies RCU peripheral
  * @return
  */
__STATIC_INLINE uint32_t LL_RCU_PLL0_GetBand(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT(RCUx->PLL0CR, RCU_PLL0CR_BDS_Msk, RCU_PLL0CR_BDS_Pos);
}

/**
  * @brief  PLL0 Update Generate
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_GenerateUpdate(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PLL0CR, RCU_PLL0CR_UG_Msk);
}

/**
  * @brief  PLL0 AutoReload Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_AutoReload_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PLL0CR, RCU_PLL0CR_ARE_Msk);
}

/**
  * @brief  PLL0 AutoReload Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_AutoReload_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PLL0CR, RCU_PLL0CR_ARE_Msk);
}

/**
  * @brief  PLL0 VCODET Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_VCODET_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PLL0CR, LL_RCU_PLL0CR_VCO_DET);
}

/**
  * @brief  PLL0 VCODET Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_VCODET_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PLL0CR, LL_RCU_PLL0CR_VCO_DET);
}

/**
  * @brief  SYSCLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src SYSCLK Source
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetSysClockSource(RCU_TypeDef *RCUx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->CCR, RCU_CCR_SCS_Msk, (((Src) & 0x3UL) << RCU_CCR_SCS_Pos));
}

/**
  * @brief  LPTMR CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src LPTMR CLK Source @ref LL_RCU_FuncClkSrcExTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetLPTMRClockSource(RCU_TypeDef *RCUx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));
    ASSERT_INLINE_PARAM(IS_LL_RCU_LPTMR_CLK_SRC(Src));

    MODIFY_REG((RCUx)->PCSR, RCU_PCSR_TMR6CS_Msk, (((Src) & 0x3UL) << RCU_PCSR_TMR6CS_Pos));
}

/**
  * @brief  LPTMR CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return LPTMR CLK Source @ref LL_RCU_FuncClkSrcExTypeDef
  */
__STATIC_INLINE uint32_t LL_RCU_GetLPTMRClockSource(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCSR, RCU_PCSR_TMR6CS_Msk, RCU_PCSR_TMR6CS_Pos);
}

/**
  * @brief  CAN CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src CAN CLK Source
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetCANClockSource(RCU_TypeDef *RCUx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCSR, RCU_PCSR_CANCS_Msk, (((Src) & 0x3UL) << RCU_PCSR_CANCS_Pos));
}

/**
  * @brief  CAN CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return CAN CLK Source
  */
__STATIC_INLINE uint32_t LL_RCU_GetCANClockSource(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCSR, RCU_PCSR_CANCS_Msk, RCU_PCSR_CANCS_Pos);
}

/**
  * @brief  USB CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src USB CLK Source
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetUSBClockSource(RCU_TypeDef *RCUx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCSR, RCU_PCSR_USBCS_Msk, (((Src) & 0x3UL) << RCU_PCSR_USBCS_Pos));
}

/**
  * @brief  USB CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return USB CLK Source
  */
__STATIC_INLINE uint32_t LL_RCU_GetUSBClockSource(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCSR, RCU_PCSR_USBCS_Msk, RCU_PCSR_USBCS_Pos);
}

/**
  * @brief  ADC CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src ADC CLK Source
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetADCClockSource(RCU_TypeDef *RCUx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCSR, RCU_PCSR_ADCCS_Msk, (((Src) & 0x3UL) << RCU_PCSR_ADCCS_Pos));
}

/**
  * @brief  ADC CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return ADC CLK Source
  */
__STATIC_INLINE uint32_t LL_RCU_GetADCClockSource(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCSR, RCU_PCSR_ADCCS_Msk, RCU_PCSR_ADCCS_Pos);
}

/**
  * @brief  GPIOD Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOD Debounce CLK Div @ref LL_RCU_GpioDbcClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetGPIODDbcClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR0, RCU_PCDR0_PDDIV_Msk, (((Div-1) & RCU_PCDR0_PDDIV_Val) << RCU_PCDR0_PDDIV_Pos));
}

/**
  * @brief  GPIOD Debounce CLK Div Get
  * @param  RCUx Specifies RCU peripheral
  * @return GPIOD Debounce CLK Div Value @ref LL_RCU_GpioDbcClkDivTypeDef
  */
__STATIC_INLINE uint32_t LL_RCU_GetGPIODDbcClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->PCDR0, RCU_PCDR0_PDDIV_Msk, RCU_PCDR0_PDDIV_Pos) + 1);
}

/**
  * @brief  GPIOC Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOC Debounce CLK Div @ref LL_RCU_GpioDbcClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetGPIOCDbcClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR0, RCU_PCDR0_PCDIV_Msk, (((Div-1) & RCU_PCDR0_PCDIV_Val) << RCU_PCDR0_PCDIV_Pos));
}

/**
  * @brief  GPIOC Debounce CLK Div Get
  * @param  RCUx Specifies RCU peripheral
  * @return GPIOC Debounce CLK Div Value @ref LL_RCU_GpioDbcClkDivTypeDef
  */
__STATIC_INLINE uint32_t LL_RCU_GetGPIOCDbcClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->PCDR0, RCU_PCDR0_PCDIV_Msk, RCU_PCDR0_PCDIV_Pos) + 1);
}

/**
  * @brief  GPIOB Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOB Debounce CLK Div @ref LL_RCU_GpioDbcClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetGPIOBDbcClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR0, RCU_PCDR0_PBDIV_Msk, (((Div-1) & RCU_PCDR0_PBDIV_Val) << RCU_PCDR0_PBDIV_Pos));
}

/**
  * @brief  GPIOB Debounce CLK Div Get
  * @param  RCUx Specifies RCU peripheral
  * @return GPIOB Debounce CLK Div Value @ref LL_RCU_GpioDbcClkDivTypeDef
  */
__STATIC_INLINE uint32_t LL_RCU_GetGPIOBDbcClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->PCDR0, RCU_PCDR0_PBDIV_Msk, RCU_PCDR0_PBDIV_Pos) + 1);
}

/**
  * @brief  GPIOA Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOA Debounce CLK Div @ref LL_RCU_GpioDbcClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetGPIOADbcClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR0, RCU_PCDR0_PADIV_Msk, (((Div-1) & RCU_PCDR0_PADIV_Val) << RCU_PCDR0_PADIV_Pos));
}

/**
  * @brief  GPIOA Debounce CLK Div Get
  * @param  RCUx Specifies RCU peripheral
  * @return GPIOA Debounce CLK Div Value @ref LL_RCU_GpioDbcClkDivTypeDef
  */
__STATIC_INLINE uint32_t LL_RCU_GetGPIOADbcClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->PCDR0, RCU_PCDR0_PADIV_Msk, RCU_PCDR0_PADIV_Pos) + 1);
}

/**
  * @brief  GPIOE Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOE Debounce CLK Div @ref LL_RCU_GpioDbcClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetGPIOEDbcClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR1, RCU_PCDR1_PEDIV_Msk, (((Div-1) & RCU_PCDR1_PEDIV_Val) << RCU_PCDR1_PEDIV_Pos));
}

/**
  * @brief  GPIOE Debounce CLK Div Get
  * @param  RCUx Specifies RCU peripheral
  * @return GPIOE Debounce CLK Div Value @ref LL_RCU_GpioDbcClkDivTypeDef
  */
__STATIC_INLINE uint32_t LL_RCU_GetGPIOEDbcClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->PCDR1, RCU_PCDR1_PEDIV_Msk, RCU_PCDR1_PEDIV_Pos) + 1);
}

/**
  * @brief  GPIOF Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOF Debounce CLK Div @ref LL_RCU_GpioDbcClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetGPIOFDbcClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR1, RCU_PCDR1_PFDIV_Msk, (((Div-1) & RCU_PCDR1_PFDIV_Val) << RCU_PCDR1_PFDIV_Pos));
}

/**
  * @brief  GPIOF Debounce CLK Div Get
  * @param  RCUx Specifies RCU peripheral
  * @return GPIOF Debounce CLK Div Value @ref LL_RCU_GpioDbcClkDivTypeDef
  */
__STATIC_INLINE uint32_t LL_RCU_GetGPIOFDbcClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT(RCUx->PCDR1, RCU_PCDR1_PFDIV_Msk, RCU_PCDR1_PFDIV_Pos) + 1);
}

/**
  * @brief  CAN Clk Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div CAN Clk Div
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetCANClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR2, RCU_PCDR2_CANDIV_Msk, (((Div-1) & 0xfUL) << RCU_PCDR2_CANDIV_Pos));
}

/**
  * @brief  CAN Clk Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return CAN Clk Div
  */
__STATIC_INLINE uint32_t LL_RCU_GetCANClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->PCDR2, RCU_PCDR2_CANDIV_Msk, RCU_PCDR2_CANDIV_Pos) + 1);
}

/**
  * @brief  USB Clk Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div USB Clk Div
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetUSBClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR2, RCU_PCDR2_USBDIV_Msk, (((Div-1) & 0xfUL) << RCU_PCDR2_USBDIV_Pos));
}

/**
  * @brief  USB Clk Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return USB Clk Div
  */
__STATIC_INLINE uint32_t LL_RCU_GetUSBClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->PCDR2, RCU_PCDR2_USBDIV_Msk, RCU_PCDR2_USBDIV_Pos) + 1);
}

/**
  * @brief  ADC Clk Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div ADC Clk Div
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetADCClockDivider(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->PCDR2, RCU_PCDR2_ADCDIV_Msk, (((Div-1) & 0xfUL) << RCU_PCDR2_ADCDIV_Pos));
}

/**
  * @brief  ADC Clk Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return ADC Clk Div
  */
__STATIC_INLINE uint32_t LL_RCU_GetADCClockDivider(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->PCDR2, RCU_PCDR2_ADCDIV_Msk, RCU_PCDR2_ADCDIV_Pos) + 1);
}

/**
  * @brief  TMR6 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableTMR6FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_TMR6FEN_Msk);
}

/**
  * @brief  TMR6 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableTMR6FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_TMR6FEN_Msk);
}

/**
  * @brief  Judge is TMR6 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledTMR6FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_TMR6FEN_Msk, RCU_PCENR_TMR6FEN_Pos);
}

/**
  * @brief  CAN1 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableCAN1FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_CAN1FEN_Msk);
}

/**
  * @brief  CAN1 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableCAN1FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_CAN1FEN_Msk);
}

/**
  * @brief  Judge is CAN1 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledCAN1FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_CAN1FEN_Msk, RCU_PCENR_CAN1FEN_Pos);
}

/**
  * @brief  CAN0 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableCAN0FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_CAN0FEN_Msk);
}

/**
  * @brief  CAN0 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableCAN0FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_CAN0FEN_Msk);
}

/**
  * @brief  Judge is CAN0 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledCAN0FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_CAN0FEN_Msk, RCU_PCENR_CAN0FEN_Pos);
}

/**
  * @brief  USB Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableUSBFunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_USBFEN_Msk);
}

/**
  * @brief  USB Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableUSBFunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_USBFEN_Msk);
}

/**
  * @brief  Judge is USB Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledUSBFunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_USBFEN_Msk, RCU_PCENR_USBFEN_Pos);
}

/**
  * @brief  HRPWM7 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM7FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM7FEN_Msk);
}

/**
  * @brief  HRPWM7 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM7FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM7FEN_Msk);
}

/**
  * @brief  Judge is HRPWM7 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM7FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM7FEN_Msk, RCU_PCENR_PWM7FEN_Pos);
}

/**
  * @brief  HRPWM6 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM6FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM6FEN_Msk);
}

/**
  * @brief  HRPWM6 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM6FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM6FEN_Msk);
}

/**
  * @brief  Judge is HRPWM6 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM6FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM6FEN_Msk, RCU_PCENR_PWM6FEN_Pos);
}

/**
  * @brief  HRPWM5 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM5FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM5FEN_Msk);
}

/**
  * @brief  HRPWM5 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM5FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM5FEN_Msk);
}

/**
  * @brief  Judge is HRPWM5 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM5FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM5FEN_Msk, RCU_PCENR_PWM5FEN_Pos);
}

/**
  * @brief  HRPWM4 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM4FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM4FEN_Msk);
}

/**
  * @brief  HRPWM4 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM4FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM4FEN_Msk);
}

/**
  * @brief  Judge is HRPWM4 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM4FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM4FEN_Msk, RCU_PCENR_PWM4FEN_Pos);
}

/**
  * @brief  HRPWM3 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM3FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM3FEN_Msk);
}

/**
  * @brief  HRPWM3 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM3FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM3FEN_Msk);
}

/**
  * @brief  Judge is HRPWM3 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM3FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM3FEN_Msk, RCU_PCENR_PWM3FEN_Pos);
}

/**
  * @brief  HRPWM2 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM2FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM2FEN_Msk);
}

/**
  * @brief  HRPWM2 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM2FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM2FEN_Msk);
}

/**
  * @brief  Judge is HRPWM2 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM2FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM2FEN_Msk, RCU_PCENR_PWM2FEN_Pos);
}

/**
  * @brief  HRPWM1 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM1FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM1FEN_Msk);
}

/**
  * @brief  HRPWM1 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM1FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM1FEN_Msk);
}

/**
  * @brief  Judge is HRPWM1 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM1FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM1FEN_Msk, RCU_PCENR_PWM1FEN_Pos);
}

/**
  * @brief  HRPWM0 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableHRPWM0FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_PWM0FEN_Msk);
}

/**
  * @brief  HRPWM0 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableHRPWM0FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_PWM0FEN_Msk);
}

/**
  * @brief  Judge is HRPWM0 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledHRPWM0FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_PWM0FEN_Msk, RCU_PCENR_PWM0FEN_Pos);
}

/**
  * @brief  ADC3 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableADC3FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_ADC3FEN_Msk);
}

/**
  * @brief  ADC3 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableADC3FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_ADC3FEN_Msk);
}

/**
  * @brief  Judge is ADC3 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledADC3FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_ADC3FEN_Msk, RCU_PCENR_ADC3FEN_Pos);
}

/**
  * @brief  ADC2 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableADC2FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_ADC2FEN_Msk);
}

/**
  * @brief  ADC2 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableADC2FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_ADC2FEN_Msk);
}

/**
  * @brief  Judge is ADC2 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledADC2FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_ADC2FEN_Msk, RCU_PCENR_ADC2FEN_Pos);
}

/**
  * @brief  ADC1 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableADC1FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_ADC1FEN_Msk);
}

/**
  * @brief  ADC1 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableADC1FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_ADC1FEN_Msk);
}

/**
  * @brief  Judge is ADC1 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledADC1FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_ADC1FEN_Msk, RCU_PCENR_ADC1FEN_Pos);
}

/**
  * @brief  ADC0 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_EnableADC0FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->PCENR, RCU_PCENR_ADC0FEN_Msk);
}

/**
  * @brief  ADC0 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PC_DisableADC0FunClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->PCENR, RCU_PCENR_ADC0FEN_Msk);
}

/**
  * @brief  Judge is ADC0 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_PC_IsEnabledADC0FunClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->PCENR, RCU_PCENR_ADC0FEN_Msk, RCU_PCENR_ADC0FEN_Pos);
}

/**
  * @brief  Judge is TMR6 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledTMR6Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk, RCU_APB0ENR_TMR6EN_Pos);
}

/**
  * @brief  TMR8 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableTMR8Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR8EN_Msk);
}

/**
  * @brief  TMR8 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableTMR8Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR8EN_Msk);
}

/**
  * @brief  Judge is TMR8 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledTMR8Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_TMR8EN_Msk, RCU_APB0ENR_TMR8EN_Pos);
}

/**
  * @brief  TMR7 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableTMR7Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR7EN_Msk);
}

/**
  * @brief  TMR7 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableTMR7Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_TMR7EN_Msk);
}

/**
  * @brief  Judge is TMR7 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledTMR7Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_TMR7EN_Msk, RCU_APB0ENR_TMR7EN_Pos);
}

/**
  * @brief  UART2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableUART2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_UART2EN_Msk);
}

/**
  * @brief  UART2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableUART2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_UART2EN_Msk);
}

/**
  * @brief  Judge is UART2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledUART2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_UART2EN_Msk, RCU_APB0ENR_UART2EN_Pos);
}

/**
  * @brief  UART1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableUART1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_UART1EN_Msk);
}

/**
  * @brief  UART1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableUART1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_UART1EN_Msk);
}

/**
  * @brief  Judge is UART1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledUART1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_UART1EN_Msk, RCU_APB0ENR_UART1EN_Pos);
}

/**
  * @brief  UART0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableUART0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_UART0EN_Msk);
}

/**
  * @brief  UART0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableUART0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_UART0EN_Msk);
}

/**
  * @brief  Judge is UART0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledUART0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_UART0EN_Msk, RCU_APB0ENR_UART0EN_Pos);
}

/**
  * @brief  I2C2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableI2C2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_I2C2EN_Msk);
}

/**
  * @brief  I2C2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableI2C2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_I2C2EN_Msk);
}

/**
  * @brief  Judge is I2C2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledI2C2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_I2C2EN_Msk, RCU_APB0ENR_I2C2EN_Pos);
}

/**
  * @brief  I2C1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableI2C1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_I2C1EN_Msk);
}

/**
  * @brief  I2C1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableI2C1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_I2C1EN_Msk);
}

/**
  * @brief  Judge is I2C1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledI2C1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_I2C1EN_Msk, RCU_APB0ENR_I2C1EN_Pos);
}

/**
  * @brief  I2C0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_EnableI2C0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0ENR, RCU_APB0ENR_I2C0EN_Msk);
}

/**
  * @brief  I2C0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_DisableI2C0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0ENR, RCU_APB0ENR_I2C0EN_Msk);
}

/**
  * @brief  Judge is I2C0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsEnabledI2C0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0ENR, RCU_APB0ENR_I2C0EN_Msk, RCU_APB0ENR_I2C0EN_Pos);
}

/**
  * @brief  TMR2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableTMR2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_TMR2EN_Msk);
}

/**
  * @brief  TMR2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableTMR2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_TMR2EN_Msk);
}

/**
  * @brief  Judge is TMR2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledTMR2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_TMR2EN_Msk, RCU_APB1ENR_TMR2EN_Pos);
}

/**
  * @brief  TMR1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableTMR1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_TMR1EN_Msk);
}

/**
  * @brief  TMR1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableTMR1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_TMR1EN_Msk);
}

/**
  * @brief  Judge is TMR1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledTMR1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_TMR1EN_Msk, RCU_APB1ENR_TMR1EN_Pos);
}

/**
  * @brief  TMR0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableTMR0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_TMR0EN_Msk);
}

/**
  * @brief  TMR0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableTMR0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_TMR0EN_Msk);
}

/**
  * @brief  Judge is TMR0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledTMR0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_TMR0EN_Msk, RCU_APB1ENR_TMR0EN_Pos);
}

/**
  * @brief  PDM3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnablePDM3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM3EN_Msk);
}

/**
  * @brief  PDM3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisablePDM3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM3EN_Msk);
}

/**
  * @brief  Judge is PDM3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledPDM3Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_PDM3EN_Msk, RCU_APB1ENR_PDM3EN_Pos);
}

/**
  * @brief  PDM2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnablePDM2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM2EN_Msk);
}

/**
  * @brief  PDM2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisablePDM2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM2EN_Msk);
}

/**
  * @brief  Judge is PDM2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledPDM2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_PDM2EN_Msk, RCU_APB1ENR_PDM2EN_Pos);
}

/**
  * @brief  PDM1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnablePDM1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM1EN_Msk);
}

/**
  * @brief  PDM1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisablePDM1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM1EN_Msk);
}

/**
  * @brief  Judge is PDM1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledPDM1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_PDM1EN_Msk, RCU_APB1ENR_PDM1EN_Pos);
}

/**
  * @brief  PDM0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnablePDM0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM0EN_Msk);
}

/**
  * @brief  PDM0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisablePDM0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_PDM0EN_Msk);
}

/**
  * @brief  Judge is PDM0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledPDM0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_PDM0EN_Msk, RCU_APB1ENR_PDM0EN_Pos);
}

/**
  * @brief  XIF CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableXIFClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_XIFEN_Msk);
}

/**
  * @brief  XIF CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableXIFClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_XIFEN_Msk);
}

/**
  * @brief  Judge is XIF CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledXIFClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_XIFEN_Msk, RCU_APB1ENR_XIFEN_Pos);
}

/**
  * @brief  CAN1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableCAN1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_CAN1EN_Msk);
}

/**
  * @brief  CAN1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableCAN1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_CAN1EN_Msk);
}

/**
  * @brief  Judge is CAN1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledCAN1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_CAN1EN_Msk, RCU_APB1ENR_CAN1EN_Pos);
}

/**
  * @brief  CAN0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableCAN0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_CAN0EN_Msk);
}

/**
  * @brief  CAN0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableCAN0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_CAN0EN_Msk);
}

/**
  * @brief  Judge is CAN0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledCAN0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_CAN0EN_Msk, RCU_APB1ENR_CAN0EN_Pos);
}

/**
  * @brief  SPI1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableSPI1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_SPI1EN_Msk);
}

/**
  * @brief  SPI1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableSPI1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_SPI1EN_Msk);
}

/**
  * @brief  Judge is SPI1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledSPI1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_SPI1EN_Msk, RCU_APB1ENR_SPI1EN_Pos);
}

/**
  * @brief  SPI0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableSPI0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_SPI0EN_Msk);
}

/**
  * @brief  SPI0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableSPI0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_SPI0EN_Msk);
}

/**
  * @brief  Judge is SPI0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledSPI0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_SPI0EN_Msk, RCU_APB1ENR_SPI0EN_Pos);
}

/**
  * @brief  UART4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableUART4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_UART4EN_Msk);
}

/**
  * @brief  UART4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableUART4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_UART4EN_Msk);
}

/**
  * @brief  Judge is UART4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledUART4Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_UART4EN_Msk, RCU_APB1ENR_UART4EN_Pos);
}

/**
  * @brief  UART3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_EnableUART3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1ENR, RCU_APB1ENR_UART3EN_Msk);
}

/**
  * @brief  UART3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_DisableUART3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1ENR, RCU_APB1ENR_UART3EN_Msk);
}

/**
  * @brief  Judge is UART3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsEnabledUART3Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1ENR, RCU_APB1ENR_UART3EN_Msk, RCU_APB1ENR_UART3EN_Pos);
}

/**
  * @brief  QEI2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableQEI2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI2EN_Msk);
}

/**
  * @brief  QEI2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableQEI2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI2EN_Msk);
}

/**
  * @brief  Judge is QEI2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledQEI2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI2EN_Msk, RCU_AHB0ENR_QEI2EN_Pos);
}

/**
  * @brief  QEI1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableQEI1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI1EN_Msk);
}

/**
  * @brief  QEI1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableQEI1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI1EN_Msk);
}

/**
  * @brief  Judge is QEI1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledQEI1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI1EN_Msk, RCU_AHB0ENR_QEI1EN_Pos);
}

/**
  * @brief  QEI0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableQEI0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI0EN_Msk);
}

/**
  * @brief  QEI0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableQEI0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI0EN_Msk);
}

/**
  * @brief  Judge is QEI0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledQEI0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_QEI0EN_Msk, RCU_AHB0ENR_QEI0EN_Pos);
}

/**
  * @brief  TMR4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableTMR4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_TMR4EN_Msk);
}

/**
  * @brief  TMR4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableTMR4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_TMR4EN_Msk);
}

/**
  * @brief  Judge is TMR4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledTMR4Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_TMR4EN_Msk, RCU_AHB0ENR_TMR4EN_Pos);
}

/**
  * @brief  TMR3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableTMR3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_TMR3EN_Msk);
}

/**
  * @brief  TMR3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableTMR3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_TMR3EN_Msk);
}

/**
  * @brief  Judge is TMR3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledTMR3Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_TMR3EN_Msk, RCU_AHB0ENR_TMR3EN_Pos);
}

/**
  * @brief  GPIOF CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableGPIOFClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PFEN_Msk);
}

/**
  * @brief  GPIOF CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableGPIOFClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PFEN_Msk);
}

/**
  * @brief  Judge is GPIOF CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledGPIOFClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_PFEN_Msk, RCU_AHB0ENR_PFEN_Pos);
}

/**
  * @brief  GPIOE CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableGPIOEClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PEEN_Msk);
}

/**
  * @brief  GPIOE CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableGPIOEClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PEEN_Msk);
}

/**
  * @brief  Judge is GPIOE CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledGPIOEClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_PEEN_Msk, RCU_AHB0ENR_PEEN_Pos);
}

/**
  * @brief  GPIOD CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableGPIODClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PDEN_Msk);
}

/**
  * @brief  GPIOD CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableGPIODClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PDEN_Msk);
}

/**
  * @brief  Judge is GPIOD CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledGPIODClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_PDEN_Msk, RCU_AHB0ENR_PDEN_Pos);
}

/**
  * @brief  GPIOC CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableGPIOCClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PCEN_Msk);
}

/**
  * @brief  GPIOC CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableGPIOCClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PCEN_Msk);
}

/**
  * @brief  Judge is GPIOC CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledGPIOCClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_PCEN_Msk, RCU_AHB0ENR_PCEN_Pos);
}

/**
  * @brief  GPIOB CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableGPIOBClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PBEN_Msk);
}

/**
  * @brief  GPIOB CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableGPIOBClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PBEN_Msk);
}

/**
  * @brief  Judge is GPIOB CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledGPIOBClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_PBEN_Msk, RCU_AHB0ENR_PBEN_Pos);
}

/**
  * @brief  GPIOA CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableGPIOAClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PAEN_Msk);
}

/**
  * @brief  GPIOA CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableGPIOAClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_PAEN_Msk);
}

/**
  * @brief  Judge is GPIOA CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledGPIOAClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_PAEN_Msk, RCU_AHB0ENR_PAEN_Pos);
}

/**
  * @brief  EFLASH CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableEFLASHClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_FLSEN_Msk);
}

/**
  * @brief  EFLASH CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableEFLASHClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_FLSEN_Msk);
}

/**
  * @brief  Judge is EFLASH CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledEFLASHClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_FLSEN_Msk, RCU_AHB0ENR_FLSEN_Pos);
}

/**
  * @brief  DMA CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_EnableDMAClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_DMAEN_Msk);
}

/**
  * @brief  DMA CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_DisableDMAClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0ENR, RCU_AHB0ENR_DMAEN_Msk);
}

/**
  * @brief  Judge is DMA CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsEnabledDMAClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0ENR, RCU_AHB0ENR_DMAEN_Msk, RCU_AHB0ENR_DMAEN_Pos);
}

/**
  * @brief  CORDIC CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableCORDICClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_CORDICEN_Msk);
}

/**
  * @brief  CORDIC CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableCORDICClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_CORDICEN_Msk);
}

/**
  * @brief  Judge is CORDIC CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledCORDICClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_CORDICEN_Msk, RCU_AHB1ENR_CORDICEN_Pos);
}

/**
  * @brief  IIR5 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableIIR5Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR5EN_Msk);
}

/**
  * @brief  IIR5 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableIIR5Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR5EN_Msk);
}

/**
  * @brief  Judge is IIR5 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledIIR5Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR5EN_Msk, RCU_AHB1ENR_IIR5EN_Pos);
}

/**
  * @brief  IIR4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableIIR4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR4EN_Msk);
}

/**
  * @brief  IIR4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableIIR4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR4EN_Msk);
}

/**
  * @brief  Judge is IIR4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledIIR4Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR4EN_Msk, RCU_AHB1ENR_IIR4EN_Pos);
}

/**
  * @brief  IIR3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableIIR3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR3EN_Msk);
}

/**
  * @brief  IIR3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableIIR3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR3EN_Msk);
}

/**
  * @brief  Judge is IIR3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledIIR3Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR3EN_Msk, RCU_AHB1ENR_IIR3EN_Pos);
}

/**
  * @brief  IIR2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableIIR2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR2EN_Msk);
}

/**
  * @brief  IIR2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableIIR2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR2EN_Msk);
}

/**
  * @brief  Judge is IIR2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledIIR2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR2EN_Msk, RCU_AHB1ENR_IIR2EN_Pos);
}

/**
  * @brief  IIR1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableIIR1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR1EN_Msk);
}

/**
  * @brief  IIR1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableIIR1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR1EN_Msk);
}

/**
  * @brief  Judge is IIR1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledIIR1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR1EN_Msk, RCU_AHB1ENR_IIR1EN_Pos);
}

/**
  * @brief  IIR0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableIIR0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR0EN_Msk);
}

/**
  * @brief  IIR0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableIIR0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR0EN_Msk);
}

/**
  * @brief  Judge is IIR0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledIIR0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_IIR0EN_Msk, RCU_AHB1ENR_IIR0EN_Pos);
}

/**
  * @brief  HRPWM7 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM7Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM7EN_Msk);
}

/**
  * @brief  HRPWM7 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM7Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM7EN_Msk);
}

/**
  * @brief  Judge is HRPWM7 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM7Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM7EN_Msk, RCU_AHB1ENR_PWM7EN_Pos);
}

/**
  * @brief  HRPWM6 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM6Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM6EN_Msk);
}

/**
  * @brief  HRPWM6 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM6Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM6EN_Msk);
}

/**
  * @brief  Judge is HRPWM6 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM6Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM6EN_Msk, RCU_AHB1ENR_PWM6EN_Pos);
}

/**
  * @brief  HRPWM5 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM5Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM5EN_Msk);
}

/**
  * @brief  HRPWM5 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM5Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM5EN_Msk);
}

/**
  * @brief  Judge is HRPWM5 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM5Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM5EN_Msk, RCU_AHB1ENR_PWM5EN_Pos);
}

/**
  * @brief  HRPWM4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM4EN_Msk);
}

/**
  * @brief  HRPWM4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM4Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM4EN_Msk);
}

/**
  * @brief  Judge is HRPWM4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM4Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM4EN_Msk, RCU_AHB1ENR_PWM4EN_Pos);
}

/**
  * @brief  HRPWM3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM3EN_Msk);
}

/**
  * @brief  HRPWM3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM3EN_Msk);
}

/**
  * @brief  Judge is HRPWM3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM3Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM3EN_Msk, RCU_AHB1ENR_PWM3EN_Pos);
}

/**
  * @brief  HRPWM2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM2EN_Msk);
}

/**
  * @brief  HRPWM2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM2EN_Msk);
}

/**
  * @brief  Judge is HRPWM2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM2EN_Msk, RCU_AHB1ENR_PWM2EN_Pos);
}

/**
  * @brief  HRPWM1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM1EN_Msk);
}

/**
  * @brief  HRPWM1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM1EN_Msk);
}

/**
  * @brief  Judge is HRPWM1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM1EN_Msk, RCU_AHB1ENR_PWM1EN_Pos);
}

/**
  * @brief  HRPWM0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableHRPWM0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM0EN_Msk);
}

/**
  * @brief  HRPWM0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableHRPWM0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM0EN_Msk);
}

/**
  * @brief  Judge is HRPWM0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWM0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_PWM0EN_Msk, RCU_AHB1ENR_PWM0EN_Pos);
}

/**
  * @brief  Judge is HRPWM0/1/2/3/4/5/6/7 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 HRPWM0/1/2/3/4/5/6/7 CLK is Disable
  * @retval 1 HRPWM0/1/2/3/4/5/6/7 CLK is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledHRPWMClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (!!READ_BIT_SHIFT((RCUx)->AHB1ENR, 0x1FE00UL, RCU_AHB1ENR_PWM0EN_Pos));
}

/**
  * @brief  CMP CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableCMPClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_CMPxEN_Msk);
}

/**
  * @brief  CMP CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableCMPClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_CMPxEN_Msk);
}

/**
  * @brief  Judge is CMP CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledCMPClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_CMPxEN_Msk, RCU_AHB1ENR_CMPxEN_Pos);
}

/**
  * @brief  DAC CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableDACClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_DACxEN_Msk);
}

/**
  * @brief  DAC CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableDACClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_DACxEN_Msk);
}

/**
  * @brief  Judge is DAC CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledDACClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_DACxEN_Msk, RCU_AHB1ENR_DACxEN_Pos);
}

/**
  * @brief  ADC3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableADC3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC3EN_Msk);
}

/**
  * @brief  ADC3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableADC3Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC3EN_Msk);
}

/**
  * @brief  Judge is ADC3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledADC3Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC3EN_Msk, RCU_AHB1ENR_ADC3EN_Pos);
}

/**
  * @brief  ADC2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableADC2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC2EN_Msk);
}

/**
  * @brief  ADC2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableADC2Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC2EN_Msk);
}

/**
  * @brief  Judge is ADC2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledADC2Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC2EN_Msk, RCU_AHB1ENR_ADC2EN_Pos);
}

/**
  * @brief  ADC1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableADC1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC1EN_Msk);
}

/**
  * @brief  ADC1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableADC1Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC1EN_Msk);
}

/**
  * @brief  Judge is ADC1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledADC1Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC1EN_Msk, RCU_AHB1ENR_ADC1EN_Pos);
}

/**
  * @brief  ADC0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableADC0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC0EN_Msk);
}

/**
  * @brief  ADC0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableADC0Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC0EN_Msk);
}

/**
  * @brief  Judge is ADC0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledADC0Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_ADC0EN_Msk, RCU_AHB1ENR_ADC0EN_Pos);
}

/**
  * @brief  Judge is ADC0/1/2/3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 ADC0/1/2/3 CLK is Disable
  * @retval 1 ADC0/1/2/3 CLK is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledADCClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (!!READ_BIT_SHIFT((RCUx)->AHB1ENR, 0x78UL, RCU_AHB1ENR_ADC0EN_Pos));
}

/**
  * @brief  USB CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableUSBClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_USBEN_Msk);
}

/**
  * @brief  USB CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableUSBClock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_USBEN_Msk);
}

/**
  * @brief  Judge is USB CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledUSBClock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_USBEN_Msk, RCU_AHB1ENR_USBEN_Pos);
}

/**
  * @brief  TMR10 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableTMR10Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_TMR10EN_Msk);
}

/**
  * @brief  TMR10 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableTMR10Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_TMR10EN_Msk);
}

/**
  * @brief  Judge is TMR10 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledTMR10Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_TMR10EN_Msk, RCU_AHB1ENR_TMR10EN_Pos);
}

/**
  * @brief  TMR9 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_EnableTMR9Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_TMR9EN_Msk);
}

/**
  * @brief  TMR9 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_DisableTMR9Clock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1ENR, RCU_AHB1ENR_TMR9EN_Msk);
}

/**
  * @brief  Judge is TMR9 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsEnabledTMR9Clock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1ENR, RCU_AHB1ENR_TMR9EN_Msk, RCU_AHB1ENR_TMR9EN_Pos);
}

/**
  * @brief  Judge is TMR6 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetTMR6(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk, RCU_APB0RSTR_TMR6RST_Pos);
}

/**
  * @brief  TMR8 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetTMR8(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR8RST_Msk);
}

/**
  * @brief  TMR8 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetTMR8(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR8RST_Msk);
}

/**
  * @brief  Judge is TMR8 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetTMR8(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR8RST_Msk, RCU_APB0RSTR_TMR8RST_Pos);
}

/**
  * @brief  TMR7 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetTMR7(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR7RST_Msk);
}

/**
  * @brief  TMR7 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetTMR7(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR7RST_Msk);
}

/**
  * @brief  Judge is TMR7 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetTMR7(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_TMR7RST_Msk, RCU_APB0RSTR_TMR7RST_Pos);
}

/**
  * @brief  UART2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetUART2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART2RST_Msk);
}

/**
  * @brief  UART2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetUART2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART2RST_Msk);
}

/**
  * @brief  Judge is UART2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetUART2(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART2RST_Msk, RCU_APB0RSTR_UART2RST_Pos);
}

/**
  * @brief  UART1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetUART1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART1RST_Msk);
}

/**
  * @brief  UART1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetUART1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART1RST_Msk);
}

/**
  * @brief  Judge is UART1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetUART1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART1RST_Msk, RCU_APB0RSTR_UART1RST_Pos);
}

/**
  * @brief  UART0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetUART0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART0RST_Msk);
}

/**
  * @brief  UART0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetUART0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART0RST_Msk);
}

/**
  * @brief  Judge is UART0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetUART0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_UART0RST_Msk, RCU_APB0RSTR_UART0RST_Pos);
}

/**
  * @brief  I2C2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetI2C2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C2RST_Msk);
}

/**
  * @brief  I2C2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetI2C2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C2RST_Msk);
}

/**
  * @brief  Judge is I2C2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetI2C2(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C2RST_Msk, RCU_APB0RSTR_I2C2RST_Pos);
}

/**
  * @brief  I2C1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetI2C1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C1RST_Msk);
}

/**
  * @brief  I2C1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetI2C1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C1RST_Msk);
}

/**
  * @brief  Judge is I2C1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetI2C1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C1RST_Msk, RCU_APB0RSTR_I2C1RST_Pos);
}

/**
  * @brief  I2C0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetI2C0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C0RST_Msk);
}

/**
  * @brief  I2C0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetI2C0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C0RST_Msk);
}

/**
  * @brief  Judge is I2C0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetI2C0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB0RSTR, RCU_APB0RSTR_I2C0RST_Msk, RCU_APB0RSTR_I2C0RST_Pos);
}

/**
  * @brief  APB0 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ForceResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->APB0RSTR, 0x0);
}

/**
  * @brief  APB0 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB0_ReleaseResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->APB0RSTR, 0xffffffffUL);
}

/**
  * @brief  Judge is APB0 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB0 Soft Reset all Assert
  * @retval 1 is APB0 Soft Reset all Assert
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsForceResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->APB0RSTR) & 0xffUL) == 0x00);
}

/**
  * @brief  Judge is APB0 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB0 Soft Reset all Release
  * @retval 1 is APB0 Soft Reset all Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB0_IsReleaseResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->APB0RSTR) & 0xffUL) == 0xffUL);
}

/**
  * @brief  TMR2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetTMR2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR2RST_Msk);
}

/**
  * @brief  TMR2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetTMR2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR2RST_Msk);
}

/**
  * @brief  Judge is TMR2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetTMR2(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR2RST_Msk, RCU_APB1RSTR_TMR2RST_Pos);
}

/**
  * @brief  TMR1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetTMR1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR1RST_Msk);
}

/**
  * @brief  TMR1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetTMR1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR1RST_Msk);
}

/**
  * @brief  Judge is TMR1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetTMR1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR1RST_Msk, RCU_APB1RSTR_TMR1RST_Pos);
}

/**
  * @brief  TMR0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetTMR0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR0RST_Msk);
}

/**
  * @brief  TMR0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetTMR0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR0RST_Msk);
}

/**
  * @brief  Judge is TMR0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetTMR0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_TMR0RST_Msk, RCU_APB1RSTR_TMR0RST_Pos);
}

/**
  * @brief  PDM3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetPDM3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM3RST_Msk);
}

/**
  * @brief  PDM3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetPDM3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM3RST_Msk);
}

/**
  * @brief  Judge is PDM3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetPDM3(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM3RST_Msk, RCU_APB1RSTR_PDM3RST_Pos);
}

/**
  * @brief  PDM2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetPDM2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM2RST_Msk);
}

/**
  * @brief  PDM2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetPDM2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM2RST_Msk);
}

/**
  * @brief  Judge is PDM2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetPDM2(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM2RST_Msk, RCU_APB1RSTR_PDM2RST_Pos);
}

/**
  * @brief  PDM1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetPDM1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM1RST_Msk);
}

/**
  * @brief  PDM1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetPDM1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM1RST_Msk);
}

/**
  * @brief  Judge is PDM1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetPDM1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM1RST_Msk, RCU_APB1RSTR_PDM1RST_Pos);
}

/**
  * @brief  PDM0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetPDM0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM0RST_Msk);
}

/**
  * @brief  PDM0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetPDM0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM0RST_Msk);
}

/**
  * @brief  Judge is PDM0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetPDM0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_PDM0RST_Msk, RCU_APB1RSTR_PDM0RST_Pos);
}

/**
  * @brief  XIF Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetXIF(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_XIFRST_Msk);
}

/**
  * @brief  XIF Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetXIF(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_XIFRST_Msk);
}

/**
  * @brief  Judge is XIF Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetXIF(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_XIFRST_Msk, RCU_APB1RSTR_XIFRST_Pos);
}

/**
  * @brief  CAN1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetCAN1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_CAN1RST_Msk);
}

/**
  * @brief  CAN1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetCAN1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_CAN1RST_Msk);
}

/**
  * @brief  Judge is CAN1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetCAN1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_CAN1RST_Msk, RCU_APB1RSTR_CAN1RST_Pos);
}

/**
  * @brief  CAN0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetCAN0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_CAN0RST_Msk);
}

/**
  * @brief  CAN0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetCAN0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_CAN0RST_Msk);
}

/**
  * @brief  Judge is CAN0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetCAN0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_CAN0RST_Msk, RCU_APB1RSTR_CAN0RST_Pos);
}

/**
  * @brief  SPI1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetSPI1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_SPI1RST_Msk);
}

/**
  * @brief  SPI1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetSPI1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_SPI1RST_Msk);
}

/**
  * @brief  Judge is SPI1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetSPI1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_SPI1RST_Msk, RCU_APB1RSTR_SPI1RST_Pos);
}

/**
  * @brief  SPI0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetSPI0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_SPI0RST_Msk);
}

/**
  * @brief  SPI0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetSPI0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_SPI0RST_Msk);
}

/**
  * @brief  Judge is SPI0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetSPI0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_SPI0RST_Msk, RCU_APB1RSTR_SPI0RST_Pos);
}

/**
  * @brief  UART4 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetUART4(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_UART4RST_Msk);
}

/**
  * @brief  UART4 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetUART4(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_UART4RST_Msk);
}

/**
  * @brief  Judge is UART4 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetUART4(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_UART4RST_Msk, RCU_APB1RSTR_UART4RST_Pos);
}

/**
  * @brief  UART3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetUART3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_UART3RST_Msk);
}

/**
  * @brief  UART3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetUART3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->APB1RSTR, RCU_APB1RSTR_UART3RST_Msk);
}

/**
  * @brief  Judge is UART3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetUART3(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->APB1RSTR, RCU_APB1RSTR_UART3RST_Msk, RCU_APB1RSTR_UART3RST_Pos);
}

/**
  * @brief  APB1 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ForceResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->APB1RSTR, 0x0);
}

/**
  * @brief  APB1 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_APB1_ReleaseResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->APB1RSTR, 0xffffffffUL);
}

/**
  * @brief  Judge is APB1 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB1 Soft Reset all Assert
  * @retval 1 is APB1 Soft Reset all Assert
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsForceResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->APB1RSTR) & 0x3fffUL) == 0x00);
}

/**
  * @brief  Judge is APB1 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB1 Soft Reset all Release
  * @retval 1 is APB1 Soft Reset all Release
  */
__STATIC_INLINE uint32_t LL_RCU_APB1_IsReleaseResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->APB1RSTR) & 0x3fffUL) == 0x3fffUL);
}

/**
  * @brief  QEI2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetQEI2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI2RST_Msk);
}

/**
  * @brief  QEI2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetQEI2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI2RST_Msk);
}

/**
  * @brief  Judge is QEI2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetQEI2(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI2RST_Msk, RCU_AHB0RSTR_QEI2RST_Pos);
}

/**
  * @brief  QEI1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetQEI1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI1RST_Msk);
}

/**
  * @brief  QEI1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetQEI1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI1RST_Msk);
}

/**
  * @brief  Judge is QEI1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetQEI1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI1RST_Msk, RCU_AHB0RSTR_QEI1RST_Pos);
}

/**
  * @brief  QEI0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetQEI0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI0RST_Msk);
}

/**
  * @brief  QEI0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetQEI0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI0RST_Msk);
}

/**
  * @brief  Judge is QEI0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetQEI0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_QEI0RST_Msk, RCU_AHB0RSTR_QEI0RST_Pos);
}

/**
  * @brief  TMR4 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetTMR4(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_TMR4RST_Msk);
}

/**
  * @brief  TMR4 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetTMR4(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_TMR4RST_Msk);
}

/**
  * @brief  Judge is TMR4 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetTMR4(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_TMR4RST_Msk, RCU_AHB0RSTR_TMR4RST_Pos);
}

/**
  * @brief  TMR3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetTMR3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_TMR3RST_Msk);
}

/**
  * @brief  TMR3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetTMR3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_TMR3RST_Msk);
}

/**
  * @brief  Judge is TMR3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetTMR3(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_TMR3RST_Msk, RCU_AHB0RSTR_TMR3RST_Pos);
}

/**
  * @brief  GPIOF Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetGPIOF(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PFRST_Msk);
}

/**
  * @brief  GPIOF Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetGPIOF(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PFRST_Msk);
}

/**
  * @brief  Judge is GPIOF Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetGPIOF(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PFRST_Msk, RCU_AHB0RSTR_PFRST_Pos);
}

/**
  * @brief  GPIOE Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetGPIOE(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PERST_Msk);
}

/**
  * @brief  GPIOE Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetGPIOE(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PERST_Msk);
}

/**
  * @brief  Judge is GPIOE Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetGPIOE(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PERST_Msk, RCU_AHB0RSTR_PERST_Pos);
}

/**
  * @brief  GPIOD Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetGPIOD(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PDRST_Msk);
}

/**
  * @brief  GPIOD Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetGPIOD(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PDRST_Msk);
}

/**
  * @brief  Judge is GPIOD Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetGPIOD(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PDRST_Msk, RCU_AHB0RSTR_PDRST_Pos);
}

/**
  * @brief  GPIOC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetGPIOC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PCRST_Msk);
}

/**
  * @brief  GPIOC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetGPIOC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PCRST_Msk);
}

/**
  * @brief  Judge is GPIOC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetGPIOC(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PCRST_Msk, RCU_AHB0RSTR_PCRST_Pos);
}

/**
  * @brief  GPIOB Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetGPIOB(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PBRST_Msk);
}

/**
  * @brief  GPIOB Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetGPIOB(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PBRST_Msk);
}

/**
  * @brief  Judge is GPIOB Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetGPIOB(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PBRST_Msk, RCU_AHB0RSTR_PBRST_Pos);
}

/**
  * @brief  GPIOA Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetGPIOA(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PARST_Msk);
}

/**
  * @brief  GPIOA Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetGPIOA(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PARST_Msk);
}

/**
  * @brief  Judge is GPIOA Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetGPIOA(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_PARST_Msk, RCU_AHB0RSTR_PARST_Pos);
}

/**
  * @brief  EFLASH Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetEFLASH(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_FLSRST_Msk);
}

/**
  * @brief  EFLASH Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetEFLASH(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_FLSRST_Msk);
}

/**
  * @brief  Judge is EFLASH Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetEFLASH(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_FLSRST_Msk, RCU_AHB0RSTR_FLSRST_Pos);
}

/**
  * @brief  DMA Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetDMA(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_DMARST_Msk);
}

/**
  * @brief  DMA Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetDMA(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_DMARST_Msk);
}

/**
  * @brief  Judge is DMA Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetDMA(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB0RSTR, RCU_AHB0RSTR_DMARST_Msk, RCU_AHB0RSTR_DMARST_Pos);
}

/**
  * @brief  AHB0 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ForceResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->AHB0RSTR, 0x0);
}

/**
  * @brief  AHB0 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB0_ReleaseResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->AHB0RSTR, 0xffffffffUL);
}

/**
  * @brief  Judge is AHB0 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB0 Soft Reset all Assert
  * @retval 1 is AHB0 Soft Reset all Assert
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsForceResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->AHB0RSTR) & 0x1fffUL) == 0x00);
}

/**
  * @brief  Judge is AHB0 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB0 Soft Reset all Release
  * @retval 1 is AHB0 Soft Reset all Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB0_IsReleaseResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->AHB0RSTR) & 0x1fffUL) == 0x1fffUL);
}

/**
  * @brief  CORDIC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetCORDIC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_CORDICRST_Msk);
}

/**
  * @brief  CORDIC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetCORDIC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_CORDICRST_Msk);
}

/**
  * @brief  Judge is CORDIC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetCORDIC(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_CORDICRST_Msk, RCU_AHB1RSTR_CORDICRST_Pos);
}

/**
  * @brief  IIR5 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetIIR5(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR5RST_Msk);
}

/**
  * @brief  IIR5 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetIIR5(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR5RST_Msk);
}

/**
  * @brief  Judge is IIR5 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetIIR5(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR5RST_Msk, RCU_AHB1RSTR_IIR5RST_Pos);
}

/**
  * @brief  IIR4 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetIIR4(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR4RST_Msk);
}

/**
  * @brief  IIR4 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetIIR4(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR4RST_Msk);
}

/**
  * @brief  Judge is IIR4 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetIIR4(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR4RST_Msk, RCU_AHB1RSTR_IIR4RST_Pos);
}

/**
  * @brief  IIR3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetIIR3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR3RST_Msk);
}

/**
  * @brief  IIR3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetIIR3(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR3RST_Msk);
}

/**
  * @brief  Judge is IIR3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetIIR3(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR3RST_Msk, RCU_AHB1RSTR_IIR3RST_Pos);
}

/**
  * @brief  IIR2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetIIR2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR2RST_Msk);
}

/**
  * @brief  IIR2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetIIR2(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR2RST_Msk);
}

/**
  * @brief  Judge is IIR2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetIIR2(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR2RST_Msk, RCU_AHB1RSTR_IIR2RST_Pos);
}

/**
  * @brief  IIR1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetIIR1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR1RST_Msk);
}

/**
  * @brief  IIR1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetIIR1(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR1RST_Msk);
}

/**
  * @brief  Judge is IIR1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetIIR1(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR1RST_Msk, RCU_AHB1RSTR_IIR1RST_Pos);
}

/**
  * @brief  IIR0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetIIR0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR0RST_Msk);
}

/**
  * @brief  IIR0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetIIR0(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR0RST_Msk);
}

/**
  * @brief  Judge is IIR0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetIIR0(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_IIR0RST_Msk, RCU_AHB1RSTR_IIR0RST_Pos);
}

/**
  * @brief  HRPWM Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetHRPWM(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_PWMRST_Msk);
}

/**
  * @brief  HRPWM Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetHRPWM(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_PWMRST_Msk);
}

/**
  * @brief  Judge is HRPWM Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetHRPWM(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_PWMRST_Msk, RCU_AHB1RSTR_PWMRST_Pos);
}

/**
  * @brief  CMP Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetCMP(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_CMPRST_Msk);
}

/**
  * @brief  CMP Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetCMP(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_CMPRST_Msk);
}

/**
  * @brief  Judge is CMP Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetCMP(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_CMPRST_Msk, RCU_AHB1RSTR_CMPRST_Pos);
}

/**
  * @brief  DAC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetDAC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_DACRST_Msk);
}

/**
  * @brief  DAC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetDAC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_DACRST_Msk);
}

/**
  * @brief  Judge is DAC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetDAC(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_DACRST_Msk, RCU_AHB1RSTR_DACRST_Pos);
}

/**
  * @brief  ADC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetADC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_ADCRST_Msk);
}

/**
  * @brief  ADC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetADC(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_ADCRST_Msk);
}

/**
  * @brief  Judge is ADC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetADC(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_ADCRST_Msk, RCU_AHB1RSTR_ADCRST_Pos);
}

/**
  * @brief  USB Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetUSB(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_USBRST_Msk);
}

/**
  * @brief  USB Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetUSB(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_USBRST_Msk);
}

/**
  * @brief  Judge is USB Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetUSB(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_USBRST_Msk, RCU_AHB1RSTR_USBRST_Pos);
}

/**
  * @brief  TMR10 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetTMR10(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_TMR10RST_Msk);
}

/**
  * @brief  TMR10 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetTMR10(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_TMR10RST_Msk);
}

/**
  * @brief  Judge is TMR10 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetTMR10(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_TMR10RST_Msk, RCU_AHB1RSTR_TMR10RST_Pos);
}

/**
  * @brief  TMR9 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetTMR9(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_TMR9RST_Msk);
}

/**
  * @brief  TMR9 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetTMR9(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_TMR9RST_Msk);
}

/**
  * @brief  Judge is TMR9 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetTMR9(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->AHB1RSTR, RCU_AHB1RSTR_TMR9RST_Msk, RCU_AHB1RSTR_TMR9RST_Pos);
}

/**
  * @brief  AHB1 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ForceResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->AHB1RSTR, 0x0);
}

/**
  * @brief  AHB1 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_AHB1_ReleaseResetAll(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->AHB1RSTR, 0xffffffffUL);
}

/**
  * @brief  Judge is AHB1 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB1 Soft Reset all Assert
  * @retval 1 is AHB1 Soft Reset all Assert
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsForceResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->AHB1RSTR) & 0x3fffUL) == 0x00);
}

/**
  * @brief  Judge is AHB1 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB1 Soft Reset all Release
  * @retval 1 is AHB1 Soft Reset all Release
  */
__STATIC_INLINE uint32_t LL_RCU_AHB1_IsReleaseResetAll(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return ((READ_REG((RCUx)->AHB1RSTR) & 0x3fffUL) == 0x3fffUL);
}

/**
  * @brief  XOSC DR Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  cur Current
  * @return None
  */
__STATIC_INLINE void LL_RCU_XOSC_SetDR(RCU_TypeDef *RCUx, uint32_t Cur)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->XOSCCR, RCU_XOSCCR_XDR_Msk, (((Cur) & 0x7UL) << RCU_XOSCCR_XDR_Pos));
}

/**
  * @brief  SYSCLK Switch Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_EnableSysclkSwitch(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->CSSCR, RCU_CSSCR_SSE_Msk);
}

/**
  * @brief  SYSCLK Switch Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_DisableSysclkSwitch(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->CSSCR, RCU_CSSCR_SSE_Msk);
}

/**
  * @brief  Judge is XOSC Loss Pending or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't XOSC Loss Pending
  * @retval 1 is XOSC Loss Pending
  */
__STATIC_INLINE uint32_t LL_RCU_IsXOSCLossPnd(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->CSSCR, RCU_CSSCR_LPD_Msk, RCU_CSSCR_LPD_Pos);
}

/**
  * @brief  XOSC Loss NMI Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_XOSC_EnableLossNMI(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->CSSCR, RCU_CSSCR_LPE_Msk);
}

/**
  * @brief  XOSC Loss NMI Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_XOSC_DisableLossNMI(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->CSSCR, RCU_CSSCR_LPE_Msk);
}

/**
  * @brief  XOSC Securce Switch Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_XOSC_EnableSecurceSwitch(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->CSSCR, RCU_CSSCR_SWE_Msk);
}

/**
  * @brief  XOSC Securce Switch Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_XOSC_DisableSecurceSwitch(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->CSSCR, RCU_CSSCR_SWE_Msk);
}

/**
  * @brief  XOSC compare threshold window Set (CSSCR.LMT)
  * @param  __RCU__ Specifies RCU peripheral
  * @param  Lmt Threshold window (0: +-2Cycle, 1: +-4Cycle, 2: +-6Cycle, 3: +-8Cycle)
  * @return None
  */
__STATIC_INLINE void LL_RCU_XOSC_SetLimitWindow(RCU_TypeDef *RCUx, uint32_t Lmt)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->CSSCR, RCU_CSSCR_LMT_Msk, (((Lmt) & 0x3UL) << RCU_CSSCR_LMT_Pos));
}

/**
  * @brief  XOSC compare threshold window Get (CSSCR.LMT)
  * @param  __RCU__ Specifies RCU peripheral
  * @return Threshold window (0: +-2Cycle .. 3: +-8Cycle)
  */
__STATIC_INLINE uint32_t LL_RCU_XOSC_GetLimitWindow(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->CSSCR, RCU_CSSCR_LMT_Msk, RCU_CSSCR_LMT_Pos);
}

/**
  * @brief  XOSC auto switch window Set (CSSCR.WIN)
  * @param  __RCU__ Specifies RCU peripheral
  * @param  Win Auto switch window (0: 3us, 1: 6us, 2: 9us, 3: 12us)
  * @return None
  */
__STATIC_INLINE void LL_RCU_XOSC_SetAutoSwitchWindow(RCU_TypeDef *RCUx, uint32_t Win)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->CSSCR, RCU_CSSCR_WIN_Msk, (((Win) & 0x3UL) << RCU_CSSCR_WIN_Pos));
}

/**
  * @brief  XOSC auto switch window Get (CSSCR.WIN)
  * @param  __RCU__ Specifies RCU peripheral
  * @return Auto switch window (0: 3us .. 3: 12us)
  */
__STATIC_INLINE uint32_t LL_RCU_XOSC_GetAutoSwitchWindow(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->CSSCR, RCU_CSSCR_WIN_Msk, RCU_CSSCR_WIN_Pos);
}

/**
  * @brief  External Clock Input Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_EnableExtClockInput(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->DBGCR, RCU_DBGCR_ECIE_Msk);
}

/**
  * @brief  External Clock Input Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_DisableExtClockInput(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->DBGCR, RCU_DBGCR_ECIE_Msk);
}

/**
  * @brief  Internal Clock Fanout Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_EnableIntClockFanout(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT((RCUx)->DBGCR, RCU_DBGCR_MCOEN_Msk);
}

/**
  * @brief  Internal Clock Fanout Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_DisableIntClockFanout(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT((RCUx)->DBGCR, RCU_DBGCR_MCOEN_Msk);
}

/**
  * @brief  Internal Clock Fanout Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src Internal Clock Fanout Source @ref RCU_IntClkFanoutSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_SetIntClockFanoutSource(RCU_TypeDef *RCUx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG((RCUx)->DBGCR, RCU_DBGCR_MCO_Msk, (((Src) & 0x7UL) << RCU_DBGCR_MCO_Pos));
}

/**
  * @brief  IWDG Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_IWDG_Reset_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_IWRSTE_Msk, RCU_SRSTSR_IWRSTE_Msk);
}

/**
  * @brief  IWDG Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_IWDG_Reset_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_IWRSTE_Msk, 0);
}

/**
  * @brief  WWDG Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_WWDG_Reset_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_WWRSTE_Msk, RCU_SRSTSR_WWRSTE_Msk);
}

/**
  * @brief  WWDG Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_WWDG_Reset_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_WWRSTE_Msk, 0);
}

/**
  * @brief  CPU LockUp Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_CPU_LockUpReset_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_LKRSTE_Msk, RCU_SRSTSR_LKRSTE_Msk);
}

/**
  * @brief  CPU LockUp Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_CPU_LockUpReset_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_LKRSTE_Msk, 0);
}

/**
  * @brief  CPU SystemREQ Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_CPU_SystemReqReset_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_SQRSTE_Msk, RCU_SRSTSR_SQRSTE_Msk);
}

/**
  * @brief  CPU SystemREQ Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_CPU_SystemReqReset_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->SRSTSR, 0x3fUL | RCU_SRSTSR_SQRSTE_Msk, 0);
}

/**
  * @brief  Judge WWDG Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't WWDG Reset
  * @retval 1 Is WWDG Reset
  */
__STATIC_INLINE uint32_t LL_RCU_IsWWDGResetActived(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->SRSR, RCU_SRSR_WWR_Msk, RCU_SRSR_WWR_Pos));
}

/**
  * @brief  Clear WWDG Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearWWDGResetPending(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, RCU_SRSR_WWR_Msk);
}

/**
  * @brief  Judge IWDG Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't IWDG Reset
  * @retval 1 Is IWDG Reset
  */
__STATIC_INLINE uint32_t LL_RCU_IsIWDGResetActived(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->SRSR, RCU_SRSR_IWR_Msk, RCU_SRSR_IWR_Pos));
}

/**
  * @brief  Clear IWDG Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearIWDGResetPending(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, RCU_SRSR_IWR_Msk);
}

/**
  * @brief  Judge CPU LockUp Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't CPU LockUp Reset
  * @retval 1 Is CPU LockUp Reset
  */
__STATIC_INLINE uint32_t LL_RCU_IsCPULockUpResetActived(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->SRSR, RCU_SRSR_LKR_Msk, RCU_SRSR_LKR_Pos));
}

/**
  * @brief  Clear CPU LockUp Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearCPULockUpResetPending(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, RCU_SRSR_LKR_Msk);
}

/**
  * @brief  Judge CPU SystemREQ Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't CPU SystemREQ Reset
  * @retval 1 Is CPU SystemREQ Reset
  */
__STATIC_INLINE uint32_t LL_RCU_IsCPUSystemReqResetActived(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->SRSR, RCU_SRSR_SQR_Msk, RCU_SRSR_SQR_Pos));
}

/**
  * @brief  Clear CPU SystemREQ Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearCPUSystemReqResetPending(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, RCU_SRSR_SQR_Msk);
}

/**
  * @brief  Judge LowPower Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't LowPower Reset
  * @retval 1 Is LowPower Reset
  */
__STATIC_INLINE uint32_t LL_RCU_IsLowPowerResetActived(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->SRSR, RCU_SRSR_LPR_Msk, RCU_SRSR_LPR_Pos));
}

/**
  * @brief  Clear LowPower Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearLowPowerResetPending(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, RCU_SRSR_LPR_Msk);
}

/**
  * @brief  Judge MCLR Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't MCLR Reset
  * @retval 1 Is MCLR Reset
  */
__STATIC_INLINE uint32_t LL_RCU_IsMCLRResetActived(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT_SHIFT((RCUx)->SRSR, RCU_SRSR_MCR_Msk, RCU_SRSR_MCR_Pos));
}

/**
  * @brief  Clear MCLR Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearMCLRResetPending(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, RCU_SRSR_MCR_Msk);
}

/**
  * @brief  Clear Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @param  Mask Reset Source Mask @ref LL_RCU_SRSR_RstSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearResetPending(RCU_TypeDef *RCUx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, (Mask & LL_RCU_SRSR_RST_SRC_FLAG_MSK));
}

/**
  * @brief  Clear All Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_ClearAllResetPending(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->SRSR, LL_RCU_SRSR_RST_SRC_FLAG_MSK);
}



/**
  * @brief  RCU Register Write Unlock
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_RegWrite_Unlock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->KEYR, 0x3fac87e4);
}

/**
  * @brief  RCU Register Write Lock
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_RegWrite_Lock(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    WRITE_REG((RCUx)->KEYR, 0x1);
}

/**
  * @brief  Judge RCU Register is unlock or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 RCU Register is lock
  * @retval 1 RCU Register is unlock
  */
__STATIC_INLINE uint32_t LL_RCU_IsRegWriteUnlock(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT((RCUx)->KEYR, RCU_KEYR_KEY_Msk, RCU_KEYR_KEY_Pos);
}

/**
  * @brief  Get System Clock Source
  * @param  RCUx Specifies RCU peripheral
  * @return System clock source
  */
__STATIC_INLINE uint32_t LL_RCU_GetSysClockSource(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT(RCUx->CCR, RCU_CCR_SCS_Msk, RCU_CCR_SCS_Pos);
}

/**
  * @brief  Enable HSE
  * @param  RCUx Specifies RCU peripheral
  */
__STATIC_INLINE void LL_RCU_HSE_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT(RCUx->XOSCCR, RCU_XOSCCR_XEN_Msk);
}

/**
  * @brief  Disable HSE
  * @param  RCUx Specifies RCU peripheral
  */
__STATIC_INLINE void LL_RCU_HSE_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT(RCUx->XOSCCR, RCU_XOSCCR_XEN_Msk);
}

/**
  * @brief  Check whether HSE is enabled
  * @param  RCUx Specifies RCU peripheral
  * @retval 0 HSE is disabled
  * @retval 1 HSE is enabled
  */
__STATIC_INLINE uint32_t LL_RCU_HSE_IsEnabled(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT(RCUx->XOSCCR, RCU_XOSCCR_XEN_Msk) != 0UL) ? 1UL : 0UL;
}

/**
  * @brief  Enable HSI
  * @param  RCUx Specifies RCU peripheral
  */
__STATIC_INLINE void LL_RCU_HSI_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT(RCUx->XOSCCR, RCU_XOSCCR_HEN_Msk);
}

/**
  * @brief  Disable HSI
  * @param  RCUx Specifies RCU peripheral
  */
__STATIC_INLINE void LL_RCU_HSI_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT(RCUx->XOSCCR, RCU_XOSCCR_HEN_Msk);
}

/**
  * @brief  Check whether HSI is enabled
  * @param  RCUx Specifies RCU peripheral
  * @retval 0 HSI is disabled
  * @retval 1 HSI is enabled
  */
__STATIC_INLINE uint32_t LL_RCU_HSI_IsEnabled(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (READ_BIT(RCUx->XOSCCR, RCU_XOSCCR_HEN_Msk) != 0UL) ? 1UL : 0UL;
}

/**
  * @brief  Get PLL0 Reference Clock Source
  * @param  RCUx Specifies RCU peripheral
  * @return PLL0 reference clock source
  */
__STATIC_INLINE uint32_t LL_RCU_PLL0_GetRefClockSource(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT(RCUx->PLL0CR, RCU_PLL0CR_RCS_Msk, RCU_PLL0CR_RCS_Pos);
}

/**
  * @brief  Check if PLL0 is locked
  * @param  RCUx Specifies RCU peripheral
  * @return Lock status (1=Locked, 0=Not Locked)
  */
__STATIC_INLINE uint32_t LL_RCU_PLL0_IsReady(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return READ_BIT_SHIFT(RCUx->PLL0CR, RCU_PLL0CR_LKF_Msk, RCU_PLL0CR_LKF_Pos);
}

/**
  * @brief  Set PLL0 Reference Clock Source
  * @param  RCUx Specifies RCU peripheral
  * @param  src Reference clock source
  */
__STATIC_INLINE void LL_RCU_PLL0_SetRefClock(RCU_TypeDef *RCUx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->PLL0CR, RCU_PLL0CR_RCS_Msk, Src << RCU_PLL0CR_RCS_Pos);
}

/**
  * @brief  Set PLL0 Division Integer Value
  * @param  RCUx Specifies RCU peripheral
  * @param  value Integer division value
  */
__STATIC_INLINE void LL_RCU_PLL0_SetDividerInteger(RCU_TypeDef *RCUx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->PLL0FR, RCU_PLL0FR_INT_Msk, ((Value & 0x3fffUL) << RCU_PLL0FR_INT_Pos));
}

/**
  * @brief  Set PLL0 Division Fraction Value
  * @param  RCUx Specifies RCU peripheral
  * @param  value Fraction division value
  */
__STATIC_INLINE void LL_RCU_PLL0_SetDividerFraction(RCU_TypeDef *RCUx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->PLL0FR, RCU_PLL0FR_FRAC_Msk, ((Value & 0xffffUL) << RCU_PLL0FR_FRAC_Pos));
}

/**
  * @brief  Get PLL0 Division Integer Value
  * @param  RCUx Specifies RCU peripheral
  * @return Integer division value
  */
__STATIC_INLINE uint32_t LL_RCU_PLL0_GetDividerInteger(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (uint32_t)(READ_BIT_SHIFT(RCUx->PLL0FR, RCU_PLL0FR_INT_Msk, RCU_PLL0FR_INT_Pos));
}

/**
  * @brief  Get PLL0 Division Fraction Value
  * @param  RCUx Specifies RCU peripheral
  * @return Fraction division value
  */
__STATIC_INLINE uint32_t LL_RCU_PLL0_GetDividerFraction(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (uint32_t)(READ_BIT_SHIFT(RCUx->PLL0FR, RCU_PLL0FR_FRAC_Msk, RCU_PLL0FR_FRAC_Pos));
}

/**
  * @brief  Check whether PLL0 is enabled
  * @param  RCUx Specifies RCU peripheral
  * @retval 0 PLL0 is disabled
  * @retval 1 PLL0 is enabled
  */
__STATIC_INLINE uint32_t LL_RCU_PLL0_IsEnabled(const RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    return (uint32_t)(READ_BIT(RCUx->PLL0CR, RCU_PLL0CR_EN_Msk) == RCU_PLL0CR_EN_Msk);
}

/**
  * @brief  Enable PLL0
  * @param  RCUx Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_Enable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    SET_BIT(RCUx->PLL0CR, RCU_PLL0CR_EN_Msk);
}

/**
  * @brief  Disable PLL0
  * @param  RCUx Specifies RCU peripheral
  * @return None
  */
__STATIC_INLINE void LL_RCU_PLL0_Disable(RCU_TypeDef *RCUx)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    CLEAR_BIT(RCUx->PLL0CR, RCU_PLL0CR_EN_Msk);
}

/**
  * @brief  Set AHB Clock Divider
  * @param  RCUx Specifies RCU peripheral
  * @param  div AHB clock divider value (1..32)
  */
__STATIC_INLINE void LL_RCU_SetAHBPrescaler(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->CCR, RCU_CCR_HPSC_Msk, (((Div)-1) & 0x3fUL) << RCU_CCR_HPSC_Pos);
}

/**
  * @brief  Set APB0 Clock Divider
  * @param  RCUx Specifies RCU peripheral
  * @param  div APB0 clock divider value (1..16)
  */
__STATIC_INLINE void LL_RCU_SetAPB0Prescaler(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->CCR, RCU_CCR_P0PSC_Msk, (((Div)-1) & 0xfUL) << RCU_CCR_P0PSC_Pos);
}

/**
  * @brief  Set APB1 Clock Divider
  * @param  RCUx Specifies RCU peripheral
  * @param  div APB1 clock divider value (1..16)
  */
__STATIC_INLINE void LL_RCU_SetAPB1Prescaler(RCU_TypeDef *RCUx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_RCU_ALL_INSTANCE(RCUx));

    MODIFY_REG(RCUx->CCR, RCU_CCR_P1PSC_Msk, (((Div)-1) & 0xfUL) << RCU_CCR_P1PSC_Pos);
}

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* RCU_LL_Exported_Functions */

/**
  * @}
  */ /* RCU_LL */

#endif /* RCU */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_RCU_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
