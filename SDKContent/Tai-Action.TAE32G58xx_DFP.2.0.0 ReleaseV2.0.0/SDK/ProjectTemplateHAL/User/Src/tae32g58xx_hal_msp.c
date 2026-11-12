/**
  ******************************************************************************
  * @file    tae32g58xx_hal_msp.c
  * @author  Tai-Action SD Team
  * @brief   HAL MSP module.
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
#include "main.h"

/** @addtogroup TAE32G58xx_Examples
  * @{
  */

#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)

/** @addtogroup TAE32G58xx_Template_HAL
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/** @defgroup MSP_HAL_Private_Functions MSP HAL Private Functions
  * @brief    MSP HAL Private Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
#if defined(HAL_GPIO_MODULE_ENABLED) && (HAL_GPIO_MODULE_ENABLED == 1)
    //GPIO Msp Init///TODO:This name may be modified.
    HAL_RCU_GPIOA_CLK_ENABLE();
    HAL_RCU_GPIOA_FORCE_RESET();
    HAL_RCU_GPIOA_RELEASE_RESET();
    HAL_RCU_GPIOB_CLK_ENABLE();
    HAL_RCU_GPIOB_FORCE_RESET();
    HAL_RCU_GPIOB_RELEASE_RESET();
    HAL_RCU_GPIOC_CLK_ENABLE();
    HAL_RCU_GPIOC_FORCE_RESET();
    HAL_RCU_GPIOC_RELEASE_RESET();
    HAL_RCU_GPIOD_CLK_ENABLE();
    HAL_RCU_GPIOD_FORCE_RESET();
    HAL_RCU_GPIOD_RELEASE_RESET();
    HAL_RCU_GPIOE_CLK_ENABLE();
    HAL_RCU_GPIOE_FORCE_RESET();
    HAL_RCU_GPIOE_RELEASE_RESET();
    HAL_RCU_GPIOF_CLK_ENABLE();
    HAL_RCU_GPIOF_FORCE_RESET();
    HAL_RCU_GPIOF_RELEASE_RESET();
#endif

#if defined(HAL_DMA_MODULE_ENABLED) && (HAL_DMA_MODULE_ENABLED == 1)
    //DMA Msp Init///TODO:This name may be modified.
    HAL_RCU_DMA_CLK_ENABLE();
    HAL_RCU_DMA_FORCE_RESET();
    HAL_RCU_DMA_RELEASE_RESET();

    //DMA Channel Interrupt Enable
    HAL_NVIC_EnableIRQ(DMA_CH0_IRQn);
    HAL_NVIC_EnableIRQ(DMA_CH1_IRQn);
    HAL_NVIC_EnableIRQ(DMA_CH2_IRQn);
    HAL_NVIC_EnableIRQ(DMA_CH3_IRQn);
    HAL_NVIC_EnableIRQ(DMA_CH4_IRQn);
    HAL_NVIC_EnableIRQ(DMA_CH5_IRQn);
#endif

#if defined(HAL_EFLASH_MODULE_ENABLED) && (HAL_EFLASH_MODULE_ENABLED == 1)
    //EFLASH Msp Init
    HAL_NVIC_EnableIRQ(EFLASH_IRQn);
#endif

#if defined(HAL_ADC_MODULE_ENABLED) && (HAL_ADC_MODULE_ENABLED == 1)
    HAL_RCU_ADC_FORCE_RESET();
    HAL_RCU_ADC_RELEASE_RESET();
#endif

#if defined(HAL_CMP_MODULE_ENABLED) && (HAL_CMP_MODULE_ENABLED == 1)
    //CMP Msp Init
    HAL_RCU_CMP_CLK_ENABLE();
    HAL_RCU_CMP_FORCE_RESET();
    HAL_RCU_CMP_RELEASE_RESET();

    HAL_NVIC_EnableIRQ(CMPG0_IRQn);
    HAL_NVIC_EnableIRQ(CMPG1_IRQn);
    HAL_NVIC_EnableIRQ(CMPG2_IRQn);
#endif

#if defined(HAL_DAC_MODULE_ENABLED) && (HAL_DAC_MODULE_ENABLED == 1)
    //DAC Msp Init
    HAL_RCU_DAC_CLK_ENABLE();
    HAL_RCU_DAC_FORCE_RESET();
    HAL_RCU_DAC_RELEASE_RESET();
#endif
}

/**
  * @brief  DeInitializes the Global MSP
  * @param  None
  * @retval None
  */
