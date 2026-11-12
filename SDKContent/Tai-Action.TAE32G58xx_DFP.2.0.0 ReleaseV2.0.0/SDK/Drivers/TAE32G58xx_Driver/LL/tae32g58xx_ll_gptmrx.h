/**
  ******************************************************************************
  * @file    tae32g58xx_ll_gptmrx.h
  * @author  Tai-Action SD Team
  * @brief   Header file for GPTMRX (General Purpose Timer) LL module
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
#ifndef _TAE32G58XX_LL_GPTMRX_H_
#define _TAE32G58XX_LL_GPTMRX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(TMR0) || defined(TMR1) || defined(TMR2)

/** @defgroup GPTMRX_LL GPTMRX LL
  * @brief    GPTMRX LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup GPTMRX_LL_Exported_Constants GPTMRX LL Exported Constants
  * @brief    GPTMRX LL Exported Constants
  * @{
  */

/** @name LL_GPTMRX_IER_ITEnMskTypeDef
  * @brief GPTMRX LL Interrupt Enable Masks
  * @{
  */
#define LL_GPTMRX_IER_ITEnMskTypeDef      uint32_t

#define LL_GPTMRX_IER_BIE                 (TMR0_IER_BIE_Msk)      /*!< Break interrupt enable          */
#define LL_GPTMRX_IER_TIE                 (TMR0_IER_TIE_Msk)      /*!< Trigger interrupt enable        */
#define LL_GPTMRX_IER_OVIE                (TMR0_IER_OVIE_Msk)     /*!< Overflow interrupt enable       */
#define LL_GPTMRX_IER_UIE                 (TMR0_IER_UIE_Msk)      /*!< Update interrupt enable         */
#define LL_GPTMRX_IER_C1OIE               (TMR0_IER_C1OIE_Msk)    /*!< CH1 output compare interrupt enable */
#define LL_GPTMRX_IER_C1MIE               (TMR0_IER_C1MIE_Msk)    /*!< CH1 input capture interrupt enable  */
#define LL_GPTMRX_IER_C0OIE               (TMR0_IER_C0OIE_Msk)    /*!< CH0 output compare interrupt enable */
#define LL_GPTMRX_IER_C0MIE               (TMR0_IER_C0MIE_Msk)    /*!< CH0 input capture interrupt enable  */

#define LL_GPTMRX_IER_IT_EN_MSK           ((TMR0_IER_BIE_Msk               | TMR0_IER_TIE_Msk                | \
                                           TMR0_IER_OVIE_Msk               | TMR0_IER_UIE_Msk                | \
                                           TMR0_IER_C1OIE_Msk              | TMR0_IER_C1MIE_Msk              | \
                                           TMR0_IER_C0OIE_Msk              | TMR0_IER_C0MIE_Msk              ))

#define LL_GPTMRX_IER_CC_IT_EN_MSK        ((TMR0_IER_C1OIE_Msk             | TMR0_IER_C1MIE_Msk              | \
                                           TMR0_IER_C0OIE_Msk              | TMR0_IER_C0MIE_Msk              ))
/**
  * @}
  */

/** @name LL_GPTMRX_SR_ITPendingMskTypeDef
  * @brief GPTMRX LL Status Flag Masks
  * @{
  */
#define LL_GPTMRX_SR_ITPendingMskTypeDef              uint32_t

#define LL_GPTMRX_SR_SBIF                 (TMR0_SR_SBIF_Msk)      /*!< System break flag               */
#define LL_GPTMRX_SR_B0IF                 (TMR0_SR_BIF_Msk)       /*!< Break input 0 flag              */
#define LL_GPTMRX_SR_TIF                  (TMR0_SR_TIF_Msk)       /*!< Trigger flag                    */
#define LL_GPTMRX_SR_OVIF                 (TMR0_SR_OVIF_Msk)      /*!< Overflow flag                   */
#define LL_GPTMRX_SR_UIF                  (TMR0_SR_UIF_Msk)       /*!< Update flag                     */
#define LL_GPTMRX_SR_CC1OIF               (TMR0_SR_CC1OIF_Msk)    /*!< CH1 output compare flag         */
#define LL_GPTMRX_SR_CC1MIF               (TMR0_SR_CC1MIF_Msk)    /*!< CH1 input capture flag          */
#define LL_GPTMRX_SR_CC0OIF               (TMR0_SR_CC0OIF_Msk)    /*!< CH0 output compare flag         */
#define LL_GPTMRX_SR_CC0MIF               (TMR0_SR_CC0MIF_Msk)    /*!< CH0 input capture flag          */

#define LL_GPTMRX_SR_IT_FLAG_MSK          ((TMR0_SR_SBIF_Msk                | TMR0_SR_BIF_Msk                 | \
                                            TMR0_SR_TIF_Msk                 | TMR0_SR_OVIF_Msk                | \
                                            TMR0_SR_UIF_Msk                 | \
                                            TMR0_SR_CC1OIF_Msk              | TMR0_SR_CC1MIF_Msk              | \
                                            TMR0_SR_CC0OIF_Msk              | TMR0_SR_CC0MIF_Msk              ))

#define LL_GPTMRX_SR_CC_IT_FLAG_MSK       ((TMR0_SR_CC1OIF_Msk              | TMR0_SR_CC1MIF_Msk              | \
                                            TMR0_SR_CC0OIF_Msk              | TMR0_SR_CC0MIF_Msk              ))

#define LL_GPTMRX_SR_BRK_IT_FLAG_MSK      ((TMR0_SR_SBIF_Msk                | TMR0_SR_BIF_Msk))

#define LL_GPTMRX_SR_UPD_IT_FLAG_MSK      ((TMR0_SR_OVIF_Msk                | TMR0_SR_UIF_Msk                 ))
/** @} */

#define LL_GPTMRX_CCER_CMP_CAP_CHNL_MSK   ((TMR0_CCER_CC1NE_Msk             | TMR0_CCER_CC1E_Msk              | \
                                            TMR0_CCER_CC0NE_Msk             | TMR0_CCER_CC0E_Msk              ))

/** @name LL_GPTMRX_TTCR_TrigOutChMskTypeDef
  * @brief GPTMRX LL TTCR TRGO Channel Selection
  * @{
  */
#define LL_GPTMRX_TTCR_TrigOutChMskTypeDef          uint32_t

#define LL_GPTMRX_TTCR_TRGI_OUT_SELECT_CH1          (TMR0_TTCR_TC1E_Msk)
#define LL_GPTMRX_TTCR_TRGI_OUT_SELECT_CH0          (TMR0_TTCR_TC0E_Msk)
/** @} */

/** @name LL_GPTMRX_BrkInputMskTypeDef
  * @brief GPTMRX LL Break Input Channel Mask
  * @{
  */
