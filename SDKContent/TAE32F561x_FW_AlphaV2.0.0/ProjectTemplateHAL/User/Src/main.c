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


/** @defgroup TAE32F561x_Examples TAE32F561x Examples
  * @brief    TAE32F561x Examples
  * @{
  */

/** @defgroup TAE32F561x_Template_HAL TAE32F561x HAL Template
  * @brief    TAE32F561x HAL Template
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

#if (defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)) && \
    (defined(HAL_RCU_MODULE_ENABLED) && (HAL_RCU_MODULE_ENABLED == 1))
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
    sys_clock.SYSCLKFrequency     = 160000000UL;
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
#else
/**
  * @brief  System Clock: 160MHz
  * @param  None
  * @return None
  */
static void SystemClock_Config(void)
{
    /* System Clock Frequency */
    const uint32_t sysclk_freq = 160000000UL;

    /* Clock Source Frequency  */
    const uint32_t clk_src_freq = 8000000UL;

    /* BAND for PLL 320MHz */
    const uint32_t pll_band = LL_RCU_PLL_BAND_1;  

    uint16_t pll_int = 0, pll_frac = 0;
    double pll_coef;
    uint32_t cr_store = 0;

    /* Store DEMCR */
    cr_store = CoreDebug->DEMCR;

    /* Enable DWT */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;	

    /* UNLOCK */
    LL_RCU_RegWrite_Unlock(RCU);

    pll_coef = (double)sysclk_freq / (double)clk_src_freq;
    pll_int = pll_coef;
    pll_frac = (pll_coef - pll_int) * 65536;        
  
    /* PLL Disable */
    LL_RCU_PLL0_Disable(RCU);

    if (LL_RCU_GetSysClockSource(RCU) == LL_RCU_SYSCLK_SRC_PLL0DivClk) {
        /* HSI Enable */
        LL_RCU_HSI_Enable(RCU);

        /* Select HSI Clock Source */
        LL_RCU_SetSysClockSource(RCU, LL_RCU_SYSCLK_SRC_RC8M);        
    }

    /* PLL Reference */
    LL_RCU_HSE_Enable(RCU);
    LL_RCU_PLL0_SetRefClock(RCU, LL_RCU_PLLCLK_SRC_HSE);
    LL_RCU_PLL0_PreDivider_1(RCU);

    /* PLL0 Reference Type */
    if (clk_src_freq > 12000000UL) {
        LL_RCU_PLL0_Set12MHigh(RCU);
    } else {
        LL_RCU_PLL0_Set12MLow(RCU);
    }

    /* Different PLL frequencies may correspond to different BANK values. */
    LL_RCU_PLL0_SetBand(RCU, pll_band);        

    /* PLL Multiplication Factor */
    LL_RCU_PLL0_SetDividerInteger(RCU, pll_int);
    LL_RCU_PLL0_SetDividerFraction(RCU, pll_frac);

    /* PLL Enable */
    LL_RCU_PLL0_Enable(RCU);

    /* Wait for PLL Lock*/
    DWT->CYCCNT = (uint32_t)0U;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    while (DWT->CYCCNT < (uint32_t)(((float)LL_SYSCTRL_HSI_GetValue() / 1000000) * 1500))
        ;
    while (!LL_RCU_PLL0_IsReady(RCU))
        ;

    /* Select System Clock Source */
    LL_RCU_SetSysClockSource(RCU, LL_RCU_SYSCLK_SRC_PLL0DivClk);

    /* Clock Prescale  */
    LL_RCU_SetAPB0Prescaler(RCU, LL_RCU_APB0_DIV2);
    LL_RCU_SetAPB1Prescaler(RCU, LL_RCU_APB1_DIV2);
    LL_RCU_SetAHBPrescaler(RCU, LL_RCU_AHB_DIV1);

    /* LOCK */
    LL_RCU_RegWrite_Lock(RCU);

    /* Update SystemCoreClock */
    SystemCoreClockUpdate(sysclk_freq);

    /* Disable DWT */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;

    /* Restore DEMCR */
    CoreDebug->DEMCR = cr_store;
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
  */ /* TAE32F561x_Template_HAL */

/**
  * @}
  */ /* TAE32F561x_Examples */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