void HAL_MspDeInit(void)
{
#if defined(HAL_GPIO_MODULE_ENABLED) && (HAL_GPIO_MODULE_ENABLED == 1)
    //GPIO Msp DeInit
    HAL_RCU_GPIOA_FORCE_RESET();
    HAL_RCU_GPIOA_RELEASE_RESET();
    HAL_RCU_GPIOB_FORCE_RESET();
    HAL_RCU_GPIOB_RELEASE_RESET();
    HAL_RCU_GPIOC_FORCE_RESET();
    HAL_RCU_GPIOC_RELEASE_RESET();
    HAL_RCU_GPIOD_FORCE_RESET();
    HAL_RCU_GPIOD_RELEASE_RESET();
    HAL_RCU_GPIOE_FORCE_RESET();
    HAL_RCU_GPIOE_RELEASE_RESET();
    HAL_RCU_GPIOF_FORCE_RESET();
    HAL_RCU_GPIOF_RELEASE_RESET();
#endif

#if defined(HAL_DMA_MODULE_ENABLED) && (HAL_DMA_MODULE_ENABLED == 1)
    //DMA Msp DeInit
    HAL_RCU_DAC_CLK_DISABLE();
    HAL_RCU_DMA_RELEASE_RESET();

    //DMA Channel Interrupt Disable
    HAL_NVIC_DisableIRQ(DMA_CH0_IRQn);
    HAL_NVIC_DisableIRQ(DMA_CH1_IRQn);
    HAL_NVIC_DisableIRQ(DMA_CH2_IRQn);
    HAL_NVIC_DisableIRQ(DMA_CH3_IRQn);
    HAL_NVIC_DisableIRQ(DMA_CH4_IRQn);
    HAL_NVIC_DisableIRQ(DMA_CH5_IRQn);
#endif

#if defined(HAL_EFLASH_MODULE_ENABLED) && (HAL_EFLASH_MODULE_ENABLED == 1)
    //EFLASH Msp DeInit
    HAL_NVIC_DisableIRQ(EFLASH_IRQn);
#endif

#if defined(HAL_ADC_MODULE_ENABLED) && (HAL_ADC_MODULE_ENABLED == 1)
    HAL_RCU_ADC_RELEASE_RESET();
#endif

#if defined(HAL_CMP_MODULE_ENABLED) && (HAL_CMP_MODULE_ENABLED == 1)
    //CMP Msp Init
    HAL_RCU_CMP_CLK_DISABLE();
    HAL_RCU_CMP_RELEASE_RESET();

    HAL_NVIC_DisableIRQ(CMPG0_IRQn);
    HAL_NVIC_DisableIRQ(CMPG1_IRQn);
    HAL_NVIC_DisableIRQ(CMPG2_IRQn);
#endif

#if defined(HAL_DAC_MODULE_ENABLED) && (HAL_DAC_MODULE_ENABLED == 1)
    //DAC Msp Init
    HAL_RCU_DAC_CLK_DISABLE();
    HAL_RCU_DAC_RELEASE_RESET();
#endif
}

#if defined(HAL_HRPWM_MODULE_ENABLED) && (HAL_HRPWM_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the HRPWM MSP
  * @param  Handle HRPWM Handle
  * @retval None
  */
void LL_HRPWM_MspInit(HAL_HRPWM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    //HRPWM Bus Clock Enable and Soft Reset
    HAL_RCU_HRPWM_CLK_ENABLE();
    HAL_RCU_HRPWM_FORCE_RESET();
    HAL_RCU_HRPWM_RELEASE_RESET();

    //NVIC HRPAM Interrupt Enable
    HAL_NVIC_EnableIRQ(HRPWM_MST_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV0_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV1_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV2_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV3_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV4_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV5_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV6_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_SLV7_IRQn);
    HAL_NVIC_EnableIRQ(HRPWM_COM_IRQn);
}

/**
  * @brief  DeInitializes the HRPWM MSP
  * @param  Handle HRPWM Handle
  * @retval None
  */
void LL_HRPWM_MspDeInit(HAL_HRPWM_HandleTypeDef *Handle)
{
    //Assert param
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(Handle->Instance));

    //HRPWM Bus Clock Disable and Soft Reset Assert
    HAL_RCU_HRPWM_CLK_DISABLE();
    HAL_RCU_HRPWM_RELEASE_RESET();

    //NVIC HRPAM Interrupt Disable
    HAL_NVIC_DisableIRQ(HRPWM_MST_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV0_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV1_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV2_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV3_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV4_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV5_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV6_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_SLV7_IRQn);
    HAL_NVIC_DisableIRQ(HRPWM_COM_IRQn);
}
#endif

#if defined(HAL_ADC_MODULE_ENABLED) && (HAL_ADC_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the ADC MSP
  * @param  Handle ADC Handle
  * @retval None
  */
