/**
  ******************************************************************************
  * @file    tae32g58xx_ll_lptmr.h
  * @author  Tai-Action SD Team
  * @brief   Header file for LPTMR (Low Power Timer) LL module
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
#ifndef _TAE32G58XX_LL_LPTMR_H_
#define _TAE32G58XX_LL_LPTMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(TMR6)

/** @defgroup LPTMR_LL LPTMR LL
  * @brief    LPTMR LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup LPTMR_LL_Exported_Constants LPTMR LL Exported Constants
  * @brief    LPTMR LL Exported Constants
  * @{
  */

/** @name LL_LPTMR_IER_ITEnMskTypeDef
  * @brief LPTMR LL Interrupt Enable Masks
  * @{
  */
#define LL_LPTMR_IER_ITEnMskTypeDef     uint32_t

#define LL_LPTMR_IER_TIE                (TMR6_IER_TIE_Msk)      /*!< Trigger interrupt enable             */
#define LL_LPTMR_IER_UIE                (TMR6_IER_UIE_Msk)      /*!< Update interrupt enable              */
#define LL_LPTMR_IER_CIE                (TMR6_IER_CIE_Msk)      /*!< CH0 output compare interrupt enable  */

#define LL_LPTMR_IER_IT_EN_MSK          ((TMR6_IER_TIE_Msk                | TMR6_IER_UIE_Msk                | \
                                          TMR6_IER_CIE_Msk))

#define LL_LPTMR_IER_CC_IT_EN_MSK       ((TMR6_IER_CIE_Msk))
/**
  * @}
  */

/** @name LL_LPTMR_SR_ITPendingMskTypeDef
  * @brief LPTMR LL Status Flag Masks
  * @{
  */
#define LL_LPTMR_SR_ITPendingMskTypeDef uint32_t


#define LL_LPTMR_SR_TIF                 (TMR6_SR_TIF_Msk)       /*!< Trigger flag                    */
#define LL_LPTMR_SR_UIF                 (TMR6_SR_UIF_Msk)       /*!< Update flag                     */
#define LL_LPTMR_SR_CIF                 (TMR6_SR_CIF_Msk)       /*!< CH0 output compare flag         */


#define LL_LPTMR_SR_IT_FLAG_MSK         ((TMR6_SR_TIF_Msk                 | TMR6_SR_UIF_Msk                 | \
                                          TMR6_SR_CIF_Msk                 ))

#define LL_LPTMR_SR_CC_IT_FLAG_MSK      ((TMR6_SR_CIF_Msk))


#define LL_LPTMR_SR_UPD_IT_FLAG_MSK     ((TMR6_SR_UIF_Msk))
/** @} */

#if LL_LPTMR_IER_IT_EN_MSK != LL_LPTMR_SR_IT_FLAG_MSK
#error "LL_LPTMR_SR_IT_FLAG_MSK"
#endif


#define LL_LPTMR_CCER_CMP_CAP_CHNL_MSK  ((TMR6_CCER_CCE_Msk))



/** @name LL_LPTMR_WorkModeTypeDef
  * @brief LPTMR LL Work Mode (CR.OPM)
  * @{
  */
#define LL_LPTMR_WorkModeTypeDef        LL_RSV_DATA_TYPE

#define LL_LPTMR_WORK_MODE_CONTINUE     (0UL)   /*!< Continue mode */
#define LL_LPTMR_WORK_MODE_SINGLE       (1UL)   /*!< Single mode   */

#define IS_LL_LPTMR_WORK_MODE(__VAL__)              (((__VAL__) == LL_LPTMR_WORK_MODE_CONTINUE) || \
                                                     ((__VAL__) == LL_LPTMR_WORK_MODE_SINGLE))
/** @} */

/** @name LL_LPTMR_OutputIdleStaTypeDef
  * @brief LPTMR LL Output Idle State
  * @{
  */
#define LL_LPTMR_OutputIdleStaTypeDef               LL_RSV_DATA_TYPE    

#define LL_LPTMR_OUTPUT_IDLE_STA_LOW                (0UL)                /*!< Output Idle State Low                            */
#define LL_LPTMR_OUTPUT_IDLE_STA_HIGH               (1UL)                /*!< Output Idle State High                           */

#define IS_LL_LPTMR_OUTPUT_IDLE_STA(__VAL__)        (((__VAL__) == LL_LPTMR_OUTPUT_IDLE_STA_LOW)  || \
                                                     ((__VAL__) == LL_LPTMR_OUTPUT_IDLE_STA_HIGH) )
/** @} */

/** @name LL_LPTMR_ETRModeTypeDef
  * @brief LPTMR LL ETR Mode (SCR.EE)
  * @{
  */
#define LL_LPTMR_ETRModeTypeDef         LL_RSV_DATA_TYPE

#define LL_LPTMR_ETR_MODE_INT_CLK     (0UL)   /*!< Internal clock mode */
#define LL_LPTMR_ETR_MODE_EXT_CLK     (1UL)   /*!< External clock mode */

#define IS_LL_LPTMR_ETR_MODE(__VAL__)               (((__VAL__) == LL_LPTMR_ETR_MODE_INT_CLK) || \
                                                     ((__VAL__) == LL_LPTMR_ETR_MODE_EXT_CLK))
/** @} */

