/**
  ******************************************************************************
  * @file    tae32g58xx_ll_adtmr.h
  * @author  Tai-Action SD Team
  * @brief   Header file for ADTMR (Advanced Timer) LL module
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
#ifndef _TAE32G58XX_LL_ADTMR_H_
#define _TAE32G58XX_LL_ADTMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if (defined(TMR9) || defined(TMR10))

/** @defgroup ADTMR_LL ADTMR LL
  * @brief    ADTMR LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup ADTMR_LL_Exported_Constants ADTMR LL Exported Constants
  * @brief    ADTMR LL Exported Constants
  * @{
  */

/** @name LL_ADTMR_IER_ITEnMskTypeDef
  * @brief ADTMR LL Interrupt Enable Masks
  * @{
  */
#define LL_ADTMR_IER_ITEnMskTypeDef     uint32_t

#define LL_ADTMR_IER_BIE                (TMR9_IER_BIE_Msk)      /*!< Break interrupt enable          */
#define LL_ADTMR_IER_TIE                (TMR9_IER_TIE_Msk)      /*!< Trigger interrupt enable        */
#define LL_ADTMR_IER_OVIE               (TMR9_IER_OVIE_Msk)     /*!< Overflow interrupt enable       */
#define LL_ADTMR_IER_UIE                (TMR9_IER_UIE_Msk)      /*!< Update interrupt enable         */
#define LL_ADTMR_IER_C3OIE              (TMR9_IER_C3OIE_Msk)    /*!< CH3 output compare interrupt enable */
#define LL_ADTMR_IER_C3MIE              (TMR9_IER_C3MIE_Msk)    /*!< CH3 input capture interrupt enable  */
#define LL_ADTMR_IER_C2OIE              (TMR9_IER_C2OIE_Msk)    /*!< CH2 output compare interrupt enable */
#define LL_ADTMR_IER_C2MIE              (TMR9_IER_C2MIE_Msk)    /*!< CH2 input capture interrupt enable  */
#define LL_ADTMR_IER_C1OIE              (TMR9_IER_C1OIE_Msk)    /*!< CH1 output compare interrupt enable */
#define LL_ADTMR_IER_C1MIE              (TMR9_IER_C1MIE_Msk)    /*!< CH1 input capture interrupt enable  */
#define LL_ADTMR_IER_C0OIE              (TMR9_IER_C0OIE_Msk)    /*!< CH0 output compare interrupt enable */
#define LL_ADTMR_IER_C0MIE              (TMR9_IER_C0MIE_Msk)    /*!< CH0 input capture interrupt enable  */

#define LL_ADTMR_IER_IT_EN_MSK          ((TMR9_IER_BIE_Msk                | TMR9_IER_TIE_Msk                | \
                                          TMR9_IER_OVIE_Msk               | TMR9_IER_UIE_Msk                | \
                                          TMR9_IER_C3OIE_Msk              | TMR9_IER_C3MIE_Msk              | \
                                          TMR9_IER_C2OIE_Msk              | TMR9_IER_C2MIE_Msk              | \
                                          TMR9_IER_C1OIE_Msk              | TMR9_IER_C1MIE_Msk              | \
                                          TMR9_IER_C0OIE_Msk              | TMR9_IER_C0MIE_Msk              ))

#define LL_ADTMR_IER_CC_IT_EN_MSK       ((TMR9_IER_C3OIE_Msk              | TMR9_IER_C3MIE_Msk              | \
                                          TMR9_IER_C2OIE_Msk              | TMR9_IER_C2MIE_Msk              | \
                                          TMR9_IER_C1OIE_Msk              | TMR9_IER_C1MIE_Msk              | \
                                          TMR9_IER_C0OIE_Msk              | TMR9_IER_C0MIE_Msk              ))
/**
  * @}
  */

/** @name LL_ADTMR_SR_ITPendingMskTypeDef
  * @brief ADTMR LL Status Flag Masks
  * @{
  */
#define LL_ADTMR_SR_ITPendingMskTypeDef uint32_t

#define LL_ADTMR_SR_B1IF                (TMR9_SR_B1IF_Msk)      /*!< Break input 1 flag              */
#define LL_ADTMR_SR_SBIF                (TMR9_SR_SBIF_Msk)      /*!< System break flag               */
#define LL_ADTMR_SR_B0IF                (TMR9_SR_B0IF_Msk)      /*!< Break input 0 flag              */
#define LL_ADTMR_SR_TIF                 (TMR9_SR_TIF_Msk)       /*!< Trigger flag                    */
#define LL_ADTMR_SR_OVIF                (TMR9_SR_OVIF_Msk)      /*!< Overflow flag                   */
#define LL_ADTMR_SR_UIF                 (TMR9_SR_UIF_Msk)       /*!< Update flag                     */
#define LL_ADTMR_SR_CC3OIF              (TMR9_SR_CC3OIF_Msk)    /*!< CH3 output compare flag         */
#define LL_ADTMR_SR_CC3MIF              (TMR9_SR_CC3MIF_Msk)    /*!< CH3 input capture flag          */
#define LL_ADTMR_SR_CC2OIF              (TMR9_SR_CC2OIF_Msk)    /*!< CH2 output compare flag         */
#define LL_ADTMR_SR_CC2MIF              (TMR9_SR_CC2MIF_Msk)    /*!< CH2 input capture flag          */
#define LL_ADTMR_SR_CC1OIF              (TMR9_SR_CC1OIF_Msk)    /*!< CH1 output compare flag         */
#define LL_ADTMR_SR_CC1MIF              (TMR9_SR_CC1MIF_Msk)    /*!< CH1 input capture flag          */
#define LL_ADTMR_SR_CC0OIF              (TMR9_SR_CC0OIF_Msk)    /*!< CH0 output compare flag         */
#define LL_ADTMR_SR_CC0MIF              (TMR9_SR_CC0MIF_Msk)    /*!< CH0 input capture flag          */

#define LL_ADTMR_SR_IT_FLAG_MSK         ((TMR9_SR_B1IF_Msk                | TMR9_SR_SBIF_Msk                | \
                                          TMR9_SR_B0IF_Msk                | TMR9_SR_TIF_Msk                 | \
                                          TMR9_SR_OVIF_Msk                | TMR9_SR_UIF_Msk                 | \
                                          TMR9_SR_CC3OIF_Msk              | TMR9_SR_CC3MIF_Msk              | \
                                          TMR9_SR_CC2OIF_Msk              | TMR9_SR_CC2MIF_Msk              | \
                                          TMR9_SR_CC1OIF_Msk              | TMR9_SR_CC1MIF_Msk              | \
                                          TMR9_SR_CC0OIF_Msk              | TMR9_SR_CC0MIF_Msk              ))

#define LL_ADTMR_SR_CC_IT_FLAG_MSK      ((TMR9_SR_CC3OIF_Msk              | TMR9_SR_CC3MIF_Msk              | \
                                          TMR9_SR_CC2OIF_Msk              | TMR9_SR_CC2MIF_Msk              | \
                                          TMR9_SR_CC1OIF_Msk              | TMR9_SR_CC1MIF_Msk              | \
                                          TMR9_SR_CC0OIF_Msk              | TMR9_SR_CC0MIF_Msk              ))

#define LL_ADTMR_SR_BRK_IT_FLAG_MSK     ((TMR9_SR_B1IF_Msk                 | TMR9_SR_SBIF_Msk                | \
                                          TMR9_SR_B0IF_Msk))

#define LL_ADTMR_SR_UPD_IT_FLAG_MSK     ((TMR9_SR_OVIF_Msk                 | TMR9_SR_UIF_Msk                ))
/** @} */

#define LL_ADTMR_CCER_CMP_CAP_CHNL_MSK  ((TMR9_CCER_CC3NE_Msk             | TMR9_CCER_CC3E_Msk              | \
                                          TMR9_CCER_CC2NE_Msk             | TMR9_CCER_CC2E_Msk              | \
                                          TMR9_CCER_CC1NE_Msk             | TMR9_CCER_CC1E_Msk              | \
                                          TMR9_CCER_CC0NE_Msk             | TMR9_CCER_CC0E_Msk              ))

/** @name LL_ADTMR_TTCR_TrigOutChMskTypeDef
  * @brief ADTMR LL TTCR TRGO Channel Selection
  * @{
  */
#define LL_ADTMR_TTCR_TrigOutChMskTypeDef          uint32_t

#define LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH3          (TMR9_TTCR_TC3E_Msk)
#define LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH2          (TMR9_TTCR_TC2E_Msk)
#define LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH1          (TMR9_TTCR_TC1E_Msk)
#define LL_ADTMR_TTCR_TRGI_OUT_SELECT_CH0          (TMR9_TTCR_TC0E_Msk)
/** @} */

/** @name LL_ADTMR_BrkInputMskTypeDef
  * @brief ADTMR LL Break Input Channel Mask
  * @{
  */
