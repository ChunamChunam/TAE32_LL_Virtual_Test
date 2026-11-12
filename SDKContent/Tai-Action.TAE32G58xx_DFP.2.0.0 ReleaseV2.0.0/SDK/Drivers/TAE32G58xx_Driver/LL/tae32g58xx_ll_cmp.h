/**
  ******************************************************************************
  * @file    tae32g58xx_ll_cmp.h
  * @author  Tai-Action SD Team
  * @brief   Header file for CMP LL module
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
#ifndef _TAE32G58XX_LL_CMP_H_
#define _TAE32G58XX_LL_CMP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(CMP0) || defined(CMP1) || defined(CMP2) || defined(CMP3) || defined(CMP4) || \
    defined(CMP5) || defined(CMP6) || defined(CMP7) || defined(CMP8)

/** @defgroup CMP_LL CMP LL
  * @brief    CMP LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Constants CMP LL Exported Constants
  * @brief    CMP LL Exported Constants
  * @{
  */


/** @defgroup CMP_LL_EC_Configuration LL CMP Configuration
  * @brief LL CMP Configuration 
  * @{
  */

/** @name LL_CMP_OutputPolTypeDef
  * @brief CMP Output Polarity Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_CMP_OutputPolTypeDef                uint32_t    
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_CMP_OutputPolTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_CMP_OUTPUT_POL_NONINVERTED          (0UL)                /*!< CMP output polarity is not inverted              */
#define LL_CMP_OUTPUT_POL_INVERTED             (1UL)                /*!< CMP output polarity is inverted                  */

#define IS_LL_CMP_OUTPUT_POL(__VAL__)          (((__VAL__) == LL_CMP_OUTPUT_POL_NONINVERTED) || \
                                                ((__VAL__) == LL_CMP_OUTPUT_POL_INVERTED) )
/** @} */

/** @name LL_CMP_BlkEvtTypeDef
  * @brief CMP Blank Event Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_CMP_BlkEvtTypeDef                   uint32_t    
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_CMP_BlkEvtTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_CMP_BLK_EVT_NONE                    (0UL)                /*!< CMP Blank Event None                             */
#define LL_CMP_BLK_EVT_TMR0_OC0                (1UL)                /*!< CMP Blank Event TMR0 OC0                         */
#define LL_CMP_BLK_EVT_TMR1_OC0                (2UL)                /*!< CMP Blank Event TMR1 OC0                         */
#define LL_CMP_BLK_EVT_TMR2_OC0                (3UL)                /*!< CMP Blank Event TMR2 OC0                         */
#define LL_CMP_BLK_EVT_TMR3_OC0                (4UL)                /*!< CMP Blank Event TMR3 OC0                         */
#define LL_CMP_BLK_EVT_TMR4_OC0                (5UL)                /*!< CMP Blank Event TMR4 OC0                         */
#define LL_CMP_BLK_EVT_TMR9_OC0                (6UL)                /*!< CMP Blank Event TMR9 OC0                         */
#define LL_CMP_BLK_EVT_TMR10_OC0               (7UL)                /*!< CMP Blank Event TMR10 OC0                        */

#define IS_LL_CMP_BLK_EVT(__VAL__)             (((__VAL__) == LL_CMP_BLK_EVT_NONE)      || \
                                                ((__VAL__) == LL_CMP_BLK_EVT_TMR0_OC0)  || \
                                                ((__VAL__) == LL_CMP_BLK_EVT_TMR1_OC0)  || \
                                                ((__VAL__) == LL_CMP_BLK_EVT_TMR2_OC0)  || \
                                                ((__VAL__) == LL_CMP_BLK_EVT_TMR3_OC0)  || \
                                                ((__VAL__) == LL_CMP_BLK_EVT_TMR4_OC0)  || \
                                                ((__VAL__) == LL_CMP_BLK_EVT_TMR9_OC0)  || \
                                                ((__VAL__) == LL_CMP_BLK_EVT_TMR10_OC0) )
/** @} */

