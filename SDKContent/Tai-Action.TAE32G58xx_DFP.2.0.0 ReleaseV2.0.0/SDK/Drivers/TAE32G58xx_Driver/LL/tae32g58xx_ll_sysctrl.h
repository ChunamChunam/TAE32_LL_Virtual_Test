/**
  ******************************************************************************
  * @file    tae32g58xx_ll_sysctrl.h
  * @author  Tai-Action SD Team
  * @brief   Header file for SYSCTRL LL module
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
#ifndef _TAE32G58XX_LL_SYSCTRL_H_
#define _TAE32G58XX_LL_SYSCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(SYSCTRL)

/** @defgroup SYSCTRL_LL SYSCTRL LL
  * @brief    SYSCTRL LL Module Driver 
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Constants SYSCTRL LL Exported Constants
  * @brief    SYSCTRL LL Exported Constants
  * @{
  */

/** @defgroup SYSCTRL_LL_EC_Keys LL SYSCTRL Keys
  * @brief LL SYSCTRL Keys 
  * @{
  */

/**
  * @brief SYSCTRL systerm register unlock KEY1
  */
#define LL_SYSCTRL_SYSTEM_REG_UNLOCK_KEY1                  (0x87E4UL)

/**
  * @brief SYSCTRL special register unlock KEY1
  */
#define LL_SYSCTRL_SPECIAL_REG_UNLOCK_KEY1                 (0x8A3DUL)

/**
  * @brief SYSCTRL special register unlock KEY2
  */
#define LL_SYSCTRL_SPECIAL_REG_UNLOCK_KEY2                 (0x19ECUL)
/**
  * @}
  */ /* SYSCTRL_LL_EC_Keys */

/** @defgroup SYSCTRL_LL_EC_Configuration LL SYSCTRL Configuration
  * @brief LL SYSCTRL Configuration 
  * @{
  */

/**
  * @brief SYSCTRL PECR Interrput Enable All Mask Definition
  */
#define LL_SYSCTRL_PECR_IT_EN_MSK                           ((SYSCTRL_PECR_VDDOCIE_Msk        | SYSCTRL_PECR_AVCCLVIE_Msk       | \
                                                              SYSCTRL_PECR_VCCLVIE_Msk        | SYSCTRL_PECR_VDDLVIE_Msk        ))

/**
  * @brief SYSCTRL Interrupt Enable Mask Definition
  */
#define LL_SYSCTRL_PECR_ITEnMskTypeDef                      uint32_t

#define LL_SYSCTRL_PECR_VDDOCIE              (SYSCTRL_PECR_VDDOCIE_Msk)           /*!< VDDOCIE Mask             */
#define LL_SYSCTRL_PECR_AVCCLVIE             (SYSCTRL_PECR_AVCCLVIE_Msk)          /*!< AVCCLVIE Mask            */
#define LL_SYSCTRL_PECR_VCCLVIE              (SYSCTRL_PECR_VCCLVIE_Msk)           /*!< VCCLVIE Mask             */
#define LL_SYSCTRL_PECR_VDDLVIE              (SYSCTRL_PECR_VDDLVIE_Msk)           /*!< VDDLVIE Mask             */

/**
  * @brief SYSCTRL PSR Interrupt Pending Mask Definition
  */
#define LL_SYSCTRL_PSR_IT_FLAG_MSK                          ((SYSCTRL_PSR_VDDOCS_Msk          | SYSCTRL_PSR_AVCCLVS_Msk         | \
                                                              SYSCTRL_PSR_VCCLVS_Msk          | SYSCTRL_PSR_VDDLVS_Msk          ))

/**
  * @brief SYSCTRL Interrupt Pending Mask Definition
  */
#define LL_SYSCTRL_PSR_ITPendingMskTypeDef                  uint32_t

#define LL_SYSCTRL_PSR_VDDOCS                (SYSCTRL_PSR_VDDOCS_Msk)             /*!< VDDOCS Mask              */
#define LL_SYSCTRL_PSR_AVCCLVS               (SYSCTRL_PSR_AVCCLVS_Msk)            /*!< AVCCLVS Mask             */
#define LL_SYSCTRL_PSR_VCCLVS                (SYSCTRL_PSR_VCCLVS_Msk)             /*!< VCCLVS Mask              */
#define LL_SYSCTRL_PSR_VDDLVS                (SYSCTRL_PSR_VDDLVS_Msk)             /*!< VDDLVS Mask              */


/**
  * @brief SYSCTRL ADC Buffer Source Definition
  */
#define LL_SYSCTRL_ADCBufSrcTypeDef                   LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_ADC_BUF_SRC_AVSS                   (0UL)                /*!< ADC Buffer Source AVSS                           */
#define LL_SYSCTRL_ADC_BUF_SRC_TSENSOR                (1UL)                /*!< ADC Buffer Source Temp SENSOR                    */
#define LL_SYSCTRL_ADC_BUF_SRC_VBGR                   (2UL)                /*!< ADC Buffer Source VBGR                           */
#define LL_SYSCTRL_ADC_BUF_SRC_VR1P2                  (3UL)                /*!< ADC Buffer Source VR1P2                          */
#define LL_SYSCTRL_ADC_BUF_SRC_VREFN                  (4UL)                /*!< ADC Buffer Source VREFN                          */
#define LL_SYSCTRL_ADC_BUF_SRC_VREF                   (5UL)                /*!< ADC Buffer Source VREF                           */
#define LL_SYSCTRL_ADC_BUF_SRC_AVCC                   (6UL)                /*!< ADC Buffer Source AVCC                           */
#define LL_SYSCTRL_ADC_BUF_SRC_AVDD                   (7UL)                /*!< ADC Buffer Source AVDD                           */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC0_OUT               (8UL)                /*!< ADC Buffer Source DAC0 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC1_OUT               (9UL)                /*!< ADC Buffer Source DAC1 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC2_OUT               (10UL)               /*!< ADC Buffer Source DAC2 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC3_OUT               (11UL)               /*!< ADC Buffer Source DAC3 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC4_OUT               (12UL)               /*!< ADC Buffer Source DAC4 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC5_OUT               (13UL)               /*!< ADC Buffer Source DAC5 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC6_OUT               (14UL)               /*!< ADC Buffer Source DAC6 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC7_OUT               (15UL)               /*!< ADC Buffer Source DAC7 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_DAC8_OUT               (16UL)               /*!< ADC Buffer Source DAC8 OUT                       */
#define LL_SYSCTRL_ADC_BUF_SRC_TOUT                   (17UL)               /*!< ADC Buffer Source TOUT                           */
#define LL_SYSCTRL_ADC_BUF_SRC_PLL0_TOUT              (18UL)               /*!< ADC Buffer Source PLL0 TOUT                      */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV19                  (19UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_ADC0_IN16              (20UL)               /*!< ADC Buffer Source ADC0 IN16                      */
#define LL_SYSCTRL_ADC_BUF_SRC_ADC1_IN16              (21UL)               /*!< ADC Buffer Source ADC1 IN16                      */
#define LL_SYSCTRL_ADC_BUF_SRC_ADC2_IN16              (22UL)               /*!< ADC Buffer Source ADC2 IN16                      */
#define LL_SYSCTRL_ADC_BUF_SRC_ADC3_IN16              (23UL)               /*!< ADC Buffer Source ADC3 IN16                      */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV24                  (24UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV25                  (25UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV26                  (26UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV27                  (27UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV28                  (28UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV29                  (29UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV30                  (30UL)               /*!< ADC Buffer Source Reserved                       */
#define LL_SYSCTRL_ADC_BUF_SRC_RSV31                  (31UL)               /*!< ADC Buffer Source Reserved                       */