/** @name LL_LPTMR_ETRFilTypeDef
  * @brief LPTMR LL ETR Filter
  * @{
  */
#define LL_LPTMR_ETRFilTypeDef              LL_RSV_DATA_TYPE

#define LL_LPTMR_ETR_FILTER_NONE            (0UL)
#define LL_LPTMR_ETR_FILTER_TDS_X1          (1UL)
#define LL_LPTMR_ETR_FILTER_TDS_X2          (2UL)
#define LL_LPTMR_ETR_FILTER_TDS_X3          (3UL)
#define LL_LPTMR_ETR_FILTER_TDS_X4          (4UL)
#define LL_LPTMR_ETR_FILTER_TDS_X5          (5UL)
#define LL_LPTMR_ETR_FILTER_TDS_X6          (6UL)
#define LL_LPTMR_ETR_FILTER_TDS_X7          (7UL)
#define LL_LPTMR_ETR_FILTER_TDS_X8          (8UL)
#define LL_LPTMR_ETR_FILTER_TDS_X9          (9UL)
#define LL_LPTMR_ETR_FILTER_TDS_X10         (10UL)
#define LL_LPTMR_ETR_FILTER_TDS_X11         (11UL)
#define LL_LPTMR_ETR_FILTER_TDS_X12         (12UL)
#define LL_LPTMR_ETR_FILTER_TDS_X13         (13UL)
#define LL_LPTMR_ETR_FILTER_TDS_X14         (14UL)
#define LL_LPTMR_ETR_FILTER_TDS_X15         (15UL)

#define IS_LL_LPTMR_ETR_FILTER(__VAL__)     (((__VAL__) >= LL_LPTMR_ETR_FILTER_NONE) && \
                                             ((__VAL__) <= LL_LPTMR_ETR_FILTER_TDS_X15))
/** @} */


/** @name LL_LPTMR_ETREdgeTypeDef
  * @brief LPTMR LL ETR Edge Mode (SCR.EMS)
  * @{
  */
#define LL_LPTMR_ETREdgeTypeDef                 LL_RSV_DATA_TYPE


#define LL_LPTMR_ETR_EDGE_MODE_CLOSE            (0UL)   /*!< Trigger closed                */
#define LL_LPTMR_ETR_EDGE_MODE_RISING           (1UL)   /*!< Rising edge                   */
#define LL_LPTMR_ETR_EDGE_MODE_FALLING          (2UL)   /*!< Falling edge                  */
#define LL_LPTMR_ETR_EDGE_MODE_RISING_FALLING   (3UL)   /*!< Both rising and falling edges */

#define IS_LL_LPTMR_ETR_EDGE_MODE(__VAL__)          (((__VAL__) == LL_LPTMR_ETR_EDGE_MODE_CLOSE) || \
                                                     ((__VAL__) == LL_LPTMR_ETR_EDGE_MODE_RISING) || \
                                                     ((__VAL__) == LL_LPTMR_ETR_EDGE_MODE_FALLING) || \
                                                     ((__VAL__) == LL_LPTMR_ETR_EDGE_MODE_RISING_FALLING))
/** @} */

/** @name LL_LPTMR_TrigTypeDef
  * @brief LPTMR LL Trigger Selection (SCR.TS)
  * @{
  */
#define LL_LPTMR_TrigTypeDef            LL_RSV_DATA_TYPE

/* Generic internal trigger sources */
#define LL_LPTMR_TRIG_ITR0              (0UL)   /*!< Internal trigger ITR0  */
#define LL_LPTMR_TRIG_ITR1              (1UL)   /*!< Internal trigger ITR1  */
#define LL_LPTMR_TRIG_ITR2              (2UL)   /*!< Internal trigger ITR2  */
#define LL_LPTMR_TRIG_ITR3              (3UL)   /*!< Internal trigger ITR3  */
#define LL_LPTMR_TRIG_ITR4              (4UL)   /*!< Internal trigger ITR4  */
#define LL_LPTMR_TRIG_ITR5              (5UL)   /*!< Internal trigger ITR5  */
#define LL_LPTMR_TRIG_ITR6              (6UL)   /*!< Internal trigger ITR6  */
#define LL_LPTMR_TRIG_ITR7              (7UL)   /*!< Internal trigger ITR7  */
#define LL_LPTMR_TRIG_ITR8              (8UL)   /*!< Internal trigger ITR8  */
#define LL_LPTMR_TRIG_ITR9              (9UL)   /*!< Internal trigger ITR9  */
#define LL_LPTMR_TRIG_ITR10             (10UL)  /*!< Internal trigger ITR10 */
#define LL_LPTMR_TRIG_ITR11             (11UL)  /*!< Internal trigger ITR11 */
#define LL_LPTMR_TRIG_ITR12             (12UL)  /*!< Internal trigger ITR12 */
#define LL_LPTMR_TRIG_ITR13             (13UL)  /*!< Internal trigger ITR13 */
#define LL_LPTMR_TRIG_ITR14             (14UL)  /*!< Internal trigger ITR14 */
#define LL_LPTMR_TRIG_ITR15             (15UL)  /*!< Internal trigger ITR15 */

#define LL_LPTMR_TRIG_ETR_FE            (21UL)  /*!< ETR rising edge        */
#define LL_LPTMR_TRIG_ETR_F             (22UL)  /*!< ETR falling edge       */

