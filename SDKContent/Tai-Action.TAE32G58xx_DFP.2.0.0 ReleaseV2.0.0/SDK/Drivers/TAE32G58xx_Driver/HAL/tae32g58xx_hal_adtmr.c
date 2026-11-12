/**
  ******************************************************************************
  * @file    tae32g58xx_hal_adtmr.c
  * @author  Tai-Action SD Team
  * @brief   ADTMR HAL module driver (advanced timer).
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

/** @defgroup ADTMR_HAL ADTMR HAL
  * @brief    ADTMR HAL module driver.
  * @{
  */

#if defined(TMR9) || defined(TMR10)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_ADTMR_MODULE_ENABLED) && (HAL_ADTMR_MODULE_ENABLED == 1)

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup ADTMR_HAL_Private_Macros ADTMR HAL Private Macros
  * @brief    ADTMR HAL Private Macros
  * @{
  */

/** @defgroup ADTMR_HAL_PM_Discriminant ADTMR HAL Discriminant
  * @brief    ADTMR HAL Discriminant
  * @{
  */

#define IS_ADTMR_ENABLE(__VAL__)                      (((__VAL__) == HAL_ADTMR_FUNC_DISABLE) || \
                                                       ((__VAL__) == HAL_ADTMR_FUNC_ENABLE))

#define IS_ADTMR_WORK_MODE(__VAL__)                   (((__VAL__) == HAL_ADTMR_WORK_MODE_CONTINUE) || \
                                                       ((__VAL__) == HAL_ADTMR_WORK_MODE_SINGLE))

#define IS_ADTMR_UPDATE_EVT_SRC(__VAL__)              (((__VAL__) == HAL_ADTMR_UPDATE_EVT_SRC_OV_UG) || \
                                                       ((__VAL__) == HAL_ADTMR_UPDATE_EVT_SRC_OV))

#define IS_ADTMR_MST_MODE(__VAL__)                    (((__VAL__) == HAL_ADTMR_MST_MODE_RESET)          || \
                                                       ((__VAL__) == HAL_ADTMR_MST_MODE_ENABLE)         || \
                                                       ((__VAL__) == HAL_ADTMR_MST_MODE_UPDATE)         || \
                                                       ((__VAL__) == HAL_ADTMR_MST_MODE_CAP_CMP_EVT)    || \
                                                       ((__VAL__) == HAL_ADTMR_MST_MODE_CMP_OUT0)       || \
                                                       ((__VAL__) == HAL_ADTMR_MST_MODE_CMP_OUT1)       || \
                                                       ((__VAL__) == HAL_ADTMR_MST_MODE_CMP_OUT2)       || \
                                                       ((__VAL__) == HAL_ADTMR_MST_MODE_CMP_OUT3))

#define IS_ADTMR_COUNTER_MODE(__VAL__)                (((__VAL__) == HAL_ADTMR_COUNTER_MODE_UP)              || \
                                                       ((__VAL__) == HAL_ADTMR_COUNTER_MODE_DOWN)            || \
                                                       ((__VAL__) == HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED1) || \
                                                       ((__VAL__) == HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED2) || \
                                                       ((__VAL__) == HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED3))

#define IS_ADTMR_DZ_DIG_FIL_CLK_DIV(__VAL__)          (((__VAL__) == HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_1) || \
                                                       ((__VAL__) == HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_2) || \
                                                       ((__VAL__) == HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_4) || \
                                                       ((__VAL__) == HAL_ADTMR_DZ_DIG_FIL_CLK_DIV_8))

#define IS_ADTMR_CHANNEL_IDX(__VAL__)                 (((__VAL__) == HAL_ADTMR_CHANNEL_0) || \
                                                       ((__VAL__) == HAL_ADTMR_CHANNEL_1) || \
                                                       ((__VAL__) == HAL_ADTMR_CHANNEL_2) || \
                                                       ((__VAL__) == HAL_ADTMR_CHANNEL_3))

#define IS_ADTMR_CAP_POL(__VAL__)                     (((__VAL__) == HAL_ADTMR_CAP_POL_CLOSE)   || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_POL_RISING)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_POL_FALLING) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_POL_BOTH_EDGE))

#define IS_ADTMR_CAP_PRESCALER(__VAL__)               (((__VAL__) == HAL_ADTMR_CAP_PRESCALER_1) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_PRESCALER_2) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_PRESCALER_4) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_PRESCALER_8))

#define IS_ADTMR_CAP_INPUT_MAP(__VAL__)               (((__VAL__) == HAL_ADTMR_CAP_INPUT_MAP_0) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_MAP_1) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_MAP_TRGI))

#define IS_ADTMR_CAP_INPUT_SRC(__VAL__)               (((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN0)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN1)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN2)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN3)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN4)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN5)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN6)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN7)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN8)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN9)  || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN10) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN11) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN12) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN13) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN14) || \
                                                       ((__VAL__) == HAL_ADTMR_CAP_INPUT_SRC_IN15))

#define IS_ADTMR_CMP_POL(__VAL__)                     (((__VAL__) == HAL_ADTMR_CMP_POL_HIGH) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_POL_LOW))

#define IS_ADTMR_OC_MODE(__VAL__)                     (((__VAL__) == HAL_ADTMR_CMP_MODE_FREEZE) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_ACTIVE) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_INACTIVE) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_TOGGLE) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_FORCE_INACTIVE) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_FORCE_ACTIVE) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_PWM1) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_PWM2) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_RETRIG_OPM1) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_RETRIG_OPM2) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_COMB_PWM1) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_COMB_PWM2) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_ASYM_PWM1) || \
                                                       ((__VAL__) == HAL_ADTMR_CMP_MODE_ASYM_PWM2))

#define IS_ADTMR_ETR_MODE(__VAL__)                    (((__VAL__) == HAL_ADTMR_ETR_MODE_EXT_CLK_1) || \
                                                       ((__VAL__) == HAL_ADTMR_ETR_MODE_EXT_CLK_2))

#define IS_ADTMR_ETR_EDGE(__VAL__)                    (((__VAL__) == HAL_ADTMR_ETR_EDGE_MODE_CLOSE) || \
                                                       ((__VAL__) == HAL_ADTMR_ETR_EDGE_MODE_RISING) || \
                                                       ((__VAL__) == HAL_ADTMR_ETR_EDGE_MODE_FALLING) || \
                                                       ((__VAL__) == HAL_ADTMR_ETR_EDGE_MODE_RISING_FALLING))

#define IS_ADTMR_ETR_INPUT_SRC(__VAL__)               (((__VAL__) >= HAL_ADTMR_ETR_INPUT_SRC_ETR0)  && \
                                                       ((__VAL__) <= HAL_ADTMR_ETR_INPUT_SRC_ETR15))

#define IS_ADTMR_TI0_IN_SRC(__VAL__)                  (((__VAL__) == HAL_ADTMR_TI0_IN_SRC_CH0)  || \
                                                       ((__VAL__) == HAL_ADTMR_TI0_IN_SRC_CH0_1_2_XOR))