#define LL_ADTMR_BrkInputMskTypeDef       uint16_t
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK0     ((uint16_t)(BIT(0)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK1     ((uint16_t)(BIT(1)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK2     ((uint16_t)(BIT(2)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK3     ((uint16_t)(BIT(3)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK4     ((uint16_t)(BIT(4)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK5     ((uint16_t)(BIT(5)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK6     ((uint16_t)(BIT(6)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK7     ((uint16_t)(BIT(7)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK8     ((uint16_t)(BIT(8)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK9     ((uint16_t)(BIT(9)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK10    ((uint16_t)(BIT(10)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK11    ((uint16_t)(BIT(11)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK12    ((uint16_t)(BIT(12)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK13    ((uint16_t)(BIT(13)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK14    ((uint16_t)(BIT(14)))
#define LL_ADTMR_BRK_IN_SIGNAL_BREAK15    ((uint16_t)(BIT(15)))
/** @} */

/** @name LL_ADTMR_BrkInputSrcMskTypeDef
  * @brief ADTMR LL Break Input Source Mask
  * @{
  */
#define LL_ADTMR_BrkInputSrcMskTypeDef        uint16_t
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP0_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK0)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP1_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK1)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP2_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK2)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP3_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK3)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP4_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK4)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP5_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK5)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP6_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK6)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP7_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK7)
#define LL_ADTMR_BRK_IN_SRC_MASK_CMP8_OUT     (LL_ADTMR_BRK_IN_SIGNAL_BREAK8)
#define LL_ADTMR_BRK_IN_SRC_MASK_TMRx_BKy     (LL_ADTMR_BRK_IN_SIGNAL_BREAK9)
#define LL_ADTMR_BRK_IN_SRC_MASK_ADC0_AWD0    (LL_ADTMR_BRK_IN_SIGNAL_BREAK10)
#define LL_ADTMR_BRK_IN_SRC_MASK_ADC1_AWD0    (LL_ADTMR_BRK_IN_SIGNAL_BREAK11)
#define LL_ADTMR_BRK_IN_SRC_MASK_PDM0_CMPH    (LL_ADTMR_BRK_IN_SIGNAL_BREAK12)
#define LL_ADTMR_BRK_IN_SRC_MASK_PDM1_CMPH    (LL_ADTMR_BRK_IN_SIGNAL_BREAK13)
#define LL_ADTMR_BRK_IN_SRC_MASK_PDM2_CMPH    (LL_ADTMR_BRK_IN_SIGNAL_BREAK14)
#define LL_ADTMR_BRK_IN_SRC_MASK_PDM3_CMPH    (LL_ADTMR_BRK_IN_SIGNAL_BREAK15)
/** @} */

/** @name LL_ADTMR_TI0InSrcTypeDef
  * @brief ADTMR LL TI0 Input Source
  * @{
  */
#define LL_ADTMR_TI0InSrcTypeDef        LL_RSV_DATA_TYPE

#define LL_ADTMR_TI0_IN_SRC_CH0         (0UL)   
#define LL_ADTMR_TI0_IN_SRC_CH0_1_2_XOR (1UL)   

#define IS_LL_ADTMR_TI0_IN_SRC(__VAL__)             (((__VAL__) == LL_ADTMR_TI0_IN_SRC_CH0) || \
                                                     ((__VAL__) == LL_ADTMR_TI0_IN_SRC_CH0_1_2_XOR))
/** @} */

/** @name LL_ADTMR_WorkModeTypeDef
  * @brief ADTMR LL Work Mode (CR0.OPM)
  * @{
  */
#define LL_ADTMR_WorkModeTypeDef        LL_RSV_DATA_TYPE

#define LL_ADTMR_WORK_MODE_CONTINUE     (0UL)   /*!< Continue mode */
#define LL_ADTMR_WORK_MODE_SINGLE       (1UL)   /*!< Single mode   */

#define IS_LL_ADTMR_WORK_MODE(__VAL__)              (((__VAL__) == LL_ADTMR_WORK_MODE_CONTINUE) || \
                                                     ((__VAL__) == LL_ADTMR_WORK_MODE_SINGLE))
/** @} */

/** @name LL_ADTMR_UpdateEvtSrcTypeDef
  * @brief ADTMR LL Update Event Source (CR0.URS)
  * @{
  */
#define LL_ADTMR_UpdateEvtSrcTypeDef    LL_RSV_DATA_TYPE

#define LL_ADTMR_UPDATE_EVT_SRC_OV_UG   (0UL)   /*!< Overflow and software (UG) */
#define LL_ADTMR_UPDATE_EVT_SRC_OV      (1UL)   /*!< Only overflow              */

#define IS_LL_ADTMR_UPDATE_EVT_SRC(__VAL__)         (((__VAL__) == LL_ADTMR_UPDATE_EVT_SRC_OV_UG) || \
                                                     ((__VAL__) == LL_ADTMR_UPDATE_EVT_SRC_OV))
/** @} */

/** @name LL_ADTMR_CntDirTypeDef
  * @brief ADTMR LL Counter Direction (CR0.DIR)
  * @{
  */
#define LL_ADTMR_CntDirTypeDef          LL_RSV_DATA_TYPE

#define LL_ADTMR_CNT_DIR_INC            (0UL)   /*!< Up counting   */
#define LL_ADTMR_CNT_DIR_DEC            (1UL)   /*!< Down counting */

#define IS_LL_ADTMR_CNT_DIR(__VAL__)                (((__VAL__) == LL_ADTMR_CNT_DIR_INC) || \
                                                     ((__VAL__) == LL_ADTMR_CNT_DIR_DEC))

/** @} */

/** @name LL_ADTMR_CtrAlignModeTypeDef
  * @brief ADTMR LL Counter Align Mode (CR0.CMS)
  * @{
  */
#define LL_ADTMR_CtrAlignModeTypeDef            LL_RSV_DATA_TYPE

#define LL_ADTMR_CTR_ALIGN_MODE_EDGE            (0UL)   /*!< Edge-aligned          */
#define LL_ADTMR_CTR_ALIGN_MODE_CENTER_1        (1UL)   /*!< Center-aligned mode 1 */
#define LL_ADTMR_CTR_ALIGN_MODE_CENTER_2        (2UL)   /*!< Center-aligned mode 2 */
#define LL_ADTMR_CTR_ALIGN_MODE_CENTER_3        (3UL)   /*!< Center-aligned mode 3 */

#define IS_LL_ADTMR_CTR_ALIGN_MODE(__VAL__)         (((__VAL__) == LL_ADTMR_CTR_ALIGN_MODE_EDGE) || \
                                                     ((__VAL__) == LL_ADTMR_CTR_ALIGN_MODE_CENTER_1) || \
                                                     ((__VAL__) == LL_ADTMR_CTR_ALIGN_MODE_CENTER_2) || \
                                                     ((__VAL__) == LL_ADTMR_CTR_ALIGN_MODE_CENTER_3))
/** @} */

/** @name LL_ADTMR_OutputIdleStaTypeDef
  * @brief ADTMR LL Output Idle State
  * @{
  */
#define LL_ADTMR_OutputIdleStaTypeDef               LL_RSV_DATA_TYPE    

#define LL_ADTMR_OUTPUT_IDLE_STA_LOW                (0UL)                /*!< Output Idle State Low                            */
#define LL_ADTMR_OUTPUT_IDLE_STA_HIGH               (1UL)                /*!< Output Idle State High                           */

#define IS_LL_ADTMR_OUTPUT_IDLE_STA(__VAL__)        (((__VAL__) == LL_ADTMR_OUTPUT_IDLE_STA_LOW)  || \
                                                     ((__VAL__) == LL_ADTMR_OUTPUT_IDLE_STA_HIGH) )
/** @} */



/** @name LL_ADTMR_MstModeTypeDef
  * @brief ADTMR LL Master Mode (CR1.MMS)
  * @{
  */
#define LL_ADTMR_MstModeTypeDef         LL_RSV_DATA_TYPE

#define LL_ADTMR_MST_MODE_RESET         (0UL)   /*!< TRGO = counter reset (UG)    */
#define LL_ADTMR_MST_MODE_ENABLE        (1UL)   /*!< TRGO = counter enable        */
#define LL_ADTMR_MST_MODE_UPDATE        (2UL)   /*!< TRGO = update event          */
#define LL_ADTMR_MST_MODE_CAP_CMP_EVT   (3UL)   /*!< TRGO = capture/compare event */
#define LL_ADTMR_MST_MODE_OC0REF        (4UL)   /*!< TRGO = OC0REF                */
#define LL_ADTMR_MST_MODE_OC1REF        (5UL)   /*!< TRGO = OC1REF                */
#define LL_ADTMR_MST_MODE_OC2REF        (6UL)   /*!< TRGO = OC2REF                */
#define LL_ADTMR_MST_MODE_OC3REF        (7UL)   /*!< TRGO = OC3REF                */

#define IS_LL_ADTMR_MST_MODE(__VAL__)               (((__VAL__) == LL_ADTMR_MST_MODE_RESET)       || \
                                                     ((__VAL__) == LL_ADTMR_MST_MODE_ENABLE)      || \
                                                     ((__VAL__) == LL_ADTMR_MST_MODE_UPDATE)      || \
                                                     ((__VAL__) == LL_ADTMR_MST_MODE_CAP_CMP_EVT) || \
                                                     ((__VAL__) == LL_ADTMR_MST_MODE_OC0REF)      || \
                                                     ((__VAL__) == LL_ADTMR_MST_MODE_OC1REF)      || \
                                                     ((__VAL__) == LL_ADTMR_MST_MODE_OC2REF)      || \
                                                     ((__VAL__) == LL_ADTMR_MST_MODE_OC3REF))

/** @} */

/** @name LL_ADTMR_ETRModeTypeDef
  * @brief ADTMR LL ETR Mode (SCR.EE)
  * @{
  */
#define LL_ADTMR_ETRModeTypeDef         LL_RSV_DATA_TYPE

#define LL_ADTMR_ETR_MODE_EXT_CLK_1     (0UL)   /*!< External clock mode 1 */
#define LL_ADTMR_ETR_MODE_EXT_CLK_2     (1UL)   /*!< External clock mode 2 */

#define IS_LL_ADTMR_ETR_MODE(__VAL__)               (((__VAL__) == LL_ADTMR_ETR_MODE_EXT_CLK_1) || \
                                                     ((__VAL__) == LL_ADTMR_ETR_MODE_EXT_CLK_2))
/** @} */

/** @name LL_ADTMR_ETRFilTypeDef
  * @brief ADTMR LL ETR Filter
  * @{
  */
#define LL_ADTMR_ETRFilTypeDef              LL_RSV_DATA_TYPE

#define LL_ADTMR_ETR_FILTER_NONE            (0UL)
#define LL_ADTMR_ETR_FILTER_TDS_X1          (1UL)
#define LL_ADTMR_ETR_FILTER_TDS_X2          (2UL)
#define LL_ADTMR_ETR_FILTER_TDS_X3          (3UL)
#define LL_ADTMR_ETR_FILTER_TDS_X4          (4UL)
#define LL_ADTMR_ETR_FILTER_TDS_X5          (5UL)
#define LL_ADTMR_ETR_FILTER_TDS_X6          (6UL)
#define LL_ADTMR_ETR_FILTER_TDS_X7          (7UL)
#define LL_ADTMR_ETR_FILTER_TDS_X8          (8UL)
#define LL_ADTMR_ETR_FILTER_TDS_X9          (9UL)
#define LL_ADTMR_ETR_FILTER_TDS_X10         (10UL)
#define LL_ADTMR_ETR_FILTER_TDS_X11         (11UL)
#define LL_ADTMR_ETR_FILTER_TDS_X12         (12UL)
#define LL_ADTMR_ETR_FILTER_TDS_X13         (13UL)
#define LL_ADTMR_ETR_FILTER_TDS_X14         (14UL)
#define LL_ADTMR_ETR_FILTER_TDS_X15         (15UL)

#define IS_LL_ADTMR_ETR_FILTER(__VAL__)     (((__VAL__) >= LL_ADTMR_ETR_FILTER_NONE) && \
                                             ((__VAL__) <= LL_ADTMR_ETR_FILTER_TDS_X15))
/** @} */


/** @name LL_ADTMR_ETREdgeTypeDef
  * @brief ADTMR LL ETR Edge Mode (SCR.EMS)
  * @{
  */
#define LL_ADTMR_ETREdgeTypeDef                 LL_RSV_DATA_TYPE


#define LL_ADTMR_ETR_EDGE_MODE_CLOSE            (0UL)   /*!< Trigger closed                */
#define LL_ADTMR_ETR_EDGE_MODE_RISING           (1UL)   /*!< Rising edge                   */
#define LL_ADTMR_ETR_EDGE_MODE_FALLING          (2UL)   /*!< Falling edge                  */
#define LL_ADTMR_ETR_EDGE_MODE_RISING_FALLING   (3UL)   /*!< Both rising and falling edges */

#define IS_LL_ADTMR_ETR_EDGE_MODE(__VAL__)          (((__VAL__) == LL_ADTMR_ETR_EDGE_MODE_CLOSE) || \
                                                     ((__VAL__) == LL_ADTMR_ETR_EDGE_MODE_RISING) || \
                                                     ((__VAL__) == LL_ADTMR_ETR_EDGE_MODE_FALLING) || \
                                                     ((__VAL__) == LL_ADTMR_ETR_EDGE_MODE_RISING_FALLING))
/** @} */

/** @name LL_ADTMR_TrigTypeDef
  * @brief ADTMR LL Trigger Selection (SCR.TS)
  * @{
  */
#define LL_ADTMR_TrigTypeDef            LL_RSV_DATA_TYPE

/* Generic internal trigger sources */
#define LL_ADTMR_TRIG_ITR0              (0UL)   /*!< Internal trigger ITR0  */
#define LL_ADTMR_TRIG_ITR1              (1UL)   /*!< Internal trigger ITR1  */
#define LL_ADTMR_TRIG_ITR2              (2UL)   /*!< Internal trigger ITR2  */
#define LL_ADTMR_TRIG_ITR3              (3UL)   /*!< Internal trigger ITR3  */
#define LL_ADTMR_TRIG_ITR4              (4UL)   /*!< Internal trigger ITR4  */
#define LL_ADTMR_TRIG_ITR5              (5UL)   /*!< Internal trigger ITR5  */
#define LL_ADTMR_TRIG_ITR6              (6UL)   /*!< Internal trigger ITR6  */
#define LL_ADTMR_TRIG_ITR7              (7UL)   /*!< Internal trigger ITR7  */
#define LL_ADTMR_TRIG_ITR8              (8UL)   /*!< Internal trigger ITR8  */
#define LL_ADTMR_TRIG_ITR9              (9UL)   /*!< Internal trigger ITR9  */
#define LL_ADTMR_TRIG_ITR10             (10UL)  /*!< Internal trigger ITR10 */
#define LL_ADTMR_TRIG_ITR11             (11UL)  /*!< Internal trigger ITR11 */
#define LL_ADTMR_TRIG_ITR12             (12UL)  /*!< Internal trigger ITR12 */
#define LL_ADTMR_TRIG_ITR13             (13UL)  /*!< Internal trigger ITR13 */
#define LL_ADTMR_TRIG_ITR14             (14UL)  /*!< Internal trigger ITR14 */
#define LL_ADTMR_TRIG_ITR15             (15UL)  /*!< Internal trigger ITR15 */

#define LL_ADTMR_TRIG_CH0_FE            (16UL)  /*!< Channel 0 rising edge  */
#define LL_ADTMR_TRIG_CH0_F             (17UL)  /*!< Channel 0 falling edge */
#define LL_ADTMR_TRIG_CH1_F             (18UL)  /*!< Channel 1 falling edge */
#define LL_ADTMR_TRIG_CH2_F             (19UL)  /*!< Channel 2 falling edge */
#define LL_ADTMR_TRIG_CH3_F             (20UL)  /*!< Channel 3 falling edge */
#define LL_ADTMR_TRIG_ETR_FE            (21UL)  /*!< ETR rising edge        */
#define LL_ADTMR_TRIG_ETR_F             (22UL)  /*!< ETR falling edge       */

/* Per-instance trigger mapping: TMR9 */
#define LL_ADTMR_TRIG_TMR9_ITR0_TMR7_TRGO            (LL_ADTMR_TRIG_ITR0)    /*!< TMR9 ITR0: TMR7_TRGO      */
#define LL_ADTMR_TRIG_TMR9_ITR1_TMR8_TRGO            (LL_ADTMR_TRIG_ITR1)    /*!< TMR9 ITR1: TMR8_TRGO      */
#define LL_ADTMR_TRIG_TMR9_ITR2_TMR0_TRGO            (LL_ADTMR_TRIG_ITR2)    /*!< TMR9 ITR2: TMR0_TRGO      */
#define LL_ADTMR_TRIG_TMR9_ITR3_TMR1_TRGO            (LL_ADTMR_TRIG_ITR3)    /*!< TMR9 ITR3: TMR1_TRGO      */
#define LL_ADTMR_TRIG_TMR9_ITR4_TMR2_TRGO            (LL_ADTMR_TRIG_ITR4)    /*!< TMR9 ITR4: TMR2_TRGO      */
#define LL_ADTMR_TRIG_TMR9_ITR5_TMR3_TRGO            (LL_ADTMR_TRIG_ITR5)    /*!< TMR9 ITR5: TMR3_TRGO      */
#define LL_ADTMR_TRIG_TMR9_ITR6_TMR4_TRGO            (LL_ADTMR_TRIG_ITR6)    /*!< TMR9 ITR6: TMR4_TRGO      */
#define LL_ADTMR_TRIG_TMR9_ITR7_TMR0_OC0             (LL_ADTMR_TRIG_ITR7)    /*!< TMR9 ITR7: TMR0_OC0       */
#define LL_ADTMR_TRIG_TMR9_ITR8_TMR1_OC0             (LL_ADTMR_TRIG_ITR8)    /*!< TMR9 ITR8: TMR1_OC0       */
#define LL_ADTMR_TRIG_TMR9_ITR9_TMR2_OC0             (LL_ADTMR_TRIG_ITR9)    /*!< TMR9 ITR9: TMR2_OC0       */
#define LL_ADTMR_TRIG_TMR9_ITR10_TMR3_OC0            (LL_ADTMR_TRIG_ITR10)   /*!< TMR9 ITR10: TMR3_OC0      */
#define LL_ADTMR_TRIG_TMR9_ITR11_TMR4_OC0            (LL_ADTMR_TRIG_ITR11)   /*!< TMR9 ITR11: TMR4_OC0      */
#define LL_ADTMR_TRIG_TMR9_ITR12_TMR10_TRGO          (LL_ADTMR_TRIG_ITR12)   /*!< TMR9 ITR12: TMR10_TRGO    */
#define LL_ADTMR_TRIG_TMR9_ITR13_TMR10_OC0           (LL_ADTMR_TRIG_ITR13)   /*!< TMR9 ITR13: TMR10_OC0     */
#define LL_ADTMR_TRIG_TMR9_ITR14_TMR10_OC1           (LL_ADTMR_TRIG_ITR14)   /*!< TMR9 ITR14: TMR10_OC1     */
#define LL_ADTMR_TRIG_TMR9_ITR15_HRPWM_SYNCO         (LL_ADTMR_TRIG_ITR15)   /*!< TMR9 ITR15: HRPWM_SYNCO   */

/* Per-instance trigger mapping: TMR10 */
#define LL_ADTMR_TRIG_TMR10_ITR0_TMR7_TRGO           (LL_ADTMR_TRIG_ITR0)    /*!< TMR10 ITR0: TMR7_TRGO     */
#define LL_ADTMR_TRIG_TMR10_ITR1_TMR8_TRGO           (LL_ADTMR_TRIG_ITR1)    /*!< TMR10 ITR1: TMR8_TRGO     */
#define LL_ADTMR_TRIG_TMR10_ITR2_TMR0_TRGO           (LL_ADTMR_TRIG_ITR2)    /*!< TMR10 ITR2: TMR0_TRGO     */
#define LL_ADTMR_TRIG_TMR10_ITR3_TMR1_TRGO           (LL_ADTMR_TRIG_ITR3)    /*!< TMR10 ITR3: TMR1_TRGO     */
#define LL_ADTMR_TRIG_TMR10_ITR4_TMR2_TRGO           (LL_ADTMR_TRIG_ITR4)    /*!< TMR10 ITR4: TMR2_TRGO     */
#define LL_ADTMR_TRIG_TMR10_ITR5_TMR3_TRGO           (LL_ADTMR_TRIG_ITR5)    /*!< TMR10 ITR5: TMR3_TRGO     */
#define LL_ADTMR_TRIG_TMR10_ITR6_TMR4_TRGO           (LL_ADTMR_TRIG_ITR6)    /*!< TMR10 ITR6: TMR4_TRGO     */
#define LL_ADTMR_TRIG_TMR10_ITR7_TMR0_OC0            (LL_ADTMR_TRIG_ITR7)    /*!< TMR10 ITR7: TMR0_OC0      */
#define LL_ADTMR_TRIG_TMR10_ITR8_TMR1_OC0            (LL_ADTMR_TRIG_ITR8)    /*!< TMR10 ITR8: TMR1_OC0      */
#define LL_ADTMR_TRIG_TMR10_ITR9_TMR2_OC0            (LL_ADTMR_TRIG_ITR9)    /*!< TMR10 ITR9: TMR2_OC0      */
#define LL_ADTMR_TRIG_TMR10_ITR10_TMR3_OC0           (LL_ADTMR_TRIG_ITR10)   /*!< TMR10 ITR10: TMR3_OC0     */
#define LL_ADTMR_TRIG_TMR10_ITR11_TMR4_OC0           (LL_ADTMR_TRIG_ITR11)   /*!< TMR10 ITR11: TMR4_OC0     */
#define LL_ADTMR_TRIG_TMR10_ITR12_TMR9_TRGO          (LL_ADTMR_TRIG_ITR12)   /*!< TMR10 ITR12: TMR9_TRGO    */
#define LL_ADTMR_TRIG_TMR10_ITR13_TMR9_OC0           (LL_ADTMR_TRIG_ITR13)   /*!< TMR10 ITR13: TMR9_OC0     */
#define LL_ADTMR_TRIG_TMR10_ITR14_TMR9_OC1           (LL_ADTMR_TRIG_ITR14)   /*!< TMR10 ITR14: TMR9_OC1     */
#define LL_ADTMR_TRIG_TMR10_ITR15_HRPWM_SYNCO        (LL_ADTMR_TRIG_ITR15)   /*!< TMR10 ITR15: HRPWM_SYNCO  */
/** @} */

/** @name LL_ADTMR_ETRInputSrcTypeDef
  * @brief ADTMR LL ETR Input Source (SCR.ETS)
  * @{
  */
#define LL_ADTMR_ETRInputSrcTypeDef     LL_RSV_DATA_TYPE

/* Common ETR input sources */
#define LL_ADTMR_ETR_INPUT_SRC_ETR0             (0UL)   /*!< Internal input ETR0      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR1             (1UL)   /*!< Internal input ETR1      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR2             (2UL)   /*!< Internal input ETR2      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR3             (3UL)   /*!< Internal input ETR3      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR4             (4UL)   /*!< Internal input ETR4      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR5             (5UL)   /*!< Internal input ETR5      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR6             (6UL)   /*!< Internal input ETR6      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR7             (7UL)   /*!< Internal input ETR7      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR8             (8UL)   /*!< Internal input ETR8      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR9             (9UL)   /*!< Internal input ETR9      */
#define LL_ADTMR_ETR_INPUT_SRC_ETR10            (10UL)  /*!< Internal input ETR10     */
#define LL_ADTMR_ETR_INPUT_SRC_ETR11            (11UL)  /*!< Internal input ETR11     */
#define LL_ADTMR_ETR_INPUT_SRC_ETR12            (12UL)  /*!< Internal input ETR12     */
#define LL_ADTMR_ETR_INPUT_SRC_ETR13            (13UL)  /*!< Internal input ETR13     */
#define LL_ADTMR_ETR_INPUT_SRC_ETR14            (14UL)  /*!< Internal input ETR14     */
#define LL_ADTMR_ETR_INPUT_SRC_ETR15            (15UL)  /*!< Internal input ETR15     */

/* TMR9 specific ETR input sources */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_PAD         (LL_ADTMR_ETR_INPUT_SRC_ETR0)   /*!< ETR from PAD             */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_CMP0        (LL_ADTMR_ETR_INPUT_SRC_ETR1)   /*!< ETR from CMP0            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_CMP1        (LL_ADTMR_ETR_INPUT_SRC_ETR2)   /*!< ETR from CMP1            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_CMP2        (LL_ADTMR_ETR_INPUT_SRC_ETR3)   /*!< ETR from CMP2            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_CMP3        (LL_ADTMR_ETR_INPUT_SRC_ETR4)   /*!< ETR from CMP3            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_CMP4        (LL_ADTMR_ETR_INPUT_SRC_ETR5)   /*!< ETR from CMP4            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_CMP5        (LL_ADTMR_ETR_INPUT_SRC_ETR6)   /*!< ETR from CMP5            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_CMP6        (LL_ADTMR_ETR_INPUT_SRC_ETR7)   /*!< ETR from CMP6            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_PDM0        (LL_ADTMR_ETR_INPUT_SRC_ETR8)   /*!< ETR from PDM0            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_PDM1        (LL_ADTMR_ETR_INPUT_SRC_ETR9)   /*!< ETR from PDM1            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_ADC0WDG0    (LL_ADTMR_ETR_INPUT_SRC_ETR10)  /*!< ETR from ADC0 watchdog 0 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_ADC0WDG1    (LL_ADTMR_ETR_INPUT_SRC_ETR11)  /*!< ETR from ADC0 watchdog 1 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_HSE         (LL_ADTMR_ETR_INPUT_SRC_ETR12)  /*!< ETR from HSE             */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_ADC1WDG0    (LL_ADTMR_ETR_INPUT_SRC_ETR13)  /*!< ETR from ADC1 watchdog 0 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_ADC1WDG1    (LL_ADTMR_ETR_INPUT_SRC_ETR14)  /*!< ETR from ADC1 watchdog 1 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR9_HSI         (LL_ADTMR_ETR_INPUT_SRC_ETR15)  /*!< ETR from HSI             */

/* TMR10 specific ETR input sources */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_PAD        (LL_ADTMR_ETR_INPUT_SRC_ETR0)   /*!< ETR from PAD             */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_CMP2       (LL_ADTMR_ETR_INPUT_SRC_ETR1)   /*!< ETR from CMP2            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_CMP3       (LL_ADTMR_ETR_INPUT_SRC_ETR2)   /*!< ETR from CMP3            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_CMP4       (LL_ADTMR_ETR_INPUT_SRC_ETR3)   /*!< ETR from CMP4            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_CMP5       (LL_ADTMR_ETR_INPUT_SRC_ETR4)   /*!< ETR from CMP5            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_CMP6       (LL_ADTMR_ETR_INPUT_SRC_ETR5)   /*!< ETR from CMP6            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_CMP7       (LL_ADTMR_ETR_INPUT_SRC_ETR6)   /*!< ETR from CMP7            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_CMP8       (LL_ADTMR_ETR_INPUT_SRC_ETR7)   /*!< ETR from CMP8            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_PDM2       (LL_ADTMR_ETR_INPUT_SRC_ETR8)   /*!< ETR from PDM2            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_PDM3       (LL_ADTMR_ETR_INPUT_SRC_ETR9)   /*!< ETR from PDM3            */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_ADC2WDG0   (LL_ADTMR_ETR_INPUT_SRC_ETR10)  /*!< ETR from ADC2 watchdog 0 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_ADC2WDG1   (LL_ADTMR_ETR_INPUT_SRC_ETR11)  /*!< ETR from ADC2 watchdog 1 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_HSE        (LL_ADTMR_ETR_INPUT_SRC_ETR12)  /*!< ETR from HSE             */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_ADC3WDG0   (LL_ADTMR_ETR_INPUT_SRC_ETR13)  /*!< ETR from ADC3 watchdog 0 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_ADC3WDG1   (LL_ADTMR_ETR_INPUT_SRC_ETR14)  /*!< ETR from ADC3 watchdog 1 */
#define LL_ADTMR_ETR_INPUT_SRC_TMR10_HSI        (LL_ADTMR_ETR_INPUT_SRC_ETR15)  /*!< ETR from HSI             */
/** @} */

/** @name LL_ADTMR_CapCmpChTypeDef
  * @brief ADTMR LL Capture/Compare Channel (4 channels)
  * @{
  */
#define LL_ADTMR_CapCmpChTypeDef            uint32_t
#define LL_ADTMR_CAP_CMP_CH_0               (0UL)   /*!< Capture/Compare channel 0 */
#define LL_ADTMR_CAP_CMP_CH_1               (1UL)   /*!< Capture/Compare channel 1 */
#define LL_ADTMR_CAP_CMP_CH_2               (2UL)   /*!< Capture/Compare channel 2 */
#define LL_ADTMR_CAP_CMP_CH_3               (3UL)   /*!< Capture/Compare channel 3 */
#define LL_ADTMR_CAP_CMP_CH_0N              (4UL)   /*!< Capture/Compare channel 0 complementary output */
#define LL_ADTMR_CAP_CMP_CH_1N              (5UL)   /*!< Capture/Compare channel 1 complementary output */
#define LL_ADTMR_CAP_CMP_CH_2N              (6UL)   /*!< Capture/Compare channel 2 complementary output */
#define LL_ADTMR_CAP_CMP_CH_3N              (7UL)   /*!< Capture/Compare channel 3 complementary output */

#define IS_LL_ADTMR_CHANNEL(__VAL__)        (((__VAL__) >= LL_ADTMR_CAP_CMP_CH_0) && ((__VAL__) <= LL_ADTMR_CAP_CMP_CH_3N))

#define LL_ADTMR_CAP_CMP_CH_NUMS            (4UL)
#define LL_ADTMR_CAP_CMP_CHN_NUMS           (4UL)
#define LL_ADTMR_CAP_CMP_ALL_CH_NUMS        (LL_ADTMR_CAP_CMP_CH_NUMS + LL_ADTMR_CAP_CMP_CHN_NUMS)

#define IS_LL_ADTMR_CAP_CMP_CH(__VAL__)     (((__VAL__) >= LL_ADTMR_CAP_CMP_CH_0) && ((__VAL__) <= LL_ADTMR_CAP_CMP_CH_3))
#define IS_LL_ADTMR_CAP_CMP_CHN(__VAL__)    (((__VAL__) >= LL_ADTMR_CAP_CMP_CH_0N) && ((__VAL__) <= LL_ADTMR_CAP_CMP_CH_3N))

#if LL_ADTMR_CAP_CMP_CH_NUMS > 4UL
#error "LL_ADTMR_CAP_CMP_CH_NUMS"
#endif

#if LL_ADTMR_CAP_CMP_CH_NUMS != LL_ADTMR_CAP_CMP_CHN_NUMS
#error "LL_ADTMR_CAP_CMP_ALL_CH_NUMS"
#endif
/** @} */

/** @name LL_ADTMR_CapCmpOCTypeDef
  * @brief ADTMR LL Compare/Capture OC Type
  * @{
  */
#define LL_ADTMR_CapCmpOCTypeDef            uint32_t
#define LL_ADTMR_CAP_CMP_OC                 (0UL)
#define LL_ADTMR_CAP_CMP_OCN                (1UL)

#define IS_LL_ADTMR_CAP_CMP_OC(__VAL__)     (((__VAL__) == LL_ADTMR_CAP_CMP_OC) || \
                                             ((__VAL__) == LL_ADTMR_CAP_CMP_OCN))
/** @} */

/** @name LL_ADTMR_CapPolTypeDef
  * @brief ADTMR LL Capture Polarity
  * @{
  */
#define LL_ADTMR_CapPolTypeDef              LL_RSV_DATA_TYPE

#define LL_ADTMR_CAP_POL_CLOSE              (0UL)   /*!< Capture disabled       */
#define LL_ADTMR_CAP_POL_RISING             (1UL)   /*!< Rising edge            */
#define LL_ADTMR_CAP_POL_FALLING            (2UL)   /*!< Falling edge           */
#define LL_ADTMR_CAP_POL_BOTH_EDGE          (3UL)   /*!< Both rising and falling */

#define IS_LL_ADTMR_CAP_POL(__VAL__)        (((__VAL__) == LL_ADTMR_CAP_POL_CLOSE)    || \
                                             ((__VAL__) == LL_ADTMR_CAP_POL_RISING)   || \
                                             ((__VAL__) == LL_ADTMR_CAP_POL_FALLING)  || \
                                             ((__VAL__) == LL_ADTMR_CAP_POL_BOTH_EDGE))

/** @} */

/** @name LL_ADTMR_CapPrscTypeDef
  * @brief ADTMR LL Capture Prescaler
  * @{
  */
#define LL_ADTMR_CapPrscTypeDef             LL_RSV_DATA_TYPE

#define LL_ADTMR_CAP_PRESCALER_1            (0UL)   /*!< Capture every edge      */
#define LL_ADTMR_CAP_PRESCALER_2            (1UL)   /*!< Capture every 2 events  */
#define LL_ADTMR_CAP_PRESCALER_4            (2UL)   /*!< Capture every 4 events  */
#define LL_ADTMR_CAP_PRESCALER_8            (3UL)   /*!< Capture every 8 events  */

#define IS_LL_ADTMR_CAP_PRESCALER(__VAL__)  (((__VAL__) == LL_ADTMR_CAP_PRESCALER_1)  || \
                                             ((__VAL__) == LL_ADTMR_CAP_PRESCALER_2)  || \
                                             ((__VAL__) == LL_ADTMR_CAP_PRESCALER_4)  || \
                                             ((__VAL__) == LL_ADTMR_CAP_PRESCALER_8))
/** @} */

/** @name LL_ADTMR_CmpCapMapTypeDef
  * @brief ADTMR LL Compare/Capture (Output/Input) Mapping
  * @{
  */
#define LL_ADTMR_CmpCapMapTypeDef           LL_RSV_DATA_TYPE

#define LL_ADTMR_CMP_CAP_MAP_OUTPUT         (0UL)   /*!< Mapped on the output */
#define LL_ADTMR_CMP_CAP_MAP_INPUT_0        (1UL)   /*!< Mapped on the input 0 */
#define LL_ADTMR_CMP_CAP_MAP_INPUT_1        (2UL)   /*!< Mapped on the input 1 */
#define LL_ADTMR_CMP_CAP_MAP_INPUT_TRGI     (3UL)   /*!< Mapped on the trigger input */

#define IS_LL_ADTMR_CMP_CAP_MAP(__VAL__)    (((__VAL__) == LL_ADTMR_CMP_CAP_MAP_OUTPUT)   || \
                                             ((__VAL__) == LL_ADTMR_CMP_CAP_MAP_INPUT_0)  || \
                                             ((__VAL__) == LL_ADTMR_CMP_CAP_MAP_INPUT_1)  || \
                                             ((__VAL__) == LL_ADTMR_CMP_CAP_MAP_INPUT_TRGI))
/** @} */

/** @name LL_ADTMR_CmpOutputMapTypeDef
  * @brief ADTMR LL Compare Output Mapping
  * @{
  */
#define LL_ADTMR_CmpOutputMapTypeDef        LL_RSV_DATA_TYPE

#define LL_ADTMR_CMP_OUTPUT_MAP_OUT         LL_ADTMR_CMP_CAP_MAP_OUTPUT   /*!< Mapped on the output */

#define IS_LL_ADTMR_CMP_OUTPUT_MAP(__VAL__) ((__VAL__) == LL_ADTMR_CMP_OUTPUT_MAP_OUT)
/** @} */

/** @name LL_ADTMR_CapInputMapTypeDef
  * @brief ADTMR LL Capture Input Mapping
  * @{
  */
#define LL_ADTMR_CapInputMapTypeDef         LL_RSV_DATA_TYPE

#define LL_ADTMR_CAP_INPUT_MAP_0            LL_ADTMR_CMP_CAP_MAP_INPUT_0    /*!< Mapped on the CH0 input */
#define LL_ADTMR_CAP_INPUT_MAP_1            LL_ADTMR_CMP_CAP_MAP_INPUT_1    /*!< Mapped on the CH1 input */
#define LL_ADTMR_CAP_INPUT_MAP_TRGI         LL_ADTMR_CMP_CAP_MAP_INPUT_TRGI   /*!< Mapped on the trigger input */

#define IS_LL_ADTMR_CAP_INPUT_MAP(__VAL__)  (((__VAL__) == LL_ADTMR_CAP_INPUT_MAP_0) || \
                                             ((__VAL__) == LL_ADTMR_CAP_INPUT_MAP_1) || \
                                             ((__VAL__) == LL_ADTMR_CAP_INPUT_MAP_TRGI))
/** @} */

/** @name LL_ADTMR_CapInputSrcTypeDef
  * @brief ADTMR LL Capture Trigger Input Source
  * @{
  */
#define LL_ADTMR_CapInputSrcTypeDef         LL_RSV_DATA_TYPE

#define LL_ADTMR_CAP_INPUT_SRC_IN0          (0UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN1          (1UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN2          (2UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN3          (3UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN4          (4UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN5          (5UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN6          (6UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN7          (7UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN8          (8UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN9          (9UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN10         (10UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN11         (11UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN12         (12UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN13         (13UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN14         (14UL)
#define LL_ADTMR_CAP_INPUT_SRC_IN15         (15UL)

#define IS_LL_ADTMR_CAP_INPUT_SRC(__VAL__)  (((__VAL__) >= LL_ADTMR_CAP_INPUT_SRC_IN0) && \
                                             ((__VAL__) <= LL_ADTMR_CAP_INPUT_SRC_IN15))

/** @} */

/** @name LL_ADTMR_CmpPolTypeDef
  * @brief ADTMR LL Compare Output Polarity
  * @{
  */
#define LL_ADTMR_CmpPolTypeDef              LL_RSV_DATA_TYPE

#define LL_ADTMR_CMP_POL_HIGH               (0UL)   /*!< Compare output active high */
#define LL_ADTMR_CMP_POL_LOW                (1UL)   /*!< Compare output active low  */

#define IS_LL_ADTMR_CMP_POL(__VAL__)        (((__VAL__) == LL_ADTMR_CMP_POL_HIGH) || \
                                             ((__VAL__) == LL_ADTMR_CMP_POL_LOW))
/** @} */

/** @name LL_ADTMR_DzDigFilClkDivTypeDef
  * @brief ADTMR LL Dead-Zone Digital Filter Clock Division
  * @{
  */
#define LL_ADTMR_DzDigFilClkDivTypeDef      LL_RSV_DATA_TYPE

#define LL_ADTMR_DZ_DIG_FIL_CLK_DIV_1       (0UL)   /*!< Clock division 1 */
#define LL_ADTMR_DZ_DIG_FIL_CLK_DIV_2       (1UL)   /*!< Clock division 2 */
#define LL_ADTMR_DZ_DIG_FIL_CLK_DIV_4       (2UL)   /*!< Clock division 4 */
#define LL_ADTMR_DZ_DIG_FIL_CLK_DIV_8       (3UL)   /*!< Clock division 8 */

#define IS_LL_ADTMR_DZ_DIG_FIL_CLK_DIV(__VAL__)       (((__VAL__) == LL_ADTMR_DZ_DIG_FIL_CLK_DIV_1) || \
                                                       ((__VAL__) == LL_ADTMR_DZ_DIG_FIL_CLK_DIV_2) || \
                                                       ((__VAL__) == LL_ADTMR_DZ_DIG_FIL_CLK_DIV_4) || \
                                                       ((__VAL__) == LL_ADTMR_DZ_DIG_FIL_CLK_DIV_8))
/** @} */

/** @name LL_ADTMR_SlvModeTypeDef
  * @brief ADTMR LL Slave Mode
  * @{
  */
#define LL_ADTMR_SlvModeTypeDef             LL_RSV_DATA_TYPE

#define LL_ADTMR_SLV_MODE_DIS               (0UL)   /*!< Slave mode disabled      */
#define LL_ADTMR_SLV_MODE_RST               (4UL)   /*!< Reset mode               */
#define LL_ADTMR_SLV_MODE_GATING            (5UL)   /*!< Gated mode               */
#define LL_ADTMR_SLV_MODE_TRIG              (6UL)   /*!< Trigger mode             */
#define LL_ADTMR_SLV_MODE_EXTCLK            (7UL)   /*!< External clock mode 1    */
#define LL_ADTMR_SLV_MODE_RST_TRIG          (8UL)   /*!< Combined reset + trigger */
#define LL_ADTMR_SLV_MODE_RST_GATING        (9UL)   /*!< Combined reset + gated   */

#define IS_LL_ADTMR_SLV_MODE(__VAL__)       (((__VAL__) == LL_ADTMR_SLV_MODE_DIS)       || \
                                             ((__VAL__) == LL_ADTMR_SLV_MODE_RST)       || \
                                             ((__VAL__) == LL_ADTMR_SLV_MODE_GATING)    || \
                                             ((__VAL__) == LL_ADTMR_SLV_MODE_TRIG)      || \
                                             ((__VAL__) == LL_ADTMR_SLV_MODE_EXTCLK)    || \
                                             ((__VAL__) == LL_ADTMR_SLV_MODE_RST_TRIG)  || \
                                             ((__VAL__) == LL_ADTMR_SLV_MODE_RST_GATING))
/** @} */


/** @name LL_ADTMR_EvtGenMaskTypeDef
  * @brief ADTMR LL Timer Event Generation Mask
  * @{
  */
#define LL_ADTMR_EvtGenMaskTypeDef                uint32_t    

#define LL_ADTMR_EVT_GEN_UPDATE                   (TMR9_UGR_UG_Msk)         /*!< Timer Event Generation Update                    */
#define LL_ADTMR_EVT_GEN_TRIGGER                  (TMR9_UGR_TG_Msk)         /*!< Timer Event Generation Trigger                   */
#define LL_ADTMR_EVT_GEN_BREAK0                   (TMR9_UGR_B0G_Msk)        /*!< Timer Event Generation Break 0                   */
#define LL_ADTMR_EVT_GEN_BREAK1                   (TMR9_UGR_B1G_Msk)        /*!< Timer Event Generation Break 1                   */
#define LL_ADTMR_EVT_GEN_CAP_CMP_0                (TMR9_UGR_CC0UG_Msk)      /*!< Timer Event Generation Capture/Compare 0         */
#define LL_ADTMR_EVT_GEN_CAP_CMP_1                (TMR9_UGR_CC1UG_Msk)      /*!< Timer Event Generation Capture/Compare 1         */
#define LL_ADTMR_EVT_GEN_CAP_CMP_2                (TMR9_UGR_CC2UG_Msk)      /*!< Timer Event Generation Capture/Compare 2         */
#define LL_ADTMR_EVT_GEN_CAP_CMP_3                (TMR9_UGR_CC3UG_Msk)      /*!< Timer Event Generation Capture/Compare 3         */

#define LL_ADTMR_EVT_GEN_ALL_MSK                  ((TMR9_UGR_CC3UG_Msk              | TMR9_UGR_CC2UG_Msk              | \
                                                    TMR9_UGR_CC1UG_Msk              | TMR9_UGR_CC0UG_Msk              | \
                                                    TMR9_UGR_B1G_Msk                | TMR9_UGR_B0G_Msk                | \
                                                    TMR9_UGR_TG_Msk                 | TMR9_UGR_UG_Msk                 ))
