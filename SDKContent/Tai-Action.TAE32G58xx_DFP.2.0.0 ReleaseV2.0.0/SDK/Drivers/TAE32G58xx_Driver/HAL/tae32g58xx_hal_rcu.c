/**
******************************************************************************
* @file    tae32g58xx_hal_rcu.c
* @author  Tai-Action Team
* @brief   RCU HAL module driver.
*          This file provides firmware functions to manage the following
*          functionalities of the Reset and Clock Control (RCU) peripheral:
*           + Initialization and de-initialization functions
*           + Peripheral Control functions
*
    @verbatim
    ==============================================================================
                      ##### RCU specific features #####
    ==============================================================================
    [..]
        After reset the device is running from High Speed Internal oscillator
        with Flash 0 wait state. All peripherals are off except internal
        SRAM, Flash and JTAG.

        (+) There is no prescaler on High speed (AHBs) and Low speed (APBs) buses:
            all peripherals mapped on these buses are running at HSI speed.
        (+) The clock for all peripherals is switched off, except the SRAM and FLASH.
        (+) All GPIOs are in analog mode, except the JTAG pins which
            are assigned to be used for debug purpose.

    [..]
        Once the device started from reset, the user application has to:
        (+) Configure the clock source to be used to drive the System clock
            (if the application needs higher frequency/performance)
        (+) Configure the System clock frequency and Flash settings
        (+) Configure the AHB and APB buses prescalers
        (+) Enable the clock for the peripheral(s) to be used

    @endverbatim
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
#include "tae32g58xx_hal.h"



/** @addtogroup TAE32G58xx_HAL_Driver
 * @{
 */

#if defined(RCU)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_RCU_MODULE_ENABLED) && (HAL_RCU_MODULE_ENABLED == 1)

/** @defgroup RCU_HAL RCU HAL
 * @brief    RCU HAL Module Driver
 * @{
 */

/* Private Type -----------------------------------------------------------*/
/* Private Constants ------------------------------------------------------------*/
/** @defgroup RCU_HAL_Private_Constants RCU HAL Private Constants
 * @{
 */
#define RCU_PLL_TIMEOUT_VALUE               100UL   /* PLL lock timeout in ms (1ms tick) */
#define RCU_CLOCKSWITCH_TIMEOUT_VALUE       500UL   /* Clock switch timeout in ms (1ms tick) */
#define RCU_PLL0CALI_ADC_TIMEOUT_VALUE      2UL     /* PLL0 calibration ADC ready/conv timeout in ms (1ms tick) */

/* Oscillator startup/stop timeouts. They live here (not in the configuration
   header) on purpose: the driver, not the application, is responsible for the
   reliability of its own startup checks, and these values are part of the
   driver's behaviour. */
#define RCU_HSE_TIMEOUT_VALUE 100UL         /* HSE ready/stop timeout in ms (1ms tick) */
#define RCU_HSI_TIMEOUT_VALUE 2UL           /* HSI ready/stop timeout in ms (1ms tick) */
#define RCU_LSI_TIMEOUT_VALUE 2UL           /* LSI ready/stop timeout in ms (1ms tick) */
#define RCU_LSE_TIMEOUT_VALUE 5000UL        /* LSE ready/stop timeout in ms (1ms tick) */

/**
 * @brief  Pre-computed DWT cycle counts for calibration delays.
 */
#define RCU_PLL0CALI_DELAY_1P2MS_CYCLES     ((HAL_SYSCTRL_HSI_GetValue()) / 1000000UL * 1200UL)
#define RCU_PLL0CALI_DELAY_1P5MS_CYCLES     ((HAL_SYSCTRL_HSI_GetValue()) / 1000000UL * 1500UL)

/* PLL0 calibration and ADC0 configuration constants */
#define RCU_PLL0_CALI_ADC_CFGR0             (0x00808321UL)      /*!< ADC CFGR0: calibration mode config   */
#define RCU_PLL0_CALI_ADC_CFGR1             (0x0000002BUL)      /*!< ADC CFGR1: calibration mode config   */
#define RCU_PLL0_CALI_ADC_SIGSEL_CLR        (0x00000000UL)      /*!< ADC SIGSEL: no signal selection      */
#define RCU_PLL0_CALI_ADC_SMPR2             (0x00000020UL)      /*!< ADC SMPR2: sampling time config      */
#define RCU_PLL0_CALI_ADC_SQR0              (0x00000011UL)      /*!< ADC SQR0: sequence config (ch17)     */
#define RCU_PLL0_CALI_ADC_DISR_CH17         (0x00020000UL)      /*!< ADC DISR: channel 17 trigger         */

/**
 * @brief  Default System Clock (PLL VCO / 2 = 360MHz / 2)
 */
#define RCU_SYS_CLK_DEFAULT     (180000000UL)

/**
 * @brief  Maximum System Clock (PLL VCO / 2 = 400MHz / 2)
 */
#define RCU_SYS_CLK_MAX         (200000000UL)
/**
 * @}
 */ /* RCU_HAL_Private_Constants */

/* Private Macros -------------------------------------------------------------*/

#define RCU_GET_INSTANCE                            (RCU)
#define RCU_GET_PLL0CAIL_ADC_INSTANCE               (ADC0)

#define IS_RCU_RESETSOURCE_FLAG(SRC)    (((SRC) != 0UL) && (((SRC) & (~HAL_RCU_RESETSOURCE_FLAG_ALL)) == 0UL))
#define IS_RCU_RESETSOURCE_EN(SRC)      (((SRC) != 0UL) && (((SRC) & (~HAL_RCU_RESETSOURCE_EN_ALL)) == 0UL))

#define IS_RCU_SYSCLK_FREQ(FREQ)        (((FREQ) >= HAL_RCU_SYSCLK_FREQ_MIN) && ((FREQ) <= HAL_RCU_SYSCLK_FREQ_MAX))

#define IS_RCU_OSCILLATORTYPE(TYPE)     (((TYPE) <= 0xfUL) && ((TYPE) != 0U))

#define IS_RCU_CLOCKTYPE(TYPE)          (((TYPE) & HAL_RCU_CLOCKTYPE_SYSCLK) != 0U)

#define IS_RCU_HSE_STATE(STATE)         (((STATE) == HAL_RCU_HSE_OFF) || \
                                         ((STATE) == HAL_RCU_HSE_ON))

#define IS_RCU_HSI_STATE(STATE)         (((STATE) == HAL_RCU_HSI_OFF) || \
                                         ((STATE) == HAL_RCU_HSI_ON))

#define IS_RCU_PLL_STATE(STATE)         (((STATE) == HAL_RCU_PLL_NONE) || \
                                         ((STATE) == HAL_RCU_PLL_OFF)  || \
                                         ((STATE) == HAL_RCU_PLL_ON))

#define IS_RCU_PLLCLK_SRC(SRC)          (((SRC) == HAL_RCU_PLLCLK_SRC_HSE)  || \
                                         ((SRC) == HAL_RCU_PLLCLK_SRC_HSI)  || \
                                         ((SRC) == HAL_RCU_PLLCLK_SRC_CLOSE))

#define IS_RCU_SYSCLK_SRC(SRC)          (((SRC) == HAL_RCU_SYSCLK_SRC_RC8M)           || \
                                         ((SRC) == HAL_RCU_SYSCLK_SRC_RC32K)          || \
                                         ((SRC) == HAL_RCU_SYSCLK_SRC_PLL0DivClk)     || \
                                         ((SRC) == HAL_RCU_SYSCLK_SRC_XOSC))

#define IS_RCU_HCLK_DIV(DIV)            (((DIV) >= HAL_RCU_AHB_DIV1) && \
                                         ((DIV) <= HAL_RCU_AHB_DIV64))

#define IS_RCU_APB0_DIV(DIV)            (((DIV) >= HAL_RCU_APB0_DIV1) && \
                                         ((DIV) <= HAL_RCU_APB0_DIV16))

#define IS_RCU_APB1_DIV(DIV)            (((DIV) >= HAL_RCU_APB1_DIV1) && \
                                         ((DIV) <= HAL_RCU_APB1_DIV16))

#define IS_RCU_ADCCLK_SRC(SRC)          (((SRC) == HAL_RCU_ADCCLK_SRC_SYSCLK) || \
                                         ((SRC) == HAL_RCU_ADCCLK_SRC_PLLCLK))

#define IS_RCU_CANCLK_SRC(SRC)          (((SRC) == HAL_RCU_CANCLK_SRC_SYSCLK) || \
                                         ((SRC) == HAL_RCU_CANCLK_SRC_PLLCLK))

#define IS_RCU_USBCLK_SRC(SRC)          (((SRC) == HAL_RCU_USBCLK_SRC_SYSCLK) || \
                                         ((SRC) == HAL_RCU_USBCLK_SRC_PLLCLK))

#define IS_RCU_LPTMRCLK_SRC(SRC)        (((SRC) == HAL_RCU_LPTMRCLK_SRC_HSI)     || \
                                         ((SRC) == HAL_RCU_LPTMRCLK_SRC_APB0CLK) || \
                                         ((SRC) == HAL_RCU_LPTMRCLK_SRC_HSE)     || \
                                         ((SRC) == HAL_RCU_LPTMRCLK_SRC_LSI))

#define IS_RCU_FUNC_CLK_DIV(DIV)        (((DIV) >= HAL_RCU_FUNC_CLK_DIV1) && \
                                         ((DIV) <= HAL_RCU_FUNC_CLK_DIV16))

#define IS_RCU_PERIPHCLK_CLK(CLK)       (((CLK) == HAL_RCU_PERIPHCLK_ADC) || \
                                         ((CLK) == HAL_RCU_PERIPHCLK_CAN) || \
                                         ((CLK) == HAL_RCU_PERIPHCLK_USB) || \
                                         ((CLK) == HAL_RCU_PERIPHCLK_LPTMR))

#define IS_RCU_CSS_LIMIT_WINDOW(WIN)    (((WIN) == HAL_RCU_CSS_LIMIT_WINDOW_2CYCLE) || \
                                         ((WIN) == HAL_RCU_CSS_LIMIT_WINDOW_4CYCLE) || \
                                         ((WIN) == HAL_RCU_CSS_LIMIT_WINDOW_6CYCLE) || \
                                         ((WIN) == HAL_RCU_CSS_LIMIT_WINDOW_8CYCLE) )

#define IS_RCU_CSS_SWITCH_WINDOW(WIN)   (((WIN) == HAL_RCU_CSS_SWITCH_WINDOW_3US) || \
                                         ((WIN) == HAL_RCU_CSS_SWITCH_WINDOW_6US) || \
                                         ((WIN) == HAL_RCU_CSS_SWITCH_WINDOW_9US) || \
                                         ((WIN) == HAL_RCU_CSS_SWITCH_WINDOW_12US))

