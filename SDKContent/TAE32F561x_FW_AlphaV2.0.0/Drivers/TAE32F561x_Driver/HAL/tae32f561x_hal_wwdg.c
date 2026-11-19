/**
  ******************************************************************************
  * @file    tae32f561x_hal_wwdg.c
  * @author  Tai-Action SD Team
  * @brief   WWDG HAL module driver.
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

#if defined(WWDG) 
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_WWDG_MODULE_ENABLED) && (HAL_WWDG_MODULE_ENABLED == 1)

/** @defgroup WWDG_HAL WWDG Hardware Abstraction Layer
  * @brief HAL layer driver for WWDG module.
  * @{
  */

/**
  * @}
  */ /* WWDG_HAL_Private_Constants */

/* Private Macro -------------------------------------------------------------*/
/** @brief WWDG_HAL_Private_Macros WWDG HAL Private Macros
  * @{
  */  
#define IS_WWDG_PRESCALER(__VAL__)          (((__VAL__) >= LL_WWDG_PRESCALER_MIN) \
                                                   && (__VAL__ <= LL_WWDG_PRESCALER_MAX))

#define IS_WWDG_WINDOW(__VAL__)                (((__VAL__) >= LL_WWDG_WINDOW_MIN) \
                                                   && (__VAL__ <= LL_WWDG_WINDOW_MAX))

#define IS_WWDG_COUNTER(__VAL__)              (((__VAL__) >= LL_WWDG_COUNTER_MIN) \
                                                   && (__VAL__ <= LL_WWDG_COUNTER_MAX))

#define IS_WWDG_EWI_MODE(__VAL__)                (((__VAL__) == HAL_WWDG_EWI_ENABLE) \
                                                   || (__VAL__ == HAL_WWDG_EWI_DISABLE))




/* Exported functions --------------------------------------------------------*/

/** @defgroup WWDG_HAL_Exported_Functions_Group1 Initialization and De-initialization functions
  * @{
  */

/**
  * @brief  Initialize the WWDG according to the specified parameters in the
  *         HAL_WWDG_InitTypeDef and start the watchdog.
  *         Before exiting, the counter is refreshed to establish a correct
  *         time base.
  * @param  hwwdg  pointer to a HAL_WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @param  WWDGx  pointer to the WWDG peripheral instance.
  * @param  Init   pointer to a HAL_WWDG_InitTypeDef structure that contains
  *                the configuration parameters for the WWDG peripheral.
  * @return HAL status
  */
  HAL_StatusTypeDef HAL_WWDG_Init(HAL_WWDG_HandleTypeDef *Handle, WWDG_TypeDef *WWDGx,
                                 HAL_WWDG_InitTypeDef *pInit)
  {
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));
    ASSERT_FUNC_PARAM(pInit != NULL);
    ASSERT_FUNC_PARAM(IS_WWDG_PRESCALER(pInit->Prescaler));
    ASSERT_FUNC_PARAM(IS_WWDG_WINDOW(pInit->Window));
    ASSERT_FUNC_PARAM(IS_WWDG_COUNTER(pInit->Counter));
    ASSERT_FUNC_PARAM(IS_WWDG_EWI_MODE(pInit->EWIMode));
    HAL_WWDG_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_WWDG_ALL_INSTANCE(WWDGx)) || (pInit == NULL)) {
            return HAL_INVALID;
        }
    });
    /* Bind the instance passed by the caller */
    Handle->Instance = WWDGx;
    WWDG_TypeDef *p_instance = Handle->Instance;

    /* Init the low level hardware e.g. Clock, NVIC */
    HAL_WWDG_MspInit(Handle);

    /* Write to WWDG registers the Prescaler and Counter values (Window deferred) */
    LL_WWDG_SetPrescaler(p_instance, pInit->Prescaler);

    /* Configure WWDG Early Wakeup Interrupt mode (peripheral + NVIC line) */
    if (pInit->EWIMode == HAL_WWDG_EWI_DISABLE) {
        LL_WWDG_DisableIT_EWIE(p_instance);
    }
    else { /* HAL_WWDG_EWI_ENABLE */
        LL_WWDG_ClearFlag_EWIF(p_instance);
        LL_WWDG_EnableIT_EWIE(p_instance);
    }

    /* Refresh counter to establish a valid time base */
    LL_WWDG_SetCounter(p_instance, pInit->Counter);

    /* Now set the actual Window value as configured by the user */
    LL_WWDG_SetWindow(p_instance, pInit->Window);

    /* Enable WWDG and start the downcounter */
    LL_WWDG_Enable(p_instance);

    /* Return function status */
    return HAL_OK;
}

