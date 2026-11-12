/**
  ******************************************************************************
  * @file    tae32g58xx_ll_dac.h
  * @author  Tai-Action SD Team
  * @brief   Header file for DAC LL module
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
#ifndef _TAE32G58XX_LL_DAC_H_
#define _TAE32G58XX_LL_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(DAC0) || defined(DAC1) || defined(DAC2) || defined(DAC3) || defined(DAC4) || \
    defined(DAC5) || defined(DAC6) || defined(DAC7) || defined(DAC8) 

/** @defgroup DAC_LL DAC LL
  * @brief    DAC LL Module Driver
  * @{
  */

/* Exported Constants --------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Constants DAC LL Exported Constants
  * @brief    DAC LL Exported Constants
  * @{
  */


/** @defgroup DAC_LL_EC_Configuration LL DAC Configuration
  * @brief LL DAC Configuration 
  * @{
  */

/** @name LL_DAC_WaveGenDirTypeDef
  * @brief DAC Sawtooth/Triangle Wave Generate Direction Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_DAC_WaveGenDirTypeDef                   uint32_t    
#else
typedef uint32_t LL_DAC_WaveGenDirTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_DAC_WAVE_GEN_DIR_DEC                    (0UL)                /*!< DAC Wave Generate Direction Decrease             */
#define LL_DAC_WAVE_GEN_DIR_INC                    (1UL)                /*!< DAC Wave Generate Direction Increase             */

#define IS_LL_DAC_WAVE_GEN_DIR(__VAL__)            (((__VAL__) == LL_DAC_WAVE_GEN_DIR_DEC) || \
                                                    ((__VAL__) == LL_DAC_WAVE_GEN_DIR_INC) )
/** @} */

/** @name LL_DAC_TrigSrcTypeDef
  * @brief DAC Trigger Source Definition
  * @note  Sawtooth Reset / Triangle Step Trigger Source
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_DAC_TrigSrcTypeDef                      uint32_t    
#else
typedef uint32_t LL_DAC_TrigSrcTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_DAC_TRIG_SRC_SW                         (0UL)                /*!< DAC Trigger Source Software                      */
#define LL_DAC_TRIG_SRC_TMR7_TRGO                  (1UL)                /*!< DAC Trigger Source TMR7 TRGO                     */
#define LL_DAC_TRIG_SRC_TMR8_TRGO                  (2UL)                /*!< DAC Trigger Source TMR7 TRGO                     */
#define LL_DAC_TRIG_SRC_TMR9_TRGO                  (3UL)                /*!< DAC Trigger Source TMR9 TRGO                     */
#define LL_DAC_TRIG_SRC_ADCTRG0                    (4UL)                /*!< DAC Trigger Source ADCTRG0                       */
#define LL_DAC_TRIG_SRC_ADCTRG2                    (5UL)                /*!< DAC Trigger Source ADCTRG2                       */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST0              (6UL)                /*!< DAC Trigger Source HRPWM DAC Rst 0               */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST1              (7UL)                /*!< DAC Trigger Source HRPWM DAC Rst 1               */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST2              (8UL)                /*!< DAC Trigger Source HRPWM DAC Rst 2               */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST3              (9UL)                /*!< DAC Trigger Source HRPWM DAC Rst 3               */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST4              (10UL)               /*!< DAC Trigger Source HRPWM DAC Rst 4               */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST5              (11UL)               /*!< DAC Trigger Source HRPWM DAC Rst 5               */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST6              (12UL)               /*!< DAC Trigger Source HRPWM DAC Rst 6               */
#define LL_DAC_TRIG_SRC_HRPWM_DACRST7              (13UL)               /*!< DAC Trigger Source HRPWM DAC Rst 7               */
#define LL_DAC_TRIG_SRC_HRPWM_DACTRGx              (14UL)               /*!< DAC Trigger Source HRPWM_DAC TRG x               */
#define LL_DAC_TRIG_SRC_EXT_PIN_PA10               (15UL)               /*!< DAC Trigger Source Ext Pin PA10                  */

#define IS_LL_DAC_TRIG_SRC(__VAL__)                (((__VAL__) == LL_DAC_TRIG_SRC_SW)            || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_TMR7_TRGO)     || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_TMR8_TRGO)     || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_TMR9_TRGO)     || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_ADCTRG0)       || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_ADCTRG2)       || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST0) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST1) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST2) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST3) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST4) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST5) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST6) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACRST7) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_HRPWM_DACTRGx) || \
                                                    ((__VAL__) == LL_DAC_TRIG_SRC_EXT_PIN_PA10)  )