/** @} */



/** @name LL_ADTMR_BrkPolTypeDef
  * @brief ADTMR LL Break Input Polarity (DCR.BK0P / DCR.BK1P)
  * @{
  */
#define LL_ADTMR_BrkPolTypeDef              LL_RSV_DATA_TYPE

#define LL_ADTMR_BRK_POL_HIGH               (0UL)   /*!< Break input high active */
#define LL_ADTMR_BRK_POL_LOW                (1UL)   /*!< Break input low active  */

#define IS_LL_ADTMR_BRK_POL(__VAL__)        (((__VAL__) == LL_ADTMR_BRK_POL_HIGH) || \
                                             ((__VAL__) == LL_ADTMR_BRK_POL_LOW))
/** @} */


/** @name LL_ADTMR_BrkInPolTypeDef
  * @brief ADTMR LL Break Input Valid Level Polarity
  * @{
  */
#define LL_ADTMR_BrkInPolTypeDef            LL_RSV_DATA_TYPE

#define LL_ADTMR_BRK_IN_POL_VALID_HIGH      (0UL)   /*!< Break input valid level high */
#define LL_ADTMR_BRK_IN_POL_VALID_LOW       (1UL)   /*!< Break input valid low high */

#define IS_LL_ADTMR_BRK_IN_POL(__VAL__)     (((__VAL__) == LL_ADTMR_BRK_IN_POL_VALID_HIGH) || \
                                             ((__VAL__) == LL_ADTMR_BRK_IN_POL_VALID_LOW))
