/**
  ******************************************************************************
  * @file    tae32g58xx_ll_gptmry.h
  * @author  Tai-Action SD Team
  * @brief   Header file for GPTMRY (General Purpose Timer) LL module
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
#ifndef _TAE32G58XX_LL_GPTMRY_H_
#define _TAE32G58XX_LL_GPTMRY_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(TMR3) || defined(TMR4)

/** @defgroup GPTMRY_LL GPTMRY LL
  * @brief    GPTMRY LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup GPTMRY_LL_Exported_Constants GPTMRY LL Exported Constants
  * @brief    GPTMRY LL Exported Constants
  * @{
  */

/** @name LL_GPTMRY_IER_ITEnMskTypeDef
  * @brief GPTMRY LL Interrupt Enable Masks
  * @{
  */
#define LL_GPTMRY_IER_ITEnMskTypeDef     uint32_t

#define LL_GPTMRY_IER_TIE                (TMR3_IER_TIE_Msk)      /*!< Trigger interrupt enable        */
#define LL_GPTMRY_IER_OVIE               (TMR3_IER_OVIE_Msk)     /*!< Overflow interrupt enable       */
#define LL_GPTMRY_IER_UIE                (TMR3_IER_UIE_Msk)      /*!< Update interrupt enable         */
#define LL_GPTMRY_IER_C3OIE              (TMR3_IER_C3OIE_Msk)    /*!< CH3 output compare interrupt enable */
#define LL_GPTMRY_IER_C3MIE              (TMR3_IER_C3MIE_Msk)    /*!< CH3 input capture interrupt enable  */
#define LL_GPTMRY_IER_C2OIE              (TMR3_IER_C2OIE_Msk)    /*!< CH2 output compare interrupt enable */
#define LL_GPTMRY_IER_C2MIE              (TMR3_IER_C2MIE_Msk)    /*!< CH2 input capture interrupt enable  */
#define LL_GPTMRY_IER_C1OIE              (TMR3_IER_C1OIE_Msk)    /*!< CH1 output compare interrupt enable */
#define LL_GPTMRY_IER_C1MIE              (TMR3_IER_C1MIE_Msk)    /*!< CH1 input capture interrupt enable  */
#define LL_GPTMRY_IER_C0OIE              (TMR3_IER_C0OIE_Msk)    /*!< CH0 output compare interrupt enable */
#define LL_GPTMRY_IER_C0MIE              (TMR3_IER_C0MIE_Msk)    /*!< CH0 input capture interrupt enable  */

#define LL_GPTMRY_IER_IT_EN_MSK          ((TMR3_IER_TIE_Msk                | \
                                           TMR3_IER_OVIE_Msk               | TMR3_IER_UIE_Msk                | \
                                           TMR3_IER_C3OIE_Msk              | TMR3_IER_C3MIE_Msk              | \
                                           TMR3_IER_C2OIE_Msk              | TMR3_IER_C2MIE_Msk              | \
                                           TMR3_IER_C1OIE_Msk              | TMR3_IER_C1MIE_Msk              | \
                                           TMR3_IER_C0OIE_Msk              | TMR3_IER_C0MIE_Msk              ))

#define LL_GPTMRY_IER_CC_IT_EN_MSK       ((TMR3_IER_C3OIE_Msk              | TMR3_IER_C3MIE_Msk              | \
                                           TMR3_IER_C2OIE_Msk              | TMR3_IER_C2MIE_Msk              | \
                                           TMR3_IER_C1OIE_Msk              | TMR3_IER_C1MIE_Msk              | \
                                           TMR3_IER_C0OIE_Msk              | TMR3_IER_C0MIE_Msk              ))
/**
  * @}
  */

/** @name LL_GPTMRY_SR_ITPendingMskTypeDef
  * @brief GPTMRY LL Status Flag Masks
  * @{
  */
#define LL_GPTMRY_SR_ITPendingMskTypeDef uint32_t

#define LL_GPTMRY_SR_TIF                 (TMR3_SR_TIF_Msk)       /*!< Trigger flag                    */
#define LL_GPTMRY_SR_OVIF                (TMR3_SR_OVIF_Msk)      /*!< Overflow flag                   */
#define LL_GPTMRY_SR_UIF                 (TMR3_SR_UIF_Msk)       /*!< Update flag                     */
#define LL_GPTMRY_SR_CC3OIF              (TMR3_SR_CC3OIF_Msk)    /*!< CH3 output compare flag         */
#define LL_GPTMRY_SR_CC3MIF              (TMR3_SR_CC3MIF_Msk)    /*!< CH3 input capture flag          */
#define LL_GPTMRY_SR_CC2OIF              (TMR3_SR_CC2OIF_Msk)    /*!< CH2 output compare flag         */
#define LL_GPTMRY_SR_CC2MIF              (TMR3_SR_CC2MIF_Msk)    /*!< CH2 input capture flag          */
#define LL_GPTMRY_SR_CC1OIF              (TMR3_SR_CC1OIF_Msk)    /*!< CH1 output compare flag         */
#define LL_GPTMRY_SR_CC1MIF              (TMR3_SR_CC1MIF_Msk)    /*!< CH1 input capture flag          */
#define LL_GPTMRY_SR_CC0OIF              (TMR3_SR_CC0OIF_Msk)    /*!< CH0 output compare flag         */
#define LL_GPTMRY_SR_CC0MIF              (TMR3_SR_CC0MIF_Msk)    /*!< CH0 input capture flag          */

#define LL_GPTMRY_SR_IT_FLAG_MSK         ((TMR3_SR_TIF_Msk                 | \
                                           TMR3_SR_OVIF_Msk                | TMR3_SR_UIF_Msk                 | \
                                           TMR3_SR_CC3OIF_Msk              | TMR3_SR_CC3MIF_Msk              | \
                                           TMR3_SR_CC2OIF_Msk              | TMR3_SR_CC2MIF_Msk              | \
                                           TMR3_SR_CC1OIF_Msk              | TMR3_SR_CC1MIF_Msk              | \
                                           TMR3_SR_CC0OIF_Msk              | TMR3_SR_CC0MIF_Msk              ))

#define LL_GPTMRY_SR_CC_IT_FLAG_MSK      ((TMR3_SR_CC3OIF_Msk              | TMR3_SR_CC3MIF_Msk              | \
                                           TMR3_SR_CC2OIF_Msk              | TMR3_SR_CC2MIF_Msk              | \
                                           TMR3_SR_CC1OIF_Msk              | TMR3_SR_CC1MIF_Msk              | \
                                           TMR3_SR_CC0OIF_Msk              | TMR3_SR_CC0MIF_Msk              ))

#define LL_GPTMRY_SR_UPD_IT_FLAG_MSK     ((TMR3_SR_OVIF_Msk                 | TMR3_SR_UIF_Msk                ))
/** @} */

#define LL_GPTMRY_CCER_CMP_CAP_CHNL_MSK  ((TMR3_CCER_CC3E_Msk              | TMR3_CCER_CC2E_Msk              | \
                                           TMR3_CCER_CC1E_Msk              | TMR3_CCER_CC0E_Msk              ))

/** @name LL_GPTMRY_TTCR_TrigOutChMskTypeDef
  * @brief GPTMRY LL TTCR TRGO Channel Selection
  * @{
  */
#define LL_GPTMRY_TTCR_TrigOutChMskTypeDef          uint32_t

#define LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH3          (TMR3_TTCR_TC3E_Msk)
#define LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH2          (TMR3_TTCR_TC2E_Msk)
#define LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH1          (TMR3_TTCR_TC1E_Msk)
#define LL_GPTMRY_TTCR_TRGI_OUT_SELECT_CH0          (TMR3_TTCR_TC0E_Msk)
/** @} */

/** @name LL_GPTMRY_TI0InSrcTypeDef
  * @brief GPTMRY LL TI0 Input Source
  * @{
  */
#define LL_GPTMRY_TI0InSrcTypeDef        LL_RSV_DATA_TYPE

#define LL_GPTMRY_TI0_IN_SRC_CH0         (0UL)   
#define LL_GPTMRY_TI0_IN_SRC_CH0_1_2_XOR (1UL)   

#define IS_LL_GPTMRY_TI0_IN_SRC(__VAL__)             (((__VAL__) == LL_GPTMRY_TI0_IN_SRC_CH0) || \
                                                      ((__VAL__) == LL_GPTMRY_TI0_IN_SRC_CH0_1_2_XOR))
/** @} */

/** @name LL_GPTMRY_WorkModeTypeDef
  * @brief GPTMRY LL Work Mode (CR0.OPM)
  * @{
  */
#define LL_GPTMRY_WorkModeTypeDef        LL_RSV_DATA_TYPE

#define LL_GPTMRY_WORK_MODE_CONTINUE     (0UL)   /*!< Continue mode */
#define LL_GPTMRY_WORK_MODE_SINGLE       (1UL)   /*!< Single mode   */

#define IS_LL_GPTMRY_WORK_MODE(__VAL__)              (((__VAL__) == LL_GPTMRY_WORK_MODE_CONTINUE) || \
                                                      ((__VAL__) == LL_GPTMRY_WORK_MODE_SINGLE))
/** @} */

/** @name LL_GPTMRY_UpdateEvtSrcTypeDef
  * @brief GPTMRY LL Update Event Source (CR0.URS)
  * @{
  */
#define LL_GPTMRY_UpdateEvtSrcTypeDef    LL_RSV_DATA_TYPE

#define LL_GPTMRY_UPDATE_EVT_SRC_OV_UG   (0UL)   /*!< Overflow and software (UG) */
#define LL_GPTMRY_UPDATE_EVT_SRC_OV      (1UL)   /*!< Only overflow              */

#define IS_LL_GPTMRY_UPDATE_EVT_SRC(__VAL__)         (((__VAL__) == LL_GPTMRY_UPDATE_EVT_SRC_OV_UG) || \
                                                      ((__VAL__) == LL_GPTMRY_UPDATE_EVT_SRC_OV))
