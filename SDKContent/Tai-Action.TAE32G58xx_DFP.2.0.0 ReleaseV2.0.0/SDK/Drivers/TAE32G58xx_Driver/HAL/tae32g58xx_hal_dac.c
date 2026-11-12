/**
  ******************************************************************************
  * @file    tae32g58xx_hal_dac.c
  * @author  Tai-Action SD Team
  * @brief   DAC HAL module driver
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

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(DAC0) || defined(DAC1) || defined(DAC2) || defined(DAC3) || defined(DAC4) || \
    defined(DAC5) || defined(DAC6) || defined(DAC7) || defined(DAC8) 
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_DAC_MODULE_ENABLED) && (HAL_DAC_MODULE_ENABLED == 1)

/** @defgroup DAC_HAL DAC HAL
  * @brief    DAC HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup DAC_HAL_Private_Macros DAC HAL Private Macros
  * @brief    DAC HAL Private Macros
  * @{
  */

/*! Macro to get the FLASH physical instance from the handle */
#define DAC_GET_INSTANCE(Handle) ((DAC_TypeDef *)((uint32_t)((Handle)->Instance)))

#define IS_DAC_SET_VALUE_RANGE(__VAL__)               (((uint32_t)(__VAL__) >= (uint32_t)0) && \
                                                       ((uint32_t)(__VAL__) <= (uint32_t)4095))   

/**
  * @}
  */ /* DAC_HAL_Private_Macros */




/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup DAC_HAL_Exported_Functions DAC HAL Exported Functions
  * @brief    DAC HAL Exported Functions
  * @{
  */

/** @defgroup DAC_HAL_EF_Initialization DAC Init and DeInit Functions
  * @brief    DAC Init and DeInit Functions
  * @{
  */

/**
  * @brief  Initialize the DAC peripheral according to the specified parameters
  *         in the handle and initialize the associated handle.
  * @note   This function disables the DAC module before applying the configuration.
  *         The low-level hardware initialization (clock, NVIC) is performed by
  *         HAL_DAC_MspInit(), which the user must re-implement if needed.
  * @param  Handle DAC handle
  * @param  DACx Pointer to the base address of the DAC peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Init(HAL_DAC_HandleTypeDef *Handle, DAC_TypeDef* DACx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(DACx));
    
    HAL_DAC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_DAC_ALL_INSTANCE(DACx))) {
            return HAL_INVALID;
        }      
    })

    Handle->Instance = DACx;

    /* Init the low level hardware eg. Clock, NVIC */
    HAL_DAC_MspInit(Handle);

    /* Disable the DAC module before applying initialization settings to ensure a clean state */
    LL_DAC_Disable(Handle->Instance);

    Handle->State = HAL_DAC_STATE_INIT;

    return HAL_OK;
}