#define IS_HAL_RCU_MCO_SOURCE(SRC)      (((SRC) == HAL_RCU_MCO_SRC_LSI)     || \
                                         ((SRC) == HAL_RCU_MCO_SRC_HSI)     || \
                                         ((SRC) == HAL_RCU_MCO_SRC_HSE)     || \
                                         ((SRC) == HAL_RCU_MCO_SRC_FCLK)    || \
                                         ((SRC) == HAL_RCU_MCO_SRC_PLL_DIV32))   


#define IS_HAL_RCU_DBC_CFG_IDX(IDX)     (((IDX) == HAL_RCU_DBC_CFG_GPIOA) || \
                                         ((IDX) == HAL_RCU_DBC_CFG_GPIOB) || \
                                         ((IDX) == HAL_RCU_DBC_CFG_GPIOC) || \
                                         ((IDX) == HAL_RCU_DBC_CFG_GPIOD) || \
                                         ((IDX) == HAL_RCU_DBC_CFG_GPIOE) || \
                                         ((IDX) == HAL_RCU_DBC_CFG_GPIOF))


#define IS_HAL_RCU_GPIO_DBC_CLK_DIV(DIV)    (((DIV) >= HAL_RCU_GPIO_DBC_CLK_DIV1) && \
                                             ((DIV) <= HAL_RCU_GPIO_DBC_CLK_DIV256))

/* Private Variables ---------------------------------------------------------*/
/* SystemCoreClock is defined in system_tae32g58xx.c from original SDK */
extern uint32_t SystemCoreClock;
extern uint32_t uwTickPrio;

/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup RCU_HAL_Private_Functions RCU HAL Private Functions
 * @{
 */

static uint32_t RCU_GetSysClockFreqFromPLLSource(void);
static uint32_t RCU_GetSysClockFreq(void);
static uint32_t RCU_GetHCLKFreq(void);
static uint32_t RCU_GetPCLK0Freq(void);
static uint32_t RCU_GetPCLK1Freq(void);
__STATIC_FORCEINLINE uint32_t RCU_GetHighSpdExtFreq(void);
static uint32_t RCU_GetPeriphSrcFreq(uint32_t Src);

static void RCU_PLL0Cali_ADC0ClkCfgRst(RCU_TypeDef *RCUx);
static void RCU_PLL0Cali_ADC0ClkRstDis(RCU_TypeDef *RCUx);
static uint32_t RCU_PLL0Cali(RCU_TypeDef *RCUx);
/**
 * @}
 */ /* RCU_HAL_Private_Functions */

/* Exported Functions --------------------------------------------------------*/

/** @defgroup RCU_HAL_Exported_Functions RCU HAL Exported Functions
 * @{
 */

/** @defgroup RCU_HAL_EF_Init Initialization and Configuration Functions
*  @brief    Initialization and Configuration functions
*
    @verbatim
    ===============================================================================
           ##### Initialization and Configuration functions #####
    ===============================================================================
    [..]
        This section provides functions allowing to configure the internal and external oscillators
        (HSE, HSI, LSE, LSI, PLL) and the System buses clocks (SYSCLK, AHB, APB0
        and APB1).

    [..] Internal/external clock and PLL configuration
        (+) HSI (high-speed internal): 48 MHz factory-trimmed RC used directly or through
            the PLL as System clock source.

        (+) LSI (low-speed internal): 32 KHz low consumption RC.

        (+) HSE (high-speed external): 4 to 48 MHz crystal oscillator used directly or
            through the PLL as System clock source.

        (+) LSE (low-speed external): 32.768 KHz oscillator.

        (+) PLL (clocked by HSI, HSE) providing output clock:
            (++) The output is used to generate the high speed system clock.

    [..] System, AHB and APB buses clocks configuration
        (+) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
            HSE and main PLL.
            The AHB clock (HCLK) is derived from System clock through configurable
            prescaler and used to clock the CPU, memory and peripherals mapped
            on AHB bus. APB0 (PCLK0) and APB1 (PCLK1) clocks are derived
            from AHB clock through configurable prescalers and used to clock
            the peripherals mapped on these buses. You can use
            "HAL_RCU_GetSysClockFreq()" function to retrieve the frequencies of these clocks.

    @endverbatim
* @{
*/

/**
 * @brief  RCU HAL SYSCLK Init - single-call clock tree setup.
 * @note   Handles oscillator enable, PLL config (via lookup table), clock source
 *         switching, and bus divider setup in one call.
 * @param  pSYSCLKCfg SYSCLK Config Pointer
 * @retval HAL_OK      SYSCLK initialized successfully
 * @retval HAL_INVALID   Invalid parameter or configuration error
 * @retval HAL_TIMEOUT HSI not ready when switching from PLL0
 */
HAL_StatusTypeDef HAL_RCU_SYSCLKInit(HAL_RCU_SYSCLKUserCfgTypeDef *pSYSCLKCfg)
{
    RCU_TypeDef *p_instance = RCU_GET_INSTANCE;

    HAL_RCU_PLLUserCfgTypeDef pll0_cfg;
    HAL_StatusTypeDef ret = HAL_ERROR;
    uint32_t tickstart;

    /* Check RCU instance */
    ASSERT_FUNC_PARAM(IS_RCU_ALL_INSTANCE(p_instance));

    /* Check null pointer */
    if (pSYSCLKCfg == NULL) {
        return HAL_INVALID;
    }

    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_RCU_SYSCLK_FREQ(pSYSCLKCfg->SYSCLKFrequency));
    ASSERT_FUNC_PARAM(IS_RCU_SYSCLK_SRC(pSYSCLKCfg->SYSCLKSource));
    ASSERT_FUNC_PARAM(IS_RCU_PLLCLK_SRC(pSYSCLKCfg->PLL0Source));
    ASSERT_FUNC_PARAM(IS_RCU_APB0_DIV(pSYSCLKCfg->APB0CLKDivider));
    ASSERT_FUNC_PARAM(IS_RCU_APB1_DIV(pSYSCLKCfg->APB1CLKDivider));
    ASSERT_FUNC_PARAM(IS_RCU_HCLK_DIV(pSYSCLKCfg->AHBCLKDivider));

    HAL_RCU_PARAM_CHECK({
        if (!IS_RCU_SYSCLK_SRC(pSYSCLKCfg->SYSCLKSource) ||
            !IS_RCU_PLLCLK_SRC(pSYSCLKCfg->PLL0Source) ||
            !IS_RCU_APB0_DIV(pSYSCLKCfg->APB0CLKDivider) ||
            !IS_RCU_APB1_DIV(pSYSCLKCfg->APB1CLKDivider) ||
            !IS_RCU_HCLK_DIV(pSYSCLKCfg->AHBCLKDivider)) {
            return HAL_INVALID;
        }
    });

    /* Auto Freq Config */
    if (pSYSCLKCfg->SYSCLKSource == HAL_RCU_SYSCLK_SRC_PLL0DivClk) {
        if (pSYSCLKCfg->PLL0Source == HAL_RCU_PLLCLK_SRC_HSE) {
            /* PLL0 CLK Source HSE */
            pSYSCLKCfg->PLL0SourceFrequency = RCU_GetHighSpdExtFreq();
        } else if (pSYSCLKCfg->PLL0Source == HAL_RCU_PLLCLK_SRC_HSI) {
            /* PLL0 CLK Source HSI */
            pSYSCLKCfg->PLL0SourceFrequency = HAL_SYSCTRL_HSI_GetValue();
        } else if (pSYSCLKCfg->PLL0Source == HAL_RCU_PLLCLK_SRC_CLOSE) {
            return HAL_ERROR;
        }
    }
    else if (pSYSCLKCfg->SYSCLKSource == HAL_RCU_SYSCLK_SRC_RC32K) {
        pSYSCLKCfg->SYSCLKFrequency = HAL_SYSCTRL_LSI_GetValue();
    }
    else if (pSYSCLKCfg->SYSCLKSource == HAL_RCU_SYSCLK_SRC_RC8M) {
        pSYSCLKCfg->SYSCLKFrequency = HAL_SYSCTRL_HSI_GetValue();
    }
    else if (pSYSCLKCfg->SYSCLKSource == HAL_RCU_SYSCLK_SRC_XOSC) {
        pSYSCLKCfg->SYSCLKFrequency = RCU_GetHighSpdExtFreq();
    }

    /* RCU Register Write Unlock */
    LL_RCU_RegWrite_Unlock(p_instance);

    /* Config SYSCLK */
    switch (pSYSCLKCfg->SYSCLKSource) {
        case HAL_RCU_SYSCLK_SRC_RC32K:
            /* SYSCLK source select RC32K */
            LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_RC32K);
            ret = HAL_OK;
            break;

        case HAL_RCU_SYSCLK_SRC_RC8M:
            /* SYSCLK source select RC8M */
            LL_RCU_HSI_Enable(p_instance);
            LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_RC8M);
            ret = HAL_OK;
            break;

        case HAL_RCU_SYSCLK_SRC_PLL0DivClk: {
            /* SYSCLK must leave PLL0 before the PLL0 clock source is reconfigured */
            if (LL_RCU_GetSysClockSource(p_instance) == LL_RCU_SYSCLK_SRC_PLL0DivClk) {
                LL_RCU_HSI_Enable(p_instance);

                /* Wait for HSI to be ready before switching to it */
                tickstart = HAL_GetTick();
                while (LL_RCU_HSI_IsEnabled(p_instance) == 0UL) {
                    if ((HAL_GetTick() - tickstart) > RCU_HSI_TIMEOUT_VALUE) {
                        /* ERROR: HSI not ready when switching from PLL0 */
                        LL_RCU_RegWrite_Lock(p_instance);
                        return HAL_TIMEOUT;
                    }
                }

                LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_RC8M);
            }

            /* RCU Register will be unlocked and locked in HAL_RCU_PLL0Config */
            LL_RCU_RegWrite_Lock(p_instance);

            /* SYSCLK PLL0 Config */
            pll0_cfg.PLLSource = pSYSCLKCfg->PLL0Source;
            pll0_cfg.PLLInFrequency = pSYSCLKCfg->PLL0SourceFrequency;
            pll0_cfg.PLLUserFrequency = pSYSCLKCfg->SYSCLKFrequency;
            ret = HAL_RCU_PLL0Config(&pll0_cfg);

            /* Keeping in unlock, RCU Register has been locked after HAL_RCU_PLL0Config */
            LL_RCU_RegWrite_Unlock(p_instance);

            /* SYSCLK Source Select PLL0DivClk */
            if (ret == HAL_OK) {
                /* SYSCLK source select PLL0DivClk */
                LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_PLL0DivClk);
            }

            break;
        }

        case HAL_RCU_SYSCLK_SRC_XOSC:
            /* SYSCLK source select XOSC */
            LL_RCU_HSE_Enable(p_instance);
            LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_XOSC);
            ret = HAL_OK;
            break;

        default:
            /* ERROR: SYSCLK Source Select Error */
            ret = HAL_ERROR;
            break;
    }

    if (ret == HAL_OK) {
        /* APB0/APB1/AHB Clock Div Config */
        LL_RCU_SetAPB0Prescaler(p_instance, pSYSCLKCfg->APB0CLKDivider);
        LL_RCU_SetAPB1Prescaler(p_instance, pSYSCLKCfg->APB1CLKDivider);
        LL_RCU_SetAHBPrescaler(p_instance, pSYSCLKCfg->AHBCLKDivider);
    }

    /* RCU Register Lock */
    LL_RCU_RegWrite_Lock(p_instance);

    if (ret == HAL_OK) {
        HAL_RCU_UpdateSystemCoreClock();
        if (HAL_InitTick(uwTickPrio) != HAL_OK) {
            ret = HAL_ERROR;
        }
    }

    return ret;
}