#define LL_GPTMRX_BrkInputMskTypeDef       uint16_t
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK0     ((uint16_t)(BIT(0)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK1     ((uint16_t)(BIT(1)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK2     ((uint16_t)(BIT(2)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK3     ((uint16_t)(BIT(3)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK4     ((uint16_t)(BIT(4)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK5     ((uint16_t)(BIT(5)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK6     ((uint16_t)(BIT(6)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK7     ((uint16_t)(BIT(7)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK8     ((uint16_t)(BIT(8)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK9     ((uint16_t)(BIT(9)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK10    ((uint16_t)(BIT(10)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK11    ((uint16_t)(BIT(11)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK12    ((uint16_t)(BIT(12)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK13    ((uint16_t)(BIT(13)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK14    ((uint16_t)(BIT(14)))
#define LL_GPTMRX_BRK_IN_SIGNAL_BREAK15    ((uint16_t)(BIT(15)))
/** @} */

/** @name LL_GPTMRX_BrkInputSrcMskTypeDef
  * @brief GPTMRX LL Break Input Source Mask
  * @{
  */
#define LL_GPTMRX_BrkInputSrcMskTypeDef        uint16_t
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP0_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK0)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP1_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK1)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP2_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK2)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP3_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK3)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP4_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK4)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP5_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK5)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP6_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK6)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP7_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK7)
#define LL_GPTMRX_BRK_IN_SRC_MASK_CMP8_OUT     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK8)
#define LL_GPTMRX_BRK_IN_SRC_MASK_TMRx_BKy     (LL_GPTMRX_BRK_IN_SIGNAL_BREAK9)
#define LL_GPTMRX_BRK_IN_SRC_MASK_ADC0_AWD0    (LL_GPTMRX_BRK_IN_SIGNAL_BREAK10)
#define LL_GPTMRX_BRK_IN_SRC_MASK_ADC1_AWD0    (LL_GPTMRX_BRK_IN_SIGNAL_BREAK11)
#define LL_GPTMRX_BRK_IN_SRC_MASK_PDM0_CMPH    (LL_GPTMRX_BRK_IN_SIGNAL_BREAK12)
#define LL_GPTMRX_BRK_IN_SRC_MASK_PDM1_CMPH    (LL_GPTMRX_BRK_IN_SIGNAL_BREAK13)
#define LL_GPTMRX_BRK_IN_SRC_MASK_PDM2_CMPH    (LL_GPTMRX_BRK_IN_SIGNAL_BREAK14)
#define LL_GPTMRX_BRK_IN_SRC_MASK_PDM3_CMPH    (LL_GPTMRX_BRK_IN_SIGNAL_BREAK15)
/** @} */

/** @name LL_GPTMRX_TI0InSrcTypeDef
  * @brief GPTMRX LL TI0 Input Source
  * @{
  */
#define LL_GPTMRX_TI0InSrcTypeDef         LL_RSV_DATA_TYPE

#define LL_GPTMRX_TI0_IN_SRC_CH0          (0UL)   
#define LL_GPTMRX_TI0_IN_SRC_CH0_1_XOR    (1UL)   

#define IS_LL_GPTMRX_TI0_IN_SRC(__VAL__)            (((__VAL__) == LL_GPTMRX_TI0_IN_SRC_CH0) || \
                                                     ((__VAL__) == LL_GPTMRX_TI0_IN_SRC_CH0_1_XOR))
/** @} */


/** @name LL_GPTMRX_WorkModeTypeDef
  * @brief GPTMRX LL Work Mode (CR0.OPM)
  * @{
  */
#define LL_GPTMRX_WorkModeTypeDef        LL_RSV_DATA_TYPE

#define LL_GPTMRX_WORK_MODE_CONTINUE     (0UL)   /*!< Continue mode */
#define LL_GPTMRX_WORK_MODE_SINGLE       (1UL)   /*!< Single mode   */

#define IS_LL_GPTMRX_WORK_MODE(__VAL__)             (((__VAL__) == LL_GPTMRX_WORK_MODE_CONTINUE) || \
                                                     ((__VAL__) == LL_GPTMRX_WORK_MODE_SINGLE))
/** @} */

/** @name LL_GPTMRX_UpdateEvtSrcTypeDef
  * @brief GPTMRX LL Update Event Source (CR0.URS)
  * @{
  */
#define LL_GPTMRX_UpdateEvtSrcTypeDef    LL_RSV_DATA_TYPE

#define LL_GPTMRX_UPDATE_EVT_SRC_OV_UG   (0UL)   /*!< Overflow and software (UG) */
#define LL_GPTMRX_UPDATE_EVT_SRC_OV      (1UL)   /*!< Only overflow              */

#define IS_LL_GPTMRX_UPDATE_EVT_SRC(__VAL__)         (((__VAL__) == LL_GPTMRX_UPDATE_EVT_SRC_OV_UG) || \
                                                     ((__VAL__) == LL_GPTMRX_UPDATE_EVT_SRC_OV))
/** @} */

/** @name LL_GPTMRX_OutputIdleStaTypeDef
  * @brief GPTMRX LL Output Idle State
  * @{
  */
#define LL_GPTMRX_OutputIdleStaTypeDef              LL_RSV_DATA_TYPE    

#define LL_GPTMRX_OUTPUT_IDLE_STA_LOW               (0UL)                /*!< Output Idle State Low                            */
#define LL_GPTMRX_OUTPUT_IDLE_STA_HIGH              (1UL)                /*!< Output Idle State High                           */

#define IS_LL_GPTMRX_OUTPUT_IDLE_STA(__VAL__)       (((__VAL__) == LL_GPTMRX_OUTPUT_IDLE_STA_LOW)  || \
                                                     ((__VAL__) == LL_GPTMRX_OUTPUT_IDLE_STA_HIGH) )
/** @} */

/** @name LL_GPTMRX_MstModeTypeDef
  * @brief GPTMRX LL Master Mode (CR1.MMS)
  * @{
  */
#define LL_GPTMRX_MstModeTypeDef          LL_RSV_DATA_TYPE

#define LL_GPTMRX_MST_MODE_RESET          (0UL)   /*!< TRGO = counter reset (UG)    */
#define LL_GPTMRX_MST_MODE_ENABLE         (1UL)   /*!< TRGO = counter enable        */
#define LL_GPTMRX_MST_MODE_UPDATE         (2UL)   /*!< TRGO = update event          */
#define LL_GPTMRX_MST_MODE_CAP_CMP_EVT    (3UL)   /*!< TRGO = capture/compare event */
#define LL_GPTMRX_MST_MODE_OC0REF         (4UL)   /*!< TRGO = OC0REF                */
#define LL_GPTMRX_MST_MODE_OC1REF         (5UL)   /*!< TRGO = OC1REF                */

#define IS_LL_GPTMRX_MST_MODE(__VAL__)              (((__VAL__) == LL_GPTMRX_MST_MODE_RESET) || \
                                                     ((__VAL__) == LL_GPTMRX_MST_MODE_ENABLE) || \
                                                     ((__VAL__) == LL_GPTMRX_MST_MODE_UPDATE) || \
                                                     ((__VAL__) == LL_GPTMRX_MST_MODE_CAP_CMP_EVT) || \
                                                     ((__VAL__) == LL_GPTMRX_MST_MODE_OC0REF) || \
                                                     ((__VAL__) == LL_GPTMRX_MST_MODE_OC1REF))
/** @} */

/** @name LL_GPTMRX_TrigTypeDef
  * @brief GPTMRX LL Trigger Selection (SCR.TS)
  * @{
  */
#define LL_GPTMRX_TrigTypeDef            LL_RSV_DATA_TYPE

/* Generic internal trigger sources */
#define LL_GPTMRX_TRIG_ITR0             (0UL)   /*!< Internal trigger ITR0  */
#define LL_GPTMRX_TRIG_ITR1             (1UL)   /*!< Internal trigger ITR1  */
#define LL_GPTMRX_TRIG_ITR2             (2UL)   /*!< Internal trigger ITR2  */
#define LL_GPTMRX_TRIG_ITR3             (3UL)   /*!< Internal trigger ITR3  */
#define LL_GPTMRX_TRIG_ITR4             (4UL)   /*!< Internal trigger ITR4  */
#define LL_GPTMRX_TRIG_ITR5             (5UL)   /*!< Internal trigger ITR5  */
#define LL_GPTMRX_TRIG_ITR6             (6UL)   /*!< Internal trigger ITR6  */
#define LL_GPTMRX_TRIG_ITR7             (7UL)   /*!< Internal trigger ITR7  */
#define LL_GPTMRX_TRIG_ITR8             (8UL)   /*!< Internal trigger ITR8  */
#define LL_GPTMRX_TRIG_ITR9             (9UL)   /*!< Internal trigger ITR9  */
#define LL_GPTMRX_TRIG_ITR10            (10UL)  /*!< Internal trigger ITR10 */
#define LL_GPTMRX_TRIG_ITR11            (11UL)  /*!< Internal trigger ITR11 */
#define LL_GPTMRX_TRIG_ITR12            (12UL)  /*!< Internal trigger ITR12 */
#define LL_GPTMRX_TRIG_ITR13            (13UL)  /*!< Internal trigger ITR13 */
#define LL_GPTMRX_TRIG_ITR14            (14UL)  /*!< Internal trigger ITR14 */
#define LL_GPTMRX_TRIG_ITR15            (15UL)  /*!< Internal trigger ITR15 */

#define LL_GPTMRX_TRIG_CH0_FE           (16UL)  /*!< Channel 0 rising edge  */
#define LL_GPTMRX_TRIG_CH0_F            (17UL)  /*!< Channel 0 falling edge */
#define LL_GPTMRX_TRIG_CH1_F            (18UL)  /*!< Channel 1 falling edge */

/* Per-instance trigger mapping: TMR0 */
#define LL_GPTMRX_TRIG_TMR0_ITR0_TMR7_TRGO           (LL_GPTMRX_TRIG_ITR0)    /*!< TMR0 ITR0: TMR7_TRGO      */
#define LL_GPTMRX_TRIG_TMR0_ITR1_TMR8_TRGO           (LL_GPTMRX_TRIG_ITR1)    /*!< TMR0 ITR1: TMR8_TRGO      */
#define LL_GPTMRX_TRIG_TMR0_ITR2_TMR1_TRGO           (LL_GPTMRX_TRIG_ITR2)    /*!< TMR0 ITR2: TMR1_TRGO      */
#define LL_GPTMRX_TRIG_TMR0_ITR3_TMR2_TRGO           (LL_GPTMRX_TRIG_ITR3)    /*!< TMR0 ITR3: TMR2_TRGO      */
#define LL_GPTMRX_TRIG_TMR0_ITR4_TMR3_TRGO           (LL_GPTMRX_TRIG_ITR4)    /*!< TMR0 ITR4: TMR3_TRGO      */
#define LL_GPTMRX_TRIG_TMR0_ITR5_TMR4_TRGO           (LL_GPTMRX_TRIG_ITR5)    /*!< TMR0 ITR5: TMR4_TRGO      */
#define LL_GPTMRX_TRIG_TMR0_ITR6_TMR1_OC0            (LL_GPTMRX_TRIG_ITR6)    /*!< TMR0 ITR6: TMR1_OC0       */
#define LL_GPTMRX_TRIG_TMR0_ITR7_TMR2_OC0            (LL_GPTMRX_TRIG_ITR7)    /*!< TMR0 ITR7: TMR2_OC0       */
#define LL_GPTMRX_TRIG_TMR0_ITR8_TMR3_OC0            (LL_GPTMRX_TRIG_ITR8)    /*!< TMR0 ITR8: TMR3_OC0       */
#define LL_GPTMRX_TRIG_TMR0_ITR9_TMR4_OC0            (LL_GPTMRX_TRIG_ITR9)    /*!< TMR0 ITR9: TMR4_OC0       */
#define LL_GPTMRX_TRIG_TMR0_ITR10_TMR9_TRGO          (LL_GPTMRX_TRIG_ITR10)   /*!< TMR0 ITR10: TMR9_TRGO     */
#define LL_GPTMRX_TRIG_TMR0_ITR11_TMR9_OC0           (LL_GPTMRX_TRIG_ITR11)   /*!< TMR0 ITR11: TMR9_OC0      */
#define LL_GPTMRX_TRIG_TMR0_ITR12_TMR9_OC1           (LL_GPTMRX_TRIG_ITR12)   /*!< TMR0 ITR12: TMR9_OC1      */
#define LL_GPTMRX_TRIG_TMR0_ITR13_TMR10_TRGO         (LL_GPTMRX_TRIG_ITR13)   /*!< TMR0 ITR13: TMR10_TRGO    */
#define LL_GPTMRX_TRIG_TMR0_ITR14_TMR10_OC0          (LL_GPTMRX_TRIG_ITR14)   /*!< TMR0 ITR14: TMR10_OC0     */
#define LL_GPTMRX_TRIG_TMR0_ITR15_HRPWM_SYNCO        (LL_GPTMRX_TRIG_ITR15)   /*!< TMR0 ITR15: HRPWM_SYNCO   */

/* Per-instance trigger mapping: TMR1 */
#define LL_GPTMRX_TRIG_TMR1_ITR0_TMR7_TRGO           (LL_GPTMRX_TRIG_ITR0)    /*!< TMR1 ITR0: TMR7_TRGO      */
#define LL_GPTMRX_TRIG_TMR1_ITR1_TMR8_TRGO           (LL_GPTMRX_TRIG_ITR1)    /*!< TMR1 ITR1: TMR8_TRGO      */
#define LL_GPTMRX_TRIG_TMR1_ITR2_TMR0_TRGO           (LL_GPTMRX_TRIG_ITR2)    /*!< TMR1 ITR2: TMR0_TRGO      */
#define LL_GPTMRX_TRIG_TMR1_ITR3_TMR2_TRGO           (LL_GPTMRX_TRIG_ITR3)    /*!< TMR1 ITR3: TMR2_TRGO      */
#define LL_GPTMRX_TRIG_TMR1_ITR4_TMR3_TRGO           (LL_GPTMRX_TRIG_ITR4)    /*!< TMR1 ITR4: TMR3_TRGO      */
#define LL_GPTMRX_TRIG_TMR1_ITR5_TMR4_TRGO           (LL_GPTMRX_TRIG_ITR5)    /*!< TMR1 ITR5: TMR4_TRGO      */
#define LL_GPTMRX_TRIG_TMR1_ITR6_TMR0_OC0            (LL_GPTMRX_TRIG_ITR6)    /*!< TMR1 ITR6: TMR0_OC0       */
#define LL_GPTMRX_TRIG_TMR1_ITR7_TMR2_OC0            (LL_GPTMRX_TRIG_ITR7)    /*!< TMR1 ITR7: TMR2_OC0       */
#define LL_GPTMRX_TRIG_TMR1_ITR8_TMR3_OC0            (LL_GPTMRX_TRIG_ITR8)    /*!< TMR1 ITR8: TMR3_OC0       */
#define LL_GPTMRX_TRIG_TMR1_ITR9_TMR4_OC0            (LL_GPTMRX_TRIG_ITR9)    /*!< TMR1 ITR9: TMR4_OC0       */
#define LL_GPTMRX_TRIG_TMR1_ITR10_TMR9_TRGO          (LL_GPTMRX_TRIG_ITR10)   /*!< TMR1 ITR10: TMR9_TRGO     */
#define LL_GPTMRX_TRIG_TMR1_ITR11_TMR9_OC0           (LL_GPTMRX_TRIG_ITR11)   /*!< TMR1 ITR11: TMR9_OC0      */
#define LL_GPTMRX_TRIG_TMR1_ITR12_TMR9_OC1           (LL_GPTMRX_TRIG_ITR12)   /*!< TMR1 ITR12: TMR9_OC1      */
#define LL_GPTMRX_TRIG_TMR1_ITR13_TMR10_TRGO         (LL_GPTMRX_TRIG_ITR13)   /*!< TMR1 ITR13: TMR10_TRGO    */
#define LL_GPTMRX_TRIG_TMR1_ITR14_TMR10_OC0          (LL_GPTMRX_TRIG_ITR14)   /*!< TMR1 ITR14: TMR10_OC0     */
#define LL_GPTMRX_TRIG_TMR1_ITR15_HRPWM_SYNCO        (LL_GPTMRX_TRIG_ITR15)   /*!< TMR1 ITR15: HRPWM_SYNCO   */

/* Per-instance trigger mapping: TMR2 */
#define LL_GPTMRX_TRIG_TMR2_ITR0_TMR7_TRGO           (LL_GPTMRX_TRIG_ITR0)    /*!< TMR2 ITR0: TMR7_TRGO      */
#define LL_GPTMRX_TRIG_TMR2_ITR1_TMR8_TRGO           (LL_GPTMRX_TRIG_ITR1)    /*!< TMR2 ITR1: TMR8_TRGO      */
#define LL_GPTMRX_TRIG_TMR2_ITR2_TMR0_TRGO           (LL_GPTMRX_TRIG_ITR2)    /*!< TMR2 ITR2: TMR0_TRGO      */
#define LL_GPTMRX_TRIG_TMR2_ITR3_TMR1_TRGO           (LL_GPTMRX_TRIG_ITR3)    /*!< TMR2 ITR3: TMR1_TRGO      */
#define LL_GPTMRX_TRIG_TMR2_ITR4_TMR3_TRGO           (LL_GPTMRX_TRIG_ITR4)    /*!< TMR2 ITR4: TMR3_TRGO      */
#define LL_GPTMRX_TRIG_TMR2_ITR5_TMR4_TRGO           (LL_GPTMRX_TRIG_ITR5)    /*!< TMR2 ITR5: TMR4_TRGO      */
#define LL_GPTMRX_TRIG_TMR2_ITR6_TMR0_OC0            (LL_GPTMRX_TRIG_ITR6)    /*!< TMR2 ITR6: TMR0_OC0       */
#define LL_GPTMRX_TRIG_TMR2_ITR7_TMR1_OC0            (LL_GPTMRX_TRIG_ITR7)    /*!< TMR2 ITR7: TMR1_OC0       */
#define LL_GPTMRX_TRIG_TMR2_ITR8_TMR3_OC0            (LL_GPTMRX_TRIG_ITR8)    /*!< TMR2 ITR8: TMR3_OC0       */
#define LL_GPTMRX_TRIG_TMR2_ITR9_TMR4_OC0            (LL_GPTMRX_TRIG_ITR9)    /*!< TMR2 ITR9: TMR4_OC0       */
#define LL_GPTMRX_TRIG_TMR2_ITR10_TMR9_TRGO          (LL_GPTMRX_TRIG_ITR10)   /*!< TMR2 ITR10: TMR9_TRGO     */
#define LL_GPTMRX_TRIG_TMR2_ITR11_TMR9_OC0           (LL_GPTMRX_TRIG_ITR11)   /*!< TMR2 ITR11: TMR9_OC0      */
#define LL_GPTMRX_TRIG_TMR2_ITR12_TMR9_OC1           (LL_GPTMRX_TRIG_ITR12)   /*!< TMR2 ITR12: TMR9_OC1      */
#define LL_GPTMRX_TRIG_TMR2_ITR13_TMR10_TRGO         (LL_GPTMRX_TRIG_ITR13)   /*!< TMR2 ITR13: TMR10_TRGO    */
#define LL_GPTMRX_TRIG_TMR2_ITR14_TMR10_OC0          (LL_GPTMRX_TRIG_ITR14)   /*!< TMR2 ITR14: TMR10_OC0     */
#define LL_GPTMRX_TRIG_TMR2_ITR15_HRPWM_SYNCO        (LL_GPTMRX_TRIG_ITR15)   /*!< TMR2 ITR15: HRPWM_SYNCO   */
/** @} */

/** @name LL_GPTMRX_CapCmpChTypeDef
  * @brief GPTMRX LL Capture/Compare Channel (4 channels)
  * @{
  */
#define LL_GPTMRX_CapCmpChTypeDef            uint32_t
#define LL_GPTMRX_CAP_CMP_CH_0               (0UL)   /*!< Capture/Compare channel 0 */
#define LL_GPTMRX_CAP_CMP_CH_1               (1UL)   /*!< Capture/Compare channel 1 */
#define LL_GPTMRX_CAP_CMP_CH_0N              (4UL)   /*!< Capture/Compare channel 0 complementary output */
#define LL_GPTMRX_CAP_CMP_CH_1N              (5UL)   /*!< Capture/Compare channel 1 complementary output */


#define IS_LL_GPTMRX_CHANNEL(__VAL__)        (((__VAL__) >= LL_GPTMRX_CAP_CMP_CH_0) && ((__VAL__) <= LL_GPTMRX_CAP_CMP_CH_1N))

#define LL_GPTMRX_CAP_CMP_CH_NUMS            (2UL)
#define LL_GPTMRX_CAP_CMP_CHN_NUMS           (2UL)
#define LL_GPTMRX_CAP_CMP_ALL_CH_NUMS        (LL_GPTMRX_CAP_CMP_CH_NUMS + LL_GPTMRX_CAP_CMP_CHN_NUMS)

#define IS_LL_GPTMRX_CAP_CMP_CH(__VAL__)     (((__VAL__) >= LL_GPTMRX_CAP_CMP_CH_0) && ((__VAL__) <= LL_GPTMRX_CAP_CMP_CH_1))
#define IS_LL_GPTMRX_CAP_CMP_CHN(__VAL__)    (((__VAL__) >= LL_GPTMRX_CAP_CMP_CH_0N) && ((__VAL__) <= LL_GPTMRX_CAP_CMP_CH_1N))

#if LL_GPTMRX_CAP_CMP_CH_NUMS > 4UL
#error "LL_GPTMRX_CAP_CMP_CH_NUMS"
#endif

#if LL_GPTMRX_CAP_CMP_CH_NUMS != LL_GPTMRX_CAP_CMP_CHN_NUMS
#error "LL_GPTMRX_CAP_CMP_ALL_CH_NUMS"
#endif

/** @} */

/** @name LL_GPTMRX_CapCmpOCTypeDef
  * @brief GPTMRX LL Compare/Capture OC Type
  * @{
  */
#define LL_GPTMRX_CapCmpOCTypeDef            uint32_t
#define LL_GPTMRX_CAP_CMP_OC                 (0UL)
#define LL_GPTMRX_CAP_CMP_OCN                (1UL)

#define IS_LL_GPTMRX_CAP_CMP_OC(__VAL__)     (((__VAL__) == LL_GPTMRX_CAP_CMP_OC) || \
                                             ((__VAL__) == LL_GPTMRX_CAP_CMP_OCN))
/** @} */

/** @name LL_GPTMRX_CapPolTypeDef
  * @brief GPTMRX LL Capture Polarity
  * @{
  */
#define LL_GPTMRX_CapPolTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRX_CAP_POL_CLOSE              (0UL)   /*!< Capture disabled       */
#define LL_GPTMRX_CAP_POL_RISING             (1UL)   /*!< Rising edge            */
#define LL_GPTMRX_CAP_POL_FALLING            (2UL)   /*!< Falling edge           */
#define LL_GPTMRX_CAP_POL_BOTH_EDGE          (3UL)   /*!< Both rising and falling */

#define IS_LL_GPTMRX_CAP_POL(__VAL__)        ((__VAL__) <= LL_GPTMRX_CAP_POL_BOTH_EDGE)

/** @} */

/** @name LL_GPTMRX_CapPrscTypeDef
  * @brief GPTMRX LL Capture Prescaler
  * @{
  */
#define LL_GPTMRX_CapPrscTypeDef             LL_RSV_DATA_TYPE

#define LL_GPTMRX_CAP_PRESCALER_1            (0UL)   /*!< Capture every edge      */
#define LL_GPTMRX_CAP_PRESCALER_2            (1UL)   /*!< Capture every 2 events  */
#define LL_GPTMRX_CAP_PRESCALER_4            (2UL)   /*!< Capture every 4 events  */
#define LL_GPTMRX_CAP_PRESCALER_8            (3UL)   /*!< Capture every 8 events  */

#define IS_LL_GPTMRX_CAP_PRESCALER(__VAL__)  (((__VAL__) == LL_GPTMRX_CAP_PRESCALER_1)  || \
                                              ((__VAL__) == LL_GPTMRX_CAP_PRESCALER_2)  || \
                                              ((__VAL__) == LL_GPTMRX_CAP_PRESCALER_4)  || \
                                              ((__VAL__) == LL_GPTMRX_CAP_PRESCALER_8))
/** @} */

/** @name LL_GPTMRX_CmpCapMapTypeDef
  * @brief GPTMRX LL Compare/Capture (Output/Input) Mapping
  * @{
  */
#define LL_GPTMRX_CmpCapMapTypeDef           LL_RSV_DATA_TYPE

#define LL_GPTMRX_CMP_CAP_MAP_OUTPUT         (0UL)   /*!< Mapped on the output */
#define LL_GPTMRX_CMP_CAP_MAP_INPUT_0        (1UL)   /*!< Mapped on the input 0 */
#define LL_GPTMRX_CMP_CAP_MAP_INPUT_1        (2UL)   /*!< Mapped on the input 1 */
#define LL_GPTMRX_CMP_CAP_MAP_INPUT_TRGI     (3UL)   /*!< Mapped on the trigger input */

#define IS_LL_GPTMRX_CMP_CAP_MAP(__VAL__)   (((__VAL__) == LL_GPTMRX_CMP_CAP_MAP_OUTPUT)   || \
                                             ((__VAL__) == LL_GPTMRX_CMP_CAP_MAP_INPUT_0)  || \
                                             ((__VAL__) == LL_GPTMRX_CMP_CAP_MAP_INPUT_1)  || \
                                             ((__VAL__) == LL_GPTMRX_CMP_CAP_MAP_INPUT_TRGI))
/** @} */

/** @name LL_GPTMRX_CmpOutputMapTypeDef
  * @brief GPTMRX LL Compare Output Mapping
  * @{
  */
#define LL_GPTMRX_CmpOutputMapTypeDef        LL_RSV_DATA_TYPE

#define LL_GPTMRX_CMP_OUTPUT_MAP_OUT         LL_GPTMRX_CMP_CAP_MAP_OUTPUT   /*!< Mapped on the output */

#define IS_LL_GPTMRX_CMP_OUTPUT_MAP(__VAL__) ((__VAL__) == LL_GPTMRX_CMP_OUTPUT_MAP_OUT)
/** @} */

/** @name LL_GPTMRX_CapInputMapTypeDef
  * @brief GPTMRX LL Capture Input Mapping
  * @{
  */
#define LL_GPTMRX_CapInputMapTypeDef         LL_RSV_DATA_TYPE

#define LL_GPTMRX_CAP_INPUT_MAP_0            LL_GPTMRX_CMP_CAP_MAP_INPUT_0    /*!< Mapped on the CH0 input */
#define LL_GPTMRX_CAP_INPUT_MAP_1            LL_GPTMRX_CMP_CAP_MAP_INPUT_1    /*!< Mapped on the CH1 input */
#define LL_GPTMRX_CAP_INPUT_MAP_TRGI         LL_GPTMRX_CMP_CAP_MAP_INPUT_TRGI   /*!< Mapped on the trigger input */

#define IS_LL_GPTMRX_CAP_INPUT_MAP(__VAL__)  (((__VAL__) == LL_GPTMRX_CAP_INPUT_MAP_0) || \
                                             ((__VAL__) == LL_GPTMRX_CAP_INPUT_MAP_1) || \
                                             ((__VAL__) == LL_GPTMRX_CAP_INPUT_MAP_TRGI))
/** @} */

/** @name LL_GPTMRX_CapInputSrcTypeDef
  * @brief GPTMRX LL Capture Trigger Input Source
  * @{
  */
#define LL_GPTMRX_CapInputSrcTypeDef         LL_RSV_DATA_TYPE

#define LL_GPTMRX_CAP_INPUT_SRC_IN0          (0UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN1          (1UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN2          (2UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN3          (3UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN4          (4UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN5          (5UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN6          (6UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN7          (7UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN8          (8UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN9          (9UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN10         (10UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN11         (11UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN12         (12UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN13         (13UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN14         (14UL)
#define LL_GPTMRX_CAP_INPUT_SRC_IN15         (15UL)

#define IS_LL_GPTMRX_CAP_INPUT_SRC(__VAL__)  (((__VAL__) >= LL_GPTMRX_CAP_INPUT_SRC_IN0) && \
                                              ((__VAL__) <= LL_GPTMRX_CAP_INPUT_SRC_IN15))

/** @} */

/** @name LL_GPTMRX_CmpPolTypeDef
  * @brief GPTMRX LL Compare Output Polarity
  * @{
  */
#define LL_GPTMRX_CmpPolTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRX_CMP_POL_HIGH               (0UL)   /*!< Compare output active high */
#define LL_GPTMRX_CMP_POL_LOW                (1UL)   /*!< Compare output active low  */

#define IS_LL_GPTMRX_CMP_POL(__VAL__)        (((__VAL__) == LL_GPTMRX_CMP_POL_HIGH) || \
                                              ((__VAL__) == LL_GPTMRX_CMP_POL_LOW))
/** @} */

/** @name LL_GPTMRX_DzDigFilClkDivTypeDef
  * @brief GPTMRX LL Dead-Zone Digital Filter Clock Division
  * @{
  */
#define LL_GPTMRX_DzDigFilClkDivTypeDef      LL_RSV_DATA_TYPE

#define LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_1       (0UL)   /*!< Clock division 1 */
#define LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_2       (1UL)   /*!< Clock division 2 */
#define LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_4       (2UL)   /*!< Clock division 4 */
#define LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_8       (3UL)   /*!< Clock division 8 */

#define IS_LL_GPTMRX_DZ_DIG_FIL_CLK_DIV(__VAL__)      (((__VAL__) == LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_1) || \
                                                       ((__VAL__) == LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_2) || \
                                                       ((__VAL__) == LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_4) || \
                                                       ((__VAL__) == LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_8))
/** @} */

/** @name LL_GPTMRX_SlvModeTypeDef
  * @brief GPTMRX LL Slave Mode
  * @{
  */
#define LL_GPTMRX_SlvModeTypeDef             LL_RSV_DATA_TYPE

#define LL_GPTMRX_SLV_MODE_DIS               (0UL)   /*!< Slave mode disabled      */
#define LL_GPTMRX_SLV_MODE_RST               (4UL)   /*!< Reset mode               */
#define LL_GPTMRX_SLV_MODE_GATING            (5UL)   /*!< Gated mode               */
#define LL_GPTMRX_SLV_MODE_TRIG              (6UL)   /*!< Trigger mode             */
#define LL_GPTMRX_SLV_MODE_EXTCLK            (7UL)   /*!< External clock mode 1    */
#define LL_GPTMRX_SLV_MODE_RST_TRIG          (8UL)   /*!< Combined reset + trigger */
#define LL_GPTMRX_SLV_MODE_RST_GATING        (9UL)   /*!< Combined reset + gated   */

#define IS_LL_GPTMRX_SLV_MODE(__VAL__)       (((__VAL__) == LL_GPTMRX_SLV_MODE_DIS) || \
                                              ((__VAL__) == LL_GPTMRX_SLV_MODE_RST) || \
                                              ((__VAL__) == LL_GPTMRX_SLV_MODE_GATING) || \
                                              ((__VAL__) == LL_GPTMRX_SLV_MODE_TRIG) || \
                                              ((__VAL__) == LL_GPTMRX_SLV_MODE_EXTCLK) || \
                                              ((__VAL__) == LL_GPTMRX_SLV_MODE_RST_TRIG) || \
                                              ((__VAL__) == LL_GPTMRX_SLV_MODE_RST_GATING))
/** @} */


/** @name LL_GPTMRX_EvtGenMaskTypeDef
  * @brief GPTMRX LL Timer Event Generation Mask
  * @{
  */
#define LL_GPTMRX_EvtGenMaskTypeDef               uint32_t    

#define LL_GPTMRX_EVT_GEN_UPDATE                  (TMR0_UGR_UG_Msk)         /*!< Timer Event Generation Update                    */
#define LL_GPTMRX_EVT_GEN_TRIGGER                 (TMR0_UGR_TG_Msk)         /*!< Timer Event Generation Trigger                   */
#define LL_GPTMRX_EVT_GEN_BREAK0                  (TMR0_UGR_BG_Msk)         /*!< Timer Event Generation Break 0                   */
#define LL_GPTMRX_EVT_GEN_CAP_CMP_0               (TMR0_UGR_CC0UG_Msk)      /*!< Timer Event Generation Capture/Compare 0         */
#define LL_GPTMRX_EVT_GEN_CAP_CMP_1               (TMR0_UGR_CC1UG_Msk)      /*!< Timer Event Generation Capture/Compare 1         */


#define LL_GPTMRX_EVT_GEN_ALL_MSK                 ((TMR0_UGR_CC1UG_Msk              | TMR0_UGR_CC0UG_Msk              | \
                                                    TMR0_UGR_BG_Msk                 | \
                                                    TMR0_UGR_TG_Msk                 | TMR0_UGR_UG_Msk                 ))
/** @} */

/** @name LL_GPTMRX_BrkPolTypeDef
  * @brief GPTMRX LL Break Input Polarity (DCR.BK0P / DCR.BK1P)
  * @{
  */
#define LL_GPTMRX_BrkPolTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRX_BRK_POL_HIGH               (0UL)   /*!< Break input high active */
#define LL_GPTMRX_BRK_POL_LOW                (1UL)   /*!< Break input low active  */

#define IS_LL_GPTMRX_BRK_POL(__VAL__)        (((__VAL__) == LL_GPTMRX_BRK_POL_HIGH) || \
                                              ((__VAL__) == LL_GPTMRX_BRK_POL_LOW))
/** @} */

/** @name LL_GPTMRX_BrkInPolTypeDef
  * @brief GPTMRX LL Break Input Valid Level Polarity
  * @{
  */
#define LL_GPTMRX_BrkInPolTypeDef            LL_RSV_DATA_TYPE

#define LL_GPTMRX_BRK_IN_POL_VALID_HIGH      (0UL)   /*!< Break input valid level high */
#define LL_GPTMRX_BRK_IN_POL_VALID_LOW       (1UL)   /*!< Break input valid low high */

#define IS_LL_GPTMRX_BRK_IN_POL(__VAL__)     (((__VAL__) == LL_GPTMRX_BRK_IN_POL_VALID_HIGH) || \
                                              ((__VAL__) == LL_GPTMRX_BRK_IN_POL_VALID_LOW))
/** @} */

/** @name LL_GPTMRX_RunOffStaTypeDef
  * @brief GPTMRX LL Run-Mode Off-State
  * @{
  */
#define LL_GPTMRX_RunOffStaTypeDef           LL_RSV_DATA_TYPE

#define LL_GPTMRX_RUN_OFF_STA_COMP_CLOSE    (0UL)   /*!< Idle-Mode Off-State complementary output close */
#define LL_GPTMRX_RUN_OFF_STA_COMP_IVD      (1UL)   /*!< Idle-Mode Off-State complementary output is in the invalid state*/

#define IS_LL_GPTMRX_RUN_OFF_STA(__VAL__)   (((__VAL__) == LL_GPTMRX_RUN_OFF_STA_COMP_CLOSE) || \
                                             ((__VAL__) == LL_GPTMRX_RUN_OFF_STA_COMP_IVD))
/** @} */

/** @name LL_GPTMRX_IdleOffStaTypeDef
  * @brief GPTMRX LL Idle-Mode Off-State
  * @{
  */
#define LL_GPTMRX_IdleOffStaTypeDef          LL_RSV_DATA_TYPE

#define LL_GPTMRX_IDLE_OFF_STA_COMP_CLOSE    (0UL)   /*!< Idle-Mode Off-State complementary output close */
#define LL_GPTMRX_IDLE_OFF_STA_COMP_IDLE     (1UL)   /*!< Idle-Mode Off-State complementary output is in the idle state*/

#define IS_LL_GPTMRX_IDLE_OFF_STA(__VAL__)   (((__VAL__) == LL_GPTMRX_IDLE_OFF_STA_COMP_CLOSE) || \
                                              ((__VAL__) == LL_GPTMRX_IDLE_OFF_STA_COMP_IDLE))
/** @} */

/** @name LL_GPTMRX_CapFilTypeDef
  * @brief GPTMRX LL Capture Filter
  * @{
  */
#define LL_GPTMRX_CapFilTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRX_CAP_FILTER_NONE            (0UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X1          (1UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X2          (2UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X3          (3UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X4          (4UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X5          (5UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X6          (6UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X7          (7UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X8          (8UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X9          (9UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X10         (10UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X11         (11UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X12         (12UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X13         (13UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X14         (14UL)
#define LL_GPTMRX_CAP_FILTER_TDS_X15         (15UL)

#define IS_LL_GPTMRX_CAP_FILTER(__VAL__)     (((__VAL__) >= LL_GPTMRX_CAP_FILTER_NONE) && \
                                              ((__VAL__) <= LL_GPTMRX_CAP_FILTER_TDS_X15))
