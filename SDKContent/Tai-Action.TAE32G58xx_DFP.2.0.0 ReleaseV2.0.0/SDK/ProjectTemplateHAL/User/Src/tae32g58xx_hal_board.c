/**
  ******************************************************************************
  * @file    tae32g58xx_hal_board.c
  * @author  Tai-Action SD Team
  * @brief   HAL Board IO.
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
/** @defgroup BOARD_HAL_Private_Functions BOARD HAL Private Functions
  * @brief    BOARD HAL Private Functions
  * @{
  */

#if defined(HAL_ADC_MODULE_ENABLED) && (HAL_ADC_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the ADC IO
  * @param  ADCx Pointer to the base address of the ADC peripheral.
  * @retval None
  */
void HAL_ADC_IoInit(ADC_TypeDef *ADCx)
{
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    //TODO
}

/**
  * @brief  DeInitializes the ADC IO
  * @param  ADCx Pointer to the base address of the ADC peripheral.
  * @retval None
  */
void HAL_ADC_IoDeInit(ADC_TypeDef *ADCx)
{
    ASSERT_FUNC_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    //TODO
}
#endif /* HAL_ADC_MODULE_ENABLED */

#if defined(HAL_HRPWM_MODULE_ENABLED) && (HAL_HRPWM_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the HRPWM IO
  * @param  HRPWMx Pointer to the base address of the HRPWM peripheral.
  * @retval None
  */
void HAL_HRPWM_IoInit(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    //TODO
}

/**
  * @brief  DeInitializes the HRPWM IO
  * @param  HRPWMx Pointer to the base address of the HRPWM peripheral.
  * @retval None
  */
void HAL_HRPWM_IoDeInit(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_FUNC_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    //TODO
}
#endif /* HAL_HRPWM_MODULE_ENABLED */

#if defined(HAL_CAN_MODULE_ENABLED) && (HAL_CAN_MODULE_ENABLED == 1)
/**
  * @brief  Initializes the CAN IO
  * @param  CANx Pointer to the base address of the CAN peripheral.
  * @retval None
  */
void HAL_CAN_IoInit(CAN_TypeDef *CANx)
{
    //Assert param
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    HAL_GPIO_InitTypeDef CAN_GPIO_Init;
    CAN_TypeDef *p_instance = CANx;

    //CAN GPIO Common Config
    memset((void *)&CAN_GPIO_Init, 0x00, sizeof(CAN_GPIO_Init));

    CAN_GPIO_Init.Mode      = HAL_GPIO_OUTPUT_PUSHPULL;
    CAN_GPIO_Init.Pull      = HAL_GPIO_PULL_NO;   //external hardware Pull Up
    CAN_GPIO_Init.Speed     = HAL_GPIO_SPEED_FREQ_LOW;
    
    if (p_instance == CAN0) {
        //CAN0 Pinmux Config: CAN0_RX->PB3 & CAN0_TX->PB4
        CAN_GPIO_Init.Pin = HAL_GPIO_PIN_3 | HAL_GPIO_PIN_4;
        CAN_GPIO_Init.Alternate = HAL_GPIO_AF_12;
        HAL_GPIO_Init(GPIOB, &CAN_GPIO_Init);

    } else if (p_instance == CAN1) {
        //CAN1 Pinmux Config: CAN1_RX->PB5 & CAN1_TX->PB6
        CAN_GPIO_Init.Pin = HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6;
        CAN_GPIO_Init.Alternate = HAL_GPIO_AF_10;
        HAL_GPIO_Init(GPIOB, &CAN_GPIO_Init);
    }
}

/**
  * @brief  DeInitializes the CAN IO
  * @param  CANx Pointer to the base address of the CAN peripheral.
  * @retval None
  */
void HAL_CAN_IoDeInit(CAN_TypeDef *CANx)
{
    //Assert param
    ASSERT_FUNC_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CAN_TypeDef *p_instance = CANx;

    if (p_instance == CAN0) {
        //CAN0 Pinmux DeInit
        HAL_GPIO_DeInit(GPIOB, HAL_GPIO_PIN_3 | HAL_GPIO_PIN_4);

    }  else if (p_instance == CAN1) {
        //CAN1 Pinmux DeInit
        HAL_GPIO_DeInit(GPIOB, HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6);
    }
}
#endif /* HAL_CAN_MODULE_ENABLED */

#if defined(HAL_DAC_MODULE_ENABLED) && (HAL_DAC_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the DAC IO
  * @param  DACx Pointer to the base address of the DAC peripheral.
  * @retval None
  */
void HAL_DAC_IoInit(DAC_TypeDef* DACx)
{
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    //TODO
}

/**
  * @brief  DeInitializes the DAC IO
  * @param  DACx Pointer to the base address of the DAC peripheral.
  * @retval None
  */
