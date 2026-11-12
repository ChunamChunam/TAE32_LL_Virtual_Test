/**
  ******************************************************************************
  * @file    tae32g58xx_hal_sysctrl.h
  * @author  Tai-Action SD Team
  * @brief   Header file for SYSCTRL HAL module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_HAL_SYSCTRL_H_
#define _TAE32G58XX_HAL_SYSCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_sysctrl.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(SYSCTRL)

/** @addtogroup SYSCTRL_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup SYSCTRL_HAL_Exported_Macros SYSCTRL HAL Exported Macros
  * @brief    SYSCTRL HAL Exported Macros
  * @{
  */

/** @defgroup SYSCTRL_HAL_EM_Function SYSCTRL HAL Macros Function
  * @brief    SYSCTRL HAL Macros Function
  * @{
  */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the PLL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#define HAL_SYSCTRL_HSI_VAL_GET                             LL_SYSCTRL_HSI_GetValue

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  *        Defines the value of the Internal Low Speed oscillator in Hz.
  * @note  The real value may vary depending on the variations in voltage and temperature.
  */ 
#define HAL_SYSCTRL_LSI_VAL_GET                             LL_SYSCTRL_LSI_GetValue


/**
  * @brief Convert a DMA HS interrupt flag number to its corresponding bit mask.
  */ 
#define HAL_SYSCTRL_DMA_HS_IFS_NUM_TO_MASK(__NUM__)         LL_SYSCTRL_DRCR_NUM_TO_MASK(__NUM__)
/**
  * @}
  */ /* SYSCTRL_HAL_EM_Function */



/** @defgroup SYSCTRL_HAL_EM_Mask SYSCTRL HAL Mask
  * @brief    SYSCTRL HAL Mask
  * @{
  */

/** @name HAL_SYSCTRL_ITEnMskTypeDef
  * @brief SYSCTRL Interrupt Enable Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_SYSCTRL_ITEnMskTypeDef                          LL_SYSCTRL_PECR_ITEnMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_SYSCTRL_PECR_ITEnMskTypeDef HAL_SYSCTRL_ITEnMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_SYSCTRL_VDD_OVER_CURRENT_IT_EN                  LL_SYSCTRL_PECR_VDDOCIE                            /*!< VDDOCIE Mask             */
#define HAL_SYSCTRL_AVCC_LOW_VOLTAGE_IT_EN                  LL_SYSCTRL_PECR_AVCCLVIE                           /*!< AVCCLVIE Mask            */
#define HAL_SYSCTRL_VCC_LOW_VOLTAGE_IT_EN                   LL_SYSCTRL_PECR_VCCLVIE                            /*!< VCCLVIE Mask             */
#define HAL_SYSCTRL_VDD_LOW_VOLTAGE_IT_EN                   LL_SYSCTRL_PECR_VDDLVIE                            /*!< VDDLVIE Mask             */
/** @} */

/** @name HAL_SYSCTRL_ITPendingMskTypeDef
  * @brief SYSCTRL Interrupt Pending Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_SYSCTRL_ITPendingMskTypeDef                     LL_SYSCTRL_PSR_ITPendingMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_SYSCTRL_PSR_ITPendingMskTypeDef HAL_SYSCTRL_ITPendingMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_SYSCTRL_VDD_OVER_CURRENT_IT_FLAG                LL_SYSCTRL_PSR_VDDOCS                              /*!< VDDOCS Mask              */
#define HAL_SYSCTRL_AVCC_LOW_VOLTAGE_IT_FLAG                LL_SYSCTRL_PSR_AVCCLVS                             /*!< AVCCLVS Mask             */
#define HAL_SYSCTRL_VCC_LOW_VOLTAGE_IT_FLAG                 LL_SYSCTRL_PSR_VCCLVS                              /*!< VCCLVS Mask              */
#define HAL_SYSCTRL_VDD_LOW_VOLTAGE_IT_FLAG                 LL_SYSCTRL_PSR_VDDLVS                              /*!< VDDLVS Mask              */
/** @} */

/**
  * @}
  */ /* SYSCTRL_HAL_EM_Function */


/** @defgroup SYSCTRL_HAL_EM_Assert SYSCTRL HAL Assert
  * @brief    SYSCTRL HAL Assert
  * @{
  */

/**
  * @brief  The HAL_SYSCTRL_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_SYSCTRL_CHECK_PARAM
#define TAE32_USE_HAL_SYSCTRL_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_SYSCTRL_CHECK_PARAM != 1) && (TAE32_USE_HAL_SYSCTRL_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_SYSCTRL_CHECK_PARAM
#define TAE32_USE_HAL_SYSCTRL_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_SYSCTRL_CHECK_PARAM */

/**
  * @brief  The HAL_SYSCTRL_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_SYSCTRL_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_SYSCTRL_CHECK_PARAM) { \
            expression;                          \
        }

/**
  * @}
  */ /* SYSCTRL_HAL_EM_Assert */

/**
  * @}
  */ /* SYSCTRL_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup SYSCTRL_HAL_Exported_Types SYSCTRL HAL Exported Types
  * @brief    SYSCTRL HAL Exported Types
  * @{
  */

/**
  * @brief SYSCTRL ADC Buffer Source Definition
  */
typedef enum
{
    HAL_SYSCTRL_ADC_BUF_SRC_AVSS       = LL_SYSCTRL_ADC_BUF_SRC_AVSS,        /*!< ADC Buffer Source AVSS          */
    HAL_SYSCTRL_ADC_BUF_SRC_TSENSOR    = LL_SYSCTRL_ADC_BUF_SRC_TSENSOR,     /*!< ADC Buffer Source Temp SENSOR   */
    HAL_SYSCTRL_ADC_BUF_SRC_VBGR       = LL_SYSCTRL_ADC_BUF_SRC_VBGR,        /*!< ADC Buffer Source VBGR          */
    HAL_SYSCTRL_ADC_BUF_SRC_VR1P2      = LL_SYSCTRL_ADC_BUF_SRC_VR1P2,       /*!< ADC Buffer Source VR1P2         */
    HAL_SYSCTRL_ADC_BUF_SRC_VREFN      = LL_SYSCTRL_ADC_BUF_SRC_VREFN,       /*!< ADC Buffer Source VREFN         */
    HAL_SYSCTRL_ADC_BUF_SRC_VREF       = LL_SYSCTRL_ADC_BUF_SRC_VREF,        /*!< ADC Buffer Source VREF          */
    HAL_SYSCTRL_ADC_BUF_SRC_AVCC       = LL_SYSCTRL_ADC_BUF_SRC_AVCC,        /*!< ADC Buffer Source AVCC          */
    HAL_SYSCTRL_ADC_BUF_SRC_AVDD       = LL_SYSCTRL_ADC_BUF_SRC_AVDD,        /*!< ADC Buffer Source AVDD          */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC0_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC0_OUT,    /*!< ADC Buffer Source DAC0 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC1_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC1_OUT,    /*!< ADC Buffer Source DAC1 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC2_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC2_OUT,    /*!< ADC Buffer Source DAC2 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC3_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC3_OUT,    /*!< ADC Buffer Source DAC3 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC4_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC4_OUT,    /*!< ADC Buffer Source DAC4 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC5_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC5_OUT,    /*!< ADC Buffer Source DAC5 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC6_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC6_OUT,    /*!< ADC Buffer Source DAC6 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC7_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC7_OUT,    /*!< ADC Buffer Source DAC7 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_DAC8_OUT   = LL_SYSCTRL_ADC_BUF_SRC_DAC8_OUT,    /*!< ADC Buffer Source DAC8 OUT      */
    HAL_SYSCTRL_ADC_BUF_SRC_TOUT       = LL_SYSCTRL_ADC_BUF_SRC_TOUT,        /*!< ADC Buffer Source TOUT          */
    HAL_SYSCTRL_ADC_BUF_SRC_PLL0_TOUT  = LL_SYSCTRL_ADC_BUF_SRC_PLL0_TOUT,   /*!< ADC Buffer Source PLL0 TOUT     */
    HAL_SYSCTRL_ADC_BUF_SRC_ADC0_IN16  = LL_SYSCTRL_ADC_BUF_SRC_ADC0_IN16,   /*!< ADC Buffer Source ADC0 IN16     */
    HAL_SYSCTRL_ADC_BUF_SRC_ADC1_IN16  = LL_SYSCTRL_ADC_BUF_SRC_ADC1_IN16,   /*!< ADC Buffer Source ADC1 IN16     */
    HAL_SYSCTRL_ADC_BUF_SRC_ADC2_IN16  = LL_SYSCTRL_ADC_BUF_SRC_ADC2_IN16,   /*!< ADC Buffer Source ADC2 IN16     */
    HAL_SYSCTRL_ADC_BUF_SRC_ADC3_IN16  = LL_SYSCTRL_ADC_BUF_SRC_ADC3_IN16,   /*!< ADC Buffer Source ADC3 IN16     */
} HAL_SYSCTRL_ADCBufSrcTypeDef;