/** @name LL_CMP_PosiInSrcTypeDef
  * @brief CMP Positive IN Source Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_CMP_PosiInSrcTypeDef                uint32_t    
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_CMP_PosiInSrcTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_CMP_POSI_IN_SRC_CMP_INP0            (0UL)                /*!< CMP Positive IN Source CMP_INP0                  */
#define LL_CMP_POSI_IN_SRC_CMP_INP1            (1UL)                /*!< CMP Positive IN Source CMP_INP1                  */

#define IS_LL_CMP_POSI_IN_SRC_CMP(__VAL__)     (((__VAL__) == LL_CMP_POSI_IN_SRC_CMP_INP0) || \
                                                ((__VAL__) == LL_CMP_POSI_IN_SRC_CMP_INP1) )
/** @} */

/** @name LL_CMP_NegInSrcTypeDef
  * @brief CMP Negative IN Source Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_CMP_NegInSrcTypeDef                 uint32_t    
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_CMP_NegInSrcTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_CMP_NEG_IN_SRC_CMP_INM0             (0UL)                /*!< CMP Negative IN Source CMP_INM0                  */
#define LL_CMP_NEG_IN_SRC_CMP_INM1             (1UL)                /*!< CMP Negative IN Source CMP_INM1                  */
#define LL_CMP_NEG_IN_SRC_DACy_OUT             (2UL)                /*!< CMP Negative IN Source DACy_OUT                  */
#define LL_CMP_NEG_IN_SRC_DACz_OUT             (3UL)                /*!< CMP Negative IN Source DACz_OUT                  */

#define IS_LL_CMP_NEG_IN_SRC(__VAL__)          (((__VAL__) == LL_CMP_NEG_IN_SRC_CMP_INM0) || \
                                                ((__VAL__) == LL_CMP_NEG_IN_SRC_CMP_INM1) || \
                                                ((__VAL__) == LL_CMP_NEG_IN_SRC_DACy_OUT) || \
                                                ((__VAL__) == LL_CMP_NEG_IN_SRC_DACz_OUT) )
/** @} */

/** @name LL_CMP_HystTypeDef
  * @brief CMP Hysteresis Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_CMP_HystTypeDef                     uint32_t    
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_CMP_HystTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_CMP_HYST_0mv                        (0UL)                /*!< CMP Hysteresis 0mv                               */
#define LL_CMP_HYST_10mv                       (1UL)                /*!< CMP Hysteresis 10mv                              */
#define LL_CMP_HYST_20mv                       (2UL)                /*!< CMP Hysteresis 20mv                              */
#define LL_CMP_HYST_30mv                       (3UL)                /*!< CMP Hysteresis 30mv                              */

#define IS_LL_CMP_HYST(__VAL__)                (((__VAL__) == LL_CMP_HYST_0mv)  || \
                                                ((__VAL__) == LL_CMP_HYST_10mv) || \
                                                ((__VAL__) == LL_CMP_HYST_20mv) || \
                                                ((__VAL__) == LL_CMP_HYST_30mv) )
/** @} */

/** @name LL_CMP_EdgeITModeTypeDef
  * @brief CMP Edge interrupt Mode Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_CMP_EdgeITModeTypeDef               uint32_t    
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_CMP_EdgeITModeTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_CMP_EDGE_IT_MODE_RISING             (BIT(0))                /*!< CMP Rising Edge interrupt Mode                */
#define LL_CMP_EDGE_IT_MODE_FALLING            (BIT(1))                /*!< CMP Falling Edge interrupt Mode               */

#define IS_LL_CMP_EDGE_IT_MODE(__VAL__)        (((__VAL__) == LL_CMP_EDGE_IT_MODE_RISING) || \
                                                ((__VAL__) == LL_CMP_EDGE_IT_MODE_FALLING) )
/** @} */

/**
  * @}
  */ /* CMP_LL_EC_Configuration */

/**
  * @}
  */ /* CMP_LL_Exported_Constants */