/** @} */

/** @name LL_GPTMRY_CntDirTypeDef
  * @brief GPTMRY LL Counter Direction (CR0.DIR)
  * @{
  */
#define LL_GPTMRY_CntDirTypeDef          LL_RSV_DATA_TYPE

#define LL_GPTMRY_CNT_DIR_INC            (0UL)   /*!< Up counting   */
#define LL_GPTMRY_CNT_DIR_DEC            (1UL)   /*!< Down counting */

#define IS_LL_GPTMRY_CNT_DIR(__VAL__)                (((__VAL__) == LL_GPTMRY_CNT_DIR_INC) || \
                                                      ((__VAL__) == LL_GPTMRY_CNT_DIR_DEC))

/** @} */

/** @name LL_GPTMRY_CtrAlignModeTypeDef
  * @brief GPTMRY LL Counter Align Mode (CR0.CMS)
  * @{
  */
#define LL_GPTMRY_CtrAlignModeTypeDef            LL_RSV_DATA_TYPE

#define LL_GPTMRY_CTR_ALIGN_MODE_EDGE            (0UL)   /*!< Edge-aligned          */
#define LL_GPTMRY_CTR_ALIGN_MODE_CENTER_1        (1UL)   /*!< Center-aligned mode 1 */
#define LL_GPTMRY_CTR_ALIGN_MODE_CENTER_2        (2UL)   /*!< Center-aligned mode 2 */
#define LL_GPTMRY_CTR_ALIGN_MODE_CENTER_3        (3UL)   /*!< Center-aligned mode 3 */

#define IS_LL_GPTMRY_CTR_ALIGN_MODE(__VAL__)         (((__VAL__) == LL_GPTMRY_CTR_ALIGN_MODE_EDGE) || \
                                                      ((__VAL__) == LL_GPTMRY_CTR_ALIGN_MODE_CENTER_1) || \
                                                      ((__VAL__) == LL_GPTMRY_CTR_ALIGN_MODE_CENTER_2) || \
                                                      ((__VAL__) == LL_GPTMRY_CTR_ALIGN_MODE_CENTER_3))
/** @} */

/** @name LL_GPTMRY_OutputIdleStaTypeDef
  * @brief GPTMRY LL Output Idle State
  * @{
  */
#define LL_GPTMRY_OutputIdleStaTypeDef               LL_RSV_DATA_TYPE    

#define LL_GPTMRY_OUTPUT_IDLE_STA_LOW                (0UL)                /*!< Output Idle State Low                            */
#define LL_GPTMRY_OUTPUT_IDLE_STA_HIGH               (1UL)                /*!< Output Idle State High                           */

#define IS_LL_GPTMRY_OUTPUT_IDLE_STA(__VAL__)        (((__VAL__) == LL_GPTMRY_OUTPUT_IDLE_STA_LOW)  || \
                                                      ((__VAL__) == LL_GPTMRY_OUTPUT_IDLE_STA_HIGH) )
/** @} */

/** @name LL_GPTMRY_MstModeTypeDef
  * @brief GPTMRY LL Master Mode (CR1.MMS)
  * @{
  */
#define LL_GPTMRY_MstModeTypeDef         LL_RSV_DATA_TYPE

#define LL_GPTMRY_MST_MODE_RESET         (0UL)   /*!< TRGO = counter reset (UG)    */
#define LL_GPTMRY_MST_MODE_ENABLE        (1UL)   /*!< TRGO = counter enable        */
#define LL_GPTMRY_MST_MODE_UPDATE        (2UL)   /*!< TRGO = update event          */
#define LL_GPTMRY_MST_MODE_CAP_CMP_EVT   (3UL)   /*!< TRGO = capture/compare event */
#define LL_GPTMRY_MST_MODE_OC0REF        (4UL)   /*!< TRGO = OC0REF                */
#define LL_GPTMRY_MST_MODE_OC1REF        (5UL)   /*!< TRGO = OC1REF                */
#define LL_GPTMRY_MST_MODE_OC2REF        (6UL)   /*!< TRGO = OC2REF                */
#define LL_GPTMRY_MST_MODE_OC3REF        (7UL)   /*!< TRGO = OC3REF                */

#define IS_LL_GPTMRY_MST_MODE(__VAL__)              (((__VAL__) == LL_GPTMRY_MST_MODE_RESET)       || \
                                                     ((__VAL__) == LL_GPTMRY_MST_MODE_ENABLE)      || \
                                                     ((__VAL__) == LL_GPTMRY_MST_MODE_UPDATE)      || \
                                                     ((__VAL__) == LL_GPTMRY_MST_MODE_CAP_CMP_EVT) || \
                                                     ((__VAL__) == LL_GPTMRY_MST_MODE_OC0REF)      || \
                                                     ((__VAL__) == LL_GPTMRY_MST_MODE_OC1REF)      || \
                                                     ((__VAL__) == LL_GPTMRY_MST_MODE_OC2REF)      || \
                                                     ((__VAL__) == LL_GPTMRY_MST_MODE_OC3REF))

/** @} */

/** @name LL_GPTMRY_ETRModeTypeDef
  * @brief GPTMRY LL ETR Mode (SCR.EE)
  * @{
  */
#define LL_GPTMRY_ETRModeTypeDef         LL_RSV_DATA_TYPE

#define LL_GPTMRY_ETR_MODE_EXT_CLK_1     (0UL)   /*!< External clock mode 1 */
#define LL_GPTMRY_ETR_MODE_EXT_CLK_2     (1UL)   /*!< External clock mode 2 */

#define IS_LL_GPTMRY_ETR_MODE(__VAL__)              (((__VAL__) == LL_GPTMRY_ETR_MODE_EXT_CLK_1) || \
                                                     ((__VAL__) == LL_GPTMRY_ETR_MODE_EXT_CLK_2))
/** @} */

/** @name LL_GPTMRY_ETRFilTypeDef
  * @brief GPTMRY LL ETR Filter
  * @{
  */
#define LL_GPTMRY_ETRFilTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRY_ETR_FILTER_NONE            (0UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X1          (1UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X2          (2UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X3          (3UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X4          (4UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X5          (5UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X6          (6UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X7          (7UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X8          (8UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X9          (9UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X10         (10UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X11         (11UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X12         (12UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X13         (13UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X14         (14UL)
#define LL_GPTMRY_ETR_FILTER_TDS_X15         (15UL)

#define IS_LL_GPTMRY_ETR_FILTER(__VAL__)     (((__VAL__) >= LL_GPTMRY_ETR_FILTER_NONE) && \
                                              ((__VAL__) <= LL_GPTMRY_ETR_FILTER_TDS_X15))
/** @} */


/** @name LL_GPTMRY_ETREdgeTypeDef
  * @brief GPTMRY LL ETR Edge Mode (SCR.EMS)
  * @{
  */
#define LL_GPTMRY_ETREdgeTypeDef                 LL_RSV_DATA_TYPE


#define LL_GPTMRY_ETR_EDGE_MODE_CLOSE            (0UL)   /*!< Trigger closed                */
#define LL_GPTMRY_ETR_EDGE_MODE_RISING           (1UL)   /*!< Rising edge                   */
#define LL_GPTMRY_ETR_EDGE_MODE_FALLING          (2UL)   /*!< Falling edge                  */
#define LL_GPTMRY_ETR_EDGE_MODE_RISING_FALLING   (3UL)   /*!< Both rising and falling edges */

#define IS_LL_GPTMRY_ETR_EDGE_MODE(__VAL__)         (((__VAL__) == LL_GPTMRY_ETR_EDGE_MODE_CLOSE) || \
                                                     ((__VAL__) == LL_GPTMRY_ETR_EDGE_MODE_RISING) || \
                                                     ((__VAL__) == LL_GPTMRY_ETR_EDGE_MODE_FALLING) || \
                                                     ((__VAL__) == LL_GPTMRY_ETR_EDGE_MODE_RISING_FALLING))
/** @} */

/** @name LL_GPTMRY_TrigTypeDef
  * @brief GPTMRY LL Trigger Selection (SCR.TS)
  * @{
  */
#define LL_GPTMRY_TrigTypeDef            LL_RSV_DATA_TYPE

/* Generic internal trigger sources */
#define LL_GPTMRY_TRIG_ITR0              (0UL)   /*!< Internal trigger ITR0  */
#define LL_GPTMRY_TRIG_ITR1              (1UL)   /*!< Internal trigger ITR1  */
#define LL_GPTMRY_TRIG_ITR2              (2UL)   /*!< Internal trigger ITR2  */
#define LL_GPTMRY_TRIG_ITR3              (3UL)   /*!< Internal trigger ITR3  */
#define LL_GPTMRY_TRIG_ITR4              (4UL)   /*!< Internal trigger ITR4  */
#define LL_GPTMRY_TRIG_ITR5              (5UL)   /*!< Internal trigger ITR5  */
#define LL_GPTMRY_TRIG_ITR6              (6UL)   /*!< Internal trigger ITR6  */
#define LL_GPTMRY_TRIG_ITR7              (7UL)   /*!< Internal trigger ITR7  */
#define LL_GPTMRY_TRIG_ITR8              (8UL)   /*!< Internal trigger ITR8  */
#define LL_GPTMRY_TRIG_ITR9              (9UL)   /*!< Internal trigger ITR9  */
#define LL_GPTMRY_TRIG_ITR10             (10UL)  /*!< Internal trigger ITR10 */
#define LL_GPTMRY_TRIG_ITR11             (11UL)  /*!< Internal trigger ITR11 */
#define LL_GPTMRY_TRIG_ITR12             (12UL)  /*!< Internal trigger ITR12 */
#define LL_GPTMRY_TRIG_ITR13             (13UL)  /*!< Internal trigger ITR13 */
#define LL_GPTMRY_TRIG_ITR14             (14UL)  /*!< Internal trigger ITR14 */
#define LL_GPTMRY_TRIG_ITR15             (15UL)  /*!< Internal trigger ITR15 */

