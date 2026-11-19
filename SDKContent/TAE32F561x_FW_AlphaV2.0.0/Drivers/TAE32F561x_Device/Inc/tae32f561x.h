/**
  ******************************************************************************
  * @file    tae32f561x.h
  * @author  Tai-Action SD Team
  * @brief   CMSIS TAE32F561x(Cortex-M4) Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for TAE32F561x devices.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral registers hardware
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F561X_H_
#define _TAE32F561X_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @defgroup TAE_CMSIS TAE CMSIS
  * @brief    TAE CMSIS
  * @{
  */

/** @defgroup TAE32F561x_Series TAE32F561x Series
  * @brief    TAE32F561x Series
  * @{
  */


/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning 586
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif


/* Includes ------------------------------------------------------------------*/
//#define TAE32F561X_REG_BIT_VERSION

#ifdef TAE32F561X_REG_BIT_VERSION
#include "tae32f561x_chip_struct.h"
#else
#include "tae32f561x_chip.h"
#endif

#if ((__CM_CMSIS_VERSION_MAIN < 5) || \
    ((__CM_CMSIS_VERSION_MAIN == 5) && (__CM_CMSIS_VERSION_SUB < 4)) || \
    ((!defined(__CM_CMSIS_VERSION_MAIN)) || (!defined(__CM_CMSIS_VERSION_SUB))))
#error "Please upgrade the CMSIS component to at least version 5.0.4, \
or add the CMSIS library path provided by TAE: ../Drivers/CMSIS/Core/Include ."
#endif


/* Exported Types ------------------------------------------------------------*/
/** @defgroup TAE32F561x_Exported_Types TAE32F561x Exported Types
  * @brief    TAE32F561x Exported Types
  * @{
  */

/** @defgroup TAE32F561x_Peripheral_Registers_Structures_Alias TAE32F561x Peripheral Registers Structures Alias
  * @brief    TAE32F561x Peripheral Registers Structures Alias
  * @{
  */

/* Internal Class Peripheral */
typedef RCU_Type     RCU_TypeDef;               /*!< RCU Peripheral Registers Structures Alias      */
typedef SYSCTRL_Type SYSCTRL_TypeDef;           /*!< SYSCTRL Peripheral Registers Structures Alias  */
typedef FLASH_Type   EFLASH_TypeDef;            /*!< EFLASH Peripheral Registers Structures Alias   */
typedef GPIOA_Type   GPIO_TypeDef;              /*!< GPIO Peripheral Registers Structures Alias     */
typedef TMR7_Type    BSTMR_TypeDef;             /*!< BSTMR Peripheral Registers Structures Alias    */
typedef TMR0_Type    GPTMRx_TypeDef;            /*!< GPTMRx Peripheral Registers Structures Alias   */

typedef QEI_Type     QEI_TypeDef;               /*!< QEI Peripheral Registers Structures Alias      */
typedef IWDG_Type    IWDG_TypeDef;              /*!< IWDG Peripheral Registers Structures Alias     */
typedef WWDG_Type    WWDG_TypeDef;              /*!< WWDG Peripheral Registers Structures Alias     */

/* Interface Class Peripheral */
typedef I2C0_Type    I2C_TypeDef;               /*!< I2C Peripheral Registers Structures Alias      */
typedef UART0_Type   UART_TypeDef;              /*!< UART Peripheral Registers Structures Alias     */
typedef SPI0_Type    SPI_TypeDef;               /*!< SPI Peripheral Registers Structures Alias      */
typedef CAN0_Type    CAN_TypeDef;               /*!< CAN Peripheral Registers Structures Alias      */

/* Analog Class Peripheral */
typedef ADC0_Type    ADC_TypeDef;               /*!< ADC Peripheral Registers Structures Alias      */
typedef DAC0_Type    DAC_TypeDef;               /*!< DAC Peripheral Registers Structures Alias      */
typedef CMP0_Type    CMP_TypeDef;               /*!< CMP Peripheral Registers Structures Alias      */