/**
  * @brief SYSCTRL VDD Voltage Definition
  */
typedef enum
{
    HAL_SYSCTRL_VDD_VOL_0V88  = LL_SYSCTRL_VDD_VOL_0V88,   /*!< VDD Voltage 0.88V   */
    HAL_SYSCTRL_VDD_VOL_0V92  = LL_SYSCTRL_VDD_VOL_0V92,   /*!< VDD Voltage 0.92V   */
    HAL_SYSCTRL_VDD_VOL_0V96  = LL_SYSCTRL_VDD_VOL_0V96,   /*!< VDD Voltage 0.96V   */
    HAL_SYSCTRL_VDD_VOL_1V    = LL_SYSCTRL_VDD_VOL_1V,     /*!< VDD Voltage 1V      */
    HAL_SYSCTRL_VDD_VOL_1V04  = LL_SYSCTRL_VDD_VOL_1V04,   /*!< VDD Voltage 1.04V   */
    HAL_SYSCTRL_VDD_VOL_1V08  = LL_SYSCTRL_VDD_VOL_1V08,   /*!< VDD Voltage 1.08V   */
    HAL_SYSCTRL_VDD_VOL_1V12  = LL_SYSCTRL_VDD_VOL_1V12,   /*!< VDD Voltage 1.12V   */
    HAL_SYSCTRL_VDD_VOL_1V16  = LL_SYSCTRL_VDD_VOL_1V16,   /*!< VDD Voltage 1.16V   */
    HAL_SYSCTRL_VDD_VOL_1V2   = LL_SYSCTRL_VDD_VOL_1V2,    /*!< VDD Voltage 1.20V   */
    HAL_SYSCTRL_VDD_VOL_1V24  = LL_SYSCTRL_VDD_VOL_1V24,   /*!< VDD Voltage 1.24V   */
    HAL_SYSCTRL_VDD_VOL_1V28  = LL_SYSCTRL_VDD_VOL_1V28,   /*!< VDD Voltage 1.28V   */
    HAL_SYSCTRL_VDD_VOL_1V32  = LL_SYSCTRL_VDD_VOL_1V32,   /*!< VDD Voltage 1.32V   */
    HAL_SYSCTRL_VDD_VOL_1V36  = LL_SYSCTRL_VDD_VOL_1V36,   /*!< VDD Voltage 1.36V   */
    HAL_SYSCTRL_VDD_VOL_1V4   = LL_SYSCTRL_VDD_VOL_1V4,    /*!< VDD Voltage 1.40V   */
    HAL_SYSCTRL_VDD_VOL_1V44  = LL_SYSCTRL_VDD_VOL_1V44,   /*!< VDD Voltage 1.44V   */
    HAL_SYSCTRL_VDD_VOL_1V48  = LL_SYSCTRL_VDD_VOL_1V48    /*!< VDD Voltage 1.48V   */
} HAL_SYSCTRL_VDDVolTypeDef;

/**
  * @brief SYSCTRL AVDD Voltage Definition
  */
typedef enum
{
    HAL_SYSCTRL_AVDD_VOL_1V   = LL_SYSCTRL_AVDD_VOL_1V,    /*!< AVDD Voltage 1V     */
    HAL_SYSCTRL_AVDD_VOL_1V1  = LL_SYSCTRL_AVDD_VOL_1V1,   /*!< AVDD Voltage 1.1V   */
    HAL_SYSCTRL_AVDD_VOL_1V2  = LL_SYSCTRL_AVDD_VOL_1V2,   /*!< AVDD Voltage 1.2V   */
    HAL_SYSCTRL_AVDD_VOL_1V3  = LL_SYSCTRL_AVDD_VOL_1V3    /*!< AVDD Voltage 1.3V   */
} HAL_SYSCTRL_AVDDVolTypeDef;

/**
  * @brief SYSCTRL VDD OverCurrent Threshold Definition
  */
typedef enum
{
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_150mA  = LL_SYSCTRL_VDD_OVER_CUR_THRES_150mA,   /*!< VDD OverCurrent Threshold 150mA   */
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_175mA  = LL_SYSCTRL_VDD_OVER_CUR_THRES_175mA,   /*!< VDD OverCurrent Threshold 175mA   */
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_200mA  = LL_SYSCTRL_VDD_OVER_CUR_THRES_200mA,   /*!< VDD OverCurrent Threshold 200mA   */
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_225mA  = LL_SYSCTRL_VDD_OVER_CUR_THRES_225mA    /*!< VDD OverCurrent Threshold 225mA   */
} HAL_SYSCTRL_VDDOverCurThresTypeDef;

/**
  * @brief SYSCTRL AVCC LowVoltage Threshold Definition
  */
typedef enum
{
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_2V55  = LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V55,   /*!< AVCC LowVoltage Threshold 2.55V   */
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_2V7   = LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V7,    /*!< AVCC LowVoltage Threshold 2.7V    */
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_2V85  = LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V85,   /*!< AVCC LowVoltage Threshold 2.85V   */
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_3V    = LL_SYSCTRL_AVCC_LOW_VOL_THRES_3V      /*!< AVCC LowVoltage Threshold 3V      */
} HAL_SYSCTRL_AVCCLowVolThresTypeDef;

/**
  * @brief SYSCTRL VDD LowVoltage Threshold Definition
  */
typedef enum
{
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V75  = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V75,   /*!< VDD LowVoltage Threshold 0.75V   */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V8   = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V8,    /*!< VDD LowVoltage Threshold 0.8V    */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V85  = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V85,   /*!< VDD LowVoltage Threshold 0.85V   */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V9   = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V9,    /*!< VDD LowVoltage Threshold 0.9V    */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V95  = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V95,   /*!< VDD LowVoltage Threshold 0.95V   */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_1V    = LL_SYSCTRL_VDD_LOW_VOL_THRES_1V,     /*!< VDD LowVoltage Threshold 1.0V    */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_1V05  = LL_SYSCTRL_VDD_LOW_VOL_THRES_1V05,   /*!< VDD LowVoltage Threshold 1.05V   */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_1V1   = LL_SYSCTRL_VDD_LOW_VOL_THRES_1V1     /*!< VDD LowVoltage Threshold 1.1V    */
} HAL_SYSCTRL_VDDLowVolThresTypeDef;

