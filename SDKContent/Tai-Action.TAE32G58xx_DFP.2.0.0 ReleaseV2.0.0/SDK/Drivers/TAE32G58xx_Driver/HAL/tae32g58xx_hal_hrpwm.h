/**
  ******************************************************************************
  * @file    tae32g58xx_hal_hrpwm.h
  * @author  Tai-Action SD Team
  * @brief   Header file for HRPWM HAL module
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
#ifndef _TAE32G58XX_HAL_HRPWM_H_
#define _TAE32G58XX_HAL_HRPWM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_hrpwm.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(HRPWM)
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_HRPWM_MODULE_ENABLED) && (HAL_HRPWM_MODULE_ENABLED == 1)

/** @addtogroup HRPWM_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup HRPWM_HAL_Exported_Constants HRPWM HAL Exported Constants
  * @brief    HRPWM HAL Exported Constants
  * @{
  */

#define HAL_PWMx_NUMS HAL_HRPWM_SLV_PWM_NUMS


/**
  * @}
  */ /* HRPWM_HAL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup HRPWM_HAL_Exported_Macros HRPWM HAL Exported Macros
  * @brief    HRPWM HAL Exported Macros
  * @{
  */

/** @defgroup HRPWM_HAL_EM_Assert HRPWM HAL Assert 
  * @brief    HRPWM HAL Assert
  * @{
  */

/**
  * @brief  The HAL_HRPWM_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_HRPWM_CHECK_PARAM
#define TAE32_USE_HAL_HRPWM_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_HRPWM_CHECK_PARAM != 1) && (TAE32_USE_HAL_HRPWM_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_HRPWM_CHECK_PARAM
#define TAE32_USE_HAL_HRPWM_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_HRPWM_CHECK_PARAM */

/**
  * @brief  The HAL_HRPWM_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_HRPWM_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_HRPWM_CHECK_PARAM) { \
            expression;                         \
        }
/**
  * @}
  */ /* HRPWM_HAL_EM_Assert */

/** @defgroup HRPWM_HAL_EM_Mask HRPWM HAL Mask
  * @brief    HRPWM HAL Mask
  * @{
  */

/**
  * @brief HRPWM Master Interrupt Enable Mask Definition
  */
#define HAL_HRPWM_MstITEnMaskTypeDef                        LL_HRPWM_MST_MDIER_ITEnMskTypeDef

#define HAL_HRPWM_MST_MDIER_REPETITION_IT_EN                LL_HRPWM_MST_MDIER_MREPIE                          /*!< MDIER_MREPIE Mask        */
#define HAL_HRPWM_MST_MDIER_RESET_IT_EN                     LL_HRPWM_MST_MDIER_MRSTIE                          /*!< MDIER_MRSTIE Mask        */
#define HAL_HRPWM_MST_MDIER_UPDATE_IT_EN                    LL_HRPWM_MST_MDIER_MUPDIE                          /*!< MDIER_MUPDIE Mask        */
#define HAL_HRPWM_MST_MDIER_SYNC_INPUT_IT_EN                LL_HRPWM_MST_MDIER_SYNCIE                          /*!< MDIER_SYNCIE Mask        */
#define HAL_HRPWM_MST_MDIER_PERIOD_IT_EN                    LL_HRPWM_MST_MDIER_MPERIE                          /*!< MDIER_MPERIE Mask        */
#define HAL_HRPWM_MST_MDIER_CMPD_IT_EN                      LL_HRPWM_MST_MDIER_MCMPDIE                         /*!< MDIER_MCMPDIE Mask       */
#define HAL_HRPWM_MST_MDIER_CMPC_IT_EN                      LL_HRPWM_MST_MDIER_MCMPCIE                         /*!< MDIER_MCMPCIE Mask       */
#define HAL_HRPWM_MST_MDIER_CMPB_IT_EN                      LL_HRPWM_MST_MDIER_MCMPBIE                         /*!< MDIER_MCMPBIE Mask       */
#define HAL_HRPWM_MST_MDIER_CMPA_IT_EN                      LL_HRPWM_MST_MDIER_MCMPAIE                         /*!< MDIER_MCMPAIE Mask       */

/**
  * @brief HRPWM Master Interrupt Pending Mask Definition
  */
#define HAL_HRPWM_MstITPendingMskTypeDef                    LL_HRPWM_MST_MISR_ITPendingMskTypeDef

#define HAL_HRPWM_MST_MISR_REPETITION_IT_FLAG               LL_HRPWM_MST_MISR_MREP                             /*!< MISR_MREP Mask           */
#define HAL_HRPWM_MST_MISR_RESET_IT_FLAG                    LL_HRPWM_MST_MISR_MRST                             /*!< MISR_MRST Mask           */
#define HAL_HRPWM_MST_MISR_UPDATE_IT_FLAG                   LL_HRPWM_MST_MISR_MUPD                             /*!< MISR_MUPD Mask           */
#define HAL_HRPWM_MST_MISR_SYNC_INPUT_IT_FLAG               LL_HRPWM_MST_MISR_SYNC                             /*!< MISR_SYNC Mask           */
#define HAL_HRPWM_MST_MISR_PERIOD_IT_FLAG                   LL_HRPWM_MST_MISR_MPER                             /*!< MISR_MPER Mask           */
#define HAL_HRPWM_MST_MISR_CMPD_IT_FLAG                     LL_HRPWM_MST_MISR_MCMPD                            /*!< MISR_MCMPD Mask          */
#define HAL_HRPWM_MST_MISR_CMPC_IT_FLAG                     LL_HRPWM_MST_MISR_MCMPC                            /*!< MISR_MCMPC Mask          */
#define HAL_HRPWM_MST_MISR_CMPB_IT_FLAG                     LL_HRPWM_MST_MISR_MCMPB                            /*!< MISR_MCMPB Mask          */
#define HAL_HRPWM_MST_MISR_CMPA_IT_FLAG                     LL_HRPWM_MST_MISR_MCMPA                            /*!< MISR_MCMPA Mask          */

/**
  * @brief HRPWM Slave Interrupt Enable Mask Definition
  */
#define HAL_HRPWM_SlvITEnMaskTypeDef                        LL_HRPWM_SLV_PWMDIER_ITEnMskTypeDef

#define HAL_HRPWM_SLV_PWMDIER_DELAY_PROT_IT_EN              LL_HRPWM_SLV_PWMDIER_DLYPRTIE                      /*!< PWMDIER_DLYPRTIE Mask    */
#define HAL_HRPWM_SLV_PWMDIER_CAPB_IT_EN                    LL_HRPWM_SLV_PWMDIER_CAPBIE                        /*!< PWMDIER_CAPBIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_CAPA_IT_EN                    LL_HRPWM_SLV_PWMDIER_CAPAIE                        /*!< PWMDIER_CAPAIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_REPETITION_IT_EN              LL_HRPWM_SLV_PWMDIER_REPIE                         /*!< PWMDIER_REPIE Mask       */
#define HAL_HRPWM_SLV_PWMDIER_RESET_IT_EN                   LL_HRPWM_SLV_PWMDIER_RSTIE                         /*!< PWMDIER_RSTIE Mask       */
#define HAL_HRPWM_SLV_PWMDIER_CLRB_IT_EN                    LL_HRPWM_SLV_PWMDIER_CLRBIE                        /*!< PWMDIER_CLRBIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_SETB_IT_EN                    LL_HRPWM_SLV_PWMDIER_SETBIE                        /*!< PWMDIER_SETBIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_CLRA_IT_EN                    LL_HRPWM_SLV_PWMDIER_CLRAIE                        /*!< PWMDIER_CLRAIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_SETA_IT_EN                    LL_HRPWM_SLV_PWMDIER_SETAIE                        /*!< PWMDIER_SETAIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_UPDATE_IT_EN                  LL_HRPWM_SLV_PWMDIER_UPDIE                         /*!< PWMDIER_UPDIE Mask       */
#define HAL_HRPWM_SLV_PWMDIER_PERIOD_IT_EN                  LL_HRPWM_SLV_PWMDIER_PERIE                         /*!< PWMDIER_PERIE Mask       */
#define HAL_HRPWM_SLV_PWMDIER_CMPD_IT_EN                    LL_HRPWM_SLV_PWMDIER_CMPDIE                        /*!< PWMDIER_CMPDIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_CMPC_IT_EN                    LL_HRPWM_SLV_PWMDIER_CMPCIE                        /*!< PWMDIER_CMPCIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_CMPB_IT_EN                    LL_HRPWM_SLV_PWMDIER_CMPBIE                        /*!< PWMDIER_CMPBIE Mask      */
#define HAL_HRPWM_SLV_PWMDIER_CMPA_IT_EN                    LL_HRPWM_SLV_PWMDIER_CMPAIE                        /*!< PWMDIER_CMPAIE Mask      */

/**
  * @brief HRPWM Slave Interrupt Pending Mask Definition
  */
#define HAL_HRPWM_SlvITPendingMskTypeDef                    LL_HRPWM_SLV_PWMISR_ITPendingMskTypeDef

#define HAL_HRPWM_SLV_PWMISR_DELAY_PROT_IT_FLAG             LL_HRPWM_SLV_PWMISR_DLYPRT                         /*!< PWMISR_DLYPRT Mask       */
#define HAL_HRPWM_SLV_PWMISR_CAPB_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CAPB                           /*!< PWMISR_CAPB Mask         */
#define HAL_HRPWM_SLV_PWMISR_CAPA_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CAPA                           /*!< PWMISR_CAPA Mask         */
#define HAL_HRPWM_SLV_PWMISR_REPETITION_IT_FLAG             LL_HRPWM_SLV_PWMISR_REP                            /*!< PWMISR_REP Mask          */
#define HAL_HRPWM_SLV_PWMISR_RESET_IT_FLAG                  LL_HRPWM_SLV_PWMISR_RST                            /*!< PWMISR_RST Mask          */
#define HAL_HRPWM_SLV_PWMISR_CLRB_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CLRB                           /*!< PWMISR_CLRB Mask         */
#define HAL_HRPWM_SLV_PWMISR_SETB_IT_FLAG                   LL_HRPWM_SLV_PWMISR_SETB                           /*!< PWMISR_SETB Mask         */
#define HAL_HRPWM_SLV_PWMISR_CLRA_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CLRA                           /*!< PWMISR_CLRA Mask         */
#define HAL_HRPWM_SLV_PWMISR_SETA_IT_FLAG                   LL_HRPWM_SLV_PWMISR_SETA                           /*!< PWMISR_SETA Mask         */
#define HAL_HRPWM_SLV_PWMISR_UPDATE_IT_FLAG                 LL_HRPWM_SLV_PWMISR_UPD                            /*!< PWMISR_UPD Mask          */
#define HAL_HRPWM_SLV_PWMISR_PERIOD_IT_FLAG                 LL_HRPWM_SLV_PWMISR_PER                            /*!< PWMISR_PER Mask          */
#define HAL_HRPWM_SLV_PWMISR_CMPD_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CMPD                           /*!< PWMISR_CMPD Mask         */
#define HAL_HRPWM_SLV_PWMISR_CMPC_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CMPC                           /*!< PWMISR_CMPC Mask         */
#define HAL_HRPWM_SLV_PWMISR_CMPB_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CMPB                           /*!< PWMISR_CMPB Mask         */
#define HAL_HRPWM_SLV_PWMISR_CMPA_IT_FLAG                   LL_HRPWM_SLV_PWMISR_CMPA                           /*!< PWMISR_CMPA Mask         */

/**
  * @brief HRPWM Common Interrupt Enable Mask Definition
  */
#define HAL_HRPWM_ComITEnMaskTypeDef                        LL_HRPWM_COM_IER_ITEnMskTypeDef

#define HAL_HRPWM_COM_IER_BURST_PERIOD_IT_EN                LL_HRPWM_COM_IER_BMPERIE                           /*!< IER_BMPERIE Mask         */
#define HAL_HRPWM_COM_IER_FLT7_IT_EN                        LL_HRPWM_COM_IER_FLT7IE                            /*!< IER_FLT7IE Mask          */
#define HAL_HRPWM_COM_IER_FLT6_IT_EN                        LL_HRPWM_COM_IER_FLT6IE                            /*!< IER_FLT6IE Mask          */
#define HAL_HRPWM_COM_IER_FLT5_IT_EN                        LL_HRPWM_COM_IER_FLT5IE                            /*!< IER_FLT5IE Mask          */
#define HAL_HRPWM_COM_IER_FLT4_IT_EN                        LL_HRPWM_COM_IER_FLT4IE                            /*!< IER_FLT4IE Mask          */
#define HAL_HRPWM_COM_IER_FLT3_IT_EN                        LL_HRPWM_COM_IER_FLT3IE                            /*!< IER_FLT3IE Mask          */
#define HAL_HRPWM_COM_IER_FLT2_IT_EN                        LL_HRPWM_COM_IER_FLT2IE                            /*!< IER_FLT2IE Mask          */
#define HAL_HRPWM_COM_IER_FLT1_IT_EN                        LL_HRPWM_COM_IER_FLT1IE                            /*!< IER_FLT1IE Mask          */
#define HAL_HRPWM_COM_IER_FLT0_IT_EN                        LL_HRPWM_COM_IER_FLT0IE                            /*!< IER_FLT0IE Mask          */
#define HAL_HRPWM_COM_IER_SYS_FLT_IT_EN                     LL_HRPWM_COM_IER_SYSFLTIE                          /*!< IER_SYSFLTIE Mask        */

/**
  * @brief HRPWM Common Interrupt Pending Mask Definition
  */
#define HAL_HRPWM_ComITPendingMskTypeDef                    LL_HRPWM_COM_ISR_ITPendingMskTypeDef

#define HAL_HRPWM_COM_ISR_BURST_PERIOD_IT_FLAG              LL_HRPWM_COM_ISR_BMPER                             /*!< ISR_BMPER Mask           */
#define HAL_HRPWM_COM_ISR_FLT7_IT_FLAG                      LL_HRPWM_COM_ISR_FLT7                              /*!< ISR_FLT7 Mask            */
#define HAL_HRPWM_COM_ISR_FLT6_IT_FLAG                      LL_HRPWM_COM_ISR_FLT6                              /*!< ISR_FLT6 Mask            */
#define HAL_HRPWM_COM_ISR_FLT5_IT_FLAG                      LL_HRPWM_COM_ISR_FLT5                              /*!< ISR_FLT5 Mask            */
#define HAL_HRPWM_COM_ISR_FLT4_IT_FLAG                      LL_HRPWM_COM_ISR_FLT4                              /*!< ISR_FLT4 Mask            */
#define HAL_HRPWM_COM_ISR_FLT3_IT_FLAG                      LL_HRPWM_COM_ISR_FLT3                              /*!< ISR_FLT3 Mask            */
#define HAL_HRPWM_COM_ISR_FLT2_IT_FLAG                      LL_HRPWM_COM_ISR_FLT2                              /*!< ISR_FLT2 Mask            */
#define HAL_HRPWM_COM_ISR_FLT1_IT_FLAG                      LL_HRPWM_COM_ISR_FLT1                              /*!< ISR_FLT1 Mask            */
#define HAL_HRPWM_COM_ISR_FLT0_IT_FLAG                      LL_HRPWM_COM_ISR_FLT0                              /*!< ISR_FLT0 Mask            */
#define HAL_HRPWM_COM_ISR_SYS_FLT_IT_FLAG                   LL_HRPWM_COM_ISR_SYSFLT                            /*!< ISR_SYSFLT Mask          */


/**
  * @brief HRPWM PWM Mask Definition
  */
#define HAL_HRPWM_PWMMaskTypeDef                            LL_HRPWM_PWMMaskTypeDef                            

#define HAL_HRPWM_PWM_NONE_MASK                             LL_HRPWM_PWM_NONE_MASK                             /*!< HRPWM PWM None Mask    */
#define HAL_HRPWM_MST_PWM_MASK                              LL_HRPWM_MST_PWM_MASK                              /*!< HRPWM Master PWM Mask  */
#define HAL_HRPWM_SLV_PWM_0_MASK                            LL_HRPWM_SLV_PWM_0_MASK                            /*!< HRPWM Slave PWM 0 Mask */
#define HAL_HRPWM_SLV_PWM_1_MASK                            LL_HRPWM_SLV_PWM_1_MASK                            /*!< HRPWM Slave PWM 1 Mask */
#define HAL_HRPWM_SLV_PWM_2_MASK                            LL_HRPWM_SLV_PWM_2_MASK                            /*!< HRPWM Slave PWM 2 Mask */
#define HAL_HRPWM_SLV_PWM_3_MASK                            LL_HRPWM_SLV_PWM_3_MASK                            /*!< HRPWM Slave PWM 3 Mask */
#define HAL_HRPWM_SLV_PWM_4_MASK                            LL_HRPWM_SLV_PWM_4_MASK                            /*!< HRPWM Slave PWM 4 Mask */
#define HAL_HRPWM_SLV_PWM_5_MASK                            LL_HRPWM_SLV_PWM_5_MASK                            /*!< HRPWM Slave PWM 5 Mask */
#define HAL_HRPWM_SLV_PWM_6_MASK                            LL_HRPWM_SLV_PWM_6_MASK                            /*!< HRPWM Slave PWM 6 Mask */
#define HAL_HRPWM_SLV_PWM_7_MASK                            LL_HRPWM_SLV_PWM_7_MASK                            /*!< HRPWM Slave PWM 7 Mask */
#define HAL_HRPWM_ALL_PWM_MASK                              LL_HRPWM_ALL_PWM_MASK                              /*!< HRPWM All PWM Mask     */

/**
  * @brief HRPWM Fault Mask Definition
  */
#define HAL_HRPWM_Slv_FltMskTypeDef                         LL_HRPWM_Slv_FltMskTypeDef     

#define HAL_HRPWM_SLV_FLT_NONE_MASK                         LL_HRPWM_SLV_FLT_NONE_MASK                         /*!< HRPWM Slave PWM Fault None Mask */
#define HAL_HRPWM_SLV_FLT_PWM_0_MASK                        LL_HRPWM_SLV_FLT_PWM_0_MASK                        /*!< HRPWM Slave PWM Fault 0 Mask    */
#define HAL_HRPWM_SLV_FLT_PWM_1_MASK                        LL_HRPWM_SLV_FLT_PWM_1_MASK                        /*!< HRPWM Slave PWM Fault 1 Mask    */
#define HAL_HRPWM_SLV_FLT_PWM_2_MASK                        LL_HRPWM_SLV_FLT_PWM_2_MASK                        /*!< HRPWM Slave PWM Fault 2 Mask    */
#define HAL_HRPWM_SLV_FLT_PWM_3_MASK                        LL_HRPWM_SLV_FLT_PWM_3_MASK                        /*!< HRPWM Slave PWM Fault 3 Mask    */
#define HAL_HRPWM_SLV_FLT_PWM_4_MASK                        LL_HRPWM_SLV_FLT_PWM_4_MASK                        /*!< HRPWM Slave PWM Fault 4 Mask    */
#define HAL_HRPWM_SLV_FLT_PWM_5_MASK                        LL_HRPWM_SLV_FLT_PWM_5_MASK                        /*!< HRPWM Slave PWM Fault 5 Mask    */
#define HAL_HRPWM_SLV_FLT_PWM_6_MASK                        LL_HRPWM_SLV_FLT_PWM_6_MASK                        /*!< HRPWM Slave PWM Fault 6 Mask    */
#define HAL_HRPWM_SLV_FLT_PWM_7_MASK                        LL_HRPWM_SLV_FLT_PWM_7_MASK                        /*!< HRPWM Slave PWM Fault 7 Mask    */
#define HAL_HRPWM_ALL_FLT_PWM_MASK                          LL_HRPWM_ALL_FLT_PWM_MASK                          /*!< HRPWM All Slave PWM Fault Mask  */

/**
  * @brief HRPWM Update Trigger PWMx Definition
  */
#define HAL_HRPWM_Slv_PWMUpdTrigTypeDef                     LL_HRPWM_Slv_PWMUpdTrigTypeDef     

#define HAL_HRPWM_SLV_UPD_TRIG_NONE_MASK                    LL_HRPWM_SLV_UPD_TRIG_NONE_MASK                    /*!< HRPWM None Update Trigger PWMx Mask    */
#define HAL_HRPWM_SLV_UPD_TRIG_MST_MASK                     LL_HRPWM_SLV_UPD_TRIG_MST_MASK                     /*!< HRPWM Master PWM Update Trigger PWMx   */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_0_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_0_MASK               /*!< HRPWM Slave PWM 0 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_1_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_1_MASK               /*!< HRPWM Slave PWM 1 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_2_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_2_MASK               /*!< HRPWM Slave PWM 2 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_3_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_3_MASK               /*!< HRPWM Slave PWM 3 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_4_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_4_MASK               /*!< HRPWM Slave PWM 4 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_5_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_5_MASK               /*!< HRPWM Slave PWM 5 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_6_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_6_MASK               /*!< HRPWM Slave PWM 6 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_SLV_PWM_7_MASK               LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_7_MASK               /*!< HRPWM Slave PWM 7 Update Trigger PWMx  */
#define HAL_HRPWM_SLV_UPD_TRIG_ALL_PWM_MASK                 LL_HRPWM_SLV_UPD_TRIG_ALL_PWM_MASK                 /*!< HRPWM All PWM Update Trigger PWMx Mask */

/**
  * @brief HRPWM PWM Output Mask Definition
  */
#define HAL_HRPWM_PWMOutputMaskTypeDef                      LL_HRPWM_PWMOutputMaskTypeDef                      

#define HAL_HRPWM_SLV_PWM_OUT_NONE_MASK                     LL_HRPWM_SLV_PWM_OUT_NONE_MASK                     /*!< HRPWM Slave PWM Out None Mask */
#define HAL_HRPWM_SLV_PWM_0_OUT_A_MASK                      LL_HRPWM_SLV_PWM_0_OUT_A_MASK                      /*!< HRPWM Slave PWM 0 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_0_OUT_A_MASK                      LL_HRPWM_SLV_PWM_0_OUT_A_MASK                      /*!< HRPWM Slave PWM 0 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_0_OUT_B_MASK                      LL_HRPWM_SLV_PWM_0_OUT_B_MASK                      /*!< HRPWM Slave PWM 0 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_1_OUT_A_MASK                      LL_HRPWM_SLV_PWM_1_OUT_A_MASK                      /*!< HRPWM Slave PWM 1 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_1_OUT_B_MASK                      LL_HRPWM_SLV_PWM_1_OUT_B_MASK                      /*!< HRPWM Slave PWM 1 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_2_OUT_A_MASK                      LL_HRPWM_SLV_PWM_2_OUT_A_MASK                      /*!< HRPWM Slave PWM 2 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_2_OUT_B_MASK                      LL_HRPWM_SLV_PWM_2_OUT_B_MASK                      /*!< HRPWM Slave PWM 2 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_3_OUT_A_MASK                      LL_HRPWM_SLV_PWM_3_OUT_A_MASK                      /*!< HRPWM Slave PWM 3 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_3_OUT_B_MASK                      LL_HRPWM_SLV_PWM_3_OUT_B_MASK                      /*!< HRPWM Slave PWM 3 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_4_OUT_A_MASK                      LL_HRPWM_SLV_PWM_4_OUT_A_MASK                      /*!< HRPWM Slave PWM 4 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_4_OUT_B_MASK                      LL_HRPWM_SLV_PWM_4_OUT_B_MASK                      /*!< HRPWM Slave PWM 4 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_5_OUT_A_MASK                      LL_HRPWM_SLV_PWM_5_OUT_A_MASK                      /*!< HRPWM Slave PWM 5 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_5_OUT_B_MASK                      LL_HRPWM_SLV_PWM_5_OUT_B_MASK                      /*!< HRPWM Slave PWM 5 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_6_OUT_A_MASK                      LL_HRPWM_SLV_PWM_6_OUT_A_MASK                      /*!< HRPWM Slave PWM 6 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_6_OUT_B_MASK                      LL_HRPWM_SLV_PWM_6_OUT_B_MASK                      /*!< HRPWM Slave PWM 6 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_7_OUT_A_MASK                      LL_HRPWM_SLV_PWM_7_OUT_A_MASK                      /*!< HRPWM Slave PWM 7 Out A Mask  */
#define HAL_HRPWM_SLV_PWM_7_OUT_B_MASK                      LL_HRPWM_SLV_PWM_7_OUT_B_MASK                      /*!< HRPWM Slave PWM 7 Out B Mask  */
#define HAL_HRPWM_SLV_PWM_OUT_ALL_MASK                      LL_HRPWM_SLV_PWM_OUT_ALL_MASK                      /*!< HRPWM Slave PWM Out All Mask  */