void HAL_ADC_MspInit(HAL_ADC_HandleTypeDef *Handle)
{
    //Assert param
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ADC_TypeDef *p_instance = Handle->Instance;

    if (p_instance == ADC0) {
        //ADC0 Bus Clock Enable 
        HAL_RCU_ADC0_CLK_ENABLE();

        //NVIC ADC0 Interrupt Enable
        HAL_NVIC_EnableIRQ(ADC0_NORM_IRQn);
        HAL_NVIC_EnableIRQ(ADC0_SAMP_IRQn);
        HAL_NVIC_EnableIRQ(ADC0_HALF_IRQn);
        HAL_NVIC_EnableIRQ(ADC0_FULL_IRQn);

    } else if (p_instance == ADC1) {

        //ADC1 Bus Clock Enable 
        HAL_RCU_ADC1_CLK_ENABLE();

        //NVIC ADC1 Interrupt Enable
        HAL_NVIC_EnableIRQ(ADC1_NORM_IRQn);
        HAL_NVIC_EnableIRQ(ADC1_SAMP_IRQn);
        HAL_NVIC_EnableIRQ(ADC1_HALF_IRQn);
        HAL_NVIC_EnableIRQ(ADC1_FULL_IRQn);

    } else if (p_instance == ADC2) {

        //ADC2 Bus Clock Enable 
        HAL_RCU_ADC2_CLK_ENABLE();

        //NVIC ADC2 Interrupt Enable
        HAL_NVIC_EnableIRQ(ADC2_NORM_IRQn);
        HAL_NVIC_EnableIRQ(ADC2_SAMP_IRQn);
        HAL_NVIC_EnableIRQ(ADC2_HALF_IRQn);
        HAL_NVIC_EnableIRQ(ADC2_FULL_IRQn);

    } else if (p_instance == ADC3) {

        //ADC3 Bus Clock Enable 
        HAL_RCU_ADC3_CLK_ENABLE();

        //NVIC ADC3 Interrupt Enable
        HAL_NVIC_EnableIRQ(ADC3_NORM_IRQn);
        HAL_NVIC_EnableIRQ(ADC3_SAMP_IRQn);
        HAL_NVIC_EnableIRQ(ADC3_HALF_IRQn);
        HAL_NVIC_EnableIRQ(ADC3_FULL_IRQn);
    }
}

/**
  * @brief  DeInitializes the ADC MSP
  * @param  Handle ADC Handle
  * @retval None
  */
void HAL_ADC_MspDeInit(HAL_ADC_HandleTypeDef *Handle)
{
    //Assert param
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(Handle->Instance));

    ADC_TypeDef *p_instance = Handle->Instance;

    if (p_instance == ADC0) {
        //NVIC ADC0 Interrupt Disable
        HAL_NVIC_DisableIRQ(ADC0_NORM_IRQn);
        HAL_NVIC_DisableIRQ(ADC0_SAMP_IRQn);
        HAL_NVIC_DisableIRQ(ADC0_HALF_IRQn);
        HAL_NVIC_DisableIRQ(ADC0_FULL_IRQn);

        //ADC0 Bus Clock Disable
        HAL_RCU_ADC0_CLK_DISABLE();

    } else if (p_instance == ADC1) {

        //NVIC ADC1 Interrupt Disable
        HAL_NVIC_DisableIRQ(ADC1_NORM_IRQn);
        HAL_NVIC_DisableIRQ(ADC1_SAMP_IRQn);
        HAL_NVIC_DisableIRQ(ADC1_HALF_IRQn);
        HAL_NVIC_DisableIRQ(ADC1_FULL_IRQn);

        //ADC1 Bus Clock Disable
        HAL_RCU_ADC1_CLK_DISABLE();

    } else if (p_instance == ADC2) {

        //NVIC ADC2 Interrupt Disable
        HAL_NVIC_DisableIRQ(ADC2_NORM_IRQn);
        HAL_NVIC_DisableIRQ(ADC2_SAMP_IRQn);
        HAL_NVIC_DisableIRQ(ADC2_HALF_IRQn);
        HAL_NVIC_DisableIRQ(ADC2_FULL_IRQn);

        //ADC2 Bus Clock Disable
        HAL_RCU_ADC2_CLK_DISABLE();

    } else if (p_instance == ADC3) {

        //NVIC ADC3 Interrupt Disable
        HAL_NVIC_DisableIRQ(ADC3_NORM_IRQn);
        HAL_NVIC_DisableIRQ(ADC3_SAMP_IRQn);
        HAL_NVIC_DisableIRQ(ADC3_HALF_IRQn);
        HAL_NVIC_DisableIRQ(ADC3_FULL_IRQn);

        //ADC3 Bus Clock Disable
        HAL_RCU_ADC3_CLK_DISABLE();
    }
}
#endif

#if defined(HAL_CAN_MODULE_ENABLED) && (HAL_CAN_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the CAN MSP
  * @param  Handle CAN Handle
  * @retval None
  */