/**
  * @brief SYSCTRL VREFBUF Output Voltage Definition
  */
typedef enum
{
    HAL_SYSCTRL_VREFBUF_VOL_2V9  = LL_SYSCTRL_VREFBUF_VOL_2V9,   /*!< VREFBUF Output Voltage 2.9V   */
    HAL_SYSCTRL_VREFBUF_VOL_2V5  = LL_SYSCTRL_VREFBUF_VOL_2V5    /*!< VREFBUF Output Voltage 2.5V   */
} HAL_SYSCTRL_VrefBufVolTypeDef;

/**
  * @brief SYSCTRL Flash Double Bank Mapping Definition
  */
typedef enum
{
    HAL_SYSCTRL_FLASH_BANK_MAPPING_0  = LL_SYSCTRL_FLASH_BANK_MAPPING_0,   /*!< Flash Bank Mapping type 0   */
    HAL_SYSCTRL_FLASH_BANK_MAPPING_1  = LL_SYSCTRL_FLASH_BANK_MAPPING_1    /*!< Flash Bank Mapping type 1   */
} HAL_SYSCTRL_FlashBankMappingTypeDef;

/**
  * @brief SYSCTRL Power Detect Enable Definition
  */
typedef enum
{
    HAL_SYSCTRL_FUNC_DISABLE    = 0U,   /*!< SYSCTRL Function Disable  */
    HAL_SYSCTRL_FUNC_ENABLE     = 1U    /*!< SYSCTRL Function Enable   */
} HAL_SYSCTRL_EnableTypeDef;

/**
  * @brief SYSCTRL VREFBUF Reference Type Definition
  */
typedef enum
{
    HAL_SYSCTRL_VREFBUF_REF_EXT = 0U,   /*!< SYSCTRL Function Disable  */
    HAL_SYSCTRL_VREFBUF_REF_INT = 1U    /*!< SYSCTRL Function Enable   */
} HAL_SYSCTRL_VrefBufTypeDef;



/**
  * @brief SYSCTRL Power Detect Type Definition
  */
typedef struct 
{
    HAL_SYSCTRL_EnableTypeDef VCCLowVoltage;    /* VCC Low Voltage Detect   */
    HAL_SYSCTRL_EnableTypeDef AVCCLowVoltage;   /* AVCC Low Voltage Detect  */
    HAL_SYSCTRL_EnableTypeDef VDDOverCurrent;   /* VDD Over Current Detect  */
    HAL_SYSCTRL_EnableTypeDef VDDLowVoltage;    /* VDD Low Voltage Detect   */
} HAL_SYSCTRL_PowerDetectTypeDef;

/**
  * @brief SYSCTRL VREFBUF Output Type Definition
  */
typedef struct 
{
    HAL_SYSCTRL_VrefBufTypeDef      Reference;      /* VREFBUF External/Internal Reference  */
    HAL_SYSCTRL_VrefBufVolTypeDef   OutputVoltage;  /* VREFBUF Output Voltage               */
} HAL_SYSCTRL_VrefBufOutputTypeDef;

/**
  * @brief SYSCTRL ADC Buffer Type Definition
  */
typedef struct 
{
    HAL_SYSCTRL_ADCBufSrcTypeDef    BufferSource;
    HAL_SYSCTRL_EnableTypeDef       BufferBypass;
    HAL_SYSCTRL_EnableTypeDef       BufferEnable;
} HAL_SYSCTRL_ADCBufTypeDef;

/**
  * @}
  */ /* SYSCTRL_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup SYSCTRL_HAL_Exported_Functions
  * @{
  */

/** @defgroup SYSCTRL_HAL_EF_Inline_Configuration
  * @{
  */