#define LL_GPTMRY_TRIG_CH0_FE            (16UL)  /*!< Channel 0 rising edge  */
#define LL_GPTMRY_TRIG_CH0_F             (17UL)  /*!< Channel 0 falling edge */
#define LL_GPTMRY_TRIG_CH1_F             (18UL)  /*!< Channel 1 falling edge */
#define LL_GPTMRY_TRIG_CH2_F             (19UL)  /*!< Channel 2 falling edge */
#define LL_GPTMRY_TRIG_CH3_F             (20UL)  /*!< Channel 3 falling edge */
#define LL_GPTMRY_TRIG_ETR_FE            (21UL)  /*!< ETR rising edge        */
#define LL_GPTMRY_TRIG_ETR_F             (22UL)  /*!< ETR falling edge       */

/* Per-instance trigger mapping: TMR3 */
#define LL_GPTMRY_TRIG_TMR3_ITR0_TMR7_TRGO           (0UL)    /*!< TMR3 ITR0: TMR7_TRGO      */
#define LL_GPTMRY_TRIG_TMR3_ITR1_TMR8_TRGO           (1UL)    /*!< TMR3 ITR1: TMR8_TRGO      */
#define LL_GPTMRY_TRIG_TMR3_ITR2_TMR0_TRGO           (2UL)    /*!< TMR3 ITR2: TMR0_TRGO      */
#define LL_GPTMRY_TRIG_TMR3_ITR3_TMR1_TRGO           (3UL)    /*!< TMR3 ITR3: TMR1_TRGO      */
#define LL_GPTMRY_TRIG_TMR3_ITR4_TMR2_TRGO           (4UL)    /*!< TMR3 ITR4: TMR2_TRGO      */
#define LL_GPTMRY_TRIG_TMR3_ITR5_TMR4_TRGO           (5UL)    /*!< TMR3 ITR5: TMR4_TRGO      */
#define LL_GPTMRY_TRIG_TMR3_ITR6_TMR0_OC0            (6UL)    /*!< TMR3 ITR6: TMR0_OC0       */
#define LL_GPTMRY_TRIG_TMR3_ITR7_TMR1_OC0            (7UL)    /*!< TMR3 ITR7: TMR1_OC0       */
#define LL_GPTMRY_TRIG_TMR3_ITR8_TMR2_OC0            (8UL)    /*!< TMR3 ITR8: TMR2_OC0       */
#define LL_GPTMRY_TRIG_TMR3_ITR9_TMR4_OC0            (9UL)    /*!< TMR3 ITR9: TMR4_OC0       */
#define LL_GPTMRY_TRIG_TMR3_ITR10_TMR9_TRGO          (10UL)   /*!< TMR3 ITR10: TMR9_TRGO     */
#define LL_GPTMRY_TRIG_TMR3_ITR11_TMR9_OC0           (11UL)   /*!< TMR3 ITR11: TMR9_OC0      */
#define LL_GPTMRY_TRIG_TMR3_ITR12_TMR9_OC1           (12UL)   /*!< TMR3 ITR12: TMR9_OC1      */
#define LL_GPTMRY_TRIG_TMR3_ITR13_TMR10_TRGO         (13UL)   /*!< TMR3 ITR13: TMR10_TRGO    */
#define LL_GPTMRY_TRIG_TMR3_ITR14_TMR10_OC0          (14UL)   /*!< TMR3 ITR14: TMR10_OC0     */
#define LL_GPTMRY_TRIG_TMR3_ITR15_HRPWM_SYNCO        (15UL)   /*!< TMR3 ITR15: HRPWM_SYNCO   */

/* Per-instance trigger mapping: TMR4 */
#define LL_GPTMRY_TRIG_TMR4_ITR0_TMR7_TRGO           (0UL)    /*!< TMR4 ITR0: TMR7_TRGO      */
#define LL_GPTMRY_TRIG_TMR4_ITR1_TMR8_TRGO           (1UL)    /*!< TMR4 ITR1: TMR8_TRGO      */
#define LL_GPTMRY_TRIG_TMR4_ITR2_TMR0_TRGO           (2UL)    /*!< TMR4 ITR2: TMR0_TRGO      */
#define LL_GPTMRY_TRIG_TMR4_ITR3_TMR1_TRGO           (3UL)    /*!< TMR4 ITR3: TMR1_TRGO      */
#define LL_GPTMRY_TRIG_TMR4_ITR4_TMR2_TRGO           (4UL)    /*!< TMR4 ITR4: TMR2_TRGO      */
#define LL_GPTMRY_TRIG_TMR4_ITR5_TMR3_TRGO           (5UL)    /*!< TMR4 ITR5: TMR3_TRGO      */
#define LL_GPTMRY_TRIG_TMR4_ITR6_TMR0_OC0            (6UL)    /*!< TMR4 ITR6: TMR0_OC0       */
#define LL_GPTMRY_TRIG_TMR4_ITR7_TMR1_OC0            (7UL)    /*!< TMR4 ITR7: TMR1_OC0       */
#define LL_GPTMRY_TRIG_TMR4_ITR8_TMR2_OC0            (8UL)    /*!< TMR4 ITR8: TMR2_OC0       */
#define LL_GPTMRY_TRIG_TMR4_ITR9_TMR3_OC0            (9UL)    /*!< TMR4 ITR9: TMR3_OC0       */
#define LL_GPTMRY_TRIG_TMR4_ITR10_TMR9_TRGO          (10UL)   /*!< TMR4 ITR10: TMR9_TRGO     */
#define LL_GPTMRY_TRIG_TMR4_ITR11_TMR9_OC0           (11UL)   /*!< TMR4 ITR11: TMR9_OC0      */
#define LL_GPTMRY_TRIG_TMR4_ITR12_TMR9_OC1           (12UL)   /*!< TMR4 ITR12: TMR9_OC1      */
#define LL_GPTMRY_TRIG_TMR4_ITR13_TMR10_TRGO         (13UL)   /*!< TMR4 ITR13: TMR10_TRGO    */
#define LL_GPTMRY_TRIG_TMR4_ITR14_TMR10_OC0          (14UL)   /*!< TMR4 ITR14: TMR10_OC0     */
#define LL_GPTMRY_TRIG_TMR4_ITR15_HRPWM_SYNCO        (15UL)   /*!< TMR4 ITR15: HRPWM_SYNCO   */

/** @} */

/** @name LL_GPTMRY_CapCmpChTypeDef
  * @brief GPTMRY LL Capture/Compare Channel (4 channels)
  * @{
  */
#define LL_GPTMRY_CapCmpChTypeDef            uint32_t
#define LL_GPTMRY_CAP_CMP_CH_0               (0UL)   /*!< Capture/Compare channel 0 */
#define LL_GPTMRY_CAP_CMP_CH_1               (1UL)   /*!< Capture/Compare channel 1 */
#define LL_GPTMRY_CAP_CMP_CH_2               (2UL)   /*!< Capture/Compare channel 2 */
#define LL_GPTMRY_CAP_CMP_CH_3               (3UL)   /*!< Capture/Compare channel 3 */

#define IS_LL_GPTMRY_CHANNEL(__VAL__)        (((__VAL__) >= LL_GPTMRY_CAP_CMP_CH_0))

#define LL_GPTMRY_CAP_CMP_CH_NUMS            (4UL)
#define LL_GPTMRY_CAP_CMP_CHN_NUMS           (0UL)
#define LL_GPTMRY_CAP_CMP_ALL_CH_NUMS        (LL_GPTMRY_CAP_CMP_CH_NUMS + LL_GPTMRY_CAP_CMP_CHN_NUMS)

#define IS_LL_GPTMRY_CAP_CMP_CH(__VAL__)     (((__VAL__) >= LL_GPTMRY_CAP_CMP_CH_0) && ((__VAL__) <= LL_GPTMRY_CAP_CMP_CH_3))
#define IS_LL_GPTMRY_CAP_CMP_CHN(__VAL__)    (0UL)

#if LL_GPTMRY_CAP_CMP_CH_NUMS > 4UL
#error "LL_GPTMRY_CAP_CMP_CH_NUMS"
#endif

#if LL_GPTMRY_CAP_CMP_CHN_NUMS > 0UL
#error "LL_GPTMRY_CAP_CMP_CHN_NUMS"
#endif
/** @} */

/** @name LL_GPTMRY_CapCmpOCTypeDef
  * @brief GPTMRY LL Compare/Capture OC Type
  * @{
  */
#define LL_GPTMRY_CapCmpOCTypeDef            uint32_t
#define LL_GPTMRY_CAP_CMP_OC                 (0UL)
#define LL_GPTMRY_CAP_CMP_OCN                (1UL)

#define IS_LL_GPTMRY_CAP_CMP_OC(__VAL__)     (((__VAL__) == LL_GPTMRY_CAP_CMP_OC) || \
                                              ((__VAL__) == LL_GPTMRY_CAP_CMP_OCN))
/** @} */

/** @name LL_GPTMRY_CapPolTypeDef
  * @brief GPTMRY LL Capture Polarity
  * @{
  */
#define LL_GPTMRY_CapPolTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRY_CAP_POL_CLOSE              (0UL)   /*!< Capture disabled       */
#define LL_GPTMRY_CAP_POL_RISING             (1UL)   /*!< Rising edge            */
#define LL_GPTMRY_CAP_POL_FALLING            (2UL)   /*!< Falling edge           */
#define LL_GPTMRY_CAP_POL_BOTH_EDGE          (3UL)   /*!< Both rising and falling */

#define IS_LL_GPTMRY_CAP_POL(__VAL__)        ((__VAL__) <= LL_GPTMRY_CAP_POL_BOTH_EDGE)

/** @} */

/** @name LL_GPTMRY_CapPrscTypeDef
  * @brief GPTMRY LL Capture Prescaler
  * @{
  */