/** @} */

/** @name LL_DAC_SAW_StepTrigSrcTypeDef
  * @brief DAC Sawtooth Step Trigger Source Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_DAC_SAW_StepTrigSrcTypeDef              uint32_t    
#else
typedef uint32_t LL_DAC_SAW_StepTrigSrcTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_DAC_SAW_STEP_TRIG_SRC_SW                (0UL)                /*!< Sawtooth Step Trigger Source Software            */
#define LL_DAC_SAW_STEP_TRIG_SRC_TMR7_TRGO         (1UL)                /*!< Sawtooth Step Trigger Source TMR7 TRGO           */
#define LL_DAC_SAW_STEP_TRIG_SRC_TMR8_TRGO         (2UL)                /*!< Sawtooth Step Trigger Source TMR8 TRGO           */
#define LL_DAC_SAW_STEP_TRIG_SRC_TMR10_TRGO        (3UL)                /*!< Sawtooth Step Trigger Source TMR10 TRGO          */
#define LL_DAC_SAW_STEP_TRIG_SRC_ADCTRG1           (4UL)                /*!< Sawtooth Step Trigger Source ADCTRG1             */
#define LL_DAC_SAW_STEP_TRIG_SRC_ADCTRG3           (5UL)                /*!< Sawtooth Step Trigger Source ADCTRG3             */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC0     (6UL)                /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 0                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC1     (7UL)                /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 1                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC2     (8UL)                /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 2                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC3     (9UL)                /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 3                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC4     (10UL)               /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 4                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC5     (11UL)               /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 5                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC6     (12UL)               /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 6                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC7     (13UL)               /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                             Increase 7                                       */
#define LL_DAC_SAW_STEP_TRIG_SRC_TMR2_TRGO         (14UL)               /*!< Sawtooth Step Trigger Source TMR2 TRGO           */
#define LL_DAC_SAW_STEP_TRIG_SRC_EXT_PIN_PA11      (15UL)               /*!< Sawtooth Step Trigger Source Ext Pin PA11        */

#define IS_LL_DAC_SAW_STEP_TRIG_SRC(__VAL__)       (((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_SW)            || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_TMR7_TRGO)     || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_TMR8_TRGO)     || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_TMR10_TRGO)    || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_ADCTRG1)       || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_ADCTRG3)       || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC0) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC1) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC2) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC3) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC4) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC5) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC6) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC7) || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_TMR2_TRGO)     || \
                                                    ((__VAL__) == LL_DAC_SAW_STEP_TRIG_SRC_EXT_PIN_PA11)  )
/** @} */

/** @name LL_DAC_TRI_MaxAmpTypeDef
  * @brief Triangle Max Amplitude Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_DAC_TRI_MaxAmpTypeDef                   uint32_t    
#else
typedef uint32_t LL_DAC_TRI_MaxAmpTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_DAC_TRI_MAX_AMP_1                       (0UL)                /*!< Triangle Max Amplitude 1                         */
#define LL_DAC_TRI_MAX_AMP_3                       (1UL)                /*!< Triangle Max Amplitude 3                         */
#define LL_DAC_TRI_MAX_AMP_7                       (2UL)                /*!< Triangle Max Amplitude 7                         */
#define LL_DAC_TRI_MAX_AMP_15                      (3UL)                /*!< Triangle Max Amplitude 15                        */
#define LL_DAC_TRI_MAX_AMP_31                      (4UL)                /*!< Triangle Max Amplitude 31                        */
#define LL_DAC_TRI_MAX_AMP_63                      (5UL)                /*!< Triangle Max Amplitude 63                        */
#define LL_DAC_TRI_MAX_AMP_127                     (6UL)                /*!< Triangle Max Amplitude 127                       */
#define LL_DAC_TRI_MAX_AMP_255                     (7UL)                /*!< Triangle Max Amplitude 255                       */
#define LL_DAC_TRI_MAX_AMP_511                     (8UL)                /*!< Triangle Max Amplitude 511                       */
#define LL_DAC_TRI_MAX_AMP_1023                    (9UL)                /*!< Triangle Max Amplitude 1023                      */
#define LL_DAC_TRI_MAX_AMP_2047                    (10UL)               /*!< Triangle Max Amplitude 2047                      */
#define LL_DAC_TRI_MAX_AMP_4095                    (11UL)               /*!< Triangle Max Amplitude 4095                      */