/**
 * @brief  HRPWM Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_HRPWM(void)
{
    LL_SYSCTRL_EnableDebug_HRPWM(SYSCTRL);
}

/**
 * @brief  HRPWM Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_HRPWM(void)
{
    LL_SYSCTRL_DisableDebug_HRPWM(SYSCTRL);
}

/**
 * @brief  Judge is HRPWM Debug Enable or not
 * @retval 0 HRPWM Debug is Disable
 * @retval 1 HRPWM Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_HRPWM(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_HRPWM(SYSCTRL));
}

/**
 * @brief  WWDG Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_WWDG(void)
{
    LL_SYSCTRL_EnableDebug_WWDG(SYSCTRL);
}

/**
 * @brief  WWDG Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_WWDG(void)
{
    LL_SYSCTRL_DisableDebug_WWDG(SYSCTRL);
}

/**
 * @brief  Judge is WWDG Debug Enable or not
 * @retval 0 WWDG Debug is Disable
 * @retval 1 WWDG Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_WWDG(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_WWDG(SYSCTRL));
}

/**
 * @brief  IWDG Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_IWDG(void)
{
    LL_SYSCTRL_EnableDebug_IWDG(SYSCTRL);
}

/**
 * @brief  IWDG Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_IWDG(void)
{
    LL_SYSCTRL_DisableDebug_IWDG(SYSCTRL);
}

/**
 * @brief  Judge is IWDG Debug Enable or not
 * @retval 0 IWDG Debug is Disable
 * @retval 1 IWDG Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_IWDG(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_IWDG(SYSCTRL));
}

/**
 * @brief  TMR0 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR0(void)
{
    LL_SYSCTRL_EnableDebug_TMR0(SYSCTRL);
}

/**
 * @brief  TMR0 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR0(void)
{
    LL_SYSCTRL_DisableDebug_TMR0(SYSCTRL);
}

/**
 * @brief  Judge is TMR0 Debug Enable or not
 * @retval 0 TMR0 Debug is Disable
 * @retval 1 TMR0 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR0(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR0(SYSCTRL));
}

/**
 * @brief  TMR1 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR1(void)
{
    LL_SYSCTRL_EnableDebug_TMR1(SYSCTRL);
}

/**
 * @brief  TMR1 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR1(void)
{
    LL_SYSCTRL_DisableDebug_TMR1(SYSCTRL);
}

/**
 * @brief  Judge is TMR1 Debug Enable or not
 * @retval 0 TMR1 Debug is Disable
 * @retval 1 TMR1 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR1(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR1(SYSCTRL));
}

/**
 * @brief  TMR2 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR2(void)
{
    LL_SYSCTRL_EnableDebug_TMR2(SYSCTRL);
}

/**
 * @brief  TMR2 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR2(void)
{
    LL_SYSCTRL_DisableDebug_TMR2(SYSCTRL);
}

/**
 * @brief  Judge is TMR2 Debug Enable or not
 * @retval 0 TMR2 Debug is Disable
 * @retval 1 TMR2 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR2(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR2(SYSCTRL));
}

/**
 * @brief  TMR3 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR3(void)
{
    LL_SYSCTRL_EnableDebug_TMR3(SYSCTRL);
}

/**
 * @brief  TMR3 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR3(void)
{
    LL_SYSCTRL_DisableDebug_TMR3(SYSCTRL);
}

/**
 * @brief  Judge is TMR3 Debug Enable or not
 * @retval 0 TMR3 Debug is Disable
 * @retval 1 TMR3 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR3(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR3(SYSCTRL));
}

/**
 * @brief  TMR4 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR4(void)
{
    LL_SYSCTRL_EnableDebug_TMR4(SYSCTRL);
}

/**
 * @brief  TMR4 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR4(void)
{
    LL_SYSCTRL_DisableDebug_TMR4(SYSCTRL);
}

/**
 * @brief  Judge is TMR4 Debug Enable or not
 * @retval 0 TMR4 Debug is Disable
 * @retval 1 TMR4 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR4(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR4(SYSCTRL));
}

/**
 * @brief  TMR7 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR7(void)
{
    LL_SYSCTRL_EnableDebug_TMR7(SYSCTRL);
}

/**
 * @brief  TMR7 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR7(void)
{
    LL_SYSCTRL_DisableDebug_TMR7(SYSCTRL);
}

/**
 * @brief  Judge is TMR7 Debug Enable or not
 * @retval 0 TMR7 Debug is Disable
 * @retval 1 TMR7 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR7(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR7(SYSCTRL));
}

/**
 * @brief  TMR8 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR8(void)
{
    LL_SYSCTRL_EnableDebug_TMR8(SYSCTRL);
}

/**
 * @brief  TMR8 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR8(void)
{
    LL_SYSCTRL_DisableDebug_TMR8(SYSCTRL);
}

/**
 * @brief  Judge is TMR8 Debug Enable or not
 * @retval 0 TMR8 Debug is Disable
 * @retval 1 TMR8 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR8(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR8(SYSCTRL));
}

/**
 * @brief  TMR9 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR9(void)
{
    LL_SYSCTRL_EnableDebug_TMR9(SYSCTRL);
}

/**
 * @brief  TMR9 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR9(void)
{
    LL_SYSCTRL_DisableDebug_TMR9(SYSCTRL);
}

/**
 * @brief  Judge is TMR9 Debug Enable or not
 * @retval 0 TMR9 Debug is Disable
 * @retval 1 TMR9 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR9(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR9(SYSCTRL));
}

/**
 * @brief  TMR10 Debug Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableDebug_TMR10(void)
{
    LL_SYSCTRL_EnableDebug_TMR10(SYSCTRL);
}

/**
 * @brief  TMR10 Debug Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableDebug_TMR10(void)
{
    LL_SYSCTRL_DisableDebug_TMR10(SYSCTRL);
}

/**
 * @brief  Judge is TMR10 Debug Enable or not
 * @retval 0 TMR10 Debug is Disable
 * @retval 1 TMR10 Debug is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsEnabledDebug_TMR10(void)
{
    return (uint32_t)(LL_SYSCTRL_IsEnabledDebug_TMR10(SYSCTRL));
}

/**
 * @brief  DMA Request Control Set
 * @note   The LSB is Request_0 and MSB is Request_31
 * @param  Pos DMA Request Control Bit Shift
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_SetDMARequestControl(uint32_t Pos)
{
    LL_SYSCTRL_SetDMARequestControl(SYSCTRL, Pos);
}

/**
 * @brief  DMA Request Config Set
 * @param  Mask DMA Request Config Bit Mask
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_SetDMARequestConfig(uint32_t Mask)
{
    LL_SYSCTRL_SetDMARequestConfig(SYSCTRL, Mask);
}

/**
 * @brief  DMA Request Control Reset
 * @note   The LSB is Request_0 and MSB is Request_31
 * @param  Pos DMA Request Control Bit Shift
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_ResetDMARequestControl(uint32_t Pos)
{
    LL_SYSCTRL_ResetDMARequestControl(SYSCTRL, Pos);
}

/**
 * @brief  DMA Request Config Reset
 * @note   The LSB is Request_0 and MSB is Request_31
 * @param  Mask DMA Request Config Bit
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_ResetDMARequestConfig(uint32_t Mask)
{
    LL_SYSCTRL_ResetDMARequestConfig(SYSCTRL, Mask);
}

/**
 * @brief  DMA Request Config Get
 * @note   For the sequence of register data bit, LSB is bit19
 * @return DMA Request Config
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetDMARequestControl(void)
{
    return (uint32_t)(LL_SYSCTRL_GetDMARequestControl(SYSCTRL));
}

/**
 * @brief  FLASH Double Bank Mapping Set
 * @param  Map Bank Mapping @ref HAL_SYSCTRL_FlashBankMappingTypeDef
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_SetEFlashBankMapping(HAL_SYSCTRL_FlashBankMappingTypeDef Map)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_FLASH_BANK_MAPPING(Map));

    LL_SYSCTRL_SetEFlashBankMapping(SYSCTRL, Map);
}

/**
 * @brief  FLASH Double Bank Mapping Get
 * @return Bank Mapping @ref HAL_SYSCTRL_FlashBankMappingTypeDef
 *
 */
__STATIC_INLINE HAL_SYSCTRL_FlashBankMappingTypeDef HAL_SYSCTRL_GetEFlashBankMapping(void)
{
    return (HAL_SYSCTRL_FlashBankMappingTypeDef)(LL_SYSCTRL_GetEFlashBankMapping(SYSCTRL));
}

/**
 * @brief  QEI2 Fault Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableQEI2Fault(void)
{
    LL_SYSCTRL_EnableQEI2Fault(SYSCTRL);
}

/**
 * @brief  QEI2 Fault Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableQEI2Fault(void)
{
    LL_SYSCTRL_DisableQEI2Fault(SYSCTRL);
}

/**
 * @brief  Judge is QEI2 Fault Enable or not
 * @retval 0 is Disable
 * @retval 1 is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsQEI2FaultEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsQEI2FaultEnable(SYSCTRL));
}

/**
 * @brief  QEI1 Fault Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableQEI1Fault(void)
{
    LL_SYSCTRL_EnableQEI1Fault(SYSCTRL);
}

/**
 * @brief  QEI1 Fault Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableQEI1Fault(void)
{
    LL_SYSCTRL_DisableQEI1Fault(SYSCTRL);
}

/**
 * @brief  Judge is QEI1 Fault Enable or not
 * @retval 0 is Disable
 * @retval 1 is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsQEI1FaultEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsQEI1FaultEnable(SYSCTRL));
}

/**
 * @brief  QEI0 Fault Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableQEI0Fault(void)
{
    LL_SYSCTRL_EnableQEI0Fault(SYSCTRL);
}

/**
 * @brief  QEI0 Fault Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableQEI0Fault(void)
{
    LL_SYSCTRL_DisableQEI0Fault(SYSCTRL);
}

/**
 * @brief  Judge is QEI0 Fault Enable or not
 * @retval 0 is Disable
 * @retval 1 is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsQEI0FaultEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsQEI0FaultEnable(SYSCTRL));
}

/**
 * @brief  XOSC Loss Fault Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableXOSCLossFault(void)
{
    LL_SYSCTRL_EnableXOSCLossFault(SYSCTRL);
}

/**
 * @brief  XOSC Loss Fault Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableXOSCLossFault(void)
{
    LL_SYSCTRL_DisableXOSCLossFault(SYSCTRL);
}

/**
 * @brief  Judge is XOSC Loss Fault Enable or not
 * @retval 0 is Disable
 * @retval 1 is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsXOSCLossFaultEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsXOSCLossFaultEnable(SYSCTRL));
}

/**
 * @brief  CPU Lockup Fault Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableCPULockupFault(void)
{
    LL_SYSCTRL_EnableCPULockupFault(SYSCTRL);
}

/**
 * @brief  CPU Lockup Fault Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableCPULockupFault(void)
{
    LL_SYSCTRL_DisableCPULockupFault(SYSCTRL);
}

/**
 * @brief  Judge is CPU Lockup Fault Enable or not
 * @retval 0 is Disable
 * @retval 1 is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsCPULockupFaultEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsCPULockupFaultEnable(SYSCTRL));
}

/**
 * @brief  FLASH nBits ECC Fault Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableNBitECCFault(void)
{
    LL_SYSCTRL_EnableNBitECCFault(SYSCTRL);
}

/**
 * @brief  FLASH nBits ECC Fault Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableNBitECCFault(void)
{
    LL_SYSCTRL_DisableNBitECCFault(SYSCTRL);
}

/**
 * @brief  Judge is CPU Lockup Fault Enable or not
 * @retval 0 is Disable
 * @retval 1 is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsNBitECCFaultEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsNBitECCFaultEnable(SYSCTRL));
}

/**
 * @brief  ADC Buffer Source Selection
 * @param  Src ADC Buffer Source 
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_SetADCBufferSource(HAL_SYSCTRL_ADCBufSrcTypeDef Src)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_ADC_BUF_SRC(Src));

    LL_SYSCTRL_SetADCBufferSource(SYSCTRL, Src);
}

/**
 * @brief  ADC Buffer Source Selection Get
 * @return ADC Buffer Source @ref HAL_SYSCTRL_ADCBufSrcTypeDef
 */