#define LL_GPTMRY_CapPrscTypeDef             LL_RSV_DATA_TYPE

#define LL_GPTMRY_CAP_PRESCALER_1            (0UL)   /*!< Capture every edge      */
#define LL_GPTMRY_CAP_PRESCALER_2            (1UL)   /*!< Capture every 2 events  */
#define LL_GPTMRY_CAP_PRESCALER_4            (2UL)   /*!< Capture every 4 events  */
#define LL_GPTMRY_CAP_PRESCALER_8            (3UL)   /*!< Capture every 8 events  */

#define IS_LL_GPTMRY_CAP_PRESCALER(__VAL__)  (((__VAL__) == LL_GPTMRY_CAP_PRESCALER_1)  || \
                                              ((__VAL__) == LL_GPTMRY_CAP_PRESCALER_2)  || \
                                              ((__VAL__) == LL_GPTMRY_CAP_PRESCALER_4)  || \
                                              ((__VAL__) == LL_GPTMRY_CAP_PRESCALER_8))
/** @} */

/** @name LL_GPTMRY_CmpCapMapTypeDef
  * @brief GPTMRY LL Compare/Capture (Output/Input) Mapping
  * @{
  */
#define LL_GPTMRY_CmpCapMapTypeDef           LL_RSV_DATA_TYPE

#define LL_GPTMRY_CMP_CAP_MAP_OUTPUT         (0UL)   /*!< Mapped on the output */
#define LL_GPTMRY_CMP_CAP_MAP_INPUT_0        (1UL)   /*!< Mapped on the input 0 */
#define LL_GPTMRY_CMP_CAP_MAP_INPUT_1        (2UL)   /*!< Mapped on the input 1 */
#define LL_GPTMRY_CMP_CAP_MAP_INPUT_TRGI     (3UL)   /*!< Mapped on the trigger input */

#define IS_LL_GPTMRY_CMP_CAP_MAP(__VAL__)    (((__VAL__) == LL_GPTMRY_CMP_CAP_MAP_OUTPUT)   || \
                                              ((__VAL__) == LL_GPTMRY_CMP_CAP_MAP_INPUT_0)  || \
                                              ((__VAL__) == LL_GPTMRY_CMP_CAP_MAP_INPUT_1)  || \
                                              ((__VAL__) == LL_GPTMRY_CMP_CAP_MAP_INPUT_TRGI))
/** @} */

/** @name LL_GPTMRY_CmpOutputMapTypeDef
  * @brief GPTMRY LL Compare Output Mapping
  * @{
  */
#define LL_GPTMRY_CmpOutputMapTypeDef        LL_RSV_DATA_TYPE

#define LL_GPTMRY_CMP_OUTPUT_MAP_OUT         LL_GPTMRY_CMP_CAP_MAP_OUTPUT   /*!< Mapped on the output */

#define IS_LL_GPTMRY_CMP_OUTPUT_MAP(__VAL__) ((__VAL__) == LL_GPTMRY_CMP_OUTPUT_MAP_OUT)
/** @} */

/** @name LL_GPTMRY_CapInputMapTypeDef
  * @brief GPTMRY LL Capture Input Mapping
  * @{
  */
#define LL_GPTMRY_CapInputMapTypeDef         LL_RSV_DATA_TYPE

#define LL_GPTMRY_CAP_INPUT_MAP_0            LL_GPTMRY_CMP_CAP_MAP_INPUT_0    /*!< Mapped on the CH0 input */
#define LL_GPTMRY_CAP_INPUT_MAP_1            LL_GPTMRY_CMP_CAP_MAP_INPUT_1    /*!< Mapped on the CH1 input */
#define LL_GPTMRY_CAP_INPUT_MAP_TRGI         LL_GPTMRY_CMP_CAP_MAP_INPUT_TRGI   /*!< Mapped on the trigger input */

#define IS_LL_GPTMRY_CAP_INPUT_MAP(__VAL__)  (((__VAL__) == LL_GPTMRY_CAP_INPUT_MAP_0) || \
                                              ((__VAL__) == LL_GPTMRY_CAP_INPUT_MAP_1) || \
                                              ((__VAL__) == LL_GPTMRY_CAP_INPUT_MAP_TRGI))
/** @} */

/** @name LL_GPTMRY_CapInputSrcTypeDef
  * @brief GPTMRY LL Capture Trigger Input Source
  * @{
  */
#define LL_GPTMRY_CapInputSrcTypeDef         LL_RSV_DATA_TYPE

#define LL_GPTMRY_CAP_INPUT_SRC_IN0          (0UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN1          (1UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN2          (2UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN3          (3UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN4          (4UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN5          (5UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN6          (6UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN7          (7UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN8          (8UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN9          (9UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN10         (10UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN11         (11UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN12         (12UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN13         (13UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN14         (14UL)
#define LL_GPTMRY_CAP_INPUT_SRC_IN15         (15UL)

#define IS_LL_GPTMRY_CAP_INPUT_SRC(__VAL__)  (((__VAL__) >= LL_GPTMRY_CAP_INPUT_SRC_IN0) && \
                                              ((__VAL__) <= LL_GPTMRY_CAP_INPUT_SRC_IN15))

/** @} */

/** @name LL_GPTMRY_CmpPolTypeDef
  * @brief GPTMRY LL Compare Output Polarity
  * @{
  */
#define LL_GPTMRY_CmpPolTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRY_CMP_POL_HIGH               (0UL)   /*!< Compare output active high */
#define LL_GPTMRY_CMP_POL_LOW                (1UL)   /*!< Compare output active low  */

#define IS_LL_GPTMRY_CMP_POL(__VAL__)        (((__VAL__) == LL_GPTMRY_CMP_POL_HIGH) || \
                                              ((__VAL__) == LL_GPTMRY_CMP_POL_LOW))
/** @} */

/** @name LL_GPTMRY_SlvModeTypeDef
  * @brief GPTMRY LL Slave Mode
  * @{
  */
#define LL_GPTMRY_SlvModeTypeDef             LL_RSV_DATA_TYPE

#define LL_GPTMRY_SLV_MODE_DIS               (0UL)   /*!< Slave mode disabled      */
#define LL_GPTMRY_SLV_MODE_RST               (4UL)   /*!< Reset mode               */
#define LL_GPTMRY_SLV_MODE_GATING            (5UL)   /*!< Gated mode               */
#define LL_GPTMRY_SLV_MODE_TRIG              (6UL)   /*!< Trigger mode             */
#define LL_GPTMRY_SLV_MODE_EXTCLK            (7UL)   /*!< External clock mode 1    */
#define LL_GPTMRY_SLV_MODE_RST_TRIG          (8UL)   /*!< Combined reset + trigger */
#define LL_GPTMRY_SLV_MODE_RST_GATING        (9UL)   /*!< Combined reset + gated   */

#define IS_LL_GPTMRY_SLV_MODE(__VAL__)       (((__VAL__) == LL_GPTMRY_SLV_MODE_DIS)       || \
                                              ((__VAL__) == LL_GPTMRY_SLV_MODE_RST)       || \
                                              ((__VAL__) == LL_GPTMRY_SLV_MODE_GATING)    || \
                                              ((__VAL__) == LL_GPTMRY_SLV_MODE_TRIG)      || \
                                              ((__VAL__) == LL_GPTMRY_SLV_MODE_EXTCLK)    || \
                                              ((__VAL__) == LL_GPTMRY_SLV_MODE_RST_TRIG)  || \
                                              ((__VAL__) == LL_GPTMRY_SLV_MODE_RST_GATING))
/** @} */


/** @name LL_GPTMRY_EvtGenMaskTypeDef
  * @brief GPTMRY LL Timer Event Generation Mask
  * @{
  */
#define LL_GPTMRY_EvtGenMaskTypeDef                uint32_t    

#define LL_GPTMRY_EVT_GEN_UPDATE                   (TMR3_UGR_UG_Msk)         /*!< Timer Event Generation Update                    */
#define LL_GPTMRY_EVT_GEN_TRIGGER                  (TMR3_UGR_TG_Msk)         /*!< Timer Event Generation Trigger                   */
#define LL_GPTMRY_EVT_GEN_CAP_CMP_0                (TMR3_UGR_CC0UG_Msk)      /*!< Timer Event Generation Capture/Compare 0         */
#define LL_GPTMRY_EVT_GEN_CAP_CMP_1                (TMR3_UGR_CC1UG_Msk)      /*!< Timer Event Generation Capture/Compare 1         */
#define LL_GPTMRY_EVT_GEN_CAP_CMP_2                (TMR3_UGR_CC2UG_Msk)      /*!< Timer Event Generation Capture/Compare 2         */
#define LL_GPTMRY_EVT_GEN_CAP_CMP_3                (TMR3_UGR_CC3UG_Msk)      /*!< Timer Event Generation Capture/Compare 3         */

#define LL_GPTMRY_EVT_GEN_ALL_MSK                  ((TMR3_UGR_CC3UG_Msk              | TMR3_UGR_CC2UG_Msk              | \
                                                     TMR3_UGR_CC1UG_Msk              | TMR3_UGR_CC0UG_Msk              | \
                                                     TMR3_UGR_TG_Msk                 | TMR3_UGR_UG_Msk                 ))
/** @} */

/** @name LL_GPTMRY_CapFilTypeDef
  * @brief GPTMRY LL Capture Filter
  * @{
  */
#define LL_GPTMRY_CapFilTypeDef              LL_RSV_DATA_TYPE

#define LL_GPTMRY_CAP_FILTER_NONE            (0UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X1          (1UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X2          (2UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X3          (3UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X4          (4UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X5          (5UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X6          (6UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X7          (7UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X8          (8UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X9          (9UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X10         (10UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X11         (11UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X12         (12UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X13         (13UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X14         (14UL)
#define LL_GPTMRY_CAP_FILTER_TDS_X15         (15UL)