#define IS_LL_DAC_TRI_MAX_AMP(__VAL__)             (((__VAL__) == LL_DAC_TRI_MAX_AMP_1)    || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_3)    || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_7)    || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_15)   || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_31)   || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_63)   || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_127)  || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_255)  || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_511)  || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_1023) || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_2047) || \
                                                    ((__VAL__) == LL_DAC_TRI_MAX_AMP_4095) )
/** @} */

/** @name LL_DAC_SAW_UpdModeTypeDef
  * @brief DAC Sawtooth Update Mode Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_DAC_SAW_UpdModeTypeDef                  uint32_t    
#else
typedef uint32_t LL_DAC_SAW_UpdModeTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_DAC_SAW_UPD_MODE_CUR_PERIOD             (0UL)                /*!< Sawtooth Update Mode Current period              */
#define LL_DAC_SAW_UPD_MODE_NEXT_PERIOD            (1UL)                /*!< Sawtooth Update Mode Next period                 */

#define IS_LL_DAC_SAW_UPD_MODE(__VAL__)            (((__VAL__) == LL_DAC_SAW_UPD_MODE_CUR_PERIOD)  || \
                                                    ((__VAL__) == LL_DAC_SAW_UPD_MODE_NEXT_PERIOD) )
/** @} */

/**
  * @}
  */ /* DAC_LL_EC_Configuration */

/**
  * @}
  */ /* DAC_LL_Exported_Constants */



/* Exported Macros -----------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Macros DAC LL Exported Macros
  * @brief    DAC LL Exported Macros
  * @{
  */

//...
  
/**
  * @}
  */ /* DAC_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Functions DAC LL Functions
  * @brief    DAC LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_DAC_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_DAC_ASSERT_INLINE_PARAM == 1)
extern void LL_DAC_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_DAC_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_DAC_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_DAC_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup DAC_LL_EF_Configuration LL DAC Configuration
  * @brief    LL DAC Configuration
  * @{
  */

/**
  * @brief  Sawtooth Update Mode Set
  * @param  DACx Specifies DAC peripheral
  * @param  Mode Sawtooth Update Mode @ref LL_DAC_SAW_UpdateModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveSawtoothUpdateMode(DAC_TypeDef *DACx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->CR, DAC0_CR_STM_Msk, (((Mode) & DAC0_CR_STM_Val) << DAC0_CR_STM_Pos));
}

/**
  * @brief  Sawtooth Update Mode Get
  * @param  DACx Specifies DAC peripheral
  * @return Sawtooth Update Mode @ref LL_DAC_SAW_UpdateModeTypeDef
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveSawtoothUpdateMode(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_STM_Msk, DAC0_CR_STM_Pos));
}

/**
  * @brief  Sawtooth Generate Enable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_EnableWaveSawtoothGenerate(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->CR, DAC0_CR_STE_Msk);
}

/**
  * @brief  Sawtooth Generate Disable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_DisableWaveSawtoothGenerate(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    CLEAR_BIT(DACx->CR, DAC0_CR_STE_Msk);
}

/**
  * @brief  Judge is Sawtooth Generate Enable or not
  * @param  DACx Specifies DAC peripheral
  * @retval 0 Sawtooth Generate is Disable
  * @retval 1 Sawtooth Generate is Enable
  */
__STATIC_INLINE uint32_t LL_DAC_IsWaveSawtoothGenerateEnable(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_STE_Msk, DAC0_CR_STE_Pos));
}

