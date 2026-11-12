/**
  ******************************************************************************
  * @file    tae32g58xx_ll_adc.h
  * @author  Tai-Action SD Team
  * @brief   Header file for ADC LL module
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
#ifndef _TAE32G58XX_LL_ADC_H_
#define _TAE32G58XX_LL_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(ADC0) || defined(ADC1) || defined(ADC2) || defined(ADC3)

/** @defgroup ADC_LL ADC LL
  * @brief    ADC LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Constants ADC LL Exported Constants
  * @brief    ADC LL Exported Constants
  * @{
  */

/** @defgroup ADC_LL_EC_Information LL ADC Information
  * @brief LL ADC Information
  * @{
  */

/**
  * @brief LL ADC Analog WDG Monitor Channel Mask Definition
  */
#define LL_ADC_AWDG_MONITOR_CHANNEL_MSK                     (0x000FFFFFUL)

/**
  * @brief LL ADC Oversampling mode Mask Definition
  */
#define LL_ADC_CFGR0_OVERSAMPLING_MODE_MSK                  ((ADC0_CFGR0_ROVSE_Msk  | ADC0_CFGR0_ROVSM_Msk   | \
                                                              ADC0_CFGR0_TROVS_Msk  | ADC0_CFGR0_JOVSE_Msk   ))

/**
  * @brief LL ADC CR Activate State Mask Definition
  */
#define LL_ADC_CR_ACTIVATE_STATE_MSK                        ((ADC0_CR_ADSTP_Msk     | ADC0_CR_JADSTP_Msk     | \
                                                              ADC0_CR_ADSTART_Msk   | ADC0_CR_JADSTART_Msk   | \
                                                              ADC0_CR_ADCAL_Msk     | ADC0_CR_ADDIS_Msk      | \
                                                              ADC0_CR_ADEN_Msk                               ))

/**
  * @brief LL ADC CFGR1 Perparing Start Mask Definition
  */
#define  LL_ADC_CFGR1_PREPARING_START_MSK                   ((ADC0_CFGR1_BIASEN_Msk | ADC0_CFGR1_REFEN_Msk   | \
                                                              ADC0_CFGR1_CHEN_Msk   ))

/**
  * @brief LL ADC IER Interrupt Enable All Mask Definition
  */
#define LL_ADC_IER_IT_EN_MSK                                ((ADC0_IER_EOSMPIE_Msk  | ADC0_IER_ADRDYIE_Msk  | \
                                                              ADC0_IER_AWD2IE_Msk   | ADC0_IER_AWD1IE_Msk   | \
                                                              ADC0_IER_AWD0IE_Msk   | ADC0_IER_OVRIE_Msk    | \
                                                              ADC0_IER_JEOSIE_Msk   | ADC0_IER_JEOCIE_Msk   | \
                                                              ADC0_IER_EOSIE_Msk    | ADC0_IER_EOCIE_Msk    ))

/**
  * @brief LL ADC IER Interrupt Enable Mask Definition
  */
#define LL_ADC_IER_ITEnMskTypeDef                           uint32_t

#define LL_ADC_IER_EOSMPIE                   (ADC0_IER_EOSMPIE_Msk)               /*!< EOSMPIE Mask             */
#define LL_ADC_IER_ADRDYIE                   (ADC0_IER_ADRDYIE_Msk)               /*!< ADRDYIE Mask             */
#define LL_ADC_IER_AWD2IE                    (ADC0_IER_AWD2IE_Msk)                /*!< AWD2IE Mask              */
#define LL_ADC_IER_AWD1IE                    (ADC0_IER_AWD1IE_Msk)                /*!< AWD1IE Mask              */
#define LL_ADC_IER_AWD0IE                    (ADC0_IER_AWD0IE_Msk)                /*!< AWD0IE Mask              */
#define LL_ADC_IER_OVRIE                     (ADC0_IER_OVRIE_Msk)                 /*!< OVRIE Mask               */
#define LL_ADC_IER_JEOSIE                    (ADC0_IER_JEOSIE_Msk)                /*!< JEOSIE Mask              */
#define LL_ADC_IER_JEOCIE                    (ADC0_IER_JEOCIE_Msk)                /*!< JEOCIE Mask              */
#define LL_ADC_IER_EOSIE                     (ADC0_IER_EOSIE_Msk)                 /*!< EOSIE Mask               */
#define LL_ADC_IER_EOCIE                     (ADC0_IER_EOCIE_Msk)                 /*!< EOCIE Mask               */


/**
  * @brief LL ADC ISR Interrupt Flag All Mask Definition
  */
#define LL_ADC_ISR_IT_FLAG_MSK                              ((ADC0_ISR_EOSMP_Msk    | ADC0_ISR_ADRDY_Msk    | \
                                                              ADC0_ISR_AWD2_Msk     | ADC0_ISR_AWD1_Msk     | \
                                                              ADC0_ISR_AWD0_Msk     | ADC0_ISR_OVR_Msk      | \
                                                              ADC0_ISR_JEOS_Msk     | ADC0_ISR_JEOC_Msk     | \
                                                              ADC0_ISR_EOS_Msk      | ADC0_ISR_EOC_Msk      ))

/**
  * @brief LL ADC ISR Sampling Interrupt Flag All Mask Definition
  */
#define LL_ADC_ISR_SAMP_IT_FLAG_MSK                         ((ADC0_ISR_EOSMP_Msk))

/**
  * @brief LL ADC ISR Status Interrupt Flag All Mask Definition
  */
#define LL_ADC_ISR_STATUS_IT_FLAG_MSK                       ((ADC0_ISR_ADRDY_Msk    | ADC0_ISR_OVR_Msk      ))

/**
  * @brief LL ADC ISR AWDG Interrupt Flag All Mask Definition
  */
#define LL_ADC_ISR_AWDG_IT_FLAG_MSK                         ((ADC0_ISR_AWD2_Msk     | ADC0_ISR_AWD1_Msk     | \
                                                              ADC0_ISR_AWD0_Msk     ))

/**
  * @brief LL ADC ISR Injected Interrupt Flag All Mask Definition
  */
#define LL_ADC_ISR_INJ_IT_FLAG_MSK                          ((ADC0_ISR_JEOS_Msk     | ADC0_ISR_JEOC_Msk     ))

/**
  * @brief LL ADC ISR Regular Interrupt Flag All Mask Definition
  */
#define LL_ADC_ISR_REG_IT_FLAG_MSK                          ((ADC0_ISR_EOS_Msk      | ADC0_ISR_EOC_Msk      ))


/**
  * @brief ADC ISR Interrupt Pending Mask Definition
  */
#define LL_ADC_ISR_ITPendingMskTypeDef                      uint32_t

#define LL_ADC_ISR_EOSMP                     (ADC0_ISR_EOSMP_Msk)                 /*!< EOSMP Mask               */
#define LL_ADC_ISR_ADRDY                     (ADC0_ISR_ADRDY_Msk)                 /*!< ADRDY Mask               */
#define LL_ADC_ISR_AWD2                      (ADC0_ISR_AWD2_Msk)                  /*!< AWD2 Mask                */
#define LL_ADC_ISR_AWD1                      (ADC0_ISR_AWD1_Msk)                  /*!< AWD1 Mask                */
#define LL_ADC_ISR_AWD0                      (ADC0_ISR_AWD0_Msk)                  /*!< AWD0 Mask                */
#define LL_ADC_ISR_OVR                       (ADC0_ISR_OVR_Msk)                   /*!< OVR Mask                 */
#define LL_ADC_ISR_JEOS                      (ADC0_ISR_JEOS_Msk)                  /*!< JEOS Mask                */
#define LL_ADC_ISR_JEOC                      (ADC0_ISR_JEOC_Msk)                  /*!< JEOC Mask                */
#define LL_ADC_ISR_EOS                       (ADC0_ISR_EOS_Msk)                   /*!< EOS Mask                 */
#define LL_ADC_ISR_EOC                       (ADC0_ISR_EOC_Msk)                   /*!< EOC Mask                 */


/**
  * @brief LL ADC DIER Date Interrupt Enable All Mask Definition
  */
#define LL_ADC_DIER_IT_EN_MSK                               ((ADC0_DIER_DONIE19_Msk | ADC0_DIER_DONIE18_Msk | \
                                                              ADC0_DIER_DONIE17_Msk | ADC0_DIER_DONIE16_Msk | \
                                                              ADC0_DIER_DONIE15_Msk | ADC0_DIER_DONIE14_Msk | \
                                                              ADC0_DIER_DONIE13_Msk | ADC0_DIER_DONIE12_Msk | \
                                                              ADC0_DIER_DONIE11_Msk | ADC0_DIER_DONIE10_Msk | \
                                                              ADC0_DIER_DONIE9_Msk  | ADC0_DIER_DONIE8_Msk  | \
                                                              ADC0_DIER_DONIE7_Msk  | ADC0_DIER_DONIE6_Msk  | \
                                                              ADC0_DIER_DONIE5_Msk  | ADC0_DIER_DONIE4_Msk  | \
                                                              ADC0_DIER_DONIE3_Msk  | ADC0_DIER_DONIE2_Msk  | \
                                                              ADC0_DIER_DONIE1_Msk  | ADC0_DIER_DONIE0_Msk  ))

/**
  * @brief LL ADC DIER Date Interrupt Enable Mask Definition
  */
#define LL_ADC_DIER_ITEnMskTypeDef                          uint32_t

#define LL_ADC_DIER_DONIE19                  (ADC0_DIER_DONIE19_Msk)              /*!< DONIE19 Mask             */
#define LL_ADC_DIER_DONIE18                  (ADC0_DIER_DONIE18_Msk)              /*!< DONIE18 Mask             */
#define LL_ADC_DIER_DONIE17                  (ADC0_DIER_DONIE17_Msk)              /*!< DONIE17 Mask             */
#define LL_ADC_DIER_DONIE16                  (ADC0_DIER_DONIE16_Msk)              /*!< DONIE16 Mask             */
#define LL_ADC_DIER_DONIE15                  (ADC0_DIER_DONIE15_Msk)              /*!< DONIE15 Mask             */
#define LL_ADC_DIER_DONIE14                  (ADC0_DIER_DONIE14_Msk)              /*!< DONIE14 Mask             */
#define LL_ADC_DIER_DONIE13                  (ADC0_DIER_DONIE13_Msk)              /*!< DONIE13 Mask             */
#define LL_ADC_DIER_DONIE12                  (ADC0_DIER_DONIE12_Msk)              /*!< DONIE12 Mask             */
#define LL_ADC_DIER_DONIE11                  (ADC0_DIER_DONIE11_Msk)              /*!< DONIE11 Mask             */
#define LL_ADC_DIER_DONIE10                  (ADC0_DIER_DONIE10_Msk)              /*!< DONIE10 Mask             */
#define LL_ADC_DIER_DONIE9                   (ADC0_DIER_DONIE9_Msk)               /*!< DONIE9 Mask              */
#define LL_ADC_DIER_DONIE8                   (ADC0_DIER_DONIE8_Msk)               /*!< DONIE8 Mask              */
#define LL_ADC_DIER_DONIE7                   (ADC0_DIER_DONIE7_Msk)               /*!< DONIE7 Mask              */
#define LL_ADC_DIER_DONIE6                   (ADC0_DIER_DONIE6_Msk)               /*!< DONIE6 Mask              */
#define LL_ADC_DIER_DONIE5                   (ADC0_DIER_DONIE5_Msk)               /*!< DONIE5 Mask              */
#define LL_ADC_DIER_DONIE4                   (ADC0_DIER_DONIE4_Msk)               /*!< DONIE4 Mask              */
#define LL_ADC_DIER_DONIE3                   (ADC0_DIER_DONIE3_Msk)               /*!< DONIE3 Mask              */
#define LL_ADC_DIER_DONIE2                   (ADC0_DIER_DONIE2_Msk)               /*!< DONIE2 Mask              */
#define LL_ADC_DIER_DONIE1                   (ADC0_DIER_DONIE1_Msk)               /*!< DONIE1 Mask              */
#define LL_ADC_DIER_DONIE0                   (ADC0_DIER_DONIE0_Msk)               /*!< DONIE0 Mask              */


/**
  * @brief LL ADC DISR Date Interrupt Flag All Mask Definition
  */
#define LL_ADC_DISR_IT_FLAG_MSK                             ((ADC0_DISR_DON19_Msk   | ADC0_DISR_DON18_Msk   | \
                                                              ADC0_DISR_DON17_Msk   | ADC0_DISR_DON16_Msk   | \
                                                              ADC0_DISR_DON15_Msk   | ADC0_DISR_DON14_Msk   | \
                                                              ADC0_DISR_DON13_Msk   | ADC0_DISR_DON12_Msk   | \
                                                              ADC0_DISR_DON11_Msk   | ADC0_DISR_DON10_Msk   | \
                                                              ADC0_DISR_DON9_Msk    | ADC0_DISR_DON8_Msk    | \
                                                              ADC0_DISR_DON7_Msk    | ADC0_DISR_DON6_Msk    | \
                                                              ADC0_DISR_DON5_Msk    | ADC0_DISR_DON4_Msk    | \
                                                              ADC0_DISR_DON3_Msk    | ADC0_DISR_DON2_Msk    | \
                                                              ADC0_DISR_DON1_Msk    | ADC0_DISR_DON0_Msk    ))

/**
  * @brief ADC DISR Date Interrupt Pending Mask Definition
  */
#define LL_ADC_DISR_ITPendingMskTypeDef                     uint32_t

#define LL_ADC_DISR_DON19                    (ADC0_DISR_DON19_Msk)                /*!< DON19 Mask               */
#define LL_ADC_DISR_DON18                    (ADC0_DISR_DON18_Msk)                /*!< DON18 Mask               */
#define LL_ADC_DISR_DON17                    (ADC0_DISR_DON17_Msk)                /*!< DON17 Mask               */
#define LL_ADC_DISR_DON16                    (ADC0_DISR_DON16_Msk)                /*!< DON16 Mask               */
#define LL_ADC_DISR_DON15                    (ADC0_DISR_DON15_Msk)                /*!< DON15 Mask               */
#define LL_ADC_DISR_DON14                    (ADC0_DISR_DON14_Msk)                /*!< DON14 Mask               */
#define LL_ADC_DISR_DON13                    (ADC0_DISR_DON13_Msk)                /*!< DON13 Mask               */
#define LL_ADC_DISR_DON12                    (ADC0_DISR_DON12_Msk)                /*!< DON12 Mask               */
#define LL_ADC_DISR_DON11                    (ADC0_DISR_DON11_Msk)                /*!< DON11 Mask               */
#define LL_ADC_DISR_DON10                    (ADC0_DISR_DON10_Msk)                /*!< DON10 Mask               */
#define LL_ADC_DISR_DON9                     (ADC0_DISR_DON9_Msk)                 /*!< DON9 Mask                */
#define LL_ADC_DISR_DON8                     (ADC0_DISR_DON8_Msk)                 /*!< DON8 Mask                */
#define LL_ADC_DISR_DON7                     (ADC0_DISR_DON7_Msk)                 /*!< DON7 Mask                */
#define LL_ADC_DISR_DON6                     (ADC0_DISR_DON6_Msk)                 /*!< DON6 Mask                */
#define LL_ADC_DISR_DON5                     (ADC0_DISR_DON5_Msk)                 /*!< DON5 Mask                */
#define LL_ADC_DISR_DON4                     (ADC0_DISR_DON4_Msk)                 /*!< DON4 Mask                */
#define LL_ADC_DISR_DON3                     (ADC0_DISR_DON3_Msk)                 /*!< DON3 Mask                */
#define LL_ADC_DISR_DON2                     (ADC0_DISR_DON2_Msk)                 /*!< DON2 Mask                */
#define LL_ADC_DISR_DON1                     (ADC0_DISR_DON1_Msk)                 /*!< DON1 Mask                */
#define LL_ADC_DISR_DON0                     (ADC0_DISR_DON0_Msk)                 /*!< DON0 Mask                */


