/**
  ******************************************************************************
  * @file    tae32g58xx_hal_lptmr.c
  * @author  Tai-Action SD Team
  * @brief   LPTMR HAL module driver (advanced timer).
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

/** @defgroup LPTMR_HAL LPTMR HAL
  * @brief    LPTMR HAL module driver.
  * @{
  */

#if defined(TMR6)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_LPTMR_MODULE_ENABLED) && (HAL_LPTMR_MODULE_ENABLED == 1)

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup LPTMR_HAL_Private_Constants LPTMR HAL Private Constants
  * @brief    LPTMR HAL Private Constants
  * @{
  */

/**
  * @brief  Default timeout value used by blocking LPTMR operations.
  */
#define LPTMR_DEFAULT_TIMEOUT         (10UL)

/**
  * @}
  */ /* LPTMR_HAL_Private_Constants */

/* Private macros ------------------------------------------------------------*/
/** @defgroup LPTMR_HAL_Private_Macros LPTMR HAL Private Macros
  * @brief    LPTMR HAL Private Macros
  * @{
  */

/** @defgroup LPTMR_HAL_PM_Discriminant LPTMR HAL Discriminant
  * @brief    LPTMR HAL Discriminant
  * @{
  */

#define IS_LPTMR_ENABLE(__VAL__)                      (((__VAL__) == HAL_LPTMR_FUNC_DISABLE) || \
                                                       ((__VAL__) == HAL_LPTMR_FUNC_ENABLE))

#define IS_LPTMR_WORK_MODE(__VAL__)                   (((__VAL__) == HAL_LPTMR_WORK_MODE_CONTINUE) || \
                                                       ((__VAL__) == HAL_LPTMR_WORK_MODE_SINGLE))

#define IS_LPTMR_CHANNEL_IDX(__VAL__)                 (((__VAL__) == HAL_LPTMR_CHANNEL_0))

#define IS_LPTMR_CMP_POL(__VAL__)                     (((__VAL__) == HAL_LPTMR_CMP_POL_HIGH) || \
                                                       ((__VAL__) == HAL_LPTMR_CMP_POL_LOW))

#define IS_LPTMR_ETR_MODE(__VAL__)                    (((__VAL__) == HAL_LPTMR_ETR_MODE_INT_CLK) || \
                                                       ((__VAL__) == HAL_LPTMR_ETR_MODE_EXT_CLK))

#define IS_LPTMR_ETR_EDGE(__VAL__)                    (((__VAL__) == HAL_LPTMR_ETR_EDGE_MODE_CLOSE) || \
                                                       ((__VAL__) == HAL_LPTMR_ETR_EDGE_MODE_RISING) || \
                                                       ((__VAL__) == HAL_LPTMR_ETR_EDGE_MODE_FALLING) || \
                                                       ((__VAL__) == HAL_LPTMR_ETR_EDGE_MODE_RISING_FALLING))

#define IS_LPTMR_SLV_MODE(__VAL__)                    (((__VAL__) == HAL_LPTMR_SLV_MODE_DIS) || \
                                                       ((__VAL__) == HAL_LPTMR_SLV_MODE_RST) || \
                                                       ((__VAL__) == HAL_LPTMR_SLV_MODE_GATING) || \
                                                       ((__VAL__) == HAL_LPTMR_SLV_MODE_TRIG) || \
                                                       ((__VAL__) == HAL_LPTMR_SLV_MODE_EXTCLK) || \
                                                       ((__VAL__) == HAL_LPTMR_SLV_MODE_RST_TRIG) || \
                                                       ((__VAL__) == HAL_LPTMR_SLV_MODE_RST_GATING))

#define IS_LPTMR_TRIG(__VAL__)                        (((__VAL__) == HAL_LPTMR_TRIG_ITR0)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR1)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR2)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR3)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR4)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR5)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR6)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR7)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR8)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR9)  || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR10) || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR11) || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR12) || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR13) || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR14) || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ITR15) || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ETR_FE) || \
                                                       ((__VAL__) == HAL_LPTMR_TRIG_ETR_F))

#define IS_LPTMR_EVENTSOURCE(__VAL__)                 (((__VAL__) == HAL_LPTMR_EVENTSOURCE_UPDATE)      || \
                                                       ((__VAL__) == HAL_LPTMR_EVENTSOURCE_TRIG)        || \
                                                       ((__VAL__) == HAL_LPTMR_EVENTSOURCE_CMP_UPD)     || \
                                                       ((__VAL__) == HAL_LPTMR_EVENTSOURCE_CNTR_START))

