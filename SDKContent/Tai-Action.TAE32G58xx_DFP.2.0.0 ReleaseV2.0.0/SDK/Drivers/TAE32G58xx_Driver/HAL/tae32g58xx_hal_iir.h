/**
  ******************************************************************************
  * @file    tae32g58xx_hal_iir.h
  * @author  Tai-Action SD Team
  * @brief   Header file for IIR HAL module
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
#ifndef _TAE32G58XX_HAL_IIR_H_
#define _TAE32G58XX_HAL_IIR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_iir.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(IIR0) || defined(IIR1) || defined(IIR2) || defined(IIR3) || \
    defined(IIR4) || defined(IIR5) 

/** @addtogroup IIR_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup IIR_HAL_Exported_Macros IIR HAL Exported Macros
  * @brief    IIR HAL Exported Macros
  * @{
  */

/** @defgroup IIR_HAL_EM_Assert IIR HAL Assert 
  * @brief    IIR HAL Assert
  * @{
  */

/**
  * @brief  The HAL_IIR_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_IIR_CHECK_PARAM
#define TAE32_USE_HAL_IIR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_IIR_CHECK_PARAM != 1) && (TAE32_USE_HAL_IIR_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_IIR_CHECK_PARAM
#define TAE32_USE_HAL_IIR_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_IIR_CHECK_PARAM */

/**
  * @brief  The HAL_IIR_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_IIR_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_IIR_CHECK_PARAM) { \
            expression;                      \
        }
/**
  * @}
  */ /* IIR_HAL_EM_Assert */

/** @defgroup HAL_CAN_EC_Information HAL CAN Information
  * @brief    CAN HAL Information
  * @{
  */

/**
  * @brief IIR Coefficient A Numbers Definition
  */
#define HAL_IIR_COEF_A_NUMBERS    LL_IIR_COEF_A_NUMS

/**
  * @brief IIR Coefficient B Numbers Definition
  */
#define HAL_IIR_COEF_B_NUMBERS    LL_IIR_COEF_B_NUMS

/**
  * @}
  */ /* HAL_CAN_EC_Information */


/**
  * @}
  */ /* IIR_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup IIR_HAL_Exported_Types IIR HAL Exported Types
  * @brief    IIR HAL Exported Types
  * @{
  */

/**
  * @brief IIR Global state
  */
typedef enum
{
  HAL_IIR_STATE_RESET                  = 0UL,              /*!< IIR not yet initialized                   */
  HAL_IIR_STATE_INIT                   = (1UL << 30U),     /*!< IIR initialized but not yet configured    */
  HAL_IIR_STATE_CONFIGURING            = (1UL << 29U),     /*!< IIR configured and ready to be activated  */
  HAL_IIR_STATE_ACTIVE                 = (1UL << 28U),     /*!< IIR activated, ready to operate           */
} HAL_IIR_StateTypeDef;

/**
  * @brief IIR Order Definition
  * @note  IIR0/1/2 Max Order is 4, IIR3/4/5 Max Order is 2
  */
typedef enum
{
    HAL_IIR_ORDER_1       = LL_IIR_ORDER_1,   /*!< IIR Order 1   */
    HAL_IIR_ORDER_2       = LL_IIR_ORDER_2,   /*!< IIR Order 2   */
    HAL_IIR_ORDER_3       = LL_IIR_ORDER_3,   /*!< IIR Order 3   */
    HAL_IIR_ORDER_4       = LL_IIR_ORDER_4    /*!< IIR Order 4   */
} HAL_IIR_OrderTypeDef;

/**
  * @brief IIR Scale Definition
  */