#define IS_LL_GPTMRY_CAP_FILTER(__VAL__)     (((__VAL__) >= LL_GPTMRY_CAP_FILTER_NONE) && \
                                              ((__VAL__) <= LL_GPTMRY_CAP_FILTER_TDS_X15))
/** @} */

/** @name LL_GPTMRY_OCModeTypeDef
  * @brief GPTMRY LL Compare Output Mode (CCMR.OCxM)
  * @{
  */
#define LL_GPTMRY_OCModeTypeDef                  LL_RSV_DATA_TYPE

#define LL_GPTMRY_CMP_MODE_FREEZE                (0UL)    /*!< Frozen                    */
#define LL_GPTMRY_CMP_MODE_ACTIVE                (1UL)    /*!< Force active              */
#define LL_GPTMRY_CMP_MODE_INACTIVE              (2UL)    /*!< Force inactive            */
#define LL_GPTMRY_CMP_MODE_TOGGLE                (3UL)    /*!< Toggle on match           */
#define LL_GPTMRY_CMP_MODE_FORCE_INACTIVE        (4UL)    /*!< Force inactive on match   */
#define LL_GPTMRY_CMP_MODE_FORCE_ACTIVE          (5UL)    /*!< Force active on match     */
#define LL_GPTMRY_CMP_MODE_PWM1                  (6UL)    /*!< PWM mode 1                */
#define LL_GPTMRY_CMP_MODE_PWM2                  (7UL)    /*!< PWM mode 2                */
#define LL_GPTMRY_CMP_MODE_RETRIG_OPM1           (8UL)    /*!< Retriggerable OPM mode 1  */
#define LL_GPTMRY_CMP_MODE_RETRIG_OPM2           (9UL)    /*!< Retriggerable OPM mode 2  */
#define LL_GPTMRY_CMP_MODE_COMB_PWM1             (12UL)   /*!< Combined PWM mode 1       */
#define LL_GPTMRY_CMP_MODE_COMB_PWM2             (13UL)   /*!< Combined PWM mode 2       */
#define LL_GPTMRY_CMP_MODE_ASYM_PWM1             (14UL)   /*!< Asymmetric PWM mode 1     */
#define LL_GPTMRY_CMP_MODE_ASYM_PWM2             (15UL)   /*!< Asymmetric PWM mode 2     */

#define IS_LL_GPTMRY_CMP_MODE(__VAL__)           ((((__VAL__) >= LL_GPTMRY_CMP_MODE_FREEZE) && ((__VAL__) <= LL_GPTMRY_CMP_MODE_RETRIG_OPM2)) || \
                                                  (((__VAL__) >= LL_GPTMRY_CMP_MODE_COMB_PWM1) && ((__VAL__) <= LL_GPTMRY_CMP_MODE_ASYM_PWM2)))
/** @} */