/**
  * @brief LL ADC DMA Full Interrupt Enable All Mask Definition
  */
#define LL_ADC_FIER_DMA_FULL_IT_EN_MSK                      ((ADC0_FIER_FULIE19_Msk | ADC0_FIER_FULIE18_Msk | \
                                                              ADC0_FIER_FULIE17_Msk | ADC0_FIER_FULIE16_Msk | \
                                                              ADC0_FIER_FULIE15_Msk | ADC0_FIER_FULIE14_Msk | \
                                                              ADC0_FIER_FULIE13_Msk | ADC0_FIER_FULIE12_Msk | \
                                                              ADC0_FIER_FULIE11_Msk | ADC0_FIER_FULIE10_Msk | \
                                                              ADC0_FIER_FULIE9_Msk  | ADC0_FIER_FULIE8_Msk  | \
                                                              ADC0_FIER_FULIE7_Msk  | ADC0_FIER_FULIE6_Msk  | \
                                                              ADC0_FIER_FULIE5_Msk  | ADC0_FIER_FULIE4_Msk  | \
                                                              ADC0_FIER_FULIE3_Msk  | ADC0_FIER_FULIE2_Msk  | \
                                                              ADC0_FIER_FULIE1_Msk  | ADC0_FIER_FULIE0_Msk  ))

/**
  * @brief LL ADC FIER DMA Full Interrupt Enable Mask Definition
  */
#define LL_ADC_FIER_ITEnMskTypeDef                          uint32_t

#define LL_ADC_FIER_FULIE19                  (ADC0_FIER_FULIE19_Msk)              /*!< FULIE19 Mask             */
#define LL_ADC_FIER_FULIE18                  (ADC0_FIER_FULIE18_Msk)              /*!< FULIE18 Mask             */
#define LL_ADC_FIER_FULIE17                  (ADC0_FIER_FULIE17_Msk)              /*!< FULIE17 Mask             */
#define LL_ADC_FIER_FULIE16                  (ADC0_FIER_FULIE16_Msk)              /*!< FULIE16 Mask             */
#define LL_ADC_FIER_FULIE15                  (ADC0_FIER_FULIE15_Msk)              /*!< FULIE15 Mask             */
#define LL_ADC_FIER_FULIE14                  (ADC0_FIER_FULIE14_Msk)              /*!< FULIE14 Mask             */
#define LL_ADC_FIER_FULIE13                  (ADC0_FIER_FULIE13_Msk)              /*!< FULIE13 Mask             */
#define LL_ADC_FIER_FULIE12                  (ADC0_FIER_FULIE12_Msk)              /*!< FULIE12 Mask             */
#define LL_ADC_FIER_FULIE11                  (ADC0_FIER_FULIE11_Msk)              /*!< FULIE11 Mask             */
#define LL_ADC_FIER_FULIE10                  (ADC0_FIER_FULIE10_Msk)              /*!< FULIE10 Mask             */
#define LL_ADC_FIER_FULIE9                   (ADC0_FIER_FULIE9_Msk)               /*!< FULIE9 Mask              */
#define LL_ADC_FIER_FULIE8                   (ADC0_FIER_FULIE8_Msk)               /*!< FULIE8 Mask              */
#define LL_ADC_FIER_FULIE7                   (ADC0_FIER_FULIE7_Msk)               /*!< FULIE7 Mask              */
#define LL_ADC_FIER_FULIE6                   (ADC0_FIER_FULIE6_Msk)               /*!< FULIE6 Mask              */
#define LL_ADC_FIER_FULIE5                   (ADC0_FIER_FULIE5_Msk)               /*!< FULIE5 Mask              */
#define LL_ADC_FIER_FULIE4                   (ADC0_FIER_FULIE4_Msk)               /*!< FULIE4 Mask              */
#define LL_ADC_FIER_FULIE3                   (ADC0_FIER_FULIE3_Msk)               /*!< FULIE3 Mask              */
#define LL_ADC_FIER_FULIE2                   (ADC0_FIER_FULIE2_Msk)               /*!< FULIE2 Mask              */
#define LL_ADC_FIER_FULIE1                   (ADC0_FIER_FULIE1_Msk)               /*!< FULIE1 Mask              */
#define LL_ADC_FIER_FULIE0                   (ADC0_FIER_FULIE0_Msk)               /*!< FULIE0 Mask              */

/**
  * @brief LL ADC DMA Full Interrupt Flag All Mask Definition
  */
#define LL_ADC_FISR_DMA_FULL_IT_FLAG_MSK                    ((ADC0_FISR_FUL19_Msk   | ADC0_FISR_FUL18_Msk   | \
                                                              ADC0_FISR_FUL17_Msk   | ADC0_FISR_FUL16_Msk   | \
                                                              ADC0_FISR_FUL15_Msk   | ADC0_FISR_FUL14_Msk   | \
                                                              ADC0_FISR_FUL13_Msk   | ADC0_FISR_FUL12_Msk   | \
                                                              ADC0_FISR_FUL11_Msk   | ADC0_FISR_FUL10_Msk   | \
                                                              ADC0_FISR_FUL9_Msk    | ADC0_FISR_FUL8_Msk    | \
                                                              ADC0_FISR_FUL7_Msk    | ADC0_FISR_FUL6_Msk    | \
                                                              ADC0_FISR_FUL5_Msk    | ADC0_FISR_FUL4_Msk    | \
                                                              ADC0_FISR_FUL3_Msk    | ADC0_FISR_FUL2_Msk    | \
                                                              ADC0_FISR_FUL1_Msk    | ADC0_FISR_FUL0_Msk    ))

/**
  * @brief ADC FISR DMA Full Interrupt Pending Mask Definition
  */
#define LL_ADC_FISR_ITPendingMskTypeDef                     uint32_t

#define LL_ADC_FISR_FUL19                    (ADC0_FISR_FUL19_Msk)                /*!< FUL19 Mask               */
#define LL_ADC_FISR_FUL18                    (ADC0_FISR_FUL18_Msk)                /*!< FUL18 Mask               */
#define LL_ADC_FISR_FUL17                    (ADC0_FISR_FUL17_Msk)                /*!< FUL17 Mask               */
#define LL_ADC_FISR_FUL16                    (ADC0_FISR_FUL16_Msk)                /*!< FUL16 Mask               */
#define LL_ADC_FISR_FUL15                    (ADC0_FISR_FUL15_Msk)                /*!< FUL15 Mask               */
#define LL_ADC_FISR_FUL14                    (ADC0_FISR_FUL14_Msk)                /*!< FUL14 Mask               */
#define LL_ADC_FISR_FUL13                    (ADC0_FISR_FUL13_Msk)                /*!< FUL13 Mask               */
#define LL_ADC_FISR_FUL12                    (ADC0_FISR_FUL12_Msk)                /*!< FUL12 Mask               */
#define LL_ADC_FISR_FUL11                    (ADC0_FISR_FUL11_Msk)                /*!< FUL11 Mask               */
#define LL_ADC_FISR_FUL10                    (ADC0_FISR_FUL10_Msk)                /*!< FUL10 Mask               */
#define LL_ADC_FISR_FUL9                     (ADC0_FISR_FUL9_Msk)                 /*!< FUL9 Mask                */
#define LL_ADC_FISR_FUL8                     (ADC0_FISR_FUL8_Msk)                 /*!< FUL8 Mask                */
#define LL_ADC_FISR_FUL7                     (ADC0_FISR_FUL7_Msk)                 /*!< FUL7 Mask                */
#define LL_ADC_FISR_FUL6                     (ADC0_FISR_FUL6_Msk)                 /*!< FUL6 Mask                */
#define LL_ADC_FISR_FUL5                     (ADC0_FISR_FUL5_Msk)                 /*!< FUL5 Mask                */
#define LL_ADC_FISR_FUL4                     (ADC0_FISR_FUL4_Msk)                 /*!< FUL4 Mask                */
#define LL_ADC_FISR_FUL3                     (ADC0_FISR_FUL3_Msk)                 /*!< FUL3 Mask                */
#define LL_ADC_FISR_FUL2                     (ADC0_FISR_FUL2_Msk)                 /*!< FUL2 Mask                */
#define LL_ADC_FISR_FUL1                     (ADC0_FISR_FUL1_Msk)                 /*!< FUL1 Mask                */
#define LL_ADC_FISR_FUL0                     (ADC0_FISR_FUL0_Msk)                 /*!< FUL0 Mask                */

/**
  * @brief LL ADC DMA Half Full Interrupt Enable All Mask Definition
  */
#define LL_ADC_HIER_DMA_HALF_IT_EN_MSK                      ((ADC0_HIER_HLFIE19_Msk | ADC0_HIER_HLFIE18_Msk | \
                                                              ADC0_HIER_HLFIE17_Msk | ADC0_HIER_HLFIE16_Msk | \
                                                              ADC0_HIER_HLFIE15_Msk | ADC0_HIER_HLFIE14_Msk | \
                                                              ADC0_HIER_HLFIE13_Msk | ADC0_HIER_HLFIE12_Msk | \
                                                              ADC0_HIER_HLFIE11_Msk | ADC0_HIER_HLFIE10_Msk | \
                                                              ADC0_HIER_HLFIE9_Msk  | ADC0_HIER_HLFIE8_Msk  | \
                                                              ADC0_HIER_HLFIE7_Msk  | ADC0_HIER_HLFIE6_Msk  | \
                                                              ADC0_HIER_HLFIE5_Msk  | ADC0_HIER_HLFIE4_Msk  | \
                                                              ADC0_HIER_HLFIE3_Msk  | ADC0_HIER_HLFIE2_Msk  | \
                                                              ADC0_HIER_HLFIE1_Msk  | ADC0_HIER_HLFIE0_Msk  ))

/**
  * @brief LL ADC HIER DMA Half Full Interrupt Enable Mask Definition
  */
#define LL_ADC_HIER_ITEnMskTypeDef                          uint32_t

#define LL_ADC_HIER_HLFIE19                  (ADC0_HIER_HLFIE19_Msk)              /*!< HLFIE19 Mask             */
#define LL_ADC_HIER_HLFIE18                  (ADC0_HIER_HLFIE18_Msk)              /*!< HLFIE18 Mask             */
#define LL_ADC_HIER_HLFIE17                  (ADC0_HIER_HLFIE17_Msk)              /*!< HLFIE17 Mask             */
#define LL_ADC_HIER_HLFIE16                  (ADC0_HIER_HLFIE16_Msk)              /*!< HLFIE16 Mask             */
#define LL_ADC_HIER_HLFIE15                  (ADC0_HIER_HLFIE15_Msk)              /*!< HLFIE15 Mask             */
#define LL_ADC_HIER_HLFIE14                  (ADC0_HIER_HLFIE14_Msk)              /*!< HLFIE14 Mask             */
#define LL_ADC_HIER_HLFIE13                  (ADC0_HIER_HLFIE13_Msk)              /*!< HLFIE13 Mask             */
#define LL_ADC_HIER_HLFIE12                  (ADC0_HIER_HLFIE12_Msk)              /*!< HLFIE12 Mask             */
#define LL_ADC_HIER_HLFIE11                  (ADC0_HIER_HLFIE11_Msk)              /*!< HLFIE11 Mask             */
#define LL_ADC_HIER_HLFIE10                  (ADC0_HIER_HLFIE10_Msk)              /*!< HLFIE10 Mask             */
#define LL_ADC_HIER_HLFIE9                   (ADC0_HIER_HLFIE9_Msk)               /*!< HLFIE9 Mask              */
#define LL_ADC_HIER_HLFIE8                   (ADC0_HIER_HLFIE8_Msk)               /*!< HLFIE8 Mask              */
#define LL_ADC_HIER_HLFIE7                   (ADC0_HIER_HLFIE7_Msk)               /*!< HLFIE7 Mask              */
#define LL_ADC_HIER_HLFIE6                   (ADC0_HIER_HLFIE6_Msk)               /*!< HLFIE6 Mask              */
#define LL_ADC_HIER_HLFIE5                   (ADC0_HIER_HLFIE5_Msk)               /*!< HLFIE5 Mask              */
#define LL_ADC_HIER_HLFIE4                   (ADC0_HIER_HLFIE4_Msk)               /*!< HLFIE4 Mask              */
#define LL_ADC_HIER_HLFIE3                   (ADC0_HIER_HLFIE3_Msk)               /*!< HLFIE3 Mask              */
#define LL_ADC_HIER_HLFIE2                   (ADC0_HIER_HLFIE2_Msk)               /*!< HLFIE2 Mask              */
#define LL_ADC_HIER_HLFIE1                   (ADC0_HIER_HLFIE1_Msk)               /*!< HLFIE1 Mask              */
#define LL_ADC_HIER_HLFIE0                   (ADC0_HIER_HLFIE0_Msk)               /*!< HLFIE0 Mask              */

/**
  * @brief LL ADC DMA Half Full Interrupt Flag All Mask Definition
  */
#define LL_ADC_HISR_DMA_HALF_IT_FLAG_MSK                    ((ADC0_HISR_HLF19_Msk   | ADC0_HISR_HLF18_Msk   | \
                                                              ADC0_HISR_HLF17_Msk   | ADC0_HISR_HLF16_Msk   | \
                                                              ADC0_HISR_HLF15_Msk   | ADC0_HISR_HLF14_Msk   | \
                                                              ADC0_HISR_HLF13_Msk   | ADC0_HISR_HLF12_Msk   | \
                                                              ADC0_HISR_HLF11_Msk   | ADC0_HISR_HLF10_Msk   | \
                                                              ADC0_HISR_HLF9_Msk    | ADC0_HISR_HLF8_Msk    | \
                                                              ADC0_HISR_HLF7_Msk    | ADC0_HISR_HLF6_Msk    | \
                                                              ADC0_HISR_HLF5_Msk    | ADC0_HISR_HLF4_Msk    | \
                                                              ADC0_HISR_HLF3_Msk    | ADC0_HISR_HLF2_Msk    | \
                                                              ADC0_HISR_HLF1_Msk    | ADC0_HISR_HLF0_Msk    ))

/**
  * @brief ADC HISR DMA Half Full Interrupt Pending Mask Definition
  */
#define LL_ADC_HISR_ITPendingMskTypeDef                     uint32_t

