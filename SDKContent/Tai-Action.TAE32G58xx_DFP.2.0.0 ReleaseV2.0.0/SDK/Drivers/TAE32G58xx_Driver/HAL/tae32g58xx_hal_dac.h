/**
  ******************************************************************************
  * @file    tae32g58xx_hal_dac.h
  * @author  Tai-Action SD Team
  * @brief   Header file for DAC HAL module
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
#ifndef _TAE32G58XX_HAL_DAC_H_
#define _TAE32G58XX_HAL_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_dac.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(DAC0) || defined(DAC1) || defined(DAC2) || defined(DAC3) || defined(DAC4) || \
    defined(DAC5) || defined(DAC6) || defined(DAC7) || defined(DAC8) 

/** @addtogroup DAC_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup DAC_HAL_Exported_Macros DAC HAL Exported Macros
  * @brief    DAC HAL Exported Macros
  * @{
  */

/** @defgroup DAC_HAL_EM_Discriminant DAC HAL Discriminant
  * @brief    DAC HAL Discriminant
  * @{
  */

//...

/**
  * @}
  */ /* DAC_HAL_EM_Discriminant */


/** @defgroup DAC_HAL_EM_Assert DAC HAL Assert 
  * @brief    DAC HAL Assert
  * @{
  */

/**
  * @brief  The HAL_DAC_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_DAC_CHECK_PARAM
#define TAE32_USE_HAL_DAC_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_DAC_CHECK_PARAM != 1) && (TAE32_USE_HAL_DAC_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_DAC_CHECK_PARAM
#define TAE32_USE_HAL_DAC_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_DAC_CHECK_PARAM */

/**
  * @brief  The HAL_DAC_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_DAC_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_DAC_CHECK_PARAM) { \
            expression;                      \
        }
/**
  * @}
  */ /* DAC_HAL_EM_Assert */


/**
  * @}
  */ /* DAC_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup DAC_HAL_Exported_Types DAC HAL Exported Types
  * @brief    DAC HAL Exported Types
  * @{
  */

/**
  * @brief DAC Global state
  */
typedef enum
{
  HAL_DAC_STATE_RESET                  = 0UL,              /*!< DAC not yet initialized                   */
  HAL_DAC_STATE_INIT                   = (1UL << 30U),     /*!< DAC initialized but not yet configured    */
  HAL_DAC_STATE_IDLE                   = (1UL << 29U),     /*!< DAC configured and ready to be activated  */
  HAL_DAC_STATE_ACTIVE                 = (1UL << 28U),     /*!< DAC activated, ready to operate           */
} HAL_DAC_StateTypeDef;

/**
  * @brief DAC Sawtooth/Triangle Wave Generate Direction Definition
  */
typedef enum
{
    HAL_DAC_WAVE_GEN_DIR_DEC  = LL_DAC_WAVE_GEN_DIR_DEC,    /*!< DAC Wave Generate Direction Decrease */
    HAL_DAC_WAVE_GEN_DIR_INC  = LL_DAC_WAVE_GEN_DIR_INC,    /*!< DAC Wave Generate Direction Increase */
    HAL_DAC_WAVE_GEN_DIR_ENUM_END                           /*!< DAC Wave Generate Direction Enum End */
} HAL_DAC_WaveGenDirTypeDef;

/**
  * @brief DAC Trigger Source Definition
  * @note  Sawtooth Reset / Triangle Step Trigger Source
  */
