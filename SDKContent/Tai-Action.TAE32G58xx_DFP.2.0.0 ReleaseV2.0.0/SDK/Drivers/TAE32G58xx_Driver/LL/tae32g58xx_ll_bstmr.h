/**
  ******************************************************************************
  * @file    tae32g58xx_ll_bstmr.h
  * @author  Tai-Action SD Team
  * @brief   Header file for BSTMR (Basic Timer) LL module
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
#ifndef _TAE32G58XX_LL_BSTMR_H_
#define _TAE32G58XX_LL_BSTMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if (defined(TMR7) || defined(TMR8))

/** @defgroup BSTMR_LL BSTMR LL
  * @brief    BSTMR LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup BSTMR_LL_Exported_Constants BSTMR LL Exported Constants
  * @brief    BSTMR LL Exported Constants
  * @{
  */

/** @name LL_BSTMR_IER_ITEnMskTypeDef
  * @brief BSTMR LL Interrupt Enable Masks
  * @{
  */
#define LL_BSTMR_IER_ITEnMskTypeDef     uint32_t

#define LL_BSTMR_IER_OVIE               (TMR7_IER_OVIE_Msk)     /*!< Overflow interrupt enable       */
#define LL_BSTMR_IER_UIE                (TMR7_IER_UIE_Msk)      /*!< Update interrupt enable         */

#define LL_BSTMR_IER_IT_EN_MSK          ((TMR7_IER_OVIE_Msk               | TMR7_IER_UIE_Msk                ))
/** @} */

/** @name LL_BSTMR_SR_ITPendingMskTypeDef
  * @brief BSTMR LL Status Flag Masks
  * @{
  */
#define LL_BSTMR_SR_ITPendingMskTypeDef uint32_t

#define LL_BSTMR_SR_OVIF                (TMR7_SR_OVIF_Msk)      /*!< Overflow flag                   */
#define LL_BSTMR_SR_UIF                 (TMR7_SR_UIF_Msk)       /*!< Update flag                     */

#define LL_BSTMR_SR_IT_FLAG_MSK         ((TMR7_SR_OVIF_Msk                | TMR7_SR_UIF_Msk                 ))

#define LL_BSTMR_SR_UPD_IT_FLAG_MSK     ((TMR7_SR_OVIF_Msk                | TMR7_SR_UIF_Msk                 ))
/** @} */



/** @name LL_BSTMR_WorkModeTypeDef
  * @brief BSTMR LL Work Mode (CR0.OPM)
  * @{
  */
#define LL_BSTMR_WorkModeTypeDef        LL_RSV_DATA_TYPE

#define LL_BSTMR_WORK_MODE_CONTINUE     (0UL)   /*!< Continue mode */
#define LL_BSTMR_WORK_MODE_SINGLE       (1UL)   /*!< Single mode   */

#define IS_LL_BSTMR_WORK_MODE(__VAL__)              (((__VAL__) == LL_BSTMR_WORK_MODE_CONTINUE) || \
                                                     ((__VAL__) == LL_BSTMR_WORK_MODE_SINGLE))
/** @} */

/** @name LL_BSTMR_UpdateEvtSrcTypeDef
  * @brief BSTMR LL Update Event Source (CR0.URS)
  * @{
  */
#define LL_BSTMR_UpdateEvtSrcTypeDef    LL_RSV_DATA_TYPE

#define LL_BSTMR_UPDATE_EVT_SRC_OV_UG   (0UL)   /*!< Overflow and software (UG) */
#define LL_BSTMR_UPDATE_EVT_SRC_OV      (1UL)   /*!< Only overflow              */

#define IS_LL_BSTMR_UPDATE_EVT_SRC(__VAL__)         (((__VAL__) == LL_BSTMR_UPDATE_EVT_SRC_OV_UG) || \
                                                     ((__VAL__) == LL_BSTMR_UPDATE_EVT_SRC_OV))
/** @} */


/** @name LL_BSTMR_MstModeTypeDef
  * @brief BSTMR LL Master Mode (CR1.MMS)
  * @{
  */
#define LL_BSTMR_MstModeTypeDef         LL_RSV_DATA_TYPE

#define LL_BSTMR_MST_MODE_RESET         (0UL)   /*!< TRGO = counter reset (UG)    */
#define LL_BSTMR_MST_MODE_ENABLE        (1UL)   /*!< TRGO = counter enable        */
#define LL_BSTMR_MST_MODE_UPDATE        (2UL)   /*!< TRGO = update event          */

