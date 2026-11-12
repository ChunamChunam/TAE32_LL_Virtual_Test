/**
  ******************************************************************************
  * @file    tae32g58xx_ll_iir.h
  * @author  Tai-Action SD Team
  * @brief   Header file for IIR LL module
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
#ifndef _TAE32G58XX_LL_IIR_H_
#define _TAE32G58XX_LL_IIR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(IIR0) || defined(IIR1) || defined(IIR2) || defined(IIR3) || \
    defined(IIR4) || defined(IIR5) 

/** @defgroup IIR_LL IIR LL
  * @brief    IIR LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Constants IIR LL Exported Constants
  * @brief    IIR LL Exported Constants
  * @{
  */


/** @defgroup IIR_LL_EC_Configuration LL IIR Configuration
  * @brief LL IIR Configuration 
  * @{
  */

/**
  * @brief IIR Coef Group Number Definition
  */
#define LL_IIR_CoefGrpNumTypeDef             LL_RSV_DATA_TYPE    

#define LL_IIR_COEF_GRP_NUM_1                (0UL)                /*!< IIR Coef Group Number 1                          */
#define LL_IIR_COEF_GRP_NUMS                 (1UL)                /*!< IIR Coef Group Numbers                           */

#define IS_LL_IIR_COEF_GRP(__VAL__)          (((__VAL__) == LL_IIR_COEF_GRP_NUM_1) || \
                                              ((__VAL__) == LL_IIR_COEF_GRP_NUMS)  )

/**
  * @brief IIR Order Definition
  * @note  IIR0/1/2 Max Order is 4, IIR3/4/5 Max Order is 2
  */
#define LL_IIR_OrderTypeDef                  LL_RSV_DATA_TYPE    

#define LL_IIR_ORDER_1                       (0UL)                /*!< IIR Order 1                                      */
#define LL_IIR_ORDER_2                       (1UL)                /*!< IIR Order 2                                      */
#define LL_IIR_ORDER_3                       (2UL)                /*!< IIR Order 3                                      */
#define LL_IIR_ORDER_4                       (3UL)                /*!< IIR Order 4                                      */

#define IS_LL_IIR_ORDER(__VAL__)             (((__VAL__) == LL_IIR_ORDER_1) || \
                                              ((__VAL__) == LL_IIR_ORDER_2) || \
                                              ((__VAL__) == LL_IIR_ORDER_3) || \
                                              ((__VAL__) == LL_IIR_ORDER_4) )

#define IS_LL_IIR_HIGH_ORDER_MAX4(__VAL__)   (((__VAL__) == LL_IIR_ORDER_1) || \
                                              ((__VAL__) == LL_IIR_ORDER_2) || \
                                              ((__VAL__) == LL_IIR_ORDER_3) || \
                                              ((__VAL__) <= LL_IIR_ORDER_4) )

#define IS_LL_IIR_LOW_ORDER_MAX2(__VAL__)    (((__VAL__) == LL_IIR_ORDER_1) || \
                                              ((__VAL__) == LL_IIR_ORDER_2) )

/**
  * @brief IIR Scale Definition
  */
#define LL_IIR_ScaleTypeDef                  LL_RSV_DATA_TYPE    

