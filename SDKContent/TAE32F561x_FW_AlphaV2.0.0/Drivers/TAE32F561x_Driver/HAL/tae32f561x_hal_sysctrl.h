/**
  ******************************************************************************
  * @file    tae32f561x_hal_sysctrl.h
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
#ifndef _TAE32F561X_HAL_SYSCTRL_H_
#define _TAE32F561X_HAL_SYSCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_hal_def.h"
#include "tae32f561x_ll_sysctrl.h"


/** @addtogroup TAE32F561X_HAL_Driver
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

/**
  * @brief SYSCTRL Interrupt Enable Mask Definition
  */
#define HAL_SYSCTRL_ITEnMskTypeDef                          LL_SYSCTRL_PECR_ITEnMskTypeDef


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
  * @brief SYSCTRL ADC Buffer Source Definition
  */
typedef enum {
    HAL_SYSCTRL_ADC_BUF_SRC_AVSS       = LL_SYSCTRL_ADC_BUF_SRC_AVSS,        /*!< ADC Buffer Source AVSS         */
    HAL_SYSCTRL_ADC_BUF_SRC_TSENSOR    = LL_SYSCTRL_ADC_BUF_SRC_TSENSOR,     /*!< ADC Buffer Source Temp SENSOR  */
    HAL_SYSCTRL_ADC_BUF_SRC_VBGR       = LL_SYSCTRL_ADC_BUF_SRC_VBGR,        /*!< ADC Buffer Source VBGR         */
    HAL_SYSCTRL_ADC_BUF_SRC_VR1P2      = LL_SYSCTRL_ADC_BUF_SRC_VR1P2,       /*!< ADC Buffer Source VR1P2        */
} HAL_SYSCTRL_ADCBufSrcTypeDef;

/**
  * @brief SYSCTRL VDD Voltage Definition
  */
typedef enum {
    HAL_SYSCTRL_VDD_VOL_0V88           = LL_SYSCTRL_VDD_VOL_0V88,            /*!< VDD Voltage 0.88V  */
    HAL_SYSCTRL_VDD_VOL_0V92           = LL_SYSCTRL_VDD_VOL_0V92,            /*!< VDD Voltage 0.92V  */
    HAL_SYSCTRL_VDD_VOL_0V96           = LL_SYSCTRL_VDD_VOL_0V96,            /*!< VDD Voltage 0.96V  */
    HAL_SYSCTRL_VDD_VOL_1V             = LL_SYSCTRL_VDD_VOL_1V,              /*!< VDD Voltage 1V     */
    HAL_SYSCTRL_VDD_VOL_1V04           = LL_SYSCTRL_VDD_VOL_1V04,            /*!< VDD Voltage 1.04V  */
    HAL_SYSCTRL_VDD_VOL_1V08           = LL_SYSCTRL_VDD_VOL_1V08,            /*!< VDD Voltage 1.08V  */
    HAL_SYSCTRL_VDD_VOL_1V12           = LL_SYSCTRL_VDD_VOL_1V12,            /*!< VDD Voltage 1.12V  */
    HAL_SYSCTRL_VDD_VOL_1V16           = LL_SYSCTRL_VDD_VOL_1V16,            /*!< VDD Voltage 1.16V  */
    HAL_SYSCTRL_VDD_VOL_1V2            = LL_SYSCTRL_VDD_VOL_1V2,             /*!< VDD Voltage 1.20V  */
    HAL_SYSCTRL_VDD_VOL_1V24           = LL_SYSCTRL_VDD_VOL_1V24,            /*!< VDD Voltage 1.24V  */
    HAL_SYSCTRL_VDD_VOL_1V28           = LL_SYSCTRL_VDD_VOL_1V28,            /*!< VDD Voltage 1.28V  */
    HAL_SYSCTRL_VDD_VOL_1V32           = LL_SYSCTRL_VDD_VOL_1V32,            /*!< VDD Voltage 1.32V  */
    HAL_SYSCTRL_VDD_VOL_1V36           = LL_SYSCTRL_VDD_VOL_1V36,            /*!< VDD Voltage 1.36V  */
    HAL_SYSCTRL_VDD_VOL_1V4            = LL_SYSCTRL_VDD_VOL_1V4,             /*!< VDD Voltage 1.40V  */
    HAL_SYSCTRL_VDD_VOL_1V44           = LL_SYSCTRL_VDD_VOL_1V44,            /*!< VDD Voltage 1.44V  */
    HAL_SYSCTRL_VDD_VOL_1V48           = LL_SYSCTRL_VDD_VOL_1V48,            /*!< VDD Voltage 1.48V  */
} HAL_SYSCTRL_VDDVolTypeDef;