#define IS_LPTMR_ETR_FILTER(__VAL__)                  (((__VAL__) >= HAL_LPTMR_ETR_FILTER_NONE) && \
                                                       ((__VAL__) <= HAL_LPTMR_ETR_FILTER_TDS_X15))


/**
  * @}
  */ /* LPTMR_HAL_PM_Discriminant */


/**
  * @}
  */ /* LPTMR_HAL_EF_Configuration */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup LPTMR_HAL_Private_Functions LPTMR HAL Private Functions
  * @{
  */
static HAL_StatusTypeDef LPTMR_BaseCfg(HAL_LPTMR_HandleTypeDef *Handle, 
                                       const HAL_LPTMR_BaseInitTypeDef *pCfg);

static HAL_StatusTypeDef LPTMR_OutputCmpCfg(HAL_LPTMR_HandleTypeDef *Handle, 
                                            const HAL_LPTMR_OutputCmpInitTypeDef *pCfg);

static HAL_StatusTypeDef LPTMR_SlvCfg(HAL_LPTMR_HandleTypeDef *Handle, 
                                      const HAL_LPTMR_SlvInitTypeDef *pCfg);

__STATIC_FORCEINLINE uint32_t LPTMR_IsSlvModeTrigEnabled(HAL_LPTMR_HandleTypeDef *Handle);
__STATIC_FORCEINLINE void LPTMR_WaitForBusIdle(HAL_LPTMR_HandleTypeDef *Handle);

static HAL_StatusTypeDef LPTMR_Activate(HAL_LPTMR_HandleTypeDef *Handle);
static HAL_StatusTypeDef LPTMR_Deactivate(HAL_LPTMR_HandleTypeDef *Handle);

static HAL_StatusTypeDef LPTMR_UpdPrdVal(HAL_LPTMR_HandleTypeDef *Handle, 
                                         uint16_t Period);

static HAL_StatusTypeDef LPTMR_UpdCmpVal(HAL_LPTMR_HandleTypeDef *Handle, 
                                         uint16_t Compare);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup LPTMR_HAL_Exported_Functions LPTMR HAL Exported Functions
  * @{
  */

/** @defgroup LPTMR_HAL_EF_Initialization LPTMR HAL Initialization
  * @{
  */

/**
  * @brief  Initialize the LPTMR peripheral according to the specified parameters
  *         and create the associated handle.
  * @param  Handle LPTMR handle.
  * @param  LPTMRx LPTMR instance.
  * @param  pInit  pointer to a HAL_LPTMR_BaseInitTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_Base_Init(HAL_LPTMR_HandleTypeDef *Handle, 
                                      LPTMR_TypeDef *LPTMRx,
                                      const HAL_LPTMR_BaseInitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));
    ASSERT_FUNC_PARAM(pInit != NULL);

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(LPTMRx)) || (pInit == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_PARAM(IS_LPTMR_WORK_MODE(pInit->WorkMode));

    HAL_StatusTypeDef ret = HAL_OK;

    Handle->State = HAL_LPTMR_STATE_RESET;

    /* Bind the instance passed by the caller */
    Handle->Instance = LPTMRx;

    /* Init the low level hardware: CLOCK, NVIC */
    HAL_LPTMR_Base_MspInit(Handle);

    Handle->UpdateInterval = (SystemCoreClockGet() / HAL_RCU_GetPeriphCLKFreq(HAL_RCU_PERIPHCLK_LPTMR)) * 6UL;

    /* Configure the time base */
    ret = LPTMR_BaseCfg(Handle, pInit);

    if (ret == HAL_OK) {
        Handle->LastErrorCodes = HAL_LPTMR_ERROR_NONE;
        Handle->State          = HAL_LPTMR_STATE_CONFIGURABLE;
    } else {
        Handle->LastErrorCodes = HAL_LPTMR_ERROR_BASE_CONFIG;
    }

    return ret;
}

/**
  * @brief  De-initialize the LPTMR peripheral.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_Base_DeInit(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LPTMR_TypeDef *p_instance = Handle->Instance;

    Handle->State = HAL_LPTMR_STATE_BUSY;

    /* Stop the counter and its interrupts */
    LL_LPTMR_DisableCounter(p_instance);

    /* Disable all capture/compare channels */
    LL_LPTMR_DisableIT(p_instance, LL_LPTMR_IER_IT_EN_MSK);
    LL_LPTMR_DisableCompareChannel(p_instance);

    /* De-init the low level hardware: GPIO, CLOCK, NVIC */
    HAL_LPTMR_Base_MspDeInit(Handle);

    Handle->LastErrorCodes = HAL_LPTMR_ERROR_NONE;
    Handle->State          = HAL_LPTMR_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the LPTMR MSP.
  * @note   This function should not be modified. When the application needs its
  *         own implementation, it may override this weak function in the user file.
  * @param  Handle LPTMR handle.
  * @return None
  */
__WEAK void HAL_LPTMR_Base_MspInit(HAL_LPTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  De-initialize the LPTMR MSP.
  * @param  Handle LPTMR handle.
  * @return None
  */
__WEAK void HAL_LPTMR_Base_MspDeInit(HAL_LPTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  Initialize the LPTMR IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval None
  */
__WEAK void HAL_LPTMR_IoInit(LPTMR_TypeDef *LPTMRx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(LPTMRx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_LPTMR_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the LPTMR IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  LPTMRx Specifies LPTMR peripheral
  * @retval None
  */
__WEAK void HAL_LPTMR_IoDeInit(LPTMR_TypeDef *LPTMRx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(LPTMRx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_LPTMR_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */

/** @defgroup LPTMR_HAL_EF_Configuration LPTMR HAL Configuration
  * @{
  */

/**
  * @brief  Configure one LPTMR output compare channel.
  * @param  Handle LPTMR handle.
  * @param  Channel LPTMR channel.
  * @param  pCfg pointer to the output compare configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_OC_Init(HAL_LPTMR_HandleTypeDef *Handle, 
                                    const HAL_LPTMR_OutputCmpInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_CMP_POL(pCfg->OCPolarity));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = LPTMR_OutputCmpCfg(Handle, pCfg);

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the LPTMR slave mode and ETR input.
  * @param  Handle LPTMR handle.
  * @param  pCfg pointer to the slave/ETR configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_InitSlave(HAL_LPTMR_HandleTypeDef *Handle,
                                      const HAL_LPTMR_SlvInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ETR_MODE(pCfg->ClokMode));
    ASSERT_FUNC_PARAM(IS_LPTMR_ETR_EDGE(pCfg->TriggerPolarity));
    ASSERT_FUNC_PARAM(IS_LPTMR_SLV_MODE(pCfg->SlaveMode));
    ASSERT_FUNC_PARAM(IS_LPTMR_TRIG(pCfg->InputTrigger));
    ASSERT_FUNC_PARAM(IS_LPTMR_ETR_FILTER(pCfg->TriggerFilter));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = LPTMR_SlvCfg(Handle, pCfg);

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @}
  */

/** @defgroup LPTMR_HAL_EF_IO_Operation LPTMR HAL IO Operation
  * @{
  */
/**
  * @brief  Start the Counter mode.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_Counter_Start(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    HAL_StatusTypeDef ret = HAL_OK;

    if (!LPTMR_IsSlvModeTrigEnabled(Handle)) {
        ret = LPTMR_Activate(Handle);
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Stop the Counter mode.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_Counter_Stop(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    HAL_StatusTypeDef ret;

    /* Wait until the disable has actually completed. */
    ret = LPTMR_Deactivate(Handle);

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Start the LPTMR time base in interrupt mode.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_Counter_Start_IT(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    HAL_StatusTypeDef ret = HAL_OK;

    if (!LPTMR_IsSlvModeTrigEnabled(Handle)) {
        ret = LPTMR_Activate(Handle);
    }

    if (ret == HAL_OK) {
        LL_LPTMR_EnableIT_UPDATE(Handle->Instance);
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Stop the LPTMR time base in interrupt mode.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_Counter_Stop_IT(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    HAL_StatusTypeDef ret;

    ret = LPTMR_Deactivate(Handle);

    if (ret == HAL_OK) {
        LL_LPTMR_DisableIT_UPDATE(Handle->Instance);
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the output compare of one channel.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_OC_Start(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    HAL_StatusTypeDef ret = HAL_OK;

    if (LL_LPTMR_IsEnabledCounter(Handle->Instance)) {
        return HAL_ERROR;
    } else {
        LL_LPTMR_EnableCompareChannel(Handle->Instance); 
    }

    if (!LPTMR_IsSlvModeTrigEnabled(Handle)) {
        ret = LPTMR_Activate(Handle);
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the output compare of one channel.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_OC_Stop(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    HAL_StatusTypeDef ret;

    ret = LPTMR_Deactivate(Handle);

    if (ret == HAL_OK) {
        LL_LPTMR_DisableCompareChannel(Handle->Instance); 
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the output compare interrupt of one channel.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_OC_StartIT(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LPTMR_TypeDef *p_instance = Handle->Instance;
    HAL_StatusTypeDef ret = HAL_OK;

    if (LL_LPTMR_IsEnabledCounter(Handle->Instance)) {
        return HAL_ERROR;
    } else {
        LL_LPTMR_EnableCompareChannel(Handle->Instance); 
    }

    if (!LPTMR_IsSlvModeTrigEnabled(Handle)) {
        ret = LPTMR_Activate(Handle);
    }

    if (ret == HAL_OK) {
        LL_LPTMR_EnableIT_CMP(p_instance);
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the output compare interrupt of one channel.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_OC_StopIT(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LPTMR_TypeDef *p_instance = Handle->Instance;
    HAL_StatusTypeDef ret;

    ret = LPTMR_Deactivate(Handle);

    if (ret == HAL_OK) {
        LL_LPTMR_DisableCompareChannel(p_instance);
        LL_LPTMR_DisableIT_CMP(p_instance);    
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Generate a software event of the LPTMR.
  * @param  Handle LPTMR handle.
  * @param  EventSource event to generate
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_GenerateEvent(HAL_LPTMR_HandleTypeDef *Handle, HAL_LPTMR_EvtSrcTypeDef EventSource)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_LPTMR_EVENTSOURCE(EventSource));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance)) || (!IS_LPTMR_EVENTSOURCE(EventSource))) {
            return HAL_INVALID;
        }
    });

    HAL_StatusTypeDef ret = HAL_OK;
    LPTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE);

    HAL_LPTMR_PARAM_UPDATE(Handle->State, HAL_LPTMR_STATE_CONFIGURABLE, HAL_LPTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (EventSource) {
        case HAL_LPTMR_EVENTSOURCE_UPDATE:
            LL_LPTMR_GenerateEvent_UPDATE(p_instance);
            break;

        case HAL_LPTMR_EVENTSOURCE_TRIG:
            LL_LPTMR_GenerateEvent_TRIG(p_instance);
            break;

        case HAL_LPTMR_EVENTSOURCE_CMP_UPD:
            LL_LPTMR_GenerateEvent_CMP(p_instance);
            break;

        case HAL_LPTMR_EVENTSOURCE_CNTR_START:
            LL_LPTMR_GenerateEvent_START(p_instance);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    Handle->State = HAL_LPTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Read the counter at runtime.
  * @param  Handle LPTMR handle.
  * @retval the timer counter register.
  */
uint16_t HAL_LPTMR_ReadCounter(const HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    return (uint16_t)(LL_LPTMR_GetCounter(Handle->Instance));
}

/**
  * @brief  Read the Compare at runtime.
  * @param  Handle LPTMR handle.
  * @retval the timer Compare register.
  */
uint16_t HAL_LPTMR_ReadCompare(const HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    return (uint16_t)(LL_LPTMR_GetCompare(Handle->Instance));
}



/**
  * @}
  */

/** @defgroup LPTMR_HAL_EF_IRQ_Handler LPTMR HAL IRQ Handler and Callbacks
  * @{
  */

/**
  * @brief  Enable the module level interrupts selected by ITMask.
  * @param  Handle LPTMR handle.
  * @param  ITMask interrupts to enable, value of @ref HAL_LPTMR_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_InterruptRequestEnable(HAL_LPTMR_HandleTypeDef *Handle, 
                                                   HAL_LPTMR_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_LPTMR_EnableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Disable the module level interrupts selected by ITMask.
  * @param  Handle LPTMR handle.
  * @param  ITMask interrupts to disable, value of @ref HAL_LPTMR_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_LPTMR_InterruptRequestDisable(HAL_LPTMR_HandleTypeDef *Handle, 
                                                    HAL_LPTMR_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_LPTMR_DisableIT(Handle->Instance, ITMask);

    return HAL_OK;
}


/**
  * @brief  Handle the LPTMR interrupt handler.
  * @param  Handle LPTMR handle.
  * @return None
  */
void HAL_LPTMR_IRQHandler(HAL_LPTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(Handle->Instance));

    HAL_LPTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_LPTMR_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    LPTMR_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_LPTMR_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_LPTMR_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_LPTMR_SR_IT_FLAG_MSK; 


    /* Trigger interrupt */
    if (flag_status_masked & LL_LPTMR_SR_TIF) {
        LL_LPTMR_ClearFlag_TRIG(p_instance);

        HAL_LPTMR_TriggerCallback(Handle);
    }

    /* Update interrupt */
    if (flag_status_masked & LL_LPTMR_SR_UIF) {
        LL_LPTMR_ClearFlag_UPDATE(p_instance);

        HAL_LPTMR_UpdateCallback(Handle);
    }

    /* Compare interrupt */
    if (flag_status_masked & LL_LPTMR_SR_CIF) {
        LL_LPTMR_ClearFlag_CMP(p_instance);    

        HAL_LPTMR_CompareMatchCallback(Handle);    
    }

}

/**
  * @brief  LPTMR update callback.
  * @param  Handle LPTMR handle.
  * @return None
  */
__WEAK void HAL_LPTMR_UpdateCallback(HAL_LPTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}


/**
  * @brief  LPTMR trigger callback.
  * @param  Handle LPTMR handle.
  * @return None
  */
__WEAK void HAL_LPTMR_TriggerCallback(HAL_LPTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  LPTMR channel compare callback.
  * @param  Handle LPTMR handle.
  * @return None
  */
__WEAK void HAL_LPTMR_CompareMatchCallback(HAL_LPTMR_HandleTypeDef *Handle)
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
/** @defgroup LPTMR_HAL_Private_Functions LPTMR HAL Private Functions
  * @{
  */

/**
  * @brief  Configure the LPTMR time base from the init structure.
  * @param  Handle LPTMR handle.
  * @param  pCfg pointer to a HAL_LPTMR_BaseInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef LPTMR_BaseCfg(HAL_LPTMR_HandleTypeDef *Handle, 
                                       const HAL_LPTMR_BaseInitTypeDef *pCfg)
{
    LPTMR_TypeDef *p_instance = Handle->Instance;
    HAL_StatusTypeDef ret;

    if (LL_LPTMR_IsEnabledCounter(p_instance)) {
        return HAL_ERROR;
    }

    ret = LPTMR_UpdPrdVal(Handle, pCfg->Period);
    if (ret != HAL_OK) {
        return ret;
    }

    /* Time base: counter value and prescaler (all 16-bit) */
    LL_LPTMR_SetCounter(p_instance, 0UL);
    LL_LPTMR_SetPrescaler(p_instance, pCfg->Prescaler);

    /* Work mode */
    LL_LPTMR_SetOnePulseMode(p_instance, (uint32_t)pCfg->WorkMode);

    LPTMR_WaitForBusIdle(Handle);

    /* Auto preload */
    HAL_FUNC_ALTER(pCfg->AutoReloadPreload, LL_LPTMR_EnableAutoReload(p_instance),
                                            LL_LPTMR_DisableAutoReload(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure one LPTMR output compare channel.
  * @param  Handle LPTMR handle.
  * @param  Channel LPTMR channel.
  * @param  pCfg pointer to a HAL_LPTMR_OutputCmpInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef LPTMR_OutputCmpCfg(HAL_LPTMR_HandleTypeDef *Handle, 
                                            const HAL_LPTMR_OutputCmpInitTypeDef *pCfg)
{
    LPTMR_TypeDef *p_instance = Handle->Instance;
    HAL_StatusTypeDef ret = HAL_OK;

    if (LL_LPTMR_IsEnabledCounter(p_instance)) {
        return HAL_ERROR;
    }

    ret = LPTMR_UpdCmpVal(Handle, pCfg->CompareValue);
    if (ret != HAL_OK) {
        return ret;
    }

    LL_LPTMR_SetPolarity(p_instance, (uint32_t)pCfg->OCPolarity);

    LPTMR_WaitForBusIdle(Handle);
                    
    HAL_FUNC_ALTER(pCfg->CompareAutoReload, LL_LPTMR_EnableComparePreload(p_instance),             
                                            LL_LPTMR_DisableComparePreload(p_instance));           

    return HAL_OK;
}

/**
  * @brief  Configure the LPTMR slave mode and ETR input.
  * @param  Handle LPTMR handle.
  * @param  pCfg pointer to a HAL_LPTMR_SlvInitTypeDef structure.
  * @return HAL
  */
static HAL_StatusTypeDef LPTMR_SlvCfg(HAL_LPTMR_HandleTypeDef *Handle, 
                                      const HAL_LPTMR_SlvInitTypeDef *pCfg)
{
    LPTMR_TypeDef *p_instance = Handle->Instance;

    if (LL_LPTMR_IsEnabledCounter(p_instance)) {
        return HAL_ERROR;
    }

    LL_LPTMR_ConfigSlaveControl(p_instance, (uint32_t)pCfg->SlaveMode, 
                                            (uint32_t)pCfg->ClokMode, 
                                            (uint32_t)pCfg->TriggerPolarity, 
                                            (uint32_t)pCfg->TriggerFilter, 
                                            (uint32_t)pCfg->InputTrigger);

    return HAL_OK;
}

/**
  * @brief  Judge whether the slave mode of LPTMR is enabled or not.
  * @param  Handle LPTMR handle.
  * @return 0: Disabled, 1: Enabled
  */
__STATIC_FORCEINLINE uint32_t LPTMR_IsSlvModeTrigEnabled(HAL_LPTMR_HandleTypeDef *Handle)
{
    const uint32_t slv_mode = LL_LPTMR_GetSlaveMode(Handle->Instance);
    return ((slv_mode == LL_LPTMR_SLV_MODE_TRIG) || (slv_mode == LL_LPTMR_SLV_MODE_RST_TRIG)) ? 1UL : 0UL;
}

/**
  * @brief  Wait for bus idle
  * @param  Handle LPTMR handle.
  */
__STATIC_FORCEINLINE void LPTMR_WaitForBusIdle(HAL_LPTMR_HandleTypeDef *Handle)
{
    for (volatile uint32_t i = 0UL; i < Handle->UpdateInterval; i++) {
        __NOP();
    }
}

/**
  * @brief  Enable the LPTMR Counter.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
static HAL_StatusTypeDef LPTMR_Activate(HAL_LPTMR_HandleTypeDef *Handle)
{
    LPTMR_TypeDef *p_instance = Handle->Instance;

    LPTMR_WaitForBusIdle(Handle);

    LL_LPTMR_EnableCounter(p_instance);
    LL_LPTMR_GenerateEvent_START(p_instance);

    return HAL_OK;
}

/**
  * @brief  Disable the LPTMR Counter.
  * @param  Handle LPTMR handle.
  * @return HAL status
  */
static HAL_StatusTypeDef LPTMR_Deactivate(HAL_LPTMR_HandleTypeDef *Handle)
{
    LPTMR_TypeDef *p_instance = Handle->Instance;

    LPTMR_WaitForBusIdle(Handle);

    LL_LPTMR_DisableCounter(p_instance);

    return HAL_OK;
}

/**
  * @brief  Set the LPTMR auto-reload period.
  * @param  Handle LPTMR handle.
  * @param  Period Period value
  * @return HAL status
  */
static HAL_StatusTypeDef LPTMR_UpdPrdVal(HAL_LPTMR_HandleTypeDef *Handle, uint16_t Period)
{
    uint32_t tickstart;
    LPTMR_TypeDef *p_instance = Handle->Instance;

    /* Wait until the update has actually completed. */
    tickstart = HAL_GetTick();
    while (LL_LPTMR_IsActiveFlag_PUS(p_instance)) {
        if (HAL_GetTick() - tickstart > LPTMR_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (LL_LPTMR_IsActiveFlag_PUS(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }

    /* Time base: period */
    LL_LPTMR_SetAutoReload(p_instance, Period);

    return HAL_OK;
}

/**
  * @brief  Set the LPTMR auto-reload period.
  * @param  Handle LPTMR handle.
  * @param  Compare Compare value
  * @return HAL status
  */
static HAL_StatusTypeDef LPTMR_UpdCmpVal(HAL_LPTMR_HandleTypeDef *Handle, uint16_t Compare)
{
    uint32_t tickstart;
    LPTMR_TypeDef *p_instance = Handle->Instance;

    /* Wait until the update has actually completed. */
    tickstart = HAL_GetTick();
    while (LL_LPTMR_IsActiveFlag_CUS(p_instance)) {
        if (HAL_GetTick() - tickstart > LPTMR_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (LL_LPTMR_IsActiveFlag_CUS(p_instance)) {
                return HAL_TIMEOUT;
            }
        }
    }  

    LL_LPTMR_SetCompare(p_instance, Compare);   
    
    return HAL_OK;
}


/**
  * @}
  */

#endif /* HAL_LPTMR_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* LPTMR */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