__STATIC_INLINE HAL_SYSCTRL_ADCBufSrcTypeDef HAL_SYSCTRL_GetADCBufferSource(void)
{
    return (HAL_SYSCTRL_ADCBufSrcTypeDef)(LL_SYSCTRL_GetADCBufferSource(SYSCTRL));
}

/**
 * @brief  ADC Buffer Bypass Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableADCBufferBypass(void)
{
    LL_SYSCTRL_EnableADCBufferBypass(SYSCTRL);
}

/**
 * @brief  ADC Buffer Bypass Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableADCBufferBypass(void)
{
    LL_SYSCTRL_DisableADCBufferBypass(SYSCTRL);
}

/**
 * @brief  Judge is ADC Buffer Bypass Enable or not
 * @retval 0 ADC Buffer Bypass is Disable
 * @retval 1 ADC Buffer Bypass is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsADCBufferBypassEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsADCBufferBypassEnable(SYSCTRL));
}

/**
 * @brief  ADC Buffer Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableADCBuffer(void)
{
    LL_SYSCTRL_EnableADCBuffer(SYSCTRL);
}

/**
 * @brief  Judge is ADC Buffer Enable or not
 * @retval 0 ADC Buffer is Disable
 * @retval 1 ADC Buffer is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsADCBufferEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsADCBufferEnable(SYSCTRL));
}

/**
  * @brief  SYSCTRL System Analog Config Set
  * @note   Unlock/Lock configuration @ref LL_SYSCTRL_UnlockSystemRegister/LL_SYSCTRL_LockSystemRegister 
  * @param  Val System Analog Config
  * @return None
  */
__STATIC_INLINE void HAL_SYSCTRL_SetSystemAnalogConfig(uint32_t Val)
{
    LL_SYSCTRL_SetSystemAnalogConfig(SYSCTRL, Val);
}

/**
  * @brief  SYSCTRL System Analog Config Get
  * @return System Analog Config
  */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetSystemAnalogConfig(void)
{
    return (uint32_t)(LL_SYSCTRL_GetSystemAnalogConfig(SYSCTRL));
}

/**
 * @brief  ADC Buffer Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableADCBuffer(void)
{
    LL_SYSCTRL_DisableADCBuffer(SYSCTRL);
}

/**
 * @brief  AVDD Drop Down Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVDD_EnableDropDown(void)
{
    LL_SYSCTRL_AVDD_EnableDropDown(SYSCTRL);
}

/**
 * @brief  AVDD Drop Down Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVDD_DisableDropDown(void)
{
    LL_SYSCTRL_AVDD_DisableDropDown(SYSCTRL);
}

/**
 * @brief  Judge is AVDD Drop Down Enable or not
 * @retval 0 AVDD Drop Down is Disable
 * @retval 1 AVDD Drop Down is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_AVDD_IsDropDownEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_AVDD_IsDropDownEnable(SYSCTRL));
}

/**
 * @brief  VDD Voltage Set
 * @param  Vol VDD Voltage @ref HAL_SYSCTRL_VDDVolTypeDef
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_SetVoltage(HAL_SYSCTRL_VDDVolTypeDef Vol)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_VDD_VOL(Vol));

    LL_SYSCTRL_VDD_SetVoltage(SYSCTRL, Vol);
}

/**
 * @brief  VDD Voltage Get
 * @return VDD Voltage @ref HAL_SYSCTRL_VDDVolTypeDef
 */
__STATIC_INLINE HAL_SYSCTRL_VDDVolTypeDef HAL_SYSCTRL_VDD_GetVoltage(void)
{
    return (HAL_SYSCTRL_VDDVolTypeDef)(LL_SYSCTRL_VDD_GetVoltage(SYSCTRL));
}

/**
 * @brief  AVDD Voltage Set
 * @param  Vol AVDD Voltage @ref HAL_SYSCTRL_AVDDVolTypeDef
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVDD_SetVoltage(HAL_SYSCTRL_AVDDVolTypeDef Vol)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_AVDD_VOL(Vol));

    LL_SYSCTRL_AVDD_SetVoltage(SYSCTRL, Vol);
}

/**
 * @brief  AVDD Voltage Get
 * @return AVDD Voltage @ref HAL_SYSCTRL_AVDDVolTypeDef
 */
__STATIC_INLINE HAL_SYSCTRL_AVDDVolTypeDef HAL_SYSCTRL_AVDD_GetVoltage(void)
{
    return (HAL_SYSCTRL_AVDDVolTypeDef)(LL_SYSCTRL_AVDD_GetVoltage(SYSCTRL));
}

/**
 * @brief  AVDD Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVDD_Enable(void)
{
    LL_SYSCTRL_AVDD_Enable(SYSCTRL);
}

/**
 * @brief  AVDD Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVDD_Disable(void)
{
    LL_SYSCTRL_AVDD_Disable(SYSCTRL);
}

/**
 * @brief  Judge is AVDD Enable or not
 * @retval 0 AVDD is Disable
 * @retval 1 AVDD is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_AVDD_IsEnabled(void)
{
    return (uint32_t)(LL_SYSCTRL_AVDD_IsEnabled(SYSCTRL));
}

/**
 * @brief  Temperature Sensor Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableTemperatureSensor(void)
{
    LL_SYSCTRL_EnableTemperatureSensor(SYSCTRL);
}

/**
 * @brief  Temperature Sensor Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_DisableTemperatureSensor(void)
{
    LL_SYSCTRL_DisableTemperatureSensor(SYSCTRL);
}

/**
 * @brief  Judge is Temperature Sensor Enable or not
 * @retval 0 Temperature Sensor is Disable
 * @retval 1 Temperature Sensor is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsTemperatureSensorEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsTemperatureSensorEnable(SYSCTRL));
}

/**
 * @brief  VDD Over Current Threshold Set
 * @param  Thres VDD Over Current Threshold @ref HAL_SYSCTRL_VDDOverCurThresTypeDef
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_SetOverCurrentThreshold(HAL_SYSCTRL_VDDOverCurThresTypeDef Thres)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_VDD_OVER_CUR_THRES(Thres));

    LL_SYSCTRL_VDD_SetOverCurrentThreshold(SYSCTRL, Thres);
}

/**
 * @brief  VDD Over Current Threshold Get
 * @return VDD Over Current Threshold @ref HAL_SYSCTRL_VDDOverCurThresTypeDef
 */