void HAL_CAN_MspInit(HAL_CAN_HandleTypeDef *Handle)
{
    //Assert param
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    CAN_TypeDef *p_instance = Handle->Instance;
    
    if (p_instance == CAN0) {
        //CAN0 Bus Clock Enable and Soft Reset
        HAL_RCU_CAN0_CLK_ENABLE();
        HAL_RCU_CAN0_FORCE_RESET();
        HAL_RCU_CAN0_RELEASE_RESET();

        //NVIC CAN0 Interrupt Enable
        HAL_NVIC_EnableIRQ(CAN0_INT0_IRQn);
        HAL_NVIC_EnableIRQ(CAN0_INT1_IRQn);

    } else if (p_instance == CAN1) {
        //CAN1 Bus Clock Enable and Soft Reset
        HAL_RCU_CAN1_CLK_ENABLE();
        HAL_RCU_CAN1_FORCE_RESET();
        HAL_RCU_CAN1_RELEASE_RESET();

        //NVIC CAN1 Interrupt Enable
        HAL_NVIC_EnableIRQ(CAN1_INT0_IRQn);
        HAL_NVIC_EnableIRQ(CAN1_INT1_IRQn);
    }
}

/**
  * @brief  DeInitializes the CAN MSP
  * @param  Handle CAN Handle
  * @retval None
  */
void HAL_CAN_MspDeInit(HAL_CAN_HandleTypeDef *Handle)
{
    //Assert param
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(Handle->Instance));

    CAN_TypeDef *p_instance = Handle->Instance;

    if (p_instance == CAN0) {
        //NVIC CAN0 Interrupt Disable
        HAL_NVIC_DisableIRQ(CAN0_INT0_IRQn);
        HAL_NVIC_DisableIRQ(CAN0_INT1_IRQn);

        //CAN0 Bus Clock Disable and Soft Reset
        HAL_RCU_CAN0_CLK_DISABLE();
        HAL_RCU_CAN0_RELEASE_RESET();

    }  else if (p_instance == CAN1) {
        //NVIC CAN1 Interrupt Disable
        HAL_NVIC_DisableIRQ(CAN1_INT0_IRQn);
        HAL_NVIC_DisableIRQ(CAN1_INT1_IRQn);

        //CAN1 Bus Clock Disable and Soft Reset 
        HAL_RCU_CAN1_CLK_DISABLE();
        HAL_RCU_CAN1_RELEASE_RESET();
    }
}
#endif

#if defined(HAL_DAC_MODULE_ENABLED) && (HAL_DAC_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the DAC MSP
  * @param  Handle DAC Handle
  * @return None
  */
void HAL_DAC_MspInit(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Already handled in HAL_MspInit */
}

/**
  * @brief  DeInitializes the DAC MSP
  * @param  Handle DAC Handle
  * @retval None
  */
void HAL_DAC_MspDeInit(HAL_DAC_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(Handle->Instance));

    /* Already handled in HAL_MspInit */
}
#endif

#if defined(HAL_CMP_MODULE_ENABLED) && (HAL_CMP_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the CMP MSP
  * @param  Handle CMP Handle
  * @retval None
  */
void HAL_CMP_MspInit(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    /* Already handled in HAL_MspInit */
}

/**
  * @brief  DeInitializes the CMP MSP
  * @param  Handle CMP Handle
  * @retval None
  */
void HAL_CMP_MspDeInit(HAL_CMP_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(Handle->Instance));

    /* Already handled in HAL_MspInit */
}
#endif

#if defined(HAL_IIR_MODULE_ENABLED) && (HAL_IIR_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the IIR MSP
  * @param  Handle IIR Handle
  * @retval None
  */
void HAL_IIR_MspInit(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    IIR_TypeDef *p_instance = Handle->Instance;
    
    if (p_instance == IIR0) {

        //IIR0 Bus Clock Enable and Soft Reset
        HAL_RCU_IIR0_CLK_ENABLE();
        HAL_RCU_IIR0_FORCE_RESET();
        HAL_RCU_IIR0_RELEASE_RESET();

    } else if (p_instance == IIR1) {

        //IIR1 Bus Clock Enable and Soft Reset
        HAL_RCU_IIR1_CLK_ENABLE();
        HAL_RCU_IIR1_FORCE_RESET();
        HAL_RCU_IIR1_RELEASE_RESET();
    } else if (p_instance == IIR2) {

        //IIR2 Bus Clock Enable and Soft Reset
        HAL_RCU_IIR2_CLK_ENABLE();
        HAL_RCU_IIR2_FORCE_RESET();
        HAL_RCU_IIR2_RELEASE_RESET();
    } else if (p_instance == IIR3) {

        //IIR3 Bus Clock Enable and Soft Reset
        HAL_RCU_IIR3_CLK_ENABLE();
        HAL_RCU_IIR3_FORCE_RESET();
        HAL_RCU_IIR3_RELEASE_RESET();
    } else if (p_instance == IIR4) {

        //IIR4 Bus Clock Enable and Soft Reset
        HAL_RCU_IIR4_CLK_ENABLE();
        HAL_RCU_IIR4_FORCE_RESET();
        HAL_RCU_IIR4_RELEASE_RESET();
    } else if (p_instance == IIR5) {

        //IIR5 Bus Clock Enable and Soft Reset
        HAL_RCU_IIR5_CLK_ENABLE();
        HAL_RCU_IIR5_FORCE_RESET();
        HAL_RCU_IIR5_RELEASE_RESET();
    }

    //NVIC IIR0 Interrupt Enable
    HAL_NVIC_EnableIRQ(IIR_IRQn);
}

