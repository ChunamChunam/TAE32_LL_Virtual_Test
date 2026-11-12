/**
  ******************************************************************************
  * @file    tae32g58xx_ll_wwdg.h
  * @author  Tai-Action SD Team
  * @brief   Header file of WWDG LL module.
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
#ifndef _TAE32G58XX_LL_WWDG_H_
#define _TAE32G58XX_LL_WWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(WWDG)

/** @defgroup WWDG_LL WWDG Low Layer Driver
  * @brief Low Layer driver for WWDG module.
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Constants WWDG LL Exported Constants
  * @{
  */

/** @defgroup WWDG_LL_EC_EWI_MODE WWDG Early Wakeup Interrupt Mode
  * @{
  */
#define LL_WWDG_EWI_DISABLE       0x00000000UL  /*!< Disable Early Wakeup Interrupt */
#define LL_WWDG_EWI_ENABLE        0x00000001UL  /*!< Enable Early Wakeup Interrupt */
/**
  * @}
  */

/** @defgroup WWDG_LL_EC_BOUNDARY WWDG LL Boundary Constants
  * @{
  */
#define LL_WWDG_PRESCALER_MIN          0x00000000UL  /*!< Minimum prescaler value          */
#define LL_WWDG_PRESCALER_MAX          0x0000FFFFUL  /*!< Maximum prescaler value          */

#define LL_WWDG_WINDOW_MIN             0x00000040UL  /*!< Minimum window value             */
#define LL_WWDG_WINDOW_MAX             0x0000FFFFUL  /*!< Maximum window value             */

#define LL_WWDG_COUNTER_MIN            0x00000040UL  /*!< Minimum counter reload value     */
#define LL_WWDG_COUNTER_MAX            0x0000FFFFUL  /*!< Maximum counter reload value     */
/**
  * @}
  */

/**
  * @}
  */ /* WWDG_LL_Exported_Constants */


/* Exported functions --------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Functions WWDG LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_WWDG_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_WWDG_ASSERT_INLINE_PARAM == 1)
extern void LL_WWDG_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_WWDG_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_WWDG_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_WWDG_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup WWDG_LL_EF_Prescaler Prescaler Configuration Functions
  * @{
  */

/**
  * @brief  Set the WWDG prescaler divider.
  * @param  WWDGx     WWDG Instance.
  * @param  Prescaler Value between @ref LL_WWDG_PRESCALER_MIN and
 *                    @ref LL_WWDG_PRESCALER_MAX.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_SetPrescaler(WWDG_TypeDef *WWDGx, uint32_t Prescaler)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    MODIFY_REG(WWDGx->PSCR, WWDG_PSCR_PSC_Msk, ((Prescaler) << WWDG_PSCR_PSC_Pos));
}

/**
  * @brief  Get the current WWDG prescaler divider.
  * @param  WWDGx WWDG Instance.
  * @return Prescaler value between @ref LL_WWDG_PRESCALER_MIN and
 *                    @ref LL_WWDG_PRESCALER_MAX
  */
__STATIC_INLINE uint32_t LL_WWDG_GetPrescaler(const WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    return (uint32_t)(READ_BIT(WWDGx->PSCR, WWDG_PSCR_PSC_Msk) >> WWDG_PSCR_PSC_Pos);
}

/**
  * @}
  */ /* WWDG_LL_EF_Prescaler */

/** @defgroup WWDG_LL_EF_Window Window Value Configuration Functions
  * @{
  */

/**
  * @brief  Set the WWDG window value.
  * @param  WWDGx  WWDG Instance.
  * @param  Window  Value between @ref LL_WWDG_WINDOW_MIN and
 *                    @ref LL_WWDG_WINDOW_MAX.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_SetWindow(WWDG_TypeDef *WWDGx, uint32_t Window)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    MODIFY_REG(WWDGx->WVR, WWDG_WVR_WV_Msk, ((Window) << WWDG_WVR_WV_Pos));
}

/**
  * @brief  Get the current WWDG window value.
  * @param  WWDGx WWDG Instance.
  * @return Window value between @ref LL_WWDG_WINDOW_MIN and
 *                    @ref LL_WWDG_WINDOW_MAX
  */