__STATIC_INLINE HAL_SYSCTRL_VDDOverCurThresTypeDef HAL_SYSCTRL_VDD_GetOverCurrentThreshold(void)
{
    return (HAL_SYSCTRL_VDDOverCurThresTypeDef)(LL_SYSCTRL_VDD_GetOverCurrentThreshold(SYSCTRL));
}

/**
 * @brief  AVCC Low Voltage Threshold Set
 * @param  Thres AVCC Low Voltage Threshold @ref HAL_SYSCTRL_AVCCLowVolThresTypeDef
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVCC_SetLowVoltageThreshold(HAL_SYSCTRL_AVCCLowVolThresTypeDef Thres)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_AVCC_LOW_VOL_THRES(Thres));
    
    LL_SYSCTRL_AVCC_SetLowVoltageThreshold(SYSCTRL, Thres);
}

/**
 * @brief  AVCC Low Voltage Threshold Get
 * @return AVCC Low Voltage Threshold @ref HAL_SYSCTRL_AVCCLowVolThresTypeDef
 */
__STATIC_INLINE HAL_SYSCTRL_AVCCLowVolThresTypeDef HAL_SYSCTRL_AVCC_GetLowVoltageThreshold(void)
{
    return (HAL_SYSCTRL_AVCCLowVolThresTypeDef)(LL_SYSCTRL_AVCC_GetLowVoltageThreshold(SYSCTRL));
}

/**
 * @brief  VDD Low Voltage Threshold Set
 * @param  Thres VDD Low Voltage Threshold @ref HAL_SYSCTRL_VDDLowVolThresTypeDef
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_SetLowVoltageThreshold(HAL_SYSCTRL_VDDLowVolThresTypeDef Thres)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_VDD_LOW_VOL_THRES(Thres));

    LL_SYSCTRL_VDD_SetLowVoltageThreshold(SYSCTRL, Thres);
}

/**
 * @brief  VDD Low Voltage Threshold Get
 * @return VDD Low Voltage Threshold @ref HAL_SYSCTRL_VDDLowVolThresTypeDef
 */
__STATIC_INLINE HAL_SYSCTRL_VDDLowVolThresTypeDef HAL_SYSCTRL_VDD_GetLowVoltageThreshold(void)
{
    return (HAL_SYSCTRL_VDDLowVolThresTypeDef)(LL_SYSCTRL_VDD_GetLowVoltageThreshold(SYSCTRL));
}

