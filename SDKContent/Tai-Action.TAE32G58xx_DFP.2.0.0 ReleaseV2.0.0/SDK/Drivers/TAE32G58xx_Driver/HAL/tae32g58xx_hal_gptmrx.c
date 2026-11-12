/**
  ******************************************************************************
  * @file    tae32g58xx_hal_gptmrx.c
  * @author  Tai-Action SD Team
  * @brief   GPTMRX HAL module driver (general purpose timer).
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

/** @defgroup GPTMRX_HAL GPTMRX HAL
  * @brief    GPTMRX HAL module driver.
  * @{
  */
#if defined(TMR0) || defined(TMR1) || defined(TMR2)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_GPTMRX_MODULE_ENABLED) && (HAL_GPTMRX_MODULE_ENABLED == 1)



/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup GPTMRX_HAL_Private_Macros GPTMRX HAL Private Macros
  * @brief    GPTMRX HAL Private Macros
  * @{
  */

/** @defgroup GPTMRX_HAL_PM_Discriminant GPTMRX HAL Discriminant
  * @brief    GPTMRX HAL Discriminant
  * @{
  */

#define IS_GPTMRX_ENABLE(__VAL__)                     (((__VAL__) == HAL_GPTMRX_FUNC_DISABLE) || \
                                                       ((__VAL__) == HAL_GPTMRX_FUNC_ENABLE))

#define IS_GPTMRX_WORK_MODE(__VAL__)                  (((__VAL__) == HAL_GPTMRX_WORK_MODE_CONTINUE) || \
                                                       ((__VAL__) == HAL_GPTMRX_WORK_MODE_SINGLE))

#define IS_GPTMRX_UPDATE_EVT_SRC(__VAL__)             (((__VAL__) == HAL_GPTMRX_UPDATE_EVT_SRC_OV_UG) || \
                                                       ((__VAL__) == HAL_GPTMRX_UPDATE_EVT_SRC_OV))

#define IS_GPTMRX_MST_MODE(__VAL__)                   (((__VAL__) == HAL_GPTMRX_MST_MODE_RESET)          || \
                                                       ((__VAL__) == HAL_GPTMRX_MST_MODE_ENABLE)         || \
                                                       ((__VAL__) == HAL_GPTMRX_MST_MODE_UPDATE)         || \
                                                       ((__VAL__) == HAL_GPTMRX_MST_MODE_CAP_CMP_EVT)    || \
                                                       ((__VAL__) == HAL_GPTMRX_MST_MODE_CMP_OUT0)       || \
                                                       ((__VAL__) == HAL_GPTMRX_MST_MODE_CMP_OUT1))

#define IS_GPTMRX_DZ_DIG_FIL_CLK_DIV(__VAL__)         (((__VAL__) == HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_1) || \
                                                       ((__VAL__) == HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_2) || \
                                                       ((__VAL__) == HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_4) || \
                                                       ((__VAL__) == HAL_GPTMRX_DZ_DIG_FIL_CLK_DIV_8))

#define IS_GPTMRX_CHANNEL_IDX(__VAL__)                (((__VAL__) == HAL_GPTMRX_CHANNEL_0) || \
                                                       ((__VAL__) == HAL_GPTMRX_CHANNEL_1))

#define IS_GPTMRX_CAP_POL(__VAL__)                    (((__VAL__) == HAL_GPTMRX_CAP_POL_CLOSE)   || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_POL_RISING)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_POL_FALLING) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_POL_BOTH_EDGE))

#define IS_GPTMRX_CAP_PRESCALER(__VAL__)              (((__VAL__) == HAL_GPTMRX_CAP_PRESCALER_1) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_PRESCALER_2) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_PRESCALER_4) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_PRESCALER_8))

#define IS_GPTMRX_CAP_INPUT_MAP(__VAL__)              (((__VAL__) == HAL_GPTMRX_CAP_INPUT_MAP_0) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_MAP_1) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_MAP_TRGI))

#define IS_GPTMRX_CAP_INPUT_SRC(__VAL__)              (((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN0)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN1)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN2)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN3)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN4)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN5)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN6)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN7)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN8)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN9)  || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN10) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN11) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN12) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN13) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN14) || \
                                                       ((__VAL__) == HAL_GPTMRX_CAP_INPUT_SRC_IN15))

#define IS_GPTMRX_CMP_POL(__VAL__)                    (((__VAL__) == HAL_GPTMRX_CMP_POL_HIGH) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_POL_LOW))

#define IS_GPTMRX_OC_MODE(__VAL__)                    (((__VAL__) == HAL_GPTMRX_CMP_MODE_FREEZE) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_ACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_INACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_TOGGLE) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_FORCE_INACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_FORCE_ACTIVE) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_PWM1) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_PWM2) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_RETRIG_OPM1) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_RETRIG_OPM2) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_COMB_PWM1) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_COMB_PWM2) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_ASYM_PWM1) || \
                                                       ((__VAL__) == HAL_GPTMRX_CMP_MODE_ASYM_PWM2))

#define IS_GPTMRX_SLV_MODE(__VAL__)                   (((__VAL__) == HAL_GPTMRX_SLV_MODE_DIS) || \
                                                       ((__VAL__) == HAL_GPTMRX_SLV_MODE_RST) || \
                                                       ((__VAL__) == HAL_GPTMRX_SLV_MODE_GATING) || \
                                                       ((__VAL__) == HAL_GPTMRX_SLV_MODE_TRIG) || \
                                                       ((__VAL__) == HAL_GPTMRX_SLV_MODE_EXTCLK) || \
                                                       ((__VAL__) == HAL_GPTMRX_SLV_MODE_RST_TRIG) || \
                                                       ((__VAL__) == HAL_GPTMRX_SLV_MODE_RST_GATING))