/**
  * @brief  DeInitializes the IIR MSP
  * @param  Handle IIR Handle
  * @retval None
  */
void HAL_IIR_MspDeInit(HAL_IIR_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_IIR_ALL_INSTANCE(Handle->Instance));

    IIR_TypeDef *p_instance = Handle->Instance;

    //NVIC IIR0 Interrupt Disable
    HAL_NVIC_DisableIRQ(IIR_IRQn);

    if (p_instance == IIR0) {

        //IIR0 Bus Clock Disable and Soft Reset Release
        HAL_RCU_IIR0_CLK_DISABLE();
        HAL_RCU_IIR0_RELEASE_RESET();

    } else if (p_instance == IIR1) {

        //IIR1 Bus Clock Disable and Soft Reset Release
        HAL_RCU_IIR1_CLK_DISABLE();
        HAL_RCU_IIR1_RELEASE_RESET();
    } else if (p_instance == IIR2) {

        //IIR2 Bus Clock Disable and Soft Reset Release
        HAL_RCU_IIR2_CLK_DISABLE();
        HAL_RCU_IIR2_RELEASE_RESET();
    } else if (p_instance == IIR3) {

        //IIR3 Bus Clock Disable and Soft Reset Release
        HAL_RCU_IIR3_CLK_DISABLE();
        HAL_RCU_IIR3_RELEASE_RESET();
    } else if (p_instance == IIR4) {

        //IIR4 Bus Clock Disable and Soft Reset Release
        HAL_RCU_IIR4_CLK_DISABLE();
        HAL_RCU_IIR4_RELEASE_RESET();
    } else if (p_instance == IIR5) {

        //IIR5 Bus Clock Disable and Soft Reset Release
        HAL_RCU_IIR5_CLK_DISABLE();
        HAL_RCU_IIR5_RELEASE_RESET();
    }
}
#endif

#if defined(HAL_QEI_MODULE_ENABLED) && (HAL_QEI_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the QEI MSP
  * @param  Handle QEI Handle
  * @retval None
  */
void HAL_QEI_MspInit(HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    QEI_TypeDef *p_instance = Handle->Instance;
    
    if (p_instance == QEI0) {
        //QEI0 Bus Clock Enable and Soft Reset 
        HAL_RCU_QEI0_CLK_ENABLE();
        HAL_RCU_QEI0_FORCE_RESET();
        HAL_RCU_QEI0_RELEASE_RESET();

        //NVIC QEI0 Interrupt Enable
        HAL_NVIC_EnableIRQ(QEI0_IRQn);

    } else if (p_instance == QEI1) {
        //QEI1 Bus Clock Enable and Soft Reset 
        HAL_RCU_QEI1_CLK_ENABLE();
        HAL_RCU_QEI1_FORCE_RESET();
        HAL_RCU_QEI1_RELEASE_RESET();

        //NVIC QEI1 Interrupt Enable
        HAL_NVIC_EnableIRQ(QEI1_IRQn);
    } else if (p_instance == QEI2) {
        //QEI2 Bus Clock Enable and Soft Reset 
        HAL_RCU_QEI2_CLK_ENABLE();
        HAL_RCU_QEI2_FORCE_RESET();
        HAL_RCU_QEI2_RELEASE_RESET();

        //NVIC QEI2 Interrupt Enable
        HAL_NVIC_EnableIRQ(QEI2_IRQn);
    }
}

/**
  * @brief  DeInitializes the QEI MSP
  * @param  Handle QEI Handle
  * @retval None
  */