/* Per-instance trigger mapping: TMR6 */
#define LL_LPTMR_TRIG_TMR6_ITR0_TMR6_CH0            (LL_LPTMR_TRIG_ITR0)    /*!< TMR6 ITR0: TMR6_CH0      */
#define LL_LPTMR_TRIG_TMR6_ITR1_CMP0_OUT            (LL_LPTMR_TRIG_ITR1)    /*!< TMR6 ITR1: CMP0_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR2_CMP1_OUT            (LL_LPTMR_TRIG_ITR2)    /*!< TMR6 ITR2: CMP1_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR3_CMP2_OUT            (LL_LPTMR_TRIG_ITR3)    /*!< TMR6 ITR3: CMP2_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR4_CMP3_OUT            (LL_LPTMR_TRIG_ITR4)    /*!< TMR6 ITR4: CMP3_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR5_CMP4_OUT            (LL_LPTMR_TRIG_ITR5)    /*!< TMR6 ITR5: CMP4_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR6_CMP5_OUT            (LL_LPTMR_TRIG_ITR6)    /*!< TMR6 ITR6: CMP5_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR7_CMP6_OUT            (LL_LPTMR_TRIG_ITR7)    /*!< TMR6 ITR7: CMP6_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR8_CMP7_OUT            (LL_LPTMR_TRIG_ITR8)    /*!< TMR6 ITR8: CMP7_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR9_CMP8_OUT            (LL_LPTMR_TRIG_ITR9)    /*!< TMR6 ITR9: CMP8_OUT      */
#define LL_LPTMR_TRIG_TMR6_ITR10                    //RESERVED
#define LL_LPTMR_TRIG_TMR6_ITR11_LVDBRK             (LL_LPTMR_TRIG_ITR11)   /*!< TMR6 ITR11: LVDBRK       */
#define LL_LPTMR_TRIG_TMR6_ITR12_PLLFLT             (LL_LPTMR_TRIG_ITR12)   /*!< TMR6 ITR12: PLLFLT       */
#define LL_LPTMR_TRIG_TMR6_ITR13_OSCFLT             (LL_LPTMR_TRIG_ITR13)   /*!< TMR6 ITR13: OSCFLT       */
#define LL_LPTMR_TRIG_TMR6_ITR14_FLSFLT             (LL_LPTMR_TRIG_ITR14)   /*!< TMR6 ITR14: FLSFLT       */
#define LL_LPTMR_TRIG_TMR6_ITR15_HRPWM_SYNCO        (LL_LPTMR_TRIG_ITR15)   /*!< TMR6 ITR15: HRPWM_SYNCO  */
/** @} */


/** @name LL_LPTMR_CapCmpChTypeDef
  * @brief LPTMR LL Capture/Compare Channel (4 channels)
  * @{
  */
#define LL_LPTMR_CapCmpChTypeDef            uint32_t
#define LL_LPTMR_CAP_CMP_CH_0               (0UL)   /*!< Capture/Compare channel 0 */

#define IS_LL_LPTMR_CHANNEL(__VAL__)        (((__VAL__) == LL_LPTMR_CAP_CMP_CH_0))

#define LL_LPTMR_CAP_CMP_CH_NUMS            (1UL)
#define LL_LPTMR_CAP_CMP_CHN_NUMS           (0UL)
#define LL_LPTMR_CAP_CMP_ALL_CH_NUMS        (LL_LPTMR_CAP_CMP_CH_NUMS + LL_LPTMR_CAP_CMP_CHN_NUMS)

#define IS_LL_LPTMR_CAP_CMP_CH(__VAL__)     (((__VAL__) == LL_LPTMR_CAP_CMP_CH_0))
#define IS_LL_LPTMR_CAP_CMP_CHN(__VAL__)    (0UL)

#if LL_LPTMR_CAP_CMP_CH_NUMS > 4UL
#error "LL_LPTMR_CAP_CMP_CH_NUMS"
#endif
/** @} */


/** @name LL_LPTMR_CmpPolTypeDef
  * @brief LPTMR LL Compare Output Polarity
  * @{
  */
#define LL_LPTMR_CmpPolTypeDef              LL_RSV_DATA_TYPE

#define LL_LPTMR_CMP_POL_HIGH               (0UL)   /*!< Compare output active high */
#define LL_LPTMR_CMP_POL_LOW                (1UL)   /*!< Compare output active low  */

#define IS_LL_LPTMR_CMP_POL(__VAL__)        (((__VAL__) == LL_LPTMR_CMP_POL_HIGH) || \
                                             ((__VAL__) == LL_LPTMR_CMP_POL_LOW))
/** @} */


/** @name LL_LPTMR_CmpEnTypeDef
  * @brief LPTMR LL Compare Output Polarity
  * @{
  */
#define LL_LPTMR_CmpEnTypeDef               LL_RSV_DATA_TYPE

#define LL_LPTMR_CMP_OUTPUT_OFF             (0UL)   /*!< Compare output off  */
#define LL_LPTMR_CMP_OUTPUT_ON              (1UL)   /*!< Compare output on   */

