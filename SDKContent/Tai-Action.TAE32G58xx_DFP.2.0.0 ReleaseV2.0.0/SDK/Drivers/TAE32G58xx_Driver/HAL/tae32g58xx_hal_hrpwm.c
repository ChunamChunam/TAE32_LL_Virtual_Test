/**
  ******************************************************************************
  * @file    tae32g58xx_hal_hrpwm.c
  * @author  Tai-Action SD Team
  * @brief   HRPWM HAL module driver
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

#if defined(HRPWM)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_HRPWM_MODULE_ENABLED) && (HAL_HRPWM_MODULE_ENABLED == 1)

/** @defgroup HRPWM_HAL HRPWM HAL
  * @brief    HRPWM HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/** @defgroup HRPWM_HAL_Private_Constants HRPWM HAL Private Constants
  * @brief    HRPWM HAL Private Constants
  * @{
  */

/**
  * @brief HRPWM Defaul Timeout definition in ms Unit
  */
#define HRPWM_DEFAULT_TIMEOUT       (25)

/**
  * @}
  */ /* HRPWM_HAL_Private_Constants */


/* Private Macros ------------------------------------------------------------*/
/** @defgroup HRPWM_HAL_Private_Macros HRPWM HAL Macros Constants
  * @brief    HRPWM HAL Private Macros
  * @{
  */

/** @defgroup HRPWM_HAL_PM_Discriminant HRPWM HAL Discriminant
  * @brief    HRPWM HAL Discriminant
  * @{
  */

#define IS_HRPWM_MST_DMA IS_LL_HRPWM_MST_DMA
#define IS_HRPWM_SLV_DMA IS_LL_HRPWM_SLV_DMA

/**
  * @}
  */ /* HRPWM_HAL_PM_Discriminant */

/**
  * @}
  */ /* HRPWM_HAL_Private_Macros */





/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup HRPWM_HAL_Private_Functions HRPWM HAL Private Functions
  * @brief    HRPWM HAL Private Functions
  * @{
  */

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_TimeBaseCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             const HAL_HRPWM_TimeBaseCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_TimeBaseCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                             const HAL_HRPWM_TimeBaseCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_WaveformTmrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                const HAL_HRPWM_TimerCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformTmrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                const HAL_HRPWM_TimerCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformTimerCtl(HAL_HRPWM_HandleTypeDef *Handle,
                                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                  const HAL_HRPWM_TimerCtlTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_DualDacCfg(HAL_HRPWM_HandleTypeDef *Handle,
                                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                            const HAL_HRPWM_DualDacCtlTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_WaveformCmpCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_CmpUnitTypeDef CmpUnit, 
                                                                const HAL_HRPWM_CompareCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformCmpCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                HAL_HRPWM_CmpUnitTypeDef CmpUnit, 
                                                                const HAL_HRPWM_CompareCfgTypeDef *pCfg);

static HAL_StatusTypeDef HRPWM_SysDMACfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                         const HAL_HRPWM_SysDMACfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_SysDMACfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                           const HAL_HRPWM_SysDMACfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_SysDMACfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                           const HAL_HRPWM_SysDMACfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_RollOverModeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                 const HAL_HRPWM_RollOverModeCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_TmrEvtFilCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                              HAL_HRPWM_ExtEvtNumTypeDef EvtNum, 
                                                              const HAL_HRPWM_TimerEventFilteringCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_ExtEvtCntrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                               HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                               HAL_HRPWM_EvtCntrTypeDef EvtCntr, 
                                                               const HAL_HRPWM_ExternalEventCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformOutputCfg(HAL_HRPWM_HandleTypeDef *Handle,
                                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                   HAL_HRPWM_OutputChnlTypeDef Channel,
                                                                   const HAL_HRPWM_OutputCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_DeadTimeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                             const HAL_HRPWM_DeadTimeCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_ChopModeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                             const HAL_HRPWM_ChopperModeCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformCapCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                                HAL_HRPWM_CapChnlTypeDef Channel,
                                                                const HAL_HRPWM_CaptureCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_ExtEvtCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                            HAL_HRPWM_ExtEvtNumTypeDef EvtNum,
                                                            const HAL_HRPWM_EventCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_FltCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                         HAL_HRPWM_FltNumTypeDef FltNum, 
                                                         const HAL_HRPWM_FaultCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_FltCntrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_FltNumTypeDef FltNum, 
                                                             const HAL_HRPWM_FaultCntrCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_FltBlkCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                            HAL_HRPWM_FltNumTypeDef FltNum, 
                                                            const HAL_HRPWM_FaultBlankingCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_ADCTrigCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_ADCTrigNumTypeDef TrigNum,
                                                             const HAL_HRPWM_ADCTriggerCfgTypeDef *pCfg);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_BurstDMAUpdateCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                   HAL_HRPWM_EnableTypeDef Enable);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_BurstDMAUpdateCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                   HAL_HRPWM_EnableTypeDef Enable);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_BurstModeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                               const HAL_HRPWM_BurstModeCfgTypeDef *pCfg);

static HAL_StatusTypeDef HRPWM_ForceRegistersUpdate(HAL_HRPWM_HandleTypeDef *Handle, 
                                                    HAL_HRPWM_PWMIdxTypeDef PwmIdx);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_ForceRegistersUpdate(HAL_HRPWM_HandleTypeDef *Handle);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_ForceRegistersUpdate(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                      HAL_HRPWM_PWMIdxTypeDef PwmIdx);

__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_SwTrigOutLvl(HAL_HRPWM_HandleTypeDef *Handle, 
                                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                              HAL_HRPWM_OutputChnlTypeDef Channel,
                                                              HAL_HRPWM_Slv_OutLvlStateTypeDef Output);

__STATIC_FORCEINLINE HAL_HRPWM_Slv_OutStateTypeDef HRPWM_Slv_OutputState(const HAL_HRPWM_HandleTypeDef *Handle, 
                                                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                         HAL_HRPWM_OutputChnlTypeDef Channel);

/**
  * @}
  */ /* HRPWM_HAL_Private_Functions */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup HRPWM_HAL_Exported_Functions HRPWM HAL Exported Functions
  * @brief    HRPWM HAL Exported Functions
  * @{
  */

/** @defgroup HRPWM_HAL_EF_Initialization HRPWM Init and DeInit Functions
  * @brief    HRPWM Init and DeInit Functions
  * @{
  */

/**
  * @brief  HRPWM HAL Init
  * @param  Handle HRPWM Handle
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Status of the Initialization
  */
HAL_StatusTypeDef HAL_HRPWM_Init(HAL_HRPWM_HandleTypeDef *Handle, 
                                 HRPWM_TypeDef *HRPWMx, 
                                 const HAL_HRPWM_InitTypeDef *pInit)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));
    ASSERT_FUNC_PARAM(pInit != NULL);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(HRPWMx)) || (pInit == NULL)) {
            return HAL_INVALID;
        }      
    });

    /* Bind peripheral instance */
    Handle->Instance = HRPWMx;

    HRPWM_TypeDef *p_instance = Handle->Instance;

    Handle->State = HAL_HRPWM_STATE_INIT;

    /* Init the low level hardware eg. Clock, NVIC */
    HAL_HRPWM_MspInit(Handle);

    /* Sync Mode Disable */
    if (pInit->SyncOptions == HAL_HRPWM_MST_SYNC_MODE_DIS) {
        LL_HRPWM_MST_DisableSyncInput(p_instance);
        LL_HRPWM_MST_DisableSyncOutput(p_instance);
    }

    /* Sync Mode Master (Sync Output) */
    if (pInit->SyncOptions & HAL_HRPWM_MST_SYNC_MODE_MST) {
        LL_HRPWM_MST_SetSyncOutSrc(p_instance, pInit->SyncOutputSource);
        LL_HRPWM_MST_SetSyncOutConfig(p_instance, pInit->SyncOutputPolarity);
        LL_HRPWM_MST_EnableSyncOutput(p_instance);
    }

    /* Sync Mode Slave (Sync Input) */
    if (pInit->SyncOptions & HAL_HRPWM_MST_SYNC_MODE_SLV) {
        LL_HRPWM_MST_SetSyncInSrc(p_instance, pInit->SyncInputSource);
        LL_HRPWM_MST_EnableSyncInput(p_instance);
    }

    Handle->State = HAL_HRPWM_STATE_IDLE;

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL DeInit
  * @param  Handle HRPWM Handle
  * @return Status of the DeInitialization
  */