/**
  * @brief  DeInitialize the WWDG peripheral.
  *         Stop the watchdog, reset registers to default values,
  *         and call the MSP DeInit callback.
  * @param  hwwdg  pointer to a HAL_WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_WWDG_DeInit(HAL_WWDG_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_WWDG_ALL_INSTANCE(Handle->Instance));
    
    HAL_WWDG_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_WWDG_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });

    WWDG_TypeDef *p_instance = Handle->Instance;    

    /* Stop the WWDG */
    LL_WWDG_Disable(p_instance);

    /* Disable Early Wakeup Interrupt and its NVIC line */
    LL_WWDG_DisableIT_EWIE(p_instance);

    /* Clear any pending Early Wakeup Interrupt flag */
    LL_WWDG_ClearFlag_EWIF(p_instance);

    /* DeInit the low level hardware e.g. Clock, NVIC */
    HAL_WWDG_MspDeInit(Handle);

    return HAL_OK;
}

/**
  * @}
  */

/**
  * @brief  Refresh the WWDG counter.
  * @param  hwwdg  pointer to a HAL_WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_WWDG_Refresh(HAL_WWDG_HandleTypeDef *Handle,uint16_t Counter)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_WWDG_ALL_INSTANCE(Handle->Instance));

    HAL_WWDG_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_WWDG_ALL_INSTANCE(Handle->Instance))) {
            return HAL_INVALID;
        }        
    });  
        
    /* Write to WWDG CVR the counter reload value to refresh with */
    LL_WWDG_SetCounter(Handle->Instance, Counter);

    /* Return function status */
    return HAL_OK;
}

/**
  * @brief  WWDG MSP Init
  * @param  hwwdg  pointer to a HAL_WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @return None
  */
__WEAK void HAL_WWDG_MspInit(HAL_WWDG_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
                the HAL_WWDG_MspInit could be implemented in the user file
        */
}

/**
  * @brief  WWDG MSP DeInit
  * @param  hwwdg  pointer to a HAL_WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @return None
  */
void __WEAK HAL_WWDG_MspDeInit(HAL_WWDG_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
                the HAL_WWDG_MspDeInit could be implemented in the user file
        */
}


/**
  * @brief  Handle WWDG interrupt request.
  * @param  hwwdg  pointer to a HAL_WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @return None
  */
void HAL_WWDG_IRQHandler(HAL_WWDG_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_WWDG_ALL_INSTANCE(Handle->Instance));

    HAL_WWDG_PARAM_CHECK({
        if ((Handle == NULL) || (!IS_WWDG_ALL_INSTANCE(Handle->Instance))) {
            return;
        }
    });

    WWDG_TypeDef *p_instance = Handle->Instance;

    /* Check if Early Wakeup Interrupt is enabled and flag is set */
    if ((LL_WWDG_IsEnabledIT_EWIE(p_instance) != 0UL) &&
        (LL_WWDG_IsActiveFlag_EWIF(p_instance) != 0UL))
    {
        /* Clear the Early Wakeup Interrupt pending flag */
        LL_WWDG_ClearFlag_EWIF(p_instance);

        /* Call the Early Wakeup callback */
        HAL_WWDG_EarlyWakeupCallback(Handle);
    }
}

/**
  * @brief  WWDG Early Wakeup callback.
  * @param  hwwdg  pointer to a HAL_WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @return None
  */
__WEAK void HAL_WWDG_EarlyWakeupCallback(HAL_WWDG_HandleTypeDef *Handle)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Handle);

    /* NOTE: This function should not be modified, when the callback is needed,
                the HAL_WWDG_EarlyWakeupCallback could be implemented in the user file
        */
}

/**
  * @}
  */


#endif /* HAL_WWDG_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* WWDG */

/**
  * @}
  */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/