/**
  * @brief HRPWM Master PWM Interrupt Definition
  */
#define HAL_HRPWM_Mst_IntTypeDef                            LL_HRPWM_Mst_IntTypeDef                            

#define HAL_HRPWM_MST_INT_NONE                              LL_HRPWM_MST_INT_NONE                              /*!< Master Interrupt None       */
#define HAL_HRPWM_MST_INT_CMPA                              LL_HRPWM_MST_INT_CMPA                              /*!< Master Interrupt Compare A  */
#define HAL_HRPWM_MST_INT_CMPB                              LL_HRPWM_MST_INT_CMPB                              /*!< Master Interrupt Compare B  */
#define HAL_HRPWM_MST_INT_CMPC                              LL_HRPWM_MST_INT_CMPC                              /*!< Master Interrupt Compare C  */
#define HAL_HRPWM_MST_INT_CMPD                              LL_HRPWM_MST_INT_CMPD                              /*!< Master Interrupt Compare D  */
#define HAL_HRPWM_MST_INT_PRD                               LL_HRPWM_MST_INT_PRD                               /*!< Master Interrupt Period     */
#define HAL_HRPWM_MST_INT_SYNCIN                            LL_HRPWM_MST_INT_SYNCIN                            /*!< Master Interrupt Sync In    */
#define HAL_HRPWM_MST_INT_UPD                               LL_HRPWM_MST_INT_UPD                               /*!< Master Interrupt Update     */
#define HAL_HRPWM_MST_INT_RST                               LL_HRPWM_MST_INT_RST                               /*!< Master Interrupt Reset      */
#define HAL_HRPWM_MST_INT_REP                               LL_HRPWM_MST_INT_REP                               /*!< Master Interrupt Repetition */
#define HAL_HRPWM_MST_INT_ALL_MASK                          LL_HRPWM_MST_INT_ALL_MASK                          /*!< Master Interrupt All Mask   */

/**
  * @brief HRPWM Master PWM DMA Definition
  */
#define HAL_HRPWM_Mst_DMATypeDef                            LL_HRPWM_Mst_DMATypeDef                            

#define HAL_HRPWM_MST_DMA_NONE                              LL_HRPWM_MST_DMA_NONE                              /*!< Master DMA None       */
#define HAL_HRPWM_MST_DMA_CMPA                              LL_HRPWM_MST_DMA_CMPA                              /*!< Master DMA Compare A  */
#define HAL_HRPWM_MST_DMA_CMPB                              LL_HRPWM_MST_DMA_CMPB                              /*!< Master DMA Compare B  */
#define HAL_HRPWM_MST_DMA_CMPC                              LL_HRPWM_MST_DMA_CMPC                              /*!< Master DMA Compare C  */
#define HAL_HRPWM_MST_DMA_CMPD                              LL_HRPWM_MST_DMA_CMPD                              /*!< Master DMA Compare D  */
#define HAL_HRPWM_MST_DMA_PRD                               LL_HRPWM_MST_DMA_PRD                               /*!< Master DMA Period     */
#define HAL_HRPWM_MST_DMA_SYNCIN                            LL_HRPWM_MST_DMA_SYNCIN                            /*!< Master DMA Sync In    */
#define HAL_HRPWM_MST_DMA_UPD                               LL_HRPWM_MST_DMA_UPD                               /*!< Master DMA Update     */
#define HAL_HRPWM_MST_DMA_RST                               LL_HRPWM_MST_DMA_RST                               /*!< Master DMA Reset      */
#define HAL_HRPWM_MST_DMA_REP                               LL_HRPWM_MST_DMA_REP                               /*!< Master DMA Repetition */
#define HAL_HRPWM_MST_DMA_ALL_MASK                          LL_HRPWM_MST_DMA_ALL_MASK                          /*!< Master DMA All Mask   */

/**
  * @brief HRPWM Slave PWM Interrupt Definition
  */
#define HAL_HRPWM_Slv_IntTypeDef                            LL_HRPWM_Slv_IntTypeDef                            

#define HAL_HRPWM_SLV_INT_NONE                              LL_HRPWM_SLV_INT_NONE                              /*!< Slave Interrupt None             */
#define HAL_HRPWM_SLV_INT_CMPA                              LL_HRPWM_SLV_INT_CMPA                              /*!< Slave Interrupt Compare A        */
#define HAL_HRPWM_SLV_INT_CMPB                              LL_HRPWM_SLV_INT_CMPB                              /*!< Slave Interrupt Compare B        */
#define HAL_HRPWM_SLV_INT_CMPC                              LL_HRPWM_SLV_INT_CMPC                              /*!< Slave Interrupt Compare C        */
#define HAL_HRPWM_SLV_INT_CMPD                              LL_HRPWM_SLV_INT_CMPD                              /*!< Slave Interrupt Compare D        */
#define HAL_HRPWM_SLV_INT_PRD_RO                            LL_HRPWM_SLV_INT_PRD_RO                            /*!< Slave Interrupt Period/Roll-Over */
#define HAL_HRPWM_SLV_INT_UPD                               LL_HRPWM_SLV_INT_UPD                               /*!< Slave Interrupt Update           */
#define HAL_HRPWM_SLV_INT_OUTA_SET                          LL_HRPWM_SLV_INT_OUTA_SET                          /*!< Slave Interrupt OutA Set         */
#define HAL_HRPWM_SLV_INT_OUTA_CLR                          LL_HRPWM_SLV_INT_OUTA_CLR                          /*!< Slave Interrupt OutA Clear       */
#define HAL_HRPWM_SLV_INT_OUTB_SET                          LL_HRPWM_SLV_INT_OUTB_SET                          /*!< Slave Interrupt OutB Set         */
#define HAL_HRPWM_SLV_INT_OUTB_CLR                          LL_HRPWM_SLV_INT_OUTB_CLR                          /*!< Slave Interrupt OutB Clear       */
#define HAL_HRPWM_SLV_INT_RST                               LL_HRPWM_SLV_INT_RST                               /*!< Slave Interrupt Reset            */
#define HAL_HRPWM_SLV_INT_REP                               LL_HRPWM_SLV_INT_REP                               /*!< Slave Interrupt Repetition       */
#define HAL_HRPWM_SLV_INT_CAPA                              LL_HRPWM_SLV_INT_CAPA                              /*!< Slave Interrupt Capture A        */
#define HAL_HRPWM_SLV_INT_CAPB                              LL_HRPWM_SLV_INT_CAPB                              /*!< Slave Interrupt Capture B        */
#define HAL_HRPWM_SLV_INT_DLY_PROT                          LL_HRPWM_SLV_INT_DLY_PROT                          /*!< Slave Interrupt Delay Protection */
#define HAL_HRPWM_SLV_INT_ALL_MASK                          LL_HRPWM_SLV_INT_ALL_MASK                          /*!< Slave Interrupt All Mask         */

/**
  * @brief HRPWM Slave PWM DMA Definition
  */
#define HAL_HRPWM_Slv_DMATypeDef                            LL_HRPWM_Slv_DMATypeDef                            

#define HAL_HRPWM_SLV_DMA_NONE                              LL_HRPWM_SLV_DMA_NONE                              /*!< Slave DMA None             */
#define HAL_HRPWM_SLV_DMA_CMPA                              LL_HRPWM_SLV_DMA_CMPA                              /*!< Slave DMA Compare A        */
#define HAL_HRPWM_SLV_DMA_CMPB                              LL_HRPWM_SLV_DMA_CMPB                              /*!< Slave DMA Compare B        */
#define HAL_HRPWM_SLV_DMA_CMPC                              LL_HRPWM_SLV_DMA_CMPC                              /*!< Slave DMA Compare C        */
#define HAL_HRPWM_SLV_DMA_CMPD                              LL_HRPWM_SLV_DMA_CMPD                              /*!< Slave DMA Compare D        */
#define HAL_HRPWM_SLV_DMA_PRD_RO                            LL_HRPWM_SLV_DMA_PRD_RO                            /*!< Slave DMA Period/Roll-Over */
#define HAL_HRPWM_SLV_DMA_UPD                               LL_HRPWM_SLV_DMA_UPD                               /*!< Slave DMA Update           */
#define HAL_HRPWM_SLV_DMA_OUTA_SET                          LL_HRPWM_SLV_DMA_OUTA_SET                          /*!< Slave DMA OutA Set         */
#define HAL_HRPWM_SLV_DMA_OUTA_CLR                          LL_HRPWM_SLV_DMA_OUTA_CLR                          /*!< Slave DMA OutA Clear       */
#define HAL_HRPWM_SLV_DMA_OUTB_SET                          LL_HRPWM_SLV_DMA_OUTB_SET                          /*!< Slave DMA OutB Set         */
#define HAL_HRPWM_SLV_DMA_OUTB_CLR                          LL_HRPWM_SLV_DMA_OUTB_CLR                          /*!< Slave DMA OutB Clear       */
#define HAL_HRPWM_SLV_DMA_RST                               LL_HRPWM_SLV_DMA_RST                               /*!< Slave DMA Reset            */
#define HAL_HRPWM_SLV_DMA_REP                               LL_HRPWM_SLV_DMA_REP                               /*!< Slave DMA Repetition       */
#define HAL_HRPWM_SLV_DMA_CAPA                              LL_HRPWM_SLV_DMA_CAPA                              /*!< Slave DMA Capture A        */
#define HAL_HRPWM_SLV_DMA_CAPB                              LL_HRPWM_SLV_DMA_CAPB                              /*!< Slave DMA Capture B        */
#define HAL_HRPWM_SLV_DMA_DLY_PROT                          LL_HRPWM_SLV_DMA_DLY_PROT                          /*!< Slave DMA Delay Protection */
#define HAL_HRPWM_SLV_DMA_ALL_MASK                          LL_HRPWM_SLV_DMA_ALL_MASK                          /*!< Slave DMA All Mask         */

/**
  * @brief HRPWM Slave Output Control Event Definition
  */
#define HAL_HRPWM_Slv_OutCtrlEvtTypeDef                     LL_HRPWM_Slv_OutCtrlEvtTypeDef                     

#define HAL_HRPWM_SLV_OUT_CTRL_EVT_NONE                     LL_HRPWM_SLV_OUT_CTRL_EVT_NONE                     /*!< Slave Output Control Event None                 */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG                  LL_HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG                  /*!< Slave Output Control Event Software Set Trigger */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPA                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPA                /*!< Slave Output Control Event PWMx Compare A       */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPB                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPB                /*!< Slave Output Control Event PWMx Compare B       */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPC                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPC                /*!< Slave Output Control Event PWMx Compare C       */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPD                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPD                /*!< Slave Output Control Event PWMx Compare D       */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_ROLL_OVER           LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_ROLL_OVER           /*!< Slave Output Control Event PWMx Roll Over       */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPA             LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPA             /*!< Slave Output Control Event Master PWM Compare A */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPB             LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPB             /*!< Slave Output Control Event Master PWM Compare B */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPC             LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPC             /*!< Slave Output Control Event Master PWM Compare C */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPD             LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPD             /*!< Slave Output Control Event Master PWM Compare D */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_PERIOD           LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_PERIOD           /*!< Slave Output Control Event Master PWM Period    */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT0                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT0                /*!< Slave Output Control Event PWMx Event 0         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT1                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT1                /*!< Slave Output Control Event PWMx Event 1         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT2                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT2                /*!< Slave Output Control Event PWMx Event 2         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT3                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT3                /*!< Slave Output Control Event PWMx Event 3         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT4                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT4                /*!< Slave Output Control Event PWMx Event 4         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT5                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT5                /*!< Slave Output Control Event PWMx Event 5         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT6                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT6                /*!< Slave Output Control Event PWMx Event 6         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT7                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT7                /*!< Slave Output Control Event PWMx Event 7         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT8                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT8                /*!< Slave Output Control Event PWMx Event 8         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT9                LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT9                /*!< Slave Output Control Event PWMx Event 9         */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_SYNC_INPUT_EVT           LL_HRPWM_SLV_OUT_CTRL_EVT_SYNC_INPUT_EVT           /*!< Slave Output Control Event Sync Input Event     */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_UPDATE              LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_UPDATE              /*!< Slave Output Control Event PWMx Update          */
#define HAL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK                 LL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK                 /*!< Slave Output Control Event All Mask             */

/**
  * @brief HRPWM Burst DMA PWM Register Update Definition
  */
#define HAL_HRPWM_BurstDMARegUpdTypeDef                     LL_HRPWM_Comm_BurstDMARegUpdTypeDef    

/**
  * @brief HRPWM Burst DMA Master PWM Register Update Definition
  */
#define HAL_HRPWM_BurstDMAMstRegUpdTypeDef                  HAL_HRPWM_BurstDMARegUpdTypeDef             

#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_NONE                LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_NONE           /*!< Burst DMA Master PWM Register Update None   */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MCR0                LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCR0           /*!< Burst DMA Master PWM Register Update MCR0   */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MCR1                LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCR1           /*!< Burst DMA Master PWM Register Update MCR1   */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MISR                LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MISR           /*!< Burst DMA Master PWM Register Update MISR   */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MDIER               LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MDIER          /*!< Burst DMA Master PWM Register Update MDIER  */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MCNTR               LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCNTR          /*!< Burst DMA Master PWM Register Update MCNTR  */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MPER                LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MPER           /*!< Burst DMA Master PWM Register Update MPER   */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MREP                LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MREP           /*!< Burst DMA Master PWM Register Update MREP   */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MCMPAR              LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPAR         /*!< Burst DMA Master PWM Register Update MCMPAR */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MCMPBR              LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPBR         /*!< Burst DMA Master PWM Register Update MCMPBR */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MCMPCR              LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPCR         /*!< Burst DMA Master PWM Register Update MCMPCR */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_MCMPDR              LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPDR         /*!< Burst DMA Master PWM Register Update MCMPDR */
#define HAL_HRPWM_BURST_DMA_MST_REG_UPD_ALL_MASK            LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL_MASK       /*!< Burst DMA Master PWM Register Update All    */

/**
  * @brief HRPWM Burst DMA Slave PWMx Register Update Definition
  */
#define HAL_HRPWM_BurstDMASlvRegUpdTypeDef                  HAL_HRPWM_BurstDMARegUpdTypeDef             

#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_NONE                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_NONE           /*!< Burst DMA Slave PWM Register Update None    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CR0                 LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CR0            /*!< Burst DMA Slave PWM Register Update CR0     */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CR1                 LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CR1            /*!< Burst DMA Slave PWM Register Update CR1     */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_ISR                 LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ISR            /*!< Burst DMA Slave PWM Register Update ISR     */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_DIER                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_DIER           /*!< Burst DMA Slave PWM Register Update DIER    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CNTR                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CNTR           /*!< Burst DMA Slave PWM Register Update CNTR    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_PERR                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_PERR           /*!< Burst DMA Slave PWM Register Update PERR    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_REPR                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_REPR           /*!< Burst DMA Slave PWM Register Update REPR    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CMPAR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPAR          /*!< Burst DMA Slave PWM Register Update CMPAR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CMPBR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPBR          /*!< Burst DMA Slave PWM Register Update CMPBR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CMPCR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPCR          /*!< Burst DMA Slave PWM Register Update CMPCR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CMPDR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPDR          /*!< Burst DMA Slave PWM Register Update CMPDR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CAPAR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPAR          /*!< Burst DMA Slave PWM Register Update CAPAR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CAPBR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBR          /*!< Burst DMA Slave PWM Register Update CAPBR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_DTR                 LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_DTR            /*!< Burst DMA Slave PWM Register Update DTR     */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_SETAR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_SETAR          /*!< Burst DMA Slave PWM Register Update SETAR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CLRAR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CLRAR          /*!< Burst DMA Slave PWM Register Update CLRAR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_SETBR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_SETBR          /*!< Burst DMA Slave PWM Register Update SETBR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CLRBR               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CLRBR          /*!< Burst DMA Slave PWM Register Update CLRBR   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_EEFR0               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR0          /*!< Burst DMA Slave PWM Register Update EEFR0   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_EEFR1               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR1          /*!< Burst DMA Slave PWM Register Update EEFR1   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_EEFR2               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR2          /*!< Burst DMA Slave PWM Register Update EEFR2   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_RSTR                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_RSTR           /*!< Burst DMA Slave PWM Register Update RSTR    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_RSTER               LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_RSTER          /*!< Burst DMA Slave PWM Register Update RSTER   */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CHPR                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CHPR           /*!< Burst DMA Slave PWM Register Update CHPR    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CAPACR              LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPACR         /*!< Burst DMA Slave PWM Register Update CAPACR  */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CAPACER             LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPACER        /*!< Burst DMA Slave PWM Register Update CAPACER */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CAPBCR              LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBCR         /*!< Burst DMA Slave PWM Register Update CAPBCR  */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_CAPBCER             LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBCER        /*!< Burst DMA Slave PWM Register Update CAPBCER */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_OUTR                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_OUTR           /*!< Burst DMA Slave PWM Register Update OUTR    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_FLTR                LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_FLTR           /*!< Burst DMA Slave PWM Register Update FLTR    */
#define HAL_HRPWM_BURST_DMA_SLV_REG_UPD_ALL_MASK            LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL_MASK       /*!< Burst DMA Slave PWM Register Update All     */

/**
  * @brief HRPWM Common ADC Trigger Event Source Definition
  */
#define HAL_HRPWM_Comm_ADCTrigEvtSrcTypeDef                 LL_HRPWM_Comm_ADCTrigEvtSrcTypeDef    
#define HAL_HRPWM_COMM_ADC_TRIG_EVT_ALL_MASK                LL_HRPWM_COMM_ADC_TRIG_EVT_ALL_MASK

/**
  * @brief HRPWM Common ADC0/2 Trigger Event Source Definition
  */
#define HAL_HRPWM_Comm_ADC02TrigEvtSrcTypeDef               HAL_HRPWM_Comm_ADCTrigEvtSrcTypeDef               

#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_NONE                  LL_HRPWM_COMM_ADC02_TRIG_EVT_NONE                  /*!< ADC0/2 Trigger Event Source None                 */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPA          LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPA          /*!< ADC0/2 Trigger Event Source Master PWM Compare A */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPB          LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPB          /*!< ADC0/2 Trigger Event Source Master PWM Compare B */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPC          LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPC          /*!< ADC0/2 Trigger Event Source Master PWM Compare C */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPD          LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPD          /*!< ADC0/2 Trigger Event Source Master PWM Compare D */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_PRD           LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_PRD           /*!< ADC0/2 Trigger Event Source Master PWM Period    */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_0             LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_0             /*!< ADC0/2 Trigger Event Source External Event 0     */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_1             LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_1             /*!< ADC0/2 Trigger Event Source External Event 1     */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_2             LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_2             /*!< ADC0/2 Trigger Event Source External Event 2     */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_3             LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_3             /*!< ADC0/2 Trigger Event Source External Event 3     */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_4             LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_4             /*!< ADC0/2 Trigger Event Source External Event 4     */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPC             /*!< ADC0/2 Trigger Event Source PWM0 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPD             /*!< ADC0/2 Trigger Event Source PWM0 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_PRD              /*!< ADC0/2 Trigger Event Source PWM0 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_RST_ROLLOVER     LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_RST_ROLLOVER     /*!< ADC0/2 Trigger Event Source PWM0 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPC             /*!< ADC0/2 Trigger Event Source PWM1 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPD             /*!< ADC0/2 Trigger Event Source PWM1 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_PRD              /*!< ADC0/2 Trigger Event Source PWM1 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_RST_ROLLOVE      LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_RST_ROLLOVE      /*!< ADC0/2 Trigger Event Source PWM1 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPC             /*!< ADC0/2 Trigger Event Source PWM2 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPD             /*!< ADC0/2 Trigger Event Source PWM2 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_PRD              /*!< ADC0/2 Trigger Event Source PWM2 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPC             /*!< ADC0/2 Trigger Event Source PWM3 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPD             /*!< ADC0/2 Trigger Event Source PWM3 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_PRD              /*!< ADC0/2 Trigger Event Source PWM3 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPC             /*!< ADC0/2 Trigger Event Source PWM4 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPD             /*!< ADC0/2 Trigger Event Source PWM4 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_PRD              /*!< ADC0/2 Trigger Event Source PWM4 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPB             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPB             /*!< ADC0/2 Trigger Event Source PWM5 Compare B       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPC             /*!< ADC0/2 Trigger Event Source PWM5 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPD             /*!< ADC0/2 Trigger Event Source PWM5 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_PRD              /*!< ADC0/2 Trigger Event Source PWM5 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_RST_ROLLOVER     LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_RST_ROLLOVER     /*!< ADC0/2 Trigger Event Source PWM5 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPC             /*!< ADC0/2 Trigger Event Source PWM6 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPD             /*!< ADC0/2 Trigger Event Source PWM6 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_PRD              /*!< ADC0/2 Trigger Event Source PWM6 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_RST_ROLLOVER     LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_RST_ROLLOVER     /*!< ADC0/2 Trigger Event Source PWM6 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPC             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPC             /*!< ADC0/2 Trigger Event Source PWM7 Compare C       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPD             LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPD             /*!< ADC0/2 Trigger Event Source PWM7 Compare D       */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_PRD              LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_PRD              /*!< ADC0/2 Trigger Event Source PWM7 Period          */
#define HAL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_RST_ROLLOVER     LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_RST_ROLLOVER     /*!< ADC0/2 Trigger Event Source PWM7 Reset/Roll-Over */

/**
  * @brief HRPWM Common ADC1/3 Trigger Event Definition
  */
#define HAL_HRPWM_Comm_ADC13TrigEvtSrcTypeDef               HAL_HRPWM_Comm_ADCTrigEvtSrcTypeDef               

#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_NONE                  LL_HRPWM_COMM_ADC13_TRIG_EVT_NONE                  /*!< ADC1/3 Trigger Event Source None                 */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPA          LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPA          /*!< ADC1/3 Trigger Event Source Master PWM Compare A */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPB          LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPB          /*!< ADC1/3 Trigger Event Source Master PWM Compare B */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPC          LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPC          /*!< ADC1/3 Trigger Event Source Master PWM Compare C */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPD          LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPD          /*!< ADC1/3 Trigger Event Source Master PWM Compare D */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_PRD           LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_PRD           /*!< ADC1/3 Trigger Event Source Master PWM Period    */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_5             LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_5             /*!< ADC1/3 Trigger Event Source External Event 5     */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_6             LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_6             /*!< ADC1/3 Trigger Event Source External Event 6     */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_7             LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_7             /*!< ADC1/3 Trigger Event Source External Event 7     */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_8             LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_8             /*!< ADC1/3 Trigger Event Source External Event 8     */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_9             LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_9             /*!< ADC1/3 Trigger Event Source External Event 9     */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPB             /*!< ADC1/3 Trigger Event Source PWM0 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPD             /*!< ADC1/3 Trigger Event Source PWM0 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_PRD              LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_PRD              /*!< ADC1/3 Trigger Event Source PWM0 Period          */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPB             /*!< ADC1/3 Trigger Event Source PWM1 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPD             /*!< ADC1/3 Trigger Event Source PWM1 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_PRD              LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_PRD              /*!< ADC1/3 Trigger Event Source PWM1 Period          */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPB             /*!< ADC1/3 Trigger Event Source PWM2 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPD             /*!< ADC1/3 Trigger Event Source PWM2 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_PRD              LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_PRD              /*!< ADC1/3 Trigger Event Source PWM2 Period          */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_RST_ROLLOVER     LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_RST_ROLLOVER     /*!< ADC1/3 Trigger Event Source PWM2 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPB             /*!< ADC1/3 Trigger Event Source PWM3 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPD             /*!< ADC1/3 Trigger Event Source PWM3 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_PRD              LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_PRD              /*!< ADC1/3 Trigger Event Source PWM3 Period          */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_RST_ROLLOVER     LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_RST_ROLLOVER     /*!< ADC1/3 Trigger Event Source PWM3 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPB             /*!< ADC1/3 Trigger Event Source PWM4 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPC             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPC             /*!< ADC1/3 Trigger Event Source PWM4 Compare C       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPD             /*!< ADC1/3 Trigger Event Source PWM4 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_RST_ROLLOVER     LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_RST_ROLLOVER     /*!< ADC1/3 Trigger Event Source PWM4 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPB             /*!< ADC1/3 Trigger Event Source PWM5 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPC             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPC             /*!< ADC1/3 Trigger Event Source PWM5 Compare C       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPD             /*!< ADC1/3 Trigger Event Source PWM5 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_PRD              LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_PRD              /*!< ADC1/3 Trigger Event Source PWM5 Period          */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPB             /*!< ADC1/3 Trigger Event Source PWM6 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPD             /*!< ADC1/3 Trigger Event Source PWM6 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_PRD              LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_PRD              /*!< ADC1/3 Trigger Event Source PWM6 Period          */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_RST_ROLLOVER     LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_RST_ROLLOVER     /*!< ADC1/3 Trigger Event Source PWM6 Reset/Roll-Over */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPB             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPB             /*!< ADC1/3 Trigger Event Source PWM7 Compare B       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPD             LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPD             /*!< ADC1/3 Trigger Event Source PWM7 Compare D       */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_PRD              LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_PRD              /*!< ADC1/3 Trigger Event Source PWM7 Period          */
#define HAL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_RST_ROLLOVER     LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_RST_ROLLOVER     /*!< ADC1/3 Trigger Event Source PWM7 Reset/Roll-Over */

