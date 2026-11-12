/**
  ******************************************************************************
  * @file    tae32g58xx_hal_gptmry.c
  * @author  Tai-Action SD Team
  * @brief   GPTMRY HAL module driver (general purpose timer).
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

/** @defgroup GPTMRY_HAL GPTMRY HAL
  * @brief    GPTMRY HAL module driver.
  * @{
  */

#if defined(TMR3) || defined(TMR4)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_GPTMRY_MODULE_ENABLED) && (HAL_GPTMRY_MODULE_ENABLED == 1)



/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup GPTMRY_HAL_Private_Macros GPTMRY HAL Private Macros
  * @brief    GPTMRY HAL Private Macros
  * @{
  */

/** @defgroup GPTMRY_HAL_PM_Discriminant GPTMRY HAL Discriminant
  * @brief    GPTMRY HAL Discriminant
  * @{
  */

#define IS_GPTMRY_ENABLE(__VAL__)                     (((__VAL__) == HAL_GPTMRY_FUNC_DISABLE) || \
                                                       ((__VAL__) == HAL_GPTMRY_FUNC_ENABLE))

#define IS_GPTMRY_WORK_MODE(__VAL__)                  (((__VAL__) == HAL_GPTMRY_WORK_MODE_CONTINUE) || \
                                                       ((__VAL__) == HAL_GPTMRY_WORK_MODE_SINGLE))

#define IS_GPTMRY_UPDATE_EVT_SRC(__VAL__)             (((__VAL__) == HAL_GPTMRY_UPDATE_EVT_SRC_OV_UG) || \
                                                       ((__VAL__) == HAL_GPTMRY_UPDATE_EVT_SRC_OV))

#define IS_GPTMRY_MST_MODE(__VAL__)                   (((__VAL__) == HAL_GPTMRY_MST_MODE_RESET)          || \
                                                       ((__VAL__) == HAL_GPTMRY_MST_MODE_ENABLE)         || \
                                                       ((__VAL__) == HAL_GPTMRY_MST_MODE_UPDATE)         || \
                                                       ((__VAL__) == HAL_GPTMRY_MST_MODE_CAP_CMP_EVT)    || \
                                                       ((__VAL__) == HAL_GPTMRY_MST_MODE_CMP_OUT0)       || \
                                                       ((__VAL__) == HAL_GPTMRY_MST_MODE_CMP_OUT1)       || \
                                                       ((__VAL__) == HAL_GPTMRY_MST_MODE_CMP_OUT2)       || \
                                                       ((__VAL__) == HAL_GPTMRY_MST_MODE_CMP_OUT3))

#define IS_GPTMRY_COUNTER_MODE(__VAL__)               (((__VAL__) == HAL_GPTMRY_COUNTER_MODE_UP)              || \
                                                       ((__VAL__) == HAL_GPTMRY_COUNTER_MODE_DOWN)            || \
                                                       ((__VAL__) == HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED1) || \
                                                       ((__VAL__) == HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED2) || \
                                                       ((__VAL__) == HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED3))

#define IS_GPTMRY_CHANNEL_IDX(__VAL__)                (((__VAL__) == HAL_GPTMRY_CHANNEL_0) || \
                                                       ((__VAL__) == HAL_GPTMRY_CHANNEL_1) || \
                                                       ((__VAL__) == HAL_GPTMRY_CHANNEL_2) || \
                                                       ((__VAL__) == HAL_GPTMRY_CHANNEL_3))

#define IS_GPTMRY_CAP_POL(__VAL__)                    (((__VAL__) == HAL_GPTMRY_CAP_POL_CLOSE)   || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_POL_RISING)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_POL_FALLING) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_POL_BOTH_EDGE))

#define IS_GPTMRY_CAP_PRESCALER(__VAL__)              (((__VAL__) == HAL_GPTMRY_CAP_PRESCALER_1) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_PRESCALER_2) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_PRESCALER_4) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_PRESCALER_8))

#define IS_GPTMRY_CAP_INPUT_MAP(__VAL__)              (((__VAL__) == HAL_GPTMRY_CAP_INPUT_MAP_0) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_MAP_1) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_MAP_TRGI))

#define IS_GPTMRY_CAP_INPUT_SRC(__VAL__)              (((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN0)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN1)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN2)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN3)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN4)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN5)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN6)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN7)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN8)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN9)  || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN10) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN11) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN12) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN13) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN14) || \
                                                       ((__VAL__) == HAL_GPTMRY_CAP_INPUT_SRC_IN15))

#define IS_GPTMRY_CMP_POL(__VAL__)                    (((__VAL__) == HAL_GPTMRY_CMP_POL_HIGH) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_POL_LOW))

#define IS_GPTMRY_OC_MODE(__VAL__)                    (((__VAL__) == HAL_GPTMRY_CMP_MODE_FREEZE) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_ACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_INACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_TOGGLE) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_FORCE_INACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_FORCE_ACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_PWM1) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_PWM2) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_RETRIG_OPM1) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_RETRIG_OPM2) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_COMB_PWM1) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_COMB_PWM2) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_ASYM_PWM1) || \
                                                       ((__VAL__) == HAL_GPTMRY_CMP_MODE_ASYM_PWM2))