#define IS_GPTMRX_TI0_IN_SRC(__VAL__)                 (((__VAL__) == HAL_GPTMRX_TI0_IN_SRC_CH0)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TI0_IN_SRC_CH0_1_XOR))

#define IS_GPTMRX_BRK_POL(__VAL__)                    (((__VAL__) == HAL_GPTMRX_BRK_POL_HIGH) || \
                                                       ((__VAL__) == HAL_GPTMRX_BRK_POL_LOW))

#define IS_GPTMRX_RUN_OFF_STA(__VAL__)                (((__VAL__) == HAL_GPTMRX_RUN_OFF_STA_COMP_CLOSE) || \
                                                       ((__VAL__) == HAL_GPTMRX_RUN_OFF_STA_COMP_IVD))

#define IS_GPTMRX_IDLE_OFF_STA(__VAL__)               (((__VAL__) == HAL_GPTMRX_IDLE_OFF_STA_COMP_CLOSE) || \
                                                       ((__VAL__) == HAL_GPTMRX_IDLE_OFF_STA_COMP_IDLE))

#define IS_GPTMRX_TRIG(__VAL__)                       (((__VAL__) == HAL_GPTMRX_TRIG_ITR0)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR1)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR2)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR3)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR4)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR5)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR6)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR7)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR8)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR9)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR10) || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR11) || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR12) || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR13) || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR14) || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_ITR15) || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_CH0_FE) || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_CH0_F)  || \
                                                       ((__VAL__) == HAL_GPTMRX_TRIG_CH1_F))

#define IS_GPTMRX_EVENTSOURCE(__VAL__)                (((__VAL__) == HAL_GPTMRX_EVENTSOURCE_UPDATE) || \
                                                       ((__VAL__) == HAL_GPTMRX_EVENTSOURCE_TRIG)   || \
                                                       ((__VAL__) == HAL_GPTMRX_EVENTSOURCE_BRK0)   || \
                                                       ((__VAL__) == HAL_GPTMRX_EVENTSOURCE_CC0)    || \
                                                       ((__VAL__) == HAL_GPTMRX_EVENTSOURCE_CC1))

/**
  * @}
  */ /* GPTMRX_HAL_PM_Discriminant */


/**
  * @}
  */ /* GPTMRX_HAL_EF_Configuration */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup GPTMRX_HAL_Private_Functions GPTMRX HAL Private Functions
  * @{
  */
static HAL_StatusTypeDef GPTMRX_BaseCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                       const HAL_GPTMRX_BaseInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRX_InputCapCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                           HAL_GPTMRX_ChannelIdxTypeDef Channel, 
                                           const HAL_GPTMRX_InputCapInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRX_OutputCmpCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                            HAL_GPTMRX_ChannelIdxTypeDef Channel, 
                                            const HAL_GPTMRX_OutputCmpInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRX_MstCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                      const HAL_GPTMRX_MstInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRX_SlvCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                      const HAL_GPTMRX_SlvInitTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRX_BrkDzCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                        const HAL_GPTMRX_BreakDeadTimeConfigTypeDef *pCfg);

static HAL_StatusTypeDef GPTMRX_BrkInCfg(HAL_GPTMRX_HandleTypeDef *Handle,
                                        HAL_GPTMRX_BreakInputTypeDef BreakInput,
                                        const HAL_GPTMRX_BreakInputConfigTypeDef *pCfg);

