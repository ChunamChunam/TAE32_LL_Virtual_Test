/**
  ******************************************************************************
  * @file    tae32g58xx_hal_qei.c
  * @author  Tai-Action SD Team
  * @brief   QEI HAL module driver
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

#if defined(QEI0) || defined(QEI1) || defined(QEI2)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_QEI_MODULE_ENABLED) && (HAL_QEI_MODULE_ENABLED == 1)

/** @defgroup QEI_HAL QEI HAL
  * @brief    QEI HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup QEI_HAL_Private_Functions QEI HAL Private Functions
  * @brief    QEI HAL Private Functions
  * @{
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_TmrCntCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                     const HAL_QEI_TmrCntCfgTypeDef *pCfg);
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_PosCntCmpCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                        const HAL_QEI_PosCntCmpCfgTypeDef *pCfg);
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_CapCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                  const HAL_QEI_CapCfgTypeDef *pCfg);
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_PosCntCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                     const HAL_QEI_PosCntCfgTypeDef *pCfg);
/**
  * @}
  */

/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup QEI_HAL_Exported_Functions QEI HAL Exported Functions
  * @brief    QEI HAL Exported Functions
  * @{
  */

/** @defgroup QEI_HAL_EF_Initialization QEI Init and DeInit Functions
  * @brief    QEI Init and DeInit Functions
  * @{
  */

/**
  * @brief  QEI HAL Init
  * @param  Handle QEI handle
  * @param  QEIx Specifies QEI peripheral
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_QEI_Init(HAL_QEI_HandleTypeDef *Handle, QEI_TypeDef *QEIx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(QEIx))) {
        return HAL_INVALID;
    }

    /* User data, do nothing. */
    (void)Handle->pUserData;

    /* Bind the peripheral instance to the handle. */
    Handle->Instance = QEIx;

    /* Init the low level hardware eg. Clock, NVIC */
    HAL_QEI_MspInit(Handle);

    Handle->State = HAL_QEI_STATE_INIT;

    return HAL_OK;
}

/**
  * @brief  QEI HAL DeInit
  * @param  Handle QEI handle
  * @return Status of the DeInitialization
  */
