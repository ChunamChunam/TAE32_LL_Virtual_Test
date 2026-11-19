/**
  ******************************************************************************
  * @file    tae32f561x_ll_iwdg.h
  * @author  Tai-Action SD Team
  * @brief   Header file of IWDG LL module.
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
#ifndef _TAE32F561X_LL_IWDG_H_
#define _TAE32F561X_LL_IWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_ll_def.h"

/** @addtogroup TAE32F561x_LL_Driver
  * @{
  */

#if defined(IWDG)

/** @defgroup IWDG_LL IWDG Low Layer Driver
  * @brief Low Layer driver for IWDG module.
  * @{
  */


/* Private constants ---------------------------------------------------------*/
/** @defgroup IWDG_LL_Private_Constants IWDG LL Private Constants
  * @{
  */
#define LL_IWDG_KEY_RELOAD                 0x0000AAAAUL              /*!< IWDG Reload Counter Enable   */
#define LL_IWDG_KEY_ENABLE                 0x0000CCCCUL              /*!< IWDG Peripheral Enable       */
#define LL_IWDG_KEY_WR_ACCESS_ENABLE       0x00003FACUL              /*!< IWDG KR Write Access Enable  */
#define LL_IWDG_KEY_WR_ACCESS_DISABLE      0x00000000UL              /*!< IWDG KR Write Access Disable */
#define LL_IWDG_KEY_DISABLE               0x0000DDDDUL              /*!< IWDG Peripheral Disable      */
/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Constants IWDG LL Exported Constants
  * @{
  */

/** @defgroup IWDG_LL_EC_PRESCALER Prescaler Divider
  * @{
  */
#define LL_IWDG_PRESCALER_4                0x00000000UL              /*!< Divider by 4   */
#define LL_IWDG_PRESCALER_8                0x00000001UL              /*!< Divider by 8   */
#define LL_IWDG_PRESCALER_16               0x00000002UL              /*!< Divider by 16  */
#define LL_IWDG_PRESCALER_32               0x00000003UL              /*!< Divider by 32  */
#define LL_IWDG_PRESCALER_64               0x00000004UL              /*!< Divider by 64  */
#define LL_IWDG_PRESCALER_128              0x00000005UL              /*!< Divider by 128 */
#define LL_IWDG_PRESCALER_256              0x00000006UL              /*!< Divider by 256 */
#define LL_IWDG_PRESCALER_512              0x00000007UL              /*!< Divider by 512 */
/**
  * @}
  */

/** @defgroup IWDG_LL_EC_MODE Operating Mode
  * @{
  */
#define LL_IWDG_MODE_RESET                 0x00000000UL              /*!< Reset mode on timeout        */
#define LL_IWDG_MODE_INTERRUPT             0x00000001UL              /*!< Interrupt mode on timeout    */
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Functions IWDG LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_IWDG_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_IWDG_ASSERT_INLINE_PARAM == 1)
extern void LL_IWDG_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_IWDG_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_IWDG_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_IWDG_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup IWDG_LL_EF_Key Key Management Functions
  * @{
  */

/**
  * @brief  Enable the Independent Watchdog
  * @note   Writing the enable key starts the IWDG counter. LSI is forced ON.
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_Enable(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    WRITE_REG(IWDGx->KEYR, LL_IWDG_KEY_ENABLE);
}

/**
  * @brief  Reload IWDG counter with value defined in the reload register
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_ReloadCounter(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    WRITE_REG(IWDGx->KEYR, LL_IWDG_KEY_RELOAD);
}

/**
  * @brief  Enable write access to IWDG_PR, IWDG_RLR and IWDG_CR registers
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_EnableWriteAccess(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    WRITE_REG(IWDGx->KEYR, LL_IWDG_KEY_WR_ACCESS_ENABLE);
}

/**
  * @brief  Disable write access to IWDG_PR, IWDG_RLR and IWDG_CR registers
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_DisableWriteAccess(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    WRITE_REG(IWDGx->KEYR, LL_IWDG_KEY_WR_ACCESS_DISABLE);
}

/**
  * @brief  Disable the Independent Watchdog (stop counting, equivalent to KEY_STOP)
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_Disable(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    WRITE_REG(IWDGx->KEYR, LL_IWDG_KEY_DISABLE);
}

/**
  * @}
  */

/** @defgroup IWDG_LL_EF_Prescaler Prescaler Configuration Functions
  * @{
  */

/**
  * @brief  Set the prescaler of the IWDG
  * @param  IWDGx IWDG Instance
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_IWDG_PRESCALER_4
  *         @arg @ref LL_IWDG_PRESCALER_8
  *         @arg @ref LL_IWDG_PRESCALER_16
  *         @arg @ref LL_IWDG_PRESCALER_32
  *         @arg @ref LL_IWDG_PRESCALER_64
  *         @arg @ref LL_IWDG_PRESCALER_128
  *         @arg @ref LL_IWDG_PRESCALER_256
  *         @arg @ref LL_IWDG_PRESCALER_512
  * @return None
  * @note   IWDG_PSCR is write-protected; call LL_IWDG_EnableWriteAccess() first.
  */
__STATIC_INLINE void LL_IWDG_SetPrescaler(IWDG_TypeDef *IWDGx, uint32_t Prescaler)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    MODIFY_REG(IWDGx->PSCR, IWDG_PSCR_PSC_Msk, (Prescaler << IWDG_PSCR_PSC_Pos));
}

