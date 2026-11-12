/**
  ******************************************************************************
  * @file    tae32g58xx_hal_cmp.c
  * @author  Tai-Action SD Team
  * @brief   CMP HAL module driver
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

#if defined(CMP0) || defined(CMP1) || defined(CMP2) || defined(CMP3) || defined(CMP4) || \
    defined(CMP5) || defined(CMP6) || defined(CMP7) || defined(CMP8)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_CMP_MODULE_ENABLED) && (HAL_CMP_MODULE_ENABLED == 1)

/** @defgroup CMP_HAL CMP HAL
  * @brief    CMP HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup CMP_HAL_Private_Macros CMP HAL Private Macros
  * @brief    CMP HAL Private Macros
  * @{
  */

/** @defgroup CMP_HAL_PM_Discriminant CMP HAL Discriminant
  * @brief    CMP HAL Discriminant
  * @{
  */

#define IS_CMP_BLK_EVT(__VAL__)                        (((__VAL__) == HAL_CMP_BLK_EVT_SOFTWARE)  || \
                                                        ((__VAL__) == HAL_CMP_BLK_EVT_TMR0_OC0)  || \
                                                        ((__VAL__) == HAL_CMP_BLK_EVT_TMR1_OC0)  || \
                                                        ((__VAL__) == HAL_CMP_BLK_EVT_TMR2_OC0)  || \
                                                        ((__VAL__) == HAL_CMP_BLK_EVT_TMR3_OC0)  || \
                                                        ((__VAL__) == HAL_CMP_BLK_EVT_TMR4_OC0)  || \
                                                        ((__VAL__) == HAL_CMP_BLK_EVT_TMR9_OC0)  || \
                                                        ((__VAL__) == HAL_CMP_BLK_EVT_TMR10_OC0))

#define IS_CMP_POSI_IN_SRC(__VAL__)                    (((__VAL__) == HAL_CMP_POSI_IN_SRC_CMP_INP0) || \
                                                        ((__VAL__) == HAL_CMP_POSI_IN_SRC_CMP_INP1))

#define IS_CMP_NEG_IN_SRC(__VAL__)                     (((__VAL__) == HAL_CMP_NEG_IN_SRC_CMP_INM0)  || \
                                                        ((__VAL__) == HAL_CMP_NEG_IN_SRC_CMP_INM1)  || \
                                                        ((__VAL__) == HAL_CMP_NEG_IN_SRC_DACy_OUT)  || \
                                                        ((__VAL__) == HAL_CMP_NEG_IN_SRC_DACz_OUT))

#define IS_CMP_HYST(__VAL__)                           (((__VAL__) == HAL_CMP_HYST_0mv)    || \
                                                        ((__VAL__) == HAL_CMP_HYST_10mv)   || \
                                                        ((__VAL__) == HAL_CMP_HYST_20mv)   || \
                                                        ((__VAL__) == HAL_CMP_HYST_30mv))

#define IS_CMP_OUT_POL_INV(__VAL__)                    (((__VAL__) == HAL_CMP_OUT_POL_INV_DISABLE) || \
                                                        ((__VAL__) == HAL_CMP_OUT_POL_INV_ENABLE))

#define IS_CMP_EDGE_IT_MODE(__VAL__)                   (((__VAL__) == HAL_CMP_EDGE_IT_MODE_NO)             || \
                                                        ((__VAL__) == HAL_CMP_EDGE_IT_MODE_RISING)         || \
                                                        ((__VAL__) == HAL_CMP_EDGE_IT_MODE_FALLING)        || \
                                                        ((__VAL__) == HAL_CMP_EDGE_IT_MODE_RISING_FALLING))

/**
  * @}
  */ /* CMP_HAL_PM_Discriminant */

/**
  * @}
  */ /* CMP_HAL_EF_Configuration */