HAL_StatusTypeDef HAL_HRPWM_DeInit(HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    /* All PWM Disable and Output Stop */
    LL_HRPWM_COM_DisableOutput(p_instance, LL_HRPWM_SLV_PWM_OUT_ALL_MASK);
    LL_HRPWM_MST_CounterDisable(p_instance, LL_HRPWM_ALL_PWM_MASK);

    /* DeInit the low level hardware eg. Clock, NVIC */
    HAL_HRPWM_MspDeInit(Handle);

    Handle->State = HAL_HRPWM_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initializes the HRPWM MSP
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MspInit(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the HRPWM MSP
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MspDeInit(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Initializes the HRPWM IO
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__WEAK void HAL_HRPWM_IoInit(HRPWM_TypeDef *HRPWMx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(HRPWMx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_IoInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the HRPWM IO
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__WEAK void HAL_HRPWM_IoDeInit(HRPWM_TypeDef *HRPWMx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(HRPWMx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_IoDeInit could be implemented in the user file
     */
}

/**
  * @}
  */ /* HRPWM_HAL_EF_Initialization */


/** @defgroup HRPWM_HAL_EF_Configuration HRPWM Configuration Functions
  * @brief    HRPWM Configuration Functions
  * @{
  */

/**
  * @brief  HRPWM HAL Timer Base Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Timer Base to be Config, include Master PWM
  * @param  pCfg Time Base Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_TimeBaseConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                           const HAL_HRPWM_TimeBaseCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }        
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_HRPWM_STATE_INIT | HAL_HRPWM_STATE_IDLE);

    //Timer Base Config
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        return HRPWM_Mst_TimeBaseCfg(Handle, pCfg);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        HAL_HRPWM_PARAM_CHECK({
            if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                return HAL_INVALID;
            }
        });

        return HRPWM_Slv_TimeBaseCfg(Handle, PwmIdx, pCfg);
    }
}

/**
  * @brief  HRPWM HAL Timer Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Timer to be Config, include Master PWM
  * @param  pCfg pointer to the timer configuration structure
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformTimerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                const HAL_HRPWM_TimerCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }        
    });

    ASSERT_FUNC_STATE(Handle->State, HAL_HRPWM_STATE_INIT | HAL_HRPWM_STATE_IDLE);

    HAL_StatusTypeDef ret;

    //Timer Base Config
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        ret = HRPWM_Mst_WaveformTmrCfg(Handle, pCfg);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
            return HAL_INVALID;
        }

        ret = HRPWM_Slv_WaveformTmrCfg(Handle, PwmIdx, pCfg);
    }

    if (ret != HAL_OK) {
        return ret;
    } else {
        return HRPWM_ForceRegistersUpdate(Handle, PwmIdx);
    }
}

/**
  * @brief  HRPWM HAL Timer Control
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Timer to be Config
  * @param  pCfg pointer to the timer control structure
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformTimerControl(HAL_HRPWM_HandleTypeDef *Handle,
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 const HAL_HRPWM_TimerCtlTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    HAL_StatusTypeDef ret;

    //Timer Base Config
    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        ret =  HRPWM_Slv_WaveformTimerCtl(Handle, PwmIdx, pCfg);
    } else {
        return HAL_INVALID;
    }

    if (ret != HAL_OK) {
        return ret;
    } else {
        return HRPWM_ForceRegistersUpdate(Handle, PwmIdx);
    } 
}

/**
  * @brief  HRPWM HAL Dual Channel Dac Configuration
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Timer to be Config
  * @param  pCfg pointer to the timer control structure
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_DualChannelDacConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 const HAL_HRPWM_DualDacCtlTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    //Dual Channel Dac Config
    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_DualDacCfg(Handle, PwmIdx, pCfg);
    } else {
        return HAL_INVALID;
    }
}

/**
  * @brief  HRPWM HAL Timer Compare Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Timer Compare to be Config, include Master PWM
  * @param  CmpUnit Compare unit to configure
  * @param  pCfg Timer Compare Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformCompareConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                  HAL_HRPWM_CmpUnitTypeDef CmpUnit, 
                                                  const HAL_HRPWM_CompareCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) ) {
            return HAL_INVALID;
        }        
    });


    //Timer Compare Config
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        return HRPWM_Mst_WaveformCmpCfg(Handle, CmpUnit, pCfg);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        HAL_HRPWM_PARAM_CHECK({
            if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                return HAL_INVALID;
            }    
        });


        return HRPWM_Slv_WaveformCmpCfg(Handle, PwmIdx, CmpUnit, pCfg);
    }
}

/**
  * @brief  HRPWM HAL System DMA Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx System DMA to be Config, include Master PWM
  * @param  pCfg System DMA Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_SysDMAConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                         const HAL_HRPWM_SysDMACfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) ) {
            return HAL_INVALID;
        }        
    });


    HAL_StatusTypeDef ret;

    ret = HRPWM_SysDMACfg(Handle, PwmIdx, pCfg);
    if (ret != HAL_OK) {
        return ret;
    }

    return HRPWM_ForceRegistersUpdate(Handle, PwmIdx);
}

/**
  * @brief  HRPWM HAL Slave PWMx Timer Roll-Over Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Roll-Over to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Timer Roll-Over Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_RollOverModeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                               const HAL_HRPWM_RollOverModeCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_RollOverModeCfg(Handle, PwmIdx, pCfg);
    } else {
        return HAL_INVALID;
    }
}

/**
  * @brief  HRPWM HAL Slave PWMx Timer Event Filter Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Event Filter to be Config, not include Master PWM
  * @param  EvtNum External Event Number to be Config
  * @param  pCfg Slave PWMx Timer Event Filter Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_TimerEventFilteringConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                      HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                      HAL_HRPWM_ExtEvtNumTypeDef EvtNum, 
                                                      const HAL_HRPWM_TimerEventFilteringCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);
    ASSERT_FUNC_PARAM(EvtNum < HAL_HRPWM_EXT_EVT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || 
            (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) || (EvtNum >= HAL_HRPWM_EXT_EVT_NUMS)) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_TmrEvtFilCfg(Handle, PwmIdx, EvtNum, pCfg);
    } else {
        return HAL_INVALID;
    }
}

/**
  * @brief  HRPWM HAL Slave PWMx Timer Event A Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Event A to be Config, not include Master PWM
  * @param  EvtCntr External event Counter for which timer event must be configured
  * @param  pCfg Slave PWMx Timer Event A Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                  HAL_HRPWM_EvtCntrTypeDef EvtCntr, 
                                                  const HAL_HRPWM_ExternalEventCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_ExtEvtCntrCfg(Handle, PwmIdx, EvtCntr, pCfg);
    } else {
        return HAL_INVALID;
    }
}

/**
  * @brief  HRPWM HAL PWMx Output Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  Channel PWM output channel
  * @param  pCfg PWM Output Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformOutputConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 HAL_HRPWM_OutputChnlTypeDef Channel,
                                                 const HAL_HRPWM_OutputCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_WaveformOutputCfg(Handle, PwmIdx, Channel, pCfg);
    } else {
        return HAL_INVALID;
    }
}

/**
  * @brief  HRPWM HAL Slave PWMx DeadTime Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx DeadTime to be Config, not include Master PWM
  * @param  pCfg Slave PWMx DeadTime Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_DeadTimeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                           const HAL_HRPWM_DeadTimeCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_DeadTimeCfg(Handle, PwmIdx, pCfg);
    } else {
        return HAL_INVALID;
    }
}


/**
  * @brief  HRPWM HAL Slave PWMx Chopper Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Chopper to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Chopper Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_ChopperModeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                              const HAL_HRPWM_ChopperModeCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_ChopModeCfg(Handle, PwmIdx, pCfg);
    } else {
        return HAL_INVALID;
    }
}

/**
  * @brief  HRPWM HAL PWM Capture Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Capture to be Config, not include Master PWM
  * @param  Channel PWM Capture Channel
  * @param  pCfg PWM Capture Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformCaptureConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                  HAL_HRPWM_CapChnlTypeDef Channel,
                                                  const HAL_HRPWM_CaptureCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_WaveformCapCfg(Handle, PwmIdx, Channel, pCfg);
    } else {
        return HAL_INVALID;
    }
}


/**
  * @brief HRPWM HAL Slave PWMx Capture Mode Config
  * @param Handle HRPWM Handle
  * @param PwmIdx Indicate which PWMx Capture Mode to be Config, not include Master PWM
  * @param Channel PWM Capture Channel
  * @param Mode PWM Capture Mode (Normal/Timeout)
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_CaptureModeConfig(HAL_HRPWM_HandleTypeDef*Handle,
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                              HAL_HRPWM_CapChnlTypeDef Channel,
                                              HAL_HRPWM_Slv_CapModeTypeDef Mode)
{
    ASSERT_FUNC_PARAM(Handle!=NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) ||(PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return HAL_INVALID;
        }
    });

    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        if (Channel==HAL_HRPWM_CAP_CHNL_A) {
            LL_HRPWM_SLV_SetCaptureAMode(Handle->Instance, PwmIdx, Mode);
        }else if(Channel==HAL_HRPWM_CAP_CHNL_B) {
            LL_HRPWM_SLV_SetCaptureBMode(Handle->Instance, PwmIdx, Mode);
        }else{
            return HAL_INVALID;
        }    
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the external event sample clock prescaler
  * @param  Handle HRPWM Handle
  * @param  Prescaler External Event Sample Clock Division
  * @note This function must be called before starting the timer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRPWM_EventPrescalerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                 HAL_HRPWM_Comm_ExtEvtSampClkDivTypeDef Prescaler)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    LL_HRPWM_COM_EE_SetPrescaler(Handle->Instance, Prescaler);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Common External Event Config
  * @param  Handle HRPWM Handle
  * @param  EvtNum External Event Nubmer Which to be Config
  * @param  pCfg Common External Event Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_EventConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                        HAL_HRPWM_ExtEvtNumTypeDef EvtNum,
                                        const HAL_HRPWM_EventCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(EvtNum < HAL_HRPWM_EXT_EVT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (EvtNum >= HAL_HRPWM_EXT_EVT_NUMS)) {
            return HAL_INVALID;
        }        
    });


    return HRPWM_Comm_ExtEvtCfg(Handle, EvtNum, pCfg);
}

/**
  * @brief  Configure the fault conditioning block prescaler
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  Prescaler Fault Sample Clock Division
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_FaultPrescalerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                 HAL_HRPWM_FltNumTypeDef FltNum, 
                                                 HAL_HRPWM_Comm_FltSampClkDivTypeDef Prescaler)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(FltNum < HAL_HRPWM_FLT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (FltNum >= HAL_HRPWM_FLT_NUMS)) {
            return HAL_INVALID;
        }        
    });


    LL_HRPWM_COM_FLT_SetPrescaler(Handle->Instance, Prescaler);

    return HAL_OK;
}


/**
  * @brief  HRPWM HAL Common Fault Config
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  pCfg Common Fault Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_FaultConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                        HAL_HRPWM_FltNumTypeDef FltNum, 
                                        const HAL_HRPWM_FaultCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(FltNum < HAL_HRPWM_FLT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (FltNum >= HAL_HRPWM_FLT_NUMS)) {
            return HAL_INVALID;
        }        
    });


    return HRPWM_Comm_FltCfg(Handle, FltNum, pCfg);
}

/**
  * @brief  HRPWM HAL Common Fault Counter Config
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  pCfg Common Fault Counter Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_FaultCounterConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_FltNumTypeDef FltNum, 
                                               const HAL_HRPWM_FaultCntrCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(FltNum < HAL_HRPWM_FLT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (FltNum >= HAL_HRPWM_FLT_NUMS)) {
            return HAL_INVALID;
        }        
    });


    return HRPWM_Comm_FltCntrCfg(Handle, FltNum, pCfg);
}

/**
  * @brief  HRPWM HAL Common Fault Blanking Config and Enable
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  pCfg Common Fault Counter Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_FaultBlankingConfigAndEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                                        HAL_HRPWM_FltNumTypeDef FltNum, 
                                                        const HAL_HRPWM_FaultBlankingCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(FltNum < HAL_HRPWM_FLT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (FltNum >= HAL_HRPWM_FLT_NUMS)) {
            return HAL_INVALID;
        }        
    });


    return HRPWM_Comm_FltBlkCfg(Handle, FltNum, pCfg);
}

/**
  * @brief  Enable or disables the HRPWM Fault mode.
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  Enable Fault(s) enabling
  * @retval None
  */
HAL_StatusTypeDef HAL_HRPWM_FaultModeCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_FltNumTypeDef FltNum, 
                                         HAL_HRPWM_EnableTypeDef Enable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(FltNum < HAL_HRPWM_FLT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (FltNum >= HAL_HRPWM_FLT_NUMS)) {
            return HAL_INVALID;
        }        
    });


    HAL_FUNC_ALTER(Enable,  LL_HRPWM_COM_LL_HRTIM_FLT_Enable(Handle->Instance, FltNum), 
                            LL_HRPWM_COM_LL_HRTIM_FLT_Disable(Handle->Instance, FltNum));

    return HAL_OK;
}

/**
  * @brief  Configure the ADC trigger postscaler register of the ADC
  * @param  Handle HRPWM Handle
  * @param  TrigNum ADC Trigger Number Which to be Config
  * @param  Postscaler Common ADC Trigger Postscaler
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_ADCPostScalerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                HAL_HRPWM_ADCTrigNumTypeDef TrigNum,
                                                uint32_t Postscaler)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(TrigNum < HAL_HRPWM_ADC_TRIG_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (TrigNum >= HAL_HRPWM_ADC_TRIG_NUMS)) {
            return HAL_INVALID;
        }        
    });


    LL_HRPWM_COM_SetADCTriggerPostScaler(Handle->Instance, TrigNum, Postscaler);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Common ADC Trigger Config
  * @param  Handle HRPWM Handle
  * @param  TrigNum ADC Trigger Number Which to be Config
  * @param  pCfg Common ADC Trigger Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_ADCTriggerConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                            HAL_HRPWM_ADCTrigNumTypeDef TrigNum,
                                            const HAL_HRPWM_ADCTriggerCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(TrigNum < HAL_HRPWM_ADC_TRIG_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL) || (TrigNum >= HAL_HRPWM_ADC_TRIG_NUMS)) {
            return HAL_INVALID;
        }        
    });


    return HRPWM_Comm_ADCTrigCfg(Handle, TrigNum, pCfg);
}

/**
  * @brief  HRPWM HAL Common DLL Current Config
  * @param  Handle HRPWM Handle
  * @param  Current DLL Current
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_DLLCurrentConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                             HAL_HRPWM_Comm_DLLCurTypeDef Current)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });


    LL_HRPWM_COM_SetDLLCurrent(Handle->Instance, Current);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Common Burst Mode Config
  * @param  Handle HRPWM Handle
  * @param  pCfg Common Burst Mode Config Pointer
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_BurstModeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                            const HAL_HRPWM_BurstModeCfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(pCfg != NULL);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (pCfg == NULL)) {
            return HAL_INVALID;
        }        
    });


    return HRPWM_Comm_BurstModeCfg(Handle, pCfg);
}

/**
  * @brief  Configure the burst DMA controller for a PWM
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Register Update, include Master PWM
  * @param  Registers registers to be written by DMA, combination of @ref HAL_HRPWM_BurstDMARegUpdTypeDef
  *                 Master @ref HAL_HRPWM_BurstDMAMstRegUpdTypeDef
  *                 Slave @ref HAL_HRPWM_BurstDMASlvRegUpdTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRPWM_BurstDMAConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                           HAL_HRPWM_BurstDMARegUpdTypeDef Registers)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        LL_HRPWM_COM_SetBurstDMAMasterPWMRegUpdate(p_instance, (HAL_HRPWM_BurstDMAMstRegUpdTypeDef)Registers);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        HAL_HRPWM_PARAM_CHECK({
            if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                return HAL_INVALID;
            }        
        });

        LL_HRPWM_COM_SetBurstDMASlavePWMxRegUpdate(p_instance, PwmIdx, (HAL_HRPWM_BurstDMASlvRegUpdTypeDef)Registers);
    }

    return HAL_OK;
}

/**
  * @brief  Enable or disables the HRPWM burst DMA update. (Default: enable, allow update)
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Register Update, include Master PWM
  * @param  Enable Burst DMA update enabling
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRPWM_BurstDMAUpdateCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                              HAL_HRPWM_EnableTypeDef Enable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
        return HAL_INVALID;
    }

    HAL_StatusTypeDef status = HAL_OK;

    //If disabled, the burst mode Compare Value and Period will not be updated.
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        status = HRPWM_Mst_BurstDMAUpdateCtl(Handle, Enable);

    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        HAL_HRPWM_PARAM_CHECK({
            if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                status = HAL_INVALID;
            }        
        });

        status = HRPWM_Slv_BurstDMAUpdateCtl(Handle, PwmIdx, Enable);
    }

    return status;
}

/**
  * @brief  Burst DMA buffer address config
  * @param  Instance Specifies HRPWM peripheral
  * @param  ReadWrite  burst DMA read or write
  * @param  BufferAddress address of the buffer the HRPWM control registers
  *                             content will be updated from.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRPWM_BurstBufferAddressConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                                     HAL_HRPWM_BurstDmaDirTypeDef ReadWrite,
                                                     uint32_t BufferAddress)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (ReadWrite == HAL_HRPWM_BURST_DMA_DIR_READ) {
        LL_HRPWM_COM_SetBurstDMAReadAddress(Handle->Instance, BufferAddress);
    } else if (ReadWrite == HAL_HRPWM_BURST_DMA_DIR_WRITE) {
        LL_HRPWM_COM_SetBurstDMAWriteAddress(Handle->Instance, BufferAddress);
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Enable or disables the HRPWM burst mode controller.
  * @param  Handle HRPWM Handle
  * @param  Enable Burst mode controller enabling
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRPWM_BurstModeCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                        HAL_HRPWM_EnableTypeDef Enable)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HAL_FUNC_ALTER(Enable,  LL_HRPWM_COM_BM_Enable(Handle->Instance), 
                            LL_HRPWM_COM_BM_Disable(Handle->Instance));

    return HAL_OK;
}

/**
  * @brief  Trig the burst mode operation.
  * @param  Handle HRPWM Handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRPWM_BurstModeSoftwareTrigger(HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_COM_BM_SetTrigEvt(Handle->Instance, LL_HRPWM_COMM_BURST_TRIG_EVT_SW);

    return HAL_OK;
}

/**
  * @brief  Configure the DMA Enable for a PWM
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Register Update, include Master PWM
  * @param  Mask registers to be written by DMA, combination of mask
  *                 Master @ref HAL_HRPWM_Mst_DMATypeDef
  *                 Slave @ref HAL_HRPWM_Slv_DMATypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRPWM_DMAEnableCtl(HAL_HRPWM_HandleTypeDef *Handle,
                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                         uint32_t Mask)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });

    HRPWM_TypeDef *p_instance = Handle->Instance;

    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        ASSERT_FUNC_PARAM(IS_HRPWM_MST_DMA(Mask));

        LL_HRPWM_MST_SetMultiDMAEnable(p_instance, (HAL_HRPWM_Mst_DMATypeDef)Mask);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);
        ASSERT_FUNC_PARAM(IS_HRPWM_SLV_DMA(Mask));

        HAL_HRPWM_PARAM_CHECK({
            if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                return HAL_INVALID;
            }        
        });

        LL_HRPWM_SLV_SetMultiDMAEnable(p_instance, PwmIdx, (HAL_HRPWM_Slv_DMATypeDef)Mask);
    }

    return HAL_OK;
}

/**
  * @}
  */ /* HRPWM_HAL_EF_Configuration */


/** @defgroup HRPWM_HAL_EF_Operation HRPWM Operation Functions
  * @brief    HRPWM Operation Functions
  * @{
  */

/**
  * @brief  HRPWM HAL PWMx Timer Counter Start
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Timer Counter to be Start, include Master PWM
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_SimpleBaseStart(HAL_HRPWM_HandleTypeDef *Handle, 
                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    //PWM Timer Counter Enable
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        LL_HRPWM_MST_EnableMasterPWM(p_instance);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        HAL_HRPWM_PARAM_CHECK({
            if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                return HAL_INVALID;
            }
        });


        LL_HRPWM_MST_EnablePWMx(p_instance, PwmIdx);
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi PWMx Timer Counter Start Simultaneously
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Timer Counter to be Start, include Master PWM, combination of @ref HAL_HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformCountStart(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_MST_CounterEnable(Handle->Instance, PwmMsk);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL PWMx Timer Counter Stop
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Timer Counter to be Stop, include Master PWM
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_SimpleBaseStop(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    //PWM Timer Counter Disable
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        LL_HRPWM_MST_DisableMasterPWM(p_instance);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        HAL_HRPWM_PARAM_CHECK({
            if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                return HAL_INVALID;
            }
        });


        LL_HRPWM_MST_DisablePWMx(p_instance, PwmIdx);
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi PWMx Timer Counter Stop Simultaneously
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Timer Counter to be Stop, include Master PWM, combination of @ref HAL_HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformCountStop(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_MST_CounterDisable(Handle->Instance, PwmMsk);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi PWMx Timer Counter Reset
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Timer Counter to be Reset, include Master PWM, combination of @ref HAL_HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_SoftwareReset(HAL_HRPWM_HandleTypeDef *Handle, 
                                          HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart = HAL_GetTick();

    LL_HRPWM_COM_ResetMultiPWMCounters(p_instance, PwmMsk);

    //Wait for Reset complete
    while (LL_HRPWM_COM_IsMultiPWMCountersResetting(p_instance, PwmMsk)) {
        if ((HAL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi Slave PWMx Output Start
  * @param  Handle HRPWM Handle
  * @param  OutputChannels Output channel start mask, combination of @ref HAL_HRPWM_PWMOutputMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformOutputStart(HAL_HRPWM_HandleTypeDef *Handle, 
                                                HAL_HRPWM_PWMOutputMaskTypeDef OutputChannels)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_COM_EnableOutput(Handle->Instance, OutputChannels);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi Slave PWMx Output Stop
  * @param  Handle HRPWM Handle
  * @param  OutputChannels Output channel stop mask, combination of @ref HAL_HRPWM_PWMOutputMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformOutputStop(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_PWMOutputMaskTypeDef OutputChannels)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_COM_DisableOutput(Handle->Instance, OutputChannels);

    return HAL_OK;
}


/**
  * @brief  HRPWM HAL Force the PWMx output to its active or inactive state
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  Channel PWM output channel
  * @param  Output The output is forced to its active or inactive level
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_WaveformSetOutputLevel(HAL_HRPWM_HandleTypeDef *Handle, 
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                   HAL_HRPWM_OutputChnlTypeDef Channel,
                                                   HAL_HRPWM_Slv_OutLvlStateTypeDef Output)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_SwTrigOutLvl(Handle, PwmIdx, Channel, Output);
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi PWMx Output Swap Enable
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Output to be Swap Enable, not include Master PWM, combination of @ref HAL_HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_OutputSwapEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                             HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_COM_EnableMultiPWMOutputSwap(Handle->Instance, PwmMsk);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi PWMx Output Swap Disable
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Output to be Swap Disable, not include Master PWM, combination of @ref HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_OutputSwapDisable(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_COM_DisableMultiPWMOutputSwap(Handle->Instance, PwmMsk);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi Register Update Enable
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Register Update to be Enable, include Master PWM, combination of @ref HAL_HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_UpdateEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_COM_EnableMultiPWMRegUpdate(Handle->Instance, PwmMsk);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi Register Update Disable
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Register Update to be Disable, include Master PWM, combination of @ref HAL_HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_UpdateDisable(HAL_HRPWM_HandleTypeDef *Handle, 
                                          HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    LL_HRPWM_COM_DisableMultiPWMRegUpdate(Handle->Instance, PwmMsk);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Multi Register Update Software Force
  * @note   Several configuration functions in the HRPWM HAL do not immediately
  *         force a register update. When preload is enabled, values written by
  *         some functions are only transferred to the active registers on the 
  *         next update event (hardware update or software force).
  *         To ensure that all pending configurations take effect immediately,
  *         call HAL_HRPWM_SoftwareUpdate() after completing the desired
  *         register setup. This is especially important when preload is enabled.
  * @param  Handle HRPWM Handle
  * @param  PwmMsk Indicate Multi PWMx Register Update to be Force, include Master PWM, combination of @ref HAL_HRPWM_PWMMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_SoftwareUpdate(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMMaskTypeDef PwmMsk)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart = HAL_GetTick();

    LL_HRPWM_COM_ForceUpdate(p_instance, PwmMsk);

    //Wait for update complete
    while (LL_HRPWM_COM_IsMultiPWMUpdateBusy(p_instance, PwmMsk)) {
        if ((HAL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Common DLL Start
  * @param  Handle HRPWM Handle
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_DLLStart(HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    //DLL Enable
    LL_HRPWM_COM_EnableDLL(p_instance);

    //DLL Start
    LL_HRPWM_COM_StartDLLCalibration(p_instance);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Common DLL Stop
  * @param  Handle HRPWM Handle
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_DLLStop(HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    //DLL Stop
    LL_HRPWM_COM_StopDLLCalibration(p_instance);

    //DLL Disable
    LL_HRPWM_COM_DisableDLL(p_instance);

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Common Fault Counter Reset
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which Counter to be Reset
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_FaultCounterReset(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_FltNumTypeDef FltNum)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(FltNum < HAL_HRPWM_FLT_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (FltNum >= HAL_HRPWM_FLT_NUMS)) {
            return HAL_INVALID;
        }
    });


    //Common Fault X Counter Reset
    LL_HRPWM_COM_FLT_ResetCounter(Handle->Instance, FltNum);

    return HAL_OK;
}


/**
  * @brief  HRPWM HAL Slave PWMx Timer Event A Enable
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Event A to be enabled, not include Master PWM
  * @param  EvtCntr External event Counter for which timer event must be enabled
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                  HAL_HRPWM_EvtCntrTypeDef EvtCntr)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        if (EvtCntr == HAL_HRPWM_EVT_CNTR_A) {
            LL_HRPWM_SLV_EnableEventCounter(Handle->Instance, PwmIdx);
        } else {
            return HAL_INVALID;
        }
        
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Slave PWMx Timer Event A Disable
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Event A to be disabled, not include Master PWM
  * @param  EvtCntr External event Counter for which timer event must be disabled
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterDisable(HAL_HRPWM_HandleTypeDef *Handle, 
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                   HAL_HRPWM_EvtCntrTypeDef EvtCntr)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        if (EvtCntr == HAL_HRPWM_EVT_CNTR_A) {
            LL_HRPWM_SLV_DisableEventCounter(Handle->Instance, PwmIdx);
        } else {
            return HAL_INVALID;
        }

    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Slave PWMx Timer Event A Reset
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Event A to be reset, not include Master PWM
  * @param  EvtCntr External event Counter for which timer event must be reset
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterReset(HAL_HRPWM_HandleTypeDef *Handle, 
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 HAL_HRPWM_EvtCntrTypeDef EvtCntr)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });


    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        if (EvtCntr == HAL_HRPWM_EVT_CNTR_A) {
            LL_HRPWM_SLV_ResetEventCounter(Handle->Instance, PwmIdx);
        } else {
            return HAL_INVALID;
        }
        
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Trigger a software capture
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Capture value to be read, not include Master PWM
  * @param  Channel PWM Capture Channel
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_SoftwareCapture(HAL_HRPWM_HandleTypeDef *Handle, 
                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                            HAL_HRPWM_CapChnlTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }
    });

    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        if (Channel == HAL_HRPWM_CAP_CHNL_A) { 
            LL_HRPWM_SLV_SetCaptureATrig(Handle->Instance, PwmIdx, LL_HRPWM_SLV_CAP_TRIG_EVT_SW_CAP);
        } else if (Channel == HAL_HRPWM_CAP_CHNL_B) {
            LL_HRPWM_SLV_SetCaptureBTrig(Handle->Instance, PwmIdx, LL_HRPWM_SLV_CAP_TRIG_EVT_SW_CAP);
        }else {
            return HAL_INVALID;
        }

    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @}
  */ /* HRPWM_HAL_EF_Operation */

/** @defgroup HRPWM_HAL_EF_State HRPWM State Functions
  * @brief    HRPWM State Functions
  * @{
  */

/**
  * @brief  Return actual value and direction of the capture register of the designated capture unit
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Capture value to be read, not include Master PWM
  * @param  Channel PWM Capture Channel
  * @param  Captured captured value and direction structure (0xFFFFFFFFUL represents an invalid value)
  * @return None
  */
void HAL_HRPWM_GetCaptured(const HAL_HRPWM_HandleTypeDef *Handle, 
                           HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                           HAL_HRPWM_CapChnlTypeDef Channel,
                           HAL_HRPWM_CaptureValueTypeDef *Captured)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(Captured != NULL);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (Captured == NULL)) {
            return;
        }        
    });

    HAL_HRPWM_CaptureValueTypeDef temp = {
        .Value = 0xFFFFFFFFUL,
        .Dir = 0xFFFFFFFFUL
    };

    /* Read captured value */
    if (Channel == HAL_HRPWM_CAP_CHNL_A) {
        LL_HRPWM_SLV_GetCaptureAValueAndDirection(Handle->Instance, PwmIdx, &temp.Value, &temp.Dir);
    } else if (Channel == HAL_HRPWM_CAP_CHNL_B) {
        LL_HRPWM_SLV_GetCaptureBValueAndDirection(Handle->Instance, PwmIdx, &temp.Value, &temp.Dir);
    }

    Captured->Value = temp.Value;
    Captured->Dir = temp.Dir;
}