#define IS_ADTMR_SLV_MODE(__VAL__)                    (((__VAL__) == HAL_ADTMR_SLV_MODE_DIS) || \
                                                       ((__VAL__) == HAL_ADTMR_SLV_MODE_RST) || \
                                                       ((__VAL__) == HAL_ADTMR_SLV_MODE_GATING) || \
                                                       ((__VAL__) == HAL_ADTMR_SLV_MODE_TRIG) || \
                                                       ((__VAL__) == HAL_ADTMR_SLV_MODE_EXTCLK) || \
                                                       ((__VAL__) == HAL_ADTMR_SLV_MODE_RST_TRIG) || \
                                                       ((__VAL__) == HAL_ADTMR_SLV_MODE_RST_GATING))

#define IS_ADTMR_BRK_POL(__VAL__)                     (((__VAL__) == HAL_ADTMR_BRK_POL_HIGH) || \
                                                       ((__VAL__) == HAL_ADTMR_BRK_POL_LOW))

#define IS_ADTMR_RUN_OFF_STA(__VAL__)                 (((__VAL__) == HAL_ADTMR_RUN_OFF_STA_COMP_CLOSE) || \
                                                       ((__VAL__) == HAL_ADTMR_RUN_OFF_STA_COMP_IVD))

#define IS_ADTMR_IDLE_OFF_STA(__VAL__)                (((__VAL__) == HAL_ADTMR_IDLE_OFF_STA_COMP_CLOSE) || \
                                                       ((__VAL__) == HAL_ADTMR_IDLE_OFF_STA_COMP_IDLE))

#define IS_ADTMR_TRIG(__VAL__)                        (((__VAL__) == HAL_ADTMR_TRIG_ITR0)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR1)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR2)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR3)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR4)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR5)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR6)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR7)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR8)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR9)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR10) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR11) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR12) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR13) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR14) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ITR15) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_CH0_FE) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_CH0_F)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_CH1_F)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_CH2_F)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_CH3_F)  || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ETR_FE) || \
                                                       ((__VAL__) == HAL_ADTMR_TRIG_ETR_F))

#define IS_ADTMR_EVENTSOURCE(__VAL__)                 (((__VAL__) == HAL_ADTMR_EVENTSOURCE_UPDATE) || \
                                                       ((__VAL__) == HAL_ADTMR_EVENTSOURCE_TRIG)   || \
                                                       ((__VAL__) == HAL_ADTMR_EVENTSOURCE_BRK0)   || \
                                                       ((__VAL__) == HAL_ADTMR_EVENTSOURCE_BRK1)   || \
                                                       ((__VAL__) == HAL_ADTMR_EVENTSOURCE_CC0)    || \
                                                       ((__VAL__) == HAL_ADTMR_EVENTSOURCE_CC1)    || \
                                                       ((__VAL__) == HAL_ADTMR_EVENTSOURCE_CC2)    || \
                                                       ((__VAL__) == HAL_ADTMR_EVENTSOURCE_CC3))

#define IS_ADTMR_ETR_FILTER(__VAL__)                  (((__VAL__) >= HAL_ADTMR_ETR_FILTER_NONE) && \
                                                       ((__VAL__) <= HAL_ADTMR_ETR_FILTER_TDS_X15))


/**
  * @}
  */ /* ADTMR_HAL_PM_Discriminant */


/**
  * @}
  */ /* ADTMR_HAL_EF_Configuration */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup ADTMR_HAL_Private_Functions ADTMR HAL Private Functions
  * @{
  */
static HAL_StatusTypeDef ADTMR_BaseCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                       const HAL_ADTMR_BaseInitTypeDef *pCfg);

static HAL_StatusTypeDef ADTMR_InputCapCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                           HAL_ADTMR_ChannelIdxTypeDef Channel, 
                                           const HAL_ADTMR_InputCapInitTypeDef *pCfg);

static HAL_StatusTypeDef ADTMR_OutputCmpCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                            HAL_ADTMR_ChannelIdxTypeDef Channel, 
                                            const HAL_ADTMR_OutputCmpInitTypeDef *pCfg);

static HAL_StatusTypeDef ADTMR_MstCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                      const HAL_ADTMR_MstInitTypeDef *pCfg);

static HAL_StatusTypeDef ADTMR_SlvCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                      const HAL_ADTMR_SlvInitTypeDef *pCfg);

static HAL_StatusTypeDef ADTMR_BrkDzCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                        const HAL_ADTMR_BreakDeadTimeConfigTypeDef *pCfg);

static HAL_StatusTypeDef ADTMR_BrkInCfg(HAL_ADTMR_HandleTypeDef *Handle,
                                        HAL_ADTMR_BreakInputTypeDef BreakInput,
                                        const HAL_ADTMR_BreakInputConfigTypeDef *pCfg);