/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Macros CMP LL Exported Macros
  * @brief    CMP LL Exported Macros
  * @{
  */


/**
  * @}
  */ /* CMP_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Types CMP LL Exported Types
  * @brief    CMP LL Exported Types
  * @{
  */

/**
  * @}
  */ /* CMP_LL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Functions CMP LL Functions
  * @brief    CMP LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_CMP_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_CMP_ASSERT_INLINE_PARAM == 1)
extern void LL_CMP_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_CMP_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_CMP_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_CMP_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup CMP_LL_EF_Configuration LL CMP Configuration
  * @brief    LL CMP Configuration
  * @{
  */

/**
  * @brief  Output Invert Enable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_EnableOutputInvert(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    SET_BIT(CMPx->CR, CMP0_CR_OPOL_Msk);
}

/**
  * @brief  Output Invert Disable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_DisableOutputInvert(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CLEAR_BIT(CMPx->CR, CMP0_CR_OPOL_Msk);
}

/**
  * @brief  Judge is Output Invert Enable or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 is Output Invert Disable
  * @retval 1 is Output Invert Enable
  */
__STATIC_INLINE uint32_t LL_CMP_IsOutputInvertEnable(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_OPOL_Msk, CMP0_CR_OPOL_Pos));
}

/**
  * @brief  Output Polarity Set
  * @param  CMPx Specifies CMP peripheral
  * @param  Polarity CMP Output Polarity @ref LL_CMP_OutputPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_SetOutputPolarity(CMP_TypeDef *CMPx, uint32_t Polarity)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    MODIFY_REG(CMPx->CR, CMP0_CR_OPOL_Msk, (((Polarity) & CMP0_CR_OPOL_Val) << CMP0_CR_OPOL_Pos));
}

/**
  * @brief  Output Polarity Get
  * @param  CMPx Specifies CMP peripheral
  * @return CMP Output Polarity @ref LL_CMP_OutputPolTypeDef
  */
__STATIC_INLINE uint32_t LL_CMP_GetOutputPolarity(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_OPOL_Msk, CMP0_CR_OPOL_Pos));
}


/**
  * @brief  Output Synchronization Enable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_EnableOutputSync(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    SET_BIT(CMPx->CR, CMP0_CR_ODEB_Msk);
}

/**
  * @brief  Output Synchronization Disable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_DisableOutputSync(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CLEAR_BIT(CMPx->CR, CMP0_CR_ODEB_Msk);
}

/**
  * @brief  Judge is Output Synchronization Enable or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 is Output Synchronization Disable
  * @retval 1 is Output Synchronization Enable
  */
__STATIC_INLINE uint32_t LL_CMP_IsOutputSyncEnable(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_ODEB_Msk, CMP0_CR_ODEB_Pos));
}

/**
  * @brief  Blank Event Set
  * @param  CMPx Specifies CMP peripheral
  * @param  Evt Blank Event @ref LL_CMP_BlkEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_SetOutputBlankingSource(CMP_TypeDef *CMPx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    MODIFY_REG(CMPx->CR, CMP0_CR_BLANKING_Msk, (((Evt) & CMP0_CR_BLANKING_Val) << CMP0_CR_BLANKING_Pos));
}

/**
  * @brief  Blank Event Get
  * @param  CMPx Specifies CMP peripheral
  * @return Blank Event @ref LL_CMP_BlkEvtTypeDef
  */
__STATIC_INLINE uint32_t LL_CMP_GetOutputBlankingSource(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_BLANKING_Msk, CMP0_CR_BLANKING_Pos));
}

/**
  * @brief  CMP Negative In Source Set
  * @param  CMPx Specifies CMP peripheral
  * @param  Src CMP Negative In Source @ref LL_CMP_NegInSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_SetInputMinus(CMP_TypeDef *CMPx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    MODIFY_REG(CMPx->CR, CMP0_CR_INM_Msk, (((Src) & CMP0_CR_INM_Val) << CMP0_CR_INM_Pos));
}

/**
  * @brief  CMP Negative In Source Get
  * @param  CMPx Specifies CMP peripheral
  * @return CMP Negative In Source @ref LL_CMP_NegInSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_CMP_GetInputMinus(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_INM_Msk, CMP0_CR_INM_Pos));
}

/**
  * @brief  CMP Hysteresis Set
  * @param  CMPx Specifies CMP peripheral
  * @param  Hyst CMP Hysteresis @ref LL_CMP_HystTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_SetInputHysteresis(CMP_TypeDef *CMPx, uint32_t Hyst)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    MODIFY_REG(CMPx->CR, CMP0_CR_HYST_Msk, (((Hyst) & CMP0_CR_HYST_Val) << CMP0_CR_HYST_Pos));
}

/**
  * @brief  CMP Hysteresis Get
  * @param  CMPx Specifies CMP peripheral
  * @return CMP Hysteresis @ref LL_CMP_HystTypeDef
  */