#define IS_GPTMRY_ETR_MODE(__VAL__)                   (((__VAL__) == HAL_GPTMRY_ETR_MODE_EXT_CLK_1) || \
                                                       ((__VAL__) == HAL_GPTMRY_ETR_MODE_EXT_CLK_2))

#define IS_GPTMRY_ETR_EDGE(__VAL__)                   (((__VAL__) == HAL_GPTMRY_ETR_EDGE_MODE_CLOSE) || \
                                                       ((__VAL__) == HAL_GPTMRY_ETR_EDGE_MODE_RISING) || \
                                                       ((__VAL__) == HAL_GPTMRY_ETR_EDGE_MODE_FALLING) || \
                                                       ((__VAL__) == HAL_GPTMRY_ETR_EDGE_MODE_RISING_FALLING))

#define IS_GPTMRY_TI0_IN_SRC(__VAL__)                 (((__VAL__) == HAL_GPTMRY_TI0_IN_SRC_CH0)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TI0_IN_SRC_CH0_1_2_XOR))

#define IS_GPTMRY_SLV_MODE(__VAL__)                   (((__VAL__) == HAL_GPTMRY_SLV_MODE_DIS) || \
                                                       ((__VAL__) == HAL_GPTMRY_SLV_MODE_RST) || \
                                                       ((__VAL__) == HAL_GPTMRY_SLV_MODE_GATING) || \
                                                       ((__VAL__) == HAL_GPTMRY_SLV_MODE_TRIG) || \
                                                       ((__VAL__) == HAL_GPTMRY_SLV_MODE_EXTCLK) || \
                                                       ((__VAL__) == HAL_GPTMRY_SLV_MODE_RST_TRIG))

#define IS_GPTMRY_TRIG(__VAL__)                       (((__VAL__) == HAL_GPTMRY_TRIG_ITR0)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR1)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR2)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR3)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR4)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR5)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR6)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR7)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR8)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR9)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR10) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR11) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR12) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR13) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR14) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ITR15) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_CH0_FE) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_CH0_F)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_CH1_F)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_CH2_F)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_CH3_F)  || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ETR_FE) || \
                                                       ((__VAL__) == HAL_GPTMRY_TRIG_ETR_F))

#define IS_GPTMRY_EVENTSOURCE(__VAL__)                (((__VAL__) == HAL_GPTMRY_EVENTSOURCE_UPDATE) || \
                                                       ((__VAL__) == HAL_GPTMRY_EVENTSOURCE_TRIG)   || \
                                                       ((__VAL__) == HAL_GPTMRY_EVENTSOURCE_CC0)    || \
                                                       ((__VAL__) == HAL_GPTMRY_EVENTSOURCE_CC1)    || \
                                                       ((__VAL__) == HAL_GPTMRY_EVENTSOURCE_CC2)    || \
                                                       ((__VAL__) == HAL_GPTMRY_EVENTSOURCE_CC3))

#define IS_GPTMRY_ETR_FILTER(__VAL__)                 (((__VAL__) >= HAL_GPTMRY_ETR_FILTER_NONE) && \
                                                       ((__VAL__) <= HAL_GPTMRY_ETR_FILTER_TDS_X15))


/**
  * @}
  */ /* GPTMRY_HAL_PM_Discriminant */


/**
  * @}
  */ /* GPTMRY_HAL_EF_Configuration */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup GPTMRY_HAL_Private_Functions GPTMRY HAL Private Functions
  * @{
  */
static HAL_StatusTypeDef GPTMRY_BaseCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                       const HAL_GPTMRY_BaseInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRY_InputCapCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                           HAL_GPTMRY_ChannelIdxTypeDef Channel, 
                                           const HAL_GPTMRY_InputCapInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRY_OutputCmpCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                            HAL_GPTMRY_ChannelIdxTypeDef Channel, 
                                            const HAL_GPTMRY_OutputCmpInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRY_MstCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                      const HAL_GPTMRY_MstInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRY_SlvCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                      const HAL_GPTMRY_SlvInitTypeDef *pCfg);

