/**
  ******************************************************************************
  * @file    startup_tae32f561x.c
  * @author  Tai-Action SD Team
  * @brief   CMSIS-Core(M) Device Startup File for a tae32f561x(Cortex-M4) Device
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
#include "tae32f561x_ll_def.h"

/** @addtogroup TAE_CMSIS
  * @{
  */

/** @defgroup TAE32F561x_Startup TAE32F561x Startup
  * @brief    TAE32F561x Startup
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/** @defgroup TAE32F561x_Startup_Private_Types TAE32F561x Startup Private Types
  * @brief    TAE32F561x Startup Private Types
  * @{
  */

/**
  * @brief Exception / Interrupt Handler Function Prototype
  */
typedef void (*VECTOR_TABLE_Type)(void);

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup TAE32F561x_Startup_Private_Functions TAE32F561x Startup Private Functions
  * @brief    TAE32F561x Startup Private Functions
  * @{
  */

/**
  * @brief Default empty handler
  */
void __NO_RETURN Default_Handler(void);

/**
  * @brief Reset handler
  */
void __NO_RETURN Reset_Handler(void);

/**
  * @brief Enter PreMain (C library entry point)
  */
void __NO_RETURN __PROGRAM_START(void);

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
	//...
#elif defined (__GNUC__) /*!< GCC Compiler */
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmissing-attributes"
#endif

/**
  * @brief Cortex-M4 core exceptions handlers
  */
__WEAK_ALIAS_FUNC(NMI_Handler,              Default_Handler)
__WEAK_ALIAS_FUNC(HardFault_Handler,        Default_Handler)
__WEAK_ALIAS_FUNC(MemManage_Handler,        Default_Handler)
__WEAK_ALIAS_FUNC(BusFault_Handler,         Default_Handler)
__WEAK_ALIAS_FUNC(UsageFault_Handler,       Default_Handler)
__WEAK_ALIAS_FUNC(SVC_Handler,              Default_Handler)
__WEAK_ALIAS_FUNC(DebugMon_Handler,         Default_Handler)
__WEAK_ALIAS_FUNC(PendSV_Handler,           Default_Handler)
__WEAK_ALIAS_FUNC(SysTick_Handler,          Default_Handler)

/**
  * @brief Peripherals interrupt handlers
  */
__WEAK_ALIAS_FUNC(I2C0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(I2C1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(UART0_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART1_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART2_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART3_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART4_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(SPI0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(SPI1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(CAN0_INT0_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(CAN0_INT1_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(CAN1_INT0_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(CAN1_INT1_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(QEI0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH0_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH1_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH2_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH3_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR7_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR8_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR2_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(IWDG_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(WWDG_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(GPIOA_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOB_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOC_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOD_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOE_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(EFLASH_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(CMPG0_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_MST_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV0_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV1_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV2_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV3_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_COMM_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_NORM_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_SAMP_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_HALF_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_FULL_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_NORM_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_SAMP_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_HALF_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_FULL_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(PMU_IRQHandler,           Default_Handler)

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
	//...
#elif defined (__GNUC__) /*!< GCC Compiler */
    #pragma GCC diagnostic pop
#endif

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup TAE32F561x_Startup_Private_Variables TAE32F561x Startup Private Variables
  * @brief    TAE32F561x Startup Private Variables
  * @{
  */

/**
  * @brief Stack pointer statement
  */
extern uint32_t __INITIAL_SP;


#if defined (__GNUC__)          /*!< GCC Compiler */
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#endif

/**
  * @brief TAE32F561x Vector Table Definition
  */
const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {

    (VECTOR_TABLE_Type) &__INITIAL_SP,  /*!<     Initial Stack Pointer          */

    /* Processor Exceptions */
    Reset_Handler,                      /*!< -15 Reset Handler                  */
    NMI_Handler,                        /*!< -14 NMI Handler                    */
    HardFault_Handler,                  /*!< -13 Hard Fault Handler             */
    MemManage_Handler,                  /*!< -12 MPU Fault Handler              */
    BusFault_Handler,                   /*!< -11 Bus Fault Handler              */
    UsageFault_Handler,                 /*!< -10 Usage Fault Handler            */
    0,                                  /*!<     Reserved                       */
    0,                                  /*!<     Reserved                       */
    0,                                  /*!<     Reserved                       */
    0,                                  /*!<     Reserved                       */
    SVC_Handler,                        /*!<  -5 SVCall Handler                 */
    DebugMon_Handler,                   /*!<  -4 Debug Monitor Handler          */
    0,                                  /*!<     Reserved                       */
    PendSV_Handler,                     /*!<  -2 PendSV Handler                 */
    SysTick_Handler,                    /*!<  -1 SysTick Handler                */

    /* Processor Interrupt */
    I2C0_IRQHandler,                    /*!<  0  I2C0 Interrupt Handler         */
    I2C1_IRQHandler,                    /*!<  1  I2C1 Interrupt Handler         */
    UART0_IRQHandler,                   /*!<  2  UART0 Interrupt Handler        */
    UART1_IRQHandler,                   /*!<  3  UART1 Interrupt Handler        */
    UART2_IRQHandler,                   /*!<  4  UART2 Interrupt Handler        */
    UART3_IRQHandler,                   /*!<  5  UART3 Interrupt Handler        */
    UART4_IRQHandler,                   /*!<  6  UART4 Interrupt Handler        */
    SPI0_IRQHandler,                    /*!<  7  SPI0 Interrupt Handler         */
    SPI1_IRQHandler,                    /*!<  8  SPI1 Interrupt Handler         */
    CAN0_INT0_IRQHandler,               /*!<  9  CAN0 Interrupt Handler         */
    CAN0_INT1_IRQHandler,               /*!< 10  CAN1 Interrupt Handler         */
    CAN1_INT0_IRQHandler,               /*!< 11  CAN0 Interrupt Handler         */
    CAN1_INT1_IRQHandler,               /*!< 12  CAN1 Interrupt Handler         */
    QEI0_IRQHandler,                    /*!< 13  QEI0 Interrupt Handler         */
    DMA_CH0_IRQHandler,                 /*!< 14  DMA_CH0 Interrupt Handler      */
    DMA_CH1_IRQHandler,                 /*!< 15  DMA_CH1 Interrupt Handler      */
    DMA_CH2_IRQHandler,                 /*!< 16  DMA_CH0 Interrupt Handler      */
    DMA_CH3_IRQHandler,                 /*!< 17  DMA_CH1 Interrupt Handler      */
    TMR7_IRQHandler,                    /*!< 18  TMR7 Interrupt Handler         */
    TMR8_IRQHandler,                    /*!< 19  TMR8 Interrupt Handler         */
    TMR0_IRQHandler,                    /*!< 20  TMR0 Interrupt Handler         */
    TMR1_IRQHandler,                    /*!< 21  TMR1 Interrupt Handler         */
    TMR2_IRQHandler,                    /*!< 22  TMR2 Interrupt Handler         */
    IWDG_IRQHandler,                    /*!< 23  IWDG Interrupt Handler         */
    WWDG_IRQHandler,                    /*!< 24  WWDG Interrupt Handler         */
    GPIOA_IRQHandler,                   /*!< 25  GPIOA Interrupt Handler        */
    GPIOB_IRQHandler,                   /*!< 26  GPIOB Interrupt Handler        */
    GPIOC_IRQHandler,                   /*!< 27  GPIOC Interrupt Handler        */
    GPIOD_IRQHandler,                   /*!< 28  GPIOD Interrupt Handler        */
    GPIOE_IRQHandler,                   /*!< 29  GPIOE Interrupt Handler        */
    EFLASH_IRQHandler,                  /*!< 30  EFLASH Interrupt Handler       */
    CMPG0_IRQHandler,                   /*!< 31  CMPG0 Interrupt Handler        */
    HRPWM_MST_IRQHandler,               /*!< 32  HRPWM_MST Interrupt Handler    */
    HRPWM_SLV0_IRQHandler,              /*!< 33  HRPWM_SLV0 Interrupt Handler   */
    HRPWM_SLV1_IRQHandler,              /*!< 34  HRPWM_SLV1 Interrupt Handler   */
    HRPWM_SLV2_IRQHandler,              /*!< 35  HRPWM_SLV2 Interrupt Handler   */
    HRPWM_SLV3_IRQHandler,              /*!< 36  HRPWM_SLV3 Interrupt Handler   */
    HRPWM_COMM_IRQHandler,              /*!< 37  HRPWM_COMM Interrupt Handler   */
    ADC0_NORM_IRQHandler,               /*!< 38  ADC0_NORM Interrupt Handler    */
    ADC0_SAMP_IRQHandler,               /*!< 39  ADC0_SAMP Interrupt Handler    */
    ADC0_HALF_IRQHandler,               /*!< 40  ADC0_HALF Interrupt Handler    */
    ADC0_FULL_IRQHandler,               /*!< 41  ADC0_FULL Interrupt Handler    */
    ADC1_NORM_IRQHandler,               /*!< 42  ADC1_NORM Interrupt Handler    */
    ADC1_SAMP_IRQHandler,               /*!< 43  ADC1_SAMP Interrupt Handler    */
    ADC1_HALF_IRQHandler,               /*!< 44  ADC1_HALF Interrupt Handler    */
    ADC1_FULL_IRQHandler,               /*!< 45  ADC1_FULL Interrupt Handler    */
    PMU_IRQHandler,                     /*!< 46  PMU Interrupt Handler          */
};

#if defined (__GNUC__)      /*!< GCC Compiler */
#pragma GCC diagnostic pop

void _start(void)
{
    int main(void);
    main();

    while (1) {
    }
}
#endif

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/** @defgroup TAE32F561x_Startup_Private_Functions TAE32F561x Startup Private Functions
  * @brief    TAE32F561x Startup Private Functions
  * @{
  */

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/**
  * @brief  Reset Handler called on controller reset
  * @param  None
  * @return None
  */
void Reset_Handler(void)
{
    SystemInit();           /* CMSIS System Initialization              */
    __PROGRAM_START();      /* Enter PreMain (C library entry point)    */
}

/**
  * @brief  Default Handler for Exceptions / Interrupts
  * @param  None
  * @return None
  */
void Default_Handler(void)
{
    while (1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
#endif

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