#define LL_IIR_SCALE_2_POWER_0               (0UL)                /*!< IIR Scale 2 Power 0                              */
#define LL_IIR_SCALE_2_POWER_1               (1UL)                /*!< IIR Scale 2 Power 1                              */
#define LL_IIR_SCALE_2_POWER_2               (2UL)                /*!< IIR Scale 2 Power 2                              */
#define LL_IIR_SCALE_2_POWER_3               (3UL)                /*!< IIR Scale 2 Power 3                              */
#define LL_IIR_SCALE_2_POWER_4               (4UL)                /*!< IIR Scale 2 Power 4                              */
#define LL_IIR_SCALE_2_POWER_5               (5UL)                /*!< IIR Scale 2 Power 5                              */
#define LL_IIR_SCALE_2_POWER_6               (6UL)                /*!< IIR Scale 2 Power 6                              */
#define LL_IIR_SCALE_2_POWER_7               (7UL)                /*!< IIR Scale 2 Power 7                              */
#define LL_IIR_SCALE_2_POWER_8               (8UL)                /*!< IIR Scale 2 Power 8                              */
#define LL_IIR_SCALE_2_POWER_9               (9UL)                /*!< IIR Scale 2 Power 9                              */
#define LL_IIR_SCALE_2_POWER_10              (10UL)               /*!< IIR Scale 2 Power 10                             */
#define LL_IIR_SCALE_2_POWER_11              (11UL)               /*!< IIR Scale 2 Power 11                             */
#define LL_IIR_SCALE_2_POWER_12              (12UL)               /*!< IIR Scale 2 Power 12                             */
#define LL_IIR_SCALE_2_POWER_13              (13UL)               /*!< IIR Scale 2 Power 13                             */
#define LL_IIR_SCALE_2_POWER_14              (14UL)               /*!< IIR Scale 2 Power 14                             */
#define LL_IIR_SCALE_2_POWER_15              (15UL)               /*!< IIR Scale 2 Power 15                             */
#define LL_IIR_SCALE_2_POWER_16              (16UL)               /*!< IIR Scale 2 Power 16                             */
#define LL_IIR_SCALE_2_POWER_17              (17UL)               /*!< IIR Scale 2 Power 17                             */
#define LL_IIR_SCALE_2_POWER_18              (18UL)               /*!< IIR Scale 2 Power 18                             */
#define LL_IIR_SCALE_2_POWER_19              (19UL)               /*!< IIR Scale 2 Power 19                             */
#define LL_IIR_SCALE_2_POWER_20              (20UL)               /*!< IIR Scale 2 Power 20                             */
#define LL_IIR_SCALE_2_POWER_21              (21UL)               /*!< IIR Scale 2 Power 21                             */
#define LL_IIR_SCALE_2_POWER_22              (22UL)               /*!< IIR Scale 2 Power 22                             */
#define LL_IIR_SCALE_2_POWER_23              (23UL)               /*!< IIR Scale 2 Power 23                             */
#define LL_IIR_SCALE_2_POWER_24              (24UL)               /*!< IIR Scale 2 Power 24                             */
#define LL_IIR_SCALE_2_POWER_25              (25UL)               /*!< IIR Scale 2 Power 25                             */
#define LL_IIR_SCALE_2_POWER_26              (26UL)               /*!< IIR Scale 2 Power 26                             */
#define LL_IIR_SCALE_2_POWER_27              (27UL)               /*!< IIR Scale 2 Power 27                             */
#define LL_IIR_SCALE_2_POWER_28              (28UL)               /*!< IIR Scale 2 Power 28                             */
#define LL_IIR_SCALE_2_POWER_29              (29UL)               /*!< IIR Scale 2 Power 29                             */
#define LL_IIR_SCALE_2_POWER_30              (30UL)               /*!< IIR Scale 2 Power 30                             */
#define LL_IIR_SCALE_2_POWER_31              (31UL)               /*!< IIR Scale 2 Power 31                             */

#define IS_LL_IIR_SCALE_2_POWER(__VAL__)     (((__VAL__) >= LL_IIR_SCALE_2_POWER_0)  && \
                                              ((__VAL__) <= LL_IIR_SCALE_2_POWER_31) )

/**
  * @brief IIR Coefficient A Definition
  */
#define LL_IIR_CoefATypeDef                  LL_RSV_DATA_TYPE    

#define LL_IIR_COEF_A_1                       (0UL)                /*!< IIR Coefficient A1                                      */
#define LL_IIR_COEF_A_2                       (1UL)                /*!< IIR Coefficient A2                                      */
#define LL_IIR_COEF_A_3                       (2UL)                /*!< IIR Coefficient A3                                      */
#define LL_IIR_COEF_A_4                       (3UL)                /*!< IIR Coefficient A4                                      */
#define LL_IIR_COEF_A_NUMS                    (4UL)                /*!< IIR Coefficient A Numbers                               */