/**
  * @brief HRPWM Slave Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv_CntrRstEvtTypeDef                     LL_HRPWM_Slv_CntrRstEvtTypeDef    
#define HAL_HRPWM_SLV_CNTR_RST_EVT_ALL_MASK                 LL_HRPWM_SLV_CNTR_RST_EVT_ALL_MASK 

/**
  * @brief HRPWM Slave0 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv0_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV0_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV0_CNTR_RST_EVT_NONE                    /*!< Slave0 Counter Reset Event None                 */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPA               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPA               /*!< Slave0 Counter Reset Event PWM5 Compare A       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave0 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave0 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave0 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave0 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave0 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave0 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave0 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave0 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave0 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave0 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave0 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave0 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave0 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave0 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave0 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_UPD                /*!< Slave0 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave0 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave0 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPA               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPA               /*!< Slave0 Counter Reset Event PWM1 Compare A       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave0 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave0 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPA               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPA               /*!< Slave0 Counter Reset Event PWM2 Compare A       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave0 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave0 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPA               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPA               /*!< Slave0 Counter Reset Event PWM3 Compare A       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave0 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave0 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPA               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPA               /*!< Slave0 Counter Reset Event PWM4 Compare A       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave0 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPD               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPD               /*!< Slave0 Counter Reset Event PWM4 Compare D       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave0 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPA               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPA               /*!< Slave0 Counter Reset Event PWM6 Compare A       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave0 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave0 Counter Reset Event PWM6 Compare D       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPA               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPA               /*!< Slave0 Counter Reset Event PWM7 Compare A       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave0 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave0 Counter Reset Event PWM7 Compare D       */

/**
  * @brief HRPWM Slave1 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv1_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV1_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV1_CNTR_RST_EVT_NONE                    /*!< Slave1 Counter Reset Event None                 */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPA               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPA               /*!< Slave1 Counter Reset Event PWM5 Compare A       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave1 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave1 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave1 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave1 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave1 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave1 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave1 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave1 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave1 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave1 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave1 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave1 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave1 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave1 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave1 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_UPD                /*!< Slave1 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave1 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave1 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPA               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPA               /*!< Slave1 Counter Reset Event PWM0 Compare A       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave1 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave1 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPA               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPA               /*!< Slave1 Counter Reset Event PWM2 Compare A       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave1 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave1 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPA               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPA               /*!< Slave1 Counter Reset Event PWM3 Compare A       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave1 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave1 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPA               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPA               /*!< Slave1 Counter Reset Event PWM4 Compare A       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave1 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPD               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPD               /*!< Slave1 Counter Reset Event PWM4 Compare D       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave1 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPA               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPA               /*!< Slave1 Counter Reset Event PWM6 Compare A       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave1 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave1 Counter Reset Event PWM6 Compare D       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPA               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPA               /*!< Slave1 Counter Reset Event PWM7 Compare A       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave1 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave1 Counter Reset Event PWM7 Compare D       */

/**
  * @brief HRPWM Slave2 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv2_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV2_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV2_CNTR_RST_EVT_NONE                    /*!< Slave2 Counter Reset Event None                 */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPA               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPA               /*!< Slave2 Counter Reset Event PWM5 Compare A       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave2 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave2 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave2 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave2 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave2 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave2 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave2 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave2 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave2 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave2 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave2 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave2 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave2 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave2 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave2 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_UPD                /*!< Slave2 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave2 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave2 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPA               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPA               /*!< Slave2 Counter Reset Event PWM0 Compare A       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave2 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave2 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPA               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPA               /*!< Slave2 Counter Reset Event PWM1 Compare A       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave2 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave2 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPA               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPA               /*!< Slave2 Counter Reset Event PWM3 Compare A       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave2 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave2 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPA               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPA               /*!< Slave2 Counter Reset Event PWM4 Compare A       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave2 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPD               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPD               /*!< Slave2 Counter Reset Event PWM4 Compare D       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave2 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPA               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPA               /*!< Slave2 Counter Reset Event PWM6 Compare A       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave2 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave2 Counter Reset Event PWM6 Compare D       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPA               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPA               /*!< Slave2 Counter Reset Event PWM7 Compare A       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave2 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave2 Counter Reset Event PWM7 Compare D       */

/**
  * @brief HRPWM Slave3 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv3_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV3_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV3_CNTR_RST_EVT_NONE                    /*!< Slave3 Counter Reset Event None                 */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPA               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPA               /*!< Slave3 Counter Reset Event PWM5 Compare A       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave3 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave3 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave3 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave3 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave3 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave3 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave3 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave3 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave3 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave3 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave3 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave3 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave3 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave3 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave3 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_UPD                /*!< Slave3 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave3 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave3 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPA               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPA               /*!< Slave3 Counter Reset Event PWM0 Compare A       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave3 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave3 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPA               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPA               /*!< Slave3 Counter Reset Event PWM1 Compare A       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave3 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave3 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPA               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPA               /*!< Slave3 Counter Reset Event PWM2 Compare A       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave3 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave3 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPA               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPA               /*!< Slave3 Counter Reset Event PWM4 Compare A       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave3 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPD               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPD               /*!< Slave3 Counter Reset Event PWM4 Compare D       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave3 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPA               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPA               /*!< Slave3 Counter Reset Event PWM6 Compare A       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave3 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave3 Counter Reset Event PWM6 Compare D       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPA               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPA               /*!< Slave3 Counter Reset Event PWM7 Compare A       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave3 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave3 Counter Reset Event PWM7 Compare D       */

/**
  * @brief HRPWM Slave4 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv4_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV4_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV4_CNTR_RST_EVT_NONE                    /*!< Slave4 Counter Reset Event None                 */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPA               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPA               /*!< Slave4 Counter Reset Event PWM5 Compare A       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave4 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave4 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave4 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave4 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave4 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave4 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave4 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave4 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave4 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave4 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave4 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave4 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave4 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave4 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave4 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_UPD                /*!< Slave4 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave4 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPD               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPD               /*!< Slave4 Counter Reset Event PWM4 Compare D       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPA               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPA               /*!< Slave4 Counter Reset Event PWM0 Compare A       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave4 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave4 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPA               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPA               /*!< Slave4 Counter Reset Event PWM1 Compare A       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave4 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave4 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPA               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPA               /*!< Slave4 Counter Reset Event PWM2 Compare A       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave4 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave4 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPA               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPA               /*!< Slave4 Counter Reset Event PWM3 Compare A       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave4 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave4 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave4 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPA               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPA               /*!< Slave4 Counter Reset Event PWM6 Compare A       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave4 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave4 Counter Reset Event PWM6 Compare D       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPA               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPA               /*!< Slave4 Counter Reset Event PWM7 Compare A       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave4 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave4 Counter Reset Event PWM7 Compare D       */

/**
  * @brief HRPWM Slave5 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv5_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV5_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV5_CNTR_RST_EVT_NONE                    /*!< Slave5 Counter Reset Event None                 */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPA               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPA               /*!< Slave5 Counter Reset Event PWM4 Compare A       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave5 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave5 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave5 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave5 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave5 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave5 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave5 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave5 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave5 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave5 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave5 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave5 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave5 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave5 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave5 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_UPD                /*!< Slave5 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave5 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPD               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPD               /*!< Slave5 Counter Reset Event PWM5 Compare D       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPA               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPA               /*!< Slave5 Counter Reset Event PWM0 Compare A       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave5 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave5 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPA               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPA               /*!< Slave5 Counter Reset Event PWM1 Compare A       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave5 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave5 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPA               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPA               /*!< Slave5 Counter Reset Event PWM2 Compare A       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave5 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave5 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPA               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPA               /*!< Slave5 Counter Reset Event PWM3 Compare A       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave5 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave5 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave5 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPA               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPA               /*!< Slave5 Counter Reset Event PWM6 Compare A       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave5 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave5 Counter Reset Event PWM6 Compare D       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPA               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPA               /*!< Slave5 Counter Reset Event PWM7 Compare A       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave5 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave5 Counter Reset Event PWM7 Compare D       */

/**
  * @brief HRPWM Slave6 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv6_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV6_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV6_CNTR_RST_EVT_NONE                    /*!< Slave6 Counter Reset Event None                 */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPA               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPA               /*!< Slave6 Counter Reset Event PWM4 Compare A       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave6 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave6 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave6 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave6 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave6 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave6 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave6 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave6 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave6 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave6 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave6 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave6 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave6 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave6 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave6 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_UPD                /*!< Slave6 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave6 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave6 Counter Reset Event PWM6 Compare D       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPA               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPA               /*!< Slave6 Counter Reset Event PWM0 Compare A       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave6 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave6 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPA               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPA               /*!< Slave6 Counter Reset Event PWM1 Compare A       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave6 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave6 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPA               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPA               /*!< Slave6 Counter Reset Event PWM2 Compare A       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave6 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave6 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPA               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPA               /*!< Slave6 Counter Reset Event PWM3 Compare A       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave6 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave6 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave6 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPA               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPA               /*!< Slave6 Counter Reset Event PWM5 Compare A       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave6 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPD               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPD               /*!< Slave6 Counter Reset Event PWM5 Compare D       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPA               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPA               /*!< Slave6 Counter Reset Event PWM7 Compare A       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave6 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave6 Counter Reset Event PWM7 Compare D       */

/**
  * @brief HRPWM Slave7 Counter Reset Event Definition
  */
#define HAL_HRPWM_Slv7_CntrRstEvtTypeDef                    HAL_HRPWM_Slv_CntrRstEvtTypeDef                    

#define HAL_HRPWM_SLV7_CNTR_RST_EVT_NONE                    LL_HRPWM_SLV7_CNTR_RST_EVT_NONE                    /*!< Slave7 Counter Reset Event None                 */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPA               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPA               /*!< Slave7 Counter Reset Event PWM4 Compare A       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPA            LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPA            /*!< Slave7 Counter Reset Event Master PWM Compare A */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPB            LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPB            /*!< Slave7 Counter Reset Event Master PWM Compare B */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPC            LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPC            /*!< Slave7 Counter Reset Event Master PWM Compare C */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPD            LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPD            /*!< Slave7 Counter Reset Event Master PWM Compare D */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_PRD             LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_PRD             /*!< Slave7 Counter Reset Event Master PWM Period    */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT0               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT0               /*!< Slave7 Counter Reset Event PWMx Event 0         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT1               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT1               /*!< Slave7 Counter Reset Event PWMx Event 1         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT2               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT2               /*!< Slave7 Counter Reset Event PWMx Event 2         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT3               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT3               /*!< Slave7 Counter Reset Event PWMx Event 3         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT4               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT4               /*!< Slave7 Counter Reset Event PWMx Event 4         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT5               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT5               /*!< Slave7 Counter Reset Event PWMx Event 5         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT6               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT6               /*!< Slave7 Counter Reset Event PWMx Event 6         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT7               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT7               /*!< Slave7 Counter Reset Event PWMx Event 7         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT8               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT8               /*!< Slave7 Counter Reset Event PWMx Event 8         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT9               LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT9               /*!< Slave7 Counter Reset Event PWMx Event 9         */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_UPD                LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_UPD                /*!< Slave7 Counter Reset Event PWMx Update          */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPB               /*!< Slave7 Counter Reset Event PWM7 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPD               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPD               /*!< Slave7 Counter Reset Event PWM7 Compare D       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPA               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPA               /*!< Slave7 Counter Reset Event PWM0 Compare A       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPB               /*!< Slave7 Counter Reset Event PWM0 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPD               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPD               /*!< Slave7 Counter Reset Event PWM0 Compare D       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPA               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPA               /*!< Slave7 Counter Reset Event PWM1 Compare A       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPB               /*!< Slave7 Counter Reset Event PWM1 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPD               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPD               /*!< Slave7 Counter Reset Event PWM1 Compare D       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPA               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPA               /*!< Slave7 Counter Reset Event PWM2 Compare A       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPB               /*!< Slave7 Counter Reset Event PWM2 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPD               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPD               /*!< Slave7 Counter Reset Event PWM2 Compare D       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPA               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPA               /*!< Slave7 Counter Reset Event PWM3 Compare A       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPB               /*!< Slave7 Counter Reset Event PWM3 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPD               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPD               /*!< Slave7 Counter Reset Event PWM3 Compare D       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPB               /*!< Slave7 Counter Reset Event PWM4 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPA               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPA               /*!< Slave7 Counter Reset Event PWM5 Compare A       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPB               /*!< Slave7 Counter Reset Event PWM5 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPD               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPD               /*!< Slave7 Counter Reset Event PWM5 Compare D       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPA               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPA               /*!< Slave7 Counter Reset Event PWM6 Compare A       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPB               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPB               /*!< Slave7 Counter Reset Event PWM6 Compare B       */
#define HAL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPD               LL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPD               /*!< Slave7 Counter Reset Event PWM6 Compare D       */

/**
  * @brief HRPWM Slave Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv_CapTrigEvtTypeDef                     LL_HRPWM_Slv_CapTrigEvtTypeDef    
#define HAL_HRPWM_SLV_CAP_TRIG_EVT_ALL_MASK                 LL_HRPWM_SLV_CAP_TRIG_EVT_ALL_MASK 

/**
  * @brief HRPWM Slave0 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv0_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV0_CAP_TRIG_EVT_NONE                    /*!< Slave0 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV0_CAP_TRIG_EVT_SW_CAP                  /*!< Slave0 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave0 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave0 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave0 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave0 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave0 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave0 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave0 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave0 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave0 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave0 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave0 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_SET           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_SET           /*!< Slave0 Capture A/B Trigger Event PWM1 OutA Set    */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_CLR           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_CLR           /*!< Slave0 Capture A/B Trigger Event PWM1 OutA Clear  */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPA               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPA               /*!< Slave0 Capture A/B Trigger Event PWM1 Compare A   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPB               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPB               /*!< Slave0 Capture A/B Trigger Event PWM1 Compare B   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_SET           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_SET           /*!< Slave0 Capture A/B Trigger Event PWM2 OutA Set    */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_CLR           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_CLR           /*!< Slave0 Capture A/B Trigger Event PWM2 OutA Clear  */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPA               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPA               /*!< Slave0 Capture A/B Trigger Event PWM2 Compare A   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPB               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPB               /*!< Slave0 Capture A/B Trigger Event PWM2 Compare B   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_SET           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_SET           /*!< Slave0 Capture A/B Trigger Event PWM3 OutA Set    */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_CLR           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_CLR           /*!< Slave0 Capture A/B Trigger Event PWM3 OutA Clear  */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPA               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPA               /*!< Slave0 Capture A/B Trigger Event PWM3 Compare A   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPB               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPB               /*!< Slave0 Capture A/B Trigger Event PWM3 Compare B   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_SET           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_SET           /*!< Slave0 Capture A/B Trigger Event PWM4 OutA Set    */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_CLR           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_CLR           /*!< Slave0 Capture A/B Trigger Event PWM4 OutA Clear  */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPA               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPA               /*!< Slave0 Capture A/B Trigger Event PWM4 Compare A   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPB               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPB               /*!< Slave0 Capture A/B Trigger Event PWM4 Compare B   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_SET           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_SET           /*!< Slave0 Capture A/B Trigger Event PWM5 OutA Set    */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_CLR           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_CLR           /*!< Slave0 Capture A/B Trigger Event PWM5 OutA Clear  */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPA               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPA               /*!< Slave0 Capture A/B Trigger Event PWM5 Compare A   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPB               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPB               /*!< Slave0 Capture A/B Trigger Event PWM5 Compare B   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_SET           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_SET           /*!< Slave0 Capture A/B Trigger Event PWM6 OutA Set    */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_CLR           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_CLR           /*!< Slave0 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPA               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPA               /*!< Slave0 Capture A/B Trigger Event PWM6 Compare A   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPB               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPB               /*!< Slave0 Capture A/B Trigger Event PWM6 Compare B   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_SET           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_SET           /*!< Slave0 Capture A/B Trigger Event PWM7 OutA Set    */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_CLR           LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_CLR           /*!< Slave0 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPA               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPA               /*!< Slave0 Capture A/B Trigger Event PWM7 Compare A   */