/**
  * @brief  Get the current prescaler of the IWDG
  * @param  IWDGx IWDG Instance
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_IWDG_PRESCALER_4
  *         @arg @ref LL_IWDG_PRESCALER_8
  *         @arg @ref LL_IWDG_PRESCALER_16
  *         @arg @ref LL_IWDG_PRESCALER_32
  *         @arg @ref LL_IWDG_PRESCALER_64
  *         @arg @ref LL_IWDG_PRESCALER_128
  *         @arg @ref LL_IWDG_PRESCALER_256
  *         @arg @ref LL_IWDG_PRESCALER_512
  */
__STATIC_INLINE uint32_t LL_IWDG_GetPrescaler(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return (uint32_t)(READ_BIT(IWDGx->PSCR, IWDG_PSCR_PSC_Msk) >> IWDG_PSCR_PSC_Pos);
}

/**
  * @}
  */

/** @defgroup IWDG_LL_EF_Reload Reload Value Configuration Functions
  * @{
  */

/**
  * @brief  Set the IWDG down-counter reload value
  * @param  IWDGx IWDG Instance
  * @param  Counter Value between Min_Data=0 and Max_Data=0xFFFF (RLR[15:0])
  * @return None
  * @note   IWDG_RLR is write-protected; call LL_IWDG_EnableWriteAccess() first.
  */
__STATIC_INLINE void LL_IWDG_SetReloadCounter(IWDG_TypeDef *IWDGx, uint32_t Counter)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    MODIFY_REG(IWDGx->RLR, IWDG_RLR_RLV_Msk, (Counter << IWDG_RLR_RLV_Pos));
}

/**
  * @brief  Get the IWDG down-counter reload value
  * @param  IWDGx IWDG Instance
  * @return Value between Min_Data=0 and Max_Data=0xFFFF (RLR[15:0])
  */
__STATIC_INLINE uint32_t LL_IWDG_GetReloadCounter(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return (uint32_t)(READ_BIT(IWDGx->RLR, IWDG_RLR_RLV_Msk) >> IWDG_RLR_RLV_Pos);
}

/**
  * @}
  */

/** @defgroup IWDG_LL_EF_Mode Operating Mode Configuration Functions
  * @{
  */

/**
  * @brief  Set the IWDG operating mode (reset or interrupt)
  * @param  IWDGx IWDG Instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_IWDG_MODE_RESET
  *         @arg @ref LL_IWDG_MODE_INTERRUPT
  * @return None
  * @note   IWDG_CR is write-protected; call LL_IWDG_EnableWriteAccess() first.
  */
