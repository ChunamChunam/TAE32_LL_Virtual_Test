/**
  ******************************************************************************
  * @file    tae32f561x_hal_bstmr.c
  * @author  Tai-Action SD Team
  * @brief   BSTMR HAL module driver (basic timer).
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
#include "tae32f561x_hal.h"


/** @addtogroup TAE32F561x_HAL_Driver
  * @{
  */

/** @defgroup BSTMR_HAL BSTMR HAL
  * @brief    BSTMR HAL module driver.
  * @{
  */

#if defined(TMR7) || defined(TMR8)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_BSTMR_MODULE_ENABLED) && (HAL_BSTMR_MODULE_ENABLED == 1)

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup BSTMR_HAL_Private_Macros BSTMR HAL Private Macros
  * @brief    BSTMR HAL Private Macros
  * @{
  */

/** @defgroup BSTMR_HAL_PM_Discriminant BSTMR HAL Discriminant
  * @brief    BSTMR HAL Discriminant
  * @{
  */

#define IS_BSTMR_ENABLE(__VAL__)                      (((__VAL__) == HAL_BSTMR_FUNC_DISABLE) || \
                                                       ((__VAL__) == HAL_BSTMR_FUNC_ENABLE))

#define IS_BSTMR_WORK_MODE(__VAL__)                   (((__VAL__) == HAL_BSTMR_WORK_MODE_CONTINUE) || \
                                                       ((__VAL__) == HAL_BSTMR_WORK_MODE_SINGLE))

#define IS_BSTMR_UPDATE_EVT_SRC(__VAL__)              (((__VAL__) == HAL_BSTMR_UPDATE_EVT_SRC_OV_UG) || \
                                                       ((__VAL__) == HAL_BSTMR_UPDATE_EVT_SRC_OV))

#define IS_BSTMR_MST_MODE(__VAL__)                    (((__VAL__) == HAL_BSTMR_MST_MODE_RESET)  || \
                                                       ((__VAL__) == HAL_BSTMR_MST_MODE_ENABLE) || \
                                                       ((__VAL__) == HAL_BSTMR_MST_MODE_UPDATE))


#define IS_BSTMR_EVENTSOURCE(__VAL__)                 (((__VAL__) == HAL_BSTMR_EVENTSOURCE_UPDATE))

/**
  * @}
  */ /* BSTMR_HAL_PM_Discriminant */