__STATIC_FORCEINLINE uint32_t ADTMR_IsSlvModeTrigEnabled(HAL_ADTMR_HandleTypeDef *Handle);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup ADTMR_HAL_Exported_Functions ADTMR HAL Exported Functions
  * @{
  */

/** @defgroup ADTMR_HAL_EF_Initialization ADTMR HAL Initialization
  * @{
  */

/**
  * @brief  Initialize the ADTMR peripheral according to the specified parameters
  *         and create the associated handle.
  * @param  Handle ADTMR handle.
  * @param  ADTMRx ADTMR instance (TMR9/TMR10).
  * @param  pInit  pointer to a HAL_ADTMR_BaseInitTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_Base_Init(HAL_ADTMR_HandleTypeDef *Handle, 
                                      ADTMR_TypeDef *ADTMRx,
                                      const HAL_ADTMR_BaseInitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));
    ASSERT_FUNC_PARAM(pInit != NULL);

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(ADTMRx)) || (pInit == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_PARAM(IS_ADTMR_WORK_MODE(pInit->WorkMode));
    ASSERT_FUNC_PARAM(IS_ADTMR_UPDATE_EVT_SRC(pInit->UpdateSource));
    ASSERT_FUNC_PARAM(IS_ADTMR_COUNTER_MODE(pInit->CounterMode));
    ASSERT_FUNC_PARAM(IS_ADTMR_DZ_DIG_FIL_CLK_DIV(pInit->DzFilterClockDivision));

    Handle->State = HAL_ADTMR_STATE_RESET;

    /* Bind the instance passed by the caller */
    Handle->Instance = ADTMRx;

    /* Init the low level hardware: CLOCK, NVIC */
    HAL_ADTMR_Base_MspInit(Handle);

    /* Configure the time base */
    (void) ADTMR_BaseCfg(Handle, pInit);

    Handle->LastErrorCodes = HAL_ADTMR_ERROR_NONE;
    Handle->State          = HAL_ADTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  De-initialize the ADTMR peripheral.
  * @param  Handle ADTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_Base_DeInit(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ADTMR_TypeDef *p_instance = Handle->Instance;

    Handle->State = HAL_ADTMR_STATE_BUSY;

    /* Stop the counter and its interrupts */
    LL_ADTMR_DisableCounter(p_instance);

    /* Disable both break inputs */
    LL_ADTMR_DisableBreak0(p_instance);
    LL_ADTMR_DisableBreak1(p_instance);

    /* Disable all capture/compare channels */
    LL_ADTMR_DisableIT(p_instance, LL_ADTMR_IER_IT_EN_MSK);

    LL_ADTMR_CC_DisableAllChannel(p_instance);

    /* De-init the low level hardware: GPIO, CLOCK, NVIC */
    HAL_ADTMR_Base_MspDeInit(Handle);

    Handle->LastErrorCodes = HAL_ADTMR_ERROR_NONE;
    Handle->State          = HAL_ADTMR_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initialize the ADTMR MSP.
  * @note   This function should not be modified. When the application needs its
  *         own implementation, it may override this weak function in the user file.
  * @param  Handle ADTMR handle.
  * @return None
  */
__WEAK void HAL_ADTMR_Base_MspInit(HAL_ADTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  De-initialize the ADTMR MSP.
  * @param  Handle ADTMR handle.
  * @return None
  */
__WEAK void HAL_ADTMR_Base_MspDeInit(HAL_ADTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  Initialize the ADTMR IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval None
  */
__WEAK void HAL_ADTMR_IoInit(ADTMR_TypeDef *ADTMRx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(ADTMRx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADTMR_IoInit could be implemented in the user file
     */
}

/**
  * @brief  De-initialize the ADTMR IO according to the application requirements.
  * @note   This is a weak function that can be overridden by the user. 
  * @param  ADTMRx Specifies ADTMR peripheral
  * @retval None
  */
__WEAK void HAL_ADTMR_IoDeInit(ADTMR_TypeDef *ADTMRx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(ADTMRx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_ADTMR_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */

/** @defgroup ADTMR_HAL_EF_Configuration ADTMR HAL Configuration
  * @{
  */

/**
  * @brief  Configure one ADTMR input capture channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @param  pCfg pointer to the input capture configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_IC_Init(HAL_ADTMR_HandleTypeDef *Handle, 
                                    HAL_ADTMR_ChannelIdxTypeDef Channel,
                                    const HAL_ADTMR_InputCapInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_CAP_POL(pCfg->ICPolarity));
    ASSERT_FUNC_PARAM(IS_ADTMR_CAP_INPUT_MAP(pCfg->ICSelection));
    ASSERT_FUNC_PARAM(IS_ADTMR_CAP_PRESCALER(pCfg->ICPrescaler));
    ASSERT_FUNC_PARAM(IS_ADTMR_CAP_INPUT_SRC(pCfg->ICTriggerSource));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = ADTMR_InputCapCfg(Handle, Channel, pCfg);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure one ADTMR output compare channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @param  pCfg pointer to the output compare configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OC_Init(HAL_ADTMR_HandleTypeDef *Handle, 
                                    HAL_ADTMR_ChannelIdxTypeDef Channel,
                                    const HAL_ADTMR_OutputCmpInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_OC_MODE(pCfg->OCMode));
    ASSERT_FUNC_PARAM(IS_ADTMR_CMP_POL(pCfg->OCPolarity));
    ASSERT_FUNC_PARAM(IS_ADTMR_CMP_POL(pCfg->OCNPolarity));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = ADTMR_OutputCmpCfg(Handle, Channel, pCfg);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the ADTMR Master mode
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to the master configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_InitMaster(HAL_ADTMR_HandleTypeDef *Handle,
                                       const HAL_ADTMR_MstInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_MST_MODE(pCfg->MasterMode));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = ADTMR_MstCfg(Handle, pCfg);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the ADTMR slave mode and ETR input.
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to the slave/ETR configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_InitSlave(HAL_ADTMR_HandleTypeDef *Handle,
                                      const HAL_ADTMR_SlvInitTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ETR_MODE(pCfg->ExtClokMode));
    ASSERT_FUNC_PARAM(IS_ADTMR_ETR_EDGE(pCfg->TriggerPolarity));
    ASSERT_FUNC_PARAM(IS_ADTMR_ETR_INPUT_SRC(pCfg->InputSource));
    ASSERT_FUNC_PARAM(IS_ADTMR_SLV_MODE(pCfg->SlaveMode));
    ASSERT_FUNC_PARAM(IS_ADTMR_TRIG(pCfg->InputTrigger));
    ASSERT_FUNC_PARAM(IS_ADTMR_ETR_FILTER(pCfg->TriggerFilter));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = ADTMR_SlvCfg(Handle, pCfg);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the ADTMR break and dead-time generator.
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to the break/dead-time configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_ConfigBreakDeadTime(HAL_ADTMR_HandleTypeDef *Handle,
                                                const HAL_ADTMR_BreakDeadTimeConfigTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK;

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_BRK_POL(pCfg->Break0Polarity));
    ASSERT_FUNC_PARAM(IS_ADTMR_BRK_POL(pCfg->Break1Polarity));
    ASSERT_FUNC_PARAM(IS_ADTMR_RUN_OFF_STA(pCfg->OffStateRunMode));
    ASSERT_FUNC_PARAM(IS_ADTMR_IDLE_OFF_STA(pCfg->OffStateIdleMode));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = ADTMR_BrkDzCfg(Handle, pCfg);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return ret;
}

/**
  * @brief  Configure the ADTMR break inputs and dead-time generator.
  * @param  Handle ADTMR handle.
  * @param  BreakInput A Break input
  * @param  pCfg pointer to the break input configuration structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_ConfigBreakInput(HAL_ADTMR_HandleTypeDef *Handle,
                                             HAL_ADTMR_BreakInputTypeDef BreakInput,
                                             const HAL_ADTMR_BreakInputConfigTypeDef *pCfg)
{
    HAL_StatusTypeDef ret = HAL_OK; 

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    ret = ADTMR_BrkInCfg(Handle, BreakInput, pCfg);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return ret;

}

/**
  * @brief  Generate a software event of the ADTMR.
  * @param  Handle ADTMR handle.
  * @param  Source TI0 input source
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_ConfigTI0InputSource(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_TI0InSrcTypeDef Source)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_TI0_IN_SRC(Source));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (!IS_ADTMR_TI0_IN_SRC(Source))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_SetTI0InputSource(Handle->Instance, (uint32_t)Source);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @}
  */

/** @defgroup ADTMR_HAL_EF_IO_Operation ADTMR HAL IO Operation
  * @{
  */
/**
  * @brief  Start the ADTMR time base (polling mode).
  * @param  Handle ADTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_Base_Start(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
        LL_ADTMR_EnableCounter(Handle->Instance);
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Stop the ADTMR time base (polling mode).
  * @param  Handle ADTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_Base_Stop(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_DisableCounter(Handle->Instance);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the ADTMR time base in interrupt mode.
  * @param  Handle ADTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_Base_Start_IT(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_EnableIT_UPDATE(Handle->Instance);
    
    if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
        LL_ADTMR_EnableCounter(Handle->Instance);
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the ADTMR time base in interrupt mode.
  * @param  Handle ADTMR handle.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_Base_Stop_IT(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_DisableIT_UPDATE(Handle->Instance);
    LL_ADTMR_DisableCounter(Handle->Instance);

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;

    return HAL_OK;
}

/**
  * @brief  Start the output compare of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OC_Start(HAL_ADTMR_HandleTypeDef *Handle, 
                                     HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_CC_EnableChannel(p_instance, (uint32_t)Channel);
    LL_ADTMR_EnableAllOutputs(p_instance);

    if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
        LL_ADTMR_EnableCounter(p_instance);
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the output compare of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OC_Stop(HAL_ADTMR_HandleTypeDef *Handle, 
                                    HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_CC_DisableChannel(p_instance, (uint32_t)Channel); 

    if (LL_ADTMR_CC_IsAllChannelDisabled(p_instance)) {
        LL_ADTMR_DisableCounter(p_instance);
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Start the output compare interrupt of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OC_StartIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_EnableIT_CxMIE(p_instance, (uint32_t)Channel);
    LL_ADTMR_CC_EnableChannel(p_instance, (uint32_t)Channel);
    LL_ADTMR_EnableAllOutputs(p_instance);

    if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
        LL_ADTMR_EnableCounter(p_instance);
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return HAL_OK;
}

/**
  * @brief  Stop the output compare interrupt of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OC_StopIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    LL_ADTMR_DisableIT_CxMIE(p_instance, (uint32_t)Channel);
    LL_ADTMR_CC_DisableChannel(p_instance, (uint32_t)Channel);

    if (LL_ADTMR_CC_IsAllChannelDisabled(p_instance)) {
        LL_ADTMR_DisableCounter(p_instance);
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the output compare of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OCN_Start(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0: 
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0N); 
            break;
        case HAL_ADTMR_CHANNEL_1: 
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1N); 
            break;
        case HAL_ADTMR_CHANNEL_2: 
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2N); 
            break;
        case HAL_ADTMR_CHANNEL_3: 
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3N); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        LL_ADTMR_EnableAllOutputs(p_instance);

        if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
            LL_ADTMR_EnableCounter(p_instance);
        }     
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the output compare of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OCN_Stop(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0N); 
            break;
        case HAL_ADTMR_CHANNEL_1: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1N); 
            break;
        case HAL_ADTMR_CHANNEL_2: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2N); 
            break;
        case HAL_ADTMR_CHANNEL_3: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3N); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_ADTMR_CC_IsAllChannelDisabled(p_instance)) {
            LL_ADTMR_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the output compare interrupt of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OCN_StartIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0:
            LL_ADTMR_EnableIT_CC0(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0N);
            break;
        case HAL_ADTMR_CHANNEL_1:
            LL_ADTMR_EnableIT_CC1(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1N);
            break;
        case HAL_ADTMR_CHANNEL_2:
            LL_ADTMR_EnableIT_CC2(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2N);
            break;
        case HAL_ADTMR_CHANNEL_3:
            LL_ADTMR_EnableIT_CC3(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3N);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        LL_ADTMR_EnableAllOutputs(p_instance);

        if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
            LL_ADTMR_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the output compare interrupt of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_OCN_StopIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0:
            LL_ADTMR_DisableIT_CC0(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0N);
            break;
        case HAL_ADTMR_CHANNEL_1:
            LL_ADTMR_DisableIT_CC1(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1N);
            break;
        case HAL_ADTMR_CHANNEL_2:
            LL_ADTMR_DisableIT_CC2(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2N);
            break;
        case HAL_ADTMR_CHANNEL_3:
            LL_ADTMR_DisableIT_CC3(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3N);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_ADTMR_CC_IsAllChannelDisabled(p_instance)) {
            LL_ADTMR_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the input capture of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_IC_Start(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0: 
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0); 
            break;
        case HAL_ADTMR_CHANNEL_1: 
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1); 
            break;
        case HAL_ADTMR_CHANNEL_2: 
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2); 
            break;
        case HAL_ADTMR_CHANNEL_3:   
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
            LL_ADTMR_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the input capture of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_IC_Stop(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0); 
            break;
        case HAL_ADTMR_CHANNEL_1: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1); 
            break;
        case HAL_ADTMR_CHANNEL_2: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2); 
            break;
        case HAL_ADTMR_CHANNEL_3: 
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3); 
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_ADTMR_CC_IsAllChannelDisabled(p_instance)) {
            LL_ADTMR_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Start the input capture interrupt of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_IC_StartIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0:
            LL_ADTMR_EnableIT_CC0(p_instance);
            LL_ADTMR_EnableIT_CC0OVR(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0);
            break;
        case HAL_ADTMR_CHANNEL_1:
            LL_ADTMR_EnableIT_CC1(p_instance);
            LL_ADTMR_EnableIT_CC1OVR(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1);
            break;
        case HAL_ADTMR_CHANNEL_2:
            LL_ADTMR_EnableIT_CC2(p_instance);
            LL_ADTMR_EnableIT_CC2OVR(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2);
            break;
        case HAL_ADTMR_CHANNEL_3:
            LL_ADTMR_EnableIT_CC3(p_instance);
            LL_ADTMR_EnableIT_CC3OVR(p_instance);
            LL_ADTMR_CC_EnableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (!ADTMR_IsSlvModeTrigEnabled(Handle)) {
            LL_ADTMR_EnableCounter(p_instance);
        }
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Stop the input capture interrupt of one channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_IC_StopIT(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (Channel >= HAL_ADTMR_CHANNEL_NUMS) {
        return HAL_INVALID;
    }

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (Channel) {
        case HAL_ADTMR_CHANNEL_0:
            LL_ADTMR_DisableIT_CC0(p_instance);
            LL_ADTMR_DisableIT_CC0OVR(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_0);
            break;
        case HAL_ADTMR_CHANNEL_1:
            LL_ADTMR_DisableIT_CC1(p_instance);
            LL_ADTMR_DisableIT_CC1OVR(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_1);
            break;
        case HAL_ADTMR_CHANNEL_2:
            LL_ADTMR_DisableIT_CC2(p_instance);
            LL_ADTMR_DisableIT_CC2OVR(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_2);
            break;
        case HAL_ADTMR_CHANNEL_3:
            LL_ADTMR_DisableIT_CC3(p_instance);
            LL_ADTMR_DisableIT_CC3OVR(p_instance);
            LL_ADTMR_CC_DisableChannel(p_instance, LL_ADTMR_CAP_CMP_CH_3);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    if (ret == HAL_OK) {
        if (LL_ADTMR_CC_IsAllChannelDisabled(p_instance)) {
            LL_ADTMR_DisableCounter(p_instance);
        }  
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Generate a software event of the ADTMR.
  * @param  Handle ADTMR handle.
  * @param  EventSource event to generate
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_GenerateEvent(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_EvtSrcTypeDef EventSource)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_EVENTSOURCE(EventSource));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (!IS_ADTMR_EVENTSOURCE(EventSource))) {
            return HAL_INVALID;
        }
    });

    volatile HAL_StatusTypeDef ret = HAL_OK;
    ADTMR_TypeDef *p_instance = Handle->Instance;

    ASSERT_FUNC_STATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE);

    HAL_ADTMR_PARAM_UPDATE(Handle->State, HAL_ADTMR_STATE_CONFIGURABLE, HAL_ADTMR_STATE_BUSY, {
        return HAL_BUSY;
    });

    switch (EventSource) {
        case HAL_ADTMR_EVENTSOURCE_UPDATE:
            LL_ADTMR_GenerateEvent_UPDATE(p_instance);
            break;

        case HAL_ADTMR_EVENTSOURCE_TRIG:
            LL_ADTMR_GenerateEvent_TRIG(p_instance);
            break;

        case HAL_ADTMR_EVENTSOURCE_BRK0:
            LL_ADTMR_GenerateEvent_BRK0(p_instance);
            break;

        case HAL_ADTMR_EVENTSOURCE_BRK1:
            LL_ADTMR_GenerateEvent_BRK1(p_instance);
            break;

        case HAL_ADTMR_EVENTSOURCE_CC0:
            LL_ADTMR_GenerateEvent_CC0(p_instance);
            break;

        case HAL_ADTMR_EVENTSOURCE_CC1:
            LL_ADTMR_GenerateEvent_CC1(p_instance);
            break;

        case HAL_ADTMR_EVENTSOURCE_CC2:
            LL_ADTMR_GenerateEvent_CC2(p_instance);
            break;

        case HAL_ADTMR_EVENTSOURCE_CC3:
            LL_ADTMR_GenerateEvent_CC3(p_instance);
            break;
        default:
            ret = HAL_INVALID;
            break;
    }

    Handle->State = HAL_ADTMR_STATE_CONFIGURABLE;
    return ret;
}

/**
  * @brief  Read the captured value for an input channel of timer.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @retval Captured value
  */
uint16_t HAL_ADTMR_ReadCapturedValue(const HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance)) || (Channel >= HAL_ADTMR_CHANNEL_NUMS)) {
            return HAL_INVALID;
        }
    });

    return (uint16_t)(LL_ADTMR_IC_GetChannelCompare(Handle->Instance, (uint32_t)Channel));
}

/**
  * @brief  Read the counter at runtime.
  * @param  Handle ADTMR handle.
  * @retval the timer counter register.
  */
uint16_t HAL_ADTMR_ReadCounter(const HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    return (uint16_t)(LL_ADTMR_GetCounter(Handle->Instance));
}

/**
  * @}
  */

/** @defgroup ADTMR_HAL_EF_IRQ_Handler ADTMR HAL IRQ Handler and Callbacks
  * @{
  */

/**
  * @brief  Enable the module level interrupts selected by ITMask.
  * @param  Handle ADTMR handle.
  * @param  ITMask interrupts to enable, value of @ref HAL_ADTMR_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_InterruptRequestEnable(HAL_ADTMR_HandleTypeDef *Handle, 
                                                   HAL_ADTMR_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_ADTMR_EnableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Disable the module level interrupts selected by ITMask.
  * @param  Handle ADTMR handle.
  * @param  ITMask interrupts to disable, value of @ref HAL_ADTMR_ITPendingMskTypeDef.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADTMR_InterruptRequestDisable(HAL_ADTMR_HandleTypeDef *Handle, 
                                                    HAL_ADTMR_ITEnMskTypeDef ITMask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_ADTMR_DisableIT(Handle->Instance, ITMask);

    return HAL_OK;
}

/**
  * @brief  Handle the ADTMR Break interrupt handler.
  * @param  Handle ADTMR handle.
  * @return None
  */
void HAL_ADTMR_BRK_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    ADTMR_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_ADTMR_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_ADTMR_GetAllITPending(p_instance) & LL_ADTMR_SR_BRK_IT_FLAG_MSK;

    /* Break interrupts (BK0 / BK1 / system fault) */
    if (int_en & LL_ADTMR_IER_BIE) {
        if (int_pending & LL_ADTMR_SR_SBIF) {
            LL_ADTMR_ClearFlag_SYSBRK(p_instance);
        }

        if (int_pending & LL_ADTMR_SR_B0IF) {
            LL_ADTMR_ClearFlag_BRK0(p_instance);
        }

        if (int_pending & LL_ADTMR_SR_B1IF) {
            LL_ADTMR_ClearFlag_BRK1(p_instance);
        }

        HAL_ADTMR_BreakCallback(Handle, int_pending);
    }
}

/**
  * @brief  Handle the ADTMR update event interrupt handler.
  * @param  Handle ADTMR handle.
  * @return None
  */
void HAL_ADTMR_UPD_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    ADTMR_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_ADTMR_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_ADTMR_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers OVIF/UIF bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_ADTMR_SR_UPD_IT_FLAG_MSK; 

    /* Update interrupt */
    if (flag_status_masked & LL_ADTMR_SR_UIF) {
        LL_ADTMR_ClearFlag_UPDATE(p_instance);

        HAL_ADTMR_PeriodElapsedCallback(Handle);
    }

    /* Overflow interrupt */
    if (flag_status_masked & LL_ADTMR_SR_OVIF) {
        LL_ADTMR_ClearFlag_OVR(p_instance);

        HAL_ADTMR_OverflowCallback(Handle);
    }
}