#define LL_ADC_HISR_HLF19                    (ADC0_HISR_HLF19_Msk)                /*!< HLF19 Mask               */
#define LL_ADC_HISR_HLF18                    (ADC0_HISR_HLF18_Msk)                /*!< HLF18 Mask               */
#define LL_ADC_HISR_HLF17                    (ADC0_HISR_HLF17_Msk)                /*!< HLF17 Mask               */
#define LL_ADC_HISR_HLF16                    (ADC0_HISR_HLF16_Msk)                /*!< HLF16 Mask               */
#define LL_ADC_HISR_HLF15                    (ADC0_HISR_HLF15_Msk)                /*!< HLF15 Mask               */
#define LL_ADC_HISR_HLF14                    (ADC0_HISR_HLF14_Msk)                /*!< HLF14 Mask               */
#define LL_ADC_HISR_HLF13                    (ADC0_HISR_HLF13_Msk)                /*!< HLF13 Mask               */
#define LL_ADC_HISR_HLF12                    (ADC0_HISR_HLF12_Msk)                /*!< HLF12 Mask               */
#define LL_ADC_HISR_HLF11                    (ADC0_HISR_HLF11_Msk)                /*!< HLF11 Mask               */
#define LL_ADC_HISR_HLF10                    (ADC0_HISR_HLF10_Msk)                /*!< HLF10 Mask               */
#define LL_ADC_HISR_HLF9                     (ADC0_HISR_HLF9_Msk)                 /*!< HLF9 Mask                */
#define LL_ADC_HISR_HLF8                     (ADC0_HISR_HLF8_Msk)                 /*!< HLF8 Mask                */
#define LL_ADC_HISR_HLF7                     (ADC0_HISR_HLF7_Msk)                 /*!< HLF7 Mask                */
#define LL_ADC_HISR_HLF6                     (ADC0_HISR_HLF6_Msk)                 /*!< HLF6 Mask                */
#define LL_ADC_HISR_HLF5                     (ADC0_HISR_HLF5_Msk)                 /*!< HLF5 Mask                */
#define LL_ADC_HISR_HLF4                     (ADC0_HISR_HLF4_Msk)                 /*!< HLF4 Mask                */
#define LL_ADC_HISR_HLF3                     (ADC0_HISR_HLF3_Msk)                 /*!< HLF3 Mask                */
#define LL_ADC_HISR_HLF2                     (ADC0_HISR_HLF2_Msk)                 /*!< HLF2 Mask                */
#define LL_ADC_HISR_HLF1                     (ADC0_HISR_HLF1_Msk)                 /*!< HLF1 Mask                */
#define LL_ADC_HISR_HLF0                     (ADC0_HISR_HLF0_Msk)                 /*!< HLF0 Mask                */



/**
  * @brief LL ADC CSR Master ADC Interrupt Flag All Mask Definition
  */
#define LL_ADC_CSR_MST_IT_FLAG_MSK                          ((ADC0_CSR_EOSMP_MST_Msk  | ADC0_CSR_ADRDY_MST_Msk  | \
                                                              ADC0_CSR_AWD2_MST_Msk   | ADC0_CSR_AWD1_MST_Msk   | \
                                                              ADC0_CSR_AWD0_MST_Msk   | ADC0_CSR_OVR_MST_Msk    | \
                                                              ADC0_CSR_JEOS_MST_Msk   | ADC0_CSR_JEOC_MST_Msk   | \
                                                              ADC0_CSR_EOS_MST_Msk    | ADC0_CSR_EOC_MST_Msk    ))


/**
  * @brief LL ADC CSR Slave ADC Interrupt Flag All Mask Definition
  */
#define LL_ADC_CSR_SLV_IT_FLAG_MSK                          ((ADC0_CSR_EOSMP_SLV_Msk  | ADC0_CSR_ADRDY_SLV_Msk  | \
                                                              ADC0_CSR_AWD2_SLV_Msk   | ADC0_CSR_AWD1_SLV_Msk   | \
                                                              ADC0_CSR_AWD0_SLV_Msk   | ADC0_CSR_OVR_SLV_Msk    | \
                                                              ADC0_CSR_JEOS_SLV_Msk   | ADC0_CSR_JEOC_SLV_Msk   | \
                                                              ADC0_CSR_EOS_SLV_Msk    | ADC0_CSR_EOC_SLV_Msk    ))

/**
  * @brief ADC CSR Interrupt Pending Mask Definition
  */
#define LL_ADC_CSR_ITPendingMskTypeDef                      uint32_t

#define LL_ADC_CSR_EOSMP_SLV                 (ADC0_CSR_EOSMP_SLV_Msk)             /*!< EOSMP_SLV Mask           */
#define LL_ADC_CSR_ADRDY_SLV                 (ADC0_CSR_ADRDY_SLV_Msk)             /*!< ADRDY_SLV Mask           */
#define LL_ADC_CSR_AWD2_SLV                  (ADC0_CSR_AWD2_SLV_Msk)              /*!< AWD2_SLV Mask            */
#define LL_ADC_CSR_AWD1_SLV                  (ADC0_CSR_AWD1_SLV_Msk)              /*!< AWD1_SLV Mask            */
#define LL_ADC_CSR_AWD0_SLV                  (ADC0_CSR_AWD0_SLV_Msk)              /*!< AWD0_SLV Mask            */
#define LL_ADC_CSR_OVR_SLV                   (ADC0_CSR_OVR_SLV_Msk)               /*!< OVR_SLV Mask             */
#define LL_ADC_CSR_JEOS_SLV                  (ADC0_CSR_JEOS_SLV_Msk)              /*!< JEOS_SLV Mask            */
#define LL_ADC_CSR_JEOC_SLV                  (ADC0_CSR_JEOC_SLV_Msk)              /*!< JEOC_SLV Mask            */
#define LL_ADC_CSR_EOS_SLV                   (ADC0_CSR_EOS_SLV_Msk)               /*!< EOS_SLV Mask             */
#define LL_ADC_CSR_EOC_SLV                   (ADC0_CSR_EOC_SLV_Msk)               /*!< EOC_SLV Mask             */
#define LL_ADC_CSR_EOSMP_MST                 (ADC0_CSR_EOSMP_MST_Msk)             /*!< EOSMP_MST Mask           */
#define LL_ADC_CSR_ADRDY_MST                 (ADC0_CSR_ADRDY_MST_Msk)             /*!< ADRDY_MST Mask           */
#define LL_ADC_CSR_AWD2_MST                  (ADC0_CSR_AWD2_MST_Msk)              /*!< AWD2_MST Mask            */
#define LL_ADC_CSR_AWD1_MST                  (ADC0_CSR_AWD1_MST_Msk)              /*!< AWD1_MST Mask            */
#define LL_ADC_CSR_AWD0_MST                  (ADC0_CSR_AWD0_MST_Msk)              /*!< AWD0_MST Mask            */
#define LL_ADC_CSR_OVR_MST                   (ADC0_CSR_OVR_MST_Msk)               /*!< OVR_MST Mask             */
#define LL_ADC_CSR_JEOS_MST                  (ADC0_CSR_JEOS_MST_Msk)              /*!< JEOS_MST Mask            */
#define LL_ADC_CSR_JEOC_MST                  (ADC0_CSR_JEOC_MST_Msk)              /*!< JEOC_MST Mask            */
#define LL_ADC_CSR_EOS_MST                   (ADC0_CSR_EOS_MST_Msk)               /*!< EOS_MST Mask             */
#define LL_ADC_CSR_EOC_MST                   (ADC0_CSR_EOC_MST_Msk)               /*!< EOC_MST Mask             */




/**
  * @}
  */ /* ADC_LL_EC_Information */


/** @defgroup ADC_LL_EC_Configuration LL ADC Configuration
  * @brief LL ADC Configuration 
  * @{
  */

/**
  * @brief ADC Channel Definition
  */
#define LL_ADC_ChTypeDef                            LL_RSV_DATA_TYPE    

#define LL_ADC_CH_0                                 (0UL)                /*!< ADC Channel 0                                    */
#define LL_ADC_CH_1                                 (1UL)                /*!< ADC Channel 1                                    */
#define LL_ADC_CH_2                                 (2UL)                /*!< ADC Channel 2                                    */
#define LL_ADC_CH_3                                 (3UL)                /*!< ADC Channel 3                                    */
#define LL_ADC_CH_4                                 (4UL)                /*!< ADC Channel 4                                    */
#define LL_ADC_CH_5                                 (5UL)                /*!< ADC Channel 5                                    */
#define LL_ADC_CH_6                                 (6UL)                /*!< ADC Channel 6                                    */
#define LL_ADC_CH_7                                 (7UL)                /*!< ADC Channel 7                                    */
#define LL_ADC_CH_8                                 (8UL)                /*!< ADC Channel 8                                    */
#define LL_ADC_CH_9                                 (9UL)                /*!< ADC Channel 9                                    */
#define LL_ADC_CH_10                                (10UL)               /*!< ADC Channel 10                                   */
#define LL_ADC_CH_11                                (11UL)               /*!< ADC Channel 11                                   */
#define LL_ADC_CH_12                                (12UL)               /*!< ADC Channel 12                                   */
#define LL_ADC_CH_13                                (13UL)               /*!< ADC Channel 13                                   */
#define LL_ADC_CH_14                                (14UL)               /*!< ADC Channel 14                                   */
#define LL_ADC_CH_15                                (15UL)               /*!< ADC Channel 15                                   */
#define LL_ADC_CH_16                                (16UL)               /*!< ADC Channel 16                                   */
#define LL_ADC_CH_17                                (17UL)               /*!< ADC Channel 17                                   */
#define LL_ADC_CH_18                                (18UL)               /*!< ADC Channel 18                                   */
#define LL_ADC_CH_19                                (19UL)               /*!< ADC Channel 19                                   */
#define LL_ADC_CH_NUMS                              (20UL)               /*!< ADC Ch Nums                                      */

#define IS_LL_ADC_CH(__VAL__)                       (((__VAL__) == LL_ADC_CH_0)    || \
                                                     ((__VAL__) == LL_ADC_CH_1)    || \
                                                     ((__VAL__) == LL_ADC_CH_2)    || \
                                                     ((__VAL__) == LL_ADC_CH_3)    || \
                                                     ((__VAL__) == LL_ADC_CH_4)    || \
                                                     ((__VAL__) == LL_ADC_CH_5)    || \
                                                     ((__VAL__) == LL_ADC_CH_6)    || \
                                                     ((__VAL__) == LL_ADC_CH_7)    || \
                                                     ((__VAL__) == LL_ADC_CH_8)    || \
                                                     ((__VAL__) == LL_ADC_CH_9)    || \
                                                     ((__VAL__) == LL_ADC_CH_10)   || \
                                                     ((__VAL__) == LL_ADC_CH_11)   || \
                                                     ((__VAL__) == LL_ADC_CH_12)   || \
                                                     ((__VAL__) == LL_ADC_CH_13)   || \
                                                     ((__VAL__) == LL_ADC_CH_14)   || \
                                                     ((__VAL__) == LL_ADC_CH_15)   || \
                                                     ((__VAL__) == LL_ADC_CH_16)   || \
                                                     ((__VAL__) == LL_ADC_CH_17)   || \
                                                     ((__VAL__) == LL_ADC_CH_18)   || \
                                                     ((__VAL__) == LL_ADC_CH_19)   )

/**
  * @brief ADC Regular Sequence Number Definition
  */
#define LL_ADC_REG_SeqNumTypeDef                    LL_RSV_DATA_TYPE    

#define LL_ADC_REG_SEQ_NUM_1                        (0UL)                /*!< ADC Regular Sequence Number 1                    */
#define LL_ADC_REG_SEQ_NUM_2                        (1UL)                /*!< ADC Regular Sequence Number 2                    */
#define LL_ADC_REG_SEQ_NUM_3                        (2UL)                /*!< ADC Regular Sequence Number 3                    */
#define LL_ADC_REG_SEQ_NUM_4                        (3UL)                /*!< ADC Regular Sequence Number 4                    */
#define LL_ADC_REG_SEQ_NUM_5                        (4UL)                /*!< ADC Regular Sequence Number 5                    */
#define LL_ADC_REG_SEQ_NUM_6                        (5UL)                /*!< ADC Regular Sequence Number 6                    */
#define LL_ADC_REG_SEQ_NUM_7                        (6UL)                /*!< ADC Regular Sequence Number 7                    */
#define LL_ADC_REG_SEQ_NUM_8                        (7UL)                /*!< ADC Regular Sequence Number 8                    */
#define LL_ADC_REG_SEQ_NUM_9                        (8UL)                /*!< ADC Regular Sequence Number 9                    */
#define LL_ADC_REG_SEQ_NUM_10                       (9UL)                /*!< ADC Regular Sequence Number 10                   */
#define LL_ADC_REG_SEQ_NUM_11                       (10UL)               /*!< ADC Regular Sequence Number 11                   */
#define LL_ADC_REG_SEQ_NUM_12                       (11UL)               /*!< ADC Regular Sequence Number 12                   */
#define LL_ADC_REG_SEQ_NUM_13                       (12UL)               /*!< ADC Regular Sequence Number 13                   */
#define LL_ADC_REG_SEQ_NUM_14                       (13UL)               /*!< ADC Regular Sequence Number 14                   */
#define LL_ADC_REG_SEQ_NUM_15                       (14UL)               /*!< ADC Regular Sequence Number 15                   */
#define LL_ADC_REG_SEQ_NUM_16                       (15UL)               /*!< ADC Regular Sequence Number 16                   */
#define LL_ADC_REG_SEQ_NUMS                         (16UL)               /*!< ADC Regular Sequence Numbers                     */

#define IS_LL_ADC_REG_SEQ(__VAL__)                  (((__VAL__) == LL_ADC_REG_SEQ_NUM_1)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_2)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_3)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_4)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_5)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_6)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_7)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_8)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_9)  || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_10) || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_11) || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_12) || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_13) || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_14) || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_15) || \
                                                     ((__VAL__) == LL_ADC_REG_SEQ_NUM_16) )

/**
  * @brief ADC Injected Sequence Number Definition
  */
#define LL_ADC_INJ_SeqNumTypeDef                    LL_RSV_DATA_TYPE    

#define LL_ADC_INJ_SEQ_NUM_1                        (0UL)                /*!< ADC Injected Sequence Number 1                   */
#define LL_ADC_INJ_SEQ_NUM_2                        (1UL)                /*!< ADC Injected Sequence Number 2                   */
#define LL_ADC_INJ_SEQ_NUM_3                        (2UL)                /*!< ADC Injected Sequence Number 3                   */
#define LL_ADC_INJ_SEQ_NUM_4                        (3UL)                /*!< ADC Injected Sequence Number 4                   */
#define LL_ADC_INJ_SEQ_NUMS                         (4UL)                /*!< ADC Injected Sequence Numbers                    */

#define IS_LL_ADC_INJ_SEQ(__VAL__)                  (((__VAL__) == LL_ADC_INJ_SEQ_NUM_1) || \
                                                     ((__VAL__) == LL_ADC_INJ_SEQ_NUM_2) || \
                                                     ((__VAL__) == LL_ADC_INJ_SEQ_NUM_3) || \
                                                     ((__VAL__) == LL_ADC_INJ_SEQ_NUM_4) )

/**
  * @brief ADC AWDG Number Definition
  */
#define LL_ADC_AWDG_NumTypeDef                      LL_RSV_DATA_TYPE    

#define LL_ADC_AWDG_NUM_0                           (0UL)                /*!< ADC AWDG Number 0                                */
#define LL_ADC_AWDG_NUM_1                           (1UL)                /*!< ADC AWDG Number 1                                */
#define LL_ADC_AWDG_NUM_2                           (2UL)                /*!< ADC AWDG Number 2                                */
#define LL_ADC_AWDG_NUMS                            (3UL)                /*!< ADC AWDG Numbers                                 */

#define IS_LL_ADC_AWDG(__VAL__)                     (((__VAL__) == LL_ADC_AWDG_NUM_0) || \
                                                     ((__VAL__) == LL_ADC_AWDG_NUM_1) || \
                                                     ((__VAL__) == LL_ADC_AWDG_NUM_2) )

/**
  * @brief ADC Channel Calibration Coefficient Group Definition
  */
#define LL_ADC_CalCoefGrpTypeDef                    LL_RSV_DATA_TYPE    