__STATIC_FORCEINLINE uint32_t GPTMRY_IsSlvModeTrigEnabled(HAL_GPTMRY_HandleTypeDef *Handle);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup GPTMRY_HAL_Exported_Functions GPTMRY HAL Exported Functions
  * @{
  */

/** @defgroup GPTMRY_HAL_EF_Initialization GPTMRY HAL Initialization
  * @{
  */

/**
  * @brief  Initialize the GPTMRY peripheral according to the specified parameters
  *         and create the associated handle.
  * @param  Handle GPTMRY handle.
  * @param  GPTMRy GPTMRY instance.
  * @param  pInit  pointer to a HAL_GPTMRY_BaseInitTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_Base_Init(HAL_GPTMRY_HandleTypeDef *Handle, 
                                      GPTMRy_TypeDef *GPTMRy,
                                      const HAL_GPTMRY_BaseInitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));
    ASSERT_FUNC_PARAM(pInit != NULL);

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(GPTMRy)) || (pInit == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_PARAM(IS_GPTMRY_WORK_MODE(pInit->WorkMode));
    ASSERT_FUNC_PARAM(IS_GPTMRY_UPDATE_EVT_SRC(pInit->UpdateSource));
    ASSERT_FUNC_PARAM(IS_GPTMRY_COUNTER_MODE(pInit->CounterMode));

    Handle->State = HAL_GPTMRY_STATE_RESET;

    /* Bind the instance passed by the caller */
    Handle->Instance = GPTMRy;

    /* Init the low level hardware: CLOCK, NVIC */
    HAL_GPTMRY_Base_MspInit(Handle);

    /* Configure the time base */
    (void) GPTMRY_BaseCfg(Handle, pInit);

    Handle->LastErrorCodes = HAL_GPTMRY_ERROR_NONE;
    Handle->State          = HAL_GPTMRY_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  De-initialize the GPTMRY peripheral.
  * @param  Handle GPTMRY handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_Base_DeInit(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    GPTMRy_TypeDef *p_instance = Handle->Instance;

    Handle->State = HAL_GPTMRY_STATE_BUSY;

    /* Stop the counter and its interrupts */
    LL_GPTMRY_DisableCounter(p_instance);

    /* Disable all capture/compare channels */
    LL_GPTMRY_DisableIT(p_instance, LL_GPTMRY_IER_IT_EN_MSK);

    LL_GPTMRY_CC_DisableAllChannel(p_instance);

    /* De-init the low level hardware: GPIO, CLOCK, NVIC */
    HAL_GPTMRY_Base_MspDeInit(Handle);

    Handle->LastErrorCodes = HAL_GPTMRY_ERROR_NONE;
    Handle->State          = HAL_GPTMRY_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the GPTMRY MSP.
  * @note   This function should not be modified. When the application needs its
  *         own implementation, it may override this weak function in the user file.
  * @param  Handle GPTMRY handle.
  * @return None
  */
__WEAK void HAL_GPTMRY_Base_MspInit(HAL_GPTMRY_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  De-initialize the GPTMRY MSP.
  * @param  Handle GPTMRY handle.
  * @return None
  */
__WEAK void HAL_GPTMRY_Base_MspDeInit(HAL_GPTMRY_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  Initialize the GPTMRY IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval None
  */
__WEAK void HAL_GPTMRY_IoInit(GPTMRy_TypeDef *GPTMRy)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(GPTMRy);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_GPTMRY_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the GPTMRY IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  GPTMRy Specifies GPTMRY peripheral
  * @retval None
  */
__WEAK void HAL_GPTMRY_IoDeInit(GPTMRy_TypeDef *GPTMRy)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(GPTMRy);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_GPTMRY_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */

/** @defgroup GPTMRY_HAL_EF_Configuration GPTMRY HAL Configuration
  * @{
  */

/**
  * @brief  Configure one GPTMRY input capture channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @param  pCfg pointer to the input capture configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_IC_Init(HAL_GPTMRY_HandleTypeDef *Handle, 
                                    HAL_GPTMRY_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRY_InputCapInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_CAP_POL(pCfg->ICPolarity));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CAP_INPUT_MAP(pCfg->ICSelection));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CAP_PRESCALER(pCfg->ICPrescaler));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CAP_INPUT_SRC(pCfg->ICTriggerSource));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRY_InputCapCfg(Handle, Channel, pCfg);

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure one GPTMRY output compare channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @param  pCfg pointer to the output compare configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_OC_Init(HAL_GPTMRY_HandleTypeDef *Handle, 
                                    HAL_GPTMRY_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRY_OutputCmpInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_OC_MODE(pCfg->OCMode));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CMP_POL(pCfg->OCPolarity));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CMP_POL(pCfg->OCNPolarity));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRY_OutputCmpCfg(Handle, Channel, pCfg);

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the GPTMRY Master mode
  * @param  Handle GPTMRY handle.
  * @param  pCfg pointer to the master configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_InitMaster(HAL_GPTMRY_HandleTypeDef *Handle,
                                       const HAL_GPTMRY_MstInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_MST_MODE(pCfg->MasterMode));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRY_MstCfg(Handle, pCfg);

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the GPTMRY slave mode and ETR input.
  * @param  Handle GPTMRY handle.
  * @param  pCfg pointer to the slave/ETR configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_InitSlave(HAL_GPTMRY_HandleTypeDef *Handle,
                                      const HAL_GPTMRY_SlvInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ETR_MODE(pCfg->ExtClokMode));
    ASSERT_FUNC_PARAM(IS_GPTMRY_ETR_EDGE(pCfg->TriggerPolarity));
    ASSERT_FUNC_PARAM(IS_GPTMRY_SLV_MODE(pCfg->SlaveMode));
    ASSERT_FUNC_PARAM(IS_GPTMRY_TRIG(pCfg->InputTrigger));
    ASSERT_FUNC_PARAM(IS_GPTMRY_ETR_FILTER(pCfg->TriggerFilter));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRY_SlvCfg(Handle, pCfg);

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Generate a software event of the GPTMRY.
  * @param  Handle GPTMRY handle.
  * @param  Source TI0 input source
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_ConfigTI0InputSource(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_TI0InSrcTypeDef Source)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_TI0_IN_SRC(Source));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance)) || (!IS_GPTMRY_TI0_IN_SRC(Source))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_SetTI0InputSource(Handle->Instance, (uint32_t)Source);

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @}
  */

/** @defgroup GPTMRY_HAL_EF_IO_Operation GPTMRY HAL IO Operation
  * @{
  */
/**
  * @brief  Start the GPTMRY time base (polling mode).
  * @param  Handle GPTMRY handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_Base_Start(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    if (!GPTMRY_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRY_EnableCounter(Handle->Instance);
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Stop the GPTMRY time base (polling mode).
  * @param  Handle GPTMRY handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_Base_Stop(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_DisableCounter(Handle->Instance);

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the GPTMRY time base in interrupt mode.
  * @param  Handle GPTMRY handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_Base_Start_IT(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_EnableIT_UPDATE(Handle->Instance);

    if (!GPTMRY_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRY_EnableCounter(Handle->Instance);
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the GPTMRY time base in interrupt mode.
  * @param  Handle GPTMRY handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_Base_Stop_IT(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_DisableIT_UPDATE(Handle->Instance);
    LL_GPTMRY_DisableCounter(Handle->Instance);

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the output compare of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_OC_Start(HAL_GPTMRY_HandleTypeDef *Handle, 
                                     HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_CC_EnableChannel(p_instance, (uint32_t)Channel);

    if (!GPTMRY_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRY_EnableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the output compare of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_OC_Stop(HAL_GPTMRY_HandleTypeDef *Handle, 
                                    HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_CC_DisableChannel(p_instance, (uint32_t)Channel); 

    if (LL_GPTMRY_CC_IsAllChannelDisabled(p_instance)) {
        LL_GPTMRY_DisableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Start the output compare interrupt of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_OC_StartIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_EnableIT_CxMIE(p_instance, (uint32_t)Channel);
    LL_GPTMRY_CC_EnableChannel(p_instance, (uint32_t)Channel);

    if (!GPTMRY_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRY_EnableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the output compare interrupt of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_OC_StopIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRY_DisableIT_CxMIE(p_instance, (uint32_t)Channel);
    LL_GPTMRY_CC_DisableChannel(p_instance, (uint32_t)Channel);

    if (LL_GPTMRY_CC_IsAllChannelDisabled(p_instance)) {
        LL_GPTMRY_DisableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the input capture of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_IC_Start(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRY_CHANNEL_0: 
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_0); 
            break;
        case HAL_GPTMRY_CHANNEL_1: 
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_1); 
            break;
        case HAL_GPTMRY_CHANNEL_2: 
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_2); 
            break;
        case HAL_GPTMRY_CHANNEL_3:   
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_3); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (!GPTMRY_IsSlvModeTrigEnabled(Handle)) {
            LL_GPTMRY_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the input capture of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_IC_Stop(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRY_CHANNEL_0: 
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_0); 
            break;
        case HAL_GPTMRY_CHANNEL_1: 
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_1); 
            break;
        case HAL_GPTMRY_CHANNEL_2: 
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_2); 
            break;
        case HAL_GPTMRY_CHANNEL_3: 
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_3); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_GPTMRY_CC_IsAllChannelDisabled(p_instance)) {
            LL_GPTMRY_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the input capture interrupt of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_IC_StartIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRY_CHANNEL_0:
            LL_GPTMRY_EnableIT_CC0(p_instance);
            LL_GPTMRY_EnableIT_CC0OVR(p_instance);
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_0);
            break;
        case HAL_GPTMRY_CHANNEL_1:
            LL_GPTMRY_EnableIT_CC1(p_instance);
            LL_GPTMRY_EnableIT_CC1OVR(p_instance);
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_1);
            break;
        case HAL_GPTMRY_CHANNEL_2:
            LL_GPTMRY_EnableIT_CC2(p_instance);
            LL_GPTMRY_EnableIT_CC2OVR(p_instance);
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_2);
            break;
        case HAL_GPTMRY_CHANNEL_3:
            LL_GPTMRY_EnableIT_CC3(p_instance);
            LL_GPTMRY_EnableIT_CC3OVR(p_instance);
            LL_GPTMRY_CC_EnableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_3);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (!GPTMRY_IsSlvModeTrigEnabled(Handle)) {
            LL_GPTMRY_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the input capture interrupt of one channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_IC_StopIT(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRY_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRY_CHANNEL_0:
            LL_GPTMRY_DisableIT_CC0(p_instance);
            LL_GPTMRY_DisableIT_CC0OVR(p_instance);
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_0);
            break;
        case HAL_GPTMRY_CHANNEL_1:
            LL_GPTMRY_DisableIT_CC1(p_instance);
            LL_GPTMRY_DisableIT_CC1OVR(p_instance);
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_1);
            break;
        case HAL_GPTMRY_CHANNEL_2:
            LL_GPTMRY_DisableIT_CC2(p_instance);
            LL_GPTMRY_DisableIT_CC2OVR(p_instance);
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_2);
            break;
        case HAL_GPTMRY_CHANNEL_3:
            LL_GPTMRY_DisableIT_CC3(p_instance);
            LL_GPTMRY_DisableIT_CC3OVR(p_instance);
            LL_GPTMRY_CC_DisableChannel(p_instance, LL_GPTMRY_CAP_CMP_CH_3);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_GPTMRY_CC_IsAllChannelDisabled(p_instance)) {
            LL_GPTMRY_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Generate a software event of the GPTMRY.
  * @param  Handle GPTMRY handle.
  * @param  EventSource event to generate
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_GenerateEvent(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_EvtSrcTypeDef EventSource)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_EVENTSOURCE(EventSource));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance)) || (!IS_GPTMRY_EVENTSOURCE(EventSource))) {
            return HAL_INVALID;
        }
    });

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE);

    HAL_GPTMRY_PARAM_UPDATE(Handle->State, HAL_GPTMRY_STATE_CONFIGURABLE, HAL_GPTMRY_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (EventSource) {
        case HAL_GPTMRY_EVENTSOURCE_UPDATE:
            LL_GPTMRY_GenerateEvent_UPDATE(p_instance);
            break;

        case HAL_GPTMRY_EVENTSOURCE_TRIG:
            LL_GPTMRY_GenerateEvent_TRIG(p_instance);
            break;

        case HAL_GPTMRY_EVENTSOURCE_CC0:
            LL_GPTMRY_GenerateEvent_CC0(p_instance);
            break;

        case HAL_GPTMRY_EVENTSOURCE_CC1:
            LL_GPTMRY_GenerateEvent_CC1(p_instance);
            break;

        case HAL_GPTMRY_EVENTSOURCE_CC2:
            LL_GPTMRY_GenerateEvent_CC2(p_instance);
            break;

        case HAL_GPTMRY_EVENTSOURCE_CC3:
            LL_GPTMRY_GenerateEvent_CC3(p_instance);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    Handle->State = HAL_GPTMRY_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Read the captured value for an input channel of timer.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @retval Captured value
  */
uint32_t HAL_GPTMRY_ReadCapturedValue(const HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance)) || (Channel >= HAL_GPTMRY_CHANNEL_NUMS)) {
            return HAL_INVALID;
        }
    });

    return (uint32_t)(LL_GPTMRY_IC_GetChannelCompare(Handle->Instance, (uint32_t)Channel));
}