/**
 * @brief  VDD Over Current Detect Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_EnableOverCurrentDetect(void)
{
    LL_SYSCTRL_VDD_EnableOverCurrentDetect(SYSCTRL);
}

/**
 * @brief  VDD Over Current Detect Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_DisableOverCurrentDetect(void)
{
    LL_SYSCTRL_VDD_DisableOverCurrentDetect(SYSCTRL);
}

/**
 * @brief   Judgs is VDD Over Current Detect Enable or not
 * @retval 0 VDD Over Current Detect is Disable
 * @retval 1 VDD Over Current Detect is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsOverCurrentDetectEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsOverCurrentDetectEnable(SYSCTRL));
}

/**
 * @brief  AVCC Low Voltage Detect Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVCC_EnableLowVoltageDetect(void)
{
    LL_SYSCTRL_AVCC_EnableLowVoltageDetect(SYSCTRL);
}

/**
 * @brief  AVCC Low Voltage Detect Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVCC_DisableLowVoltageDetect(void)
{
    LL_SYSCTRL_AVCC_DisableLowVoltageDetect(SYSCTRL);
}

/**
 * @brief   Judgs is AVCC Low Voltage Detect Enable or not
 * @retval 0 AVCC Low Voltage Detect is Disable
 * @retval 1 AVCC Low Voltage Detect is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_AVCC_IsLowVoltageDetectEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_AVCC_IsLowVoltageDetectEnable(SYSCTRL));
}

/**
 * @brief  VCC Low Voltage Detect Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VCC_EnableLowVoltageDetect(void)
{
    LL_SYSCTRL_VCC_EnableLowVoltageDetect(SYSCTRL);
}

/**
 * @brief  VCC Low Voltage Detect Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VCC_DisableLowVoltageDetect(void)
{
    LL_SYSCTRL_VCC_DisableLowVoltageDetect(SYSCTRL);
}

/**
 * @brief   Judgs is VCC Low Voltage Detect Enable or not
 * @retval 0 VCC Low Voltage Detect is Disable
 * @retval 1 VCC Low Voltage Detect is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VCC_IsLowVoltageDetectEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VCC_IsLowVoltageDetectEnable(SYSCTRL));
}

/**
 * @brief  VDD Low Voltage Detect Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_EnableLowVoltageDetect(void)
{
    LL_SYSCTRL_VDD_EnableLowVoltageDetect(SYSCTRL);
}

/**
 * @brief  VDD Low Voltage Detect Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_DisableLowVoltageDetect(void)
{
    LL_SYSCTRL_VDD_DisableLowVoltageDetect(SYSCTRL);
}

/**
 * @brief   Judgs is VDD Low Voltage Detect Enable or not
 * @retval 0 VDD Low Voltage Detect is Disable
 * @retval 1 VDD Low Voltage Detect is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsLowVoltageDetectEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsLowVoltageDetectEnable(SYSCTRL));
}

/**
 * @brief  VDD Over Current Braking Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_EnableOverCurrentBrake(void)
{
    LL_SYSCTRL_VDD_EnableOverCurrentBrake(SYSCTRL);
}

/**
 * @brief  VDD Over Current Braking Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_DisableOverCurrentBrake(void)
{
    LL_SYSCTRL_VDD_DisableOverCurrentBrake(SYSCTRL);
}

/**
 * @brief  Judge is VDD Over Current Braking Enable or not
 * @retval 0 VDD Over Current Braking is Disable
 * @retval 1 VDD Over Current Braking is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsOverCurrentBrakeEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsOverCurrentBrakeEnable(SYSCTRL));
}

/**
 * @brief  AVCC Low Voltage Braking Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVCC_EnableLowVoltageBrake(void)
{
    LL_SYSCTRL_AVCC_EnableLowVoltageBrake(SYSCTRL);
}

/**
 * @brief  AVCC Low Voltage Braking Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVCC_DisableLowVoltageBrake(void)
{
    LL_SYSCTRL_AVCC_DisableLowVoltageBrake(SYSCTRL);
}

/**
 * @brief  Judge is AVCC Low Voltage Braking Enable or not
 * @retval 0 AVCC Low Voltage Braking is Disable
 * @retval 1 AVCC Low Voltage Braking is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_AVCC_IsLowVoltageBrakeEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_AVCC_IsLowVoltageBrakeEnable(SYSCTRL));
}

/**
 * @brief  VCC Low Voltage Braking Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VCC_EnableLowVoltageBrake(void)
{
    LL_SYSCTRL_VCC_EnableLowVoltageBrake(SYSCTRL);
}

/**
 * @brief  VCC Low Voltage Braking Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VCC_DisableLowVoltageBrake(void)
{
    LL_SYSCTRL_VCC_DisableLowVoltageBrake(SYSCTRL);
}

/**
 * @brief  Judge is VCC Low Voltage Braking Enable or not
 * @retval 0 VCC Low Voltage Braking is Disable
 * @retval 1 VCC Low Voltage Braking is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VCC_IsLowVoltageBrakeEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VCC_IsLowVoltageBrakeEnable(SYSCTRL));
}

/**
 * @brief  VDD Low Voltage Braking Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_EnableLowVoltageBrake(void)
{
    LL_SYSCTRL_VDD_EnableLowVoltageBrake(SYSCTRL);
}

/**
 * @brief  VDD Low Voltage Braking Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_DisableLowVoltageBrake(void)
{
    LL_SYSCTRL_VDD_DisableLowVoltageBrake(SYSCTRL);
}

/**
 * @brief  Judge is VDD Low Voltage Braking Enable or not
 * @retval 0 VDD Low Voltage Braking is Disable
 * @retval 1 VDD Low Voltage Braking is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsLowVoltageBrakeEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsLowVoltageBrakeEnable(SYSCTRL));
}

/**
 * @brief  VDD Over Current Reset Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_EnableOverCurrentReset(void)
{
    LL_SYSCTRL_VDD_EnableOverCurrentReset(SYSCTRL);
}

/**
 * @brief  VDD Over Current Reset Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_DisableOverCurrentReset(void)
{
    LL_SYSCTRL_VDD_DisableOverCurrentReset(SYSCTRL);
}

/**
 * @brief  Judge is VDD Over Current Reset Enable or not
 * @retval 0 VDD Over Current Reset is Disable
 * @retval 1 VDD Over Current Reset is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsOverCurrentResetEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsOverCurrentResetEnable(SYSCTRL));
}

/**
 * @brief  AVCC Low Voltage Reset Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVCC_EnableLowVoltageReset(void)
{
    LL_SYSCTRL_AVCC_EnableLowVoltageReset(SYSCTRL);
}

/**
 * @brief  AVCC Low Voltage Reset Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_AVCC_DisableLowVoltageReset(void)
{
    LL_SYSCTRL_AVCC_DisableLowVoltageReset(SYSCTRL);
}

/**
 * @brief  Judge is AVCC Low Voltage Reset Enable or not
 * @retval 0 AVCC Low Voltage Reset is Disable
 * @retval 1 AVCC Low Voltage Reset is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_AVCC_IsLowVoltageResetEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_AVCC_IsLowVoltageResetEnable(SYSCTRL));
}

/**
 * @brief  VCC Low Voltage Reset Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VCC_EnableLowVoltageReset(void)
{
    LL_SYSCTRL_VCC_EnableLowVoltageReset(SYSCTRL);
}

/**
 * @brief  VCC Low Voltage Reset Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VCC_DisableLowVoltageReset(void)
{
    LL_SYSCTRL_VCC_DisableLowVoltageReset(SYSCTRL);
}

/**
 * @brief  Judge is VCC Low Voltage Reset Enable or not
 * @retval 0 VCC Low Voltage Reset is Disable
 * @retval 1 VCC Low Voltage Reset is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VCC_IsLowVoltageResetEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VCC_IsLowVoltageResetEnable(SYSCTRL));
}

/**
 * @brief  VDD Low Voltage Reset Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_EnableLowVoltageReset(void)
{
    LL_SYSCTRL_VDD_EnableLowVoltageReset(SYSCTRL);
}

/**
 * @brief  VDD Low Voltage Reset Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VDD_DisableLowVoltageReset(void)
{
    LL_SYSCTRL_VDD_DisableLowVoltageReset(SYSCTRL);
}

/**
 * @brief  Judge is VDD Low Voltage Reset Enable or not
 * @retval 0 VDD Low Voltage Reset is Disable
 * @retval 1 VDD Low Voltage Reset is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsLowVoltageResetEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsLowVoltageResetEnable(SYSCTRL));
}

/**
 * @brief  Judge is VDD Over Current or not
 * @retval 0 VDD isn't Over Current
 * @retval 1 VDD is Over Current
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsOverCurrentActived(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsOverCurrentActived(SYSCTRL));
}

/**
 * @brief  Judge is AVCC Low Voltage or not
 * @retval 0 AVCC isn't Low Voltage
 * @retval 1 AVCC is Low Voltage
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_AVCC_IsLowVoltageActived(void)
{
    return (uint32_t)(LL_SYSCTRL_AVCC_IsLowVoltageActived(SYSCTRL));
}

/**
 * @brief  Judge is VCC Low Voltage or not
 * @retval 0 VCC isn't Low Voltage
 * @retval 1 VCC is Low Voltage
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VCC_IsLowVoltageActived(void)
{
    return (uint32_t)(LL_SYSCTRL_VCC_IsLowVoltageActived(SYSCTRL));
}

/**
 * @brief  Judge is VDD Low Voltage or not
 * @retval 0 VDD isn't Low Voltage
 * @retval 1 VDD is Low Voltage
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VDD_IsLowVoltageActived(void)
{
    return (uint32_t)(LL_SYSCTRL_VDD_IsLowVoltageActived(SYSCTRL));
}

/**
 * @brief  SYSCTRL Chip ID Get
 * @retval Chip ID - 16bit
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetChipID(void)
{
    return (uint32_t)(LL_SYSCTRL_GetChipID(SYSCTRL));
}

/**
 * @brief  SYSCTRL Chip DCN Get
 * @retval Chip DCN - 8bit
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetChipDCN(void)
{
    return (uint32_t)(LL_SYSCTRL_GetChipDCN(SYSCTRL));
}

/**
 * @brief  SYSCTRL System Register Write Unlock
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_UnlockSystemRegister(void)
{
    LL_SYSCTRL_UnlockSystemRegister(SYSCTRL);
}

/**
 * @brief  SYSCTRL System Register Write Lock
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_LockSystemRegister(void)
{
    LL_SYSCTRL_LockSystemRegister(SYSCTRL);
}

/**
 * @brief  SYSCTRL Special Register Write Unlock
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_UnlockSpecialRegister(void)
{
    LL_SYSCTRL_UnlockSpecialRegister(SYSCTRL);
}

/**
 * @brief  SYSCTRL Special Register Write Lock
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_LockSpecialRegister(void)
{
    LL_SYSCTRL_LockSpecialRegister(SYSCTRL);
}

/**
 * @brief  SYSCTRL UID0 Get
 * @retval UID0
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetUID0(void)
{
    return (uint32_t)(LL_SYSCTRL_GetUID0(SYSCTRL));
}

/**
 * @brief  SYSCTRL UID1 Get
 * @retval UID1
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetUID1(void)
{
    return (uint32_t)(LL_SYSCTRL_GetUID1(SYSCTRL));
}

/**
 * @brief  SYSCTRL UID2 Get
 * @retval UID2
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetUID2(void)
{
    return (uint32_t)(LL_SYSCTRL_GetUID2(SYSCTRL));
}

/**
 * @brief  SYSCTRL UID3 Get
 * @retval UID3
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetUID3(void)
{
    return (uint32_t)(LL_SYSCTRL_GetUID3(SYSCTRL));
}

/**
 * @brief  SYSCTRL EFLASH Size Get
 * @retval EFLASH Size in KByte unit
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetEFlashSize(void)
{
    return (uint32_t)(LL_SYSCTRL_GetEFlashSize(SYSCTRL));
}

/**
  * @brief  SYSCTRL internal BGR voltage Get
  * @return Internal BGR voltage
  */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetInternalBGRVoltage(void)
{
    return (uint32_t)(LL_SYSCTRL_GetInternalBGRVoltage(SYSCTRL));
}