/**
  * @brief IIR Coefficient B Definition
  */
#define LL_IIR_CoefBTypeDef                  LL_RSV_DATA_TYPE    

#define LL_IIR_COEF_B_0                       (0UL)                /*!< IIR Coefficient B0                                      */
#define LL_IIR_COEF_B_1                       (1UL)                /*!< IIR Coefficient B1                                      */
#define LL_IIR_COEF_B_2                       (2UL)                /*!< IIR Coefficient B2                                      */
#define LL_IIR_COEF_B_3                       (3UL)                /*!< IIR Coefficient B3                                      */
#define LL_IIR_COEF_B_4                       (4UL)                /*!< IIR Coefficient B4                                      */
#define LL_IIR_COEF_B_5                       (5UL)                /*!< IIR Coefficient B5                                      */
#define LL_IIR_COEF_B_NUMS                    (6UL)                /*!< IIR Coefficient B Numbers                               */

/**
  * @}
  */ /* IIR_LL_EC_Configuration */

/**
  * @}
  */ /* IIR_LL_Exported_Constants */



/* Exported Macros -----------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Macros IIR LL Exported Macros
  * @brief    IIR LL Exported Macros
  * @{
  */

/**
  * @brief  IIR Coef Register offset
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Offset in IIR_Coef_TypeDef type
  * @return IIR_Coef_TypeDef type struct
  */
#define LL_IIR_COEF_REG_OFFSET(__REG__, offset)        \
    (*((volatile IIR_Coef_TypeDef *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) * (sizeof(IIR_Coef_TypeDef)))))))

/**
  * @brief  IIR Coefficient field sign bit mask
  * @note   Derived from the MSB of the IIR coefficient field mask
  */
#define LL_IIR_COEF_SIGN_BIT_MSK     ((IIR0_G0B0R_G0B0COEF_Val) & (~((IIR0_G0B0R_G0B0COEF_Val) >> 1)))

/**
  * @brief  IIR Coefficient field sign extension mask
  * @note   Bits above the IIR coefficient field, used to fill the sign bits
  */
#define LL_IIR_COEF_SIGN_EXT_MSK     ((~((IIR0_G0B0R_G0B0COEF_Val))) & 0xFFFFFFFFUL)

/**
  * @}
  */ /* IIR_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Types IIR LL Exported Types
  * @brief    IIR LL Exported Types
  * @{
  */

/**
  * @}
  */ /* IIR_LL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Functions IIR LL Functions
  * @brief    IIR LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_IIR_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_IIR_ASSERT_INLINE_PARAM == 1)
extern void LL_IIR_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_IIR_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_IIR_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_IIR_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup IIR_LL_EF_Configuration LL IIR Configuration
  * @brief    LL IIR Configuration
  * @{
  */

/**
  * @brief  IIR Soft Reset
  * @param  IIRx Specifies IIR peripheral
  * @return None
  */
__STATIC_INLINE void LL_IIR_SoftReset(IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    SET_BIT(IIRx->CR, IIR0_CR_RST_Msk);
}

/**
  * @brief  Error Interrupt Enable
  * @param  IIRx Specifies IIR peripheral
  * @return None
  */
__STATIC_INLINE void LL_IIR_EnableIT_IEE(IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    SET_BIT(IIRx->CR, IIR0_CR_IEE_Msk);
}

/**
  * @brief  Error Interrupt Disable
  * @param  IIRx Specifies IIR peripheral
  * @return None
  */
__STATIC_INLINE void LL_IIR_DisableIT_IEE(IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    CLEAR_BIT(IIRx->CR, IIR0_CR_IEE_Msk);
}