void HAL_DAC_IoDeInit(DAC_TypeDef* DACx)
{
    ASSERT_FUNC_PARAM(IS_DAC_ALL_INSTANCE(DACx));

    //TODO
}
#endif /* HAL_DAC_MODULE_ENABLED */

#if defined(HAL_CMP_MODULE_ENABLED) && (HAL_CMP_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the CMP IO
  * @param  CMPx Pointer to the base address of the CMP peripheral.
  * @retval None
  */
void HAL_CMP_IoInit(CMP_TypeDef *CMPx)
{
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    HAL_GPIO_InitTypeDef CMP_GPIO_Init;
    CMP_TypeDef *p_instance = CMPx;

    memset((void *)&CMP_GPIO_Init, 0x00, sizeof(CMP_GPIO_Init));

    //CMP GPIO Common Config
    CMP_GPIO_Init.Mode = HAL_GPIO_OUTPUT_PUSHPULL;
    CMP_GPIO_Init.Pull = HAL_GPIO_PULL_NO;
    CMP_GPIO_Init.Speed = HAL_GPIO_SPEED_FREQ_LOW;

    //Test Pin to Generate test wave
    CMP_GPIO_Init.Pin = HAL_GPIO_PIN_15;
    CMP_GPIO_Init.Alternate = HAL_GPIO_AF_1;
    HAL_GPIO_Init(GPIOB, &CMP_GPIO_Init);

    if (p_instance == CMP1) {
        //CMP1 Pinmux Config: PA7->CMP1_INP0
        CMP_GPIO_Init.Pin = HAL_GPIO_PIN_7;
        CMP_GPIO_Init.Alternate = HAL_GPIO_AF_15;
        HAL_GPIO_Init(GPIOA, &CMP_GPIO_Init);
    }
}

/**
  * @brief  DeInitializes the CMP IO
  * @param  CMPx Pointer to the base address of the CMP peripheral.
  * @retval None
  */
void HAL_CMP_IoDeInit(CMP_TypeDef *CMPx)
{
    ASSERT_FUNC_PARAM(IS_CMP_ALL_INSTANCE(CMPx));

    CMP_TypeDef *p_instance = CMPx;

    //Test Pin DeInit
    HAL_GPIO_DeInit(GPIOB, HAL_GPIO_PIN_15);

    if (p_instance == CMP1) {
        //CMP1 Pinmux DeInit
        HAL_GPIO_DeInit(GPIOA, HAL_GPIO_PIN_7);
    }
}
#endif /* HAL_CMP_MODULE_ENABLED */

#if defined(HAL_QEI_MODULE_ENABLED) && (HAL_QEI_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the QEI IO
  * @param  QEIx Pointer to the base address of the QEI peripheral.
  * @retval None
  */
void HAL_QEI_IoInit(QEI_TypeDef *QEIx)
{
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    //TODO
}

/**
  * @brief  DeInitializes the QEI IO
  * @param  QEIx Pointer to the base address of the QEI peripheral.
  * @retval None
  */
void HAL_QEI_IoDeInit(QEI_TypeDef *QEIx)
{
    ASSERT_FUNC_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    //TODO
}
#endif /* HAL_QEI_MODULE_ENABLED */

#if defined(HAL_I2C_MODULE_ENABLED) && (HAL_I2C_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the I2C IO
  * @param  I2Cx Pointer to the base address of the I2C peripheral.
  * @retval None
  */
void HAL_I2C_IoInit(I2C_TypeDef *I2Cx)
{
    ASSERT_FUNC_PARAM(IS_I2C_ALL_INSTANCE(I2Cx));

    //TODO
}

/**
  * @brief  DeInitializes the I2C IO
  * @param  I2Cx Pointer to the base address of the I2C peripheral.
  * @retval None
  */
void HAL_I2C_IoDeInit(I2C_TypeDef *I2Cx)
{
    ASSERT_FUNC_PARAM(IS_I2C_ALL_INSTANCE(I2Cx));

    //TODO
}
#endif /* HAL_I2C_MODULE_ENABLED */

#if defined(HAL_SPI_MODULE_ENABLED) && (HAL_SPI_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the SPI IO
  * @param  SPIx Pointer to the base address of the SPI peripheral.
  * @retval None
  */
void HAL_SPI_IoInit(SPI_TypeDef *SPIx)
{
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    //TODO
}

/**
  * @brief  DeInitializes the SPI IO
  * @param  SPIx Pointer to the base address of the SPI peripheral.
  * @retval None
  */
void HAL_SPI_IoDeInit(SPI_TypeDef *SPIx)
{
    ASSERT_FUNC_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    //TODO
}
#endif /* HAL_SPI_MODULE_ENABLED */