/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPTMRY_LL_Exported_Macros GPTMRY LL Exported Macros
  * @brief    GPTMRY LL Exported Macros
  * @{
  */


/**
  * @brief  GPTMRY 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define LL_GPTMRY_REG_OFFSET(__REG__, offset)            \
        (*((volatile uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))
/**
  * @}
  */ /* GPTMRY_LL_Exported_Macros */

/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup GPTMRY_LL_Exported_Functions GPTMRY LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_GPTMRY_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_GPTMRY_ASSERT_INLINE_PARAM == 1)
extern void LL_GPTMRY_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_GPTMRY_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_GPTMRY_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_GPTMRY_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup GPTMRY_LL_EF_Configuration LL GPTMRY Configuration
  * @brief    LL GPTMRY Configuration
  * @{
  */

/**
  * @brief  Enable the counter
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableCounter(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->CR0, TMR3_CR0_CEN_Msk);
}

/**
  * @brief  Disable the counter
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableCounter(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->CR0, TMR3_CR0_CEN_Msk);
}

/**
  * @brief  Judge whether the counter is enabled or not (CR0.CEN)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Counter is disabled
  * @retval 1 Counter is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledCounter(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_CEN_Msk, TMR3_CR0_CEN_Pos));
}

/**
  * @brief  Set the counter value (32 bits)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetCounter(GPTMRy_TypeDef *GPTMRy, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->CNTR, ((Val) & TMR3_CNTR_CNT_Val));
}

/**
  * @brief  Get the counter value (32 bits)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Counter value (16 bits)
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetCounter(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CNTR) & TMR3_CNTR_CNT_Val);
}

/**
  * @brief  Set the counter period (auto-reload value, 16 bits)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Period Counter period value
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetAutoReload(GPTMRy_TypeDef *GPTMRy, uint32_t Period)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->CPR, ((Period) & TMR3_CPR_CPV_Val));
}

/**
  * @brief  Get the counter period (16 bits)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Counter period (16 bits)
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetAutoReload(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CPR) & TMR3_CPR_CPV_Val);
}

/**
  * @brief  Set the prescaler division value (16 bits)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetPrescaler(GPTMRy_TypeDef *GPTMRy, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->PSCR, ((Val) & TMR3_PSCR_PSC_Val));
}

/**
  * @brief  Get the prescaler division value (16 bits)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Prescaler division value (16 bits)
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetPrescaler(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->PSCR) & TMR3_PSCR_PSC_Val);
}

/**
  * @brief  Enable the auto-preload
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableAutoReload(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->CR0, TMR3_CR0_ARE_Msk);
}

/**
  * @brief  Disable the auto-preload
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableAutoReload(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->CR0, TMR3_CR0_ARE_Msk);
}

/**
  * @brief  Judge whether the auto-preload is enabled or not
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Auto-preload is disabled
  * @retval 1 Auto-preload is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsAutoReloadEnabled(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_ARE_Msk, TMR3_CR0_ARE_Pos));
}

/**
  * @brief  Set TI0 Input Source 
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Src TI0 Input Source @ref LL_GPTMRY_TI0InSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetTI0InputSource(GPTMRy_TypeDef *GPTMRy, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG(GPTMRy->CR0, TMR3_CR0_TI0S_Msk, (((Src) & TMR3_CR0_TI0S_Val) << TMR3_CR0_TI0S_Pos));
}

/**
  * @brief  Get TI0 Input Source 
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return TI0 Input Source @ref LL_GPTMRY_TI0InSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetTI0InputSource(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_TI0S_Msk, TMR3_CR0_TI0S_Pos));
}

/**
  * @brief  Set the counter work mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRY_WorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetOnePulseMode(GPTMRy_TypeDef *GPTMRy, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_WORK_MODE(Mode));

    MODIFY_REG((GPTMRy)->CR0, TMR3_CR0_OPM_Msk, (((Mode) & TMR3_CR0_OPM_Val) << TMR3_CR0_OPM_Pos));
}

/**
  * @brief  Get the counter work mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Counter work mode @ref LL_GPTMRY_WorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetOnePulseMode(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_OPM_Msk, TMR3_CR0_OPM_Pos));
}

/**
  * @brief  Set the update event source
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Src Source to be selected @ref LL_GPTMRY_UpdateEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetUpdateSource(GPTMRy_TypeDef *GPTMRy, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_UPDATE_EVT_SRC(Src));

    MODIFY_REG((GPTMRy)->CR0, TMR3_CR0_URS_Msk, (((Src) & TMR3_CR0_URS_Val) << TMR3_CR0_URS_Pos));
}

/**
  * @brief  Get the update event source
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Update event source @ref LL_GPTMRY_UpdateEvtSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetUpdateSource(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_URS_Msk, TMR3_CR0_URS_Pos));
}

/**
  * @brief  Enable the update event (UDIS = 0)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableUpdateEvent(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->CR0, TMR3_CR0_UDIS_Msk);
}

/**
  * @brief  Disable the update event (UDIS = 1)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableUpdateEvent(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->CR0, TMR3_CR0_UDIS_Msk);
}

/**
  * @brief  Judge whether the update event is enabled or not
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Update event is disabled
  * @retval 1 Update event is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledUpdateEvent(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (!(READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_UDIS_Msk, TMR3_CR0_UDIS_Pos)));
}

/**
  * @brief  Set the counter direction
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Dir Capture/compare direction @ref LL_GPTMRY_CntDirTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetDirection(GPTMRy_TypeDef *GPTMRy, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_CNT_DIR(Dir));

    MODIFY_REG((GPTMRy)->CR0, TMR3_CR0_DIR_Msk, (((Dir) & TMR3_CR0_DIR_Val) << TMR3_CR0_DIR_Pos));
}

/**
  * @brief  Get the counter direction
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Counter direction @ref LL_GPTMRY_CntDirTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetDirection(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_DIR_Msk, TMR3_CR0_DIR_Pos));
}

/**
  * @brief  Set the counter alignment mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRY_CtrAlignModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetAlignmentMode(GPTMRy_TypeDef *GPTMRy, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_CTR_ALIGN_MODE(Mode));

    MODIFY_REG((GPTMRy)->CR0, TMR3_CR0_CMS_Msk, (((Mode) & TMR3_CR0_CMS_Val) << TMR3_CR0_CMS_Pos));
}

/**
  * @brief  Get the counter alignment mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Counter alignment mode @ref LL_GPTMRY_CtrAlignModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetAlignmentMode(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_CMS_Msk, TMR3_CR0_CMS_Pos));
}

/**
  * @brief  Set the master mode (source of the TRGO signal)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRY_MstModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetTriggerOutput(GPTMRy_TypeDef *GPTMRy, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_MST_MODE(Mode));

    MODIFY_REG((GPTMRy)->CR1, TMR3_CR1_MMS_Msk, (((Mode) & TMR3_CR1_MMS_Val) << TMR3_CR1_MMS_Pos));
}

/**
  * @brief  Get the master mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Master mode @ref LL_GPTMRY_MstModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetTriggerOutput(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR1, TMR3_CR1_MMS_Msk, TMR3_CR1_MMS_Pos));
}

/**
  * @brief  Set the ETR mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRY_ETRModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetETRMode(GPTMRy_TypeDef *GPTMRy, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_ETR_MODE(Mode));

    MODIFY_REG((GPTMRy)->SCR, TMR3_SCR_EE_Msk, (((Mode) & TMR3_SCR_EE_Val) << TMR3_SCR_EE_Pos));
}

/**
  * @brief  Get the ETR mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return ETR mode @ref LL_GPTMRY_ETRModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetETRMode(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SCR, TMR3_SCR_EE_Msk, TMR3_SCR_EE_Pos));
}

/**
  * @brief  Set the ETR edge mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRY_ETREdgeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetETREdgeMode(GPTMRy_TypeDef *GPTMRy, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_ETR_EDGE_MODE(Mode));

    MODIFY_REG((GPTMRy)->SCR, TMR3_SCR_EMS_Msk, (((Mode) & TMR3_SCR_EMS_Val) << TMR3_SCR_EMS_Pos));
}

/**
  * @brief  Get the ETR edge mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return ETR edge mode @ref LL_GPTMRY_ETREdgeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetETREdgeMode(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SCR, TMR3_SCR_EMS_Msk, TMR3_SCR_EMS_Pos));
}

/**
  * @brief  Set the ETR filter coefficient (SCR.EFS, 4 bits)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Fil Filter value @ref LL_GPTMRY_ETRFilTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetETRFilter(GPTMRy_TypeDef *GPTMRy, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->SCR, TMR3_SCR_EFS_Msk, (((Fil) & TMR3_SCR_EFS_Val) << TMR3_SCR_EFS_Pos));
}

/**
  * @brief  Get the ETR filter coefficient
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return ETR filter coefficient @ref LL_GPTMRY_ETRFilTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetETRFilter(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SCR, TMR3_SCR_EFS_Msk, TMR3_SCR_EFS_Pos));
}

/**
  * @brief  Set the trigger input source (SCR.TS, 5 bits, raw value)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Tri Trigger selection @ref LL_GPTMRY_TrigTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetTriggerInput(GPTMRy_TypeDef *GPTMRy, uint32_t Tri)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->SCR, TMR3_SCR_TS_Msk, (((Tri) & TMR3_SCR_TS_Val) << TMR3_SCR_TS_Pos));
}

/**
  * @brief  Get the trigger input source
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Trigger input source @ref LL_GPTMRY_TrigTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetTrigger(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SCR, TMR3_SCR_TS_Msk, TMR3_SCR_TS_Pos));
}

/**
  * @brief  Set the slave mode (SCR.SMS, 4 bits, raw value)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mode Mode to be set @ref LL_GPTMRY_SlvModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetSlaveMode(GPTMRy_TypeDef *GPTMRy, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->SCR, TMR3_SCR_SMS_Msk, (((Mode) & TMR3_SCR_SMS_Val) << TMR3_SCR_SMS_Pos));
}

/**
  * @brief  Get the slave mode
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Slave mode @ref LL_GPTMRY_SlvModeTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetSlaveMode(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SCR, TMR3_SCR_SMS_Msk, TMR3_SCR_SMS_Pos));
}

/**
  * @brief  Set the dead-time digital filter clock division (CR0.DCD)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Div Dead-zone / digital filter clock division @ref LL_GPTMRY_DzDigFilClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetDzDigFilClkDiv(GPTMRy_TypeDef *GPTMRy, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_DZ_DIG_FIL_CLK_DIV(Div));

    MODIFY_REG((GPTMRy)->CR0, TMR3_CR0_DCD_Msk, (((Div) & TMR3_CR0_DCD_Val) << TMR3_CR0_DCD_Pos));
}

/**
  * @brief  Get the dead-time digital filter clock division (CR0.DCD)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Clock division: @ref LL_GPTMRY_DZ_DIG_FIL_CLK_DIV_1 ... _8
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetDzDigFilClkDiv(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->CR0, TMR3_CR0_DCD_Msk, TMR3_CR0_DCD_Pos));
}

/**
  * @brief  Generate a software update event
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_GenerateEvent_UPDATE(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->UGR, TMR3_UGR_UG_Msk);
}

/**
  * @brief  Generate a trigger event
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_GenerateEvent_TRIG(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->UGR, TMR3_UGR_TG_Msk);
}

/**
  * @brief  Generate a capture/compare 0 update event
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_GenerateEvent_CC0(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->UGR, TMR3_UGR_CC0UG_Msk);
}

/**
  * @brief  Generate a capture/compare 1 update event
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_GenerateEvent_CC1(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->UGR, TMR3_UGR_CC1UG_Msk);
}

/**
  * @brief  Generate a capture/compare 2 update event
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_GenerateEvent_CC2(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->UGR, TMR3_UGR_CC2UG_Msk);
}

/**
  * @brief  Generate a capture/compare 3 update event
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_GenerateEvent_CC3(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->UGR, TMR3_UGR_CC3UG_Msk);
}

/**
  * @brief  Generate a update event
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_GenerateEvent_CCxUG(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    SET_BIT((GPTMRy)->UGR, (TMR3_UGR_CC0UG_Msk) << (((Channel) % 4UL) * 1UL));
}

/**
  * @brief  Set the input filter of a given capture channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Fil Filter value @ref LL_GPTMRY_CapFilTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_IC_SetFilter(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_OC0M_Msk << (((Channel) % 4UL) * 8UL), 
            (((Fil) & TMR3_CCMR_OC0M_Val) << (TMR3_CCMR_OC0M_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the output mode of a given compare channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Mode Mode (CCMR.OCxM) @ref LL_GPTMRY_OCModeTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_OC_SetMode(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_OC0M_Msk << (((Channel) % 4UL) * 8UL), 
            (((Mode) & TMR3_CCMR_OC0M_Val) << (TMR3_CCMR_OC0M_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the input prescaler of a given capture channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Prsc Prescaler value @ref LL_GPTMRY_CapPrscTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_IC_SetPrescaler(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Prsc)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((Prsc) & TMR3_CCMR_CC0PE_Val) << (TMR3_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Enable the output preload of a given compare channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_OC_EnablePreload(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((0x1UL) & TMR3_CCMR_CC0PE_Val) << (TMR3_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Disable the output preload of a given compare channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_OC_DisablePreload(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((0x0UL) & TMR3_CCMR_CC0PE_Val) << (TMR3_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the active input 
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Active Capture/compare direction @ref LL_GPTMRY_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_IC_SetActiveInput(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Active)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC0S_Msk << (((Channel) % 4UL) * 8UL), 
            (((Active) & TMR3_CCMR_CC0S_Val) << (TMR3_CCMR_CC0S_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Get the active input 
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return Capture/compare direction @ref LL_GPTMRY_CmpCapMapTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IC_GetActiveInput(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)(READ_BIT_SHIFT((GPTMRy)->CCMR, TMR3_CCMR_CC0S_Msk << (((Channel) % 4UL) * 8UL), 
            (TMR3_CCMR_CC0S_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the CC0 channel direction
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Dir Capture/compare direction @ref LL_GPTMRY_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetCapCmpDirCC0(GPTMRy_TypeDef *GPTMRy, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC0S_Msk, (((Dir) & TMR3_CCMR_CC0S_Val) << TMR3_CCMR_CC0S_Pos));
}

/**
  * @brief  Set the CC1 channel direction
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Dir Capture/compare direction @ref LL_GPTMRY_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetCapCmpDirCC1(GPTMRy_TypeDef *GPTMRy, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC1S_Msk, (((Dir) & TMR3_CCMR_CC1S_Val) << TMR3_CCMR_CC1S_Pos));
}

/**
  * @brief  Set the CC2 channel direction
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Dir Capture/compare direction @ref LL_GPTMRY_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetCapCmpDirCC2(GPTMRy_TypeDef *GPTMRy, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC2S_Msk, (((Dir) & TMR3_CCMR_CC2S_Val) << TMR3_CCMR_CC2S_Pos));
}

/**
  * @brief  Set the CC3 channel direction
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Dir Capture/compare direction @ref LL_GPTMRY_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetCapCmpDirCC3(GPTMRy_TypeDef *GPTMRy, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->CCMR, TMR3_CCMR_CC3S_Msk, (((Dir) & TMR3_CCMR_CC3S_Val) << TMR3_CCMR_CC3S_Pos));
}

/**
  * @brief  Set the output polarity of a given compare channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Pol Output Polarity @ref LL_GPTMRY_CmpPolTypeDef
  * @param  IsOCN @ref LL_GPTMRY_CapCmpOCTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_OC_SetPolarity(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Pol, uint32_t IsOCN)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_CAP_CMP_OC(IsOCN));

    if (!IsOCN) {
        MODIFY_REG((GPTMRy)->CCER, (0x1UL << TMR3_CCER_CC0P_Pos) << (((Channel) % 4UL) * 4UL), 
                (((Pol) & 0x1UL) << (TMR3_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)));      
    } else {
        MODIFY_REG((GPTMRy)->CCER, (0x1UL << (TMR3_CCER_CC0P_Pos + 1UL)) << (((Channel) % 4UL) * 4UL), 
                (((Pol) & 0x1UL) << (((TMR3_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)) + 1UL)));
    }
}

/**
  * @brief  Set the input polarity of a given capture channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Pol Input Polarity @ref LL_GPTMRY_CapPolTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_IC_SetPolarity(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CCER, TMR3_CCER_CC0P_Msk << (((Channel) % 4UL) * 4UL), 
            (((Pol) & 0x3UL) << (TMR3_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)));
}

/**
  * @brief  Get the input polarity of a given capture channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval Input Polarity @ref LL_GPTMRY_CapPolTypeDef
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IC_GetPolarity(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM(IS_LL_GPTMRY_CHANNEL(Channel));

    return (uint32_t)(READ_BIT_SHIFT((GPTMRy)->CCER, TMR3_CCER_CC0P_Msk << (((Channel) % 4UL) * 4UL), 
                                                    (TMR3_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)));
}

/**
  * @brief  Enable a given capture/compare channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_CC_EnableChannel(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CHANNEL(Channel)) && (Channel < 4UL));

    if (Channel <= LL_GPTMRY_CAP_CMP_CH_3) {
        MODIFY_REG((GPTMRy)->CCER, TMR3_CCER_CC0E_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x1UL) & TMR3_CCER_CC0E_Val) << (TMR3_CCER_CC0E_Pos + ((Channel) % 4UL) * 4UL)));
    }
}

/**
  * @brief  Disable a given capture/compare channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_CC_DisableChannel(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CHANNEL(Channel)) && (Channel < 4UL));

    if (Channel <= LL_GPTMRY_CAP_CMP_CH_3) {
        MODIFY_REG((GPTMRy)->CCER, TMR3_CCER_CC0E_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x0UL) & TMR3_CCER_CC0E_Val) << (TMR3_CCER_CC0E_Pos + ((Channel) % 4UL) * 4UL)));
    }
}

/**
  * @brief  Judge whether the all channel is disabled or not
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 A channel is enaabled
  * @retval 1 All channel is disabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_CC_IsAllChannelDisabled(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (uint32_t)((READ_BIT((GPTMRy)->CCER, LL_GPTMRY_CCER_CMP_CAP_CHNL_MSK) == 0UL) ? 1UL : 0UL );
}

/**
  * @brief  Disable a given capture/compare channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_CC_DisableAllChannel(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->CCER, LL_GPTMRY_CCER_CMP_CAP_CHNL_MSK );
}


/**
  * @brief  Set the CCx compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_OC_SetChannelCompare(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    WRITE_REG(LL_GPTMRY_REG_OFFSET((GPTMRy)->CC0R, (Channel % 4)), ((Val) & TMR3_CC0R_CC0V_Val));
}

/**
  * @brief  Get the CCx compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return CC0 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IC_GetChannelCompare(const GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return ((READ_REG(LL_GPTMRY_REG_OFFSET((GPTMRy)->CC0R, (Channel % 4)))) & TMR3_CC0R_CC0V_Val);
}


/**
  * @brief  Set the CC0 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_OC_SetCompareCH0(GPTMRy_TypeDef *GPTMRy, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->CC0R, ((Val) & TMR3_CC0R_CC0V_Val));
}

/**
  * @brief  Get the CC0 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC0 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_OC_GetCompareCH0(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC0R) & TMR3_CC0R_CC0V_Val);
}

/**
  * @brief  Read the CC0 capture value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC0 capture value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IC_GetCaptureCH0(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC0R) & TMR3_CC0R_CC0V_Val);
}

/**
  * @brief  Set the CC1 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_OC_SetCompareCH1(GPTMRy_TypeDef *GPTMRy, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->CC1R, ((Val) & TMR3_CC1R_CC1V_Val));
}

/**
  * @brief  Get the CC1 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC1 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_OC_GetCompareCH1(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC1R) & TMR3_CC1R_CC1V_Val);
}

/**
  * @brief  Read the CC1 capture value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC1 capture value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IC_GetCaptureCH1(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC1R) & TMR3_CC1R_CC1V_Val);
}

/**
  * @brief  Set the CC2 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_OC_SetCompareCH2(GPTMRy_TypeDef *GPTMRy, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->CC2R, ((Val) & TMR3_CC2R_CC2V_Val));
}

/**
  * @brief  Get the CC2 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC2 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_OC_GetCompareCH2(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC2R) & TMR3_CC2R_CC2V_Val);
}

/**
  * @brief  Read the CC2 capture value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC2 capture value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IC_GetCaptureCH2(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC2R) & TMR3_CC2R_CC2V_Val);
}

/**
  * @brief  Set the CC3 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_OC_SetCompareCH3(GPTMRy_TypeDef *GPTMRy, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->CC3R, ((Val) & TMR3_CC3R_CC3V_Val));
}

/**
  * @brief  Get the CC3 compare value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC3 compare value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_OC_GetCompareCH3(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC3R) & TMR3_CC3R_CC3V_Val);
}

/**
  * @brief  Read the CC3 capture value
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return CC3 capture value
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IC_GetCaptureCH3(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->CC3R) & TMR3_CC3R_CC3V_Val);
}

/**
  * @brief  Select the input source of a given capture channel.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @param  Src Input source  @ref LL_GPTMRY_CapInputSrcTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_GPTMRY_IC_SetInputSource(GPTMRy_TypeDef *GPTMRy, uint32_t Channel, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((GPTMRy)->CIR, TMR3_CIR_C0TIS_Msk << (((Channel) % 4UL) * 8UL), 
            (((Src) & TMR3_CIR_C0TIS_Val) << (TMR3_CIR_C0TIS_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the master trigger output (TRGO) pulse width
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Width Output pulse width
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetTrigOutputWidth(GPTMRy_TypeDef *GPTMRy, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->TTCR, TMR3_TTCR_TOW_Msk, (((Width) & TMR3_TTCR_TOW_Val) << TMR3_TTCR_TOW_Pos));
}

/**
  * @brief  Get the master trigger output pulse width
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Master trigger output pulse width
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetTrigOutputWidth(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->TTCR, TMR3_TTCR_TOW_Msk, TMR3_TTCR_TOW_Pos));
}

/**
  * @brief  Set the trigger cycles width (TTCR.TCW)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Width Output pulse width
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_SetTrigCyclesWidth(GPTMRy_TypeDef *GPTMRy, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    MODIFY_REG((GPTMRy)->TTCR, TMR3_TTCR_TCW_Msk, (((Width) & TMR3_TTCR_TCW_Val) << TMR3_TTCR_TCW_Pos));
}

/**
  * @brief  Get the trigger cycles width (TTCR.TCW)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Trigger cycles width (TTCR.TCW)
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetTrigCyclesWidth(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->TTCR, TMR3_TTCR_TCW_Msk, TMR3_TTCR_TCW_Pos));
}

/**
  * @brief  Enable the CH0 trigger output (TTCR.TC0E)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableTriggerCH0(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC0E_Msk);
}

/**
  * @brief  Disable the CH0 trigger output
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableTriggerCH0(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC0E_Msk);
}

/**
  * @brief  Enable the CH1 trigger output (TTCR.TC1E)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableTriggerCH1(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC1E_Msk);
}

/**
  * @brief  Disable the CH1 trigger output
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableTriggerCH1(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC1E_Msk);
}

/**
  * @brief  Enable the CH2 trigger output (TTCR.TC2E)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableTriggerCH2(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC2E_Msk);
}

/**
  * @brief  Disable the CH2 trigger output
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableTriggerCH2(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC2E_Msk);
}

/**
  * @brief  Enable the CH3 trigger output (TTCR.TC3E)
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableTriggerCH3(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC3E_Msk);
}

/**
  * @brief  Disable the CH3 trigger output
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableTriggerCH3(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC3E_Msk);
}

/**
  * @brief  Enable a channel trigger output
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableChannelTrigger(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    SET_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC0E_Msk << ((Channel % 4UL) * 1UL));
}

/**
  * @brief  Disable a channel trigger output
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableChannelTrigger(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    CLEAR_BIT((GPTMRy)->TTCR, TMR3_TTCR_TC0E_Msk << ((Channel % 4UL) * 1UL));
}


/**
  * @}
  */

/** @defgroup GPTMRY_LL_EF_IT_Management LL GPTMRY Interrupt Management
  * @brief    LL GPTMRY Interrupt Management
  * @details    Per-channel capture/compare and over-capture interrupts.
  * @{
  */

/**
  * @brief  Enable the update interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_UPDATE(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_UIE_Msk);
}

/**
  * @brief  Disable the update interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_UPDATE(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_UIE_Msk);
}

/**
  * @brief  Enable the counter overflow interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_OVIE_Msk);
}

/**
  * @brief  Disable the counter overflow interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_OVIE_Msk);
}

/**
  * @brief  Judge whether the counter overflow interrupt is enabled or not
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Counter overflow interrupt is disabled
  * @retval 1 Counter overflow interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_OVIE_Msk, TMR3_IER_OVIE_Pos));
}

/**
  * @brief  Judge whether the update event interrupt is enabled or not
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Update event interrupt is disabled
  * @retval 1 Update event interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_UPDATE(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_UIE_Msk, TMR3_IER_UIE_Pos));
}

/**
  * @brief  Enable the trigger interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_TRIG(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_TIE_Msk);
}

/**
  * @brief  Disable the trigger interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_TRIG(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_TIE_Msk);
}

/**
  * @brief  Judge whether the trigger interrupt is enabled or not
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Trigger interrupt is disabled
  * @retval 1 Trigger interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_TRIG(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_TIE_Msk, TMR3_IER_TIE_Pos));
}

/**
  * @brief  Get the whole interrupt enable register
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Whole interrupt enable register
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetAllIntEn(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->IER));
}

/**
  * @brief  Judge whether the counter overflow flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Counter overflow flag is cleared
  * @retval 1 Counter overflow flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_OVIF_Msk, TMR3_SR_OVIF_Pos));
}

/**
  * @brief  Clear the counter overflow flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_OVIF_Msk);
}

/**
  * @brief  Judge whether the update event flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Update event flag is cleared
  * @retval 1 Update event flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_UPDATE(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_UIF_Msk, TMR3_SR_UIF_Pos));
}

/**
  * @brief  Clear the update event flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_UPDATE(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_UIF_Msk);
}

/**
  * @brief  Judge whether the trigger flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 Trigger flag is cleared
  * @retval 1 Trigger flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_TRIG(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_TIF_Msk, TMR3_SR_TIF_Pos));
}

/**
  * @brief  Clear the trigger flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_TRIG(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_TIF_Msk);
}

/**
  * @brief  Get the whole status register
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Whole status register
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetAllFlag(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_REG((GPTMRy)->SR));
}

/**
  * @brief  Enable the CCx capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CxMIE(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C0MIE_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Disable the CCx capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CxMIE(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C0MIE_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Judge whether the CCx capture/compare interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval 0 CCx capture/compare interrupt is disabled
  * @retval 1 CCx capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CxMIE(const GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)((READ_BIT((GPTMRy)->IER, TMR3_IER_C0MIE_Msk << ((Channel % 4UL) * 2UL))) ? 1UL : 0UL);
}

/**
  * @brief  Judge whether the CCx over-capture interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval 0 CCx over-capture interrupt is disabled
  * @retval 1 CCx over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CxOIE(const GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)((READ_BIT((GPTMRy)->IER, TMR3_IER_C0OIE_Msk << ((Channel % 4UL) * 2UL))) ? 1UL : 0UL);
}

/**
  * @brief  Enable the CC0 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC0(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C0MIE_Msk);
}

/**
  * @brief  Disable the CC0 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC0(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C0MIE_Msk);
}

/**
  * @brief  Judge whether the CC0 capture/compare interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC0 capture/compare interrupt is disabled
  * @retval 1 CC0 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC0(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C0MIE_Msk, TMR3_IER_C0MIE_Pos));
}

/**
  * @brief  Enable the CC0 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC0OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C0OIE_Msk);
}

/**
  * @brief  Disable the CC0 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC0OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C0OIE_Msk);
}

/**
  * @brief  Judge whether the CC0 over-capture interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC0 over-capture interrupt is disabled
  * @retval 1 CC0 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC0OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C0OIE_Msk, TMR3_IER_C0OIE_Pos));
}

/**
  * @brief  Enable the CC1 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC1(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C1MIE_Msk);
}

/**
  * @brief  Disable the CC1 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC1(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C1MIE_Msk);
}

/**
  * @brief  Judge whether the CC1 capture/compare interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC1 capture/compare interrupt is disabled
  * @retval 1 CC1 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC1(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C1MIE_Msk, TMR3_IER_C1MIE_Pos));
}

/**
  * @brief  Enable the CC1 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC1OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C1OIE_Msk);
}

/**
  * @brief  Disable the CC1 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC1OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C1OIE_Msk);
}

/**
  * @brief  Judge whether the CC1 over-capture interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC1 over-capture interrupt is disabled
  * @retval 1 CC1 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC1OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C1OIE_Msk, TMR3_IER_C1OIE_Pos));
}

/**
  * @brief  Enable the CC2 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC2(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C2MIE_Msk);
}

/**
  * @brief  Disable the CC2 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC2(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C2MIE_Msk);
}

/**
  * @brief  Judge whether the CC2 capture/compare interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC2 capture/compare interrupt is disabled
  * @retval 1 CC2 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC2(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C2MIE_Msk, TMR3_IER_C2MIE_Pos));
}

/**
  * @brief  Enable the CC2 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC2OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C2OIE_Msk);
}

/**
  * @brief  Disable the CC2 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC2OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C2OIE_Msk);
}

/**
  * @brief  Judge whether the CC2 over-capture interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC2 over-capture interrupt is disabled
  * @retval 1 CC2 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC2OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C2OIE_Msk, TMR3_IER_C2OIE_Pos));
}

/**
  * @brief  Enable the CC3 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC3(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C3MIE_Msk);
}

/**
  * @brief  Disable the CC3 capture/compare interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC3(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C3MIE_Msk);
}

/**
  * @brief  Judge whether the CC3 capture/compare interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC3 capture/compare interrupt is disabled
  * @retval 1 CC3 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC3(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C3MIE_Msk, TMR3_IER_C3MIE_Pos));
}

/**
  * @brief  Enable the CC3 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT_CC3OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT((GPTMRy)->IER, TMR3_IER_C3OIE_Msk);
}

/**
  * @brief  Disable the CC3 over-capture interrupt
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT_CC3OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT((GPTMRy)->IER, TMR3_IER_C3OIE_Msk);
}

/**
  * @brief  Judge whether the CC3 over-capture interrupt is enabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC3 over-capture interrupt is disabled
  * @retval 1 CC3 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT_CC3OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->IER, TMR3_IER_C3OIE_Msk, TMR3_IER_C3OIE_Pos));
}

/**
  * @brief  Judge whether the CCx capture/compare flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CCx capture/compare flag is cleared
  * @retval 1 CCx capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CCxMIF(const GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)((READ_BIT((GPTMRy)->SR, (TMR3_SR_CC0MIF_Msk << ((Channel % 4UL) * 2UL)))) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CCx capture/compare flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CCxMIF(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC0MIF_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Judge whether the CCx over-capture flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @retval 0 CCx over-capture flag is cleared
  * @retval 1 CCx over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CCxOIF(const GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (uint32_t)((READ_BIT((GPTMRy)->SR, (TMR3_SR_CC0OIF_Msk << ((Channel % 4UL) * 2UL)))) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CCx over-capture flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Channel Capture/compare channel @ref LL_GPTMRY_CapCmpChTypeDef (LL_GPTMRY_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CCxOIF(GPTMRy_TypeDef *GPTMRy, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_INLINE_PARAM((IS_LL_GPTMRY_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC0OIF_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Judge whether the CC0 capture/compare flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC0 capture/compare flag is cleared
  * @retval 1 CC0 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC0(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC0MIF_Msk, TMR3_SR_CC0MIF_Pos));
}

/**
  * @brief  Clear the CC0 capture/compare flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC0(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC0MIF_Msk);
}

/**
  * @brief  Judge whether the CC0 over-capture flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC0 over-capture flag is cleared
  * @retval 1 CC0 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC0OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC0OIF_Msk, TMR3_SR_CC0OIF_Pos));
}

/**
  * @brief  Clear the CC0 over-capture flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC0OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC0OIF_Msk);
}

/**
  * @brief  Judge whether the CC1 capture/compare flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC1 capture/compare flag is cleared
  * @retval 1 CC1 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC1(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC1MIF_Msk, TMR3_SR_CC1MIF_Pos));
}

/**
  * @brief  Clear the CC1 capture/compare flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC1(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC1MIF_Msk);
}

/**
  * @brief  Judge whether the CC1 over-capture flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC1 over-capture flag is cleared
  * @retval 1 CC1 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC1OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC1OIF_Msk, TMR3_SR_CC1OIF_Pos));
}

/**
  * @brief  Clear the CC1 over-capture flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC1OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC1OIF_Msk);
}

/**
  * @brief  Judge whether the CC2 capture/compare flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC2 capture/compare flag is cleared
  * @retval 1 CC2 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC2(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC2MIF_Msk, TMR3_SR_CC2MIF_Pos));
}

/**
  * @brief  Clear the CC2 capture/compare flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC2(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC2MIF_Msk);
}

/**
  * @brief  Judge whether the CC2 over-capture flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC2 over-capture flag is cleared
  * @retval 1 CC2 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC2OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC2OIF_Msk, TMR3_SR_CC2OIF_Pos));
}

/**
  * @brief  Clear the CC2 over-capture flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC2OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC2OIF_Msk);
}

/**
  * @brief  Judge whether the CC3 capture/compare flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC3 capture/compare flag is cleared
  * @retval 1 CC3 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC3(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC3MIF_Msk, TMR3_SR_CC3MIF_Pos));
}

/**
  * @brief  Clear the CC3 capture/compare flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC3(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC3MIF_Msk);
}

/**
  * @brief  Judge whether the CC3 over-capture flag is set
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval 0 CC3 over-capture flag is cleared
  * @retval 1 CC3 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag_CC3OVR(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT_SHIFT((GPTMRy)->SR, TMR3_SR_CC3OIF_Msk, TMR3_SR_CC3OIF_Pos));
}

/**
  * @brief  Clear the CC3 over-capture flag
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag_CC3OVR(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG((GPTMRy)->SR, TMR3_SR_CC3OIF_Msk);
}

/**
  * @brief  GPTMRY Interrupt enable
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mask Mask to enable @ref LL_GPTMRY_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_EnableIT(GPTMRy_TypeDef *GPTMRy, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    SET_BIT(GPTMRy->IER, Mask);
}

/**
  * @brief  GPTMRY Interrupt disable
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mask Mask to disable @ref LL_GPTMRY_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_DisableIT(GPTMRy_TypeDef *GPTMRy, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    CLEAR_BIT(GPTMRy->IER, Mask);
}

/**
  * @brief  Check if GPTMRY Interrupt is enabled or disabled
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mask Mask to check @ref LL_GPTMRY_IER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsEnabledIT(const GPTMRy_TypeDef *GPTMRy, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(GPTMRy->IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mask Mask to clear @ref LL_GPTMRY_SR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_GPTMRY_ClearFlag(GPTMRy_TypeDef *GPTMRy, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    WRITE_REG(GPTMRy->SR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @param  Mask Mask to check @ref LL_GPTMRY_SR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPTMRY_IsActiveFlag(const GPTMRy_TypeDef *GPTMRy, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(GPTMRy->SR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  GPTMRY Interrupt All Enable Get
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Interrupt Enable Bit
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetAllEnabledIT(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT(GPTMRy->IER, LL_GPTMRY_IER_IT_EN_MSK));
}

/**
  * @brief  Get interrupt status of the specified GPTMRY channel 
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @return Interrupt status
  */
__STATIC_INLINE uint32_t LL_GPTMRY_GetAllITPending(const GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_INLINE_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    return (READ_BIT(GPTMRy->SR, LL_GPTMRY_SR_IT_FLAG_MSK));
}


/**
  * @}
  */ /* GPTMRY_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* GPTMRY_LL_Exported_Functions */

#endif /* GPTMRY */

/**
  * @}
  */ /* GPTMRY_LL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_GPTMRY_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/