/**
  * @brief  De-initialize the DAC peripheral and restore default configurations.
  * @note   This function disables the DAC module and calls HAL_DAC_MspDeInit()
  *         to release hardware resources (clock, NVIC).
  * @param  Handle DAC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_DeInit(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));
    
    HAL_DAC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_DAC_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }      
    })

    /* Disable the DAC module */
    LL_DAC_Disable(Handle->Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    HAL_DAC_MspDeInit(Handle);

    Handle->State = HAL_DAC_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the DAC MSP (MCU Specific Package) according to the
  *         application requirements.
  * @note   This is a weak function that can be overridden by the user. It is
  *         automatically called by HAL_DAC_Init() and should contain all
  *         hardware-level initialization (GPIO, clock, NVIC, etc.).
  * @param  Handle DAC handle
  * @retval None
  */
__WEAK void HAL_DAC_MspInit(HAL_DAC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_DAC_MspInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the DAC MSP according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. It is
  *         automatically called by HAL_DAC_DeInit() and should release hardware
  *         resources previously configured in HAL_DAC_MspInit().
  * @param  Handle DAC handle
  * @retval None
  */
__WEAK void HAL_DAC_MspDeInit(HAL_DAC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_DAC_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Initialize the DAC IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user.
  * @param  DACx Pointer to the base address of the DAC peripheral.
  * @retval None
  */
__WEAK void HAL_DAC_IoInit(DAC_TypeDef* DACx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(DACx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_DAC_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the DAC IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  DACx Pointer to the base address of the DAC peripheral.
  * @retval None
  */
__WEAK void HAL_DAC_IoDeInit(DAC_TypeDef* DACx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(DACx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_DAC_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */ /* DAC_HAL_EF_Initialization */


/** @defgroup DAC_HAL_EF_Configuration DAC Configuration Functions
  * @brief    DAC Configuration Functions
  * @{
  */

/**
  * @brief  Enable or disable the DAC trigger conversion.
  * @note   When enabled, the DAC output is updated only on a hardware trigger
  *         event. When disabled, the DAC output updates immediately after a
  *         write to the data register.
  * @param  Handle DAC handle
  * @param  IsEnable Enable/disable trigger conversion.
  *         This parameter can be: @ref HAL_DAC_TrigConvEnTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_TriggerConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_TrigConvEnTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));
    
    HAL_DAC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_DAC_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }      
    })

    /* Configure the DAC trigger mode based on the IsEnable flag */
    HAL_FUNC_ALTER(IsEnable, LL_DAC_EnableTrigger(Handle->Instance), LL_DAC_DisableTrigger(Handle->Instance));

    return HAL_OK;
}

/**
  * @brief  Configure the DAC output buffer enable.
  * @param  Handle DAC handle
  * @param  IsEnable Enable/disable output buffer.
  *         This parameter can be: @ref HAL_DAC_OutBufEnTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_OutputBufferConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_OutBufEnTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));
    
    HAL_DAC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_DAC_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }      
    })

    /* Configure the DAC output buffer based on the IsEnable flag */
    HAL_FUNC_ALTER(IsEnable, LL_DAC_EnableBufferOutput(Handle->Instance), LL_DAC_DisableBufferOutput(Handle->Instance));

    return HAL_OK;
}

/**
  * @brief  Configure the DAC bypass output buffer mode.
  * @param  Handle DAC handle
  * @param  IsEnable Enable/disable bypass output buffer.
  *         This parameter can be: @ref HAL_DAC_OutBufEnTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_BypassBufferConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_OutBufEnTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));
    
    HAL_DAC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_DAC_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }      
    })

    /* Configure the DAC bypass output buffer based on the IsEnable flag */
    HAL_FUNC_ALTER(IsEnable, LL_DAC_EnableBypassBufferOutput(Handle->Instance), LL_DAC_DisableBypassBufferOutput(Handle->Instance));

    return HAL_OK;
}

/**
  * @brief  Configure the DAC sawtooth wave generation.
  * @note   This function first disables both sawtooth and triangle generation,
  *         then sets the sawtooth parameters, and finally enables sawtooth
  *         generation. The configuration structure must be provided.
  * @param  Handle DAC handle
  * @param  pCfg Pointer to a @ref HAL_DAC_SAW_CfgTypeDef structure that contains
  *              the sawtooth configuration parameters.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SAW_WaveConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_SAW_CfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_DAC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_DAC_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }      
    })

    DAC_TypeDef *p_instance;
    p_instance = Handle->Instance;

    /* Disable both sawtooth and triangle generation before re-configuration to avoid conflicts */
    LL_DAC_DisableWaveSawtoothGenerate(p_instance);
    LL_DAC_DisableWaveTriangleGenerate(p_instance);

    /* Configure sawtooth wave parameters: direction, reset value, step value,
       reset trigger source, step trigger source, and update mode */
    LL_DAC_SetWaveSawtoothPolarity(p_instance, pCfg->Direction);
    LL_DAC_SetWaveSawtoothResetData(p_instance, pCfg->ResetValue);
    LL_DAC_SetWaveSawtoothStepData(p_instance, pCfg->StepValue);
    LL_DAC_SetWaveSawtoothResetTriggerSource(p_instance, pCfg->ResetTrigSrce);
    LL_DAC_SetWaveSawtoothStepTriggerSource(p_instance, pCfg->StepTrigSrce);
    LL_DAC_SetWaveSawtoothUpdateMode(p_instance, pCfg->UpdateMode);

    /* Enable sawtooth generation */
    LL_DAC_EnableWaveSawtoothGenerate(p_instance);

    return HAL_OK;
}

/**
  * @brief  Configure the DAC triangle wave generation.
  * @note   This function first disables both sawtooth and triangle generation,
  *         then sets the triangle parameters, and finally enables triangle
  *         generation. The configuration structure must be provided.
  * @param  Handle DAC handle
  * @param  pCfg Pointer to a @ref HAL_DAC_TRI_CfgTypeDef structure that contains
  *              the triangle configuration parameters.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_TRI_WaveConfig(HAL_DAC_HandleTypeDef *Handle, HAL_DAC_TRI_CfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_DAC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_DAC_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }      
    })

    DAC_TypeDef *p_instance;
    p_instance = Handle->Instance;

    /* Disable both sawtooth and triangle generation before re-configuration to avoid conflicts */
    LL_DAC_DisableWaveSawtoothGenerate(p_instance);
    LL_DAC_DisableWaveTriangleGenerate(p_instance);

    /* Configure triangle wave parameters: initial value, max amplitude,
       generation direction, and trigger source */
    LL_DAC_SetWaveTriangleInitialValue(p_instance, pCfg->InitVal);
    LL_DAC_SetWaveTriangleAmplitude(p_instance, pCfg->MaxAmplitude);
    LL_DAC_SetWaveTriangleDirection(p_instance, pCfg->Direction);
    LL_DAC_SetTriggerSource(p_instance, pCfg->StepTrigSrce);

    /* Enable triangle generation */
    LL_DAC_EnableWaveTriangleGenerate(p_instance);

    return HAL_OK;
}

/**
  * @}
  */ /* DAC_HAL_EF_Configuration */


/** @defgroup DAC_HAL_EF_Operation DAC Operation Functions
  * @brief    DAC Operation Functions
  * @{
  */

/**
  * @brief  Enable the DAC peripheral and start the conversion.
  * @param  Handle DAC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Start(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_DAC_STATE_INIT | HAL_DAC_STATE_IDLE | HAL_DAC_STATE_ACTIVE);

    /* Enable the DAC module */
    LL_DAC_Enable(Handle->Instance);

    Handle->State = HAL_DAC_STATE_ACTIVE;

    return HAL_OK;
}

/**
  * @brief  Disable the DAC peripheral and stop the conversion.
  * @param  Handle DAC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Stop(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_DAC_STATE_INIT | HAL_DAC_STATE_IDLE | HAL_DAC_STATE_ACTIVE);

    /* Disable the DAC module */
    LL_DAC_Disable(Handle->Instance);

    Handle->State = HAL_DAC_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Set the DAC output value.
  * @param  Handle DAC handle
  * @param  Value 12-bit digital value (0 to 4095) to be converted to analog output.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SetValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_DAC_SET_VALUE_RANGE(Value));

    HAL_DAC_PARAM_CHECK({
        if ((!IS_DAC_SET_VALUE_RANGE(Value))) {
            return HAL_INVALID;
        }      
    })

    /* Write the digital value to the DAC data register */
    LL_DAC_SetConvertData(Handle->Instance, Value);

    return HAL_OK;
}