/**
  * @brief  Return actual level (active or inactive) of the designated output
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Output level to be read, not include Master PWM
  * @param  Channel PWM output channel
  * @retval 0xFFFFFFFF: Invalid value
  * @retval 0: Output Invalid
  * @retval 1: Output valid
  */
uint32_t HAL_HRPWM_WaveformGetOutputLevel(const HAL_HRPWM_HandleTypeDef *Handle,
                                          HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                          HAL_HRPWM_OutputChnlTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return 0xFFFFFFFFUL;
        }        
    });

    HRPWM_TypeDef *p_instance = Handle->Instance;

    if (Channel == HAL_HRPWM_OUTPUT_CHNL_A) {
        return LL_HRPWM_SLV_GetOutputA(p_instance, PwmIdx);
    } else if (Channel == HAL_HRPWM_OUTPUT_CHNL_B) {
        return LL_HRPWM_SLV_GetOutputB(p_instance, PwmIdx);
    } else {
        return 0xFFFFFFFFUL;
    }
}

/**
  * @brief  Return the level (active or inactive) of the designated output
  *         when the delayed protection was triggered.
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Output level to be read, not include Master PWM
  * @param  Channel PWM output channel
  * @retval 0xFFFFFFFF: Invalid value
  * @retval 0: Output Invalid
  * @retval 1: Output valid
  */