/**
  * @}
  */


/** @defgroup TAE32F561x_Peripheral_Registers_Structures TAE32F561x Peripheral Registers Structures
  * @brief    TAE32F561x Peripheral Registers Structures
  * @{
  */


/**
  * @brief DMA Channel Numbers
  */
#define DMA_CH_NUMS     (4)

/**
  * @brief DMA Channel
  */
typedef struct {
    DMA0_Type     REG;              /*!< DMA Register                   */
    __IM uint32_t RESERVED[1];
} DMA_CH_TypeDef;

/**
  * @brief DMA Registers Structure
  */
typedef struct {                    /*!< (@ 0x40022000) DMA Structure   */
    DMA_CH_TypeDef CH[DMA_CH_NUMS]; /*!< DMA Channel control Register   */
} DMA_TypeDef;                      /*!< Size = 128 (0xc0)              */


/**
  * @brief ADC DMA
  */
typedef struct {
    __IOM uint32_t TCR;             /*!< (@ 0x00000000) ADC DMA Transfer Control Register    */
    __IOM uint32_t TAR;             /*!< (@ 0x00000004) ADC DMA Transfer Address Register    */
    __IOM uint32_t TLR;             /*!< (@ 0x00000008) ADC DMA Transfer Length Register     */
    __IM  uint32_t RESERVED;
} ADC_DMA_TypeDef;


/**
  * @brief HRPWM PWMx Registers
  */
typedef struct {
    HRPWM_SLV0_Type REG;            /*!< HRPWM Slave Register           */
    __IM  uint32_t  RESERVED3[34];
} HRPWM_PWMx_TypeDef;

/**
  * @brief HRPWM Registers Structure
  */
typedef struct {                    /*!< (@ 0x4003B000) HRPWM Structure */
    HRPWM_MST_Type     Master;      /*!< HRPWM Master Registers         */
    __IM  uint32_t     RESERVED[42];
    HRPWM_PWMx_TypeDef PWM[4];      /*!< HRPWM PWMx Registers           */
    __IM  uint32_t     RESERVED1[640];
    HRPWM_COM_Type     Common;      /*!< HRPWM Common Registers         */
} HRPWM_TypeDef;                    /*!< Size = 4084 (0xFF4)            */


/**
  * @brief IQDIV Channel Numbers
  */
#define IQDIV_CH_NUMS     2

typedef struct {
  __IOM uint32_t  CR;               /*!< (@ 0x00000000) IQDIV Config Register           */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  DNDL;             /*!< (@ 0x00000008) IQDIV Dividend Low Register     */
  __IOM uint32_t  DNDH;             /*!< (@ 0x0000000C) IQDIV Dividend High Register    */
  __IOM uint32_t  SOR;              /*!< (@ 0x00000010) IQDIV Divisor Register          */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  RLTL;             /*!< (@ 0x00000018) IQDIV Result Low Register       */
  __IOM uint32_t  RLTH;             /*!< (@ 0x0000001C) IQDIV Result High Register      */
} IQDIV_CH_TypeDef;  

/**
  * @brief IQDIV Registers Structure
  */
typedef struct {                    /*!< (@ 0x4003F000) IQDIV Structure             */
    IQDIV_CH_TypeDef CH[IQDIV_CH_NUMS];
} IQDIV_TypeDef;                    /*!< Size = 64 (0x40)                           */

/**
  * @}
  */

/**
  * @}
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup TAE32F561x_Exported_Constants TAE32F561x Exported Constants
  * @brief    TAE32F561x Exported Constants
  * @{
  */

#define EFLASH_IRQn             (FLASH_IRQn)                    /*!< EFLASH IRQ Number Alias                                */


/** @defgroup TAE32F561x_Peripheral_Memory_Map TAE32F561x Peripheral Memory Map
  * @brief    TAE32F561x Peripheral Memory Map
  * @{
  */