/**
  * @brief  Judge is Error Interrupt Enable or not
  * @param  IIRx Specifies IIR peripheral
  * @retval 0 Error Interrupt is Disable
  * @retval 1 Error Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_IIR_IsEnabledIT_IEE(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->CR, IIR0_CR_IEE_Msk, IIR0_CR_IEE_Pos));
}

/**
  * @brief  IIR Ordef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  order IIR Order @ref LL_IIR_OrderTypeDef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetOrder(IIR_TypeDef *IIRx, uint32_t Order)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    MODIFY_REG(IIRx->CR, IIR0_CR_ORD_Msk, (((Order) & IIR0_CR_ORD_Val) << IIR0_CR_ORD_Pos));
}

/**
  * @brief  IIR Order Get
  * @param  IIRx Specifies IIR peripheral
  * @return IIR Order @ref LL_IIR_OrderTypeDef
  */
__STATIC_INLINE uint32_t LL_IIR_GetOrder(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->CR, IIR0_CR_ORD_Msk, IIR0_CR_ORD_Pos));
}

/**
  * @brief  IIR Enable
  * @param  IIRx Specifies IIR peripheral
  * @return None
  */
__STATIC_INLINE void LL_IIR_Enable(IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    SET_BIT(IIRx->CR, IIR0_CR_IEN_Msk);
}

/**
  * @brief  IIR Disable
  * @param  IIRx Specifies IIR peripheral
  * @return None
  */
__STATIC_INLINE void LL_IIR_Disable(IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    CLEAR_BIT(IIRx->CR, IIR0_CR_IEN_Msk);
}

/**
  * @brief  Judge is IIR Enable or not
  * @param  IIRx Specifies IIR peripheral
  * @retval 0 IIR is Disable
  * @retval 1 IIR is Enable
  */
__STATIC_INLINE uint32_t LL_IIR_IsEnabled(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)((READ_BIT(IIRx->CR, IIR0_CR_IEN_Msk)) ? (1UL) : (0UL) );
}

/**
  * @brief  Judge is IIR Busy or not
  * @param  IIRx Specifies IIR peripheral
  * @retval 0 IIR is Idle
  * @retval 1 IIR is Busy
  */
__STATIC_INLINE uint32_t LL_IIR_IsBusy(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->ISR, IIR0_ISR_BSY_Msk, IIR0_ISR_BSY_Pos));
}

/**
  * @brief  Judge is Error Interrupt Pending or not
  * @param  IIRx Specifies IIR peripheral
  * @retval 0 isn't Error Interrupt Pending
  * @retval 1 is Error Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_IIR_IsActiveFlag_ERR(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->ISR, IIR0_ISR_ERR_Msk, IIR0_ISR_ERR_Pos));
}

/**
  * @brief  Error Interrupt Pending Clear
  * @param  IIRx Specifies IIR peripheral
  * @return None
  */
__STATIC_INLINE void LL_IIR_ClearFlag_ERR(IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(IIRx->ISR, IIR0_ISR_ERR_Msk);
}

/**
  * @brief  Input Data Write
  * @param  IIRx Specifies IIR peripheral
  * @param  Dat Input Data
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetInputData(IIR_TypeDef *IIRx, int16_t Dat)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(IIRx->IDR, (((uint32_t)Dat) & IIR0_IDR_ID_Val));
}

/**
  * @brief  Output Data Read
  * @param  IIRx Specifies IIR peripheral
  * @return 16 bits Output Data
  */
__STATIC_INLINE int16_t LL_IIR_GetOutputData(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (int16_t)(READ_BIT_SHIFT(IIRx->ODR, IIR0_ODR_OD_Msk, IIR0_ODR_OD_Pos));
}

/**
  * @brief  High-order Output Scale Set
  * @param  IIRx Specifies IIR peripheral
  * @param  Scale High-order Output Scale @ref LL_IIR_ScaleTypeDef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetHighOrderOutputScale(IIR_TypeDef *IIRx, uint32_t Scale)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    MODIFY_REG(IIRx->SCL, IIR0_SCL_OSCL1_Msk, (((Scale) & IIR0_SCL_OSCL1_Val) << IIR0_SCL_OSCL1_Pos));
}

/**
  * @brief  High-order Output Scale Get
  * @param  IIRx Specifies IIR peripheral
  * @return High-order Output Scale @ref LL_IIR_ScaleTypeDef
  */
