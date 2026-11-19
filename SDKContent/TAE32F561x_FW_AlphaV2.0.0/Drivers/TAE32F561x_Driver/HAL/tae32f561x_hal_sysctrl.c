/**
  ******************************************************************************
  * @file    tae32f561x_hal_sysctrl.c
  * @author  Tai-Action SD Team
  * @brief   SYSCTRL HAL module driver
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

#if defined(SYSCTRL)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_SYSCTRL_MODULE_ENABLED) && (HAL_SYSCTRL_MODULE_ENABLED == 1)

/** @defgroup SYSCTRL_HAL SYSCTRL HAL
  * @brief    SYSCTRL HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup SYSCTRL_HAL_Private_Macros SYSCTRL HAL Private Macros
  * @brief    SYSCTRL HAL Private Macros
  * @{
  */

#define SYSCTRL_GET_INSTANCE                          (SYSCTRL)

#define IS_SYSCTRL_VREFBUF_REF(__VAL__)               (((__VAL__) == HAL_SYSCTRL_VREFBUF_REF_EXT) || \
                                                       ((__VAL__) == HAL_SYSCTRL_VREFBUF_REF_INT) )

#define IS_SYSCTRL_VREFBUF_VOL(__VAL__)               (((__VAL__) == HAL_SYSCTRL_VREFBUF_VOL_2V9) || \
                                                       ((__VAL__) == HAL_SYSCTRL_VREFBUF_VOL_2V5) )

#define IS_SYSCTRL_ENABLE(__VAL__)                    (((__VAL__) == HAL_SYSCTRL_FUNC_DISABLE) || \
                                                       ((__VAL__) == HAL_SYSCTRL_FUNC_ENABLE) )

#define IS_SYSCTRL_ADC_BUF_SRC(__VAL__)               (((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_AVSS)      ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_TSENSOR))           


/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup SYSCTRL_HAL_Exported_Functions SYSCTRL HAL Exported Functions
  * @brief    SYSCTRL HAL Exported Functions
  * @{
  */

/** @defgroup SYSCTRL_HAL_EF_Configuration SYSCTRL Configuration Functions
  * @brief    SYSCTRL Configuration Functions
  * @{
  */

/**
 * @brief Configure the power monitor function.
 * @param pCfg      Pointer to a HAL_SYSCTRL_PowerDetectTypeDef configuration
 * @retval  HAL_OK      - Configuration successful.
 * @retval  HAL_INVALID - Invalid parameter.
 */
HAL_StatusTypeDef HAL_SYSCTRL_PowerMonitorConfig(HAL_SYSCTRL_PowerDetectTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_SYSCTRL_ENABLE(pCfg->VCCLowVoltage));
    ASSERT_FUNC_PARAM(IS_SYSCTRL_ENABLE(pCfg->AVCCLowVoltage));
    ASSERT_FUNC_PARAM(IS_SYSCTRL_ENABLE(pCfg->VDDOverCurrent));
    ASSERT_FUNC_PARAM(IS_SYSCTRL_ENABLE(pCfg->VDDLowVoltage));

    HAL_SYSCTRL_PARAM_CHECK({
        if (pCfg == NULL) {
            return HAL_INVALID;
        }     
        
        if ((!IS_SYSCTRL_ENABLE(pCfg->VCCLowVoltage))   || 
            (!IS_SYSCTRL_ENABLE(pCfg->AVCCLowVoltage))  ||
            (!IS_SYSCTRL_ENABLE(pCfg->VDDOverCurrent))  ||
            (!IS_SYSCTRL_ENABLE(pCfg->VDDLowVoltage))) {
            return HAL_INVALID;
        }
    });

    HAL_SYSCTRL_UnlockSystemRegister();

    HAL_FUNC_ALTER(pCfg->VCCLowVoltage,     HAL_SYSCTRL_VCC_EnableLowVoltageDetect(),
                                            HAL_SYSCTRL_VCC_DisableLowVoltageDetect());

    HAL_FUNC_ALTER(pCfg->AVCCLowVoltage,    HAL_SYSCTRL_AVCC_EnableLowVoltageDetect(),
                                            HAL_SYSCTRL_AVCC_DisableLowVoltageDetect());

    HAL_FUNC_ALTER(pCfg->VDDOverCurrent,    HAL_SYSCTRL_VDD_EnableOverCurrentDetect(),
                                            HAL_SYSCTRL_VDD_DisableOverCurrentDetect());

    HAL_FUNC_ALTER(pCfg->VDDLowVoltage,     HAL_SYSCTRL_VDD_EnableLowVoltageDetect(),
                                            HAL_SYSCTRL_VDD_DisableLowVoltageDetect());

    HAL_SYSCTRL_LockSystemRegister();

    return HAL_OK;
}