#define HAL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPB               LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPB               /*!< Slave0 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave1 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv1_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV1_CAP_TRIG_EVT_NONE                    /*!< Slave1 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV1_CAP_TRIG_EVT_SW_CAP                  /*!< Slave1 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave1 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave1 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave1 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave1 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave1 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave1 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave1 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave1 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave1 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave1 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave1 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_SET           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_SET           /*!< Slave1 Capture A/B Trigger Event PWM0 OutA Set    */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_CLR           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_CLR           /*!< Slave1 Capture A/B Trigger Event PWM0 OutA Clear  */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPA               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPA               /*!< Slave1 Capture A/B Trigger Event PWM0 Compare A   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPB               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPB               /*!< Slave1 Capture A/B Trigger Event PWM0 Compare B   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_SET           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_SET           /*!< Slave1 Capture A/B Trigger Event PWM2 OutA Set    */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_CLR           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_CLR           /*!< Slave1 Capture A/B Trigger Event PWM2 OutA Clear  */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPA               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPA               /*!< Slave1 Capture A/B Trigger Event PWM2 Compare A   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPB               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPB               /*!< Slave1 Capture A/B Trigger Event PWM2 Compare B   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_SET           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_SET           /*!< Slave1 Capture A/B Trigger Event PWM3 OutA Set    */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_CLR           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_CLR           /*!< Slave1 Capture A/B Trigger Event PWM3 OutA Clear  */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPA               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPA               /*!< Slave1 Capture A/B Trigger Event PWM3 Compare A   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPB               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPB               /*!< Slave1 Capture A/B Trigger Event PWM3 Compare B   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_SET           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_SET           /*!< Slave1 Capture A/B Trigger Event PWM4 OutA Set    */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_CLR           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_CLR           /*!< Slave1 Capture A/B Trigger Event PWM4 OutA Clear  */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPA               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPA               /*!< Slave1 Capture A/B Trigger Event PWM4 Compare A   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPB               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPB               /*!< Slave1 Capture A/B Trigger Event PWM4 Compare B   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_SET           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_SET           /*!< Slave1 Capture A/B Trigger Event PWM5 OutA Set    */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_CLR           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_CLR           /*!< Slave1 Capture A/B Trigger Event PWM5 OutA Clear  */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPA               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPA               /*!< Slave1 Capture A/B Trigger Event PWM5 Compare A   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPB               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPB               /*!< Slave1 Capture A/B Trigger Event PWM5 Compare B   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_SET           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_SET           /*!< Slave1 Capture A/B Trigger Event PWM6 OutA Set    */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_CLR           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_CLR           /*!< Slave1 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPA               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPA               /*!< Slave1 Capture A/B Trigger Event PWM6 Compare A   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPB               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPB               /*!< Slave1 Capture A/B Trigger Event PWM6 Compare B   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_SET           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_SET           /*!< Slave1 Capture A/B Trigger Event PWM7 OutA Set    */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_CLR           LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_CLR           /*!< Slave1 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPA               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPA               /*!< Slave1 Capture A/B Trigger Event PWM7 Compare A   */
#define HAL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPB               LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPB               /*!< Slave1 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave2 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv2_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV2_CAP_TRIG_EVT_NONE                    /*!< Slave2 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV2_CAP_TRIG_EVT_SW_CAP                  /*!< Slave2 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave2 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave2 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave2 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave2 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave2 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave2 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave2 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave2 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave2 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave2 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave2 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_SET           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_SET           /*!< Slave2 Capture A/B Trigger Event PWM0 OutA Set    */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_CLR           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_CLR           /*!< Slave2 Capture A/B Trigger Event PWM0 OutA Clear  */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPA               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPA               /*!< Slave2 Capture A/B Trigger Event PWM0 Compare A   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPB               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPB               /*!< Slave2 Capture A/B Trigger Event PWM0 Compare B   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_SET           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_SET           /*!< Slave2 Capture A/B Trigger Event PWM1 OutA Set    */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_CLR           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_CLR           /*!< Slave2 Capture A/B Trigger Event PWM1 OutA Clear  */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPA               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPA               /*!< Slave2 Capture A/B Trigger Event PWM1 Compare A   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPB               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPB               /*!< Slave2 Capture A/B Trigger Event PWM1 Compare B   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_SET           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_SET           /*!< Slave2 Capture A/B Trigger Event PWM3 OutA Set    */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_CLR           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_CLR           /*!< Slave2 Capture A/B Trigger Event PWM3 OutA Clear  */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPA               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPA               /*!< Slave2 Capture A/B Trigger Event PWM3 Compare A   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPB               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPB               /*!< Slave2 Capture A/B Trigger Event PWM3 Compare B   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_SET           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_SET           /*!< Slave2 Capture A/B Trigger Event PWM4 OutA Set    */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_CLR           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_CLR           /*!< Slave2 Capture A/B Trigger Event PWM4 OutA Clear  */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPA               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPA               /*!< Slave2 Capture A/B Trigger Event PWM4 Compare A   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPB               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPB               /*!< Slave2 Capture A/B Trigger Event PWM4 Compare B   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_SET           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_SET           /*!< Slave2 Capture A/B Trigger Event PWM5 OutA Set    */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_CLR           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_CLR           /*!< Slave2 Capture A/B Trigger Event PWM5 OutA Clear  */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPA               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPA               /*!< Slave2 Capture A/B Trigger Event PWM5 Compare A   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPB               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPB               /*!< Slave2 Capture A/B Trigger Event PWM5 Compare B   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_SET           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_SET           /*!< Slave2 Capture A/B Trigger Event PWM6 OutA Set    */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_CLR           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_CLR           /*!< Slave2 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPA               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPA               /*!< Slave2 Capture A/B Trigger Event PWM6 Compare A   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPB               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPB               /*!< Slave2 Capture A/B Trigger Event PWM6 Compare B   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_SET           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_SET           /*!< Slave2 Capture A/B Trigger Event PWM7 OutA Set    */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_CLR           LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_CLR           /*!< Slave2 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPA               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPA               /*!< Slave2 Capture A/B Trigger Event PWM7 Compare A   */
#define HAL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPB               LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPB               /*!< Slave2 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave3 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv3_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV3_CAP_TRIG_EVT_NONE                    /*!< Slave3 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV3_CAP_TRIG_EVT_SW_CAP                  /*!< Slave3 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave3 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave3 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave3 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave3 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave3 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave3 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave3 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave3 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave3 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave3 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave3 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_SET           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_SET           /*!< Slave3 Capture A/B Trigger Event PWM0 OutA Set    */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_CLR           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_CLR           /*!< Slave3 Capture A/B Trigger Event PWM0 OutA Clear  */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPA               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPA               /*!< Slave3 Capture A/B Trigger Event PWM0 Compare A   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPB               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPB               /*!< Slave3 Capture A/B Trigger Event PWM0 Compare B   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_SET           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_SET           /*!< Slave3 Capture A/B Trigger Event PWM1 OutA Set    */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_CLR           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_CLR           /*!< Slave3 Capture A/B Trigger Event PWM1 OutA Clear  */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPA               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPA               /*!< Slave3 Capture A/B Trigger Event PWM1 Compare A   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPB               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPB               /*!< Slave3 Capture A/B Trigger Event PWM1 Compare B   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_SET           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_SET           /*!< Slave3 Capture A/B Trigger Event PWM2 OutA Set    */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_CLR           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_CLR           /*!< Slave3 Capture A/B Trigger Event PWM2 OutA Clear  */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPA               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPA               /*!< Slave3 Capture A/B Trigger Event PWM2 Compare A   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPB               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPB               /*!< Slave3 Capture A/B Trigger Event PWM2 Compare B   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_SET           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_SET           /*!< Slave3 Capture A/B Trigger Event PWM4 OutA Set    */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_CLR           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_CLR           /*!< Slave3 Capture A/B Trigger Event PWM4 OutA Clear  */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPA               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPA               /*!< Slave3 Capture A/B Trigger Event PWM4 Compare A   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPB               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPB               /*!< Slave3 Capture A/B Trigger Event PWM4 Compare B   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_SET           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_SET           /*!< Slave3 Capture A/B Trigger Event PWM5 OutA Set    */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_CLR           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_CLR           /*!< Slave3 Capture A/B Trigger Event PWM5 OutA Clear  */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPA               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPA               /*!< Slave3 Capture A/B Trigger Event PWM5 Compare A   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPB               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPB               /*!< Slave3 Capture A/B Trigger Event PWM5 Compare B   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_SET           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_SET           /*!< Slave3 Capture A/B Trigger Event PWM6 OutA Set    */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_CLR           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_CLR           /*!< Slave3 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPA               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPA               /*!< Slave3 Capture A/B Trigger Event PWM6 Compare A   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPB               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPB               /*!< Slave3 Capture A/B Trigger Event PWM6 Compare B   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_SET           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_SET           /*!< Slave3 Capture A/B Trigger Event PWM7 OutA Set    */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_CLR           LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_CLR           /*!< Slave3 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPA               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPA               /*!< Slave3 Capture A/B Trigger Event PWM7 Compare A   */
#define HAL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPB               LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPB               /*!< Slave3 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave4 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv4_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV4_CAP_TRIG_EVT_NONE                    /*!< Slave4 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV4_CAP_TRIG_EVT_SW_CAP                  /*!< Slave4 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave4 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave4 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave4 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave4 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave4 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave4 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave4 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave4 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave4 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave4 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave4 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_SET           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_SET           /*!< Slave4 Capture A/B Trigger Event PWM0 OutA Set    */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_CLR           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_CLR           /*!< Slave4 Capture A/B Trigger Event PWM0 OutA Clear  */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPA               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPA               /*!< Slave4 Capture A/B Trigger Event PWM0 Compare A   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPB               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPB               /*!< Slave4 Capture A/B Trigger Event PWM0 Compare B   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_SET           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_SET           /*!< Slave4 Capture A/B Trigger Event PWM1 OutA Set    */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_CLR           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_CLR           /*!< Slave4 Capture A/B Trigger Event PWM1 OutA Clear  */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPA               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPA               /*!< Slave4 Capture A/B Trigger Event PWM1 Compare A   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPB               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPB               /*!< Slave4 Capture A/B Trigger Event PWM1 Compare B   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_SET           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_SET           /*!< Slave4 Capture A/B Trigger Event PWM2 OutA Set    */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_CLR           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_CLR           /*!< Slave4 Capture A/B Trigger Event PWM2 OutA Clear  */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPA               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPA               /*!< Slave4 Capture A/B Trigger Event PWM2 Compare A   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPB               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPB               /*!< Slave4 Capture A/B Trigger Event PWM2 Compare B   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_SET           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_SET           /*!< Slave4 Capture A/B Trigger Event PWM3 OutA Set    */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_CLR           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_CLR           /*!< Slave4 Capture A/B Trigger Event PWM3 OutA Clear  */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPA               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPA               /*!< Slave4 Capture A/B Trigger Event PWM3 Compare A   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPB               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPB               /*!< Slave4 Capture A/B Trigger Event PWM3 Compare B   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_SET           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_SET           /*!< Slave4 Capture A/B Trigger Event PWM5 OutA Set    */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_CLR           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_CLR           /*!< Slave4 Capture A/B Trigger Event PWM5 OutA Clear  */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPA               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPA               /*!< Slave4 Capture A/B Trigger Event PWM5 Compare A   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPB               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPB               /*!< Slave4 Capture A/B Trigger Event PWM5 Compare B   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_SET           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_SET           /*!< Slave4 Capture A/B Trigger Event PWM6 OutA Set    */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_CLR           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_CLR           /*!< Slave4 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPA               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPA               /*!< Slave4 Capture A/B Trigger Event PWM6 Compare A   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPB               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPB               /*!< Slave4 Capture A/B Trigger Event PWM6 Compare B   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_SET           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_SET           /*!< Slave4 Capture A/B Trigger Event PWM7 OutA Set    */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_CLR           LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_CLR           /*!< Slave4 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPA               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPA               /*!< Slave4 Capture A/B Trigger Event PWM7 Compare A   */
#define HAL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPB               LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPB               /*!< Slave4 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave5 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv5_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV5_CAP_TRIG_EVT_NONE                    /*!< Slave5 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV5_CAP_TRIG_EVT_SW_CAP                  /*!< Slave5 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave5 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave5 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave5 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave5 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave5 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave5 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave5 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave5 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave5 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave5 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave5 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_SET           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_SET           /*!< Slave5 Capture A/B Trigger Event PWM0 OutA Set    */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_CLR           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_CLR           /*!< Slave5 Capture A/B Trigger Event PWM0 OutA Clear  */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPA               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPA               /*!< Slave5 Capture A/B Trigger Event PWM0 Compare A   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPB               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPB               /*!< Slave5 Capture A/B Trigger Event PWM0 Compare B   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_SET           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_SET           /*!< Slave5 Capture A/B Trigger Event PWM1 OutA Set    */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_CLR           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_CLR           /*!< Slave5 Capture A/B Trigger Event PWM1 OutA Clear  */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPA               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPA               /*!< Slave5 Capture A/B Trigger Event PWM1 Compare A   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPB               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPB               /*!< Slave5 Capture A/B Trigger Event PWM1 Compare B   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_SET           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_SET           /*!< Slave5 Capture A/B Trigger Event PWM2 OutA Set    */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_CLR           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_CLR           /*!< Slave5 Capture A/B Trigger Event PWM2 OutA Clear  */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPA               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPA               /*!< Slave5 Capture A/B Trigger Event PWM2 Compare A   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPB               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPB               /*!< Slave5 Capture A/B Trigger Event PWM2 Compare B   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_SET           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_SET           /*!< Slave5 Capture A/B Trigger Event PWM3 OutA Set    */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_CLR           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_CLR           /*!< Slave5 Capture A/B Trigger Event PWM3 OutA Clear  */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPA               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPA               /*!< Slave5 Capture A/B Trigger Event PWM3 Compare A   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPB               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPB               /*!< Slave5 Capture A/B Trigger Event PWM3 Compare B   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_SET           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_SET           /*!< Slave5 Capture A/B Trigger Event PWM4 OutA Set    */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_CLR           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_CLR           /*!< Slave5 Capture A/B Trigger Event PWM4 OutA Clear  */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPA               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPA               /*!< Slave5 Capture A/B Trigger Event PWM4 Compare A   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPB               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPB               /*!< Slave5 Capture A/B Trigger Event PWM4 Compare B   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_SET           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_SET           /*!< Slave5 Capture A/B Trigger Event PWM6 OutA Set    */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_CLR           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_CLR           /*!< Slave5 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPA               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPA               /*!< Slave5 Capture A/B Trigger Event PWM6 Compare A   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPB               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPB               /*!< Slave5 Capture A/B Trigger Event PWM6 Compare B   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_SET           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_SET           /*!< Slave5 Capture A/B Trigger Event PWM7 OutA Set    */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_CLR           LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_CLR           /*!< Slave5 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPA               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPA               /*!< Slave5 Capture A/B Trigger Event PWM7 Compare A   */
#define HAL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPB               LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPB               /*!< Slave5 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave6 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv6_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV6_CAP_TRIG_EVT_NONE                    /*!< Slave6 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV6_CAP_TRIG_EVT_SW_CAP                  /*!< Slave6 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave6 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave6 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave6 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave6 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave6 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave6 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave6 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave6 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave6 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave6 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave6 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_SET           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_SET           /*!< Slave6 Capture A/B Trigger Event PWM0 OutA Set    */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_CLR           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_CLR           /*!< Slave6 Capture A/B Trigger Event PWM0 OutA Clear  */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPA               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPA               /*!< Slave6 Capture A/B Trigger Event PWM0 Compare A   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPB               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPB               /*!< Slave6 Capture A/B Trigger Event PWM0 Compare B   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_SET           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_SET           /*!< Slave6 Capture A/B Trigger Event PWM1 OutA Set    */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_CLR           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_CLR           /*!< Slave6 Capture A/B Trigger Event PWM1 OutA Clear  */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPA               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPA               /*!< Slave6 Capture A/B Trigger Event PWM1 Compare A   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPB               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPB               /*!< Slave6 Capture A/B Trigger Event PWM1 Compare B   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_SET           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_SET           /*!< Slave6 Capture A/B Trigger Event PWM2 OutA Set    */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_CLR           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_CLR           /*!< Slave6 Capture A/B Trigger Event PWM2 OutA Clear  */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPA               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPA               /*!< Slave6 Capture A/B Trigger Event PWM2 Compare A   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPB               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPB               /*!< Slave6 Capture A/B Trigger Event PWM2 Compare B   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_SET           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_SET           /*!< Slave6 Capture A/B Trigger Event PWM3 OutA Set    */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_CLR           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_CLR           /*!< Slave6 Capture A/B Trigger Event PWM3 OutA Clear  */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPA               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPA               /*!< Slave6 Capture A/B Trigger Event PWM3 Compare A   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPB               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPB               /*!< Slave6 Capture A/B Trigger Event PWM3 Compare B   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_SET           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_SET           /*!< Slave6 Capture A/B Trigger Event PWM4 OutA Set    */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_CLR           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_CLR           /*!< Slave6 Capture A/B Trigger Event PWM4 OutA Clear  */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPA               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPA               /*!< Slave6 Capture A/B Trigger Event PWM4 Compare A   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPB               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPB               /*!< Slave6 Capture A/B Trigger Event PWM4 Compare B   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_SET           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_SET           /*!< Slave6 Capture A/B Trigger Event PWM5 OutA Set    */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_CLR           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_CLR           /*!< Slave6 Capture A/B Trigger Event PWM5 OutA Clear  */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPA               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPA               /*!< Slave6 Capture A/B Trigger Event PWM5 Compare A   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPB               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPB               /*!< Slave6 Capture A/B Trigger Event PWM5 Compare B   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_SET           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_SET           /*!< Slave6 Capture A/B Trigger Event PWM7 OutA Set    */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_CLR           LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_CLR           /*!< Slave6 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPA               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPA               /*!< Slave6 Capture A/B Trigger Event PWM7 Compare A   */
#define HAL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPB               LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPB               /*!< Slave6 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave7 Capture A/B Trigger Event Definition
  */
#define HAL_HRPWM_Slv7_CapTrigEvtTypeDef                    HAL_HRPWM_Slv_CapTrigEvtTypeDef                    

#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_NONE                    LL_HRPWM_SLV7_CAP_TRIG_EVT_NONE                    /*!< Slave7 Capture A/B Trigger Event None             */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_SW_CAP                  LL_HRPWM_SLV7_CAP_TRIG_EVT_SW_CAP                  /*!< Slave7 Capture A/B Trigger Event Software Capture */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_UPD                LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_UPD                /*!< Slave7 Capture A/B Trigger Event PWMx Update      */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT0               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT0               /*!< Slave7 Capture A/B Trigger Event PWMx Event 0     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT1               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT1               /*!< Slave7 Capture A/B Trigger Event PWMx Event 1     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT2               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT2               /*!< Slave7 Capture A/B Trigger Event PWMx Event 2     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT3               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT3               /*!< Slave7 Capture A/B Trigger Event PWMx Event 3     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT4               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT4               /*!< Slave7 Capture A/B Trigger Event PWMx Event 4     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT5               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT5               /*!< Slave7 Capture A/B Trigger Event PWMx Event 5     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT6               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT6               /*!< Slave7 Capture A/B Trigger Event PWMx Event 6     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT7               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT7               /*!< Slave7 Capture A/B Trigger Event PWMx Event 7     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT8               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT8               /*!< Slave7 Capture A/B Trigger Event PWMx Event 8     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT9               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT9               /*!< Slave7 Capture A/B Trigger Event PWMx Event 9     */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_SET           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_SET           /*!< Slave7 Capture A/B Trigger Event PWM0 OutA Set    */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_CLR           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_CLR           /*!< Slave7 Capture A/B Trigger Event PWM0 OutA Clear  */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPA               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPA               /*!< Slave7 Capture A/B Trigger Event PWM0 Compare A   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPB               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPB               /*!< Slave7 Capture A/B Trigger Event PWM0 Compare B   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_SET           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_SET           /*!< Slave7 Capture A/B Trigger Event PWM1 OutA Set    */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_CLR           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_CLR           /*!< Slave7 Capture A/B Trigger Event PWM1 OutA Clear  */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPA               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPA               /*!< Slave7 Capture A/B Trigger Event PWM1 Compare A   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPB               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPB               /*!< Slave7 Capture A/B Trigger Event PWM1 Compare B   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_SET           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_SET           /*!< Slave7 Capture A/B Trigger Event PWM2 OutA Set    */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_CLR           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_CLR           /*!< Slave7 Capture A/B Trigger Event PWM2 OutA Clear  */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPA               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPA               /*!< Slave7 Capture A/B Trigger Event PWM2 Compare A   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPB               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPB               /*!< Slave7 Capture A/B Trigger Event PWM2 Compare B   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_SET           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_SET           /*!< Slave7 Capture A/B Trigger Event PWM3 OutA Set    */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_CLR           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_CLR           /*!< Slave7 Capture A/B Trigger Event PWM3 OutA Clear  */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPA               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPA               /*!< Slave7 Capture A/B Trigger Event PWM3 Compare A   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPB               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPB               /*!< Slave7 Capture A/B Trigger Event PWM3 Compare B   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_SET           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_SET           /*!< Slave7 Capture A/B Trigger Event PWM4 OutA Set    */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_CLR           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_CLR           /*!< Slave7 Capture A/B Trigger Event PWM4 OutA Clear  */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPA               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPA               /*!< Slave7 Capture A/B Trigger Event PWM4 Compare A   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPB               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPB               /*!< Slave7 Capture A/B Trigger Event PWM4 Compare B   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_SET           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_SET           /*!< Slave7 Capture A/B Trigger Event PWM5 OutA Set    */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_CLR           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_CLR           /*!< Slave7 Capture A/B Trigger Event PWM5 OutA Clear  */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPA               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPA               /*!< Slave7 Capture A/B Trigger Event PWM5 Compare A   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPB               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPB               /*!< Slave7 Capture A/B Trigger Event PWM5 Compare B   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_SET           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_SET           /*!< Slave7 Capture A/B Trigger Event PWM6 OutA Set    */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_CLR           LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_CLR           /*!< Slave7 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPA               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPA               /*!< Slave7 Capture A/B Trigger Event PWM6 Compare A   */
#define HAL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPB               LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPB               /*!< Slave7 Capture A/B Trigger Event PWM6 Compare B   */

/**
  * @brief HRPWM Burst Mode Trigger Event Definition
  */
#define HAL_HRPWM_BurstTrigEvtTypeDef                       LL_HRPWM_Comm_BurstTrigEvtTypeDef                  

#define HAL_HRPWM_BURST_TRIG_EVT_NONE                       LL_HRPWM_COMM_BURST_TRIG_EVT_NONE                  /*!< Burst Mode Trigger Event None                       */
#define HAL_HRPWM_BURST_TRIG_EVT_SW                         LL_HRPWM_COMM_BURST_TRIG_EVT_SW                    /*!< Burst Mode Trigger Event Software                   */
#define HAL_HRPWM_BURST_TRIG_EVT_MST_PWM_RST_ROLLOVER       LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_RST_ROLLOVER  /*!< Burst Mode Trigger Event Master PWM Reset Roll-Over */
#define HAL_HRPWM_BURST_TRIG_EVT_MST_PWM_REP                LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_REP           /*!< Burst Mode Trigger Event Master PWM Repetition      */
#define HAL_HRPWM_BURST_TRIG_EVT_MST_PWM_CMPA               LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPA          /*!< Burst Mode Trigger Event Master PWM Compare A       */
#define HAL_HRPWM_BURST_TRIG_EVT_MST_PWM_CMPB               LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPB          /*!< Burst Mode Trigger Event Master PWM Compare B       */
#define HAL_HRPWM_BURST_TRIG_EVT_MST_PWM_CMPC               LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPC          /*!< Burst Mode Trigger Event Master PWM Compare C       */
#define HAL_HRPWM_BURST_TRIG_EVT_MST_PWM_CMPD               LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPD          /*!< Burst Mode Trigger Event Master PWM Compare D       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM0_RST_ROLLOVER          LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_RST_ROLLOVER     /*!< Burst Mode Trigger Event PWM0 Reset Roll-Over       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM0_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_REP              /*!< Burst Mode Trigger Event PWM0 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM0_CMPA                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_CMPA             /*!< Burst Mode Trigger Event PWM0 Compare A             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM0_CMPB                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_CMPB             /*!< Burst Mode Trigger Event PWM0 Compare B             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM1_RST_ROLLOVER          LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_RST_ROLLOVER     /*!< Burst Mode Trigger Event PWM1 Reset Roll-Over       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM1_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_REP              /*!< Burst Mode Trigger Event PWM1 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM1_CMPA                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_CMPA             /*!< Burst Mode Trigger Event PWM1 Compare A             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM1_CMPB                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_CMPB             /*!< Burst Mode Trigger Event PWM1 Compare B             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM2_RST_ROLLOVER          LL_HRPWM_COMM_BURST_TRIG_EVT_PWM2_RST_ROLLOVER     /*!< Burst Mode Trigger Event PWM2 Reset Roll-Over       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM2_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM2_REP              /*!< Burst Mode Trigger Event PWM2 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM2_CMPA                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM2_CMPA             /*!< Burst Mode Trigger Event PWM2 Compare A             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM3_RST_ROLLOVER          LL_HRPWM_COMM_BURST_TRIG_EVT_PWM3_RST_ROLLOVER     /*!< Burst Mode Trigger Event PWM3 Reset Roll-Over       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM3_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM3_REP              /*!< Burst Mode Trigger Event PWM3 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM3_CMPB                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM3_CMPB             /*!< Burst Mode Trigger Event PWM3 Compare B             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM4_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_REP              /*!< Burst Mode Trigger Event PWM4 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM4_CMPA                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_CMPA             /*!< Burst Mode Trigger Event PWM4 Compare A             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM4_CMPB                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_CMPB             /*!< Burst Mode Trigger Event PWM4 Compare B             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM5_RST_ROLLOVER          LL_HRPWM_COMM_BURST_TRIG_EVT_PWM5_RST_ROLLOVER     /*!< Burst Mode Trigger Event PWM5 Reset Roll-Over       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM5_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM5_REP              /*!< Burst Mode Trigger Event PWM5 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM5_CMPA                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM5_CMPA             /*!< Burst Mode Trigger Event PWM5 Compare A             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM0_PRD_EVT7              LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_PRD_EVT7         /*!< Burst Mode Trigger Event PWM0 Event 7 after Period  */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM4_PRD_EVT8              LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_PRD_EVT8         /*!< Burst Mode Trigger Event PWM4 Event 8 after Period  */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM0_EVT7                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_EVT7             /*!< Burst Mode Trigger Event PWM0 Event 7               */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM4_EVT8                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_EVT8             /*!< Burst Mode Trigger Event PWM4 Event 8               */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM_BM_IN2                 LL_HRPWM_COMM_BURST_TRIG_EVT_PWM_BM_IN2            /*!< Burst Mode Trigger Event hrpwm_bm_in2               */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM6_RST_ROLLOVER          LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_RST_ROLLOVER     /*!< Burst Mode Trigger Event PWM6 Reset Roll-Over       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM6_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_REP              /*!< Burst Mode Trigger Event PWM6 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM6_CMPA                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_CMPA             /*!< Burst Mode Trigger Event PWM6 Compare A             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM6_CMPB                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_CMPB             /*!< Burst Mode Trigger Event PWM6 Compare B             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM7_RST_ROLLOVER          LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_RST_ROLLOVER     /*!< Burst Mode Trigger Event PWM7 Reset Roll-Over       */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM7_REP                   LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_REP              /*!< Burst Mode Trigger Event PWM7 Repetition            */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM7_CMPA                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_CMPA             /*!< Burst Mode Trigger Event PWM7 Compare A             */
#define HAL_HRPWM_BURST_TRIG_EVT_PWM7_CMPB                  LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_CMPB             /*!< Burst Mode Trigger Event PWM7 Compare B             */
/**
  * @}
  */ /* HRPWM_HAL_EM_Mask */

/**
  * @}
  */ /* HRPWM_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup HRPWM_HAL_Exported_Types HRPWM HAL Exported Types
  * @brief    HRPWM HAL Exported Types
  * @{
  */

/**
  * @brief  HAL TIM Global States definition.
  */
typedef enum
{
  HAL_HRPWM_STATE_RESET   = 0U,             /*!< Peripheral not yet initialized                     */
  HAL_HRPWM_STATE_INIT    = (1UL << 30U),   /*!< Peripheral initialized but not yet configured      */
  HAL_HRPWM_STATE_IDLE    = (1UL << 29U),   /*!< Peripheral initialized and a global config applied */
  HAL_HRPWM_STATE_ACTIVE  = (1UL << 28U),   /*!< Counter is running                                 */
} HAL_HRPWM_StateTypeDef;

/**
  * @brief HRPWM Function Enable Definition
  */
typedef enum
{
    HAL_HRPWM_FUNC_DISABLE  = 0U,    /*!< HRPWM Function Disable  */
    HAL_HRPWM_FUNC_ENABLE   = 1U     /*!< HRPWM Function Enable   */
} HAL_HRPWM_EnableTypeDef;

/**
  * @brief HRPWM PWM Group Definition
  */
typedef enum
{
    HAL_HRPWM_GRP_MASTER  = 0U,   /*!< HRPWM Master   */
    HAL_HRPWM_GRP_SLAVE   = 1U,   /*!< HRPWM Slave    */
    HAL_HRPWM_GRP_COMMON  = 2,    /*!< HRPWM Common   */
} HAL_HRPWM_PWMGrpTypeDef;