/* Memory Region Map */
#define EFLASH_MEM_BASE         0x08000000UL                    /*!< EFLASH Memory base address in the alias region         */
#define EFLASH_BANK_END         0x0803FFFFUL                    /*!< EFLASH Bank End address in the alias region            */
#define SRAMA_BASE              0x20000000UL                    /*!< SRAMA base address in the alias region                 */
#define SRAMB_BASE              0x20002000UL                    /*!< SRAMB base address in the alias region                 */
#define SRAMC_BASE              0x20004000UL                    /*!< SRAMC base address in the alias region                 */
#define SRAMD_BASE              0x20006000UL                    /*!< SRAMD base address in the alias region                 */

/* Peripheral Bus Map */
#define PERIPH_BASE             0x40000000UL                    /*!< Peripheral base address in the alias region            */
#define APB0PERIPH_BASE         (PERIPH_BASE               )    /*!< APB0 Peripheral base address in the alias region       */
#define APB1PERIPH_BASE         (PERIPH_BASE + 0x00010000UL)    /*!< APB1 Peripheral base address in the alias region       */
#define AHB0PERIPH_BASE         (PERIPH_BASE + 0x00020000UL)    /*!< AHB0 Peripheral base address in the alias region       */
#define AHB1PERIPH_BASE         (PERIPH_BASE + 0x00030000UL)    /*!< AHB1 Peripheral base address in the alias region       */

/**
  * @}
  */


/** @defgroup TAE32F561x_Peripheral_Declaration TAE32F561x Peripheral Declaration
  * @brief    TAE32F561x Peripheral Declaration
  * @{
  */

/* APB0 */
#undef I2C0
#undef I2C1
#undef UART0
#undef UART1
#undef UART2
#undef TMR7
#undef TMR8
#undef IWDG
#undef WWDG

/* APB1 */
#undef UART3
#undef UART4
#undef SPI0
#undef SPI1
#undef CAN0
#undef CAN1
#undef TMR0
#undef TMR1
#undef TMR2

/* AHB0 */
#undef RCU
#undef SYSCTRL
#undef FLASH
#undef GPIOA
#undef GPIOB
#undef GPIOC
#undef GPIOD
#undef GPIOE
#undef VBUF
#undef QEI

/* AHB1 */
#undef ADC0
#undef ADC1
#undef DAC0
#undef DAC1
#undef DAC2
#undef DAC3
#undef CMP0
#undef CMP1
#undef CMP2
#undef CMP3
#undef IQDIV

/* APB0 */
#define I2C0        ((I2C_TypeDef     *) I2C0_BASE      )       /*!< I2C0 Peripheral Declaration    */
#define I2C1        ((I2C_TypeDef     *) I2C1_BASE      )       /*!< I2C1 Peripheral Declaration    */
#define UART0       ((UART_TypeDef    *) UART0_BASE     )       /*!< UART0 Peripheral Declaration   */
#define UART1       ((UART_TypeDef    *) UART1_BASE     )       /*!< UART1 Peripheral Declaration   */
#define UART2       ((UART_TypeDef    *) UART2_BASE     )       /*!< UART2 Peripheral Declaration   */
#define TMR7        ((BSTMR_TypeDef   *) TMR7_BASE      )       /*!< TMR7 Peripheral Declaration    */
#define TMR8        ((BSTMR_TypeDef   *) TMR8_BASE      )       /*!< TMR8 Peripheral Declaration    */
#define IWDG        ((IWDG_TypeDef    *) IWDG_BASE      )       /*!< IWDG Peripheral Declaration    */
#define WWDG        ((WWDG_TypeDef    *) WWDG_BASE      )       /*!< WWDG Peripheral Declaration    */