#define IS_LL_SYSCTRL_ADC_BUF_SRC(__VAL__)            (((__VAL__) >= LL_SYSCTRL_ADC_BUF_SRC_AVSS) && ((__VAL__) < LL_SYSCTRL_ADC_BUF_SRC_RSV19) || \
                                                       ((__VAL__) > LL_SYSCTRL_ADC_BUF_SRC_RSV19) && ((__VAL__) < LL_SYSCTRL_ADC_BUF_SRC_RSV24) )

/**
  * @brief SYSCTRL VDD Voltage Definition
  */
#define LL_SYSCTRL_VDDVolTypeDef                      LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_VDD_VOL_0V88                       (0UL)                /*!< VDD Voltage 0.88V                                */
#define LL_SYSCTRL_VDD_VOL_0V92                       (1UL)                /*!< VDD Voltage 0.92V                                */
#define LL_SYSCTRL_VDD_VOL_0V96                       (2UL)                /*!< VDD Voltage 0.96V                                */
#define LL_SYSCTRL_VDD_VOL_1V                         (3UL)                /*!< VDD Voltage 1V                                   */
#define LL_SYSCTRL_VDD_VOL_1V04                       (4UL)                /*!< VDD Voltage 1.04V                                */
#define LL_SYSCTRL_VDD_VOL_1V08                       (5UL)                /*!< VDD Voltage 1.08V                                */
#define LL_SYSCTRL_VDD_VOL_1V12                       (6UL)                /*!< VDD Voltage 1.12V                                */
#define LL_SYSCTRL_VDD_VOL_1V16                       (7UL)                /*!< VDD Voltage 1.16V                                */
#define LL_SYSCTRL_VDD_VOL_1V2                        (8UL)                /*!< VDD Voltage 1.20V                                */
#define LL_SYSCTRL_VDD_VOL_1V24                       (9UL)                /*!< VDD Voltage 1.24V                                */
#define LL_SYSCTRL_VDD_VOL_1V28                       (10UL)               /*!< VDD Voltage 1.28V                                */
#define LL_SYSCTRL_VDD_VOL_1V32                       (11UL)               /*!< VDD Voltage 1.32V                                */
#define LL_SYSCTRL_VDD_VOL_1V36                       (12UL)               /*!< VDD Voltage 1.36V                                */
#define LL_SYSCTRL_VDD_VOL_1V4                        (13UL)               /*!< VDD Voltage 1.40V                                */
#define LL_SYSCTRL_VDD_VOL_1V44                       (14UL)               /*!< VDD Voltage 1.44V                                */
#define LL_SYSCTRL_VDD_VOL_1V48                       (15UL)               /*!< VDD Voltage 1.48V                                */

#define IS_LL_SYSCTRL_VDD_VOL(__VAL__)                (((__VAL__) == LL_SYSCTRL_VDD_VOL_0V88) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_0V92) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_0V96) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V)   || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V04) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V08) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V12) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V16) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V2)  || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V24) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V28) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V32) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V36) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V4)  || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V44) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_VOL_1V48) )

/**
  * @brief SYSCTRL AVDD Voltage Definition
  */
#define LL_SYSCTRL_AVDDVolTypeDef                     LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_AVDD_VOL_1V                        (0UL)                /*!< AVDD Voltage 1V                                  */
#define LL_SYSCTRL_AVDD_VOL_1V1                       (1UL)                /*!< AVDD Voltage 1.1V                                */
#define LL_SYSCTRL_AVDD_VOL_1V2                       (2UL)                /*!< AVDD Voltage 1.2V                                */
#define LL_SYSCTRL_AVDD_VOL_1V3                       (3UL)                /*!< AVDD Voltage 1.3V                                */

#define IS_LL_SYSCTRL_AVDD_VOL(__VAL__)               (((__VAL__) == LL_SYSCTRL_AVDD_VOL_1V)  || \
                                                       ((__VAL__) == LL_SYSCTRL_AVDD_VOL_1V1) || \
                                                       ((__VAL__) == LL_SYSCTRL_AVDD_VOL_1V2) || \
                                                       ((__VAL__) == LL_SYSCTRL_AVDD_VOL_1V3) )

/**
  * @brief SYSCTRL VDD OverCurrent Threshold Definition
  */
#define LL_SYSCTRL_VDDOverCurThresTypeDef             LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_VDD_OVER_CUR_THRES_150mA           (0UL)                /*!< VDD OverCurrent Threshold 150mA                  */
#define LL_SYSCTRL_VDD_OVER_CUR_THRES_175mA           (1UL)                /*!< VDD OverCurrent Threshold 175mA                  */
#define LL_SYSCTRL_VDD_OVER_CUR_THRES_200mA           (2UL)                /*!< VDD OverCurrent Threshold 200mA                  */
#define LL_SYSCTRL_VDD_OVER_CUR_THRES_225mA           (3UL)                /*!< VDD OverCurrent Threshold 225mA                  */

#define IS_LL_SYSCTRL_VDD_OVER_CUR_THRES(__VAL__)     (((__VAL__) == LL_SYSCTRL_VDD_OVER_CUR_THRES_150mA) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_OVER_CUR_THRES_175mA) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_OVER_CUR_THRES_200mA) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_OVER_CUR_THRES_225mA) )

/**
  * @brief SYSCTRL AVCC LowVoltage Threshold Definition
  */
#define LL_SYSCTRL_AVCCLowVolThresTypeDef             LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V55            (0UL)                /*!< AVCC LowVoltage Threshold 2.55V                  */
#define LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V7             (1UL)                /*!< AVCC LowVoltage Threshold 2.7V                   */
#define LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V85            (2UL)                /*!< AVCC LowVoltage Threshold 2.85V                  */
#define LL_SYSCTRL_AVCC_LOW_VOL_THRES_3V              (3UL)                /*!< AVCC LowVoltage Threshold 3V                     */

#define IS_LL_SYSCTRL_AVCC_LOW_VOL_THRES(__VAL__)     (((__VAL__) == LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V55) || \
                                                       ((__VAL__) == LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V7)  || \
                                                       ((__VAL__) == LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V85) || \
                                                       ((__VAL__) == LL_SYSCTRL_AVCC_LOW_VOL_THRES_3V)   )

/**
  * @brief SYSCTRL VDD LowVoltage Threshold Definition
  */