/**
  * @brief SYSCTRL AVDD Voltage Definition
  */
typedef enum {
    HAL_SYSCTRL_AVDD_VOL_1V            = LL_SYSCTRL_AVDD_VOL_1V,             /*!< AVDD Voltage 1V    */
    HAL_SYSCTRL_AVDD_VOL_1V1           = LL_SYSCTRL_AVDD_VOL_1V1,            /*!< AVDD Voltage 1.1V  */
    HAL_SYSCTRL_AVDD_VOL_1V2           = LL_SYSCTRL_AVDD_VOL_1V2,            /*!< AVDD Voltage 1.2V  */
    HAL_SYSCTRL_AVDD_VOL_1V3           = LL_SYSCTRL_AVDD_VOL_1V3,            /*!< AVDD Voltage 1.3V  */
} HAL_SYSCTRL_AVDDVolTypeDef;

/**
  * @brief SYSCTRL VDD OverCurrent Threshold Definition
  */
typedef enum {
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_150mA = LL_SYSCTRL_VDD_OVER_CUR_THRES_150mA,  /*!< VDD OverCurrent Threshold 150mA    */
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_175mA = LL_SYSCTRL_VDD_OVER_CUR_THRES_175mA,  /*!< VDD OverCurrent Threshold 175mA    */
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_200mA = LL_SYSCTRL_VDD_OVER_CUR_THRES_200mA,  /*!< VDD OverCurrent Threshold 200mA    */
    HAL_SYSCTRL_VDD_OVER_CUR_THRES_225mA = LL_SYSCTRL_VDD_OVER_CUR_THRES_225mA,  /*!< VDD OverCurrent Threshold 225mA    */
} HAL_SYSCTRL_VDDOverCurThresTypeDef;

/**
  * @brief SYSCTRL AVCC LowVoltage Threshold Definition
  */
typedef enum {
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_2V55  = LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V55,   /*!< AVCC LowVoltage Threshold 2.55V    */
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_2V7   = LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V7,    /*!< AVCC LowVoltage Threshold 2.7V     */
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_2V85  = LL_SYSCTRL_AVCC_LOW_VOL_THRES_2V85,   /*!< AVCC LowVoltage Threshold 2.85V    */
    HAL_SYSCTRL_AVCC_LOW_VOL_THRES_3V    = LL_SYSCTRL_AVCC_LOW_VOL_THRES_3V,     /*!< AVCC LowVoltage Threshold 3V       */
} HAL_SYSCTRL_AVCCLowVolThresTypeDef;

/**
  * @brief SYSCTRL VDD LowVoltage Threshold Definition
  */
typedef enum {
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V75   = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V75,    /*!< VDD LowVoltage Threshold 0.75V     */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V8    = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V8,     /*!< VDD LowVoltage Threshold 0.8V      */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V85   = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V85,    /*!< VDD LowVoltage Threshold 0.85V     */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V9    = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V9,     /*!< VDD LowVoltage Threshold 0.9V      */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_0V95   = LL_SYSCTRL_VDD_LOW_VOL_THRES_0V95,    /*!< VDD LowVoltage Threshold 0.95V     */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_1V     = LL_SYSCTRL_VDD_LOW_VOL_THRES_1V,      /*!< VDD LowVoltage Threshold 1.0V      */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_1V05   = LL_SYSCTRL_VDD_LOW_VOL_THRES_1V05,    /*!< VDD LowVoltage Threshold 1.05V     */
    HAL_SYSCTRL_VDD_LOW_VOL_THRES_1V1    = LL_SYSCTRL_VDD_LOW_VOL_THRES_1V1,     /*!< VDD LowVoltage Threshold 1.1V      */
} HAL_SYSCTRL_VDDLowVolThresTypeDef;

/**
  * @brief SYSCTRL VREFBUF Output Voltage Definition
  */
typedef enum {
    HAL_SYSCTRL_VREFBUF_VOL_2V9        = LL_SYSCTRL_VREFBUF_VOL_2V9,          /* VREFBUF Output Voltage 2.9V  */
    HAL_SYSCTRL_VREFBUF_VOL_2V5        = LL_SYSCTRL_VREFBUF_VOL_2V5,          /* VREFBUF Output Voltage 2.5V  */
} HAL_SYSCTRL_VREFBUFVolTypeDef;

/**
  * @brief SYSCTRL Flash Double Bank Mapping Definition
  */
