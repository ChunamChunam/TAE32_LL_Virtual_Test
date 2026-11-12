/**
  ******************************************************************************
  * @file    tae32g58xx_hal_adc.c
  * @author  Tai-Action SD Team
  * @brief   ADC HAL module driver
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

/** @defgroup ADC_HAL ADC HAL
  * @brief    ADC HAL Module Driver
  * @{
  */

#if defined(ADC0) || defined(ADC1) || defined(ADC2) || defined(ADC3)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_ADC_MODULE_ENABLED) && (HAL_ADC_MODULE_ENABLED == 1)

/* Private Constants ---------------------------------------------------------*/
/** @defgroup ADC_HAL_Private_Constants ADC HAL Private Constants
  * @brief    ADC HAL Private Constants
  * @{
  */

/**
  * @brief  Default timeout value used by blocking ADC operations.
  * @note   The timeout is expressed in milliseconds. It is used, for example,
  *         when waiting for the ADC to be enabled or disabled, or when waiting
  *         for a conversion to start or stop.
  */
#define ADC_DEFAULT_TIMEOUT         (10UL)

/**
  * @}
  */ /* ADC_HAL_Private_Constants */

/* Private Macros ------------------------------------------------------------*/
/** @defgroup ADC_HAL_Private_Macros ADC HAL Private Macros
  * @brief    ADC HAL Private Macros
  * @{
  */

/**
  * @brief  Macro to define a weak "sample channel conversion done" callback for
  *         a specific ADC channel.
  * @param  x ADC channel number in the range [0, HAL_ADC_CH_NUMS - 1].
  * @note   This macro generates a weak function with the name
  *         HAL_ADC_SAMP_Ch{x}ConvDoneCallback. The application can override
  *         any generated callback by implementing a strong function with the
  *         same name.
  * @return None.
  */
#define ADC_SAMP_CHx_CONV_DONE_CALLBACK(x)                                                  \
/**                                                                          */             \
/** @brief  ADC Sample Channel x Conversion Done Interrupt Callback Function */             \
/** @param  Handle ADC handle                                                */             \
/** @return None                                                             */             \
/**/                                                                                        \
__WEAK void HAL_ADC_SAMP_Ch##x##ConvDoneCallback(HAL_ADC_HandleTypeDef *Handle)             \
{                                                                                           \
    /* Prevent unused argument(s) compilation warning */                                    \
    HAL_UNUSED(Handle);                                                                     \
                                                                                            \
    /* NOTE: This function should not be modified. When the callback is needed,          */ \
    /*       the HAL_ADC_SAMP_ChxConvDoneCallback could be implemented in the user file  */ \
    /**/                                                                                    \
}

/**
  * @brief  Macro to define a weak "DMA half transfer complete" callback for a
  *         specific ADC channel.
  * @param  x ADC channel number in the range [0, HAL_ADC_CH_NUMS - 1].
  * @note   This macro generates a weak function with the name
  *         HAL_ADC_DMA_Ch{x}HalfCpltCallback. The application can override
  *         any generated callback by implementing a strong function with the
  *         same name.
  * @return None.
  */
#define ADC_DMA_CHx_HALF_CPLT_CALLBACK(x)                                                   \
/**                                                             */                          \
/** @brief  ADC DMA Half Complete Interrupt Callback Function   */                          \
/** @param  Handle ADC handle                                   */                          \
/** @return None                                                */                          \
/**/                                                                                        \
__WEAK void HAL_ADC_DMA_Ch##x##HalfCpltCallback(HAL_ADC_HandleTypeDef *Handle)              \
{                                                                                           \
    /* Prevent unused argument(s) compilation warning */                                    \
    HAL_UNUSED(Handle);                                                                     \
                                                                                            \
    /* NOTE: This function should not be modified. When the callback is needed,          */ \
    /*       the HAL_ADC_DMA_ChxHalfCpltCallback could be implemented in the user file   */ \
    /**/                                                                                    \
}

/**
  * @brief  Macro to define a weak "DMA transfer complete" callback for a
  *         specific ADC channel.
  * @param  x ADC channel number in the range [0, HAL_ADC_CH_NUMS - 1].
  * @note   This macro generates a weak function with the name
  *         HAL_ADC_DMA_Ch{x}CpltCallback. The application can override any
  *         generated callback by implementing a strong function with the same
  *         name.
  * @return None.
  */
#define ADC_DMA_CHx_CPLT_CALLBACK(x)                                                        \
/**                                                         */                              \
/** @brief  ADC DMA Complete Interrupt Callback Function    */                              \
/** @param  Handle ADC handle                               */                              \
/** @return None                                            */                              \
/**/                                                                                        \
__WEAK void HAL_ADC_DMA_Ch##x##CpltCallback(HAL_ADC_HandleTypeDef *Handle)                  \
{                                                                                           \
    /* Prevent unused argument(s) compilation warning */                                    \
    HAL_UNUSED(Handle);                                                                     \
                                                                                            \
    /* NOTE: This function should not be modified. When the callback is needed,      */     \
    /*       the HAL_ADC_DMA_ChxCpltCallback could be implemented in the user file   */     \
    /**/                                                                                    \
}

#define IS_ADC_CHANNEL_NUMBER(__VAL__)                 ((uint32_t)(__VAL__) < (uint32_t)HAL_ADC_CH_NUMS)

#define IS_ADC_OVER_SAMP_RATIO(__VAL__)                (((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_2)    || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_4)    || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_8)    || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_16)   || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_32)   || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_64)   || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_128)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_RATIO_256)) 

#define IS_ADC_OVER_SAMP_SHIFT(__VAL__)                (((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_NONE)     || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_1)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_2)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_3)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_4)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_5)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_6)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_7)  || \
                                                        ((__VAL__) == HAL_ADC_OVER_SAMP_SHIFT_RIGHT_8)) 

#define IS_ADC_SAMP_MODE(__VAL__)                      (((__VAL__) == HAL_ADC_SAMP_MODE_OVER_SAMP_DISABLE)     || \
                                                        ((__VAL__) == HAL_ADC_SAMP_MODE_REG_CONTINUED)         || \
                                                        ((__VAL__) == HAL_ADC_SAMP_MODE_REG_RESUMED)           || \
                                                        ((__VAL__) == HAL_ADC_SAMP_MODE_TRIGGERED_REG_RESUMED) || \
                                                        ((__VAL__) == HAL_ADC_SAMP_MODE_INJ_REG_RESUMED)       || \
                                                        ((__VAL__) == HAL_ADC_SAMP_MODE_INJ)) 
/**
  * @}
  */ /* ADC_HAL_Private_Macros */

/* Private Types -------------------------------------------------------------*/
/** @defgroup ADC_HAL_Private_Types ADC HAL Private Types
  * @brief    ADC HAL Private Types
  * @{
  */

/**
  * @}
  */ /* ADC_HAL_Private_Types */

/* Private Variables ---------------------------------------------------------*/
/** @defgroup ADC_HAL_Private_Variables ADC HAL Private Variables
  * @brief    ADC HAL Private Variables
  * @{
  */

/**
  * @brief  Look-up table of weak callback functions for per-channel
  *         "conversion done" events.
  * @note   The index of the table corresponds to the ADC channel number.
  *         These callbacks are invoked by the ADC sample interrupt handler
  *         when the conversion of a particular channel completes.
  */
static const HAL_ADC_IRQCallback ADC_SAMP_ChxConvDoneCallback[HAL_ADC_CH_NUMS] = {
    HAL_ADC_SAMP_Ch0ConvDoneCallback,
    HAL_ADC_SAMP_Ch1ConvDoneCallback,
    HAL_ADC_SAMP_Ch2ConvDoneCallback,
    HAL_ADC_SAMP_Ch3ConvDoneCallback,
    HAL_ADC_SAMP_Ch4ConvDoneCallback,
    HAL_ADC_SAMP_Ch5ConvDoneCallback,
    HAL_ADC_SAMP_Ch6ConvDoneCallback,
    HAL_ADC_SAMP_Ch7ConvDoneCallback,
    HAL_ADC_SAMP_Ch8ConvDoneCallback,
    HAL_ADC_SAMP_Ch9ConvDoneCallback,
    HAL_ADC_SAMP_Ch10ConvDoneCallback,
    HAL_ADC_SAMP_Ch11ConvDoneCallback,
    HAL_ADC_SAMP_Ch12ConvDoneCallback,
    HAL_ADC_SAMP_Ch13ConvDoneCallback,
    HAL_ADC_SAMP_Ch14ConvDoneCallback,
    HAL_ADC_SAMP_Ch15ConvDoneCallback,
    HAL_ADC_SAMP_Ch16ConvDoneCallback,
    HAL_ADC_SAMP_Ch17ConvDoneCallback,
    HAL_ADC_SAMP_Ch18ConvDoneCallback,
    HAL_ADC_SAMP_Ch19ConvDoneCallback,
};

/**
  * @brief  Look-up table of weak callback functions for per-channel
  *         "DMA half transfer complete" events.
  * @note   The index of the table corresponds to the ADC channel number.
  *         These callbacks are invoked when the DMA has transferred half of
  *         the expected data for a channel.
  */
static const HAL_ADC_IRQCallback ADC_DMA_ChxHalfCpltCallback[HAL_ADC_CH_NUMS] = {
    HAL_ADC_DMA_Ch0HalfCpltCallback,
    HAL_ADC_DMA_Ch1HalfCpltCallback,
    HAL_ADC_DMA_Ch2HalfCpltCallback,
    HAL_ADC_DMA_Ch3HalfCpltCallback,
    HAL_ADC_DMA_Ch4HalfCpltCallback,
    HAL_ADC_DMA_Ch5HalfCpltCallback,
    HAL_ADC_DMA_Ch6HalfCpltCallback,
    HAL_ADC_DMA_Ch7HalfCpltCallback,
    HAL_ADC_DMA_Ch8HalfCpltCallback,
    HAL_ADC_DMA_Ch9HalfCpltCallback,
    HAL_ADC_DMA_Ch10HalfCpltCallback,
    HAL_ADC_DMA_Ch11HalfCpltCallback,
    HAL_ADC_DMA_Ch12HalfCpltCallback,
    HAL_ADC_DMA_Ch13HalfCpltCallback,
    HAL_ADC_DMA_Ch14HalfCpltCallback,
    HAL_ADC_DMA_Ch15HalfCpltCallback,
    HAL_ADC_DMA_Ch16HalfCpltCallback,
    HAL_ADC_DMA_Ch17HalfCpltCallback,
    HAL_ADC_DMA_Ch18HalfCpltCallback,
    HAL_ADC_DMA_Ch19HalfCpltCallback,
};

/**
  * @brief  Look-up table of weak callback functions for per-channel
  *         "DMA transfer complete" events.
  * @note   The index of the table corresponds to the ADC channel number.
  *         These callbacks are invoked when the DMA has transferred all the
  *         expected data for a channel.
  */
static const HAL_ADC_IRQCallback ADC_DMA_ChxCpltCallback[HAL_ADC_CH_NUMS] = {
    HAL_ADC_DMA_Ch0CpltCallback,
    HAL_ADC_DMA_Ch1CpltCallback,
    HAL_ADC_DMA_Ch2CpltCallback,
    HAL_ADC_DMA_Ch3CpltCallback,
    HAL_ADC_DMA_Ch4CpltCallback,
    HAL_ADC_DMA_Ch5CpltCallback,
    HAL_ADC_DMA_Ch6CpltCallback,
    HAL_ADC_DMA_Ch7CpltCallback,
    HAL_ADC_DMA_Ch8CpltCallback,
    HAL_ADC_DMA_Ch9CpltCallback,
    HAL_ADC_DMA_Ch10CpltCallback,
    HAL_ADC_DMA_Ch11CpltCallback,
    HAL_ADC_DMA_Ch12CpltCallback,
    HAL_ADC_DMA_Ch13CpltCallback,
    HAL_ADC_DMA_Ch14CpltCallback,
    HAL_ADC_DMA_Ch15CpltCallback,
    HAL_ADC_DMA_Ch16CpltCallback,
    HAL_ADC_DMA_Ch17CpltCallback,
    HAL_ADC_DMA_Ch18CpltCallback,
    HAL_ADC_DMA_Ch19CpltCallback,
};

/**
  * @}
  */

/* Private Functions Prototypes -----------------------------------------------*/
/** @defgroup ADC_HAL_Private_Functions ADC HAL Private Functions
  * @brief    ADC HAL Private Functions
  * @{
  */

__STATIC_FORCEINLINE void ADC_DisableAndClearIT(HAL_ADC_HandleTypeDef *Handle);