/**
  * @brief  Read the counter value at runtime.
  * @param  Handle GPTMRY handle.
  * @retval the timer counter register.
  */
uint32_t HAL_GPTMRY_ReadCounter(const HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    return (uint32_t)(LL_GPTMRY_GetCounter(Handle->Instance));
}

/**
  * @}
  */

/** @defgroup GPTMRY_HAL_EF_IRQ_Handler GPTMRY HAL IRQ Handler and Callbacks
  * @{
  */

/**
  * @brief  Enable the module level interrupts selected by ITMask.
  * @param  Handle GPTMRY handle.
  * @param  ITMask interrupts to enable, value of @ref HAL_GPTMRY_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_InterruptRequestEnable(HAL_GPTMRY_HandleTypeDef *Handle, 
                                                   HAL_GPTMRY_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_GPTMRY_EnableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Disable the module level interrupts selected by ITMask.
  * @param  Handle GPTMRY handle.
  * @param  ITMask interrupts to disable, value of @ref HAL_GPTMRY_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRY_InterruptRequestDisable(HAL_GPTMRY_HandleTypeDef *Handle, 
                                                    HAL_GPTMRY_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_GPTMRY_DisableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Handle the GPTMRY update event interrupt handler.
  * @param  Handle GPTMRY handle.
  * @return None
  */