/** @} */

/** @name LL_GPTMRX_OCModeTypeDef
  * @brief GPTMRX LL Compare Output Mode (CCMR.OCxM)
  * @{
  */
#define LL_GPTMRX_OCModeTypeDef                  LL_RSV_DATA_TYPE

#define LL_GPTMRX_CMP_MODE_FREEZE                (0UL)    /*!< Frozen                    */
#define LL_GPTMRX_CMP_MODE_ACTIVE                (1UL)    /*!< Force active              */
#define LL_GPTMRX_CMP_MODE_INACTIVE              (2UL)    /*!< Force inactive            */
#define LL_GPTMRX_CMP_MODE_TOGGLE                (3UL)    /*!< Toggle on match           */
#define LL_GPTMRX_CMP_MODE_FORCE_INACTIVE        (4UL)    /*!< Force inactive on match   */
#define LL_GPTMRX_CMP_MODE_FORCE_ACTIVE          (5UL)    /*!< Force active on match     */
#define LL_GPTMRX_CMP_MODE_PWM1                  (6UL)    /*!< PWM mode 1                */
#define LL_GPTMRX_CMP_MODE_PWM2                  (7UL)    /*!< PWM mode 2                */
#define LL_GPTMRX_CMP_MODE_RETRIG_OPM1           (8UL)    /*!< Retriggerable OPM mode 1  */
#define LL_GPTMRX_CMP_MODE_RETRIG_OPM2           (9UL)    /*!< Retriggerable OPM mode 2  */
#define LL_GPTMRX_CMP_MODE_COMB_PWM1             (12UL)   /*!< Combined PWM mode 1       */
#define LL_GPTMRX_CMP_MODE_COMB_PWM2             (13UL)   /*!< Combined PWM mode 2       */
#define LL_GPTMRX_CMP_MODE_ASYM_PWM1             (14UL)   /*!< Asymmetric PWM mode 1     */
#define LL_GPTMRX_CMP_MODE_ASYM_PWM2             (15UL)   /*!< Asymmetric PWM mode 2     */