static HAL_StatusTypeDef ADC_Enable(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_Disable(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_REG_ConvGrpUpdate(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_INJ_ConvGrpUpdate(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_REG_StartConv(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_INJ_StartConv(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_REG_StopConv(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_INJ_StopConv(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_Activate(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_Deactivate(HAL_ADC_HandleTypeDef *Handle);
static HAL_StatusTypeDef ADC_AutoCalibration(HAL_ADC_HandleTypeDef *Handle);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_OverSampCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       const HAL_ADC_OversampConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_REG_Cfg(HAL_ADC_HandleTypeDef *Handle, 
                                                   const HAL_ADC_RegularConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_INJ_Cfg(HAL_ADC_HandleTypeDef *Handle, 
                                                   const HAL_ADC_InjectionConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_CaliCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                   const HAL_ADC_CalibrationConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_CaliCoefGrpCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                          HAL_ADC_CalCoefGrpTypeDef Group,
                                                          const HAL_ADC_CaliCoefGrpConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_CaliChCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                     HAL_ADC_ChTypeDef Channel,
                                                     const HAL_ADC_ChannelCaliConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_AutoCaliCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       const HAL_ADC_AutoCaliConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_ChannelCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                      HAL_ADC_SampGrpTypeDef Group, 
                                                      const HAL_ADC_ChannelConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_IndepDMACfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       const HAL_ADC_IndepDMAConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_AWDG_Cfg(HAL_ADC_HandleTypeDef *Handle, 
                                                    const HAL_ADC_AnalogWDGConfTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_SatThresCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       HAL_ADC_SampGrpTypeDef Group,
                                                       int16_t Minimum, 
                                                       int16_t Maximum);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollITEvt(HAL_ADC_HandleTypeDef *Handle,
                                                     HAL_ADC_ITPendingMskTypeDef EventType,
                                                     uint32_t Timeout);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollRegConv(HAL_ADC_HandleTypeDef *Handle, 
                                                       uint32_t Timeout);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollRegConvSeq(HAL_ADC_HandleTypeDef *Handle, 
                                                          uint32_t Timeout);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollInjConv(HAL_ADC_HandleTypeDef *Handle, 
                                                       uint32_t Timeout);

__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollInjConvSeq(HAL_ADC_HandleTypeDef *Handle, 
                                                          uint32_t Timeout);

__STATIC_FORCEINLINE void ADC_SMP_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void ADC_STA_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void ADC_AWD_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void ADC_REG_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask);
__STATIC_FORCEINLINE void ADC_INJ_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup ADC_HAL_Exported_Functions ADC HAL Exported Functions
  * @brief    ADC HAL Exported Functions
  * @{
  */

/** @defgroup ADC_HAL_EF_Initialization ADC Init and DeInit Functions
  * @brief    ADC Init and DeInit Functions
  * @{
  */

/**
  * @brief  Initialize the ADC peripheral according to the parameters specified
  *         in @p pInit.
  * @note   This function performs the following steps:
  *         - Binds the ADC peripheral instance to the handle.
  *         - Initializes the low-level hardware interface through
  *           HAL_ADC_MspInit().
  *         - Configures the dual/quad mode and the interleaved phase delay if
  *           interleaved mode is selected.
  *         - Sets the handle states to indicate that the ADC is being
  *           configured.
  * @param  Handle ADC handle
  * @param  ADCx Pointer to the base address of the ADC peripheral.
  * @param  pInit Pointer to a HAL_ADC_InitTypeDef structure that contains the
  *         configuration information.
  * @retval HAL_OK      - Initialization completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - A conversion is already running, or the ADC is
  *                       already enabled.
  */
HAL_StatusTypeDef HAL_ADC_Init(HAL_ADC_HandleTypeDef *Handle, 
                               ADC_TypeDef *ADCx, 
                               HAL_ADC_InitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(ADCx));
    ASSERT_FUNC_PARAM(pInit != NULL);

    if (Handle == NULL || !IS_ADC_ALL_INSTANCE(ADCx) || pInit == NULL) {
        return HAL_INVALID;
    }

    /* User data, do nothing. */
    (void)Handle->pUserData;

    /* Bind the peripheral instance to the handle. */
    Handle->Instance = ADCx;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* The ADC cannot be initialized while a conversion is running. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_ERROR;
    }

    /* Initialize the low-level hardware (clock, NVIC, etc.). */
    HAL_ADC_MspInit(Handle);

    Handle->State = HAL_ADC_STATE_INIT;
    Handle->RegGrpState = HAL_ADC_GRP_STATE_RESET;
    Handle->InjGrpState = HAL_ADC_GRP_STATE_RESET;

    /* Clear Interrupt Flag */
    LL_ADC_ClearFlag(p_instance, LL_ADC_ISR_IT_FLAG_MSK);
    LL_ADC_ClearDataFlag(p_instance,LL_ADC_DISR_IT_FLAG_MSK);
    LL_ADC_DMA_ClearHalfFullFlag(p_instance, LL_ADC_HISR_DMA_HALF_IT_FLAG_MSK);
    LL_ADC_DMA_ClearFullFlag(p_instance, LL_ADC_FISR_DMA_FULL_IT_FLAG_MSK);

    /* Dual/quad ADC mode configuration. */
    LL_ADC_SetMultimode(p_instance, pInit->DualMode);

    if (pInit->DualMode == HAL_ADC_DUAL_MODE_REG_INTERLEAVED) {
        LL_ADC_SetMultiTwoSamplingDelay(p_instance, pInit->DualPhaseDelay);
    }

    Handle->LastErrorCodes = HAL_ADC_ERROR_NONE;

    Handle->RegGrpState = HAL_ADC_GRP_STATE_CONFIG;
    Handle->InjGrpState = HAL_ADC_GRP_STATE_CONFIG;

    Handle->State = HAL_ADC_STATE_CONFIGURING;

    return HAL_OK;
}

/**
  * @brief  De-initialize the ADC peripheral.
  * @note   This function first stops any ongoing conversions and disables the
  *         ADC. It then disables all interrupts, clears allpending flags,
  *          and calls HAL_ADC_MspDeInit() to release the
  *         low-level hardware resources.
  * @param  Handle ADC handle
  * @retval HAL_OK      - De-initialization completed successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_ADC_DeInit(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    HAL_StatusTypeDef status = HAL_OK;

    /* Stop the current operations */
    status = ADC_Deactivate(Handle);

    /* Clear flags and disable interrupts. */
    ADC_DisableAndClearIT(Handle);

    /* De-initialize the low-level hardware resources. */
    HAL_ADC_MspDeInit(Handle);

    Handle->State = HAL_ADC_STATE_RESET;

    Handle->RegGrpState = HAL_ADC_GRP_STATE_RESET;
    Handle->InjGrpState = HAL_ADC_GRP_STATE_RESET;

    return status;
}


/**
  * @brief  Initialize the ADC MSP (MCU Support Package).
  * @note   This weak function is intended to be overridden by the application.
  *         It should configure the peripheral clock, GPIO pins, and NVIC
  *         settings required by the ADC peripheral.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_MspInit(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_MspInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the ADC MSP.
  * @note   This weak function is intended to be overridden by the application.
  *         It should disable the ADC clock, release GPIO pins, and remove the
  *         NVIC settings.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_MspDeInit(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Initialize the ADC IO interface.
  * @note   This weak function is intended to be overridden by the application.
  *         It may be used to configure multiplexed pins or any external analog
  *         front-end control lines.
  * @param  ADCx Pointer to the base address of the ADC peripheral.
  * @retval None
  */
__WEAK void HAL_ADC_IoInit(ADC_TypeDef *ADCx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(ADCx); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the ADC IO interface.
  * @note   This weak function is intended to be overridden by the application.
  *         It should release any resources acquired by HAL_ADC_IoInit().
  * @param  ADCx Pointer to the base address of the ADC peripheral.
  * @retval None
  */
__WEAK void HAL_ADC_IoDeInit(ADC_TypeDef *ADCx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(ADCx); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */ /* ADC_HAL_EF_Initialization */


/** @defgroup ADC_HAL_EF_Configuration ADC Submodule Config Functions
  * @brief    ADC Submodule Config Functions
  * @{
  */


/**
  * @brief  Configure the oversampling feature of the ADC.
  * @note   Oversampling accumulates multiple conversions of the same channel
  *         and optionally shifts the result right, effectively increasing the
  *         signal-to-noise ratio at the cost of throughput. This function
  *         selects the oversampling mode, ratio, and right bit shift.
  *         The ADC must not be currently converting.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_OversampConfTypeDef structure containing
  *         the oversampling configuration.
  * @retval HAL_OK      - Configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_BUSY    - A conversion is already running.
  */
HAL_StatusTypeDef HAL_ADC_OverSamplingConfig(HAL_ADC_HandleTypeDef *Handle, 
                                             const HAL_ADC_OversampConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_PARAM(IS_ADC_OVER_SAMP_RATIO(pCfg->Ratio));
    ASSERT_FUNC_PARAM(IS_ADC_OVER_SAMP_SHIFT(pCfg->RightBitShift));
    ASSERT_FUNC_PARAM(IS_ADC_SAMP_MODE(pCfg->OversamplingMode));

    HAL_ADC_PARAM_CHECK({
        if ((!IS_ADC_OVER_SAMP_RATIO(pCfg->Ratio)) || (!IS_ADC_OVER_SAMP_SHIFT(pCfg->RightBitShift)) ||
            (!IS_ADC_SAMP_MODE(pCfg->OversamplingMode))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING);

    return ADC_OverSampCfg(Handle, pCfg);
}

/**
  * @brief  Configure the regular conversion group of the ADC.
  * @note   This function configures:
  *         - The overrun behavior.
  *         - The number of ranks in the regular sequencer.
  *         - The external trigger source and polarity.
  *         - The continuous or single conversion mode.
  *         - The discontinuous mode and the number of discontinuous
  *           conversions.
  *         The regular group must not be currently converting.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_RegularConfTypeDef structure containing
  *         the regular group configuration.
  * @retval HAL_OK      - Configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_BUSY    - A regular conversion is already running.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_RegularConfig(HAL_ADC_HandleTypeDef *Handle, 
                                        const HAL_ADC_RegularConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_CONFIG | HAL_ADC_GRP_STATE_IDLE);

    if ((Handle->State & (HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE))) {
        return ADC_REG_Cfg(Handle, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the injected conversion group of the ADC.
  * @note   This function configures:
  *         - The number of ranks in the injected sequencer.
  *         - The external trigger source and polarity.
  *         - The automatic injection trigger from the regular group.
  *         - The discontinuous mode for the injected group.
  *         The injected group must not be currently converting.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_InjectionConfTypeDef structure containing
  *         the injected group configuration.
  * @retval HAL_OK      - Configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid, or the requested
  *                       combination of automatic injection with external
  *                       triggers / discontinuous mode is not allowed.
  * @retval HAL_BUSY    - An injected conversion is already running.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_InjectedConfig(HAL_ADC_HandleTypeDef *Handle, 
                                         const HAL_ADC_InjectionConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_CONFIG | HAL_ADC_GRP_STATE_IDLE);

    if ((Handle->State & (HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE))) {
        return ADC_INJ_Cfg(Handle, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure a channel and assign it to an ADC conversion group.
  * @note   The channel is configured with its sampling time and input mode
  *         (single-ended or differential). In differential mode, the adjacent
  *         higher channel is automatically used as the negative input.
  *         The chosen group must not be currently converting.
  * @param  Handle ADC handle
  * @param  Group ADC group to which the channel is assigned:
  *         @arg HAL_ADC_GROUP_REGULAR
  *         @arg HAL_ADC_GROUP_INJECTED
  * @param  pCfg Pointer to a HAL_ADC_ChannelConfTypeDef structure containing
  *         the channel configuration.
  * @retval HAL_OK      - Channel configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid (invalid channel or
  *                       invalid differential pair).
  * @retval HAL_BUSY    - The selected group is currently converting.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_ChannelConfig(HAL_ADC_HandleTypeDef *Handle, 
                                        HAL_ADC_SampGrpTypeDef Group, 
                                        const HAL_ADC_ChannelConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    if (Group == HAL_ADC_GROUP_REGULAR) {
        ASSERT_FUNC_STATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_CONFIG | HAL_ADC_GRP_STATE_IDLE);

        status = ADC_ChannelCfg(Handle, HAL_ADC_GROUP_REGULAR, pCfg);

    }else if (Group == HAL_ADC_GROUP_INJECTED) {
        ASSERT_FUNC_STATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_CONFIG | HAL_ADC_GRP_STATE_IDLE);

        status = ADC_ChannelCfg(Handle, HAL_ADC_GROUP_INJECTED, pCfg);

    } else {
        status = HAL_INVALID;
    }

    return status;
}

/**
  * @brief  Configure the independent DMA transfer for a specific ADC channel.
  * @note   This interface allows the ADC to transfer conversion data of one
  *         channel automatically to a memory buffer without CPU intervention.
  *         The configuration includes the destination address, the transfer
  *         length in half-words, and the DMA options such as circular mode,
  *         fixed address mode, and interrupt generation.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_IndepDMAConfTypeDef structure containing
  *         the DMA configuration.
  * @retval HAL_OK      - Configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_BUSY    - The ADC is currently converting.
  */
HAL_StatusTypeDef HAL_ADC_IndependentDMAConfig(HAL_ADC_HandleTypeDef *Handle, 
                                               const HAL_ADC_IndepDMAConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_CHANNEL_NUMBER(pCfg->Channel));

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_CONFIG | HAL_ADC_GRP_STATE_IDLE);
    ASSERT_FUNC_STATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_CONFIG | HAL_ADC_GRP_STATE_IDLE);

    HAL_ADC_PARAM_CHECK({
        if (!IS_ADC_CHANNEL_NUMBER(pCfg->Channel)) {
            return HAL_INVALID;
        }

        if ((pCfg->BufferInHalfWords == 0) || ((pCfg->BufferInHalfWords > (UINT16_MAX/2)))) {
            return HAL_INVALID;
        }
    });

    return ADC_IndepDMACfg(Handle, pCfg);
}

/**
  * @brief  Configure the calibration parameters for a specific ADC channel.
  * @note   Calibration parameters include the coefficient group, the offset
  *         compensation, the gain compensation, and whether the saturation
  *         arithmetic is supported. These parameters are used to correct the
  *         measured conversion data.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_CalibrationConfTypeDef structure
  *         containing the calibration configuration.
  * @retval HAL_OK      - Calibration configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_BUSY    - A conversion is currently running.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_CalibrationConfig(HAL_ADC_HandleTypeDef *Handle, 
                                            const HAL_ADC_CalibrationConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);

    if (Handle->State & (HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE)) {
        return ADC_CaliCfg(Handle, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the calibration value for a specific ADC coefficient Group.
  * @note   Calibration parameters include the offset compensation, the gain 
  *         compensation. 
  * @param  Handle ADC handle
  * @param  Group Calibration coefficient group number to be set.
  * @param  pCfg Pointer to a HAL_ADC_CaliCoefGrpConfTypeDef structure
  *         containing the calibration coefficient group configuration.
  * @retval HAL_OK      - Calibration configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_BUSY    - A conversion is currently running.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_CalibrationCoefficientGroupConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                            HAL_ADC_CalCoefGrpTypeDef Group,
                                                            const HAL_ADC_CaliCoefGrpConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);

    if (Handle->State & (HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE)) {
        return ADC_CaliCoefGrpCfg(Handle, Group, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the calibration group for a specific ADC channel.
  * @note   The parameters include the coefficient group and whether 
  *         the saturation arithmetic is supported. 
  * @param  Handle ADC handle
  * @param  Channel ADC channel number to be set.
  * @param  pCfg Pointer to a HAL_ADC_ChannelCaliConfTypeDef structure
  *         containing the group and saturation arithmetic configuration.
  * @retval HAL_OK      - Calibration configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_BUSY    - A conversion is currently running.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_ChannelCalibrationConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                   HAL_ADC_ChTypeDef Channel,
                                                   const HAL_ADC_ChannelCaliConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_CHANNEL_NUMBER(Channel));

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL) || (!IS_ADC_CHANNEL_NUMBER(Channel))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);

    if (Handle->State & (HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE)) {
        return ADC_CaliChCfg(Handle, Channel, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure the auto-calibration parameters of the ADC.
  * @note   Auto-calibration allows the ADC to determine and correct its own
  *         offset and gain errors. The configuration selects the calibration
  *         mode (single-ended or differential) and the oversampling ratio used
  *         during the calibration phase.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_AutoCaliConfTypeDef structure containing
  *         the auto-calibration configuration.
  * @retval HAL_OK      - Auto-calibration configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_BUSY    - A conversion or a calibration is currently running.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_AutoCalibrationConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                const HAL_ADC_AutoCaliConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);

    if (Handle->State & (HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE)) {
        return ADC_AutoCaliCfg(Handle, pCfg);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Configure an analog watchdog for a selected channel or for all
  *         channels of a group.
  * @note   The analog watchdog monitors the converted data and raises an
  *         interrupt or sets a flag when the data falls outside the configured
  *         high/low threshold window. The watchdog can be configured to monitor
  *         a single channel, all channels of the regular group, all channels of
  *         the injected group, or any combination. A filtering feature can also
  *         be enabled to require several consecutive out-of-window samples
  *         before triggering an event.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_AnalogWDGConfTypeDef structure containing
  *         the watchdog configuration.
  * @retval HAL_OK      - Analog watchdog configuration completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - The ADC is already running with a conversion, or the
  *                       handle is not in a configurable state.
  */
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(HAL_ADC_HandleTypeDef *Handle, 
                                          const HAL_ADC_AnalogWDGConfTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(pCfg->Channel < HAL_ADC_CH_NUMS);
    ASSERT_FUNC_PARAM(pCfg->WatchdogNumber < HAL_ADC_AWDG_NUMS);

    HAL_ADC_PARAM_CHECK({
        if ((pCfg == NULL)) {
            return HAL_INVALID;
        }

        if (pCfg->Channel >= HAL_ADC_CH_NUMS || pCfg->WatchdogNumber >= HAL_ADC_AWDG_NUMS) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING);

    /* Parameters that can be updated only when the ADC is disabled. */
    if ((Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    return ADC_AWDG_Cfg(Handle, pCfg);
}

/**
  * @brief  Configure the bias current of the ADC analog front-end.
  * @note   The bias current influences the ADC conversion speed and accuracy.
  *         This parameter must be set while the ADC is disabled.
  * @param  Handle ADC handle
  * @param  Current Bias current value to be set.
  * @retval HAL_OK      - Bias current configuration completed successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The handle is not in a configurable state.
  * @retval HAL_FAILED  - The ADC is already enabled.
  */
HAL_StatusTypeDef HAL_ADC_BiasCurrentConfig(HAL_ADC_HandleTypeDef *Handle, 
                                            HAL_ADC_BiasCurTypeDef Current)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING);

    /* Parameters that can be updated only when the ADC is disabled. */
    if ((Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    if (!LL_ADC_IsEnabled(Handle->Instance)) {
        LL_ADC_SetBiasCurrent(Handle->Instance, Current);
    } else {
        return HAL_FAILED;
    }

    return HAL_OK;
}

/**
 * @brief  Configure the ADC saturation thresholds (minimum and maximum) for the selected group.
 * @param  Handle ADC handle
 * @param  Group Specifies the ADC group whose saturation thresholds are to be configured.
 *         This parameter can be one of the following values:
 *           @arg HAL_ADC_GROUP_REGULAR  : Regular conversion group
 *           @arg HAL_ADC_GROUP_INJECTED : Injected conversion group
 * @param  Minimum Minimum saturation threshold value to be written.
 * @param  Maximum Maximum saturation threshold value to be written.
 * @retval HAL_OK       - Configuration completed successfully.
 * @retval HAL_ERROR    - Invalid handle, invalid ADC instance, or ADC is not in configuring/active state.
 * @retval HAL_BUSY     - A conversion is currently running; configuration cannot be performed.
 * @retval HAL_INVALID  - Invalid group value (only possible if the Group parameter is not valid).
 */
HAL_StatusTypeDef HAL_ADC_SaturationThresholdsConfig(HAL_ADC_HandleTypeDef *Handle, 
                                                     HAL_ADC_SampGrpTypeDef Group,
                                                     int16_t Minimum, 
                                                     int16_t Maximum)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);

    if (Handle->State & (HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE)) {
        return ADC_SatThresCfg(Handle, Group, Minimum, Maximum);
    } else {
        return HAL_ERROR;
    }
}

/**
  * @}
  */ /* ADC_HAL_EF_Configuration */


/** @defgroup ADC_HAL_EF_Operation ADC Operation Function
  * @brief    ADC Operation Function
  * @{
  */

/**
  * @brief  Enable the ADC peripheral and its analog front-end.
  * @note   This function does not start any conversion. It only prepares the
  *         ADC for operation by enabling the internal reference, bias, and
  *         channel circuitry, and then waits for the ADC to become ready.
  *         The handle state is transitioned from CONFIGURING to READY, and
  *         then to ACTIVE.
  * @param  Handle ADC handle
  * @retval HAL_OK      - ADC enabled successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The handle is not in the CONFIGURING state.
  * @retval HAL_FAILED  - The hardware activation failed.
  */
HAL_StatusTypeDef HAL_ADC_Start(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    HAL_StatusTypeDef status = HAL_OK;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING);

    HAL_ADC_PARAM_UPDATE(Handle->State, HAL_ADC_STATE_CONFIGURING, HAL_ADC_STATE_READY, {
        return HAL_ERROR;
    });

    /* Activate the ADC analog front-end and enable the peripheral. */
    if (ADC_Activate(Handle) != HAL_OK) {
        Handle->State = HAL_ADC_STATE_CONFIGURING;
        return HAL_FAILED;
    }

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_READY);

    Handle->State       = HAL_ADC_STATE_ACTIVE;
    Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
    Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;

    return status;
}

/**
  * @brief  Disable the ADC peripheral and return it to the CONFIGURING state.
  * @note   This function stops all ongoing conversions on both the regular and
  *         injected groups, disables the ADC peripheral, and clears all
  *         pending interrupts and flags. The handle state is returned to
  *         CONFIGURING so that the configuration can be modified again.
  * @param  Handle ADC handle
  * @retval HAL_OK      - ADC disabled successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The handle is not in the ACTIVE state.
  */
HAL_StatusTypeDef HAL_ADC_Stop(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = ADC_Deactivate(Handle);

    /* Clear flags and disable interrupts. */
    ADC_DisableAndClearIT(Handle);

    if (status == HAL_OK) {
        Handle->State       = HAL_ADC_STATE_CONFIGURING;
        Handle->RegGrpState = HAL_ADC_GRP_STATE_CONFIG;
        Handle->InjGrpState = HAL_ADC_GRP_STATE_CONFIG;
    }

    /* Return function status. */
    return status;
}

/**
  * @brief  Start the ADC regular group conversion (polling mode).
  * @note   This function updates the regular group conversion mode, then starts
  *          the ADC regular group conversion. It is used for software-triggered
  *          or hardware-triggered conversions without interrupts. The regular
  *          group state is set to ACTIVE during conversion and returned to IDLE
  *          if the start fails.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Regular group conversion started successfully.
  * @retval HAL_ERROR   - Invalid ADC handle or ADC not in ACTIVE state.
  * @retval HAL_BUSY    - The regular group is already active.
  * @retval HAL_FAILED  - Invalid regular group configuration.
  */
HAL_StatusTypeDef HAL_ADC_RegularStartConv(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_IDLE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    HAL_ADC_PARAM_UPDATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_IDLE, HAL_ADC_GRP_STATE_ACTIVE, {
        return HAL_BUSY;
    });

    /* Update the regular conversion group configuration. */
    status = ADC_REG_ConvGrpUpdate(Handle);
    if (status != HAL_OK) {
        Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
        return HAL_FAILED;
    }

    /* Start the ADC regular group conversion. */
    status = ADC_REG_StartConv(Handle);
    if (status != HAL_OK) {
        Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Start the next regular conversion in discontinuous mode.
  * @note   This function is used to trigger the next conversion of the regular
  *          group when operating in discontinuous conversion mode. It verifies that
  *          the conversion group and ADC are in valid states, then starts the next
  *          sub-conversion if allowed by the configuration.
  * @param  Handle ADC handle, pointer to ADC_HandleTypeDef structure.
  * @retval HAL_OK      - The next conversion was started successfully.
  * @retval HAL_ERROR   - Parameter error or ADC/regular group not in active state.
  * @retval HAL_BUSY    - The regular group is not in the IDLE state.
  * @retval HAL_FAILED  - Operation not allowed by the current ADC configuration.
  * @retval HAL_TIMEOUT - The hardware did not acknowledge the start of the
  *                       conversion within the configured timeout.
  */
HAL_StatusTypeDef HAL_ADC_RegularStartNextConv(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_ACTIVE);

    uint32_t conv_mode;
    HAL_StatusTypeDef status = HAL_OK;
    ADC_TypeDef *p_instance = Handle->Instance;

    if ((!(Handle->State & HAL_ADC_STATE_ACTIVE))           ||
        (!(Handle->RegGrpState & HAL_ADC_GRP_STATE_ACTIVE)) ) {
        return HAL_ERROR;
    }

    conv_mode = LL_ADC_REG_GetContinuousMode(p_instance);

    /* Re-check the regular group setting */
    if (((LL_ADC_REG_GetSequencerDiscont(p_instance)) && (LL_ADC_INJ_GetTrigAuto(p_instance)))) {
        return HAL_FAILED;
    }

    /* Discontinuous Conversion Mode */
    if (((LL_ADC_REG_GetSequencerDiscont(p_instance)) && (conv_mode == LL_ADC_REG_CONV_SINGLE))) {
        /* Start the ADC regular group conversion. */
        status = ADC_REG_StartConv(Handle);
        if (status == HAL_OK) {
            return HAL_OK;
        }
    }

    return status;
}

/**
  * @brief  Start the ADC injected group conversion (polling mode).
  * @note   This function updates the injected group conversion mode, then starts
  *          the ADC injected group conversion. It is used for software-triggered
  *          or hardware-triggered conversions without interrupts. The injected
  *          group state is set to ACTIVE during conversion and returned to IDLE
  *          if the start fails.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Injected group conversion started successfully.
  * @retval HAL_ERROR   - Invalid ADC handle or ADC not in ACTIVE state.
  * @retval HAL_BUSY    - The injected group is already active.
  * @retval HAL_FAILED  - Invalid injected group configuration.
  */
HAL_StatusTypeDef HAL_ADC_InjectedStartConv(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_IDLE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    /* In automatic injection mode, JADSTART must remain cleared. */
    if (LL_ADC_INJ_GetTrigAuto(Handle->Instance)) {
        return HAL_FAILED;
    }

    HAL_ADC_PARAM_UPDATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_IDLE, HAL_ADC_GRP_STATE_ACTIVE, {
        return HAL_BUSY;
    });

    /* Update the injected conversion group configuration. */
    status = ADC_INJ_ConvGrpUpdate(Handle);
    if (status != HAL_OK) {
        Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
        return HAL_FAILED;
    }

    /* Start the ADC injected group conversion. */
    status = ADC_INJ_StartConv(Handle);
    if (status != HAL_OK) {
        Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Start the next injected conversion in discontinuous mode.
  * @note   This function is used to trigger the next conversion of the injected
  *          group when operating in discontinuous conversion mode. It verifies that
  *          the conversion group and ADC are in valid states, then starts the next
  *          sub-conversion if allowed by the configuration.
  * @param  Handle ADC handle, pointer to ADC_HandleTypeDef structure.
  * @retval HAL_OK      - The next conversion was started successfully.
  * @retval HAL_ERROR   - Parameter error or ADC/injected group not in active state.
  * @retval HAL_BUSY    - The injected group is not in the IDLE state.
  * @retval HAL_FAILED  - Operation not allowed by the current ADC configuration.
  * @retval HAL_TIMEOUT - The hardware did not acknowledge the start of the
  *                       conversion within the configured timeout.
  */
HAL_StatusTypeDef HAL_ADC_InjectedStartNextConv(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_ACTIVE);

    uint32_t is_sw_trg;
    HAL_StatusTypeDef status = HAL_OK;
    ADC_TypeDef *p_instance = Handle->Instance;

    if ((!(Handle->State & HAL_ADC_STATE_ACTIVE))           ||
        (!(Handle->InjGrpState & HAL_ADC_GRP_STATE_ACTIVE)) ) {
        return HAL_ERROR;
    }

    /* Re-check the injected group setting */
    is_sw_trg = LL_ADC_INJ_GetTriggerEdge(p_instance);
    if ((LL_ADC_INJ_GetTrigAuto(p_instance)) || (is_sw_trg != LL_ADC_SEQ_TRIG_POL_SW)) {
        return HAL_FAILED;
    }

    /* Discontinuous Conversion Mode */
    if ((LL_ADC_INJ_GetSequencerDiscont(p_instance))) {
        /* Start the ADC injected group conversion. */
        status = ADC_INJ_StartConv(Handle);
        if (status == HAL_OK) {
            return HAL_OK;
        }
    }

    return status;
}

/**
  * @brief  Stop the conversion of the regular group.
  * @note   This function stops an ongoing regular conversion and returns the
  *         regular group state to IDLE.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Regular conversion stopped successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The handle is not in the ACTIVE state.
  * @retval HAL_TIMEOUT - The hardware did not acknowledge the stop request
  *                       within the configured timeout.
  */
HAL_StatusTypeDef HAL_ADC_RegularStopConv(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    status = ADC_REG_StopConv(Handle);
    if (status == HAL_OK) {
        Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Stop the conversion of the injected group.
  * @note   This function stops an ongoing injected conversion and returns the
  *         injected group state to IDLE.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Injected conversion stopped successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_ERROR   - The handle is not in the ACTIVE state.
  * @retval HAL_TIMEOUT - The hardware did not acknowledge the stop request
  *                       within the configured timeout.
  */
HAL_StatusTypeDef HAL_ADC_InjectedStopConv(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    status = ADC_INJ_StopConv(Handle);
    if (status == HAL_OK) {
        Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Start the ADC regular group conversion with interrupt (IT mode).
  * @note   This function clears the relevant regular group interrupt flags,
  *          enables the end-of-sequence interrupt, and starts the conversion.
  *          The regular group state is set to ACTIVE and remains ACTIVE until
  *          the conversion is completed or stopped by the interrupt handler or
  *          HAL_ADC_RegularStopConv_IT().
  * @param  Handle ADC handle
  * @retval HAL_OK      - Conversion started successfully with interrupts enabled.
  * @retval HAL_ERROR   - Invalid ADC handle or ADC not in ACTIVE state.
  * @retval HAL_BUSY    - The regular group is already active.
  * @retval HAL_FAILED  - Invalid regular group configuration.
  */
HAL_StatusTypeDef HAL_ADC_RegularStartConv_IT(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_IDLE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    HAL_ADC_PARAM_UPDATE(Handle->RegGrpState, HAL_ADC_GRP_STATE_IDLE, HAL_ADC_GRP_STATE_ACTIVE, {
        return HAL_BUSY;
    });

    /* Update the regular conversion group configuration. */
    status = ADC_REG_ConvGrpUpdate(Handle);
    if (status != HAL_OK) {
        Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
        return HAL_FAILED;
    }

    /* Clear ADC group regular interrupt flag. */
    (void)HAL_ADC_InterruptFlagClear(Handle,    HAL_ADC_ISR_REGULAR_SEQUENCE_END_IT_FLAG | 
                                                HAL_ADC_ISR_REGULAR_CONVERT_END_IT_FLAG);

    /* Enable ADC end of conversion interrupt. */    
    (void)HAL_ADC_InterruptRequestEnable(Handle,HAL_ADC_IER_REGULAR_SEQUENCE_END_IT_EN);

    /* Injected auto-conversion relevant interrupt. */
    if (LL_ADC_INJ_GetTrigAuto(Handle->Instance)) {
        (void)HAL_ADC_InterruptFlagClear(Handle,    HAL_ADC_ISR_INJECTED_SEQUENCE_END_IT_FLAG | 
                                                    HAL_ADC_ISR_INJECTED_CONVERT_END_IT_FLAG);

        (void)HAL_ADC_InterruptRequestEnable(Handle,HAL_ADC_IER_REGULAR_SEQUENCE_END_IT_EN | 
                                                    HAL_ADC_IER_INJECTED_SEQUENCE_END_IT_EN);
    }

    /* Start the ADC regular group conversion. */
    status = ADC_REG_StartConv(Handle);
    if (status != HAL_OK) {
        Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Stop the ADC regular group conversion with interrupt (IT mode).
  * @note   This function disables the regular group end-of-sequence interrupt and
  *          stops the ongoing conversion. The regular group state is set to IDLE
  *          if the stop operation succeeds.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Conversion stopped and interrupts disabled.
  * @retval HAL_ERROR   - Invalid ADC handle or ADC not in ACTIVE state.
  */
HAL_StatusTypeDef HAL_ADC_RegularStopConv_IT(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    /* Stop the ADC regular group conversion. */
    status = ADC_REG_StopConv(Handle);
    if (status == HAL_OK) {
        /* Disable ADC end of conversion interrupt. */    
        (void)HAL_ADC_InterruptRequestDisable(Handle, HAL_ADC_IER_REGULAR_SEQUENCE_END_IT_EN);

        /* Injected auto-conversion relevant interrupt. */
        if (LL_ADC_INJ_GetTrigAuto(Handle->Instance)) {
            (void)HAL_ADC_InterruptRequestDisable(Handle, HAL_ADC_IER_INJECTED_SEQUENCE_END_IT_EN);
        }
        
        Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Start the ADC injected group conversion with interrupt (IT mode).
  * @note   This function updates the injected group conversion mode, clears the
  *          relevant injected group interrupt flags, enables the injected sequence
  *          end interrupt, and starts the conversion. The injected group state is
  *          set to ACTIVE and remains ACTIVE until the conversion is completed or
  *          stopped by HAL_ADC_InjectedStopConv_IT() or the interrupt handler.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Conversion started successfully with interrupts enabled.
  * @retval HAL_ERROR   - Invalid ADC handle or ADC not in ACTIVE state.
  * @retval HAL_BUSY    - The injected group is already active.
  * @retval HAL_FAILED  - Invalid injected group configuration.
  */
HAL_StatusTypeDef HAL_ADC_InjectedStartConv_IT(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);
    ASSERT_FUNC_STATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_IDLE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    /* In automatic injection mode, JADSTART must remain cleared. */
    if (LL_ADC_INJ_GetTrigAuto(Handle->Instance)) {
        return HAL_FAILED;
    }

    HAL_ADC_PARAM_UPDATE(Handle->InjGrpState, HAL_ADC_GRP_STATE_IDLE, HAL_ADC_GRP_STATE_ACTIVE, {
        return HAL_BUSY;
    });

    /* Update the injected conversion group configuration. */
    status = ADC_INJ_ConvGrpUpdate(Handle);
    if (status != HAL_OK) {
        Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
        return HAL_FAILED;
    }

    /* Clear ADC group injected interrupt flag. */
    (void)HAL_ADC_InterruptFlagClear(Handle,    HAL_ADC_ISR_INJECTED_SEQUENCE_END_IT_FLAG | 
                                                HAL_ADC_ISR_INJECTED_CONVERT_END_IT_FLAG);

    /* Enable ADC end of conversion interrupt. */    
    (void)HAL_ADC_InterruptRequestEnable(Handle,HAL_ADC_IER_INJECTED_SEQUENCE_END_IT_EN);

    /* Start the ADC injected group conversion. */
    status = ADC_INJ_StartConv(Handle);
    if (status != HAL_OK) {
        Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Stop the ADC injected group conversion.
  * @note   This function stops the ongoing injected group conversion. If the stop
  *          operation succeeds, it disables the injected sequence end interrupt and
  *          sets the injected group state to IDLE.
  * @param  Handle ADC handle
  * @retval HAL_OK    Conversion stopped and interrupts disabled.
  * @retval HAL_ERROR Invalid ADC handle or ADC not in ACTIVE state.
  */
HAL_StatusTypeDef HAL_ADC_InjectedStopConv_IT(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    status = ADC_INJ_StopConv(Handle);
    if (status == HAL_OK) {
        /* Disable ADC end of conversion interrupt. */    
        (void)HAL_ADC_InterruptRequestDisable(Handle,HAL_ADC_IER_INJECTED_SEQUENCE_END_IT_EN);

        Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
    }

    return status;
}

/**
  * @brief  Start the ADC auto-calibration process.
  * @note   This function launches the auto-calibration process that determines
  *         and stores the internal offset and gain correction factors. The ADC
  *         must be active but no conversion may be running. The handle state
  *         is temporarily set to CALIB while the calibration is in progress.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Auto-calibration completed successfully.
  * @retval HAL_INVALID - A parameter is invalid.
  * @retval HAL_BUSY    - The handle is not in the ACTIVE state.
  * @retval HAL_TIMEOUT - The calibration did not complete within the configured
  *                       timeout period.
  */
HAL_StatusTypeDef HAL_ADC_AutoCalibration(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    HAL_ADC_PARAM_UPDATE(Handle->State, HAL_ADC_STATE_ACTIVE, HAL_ADC_STATE_CALIB, {
        return HAL_BUSY;
    });

    status = ADC_AutoCalibration(Handle);

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CALIB);

    if (status != HAL_TIMEOUT) {
        Handle->State = HAL_ADC_STATE_ACTIVE;
    }

    return status;
}

/**
  * @brief  Poll for a specific ADC event.
  * @note   This function blocks until the specified ADC event (e.g., overflow,
  *          analog watchdog, etc.) is raised. When the event flag is set, it is
  *          cleared before returning. The function can be called when the ADC is
  *          either in configuring state or active state.
  * @param  Handle ADC handle
  * @param  EventType ADC event type to wait for
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK      - The specified event occurred and its flag was cleared.
  * @retval HAL_TIMEOUT - Timeout occurred, the event flag was not set.
  * @retval HAL_ERROR   - Parameter error or invalid ADC state.
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(HAL_ADC_HandleTypeDef *Handle,
                                       HAL_ADC_ITPendingMskTypeDef EventType,
                                       uint32_t Timeout)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_CONFIGURING | HAL_ADC_STATE_ACTIVE);

    return ADC_PollITEvt(Handle, EventType, Timeout);
}

/**
  * @brief  Wait for regular group conversion to be completed.
  * @note   This function blocks until the ADC regular group conversion completes.
  *          If the regular sequence length is 1, it waits for the end of the unitary
  *          conversion; otherwise, it waits for the end of the complete regular
  *          conversion sequence.
  *          After the conversion completes, if the conversion mode is single conversion
  *          (HAL_ADC_GRP_CONV_ONCE), the regular group state is set to idle.
  * @param  Handle ADC handle
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK       - Regular group conversion completed.
  * @retval HAL_TIMEOUT  - Timeout occurred, conversion not completed.
  * @retval HAL_ERROR    - Parameter error or invalid ADC state (not in active state).
  */
HAL_StatusTypeDef HAL_ADC_PollForRegularConversion(HAL_ADC_HandleTypeDef *Handle, 
                                                   uint32_t Timeout)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    status = ADC_PollRegConvSeq(Handle, Timeout);  

    if (status == HAL_OK) {
        if (Handle->RegGrpConv == HAL_ADC_GRP_CONV_ONCE) {
            Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
        }        
    }

    return status;
}

/**
  * @brief  Wait for injected group conversion to be completed.
  * @note   This function blocks until the ADC injected group conversion completes.
  *          If the injected sequence length is 1, it waits for the end of the unitary
  *          conversion; otherwise, it waits for the end of the complete injected
  *          conversion sequence.
  *          After the conversion completes, if the conversion mode is single conversion
  *          (HAL_ADC_GRP_CONV_ONCE), the injected group state is set to idle.
  * @param  Handle ADC handle
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK       - Injected group conversion completed.
  * @retval HAL_TIMEOUT  - Timeout occurred, conversion not completed.
  * @retval HAL_ERROR    - Parameter error or invalid ADC state (not in active state).
  */
HAL_StatusTypeDef HAL_ADC_PollForInjectedConversion(HAL_ADC_HandleTypeDef *Handle, 
                                                    uint32_t Timeout)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_STATE(Handle->State, HAL_ADC_STATE_ACTIVE);

    HAL_StatusTypeDef status = HAL_OK;

    if (!(Handle->State & HAL_ADC_STATE_ACTIVE)) {
        return HAL_ERROR;
    }

    status = ADC_PollInjConvSeq(Handle, Timeout);   

    if (status == HAL_OK) {
        if (Handle->InjGrpConv == HAL_ADC_GRP_CONV_ONCE) {
            Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
        }        
    }

    return status;
}

/**
  * @brief  Get the conversion result of the regular group.
  * @note   Reading the regular data register automatically clears the
  *         end-of-conversion flag (EOC) for the regular group.
  * @note   This function does not clear the end-of-sequence flag (EOS). The EOS
  *         flag behavior depends on the sequencer configuration:
  *         - If the regular sequencer contains a single rank, EOS is equivalent
  *           to EOC.
  *         - If the sequencer contains multiple ranks, only EOC is raised at
  *           the end of each single conversion, while both EOC and EOS are
  *           raised at the end of the complete scan sequence.
  * @param  Handle ADC handle
  * @retval The 16-bit ADC conversion data of the regular group.
  */
uint16_t HAL_ADC_GetValue(const HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    /* Note: The EOC flag is not cleared here by software because it is        */
    /*       automatically cleared by the hardware when reading the data       */
    /*       register.                                                         */

    /* Return the ADC converted value. */
    return (uint16_t)LL_ADC_REG_ReadConversionData(Handle->Instance);
}

/**
  * @brief  Get the conversion result of a specific channel stored in the
  *         regular sequence data registers.
  * @note   The ADC must have completed the conversion of the specified channel.
  *         The channel data register is updated at each end of conversion.
  * @param  Handle ADC handle
  * @param  Channel ADC channel whose conversion data is to be read.
  * @retval The 16-bit ADC conversion data of the specified channel.
  */
uint16_t HAL_ADC_RegularGetValue(const HAL_ADC_HandleTypeDef *Handle, 
                                 HAL_ADC_ChTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Channel < HAL_ADC_CH_NUMS);

    /* Return the conversion data of the specified channel. */
    return (uint16_t)LL_ADC_ReadChannelData(Handle->Instance, Channel);
}

/**
  * @brief  Get the conversion result of a specific rank in the injected
  *         sequence.
  * @note   The ADC must have completed the conversion of the specified rank.
  * @param  Handle ADC handle
  * @param  Number Rank number in the injected sequence to be read.
  * @retval The 16-bit ADC conversion data of the specified injected rank.
  */
uint16_t HAL_ADC_InjectedGetValue(const HAL_ADC_HandleTypeDef *Handle, 
                                  HAL_ADC_INJ_SeqNumTypeDef Number)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Number < HAL_ADC_INJ_SEQ_NUMS);

    /* Return the conversion data of the specified injected sequence number. */
    return (uint16_t)LL_ADC_INJ_ReadConversionData(Handle->Instance, Number);
}

/**
  * @brief  Start DMA transfer for a specific ADC channel.
  * @note   This function clears all ADC interrupt status flags (EOC, EOS, JEOC,
  *          JEOS, OVR) and then starts the DMA transfer for the specified channel.
  *          It is used to configure a DMA-based conversion for a single channel.
  * @param  Handle ADC handle
  * @param  Channel ADC channel to start DMA for
  * @retval HAL_OK      - Operation completed successfully.
  */
HAL_StatusTypeDef HAL_ADC_ChannelDMAStart(HAL_ADC_HandleTypeDef *Handle, 
                                          HAL_ADC_ChTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Channel < HAL_ADC_CH_NUMS);

    /* Clear flags */
    LL_ADC_ClearFlag_DONx(Handle->Instance, Channel);
    
    /* Start DMA trnsfer */
    LL_ADC_DMA_ChannelStart(Handle->Instance, Channel);

    return HAL_OK;
}

/**
  * @brief  Stop DMA transfer for a specific ADC channel.
  * @note   This function stops the DMA transfer currently configured for the
  *          specified ADC channel.
  * @param  Handle ADC handle
  * @param  Channel ADC channel to stop DMA for, a value of @ref HAL_ADC_ChTypeDef.
  * @retval HAL_OK      - Operation completed successfully.
  */
HAL_StatusTypeDef HAL_ADC_ChannelDMAStop(HAL_ADC_HandleTypeDef *Handle, 
                                         HAL_ADC_ChTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Channel < HAL_ADC_CH_NUMS);

    LL_ADC_DMA_ChannelStop(Handle->Instance, Channel);

    return HAL_OK;
}

/**
  * @brief  Get DMA status for a specific ADC channel.
  * @note   This function checks whether the DMA transfer for the specified ADC
  *          channel is in the process of stopping. It can be used after calling
  *          HAL_ADC_ChannelDMAStop() to determine when the DMA has fully stopped.
  * @param  Handle ADC handle
  * @param  Channel ADC channel to check
  * @retval HAL_OK      - DMA is not stopping and is ready for new transfers.
  * @retval HAL_BUSY    - DMA is currently in the process of stopping.
  * @note  This function provides a non-blocking way to verify DMA stop completion.
  */
HAL_StatusTypeDef HAL_ADC_GetDMAStatus(HAL_ADC_HandleTypeDef *Handle, 
                                       HAL_ADC_ChTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Channel < HAL_ADC_CH_NUMS);

    if (LL_ADC_DMA_IsStopping(Handle->Instance, Channel)) {
        return HAL_BUSY;
    } else {
        return HAL_OK;
    }
}

/**
  * @brief  Read the converted data of the master ADC in a dual/quad mode
  *         configuration.
  * @note   Only the master ADC can read this data; the slave ADC does not have
  *         access to the combined data register.
  * @param  Handle ADC handle
  * @retval The 16-bit conversion data of the master ADC, or 0xFFFF if the
  *         handle does not refer to a master ADC.
  */
uint16_t HAL_ADC_GetMasterChannelValue(const HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADC_MASTER_INSTANCE(Handle->Instance));
    
    HAL_ADC_PARAM_CHECK({
        if (!IS_ADC_MASTER_INSTANCE(Handle->Instance)) {
            return 0xFFFF;
        }
    });

    /* Return the master ADC converted data. */
    return (uint16_t)LL_ADC_REG_GetMasterConvData(Handle->Instance);
}

/**
  * @brief  Read the converted data of the slave ADC in a dual/quad mode
  *         configuration.
  * @note   Only the master ADC can read this data; the slave ADC does not have
  *         access to the combined data register.
  * @param  Handle ADC handle
  * @retval The 16-bit conversion data of the slave ADC, or 0xFFFF if the
  *         handle does not refer to a master ADC.
  */
uint16_t HAL_ADC_GetSlaveChannelValue(const HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADC_MASTER_INSTANCE(Handle->Instance));
    
    HAL_ADC_PARAM_CHECK({
        if (!IS_ADC_MASTER_INSTANCE(Handle->Instance)) {
            return 0xFFFF;
        }
    });

    /* Return the slave ADC converted data. */
    return (uint16_t)LL_ADC_REG_GetSlaveConvData(Handle->Instance);
}

/**
  * @}
  */ /* ADC_HAL_EF_Operation */

/** @defgroup ADC_HAL_EF_Interrupt ADC Interrupt Handler and Callback
  * @brief    ADC Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  Enable one or more ADC interrupt sources.
  * @param  Handle ADC handle
  * @param  InterruptRequests Bitmask of the interrupt sources to enable.
  *         This parameter can be any combination of @ref HAL_ADC_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully enabled.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_ADC_InterruptRequestEnable(HAL_ADC_HandleTypeDef *Handle,
                                                 HAL_ADC_ITEnMskTypeDef InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    LL_ADC_EnableIT(Handle->Instance, InterruptRequests);

    return HAL_OK;
}

/**
  * @brief  Disable one or more ADC interrupt sources.
  * @param  Handle ADC handle
  * @param  InterruptRequests Bitmask of the interrupt sources to disable.
  *         This parameter can be any combination of @ref HAL_ADC_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully disabled.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_ADC_InterruptRequestDisable(HAL_ADC_HandleTypeDef *Handle,
                                                  HAL_ADC_ITEnMskTypeDef InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    LL_ADC_DisableIT(Handle->Instance, InterruptRequests);

    return HAL_OK;
}

/**
  * @brief  Clear a specific ADC interrupt pending flag.
  * @param  Handle ADC handle
  * @param  InterruptFlag ADC interrupt pending flag(s) to clear, a value or
  *                       combination of @ref HAL_ADC_ITPendingMskTypeDef.
  * @retval HAL_OK  The interrupt flag(s) were cleared successfully.
  */
HAL_StatusTypeDef HAL_ADC_InterruptFlagClear(HAL_ADC_HandleTypeDef *Handle,
                                             HAL_ADC_ITPendingMskTypeDef InterruptFlag)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    LL_ADC_ClearFlag(Handle->Instance, InterruptFlag);

    return HAL_OK;
}

/**
  * @brief  ADC Normal IRQ Handler
  * @note   The pending interrupt flags are cleared automatically by a read or
  *         write access according to the hardware behavior. This function
  *         masks the pending flags with the enabled interrupt sources and then
  *         dispatches to the individual handlers for sampling, regular group,
  *         injected group, analog watchdog, and status events.
  * @param  Handle ADC handle
  * @retval None
  */
void HAL_ADC_NORM_IRQHandler(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    ADC_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_ADC_GetNormAllInterruptEnable(p_instance);
    const uint32_t int_pending = LL_ADC_GetNormalChannelsITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_ADC_ISR_IT_FLAG_MSK; 

    /* Dispatch to the individual interrupt handlers. */
    ADC_SMP_IRQHandler(Handle, flag_status_masked);
    ADC_REG_IRQHandler(Handle, flag_status_masked);
    ADC_INJ_IRQHandler(Handle, flag_status_masked);
    ADC_AWD_IRQHandler(Handle, flag_status_masked);
    ADC_STA_IRQHandler(Handle, flag_status_masked);
}

/**
  * @brief  Callback invoked when the sampling phase of a conversion ends.
  * @note   The application can override this weak function to be notified
  *         when the ADC has finished sampling the analog input and is about
  *         to start the conversion phase.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_EndOfSamplingCallback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_EndOfSamplingCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the ADC peripheral becomes ready after being
  *         enabled.
  * @note   The application can override this weak function to start conversions
  *         or perform additional initialization after the ADC is ready.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_ReadyCallback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_ReadyCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when analog watchdog 2 detects an out-of-window
  *         conversion result.
  * @note   The application can override this weak function to implement a
  *         custom response to the watchdog event.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_AWDG2Callback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_AWDG2Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when analog watchdog 1 detects an out-of-window
  *         conversion result.
  * @note   The application can override this weak function to implement a
  *         custom response to the watchdog event.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_AWDG1Callback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_AWDG1Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when analog watchdog 0 detects an out-of-window
  *         conversion result.
  * @note   The application can override this weak function to implement a
  *         custom response to the watchdog event.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_AWDG0Callback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_AWDG0Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when an overrun event occurs on the regular data
  *         register.
  * @note   An overrun occurs when a new conversion result is written to the
  *         data register before the previous value has been read. The
  *         application can override this weak function to handle the lost
  *         data condition.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_OverflowCallback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_OverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the injected sequence conversion is complete.
  * @note   The application can override this weak function to be notified when
  *         the entire injected sequence has been converted.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_EndOfInjectedSeqCallback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_EndOfInjectedSeqCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a single injected conversion completes.
  * @note   The application can override this weak function to be notified
  *         after each individual conversion within the injected sequence.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_EndOfInjectedConvCallback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_EndOfInjectedConvCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when the regular sequence conversion is complete.
  * @note   The application can override this weak function to be notified when
  *         the entire regular sequence has been converted.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_EndOfRegularSeqCallback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_EndOfRegularSeqCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback invoked when a single regular conversion completes.
  * @note   The application can override this weak function to be notified
  *         after each individual conversion within the regular sequence.
  * @param  Handle ADC handle
  * @retval None
  */
__WEAK void HAL_ADC_NORM_EndOfRegularConvCallback(HAL_ADC_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_NORM_EndOfRegularConvCallback could be implemented in the user file
     */
}


/**
  * @brief  Handle a specific channel's sample conversion-done interrupt.
  * @note   This function checks whether the conversion-done interrupt for the
  *         selected channel is enabled and pending. If both conditions are
  *         satisfied, it clears the pending flag, invokes the per-channel
  *         weak callback, and finally invokes the shared channel callback.
  * @param  Handle ADC handle
  * @param  Channel ADC channel number to be serviced.
  * @retval None
  */
void HAL_ADC_SAMP_ChannelIRQHandler(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Channel < HAL_ADC_CH_NUMS);

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance)) || (Channel >= HAL_ADC_CH_NUMS)) {
            return;
        }
    });

    ADC_TypeDef *p_instance = Handle->Instance;

    /* Sample Channel Conversion Done Interrupt Handler. */
    if (LL_ADC_IsEnabledIT_DONIEx(p_instance, Channel) && LL_ADC_IsActiveFlag_DONx(p_instance, Channel)) {
        /* Clear the conversion-done pending flag. */
        LL_ADC_ClearFlag_DONx(p_instance, Channel);

        /* Invoke the per-channel weak callback. */
        ADC_SAMP_ChxConvDoneCallback[Channel](Handle);

        /* Invoke the shared channel callback. */
        HAL_ADC_SAMP_ChConvDoneCallback(Handle, Channel);
    }
}

