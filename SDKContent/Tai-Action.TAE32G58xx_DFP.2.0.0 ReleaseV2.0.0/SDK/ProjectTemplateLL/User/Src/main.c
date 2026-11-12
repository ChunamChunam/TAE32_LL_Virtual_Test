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

/** @defgroup TAE32G58xx_Template_LL TAE32G58xx LL Template
  * @brief    TAE32G58xx LL Template
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
static void SystemClock_Config(void);
static void PeripheralClock_Config(void);
/**
  * @}
  */ /* MAIN_Private_Functions */

/* Exported Variables --------------------------------------------------------*/

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
    /* System Clock */
    SystemClock_Config();

    /* SysTick */
    LL_Init1msTick(SystemCoreClockGet());

    /* Peripheral Clock */
    PeripheralClock_Config();

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


/**
  * @brief  System Clock: 180MHz
  * @param  None
  * @return None
  */
static void SystemClock_Config(void)
{
    /* System Clock Frequency */
    const uint32_t sysclk_freq = 180000000UL;

    /* Clock Source Frequency  */
    const uint32_t clk_src_freq = 8000000UL;

    /* BAND for PLL 360MHz */
    const uint32_t pll_band = LL_RCU_PLL_BAND_3;  

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

/**
  * @brief  Peripheral Clock Config
  * @param  None
  * @return None
  */
static void PeripheralClock_Config(void)
{
    /* Register Unlock */
    LL_RCU_RegWrite_Unlock(RCU);

    LL_RCU_SetADCClockSource(RCU, LL_RCU_FUNC_CLK_SRC_PLL0);
    LL_RCU_SetADCClockDivider(RCU, LL_RCU_FUNC_CLK_DIV6);

    LL_RCU_SetCANClockSource(RCU, LL_RCU_FUNC_CLK_SRC_PLL0);
    LL_RCU_SetCANClockDivider(RCU, LL_RCU_FUNC_CLK_DIV3);

    /* Register Lock */
    LL_RCU_RegWrite_Lock(RCU);
    
    /* NVIC Interrupt */
    LL_NVIC_SetPriorityGrouping(LL_NVIC_PRIORITYGROUP_4);
}

/**
  * @}
  */ /* MAIN_Private_Functions */

/* Exported Functions --------------------------------------------------------*/
/** @defgroup MAIN_Exported_Functions MAIN Exported Functions
  * @brief    MAIN Exported Functions
  * @{
  */

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
  */ /* MAIN_Exported_Functions */

/**
  * @}
  */ /* TAE32G58xx_Template_LL */

/**
  * @}
  */ /* TAE32G58xx_Examples */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