#if defined(HAL_UART_MODULE_ENABLED) && (HAL_UART_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the UART IO
  * @param  UARTx Pointer to the base address of the UART peripheral.
  * @retval None
  */
void HAL_UART_IoInit(UART_TypeDef *UARTx)
{
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    //TODO
}

/**
  * @brief  DeInitializes the UART IO
  * @param  UARTx Pointer to the base address of the UART peripheral.
  * @retval None
  */
void HAL_UART_IoDeInit(UART_TypeDef *UARTx)
{
    ASSERT_FUNC_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    //TODO
}
#endif /* HAL_UART_MODULE_ENABLED */

#if defined(HAL_PDM_MODULE_ENABLED) && (HAL_PDM_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the PDM IO
  * @param  PDMx Pointer to the base address of the PDM peripheral.
  * @retval None
  */
void HAL_PDM_IoInit(PDM_TypeDef *PDMx)
{
    ASSERT_FUNC_PARAM(IS_PDM_ALL_INSTANCE(PDMx));

    //TODO
}

/**
  * @brief  DeInitializes the PDM IO
  * @param  PDMx Pointer to the base address of the PDM peripheral.
  * @retval None
  */
void HAL_PDM_IoDeInit(PDM_TypeDef *PDMx)
{
    ASSERT_FUNC_PARAM(IS_PDM_ALL_INSTANCE(PDMx));

    //TODO
}
#endif /* HAL_PDM_MODULE_ENABLED */

#if defined(HAL_ADTMR_MODULE_ENABLED) && (HAL_ADTMR_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the ADTMR IO
  * @param  ADTMRx Pointer to the base address of the ADTMR peripheral.
  * @retval None
  */
void HAL_ADTMR_IoInit(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    //TODO
}

/**
  * @brief  DeInitializes the ADTMR IO
  * @param  ADTMRx Pointer to the base address of the ADTMR peripheral.
  * @retval None
  */
void HAL_ADTMR_IoDeInit(ADTMR_TypeDef *ADTMRx)
{
    ASSERT_FUNC_PARAM(IS_ADTMR_ALL_INSTANCE(ADTMRx));

    //TODO
}
#endif /* HAL_ADTMR_MODULE_ENABLED */

#if defined(HAL_GPTMRX_MODULE_ENABLED) && (HAL_GPTMRX_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the GPTMRX IO
  * @param  GPTMRx Pointer to the base address of the GPTMRX peripheral.
  * @retval None
  */
void HAL_GPTMRX_IoInit(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    //TODO
}

/**
  * @brief  DeInitializes the GPTMRX IO
  * @param  GPTMRx Pointer to the base address of the GPTMRX peripheral.
  * @retval None
  */
void HAL_GPTMRX_IoDeInit(GPTMRx_TypeDef *GPTMRx)
{
    ASSERT_FUNC_PARAM(IS_GPTMRX_ALL_INSTANCE(GPTMRx));

    //TODO
}
#endif /* HAL_GPTMRX_MODULE_ENABLED */

#if defined(HAL_GPTMRY_MODULE_ENABLED) && (HAL_GPTMRY_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the GPTMRY IO
  * @param  GPTMRy Pointer to the base address of the GPTMRY peripheral.
  * @retval None
  */
void HAL_GPTMRY_IoInit(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    //TODO
}

/**
  * @brief  DeInitializes the GPTMRY IO
  * @param  GPTMRy Pointer to the base address of the GPTMRY peripheral.
  * @retval None
  */
void HAL_GPTMRY_IoDeInit(GPTMRy_TypeDef *GPTMRy)
{
    ASSERT_FUNC_PARAM(IS_GPTMRY_ALL_INSTANCE(GPTMRy));

    //TODO
}
#endif /* HAL_GPTMRY_MODULE_ENABLED */

#if defined(HAL_LPTMR_MODULE_ENABLED) && (HAL_LPTMR_MODULE_ENABLED == 1)
/**
  * @brief  DeInitializes the LPTMR IO
  * @param  LPTMRx Pointer to the base address of the LPTMR peripheral.
  * @retval None
  */
void HAL_LPTMR_IoInit(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    //TODO
}

/**
  * @brief  DeInitializes the LPTMR IO
  * @param  LPTMRx Pointer to the base address of the LPTMR peripheral.
  * @retval None
  */
void HAL_LPTMR_IoDeInit(LPTMR_TypeDef *LPTMRx)
{
    ASSERT_FUNC_PARAM(IS_LPTMR_ALL_INSTANCE(LPTMRx));

    //TODO
}
#endif /* HAL_LPTMR_MODULE_ENABLED */


/**
  * @}
  */ /* BOARD_HAL_Private_Functions */


/**
  * @}
  */ /* TAE32G58xx_Template_HAL */

#endif

/**
  * @}
  */ /* TAE32G58xx_Examples */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