/** @} */

/** @name LL_ADTMR_RunOffStaTypeDef
  * @brief ADTMR LL Run-Mode Off-State
  * @{
  */
#define LL_ADTMR_RunOffStaTypeDef           LL_RSV_DATA_TYPE

#define LL_ADTMR_RUN_OFF_STA_COMP_CLOSE    (0UL)   /*!< Idle-Mode Off-State complementary output close */
#define LL_ADTMR_RUN_OFF_STA_COMP_IVD      (1UL)   /*!< Idle-Mode Off-State complementary output is in the invalid state*/

#define IS_LL_ADTMR_RUN_OFF_STA(__VAL__)   (((__VAL__) == LL_ADTMR_RUN_OFF_STA_COMP_CLOSE) || \
                                             ((__VAL__) == LL_ADTMR_RUN_OFF_STA_COMP_IVD))
/** @} */

/** @name LL_ADTMR_IdleOffStaTypeDef
  * @brief ADTMR LL Idle-Mode Off-State
  * @{
  */
#define LL_ADTMR_IdleOffStaTypeDef          LL_RSV_DATA_TYPE

#define LL_ADTMR_IDLE_OFF_STA_COMP_CLOSE    (0UL)   /*!< Idle-Mode Off-State complementary output close */
#define LL_ADTMR_IDLE_OFF_STA_COMP_IDLE     (1UL)   /*!< Idle-Mode Off-State complementary output is in the idle state*/