/**
  * @brief  Sawtooth Generate Direction Set
  * @param  DACx Specifies DAC peripheral
  * @param  Dir Sawtooth Generate Direction @ref LL_DAC_WaveGenDirTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveSawtoothPolarity(DAC_TypeDef *DACx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->CR, DAC0_CR_STDIR_Msk, (((Dir) & DAC0_CR_STDIR_Val) << DAC0_CR_STDIR_Pos));
}

/**
  * @brief  Sawtooth Generate Direction Get
  * @param  DACx Specifies DAC peripheral
  * @return Sawtooth Generate Direction @ref LL_DAC_WaveGenDirTypeDef
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveSawtoothPolarity(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_STDIR_Msk, DAC0_CR_STDIR_Pos));
}

/**
  * @brief  Sawtooth Step Trigger Source Set
  * @param  DACx Specifies DAC peripheral
  * @param  Src Sawtooth Step Trigger Source
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveSawtoothStepTriggerSource(DAC_TypeDef *DACx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->CR, DAC0_CR_STINCTRIG_Msk, (((Src) & DAC0_CR_STINCTRIG_Val) << DAC0_CR_STINCTRIG_Pos));
}

/**
  * @brief  Sawtooth Step Trigger Source Get
  * @param  DACx Specifies DAC peripheral
  * @return Sawtooth Step Trigger Source @ref LL_DAC_SAW_StepTrigSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveSawtoothStepTriggerSource(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_STINCTRIG_Msk, DAC0_CR_STINCTRIG_Pos));
}

/**
  * @brief  Sawtooth Reset Trigger Source Set
  * @param  DACx Specifies DAC peripheral
  * @param  Src Sawtooth Reset Trigger Source @ref LL_DAC_TrigSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveSawtoothResetTriggerSource(DAC_TypeDef *DACx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->CR, DAC0_CR_STRSTTRIG_Msk, (((Src) & DAC0_CR_STRSTTRIG_Val) << DAC0_CR_STRSTTRIG_Pos));
}

/**
  * @brief  Sawtooth Reset Trigger Source Get
  * @param  DACx Specifies DAC peripheral
  * @return Sawtooth Reset Trigger Source @ref LL_DAC_TrigSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveSawtoothResetTriggerSource(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_STRSTTRIG_Msk, DAC0_CR_STRSTTRIG_Pos));
}

/**
  * @brief  Triangle Generate Enable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_EnableWaveTriangleGenerate(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->CR, DAC0_CR_TGE_Msk);
}

/**
  * @brief  Triangle Generate Disable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_DisableWaveTriangleGenerate(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    CLEAR_BIT(DACx->CR, DAC0_CR_TGE_Msk);
}

/**
  * @brief  Judge is Triangle Generate Enable or not
  * @param  DACx Specifies DAC peripheral
  * @retval 0 Triangle Generate is Disable
  * @retval 1 Triangle Generate is Enable
  */
__STATIC_INLINE uint32_t LL_DAC_IsWaveTriangleGenerateEnable(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_TGE_Msk, DAC0_CR_TGE_Pos));
}

/**
  * @brief  Triangle Generate Direction Set
  * @param  DACx Specifies DAC peripheral
  * @param  Dir Triangle Generate Direction @ref LL_DAC_WaveGenDirTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveTriangleDirection(DAC_TypeDef *DACx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->CR, DAC0_CR_TGDIR_Msk, (((Dir) & DAC0_CR_TGDIR_Val) << DAC0_CR_TGDIR_Pos));
}

/**
  * @brief  Triangle Generate Direction Get
  * @param  DACx Specifies DAC peripheral
  * @return Triangle Generate Direction @ref LL_DAC_WaveGenDirTypeDef
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveTriangleDirection(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_TGDIR_Msk, DAC0_CR_TGDIR_Pos));
}

/**
  * @brief  Triangle Max Amplitude Set
  * @param  DACx Specifies DAC peripheral
  * @param  Amp Triangle Max Amplitude @ref LL_DAC_TRI_MaxAmpTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveTriangleAmplitude(DAC_TypeDef *DACx, uint32_t Amp)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->CR, DAC0_CR_TGAMP_Msk, (((Amp) & DAC0_CR_TGAMP_Val) << DAC0_CR_TGAMP_Pos));
}

/**
  * @brief  Triangle Max Amplitude Get
  * @param  DACx Specifies DAC peripheral
  * @return Triangle Max Amplitude @ref LL_DAC_TRI_MaxAmpTypeDef
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveTriangleAmplitude(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_TGAMP_Msk, DAC0_CR_TGAMP_Pos));
}

/**
  * @brief  Triangle Trigger Source Set
  * @param  DACx Specifies DAC peripheral
  * @param  Src Triangle Trigger Source @ref LL_DAC_TrigSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetTriggerSource(DAC_TypeDef *DACx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->CR, DAC0_CR_TGTRIG_Msk, (((Src) & DAC0_CR_TGTRIG_Val) << DAC0_CR_TGTRIG_Pos));
}

/**
  * @brief  Triangle Trigger Source Get
  * @param  DACx Specifies DAC peripheral
  * @return Triangle Trigger Source @ref LL_DAC_TrigSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_DAC_GetTriggerSource(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_TGTRIG_Msk, DAC0_CR_TGTRIG_Pos));
}

/**
  * @brief  DAC Trigger Enable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_EnableTrigger(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->CR, DAC0_CR_TEN_Msk);
}

/**
  * @brief  DAC Trigger Disable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_DisableTrigger(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    CLEAR_BIT(DACx->CR, DAC0_CR_TEN_Msk);
}

/**
  * @brief  Judge is DAC Trigger Enable or not
  * @param  DACx Specifies DAC peripheral
  * @retval 0 DAC Trigger is Disable
  * @retval 1 DAC Trigger is Enable
  */