void HAL_QEI_MspDeInit(HAL_QEI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(Handle->Instance));

    QEI_TypeDef *p_instance = Handle->Instance;

    if (p_instance == QEI0) {
        //NVIC QEI0 Interrupt Disable
        HAL_NVIC_DisableIRQ(QEI0_IRQn);

        //QEI0 Bus Clock Disable and Soft Reset Release
        HAL_RCU_QEI0_CLK_DISABLE();
        HAL_RCU_QEI0_RELEASE_RESET();

    }  else if (p_instance == QEI1) {
        //NVIC QEI1 Interrupt Disable
        HAL_NVIC_DisableIRQ(QEI1_IRQn);

        //QEI1 Bus Clock Disable and Soft Reset Release
        HAL_RCU_QEI1_CLK_DISABLE();
        HAL_RCU_QEI1_RELEASE_RESET();
    }  else if (p_instance == QEI2) {

        //NVIC QEI2 Interrupt Disable
        HAL_NVIC_DisableIRQ(QEI2_IRQn);

        //QEI2 Bus Clock Disable and Soft Reset Release
        HAL_RCU_QEI2_CLK_DISABLE();
        HAL_RCU_QEI2_RELEASE_RESET();
    }
}
#endif /* HAL_QEI_MODULE_ENABLED */

#if defined(HAL_SPI_MODULE_ENABLED) && (HAL_SPI_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the SPI MSP
  * @param  Handle SPI Handle
  * @retval None
  */
void HAL_SPI_MspInit(HAL_SPI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(Handle->Instance));

    SPI_TypeDef *p_instance = Handle->Instance;

    if (p_instance == SPI0) {
        //SPI0 Bus Clock Enable and Soft Reset
        HAL_RCU_SPI0_CLK_ENABLE();
        HAL_RCU_SPI0_FORCE_RESET();
        HAL_RCU_SPI0_RELEASE_RESET();

        //NVIC SPI0 Interrupt Enable
        HAL_NVIC_EnableIRQ(SPI0_IRQn);

    } else if (p_instance == SPI1) {
        //SPI1 Bus Clock Enable and Soft Reset
        HAL_RCU_SPI1_CLK_ENABLE();
        HAL_RCU_SPI1_FORCE_RESET();
        HAL_RCU_SPI1_RELEASE_RESET();

        //NVIC SPI1 Interrupt Enable
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
    }
}

/**
  * @brief  DeInitializes the SPI MSP
  * @param  Handle SPI Handle
  * @retval None
  */
void HAL_SPI_MspDeInit(HAL_SPI_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(Handle->Instance));

    SPI_TypeDef *p_instance = Handle->Instance;

    if (p_instance == SPI0) {
        //NVIC SPI0 Interrupt Disable
        HAL_NVIC_DisableIRQ(SPI0_IRQn);

        //SPI0 Bus Clock Disable and Soft Reset Release
        HAL_RCU_SPI0_CLK_DISABLE();
        HAL_RCU_SPI0_RELEASE_RESET();

    } else if (p_instance == SPI1) {
        //NVIC SPI1 Interrupt Disable
        HAL_NVIC_DisableIRQ(SPI1_IRQn);

        //SPI1 Bus Clock Disable and Soft Reset Release
        HAL_RCU_SPI1_CLK_DISABLE();
        HAL_RCU_SPI1_RELEASE_RESET();
    }
}
#endif /* HAL_SPI_MODULE_ENABLED */

#if defined(HAL_I2C_MODULE_ENABLED) && (HAL_I2C_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the I2C MSP
  * @param  Handle I2C Handle
  * @retval None
  */
void HAL_I2C_MspInit(HAL_I2C_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_I2C_ALL_INSTANCE(Handle->Instance));

    I2C_TypeDef *p_instance = Handle->Instance;

    if (p_instance == I2C0) {
        //I2C0 Bus Clock Enable and Soft Reset
        HAL_RCU_I2C0_CLK_ENABLE();
        HAL_RCU_I2C0_FORCE_RESET();
        HAL_RCU_I2C0_RELEASE_RESET();

        //NVIC I2C0 Interrupt Enable
        HAL_NVIC_EnableIRQ(I2C0_IRQn);

    } else if (p_instance == I2C1) {
        //I2C1 Bus Clock Enable and Soft Reset
        HAL_RCU_I2C1_CLK_ENABLE();
        HAL_RCU_I2C1_FORCE_RESET();
        HAL_RCU_I2C1_RELEASE_RESET();

        //NVIC I2C1 Interrupt Enable
        HAL_NVIC_EnableIRQ(I2C1_IRQn);

    } else if (p_instance == I2C2) {
        //I2C2 Bus Clock Enable and Soft Reset
        HAL_RCU_I2C2_CLK_ENABLE();
        HAL_RCU_I2C2_FORCE_RESET();
        HAL_RCU_I2C2_RELEASE_RESET();

        //NVIC I2C2 Interrupt Enable
        HAL_NVIC_EnableIRQ(I2C2_IRQn);
    }
}

/**
  * @brief  DeInitializes the I2C MSP
  * @param  Handle I2C Handle
  * @retval None
  */