/* APB1 */
#define UART3       ((UART_TypeDef    *) UART3_BASE     )       /*!< UART3 Peripheral Declaration   */
#define UART4       ((UART_TypeDef    *) UART4_BASE     )       /*!< UART4 Peripheral Declaration   */
#define SPI0        ((SPI_TypeDef     *) SPI0_BASE      )       /*!< SPI0 Peripheral Declaration    */
#define SPI1        ((SPI_TypeDef     *) SPI1_BASE      )       /*!< SPI1 Peripheral Declaration    */
#define CAN0        ((CAN_TypeDef     *) CAN0_BASE      )       /*!< CAN0 Peripheral Declaration    */
#define CAN1        ((CAN_TypeDef     *) CAN1_BASE      )       /*!< CAN1 Peripheral Declaration    */
#define TMR0        ((GPTMRx_TypeDef  *) TMR0_BASE      )       /*!< TMR0 Peripheral Declaration    */
#define TMR1        ((GPTMRx_TypeDef  *) TMR1_BASE      )       /*!< TMR1 Peripheral Declaration    */
#define TMR2        ((GPTMRx_TypeDef  *) TMR2_BASE      )       /*!< TMR2 Peripheral Declaration    */

/* AHB0 */
#define RCU         ((RCU_TypeDef     *) RCU_BASE       )       /*!< RCU Peripheral Declaration     */
#define SYSCTRL     ((SYSCTRL_TypeDef *) SYSCTRL_BASE   )       /*!< SYSCTRL Peripheral Declaration */
#define DMA         ((DMA_TypeDef     *) DMA0_BASE      )       /*!< DMA Peripheral Declaration     */
#define EFLASH      ((EFLASH_TypeDef  *) FLASH_BASE     )       /*!< EFLASH Peripheral Declaration  */
#define GPIOA       ((GPIO_TypeDef    *) GPIOA_BASE     )       /*!< GPIOA Peripheral Declaration   */
#define GPIOB       ((GPIO_TypeDef    *) GPIOB_BASE     )       /*!< GPIOB Peripheral Declaration   */
#define GPIOC       ((GPIO_TypeDef    *) GPIOC_BASE     )       /*!< GPIOC Peripheral Declaration   */
#define GPIOD       ((GPIO_TypeDef    *) GPIOD_BASE     )       /*!< GPIOD Peripheral Declaration   */
#define GPIOE       ((GPIO_TypeDef    *) GPIOE_BASE     )       /*!< GPIOE Peripheral Declaration   */
#define QEI         ((QEI_TypeDef     *) QEI_BASE       )       /*!< QEI Peripheral Declaration     */
#define QEI0        (QEI)                                       /*!< QEI0 Peripheral Declaration    */

/* AHB1 */
#define ADC0        ((ADC_TypeDef     *) ADC0_BASE      )       /*!< ADC0 Peripheral Declaration    */
#define ADC1        ((ADC_TypeDef     *) ADC1_BASE      )       /*!< ADC1 Peripheral Declaration    */
#define DAC0        ((DAC_TypeDef     *) DAC0_BASE      )       /*!< DAC0 Peripheral Declaration    */
#define DAC1        ((DAC_TypeDef     *) DAC1_BASE      )       /*!< DAC1 Peripheral Declaration    */
#define DAC2        ((DAC_TypeDef     *) DAC2_BASE      )       /*!< DAC2 Peripheral Declaration    */
#define DAC3        ((DAC_TypeDef     *) DAC3_BASE      )       /*!< DAC3 Peripheral Declaration    */
#define CMP0        ((CMP_TypeDef     *) CMP0_BASE      )       /*!< CMP0 Peripheral Declaration    */
#define CMP1        ((CMP_TypeDef     *) CMP1_BASE      )       /*!< CMP1 Peripheral Declaration    */
#define CMP2        ((CMP_TypeDef     *) CMP2_BASE      )       /*!< CMP2 Peripheral Declaration    */
#define CMP3        ((CMP_TypeDef     *) CMP3_BASE      )       /*!< CMP3 Peripheral Declaration    */
#define HRPWM       ((HRPWM_TypeDef   *) HRPWM_MST_BASE )       /*!< HRPWM Peripheral Declaration   */
#define IQDIV       ((IQDIV_TypeDef   *) IQDIV_BASE     )       /*!< IQDIV Peripheral Declaration   */