__STATIC_INLINE uint32_t LL_IIR_GetHighOrderOutputScale(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->SCL, IIR0_SCL_OSCL1_Msk, IIR0_SCL_OSCL1_Pos));
}

/**
  * @brief  High-order Feedback Scale Set
  * @param  IIRx Specifies IIR peripheral
  * @param  Scale High-order Feedback Scale @ref LL_IIR_ScaleTypeDef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetHighOrderFeedbackScale(IIR_TypeDef *IIRx, uint32_t Scale)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    MODIFY_REG(IIRx->SCL, IIR0_SCL_FSCL1_Msk, (((Scale) & IIR0_SCL_FSCL1_Val) << IIR0_SCL_FSCL1_Pos));
}

/**
  * @brief  High-order Feedback Scale Get
  * @param  IIRx Specifies IIR peripheral
  * @return High-order Feedback Scale @ref LL_IIR_ScaleTypeDef
  */
__STATIC_INLINE uint32_t LL_IIR_GetHighOrderFeedbackScale(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->SCL, IIR0_SCL_FSCL1_Msk, IIR0_SCL_FSCL1_Pos));
}

/**
  * @brief  Output Scale Set
  * @param  IIRx Specifies IIR peripheral
  * @param  Scale Output Scale @ref LL_IIR_ScaleTypeDef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetOutputScale(IIR_TypeDef *IIRx, uint32_t Scale)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    MODIFY_REG(IIRx->SCL, IIR0_SCL_OSCL0_Msk, (((Scale) & IIR0_SCL_OSCL0_Val) << IIR0_SCL_OSCL0_Pos));
}

/**
  * @brief  Output Scale Get
  * @param  IIRx Specifies IIR peripheral
  * @return Output Scale @ref LL_IIR_ScaleTypeDef
  */
__STATIC_INLINE uint32_t LL_IIR_GetOutputScale(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->SCL, IIR0_SCL_OSCL0_Msk, IIR0_SCL_OSCL0_Pos));
}

/**
  * @brief  Feedback Scale Set
  * @param  IIRx Specifies IIR peripheral
  * @param  Scale Feedback Scale @ref LL_IIR_ScaleTypeDef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetFeedbackScale(IIR_TypeDef *IIRx, uint32_t Scale)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    MODIFY_REG(IIRx->SCL, IIR0_SCL_FSCL0_Msk, (((Scale) & IIR0_SCL_FSCL0_Val) << IIR0_SCL_FSCL0_Pos));
}

/**
  * @brief  Feedback Scale Get
  * @param  IIRx Specifies IIR peripheral
  * @return Feedback Scale @ref LL_IIR_ScaleTypeDef
  */
__STATIC_INLINE uint32_t LL_IIR_GetFeedbackScale(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    return (uint32_t)(READ_BIT_SHIFT(IIRx->SCL, IIR0_SCL_FSCL0_Msk, IIR0_SCL_FSCL0_Pos));
}