void HAL_I2C_MspDeInit(HAL_I2C_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_I2C_ALL_INSTANCE(Handle->Instance));

    I2C_TypeDef *p_instance = Handle->Instance;

    if (p_instance == I2C0) {
        //NVIC I2C0 Interrupt Disable
        HAL_NVIC_DisableIRQ(I2C0_IRQn);

        //I2C0 Bus Clock Disable and Soft Reset Release
        HAL_RCU_I2C0_CLK_DISABLE();
        HAL_RCU_I2C0_RELEASE_RESET();

    } else if (p_instance == I2C1) {
        //NVIC I2C1 Interrupt Disable
        HAL_NVIC_DisableIRQ(I2C1_IRQn);

        //I2C1 Bus Clock Disable and Soft Reset Release
        HAL_RCU_I2C1_CLK_DISABLE();
        HAL_RCU_I2C1_RELEASE_RESET();

    } else if (p_instance == I2C2) {
        //NVIC I2C2 Interrupt Disable
        HAL_NVIC_DisableIRQ(I2C2_IRQn);

        //I2C2 Bus Clock Disable and Soft Reset Release
        HAL_RCU_I2C2_CLK_DISABLE();
        HAL_RCU_I2C2_RELEASE_RESET();
    }
}
#endif /* HAL_I2C_MODULE_ENABLED */

#if defined(HAL_UART_MODULE_ENABLED) && (HAL_UART_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the UART MSP
  * @param  Handle UART Handle
  * @retval None
  */
void HAL_UART_MspInit(HAL_UART_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(Handle->Instance));

    UART_TypeDef *p_instance = Handle->Instance;

    if (p_instance == UART0) {
        //UART0 Bus Clock Enable and Soft Reset
        HAL_RCU_UART0_CLK_ENABLE();
        HAL_RCU_UART0_FORCE_RESET();
        HAL_RCU_UART0_RELEASE_RESET();

        //NVIC UART0 Interrupt Enable
        HAL_NVIC_EnableIRQ(UART0_IRQn);

    } else if (p_instance == UART1) {
        //UART1 Bus Clock Enable and Soft Reset
        HAL_RCU_UART1_CLK_ENABLE();
        HAL_RCU_UART1_FORCE_RESET();
        HAL_RCU_UART1_RELEASE_RESET();

        //NVIC UART1 Interrupt Enable
        HAL_NVIC_EnableIRQ(UART1_IRQn);

    } else if (p_instance == UART2) {
        //UART2 Bus Clock Enable and Soft Reset
        HAL_RCU_UART2_CLK_ENABLE();
        HAL_RCU_UART2_FORCE_RESET();
        HAL_RCU_UART2_RELEASE_RESET();

        //NVIC UART2 Interrupt Enable
        HAL_NVIC_EnableIRQ(UART2_IRQn);

    } else if (p_instance == UART3) {
        //UART3 Bus Clock Enable and Soft Reset
        HAL_RCU_UART3_CLK_ENABLE();
        HAL_RCU_UART3_FORCE_RESET();
        HAL_RCU_UART3_RELEASE_RESET();

        //NVIC UART3 Interrupt Enable
        HAL_NVIC_EnableIRQ(UART3_IRQn);

    } else if (p_instance == UART4) {
        //UART4 Bus Clock Enable and Soft Reset
        HAL_RCU_UART4_CLK_ENABLE();
        HAL_RCU_UART4_FORCE_RESET();
        HAL_RCU_UART4_RELEASE_RESET();

        //NVIC UART4 Interrupt Enable
        HAL_NVIC_EnableIRQ(UART4_IRQn);
    }
}

/**
  * @brief  DeInitializes the UART MSP
  * @param  Handle UART Handle
  * @retval None
  */
void HAL_UART_MspDeInit(HAL_UART_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(Handle->Instance));

    UART_TypeDef *p_instance = Handle->Instance;

    if (p_instance == UART0) {
        //NVIC UART0 Interrupt Disable
        HAL_NVIC_DisableIRQ(UART0_IRQn);

        //UART0 Bus Clock Disable and Soft Reset Release
        HAL_RCU_UART0_CLK_DISABLE();
        HAL_RCU_UART0_RELEASE_RESET();

    } else if (p_instance == UART1) {
        //NVIC UART1 Interrupt Disable
        HAL_NVIC_DisableIRQ(UART1_IRQn);

        //UART1 Bus Clock Disable and Soft Reset Release
        HAL_RCU_UART1_CLK_DISABLE();
        HAL_RCU_UART1_RELEASE_RESET();

    } else if (p_instance == UART2) {
        //NVIC UART2 Interrupt Disable
        HAL_NVIC_DisableIRQ(UART2_IRQn);

        //UART2 Bus Clock Disable and Soft Reset Release
        HAL_RCU_UART2_CLK_DISABLE();
        HAL_RCU_UART2_RELEASE_RESET();

    } else if (p_instance == UART3) {
        //NVIC UART3 Interrupt Disable
        HAL_NVIC_DisableIRQ(UART3_IRQn);

        //UART3 Bus Clock Disable and Soft Reset Release
        HAL_RCU_UART3_CLK_DISABLE();
        HAL_RCU_UART3_RELEASE_RESET();

    } else if (p_instance == UART4) {
        //NVIC UART4 Interrupt Disable
        HAL_NVIC_DisableIRQ(UART4_IRQn);

        //UART4 Bus Clock Disable and Soft Reset Release
        HAL_RCU_UART4_CLK_DISABLE();
        HAL_RCU_UART4_RELEASE_RESET();
    }
}
#endif /* HAL_UART_MODULE_ENABLED */