/**
  * @brief  Handle the ADTMR trigger interrupt handler.
  * @param  Handle ADTMR handle.
  * @return None
  */
void HAL_ADTMR_TRG_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    ADTMR_TypeDef *p_instance = Handle->Instance;

    /* Trigger interrupt */
    if ((LL_ADTMR_IsEnabledIT_TRIG(p_instance) != 0UL) && 
        (LL_ADTMR_IsActiveFlag_TRIG(p_instance) != 0UL)) {
        /* Clear flag */
        LL_ADTMR_ClearFlag_TRIG(p_instance);

        /* Invoke callback */
        HAL_ADTMR_TriggerCallback(Handle);
    }
}

/**
  * @brief  Handle the ADTMR Compare/Capture interrupt handler.
  * @param  Handle ADTMR handle.
  * @return None
  */
void HAL_ADTMR_CC_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });
    
    ADTMR_TypeDef *p_instance = Handle->Instance;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_ADTMR_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_ADTMR_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers CCx bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_ADTMR_SR_CC_IT_FLAG_MSK; 

    /* CC0 */
    if (flag_status_masked & LL_ADTMR_SR_CC0OIF) {
        LL_ADTMR_ClearFlag_CC0OVR(p_instance);         

        HAL_ADTMR_IC_OverCaptureCallback(Handle, HAL_ADTMR_CHANNEL_0); 
    }

    if (flag_status_masked & LL_ADTMR_SR_CC0MIF) {
        LL_ADTMR_ClearFlag_CC0(p_instance);    

        if (LL_ADTMR_IC_GetActiveInput(p_instance, LL_ADTMR_CAP_CMP_CH_0) == LL_ADTMR_CMP_CAP_MAP_OUTPUT) {
            HAL_ADTMR_OC_DelayElapsedCallback(Handle, HAL_ADTMR_CHANNEL_0);    
        } else {
            HAL_ADTMR_IC_CaptureCallback(Handle, HAL_ADTMR_CHANNEL_0);    
        }
    }

    /* CC1 */
    if (flag_status_masked & LL_ADTMR_SR_CC1OIF) {
        LL_ADTMR_ClearFlag_CC1OVR(p_instance);         

        HAL_ADTMR_IC_OverCaptureCallback(Handle, HAL_ADTMR_CHANNEL_1); 
    }

    if (flag_status_masked & LL_ADTMR_SR_CC1MIF) {
        LL_ADTMR_ClearFlag_CC1(p_instance);    

        if (LL_ADTMR_IC_GetActiveInput(p_instance, LL_ADTMR_CAP_CMP_CH_1) == LL_ADTMR_CMP_CAP_MAP_OUTPUT) {
            HAL_ADTMR_OC_DelayElapsedCallback(Handle, HAL_ADTMR_CHANNEL_1);    
        } else {
            HAL_ADTMR_IC_CaptureCallback(Handle, HAL_ADTMR_CHANNEL_1);    
        }
    }

    /* CC2 */
    if (flag_status_masked & LL_ADTMR_SR_CC2OIF) {
        LL_ADTMR_ClearFlag_CC2OVR(p_instance);         

        HAL_ADTMR_IC_OverCaptureCallback(Handle, HAL_ADTMR_CHANNEL_2); 
    }

    if (flag_status_masked & LL_ADTMR_SR_CC2MIF) {
        LL_ADTMR_ClearFlag_CC2(p_instance);    

        if (LL_ADTMR_IC_GetActiveInput(p_instance, LL_ADTMR_CAP_CMP_CH_2) == LL_ADTMR_CMP_CAP_MAP_OUTPUT) {
            HAL_ADTMR_OC_DelayElapsedCallback(Handle, HAL_ADTMR_CHANNEL_2);    
        } else {
            HAL_ADTMR_IC_CaptureCallback(Handle, HAL_ADTMR_CHANNEL_2);    
        }
    }

    /* CC3 */
    if (flag_status_masked & LL_ADTMR_SR_CC3OIF) {
        LL_ADTMR_ClearFlag_CC3OVR(p_instance);         

        HAL_ADTMR_IC_OverCaptureCallback(Handle, HAL_ADTMR_CHANNEL_3); 
    }

    if (flag_status_masked & LL_ADTMR_SR_CC3MIF) {
        LL_ADTMR_ClearFlag_CC3(p_instance);    

        if (LL_ADTMR_IC_GetActiveInput(p_instance, LL_ADTMR_CAP_CMP_CH_3) == LL_ADTMR_CMP_CAP_MAP_OUTPUT) {
            HAL_ADTMR_OC_DelayElapsedCallback(Handle, HAL_ADTMR_CHANNEL_3);    
        } else {
            HAL_ADTMR_IC_CaptureCallback(Handle, HAL_ADTMR_CHANNEL_3);    
        } 
    }
}