#define LL_ADC_CAL_COEF_GRP_0                       (0UL)                /*!< ADC Channel Calibration Coefficient Group 0      */
#define LL_ADC_CAL_COEF_GRP_1                       (1UL)                /*!< ADC Channel Calibration Coefficient Group 1      */
#define LL_ADC_CAL_COEF_GRP_2                       (2UL)                /*!< ADC Channel Calibration Coefficient Group 2      */
#define LL_ADC_CAL_COEF_GRP_3                       (3UL)                /*!< ADC Channel Calibration Coefficient Group 3      */
#define LL_ADC_CAL_COEF_GRP_NUMS                    (4UL)                /*!< ADC Channel Calibration Coefficient Group Nums   */

#define IS_LL_ADC_CAL_COEF_GRP(__VAL__)             (((__VAL__) == LL_ADC_CAL_COEF_GRP_0) || \
                                                     ((__VAL__) == LL_ADC_CAL_COEF_GRP_1) || \
                                                     ((__VAL__) == LL_ADC_CAL_COEF_GRP_2) || \
                                                     ((__VAL__) == LL_ADC_CAL_COEF_GRP_3) )

/**
  * @brief Regular Discontinuous Conversion Numbers Definition
  */
#define LL_ADC_REG_DisContConvNumTypeDef            LL_RSV_DATA_TYPE    

#define LL_ADC_REG_DISCONT_CONV_NUM_1               (0UL)                /*!< Regular Discontinuous Conversion Numbers 1       */
#define LL_ADC_REG_DISCONT_CONV_NUM_2               (1UL)                /*!< Regular Discontinuous Conversion Numbers 2       */
#define LL_ADC_REG_DISCONT_CONV_NUM_3               (2UL)                /*!< Regular Discontinuous Conversion Numbers 3       */
#define LL_ADC_REG_DISCONT_CONV_NUM_4               (3UL)                /*!< Regular Discontinuous Conversion Numbers 4       */
#define LL_ADC_REG_DISCONT_CONV_NUM_5               (4UL)                /*!< Regular Discontinuous Conversion Numbers 5       */
#define LL_ADC_REG_DISCONT_CONV_NUM_6               (5UL)                /*!< Regular Discontinuous Conversion Numbers 6       */
#define LL_ADC_REG_DISCONT_CONV_NUM_7               (6UL)                /*!< Regular Discontinuous Conversion Numbers 7       */
#define LL_ADC_REG_DISCONT_CONV_NUM_8               (7UL)                /*!< Regular Discontinuous Conversion Numbers 8       */

#define IS_LL_ADC_REG_DISCONT_CONV_NUM(__VAL__)     (((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_1) || \
                                                     ((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_2) || \
                                                     ((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_3) || \
                                                     ((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_4) || \
                                                     ((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_5) || \
                                                     ((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_6) || \
                                                     ((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_7) || \
                                                     ((__VAL__) == LL_ADC_REG_DISCONT_CONV_NUM_8) )

/**
  * @brief ADC Regular Sequence Length Definition
  */
#define LL_ADC_REG_SeqLenTypeDef                    LL_RSV_DATA_TYPE    

#define LL_ADC_REG_SEQ_LEN_1                        (0UL)                /*!< ADC Regular Sequence Length 1                    */
#define LL_ADC_REG_SEQ_LEN_2                        (1UL)                /*!< ADC Regular Sequence Length 2                    */
#define LL_ADC_REG_SEQ_LEN_3                        (2UL)                /*!< ADC Regular Sequence Length 3                    */
#define LL_ADC_REG_SEQ_LEN_4                        (3UL)                /*!< ADC Regular Sequence Length 4                    */
#define LL_ADC_REG_SEQ_LEN_5                        (4UL)                /*!< ADC Regular Sequence Length 5                    */
#define LL_ADC_REG_SEQ_LEN_6                        (5UL)                /*!< ADC Regular Sequence Length 6                    */
#define LL_ADC_REG_SEQ_LEN_7                        (6UL)                /*!< ADC Regular Sequence Length 7                    */
#define LL_ADC_REG_SEQ_LEN_8                        (7UL)                /*!< ADC Regular Sequence Length 8                    */
#define LL_ADC_REG_SEQ_LEN_9                        (8UL)                /*!< ADC Regular Sequence Length 9                    */
#define LL_ADC_REG_SEQ_LEN_10                       (9UL)                /*!< ADC Regular Sequence Length 10                   */
#define LL_ADC_REG_SEQ_LEN_11                       (10UL)               /*!< ADC Regular Sequence Length 11                   */
#define LL_ADC_REG_SEQ_LEN_12                       (11UL)               /*!< ADC Regular Sequence Length 12                   */
#define LL_ADC_REG_SEQ_LEN_13                       (12UL)               /*!< ADC Regular Sequence Length 13                   */
#define LL_ADC_REG_SEQ_LEN_14                       (13UL)               /*!< ADC Regular Sequence Length 14                   */
#define LL_ADC_REG_SEQ_LEN_15                       (14UL)               /*!< ADC Regular Sequence Length 15                   */
#define LL_ADC_REG_SEQ_LEN_16                       (15UL)               /*!< ADC Regular Sequence Length 16                   */

#define IS_LL_ADC_REG_SEQ_LEN(__VAL__)              (((__VAL__) >= LL_ADC_REG_SEQ_LEN_1)  && \
                                                     ((__VAL__) <= LL_ADC_REG_SEQ_LEN_16) )

/**
  * @brief Regular Conversion Mode Definition
  */
#define LL_ADC_REG_ConvModeTypeDef                  LL_RSV_DATA_TYPE    

#define LL_ADC_REG_CONV_SINGLE                      (0UL)                /*!< Regular Conversion Mode Single                   */
#define LL_ADC_REG_CONV_CONTINUOUS                  (1UL)                /*!< Regular Conversion Mode Continuous               */

#define IS_LL_ADC_REG_CONV(__VAL__)                 (((__VAL__) == LL_ADC_REG_CONV_SINGLE)     || \
                                                     ((__VAL__) == LL_ADC_REG_CONV_CONTINUOUS) )

/**
  * @brief ADC Channel Input Mode Definition
  */
#define LL_ADC_InputModeTypeDef                     LL_RSV_DATA_TYPE    

#define LL_ADC_INPUT_MODE_SINGLE_END                (0UL)                /*!< ADC Channel Input Mode Single-End                */
#define LL_ADC_INPUT_MODE_DIFF                      (1UL)                /*!< ADC Channel Input Mode Differential              */

#define IS_LL_ADC_INPUT_MODE(__VAL__)               (((__VAL__) == LL_ADC_INPUT_MODE_SINGLE_END) || \
                                                     ((__VAL__) == LL_ADC_INPUT_MODE_DIFF)       )

/**
  * @brief ADC Channel Sample Time Definition
  */
#define LL_ADC_SampTimeTypeDef                      LL_RSV_DATA_TYPE    

#define LL_ADC_SAMP_TIME_2_CYCLES                   (0UL)                /*!< ADC Channel Sample Time 2 Cycles                 */
#define LL_ADC_SAMP_TIME_6_CYCLES                   (1UL)                /*!< ADC Channel Sample Time 6 Cycles                 */
#define LL_ADC_SAMP_TIME_14_CYCLES                  (2UL)                /*!< ADC Channel Sample Time 14 Cycles                */
#define LL_ADC_SAMP_TIME_30_CYCLES                  (3UL)                /*!< ADC Channel Sample Time 30 Cycles                */
#define LL_ADC_SAMP_TIME_62_CYCLES                  (4UL)                /*!< ADC Channel Sample Time 62 Cycles                */
#define LL_ADC_SAMP_TIME_126_CYCLES                 (5UL)                /*!< ADC Channel Sample Time 126 Cycles               */
#define LL_ADC_SAMP_TIME_254_CYCLES                 (6UL)                /*!< ADC Channel Sample Time 254 Cycles               */
#define LL_ADC_SAMP_TIME_510_CYCLES                 (7UL)                /*!< ADC Channel Sample Time 510 Cycles               */

#define IS_LL_ADC_SAMP_TIME(__VAL__)                (((__VAL__) == LL_ADC_SAMP_TIME_2_CYCLES)   || \
                                                     ((__VAL__) == LL_ADC_SAMP_TIME_6_CYCLES)   || \
                                                     ((__VAL__) == LL_ADC_SAMP_TIME_14_CYCLES)  || \
                                                     ((__VAL__) == LL_ADC_SAMP_TIME_30_CYCLES)  || \
                                                     ((__VAL__) == LL_ADC_SAMP_TIME_62_CYCLES)  || \
                                                     ((__VAL__) == LL_ADC_SAMP_TIME_126_CYCLES) || \
                                                     ((__VAL__) == LL_ADC_SAMP_TIME_254_CYCLES) || \
                                                     ((__VAL__) == LL_ADC_SAMP_TIME_510_CYCLES) )

/**
  * @brief ADC Injected Sequence Length Definition
  */
#define LL_ADC_INJ_SeqLenTypeDef                    LL_RSV_DATA_TYPE    

#define LL_ADC_INJ_SEQ_LEN_1                        (0UL)                /*!< ADC Injected Sequence Length 1                   */
#define LL_ADC_INJ_SEQ_LEN_2                        (1UL)                /*!< ADC Injected Sequence Length 2                   */
#define LL_ADC_INJ_SEQ_LEN_3                        (2UL)                /*!< ADC Injected Sequence Length 3                   */
#define LL_ADC_INJ_SEQ_LEN_4                        (3UL)                /*!< ADC Injected Sequence Length 4                   */

#define IS_LL_ADC_INJ_SEQ_LEN(__VAL__)              (((__VAL__) == LL_ADC_INJ_SEQ_LEN_1) || \
                                                     ((__VAL__) == LL_ADC_INJ_SEQ_LEN_2) || \
                                                     ((__VAL__) == LL_ADC_INJ_SEQ_LEN_3) || \
                                                     ((__VAL__) == LL_ADC_INJ_SEQ_LEN_4) )

/**
  * @brief Normal Channel Oversample Mode Definition
  */
#define LL_ADC_NormOverSampModeTypeDef              LL_RSV_DATA_TYPE    

#define LL_ADC_NORM_OVER_SAMP_CONTINUE              (0UL)                /*!< Normal Channel Oversample Mode Continue          */
#define LL_ADC_NORM_OVER_SAMP_RESUME                (1UL)                /*!< Normal Channel Oversample Mode Resume            */

#define IS_LL_ADC_NORM_OVER_SAMP(__VAL__)           (((__VAL__) == LL_ADC_NORM_OVER_SAMP_CONTINUE) || \
                                                     ((__VAL__) == LL_ADC_NORM_OVER_SAMP_RESUME)   )

/**
  * @brief Overrun Mode Definition
  */
#define LL_ADC_OverRunModeTypeDef                   LL_RSV_DATA_TYPE    

#define LL_ADC_OVERRUN_DATA_PRESERVED               (0UL)                /*!< Overrun Mode Preserved                           */
#define LL_ADC_OVERRUN_DATA_OVERWRITTEN             (1UL)                /*!< Overrun Mode Overwriten                          */

#define IS_LL_ADC_OVERRUN_DATA(__VAL__)             (((__VAL__) == LL_ADC_OVERRUN_DATA_PRESERVED)   || \
                                                     ((__VAL__) == LL_ADC_OVERRUN_DATA_OVERWRITTEN) )

/**
  * @brief Over Sample Data Shift Definition
  */
#define LL_ADC_OverSampShiftTypeDef                 LL_RSV_DATA_TYPE    

#define LL_ADC_OVER_SAMP_SHIFT_NONE                 (0UL)                /*!< Over Sample Data Shift None                      */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_1              (1UL)                /*!< Over Sample Data Shift Right 1                   */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_2              (2UL)                /*!< Over Sample Data Shift Right 2                   */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_3              (3UL)                /*!< Over Sample Data Shift Right 3                   */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_4              (4UL)                /*!< Over Sample Data Shift Right 4                   */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_5              (5UL)                /*!< Over Sample Data Shift Right 5                   */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_6              (6UL)                /*!< Over Sample Data Shift Right 6                   */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_7              (7UL)                /*!< Over Sample Data Shift Right 7                   */
#define LL_ADC_OVER_SAMP_SHIFT_RIGHT_8              (8UL)                /*!< Over Sample Data Shift Right 8                   */

#define IS_LL_ADC_OVER_SAMP_SHIFT(__VAL__)          (((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_NONE)    || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_1) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_2) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_3) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_4) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_5) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_6) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_7) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_SHIFT_RIGHT_8) )

/**
  * @brief Over Sample Ratio Definition
  */
#define LL_ADC_OverSampRatioTypeDef                 LL_RSV_DATA_TYPE    

#define LL_ADC_OVER_SAMP_RATIO_2                    (0UL)                /*!< Over Sample Ratio 2                              */
#define LL_ADC_OVER_SAMP_RATIO_4                    (1UL)                /*!< Over Sample Ratio 4                              */
#define LL_ADC_OVER_SAMP_RATIO_8                    (2UL)                /*!< Over Sample Ratio 8                              */
#define LL_ADC_OVER_SAMP_RATIO_16                   (3UL)                /*!< Over Sample Ratio 16                             */
#define LL_ADC_OVER_SAMP_RATIO_32                   (4UL)                /*!< Over Sample Ratio 32                             */
#define LL_ADC_OVER_SAMP_RATIO_64                   (5UL)                /*!< Over Sample Ratio 64                             */
#define LL_ADC_OVER_SAMP_RATIO_128                  (6UL)                /*!< Over Sample Ratio 128                            */
#define LL_ADC_OVER_SAMP_RATIO_256                  (7UL)                /*!< Over Sample Ratio 256                            */

#define IS_LL_ADC_OVER_SAMP_RATIO(__VAL__)          (((__VAL__) == LL_ADC_OVER_SAMP_RATIO_2)   || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_RATIO_4)   || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_RATIO_8)   || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_RATIO_16)  || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_RATIO_32)  || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_RATIO_64)  || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_RATIO_128) || \
                                                     ((__VAL__) == LL_ADC_OVER_SAMP_RATIO_256) )

/**
  * @brief ADC Bias Current Definition
  */
#define LL_ADC_BiasCurTypeDef                       LL_RSV_DATA_TYPE    

#define LL_ADC_BIAS_CUR_10uA                        (0UL)                /*!< ADC Bias Current 10uA                            */
#define LL_ADC_BIAS_CUR_12uA                        (1UL)                /*!< ADC Bias Current 12uA                            */
#define LL_ADC_BIAS_CUR_14uA                        (2UL)                /*!< ADC Bias Current 14uA                            */
#define LL_ADC_BIAS_CUR_8uA                         (3UL)                /*!< ADC Bias Current 8uA                             */

#define IS_LL_ADC_BIAS_CUR(__VAL__)                 (((__VAL__) == LL_ADC_BIAS_CUR_10uA) || \
                                                     ((__VAL__) == LL_ADC_BIAS_CUR_12uA) || \
                                                     ((__VAL__) == LL_ADC_BIAS_CUR_14uA) || \
                                                     ((__VAL__) == LL_ADC_BIAS_CUR_8uA)  )

/**
  * @brief ADC Dual Mode Definition
  * @note  Dual mode Only Master ADC Valid
  *        Quad mode Only Master ADC0/2 Valid
  */
#define LL_ADC_DualModeTypeDef                      LL_RSV_DATA_TYPE    