void HAL_GPTMRY_UPD_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    GPTMRy_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_GPTMRY_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_GPTMRY_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers OVIF/UIF bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_GPTMRY_SR_UPD_IT_FLAG_MSK; 

    /* Update interrupt */
    if (flag_status_masked & LL_GPTMRY_SR_UIF) {
        LL_GPTMRY_ClearFlag_UPDATE(p_instance);

        HAL_GPTMRY_PeriodElapsedCallback(Handle);
    }

    /* Overflow interrupt */
    if (flag_status_masked & LL_GPTMRY_SR_OVIF) {
        LL_GPTMRY_ClearFlag_OVR(p_instance);

        HAL_GPTMRY_OverflowCallback(Handle);
    }
}

/**
  * @brief  Handle the GPTMRY trigger interrupt handler.
  * @param  Handle GPTMRY handle.
  * @return None
  */
void HAL_GPTMRY_TRG_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    GPTMRy_TypeDef *p_instance = Handle->Instance;

    /* Trigger interrupt */
    if ((LL_GPTMRY_IsEnabledIT_TRIG(p_instance) != 0UL) && 
        (LL_GPTMRY_IsActiveFlag_TRIG(p_instance) != 0UL)) {
        /* Clear flag */
        LL_GPTMRY_ClearFlag_TRIG(p_instance);

        /* Invoke callback */
        HAL_GPTMRY_TriggerCallback(Handle);
    }
}

/**
  * @brief  Handle the GPTMRY Compare/Capture interrupt handler.
  * @param  Handle GPTMRY handle.
  * @return None
  */