__STATIC_INLINE void LL_IWDG_SetMode(IWDG_TypeDef *IWDGx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    MODIFY_REG(IWDGx->CR, IWDG_CR_MODE_Msk, (Mode << IWDG_CR_MODE_Pos));
}

/**
  * @brief  Get the current IWDG operating mode
  * @param  IWDGx IWDG Instance
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_IWDG_MODE_RESET
  *         @arg @ref LL_IWDG_MODE_INTERRUPT
  */
__STATIC_INLINE uint32_t LL_IWDG_GetMode(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return (uint32_t)(READ_BIT(IWDGx->CR, IWDG_CR_MODE_Msk) >> IWDG_CR_MODE_Pos);
}

/**
  * @}
  */

/** @defgroup IWDG_LL_EF_IT_Management Interrupt Management
  * @brief LL IWDG Interrupt Management
  * @{
  */

/**
  * @brief  Enable the IWDG timeout interrupt
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_EnableIT_TOIE(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    SET_BIT(IWDGx->CR, IWDG_CR_TOIE_Msk);
}

/**
  * @brief  Disable the IWDG timeout interrupt
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_DisableIT_TOIE(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    CLEAR_BIT(IWDGx->CR, IWDG_CR_TOIE_Msk);
}

/**
  * @brief  Check if the IWDG timeout interrupt is enabled
  * @param  IWDGx IWDG Instance
  * @retval 0: Interrupt disabled, 1: Interrupt enabled
  */
__STATIC_INLINE uint32_t LL_IWDG_IsEnabledIT_TOIE(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return ((READ_BIT(IWDGx->CR, IWDG_CR_TOIE_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if IWDG timeout interrupt flag is set
  * @param  IWDGx IWDG Instance
  * @retval 0: No timeout, 1: Timeout occurred
  */
__STATIC_INLINE uint32_t LL_IWDG_IsActiveFlag_TOIF(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return ((READ_BIT(IWDGx->SR, IWDG_SR_TOIF_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Clear IWDG timeout interrupt flag
  * @param  IWDGx IWDG Instance
  * @return None
  */
__STATIC_INLINE void LL_IWDG_ClearFlag_TOIF(IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    WRITE_REG(IWDGx->SR, IWDG_SR_TOIF_Msk);
}

/**
  * @brief  Check if reload value update is in progress
  * @param  IWDGx IWDG Instance
  * @retval 0: Update complete, 1: Update in progress
  */
__STATIC_INLINE uint32_t LL_IWDG_IsActiveFlag_RLVUPD(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return ((READ_BIT(IWDGx->SR, IWDG_SR_RLVUPD_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if prescaler value update is in progress
  * @param  IWDGx IWDG Instance
  * @retval 0: Update complete, 1: Update in progress
  */
__STATIC_INLINE uint32_t LL_IWDG_IsActiveFlag_PSCUPD(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return ((READ_BIT(IWDGx->SR, IWDG_SR_PSCUPD_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if IWDG is ready (no reload or prescaler update in progress)
  * @param  IWDGx IWDG Instance
  * @retval 0: Not ready (busy), 1: Ready
  */
__STATIC_INLINE uint32_t LL_IWDG_IsReady(const IWDG_TypeDef *IWDGx)
{
    ASSERT_INLINE_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));

    return ((READ_BIT(IWDGx->SR, (IWDG_SR_RLVUPD_Msk | IWDG_SR_PSCUPD_Msk)) == 0UL) ? 1UL : 0UL);
}

/**
  * @}
  */ /* IWDG_LL_EF_IT_Management  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */  /* IWDG_LL_Exported_Functions */

/**
  * @}
  */ /* IWDG_LL */

#endif /* IWDG */

/**
  * @}
  */ /* TAE32F561x_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32F561X_LL_IWDG_H_ */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/