#define LL_ADC_DUAL_MODE_INDEPEND                   (0UL)                /*!< ADC Dual Mode Disabled                           */
#define LL_ADC_DUAL_MODE_REG_INJ_SYNC               (1UL)                /*!< ADC Dual Mode Regular and Injected Sync          */
#define LL_ADC_DUAL_MODE_REG_SYNC_INJ_TRIG          (2UL)                /*!< ADC Dual Mode Regular Sync and Injected Trigger  */
#define LL_ADC_DUAL_MODE_REG_TRIG_INJ_SYNC          (3UL)                /*!< ADC Dual Mode Regular Trigger and Injected Sync  */
#define LL_ADC_DUAL_MODE_INJ_SYNC                   (4UL)                /*!< ADC Dual Mode Injected Sync                      */
#define LL_ADC_DUAL_MODE_REG_SYNC                   (5UL)                /*!< ADC Dual Mode Regular Sync                       */
#define LL_ADC_DUAL_MODE_REG_INTERLEAVED            (6UL)                /*!< ADC Dual Mode Regular InterleaveD                */
#define LL_ADC_DUAL_MODE_INJ_TRIG                   (7UL)                /*!< ADC Dual Mode Injected Trigger                   */
#define LL_ADC_QUAD_MODE_INJ_SYNC                   (12UL)               /*!< ADC Quad Mode Injected Sync                      */
#define LL_ADC_QUAD_MODE_REG_SYNC                   (13UL)               /*!< ADC Quad Mode Regular Sync                       */

/**
  * @brief ADC Sequence Trigger Polarity Definition
  */
#define LL_ADC_SeqTrigPolTypeDef                    LL_RSV_DATA_TYPE    

#define LL_ADC_SEQ_TRIG_POL_SW                      (0UL)                /*!< ADC Sequence Trigger Polarity Software           */
#define LL_ADC_SEQ_TRIG_POL_HW_RISING               (1UL)                /*!< ADC Sequence Trigger Polarity Hardware Rising    */
#define LL_ADC_SEQ_TRIG_POL_HW_FALLING              (2UL)                /*!< ADC Sequence Trigger Polarity Hardware Falling   */
#define LL_ADC_SEQ_TRIG_POL_HW_BOTH_EDGE            (3UL)                /*!< ADC Sequence Trigger Polarity Hardware Both Edge */

#define IS_LL_ADC_SEQ_TRIG_POL(__VAL__)             (((__VAL__) == LL_ADC_SEQ_TRIG_POL_SW)           || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_POL_HW_RISING)    || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_POL_HW_FALLING)   || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_POL_HW_BOTH_EDGE) )

/**
  * @brief ADC Sequence Trigger Event Definition
  */
#define LL_ADC_SeqTrigEvtTypeDef                    LL_RSV_DATA_TYPE    

#define LL_ADC_SEQ_TRIG_EVT_TMR7_TRGO               (0UL)                /*!< ADC Sequence Trigger Event TMR7_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR8_TRGO               (1UL)                /*!< ADC Sequence Trigger Event TMR8_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR0_CC0                (2UL)                /*!< ADC Sequence Trigger Event TMR0_CC0              */
#define LL_ADC_SEQ_TRIG_EVT_TMR1_CC0                (3UL)                /*!< ADC Sequence Trigger Event TMR1_CC0              */
#define LL_ADC_SEQ_TRIG_EVT_TMR2_CC0                (4UL)                /*!< ADC Sequence Trigger Event TMR2_CC0              */
#define LL_ADC_SEQ_TRIG_EVT_TMR0_TRGO               (5UL)                /*!< ADC Sequence Trigger Event TMR0_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR1_TRGO               (6UL)                /*!< ADC Sequence Trigger Event TMR1_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR2_TRGO               (7UL)                /*!< ADC Sequence Trigger Event TMR2_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR3_CC0                (8UL)                /*!< ADC Sequence Trigger Event TMR3_CC0              */
#define LL_ADC_SEQ_TRIG_EVT_TMR3_CC1                (9UL)                /*!< ADC Sequence Trigger Event TMR3_CC1              */
#define LL_ADC_SEQ_TRIG_EVT_TMR3_TRGO               (10UL)               /*!< ADC Sequence Trigger Event TMR3_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR4_CC0                (11UL)               /*!< ADC Sequence Trigger Event TMR4_CC0              */
#define LL_ADC_SEQ_TRIG_EVT_TMR4_CC1                (12UL)               /*!< ADC Sequence Trigger Event TMR4_CC1              */
#define LL_ADC_SEQ_TRIG_EVT_TMR4_TRGO               (13UL)               /*!< ADC Sequence Trigger Event TMR4_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR9_CC0                (14UL)               /*!< ADC Sequence Trigger Event TMR9_CC0              */
#define LL_ADC_SEQ_TRIG_EVT_TMR9_CC1                (15UL)               /*!< ADC Sequence Trigger Event TMR9_CC1              */
#define LL_ADC_SEQ_TRIG_EVT_TMR9_TRGO               (16UL)               /*!< ADC Sequence Trigger Event TMR9_TRGO             */
#define LL_ADC_SEQ_TRIG_EVT_TMR10_CC0               (17UL)               /*!< ADC Sequence Trigger Event TMR10_CC0             */
#define LL_ADC_SEQ_TRIG_EVT_TMR10_CC1               (18UL)               /*!< ADC Sequence Trigger Event TMR10_CC1             */
#define LL_ADC_SEQ_TRIG_EVT_TMR10_CC2               (19UL)               /*!< ADC Sequence Trigger Event TMR10_CC2             */
#define LL_ADC_SEQ_TRIG_EVT_TMR10_TRGO              (20UL)               /*!< ADC Sequence Trigger Event TMR10_TRGO            */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG0           (21UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG0         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG1           (22UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG1         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG2           (23UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG2         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG3           (24UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG3         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG4           (25UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG4         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG5           (26UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG5         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG6           (27UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG6         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG7           (28UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG7         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG8           (29UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG8         */
#define LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG9           (30UL)               /*!< ADC Sequence Trigger Event HRPWM_ADCTRG9         */
#define LL_ADC_SEQ_TRIG_EVT_EXT_PIN_PA_8_9          (31UL)               /*!< ADC Sequence Trigger Event Ext Pin PA8/PA9       */
#define LL_ADC_SEQ_TRIG_EVT_REG_PA8                 (31UL)               /*!< ADC Sequence Trigger Event PA8 (Regular group)   */
#define LL_ADC_SEQ_TRIG_EVT_INJ_PA9                 (31UL)               /*!< ADC Sequence Trigger Event PA9 (Injected group)  */
#define LL_ADC_SEQ_TRIG_EVT_SOFTWARE                (0x7FFFFFFFUL & ~ADC0_LR_EXTSEL_Val)  /*!< ADC Sequence Trigger Event Software */

#define IS_LL_ADC_SEQ_TRIG_EVT(__VAL__)             (((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR7_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR8_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR0_CC0)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR1_CC0)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR2_CC0)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR0_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR1_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR2_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR3_CC0)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR3_CC1)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR3_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR4_CC0)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR4_CC1)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR4_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR9_CC0)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR9_CC1)       || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR9_TRGO)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR10_CC0)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR10_CC1)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR10_CC2)      || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_TMR10_TRGO)     || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG0)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG1)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG2)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG3)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG4)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG5)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG6)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG7)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG8)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG9)  || \
                                                     ((__VAL__) == LL_ADC_SEQ_TRIG_EVT_EXT_PIN_PA_8_9) )

/**
  * @brief ADC Calibration Mode Definition
  */
#define LL_ADC_CalModeTypeDef                       LL_RSV_DATA_TYPE    

#define LL_ADC_CAL_MODE_SINGLE_END                  (0UL)                /*!< ADC Calibration Mode Single-End                  */
#define LL_ADC_CAL_MODE_DIFF                        (1UL)                /*!< ADC Calibration Mode Differential                */

#define IS_LL_ADC_CAL_MODE(__VAL__)                 (((__VAL__) == LL_ADC_CAL_MODE_SINGLE_END) || \
                                                     ((__VAL__) == LL_ADC_CAL_MODE_DIFF)       )

/**
  * @brief ADC Channel Saturation Arithmetic Mode Definition
  */
#define LL_ADC_ChSaturationTypeDef                  LL_RSV_DATA_TYPE

#define LL_ADC_CH_SATURATION_SUPPORT                (0UL)                /*!< Channel Saturation Arithmetic Support            */
#define LL_ADC_CH_SATURATION_NOT_SUPPORT            (1UL)                /*!< Channel Saturation Arithmetic Not Support        */

#define IS_LL_ADC_CH_SATURATION(__VAL__)            (((__VAL__) == LL_ADC_CH_SATURATION_SUPPORT)      || \
                                                     ((__VAL__) == LL_ADC_CH_SATURATION_NOT_SUPPORT)  )

/**
  * @brief ADC DMA Fix Address Enable Definition
  */
#define LL_ADC_DMAFixAddrEnTypeDef                  LL_RSV_DATA_TYPE

#define LL_ADC_DMA_FIXED_ADDRESS_DISABLE            (0UL)                /*!< DMA Fix Address Disable                          */
#define LL_ADC_DMA_FIXED_ADDRESS_ENABLE             (1UL)                /*!< DMA Fix Address Enable                           */

#define IS_LL_ADC_DMA_FIXED_ADDRESS(__VAL__)        (((__VAL__) == LL_ADC_DMA_FIXED_ADDRESS_DISABLE)  || \
                                                     ((__VAL__) == LL_ADC_DMA_FIXED_ADDRESS_ENABLE)   )

/**
  * @brief ADC DMA Circulation Mode Enable Definition
  */
#define LL_ADC_DMACircModeEnTypeDef                 LL_RSV_DATA_TYPE

#define LL_ADC_DMA_CIRC_MODE_DISABLE                (0UL)                /*!< DMA Circulation Mode Disable                     */
#define LL_ADC_DMA_CIRC_MODE_ENABLE                 (1UL)                /*!< DMA Circulation Mode Enable                      */

#define IS_LL_ADC_DMA_CIRC_MODE(__VAL__)            (((__VAL__) == LL_ADC_DMA_CIRC_MODE_DISABLE)  || \
                                                     ((__VAL__) == LL_ADC_DMA_CIRC_MODE_ENABLE)   )

/**
  * @brief ADC AWDG Filter Point Numbers Definition
  */
#define LL_ADC_AWDG_FilterPointNumsTypeDef          LL_RSV_DATA_TYPE    

#define LL_ADC_AWDG_FILTER_POINT_NONE               (0UL)                /*!< ADC AWDG Filter Point None                       */
#define LL_ADC_AWDG_FILTER_POINT_NUM_2              (1UL)                /*!< ADC AWDG Filter Point Numbers 2                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_3              (2UL)                /*!< ADC AWDG Filter Point Numbers 3                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_4              (3UL)                /*!< ADC AWDG Filter Point Numbers 4                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_5              (4UL)                /*!< ADC AWDG Filter Point Numbers 5                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_6              (5UL)                /*!< ADC AWDG Filter Point Numbers 6                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_7              (6UL)                /*!< ADC AWDG Filter Point Numbers 7                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_8              (7UL)                /*!< ADC AWDG Filter Point Numbers 8                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_9              (8UL)                /*!< ADC AWDG Filter Point Numbers 9                  */
#define LL_ADC_AWDG_FILTER_POINT_NUM_10             (9UL)                /*!< ADC AWDG Filter Point Numbers 10                 */
#define LL_ADC_AWDG_FILTER_POINT_NUM_11             (10UL)               /*!< ADC AWDG Filter Point Numbers 11                 */
#define LL_ADC_AWDG_FILTER_POINT_NUM_12             (11UL)               /*!< ADC AWDG Filter Point Numbers 12                 */
#define LL_ADC_AWDG_FILTER_POINT_NUM_13             (12UL)               /*!< ADC AWDG Filter Point Numbers 13                 */
#define LL_ADC_AWDG_FILTER_POINT_NUM_14             (13UL)               /*!< ADC AWDG Filter Point Numbers 14                 */
#define LL_ADC_AWDG_FILTER_POINT_NUM_15             (14UL)               /*!< ADC AWDG Filter Point Numbers 15                 */
#define LL_ADC_AWDG_FILTER_POINT_NUM_16             (15UL)               /*!< ADC AWDG Filter Point Numbers 16                 */

#define IS_LL_ADC__AWDG_FILTER_POINT(__VAL__)       (((__VAL__) >= LL_ADC_AWDG_FILTER_POINT_NONE)  && \
                                                     ((__VAL__) <= LL_ADC_AWDG_FILTER_POINT_NUM_16) )

/**
  * @brief ADC Sampling Mode Definition
  */
#define LL_ADC_SamplingModeTypeDef                  LL_RSV_DATA_TYPE    

#define LL_ADC_SAMP_MODE_OVER_SAMP_DISABLE          (0x00000000UL)                /*!< ADC oversampling disabled.              */
#define LL_ADC_SAMP_MODE_REG_CONTINUED              (ADC0_CFGR0_ROVSE_Msk)        /*!< ADC oversampling on conversions of ADC   \
                                                                                      group regular.                           */
#define LL_ADC_SAMP_MODE_REG_RESUMED                (ADC0_CFGR0_ROVSE_Msk | ADC0_CFGR0_ROVSM_Msk)  /*!< ADC oversampling on     \
                                                                                      conversions of ADC group regular.        */
#define LL_ADC_SAMP_MODE_TRIGGERED_REG_RESUMED      (ADC0_CFGR0_ROVSE_Msk | ADC0_CFGR0_ROVSM_Msk | ADC0_CFGR0_TROVS_Msk)  /*!<  \ 
                                                                                      ADC oversampling on conversions of ADC    \
                                                                                      group regular in triggered.              */
#define LL_ADC_SAMP_MODE_INJ_REG_RESUMED            (ADC0_CFGR0_ROVSE_Msk | ADC0_CFGR0_ROVSM_Msk | ADC0_CFGR0_JOVSE_Msk)  /*!<  \
                                                                                      ADC oversampling on conversions of ADC    \
                                                                                      groups regular and injected.             */
#define LL_ADC_SAMP_MODE_INJ                        (ADC0_CFGR0_JOVSE_Msk)        /*!< ADC oversampling on conversions of ADC   \
                                                                                      group injected.                          */


/**
  * @}
  */ /* ADC_LL_EC_Configuration */

/**
  * @}
  */ /* ADC_LL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC LL Exported Macros
  * @brief    ADC LL Exported Macros
  * @{
  */


/**
  * @brief  ADC 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define LL_ADC_REG_OFFSET(__REG__, offset)            \
        (*((volatile uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))

/**
  * @brief  ADC DMA Register offset
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Offset in ADC_DMA_TypeDef type
  * @return ADC_DMA_TypeDef type struct
  */
#define LL_ADC_DMA_REG_OFFSET(__REG__, offset)        \
        (*((volatile ADC_DMA_TypeDef *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) * (sizeof(ADC_DMA_TypeDef)))))))
/**
  * @}
  */ /* ADC_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC LL Functions
  * @brief    ADC LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_ADC_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_ADC_ASSERT_INLINE_PARAM == 1)
extern void LL_ADC_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_ADC_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_ADC_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_ADC_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup ADC_LL_EF_Configuration LL ADC Configuration
  * @brief    LL ADC Configuration
  * @{
  */

/**
  * @brief  Calibration Mode Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Mode Calibration Mode @ref LL_ADC_CalModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetCalibrationMode(ADC_TypeDef *ADCx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CR, ADC0_CR_ADCALDIF_Msk, (((Mode) & ADC0_CR_ADCALDIF_Val) << ADC0_CR_ADCALDIF_Pos));
}

/**
  * @brief  Calibration Mode Get
  * @param  ADCx Specifies ADC peripheral
  * @return Calibration Mode @ref LL_ADC_CalModeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibrationMode(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_ADCALDIF_Msk, ADC0_CR_ADCALDIF_Pos));
}

/**
  * @brief  Judge is ADC Activated or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 ADC isn't Activated
  * @retval 1 ADC is Activated
  */