uint32_t HAL_HRPWM_GetDelayedProtectionStatus(const HAL_HRPWM_HandleTypeDef *Handle,
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                              HAL_HRPWM_OutputChnlTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return 0xFFFFFFFFUL;
        }        
    });

    HRPWM_TypeDef *p_instance = Handle->Instance;

    if (Channel == HAL_HRPWM_OUTPUT_CHNL_A) {
        return LL_HRPWM_SLV_GetOutputAProtection(p_instance, PwmIdx);
    } else if (Channel == HAL_HRPWM_OUTPUT_CHNL_B) {
        return LL_HRPWM_SLV_GetOutputBProtection(p_instance, PwmIdx);
    } else {
        return 0xFFFFFFFFUL;
    }
}

/**
  * @brief  Indicate on which output the signal is currently active (when the
  *         push pull mode is enabled).
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Output level to be read, not include Master PWM
  * @retval 0xFFFFFFFF: Invalid value
  * @retval 0: OUTA Push-Pull Output, OUTB Force Invalid
  * @retval 1: OUTB Push-Pull Output, OUTA Force Invalid
  */
uint32_t HAL_HRPWM_GetCurrentPushPullStatus(const HAL_HRPWM_HandleTypeDef *Handle,
                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return 0xFFFFFFFFUL;
        }        
    });

    return LL_HRPWM_SLV_GetCurrentPushPullStatus(Handle->Instance, PwmIdx);
}

/**
  * @brief  Indicate on which output the signal was applied, in push-pull mode,
            balanced fault mode or delayed idle mode, when the protection was triggered.
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Output level to be read, not include Master PWM
  * @retval 0xFFFFFFFF: Invalid value
  * @retval 0: OUTA Push-Pull Output, OUTB Force Invalid
  * @retval 1: OUTB Push-Pull Output, OUTA Force Invalid
  */
uint32_t HAL_HRPWM_GetIdlePushPullStatus(const HAL_HRPWM_HandleTypeDef *Handle,
                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return 0xFFFFFFFFUL;
        }        
    });

    return LL_HRPWM_SLV_GetIdlePushPullStatus(Handle->Instance, PwmIdx);
}

/**
  * @brief  Indicate on which output the signal was applied, in push-pull mode,
            balanced fault mode or delayed idle mode, when the protection was triggered.
  * @param  Handle HRPWM Handle
  * @retval 0xFFFFFFFF: Invalid value
  * @retval 0: Common Burst Mode is Inactive
  * @retval 1: Common Burst Mode is Active
  */
uint32_t HAL_HRPWM_GetBurstStatus(const HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return 0xFFFFFFFFUL;
        }        
    });

    return LL_HRPWM_COM_BM_GetStatus(Handle->Instance);
}

/**
  * @brief  HRPWM HAL Return actual state (RUN, IDLE, FAULT) 
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  Channel PWM output channel
  * @return HRPWM Slave Output Level Status
  */
HAL_HRPWM_Slv_OutStateTypeDef HAL_HRPWM_WaveformGetOutputState(const HAL_HRPWM_HandleTypeDef *Handle, 
                                                               HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                               HAL_HRPWM_OutputChnlTypeDef Channel)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    if (PwmIdx < HAL_HRPWM_SLV_PWM_NUMS) {
        return HRPWM_Slv_OutputState(Handle, PwmIdx, Channel);
    } else {
        return HAL_HRPWM_SLV_OUT_STATE_FAULT;
    }
}

/**
  * @}
  */ /* HRPWM_HAL_EF_State */

/** @defgroup HRPWM_HAL_EF_Interrupt HRPWM Interrupt Handler and Callback
  * @brief    HRPWM Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  HRPWM HAL Interrupt Requests Enable
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Requests to be enable, include Master PWM
  * @param  Group Indicate which group interrupt request to be config
  * @param  InterruptRequests Interrupt Requests
  *             For HAL_HRPWM_GRP_MASTER @ref HAL_HRPWM_MstITEnMaskTypeDef
  *             For HAL_HRPWM_GRP_SLAVE  @ref HAL_HRPWM_SlvITEnMaskTypeDef
  *             For HAL_HRPWM_GRP_COMMON @ref HAL_HRPWM_ComITEnMaskTypeDef
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_InterruptRequestEnable(HAL_HRPWM_HandleTypeDef *Handle,
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,  
                                                   HAL_HRPWM_PWMGrpTypeDef Group,
                                                   uint32_t InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });

    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Interrupt Requests Config
    switch (Group) {
        case HAL_HRPWM_GRP_MASTER:
            ASSERT_FUNC_PARAM(PwmIdx == HAL_HRPWM_MST_PWM);

            HAL_HRPWM_PARAM_CHECK({
                if (PwmIdx != HAL_HRPWM_MST_PWM) {
                    return HAL_INVALID;
                }        
            });

            LL_HRPWM_MST_EnableIT(p_instance, InterruptRequests);
            break;

        case HAL_HRPWM_GRP_SLAVE:
            ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

            HAL_HRPWM_PARAM_CHECK({
                if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                    return HAL_INVALID;
                }    
            });

            LL_HRPWM_SLV_EnableIT(p_instance, PwmIdx, InterruptRequests);
            break;

        case HAL_HRPWM_GRP_COMMON:
            LL_HRPWM_COM_EnableIT(p_instance, InterruptRequests);
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Interrupt Requests Disable
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Requests to be disable, include Master PWM
  * @param  Group Indicate which group interrupt request to be config
  * @param  InterruptRequests
  * @return HAL Status
  */
HAL_StatusTypeDef HAL_HRPWM_InterruptRequestDisable(HAL_HRPWM_HandleTypeDef *Handle,
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,  
                                                   HAL_HRPWM_PWMGrpTypeDef Group,
                                                   uint32_t InterruptRequests)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });

    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Interrupt Requests Config
    switch (Group) {
        case HAL_HRPWM_GRP_MASTER:
            ASSERT_FUNC_PARAM(PwmIdx == HAL_HRPWM_MST_PWM);

            HAL_HRPWM_PARAM_CHECK({
                if (PwmIdx != HAL_HRPWM_MST_PWM) {
                    return HAL_INVALID;
                }        
            });

            LL_HRPWM_MST_DisableIT(p_instance, InterruptRequests);
            break;

        case HAL_HRPWM_GRP_SLAVE:
            ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

            HAL_HRPWM_PARAM_CHECK({
                if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
                    return HAL_INVALID;
                }    
            });

            LL_HRPWM_SLV_DisableIT(p_instance, PwmIdx, InterruptRequests);
            break;

        case HAL_HRPWM_GRP_COMMON:
            LL_HRPWM_COM_DisableIT(p_instance, InterruptRequests);
            break;

        default:
            return HAL_INVALID;
    }

    return HAL_OK;
}


/**
  * @brief  HRPWM Master IRQ Handler
  * @param  Handle HRPWM Handle
  * @return None
  */
void HAL_HRPWM_MST_IRQHandler(HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return ;
        }
    });

    HRPWM_TypeDef *p_instance = Handle->Instance;

    /* Logical AND between flags status and interrupts sources enabled (for registers bitfields aligned) */
    const uint32_t int_en = LL_HRPWM_MST_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_HRPWM_Mst_AllIntPnd_Get(p_instance);
    const uint32_t flag_status_masked = (int_pending & int_en); 


    //Compare A Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MCMPA)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MCMPA(p_instance);

        //Callback
        HAL_HRPWM_MST_CompareAEventCallback(Handle);
    }

    //Compare B Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MCMPB)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MCMPB(p_instance);

        //Callback
        HAL_HRPWM_MST_CompareBEventCallback(Handle);
    }

    //Compare C Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MCMPC)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MCMPC(p_instance);

        //Callback
        HAL_HRPWM_MST_CompareCEventCallback(Handle);
    }

    //Compare D Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MCMPD)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MCMPD(p_instance);

        //Callback
        HAL_HRPWM_MST_CompareDEventCallback(Handle);
    }

    //Period Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MPER)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MPER(p_instance);

        //Callback
        HAL_HRPWM_MST_PeriodEventCallback(Handle);
    }

    //Sync Input Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_SYNC)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_SYNC(p_instance);

        //Callback
        HAL_HRPWM_MST_SynchronizationEventCallback(Handle);
    }

    //Update Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MUPD)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MUPD(p_instance);

        //Callback
        HAL_HRPWM_MST_RegistersUpdateCallback(Handle);
    }

    //Reset Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MRST)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MRST(p_instance);

        //Callback
        HAL_HRPWM_MST_CounterResetCallback(Handle);
    }

    //Repetition Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_MST_MISR_MREP)) {
        //Clear Interrupt Pending
        LL_HRPWM_MST_ClearFlag_MREP(p_instance);

        //Callback
        HAL_HRPWM_MST_RepetitionEventCallback(Handle);
    }
}