typedef enum
{
    HAL_DAC_TRIG_SRC_SW             = LL_DAC_TRIG_SRC_SW,              /*!< DAC Trigger Source Software          */
    HAL_DAC_TRIG_SRC_TMR7_TRGO      = LL_DAC_TRIG_SRC_TMR7_TRGO,       /*!< DAC Trigger Source TMR7 TRGO         */
    HAL_DAC_TRIG_SRC_TMR8_TRGO      = LL_DAC_TRIG_SRC_TMR8_TRGO,       /*!< DAC Trigger Source TMR7 TRGO         */
    HAL_DAC_TRIG_SRC_TMR9_TRGO      = LL_DAC_TRIG_SRC_TMR9_TRGO,       /*!< DAC Trigger Source TMR9 TRGO         */
    HAL_DAC_TRIG_SRC_ADCTRG0        = LL_DAC_TRIG_SRC_ADCTRG0,         /*!< DAC Trigger Source ADCTRG0           */
    HAL_DAC_TRIG_SRC_ADCTRG2        = LL_DAC_TRIG_SRC_ADCTRG2,         /*!< DAC Trigger Source ADCTRG2           */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST0  = LL_DAC_TRIG_SRC_HRPWM_DACRST0,   /*!< DAC Trigger Source HRPWM DAC Rst 0   */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST1  = LL_DAC_TRIG_SRC_HRPWM_DACRST1,   /*!< DAC Trigger Source HRPWM DAC Rst 1   */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST2  = LL_DAC_TRIG_SRC_HRPWM_DACRST2,   /*!< DAC Trigger Source HRPWM DAC Rst 2   */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST3  = LL_DAC_TRIG_SRC_HRPWM_DACRST3,   /*!< DAC Trigger Source HRPWM DAC Rst 3   */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST4  = LL_DAC_TRIG_SRC_HRPWM_DACRST4,   /*!< DAC Trigger Source HRPWM DAC Rst 4   */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST5  = LL_DAC_TRIG_SRC_HRPWM_DACRST5,   /*!< DAC Trigger Source HRPWM DAC Rst 5   */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST6  = LL_DAC_TRIG_SRC_HRPWM_DACRST6,   /*!< DAC Trigger Source HRPWM DAC Rst 6   */
    HAL_DAC_TRIG_SRC_HRPWM_DACRST7  = LL_DAC_TRIG_SRC_HRPWM_DACRST7,   /*!< DAC Trigger Source HRPWM DAC Rst 7   */
    HAL_DAC_TRIG_SRC_HRPWM_DACTRGx  = LL_DAC_TRIG_SRC_HRPWM_DACTRGx,   /*!< DAC Trigger Source HRPWM_DAC TRG x   */
    HAL_DAC_TRIG_SRC_EXT_PIN_PA10   = LL_DAC_TRIG_SRC_EXT_PIN_PA10,    /*!< DAC Trigger Source Ext Pin PA10      */
    HAL_DAC_TRIG_SRC_ENUM_END                                          /*!< DAC Trigger Source Enum End          */
} HAL_DAC_TrigSrcTypeDef;

/**
  * @brief DAC Sawtooth Step Trigger Source Definition
  */
typedef enum
{
    HAL_DAC_SAW_STEP_TRIG_SRC_SW             = LL_DAC_SAW_STEP_TRIG_SRC_SW,              /*!< Sawtooth Step Trigger Source Software            */
    HAL_DAC_SAW_STEP_TRIG_SRC_TMR7_TRGO      = LL_DAC_SAW_STEP_TRIG_SRC_TMR7_TRGO,       /*!< Sawtooth Step Trigger Source TMR7 TRGO           */
    HAL_DAC_SAW_STEP_TRIG_SRC_TMR8_TRGO      = LL_DAC_SAW_STEP_TRIG_SRC_TMR8_TRGO,       /*!< Sawtooth Step Trigger Source TMR8 TRGO           */
    HAL_DAC_SAW_STEP_TRIG_SRC_TMR10_TRGO     = LL_DAC_SAW_STEP_TRIG_SRC_TMR10_TRGO,      /*!< Sawtooth Step Trigger Source TMR10 TRGO          */
    HAL_DAC_SAW_STEP_TRIG_SRC_ADCTRG1        = LL_DAC_SAW_STEP_TRIG_SRC_ADCTRG1,         /*!< Sawtooth Step Trigger Source ADCTRG1             */
    HAL_DAC_SAW_STEP_TRIG_SRC_ADCTRG3        = LL_DAC_SAW_STEP_TRIG_SRC_ADCTRG3,         /*!< Sawtooth Step Trigger Source ADCTRG3             */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC0  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC0,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 0                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC1  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC1,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 1                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC2  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC2,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 2                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC3  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC3,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 3                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC4  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC4,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 4                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC5  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC5,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 5                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC6  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC6,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 6                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC7  = LL_DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC7,   /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth  \
                                                                                              Increase 7                                       */
    HAL_DAC_SAW_STEP_TRIG_SRC_TMR2_TRGO      = LL_DAC_SAW_STEP_TRIG_SRC_TMR2_TRGO,       /*!< Sawtooth Step Trigger Source TMR2 TRGO           */
    HAL_DAC_SAW_STEP_TRIG_SRC_EXT_PIN_PA11   = LL_DAC_SAW_STEP_TRIG_SRC_EXT_PIN_PA11,    /*!< Sawtooth Step Trigger Source Ext Pin PA11        */
    HAL_DAC_SAW_STEP_TRIG_SRC_ENUM_END                                                   /*!< Sawtooth Step Trigger Source Enum End            */
} HAL_DAC_SAW_StepTrigSrcTypeDef;