#define IS_LL_ADTMR_IDLE_OFF_STA(__VAL__)   (((__VAL__) == LL_ADTMR_IDLE_OFF_STA_COMP_CLOSE) || \
                                             ((__VAL__) == LL_ADTMR_IDLE_OFF_STA_COMP_IDLE))
/** @} */

/** @name LL_ADTMR_CapFilTypeDef
  * @brief ADTMR LL Capture Filter
  * @{
  */
#define LL_ADTMR_CapFilTypeDef              LL_RSV_DATA_TYPE

#define LL_ADTMR_CAP_FILTER_NONE            (0UL)
#define LL_ADTMR_CAP_FILTER_TDS_X1          (1UL)
#define LL_ADTMR_CAP_FILTER_TDS_X2          (2UL)
#define LL_ADTMR_CAP_FILTER_TDS_X3          (3UL)
#define LL_ADTMR_CAP_FILTER_TDS_X4          (4UL)
#define LL_ADTMR_CAP_FILTER_TDS_X5          (5UL)
#define LL_ADTMR_CAP_FILTER_TDS_X6          (6UL)
#define LL_ADTMR_CAP_FILTER_TDS_X7          (7UL)
#define LL_ADTMR_CAP_FILTER_TDS_X8          (8UL)
#define LL_ADTMR_CAP_FILTER_TDS_X9          (9UL)
#define LL_ADTMR_CAP_FILTER_TDS_X10         (10UL)
#define LL_ADTMR_CAP_FILTER_TDS_X11         (11UL)
#define LL_ADTMR_CAP_FILTER_TDS_X12         (12UL)
#define LL_ADTMR_CAP_FILTER_TDS_X13         (13UL)
#define LL_ADTMR_CAP_FILTER_TDS_X14         (14UL)
#define LL_ADTMR_CAP_FILTER_TDS_X15         (15UL)

#define IS_LL_ADTMR_CAP_FILTER(__VAL__)     (((__VAL__) >= LL_ADTMR_CAP_FILTER_NONE) && \
                                             ((__VAL__) <= LL_ADTMR_CAP_FILTER_TDS_X15))
/** @} */

/** @name LL_ADTMR_OCModeTypeDef
  * @brief ADTMR LL Compare Output Mode (CCMR.OCxM)
  * @{
  */
#define LL_ADTMR_OCModeTypeDef                  LL_RSV_DATA_TYPE

#define LL_ADTMR_CMP_MODE_FREEZE                (0UL)    /*!< Frozen                    */
#define LL_ADTMR_CMP_MODE_ACTIVE                (1UL)    /*!< Force active              */
#define LL_ADTMR_CMP_MODE_INACTIVE              (2UL)    /*!< Force inactive            */
#define LL_ADTMR_CMP_MODE_TOGGLE                (3UL)    /*!< Toggle on match           */
#define LL_ADTMR_CMP_MODE_FORCE_INACTIVE        (4UL)    /*!< Force inactive on match   */
#define LL_ADTMR_CMP_MODE_FORCE_ACTIVE          (5UL)    /*!< Force active on match     */
#define LL_ADTMR_CMP_MODE_PWM1                  (6UL)    /*!< PWM mode 1                */
#define LL_ADTMR_CMP_MODE_PWM2                  (7UL)    /*!< PWM mode 2                */
#define LL_ADTMR_CMP_MODE_RETRIG_OPM1           (8UL)    /*!< Retriggerable OPM mode 1  */
#define LL_ADTMR_CMP_MODE_RETRIG_OPM2           (9UL)    /*!< Retriggerable OPM mode 2  */
#define LL_ADTMR_CMP_MODE_COMB_PWM1             (12UL)   /*!< Combined PWM mode 1       */
#define LL_ADTMR_CMP_MODE_COMB_PWM2             (13UL)   /*!< Combined PWM mode 2       */
#define LL_ADTMR_CMP_MODE_ASYM_PWM1             (14UL)   /*!< Asymmetric PWM mode 1     */
#define LL_ADTMR_CMP_MODE_ASYM_PWM2             (15UL)   /*!< Asymmetric PWM mode 2     */

#define IS_LL_ADTMR_CMP_MODE(__VAL__)           ((((__VAL__) >= LL_ADTMR_CMP_MODE_FREEZE)    && ((__VAL__) <= LL_ADTMR_CMP_MODE_RETRIG_OPM2)) || \
                                                 (((__VAL__) >= LL_ADTMR_CMP_MODE_COMB_PWM1) && ((__VAL__) <= LL_ADTMR_CMP_MODE_ASYM_PWM2)))
/** @} */


/**
  * @}
  */ /* ADTMR_LL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup ADTMR_LL_Exported_Macros ADTMR LL Exported Macros
  * @brief    ADTMR LL Exported Macros
  * @{
  */


/**
  * @brief  ADTMR 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define LL_ADTMR_REG_OFFSET(__REG__, offset)            \
        (*((volatile uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))
/**
  * @}
  */ /* ADTMR_LL_Exported_Macros */