__STATIC_INLINE uint32_t LL_DAC_IsTriggerEnabled(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_TEN_Msk, DAC0_CR_TEN_Pos));
}

/**
  * @brief  DAC Buffer Output Enable
  * @param  DACx Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
__STATIC_INLINE void LL_DAC_EnableBufferOutput(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->CR, DAC0_CR_OEN_Msk);
}

/**
  * @brief  DAC Buffer Output Disable
  * @param  DACx Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
__STATIC_INLINE void LL_DAC_DisableBufferOutput(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    CLEAR_BIT(DACx->CR, DAC0_CR_OEN_Msk);
}

/**
  * @brief  Judge is DAC Buffer Output Enable or not
  * @param  DACx Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @retval 0 DAC Buffer Output is Disable
  * @retval 1 DAC Buffer Output is Enable
  */
__STATIC_INLINE uint32_t LL_DAC_IsBufferOutputEnable(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_OEN_Msk, DAC0_CR_OEN_Pos));
}

/**
  * @brief  DAC Bypass Buffer Output Enable
  * @param  DACx Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
__STATIC_INLINE void LL_DAC_EnableBypassBufferOutput(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->CR, DAC0_CR_BEN_Msk);
}

/**
  * @brief  Judge is DAC Bypass Buffer Output Enable or not
  * @param  DACx Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @retval 0 DAC Bypass Buffer Output is Disable
  * @retval 1 DAC Bypass Buffer Output is Enable
  */
__STATIC_INLINE uint32_t LL_DAC_IsBypassBufferOutputEnable(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_BEN_Msk, DAC0_CR_BEN_Pos));
}

/**
  * @brief  DAC Bypass Buffer Output Disable
  * @param  DACx Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
__STATIC_INLINE void LL_DAC_DisableBypassBufferOutput(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    CLEAR_BIT(DACx->CR, DAC0_CR_BEN_Msk);
}

/**
  * @brief  DAC Enable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_Enable(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->CR, DAC0_CR_PEN_Msk);
}

/**
  * @brief  DAC Disable
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_Disable(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    CLEAR_BIT(DACx->CR, DAC0_CR_PEN_Msk);
}

/**
  * @brief  Judge is DAC Enable or not
  * @param  DACx Specifies DAC peripheral
  * @retval 0 DAC is Disable
  * @retval 1 DAC is Enable
  */
__STATIC_INLINE uint32_t LL_DAC_IsEnabled(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->CR, DAC0_CR_PEN_Msk, DAC0_CR_PEN_Pos));
}

/**
  * @brief  DAC Data Write
  * @param  DACx Specifies DAC peripheral
  * @param  Dat Write Data
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetConvertData(DAC_TypeDef *DACx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    WRITE_REG(DACx->WDR, ((Dat) & DAC0_WDR_WDAT_Val));
}

/**
  * @brief  Triangle Initial Value Set
  * @param  DACx Specifies DAC peripheral
  * @param  Val Triangle Initial Value
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveTriangleInitialValue(DAC_TypeDef *DACx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    WRITE_REG(DACx->WDR, ((Val) & DAC0_WDR_WDAT_Val));
}

/**
  * @brief  Triangle Initial Value Get
  * @param  DACx Specifies DAC peripheral
  * @return Triangle Initial Value
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveTriangleInitialValue(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));
    
    return (uint32_t)(READ_BIT_SHIFT(DACx->WDR, DAC0_WDR_WDAT_Msk, DAC0_WDR_WDAT_Pos));
}

/**
  * @brief  DAC Data Read
  * @param  DACx Specifies DAC peripheral
  * @return Read Data
  */