/**
 * @brief  Configure the PLL0 with pre-calibrated lookup table.
 * @note   Uses the pre-calibrated PLL lookup table.
 *         Falls back to auto-calculation if the frequency is not in the table.
 * @param  pPLL0Config PLL0 Config Pointer
 * @retval HAL_OK      PLL0 configured and locked
 * @retval HAL_INVALID   Invalid parameter or unsupported frequency
 * @retval HAL_TIMEOUT PLL0 lock timeout
 */
HAL_StatusTypeDef HAL_RCU_PLL0Config(HAL_RCU_PLLUserCfgTypeDef *pPLL0Config)
{
    RCU_TypeDef *p_instance = RCU_GET_INSTANCE;

    uint8_t pll0_adc0_set = 0;
    uint16_t pll_integer = 0, pll_fraction = 0;
    uint32_t pll_vco_band;
    uint32_t tickstart;
    LL_RCU_PllPreDivTypeDef pre_div = LL_RCU_PLL_PRE_DIV_IVD;
    

    /* Check Null pointer */
    ASSERT_FUNC_PARAM(pPLL0Config != NULL);

    if (pPLL0Config == NULL) {
        return HAL_INVALID;
    }

    /* Check SYSCLK frequency upper limit */
    if (pPLL0Config->PLLUserFrequency > RCU_SYS_CLK_MAX) {
        return HAL_INVALID;
    }

    if (pPLL0Config->PLLSource == HAL_RCU_PLLCLK_SRC_HSI) {
        pPLL0Config->PLLInFrequency = HAL_SYSCTRL_HSI_GetValue();
    }

    if (pPLL0Config->PLLInFrequency) {
        double pll_coef = (double)pPLL0Config->PLLUserFrequency / pPLL0Config->PLLInFrequency;
        pll_integer = pll_coef;
        pll_fraction = (pll_coef - pll_integer) * 65536;

        pre_div = LL_RCU_PLL_PRE_DIV_1;
        pll_vco_band = LL_RCU_PLL_BAND_1;
    }
    else {
        /* PLL configuration not found in the lookup table */
        return HAL_INVALID;
    }


    /* RCU CTRL Register Unlock */
    LL_RCU_RegWrite_Unlock(p_instance);

    /* ADC0 for PLL0 Band value calibration. 
       It is only needed when the band has to be calibrated on the fly */
    if ((pPLL0Config->PLLUserFrequency == RCU_SYS_CLK_MAX) &&
        (pPLL0Config->PLLSource == HAL_RCU_PLLCLK_SRC_HSI)) {
        pll0_adc0_set = 0;
    }
    else {
        /* Reset ADC0 for PLL0 Band value calibration */
        RCU_PLL0Cali_ADC0ClkCfgRst(p_instance);
        pll0_adc0_set = 1;
    }

    /* PLL0 Disable before config */
    LL_RCU_PLL0_Disable(p_instance);

    switch (pPLL0Config->PLLSource) {
        case HAL_RCU_PLLCLK_SRC_HSE:
            LL_RCU_HSE_Enable(p_instance);
            /* PLL0 CLK Source Select HSE */
            LL_RCU_PLL0_SetRefClock(p_instance, LL_RCU_PLLCLK_SRC_HSE);
            break;

        case HAL_RCU_PLLCLK_SRC_HSI:
            LL_RCU_HSI_Enable(p_instance);
            /* PLL0 CLK Source Select HSI */
            LL_RCU_PLL0_SetRefClock(p_instance, LL_RCU_PLLCLK_SRC_HSI);
            break;

        case HAL_RCU_PLLCLK_SRC_CLOSE:
            /* PLL0 CLK Source Select Close */
            LL_RCU_PLL0_SetRefClock(p_instance, LL_RCU_PLLCLK_SRC_CLOSE);
            break;

        default:
            /* PLL0 CLK Source Select Error */
            LL_RCU_RegWrite_Lock(p_instance);
            return HAL_INVALID;
    }

    /* PLL0 Pre-Div Config */
    if (pre_div == LL_RCU_PLL_PRE_DIV_1) {
        LL_RCU_PLL0_PreDivider_1(p_instance);
    } else if (pre_div == LL_RCU_PLL_PRE_DIV_2) {
        LL_RCU_PLL0_PreDivider_2(p_instance);
    } else {
        /* Unknown PLL0 Pre-Div config, set to default 1 division */
        pre_div = LL_RCU_PLL_PRE_DIV_1;
        LL_RCU_PLL0_PreDivider_1(p_instance);
    }

    /* PLL0 LPF Config */
    if (pPLL0Config->PLLInFrequency / pre_div > 12000000UL) {
        LL_RCU_PLL0_Set12MHigh(p_instance);
    }
    else {
        LL_RCU_PLL0_Set12MLow(p_instance);
    }

    /* PLL0 integer/fraction and Gain Config */
    LL_RCU_PLL0_SetDividerInteger(p_instance, pll_integer);
    LL_RCU_PLL0_SetDividerFraction(p_instance, pll_fraction);

    /* RCU Register will be unlocked and locked in RCU_PLL0Cali */
    LL_RCU_RegWrite_Lock(p_instance);

    /* PLL0 Band value calibration. The factory band values live in SYSCTRL and both
       were calibrated with RC8M as the reference clock, so RC8M is the only source 
       that has a factory value to read back; every other source is calibrated on the fly */
    if ((pPLL0Config->PLLUserFrequency == RCU_SYS_CLK_MAX) && 
        (pPLL0Config->PLLSource == HAL_RCU_PLLCLK_SRC_HSI)) {
        /* PLL VCO 400MHz / 2 = 200MHz */
        pll_vco_band = HAL_SYSCTRL_RC8M_GetBandForPLL0CLK200MHz();
    }else if ((pPLL0Config->PLLUserFrequency == RCU_SYS_CLK_DEFAULT) && 
        (pPLL0Config->PLLSource == HAL_RCU_PLLCLK_SRC_HSI)) {
        /* PLL VCO 360MHz / 2 = 180MHz */
        pll_vco_band = HAL_SYSCTRL_RC8M_GetBandForPLL0CLK180MHz();
    } else {
        /* PLL0Cali function has lock before return */
        pll_vco_band = RCU_PLL0Cali(p_instance);
    }

    /* Keeping in unlock, RCU Register has been locked after RCU_PLL0Cali */
    LL_RCU_RegWrite_Unlock(p_instance); 

    /* Restore ADC0 to default state */
    if (pll0_adc0_set) {
        RCU_PLL0Cali_ADC0ClkRstDis(p_instance);
    }

    /* PLL0 VCO Band Config and Enable */
    LL_RCU_PLL0_SetBand(p_instance, pll_vco_band);
    LL_RCU_PLL0_Enable(p_instance);

    /* Wait for PLL0 Lock */
    tickstart = HAL_GetTick();
    while (!LL_RCU_PLL0_IsReady(p_instance)) {
        if ((HAL_GetTick() - tickstart) > RCU_PLL_TIMEOUT_VALUE) {
            /* PLL0 lock timeout */
            LL_RCU_RegWrite_Lock(p_instance);
            return HAL_TIMEOUT;
        }
    }

    /* RCU Register Lock */
    LL_RCU_RegWrite_Lock(p_instance);

    return HAL_OK;
}

