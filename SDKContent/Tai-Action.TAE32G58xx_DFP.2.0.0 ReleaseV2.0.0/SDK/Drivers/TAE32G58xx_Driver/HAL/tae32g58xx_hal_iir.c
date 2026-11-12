/**
  ******************************************************************************
  * @file    tae32g58xx_hal_iir.c
  * @author  Tai-Action SD Team
  * @brief   IIR HAL module driver
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

#if defined(IIR0) || defined(IIR1) || defined(IIR2) || defined(IIR3) || \
    defined(IIR4) || defined(IIR5) 
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_IIR_MODULE_ENABLED) && (HAL_IIR_MODULE_ENABLED == 1)

/** @defgroup IIR_HAL IIR HAL
  * @brief    IIR HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup IIR_HAL_Exported_Functions IIR HAL Exported Functions
  * @brief    IIR HAL Exported Functions
  * @{
  */

/** @defgroup IIR_HAL_EF_Initialization IIR Init and DeInit Functions
  * @brief    IIR Init and DeInit Functions
  * @{
  */

/**
  * @brief  Initialize the IIR peripheral and the associated HAL handle.
  * @param  Handle IIR handle
  * @param  IIRx   IIR peripheral base address.
  * @retval HAL_OK      - If the initialization is successful.
  * @retval HAL_INVALID - If a handle or instance parameter is invalid.
  */
HAL_StatusTypeDef HAL_IIR_Init(HAL_IIR_HandleTypeDef *Handle, IIR_TypeDef *IIRx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(IIRx));

    if ((Handle == NULL) || (!IS_IIR_ALL_INSTANCE(IIRx))) {
        return HAL_INVALID;
    }

    /* Bind the peripheral instance to the handle. */
    Handle->Instance = IIRx;

    /* Initialize the low level hardware, e.g. Clock, NVIC. */
    HAL_IIR_MspInit(Handle);

    Handle->State = HAL_IIR_STATE_INIT;

    return HAL_OK;
}

/**
  * @brief  De-initialize the IIR peripheral and the associated HAL handle.
  * @param  Handle IIR handle
  * @retval HAL_OK      - If the de-initialization is successful.
  * @retval HAL_INVALID - If a handle or instance parameter is invalid.
  */