__STATIC_FORCEINLINE uint32_t GPTMRX_IsSlvModeTrigEnabled(HAL_GPTMRX_HandleTypeDef *Handle);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup GPTMRX_HAL_Exported_Functions GPTMRX HAL Exported Functions
  * @{
  */

/** @defgroup GPTMRX_HAL_EF_Initialization GPTMRX HAL Initialization
  * @{
  */

/**
  * @brief  Initialize the GPTMRX peripheral according to the specified parameters
  *         and create the associated handle.
  * @param  Handle GPTMRX handle.
  * @param  GPTMRx GPTMRX instance.
  * @param  pInit  pointer to a HAL_GPTMRX_BaseInitTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_Base_Init(HAL_GPTMRX_HandleTypeDef *Handle, 
                                      GPTMRx_TypeDef *GPTMRx,
                                      const HAL_GPTMRX_BaseInitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));
    ASSERT_FUNC_PARAM(pInit != NULL);

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(GPTMRx)) || (pInit == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_PARAM(IS_GPTMRX_WORK_MODE(pInit->WorkMode));
    ASSERT_FUNC_PARAM(IS_GPTMRX_UPDATE_EVT_SRC(pInit->UpdateSource));
    ASSERT_FUNC_PARAM(IS_GPTMRX_DZ_DIG_FIL_CLK_DIV(pInit->DzFilterClockDivision));

    Handle->State = HAL_GPTMRX_STATE_RESET;

    /* Bind the instance passed by the caller */
    Handle->Instance = GPTMRx;

    /* Init the low level hardware: CLOCK, NVIC */
    HAL_GPTMRX_Base_MspInit(Handle);

    /* Configure the time base */
    (void) GPTMRX_BaseCfg(Handle, pInit);

    Handle->LastErrorCodes = HAL_GPTMRX_ERROR_NONE;
    Handle->State          = HAL_GPTMRX_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  De-initialize the GPTMRX peripheral.
  * @param  Handle GPTMRX handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_Base_DeInit(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    GPTMRx_TypeDef *p_instance = Handle->Instance;

    Handle->State = HAL_GPTMRX_STATE_BUSY;

    /* Stop the counter and its interrupts */
    LL_GPTMRX_DisableCounter(p_instance);

    /* Disable both break inputs */
    LL_GPTMRX_DisableBreak0(p_instance);

    /* Disable all capture/compare channels */
    LL_GPTMRX_DisableIT(p_instance, LL_GPTMRX_IER_IT_EN_MSK);

    LL_GPTMRX_CC_DisableAllChannel(p_instance);

    /* De-init the low level hardware: GPIO, CLOCK, NVIC */
    HAL_GPTMRX_Base_MspDeInit(Handle);

    Handle->LastErrorCodes = HAL_GPTMRX_ERROR_NONE;
    Handle->State          = HAL_GPTMRX_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the GPTMRX MSP.
  * @note   This function should not be modified. When the application needs its
  *         own implementation, it may override this weak function in the user file.
  * @param  Handle GPTMRX handle.
  * @return None
  */
__WEAK void HAL_GPTMRX_Base_MspInit(HAL_GPTMRX_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  De-initialize the GPTMRX MSP.
  * @param  Handle GPTMRX handle.
  * @return None
  */
__WEAK void HAL_GPTMRX_Base_MspDeInit(HAL_GPTMRX_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  Initialize the GPTMRX IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval None
  */
__WEAK void HAL_GPTMRX_IoInit(GPTMRx_TypeDef *GPTMRx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(GPTMRx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_GPTMRX_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the GPTMRX IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  GPTMRx Specifies GPTMRX peripheral
  * @retval None
  */
__WEAK void HAL_GPTMRX_IoDeInit(GPTMRx_TypeDef *GPTMRx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(GPTMRx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_GPTMRX_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */

/** @defgroup GPTMRX_HAL_EF_Configuration GPTMRX HAL Configuration
  * @{
  */

/**
  * @brief  Configure one GPTMRX input capture channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @param  pCfg pointer to the input capture configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_IC_Init(HAL_GPTMRX_HandleTypeDef *Handle, 
                                    HAL_GPTMRX_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRX_InputCapInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_CAP_POL(pCfg->ICPolarity));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CAP_INPUT_MAP(pCfg->ICSelection));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CAP_PRESCALER(pCfg->ICPrescaler));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CAP_INPUT_SRC(pCfg->ICTriggerSource));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRX_InputCapCfg(Handle, Channel, pCfg);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure one GPTMRX output compare channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @param  pCfg pointer to the output compare configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OC_Init(HAL_GPTMRX_HandleTypeDef *Handle, 
                                    HAL_GPTMRX_ChannelIdxTypeDef Channel,
                                    const HAL_GPTMRX_OutputCmpInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_OC_MODE(pCfg->OCMode));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CMP_POL(pCfg->OCPolarity));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CMP_POL(pCfg->OCNPolarity));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRX_OutputCmpCfg(Handle, Channel, pCfg);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the GPTMRX Master mode
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to the master configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_InitMaster(HAL_GPTMRX_HandleTypeDef *Handle,
                                       const HAL_GPTMRX_MstInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_MST_MODE(pCfg->MasterMode));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRX_MstCfg(Handle, pCfg);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the GPTMRX slave mode and ETR input.
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to the slave/ETR configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_InitSlave(HAL_GPTMRX_HandleTypeDef *Handle,
                                      const HAL_GPTMRX_SlvInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_SLV_MODE(pCfg->SlaveMode));
    ASSERT_FUNC_PARAM(IS_GPTMRX_TRIG(pCfg->InputTrigger));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRX_SlvCfg(Handle, pCfg);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the GPTMRX break and dead-time generator.
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to the break/dead-time configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_ConfigBreakDeadTime(HAL_GPTMRX_HandleTypeDef *Handle,
                                                const HAL_GPTMRX_BreakDeadTimeConfigTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_BRK_POL(pCfg->Break0Polarity));
    ASSERT_FUNC_PARAM(IS_GPTMRX_RUN_OFF_STA(pCfg->OffStateRunMode));
    ASSERT_FUNC_PARAM(IS_GPTMRX_IDLE_OFF_STA(pCfg->OffStateIdleMode));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRX_BrkDzCfg(Handle, pCfg);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the GPTMRX break inputs and dead-time generator.
  * @param  Handle GPTMRX handle.
  * @param  BreakInput A Break input
  * @param  pCfg pointer to the break input configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_ConfigBreakInput(HAL_GPTMRX_HandleTypeDef *Handle,
                                             HAL_GPTMRX_BreakInputTypeDef BreakInput,
                                             const HAL_GPTMRX_BreakInputConfigTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK; 

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = GPTMRX_BrkInCfg(Handle, BreakInput, pCfg);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return ret;

}

/**
  * @brief  Generate a software event of the GPTMRX.
  * @param  Handle GPTMRX handle.
  * @param  Source TI0 input source
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_TI0InputSourceConfig(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_TI0InSrcTypeDef Source)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_TI0_IN_SRC(Source));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (!IS_GPTMRX_TI0_IN_SRC(Source))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_SetTI0InputSource(Handle->Instance, (uint32_t)Source);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return HAL_OK;
}


/**
  * @}
  */

/** @defgroup GPTMRX_HAL_EF_IO_Operation GPTMRX HAL IO Operation
  * @{
  */
/**
  * @brief  Start the GPTMRX time base (polling mode).
  * @param  Handle GPTMRX handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_Base_Start(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRX_EnableCounter(Handle->Instance);
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Stop the GPTMRX time base (polling mode).
  * @param  Handle GPTMRX handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_Base_Stop(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_DisableCounter(Handle->Instance);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the GPTMRX time base in interrupt mode.
  * @param  Handle GPTMRX handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_Base_Start_IT(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_EnableIT_UPDATE(Handle->Instance);

    if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRX_EnableCounter(Handle->Instance);
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the GPTMRX time base in interrupt mode.
  * @param  Handle GPTMRX handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_Base_Stop_IT(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_DisableIT_UPDATE(Handle->Instance);
    LL_GPTMRX_DisableCounter(Handle->Instance);

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the output compare of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OC_Start(HAL_GPTMRX_HandleTypeDef *Handle, 
                                     HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_CC_EnableChannel(p_instance, (uint32_t)Channel);
    LL_GPTMRX_EnableAllOutputs(p_instance);

    if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRX_EnableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the output compare of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OC_Stop(HAL_GPTMRX_HandleTypeDef *Handle, 
                                    HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_CC_DisableChannel(p_instance, (uint32_t)Channel); 

    if (LL_GPTMRX_CC_IsAllChannelDisabled(p_instance)) {
        LL_GPTMRX_DisableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Start the output compare interrupt of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OC_StartIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_EnableIT_CxMIE(p_instance, (uint32_t)Channel);
    LL_GPTMRX_CC_EnableChannel(p_instance, (uint32_t)Channel);
    LL_GPTMRX_EnableAllOutputs(p_instance);

    if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
        LL_GPTMRX_EnableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the output compare interrupt of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OC_StopIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_GPTMRX_DisableIT_CxMIE(p_instance, (uint32_t)Channel);
    LL_GPTMRX_CC_DisableChannel(p_instance, (uint32_t)Channel);

    if (LL_GPTMRX_CC_IsAllChannelDisabled(p_instance)) {
        LL_GPTMRX_DisableCounter(p_instance);
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the output compare of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OCN_Start(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0: 
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0N); 
            break;
        case HAL_GPTMRX_CHANNEL_1: 
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1N); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        LL_GPTMRX_EnableAllOutputs(p_instance);

        if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
            LL_GPTMRX_EnableCounter(p_instance);
        }      
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the output compare of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OCN_Stop(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0: 
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0N); 
            break;
        case HAL_GPTMRX_CHANNEL_1: 
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1N); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_GPTMRX_CC_IsAllChannelDisabled(p_instance)) {
            LL_GPTMRX_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the output compare interrupt of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OCN_StartIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0:
            LL_GPTMRX_EnableIT_CC0(p_instance);
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0N);
            break;
        case HAL_GPTMRX_CHANNEL_1:
            LL_GPTMRX_EnableIT_CC1(p_instance);
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1N);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        LL_GPTMRX_EnableAllOutputs(p_instance);

        if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
            LL_GPTMRX_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the output compare interrupt of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_OCN_StopIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0:
            LL_GPTMRX_DisableIT_CC0(p_instance);
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0N);
            break;
        case HAL_GPTMRX_CHANNEL_1:
            LL_GPTMRX_DisableIT_CC1(p_instance);
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1N);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_GPTMRX_CC_IsAllChannelDisabled(p_instance)) {
            LL_GPTMRX_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the input capture of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_IC_Start(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0: 
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0); 
            break;
        case HAL_GPTMRX_CHANNEL_1: 
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
            LL_GPTMRX_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the input capture of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_IC_Stop(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0: 
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0); 
            break;
        case HAL_GPTMRX_CHANNEL_1: 
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_GPTMRX_CC_IsAllChannelDisabled(p_instance)) {
            LL_GPTMRX_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the input capture interrupt of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_IC_StartIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0:
            LL_GPTMRX_EnableIT_CC0(p_instance);
            LL_GPTMRX_EnableIT_CC0OVR(p_instance);
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0);
            break;
        case HAL_GPTMRX_CHANNEL_1:
            LL_GPTMRX_EnableIT_CC1(p_instance);
            LL_GPTMRX_EnableIT_CC1OVR(p_instance);
            LL_GPTMRX_CC_EnableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (!GPTMRX_IsSlvModeTrigEnabled(Handle)) {
            LL_GPTMRX_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the input capture interrupt of one channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_IC_StopIT(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_GPTMRX_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_GPTMRX_CHANNEL_0:
            LL_GPTMRX_DisableIT_CC0(p_instance);
            LL_GPTMRX_DisableIT_CC0OVR(p_instance);
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_0);
            break;
        case HAL_GPTMRX_CHANNEL_1:
            LL_GPTMRX_DisableIT_CC1(p_instance);
            LL_GPTMRX_DisableIT_CC1OVR(p_instance);
            LL_GPTMRX_CC_DisableChannel(p_instance, LL_GPTMRX_CAP_CMP_CH_1);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_GPTMRX_CC_IsAllChannelDisabled(p_instance)) {
            LL_GPTMRX_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Enable the module level interrupts selected by ITMask.
  * @param  Handle GPTMRX handle.
  * @param  ITMask interrupts to enable, value of @ref HAL_GPTMRX_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_InterruptRequestEnable(HAL_GPTMRX_HandleTypeDef *Handle, 
                                                   HAL_GPTMRX_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_GPTMRX_EnableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Disable the module level interrupts selected by ITMask.
  * @param  Handle GPTMRX handle.
  * @param  ITMask interrupts to disable, value of @ref HAL_GPTMRX_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_InterruptRequestDisable(HAL_GPTMRX_HandleTypeDef *Handle, 
                                                    HAL_GPTMRX_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_GPTMRX_DisableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Generate a software event of the GPTMRX.
  * @param  Handle GPTMRX handle.
  * @param  EventSource event to generate
  * @return HAL status
  */
HAL_StatusTypeDef HAL_GPTMRX_GenerateEvent(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_EvtSrcTypeDef EventSource)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_EVENTSOURCE(EventSource));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (!IS_GPTMRX_EVENTSOURCE(EventSource))) {
            return HAL_INVALID;
        }
    });

    volatile HAL_StatusTypeDef ret = HAL_OK;
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE);

    HAL_GPTMRX_PARAM_UPDATE(Handle->State, HAL_GPTMRX_STATE_CONFIGURABLE, HAL_GPTMRX_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (EventSource) {
        case HAL_GPTMRX_EVENTSOURCE_UPDATE:
            LL_GPTMRX_GenerateEvent_UPDATE(p_instance);
            break;

        case HAL_GPTMRX_EVENTSOURCE_TRIG:
            LL_GPTMRX_GenerateEvent_TRIG(p_instance);
            break;

        case HAL_GPTMRX_EVENTSOURCE_BRK0:
            LL_GPTMRX_GenerateEvent_BRK0(p_instance);
            break;

        case HAL_GPTMRX_EVENTSOURCE_CC0:
            LL_GPTMRX_GenerateEvent_CC0(p_instance);
            break;

        case HAL_GPTMRX_EVENTSOURCE_CC1:
            LL_GPTMRX_GenerateEvent_CC1(p_instance);
            break;

        default:
            ret = HAL_INVALID;
            break;
    }

    Handle->State = HAL_GPTMRX_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Read the captured value for an input channel of timer.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @retval Captured value
  */
uint16_t HAL_GPTMRX_ReadCapturedValue(const HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance)) || (Channel >= HAL_GPTMRX_CHANNEL_NUMS)) {
            return HAL_INVALID;
        }
    });

    return (uint16_t)(LL_GPTMRX_IC_GetChannelCompare(Handle->Instance, (uint32_t)Channel));
}