__STATIC_INLINE uint32_t LL_WWDG_GetWindow(const WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    return (uint32_t)(READ_BIT(WWDGx->WVR, WWDG_WVR_WV_Msk) >> WWDG_WVR_WV_Pos);
}

/**
  * @}
  */ /* WWDG_LL_EF_Window */

/** @defgroup WWDG_LL_EF_Counter Counter Value Configuration Functions
  * @{
  */

/**
  * @brief  Set the WWDG counter reload value.
  * @param  WWDGx   WWDG Instance.
  * @param  Counter Value between @ref LL_WWDG_COUNTER_MIN and
 *                    @ref LL_WWDG_COUNTER_MAX.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_SetCounter(WWDG_TypeDef *WWDGx, uint32_t Counter)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    MODIFY_REG(WWDGx->CVR, WWDG_CVR_CV_Msk, ((Counter) << WWDG_CVR_CV_Pos));
}

/**
  * @brief  Get the current WWDG counter value.
  * @param  WWDGx WWDG Instance.
  * @return Counter value between @ref LL_WWDG_COUNTER_MIN and
 *                    @ref LL_WWDG_COUNTER_MAX
  */
__STATIC_INLINE uint32_t LL_WWDG_GetCounter(const WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    return (uint32_t)(READ_BIT(WWDGx->CVR, WWDG_CVR_CV_Msk) >> WWDG_CVR_CV_Pos);
}

/**
  * @}
  */ /* WWDG_LL_EF_Counter */

/** @defgroup WWDG_LL_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief  Enable the WWDG Early Wakeup Interrupt.
  * @param  WWDGx WWDG Instance.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_EnableIT_EWIE(WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    SET_BIT(WWDGx->CR, WWDG_CR_EWIE_Msk);
}

/**
  * @brief  Disable the WWDG Early Wakeup Interrupt.
  * @param  WWDGx WWDG Instance.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_DisableIT_EWIE(WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    CLEAR_BIT(WWDGx->CR, WWDG_CR_EWIE_Msk);
}

/**
  * @brief  Check if the WWDG Early Wakeup Interrupt is enabled.
  * @param  WWDGx WWDG Instance.
  * @retval 0: Interrupt disabled, 1: Interrupt enabled
  */
__STATIC_INLINE uint32_t LL_WWDG_IsEnabledIT_EWIE(const WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    return ((READ_BIT(WWDGx->CR, WWDG_CR_EWIE_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if WWDG Early Wakeup Interrupt flag is set.
  * @param  WWDGx WWDG Instance.
  * @retval 0: No EWI, 1: EWI occurred
  */
__STATIC_INLINE uint32_t LL_WWDG_IsActiveFlag_EWIF(const WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    return ((READ_BIT(WWDGx->ISR, WWDG_ISR_EWIF_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Clear WWDG Early Wakeup Interrupt flag.
  * @param  WWDGx WWDG Instance.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_ClearFlag_EWIF(WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    WRITE_REG(WWDGx->ISR, WWDG_ISR_EWIF_Msk);
}

/**
  * @}
  */ /* WWDG_LL_EF_IT_Management */

/** @defgroup WWDG_LL_EF_Enable WWDG Enable/Disable Functions
  * @{
  */

/**
  * @brief  Enable WWDG counter.
  * @param  WWDGx WWDG Instance.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_Enable(WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    SET_BIT(WWDGx->CR, WWDG_CR_WEN_Msk);
}

/**
  * @brief  Disable WWDG counter.
  * @param  WWDGx WWDG Instance.
  * @return None
  */
__STATIC_INLINE void LL_WWDG_Disable(WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    CLEAR_BIT(WWDGx->CR, WWDG_CR_WEN_Msk);
}

/**
  * @brief  Check if WWDG is enabled.
  * @param  WWDGx WWDG Instance.
  * @retval 0: WWDG disabled, 1: WWDG enabled
  */
__STATIC_INLINE uint32_t LL_WWDG_IsEnabled(const WWDG_TypeDef *WWDGx)
{
    ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));

    return ((READ_BIT(WWDGx->CR, WWDG_CR_WEN_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @}
  */ /* WWDG_LL_EF_Enable */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* IWDG_LL_Exported_Functions */

/**
  * @}
  */ /* WWDG_LL */

#endif /* WWDG */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_WWDG_H_ */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE***********/