#define LL_SYSCTRL_VDDLowVolThresTypeDef              LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_VDD_LOW_VOL_THRES_0V75             (0UL)                /*!< VDD LowVoltage Threshold 0.75V                   */
#define LL_SYSCTRL_VDD_LOW_VOL_THRES_0V8              (1UL)                /*!< VDD LowVoltage Threshold 0.8V                    */
#define LL_SYSCTRL_VDD_LOW_VOL_THRES_0V85             (2UL)                /*!< VDD LowVoltage Threshold 0.85V                   */
#define LL_SYSCTRL_VDD_LOW_VOL_THRES_0V9              (3UL)                /*!< VDD LowVoltage Threshold 0.9V                    */
#define LL_SYSCTRL_VDD_LOW_VOL_THRES_0V95             (4UL)                /*!< VDD LowVoltage Threshold 0.95V                   */
#define LL_SYSCTRL_VDD_LOW_VOL_THRES_1V               (5UL)                /*!< VDD LowVoltage Threshold 1.0V                    */
#define LL_SYSCTRL_VDD_LOW_VOL_THRES_1V05             (6UL)                /*!< VDD LowVoltage Threshold 1.05V                   */
#define LL_SYSCTRL_VDD_LOW_VOL_THRES_1V1              (7UL)                /*!< VDD LowVoltage Threshold 1.1V                    */

#define IS_LL_SYSCTRL_VDD_LOW_VOL_THRES(__VAL__)      (((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_0V75) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_0V8)  || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_0V85) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_0V9)  || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_0V95) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_1V)   || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_1V05) || \
                                                       ((__VAL__) == LL_SYSCTRL_VDD_LOW_VOL_THRES_1V1)  )

/**
  * @brief SYSCTRL VREFBUF Output Voltage Definition
  */
#define LL_SYSCTRL_VREFBUFVolTypeDef                  LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_VREFBUF_VOL_2V9                    (0UL)                /*!< VREFBUF Output Voltage 2.9V                      */
#define LL_SYSCTRL_VREFBUF_VOL_2V5                    (1UL)                /*!< VREFBUF Output Voltage 2.5V                      */

#define IS_LL_SYSCTRL_VREFBUF_VOL(__VAL__)            (((__VAL__) == LL_SYSCTRL_VREFBUF_VOL_2V9) || \
                                                       ((__VAL__) == LL_SYSCTRL_VREFBUF_VOL_2V5) )

/**
  * @brief Flash Double Bank Mapping Definition
  */
#define LL_SYSCTRL_FlashBankMappingTypeDef            LL_RSV_DATA_TYPE    

#define LL_SYSCTRL_FLASH_BANK_MAPPING_0               (0UL)                /*!< Flash Bank Mapping type 0                        */
#define LL_SYSCTRL_FLASH_BANK_MAPPING_1               (1UL)                /*!< Flash Bank Mapping type 1                        */

#define IS_LL_SYSCTRL_FLASH_BANK_MAPPING(__VAL__)     (((__VAL__) == LL_SYSCTRL_FLASH_BANK_MAPPING_0) || \
                                                       ((__VAL__) == LL_SYSCTRL_FLASH_BANK_MAPPING_1) )

/**
  * @}
  */ /* SYSCTRL_LL_EC_Configuration */

/**
  * @}
  */ /* SYSCTRL_LL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Macros SYSCTRL LL Exported Macros
  * @brief    SYSCTRL LL Exported Macros
  * @{
  */

/**
  * @brief Convert a DMA HS interrupt flag number to its corresponding bit mask.
  */ 
#define LL_SYSCTRL_DRCR_NUM_TO_MASK(__NUM__)          (((uint32_t)__NUM__ >= POSITION_VAL(SYSCTRL_DMARCR_DRCR_Msk)) ? \
                                                        ((BIT(((uint32_t)__NUM__) % 32UL)) & SYSCTRL_DMARCR_DRCR_Msk) : 0UL)
/**
  * @}
  */ /* SYSCTRL_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Functions SYSCTRL LL Exported Functions
  * @brief    SYSCTRL LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_SYSCTRL_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_SYSCTRL_ASSERT_INLINE_PARAM == 1)
extern void LL_SYSCTRL_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_SYSCTRL_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_SYSCTRL_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_SYSCTRL_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup SYSCTRL_LL_EF_Configuration LL SYSCTRL Configuration
  * @brief    LL SYSCTRL Configuration
  * @{
  */