/**
  * @brief  HRPWM Master Compare A Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_CompareAEventCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_CompareAEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Compare B Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_CompareBEventCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_CompareBEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Compare C Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_CompareCEventCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_CompareCEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Compare D Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_CompareDEventCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_CompareDEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Period Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_PeriodEventCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_PeriodEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Sync Input Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_SynchronizationEventCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_SynchronizationEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Update Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_RegistersUpdateCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_RegistersUpdateCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Reset Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_CounterResetCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_CounterResetCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Repetition Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_MST_RepetitionEventCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_MST_RepetitionEventCallback could be implemented in the user file
     */
}


/**
  * @brief  HRPWM Slave IRQ Handler
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt to be Handler, not include Master PWM
  * @return None
  */
void HAL_HRPWM_SLV_IRQHandler(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));
    ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance)) || (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS)) {
            return;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    /* Logical AND between flags status and interrupts sources enabled (for registers bitfields aligned) */
    const uint32_t int_en = LL_HRPWM_SLV_GetAllEnabledIT(p_instance, PwmIdx);
    const uint32_t int_pending = LL_HRPWM_SLV_GetAllITPending(p_instance, PwmIdx);
    const uint32_t flag_status_masked = (int_pending & int_en); 


    //Compare A Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CMPA)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CMPA(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_CompareAEventCallback(Handle, PwmIdx);
    }

    //Compare B Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CMPB)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CMPB(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_CompareBEventCallback(Handle, PwmIdx);
    }

    //Compare C Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CMPC)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CMPC(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_CompareCEventCallback(Handle, PwmIdx);
    }

    //Compare D Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CMPD)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CMPD(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_CompareDEventCallback(Handle, PwmIdx);
    }

    //Period/Roll-Over Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_PER)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_PER(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_PeriodOrRollOverCallback(Handle, PwmIdx);
    }

    //Update Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_UPD)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_UPD(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_PeriodEventCallback(Handle, PwmIdx);
    }

    //OutA Set Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_SETA)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_SETA(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_OutputASetCallback(Handle, PwmIdx);
    }

    //OutA Clear Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CLRA)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CLRA(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_OutputAClearCallback(Handle, PwmIdx);
    }

    //OutB Set Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_SETB)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_SETB(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_OutputBSetCallback(Handle, PwmIdx);
    }

    //OutB Clear Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CLRB)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CLRB(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_OutputBClearCallback(Handle, PwmIdx);
    }

    //Reset Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_RST)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_RST(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_CounterResetCallback(Handle, PwmIdx);
    }

    //Repetition Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_REP)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_REP(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_RepetitionEventCallback(Handle, PwmIdx);
    }

    //Capture A Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CAPA)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CAPA(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_CaptureAEventCallback(Handle, PwmIdx);
    }

    //Capture B Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_CAPB)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_CAPB(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_CaptureBEventCallback(Handle, PwmIdx);
    }

    //Delayed Protection Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_SLV_PWMISR_DLYPRT)) {
        //Clear Interrupt Pending
        LL_HRPWM_SLV_ClearFlag_DLYPRT(p_instance, PwmIdx);

        //Callback
        HAL_HRPWM_SLV_DelayedProtectionCallback(Handle, PwmIdx);
    }
}

/**
  * @brief  HRPWM Slave PWMx Compare A Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_CompareAEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_CompareAEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Compare B Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_CompareBEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_CompareBEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Compare C Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_CompareCEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_CompareCEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Compare D Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_CompareDEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_CompareDEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Period/Roll-Over Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_PeriodOrRollOverCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_PeriodOrRollOverCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Update Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_PeriodEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_PeriodEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutA Set Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_OutputASetCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_OutputASetCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutA Clear Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_OutputAClearCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_OutputAClearCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutB Set Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_OutputBSetCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_OutputBSetCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutB Clear Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_OutputBClearCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_OutputBClearCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Reset Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_CounterResetCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_CounterResetCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Repetition Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_RepetitionEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_RepetitionEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Capture A Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_CaptureAEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_CaptureAEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Capture B Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_CaptureBEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_CaptureBEventCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Delayed Protection Interrupt Callback
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void HAL_HRPWM_SLV_DelayedProtectionCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);
    HAL_UNUSED(PwmIdx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_SLV_DelayedProtectionCallback could be implemented in the user file
     */
}


/**
  * @brief  HRPWM Common IRQ Handler
  * @param  Handle HRPWM Handle
  * @return None
  */
void HAL_HRPWM_COM_IRQHandler(HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    HAL_HRPWM_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_HRPWM_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });


    HRPWM_TypeDef *p_instance = Handle->Instance;

    /* Logical AND between flags status and interrupts sources enabled (for registers bitfields aligned) */
    const uint32_t int_en = LL_HRPWM_COM_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_HRPWM_COM_GetAllITPending(p_instance);
    const uint32_t flag_status_masked = (int_pending & int_en); 


    //Fault 0 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT0)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT0(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault0Callback(Handle);
    }

    //Fault 1 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT1)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT1(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault1Callback(Handle);
    }

    //Fault 2 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT2)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT2(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault2Callback(Handle);
    }

    //Fault 3 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT3)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT3(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault3Callback(Handle);
    }

    //Fault 4 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT4)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT4(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault4Callback(Handle);
    }

    //Fault 5 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT5)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT5(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault5Callback(Handle);
    }

    //Fault 6 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT6)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT6(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault6Callback(Handle);
    }

    //Fault 7 Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_FLT7)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_FLT7(p_instance);

        //Callback
        HAL_HRPWM_COM_Fault7Callback(Handle);
    }

    //System Fault Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_SYSFLT)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_SYSFLT(p_instance);

        //Callback
        HAL_HRPWM_COM_SystemFaultCallback(Handle);
    }

    //Burst Mode Period Interrupt Handler
    if ((flag_status_masked & LL_HRPWM_COM_ISR_BMPER)) {
        //Clear Interrupt Pending
        LL_HRPWM_COM_ClearFlag_BMPER(p_instance);

        //Callback
        HAL_HRPWM_COM_BurstModePeriodCallback(Handle);
    }
}

/**
  * @brief  HRPWM Common Fault 0 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault0Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault0Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 1 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault1Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault1Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 2 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault2Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault2Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 3 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault3Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault3Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 4 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault4Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault4Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 5 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault5Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault5Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 6 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault6Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault6Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 7 Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_Fault7Callback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_Fault7Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common System Fault Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_SystemFaultCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_SystemFaultCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Busrt Mode Period Interrupt Callback
  * @param  Handle HRPWM Handle
  * @return None
  */
__WEAK void HAL_HRPWM_COM_BurstModePeriodCallback(HAL_HRPWM_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_HRPWM_COM_BurstModePeriodCallback could be implemented in the user file
     */
}

/**
  * @}
  */ /* HRPWM_HAL_EF_Interrupt */