/**
  * @}
  */ /* BSTMR_HAL_EF_Configuration */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup BSTMR_HAL_Private_Functions BSTMR HAL Private Functions
  * @{
  */
static HAL_StatusTypeDef BSTMR_BaseCfg(HAL_BSTMR_HandleTypeDef *Handle, 
                                       const HAL_BSTMR_BaseInitTypeDef *pCfg);

static HAL_StatusTypeDef BSTMR_MstCfg(HAL_BSTMR_HandleTypeDef *Handle, 
                                      const HAL_BSTMR_MstInitTypeDef *pCfg);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup BSTMR_HAL_Exported_Functions BSTMR HAL Exported Functions
  * @{
  */

/** @defgroup BSTMR_HAL_EF_Initialization BSTMR HAL Initialization
  * @{
  */

/**
  * @brief  Initialize the BSTMR peripheral according to the specified parameters
  *         and create the associated handle.
  * @param  Handle BSTMR handle.
  * @param  BSTMRx BSTMR instance
  * @param  pInit  pointer to a HAL_BSTMR_BaseInitTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_Base_Init(HAL_BSTMR_HandleTypeDef *Handle, 
                                      BSTMR_TypeDef *BSTMRx,
                                      const HAL_BSTMR_BaseInitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(BSTMRx));
    ASSERT_FUNC_PARAM(pInit != NULL);

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(BSTMRx)) || (pInit == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_PARAM(IS_BSTMR_WORK_MODE(pInit->WorkMode));
    ASSERT_FUNC_PARAM(IS_BSTMR_UPDATE_EVT_SRC(pInit->UpdateSource));

    Handle->State = HAL_BSTMR_STATE_RESET;

    /* Bind the instance passed by the caller */
    Handle->Instance = BSTMRx;

    /* Init the low level hardware: CLOCK, NVIC */
    HAL_BSTMR_Base_MspInit(Handle);

    /* Configure the time base */
    (void) BSTMR_BaseCfg(Handle, pInit);

    Handle->LastErrorCodes = HAL_BSTMR_ERROR_NONE;
    Handle->State          = HAL_BSTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  De-initialize the BSTMR peripheral.
  * @param  Handle BSTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_Base_DeInit(HAL_BSTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    BSTMR_TypeDef *p_instance = Handle->Instance;

    Handle->State = HAL_BSTMR_STATE_BUSY;

    /* Stop the counter and its interrupts */
    LL_BSTMR_DisableCounter(p_instance);

    /* Disable all capture/compare channels */
    LL_BSTMR_DisableIT(p_instance, LL_BSTMR_IER_IT_EN_MSK);

    /* De-init the low level hardware: GPIO, CLOCK, NVIC */
    HAL_BSTMR_Base_MspDeInit(Handle);

    Handle->LastErrorCodes = HAL_BSTMR_ERROR_NONE;
    Handle->State          = HAL_BSTMR_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the BSTMR MSP.
  * @note   This function should not be modified. When the application needs its
  *         own implementation, it may override this weak function in the user file.
  * @param  Handle BSTMR handle.
  * @return None
  */
__WEAK void HAL_BSTMR_Base_MspInit(HAL_BSTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  De-initialize the BSTMR MSP.
  * @param  Handle BSTMR handle.
  * @return None
  */
__WEAK void HAL_BSTMR_Base_MspDeInit(HAL_BSTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @}
  */

/** @defgroup BSTMR_HAL_EF_Configuration BSTMR HAL Configuration
  * @{
  */

/**
  * @brief  Configure the BSTMR Master mode
  * @param  Handle BSTMR handle.
  * @param  pCfg pointer to the master configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_InitMaster(HAL_BSTMR_HandleTypeDef *Handle,
                                       const HAL_BSTMR_MstInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_MST_MODE(pCfg->MasterMode));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE);

    HAL_BSTMR_PARAM_UPDATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE, HAL_BSTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = BSTMR_MstCfg(Handle, pCfg);

    Handle->State = HAL_BSTMR_STATE_CONFIGURABLE;

    return ret;
}


/**
  * @}
  */

/** @defgroup BSTMR_HAL_EF_IO_Operation BSTMR HAL IO Operation
  * @{
  */
/**
  * @brief  Start the BSTMR time base (polling mode).
  * @param  Handle BSTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_Base_Start(HAL_BSTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE);

    HAL_BSTMR_PARAM_UPDATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE, HAL_BSTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_BSTMR_EnableCounter(Handle->Instance);

    Handle->State = HAL_BSTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Stop the BSTMR time base (polling mode).
  * @param  Handle BSTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_Base_Stop(HAL_BSTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE);

    HAL_BSTMR_PARAM_UPDATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE, HAL_BSTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_BSTMR_DisableCounter(Handle->Instance);

    Handle->State = HAL_BSTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the BSTMR time base in interrupt mode.
  * @param  Handle BSTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_Base_Start_IT(HAL_BSTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE);

    HAL_BSTMR_PARAM_UPDATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE, HAL_BSTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_BSTMR_EnableIT_UPDATE(Handle->Instance);
    LL_BSTMR_EnableCounter(Handle->Instance);

    Handle->State = HAL_BSTMR_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the BSTMR time base in interrupt mode.
  * @param  Handle BSTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_Base_Stop_IT(HAL_BSTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE);

    HAL_BSTMR_PARAM_UPDATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE, HAL_BSTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_BSTMR_DisableIT_UPDATE(Handle->Instance);
    LL_BSTMR_DisableCounter(Handle->Instance);

    Handle->State = HAL_BSTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}


/**
  * @brief  Enable the module level interrupts selected by ITMask.
  * @param  Handle BSTMR handle.
  * @param  ITMask interrupts to enable, value of @ref HAL_BSTMR_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_InterruptRequestEnable(HAL_BSTMR_HandleTypeDef *Handle, 
                                                   HAL_BSTMR_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_BSTMR_EnableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Disable the module level interrupts selected by ITMask.
  * @param  Handle BSTMR handle.
  * @param  ITMask interrupts to disable, value of @ref HAL_BSTMR_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_InterruptRequestDisable(HAL_BSTMR_HandleTypeDef *Handle, 
                                                    HAL_BSTMR_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_BSTMR_DisableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Generate a software event of the BSTMR.
  * @param  Handle BSTMR handle.
  * @param  EventSource event to generate
  * @return HAL status
  */
HAL_StatusTypeDef HAL_BSTMR_GenerateEvent(HAL_BSTMR_HandleTypeDef *Handle, HAL_BSTMR_EvtSrcTypeDef EventSource)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_BSTMR_EVENTSOURCE(EventSource));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance)) || (!IS_BSTMR_EVENTSOURCE(EventSource))) {
            return HAL_INVALID;
        }
    });

    volatile HAL_StatusTypeDef ret = HAL_OK;
    BSTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE);

    HAL_BSTMR_PARAM_UPDATE(Handle->State, HAL_BSTMR_STATE_CONFIGURABLE, HAL_BSTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (EventSource) {
        case HAL_BSTMR_EVENTSOURCE_UPDATE:
            LL_BSTMR_GenerateEvent_UPDATE(p_instance);
            break;

        default:
            ret = HAL_INVALID;
            break;
    }

    Handle->State = HAL_BSTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Read the counter value at runtime.
  * @param  Handle BSTMR handle.
  * @retval the timer counter register.
  */
uint16_t HAL_BSTMR_ReadCounter(const HAL_BSTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    return (uint16_t)(LL_BSTMR_GetCounter(Handle->Instance));
}


/**
  * @}
  */

/** @defgroup BSTMR_HAL_EF_IRQ_Handler BSTMR HAL IRQ Handler and Callbacks
  * @{
  */

/**
  * @brief  Handle the BSTMR interrupt request.
  * @param  Handle BSTMR handle.
  * @return None
  */
void HAL_BSTMR_IRQHandler(HAL_BSTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_BSTMR_ALL_INSTANCE(Handle->Instance));

    HAL_BSTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_BSTMR_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    BSTMR_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_BSTMR_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_BSTMR_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers OVIF/UIF bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_BSTMR_SR_UPD_IT_FLAG_MSK; 

    /* Update interrupt */
    if ((flag_status_masked & LL_BSTMR_SR_UIF)) {
        LL_BSTMR_ClearFlag_UPDATE(p_instance);

        HAL_BSTMR_PeriodElapsedCallback(Handle);
    }

    /* Overflow interrupt */
    if ((flag_status_masked & LL_BSTMR_SR_OVIF)) {
        LL_BSTMR_ClearFlag_OVR(p_instance);

        HAL_BSTMR_OverflowCallback(Handle);
    }
}