/**
  * @brief  Read the counter value at runtime.
  * @param  Handle GPTMRX handle.
  * @retval the timer counter register.
  */
uint16_t HAL_GPTMRX_ReadCounter(const HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    return (uint16_t)(LL_GPTMRX_GetCounter(Handle->Instance));
}

/**
  * @}
  */

/** @defgroup GPTMRX_HAL_EF_IRQ_Handler GPTMRX HAL IRQ Handler and Callbacks
  * @{
  */

/**
  * @brief  Handle the GPTMRX Break interrupt request.
  * @param  Handle GPTMRX handle.
  * @return None
  */
void HAL_GPTMRX_BRK_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    GPTMRx_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_GPTMRX_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_GPTMRX_GetAllITPending(p_instance) & LL_GPTMRX_SR_BRK_IT_FLAG_MSK;

    /* Break interrupts (BK0 / BK1 / system fault) */
    if (int_en & LL_GPTMRX_IER_BIE) {
        if (int_pending & LL_GPTMRX_SR_SBIF) {
            LL_GPTMRX_ClearFlag_SYSBRK(p_instance);
        }

        if (int_pending & LL_GPTMRX_SR_B0IF) {
            LL_GPTMRX_ClearFlag_BRK0(p_instance);
        }

        HAL_GPTMRX_BreakCallback(Handle, int_pending);
    }
}