HAL_StatusTypeDef HAL_QEI_DeInit(HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance))) {
        return HAL_INVALID;
    }

    /* DeInit the low level hardware eg. Clock, NVIC */
    HAL_QEI_MspDeInit(Handle);

    Handle->State = HAL_QEI_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initializes the QEI MSP
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_MspInit(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the QEI MSP
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_MspDeInit(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Initialize the QEI IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  QEIx Specifies QEI peripheral
  * @retval None
  */
__WEAK void HAL_QEI_IoInit(QEI_TypeDef *QEIx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(QEIx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the QEI IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  QEIx Specifies QEI peripheral
  * @retval None
  */
__WEAK void HAL_QEI_IoDeInit(QEI_TypeDef *QEIx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(QEIx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_IoDeInit could be implemented in the user file
     */
}


/**
  * @}
  */ /* QEI_HAL_EF_Initialization */

/** @defgroup QEI_HAL_EF_Configuration QEI Configuration Functions
  * @brief    QEI Configuration Functions
  * @{
  */

/**
  * @brief  QEI Position Counter Init
  * @param  Handle QEI handle
  * @param  pCfg  QEI Position Counter Init Pointer
  * @return Status of the Initialization
  */
HAL_StatusTypeDef HAL_QEI_PositionCounterConfig(HAL_QEI_HandleTypeDef *Handle, 
                                                const HAL_QEI_PosCntCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_QEI_STATE_INIT | HAL_QEI_STATE_IDLE);

    return QEI_PosCntCfg(Handle, pCfg);

  }

/**
  * @brief  QEI Timer Counter Config
  * @param  Handle QEI handle
  * @param  pCfg  QEI Timer Counter Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_QEI_TimerCounterConfig(HAL_QEI_HandleTypeDef *Handle, 
                                             const HAL_QEI_TmrCntCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_QEI_STATE_INIT | HAL_QEI_STATE_IDLE);

    return QEI_TmrCntCfg(Handle, pCfg);
}

/**
  * @brief  QEI Position Counter Compare Config
  * @param  Handle QEI handle
  * @param  pCfg  QEI Position Counter Compare Config Pointer
  * @return HAL Status 
  */
HAL_StatusTypeDef HAL_QEI_PositionCounterCompareConfig(HAL_QEI_HandleTypeDef *Handle, 
                                                       const HAL_QEI_PosCntCmpCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_QEI_STATE_INIT | HAL_QEI_STATE_IDLE);

    return QEI_PosCntCmpCfg(Handle, pCfg);

}

/**
  * @brief  QEI Capture Config
  * @param  Handle QEI handle
  * @param  pCfg  QEI Capture Config Pointer
  * @return Status of the Initialization
  */
HAL_StatusTypeDef HAL_QEI_CaptureConfig(HAL_QEI_HandleTypeDef *Handle, 
                                        const HAL_QEI_CapCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_QEI_STATE_INIT | HAL_QEI_STATE_IDLE);

    return QEI_CapCfg(Handle, pCfg);
}

/**
  * @}
  */ /* QEI_HAL_EF_Configuration */

/** @defgroup QEI_HAL_EF_Operation QEI Operation Functions
  * @brief    QEI Operation Functions
  * @{
  */

/**
  * @brief  QEI Enable
  * @param  Handle QEI handle
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_QEI_Enable(HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_QEI_STATE_INIT | HAL_QEI_STATE_IDLE | HAL_QEI_STATE_ACTIVE);

    //QEI Enable
    LL_QEI_Enable(Handle->Instance);

    Handle->State = HAL_QEI_STATE_ACTIVE;

    return HAL_OK;
}

/**
  * @brief  QEI Disable
  * @param  Handle QEI handle
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_QEI_Disable(HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_QEI_STATE_INIT | HAL_QEI_STATE_IDLE | HAL_QEI_STATE_ACTIVE);

    //QEI Enable
    LL_QEI_Disable(Handle->Instance);

    Handle->State = HAL_QEI_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  Get Index Event Position
  * @param  Handle QEI handle
  * @return Index Event Position
  */
uint32_t HAL_QEI_GetIndexEventPosition(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return LL_QEI_GetIndexPositionLatch(Handle->Instance);
}

/**
  * @brief  Get Index Event Diretion
  * @param  Handle QEI handle
  * @return Index Event Diretion
  */
uint32_t HAL_QEI_GetIndexEventDiretion(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return LL_QEI_GetDirection(Handle->Instance);
}

/**
  * @brief  Get Timer Event Position
  * @param  Handle QEI handle
  * @return Timer Event Position
  */
uint32_t HAL_QEI_GetTimerEventPosition(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return LL_QEI_GetPositionLatch(Handle->Instance);
}

/**
  * @brief  Get Capture Counter
  * @param  Handle QEI handle
  * @return Capture Counter
  */
uint32_t HAL_QEI_GetCaptureEventCounter(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return LL_QEI_GetCaptureTimerLatch(Handle->Instance);
}

/**
  * @brief  Get Capture Period
  * @param  Handle QEI handle
  * @return Capture Period
  */
uint32_t HAL_QEI_GetCaptureEventPeriod(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return LL_QEI_GetCapturePeriodLatch(Handle->Instance);
}

/**
  * @brief  Get Direction First Index Status
  * @param  Handle QEI handle
  * @return Direction First Index Status
  */
HAL_QEI_DirFstIdxStaTypeDef HAL_QEI_GetDirectionFirstIndexStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return (HAL_QEI_DirFstIdxStaTypeDef)LL_QEI_GetFirstIndexDirectionStatus(Handle->Instance);
}

/**
  * @brief  Get Direction Index Status
  * @param  Handle QEI handle
  * @return Direction Index Status
  */
HAL_QEI_DirIdxLchStaTypeDef HAL_QEI_GetDirectionIndexStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return (HAL_QEI_DirIdxLchStaTypeDef)LL_QEI_GetIndexDirectionStatus(Handle->Instance);
}

/**
  * @brief  Get Direction Status
  * @param  Handle QEI handle
  * @return Direction Status
  */