/**
  * @brief HRPWM PWM Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_PWM_0     = LL_HRPWM_SLV_PWM_0,      /*!< HRPWM Slave PWM 0         */
    HAL_HRPWM_SLV_PWM_1     = LL_HRPWM_SLV_PWM_1,      /*!< HRPWM Slave PWM 1         */
    HAL_HRPWM_SLV_PWM_2     = LL_HRPWM_SLV_PWM_2,      /*!< HRPWM Slave PWM 2         */
    HAL_HRPWM_SLV_PWM_3     = LL_HRPWM_SLV_PWM_3,      /*!< HRPWM Slave PWM 3         */
    HAL_HRPWM_SLV_PWM_4     = LL_HRPWM_SLV_PWM_4,      /*!< HRPWM Slave PWM 4         */
    HAL_HRPWM_SLV_PWM_5     = LL_HRPWM_SLV_PWM_5,      /*!< HRPWM Slave PWM 5         */
    HAL_HRPWM_SLV_PWM_6     = LL_HRPWM_SLV_PWM_6,      /*!< HRPWM Slave PWM 6         */
    HAL_HRPWM_SLV_PWM_7     = LL_HRPWM_SLV_PWM_7,      /*!< HRPWM Slave PWM 7         */
    HAL_HRPWM_SLV_PWM_NUMS  = LL_HRPWM_SLV_PWM_NUMS,   /*!< HRPWM Slave PWM Numbers   */
    HAL_HRPWM_MST_PWM       = LL_HRPWM_MST_PWM         /*!< HRPWM Master PWM          */
} HAL_HRPWM_PWMIdxTypeDef;

/**
  * @brief HRPWM External Event Number Definition
  */
typedef enum
{
    HAL_HRPWM_EXT_EVT_NUM_0  = LL_HRPWM_EXT_EVT_NUM_0,   /*!< HRPWM External Event Number 0   */
    HAL_HRPWM_EXT_EVT_NUM_1  = LL_HRPWM_EXT_EVT_NUM_1,   /*!< HRPWM External Event Number 1   */
    HAL_HRPWM_EXT_EVT_NUM_2  = LL_HRPWM_EXT_EVT_NUM_2,   /*!< HRPWM External Event Number 2   */
    HAL_HRPWM_EXT_EVT_NUM_3  = LL_HRPWM_EXT_EVT_NUM_3,   /*!< HRPWM External Event Number 3   */
    HAL_HRPWM_EXT_EVT_NUM_4  = LL_HRPWM_EXT_EVT_NUM_4,   /*!< HRPWM External Event Number 4   */
    HAL_HRPWM_EXT_EVT_NUM_5  = LL_HRPWM_EXT_EVT_NUM_5,   /*!< HRPWM External Event Number 5   */
    HAL_HRPWM_EXT_EVT_NUM_6  = LL_HRPWM_EXT_EVT_NUM_6,   /*!< HRPWM External Event Number 6   */
    HAL_HRPWM_EXT_EVT_NUM_7  = LL_HRPWM_EXT_EVT_NUM_7,   /*!< HRPWM External Event Number 7   */
    HAL_HRPWM_EXT_EVT_NUM_8  = LL_HRPWM_EXT_EVT_NUM_8,   /*!< HRPWM External Event Number 8   */
    HAL_HRPWM_EXT_EVT_NUM_9  = LL_HRPWM_EXT_EVT_NUM_9,   /*!< HRPWM External Event Number 9   */
    HAL_HRPWM_EXT_EVT_NUMS   = LL_HRPWM_EXT_EVT_NUMS     /*!< HRPWM External Event Numbers    */
} HAL_HRPWM_ExtEvtNumTypeDef;

/**
  * @brief HRPWM Fault Number Definition
  */
typedef enum
{
    HAL_HRPWM_FLT_NUM_0   = LL_HRPWM_FLT_NUM_0,   /*!< HRPWM Fault Number 0   */
    HAL_HRPWM_FLT_NUM_1   = LL_HRPWM_FLT_NUM_1,   /*!< HRPWM Fault Number 1   */
    HAL_HRPWM_FLT_NUM_2   = LL_HRPWM_FLT_NUM_2,   /*!< HRPWM Fault Number 2   */
    HAL_HRPWM_FLT_NUM_3   = LL_HRPWM_FLT_NUM_3,   /*!< HRPWM Fault Number 3   */
    HAL_HRPWM_FLT_NUM_4   = LL_HRPWM_FLT_NUM_4,   /*!< HRPWM Fault Number 4   */
    HAL_HRPWM_FLT_NUM_5   = LL_HRPWM_FLT_NUM_5,   /*!< HRPWM Fault Number 5   */
    HAL_HRPWM_FLT_NUM_6   = LL_HRPWM_FLT_NUM_6,   /*!< HRPWM Fault Number 6   */
    HAL_HRPWM_FLT_NUM_7   = LL_HRPWM_FLT_NUM_7,   /*!< HRPWM Fault Number 7   */
    HAL_HRPWM_FLT_NUMS    = LL_HRPWM_FLT_NUMS     /*!< HRPWM Fault Numbers    */
} HAL_HRPWM_FltNumTypeDef;

/**
  * @brief HRPWM ADC Trigger Number Definition
  */
typedef enum
{
    HAL_HRPWM_ADC_TRIG_NUM_0  = LL_HRPWM_ADC_TRIG_NUM_0,   /*!< HRPWM ADC Trigger Number 0   */
    HAL_HRPWM_ADC_TRIG_NUM_1  = LL_HRPWM_ADC_TRIG_NUM_1,   /*!< HRPWM ADC Trigger Number 1   */
    HAL_HRPWM_ADC_TRIG_NUM_2  = LL_HRPWM_ADC_TRIG_NUM_2,   /*!< HRPWM ADC Trigger Number 2   */
    HAL_HRPWM_ADC_TRIG_NUM_3  = LL_HRPWM_ADC_TRIG_NUM_3,   /*!< HRPWM ADC Trigger Number 3   */
    HAL_HRPWM_ADC_TRIG_NUM_4  = LL_HRPWM_ADC_TRIG_NUM_4,   /*!< HRPWM ADC Trigger Number 4   */
    HAL_HRPWM_ADC_TRIG_NUM_5  = LL_HRPWM_ADC_TRIG_NUM_5,   /*!< HRPWM ADC Trigger Number 5   */
    HAL_HRPWM_ADC_TRIG_NUM_6  = LL_HRPWM_ADC_TRIG_NUM_6,   /*!< HRPWM ADC Trigger Number 6   */
    HAL_HRPWM_ADC_TRIG_NUM_7  = LL_HRPWM_ADC_TRIG_NUM_7,   /*!< HRPWM ADC Trigger Number 7   */
    HAL_HRPWM_ADC_TRIG_NUM_8  = LL_HRPWM_ADC_TRIG_NUM_8,   /*!< HRPWM ADC Trigger Number 8   */
    HAL_HRPWM_ADC_TRIG_NUM_9  = LL_HRPWM_ADC_TRIG_NUM_9,   /*!< HRPWM ADC Trigger Number 9   */
    HAL_HRPWM_ADC_TRIG_NUMS   = LL_HRPWM_ADC_TRIG_NUMS     /*!< HRPWM ADC Trigger Numbers    */
} HAL_HRPWM_ADCTrigNumTypeDef;

/**
  * @brief HRPWM PWM Work Mode Definition
  */
typedef enum
{
    HAL_HRPWM_WORK_MODE_SINGLE      = 0U,   /*!< Non retriggerable single-shot mode */
    HAL_HRPWM_WORK_MODE_CONTINUE    = 1U,   /*!< Continuous mode                    */
    HAL_HRPWM_WORK_MODE_SINGLE_REP  = 2U    /*!< Retriggerable single-shot mode     */
} HAL_HRPWM_WorkModeTypeDef;

/**
  * @brief HRPWM PWM Burst Work Mode Definition
  */
typedef enum
{
    HAL_HRPWM_BURST_WORK_MODE_SINGLE    = LL_HRPWM_WORK_MODE_SINGLE,    /*!< single-shot mode in burst mode */
    HAL_HRPWM_BURST_WORK_MODE_CONTINUE  = LL_HRPWM_WORK_MODE_CONTINUE,  /*!< Continuous mode in burst mode  */
} HAL_HRPWM_BurstWorkModeTypeDef;

/**
  * @brief HRPWM DAC Sync Source Definition
  */
typedef enum
{
    HAL_HRPWM_DAC_SYNC_SRC_NONE   = LL_HRPWM_DAC_SYNC_SRC_NONE,    /*!< DAC Sync Source None    */
    HAL_HRPWM_DAC_SYNC_SRC_TRIG0  = LL_HRPWM_DAC_SYNC_SRC_TRIG0,   /*!< DAC Sync Source Trig0   */
    HAL_HRPWM_DAC_SYNC_SRC_TRIG1  = LL_HRPWM_DAC_SYNC_SRC_TRIG1,   /*!< DAC Sync Source Trig1   */
    HAL_HRPWM_DAC_SYNC_SRC_TRIG2  = LL_HRPWM_DAC_SYNC_SRC_TRIG2    /*!< DAC Sync Source Trig2   */
} HAL_HRPWM_DACSyncSrcTypeDef;

/**
  * @brief HRPWM Clock Prescaler Definition
  */
typedef enum
{
    HAL_HRPWM_CLK_PRESCL_MUL_32  = LL_HRPWM_CLK_PRESCL_MUL_32,   /*!< Clock Prescaler Multi 32     */
    HAL_HRPWM_CLK_PRESCL_MUL_16  = LL_HRPWM_CLK_PRESCL_MUL_16,   /*!< Clock Prescaler Multi 16     */
    HAL_HRPWM_CLK_PRESCL_MUL_8   = LL_HRPWM_CLK_PRESCL_MUL_8,    /*!< Clock Prescaler Multi 8      */
    HAL_HRPWM_CLK_PRESCL_MUL_4   = LL_HRPWM_CLK_PRESCL_MUL_4,    /*!< Clock Prescaler Multi 4      */
    HAL_HRPWM_CLK_PRESCL_MUL_2   = LL_HRPWM_CLK_PRESCL_MUL_2,    /*!< Clock Prescaler Multi 2      */
    HAL_HRPWM_CLK_PRESCL_DIV_1   = LL_HRPWM_CLK_PRESCL_DIV_1,    /*!< Clock Prescaler Division 1   */
    HAL_HRPWM_CLK_PRESCL_DIV_2   = LL_HRPWM_CLK_PRESCL_DIV_2,    /*!< Clock Prescaler Division 2   */
    HAL_HRPWM_CLK_PRESCL_DIV_4   = LL_HRPWM_CLK_PRESCL_DIV_4     /*!< Clock Prescaler Division 4   */
} HAL_HRPWM_ClkPresclTypeDef;

/**
  * @brief HRPWM PWM Interleaved Mode Definition
  */
typedef enum
{
    HAL_HRPWM_INTLVD_MODE_CLOSE  = LL_HRPWM_INTLVD_MODE_CLOSE,   /*!< PWM Interleaved Mode Close   */
    HAL_HRPWM_INTLVD_MODE_1_3    = LL_HRPWM_INTLVD_MODE_1_3,     /*!< PWM Interleaved Mode 1/3     */
    HAL_HRPWM_INTLVD_MODE_1_4    = LL_HRPWM_INTLVD_MODE_1_4      /*!< PWM Interleaved Mode 1/4     */
} HAL_HRPWM_IntlvdModeTypeDef;

/**
  * @brief HRPWM Master Update Gate Definition
  */
typedef enum
{
    HAL_HRPWM_MST_UPD_GATE_BST_DMA_INDEPEND  = LL_HRPWM_MST_UPD_GATE_BST_DMA_INDEPEND,   /*!< Master Update Gate Burst DMA Done Independent    */
    HAL_HRPWM_MST_UPD_GATE_BST_DMA_DONE      = LL_HRPWM_MST_UPD_GATE_BST_DMA_DONE,       /*!< Master Update Gate Burst DMA Done Done           */
    HAL_HRPWM_MST_UPD_GATE_BST_DMA_NEXT      = LL_HRPWM_MST_UPD_GATE_BST_DMA_NEXT        /*!< Master Update Gate Burst DMA Done Next Update    \
                                                                                              Event                                            */
} HAL_HRPWM_Mst_UpdGateTypeDef;

/**
  * @brief HRPWM Master Sync Mode Definition
  */
typedef enum
{
    HAL_HRPWM_MST_SYNC_MODE_DIS      = LL_HRPWM_MST_SYNC_MODE_DIS,      /*!< Master Sync Mode Disable        */
    HAL_HRPWM_MST_SYNC_MODE_MST      = LL_HRPWM_MST_SYNC_MODE_MST,      /*!< Master Sync Mode Master         */
    HAL_HRPWM_MST_SYNC_MODE_SLV      = LL_HRPWM_MST_SYNC_MODE_SLV,      /*!< Master Sync Mode Slave          */
    HAL_HRPWM_MST_SYNC_MODE_MST_SLV  = LL_HRPWM_MST_SYNC_MODE_MST_SLV   /*!< Master Sync Mode Master&Slave   */
} HAL_HRPWM_Mst_SyncModeTypeDef;

/**
  * @brief HRPWM Master Sync Output Source Definition
  */
typedef enum
{
    HAL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_START   = LL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_START,    /*!< Master Sync Output Source Master PWM Start       */
    HAL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_CMPA    = LL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_CMPA,     /*!< Master Sync Output Source Master PWM Compare A   */
    HAL_HRPWM_MST_SYNC_OUT_SRC_PWM0_START_RST  = LL_HRPWM_MST_SYNC_OUT_SRC_PWM0_START_RST,   /*!< Master Sync Output Source PWM0 Start/Reset       */
    HAL_HRPWM_MST_SYNC_OUT_SRC_PWM0_CMPA       = LL_HRPWM_MST_SYNC_OUT_SRC_PWM0_CMPA         /*!< Master Sync Output Source PWM0 Compare A         */
} HAL_HRPWM_Mst_SyncOutSrcTypeDef;

/**
  * @brief HRPWM Master Sync Output Polarity Definition
  */
typedef enum
{
    HAL_HRPWM_MST_SYNC_OUT_POL_ACT_HIGH  = LL_HRPWM_MST_SYNC_OUT_POL_ACT_HIGH,   /*!< Master Sync Output Polarity Active High   */
    HAL_HRPWM_MST_SYNC_OUT_POL_ACT_LOW   = LL_HRPWM_MST_SYNC_OUT_POL_ACT_LOW     /*!< Master Sync Output Polarity Active Low    */
} HAL_HRPWM_Mst_SyncOutPolTypeDef;

/**
  * @brief HRPWM Master Sync Input Source Definition
  */
typedef enum
{
    HAL_HRPWM_MST_SYNC_IN_SRC_TMR9_TRGO   = LL_HRPWM_MST_SYNC_IN_SRC_TMR9_TRGO,   /*!< Master Sync Input Source TMR9_TRGO    */
    HAL_HRPWM_MST_SYNC_IN_SRC_HRPWM_SCIN  = LL_HRPWM_MST_SYNC_IN_SRC_HRPWM_SCIN   /*!< Master Sync Input Source HRPWM SCIN   */
} HAL_HRPWM_Mst_SyncInSrcTypeDef;

/**
  * @brief HRPWM Slave Update Gate Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND  = LL_HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND,   /*!< Slave Update Gate Burst DMA Done Independent     */
    HAL_HRPWM_SLV_UPD_GATE_IN0_RISING        = LL_HRPWM_SLV_UPD_GATE_IN0_RISING,         /*!< Slave Update Gate hrpwm_upd_in[0] Rising Egde    */
    HAL_HRPWM_SLV_UPD_GATE_IN1_RISING        = LL_HRPWM_SLV_UPD_GATE_IN1_RISING,         /*!< Slave Update Gate hrpwm_upd_in[1] Rising Egde    */
    HAL_HRPWM_SLV_UPD_GATE_IN2_RISING        = LL_HRPWM_SLV_UPD_GATE_IN2_RISING,         /*!< Slave Update Gate hrpwm_upd_in[2] Rising Egde    */
    HAL_HRPWM_SLV_UPD_GATE_IN0_RISING_NEXT   = LL_HRPWM_SLV_UPD_GATE_IN0_RISING_NEXT,    /*!< Slave Update Gate Next Update Event after        \
                                                                                              hrpwm_upd_in[0] Rising Egde                      */
    HAL_HRPWM_SLV_UPD_GATE_IN1_RISING_NEXT   = LL_HRPWM_SLV_UPD_GATE_IN1_RISING_NEXT,    /*!< Slave Update Gate Next Update Event after        \
                                                                                              hrpwm_upd_in[1] Rising Egde                      */
    HAL_HRPWM_SLV_UPD_GATE_IN2_RISING_NEXT   = LL_HRPWM_SLV_UPD_GATE_IN2_RISING_NEXT,    /*!< Slave Update Gate Next Update Event after        \
                                                                                              hrpwm_upd_in[2] Rising Egde                      */
    HAL_HRPWM_SLV_UPD_GATE_BST_DMA_DONE      = LL_HRPWM_SLV_UPD_GATE_BST_DMA_DONE,       /*!< Slave Update Gate Burst DMA Done Done            */
    HAL_HRPWM_SLV_UPD_GATE_BST_DMA_NEXT      = LL_HRPWM_SLV_UPD_GATE_BST_DMA_NEXT        /*!< Slave Update Gate Burst DMA Done Next Update     \
                                                                                              Event                                            */
} HAL_HRPWM_Slv_UpdGateTypeDef;

/**
  * @brief HRPWM Slave CMP Auto Delayed Mode Definition
  * @note For CMPD, x = B; For CMPB, x = A; For CMPA/CMPC, unrelated
  */
typedef enum
{
    HAL_HRPWM_SLV_CMP_AUTO_DLY_ALWAYS           = LL_HRPWM_SLV_CMP_BD_AUTO_DLY_ALWAYS,          /*!< Slave CMP Auto Delayd Mode Always            */
    HAL_HRPWM_SLV_CMP_AUTO_DLY_AFTER_CAPx       = LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx,      /*!< Slave CMP Auto Delayd Mode After CAPx        */
    HAL_HRPWM_SLV_CMP_AUTO_DLY_AFTER_CAPx_CMPA  = LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx_CMPA, /*!< Slave CMP Auto Delayd Mode After CAPx/CMPA   */
    HAL_HRPWM_SLV_CMP_AUTO_DLY_AFTER_CAPx_CMPC  = LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx_CMPC  /*!< Slave CMP Auto Delayd Mode After CAPx/CMPC   */
} HAL_HRPWM_Slv_CmpAutoDlyTypeDef;

/**
  * @brief HRPWM CMP Unit Definition
  */
typedef enum
{
    HAL_HRPWM_CMP_UNIT_A  = 0U,   /*!< Slave CMP Unit A */
    HAL_HRPWM_CMP_UNIT_B  = 1U,   /*!< Slave CMP Unit B */
    HAL_HRPWM_CMP_UNIT_C  = 2U,   /*!< Slave CMP Unit C */
    HAL_HRPWM_CMP_UNIT_D  = 3U    /*!< Slave CMP Unit D */
} HAL_HRPWM_CmpUnitTypeDef;

/**
  * @brief HRPWM Slave ReSync Mode Definition
  * @note  The functions are subject to the meanings expressed in the annotations
  */
typedef enum
{
    HAL_HRPWM_SLV_RESYNC_IMMEDIATELY           = LL_HRPWM_SLV_RESYNC_IMMEDIATELY,           /*!< Slave ReSync Mode Immediately                    */
    HAL_HRPWM_SLV_RESYNC_NEXT_RST_OR_ROLLOVER  = LL_HRPWM_SLV_RESYNC_NEXT_RST_OR_ROLLOVER   /*!< Slave ReSync Mode Wait for Next Reset/Roll-Over  \
                                                                                                 Event                                            */
} HAL_HRPWM_Slv_ReSyncModeTypeDef;

/**
  * @brief HRPWM Slave Roll-Over Mode Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_ROLL_OVER_0_PERIOD  = LL_HRPWM_SLV_ROLL_OVER_0_PERIOD,   /*!< Slave Roll-Over Mode Generate at O/Period   */
    HAL_HRPWM_SLV_ROLL_OVER_0         = LL_HRPWM_SLV_ROLL_OVER_0,          /*!< Slave Roll-Over Mode Generate at O          */
    HAL_HRPWM_SLV_ROLL_OVER_PERIOD    = LL_HRPWM_SLV_ROLL_OVER_PERIOD      /*!< Slave Roll-Over Mode Generate at Period     */
} HAL_HRPWM_Slv_RollOverModeTypeDef;

/**
  * @brief HRPWM Slave Capture Mode Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_CAP_MODE_NORMAL   = LL_HRPWM_SLV_CAP_MODE_NORMAL,   /*!< Slave Capture Mode Normal    */
    HAL_HRPWM_SLV_CAP_MODE_TIMEOUT  = LL_HRPWM_SLV_CAP_MODE_TIMEOUT   /*!< Slave Capture Mode Timeout   */
} HAL_HRPWM_Slv_CapModeTypeDef;

/**
  * @brief HRPWM Slave Direction Mode Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_DIR_UP       = LL_HRPWM_SLV_DIR_UP,       /*!< Slave Direction Mode Up        */
    HAL_HRPWM_SLV_DIR_UP_DOWN  = LL_HRPWM_SLV_DIR_UP_DOWN   /*!< Slave Direction Mode Up-Down   */
} HAL_HRPWM_Slv_DirModeTypeDef;

/**
  * @brief HRPWM Slave Capture Direction Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_CAP_DIR_UP    = LL_HRPWM_SLV_CAP_DIR_UP,    /*!< Slave Capture Direction Up   */
    HAL_HRPWM_SLV_CAP_DIR_DOWN  = LL_HRPWM_SLV_CAP_DIR_DOWN   /*!< Slave Capture Direction Down */
} HAL_HRPWM_Slv_CapDirTypeDef;

/**
  * @brief HRPWM Slave DAC Reset Trigger Source Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_DAC_RST_TRIG_SRC_RST   = LL_HRPWM_SLV_DAC_RST_TRIG_SRC_RST,   /*!< Slave DAC Reset Trigger Source RST Event    */
    HAL_HRPWM_SLV_DAC_RST_TRIG_SRC_SETA  = LL_HRPWM_SLV_DAC_RST_TRIG_SRC_SETA   /*!< Slave DAC Reset Trigger Source SETA Event   */
} HAL_HRPWM_Slv_DACRstTrigSrcTypeDef;

/**
  * @brief HRPWM Slave DAC Step Trigger Source Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CMPD  = LL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CMPD,   /*!< Slave DAC Step Trigger Source CMPD Event   */
    HAL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CLRA  = LL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CLRA    /*!< Slave DAC Step Trigger Source CLRA Event   */
} HAL_HRPWM_Slv_DACStepTrigSrcTypeDef;

/**
  * @brief HRPWM Slave DeadTime Direction Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_DT_DIR_POSITIVE  = LL_HRPWM_SLV_DT_DIR_POSITIVE,   /*!< Slave DeadTime Direction Positive   */
    HAL_HRPWM_SLV_DT_DIR_NEGATIVE  = LL_HRPWM_SLV_DT_DIR_NEGATIVE    /*!< Slave DeadTime Direction Negative   */
} HAL_HRPWM_Slv_DtDirTypeDef;

/**
  * @brief HRPWM Slave External Event Filter Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_EXT_EVT_FIL_DIS                    = LL_HRPWM_SLV_EXT_EVT_FIL_DIS,                    /*!< Slave External Event Filter Disable              */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPA         = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPA,         /*!< Slave External Event Filter Blank from           \
                                                                                                             Reset/Roll-Over to Compare A                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPB         = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPB,         /*!< Slave External Event Filter Blank from           \
                                                                                                             Reset/Roll-Over to Compare B                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPC         = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPC,         /*!< Slave External Event Filter Blank from           \
                                                                                                             Reset/Roll-Over to Compare C                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPD         = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPD,         /*!< Slave External Event Filter Blank from           \
                                                                                                             Reset/Roll-Over to Compare D                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPA_CMPB       = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPA_CMPB,       /*!< Slave External Event Filter Blank from Up        \
                                                                                                             Compare A to Up Compare B                        */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPC_CMPD       = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPC_CMPD,       /*!< Slave External Event Filter Blank from Up        \
                                                                                                             Compare C to Up Compare D                        */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPA_CMPB     = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPA_CMPB,     /*!< Slave External Event Filter Blank from Down      \
                                                                                                             Compare A to Down Compare B                      */
    HAL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPC_CMPD     = LL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPC_CMPD,     /*!< Slave External Event Filter Blank from Down      \
                                                                                                             Compare C to Down Compare D                      */
    HAL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPA         = LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPA,         /*!< Slave External Event Filter Window from          \
                                                                                                             Reset/Roll-Over to Compare A                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPB         = LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPB,         /*!< Slave External Event Filter Window from          \
                                                                                                             Reset/Roll-Over to Compare B                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPC         = LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPC,         /*!< Slave External Event Filter Window from          \
                                                                                                             Reset/Roll-Over to Compare C                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPD         = LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPD,         /*!< Slave External Event Filter Window from          \
                                                                                                             Reset/Roll-Over to Compare D                     */
    HAL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_CMPC       = LL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_CMPC,       /*!< Slave External Event Filter Window from Up       \
                                                                                                             Compare B to Up Compare C                        */
    HAL_HRPWM_SLV_EXT_EVT_FIL_WIN_DOWN_CMPB_CMPC     = LL_HRPWM_SLV_EXT_EVT_FIL_WIN_DOWN_CMPB_CMPC,     /*!< Slave External Event Filter Window from Dowm     \
                                                                                                             Compare B to Dowm Compare C                      */
    HAL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_DOWN_CMPC  = LL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_DOWN_CMPC   /*!< Slave External Event Filter Window from Up       \
                                                                                                             Compare B to Down Compare C                      */
} HAL_HRPWM_Slv_ExtEvtFilTypeDef;