/**
  * @brief  Handle the GPTMRX update event interrupt handler.
  * @param  Handle GPTMRX handle.
  * @return None
  */
void HAL_GPTMRX_UPD_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    GPTMRx_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_GPTMRX_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_GPTMRX_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers OVIF/UIF bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_GPTMRX_SR_UPD_IT_FLAG_MSK; 

    /* Update interrupt */
    if ((flag_status_masked & LL_GPTMRX_SR_UIF)) {
        LL_GPTMRX_ClearFlag_UPDATE(p_instance);

        HAL_GPTMRX_PeriodElapsedCallback(Handle);
    }

    /* Overflow interrupt */
    if ((flag_status_masked & LL_GPTMRX_SR_OVIF)) {
        LL_GPTMRX_ClearFlag_OVR(p_instance);

        HAL_GPTMRX_OverflowCallback(Handle);
    }
}

/**
  * @brief  Handle the GPTMRX trigger interrupt handler.
  * @param  Handle GPTMRX handle.
  * @return None
  */
void HAL_GPTMRX_TRG_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    GPTMRx_TypeDef *p_instance = Handle->Instance;

    /* Trigger interrupt */
    if ((LL_GPTMRX_IsEnabledIT_TRIG(p_instance) != 0UL) && 
        (LL_GPTMRX_IsActiveFlag_TRIG(p_instance) != 0UL)) {
        /* Clear flag */
        LL_GPTMRX_ClearFlag_TRIG(p_instance);

        /* Invoke callback */
        HAL_GPTMRX_TriggerCallback(Handle);
    }
}