void HAL_GPTMRY_CC_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });
    
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_GPTMRY_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_GPTMRY_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers CCx bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_GPTMRY_SR_CC_IT_FLAG_MSK; 

    /* CC0 */
    if (flag_status_masked & LL_GPTMRY_SR_CC0OIF) {
        LL_GPTMRY_ClearFlag_CC0OVR(p_instance);         

        HAL_GPTMRY_IC_OverCaptureCallback(Handle, HAL_GPTMRY_CHANNEL_0); 
    }

    if (flag_status_masked & LL_GPTMRY_SR_CC0MIF) {
        LL_GPTMRY_ClearFlag_CC0(p_instance);    

        if (LL_GPTMRY_IC_GetActiveInput(p_instance, LL_GPTMRY_CAP_CMP_CH_0) == LL_GPTMRY_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRY_OC_DelayElapsedCallback(Handle, HAL_GPTMRY_CHANNEL_0);    
        } else {
            HAL_GPTMRY_IC_CaptureCallback(Handle, HAL_GPTMRY_CHANNEL_0);    
        }
    }

    /* CC1 */
    if (flag_status_masked & LL_GPTMRY_SR_CC1OIF) {
        LL_GPTMRY_ClearFlag_CC1OVR(p_instance);         

        HAL_GPTMRY_IC_OverCaptureCallback(Handle, HAL_GPTMRY_CHANNEL_1); 
    }

    if (flag_status_masked & LL_GPTMRY_SR_CC1MIF) {
        LL_GPTMRY_ClearFlag_CC1(p_instance);    

        if (LL_GPTMRY_IC_GetActiveInput(p_instance, LL_GPTMRY_CAP_CMP_CH_1) == LL_GPTMRY_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRY_OC_DelayElapsedCallback(Handle, HAL_GPTMRY_CHANNEL_1);    
        } else {
            HAL_GPTMRY_IC_CaptureCallback(Handle, HAL_GPTMRY_CHANNEL_1);    
        }
    }

    /* CC2 */
    if (flag_status_masked & LL_GPTMRY_SR_CC2OIF) {
        LL_GPTMRY_ClearFlag_CC2OVR(p_instance);         

        HAL_GPTMRY_IC_OverCaptureCallback(Handle, HAL_GPTMRY_CHANNEL_2); 
    }

    if (flag_status_masked & LL_GPTMRY_SR_CC2MIF) {
        LL_GPTMRY_ClearFlag_CC2(p_instance);    

        if (LL_GPTMRY_IC_GetActiveInput(p_instance, LL_GPTMRY_CAP_CMP_CH_2) == LL_GPTMRY_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRY_OC_DelayElapsedCallback(Handle, HAL_GPTMRY_CHANNEL_2);    
        } else {
            HAL_GPTMRY_IC_CaptureCallback(Handle, HAL_GPTMRY_CHANNEL_2);    
        }
    }

    /* CC3 */
    if (flag_status_masked & LL_GPTMRY_SR_CC3OIF) {
        LL_GPTMRY_ClearFlag_CC3OVR(p_instance);         

        HAL_GPTMRY_IC_OverCaptureCallback(Handle, HAL_GPTMRY_CHANNEL_3); 
    }

    if (flag_status_masked & LL_GPTMRY_SR_CC3MIF) {
        LL_GPTMRY_ClearFlag_CC3(p_instance);    

        if (LL_GPTMRY_IC_GetActiveInput(p_instance, LL_GPTMRY_CAP_CMP_CH_3) == LL_GPTMRY_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRY_OC_DelayElapsedCallback(Handle, HAL_GPTMRY_CHANNEL_3);    
        } else {
            HAL_GPTMRY_IC_CaptureCallback(Handle, HAL_GPTMRY_CHANNEL_3);    
        } 
    }
}

/**
  * @brief  Handle the GPTMRY Compare/Capture channel interrupt handler.
  * @param  Handle GPTMRY handle.
  * @return None
  */
void HAL_GPTMRY_CCx_IRQHandler(HAL_GPTMRY_HandleTypeDef *Handle, HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRY_CHANNEL_IDX(Channel));

    HAL_GPTMRY_PARAM_CHECK({
        if ((Handle == NULL)                            || 
            (!IS_GPTMRY_ALL_INSTANCE(Handle->Instance))  || 
            (!IS_GPTMRY_CHANNEL_IDX(Channel))) {
            return;
        }
    });
    
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    if ((LL_GPTMRY_IsActiveFlag_CCxOIF(p_instance, (uint32_t)Channel)) && 
        (LL_GPTMRY_IsEnabledIT_CxOIE(p_instance, (uint32_t)Channel))) {
        /* Clear flag */
        LL_GPTMRY_ClearFlag_CCxOIF(p_instance, (uint32_t)Channel);         

        /* Invoke callback */
        HAL_GPTMRY_IC_OverCaptureCallback(Handle, Channel); 
    }

    if ((LL_GPTMRY_IsActiveFlag_CCxMIF(p_instance, (uint32_t)Channel)) && 
        (LL_GPTMRY_IsEnabledIT_CxMIE(p_instance, (uint32_t)Channel))) {
        /* Clear flag */
        LL_GPTMRY_ClearFlag_CCxMIF(p_instance, (uint32_t)Channel);    

        /* Invoke callback */
        if (LL_GPTMRY_IC_GetActiveInput(p_instance, (uint32_t)Channel) == LL_GPTMRY_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRY_OC_DelayElapsedCallback(Handle, Channel);    
        } else {
            HAL_GPTMRY_IC_CaptureCallback(Handle, Channel);    
        }
    }
}


/**
  * @brief  GPTMRY update (reload) callback.
  * @param  Handle GPTMRY handle.
  * @return None
  */