/**
  * @brief HRPWM Slave External Event Counter Definition
  */
typedef enum
{
    HAL_HRPWM_EVT_CNTR_A  = 0U, /*!< Event Counter A        */
    HAL_HRPWM_EVT_CNTR_RSV      /*!< Event Counter Reserved */
} HAL_HRPWM_EvtCntrTypeDef;

/**
  * @brief HRPWM Output Channel Definition
  */
typedef enum
{
    HAL_HRPWM_OUTPUT_CHNL_A  = 0U, /*!< Output Channel A        */
    HAL_HRPWM_OUTPUT_CHNL_B        /*!< Output Channel B */
} HAL_HRPWM_OutputChnlTypeDef;

/**
  * @brief HRPWM Capture Channel Definition
  */
typedef enum
{
    HAL_HRPWM_CAP_CHNL_A  = 0U, /*!< Capture Channel A        */
    HAL_HRPWM_CAP_CHNL_B        /*!< Capture Channel B */
} HAL_HRPWM_CapChnlTypeDef;

/**
  * @brief HRPWM Slave External Event A Counter Reset Mode Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_EVT_CNTR_RST_RSTRO_ALWAYS       = LL_HRPWM_SLV_EVTA_CNTR_RST_RSTRO_ALWAYS,       /*!< Slave Event Counter Reset at Reset/Roll-Over      \
                                                                                                         Event Always                                     */
    HAL_HRPWM_SLV_EVT_CNTR_RST_RSTRO_LAST_NO_EVT  = LL_HRPWM_SLV_EVTA_CNTR_RST_RSTRO_LAST_NO_EVT   /*!< Slave Event Counter Reset at Reset/Roll-Over      \
                                                                                                         Event Only Last No Event                         */
} HAL_HRPWM_Slv_EvtCntrRstModeTypeDef;

/**
  * @brief HRPWM Slave Chopper Start Pulse Width Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_PC_PULSE_WIDH_16   = LL_HRPWM_SLV_PC_PULSE_WIDH_16,    /*!< HRPWM Slave Chopper Start Pulse Width 16    */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_32   = LL_HRPWM_SLV_PC_PULSE_WIDH_32,    /*!< HRPWM Slave Chopper Start Pulse Width 32    */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_48   = LL_HRPWM_SLV_PC_PULSE_WIDH_48,    /*!< HRPWM Slave Chopper Start Pulse Width 48    */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_64   = LL_HRPWM_SLV_PC_PULSE_WIDH_64,    /*!< HRPWM Slave Chopper Start Pulse Width 64    */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_80   = LL_HRPWM_SLV_PC_PULSE_WIDH_80,    /*!< HRPWM Slave Chopper Start Pulse Width 80    */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_96   = LL_HRPWM_SLV_PC_PULSE_WIDH_96,    /*!< HRPWM Slave Chopper Start Pulse Width 96    */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_112  = LL_HRPWM_SLV_PC_PULSE_WIDH_112,   /*!< HRPWM Slave Chopper Start Pulse Width 112   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_128  = LL_HRPWM_SLV_PC_PULSE_WIDH_128,   /*!< HRPWM Slave Chopper Start Pulse Width 128   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_144  = LL_HRPWM_SLV_PC_PULSE_WIDH_144,   /*!< HRPWM Slave Chopper Start Pulse Width 144   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_160  = LL_HRPWM_SLV_PC_PULSE_WIDH_160,   /*!< HRPWM Slave Chopper Start Pulse Width 160   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_176  = LL_HRPWM_SLV_PC_PULSE_WIDH_176,   /*!< HRPWM Slave Chopper Start Pulse Width 176   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_192  = LL_HRPWM_SLV_PC_PULSE_WIDH_192,   /*!< HRPWM Slave Chopper Start Pulse Width 192   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_208  = LL_HRPWM_SLV_PC_PULSE_WIDH_208,   /*!< HRPWM Slave Chopper Start Pulse Width 208   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_224  = LL_HRPWM_SLV_PC_PULSE_WIDH_224,   /*!< HRPWM Slave Chopper Start Pulse Width 224   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_240  = LL_HRPWM_SLV_PC_PULSE_WIDH_240,   /*!< HRPWM Slave Chopper Start Pulse Width 240   */
    HAL_HRPWM_SLV_PC_PULSE_WIDH_256  = LL_HRPWM_SLV_PC_PULSE_WIDH_256    /*!< HRPWM Slave Chopper Start Pulse Width 256   */
} HAL_HRWPM_Slv_PC_PulseWidthTypeDef;

/**
  * @brief HRPWM Slave Chopper Duty Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_PC_DUTY_8_0  = LL_HRPWM_SLV_PC_DUTY_8_0,   /*!< HRPWM Slave Chopper Duty 0/8   */
    HAL_HRPWM_SLV_PC_DUTY_8_1  = LL_HRPWM_SLV_PC_DUTY_8_1,   /*!< HRPWM Slave Chopper Duty 1/8   */
    HAL_HRPWM_SLV_PC_DUTY_8_2  = LL_HRPWM_SLV_PC_DUTY_8_2,   /*!< HRPWM Slave Chopper Duty 2/8   */
    HAL_HRPWM_SLV_PC_DUTY_8_3  = LL_HRPWM_SLV_PC_DUTY_8_3,   /*!< HRPWM Slave Chopper Duty 3/8   */
    HAL_HRPWM_SLV_PC_DUTY_8_4  = LL_HRPWM_SLV_PC_DUTY_8_4,   /*!< HRPWM Slave Chopper Duty 4/8   */
    HAL_HRPWM_SLV_PC_DUTY_8_5  = LL_HRPWM_SLV_PC_DUTY_8_5,   /*!< HRPWM Slave Chopper Duty 5/8   */
    HAL_HRPWM_SLV_PC_DUTY_8_6  = LL_HRPWM_SLV_PC_DUTY_8_6,   /*!< HRPWM Slave Chopper Duty 6/8   */
    HAL_HRPWM_SLV_PC_DUTY_8_7  = LL_HRPWM_SLV_PC_DUTY_8_7    /*!< HRPWM Slave Chopper Duty 7/8   */
} HAL_HRPWM_Slv_PC_DutyTypeDef;

/**
  * @brief HRPWM Slave Chopper Frequency Division Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_PC_FREQ_DIV_16   = LL_HRPWM_SLV_PC_FREQ_DIV_16,    /*!< HRPWM Slave Chopper Frequency Division 16    */
    HAL_HRPWM_SLV_PC_FREQ_DIV_32   = LL_HRPWM_SLV_PC_FREQ_DIV_32,    /*!< HRPWM Slave Chopper Frequency Division 32    */
    HAL_HRPWM_SLV_PC_FREQ_DIV_48   = LL_HRPWM_SLV_PC_FREQ_DIV_48,    /*!< HRPWM Slave Chopper Frequency Division 48    */
    HAL_HRPWM_SLV_PC_FREQ_DIV_64   = LL_HRPWM_SLV_PC_FREQ_DIV_64,    /*!< HRPWM Slave Chopper Frequency Division 64    */
    HAL_HRPWM_SLV_PC_FREQ_DIV_80   = LL_HRPWM_SLV_PC_FREQ_DIV_80,    /*!< HRPWM Slave Chopper Frequency Division 80    */
    HAL_HRPWM_SLV_PC_FREQ_DIV_96   = LL_HRPWM_SLV_PC_FREQ_DIV_96,    /*!< HRPWM Slave Chopper Frequency Division 96    */
    HAL_HRPWM_SLV_PC_FREQ_DIV_112  = LL_HRPWM_SLV_PC_FREQ_DIV_112,   /*!< HRPWM Slave Chopper Frequency Division 112   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_128  = LL_HRPWM_SLV_PC_FREQ_DIV_128,   /*!< HRPWM Slave Chopper Frequency Division 128   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_144  = LL_HRPWM_SLV_PC_FREQ_DIV_144,   /*!< HRPWM Slave Chopper Frequency Division 144   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_160  = LL_HRPWM_SLV_PC_FREQ_DIV_160,   /*!< HRPWM Slave Chopper Frequency Division 160   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_176  = LL_HRPWM_SLV_PC_FREQ_DIV_176,   /*!< HRPWM Slave Chopper Frequency Division 176   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_192  = LL_HRPWM_SLV_PC_FREQ_DIV_192,   /*!< HRPWM Slave Chopper Frequency Division 192   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_208  = LL_HRPWM_SLV_PC_FREQ_DIV_208,   /*!< HRPWM Slave Chopper Frequency Division 208   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_224  = LL_HRPWM_SLV_PC_FREQ_DIV_224,   /*!< HRPWM Slave Chopper Frequency Division 224   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_240  = LL_HRPWM_SLV_PC_FREQ_DIV_240,   /*!< HRPWM Slave Chopper Frequency Division 240   */
    HAL_HRPWM_SLV_PC_FREQ_DIV_256  = LL_HRPWM_SLV_PC_FREQ_DIV_256    /*!< HRPWM Slave Chopper Frequency Division 256   */
} HAL_HRPWM_Slv_PC_FreqDivTypeDef;

/**
  * @brief HRPWM Slave Delay Protection Mechanism Definition
  * @note  x = 6, y = 5 for PWM0~3; x = 8, y = 7 for PWM4~7
  */
typedef enum
{
    HAL_HRPWM_SLV_DLY_PROT_MECH_DISABLE          = LL_HRPWM_SLV_DLY_PROT_MECH_DISABLE,           /*!< Slave Delay Protection Disable                   */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTy_IDLE   = LL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTy_IDLE,    /*!< Slave Delay Protection Mechanism OutA Delay Idle \
                                                                                                      on Ext Event y                                   */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTy_IDLE   = LL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTy_IDLE,    /*!< Slave Delay Protection Mechanism OutB Delay Idle \
                                                                                                      on Ext Event y                                   */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_IDLE  = LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_IDLE,   /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                                      Idle on Ext Event y                              */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_BAL   = LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_BAL,    /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                                      Balance on Ext Event y                           */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTx_IDLE   = LL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTx_IDLE,    /*!< Slave Delay Protection Mechanism OutA Delay Idle \
                                                                                                      on Ext Event x                                   */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTx_IDLE   = LL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTx_IDLE,    /*!< Slave Delay Protection Mechanism OutB Delay Idle \
                                                                                                      on Ext Event x                                   */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_IDLE  = LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_IDLE,   /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                                      Idle on Ext Event x                              */
    HAL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_BAL   = LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_BAL     /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                                      Balance on Ext Event x                           */
} HAL_HRPWM_Slv_DlyProtMechTypeDef;

/**
  * @brief HRPWM Slave Output Idle Status Level Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_OUT_IDLE_LVL_INVLD  = LL_HRPWM_SLV_OUT_IDLE_LVL_INVLD,   /*!< Slave Out Idle Status Level Invalid   */
    HAL_HRPWM_SLV_OUT_IDLE_LVL_VLD    = LL_HRPWM_SLV_OUT_IDLE_LVL_VLD      /*!< Slave Out Idle Status Level Valid     */
} HAL_HRPWM_Slv_OutIdleLvlTypeDef;

/**
  * @brief HRPWM Slave Output Level Status Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_OUT_LVL_STATE_INVLD  = 0U,    /*!< Slave Output Level Invalid  */
    HAL_HRPWM_SLV_OUT_LVL_STATE_VLD    = 1U     /*!< Slave Output Level Valid    */
} HAL_HRPWM_Slv_OutLvlStateTypeDef;

/**
  * @brief HRPWM Slave Output Status Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_OUT_STATE_IDLE    = 1U,   /*!< Slave Output State Idle  */
    HAL_HRPWM_SLV_OUT_STATE_RUN     = 2U,   /*!< Slave Output State Run   */
    HAL_HRPWM_SLV_OUT_STATE_FAULT   = 3U    /*!< Slave Output State Fault */
} HAL_HRPWM_Slv_OutStateTypeDef;

/**
  * @brief HRPWM Slave Output Fault Status Level Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_OUT_FAULT_LVL_NO_ACTION  = LL_HRPWM_SLV_OUT_FAULT_LVL_NO_ACTION,   /*!< Slave Out Fault Status Level No Action   */
    HAL_HRPWM_SLV_OUT_FAULT_LVL_VLD        = LL_HRPWM_SLV_OUT_FAULT_LVL_VLD,         /*!< Slave Out Fault Status Level Valid       */
    HAL_HRPWM_SLV_OUT_FAULT_LVL_INVLD      = LL_HRPWM_SLV_OUT_FAULT_LVL_INVLD,       /*!< Slave Out Fault Status Level Invalid     */
    HAL_HRPWM_SLV_OUT_FAULT_LVL_HZ         = LL_HRPWM_SLV_OUT_FAULT_LVL_HZ           /*!< Slave Out Fault Status Level High-Z      */
} HAL_HRPWM_Slv_OutFaultLvlTypeDef;

/**
  * @brief HRPWM Slave Output Polarity Definition
  */
typedef enum
{
    HAL_HRPWM_SLV_OUT_POL_ACT_HIGH  = LL_HRPWM_SLV_OUT_POL_ACT_HIGH,   /*!< Slave Out Polarity Active High   */
    HAL_HRPWM_SLV_OUT_POL_ACT_LOW   = LL_HRPWM_SLV_OUT_POL_ACT_LOW     /*!< Slave Out Polarity Active Low    */
} HAL_HRPWM_Slv_OutPolTypeDef;

/**
  * @brief HRPWM Common ADC Trigger x Update Source Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_MST_PWM  = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_MST_PWM,   /*!< Common ADC Trigger x Update Source Master PWM   */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM0     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM0,      /*!< Common ADC Trigger x Update Source PWM0         */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM1     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM1,      /*!< Common ADC Trigger x Update Source PWM1         */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM2     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM2,      /*!< Common ADC Trigger x Update Source PWM2         */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM3     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM3,      /*!< Common ADC Trigger x Update Source PWM3         */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM4     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM4,      /*!< Common ADC Trigger x Update Source PWM4         */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM5     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM5,      /*!< Common ADC Trigger x Update Source PWM5         */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM6     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM6,      /*!< Common ADC Trigger x Update Source PWM6         */
    HAL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM7     = LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM7       /*!< Common ADC Trigger x Update Source PWM7         */
} HAL_HRPWM_Comm_ADCTrigUpdSrcTypeDef;

/**
  * @brief HRPWM Common ADC Trigger x Event Length Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_16CLK  = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_16CLK,   /*!< Common ADC Trigger x Event Length 16 hrpwm_clk   */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_15CLK  = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_15CLK,   /*!< Common ADC Trigger x Event Length 15 hrpwm_clk   */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_14CLK  = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_14CLK,   /*!< Common ADC Trigger x Event Length 14 hrpwm_clk   */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_13CLK  = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_13CLK,   /*!< Common ADC Trigger x Event Length 13 hrpwm_clk   */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_12CLK  = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_12CLK,   /*!< Common ADC Trigger x Event Length 12 hrpwm_clk   */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_11CLK  = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_11CLK,   /*!< Common ADC Trigger x Event Length 11 hrpwm_clk   */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_10CLK  = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_10CLK,   /*!< Common ADC Trigger x Event Length 10 hrpwm_clk   */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_9CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_9CLK,    /*!< Common ADC Trigger x Event Length 9 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_8CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_8CLK,    /*!< Common ADC Trigger x Event Length 8 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_7CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_7CLK,    /*!< Common ADC Trigger x Event Length 7 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_6CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_6CLK,    /*!< Common ADC Trigger x Event Length 6 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_5CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_5CLK,    /*!< Common ADC Trigger x Event Length 5 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_4CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_4CLK,    /*!< Common ADC Trigger x Event Length 4 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_3CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_3CLK,    /*!< Common ADC Trigger x Event Length 3 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_2CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_2CLK,    /*!< Common ADC Trigger x Event Length 2 hrpwm_clk    */
    HAL_HRPWM_COMM_ADC_TRIG_EVT_LEN_1CLK   = LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_1CLK     /*!< Common ADC Trigger x Event Length 1 hrpwm_clk    */
} HAL_HRPWM_Comm_ADCTrigEvtLenTypeDef;

/**
  * @brief HRPWM Common External Event Input Active Edge Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_LVL      = LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_LVL,       /*!< Common External Event Input Edge Active Level    */
    HAL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_RISING   = LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_RISING,    /*!< Common External Event Input Edge Active Rising   */
    HAL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_FALLING  = LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_FALLING,   /*!< Common External Event Input Edge Active Falling  */
    HAL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_BOTH     = LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_BOTH       /*!< Common External Event Input Edge Active          \
                                                                                                          Rising/Falling                                   */
} HAL_HRPWM_Comm_ExtEvtInputEdgeTypeDef;

/**
  * @brief HRPWM Common External Event Input Polarity Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_HIGH  = LL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_HIGH,   /*!< Common External Event Input Polarity Active High */
    HAL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_LOW   = LL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_LOW     /*!< Common External Event Input Polarity Active Low  */
} HAL_HRPWM_Comm_ExtEvtInputPolTypeDef;

/**
  * @brief HRPWM Common External Event X Input Source Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_HRPWM_EVT0  = LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_HRPWM_EVT0,   /*!< Common External Event0 Input Source HRPWM_EVT0   */
    HAL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_CMP1_OUT    = LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_CMP1_OUT,     /*!< Common External Event0 Input Source CMP1_OUT     */
    HAL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_TMR9_TRGO   = LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_TMR9_TRGO,    /*!< Common External Event0 Input Source TMR9_TRGO    */
    HAL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_ADC0_AWD0   = LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_ADC0_AWD0,    /*!< Common External Event0 Input Source ADC0_AWD0    */
    HAL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_HRPWM_EVT1  = LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_HRPWM_EVT1,   /*!< Common External Event1 Input Source HRPWM_EVT1   */
    HAL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_CMP3_OUT    = LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_CMP3_OUT,     /*!< Common External Event1 Input Source CMP3_OUT     */
    HAL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_TMR3_TRGO   = LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_TMR3_TRGO,    /*!< Common External Event1 Input Source TMR3_TRGO    */
    HAL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_ADC0_AWD1   = LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_ADC0_AWD1,    /*!< Common External Event1 Input Source ADC0_AWD1    */
    HAL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_HRPWM_EVT2  = LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_HRPWM_EVT2,   /*!< Common External Event2 Input Source HRPWM_EVT2   */
    HAL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP5_OUT    = LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP5_OUT,     /*!< Common External Event2 Input Source CMP5_OUT     */
    HAL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_TMR4_TRGO   = LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_TMR4_TRGO,    /*!< Common External Event2 Input Source TMR4_TRGO    */
    HAL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP7_OUT    = LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP7_OUT,     /*!< Common External Event2 Input Source CMP7_OUT     */
    HAL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_HRPWM_EVT3  = LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_HRPWM_EVT3,   /*!< Common External Event3 Input Source HRPWM_EVT3   */
    HAL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP0_OUT    = LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP0_OUT,     /*!< Common External Event3 Input Source CMP0_OUT     */
    HAL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP4_OUT    = LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP4_OUT,     /*!< Common External Event3 Input Source CMP4_OUT     */
    HAL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_ADC1_AWD0   = LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_ADC1_AWD0,    /*!< Common External Event3 Input Source ADC1_AWD0    */
    HAL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_HRPWM_EVT4  = LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_HRPWM_EVT4,   /*!< Common External Event4 Input Source HRPWM_EVT4   */
    HAL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP2_OUT    = LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP2_OUT,     /*!< Common External Event4 Input Source CMP2_OUT     */
    HAL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP6_OUT    = LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP6_OUT,     /*!< Common External Event4 Input Source CMP6_OUT     */
    HAL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_ADC1_AWD1   = LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_ADC1_AWD1,    /*!< Common External Event4 Input Source ADC1_AWD1    */
    HAL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_HRPWM_EVT5  = LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_HRPWM_EVT5,   /*!< Common External Event5 Input Source HRPWM_EVT5   */
    HAL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP1_OUT    = LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP1_OUT,     /*!< Common External Event5 Input Source CMP1_OUT     */
    HAL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP0_OUT    = LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP0_OUT,     /*!< Common External Event5 Input Source CMP0_OUT     */
    HAL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP8_OUT    = LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP8_OUT,     /*!< Common External Event5 Input Source CMP8_OUT     */
    HAL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_HRPWM_EVT6  = LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_HRPWM_EVT6,   /*!< Common External Event6 Input Source HRPWM_EVT6   */
    HAL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_CMP3_OUT    = LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_CMP3_OUT,     /*!< Common External Event6 Input Source CMP3_OUT     */
    HAL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_TMR8_TRGO   = LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_TMR8_TRGO,    /*!< Common External Event6 Input Source TMR8_TRGO    */
    HAL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_ADC2_AWD0   = LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_ADC2_AWD0,    /*!< Common External Event6 Input Source ADC2_AWD0    */
    HAL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_HRPWM_EVT7  = LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_HRPWM_EVT7,   /*!< Common External Event7 Input Source HRPWM_EVT7   */
    HAL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP5_OUT    = LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP5_OUT,     /*!< Common External Event7 Input Source CMP5_OUT     */
    HAL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP2_OUT    = LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP2_OUT,     /*!< Common External Event7 Input Source CMP2_OUT     */
    HAL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_ADC3_AWD0   = LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_ADC3_AWD0,    /*!< Common External Event7 Input Source ADC3_AWD0    */
    HAL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_HRPWM_EVT8  = LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_HRPWM_EVT8,   /*!< Common External Event8 Input Source HRPWM_EVT8   */
    HAL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP4_OUT    = LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP4_OUT,     /*!< Common External Event8 Input Source CMP4_OUT     */
    HAL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_TMR0_TRGO   = LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_TMR0_TRGO,    /*!< Common External Event8 Input Source TMR0_TRGO    */
    HAL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP3_OUT    = LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP3_OUT,     /*!< Common External Event8 Input Source CMP3_OUT     */
    HAL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_HRPWM_EVT9  = LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_HRPWM_EVT9,   /*!< Common External Event9 Input Source HRPWM_EVT9   */
    HAL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_CMP6_OUT    = LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_CMP6_OUT,     /*!< Common External Event9 Input Source CMP6_OUT     */
    HAL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_TMR7_TRGO   = LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_TMR7_TRGO,    /*!< Common External Event9 Input Source TMR7_TRGO    */
    HAL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_PDM0_CMPH   = LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_PDM0_CMPH,    /*!< Common External Event9 Input Source PDM0_CMPH    */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT0  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT0,   /*!< External Event X Input Source HRPWM_EVT0         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT1  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT1,   /*!< External Event X Input Source HRPWM_EVT1         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT2  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT2,   /*!< External Event X Input Source HRPWM_EVT2         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT3  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT3,   /*!< External Event X Input Source HRPWM_EVT3         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT4  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT4,   /*!< External Event X Input Source HRPWM_EVT4         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT5  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT5,   /*!< External Event X Input Source HRPWM_EVT5         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT6  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT6,   /*!< External Event X Input Source HRPWM_EVT6         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT7  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT7,   /*!< External Event X Input Source HRPWM_EVT7         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT8  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT8,   /*!< External Event X Input Source HRPWM_EVT8         */
    HAL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT9  = LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT9    /*!< External Event X Input Source HRPWM_EVT9         */
} HAL_HRPWM_Comm_ExtEvtXInputSrcTypeDef;