/**
  * @brief  Get the current DAC output value.
  * @note   This function reads the DAC data register and returns the last
  *         written value.
  * @param  Handle DAC handle
  * @retval 12-bit digital value currently stored in the DAC data register.
  *         Note: This is the programmed value, not the actual analog output.
  */
uint16_t HAL_DAC_GetValue(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Read the current DAC data register value */
    return (uint16_t)LL_DAC_RetrieveOutputData(Handle->Instance);
}

/**
  * @brief  Set the DAC sawtooth wave reset value.
  * @param  Handle DAC handle
  * @param  Value Sawtooth wave reset value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SAW_SetResetValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    LL_DAC_SetWaveSawtoothResetData(Handle->Instance, Value);

    return HAL_OK;
}

/**
  * @brief  Set the DAC sawtooth wave step value.
  * @param  Handle DAC handle
  * @param  Value Sawtooth wave step value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SAW_SetStepValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    LL_DAC_SetWaveSawtoothStepData(Handle->Instance, Value);

    return HAL_OK;
}

/**
  * @brief  Set the DAC triangle wave initial value.
  * @param  Handle DAC handle
  * @param  Value triangle wave initial value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_TRI_SetInitialValue(HAL_DAC_HandleTypeDef *Handle, uint16_t Value)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    LL_DAC_SetWaveTriangleInitialValue(Handle->Instance, Value);

    return HAL_OK;
}


/**
  * @brief  Trigger a sawtooth reset via software.
  * @note   This function generates a software trigger to reset the sawtooth
  *         generator's current value to the configured reset value.
  * @param  Handle DAC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SAW_ResetSwTrigger(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Generate a software reset trigger for the sawtooth generator */
    LL_DAC_TrigSWConversionSawtoothReset(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Trigger a sawtooth step via software.
  * @note   This function generates a software trigger to advance the sawtooth
  *         generator by one step.
  * @param  Handle DAC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SAW_StepSwTrigger(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Generate a software step trigger for the sawtooth generator */
    LL_DAC_TrigSWConversionSawtoothStep(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Trigger a triangle step via software.
  * @note   This function generates a software trigger to advance the triangle
  *         generator by one step.
  * @param  Handle DAC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_TRI_StepSwTrigger(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Generate a software step trigger for the triangle generator */
    LL_DAC_TrigSWConversionTriangleStep(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Check if the sawtooth reset trigger is done
  * @note   Only effective in the sawtooth wave mode
  * @param  Handle DAC handle
  * @retval Trigger status
  */
HAL_DAC_TrigDoneTypeDef HAL_DAC_SAW_IsResetTriggerDone(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Enable the DAC module */
    if (LL_DAC_IsSWTrigActived(Handle->Instance)) {
        LL_DAC_ClearSWTrigFlag(Handle->Instance);
        return HAL_DAC_TRIG_DONE;
    } else {
        return HAL_DAC_TRIG_NOT_DONE;
    }
}

/**
  * @brief  Check if the sawtooth step trigger is done
  * @note   Only effective in the sawtooth wave mode
  * @param  Handle DAC handle
  * @retval Trigger status
  */
HAL_DAC_TrigDoneTypeDef HAL_DAC_SAW_IsStepTriggerDone(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Enable the DAC module */
    if (LL_DAC_IsSWTrigBActived(Handle->Instance)) {
        LL_DAC_ClearSWTrigBFlag(Handle->Instance);
        return HAL_DAC_TRIG_DONE;
    } else {
        return HAL_DAC_TRIG_NOT_DONE;
    }
}

/**
  * @brief  Check if the triangle step trigger is done
  * @note   Only effective in the triangle wave mode
  * @param  Handle DAC handle
  * @retval Trigger status
  */
HAL_DAC_TrigDoneTypeDef HAL_DAC_TRI_IsStepTriggerDone(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Enable the DAC module */
    if (LL_DAC_IsSWTrigBActived(Handle->Instance)) {
        LL_DAC_ClearSWTrigBFlag(Handle->Instance);
        return HAL_DAC_TRIG_DONE;
    } else {
        return HAL_DAC_TRIG_NOT_DONE;
    }
}

/**
  * @}
  */ /* DAC_HAL_EF_Operation */

/**
  * @}
  */ /* DAC_HAL_Exported_Functions */


/* Private Functions ---------------------------------------------------------*/

/**
  * @}
  */ /* DAC_HAL */

#endif  /* HAL_DAC_MODULE_ENABLED */
#endif  /* HAL_MODULE_ENABLED */
#endif  /* DAC */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