HAL_QEI_DirStaTypeDef HAL_QEI_GetDirectionStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return LL_QEI_GetDirection(Handle->Instance);
}

/**
  * @brief  Get Capture Overflow Error Status
  * @param  Handle QEI handle
  * @return Capture Overflow Error Status
  */
HAL_QEI_CapOvfErrStaTypeDef HAL_QEI_GetCaptureOverflowErrorStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return (LL_QEI_IsCaptureOverflowErrorActived(Handle->Instance)) ? HAL_QEI_CAP_OVF_ERR_STS_ERR : HAL_QEI_CAP_OVF_ERR_STS_NO_ERR;
}

/**
  * @brief  Clear Capture Overflow Error Status
  * @param  Handle QEI handle
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_QEI_ClearCaptureOverflowErrorStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_QEI_ClearCaptureOverflowErrorFlag(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Get Capture Direction Error Status
  * @param  Handle QEI handle
  * @return Capture Direction Error Status
  */
HAL_QEI_CapDirErrStaTypeDef HAL_QEI_GetCaptureDirectionErrorStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return ((LL_QEI_IsCaptureDirectionErrorActived(Handle->Instance)) ? HAL_QEI_CAP_DIR_ERR_STS_ERR : HAL_QEI_CAP_DIR_ERR_STS_NO_ERR);
}

/**
  * @brief  Clear Capture Direction ErrorStatus
  * @param  Handle QEI handle
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_QEI_ClearCaptureDirectionErrorStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    HAL_QEI_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_QEI_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_QEI_ClearCaptureDirectionErrorFlag(Handle->Instance);

    return HAL_OK;
}

/**
  * @brief  Get First Index Status
  * @param  Handle QEI handle
  * @return First Index Status
  */
HAL_QEI_FstIdxStaTypeDef HAL_QEI_GetFirstIndexStatus(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return ((LL_QEI_IsFirstIndexActived(Handle->Instance)) ? HAL_QEI_FIRST_IDX_STS_DET : HAL_QEI_FIRST_IDX_STS_NOT_DET);
}

/**
  * @brief  Get Current Position Counter
  * @param  Handle QEI handle
  * @return Current Position
  */
uint32_t HAL_QEI_GetCurrentPositionCounter(const HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    return (LL_QEI_GetPosition(Handle->Instance));
}

/**
  * @}
  */ /* QEI_HAL_EF_Operation */


/** @defgroup QEI_HAL_EF_Interrupt QEI Interrupt Handler and Callback
  * @brief    QEI Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  Enable one or more QEI interrupt sources.
  * @param  Handle QEI handle
  * @param  InterruptRequests Bitmask of the interrupt sources to enable. This
  *         parameter can be any combination of @ref HAL_QEI_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully enabled.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_QEI_InterruptRequestEnable(HAL_QEI_HandleTypeDef *Handle,
                                                 HAL_QEI_ITEnMskTypeDef InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    LL_QEI_EnableIT(Handle->Instance, InterruptRequests);

    return HAL_OK;
}

/**
  * @brief  Disable one or more QEI interrupt sources.
  * @param  Handle QEI handle
  * @param  InterruptRequests Bitmask of the interrupt sources to disable. This
  *         parameter can be any combination of @ref HAL_QEI_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully disabled.
  * @retval HAL_INVALID - A parameter is invalid.
  */
HAL_StatusTypeDef HAL_QEI_InterruptRequestDisable(HAL_QEI_HandleTypeDef *Handle,
                                                  HAL_QEI_ITEnMskTypeDef InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    LL_QEI_DisableIT(Handle->Instance, InterruptRequests);

    return HAL_OK;
}


/**
  * @brief  QEI IRQ Handler
  * @param  Handle QEI handle
  * @return None
  */
