/**
  ******************************************************************************
  * @file    tae32g58xx_hal_sysctrl.c
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
#include "tae32g58xx_hal.h"


/** @addtogroup TAE32G58xx_HAL_Driver
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
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_TSENSOR)   ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_VBGR)      ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_VR1P2)     ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_VREFN)     ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_VREF)      ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_AVCC)      ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_AVDD)      ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC0_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC1_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC2_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC3_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC4_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC5_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC6_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC7_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_DAC8_OUT)  ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_TOUT)      ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_PLL0_TOUT) ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_ADC0_IN16) ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_ADC1_IN16) ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_ADC2_IN16) ||         \
                                                       ((__VAL__) == HAL_SYSCTRL_ADC_BUF_SRC_ADC3_IN16))           

/**
  * @}
  */ /* SYSCTRL_HAL_EF_Configuration */

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

/**
 * @brief Configure the VREFBUF output.
 * @param pCfg      Pointer to a HAL_SYSCTRL_VrefBufOutputTypeDef configuration
 * @retval  HAL_OK      - Configuration successful.
 * @retval  HAL_INVALID - Invalid parameter.
 */
HAL_StatusTypeDef HAL_SYSCTRL_VrefBufferOutputConfig(HAL_SYSCTRL_VrefBufOutputTypeDef *pCfg)
{
    ASSERT_FUNC_PARAM(pCfg != NULL);
    ASSERT_FUNC_PARAM(IS_SYSCTRL_VREFBUF_REF(pCfg->Reference));
    ASSERT_FUNC_PARAM(IS_SYSCTRL_VREFBUF_VOL(pCfg->OutputVoltage));

    HAL_SYSCTRL_PARAM_CHECK({
        if (pCfg == NULL) {
            return HAL_INVALID;
        }     
        
        if ((!IS_SYSCTRL_VREFBUF_REF(pCfg->Reference)) || 
            (!IS_SYSCTRL_VREFBUF_VOL(pCfg->OutputVoltage))) {
            return HAL_INVALID;
        }
    });

    HAL_SYSCTRL_UnlockSpecialRegister();

    HAL_SYSCTRL_VREFBUF_SetOutputVoltage(pCfg->OutputVoltage);

    if (pCfg->Reference == HAL_SYSCTRL_VREFBUF_REF_INT) {
        HAL_SYSCTRL_VREFBUF_Enable();
    } else if (pCfg->Reference == HAL_SYSCTRL_VREFBUF_REF_EXT) {
        HAL_SYSCTRL_VREFBUF_Disable();
    }

    HAL_SYSCTRL_LockSpecialRegister();

    return HAL_OK;
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
  * @}
  */ /* SYSCTRL_HAL_EF_Configuration */

/** @defgroup SYSCTRL_HAL_EF_Interrupt SYSCTRL Interrupt Handler and Callback
  * @brief    SYSCTRL Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  Enable one or more SYSCTRL interrupt sources.
  * @param  InterruptRequests Bitmask of the interrupt sources to enable. This
  *         parameter can be any combination of @ref HAL_SYSCTRL_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully enabled.
  */
HAL_StatusTypeDef HAL_SYSCTRL_InterruptRequestEnable(HAL_SYSCTRL_ITEnMskTypeDef InterruptRequests)
{
    SYSCTRL_TypeDef *p_instance = SYSCTRL_GET_INSTANCE;

    LL_SYSCTRL_UnlockSystemRegister(p_instance);
    LL_SYSCTRL_EnableIT(p_instance, InterruptRequests);
    LL_SYSCTRL_LockSystemRegister(p_instance);

    return HAL_OK;
}

/**
  * @brief  Disable one or more SYSCTRL interrupt sources.
  * @param  Handle Pointer to a SYSCTRL handle.
  * @param  InterruptRequests Bitmask of the interrupt sources to disable. This
  *         parameter can be any combination of @ref HAL_SYSCTRL_ITEnMskTypeDef.
  * @retval HAL_OK      - Interrupts successfully disabled.
  */