__WEAK void HAL_GPTMRY_PeriodElapsedCallback(HAL_GPTMRY_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  GPTMRY overflow callback.
  * @param  Handle GPTMRY handle.
  * @return None
  */
__WEAK void HAL_GPTMRY_OverflowCallback(HAL_GPTMRY_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  GPTMRY trigger callback.
  * @param  Handle GPTMRY handle.
  * @return None
  */
__WEAK void HAL_GPTMRY_TriggerCallback(HAL_GPTMRY_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  GPTMRY channel compare callback.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return None
  */
__WEAK void HAL_GPTMRY_OC_DelayElapsedCallback(HAL_GPTMRY_HandleTypeDef *Handle, 
                                              HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    HAL_UNUSED(Handle);
    HAL_UNUSED(Channel);
}

/**
  * @brief  GPTMRY channel capture callback.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return None
  */
__WEAK void HAL_GPTMRY_IC_CaptureCallback(HAL_GPTMRY_HandleTypeDef *Handle, 
                                         HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    HAL_UNUSED(Handle);
    HAL_UNUSED(Channel);
}

/**
  * @brief  GPTMRY channel over-capture callback.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @return None
  */
__WEAK void HAL_GPTMRY_IC_OverCaptureCallback(HAL_GPTMRY_HandleTypeDef *Handle, 
                                             HAL_GPTMRY_ChannelIdxTypeDef Channel)
{
    HAL_UNUSED(Handle);
    HAL_UNUSED(Channel);
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/
/** @defgroup GPTMRY_HAL_Private_Functions GPTMRY HAL Private Functions
  * @{
  */

/**
  * @brief  Configure the GPTMRY time base from the init structure.
  * @param  Handle GPTMRY handle.
  * @param  pCfg pointer to a HAL_GPTMRY_BaseInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRY_BaseCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                       const HAL_GPTMRY_BaseInitTypeDef *pCfg)
{
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    /* Time base: counter value, period and prescaler */
    LL_GPTMRY_SetCounter(p_instance, 0UL);
    LL_GPTMRY_SetAutoReload(p_instance, pCfg->Period);
    LL_GPTMRY_SetPrescaler(p_instance, pCfg->Prescaler);

    /* Work mode */
    LL_GPTMRY_SetOnePulseMode(p_instance, (uint32_t)pCfg->WorkMode);

    switch (pCfg->CounterMode) {
        case HAL_GPTMRY_COUNTER_MODE_UP:
            LL_GPTMRY_SetAlignmentMode(p_instance, LL_GPTMRY_CTR_ALIGN_MODE_EDGE);
            LL_GPTMRY_SetDirection(p_instance, LL_GPTMRY_CNT_DIR_INC);
            break;

        case HAL_GPTMRY_COUNTER_MODE_DOWN:
            LL_GPTMRY_SetAlignmentMode(p_instance, LL_GPTMRY_CTR_ALIGN_MODE_EDGE);
            LL_GPTMRY_SetDirection(p_instance, LL_GPTMRY_CNT_DIR_DEC);
            break;

        case HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED1:
            LL_GPTMRY_SetAlignmentMode(p_instance, LL_GPTMRY_CTR_ALIGN_MODE_CENTER_1);
            break;

        case HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED2:
            LL_GPTMRY_SetAlignmentMode(p_instance, LL_GPTMRY_CTR_ALIGN_MODE_CENTER_2);
            break;

        case HAL_GPTMRY_COUNTER_MODE_CENTER_ALIGNED3:
            LL_GPTMRY_SetAlignmentMode(p_instance, LL_GPTMRY_CTR_ALIGN_MODE_CENTER_3);
            break;

        default:
            break;
    }

    /* Update event source and enable */
    LL_GPTMRY_SetUpdateSource(p_instance, (uint32_t)pCfg->UpdateSource);

    if (pCfg->UpdateEvent == HAL_GPTMRY_UPDATE_EVT_ASSERT) {
        LL_GPTMRY_DisableUpdateEvent(p_instance);
    } else if (pCfg->UpdateEvent == HAL_GPTMRY_UPDATE_EVT_RELEASE) {
        LL_GPTMRY_EnableUpdateEvent(p_instance);
    }

    /* Auto preload */
    HAL_FUNC_ALTER(pCfg->AutoReloadPreload, LL_GPTMRY_EnableAutoReload(p_instance),
                                            LL_GPTMRY_DisableAutoReload(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure one GPTMRY input capture channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @param  pCfg pointer to a HAL_GPTMRY_InputCapInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRY_InputCapCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                           HAL_GPTMRY_ChannelIdxTypeDef Channel, 
                                           const HAL_GPTMRY_InputCapInitTypeDef *pCfg)
{
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    LL_GPTMRY_IC_SetActiveInput(p_instance, Channel, (uint32_t)pCfg->ICSelection);
    LL_GPTMRY_IC_SetFilter(p_instance, Channel, (uint32_t)pCfg->ICFilter);
    LL_GPTMRY_IC_SetPrescaler(p_instance, Channel, (uint32_t)pCfg->ICPrescaler);
    LL_GPTMRY_IC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->ICPolarity);
    LL_GPTMRY_IC_SetInputSource(p_instance, Channel, (uint32_t)pCfg->ICTriggerSource);

    return HAL_OK;
}

/**
  * @brief  Configure one GPTMRY output compare channel.
  * @param  Handle GPTMRY handle.
  * @param  Channel GPTMRY channel.
  * @param  pCfg pointer to a HAL_GPTMRY_OutputCmpInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRY_OutputCmpCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                            HAL_GPTMRY_ChannelIdxTypeDef Channel, 
                                            const HAL_GPTMRY_OutputCmpInitTypeDef *pCfg)
{
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    LL_GPTMRY_IC_SetActiveInput(p_instance, Channel, LL_GPTMRY_CMP_CAP_MAP_OUTPUT);                           
    LL_GPTMRY_OC_SetChannelCompare(p_instance, Channel, pCfg->CompareValue);                                             
    LL_GPTMRY_OC_SetMode(p_instance, Channel, (uint32_t)pCfg->OCMode);          
    LL_GPTMRY_OC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->OCPolarity, LL_GPTMRY_CAP_CMP_OC);    
    LL_GPTMRY_OC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->OCNPolarity, LL_GPTMRY_CAP_CMP_OCN);          

    HAL_FUNC_ALTER(pCfg->CompareAutoReload,
                    LL_GPTMRY_OC_EnablePreload(p_instance, Channel),             
                    LL_GPTMRY_OC_DisablePreload(p_instance, Channel));           

    return HAL_OK;
}

/**
  * @brief  Configure the GPTMRY master
  * @param  Handle GPTMRY handle.
  * @param  pCfg pointer to a HAL_GPTMRY_MstInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRY_MstCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                      const HAL_GPTMRY_MstInitTypeDef *pCfg)
{
    GPTMRy_TypeDef *p_instance = Handle->Instance;
    const uint32_t trgo_ch_msk = pCfg->TRGOSelection;

    /* Master mode and TRGO width */
    LL_GPTMRY_SetTriggerOutput(p_instance, (uint32_t)pCfg->MasterMode);
    LL_GPTMRY_SetTrigOutputWidth(p_instance, pCfg->TRGOWidth);
    LL_GPTMRY_SetTrigCyclesWidth(p_instance, pCfg->TRGCCWidth); 

    if (trgo_ch_msk & HAL_GPTMRY_TRGI_OUT_SELECT_CH0_MASK) {
        LL_GPTMRY_EnableTriggerCH0(p_instance);
    } else {
        LL_GPTMRY_DisableTriggerCH0(p_instance);
    }

    if (trgo_ch_msk & HAL_GPTMRY_TRGI_OUT_SELECT_CH1_MASK) {
        LL_GPTMRY_EnableTriggerCH1(p_instance);
    } else {
        LL_GPTMRY_DisableTriggerCH1(p_instance);
    }

    if (trgo_ch_msk & HAL_GPTMRY_TRGI_OUT_SELECT_CH2_MASK) {
        LL_GPTMRY_EnableTriggerCH2(p_instance);
    } else {
        LL_GPTMRY_DisableTriggerCH2(p_instance);
    }

    if (trgo_ch_msk & HAL_GPTMRY_TRGI_OUT_SELECT_CH3_MASK) {
        LL_GPTMRY_EnableTriggerCH3(p_instance);
    } else {
        LL_GPTMRY_DisableTriggerCH3(p_instance);
    }

    return HAL_OK;
}


/**
  * @brief  Configure the GPTMRY slave mode and ETR input.
  * @param  Handle GPTMRY handle.
  * @param  pCfg pointer to a HAL_GPTMRY_SlvInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRY_SlvCfg(HAL_GPTMRY_HandleTypeDef *Handle, 
                                      const HAL_GPTMRY_SlvInitTypeDef *pCfg)
{
    GPTMRy_TypeDef *p_instance = Handle->Instance;

    LL_GPTMRY_SetTriggerInput(p_instance, (uint32_t)pCfg->InputTrigger);
    LL_GPTMRY_SetSlaveMode(p_instance, (uint32_t)pCfg->SlaveMode);

    /* External trigger (ETR) input */
    LL_GPTMRY_SetETRMode(p_instance, (uint32_t)pCfg->ExtClokMode);
    LL_GPTMRY_SetETREdgeMode(p_instance, (uint32_t)pCfg->TriggerPolarity);
    LL_GPTMRY_SetETRFilter(p_instance, (uint32_t)pCfg->TriggerFilter);

    return HAL_OK;
}

/**
  * @brief  Judge whether the slave mode of GPTMRY is enabled or not.
  * @param  Handle GPTMRY handle.
  * @return 0: Disabled, 1: Enabled
  */
__STATIC_FORCEINLINE uint32_t GPTMRY_IsSlvModeTrigEnabled(HAL_GPTMRY_HandleTypeDef *Handle)
{
    const uint32_t slv_mode = LL_GPTMRY_GetSlaveMode(Handle->Instance);
    return ((slv_mode == LL_GPTMRY_SLV_MODE_TRIG) || (slv_mode == LL_GPTMRY_SLV_MODE_RST_TRIG)) ? 1UL : 0UL;
}


/**
  * @}
  */

#endif /* HAL_GPTMRY_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */  
#endif /* GPTMRY */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

