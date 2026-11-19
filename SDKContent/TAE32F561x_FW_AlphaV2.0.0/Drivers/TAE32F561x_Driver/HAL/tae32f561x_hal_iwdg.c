/**
  ******************************************************************************
  * @file    tae32f561x_hal_iwdg.c
  * @author  Tai-Action SD Team
  * @brief   IWDG HAL module driver.
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

#if defined(IWDG) 
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_IWDG_MODULE_ENABLED) && (HAL_IWDG_MODULE_ENABLED == 1)

/** @defgroup IWDG_HAL IWDG Hardware Abstraction Layer
  * @brief HAL layer driver for IWDG module.
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/** @defgroup IWDG_Private_Defines IWDG Private Defines
  * @{
  */

#define HAL_IWDG_DEFAULT_TIMEOUT       (100)
/**
  * @}
  */


/**
  * @}
  */ /* IWDG_HAL_Private_Constants */

/* Private Macro -------------------------------------------------------------*/
/** @brief IWDG_HAL_Private_Macros IWDG HAL Private Macros
  * @{
  */  

#define IS_IWDG_RELOAD(__VAL__)                            (((__VAL__) >= 1UL) && ((__VAL__) <= 0xFFFFUL))

#define IS_IWDG_MODE(__VAL__)                              (((__VAL__) == HAL_IWDG_MODE_RESET)   || \
                                                            ((__VAL__) == HAL_IWDG_MODE_INTERRUPT))

#define IS_IWDG_PRESCALER(__VAL__)                         (((__VAL__) == HAL_IWDG_PRESCALER_4)  || \
                                                            ((__VAL__) == HAL_IWDG_PRESCALER_8)  || \
                                                            ((__VAL__) == HAL_IWDG_PRESCALER_16) || \
                                                            ((__VAL__) == HAL_IWDG_PRESCALER_32) || \
                                                            ((__VAL__) == HAL_IWDG_PRESCALER_64) || \
                                                            ((__VAL__) == HAL_IWDG_PRESCALER_128) || \
                                                            ((__VAL__) == HAL_IWDG_PRESCALER_256) || \
                                                            ((__VAL__) == HAL_IWDG_PRESCALER_512))

/* Exported functions --------------------------------------------------------*/

/** @defgroup IWDG_HAL_Exported_Functions_Group1 Initialization and Start functions
  * @{
  */

/**
  * @brief  Initialize the IWDG according to the specified parameters in the
  *         IWDG_InitTypeDef and start watchdog. Before exiting function,
  *         watchdog is refreshed in order to have correct time base.
  * @param  Handle IWDG handle
  * @param  IWDGx  pointer to the IWDG peripheral instance.
  * @param  pInit  pointer to a HAL_IWDG_InitTypeDef structure that contains
  *                the configuration parameters for the IWDG peripheral.
  * @retval HAL_OK      - Initialization completed successfully.
  * @retval HAL_INVALID - At least one parameter is invalid.
  * @retval HAL_ERROR   - IWDG is already running, or the IWDG is
  *                       already enabled.
  */
HAL_StatusTypeDef HAL_IWDG_Init(HAL_IWDG_HandleTypeDef *Handle, IWDG_TypeDef *IWDGx,
                                HAL_IWDG_InitTypeDef *pInit)
{
    uint32_t tickstart = 0U;
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IWDG_ALL_INSTANCE(IWDGx));
    ASSERT_FUNC_PARAM(pInit != NULL);
    ASSERT_FUNC_PARAM(IS_IWDG_PRESCALER(pInit->Prescaler));
    ASSERT_FUNC_PARAM(IS_IWDG_RELOAD(pInit->Reload));
    ASSERT_FUNC_PARAM(IS_IWDG_MODE(pInit->Mode));
    /* Check the IWDG handle allocation */
    /* Check NULL pointers */
    HAL_IWDG_PARAM_CHECK({
        if ((Handle == NULL) || (pInit == NULL)) {
            return HAL_INVALID;
        }
    });

    /* Bind the instance passed by the caller */
    Handle->Instance = IWDGx;
    IWDG_TypeDef *p_instance = Handle->Instance;

    /* Init the low level hardware e.g. Clock, NVIC */
    HAL_IWDG_MspInit(Handle);   

    /* Enable write access to IWDG_PR, IWDG_RLR and IWDG_CR registers by writing
    unlock key in KEYR */
    LL_IWDG_EnableWriteAccess(p_instance);

    /* Write the prescaler first, then wait for the prescaler update to
    complete before writing the reload register. On this IWDG, writing RLR
    while a prescaler update is in progress (PSCUPD set, e.g. when re-init
    a running watchdog) causes the reload write to be ignored, leaving RLR
    stuck at its previous value. */
    LL_IWDG_SetPrescaler(p_instance, pInit->Prescaler);//����Ԥ��Ƶ��

    tickstart = HAL_GetTick();
    while (LL_IWDG_IsActiveFlag_PSCUPD(p_instance) != 0UL) {
        if ((HAL_GetTick() - tickstart) > HAL_IWDG_DEFAULT_TIMEOUT) {
            break;
        }
    }

    LL_IWDG_SetReloadCounter(p_instance, pInit->Reload);
    tickstart = HAL_GetTick();
    while (LL_IWDG_IsActiveFlag_RLVUPD(p_instance) != 0UL) {
        if ((HAL_GetTick() - tickstart) > HAL_IWDG_DEFAULT_TIMEOUT) {
            break;
        }
    }

    /* Configure IWDG operating mode (Reset or Interrupt) */
    if (pInit->Mode == HAL_IWDG_MODE_RESET) {
        LL_IWDG_SetMode(p_instance, LL_IWDG_MODE_RESET);
        LL_IWDG_DisableIT_TOIE(p_instance);
    }
    else  /* HAL_IWDG_MODE_INTERRUPT */
    {
        LL_IWDG_SetMode(p_instance, LL_IWDG_MODE_INTERRUPT);
        LL_IWDG_ClearFlag_TOIF(p_instance);
        LL_IWDG_EnableIT_TOIE(p_instance);
    }

    /* Re-lock the protected CR/RLR/PSCR registers once configuration is done */
    LL_IWDG_DisableWriteAccess(p_instance);

    /* Enable IWDG. LSI is turned on automatically.
    Placed after full configuration to avoid watchdog timeout during setup. */
    LL_IWDG_Enable(p_instance);

    /* Check pending flag, if previous update not done, return timeout */
    tickstart = HAL_GetTick();

    /* Wait for register to be updated */
    while (LL_IWDG_IsReady(p_instance) == 0UL) {
        if ((HAL_GetTick() - tickstart) > HAL_IWDG_DEFAULT_TIMEOUT) {
            if (LL_IWDG_IsReady(p_instance) == 0UL) {
                return HAL_TIMEOUT;
            }
        }
    }
    /* Reload IWDG counter with value defined in the reload register */
    LL_IWDG_ReloadCounter(p_instance);

    /* Return function status */
    return HAL_OK;
}