__STATIC_INLINE uint32_t LL_ADC_IsActivated(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)((READ_BIT(ADCx->CR, LL_ADC_CR_ACTIVATE_STATE_MSK)) ? 1UL : 0UL);
}

/**
  * @brief  Judge is ADC Deactivated or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 ADC isn't Deactivated
  * @retval 1 ADC is Deactivated
  */
__STATIC_INLINE uint32_t LL_ADC_IsDeactivated(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)((!READ_BIT(ADCx->CR, LL_ADC_CR_ACTIVATE_STATE_MSK)) ? 1UL : 0UL);
}

/**
  * @brief  Calibration Start 
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_StartCalibration(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADCAL_Msk);
}

/**
  * @brief  Judge is Calibration Starting or not 
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 Calibration not start
  * @retval 1 Calibration Starting
  */
__STATIC_INLINE uint32_t LL_ADC_IsCalibrationOnGoing(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_ADCAL_Msk, ADC0_CR_ADCAL_Pos));
}

/**
  * @brief  Judge is Conversion Stopping or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 Conversion has Stopped
  * @retval 1 Conversion is Stopping
  */
__STATIC_INLINE uint32_t LL_ADC_IsConversionStopping(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)((READ_BIT(ADCx->CR, ADC0_CR_ADSTP_Msk | ADC0_CR_JADSTP_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Judge is Conversion Running or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 Conversion isn't Running
  * @retval 1 Conversion is Running
  */
__STATIC_INLINE uint32_t LL_ADC_IsConversionRunning(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)((READ_BIT(ADCx->CR, ADC0_CR_ADSTART_Msk | ADC0_CR_JADSTART_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Injected Conversion Stop
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_StopConversion(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_JADSTP_Msk);
}

/**
  * @brief  Judge is Injected Conversion Stopping or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 Injected Conversion has Stopped
  * @retval 1 Injected Conversion is Stopping
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsStopConversionOngoing(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_JADSTP_Msk, ADC0_CR_JADSTP_Pos));
}

/**
  * @brief  Regular Conversion Stop
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_StopConversion(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADSTP_Msk);
}

/**
  * @brief  Judge is Regular Conversion Stopping or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 Regular Conversion has Stopped
  * @retval 1 Regular Conversion is Stopping
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsStopConversionOngoing(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_ADSTP_Msk, ADC0_CR_ADSTP_Pos));
}

/**
  * @brief  Injected Conversion Start
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_StartConversion(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_JADSTART_Msk);
}

/**
  * @brief  Judge is Injected Conversion Running or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 Injected Conversion isn't Running
  * @retval 1 Injected Conversion is Running
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsConversionOngoing(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_JADSTART_Msk, ADC0_CR_JADSTART_Pos));
}

/**
  * @brief  Regular Conversion Start
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_StartConversion(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADSTART_Msk);
}

/**
  * @brief  Judge is Regular Conversion Running or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 Regular Conversion isn't Running
  * @retval 1 Regular Conversion is Running
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsConversionOngoing(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_ADSTART_Msk, ADC0_CR_ADSTART_Pos));
}

/**
  * @brief  ADC Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADDIS_Msk);
}

/**
  * @brief  Judge is ADC Stopping or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 ADC has Stopped
  * @retval 1 ADC is Stopping
  */
__STATIC_INLINE uint32_t LL_ADC_IsDisableOngoing(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_ADDIS_Msk, ADC0_CR_ADDIS_Pos));
}

/**
  * @brief  ADC Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADEN_Msk);
}

/**
  * @brief  Judge is ADC Running or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 ADC isn't Running
  * @retval 1 ADC is Running
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_ADEN_Msk, ADC0_CR_ADEN_Pos));
}

/**
  * @brief  Auto-calibration Ratio Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ratio Auto-calibration Ratio @ref LL_ADC_OverSampRatioTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetAutoCalibrationRatio(ADC_TypeDef *ADCx, uint32_t Ratio)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, ADC0_CFGR0_OVSCAL_Msk, (((Ratio) & ADC0_CFGR0_OVSCAL_Val) << ADC0_CFGR0_OVSCAL_Pos));
}

/**
  * @brief  Auto-calibration Ratio Get
  * @param  ADCx Specifies ADC peripheral
  * @return Auto-calibration Ratio @ref LL_ADC_OverSampRatioTypeDef
  */
__STATIC_INLINE uint32_t LL_ADC_GetAutoCalibrationRatio(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CFGR0, ADC0_CFGR0_OVSCAL_Msk, ADC0_CFGR0_OVSCAL_Pos));
}

/**
  * @brief  Regular Conversion Mode Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Mode Regular Conversion Mode @ref LL_ADC_REG_ConvModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *ADCx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, ADC0_CFGR0_CONT_Msk, (((Mode) & ADC0_CFGR0_CONT_Val) << ADC0_CFGR0_CONT_Pos));
}

/**
  * @brief  Regular Conversion Mode Get
  * @param  ADCx Specifies ADC peripheral
  * @return Regular Conversion Mode @ref LL_ADC_REG_ConvModeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetContinuousMode(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CFGR0, ADC0_CFGR0_CONT_Msk, ADC0_CFGR0_CONT_Pos));
}

/**
  * @brief  Injected Auto Conversion Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_EnableTrigAuto(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR0, ADC0_CFGR0_JAUTO_Msk);
}

/**
  * @brief  Injected Auto Conversion Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_DisableTrigAuto(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR0, ADC0_CFGR0_JAUTO_Msk);
}

/**
  * @brief  Judge is Injected Auto Conversion Enable or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Injected Auto Conversion Enable
  * @retval 1 is Injected Auto Conversion Enable
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTrigAuto(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)((READ_BIT(ADCx->CFGR0, ADC0_CFGR0_JAUTO_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Injected Discontinuous Conversion Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_EnableSequencerDiscont(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR0, ADC0_CFGR0_JDISCEN_Msk);
}

/**
  * @brief  Injected Discontinuous Conversion Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_DisableSequencerDiscont(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR0, ADC0_CFGR0_JDISCEN_Msk);
}

/**
  * @brief  Judge is Injected Discontinuous Conversion Enable or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Injected Discontinuous Conversion Enable
  * @retval 1 is Injected Discontinuous Conversion Enable
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)((READ_BIT(ADCx->CFGR0, ADC0_CFGR0_JDISCEN_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Regular Discontinuous Conversion Numbers Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Num Regular Discontinuous Conversion Numbers @ref LL_ADC_REG_DisContConvNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerDiscontNumber(ADC_TypeDef *ADCx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, ADC0_CFGR0_DISCNUM_Msk, (((Num) & ADC0_CFGR0_DISCNUM_Val) << ADC0_CFGR0_DISCNUM_Pos));
}

/**
  * @brief  Regular Discontinuous Conversion Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_EnableSequencerDiscont(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR0, ADC0_CFGR0_DISCEN_Msk);
}

/**
  * @brief  Regular Discontinuous Conversion Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_DisableSequencerDiscont(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR0, ADC0_CFGR0_DISCEN_Msk);
}

/**
  * @brief  Judge is Regular Discontinuous Conversion Enable or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Regular Discontinuous Conversion Enable
  * @retval 1 is Regular Discontinuous Conversion Enable
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)((READ_BIT(ADCx->CFGR0, ADC0_CFGR0_DISCEN_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Overrun Mode Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Mode Overrun Mode @ref LL_ADC_OverRunModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetOverrun(ADC_TypeDef *ADCx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, ADC0_CFGR0_OVRMOD_Msk, (((Mode) & ADC0_CFGR0_OVRMOD_Val) << ADC0_CFGR0_OVRMOD_Pos));
}

/**
  * @brief  Trigger Over Sample Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableOverSamplingDiscont(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR0, ADC0_CFGR0_TROVS_Msk);
}

/**
  * @brief  Trigger Over Sample Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableOverSamplingDiscont(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR0, ADC0_CFGR0_TROVS_Msk);
}

/**
  * @brief  Over Sample Right Shift Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Shift Over Sample Right Shift bits @ref LL_ADC_OverSampShiftTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingRightShift(ADC_TypeDef *ADCx, uint32_t Shift)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, ADC0_CFGR0_OVSS_Msk, (((Shift) & ADC0_CFGR0_OVSS_Val) << ADC0_CFGR0_OVSS_Pos));
}

/**
  * @brief  Normal Channel Oversample Mode Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Mode Normal Channel Oversample Mode @ref LL_ADC_NormOverSampModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetNormalChannelOversampleMode(ADC_TypeDef *ADCx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, ADC0_CFGR0_ROVSM_Msk, (((Mode) & ADC0_CFGR0_ROVSM_Val) << ADC0_CFGR0_ROVSM_Pos));
}

/**
  * @brief  Over Sample Ratio Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ratio Over Sample Ratio @ref LL_ADC_OverSampRatioTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingRatio(ADC_TypeDef *ADCx, uint32_t Ratio)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, ADC0_CFGR0_OVSR_Msk, (((Ratio) & ADC0_CFGR0_OVSR_Val) << ADC0_CFGR0_OVSR_Pos));
}

/**
  * @brief  Oversampling Mode Config
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Oversampling Mode @ref LL_ADC_SamplingModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingScope(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR0, LL_ADC_CFGR0_OVERSAMPLING_MODE_MSK, (Mask & LL_ADC_CFGR0_OVERSAMPLING_MODE_MSK));
}

/**
  * @brief  Injected Oversample Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_EnableOverSampling(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR0, ADC0_CFGR0_JOVSE_Msk);
}

/**
  * @brief  Injected Oversample Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_DisableOverSampling(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR0, ADC0_CFGR0_JOVSE_Msk);
}

/**
  * @brief  Regular Oversample Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_EnableOverSampling(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR0, ADC0_CFGR0_ROVSE_Msk);
}

/**
  * @brief  Regular Oversample Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_DisableOverSampling(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR0, ADC0_CFGR0_ROVSE_Msk);
}

/**
  * @brief  AWDG2 Monitor Injected Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWD2MonitorInjected(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_JAWD2EN_Msk);
}

/**
  * @brief  AWDG2 Monitor Injected Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWD2MonitorInjected(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_JAWD2EN_Msk);
}

/**
  * @brief  AWDG1 Monitor Injected Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWD1MonitorInjected(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_JAWD1EN_Msk);
}

/**
  * @brief  AWDG1 Monitor Injected Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWD1MonitorInjected(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_JAWD1EN_Msk);
}

/**
  * @brief  AWDG0 Monitor Injected Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWD0MonitorInjected(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_JAWD0EN_Msk);
}

/**
  * @brief  AWDG0 Monitor Injected Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWD0MonitorInjected(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_JAWD0EN_Msk);
}

/**
  * @brief  AWDG Monitor Injected Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWDxMonitorInjected(ADC_TypeDef *ADCx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, BIT(((Num) % LL_ADC_AWDG_NUMS) + ADC0_CFGR1_JAWD0EN_Pos));
}

/**
  * @brief  AWDG Monitor Injected Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWDxMonitorInjected(ADC_TypeDef *ADCx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, BIT(((Num) % LL_ADC_AWDG_NUMS) + ADC0_CFGR1_JAWD0EN_Pos));
}

/**
  * @brief  AWDG2 Monitor Regular Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWD2MonitorRegular(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_AWD2EN_Msk);
}

/**
  * @brief  AWDG2 Monitor Regular Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWD2MonitorRegular(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_AWD2EN_Msk);
}

/**
  * @brief  AWDG1 Monitor Regular Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWD1MonitorRegular(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_AWD1EN_Msk);
}

/**
  * @brief  AWDG1 Monitor Regular Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWD1MonitorRegular(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_AWD1EN_Msk);
}

/**
  * @brief  AWDG0 Monitor Regular Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWD0MonitorRegular(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_AWD0EN_Msk);
}

/**
  * @brief  AWDG0 Monitor Regular Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWD0MonitorRegular(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_AWD0EN_Msk);
}

/**
  * @brief  AWDG Monitor Regular Sequence Enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWDxMonitorRegular(ADC_TypeDef *ADCx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, BIT(((Num) % LL_ADC_AWDG_NUMS) + ADC0_CFGR1_AWD0EN_Pos));
}

/**
  * @brief  AWDG Monitor Regular Sequence Disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWDxMonitorRegular(ADC_TypeDef *ADCx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, BIT(((Num) % LL_ADC_AWDG_NUMS) + ADC0_CFGR1_AWD0EN_Pos));
}

/**
  * @brief  ADC Bias Current Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Cur ADC Bias Current @ref LL_ADC_BiasCurTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetBiasCurrent(ADC_TypeDef *ADCx, uint32_t Cur)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CFGR1, ADC0_CFGR1_ISEL_Msk, (((Cur) & ADC0_CFGR1_ISEL_Val) << ADC0_CFGR1_ISEL_Pos));
}

/**
  * @brief  ADC Channel Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableChannel(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_CHEN_Msk);
}

/**
  * @brief  ADC Channel Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableChannel(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_CHEN_Msk);
}

/**
  * @brief  ADC Reference Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableReference(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_REFEN_Msk);
}

/**
  * @brief  ADC Reference Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableReference(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_REFEN_Msk);
}

/**
  * @brief  ADC Bias Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableBias(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, ADC0_CFGR1_BIASEN_Msk);
}

/**
  * @brief  ADC Bias Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableBias(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_BIASEN_Msk);
}

/**
  * @brief  Preparing Start ADC Assert
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_AssertPreparingStart(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CFGR1, LL_ADC_CFGR1_PREPARING_START_MSK);
}

/**
  * @brief  Preparing Start ADC Release
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ReleasePreparingStart(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->CFGR1, LL_ADC_CFGR1_PREPARING_START_MSK);
}

/**
  * @brief  Judge is Sample End Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Sample End Interrupt Pending
  * @retval 1 is Sample End Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOSMP(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_EOSMP_Msk, ADC0_ISR_EOSMP_Pos));
}

/**
  * @brief  Sample End Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOSMP(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_EOSMP_Msk);
}

/**
  * @brief  Judge is ADC Ready Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't ADC Ready Interrupt Pending
  * @retval 1 is ADC Ready Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_ADRDY(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_ADRDY_Msk, ADC0_ISR_ADRDY_Pos));
}

/**
  * @brief  ADC Ready Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_ADRDY(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_ADRDY_Msk);
}

/**
  * @brief  Judge is AWDG2 Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't AWDG2 Interrupt Pending
  * @retval 1 is AWDG2 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD3(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_AWD2_Msk, ADC0_ISR_AWD2_Pos));
}

/**
  * @brief  AWDG2 Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD3(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_AWD2_Msk);
}

/**
  * @brief  Judge is AWDG1 Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't AWDG1 Interrupt Pending
  * @retval 1 is AWDG1 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD2(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_AWD1_Msk, ADC0_ISR_AWD1_Pos));
}

/**
  * @brief  AWDG1 Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD2(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_AWD1_Msk);
}

/**
  * @brief  Judge is AWDG0 Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't AWDG0 Interrupt Pending
  * @retval 1 is AWDG0 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD1(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_AWD0_Msk, ADC0_ISR_AWD0_Pos));
}

/**
  * @brief  AWDG0 Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD1(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_AWD0_Msk);
}

/**
  * @brief  Judge is Overflow Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Overflow Interrupt Pending
  * @retval 1 is Overflow Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVR(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_OVR_Msk, ADC0_ISR_OVR_Pos));
}

/**
  * @brief  Overflow Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVR(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_OVR_Msk);
}

/**
  * @brief  Judge is Injected Sequence End Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Injected Sequence End Interrupt Pending
  * @retval 1 is Injected Sequence End Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOS(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_JEOS_Msk, ADC0_ISR_JEOS_Pos));
}

/**
  * @brief  Injected Sequence End Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_JEOS_Msk);
}

/**
  * @brief  Judge is Injected Conversion End Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Injected Conversion End Interrupt Pending
  * @retval 1 is Injected Conversion End Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOC(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_JEOC_Msk, ADC0_ISR_JEOC_Pos));
}

/**
  * @brief  Injected Conversion End Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOC(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_JEOC_Msk);
}

/**
  * @brief  Judge is Regular Sequence End Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Regular Sequence End Interrupt Pending
  * @retval 1 is Regular Sequence End Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOS(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_EOS_Msk, ADC0_ISR_EOS_Pos));
}

/**
  * @brief  Regular Sequence End Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOS(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_EOS_Msk);
}

/**
  * @brief  Judge is Regular Conversion End Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't Regular Conversion End Interrupt Pending
  * @retval 1 is Regular Conversion End Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOC(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_EOC_Msk, ADC0_ISR_EOC_Pos));
}

/**
  * @brief  Regular Conversion End Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOC(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, ADC0_ISR_EOC_Msk);
}

/**
  * @brief  ADC Normal All Interrupt Pending Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Normal All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_GetNormalChannelsITPending(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->ISR));
}

/**
  * @brief  Sample End Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOSMP(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_EOSMPIE_Msk);
}

/**
  * @brief  Sample End Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOSMP(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_EOSMPIE_Msk);
}

/**
  * @brief  ADC Ready Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_ADRDY(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_ADRDYIE_Msk);
}

/**
  * @brief  ADC Ready Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_ADRDY(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_ADRDYIE_Msk);
}

/**
  * @brief  AWDG2 Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWDG2(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_AWD2IE_Msk);
}

/**
  * @brief  AWDG2 Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWDG2(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_AWD2IE_Msk);
}

/**
  * @brief  AWDG1 Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWDG1(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_AWD1IE_Msk);
}

/**
  * @brief  AWDG1 Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWDG1(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_AWD1IE_Msk);
}

/**
  * @brief  AWDG0 Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWDG0(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_AWD0IE_Msk);
}

/**
  * @brief  AWDG0 Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWDG0(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_AWD0IE_Msk);
}

/**
  * @brief  Overflow Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_OVR(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_OVRIE_Msk);
}

/**
  * @brief  Overflow Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_OVR(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_OVRIE_Msk);
}

/**
  * @brief  Injected Sequence End Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOS(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_JEOSIE_Msk);
}

/**
  * @brief  Injected Sequence End Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOS(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_JEOSIE_Msk);
}

/**
  * @brief  Injected Conversion End Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOC(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_JEOCIE_Msk);
}

/**
  * @brief  Injected Conversion End Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOC(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_JEOCIE_Msk);
}

/**
  * @brief  Regular Sequence End Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOS(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_EOSIE_Msk);
}

/**
  * @brief  Regular Sequence End Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOS(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_EOSIE_Msk);
}

/**
  * @brief  Regular Conversion End Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOC(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, ADC0_IER_EOCIE_Msk);
}

/**
  * @brief  Regular Conversion End Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOC(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, ADC0_IER_EOCIE_Msk);
}

/**
  * @brief  ADC Normal All Interrupt Enable Status Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Normal All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_ADC_GetNormAllInterruptEnable(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->IER));
}

/**
  * @brief  ADC Channel Conversion Mode Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  Mode ADC Channel Conversion Mode @ref LL_ADC_InputModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetChannelSingleDiff(ADC_TypeDef *ADCx, uint32_t Ch, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->SIGSEL, BIT(Ch % LL_ADC_CH_NUMS), (((Mode) & 0x1UL) << (Ch % LL_ADC_CH_NUMS)));
}

/**
  * @brief  ADC Channel Sample Time Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  Time ADC Channel Sample Time @ref LL_ADC_SampTimeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Ch, uint32_t Time)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(LL_ADC_REG_OFFSET(ADCx->SMPR0, Ch / 8 % ((LL_ADC_CH_NUMS + 7) / 8)), 
              (ADC0_SMPR0_SMP0_Msk >> ADC0_SMPR0_SMP0_Pos) << ((Ch % 8) * 4), 
              (((Time) & (ADC0_SMPR0_SMP0_Msk >> ADC0_SMPR0_SMP0_Pos)) << ((Ch % 8) * 4)));
}

/**
  * @brief  ADC Channel Calibration Coefficient Group Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  Grp Calibration Coefficient Group @ref LL_ADC_CalCoefGrpTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetCalibrationFactor(ADC_TypeDef *ADCx, uint32_t Ch, uint32_t Grp)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(LL_ADC_REG_OFFSET(ADCx->CALR0, Ch / 8 % ((LL_ADC_CH_NUMS + 7) / 8)), 
              (ADC0_CALR0_CAL0_Msk >> ADC0_CALR0_CAL0_Pos) << ((Ch % 8) * 4), 
              (((Grp) & (ADC0_CALR0_CAL0_Msk >> ADC0_CALR0_CAL0_Pos)) << ((Ch % 8) * 4)));
}

/**
  * @brief  ADC Channel Saturation Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  Sat_dis Saturation Disable @ref LL_ADC_ChSaturationTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetChannelSaturation(ADC_TypeDef *ADCx, uint32_t Ch, uint32_t Sat_dis)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(LL_ADC_REG_OFFSET(ADCx->CALR0, Ch / 8 % ((LL_ADC_CH_NUMS + 7) / 8)), 
              0x1UL << (3 + (Ch % 8) * 4), 
              (((!!Sat_dis) & 0x1UL) << (3 + (Ch % 8) * 4)));
}

/**
  * @brief  ADC Regular Sequence Channel Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Seq Regular Sequence Number @ref LL_ADC_REG_SeqNumTypeDef
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Seq, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(LL_ADC_REG_OFFSET(ADCx->SQR0, Seq / 5 % ((LL_ADC_REG_SEQ_NUMS + 4) / 5)), 
              (ADC0_SQR0_SQ1_Msk >> ADC0_SQR0_SQ1_Pos) << ((Seq % 5) * 6), 
              (((Ch) & (ADC0_SQR0_SQ1_Msk >> ADC0_SQR0_SQ1_Pos)) << ((Seq % 5) * 6)));
}

/**
  * @brief  Regular Sequence Length Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Len Regular Sequence Length @ref LL_ADC_REG_SeqLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->LR, ADC0_LR_LEN_Msk, (((Len) & ADC0_LR_LEN_Val) << ADC0_LR_LEN_Pos));
}

/**
  * @brief  Regular Sequence Length Get
  * @param  ADCx Specifies ADC peripheral
  * @return Regular Sequence Length @ref LL_ADC_REG_SeqLenTypeDef
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerLength(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->LR, ADC0_LR_LEN_Msk, ADC0_LR_LEN_Pos));
}

/**
  * @brief  Regular Sequence Trigger Polarity Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Pol Regular Sequence Trigger Polarity @ref LL_ADC_SeqTrigPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->LR, ADC0_LR_EXTEN_Msk, (((Pol) & ADC0_LR_EXTEN_Val) << ADC0_LR_EXTEN_Pos));
}

/**
  * @brief  Regular Sequence Trigger Polarity Get
  * @param  ADCx Specifies ADC peripheral
  * @return Regular Sequence Trigger Polarity @ref LL_ADC_SeqTrigPolTypeDef
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->LR, ADC0_LR_EXTEN_Msk, ADC0_LR_EXTEN_Pos));
}

/**
  * @brief  Regular Sequence Trigger Event Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Evt Regular Sequence Trigger Event @ref LL_ADC_SeqTrigEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->LR, ADC0_LR_EXTSEL_Msk, (((Evt) & ADC0_LR_EXTSEL_Val) << ADC0_LR_EXTSEL_Pos));
}

/**
  * @brief  Regular Sequence Data Read
  * @param  ADCx Specifies ADC peripheral
  * @return Regular Sequence Data
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadConversionData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->DR, ADC0_DR_RDATA_Msk, ADC0_DR_RDATA_Pos));
}

/**
  * @brief   ADC Maximum Regular Data Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Val ADC Maximum Regular Dat
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetMaxData(ADC_TypeDef *ADCx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->MAXDR, ADC0_MAXDR_MAXDATA_Msk, (((Val) & ADC0_MAXDR_MAXDATA_Val) << ADC0_MAXDR_MAXDATA_Pos));
}

/**
  * @brief   ADC Maximum Regular Data Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Maximum Regular Dat
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetMaxData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->MAXDR, ADC0_MAXDR_MAXDATA_Msk, ADC0_MAXDR_MAXDATA_Pos));
}

/**
  * @brief   ADC Minimum Regular Data Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Val ADC Minimum Regular Dat
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_SetMinData(ADC_TypeDef *ADCx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->MINDR, ADC0_MINDR_MINDATA_Msk, (((Val) & ADC0_MINDR_MINDATA_Val) << ADC0_MINDR_MINDATA_Pos));
}

/**
  * @brief   ADC Minimum Regular Data Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Minimum Regular Dat
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetMinData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->MINDR, ADC0_MINDR_MINDATA_Msk, ADC0_MINDR_MINDATA_Pos));
}

/**
  * @brief  ADC Injected Sequence Channel Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Seq Injected Sequence Number @ref LL_ADC_INJ_SeqNumTypeDef
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Seq, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->JSQR, (ADC0_JSQR_JSQ1_Val) << ((Seq % LL_ADC_INJ_SEQ_NUMS) * 6), 
              (((Ch) & (ADC0_JSQR_JSQ1_Val)) << ((Seq % LL_ADC_INJ_SEQ_NUMS) * 6)));
}

/**
  * @brief  Injected Sequence Length Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Len Injected Sequence Length @ref LL_ADC_INJ_SeqLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->JLR, ADC0_JLR_JLEN_Msk, (((Len) & ADC0_JLR_JLEN_Val) << ADC0_JLR_JLEN_Pos));
}

/**
  * @brief  Injected Sequence Length Get
  * @param  ADCx Specifies ADC peripheral
  * @return Injected Sequence Length @ref LL_ADC_INJ_SeqLenTypeDef
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerLength(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->JLR, ADC0_JLR_JLEN_Msk, ADC0_JLR_JLEN_Pos));
}

/**
  * @brief  Injected Sequence Trigger Polarity Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Pol Injected Sequence Trigger Polarity @ref LL_ADC_SeqTrigPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->JLR, ADC0_JLR_JEXTEN_Msk, (((Pol) & ADC0_JLR_JEXTEN_Val) << ADC0_JLR_JEXTEN_Pos));
}

/**
  * @brief  Injected Sequence Trigger Polarity Get
  * @param  ADCx Specifies ADC peripheral
  * @return Injected Sequence Trigger Polarity @ref LL_ADC_SeqTrigPolTypeDef
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->JLR, ADC0_JLR_JEXTEN_Msk, ADC0_JLR_JEXTEN_Pos));
}

/**
  * @brief  Injected Sequence Trigger Event Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Evt Injected Sequence Trigger Event @ref LL_ADC_SeqTrigEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->JLR, ADC0_JLR_JEXTSEL_Msk, (((Evt) & ADC0_JLR_JEXTSEL_Val) << ADC0_JLR_JEXTSEL_Pos));
}

/**
  * @brief   ADC Maximum Injected Data Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Val ADC Maximum Injected Dat
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_SetMaxData(ADC_TypeDef *ADCx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->MAXJDR, ADC0_MAXJDR_MAXDATA_Msk, (((Val) & ADC0_MAXJDR_MAXDATA_Val) << ADC0_MAXJDR_MAXDATA_Pos));
}

/**
  * @brief   ADC Maximum Injected Data Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Maximum Injected Dat
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetMaxData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->MAXJDR, ADC0_MAXJDR_MAXDATA_Msk, ADC0_MAXJDR_MAXDATA_Pos));
}

/**
  * @brief   ADC Minimum Injected Data Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Val ADC Minimum Injected Dat
  * @return None
  */
__STATIC_INLINE void LL_ADC_INJ_SetMinData(ADC_TypeDef *ADCx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->MINJDR, ADC0_MINJDR_MINDATA_Msk, (((Val) & ADC0_MINJDR_MINDATA_Val) << ADC0_MINJDR_MINDATA_Pos));
}