/**
  * @brief  BSTMR update (reload) callback.
  * @param  Handle BSTMR handle.
  * @return None
  */
__WEAK void HAL_BSTMR_PeriodElapsedCallback(HAL_BSTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  BSTMR overflow callback.
  * @param  Handle BSTMR handle.
  * @return None
  */
__WEAK void HAL_BSTMR_OverflowCallback(HAL_BSTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/
/** @defgroup BSTMR_HAL_Private_Functions BSTMR HAL Private Functions
  * @{
  */

/**
  * @brief  Configure the BSTMR time base from the init structure.
  * @param  Handle BSTMR handle.
  * @param  pCfg pointer to a HAL_BSTMR_BaseInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef BSTMR_BaseCfg(HAL_BSTMR_HandleTypeDef *Handle, 
                                       const HAL_BSTMR_BaseInitTypeDef *pCfg)
{
    BSTMR_TypeDef *p_instance = Handle->Instance;

    /* Time base: counter value, period and prescaler (all 16-bit) */
    LL_BSTMR_SetCounter(p_instance, 0UL);
    LL_BSTMR_SetAutoReload(p_instance, pCfg->Period);
    LL_BSTMR_SetPrescaler(p_instance, pCfg->Prescaler);

    /* Work mode */
    LL_BSTMR_SetOnePulseMode(p_instance, (uint32_t)pCfg->WorkMode);

    /* Update event source and enable */
    LL_BSTMR_SetUpdateSource(p_instance, (uint32_t)pCfg->UpdateSource);

    if (pCfg->UpdateEvent == HAL_BSTMR_UPDATE_EVT_ASSERT) {
        LL_BSTMR_DisableUpdateEvent(p_instance);
    } else if (pCfg->UpdateEvent == HAL_BSTMR_UPDATE_EVT_RELEASE) {
        LL_BSTMR_EnableUpdateEvent(p_instance);
    }

    /* Auto preload */
    HAL_FUNC_ALTER(pCfg->AutoReloadPreload, LL_BSTMR_EnableAutoReload(p_instance),
                                            LL_BSTMR_DisableAutoReload(p_instance));

    return HAL_OK;
}


/**
  * @brief  Configure the BSTMR master
  * @param  Handle BSTMR handle.
  * @param  pCfg pointer to a HAL_BSTMR_MstInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef BSTMR_MstCfg(HAL_BSTMR_HandleTypeDef *Handle, 
                                      const HAL_BSTMR_MstInitTypeDef *pCfg)
{
    BSTMR_TypeDef *p_instance = Handle->Instance;

    /* Master mode and TRGO width */
    LL_BSTMR_SetTriggerOutput(p_instance, (uint32_t)pCfg->MasterMode);
    LL_BSTMR_SetTrigOutputWidth(p_instance, pCfg->TRGOWidth);

    return HAL_OK;
}

/**
  * @}
  */

#endif /* HAL_BSTMR_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* BSTMR */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