/**
  * @brief  B0 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  B0 B0 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefB0(IIR_TypeDef *IIRx, int32_t B0)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB0R, (((uint32_t)B0) & IIR0_G0B0R_G0B0COEF_Val));
}

/**
  * @brief  B0 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return B0 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefB0(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB0R,
                                             IIR0_G0B0R_G0B0COEF_Msk, IIR0_G0B0R_G0B0COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  B1 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  B1 B1 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefB1(IIR_TypeDef *IIRx, int32_t B1)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB1R, (((uint32_t)B1) & IIR0_G0B1R_G0B1COEF_Val));
}

/**
  * @brief  B1 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return B1 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefB1(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB1R,
                                             IIR0_G0B1R_G0B1COEF_Msk, IIR0_G0B1R_G0B1COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  B2 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  B2 B2 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefB2(IIR_TypeDef *IIRx, int32_t B2)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB2R, (((uint32_t)B2) & IIR0_G0B2R_G0B2COEF_Val));
}

/**
  * @brief  B2 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return B2 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefB2(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB2R,
                                             IIR0_G0B2R_G0B2COEF_Msk, IIR0_G0B2R_G0B2COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  B3 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  B3 B3 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefB3(IIR_TypeDef *IIRx, int32_t B3)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB3R, (((uint32_t)B3) & IIR0_G0B3R_G0B3COEF_Val));
}

/**
  * @brief  B3 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return B3 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefB3(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB3R,
                                             IIR0_G0B3R_G0B3COEF_Msk, IIR0_G0B3R_G0B3COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  B4 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  B4 B4 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefB4(IIR_TypeDef *IIRx, int32_t B4)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB4R, (((uint32_t)B4) & IIR0_G0B4R_G0B4COEF_Val));
}

/**
  * @brief  B4 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return B4 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefB4(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB4R,
                                             IIR0_G0B4R_G0B4COEF_Msk, IIR0_G0B4R_G0B4COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  B5 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  B5 B5 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefB5(IIR_TypeDef *IIRx, int32_t B5)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB5R, (((uint32_t)B5) & IIR0_G0B5R_G0B5COEF_Val));
}

/**
  * @brief  B5 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return B5 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefB5(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNB5R,
                                             IIR0_G0B5R_G0B5COEF_Msk, IIR0_G0B5R_G0B5COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  A1 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  A1 A1 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefA1(IIR_TypeDef *IIRx, int32_t A1)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA1R, (((uint32_t)A1) & IIR0_G0A1R_G0A1COEF_Val));
}

/**
  * @brief  A1 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return A1 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefA1(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA1R,
                                             IIR0_G0A1R_G0A1COEF_Msk, IIR0_G0A1R_G0A1COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  A2 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  A2 A2 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefA2(IIR_TypeDef *IIRx, int32_t A2)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA2R, (((uint32_t)A2) & IIR0_G0A2R_G0A2COEF_Val));
}

/**
  * @brief  A2 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return A2 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefA2(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA2R,
                                             IIR0_G0A2R_G0A2COEF_Msk, IIR0_G0A2R_G0A2COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  A3 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  A3 A3 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefA3(IIR_TypeDef *IIRx, int32_t A3)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA3R, (((uint32_t)A3) & IIR0_G0A3R_G0A3COEF_Val));
}

/**
  * @brief  A3 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return A3 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefA3(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA3R,
                                             IIR0_G0A3R_G0A3COEF_Msk, IIR0_G0A3R_G0A3COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @brief  A4 Coef Set
  * @param  IIRx Specifies IIR peripheral
  * @param  A4 A4 Coef
  * @return None
  */
__STATIC_INLINE void LL_IIR_SetCoefA4(IIR_TypeDef *IIRx, int32_t A4)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    WRITE_REG(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA4R, (((uint32_t)A4) & IIR0_G0A4R_G0A4COEF_Val));
}

/**
  * @brief  A4 Coef Get
  * @param  IIRx Specifies IIR peripheral
  * @return A4 Coef
  */
__STATIC_INLINE int32_t LL_IIR_GetCoefA4(const IIR_TypeDef *IIRx)
{
    ASSERT_INLINE_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    uint32_t coef = (uint32_t)READ_BIT_SHIFT(LL_IIR_COEF_REG_OFFSET(IIRx->G0B0R, LL_IIR_COEF_GRP_NUM_1).GNA4R,
                                             IIR0_G0A4R_G0A4COEF_Msk, IIR0_G0A4R_G0A4COEF_Pos);

    return (int32_t)((coef & LL_IIR_COEF_SIGN_BIT_MSK) ? (coef | LL_IIR_COEF_SIGN_EXT_MSK) : coef);
}

/**
  * @}
  */ /* IIR_LL_EF_Configuration */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* IIR_LL_Exported_Functions */


/**
  * @}
  */ /* IIR_LL */

#endif /* IIR */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_IIR_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