/**
  * @brief   ADC Minimum Injected Data Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Minimum Injected Dat
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetMinData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->MINJDR, ADC0_MINJDR_MINDATA_Msk, ADC0_MINJDR_MINDATA_Pos));
}

/**
  * @brief  Injected Sequence Data Read
  * @param  ADCx Specifies ADC peripheral
  * @param  Seq Injected Sequence Number @ref LL_ADC_INJ_SeqNumTypeDef
  * @return Injected Sequence Data
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_ReadConversionData(const ADC_TypeDef *ADCx, uint32_t Seq)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(LL_ADC_REG_OFFSET(ADCx->JDR0, ((Seq) % LL_ADC_INJ_SEQ_NUMS))));
}

/**
  * @brief  AWDG Threshold High Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @param  Thres AWDG Threshold High
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDThresholdHigh(ADC_TypeDef *ADCx, uint32_t Num, int16_t Thres)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(LL_ADC_REG_OFFSET(ADCx->TR0, ((Num) % LL_ADC_AWDG_NUMS)), 
              ADC0_TR0_HT0_Msk, ((((uint32_t)Thres) & ADC0_TR0_HT0_Val) << ADC0_TR0_HT0_Pos));
}

/**
  * @brief  AWDG Threshold Low Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @param  Thres AWDG Threshold Low
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDThresholdLow(ADC_TypeDef *ADCx, uint32_t Num, int16_t Thres)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(LL_ADC_REG_OFFSET(ADCx->TR0, ((Num) % LL_ADC_AWDG_NUMS)), 
              ADC0_TR0_LT0_Msk, ((((uint32_t)Thres) & ADC0_TR0_LT0_Val) << ADC0_TR0_LT0_Pos));
}

/**
  * @brief  AWDG Filter Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @param  Fil AWDG Filter @ref LL_ADC_AWDG_FilterPointNumsTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetAWDFilteringConfiguration(ADC_TypeDef *ADCx, uint32_t Num, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(LL_ADC_REG_OFFSET(ADCx->AWD0CR, ((Num) % LL_ADC_AWDG_NUMS)), 
              ADC0_AWD0CR_AWDFILT_Msk, (((Fil) & ADC0_AWD0CR_AWDFILT_Val) << ADC0_AWD0CR_AWDFILT_Pos));
}

/**
  * @brief  AWDG Channel Monitor Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @param  Mask Channel Number Mask, combination of @ref LL_ADC_AWDG_MONITOR_CHANNEL_MSK, bit0 represents channel1...
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDChannelMonitor(ADC_TypeDef *ADCx, uint32_t Num, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(LL_ADC_REG_OFFSET(ADCx->AWD0CR, ((Num) % LL_ADC_AWDG_NUMS)), (Mask & ADC0_AWD0CR_AW0CH_Val));
}

/**
  * @brief  AWDG Channel Monitor Reset
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @param  Mask Channel Number Mask, combination of @ref LL_ADC_AWDG_MONITOR_CHANNEL_MSK, bit0 represents channel1...
  * @return None
  */
__STATIC_INLINE void LL_ADC_ResetAnalogWDChannelMonitor(ADC_TypeDef *ADCx, uint32_t Num, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(LL_ADC_REG_OFFSET(ADCx->AWD0CR, ((Num) % LL_ADC_AWDG_NUMS)), (Mask & ADC0_AWD0CR_AW0CH_Val));
}