/**
  * @}
  */ /* HRPWM_HAL_Exported_Functions */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup HRPWM_HAL_Private_Functions
  * @{
  */

/**
  * @brief  HRPWM Master PWM Timer Base Config
  * @param  Handle HRPWM Handle
  * @param  pCfg Master PWM Timer Base Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_TimeBaseCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             const HAL_HRPWM_TimeBaseCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Master PWM Timer Base Config

    switch (pCfg->Mode) {
    case HAL_HRPWM_WORK_MODE_SINGLE:
        LL_HRPWM_MST_SetCounterMode(p_instance, LL_HRPWM_WORK_MODE_SINGLE);
        LL_HRPWM_MST_DisableRetriggerMode(p_instance);
        break;

    case HAL_HRPWM_WORK_MODE_CONTINUE:
        LL_HRPWM_MST_SetCounterMode(p_instance, LL_HRPWM_WORK_MODE_CONTINUE);
        break;

    case HAL_HRPWM_WORK_MODE_SINGLE_REP:
        LL_HRPWM_MST_SetCounterMode(p_instance, LL_HRPWM_WORK_MODE_SINGLE);
        LL_HRPWM_MST_EnableRetriggerMode(p_instance);
        break;

    default:
        return HAL_INVALID;
    }

    LL_HRPWM_MST_SetPrescaler(p_instance, pCfg->PrescalerRatio);
    LL_HRPWM_MST_SetRepetition(p_instance, pCfg->RepetitionCounter);
    LL_HRPWM_MST_SetPeriod(p_instance, pCfg->Period);

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Base Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Base to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Timer Base Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_TimeBaseCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                             const HAL_HRPWM_TimeBaseCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx Timer Base Config

    switch (pCfg->Mode) {
    case HAL_HRPWM_WORK_MODE_SINGLE:
        LL_HRPWM_SLV_SetCounterMode(p_instance, PwmIdx, LL_HRPWM_WORK_MODE_SINGLE);
        LL_HRPWM_SLV_DisableRetriggerMode(p_instance, PwmIdx);
        break;

    case HAL_HRPWM_WORK_MODE_CONTINUE:
        LL_HRPWM_SLV_SetCounterMode(p_instance, PwmIdx, LL_HRPWM_WORK_MODE_CONTINUE);
        break;

    case HAL_HRPWM_WORK_MODE_SINGLE_REP:
        LL_HRPWM_SLV_SetCounterMode(p_instance, PwmIdx, LL_HRPWM_WORK_MODE_SINGLE);
        LL_HRPWM_SLV_EnableRetriggerMode(p_instance, PwmIdx);
        break;

    default:
        return HAL_INVALID;
    }

    LL_HRPWM_SLV_SetPrescaler(p_instance, PwmIdx, pCfg->PrescalerRatio);
    LL_HRPWM_SLV_SetRepetition(p_instance, PwmIdx, pCfg->RepetitionCounter);
    LL_HRPWM_SLV_SetPeriod(p_instance, PwmIdx, pCfg->Period);
    return HAL_OK;
}


/**
  * @brief  HRPWM Master PWM Timer Config
  * @param  Handle HRPWM Handle
  * @param  pCfg Master PWM Timer Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_WaveformTmrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                const HAL_HRPWM_TimerCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    LL_HRPWM_MST_SetInterleavedMode(p_instance, pCfg->InterleavedMode);
    LL_HRPWM_MST_SetUpdateGating(p_instance, pCfg->MstUpdateGating);
    LL_HRPWM_MST_SetDACSyncSource(p_instance, pCfg->DACSynchro);

    HAL_FUNC_ALTER(pCfg->HalfModeEnable,    LL_HRPWM_MST_EnableHalfMode(p_instance), LL_HRPWM_MST_DisableHalfMode(p_instance));
    HAL_FUNC_ALTER(pCfg->StartOnSync,       LL_HRPWM_MST_EnableStartOnSync(p_instance), LL_HRPWM_MST_DisableStartOnSync(p_instance));
    HAL_FUNC_ALTER(pCfg->ResetOnSync,       LL_HRPWM_MST_EnableResetOnSync(p_instance), LL_HRPWM_MST_DisableResetOnSync(p_instance));
    HAL_FUNC_ALTER(pCfg->PreloadEnable,     LL_HRPWM_MST_EnablePreload(p_instance), LL_HRPWM_MST_DisablePreload(p_instance));
    HAL_FUNC_ALTER(pCfg->RepetitionUpdate,  LL_HRPWM_MST_EnableRepetitionUpdate(p_instance), LL_HRPWM_MST_DisableRepetitionUpdate(p_instance));
    HAL_FUNC_ALTER(pCfg->ResetUpdate,       LL_HRPWM_MST_EnableResetRollOverUpdate(p_instance), LL_HRPWM_MST_DisableResetRollOverUpdate(p_instance));

    if(pCfg->BurstMode == HAL_HRPWM_BURST_MODE_CNT_STOP) {
        LL_HRPWM_COM_BM_EnableMasterPWMCounterStop(p_instance);
    } else if (pCfg->BurstMode == HAL_HRPWM_BURST_MODE_CNT_KEEP) {
        LL_HRPWM_COM_BM_DisableMasterPWMCounterStop(p_instance);
    } else {
        //do nothing...
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Base to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Timer Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformTmrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                const HAL_HRPWM_TimerCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    LL_HRPWM_SLV_SetInterleavedMode(p_instance, PwmIdx, pCfg->InterleavedMode);
    LL_HRPWM_SLV_SetUpdateGating(p_instance, PwmIdx, pCfg->UpdateGating);
    LL_HRPWM_SLV_SetDACTrig(p_instance, PwmIdx, pCfg->DACSynchro);
    LL_HRPWM_SLV_SetResetTrig(p_instance, PwmIdx, pCfg->ResetTrigger);
    LL_HRPWM_SLV_SetUpdateTrigPWMx(p_instance, PwmIdx, pCfg->UpdateTrigger);
    LL_HRPWM_SLV_SetFaultChannel(p_instance, PwmIdx, pCfg->FaultEnable);

    HAL_FUNC_ALTER(pCfg->HalfModeEnable,    LL_HRPWM_SLV_EnableHalfMode(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisableHalfMode(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->StartOnSync,       LL_HRPWM_SLV_EnableStartOnSync(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisableStartOnSync(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->ResetOnSync,       LL_HRPWM_SLV_EnableResetOnSync(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisableResetOnSync(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->PreloadEnable,     LL_HRPWM_SLV_EnablePreload(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisablePreload(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->RepetitionUpdate,  LL_HRPWM_SLV_EnableRepetitionUpdate(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisableRepetitionUpdate(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->ResetUpdate,       LL_HRPWM_SLV_EnableResetRollOverUpdate(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisableResetRollOverUpdate(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->PushPull,          LL_HRPWM_SLV_EnablePushPullMode(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisablePushPullMode(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->DeadTimeInsertion, LL_HRPWM_SLV_EnableDeadTime(p_instance, PwmIdx), 
                                            LL_HRPWM_SLV_DisableDeadTime(p_instance, PwmIdx));

    //Balanced mode is available only in push-pull mode
    if ((pCfg->PushPull == HAL_HRPWM_FUNC_ENABLE) || 
        ((pCfg->DelayedProtectionMode != HAL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_BAL) && 
         (pCfg->DelayedProtectionMode != HAL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_BAL))) {
        
        //Is Enable Delayed Protection
        if (pCfg->DelayedProtectionMode != HAL_HRPWM_SLV_DLY_PROT_MECH_DISABLE) {
            LL_HRPWM_SLV_SetDLYPRTMode(p_instance, PwmIdx, pCfg->DelayedProtectionMode);
            LL_HRPWM_SLV_EnableDLYPRT(p_instance, PwmIdx);
        } else {
            LL_HRPWM_SLV_DisableDLYPRT(p_instance, PwmIdx);
        }
    } else {
        LL_HRPWM_SLV_DisableDLYPRT(p_instance, PwmIdx);
    }

    HAL_FUNC_ALTER(pCfg->BalancedIdleAutomaticResume,   LL_HRPWM_SLV_EnableBIAR(p_instance, PwmIdx),
                                                        LL_HRPWM_SLV_DisableBIAR(p_instance, PwmIdx));

    //Counter stop mode in burst mode
    if(pCfg->BurstMode == HAL_HRPWM_BURST_MODE_CNT_STOP) {
        LL_HRPWM_COM_BM_EnablePWMxCounterStop(p_instance, PwmIdx);
    } else if (pCfg->BurstMode == HAL_HRPWM_BURST_MODE_CNT_KEEP) {
        LL_HRPWM_COM_BM_DisablePWMxCounterStop(p_instance, PwmIdx);
    } else {
        //do nothing...
    }

    if (pCfg->UpdateGating == HAL_HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND) {
        LL_HRPWM_SLV_EnableResyncUpdate(p_instance, PwmIdx, pCfg->ReSyncUpdate);
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Control
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Control to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Timer Control Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformTimerCtl(HAL_HRPWM_HandleTypeDef *Handle,
                                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                  const HAL_HRPWM_TimerCtlTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    LL_HRPWM_SLV_SetCountingMode(p_instance, PwmIdx, pCfg->UpDownMode);

    HAL_FUNC_ALTER(pCfg->TrigHalf,      LL_HRPWM_SLV_EnableTriggeredHalfMode(p_instance, PwmIdx), 
                                        LL_HRPWM_SLV_DisableTriggeredHalfMode(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->GreaterCMPC,   LL_HRPWM_SLV_EnableCompareCGreaterThanMode(p_instance, PwmIdx),
                                        LL_HRPWM_SLV_DisableCompareCGreaterThanMode(p_instance, PwmIdx));
    HAL_FUNC_ALTER(pCfg->GreaterCMPA,   LL_HRPWM_SLV_EnableCompareAGreaterThanMode(p_instance, PwmIdx),
                                        LL_HRPWM_SLV_DisableCompareAGreaterThanMode(p_instance, PwmIdx));

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Dual Channel DAC
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Control to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Dual Channel DAC Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_DualDacCfg(HAL_HRPWM_HandleTypeDef *Handle,
                                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                            const HAL_HRPWM_DualDacCtlTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    LL_HRPWM_SLV_SetDualDacResetTrigger(p_instance, PwmIdx, pCfg->DualChannelDacReset);
    LL_HRPWM_SLV_SetDualDacStepTrigger(p_instance, PwmIdx, pCfg->DualChannelDacStep);
    HAL_FUNC_ALTER(pCfg->DualChannelDacEnable, 
                    LL_HRPWM_SLV_EnableDualDacTrigger(p_instance, PwmIdx), 
                    LL_HRPWM_SLV_DisableDualDacTrigger(p_instance, PwmIdx));

    return HAL_OK;
}


/**
  * @brief  HRPWM Master PWM Timer Compare Config
  * @param  Handle HRPWM Handle
  * @param  CmpUnit Compare unit to configure
  * @param  pCfg Master PWM Timer Compare Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_WaveformCmpCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_CmpUnitTypeDef CmpUnit, 
                                                                const HAL_HRPWM_CompareCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    switch (CmpUnit) {
    case HAL_HRPWM_CMP_UNIT_A:
        LL_HRPWM_MST_SetCompareA(p_instance, pCfg->CompareValue);
        break;
    
    case HAL_HRPWM_CMP_UNIT_B:
        LL_HRPWM_MST_SetCompareB(p_instance, pCfg->CompareValue);
        break;

    case HAL_HRPWM_CMP_UNIT_C:
        LL_HRPWM_MST_SetCompareC(p_instance, pCfg->CompareValue);
        break;

    case HAL_HRPWM_CMP_UNIT_D:
        LL_HRPWM_MST_SetCompareD(p_instance, pCfg->CompareValue);
        break;

    default:
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Compare Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Compare to be Config, not include Master PWM
  * @param  CmpUnit Compare unit to configure
  * @param  pCfg Slave PWMx Timer Compare Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformCmpCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                HAL_HRPWM_CmpUnitTypeDef CmpUnit, 
                                                                const HAL_HRPWM_CompareCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx Timer Compare Config
    switch (CmpUnit)
    {
    case HAL_HRPWM_CMP_UNIT_A:
        LL_HRPWM_SLV_SetCompareA(p_instance, PwmIdx, pCfg->CompareValue);
        break;
    
    case HAL_HRPWM_CMP_UNIT_B:
        if (pCfg->AutoDelayedMode != HAL_HRPWM_SLV_CMP_AUTO_DLY_ALWAYS) {
            LL_HRPWM_SLV_SetCompareBAutoDelayMode(p_instance, PwmIdx, pCfg->AutoDelayedMode);

            if (pCfg->AutoDelayedMode == HAL_HRPWM_SLV_CMP_AUTO_DLY_AFTER_CAPx_CMPA) {
                LL_HRPWM_SLV_SetCompareA(p_instance, PwmIdx, pCfg->AutoDelayedTimeout);
            } else if (pCfg->AutoDelayedMode == HAL_HRPWM_SLV_CMP_AUTO_DLY_AFTER_CAPx_CMPC) {
                LL_HRPWM_SLV_SetCompareC(p_instance, PwmIdx, pCfg->AutoDelayedTimeout);
            } else {
                //do nothing...
            }
        } else {
            LL_HRPWM_SLV_SetCompareBAutoDelayMode(p_instance, PwmIdx, LL_HRPWM_SLV_CMPB_AUTO_DLY_ALWAYS);
        }
        
        LL_HRPWM_SLV_SetCompareB(p_instance, PwmIdx, pCfg->CompareValue);
        break;

    case HAL_HRPWM_CMP_UNIT_C:
        LL_HRPWM_SLV_SetCompareC(p_instance, PwmIdx, pCfg->CompareValue);
        break;

    case HAL_HRPWM_CMP_UNIT_D:
        if (pCfg->AutoDelayedMode != HAL_HRPWM_SLV_CMP_AUTO_DLY_ALWAYS) {
            LL_HRPWM_SLV_SetCompareDAutoDelayMode(p_instance, PwmIdx, pCfg->AutoDelayedMode);

            if (pCfg->AutoDelayedMode == HAL_HRPWM_SLV_CMP_AUTO_DLY_AFTER_CAPx_CMPA) {
                LL_HRPWM_SLV_SetCompareA(p_instance, PwmIdx, pCfg->AutoDelayedTimeout);
            } else if (pCfg->AutoDelayedMode == HAL_HRPWM_SLV_CMP_AUTO_DLY_AFTER_CAPx_CMPC) {
                LL_HRPWM_SLV_SetCompareC(p_instance, PwmIdx, pCfg->AutoDelayedTimeout);
            } else {
                //do nothing...
            }
        } else {
            LL_HRPWM_SLV_SetCompareDAutoDelayMode(p_instance, PwmIdx, LL_HRPWM_SLV_CMPD_AUTO_DLY_ALWAYS);
        }

        LL_HRPWM_SLV_SetCompareD(p_instance, PwmIdx, pCfg->CompareValue);
        break;

    default:
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM System DMA Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx System DMA to be Config, include Master PWM
  * @param  pCfg System DMA Config Pointer
  * @return HAL Status
  */
static HAL_StatusTypeDef HRPWM_SysDMACfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                        HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                        const HAL_HRPWM_SysDMACfgTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(pCfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Handle->Instance) || pCfg == NULL) {
        return HAL_INVALID;
    }

    //System DMA Config
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        return HRPWM_Mst_SysDMACfg(Handle, pCfg);
    } else {
        ASSERT_FUNC_PARAM(PwmIdx < HAL_HRPWM_SLV_PWM_NUMS);

        if (PwmIdx >= HAL_HRPWM_SLV_PWM_NUMS) {
            return HAL_INVALID;
        }

        return HRPWM_Slv_SysDMACfg(Handle, PwmIdx, pCfg);
    }
}