#define IS_LL_LPTMR_CMP_OUTPUT(__VAL__)     (((__VAL__) == LL_LPTMR_CMP_OUTPUT_OFF) || \
                                             ((__VAL__) == LL_LPTMR_CMP_OUTPUT_ON))
/** @} */

/** @name LL_LPTMR_SlvModeTypeDef
  * @brief LPTMR LL Slave Mode
  * @{
  */
#define LL_LPTMR_SlvModeTypeDef             LL_RSV_DATA_TYPE

#define LL_LPTMR_SLV_MODE_DIS               (0UL)   /*!< Slave mode disabled      */
#define LL_LPTMR_SLV_MODE_RST               (4UL)   /*!< Reset mode               */
#define LL_LPTMR_SLV_MODE_GATING            (5UL)   /*!< Gated mode               */
#define LL_LPTMR_SLV_MODE_TRIG              (6UL)   /*!< Trigger mode             */
#define LL_LPTMR_SLV_MODE_EXTCLK            (7UL)   /*!< External clock mode 1    */
#define LL_LPTMR_SLV_MODE_RST_TRIG          (8UL)   /*!< Combined reset + trigger */
#define LL_LPTMR_SLV_MODE_RST_GATING        (9UL)   /*!< Combined reset + gated   */

#define IS_LL_LPTMR_SLV_MODE(__VAL__)       (((__VAL__) == LL_LPTMR_SLV_MODE_DIS)       || \
                                             ((__VAL__) == LL_LPTMR_SLV_MODE_RST)       || \
                                             ((__VAL__) == LL_LPTMR_SLV_MODE_GATING)    || \
                                             ((__VAL__) == LL_LPTMR_SLV_MODE_TRIG)      || \
                                             ((__VAL__) == LL_LPTMR_SLV_MODE_EXTCLK)    || \
                                             ((__VAL__) == LL_LPTMR_SLV_MODE_RST_TRIG)  || \
                                             ((__VAL__) == LL_LPTMR_SLV_MODE_RST_GATING))
/** @} */

/** @name LL_LPTMR_EvtGenMaskTypeDef
  * @brief LPTMR LL Timer Event Generation Mask
  * @{
  */
#define LL_LPTMR_EvtGenMaskTypeDef                uint32_t    

#define LL_LPTMR_EVT_GEN_UPDATE                   (TMR6_UGR_UG_Msk)         /*!< Timer Event Generation Update                    */
#define LL_LPTMR_EVT_GEN_TRIGGER                  (TMR6_UGR_TG_Msk)         /*!< Timer Event Generation Trigger                   */
#define LL_LPTMR_EVT_GEN_COMPARE_UPDATE           (TMR6_UGR_CG_Msk)         /*!< Timer Event Generation Compare Update            */
#define LL_LPTMR_EVT_GEN_COUNTER_START            (TMR6_UGR_SG_Msk)         /*!< Timer Event Generation Counter Start             */

#define LL_LPTMR_EVT_GEN_ALL_MSK                  ((TMR6_UGR_SG_Msk                 | TMR6_UGR_CG_Msk                | \
                                                    TMR6_UGR_TG_Msk                 | TMR6_UGR_UG_Msk                 ))
/** @} */


/**
  * @}
  */ /* LPTMR_LL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup LPTMR_LL_Exported_Macros LPTMR LL Exported Macros
  * @brief    LPTMR LL Exported Macros
  * @{
  */

/**
  * @brief  LPTMR 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define LL_LPTMR_REG_OFFSET(__REG__, offset)            \
        (*((volatile uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))
/**
  * @}
  */ /* LPTMR_LL_Exported_Macros */