/**
  * @brief HRPWM Common External Event Sample Clock Division Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_1  = LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_1,   /*!< Common External Event Sample Clock Division 1   */
    HAL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_2  = LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_2,   /*!< Common External Event Sample Clock Division 2   */
    HAL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_4  = LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_4,   /*!< Common External Event Sample Clock Division 4   */
    HAL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_8  = LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_8    /*!< Common External Event Sample Clock Division 8   */
} HAL_HRPWM_Comm_ExtEvtSampClkDivTypeDef;

/**
  * @brief HRPWM Common ADC4/6/8 Trigger Event Source Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_DEFAULT            = LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPA,        /*!< ADC4/6/8 Trigger Event Source Default            */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPA       = LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPA,        /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                                                A                                                */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPB       = LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPB,        /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                                                B                                                */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPC       = LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPC,        /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                                                C                                                */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPD       = LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPD,        /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                                                D                                                */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_PRD        = LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_PRD,         /*!< ADC4/6/8 Trigger Event Source Master PWM Period  */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_0          = LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_0,           /*!< ADC4/6/8 Trigger Event Source External Event 0   */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_1          = LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_1,           /*!< ADC4/6/8 Trigger Event Source External Event 1   */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_2          = LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_2,           /*!< ADC4/6/8 Trigger Event Source External Event 2   */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_3          = LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_3,           /*!< ADC4/6/8 Trigger Event Source External Event 3   */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_4          = LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_4,           /*!< ADC4/6/8 Trigger Event Source External Event 4   */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM0 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM0 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM0 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_RST_ROLLOVER  = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_RST_ROLLOVER,   /*!< ADC4/6/8 Trigger Event Source PWM0               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM1 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM1 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM1 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_RST_ROLLOVE   = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_RST_ROLLOVE,    /*!< ADC4/6/8 Trigger Event Source PWM1               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM2 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM2 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM2 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM3 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM3 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM3 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM4 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM4 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM4 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPB          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPB,           /*!< ADC4/6/8 Trigger Event Source PWM5 Compare B     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM5 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM5 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM5 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_RST_ROLLOVER  = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_RST_ROLLOVER,   /*!< ADC4/6/8 Trigger Event Source PWM5               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM6 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM6 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM6 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_RST_ROLLOVER  = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_RST_ROLLOVER,   /*!< ADC4/6/8 Trigger Event Source PWM6               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPC          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM7 Compare C     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPD          = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM7 Compare D     */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_PRD           = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM7 Period        */
    HAL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_RST_ROLLOVER  = LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_RST_ROLLOVER    /*!< ADC4/6/8 Trigger Event Source PWM7               \
                                                                                                                Reset/Roll-Over                                  */
} HAL_HRPWM_Comm_ADC468TrigEvtSrcTypeDef;

/**
  * @brief HRPWM Common ADC5/7/9 Trigger Event Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_DEFAULT            = LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPA,        /*!< ADC5/7/9 Trigger Event Source Default            */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPA       = LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPA,        /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                                                A                                                */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPB       = LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPB,        /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                                                B                                                */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPC       = LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPC,        /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                                                C                                                */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPD       = LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPD,        /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                                                D                                                */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_PRD        = LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_PRD,         /*!< ADC5/7/9 Trigger Event Source Master PWM Period  */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_5          = LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_5,           /*!< ADC5/7/9 Trigger Event Source External Event 5   */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_6          = LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_6,           /*!< ADC5/7/9 Trigger Event Source External Event 6   */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_7          = LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_7,           /*!< ADC5/7/9 Trigger Event Source External Event 7   */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_8          = LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_8,           /*!< ADC5/7/9 Trigger Event Source External Event 8   */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_9          = LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_9,           /*!< ADC5/7/9 Trigger Event Source External Event 9   */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM0 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM0 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_PRD           = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM0 Period        */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM1 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM1 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_PRD           = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM1 Period        */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM2 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM2 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_PRD           = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM2 Period        */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_RST_ROLLOVER  = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM2               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM3 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM3 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_PRD           = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM3 Period        */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_RST_ROLLOVER  = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM3               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM4 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPC          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPC,           /*!< ADC5/7/9 Trigger Event Source PWM4 Compare C     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM4 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_RST_ROLLOVER  = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM4               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM5 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPC          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPC,           /*!< ADC5/7/9 Trigger Event Source PWM5 Compare C     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM5 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_PRD           = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM5 Period        */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM6 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM6 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_PRD           = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM6 Period        */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_RST_ROLLOVER  = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM6               \
                                                                                                                Reset/Roll-Over                                  */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPB          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM7 Compare B     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPD          = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM7 Compare D     */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_PRD           = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM7 Period        */
    HAL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_RST_ROLLOVER  = LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_RST_ROLLOVER    /*!< ADC5/7/9 Trigger Event Source PWM7               \
                                                                                                                Reset/Roll-Over                                  */
} HAL_HRPWM_Comm_ADC579TrigEvtSrcTypeDef;

/**
  * @brief HRPWM Common DLL Current Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_DLL_CUR_4uA  = LL_HRPWM_COMM_DLL_CUR_4uA,   /*!< Common DLL Current 4uA   */
    HAL_HRPWM_COMM_DLL_CUR_6uA  = LL_HRPWM_COMM_DLL_CUR_6uA,   /*!< Common DLL Current 6uA   */
    HAL_HRPWM_COMM_DLL_CUR_8uA  = LL_HRPWM_COMM_DLL_CUR_8uA    /*!< Common DLL Current 8uA   */
} HAL_HRPWM_Comm_DLLCurTypeDef;

/**
  * @brief HRPWM Common Fault X Input Source Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_FLTx  = LL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_FLTx,   /*!< Common Fault Input Source HRPWM Fault         */
    HAL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_EVTx  = LL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_EVTx,   /*!< Common Fault Input Source HRPWM Event         */
    HAL_HRPWM_COMM_FLT0_INPUT_SRC_CMP1_OUT    = LL_HRPWM_COMM_FLT0_INPUT_SRC_CMP1_OUT,     /*!< Common Fault 0 Input Source HRPWM CMP 1 Out   */
    HAL_HRPWM_COMM_FLT1_INPUT_SRC_CMP3_OUT    = LL_HRPWM_COMM_FLT1_INPUT_SRC_CMP3_OUT,     /*!< Common Fault 1 Input Source HRPWM CMP 3 Out   */
    HAL_HRPWM_COMM_FLT2_INPUT_SRC_CMP5_OUT    = LL_HRPWM_COMM_FLT2_INPUT_SRC_CMP5_OUT,     /*!< Common Fault 2 Input Source HRPWM CMP 5 Out   */
    HAL_HRPWM_COMM_FLT3_INPUT_SRC_CMP0_OUT    = LL_HRPWM_COMM_FLT3_INPUT_SRC_CMP0_OUT,     /*!< Common Fault 3 Input Source HRPWM CMP 0 Out   */
    HAL_HRPWM_COMM_FLT4_INPUT_SRC_CMP2_OUT    = LL_HRPWM_COMM_FLT4_INPUT_SRC_CMP2_OUT,     /*!< Common Fault 4 Input Source HRPWM CMP 2 Out   */
    HAL_HRPWM_COMM_FLT5_INPUT_SRC_CMP4_OUT    = LL_HRPWM_COMM_FLT5_INPUT_SRC_CMP4_OUT,     /*!< Common Fault 5 Input Source HRPWM CMP 4 Out   */
    HAL_HRPWM_COMM_FLT6_INPUT_SRC_CMP7_OUT    = LL_HRPWM_COMM_FLT6_INPUT_SRC_CMP7_OUT,     /*!< Common Fault 6 Input Source HRPWM CMP 7 Out   */
    HAL_HRPWM_COMM_FLT7_INPUT_SRC_CMP8_OUT    = LL_HRPWM_COMM_FLT7_INPUT_SRC_CMP8_OUT      /*!< Common Fault 7 Input Source HRPWM CMP 8 Out   */
} HAL_HRPWM_Comm_FltXInputSrcTypeDef;

/**
  * @brief HRPWM Common Fault x Input Polarity Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_FLT_INPUT_POL_ACT_HIGH  = LL_HRPWM_COMM_FLT_INPUT_POL_ACT_HIGH,   /*!< Common Fault x Input Polarity Active High   */
    HAL_HRPWM_COMM_FLT_INPUT_POL_ACT_LOW   = LL_HRPWM_COMM_FLT_INPUT_POL_ACT_LOW     /*!< Common Fault x Input Polarity Active Low    */
} HAL_HRPWM_Comm_FltInputPolTypeDef;

/**
  * @brief HRPWM Common Fault Sample Clock Division Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_FLT_SAMP_CLK_DIV_1  = LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_1,   /*!< Common Fault Sample Clock Division 1   */
    HAL_HRPWM_COMM_FLT_SAMP_CLK_DIV_2  = LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_2,   /*!< Common Fault Sample Clock Division 2   */
    HAL_HRPWM_COMM_FLT_SAMP_CLK_DIV_4  = LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_4,   /*!< Common Fault Sample Clock Division 4   */
    HAL_HRPWM_COMM_FLT_SAMP_CLK_DIV_8  = LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_8    /*!< Common Fault Sample Clock Division 8   */
} HAL_HRPWM_Comm_FltSampClkDivTypeDef;

/**
  * @brief HRPWM Common Fault X Blank Source Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_FLT_BLK_SRC_FIXED_WIN  = LL_HRPWM_COMM_FLT_BLK_SRC_FIXED_WIN,   /*!< Common Fault X Blank Source Fixed Window   */
    HAL_HRPWM_COMM_FLT_BLK_SRC_MOVED_WIN  = LL_HRPWM_COMM_FLT_BLK_SRC_MOVED_WIN    /*!< Common Fault X Blank Source Moved Window   */
} HAL_HRPWM_Comm_FltBlkSrcTypeDef;

/**
  * @brief HRPWM Common Fault X Counter Reset Mode Definition
  */
typedef enum
{
    HAL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_ALWAYS       = LL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_ALWAYS,       /*!< Common Fault Counter Reset at Reset/Roll-Over    \
                                                                                                         Event Always                                     */
    HAL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_LAST_NO_EVT  = LL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_LAST_NO_EVT   /*!< Common Fault Counter Reset at Reset/Roll-Over    \
                                                                                                         Event Only Last No Event                         */
} HAL_HRPWM_Comm_FltCntrRstModeTypeDef;

/**
  * @brief HRPWM Burst Mode Clock Prescaler Definition
  */
typedef enum
{
    HAL_HRPWM_BURST_CLK_PRESCL_1      = LL_HRPWM_COMM_BURST_CLK_PRESCL_1,       /*!< Burst Mode Clock Prescaler 1       */
    HAL_HRPWM_BURST_CLK_PRESCL_2      = LL_HRPWM_COMM_BURST_CLK_PRESCL_2,       /*!< Burst Mode Clock Prescaler 2       */
    HAL_HRPWM_BURST_CLK_PRESCL_4      = LL_HRPWM_COMM_BURST_CLK_PRESCL_4,       /*!< Burst Mode Clock Prescaler 4       */
    HAL_HRPWM_BURST_CLK_PRESCL_8      = LL_HRPWM_COMM_BURST_CLK_PRESCL_8,       /*!< Burst Mode Clock Prescaler 8       */
    HAL_HRPWM_BURST_CLK_PRESCL_16     = LL_HRPWM_COMM_BURST_CLK_PRESCL_16,      /*!< Burst Mode Clock Prescaler 16      */
    HAL_HRPWM_BURST_CLK_PRESCL_32     = LL_HRPWM_COMM_BURST_CLK_PRESCL_32,      /*!< Burst Mode Clock Prescaler 32      */
    HAL_HRPWM_BURST_CLK_PRESCL_64     = LL_HRPWM_COMM_BURST_CLK_PRESCL_64,      /*!< Burst Mode Clock Prescaler 64      */
    HAL_HRPWM_BURST_CLK_PRESCL_128    = LL_HRPWM_COMM_BURST_CLK_PRESCL_128,     /*!< Burst Mode Clock Prescaler 128     */
    HAL_HRPWM_BURST_CLK_PRESCL_256    = LL_HRPWM_COMM_BURST_CLK_PRESCL_256,     /*!< Burst Mode Clock Prescaler 256     */
    HAL_HRPWM_BURST_CLK_PRESCL_512    = LL_HRPWM_COMM_BURST_CLK_PRESCL_512,     /*!< Burst Mode Clock Prescaler 512     */
    HAL_HRPWM_BURST_CLK_PRESCL_1024   = LL_HRPWM_COMM_BURST_CLK_PRESCL_1024,    /*!< Burst Mode Clock Prescaler 1024    */
    HAL_HRPWM_BURST_CLK_PRESCL_2048   = LL_HRPWM_COMM_BURST_CLK_PRESCL_2048,    /*!< Burst Mode Clock Prescaler 2048    */
    HAL_HRPWM_BURST_CLK_PRESCL_4096   = LL_HRPWM_COMM_BURST_CLK_PRESCL_4096,    /*!< Burst Mode Clock Prescaler 4096    */
    HAL_HRPWM_BURST_CLK_PRESCL_8192   = LL_HRPWM_COMM_BURST_CLK_PRESCL_8192,    /*!< Burst Mode Clock Prescaler 8192    */
    HAL_HRPWM_BURST_CLK_PRESCL_16384  = LL_HRPWM_COMM_BURST_CLK_PRESCL_16384,   /*!< Burst Mode Clock Prescaler 16384   */
    HAL_HRPWM_BURST_CLK_PRESCL_32768  = LL_HRPWM_COMM_BURST_CLK_PRESCL_32768    /*!< Burst Mode Clock Prescaler 32768   */
} HAL_HRPWM_BurstClkPresclTypeDef;

/**
  * @brief HRPWM Burst Mode Trigger Mode Definition
  */
typedef enum
{
    HAL_HRPWM_BURST_TRIG_MODE_ASYNC  = LL_HRPWM_COMM_BURST_TRIG_MODE_ASYNC,   /*!< Burst Mode Asynchronous Trigger Mode   */
    HAL_HRPWM_BURST_TRIG_MODE_SYNC   = LL_HRPWM_COMM_BURST_TRIG_MODE_SYNC     /*!< Burst Mode Synchronous Trigger Mode    */
} HAL_HRPWM_BurstTrigModeTypeDef;

/**
  * @brief HRPWM Burst Mode Clock Source Definition
  */
typedef enum
{
    HAL_HRPWM_BURST_CLK_SRC_MST_PWM_RST_ROLLOVER  = LL_HRPWM_COMM_BURST_CLK_SRC_MST_PWM_RST_ROLLOVER,   /*!< Burst Mode Clock Source Master PWM Reset/Roll-Over */
    HAL_HRPWM_BURST_CLK_SRC_PWM0_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM0_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM0 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_PWM1_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM1_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM1 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_PWM2_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM2_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM2 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_PWM3_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM3_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM3 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_PWM4_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM4_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM4 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_PWM5_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM5_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM5 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_PWM6_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM6_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM6 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_PWM7_RST_ROLLOVER     = LL_HRPWM_COMM_BURST_CLK_SRC_PWM7_RST_ROLLOVER,      /*!< Burst Mode Clock Source PWM7 Reset/Roll-Over       */
    HAL_HRPWM_BURST_CLK_SRC_HRPWM_BM_IN0          = LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN0,           /*!< Burst Mode Clock Source hrpwm_bm_in0               */
    HAL_HRPWM_BURST_CLK_SRC_HRPWM_BM_IN1          = LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN1,           /*!< Burst Mode Clock Source hrpwm_bm_in1               */
    HAL_HRPWM_BURST_CLK_SRC_HRPWM_BM_IN2          = LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN2,           /*!< Burst Mode Clock Source hrpwm_bm_in2               */
    HAL_HRPWM_BURST_CLK_SRC_HRPWM_FUNC_CLK        = LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_FUNC_CLK          /*!< Burst Mode Clock Source HRPWM Function Clock       */
} HAL_HRPWM_BurstClkSrcTypeDef;

/**
  * @brief HRPWM Burst DMA Read/Write Direction Definition
  */
typedef enum
{
    HAL_HRPWM_BURST_DMA_DIR_READ    = 0U,    /*!< HRPWM Burst DMA Read    */
    HAL_HRPWM_BURST_DMA_DIR_WRITE   = 1U     /*!< HRPWM Burst DMA Write   */
} HAL_HRPWM_BurstDmaDirTypeDef;

/**
  * @brief HRPWM Burst Mode Enable Definition
  */
typedef enum
{
    HAL_HRPWM_BURST_MODE_CNT_KEEP = 0U,   /*!< HRPWM Burst Mode counter keep going  */
    HAL_HRPWM_BURST_MODE_CNT_STOP = 1U    /*!< HRPWM Burst Mode counter stop        */
} HAL_HRPWM_BurstModeCntTypeDef;


/**
  * @brief  HRPWM Configuration Structure definition
  */
typedef struct
{
    HAL_HRPWM_Mst_SyncModeTypeDef     SyncOptions;              /*!< Specifies how the HRPWM instance handles the external synchronization signals.
                                                                  The HRPWM instance can be configured to act as a slave (waiting for a trigger
                                                                  to be synchronized) or a master (generating a synchronization signal) or both       */
    HAL_HRPWM_Mst_SyncInSrcTypeDef    SyncInputSource;          /*!< Specifies the external synchronization input source (significant only when
                                                                  the HRPWM instance is configured as a slave)                                        */
    HAL_HRPWM_Mst_SyncOutSrcTypeDef   SyncOutputSource;         /*!< Specifies the source and event to be sent on the external synchronization outputs
                                                                  (significant only when the HRPWM instance is configured as a master)                */
    HAL_HRPWM_Mst_SyncOutPolTypeDef   SyncOutputPolarity;       /*!< Specifies the conditioning of the event to be sent on the external synchronization
                                                                  outputs (significant only when the HRPWM instance is configured as a master)        */
} HAL_HRPWM_InitTypeDef;

/**
  * @brief HRPWM Master/Slave Timer Base Config Structure Definition
  */
typedef struct
{
    uint16_t                    Period;             /*!< Repetition Period                */
    uint8_t                     RepetitionCounter;  /*!< Counter Period                   */
    HAL_HRPWM_ClkPresclTypeDef  PrescalerRatio;     /*!< Clock Prescaler Ratio            */
    HAL_HRPWM_WorkModeTypeDef   Mode;               /*!< Single/Continue operating mode   */
} HAL_HRPWM_TimeBaseCfgTypeDef;

/**
  * @brief  Timer configuration definition
  */
typedef struct
{
    HAL_HRPWM_EnableTypeDef           HalfModeEnable;         /*!< Relevant for all HRPWM timers, including the master.
                                                                Specifies whether or not half mode is enabled */
    HAL_HRPWM_IntlvdModeTypeDef       InterleavedMode;        /*!< Relevant for all HRPWM timers, including the master.
                                                                Specifies whether or not half mode is enabled */
    HAL_HRPWM_EnableTypeDef           StartOnSync;            /*!< Relevant for all HRPWM timers, including the master.
                                                                Specifies whether or not timer is reset by a rising 
                                                                edge on the synchronization input (when enabled). */
    HAL_HRPWM_EnableTypeDef           ResetOnSync;            /*!< Relevant for all HRPWM timers, including the master.
                                                                Specifies whether or not timer is reset by a rising 
                                                                edge on the synchronization input (when enabled). */
    HAL_HRPWM_DACSyncSrcTypeDef       DACSynchro;             /*!< Relevant for all HRPWM timers, including the master.
                                                                Indicates whether or not the a DAC synchronization event is generated. */
    HAL_HRPWM_EnableTypeDef           PreloadEnable;          /*!< Relevant for all HRPWM timers, including the master.
                                                                Specifies whether or not register preload is enabled. */
    HAL_HRPWM_Mst_UpdGateTypeDef      MstUpdateGating;        /*!< Relevant for Master PWM, not including the slave.
                                                                Specifies how the update occurs with respect to a burst DMA transaction. */
    HAL_HRPWM_Slv_UpdGateTypeDef      UpdateGating;           /*!< Relevant for Slave PWM , not including the master.
                                                                Specifies how the update occurs with respect to a burst DMA transaction or
                                                                update enable inputs (Slave timers only). */
    HAL_HRPWM_BurstModeCntTypeDef     BurstMode;              /*!< Relevant for PWM configuration.
                                                                Specifies how the timer behaves during a burst mode operation. */
    HAL_HRPWM_EnableTypeDef           RepetitionUpdate;       /*!< Relevant for all HRPWM timers, including the master.
                                                                Specifies whether or not registers update is triggered by the repetition event. */
    HAL_HRPWM_EnableTypeDef           ResetUpdate;            /*!< Relevant for all HRPWM timers, including the master.
                                                                Specifies whether or not registers update is triggered when the timer counter is reset. */
    HAL_HRPWM_EnableTypeDef           PushPull;               /*!< Relevant for Slave PWM.
                                                                Specifies whether or not the push-pull mode is enabled. */
    HAL_HRPWM_Slv_FltMskTypeDef       FaultEnable;            /*!< Relevant for Slave PWM.
                                                                Specifies which fault channels are enabled for the timer.
                                                                This parameter can be a combination of @ref HAL_HRPWM_Slv_FltMskTypeDef  */
    HAL_HRPWM_EnableTypeDef           DeadTimeInsertion;      /*!< Relevant for Slave PWM.
                                                                Specifies whether or not dead-time insertion is enabled for the PWMx. */
    HAL_HRPWM_Slv_DlyProtMechTypeDef  DelayedProtectionMode;  /*!< Relevant for Slave PWM.
                                                                Specifies the delayed protection mode. */
    HAL_HRPWM_EnableTypeDef           BalancedIdleAutomaticResume; /*!< Indicates whether or not outputs are automatically re-enabled after 
                                                                a balanced idle event.  */
    HAL_HRPWM_Slv_PWMUpdTrigTypeDef   UpdateTrigger;          /*!< Relevant for Slave PWM.
                                                                Specifies source(s) triggering the PWMx registers update.
                                                                This parameter can be a combination of @ref HAL_HRPWM_Slv_PWMUpdTrigTypeDef */
    HAL_HRPWM_Slv_CntrRstEvtTypeDef   ResetTrigger;           /*!< Relevant for Slave PWM.
                                                                Specifies source(s) triggering the PWMx counter reset.
                                                                This parameter can be a combination of @ref HAL_HRPWM_Slv_CntrRstEvtTypeDef */
    HAL_HRPWM_Slv_ReSyncModeTypeDef   ReSyncUpdate;           /*!< Relevant for Slave PWM.
                                                                Specifies whether update source is coming from the timing unit */
} HAL_HRPWM_TimerCfgTypeDef;


/**
  * @brief  Timer control definition
  */
typedef struct
{
    HAL_HRPWM_Slv_DirModeTypeDef  UpDownMode;            /*!<  Relevant for Slave PWM
                                                            Specifies whether or not counter is operating in up or up-down counting mode. */
    HAL_HRPWM_EnableTypeDef       TrigHalf;              /*!<  Relevant for Slave PWM
                                                            Specifies whether or not compare B is operating in Trigger half mode. */
    HAL_HRPWM_EnableTypeDef       GreaterCMPC;           /*!<  Relevant for Slave PWM
                                                            Specifies whether or not compare C is operating in compare match or greater mode. */
    HAL_HRPWM_EnableTypeDef       GreaterCMPA;           /*!<  Relevant for Slave PWM
                                                            Specifies whether or not compare A is operating in compare match or greater mode. */
} HAL_HRPWM_TimerCtlTypeDef;

/**
  * @brief  Timer control definition
  */
typedef struct
{
    HAL_HRPWM_Slv_DACRstTrigSrcTypeDef  DualChannelDacReset;   /*!<  Relevant for Slave PWM
                                                                  Specifies how the hrpwm_dac_reset_trgx trigger is generated.  */
    HAL_HRPWM_Slv_DACStepTrigSrcTypeDef DualChannelDacStep;    /*!<  Relevant for Slave PWM
                                                                  Specifies how the hrpwm_dac_step_trgx trigger is generated. */
    HAL_HRPWM_EnableTypeDef             DualChannelDacEnable;  /*!<  Relevant for Slave PWM
                                                                  Enables or not the dual channel DAC triggering mechanism.  */
} HAL_HRPWM_DualDacCtlTypeDef;