#define IS_LL_GPTMRX_CMP_MODE(__VAL__)           ((((__VAL__) >= LL_GPTMRX_CMP_MODE_FREEZE)    && ((__VAL__) <= LL_GPTMRX_CMP_MODE_RETRIG_OPM2)) || \
                                                  (((__VAL__) >= LL_GPTMRX_CMP_MODE_COMB_PWM1) && ((__VAL__) <= LL_GPTMRX_CMP_MODE_ASYM_PWM2)))
/** @} */


/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPTMRX_LL_Exported_Macros GPTMRX LL Exported Macros
  * @brief    GPTMRX LL Exported Macros
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_GPTMRX_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_GPTMRX_ASSERT_INLINE_PARAM == 1)
extern void LL_GPTMRX_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_GPTMRX_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_GPTMRX_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_GPTMRX_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @brief  GPTMRX 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define LL_GPTMRX_REG_OFFSET(__REG__, offset)            \
        (*((volatile uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))
/**
  * @}
  */ /* GPTMRX_LL_Exported_Macros */

/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup GPTMRX_LL_Exported_Functions GPTMRX LL Exported Functions
  * @{
  */

/** @defgroup GPTMRX_LL_EF_Configuration LL GPTMRX Configuration
  * @brief    LL GPTMRX Configuration
  * @{
  */

/**
  * @brief  Enable the counter
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableCounter(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->CR0, TMR0_CR0_CEN_Msk);
}

/**
  * @brief  Disable the counter
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableCounter(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->CR0, TMR0_CR0_CEN_Msk);
}

/**
  * @brief  Judge whether the counter is enabled or not (CR0.CEN)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Counter is disabled
  * @retval 1 Counter is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledCounter(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->CR0, TMR0_CR0_CEN_Msk, TMR0_CR0_CEN_Pos));
}

/**
  * @brief  Set the counter value (16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetCounter(GPTMRx_TypeDef *GPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->CNTR, ((Val) & TMR0_CNTR_CNT_Val));
}

/**
  * @brief  Get the counter value (16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Counter value (16 bits)
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetCounter(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->CNTR) & TMR0_CNTR_CNT_Val);
}

/**
  * @brief  Set the counter period (auto-reload value, 16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Period Counter period value
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetAutoReload(GPTMRx_TypeDef *GPTMRx, uint32_t Period)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->CPR, ((Period) & TMR0_CPR_CPV_Val));
}

/**
  * @brief  Get the counter period (16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Counter period (16 bits)
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetAutoReload(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->CPR) & TMR0_CPR_CPV_Val);
}

/**
  * @brief  Set the prescaler division value (16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetPrescaler(GPTMRx_TypeDef *GPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->PSCR, ((Val) & TMR0_PSCR_PSC_Val));
}

/**
  * @brief  Get the prescaler division value (16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Prescaler division value (16 bits)
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetPrescaler(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->PSCR) & TMR0_PSCR_PSC_Val);
}

/**
  * @brief  Set the repetition counter value (CRR.REP, 8 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetRepetitionCounter(GPTMRx_TypeDef *GPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->CRR, ((Val) & TMR0_CRR_REP_Val));
}

/**
  * @brief  Get the repetition counter value (8 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Repetition counter value (8 bits)
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetRepetitionCounter(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->CRR) & TMR0_CRR_REP_Val);
}

/**
  * @brief  Enable the auto-preload
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableAutoReload(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->CR0, TMR0_CR0_ARE_Msk);
}

/**
  * @brief  Disable the auto-preload
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableAutoReload(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->CR0, TMR0_CR0_ARE_Msk);
}

/**
  * @brief  Judge whether the auto-preload is enabled or not
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Auto-preload is disabled
  * @retval 1 Auto-preload is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsAutoReloadEnabled(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->CR0, TMR0_CR0_ARE_Msk, TMR0_CR0_ARE_Pos));
}

/**
  * @brief  Set TI0 Input Source 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Src TI0 Input Source @ref LL_GPTMRX_TI0InSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetTI0InputSource(GPTMRx_TypeDef *GPTMRx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG(GPTMRx->CR0, TMR9_CR0_TI0S_Msk, (((Src) & TMR9_CR0_TI0S_Val) << TMR9_CR0_TI0S_Pos));
}

/**
  * @brief  Get TI0 Input Source 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return TI0 Input Source @ref LL_GPTMRX_TI0InSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetTI0InputSource(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->CR0, TMR9_CR0_TI0S_Msk, TMR9_CR0_TI0S_Pos));
}

/**
  * @brief  Set the counter work mode
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRX_WorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetOnePulseMode(GPTMRx_TypeDef *GPTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRX_WORK_MODE(Mode));

    MODIFY_REG((GPTMRx)->CR0, TMR0_CR0_OPM_Msk, (((Mode) & TMR0_CR0_OPM_Val) << TMR0_CR0_OPM_Pos));
}

/**
  * @brief  Get the counter work mode
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Counter work mode @ref LL_GPTMRX_WorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetOnePulseMode(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->CR0, TMR0_CR0_OPM_Msk, TMR0_CR0_OPM_Pos));
}

/**
  * @brief  Set the update event source
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Src Source to be selected @ref LL_GPTMRX_UpdateEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetUpdateSource(GPTMRx_TypeDef *GPTMRx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRX_UPDATE_EVT_SRC(Src));

    MODIFY_REG((GPTMRx)->CR0, TMR0_CR0_URS_Msk, (((Src) & TMR0_CR0_URS_Val) << TMR0_CR0_URS_Pos));
}

/**
  * @brief  Get the update event source
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Update event source @ref LL_GPTMRX_UpdateEvtSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetUpdateSource(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->CR0, TMR0_CR0_URS_Msk, TMR0_CR0_URS_Pos));
}

/**
  * @brief  Enable the update event (UDIS = 0)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableUpdateEvent(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->CR0, TMR0_CR0_UDIS_Msk);
}

/**
  * @brief  Disable the update event (UDIS = 1)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableUpdateEvent(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->CR0, TMR0_CR0_UDIS_Msk);
}

/**
  * @brief  Judge whether the update event is enabled or not
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Update event is disabled
  * @retval 1 Update event is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledUpdateEvent(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (!(READ_BIT_SHIFT((GPTMRx)->CR0, TMR0_CR0_UDIS_Msk, TMR0_CR0_UDIS_Pos)));
}

/**
  * @brief  Set the master mode (source of the TRGO signal)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRX_MstModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetTriggerOutput(GPTMRx_TypeDef *GPTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRX_MST_MODE(Mode));

    MODIFY_REG((GPTMRx)->CR1, TMR0_CR1_MMS_Msk, (((Mode) & TMR0_CR1_MMS_Val) << TMR0_CR1_MMS_Pos));
}

/**
  * @brief  Get the master mode
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Master mode @ref LL_GPTMRX_MstModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetTriggerOutput(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->CR1, TMR0_CR1_MMS_Msk, TMR0_CR1_MMS_Pos));
}


/**
  * @brief  Set the output idle state of a given channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_*)
  * @param  IdleState Idle state @ref LL_GPTMRX_OutputIdleStaTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_OC_SetIdleState(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t IdleState)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CHANNEL(Channel)));

    if (Channel <= LL_GPTMRX_CAP_CMP_CH_1) {
        MODIFY_REG((GPTMRx)->CR1, TMR0_CR1_OIS0_Msk << (((uint32_t)(Channel) % 2) * 2), 
            (((IdleState) & TMR0_CR1_OIS0_Val) << (TMR0_CR1_OIS0_Pos + ((uint32_t)(Channel) % 2) * 2)));
    } else if (Channel <= LL_GPTMRX_CAP_CMP_CH_1N){
        MODIFY_REG((GPTMRx)->CR1, TMR0_CR1_OIS0N_Msk << (((uint32_t)(Channel) % 2) * 2), 
            (((IdleState) & TMR0_CR1_OIS0N_Val) << (TMR0_CR1_OIS0N_Pos + ((uint32_t)(Channel) % 2) * 2)));
    }
}

/**
  * @brief  Set the trigger input source (SCR.TS, 5 bits, raw value)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Tri Trigger selection @ref LL_GPTMRX_TrigTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetTriggerInput(GPTMRx_TypeDef *GPTMRx, uint32_t Tri)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->SCR, TMR0_SCR_TS_Msk, (((Tri) & TMR0_SCR_TS_Val) << TMR0_SCR_TS_Pos));
}

/**
  * @brief  Get the trigger input source
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Trigger input source @ref LL_GPTMRX_TrigTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetTrigger(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SCR, TMR0_SCR_TS_Msk, TMR0_SCR_TS_Pos));
}

/**
  * @brief  Set the slave mode (SCR.SMS, 4 bits, raw value)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRX_SlvModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetSlaveMode(GPTMRx_TypeDef *GPTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->SCR, TMR0_SCR_SMS_Msk, (((Mode) & TMR0_SCR_SMS_Val) << TMR0_SCR_SMS_Pos));
}

/**
  * @brief  Get the slave mode
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Slave mode @ref LL_GPTMRX_SlvModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetSlaveMode(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SCR, TMR0_SCR_SMS_Msk, TMR0_SCR_SMS_Pos));
}

/**
  * @brief  Enable the master/slave fast sync (SCR.FE)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableMstSlvFastSync(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->SCR, TMR0_SCR_FE_Msk);
}

/**
  * @brief  Disable the master/slave fast sync
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableMstSlvFastSync(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->SCR, TMR0_SCR_FE_Msk);
}

/**
  * @brief  Set the dead-time generator value (DCR.DTG, 8 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Dtg Dead-time value
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetFallingDeadTime(GPTMRx_TypeDef *GPTMRx, uint32_t Dtg)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->DCR, TMR0_DCR_DTG_Msk, (((Dtg) & TMR0_DCR_DTG_Val) << TMR0_DCR_DTG_Pos));
}

/**
  * @brief  Get the dead-time generator value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Dead-time generator value
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetFallingDeadTime(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->DCR, TMR0_DCR_DTG_Msk, TMR0_DCR_DTG_Pos));
}

/**
  * @brief  Set the dead-time digital filter clock division (CR0.DCD)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Div Dead-zone / digital filter clock division @ref LL_GPTMRX_DzDigFilClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetDzDigFilClkDiv(GPTMRx_TypeDef *GPTMRx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRX_DZ_DIG_FIL_CLK_DIV(Div));

    MODIFY_REG((GPTMRx)->CR0, TMR0_CR0_DCD_Msk, (((Div) & TMR0_CR0_DCD_Val) << TMR0_CR0_DCD_Pos));
}

/**
  * @brief  Get the dead-time digital filter clock division (CR0.DCD)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Clock division: @ref LL_GPTMRX_DZ_DIG_FIL_CLK_DIV_1 ... _8
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetDzDigFilClkDiv(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->CR0, TMR0_CR0_DCD_Msk, TMR0_CR0_DCD_Pos));
}

/**
  * @brief  Enable the main output (DCR.MOE)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableAllOutputs(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->DCR, TMR0_DCR_MOE_Msk);
}

/**
  * @brief  Disable the main output (DCR.MOE)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableAllOutputs(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->DCR, TMR0_DCR_MOE_Msk);
}

/**
  * @brief  Enable the automatic output (DCR.AOE)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableAutomaticOutput(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->DCR, TMR0_DCR_AOE_Msk);
}

/**
  * @brief  Disable the automatic output (DCR.AOE)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableAutomaticOutput(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->DCR, TMR0_DCR_AOE_Msk);
}

/**
  * @brief  Set the run-mode off-state of the outputs (DCR.OSSR)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Sta Output off-state @ref LL_GPTMRX_RunOffStaTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetRunModeOffState(GPTMRx_TypeDef *GPTMRx, uint32_t Sta)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRX_OUTPUT_STATE(Sta));

    MODIFY_REG((GPTMRx)->DCR, TMR0_DCR_OSSR_Msk, (((Sta) & TMR0_DCR_OSSR_Val) << TMR0_DCR_OSSR_Pos));
}

/**
  * @brief  Set the idle-mode off-state of the outputs (DCR.OSSI)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Sta Output off-state @ref LL_GPTMRX_IdleOffStaTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetIdleModeOffState(GPTMRx_TypeDef *GPTMRx, uint32_t Sta)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRX_OUTPUT_STATE(Sta));

    MODIFY_REG((GPTMRx)->DCR, TMR0_DCR_OSSI_Msk, (((Sta) & TMR0_DCR_OSSI_Val) << TMR0_DCR_OSSI_Pos));
}

/**
  * @brief  Enable break input 0 (DCR.BK0E)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableBreak0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->DCR, TMR0_DCR_BKE_Msk);
}

/**
  * @brief  Disable break input 0
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableBreak0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->DCR, TMR0_DCR_BKE_Msk);
}

/**
  * @brief  Set break input 0 polarity (DCR.BK0P)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Pol Polarity to be set @ref LL_GPTMRX_BrkPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetBreak0Polarity(GPTMRx_TypeDef *GPTMRx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->DCR, TMR0_DCR_BKP_Msk, (((Pol) & TMR0_DCR_BKP_Val) << TMR0_DCR_BKP_Pos));
}

/**
  * @brief  Set break input 0 filter (DCR.BK0F, 8 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Fil Filter value
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetBreak0Filter(GPTMRx_TypeDef *GPTMRx, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->DCR, TMR0_DCR_BKF_Msk, (((Fil) & TMR0_DCR_BKF_Val) << TMR0_DCR_BKF_Pos));
}

/**
  * @brief  Set the break input 0 source mask (BER.B0IEN, 16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  En Enable mask
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetBreak0InputEnable(GPTMRx_TypeDef *GPTMRx, uint32_t En)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->BER, TMR0_BER_BIEN_Msk, (((En) & TMR0_BER_BIEN_Val) << TMR0_BER_BIEN_Pos));
}

/**
  * @brief  Set the break input 0 polarity mask (BPR.B0POL, 16 bits)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Pol Polarity to be set @ref LL_GPTMRX_BrkPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetBreak0InputPolarity(GPTMRx_TypeDef *GPTMRx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->BPR, TMR0_BPR_BPOL_Msk, (((Pol) & TMR0_BPR_BPOL_Val) << TMR0_BPR_BPOL_Pos));
}

/**
  * @brief  Enable the break input 0 source 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  MskBit This parameter can be one of the LL_GPTMRX_BRK_IN_SRC_MASK_* @ref LL_GPTMRX_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableBreak0Input(GPTMRx_TypeDef *GPTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->BER, TMR0_BER_BIEN_Msk & (MskBit << TMR0_BER_BIEN_Pos));
}

/**
  * @brief  Disable the break input 0 source 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  MskBit This parameter can be one of the LL_GPTMRX_BRK_IN_SRC_MASK_* @ref LL_GPTMRX_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableBreak0Input(GPTMRx_TypeDef *GPTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->BER, TMR0_BER_BIEN_Msk & (MskBit << TMR0_BER_BIEN_Pos));
}

/**
  * @brief  Set the break input 0 polarity high
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  MskBit This parameter can be one of the LL_GPTMRX_BRK_IN_SRC_MASK_* @ref LL_GPTMRX_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetBreak0InputPolarityHigh(GPTMRx_TypeDef *GPTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->BPR, TMR0_BPR_BPOL_Msk & (MskBit << TMR0_BPR_BPOL_Pos));
}

/**
  * @brief  Set the break input 0 polarity low
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  MskBit This parameter can be one of the LL_GPTMRX_BRK_IN_SRC_MASK_* @ref LL_GPTMRX_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetBreak0InputPolarityLow(GPTMRx_TypeDef *GPTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->BPR, TMR0_BPR_BPOL_Msk & (MskBit << TMR0_BPR_BPOL_Pos));
}

/**
  * @brief  Generate a software update event
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_GenerateEvent_UPDATE(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->UGR, TMR0_UGR_UG_Msk);
}

/**
  * @brief  Generate a trigger event
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_GenerateEvent_TRIG(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->UGR, TMR0_UGR_TG_Msk);
}

/**
  * @brief  Generate a break 0 event (UGR.B0G)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_GenerateEvent_BRK0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->UGR, TMR0_UGR_BG_Msk);
}

/**
  * @brief  Generate a capture/compare 0 update event
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_GenerateEvent_CC0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->UGR, TMR0_UGR_CC0UG_Msk);
}

/**
  * @brief  Generate a capture/compare 1 update event
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_GenerateEvent_CC1(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->UGR, TMR0_UGR_CC1UG_Msk);
}

/**
  * @brief  Generate a update event
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_GenerateEvent_CCxUG(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    SET_BIT((GPTMRx)->UGR, (TMR0_UGR_CC0UG_Msk) << (((Channel) % 2UL) * 1UL));
}

/**
  * @brief  Set the input filter of a given capture channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Fil Filter value @ref LL_GPTMRX_CapFilTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_IC_SetFilter(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_OC0M_Msk << (((Channel) % 2UL) * 8UL), 
            (((Fil) & TMR0_CCMR_OC0M_Val) << (TMR0_CCMR_OC0M_Pos + ((Channel) % 2UL) * 8UL)));
}

/**
  * @brief  Set the output mode of a given compare channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Mode Mode (CCMR.OCxM) @ref LL_GPTMRX_OCModeTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_OC_SetMode(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_OC0M_Msk << (((Channel) % 2UL) * 8UL), 
            (((Mode) & TMR0_CCMR_OC0M_Val) << (TMR0_CCMR_OC0M_Pos + ((Channel) % 2UL) * 8UL)));
}

/**
  * @brief  Set the input prescaler of a given capture channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Prsc Prescaler value @ref LL_GPTMRX_CapPrscTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_IC_SetPrescaler(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Prsc)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_CC0PE_Msk << (((Channel) % 2UL) * 8UL), 
            (((Prsc) & TMR0_CCMR_CC0PE_Val) << (TMR0_CCMR_CC0PE_Pos + ((Channel) % 2UL) * 8UL)));
}

/**
  * @brief  Enable the output preload of a given compare channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_OC_EnablePreload(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_CC0PE_Msk << (((Channel) % 2UL) * 8UL), 
            (((0x1UL) & TMR0_CCMR_CC0PE_Val) << (TMR0_CCMR_CC0PE_Pos + ((Channel) % 2UL) * 8UL)));
}

/**
  * @brief  Disable the output preload of a given compare channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_OC_DisablePreload(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_CC0PE_Msk << (((Channel) % 2UL) * 8UL), 
            (((0x0UL) & TMR0_CCMR_CC0PE_Val) << (TMR0_CCMR_CC0PE_Pos + ((Channel) % 2UL) * 8UL)));
}

/**
  * @brief  Set the active input 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Active Capture/compare direction @ref LL_GPTMRX_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_IC_SetActiveInput(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Active)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_CC0S_Msk << (((Channel) % 2UL) * 8UL), 
            (((Active) & TMR0_CCMR_CC0S_Val) << (TMR0_CCMR_CC0S_Pos + ((Channel) % 2UL) * 8UL)));
}

/**
  * @brief  Get the active input 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return Capture/compare direction @ref LL_GPTMRX_CmpCapMapTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IC_GetActiveInput(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)(READ_BIT_SHIFT((GPTMRx)->CCMR, TMR9_CCMR_CC0S_Msk << (((Channel) % 4UL) * 8UL), 
            (TMR9_CCMR_CC0S_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the CC0 channel direction
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Dir Capture/compare direction @ref LL_GPTMRX_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetCapCmpDirCC0(GPTMRx_TypeDef *GPTMRx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_CC0S_Msk, (((Dir) & TMR0_CCMR_CC0S_Val) << TMR0_CCMR_CC0S_Pos));
}

/**
  * @brief  Set the CC1 channel direction
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Dir Capture/compare direction @ref LL_GPTMRX_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetCapCmpDirCC1(GPTMRx_TypeDef *GPTMRx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->CCMR, TMR0_CCMR_CC1S_Msk, (((Dir) & TMR0_CCMR_CC1S_Val) << TMR0_CCMR_CC1S_Pos));
}

/**
  * @brief  Set the output polarity of a given compare channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Pol Output Polarity @ref LL_GPTMRX_CmpPolTypeDef
  * @param  IsOCN @ref LL_GPTMRX_CapCmpOCTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_OC_SetPolarity(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Pol, uint32_t IsOCN)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRX_CAP_CMP_OC(IsOCN));

    if (!IsOCN) {
        MODIFY_REG((GPTMRx)->CCER, (0x1UL << TMR0_CCER_CC0P_Pos) << (((Channel) % 2UL) * 4UL), 
                (((Pol) & 0x1UL) << (TMR0_CCER_CC0P_Pos + ((Channel) % 2UL) * 4UL)));      
    } else {
        MODIFY_REG((GPTMRx)->CCER, (0x1UL << (TMR0_CCER_CC0P_Pos + 1UL)) << (((Channel) % 2UL) * 4UL), 
                (((Pol) & 0x1UL) << (((TMR0_CCER_CC0P_Pos + ((Channel) % 2UL) * 4UL)) + 1UL)));
    }
}

/**
  * @brief  Set the input polarity of a given capture channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Pol Input Polarity @ref LL_GPTMRX_CapPolTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_IC_SetPolarity(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CCER, TMR0_CCER_CC0P_Msk << (((Channel) % 2UL) * 4UL), 
            (((Pol) & 0x3UL) << (TMR0_CCER_CC0P_Pos + ((Channel) % 2UL) * 4UL)));
}

/**
  * @brief  Get the input polarity of a given capture channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval Input Polarity @ref LL_GPTMRX_CapPolTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IC_GetPolarity(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    return (uint32_t)(READ_BIT_SHIFT((GPTMRx)->CCER, TMR0_CCER_CC0P_Msk << (((Channel) % 2UL) * 4UL), 
                                                    (TMR0_CCER_CC0P_Pos + ((Channel) % 2UL) * 4UL)));
}

/**
  * @brief  Enable a given capture/compare channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_CC_EnableChannel(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CHANNEL(Channel)) && (Channel < 2));

    if (Channel <= LL_GPTMRX_CAP_CMP_CH_1) {
        MODIFY_REG((GPTMRx)->CCER, TMR0_CCER_CC0E_Msk << (((Channel) % 2UL) * 4UL), 
                (((0x1UL) & TMR0_CCER_CC0E_Val) << (TMR0_CCER_CC0E_Pos + ((Channel) % 2UL) * 4UL)));
    } else if (Channel <= LL_GPTMRX_CAP_CMP_CH_1N){
        MODIFY_REG((GPTMRx)->CCER, TMR0_CCER_CC0NE_Msk << (((Channel - LL_GPTMRX_CAP_CMP_CH_0N) % 2UL) * 4UL), 
                (((0x1UL) & TMR0_CCER_CC0NE_Val) << (TMR0_CCER_CC0NE_Pos + ((Channel) % 2UL) * 4UL)));
    }
}

/**
  * @brief  Disable a given capture/compare channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_CC_DisableChannel(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CHANNEL(Channel)) && (Channel < 2));

    if (Channel <= LL_GPTMRX_CAP_CMP_CH_1) {
        MODIFY_REG((GPTMRx)->CCER, TMR0_CCER_CC0E_Msk << (((Channel) % 2UL) * 4UL), 
                (((0x0UL) & TMR0_CCER_CC0E_Val) << (TMR0_CCER_CC0E_Pos + ((Channel) % 2UL) * 4UL)));
    } else if (Channel <= LL_GPTMRX_CAP_CMP_CH_1N){
        MODIFY_REG((GPTMRx)->CCER, TMR0_CCER_CC0NE_Msk << (((Channel) % 2UL) * 4UL), 
                (((0x0UL) & TMR0_CCER_CC0NE_Val) << (TMR0_CCER_CC0NE_Pos + ((Channel) % 2UL) * 4UL)));
    }
}

/**
  * @brief  Judge whether the all channel is disabled or not
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 A channel is enaabled
  * @retval 1 All channel is disabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_CC_IsAllChannelDisabled(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (uint32_t)((READ_BIT((GPTMRx)->CCER, LL_GPTMRX_CCER_CMP_CAP_CHNL_MSK) == 0UL) ? 1UL : 0UL );
}

/**
  * @brief  Disable a given capture/compare channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_CC_DisableAllChannel(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->CCER, LL_GPTMRX_CCER_CMP_CAP_CHNL_MSK );
}


/**
  * @brief  Set the CCx compare value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_OC_SetChannelCompare(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    WRITE_REG(LL_GPTMRX_REG_OFFSET((GPTMRx)->CC0R, (Channel % 4)), ((Val) & TMR0_CC0R_CC0V_Val));
}

/**
  * @brief  Get the CCx compare value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return CC0 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IC_GetChannelCompare(const GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return ((READ_REG(LL_GPTMRX_REG_OFFSET((GPTMRx)->CC0R, (Channel % 4)))) & TMR0_CC0R_CC0V_Val);
}


/**
  * @brief  Set the CC0 compare value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_OC_SetCompareCH0(GPTMRx_TypeDef *GPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->CC0R, ((Val) & TMR0_CC0R_CC0V_Val));
}

/**
  * @brief  Get the CC0 compare value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return CC0 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRX_OC_GetCompareCH0(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->CC0R) & TMR0_CC0R_CC0V_Val);
}

/**
  * @brief  Read the CC0 capture value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return CC0 capture value
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IC_GetCaptureCH0(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->CC0R) & TMR0_CC0R_CC0V_Val);
}

/**
  * @brief  Set the CC1 compare value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_OC_SetCompareCH1(GPTMRx_TypeDef *GPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->CC1R, ((Val) & TMR0_CC1R_CC1V_Val));
}

/**
  * @brief  Get the CC1 compare value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return CC1 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRX_OC_GetCompareCH1(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->CC1R) & TMR0_CC1R_CC1V_Val);
}

/**
  * @brief  Read the CC1 capture value
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return CC1 capture value
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IC_GetCaptureCH1(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->CC1R) & TMR0_CC1R_CC1V_Val);
}

/**
  * @brief  Select the input source of a given capture channel.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @param  Src Input source  @ref LL_GPTMRX_CapInputSrcTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRX_IC_SetInputSource(GPTMRx_TypeDef *GPTMRx, uint32_t Channel, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    MODIFY_REG((GPTMRx)->CIR, TMR0_CIR_C0TIS_Msk << (((Channel) % 2UL) * 8UL), 
            (((Src) & TMR0_CIR_C0TIS_Val) << (TMR0_CIR_C0TIS_Pos + ((Channel) % 2UL) * 8UL)));
}

/**
  * @brief  Set the master trigger output (TRGO) pulse width
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Width Output pulse width
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetTrigOutputWidth(GPTMRx_TypeDef *GPTMRx, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->TTCR, TMR0_TTCR_TOW_Msk, (((Width) & TMR0_TTCR_TOW_Val) << TMR0_TTCR_TOW_Pos));
}

/**
  * @brief  Get the master trigger output pulse width
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Master trigger output pulse width
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetTrigOutputWidth(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->TTCR, TMR0_TTCR_TOW_Msk, TMR0_TTCR_TOW_Pos));
}

/**
  * @brief  Set the trigger cycles width (TTCR.TCW)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Width Output pulse width
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_SetTrigCyclesWidth(GPTMRx_TypeDef *GPTMRx, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    MODIFY_REG((GPTMRx)->TTCR, TMR0_TTCR_TCW_Msk, (((Width) & TMR0_TTCR_TCW_Val) << TMR0_TTCR_TCW_Pos));
}

/**
  * @brief  Get the trigger cycles width (TTCR.TCW)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Trigger cycles width (TTCR.TCW)
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetTrigCyclesWidth(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->TTCR, TMR0_TTCR_TCW_Msk, TMR0_TTCR_TCW_Pos));
}

/**
  * @brief  Enable the CH0 trigger output (TTCR.TC0E)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableTriggerCH0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->TTCR, TMR0_TTCR_TC0E_Msk);
}

/**
  * @brief  Disable the CH0 trigger output
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableTriggerCH0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->TTCR, TMR0_TTCR_TC0E_Msk);
}

/**
  * @brief  Enable the CH1 trigger output (TTCR.TC1E)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableTriggerCH1(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->TTCR, TMR0_TTCR_TC1E_Msk);
}

/**
  * @brief  Disable the CH1 trigger output
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableTriggerCH1(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->TTCR, TMR0_TTCR_TC1E_Msk);
}

/**
  * @brief  Enable a channel trigger output
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableChannelTrigger(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    SET_BIT((GPTMRx)->TTCR, TMR0_TTCR_TC0E_Msk << ((Channel % 2UL) * 1UL));
}

/**
  * @brief  Disable a channel trigger output
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableChannelTrigger(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    CLEAR_BIT((GPTMRx)->TTCR, TMR0_TTCR_TC0E_Msk << ((Channel % 2UL) * 1UL));
}


/**
  * @}
  */

/** @defgroup GPTMRX_LL_EF_IT_Management LL GPTMRX Interrupt Management
  * @brief    LL GPTMRX Interrupt Management
  * @details    Per-channel capture/compare and over-capture interrupts.
  * @{
  */

/**
  * @brief  Enable the update interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_UPDATE(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_UIE_Msk);
}

/**
  * @brief  Disable the update interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_UPDATE(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_UIE_Msk);
}

/**
  * @brief  Enable the counter overflow interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_OVIE_Msk);
}

/**
  * @brief  Disable the counter overflow interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_OVIE_Msk);
}

/**
  * @brief  Judge whether the counter overflow interrupt is enabled or not
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Counter overflow interrupt is disabled
  * @retval 1 Counter overflow interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_OVR(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_OVIE_Msk, TMR0_IER_OVIE_Pos));
}

/**
  * @brief  Judge whether the update event interrupt is enabled or not
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Update event interrupt is disabled
  * @retval 1 Update event interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_UPDATE(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_UIE_Msk, TMR0_IER_UIE_Pos));
}

/**
  * @brief  Enable the trigger interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_TRIG(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_TIE_Msk);
}

/**
  * @brief  Disable the trigger interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_TRIG(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_TIE_Msk);
}

/**
  * @brief  Judge whether the trigger interrupt is enabled or not
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Trigger interrupt is disabled
  * @retval 1 Trigger interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_TRIG(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_TIE_Msk, TMR0_IER_TIE_Pos));
}

/**
  * @brief  Enable the break interrupt (both break inputs and system break)
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_BRK(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_BIE_Msk);
}

/**
  * @brief  Disable the break interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_BRK(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_BIE_Msk);
}

/**
  * @brief  Judge whether the break interrupt is enabled or not
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Break interrupt is disabled
  * @retval 1 Break interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_BRK(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_BIE_Msk, TMR0_IER_BIE_Pos));
}

/**
  * @brief  Get the whole interrupt enable register
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Whole interrupt enable register
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetAllIntEn(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->IER));
}

/**
  * @brief  Judge whether the counter overflow flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Counter overflow flag is cleared
  * @retval 1 Counter overflow flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_OVR(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_OVIF_Msk, TMR0_SR_OVIF_Pos));
}

/**
  * @brief  Clear the counter overflow flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_OVIF_Msk);
}

/**
  * @brief  Judge whether the update event flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Update event flag is cleared
  * @retval 1 Update event flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_UPDATE(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_UIF_Msk, TMR0_SR_UIF_Pos));
}

/**
  * @brief  Clear the update event flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_UPDATE(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_UIF_Msk);
}

/**
  * @brief  Judge whether the trigger flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Trigger flag is cleared
  * @retval 1 Trigger flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_TRIG(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_TIF_Msk, TMR0_SR_TIF_Pos));
}

/**
  * @brief  Clear the trigger flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_TRIG(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_TIF_Msk);
}

/**
  * @brief  Judge whether the break 0 flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 Break 0 flag is cleared
  * @retval 1 Break 0 flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_BRK0(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_BIF_Msk, TMR0_SR_BIF_Pos));
}

/**
  * @brief  Clear the break 0 flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_BRK0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_BIF_Msk);
}

/**
  * @brief  Judge whether the system fault break flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 System fault break flag is cleared
  * @retval 1 System fault break flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_SYSBRK(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_SBIF_Msk, TMR0_SR_SBIF_Pos));
}

/**
  * @brief  Clear the system fault break flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_SYSBRK(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_SBIF_Msk);
}

/**
  * @brief  Get the whole status register
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Whole status register
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetAllFlag(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_REG((GPTMRx)->SR));
}

/**
  * @brief  Enable the CCx capture/compare interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_CxMIE(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    SET_BIT((GPTMRx)->IER, TMR0_IER_C0MIE_Msk << ((Channel % 2UL) * 2UL));
}

/**
  * @brief  Disable the CCx capture/compare interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_CxMIE(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_C0MIE_Msk << ((Channel % 2UL) * 2UL));
}

/**
  * @brief  Judge whether the CCx capture/compare interrupt is enabled
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval 0 CCx capture/compare interrupt is disabled
  * @retval 1 CCx capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_CxMIE(const GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    return (uint32_t)((READ_BIT((GPTMRx)->IER, TMR0_IER_C0MIE_Msk << ((Channel % 2UL) * 2UL))) ? 1UL : 0UL);
}

/**
  * @brief  Judge whether the CCx over-capture interrupt is enabled
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval 0 CCx over-capture interrupt is disabled
  * @retval 1 CCx over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_CxOIE(const GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    return (uint32_t)((READ_BIT((GPTMRx)->IER, TMR0_IER_C0OIE_Msk << ((Channel % 2UL) * 2UL))) ? 1UL : 0UL);
}

/**
  * @brief  Enable the CC0 capture/compare interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_CC0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_C0MIE_Msk);
}

/**
  * @brief  Disable the CC0 capture/compare interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_CC0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_C0MIE_Msk);
}

/**
  * @brief  Judge whether the CC0 capture/compare interrupt is enabled
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC0 capture/compare interrupt is disabled
  * @retval 1 CC0 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_CC0(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_C0MIE_Msk, TMR0_IER_C0MIE_Pos));
}

/**
  * @brief  Enable the CC0 over-capture interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_CC0OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_C0OIE_Msk);
}

/**
  * @brief  Disable the CC0 over-capture interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_CC0OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_C0OIE_Msk);
}

/**
  * @brief  Judge whether the CC0 over-capture interrupt is enabled
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC0 over-capture interrupt is disabled
  * @retval 1 CC0 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_CC0OVR(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_C0OIE_Msk, TMR0_IER_C0OIE_Pos));
}

/**
  * @brief  Enable the CC1 capture/compare interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_CC1(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_C1MIE_Msk);
}

/**
  * @brief  Disable the CC1 capture/compare interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_CC1(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_C1MIE_Msk);
}

/**
  * @brief  Judge whether the CC1 capture/compare interrupt is enabled
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC1 capture/compare interrupt is disabled
  * @retval 1 CC1 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_CC1(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_C1MIE_Msk, TMR0_IER_C1MIE_Pos));
}

/**
  * @brief  Enable the CC1 over-capture interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT_CC1OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT((GPTMRx)->IER, TMR0_IER_C1OIE_Msk);
}

/**
  * @brief  Disable the CC1 over-capture interrupt
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT_CC1OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT((GPTMRx)->IER, TMR0_IER_C1OIE_Msk);
}

/**
  * @brief  Judge whether the CC1 over-capture interrupt is enabled
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC1 over-capture interrupt is disabled
  * @retval 1 CC1 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT_CC1OVR(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->IER, TMR0_IER_C1OIE_Msk, TMR0_IER_C1OIE_Pos));
}

/**
  * @brief  Judge whether the CCx capture/compare flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CCx capture/compare flag is cleared
  * @retval 1 CCx capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_CCxMIF(const GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    return (uint32_t)((READ_BIT((GPTMRx)->SR, (TMR0_SR_CC0MIF_Msk << ((Channel % 2UL) * 2UL)))) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CCx capture/compare flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_CCxMIF(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_CC0MIF_Msk << ((Channel % 2UL) * 2UL));
}

/**
  * @brief  Judge whether the CCx over-capture flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @retval 0 CCx over-capture flag is cleared
  * @retval 1 CCx over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_CCxOIF(const GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    return (uint32_t)((READ_BIT((GPTMRx)->SR, (TMR0_SR_CC0OIF_Msk << ((Channel % 2UL) * 2UL)))) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CCx over-capture flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRX_CapCmpChTypeDef (LL_GPTMRX_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_CCxOIF(GPTMRx_TypeDef *GPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRX_CAP_CMP_CH(Channel)) && (Channel < 2UL));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_CC0OIF_Msk << ((Channel % 2UL) * 2UL));
}

/**
  * @brief  Judge whether the CC0 capture/compare flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC0 capture/compare flag is cleared
  * @retval 1 CC0 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_CC0(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_CC0MIF_Msk, TMR0_SR_CC0MIF_Pos));
}

/**
  * @brief  Clear the CC0 capture/compare flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_CC0(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_CC0MIF_Msk);
}

/**
  * @brief  Judge whether the CC0 over-capture flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC0 over-capture flag is cleared
  * @retval 1 CC0 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_CC0OVR(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_CC0OIF_Msk, TMR0_SR_CC0OIF_Pos));
}

/**
  * @brief  Clear the CC0 over-capture flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_CC0OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_CC0OIF_Msk);
}

/**
  * @brief  Judge whether the CC1 capture/compare flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC1 capture/compare flag is cleared
  * @retval 1 CC1 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_CC1(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_CC1MIF_Msk, TMR0_SR_CC1MIF_Pos));
}

/**
  * @brief  Clear the CC1 capture/compare flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_CC1(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_CC1MIF_Msk);
}

/**
  * @brief  Judge whether the CC1 over-capture flag is set
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval 0 CC1 over-capture flag is cleared
  * @retval 1 CC1 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag_CC1OVR(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT_SHIFT((GPTMRx)->SR, TMR0_SR_CC1OIF_Msk, TMR0_SR_CC1OIF_Pos));
}

/**
  * @brief  Clear the CC1 over-capture flag
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag_CC1OVR(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG((GPTMRx)->SR, TMR0_SR_CC1OIF_Msk);
}

/**
  * @brief  GPTMRX Interrupt enable
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mask Mask to enable @ref LL_GPTMRX_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_EnableIT(GPTMRx_TypeDef *GPTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    SET_BIT(GPTMRx->IER, Mask);
}

/**
  * @brief  GPTMRX Interrupt disable
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mask Mask to disable @ref LL_GPTMRX_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_DisableIT(GPTMRx_TypeDef *GPTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    CLEAR_BIT(GPTMRx->IER, Mask);
}

/**
  * @brief  Check if GPTMRX Interrupt is enabled or disabled
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mask Mask to check @ref LL_GPTMRX_IER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsEnabledIT(const GPTMRx_TypeDef *GPTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(GPTMRx->IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mask Mask to clear @ref LL_GPTMRX_SR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRX_ClearFlag(GPTMRx_TypeDef *GPTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    WRITE_REG(GPTMRx->SR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @param  Mask Mask to check @ref LL_GPTMRX_SR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPTMRX_IsActiveFlag(const GPTMRx_TypeDef *GPTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(GPTMRx->SR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  GPTMRX Interrupt All Enable Get
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Interrupt Enable Bit
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetAllEnabledIT(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT(GPTMRx->IER, LL_GPTMRX_IER_IT_EN_MSK));
}

/**
  * @brief  Get interrupt status of the specified GPTMRX channel 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @return Interrupt status
  */
__STATIC_INLINE uint32_t LL_GPTMRX_GetAllITPending(const GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_INLINE_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    return (READ_BIT(GPTMRx->SR, LL_GPTMRX_SR_IT_FLAG_MSK));
}


/**
  * @}
  */ /* GPTMRX_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* GPTMRX_LL_Exported_Functions */

#endif /* GPTMRX */

/**
  * @}
  */ /* GPTMRX_LL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_GPTMRX_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/