/**
  * @brief  Handle the ADTMR Compare/Capture channel interrupt handler.
  * @param  Handle ADTMR handle.
  * @return None
  */
void HAL_ADTMR_CCx_IRQHandler(HAL_ADTMR_HandleTypeDef *Handle, HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(IS_ADTMR_CHANNEL_IDX(Channel));

    HAL_ADTMR_PARAM_CHECK({
        if ((Handle == NULL)                            || 
            (!IS_ADTMR_ALL_INSTANCE(Handle->Instance))  || 
            (!IS_ADTMR_CHANNEL_IDX(Channel))) {
            return;
        }
    });
    
    ADTMR_TypeDef *p_instance = Handle->Instance;

    if ((LL_ADTMR_IsActiveFlag_CCxOIF(p_instance, (uint32_t)Channel)) && 
        (LL_ADTMR_IsEnabledIT_CxOIE(p_instance, (uint32_t)Channel))) {
        /* Clear flag */
        LL_ADTMR_ClearFlag_CCxOIF(p_instance, (uint32_t)Channel);         

        /* Invoke callback */
        HAL_ADTMR_IC_OverCaptureCallback(Handle, Channel); 
    }

    if ((LL_ADTMR_IsActiveFlag_CCxMIF(p_instance, (uint32_t)Channel)) && 
        (LL_ADTMR_IsEnabledIT_CxMIE(p_instance, (uint32_t)Channel))) {
        /* Clear flag */
        LL_ADTMR_ClearFlag_CCxMIF(p_instance, (uint32_t)Channel);    

        /* Invoke callback */
        if (LL_ADTMR_IC_GetActiveInput(p_instance, (uint32_t)Channel) == LL_ADTMR_CMP_CAP_MAP_OUTPUT) {
            HAL_ADTMR_OC_DelayElapsedCallback(Handle, Channel);    
        } else {
            HAL_ADTMR_IC_CaptureCallback(Handle, Channel);    
        }
    }
}