void HAL_QEI_IRQHandler(HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    HAL_QEI_PARAM_CHECK({
        if (!IS_QEI_ALL_INSTANCE(Handle->Instance)) {
            return;
        }      
    });

    QEI_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_QEI_GetInterruptEnableStatus(p_instance);
    const uint32_t int_pending = LL_QEI_GetInterruptStatus(p_instance);

    /* Build a mask of flags that are both pending and enabled in the
       corresponding interrupt-enable registers */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_QEI_STSR_IT_FLAG_MSK; 


    //Capture Done Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_CDS)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_CDS(p_instance);

        //Callback
        HAL_QEI_CaptureDoneCallback(Handle);
    }

    //Positon Counter Reset Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_PRS)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_PRS(p_instance);

        //Callback
        HAL_QEI_PosCntResetCallback(Handle);
    }

    //Positon Counter Initial Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_PIS)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_PIS(p_instance);

        //Callback
        HAL_QEI_PosCntInitialCallback(Handle);
    }

    //Timer Overflow Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_UTO)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_UTO(p_instance);

        //Callback
        HAL_QEI_TimerOverflowCallback(Handle);
    }

    //Positon Counter Latch Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_IEL)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_IEL(p_instance);

        //Callback
        HAL_QEI_PosCntLatchCallback(Handle);
    }

    //Positon Counter Compare Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_PCM)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_PCM(p_instance);

        //Callback
        HAL_QEI_PosCntCompareCallback(Handle);
    }

    //Positon Counter Overflow Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_PCO)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_PCO(p_instance);

        //Callback
        HAL_QEI_PosCntOverflowCallback(Handle);
    }

    //Positon Counter Underflow Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_PCU)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_PCU(p_instance);

        //Callback
        HAL_QEI_PosCntUnderflowCallback(Handle);
    }

    //Direction Change Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_QDC)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_QDC(p_instance);

        //Callback
        HAL_QEI_DirectionChangeCallback(Handle);
    }

    //Phase Error Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_PHE)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_PHE(p_instance);

        //Callback
        HAL_QEI_PhaseErrorCallback(Handle);
    }

    //Position Counter Interrupt Handler
    if ((flag_status_masked & LL_QEI_STSR_PCE)) {
        //Interrupt Pending Clear
        LL_QEI_ClearFlag_PCE(p_instance);

        //Callback
        HAL_QEI_PosCntErrorCallback(Handle);
    }
}


/**
  * @brief  Capture Done Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_CaptureDoneCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_CaptureDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Reset Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PosCntResetCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PosCntResetCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Initial Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PosCntInitialCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PosCntInitialCallback could be implemented in the user file
     */
}

/**
  * @brief  Timer Overflow Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_TimerOverflowCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_TimerOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Latch Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PosCntLatchCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PosCntLatchCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Compare Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PosCntCompareCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PosCntCompareCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Overflow Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PosCntOverflowCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PosCntOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Underflow Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PosCntUnderflowCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PosCntUnderflowCallback could be implemented in the user file
     */
}

/**
  * @brief  Direction Change Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_DirectionChangeCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_DirectionChangeCallback could be implemented in the user file
     */
}

/**
  * @brief  Phase Error Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PhaseErrorCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PhaseErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Error Interrupt Callback Function
  * @param  Handle QEI handle
  * @return None
  */
__WEAK void HAL_QEI_PosCntErrorCallback(HAL_QEI_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_QEI_PosCntErrorCallback could be implemented in the user file
     */
}

/**
  * @}
  */ /* QEI_HAL_EF_Interrupt */

