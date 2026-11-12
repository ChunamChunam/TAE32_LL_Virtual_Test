/**
  ******************************************************************************
  * @file    main.c
  * @author  Tai-Action SD Team
  * @brief   main source file for UnitTest project
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
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

#define DBG_TAG     "APP"
#define DBG_LVL     DBG_LOG
#include "dbg/tae_dbg.h"


/** @defgroup TAE32G58xx_Examples TAE32G58xx Examples
  * @brief    TAE32G58xx Examples
  * @{
  */

/** @defgroup TAE32G58xx_Template_HAL TAE32G58xx HAL Template
  * @brief    TAE32G58xx HAL Template
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @addtogroup MAIN_Private_Functions MAIN Private Functions
  * @{
  */
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
static void SystemClock_Config(void);
#endif
/**
  * @}
  */

/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/** @defgroup MAIN_Private_Functions MAIN Private Functions
  * @brief    MAIN Private Functions
  * @{
  */

/**
  * @brief  main entry
  * @param  None
  * @return status
  */
int main(void)
{
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
    /* SysTick and NVIC Group */
    HAL_Init();

    /* System Clock */
    SystemClock_Config();
#endif

    /* Debug Print */
    User_Debug_Init(USER_DBG_IFC_UART1);
    LOG_D("App start\r\n");

    /* User Code */
    //...

    /* Safety Loop */
    while (1) {
        __NOP();
    }
}

#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
/**
  * @brief  HAL SYSCLK Config
  * @param  None
  * @return None
  */
static void SystemClock_Config(void)
{
    HAL_StatusTypeDef ret;
    HAL_RCU_SYSCLKUserCfgTypeDef sys_clock;

    sys_clock.SYSCLKSource        = HAL_RCU_SYSCLK_SRC_PLL0DivClk;
    sys_clock.SYSCLKFrequency     = 180000000UL;
    sys_clock.PLL0Source          = HAL_RCU_PLLCLK_SRC_HSE;
    sys_clock.PLL0SourceFrequency = HSE_VALUE;
    sys_clock.APB0CLKDivider      = HAL_RCU_APB0_DIV2;
    sys_clock.APB1CLKDivider      = HAL_RCU_APB1_DIV2;
    sys_clock.AHBCLKDivider       = HAL_RCU_AHB_DIV1;

    ret = HAL_RCU_SYSCLKInit(&sys_clock);
    if (ret != HAL_OK) {
        while (1) {
            __NOP();
        }
    }
}
#endif

#if defined(TAE32_USE_FULL_ASSERT) && defined(TAE32_USE_ASSERT_FUNC_PARAM)
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_func_failed error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_func_failed error line source number
  * @retval None
  */
void assert_func_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    if (file != NULL) {
        LOG_E("[FUNC]Assert failed in %s line %" PRIu32 "", file, line);
    }

    /* Infinite loop */
    while (1) {
        __NOP();
    }
}
#endif

#if defined(TAE32_USE_FULL_ASSERT) && defined(TAE32_USE_ASSERT_FUNC_STATE)
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_state_failed error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_state_failed error line source number
  * @retval None
  */
void assert_state_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    if (file != NULL) {
        LOG_E("[STATE]Assert failed in %s line %" PRIu32 "", file, line);
    }

    /* Infinite loop */
    while (1) {
        __NOP();
    }
}
#endif

/**
  * @}
  */ /* MAIN_Private_Functions */


/**
  * @}
  */ /* TAE32G58xx_Template_HAL */

/**
  * @}
  */ /* TAE32G58xx_Examples */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