/**
  * @brief Triangle Max Amplitude Definition
  */
typedef enum
{
    HAL_DAC_TRI_MAX_AMP_1     = LL_DAC_TRI_MAX_AMP_1,      /*!< Triangle Max Amplitude 1        */
    HAL_DAC_TRI_MAX_AMP_3     = LL_DAC_TRI_MAX_AMP_3,      /*!< Triangle Max Amplitude 3        */
    HAL_DAC_TRI_MAX_AMP_7     = LL_DAC_TRI_MAX_AMP_7,      /*!< Triangle Max Amplitude 7        */
    HAL_DAC_TRI_MAX_AMP_15    = LL_DAC_TRI_MAX_AMP_15,     /*!< Triangle Max Amplitude 15       */
    HAL_DAC_TRI_MAX_AMP_31    = LL_DAC_TRI_MAX_AMP_31,     /*!< Triangle Max Amplitude 31       */
    HAL_DAC_TRI_MAX_AMP_63    = LL_DAC_TRI_MAX_AMP_63,     /*!< Triangle Max Amplitude 63       */
    HAL_DAC_TRI_MAX_AMP_127   = LL_DAC_TRI_MAX_AMP_127,    /*!< Triangle Max Amplitude 127      */
    HAL_DAC_TRI_MAX_AMP_255   = LL_DAC_TRI_MAX_AMP_255,    /*!< Triangle Max Amplitude 255      */
    HAL_DAC_TRI_MAX_AMP_511   = LL_DAC_TRI_MAX_AMP_511,    /*!< Triangle Max Amplitude 511      */
    HAL_DAC_TRI_MAX_AMP_1023  = LL_DAC_TRI_MAX_AMP_1023,   /*!< Triangle Max Amplitude 1023     */
    HAL_DAC_TRI_MAX_AMP_2047  = LL_DAC_TRI_MAX_AMP_2047,   /*!< Triangle Max Amplitude 2047     */
    HAL_DAC_TRI_MAX_AMP_4095  = LL_DAC_TRI_MAX_AMP_4095,   /*!< Triangle Max Amplitude 4095     */
    HAL_DAC_TRI_MAX_AMP_ENUM_END                           /*!< Triangle Max Amplitude Enum End */
} HAL_DAC_TRI_MaxAmpTypeDef;

/**
  * @brief DAC Sawtooth Update Mode Definition
  */
typedef enum
{
    HAL_DAC_SAW_UPD_MODE_CUR_PERIOD   = LL_DAC_SAW_UPD_MODE_CUR_PERIOD,   /*!< Sawtooth Update Mode Current period   */
    HAL_DAC_SAW_UPD_MODE_NEXT_PERIOD  = LL_DAC_SAW_UPD_MODE_NEXT_PERIOD,  /*!< Sawtooth Update Mode Next period      */
    HAL_DAC_SAW_UPD_MODE_ENUM_END                                         /*!< Sawtooth Update Mode Enum End         */
} HAL_DAC_SAW_UpdModeTypeDef;


/**
  * @brief DAC Trigger Convert Enable Definition
  */
typedef enum
{
    HAL_DAC_TRIG_CONVERT_DISABLE  = 0UL,  /*!< Trigger Convert Disaable   */
    HAL_DAC_TRIG_CONVERT_ENABLE   = 1UL   /*!< Trigger Convert Enable     */
} HAL_DAC_TrigConvEnTypeDef;

/**
  * @brief DAC Output Buffer Enable Definition
  */
typedef enum
{
    HAL_DAC_OUTPUT_BUFFER_DISABLE  = 0UL, /*!< Output Buffer Disable  */
    HAL_DAC_OUTPUT_BUFFER_ENABLE   = 1UL  /*!< Output Buffer Enable   */
} HAL_DAC_OutBufEnTypeDef;

/**
  * @brief DAC Trigger Done Definition
  */
typedef enum
{
    HAL_DAC_TRIG_NOT_DONE  = 0UL,  /*!< DAC Trigger Not Done  */
    HAL_DAC_TRIG_DONE      = 1UL   /*!< DAC Trigger Done      */
} HAL_DAC_TrigDoneTypeDef;

/**
  * @brief DAC Sawtooth Config Structure Definition
  */