/**
  * @brief  Compare unit configuration definition
  */
typedef struct
{
    uint16_t                        CompareValue;         /*!< Specifies the compare value of the timer compare unit.
                                                            The minimum value must be greater than or equal to 3 periods of the fHRTIM clock. */
    HAL_HRPWM_Slv_CmpAutoDlyTypeDef AutoDelayedMode;      /*!< Specifies the Slave PWMx auto delayed mode for compare unit B or D.            */
    uint16_t                        AutoDelayedTimeout;   /*!< Specifies compare value for timing unit A or C when auto delayed mode with 
                                                            time out is selected. 
                                                            CompareValue +  AutoDelayedTimeout must be less than 0xFFFFU                      */
} HAL_HRPWM_CompareCfgTypeDef;

/**
  * @brief HRPWM Master/Slave System DMA Config Structure Definition
  */
typedef struct 
{
    HAL_HRPWM_EnableTypeDef             WriteRegEnable; /*!< System DMA Write Register Data Enable            */
    uint32_t                            BufferInWords;  /*!< System DMA Write Register Data Buff Size (WORDS) */
    HAL_HRPWM_BurstDMAMstRegUpdTypeDef  MstRegUpdate;   /*!< System DMA Updata Master Register Type           */
    HAL_HRPWM_BurstDMASlvRegUpdTypeDef  SlvRegUpdate;   /*!< System DMA Updata Slave Register Type            */
} HAL_HRPWM_SysDMACfgTypeDef;

/**
  * @brief HRPWM Timer Roll-Over Config Structure Definition
  */
typedef struct 
{
    HAL_HRPWM_Slv_RollOverModeTypeDef CounterRollOver;    /*!< Timer Counter Roll-Over Mode   */
    HAL_HRPWM_Slv_RollOverModeTypeDef OutputRollOver;     /*!< Output Roll-Over Mode          */
    HAL_HRPWM_Slv_RollOverModeTypeDef ADCRollOver;        /*!< ADC Roll-Over Mode             */
    HAL_HRPWM_Slv_RollOverModeTypeDef EventRollOver;      /*!< Event Roll-Over Mode           */
    HAL_HRPWM_Slv_RollOverModeTypeDef FaultRollOver;      /*!< Fault Roll-Over Mode           */
} HAL_HRPWM_RollOverModeCfgTypeDef;


/**
  * @brief  External event filtering in timing units configuration definition
  */
typedef struct
{
    HAL_HRPWM_Slv_ExtEvtFilTypeDef  Filter;       /*!< Specifies the type of event filtering within the timing unit. */
    HAL_HRPWM_EnableTypeDef         Latch;        /*!< Specifies whether or not the signal is latched. */
} HAL_HRPWM_TimerEventFilteringCfgTypeDef;

/**
  * @brief HRPWM Timer Event Counter Config Structure Definition
  */
typedef struct
{
    HAL_HRPWM_Slv_EvtCntrRstModeTypeDef   ResetMode;      /*!< Specifies the External Event Counter Reset Mode. */
    HAL_HRPWM_ExtEvtNumTypeDef            Source;         /*!< Specifies the External Event Counter source selection.   */
    uint8_t                               Counter;        /*!< Specifies the External Event Counter Threshold.
                                                              This parameter can be a number between 0x0 and 0x3F  */
} HAL_HRPWM_ExternalEventCfgTypeDef;

/**
  * @brief  Output configuration definition
  */
typedef struct
{
    HAL_HRPWM_Slv_OutPolTypeDef       Polarity;                    /*!< Specifies the output polarity.  */
    HAL_HRPWM_Slv_OutCtrlEvtTypeDef   SetSource;                   /*!< Specifies the event(s) transitioning the output from its inactive level to its active level.
                                                                      This parameter can be a combination of @ref HAL_HRPWM_Slv_OutCtrlEvtTypeDef */
    HAL_HRPWM_Slv_OutCtrlEvtTypeDef   ResetSource;                 /*!< Specifies the event(s) transitioning the output from its active level to its inactive level.
                                                                      This parameter can be a combination of @ref HAL_HRPWM_Slv_OutCtrlEvtTypeDef */
    HAL_HRPWM_EnableTypeDef           IdleMode;                    /*!< Specifies whether or not the output is affected by a burst mode operation. */
    HAL_HRPWM_Slv_OutIdleLvlTypeDef   IdleLevel;                   /*!< Specifies whether the output level is active or inactive when in IDLE state. */
    HAL_HRPWM_Slv_OutFaultLvlTypeDef  FaultLevel;                  /*!< Specifies whether the output level is active or inactive when in FAULT state. */
    HAL_HRPWM_EnableTypeDef           ChopperModeEnable;           /*!< Indicates whether or not the chopper mode is enabled */
    HAL_HRPWM_EnableTypeDef           BurstModeEntryDelayed;       /*!< Indicates whether or not dead-time is inserted when entering the IDLE state during a burst mode operation. */
} HAL_HRPWM_OutputCfgTypeDef;

/**
  * @brief HRPWM Dead time feature configuration definition
  */
typedef struct
{
    uint16_t                    RisingValue;      /*!< Specifies the dead-time following a rising edge.
                                                      This parameter can be a number between 0x0 and 0xFFFU */
    HAL_HRPWM_Slv_DtDirTypeDef  RisingSign;       /*!< Specifies whether the dead-time is positive or negative on rising edge.  */
    uint16_t                    FallingValue;     /*!< Specifies the dead-time following a falling edge.
                                                      This parameter can be a number between 0x0 and 0xFFFU */
    HAL_HRPWM_Slv_DtDirTypeDef  FallingSign;      /*!< Specifies whether the dead-time is positive or negative on falling edge. */
} HAL_HRPWM_DeadTimeCfgTypeDef;

/**
  * @brief  Chopper mode configuration definition
  */
typedef struct
{
    HAL_HRPWM_Slv_PC_FreqDivTypeDef     CarrierFreq;  /*!< Chopper Frequency Division */
    HAL_HRPWM_Slv_PC_DutyTypeDef        DutyCycle;    /*!< Chopper Duty               */
    HAL_HRWPM_Slv_PC_PulseWidthTypeDef  StartPulse;   /*!< Chopper Start Pulse Width  */
} HAL_HRPWM_ChopperModeCfgTypeDef;

/**
  * @brief  Capture unit content definition
  */
typedef struct
{
    uint32_t  Value;    /*!< Holds the counter value when the capture event occurred.
                            This parameter can be a number between 0x0 and 0xFFFFU */
    uint32_t  Dir;      /*!< Holds the counting direction value  when the capture event occurred. @ref HAL_HRPWM_Slv_CapDirTypeDef  */
} HAL_HRPWM_CaptureValueTypeDef;

/**
  * @brief  Capture unit configuration definition
  */
typedef struct
{
    HAL_HRPWM_Slv_CapTrigEvtTypeDef Trigger;          /*!< Specifies source(s) triggering the capture.
                                                          This parameter can be a combination of @ref HAL_HRPWM_Slv_CapTrigEvtTypeDef */
} HAL_HRPWM_CaptureCfgTypeDef;

/**
  * @brief  External event channel configuration definition
  */
typedef struct
{
    HAL_HRPWM_Comm_ExtEvtXInputSrcTypeDef Source;        /*!< Identifies the source of the external event.  */
    HAL_HRPWM_Comm_ExtEvtInputPolTypeDef  Polarity;      /*!< Specifies the polarity of the external event (in case of level sensitivity).  */
    HAL_HRPWM_Comm_ExtEvtInputEdgeTypeDef Sensitivity;   /*!< Specifies the sensitivity of the external event. */
    uint8_t                               Filter;        /*!< Defines the frequency used to sample the External Event and the length of the digital filter.
                                                              Filter Time = N×1/f_sample */
    HAL_HRPWM_EnableTypeDef               FastMode;      /*!< Indicates whether or not low latency mode is enabled for the external event.  */
} HAL_HRPWM_EventCfgTypeDef;

/**
  * @brief  Fault configuration definition
  */
typedef struct
{
    HAL_HRPWM_Comm_FltXInputSrcTypeDef  Source;       /*!< Identifies the source of the fault.  */
    HAL_HRPWM_Comm_FltInputPolTypeDef   Polarity;     /*!< Specifies the polarity of the fault event. */
    uint8_t                             Filter;       /*!< Defines the frequency used to sample the Fault input and the length of the digital filter.
                                                          Filter Time = N×1/f_sample*/
} HAL_HRPWM_FaultCfgTypeDef;

/**
  * @brief  Fault Counter configuration definition
  */
typedef struct
{
    uint8_t                               Threshold;  /*!< Specifies the Fault counter Threshold.
                                                          This parameter can be a number between 0x0 and 0xF  */
    HAL_HRPWM_Comm_FltCntrRstModeTypeDef  ResetMode;  /*!< Specifies the reset mode of a fault event counter.  */
} HAL_HRPWM_FaultCntrCfgTypeDef;

/**
  * @brief  Fault blanking configuration definition
  */
typedef struct
{
  HAL_HRPWM_EnableTypeDef           BlankingEnable;   /*!< Fault Blank Enable */
  HAL_HRPWM_Comm_FltBlkSrcTypeDef   BlankingSource;   /*!< Specifies the blanking source of a fault event.  */
} HAL_HRPWM_FaultBlankingCfgTypeDef;

/**
  * @brief  ADC trigger configuration definition
  */
typedef struct
{
    HAL_HRPWM_Comm_ADCTrigUpdSrcTypeDef     UpdateSource;   /*!< Specifies the ADC trigger update source.  */
    HAL_HRPWM_Comm_ADCTrigEvtSrcTypeDef     Trigger;        /*!< Specifies the event(s) triggering the ADC0/1/2/3 conversion.
                                                              This parameter can be a combination of @ref HAL_HRPWM_Comm_ADCTrigEvtSrcTypeDef  */
    HAL_HRPWM_Comm_ADC468TrigEvtSrcTypeDef  Trigger468;     /*!< Specifies the event(s) triggering the ADC4/6/8 conversion.  */
    HAL_HRPWM_Comm_ADC579TrigEvtSrcTypeDef  Trigger579;     /*!< Specifies the event(s) triggering the ADC5/7/9 conversion.  */
    HAL_HRPWM_Comm_ADCTrigEvtLenTypeDef     TriggerLength;  /*!< Specifies the ADC trigger length         */
} HAL_HRPWM_ADCTriggerCfgTypeDef;

/**
  * @brief  Burst mode configuration definition
  */
typedef struct
{
    HAL_HRPWM_BurstWorkModeTypeDef        Mode;           /*!< Specifies the burst mode operating mode. */
    HAL_HRPWM_BurstClkSrcTypeDef          ClockSource;    /*!< Specifies the burst mode clock source. */
    HAL_HRPWM_BurstClkPresclTypeDef       Prescaler;      /*!< Specifies the burst mode prescaler. */
    HAL_HRPWM_EnableTypeDef               PreloadEnable;  /*!< Specifies whether or not preload is enabled for burst mode related registers. */
    HAL_HRPWM_BurstTrigEvtTypeDef         Trigger;        /*!< Specifies the event(s) triggering the burst operation.
                                                              This parameter can be a combination of @ref HAL_HRPWM_BurstTrigEvtTypeDef  */
    uint16_t                              IdleDuration;   /*!< Specifies number of periods during which the selected timers are in idle state. */
    uint16_t                              Period;         /*!< Specifies burst mode repetition period.
                                                              This parameter must be a number greater than or equal to 1  */
    HAL_HRPWM_BurstTrigModeTypeDef        TriggerMode;    /*!< Specifies burst mode trigger mode */
} HAL_HRPWM_BurstModeCfgTypeDef;


typedef struct HAL_HRPWM_HandleStructDef HAL_HRPWM_HandleTypeDef; /*!< HAL HRPWM handle structure type */

/**
  * @brief  CMP Handle Structure definition
  */
struct HAL_HRPWM_HandleStructDef
{
    HRPWM_TypeDef                     *Instance;          /*!< Register base address    */
    volatile HAL_HRPWM_StateTypeDef   State;              /*!< Global state             */
    volatile uint32_t                 ErrorCode;          /*!< Error code               */
    const void                        *pUserData;         /*!< User data pointer        */
};

/**
  * @}
  */ /* HRPWM_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup HRPMW_HAL_Exported_Functions
  * @{
  */

/** @addtogroup HRPMW_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_HRPWM_Init(HAL_HRPWM_HandleTypeDef *Handle, 
                                 HRPWM_TypeDef *HRPWMx, 
                                 const HAL_HRPWM_InitTypeDef *pInit);
HAL_StatusTypeDef HAL_HRPWM_DeInit(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MspInit(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MspDeInit(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_IoInit(HRPWM_TypeDef *HRPWMx);
void HAL_HRPWM_IoDeInit(HRPWM_TypeDef *HRPWMx);
/**
  * @}
  */


/** @addtogroup HRPMW_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_HRPWM_TimeBaseConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                           const HAL_HRPWM_TimeBaseCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_WaveformTimerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                const HAL_HRPWM_TimerCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_WaveformTimerControl(HAL_HRPWM_HandleTypeDef *Handle,
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 const HAL_HRPWM_TimerCtlTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_DualChannelDacConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 const HAL_HRPWM_DualDacCtlTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_WaveformCompareConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                  HAL_HRPWM_CmpUnitTypeDef CmpUnit, 
                                                  const HAL_HRPWM_CompareCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_WaveformOutputConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 HAL_HRPWM_OutputChnlTypeDef Channel,
                                                 const HAL_HRPWM_OutputCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_WaveformCaptureConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                                  HAL_HRPWM_CapChnlTypeDef Channel,
                                                  const HAL_HRPWM_CaptureCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_CaptureModeConfig(HAL_HRPWM_HandleTypeDef*Handle,
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                              HAL_HRPWM_CapChnlTypeDef Channel,
                                              HAL_HRPWM_Slv_CapModeTypeDef Mode);

HAL_StatusTypeDef HAL_HRPWM_DeadTimeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                           const HAL_HRPWM_DeadTimeCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_ChopperModeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                              const HAL_HRPWM_ChopperModeCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_TimerEventFilteringConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                      HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                      HAL_HRPWM_ExtEvtNumTypeDef EvtNum, 
                                                      const HAL_HRPWM_TimerEventFilteringCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                  HAL_HRPWM_EvtCntrTypeDef EvtCntr, 
                                                  const HAL_HRPWM_ExternalEventCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_EventPrescalerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                 HAL_HRPWM_Comm_ExtEvtSampClkDivTypeDef Prescaler);

HAL_StatusTypeDef HAL_HRPWM_EventConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                        HAL_HRPWM_ExtEvtNumTypeDef EvtNum,
                                        const HAL_HRPWM_EventCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_FaultPrescalerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                 HAL_HRPWM_FltNumTypeDef FltNum, 
                                                 HAL_HRPWM_Comm_FltSampClkDivTypeDef Prescaler);

HAL_StatusTypeDef HAL_HRPWM_FaultConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                        HAL_HRPWM_FltNumTypeDef FltNum, 
                                        const HAL_HRPWM_FaultCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_FaultCounterConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_FltNumTypeDef FltNum, 
                                               const HAL_HRPWM_FaultCntrCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_FaultBlankingConfigAndEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                                        HAL_HRPWM_FltNumTypeDef FltNum, 
                                                        const HAL_HRPWM_FaultBlankingCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_FaultModeCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_FltNumTypeDef FltNum, 
                                         HAL_HRPWM_EnableTypeDef Enable);

HAL_StatusTypeDef HAL_HRPWM_ADCPostScalerConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                                HAL_HRPWM_ADCTrigNumTypeDef TrigNum,
                                                uint32_t Postscaler);

HAL_StatusTypeDef HAL_HRPWM_ADCTriggerConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                            HAL_HRPWM_ADCTrigNumTypeDef TrigNum,
                                            const HAL_HRPWM_ADCTriggerCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_RollOverModeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                               const HAL_HRPWM_RollOverModeCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_DLLCurrentConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                             HAL_HRPWM_Comm_DLLCurTypeDef Current);

HAL_StatusTypeDef HAL_HRPWM_BurstModeConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                            const HAL_HRPWM_BurstModeCfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_BurstDMAConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                           HAL_HRPWM_BurstDMARegUpdTypeDef Registers);

HAL_StatusTypeDef HAL_HRPWM_BurstDMAUpdateCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                              HAL_HRPWM_EnableTypeDef Enable);

HAL_StatusTypeDef HAL_HRPWM_BurstBufferAddressConfig(HAL_HRPWM_HandleTypeDef *Handle,
                                                     HAL_HRPWM_BurstDmaDirTypeDef ReadWrite,
                                                     uint32_t BufferAddress);

HAL_StatusTypeDef HAL_HRPWM_BurstModeCtl(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_EnableTypeDef Enable);

HAL_StatusTypeDef HAL_HRPWM_BurstModeSoftwareTrigger(HAL_HRPWM_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_HRPWM_SysDMAConfig(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                         const HAL_HRPWM_SysDMACfgTypeDef *pCfg);

HAL_StatusTypeDef HAL_HRPWM_DMAEnableCtl(HAL_HRPWM_HandleTypeDef *Handle,
                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                         uint32_t Mask);

/**
  * @}
  */ /* HRPMW_HAL_EF_Configuration */


/** @addtogroup HRPMW_HAL_EF_Operation
  * @{
  */

HAL_StatusTypeDef HAL_HRPWM_SimpleBaseStart(HAL_HRPWM_HandleTypeDef *Handle, 
                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx);

HAL_StatusTypeDef HAL_HRPWM_SimpleBaseStop(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMIdxTypeDef PwmIdx);

HAL_StatusTypeDef HAL_HRPWM_WaveformCountStart(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_WaveformCountStop(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_SoftwareReset(HAL_HRPWM_HandleTypeDef *Handle, 
                                          HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_WaveformOutputStart(HAL_HRPWM_HandleTypeDef *Handle, 
                                                HAL_HRPWM_PWMOutputMaskTypeDef OutputChannels);

HAL_StatusTypeDef HAL_HRPWM_WaveformOutputStop(HAL_HRPWM_HandleTypeDef *Handle, 
                                               HAL_HRPWM_PWMOutputMaskTypeDef OutputChannels);

HAL_StatusTypeDef HAL_HRPWM_WaveformSetOutputLevel(HAL_HRPWM_HandleTypeDef *Handle, 
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                   HAL_HRPWM_OutputChnlTypeDef Channel,
                                                   HAL_HRPWM_Slv_OutLvlStateTypeDef Output);

HAL_StatusTypeDef HAL_HRPWM_OutputSwapEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                             HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_OutputSwapDisable(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_UpdateEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                         HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_UpdateDisable(HAL_HRPWM_HandleTypeDef *Handle, 
                                          HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_SoftwareUpdate(HAL_HRPWM_HandleTypeDef *Handle, 
                                           HAL_HRPWM_PWMMaskTypeDef PwmMsk);

HAL_StatusTypeDef HAL_HRPWM_DLLStart(HAL_HRPWM_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_HRPWM_DLLStop(HAL_HRPWM_HandleTypeDef *Handle);

HAL_StatusTypeDef HAL_HRPWM_FaultCounterReset(HAL_HRPWM_HandleTypeDef *Handle, 
                                              HAL_HRPWM_FltNumTypeDef FltNum);

HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterEnable(HAL_HRPWM_HandleTypeDef *Handle, 
                                                  HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                  HAL_HRPWM_EvtCntrTypeDef EvtCntr);

HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterDisable(HAL_HRPWM_HandleTypeDef *Handle, 
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                   HAL_HRPWM_EvtCntrTypeDef EvtCntr);

HAL_StatusTypeDef HAL_HRPWM_ExtEventCounterReset(HAL_HRPWM_HandleTypeDef *Handle, 
                                                 HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                 HAL_HRPWM_EvtCntrTypeDef EvtCntr);                                                   

HAL_StatusTypeDef HAL_HRPWM_SoftwareCapture(HAL_HRPWM_HandleTypeDef *Handle, 
                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                                            HAL_HRPWM_CapChnlTypeDef Channel);                                                 
/**
  * @}
  */ /* HRPMW_HAL_EF_Operation */

/** @addtogroup HRPMW_HAL_EF_State
  * @{
  */

void HAL_HRPWM_GetCaptured(const HAL_HRPWM_HandleTypeDef *Handle, 
                           HAL_HRPWM_PWMIdxTypeDef PwmIdx, 
                           HAL_HRPWM_CapChnlTypeDef Channel,
                           HAL_HRPWM_CaptureValueTypeDef *Captured);

uint32_t HAL_HRPWM_WaveformGetOutputLevel(const HAL_HRPWM_HandleTypeDef *Handle,
                                          HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                          HAL_HRPWM_OutputChnlTypeDef Channel);

uint32_t HAL_HRPWM_GetDelayedProtectionStatus(const HAL_HRPWM_HandleTypeDef *Handle,
                                              HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                              HAL_HRPWM_OutputChnlTypeDef Channel);

uint32_t HAL_HRPWM_GetCurrentPushPullStatus(const HAL_HRPWM_HandleTypeDef *Handle,
                                            HAL_HRPWM_PWMIdxTypeDef PwmIdx);

uint32_t HAL_HRPWM_GetIdlePushPullStatus(const HAL_HRPWM_HandleTypeDef *Handle,
                                         HAL_HRPWM_PWMIdxTypeDef PwmIdx);

uint32_t HAL_HRPWM_GetBurstStatus(const HAL_HRPWM_HandleTypeDef *Handle);

HAL_HRPWM_Slv_OutStateTypeDef HAL_HRPWM_WaveformGetOutputState(const HAL_HRPWM_HandleTypeDef *Handle, 
                                                               HAL_HRPWM_PWMIdxTypeDef PwmIdx,
                                                               HAL_HRPWM_OutputChnlTypeDef Channel);

/**
  * @}
  */ /* HRPMW_HAL_EF_State */

/** @addtogroup HRPMW_HAL_Exported_Functions_Interrupt
  * @{
  */

HAL_StatusTypeDef HAL_HRPWM_InterruptRequestEnable(HAL_HRPWM_HandleTypeDef *Handle,
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,  
                                                   HAL_HRPWM_PWMGrpTypeDef Group,
                                                   uint32_t InterruptRequests);

HAL_StatusTypeDef HAL_HRPWM_InterruptRequestDisable(HAL_HRPWM_HandleTypeDef *Handle,
                                                   HAL_HRPWM_PWMIdxTypeDef PwmIdx,  
                                                   HAL_HRPWM_PWMGrpTypeDef Group,
                                                   uint32_t InterruptRequests);

//Master PWM Interrrupt Handler
void HAL_HRPWM_MST_IRQHandler(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_CompareAEventCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_CompareBEventCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_CompareCEventCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_CompareDEventCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_PeriodEventCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_SynchronizationEventCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_RegistersUpdateCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_CounterResetCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_MST_RepetitionEventCallback(HAL_HRPWM_HandleTypeDef *Handle);

//Slave PWMx Interrupt Handler
void HAL_HRPWM_SLV_IRQHandler(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_CompareAEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_CompareBEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_CompareCEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_CompareDEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_PeriodOrRollOverCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_PeriodEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_OutputASetCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_OutputAClearCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_OutputBSetCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_OutputBClearCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_CounterResetCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_RepetitionEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_CaptureAEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_CaptureBEventCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);
void HAL_HRPWM_SLV_DelayedProtectionCallback(HAL_HRPWM_HandleTypeDef *Handle, HAL_HRPWM_PWMIdxTypeDef PwmIdx);

//Common Interrupt Handler
void HAL_HRPWM_COM_IRQHandler(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault0Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault1Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault2Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault3Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault4Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault5Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault6Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_Fault7Callback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_SystemFaultCallback(HAL_HRPWM_HandleTypeDef *Handle);
void HAL_HRPWM_COM_BurstModePeriodCallback(HAL_HRPWM_HandleTypeDef *Handle);
/**
  * @}
  */

/**
  * @}
  */ /* HRPMW_HAL_Exported_Functions */


/**
  * @}
  */ /* HRPWM_HAL */

#endif  /* HAL_HRPWM_MODULE_ENABLED */
#endif  /* HAL_MODULE_ENABLED */
#endif  /* HRPWM */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_HRPWM_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