/**
  * @}
  */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup TAE32F561x_Exported_Macros TAE32F561x Exported Macros
  * @brief    TAE32F561x Exported Macros
  * @{
  */

/**
  * @brief  Judge is I2C instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't I2C instance
  * @retval 1 is I2C instance
  */
#define IS_I2C_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == I2C0 || (__INSTANCE__) == I2C1)

/**
  * @brief  Judge is UART instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't UART instance
  * @retval 1 is UART instance
  */
#define IS_UART_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == UART0 || (__INSTANCE__) == UART1 || \
                                                     (__INSTANCE__) == UART2 || (__INSTANCE__) == UART3 || \
                                                     (__INSTANCE__) == UART4)

/**
  * @brief  Judge is BSTMR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't BSTMR instance
  * @retval 1 is BSTMR instance
  */
#define IS_BSTMR_ALL_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == TMR7 || (__INSTANCE__) == TMR8)

/**
  * @brief  Judge is QEI instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't QEI instance
  * @retval 1 is QEI instance
  */
#define IS_QEI_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == QEI)

/**
  * @brief  Judge is IWDG instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IWDG instance
  * @retval 1 is IWDG instance
  */
#define IS_IWDG_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == IWDG)

/**
  * @brief  Judge is WWDG instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't WWDG instance
  * @retval 1 is WWDG instance
  */
#define IS_WWDG_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == WWDG)


/**
  * @brief  Judge is SPI instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't SPI instance
  * @retval 1 is SPI instance
  */
#define IS_SPI_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == SPI0 || (__INSTANCE__) == SPI1)

/**
  * @brief  Judge is CAN instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't CAN instance
  * @retval 1 is CAN instance
  */
#define IS_CAN_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == CAN0 || (__INSTANCE__) == CAN1)

/**
  * @brief  Judge is GPTMRX instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't GPTMRX instance
  * @retval 1 is GPTMRX instance
  */
#define IS_GPTMRX_ALL_INSTANCE(__INSTANCE__)        ((__INSTANCE__) == TMR0 || (__INSTANCE__) == TMR1 || (__INSTANCE__) == TMR2)


/**
  * @brief  Judge is RCU instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't RCU instance
  * @retval 1 is RCU instance
  */
#define IS_RCU_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == RCU)

/**
  * @brief  Judge is SYSCTRL instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't SYSCTRL instance
  * @retval 1 is SYSCTRL instance
  */
#define IS_SYSCTRL_ALL_INSTANCE(__INSTANCE__)       ((__INSTANCE__) == SYSCTRL)

/**
  * @brief  Judge is DMA instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't DMA instance
  * @retval 1 is DMA instance
  */
#define IS_DMA_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == DMA)

/**
  * @brief  Judge is EFLASH instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't EFLASH instance
  * @retval 1 is EFLASH instance
  */
#define IS_EFLASH_ALL_INSTANCE(__INSTANCE__)        ((__INSTANCE__) == EFLASH)

/**
  * @brief  Judge is GPIO instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't GPIO instance
  * @retval 1 is GPIO instance
  */
#define IS_GPIO_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == GPIOA || (__INSTANCE__) == GPIOB || \
                                                     (__INSTANCE__) == GPIOC || (__INSTANCE__) == GPIOD || \
                                                     (__INSTANCE__) == GPIOE)

/**
  * @brief  Judge is ADC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't ADC instance
  * @retval 1 is ADC instance
  */
#define IS_ADC_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == ADC0 || (__INSTANCE__) == ADC1)