/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup ADTMR_LL_Exported_Functions ADTMR LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_ADTMR_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_ADTMR_ASSERT_INLINE_PARAM == 1)
extern void LL_ADTMR_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_ADTMR_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_ADTMR_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_ADTMR_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup ADTMR_LL_EF_Configuration LL ADTMR Configuration
  * @brief    LL ADTMR Configuration
  * @{
  */

/**
  * @brief  Enable the counter
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableCounter(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->CR0, TMR9_CR0_CEN_Msk);
}

/**
  * @brief  Disable the counter
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableCounter(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->CR0, TMR9_CR0_CEN_Msk);
}

/**
  * @brief  Judge whether the counter is enabled or not (CR0.CEN)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Counter is disabled
  * @retval 1 Counter is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledCounter(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_CEN_Msk, TMR9_CR0_CEN_Pos));
}

/**
  * @brief  Set the counter value (16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetCounter(ADTMR_TypeDef *ADTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->CNTR, ((Val) & TMR9_CNTR_CNT_Val));
}

/**
  * @brief  Get the counter value (16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Counter value (16 bits)
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetCounter(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CNTR) & TMR9_CNTR_CNT_Val);
}

/**
  * @brief  Set the counter period (auto-reload value, 16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Period Counter period value
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetAutoReload(ADTMR_TypeDef *ADTMRx, uint32_t Period)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->CPR, ((Period) & TMR9_CPR_CPV_Val));
}

/**
  * @brief  Get the counter period (16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Counter period (16 bits)
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetAutoReload(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CPR) & TMR9_CPR_CPV_Val);
}

/**
  * @brief  Set the prescaler division value (16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetPrescaler(ADTMR_TypeDef *ADTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->PSCR, ((Val) & TMR9_PSCR_PSC_Val));
}

/**
  * @brief  Get the prescaler division value (16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Prescaler division value (16 bits)
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetPrescaler(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->PSCR) & TMR9_PSCR_PSC_Val);
}

/**
  * @brief  Set the repetition counter value (CRR.REP, 8 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetRepetitionCounter(ADTMR_TypeDef *ADTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->CRR, ((Val) & TMR9_CRR_REP_Val));
}

/**
  * @brief  Get the repetition counter value (8 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Repetition counter value (8 bits)
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetRepetitionCounter(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CRR) & TMR9_CRR_REP_Val);
}

/**
  * @brief  Enable the auto-preload
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableAutoReload(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->CR0, TMR9_CR0_ARE_Msk);
}

/**
  * @brief  Disable the auto-preload
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableAutoReload(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->CR0, TMR9_CR0_ARE_Msk);
}

/**
  * @brief  Judge whether the auto-preload is enabled or not
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Auto-preload is disabled
  * @retval 1 Auto-preload is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsAutoReloadEnabled(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_ARE_Msk, TMR9_CR0_ARE_Pos));
}

/**
  * @brief  Set TI0 Input Source 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Src TI0 Input Source @ref LL_ADTMR_TI0InSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetTI0InputSource(ADTMR_TypeDef *ADTMRx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG(ADTMRx->CR0, TMR9_CR0_TI0S_Msk, (((Src) & TMR9_CR0_TI0S_Val) << TMR9_CR0_TI0S_Pos));
}

/**
  * @brief  Get TI0 Input Source 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return TI0 Input Source @ref LL_ADTMR_TI0InSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetTI0InputSource(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_TI0S_Msk, TMR9_CR0_TI0S_Pos));
}

/**
  * @brief  Set the counter work mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mode Mode to be set @ref LL_ADTMR_WorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetOnePulseMode(ADTMR_TypeDef *ADTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_WORK_MODE(Mode));

    MODIFY_REG((ADTMRx)->CR0, TMR9_CR0_OPM_Msk, (((Mode) & TMR9_CR0_OPM_Val) << TMR9_CR0_OPM_Pos));
}

/**
  * @brief  Get the counter work mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Counter work mode @ref LL_ADTMR_WorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetOnePulseMode(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_OPM_Msk, TMR9_CR0_OPM_Pos));
}

/**
  * @brief  Set the update event source
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Src Source to be selected @ref LL_ADTMR_UpdateEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetUpdateSource(ADTMR_TypeDef *ADTMRx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_UPDATE_EVT_SRC(Src));

    MODIFY_REG((ADTMRx)->CR0, TMR9_CR0_URS_Msk, (((Src) & TMR9_CR0_URS_Val) << TMR9_CR0_URS_Pos));
}

/**
  * @brief  Get the update event source
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Update event source @ref LL_ADTMR_UpdateEvtSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetUpdateSource(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_URS_Msk, TMR9_CR0_URS_Pos));
}

/**
  * @brief  Enable the update event (UDIS = 0)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableUpdateEvent(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->CR0, TMR9_CR0_UDIS_Msk);
}

/**
  * @brief  Disable the update event (UDIS = 1)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableUpdateEvent(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->CR0, TMR9_CR0_UDIS_Msk);
}

/**
  * @brief  Judge whether the update event is enabled or not
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Update event is disabled
  * @retval 1 Update event is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledUpdateEvent(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (!(READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_UDIS_Msk, TMR9_CR0_UDIS_Pos)));
}

/**
  * @brief  Set the counter direction
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Dir Capture/compare direction @ref LL_ADTMR_CntDirTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetDirection(ADTMR_TypeDef *ADTMRx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_CNT_DIR(Dir));

    MODIFY_REG((ADTMRx)->CR0, TMR9_CR0_DIR_Msk, (((Dir) & TMR9_CR0_DIR_Val) << TMR9_CR0_DIR_Pos));
}

/**
  * @brief  Get the counter direction
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Counter direction @ref LL_ADTMR_CntDirTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetDirection(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_DIR_Msk, TMR9_CR0_DIR_Pos));
}

/**
  * @brief  Set the counter alignment mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mode Mode to be set @ref LL_ADTMR_CtrAlignModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetAlignmentMode(ADTMR_TypeDef *ADTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_CTR_ALIGN_MODE(Mode));

    MODIFY_REG((ADTMRx)->CR0, TMR9_CR0_CMS_Msk, (((Mode) & TMR9_CR0_CMS_Val) << TMR9_CR0_CMS_Pos));
}

/**
  * @brief  Get the counter alignment mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Counter alignment mode @ref LL_ADTMR_CtrAlignModeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetAlignmentMode(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_CMS_Msk, TMR9_CR0_CMS_Pos));
}

/**
  * @brief  Set the master mode (source of the TRGO signal)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mode Mode to be set @ref LL_ADTMR_MstModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetTriggerOutput(ADTMR_TypeDef *ADTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_MST_MODE(Mode));

    MODIFY_REG((ADTMRx)->CR1, TMR9_CR1_MMS_Msk, (((Mode) & TMR9_CR1_MMS_Val) << TMR9_CR1_MMS_Pos));
}

/**
  * @brief  Get the master mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Master mode @ref LL_ADTMR_MstModeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetTriggerOutput(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR1, TMR9_CR1_MMS_Msk, TMR9_CR1_MMS_Pos));
}


/**
  * @brief  Set the output idle state of a given channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_*)
  * @param  IdleState Idle state @ref LL_ADTMR_OutputIdleStaTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetIdleState(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t IdleState)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_CHANNEL(Channel));

    if (Channel <= LL_ADTMR_CAP_CMP_CH_3) {
        MODIFY_REG((ADTMRx)->CR1, TMR9_CR1_OIS0_Msk << (((uint32_t)(Channel) % 4) * 2), 
            (((IdleState) & TMR9_CR1_OIS0_Val) << (TMR9_CR1_OIS0_Pos + ((uint32_t)(Channel) % 4) * 2)));
    } else if (Channel <= LL_ADTMR_CAP_CMP_CH_3N){
        MODIFY_REG((ADTMRx)->CR1, TMR9_CR1_OIS0N_Msk << (((uint32_t)(Channel) % 4) * 2), 
            (((IdleState) & TMR9_CR1_OIS0N_Val) << (TMR9_CR1_OIS0N_Pos + ((uint32_t)(Channel) % 4) * 2)));
    }
}

/**
  * @brief  Select the ETR input source (SCR.ETS, 4 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Src Source to be selected @ref LL_ADTMR_ETRInputSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetETRInputSrc(ADTMR_TypeDef *ADTMRx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->SCR, TMR9_SCR_ETS_Msk, (((Src) & TMR9_SCR_ETS_Val) << TMR9_SCR_ETS_Pos));
}

/**
  * @brief  Get the ETR input source
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return ETR input source @ref LL_ADTMR_ETRInputSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetETRInputSrc(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SCR, TMR9_SCR_ETS_Msk, TMR9_SCR_ETS_Pos));
}

/**
  * @brief  Set the ETR mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mode Mode to be set @ref LL_ADTMR_ETRModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetETRMode(ADTMR_TypeDef *ADTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_ETR_MODE(Mode));

    MODIFY_REG((ADTMRx)->SCR, TMR9_SCR_EE_Msk, (((Mode) & TMR9_SCR_EE_Val) << TMR9_SCR_EE_Pos));
}

/**
  * @brief  Get the ETR mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return ETR mode @ref LL_ADTMR_ETRModeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetETRMode(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SCR, TMR9_SCR_EE_Msk, TMR9_SCR_EE_Pos));
}

/**
  * @brief  Set the ETR edge mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mode Mode to be set @ref LL_ADTMR_ETREdgeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetETREdgeMode(ADTMR_TypeDef *ADTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_ETR_EDGE_MODE(Mode));

    MODIFY_REG((ADTMRx)->SCR, TMR9_SCR_EMS_Msk, (((Mode) & TMR9_SCR_EMS_Val) << TMR9_SCR_EMS_Pos));
}

/**
  * @brief  Get the ETR edge mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return ETR edge mode @ref LL_ADTMR_ETREdgeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetETREdgeMode(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SCR, TMR9_SCR_EMS_Msk, TMR9_SCR_EMS_Pos));
}

/**
  * @brief  Set the ETR filter coefficient (SCR.EFS, 4 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Fil Filter value @ref LL_ADTMR_ETRFilTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetETRFilter(ADTMR_TypeDef *ADTMRx, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->SCR, TMR9_SCR_EFS_Msk, (((Fil) & TMR9_SCR_EFS_Val) << TMR9_SCR_EFS_Pos));
}

/**
  * @brief  Get the ETR filter coefficient
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return ETR filter coefficient @ref LL_ADTMR_ETRFilTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetETRFilter(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SCR, TMR9_SCR_EFS_Msk, TMR9_SCR_EFS_Pos));
}

/**
  * @brief  Set the trigger input source (SCR.TS, 5 bits, raw value)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Tri Trigger selection @ref LL_ADTMR_TrigTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetTriggerInput(ADTMR_TypeDef *ADTMRx, uint32_t Tri)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->SCR, TMR9_SCR_TS_Msk, (((Tri) & TMR9_SCR_TS_Val) << TMR9_SCR_TS_Pos));
}

/**
  * @brief  Get the trigger input source
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Trigger input source @ref LL_ADTMR_TrigTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetTrigger(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SCR, TMR9_SCR_TS_Msk, TMR9_SCR_TS_Pos));
}

/**
  * @brief  Set the slave mode (SCR.SMS, 4 bits, raw value)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mode Mode to be set @ref LL_ADTMR_SlvModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetSlaveMode(ADTMR_TypeDef *ADTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->SCR, TMR9_SCR_SMS_Msk, (((Mode) & TMR9_SCR_SMS_Val) << TMR9_SCR_SMS_Pos));
}

/**
  * @brief  Get the slave mode
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Slave mode @ref LL_ADTMR_SlvModeTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetSlaveMode(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SCR, TMR9_SCR_SMS_Msk, TMR9_SCR_SMS_Pos));
}

/**
  * @brief  Enable the master/slave fast sync (SCR.FE)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableMstSlvFastSync(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->SCR, TMR9_SCR_FE_Msk);
}

/**
  * @brief  Disable the master/slave fast sync
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableMstSlvFastSync(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->SCR, TMR9_SCR_FE_Msk);
}

/**
  * @brief  Set the dead-time generator value (DCR.DTG, 8 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Dtg Dead-time value
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetFallingDeadTime(ADTMR_TypeDef *ADTMRx, uint32_t Dtg)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->DCR, TMR9_DCR_DTG_Msk, (((Dtg) & TMR9_DCR_DTG_Val) << TMR9_DCR_DTG_Pos));
}

/**
  * @brief  Get the dead-time generator value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Dead-time generator value
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetFallingDeadTime(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->DCR, TMR9_DCR_DTG_Msk, TMR9_DCR_DTG_Pos));
}

/**
  * @brief  Set the dead-time digital filter clock division (CR0.DCD)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Div Dead-zone / digital filter clock division @ref LL_ADTMR_DzDigFilClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetDzDigFilClkDiv(ADTMR_TypeDef *ADTMRx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_DZ_DIG_FIL_CLK_DIV(Div));

    MODIFY_REG((ADTMRx)->CR0, TMR9_CR0_DCD_Msk, (((Div) & TMR9_CR0_DCD_Val) << TMR9_CR0_DCD_Pos));
}

/**
  * @brief  Get the dead-time digital filter clock division (CR0.DCD)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Clock division: @ref LL_ADTMR_DZ_DIG_FIL_CLK_DIV_1 ... _8
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetDzDigFilClkDiv(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->CR0, TMR9_CR0_DCD_Msk, TMR9_CR0_DCD_Pos));
}

/**
  * @brief  Enable the main output (DCR.MOE)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableAllOutputs(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->DCR, TMR9_DCR_MOE_Msk);
}

/**
  * @brief  Disable the main output (DCR.MOE)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableAllOutputs(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->DCR, TMR9_DCR_MOE_Msk);
}

/**
  * @brief  Enable the automatic output (DCR.AOE)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableAutomaticOutput(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->DCR, TMR9_DCR_AOE_Msk);
}

/**
  * @brief  Disable the automatic output (DCR.AOE)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableAutomaticOutput(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->DCR, TMR9_DCR_AOE_Msk);
}

/**
  * @brief  Set the run-mode off-state of the outputs (DCR.OSSR)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Sta Output off-state @ref LL_ADTMR_RunOffStaTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetRunModeOffState(ADTMR_TypeDef *ADTMRx, uint32_t Sta)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_OUTPUT_STATE(Sta));

    MODIFY_REG((ADTMRx)->DCR, TMR9_DCR_OSSR_Msk, (((Sta) & TMR9_DCR_OSSR_Val) << TMR9_DCR_OSSR_Pos));
}

/**
  * @brief  Set the idle-mode off-state of the outputs (DCR.OSSI)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Sta Output off-state @ref LL_ADTMR_IdleOffStaTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetIdleModeOffState(ADTMR_TypeDef *ADTMRx, uint32_t Sta)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_OUTPUT_STATE(Sta));

    MODIFY_REG((ADTMRx)->DCR, TMR9_DCR_OSSI_Msk, (((Sta) & TMR9_DCR_OSSI_Val) << TMR9_DCR_OSSI_Pos));
}

/**
  * @brief  Enable break input 0 (DCR.BK0E)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableBreak0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->DCR, TMR9_DCR_BK0E_Msk);
}

/**
  * @brief  Disable break input 0
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableBreak0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->DCR, TMR9_DCR_BK0E_Msk);
}

/**
  * @brief  Set break input 0 polarity (DCR.BK0P)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Pol Polarity to be set @ref LL_ADTMR_BrkPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak0Polarity(ADTMR_TypeDef *ADTMRx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->DCR, TMR9_DCR_BK0P_Msk, (((Pol) & TMR9_DCR_BK0P_Val) << TMR9_DCR_BK0P_Pos));
}

/**
  * @brief  Set break input 0 filter (DCR.BK0F, 8 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Fil Filter value
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak0Filter(ADTMR_TypeDef *ADTMRx, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->DCR, TMR9_DCR_BK0F_Msk, (((Fil) & TMR9_DCR_BK0F_Val) << TMR9_DCR_BK0F_Pos));
}

/**
  * @brief  Enable break input 1 (DCR.BK1E)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableBreak1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->DCR, TMR9_DCR_BK1E_Msk);
}

/**
  * @brief  Disable break input 1
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableBreak1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->DCR, TMR9_DCR_BK1E_Msk);
}

/**
  * @brief  Set break input 1 polarity (DCR.BK1P)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Pol Polarity to be set @ref LL_ADTMR_BrkPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak1Polarity(ADTMR_TypeDef *ADTMRx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->DCR, TMR9_DCR_BK1P_Msk, (((Pol) & TMR9_DCR_BK1P_Val) << TMR9_DCR_BK1P_Pos));
}

/**
  * @brief  Set break input 1 filter (DCR.BK1F, 8 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Fil Filter value
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak1Filter(ADTMR_TypeDef *ADTMRx, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->DCR, TMR9_DCR_BK1F_Msk, (((Fil) & TMR9_DCR_BK1F_Val) << TMR9_DCR_BK1F_Pos));
}

/**
  * @brief  Set the break input 0 source mask (BER.B0IEN, 16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  En Enable mask
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak0InputEnable(ADTMR_TypeDef *ADTMRx, uint32_t En)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->BER, TMR9_BER_B0IEN_Msk, (((En) & TMR9_BER_B0IEN_Val) << TMR9_BER_B0IEN_Pos));
}

/**
  * @brief  Set the break input 0 polarity mask (BPR.B0POL, 16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Pol Polarity to be set @ref LL_ADTMR_BrkPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak0InputPolarity(ADTMR_TypeDef *ADTMRx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->BPR, TMR9_BPR_B0POL_Msk, (((Pol) & TMR9_BPR_B0POL_Val) << TMR9_BPR_B0POL_Pos));
}

/**
  * @brief  Enable the break input 0 source 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableBreak0Input(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->BER, TMR9_BER_B0IEN_Msk & (MskBit << TMR9_BER_B0IEN_Pos));
}

/**
  * @brief  Disable the break input 0 source 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableBreak0Input(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->BER, TMR9_BER_B0IEN_Msk & (MskBit << TMR9_BER_B0IEN_Pos));
}

/**
  * @brief  Set the break input 0 polarity high
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak0InputPolarityHigh(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->BPR, TMR9_BPR_B0POL_Msk & (MskBit << TMR9_BPR_B0POL_Pos));
}

/**
  * @brief  Set the break input 0 polarity low
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak0InputPolarityLow(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->BPR, TMR9_BPR_B0POL_Msk & (MskBit << TMR9_BPR_B0POL_Pos));
}

/**
  * @brief  Set the break input 1 source mask (BER.B1IEN, 16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  En Enable mask
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak1InputEnable(ADTMR_TypeDef *ADTMRx, uint32_t En)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->BER, TMR9_BER_B1IEN_Msk, (((En) & TMR9_BER_B1IEN_Val) << TMR9_BER_B1IEN_Pos));
}

/**
  * @brief  Set the break input 1 polarity mask (BPR.B1POL, 16 bits)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Pol Polarity to be set @ref LL_ADTMR_BrkPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak1InputPolarity(ADTMR_TypeDef *ADTMRx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->BPR, TMR9_BPR_B1POL_Msk, (((Pol) & TMR9_BPR_B1POL_Val) << TMR9_BPR_B1POL_Pos));
}

/**
  * @brief  Enable the break input 1 source 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableBreak1Input(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->BER, TMR9_BER_B1IEN_Msk & (MskBit << TMR9_BER_B1IEN_Pos));
}

/**
  * @brief  Disable the break input 1 source 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableBreak1Input(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->BER, TMR9_BER_B1IEN_Msk & (MskBit << TMR9_BER_B1IEN_Pos));
}

/**
  * @brief  Set the break input 1 polarity high
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak1InputPolarityHigh(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->BPR, TMR9_BPR_B1POL_Msk & (MskBit << TMR9_BPR_B1POL_Pos));
}

/**
  * @brief  Set the break input 1 polarity low
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  MskBit This parameter can be one of the LL_ADTMR_BRK_IN_SRC_MASK_* @ref LL_ADTMR_BrkInputSrcMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetBreak1InputPolarityLow(ADTMR_TypeDef *ADTMRx, uint32_t MskBit)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->BPR, TMR9_BPR_B1POL_Msk & (MskBit << TMR9_BPR_B1POL_Pos));
}


/**
  * @brief  Generate a software update event
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_UPDATE(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_UG_Msk);
}

/**
  * @brief  Generate a trigger event
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_TRIG(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_TG_Msk);
}

/**
  * @brief  Generate a break 0 event (UGR.B0G)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_BRK0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_B0G_Msk);
}

/**
  * @brief  Generate a break 1 event (UGR.B1G)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_BRK1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_B1G_Msk);
}

/**
  * @brief  Generate a capture/compare 0 update event
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_CC0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_CC0UG_Msk);
}

/**
  * @brief  Generate a capture/compare 1 update event
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_CC1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_CC1UG_Msk);
}

/**
  * @brief  Generate a capture/compare 2 update event
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_CC2(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_CC2UG_Msk);
}

/**
  * @brief  Generate a capture/compare 3 update event
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_CC3(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->UGR, TMR9_UGR_CC3UG_Msk);
}

/**
  * @brief  Generate a update event
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_GenerateEvent_CCxUG(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    SET_BIT((ADTMRx)->UGR, (TMR9_UGR_CC0UG_Msk) << (((Channel) % 4UL) * 1UL));
}

/**
  * @brief  Set the input filter of a given capture channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Fil Filter value @ref LL_ADTMR_CapFilTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_IC_SetFilter(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_OC0M_Msk << (((Channel) % 4UL) * 8UL), 
            (((Fil) & TMR9_CCMR_OC0M_Val) << (TMR9_CCMR_OC0M_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the output mode of a given compare channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Mode Mode (CCMR.OCxM) @ref LL_ADTMR_OCModeTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetMode(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_OC0M_Msk << (((Channel) % 4UL) * 8UL), 
            (((Mode) & TMR9_CCMR_OC0M_Val) << (TMR9_CCMR_OC0M_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the input prescaler of a given capture channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Prsc Prescaler value @ref LL_ADTMR_CapPrscTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_IC_SetPrescaler(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Prsc)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((Prsc) & TMR9_CCMR_CC0PE_Val) << (TMR9_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Enable the output preload of a given compare channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_OC_EnablePreload(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((0x1UL) & TMR9_CCMR_CC0PE_Val) << (TMR9_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Disable the output preload of a given compare channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_OC_DisablePreload(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((0x0UL) & TMR9_CCMR_CC0PE_Val) << (TMR9_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the active input 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Active Capture/compare direction @ref LL_ADTMR_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_IC_SetActiveInput(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Active)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC0S_Msk << (((Channel) % 4UL) * 8UL), 
            (((Active) & TMR9_CCMR_CC0S_Val) << (TMR9_CCMR_CC0S_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Get the active input 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return Capture/compare direction @ref LL_ADTMR_CmpCapMapTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_IC_GetActiveInput(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)(READ_BIT_SHIFT((ADTMRx)->CCMR, TMR9_CCMR_CC0S_Msk << (((Channel) % 4UL) * 8UL), 
            (TMR9_CCMR_CC0S_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the CC0 channel direction
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Dir Capture/compare direction @ref LL_ADTMR_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetCapCmpDirCC0(ADTMR_TypeDef *ADTMRx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC0S_Msk, (((Dir) & TMR9_CCMR_CC0S_Val) << TMR9_CCMR_CC0S_Pos));
}

/**
  * @brief  Set the CC1 channel direction
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Dir Capture/compare direction @ref LL_ADTMR_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetCapCmpDirCC1(ADTMR_TypeDef *ADTMRx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC1S_Msk, (((Dir) & TMR9_CCMR_CC1S_Val) << TMR9_CCMR_CC1S_Pos));
}

/**
  * @brief  Set the CC2 channel direction
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Dir Capture/compare direction @ref LL_ADTMR_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetCapCmpDirCC2(ADTMR_TypeDef *ADTMRx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC2S_Msk, (((Dir) & TMR9_CCMR_CC2S_Val) << TMR9_CCMR_CC2S_Pos));
}

/**
  * @brief  Set the CC3 channel direction
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Dir Capture/compare direction @ref LL_ADTMR_CmpCapMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetCapCmpDirCC3(ADTMR_TypeDef *ADTMRx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->CCMR, TMR9_CCMR_CC3S_Msk, (((Dir) & TMR9_CCMR_CC3S_Val) << TMR9_CCMR_CC3S_Pos));
}

/**
  * @brief  Set the output polarity of a given compare channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Pol Output Polarity @ref LL_ADTMR_CmpPolTypeDef
  * @param  IsOCN @ref LL_ADTMR_CapCmpOCTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetPolarity(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Pol, uint32_t IsOCN)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_CAP_CMP_OC(IsOCN));

    if (!IsOCN) {
        MODIFY_REG((ADTMRx)->CCER, (0x1UL << TMR9_CCER_CC0P_Pos) << (((Channel) % 4UL) * 4UL), 
                (((Pol) & 0x1UL) << (TMR9_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)));      
    } else {
        MODIFY_REG((ADTMRx)->CCER, (0x1UL << (TMR9_CCER_CC0P_Pos + 1UL)) << (((Channel) % 4UL) * 4UL), 
                (((Pol) & 0x1UL) << (((TMR9_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)) + 1UL)));
    }
}

/**
  * @brief  Set the input polarity of a given capture channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Pol Input Polarity @ref LL_ADTMR_CapPolTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_IC_SetPolarity(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CCER, TMR9_CCER_CC0P_Msk << (((Channel) % 4UL) * 4UL), 
            (((Pol) & 0x3UL) << (TMR9_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)));
}

/**
  * @brief  Get the input polarity of a given capture channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval Input Polarity @ref LL_ADTMR_CapPolTypeDef
  */
__STATIC_INLINE uint32_t LL_ADTMR_IC_GetPolarity(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM(IS_LL_ADTMR_CHANNEL(Channel));

    return (uint32_t)(READ_BIT_SHIFT((ADTMRx)->CCER, TMR9_CCER_CC0P_Msk << (((Channel) % 4UL) * 4UL), 
                                                    (TMR9_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)));
}

/**
  * @brief  Enable a given capture/compare channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_CC_EnableChannel(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CHANNEL(Channel)) && (Channel < 8UL));

    if (Channel <= LL_ADTMR_CAP_CMP_CH_3) {
        MODIFY_REG((ADTMRx)->CCER, TMR9_CCER_CC0E_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x1UL) & TMR9_CCER_CC0E_Val) << (TMR9_CCER_CC0E_Pos + ((Channel) % 4UL) * 4UL)));
    } else if (Channel <= LL_ADTMR_CAP_CMP_CH_3N){
        MODIFY_REG((ADTMRx)->CCER, TMR9_CCER_CC0NE_Msk << (((Channel - LL_ADTMR_CAP_CMP_CH_0N) % 4UL) * 4UL), 
                (((0x1UL) & TMR9_CCER_CC0NE_Val) << (TMR9_CCER_CC0NE_Pos + ((Channel) % 4UL) * 4UL)));
    }
}

/**
  * @brief  Disable a given capture/compare channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_CC_DisableChannel(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CHANNEL(Channel)) && (Channel < 8UL));

    if (Channel <= LL_ADTMR_CAP_CMP_CH_3) {
        MODIFY_REG((ADTMRx)->CCER, TMR9_CCER_CC0E_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x0UL) & TMR9_CCER_CC0E_Val) << (TMR9_CCER_CC0E_Pos + ((Channel) % 4UL) * 4UL)));
    } else if (Channel <= LL_ADTMR_CAP_CMP_CH_3N){
        MODIFY_REG((ADTMRx)->CCER, TMR9_CCER_CC0NE_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x0UL) & TMR9_CCER_CC0NE_Val) << (TMR9_CCER_CC0NE_Pos + ((Channel) % 4UL) * 4UL)));
    }
}

/**
  * @brief  Judge whether the all channel is disabled or not
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 A channel is enaabled
  * @retval 1 All channel is disabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_CC_IsAllChannelDisabled(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (uint32_t)((READ_BIT((ADTMRx)->CCER, LL_ADTMR_CCER_CMP_CAP_CHNL_MSK) == 0UL) ? 1UL : 0UL );
}

/**
  * @brief  Disable a given capture/compare channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_CC_DisableAllChannel(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->CCER, LL_ADTMR_CCER_CMP_CAP_CHNL_MSK );
}


/**
  * @brief  Set the CCx compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetChannelCompare(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    WRITE_REG(LL_ADTMR_REG_OFFSET((ADTMRx)->CC0R, (Channel % 4)), ((Val) & TMR9_CC0R_CC0V_Val));
}

/**
  * @brief  Get the CCx compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return CC0 compare value
  */
__STATIC_INLINE uint32_t LL_ADTMR_IC_GetChannelCompare(const ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return ((READ_REG(LL_ADTMR_REG_OFFSET((ADTMRx)->CC0R, (Channel % 4)))) & TMR9_CC0R_CC0V_Val);
}


/**
  * @brief  Set the CC0 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetCompareCH0(ADTMR_TypeDef *ADTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->CC0R, ((Val) & TMR9_CC0R_CC0V_Val));
}

/**
  * @brief  Get the CC0 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC0 compare value
  */
__STATIC_INLINE uint32_t LL_ADTMR_OC_GetCompareCH0(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC0R) & TMR9_CC0R_CC0V_Val);
}