/**
  * @brief  ADTMR update (reload) callback.
  * @param  Handle ADTMR handle.
  * @return None
  */
__WEAK void HAL_ADTMR_PeriodElapsedCallback(HAL_ADTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  ADTMR overflow callback.
  * @param  Handle ADTMR handle.
  * @return None
  */
__WEAK void HAL_ADTMR_OverflowCallback(HAL_ADTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  ADTMR trigger callback.
  * @param  Handle ADTMR handle.
  * @return None
  */
__WEAK void HAL_ADTMR_TriggerCallback(HAL_ADTMR_HandleTypeDef *Handle)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  ADTMR break callback.
  * @param  Handle ADTMR handle.
  * @return None
  */
__WEAK void HAL_ADTMR_BreakCallback(HAL_ADTMR_HandleTypeDef *Handle, 
                                    HAL_ADTMR_ITPendingMskTypeDef BreakEvent)
{
    HAL_UNUSED(Handle);
}

/**
  * @brief  ADTMR channel compare callback.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return None
  */
__WEAK void HAL_ADTMR_OC_DelayElapsedCallback(HAL_ADTMR_HandleTypeDef *Handle, 
                                              HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    HAL_UNUSED(Handle);
    HAL_UNUSED(Channel);
}

/**
  * @brief  ADTMR channel capture callback.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return None
  */
__WEAK void HAL_ADTMR_IC_CaptureCallback(HAL_ADTMR_HandleTypeDef *Handle, 
                                         HAL_ADTMR_ChannelIdxTypeDef Channel)
{
    HAL_UNUSED(Handle);
    HAL_UNUSED(Channel);
}

/**
  * @brief  ADTMR channel over-capture callback.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @return None
  */
__WEAK void HAL_ADTMR_IC_OverCaptureCallback(HAL_ADTMR_HandleTypeDef *Handle, 
                                             HAL_ADTMR_ChannelIdxTypeDef Channel)
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
/** @defgroup ADTMR_HAL_Private_Functions ADTMR HAL Private Functions
  * @{
  */

/**
  * @brief  Configure the ADTMR time base from the init structure.
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to a HAL_ADTMR_BaseInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef ADTMR_BaseCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                       const HAL_ADTMR_BaseInitTypeDef *pCfg)
{
    ADTMR_TypeDef *p_instance = Handle->Instance;



    /* Time base: counter value, period and prescaler (all 16-bit) */
    LL_ADTMR_SetCounter(p_instance, 0UL);
    LL_ADTMR_SetAutoReload(p_instance, pCfg->Period);
    LL_ADTMR_SetPrescaler(p_instance, pCfg->Prescaler);

    /* Work mode */
    LL_ADTMR_SetOnePulseMode(p_instance, (uint32_t)pCfg->WorkMode);

    /* Advance configuration */
    LL_ADTMR_SetRepetitionCounter(p_instance, pCfg->RepetitionCounter);
    LL_ADTMR_SetDzDigFilClkDiv(p_instance, (uint32_t)pCfg->DzFilterClockDivision);

    switch (pCfg->CounterMode) {
        case HAL_ADTMR_COUNTER_MODE_UP:
            LL_ADTMR_SetAlignmentMode(p_instance, LL_ADTMR_CTR_ALIGN_MODE_EDGE);
            LL_ADTMR_SetDirection(p_instance, LL_ADTMR_CNT_DIR_INC);
            break;

        case HAL_ADTMR_COUNTER_MODE_DOWN:
            LL_ADTMR_SetAlignmentMode(p_instance, LL_ADTMR_CTR_ALIGN_MODE_EDGE);
            LL_ADTMR_SetDirection(p_instance, LL_ADTMR_CNT_DIR_DEC);
            break;

        case HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED1:
            LL_ADTMR_SetAlignmentMode(p_instance, LL_ADTMR_CTR_ALIGN_MODE_CENTER_1);
            break;

        case HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED2:
            LL_ADTMR_SetAlignmentMode(p_instance, LL_ADTMR_CTR_ALIGN_MODE_CENTER_2);
            break;

        case HAL_ADTMR_COUNTER_MODE_CENTER_ALIGNED3:
            LL_ADTMR_SetAlignmentMode(p_instance, LL_ADTMR_CTR_ALIGN_MODE_CENTER_3);
            break;

        default:
            break;
    }

    /* Update event source and enable */
    LL_ADTMR_SetUpdateSource(p_instance, (uint32_t)pCfg->UpdateSource);

    if (pCfg->UpdateEvent == HAL_ADTMR_UPDATE_EVT_ASSERT) {
        LL_ADTMR_DisableUpdateEvent(p_instance);
    } else if (pCfg->UpdateEvent == HAL_ADTMR_UPDATE_EVT_RELEASE) {
        LL_ADTMR_EnableUpdateEvent(p_instance);
    }

    /* Auto preload */
    HAL_FUNC_ALTER(pCfg->AutoReloadPreload, LL_ADTMR_EnableAutoReload(p_instance),
                                            LL_ADTMR_DisableAutoReload(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure one ADTMR input capture channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @param  pCfg pointer to a HAL_ADTMR_InputCapInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef ADTMR_InputCapCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                           HAL_ADTMR_ChannelIdxTypeDef Channel, 
                                           const HAL_ADTMR_InputCapInitTypeDef *pCfg)
{
    ADTMR_TypeDef *p_instance = Handle->Instance;

    LL_ADTMR_IC_SetActiveInput(p_instance, Channel, (uint32_t)pCfg->ICSelection);
    LL_ADTMR_IC_SetFilter(p_instance, Channel, (uint32_t)pCfg->ICFilter);
    LL_ADTMR_IC_SetPrescaler(p_instance, Channel, (uint32_t)pCfg->ICPrescaler);
    LL_ADTMR_IC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->ICPolarity);
    LL_ADTMR_IC_SetInputSource(p_instance, Channel, (uint32_t)pCfg->ICTriggerSource);

    return HAL_OK;
}

/**
  * @brief  Configure one ADTMR output compare channel.
  * @param  Handle ADTMR handle.
  * @param  Channel ADTMR channel.
  * @param  pCfg pointer to a HAL_ADTMR_OutputCmpInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef ADTMR_OutputCmpCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                            HAL_ADTMR_ChannelIdxTypeDef Channel, 
                                            const HAL_ADTMR_OutputCmpInitTypeDef *pCfg)
{
    ADTMR_TypeDef *p_instance = Handle->Instance;

    LL_ADTMR_IC_SetActiveInput(p_instance, Channel, LL_ADTMR_CMP_CAP_MAP_OUTPUT);                           
    LL_ADTMR_OC_SetChannelCompare(p_instance, Channel, pCfg->CompareValue);
    LL_ADTMR_OC_SetMode(p_instance, Channel, (uint32_t)pCfg->OCMode);          
    LL_ADTMR_OC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->OCPolarity, LL_ADTMR_CAP_CMP_OC);    
    LL_ADTMR_OC_SetPolarity(p_instance, Channel, (uint32_t)pCfg->OCNPolarity, LL_ADTMR_CAP_CMP_OCN);          

    LL_ADTMR_OC_SetIdleState(p_instance, Channel, (uint32_t)pCfg->OCIdleState);
    LL_ADTMR_OC_SetIdleState(p_instance, (((uint32_t)Channel) % LL_ADTMR_CAP_CMP_CH_NUMS) + LL_ADTMR_CAP_CMP_CH_0N, (uint32_t)pCfg->OCNIdleState);  
                    
    HAL_FUNC_ALTER(pCfg->CompareAutoReload,
                    LL_ADTMR_OC_EnablePreload(p_instance, Channel),             
                    LL_ADTMR_OC_DisablePreload(p_instance, Channel));           

    return HAL_OK;
}

/**
  * @brief  Configure the ADTMR master
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to a HAL_ADTMR_MstInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef ADTMR_MstCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                      const HAL_ADTMR_MstInitTypeDef *pCfg)
{
    ADTMR_TypeDef *p_instance = Handle->Instance;
    const uint32_t trgo_ch_msk = pCfg->TRGOSelection;

    /* Master mode and TRGO width */
    LL_ADTMR_SetTriggerOutput(p_instance, (uint32_t)pCfg->MasterMode);
    LL_ADTMR_SetTrigOutputWidth(p_instance, pCfg->TRGOWidth);
    LL_ADTMR_SetTrigCyclesWidth(p_instance, pCfg->TRGCCWidth); 

    if (trgo_ch_msk & HAL_ADTMR_TRGI_OUT_SELECT_CH0_MASK) {
        LL_ADTMR_EnableTriggerCH0(p_instance);
    } else {
        LL_ADTMR_DisableTriggerCH0(p_instance);
    }

    if (trgo_ch_msk & HAL_ADTMR_TRGI_OUT_SELECT_CH1_MASK) {
        LL_ADTMR_EnableTriggerCH1(p_instance);
    } else {
        LL_ADTMR_DisableTriggerCH1(p_instance);
    }

    if (trgo_ch_msk & HAL_ADTMR_TRGI_OUT_SELECT_CH2_MASK) {
        LL_ADTMR_EnableTriggerCH2(p_instance);
    } else {
        LL_ADTMR_DisableTriggerCH2(p_instance);
    }

    if (trgo_ch_msk & HAL_ADTMR_TRGI_OUT_SELECT_CH3_MASK) {
        LL_ADTMR_EnableTriggerCH3(p_instance);
    } else {
        LL_ADTMR_DisableTriggerCH3(p_instance);
    }

    return HAL_OK;
}


/**
  * @brief  Configure the ADTMR slave mode and ETR input.
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to a HAL_ADTMR_SlvInitTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef ADTMR_SlvCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                      const HAL_ADTMR_SlvInitTypeDef *pCfg)
{
    ADTMR_TypeDef *p_instance = Handle->Instance;

    LL_ADTMR_SetTriggerInput(p_instance, (uint32_t)pCfg->InputTrigger);
    LL_ADTMR_SetSlaveMode(p_instance, (uint32_t)pCfg->SlaveMode);

    /* External trigger (ETR) input */
    LL_ADTMR_SetETRInputSrc(p_instance, (uint32_t)pCfg->InputSource);
    LL_ADTMR_SetETRMode(p_instance, (uint32_t)pCfg->ExtClokMode);
    LL_ADTMR_SetETREdgeMode(p_instance, (uint32_t)pCfg->TriggerPolarity);
    LL_ADTMR_SetETRFilter(p_instance, (uint32_t)pCfg->TriggerFilter);

    HAL_FUNC_ALTER(pCfg->FastSync,
                  LL_ADTMR_EnableMstSlvFastSync(p_instance),
                  LL_ADTMR_DisableMstSlvFastSync(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure the ADTMR break state, dead-time and output off-state.
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to a HAL_ADTMR_BreakDeadTimeConfigTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef ADTMR_BrkDzCfg(HAL_ADTMR_HandleTypeDef *Handle, 
                                        const HAL_ADTMR_BreakDeadTimeConfigTypeDef *pCfg)
{
    ADTMR_TypeDef *p_instance = Handle->Instance;

    /* Break 0 */
    LL_ADTMR_SetBreak0Polarity(p_instance, (uint32_t)pCfg->Break0Polarity);
    LL_ADTMR_SetBreak0Filter(p_instance, pCfg->Break0Filter);
    HAL_FUNC_ALTER(pCfg->Break0State,
                  LL_ADTMR_EnableBreak0(p_instance),
                  LL_ADTMR_DisableBreak0(p_instance));

    /* Break 1 */
    LL_ADTMR_SetBreak1Polarity(p_instance, (uint32_t)pCfg->Break1Polarity);
    LL_ADTMR_SetBreak1Filter(p_instance, pCfg->Break1Filter);
    HAL_FUNC_ALTER(pCfg->Break1State,
                  LL_ADTMR_EnableBreak1(p_instance),
                  LL_ADTMR_DisableBreak1(p_instance));

    /* Break interrupt */
    HAL_FUNC_ALTER(pCfg->BreakIT,
                  LL_ADTMR_EnableIT_BRK(p_instance),
                  LL_ADTMR_DisableIT_BRK(p_instance));

    /* Dead-time generator */
    LL_ADTMR_SetFallingDeadTime(p_instance, pCfg->DeadTime);

    LL_ADTMR_SetRunModeOffState(p_instance, (uint32_t)pCfg->OffStateRunMode);
    LL_ADTMR_SetIdleModeOffState(p_instance, (uint32_t)pCfg->OffStateIdleMode);

    HAL_FUNC_ALTER(pCfg->AutomaticOutput,
                  LL_ADTMR_EnableAutomaticOutput(p_instance),
                  LL_ADTMR_DisableAutomaticOutput(p_instance));

    return HAL_OK;
}

/**
  * @brief  Configure the ADTMR break inputs.
  * @param  Handle ADTMR handle.
  * @param  pCfg pointer to a HAL_ADTMR_BreakDeadTimeConfigTypeDef structure.
  * @return None
  */
static HAL_StatusTypeDef ADTMR_BrkInCfg(HAL_ADTMR_HandleTypeDef *Handle,
                                        HAL_ADTMR_BreakInputTypeDef BreakInput,
                                        const HAL_ADTMR_BreakInputConfigTypeDef *pCfg)
{
    ADTMR_TypeDef *p_instance = Handle->Instance;

    switch (BreakInput) {
        case HAL_ADTMR_BREAK_INPUT_BK0:
            if (pCfg->Polarity == HAL_ADTMR_BRK_IN_VALID_POL_HIGH) {
                LL_ADTMR_SetBreak0InputPolarityHigh(p_instance, (uint32_t)(pCfg->Source));
            } else if (pCfg->Polarity == HAL_ADTMR_BRK_IN_VALID_POL_LOW) {
                LL_ADTMR_SetBreak0InputPolarityLow(p_instance, (uint32_t)(pCfg->Source));
            }

            if (pCfg->Enable == HAL_ADTMR_FUNC_ENABLE) {
                LL_ADTMR_EnableBreak0Input(p_instance, (uint32_t)(pCfg->Source));        
            } else {
                LL_ADTMR_DisableBreak0Input(p_instance, ((uint32_t)(pCfg->Source)));
            }

            break;
        case HAL_ADTMR_BREAK_INPUT_BK1:
            if (pCfg->Polarity == HAL_ADTMR_BRK_IN_VALID_POL_HIGH) {
                LL_ADTMR_SetBreak1InputPolarityHigh(p_instance, (uint32_t)(pCfg->Source));
            } else if (pCfg->Polarity == HAL_ADTMR_BRK_IN_VALID_POL_LOW) {
                LL_ADTMR_SetBreak1InputPolarityLow(p_instance, (uint32_t)(pCfg->Source));
            }

            if (pCfg->Enable == HAL_ADTMR_FUNC_ENABLE) {
                LL_ADTMR_EnableBreak1Input(p_instance, (uint32_t)(pCfg->Source));        
            } else {
                LL_ADTMR_DisableBreak1Input(p_instance, ((uint32_t)(pCfg->Source)));
            }

            break;
        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Judge whether the slave mode of ADTMR is enabled or not.
  * @param  Handle ADTMR handle.
  * @return 0: Disabled, 1: Enabled
  */
__STATIC_FORCEINLINE uint32_t ADTMR_IsSlvModeTrigEnabled(HAL_ADTMR_HandleTypeDef *Handle)
{
    const uint32_t slv_mode = LL_ADTMR_GetSlaveMode(Handle->Instance);
    return ((slv_mode == LL_ADTMR_SLV_MODE_TRIG) || (slv_mode == LL_ADTMR_SLV_MODE_RST_TRIG)) ? 1UL : 0UL;
}


/**
  * @}
  */

#endif /* HAL_ADTMR_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* ADTMR */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