/**
  * @brief  Judge is Master ADC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't Master ADC instance
  * @retval 1 is Master ADC instance
  */
#define IS_ADC_MASTER_INSTANCE(__INSTANCE__)        ((__INSTANCE__) == ADC0)

/**
  * @brief  Judge is Slave ADC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't Slave ADC instance
  * @retval 1 is Slave ADC instance
  */
#define IS_ADC_SLAVE_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == ADC1)

/**
  * @brief  Judge is DAC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't DAC instance
  * @retval 1 is DAC instance
  */
#define IS_DAC_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == DAC0 || (__INSTANCE__) == DAC1 || \
                                                     (__INSTANCE__) == DAC2 || (__INSTANCE__) == DAC3)

/**
  * @brief  Judge is CMP instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't CMP instance
  * @retval 1 is CMP instance
  */
#define IS_CMP_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == CMP0 || (__INSTANCE__) == CMP1 || \
                                                     (__INSTANCE__) == CMP2 || (__INSTANCE__) == CMP3)

/**
  * @brief  Judge is HRPWM instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't HRPWM instance
  * @retval 1 is HRPWM instance
  */
#define IS_HRPWM_ALL_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == HRPWM)

/**
  * @brief  Judge is TMR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't TMR instance
  * @retval 1 is TMR instance
  */
#define IS_TMR_ALL_INSTANCE(__INSTANCE__)           (IS_BSTMR_ALL_INSTANCE(__INSTANCE__)  || \
                                                     IS_GPTMRX_ALL_INSTANCE(__INSTANCE__))

/**
  * @brief  Judge is IQDIV instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IQDIV instance
  * @retval 1 is IQDIV instance
  */
#define IS_IQDIV_ALL_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == IQDIV)


/**
  * @brief  Get I2C IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for I2C
 */
#define GET_I2C_IRQ_NUMBER(__INSTANCE__)            \
    (  ((__INSTANCE__) == I2C0)   ? I2C0_IRQn       \
     : ((__INSTANCE__) == I2C1)   ? I2C1_IRQn       \
                                  : ((IRQn_Type)-128))

/**
  * @brief  Get UART IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for UART
 */
#define GET_UART_IRQ_NUMBER(__INSTANCE__)           \
    (  ((__INSTANCE__) == UART0)   ? UART0_IRQn     \
     : ((__INSTANCE__) == UART1)   ? UART1_IRQn     \
     : ((__INSTANCE__) == UART2)   ? UART2_IRQn     \
     : ((__INSTANCE__) == UART3)   ? UART3_IRQn     \
     : ((__INSTANCE__) == UART4)   ? UART4_IRQn     \
                                  : ((IRQn_Type)-128))

/**
  * @brief  Get SPI IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for SPI
 */
#define GET_SPI_IRQ_NUMBER(__INSTANCE__)            \
    (  ((__INSTANCE__) == SPI0)   ? SPI0_IRQn       \
     : ((__INSTANCE__) == SPI1)   ? SPI1_IRQn       \
                                  : ((IRQn_Type)-128))

/**
  * @brief  Get CAN IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for CAN
 */
#define GET_CAN_INT0_IRQ_NUMBER(__INSTANCE__)       \
    (  ((__INSTANCE__) == CAN0)   ? CAN0_INT0_IRQn  \
     : ((__INSTANCE__) == CAN1)   ? CAN1_INT0_IRQn  \
                                  : ((IRQn_Type)-128))

/**
  * @brief  Get CAN IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for CAN
 */
#define GET_CAN_INT1_IRQ_NUMBER(__INSTANCE__)       \
    (  ((__INSTANCE__) == CAN0)   ? CAN0_INT1_IRQn  \
     : ((__INSTANCE__) == CAN1)   ? CAN1_INT1_IRQn  \
                                  : ((IRQn_Type)-128))


/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif


/**
  * @}
  */


/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _TAE32F561X_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