typedef enum
{
    HAL_IIR_SCALE_2_POWER_0   = LL_IIR_SCALE_2_POWER_0,    /*!< IIR Scale 2 Power 0    */
    HAL_IIR_SCALE_2_POWER_1   = LL_IIR_SCALE_2_POWER_1,    /*!< IIR Scale 2 Power 1    */
    HAL_IIR_SCALE_2_POWER_2   = LL_IIR_SCALE_2_POWER_2,    /*!< IIR Scale 2 Power 2    */
    HAL_IIR_SCALE_2_POWER_3   = LL_IIR_SCALE_2_POWER_3,    /*!< IIR Scale 2 Power 3    */
    HAL_IIR_SCALE_2_POWER_4   = LL_IIR_SCALE_2_POWER_4,    /*!< IIR Scale 2 Power 4    */
    HAL_IIR_SCALE_2_POWER_5   = LL_IIR_SCALE_2_POWER_5,    /*!< IIR Scale 2 Power 5    */
    HAL_IIR_SCALE_2_POWER_6   = LL_IIR_SCALE_2_POWER_6,    /*!< IIR Scale 2 Power 6    */
    HAL_IIR_SCALE_2_POWER_7   = LL_IIR_SCALE_2_POWER_7,    /*!< IIR Scale 2 Power 7    */
    HAL_IIR_SCALE_2_POWER_8   = LL_IIR_SCALE_2_POWER_8,    /*!< IIR Scale 2 Power 8    */
    HAL_IIR_SCALE_2_POWER_9   = LL_IIR_SCALE_2_POWER_9,    /*!< IIR Scale 2 Power 9    */
    HAL_IIR_SCALE_2_POWER_10  = LL_IIR_SCALE_2_POWER_10,   /*!< IIR Scale 2 Power 10   */
    HAL_IIR_SCALE_2_POWER_11  = LL_IIR_SCALE_2_POWER_11,   /*!< IIR Scale 2 Power 11   */
    HAL_IIR_SCALE_2_POWER_12  = LL_IIR_SCALE_2_POWER_12,   /*!< IIR Scale 2 Power 12   */
    HAL_IIR_SCALE_2_POWER_13  = LL_IIR_SCALE_2_POWER_13,   /*!< IIR Scale 2 Power 13   */
    HAL_IIR_SCALE_2_POWER_14  = LL_IIR_SCALE_2_POWER_14,   /*!< IIR Scale 2 Power 14   */
    HAL_IIR_SCALE_2_POWER_15  = LL_IIR_SCALE_2_POWER_15,   /*!< IIR Scale 2 Power 15   */
    HAL_IIR_SCALE_2_POWER_16  = LL_IIR_SCALE_2_POWER_16,   /*!< IIR Scale 2 Power 16   */
    HAL_IIR_SCALE_2_POWER_17  = LL_IIR_SCALE_2_POWER_17,   /*!< IIR Scale 2 Power 17   */
    HAL_IIR_SCALE_2_POWER_18  = LL_IIR_SCALE_2_POWER_18,   /*!< IIR Scale 2 Power 18   */
    HAL_IIR_SCALE_2_POWER_19  = LL_IIR_SCALE_2_POWER_19,   /*!< IIR Scale 2 Power 19   */
    HAL_IIR_SCALE_2_POWER_20  = LL_IIR_SCALE_2_POWER_20,   /*!< IIR Scale 2 Power 20   */
    HAL_IIR_SCALE_2_POWER_21  = LL_IIR_SCALE_2_POWER_21,   /*!< IIR Scale 2 Power 21   */
    HAL_IIR_SCALE_2_POWER_22  = LL_IIR_SCALE_2_POWER_22,   /*!< IIR Scale 2 Power 22   */
    HAL_IIR_SCALE_2_POWER_23  = LL_IIR_SCALE_2_POWER_23,   /*!< IIR Scale 2 Power 23   */
    HAL_IIR_SCALE_2_POWER_24  = LL_IIR_SCALE_2_POWER_24,   /*!< IIR Scale 2 Power 24   */
    HAL_IIR_SCALE_2_POWER_25  = LL_IIR_SCALE_2_POWER_25,   /*!< IIR Scale 2 Power 25   */
    HAL_IIR_SCALE_2_POWER_26  = LL_IIR_SCALE_2_POWER_26,   /*!< IIR Scale 2 Power 26   */
    HAL_IIR_SCALE_2_POWER_27  = LL_IIR_SCALE_2_POWER_27,   /*!< IIR Scale 2 Power 27   */
    HAL_IIR_SCALE_2_POWER_28  = LL_IIR_SCALE_2_POWER_28,   /*!< IIR Scale 2 Power 28   */
    HAL_IIR_SCALE_2_POWER_29  = LL_IIR_SCALE_2_POWER_29,   /*!< IIR Scale 2 Power 29   */
    HAL_IIR_SCALE_2_POWER_30  = LL_IIR_SCALE_2_POWER_30,   /*!< IIR Scale 2 Power 30   */
    HAL_IIR_SCALE_2_POWER_31  = LL_IIR_SCALE_2_POWER_31    /*!< IIR Scale 2 Power 31   */
} HAL_IIR_ScaleTypeDef;

/**
  * @brief IIR Coefficient A Definition
  */
typedef enum
{
    HAL_IIR_COEF_A_1       = LL_IIR_COEF_A_1,   /*!< IIR Coefficient A1 */
    HAL_IIR_COEF_A_2       = LL_IIR_COEF_A_2,   /*!< IIR Coefficient A2 */
    HAL_IIR_COEF_A_3       = LL_IIR_COEF_A_3,   /*!< IIR Coefficient A3 */
    HAL_IIR_COEF_A_4       = LL_IIR_COEF_A_4    /*!< IIR Coefficient A4 */
} HAL_IIR_CoefATypeDef;

/**
  * @brief IIR Coefficient B Definition
  */