typedef enum {
    HAL_SYSCTRL_FLASH_BANK_MAPPING_0   = LL_SYSCTRL_FLASH_BANK_MAPPING_0,     /* Flash Bank Mapping type 0 */
    HAL_SYSCTRL_FLASH_BANK_MAPPING_1   = LL_SYSCTRL_FLASH_BANK_MAPPING_1,     /* Flash Bank Mapping type 1 */
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
  * @brief SYSCTRL ADC Buffer Type Definition
  */
typedef struct 
{
    HAL_SYSCTRL_ADCBufSrcTypeDef    BufferSource;
    HAL_SYSCTRL_EnableTypeDef       BufferBypass;
    HAL_SYSCTRL_EnableTypeDef       BufferEnable;
} HAL_SYSCTRL_ADCBufTypeDef;

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
 * @brief  ADC Buffer Enable
 * @return None
 */
__STATIC_INLINE void HAL_SYSCTRL_EnableADCBuffer(void)
{
    LL_SYSCTRL_EnableADCBuffer(SYSCTRL);
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
 * @brief  Judge is ADC Buffer Enable or not
 * @retval 0 ADC Buffer is Disable
 * @retval 1 ADC Buffer is Enable
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_IsADCBufferEnable(void)
{
    return (uint32_t)(LL_SYSCTRL_IsADCBufferEnable(SYSCTRL));
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
 * @brief  SYSCTRL RC8M PLL0CLK Output 160MHz Band Value Get
 * @note   This band value is only used for typical scene which PLL0 analog output 360M
 * @return RC8M PLL0 Band Value
 */
__STATIC_INLINE uint32_t HAL_SYSCTRL_RC8M_GetBandForPLL0CLK160MHz(void)
{
    return (uint32_t)(LL_SYSCTRL_RC8M_GetBandForPLLCLK160MHz(SYSCTRL));
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
  * @brief  SYSCTRL System Analog Config Get
  * @return System Analog Config
  */
__STATIC_INLINE uint32_t HAL_SYSCTRL_GetSystemAnalogConfig(void)
{
    return (uint32_t)(LL_SYSCTRL_GetSystemAnalogConfig(SYSCTRL));
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
  * @brief  SYSCTRL Analog Trim Config Set
  * @note   Unlock/Lock configuration @ref HAL_SYSCTRL_UnlockSpecialRegister/HAL_SYSCTRL_LockSpecialRegister 
  * @param  Val Analog Trim Config
  * @return None
  */
__STATIC_INLINE void HAL_SYSCTRL_SetAnalogTrimConfig(uint32_t Val)
{
    LL_SYSCTRL_SetAnalogTrimConfig(SYSCTRL, Val);
}


void HAL_SYSCTRL_VDDOverCurCallback(SYSCTRL_TypeDef *Instance);
void HAL_SYSCTRL_VDDLowVolCallback(SYSCTRL_TypeDef *Instance);
void HAL_SYSCTRL_VCCLowVolCallback(SYSCTRL_TypeDef *Instance);
void HAL_SYSCTRL_AVCCLowVolCallback(SYSCTRL_TypeDef *Instance);


#define LL_ADC_CH_0                                 (0UL)                /*!< ADC Channel 0                                    */
#define LL_ADC_CH_1                                 (1UL)                /*!< ADC Channel 1                                    */
#define LL_ADC_CH_2                                 (2UL)                /*!< ADC Channel 2                                    */
#define LL_ADC_CH_3                                 (3UL)                /*!< ADC Channel 3                                    */
#define LL_ADC_CH_4                                 (4UL)                /*!< ADC Channel 4                                    */
#define LL_ADC_CH_5                                 (5UL)                /*!< ADC Channel 5                                    */
#define LL_ADC_CH_6                                 (6UL)                /*!< ADC Channel 6                                    */
#define LL_ADC_CH_7                                 (7UL)                /*!< ADC Channel 7                                    */
#define LL_ADC_CH_8                                 (8UL)                /*!< ADC Channel 8                                    */
#define LL_ADC_CH_9                                 (9UL)                /*!< ADC Channel 9                                    */
#define LL_ADC_CH_10                                (10UL)               /*!< ADC Channel 10                                   */
#define LL_ADC_CH_11                                (11UL)               /*!< ADC Channel 11                                   */
#define LL_ADC_CH_12                                (12UL)               /*!< ADC Channel 12                                   */
#define LL_ADC_CH_13                                (13UL)               /*!< ADC Channel 13                                   */
#define LL_ADC_CH_14                                (14UL)               /*!< ADC Channel 14                                   */
#define LL_ADC_CH_15                                (15UL)               /*!< ADC Channel 15                                   */

#define LL_ADC_CH_NUMS                              (16UL)               /*!< ADC Ch Nums                                      */

#define IS_LL_ADC_CH(__VAL__)                       (((__VAL__) == LL_ADC_CH_0)    || \
                                                     ((__VAL__) == LL_ADC_CH_1)    || \
                                                     ((__VAL__) == LL_ADC_CH_2)    || \
                                                     ((__VAL__) == LL_ADC_CH_3)    || \
                                                     ((__VAL__) == LL_ADC_CH_4)    || \
                                                     ((__VAL__) == LL_ADC_CH_5)    || \
                                                     ((__VAL__) == LL_ADC_CH_6)    || \
                                                     ((__VAL__) == LL_ADC_CH_7)    || \
                                                     ((__VAL__) == LL_ADC_CH_8)    || \
                                                     ((__VAL__) == LL_ADC_CH_9)    || \
                                                     ((__VAL__) == LL_ADC_CH_10)   || \
                                                     ((__VAL__) == LL_ADC_CH_11)   || \
                                                     ((__VAL__) == LL_ADC_CH_12)   || \
                                                     ((__VAL__) == LL_ADC_CH_13)   || \
                                                     ((__VAL__) == LL_ADC_CH_14)   || \
                                                     ((__VAL__) == LL_ADC_CH_15))

/** @} */


//TODO: below need to be added in ADC

/**
  * @brief  ADC Enable
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADEN_Msk);
}

/**
  * @brief  Regular Conversion Start
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_StartConversion(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADSTART_Msk);
}

/**
  * @brief  Regular Conversion Stop
  * @param  ADCx Specifies ADC peripheral
  * @return None
  */
__STATIC_INLINE void LL_ADC_REG_StopConversion(ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    SET_BIT(ADCx->CR, ADC0_CR_ADSTP_Msk);
}

/**
  * @brief  Regular Sequence Data Read
  * @param  ADCx Specifies ADC peripheral
  * @return Regular Sequence Data
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadConversionData(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->DR, ADC0_DR_RDATA_Msk, ADC0_DR_RDATA_Pos));
}

/**
  * @brief  Set ADC0 CFGR0 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to CFGR0.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetConfig(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->CFGR0, Value);
}

/**
  * @brief  Set ADC0 CFGR1 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to CFGR1.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetConfigEx(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->CFGR1, Value);
}

/**
  * @brief  Set ADC0 SIGSEL register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to SIGSEL.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetDifferEnd(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->SIGSEL, Value);
}

/**
  * @brief  Set ADC0 SMPR1 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to SMPR1.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetSamlpeTime(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->SMPR1, Value);
}

/**
  * @brief  Get ADC0 SMPR1 register.
  * @param  ADCx Specifies ADC peripheral.
  * @return SMPR1 register value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetSamlpeTime(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_REG(ADCx->SMPR1));
}

/**
  * @brief  Set ADC0 SQR0 register.
  * @param  ADCx Specifies ADC peripheral.
  * @param  Value Value to be written to SQR0.
  * @return None.
  */
__STATIC_INLINE void LL_ADC_SetRegularSequence(ADC_TypeDef *ADCx, uint32_t Value)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->SQR0, Value);
}

/**
  * @brief  Channel Conversion Done Interrupt Pending Clear
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @return None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_DONx(ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    WRITE_REG(ADCx->DISR, BIT(((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Judge is Channel Conversion Done Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @param  Ch Channel Number @ref LL_ADC_ChTypeDef
  * @retval 0 isn't Channel Conversion Done Interrupt Pending
  * @retval 1 is Channel Conversion Done Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_DONx(const ADC_TypeDef *ADCx, uint32_t Ch)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->DISR, BIT(((Ch) % LL_ADC_CH_NUMS)), ((Ch) % LL_ADC_CH_NUMS)));
}

/**
  * @brief  Judge is ADC Ready Interrupt Pending or not
  * @param  ADCx Specifies ADC peripheral
  * @retval 0 isn't ADC Ready Interrupt Pending
  * @retval 1 is ADC Ready Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_ADRDY(const ADC_TypeDef *ADCx)
{
    ASSERT_INLINE_PARAM(IS_ADC_ALL_INSTANCE(ADCx));

    return (uint32_t)(READ_BIT_SHIFT(ADCx->ISR, ADC0_ISR_ADRDY_Msk, ADC0_ISR_ADRDY_Pos));
}

/**
  * @}
  */ /* SYSCTRL_HAL_EF_Interrupt */

/**
  * @}
  */ /* SYSCTRL_HAL_Exported_Functions */

/**
  * @}
  */ /* SYSCTRL_HAL */

#endif

/**
  * @}
  */ /* TAE32F561x_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