HAL_StatusTypeDef HAL_IIR_DeInit(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    if ((Handle == NULL) || (!IS_IIR_ALL_INSTANCE(Handle->Instance))) {
        return HAL_INVALID;
    }

    /* De-initialize the low level hardware, e.g. Clock, NVIC. */
    HAL_IIR_MspDeInit(Handle);

    Handle->State = HAL_IIR_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the IIR MSP (MCU support package).
  * @param  Handle IIR handle
  * @retval None
  * @note   This function is declared as weak and can be overridden by the user.
  */
__WEAK void HAL_IIR_MspInit(HAL_IIR_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_IIR_MspInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the IIR MSP (MCU support package).
  * @param  Handle IIR handle
  * @retval None
  * @note   This function is declared as weak and can be overridden by the user.
  */
__WEAK void HAL_IIR_MspDeInit(HAL_IIR_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_IIR_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */ /* IIR_HAL_EF_Initialization */

/** @defgroup IIR_HAL_EF_Configuration IIR Configuration Functions
  * @brief    IIR Configuration Functions
  * @{
  */

/**
  * @brief  Configure the IIR filter parameters: order, scale factors and coefficients.
  * @param  Handle IIR handle
  * @param  pCfg   Pointer to an IIR parameter configuration structure.
  * @retval HAL_OK      - If the configuration is successful.
  * @retval HAL_INVALID - If the handle, configuration pointer or order is invalid.
  */
HAL_StatusTypeDef HAL_IIR_Config(HAL_IIR_HandleTypeDef *Handle, 
                                 const HAL_IIR_ParamCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_IIR_PARAM_CHECK({
        if ((Handle == NULL) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    IIR_TypeDef *p_instance = Handle->Instance;

    if (IS_IIRy_ALL_INSTANCE(Handle->Instance) && pCfg->Order > LL_IIR_ORDER_2) {
        return HAL_INVALID;
    }

    /* Configure the IIR filter order. */
    LL_IIR_SetOrder(p_instance, pCfg->Order);

    /* Configure scaling parameters. */
    LL_IIR_SetFeedbackScale(p_instance, pCfg->FeedbackScale);
    LL_IIR_SetOutputScale(p_instance, pCfg->OutputScale);

    /* Configure feed-forward coefficients B0-B5. */
    LL_IIR_SetCoefB0(p_instance, pCfg->Coefficient.Bx[0]);
    LL_IIR_SetCoefB1(p_instance, pCfg->Coefficient.Bx[1]);
    LL_IIR_SetCoefB2(p_instance, pCfg->Coefficient.Bx[2]);
    LL_IIR_SetCoefB3(p_instance, pCfg->Coefficient.Bx[3]);
    LL_IIR_SetCoefB4(p_instance, pCfg->Coefficient.Bx[4]);
    LL_IIR_SetCoefB5(p_instance, pCfg->Coefficient.Bx[5]);

    /* Configure feedback coefficients A1-A4. */
    LL_IIR_SetCoefA1(p_instance, pCfg->Coefficient.Ax[0]);
    LL_IIR_SetCoefA2(p_instance, pCfg->Coefficient.Ax[1]);
    LL_IIR_SetCoefA3(p_instance, pCfg->Coefficient.Ax[2]);
    LL_IIR_SetCoefA4(p_instance, pCfg->Coefficient.Ax[3]);

    /* Configure additional scaling for high-order filters. */
    if (pCfg->Order >= HAL_IIR_ORDER_3) {
        LL_IIR_SetHighOrderOutputScale(p_instance, pCfg->HighOutputScale);
        LL_IIR_SetHighOrderFeedbackScale(p_instance, pCfg->HighFeedbackScale);      
    }

    Handle->State = HAL_IIR_STATE_CONFIGURING;

    return HAL_OK;
}

/**
  * @brief  Reset the IIR peripheral to its default configuration.
  * @param  Handle IIR handle
  * @retval HAL_OK      - If the reset is successful.
  * @retval HAL_INVALID - If the handle or instance parameter is invalid.
  */
HAL_StatusTypeDef HAL_IIR_Reset(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    HAL_IIR_PARAM_CHECK({
        if (!IS_IIR_ALL_INSTANCE(Handle->Instance)) {
            return HAL_INVALID;
        }
    });

    IIR_TypeDef *p_instance = Handle->Instance;

    /* Perform a software reset and restore the default order. */
    LL_IIR_SoftReset(p_instance);
    LL_IIR_SetOrder(p_instance, LL_IIR_ORDER_2);

    /* Reset all scaling parameters. */
    LL_IIR_SetFeedbackScale(p_instance, LL_IIR_SCALE_2_POWER_0);
    LL_IIR_SetOutputScale(p_instance, LL_IIR_SCALE_2_POWER_0);
    LL_IIR_SetHighOrderOutputScale(p_instance, LL_IIR_SCALE_2_POWER_0);
    LL_IIR_SetHighOrderFeedbackScale(p_instance, LL_IIR_SCALE_2_POWER_0);

    /* Reset feed-forward coefficient B0-B5. */
    LL_IIR_SetCoefB0(p_instance, 0);
    LL_IIR_SetCoefB1(p_instance, 0);
    LL_IIR_SetCoefB2(p_instance, 0);
    LL_IIR_SetCoefB3(p_instance, 0);
    LL_IIR_SetCoefB4(p_instance, 0);
    LL_IIR_SetCoefB5(p_instance, 0);

    /* Reset feedback coefficient A1-A4. */
    LL_IIR_SetCoefA1(p_instance, 0);
    LL_IIR_SetCoefA2(p_instance, 0);
    LL_IIR_SetCoefA3(p_instance, 0);
    LL_IIR_SetCoefA4(p_instance, 0);

    return HAL_OK;
}

/**
  * @}
  */ /* IIR_HAL_EF_Configuration */

/** @defgroup IIR_HAL_EF_Operation IIR Operation Functions
  * @brief    IIR Operation Functions
  * @{
  */

/**
  * @brief  Enable the IIR peripheral.
  * @param  Handle IIR handle
  * @retval HAL_OK      - If the IIR is successfully enabled.
  */
HAL_StatusTypeDef HAL_IIR_Enable(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    LL_IIR_Enable(Handle->Instance);

    /* Update the HAL state if the IIR was initialized/configured. */
    if (Handle->State & (HAL_IIR_STATE_INIT | HAL_IIR_STATE_CONFIGURING)) {
        Handle->State = HAL_IIR_STATE_ACTIVE;
    }

    return HAL_OK;
}

/**
  * @brief  Disable the IIR peripheral.
  * @param  Handle IIR handle
  * @retval HAL_OK      - If the IIR is successfully disabled.
  */
HAL_StatusTypeDef HAL_IIR_Disable(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    LL_IIR_Disable(Handle->Instance);

    /* Move the state back to configuring after disabling. */
    if (Handle->State & (HAL_IIR_STATE_ACTIVE)) {
        Handle->State = HAL_IIR_STATE_CONFIGURING;
    }

    return HAL_OK;
}

/**
  * @brief  Perform one IIR filtering calculation without polling the BUSY flag.
  * @param  Handle  IIR handle
  * @param  DataIn  16-bit signed input data sample.
  * @param  DataOut Pointer to the 16-bit signed output data sample.
  * @retval HAL_OK      - If the calculation is successfully started and output read.
  * @retval HAL_INVALID - If a handle or output pointer parameter is invalid.
  * @note   This function writes the input sample and reads the output after a
  *         small fixed delay. It does not wait for the BUSY flag to be cleared.
  */
HAL_StatusTypeDef HAL_IIR_CalculatingNoWait(HAL_IIR_HandleTypeDef *Handle, 
                                      int16_t DataIn, 
                                      int16_t *DataOut)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(DataOut != NULL);

    HAL_IIR_PARAM_CHECK({
        if (!IS_IIR_ALL_INSTANCE(Handle->Instance) || DataOut == NULL) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_IIR_STATE_ACTIVE);

    /* Write the input data to the IIR peripheral. */
    LL_IIR_SetInputData(Handle->Instance, DataIn);
    __NOP();
    __NOP();
    __NOP();

    /* Read the output data from the IIR peripheral. */
    *DataOut = LL_IIR_GetOutputData(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Perform one IIR filtering calculation and wait for the BUSY flag.
  * @param  Handle  IIR handle
  * @param  DataIn  16-bit signed input data sample.
  * @param  DataOut Pointer to the 16-bit signed output data sample.
  * @param  Timeout Maximum waiting time in ticks.
  *                  Use HAL_WAIT_FOREVER to wait indefinitely.
  * @retval HAL_OK      - If the calculation is completed and the output is read.
  * @retval HAL_INVALID - If a handle or output pointer parameter is invalid.
  * @retval HAL_ERROR   - If an IIR error flag is set.
  * @retval HAL_TIMEOUT - If the BUSY flag is not cleared within the specified timeout.
  */
HAL_StatusTypeDef HAL_IIR_CalculatingPollingBusy(HAL_IIR_HandleTypeDef *Handle, 
                                           int16_t DataIn, 
                                           int16_t *DataOut, 
                                           uint32_t Timeout)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(DataOut != NULL);

    HAL_IIR_PARAM_CHECK({
        if (!IS_IIR_ALL_INSTANCE(Handle->Instance) || DataOut == NULL) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_IIR_STATE_ACTIVE);

    IIR_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart = HAL_GetTick();

    /* Write the input data to the IIR peripheral. */
    LL_IIR_SetInputData(p_instance, DataIn);

    /* Wait for the BUSY flag to be cleared, and check for errors first because
       the calculation may not have started if an error occurred. */
    do {
        /* Check whether an error has occurred. */
        if (LL_IIR_IsActiveFlag_ERR(p_instance)) {
            LL_IIR_ClearFlag_ERR(p_instance);
            return HAL_ERROR;
        }

        if (Timeout != HAL_WAIT_FOREVER && (HAL_GetTick() - tickstart) > Timeout) {
            return HAL_TIMEOUT;
        }
    } while (LL_IIR_IsBusy(p_instance));

    /* Read the output data from the IIR peripheral. */
    *DataOut = LL_IIR_GetOutputData(p_instance);

    return HAL_OK;
}

/**
  * @}
  */ /* IIR_HAL_EF_Operation */

/** @defgroup IIR_HAL_EF_Interrupt IIR Interrupt Handler and Callbacks
  * @brief    IIR Interrupt Handler and Callbacks
  * @{
  */

/**
  * @brief  Enable the IIR error interrupt.
  * @param  Handle IIR handle
  * @retval HAL_OK      - If the error interrupt is successfully enabled.
  */
HAL_StatusTypeDef HAL_IIR_ErrorInterruptEnable(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    LL_IIR_EnableIT_IEE(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Disable the IIR error interrupt.
  * @param  Handle IIR handle
  * @retval HAL_OK      - If the error interrupt is successfully disabled.
  */
HAL_StatusTypeDef HAL_IIR_ErrorInterruptDisable(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    LL_IIR_DisableIT_IEE(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Handle the IIR interrupt request.
  * @param  Handle IIR handle
  * @retval None
  */
void HAL_IIR_IRQHandler(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    HAL_IIR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_IIR_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    IIR_TypeDef *p_instance = Handle->Instance;

    /* Error interrupt handling. */
    if (LL_IIR_IsEnabledIT_IEE(p_instance) && LL_IIR_IsActiveFlag_ERR(p_instance)) {
        /* Clear the pending error interrupt flag. */
        LL_IIR_ClearFlag_ERR(p_instance);

        /* Invoke the error callback. */
        HAL_IIR_ErrorCallback(Handle);
    }
}

/**
  * @brief  IIR error interrupt callback.
  * @param  Handle IIR handle
  * @retval None
  * @note   This function is declared as weak and can be overridden by the user.
  */
__WEAK void HAL_IIR_ErrorCallback(HAL_IIR_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_IIR_ErrorCallback could be implemented in the user file
     */
}

/**
  * @}
  */ /* IIR_HAL_EF_Interrupt */

/**
  * @}
  */ /* IIR_HAL_Exported_Functions */


/* Private Functions ---------------------------------------------------------*/

/**
  * @}
  */ /* IIR_HAL */

#endif  /* HAL_IIR_MODULE_ENABLED */
#endif  /* HAL_MODULE_ENABLED */
#endif  /* IIR */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