/**
  * @brief  Read the CC0 capture value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC0 capture value
  */
__STATIC_INLINE uint32_t LL_ADTMR_IC_GetCaptureCH0(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC0R) & TMR9_CC0R_CC0V_Val);
}

/**
  * @brief  Set the CC1 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetCompareCH1(ADTMR_TypeDef *ADTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->CC1R, ((Val) & TMR9_CC1R_CC1V_Val));
}

/**
  * @brief  Get the CC1 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC1 compare value
  */
__STATIC_INLINE uint32_t LL_ADTMR_OC_GetCompareCH1(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC1R) & TMR9_CC1R_CC1V_Val);
}

/**
  * @brief  Read the CC1 capture value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC1 capture value
  */
__STATIC_INLINE uint32_t LL_ADTMR_IC_GetCaptureCH1(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC1R) & TMR9_CC1R_CC1V_Val);
}

/**
  * @brief  Set the CC2 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetCompareCH2(ADTMR_TypeDef *ADTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->CC2R, ((Val) & TMR9_CC2R_CC2V_Val));
}

/**
  * @brief  Get the CC2 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC2 compare value
  */
__STATIC_INLINE uint32_t LL_ADTMR_OC_GetCompareCH2(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC2R) & TMR9_CC2R_CC2V_Val);
}

/**
  * @brief  Read the CC2 capture value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC2 capture value
  */
__STATIC_INLINE uint32_t LL_ADTMR_IC_GetCaptureCH2(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC2R) & TMR9_CC2R_CC2V_Val);
}

/**
  * @brief  Set the CC3 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_OC_SetCompareCH3(ADTMR_TypeDef *ADTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->CC3R, ((Val) & TMR9_CC3R_CC3V_Val));
}

/**
  * @brief  Get the CC3 compare value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC3 compare value
  */
__STATIC_INLINE uint32_t LL_ADTMR_OC_GetCompareCH3(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC3R) & TMR9_CC3R_CC3V_Val);
}

/**
  * @brief  Read the CC3 capture value
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return CC3 capture value
  */
__STATIC_INLINE uint32_t LL_ADTMR_IC_GetCaptureCH3(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->CC3R) & TMR9_CC3R_CC3V_Val);
}

/**
  * @brief  Select the input source of a given capture channel.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @param  Src Input source  @ref LL_ADTMR_CapInputSrcTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_ADTMR_IC_SetInputSource(ADTMR_TypeDef *ADTMRx, uint32_t Channel, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((ADTMRx)->CIR, TMR9_CIR_C0TIS_Msk << (((Channel) % 4UL) * 8UL), 
            (((Src) & TMR9_CIR_C0TIS_Val) << (TMR9_CIR_C0TIS_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the master trigger output (TRGO) pulse width
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Width Output pulse width
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetTrigOutputWidth(ADTMR_TypeDef *ADTMRx, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->TTCR, TMR9_TTCR_TOW_Msk, (((Width) & TMR9_TTCR_TOW_Val) << TMR9_TTCR_TOW_Pos));
}

/**
  * @brief  Get the master trigger output pulse width
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Master trigger output pulse width
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetTrigOutputWidth(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->TTCR, TMR9_TTCR_TOW_Msk, TMR9_TTCR_TOW_Pos));
}

/**
  * @brief  Set the trigger cycles width (TTCR.TCW)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Width Output pulse width
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_SetTrigCyclesWidth(ADTMR_TypeDef *ADTMRx, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    MODIFY_REG((ADTMRx)->TTCR, TMR9_TTCR_TCW_Msk, (((Width) & TMR9_TTCR_TCW_Val) << TMR9_TTCR_TCW_Pos));
}

/**
  * @brief  Get the trigger cycles width (TTCR.TCW)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Trigger cycles width (TTCR.TCW)
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetTrigCyclesWidth(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->TTCR, TMR9_TTCR_TCW_Msk, TMR9_TTCR_TCW_Pos));
}

/**
  * @brief  Enable the CH0 trigger output (TTCR.TC0E)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableTriggerCH0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC0E_Msk);
}

/**
  * @brief  Disable the CH0 trigger output
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableTriggerCH0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC0E_Msk);
}

/**
  * @brief  Enable the CH1 trigger output (TTCR.TC1E)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableTriggerCH1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC1E_Msk);
}

/**
  * @brief  Disable the CH1 trigger output
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableTriggerCH1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC1E_Msk);
}

/**
  * @brief  Enable the CH2 trigger output (TTCR.TC2E)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableTriggerCH2(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC2E_Msk);
}

/**
  * @brief  Disable the CH2 trigger output
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableTriggerCH2(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC2E_Msk);
}

/**
  * @brief  Enable the CH3 trigger output (TTCR.TC3E)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableTriggerCH3(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC3E_Msk);
}

/**
  * @brief  Disable the CH3 trigger output
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableTriggerCH3(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC3E_Msk);
}

/**
  * @brief  Enable a channel trigger output
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableChannelTrigger(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    SET_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC0E_Msk << ((Channel % 4UL) * 1UL));
}

/**
  * @brief  Disable a channel trigger output
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableChannelTrigger(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    CLEAR_BIT((ADTMRx)->TTCR, TMR9_TTCR_TC0E_Msk << ((Channel % 4UL) * 1UL));
}


/**
  * @}
  */