/**
 * @brief  Initializes the RCU Oscillators according to the specified parameters in the
 *         HAL_RCU_OscInitTypeDef.
 * @param  pOscInit pointer to an HAL_RCU_OscInitTypeDef structure that
 *         contains the configuration information for the RCU Oscillators.
 * @note   The PLL is not disabled when used as system clock.
 * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
 *         supported by this API. User should request a transition to LSE Off
 *         first and then LSE On or LSE Bypass.
 * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
 *         supported by this API. User should request a transition to HSE Off
 *         first and then HSE On or HSE Bypass.
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_OscConfig(HAL_RCU_OscInitTypeDef *pOscInit)
{
    RCU_TypeDef *p_instance = RCU_GET_INSTANCE;

    uint32_t tickstart;
    uint32_t temp_sysclksrc;
    uint32_t temp_pllckcfg;

    uint32_t current_sysclk_source;
    uint32_t need_switch_back = 0UL;

    /* Check Null pointer */
    if (pOscInit == NULL) {
        return HAL_INVALID;
    }

    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_RCU_OSCILLATORTYPE(pOscInit->OscillatorType));
    ASSERT_FUNC_PARAM(IS_RCU_PLL_STATE(pOscInit->PLLState));

    /*------------------------------ HSE Configuration -------------------------*/
    if (((pOscInit->OscillatorType) & HAL_RCU_OSCILLATORTYPE_HSE) == HAL_RCU_OSCILLATORTYPE_HSE) {
        /* Check the parameters */
        ASSERT_FUNC_PARAM(IS_RCU_HSE_STATE(pOscInit->HSEState));

        temp_sysclksrc = LL_RCU_GetSysClockSource(p_instance);
        temp_pllckcfg = LL_RCU_PLL0_GetRefClockSource(p_instance);

        /* Check if HSE is used as system clock or PLL source - disallow turning it off */
        if (((temp_sysclksrc == LL_RCU_SYSCLK_SRC_PLL0DivClk) && (temp_pllckcfg == LL_RCU_PLLCLK_SRC_HSE)) ||
            (temp_sysclksrc == LL_RCU_SYSCLK_SRC_XOSC)) {
            if ((LL_RCU_HSE_IsEnabled(p_instance) != 0UL) && (pOscInit->HSEState == HAL_RCU_HSE_OFF)) {
                return HAL_ERROR;
            }
        } else {
            if (pOscInit->HSEState == HAL_RCU_HSE_ON) {
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_HSE_Enable(p_instance);
                LL_RCU_RegWrite_Lock(p_instance);

                tickstart = HAL_GetTick();
                while (LL_RCU_HSE_IsEnabled(p_instance) == 0UL) {
                    if ((HAL_GetTick() - tickstart) > RCU_HSE_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
            } else if (pOscInit->HSEState == HAL_RCU_HSE_OFF) {
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_HSE_Disable(p_instance);
                LL_RCU_RegWrite_Lock(p_instance);

                tickstart = HAL_GetTick();
                while (LL_RCU_HSE_IsEnabled(p_instance) != 0UL) {
                    if ((HAL_GetTick() - tickstart) > RCU_HSE_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
            } else {
                return HAL_INVALID;
            }
        }
    }

    /*------------------------------ HSI Configuration -------------------------*/
    if (((pOscInit->OscillatorType) & HAL_RCU_OSCILLATORTYPE_HSI) == HAL_RCU_OSCILLATORTYPE_HSI) {
        /* Check the parameters */
        ASSERT_FUNC_PARAM(IS_RCU_HSI_STATE(pOscInit->HSIState));

        temp_sysclksrc = LL_RCU_GetSysClockSource(p_instance);
        temp_pllckcfg = LL_RCU_PLL0_GetRefClockSource(p_instance);

        /* Check if HSI is used as system clock or PLL source - disallow turning it off */
        if (((temp_sysclksrc == LL_RCU_SYSCLK_SRC_PLL0DivClk) && (temp_pllckcfg == LL_RCU_PLLCLK_SRC_HSI)) ||
            (temp_sysclksrc == LL_RCU_SYSCLK_SRC_RC8M)) {
            if ((LL_RCU_HSI_IsEnabled(p_instance) != 0UL) && (pOscInit->HSIState == HAL_RCU_HSI_OFF)) {
                return HAL_ERROR;
            }
        }
        else {
            /* HSI ON */
            if (pOscInit->HSIState == HAL_RCU_HSI_ON) {
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_HSI_Enable(p_instance);
                LL_RCU_RegWrite_Lock(p_instance);

                tickstart = HAL_GetTick();
                while (LL_RCU_HSI_IsEnabled(p_instance) == 0UL) {
                    if ((HAL_GetTick() - tickstart) > RCU_HSI_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
            }
            /* HSI OFF */
            else if (pOscInit->HSIState == HAL_RCU_HSI_OFF) {
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_HSI_Disable(p_instance);
                LL_RCU_RegWrite_Lock(p_instance);

                tickstart = HAL_GetTick();
                while (LL_RCU_HSI_IsEnabled(p_instance) != 0UL) {
                    if ((HAL_GetTick() - tickstart) > RCU_HSI_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
            }
            else {
                return HAL_INVALID;
            }
        }
    }


    /*-------------------------------- PLL ON ---------------------------------*/
    if (pOscInit->PLLState == HAL_RCU_PLL_ON) {
        /* Check the parameters */
        ASSERT_FUNC_PARAM(IS_RCU_PLLCLK_SRC(pOscInit->PLLSource));

        current_sysclk_source = LL_RCU_GetSysClockSource(p_instance);

        /* If SYSCLK is currently using PLL0DivClk, switch back to HSI first */
        if (current_sysclk_source == LL_RCU_SYSCLK_SRC_PLL0DivClk) {
            tickstart = HAL_GetTick();
            /* Ensure HSI is ready before switching */
            while (LL_RCU_HSI_IsEnabled(p_instance) == 0UL) {
                if ((HAL_GetTick() - tickstart) > RCU_HSI_TIMEOUT_VALUE) {
                    return HAL_TIMEOUT;
                }
            }

            LL_RCU_RegWrite_Unlock(p_instance);
            LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_RC8M);
            LL_RCU_RegWrite_Lock(p_instance);

            tickstart = HAL_GetTick();
            while (LL_RCU_GetSysClockSource(p_instance) != LL_RCU_SYSCLK_SRC_RC8M) {
                if ((HAL_GetTick() - tickstart) > RCU_CLOCKSWITCH_TIMEOUT_VALUE) {
                    return HAL_TIMEOUT;
                }
            }

            need_switch_back = 1UL;
        }

        /* Disable PLL and wait for unlock */
        LL_RCU_RegWrite_Unlock(p_instance);
        LL_RCU_PLL0_Disable(p_instance);
        LL_RCU_RegWrite_Lock(p_instance);

        tickstart = HAL_GetTick();
        while (LL_RCU_PLL0_IsReady(p_instance) != 0UL) {
            if ((HAL_GetTick() - tickstart) > RCU_PLL_TIMEOUT_VALUE) {
                return HAL_TIMEOUT;
            }
        }

        /* RCU Unlock */
        LL_RCU_RegWrite_Unlock(p_instance);

        /* Set PLL reference clock source */
        LL_RCU_PLL0_SetRefClock(p_instance, pOscInit->PLLSource);

        /* Default PLL0 Pre-Divider */
        LL_RCU_PLL0_PreDivider_1(p_instance);

        /* Set PLL integer and fraction dividers */
        LL_RCU_PLL0_SetDividerInteger(p_instance, pOscInit->PLLInteger);
        LL_RCU_PLL0_SetDividerFraction(p_instance, pOscInit->PLLFraction);
        LL_RCU_PLL0_SetBand(p_instance, pOscInit->PLLBand);
        LL_RCU_PLL0_Enable(p_instance);

        /* RCU Lock */
        LL_RCU_RegWrite_Lock(p_instance);

        tickstart = HAL_GetTick();
        while (LL_RCU_PLL0_IsReady(p_instance) == 0UL) {
            if ((HAL_GetTick() - tickstart) > RCU_PLL_TIMEOUT_VALUE) {
                return HAL_TIMEOUT;
            }
        }

        /* Switch SYSCLK back to PLL0DivClk if it was the source before */
        if (need_switch_back != 0UL) {
            tickstart = HAL_GetTick();

            LL_RCU_RegWrite_Unlock(p_instance);
            LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_PLL0DivClk);
            LL_RCU_RegWrite_Lock(p_instance);

            while (LL_RCU_GetSysClockSource(p_instance) != LL_RCU_SYSCLK_SRC_PLL0DivClk) {
                if ((HAL_GetTick() - tickstart) > RCU_CLOCKSWITCH_TIMEOUT_VALUE) {
                    return HAL_TIMEOUT;
                }
            }
        }
    }
    /*------------------------------- PLL OFF --------------------------------*/
    else if (pOscInit->PLLState == HAL_RCU_PLL_OFF) {
        current_sysclk_source = LL_RCU_GetSysClockSource(p_instance);

        /* If SYSCLK is currently using PLL0DivClk, switch back to HSI first */
        if (current_sysclk_source == LL_RCU_SYSCLK_SRC_PLL0DivClk) {
            tickstart = HAL_GetTick();
            /* Ensure HSI is ready before switching */
            while (LL_RCU_HSI_IsEnabled(p_instance) == 0UL) {
                if ((HAL_GetTick() - tickstart) > RCU_HSI_TIMEOUT_VALUE) {
                    return HAL_TIMEOUT;
                }
            }

            LL_RCU_RegWrite_Unlock(p_instance);
            LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_RC8M);
            LL_RCU_RegWrite_Lock(p_instance);

            tickstart = HAL_GetTick();
            while (LL_RCU_GetSysClockSource(p_instance) != LL_RCU_SYSCLK_SRC_RC8M) {
                if ((HAL_GetTick() - tickstart) > RCU_CLOCKSWITCH_TIMEOUT_VALUE) {
                    return HAL_TIMEOUT;
                }
            }
        }

        /* Disable PLL */
        LL_RCU_RegWrite_Unlock(p_instance);
        LL_RCU_PLL0_Disable(p_instance);
        LL_RCU_RegWrite_Lock(p_instance);

        /* Wait for PLL unlock */
        tickstart = HAL_GetTick();
        while (LL_RCU_PLL0_IsReady(p_instance) != 0UL) {
            if ((HAL_GetTick() - tickstart) > RCU_PLL_TIMEOUT_VALUE) {
                return HAL_TIMEOUT;
            }
        }
    }
    else {
        return HAL_INVALID;
    }

    return HAL_OK;
}

/**
 * @brief  Initializes the CPU, AHB and APB buses clocks according to the specified
 *         parameters in the HAL_RCU_ClkInitTypeDef.
 * @note   Each LL_RCU_Set* function internally handles RCU register Unlock/Lock.
 *         Caller does NOT need to Unlock RCU before calling this function.
 * @param  pClkInit pointer to an HAL_RCU_ClkInitTypeDef structure that
 *         contains the configuration information for the RCU peripheral.
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_ClockConfig(HAL_RCU_ClkInitTypeDef *pClkInit)
{
    RCU_TypeDef *p_instance = RCU_GET_INSTANCE;

    uint32_t tickstart;

    /* Check Null pointer */
    if (pClkInit == NULL) {
        return HAL_INVALID;
    }

    /* Check the parameters */
    ASSERT_FUNC_PARAM(IS_RCU_CLOCKTYPE(pClkInit->ClockType));

    /*-------------------------- SYSCLK Configuration --------------------------*/
    if (((pClkInit->ClockType) & HAL_RCU_CLOCKTYPE_SYSCLK) == HAL_RCU_CLOCKTYPE_SYSCLK) {
        ASSERT_FUNC_PARAM(IS_RCU_SYSCLK_SRC(pClkInit->SYSCLKSource));

        tickstart = HAL_GetTick();

        switch (pClkInit->SYSCLKSource) {
            case HAL_RCU_SYSCLK_SRC_RC8M:
                if (LL_RCU_HSI_IsEnabled(p_instance) == 0UL) {
                    return HAL_ERROR;
                }
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_RC8M);
                LL_RCU_RegWrite_Lock(p_instance);
                while (LL_RCU_GetSysClockSource(p_instance) != LL_RCU_SYSCLK_SRC_RC8M) {
                    if ((HAL_GetTick() - tickstart) > RCU_CLOCKSWITCH_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
                break;

            case HAL_RCU_SYSCLK_SRC_RC32K:
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_RC32K);
                LL_RCU_RegWrite_Lock(p_instance);
                while (LL_RCU_GetSysClockSource(p_instance) != LL_RCU_SYSCLK_SRC_RC32K) {
                    if ((HAL_GetTick() - tickstart) > RCU_CLOCKSWITCH_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
                break;

            case HAL_RCU_SYSCLK_SRC_XOSC:
                if (LL_RCU_HSE_IsEnabled(p_instance) == 0UL) {
                    return HAL_ERROR;
                }
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_SetSysClockSource(p_instance, LL_RCU_SYSCLK_SRC_XOSC);
                LL_RCU_RegWrite_Lock(p_instance);
                while (LL_RCU_GetSysClockSource(p_instance) != LL_RCU_SYSCLK_SRC_XOSC) {
                    if ((HAL_GetTick() - tickstart) > RCU_CLOCKSWITCH_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
                break;

            case HAL_RCU_SYSCLK_SRC_PLL0DivClk:
                if (LL_RCU_PLL0_IsReady(p_instance) == 0UL) {
                    return HAL_ERROR;
                }
                LL_RCU_RegWrite_Unlock(p_instance);
                LL_RCU_SetSysClockSource(p_instance, pClkInit->SYSCLKSource);
                LL_RCU_RegWrite_Lock(p_instance);
                while (LL_RCU_GetSysClockSource(p_instance) != pClkInit->SYSCLKSource) {
                    if ((HAL_GetTick() - tickstart) > RCU_CLOCKSWITCH_TIMEOUT_VALUE) {
                        return HAL_TIMEOUT;
                    }
                }
                break;

            default:
                return HAL_INVALID;
        }
    }

    /*--------------------------- HCLK Configuration ---------------------------*/
    if (((pClkInit->ClockType) & HAL_RCU_CLOCKTYPE_HCLK) == HAL_RCU_CLOCKTYPE_HCLK) {
        ASSERT_FUNC_PARAM(IS_RCU_HCLK_DIV(pClkInit->AHBCLKDivider));

        LL_RCU_RegWrite_Unlock(p_instance);
        LL_RCU_SetAHBPrescaler(p_instance, pClkInit->AHBCLKDivider);
        LL_RCU_RegWrite_Lock(p_instance);
    }

    /*-------------------------- PCLK0 Configuration ---------------------------*/
    if (((pClkInit->ClockType) & HAL_RCU_CLOCKTYPE_PCLK0) == HAL_RCU_CLOCKTYPE_PCLK0) {
        ASSERT_FUNC_PARAM(IS_RCU_APB0_DIV(pClkInit->APB0CLKDivider));

        LL_RCU_RegWrite_Unlock(p_instance);
        LL_RCU_SetAPB0Prescaler(p_instance, pClkInit->APB0CLKDivider);
        LL_RCU_RegWrite_Lock(p_instance);
    }

    /*-------------------------- PCLK1 Configuration ---------------------------*/
    if (((pClkInit->ClockType) & HAL_RCU_CLOCKTYPE_PCLK1) == HAL_RCU_CLOCKTYPE_PCLK1) {
        ASSERT_FUNC_PARAM(IS_RCU_APB1_DIV(pClkInit->APB1CLKDivider));

        LL_RCU_RegWrite_Unlock(p_instance);
        LL_RCU_SetAPB1Prescaler(p_instance, pClkInit->APB1CLKDivider);
        LL_RCU_RegWrite_Lock(p_instance);
    }

    /* Update SystemCoreClock */
    SystemCoreClock = RCU_GetSysClockFreq();

    if (HAL_InitTick(uwTickPrio) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the MCO (internal clock fanout) output and enable it.
  * @param  Source MCO output source @ref HAL_RCU_MCOSourceTypeDef
  * @retval HAL_OK      Configuration done and output enabled
  * @retval HAL_INVALID Source is not a valid source
  */
HAL_StatusTypeDef HAL_RCU_MCOConfig(HAL_RCU_MCOSourceTypeDef Source)
{
    ASSERT_FUNC_PARAM(IS_HAL_RCU_MCO_SOURCE(Source));

    HAL_RCU_PARAM_CHECK({
        if (IS_HAL_RCU_MCO_SOURCE(Source) == 0U) {
            return HAL_INVALID;
        }
    });

    RCU_TypeDef *p_instance = RCU_GET_INSTANCE;

    LL_RCU_RegWrite_Unlock(p_instance);
    LL_RCU_SetIntClockFanoutSource(p_instance, (uint32_t)Source);
    LL_RCU_EnableIntClockFanout(p_instance);
    LL_RCU_RegWrite_Lock(p_instance);

    return HAL_OK;
}

/**
  * @brief  Configure the GPIO Debounce Clock Divider.
  * @param  Index GPIO debounce config index 
  * @param  ClockDivider GPIO Debounce Clock Divider
  * @retval HAL_OK      Configuration done
  * @retval HAL_INVALID Parameter is not a valid value
  */
HAL_StatusTypeDef HAL_RCU_GPIODebounceConfig(HAL_RCU_DbcCfgIdxTypeDef Index, 
                                             HAL_RCU_GpioDbcClkDivTypeDef ClockDivider)
{
    ASSERT_FUNC_PARAM(IS_HAL_RCU_DBC_CFG_IDX(Index));
    ASSERT_FUNC_PARAM(IS_HAL_RCU_GPIO_DBC_CLK_DIV(ClockDivider));

    HAL_RCU_PARAM_CHECK({
        if (IS_HAL_RCU_DBC_CFG_IDX(Index) == 0U) {
            return HAL_INVALID;
        }

        if (IS_HAL_RCU_GPIO_DBC_CLK_DIV(ClockDivider) == 0U) {
            return HAL_INVALID;
        }
    });

    HAL_StatusTypeDef ret = HAL_OK;
    RCU_TypeDef *p_instance = RCU_GET_INSTANCE;

    LL_RCU_RegWrite_Unlock(p_instance);

    switch (Index) {
        case HAL_RCU_DBC_CFG_GPIOA:
            LL_RCU_SetGPIOADbcClockDivider(p_instance, (uint32_t)ClockDivider);
            break;

        case HAL_RCU_DBC_CFG_GPIOB:
            LL_RCU_SetGPIOBDbcClockDivider(p_instance, (uint32_t)ClockDivider);
            break;

        case HAL_RCU_DBC_CFG_GPIOC:
            LL_RCU_SetGPIOCDbcClockDivider(p_instance, (uint32_t)ClockDivider);
            break;

        case HAL_RCU_DBC_CFG_GPIOD:
            LL_RCU_SetGPIODDbcClockDivider(p_instance, (uint32_t)ClockDivider);
            break;

        case HAL_RCU_DBC_CFG_GPIOE:
            LL_RCU_SetGPIOEDbcClockDivider(p_instance, (uint32_t)ClockDivider);
            break;

        case HAL_RCU_DBC_CFG_GPIOF:
            LL_RCU_SetGPIOFDbcClockDivider(p_instance, (uint32_t)ClockDivider);
            break;

        default:
            ret = HAL_INVALID;
            break;
    }

    LL_RCU_RegWrite_Lock(p_instance);

    return ret;
}

/**
 * @brief  Return the SYSCLK source and the AHB/APB0/APB1 dividers.
 * @note   Reads RCU_CCR (manual 7.3.2.3).
 * @param  pClkInit pointer to an HAL_RCU_ClkInitTypeDef structure that receives
 *         the current clock configuration.
 * @return None
 */
void HAL_RCU_GetClockConfig(HAL_RCU_ClkInitTypeDef *pClkInit)
{
    RCU_TypeDef *RCUx = RCU_GET_INSTANCE;

    if (pClkInit == NULL) {
        return;
    }

    pClkInit->ClockType         = HAL_RCU_CLOCKTYPE_SYSCLK | HAL_RCU_CLOCKTYPE_HCLK |
                                  HAL_RCU_CLOCKTYPE_PCLK0  | HAL_RCU_CLOCKTYPE_PCLK1;

    pClkInit->SYSCLKSource      = (uint32_t)LL_RCU_GetSysClockSource(RCUx);
    pClkInit->AHBCLKDivider     = (uint32_t)LL_RCU_GetAHBPrescaler(RCUx);
    pClkInit->APB0CLKDivider    = (uint32_t)LL_RCU_GetAPB0Prescaler(RCUx);
    pClkInit->APB1CLKDivider    = (uint32_t)LL_RCU_GetAPB1Prescaler(RCUx);
}

/**
 * @brief  Return the oscillator configuration.
 * @note   This MCU has neither LSE oscillator nor HSI calibration register, so
 *         LSEState is reported as LL_RCU_LSE_OFF and HSICalibrationValue as 0.
 * @param  pOscInit pointer to an HAL_RCU_OscInitTypeDef structure that receives
 *         the current oscillator configuration.
 * @return None
 */
void HAL_RCU_GetOscConfig(HAL_RCU_OscInitTypeDef *pOscInit)
{
    RCU_TypeDef *RCUx = RCU_GET_INSTANCE;

    if (pOscInit == NULL) {
        return;
    }

    const uint32_t pll_ready = LL_RCU_PLL0_IsReady(RCUx);;

    pOscInit->OscillatorType =  HAL_RCU_OSCILLATORTYPE_HSE | 
                                HAL_RCU_OSCILLATORTYPE_HSI |
                                HAL_RCU_OSCILLATORTYPE_LSI;

    pOscInit->HSEState = (LL_RCU_HSE_IsEnabled(RCUx) != 0UL) ? HAL_RCU_HSE_ON : HAL_RCU_HSE_OFF;
    pOscInit->HSIState = (LL_RCU_HSI_IsEnabled(RCUx) != 0UL) ? HAL_RCU_HSI_ON : HAL_RCU_HSI_OFF;

    if (pll_ready == 0UL) {
        pOscInit->PLLState = HAL_RCU_PLL_OFF;
    } else if(pll_ready == 1UL) {
        pOscInit->PLLState = HAL_RCU_PLL_ON;
    }

    pOscInit->PLLSource = (HAL_RCU_PLLSourceTypeDef)LL_RCU_PLL0_GetRefClockSource(RCUx);
    pOscInit->PLLFraction = (uint16_t)LL_RCU_PLL0_GetDividerFraction(RCUx);       
    pOscInit->PLLInteger = (uint16_t)LL_RCU_PLL0_GetDividerInteger(RCUx);    
    pOscInit->PLLBand = (HAL_RCU_PllBandTypeDef)LL_RCU_PLL0_GetBand(RCUx);      
}

/**
 * @}
 */ /* RCU_HAL_EF_Init */

/** @defgroup RCU_HAL_EF_ClockFreq Clock Frequency Functions
 * @brief    Clock Frequency Functions
 * @{
 */

/**
 * @brief  Returns the frequencies of different on chip clocks: SYSCLK, HCLK,
 *         PCLK0 and PCLK1.
 * @param  pClocks pointer to a HAL_RCU_ClocksTypeDef structure which holds
 *         the clocks frequencies.
 * @return None
 */
void HAL_RCU_GetClockFreq(HAL_RCU_ClocksTypeDef *pClocks)
{
    ASSERT_FUNC_PARAM(pClocks != NULL);

    if (pClocks == NULL) {
        return;
    }

    pClocks->SYSCLKFrequency    = RCU_GetSysClockFreq();
    pClocks->HCLKFrequency      = RCU_GetHCLKFreq();
    pClocks->PCLK0Frequency     = RCU_GetPCLK0Freq();
    pClocks->PCLK1Frequency     = RCU_GetPCLK1Freq();
}

/**
 * @brief  Returns the SYSCLK frequency.
 * @return SYSCLK frequency
 */
uint32_t HAL_RCU_GetSysClockFreq(void)
{
    return RCU_GetSysClockFreq();
}

/**
 * @brief  Returns the HCLK frequency.
 * @return HCLK frequency
 */
uint32_t HAL_RCU_GetHCLKFreq(void)
{
    return RCU_GetHCLKFreq();
}

/**
 * @brief  Returns the PCLK0 frequency.
 * @return PCLK0 frequency
 */
uint32_t HAL_RCU_GetPCLK0Freq(void)
{
    return RCU_GetPCLK0Freq();
}

/**
 * @brief  Returns the PCLK1 frequency.
 * @return PCLK1 frequency
 */
uint32_t HAL_RCU_GetPCLK1Freq(void)
{
    return RCU_GetPCLK1Freq();
}

/**
 * @brief  Returns the frequency of the specified peripheral function clock.
 * @param  PeriphClock Peripheral clock domain 
 * @return Peripheral clock frequency in Hz, 0 if PeriphClock is invalid
 */
uint32_t HAL_RCU_GetPeriphCLKFreq(HAL_RCU_PeriphClkTypeDef PeriphClock)
{
    ASSERT_FUNC_PARAM(IS_RCU_PERIPHCLK_CLK(PeriphClock));

    RCU_TypeDef *RCUx = RCU_GET_INSTANCE;

    switch (PeriphClock) {
        case HAL_RCU_PERIPHCLK_ADC:
            return RCU_GetPeriphSrcFreq(LL_RCU_GetADCClockSource(RCUx)) / LL_RCU_GetADCClockDivider(RCUx);

        case HAL_RCU_PERIPHCLK_CAN:
            return RCU_GetPeriphSrcFreq(LL_RCU_GetCANClockSource(RCUx)) / LL_RCU_GetCANClockDivider(RCUx);

        case HAL_RCU_PERIPHCLK_USB:
            return RCU_GetPeriphSrcFreq(LL_RCU_GetUSBClockSource(RCUx)) / LL_RCU_GetUSBClockDivider(RCUx);

        case HAL_RCU_PERIPHCLK_LPTMR:
            switch (LL_RCU_GetLPTMRClockSource(RCUx)) {
                case LL_RCU_FUNC_CLK_SRC_EX_APB0CLK:
                    return RCU_GetPCLK0Freq();

                case LL_RCU_FUNC_CLK_SRC_EX_HSE:
                    return RCU_GetHighSpdExtFreq();

                case LL_RCU_FUNC_CLK_SRC_EX_LSI:
                    return HAL_SYSCTRL_LSI_GetValue();

                case LL_RCU_FUNC_CLK_SRC_EX_HSI:
                default:
                    return HAL_SYSCTRL_HSI_GetValue();
            }

        default:
            return 0UL;
    }
}

/**
 * @brief  Updates the SystemCoreClock global variable.
 * @return None
 */
void HAL_RCU_UpdateSystemCoreClock(void)
{
    SystemCoreClock = RCU_GetSysClockFreq();
}
/**
 * @}
 */ /* RCU_HAL_EF_ClockFreq */


/** @defgroup RCU_HAL_EF_Status Status and Flag Functions
 * @brief    Status and Flag Functions
 * @{
 */

/**
 * @brief  Check whether PLL0 is locked.
 * @retval 0 PLL0 is not locked
 * @retval 1 PLL0 is locked
 */
uint32_t HAL_RCU_PLL0_IsReady(void)
{
    return (uint32_t)LL_RCU_PLL0_IsReady(RCU_GET_INSTANCE);
}

/**
 * @brief  Check whether a XOSC(HSE) loss event is pending (CSS).
 * @retval 0 No XOSC loss detected
 * @retval 1 XOSC loss detected
 */
uint32_t HAL_RCU_IsActiveFlag_CSS(void)
{
    return (uint32_t)LL_RCU_IsXOSCLossPnd(RCU_GET_INSTANCE);
}

/**
 * @brief  Get the system reset source flags.
 * @return This value will be any combination of @ref HAL_RCU_RstSrcPendingMskTypeDef
 */
HAL_RCU_RstSrcPendingMskTypeDef HAL_RCU_GetResetSource(void)
{
    RCU_TypeDef *RCUx = RCU_GET_INSTANCE;
    uint32_t src = 0UL;

    if (LL_RCU_IsMCLRResetActived(RCUx) != 0UL) {
        src |= HAL_RCU_RESETSOURCE_FLAG_MCLR;
    }

    if (LL_RCU_IsLowPowerResetActived(RCUx) != 0UL) {
        src |= HAL_RCU_RESETSOURCE_FLAG_LVD;
    }

    if (LL_RCU_IsCPUSystemReqResetActived(RCUx) != 0UL) {
        src |= HAL_RCU_RESETSOURCE_FLAG_SYSREQ;
    }

    if (LL_RCU_IsCPULockUpResetActived(RCUx) != 0UL) {
        src |= HAL_RCU_RESETSOURCE_FLAG_LOCKUP;
    }

    if (LL_RCU_IsIWDGResetActived(RCUx) != 0UL) {
        src |= HAL_RCU_RESETSOURCE_FLAG_IWDG;
    }

    if (LL_RCU_IsWWDGResetActived(RCUx) != 0UL) {
        src |= HAL_RCU_RESETSOURCE_FLAG_WWDG;
    }

    return src;
}

/**
 * @brief  Clear the system reset source flags.
 * @param  ResetSource This parameter can be any combination of @ref HAL_RCU_RstSrcPendingMskTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_ClearResetSource(HAL_RCU_RstSrcPendingMskTypeDef ResetSource)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_RESETSOURCE_FLAG(ResetSource) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_ClearResetPending(RCU_GET_INSTANCE, ResetSource);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Enable the reset sources that can generate a system reset.
 * @param  ResetSource Reset sources to enable.
 *         This parameter can be any combination of @ref HAL_RCU_RstSrcEnMskTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_EnableResetSource(HAL_RCU_RstSrcEnMskTypeDef ResetSource)
{
    RCU_TypeDef *RCUx = RCU_GET_INSTANCE;

    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_RESETSOURCE_EN(ResetSource) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_SYSREQ) != 0UL) {
        LL_RCU_CPU_SystemReqReset_Enable(RCUx);
    }

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_LOCKUP) != 0UL) {
        LL_RCU_CPU_LockUpReset_Enable(RCUx);
    }

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_IWDG) != 0UL) {
        LL_RCU_IWDG_Reset_Enable(RCUx);
    }

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_WWDG) != 0UL) {
        LL_RCU_WWDG_Reset_Enable(RCUx);
    }

    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Disable the reset sources that can generate a system reset.
 * @param  ResetSource Reset sources to disable.
 *         This parameter can be any combination of @ref HAL_RCU_RstSrcEnMskTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_DisableResetSource(HAL_RCU_RstSrcEnMskTypeDef ResetSource)
{
    RCU_TypeDef *RCUx = RCU_GET_INSTANCE;

    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_RESETSOURCE_EN(ResetSource) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_SYSREQ) != 0UL) {
        LL_RCU_CPU_SystemReqReset_Disable(RCUx);
    }

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_LOCKUP) != 0UL) {
        LL_RCU_CPU_LockUpReset_Disable(RCUx);
    }

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_IWDG) != 0UL) {
        LL_RCU_IWDG_Reset_Disable(RCUx);
    }

    if ((ResetSource & HAL_RCU_RESETSOURCE_EN_WWDG) != 0UL) {
        LL_RCU_WWDG_Reset_Disable(RCUx);
    }

    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @}
 */ /* RCU_HAL_EF_Status */

/** @defgroup RCU_HAL_EF_CSS Clock Security System Functions
 * @brief    Clock Security System Functions 
 * @{
 */

/**
 * @brief  Enable the clock security system 
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_EnableCSS(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_XOSC_EnableSecurceSwitch(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Disable the clock security system
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_DisableCSS(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_XOSC_DisableSecurceSwitch(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Enable the CSS NMI interrupt
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_EnableCSS_IT(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_XOSC_EnableLossNMI(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Disable the CSS NMI interrupt 
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_DisableCSS_IT(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_XOSC_DisableLossNMI(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Set the XOSC compare threshold window
 * @param  Lmt Threshold window @ref HAL_RCU_CSSLimitWindowTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetCSSLimitWindow(HAL_RCU_CSSLimitWindowTypeDef Lmt)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_CSS_LIMIT_WINDOW(Lmt) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_XOSC_SetLimitWindow(RCU_GET_INSTANCE, Lmt);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Set the XOSC auto switch window.
 * @param  Win Auto switch window @ref HAL_RCU_CSSSwitchWindowTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetCSSAutoSwitchWindow(HAL_RCU_CSSSwitchWindowTypeDef Win)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_CSS_SWITCH_WINDOW(Win) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_XOSC_SetAutoSwitchWindow(RCU_GET_INSTANCE, Win);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the XOSC compare threshold window.
 * @return Threshold window @ref HAL_RCU_CSSLimitWindowTypeDef
 */
HAL_RCU_CSSLimitWindowTypeDef HAL_RCU_GetCSSLimitWindow(void)
{
    return (HAL_RCU_CSSLimitWindowTypeDef)LL_RCU_XOSC_GetLimitWindow(RCU_GET_INSTANCE);
}

/**
 * @brief  Get the XOSC auto switch window.
 * @return Auto switch window @ref HAL_RCU_CSSSwitchWindowTypeDef
 */
HAL_RCU_CSSSwitchWindowTypeDef HAL_RCU_GetCSSAutoSwitchWindow(void)
{
    return (HAL_RCU_CSSSwitchWindowTypeDef)LL_RCU_XOSC_GetAutoSwitchWindow(RCU_GET_INSTANCE);
}

/**
 * @brief  Enable the system clock auto switch on XOSC loss whatever the SYSCLK source
 *         is HSE or PLL.
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_EnableSysClkSwitch(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_EnableSysclkSwitch(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Disable the system clock auto switch.
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_DisableSysClkSwitch(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_DisableSysclkSwitch(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Enable the PLL0 auto reload (PLLCR.ARE).
 * @note   Recommended with the CSS (manual 7.2.6 note 2).
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_EnablePLL0AutoReload(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_PLL0_AutoReload_Enable(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Disable the PLL0 auto reload (PLLCR.ARE).
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_DisablePLL0AutoReload(void)
{
    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_PLL0_AutoReload_Disable(RCU_GET_INSTANCE);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Handle the RCU NMI interrupt (XOSC loss / clock monitor).
 * @note   To be called from the user NMI_Handler().
 * @note   CSSCR.LPD is a read-only status bit (manual 7.3.2.18) which cannot be cleared
 *         by software, so this handler only checks the flag and calls the user callback;
 *         the pending condition has to be removed inside the callback by restoring the
 *         system clock (or by disabling and re-enabling the clock monitor). The flag stays
 *         set until the oscillator recovers, therefore the NMI can be re-entered
 *         (manual 7.2.6).
 * @note   The NMI is shared with the FLASH multi-bit ECC error (manual table 11-1).
 *         This handler only services the XOSC clock monitor; the ECC branch has to be
 *         handled by the user inside NMI_Handler().
 * @return None
 */
void HAL_RCU_NMI_IRQHandler(void)
{
    if (LL_RCU_IsXOSCLossPnd(RCU_GET_INSTANCE) != 0UL) {
        HAL_RCU_CSSCallback();
    }
}

/**
 * @brief  Clock security system callback.
 * @note   This function should not be modified. When the callback is needed,
 *         the HAL_RCU_CSSCallback could be implemented in the user file.
 * @return None
 */
__WEAK void HAL_RCU_CSSCallback(void)
{
    /* NOTE: This function should not be modified. When the callback is needed,
               the HAL_RCU_CSSCallback could be implemented in the user file. */
}

/**
 * @}
 */ /* RCU_HAL_EF_CSS */

/** @defgroup RCU_HAL_EF_PeriphClkConfig Peripheral Function Clock Config Functions
 * @brief    Peripheral Function Clock Config Functions (manual 7.3.2.4/7.3.2.7)
 * @{
 */

/**
 * @brief  Set the ADC clock source 
 * @param  Src ADC clock source @ref HAL_RCU_ADCCLKSourceTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetADCClockSource(HAL_RCU_ADCCLKSourceTypeDef Src)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_ADCCLK_SRC(Src) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_SetADCClockSource(RCU_GET_INSTANCE, Src);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the ADC clock source 
 * @return ADC clock source @ref HAL_RCU_ADCCLKSourceTypeDef
 */
HAL_RCU_ADCCLKSourceTypeDef HAL_RCU_GetADCClockSource(void)
{
    return (HAL_RCU_ADCCLKSourceTypeDef)LL_RCU_GetADCClockSource(RCU_GET_INSTANCE);
}

/**
 * @brief  Set the ADC clock divider
 * @param  Div ADC clock divider @ref HAL_RCU_FuncClkDivTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetADCClockDivider(HAL_RCU_FuncClkDivTypeDef Div)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_FUNC_CLK_DIV(Div) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_SetADCClockDivider(RCU_GET_INSTANCE, Div);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the ADC clock divider 
 * @return ADC clock divider @ref HAL_RCU_FuncClkDivTypeDef
 */
HAL_RCU_FuncClkDivTypeDef HAL_RCU_GetADCClockDivider(void)
{
    return (HAL_RCU_FuncClkDivTypeDef)LL_RCU_GetADCClockDivider(RCU_GET_INSTANCE);
}

/**
 * @brief  Set the CAN clock source 
 * @param  Src CAN clock source @ref HAL_RCU_CANCLKSourceTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetCANClockSource(HAL_RCU_CANCLKSourceTypeDef Src)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_CANCLK_SRC(Src) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_SetCANClockSource(RCU_GET_INSTANCE, Src);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the CAN clock source 
 * @return CAN clock source @ref HAL_RCU_CANCLKSourceTypeDef
 */
HAL_RCU_CANCLKSourceTypeDef HAL_RCU_GetCANClockSource(void)
{
    return (HAL_RCU_CANCLKSourceTypeDef)LL_RCU_GetCANClockSource(RCU_GET_INSTANCE);
}

/**
 * @brief  Set the CAN clock divider 
 * @param  Div CAN clock divider @ref HAL_RCU_FuncClkDivTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetCANClockDivider(HAL_RCU_FuncClkDivTypeDef Div)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_FUNC_CLK_DIV(Div) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_SetCANClockDivider(RCU_GET_INSTANCE, Div);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the CAN clock divider
 * @return CAN clock divider @ref HAL_RCU_FuncClkDivTypeDef
 */
HAL_RCU_FuncClkDivTypeDef HAL_RCU_GetCANClockDivider(void)
{
    return (HAL_RCU_FuncClkDivTypeDef)LL_RCU_GetCANClockDivider(RCU_GET_INSTANCE);
}

/**
 * @brief  Set the USB clock source
 * @param  Src USB clock source @ref HAL_RCU_USBCLKSourceTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetUSBClockSource(HAL_RCU_USBCLKSourceTypeDef Src)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_USBCLK_SRC(Src) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_SetUSBClockSource(RCU_GET_INSTANCE, Src);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the USB clock source 
 * @return USB clock source @ref HAL_RCU_USBCLKSourceTypeDef
 */
HAL_RCU_USBCLKSourceTypeDef HAL_RCU_GetUSBClockSource(void)
{
    return (HAL_RCU_USBCLKSourceTypeDef)LL_RCU_GetUSBClockSource(RCU_GET_INSTANCE);
}

/**
 * @brief  Set the USB clock divider 
 * @param  Div USB clock divider @ref HAL_RCU_FuncClkDivTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetUSBClockDivider(HAL_RCU_FuncClkDivTypeDef Div)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_FUNC_CLK_DIV(Div) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_SetUSBClockDivider(RCU_GET_INSTANCE, Div);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the USB clock divider 
 * @return USB clock divider @ref HAL_RCU_FuncClkDivTypeDef
 */
HAL_RCU_FuncClkDivTypeDef HAL_RCU_GetUSBClockDivider(void)
{
    return (HAL_RCU_FuncClkDivTypeDef)LL_RCU_GetUSBClockDivider(RCU_GET_INSTANCE);
}

/**
 * @brief  Set the TMR6 (low power timer) clock source 
 * @param  Src TMR6 clock source @ref HAL_RCU_LPTMRCLKSourceTypeDef
 * @return HAL status
 */
HAL_StatusTypeDef HAL_RCU_SetTMR6ClockSource(HAL_RCU_LPTMRCLKSourceTypeDef Src)
{
    HAL_RCU_PARAM_CHECK({ 
        if (IS_RCU_LPTMRCLK_SRC(Src) == 0U) { 
            return HAL_INVALID; 
        } 
    });

    LL_RCU_RegWrite_Unlock(RCU_GET_INSTANCE);
    LL_RCU_SetLPTMRClockSource(RCU_GET_INSTANCE, Src);
    LL_RCU_RegWrite_Lock(RCU_GET_INSTANCE);

    return HAL_OK;
}

/**
 * @brief  Get the TMR6 (low power timer) clock source 
 * @return TMR6 clock source @ref HAL_RCU_LPTMRCLKSourceTypeDef
 */
HAL_RCU_LPTMRCLKSourceTypeDef HAL_RCU_GetTMR6ClockSource(void)
{
    return (HAL_RCU_LPTMRCLKSourceTypeDef)LL_RCU_GetLPTMRClockSource(RCU_GET_INSTANCE);
}

/**
 * @}
 */ /* RCU_HAL_EF_PeriphClkConfig */

/**
 * @}
 */ /* RCU_HAL_Exported_Functions */

/** @defgroup RCU_HAL_Private_Functions RCU HAL Private Functions
 * @{
 */

/**
 * @brief  Return the SYSCLK frequency (internal function).
 * @return SYSCLK frequency in Hz
 */
static uint32_t RCU_GetSysClockFreq(void)
{
    uint32_t sysclockfreq;

    switch (LL_RCU_GetSysClockSource(RCU_GET_INSTANCE)) {
        case LL_RCU_SYSCLK_SRC_RC8M:
            sysclockfreq = HAL_SYSCTRL_HSI_GetValue();
            break;

        case LL_RCU_SYSCLK_SRC_RC32K:
            sysclockfreq = HAL_SYSCTRL_LSI_GetValue();
            break;

        case LL_RCU_SYSCLK_SRC_XOSC:
            sysclockfreq = RCU_GetHighSpdExtFreq();
            break;

        case LL_RCU_SYSCLK_SRC_PLL0DivClk:
            sysclockfreq = RCU_GetSysClockFreqFromPLLSource();
            break;

        default:
            sysclockfreq = HAL_SYSCTRL_HSI_GetValue();
            break;
    }

    return sysclockfreq;
}

/**
 * @brief  Return the HCLK frequency (internal function).
 * @return HCLK frequency in Hz
 */
static uint32_t RCU_GetHCLKFreq(void)
{
    return (RCU_GetSysClockFreq() / LL_RCU_GetAHBPrescaler(RCU_GET_INSTANCE));
}

/**
 * @brief  Return the PCLK0 frequency (internal function).
 * @return PCLK0 frequency in Hz
 */
static uint32_t RCU_GetPCLK0Freq(void)
{
    return (RCU_GetHCLKFreq() / LL_RCU_GetAPB0Prescaler(RCU_GET_INSTANCE));
}

/**
 * @brief  Return the PCLK1 frequency (internal function).
 * @return PCLK1 frequency in Hz
 */
static uint32_t RCU_GetPCLK1Freq(void)
{
    return (RCU_GetHCLKFreq() / LL_RCU_GetAPB1Prescaler(RCU_GET_INSTANCE));
}

/**
 * @brief  Return the frequency of a peripheral function clock source.
 * @note   PLLCLK is the PLL output before the fixed divide-by-2
 * @param  Src Clock source @ref LL_RCU_FuncClkSrcTypeDef
 * @return Clock source frequency in Hz
 */
static uint32_t RCU_GetPeriphSrcFreq(LL_RCU_FuncClkSrcTypeDef Src)
{
    if (Src == LL_RCU_FUNC_CLK_SRC_PLL0) {
        return (RCU_GetSysClockFreqFromPLLSource() * 2UL);
    } else if (Src == LL_RCU_FUNC_CLK_SRC_SYSCLK) {
        return (RCU_GetSysClockFreq());
    } else {
        return 0;
    }
}

/**
 * @brief  Return the SYSCLK frequency derived from PLL source.
 * @return SYSCLK frequency in Hz
 */
__STATIC_FORCEINLINE uint32_t RCU_GetHighSpdExtFreq(void)
{
    return HSE_VALUE;
}

/**
 * @brief  Return the SYSCLK frequency derived from PLL source.
 * @return SYSCLK frequency in Hz
 */
static uint32_t RCU_GetSysClockFreqFromPLLSource(void)
{
    uint32_t pll_source;
    uint32_t pll_integer;
    uint32_t pll_fraction;
    uint32_t ref_clk;
    uint32_t pll_freq;

    pll_source = LL_RCU_PLL0_GetRefClockSource(RCU_GET_INSTANCE);
    pll_integer = LL_RCU_PLL0_GetDividerInteger(RCU_GET_INSTANCE);
    pll_fraction = LL_RCU_PLL0_GetDividerFraction(RCU_GET_INSTANCE);

    /* Determine reference clock frequency based on PLL source */
    if (pll_source == LL_RCU_PLLCLK_SRC_HSI) {
        ref_clk = HAL_SYSCTRL_HSI_GetValue();
    }
    else if (pll_source == LL_RCU_PLLCLK_SRC_HSE) {
        ref_clk = HSE_VALUE;
    }
    else {
        /* Unknown or NONE source: fallback to default clock value for safety */
        ref_clk = LL_SYSCTRL_HSI_GetValue();
    }

    /* PLL VCO = ref_clk * 2 * (INT + FRAC/65536)
     * PLL0DivClk(SYSCLK) = PLL VCO / 2 = ref_clk * (INT + FRAC/65536)
     * Use 64-bit arithmetic to avoid overflow: ref_clk * FRAC can exceed uint32_t range
     * e.g. 8MHz * 32768 = 262G > 4.29G (uint32_t max)
     *
     * pll_freq here already equals ref_clk * (INT + FRAC/65536),
     * which is the SYSCLK value (PLL VCO / 2). No additional division needed. */
    pll_freq = (uint32_t)((uint64_t)ref_clk * pll_integer + (uint64_t)ref_clk * pll_fraction / 65536UL);

    return pll_freq;
}

/**
 * @brief  ADC0 Clock Config and Soft Reset Release for PLL Calibrate
 * @note   Unlock the RCU register before use
 * @param  RCUx Specifies RCU peripheral
 * @return None
 */
static void RCU_PLL0Cali_ADC0ClkCfgRst(RCU_TypeDef *RCUx)
{
    /* Clock Disable */
    LL_RCU_AHB1_DisableADC0Clock(RCUx);
    LL_RCU_PC_DisableADC0FunClock(RCUx);

    /* Clock Config */
    LL_RCU_SetADCClockSource(RCUx, LL_RCU_FUNC_CLK_SRC_SYSCLK);
    LL_RCU_SetADCClockDivider(RCUx, LL_RCU_FUNC_CLK_DIV1);

    /* Clock Enable */
    LL_RCU_AHB1_EnableADC0Clock(RCUx);
    LL_RCU_PC_EnableADC0FunClock(RCUx);

    /* ADC Reset */
    LL_RCU_AHB1_ForceResetADC(RCUx);
    LL_RCU_AHB1_ReleaseResetADC(RCUx);
}

/**
 * @brief  ADC0 Clock Disable and Soft Reset Release for PLL Calibrate
 * @note   Unlock the RCU register before use
 * @param  RCUx Specifies RCU peripheral
 * @return None
 */
static void RCU_PLL0Cali_ADC0ClkRstDis(RCU_TypeDef *RCUx)
{
    /* ADC Reset */
    LL_RCU_AHB1_ForceResetADC(RCUx);
    LL_RCU_AHB1_ReleaseResetADC(RCUx);

    /* Clock Disable */
    LL_RCU_AHB1_DisableADC0Clock(RCUx);
    LL_RCU_PC_DisableADC0FunClock(RCUx);
}

/**
 * @brief  RCU LL PLL0 calibrate
 * @param  RCUx Specifies RCU peripheral
 * @return Fitband
 */
static uint32_t RCU_PLL0Cali(RCU_TypeDef *RCUx)
{
    uint32_t cpout_vout_table[4];
    uint32_t fit_band = 0;
    uint32_t atcr = HAL_SYSCTRL_GetAnalogTrimConfig();
    uint32_t sysatr = HAL_SYSCTRL_GetSystemAnalogConfig();
    uint32_t pll0_status = LL_RCU_PLL0_IsEnabled(RCUx);
    uint32_t pll_band_index;
    int32_t trim_val;
    uint32_t cr_store = 0;
    uint32_t tickstart = 0;

    ADC_TypeDef *ADCx = RCU_GET_PLL0CAIL_ADC_INSTANCE;

    /* Store DEMCR and enable DWT early so the cleanup path can always restore it. */
    cr_store = CoreDebug->DEMCR;
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /* RCU/SYSCTRL Reg Unlock */
    LL_RCU_RegWrite_Unlock(RCUx);
    HAL_SYSCTRL_UnlockSystemRegister();
    HAL_SYSCTRL_UnlockSpecialRegister();

    /* Vref Buf output 2.5V */
    HAL_SYSCTRL_VREFBUF_SetOutputVoltage(HAL_SYSCTRL_VREFBUF_VOL_2V5);
    HAL_SYSCTRL_VREFBUF_Enable();

    /* ADC BUF select VRIP2 */
    HAL_SYSCTRL_EnableADCBuffer();
    HAL_SYSCTRL_SetADCBufferSource(0x3);

    /* delay 1.2ms */
    DWT->CYCCNT = (uint32_t)0U;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    while (DWT->CYCCNT < RCU_PLL0CALI_DELAY_1P2MS_CYCLES)
        ;

    /* ADC Config (PLL calibration mode) */
    LL_ADC_SetConfig(ADCx, RCU_PLL0_CALI_ADC_CFGR0);
    LL_ADC_SetConfigEx(ADCx, RCU_PLL0_CALI_ADC_CFGR1);
    LL_ADC_SetDifferEnd(ADCx, RCU_PLL0_CALI_ADC_SIGSEL_CLR);
    LL_ADC_SetSamlpeTime(ADCx, RCU_PLL0_CALI_ADC_SMPR2);
    LL_ADC_SetRegularSequence(ADCx, RCU_PLL0_CALI_ADC_SQR0);

    LL_ADC_Enable(ADCx);

    tickstart = HAL_GetTick();
    while (LL_ADC_IsActiveFlag_ADRDY(ADCx) != 1U) {
        if ((HAL_GetTick() - tickstart) > RCU_PLL0CALI_ADC_TIMEOUT_VALUE) {
            break;
        }
    }

    /* ADC REG Start Conversion (channel 17) */
    LL_ADC_ClearFlag_DONx(ADCx, LL_ADC_CH_17);
    LL_ADC_REG_StartConversion(ADCx);

    tickstart = HAL_GetTick();
    while (LL_ADC_IsActiveFlag_DONx(ADCx, LL_ADC_CH_17) != 1U) {
        if ((HAL_GetTick() - tickstart) > RCU_PLL0CALI_ADC_TIMEOUT_VALUE) {
            break;
        }
    }

    trim_val = LL_ADC_REG_ReadConversionData(ADCx);
    LL_ADC_ClearFlag_DONx(ADCx, LL_ADC_CH_17);

    /* ADC BUF select PLL0 CPOUT */
    HAL_SYSCTRL_SetADCBufferSource(LL_SYSCTRL_ADC_BUF_SRC_PLL0_TOUT);

    /* PLL0 VCOD Enable */
    LL_RCU_PLL0_VCODET_Enable(RCUx);

    for (pll_band_index = LL_RCU_PLL_BAND_0; pll_band_index <= LL_RCU_PLL_BAND_3; pll_band_index++) {
        LL_RCU_PLL0_Disable(RCUx);
        LL_RCU_PLL0_SetBand(RCUx, pll_band_index);
        LL_RCU_PLL0_Enable(RCUx);

        /* delay 1.5ms */
        DWT->CYCCNT = (uint32_t)0U;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

        while (DWT->CYCCNT < RCU_PLL0CALI_DELAY_1P5MS_CYCLES)
            ;

        cpout_vout_table[pll_band_index] = HAL_ABS(((int32_t)LL_ADC_REG_ReadConversionData(ADCx)) - trim_val / 2);
        LL_ADC_ClearFlag_DONx(ADCx, LL_ADC_CH_17);
    }

    /* Restore PLL0 status */
    if (pll0_status) {
        LL_RCU_PLL0_Enable(RCUx);
    }
    else {
        LL_RCU_PLL0_Disable(RCUx);
    }

    /* PLL0 VCODET Disable */
    LL_RCU_PLL0_VCODET_Disable(RCUx);

    /* Disable DWT cycle counter */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;

    /* Restore DEMCR before band selection */
    CoreDebug->DEMCR = cr_store;

    for (pll_band_index = 0; pll_band_index < 4; pll_band_index++) {
        if (cpout_vout_table[pll_band_index] < cpout_vout_table[fit_band]) {
            fit_band = pll_band_index;
        }
    }

    /* Stop ADC */
    LL_ADC_REG_StopConversion(ADCx);

    /* Restore SYSATR Reg */
    HAL_SYSCTRL_SetSystemAnalogConfig(sysatr);

    /* Restore ATCR Reg */
    HAL_SYSCTRL_SetAnalogTrimConfig(atcr);

    /* RCU/SYSCTRL Reg Lock */
    LL_RCU_RegWrite_Lock(RCUx);
    HAL_SYSCTRL_LockSystemRegister();
    HAL_SYSCTRL_LockSpecialRegister();

    return fit_band;
}

/**
 * @}
 */ /* RCU_HAL_Private_Functions */

/**
 * @}
 */ /* RCU_HAL */

#endif /* HAL_RCU_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* RCU */

/**
 * @}
 */ /* TAE32G58xx_HAL_Driver */

/************************ (C) COPYRIGHT Tai-Action *****END OF FILE****/