/**
  * @brief  AWDG Channel Monitor Enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableAnalogWDChannelMonitor(ADC_TypeDef *ADCx, uint32_t Num, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(LL_ADC_REG_OFFSET(ADCx->AWD0CR, ((Num) % LL_ADC_AWDG_NUMS)), BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  AWDG Channel Monitor Disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Num AWDG Number @ref LL_ADC_AWDG_NumTypeDef
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableAnalogWDChannelMonitor(ADC_TypeDef *ADCx, uint32_t Num, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(LL_ADC_REG_OFFSET(ADCx->AWD0CR, ((Num) % LL_ADC_AWDG_NUMS)), BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Offset Coefficient Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Grp Calibration Coefficient Group @ref LL_ADC_CalCoefGrpTypeDef
  * @param  Coef Offset Coefficient
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetOffset(ADC_TypeDef *ADCx, uint32_t Grp, int16_t Coef)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(LL_ADC_REG_OFFSET(ADCx->OFR0, ((Grp) % LL_ADC_CAL_COEF_GRP_NUMS)), (((uint32_t)Coef) & ADC0_OFR0_OFFSET_Val));
}

/**
  * @brief  Offset Coefficient Get
  * @param  ADCx Specifies ADC peripheral
  * @param  Grp Calibration Coefficient Group @ref LL_ADC_CalCoefGrpTypeDef
  * @param  Coef 
  * @return Offset Coefficient
  */
__STATIC_INLINE int16_t LL_ADC_GetOffset(ADC_TypeDef *ADCx, uint32_t Grp)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return ((int16_t)READ_BIT_SHIFT(LL_ADC_REG_OFFSET(ADCx->OFR0, ((Grp) % LL_ADC_CAL_COEF_GRP_NUMS)), 
                                    ADC0_OFR0_OFFSET_Msk, ADC0_OFR0_OFFSET_Pos));
}

/**
  * @brief  Gain Coefficient Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Grp Calibration Coefficient Group @ref LL_ADC_CalCoefGrpTypeDef
  * @param  Coef Gain Coefficient
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetGainCompensation(ADC_TypeDef *ADCx, uint32_t Grp, uint32_t Coef)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(LL_ADC_REG_OFFSET(ADCx->GCR0, ((Grp) % LL_ADC_CAL_COEF_GRP_NUMS)), ((Coef) & ADC0_GCR0_COEFF_Val));
}

/**
  * @brief  Judge is Channel Conversion Done Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 isn't Channel Conversion Done Interrupt Pending
  * @retval 1 is Channel Conversion Done Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_DONx(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->DISR, BIT(((Ch) % LL_ADC_CH_NUMS)), ((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Channel Conversion Done Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_DONx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->DISR, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  ADC Sample All Interrupt Pending Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Sample All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_GetAllSampleITPending(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->DISR));
}

/**
  * @brief  Channel Conversion Done Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_DONIEx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->DIER, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Channel Conversion Done Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_DONIEx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->DIER, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Judge is Channel Conversion Done Interrupt Enable or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 Channel Conversion Done Interrupt is Disable
  * @retval 1 Channel Conversion Done Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_DONIEx(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->DIER, BIT(((Ch) % LL_ADC_CH_NUMS)), ((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  ADC Sample All Interrupt Enable Status Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC Sample All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_ADC_GetAllSampleEnabledIT(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->DIER));
}

/**
  * @brief  Channel Data Read
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return Channel Data
  */
__STATIC_INLINE uint32_t LL_ADC_ReadChannelData(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(LL_ADC_REG_OFFSET(ADCx->CDR0, ((Ch) % LL_ADC_CH_NUMS)), 
                      ADC0_CDR0_CDATA_Msk, ADC0_CDR0_CDATA_Pos));
}

/**
  * @brief  Judge is Channel DMA Transfer Half Complete Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 isn't Channel DMA Transfer Half Complete Interrupt Pending
  * @retval 1 is Channel DMA Transfer Half Complete Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_HLFx(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->HISR, BIT(((Ch) % LL_ADC_CH_NUMS)), ((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Channel DMA Transfer Half Complete Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_HLFx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->HISR, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  ADC DMA Transfer Half Complete All Interrupt Pending Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC DMA Transfer Half Complete All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_GetAllHalfCpltITPending(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->HISR));
}

/**
  * @brief  Channel DMA Transfer Half Complete Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_HLFIEx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->HIER, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Channel DMA Transfer Half Complete Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_HLFIEx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->HIER, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Judge is Channel DMA Transfer Half Complete Interrupt Enable or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 Channel DMA Transfer Half Complete Interrupt is Disable
  * @retval 1 Channel DMA Transfer Half Complete Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_HLFIEx(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->HIER, BIT(((Ch) % LL_ADC_CH_NUMS)), ((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  ADC DMA Transfer Half Complete All Interrupt Enable Status Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC DMA Transfer Half Complete All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_ADC_GetAllHalfCpltEnabledIT(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->HIER));
}

/**
  * @brief  Judge is Channel DMA Transfer Complete Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 isn't Channel DMA Transfer Complete Interrupt Pending
  * @retval 1 is Channel DMA Transfer Complete Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_FULx(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->FISR, BIT(((Ch) % LL_ADC_CH_NUMS)), ((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Channel DMA Transfer Complete Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_FULx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->FISR, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  ADC DMA Transfer Complete All Interrupt Pending Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC DMA Transfer Complete All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_GetAllCpltITPending(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->FISR));
}

/**
  * @brief  Channel DMA Transfer Complete Interrupt Enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT_FULIEx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->FIER, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Channel DMA Transfer Complete Interrupt Disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT_FULIEx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->FIER, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Judge is Channel DMA Transfer Complete Interrupt Enable or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 Channel DMA Transfer Complete Interrupt is Disable
  * @retval 1 Channel DMA Transfer Complete Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_FULIEx(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->FIER, BIT(((Ch) % LL_ADC_CH_NUMS)), ((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  ADC DMA Transfer Complete All Interrupt Enable Status Get
  * @param  ADCx Specifies ADC peripheral
  * @return ADC DMA Transfer Complete All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_ADC_GetAllCpltEnabledIT(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->FIER));
}

/**
  * @brief  Channel DMA Fix Address Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  En DMA Fix Address Enable @ref LL_ADC_DMAFixAddrEnTypeDef
  * @return Channel Data
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_SetChannelFixAddress(const ADC_TypeDef *ADCx, uint32_t Ch, uint32_t En)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(MODIFY_REG(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, ((Ch) % LL_ADC_CH_NUMS)).TCR, 
                                ADC0_TCR0_FIX_Msk, ((!!(En)) << ADC0_TCR0_FIX_Pos)));
}

/**
  * @brief  Channel DMA Circulation Mode Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  En DMA Circulation Mode Enable @ref LL_ADC_DMACircModeEnTypeDef
  * @return Channel Data
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_SetChannelCirculationMode(const ADC_TypeDef *ADCx, uint32_t Ch, uint32_t En)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(MODIFY_REG(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, ((Ch) % LL_ADC_CH_NUMS)).TCR, 
                                ADC0_TCR0_CIRC_Msk, ((!!(En)) << ADC0_TCR0_CIRC_Pos)));
}

/**
  * @brief  Channel DMA Stop
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_ChannelStop(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, ((Ch) % LL_ADC_CH_NUMS)).TCR, ADC0_TCR0_STP_Msk);
}

/**
  * @brief  Judge is Channel DMA Stopping or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 isn't Channel DMA Stopping
  * @retval 1 is Channel DMA Stopping
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_IsStopping(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, ((Ch) % LL_ADC_CH_NUMS)).TCR, 
                                    ADC0_TCR0_STP_Msk, ADC0_TCR0_STP_Pos));
}

/**
  * @brief  Channel DMA Start
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_ChannelStart(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, ((Ch) % LL_ADC_CH_NUMS)).TCR, ADC0_TCR0_START_Msk);
}

/**
  * @brief  Channel DMA Transfer Address Set
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  Addr Channel DMA Transfer Address
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_SetTransferAddress(ADC_TypeDef *ADCx, uint32_t Ch, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, ((Ch) % LL_ADC_CH_NUMS)).TAR, ((Addr) & ADC0_TAR0_ADDR_Val));
}

/**
  * @brief  Channel DMA Transfer Length Set 
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @param  Len Channel DMA Transfer Length in bytes
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_SetTransferLength(ADC_TypeDef *ADCx, uint32_t Ch, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, ((Ch) % LL_ADC_CH_NUMS)).TLR, ((Len) & ADC0_TLR0_LENG_Val));
}

/**
  * @brief  Daul ADC Sample Phase Delay Set
  * @note   Only Master ADC Valid
  * @param  ADCx Specifies ADC peripheral
  * @param  Dly Daul ADC Sample Phase Delay
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetMultiTwoSamplingDelay(ADC_TypeDef *ADCx, uint32_t Dly)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CCR, ADC0_CCR_DELAY_Msk, (((Dly) & ADC0_CCR_DELAY_Val) << ADC0_CCR_DELAY_Pos));
}

/**
  * @brief  Daul ADC Mode Set
  * @note   Dual mode Only Master ADC Valid
  *         Quad mode Only Master ADC0/2 Valid
  * @param  ADCx Specifies ADC peripheral
  * @param  Mode Daul ADC Mode
  * @return None
  */
__STATIC_INLINE void LL_ADC_SetMultimode(ADC_TypeDef *ADCx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    MODIFY_REG(ADCx->CCR, ADC0_CCR_DUAL_Msk, (((Mode) & ADC0_CCR_DUAL_Val) << ADC0_CCR_DUAL_Pos));
}


/**
  * @brief  Read Master ADC Interrupt Pengding  
  * @note   Only the master ADC reading is valid.
  * @param  ADCx Specifies ADC peripheral
  * @return Master ADC Interrupt Pengding in Dual ADC Mode
  */
__STATIC_INLINE uint32_t LL_ADC_GetMasterITPending(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_MASTER_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CSR, LL_ADC_CSR_MST_IT_FLAG_MSK, ADC0_CSR_EOC_MST_Pos));
}

/**
  * @brief  Read Slave ADC Interrupt Pengding  
  * @note   Only the master ADC reading is valid.
  * @param  ADCx Specifies ADC peripheral 
  * @return Slave ADC Interrupt Pengding in Dual ADC Mode
  */
__STATIC_INLINE uint32_t LL_ADC_GetSlaveITPending(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_MASTER_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CSR, LL_ADC_CSR_SLV_IT_FLAG_MSK, ADC0_CSR_EOC_SLV_Pos));
}


/**
  * @brief  Read converted data of master ADC regular sequence 
  * @note   Only the master ADC reading is valid.
  * @param  ADCx Specifies ADC peripheral
  * @return Converted data of master ADC regular sequence 
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetMasterConvData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_MASTER_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CDR, ADC0_CDR_RDATA_MST_Msk, ADC0_CDR_RDATA_MST_Pos));
}

/**
  * @brief  Read converted data of slave ADC regular sequence 
  * @note   Only the master ADC reading is valid.
  * @param  ADCx Specifies ADC peripheral
  * @return Converted data of slave ADC regular sequence 
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSlaveConvData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_MASTER_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->CDR, ADC0_CDR_RDATA_SLV_Msk, ADC0_CDR_RDATA_SLV_Pos));
}

/**
  * @brief  Set ADC0 CFGR0 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to CFGR0.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetConfig(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->CFGR0, Value);
}

/**
  * @brief  Get ADC0 CFGR0 register.
  * @param  ADCx Specifies ADC peripheral.
  * @return CFGR0 register value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetConfig(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->CFGR0));
}

/**
  * @brief  Set ADC0 CFGR1 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to CFGR1.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetConfigEx(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->CFGR1, Value);
}

/**
  * @brief  Get ADC0 CFGR1 register.
  * @param  ADCx Specifies ADC peripheral.
  * @return CFGR1 register value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetConfigEx(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->CFGR1));
}

/**
  * @brief  Set ADC0 SIGSEL register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to SIGSEL.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetDifferEnd(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->SIGSEL, Value);
}

/**
  * @brief  Get ADC0 SIGSEL register.
  * @param  ADCx Specifies ADC peripheral.
  * @return SIGSEL register value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetDifferEnd(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->SIGSEL));
}

/**
  * @brief  Set ADC0 SMPR2 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to SMPR2.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetSamlpeTime(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->SMPR2, Value);
}

/**
  * @brief  Get ADC0 SMPR2 register.
  * @param  ADCx Specifies ADC peripheral.
  * @return SMPR2 register value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetSamlpeTime(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->SMPR2));
}

/**
  * @brief  Set ADC0 SQR0 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to SQR0.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetRegularSequence(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->SQR0, Value);
}

/**
  * @brief  Get ADC0 SQR0 register.
  * @param  ADCx Specifies ADC peripheral.
  * @return SQR0 register value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetRegularSequence(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->SQR0));
}

/**
  * @}
  */ /* ADC_LL_EF_Configuration */

/** @defgroup ADC_LL_EF_IT_Management LL ADC Interrupt Management
  * @brief LL ADC Interrupt Management
  * @{
  */

/**
  * @brief  ADC Interrupt enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to enable @ref LL_ADC_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->IER, Mask);
}

/**
  * @brief  ADC Interrupt disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to disable @ref LL_ADC_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->IER, Mask);
}

/**
  * @brief  Check if ADC Interrupt is enabled or disabled
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_IER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to clear @ref LL_ADC_ISR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->ISR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_ISR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->ISR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  ADC Data Interrupt enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to enable @ref LL_ADC_DIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_EnableDataIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->DIER, Mask);
}

/**
  * @brief  ADC Data Interrupt disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to disable @ref LL_ADC_DIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DisableDataIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->DIER, Mask);
}

/**
  * @brief  Check if ADC Data Interrupt is enabled or disabled
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_DIER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledDataIT(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->DIER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear ADC Data Interrupt Pending
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_DISR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearDataFlag(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->DISR, Mask);
}

/**
  * @brief  Get ADC Data Interrupt Pending.
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_DISR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveDataFlag(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->DISR, Mask) == (Mask)) ? 1UL : 0UL);
}


/**
  * @brief  ADC DMA Full Interrupt enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to enable @ref LL_ADC_FIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_EnableFullIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->FIER, Mask);
}

/**
  * @brief  ADC DMA Full Interrupt disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to disable @ref LL_ADC_FIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_DisableFullIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->FIER, Mask);
}

/**
  * @brief  Check if ADC DMA Full Interrupt is enabled or disabled
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_FIER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_IsEnableFullIT(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->FIER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear DMA Full Interrupt Pending
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_FISR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_ClearFullFlag(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->FISR, Mask);
}

/**
  * @brief  Get DMA Full Interrupt Pending.
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_FISR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_IsActiveFullFlag(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->FISR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  ADC DMA Half Full Interrupt enable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to enable @ref LL_ADC_HIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_EnableHalfFullIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->HIER, Mask);
}

/**
  * @brief  ADC DMA Half Full Interrupt disable
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to disable @ref LL_ADC_HIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_DisableHalfFullIT(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    CLEAR_BIT(ADCx->HIER, Mask);
}

/**
  * @brief  Check if ADC DMA Half Full Interrupt is enabled or disabled
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_HIER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_IsEnableHalfFullIT(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->HIER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear DMA Half Full Interrupt Pending
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_HISR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_DMA_ClearHalfFullFlag(ADC_TypeDef *ADCx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->HISR, Mask);
}

/**
  * @brief  Get DMA Half Full Interrupt Pending.
  * @param  ADCx Specifies ADC peripheral
  * @param  Mask Mask to check @ref LL_ADC_HISR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_IsActiveHalfFullFlag(const ADC_TypeDef *ADCx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADCx->HISR, Mask) == (Mask)) ? 1UL : 0UL);
}


/**
  * @}
  */ /* ADC_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* ADC_LL_Exported_Functions */

/**
  * @}
  */ /* ADC_LL */

#endif /* ADC */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_ADC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