/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup LPTMR_LL_Exported_Functions LPTMR LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_LPTMR_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_LPTMR_ASSERT_INLINE_PARAM == 1)
extern void LL_LPTMR_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_LPTMR_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_LPTMR_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_LPTMR_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup LPTMR_LL_EF_Configuration LL LPTMR Configuration
  * @brief    LL LPTMR Configuration
  * @{
  */

/**
  * @brief  Enable the counter
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_EnableCounter(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->CR, TMR6_CR_CEN_Msk);
}

/**
  * @brief  Disable the counter
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_DisableCounter(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    CLEAR_BIT((LPTMRx)->CR, TMR6_CR_CEN_Msk);
}

/**
  * @brief  Judge whether the counter is enabled or not (CR.CEN)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 Counter is disabled
  * @retval 1 Counter is enabled
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsEnabledCounter(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->CR, TMR6_CR_CEN_Msk, TMR6_CR_CEN_Pos));
}

/**
  * @brief  Set the counter value (16 bits)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetCounter(LPTMR_TypeDef *LPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->CNTR, ((Val) & TMR6_CNTR_CNT_Val));
}

/**
  * @brief  Get the counter value (16 bits)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Counter value (16 bits)
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetCounter(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_REG((LPTMRx)->CNTR) & TMR6_CNTR_CNT_Val);
}

/**
  * @brief  Set the counter period (auto-reload value, 16 bits)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Period Counter period value
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetAutoReload(LPTMR_TypeDef *LPTMRx, uint32_t Period)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->CPR, ((Period) & TMR6_CPR_CPV_Val));
}

/**
  * @brief  Get the counter period (16 bits)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Counter period (16 bits)
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetAutoReload(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_REG((LPTMRx)->CPR) & TMR6_CPR_CPV_Val);
}

/**
  * @brief  Set the prescaler division value (16 bits)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetPrescaler(LPTMR_TypeDef *LPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->PSCR, ((Val) & TMR6_PSCR_PSC_Val));
}

/**
  * @brief  Get the prescaler division value (16 bits)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Prescaler division value (16 bits)
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetPrescaler(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_REG((LPTMRx)->PSCR) & TMR6_PSCR_PSC_Val);
}

/**
  * @brief  Enable the auto-preload
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_EnableAutoReload(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->CR, TMR6_CR_ARE_Msk);
}

/**
  * @brief  Disable the auto-preload
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_DisableAutoReload(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    CLEAR_BIT((LPTMRx)->CR, TMR6_CR_ARE_Msk);
}

/**
  * @brief  Judge whether the auto-preload is enabled or not
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 Auto-preload is disabled
  * @retval 1 Auto-preload is enabled
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsAutoReloadEnabled(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->CR, TMR6_CR_ARE_Msk, TMR6_CR_ARE_Pos));
}

/**
  * @brief  Set the counter work mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mode Mode to be set @ref LL_LPTMR_WorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetOnePulseMode(LPTMR_TypeDef *LPTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_LPTMR_WORK_MODE(Mode));

    MODIFY_REG((LPTMRx)->CR, TMR6_CR_OPM_Msk, (((Mode) & TMR6_CR_OPM_Val) << TMR6_CR_OPM_Pos));
}

/**
  * @brief  Get the counter work mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Counter work mode @ref LL_LPTMR_WorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetOnePulseMode(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->CR, TMR6_CR_OPM_Msk, TMR6_CR_OPM_Pos));
}



/**
  * @brief  Set the ETR mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Slv Mode to be set @ref LL_LPTMR_SlvModeTypeDef
  * @param  Etr Mode to be set @ref LL_LPTMR_ETRModeTypeDef
  * @param  Edge Mode to be set @ref LL_LPTMR_ETREdgeTypeDef
  * @param  Fil Filter value @ref LL_LPTMR_ETRFilTypeDef
  * @param  Tri Trigger selection @ref LL_LPTMR_TrigTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_ConfigSlaveControl(LPTMR_TypeDef *LPTMRx, uint32_t Slv, 
                                                 uint32_t Etr, uint32_t Edge,
                                                 uint32_t Fil, uint32_t Tri)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->SCR, ((((Slv) & TMR6_SCR_SMS_Val) << TMR6_SCR_SMS_Pos) & TMR6_SCR_SMS_Msk)    |
                              ((((Etr) & TMR6_SCR_EE_Val) << TMR6_SCR_EE_Pos) & TMR6_SCR_EE_Msk)      |
                              ((((Edge) & TMR6_SCR_EMS_Val) << TMR6_SCR_EMS_Pos) & TMR6_SCR_EMS_Msk)  |
                              ((((Fil) & TMR6_SCR_EFS_Val) << TMR6_SCR_EFS_Pos) & TMR6_SCR_EFS_Msk)   |
                              ((((Tri) & TMR6_SCR_TS_Val) << TMR6_SCR_TS_Pos) & TMR6_SCR_TS_Msk));
}

/**
  * @brief  Set the ETR mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mode Mode to be set @ref LL_LPTMR_ETRModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetETRMode(LPTMR_TypeDef *LPTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_LPTMR_ETR_MODE(Mode));

    MODIFY_REG((LPTMRx)->SCR, TMR6_SCR_EE_Msk, (((Mode) & TMR6_SCR_EE_Val) << TMR6_SCR_EE_Pos));
}

/**
  * @brief  Get the ETR mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return ETR mode @ref LL_LPTMR_ETRModeTypeDef
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetETRMode(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SCR, TMR6_SCR_EE_Msk, TMR6_SCR_EE_Pos));
}

/**
  * @brief  Set the ETR edge mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mode Mode to be set @ref LL_LPTMR_ETREdgeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetETREdgeMode(LPTMR_TypeDef *LPTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM(IS_LL_LPTMR_ETR_EDGE_MODE(Mode));

    MODIFY_REG((LPTMRx)->SCR, TMR6_SCR_EMS_Msk, (((Mode) & TMR6_SCR_EMS_Val) << TMR6_SCR_EMS_Pos));
}

/**
  * @brief  Get the ETR edge mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return ETR edge mode @ref LL_LPTMR_ETREdgeTypeDef
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetETREdgeMode(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SCR, TMR6_SCR_EMS_Msk, TMR6_SCR_EMS_Pos));
}

/**
  * @brief  Set the ETR filter coefficient (SCR.EFS, 4 bits)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Fil Filter value @ref LL_LPTMR_ETRFilTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetETRFilter(LPTMR_TypeDef *LPTMRx, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    MODIFY_REG((LPTMRx)->SCR, TMR6_SCR_EFS_Msk, (((Fil) & TMR6_SCR_EFS_Val) << TMR6_SCR_EFS_Pos));
}

/**
  * @brief  Get the ETR filter coefficient
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return ETR filter coefficient @ref LL_LPTMR_ETRFilTypeDef
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetETRFilter(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SCR, TMR6_SCR_EFS_Msk, TMR6_SCR_EFS_Pos));
}

/**
  * @brief  Set the trigger input source (SCR.TS, 5 bits, raw value)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Tri Trigger selection @ref LL_LPTMR_TrigTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetTriggerInput(LPTMR_TypeDef *LPTMRx, uint32_t Tri)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    MODIFY_REG((LPTMRx)->SCR, TMR6_SCR_TS_Msk, (((Tri) & TMR6_SCR_TS_Val) << TMR6_SCR_TS_Pos));
}

/**
  * @brief  Get the trigger input source
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Trigger input source @ref LL_LPTMR_TrigTypeDef
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetTrigger(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SCR, TMR6_SCR_TS_Msk, TMR6_SCR_TS_Pos));
}

/**
  * @brief  Set the slave mode (SCR.SMS, 4 bits, raw value)
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mode Mode to be set @ref LL_LPTMR_SlvModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetSlaveMode(LPTMR_TypeDef *LPTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    MODIFY_REG((LPTMRx)->SCR, TMR6_SCR_SMS_Msk, (((Mode) & TMR6_SCR_SMS_Val) << TMR6_SCR_SMS_Pos));
}

/**
  * @brief  Get the slave mode
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Slave mode @ref LL_LPTMR_SlvModeTypeDef
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetSlaveMode(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SCR, TMR6_SCR_SMS_Msk, TMR6_SCR_SMS_Pos));
}

/**
  * @brief  Generate a software update event
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_GenerateEvent_UPDATE(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->UGR, TMR6_UGR_UG_Msk);
}

/**
  * @brief  Generate a trigger event
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_GenerateEvent_TRIG(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->UGR, TMR6_UGR_TG_Msk);
}

/**
  * @brief  Generate a compare update event
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_GenerateEvent_CMP(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->UGR, TMR6_UGR_CG_Msk);
}

/**
  * @brief  Generate a counter start generation
  * @param  LPTMRx Specifies TMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_GenerateEvent_START(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE (LPTMRx));

    SET_BIT((LPTMRx)->UGR, TMR6_UGR_SG_Msk);
}

/**
  * @brief  Judge whether the LPTMR is starting
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 No action
  * @retval 1 LPTMR is is starting
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsStarting(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->UGR, TMR6_UGR_SG_Msk, TMR6_UGR_SG_Pos));
}


#if 0///TODO:DELETE
/**
  * @brief  Enable the output preload of a given compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_LPTMR_CapCmpChTypeDef (LL_LPTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_OC_EnablePreload(LPTMR_TypeDef *LPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_LPTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((LPTMRx)->CCMR, TMR6_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((0x1UL) & TMR6_CCMR_CC0PE_Val) << (TMR6_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Disable the output preload of a given compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_LPTMR_CapCmpChTypeDef (LL_LPTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_OC_DisablePreload(LPTMR_TypeDef *LPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_LPTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));

    MODIFY_REG((LPTMRx)->CCMR, TMR6_CCMR_CC0PE_Msk << (((Channel) % 4UL) * 8UL), 
            (((0x0UL) & TMR6_CCMR_CC0PE_Val) << (TMR6_CCMR_CC0PE_Pos + ((Channel) % 4UL) * 8UL)));
}

/**
  * @brief  Set the output polarity of a given compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_LPTMR_CapCmpChTypeDef (LL_LPTMR_CAP_CMP_CH_x)
  * @param  Pol Output Polarity @ref LL_LPTMR_CmpPolTypeDef
  * @param  IsOCN @ref LL_LPTMR_CapCmpOCTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_OC_SetPolarity(LPTMR_TypeDef *LPTMRx, uint32_t Channel, uint32_t Pol, uint32_t IsOCN)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_LPTMR_CAP_CMP_CH(Channel)) && (Channel < 4UL));
    ASSERT_INLINE_PARAM(IS_LL_LPTMR_CAP_CMP_OC(IsOCN));

    if (!IsOCN) {
        MODIFY_REG((LPTMRx)->CCER, (0x1UL << TMR6_CCER_CC0P_Pos) << (((Channel) % 4UL) * 4UL), 
                (((Pol) & 0x1UL) << (TMR6_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)));      
    } else {
        MODIFY_REG((LPTMRx)->CCER, (0x1UL << (TMR6_CCER_CC0P_Pos + 1UL)) << (((Channel) % 4UL) * 4UL), 
                (((Pol) & 0x1UL) << (((TMR6_CCER_CC0P_Pos + ((Channel) % 4UL) * 4UL)) + 1UL)));
    }
}

/**
  * @brief  Enable a given capture/compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_LPTMR_CapCmpChTypeDef (LL_LPTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_CC_EnableChannel(LPTMR_TypeDef *LPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_LPTMR_CHANNEL(Channel)) && (Channel < 8UL));

    if (Channel <= LL_LPTMR_CAP_CMP_CH_3) {
        MODIFY_REG((LPTMRx)->CCER, TMR6_CCER_CC0E_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x1UL) & TMR6_CCER_CC0E_Val) << (TMR6_CCER_CC0E_Pos + ((Channel) % 4UL) * 4UL)));
    } else if (Channel <= LL_LPTMR_CAP_CMP_CH_3N){
        MODIFY_REG((LPTMRx)->CCER, TMR6_CCER_CC0NE_Msk << (((Channel - LL_LPTMR_CAP_CMP_CH_0N) % 4UL) * 4UL), 
                (((0x1UL) & TMR6_CCER_CC0NE_Val) << (TMR6_CCER_CC0NE_Pos + ((Channel) % 4UL) * 4UL)));
    }
}

/**
  * @brief  Disable a given capture/compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Channel Capture/compare channel @ref LL_LPTMR_CapCmpChTypeDef (LL_LPTMR_CAP_CMP_CH_x)
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_CC_DisableChannel(LPTMR_TypeDef *LPTMRx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_INLINE_PARAM((IS_LL_LPTMR_CHANNEL(Channel)) && (Channel < 8UL));

    if (Channel <= LL_LPTMR_CAP_CMP_CH_3) {
        MODIFY_REG((LPTMRx)->CCER, TMR6_CCER_CC0E_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x0UL) & TMR6_CCER_CC0E_Val) << (TMR6_CCER_CC0E_Pos + ((Channel) % 4UL) * 4UL)));
    } else if (Channel <= LL_LPTMR_CAP_CMP_CH_3N){
        MODIFY_REG((LPTMRx)->CCER, TMR6_CCER_CC0NE_Msk << (((Channel) % 4UL) * 4UL), 
                (((0x0UL) & TMR6_CCER_CC0NE_Val) << (TMR6_CCER_CC0NE_Pos + ((Channel) % 4UL) * 4UL)));
    }
}
#endif

/**
  * @brief  Enable the output preload of a given compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_EnableComparePreload(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->CCMR, TMR6_CCMR_RLD_Msk);
}

/**
  * @brief  Disable the output preload of a given compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_DisableComparePreload(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    CLEAR_BIT((LPTMRx)->CCMR, TMR6_CCMR_RLD_Msk);
}

/**
  * @brief  Configurate the output compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  En Output Enable @ref LL_LPTMR_CmpEnTypeDef
  * @param  Pol Output Polarity @ref LL_LPTMR_CmpPolTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_ConfigCompareOutput(LPTMR_TypeDef *LPTMRx, uint32_t En ,uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->CCER, ((((Pol) & TMR6_CCER_CCP_Val) << TMR6_CCER_CCP_Pos) & TMR6_CCER_CCP_Msk) |
                              ((((En) & TMR6_CCER_CCE_Val) << TMR6_CCER_CCE_Pos) & TMR6_CCER_CCE_Msk));
}

/**
  * @brief  Set the output polarity of a given compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Pol Output Polarity @ref LL_LPTMR_CmpPolTypeDef
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_SetPolarity(LPTMR_TypeDef *LPTMRx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    MODIFY_REG((LPTMRx)->CCER, TMR6_CCER_CCP_Msk, (((Pol) & TMR6_CCER_CCP_Val) << TMR6_CCER_CCP_Pos ));   
}

/**
  * @brief  Enable a compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_EnableCompareChannel(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->CCER, TMR6_CCER_CCE_Msk);   
}

/**
  * @brief  Disable a compare channel.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval None
  */
__STATIC_INLINE void LL_LPTMR_DisableCompareChannel(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
  
    CLEAR_BIT((LPTMRx)->CCER, TMR6_CCER_CCE_Msk);   
}

/**
  * @brief  Set the CC0 compare value
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_SetCompare(LPTMR_TypeDef *LPTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->CC0R, ((Val) & TMR6_CC0R_CMP_Val));
}

/**
  * @brief  Get the CC0 compare value
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return CC0 compare value
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetCompare(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_REG((LPTMRx)->CC0R) & TMR6_CC0R_CMP_Val);
}


/**
  * @}
  */

/** @defgroup LPTMR_LL_EF_IT_Management LL LPTMR Interrupt Management
  * @brief    LL LPTMR Interrupt Management
  * @details    Per-channel capture/compare and over-capture interrupts.
  * @{
  */

/**
  * @brief  Enable the update interrupt
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_EnableIT_UPDATE(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->IER, TMR6_IER_UIE_Msk);
}

/**
  * @brief  Disable the update interrupt
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_DisableIT_UPDATE(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    CLEAR_BIT((LPTMRx)->IER, TMR6_IER_UIE_Msk);
}

/**
  * @brief  Judge whether the update event interrupt is enabled or not
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 Update event interrupt is disabled
  * @retval 1 Update event interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsEnabledIT_UPDATE(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->IER, TMR6_IER_UIE_Msk, TMR6_IER_UIE_Pos));
}

/**
  * @brief  Enable the trigger interrupt
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_EnableIT_TRIG(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->IER, TMR6_IER_TIE_Msk);
}

/**
  * @brief  Disable the trigger interrupt
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_DisableIT_TRIG(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    CLEAR_BIT((LPTMRx)->IER, TMR6_IER_TIE_Msk);
}

/**
  * @brief  Judge whether the trigger interrupt is enabled or not
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 Trigger interrupt is disabled
  * @retval 1 Trigger interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsEnabledIT_TRIG(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->IER, TMR6_IER_TIE_Msk, TMR6_IER_TIE_Pos));
}


/**
  * @brief  Enable the compare interrupt
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_EnableIT_CMP(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT((LPTMRx)->IER, TMR6_IER_CIE_Msk);
}

/**
  * @brief  Disable the compare interrupt
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_DisableIT_CMP(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    CLEAR_BIT((LPTMRx)->IER, TMR6_IER_CIE_Msk);
}

/**
  * @brief  Judge whether the compare interrupt is enabled
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 compare interrupt is disabled
  * @retval 1 compare interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsEnabledIT_CMP(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->IER, TMR6_IER_CIE_Msk, TMR6_IER_CIE_Pos));
}

/**
  * @brief  Get the whole interrupt enable register
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Whole interrupt enable register
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetAllIntEn(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_REG((LPTMRx)->IER));
}

/**
  * @brief  Judge whether the update event flag is set
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 Update event flag is cleared
  * @retval 1 Update event flag is set
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsActiveFlag_UPDATE(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SR, TMR6_SR_UIF_Msk, TMR6_SR_UIF_Pos));
}

/**
  * @brief  Clear the update event flag
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_ClearFlag_UPDATE(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->SR, TMR6_SR_UIF_Msk);
}

/**
  * @brief  Judge whether the trigger flag is set
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 Trigger flag is cleared
  * @retval 1 Trigger flag is set
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsActiveFlag_TRIG(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SR, TMR6_SR_TIF_Msk, TMR6_SR_TIF_Pos));
}

/**
  * @brief  Clear the trigger flag
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_ClearFlag_TRIG(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->SR, TMR6_SR_TIF_Msk);
}

/**
  * @brief  Get the whole status register
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Whole status register
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetAllFlag(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_REG((LPTMRx)->SR));
}


/**
  * @brief  Judge is Counter Running Done or not
  * @param  TMRx Specifies TMR peripheral
  * @retval 0 Counter isn't Running
  * @retval 1 Counter is Running
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsActiveFlag_STS(const LPTMR_TypeDef *TMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE (TMRx));

    return (READ_BIT_SHIFT((TMRx)->SR, TMR6_SR_STS_Msk, TMR6_SR_STS_Pos));
}

/**
  * @brief  Judge is Compare Update Done or not
  * @param  TMRx Specifies TMR peripheral
  * @retval 0 Compare Update isn't Done
  * @retval 1 Compare Update is Done
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsActiveFlag_CUS(const LPTMR_TypeDef *TMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE (TMRx));

    return (!READ_BIT_SHIFT((TMRx)->SR, TMR6_SR_CUS_Msk, TMR6_SR_CUS_Pos));
}

/**
  * @brief  Judge is Period Update Done or not
  * @param  TMRx Specifies TMR peripheral
  * @retval 0 Period Update isn't Done
  * @retval 1 Period Update is Done
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsActiveFlag_PUS(const LPTMR_TypeDef *TMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE (TMRx));

    return (!READ_BIT_SHIFT((TMRx)->SR, TMR6_SR_PUS_Msk, TMR6_SR_PUS_Pos));
}

/**
  * @brief  Judge whether the compare flag is set
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval 0 compare flag is cleared
  * @retval 1 compare flag is set
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsActiveFlag_CMP(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT_SHIFT((LPTMRx)->SR, TMR6_SR_CIF_Msk, TMR6_SR_CIF_Pos));
}

/**
  * @brief  Clear the compare flag
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_ClearFlag_CMP(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG((LPTMRx)->SR, TMR6_SR_CIF_Msk);
}

/**
  * @brief  LPTMR Interrupt enable
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mask Mask to enable @ref LL_LPTMR_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_EnableIT(LPTMR_TypeDef *LPTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    SET_BIT(LPTMRx->IER, Mask);
}

/**
  * @brief  LPTMR Interrupt disable
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mask Mask to disable @ref LL_LPTMR_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_DisableIT(LPTMR_TypeDef *LPTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    CLEAR_BIT(LPTMRx->IER, Mask);
}

/**
  * @brief  Check if LPTMR Interrupt is enabled or disabled
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mask Mask to check @ref LL_LPTMR_IER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsEnabledIT(const LPTMR_TypeDef *LPTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(LPTMRx->IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mask Mask to clear @ref LL_LPTMR_SR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_LPTMR_ClearFlag(LPTMR_TypeDef *LPTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    WRITE_REG(LPTMRx->SR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  LPTMRx Specifies LPTMR peripheral
  * @param  Mask Mask to check @ref LL_LPTMR_SR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTMR_IsActiveFlag(const LPTMR_TypeDef *LPTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(LPTMRx->SR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  LPTMR Interrupt All Enable Get
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Interrupt Enable Bit
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetAllEnabledIT(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT(LPTMRx->IER, LL_LPTMR_IER_IT_EN_MSK));
}

/**
  * @brief  Get interrupt status of the specified LPTMR channel 
  * @param  LPTMRx Specifies LPTMR peripheral
  * @return Interrupt status
  */
__STATIC_INLINE uint32_t LL_LPTMR_GetAllITPending(const LPTMR_TypeDef *LPTMRx)
{
    ASSERT_INLINE_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    return (READ_BIT(LPTMRx->SR, LL_LPTMR_SR_IT_FLAG_MSK));
}


/**
  * @}
  */ /* LPTMR_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* LPTMR_LL_Exported_Functions */

#endif /* LPTMR */

/**
  * @}
  */ /* LPTMR_LL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_LPTMR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/