#define IS_LL_BSTMR_MST_MODE(__VAL__)               (((__VAL__) == LL_BSTMR_MST_MODE_RESET)       || \
                                                     ((__VAL__) == LL_BSTMR_MST_MODE_ENABLE)      || \
                                                     ((__VAL__) == LL_BSTMR_MST_MODE_UPDATE))
/** @} */

/** @name LL_BSTMR_EvtGenMaskTypeDef
  * @brief BSTMR LL Timer Event Generation Mask
  * @{
  */
#define LL_BSTMR_EvtGenMaskTypeDef                uint32_t    

#define LL_BSTMR_EVT_GEN_UPDATE                   (TMR7_UGR_UG_Msk)         /*!< Timer Event Generation Update                    */

#define LL_BSTMR_EVT_GEN_ALL_MSK                  ((TMR7_UGR_UG_Msk))
/** @} */

/** @name LL_BSTMR_BrkPolTypeDef
  * @brief BSTMR LL Break Input Polarity (DCR.BK0P / DCR.BK1P)
  * @{
  */
#define LL_BSTMR_BrkPolTypeDef              LL_RSV_DATA_TYPE

#define LL_BSTMR_BRK_POL_HIGH               (0UL)   /*!< Break input high active */
#define LL_BSTMR_BRK_POL_LOW                (1UL)   /*!< Break input low active  */

#define IS_LL_BSTMR_BRK_POL(__VAL__)        (((__VAL__) == LL_BSTMR_BRK_POL_HIGH) || \
                                             ((__VAL__) == LL_BSTMR_BRK_POL_LOW))
/** @} */

/** @name LL_BSTMR_BrkInPolTypeDef
  * @brief BSTMR LL Break Input Valid Level Polarity
  * @{
  */
#define LL_BSTMR_BrkInPolTypeDef            LL_RSV_DATA_TYPE

#define LL_BSTMR_BRK_IN_POL_VALID_HIGH      (0UL)   /*!< Break input valid level high */
#define LL_BSTMR_BRK_IN_POL_VALID_LOW       (1UL)   /*!< Break input valid low high */

#define IS_LL_BSTMR_BRK_IN_POL(__VAL__)     (((__VAL__) == LL_BSTMR_BRK_IN_POL_VALID_HIGH) || \
                                             ((__VAL__) == LL_BSTMR_BRK_IN_POL_VALID_LOW))
/** @} */

/** @name LL_BSTMR_RunOffStaTypeDef
  * @brief BSTMR LL Run-Mode Off-State
  * @{
  */
#define LL_BSTMR_RunOffStaTypeDef           LL_RSV_DATA_TYPE

#define LL_BSTMR_RUN_OFF_STA_COMP_CLOSE    (0UL)   /*!< Idle-Mode Off-State complementary output close */
#define LL_BSTMR_RUN_OFF_STA_COMP_IVD      (1UL)   /*!< Idle-Mode Off-State complementary output is in the invalid state*/

#define IS_LL_BSTMR_RUN_OFF_STA(__VAL__)   (((__VAL__) == LL_BSTMR_RUN_OFF_STA_COMP_CLOSE) || \
                                             ((__VAL__) == LL_BSTMR_RUN_OFF_STA_COMP_IVD))
/** @} */

/** @name LL_BSTMR_IdleOffStaTypeDef
  * @brief BSTMR LL Idle-Mode Off-State
  * @{
  */
#define LL_BSTMR_IdleOffStaTypeDef          LL_RSV_DATA_TYPE

#define LL_BSTMR_IDLE_OFF_STA_COMP_CLOSE    (0UL)   /*!< Idle-Mode Off-State complementary output close */
#define LL_BSTMR_IDLE_OFF_STA_COMP_IDLE     (1UL)   /*!< Idle-Mode Off-State complementary output is in the idle state*/

#define IS_LL_BSTMR_IDLE_OFF_STA(__VAL__)   (((__VAL__) == LL_BSTMR_IDLE_OFF_STA_COMP_CLOSE) || \
                                             ((__VAL__) == LL_BSTMR_IDLE_OFF_STA_COMP_IDLE))
/** @} */

/** @name LL_BSTMR_CapFilTypeDef
  * @brief BSTMR LL Capture Filter
  * @{
  */
#define LL_BSTMR_CapFilTypeDef              LL_RSV_DATA_TYPE