/**
  * @brief  HRPWM Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_HRPWM(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_PWMDEN_Msk);
}

/**
  * @brief  HRPWM Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_HRPWM(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_PWMDEN_Msk);
}

/**
  * @brief  Judge is HRPWM Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 HRPWM Debug is Disable
  * @retval 1 HRPWM Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_HRPWM(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_PWMDEN_Msk, SYSCTRL_SYSDCR_PWMDEN_Pos));
}

/**
  * @brief  WWDG Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_WWDG(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_WWDGDEN_Msk);
}

/**
  * @brief  WWDG Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_WWDG(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_WWDGDEN_Msk);
}

/**
  * @brief  Judge is WWDG Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 WWDG Debug is Disable
  * @retval 1 WWDG Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_WWDG(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_WWDGDEN_Msk, SYSCTRL_SYSDCR_WWDGDEN_Pos));
}

/**
  * @brief  IWDG Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_IWDG(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_IWDGDEN_Msk);
}

/**
  * @brief  IWDG Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_IWDG(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_IWDGDEN_Msk);
}

/**
  * @brief  Judge is IWDG Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 IWDG Debug is Disable
  * @retval 1 IWDG Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_IWDG(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_IWDGDEN_Msk, SYSCTRL_SYSDCR_IWDGDEN_Pos));
}

/**
  * @brief  TMR0 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR0(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR0DEN_Msk);
}

/**
  * @brief  TMR0 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR0(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR0DEN_Msk);
}

/**
  * @brief  Judge is TMR0 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR0 Debug is Disable
  * @retval 1 TMR0 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR0(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR0DEN_Msk, SYSCTRL_SYSDCR_TMR0DEN_Pos));
}

/**
  * @brief  TMR1 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR1(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR1DEN_Msk);
}

/**
  * @brief  TMR1 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR1(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR1DEN_Msk);
}

/**
  * @brief  Judge is TMR1 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR1 Debug is Disable
  * @retval 1 TMR1 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR1(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR1DEN_Msk, SYSCTRL_SYSDCR_TMR1DEN_Pos));
}

/**
  * @brief  TMR2 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR2(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR2DEN_Msk);
}

/**
  * @brief  TMR2 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR2(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR2DEN_Msk);
}

/**
  * @brief  Judge is TMR2 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR2 Debug is Disable
  * @retval 1 TMR2 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR2(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR2DEN_Msk, SYSCTRL_SYSDCR_TMR2DEN_Pos));
}

/**
  * @brief  TMR3 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR3(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR3DEN_Msk);
}

/**
  * @brief  TMR3 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR3(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR3DEN_Msk);
}

/**
  * @brief  Judge is TMR3 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR3 Debug is Disable
  * @retval 1 TMR3 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR3(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR3DEN_Msk, SYSCTRL_SYSDCR_TMR3DEN_Pos));
}

/**
  * @brief  TMR4 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR4(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR4DEN_Msk);
}

/**
  * @brief  TMR4 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR4(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR4DEN_Msk);
}

/**
  * @brief  Judge is TMR4 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR4 Debug is Disable
  * @retval 1 TMR4 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR4(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR4DEN_Msk, SYSCTRL_SYSDCR_TMR4DEN_Pos));
}

/**
  * @brief  TMR7 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR7(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR7DEN_Msk);
}

/**
  * @brief  TMR7 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR7(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR7DEN_Msk);
}

/**
  * @brief  Judge is TMR7 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR7 Debug is Disable
  * @retval 1 TMR7 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR7(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR7DEN_Msk, SYSCTRL_SYSDCR_TMR7DEN_Pos));
}

/**
  * @brief  TMR8 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR8(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR8DEN_Msk);
}

/**
  * @brief  TMR8 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR8(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR8DEN_Msk);
}

/**
  * @brief  Judge is TMR8 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR8 Debug is Disable
  * @retval 1 TMR8 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR8(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR8DEN_Msk, SYSCTRL_SYSDCR_TMR8DEN_Pos));
}

/**
  * @brief  TMR9 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR9(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR9DEN_Msk);
}

/**
  * @brief  TMR9 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR9(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR9DEN_Msk);
}

/**
  * @brief  Judge is TMR9 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR9 Debug is Disable
  * @retval 1 TMR9 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR9(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR9DEN_Msk, SYSCTRL_SYSDCR_TMR9DEN_Pos));
}

/**
  * @brief  TMR10 Debug Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableDebug_TMR10(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR10DEN_Msk);
}

/**
  * @brief  TMR10 Debug Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableDebug_TMR10(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR10DEN_Msk);
}

/**
  * @brief  Judge is TMR10 Debug Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 TMR10 Debug is Disable
  * @retval 1 TMR10 Debug is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledDebug_TMR10(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));
    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSDCR, SYSCTRL_SYSDCR_TMR10DEN_Msk, SYSCTRL_SYSDCR_TMR10DEN_Pos));
}

/**
  * @brief  DMA Request Control Set
  * @note   The LSB is Request_0 and MSB is Request_31
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Pos DMA Request Control Bit Shift
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_SetDMARequestControl(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Pos)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->DMARCR, (0x1UL << (Pos & 0x1fUL)) & SYSCTRL_DMARCR_DRCR_Msk);
}

/**
  * @brief  DMA Request Config Set
  * @note   The LSB is Request_0 and MSB is Request_31
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Mask DMA Request Control Bit Mask
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_SetDMARequestConfig(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->DMARCR, (Mask) & SYSCTRL_DMARCR_DRCR_Msk);
}

/**
  * @brief  DMA Request Control Reset
  * @note   The LSB is Request_0 and MSB is Request_31
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Pos DMA Request Control Bit Shift
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_ResetDMARequestControl(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Pos)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->DMARCR, (0x1UL << (Pos & 0x1fUL)) & SYSCTRL_DMARCR_DRCR_Msk);
}

/**
  * @brief  DMA Request Config Reset
  * @note   The LSB is Request_0 and MSB is Request_31
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Mask DMA Request Control Bit Mask
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_ResetDMARequestConfig(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->DMARCR, (Mask) & SYSCTRL_DMARCR_DRCR_Msk);
}

/**
  * @brief  DMA Request Config Get
  * @note   For the sequence of register data bit, LSB is bit19
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return DMA Request Config 
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetDMARequestControl(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_REG(SYSCTRLx->DMARCR));
}

/**
  * @brief  FLASH Double Bank Mapping Set
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Map Bank Mapping @ref LL_SYSCTRL_FlashBankMappingTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_SetEFlashBankMapping(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Map)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_FBM_Msk, ((Map) & 0x01) << SYSCTRL_SYSCR_FBM_Pos);
}

/**
  * @brief  FLASH Double Bank Mapping Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return Bank Mapping @ref LL_SYSCTRL_FlashBankMappingTypeDef
  * 
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetEFlashBankMapping(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_FBM_Msk, SYSCTRL_SYSCR_FBM_Pos));
}

/**
  * @brief  QEI2 Fault Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableQEI2Fault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI2FE_Msk);
}

/**
  * @brief  QEI2 Fault Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableQEI2Fault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI2FE_Msk);
}

/**
  * @brief  Judge is QEI2 Fault Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsQEI2FaultEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI2FE_Msk, SYSCTRL_SYSCR_QEI2FE_Pos));
}

/**
  * @brief  QEI1 Fault Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableQEI1Fault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI1FE_Msk);
}

/**
  * @brief  QEI1 Fault Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableQEI1Fault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI1FE_Msk);
}

/**
  * @brief  Judge is QEI1 Fault Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsQEI1FaultEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI1FE_Msk, SYSCTRL_SYSCR_QEI1FE_Pos));
}

/**
  * @brief  QEI0 Fault Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableQEI0Fault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI0FE_Msk);
}

/**
  * @brief  QEI0 Fault Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableQEI0Fault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI0FE_Msk);
}

/**
  * @brief  Judge is QEI0 Fault Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsQEI0FaultEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_QEI0FE_Msk, SYSCTRL_SYSCR_QEI0FE_Pos));
}

/**
  * @brief  XOSC Loss Fault Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableXOSCLossFault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_OSCFE_Msk);
}

/**
  * @brief  XOSC Loss Fault Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableXOSCLossFault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_OSCFE_Msk);
}

/**
  * @brief  Judge is XOSC Loss Fault Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsXOSCLossFaultEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_OSCFE_Msk, SYSCTRL_SYSCR_OSCFE_Pos));
}

/**
  * @brief  CPU Lockup Fault Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableCPULockupFault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_LKFE_Msk);
}

/**
  * @brief  CPU Lockup Fault Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableCPULockupFault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_LKFE_Msk);
}

/**
  * @brief  Judge is CPU Lockup Fault Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsCPULockupFaultEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_LKFE_Msk, SYSCTRL_SYSCR_LKFE_Pos));
}

/**
  * @brief  FLASH nBits ECC Fault Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableNBitECCFault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_ECCFE_Msk);
}

/**
  * @brief  FLASH nBits ECC Fault Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableNBitECCFault(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_ECCFE_Msk);
}

/**
  * @brief  Judge is CPU Lockup Fault Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsNBitECCFaultEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSCR, SYSCTRL_SYSCR_ECCFE_Msk, SYSCTRL_SYSCR_ECCFE_Pos));
}

/**
  * @brief  ADC Buffer Source Selection
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Src ADC Buffer Source @ref LL_SYSCTRL_ADCBufSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_SetADCBufferSource(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFSRC_Msk, (((Src) & SYSCTRL_SYSATR_ABFSRC_Val) << SYSCTRL_SYSATR_ABFSRC_Pos));
}

/**
  * @brief  ADC Buffer Source Selection Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return ADC Buffer Source @ref LL_SYSCTRL_ADCBufSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetADCBufferSource(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFSRC_Msk, SYSCTRL_SYSATR_ABFSRC_Pos));
}

/**
  * @brief  ADC Buffer Bypass Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableADCBufferBypass(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFBYP_Msk);
}

/**
  * @brief  ADC Buffer Bypass Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableADCBufferBypass(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFBYP_Msk);
}

/**
  * @brief  Judge is ADC Buffer Bypass Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 ADC Buffer Bypass is Disable
  * @retval 1 ADC Buffer Bypass is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsADCBufferBypassEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFBYP_Msk, SYSCTRL_SYSATR_ABFBYP_Pos));
}

/**
  * @brief  ADC Buffer Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableADCBuffer(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFEN_Msk);
}

/**
  * @brief  ADC Buffer Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableADCBuffer(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFEN_Msk);
}

/**
  * @brief  Judge is ADC Buffer Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 ADC Buffer is Disable
  * @retval 1 ADC Buffer is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsADCBufferEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->SYSATR, SYSCTRL_SYSATR_ABFEN_Msk, SYSCTRL_SYSATR_ABFEN_Pos));
}

/**
  * @brief  SYSCTRL System Analog Config Set
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSystemRegister/LL_SYSCTRL_LockSystemRegister 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Val System Analog Config
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_SetSystemAnalogConfig(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    WRITE_REG(SYSCTRLx->SYSATR, Val);
}

/**
  * @brief  SYSCTRL System Analog Config Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return System Analog Config
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetSystemAnalogConfig(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_REG(SYSCTRLx->SYSATR));
}

/**
  * @brief  AVDD Drop Down Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVDD_EnableDropDown(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDDRD_Msk);
}

/**
  * @brief  AVDD Drop Down Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVDD_DisableDropDown(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDDRD_Msk);
}

/**
  * @brief  Judge is AVDD Drop Down Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 AVDD Drop Down is Disable
  * @retval 1 AVDD Drop Down is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVDD_IsDropDownEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDDRD_Msk, SYSCTRL_PWRCR_AVDDDRD_Pos));
}

/**
  * @brief  VDD Voltage Set
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Vol VDD Voltage @ref LL_SYSCTRL_VDDVolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_SetVoltage(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Vol)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_VDDSET_Msk, (((Vol) & SYSCTRL_PWRCR_VDDSET_Val) << SYSCTRL_PWRCR_VDDSET_Pos));
}

/**
  * @brief  VDD Voltage Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return VDD Voltage @ref LL_SYSCTRL_VDDVolTypeDef
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_GetVoltage(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_VDDSET_Msk, SYSCTRL_PWRCR_VDDSET_Pos));
}

/**
  * @brief  AVDD Voltage Set
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Vol AVDD Voltage @ref LL_SYSCTRL_AVDDVolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVDD_SetVoltage(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Vol)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDSET_Msk, (((Vol) & SYSCTRL_PWRCR_AVDDSET_Val) << SYSCTRL_PWRCR_AVDDSET_Pos));
}

/**
  * @brief  AVDD Voltage Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return AVDD Voltage @ref LL_SYSCTRL_AVDDVolTypeDef
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVDD_GetVoltage(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDSET_Msk, SYSCTRL_PWRCR_AVDDSET_Pos));
}

/**
  * @brief  AVDD Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVDD_Enable(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDEN_Msk);
}

/**
  * @brief  AVDD Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVDD_Disable(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDEN_Msk);
}

/**
  * @brief  Judge is AVDD Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 AVDD is Disable
  * @retval 1 AVDD is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVDD_IsEnabled(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_AVDDEN_Msk, SYSCTRL_PWRCR_AVDDEN_Pos));
}

/**
  * @brief  Temperature Sensor Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableTemperatureSensor(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_TSE_Msk);
}

/**
  * @brief  Temperature Sensor Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableTemperatureSensor(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_TSE_Msk);
}

/**
  * @brief  Judge is Temperature Sensor Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 Temperature Sensor is Disable
  * @retval 1 Temperature Sensor is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsTemperatureSensorEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PWRCR, SYSCTRL_PWRCR_TSE_Msk, SYSCTRL_PWRCR_TSE_Pos));
}

/**
  * @brief  VDD Over Current Threshold Set
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Thres VDD Over Current Threshold @ref LL_SYSCTRL_VDDOverCurThresTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_SetOverCurrentThreshold(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Thres)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDOCL_Msk, (((Thres) & SYSCTRL_PLCR_VDDOCL_Val) << SYSCTRL_PLCR_VDDOCL_Pos));
}

/**
  * @brief  VDD Over Current Threshold Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return VDD Over Current Threshold @ref LL_SYSCTRL_VDDOverCurThresTypeDef
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_GetOverCurrentThreshold(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDOCL_Msk, SYSCTRL_PLCR_VDDOCL_Pos));
}

/**
  * @brief  AVCC Low Voltage Threshold Set
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Thres AVCC Low Voltage Threshold @ref LL_SYSCTRL_AVCCLowVolThresTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVCC_SetLowVoltageThreshold(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Thres)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->PLCR, SYSCTRL_PLCR_AVCCLVL_Msk, (((Thres) & SYSCTRL_PLCR_AVCCLVL_Val) << SYSCTRL_PLCR_AVCCLVL_Pos));
}

/**
  * @brief  AVCC Low Voltage Threshold Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return AVCC Low Voltage Threshold @ref LL_SYSCTRL_AVCCLowVolThresTypeDef
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVCC_GetLowVoltageThreshold(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PLCR, SYSCTRL_PLCR_AVCCLVL_Msk, SYSCTRL_PLCR_AVCCLVL_Pos));
}

/**
  * @brief  VDD Low Voltage Threshold Set
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Thres VDD Low Voltage Threshold @ref LL_SYSCTRL_VDDLowVolThresTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_SetLowVoltageThreshold(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Thres)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDLVS_Msk, (((Thres) & SYSCTRL_PLCR_VDDLVS_Val) << SYSCTRL_PLCR_VDDLVS_Pos));
}

/**
  * @brief  VDD Low Voltage Threshold Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return VDD Low Voltage Threshold @ref LL_SYSCTRL_VDDLowVolThresTypeDef
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_GetLowVoltageThreshold(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDLVS_Msk, SYSCTRL_PLCR_VDDLVS_Pos));
}

/**
  * @brief  VDD Over Current Detect Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_EnableOverCurrentDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDOCE_Msk);
}

/**
  * @brief  VDD Over Current Detect Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_DisableOverCurrentDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDOCE_Msk);
}

/**
  * @brief   Judgs is VDD Over Current Detect Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Over Current Detect is Disable
  * @retval 1 VDD Over Current Detect is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsOverCurrentDetectEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDOCE_Msk, SYSCTRL_PLCR_VDDOCE_Pos));
}

/**
  * @brief  AVCC Low Voltage Detect Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVCC_EnableLowVoltageDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_AVCCLVE_Msk);
}

/**
  * @brief  AVCC Low Voltage Detect Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVCC_DisableLowVoltageDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_AVCCLVE_Msk);
}

/**
  * @brief   Judgs is AVCC Low Voltage Detect Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 AVCC Low Voltage Detect is Disable
  * @retval 1 AVCC Low Voltage Detect is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVCC_IsLowVoltageDetectEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PLCR, SYSCTRL_PLCR_AVCCLVE_Msk, SYSCTRL_PLCR_AVCCLVE_Pos));
}

/**
  * @brief  VCC Low Voltage Detect Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VCC_EnableLowVoltageDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VCCLVE_Msk);
}

/**
  * @brief  VCC Low Voltage Detect Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VCC_DisableLowVoltageDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VCCLVE_Msk);
}

/**
  * @brief   Judgs is VCC Low Voltage Detect Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VCC Low Voltage Detect is Disable
  * @retval 1 VCC Low Voltage Detect is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VCC_IsLowVoltageDetectEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VCCLVE_Msk, SYSCTRL_PLCR_VCCLVE_Pos));
}

/**
  * @brief  VDD Low Voltage Detect Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_EnableLowVoltageDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDLVE_Msk);
}

/**
  * @brief  VDD Low Voltage Detect Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_DisableLowVoltageDetect(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDLVE_Msk);
}

/**
  * @brief   Judgs is VDD Low Voltage Detect Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Low Voltage Detect is Disable
  * @retval 1 VDD Low Voltage Detect is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsLowVoltageDetectEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PLCR, SYSCTRL_PLCR_VDDLVE_Msk, SYSCTRL_PLCR_VDDLVE_Pos));
}

/**
  * @brief  VDD Over Current Braking Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_EnableOverCurrentBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCBE_Msk);
}

/**
  * @brief  VDD Over Current Braking Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_DisableOverCurrentBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCBE_Msk);
}

/**
  * @brief  Judge is VDD Over Current Braking Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Over Current Braking is Disable
  * @retval 1 VDD Over Current Braking is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsOverCurrentBrakeEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));
    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCBE_Msk, SYSCTRL_PECR_VDDOCBE_Pos));
}

/**
  * @brief  AVCC Low Voltage Braking Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVCC_EnableLowVoltageBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVBE_Msk);
}

/**
  * @brief  AVCC Low Voltage Braking Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVCC_DisableLowVoltageBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVBE_Msk);
}

/**
  * @brief  Judge is AVCC Low Voltage Braking Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 AVCC Low Voltage Braking is Disable
  * @retval 1 AVCC Low Voltage Braking is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVCC_IsLowVoltageBrakeEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVBE_Msk, SYSCTRL_PECR_AVCCLVBE_Pos));
}

/**
  * @brief  VCC Low Voltage Braking Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VCC_EnableLowVoltageBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVBE_Msk);
}

/**
  * @brief  VCC Low Voltage Braking Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VCC_DisableLowVoltageBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVBE_Msk);
}

/**
  * @brief  Judge is VCC Low Voltage Braking Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VCC Low Voltage Braking is Disable
  * @retval 1 VCC Low Voltage Braking is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VCC_IsLowVoltageBrakeEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVBE_Msk, SYSCTRL_PECR_VCCLVBE_Pos));
}

/**
  * @brief  VDD Low Voltage Braking Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_EnableLowVoltageBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVBE_Msk);
}

/**
  * @brief  VDD Low Voltage Braking Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_DisableLowVoltageBrake(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVBE_Msk);
}

/**
  * @brief  Judge is VDD Low Voltage Braking Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Low Voltage Braking is Disable
  * @retval 1 VDD Low Voltage Braking is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsLowVoltageBrakeEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVBE_Msk, SYSCTRL_PECR_VDDLVBE_Pos));
}

/**
  * @brief  VDD Over Current Reset Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_EnableOverCurrentReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCRE_Msk);
}

/**
  * @brief  VDD Over Current Reset Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_DisableOverCurrentReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCRE_Msk);
}

/**
  * @brief  Judge is VDD Over Current Reset Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Over Current Reset is Disable
  * @retval 1 VDD Over Current Reset is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsOverCurrentResetEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCRE_Msk, SYSCTRL_PECR_VDDOCRE_Pos));
}

/**
  * @brief  AVCC Low Voltage Reset Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVCC_EnableLowVoltageReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVRE_Msk);
}

/**
  * @brief  AVCC Low Voltage Reset Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_AVCC_DisableLowVoltageReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVRE_Msk);
}

/**
  * @brief  Judge is AVCC Low Voltage Reset Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 AVCC Low Voltage Reset is Disable
  * @retval 1 AVCC Low Voltage Reset is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVCC_IsLowVoltageResetEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));
    
    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVRE_Msk, SYSCTRL_PECR_AVCCLVRE_Pos));
}

/**
  * @brief  VCC Low Voltage Reset Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VCC_EnableLowVoltageReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVRE_Msk);
}

/**
  * @brief  VCC Low Voltage Reset Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VCC_DisableLowVoltageReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVRE_Msk);
}

/**
  * @brief  Judge is VCC Low Voltage Reset Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VCC Low Voltage Reset is Disable
  * @retval 1 VCC Low Voltage Reset is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VCC_IsLowVoltageResetEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVRE_Msk, SYSCTRL_PECR_VCCLVRE_Pos));
}

/**
  * @brief  VDD Low Voltage Reset Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_EnableLowVoltageReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVRE_Msk);
}

/**
  * @brief  VDD Low Voltage Reset Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VDD_DisableLowVoltageReset(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVRE_Msk);
}

/**
  * @brief  Judge is VDD Low Voltage Reset Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Low Voltage Reset is Disable
  * @retval 1 VDD Low Voltage Reset is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsLowVoltageResetEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));
    
    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVRE_Msk, SYSCTRL_PECR_VDDLVRE_Pos));
}

/**
  * @brief  VDD Over Current Interrupt Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableIT_VDDOCIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCIE_Msk);
}

/**
  * @brief  VDD Over Current Interrupt Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableIT_VDDOCIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCIE_Msk);
}

/**
  * @brief  Judge is VDD Over Current Interrupt Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Over Current Interrupt is Disable
  * @retval 1 VDD Over Current Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledIT_VDDOCIE(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDOCIE_Msk, SYSCTRL_PECR_VDDOCIE_Pos));
}

/**
  * @brief  AVCC Low Voltage Interrupt Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableIT_AVCCLVIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVIE_Msk);
}

/**
  * @brief  AVCC Low Voltage Interrupt Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableIT_AVCCLVIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVIE_Msk);
}

/**
  * @brief  Judge is AVCC Low Voltage Interrupt Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 AVCC Low Voltage Interrupt is Disable
  * @retval 1 AVCC Low Voltage Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledIT_AVCCLVIE(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_AVCCLVIE_Msk, SYSCTRL_PECR_AVCCLVIE_Pos));
}

/**
  * @brief  VCC Low Voltage Interrupt Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableIT_VCCLVIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVIE_Msk);
}

/**
  * @brief  VCC Low Voltage Interrupt Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableIT_VCCLVIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVIE_Msk);
}

/**
  * @brief  Judge is VCC Low Voltage Interrupt Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VCC Low Voltage Interrupt is Disable
  * @retval 1 VCC Low Voltage Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledIT_VCCLVIE(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VCCLVIE_Msk, SYSCTRL_PECR_VCCLVIE_Pos));
}

/**
  * @brief  VDD Low Voltage Interrupt Enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableIT_VDDLVIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVIE_Msk);
}

/**
  * @brief  VDD Low Voltage Interrupt Disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableIT_VDDLVIE(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVIE_Msk);
}

/**
  * @brief  Judge is VDD Low Voltage Interrupt Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD Low Voltage Interrupt is Disable
  * @retval 1 VDD Low Voltage Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledIT_VDDLVIE(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));
    
    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PECR, SYSCTRL_PECR_VDDLVIE_Msk, SYSCTRL_PECR_VDDLVIE_Pos));
}

/**
  * @brief  SYSCTRL Interrupt All Enable Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return Interrupt Enable Bit
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetAllEnabledIT(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)((READ_REG(SYSCTRLx->PECR)) & LL_SYSCTRL_PECR_IT_EN_MSK);
}

/**
  * @brief  SYSCTRL Interrupt All Pending Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return Interrupt Pending Bit
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetAllITPending(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)((READ_REG(SYSCTRLx->PSR)) & LL_SYSCTRL_PSR_IT_FLAG_MSK);
}

/**
  * @brief  Judge is VDD Over Current or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD isn't Over Current
  * @retval 1 VDD is Over Current
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsOverCurrentActived(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PSR, SYSCTRL_PSR_VDDOCS_Msk, SYSCTRL_PSR_VDDOCS_Pos));
}

/**
  * @brief  Judge is AVCC Low Voltage or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 AVCC isn't Low Voltage
  * @retval 1 AVCC is Low Voltage
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_AVCC_IsLowVoltageActived(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PSR, SYSCTRL_PSR_AVCCLVS_Msk, SYSCTRL_PSR_AVCCLVS_Pos));
}

/**
  * @brief  Judge is VCC Low Voltage or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VCC isn't Low Voltage
  * @retval 1 VCC is Low Voltage
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VCC_IsLowVoltageActived(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PSR, SYSCTRL_PSR_VCCLVS_Msk, SYSCTRL_PSR_VCCLVS_Pos));
}

/**
  * @brief  Judge is VDD Low Voltage or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VDD isn't Low Voltage
  * @retval 1 VDD is Low Voltage
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VDD_IsLowVoltageActived(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->PSR, SYSCTRL_PSR_VDDLVS_Msk, SYSCTRL_PSR_VDDLVS_Pos));
}

/**
  * @brief  SYSCTRL Chip ID Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval Chip ID - 16bit
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetChipID(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->CIDR, SYSCTRL_CIDR_CID_Msk, SYSCTRL_CIDR_CID_Pos));
}

/**
  * @brief  SYSCTRL Chip DCN Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval Chip DCN - 8bit
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetChipDCN(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->CIDR, SYSCTRL_CIDR_DCN_Msk, SYSCTRL_CIDR_DCN_Pos));
}

/**
  * @brief  SYSCTRL System Register Write Unlock
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_UnlockSystemRegister(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    WRITE_REG(SYSCTRLx->KEYR, LL_SYSCTRL_SYSTEM_REG_UNLOCK_KEY1);
    (void)READ_REG(SYSCTRLx->KEYR);
}

/**
  * @brief  SYSCTRL System Register Write Lock
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_LockSystemRegister(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    WRITE_REG(SYSCTRLx->KEYR, SYSCTRL_KEYR_KST0_Msk);
}

/**
  * @brief  Judge is System Register Unlock or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 System Register is Lock
  * @retval 1 System Register is Unlock
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsSystemRegisterUnlock(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));
    return (uint32_t)((READ_BIT(SYSCTRLx->KEYR, SYSCTRL_KEYR_KST0_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  SYSCTRL Special Register Write Unlock
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_UnlockSpecialRegister(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    WRITE_REG(SYSCTRLx->KEYR, LL_SYSCTRL_SPECIAL_REG_UNLOCK_KEY1);
    (void)READ_REG(SYSCTRLx->KEYR);
    WRITE_REG(SYSCTRLx->KEYR, LL_SYSCTRL_SPECIAL_REG_UNLOCK_KEY2); 
    (void)READ_REG(SYSCTRLx->KEYR);
}

/**
  * @brief  SYSCTRL Special Register Write Lock
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_LockSpecialRegister(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    WRITE_REG(SYSCTRLx->KEYR, SYSCTRL_KEYR_KST1_Msk);
}

/**
  * @brief  Judge is Special Register Unlock or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 Special Register is Lock
  * @retval 1 Special Register is Unlock
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsSpecialRegisterUnlock(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)((READ_BIT(SYSCTRLx->KEYR, SYSCTRL_KEYR_KST1_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  SYSCTRL UID0 Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval UID0
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetUID0(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_REG(SYSCTRLx->UID0));
}

/**
  * @brief  SYSCTRL UID1 Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval UID1
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetUID1(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_REG(SYSCTRLx->UID1));
}

/**
  * @brief  SYSCTRL UID2 Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval UID2
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetUID2(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_REG(SYSCTRLx->UID2));
}

/**
  * @brief  SYSCTRL UID3 Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval UID3
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetUID3(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_REG(SYSCTRLx->UID3));
}

/**
  * @brief  SYSCTRL EFLASH Size Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval EFLASH Size in KByte unit
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetEFlashSize(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->UID3, 0xffff0000UL, 16));
}

/**
  * @brief  SYSCTRL VREFBUF Output Voltage Status Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VREFBUF Output is building
  * @retval 1 VREFBUF Output is done
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VREFBUF_IsOutputVoltageBuilt(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFRDY_Msk, SYSCTRL_ATCR_VBFRDY_Pos));
}

/**
  * @brief  SYSCTRL internal BGR voltage Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return Internal BGR voltage
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetInternalBGRVoltage(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_BGV_Msk, SYSCTRL_ATCR_BGV_Pos));
}

/**
  * @brief  SYSCTRL VREFBUF Current Limiting Enable
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSpecialRegister/LL_SYSCTRL_LockSpecialRegister 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VREFBUF_EnableCurrentLimiting(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFCL_Msk);
}

/**
  * @brief  SYSCTRL VREFBUF Current Limiting Disable
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSpecialRegister/LL_SYSCTRL_LockSpecialRegister 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VREFBUF_DisableCurrentLimiting(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFCL_Msk);
}

/**
  * @brief  Judge is SYSCTRL VREFBUF Current Limiting Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 Current Limiting is disable
  * @retval 1 Current Limiting is enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VREFBUF_IsCurrentLimitingEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFCL_Msk, SYSCTRL_ATCR_VBFCL_Pos));
}

/**
  * @brief  SYSCTRL VREFBUF Trim Set
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return VREFBUF Trim
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VREFBUF_GetTrim(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFTRIM_Msk, SYSCTRL_ATCR_VBFTRIM_Pos));
}

/**
  * @brief  SYSCTRL VREFBUF Output Voltage Set
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSpecialRegister/LL_SYSCTRL_LockSpecialRegister 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Vol VREFBUF Output Voltage @ref LL_SYSCTRL_VREFBUFVolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VREFBUF_SetOutputVoltage(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Vol)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    MODIFY_REG(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFSEL_Msk, ((Vol) & SYSCTRL_ATCR_VBFSEL_Val) << SYSCTRL_ATCR_VBFSEL_Pos);
}

/**
  * @brief  SYSCTRL VREFBUF Output Voltage Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return VREFBUF Output Voltage @ref LL_SYSCTRL_VREFBUFVolTypeDef
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VREFBUF_GetOutputVoltage(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFSEL_Msk, SYSCTRL_ATCR_VBFSEL_Pos));
}

/**
  * @brief  SYSCTRL VREFBUF Enable
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSpecialRegister/LL_SYSCTRL_LockSpecialRegister 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VREFBUF_Enable(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFEN_Msk);
}

/**
  * @brief  SYSCTRL VREFBUF Disable
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSpecialRegister/LL_SYSCTRL_LockSpecialRegister 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_VREFBUF_Disable(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFEN_Msk);
}

/**
  * @brief  Judge is SYSCTRL VREFBUF Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 VREFBUF is Disable
  * @retval 1 VREFBUF is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_VREFBUF_IsEnabled(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_VBFEN_Msk, SYSCTRL_ATCR_VBFEN_Pos));
}

/**
  * @brief  SYSCTRL REF Reference Current Calibration Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return REF Reference Current
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetReferenceCurrent(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_REFITRIM_Msk, SYSCTRL_ATCR_REFITRIM_Pos));
}

/**
  * @brief  SYSCTRL REF Reference Voltage Calibration Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return REF Reference Voltage
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetReferenceVoltage(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->ATCR, SYSCTRL_ATCR_REFVTRIM_Msk, SYSCTRL_ATCR_REFVTRIM_Pos));
}

/**
  * @brief  SYSCTRL Analog Trim Config Set
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSpecialRegister/LL_SYSCTRL_LockSpecialRegister 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Val Analog Trim Config
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_SetAnalogTrimConfig(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    WRITE_REG(SYSCTRLx->ATCR, Val);
}

/**
  * @brief  SYSCTRL Analog Trim Config Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return Analog Trim Config
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_GetAnalogTrimConfig(SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_REG(SYSCTRLx->ATCR));
}


/**
  * @brief  SYSCTRL RC8M Real Value Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC8M Real Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC8M_GetRealFrequency(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR2, SYSCTRL_FCR2_RC8M_Msk, SYSCTRL_FCR2_RC8M_Pos));
}

/**
  * @brief  Judge is SYSCTRL ADC Conversion Phase Clock Enable or not
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @retval 0 ADC Conversion Phase Clock isn't Enable
  * @retval 1 ADC Conversion Phase Clock is Enable
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsADCConversionPhaseClockEnable(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR2, SYSCTRL_FCR2_ADCPVEN_Msk, SYSCTRL_FCR2_ADCPVEN_Pos));
}

/**
  * @brief  SYSCTRL RC8M PLL0CLK Output 180MHz Band Value Get
  * @note   This band value is only used for typical scene which PLL0 analog output 360M
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC8M PLL0 Band Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC8M_GetBandForPLL0CLK180MHz(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR2, SYSCTRL_FCR2_PLL0BANDx_Msk, SYSCTRL_FCR2_PLL0BANDx_Pos));
}

/**
  * @brief  SYSCTRL RC8M PLL0CLK Output 200MHz Band Value Get
  * @note   This band value is only used for typical scene which PLL0 analog output 400M
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC8M PLL0 Band Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC8M_GetBandForPLL0CLK200MHz(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR2, SYSCTRL_FCR2_PLL0BANDy_Msk, SYSCTRL_FCR2_PLL0BANDy_Pos));
}

/**
  * @brief  SYSCTRL RC8M PLL0CLK Output 200MHz INT Value Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC8M PLL0 INT Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC8M_GetINTForPLL0CLK200MHz(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR3, SYSCTRL_FCR3_PLL0INTy_Msk, SYSCTRL_FCR3_PLL0INTy_Pos));
}
/**
  * @brief  SYSCTRL RC8M PLL0CLK Output 200MHz FRAC Value Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC8M PLL0 FRAC Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC8M_GetFRACForPLL0CLK200MHz(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR3, SYSCTRL_FCR3_PLL0FRACy_Msk, SYSCTRL_FCR3_PLL0FRACy_Pos));
}

/**
  * @brief  SYSCTRL RC8M PLL0CLK Output 180MHz INT Value Get 
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC8M PLL0 INT Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC8M_GetINTForPLL0CLK180MHz(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR4, SYSCTRL_FCR4_PLL0INTx_Msk, SYSCTRL_FCR4_PLL0INTx_Pos));
}
/**
  * @brief  SYSCTRL RC8M PLL0CLK Output 180MHz FRAC Value Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC8M PLL0 FRAC Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC8M_GetFRACForPLL0CLK180MHz(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR4, SYSCTRL_FCR4_PLL0FRACx_Msk, SYSCTRL_FCR4_PLL0FRACx_Pos));
}

/**
  * @brief  SYSCTRL RC32K Real Value Get
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @return RC32K Real Value
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_RC32K_GetRealFrequency(const SYSCTRL_TypeDef *SYSCTRLx)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    return (uint32_t)(READ_BIT_SHIFT(SYSCTRLx->FCR5, SYSCTRL_FCR5_RC32K_Msk, SYSCTRL_FCR5_RC32K_Pos));
}
/**
  * @}
  */ /* SYSCTRL_LL_EF_Configuration */