/**
  * @brief  Handle the GPTMRX Compare/Capture interrupt handler.
  * @param  Handle GPTMRX handle.
  * @return None
  */
void HAL_GPTMRX_CC_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });
    
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_GPTMRX_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_GPTMRX_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers CCx bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_GPTMRX_SR_CC_IT_FLAG_MSK; 

    /* CC0 */
    if (flag_status_masked & LL_GPTMRX_SR_CC0OIF) {
        LL_GPTMRX_ClearFlag_CC0OVR(p_instance);         

        HAL_GPTMRX_IC_OverCaptureCallback(Handle, HAL_GPTMRX_CHANNEL_0); 
    }

    if (flag_status_masked & LL_GPTMRX_SR_CC0MIF) {
        LL_GPTMRX_ClearFlag_CC0(p_instance);    

        if (LL_GPTMRX_IC_GetActiveInput(p_instance, LL_GPTMRX_CAP_CMP_CH_0) == LL_GPTMRX_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRX_OC_DelayElapsedCallback(Handle, HAL_GPTMRX_CHANNEL_0);    
        } else {
            HAL_GPTMRX_IC_CaptureCallback(Handle, HAL_GPTMRX_CHANNEL_0);    
        }
    }

    /* CC1 */
    if (flag_status_masked & LL_GPTMRX_SR_CC1OIF) {
        LL_GPTMRX_ClearFlag_CC1OVR(p_instance);         

        HAL_GPTMRX_IC_OverCaptureCallback(Handle, HAL_GPTMRX_CHANNEL_1); 
    }

    if (flag_status_masked & LL_GPTMRX_SR_CC1MIF) {
        LL_GPTMRX_ClearFlag_CC1(p_instance);    

        if (LL_GPTMRX_IC_GetActiveInput(p_instance, LL_GPTMRX_CAP_CMP_CH_1) == LL_GPTMRX_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRX_OC_DelayElapsedCallback(Handle, HAL_GPTMRX_CHANNEL_1);    
        } else {
            HAL_GPTMRX_IC_CaptureCallback(Handle, HAL_GPTMRX_CHANNEL_1);    
        }
    }
}

/**
  * @brief  Handle the GPTMRX Compare/Capture channel interrupt handler.
  * @param  Handle GPTMRX handle.
  * @return None
  */
void HAL_GPTMRX_CCx_IRQHandler(HAL_GPTMRX_HandleTypeDef *Handle, HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_GPTMRX_CHANNEL_IDX(Channel));

    HAL_GPTMRX_PARAM_CHECK({
        if ((Handle == NULL)                            || 
            (!IS_GPTMRX_ALL_INSTANCE(Handle->Instance))  || 
            (!IS_GPTMRX_CHANNEL_IDX(Channel))) {
            return;
        }
    });
    
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    if ((LL_GPTMRX_IsActiveFlag_CCxOIF(p_instance, Channel)) && 
        (LL_GPTMRX_IsEnabledIT_CxOIE(p_instance, Channel))) {
        /* Clear flag */
        LL_GPTMRX_ClearFlag_CCxOIF(p_instance, Channel);         

        /* Invoke callback */
        HAL_GPTMRX_IC_OverCaptureCallback(Handle, Channel); 
    }

    if ((LL_GPTMRX_IsActiveFlag_CCxMIF(p_instance, Channel)) && 
        (LL_GPTMRX_IsEnabledIT_CxMIE(p_instance, Channel))) {
        /* Clear flag */
        LL_GPTMRX_ClearFlag_CCxMIF(p_instance, Channel);    

        /* Invoke callback */
        if (LL_GPTMRX_IC_GetActiveInput(p_instance, (uint32_t)Channel) == LL_GPTMRX_CMP_CAP_MAP_OUTPUT) {
            HAL_GPTMRX_OC_DelayElapsedCallback(Handle, Channel);    
        } else {
            HAL_GPTMRX_IC_CaptureCallback(Handle, Channel);    
        } 
    }
}


/**
  * @brief  GPTMRX update (reload) callback.
  * @param  Handle GPTMRX handle.
  * @return None
  */