#define LL_BSTMR_CAP_FILTER_NONE            (0UL)
#define LL_BSTMR_CAP_FILTER_TDS_X1          (1UL)
#define LL_BSTMR_CAP_FILTER_TDS_X2          (2UL)
#define LL_BSTMR_CAP_FILTER_TDS_X3          (3UL)
#define LL_BSTMR_CAP_FILTER_TDS_X4          (4UL)
#define LL_BSTMR_CAP_FILTER_TDS_X5          (5UL)
#define LL_BSTMR_CAP_FILTER_TDS_X6          (6UL)
#define LL_BSTMR_CAP_FILTER_TDS_X7          (7UL)
#define LL_BSTMR_CAP_FILTER_TDS_X8          (8UL)
#define LL_BSTMR_CAP_FILTER_TDS_X9          (9UL)
#define LL_BSTMR_CAP_FILTER_TDS_X10         (10UL)
#define LL_BSTMR_CAP_FILTER_TDS_X11         (11UL)
#define LL_BSTMR_CAP_FILTER_TDS_X12         (12UL)
#define LL_BSTMR_CAP_FILTER_TDS_X13         (13UL)
#define LL_BSTMR_CAP_FILTER_TDS_X14         (14UL)
#define LL_BSTMR_CAP_FILTER_TDS_X15         (15UL)

#define IS_LL_BSTMR_CAP_FILTER(__VAL__)     (((__VAL__) >= LL_BSTMR_CAP_FILTER_NONE) && \
                                             ((__VAL__) <= LL_BSTMR_CAP_FILTER_TDS_X15))