void HAL_SYSCTRL_IRQHandler(void)
{
    SYSCTRL_TypeDef *p_instance = SYSCTRL_GET_INSTANCE;
    //VDD OverCurrent Interrupt Handler
    if (LL_SYSCTRL_VDD_IsOverCurrentActived(p_instance)) {
        //LOG_D("VDD Over Current INT.\n");

        //Callback
        HAL_SYSCTRL_VDDOverCurCallback(p_instance);
    }

    //VDD LowVoltage Interrupt Handler
    if (LL_SYSCTRL_VDD_IsLowVoltageActived(p_instance)) {
        //LOG_D("VDD Low Voltage INT.\n");

        //Callback
        //HAL_SYSCTRL_VDDLowVolCallback(p_instance);
    }

    //VCC LowVoltage Interrupt Handler
    if (LL_SYSCTRL_VCC_IsLowVoltageActived(p_instance)) {
        //LOG_D("VCC Low Voltage INT.\n");

        //Callback
        HAL_SYSCTRL_VCCLowVolCallback(p_instance);
    }

    //AVCC LowVoltage Interrupt Handler
    if (LL_SYSCTRL_AVCC_IsLowVoltageActived(p_instance)) {
        //LOG_D("AVCC Low Voltage INT.\n");

        //Callback
        HAL_SYSCTRL_AVCCLowVolCallback(p_instance);
    }
}


/**
 * @brief Configure the ADC Buffer.
 * @param pCfg      Pointer to a HAL_SYSCTRL_ADCBufTypeDef configuration
 * @retval  HAL_OK      - Configuration successful.
 * @retval  HAL_INVALID - Invalid parameter.
 */
HAL_StatusTypeDef HAL_SYSCTRL_ADCBufferConfig(HAL_SYSCTRL_ADCBufTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_SYSCTRL_ENABLE(pCfg->BufferEnable));
    ASSERT_FUNC_PARAM(IS_SYSCTRL_ENABLE(pCfg->BufferBypass));
    ASSERT_FUNC_PARAM(IS_SYSCTRL_ADC_BUF_SRC(pCfg->BufferSource));

    HAL_SYSCTRL_PARAM_CHECK({
        if (pCfg == NULL) {
            return HAL_INVALID;
        }     
        
        if ((!IS_SYSCTRL_ENABLE(pCfg->BufferEnable)) ||
            (!IS_SYSCTRL_ENABLE(pCfg->BufferBypass)) ||
            (!IS_SYSCTRL_ADC_BUF_SRC(pCfg->BufferSource))) {
            return HAL_INVALID;
        } 
    });

    HAL_SYSCTRL_UnlockSystemRegister();

    HAL_SYSCTRL_SetADCBufferSource(pCfg->BufferSource);

    HAL_FUNC_ALTER(pCfg->BufferBypass,  HAL_SYSCTRL_EnableADCBufferBypass(),
                                        HAL_SYSCTRL_DisableADCBufferBypass());

    HAL_FUNC_ALTER(pCfg->BufferEnable,  HAL_SYSCTRL_EnableADCBuffer(),
                                        HAL_SYSCTRL_DisableADCBuffer());

    HAL_SYSCTRL_LockSystemRegister();

    return HAL_OK;
}

/**
  * @brief  SYSCTRL VDD Over Current Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void HAL_SYSCTRL_VDDOverCurCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_VDDOverCurCallback could be implemented in the user file
     */
}

/**
  * @brief  SYSCTRL VDD Low Voltage Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void HAL_SYSCTRL_VDDLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_VDDLowVolCallback could be implemented in the user file
     */
}

/**
  * @brief  SYSCTRL VCC Low Voltage Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void HAL_SYSCTRL_VCCLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_VCCLowVolCallback could be implemented in the user file
     */
}

/**
  * @brief  SYSCTRL AVCC Low Voltage Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void HAL_SYSCTRL_AVCCLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_AVCCLowVolCallback could be implemented in the user file
     */
}

/**
  * @}
  */ /* SYSCTRL_HAL_EF_Interrupt */

/**
  * @}
  */ /* SYSCTRL_HAL_Exported_Functions */

/* Private Functions ---------------------------------------------------------*/

/**
  * @}
  */ /* SYSCTRL_HAL */

#endif /* HAL_SYSCTRL_MODULE_ENABLED */
#endif /* HAL_MODLE_ENABLED */
#endif /* SYSCTRL */


/**
  * @}
  */ /* TAE32F561x_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