/**
  * @brief  Shared callback invoked when the conversion of any channel completes.
  * @note   The application can override this weak function to receive a single
  *         callback for every channel conversion-done event, while still
  *         retaining the per-channel callbacks generated by the macro.
  * @param  Handle ADC handle
  * @param  Channel ADC channel number whose conversion completed.
  * @retval None
  */
__WEAK void HAL_ADC_SAMP_ChConvDoneCallback(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 
    HAL_UNUSED(Channel);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_SAMP_ChConvDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  Handle a specific channel's DMA half-complete interrupt.
  * @note   This function checks whether the DMA half-complete interrupt for
  *         the selected channel is enabled and pending. If both conditions are
  *         satisfied, it clears the pending flag, invokes the per-channel weak
  *         callback, and finally invokes the shared channel callback.
  * @param  Handle ADC handle
  * @param  Channel ADC channel number whose DMA transfer reached half.
  * @retval None
  */
void HAL_ADC_DMA_ChHalfCpltIRQHandler(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Channel < HAL_ADC_CH_NUMS);

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance)) || (Channel >= HAL_ADC_CH_NUMS)) {
            return;
        }
    });

    ADC_TypeDef *p_instance = Handle->Instance;

    /* DMA Channel Half Complete Interrupt Handler. */
    if (LL_ADC_IsEnabledIT_HLFIEx(p_instance, Channel) && LL_ADC_IsActiveFlag_HLFx(p_instance, Channel)) {
        /* Clear the DMA half-complete pending flag. */
        LL_ADC_ClearFlag_HLFx(p_instance, Channel);

        /* Invoke the per-channel weak callback. */
        ADC_DMA_ChxHalfCpltCallback[Channel](Handle);

        /* Invoke the shared channel callback. */
        HAL_ADC_DMA_ChHalfCpltCallback(Handle, Channel);
    }
}