typedef struct 
{
    uint16_t                        ResetValue;       /*!< Reset Value                */
    uint16_t                        StepValue;        /*!< Step Value                 */
    HAL_DAC_WaveGenDirTypeDef       Direction;        /*!< Wave Generate Direction    */
    HAL_DAC_TrigSrcTypeDef          ResetTrigSrce;    /*!< Reset Trigger Source       */
    HAL_DAC_SAW_StepTrigSrcTypeDef  StepTrigSrce;     /*!< Step Trigger Source        */
    HAL_DAC_SAW_UpdModeTypeDef      UpdateMode;       /*!< Update Mode                */
} HAL_DAC_SAW_CfgTypeDef;

/**
  * @brief DAC Triangle Config Structure Definition
  */
typedef struct 
{
    uint16_t                    InitVal;              /*!< Initial Value              */
    HAL_DAC_TRI_MaxAmpTypeDef   MaxAmplitude;         /*!< Max Amplitude              */
    HAL_DAC_WaveGenDirTypeDef   Direction;            /*!< Wave Generate Direction    */
    HAL_DAC_TrigSrcTypeDef      StepTrigSrce;         /*!< Step Trigger Source        */
} HAL_DAC_TRI_CfgTypeDef;


typedef struct HAL_DAC_HandleStructDef HAL_DAC_HandleTypeDef; /*!< HAL DAC handle structure type */

/**
  * @brief  DAC Handle Structure definition
  */
struct HAL_DAC_HandleStructDef
{
    DAC_TypeDef                     *Instance;          /*!< Register base address    */
    volatile HAL_DAC_StateTypeDef   State;              /*!< Global state             */
    volatile uint32_t               ErrorCode;          /*!< DAC error code           */
    const void                      *pUserData;         /*!< User data pointer        */
};


/**
  * @}
  */ /* DAC_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup DAC_HAL_Exported_Functions
  * @{
  */

/** @addtogroup DAC_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_DAC_Init(HAL_DAC_HandleTypeDef *Handle, DAC_TypeDef* DACx);
HAL_StatusTypeDef HAL_DAC_DeInit(HAL_DAC_HandleTypeDef *Handle);
void HAL_DAC_MspInit(HAL_DAC_HandleTypeDef *Handle);
void HAL_DAC_MspDeInit(HAL_DAC_HandleTypeDef *Handle);
void HAL_DAC_IoInit(DAC_TypeDef* DACx);
void HAL_DAC_IoDeInit(DAC_TypeDef* DACx);
/**
  * @}
  */ /* DAC_HAL_EF_Initialization */


/** @addtogroup DAC_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_DAC_TriggerConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_TrigConvEnTypeDef IsEnable);
HAL_StatusTypeDef HAL_DAC_OutputBufferConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_OutBufEnTypeDef IsEnable);
HAL_StatusTypeDef HAL_DAC_BypassBufferConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_OutBufEnTypeDef IsEnable);
HAL_StatusTypeDef HAL_DAC_SAW_WaveConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_SAW_CfgTypeDef *pCfg);
HAL_StatusTypeDef HAL_DAC_TRI_WaveConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_TRI_CfgTypeDef *pCfg);
/**
  * @}
  */ /* DAC_HAL_EF_Configuration */


/** @addtogroup DAC_HAL_EF_Operation
  * @{
  */
HAL_StatusTypeDef HAL_DAC_Start(HAL_DAC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_DAC_Stop(HAL_DAC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_DAC_SetValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value);
uint16_t HAL_DAC_GetValue(HAL_DAC_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_DAC_SAW_SetResetValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value);
HAL_StatusTypeDef HAL_DAC_SAW_SetStepValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value);
HAL_StatusTypeDef HAL_DAC_TRI_SetInitialValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value);

HAL_StatusTypeDef HAL_DAC_SAW_ResetSwTrigger(HAL_DAC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_DAC_SAW_StepSwTrigger(HAL_DAC_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_DAC_TRI_StepSwTrigger(HAL_DAC_HandleTypeDef *Handle);

HAL_DAC_TrigDoneTypeDef HAL_DAC_SAW_IsResetTriggerDone(HAL_DAC_HandleTypeDef *Handle);
HAL_DAC_TrigDoneTypeDef HAL_DAC_SAW_IsStepTriggerDone(HAL_DAC_HandleTypeDef *Handle);
HAL_DAC_TrigDoneTypeDef HAL_DAC_TRI_IsStepTriggerDone(HAL_DAC_HandleTypeDef *Handle);
/**
  * @}
  */ /* DAC_HAL_EF_Operation */

/**
  * @}
  */ /* DAC_HAL_Exported_Functions */

/**
  * @}
  */ /* DAC_HAL */

#endif /* DAC */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_DAC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