__WEAK void HAL_GPTMRX_PeriodElapsedCallback(HAL_GPTMRX_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  GPTMRX overflow callback.
  * @param  Handle GPTMRX handle.
  * @return None
  */
__WEAK void HAL_GPTMRX_OverflowCallback(HAL_GPTMRX_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  GPTMRX trigger callback.
  * @param  Handle GPTMRX handle.
  * @return None
  */
__WEAK void HAL_GPTMRX_TriggerCallback(HAL_GPTMRX_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  GPTMRX break callback.
  * @param  Handle GPTMRX handle.
  * @return None
  */
__WEAK void HAL_GPTMRX_BreakCallback(HAL_GPTMRX_HandleTypeDef *Handle, 
                                     HAL_GPTMRX_ITPendingMskTypeDef BreakEvent)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  GPTMRX channel compare callback.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return None
  */
__WEAK void HAL_GPTMRX_OC_DelayElapsedCallback(HAL_GPTMRX_HandleTypeDef *Handle, 
                                               HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    HAL_UNUSED(Handle);
    HAL_UNUSED(Channel);
}
/**
  * @brief  GPTMRX channel capture callback.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return None
  */
__WEAK void HAL_GPTMRX_IC_CaptureCallback(HAL_GPTMRX_HandleTypeDef *Handle, 
                                          HAL_GPTMRX_ChannelIdxTypeDef Channel)
{
    HAL_UNUSED(Handle);
    HAL_UNUSED(Channel);
}

/**
  * @brief  GPTMRX channel over-capture callback.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @return None
  */
__WEAK void HAL_GPTMRX_IC_OverCaptureCallback(HAL_GPTMRX_HandleTypeDef *Handle, 
                                              HAL_GPTMRX_ChannelIdxTypeDef Channel)
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
/** @defgroup GPTMRX_HAL_Private_Functions GPTMRX HAL Private Functions
  * @{
  */

/**
  * @brief  Configure the GPTMRX time base from the init structure.
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to a HAL_GPTMRX_BaseInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRX_BaseCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                       const HAL_GPTMRX_BaseInitTypeDef *pCfg)
{
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    /* Time base: counter value, period and prescaler (all 16-bit) */
    LL_GPTMRX_SetCounter(p_instance, 0UL);
    LL_GPTMRX_SetAutoReload(p_instance, pCfg->Period);
    LL_GPTMRX_SetPrescaler(p_instance, pCfg->Prescaler);

    /* Work mode */
    LL_GPTMRX_SetOnePulseMode(p_instance, (uint32_t)pCfg->WorkMode);

    /* Advance configuration */
    LL_GPTMRX_SetRepetitionCounter(p_instance, pCfg->RepetitionCounter);
    LL_GPTMRX_SetDzDigFilClkDiv(p_instance, (uint32_t)pCfg->DzFilterClockDivision);

    /* Update event source and enable */
    LL_GPTMRX_SetUpdateSource(p_instance, (uint32_t)pCfg->UpdateSource);

    if (pCfg->UpdateEvent == HAL_GPTMRX_UPDATE_EVT_ASSERT) {
        LL_GPTMRX_DisableUpdateEvent(p_instance);
    } else if (pCfg->UpdateEvent == HAL_GPTMRX_UPDATE_EVT_RELEASE) {
        LL_GPTMRX_EnableUpdateEvent(p_instance);
    }

    /* Auto preload */
    HAL_FUNC_ALTER(pCfg->AutoReloadPreload, LL_GPTMRX_EnableAutoReload(p_instance),
                                            LL_GPTMRX_DisableAutoReload(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure one GPTMRX input capture channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @param  pCfg pointer to a HAL_GPTMRX_InputCapInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRX_InputCapCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                           HAL_GPTMRX_ChannelIdxTypeDef Channel, 
                                           const HAL_GPTMRX_InputCapInitTypeDef *pCfg)
{
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    LL_GPTMRX_IC_SetActiveInput(p_instance, Channel, (uint32_t)pCfg->ICSelection);
    LL_GPTMRX_IC_SetFilter(p_instance, Channel, (uint32_t)pCfg->ICFilter);
    LL_GPTMRX_IC_SetPrescaler(p_instance, Channel, (uint32_t)pCfg->ICPrescaler);
    LL_GPTMRX_IC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->ICPolarity);
    LL_GPTMRX_IC_SetInputSource(p_instance, Channel, (uint32_t)pCfg->ICTriggerSource);

    return HAL_OK;
}

/**
  * @brief  Configure one GPTMRX output compare channel.
  * @param  Handle GPTMRX handle.
  * @param  Channel GPTMRX channel.
  * @param  pCfg pointer to a HAL_GPTMRX_OutputCmpInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRX_OutputCmpCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                            HAL_GPTMRX_ChannelIdxTypeDef Channel, 
                                            const HAL_GPTMRX_OutputCmpInitTypeDef *pCfg)
{
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    LL_GPTMRX_IC_SetActiveInput(p_instance, Channel, LL_GPTMRX_CMP_CAP_MAP_OUTPUT);                           
    LL_GPTMRX_OC_SetChannelCompare(p_instance, Channel, pCfg->CompareValue);
    LL_GPTMRX_OC_SetMode(p_instance, Channel, (uint32_t)pCfg->OCMode);          
    LL_GPTMRX_OC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->OCPolarity, LL_GPTMRX_CAP_CMP_OC);    
    LL_GPTMRX_OC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->OCNPolarity, LL_GPTMRX_CAP_CMP_OCN);          

    LL_GPTMRX_OC_SetIdleState(p_instance, Channel, (uint32_t)pCfg->OCIdleState);    
    LL_GPTMRX_OC_SetIdleState(p_instance, (((uint32_t)Channel) % LL_GPTMRX_CAP_CMP_CH_NUMS) + LL_GPTMRX_CAP_CMP_CH_0N, (uint32_t)pCfg->OCNIdleState);  
                    
    HAL_FUNC_ALTER(pCfg->CompareAutoReload,
                    LL_GPTMRX_OC_EnablePreload(p_instance, Channel),             
                    LL_GPTMRX_OC_DisablePreload(p_instance, Channel));           

    return HAL_OK;
}

/**
  * @brief  Configure the GPTMRX master
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to a HAL_GPTMRX_MstInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRX_MstCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                      const HAL_GPTMRX_MstInitTypeDef *pCfg)
{
    GPTMRx_TypeDef *p_instance = Handle->Instance;
    const uint32_t trgo_ch_msk = pCfg->TRGOSelection;

    /* Master mode and TRGO width */
    LL_GPTMRX_SetTriggerOutput(p_instance, (uint32_t)pCfg->MasterMode);
    LL_GPTMRX_SetTrigOutputWidth(p_instance, pCfg->TRGOWidth);
    LL_GPTMRX_SetTrigCyclesWidth(p_instance, pCfg->TRGCCWidth); 

    if (trgo_ch_msk & HAL_GPTMRX_TRGI_OUT_SELECT_CH0_MASK) {
        LL_GPTMRX_EnableTriggerCH0(p_instance);
    } else {
        LL_GPTMRX_DisableTriggerCH0(p_instance);
    }

    if (trgo_ch_msk & HAL_GPTMRX_TRGI_OUT_SELECT_CH1_MASK) {
        LL_GPTMRX_EnableTriggerCH1(p_instance);
    } else {
        LL_GPTMRX_DisableTriggerCH1(p_instance);
    }

    return HAL_OK;
}


/**
  * @brief  Configure the GPTMRX slave mode and ETR input.
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to a HAL_GPTMRX_SlvInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRX_SlvCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                      const HAL_GPTMRX_SlvInitTypeDef *pCfg)
{
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    LL_GPTMRX_SetTriggerInput(p_instance, (uint32_t)pCfg->InputTrigger);
    LL_GPTMRX_SetSlaveMode(p_instance, (uint32_t)pCfg->SlaveMode);

    HAL_FUNC_ALTER(pCfg->FastSync,
                  LL_GPTMRX_EnableMstSlvFastSync(p_instance),
                  LL_GPTMRX_DisableMstSlvFastSync(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure the GPTMRX break state, dead-time and output off-state.
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to a HAL_GPTMRX_BreakDeadTimeConfigTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRX_BrkDzCfg(HAL_GPTMRX_HandleTypeDef *Handle, 
                                        const HAL_GPTMRX_BreakDeadTimeConfigTypeDef *pCfg)
{
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    /* Break 0 */
    LL_GPTMRX_SetBreak0Polarity(p_instance, (uint32_t)pCfg->Break0Polarity);
    LL_GPTMRX_SetBreak0Filter(p_instance, pCfg->Break0Filter);
    HAL_FUNC_ALTER(pCfg->Break0State,
                  LL_GPTMRX_EnableBreak0(p_instance),
                  LL_GPTMRX_DisableBreak0(p_instance));

    /* Break interrupt */
    HAL_FUNC_ALTER(pCfg->BreakIT,
                  LL_GPTMRX_EnableIT_BRK(p_instance),
                  LL_GPTMRX_DisableIT_BRK(p_instance));

    /* Dead-time generator */
    LL_GPTMRX_SetFallingDeadTime(p_instance, pCfg->DeadTime);

    LL_GPTMRX_SetRunModeOffState(p_instance, (uint32_t)pCfg->OffStateRunMode);
    LL_GPTMRX_SetIdleModeOffState(p_instance, (uint32_t)pCfg->OffStateIdleMode);

    HAL_FUNC_ALTER(pCfg->AutomaticOutput,
                  LL_GPTMRX_EnableAutomaticOutput(p_instance),
                  LL_GPTMRX_DisableAutomaticOutput(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure the GPTMRX break inputs.
  * @param  Handle GPTMRX handle.
  * @param  pCfg pointer to a HAL_GPTMRX_BreakDeadTimeConfigTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef GPTMRX_BrkInCfg(HAL_GPTMRX_HandleTypeDef *Handle,
                                        HAL_GPTMRX_BreakInputTypeDef BreakInput,
                                        const HAL_GPTMRX_BreakInputConfigTypeDef *pCfg)
{
    GPTMRx_TypeDef *p_instance = Handle->Instance;

    switch (BreakInput) {
        case HAL_GPTMRX_BREAK_INPUT_BK0:
            if (pCfg->Polarity == HAL_GPTMRX_BRK_IN_VALID_POL_HIGH) {
                LL_GPTMRX_SetBreak0InputPolarityHigh(p_instance, (uint32_t)(pCfg->Source));
            } else if (pCfg->Polarity == HAL_GPTMRX_BRK_IN_VALID_POL_LOW) {
                LL_GPTMRX_SetBreak0InputPolarityLow(p_instance, (uint32_t)(pCfg->Source));
            }

            if (pCfg->Enable == HAL_GPTMRX_FUNC_ENABLE) {
                LL_GPTMRX_EnableBreak0Input(p_instance, (uint32_t)(pCfg->Source));        
            } else {
                LL_GPTMRX_DisableBreak0Input(p_instance, ((uint32_t)(pCfg->Source)));
            }

            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}


/**
  * @brief  Judge whether the slave mode of GPTMRX is enabled or not.
  * @param  Handle GPTMRX handle.
  * @return 0: Disabled, 1: Enabled
  */
__STATIC_FORCEINLINE uint32_t GPTMRX_IsSlvModeTrigEnabled(HAL_GPTMRX_HandleTypeDef *Handle)
{
    const uint32_t slv_mode = LL_GPTMRX_GetSlaveMode(Handle->Instance);
    return ((slv_mode == LL_GPTMRX_SLV_MODE_TRIG) || (slv_mode == LL_GPTMRX_SLV_MODE_RST_TRIG)) ? 1UL : 0UL;
}


/**
  * @}
  */

#endif /* HAL_GPTMRX_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* GPTMRX */
/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