/**
  * @brief  DeInitialize the IWDG peripheral.
  *         Stop the watchdog, reset registers to default values,
  *         and call the MSP DeInit callback.
  * @param  hiwdg  pointer to a HAL_IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_IWDG_DeInit(HAL_IWDG_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IWDG_ALL_INSTANCE(Handle->Instance));
    
    HAL_IWDG_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_IWDG_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });

    IWDG_TypeDef *p_instance = Handle->Instance;

    /* Stop the IWDG (write 0xDDDD to KEYR) */
    LL_IWDG_Disable(p_instance);

    /* Enable write access once and restore all registers to default */
    LL_IWDG_EnableWriteAccess(p_instance);
    LL_IWDG_DisableIT_TOIE(p_instance);
    LL_IWDG_DisableWriteAccess(p_instance);

    /* Clear timeout interrupt pending flag */
    LL_IWDG_ClearFlag_TOIF(p_instance);

    /* DeInit the low level hardware e.g. Clock, NVIC */
    HAL_IWDG_MspDeInit(Handle);

    return HAL_OK;
}

/**
  * @}
  */


/**
  * @brief  Refresh the IWDG.
  * @note   This function waits for any pending register update (RLVUPD/PSCUPD)
  *         to complete before reloading the counter, preventing the reload
  *         from being ignored by hardware during an ongoing register update.
  * @param  hiwdg  pointer to a HAL_IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Refresh(HAL_IWDG_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IWDG_ALL_INSTANCE(Handle->Instance));
    
    HAL_IWDG_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_IWDG_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });

    IWDG_TypeDef *p_instance = Handle->Instance;

    /* Reload IWDG counter with value defined in the reload register */
    LL_IWDG_ReloadCounter(p_instance);

    /* Return function status */
    return HAL_OK;
}

/**
  * @}
  */


/**
  * @brief  IWDG MSP Init
  * @param  hiwdg  pointer to a HAL_IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @return None
  */
__WEAK void HAL_IWDG_MspInit(HAL_IWDG_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
    the HAL_IWDG_MspInit could be implemented in the user file
    */
}

/**
  * @brief  IWDG MSP DeInit
  * @param  hiwdg  pointer to a HAL_IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @return None
  */
__WEAK void HAL_IWDG_MspDeInit(HAL_IWDG_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
    the HAL_IWDG_MspDeInit could be implemented in the user file
    */
}

/**
  * @brief  Handle IWDG interrupt request.
  * @param  hiwdg  pointer to a HAL_IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @return None
  */
void HAL_IWDG_IRQHandler(HAL_IWDG_HandleTypeDef *Handle)
{

    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IWDG_ALL_INSTANCE(Handle->Instance));

    HAL_IWDG_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_IWDG_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    IWDG_TypeDef *p_instance = Handle->Instance; 

    /* Check if timeout interrupt is enabled and flag is set */
    if ((LL_IWDG_IsEnabledIT_TOIE(p_instance) != 0UL) &&
    (LL_IWDG_IsActiveFlag_TOIF(p_instance) != 0UL))
    {
        /* Clear the timeout interrupt pending flag */
        LL_IWDG_ClearFlag_TOIF(p_instance);

        /* Call the timeout callback */
        HAL_IWDG_TimeoutCallback(Handle);
    }
}

/**
  * @brief  IWDG timeout callback.
  * @param  hiwdg  pointer to a HAL_IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @return None
  */
__WEAK void HAL_IWDG_TimeoutCallback(HAL_IWDG_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
    the HAL_IWDG_TimeoutCallback could be implemented in the user file
    */
}

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_IWDG_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* IWDG */

/**
  * @}
  */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/