__STATIC_INLINE uint32_t LL_CMP_GetInputHysteresis(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_HYST_Msk, CMP0_CR_HYST_Pos));
}

/**
  * @brief  CMP Positive In Source Set
  * @param  CMPx Specifies CMP peripheral
  * @param  Src CMP Positive In Source @ref LL_CMP_PosiInSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_SetInputPlus(CMP_TypeDef *CMPx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    MODIFY_REG(CMPx->CR, CMP0_CR_INP_Msk, (((Src) & CMP0_CR_INP_Val) << CMP0_CR_INP_Pos));
}


/**
  * @brief  CMP Positive In Source Get
  * @param  CMPx Specifies CMP peripheral
  * @return CMP Positive In Source @ref LL_CMP_PosiInSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_CMP_GetInputPlus(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_INP_Msk, CMP0_CR_INP_Pos));
}

/**
  * @brief  CMP Software Blanking Enable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_EnableSwBlanking(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    SET_BIT(CMPx->CR, CMP0_CR_CBLK_Msk);
}

/**
  * @brief  CMP Software Blanking Disable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_DisableSwBlanking(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CLEAR_BIT(CMPx->CR, CMP0_CR_CBLK_Msk);
}

/**
  * @brief  Judge is CMP Software Blanking Enable or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 is Software Blanking Disable
  * @retval 1 is Software Blanking Enable
  */
__STATIC_INLINE uint32_t LL_CMP_IsSwBlankingEnable(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_CBLK_Msk, CMP0_CR_CBLK_Pos));
}

/**
  * @brief  CMP Enable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_Enable(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    SET_BIT(CMPx->CR, CMP0_CR_CEN_Msk);
}

/**
  * @brief  CMP Disable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_Disable(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CLEAR_BIT(CMPx->CR, CMP0_CR_CEN_Msk);
}


/**
  * @brief  Judge is CMP Enable or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 CMP is Disable
  * @retval 1 CMP is Enable
  */
__STATIC_INLINE uint32_t LL_CMP_IsEnabled(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->CR, CMP0_CR_CEN_Msk, CMP0_CR_CEN_Pos));
}

/**
  * @brief  CMP Output Debounce Set
  * @param  CMPx Specifies CMP peripheral
  * @param  Dbc CMP Output Debounce
  * @return None
  */
__STATIC_INLINE void LL_CMP_SetOutputDebounce(CMP_TypeDef *CMPx, uint32_t Dbc)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    WRITE_REG(CMPx->DEBR, ((Dbc) & CMP0_DEBR_DEB_Val));
}

/**
  * @brief  CMP Output Debounce Get
  * @param  CMPx Specifies CMP peripheral
  * @return CMP Output Debounce
  */
__STATIC_INLINE uint32_t LL_CMP_GetOutputDebounce(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->DEBR, CMP0_DEBR_DEB_Msk, CMP0_DEBR_DEB_Pos));
}

/**
  * @brief  CMP Falling Edge Interrupt Enable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_EnableIT_FALIE(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    SET_BIT(CMPx->IER, CMP0_IER_FALIE_Msk);
}

/**
  * @brief  CMP Falling Edge Interrupt Disable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_DisableIT_FALIE(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CLEAR_BIT(CMPx->IER, CMP0_IER_FALIE_Msk);
}

/**
  * @brief  Judge is CMP Falling Edge Interrupt Enable or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 CMP Falling Edge Interrupt is Disable
  * @retval 1 CMP Falling Edge Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_CMP_IsEnabledIT_FALIE(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->IER, CMP0_IER_FALIE_Msk, CMP0_IER_FALIE_Pos));
}

/**
  * @brief  CMP Rising Edge Interrupt Enable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_EnableIT_RISIE(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    SET_BIT(CMPx->IER, CMP0_IER_RISIE_Msk);
}

/**
  * @brief  CMP Rising Edge Interrupt Disable
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_DisableIT_RISIE(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CLEAR_BIT(CMPx->IER, CMP0_IER_RISIE_Msk);
}

/**
  * @brief  Judge is CMP Rising Edge Interrupt Enable or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 CMP Rising Edge Interrupt is Disable
  * @retval 1 CMP Rising Edge Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_CMP_IsEnabledIT_RISIE(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->IER, CMP0_IER_RISIE_Msk, CMP0_IER_RISIE_Pos));
}

/**
  * @brief  CMP Output Status Read Before Polarity
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 CMP output low
  * @retval 1 CMP output high
  */