/** @defgroup ADTMR_LL_EF_IT_Management LL ADTMR Interrupt Management
  * @brief    LL ADTMR Interrupt Management
  * @details    Per-channel capture/compare and over-capture interrupts.
  * @{
  */

/**
  * @brief  Enable the update interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_UPDATE(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_UIE_Msk);
}

/**
  * @brief  Disable the update interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_UPDATE(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_UIE_Msk);
}

/**
  * @brief  Enable the counter overflow interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_OVIE_Msk);
}

/**
  * @brief  Disable the counter overflow interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_OVIE_Msk);
}

/**
  * @brief  Judge whether the counter overflow interrupt is enabled or not
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Counter overflow interrupt is disabled
  * @retval 1 Counter overflow interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_OVIE_Msk, TMR9_IER_OVIE_Pos));
}

/**
  * @brief  Judge whether the update event interrupt is enabled or not
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Update event interrupt is disabled
  * @retval 1 Update event interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_UPDATE(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_UIE_Msk, TMR9_IER_UIE_Pos));
}

/**
  * @brief  Enable the trigger interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_TRIG(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_TIE_Msk);
}

/**
  * @brief  Disable the trigger interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_TRIG(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_TIE_Msk);
}

/**
  * @brief  Judge whether the trigger interrupt is enabled or not
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Trigger interrupt is disabled
  * @retval 1 Trigger interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_TRIG(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_TIE_Msk, TMR9_IER_TIE_Pos));
}

/**
  * @brief  Enable the break interrupt (both break inputs and system break)
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_BRK(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_BIE_Msk);
}

/**
  * @brief  Disable the break interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_BRK(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_BIE_Msk);
}

/**
  * @brief  Judge whether the break interrupt is enabled or not
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Break interrupt is disabled
  * @retval 1 Break interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_BRK(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_BIE_Msk, TMR9_IER_BIE_Pos));
}

/**
  * @brief  Get the whole interrupt enable register
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Whole interrupt enable register
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetAllIntEn(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->IER));
}

/**
  * @brief  Judge whether the counter overflow flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Counter overflow flag is cleared
  * @retval 1 Counter overflow flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_OVIF_Msk, TMR9_SR_OVIF_Pos));
}

/**
  * @brief  Clear the counter overflow flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_OVIF_Msk);
}

/**
  * @brief  Judge whether the update event flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Update event flag is cleared
  * @retval 1 Update event flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_UPDATE(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_UIF_Msk, TMR9_SR_UIF_Pos));
}

/**
  * @brief  Clear the update event flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_UPDATE(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_UIF_Msk);
}

/**
  * @brief  Judge whether the trigger flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Trigger flag is cleared
  * @retval 1 Trigger flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_TRIG(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_TIF_Msk, TMR9_SR_TIF_Pos));
}

/**
  * @brief  Clear the trigger flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_TRIG(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_TIF_Msk);
}

/**
  * @brief  Judge whether the break 0 flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Break 0 flag is cleared
  * @retval 1 Break 0 flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_BRK0(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_B0IF_Msk, TMR9_SR_B0IF_Pos));
}

/**
  * @brief  Clear the break 0 flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_BRK0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_B0IF_Msk);
}

/**
  * @brief  Judge whether the break 1 flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 Break 1 flag is cleared
  * @retval 1 Break 1 flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_BRK1(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_B1IF_Msk, TMR9_SR_B1IF_Pos));
}

/**
  * @brief  Clear the break 1 flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_BRK1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_B1IF_Msk);
}

/**
  * @brief  Judge whether the system fault break flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 System fault break flag is cleared
  * @retval 1 System fault break flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_SYSBRK(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_SBIF_Msk, TMR9_SR_SBIF_Pos));
}

/**
  * @brief  Clear the system fault break flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_SYSBRK(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_SBIF_Msk);
}

/**
  * @brief  Get the whole status register
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Whole status register
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetAllFlag(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_REG((ADTMRx)->SR));
}

/**
  * @brief  Enable the CCx capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CxMIE(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C0MIE_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Disable the CCx capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CxMIE(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C0MIE_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Judge whether the CCx capture/compare interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval 0 CCx capture/compare interrupt is disabled
  * @retval 1 CCx capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CxMIE(const ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)((READ_BIT((ADTMRx)->IER, TMR9_IER_C0MIE_Msk << ((Channel % 4UL) * 2UL))) ? 1UL : 0UL);
}

/**
  * @brief  Judge whether the CCx over-capture interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval 0 CCx over-capture interrupt is disabled
  * @retval 1 CCx over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CxOIE(const ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)((READ_BIT((ADTMRx)->IER, TMR9_IER_C0OIE_Msk << ((Channel % 4UL) * 2UL))) ? 1UL : 0UL);
}

/**
  * @brief  Enable the CC0 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C0MIE_Msk);
}

/**
  * @brief  Disable the CC0 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C0MIE_Msk);
}

/**
  * @brief  Judge whether the CC0 capture/compare interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC0 capture/compare interrupt is disabled
  * @retval 1 CC0 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC0(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C0MIE_Msk, TMR9_IER_C0MIE_Pos));
}

/**
  * @brief  Enable the CC0 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC0OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C0OIE_Msk);
}

/**
  * @brief  Disable the CC0 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC0OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C0OIE_Msk);
}

/**
  * @brief  Judge whether the CC0 over-capture interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC0 over-capture interrupt is disabled
  * @retval 1 CC0 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC0OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C0OIE_Msk, TMR9_IER_C0OIE_Pos));
}

/**
  * @brief  Enable the CC1 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C1MIE_Msk);
}

/**
  * @brief  Disable the CC1 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C1MIE_Msk);
}

/**
  * @brief  Judge whether the CC1 capture/compare interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC1 capture/compare interrupt is disabled
  * @retval 1 CC1 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC1(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C1MIE_Msk, TMR9_IER_C1MIE_Pos));
}

/**
  * @brief  Enable the CC1 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC1OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C1OIE_Msk);
}

/**
  * @brief  Disable the CC1 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC1OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C1OIE_Msk);
}

/**
  * @brief  Judge whether the CC1 over-capture interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC1 over-capture interrupt is disabled
  * @retval 1 CC1 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC1OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C1OIE_Msk, TMR9_IER_C1OIE_Pos));
}

/**
  * @brief  Enable the CC2 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC2(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C2MIE_Msk);
}

/**
  * @brief  Disable the CC2 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC2(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C2MIE_Msk);
}

/**
  * @brief  Judge whether the CC2 capture/compare interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC2 capture/compare interrupt is disabled
  * @retval 1 CC2 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC2(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C2MIE_Msk, TMR9_IER_C2MIE_Pos));
}

/**
  * @brief  Enable the CC2 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC2OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C2OIE_Msk);
}

/**
  * @brief  Disable the CC2 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC2OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C2OIE_Msk);
}

/**
  * @brief  Judge whether the CC2 over-capture interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC2 over-capture interrupt is disabled
  * @retval 1 CC2 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC2OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C2OIE_Msk, TMR9_IER_C2OIE_Pos));
}

/**
  * @brief  Enable the CC3 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC3(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C3MIE_Msk);
}

/**
  * @brief  Disable the CC3 capture/compare interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC3(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C3MIE_Msk);
}

/**
  * @brief  Judge whether the CC3 capture/compare interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC3 capture/compare interrupt is disabled
  * @retval 1 CC3 capture/compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC3(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C3MIE_Msk, TMR9_IER_C3MIE_Pos));
}

/**
  * @brief  Enable the CC3 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT_CC3OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT((ADTMRx)->IER, TMR9_IER_C3OIE_Msk);
}

/**
  * @brief  Disable the CC3 over-capture interrupt
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT_CC3OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT((ADTMRx)->IER, TMR9_IER_C3OIE_Msk);
}

/**
  * @brief  Judge whether the CC3 over-capture interrupt is enabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC3 over-capture interrupt is disabled
  * @retval 1 CC3 over-capture interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT_CC3OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->IER, TMR9_IER_C3OIE_Msk, TMR9_IER_C3OIE_Pos));
}

/**
  * @brief  Judge whether the CCx capture/compare flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CCx capture/compare flag is cleared
  * @retval 1 CCx capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CCxMIF(const ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    return (uint32_t)((READ_BIT((ADTMRx)->SR, (TMR9_SR_CC0MIF_Msk << ((Channel % 4UL) * 2UL)))) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CCx capture/compare flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CCxMIF(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC0MIF_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Judge whether the CCx over-capture flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @retval 0 CCx over-capture flag is cleared
  * @retval 1 CCx over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CCxOIF(const ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (uint32_t)((READ_BIT((ADTMRx)->SR, (TMR9_SR_CC0OIF_Msk << ((Channel % 4UL) * 2UL)))) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CCx over-capture flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_ADTMR_CapCmpChTypeDef (LL_ADTMR_CAP_CMP_CH_x)
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CCxOIF(ADTMR_TypeDef *ADTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_INLINE_PARAM((IS_LL_ADTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC0OIF_Msk << ((Channel % 4UL) * 2UL));
}

/**
  * @brief  Judge whether the CC0 capture/compare flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC0 capture/compare flag is cleared
  * @retval 1 CC0 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC0(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC0MIF_Msk, TMR9_SR_CC0MIF_Pos));
}

/**
  * @brief  Clear the CC0 capture/compare flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC0(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC0MIF_Msk);
}

/**
  * @brief  Judge whether the CC0 over-capture flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC0 over-capture flag is cleared
  * @retval 1 CC0 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC0OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC0OIF_Msk, TMR9_SR_CC0OIF_Pos));
}

/**
  * @brief  Clear the CC0 over-capture flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC0OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC0OIF_Msk);
}

/**
  * @brief  Judge whether the CC1 capture/compare flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC1 capture/compare flag is cleared
  * @retval 1 CC1 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC1(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC1MIF_Msk, TMR9_SR_CC1MIF_Pos));
}

/**
  * @brief  Clear the CC1 capture/compare flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC1(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC1MIF_Msk);
}

/**
  * @brief  Judge whether the CC1 over-capture flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC1 over-capture flag is cleared
  * @retval 1 CC1 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC1OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC1OIF_Msk, TMR9_SR_CC1OIF_Pos));
}

/**
  * @brief  Clear the CC1 over-capture flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC1OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC1OIF_Msk);
}

/**
  * @brief  Judge whether the CC2 capture/compare flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC2 capture/compare flag is cleared
  * @retval 1 CC2 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC2(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC2MIF_Msk, TMR9_SR_CC2MIF_Pos));
}

/**
  * @brief  Clear the CC2 capture/compare flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC2(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC2MIF_Msk);
}

/**
  * @brief  Judge whether the CC2 over-capture flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC2 over-capture flag is cleared
  * @retval 1 CC2 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC2OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC2OIF_Msk, TMR9_SR_CC2OIF_Pos));
}

/**
  * @brief  Clear the CC2 over-capture flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC2OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC2OIF_Msk);
}

/**
  * @brief  Judge whether the CC3 capture/compare flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC3 capture/compare flag is cleared
  * @retval 1 CC3 capture/compare flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC3(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC3MIF_Msk, TMR9_SR_CC3MIF_Pos));
}

/**
  * @brief  Clear the CC3 capture/compare flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC3(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC3MIF_Msk);
}

/**
  * @brief  Judge whether the CC3 over-capture flag is set
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval 0 CC3 over-capture flag is cleared
  * @retval 1 CC3 over-capture flag is set
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag_CC3OVR(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT_SHIFT((ADTMRx)->SR, TMR9_SR_CC3OIF_Msk, TMR9_SR_CC3OIF_Pos));
}

/**
  * @brief  Clear the CC3 over-capture flag
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag_CC3OVR(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG((ADTMRx)->SR, TMR9_SR_CC3OIF_Msk);
}

/**
  * @brief  ADTMR Interrupt enable
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mask Mask to enable @ref LL_ADTMR_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_EnableIT(ADTMR_TypeDef *ADTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    SET_BIT(ADTMRx->IER, Mask);
}

/**
  * @brief  ADTMR Interrupt disable
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mask Mask to disable @ref LL_ADTMR_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_DisableIT(ADTMR_TypeDef *ADTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    CLEAR_BIT(ADTMRx->IER, Mask);
}

/**
  * @brief  Check if ADTMR Interrupt is enabled or disabled
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mask Mask to check @ref LL_ADTMR_IER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsEnabledIT(const ADTMR_TypeDef *ADTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADTMRx->IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mask Mask to clear @ref LL_ADTMR_SR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADTMR_ClearFlag(ADTMR_TypeDef *ADTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    WRITE_REG(ADTMRx->SR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  ADTMRx Specifies ADTMR peripheral
  * @param  Mask Mask to check @ref LL_ADTMR_SR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADTMR_IsActiveFlag(const ADTMR_TypeDef *ADTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(ADTMRx->SR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  ADTMR Interrupt All Enable Get
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Interrupt Enable Bit
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetAllEnabledIT(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT(ADTMRx->IER, LL_ADTMR_IER_IT_EN_MSK));
}

/**
  * @brief  Get interrupt status of the specified ADTMR channel 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @return Interrupt status
  */
__STATIC_INLINE uint32_t LL_ADTMR_GetAllITPending(const ADTMR_TypeDef *ADTMRx)
{
    ASSERT_INLINE_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    return (READ_BIT(ADTMRx->SR, LL_ADTMR_SR_IT_FLAG_MSK));
}


/**
  * @}
  */ /* ADTMR_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* ADTMR_LL_Exported_Functions */

#endif /* ADTMR */

/**
  * @}
  */ /* ADTMR_LL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_ADTMR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/