/**
  * @brief  HRPWM Master PWM System DMA Config
  * @param  Handle HRPWM Handle
  * @param  pCfg Master PWM System DMA Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_SysDMACfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                           const HAL_HRPWM_SysDMACfgTypeDef *pCfg)
{
    uint32_t count;
    uint32_t mask;

    HRPWM_TypeDef *p_instance = Handle->Instance;

    count = 0;
    mask = pCfg->MstRegUpdate;

    if (pCfg->WriteRegEnable == HAL_HRPWM_FUNC_ENABLE) {
        while (mask) {
            mask &= (mask - 1);
            count++;
        }

        if (count > pCfg->BufferInWords) {
            return HAL_INVALID;
        }
    }

    //Master PWM System DMA Config
    if (pCfg->WriteRegEnable == HAL_HRPWM_FUNC_ENABLE) {
        if (pCfg->MstRegUpdate != HAL_HRPWM_BURST_DMA_MST_REG_UPD_NONE) {
            LL_HRPWM_MST_EnableSysDMAWriteUpdate(p_instance, pCfg->MstRegUpdate);
        } else {
            LL_HRPWM_MST_DisableSysDMAWriteUpdate(p_instance, LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL_MASK);
        }

    } else {
        LL_HRPWM_MST_DisableSysDMAWriteUpdate(p_instance, LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL_MASK);
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx System DMA Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx System DMA to be Config, not include Master PWM
  * @param  pCfg Slave PWMx System DMA Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_SysDMACfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                           const HAL_HRPWM_SysDMACfgTypeDef *pCfg)
{
    uint32_t count;
    uint32_t mask;

    HRPWM_TypeDef *p_instance = Handle->Instance;

    count = 0;
    mask = pCfg->SlvRegUpdate;

    if (pCfg->WriteRegEnable == HAL_HRPWM_FUNC_ENABLE) {
        while (mask) {
            mask &= (mask - 1);
            count++;
        }

        if (count > pCfg->BufferInWords) {
            return HAL_INVALID;
        }
    }

    //Slave PWMx System DMA Config
    if (pCfg->WriteRegEnable == HAL_HRPWM_FUNC_ENABLE) {
        if(pCfg->SlvRegUpdate != HAL_HRPWM_BURST_DMA_SLV_REG_UPD_NONE) {
            LL_HRPWM_SLV_EnableSysDMAWriteUpdate(p_instance, PwmIdx, pCfg->SlvRegUpdate);
        } else {
            LL_HRPWM_SLV_DisableSysDMAWriteUpdate(p_instance, PwmIdx, LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL_MASK);
        }

    } else {
        LL_HRPWM_SLV_DisableSysDMAWriteUpdate(p_instance, PwmIdx, LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL_MASK);
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Roll-Over Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Roll-Over to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Timer Roll-Over Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_RollOverModeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                 const HAL_HRPWM_RollOverModeCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx Timer Roll-Over Config
    LL_HRPWM_SLV_SetRollOverMode(p_instance, PwmIdx, pCfg->CounterRollOver);
    LL_HRPWM_SLV_SetOutputRollOverMode(p_instance, PwmIdx, pCfg->OutputRollOver);
    LL_HRPWM_SLV_SetADCRollOverMode(p_instance, PwmIdx, pCfg->ADCRollOver);
    LL_HRPWM_SLV_SetEventRollOverMode(p_instance, PwmIdx, pCfg->EventRollOver);
    LL_HRPWM_SLV_SetFaultEventRollOverMode(p_instance, PwmIdx, pCfg->FaultRollOver);

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Event Filter Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Event Filter to be Config, not include Master PWM
  * @param  EvtNum External Event Number to be Config
  * @param  pCfg Slave PWMx Timer Event Filter Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_TmrEvtFilCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                              HAL_HRPWM_ExtEvtNumTypeDef EvtNum, 
                                                              const HAL_HRPWM_TimerEventFilteringCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx Timer Event Filter Config
    LL_HRPWM_SLV_SetEventFilter(p_instance, PwmIdx, EvtNum, pCfg->Filter);
    HAL_FUNC_ALTER(pCfg->Latch, LL_HRPWM_SLV_EnableEventBlankLatch(p_instance, PwmIdx, EvtNum),
                                LL_HRPWM_SLV_DisableEventBlankLatch(p_instance, PwmIdx, EvtNum));

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Event Counter Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Timer Event A to be Config, not include Master PWM
  * @param  EvtCntr External event Counter for which timer event must be configured
  * @param  pCfg Slave PWMx Timer Event A Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_ExtEvtCntrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                               HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                               HAL_HRPWM_EvtCntrTypeDef EvtCntr, 
                                                               const HAL_HRPWM_ExternalEventCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx Timer Event A Config    
    if (EvtCntr == HAL_HRPWM_EVT_CNTR_A) {
        LL_HRPWM_SLV_SetEventCounterSource(p_instance, PwmIdx, pCfg->Source);
        LL_HRPWM_SLV_SetEventCounterThreshold(p_instance, PwmIdx, pCfg->Counter);
        LL_HRPWM_SLV_SetEventCounterResetMode(p_instance, PwmIdx, pCfg->ResetMode);        
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Output Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  Channel PWM output channel
  * @param  pCfg Slave PWMx Output Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformOutputCfg(HAL_HRPWM_HandleTypeDef *Handle,
                                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                   HAL_HRPWM_OutputChnlTypeDef Channel,
                                                                   const HAL_HRPWM_OutputCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    if (Channel == HAL_HRPWM_OUTPUT_CHNL_A) {
        LL_HRPWM_SLV_SetOutputASetSrc(p_instance, PwmIdx, pCfg->SetSource);
        LL_HRPWM_SLV_SetOutputAClrSrc(p_instance, PwmIdx, pCfg->ResetSource);
        LL_HRPWM_SLV_SetOutputAPolarityAndIdleLevel(p_instance, PwmIdx, pCfg->Polarity, pCfg->IdleLevel);
        LL_HRPWM_SLV_OUT_SetAFaultState(p_instance, PwmIdx, pCfg->FaultLevel);

        HAL_FUNC_ALTER(pCfg->IdleMode,              LL_HRPWM_SLV_EnableOutputABurstModeIdle(p_instance, PwmIdx),
                                                    LL_HRPWM_SLV_DisableOutputABurstModeIdle(p_instance, PwmIdx));
        HAL_FUNC_ALTER(pCfg->ChopperModeEnable,     LL_HRPWM_SLV_EnableOutputAChopper(p_instance, PwmIdx), 
                                                    LL_HRPWM_SLV_DisableOutputAChopper(p_instance, PwmIdx));
        HAL_FUNC_ALTER(pCfg->BurstModeEntryDelayed, LL_HRPWM_SLV_EnableOutputAIdleDeadTime(p_instance, PwmIdx),
                                                    LL_HRPWM_SLV_DisableOutputAIdleDeadTime(p_instance, PwmIdx));

    } else if (Channel == HAL_HRPWM_OUTPUT_CHNL_B) {
        LL_HRPWM_SLV_SetOutputBSetSrc(p_instance, PwmIdx, pCfg->SetSource);
        LL_HRPWM_SLV_SetOutputBClrSrc(p_instance, PwmIdx, pCfg->ResetSource);
        LL_HRPWM_SLV_SetOutputBPolarityAndIdleLevel(p_instance, PwmIdx, pCfg->Polarity, pCfg->IdleLevel);
        LL_HRPWM_SLV_OUT_SetBFaultState(p_instance, PwmIdx, pCfg->FaultLevel);

        HAL_FUNC_ALTER(pCfg->ChopperModeEnable, LL_HRPWM_SLV_EnableOutputBChopper(p_instance, PwmIdx), LL_HRPWM_SLV_DisableOutputBChopper(p_instance, PwmIdx));
        HAL_FUNC_ALTER(pCfg->IdleMode, LL_HRPWM_SLV_EnableOutputBBurstModeIdle(p_instance, PwmIdx),
                    LL_HRPWM_SLV_DisableOutputBBurstModeIdle(p_instance, PwmIdx));
        HAL_FUNC_ALTER(pCfg->BurstModeEntryDelayed, LL_HRPWM_SLV_EnableOutputBIdleDeadTime(p_instance, PwmIdx),
                    LL_HRPWM_SLV_DisableOutputBIdleDeadTime(p_instance, PwmIdx));

    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx DeadTime Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx DeadTime to be Config, not include Master PWM
  * @param  pCfg Slave PWMx DeadTime Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_DeadTimeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                             const HAL_HRPWM_DeadTimeCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx DeadTime Config
    LL_HRPWM_SLV_DT_SetRisingValue(p_instance, PwmIdx, pCfg->RisingValue);
    LL_HRPWM_SLV_DT_SetFallingValue(p_instance, PwmIdx, pCfg->FallingValue);
    LL_HRPWM_SLV_DT_SetRisingSign(p_instance, PwmIdx, pCfg->RisingSign);
    LL_HRPWM_SLV_DT_SetFallingSign(p_instance, PwmIdx, pCfg->FallingSign);

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Chopper Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Chopper to be Config, not include Master PWM
  * @param  pCfg Slave PWMx Chopper Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_ChopModeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                             const HAL_HRPWM_ChopperModeCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx Chopper Config
    LL_HRPWM_SLV_CHP_SetDutyCycle(p_instance, PwmIdx, pCfg->DutyCycle);
    LL_HRPWM_SLV_CHP_SetPrescaler(p_instance, PwmIdx, pCfg->CarrierFreq);
    LL_HRPWM_SLV_CHP_SetPulseWidth(p_instance, PwmIdx, pCfg->StartPulse);

    return HAL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Capture Config
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Capture to be Config, not include Master PWM
  * @param  Channel PWMx Capture Channel
  * @param  pCfg Slave PWMx Capture Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_WaveformCapCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                                HAL_HRPWM_CapChnlTypeDef Channel,
                                                                const HAL_HRPWM_CaptureCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Slave PWMx Capture Config
    if (Channel == HAL_HRPWM_CAP_CHNL_A) {
        LL_HRPWM_SLV_SetCaptureATrig(p_instance, PwmIdx, pCfg->Trigger);
    } else if (Channel == HAL_HRPWM_CAP_CHNL_B) {
        LL_HRPWM_SLV_SetCaptureBTrig(p_instance, PwmIdx, pCfg->Trigger);
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM Common External Event Config
  * @param  Handle HRPWM Handle
  * @param  EvtNum External Event Nubmer Which to be Config
  * @param  pCfg Common External Event Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_ExtEvtCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                            HAL_HRPWM_ExtEvtNumTypeDef EvtNum,
                                                            const HAL_HRPWM_EventCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    if ((pCfg->Sensitivity != HAL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_LVL) &&
        (pCfg->FastMode == HAL_HRPWM_FUNC_ENABLE)) {
        return HAL_INVALID;
    }

    //Common External Event Config
    LL_HRPWM_COM_EE_SetSrc(p_instance, EvtNum, pCfg->Source);
    LL_HRPWM_COM_EE_SetPolarity(p_instance, EvtNum, pCfg->Polarity);
    LL_HRPWM_COM_EE_SetSensitivity(p_instance, EvtNum, pCfg->Sensitivity);
    LL_HRPWM_COM_EE_SetFilter(p_instance, EvtNum, pCfg->Filter);

    HAL_FUNC_ALTER(pCfg->FastMode,  LL_HRPWM_COM_EE_EnableFastMode(p_instance, EvtNum),
                                    LL_HRPWM_COM_EE_DisableFastMode(p_instance, EvtNum));

    return HAL_OK;
}

/**
  * @brief  HRPWM Common Fault Config
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  pCfg Common Fault Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_FltCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                         HAL_HRPWM_FltNumTypeDef FltNum, 
                                                         const HAL_HRPWM_FaultCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Common Fault Config
    LL_HRPWM_COM_FLT_SetSrc(p_instance, FltNum, pCfg->Source);
    LL_HRPWM_COM_FLT_SetPolarity(p_instance, FltNum, pCfg->Polarity);
    LL_HRPWM_COM_FLT_SetFilter(p_instance, FltNum, pCfg->Filter);

    return HAL_OK;
}

/**
  * @brief  HRPWM Common Fault Counter Config
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  pCfg Common Fault Counter Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_FltCntrCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_FltNumTypeDef FltNum, 
                                                             const HAL_HRPWM_FaultCntrCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Common Fault Counter Config
    LL_HRPWM_COM_FLT_SetCounterThreshold(p_instance, FltNum, pCfg->Threshold);
    LL_HRPWM_COM_FLT_SetResetMode(p_instance, FltNum, pCfg->ResetMode);

    return HAL_OK;
}

/**
  * @brief  HRPWM Common Fault Blanking Config
  * @param  Handle HRPWM Handle
  * @param  FltNum Fault Number Which to be Config
  * @param  pCfg Common Fault Blanking Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_FltBlkCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                            HAL_HRPWM_FltNumTypeDef FltNum, 
                                                            const HAL_HRPWM_FaultBlankingCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Common Fault Blanking Config
    LL_HRPWM_COM_FLT_SetBlankingSrc(p_instance, FltNum, pCfg->BlankingSource);

    HAL_FUNC_ALTER(pCfg->BlankingEnable,    LL_HRPWM_COM_FLT_EnableBlanking(p_instance, FltNum), 
                                            LL_HRPWM_COM_FLT_DisableBlanking(p_instance, FltNum));

    return HAL_OK;
}

/**
  * @brief  HRPWM Common ADC Trigger Config
  * @param  Handle HRPWM Handle
  * @param  TrigNum ADC Trigger Number Which to be Config
  * @param  pCfg Common ADC Trigger Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_ADCTrigCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                             HAL_HRPWM_ADCTrigNumTypeDef TrigNum,
                                                             const HAL_HRPWM_ADCTriggerCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Common ADC Trigger Config
    switch (TrigNum) {
        case HAL_HRPWM_ADC_TRIG_NUM_0:
            LL_HRPWM_COM_ConfigADCTrigger0Event(p_instance, pCfg->Trigger);
            LL_HRPWM_COM_SetADCTrigger0EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger0UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_1:
            LL_HRPWM_COM_ConfigADCTrigger1Event(p_instance, pCfg->Trigger);
            LL_HRPWM_COM_SetADCTrigger1EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger1UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_2:
            LL_HRPWM_COM_ConfigADCTrigger2Event(p_instance, pCfg->Trigger);
            LL_HRPWM_COM_SetADCTrigger2EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger2UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_3:
            LL_HRPWM_COM_ConfigADCTrigger3Event(p_instance, pCfg->Trigger);
            LL_HRPWM_COM_SetADCTrigger3EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger3UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_4:
            LL_HRPWM_COM_SetADCTrigger4EventSource(p_instance, pCfg->Trigger468);
            LL_HRPWM_COM_SetADCTrigger4EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger4UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_5:
            LL_HRPWM_COM_SetADCTrigger5EventSource(p_instance, pCfg->Trigger579);
            LL_HRPWM_COM_SetADCTrigger5EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger5UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_6:
            LL_HRPWM_COM_SetADCTrigger6EventSource(p_instance, pCfg->Trigger468);
            LL_HRPWM_COM_SetADCTrigger6EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger6UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_7:
            LL_HRPWM_COM_SetADCTrigger7EventSource(p_instance, pCfg->Trigger579);
            LL_HRPWM_COM_SetADCTrigger7EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger7UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_8:
            LL_HRPWM_COM_SetADCTrigger8EventSource(p_instance, pCfg->Trigger468);
            LL_HRPWM_COM_SetADCTrigger8EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger8UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        case HAL_HRPWM_ADC_TRIG_NUM_9:
            LL_HRPWM_COM_SetADCTrigger9EventSource(p_instance, pCfg->Trigger579);
            LL_HRPWM_COM_SetADCTrigger9EventLength(p_instance, pCfg->TriggerLength);
            LL_HRPWM_COM_SetADCTrigger9UpdateSource(p_instance, pCfg->UpdateSource);
            break;

        default:
            /* Common ADC Tirgger NumberInvalid */
            return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Enable or disables the Master HRPWM burst DMA update. (Default: enable, allow update)
  * @param  Handle HRPWM Handle
  * @param  Enable Burst DMA update enabling
  * @retval HAL status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_BurstDMAUpdateCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                   HAL_HRPWM_EnableTypeDef Enable)
{
    //If disabled, the burst mode Compare Value and Period will not be updated.
    HAL_FUNC_ALTER(Enable,  LL_HRPWM_MST_ReleaseBurstDMADisable(Handle->Instance), 
                            LL_HRPWM_MST_AssertBurstDMADisable(Handle->Instance));

    return HAL_OK;
}