#if defined(HAL_PDM_MODULE_ENABLED) && (HAL_PDM_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the PDM MSP
  * @param  Handle PDM Handle
  * @retval None
  */
void HAL_PDM_MspInit(HAL_PDM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_PDM_ALL_INSTANCE(Handle->Instance));

    PDM_TypeDef *p_instance = Handle->Instance;

    if (p_instance == PDM0) {
        //PDM0 Bus Clock Enable and Soft Reset
        HAL_RCU_PDM0_CLK_ENABLE();
        HAL_RCU_PDM0_FORCE_RESET();
        HAL_RCU_PDM0_RELEASE_RESET();

        //NVIC PDM0 Interrupt Enable
        HAL_NVIC_EnableIRQ(PDM0_IRQn);

    } else if (p_instance == PDM1) {
        //PDM1 Bus Clock Enable and Soft Reset
        HAL_RCU_PDM1_CLK_ENABLE();
        HAL_RCU_PDM1_FORCE_RESET();
        HAL_RCU_PDM1_RELEASE_RESET();

        //NVIC PDM1 Interrupt Enable
        HAL_NVIC_EnableIRQ(PDM1_IRQn);

    } else if (p_instance == PDM2) {
        //PDM2 Bus Clock Enable and Soft Reset
        HAL_RCU_PDM2_CLK_ENABLE();
        HAL_RCU_PDM2_FORCE_RESET();

        //NVIC PDM2 Interrupt Enable
        HAL_NVIC_EnableIRQ(PDM2_IRQn);

    } else if (p_instance == PDM3) {
        //PDM3 Bus Clock Enable and Soft Reset
        HAL_RCU_PDM3_CLK_ENABLE();
        HAL_RCU_PDM3_FORCE_RESET();
        HAL_RCU_PDM3_RELEASE_RESET();

        //NVIC PDM3 Interrupt Enable
        HAL_NVIC_EnableIRQ(PDM3_IRQn);
    }
}

/**
  * @brief  DeInitializes the PDM MSP
  * @param  Handle PDM Handle
  * @retval None
  */
void HAL_PDM_MspDeInit(HAL_PDM_HandleTypeDef *Handle)
{
    ASSERT_FUNC_PARAM(Handle != NULL);
    ASSERT_FUNC_PARAM(IS_PDM_ALL_INSTANCE(Handle->Instance));

    PDM_TypeDef *p_instance = Handle->Instance;

    if (p_instance == PDM0) {
        //NVIC PDM0 Interrupt Disable
        HAL_NVIC_DisableIRQ(PDM0_IRQn);

        //PDM0 Bus Clock Disable and Soft Reset Release
        HAL_RCU_PDM0_CLK_DISABLE();
        HAL_RCU_PDM0_RELEASE_RESET();

    } else if (p_instance == PDM1) {
        //NVIC PDM1 Interrupt Disable
        HAL_NVIC_DisableIRQ(PDM1_IRQn);

        //PDM1 Bus Clock Disable and Soft Reset Release
        HAL_RCU_PDM1_CLK_DISABLE();
        HAL_RCU_PDM1_RELEASE_RESET();

    } else if (p_instance == PDM2) {
        //NVIC PDM2 Interrupt Disable
        HAL_NVIC_DisableIRQ(PDM2_IRQn);

        //PDM2 Bus Clock Disable and Soft Reset Release
        HAL_RCU_PDM2_CLK_DISABLE();
        HAL_RCU_PDM2_RELEASE_RESET();

    } else if (p_instance == PDM3) {
        //NVIC PDM3 Interrupt Disable
        HAL_NVIC_DisableIRQ(PDM3_IRQn);

        //PDM3 Bus Clock Disable and Soft Reset Release
        HAL_RCU_PDM3_CLK_DISABLE();
        HAL_RCU_PDM3_RELEASE_RESET();
    }
}
#endif /* HAL_PDM_MODULE_ENABLED */

/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_MODULE_ENABLED */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