/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CMP_HAL_Exported_Functions CMP HAL Exported Functions
  * @brief    CMP HAL Exported Functions
  * @{
  */

/** @defgroup CMP_HAL_EF_Initialization CMP Init and DeInit Functions
  * @brief    CMP Init and DeInit Functions
  * @{
  */

/**
  * @brief  Initialize the CMP peripheral according to the specified parameters
  *         in the HAL_CMP_InitTypeDef structure and initialize the associated handle.
  * @note   This function disables the CMP module before applying the configuration.
  *         The low-level hardware initialization (clock, NVIC) is performed by
  *         HAL_CMP_MspInit(), which the user must re-implement if needed.
  * @param  Handle CMP handle
  * @param  CMPx Pointer to the base address of the CMP peripheral.
  * @param  pInit Pointer to a HAL_CMP_InitTypeDef structure that contains
  *              the configuration information for the CMP peripheral
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_Init(HAL_CMP_HandleTypeDef *Handle, CMP_TypeDef *CMPx, HAL_CMP_InitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(CMPx));
    ASSERT_FUNC_PARAM(pInit != NULL);
    
    HAL_CMP_PARAM_CHECK({
        if (Handle == NULL || !IS_CMP_ALL_INSTANCE(CMPx) || pInit == NULL) {
            return HAL_INVALID;
        }
    })

    Handle->Instance = CMPx;
    Handle->State = HAL_CMP_STATE_INIT;

    /* Init the low level hardware eg. Clock, NVIC */
    HAL_CMP_MspInit(Handle);

    /* Disable the CMP module before applying initialization settings to ensure a clean state */
    LL_CMP_Disable(CMPx);

    /* Disable all interrupt first */
    LL_CMP_DisableIT(CMPx, LL_CMP_EDGE_IT_MODE_RISING | LL_CMP_EDGE_IT_MODE_FALLING);

    /* Initial configuration */
    LL_CMP_SetInputMinus(CMPx, pInit->InputMinus);
    LL_CMP_SetInputPlus(CMPx, pInit->InputPlus);
    LL_CMP_SetInputHysteresis(CMPx, pInit->Hysteresis);
    LL_CMP_SetOutputBlankingSource(CMPx, pInit->BlankingSrce);

    HAL_FUNC_ALTER (pInit->OutputPol == HAL_CMP_OUT_POL_INV_ENABLE, 
            LL_CMP_EnableOutputInvert(CMPx), LL_CMP_DisableOutputInvert(CMPx));

    switch (pInit->TriggerMode)
    {
        case HAL_CMP_EDGE_IT_MODE_NO:
            // Do nothing...
            break;

        case HAL_CMP_EDGE_IT_MODE_RISING:
            LL_CMP_EnableIT(CMPx, LL_CMP_EDGE_IT_MODE_RISING);
            break;

        case HAL_CMP_EDGE_IT_MODE_FALLING:
            LL_CMP_EnableIT(CMPx, LL_CMP_EDGE_IT_MODE_FALLING);
            break;

        case HAL_CMP_EDGE_IT_MODE_RISING_FALLING:
            LL_CMP_EnableIT(CMPx, LL_CMP_EDGE_IT_MODE_RISING | LL_CMP_EDGE_IT_MODE_FALLING);
            break;

        default:
            return HAL_ERROR;
    }

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  De-initialize the CMP peripheral and restore default configurations.
  * @note   This function disables the CMP module and calls HAL_CMP_MspDeInit()
  *         to release hardware resources (clock, NVIC).
  * @param  Handle CMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_DeInit(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    /* Disable the CMP module */
    LL_CMP_Disable(Handle->Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    HAL_CMP_MspDeInit(Handle);

    Handle->State = HAL_CMP_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the CMP MSP (MCU Specific Package) according to the
  *         application requirements.
  * @note   This is a weak function that can be overridden by the user. It is
  *         automatically called by HAL_CMP_Init() and should contain all
  *         hardware-level initialization (GPIO, clock, NVIC, etc.).
  * @param  Handle CMP handle
  * @retval None
  */
__WEAK void HAL_CMP_MspInit(HAL_CMP_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CMP_MspInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the CMP MSP according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. It is
  *         automatically called by HAL_CMP_DeInit() and should release hardware
  *         resources previously configured in HAL_CMP_MspInit().
  * @param  Handle CMP handle
  * @retval None
  */
__WEAK void HAL_CMP_MspDeInit(HAL_CMP_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CMP_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Initialize the CMP IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  CMPx Pointer to the base address of the CMP peripheral.
  * @retval None
  */
__WEAK void HAL_CMP_IoInit(CMP_TypeDef *CMPx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(CMPx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CMP_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the CMP IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  CMPx Pointer to the base address of the CMP peripheral.
  * @retval None
  */
__WEAK void HAL_CMP_IoDeInit(CMP_TypeDef *CMPx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(CMPx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CMP_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */ /* CMP_HAL_EF_Initialization */

/** @defgroup CMP_HAL_EF_Configuration CMP Configuration Functions
  * @brief    CMP Configuration Functions
  * @{
  */

/**
 * @brief CMP Blanking Config
 * @param CMPx Specifies CMP peripheral
 * @return HAL Status 
 */
HAL_StatusTypeDef HAL_CMP_BlankingConfig(HAL_CMP_HandleTypeDef *Handle, HAL_CMP_BlkEvtTypeDef BlankingSrce)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_CMP_SetOutputBlankingSource(Handle->Instance, (uint32_t)BlankingSrce);

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;
    
    return HAL_OK;
}

/**
  * @}
  */ /* CMP_HAL_EF_Configuration */

/** @defgroup CMP_HAL_EF_Operation CMP Operation Functions
  * @brief    CMP Operation Functions
  * @{
  */

/**
  * @brief  Enable the CMP peripheral and start the comparison operation.
  * @param  Handle CMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_Start(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Enable the CMP module */
    LL_CMP_Enable(Handle->Instance);

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Disable the CMP peripheral and stop the comparison operation.
  * @param  Handle CMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_Stop(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Disable the CMP module */
    LL_CMP_Disable(Handle->Instance);

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
 * @brief CMP Software Blanking Enable
 * @param CMPx Specifies CMP peripheral
 * @return HAL Status 
 */
HAL_StatusTypeDef HAL_CMP_EnableSwBlanking(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Verify blanking event is set correctly, then enable software blanking */
    if(LL_CMP_GetOutputBlankingSource(Handle->Instance) == LL_CMP_BLK_EVT_NONE) {
        /* Enable CMP software blanking */
        LL_CMP_EnableSwBlanking(Handle->Instance);
    } else {
        Handle->State = HAL_CMP_STATE_CONFIGURABLE;
        return HAL_FAILED;
    }

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;
    
    return HAL_OK;
}

/**
  * @brief  Disable software blanking for the CMP output.
  * @param  Handle CMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_DisableSwBlanking(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Disable CMP software blanking */
    LL_CMP_DisableSwBlanking(Handle->Instance);

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;
    
    return HAL_OK;
}

/**
  * @brief  Enable output synchronization for the CMP.
  * @note   Synchronization can filter out asynchronous events or align the
  *         output with a clock domain.
  * @param  Handle CMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_EnableOutputSync(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Enable output synchronization */
    LL_CMP_EnableOutputSync(Handle->Instance);

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;
    
    return HAL_OK;
}

/**
  * @brief  Disable output synchronization for the CMP.
  * @param  Handle CMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_DisableOutputSync(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Disable output synchronization */
    LL_CMP_DisableOutputSync(Handle->Instance);

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;
    
    return HAL_OK;
}

/**
  * @brief  Configure the output debounce time for the CMP.
  * @note   The debounce timer filters out transient pulses on the comparator output.
  *         The value specifies the number of clock cycles the output must remain
  *         stable before being taken into account.
  * @param  Handle CMP handle
  * @param  Debounce Specifies the debounce time in clock cycles.
  *                  This parameter is directly written to the hardware
  *                  debounce register.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CMP_OutputDebounce(HAL_CMP_HandleTypeDef *Handle, uint32_t Debounce)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    })

    ASSERT_FUNC_STATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE);

    HAL_CMP_PARAM_UPDATE(Handle->State, HAL_CMP_STATE_CONFIGURABLE, HAL_CMP_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Set the CMP output debounce timing */
    LL_CMP_SetOutputDebounce(Handle->Instance, Debounce);

    Handle->State = HAL_CMP_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @}
  */ /* CMP_HAL_EF_Operation */


/** @defgroup CMP_HAL_EF_Interrupt CMP Interrupt Handler and Callback
  * @brief    CMP Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  Handle CMP interrupt requests.
  * @note   This function checks pending rising and falling edge interrupts,
  *         clears the corresponding flags and invokes the callback functions
  *         HAL_CMP_RisingEdgeCallback() or HAL_CMP_FallingEdgeCallback().
  *         It should be called from the CMP interrupt handler.
  * @param  Handle CMP handle
  * @retval None
  */
void HAL_CMP_IRQHandler(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    HAL_CMP_PARAM_CHECK({
        if ((Handle == NULL) || !IS_CMP_ALL_INSTANCE(Handle->Instance)) {
            return ;
        }
    })

    CMP_TypeDef *p_instance;
    p_instance = Handle->Instance;

    /* Handle CMP rising edge interrupt: check if enabled and pending */
    if (LL_CMP_IsEnabledIT_RISIE(p_instance) && LL_CMP_IsActiveFlag_RIS(p_instance)) {
        /* Clear the rising edge interrupt pending flag */
        LL_CMP_ClearFlag_RIS(p_instance);

        /* Invoke the user callback for rising edge event */
        HAL_CMP_RisingEdgeCallback(Handle);
    }

    /* Handle CMP falling edge interrupt: check if enabled and pending */
    if (LL_CMP_IsEnabledIT_FALIE(p_instance) && LL_CMP_IsActiveFlag_FAL(p_instance)) {
        /* Clear the falling edge interrupt pending flag */
        LL_CMP_ClearFlag_FAL(p_instance);

        /* Invoke the user callback for falling edge event */
        HAL_CMP_FallingEdgeCallback(Handle);
    }
}

/**
  * @brief  Callback function called when a rising edge is detected on the CMP output.
  * @note   This is a weak function; the user can override it to implement custom
  *         rising-edge handling. It is invoked by HAL_CMP_IRQHandler().
  * @param  Handle CMP handle
  * @retval None
  */
__WEAK void HAL_CMP_RisingEdgeCallback(HAL_CMP_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CMP_RisingEdgeCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function called when a falling edge is detected on the CMP output.
  * @note   This is a weak function; the user can override it to implement custom
  *         falling-edge handling. It is invoked by HAL_CMP_IRQHandler().
  * @param  Handle CMP handle
  * @retval None
  */
__WEAK void HAL_CMP_FallingEdgeCallback(HAL_CMP_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_CMP_FallingEdgeCallback could be implemented in the user file
     */
}

/**
  * @}
  */ /* CMP_HAL_EF_Interrupt */

/**
  * @}
  */ /* CMP_HAL_Exported_Functions */


/* Private Functions ---------------------------------------------------------*/

/**
  * @}
  */ /* CMP_HAL */

#endif  /* HAL_CMP_MODULE_ENABLED */
#endif  /* HAL_MODULE_ENABLED */
#endif  /* CMP */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