/**
 * @brief  SYSCTRL VREFBUF Output Voltage Status Get
 * @retval 0 VREFBUF Output is building
 * @retval 1 VREFBUF Output is done
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VREFBUF_IsOutputVoltageBuilt(void)
{
    return (uint32_t)(LL_SYSCTRL_VREFBUF_IsOutputVoltageBuilt(SYSCTRL));
}

/**
 * @brief  SYSCTRL VREFBUF Current Limiting Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VREFBUF_EnableCurrentLimiting(void)
{
    LL_SYSCTRL_VREFBUF_EnableCurrentLimiting(SYSCTRL);
}

/**
 * @brief  SYSCTRL VREFBUF Current Limiting Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VREFBUF_DisableCurrentLimiting(void)
{
    LL_SYSCTRL_VREFBUF_DisableCurrentLimiting(SYSCTRL);
}

/**
 * @brief  Judge is SYSCTRL VREFBUF Current Limiting Enable or not
 * @retval 0 Current Limiting is disable
 * @retval 1 Current Limiting is enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_VREFBUF_IsCurrentLimitingEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_VREFBUF_IsCurrentLimitingEnable(SYSCTRL));
}

/**
 * @brief  SYSCTRL VREFBUF Output Voltage Set
 * @param  Vol VREFBUF Output Voltage
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VREFBUF_SetOutputVoltage(HAL_SYSCTRL_VrefBufVolTypeDef Vol)
{
    ASSERT_INLINE_PARAM(IS_LL_SYSCTRL_VREFBUF_VOL(Vol));

    LL_SYSCTRL_VREFBUF_SetOutputVoltage(SYSCTRL, Vol);
}

/**
 * @brief  SYSCTRL VREFBUF Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VREFBUF_Enable(void)
{
    LL_SYSCTRL_VREFBUF_Enable(SYSCTRL);
}

/**
 * @brief  SYSCTRL VREFBUF Disable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_VREFBUF_Disable(void)
{
    LL_SYSCTRL_VREFBUF_Disable(SYSCTRL);
}

/**
  * @brief  SYSCTRL REF Reference Current Calibration Get
  * @return REF Reference Current
  */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetReferenceCurrent(void)
{
    return (uint32_t)(LL_SYSCTRL_GetReferenceCurrent(SYSCTRL));
}

/**
  * @brief  SYSCTRL REF Reference Voltage Calibration Get
  * @return REF Reference Voltage
  */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetReferenceVoltage(void)
{
    return (uint32_t)(LL_SYSCTRL_GetReferenceVoltage(SYSCTRL));
}

/**
  * @brief  SYSCTRL Analog Trim Config Set
  * @note   Unlock/Lock configuration @ref HAL_SYSCTRL_UnlockSpecialRegister/HAL_SYSCTRL_LockSpecialRegister 
  * @param  Val Analog Trim Config
  * @return None
  */
__STATIC_INLINE void HAL_SYSCTRL_SetAnalogTrimConfig(uint32_t Val)
{
    LL_SYSCTRL_SetAnalogTrimConfig(SYSCTRL, Val);
}

/**
  * @brief  SYSCTRL Analog Trim Config Get
  * @return Analog Trim Config
  */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetAnalogTrimConfig(void)
{
    return (uint32_t)(LL_SYSCTRL_GetAnalogTrimConfig(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC8M Real Value Get
 * @return RC8M Real Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetRealFrequency(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetRealFrequency(SYSCTRL));
}

/**
 * @brief  Judge is SYSCTRL ADC Conversion Phase Clock Enable or not
 * @retval 0 ADC Conversion Phase Clock isn't Enable
 * @retval 1 ADC Conversion Phase Clock is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsADCConversionPhaseClockEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsADCConversionPhaseClockEnable(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC8M PLL0CLK Output 180MHz Band Value Get
 * @note   This band value is only used for typical scene which PLL0 analog output 360M
 * @return RC8M PLL0 Band Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetBandForPLL0CLK180MHz(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetBandForPLL0CLK180MHz(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC8M PLL0CLK Output 200MHz Band Value Get
 * @note   This band value is only used for typical scene which PLL0 analog output 400M
 * @return RC8M PLL0 Band Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetBandForPLL0CLK200MHz(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetBandForPLL0CLK200MHz(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC8M PLL0CLK Output 180MHz INT Value Get
 * @return RC8M PLL0 INT Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetINTForPLL0CLK180MHz(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetINTForPLL0CLK180MHz(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC8M PLL0CLK Output 180MHz FRAC Value Get
 * @return RC8M PLL0 FRAC Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetFRACForPLL0CLK180MHz(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetFRACForPLL0CLK180MHz(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC8M PLL0CLK Output 200MHz INT Value Get
 * @return RC8M PLL0 INT Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetINTForPLL0CLK200MHz(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetINTForPLL0CLK200MHz(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC8M PLL0CLK Output 200MHz FRAC Value Get
 * @return RC8M PLL0 FRAC Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetFRACForPLL0CLK200MHz(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetFRACForPLL0CLK200MHz(SYSCTRL));
}

/**
 * @brief  SYSCTRL RC32K Real Value Get
 * @return RC32K Real Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC32K_GetRealFrequency(void)
{
    return (uint32_t)(LL_SYSCTRL_RC32K_GetRealFrequency(SYSCTRL));
}


/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the PLL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
__STATIC_INLINE uint32_t HAL_SYSCTRL_HSI_GetValue(void)
{
    return LL_SYSCTRL_HSI_GetValue();
}

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  *        Defines the value of the Internal Low Speed oscillator in Hz.
  * @note  The real value may vary depending on the variations in voltage and temperature.
  */ 
__STATIC_INLINE uint32_t HAL_SYSCTRL_LSI_GetValue(void)
{
    return LL_SYSCTRL_LSI_GetValue();
}

/**
  * @}
  */ /* SYSCTRL_HAL_EF_Inline_Configuration */


/** @addtogroup SYSCTRL_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_SYSCTRL_PowerMonitorConfig(HAL_SYSCTRL_PowerDetectTypeDef *pCfg);
HAL_StatusTypeDef HAL_SYSCTRL_VrefBufferOutputConfig(HAL_SYSCTRL_VrefBufOutputTypeDef *pCfg);
HAL_StatusTypeDef HAL_SYSCTRL_ADCBufferConfig(HAL_SYSCTRL_ADCBufTypeDef *pCfg);
/**
  * @}
  */ /* SYSCTRL_HAL_EF_Configuration */


/** @addtogroup SYSCTRL_HAL_EF_Interrupt
  * @{
  */

HAL_StatusTypeDef HAL_SYSCTRL_InterruptRequestEnable(HAL_SYSCTRL_ITEnMskTypeDef InterruptRequests);
HAL_StatusTypeDef HAL_SYSCTRL_InterruptRequestDisable(HAL_SYSCTRL_ITEnMskTypeDef InterruptRequests);

void HAL_SYSCTRL_IRQHandler(void);

void HAL_SYSCTRL_VDDOverCurCallback(SYSCTRL_TypeDef *Instance);
void HAL_SYSCTRL_VDDLowVolCallback(SYSCTRL_TypeDef *Instance);
void HAL_SYSCTRL_VCCLowVolCallback(SYSCTRL_TypeDef *Instance);
void HAL_SYSCTRL_AVCCLowVolCallback(SYSCTRL_TypeDef *Instance);
/**
  * @}
  */ /* SYSCTRL_HAL_EF_Interrupt */

/**
  * @}
  */ /* SYSCTRL_HAL_Exported_Functions */

/**
  * @}
  */ /* SYSCTRL_HAL */

#endif /* SYSCTRL */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_SYSCTRL_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