/**
  * @}
  */ /* QEI_HAL_Exported_Functions */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup QEI_HAL_Private_Functions
  * @{
  */

/**
  * @brief  QEI Position Counter Init
  * @param  Handle QEI handle
  * @param  pCfg  QEI Position Counter Init Pointer
  * @return Status of the Initialization
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_PosCntCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                     const HAL_QEI_PosCntCfgTypeDef *pCfg)
{
    QEI_TypeDef *p_instance = Handle->Instance;

    //Init/Max Value Init
    LL_QEI_SetInitialPosition(p_instance, pCfg->InitialValue);
    LL_QEI_SetPositionMax(p_instance, pCfg->MaxValue);

    //Debounce Value
    LL_QEI_SetDebounceValue(p_instance, pCfg->DebounceWindow);

    //Input Signal Config
    LL_QEI_SetIndexInputPolarity(p_instance, pCfg->IndexPolarity);
    LL_QEI_SetQEAInputPolarity(p_instance, pCfg->QEAPolarity);
    LL_QEI_SetQEBInputPolarity(p_instance, pCfg->QEBPolarity);
    HAL_FUNC_ALTER(pCfg->InputSwap, LL_QEI_EnableSwapQEA_B(p_instance), LL_QEI_DisableSwapQEA_B(p_instance));

    //Work Mode Config
    LL_QEI_SetPositionCounterWorkMode(p_instance, pCfg->WorkMode);
    LL_QEI_SetDirectionCounterMode(p_instance, pCfg->DirectionCounterMode);
    LL_QEI_SetClockRateMode(p_instance, pCfg->ClockRateMode);
    LL_QEI_SetPositionResetMode(p_instance, pCfg->ResetMode);

    //Index Control Config
    LL_QEI_SetPositionInitMode(p_instance, pCfg->IndexInitEdge);
    LL_QEI_SetLatchMode(p_instance, pCfg->IndexLatchEdge);
    HAL_FUNC_ALTER(pCfg->IndexResetMode, LL_QEI_EnableIndexResetPosition(p_instance), LL_QEI_DisableIndexResetPosition(p_instance));

    return HAL_OK;
}

/**
  * @brief  QEI Timer Counter Config
  * @param  Handle QEI handle
  * @param  pCfg  QEI Timer Counter Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_TmrCntCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                     const HAL_QEI_TmrCntCfgTypeDef *pCfg)
{
     QEI_TypeDef *p_instance = Handle->Instance;

    if (!pCfg->TimerEnable) {
        LL_QEI_DisableUnitTimer(p_instance);
        return HAL_OK;
    }

    //Timer Start/Period Value Config
    LL_QEI_SetUnitTimerValue(p_instance, pCfg->StartValue);
    LL_QEI_LoadUnitTimer(p_instance, pCfg->Period);

    //Timer Enable
    LL_QEI_EnableUnitTimer(p_instance);

    return HAL_OK;
}

/**
  * @brief  QEI Position Counter Compare Config
  * @param  Handle QEI handle
  * @param  pCfg  QEI Position Counter Compare Config Pointer
  * @return HAL Status 
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_PosCntCmpCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                        const HAL_QEI_PosCntCmpCfgTypeDef *pCfg)
{
    QEI_TypeDef *p_instance = Handle->Instance;

    if (!pCfg->CompareEnable) {
        LL_QEI_DisableCompare(p_instance);
        return HAL_OK;
    }

    //Compare Config
    LL_QEI_SetCompareValue(p_instance, pCfg->CompareValue);
    HAL_FUNC_ALTER(pCfg->ShadowEnable, LL_QEI_EnableCompareShadow(p_instance), LL_QEI_DisableCompareShadow(p_instance));

    //Compare Enable
    LL_QEI_EnableCompare(p_instance);

    return HAL_OK;
}

/**
  * @brief  QEI Capture Config
  * @param  Handle QEI handle
  * @param  pCfg  QEI Capture Config Pointer
  * @return Status of the Initialization
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef QEI_CapCfg(HAL_QEI_HandleTypeDef *Handle, 
                                                  const HAL_QEI_CapCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    if (!IS_QEI_ALL_INSTANCE(Handle->Instance) || pCfg == NULL) {
        return HAL_INVALID;
    }

    QEI_TypeDef *p_instance = Handle->Instance;

    if (!pCfg->CaptureEnable) {
        LL_QEI_DisableCapture(p_instance);
        return HAL_OK;
    }

    //Capture Config
    LL_QEI_SetCaptureEventPrescale(p_instance, pCfg->EventDivision);
    LL_QEI_SetCaptureTimerClockPrescale(p_instance, pCfg->TimerClockDivision);
    LL_QEI_SetCaptureLatchMode(p_instance, pCfg->LatchMode);

    //Capture Enable
    LL_QEI_EnableCapture(p_instance);

    return HAL_OK;
}

/**
  * @}
  */ /* QEI_HAL_Private_Functions */



/**
  * @}
  */ /* QEI_HAL */

#endif  /* HAL_QEI_MODULE_ENABLED */
#endif  /* HAL_MODULE_ENABLED */
#endif  /* QEI */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