__STATIC_INLINE uint32_t LL_CMP_ReadOutputLevel(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->ISR, CMP0_ISR_OVAL_Msk, CMP0_ISR_OVAL_Pos));
}

/**
  * @brief  Judge is CMP Falling Edge Interrupt Pending or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 isn't CMP Falling Edge Interrupt Pending
  * @retval 1 is CMP Falling Edge Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CMP_IsActiveFlag_FAL(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->ISR, CMP0_ISR_FAL_Msk, CMP0_ISR_FAL_Pos));
}

/**
  * @brief  CMP Falling Edge Interrupt Pending Clear
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_ClearFlag_FAL(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    WRITE_REG(CMPx->ISR, CMP0_ISR_FAL_Msk);
}

/**
  * @brief  Judge is CMP Rising Edge Interrupt Pending or not
  * @param  CMPx Specifies CMP peripheral
  * @retval 0 isn't CMP Rising Edge Interrupt Pending
  * @retval 1 is CMP Rising Edge Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CMP_IsActiveFlag_RIS(const CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    return (uint32_t)(READ_BIT_SHIFT(CMPx->ISR, CMP0_ISR_RIS_Msk, CMP0_ISR_RIS_Pos));
}

/**
  * @brief  CMP Rising Edge Interrupt Pending Clear
  * @param  CMPx Specifies CMP peripheral
  * @return None
  */
__STATIC_INLINE void LL_CMP_ClearFlag_RIS(CMP_TypeDef *CMPx)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    WRITE_REG(CMPx->ISR, CMP0_ISR_RIS_Msk);
}
/**
  * @}
  */ /* CMP_LL_EF_Configuration */

/** @defgroup CMP_LL_EF_IT_Management LL CMP Interrupt Management
  * @brief LL CMP Interrupt Management
  * @{
  */

/**
  * @brief  CMP Interrupt enable
  * @param  CMPx Specifies CMP peripheral
  * @param  Mask Mask to enable @ref LL_CMP_EdgeITModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_EnableIT(CMP_TypeDef *CMPx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    SET_BIT(CMPx->IER, Mask);
}

/**
  * @brief  CMP Interrupt disable
  * @param  CMPx Specifies CMP peripheral
  * @param  Mask Mask to disable @ref LL_CMP_EdgeITModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_DisableIT(CMP_TypeDef *CMPx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CLEAR_BIT(CMPx->IER, Mask);
}

/**
  * @brief  Check if CMP Interrupt is enabled or disabled
  * @param  CMPx Specifies CMP peripheral
  * @param  Mask Mask to check @ref LL_CMP_EdgeITModeTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_CMP_IsEnabledIT(const CMP_TypeDef *CMPx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(CMPx->IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  CMPx Specifies CMP peripheral
  * @param  Mask Mask to clear @ref LL_CMP_ISR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CMP_ClearFlag(CMP_TypeDef *CMPx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    WRITE_REG(CMPx->ISR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  CMPx Specifies CMP peripheral
  * @param  Mask Mask to check @ref LL_CMP_ISR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CMP_IsActiveFlag(const CMP_TypeDef *CMPx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(CMPx->ISR, Mask) == (Mask)) ? 1UL : 0UL);
}


/**
  * @}
  */ /* CMP_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* CMP_LL_Exported_Functions */


/**
  * @}
  */ /* CMP_LL */

#endif /* CMP */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_CMP_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