/** @defgroup SYSCTRL_LL_EF_Information LL SYSCTRL Information
  * @brief    LL SYSCTRL Information
  * @{
  */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the PLL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_HSI_GetValue(void)
{
    uint32_t hsi_value = LL_SYSCTRL_RC8M_GetRealFrequency(SYSCTRL);
    return (uint32_t)(hsi_value == 0xffffffUL ? 8000000UL : hsi_value);
}

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  *        Defines the value of the Internal Low Speed oscillator in Hz.
  * @note  The real value may vary depending on the variations in voltage and temperature.
  */ 
__STATIC_INLINE uint32_t LL_SYSCTRL_LSI_GetValue(void)
{
    uint32_t lsi_value = LL_SYSCTRL_RC32K_GetRealFrequency(SYSCTRL);
    return (uint32_t)(lsi_value == 0xffffUL ? 32000UL : lsi_value);
}
/**
  * @}
  */ /* SYSCTRL_LL_EF_Information */


/** @defgroup SYSCTRL_LL_EF_IT_Management LL SYSCTRL Interrupt Management
  * @brief LL SYSCTRL Interrupt Management
  * @{
  */

/**
  * @brief  SYSCTRL Interrupt enable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Mask Mask to enable @ref LL_SYSCTRL_PECR_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_EnableIT(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    SET_BIT(SYSCTRLx->PECR, Mask);
}

/**
  * @brief  SYSCTRL Interrupt disable
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Mask Mask to disable @ref LL_SYSCTRL_PECR_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_DisableIT(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    CLEAR_BIT(SYSCTRLx->PECR, Mask);
}

/**
  * @brief  Check if SYSCTRL Interrupt is enabled or disabled
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Mask Mask to check @ref LL_SYSCTRL_PECR_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsEnabledIT(const SYSCTRL_TypeDef *SYSCTRLx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(SYSCTRLx->PECR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Mask Mask to check @ref LL_SYSCTRL_PSR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_SYSCTRL_ClearFlag(SYSCTRL_TypeDef *SYSCTRLx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_SYSCTRL_ALL_INSTANCE(SYSCTRLx));

    WRITE_REG(SYSCTRLx->PSR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  SYSCTRLx Specifies SYSCTRL peripheral
  * @param  Mask Mask to check @ref LL_SYSCTRL_PSR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCTRL_IsActiveFlag(const SYSCTRL_TypeDef *SYSCTRLx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(SYSCTRLx->PSR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @}
  */ /* SYSCTRL_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* SYSCTRL_LL_Exported_Functions */

#endif /* SYSCTRL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_SYSCTRL_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