/**
  * @brief  Shared callback invoked when the DMA half-complete event occurs for
  *         any channel.
  * @note   The application can override this weak function to receive a single
  *         callback for every channel half-complete event.
  * @param  Handle ADC handle
  * @param  Channel ADC channel number whose DMA transfer reached half.
  * @retval None
  */
__WEAK void HAL_ADC_DMA_ChHalfCpltCallback(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 
    HAL_UNUSED(Channel);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_DMA_ChHalfCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Handle a specific channel's DMA complete interrupt.
  * @note   This function checks whether the DMA complete interrupt for the
  *         selected channel is enabled and pending. If both conditions are
  *         satisfied, it clears the pending flag, invokes the per-channel weak
  *         callback, and finally invokes the shared channel callback.
  * @param  Handle ADC handle
  * @param  Channel ADC channel number whose DMA transfer completed.
  * @retval None
  */
void HAL_ADC_DMA_ChCpltIRQHandler(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Channel < HAL_ADC_CH_NUMS);

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance)) || (Channel >= HAL_ADC_CH_NUMS)) {
            return;
        }
    });

    ADC_TypeDef *p_instance = Handle->Instance;

    /* DMA Channel Complete Interrupt Handler. */
    if (LL_ADC_IsEnabledIT_FULIEx(p_instance, Channel) && LL_ADC_IsActiveFlag_FULx(p_instance, Channel)) {
        /* Clear the DMA complete pending flag. */
        LL_ADC_ClearFlag_FULx(p_instance, Channel);

        /* Invoke the per-channel weak callback. */
        ADC_DMA_ChxCpltCallback[Channel](Handle);

        /* Invoke the shared channel callback. */
        HAL_ADC_DMA_ChCpltCallback(Handle, Channel);
    }
}