/**
  * @brief  Enable or disables the Master HRPWM burst DMA update. (Default: enable, allow update)
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which PWMx Register Update, include Master PWM
  * @param  Enable Burst DMA update enabling
  * @retval HAL status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_BurstDMAUpdateCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                   HAL_HRPWM_EnableTypeDef Enable)
{
    //If disabled, the burst mode Compare Value and Period will not be updated.
    HAL_FUNC_ALTER(Enable,  LL_HRPWM_SLV_ReleasePWMxBurstDMADisable(Handle->Instance, PwmIdx), 
                            LL_HRPWM_SLV_AssertPWMxBurstDMADisable(Handle->Instance, PwmIdx));

    return HAL_OK;
}

/**
  * @brief  HRPWM Common Burst Mode Config
  * @param  Handle HRPWM Handle
  * @param  pCfg Common Burst Mode Config Pointer
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Comm_BurstModeCfg(HAL_HRPWM_HandleTypeDef *Handle, 
                                                               const HAL_HRPWM_BurstModeCfgTypeDef *pCfg)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    //Burst Mode Common Config
    LL_HRPWM_COM_BM_SetMode(p_instance, pCfg->Mode);
    LL_HRPWM_COM_BM_SetClockSrc(p_instance, pCfg->ClockSource);
    LL_HRPWM_COM_BM_SetPrescaler(p_instance, pCfg->Prescaler);
    LL_HRPWM_COM_BM_SetPeriod(p_instance, pCfg->Period);
    LL_HRPWM_COM_BM_SetCompare(p_instance, pCfg->IdleDuration);
    LL_HRPWM_COM_BM_SetTrigEvt(p_instance, pCfg->Trigger);
    LL_HRPWM_COM_BM_SetTrigMode(p_instance, pCfg->TriggerMode);

    HAL_FUNC_ALTER(pCfg->PreloadEnable, LL_HRPWM_COM_BM_EnablePreload(p_instance), 
                                        LL_HRPWM_COM_BM_DisablePreload(p_instance));

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Register Update Software Force
  * @param  Instance Specifies HRPWM peripheral
  * @param  PwmIdx Indicate which PWMx Register Update to be Force, include Master PWM
  * @return HAL Status
  */
static HAL_StatusTypeDef HRPWM_ForceRegistersUpdate(HAL_HRPWM_HandleTypeDef *Handle, 
                                                    HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    if (PwmIdx == HAL_HRPWM_MST_PWM) {
        return HRPWM_Mst_ForceRegistersUpdate(Handle);
    } else {
        return HRPWM_Slv_ForceRegistersUpdate(Handle, PwmIdx);
    }
}

/**
  * @brief  HRPWM HAL Master Register Update Software Force
  * @param  Instance Specifies HRPWM peripheral
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Mst_ForceRegistersUpdate(HAL_HRPWM_HandleTypeDef *Handle)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart = HAL_GetTick();

    //Common Register Update Force
    LL_HRPWM_COM_SoftwareUpdateMasterPWM(p_instance);

    //Wait for update complete
    while (LL_HRPWM_COM_IsMasterPWMUpdateBusy(p_instance)) {
        if ((HAL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  HRPWM HAL Slave Register Update Software Force
  * @param  Instance Specifies HRPWM peripheral
  * @param  PwmIdx Indicate which PWMx Register Update to be Force, not include Master PWM
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_ForceRegistersUpdate(HAL_HRPWM_HandleTypeDef *Handle, 
                                                                      HAL_HRPWM_PWMIdxTypeDef PwmIdx)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;
    uint32_t tickstart = HAL_GetTick();

    //Common Register Update Force
    LL_HRPWM_COM_SoftwareUpdatePWMx(p_instance, PwmIdx);

    //Wait for update complete
    while (LL_HRPWM_COM_IsPWMxUpdateBusy(p_instance, PwmIdx)) {
        if ((HAL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Force the PWMx output to its active or inactive state
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  Channel PWM output channel
  * @param  Output The output is forced to its active or inactive level
  * @return HAL Status
  */
__STATIC_FORCEINLINE HAL_StatusTypeDef HRPWM_Slv_SwTrigOutLvl(HAL_HRPWM_HandleTypeDef *Handle, 
                                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                              HAL_HRPWM_OutputChnlTypeDef Channel,
                                                              HAL_HRPWM_Slv_OutLvlStateTypeDef Output)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;

    /* Software Trigger */
    if (Channel == HAL_HRPWM_OUTPUT_CHNL_A) {
        if (Output == HAL_HRPWM_SLV_OUT_LVL_STATE_VLD) {
            LL_HRPWM_SLV_SetOutputASetSrc(p_instance, PwmIdx, LL_HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG);
        } else if (Output == HAL_HRPWM_SLV_OUT_LVL_STATE_INVLD) {
            LL_HRPWM_SLV_SetOutputAClrSrc(p_instance, PwmIdx, LL_HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG);
        } else {
            return HAL_INVALID;
        }

    } else if (Channel == HAL_HRPWM_OUTPUT_CHNL_B) {
        if (Output == HAL_HRPWM_SLV_OUT_LVL_STATE_VLD) {
            LL_HRPWM_SLV_SetOutputBSetSrc(p_instance, PwmIdx, LL_HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG);
        } else if (Output == HAL_HRPWM_SLV_OUT_LVL_STATE_INVLD) {
            LL_HRPWM_SLV_SetOutputBClrSrc(p_instance, PwmIdx, LL_HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG);
        } else {
            return HAL_INVALID;
        }
    } else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
  * @brief  Return actual state (RUN, IDLE, FAULT) 
  * @param  Handle HRPWM Handle
  * @param  PwmIdx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  Channel PWM output channel
  * @return HRPWM Slave Output Level Status
  */
__STATIC_FORCEINLINE HAL_HRPWM_Slv_OutStateTypeDef HRPWM_Slv_OutputState(const HAL_HRPWM_HandleTypeDef *Handle, 
                                                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                                         HAL_HRPWM_OutputChnlTypeDef Channel)
{
    HRPWM_TypeDef *p_instance = Handle->Instance;
    uint32_t output_state;

    if (Channel == HAL_HRPWM_OUTPUT_CHNL_A) {
        if ((LL_HRPWM_COM_IsPWMxOutputAEnabled(p_instance, PwmIdx)) != (uint32_t)0UL) {
            /* Output A is enabled */
            output_state = HAL_HRPWM_SLV_OUT_STATE_RUN;
        } else {
            if ((LL_HRPWM_COM_IsPWMxOutputADisabled(p_instance, PwmIdx)) != 0UL) {
                /* Output A is disabled but state is abnormal */
                output_state = HAL_HRPWM_SLV_OUT_STATE_FAULT;
            } else {
                /* Output A is disabled or idle */
                output_state = HAL_HRPWM_SLV_OUT_STATE_IDLE;
            }
        }

    } else if (Channel == HAL_HRPWM_OUTPUT_CHNL_B) {
        if ((LL_HRPWM_COM_IsPWMxOutputBEnabled(p_instance, PwmIdx)) != (uint32_t)0UL) {
            /* Output B is enabled */
            output_state = HAL_HRPWM_SLV_OUT_STATE_RUN;
        } else {
            if ((LL_HRPWM_COM_IsPWMxOutputBDisabled(p_instance, PwmIdx)) != (uint32_t)0UL) {
                /* Output B state error */
                output_state = HAL_HRPWM_SLV_OUT_STATE_FAULT;
            } else {
                /* Output B is disabled */
                output_state = HAL_HRPWM_SLV_OUT_STATE_IDLE;
            }
        }

    } else {
        return HAL_HRPWM_SLV_OUT_STATE_FAULT;
    }

    return output_state;
}

/**
  * @}
  */ /* HRPWM_HAL_Private_Functions */

/**
  * @}
  */ /* HRPWM_HAL */

#endif  /* HAL_HRPWM_MODULE_ENABLED */
#endif  /* HAL_MODULE_ENABLED */
#endif  /* HRPWM */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