/** @} */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup BSTMR_LL_Exported_Functions BSTMR LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_BSTMR_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_BSTMR_ASSERT_INLINE_PARAM == 1)
extern void LL_BSTMR_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_BSTMR_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_BSTMR_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_BSTMR_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup BSTMR_LL_EF_Configuration LL BSTMR Configuration
  * @brief    LL BSTMR Configuration
  * @{
  */

/**
  * @brief  Enable the counter
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_EnableCounter(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    SET_BIT((BSTMRx)->CR0, TMR7_CR0_CEN_Msk);
}

/**
  * @brief  Disable the counter
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_DisableCounter(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    CLEAR_BIT((BSTMRx)->CR0, TMR7_CR0_CEN_Msk);
}

/**
  * @brief  Judge whether the counter is enabled or not (CR0.CEN)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @retval 0 Counter is disabled
  * @retval 1 Counter is enabled
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsEnabledCounter(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->CR0, TMR7_CR0_CEN_Msk, TMR7_CR0_CEN_Pos));
}

/**
  * @brief  Set the counter value (16 bits)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_SetCounter(BSTMR_TypeDef *BSTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    WRITE_REG((BSTMRx)->CNTR, ((Val) & TMR7_CNTR_CNT_Val));
}

/**
  * @brief  Get the counter value (16 bits)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Counter value (16 bits)
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetCounter(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_REG((BSTMRx)->CNTR) & TMR7_CNTR_CNT_Val);
}

/**
  * @brief  Set the counter period (auto-reload value, 16 bits)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Period Counter period value
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_SetAutoReload(BSTMR_TypeDef *BSTMRx, uint32_t Period)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    WRITE_REG((BSTMRx)->CPR, ((Period) & TMR7_CPR_CPV_Val));
}

/**
  * @brief  Get the counter period (16 bits)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Counter period (16 bits)
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetAutoReload(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_REG((BSTMRx)->CPR) & TMR7_CPR_CPV_Val);
}

/**
  * @brief  Set the prescaler division value (16 bits)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Val Value to be written
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_SetPrescaler(BSTMR_TypeDef *BSTMRx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    WRITE_REG((BSTMRx)->PSCR, ((Val) & TMR7_PSCR_PSC_Val));
}

/**
  * @brief  Get the prescaler division value (16 bits)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Prescaler division value (16 bits)
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetPrescaler(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_REG((BSTMRx)->PSCR) & TMR7_PSCR_PSC_Val);
}


/**
  * @brief  Enable the auto-preload
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_EnableAutoReload(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    SET_BIT((BSTMRx)->CR0, TMR7_CR0_ARE_Msk);
}

/**
  * @brief  Disable the auto-preload
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_DisableAutoReload(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    CLEAR_BIT((BSTMRx)->CR0, TMR7_CR0_ARE_Msk);
}

/**
  * @brief  Judge whether the auto-preload is enabled or not
  * @param  BSTMRx Specifies BSTMR peripheral
  * @retval 0 Auto-preload is disabled
  * @retval 1 Auto-preload is enabled
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsAutoReloadEnabled(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->CR0, TMR7_CR0_ARE_Msk, TMR7_CR0_ARE_Pos));
}

/**
  * @brief  Set the counter work mode
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Mode Mode to be set @ref LL_BSTMR_WorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_SetOnePulseMode(BSTMR_TypeDef *BSTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));
    ASSERT_INLINE_PARAM(IS_LL_BSTMR_WORK_MODE(Mode));

    MODIFY_REG((BSTMRx)->CR0, TMR7_CR0_OPM_Msk, (((Mode) & TMR7_CR0_OPM_Val) << TMR7_CR0_OPM_Pos));
}

/**
  * @brief  Get the counter work mode
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Counter work mode @ref LL_BSTMR_WorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetOnePulseMode(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->CR0, TMR7_CR0_OPM_Msk, TMR7_CR0_OPM_Pos));
}

/**
  * @brief  Set the update event source
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Src Source to be selected @ref LL_BSTMR_UpdateEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_SetUpdateSource(BSTMR_TypeDef *BSTMRx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));
    ASSERT_INLINE_PARAM(IS_LL_BSTMR_UPDATE_EVT_SRC(Src));

    MODIFY_REG((BSTMRx)->CR0, TMR7_CR0_URS_Msk, (((Src) & TMR7_CR0_URS_Val) << TMR7_CR0_URS_Pos));
}

/**
  * @brief  Get the update event source
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Update event source @ref LL_BSTMR_UpdateEvtSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetUpdateSource(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->CR0, TMR7_CR0_URS_Msk, TMR7_CR0_URS_Pos));
}

/**
  * @brief  Enable the update event (UDIS = 0)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_EnableUpdateEvent(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    CLEAR_BIT((BSTMRx)->CR0, TMR7_CR0_UDIS_Msk);
}

/**
  * @brief  Disable the update event (UDIS = 1)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_DisableUpdateEvent(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    SET_BIT((BSTMRx)->CR0, TMR7_CR0_UDIS_Msk);
}

/**
  * @brief  Judge whether the update event is enabled or not
  * @param  BSTMRx Specifies BSTMR peripheral
  * @retval 0 Update event is disabled
  * @retval 1 Update event is enabled
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsEnabledUpdateEvent(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (!(READ_BIT_SHIFT((BSTMRx)->CR0, TMR7_CR0_UDIS_Msk, TMR7_CR0_UDIS_Pos)));
}

/**
  * @brief  Set the master mode (source of the TRGO signal)
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Mode Mode to be set @ref LL_BSTMR_MstModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_SetTriggerOutput(BSTMR_TypeDef *BSTMRx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));
    ASSERT_INLINE_PARAM(IS_LL_BSTMR_MST_MODE(Mode));

    MODIFY_REG((BSTMRx)->CR1, TMR7_CR1_MMS_Msk, (((Mode) & TMR7_CR1_MMS_Val) << TMR7_CR1_MMS_Pos));
}

/**
  * @brief  Get the master mode
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Master mode @ref LL_BSTMR_MstModeTypeDef
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetTriggerOutput(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->CR1, TMR7_CR1_MMS_Msk, TMR7_CR1_MMS_Pos));
}

/**
  * @brief  Generate a software update event
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_GenerateEvent_UPDATE(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    SET_BIT((BSTMRx)->UGR, TMR7_UGR_UG_Msk);
}

/**
  * @brief  Set the master trigger output (TRGO) pulse width
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Width Output pulse width
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_SetTrigOutputWidth(BSTMR_TypeDef *BSTMRx, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    MODIFY_REG((BSTMRx)->TCR, TMR7_TCR_TOW_Msk, (((Width) & TMR7_TCR_TOW_Val) << TMR7_TCR_TOW_Pos));
}

/**
  * @brief  Get the master trigger output pulse width
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Master trigger output pulse width
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetTrigOutputWidth(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->TCR, TMR7_TCR_TOW_Msk, TMR7_TCR_TOW_Pos));
}


/**
  * @}
  */

/** @defgroup BSTMR_LL_EF_IT_Management LL BSTMR Interrupt Management
  * @brief    LL BSTMR Interrupt Management
  * @details    Per-channel capture/compare and over-capture interrupts.
  * @{
  */

/**
  * @brief  Enable the update interrupt
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_EnableIT_UPDATE(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    SET_BIT((BSTMRx)->IER, TMR7_IER_UIE_Msk);
}

/**
  * @brief  Disable the update interrupt
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_DisableIT_UPDATE(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    CLEAR_BIT((BSTMRx)->IER, TMR7_IER_UIE_Msk);
}

/**
  * @brief  Enable the counter overflow interrupt
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_EnableIT_OVR(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    SET_BIT((BSTMRx)->IER, TMR7_IER_OVIE_Msk);
}

/**
  * @brief  Disable the counter overflow interrupt
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_DisableIT_OVR(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    CLEAR_BIT((BSTMRx)->IER, TMR7_IER_OVIE_Msk);
}

/**
  * @brief  Judge whether the counter overflow interrupt is enabled or not
  * @param  BSTMRx Specifies BSTMR peripheral
  * @retval 0 Counter overflow interrupt is disabled
  * @retval 1 Counter overflow interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsEnabledIT_OVR(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->IER, TMR7_IER_OVIE_Msk, TMR7_IER_OVIE_Pos));
}

/**
  * @brief  Judge whether the update event interrupt is enabled or not
  * @param  BSTMRx Specifies BSTMR peripheral
  * @retval 0 Update event interrupt is disabled
  * @retval 1 Update event interrupt is enabled
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsEnabledIT_UPDATE(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->IER, TMR7_IER_UIE_Msk, TMR7_IER_UIE_Pos));
}

/**
  * @brief  Get the whole interrupt enable register
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Whole interrupt enable register
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetAllIntEn(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_REG((BSTMRx)->IER));
}

/**
  * @brief  Judge whether the counter overflow flag is set
  * @param  BSTMRx Specifies BSTMR peripheral
  * @retval 0 Counter overflow flag is cleared
  * @retval 1 Counter overflow flag is set
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsActiveFlag_OVR(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->SR, TMR7_SR_OVIF_Msk, TMR7_SR_OVIF_Pos));
}

/**
  * @brief  Clear the counter overflow flag
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_ClearFlag_OVR(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    WRITE_REG((BSTMRx)->SR, TMR7_SR_OVIF_Msk);
}

/**
  * @brief  Judge whether the update event flag is set
  * @param  BSTMRx Specifies BSTMR peripheral
  * @retval 0 Update event flag is cleared
  * @retval 1 Update event flag is set
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsActiveFlag_UPDATE(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT_SHIFT((BSTMRx)->SR, TMR7_SR_UIF_Msk, TMR7_SR_UIF_Pos));
}

/**
  * @brief  Clear the update event flag
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_ClearFlag_UPDATE(BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    WRITE_REG((BSTMRx)->SR, TMR7_SR_UIF_Msk);
}

/**
  * @brief  Get the whole status register
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Whole status register
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetAllFlag(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_REG((BSTMRx)->SR));
}

/**
  * @brief  BSTMR Interrupt enable
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Mask Mask to enable @ref LL_BSTMR_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_EnableIT(BSTMR_TypeDef *BSTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    SET_BIT(BSTMRx->IER, Mask);
}

/**
  * @brief  BSTMR Interrupt disable
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Mask Mask to disable @ref LL_BSTMR_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_DisableIT(BSTMR_TypeDef *BSTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    CLEAR_BIT(BSTMRx->IER, Mask);
}

/**
  * @brief  Check if BSTMR Interrupt is enabled or disabled
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Mask Mask to check @ref LL_BSTMR_IER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsEnabledIT(const BSTMR_TypeDef *BSTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(BSTMRx->IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Mask Mask to clear @ref LL_BSTMR_SR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_BSTMR_ClearFlag(BSTMR_TypeDef *BSTMRx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    WRITE_REG(BSTMRx->SR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  BSTMRx Specifies BSTMR peripheral
  * @param  Mask Mask to check @ref LL_BSTMR_SR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_BSTMR_IsActiveFlag(const BSTMR_TypeDef *BSTMRx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(BSTMRx->SR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  BSTMR Interrupt All Enable Get
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Interrupt Enable Bit
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetAllEnabledIT(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT(BSTMRx->IER, LL_BSTMR_IER_IT_EN_MSK));
}

/**
  * @brief  Get interrupt status of the specified BSTMR channel 
  * @param  BSTMRx Specifies BSTMR peripheral
  * @return Interrupt status
  */
__STATIC_INLINE uint32_t LL_BSTMR_GetAllITPending(const BSTMR_TypeDef *BSTMRx)
{
    ASSERT_INLINE_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));

    return (READ_BIT(BSTMRx->SR, LL_BSTMR_SR_IT_FLAG_MSK));
}


/**
  * @}
  */ /* BSTMR_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* BSTMR_LL_Exported_Functions */

/**
  * @}
  */ /* BSTMR_LL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BSTMR */

#endif /* _TAE32G58XX_LL_BSTMR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/