/**
  * @brief  Shared callback invoked when the DMA complete event occurs for any
  *         channel.
  * @note   The application can override this weak function to receive a single
  *         callback for every channel complete event.
  * @param  Handle ADC handle
  * @param  Channel ADC channel number whose DMA transfer completed.
  * @retval None
  */
__WEAK void HAL_ADC_DMA_ChCpltCallback(HAL_ADC_HandleTypeDef *Handle, HAL_ADC_ChTypeDef Channel)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle); 
    HAL_UNUSED(Channel);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADC_DMA_ChCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  Scan all ADC channels and service any enabled and pending channel
  *         conversion-done interrupts.
  * @note   This function is intended for use in a dedicated sample-complete
  *         interrupt handler. It reads the global sampling interrupt enable and
  *         pending registers, masks them, and then iterates through every ADC
  *         channel to handle the corresponding conversion-done event.
  * @param  Handle ADC handle
  * @retval None
  */
void HAL_ADC_SAMP_IRQHandler(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    HAL_ADC_ChTypeDef ch;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Read the sampling interrupt enable and pending registers. */
    const uint32_t int_en = LL_ADC_GetAllSampleEnabledIT(p_instance);
    const uint32_t int_pending = LL_ADC_GetAllSampleITPending(p_instance);

    /* Keep only the enabled and pending flags aligned to channel bits. */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_ADC_DISR_IT_FLAG_MSK; 

    /* Scan through every available ADC channel. */
    for (ch = HAL_ADC_CH_0; ch < HAL_ADC_CH_NUMS; ch++) {
        /* Channel Conversion Done Interrupt Handler. */
        if ((flag_status_masked & BIT(ch))) {
            /* Clear the conversion-done pending flag for this channel. */
            LL_ADC_ClearFlag_DONx(p_instance, ch);

            /* Invoke the per-channel weak callback. */
            ADC_SAMP_ChxConvDoneCallback[ch](Handle);

            /* Invoke the shared channel callback. */
            HAL_ADC_SAMP_ChConvDoneCallback(Handle, ch);
        }
    }
}

ADC_SAMP_CHx_CONV_DONE_CALLBACK(0);                     /*!< ADC Sample Channel 0 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(1);                     /*!< ADC Sample Channel 1 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(2);                     /*!< ADC Sample Channel 2 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(3);                     /*!< ADC Sample Channel 3 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(4);                     /*!< ADC Sample Channel 4 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(5);                     /*!< ADC Sample Channel 5 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(6);                     /*!< ADC Sample Channel 6 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(7);                     /*!< ADC Sample Channel 7 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(8);                     /*!< ADC Sample Channel 8 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(9);                     /*!< ADC Sample Channel 9 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(10);                    /*!< ADC Sample Channel 10 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(11);                    /*!< ADC Sample Channel 11 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(12);                    /*!< ADC Sample Channel 12 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(13);                    /*!< ADC Sample Channel 13 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(14);                    /*!< ADC Sample Channel 14 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(15);                    /*!< ADC Sample Channel 15 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(16);                    /*!< ADC Sample Channel 16 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(17);                    /*!< ADC Sample Channel 17 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(18);                    /*!< ADC Sample Channel 18 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(19);                    /*!< ADC Sample Channel 19 Conversion Done Interrupt Callback   */


/**
  * @brief  ADC DMA Half Complete IRQ Handler
  * @param  Handle ADC handle
  * @return None
  */
void HAL_ADC_DMA_HalfCpltIRQHandler(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    HAL_ADC_ChTypeDef ch;

    ADC_TypeDef *p_instance = Handle->Instance;

    /* Interrupt Enalbe and Pending Get */
    const uint32_t int_en = LL_ADC_GetAllHalfCpltEnabledIT(p_instance);
    const uint32_t int_pending = LL_ADC_GetAllHalfCpltITPending(p_instance);

    /* Logical AND between flags status and interrupts sources enabled (for registers bitfields aligned) */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_ADC_HISR_DMA_HALF_IT_FLAG_MSK; 

    /* Scan through every available ADC channel. */
    for (ch = HAL_ADC_CH_0; ch < HAL_ADC_CH_NUMS; ch++) {
        /* DMA Half Complete Interrupt Handler. */
        if ((flag_status_masked & BIT(ch))) {
            /* Clear the DMA half complete pending flag for this channel. */
            LL_ADC_ClearFlag_HLFx(p_instance, ch);

            /* Invoke the per-channel weak callback. */
            ADC_DMA_ChxHalfCpltCallback[ch](Handle);

            /* Invoke the shared channel callback. */
            HAL_ADC_DMA_ChHalfCpltCallback(Handle, ch);
        }
    }
}

/* Generate weak per-channel DMA half-complete callbacks. */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(0);                      /*!< ADC DMA Channel 0 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(1);                      /*!< ADC DMA Channel 1 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(2);                      /*!< ADC DMA Channel 2 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(3);                      /*!< ADC DMA Channel 3 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(4);                      /*!< ADC DMA Channel 4 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(5);                      /*!< ADC DMA Channel 5 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(6);                      /*!< ADC DMA Channel 6 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(7);                      /*!< ADC DMA Channel 7 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(8);                      /*!< ADC DMA Channel 8 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(9);                      /*!< ADC DMA Channel 9 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(10);                     /*!< ADC DMA Channel 10 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(11);                     /*!< ADC DMA Channel 11 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(12);                     /*!< ADC DMA Channel 12 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(13);                     /*!< ADC DMA Channel 13 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(14);                     /*!< ADC DMA Channel 14 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(15);                     /*!< ADC DMA Channel 15 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(16);                     /*!< ADC DMA Channel 16 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(17);                     /*!< ADC DMA Channel 17 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(18);                     /*!< ADC DMA Channel 18 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(19);                     /*!< ADC DMA Channel 19 Half Complete Interrupt Callback    */

/**
  * @brief  Scan all ADC channels and service any enabled and pending DMA
  *         complete interrupts.
  * @note   This function reads the global DMA complete interrupt enable and
  *         pending registers, masks them, and then iterates through every ADC
  *         channel to handle the corresponding complete event.
  * @param  Handle ADC handle
  * @retval None
  */
void HAL_ADC_DMA_CpltIRQHandler(HAL_ADC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    HAL_ADC_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADC_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    HAL_ADC_ChTypeDef ch;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Read the DMA complete interrupt enable and pending registers. */
    const uint32_t int_en = LL_ADC_GetAllCpltEnabledIT(p_instance);
    const uint32_t int_pending = LL_ADC_GetAllCpltITPending(p_instance);

    /* Keep only the enabled and pending flags aligned to channel bits. */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_ADC_FISR_DMA_FULL_IT_FLAG_MSK; 

    /* Scan through every available ADC channel. */
    for (ch = HAL_ADC_CH_0; ch < HAL_ADC_CH_NUMS; ch++) {
        /* DMA Complete Interrupt Handler. */
        if ((flag_status_masked & BIT(ch))) {
            /* Clear the DMA complete pending flag for this channel. */
            LL_ADC_ClearFlag_FULx(p_instance, ch);

            /* Invoke the per-channel weak callback. */
            ADC_DMA_ChxCpltCallback[ch](Handle);

            /* Invoke the shared channel callback. */
            HAL_ADC_DMA_ChCpltCallback(Handle, ch);
        }
    }
}

/* Generate weak per-channel DMA complete callbacks. */
ADC_DMA_CHx_CPLT_CALLBACK(0);                    /*!< ADC DMA Channel 0  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(1);                    /*!< ADC DMA Channel 1  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(2);                    /*!< ADC DMA Channel 2  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(3);                    /*!< ADC DMA Channel 3  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(4);                    /*!< ADC DMA Channel 4  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(5);                    /*!< ADC DMA Channel 5  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(6);                    /*!< ADC DMA Channel 6  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(7);                    /*!< ADC DMA Channel 7  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(8);                    /*!< ADC DMA Channel 8  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(9);                    /*!< ADC DMA Channel 9  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(10);                   /*!< ADC DMA Channel 10 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(11);                   /*!< ADC DMA Channel 11 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(12);                   /*!< ADC DMA Channel 12 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(13);                   /*!< ADC DMA Channel 13 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(14);                   /*!< ADC DMA Channel 14 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(15);                   /*!< ADC DMA Channel 15 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(16);                   /*!< ADC DMA Channel 16 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(17);                   /*!< ADC DMA Channel 17 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(18);                   /*!< ADC DMA Channel 18 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(19);                   /*!< ADC DMA Channel 19 Complete Interrupt Callback    */

/**
  * @}
  */ /* ADC_HAL_EF_Interrupt */

/**
  * @}
  */ /* ADC_HAL_Exported_Functions */


/* Private Functions ---------------------------------------------------------*/
/** @defgroup ADC_HAL_Private_Functions ADC HAL Private Functions
  * @brief    ADC HAL Private Functions
  * @{
  */

/**
  * @brief  Enable the selected ADC instance and wait until it becomes ready.
  * @note   This function first verifies that the ADC is not already enabled.
  *         If it is not active, the ready flag is cleared, the ADC is enabled,
  *         and the function waits for the ready flag to be set by the hardware.
  *         A timeout is implemented to avoid being stuck if the ADC cannot
  *         be enabled (e.g., missing clock).
  * @param  Handle ADC handle
  * @retval HAL_OK      - ADC enabled successfully.
  * @retval HAL_TIMEOUT - The ADC did not become ready within the allowed time.
  * @retval HAL_ERROR   - The ADC was already enabled but not in the expected
  *                       internal state.
  */