HAL_StatusTypeDef HAL_SYSCTRL_InterruptRequestDisable(HAL_SYSCTRL_ITEnMskTypeDef InterruptRequests)
{
    SYSCTRL_TypeDef *p_instance = SYSCTRL_GET_INSTANCE;

    LL_SYSCTRL_UnlockSystemRegister(p_instance);
    LL_SYSCTRL_DisableIT(p_instance, InterruptRequests);
    LL_SYSCTRL_LockSystemRegister(p_instance);

    return HAL_OK;
}

/**
  * @brief  Handle SYSCTRL interrupt requests.
  * @note   This function checks the status of all PMU event flags (VDD over-
  *         current, VDD low voltage, VCC low voltage, AVCC low voltage) and
  *         invokes the corresponding callback when an event is detected.
  *         It should be called from the SYSCTRL interrupt handler in the
  *         vector table.
  * @retval None
  */
void HAL_SYSCTRL_IRQHandler(void)
{
    SYSCTRL_TypeDef *p_instance = SYSCTRL_GET_INSTANCE;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_SYSCTRL_GetAllEnabledIT(p_instance);
    const uint32_t int_pending = LL_SYSCTRL_GetAllITPending(p_instance);

    /* Build a mask of flags that are both pending and enabled (for registers bitfields aligned) . */
    const uint32_t flag_status_masked = (int_pending & int_en) & LL_SYSCTRL_PSR_IT_FLAG_MSK; 

    /* VDD LowVoltage Interrupt Handler */ 
    if ((flag_status_masked & LL_SYSCTRL_PSR_VDDLVS)) {
        /* Callback */
        HAL_SYSCTRL_VDDLowVolCallback(p_instance);
    }

    /* VCC LowVoltage Interrupt Handler */ 
    if ((flag_status_masked & LL_SYSCTRL_PSR_VCCLVS)) {
        /* Callback */
        HAL_SYSCTRL_VCCLowVolCallback(p_instance);
    }

    /* AVCC LowVoltage Interrupt Handler */ 
    if ((flag_status_masked & LL_SYSCTRL_PSR_AVCCLVS)) {
        /* Callback */
        HAL_SYSCTRL_AVCCLowVolCallback(p_instance);
    }

    /* VDD OverCurrent Interrupt Handler */ 
    if ((flag_status_masked & LL_SYSCTRL_PSR_VDDOCS)) {
        /* Callback */
        HAL_SYSCTRL_VDDOverCurCallback(p_instance);
    }

}

/**
  * @brief  Callback function for SYSCTRL VDD over-current interrupt.
  * @note   This is a weak function which can be overridden by the user to
  *         implement custom VDD over-current handling.
  * @param  Instance Specifies SYSCTRL peripheral
  * @retval None
  */
__WEAK void HAL_SYSCTRL_VDDOverCurCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SYSCTRL_VDDOverCurCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function for SYSCTRL VDD low voltage interrupt.
  * @note   This is a weak function which can be overridden by the user to
  *         implement custom VDD low voltage handling.
  * @param  Instance Specifies SYSCTRL peripheral
  * @retval None
  */
__WEAK void HAL_SYSCTRL_VDDLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SYSCTRL_VDDLowVolCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function for SYSCTRL VCC low voltage interrupt.
  * @note   This is a weak function which can be overridden by the user to
  *         implement custom VCC low voltage handling.
  * @param  Instance Specifies SYSCTRL peripheral
  * @retval None
  */
__WEAK void HAL_SYSCTRL_VCCLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SYSCTRL_VCCLowVolCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function for SYSCTRL AVCC low voltage interrupt.
  * @note   This is a weak function which can be overridden by the user to
  *         implement custom AVCC low voltage handling.
  * @param  Instance Specifies SYSCTRL peripheral
  * @retval None
  */
__WEAK void HAL_SYSCTRL_AVCCLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_SYSCTRL_AVCCLowVolCallback could be implemented in the user file
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
  */ /* TAE32G58xx_HAL_Driver */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