typedef enum
{
    HAL_IIR_COEF_B_0       = LL_IIR_COEF_B_0,   /*!< IIR Coefficient B0 */
    HAL_IIR_COEF_B_1       = LL_IIR_COEF_B_1,   /*!< IIR Coefficient B1 */
    HAL_IIR_COEF_B_2       = LL_IIR_COEF_B_2,   /*!< IIR Coefficient B2 */
    HAL_IIR_COEF_B_3       = LL_IIR_COEF_B_3,   /*!< IIR Coefficient B3 */
    HAL_IIR_COEF_B_4       = LL_IIR_COEF_B_4,   /*!< IIR Coefficient B4 */
    HAL_IIR_COEF_B_5       = LL_IIR_COEF_B_5    /*!< IIR Coefficient B5 */
} HAL_IIR_CoefBTypeDef;

/**
  * @brief IIR coefficient type definition
  */
typedef struct {
    int32_t Bx[HAL_IIR_COEF_B_NUMBERS];          /*!< coefficient B0~B5     */
    int32_t Ax[HAL_IIR_COEF_A_NUMBERS];          /*!< coefficient A1~A4     */
} HAL_IIR_CoefTypeDef;

/**
  * @brief IIR user config type definition
  */
typedef struct {
    HAL_IIR_OrderTypeDef Order;               /*!< Order Selection                  */
    HAL_IIR_ScaleTypeDef OutputScale;         /*!< Output Scale                     */
    HAL_IIR_ScaleTypeDef FeedbackScale;       /*!< Feedback Scale                   */
    HAL_IIR_CoefTypeDef  Coefficient;         /*!< GroupN Coef                      */
    HAL_IIR_ScaleTypeDef HighOutputScale;     /*!< High Order Filter Output Scale   */
    HAL_IIR_ScaleTypeDef HighFeedbackScale;   /*!< High Order Filter Feedback Scale */    
} HAL_IIR_ParamCfgTypeDef;

typedef struct HAL_IIR_HandleStructDef HAL_IIR_HandleTypeDef; /*!< HAL IIR handle structure type */

/**
  * @brief  IIR Handle Structure definition
  */
struct HAL_IIR_HandleStructDef
{
    IIR_TypeDef                     *Instance;          /*!< Register base address    */
    volatile HAL_IIR_StateTypeDef   State;              /*!< Global state             */
    volatile uint32_t               ErrorCode;          /*!< IIR error code           */
    const void                      *pUserData;         /*!< User data pointer        */
};


/**
  * @}
  */ /* IIR_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup IIR_HAL_Exported_Functions
  * @{
  */

/** @addtogroup IIR_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_IIR_Init(HAL_IIR_HandleTypeDef *Handle, IIR_TypeDef *IIRx);
HAL_StatusTypeDef HAL_IIR_DeInit(HAL_IIR_HandleTypeDef *Handle);
void HAL_IIR_MspInit(HAL_IIR_HandleTypeDef *Handle);
void HAL_IIR_MspDeInit(HAL_IIR_HandleTypeDef *Handle);
/**
  * @}
  */ /* IIR_HAL_EF_Initialization */

/** @addtogroup IIR_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_IIR_Config(HAL_IIR_HandleTypeDef *Handle, 
                                 const HAL_IIR_ParamCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_IIR_Reset(HAL_IIR_HandleTypeDef *Handle);

/**
  * @}
  */ /* IIR_HAL_EF_Configuration */

/** @addtogroup IIR_HAL_EF_Operation
  * @{
  */

HAL_StatusTypeDef HAL_IIR_Enable(HAL_IIR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_IIR_Disable(HAL_IIR_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_IIR_CalculatingNoWait(HAL_IIR_HandleTypeDef *Handle, 
                                      int16_t DataIn, 
                                      int16_t *DataOut);

HAL_StatusTypeDef HAL_IIR_CalculatingPollingBusy(HAL_IIR_HandleTypeDef *Handle, 
                                           int16_t DataIn, 
                                           int16_t *DataOut, 
                                           uint32_t Timeout);

/**
  * @}
  */ /* IIR_HAL_EF_Operation */

/** @addtogroup IIR_HAL_EF_Interrupt
  * @{
  */
HAL_StatusTypeDef HAL_IIR_ErrorInterruptEnable(HAL_IIR_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_IIR_ErrorInterruptDisable(HAL_IIR_HandleTypeDef *Handle);

void HAL_IIR_IRQHandler(HAL_IIR_HandleTypeDef *Handle);
void HAL_IIR_ErrorCallback(HAL_IIR_HandleTypeDef *Handle);

/**
  * @}
  */ /* IIR_HAL_EF_Interrupt */

/**
  * @}
  */ /* IIR_HAL_Exported_Functions */


/**
  * @}
  */ /* IIR_HAL */

#endif /* IIR */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_IIR_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