static HAL_StatusTypeDef ADC_Enable(HAL_ADC_HandleTypeDef *Handle)
{
    uint32_t tickstart;  
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Enable the ADC and wait for the ready flag. */
    if (!LL_ADC_IsEnabled(p_instance)) {
        /* Check that the ADC is not already active. */
        if (!LL_ADC_IsActivated(p_instance)) {
            /* Clear the ADC ready flag before enabling. */
            LL_ADC_ClearFlag_ADRDY(p_instance);

            /* Enable the ADC peripheral. */
            LL_ADC_Enable(p_instance);

            /* Wait for the hardware to assert the ready flag. */
            tickstart = HAL_GetTick();
            while (!LL_ADC_IsActiveFlag_ADRDY(p_instance)) {
                /* If the ADC was not effectively started, re-assert the enable. */
                if (!LL_ADC_IsEnabled(p_instance)) {
                    LL_ADC_Enable(p_instance);
                }

                /* Check for timeout. */
                if ((HAL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
                    /* Re-check to avoid false timeout detection. */
                    if (!LL_ADC_IsActiveFlag_ADRDY(p_instance)) {
                        return HAL_TIMEOUT;
                    }
                }
            }            
        } else {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Disable the selected ADC instance and wait until it is effectively
  *         turned off.
  * @note   This function only disables the ADC when no conversion is running.
  *         The ready flag is cleared after the disable request, and the
  *         function waits for the hardware to confirm that the ADC is no
  *         longer running.
  * @param  Handle ADC handle
  * @retval HAL_OK      - ADC disabled successfully.
  * @retval HAL_TIMEOUT - The ADC did not turn off within the allowed time.
  * @retval HAL_ERROR   - A conversion is still running, or the ADC is in an
  *                       unexpected internal state.
  */
static HAL_StatusTypeDef ADC_Disable(HAL_ADC_HandleTypeDef *Handle)
{
    uint32_t tickstart;  
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Check whether the ADC is still running or stopping. */
    if ((LL_ADC_IsEnabled(p_instance)) || LL_ADC_IsDisableOngoing(p_instance)) {
        /* Verify that no conversion is in progress before disabling. */
        if ((!LL_ADC_IsConversionRunning(p_instance))) {
            /* Disable the ADC peripheral. */
            LL_ADC_Disable(p_instance);

            /* Clear the ADC ready flag. */
            LL_ADC_ClearFlag_ADRDY(p_instance);

            /* Wait for the hardware to acknowledge the disable. */
            tickstart = HAL_GetTick();
            while (LL_ADC_IsEnabled(p_instance)) {
                /* Check for timeout. */
                if ((HAL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
                    /* Re-check to avoid false timeout detection. */
                    if (LL_ADC_IsEnabled(p_instance)) {
                        return HAL_TIMEOUT;
                    }
                }
            }
        } else {
            /* A conversion is in progress: cannot disable. */
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}


/**
  * @brief  Update the regular conversion group configuration (internal function).
  * @details This function validates the current regular and injected group settings
  *          for unsupported combinations:
  *          - Regular discontinuous mode with regular continuous conversion mode.
  *          - Regular discontinuous mode with injected auto-conversion enabled.
  *          - Injected auto-conversion enabled with injected trigger not set to software.
  *          If any invalid combination is found, HAL_FAILED is returned.
  *          If the configuration is valid, it updates the handle's regular group
  *          conversion mode:
  *          - HAL_ADC_GRP_CONV_ONCE if regular conversion mode is single and
  *            regular trigger is software.
  *          - HAL_ADC_GRP_CONV_CONTINUOUS otherwise.
  *          Additionally, it updates the injected group conversion mode metadata:
  *          - HAL_ADC_GRP_CONV_CONTINUOUS if auto-injection is enabled or the
  *            injected trigger is not software (the injected group may be triggered
  *            without a one-shot software start).
  *          - HAL_ADC_GRP_CONV_ONCE otherwise.
  * @param  Handle ADC handle, pointer to ADC_HandleTypeDef structure.
  * @retval HAL_OK      - Configuration is valid and conversion group states were updated.
  * @retval HAL_FAILED  - Invalid configuration detected.
  * @note  This function does not start any conversion; it only refreshes metadata.
  */
static HAL_StatusTypeDef ADC_REG_ConvGrpUpdate(HAL_ADC_HandleTypeDef *Handle)
{
    ADC_TypeDef *p_instance = Handle->Instance;
    uint32_t conv_mode = LL_ADC_REG_GetContinuousMode(p_instance);
    uint32_t is_discrete = LL_ADC_REG_GetSequencerDiscont(p_instance);
    uint32_t is_auto_inj = LL_ADC_INJ_GetTrigAuto(p_instance);
    uint32_t is_inj_trg = LL_ADC_INJ_GetTriggerEdge(p_instance);

    /* Re-check the regular group setting */
    if (((is_discrete) && (conv_mode == LL_ADC_REG_CONV_CONTINUOUS)) ||
        ((is_discrete) && (is_auto_inj)) ||
        ((is_auto_inj) && (is_inj_trg != LL_ADC_SEQ_TRIG_POL_SW))) {
        return HAL_FAILED;
    }

    /* Refresh the conversion group state. */
    if ((conv_mode == LL_ADC_REG_CONV_SINGLE) && (LL_ADC_REG_GetTriggerEdge(p_instance) == LL_ADC_SEQ_TRIG_POL_SW)) {
        Handle->RegGrpConv = HAL_ADC_GRP_CONV_ONCE;
    } else {
        Handle->RegGrpConv = HAL_ADC_GRP_CONV_CONTINUOUS;
    }

    /* The channels in the injected group will be converted automatically after the regular group channels. */
    if ((is_auto_inj) || (is_inj_trg != LL_ADC_SEQ_TRIG_POL_SW)) {
        Handle->InjGrpConv = HAL_ADC_GRP_CONV_CONTINUOUS;
    } else {
        Handle->InjGrpConv = HAL_ADC_GRP_CONV_ONCE;
    }

    return HAL_OK;
}

/**
  * @brief  Update the injected conversion group configuration.
  * @details This function checks the current ADC injected group settings for invalid
  *          combinations (auto-injection combined with regular discontinuous mode, or
  *          auto-injection with non-software trigger). If the configuration is valid,
  *          it updates the handle's injected group conversion mode:
  *          - HAL_ADC_GRP_CONV_ONCE if auto-injection is disabled and software trigger
  *          - HAL_ADC_GRP_CONV_CONTINUOUS otherwise
  * @param  Handle ADC handle
  * @retval HAL_OK      - Configuration is valid and the conversion mode was updated.
  * @retval HAL_FAILED  - Invalid injected group configuration detected.
  * @note  This function does not start any conversion; it only refreshes metadata.
  */
static HAL_StatusTypeDef ADC_INJ_ConvGrpUpdate(HAL_ADC_HandleTypeDef *Handle)
{
    ADC_TypeDef *p_instance = Handle->Instance;
    uint32_t is_sw_trg = LL_ADC_INJ_GetTriggerEdge(p_instance);
    uint32_t is_auto_inj = LL_ADC_INJ_GetTrigAuto(p_instance);

    /* Re-check the injected group setting */ 
    if (((is_auto_inj) && (LL_ADC_REG_GetSequencerDiscont(p_instance))) ||
        ((is_auto_inj) && (is_sw_trg != LL_ADC_SEQ_TRIG_POL_SW))) {
        return HAL_FAILED;
    }

    /* Refresh the conversion group state */
    if ((!is_auto_inj) && (is_sw_trg == LL_ADC_SEQ_TRIG_POL_SW)) {
        Handle->InjGrpConv = HAL_ADC_GRP_CONV_ONCE;
    } else {
        Handle->InjGrpConv = HAL_ADC_GRP_CONV_CONTINUOUS;
    }

    return HAL_OK;
}

/**
  * @brief  Start the ADC regular group conversion.
  * @note   This function verifies that the ADC is running and that no regular
  *         conversion is already ongoing. It then starts the conversion and
  *         waits for the hardware to confirm that the conversion has actually
  *         started.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Regular conversion started successfully.
  * @retval HAL_ERROR   - The ADC is not running.
  * @retval HAL_BUSY    - A regular conversion is already in progress.
  * @retval HAL_TIMEOUT - The hardware did not confirm the start in time.
  */
static HAL_StatusTypeDef ADC_REG_StartConv(HAL_ADC_HandleTypeDef *Handle)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Verify that the ADC is running. */
    if (!LL_ADC_IsEnabled(p_instance)) {
        return HAL_ERROR;
    } 

    /* Verify that no regular conversion is already in progress. */
    if (LL_ADC_REG_IsConversionOngoing(p_instance)) {
        return HAL_BUSY;
    }

    /* Start the regular conversion. */
    LL_ADC_REG_StartConversion(p_instance);

    /* Wait until the hardware confirms the conversion has started. */
    tickstart = HAL_GetTick();
    while (!LL_ADC_REG_IsConversionOngoing(p_instance)) {
        if ((HAL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (!LL_ADC_REG_IsConversionOngoing(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    return HAL_OK;
}

/**
  * @brief  Start the ADC injected group conversion.
  * @note   This function verifies that the ADC is running and that no injected
  *         conversion is already ongoing. It then starts the conversion and
  *         waits for the hardware to confirm that the conversion has actually
  *         started.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Injected conversion started successfully.
  * @retval HAL_ERROR   - The ADC is not running.
  * @retval HAL_BUSY    - An injected conversion is already in progress.
  * @retval HAL_TIMEOUT - The hardware did not confirm the start in time.
  */
static HAL_StatusTypeDef ADC_INJ_StartConv(HAL_ADC_HandleTypeDef *Handle)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Verify that the ADC is running. */
    if (!LL_ADC_IsEnabled(p_instance)) {
        return HAL_ERROR;
    } 

    /* Verify that no injected conversion is already in progress. */
    if (LL_ADC_INJ_IsConversionOngoing(p_instance)) {
        return HAL_BUSY;
    }

    /* Start the injected conversion. */
    LL_ADC_INJ_StartConversion(p_instance);

    /* Wait until the hardware confirms the conversion has started. */
    tickstart = HAL_GetTick();
    while (!LL_ADC_INJ_IsConversionOngoing(p_instance)) {
        if ((HAL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (!LL_ADC_INJ_IsConversionOngoing(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    return HAL_OK;
}

/**
  * @brief  Stop the ADC regular group conversion.
  * @note   This function stops an ongoing regular conversion and waits until
  *         the hardware acknowledges the stop. If no conversion is running or
  *         stopping, the function returns HAL_OK immediately.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Regular conversion stopped successfully.
  * @retval HAL_TIMEOUT - The hardware did not confirm the stop in time.
  */
static HAL_StatusTypeDef ADC_REG_StopConv(HAL_ADC_HandleTypeDef *Handle)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Check whether a regular conversion is running or stopping. */
    if ((!LL_ADC_REG_IsConversionOngoing(p_instance)) 
    &&  (!LL_ADC_REG_IsStopConversionOngoing(p_instance))) {
        return HAL_OK;
    }
    
    /* Request the hardware to stop the regular conversion. */
    LL_ADC_REG_StopConversion(p_instance);

    /* Wait until the conversion has actually stopped. */
    tickstart = HAL_GetTick();
    while (LL_ADC_REG_IsConversionOngoing(p_instance)) {
        if ((HAL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (LL_ADC_REG_IsConversionOngoing(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    return HAL_OK;
}

/**
  * @brief  Stop the ADC injected group conversion.
  * @note   This function stops an ongoing injected conversion and waits until
  *         the hardware acknowledges the stop. If no conversion is running or
  *         stopping, the function returns HAL_OK immediately.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Injected conversion stopped successfully.
  * @retval HAL_TIMEOUT - The hardware did not confirm the stop in time.
  */
static HAL_StatusTypeDef ADC_INJ_StopConv(HAL_ADC_HandleTypeDef *Handle)
{
    uint32_t tickstart;  
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Check whether an injected conversion is running or stopping. */
    if ((!LL_ADC_INJ_IsConversionOngoing(p_instance)) 
    &&  (!LL_ADC_INJ_IsStopConversionOngoing(p_instance))) {
        return HAL_OK;
    }

    /* Request the hardware to stop the injected conversion. */
    LL_ADC_INJ_StopConversion(p_instance);

    /* Wait until the conversion has actually stopped. */
    tickstart = HAL_GetTick();
    while (LL_ADC_INJ_IsConversionOngoing(p_instance)) {
        if ((HAL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (LL_ADC_INJ_IsConversionOngoing(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    return HAL_OK;
}

/**
  * @brief  Activate the ADC by enabling its internal analog blocks and the ADC
  *         peripheral.
  * @note   This function is called by HAL_ADC_Start(). It enables the channel
  *         logic, the voltage reference, and the bias current, and then invokes
  *         ADC_Enable() to switch on the ADC core.
  * @param  Handle ADC handle
  * @retval HAL_OK      - ADC activated successfully.
  * @retval HAL_TIMEOUT - The ADC did not become ready in time.
  * @retval HAL_ERROR   - The ADC could not be enabled.
  */
static HAL_StatusTypeDef ADC_Activate(HAL_ADC_HandleTypeDef *Handle)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Enable the analog front-end components. */
    LL_ADC_AssertPreparingStart(p_instance);

    /* Enable the ADC peripheral and wait for readiness. */
    return ADC_Enable(Handle);
}

/**
  * @brief  Deactivate the ADC by stopping all conversions and disabling the
  *         ADC peripheral.
  * @note   This function is called by HAL_ADC_Stop() and HAL_ADC_DeInit(). It
  *         stops any ongoing regular and injected conversions, then disables
  *         the ADC core.
  * @param  Handle ADC handle
  * @retval HAL_OK      - ADC deactivated successfully.
  * @retval HAL_TIMEOUT - The ADC did not turn off in time.
  */
static HAL_StatusTypeDef ADC_Deactivate(HAL_ADC_HandleTypeDef *Handle)
{
    HAL_StatusTypeDef status = HAL_OK;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Stop any ongoing regular conversion. */
    if (LL_ADC_REG_IsConversionOngoing(p_instance)) {
        (void)ADC_REG_StopConv(Handle);
    }

    /* Stop any ongoing injected conversion. */
    if (LL_ADC_INJ_IsConversionOngoing(p_instance)) {
        (void)ADC_INJ_StopConv(Handle);
    }

    /* Disable the ADC peripheral. */
    status = ADC_Disable(Handle);

    /* Disable the analog front-end components. */
    if (status == HAL_OK) {
        LL_ADC_ReleasePreparingStart(p_instance);
    }

    return status;
}

/**
  * @brief  Run the ADC auto-calibration.
  * @note   The auto-calibration uses the ADC internal reference to determine
  *         the offset and gain correction values. The function waits until the
  *         calibration phase is complete.
  * @param  Handle ADC handle
  * @retval HAL_OK      - Auto-calibration completed successfully.
  * @retval HAL_ERROR   - The ADC is not running.
  * @retval HAL_BUSY    - A conversion is already in progress.
  * @retval HAL_TIMEOUT - The calibration did not finish in time.
  */
static HAL_StatusTypeDef ADC_AutoCalibration(HAL_ADC_HandleTypeDef *Handle)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Verify that the ADC is running. */
    if (!LL_ADC_IsEnabled(p_instance)) {
        return HAL_ERROR;
    }

    /* Verify that no conversion is in progress. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_BUSY;
    }
    
    /* Start the auto-calibration. */
    LL_ADC_StartCalibration(p_instance);

    /* Wait until the calibration has completed. */
    tickstart = HAL_GetTick();
    while (LL_ADC_IsCalibrationOnGoing(p_instance)) {
        if ((HAL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (LL_ADC_IsCalibrationOnGoing(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    return HAL_OK;
}

/**
  * @brief  Disable all ADC interrupt enables and clear all pending interrupt
  *         flags.
  * @note   This helper is used when stopping or de-initializing the ADC to put
  *         the interrupt logic into a clean state.
  * @param  Handle ADC handle
  * @retval None
  */
__STATIC_FORCEINLINE void ADC_DisableAndClearIT(HAL_ADC_HandleTypeDef *Handle)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Disable the DMA half-complete interrupt enables. */
    LL_ADC_DMA_DisableHalfFullIT(p_instance, LL_ADC_HIER_DMA_HALF_IT_EN_MSK);

    /* Disable the DMA complete interrupt enables. */
    LL_ADC_DMA_DisableFullIT(p_instance, LL_ADC_FIER_DMA_FULL_IT_EN_MSK);

    /* Disable the per-channel data interrupt enables. */
    LL_ADC_DisableDataIT(p_instance, LL_ADC_DIER_IT_EN_MSK);

    /* Disable the global interrupt enables. */
    LL_ADC_DisableIT(p_instance, LL_ADC_IER_IT_EN_MSK);

    /* Clear the DMA half-complete pending flags. */
    LL_ADC_DMA_ClearHalfFullFlag(p_instance, LL_ADC_HISR_DMA_HALF_IT_FLAG_MSK);

    /* Clear the DMA complete pending flags. */
    LL_ADC_DMA_ClearFullFlag(p_instance, LL_ADC_FISR_DMA_FULL_IT_FLAG_MSK);

    /* Clear the per-channel data pending flags. */
    LL_ADC_ClearDataFlag(p_instance, LL_ADC_DISR_IT_FLAG_MSK);

    /* Clear the global pending flags. */
    LL_ADC_ClearFlag(p_instance, LL_ADC_ISR_IT_FLAG_MSK);
}

/**
  * @brief  Apply the oversampling configuration to the ADC hardware.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to the oversampling configuration structure.
  * @return HAL_OK on success, HAL_BUSY if a conversion is running,
  *         or HAL_INVALID if the configuration is not supported.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_OverSampCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       const HAL_ADC_OversampConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Refuse configuration while a conversion is running. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the oversampling mode. */
    switch (pCfg->OversamplingMode) {
        case HAL_ADC_SAMP_MODE_OVER_SAMP_DISABLE:
            LL_ADC_SetOverSamplingScope(p_instance, LL_ADC_SAMP_MODE_OVER_SAMP_DISABLE);
            break;

        case HAL_ADC_SAMP_MODE_REG_CONTINUED:
            LL_ADC_SetOverSamplingScope(p_instance, LL_ADC_SAMP_MODE_REG_CONTINUED);
            break;

        case HAL_ADC_SAMP_MODE_REG_RESUMED:
            LL_ADC_SetOverSamplingScope(p_instance, LL_ADC_SAMP_MODE_REG_RESUMED);
            break;

        case HAL_ADC_SAMP_MODE_TRIGGERED_REG_RESUMED:
            LL_ADC_SetOverSamplingScope(p_instance, LL_ADC_SAMP_MODE_TRIGGERED_REG_RESUMED);
            break;

        case HAL_ADC_SAMP_MODE_INJ_REG_RESUMED:
            LL_ADC_SetOverSamplingScope(p_instance, LL_ADC_SAMP_MODE_INJ_REG_RESUMED);
            break;

        case HAL_ADC_SAMP_MODE_INJ:
            LL_ADC_SetOverSamplingScope(p_instance, LL_ADC_SAMP_MODE_INJ);
            break;

        default:
            return HAL_INVALID;
    }

    /* Configure the oversampling ratio and right bit shift. */
    LL_ADC_SetOverSamplingRatio(p_instance, pCfg->Ratio);
    LL_ADC_SetOverSamplingRightShift(p_instance, pCfg->RightBitShift);

    return HAL_OK;
}

/**
  * @brief  Apply the regular group configuration to the ADC hardware.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to the regular group configuration structure.
  * @return HAL_OK on success, or HAL_BUSY if a regular conversion is running.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_REG_Cfg(HAL_ADC_HandleTypeDef *Handle, 
                                                   const HAL_ADC_RegularConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Refuse configuration while a regular conversion is running. */
    if (LL_ADC_REG_IsConversionOngoing(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the overrun behavior. */
    LL_ADC_REG_SetOverrun(p_instance, pCfg->Overrun);

    /* Configure the number of conversions in the regular sequence. */
    LL_ADC_REG_SetSequencerLength(p_instance, pCfg->NbrOfConversion);

    /* External trigger event: when using a hardware trigger, ensure that the   */
    /* interval between trigger events is longer than the injection sequence.   */
    if (pCfg->ExternalTrigConv != HAL_ADC_SEQ_TRIG_EVT_SOFTWARE) {
        LL_ADC_REG_SetTriggerSource(p_instance, pCfg->ExternalTrigConv);
        LL_ADC_REG_SetTriggerEdge(p_instance, pCfg->ExternalTrigConvEdge);
    } else {
        LL_ADC_REG_SetTriggerEdge(p_instance, LL_ADC_SEQ_TRIG_POL_SW);
    }
    
    /* The continuous mode and the discontinuous mode are mutually exclusive.   */
    /* If both are enabled, the continuous mode is treated as disabled.         */
    if ((pCfg->DiscontinuousConvMode == HAL_ADC_DISCONTINUE_CONV_ENABLE) &&
        (pCfg->ContinuousConvMode == HAL_ADC_REG_CONV_CONTINUOUS)) {
        LL_ADC_REG_SetContinuousMode(p_instance, LL_ADC_REG_CONV_SINGLE);
    } else {
        LL_ADC_REG_SetContinuousMode(p_instance, pCfg->ContinuousConvMode);
    }

    /* The automatic injection mode and the discontinuous mode cannot be used   */
    /* simultaneously. When automatic injection is enabled, discontinuous mode  */
    /* must be disabled.                                                        */
    if ((pCfg->DiscontinuousConvMode == HAL_ADC_DISCONTINUE_CONV_ENABLE) && 
        (!LL_ADC_INJ_GetTrigAuto(p_instance))) {
        LL_ADC_REG_SetSequencerDiscontNumber(p_instance, pCfg->NbrOfDiscConversion);
        LL_ADC_REG_EnableSequencerDiscont(p_instance);
    } else {
        LL_ADC_REG_DisableSequencerDiscont(p_instance);
    }

    return HAL_OK;
}

/**
  * @brief  Apply the injected group configuration to the ADC hardware.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to the injected group configuration structure.
  * @return HAL_OK on success, HAL_INVALID if an illegal combination is
  *         requested, or HAL_BUSY if an injected conversion is running.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_INJ_Cfg(HAL_ADC_HandleTypeDef *Handle, 
                                                   const HAL_ADC_InjectionConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Automatic injection and discontinuous mode cannot be used together. */
    if ((LL_ADC_REG_GetSequencerDiscont(p_instance)) 
    &&  (pCfg->AutoInjectedConv == HAL_ADC_INJ_AUTO_CONV_ENABLE)) {
        return HAL_INVALID;
    }

    /* In automatic injection mode, external triggers on the injected group     */
    /* are not allowed.                                                         */
    if ((pCfg->ExternalTrigInjecConv != HAL_ADC_SEQ_TRIG_EVT_SOFTWARE)
    &&  (pCfg->AutoInjectedConv == HAL_ADC_INJ_AUTO_CONV_ENABLE)) {
        return HAL_INVALID;
    }

    /* Refuse configuration while an injected conversion is running. */
    if (LL_ADC_INJ_IsConversionOngoing(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the number of conversions in the injected sequence. */
    LL_ADC_INJ_SetSequencerLength(p_instance, pCfg->InjectedNbrOfConversion);

    /* External trigger event: when using a hardware trigger, ensure that the   */
    /* interval between trigger events is longer than the injection sequence.   */
    if (pCfg->ExternalTrigInjecConv != HAL_ADC_SEQ_TRIG_EVT_SOFTWARE) {
        LL_ADC_INJ_DisableTrigAuto(p_instance);
        LL_ADC_INJ_SetTriggerSource(p_instance, pCfg->ExternalTrigInjecConv);
        LL_ADC_INJ_SetTriggerEdge(p_instance, pCfg->ExternalTrigInjecConvEdge);
    } else {
        LL_ADC_INJ_SetTriggerEdge(p_instance, LL_ADC_SEQ_TRIG_POL_SW);
    }

    /* Configure automatic injection and the injected discontinuous mode. */
    if (pCfg->AutoInjectedConv == HAL_ADC_INJ_AUTO_CONV_ENABLE) {
        LL_ADC_INJ_DisableSequencerDiscont(p_instance);
        LL_ADC_INJ_EnableTrigAuto(p_instance);
    } else {
        LL_ADC_INJ_DisableTrigAuto(p_instance);
        
        /* Injected discontinuous mode */
        if (pCfg->InjectedDiscontinuousConvMode == HAL_ADC_DISCONTINUE_CONV_ENABLE) {
            LL_ADC_INJ_EnableSequencerDiscont(p_instance);
        } else {
            LL_ADC_INJ_DisableSequencerDiscont(p_instance);
        } 
    }

    return HAL_OK;
}

/**
  * @brief  Configure a channel and assign it to the selected conversion group.
  * @param  Handle ADC handle
  * @param  Group Conversion group (regular or injected).
  * @param  pCfg Channel configuration structure.
  * @return HAL_OK on success, HAL_INVALID if the channel is invalid,
  *         HAL_BUSY if a conversion is running, or HAL_ERROR if the group is
  *         active.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_ChannelCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                      HAL_ADC_SampGrpTypeDef Group, 
                                                      const HAL_ADC_ChannelConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* In differential mode, the adjacent channel is used as the negative input. */
    if ((pCfg->SingleDiff == HAL_ADC_INPUT_MODE_DIFF) && ((pCfg->Channel + 1) >= HAL_ADC_CH_NUMS)) {
        return HAL_INVALID;
    }

    /* Refuse configuration while a conversion is running. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the channel in the requested group. */
    switch (Group)  {
        case HAL_ADC_GROUP_REGULAR:
            /* Configure only when the regular group is not busy. */
            if (!LL_ADC_REG_IsConversionOngoing(p_instance)) {
                LL_ADC_REG_SetSequencerRanks(p_instance, pCfg->Rank, pCfg->Channel);
                
                /* For differential channels, set the sampling time of the        */
                /* paired negative input as well.                                 */
                if ((pCfg->SingleDiff == LL_ADC_INPUT_MODE_DIFF) && (pCfg->AssignDiffChannel1 == HAL_ADC_FUNC_ENABLE)) {
                    LL_ADC_SetChannelSamplingTime(p_instance, pCfg->Channel + 1, pCfg->SamplingTime);
                }
            } else {
                return HAL_ERROR;
            }

            break;

        case HAL_ADC_GROUP_INJECTED:
            /* Configure only when the injected group is not busy. */
            if (!LL_ADC_INJ_IsConversionOngoing(p_instance)) {
                LL_ADC_INJ_SetSequencerRanks(p_instance, pCfg->Rank, pCfg->Channel);

                /* For differential channels, set the sampling time of the        */
                /* paired negative input as well.                                 */
                if ((pCfg->SingleDiff == LL_ADC_INPUT_MODE_DIFF) && (pCfg->AssignDiffChannel1 == HAL_ADC_FUNC_ENABLE)) {
                    LL_ADC_SetChannelSamplingTime(p_instance, pCfg->Channel + 1, pCfg->SamplingTime);
                }
            } else {
                return HAL_ERROR;
            }

            break;

        default:
            return HAL_INVALID;
    }

    /* Apply the sampling time and the input mode to the selected channel. */
    LL_ADC_SetChannelSamplingTime(p_instance, pCfg->Channel, pCfg->SamplingTime);
    LL_ADC_SetChannelSingleDiff(p_instance, pCfg->Channel, pCfg->SingleDiff);

    /* Enable Done Interrupt */
    HAL_FUNC_ALTER(pCfg->SamplingCompleteIT,  LL_ADC_EnableIT_DONIEx(p_instance, pCfg->Channel),
                                              LL_ADC_DisableIT_DONIEx(p_instance, pCfg->Channel));

    return HAL_OK;
}

/**
  * @brief  Configure the independent DMA transfer for a specific ADC channel.
  * @note   This interface allows the ADC to transfer conversion data of one
  *         channel automatically to a memory buffer without CPU intervention.
  *         The configuration includes the destination address, the transfer
  *         length in half-words, and the DMA options such as circular mode,
  *         fixed address mode, and interrupt generation.
  * @param  Handle ADC handle
  * @param  pCfg Pointer to a HAL_ADC_IndepDMAConfTypeDef structure containing
  *         the DMA configuration.
  * @retval HAL_OK      - Configuration completed successfully.
  * @retval HAL_BUSY    - The ADC is currently converting.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_IndepDMACfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       const HAL_ADC_IndepDMAConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Check whether the ADC is currently converting. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the DMA transfer address and length for the channel. */
    LL_ADC_DMA_SetTransferAddress(p_instance, pCfg->Channel, pCfg->BufferAddress);
    LL_ADC_DMA_SetTransferLength(p_instance, pCfg->Channel, pCfg->BufferInHalfWords * 2);

    /* Enable or disable the fixed destination address mode. */
    HAL_FUNC_ALTER(pCfg->FixAddress,        LL_ADC_DMA_SetChannelFixAddress(p_instance, pCfg->Channel, LL_ADC_DMA_FIXED_ADDRESS_ENABLE),
                                            LL_ADC_DMA_SetChannelFixAddress(p_instance, pCfg->Channel, LL_ADC_DMA_FIXED_ADDRESS_DISABLE));

    /* Enable or disable the circular mode. */
    HAL_FUNC_ALTER(pCfg->Circulation,       LL_ADC_DMA_SetChannelCirculationMode(p_instance, pCfg->Channel, LL_ADC_DMA_CIRC_MODE_ENABLE),
                                            LL_ADC_DMA_SetChannelCirculationMode(p_instance, pCfg->Channel, LL_ADC_DMA_CIRC_MODE_DISABLE));

    /* Enable or disable the DMA half-complete interrupt. */
    HAL_FUNC_ALTER(pCfg->HalfCompleteIT,    LL_ADC_EnableIT_HLFIEx(p_instance, pCfg->Channel), 
                                            LL_ADC_DisableIT_HLFIEx(p_instance, pCfg->Channel));

    /* Enable or disable the DMA complete interrupt. */
    HAL_FUNC_ALTER(pCfg->CompleteIT,        LL_ADC_EnableIT_FULIEx(p_instance, pCfg->Channel), 
                                            LL_ADC_DisableIT_FULIEx(p_instance, pCfg->Channel));

    return HAL_OK;
}

/**
  * @brief  Apply the channel calibration configuration.
  * @param  Handle ADC handle
  * @param  pCfg Calibration configuration structure.
  * @return HAL_OK on success, or HAL_BUSY if a conversion is running.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_CaliCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                   const HAL_ADC_CalibrationConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Refuse configuration while a conversion is running. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the calibration coefficient group, offset, and gain. */
    LL_ADC_SetCalibrationFactor(p_instance, pCfg->Channel, pCfg->CoefficientGroup);
    LL_ADC_SetOffset(p_instance, pCfg->CoefficientGroup, pCfg->OffsetCompensation);
    LL_ADC_SetGainCompensation(p_instance, pCfg->CoefficientGroup, pCfg->GainCompensation);
    
    /* Enable or disable saturation arithmetic. */
    if (pCfg->Saturation == HAL_ADC_CH_SATURATION_SUPPORT) {
        LL_ADC_SetChannelSaturation(p_instance, pCfg->Channel, LL_ADC_CH_SATURATION_SUPPORT);
    } else {
        LL_ADC_SetChannelSaturation(p_instance, pCfg->Channel, LL_ADC_CH_SATURATION_NOT_SUPPORT);
    }

    return HAL_OK;
}

/**
  * @brief  Apply the calibration coefficient group configuration.
  * @param  Handle ADC handle
  * @param  Group Calibration coefficient group number to be set.
  * @param  pCfg Calibration coefficient group structure.
  * @return HAL_OK on success, or HAL_BUSY if a conversion is running.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_CaliCoefGrpCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                          HAL_ADC_CalCoefGrpTypeDef Group,
                                                          const HAL_ADC_CaliCoefGrpConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Refuse configuration while a conversion is running. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the calibration coefficient group, offset, and gain. */
    LL_ADC_SetOffset(p_instance, Group, pCfg->OffsetCompensation);
    LL_ADC_SetGainCompensation(p_instance, Group, pCfg->GainCompensation);

    return HAL_OK;
}

/**
  * @brief  Apply the calibration channel configuration.
  * @param  Handle ADC handle
  * @param  Channel ADC channel number to be set.
  * @param  pCfg Calibration channel structure.
  * @return HAL_OK on success, or HAL_BUSY if a conversion is running.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_CaliChCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                     HAL_ADC_ChTypeDef Channel,
                                                     const HAL_ADC_ChannelCaliConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Refuse configuration while a conversion is running. */
    if (LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_BUSY;
    }

    LL_ADC_SetCalibrationFactor(p_instance, Channel, pCfg->CoefficientGroup);

    /* Enable or disable saturation arithmetic. */
    if (pCfg->Saturation == HAL_ADC_CH_SATURATION_SUPPORT) {
        LL_ADC_SetChannelSaturation(p_instance, Channel, LL_ADC_CH_SATURATION_SUPPORT);
    } else {
        LL_ADC_SetChannelSaturation(p_instance, Channel, LL_ADC_CH_SATURATION_NOT_SUPPORT);
    }

    return HAL_OK;
}


/**
  * @brief  Apply the auto-calibration configuration.
  * @param  Handle ADC handle
  * @param  pCfg Auto-calibration configuration structure.
  * @return HAL_OK on success, or HAL_BUSY if a conversion or calibration is
  *         running.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_AutoCaliCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       const HAL_ADC_AutoCaliConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Refuse configuration while a conversion or calibration is running. */
    if (LL_ADC_IsConversionRunning(p_instance) || LL_ADC_IsCalibrationOnGoing(p_instance)) {
        return HAL_BUSY;
    }

    /* Configure the calibration mode and the oversampling ratio. */
    LL_ADC_SetCalibrationMode(p_instance, pCfg->Mode);
    LL_ADC_SetAutoCalibrationRatio(p_instance, pCfg->OversamplingRatio);

    return HAL_OK;
}

/**
  * @brief  Apply the analog watchdog configuration.
  * @param  Handle ADC handle
  * @param  pCfg Analog watchdog configuration structure.
  * @return HAL_OK on success, HAL_ERROR if the ADC is running or converting,
  *         or HAL_INVALID if the watchdog mode is not supported.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_AWDG_Cfg(HAL_ADC_HandleTypeDef *Handle, 
                                                    const HAL_ADC_AnalogWDGConfTypeDef *pCfg)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    /* The watchdog can only be configured while the ADC is disabled. */
    if ((LL_ADC_IsEnabled(p_instance)) || LL_ADC_IsConversionRunning(p_instance)) {
        return HAL_ERROR;
    }

    /* Configure the common watchdog parameters. */
    LL_ADC_SetAWDFilteringConfiguration(p_instance, pCfg->WatchdogNumber, pCfg->FilteringConfig);
    LL_ADC_SetAnalogWDThresholdHigh(p_instance, pCfg->WatchdogNumber, (uint32_t)pCfg->HighThreshold);
    LL_ADC_SetAnalogWDThresholdLow(p_instance, pCfg->WatchdogNumber, (uint32_t)pCfg->LowThreshold);

    /* Disable the watchdog monitors and reset the channel selection. */
    LL_ADC_DisableAnalogWDxMonitorRegular(p_instance, pCfg->WatchdogNumber);
    LL_ADC_DisableAnalogWDxMonitorInjected(p_instance, pCfg->WatchdogNumber);

    /* If it is not a custom-defined combined mode, monitoring channels will be reset. */
    if ((pCfg->WatchdogMode != HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_REGULAR) && 
        (pCfg->WatchdogMode != HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_INJECTED) &&
        (pCfg->WatchdogMode != HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_REGULAR_INJECTED)) {
        LL_ADC_ResetAnalogWDChannelMonitor(p_instance, pCfg->WatchdogNumber, LL_ADC_AWDG_MONITOR_CHANNEL_MSK);
    }

    /* Configure the monitoring scope according to the watchdog mode. */
    switch (pCfg->WatchdogMode) {
        case HAL_ADC_AWDG_MONITOR_MODE_DISABLE:
            /* All monitors are disabled, nothing further to do. */
            break;

        case HAL_ADC_AWDG_MONITOR_MODE_SINGLE_REGULAR:
        case HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_REGULAR:
            LL_ADC_EnableAnalogWDChannelMonitor(p_instance, pCfg->WatchdogNumber, pCfg->Channel);
            LL_ADC_EnableAnalogWDxMonitorRegular(p_instance, pCfg->WatchdogNumber);
            break;

        case HAL_ADC_AWDG_MONITOR_MODE_SINGLE_INJECTED:
        case HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_INJECTED:
            LL_ADC_EnableAnalogWDChannelMonitor(p_instance, pCfg->WatchdogNumber, pCfg->Channel);
            LL_ADC_EnableAnalogWDxMonitorInjected(p_instance, pCfg->WatchdogNumber);
            break;

        case HAL_ADC_AWDG_MONITOR_MODE_SINGLE_REGULAR_INJECTED:
        case HAL_ADC_AWDG_MONITOR_MODE_CUSTOM_REGULAR_INJECTED:
            LL_ADC_EnableAnalogWDChannelMonitor(p_instance, pCfg->WatchdogNumber, pCfg->Channel);
            LL_ADC_EnableAnalogWDxMonitorRegular(p_instance, pCfg->WatchdogNumber);
            LL_ADC_EnableAnalogWDxMonitorInjected(p_instance, pCfg->WatchdogNumber);
            break;

        case HAL_ADC_AWDG_MONITOR_MODE_ALL_REGULAR:
            LL_ADC_SetAnalogWDChannelMonitor(p_instance, pCfg->WatchdogNumber, LL_ADC_AWDG_MONITOR_CHANNEL_MSK);
            LL_ADC_EnableAnalogWDxMonitorRegular(p_instance, pCfg->WatchdogNumber);
            break;

        case HAL_ADC_AWDG_MONITOR_MODE_ALL_INJECTED:
            LL_ADC_SetAnalogWDChannelMonitor(p_instance, pCfg->WatchdogNumber, LL_ADC_AWDG_MONITOR_CHANNEL_MSK);
            LL_ADC_EnableAnalogWDxMonitorInjected(p_instance, pCfg->WatchdogNumber);
            break;

        case HAL_ADC_AWDG_MONITOR_MODE_ALL_REGULAR_INJECTED:
            LL_ADC_SetAnalogWDChannelMonitor(p_instance, pCfg->WatchdogNumber, LL_ADC_AWDG_MONITOR_CHANNEL_MSK);
            LL_ADC_EnableAnalogWDxMonitorRegular(p_instance, pCfg->WatchdogNumber);
            LL_ADC_EnableAnalogWDxMonitorInjected(p_instance, pCfg->WatchdogNumber);
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
 * @brief  Configure the saturation thresholds for the specified conversion group.
 * @param  Handle ADC handle
 * @param  Group Specifies the ADC group:
 *           @arg HAL_ADC_GROUP_REGULAR  : Regular group thresholds
 *           @arg HAL_ADC_GROUP_INJECTED : Injected group thresholds
 * @param  Minimum Minimum saturation threshold value (int16_t).
 * @param  Maximum Maximum saturation threshold value (int16_t).
 * @retval HAL_OK       - Thresholds successfully configured.
 * @retval HAL_BUSY     - A conversion is running on the selected group; no changes made.
 * @retval HAL_INVALID  - The Group parameter is not recognized.
 */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_SatThresCfg(HAL_ADC_HandleTypeDef *Handle, 
                                                       HAL_ADC_SampGrpTypeDef Group,
                                                       int16_t Minimum, 
                                                       int16_t Maximum)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    if (Group == HAL_ADC_GROUP_REGULAR) {
        if (LL_ADC_REG_IsConversionOngoing(p_instance)) {
            return HAL_BUSY;
        }

        LL_ADC_REG_SetMinData(p_instance, Minimum);
        LL_ADC_REG_SetMaxData(p_instance, Maximum);

    } else if (Group == HAL_ADC_GROUP_INJECTED) {
        if (LL_ADC_INJ_IsConversionOngoing(p_instance)) {
            return HAL_BUSY;
        }

        LL_ADC_INJ_SetMinData(p_instance, Minimum);
        LL_ADC_INJ_SetMaxData(p_instance, Maximum);

    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Poll the ADC event flag.
  * @note   This function waits until the specified ADC event flag is raised.
  *          During waiting, timeout is checked; once timeout occurs, the flag
  *          status is re-checked to eliminate misjudgment at boundary moments.
  *          After the flag is set, it is cleared.
  * @param  Handle ADC handle
  * @param  EventType ADC event type to wait for,
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK        The event flag was set and cleared.
  * @retval HAL_TIMEOUT   Timed out and the event flag was not set.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollITEvt(HAL_ADC_HandleTypeDef *Handle,
                                                     HAL_ADC_ITPendingMskTypeDef EventType,
                                                     uint32_t Timeout)
{
    ADC_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart= HAL_GetTick();

    /* Wait until selected flag is raised. */
    while (!LL_ADC_IsActiveFlag(p_instance, (uint32_t)EventType)) {
        if ((HAL_GetTick() - tickstart) > Timeout) {
            /* Re-check to avoid false timeout detection. */
            if (!LL_ADC_IsActiveFlag(p_instance, (uint32_t)EventType)) {
                return HAL_TIMEOUT;
            }
        }
    }

    LL_ADC_ClearFlag(p_instance, (uint32_t)EventType);

    return HAL_OK;
}

/**
  * @brief  Poll the regular group conversion end flag.
  * @note   Internal function to wait for the ADC regular group end-of-conversion
  *          interrupt flag to be set. During waiting, timeout is checked; once timeout
  *          occurs, the flag status is re-checked to eliminate misjudgment at boundary
  *          moments. After the flag is set, it is cleared.
  * @param  Handle ADC handle, pointer to ADC_HandleTypeDef structure.
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK        End-of-conversion flag was set and cleared.
  * @retval HAL_TIMEOUT   Timed out and the end-of-conversion flag was not set.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollRegConv(HAL_ADC_HandleTypeDef *Handle, 
                                                       uint32_t Timeout)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Get tick count */
    tickstart = HAL_GetTick();

    /* Wait until end of unitary conversion flag is raised */
    while (!LL_ADC_IsActiveFlag_EOC(p_instance)) {
        if ((HAL_GetTick() - tickstart) > Timeout) {
            /* Re-check to avoid false timeout detection. */
            if (!LL_ADC_IsActiveFlag_EOC(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    /* Clear flag */
    LL_ADC_ClearFlag_EOC(p_instance);

    return HAL_OK;
}

/**
  * @brief  Poll the regular group sequence end flag.
  * @note   This function waits until the ADC regular group sequence end interrupt
  *          flag is set. The sequence end flag indicates that the complete regular
  *          sequence of conversions has finished. During waiting, timeout is checked;
  *          once timeout occurs, the flag status is re-checked to eliminate misjudgment
  *          at boundary moments. After the flag is set, it is cleared.
  * @param  Handle ADC handle
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK       Sequence end flag was set and cleared.
  * @retval HAL_TIMEOUT  Timed out and the sequence end flag was not set.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollRegConvSeq(HAL_ADC_HandleTypeDef *Handle, 
                                                          uint32_t Timeout)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Get tick count */
    tickstart = HAL_GetTick();

    /* Wait until end of unitary conversion flag is raised */
    while (!LL_ADC_IsActiveFlag_EOS(p_instance)) {
        if ((HAL_GetTick() - tickstart) > Timeout) {
            /* Re-check to avoid false timeout detection. */
            if (!LL_ADC_IsActiveFlag_EOS(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    /* Clear flag */
    LL_ADC_ClearFlag_EOS(p_instance);

    return HAL_OK;
}

/**
  * @brief  Poll the injected group conversion end flag.
  * @note   Internal function to wait for the ADC injected group end-of-conversion
  *          interrupt flag to be set. During waiting, timeout is checked; once timeout
  *          occurs, the flag status is re-checked to eliminate misjudgment at boundary
  *          moments. After the flag is set, it is cleared.
  * @param  Handle ADC handle, pointer to ADC_HandleTypeDef structure.
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK       End-of-conversion flag was set and cleared.
  * @retval HAL_TIMEOUT  Timed out and the end-of-conversion flag was not set.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollInjConv(HAL_ADC_HandleTypeDef *Handle, 
                                                       uint32_t Timeout)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Get tick count */
    tickstart = HAL_GetTick();

    /* Wait until end of unitary conversion flag is raised */
    while (!LL_ADC_IsActiveFlag_JEOC(p_instance)) {
        if ((HAL_GetTick() - tickstart) > Timeout) {
            /* Re-check to avoid false timeout detection. */
            if (!LL_ADC_IsActiveFlag_JEOC(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    /* Clear flag */
    LL_ADC_ClearFlag_JEOC(p_instance);

    return HAL_OK;
}

/**
  * @brief  Poll the injected group sequence end flag.
  * @note   This function waits until the ADC injected group sequence end interrupt
  *          flag is set. The sequence end flag indicates that the complete injected
  *          sequence of conversions has finished. During waiting, timeout is checked;
  *          once timeout occurs, the flag status is re-checked to eliminate misjudgment
  *          at boundary moments. After the flag is set, it is cleared.
  * @param  Handle ADC handle, pointer to ADC_HandleTypeDef structure.
  * @param  Timeout Timeout duration in system ticks.
  * @retval HAL_OK       Sequence end flag was set and cleared.
  * @retval HAL_TIMEOUT  Timed out and the sequence end flag was not set.
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef ADC_PollInjConvSeq(HAL_ADC_HandleTypeDef *Handle, 
                                                          uint32_t Timeout)
{
    uint32_t tickstart;
    ADC_TypeDef *p_instance = Handle->Instance;

    /* Get tick count */
    tickstart = HAL_GetTick();

    /* Wait until end of unitary conversion flag is raised */
    while (!LL_ADC_IsActiveFlag_JEOS(p_instance)) {
        if ((HAL_GetTick() - tickstart) > Timeout) {
            /* Re-check to avoid false timeout detection. */
            if (!LL_ADC_IsActiveFlag_JEOS(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    /* Clear flag */
    LL_ADC_ClearFlag_JEOS(p_instance);

    return HAL_OK;
}

/**
  * @brief  ADC Sampling IRQ Handler
  * @param  Handle ADC handle
  * @param  FlagMask Mask containing enabled and pending sampling flags.
  * @return None
  */
__STATIC_FORCEINLINE void ADC_SMP_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask)
{
    if ((FlagMask & LL_ADC_ISR_EOSMP)) {
        /* Clear the sampling-end pending flag. */
        LL_ADC_ClearFlag_EOSMP(Handle->Instance);

        /* Invoke the sampling-end callback. */
        HAL_ADC_NORM_EndOfSamplingCallback(Handle);
    }
}

/**
  * @brief  ADC Status IRQ Handler
  * @param  Handle ADC handle
  * @param  FlagMask Mask containing enabled and pending status flags.
  * @return None
  */
__STATIC_FORCEINLINE void ADC_STA_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_ADC_ISR_STATUS_IT_FLAG_MSK; 

    /* Handle the ADC ready event. */
    if ((flag_status_masked & LL_ADC_ISR_ADRDY)) {
        /* Clear the ready pending flag. */
        LL_ADC_ClearFlag_ADRDY(p_instance);

        /* Invoke the ready callback. */
        HAL_ADC_NORM_ReadyCallback(Handle);
    }

    /* Handle the overrun event. */
    if ((flag_status_masked & LL_ADC_ISR_OVR)) {
        /* Clear the overrun pending flag. */
        LL_ADC_ClearFlag_OVR(p_instance);

        /* Record the overrun error in the handle. */
        Handle->LastErrorCodes |= HAL_ADC_ERROR_OVERRUN;

        /* Invoke the overflow callback. */
        HAL_ADC_NORM_OverflowCallback(Handle);
    }
}

/**
  * @brief  ADC AWDG IRQ Handler
  * @param  Handle ADC handle
  * @param  FlagMask Mask containing enabled and pending watchdog flags.
  * @return None
  */
__STATIC_FORCEINLINE void ADC_AWD_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_ADC_ISR_AWDG_IT_FLAG_MSK; 

    /* If no watchdog flag is pending, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle watchdog 2. */
    if ((flag_status_masked & LL_ADC_ISR_AWD2)) {
        /* Clear the AWDG2 pending flag. */
        LL_ADC_ClearFlag_AWD3(p_instance);

        /* Invoke the AWDG2 callback. */
        HAL_ADC_NORM_AWDG2Callback(Handle);
    }

    /* Handle watchdog 1. */
    if ((flag_status_masked & LL_ADC_ISR_AWD1)) {
        /* Clear the AWDG1 pending flag. */
        LL_ADC_ClearFlag_AWD2(p_instance);

        /* Invoke the AWDG1 callback. */
        HAL_ADC_NORM_AWDG1Callback(Handle);
    }

    /* Handle watchdog 0. */
    if ((flag_status_masked & LL_ADC_ISR_AWD0)) {
        /* Clear the AWDG0 pending flag. */
        LL_ADC_ClearFlag_AWD1(p_instance);

        /* Invoke the AWDG0 callback. */
        HAL_ADC_NORM_AWDG0Callback(Handle);
    }
}

/**
  * @brief  ADC Regular IRQ Handler
  * @param  Handle ADC handle
  * @param  FlagMask Mask containing enabled and pending regular flags.
  * @return None
  */
__STATIC_FORCEINLINE void ADC_REG_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_ADC_ISR_REG_IT_FLAG_MSK; 

    /* If no regular flag is pending, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle the regular sequence-end event. */
    if ((flag_status_masked & LL_ADC_ISR_EOS)) {
        /* Clear the regular sequence-end pending flag. */
        LL_ADC_ClearFlag_EOS(p_instance);

        if (Handle->RegGrpConv == HAL_ADC_GRP_CONV_ONCE) {
            Handle->RegGrpState = HAL_ADC_GRP_STATE_IDLE;
        }  

        /* Invoke the regular sequence-end callback. */
        HAL_ADC_NORM_EndOfRegularSeqCallback(Handle);
    }

    /* Handle the regular conversion-end event. */
    if ((flag_status_masked & LL_ADC_ISR_EOC)) {
        /* Clear the regular conversion-end pending flag. */
        LL_ADC_ClearFlag_EOC(p_instance);

        /* Invoke the regular conversion-end callback. */
        HAL_ADC_NORM_EndOfRegularConvCallback(Handle);
    }
}

/**
  * @brief  ADC Injected IRQ Handler
  * @param  Handle ADC handle
  * @param  FlagMask Mask containing enabled and pending injected flags.
  * @return None
  */
__STATIC_FORCEINLINE void ADC_INJ_IRQHandler(HAL_ADC_HandleTypeDef *Handle, uint32_t FlagMask)
{
    ADC_TypeDef *p_instance = Handle->Instance;

    const uint32_t flag_status_masked = (FlagMask) & LL_ADC_ISR_INJ_IT_FLAG_MSK; 

    /* If no injected flag is pending, exit immediately. */
    if (!flag_status_masked) {
        return;
    }

    /* Handle the injected sequence-end event. */
    if ((flag_status_masked & LL_ADC_ISR_JEOS)) {
        /* Clear the injected sequence-end pending flag. */
        LL_ADC_ClearFlag_JEOS(p_instance);

        if (Handle->InjGrpConv == HAL_ADC_GRP_CONV_ONCE) {
            Handle->InjGrpState = HAL_ADC_GRP_STATE_IDLE;
        }  

        /* Invoke the injected sequence-end callback. */
        HAL_ADC_NORM_EndOfInjectedSeqCallback(Handle);
    }

    /* Handle the injected conversion-end event. */
    if ((flag_status_masked & LL_ADC_ISR_JEOC)) {
        /* Clear the injected conversion-end pending flag. */
        LL_ADC_ClearFlag_JEOC(p_instance);

        /* Invoke the injected conversion-end callback. */
        HAL_ADC_NORM_EndOfInjectedConvCallback(Handle);
    }

}


/**
  * @}
  */ /* ADC_HAL_Private_Functions */


#endif  /* HAL_ADC_MODULE_ENABLED */
#endif  /* HAL_MODULE_ENABLED */
#endif  /* ADC */

/**
  * @}
  */ /* ADC_HAL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