__STATIC_INLINE uint32_t LL_DAC_RetrieveOutputData(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->RDR, DAC0_RDR_RDAT_Msk, DAC0_RDR_RDAT_Pos));
}

/**
  * @brief  Sawtooth Wave Step Data Set
  * @param  DACx Specifies DAC peripheral
  * @param  Dat Sawtooth Wave Step Data
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveSawtoothStepData(DAC_TypeDef *DACx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    WRITE_REG(DACx->SIDR, ((Dat) & DAC0_SIDR_SID_Val));
}

/**
  * @brief  Sawtooth Wave Step Data Get
  * @param  DACx Specifies DAC peripheral
  * @return Sawtooth Wave Step Data
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveSawtoothStepData(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->SIDR, DAC0_SIDR_SID_Msk, DAC0_SIDR_SID_Pos));
}

/**
  * @brief  Sawtooth Wave Reset Data Set
  * @param  DACx Specifies DAC peripheral
  * @param  Dat Sawtooth Wave Reset Data
  * @return None
  */
__STATIC_INLINE void LL_DAC_SetWaveSawtoothResetData(DAC_TypeDef *DACx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    MODIFY_REG(DACx->SRDR, DAC0_SRDR_SRD_Msk, (((Dat) & DAC0_SRDR_SRD_Val) << DAC0_SRDR_SRD_Pos));
}

/**
  * @brief  Sawtooth Wave Reset Data Integer Part Get
  * @param  DACx Specifies DAC peripheral
  * @param  dat Sawtooth Wave Reset Data
  * @return Sawtooth Wave Reset Data Integer Part
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveSawtoothResetData(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->SRDR, DAC0_SRDR_SRD_Msk, DAC0_SRDR_SRD_Pos));
}

/**
  * @brief  Sawtooth Wave Reset Data Fractional Part Get
  * @param  DACx Specifies DAC peripheral
  * @param  dat Sawtooth Wave Reset Data
  * @return Sawtooth Wave Reset Data Fractional Part
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveSawtoothResetDataFra(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->SRDR, DAC0_SRDR_SRDL_Msk, DAC0_SRDR_SRDL_Pos));
}

/**
  * @brief  Sawtooth Step Software Trigger
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_TrigSWConversionSawtoothStep(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->SWTR, DAC0_SWTR_SWTB_Msk);
}

/**
  * @brief  Triangle Step Software Trigger
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_TrigSWConversionTriangleStep(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->SWTR, DAC0_SWTR_SWT_Msk);
}

/**
  * @brief  Sawtooth Reset Software Trigger
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_TrigSWConversionSawtoothReset(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    SET_BIT(DACx->SWTR, DAC0_SWTR_SWT_Msk);
}

/**
  * @brief  Judge is DAC Data Output DoneB Interrupt Pending or not
  * @param  DACx Specifies DAC peripheral
  * @retval 0 isn't DAC Data Output DoneB Interrupt Pending
  * @retval 1 is DAC Data Output DoneB Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_DAC_IsSWTrigBActived(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->SR, DAC0_SR_DONB_Msk, DAC0_SR_DONB_Pos));
}

/**
  * @brief  DAC Data Output DoneB Interrupt Pending Clear
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_ClearSWTrigBFlag(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    WRITE_REG(DACx->SR, DAC0_SR_DONB_Msk);
}

/**
  * @brief  Judge is DAC Data Output Done Interrupt Pending or not
  * @param  DACx Specifies DAC peripheral
  * @retval 0 isn't DAC Data Output Done Interrupt Pending
  * @retval 1 is DAC Data Output Done Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_DAC_IsSWTrigActived(const DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    return (uint32_t)(READ_BIT_SHIFT(DACx->SR, DAC0_SR_DON_Msk, DAC0_SR_DON_Pos));
}

/**
  * @brief  DAC Data Output Done Interrupt Pending Clear
  * @param  DACx Specifies DAC peripheral
  * @return None
  */
__STATIC_INLINE void LL_DAC_ClearSWTrigFlag(DAC_TypeDef *DACx)
{
    ASSERT_INLINE_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    WRITE_REG(DACx->SR, DAC0_SR_DON_Msk);
}
/**
  * @}
  */ /* DAC_LL_EF_Configuration */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* DAC_LL_Exported_Functions */

/**
  * @}
  */ /* DAC_LL */

#endif /* DAC */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_DAC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

