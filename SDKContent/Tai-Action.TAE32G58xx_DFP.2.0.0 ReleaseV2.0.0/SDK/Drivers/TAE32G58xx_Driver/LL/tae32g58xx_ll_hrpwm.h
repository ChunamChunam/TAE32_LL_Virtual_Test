/**
  ******************************************************************************
  * @file    tae32g58xx_ll_hrpwm.h
  * @author  Tai-Action SD Team
  * @brief   Header file for HRPWM LL module
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
#ifndef _TAE32G58XX_LL_HRPWM_H_
#define _TAE32G58XX_LL_HRPWM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(HRPWM)

/** @defgroup HRPWM_LL HRPWM LL
  * @brief    HRPWM LL Module Driver
  * @{
  */

/* Exported Constants --------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Constants HRPWM LL Exported Constants
  * @brief    HRPWM LL Exported Constants
  * @{
  */

/** @defgroup HRPWM_LL_EC_Information LL HRPWM Information
  * @brief LL HRPWM Information 
  * @{
  */

/**
  * @brief HRPWM Slave PWM Numbers Definition
  */
#define LL_HRPWM_PWMx_NUMS (8U)

/**
  * @brief LL HRPWM MCR1 Counter Enable All Mask Definition
  */
#define LL_HRPWM_MCR1_PWM_EN_MSK                            ((HRPWM_MST_MCR1_MCEN_Msk  | HRPWM_MST_MCR1_CEN0_Msk | \
                                                              HRPWM_MST_MCR1_CEN1_Msk  | HRPWM_MST_MCR1_CEN2_Msk | \
                                                              HRPWM_MST_MCR1_CEN3_Msk  | HRPWM_MST_MCR1_CEN4_Msk | \
                                                              HRPWM_MST_MCR1_CEN5_Msk  | HRPWM_MST_MCR1_CEN6_Msk | \
                                                              HRPWM_MST_MCR1_CEN7_Msk)) 

/**
  * @brief LL HRPWM MDIER Master DMA Enable All Mask Definition
  */
#define LL_HRPWM_MDIER_DMA_EN_MSK                           ((HRPWM_MST_MDIER_MCMPADE_Msk | HRPWM_MST_MDIER_MCMPBDE_Msk | \
                                                              HRPWM_MST_MDIER_MCMPCDE_Msk | HRPWM_MST_MDIER_MCMPDDE_Msk | \
                                                              HRPWM_MST_MDIER_MPERDE_Msk  | HRPWM_MST_MDIER_SYNCDE_Msk  | \
                                                              HRPWM_MST_MDIER_MUPDDE_Msk  |  HRPWM_MST_MDIER_MRSTDE_Msk | \
                                                              HRPWM_MST_MDIER_MREPDE_Msk)) 

/**
  * @brief LL HRPWM MDIER Master Interrput Enable All Mask Definition
  */
#define LL_HRPWM_MDIER_MST_IT_EN_MSK                        ((HRPWM_MST_MDIER_MCMPAIE_Msk | HRPWM_MST_MDIER_MCMPBIE_Msk | \
                                                              HRPWM_MST_MDIER_MCMPCIE_Msk | HRPWM_MST_MDIER_MCMPDIE_Msk | \
                                                              HRPWM_MST_MDIER_MPERIE_Msk  | HRPWM_MST_MDIER_SYNCIE_Msk  | \
                                                              HRPWM_MST_MDIER_MUPDIE_Msk  |  HRPWM_MST_MDIER_MRSTIE_Msk | \
                                                              HRPWM_MST_MDIER_MREPIE_Msk)) 

/**
  * @brief HRPWM Master Interrupt Enable Mask Definition
  */
#define LL_HRPWM_MST_MDIER_ITEnMskTypeDef                   uint32_t

#define LL_HRPWM_MST_MDIER_MREPIE            (HRPWM_MST_MDIER_MREPIE_Msk)         /*!< MDIER_MREPIE Mask        */
#define LL_HRPWM_MST_MDIER_MRSTIE            (HRPWM_MST_MDIER_MRSTIE_Msk)         /*!< MDIER_MRSTIE Mask        */
#define LL_HRPWM_MST_MDIER_MUPDIE            (HRPWM_MST_MDIER_MUPDIE_Msk)         /*!< MDIER_MUPDIE Mask        */
#define LL_HRPWM_MST_MDIER_SYNCIE            (HRPWM_MST_MDIER_SYNCIE_Msk)         /*!< MDIER_SYNCIE Mask        */
#define LL_HRPWM_MST_MDIER_MPERIE            (HRPWM_MST_MDIER_MPERIE_Msk)         /*!< MDIER_MPERIE Mask        */
#define LL_HRPWM_MST_MDIER_MCMPDIE           (HRPWM_MST_MDIER_MCMPDIE_Msk)        /*!< MDIER_MCMPDIE Mask       */
#define LL_HRPWM_MST_MDIER_MCMPCIE           (HRPWM_MST_MDIER_MCMPCIE_Msk)        /*!< MDIER_MCMPCIE Mask       */
#define LL_HRPWM_MST_MDIER_MCMPBIE           (HRPWM_MST_MDIER_MCMPBIE_Msk)        /*!< MDIER_MCMPBIE Mask       */
#define LL_HRPWM_MST_MDIER_MCMPAIE           (HRPWM_MST_MDIER_MCMPAIE_Msk)        /*!< MDIER_MCMPAIE Mask       */

/**
  * @brief LL HRPWM MISR Master Interrput Enable All Mask Definition
  */
#define LL_HRPWM_MISR_MST_IT_FLAG_MSK                       ((HRPWM_MST_MISR_MCMPA_Msk | HRPWM_MST_MISR_MCMPB_Msk | \
                                                              HRPWM_MST_MISR_MCMPC_Msk | HRPWM_MST_MISR_MCMPD_Msk | \
                                                              HRPWM_MST_MISR_MPER_Msk  | HRPWM_MST_MISR_SYNC_Msk  | \
                                                              HRPWM_MST_MISR_MUPD_Msk  | HRPWM_MST_MISR_MRST_Msk  | \
                                                              HRPWM_MST_MISR_MREP_Msk))             

/**
  * @brief HRPWM Master Interrupt Pending Mask Definition
  */
#define LL_HRPWM_MST_MISR_ITPendingMskTypeDef               uint32_t

#define LL_HRPWM_MST_MISR_MREP               (HRPWM_MST_MISR_MREP_Msk)            /*!< MISR_MREP Mask           */
#define LL_HRPWM_MST_MISR_MRST               (HRPWM_MST_MISR_MRST_Msk)            /*!< MISR_MRST Mask           */
#define LL_HRPWM_MST_MISR_MUPD               (HRPWM_MST_MISR_MUPD_Msk)            /*!< MISR_MUPD Mask           */
#define LL_HRPWM_MST_MISR_SYNC               (HRPWM_MST_MISR_SYNC_Msk)            /*!< MISR_SYNC Mask           */
#define LL_HRPWM_MST_MISR_MPER               (HRPWM_MST_MISR_MPER_Msk)            /*!< MISR_MPER Mask           */
#define LL_HRPWM_MST_MISR_MCMPD              (HRPWM_MST_MISR_MCMPD_Msk)           /*!< MISR_MCMPD Mask          */
#define LL_HRPWM_MST_MISR_MCMPC              (HRPWM_MST_MISR_MCMPC_Msk)           /*!< MISR_MCMPC Mask          */
#define LL_HRPWM_MST_MISR_MCMPB              (HRPWM_MST_MISR_MCMPB_Msk)           /*!< MISR_MCMPB Mask          */
#define LL_HRPWM_MST_MISR_MCMPA              (HRPWM_MST_MISR_MCMPA_Msk)           /*!< MISR_MCMPA Mask          */

/**
  * @brief LL HRPWM MDMAUR Master System DMA Update All Mask Definition
  */
#define LL_HRPWM_MDMAUR_SYSDMA_UPD_MSK                      ((HRPWM_MST_MDMAUR_MCR0_Msk   | HRPWM_MST_MDMAUR_MCR1_Msk   | \
                                                              HRPWM_MST_MDMAUR_MISR_Msk   | HRPWM_MST_MDMAUR_MDIER_Msk  | \
                                                              HRPWM_MST_MDMAUR_MCNTR_Msk  | HRPWM_MST_MDMAUR_MPER_Msk   | \
                                                              HRPWM_MST_MDMAUR_MREP_Msk   | HRPWM_MST_MDMAUR_MCMPAR_Msk | \
                                                              HRPWM_MST_MDMAUR_MCMPBR_Msk | HRPWM_MST_MDMAUR_MCMPCR_Msk | \
                                                              HRPWM_MST_MDMAUR_MCMPDR_Msk )) 

/**
  * @brief LL HRPWM PWMCR1 Slave Update Event Trigger All Mask Definition
  */
#define LL_HRPWM_PWMCR1_UPD_TRG_PWMx_MSK                    ((HRPWM_SLV0_PWMCR1_UPD7_Msk | HRPWM_SLV0_PWMCR1_UPD6_Msk | \
                                                              HRPWM_SLV0_PWMCR1_UPD5_Msk | HRPWM_SLV0_PWMCR1_UPD4_Msk | \
                                                              HRPWM_SLV0_PWMCR1_UPD3_Msk | HRPWM_SLV0_PWMCR1_UPD2_Msk | \
                                                              HRPWM_SLV0_PWMCR1_UPD1_Msk | HRPWM_SLV0_PWMCR1_UPD0_Msk | \
                                                              HRPWM_SLV0_PWMCR1_MUPD_Msk))

/**
  * @brief LL HRPWM PWMDIER Slave DMA Enable All Mask Definition
  */
#define LL_HRPWM_PWMDIER_PWMx_DMA_EN_MSK                    ((HRPWM_SLV0_PWMDIER_DLYPRTDE_Msk | HRPWM_SLV0_PWMDIER_CAPBDE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_CAPADE_Msk   | HRPWM_SLV0_PWMDIER_REPDE_Msk  | \
                                                              HRPWM_SLV0_PWMDIER_RSTDE_Msk    | HRPWM_SLV0_PWMDIER_CLRBDE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_SETBDE_Msk   | HRPWM_SLV0_PWMDIER_CLRADE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_SETADE_Msk   | HRPWM_SLV0_PWMDIER_UPDDE_Msk  | \
                                                              HRPWM_SLV0_PWMDIER_PERDE_Msk    | HRPWM_SLV0_PWMDIER_CMPDDE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_CMPCDE_Msk   | HRPWM_SLV0_PWMDIER_CMPBDE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_CMPADE_Msk))

/**
  * @brief LL HRPWM PWMDIER Slave Interrput Enable All Mask Definition
  */
#define LL_HRPWM_PWMDIER_PWMx_IT_EN_MSK                     ((HRPWM_SLV0_PWMDIER_DLYPRTIE_Msk | HRPWM_SLV0_PWMDIER_CAPBIE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_CAPAIE_Msk   | HRPWM_SLV0_PWMDIER_REPIE_Msk  | \
                                                              HRPWM_SLV0_PWMDIER_RSTIE_Msk    | HRPWM_SLV0_PWMDIER_CLRBIE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_SETBIE_Msk   | HRPWM_SLV0_PWMDIER_CLRAIE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_SETAIE_Msk   | HRPWM_SLV0_PWMDIER_UPDIE_Msk  | \
                                                              HRPWM_SLV0_PWMDIER_PERIE_Msk    | HRPWM_SLV0_PWMDIER_CMPDIE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_CMPCIE_Msk   | HRPWM_SLV0_PWMDIER_CMPBIE_Msk | \
                                                              HRPWM_SLV0_PWMDIER_CMPAIE_Msk))

/**
  * @brief HRPWM Slave Interrupt Enable Mask Definition
  */
#define LL_HRPWM_SLV_PWMDIER_ITEnMskTypeDef                 uint32_t

#define LL_HRPWM_SLV_PWMDIER_DLYPRTIE        (HRPWM_SLV0_PWMDIER_DLYPRTIE_Msk)    /*!< PWMDIER_DLYPRTIE Mask    */
#define LL_HRPWM_SLV_PWMDIER_CAPBIE          (HRPWM_SLV0_PWMDIER_CAPBIE_Msk)      /*!< PWMDIER_CAPBIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_CAPAIE          (HRPWM_SLV0_PWMDIER_CAPAIE_Msk)      /*!< PWMDIER_CAPAIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_REPIE           (HRPWM_SLV0_PWMDIER_REPIE_Msk)       /*!< PWMDIER_REPIE Mask       */
#define LL_HRPWM_SLV_PWMDIER_RSTIE           (HRPWM_SLV0_PWMDIER_RSTIE_Msk)       /*!< PWMDIER_RSTIE Mask       */
#define LL_HRPWM_SLV_PWMDIER_CLRBIE          (HRPWM_SLV0_PWMDIER_CLRBIE_Msk)      /*!< PWMDIER_CLRBIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_SETBIE          (HRPWM_SLV0_PWMDIER_SETBIE_Msk)      /*!< PWMDIER_SETBIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_CLRAIE          (HRPWM_SLV0_PWMDIER_CLRAIE_Msk)      /*!< PWMDIER_CLRAIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_SETAIE          (HRPWM_SLV0_PWMDIER_SETAIE_Msk)      /*!< PWMDIER_SETAIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_UPDIE           (HRPWM_SLV0_PWMDIER_UPDIE_Msk)       /*!< PWMDIER_UPDIE Mask       */
#define LL_HRPWM_SLV_PWMDIER_PERIE           (HRPWM_SLV0_PWMDIER_PERIE_Msk)       /*!< PWMDIER_PERIE Mask       */
#define LL_HRPWM_SLV_PWMDIER_CMPDIE          (HRPWM_SLV0_PWMDIER_CMPDIE_Msk)      /*!< PWMDIER_CMPDIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_CMPCIE          (HRPWM_SLV0_PWMDIER_CMPCIE_Msk)      /*!< PWMDIER_CMPCIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_CMPBIE          (HRPWM_SLV0_PWMDIER_CMPBIE_Msk)      /*!< PWMDIER_CMPBIE Mask      */
#define LL_HRPWM_SLV_PWMDIER_CMPAIE          (HRPWM_SLV0_PWMDIER_CMPAIE_Msk)      /*!< PWMDIER_CMPAIE Mask      */

/**
  * @brief LL HRPWM PWMISR Slave Interrput Flag All Mask Definition
  */
#define LL_HRPWM_PWMISR_PWMx_IT_FLAG_MSK                    ((HRPWM_SLV0_PWMISR_DLYPRT_Msk | HRPWM_SLV0_PWMISR_CAPB_Msk | \
                                                              HRPWM_SLV0_PWMISR_CAPA_Msk   | HRPWM_SLV0_PWMISR_REP_Msk  | \
                                                              HRPWM_SLV0_PWMISR_RST_Msk    | HRPWM_SLV0_PWMISR_CLRB_Msk | \
                                                              HRPWM_SLV0_PWMISR_SETB_Msk   | HRPWM_SLV0_PWMISR_CLRA_Msk | \
                                                              HRPWM_SLV0_PWMISR_SETA_Msk   | HRPWM_SLV0_PWMISR_UPD_Msk  | \
                                                              HRPWM_SLV0_PWMISR_PER_Msk    | HRPWM_SLV0_PWMISR_CMPD_Msk | \
                                                              HRPWM_SLV0_PWMISR_CMPC_Msk   | HRPWM_SLV0_PWMISR_CMPB_Msk | \
                                                              HRPWM_SLV0_PWMISR_CMPA_Msk))

/**
  * @brief HRPWM Slave Interrupt Pending Mask Definition
  */
#define LL_HRPWM_SLV_PWMISR_ITPendingMskTypeDef             uint32_t

#define LL_HRPWM_SLV_PWMISR_DLYPRT           (HRPWM_SLV0_PWMISR_DLYPRT_Msk)       /*!< PWMISR_DLYPRT Mask       */
#define LL_HRPWM_SLV_PWMISR_CAPB             (HRPWM_SLV0_PWMISR_CAPB_Msk)         /*!< PWMISR_CAPB Mask         */
#define LL_HRPWM_SLV_PWMISR_CAPA             (HRPWM_SLV0_PWMISR_CAPA_Msk)         /*!< PWMISR_CAPA Mask         */
#define LL_HRPWM_SLV_PWMISR_REP              (HRPWM_SLV0_PWMISR_REP_Msk)          /*!< PWMISR_REP Mask          */
#define LL_HRPWM_SLV_PWMISR_RST              (HRPWM_SLV0_PWMISR_RST_Msk)          /*!< PWMISR_RST Mask          */
#define LL_HRPWM_SLV_PWMISR_CLRB             (HRPWM_SLV0_PWMISR_CLRB_Msk)         /*!< PWMISR_CLRB Mask         */
#define LL_HRPWM_SLV_PWMISR_SETB             (HRPWM_SLV0_PWMISR_SETB_Msk)         /*!< PWMISR_SETB Mask         */
#define LL_HRPWM_SLV_PWMISR_CLRA             (HRPWM_SLV0_PWMISR_CLRA_Msk)         /*!< PWMISR_CLRA Mask         */
#define LL_HRPWM_SLV_PWMISR_SETA             (HRPWM_SLV0_PWMISR_SETA_Msk)         /*!< PWMISR_SETA Mask         */
#define LL_HRPWM_SLV_PWMISR_UPD              (HRPWM_SLV0_PWMISR_UPD_Msk)          /*!< PWMISR_UPD Mask          */
#define LL_HRPWM_SLV_PWMISR_PER              (HRPWM_SLV0_PWMISR_PER_Msk)          /*!< PWMISR_PER Mask          */
#define LL_HRPWM_SLV_PWMISR_CMPD             (HRPWM_SLV0_PWMISR_CMPD_Msk)         /*!< PWMISR_CMPD Mask         */
#define LL_HRPWM_SLV_PWMISR_CMPC             (HRPWM_SLV0_PWMISR_CMPC_Msk)         /*!< PWMISR_CMPC Mask         */
#define LL_HRPWM_SLV_PWMISR_CMPB             (HRPWM_SLV0_PWMISR_CMPB_Msk)         /*!< PWMISR_CMPB Mask         */
#define LL_HRPWM_SLV_PWMISR_CMPA             (HRPWM_SLV0_PWMISR_CMPA_Msk)         /*!< PWMISR_CMPA Mask         */

/**
  * @brief LL HRPWM FLTR Slave Fault Enable All Mask Definition
  */
#define LL_HRPWM_FLTR_PWMx_FLTx_EN_MSK                      ((HRPWM_SLV0_FLTR_FLT7EN_Msk | HRPWM_SLV0_FLTR_FLT6EN_Msk | \
                                                              HRPWM_SLV0_FLTR_FLT5EN_Msk | HRPWM_SLV0_FLTR_FLT4EN_Msk | \
                                                              HRPWM_SLV0_FLTR_FLT3EN_Msk | HRPWM_SLV0_FLTR_FLT2EN_Msk | \
                                                              HRPWM_SLV0_FLTR_FLT1EN_Msk | HRPWM_SLV0_FLTR_FLT0EN_Msk))

/**
  * @brief LL HRPWM CR0 PWM Update Disable All Mask Definition
  */
#define LL_HRPWM_CR0_UPD_DIS_MSK                            ((HRPWM_COM_CR0_MUDIS_Msk | HRPWM_COM_CR0_UDIS0_Msk | \
                                                              HRPWM_COM_CR0_UDIS1_Msk | HRPWM_COM_CR0_UDIS2_Msk | \
                                                              HRPWM_COM_CR0_UDIS3_Msk | HRPWM_COM_CR0_UDIS4_Msk | \
                                                              HRPWM_COM_CR0_UDIS5_Msk | HRPWM_COM_CR0_UDIS6_Msk | \
                                                              HRPWM_COM_CR0_UDIS7_Msk)) 

/**
  * @brief LL HRPWM CR1 PWM Output Swap All Mask Definition
  */
#define LL_HRPWM_CR1_SWAP_AB_MSK                            ((HRPWM_COM_CR1_SWP0_Msk | HRPWM_COM_CR1_SWP1_Msk | \
                                                              HRPWM_COM_CR1_SWP2_Msk | HRPWM_COM_CR1_SWP3_Msk | \
                                                              HRPWM_COM_CR1_SWP4_Msk | HRPWM_COM_CR1_SWP5_Msk | \
                                                              HRPWM_COM_CR1_SWP6_Msk | HRPWM_COM_CR1_SWP7_Msk)) 

/**
  * @brief LL HRPWM CR2 PWM Software Update All Mask Definition
  */
#define LL_HRPWM_CR2_SW_UPD_MSK                             ((HRPWM_COM_CR2_MSWU_Msk | HRPWM_COM_CR2_SWU0_Msk | \
                                                              HRPWM_COM_CR2_SWU1_Msk | HRPWM_COM_CR2_SWU2_Msk | \
                                                              HRPWM_COM_CR2_SWU3_Msk | HRPWM_COM_CR2_SWU4_Msk | \
                                                              HRPWM_COM_CR2_SWU5_Msk | HRPWM_COM_CR2_SWU6_Msk | \
                                                              HRPWM_COM_CR2_SWU7_Msk)) 

/**
  * @brief LL HRPWM IER Common Interrput Enable All Mask Definition
  */
#define LL_HRPWM_IER_COM_IT_EN_MSK                          ((HRPWM_COM_IER_SYSFLTIE_Msk | HRPWM_COM_IER_FLT0IE_Msk | \
                                                              HRPWM_COM_IER_FLT1IE_Msk   | HRPWM_COM_IER_FLT2IE_Msk | \
                                                              HRPWM_COM_IER_FLT3IE_Msk   | HRPWM_COM_IER_FLT4IE_Msk | \
                                                              HRPWM_COM_IER_FLT5IE_Msk   | HRPWM_COM_IER_FLT6IE_Msk | \
                                                              HRPWM_COM_IER_FLT7IE_Msk   | HRPWM_COM_IER_BMPERIE_Msk))

/**
  * @brief HRPWM Common Interrupt Enable Mask Definition
  */
#define LL_HRPWM_COM_IER_ITEnMskTypeDef                     uint32_t

#define LL_HRPWM_COM_IER_BMPERIE             (HRPWM_COM_IER_BMPERIE_Msk)          /*!< IER_BMPERIE Mask         */
#define LL_HRPWM_COM_IER_FLT7IE              (HRPWM_COM_IER_FLT7IE_Msk)           /*!< IER_FLT7IE Mask          */
#define LL_HRPWM_COM_IER_FLT6IE              (HRPWM_COM_IER_FLT6IE_Msk)           /*!< IER_FLT6IE Mask          */
#define LL_HRPWM_COM_IER_FLT5IE              (HRPWM_COM_IER_FLT5IE_Msk)           /*!< IER_FLT5IE Mask          */
#define LL_HRPWM_COM_IER_FLT4IE              (HRPWM_COM_IER_FLT4IE_Msk)           /*!< IER_FLT4IE Mask          */
#define LL_HRPWM_COM_IER_FLT3IE              (HRPWM_COM_IER_FLT3IE_Msk)           /*!< IER_FLT3IE Mask          */
#define LL_HRPWM_COM_IER_FLT2IE              (HRPWM_COM_IER_FLT2IE_Msk)           /*!< IER_FLT2IE Mask          */
#define LL_HRPWM_COM_IER_FLT1IE              (HRPWM_COM_IER_FLT1IE_Msk)           /*!< IER_FLT1IE Mask          */
#define LL_HRPWM_COM_IER_FLT0IE              (HRPWM_COM_IER_FLT0IE_Msk)           /*!< IER_FLT0IE Mask          */
#define LL_HRPWM_COM_IER_SYSFLTIE            (HRPWM_COM_IER_SYSFLTIE_Msk)         /*!< IER_SYSFLTIE Mask        */

/**
  * @brief LL HRPWM ISR Common Interrput Flag All Mask Definition
  */
#define LL_HRPWM_ISR_COM_IT_FLAG_MSK                        ((HRPWM_COM_ISR_SYSFLT_Msk | HRPWM_COM_ISR_FLT0_Msk | \
                                                              HRPWM_COM_ISR_FLT1_Msk   | HRPWM_COM_ISR_FLT2_Msk | \
                                                              HRPWM_COM_ISR_FLT3_Msk   | HRPWM_COM_ISR_FLT4_Msk | \
                                                              HRPWM_COM_ISR_FLT5_Msk   | HRPWM_COM_ISR_FLT6_Msk | \
                                                              HRPWM_COM_ISR_FLT7_Msk   | HRPWM_COM_ISR_BMPER_Msk))

/**
  * @brief HRPWM Common Interrupt Pending Mask Definition
  */
#define LL_HRPWM_COM_ISR_ITPendingMskTypeDef                uint32_t

#define LL_HRPWM_COM_ISR_BMPER               (HRPWM_COM_ISR_BMPER_Msk)            /*!< ISR_BMPER Mask           */
#define LL_HRPWM_COM_ISR_FLT7                (HRPWM_COM_ISR_FLT7_Msk)             /*!< ISR_FLT7 Mask            */
#define LL_HRPWM_COM_ISR_FLT6                (HRPWM_COM_ISR_FLT6_Msk)             /*!< ISR_FLT6 Mask            */
#define LL_HRPWM_COM_ISR_FLT5                (HRPWM_COM_ISR_FLT5_Msk)             /*!< ISR_FLT5 Mask            */
#define LL_HRPWM_COM_ISR_FLT4                (HRPWM_COM_ISR_FLT4_Msk)             /*!< ISR_FLT4 Mask            */
#define LL_HRPWM_COM_ISR_FLT3                (HRPWM_COM_ISR_FLT3_Msk)             /*!< ISR_FLT3 Mask            */
#define LL_HRPWM_COM_ISR_FLT2                (HRPWM_COM_ISR_FLT2_Msk)             /*!< ISR_FLT2 Mask            */
#define LL_HRPWM_COM_ISR_FLT1                (HRPWM_COM_ISR_FLT1_Msk)             /*!< ISR_FLT1 Mask            */
#define LL_HRPWM_COM_ISR_FLT0                (HRPWM_COM_ISR_FLT0_Msk)             /*!< ISR_FLT0 Mask            */
#define LL_HRPWM_COM_ISR_SYSFLT              (HRPWM_COM_ISR_SYSFLT_Msk)           /*!< ISR_SYSFLT Mask          */

/**
  * @brief LL HRPWM OENR PWM OutA/B Start All Mask Definition
  */
#define LL_HRPWM_OENR_OUTx_START_MSK                        ((HRPWM_COM_OENR_OEN7B_Msk | HRPWM_COM_OENR_OEN7A_Msk | \
                                                              HRPWM_COM_OENR_OEN6B_Msk | HRPWM_COM_OENR_OEN6A_Msk | \
                                                              HRPWM_COM_OENR_OEN5B_Msk | HRPWM_COM_OENR_OEN5A_Msk | \
                                                              HRPWM_COM_OENR_OEN4B_Msk | HRPWM_COM_OENR_OEN4A_Msk | \
                                                              HRPWM_COM_OENR_OEN3B_Msk | HRPWM_COM_OENR_OEN3A_Msk | \
                                                              HRPWM_COM_OENR_OEN2B_Msk | HRPWM_COM_OENR_OEN2A_Msk | \
                                                              HRPWM_COM_OENR_OEN1B_Msk | HRPWM_COM_OENR_OEN1A_Msk | \
                                                              HRPWM_COM_OENR_OEN0B_Msk | HRPWM_COM_OENR_OEN0A_Msk))

/**
  * @brief LL HRPWM ODISR PWM OutA/B Stop All Mask Definition
  */
#define LL_HRPWM_ODISR_OUTx_STOP_MSK                        ((HRPWM_COM_ODISR_ODIS7B_Msk | HRPWM_COM_ODISR_ODIS7A_Msk | \
                                                              HRPWM_COM_ODISR_ODIS6B_Msk | HRPWM_COM_ODISR_ODIS6A_Msk | \
                                                              HRPWM_COM_ODISR_ODIS5B_Msk | HRPWM_COM_ODISR_ODIS5A_Msk | \
                                                              HRPWM_COM_ODISR_ODIS4B_Msk | HRPWM_COM_ODISR_ODIS4A_Msk | \
                                                              HRPWM_COM_ODISR_ODIS3B_Msk | HRPWM_COM_ODISR_ODIS3A_Msk | \
                                                              HRPWM_COM_ODISR_ODIS2B_Msk | HRPWM_COM_ODISR_ODIS2A_Msk | \
                                                              HRPWM_COM_ODISR_ODIS1B_Msk | HRPWM_COM_ODISR_ODIS1A_Msk | \
                                                              HRPWM_COM_ODISR_ODIS0B_Msk | HRPWM_COM_ODISR_ODIS0A_Msk))


/**
  * @}
  */ /* HRPWM_LL_EC_Register */



/** @defgroup HRPWM_LL_EC_Configuration LL HRPWM Configuration
  * @brief LL HRPWM Configuration 
  * @{
  */

/**
  * @brief HRPWM PWM Index Definition
  */
#define LL_HRPWM_PWMIdxTypeDef                               LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_PWM_0                                   (0UL)                 /*!< HRPWM Slave PWM 0                                */
#define LL_HRPWM_SLV_PWM_1                                   (1UL)                 /*!< HRPWM Slave PWM 1                                */
#define LL_HRPWM_SLV_PWM_2                                   (2UL)                 /*!< HRPWM Slave PWM 2                                */
#define LL_HRPWM_SLV_PWM_3                                   (3UL)                 /*!< HRPWM Slave PWM 3                                */
#define LL_HRPWM_SLV_PWM_4                                   (4UL)                 /*!< HRPWM Slave PWM 4                                */
#define LL_HRPWM_SLV_PWM_5                                   (5UL)                 /*!< HRPWM Slave PWM 5                                */
#define LL_HRPWM_SLV_PWM_6                                   (6UL)                 /*!< HRPWM Slave PWM 6                                */
#define LL_HRPWM_SLV_PWM_7                                   (7UL)                 /*!< HRPWM Slave PWM 7                                */
#define LL_HRPWM_SLV_PWM_NUMS                                (8UL)                 /*!< HRPWM Slave PWM Numbers                          */
#define LL_HRPWM_MST_PWM                                     (9UL)                 /*!< HRPWM Master PWM                                 */

#define IS_LL_HRPWM_SLV_PWM_IDX(__VAL__)                     (((__VAL__) == LL_HRPWM_SLV_PWM_0) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_1) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_2) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_3) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_4) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_5) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_6) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_7) )

/**
  * @brief HRPWM External Event Number Definition
  */
#define LL_HRPWM_ExtEvtNumTypeDef                            LL_RSV_DATA_TYPE     

#define LL_HRPWM_EXT_EVT_NUM_0                               (0UL)                 /*!< HRPWM External Event Number 0                    */
#define LL_HRPWM_EXT_EVT_NUM_1                               (1UL)                 /*!< HRPWM External Event Number 1                    */
#define LL_HRPWM_EXT_EVT_NUM_2                               (2UL)                 /*!< HRPWM External Event Number 2                    */
#define LL_HRPWM_EXT_EVT_NUM_3                               (3UL)                 /*!< HRPWM External Event Number 3                    */
#define LL_HRPWM_EXT_EVT_NUM_4                               (4UL)                 /*!< HRPWM External Event Number 4                    */
#define LL_HRPWM_EXT_EVT_NUM_5                               (5UL)                 /*!< HRPWM External Event Number 5                    */
#define LL_HRPWM_EXT_EVT_NUM_6                               (6UL)                 /*!< HRPWM External Event Number 6                    */
#define LL_HRPWM_EXT_EVT_NUM_7                               (7UL)                 /*!< HRPWM External Event Number 7                    */
#define LL_HRPWM_EXT_EVT_NUM_8                               (8UL)                 /*!< HRPWM External Event Number 8                    */
#define LL_HRPWM_EXT_EVT_NUM_9                               (9UL)                 /*!< HRPWM External Event Number 9                    */
#define LL_HRPWM_EXT_EVT_NUMS                                (10UL)                /*!< HRPWM External Event Numbers                     */

#define IS_LL_HRPWM_EXT_EVT(__VAL__)                         (((__VAL__) == LL_HRPWM_EXT_EVT_NUM_0) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_1) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_2) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_3) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_4) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_5) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_6) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_7) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_8) || \
                                                              ((__VAL__) == LL_HRPWM_EXT_EVT_NUM_9) )

/**
  * @brief HRPWM Fault Number Definition
  */
#define LL_HRPWM_FltNumTypeDef                               LL_RSV_DATA_TYPE     

#define LL_HRPWM_FLT_NUM_0                                   (0UL)                 /*!< HRPWM Fault Number 0                             */
#define LL_HRPWM_FLT_NUM_1                                   (1UL)                 /*!< HRPWM Fault Number 1                             */
#define LL_HRPWM_FLT_NUM_2                                   (2UL)                 /*!< HRPWM Fault Number 2                             */
#define LL_HRPWM_FLT_NUM_3                                   (3UL)                 /*!< HRPWM Fault Number 3                             */
#define LL_HRPWM_FLT_NUM_4                                   (4UL)                 /*!< HRPWM Fault Number 4                             */
#define LL_HRPWM_FLT_NUM_5                                   (5UL)                 /*!< HRPWM Fault Number 5                             */
#define LL_HRPWM_FLT_NUM_6                                   (6UL)                 /*!< HRPWM Fault Number 6                             */
#define LL_HRPWM_FLT_NUM_7                                   (7UL)                 /*!< HRPWM Fault Number 7                             */
#define LL_HRPWM_FLT_NUMS                                    (8UL)                 /*!< HRPWM Fault Numbers                              */

#define IS_LL_HRPWM_FLT(__VAL__)                             (((__VAL__) == LL_HRPWM_FLT_NUM_0) || \
                                                              ((__VAL__) == LL_HRPWM_FLT_NUM_1) || \
                                                              ((__VAL__) == LL_HRPWM_FLT_NUM_2) || \
                                                              ((__VAL__) == LL_HRPWM_FLT_NUM_3) || \
                                                              ((__VAL__) == LL_HRPWM_FLT_NUM_4) || \
                                                              ((__VAL__) == LL_HRPWM_FLT_NUM_5) || \
                                                              ((__VAL__) == LL_HRPWM_FLT_NUM_6) || \
                                                              ((__VAL__) == LL_HRPWM_FLT_NUM_7) )

/**
  * @brief HRPWM ADC Trigger Number Definition
  */
#define LL_HRPWM_ADCTrigNumTypeDef                           LL_RSV_DATA_TYPE     

#define LL_HRPWM_ADC_TRIG_NUM_0                              (0UL)                 /*!< HRPWM ADC Trigger Number 0                       */
#define LL_HRPWM_ADC_TRIG_NUM_1                              (1UL)                 /*!< HRPWM ADC Trigger Number 1                       */
#define LL_HRPWM_ADC_TRIG_NUM_2                              (2UL)                 /*!< HRPWM ADC Trigger Number 2                       */
#define LL_HRPWM_ADC_TRIG_NUM_3                              (3UL)                 /*!< HRPWM ADC Trigger Number 3                       */
#define LL_HRPWM_ADC_TRIG_NUM_4                              (4UL)                 /*!< HRPWM ADC Trigger Number 4                       */
#define LL_HRPWM_ADC_TRIG_NUM_5                              (5UL)                 /*!< HRPWM ADC Trigger Number 5                       */
#define LL_HRPWM_ADC_TRIG_NUM_6                              (6UL)                 /*!< HRPWM ADC Trigger Number 6                       */
#define LL_HRPWM_ADC_TRIG_NUM_7                              (7UL)                 /*!< HRPWM ADC Trigger Number 7                       */
#define LL_HRPWM_ADC_TRIG_NUM_8                              (8UL)                 /*!< HRPWM ADC Trigger Number 8                       */
#define LL_HRPWM_ADC_TRIG_NUM_9                              (9UL)                 /*!< HRPWM ADC Trigger Number 9                       */
#define LL_HRPWM_ADC_TRIG_NUMS                               (10UL)                /*!< HRPWM ADC Trigger Numbers                        */

#define IS_LL_HRPWM_ADC_TRIG(__VAL__)                        (((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_0) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_1) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_2) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_3) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_4) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_5) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_6) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_7) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_8) || \
                                                              ((__VAL__) == LL_HRPWM_ADC_TRIG_NUM_9) )

/**
  * @brief HRPWM PWM Work Mode Definition
  */
#define LL_HRPWM_WorkModeTypeDef                             LL_RSV_DATA_TYPE     

#define LL_HRPWM_WORK_MODE_SINGLE                            (0UL)                 /*!< PWM Work Mode Single                             */
#define LL_HRPWM_WORK_MODE_CONTINUE                          (1UL)                 /*!< PWM Work Mode Continue                           */

#define IS_LL_HRPWM_WORK_MODE(__VAL__)                       (((__VAL__) == LL_HRPWM_WORK_MODE_SINGLE)   || \
                                                              ((__VAL__) == LL_HRPWM_WORK_MODE_CONTINUE) )

/**
  * @brief HRPWM DAC Sync Source Definition
  */
#define LL_HRPWM_DACSyncSrcTypeDef                           LL_RSV_DATA_TYPE     

#define LL_HRPWM_DAC_SYNC_SRC_NONE                           (0UL)                 /*!< DAC Sync Source None                             */
#define LL_HRPWM_DAC_SYNC_SRC_TRIG0                          (1UL)                 /*!< DAC Sync Source Trig0                            */
#define LL_HRPWM_DAC_SYNC_SRC_TRIG1                          (2UL)                 /*!< DAC Sync Source Trig1                            */
#define LL_HRPWM_DAC_SYNC_SRC_TRIG2                          (3UL)                 /*!< DAC Sync Source Trig2                            */

#define IS_LL_HRPWM_DAC_SYNC_SRC(__VAL__)                    (((__VAL__) == LL_HRPWM_DAC_SYNC_SRC_NONE)  || \
                                                              ((__VAL__) == LL_HRPWM_DAC_SYNC_SRC_TRIG0) || \
                                                              ((__VAL__) == LL_HRPWM_DAC_SYNC_SRC_TRIG1) || \
                                                              ((__VAL__) == LL_HRPWM_DAC_SYNC_SRC_TRIG2) )

/**
  * @brief HRPWM Clock Prescaler Definition
  */
#define LL_HRPWM_ClkPresclTypeDef                            LL_RSV_DATA_TYPE     

#define LL_HRPWM_CLK_PRESCL_MUL_32                           (0UL)                 /*!< Clock Prescaler Multi 32                         */
#define LL_HRPWM_CLK_PRESCL_MUL_16                           (1UL)                 /*!< Clock Prescaler Multi 16                         */
#define LL_HRPWM_CLK_PRESCL_MUL_8                            (2UL)                 /*!< Clock Prescaler Multi 8                          */
#define LL_HRPWM_CLK_PRESCL_MUL_4                            (3UL)                 /*!< Clock Prescaler Multi 4                          */
#define LL_HRPWM_CLK_PRESCL_MUL_2                            (4UL)                 /*!< Clock Prescaler Multi 2                          */
#define LL_HRPWM_CLK_PRESCL_DIV_1                            (5UL)                 /*!< Clock Prescaler Division 1                       */
#define LL_HRPWM_CLK_PRESCL_DIV_2                            (6UL)                 /*!< Clock Prescaler Division 2                       */
#define LL_HRPWM_CLK_PRESCL_DIV_4                            (7UL)                 /*!< Clock Prescaler Division 4                       */

#define IS_LL_HRPWM_CLK_PRESCL(__VAL__)                      (((__VAL__) == LL_HRPWM_CLK_PRESCL_MUL_32) || \
                                                              ((__VAL__) == LL_HRPWM_CLK_PRESCL_MUL_16) || \
                                                              ((__VAL__) == LL_HRPWM_CLK_PRESCL_MUL_8)  || \
                                                              ((__VAL__) == LL_HRPWM_CLK_PRESCL_MUL_4)  || \
                                                              ((__VAL__) == LL_HRPWM_CLK_PRESCL_MUL_2)  || \
                                                              ((__VAL__) == LL_HRPWM_CLK_PRESCL_DIV_1)  || \
                                                              ((__VAL__) == LL_HRPWM_CLK_PRESCL_DIV_2)  || \
                                                              ((__VAL__) == LL_HRPWM_CLK_PRESCL_DIV_4)  )

/**
  * @brief HRPWM PWM Interleaved Mode Definition
  */
#define LL_HRPWM_IntlvdModeTypeDef                           LL_RSV_DATA_TYPE     

#define LL_HRPWM_INTLVD_MODE_CLOSE                           (0UL)                 /*!< PWM Interleaved Mode Close                       */
#define LL_HRPWM_INTLVD_MODE_1_3                             (1UL)                 /*!< PWM Interleaved Mode 1/3                         */
#define LL_HRPWM_INTLVD_MODE_1_4                             (2UL)                 /*!< PWM Interleaved Mode 1/4                         */

#define IS_LL_HRPWM_INTLVD_MODE(__VAL__)                     (((__VAL__) == LL_HRPWM_INTLVD_MODE_CLOSE) || \
                                                              ((__VAL__) == LL_HRPWM_INTLVD_MODE_1_3)   || \
                                                              ((__VAL__) == LL_HRPWM_INTLVD_MODE_1_4)   )

/**
  * @brief HRPWM Master Update Gate Definition
  */
#define LL_HRPWM_Mst_UpdGateTypeDef                          LL_RSV_DATA_TYPE     

#define LL_HRPWM_MST_UPD_GATE_BST_DMA_INDEPEND               (0UL)                 /*!< Master Update Gate Burst DMA Done Independent    */
#define LL_HRPWM_MST_UPD_GATE_BST_DMA_DONE                   (2UL)                 /*!< Master Update Gate Burst DMA Done Done           */
#define LL_HRPWM_MST_UPD_GATE_BST_DMA_NEXT                   (3UL)                 /*!< Master Update Gate Burst DMA Done Next Update    \
                                                                                        Event                                            */

#define IS_LL_HRPWM_MST_UPD_GATE_BST_DMA(__VAL__)            (((__VAL__) == LL_HRPWM_MST_UPD_GATE_BST_DMA_INDEPEND) || \
                                                              ((__VAL__) == LL_HRPWM_MST_UPD_GATE_BST_DMA_DONE)     || \
                                                              ((__VAL__) == LL_HRPWM_MST_UPD_GATE_BST_DMA_NEXT)     )

/**
  * @brief HRPWM Master Sync Mode Definition
  */
#define LL_HRPWM_Mst_SyncModeTypeDef                         LL_RSV_DATA_TYPE     

#define LL_HRPWM_MST_SYNC_MODE_DIS                           (0UL)                 /*!< Master Sync Mode Disable                         */
#define LL_HRPWM_MST_SYNC_MODE_MST                           (BIT(0))              /*!< Master Sync Mode Master                          */
#define LL_HRPWM_MST_SYNC_MODE_SLV                           (BIT(1))              /*!< Master Sync Mode Slave                           */
#define LL_HRPWM_MST_SYNC_MODE_MST_SLV                       (BIT(0) | BIT(1))     /*!< Master Sync Mode Master&Slave                    */

#define IS_LL_HRPWM_MST_SYNC_MODE(__VAL__)                   (((__VAL__) == LL_HRPWM_MST_SYNC_MODE_DIS)     || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_MODE_MST)     || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_MODE_SLV)     || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_MODE_MST_SLV) )

/**
  * @brief HRPWM Master Sync Output Source Definition
  */
#define LL_HRPWM_Mst_SyncOutSrcTypeDef                       LL_RSV_DATA_TYPE     

#define LL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_START              (0UL)                 /*!< Master Sync Output Source Master PWM Start       */
#define LL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_CMPA               (1UL)                 /*!< Master Sync Output Source Master PWM Compare A   */
#define LL_HRPWM_MST_SYNC_OUT_SRC_PWM0_START_RST             (2UL)                 /*!< Master Sync Output Source PWM0 Start/Reset       */
#define LL_HRPWM_MST_SYNC_OUT_SRC_PWM0_CMPA                  (3UL)                 /*!< Master Sync Output Source PWM0 Compare A         */

#define IS_LL_HRPWM_MST_SYNC_OUT_SRC(__VAL__)                (((__VAL__) == LL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_START)  || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_OUT_SRC_MST_PWM_CMPA)   || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_OUT_SRC_PWM0_START_RST) || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_OUT_SRC_PWM0_CMPA)      )

/**
  * @brief HRPWM Master Sync Output Polarity Definition
  */
#define LL_HRPWM_Mst_SyncOutPolTypeDef                       LL_RSV_DATA_TYPE     

#define LL_HRPWM_MST_SYNC_OUT_POL_ACT_HIGH                   (0UL)                 /*!< Master Sync Output Polarity Active High          */
#define LL_HRPWM_MST_SYNC_OUT_POL_ACT_LOW                    (1UL)                 /*!< Master Sync Output Polarity Active Low           */

#define IS_LL_HRPWM_MST_SYNC_OUT_POL_ACT(__VAL__)            (((__VAL__) == LL_HRPWM_MST_SYNC_OUT_POL_ACT_HIGH) || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_OUT_POL_ACT_LOW)  )

/**
  * @brief HRPWM Master Sync Input Source Definition
  */
#define LL_HRPWM_Mst_SyncInSrcTypeDef                        LL_RSV_DATA_TYPE     

#define LL_HRPWM_MST_SYNC_IN_SRC_TMR9_TRGO                   (0UL)                 /*!< Master Sync Input Source TMR9_TRGO               */
#define LL_HRPWM_MST_SYNC_IN_SRC_HRPWM_SCIN                  (1UL)                 /*!< Master Sync Input Source HRPWM SCIN              */

#define IS_LL_HRPWM_MST_SYNC_IN_SRC(__VAL__)                 (((__VAL__) == LL_HRPWM_MST_SYNC_IN_SRC_TMR9_TRGO)  || \
                                                              ((__VAL__) == LL_HRPWM_MST_SYNC_IN_SRC_HRPWM_SCIN) )

/**
  * @brief HRPWM Slave Update Gate Definition
  */
#define LL_HRPWM_Slv_UpdGateTypeDef                          LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND               (0UL)                 /*!< Slave Update Gate Burst DMA Done Independent     */
#define LL_HRPWM_SLV_UPD_GATE_IN0_RISING                     (2UL)                 /*!< Slave Update Gate hrpwm_upd_in[0] Rising Egde    */
#define LL_HRPWM_SLV_UPD_GATE_IN1_RISING                     (3UL)                 /*!< Slave Update Gate hrpwm_upd_in[1] Rising Egde    */
#define LL_HRPWM_SLV_UPD_GATE_IN2_RISING                     (4UL)                 /*!< Slave Update Gate hrpwm_upd_in[2] Rising Egde    */
#define LL_HRPWM_SLV_UPD_GATE_IN0_RISING_NEXT                (5UL)                 /*!< Slave Update Gate Next Update Event after        \
                                                                                        hrpwm_upd_in[0] Rising Egde                      */
#define LL_HRPWM_SLV_UPD_GATE_IN1_RISING_NEXT                (6UL)                 /*!< Slave Update Gate Next Update Event after        \
                                                                                        hrpwm_upd_in[1] Rising Egde                      */
#define LL_HRPWM_SLV_UPD_GATE_IN2_RISING_NEXT                (7UL)                 /*!< Slave Update Gate Next Update Event after        \
                                                                                        hrpwm_upd_in[2] Rising Egde                      */
#define LL_HRPWM_SLV_UPD_GATE_BST_DMA_DONE                   (8UL)                 /*!< Slave Update Gate Burst DMA Done Done            */
#define LL_HRPWM_SLV_UPD_GATE_BST_DMA_NEXT                   (12UL)                /*!< Slave Update Gate Burst DMA Done Next Update     \
                                                                                        Event                                            */

#define IS_LL_HRPWM_SLV_UPD_GATE(__VAL__)                    (((__VAL__) == LL_HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_IN0_RISING)       || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_IN1_RISING)       || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_IN2_RISING)       || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_IN0_RISING_NEXT)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_IN1_RISING_NEXT)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_IN2_RISING_NEXT)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_BST_DMA_DONE)     || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_GATE_BST_DMA_NEXT)     )

/**
  * @brief HRPWM Slave CMPB/CMPD Auto Delayed Mode Definition
  */
#define LL_HRPWM_Slv_CmpBDAutoDlyTypeDef                    LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_CMP_BD_AUTO_DLY_ALWAYS                 (0UL)                 /*!< Slave CMPB/CMPD Auto Delayd Mode Always           */
#define LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx             (1UL)                 /*!< Slave CMPB/CMPD Auto Delayd Mode After CAPx       */
#define LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx_CMPA        (2UL)                 /*!< Slave CMPB/CMPD Auto Delayd Mode After CAPx/CMPA  */
#define LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx_CMPC        (3UL)                 /*!< Slave CMPB/CMPD Auto Delayd Mode After CAPx/CMPC  */

#define IS_LL_HRPWM_SLV_CMP_BD_AUTO_DLY(__VAL__)            (((__VAL__) == LL_HRPWM_SLV_CMP_BD_AUTO_DLY_ALWAYS)           || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx_CMPA) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMP_BD_AUTO_DLY_AFTER_CAPx_CMPC) )

/**
  * @brief HRPWM Slave CMPD Auto Delayed Mode Definition
  */
#define LL_HRPWM_Slv_CmpDAutoDlyTypeDef                      LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_CMPD_AUTO_DLY_ALWAYS                    (0UL)                 /*!< Slave CMPD Auto Delayd Mode Always               */
#define LL_HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB                (1UL)                 /*!< Slave CMPD Auto Delayd Mode After CAPB           */
#define LL_HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB_CMPA           (2UL)                 /*!< Slave CMPD Auto Delayd Mode After CAPB/CMPA      */
#define LL_HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB_CMPC           (3UL)                 /*!< Slave CMPD Auto Delayd Mode After CAPB/CMPC      */

#define IS_LL_HRPWM_SLV_CMPD_AUTO_DLY(__VAL__)               (((__VAL__) == LL_HRPWM_SLV_CMPD_AUTO_DLY_ALWAYS)          || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB_CMPA) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB_CMPC) )

/**
  * @brief HRPWM Slave CMPB Auto Delayed Mode Definition
  */
#define LL_HRPWM_Slv_CmpBAutoDlyTypeDef                      LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_CMPB_AUTO_DLY_ALWAYS                    (0UL)                 /*!< Slave CMPB Auto Delayd Mode Always               */
#define LL_HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA                (1UL)                 /*!< Slave CMPB Auto Delayd Mode After CAPA           */
#define LL_HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA_CMPA           (2UL)                 /*!< Slave CMPB Auto Delayd Mode After CAPA/CMPA      */
#define LL_HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA_CMPC           (3UL)                 /*!< Slave CMPB Auto Delayd Mode After CAPA/CMPC      */

#define IS_LL_HRPWM_SLV_CMPB_AUTO_DLY(__VAL__)               (((__VAL__) == LL_HRPWM_SLV_CMPB_AUTO_DLY_ALWAYS)          || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA_CMPA) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA_CMPC) )

/**
  * @brief HRPWM Slave ReSync Mode Definition
  * @note  The functions are subject to the meanings expressed in the annotations
  */
#define LL_HRPWM_Slv_ReSyncModeTypeDef                       LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_RESYNC_IMMEDIATELY                      (0UL)                 /*!< Slave ReSync Mode Immediately                    */
#define LL_HRPWM_SLV_RESYNC_NEXT_RST_OR_ROLLOVER             (1UL)                 /*!< Slave ReSync Mode Wait for Next Reset/Roll-Over  \
                                                                                        Event                                            */

#define IS_LL_HRPWM_SLV_RESYNC(__VAL__)                      (((__VAL__) == LL_HRPWM_SLV_RESYNC_IMMEDIATELY)          || \
                                                              ((__VAL__) == LL_HRPWM_SLV_RESYNC_NEXT_RST_OR_ROLLOVER) )

/**
  * @brief HRPWM Slave Roll-Over Mode Definition
  */
#define LL_HRPWM_Slv_RollOverModeTypeDef                     LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_ROLL_OVER_0_PERIOD                      (0UL)                 /*!< Slave Roll-Over Mode Generate at 0/Period        */
#define LL_HRPWM_SLV_ROLL_OVER_0                             (1UL)                 /*!< Slave Roll-Over Mode Generate at 0               */
#define LL_HRPWM_SLV_ROLL_OVER_PERIOD                        (2UL)                 /*!< Slave Roll-Over Mode Generate at Period          */

#define IS_LL_HRPWM_SLV_ROLL_OVER(__VAL__)                   (((__VAL__) == LL_HRPWM_SLV_ROLL_OVER_0_PERIOD) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_ROLL_OVER_0)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_ROLL_OVER_PERIOD)   )

/**
  * @brief HRPWM Slave Capture Mode Definition
  */
#define LL_HRPWM_Slv_CapModeTypeDef                          LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_CAP_MODE_NORMAL                         (0UL)                 /*!< Slave Capture Mode Normal                        */
#define LL_HRPWM_SLV_CAP_MODE_TIMEOUT                        (1UL)                 /*!< Slave Capture Mode Timeout                       */

#define IS_LL_HRPWM_SLV_CAP_MODE(__VAL__)                    (((__VAL__) == LL_HRPWM_SLV_CAP_MODE_NORMAL)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CAP_MODE_TIMEOUT) )

/**
  * @brief HRPWM Slave Capture Direction Definition
  */
#define LL_HRPWM_Slv_CapDirTypeDef                           LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_CAP_DIR_UP                              (0UL)                 /*!< Slave Capture Direction Up                       */
#define LL_HRPWM_SLV_CAP_DIR_DOWN                            (1UL)                 /*!< Slave Capture Direction Down                     */

#define IS_LL_HRPWM_CAP_DIR(__VAL__)                         (((__VAL__) == LL_HRPWM_SLV_CAP_DIR_UP)   || \
                                                              ((__VAL__) == LL_HRPWM_SLV_CAP_DIR_DOWN) )

/**
  * @brief HRPWM Slave Direction Mode Definition
  */
#define LL_HRPWM_Slv_DirModeTypeDef                          LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_DIR_UP                                  (0UL)                 /*!< Slave Direction Mode Up                          */
#define LL_HRPWM_SLV_DIR_UP_DOWN                             (1UL)                 /*!< Slave Direction Mode Up-Down                     */

#define IS_LL_HRPWM_SLV_DIR(__VAL__)                         (((__VAL__) == LL_HRPWM_SLV_DIR_UP)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DIR_UP_DOWN) )

/**
  * @brief HRPWM Slave DAC Reset Trigger Source Definition
  */
#define LL_HRPWM_Slv_DACRstTrigSrcTypeDef                    LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_DAC_RST_TRIG_SRC_RST                    (0UL)                 /*!< Slave DAC Reset Trigger Source RST Event         */
#define LL_HRPWM_SLV_DAC_RST_TRIG_SRC_SETA                   (1UL)                 /*!< Slave DAC Reset Trigger Source SETA Event        */

#define IS_LL_HRPWM_SLV_DAC_RST_TRIG_SRC(__VAL__)            (((__VAL__) == LL_HRPWM_SLV_DAC_RST_TRIG_SRC_RST)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DAC_RST_TRIG_SRC_SETA) )

/**
  * @brief HRPWM Slave DAC Step Trigger Source Definition
  */
#define LL_HRPWM_Slv_DACStepTrigSrcTypeDef                   LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CMPD                  (0UL)                 /*!< Slave DAC Step Trigger Source CMPD Event         */
#define LL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CLRA                  (1UL)                 /*!< Slave DAC Step Trigger Source CLRA Event         */

#define IS_LL_HRPWM_SLV_DAC_STEP_TRIG_SRC(__VAL__)           (((__VAL__) == LL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CMPD) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DAC_STEP_TRIG_SRC_CLRA) )

/**
  * @brief HRPWM Slave DeadTime Direction Definition
  */
#define LL_HRPWM_Slv_DtDirTypeDef                            LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_DT_DIR_POSITIVE                         (0UL)                 /*!< Slave DeadTime Direction Positive                */
#define LL_HRPWM_SLV_DT_DIR_NEGATIVE                         (1UL)                 /*!< Slave DeadTime Direction Negative                */

#define IS_LL_HRPWM_SLV_DT_DIR(__VAL__)                      (((__VAL__) == LL_HRPWM_SLV_DT_DIR_POSITIVE) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DT_DIR_NEGATIVE) )

/**
  * @brief HRPWM Slave External Event Filter Definition
  */
#define LL_HRPWM_Slv_ExtEvtFilTypeDef                        LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_EXT_EVT_FIL_DIS                         (0UL)                 /*!< Slave External Event Filter Disable              */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPA              (1UL)                 /*!< Slave External Event Filter Blank from           \
                                                                                        Reset/Roll-Over to Compare A                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPB              (2UL)                 /*!< Slave External Event Filter Blank from           \
                                                                                        Reset/Roll-Over to Compare B                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPC              (3UL)                 /*!< Slave External Event Filter Blank from           \
                                                                                        Reset/Roll-Over to Compare C                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPD              (4UL)                 /*!< Slave External Event Filter Blank from           \
                                                                                        Reset/Roll-Over to Compare D                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPA_CMPB            (5UL)                 /*!< Slave External Event Filter Blank from Up        \
                                                                                        Compare A to Up Compare B                        */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPC_CMPD            (6UL)                 /*!< Slave External Event Filter Blank from Up        \
                                                                                        Compare C to Up Compare D                        */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPA_CMPB          (7UL)                 /*!< Slave External Event Filter Blank from Down      \
                                                                                        Compare A to Down Compare B                      */
#define LL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPC_CMPD          (8UL)                 /*!< Slave External Event Filter Blank from Down      \
                                                                                        Compare C to Down Compare D                      */
#define LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPA              (9UL)                 /*!< Slave External Event Filter Window from          \
                                                                                        Reset/Roll-Over to Compare A                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPB              (10UL)                /*!< Slave External Event Filter Window from          \
                                                                                        Reset/Roll-Over to Compare B                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPC              (11UL)                /*!< Slave External Event Filter Window from          \
                                                                                        Reset/Roll-Over to Compare C                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPD              (12UL)                /*!< Slave External Event Filter Window from          \
                                                                                        Reset/Roll-Over to Compare D                     */
#define LL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_CMPC            (13UL)                /*!< Slave External Event Filter Window from Up       \
                                                                                        Compare B to Up Compare C                        */
#define LL_HRPWM_SLV_EXT_EVT_FIL_WIN_DOWN_CMPB_CMPC          (14UL)                /*!< Slave External Event Filter Window from Dowm     \
                                                                                        Compare B to Dowm Compare C                      */
#define LL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_DOWN_CMPC       (15UL)                /*!< Slave External Event Filter Window from Up       \
                                                                                        Compare B to Down Compare C                      */

#define IS_LL_HRPWM_SLV_EXT_EVT_FIL(__VAL__)                 (((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_DIS)                   || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPA)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPB)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPC)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPD)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPA_CMPB)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPC_CMPD)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPA_CMPB)    || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPC_CMPD)    || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPA)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPB)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPC)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPD)        || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_CMPC)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_WIN_DOWN_CMPB_CMPC)    || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_DOWN_CMPC) )

/**
  * @brief HRPWM Slave External Event A Counter Reset Mode Definition
  */
#define LL_HRPWM_Slv_EvtACntrRstModeTypeDef                  LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_EVTA_CNTR_RST_RSTRO_ALWAYS              (0UL)                 /*!< Slave Event A Counter Reset at Reset/Roll-Over   \
                                                                                        Event Always                                     */
#define LL_HRPWM_SLV_EVTA_CNTR_RST_RSTRO_LAST_NO_EVT         (1UL)                 /*!< Slave Event A Counter Reset at Reset/Roll-Over   \
                                                                                        Event Only Last No Event                         */

#define IS_LL_HRPWM_SLV_EVTA_CNTR_RST_RSTRO(__VAL__)         (((__VAL__) == LL_HRPWM_SLV_EVTA_CNTR_RST_RSTRO_ALWAYS)      || \
                                                              ((__VAL__) == LL_HRPWM_SLV_EVTA_CNTR_RST_RSTRO_LAST_NO_EVT) )

/**
  * @brief HRPWM Slave Chopper Start Pulse Width Definition
  */
#define LL_HRWPM_Slv_PC_PulseWidthTypeDef                    LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_PC_PULSE_WIDH_16                        (0UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 16         */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_32                        (1UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 32         */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_48                        (2UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 48         */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_64                        (3UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 64         */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_80                        (4UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 80         */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_96                        (5UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 96         */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_112                       (6UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 112        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_128                       (7UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 128        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_144                       (8UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 144        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_160                       (9UL)                 /*!< HRPWM Slave Chopper Start Pulse Width 160        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_176                       (10UL)                /*!< HRPWM Slave Chopper Start Pulse Width 176        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_192                       (11UL)                /*!< HRPWM Slave Chopper Start Pulse Width 192        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_208                       (12UL)                /*!< HRPWM Slave Chopper Start Pulse Width 208        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_224                       (13UL)                /*!< HRPWM Slave Chopper Start Pulse Width 224        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_240                       (14UL)                /*!< HRPWM Slave Chopper Start Pulse Width 240        */
#define LL_HRPWM_SLV_PC_PULSE_WIDH_256                       (15UL)                /*!< HRPWM Slave Chopper Start Pulse Width 256        */

#define IS_LL_HRPWM_SLV_PC_PULSE_WIDH(__VAL__)               (((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_16)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_32)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_48)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_64)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_80)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_96)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_112) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_128) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_144) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_160) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_176) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_192) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_208) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_224) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_240) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_PULSE_WIDH_256) )

/**
  * @brief HRPWM Slave Chopper Duty Definition
  */
#define LL_HRPWM_Slv_PC_DutyTypeDef                          LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_PC_DUTY_8_0                             (0UL)                 /*!< HRPWM Slave Chopper Duty 0/8                     */
#define LL_HRPWM_SLV_PC_DUTY_8_1                             (1UL)                 /*!< HRPWM Slave Chopper Duty 1/8                     */
#define LL_HRPWM_SLV_PC_DUTY_8_2                             (2UL)                 /*!< HRPWM Slave Chopper Duty 2/8                     */
#define LL_HRPWM_SLV_PC_DUTY_8_3                             (3UL)                 /*!< HRPWM Slave Chopper Duty 3/8                     */
#define LL_HRPWM_SLV_PC_DUTY_8_4                             (4UL)                 /*!< HRPWM Slave Chopper Duty 4/8                     */
#define LL_HRPWM_SLV_PC_DUTY_8_5                             (5UL)                 /*!< HRPWM Slave Chopper Duty 5/8                     */
#define LL_HRPWM_SLV_PC_DUTY_8_6                             (6UL)                 /*!< HRPWM Slave Chopper Duty 6/8                     */
#define LL_HRPWM_SLV_PC_DUTY_8_7                             (7UL)                 /*!< HRPWM Slave Chopper Duty 7/8                     */

#define IS_LL_HRPWM_SLV_PC_DUTY_8(__VAL__)                   (((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_0) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_1) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_2) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_3) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_4) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_5) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_6) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_DUTY_8_7) )

/**
  * @brief HRPWM Slave Chopper Frequency Division Definition
  */
#define LL_HRPWM_Slv_PC_FreqDivTypeDef                       LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_PC_FREQ_DIV_16                          (0UL)                 /*!< HRPWM Slave Chopper Frequency Division 16        */
#define LL_HRPWM_SLV_PC_FREQ_DIV_32                          (1UL)                 /*!< HRPWM Slave Chopper Frequency Division 32        */
#define LL_HRPWM_SLV_PC_FREQ_DIV_48                          (2UL)                 /*!< HRPWM Slave Chopper Frequency Division 48        */
#define LL_HRPWM_SLV_PC_FREQ_DIV_64                          (3UL)                 /*!< HRPWM Slave Chopper Frequency Division 64        */
#define LL_HRPWM_SLV_PC_FREQ_DIV_80                          (4UL)                 /*!< HRPWM Slave Chopper Frequency Division 80        */
#define LL_HRPWM_SLV_PC_FREQ_DIV_96                          (5UL)                 /*!< HRPWM Slave Chopper Frequency Division 96        */
#define LL_HRPWM_SLV_PC_FREQ_DIV_112                         (6UL)                 /*!< HRPWM Slave Chopper Frequency Division 112       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_128                         (7UL)                 /*!< HRPWM Slave Chopper Frequency Division 128       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_144                         (8UL)                 /*!< HRPWM Slave Chopper Frequency Division 144       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_160                         (9UL)                 /*!< HRPWM Slave Chopper Frequency Division 160       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_176                         (10UL)                /*!< HRPWM Slave Chopper Frequency Division 176       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_192                         (11UL)                /*!< HRPWM Slave Chopper Frequency Division 192       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_208                         (12UL)                /*!< HRPWM Slave Chopper Frequency Division 208       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_224                         (13UL)                /*!< HRPWM Slave Chopper Frequency Division 224       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_240                         (14UL)                /*!< HRPWM Slave Chopper Frequency Division 240       */
#define LL_HRPWM_SLV_PC_FREQ_DIV_256                         (15UL)                /*!< HRPWM Slave Chopper Frequency Division 256       */

#define IS_LL_HRPWM_SLV_PC_FREQ_DIV(__VAL__)                 (((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_16)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_32)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_48)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_64)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_80)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_96)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_112) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_128) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_144) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_160) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_176) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_192) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_208) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_224) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_240) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PC_FREQ_DIV_256) )

/**
  * @brief HRPWM Slave Delay Protection Mechanism Definition
  * @note  x = 6, y = 5 for PWM0~3; x = 8, y = 7 for PWM4~7
  */
#define LL_HRPWM_Slv_DlyProtMechTypeDef                      LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTy_IDLE            (0UL)                 /*!< Slave Delay Protection Mechanism OutA Delay Idle \
                                                                                        on Ext Event y                                   */
#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTy_IDLE            (1UL)                 /*!< Slave Delay Protection Mechanism OutB Delay Idle \
                                                                                        on Ext Event y                                   */
#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_IDLE           (2UL)                 /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                        Idle on Ext Event y                              */
#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_BAL            (3UL)                 /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                        Balance on Ext Event y                           */
#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTx_IDLE            (4UL)                 /*!< Slave Delay Protection Mechanism OutA Delay Idle \
                                                                                        on Ext Event x                                   */
#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTx_IDLE            (5UL)                 /*!< Slave Delay Protection Mechanism OutB Delay Idle \
                                                                                        on Ext Event x                                   */
#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_IDLE           (6UL)                 /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                        Idle on Ext Event x                              */
#define LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_BAL            (7UL)                 /*!< Slave Delay Protection Mechanism OutAB Delay     \
                                                                                        Balance on Ext Event x                           */
#define LL_HRPWM_SLV_DLY_PROT_MECH_DISABLE                   (0x7FFFFFFFUL & ~HRPWM_SLV0_OUTR_DLYPRT_Val)  /*!< Slave Delay Protection Disable */
                                                                                        

#define IS_LL_HRPWM_SLV_DLY_PROT_MECH(__VAL__)               (((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTy_IDLE)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTy_IDLE)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_IDLE) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_BAL)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTx_IDLE)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTx_IDLE)  || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_IDLE) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_BAL)  )

/**
  * @brief HRPWM Slave Out Idle Status Level Definition
  */
#define LL_HRPWM_Slv_OutIdleLvlTypeDef                       LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_OUT_IDLE_LVL_INVLD                      (0UL)                 /*!< Slave Out Idle Status Level Invalid              */
#define LL_HRPWM_SLV_OUT_IDLE_LVL_VLD                        (1UL)                 /*!< Slave Out Idle Status Level Valid                */

#define IS_LL_HRPWM_SLV_OUT_IDLE_LVL(__VAL__)                (((__VAL__) == LL_HRPWM_SLV_OUT_IDLE_LVL_INVLD) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_OUT_IDLE_LVL_VLD)   )

/**
  * @brief HRPWM Slave Out Fault Status Level Definition
  */
#define LL_HRPWM_Slv_OutFaultLvlTypeDef                      LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_OUT_FAULT_LVL_NO_ACTION                 (0UL)                 /*!< Slave Out Fault Status Level No Action           */
#define LL_HRPWM_SLV_OUT_FAULT_LVL_VLD                       (1UL)                 /*!< Slave Out Fault Status Level Valid               */
#define LL_HRPWM_SLV_OUT_FAULT_LVL_INVLD                     (2UL)                 /*!< Slave Out Fault Status Level Invalid             */
#define LL_HRPWM_SLV_OUT_FAULT_LVL_HZ                        (3UL)                 /*!< Slave Out Fault Status Level High-Z              */

#define IS_LL_HRPWM_SLV_OUT_FAULT_LVL(__VAL__)               (((__VAL__) == LL_HRPWM_SLV_OUT_FAULT_LVL_NO_ACTION) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_OUT_FAULT_LVL_VLD)       || \
                                                              ((__VAL__) == LL_HRPWM_SLV_OUT_FAULT_LVL_INVLD)     || \
                                                              ((__VAL__) == LL_HRPWM_SLV_OUT_FAULT_LVL_HZ)        )

/**
  * @brief HRPWM Slave Out Polarity Definition
  */
#define LL_HRPWM_Slv_OutPolTypeDef                           LL_RSV_DATA_TYPE     

#define LL_HRPWM_SLV_OUT_POL_ACT_HIGH                        (0UL)                 /*!< Slave Out Polarity Active High                   */
#define LL_HRPWM_SLV_OUT_POL_ACT_LOW                         (1UL)                 /*!< Slave Out Polarity Active Low                    */

#define IS_LL_HRPWM_SLV_OUT_POL_ACT(__VAL__)                 (((__VAL__) == LL_HRPWM_SLV_OUT_POL_ACT_HIGH) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_OUT_POL_ACT_LOW)  )

/**
  * @brief HRPWM Common ADC Trigger x Update Source Definition
  */
#define LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef                   LL_RSV_DATA_TYPE

#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_MST_PWM               (0UL)                 /*!< Common ADC Trigger x Update Source Master PWM    */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM0                  (1UL)                 /*!< Common ADC Trigger x Update Source PWM0          */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM1                  (2UL)                 /*!< Common ADC Trigger x Update Source PWM1          */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM2                  (3UL)                 /*!< Common ADC Trigger x Update Source PWM2          */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM3                  (4UL)                 /*!< Common ADC Trigger x Update Source PWM3          */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM4                  (5UL)                 /*!< Common ADC Trigger x Update Source PWM4          */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM5                  (6UL)                 /*!< Common ADC Trigger x Update Source PWM5          */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM6                  (7UL)                 /*!< Common ADC Trigger x Update Source PWM6          */
#define LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM7                  (8UL)                 /*!< Common ADC Trigger x Update Source PWM7          */

#define IS_LL_HRPWM_COMM_ADC_TRIG_UPD_SRC(__VAL__)           (((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_MST_PWM) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM0)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM1)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM2)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM3)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM4)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM5)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM6)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM7)    )

/**
  * @brief HRPWM Common ADC Trigger x Event Length Definition
  */
#define LL_HRPWM_Comm_ADCTrigEvtLenTypeDef                   LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_16CLK                 (0UL)                 /*!< Common ADC Trigger x Event Length 16 hrpwm_clk   */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_15CLK                 (1UL)                 /*!< Common ADC Trigger x Event Length 15 hrpwm_clk   */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_14CLK                 (2UL)                 /*!< Common ADC Trigger x Event Length 14 hrpwm_clk   */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_13CLK                 (3UL)                 /*!< Common ADC Trigger x Event Length 13 hrpwm_clk   */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_12CLK                 (4UL)                 /*!< Common ADC Trigger x Event Length 12 hrpwm_clk   */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_11CLK                 (5UL)                 /*!< Common ADC Trigger x Event Length 11 hrpwm_clk   */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_10CLK                 (6UL)                 /*!< Common ADC Trigger x Event Length 10 hrpwm_clk   */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_9CLK                  (7UL)                 /*!< Common ADC Trigger x Event Length 9 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_8CLK                  (8UL)                 /*!< Common ADC Trigger x Event Length 8 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_7CLK                  (9UL)                 /*!< Common ADC Trigger x Event Length 7 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_6CLK                  (10UL)                /*!< Common ADC Trigger x Event Length 6 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_5CLK                  (11UL)                /*!< Common ADC Trigger x Event Length 5 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_4CLK                  (12UL)                /*!< Common ADC Trigger x Event Length 4 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_3CLK                  (13UL)                /*!< Common ADC Trigger x Event Length 3 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_2CLK                  (14UL)                /*!< Common ADC Trigger x Event Length 2 hrpwm_clk    */
#define LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_1CLK                  (15UL)                /*!< Common ADC Trigger x Event Length 1 hrpwm_clk    */

#define IS_LL_HRPWM_COMM_ADC_TRIG_EVT_LEN(__VAL__)           (((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_16CLK) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_15CLK) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_14CLK) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_13CLK) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_12CLK) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_11CLK) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_10CLK) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_9CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_8CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_7CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_6CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_5CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_4CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_3CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_2CLK)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC_TRIG_EVT_LEN_1CLK)  )

/**
  * @brief HRPWM Common External Event Input Active Edge Definition
  */
#define LL_HRPWM_Comm_ExtEvtInputEdgeTypeDef                 LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_LVL             (0UL)                 /*!< Common External Event Input Edge Active Level    */
#define LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_RISING          (1UL)                 /*!< Common External Event Input Edge Active Rising   */
#define LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_FALLING         (2UL)                 /*!< Common External Event Input Edge Active Falling  */
#define LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_BOTH            (3UL)                 /*!< Common External Event Input Edge Active          \
                                                                                        Rising/Falling                                   */

#define IS_LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT(__VAL__)     (((__VAL__) == LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_LVL)     || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_RISING)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_FALLING) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_BOTH)    )

/**
  * @brief HRPWM Common External Event Input Polarity Definition
  */
#define LL_HRPWM_Comm_ExtEvtInputPolTypeDef                  LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_HIGH             (0UL)                 /*!< Common External Event Input Polarity Active High */
#define LL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_LOW              (1UL)                 /*!< Common External Event Input Polarity Active Low  */

#define IS_LL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT(__VAL__)      (((__VAL__) == LL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_HIGH) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_LOW)  )

/**
  * @brief HRPWM Common External Event X Input Source Definition
  */
#define LL_HRPWM_Comm_ExtEvtXInputSrcTypeDef                 LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_HRPWM_EVT0          (0UL)                 /*!< Common External Event0 Input Source HRPWM_EVT0   */
#define LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_CMP1_OUT            (1UL)                 /*!< Common External Event0 Input Source CMP1_OUT     */
#define LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_TMR9_TRGO           (2UL)                 /*!< Common External Event0 Input Source TMR9_TRGO    */
#define LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_ADC0_AWD0           (3UL)                 /*!< Common External Event0 Input Source ADC0_AWD0    */
#define LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_HRPWM_EVT1          (0UL)                 /*!< Common External Event1 Input Source HRPWM_EVT1   */
#define LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_CMP3_OUT            (1UL)                 /*!< Common External Event1 Input Source CMP3_OUT     */
#define LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_TMR3_TRGO           (2UL)                 /*!< Common External Event1 Input Source TMR3_TRGO    */
#define LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_ADC0_AWD1           (3UL)                 /*!< Common External Event1 Input Source ADC0_AWD1    */
#define LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_HRPWM_EVT2          (0UL)                 /*!< Common External Event2 Input Source HRPWM_EVT2   */
#define LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP5_OUT            (1UL)                 /*!< Common External Event2 Input Source CMP5_OUT     */
#define LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_TMR4_TRGO           (2UL)                 /*!< Common External Event2 Input Source TMR4_TRGO    */
#define LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP7_OUT            (3UL)                 /*!< Common External Event2 Input Source CMP7_OUT     */
#define LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_HRPWM_EVT3          (0UL)                 /*!< Common External Event3 Input Source HRPWM_EVT3   */
#define LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP0_OUT            (1UL)                 /*!< Common External Event3 Input Source CMP0_OUT     */
#define LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP4_OUT            (2UL)                 /*!< Common External Event3 Input Source CMP4_OUT     */
#define LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_ADC1_AWD0           (3UL)                 /*!< Common External Event3 Input Source ADC1_AWD0    */
#define LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_HRPWM_EVT4          (0UL)                 /*!< Common External Event4 Input Source HRPWM_EVT4   */
#define LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP2_OUT            (1UL)                 /*!< Common External Event4 Input Source CMP2_OUT     */
#define LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP6_OUT            (2UL)                 /*!< Common External Event4 Input Source CMP6_OUT     */
#define LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_ADC1_AWD1           (3UL)                 /*!< Common External Event4 Input Source ADC1_AWD1    */
#define LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_HRPWM_EVT5          (0UL)                 /*!< Common External Event5 Input Source HRPWM_EVT5   */
#define LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP1_OUT            (1UL)                 /*!< Common External Event5 Input Source CMP1_OUT     */
#define LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP0_OUT            (2UL)                 /*!< Common External Event5 Input Source CMP0_OUT     */
#define LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP8_OUT            (3UL)                 /*!< Common External Event5 Input Source CMP8_OUT     */
#define LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_HRPWM_EVT6          (0UL)                 /*!< Common External Event6 Input Source HRPWM_EVT6   */
#define LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_CMP3_OUT            (1UL)                 /*!< Common External Event6 Input Source CMP3_OUT     */
#define LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_TMR8_TRGO           (2UL)                 /*!< Common External Event6 Input Source TMR8_TRGO    */
#define LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_ADC2_AWD0           (3UL)                 /*!< Common External Event6 Input Source ADC2_AWD0    */
#define LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_HRPWM_EVT7          (0UL)                 /*!< Common External Event7 Input Source HRPWM_EVT7   */
#define LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP5_OUT            (1UL)                 /*!< Common External Event7 Input Source CMP5_OUT     */
#define LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP2_OUT            (2UL)                 /*!< Common External Event7 Input Source CMP2_OUT     */
#define LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_ADC3_AWD0           (3UL)                 /*!< Common External Event7 Input Source ADC3_AWD0    */
#define LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_HRPWM_EVT8          (0UL)                 /*!< Common External Event8 Input Source HRPWM_EVT8   */
#define LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP4_OUT            (1UL)                 /*!< Common External Event8 Input Source CMP4_OUT     */
#define LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_TMR0_TRGO           (2UL)                 /*!< Common External Event8 Input Source TMR0_TRGO    */
#define LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP3_OUT            (3UL)                 /*!< Common External Event8 Input Source CMP3_OUT     */
#define LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_HRPWM_EVT9          (0UL)                 /*!< Common External Event9 Input Source HRPWM_EVT9   */
#define LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_CMP6_OUT            (1UL)                 /*!< Common External Event9 Input Source CMP6_OUT     */
#define LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_TMR7_TRGO           (2UL)                 /*!< Common External Event9 Input Source TMR7_TRGO    */
#define LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_PDM0_CMPH           (3UL)                 /*!< Common External Event9 Input Source PDM0_CMPH    */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT0          (4UL)                 /*!< External Event X Input Source HRPWM_EVT0         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT1          (5UL)                 /*!< External Event X Input Source HRPWM_EVT1         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT2          (6UL)                 /*!< External Event X Input Source HRPWM_EVT2         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT3          (7UL)                 /*!< External Event X Input Source HRPWM_EVT3         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT4          (8UL)                 /*!< External Event X Input Source HRPWM_EVT4         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT5          (9UL)                 /*!< External Event X Input Source HRPWM_EVT5         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT6          (10UL)                /*!< External Event X Input Source HRPWM_EVT6         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT7          (11UL)                /*!< External Event X Input Source HRPWM_EVT7         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT8          (12UL)                /*!< External Event X Input Source HRPWM_EVT8         */
#define LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT9          (13UL)                /*!< External Event X Input Source HRPWM_EVT9         */

#define IS_LL_HRPWM_COMM_EXT(__VAL__)                        (((__VAL__) == LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_HRPWM_EVT0) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_CMP1_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_TMR9_TRGO)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT0_INPUT_SRC_ADC0_AWD0)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_HRPWM_EVT1) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_CMP3_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_TMR3_TRGO)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT1_INPUT_SRC_ADC0_AWD1)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_HRPWM_EVT2) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP5_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_TMR4_TRGO)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP7_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_HRPWM_EVT3) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP0_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP4_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT3_INPUT_SRC_ADC1_AWD0)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_HRPWM_EVT4) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP2_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP6_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT4_INPUT_SRC_ADC1_AWD1)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_HRPWM_EVT5) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP1_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP0_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP8_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_HRPWM_EVT6) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_CMP3_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_TMR8_TRGO)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT6_INPUT_SRC_ADC2_AWD0)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_HRPWM_EVT7) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP5_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP2_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT7_INPUT_SRC_ADC3_AWD0)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_HRPWM_EVT8) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP4_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_TMR0_TRGO)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP3_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_HRPWM_EVT9) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_CMP6_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_TMR7_TRGO)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT9_INPUT_SRC_PDM0_CMPH)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT0) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT1) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT2) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT3) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT4) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT5) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT6) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT7) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT8) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT9) )

/**
  * @brief HRPWM Common External Event Sample Clock Division Definition
  */
#define LL_HRPWM_Comm_ExtEvtSampClkDivTypeDef                LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_1                 (0UL)                 /*!< Common External Event Sample Clock Division 1    */
#define LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_2                 (1UL)                 /*!< Common External Event Sample Clock Division 2    */
#define LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_4                 (2UL)                 /*!< Common External Event Sample Clock Division 4    */
#define LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_8                 (3UL)                 /*!< Common External Event Sample Clock Division 8    */

#define IS_LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV(__VAL__)       (((__VAL__) == LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_1) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_2) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_4) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_8) )

/**
  * @brief HRPWM Common ADC4/6/8 Trigger Event Source Definition
  */
#define LL_HRPWM_Comm_ADC468TrigEvtSrcTypeDef                LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPA           (0UL)                 /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                        A                                                */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPB           (1UL)                 /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                        B                                                */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPC           (2UL)                 /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                        C                                                */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPD           (3UL)                 /*!< ADC4/6/8 Trigger Event Source Master PWM Compare \
                                                                                        D                                                */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_PRD            (4UL)                 /*!< ADC4/6/8 Trigger Event Source Master PWM Period  */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_0              (5UL)                 /*!< ADC4/6/8 Trigger Event Source External Event 0   */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_1              (6UL)                 /*!< ADC4/6/8 Trigger Event Source External Event 1   */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_2              (7UL)                 /*!< ADC4/6/8 Trigger Event Source External Event 2   */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_3              (8UL)                 /*!< ADC4/6/8 Trigger Event Source External Event 3   */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_4              (9UL)                 /*!< ADC4/6/8 Trigger Event Source External Event 4   */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPC              (10UL)                /*!< ADC4/6/8 Trigger Event Source PWM0 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPD              (11UL)                /*!< ADC4/6/8 Trigger Event Source PWM0 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_PRD               (12UL)                /*!< ADC4/6/8 Trigger Event Source PWM0 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_RST_ROLLOVER      (13UL)                /*!< ADC4/6/8 Trigger Event Source PWM0               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPC              (14UL)                /*!< ADC4/6/8 Trigger Event Source PWM1 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPD              (15UL)                /*!< ADC4/6/8 Trigger Event Source PWM1 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_PRD               (16UL)                /*!< ADC4/6/8 Trigger Event Source PWM1 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_RST_ROLLOVE       (17UL)                /*!< ADC4/6/8 Trigger Event Source PWM1               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPC              (18UL)                /*!< ADC4/6/8 Trigger Event Source PWM2 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPD              (19UL)                /*!< ADC4/6/8 Trigger Event Source PWM2 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_PRD               (20UL)                /*!< ADC4/6/8 Trigger Event Source PWM2 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPC              (21UL)                /*!< ADC4/6/8 Trigger Event Source PWM3 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPD              (22UL)                /*!< ADC4/6/8 Trigger Event Source PWM3 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_PRD               (23UL)                /*!< ADC4/6/8 Trigger Event Source PWM3 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPC              (24UL)                /*!< ADC4/6/8 Trigger Event Source PWM4 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPD              (25UL)                /*!< ADC4/6/8 Trigger Event Source PWM4 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_PRD               (26UL)                /*!< ADC4/6/8 Trigger Event Source PWM4 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPB              (27UL)                /*!< ADC4/6/8 Trigger Event Source PWM5 Compare B     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPC              (28UL)                /*!< ADC4/6/8 Trigger Event Source PWM5 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPD              (29UL)                /*!< ADC4/6/8 Trigger Event Source PWM5 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_PRD               (30UL)                /*!< ADC4/6/8 Trigger Event Source PWM5 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_RST_ROLLOVER      (31UL)                /*!< ADC4/6/8 Trigger Event Source PWM5               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPC              (32UL)                /*!< ADC4/6/8 Trigger Event Source PWM6 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPD              (33UL)                /*!< ADC4/6/8 Trigger Event Source PWM6 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_PRD               (34UL)                /*!< ADC4/6/8 Trigger Event Source PWM6 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_RST_ROLLOVER      (35UL)                /*!< ADC4/6/8 Trigger Event Source PWM6               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPC              (36UL)                /*!< ADC4/6/8 Trigger Event Source PWM7 Compare C     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPD              (37UL)                /*!< ADC4/6/8 Trigger Event Source PWM7 Compare D     */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_PRD               (38UL)                /*!< ADC4/6/8 Trigger Event Source PWM7 Period        */
#define LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_RST_ROLLOVER      (39UL)                /*!< ADC4/6/8 Trigger Event Source PWM7               \
                                                                                        Reset/Roll-Over                                  */

#define IS_LL_HRPWM_COMM_ADC468_TRIG_EVT(__VAL__)            (((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPA)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPB)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPC)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPD)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_PRD)       || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_0)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_1)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_2)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_3)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_4)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM0_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM1_RST_ROLLOVE)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM2_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM3_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM4_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM5_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM6_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC468_TRIG_EVT_PWM7_RST_ROLLOVER) )

/**
  * @brief HRPWM Common ADC5/7/9 Trigger Event Definition
  */
#define LL_HRPWM_Comm_ADC579TrigEvtSrcTypeDef                LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPA           (0UL)                 /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                        A                                                */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPB           (1UL)                 /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                        B                                                */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPC           (2UL)                 /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                        C                                                */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPD           (3UL)                 /*!< ADC5/7/9 Trigger Event Source Master PWM Compare \
                                                                                        D                                                */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_PRD            (4UL)                 /*!< ADC5/7/9 Trigger Event Source Master PWM Period  */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_5              (5UL)                 /*!< ADC5/7/9 Trigger Event Source External Event 5   */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_6              (6UL)                 /*!< ADC5/7/9 Trigger Event Source External Event 6   */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_7              (7UL)                 /*!< ADC5/7/9 Trigger Event Source External Event 7   */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_8              (8UL)                 /*!< ADC5/7/9 Trigger Event Source External Event 8   */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_9              (9UL)                 /*!< ADC5/7/9 Trigger Event Source External Event 9   */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPB              (10UL)                /*!< ADC5/7/9 Trigger Event Source PWM0 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPD              (11UL)                /*!< ADC5/7/9 Trigger Event Source PWM0 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_PRD               (12UL)                /*!< ADC5/7/9 Trigger Event Source PWM0 Period        */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPB              (13UL)                /*!< ADC5/7/9 Trigger Event Source PWM1 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPD              (14UL)                /*!< ADC5/7/9 Trigger Event Source PWM1 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_PRD               (15UL)                /*!< ADC5/7/9 Trigger Event Source PWM1 Period        */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPB              (16UL)                /*!< ADC5/7/9 Trigger Event Source PWM2 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPD              (17UL)                /*!< ADC5/7/9 Trigger Event Source PWM2 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_PRD               (18UL)                /*!< ADC5/7/9 Trigger Event Source PWM2 Period        */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_RST_ROLLOVER      (19UL)                /*!< ADC5/7/9 Trigger Event Source PWM2               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPB              (20UL)                /*!< ADC5/7/9 Trigger Event Source PWM3 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPD              (21UL)                /*!< ADC5/7/9 Trigger Event Source PWM3 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_PRD               (22UL)                /*!< ADC5/7/9 Trigger Event Source PWM3 Period        */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_RST_ROLLOVER      (23UL)                /*!< ADC5/7/9 Trigger Event Source PWM3               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPB              (24UL)                /*!< ADC5/7/9 Trigger Event Source PWM4 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPC              (25UL)                /*!< ADC5/7/9 Trigger Event Source PWM4 Compare C     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPD              (26UL)                /*!< ADC5/7/9 Trigger Event Source PWM4 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_RST_ROLLOVER      (27UL)                /*!< ADC5/7/9 Trigger Event Source PWM4               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPB              (28UL)                /*!< ADC5/7/9 Trigger Event Source PWM5 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPC              (29UL)                /*!< ADC5/7/9 Trigger Event Source PWM5 Compare C     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPD              (30UL)                /*!< ADC5/7/9 Trigger Event Source PWM5 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_PRD               (31UL)                /*!< ADC5/7/9 Trigger Event Source PWM5 Period        */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPB              (32UL)                /*!< ADC5/7/9 Trigger Event Source PWM6 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPD              (33UL)                /*!< ADC5/7/9 Trigger Event Source PWM6 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_PRD               (34UL)                /*!< ADC5/7/9 Trigger Event Source PWM6 Period        */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_RST_ROLLOVER      (35UL)                /*!< ADC5/7/9 Trigger Event Source PWM6               \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPB              (36UL)                /*!< ADC5/7/9 Trigger Event Source PWM7 Compare B     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPD              (37UL)                /*!< ADC5/7/9 Trigger Event Source PWM7 Compare D     */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_PRD               (38UL)                /*!< ADC5/7/9 Trigger Event Source PWM7 Period        */
#define LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_RST_ROLLOVER      (39UL)                /*!< ADC5/7/9 Trigger Event Source PWM7               \
                                                                                        Reset/Roll-Over                                  */

#define IS_LL_HRPWM_COMM_ADC579_TRIG_EVT(__VAL__)            (((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPA)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPB)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPC)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPD)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_PRD)       || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_5)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_6)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_7)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_8)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_9)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM0_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM1_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM2_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM3_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM4_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPC)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM5_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM6_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPB)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPD)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_PRD)          || \
                                                              ((__VAL__) == LL_HRPWM_COMM_ADC579_TRIG_EVT_PWM7_RST_ROLLOVER) )

/**
  * @brief HRPWM Common DLL Current Definition
  */
#define LL_HRPWM_Comm_DLLCurTypeDef                          LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_DLL_CUR_4uA                            (0UL)                 /*!< Common DLL Current 4uA                           */
#define LL_HRPWM_COMM_DLL_CUR_6uA                            (1UL)                 /*!< Common DLL Current 6uA                           */
#define LL_HRPWM_COMM_DLL_CUR_8uA                            (3UL)                 /*!< Common DLL Current 8uA                           */

#define IS_LL_HRPWM_COMM_DLL_CUR(__VAL__)                    (((__VAL__) == LL_HRPWM_COMM_DLL_CUR_4uA) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_DLL_CUR_6uA) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_DLL_CUR_8uA) )

/**
  * @brief HRPWM Common Fault X Input Source Definition
  */
#define LL_HRPWM_Comm_FltXInputSrcTypeDef                    LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_FLTx              (0UL)                 /*!< Common Fault Input Source HRPWM Fault            */
#define LL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_EVTx              (2UL)                 /*!< Common Fault Input Source HRPWM Event            */
#define LL_HRPWM_COMM_FLT0_INPUT_SRC_CMP1_OUT                (1UL)                 /*!< Common Fault 0 Input Source HRPWM CMP 1 Out      */
#define LL_HRPWM_COMM_FLT1_INPUT_SRC_CMP3_OUT                (1UL)                 /*!< Common Fault 1 Input Source HRPWM CMP 3 Out      */
#define LL_HRPWM_COMM_FLT2_INPUT_SRC_CMP5_OUT                (1UL)                 /*!< Common Fault 2 Input Source HRPWM CMP 5 Out      */
#define LL_HRPWM_COMM_FLT3_INPUT_SRC_CMP0_OUT                (1UL)                 /*!< Common Fault 3 Input Source HRPWM CMP 0 Out      */
#define LL_HRPWM_COMM_FLT4_INPUT_SRC_CMP2_OUT                (1UL)                 /*!< Common Fault 4 Input Source HRPWM CMP 2 Out      */
#define LL_HRPWM_COMM_FLT5_INPUT_SRC_CMP4_OUT                (1UL)                 /*!< Common Fault 5 Input Source HRPWM CMP 4 Out      */
#define LL_HRPWM_COMM_FLT6_INPUT_SRC_CMP7_OUT                (1UL)                 /*!< Common Fault 6 Input Source HRPWM CMP 7 Out      */
#define LL_HRPWM_COMM_FLT7_INPUT_SRC_CMP8_OUT                (1UL)                 /*!< Common Fault 7 Input Source HRPWM CMP 8 Out      */

#define IS_LL_HRPWM_FLT_INPUT_SRC(__VAL__)                   (((__VAL__) == LL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_FLTx) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLTx_INPUT_SRC_HRPWM_EVTx) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT0_INPUT_SRC_CMP1_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT1_INPUT_SRC_CMP3_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT2_INPUT_SRC_CMP5_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT3_INPUT_SRC_CMP0_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT4_INPUT_SRC_CMP2_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT5_INPUT_SRC_CMP4_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT6_INPUT_SRC_CMP7_OUT)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT7_INPUT_SRC_CMP8_OUT)   )

/**
  * @brief HRPWM Common Fault x Input Polarity Definition
  */
#define LL_HRPWM_Comm_FltInputPolTypeDef                     LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_FLT_INPUT_POL_ACT_HIGH                 (0UL)                 /*!< Common Fault x Input Polarity Active High        */
#define LL_HRPWM_COMM_FLT_INPUT_POL_ACT_LOW                  (1UL)                 /*!< Common Fault x Input Polarity Active Low         */

#define IS_LL_HRPWM_COMM_FLT_INPUT_POL_ACT(__VAL__)          (((__VAL__) == LL_HRPWM_COMM_FLT_INPUT_POL_ACT_HIGH) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT_INPUT_POL_ACT_LOW)  )

/**
  * @brief HRPWM Common Fault Sample Clock Division Definition
  */
#define LL_HRPWM_Comm_FltSampClkDivTypeDef                   LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_1                     (0UL)                 /*!< Common Fault Sample Clock Division 1             */
#define LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_2                     (1UL)                 /*!< Common Fault Sample Clock Division 2             */
#define LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_4                     (2UL)                 /*!< Common Fault Sample Clock Division 4             */
#define LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_8                     (3UL)                 /*!< Common Fault Sample Clock Division 8             */

#define IS_LL_HRPWM_COMM_FLT_SAMP_CLK_DIV(__VAL__)           (((__VAL__) == LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_1) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_2) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_4) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT_SAMP_CLK_DIV_8) )

/**
  * @brief HRPWM Common Fault X Blank Source Definition
  */
#define LL_HRPWM_Comm_FltBlkSrcTypeDef                       LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_FLT_BLK_SRC_FIXED_WIN                  (0UL)                 /*!< Common Fault X Blank Source Fixed Window         */
#define LL_HRPWM_COMM_FLT_BLK_SRC_MOVED_WIN                  (1UL)                 /*!< Common Fault X Blank Source Moved Window         */

#define IS_LL_HRPWM_COMM_FLT_BLK_SRC(__VAL__)                (((__VAL__) == LL_HRPWM_COMM_FLT_BLK_SRC_FIXED_WIN) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT_BLK_SRC_MOVED_WIN) )

/**
  * @brief HRPWM Common Fault X Counter Reset Mode Definition
  */
#define LL_HRPWM_Comm_FltCntrRstModeTypeDef                  LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_ALWAYS              (0UL)                 /*!< Common Fault Counter Reset at Reset/Roll-Over    \
                                                                                        Event Always                                     */
#define LL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_LAST_NO_EVT         (1UL)                 /*!< Common Fault Counter Reset at Reset/Roll-Over    \
                                                                                        Event Only Last No Event                         */

#define IS_LL_HRPWM_COMM_FLT_CNTR_RST_RSTRO(__VAL__)         (((__VAL__) == LL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_ALWAYS)      || \
                                                              ((__VAL__) == LL_HRPWM_COMM_FLT_CNTR_RST_RSTRO_LAST_NO_EVT) )

/**
  * @brief HRPWM Common Burst Mode Clock Prescaler Definition
  */
#define LL_HRPWM_Comm_BurstClkPresclTypeDef                  LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_BURST_CLK_PRESCL_1                     (0UL)                 /*!< Common Burst Mode Clock Prescaler 1              */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_2                     (1UL)                 /*!< Common Burst Mode Clock Prescaler 2              */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_4                     (2UL)                 /*!< Common Burst Mode Clock Prescaler 4              */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_8                     (3UL)                 /*!< Common Burst Mode Clock Prescaler 8              */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_16                    (4UL)                 /*!< Common Burst Mode Clock Prescaler 16             */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_32                    (5UL)                 /*!< Common Burst Mode Clock Prescaler 32             */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_64                    (6UL)                 /*!< Common Burst Mode Clock Prescaler 64             */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_128                   (7UL)                 /*!< Common Burst Mode Clock Prescaler 128            */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_256                   (8UL)                 /*!< Common Burst Mode Clock Prescaler 256            */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_512                   (9UL)                 /*!< Common Burst Mode Clock Prescaler 512            */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_1024                  (10UL)                /*!< Common Burst Mode Clock Prescaler 1024           */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_2048                  (11UL)                /*!< Common Burst Mode Clock Prescaler 2048           */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_4096                  (12UL)                /*!< Common Burst Mode Clock Prescaler 4096           */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_8192                  (13UL)                /*!< Common Burst Mode Clock Prescaler 8192           */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_16384                 (14UL)                /*!< Common Burst Mode Clock Prescaler 16384          */
#define LL_HRPWM_COMM_BURST_CLK_PRESCL_32768                 (15UL)                /*!< Common Burst Mode Clock Prescaler 32768          */

#define IS_LL_HRPWM_COMM_BURST_CLK_PRESCL(__VAL__)           (((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_1)     || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_2)     || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_4)     || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_8)     || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_16)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_32)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_64)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_128)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_256)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_512)   || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_1024)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_2048)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_4096)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_8192)  || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_16384) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_PRESCL_32768) )

/**
  * @brief HRPWM Common Burst Mode Trigger Mode Definition
  */
#define LL_HRPWM_Comm_BurstTrigModeTypeDef                   LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_BURST_TRIG_MODE_ASYNC                  (0UL)                 /*!< Common Burst Mode Asynchronous Trigger Mode      */
#define LL_HRPWM_COMM_BURST_TRIG_MODE_SYNC                   (1UL)                 /*!< Common Burst Mode Synchronous Trigger Mode       */

#define IS_LL_HRPWM_COMM_BURST_TRIG_MODE(__VAL__)            (((__VAL__) == LL_HRPWM_COMM_BURST_TRIG_MODE_ASYNC) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_TRIG_MODE_SYNC)  )

/**
  * @brief HRPWM Common Burst Mode Clock Source Definition
  */
#define LL_HRPWM_Comm_BurstClkSrcTypeDef                     LL_RSV_DATA_TYPE     

#define LL_HRPWM_COMM_BURST_CLK_SRC_MST_PWM_RST_ROLLOVER     (0UL)                 /*!< Common Burst Mode Clock Source Master PWM        \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM0_RST_ROLLOVER        (1UL)                 /*!< Common Burst Mode Clock Source PWM0              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM1_RST_ROLLOVER        (2UL)                 /*!< Common Burst Mode Clock Source PWM1              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM2_RST_ROLLOVER        (3UL)                 /*!< Common Burst Mode Clock Source PWM2              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM3_RST_ROLLOVER        (4UL)                 /*!< Common Burst Mode Clock Source PWM3              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM4_RST_ROLLOVER        (5UL)                 /*!< Common Burst Mode Clock Source PWM4              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM5_RST_ROLLOVER        (6UL)                 /*!< Common Burst Mode Clock Source PWM5              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM6_RST_ROLLOVER        (7UL)                 /*!< Common Burst Mode Clock Source PWM6              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_PWM7_RST_ROLLOVER        (8UL)                 /*!< Common Burst Mode Clock Source PWM7              \
                                                                                        Reset/Roll-Over                                  */
#define LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN0             (12UL)                /*!< Common Burst Mode Clock Source hrpwm_bm_in0      */
#define LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN1             (13UL)                /*!< Common Burst Mode Clock Source hrpwm_bm_in1      */
#define LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN2             (14UL)                /*!< Common Burst Mode Clock Source hrpwm_bm_in2      */
#define LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_FUNC_CLK           (15UL)                /*!< Common Burst Mode Clock Source HRPWM Function    \
                                                                                        Clock                                            */

#define IS_LL_HRPWM_COMM_BURST_CLK_SRC(__VAL__)              (((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_MST_PWM_RST_ROLLOVER) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM0_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM1_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM2_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM3_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM4_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM5_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM6_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_PWM7_RST_ROLLOVER)    || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN0)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN1)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN2)         || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_CLK_SRC_HRPWM_FUNC_CLK)       )


/**
  * @brief HRPWM PWM Mask Definition
  */
#define LL_HRPWM_PWMMaskTypeDef                              uint32_t     

#define LL_HRPWM_PWM_NONE_MASK                               (0UL)                 /*!< HRPWM PWM None Mask                              */
#define LL_HRPWM_MST_PWM_MASK                                (BIT(0))              /*!< HRPWM Master PWM Mask                            */
#define LL_HRPWM_SLV_PWM_0_MASK                              (BIT(1))              /*!< HRPWM Slave PWM 0 Mask                           */
#define LL_HRPWM_SLV_PWM_1_MASK                              (BIT(2))              /*!< HRPWM Slave PWM 1 Mask                           */
#define LL_HRPWM_SLV_PWM_2_MASK                              (BIT(3))              /*!< HRPWM Slave PWM 2 Mask                           */
#define LL_HRPWM_SLV_PWM_3_MASK                              (BIT(4))              /*!< HRPWM Slave PWM 3 Mask                           */
#define LL_HRPWM_SLV_PWM_4_MASK                              (BIT(5))              /*!< HRPWM Slave PWM 4 Mask                           */
#define LL_HRPWM_SLV_PWM_5_MASK                              (BIT(6))              /*!< HRPWM Slave PWM 5 Mask                           */
#define LL_HRPWM_SLV_PWM_6_MASK                              (BIT(7))              /*!< HRPWM Slave PWM 6 Mask                           */
#define LL_HRPWM_SLV_PWM_7_MASK                              (BIT(8))              /*!< HRPWM Slave PWM 7 Mask                           */
#define LL_HRPWM_ALL_PWM_MASK                                (0x1FFUL)             /*!< HRPWM All PWM Mask                               */

#define IS_LL_HRPWM_PWM_MASK(__VAL__)                        ((((__VAL__) & LL_HRPWM_ALL_PWM_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_PWM_NONE_MASK) )

#if (LL_HRPWM_ALL_PWM_MASK != LL_HRPWM_MDIER_MST_IT_EN_MSK) || \
    (LL_HRPWM_ALL_PWM_MASK != LL_HRPWM_CR2_SW_UPD_MSK)      || \
    (LL_HRPWM_ALL_PWM_MASK != LL_HRPWM_CR0_UPD_DIS_MSK)
#error "LL_HRPWM_PWMMaskTypeDef"
#endif


/**
  * @brief HRPWM Fault Mask Definition
  */
#define LL_HRPWM_Slv_FltMskTypeDef                           uint32_t     

#define LL_HRPWM_SLV_FLT_NONE_MASK                           (0UL)                 /*!< HRPWM Slave PWM Fault None Mask                  */
#define LL_HRPWM_SLV_FLT_PWM_0_MASK                          (BIT(0))              /*!< HRPWM Slave PWM Fault 0 Mask                     */
#define LL_HRPWM_SLV_FLT_PWM_1_MASK                          (BIT(1))              /*!< HRPWM Slave PWM Fault 1 Mask                     */
#define LL_HRPWM_SLV_FLT_PWM_2_MASK                          (BIT(2))              /*!< HRPWM Slave PWM Fault 2 Mask                     */
#define LL_HRPWM_SLV_FLT_PWM_3_MASK                          (BIT(3))              /*!< HRPWM Slave PWM Fault 3 Mask                     */
#define LL_HRPWM_SLV_FLT_PWM_4_MASK                          (BIT(4))              /*!< HRPWM Slave PWM Fault 4 Mask                     */
#define LL_HRPWM_SLV_FLT_PWM_5_MASK                          (BIT(5))              /*!< HRPWM Slave PWM Fault 5 Mask                     */
#define LL_HRPWM_SLV_FLT_PWM_6_MASK                          (BIT(6))              /*!< HRPWM Slave PWM Fault 6 Mask                     */
#define LL_HRPWM_SLV_FLT_PWM_7_MASK                          (BIT(7))              /*!< HRPWM Slave PWM Fault 7 Mask                     */
#define LL_HRPWM_ALL_FLT_PWM_MASK                            (0xFFUL)              /*!< HRPWM All Slave PWM Fault Mask                   */

#define IS_LL_HRPWM_SLV_PWM_FLT_MASK(__VAL__)                ((((__VAL__) & LL_HRPWM_ALL_FLT_PWM_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_FLT_NONE_MASK) )

#if LL_HRPWM_ALL_FLT_PWM_MASK != LL_HRPWM_FLTR_PWMx_FLTx_EN_MSK
#error "LL_HRPWM_Slv_FltMskTypeDef"
#endif

/**
  * @brief HRPWM Update Trigger PWMx Definition
  */
#define LL_HRPWM_Slv_PWMUpdTrigTypeDef                       uint32_t     

#define LL_HRPWM_SLV_UPD_TRIG_NONE_MASK                      (0UL)                 /*!< HRPWM None Update Trigger PWMx Mask              */
#define LL_HRPWM_SLV_UPD_TRIG_MST_MASK                       (BIT(16))             /*!< HRPWM Master PWM Update Trigger PWMx             */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_0_MASK                 (BIT(17))             /*!< HRPWM Slave PWM 0 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_1_MASK                 (BIT(18))             /*!< HRPWM Slave PWM 1 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_2_MASK                 (BIT(19))             /*!< HRPWM Slave PWM 2 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_3_MASK                 (BIT(20))             /*!< HRPWM Slave PWM 3 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_4_MASK                 (BIT(21))             /*!< HRPWM Slave PWM 4 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_5_MASK                 (BIT(22))             /*!< HRPWM Slave PWM 5 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_6_MASK                 (BIT(23))             /*!< HRPWM Slave PWM 6 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_SLV_PWM_7_MASK                 (BIT(24))             /*!< HRPWM Slave PWM 7 Update Trigger PWMx            */
#define LL_HRPWM_SLV_UPD_TRIG_ALL_PWM_MASK                   (0x01FF0000UL)        /*!< HRPWM All PWM Update Trigger PWMx Mask           */

#define IS_LL_HRPWM_SLV_UPD_TRIG_PWM_MASK(__VAL__)           ((((__VAL__) & LL_HRPWM_SLV_UPD_TRIG_ALL_PWM_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_UPD_TRIG_NONE_MASK) )

#if LL_HRPWM_SLV_UPD_TRIG_ALL_PWM_MASK != LL_HRPWM_PWMCR1_UPD_TRG_PWMx_MSK
#error "LL_HRPWM_Slv_PWMUpdTrigTypeDef"
#endif

/**
  * @brief HRPWM PWM Output Mask Definition
  */
#define LL_HRPWM_PWMOutputMaskTypeDef                        uint32_t     

#define LL_HRPWM_SLV_PWM_OUT_NONE_MASK                       (0UL)                 /*!< HRPWM Slave PWM Out None Mask                    */
#define LL_HRPWM_SLV_PWM_0_OUT_A_MASK                        (BIT(0))              /*!< HRPWM Slave PWM 0 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_0_OUT_B_MASK                        (BIT(1))              /*!< HRPWM Slave PWM 0 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_1_OUT_A_MASK                        (BIT(2))              /*!< HRPWM Slave PWM 1 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_1_OUT_B_MASK                        (BIT(3))              /*!< HRPWM Slave PWM 1 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_2_OUT_A_MASK                        (BIT(4))              /*!< HRPWM Slave PWM 2 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_2_OUT_B_MASK                        (BIT(5))              /*!< HRPWM Slave PWM 2 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_3_OUT_A_MASK                        (BIT(6))              /*!< HRPWM Slave PWM 3 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_3_OUT_B_MASK                        (BIT(7))              /*!< HRPWM Slave PWM 3 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_4_OUT_A_MASK                        (BIT(8))              /*!< HRPWM Slave PWM 4 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_4_OUT_B_MASK                        (BIT(9))              /*!< HRPWM Slave PWM 4 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_5_OUT_A_MASK                        (BIT(10))             /*!< HRPWM Slave PWM 5 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_5_OUT_B_MASK                        (BIT(11))             /*!< HRPWM Slave PWM 5 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_6_OUT_A_MASK                        (BIT(12))             /*!< HRPWM Slave PWM 6 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_6_OUT_B_MASK                        (BIT(13))             /*!< HRPWM Slave PWM 6 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_7_OUT_A_MASK                        (BIT(14))             /*!< HRPWM Slave PWM 7 Out A Mask                     */
#define LL_HRPWM_SLV_PWM_7_OUT_B_MASK                        (BIT(15))             /*!< HRPWM Slave PWM 7 Out B Mask                     */
#define LL_HRPWM_SLV_PWM_OUT_ALL_MASK                        (0xFFFFUL)            /*!< HRPWM Slave PWM Out All Mask                     */

#define IS_LL_HRPWM_SLV_PWM_OUT(__VAL__)                     ((((__VAL__) & LL_HRPWM_SLV_PWM_OUT_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_PWM_OUT_NONE_MASK) )

#if (LL_HRPWM_SLV_PWM_OUT_ALL_MASK != LL_HRPWM_OENR_OUTx_START_MSK) || \
    (LL_HRPWM_SLV_PWM_OUT_ALL_MASK != LL_HRPWM_ODISR_OUTx_STOP_MSK)
#error "LL_HRPWM_PWMOutputMaskTypeDef"
#endif

/**
  * @brief HRPWM Master PWM Interrupt Definition
  */
#define LL_HRPWM_Mst_IntTypeDef                              uint32_t     

#define LL_HRPWM_MST_INT_NONE                                (0UL)                 /*!< Master Interrupt None                            */
#define LL_HRPWM_MST_INT_CMPA                                (BIT(0))              /*!< Master Interrupt Compare A                       */
#define LL_HRPWM_MST_INT_CMPB                                (BIT(1))              /*!< Master Interrupt Compare B                       */
#define LL_HRPWM_MST_INT_CMPC                                (BIT(2))              /*!< Master Interrupt Compare C                       */
#define LL_HRPWM_MST_INT_CMPD                                (BIT(3))              /*!< Master Interrupt Compare D                       */
#define LL_HRPWM_MST_INT_PRD                                 (BIT(4))              /*!< Master Interrupt Period                          */
#define LL_HRPWM_MST_INT_SYNCIN                              (BIT(5))              /*!< Master Interrupt Sync In                         */
#define LL_HRPWM_MST_INT_UPD                                 (BIT(6))              /*!< Master Interrupt Update                          */
#define LL_HRPWM_MST_INT_RST                                 (BIT(7))              /*!< Master Interrupt Reset                           */
#define LL_HRPWM_MST_INT_REP                                 (BIT(8))              /*!< Master Interrupt Repetition                      */
#define LL_HRPWM_MST_INT_ALL_MASK                            (0x01FFUL)            /*!< Master Interrupt All Mask                        */

#define IS_LL_HRPWM_MST_INT(__VAL__)                         ((((__VAL__) & LL_HRPWM_MST_INT_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_MST_INT_NONE))

#if (LL_HRPWM_MST_INT_ALL_MASK != LL_HRPWM_MDIER_MST_IT_EN_MSK) || \
    (LL_HRPWM_MST_INT_ALL_MASK != LL_HRPWM_MISR_MST_IT_FLAG_MSK)
#error "LL_HRPWM_Mst_IntTypeDef"
#endif

/**
  * @brief HRPWM Master PWM DMA Definition
  */
#define LL_HRPWM_Mst_DMATypeDef                              uint32_t     

#define LL_HRPWM_MST_DMA_NONE                                (0UL)                 /*!< Master DMA None                                  */
#define LL_HRPWM_MST_DMA_CMPA                                (BIT(16))             /*!< Master DMA Compare A                             */
#define LL_HRPWM_MST_DMA_CMPB                                (BIT(17))             /*!< Master DMA Compare B                             */
#define LL_HRPWM_MST_DMA_CMPC                                (BIT(18))             /*!< Master DMA Compare C                             */
#define LL_HRPWM_MST_DMA_CMPD                                (BIT(19))             /*!< Master DMA Compare D                             */
#define LL_HRPWM_MST_DMA_PRD                                 (BIT(20))             /*!< Master DMA Period                                */
#define LL_HRPWM_MST_DMA_SYNCIN                              (BIT(21))             /*!< Master DMA Sync In                               */
#define LL_HRPWM_MST_DMA_UPD                                 (BIT(22))             /*!< Master DMA Update                                */
#define LL_HRPWM_MST_DMA_RST                                 (BIT(23))             /*!< Master DMA Reset                                 */
#define LL_HRPWM_MST_DMA_REP                                 (BIT(24))             /*!< Master DMA Repetition                            */
#define LL_HRPWM_MST_DMA_ALL_MASK                            (0x01FF0000UL)        /*!< Master DMA All Mask                              */

#define IS_LL_HRPWM_MST_DMA(__VAL__)                         ((((__VAL__) & LL_HRPWM_MST_DMA_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_MST_DMA_NONE))

#if LL_HRPWM_MST_DMA_ALL_MASK != LL_HRPWM_MDIER_DMA_EN_MSK
#error "LL_HRPWM_Mst_DMATypeDef"
#endif

/**
  * @brief HRPWM Slave PWM Interrupt Definition
  */
#define LL_HRPWM_Slv_IntTypeDef                              uint32_t     

#define LL_HRPWM_SLV_INT_NONE                                (0UL)                 /*!< Slave Interrupt None                             */
#define LL_HRPWM_SLV_INT_CMPA                                (BIT(0))              /*!< Slave Interrupt Compare A                        */
#define LL_HRPWM_SLV_INT_CMPB                                (BIT(1))              /*!< Slave Interrupt Compare B                        */
#define LL_HRPWM_SLV_INT_CMPC                                (BIT(2))              /*!< Slave Interrupt Compare C                        */
#define LL_HRPWM_SLV_INT_CMPD                                (BIT(3))              /*!< Slave Interrupt Compare D                        */
#define LL_HRPWM_SLV_INT_PRD_RO                              (BIT(4))              /*!< Slave Interrupt Period/Roll-Over                 */
#define LL_HRPWM_SLV_INT_UPD                                 (BIT(5))              /*!< Slave Interrupt Update                           */
#define LL_HRPWM_SLV_INT_OUTA_SET                            (BIT(6))              /*!< Slave Interrupt OutA Set                         */
#define LL_HRPWM_SLV_INT_OUTA_CLR                            (BIT(7))              /*!< Slave Interrupt OutA Clear                       */
#define LL_HRPWM_SLV_INT_OUTB_SET                            (BIT(8))              /*!< Slave Interrupt OutB Set                         */
#define LL_HRPWM_SLV_INT_OUTB_CLR                            (BIT(9))              /*!< Slave Interrupt OutB Clear                       */
#define LL_HRPWM_SLV_INT_RST                                 (BIT(10))             /*!< Slave Interrupt Reset                            */
#define LL_HRPWM_SLV_INT_REP                                 (BIT(11))             /*!< Slave Interrupt Repetition                       */
#define LL_HRPWM_SLV_INT_CAPA                                (BIT(12))             /*!< Slave Interrupt Capture A                        */
#define LL_HRPWM_SLV_INT_CAPB                                (BIT(13))             /*!< Slave Interrupt Capture B                        */
#define LL_HRPWM_SLV_INT_DLY_PROT                            (BIT(14))             /*!< Slave Interrupt Delay Protection                 */
#define LL_HRPWM_SLV_INT_ALL_MASK                            (0x7FFFUL)            /*!< Slave Interrupt All Mask                         */

#define IS_LL_HRPWM_SLV_INT(__VAL__)                         ((((__VAL__) & LL_HRPWM_SLV_INT_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_INT_NONE))

#if (LL_HRPWM_SLV_INT_ALL_MASK != LL_HRPWM_PWMDIER_PWMx_IT_EN_MSK) || \
    (LL_HRPWM_SLV_INT_ALL_MASK != LL_HRPWM_PWMISR_PWMx_IT_FLAG_MSK)
#error "LL_HRPWM_Slv_IntTypeDef"
#endif

/**
  * @brief HRPWM Slave PWM DMA Definition
  */
#define LL_HRPWM_Slv_DMATypeDef                              uint32_t     

#define LL_HRPWM_SLV_DMA_NONE                                (0UL)                 /*!< Slave DMA None                                   */
#define LL_HRPWM_SLV_DMA_CMPA                                (BIT(16))             /*!< Slave DMA Compare A                              */
#define LL_HRPWM_SLV_DMA_CMPB                                (BIT(17))             /*!< Slave DMA Compare B                              */
#define LL_HRPWM_SLV_DMA_CMPC                                (BIT(18))             /*!< Slave DMA Compare C                              */
#define LL_HRPWM_SLV_DMA_CMPD                                (BIT(19))             /*!< Slave DMA Compare D                              */
#define LL_HRPWM_SLV_DMA_PRD_RO                              (BIT(20))             /*!< Slave DMA Period/Roll-Over                       */
#define LL_HRPWM_SLV_DMA_UPD                                 (BIT(21))             /*!< Slave DMA Update                                 */
#define LL_HRPWM_SLV_DMA_OUTA_SET                            (BIT(22))             /*!< Slave DMA OutA Set                               */
#define LL_HRPWM_SLV_DMA_OUTA_CLR                            (BIT(23))             /*!< Slave DMA OutA Clear                             */
#define LL_HRPWM_SLV_DMA_OUTB_SET                            (BIT(24))             /*!< Slave DMA OutB Set                               */
#define LL_HRPWM_SLV_DMA_OUTB_CLR                            (BIT(25))             /*!< Slave DMA OutB Clear                             */
#define LL_HRPWM_SLV_DMA_RST                                 (BIT(26))             /*!< Slave DMA Reset                                  */
#define LL_HRPWM_SLV_DMA_REP                                 (BIT(27))             /*!< Slave DMA Repetition                             */
#define LL_HRPWM_SLV_DMA_CAPA                                (BIT(28))             /*!< Slave DMA Capture A                              */
#define LL_HRPWM_SLV_DMA_CAPB                                (BIT(29))             /*!< Slave DMA Capture B                              */
#define LL_HRPWM_SLV_DMA_DLY_PROT                            (BIT(30))             /*!< Slave DMA Delay Protection                       */
#define LL_HRPWM_SLV_DMA_ALL_MASK                            (0x7FFF0000UL)        /*!< Slave DMA All Mask                               */

#define IS_LL_HRPWM_SLV_DMA(__VAL__)                         ((((__VAL__) & LL_HRPWM_SLV_DMA_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_DMA_NONE))

#if LL_HRPWM_SLV_DMA_ALL_MASK != LL_HRPWM_PWMDIER_PWMx_DMA_EN_MSK
#error "LL_HRPWM_Slv_DMATypeDef"
#endif

/**
  * @brief HRPWM Common Interrupt Definition
  */
#define LL_HRPWM_Comm_IntTypeDef                              uint32_t     

#define LL_HRPWM_COMM_INT_NONE                                (0UL)                 /*!< Common Interrupt None                           */
#define LL_HRPWM_COMM_INT_FAULT_SYS                           (BIT(0))              /*!< Common Interrupt System Fault                   */
#define LL_HRPWM_COMM_INT_FAULT_0                             (BIT(1))              /*!< Common Interrupt Fault 0                        */
#define LL_HRPWM_COMM_INT_FAULT_1                             (BIT(2))              /*!< Common Interrupt Fault 1                        */
#define LL_HRPWM_COMM_INT_FAULT_2                             (BIT(3))              /*!< Common Interrupt Fault 2                        */
#define LL_HRPWM_COMM_INT_FAULT_3                             (BIT(4))              /*!< Common Interrupt Fault 3                        */
#define LL_HRPWM_COMM_INT_FAULT_4                             (BIT(5))              /*!< Common Interrupt Fault 4                        */
#define LL_HRPWM_COMM_INT_FAULT_5                             (BIT(6))              /*!< Common Interrupt Fault 5                        */
#define LL_HRPWM_COMM_INT_FAULT_6                             (BIT(7))              /*!< Common Interrupt Fault 6                        */
#define LL_HRPWM_COMM_INT_FAULT_7                             (BIT(8))              /*!< Common Interrupt Fault 7                        */
#define LL_HRPWM_COMM_INT_BURST_PRD                           (BIT(15))             /*!< Common Interrupt Burst Mode Period              */
#define LL_HRPWM_COMM_INT_ALL_MASK                            (0x81FFUL)            /*!< Common Interrupt All Mask                       */

#define IS_LL_HRPWM_COMM_INT(__VAL__)                         ((((__VAL__) & LL_HRPWM_COMM_INT_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_INT_NONE))

#if (LL_HRPWM_COMM_INT_ALL_MASK != LL_HRPWM_IER_COM_IT_EN_MSK) || \
    (LL_HRPWM_COMM_INT_ALL_MASK != LL_HRPWM_ISR_COM_IT_FLAG_MSK)
#error "LL_HRPWM_Comm_IntTypeDef"
#endif

/**
  * @brief HRPWM Slave Output Control Event Definition
  */
#define LL_HRPWM_Slv_OutCtrlEvtTypeDef                       uint32_t     

#define LL_HRPWM_SLV_OUT_CTRL_EVT_NONE                       (0UL)                 /*!< Slave Output Control Event None                  */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG                    (BIT(0))              /*!< Slave Output Control Event Software Set Trigger  */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPA                  (BIT(1))              /*!< Slave Output Control Event PWMx Compare A        */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPB                  (BIT(2))              /*!< Slave Output Control Event PWMx Compare B        */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPC                  (BIT(3))              /*!< Slave Output Control Event PWMx Compare C        */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPD                  (BIT(4))              /*!< Slave Output Control Event PWMx Compare D        */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_ROLL_OVER             (BIT(5))              /*!< Slave Output Control Event PWMx Roll Over        */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPA               (BIT(6))              /*!< Slave Output Control Event Master PWM Compare A  */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPB               (BIT(7))              /*!< Slave Output Control Event Master PWM Compare B  */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPC               (BIT(8))              /*!< Slave Output Control Event Master PWM Compare C  */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPD               (BIT(9))              /*!< Slave Output Control Event Master PWM Compare D  */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_PERIOD             (BIT(10))             /*!< Slave Output Control Event Master PWM Period     */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT0                  (BIT(11))             /*!< Slave Output Control Event PWMx Event 0          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT1                  (BIT(12))             /*!< Slave Output Control Event PWMx Event 1          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT2                  (BIT(13))             /*!< Slave Output Control Event PWMx Event 2          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT3                  (BIT(14))             /*!< Slave Output Control Event PWMx Event 3          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT4                  (BIT(15))             /*!< Slave Output Control Event PWMx Event 4          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT5                  (BIT(16))             /*!< Slave Output Control Event PWMx Event 5          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT6                  (BIT(17))             /*!< Slave Output Control Event PWMx Event 6          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT7                  (BIT(18))             /*!< Slave Output Control Event PWMx Event 7          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT8                  (BIT(19))             /*!< Slave Output Control Event PWMx Event 8          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT9                  (BIT(20))             /*!< Slave Output Control Event PWMx Event 9          */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_SYNC_INPUT_EVT             (BIT(21))             /*!< Slave Output Control Event Sync Input Event      */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_PWMx_UPDATE                (BIT(22))             /*!< Slave Output Control Event PWMx Update           */
#define LL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK                   (0x7FFFFFUL)          /*!< Slave Output Control Event All Mask              */

#define IS_LL_HRPWM_SLV_OUT_CTRL_EVT(__VAL__)                ((((__VAL__) & LL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_SLV_OUT_CTRL_EVT_NONE) )

/**
  * @brief HRPWM Common Burst DMA PWM Register Update Definition
  */
#define LL_HRPWM_Comm_BurstDMARegUpdTypeDef                  uint32_t

/**
  * @brief HRPWM Common Burst DMA Master PWM Register Update Definition
  */
#define LL_HRPWM_Comm_BurstDMAMstRegUpdTypeDef               uint32_t     

#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_NONE             (0UL)                 /*!< Common Burst DMA Master PWM Register Update None */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCR0             (BIT(0))              /*!< Common Burst DMA Master PWM Register Update MCR0 */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCR1             (BIT(1))              /*!< Common Burst DMA Master PWM Register Update MCR1 */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MISR             (BIT(2))              /*!< Common Burst DMA Master PWM Register Update MISR */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MDIER            (BIT(3))              /*!< Common Burst DMA Master PWM Register Update      \
                                                                                        MDIER                                            */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCNTR            (BIT(4))              /*!< Common Burst DMA Master PWM Register Update      \
                                                                                        MCNTR                                            */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MPER             (BIT(5))              /*!< Common Burst DMA Master PWM Register Update MPER */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MREP             (BIT(6))              /*!< Common Burst DMA Master PWM Register Update MREP */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPAR           (BIT(7))              /*!< Common Burst DMA Master PWM Register Update      \
                                                                                        MCMPAR                                           */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPBR           (BIT(8))              /*!< Common Burst DMA Master PWM Register Update      \
                                                                                        MCMPBR                                           */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPCR           (BIT(9))              /*!< Common Burst DMA Master PWM Register Update      \
                                                                                        MCMPCR                                           */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPDR           (BIT(10))             /*!< Common Burst DMA Master PWM Register Update      \
                                                                                        MCMPDR                                           */
#define LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL_MASK         (0x7FFUL)             /*!< Common Burst DMA Master PWM Register Update All  */

#define IS_LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD(__VAL__)      ((((__VAL__) & LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_NONE) )

#if LL_HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL_MASK != LL_HRPWM_MDMAUR_SYSDMA_UPD_MSK
#error "LL_HRPWM_Slv_DMATypeDef"
#endif


/**
  * @brief HRPWM Common Burst DMA Slave PWMx Register Update Definition
  */
#define LL_HRPWM_Comm_BurstDMASlvRegUpdTypeDef               uint32_t     

#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_NONE             (0UL)                 /*!< Common Burst DMA Slave PWM Register Update None  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CR0              (BIT(0))              /*!< Common Burst DMA Slave PWM Register Update CR0   */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CR1              (BIT(1))              /*!< Common Burst DMA Slave PWM Register Update CR1   */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ISR              (BIT(2))              /*!< Common Burst DMA Slave PWM Register Update ISR   */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_DIER             (BIT(3))              /*!< Common Burst DMA Slave PWM Register Update DIER  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CNTR             (BIT(4))              /*!< Common Burst DMA Slave PWM Register Update CNTR  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_PERR             (BIT(5))              /*!< Common Burst DMA Slave PWM Register Update PERR  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_REPR             (BIT(6))              /*!< Common Burst DMA Slave PWM Register Update REPR  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPAR            (BIT(7))              /*!< Common Burst DMA Slave PWM Register Update CMPAR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPBR            (BIT(8))              /*!< Common Burst DMA Slave PWM Register Update CMPBR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPCR            (BIT(9))              /*!< Common Burst DMA Slave PWM Register Update CMPCR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPDR            (BIT(10))             /*!< Common Burst DMA Slave PWM Register Update CMPDR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPAR            (BIT(11))             /*!< Common Burst DMA Slave PWM Register Update CAPAR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBR            (BIT(12))             /*!< Common Burst DMA Slave PWM Register Update CAPBR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_DTR              (BIT(13))             /*!< Common Burst DMA Slave PWM Register Update DTR   */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_SETAR            (BIT(14))             /*!< Common Burst DMA Slave PWM Register Update SETAR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CLRAR            (BIT(15))             /*!< Common Burst DMA Slave PWM Register Update CLRAR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_SETBR            (BIT(16))             /*!< Common Burst DMA Slave PWM Register Update SETBR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CLRBR            (BIT(17))             /*!< Common Burst DMA Slave PWM Register Update CLRBR */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR0            (BIT(18))             /*!< Common Burst DMA Slave PWM Register Update EEFR0 */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR1            (BIT(19))             /*!< Common Burst DMA Slave PWM Register Update EEFR1 */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR2            (BIT(20))             /*!< Common Burst DMA Slave PWM Register Update EEFR2 */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_RSTR             (BIT(21))             /*!< Common Burst DMA Slave PWM Register Update RSTR  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_RSTER            (BIT(22))             /*!< Common Burst DMA Slave PWM Register Update RSTER */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CHPR             (BIT(23))             /*!< Common Burst DMA Slave PWM Register Update CHPR  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPACR           (BIT(24))             /*!< Common Burst DMA Slave PWM Register Update       \
                                                                                        CAPACR                                           */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPACER          (BIT(25))             /*!< Common Burst DMA Slave PWM Register Update       \
                                                                                        CAPACER                                          */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBCR           (BIT(26))             /*!< Common Burst DMA Slave PWM Register Update       \
                                                                                        CAPBCR                                           */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBCER          (BIT(27))             /*!< Common Burst DMA Slave PWM Register Update       \
                                                                                        CAPBCER                                          */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_OUTR             (BIT(28))             /*!< Common Burst DMA Slave PWM Register Update OUTR  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_FLTR             (BIT(29))             /*!< Common Burst DMA Slave PWM Register Update FLTR  */
#define LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL_MASK         (0x3FFFFFFFUL)        /*!< Common Burst DMA Slave PWM Register Update All   */

#define IS_LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD(__VAL__)      ((((__VAL__) & LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL_MASK) != 0UL) || \
                                                              ((__VAL__) == LL_HRPWM_COMM_BURST_DMA_SLV_REG_UPD_NONE) )

/**
  * @brief HRPWM Common ADC Trigger Event Source Definition
  */
#define LL_HRPWM_Comm_ADCTrigEvtSrcTypeDef             uint64_t    
#define LL_HRPWM_COMM_ADC_TRIG_EVT_ALL_MASK            (0xFFFFFFFFFFULL) 

/**
  * @brief HRPWM Common ADC0/2 Trigger Event Source Definition
  */
#define LL_HRPWM_Comm_ADC02TrigEvtSrcTypeDef           LL_HRPWM_Comm_ADCTrigEvtSrcTypeDef

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_NONE              (0)                     /*!< ADC0/2 Trigger Event Source None                   */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPA      BITLL(0)                /*!< ADC0/2 Trigger Event Source Master PWM Compare A   */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPB      BITLL(1)                /*!< ADC0/2 Trigger Event Source Master PWM Compare B   */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPC      BITLL(2)                /*!< ADC0/2 Trigger Event Source Master PWM Compare C   */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPD      BITLL(3)                /*!< ADC0/2 Trigger Event Source Master PWM Compare D   */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_PRD       BITLL(4)                /*!< ADC0/2 Trigger Event Source Master PWM Period      */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_0         BITLL(5)                /*!< ADC0/2 Trigger Event Source External Event 0       */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_1         BITLL(6)                /*!< ADC0/2 Trigger Event Source External Event 1       */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_2         BITLL(7)                /*!< ADC0/2 Trigger Event Source External Event 2       */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_3         BITLL(8)                /*!< ADC0/2 Trigger Event Source External Event 3       */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_4         BITLL(9)                /*!< ADC0/2 Trigger Event Source External Event 4       */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPC         BITLL(10)               /*!< ADC0/2 Trigger Event Source PWM0 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPD         BITLL(11)               /*!< ADC0/2 Trigger Event Source PWM0 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_PRD          BITLL(12)               /*!< ADC0/2 Trigger Event Source PWM0 Period            */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM0_RST_ROLLOVER BITLL(13)               /*!< ADC0/2 Trigger Event Source PWM0 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPC         BITLL(14)               /*!< ADC0/2 Trigger Event Source PWM1 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPD         BITLL(15)               /*!< ADC0/2 Trigger Event Source PWM1 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_PRD          BITLL(16)               /*!< ADC0/2 Trigger Event Source PWM1 Period            */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM1_RST_ROLLOVE  BITLL(17)               /*!< ADC0/2 Trigger Event Source PWM1 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPC         BITLL(18)               /*!< ADC0/2 Trigger Event Source PWM2 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPD         BITLL(19)               /*!< ADC0/2 Trigger Event Source PWM2 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM2_PRD          BITLL(20)               /*!< ADC0/2 Trigger Event Source PWM2 Period            */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPC         BITLL(21)               /*!< ADC0/2 Trigger Event Source PWM3 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPD         BITLL(22)               /*!< ADC0/2 Trigger Event Source PWM3 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM3_PRD          BITLL(23)               /*!< ADC0/2 Trigger Event Source PWM3 Period            */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPC         BITLL(24)               /*!< ADC0/2 Trigger Event Source PWM4 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPD         BITLL(25)               /*!< ADC0/2 Trigger Event Source PWM4 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM4_PRD          BITLL(26)               /*!< ADC0/2 Trigger Event Source PWM4 Period            */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPB         BITLL(27)               /*!< ADC0/2 Trigger Event Source PWM5 Compare B         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPC         BITLL(28)               /*!< ADC0/2 Trigger Event Source PWM5 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPD         BITLL(29)               /*!< ADC0/2 Trigger Event Source PWM5 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_PRD          BITLL(30)               /*!< ADC0/2 Trigger Event Source PWM5 Period            */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM5_RST_ROLLOVER ((uint64_t)BITLL(31))   /*!< ADC0/2 Trigger Event Source PWM5 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPC         ((uint64_t)BITLL(32))   /*!< ADC0/2 Trigger Event Source PWM6 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPD         ((uint64_t)BITLL(33))   /*!< ADC0/2 Trigger Event Source PWM6 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_PRD          ((uint64_t)BITLL(34))   /*!< ADC0/2 Trigger Event Source PWM6 Period            */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM6_RST_ROLLOVER ((uint64_t)BITLL(35))   /*!< ADC0/2 Trigger Event Source PWM6 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPC         ((uint64_t)BITLL(36))   /*!< ADC0/2 Trigger Event Source PWM7 Compare C         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPD         ((uint64_t)BITLL(37))   /*!< ADC0/2 Trigger Event Source PWM7 Compare D         */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_PRD          ((uint64_t)BITLL(38))   /*!< ADC0/2 Trigger Event Source PWM7 Period            */
#define LL_HRPWM_COMM_ADC02_TRIG_EVT_PWM7_RST_ROLLOVER ((uint64_t)BITLL(39))   /*!< ADC0/2 Trigger Event Source PWM7 Reset/Roll-Over   */

/**
  * @brief HRPWM Common ADC1/3 Trigger Event Definition
  */
#define LL_HRPWM_Comm_ADC13TrigEvtSrcTypeDef           LL_HRPWM_Comm_ADCTrigEvtSrcTypeDef

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_NONE              (0)                     /*!< ADC1/3 Trigger Event Source None                   */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPA      BITLL(0)                /*!< ADC1/3 Trigger Event Source Master PWM Compare A   */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPB      BITLL(1)                /*!< ADC1/3 Trigger Event Source Master PWM Compare B   */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPC      BITLL(2)                /*!< ADC1/3 Trigger Event Source Master PWM Compare C   */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPD      BITLL(3)                /*!< ADC1/3 Trigger Event Source Master PWM Compare D   */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_PRD       BITLL(4)                /*!< ADC1/3 Trigger Event Source Master PWM Period      */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_5         BITLL(5)                /*!< ADC1/3 Trigger Event Source External Event 5       */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_6         BITLL(6)                /*!< ADC1/3 Trigger Event Source External Event 6       */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_7         BITLL(7)                /*!< ADC1/3 Trigger Event Source External Event 7       */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_8         BITLL(8)                /*!< ADC1/3 Trigger Event Source External Event 8       */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_9         BITLL(9)                /*!< ADC1/3 Trigger Event Source External Event 9       */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPB         BITLL(10)               /*!< ADC1/3 Trigger Event Source PWM0 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPD         BITLL(11)               /*!< ADC1/3 Trigger Event Source PWM0 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM0_PRD          BITLL(12)               /*!< ADC1/3 Trigger Event Source PWM0 Period            */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPB         BITLL(13)               /*!< ADC1/3 Trigger Event Source PWM1 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPD         BITLL(14)               /*!< ADC1/3 Trigger Event Source PWM1 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM1_PRD          BITLL(15)               /*!< ADC1/3 Trigger Event Source PWM1 Period            */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPB         BITLL(16)               /*!< ADC1/3 Trigger Event Source PWM2 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPD         BITLL(17)               /*!< ADC1/3 Trigger Event Source PWM2 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_PRD          BITLL(18)               /*!< ADC1/3 Trigger Event Source PWM2 Period            */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM2_RST_ROLLOVER BITLL(19)               /*!< ADC1/3 Trigger Event Source PWM2 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPB         BITLL(20)               /*!< ADC1/3 Trigger Event Source PWM3 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPD         BITLL(21)               /*!< ADC1/3 Trigger Event Source PWM3 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_PRD          BITLL(22)               /*!< ADC1/3 Trigger Event Source PWM3 Period            */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM3_RST_ROLLOVER BITLL(23)               /*!< ADC1/3 Trigger Event Source PWM3 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPB         BITLL(24)               /*!< ADC1/3 Trigger Event Source PWM4 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPC         BITLL(25)               /*!< ADC1/3 Trigger Event Source PWM4 Compare C         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPD         BITLL(26)               /*!< ADC1/3 Trigger Event Source PWM4 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM4_RST_ROLLOVER BITLL(27)               /*!< ADC1/3 Trigger Event Source PWM4 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPB         BITLL(28)               /*!< ADC1/3 Trigger Event Source PWM5 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPC         BITLL(29)               /*!< ADC1/3 Trigger Event Source PWM5 Compare C         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPD         BITLL(30)               /*!< ADC1/3 Trigger Event Source PWM5 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM5_PRD          ((uint64_t)BITLL(31))   /*!< ADC1/3 Trigger Event Source PWM5 Period            */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPB         ((uint64_t)BITLL(32))   /*!< ADC1/3 Trigger Event Source PWM6 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPD         ((uint64_t)BITLL(33))   /*!< ADC1/3 Trigger Event Source PWM6 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_PRD          ((uint64_t)BITLL(34))   /*!< ADC1/3 Trigger Event Source PWM6 Period            */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM6_RST_ROLLOVER ((uint64_t)BITLL(35))   /*!< ADC1/3 Trigger Event Source PWM6 Reset/Roll-Over   */

#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPB         ((uint64_t)BITLL(36))   /*!< ADC1/3 Trigger Event Source PWM7 Compare B         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPD         ((uint64_t)BITLL(37))   /*!< ADC1/3 Trigger Event Source PWM7 Compare D         */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_PRD          ((uint64_t)BITLL(38))   /*!< ADC1/3 Trigger Event Source PWM7 Period            */
#define LL_HRPWM_COMM_ADC13_TRIG_EVT_PWM7_RST_ROLLOVER ((uint64_t)BITLL(39))   /*!< ADC1/3 Trigger Event Source PWM7 Reset/Roll-Over   */


/**
  * @brief HRPWM Slave PWM Counter Reset Event Definition
  */
#define LL_HRPWM_Slv_CntrRstEvtTypeDef             uint64_t    
#define LL_HRPWM_SLV_CNTR_RST_EVT_ALL_MASK         (0x3FFFFFFFFFULL) 

#define LL_HRPWM_SLV_CNTR_RST_EVT_NONE             (0)                 /*!< Slave PWM Counter Reset Event None                    */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM5_CMPA        BITLL(0)            /*!< Slave PWM Counter Reset Event PWM5 Compare A          */

#define LL_HRPWM_SLV_CNTR_RST_EVT_MST_PWM_CMPA     BITLL(1)            /*!< Slave PWM Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV_CNTR_RST_EVT_MST_PWM_CMPB     BITLL(2)            /*!< Slave PWM Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV_CNTR_RST_EVT_MST_PWM_CMPC     BITLL(3)            /*!< Slave PWM Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV_CNTR_RST_EVT_MST_PWM_CMPD     BITLL(4)            /*!< Slave PWM Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV_CNTR_RST_EVT_MST_PWM_PRD      BITLL(5)            /*!< Slave PWM Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT0        BITLL(6)            /*!< Slave PWM Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT1        BITLL(7)            /*!< Slave PWM Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT2        BITLL(8)            /*!< Slave PWM Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT3        BITLL(9)            /*!< Slave PWM Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT4        BITLL(10)           /*!< Slave PWM Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT5        BITLL(11)           /*!< Slave PWM Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT6        BITLL(12)           /*!< Slave PWM Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT7        BITLL(13)           /*!< Slave PWM Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT8        BITLL(14)           /*!< Slave PWM Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_EVT9        BITLL(15)           /*!< Slave PWM Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWMx_UPD         BITLL(16)           /*!< Slave PWM Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM0_CMPB        BITLL(17)           /*!< Slave PWM Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM0_CMPD        BITLL(18)           /*!< Slave PWM Counter Reset Event PWM0 Compare D          */

#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM1_CMPA        BITLL(19)           /*!< Slave PWM Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM1_CMPB        BITLL(20)           /*!< Slave PWM Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM1_CMPD        BITLL(21)           /*!< Slave PWM Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM2_CMPA        BITLL(22)           /*!< Slave PWM Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM2_CMPB        BITLL(23)           /*!< Slave PWM Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM2_CMPD        BITLL(24)           /*!< Slave PWM Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM3_CMPA        BITLL(25)           /*!< Slave PWM Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM3_CMPB        BITLL(26)           /*!< Slave PWM Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM3_CMPD        BITLL(27)           /*!< Slave PWM Counter Reset Event PWM3 Compare D          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM4_CMPA        BITLL(28)           /*!< Slave PWM Counter Reset Event PWM4 Compare A          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM4_CMPB        BITLL(29)           /*!< Slave PWM Counter Reset Event PWM4 Compare B          */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM4_CMPD        BITLL(30)           /*!< Slave PWM Counter Reset Event PWM4 Compare D          */

#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM5_CMPB        ((uint64_t)(BITLL(31)))  /*!< Slave PWM Counter Reset Event PWM5 Compare B     */

#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM6_CMPA        ((uint64_t)(BITLL(32)))  /*!< Slave PWM Counter Reset Event PWM6 Compare A     */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM6_CMPB        ((uint64_t)(BITLL(33)))  /*!< Slave PWM Counter Reset Event PWM6 Compare B     */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM6_CMPD        ((uint64_t)(BITLL(34)))  /*!< Slave PWM Counter Reset Event PWM6 Compare D     */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM7_CMPA        ((uint64_t)(BITLL(35)))  /*!< Slave PWM Counter Reset Event PWM7 Compare A     */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM7_CMPB        ((uint64_t)(BITLL(36)))  /*!< Slave PWM Counter Reset Event PWM7 Compare B     */
#define LL_HRPWM_SLV_CNTR_RST_EVT_PWM7_CMPD        ((uint64_t)(BITLL(37)))  /*!< Slave PWM Counter Reset Event PWM7 Compare D     */


/**
  * @brief HRPWM Slave0 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv0_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV0_CNTR_RST_EVT_NONE            (0)                 /*!< Slave0 Counter Reset Event None                    */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave0 Counter Reset Event PWM5 Compare A          */

#define LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave0 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave0 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave0 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave0 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave0 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave0 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave0 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave0 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave0 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave0 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave0 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave0 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave0 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave0 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave0 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave0 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPB       BITLL(17)           /*!< Slave0 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPD       BITLL(18)           /*!< Slave0 Counter Reset Event PWM0 Compare D          */

#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPA       BITLL(19)           /*!< Slave0 Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPB       BITLL(20)           /*!< Slave0 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPD       BITLL(21)           /*!< Slave0 Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave0 Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave0 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPD       BITLL(24)           /*!< Slave0 Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPA       BITLL(25)           /*!< Slave0 Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPB       BITLL(26)           /*!< Slave0 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPD       BITLL(27)           /*!< Slave0 Counter Reset Event PWM3 Compare D          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave0 Counter Reset Event PWM4 Compare A          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave0 Counter Reset Event PWM4 Compare B          */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave0 Counter Reset Event PWM4 Compare D          */

#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave0 Counter Reset Event PWM5 Compare B     */

#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave0 Counter Reset Event PWM6 Compare A     */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave0 Counter Reset Event PWM6 Compare B     */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave0 Counter Reset Event PWM6 Compare D     */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave0 Counter Reset Event PWM7 Compare A     */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave0 Counter Reset Event PWM7 Compare B     */
#define LL_HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave0 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave1 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv1_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV1_CNTR_RST_EVT_NONE            (0)                 /*!< Slave1 Counter Reset Event None                    */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave1 Counter Reset Event PWM5 Compare A          */

#define LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave1 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave1 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave1 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave1 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave1 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave1 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave1 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave1 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave1 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave1 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave1 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave1 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave1 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave1 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave1 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave1 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPB       BITLL(17)           /*!< Slave1 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPD       BITLL(18)           /*!< Slave1 Counter Reset Event PWM1 Compare D          */

#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave1 Counter Reset Event PWM0 Compare A          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave1 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave1 Counter Reset Event PWM0 Compare D          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave1 Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave1 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPD       BITLL(24)           /*!< Slave1 Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPA       BITLL(25)           /*!< Slave1 Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPB       BITLL(26)           /*!< Slave1 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPD       BITLL(27)           /*!< Slave1 Counter Reset Event PWM3 Compare D          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave1 Counter Reset Event PWM4 Compare A          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave1 Counter Reset Event PWM4 Compare B          */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave1 Counter Reset Event PWM4 Compare D          */

#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave1 Counter Reset Event PWM5 Compare B      */

#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave1 Counter Reset Event PWM6 Compare A      */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave1 Counter Reset Event PWM6 Compare B      */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave1 Counter Reset Event PWM6 Compare D      */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave1 Counter Reset Event PWM7 Compare A      */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave1 Counter Reset Event PWM7 Compare B      */
#define LL_HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave1 Counter Reset Event PWM7 Compare D      */

/**
  * @brief HRPWM Slave2 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv2_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV2_CNTR_RST_EVT_NONE            (0)                 /*!< Slave2 Counter Reset Event None                    */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave2 Counter Reset Event PWM5 Compare A          */

#define LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave2 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave2 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave2 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave2 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave2 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave2 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave2 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave2 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave2 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave2 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave2 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave2 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave2 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave2 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave2 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave2 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPB       BITLL(17)           /*!< Slave2 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPD       BITLL(18)           /*!< Slave2 Counter Reset Event PWM2 Compare D          */

#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave2 Counter Reset Event PWM0 Compare A          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave2 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave2 Counter Reset Event PWM0 Compare D          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave2 Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave2 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave2 Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPA       BITLL(25)           /*!< Slave2 Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPB       BITLL(26)           /*!< Slave2 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPD       BITLL(27)           /*!< Slave2 Counter Reset Event PWM3 Compare D          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave2 Counter Reset Event PWM4 Compare A          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave2 Counter Reset Event PWM4 Compare B          */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave2 Counter Reset Event PWM4 Compare D          */

#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave2 Counter Reset Event PWM5 Compare B      */

#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave2 Counter Reset Event PWM6 Compare A      */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave2 Counter Reset Event PWM6 Compare B      */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave2 Counter Reset Event PWM6 Compare D      */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave2 Counter Reset Event PWM7 Compare A      */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave2 Counter Reset Event PWM7 Compare B      */
#define LL_HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave2 Counter Reset Event PWM7 Compare D      */

/**
  * @brief HRPWM Slave3 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv3_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV3_CNTR_RST_EVT_NONE            (0)                 /*!< Slave3 Counter Reset Event None                    */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave3 Counter Reset Event PWM5 Compare A          */

#define LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave3 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave3 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave3 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave3 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave3 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave3 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave3 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave3 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave3 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave3 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave3 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave3 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave3 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave3 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave3 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave3 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPB       BITLL(17)           /*!< Slave3 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPD       BITLL(18)           /*!< Slave3 Counter Reset Event PWM3 Compare D          */

#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave3 Counter Reset Event PWM0 Compare A          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave3 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave3 Counter Reset Event PWM0 Compare D          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave3 Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave3 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave3 Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave3 Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave3 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave3 Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave3 Counter Reset Event PWM4 Compare A          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave3 Counter Reset Event PWM4 Compare B          */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave3 Counter Reset Event PWM4 Compare D          */

#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave3 Counter Reset Event PWM5 Compare B      */

#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave3 Counter Reset Event PWM6 Compare A      */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave3 Counter Reset Event PWM6 Compare B      */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave3 Counter Reset Event PWM6 Compare D      */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave3 Counter Reset Event PWM7 Compare A      */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave3 Counter Reset Event PWM7 Compare B      */
#define LL_HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave3 Counter Reset Event PWM7 Compare D      */

/**
  * @brief HRPWM Slave4 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv4_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV4_CNTR_RST_EVT_NONE            (0)                 /*!< Slave4 Counter Reset Event None                    */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave4 Counter Reset Event PWM5 Compare A          */

#define LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave4 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave4 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave4 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave4 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave4 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave4 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave4 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave4 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave4 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave4 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave4 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave4 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave4 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave4 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave4 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave4 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPB       BITLL(17)           /*!< Slave4 Counter Reset Event PWM4 Compare B          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPD       BITLL(18)           /*!< Slave4 Counter Reset Event PWM4 Compare D          */

#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave4 Counter Reset Event PWM0 Compare A          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave4 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave4 Counter Reset Event PWM0 Compare D          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave4 Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave4 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave4 Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave4 Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave4 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave4 Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave4 Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave4 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave4 Counter Reset Event PWM3 Compare D          */

#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave4 Counter Reset Event PWM5 Compare B     */

#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave4 Counter Reset Event PWM6 Compare A     */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave4 Counter Reset Event PWM6 Compare B     */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave4 Counter Reset Event PWM6 Compare D     */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave4 Counter Reset Event PWM7 Compare A     */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave4 Counter Reset Event PWM7 Compare B     */
#define LL_HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave4 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave5 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv5_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV5_CNTR_RST_EVT_NONE            (0)                 /*!< Slave5 Counter Reset Event None                    */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPA       BITLL(0)            /*!< Slave5 Counter Reset Event PWM4 Compare A          */

#define LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave5 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave5 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave5 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave5 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave5 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave5 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave5 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave5 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave5 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave5 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave5 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave5 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave5 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave5 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave5 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave5 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPB       BITLL(17)           /*!< Slave5 Counter Reset Event PWM5 Compare B          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPD       BITLL(18)           /*!< Slave5 Counter Reset Event PWM5 Compare D          */

#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave5 Counter Reset Event PWM0 Compare A          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave5 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave5 Counter Reset Event PWM0 Compare D          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave5 Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave5 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave5 Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave5 Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave5 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave5 Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave5 Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave5 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave5 Counter Reset Event PWM3 Compare D          */

#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave5 Counter Reset Event PWM4 Compare B     */

#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave5 Counter Reset Event PWM6 Compare A     */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave5 Counter Reset Event PWM6 Compare B     */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave5 Counter Reset Event PWM6 Compare D     */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave5 Counter Reset Event PWM7 Compare A     */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave5 Counter Reset Event PWM7 Compare B     */
#define LL_HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave5 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave6 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv6_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV6_CNTR_RST_EVT_NONE            (0)                 /*!< Slave6 Counter Reset Event None                    */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPA       BITLL(0)            /*!< Slave6 Counter Reset Event PWM4 Compare A          */

#define LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave6 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave6 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave6 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave6 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave6 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave6 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave6 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave6 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave6 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave6 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave6 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave6 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave6 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave6 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave6 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave6 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPB       BITLL(17)           /*!< Slave6 Counter Reset Event PWM6 Compare B          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPD       BITLL(18)           /*!< Slave6 Counter Reset Event PWM6 Compare D          */

#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave6 Counter Reset Event PWM0 Compare A          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave6 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave6 Counter Reset Event PWM0 Compare D          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave6 Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave6 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave6 Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave6 Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave6 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave6 Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave6 Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave6 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave6 Counter Reset Event PWM3 Compare D          */

#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave6 Counter Reset Event PWM4 Compare B     */

#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave6 Counter Reset Event PWM5 Compare A     */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave6 Counter Reset Event PWM5 Compare B     */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave6 Counter Reset Event PWM5 Compare D     */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave6 Counter Reset Event PWM7 Compare A     */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave6 Counter Reset Event PWM7 Compare B     */
#define LL_HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave6 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave7 Counter Reset Event Definition
  */
#define LL_HRPWM_Slv7_CntrRstEvtTypeDef            LL_HRPWM_Slv_CntrRstEvtTypeDef

#define LL_HRPWM_SLV7_CNTR_RST_EVT_NONE            (0)                 /*!< Slave7 Counter Reset Event None                    */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPA       BITLL(0)            /*!< Slave7 Counter Reset Event PWM4 Compare A          */

#define LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave7 Counter Reset Event Master PWM Compare A    */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave7 Counter Reset Event Master PWM Compare B    */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave7 Counter Reset Event Master PWM Compare C    */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave7 Counter Reset Event Master PWM Compare D    */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave7 Counter Reset Event Master PWM Period       */

#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave7 Counter Reset Event PWMx Event 0            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave7 Counter Reset Event PWMx Event 1            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave7 Counter Reset Event PWMx Event 2            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave7 Counter Reset Event PWMx Event 3            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave7 Counter Reset Event PWMx Event 4            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave7 Counter Reset Event PWMx Event 5            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave7 Counter Reset Event PWMx Event 6            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave7 Counter Reset Event PWMx Event 7            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave7 Counter Reset Event PWMx Event 8            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave7 Counter Reset Event PWMx Event 9            */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave7 Counter Reset Event PWMx Update             */

#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPB       BITLL(17)           /*!< Slave7 Counter Reset Event PWM7 Compare B          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPD       BITLL(18)           /*!< Slave7 Counter Reset Event PWM7 Compare D          */

#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave7 Counter Reset Event PWM0 Compare A          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave7 Counter Reset Event PWM0 Compare B          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave7 Counter Reset Event PWM0 Compare D          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave7 Counter Reset Event PWM1 Compare A          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave7 Counter Reset Event PWM1 Compare B          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave7 Counter Reset Event PWM1 Compare D          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave7 Counter Reset Event PWM2 Compare A          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave7 Counter Reset Event PWM2 Compare B          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave7 Counter Reset Event PWM2 Compare D          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave7 Counter Reset Event PWM3 Compare A          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave7 Counter Reset Event PWM3 Compare B          */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave7 Counter Reset Event PWM3 Compare D          */

#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave7 Counter Reset Event PWM4 Compare B      */

#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave7 Counter Reset Event PWM5 Compare A      */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave7 Counter Reset Event PWM5 Compare B      */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave7 Counter Reset Event PWM5 Compare D      */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave7 Counter Reset Event PWM6 Compare A      */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave7 Counter Reset Event PWM6 Compare B      */
#define LL_HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave7 Counter Reset Event PWM6 Compare D      */


/**
  * @brief HRPWM Slave Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv_CapTrigEvtTypeDef             uint64_t    
#define LL_HRPWM_SLV_CAP_TRIG_EVT_ALL_MASK         (0xFFFFFFFFFFULL) 

#define LL_HRPWM_SLV_CAP_TRIG_EVT_NONE             (0)                 /*!< Slave PWM Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_SW_CAP           BITLL(0)            /*!< Slave PWM Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_UPD         BITLL(1)            /*!< Slave PWM Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT0        BITLL(2)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT1        BITLL(3)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT2        BITLL(4)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT3        BITLL(5)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT4        BITLL(6)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT5        BITLL(7)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT6        BITLL(8)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT7        BITLL(9)            /*!< Slave PWM Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT8        BITLL(10)           /*!< Slave PWM Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWMx_EVT9        BITLL(11)           /*!< Slave PWM Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM1_OUTA_SET    BITLL(12)           /*!< Slave PWM Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM1_OUTA_CLR    BITLL(13)           /*!< Slave PWM Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM1_CMPA        BITLL(14)           /*!< Slave PWM Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM1_CMPB        BITLL(15)           /*!< Slave PWM Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM2_OUTA_SET    BITLL(16)           /*!< Slave PWM Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM2_OUTA_CLR    BITLL(17)           /*!< Slave PWM Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM2_CMPA        BITLL(18)           /*!< Slave PWM Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM2_CMPB        BITLL(19)           /*!< Slave PWM Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM3_OUTA_SET    BITLL(20)           /*!< Slave PWM Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM3_OUTA_CLR    BITLL(21)           /*!< Slave PWM Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM3_CMPA        BITLL(22)           /*!< Slave PWM Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM3_CMPB        BITLL(23)           /*!< Slave PWM Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM4_OUTA_SET    BITLL(24)           /*!< Slave PWM Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM4_OUTA_CLR    BITLL(25)           /*!< Slave PWM Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM4_CMPA        BITLL(26)           /*!< Slave PWM Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM4_CMPB        BITLL(27)           /*!< Slave PWM Capture A/B Trigger Event PWM4 Compare B    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM5_OUTA_SET    BITLL(28)           /*!< Slave PWM Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM5_OUTA_CLR    BITLL(29)           /*!< Slave PWM Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM5_CMPA        BITLL(30)           /*!< Slave PWM Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM5_CMPB        ((uint64_t)(BITLL(31)))  /*!< Slave PWM Capture A/B Trigger Event PWM5 Compare B   */

#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM6_OUTA_SET    ((uint64_t)(BITLL(32)))  /*!< Slave PWM Capture A/B Trigger Event PWM6 OutA Set    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM6_OUTA_CLR    ((uint64_t)(BITLL(33)))  /*!< Slave PWM Capture A/B Trigger Event PWM6 OutA Clear  */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM6_CMPA        ((uint64_t)(BITLL(34)))  /*!< Slave PWM Capture A/B Trigger Event PWM6 Compare A   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM6_CMPB        ((uint64_t)(BITLL(35)))  /*!< Slave PWM Capture A/B Trigger Event PWM6 Compare B   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM7_OUTA_SET    ((uint64_t)(BITLL(36)))  /*!< Slave PWM Capture A/B Trigger Event PWM7 OutA Set    */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM7_OUTA_CLR    ((uint64_t)(BITLL(37)))  /*!< Slave PWM Capture A/B Trigger Event PWM7 OutA Clear  */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM7_CMPA        ((uint64_t)(BITLL(38)))  /*!< Slave PWM Capture A/B Trigger Event PWM7 Compare A   */
#define LL_HRPWM_SLV_CAP_TRIG_EVT_PWM7_CMPB        ((uint64_t)(BITLL(39)))  /*!< Slave PWM Capture A/B Trigger Event PWM7 Compare B   */


/**
  * @brief HRPWM Slave0 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv0_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV0_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave0 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave0 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave0 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave0 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave0 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(12)           /*!< Slave0 Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(13)           /*!< Slave0 Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPA       BITLL(14)           /*!< Slave0 Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPB       BITLL(15)           /*!< Slave0 Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(16)           /*!< Slave0 Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(17)           /*!< Slave0 Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPA       BITLL(18)           /*!< Slave0 Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPB       BITLL(19)           /*!< Slave0 Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(20)           /*!< Slave0 Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(21)           /*!< Slave0 Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPA       BITLL(22)           /*!< Slave0 Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPB       BITLL(23)           /*!< Slave0 Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave0 Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave0 Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave0 Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave0 Capture A/B Trigger Event PWM4 Compare B    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave0 Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave0 Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave0 Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave0 Capture A/B Trigger Event PWM5 Compare B   */

#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32)))  /*!< Slave0 Capture A/B Trigger Event PWM6 OutA Set    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33)))  /*!< Slave0 Capture A/B Trigger Event PWM6 OutA Clear  */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34)))  /*!< Slave0 Capture A/B Trigger Event PWM6 Compare A   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35)))  /*!< Slave0 Capture A/B Trigger Event PWM6 Compare B   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36)))  /*!< Slave0 Capture A/B Trigger Event PWM7 OutA Set    */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37)))  /*!< Slave0 Capture A/B Trigger Event PWM7 OutA Clear  */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38)))  /*!< Slave0 Capture A/B Trigger Event PWM7 Compare A   */
#define LL_HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39)))  /*!< Slave0 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave1 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv1_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV1_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave1 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave1 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave1 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave1 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave1 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave1 Capture A/B Trigger Event PWM0 OutA Set     */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave1 Capture A/B Trigger Event PWM0 OutA Clear   */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave1 Capture A/B Trigger Event PWM0 Compare A    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave1 Capture A/B Trigger Event PWM0 Compare B    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(16)           /*!< Slave1 Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(17)           /*!< Slave1 Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPA       BITLL(18)           /*!< Slave1 Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPB       BITLL(19)           /*!< Slave1 Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(20)           /*!< Slave1 Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(21)           /*!< Slave1 Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPA       BITLL(22)           /*!< Slave1 Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPB       BITLL(23)           /*!< Slave1 Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave1 Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave1 Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave1 Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave1 Capture A/B Trigger Event PWM4 Compare B    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave1 Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave1 Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave1 Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave1 Capture A/B Trigger Event PWM5 Compare B    */

#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave1 Capture A/B Trigger Event PWM6 OutA Set     */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave1 Capture A/B Trigger Event PWM6 OutA Clear   */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave1 Capture A/B Trigger Event PWM6 Compare A    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave1 Capture A/B Trigger Event PWM6 Compare B    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave1 Capture A/B Trigger Event PWM7 OutA Set     */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave1 Capture A/B Trigger Event PWM7 OutA Clear   */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave1 Capture A/B Trigger Event PWM7 Compare A    */
#define LL_HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave1 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave2 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv2_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV2_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave2 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave2 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave2 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave2 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave2 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave2 Capture A/B Trigger Event PWM0 OutA Set     */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave2 Capture A/B Trigger Event PWM0 OutA Clear   */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave2 Capture A/B Trigger Event PWM0 Compare A    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave2 Capture A/B Trigger Event PWM0 Compare B    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave2 Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave2 Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave2 Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave2 Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(20)           /*!< Slave2 Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(21)           /*!< Slave2 Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPA       BITLL(22)           /*!< Slave2 Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPB       BITLL(23)           /*!< Slave2 Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave2 Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave2 Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave2 Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave2 Capture A/B Trigger Event PWM4 Compare B    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave2 Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave2 Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave2 Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave2 Capture A/B Trigger Event PWM5 Compare B    */

#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave2 Capture A/B Trigger Event PWM6 OutA Set     */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave2 Capture A/B Trigger Event PWM6 OutA Clear   */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave2 Capture A/B Trigger Event PWM6 Compare A    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave2 Capture A/B Trigger Event PWM6 Compare B    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave2 Capture A/B Trigger Event PWM7 OutA Set     */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave2 Capture A/B Trigger Event PWM7 OutA Clear   */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave2 Capture A/B Trigger Event PWM7 Compare A    */
#define LL_HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave2 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave3 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv3_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV3_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave3 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave3 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave3 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave3 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave3 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave3 Capture A/B Trigger Event PWM0 OutA Set     */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave3 Capture A/B Trigger Event PWM0 OutA Clear   */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave3 Capture A/B Trigger Event PWM0 Compare A    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave3 Capture A/B Trigger Event PWM0 Compare B    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave3 Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave3 Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave3 Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave3 Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave3 Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave3 Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave3 Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave3 Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave3 Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave3 Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave3 Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave3 Capture A/B Trigger Event PWM4 Compare B    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave3 Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave3 Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave3 Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave3 Capture A/B Trigger Event PWM5 Compare B    */

#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave3 Capture A/B Trigger Event PWM6 OutA Set     */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave3 Capture A/B Trigger Event PWM6 OutA Clear   */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave3 Capture A/B Trigger Event PWM6 Compare A    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave3 Capture A/B Trigger Event PWM6 Compare B    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave3 Capture A/B Trigger Event PWM7 OutA Set     */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave3 Capture A/B Trigger Event PWM7 OutA Clear   */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave3 Capture A/B Trigger Event PWM7 Compare A    */
#define LL_HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave3 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave4 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv4_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV4_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave4 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave4 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave4 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave4 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave4 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave4 Capture A/B Trigger Event PWM0 OutA Set     */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave4 Capture A/B Trigger Event PWM0 OutA Clear   */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave4 Capture A/B Trigger Event PWM0 Compare A    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave4 Capture A/B Trigger Event PWM0 Compare B    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave4 Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave4 Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave4 Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave4 Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave4 Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave4 Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave4 Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave4 Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave4 Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave4 Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave4 Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave4 Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave4 Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave4 Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave4 Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave4 Capture A/B Trigger Event PWM5 Compare B    */

#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave4 Capture A/B Trigger Event PWM6 OutA Set     */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave4 Capture A/B Trigger Event PWM6 OutA Clear   */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave4 Capture A/B Trigger Event PWM6 Compare A    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave4 Capture A/B Trigger Event PWM6 Compare B    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave4 Capture A/B Trigger Event PWM7 OutA Set     */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave4 Capture A/B Trigger Event PWM7 OutA Clear   */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave4 Capture A/B Trigger Event PWM7 Compare A    */
#define LL_HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave4 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave5 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv5_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV5_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave5 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave5 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave5 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave5 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave5 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave5 Capture A/B Trigger Event PWM0 OutA Set     */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave5 Capture A/B Trigger Event PWM0 OutA Clear   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave5 Capture A/B Trigger Event PWM0 Compare A    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave5 Capture A/B Trigger Event PWM0 Compare B    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave5 Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave5 Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave5 Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave5 Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave5 Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave5 Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave5 Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave5 Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave5 Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave5 Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave5 Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave5 Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(28)           /*!< Slave5 Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(29)           /*!< Slave5 Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPA       BITLL(30)           /*!< Slave5 Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave5 Capture A/B Trigger Event PWM4 Compare B    */

#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32)))  /*!< Slave5 Capture A/B Trigger Event PWM6 OutA Set    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33)))  /*!< Slave5 Capture A/B Trigger Event PWM6 OutA Clear  */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34)))  /*!< Slave5 Capture A/B Trigger Event PWM6 Compare A   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35)))  /*!< Slave5 Capture A/B Trigger Event PWM6 Compare B   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36)))  /*!< Slave5 Capture A/B Trigger Event PWM7 OutA Set    */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37)))  /*!< Slave5 Capture A/B Trigger Event PWM7 OutA Clear  */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38)))  /*!< Slave5 Capture A/B Trigger Event PWM7 Compare A   */
#define LL_HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39)))  /*!< Slave5 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave6 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv6_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV6_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave6 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave6 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave6 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave6 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave6 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave6 Capture A/B Trigger Event PWM0 OutA Set     */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave6 Capture A/B Trigger Event PWM0 OutA Clear   */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave6 Capture A/B Trigger Event PWM0 Compare A    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave6 Capture A/B Trigger Event PWM0 Compare B    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave6 Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave6 Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave6 Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave6 Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave6 Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave6 Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave6 Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave6 Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave6 Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave6 Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave6 Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave6 Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(28)           /*!< Slave6 Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(29)           /*!< Slave6 Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPA       BITLL(30)           /*!< Slave6 Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave6 Capture A/B Trigger Event PWM4 Compare B    */

#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave6 Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave6 Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave6 Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave6 Capture A/B Trigger Event PWM5 Compare B    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave6 Capture A/B Trigger Event PWM7 OutA Set     */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave6 Capture A/B Trigger Event PWM7 OutA Clear   */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave6 Capture A/B Trigger Event PWM7 Compare A    */
#define LL_HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave6 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave7 Capture A/B Trigger Event Definition
  */
#define LL_HRPWM_Slv7_CapTrigEvtTypeDef            LL_HRPWM_Slv_CapTrigEvtTypeDef

#define LL_HRPWM_SLV7_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave7 Capture A/B Trigger Event None              */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave7 Capture A/B Trigger Event Software Capture  */

#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave7 Capture A/B Trigger Event PWMx Update       */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 0      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 1      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 2      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 3      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 4      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 5      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 6      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 7      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave7 Capture A/B Trigger Event PWMx Event 8      */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave7 Capture A/B Trigger Event PWMx Event 9      */

#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave7 Capture A/B Trigger Event PWM0 OutA Set     */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave7 Capture A/B Trigger Event PWM0 OutA Clear   */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave7 Capture A/B Trigger Event PWM0 Compare A    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave7 Capture A/B Trigger Event PWM0 Compare B    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave7 Capture A/B Trigger Event PWM1 OutA Set     */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave7 Capture A/B Trigger Event PWM1 OutA Clear   */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave7 Capture A/B Trigger Event PWM1 Compare A    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave7 Capture A/B Trigger Event PWM1 Compare B    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave7 Capture A/B Trigger Event PWM2 OutA Set     */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave7 Capture A/B Trigger Event PWM2 OutA Clear   */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave7 Capture A/B Trigger Event PWM2 Compare A    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave7 Capture A/B Trigger Event PWM2 Compare B    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave7 Capture A/B Trigger Event PWM3 OutA Set     */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave7 Capture A/B Trigger Event PWM3 OutA Clear   */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave7 Capture A/B Trigger Event PWM3 Compare A    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave7 Capture A/B Trigger Event PWM3 Compare B    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(28)           /*!< Slave7 Capture A/B Trigger Event PWM4 OutA Set     */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(29)           /*!< Slave7 Capture A/B Trigger Event PWM4 OutA Clear   */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPA       BITLL(30)           /*!< Slave7 Capture A/B Trigger Event PWM4 Compare A    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31)))/*!< Slave7 Capture A/B Trigger Event PWM4 Compare B     */

#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave7 Capture A/B Trigger Event PWM5 OutA Set     */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave7 Capture A/B Trigger Event PWM5 OutA Clear   */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave7 Capture A/B Trigger Event PWM5 Compare A    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave7 Capture A/B Trigger Event PWM5 Compare B    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave7 Capture A/B Trigger Event PWM6 OutA Set     */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave7 Capture A/B Trigger Event PWM6 OutA Clear   */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave7 Capture A/B Trigger Event PWM6 Compare A    */
#define LL_HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave7 Capture A/B Trigger Event PWM6 Compare B    */


/**
  * @brief HRPWM Common Burst Mode Trigger Event Definition
  */
#define LL_HRPWM_Comm_BurstTrigEvtTypeDef                  uint64_t

#define LL_HRPWM_COMM_BURST_TRIG_EVT_NONE                  (0)         /*!< Common Burst Mode Trigger Event None                       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_SW                    BITLL(0)    /*!< Common Burst Mode Trigger Event Software                   */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_RST_ROLLOVER  BITLL(1)    /*!< Common Burst Mode Trigger Event Master PWM Reset Roll-Over */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_REP           BITLL(2)    /*!< Common Burst Mode Trigger Event Master PWM Repetition      */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPA          BITLL(3)    /*!< Common Burst Mode Trigger Event Master PWM Compare A       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPB          BITLL(4)    /*!< Common Burst Mode Trigger Event Master PWM Compare B       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPC          BITLL(5)    /*!< Common Burst Mode Trigger Event Master PWM Compare C       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPD          BITLL(6)    /*!< Common Burst Mode Trigger Event Master PWM Compare D       */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_RST_ROLLOVER     BITLL(7)    /*!< Common Burst Mode Trigger Event PWM0 Reset Roll-Over       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_REP              BITLL(8)    /*!< Common Burst Mode Trigger Event PWM0 Repetition            */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_CMPA             BITLL(9)    /*!< Common Burst Mode Trigger Event PWM0 Compare A             */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_CMPB             BITLL(10)   /*!< Common Burst Mode Trigger Event PWM0 Compare B             */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_RST_ROLLOVER     BITLL(11)   /*!< Common Burst Mode Trigger Event PWM1 Reset Roll-Over       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_REP              BITLL(12)   /*!< Common Burst Mode Trigger Event PWM1 Repetition            */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_CMPA             BITLL(13)   /*!< Common Burst Mode Trigger Event PWM1 Compare A             */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM1_CMPB             BITLL(14)   /*!< Common Burst Mode Trigger Event PWM1 Compare B             */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM2_RST_ROLLOVER     BITLL(15)   /*!< Common Burst Mode Trigger Event PWM2 Reset Roll-Over       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM2_REP              BITLL(16)   /*!< Common Burst Mode Trigger Event PWM2 Repetition            */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM2_CMPA             BITLL(17)   /*!< Common Burst Mode Trigger Event PWM2 Compare A             */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM3_RST_ROLLOVER     BITLL(18)   /*!< Common Burst Mode Trigger Event PWM3 Reset Roll-Over       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM3_REP              BITLL(19)   /*!< Common Burst Mode Trigger Event PWM3 Repetition            */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM3_CMPB             BITLL(20)   /*!< Common Burst Mode Trigger Event PWM3 Compare B             */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_REP              BITLL(21)   /*!< Common Burst Mode Trigger Event PWM4 Repetition            */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_CMPA             BITLL(22)   /*!< Common Burst Mode Trigger Event PWM4 Compare A             */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_CMPB             BITLL(23)   /*!< Common Burst Mode Trigger Event PWM4 Compare B             */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM5_RST_ROLLOVER     BITLL(24)   /*!< Common Burst Mode Trigger Event PWM5 Reset Roll-Over       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM5_REP              BITLL(25)   /*!< Common Burst Mode Trigger Event PWM5 Repetition            */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM5_CMPA             BITLL(26)   /*!< Common Burst Mode Trigger Event PWM5 Compare A             */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_PRD_EVT7         BITLL(27)   /*!< Common Burst Mode Trigger Event PWM0 Event 7 after Period  */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_PRD_EVT8         BITLL(28)   /*!< Common Burst Mode Trigger Event PWM4 Event 8 after Period  */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM0_EVT7             BITLL(29)   /*!< Common Burst Mode Trigger Event PWM0 Event 7               */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM4_EVT8             BITLL(30)   /*!< Common Burst Mode Trigger Event PWM4 Event 8               */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM_BM_IN2            ((uint64_t)(BITLL(31)))  /*!< Common Burst Mode Trigger Event hrpwm_bm_in2          */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_RST_ROLLOVER     ((uint64_t)(BITLL(32))) /*!< Common Burst Mode Trigger Event PWM6 Reset Roll-Over   */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_REP              ((uint64_t)(BITLL(33)))  /*!< Common Burst Mode Trigger Event PWM6 Repetition       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_CMPA             ((uint64_t)(BITLL(34)))  /*!< Common Burst Mode Trigger Event PWM6 Compare A        */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM6_CMPB             ((uint64_t)(BITLL(35)))  /*!< Common Burst Mode Trigger Event PWM6 Compare B        */

#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_RST_ROLLOVER     ((uint64_t)(BITLL(36))) /*!< Common Burst Mode Trigger Event PWM7 Reset Roll-Over   */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_REP              ((uint64_t)(BITLL(37)))  /*!< Common Burst Mode Trigger Event PWM7 Repetition       */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_CMPA             ((uint64_t)(BITLL(38)))  /*!< Common Burst Mode Trigger Event PWM7 Compare A        */
#define LL_HRPWM_COMM_BURST_TRIG_EVT_PWM7_CMPB             ((uint64_t)(BITLL(39)))  /*!< Common Burst Mode Trigger Event PWM7 Compare B        */
/**
  * @}
  */ /* HRPWM_LL_EC_Configuration */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Macros HRPWM LL Exported Macros
  * @brief    HRPWM LL Exported Macros
  * @{
  */



/**
  * @brief  HRPWM 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define LL_HRPWM_REG_OFFSET(__REG__, offset) \
        (*((volatile uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))


/**
  * @}
  */ /* HRPWM_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Functions HRPWM LL Functions
  * @brief    HRPWM LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_HRPWM_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_HRPWM_ASSERT_INLINE_PARAM == 1)
extern void LL_HRPWM_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_HRPWM_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_HRPWM_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_HRPWM_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup HRPWM_LL_EF_Configuration LL HRPWM Configuration
  * @brief    LL HRPWM Configuration
  * @{
  */

/**
  * @brief  Master PWM Update Gate Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Gate Master PWM Update Gate @ref LL_HRPWM_Mst_UpdGateTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetUpdateGating(HRPWM_TypeDef *HRPWMx, uint32_t Gate)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_BRSTDMA_Msk, (((Gate) & HRPWM_MST_MCR0_BRSTDMA_Val) << HRPWM_MST_MCR0_BRSTDMA_Pos));
}

/**
  * @brief  Master PWM Repetition Trigger PWM Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableRepetitionUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_MREPU_Msk);
}

/**
  * @brief  Master PWM Repetition Trigger PWM Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableRepetitionUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_MREPU_Msk);
}

/**
  * @brief  Master PWM Reset/RollOver Trigger PWM Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableResetRollOverUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_MRSTU_Msk);
}

/**
  * @brief  Master PWM Reset/RollOver Trigger PWM Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableResetRollOverUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_MRSTU_Msk);
}

/**
  * @brief  Master Preload Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePreload(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_PREEN_Msk);
}

/**
  * @brief  Master Preload Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePreload(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_PREEN_Msk);
}

/**
  * @brief  Master DAC Trigger Sync Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src Master DAC Trigger Sync Source @ref LL_HRPWM_DACSyncSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetDACSyncSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_DACSYNC_Msk, (((Src) & HRPWM_MST_MCR0_DACSYNC_Val) << HRPWM_MST_MCR0_DACSYNC_Pos));
}

/**
  * @brief  Master Sync Event Output Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src Master Sync Event Output Source @ref LL_HRPWM_Mst_SyncOutSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetSyncOutSrc(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTSRC_Msk, (((Src) & HRPWM_MST_MCR0_SYNCOUTSRC_Val) << HRPWM_MST_MCR0_SYNCOUTSRC_Pos));
}

/**
  * @brief  Master Sync Event Output Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableSyncOutput(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTEN_Msk);
}

/**
  * @brief  Master Sync Event Output Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableSyncOutput(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTEN_Msk);
}

/**
  * @brief  Master Sync Event Output Polarity Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pol Master Sync Event Output Polarity @ref LL_HRPWM_Mst_SyncOutPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetSyncOutConfig(HRPWM_TypeDef *HRPWMx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTPOL_Msk, (((Pol) & HRPWM_MST_MCR0_SYNCOUTPOL_Val) << HRPWM_MST_MCR0_SYNCOUTPOL_Pos));
}

/**
  * @brief  Master Sync Event Start Master PWM Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableStartOnSync(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCSTRTM_Msk);
}

/**
  * @brief  Master Sync Event Start Master PWM Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableStartOnSync(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCSTRTM_Msk);
}

/**
  * @brief  Master Sync Event Reset Master PWM Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableResetOnSync(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCRSTM_Msk);
}

/**
  * @brief  Master Sync Event Reset Master PWM Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableResetOnSync(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCRSTM_Msk);
}

/**
  * @brief  Master Sync Event Input Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableSyncInput(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCINEN_Msk);
}

/**
  * @brief  Master Sync Event Input Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableSyncInput(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCINEN_Msk);
}

/**
  * @brief  Master Sync Event Input Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src Master Sync Event Input Source
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetSyncInSrc(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_SYNCINSRC_Msk, 
            (((Src) & HRPWM_MST_MCR0_SYNCINSRC_Val) << HRPWM_MST_MCR0_SYNCINSRC_Pos));
}

/**
  * @brief  Master PWM Interleaved Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mode Master PWM Interleaved Mode @ref LL_HRPWM_IntlvdModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetInterleavedMode(HRPWM_TypeDef *HRPWMx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_INTLVD_Msk, 
            (((Mode) & HRPWM_MST_MCR0_INTLVD_Val) << HRPWM_MST_MCR0_INTLVD_Pos));
}

/**
  * @brief  Master PWM Half Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableHalfMode(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_HALF_Msk);
}

/**
  * @brief  Master PWM Half Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableHalfMode(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_HALF_Msk);
}

/**
  * @brief  Master PWM Repeat Trigger Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableRetriggerMode(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_RETRIG_Msk);
}

/**
  * @brief  Master PWM Repeat Trigger Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableRetriggerMode(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_RETRIG_Msk);
}

/**
  * @brief  Master PWM Work Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mode Master PWM Work Mode @ref LL_HRPWM_WorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetCounterMode(HRPWM_TypeDef *HRPWMx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_CONT_Msk, 
            (((Mode) & HRPWM_MST_MCR0_CONT_Val) << HRPWM_MST_MCR0_CONT_Pos));
}

/**
  * @brief  Master PWM Clock Division Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Div Master PWM Clock Division @ref LL_HRPWM_ClkPresclTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetPrescaler(HRPWM_TypeDef *HRPWMx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_CKPSC_Msk, 
            (((Div) & HRPWM_MST_MCR0_CKPSC_Val) << HRPWM_MST_MCR0_CKPSC_Pos));
}

/**
  * @brief  Master PWM Burst DMA Disable Assert
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_AssertBurstDMADisable(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_BDMADIS_Msk);
}

/**
  * @brief  Master PWM Burst DMA Disable Release
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ReleaseBurstDMADisable(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_BDMADIS_Msk);
}

/**
  * @brief  Master PWM Burst DMA Disable Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0: Master PWM Burst DMA Disable Release
  * @retval 1: Master PWM Burst DMA Disable Assert
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsBurstDMADisableAsserted(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_BDMADIS_Msk, HRPWM_MST_MCR1_BDMADIS_Pos));
}

/**
  * @brief  Master PWM7 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM7(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN7_Msk);
}

/**
  * @brief  Master PWM7 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM7(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN7_Msk);
}

/**
  * @brief  Master PWM6 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM6(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN6_Msk);
}

/**
  * @brief  Master PWM6 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM6(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN6_Msk);
}

/**
  * @brief  Master PWM5 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM5(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN5_Msk);
}

/**
  * @brief  Master PWM5 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM5(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN5_Msk);
}

/**
  * @brief  Master PWM4 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM4(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN4_Msk);
}

/**
  * @brief  Master PWM4 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM4(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN4_Msk);
}

/**
  * @brief  Master PWM3 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM3(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN3_Msk);
}

/**
  * @brief  Master PWM3 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM3(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN3_Msk);
}

/**
  * @brief  Master PWM2 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM2(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN2_Msk);
}

/**
  * @brief  Master PWM2 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM2(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN2_Msk);
}

/**
  * @brief  Master PWM1 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM1(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN1_Msk);
}

/**
  * @brief  Master PWM1 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM1(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN1_Msk);
}

/**
  * @brief  Master PWM0 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWM0(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN0_Msk);
}

/**
  * @brief  Master PWM0 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWM0(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN0_Msk);
}

/**
  * @brief  Master PWMx Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePWMx(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_MST_MCR1_CEN0_Pos));
}

/**
  * @brief  Master PWMx Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePWMx(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_MST_MCR1_CEN0_Pos));
}

/**
  * @brief  Master PWM Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableMasterPWM(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_MCEN_Msk);
}

/**
  * @brief  Master PWM Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableMasterPWM(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_MCEN_Msk);
}

/**
  * @brief  Master Multi PWM Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_CounterEnable(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MCR1, ((Pwmxs) & LL_HRPWM_ALL_PWM_MASK) << HRPWM_MST_MCR1_MCEN_Pos);
}

/**
  * @brief  Master Multi PWM Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_CounterDisable(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MCR1, ((Pwmxs) & LL_HRPWM_ALL_PWM_MASK) << HRPWM_MST_MCR1_MCEN_Pos);
}

/**
  * @brief  Judge is Master Repetition Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Repetition Interrupt Pending
  * @retval 1 is Master Repetition Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MREP(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MREP_Msk, HRPWM_MST_MISR_MREP_Pos));
}

/**
  * @brief  Master Repetition Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MREP(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MREP_Msk);
}

/**
  * @brief  Judge is Master Reset Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Reset Interrupt Pending
  * @retval 1 is Master Reset Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MRST(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MRST_Msk, HRPWM_MST_MISR_MRST_Pos));
}

/**
  * @brief  Master Reset Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MRST(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MRST_Msk);
}

/**
  * @brief  Judge is Master Update Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Update Interrupt Pending
  * @retval 1 is Master Update Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MUPD(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MUPD_Msk, HRPWM_MST_MISR_MUPD_Pos));
}

/**
  * @brief  Master Update Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MUPD(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MUPD_Msk);
}

/**
  * @brief  Judge is Master Sync Input Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Sync Input Interrupt Pending
  * @retval 1 is Master Sync Input Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_SYNC(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_SYNC_Msk, HRPWM_MST_MISR_SYNC_Pos));
}

/**
  * @brief  Master Sync Input Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_SYNC(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_SYNC_Msk);
}

/**
  * @brief  Judge is Master Period Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Period Interrupt Pending
  * @retval 1 is Master Period Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MPER(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MPER_Msk, HRPWM_MST_MISR_MPER_Pos));
}

/**
  * @brief  Master Period Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MPER(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MPER_Msk);
}

/**
  * @brief  Judge is Master Compare D Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare D Interrupt Pending
  * @retval 1 is Master Compare D Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MCMPD(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPD_Msk, HRPWM_MST_MISR_MCMPD_Pos));
}

/**
  * @brief  Master Compare D Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MCMPD(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPD_Msk);
}

/**
  * @brief  Judge is Master Compare C Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare C Interrupt Pending
  * @retval 1 is Master Compare C Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MCMPC(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPC_Msk, HRPWM_MST_MISR_MCMPC_Pos));
}

/**
  * @brief  Master Compare C Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MCMPC(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPC_Msk);
}

/**
  * @brief  Judge is Master Compare B Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare B Interrupt Pending
  * @retval 1 is Master Compare B Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MCMPB(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPB_Msk, HRPWM_MST_MISR_MCMPB_Pos));
}

/**
  * @brief  Master Compare B Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MCMPB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPB_Msk);
}

/**
  * @brief  Judge is Master Compare A Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare A Interrupt Pending
  * @retval 1 is Master Compare A Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsActiveFlag_MCMPA(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPA_Msk, HRPWM_MST_MISR_MCMPA_Pos));
}

/**
  * @brief  Master Compare A Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_ClearFlag_MCMPA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MISR, HRPWM_MST_MISR_MCMPA_Msk);
}

/**
  * @brief  HRPWM Master PWM All Interrupt Pending Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return HRPWM Master PWM All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_Mst_AllIntPnd_Get(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT(HRPWMx->Master.MISR, LL_HRPWM_MISR_MST_IT_FLAG_MSK));
}

/**
  * @brief  Master Repetition DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableRepetitionDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MREPDE_Msk);
}

/**
  * @brief  Master Repetition DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableRepetitionDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MREPDE_Msk);
}

/**
  * @brief  Master Reset DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableResetDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MRSTDE_Msk);
}

/**
  * @brief  Master Reset DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableResetDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MRSTDE_Msk);
}

/**
  * @brief  Master Update DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableUpdateDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MUPDDE_Msk);
}

/**
  * @brief  Master Update DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableUpdateDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MUPDDE_Msk);
}

/**
  * @brief  Master Sync Input DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableSyncDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_SYNCDE_Msk);
}

/**
  * @brief  Master Sync Input DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableSyncDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_SYNCDE_Msk);
}

/**
  * @brief  Master Period DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnablePeriodDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MPERDE_Msk);
}

/**
  * @brief  Master Period DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisablePeriodDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MPERDE_Msk);
}

/**
  * @brief  Master Compare D DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableCompareDDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPDDE_Msk);
}

/**
  * @brief  Master Compare D DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableCompareDDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPDDE_Msk);
}

/**
  * @brief  Master Compare C DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableCompareCDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPCDE_Msk);
}

/**
  * @brief  Master Compare C DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableCompareCDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPCDE_Msk);
}

/**
  * @brief  Master Compare B DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableCompareBDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPBDE_Msk);
}

/**
  * @brief  Master Compare B DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableCompareBDMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPBDE_Msk);
}

/**
  * @brief  Master Compare A DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableCompareADMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPADE_Msk);
}

/**
  * @brief  Master Compare A DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableCompareADMA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPADE_Msk);
}

/**
  * @brief  Master DMA Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Msk DMA Mask Combination @ref LL_HRPWM_Mst_DMATypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetMultiDMAEnable(HRPWM_TypeDef *HRPWMx, uint32_t Msk)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Master.MDIER, LL_HRPWM_MDIER_DMA_EN_MSK, ((Msk) & LL_HRPWM_MDIER_DMA_EN_MSK));
}

/**
  * @brief  Master Repetition Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MREPIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MREPIE_Msk);
}

/**
  * @brief  Master Repetition Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MREPIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MREPIE_Msk);
}

/**
  * @brief  Master Reset Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MRSTIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MRSTIE_Msk);
}

/**
  * @brief  Master Reset Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MRSTIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MRSTIE_Msk);
}

/**
  * @brief  Master Update Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MUPDIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MUPDIE_Msk);
}

/**
  * @brief  Master Update Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MUPDIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MUPDIE_Msk);
}

/**
  * @brief  Master Sync Input Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_SYNCIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_SYNCIE_Msk);
}

/**
  * @brief  Master Sync Input Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_SYNCIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_SYNCIE_Msk);
}

/**
  * @brief  Master Period Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MPERIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MPERIE_Msk);
}

/**
  * @brief  Master Period Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MPERIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MPERIE_Msk);
}

/**
  * @brief  Master Compare D Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MCMPDIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPDIE_Msk);
}

/**
  * @brief  Master Compare D Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MCMPDIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPDIE_Msk);
}

/**
  * @brief  Master Compare C Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MCMPCIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPCIE_Msk);
}

/**
  * @brief  Master Compare C Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MCMPCIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPCIE_Msk);
}

/**
  * @brief  Master Compare B Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MCMPBIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPBIE_Msk);
}

/**
  * @brief  Master Compare B Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MCMPBIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPBIE_Msk);
}

/**
  * @brief  Master Compare A Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT_MCMPAIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPAIE_Msk);
}

/**
  * @brief  Master Compare A Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT_MCMPAIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, HRPWM_MST_MDIER_MCMPAIE_Msk);
}

/**
  * @brief  HRPWM Master PWM All Interrupt Enable Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return HRPWM Master PWM All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetAllEnabledIT(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT(HRPWMx->Master.MDIER, LL_HRPWM_MDIER_MST_IT_EN_MSK));
}

/**
  * @brief  Master PWM Counter Write
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Cnt Master PWM Counter
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetCounter(HRPWM_TypeDef *HRPWMx, uint32_t Cnt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MCNTR, HRPWM_MST_MCNTR_CNTWR_Msk | ((Cnt) & HRPWM_MST_MCNTR_MCNT_Val)); 
    while (READ_BIT_SHIFT(HRPWMx->Master.MCNTR, HRPWM_MST_MCNTR_CNTWR_Msk, HRPWM_MST_MCNTR_CNTWR_Pos));
}

/**
  * @brief  Master PWM Counter Read
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master PWM Counter
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetCounter(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MCNTR, HRPWM_MST_MCNTR_MCNT_Msk, HRPWM_MST_MCNTR_MCNT_Pos));
}

/**
  * @brief  Master PWM Counter Period Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Prd Master PWM Counter Period
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetPeriod(HRPWM_TypeDef *HRPWMx, uint32_t Prd)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MPER, ((Prd) & HRPWM_MST_MPER_MPER_Val));
}

/**
  * @brief  Master PWM Counter Period Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master PWM Counter Period
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetPeriod(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MPER, HRPWM_MST_MPER_MPER_Msk, HRPWM_MST_MPER_MPER_Pos));
}

/**
  * @brief  Master PWM Repetition Period Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Prd Master PWM Repetition Period
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetRepetition(HRPWM_TypeDef *HRPWMx, uint32_t Prd)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MREP, ((Prd) & HRPWM_MST_MREP_MREP_Val));
}

/**
  * @brief  Master PWM Repetition Period Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master PWM Repetition Period
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetRepetition(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MREP, HRPWM_MST_MREP_MREP_Msk, HRPWM_MST_MREP_MREP_Pos));
}

/**
  * @brief  Master PWM Compare A Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Val Master PWM Compare A Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetCompareA(HRPWM_TypeDef *HRPWMx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MCMPAR, ((Val) & HRPWM_MST_MCMPAR_MCMPA_Val));
}

/**
  * @brief  Master PWM Compare A Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master PWM Compare A Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetCompareA(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MCMPAR, HRPWM_MST_MCMPAR_MCMPA_Msk, HRPWM_MST_MCMPAR_MCMPA_Pos));
}

/**
  * @brief  Master PWM Compare B Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Val Master PWM Compare B Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetCompareB(HRPWM_TypeDef *HRPWMx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MCMPBR, ((Val) & HRPWM_MST_MCMPBR_MCMPB_Val));
}

/**
  * @brief  Master PWM Compare B Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master PWM Compare B Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetCompareB(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MCMPBR, HRPWM_MST_MCMPBR_MCMPB_Msk, HRPWM_MST_MCMPBR_MCMPB_Pos));
}

/**
  * @brief  Master PWM Compare C Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Val Master PWM Compare C Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetCompareC(HRPWM_TypeDef *HRPWMx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MCMPCR, ((Val) & HRPWM_MST_MCMPCR_MCMPC_Val));
}

/**
  * @brief  Master PWM Compare C Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master PWM Compare C Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetCompareC(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MCMPCR, HRPWM_MST_MCMPCR_MCMPC_Msk, HRPWM_MST_MCMPCR_MCMPC_Pos));
}

/**
  * @brief  Master PWM Compare D Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Val Master PWM Compare D Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_SetCompareD(HRPWM_TypeDef *HRPWMx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Master.MCMPDR, ((Val) & HRPWM_MST_MCMPDR_MCMPD_Val));
}

/**
  * @brief  Master PWM Compare D Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master PWM Compare D Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetCompareD(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MCMPDR, HRPWM_MST_MCMPDR_MCMPD_Msk, HRPWM_MST_MCMPDR_MCMPD_Pos));
}

/**
  * @brief  Master PWM Register Support that System DMA Write into MDMADR and Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Reg Register Type Mask @ref LL_HRPWM_Comm_BurstDMAMstRegUpdTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableSysDMAWriteUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Reg)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDMAUR, Reg);
}

/**
  * @brief  Master PWM Register Support that System DMA Write into MDMADR and Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Reg Register Type Mask @ref LL_HRPWM_Comm_BurstDMAMstRegUpdTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableSysDMAWriteUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Reg)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDMAUR, Reg);
}

/**
  * @brief  Get Master PWM Register Support Update Register
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Register Type Mask @ref LL_HRPWM_Comm_BurstDMAMstRegUpdTypeDef
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_GetSysDMAWriteUpdate(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Master.MDMAUR, LL_HRPWM_MDMAUR_SYSDMA_UPD_MSK, 0));
}

/**
  * @brief  Master System DMA Data Address Read
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Master System DMA Data Address
  */
__STATIC_INLINE uint32_t* LL_HRPWM_MST_GetSysDMADataAddr(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t*)(&(HRPWMx->Master.MDMADR));
}

/**
  * @brief  Slave PWMx Update Gate Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Gate Slave PWMx Update Gate @ref LL_HRPWM_Slv_UpdGateTypeDef  
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetUpdateGating(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Gate)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_UPDGAT_Msk, (((Gate) & HRPWM_SLV0_PWMCR0_UPDGAT_Val) << HRPWM_SLV0_PWMCR0_UPDGAT_Pos));
}

/**
  * @brief  Slave PWMx Repetition Trigger PWM Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableRepetitionUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDREP_Msk);
}

/**
  * @brief  Slave PWMx Repetition Trigger PWM Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableRepetitionUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDREP_Msk);
}

/**
  * @brief  Slave PWMx Reset/RollOver Trigger PWM Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableResetRollOverUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDRST_Msk);
}

/**
  * @brief  Slave PWMx Reset/RollOver Trigger PWM Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableResetRollOverUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDRST_Msk);
}

/**
  * @brief  Slave Preload Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnablePreload(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PREEN_Msk);
}

/**
  * @brief  Slave Preload Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisablePreload(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PREEN_Msk);
}

/**
  * @brief  Slave DAC Trigger Sync Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Src Slave DAC Trigger Sync Source
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetDACTrig(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_DACSYNC_Msk, (((Src) & HRPWM_SLV0_PWMCR0_DACSYNC_Val) << HRPWM_SLV0_PWMCR0_DACSYNC_Pos));
}

/**
  * @brief  Slave PWMx CMPC Greater Than Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCompareCGreaterThanMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPC_Msk);
}

/**
  * @brief  Slave PWMx CMPC Greater Than Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCompareCGreaterThanMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPC_Msk);
}

/**
  * @brief  Slave PWMx CMPA Greater Than Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCompareAGreaterThanMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPA_Msk);
}

/**
  * @brief  Slave PWMx CMPA Greater Than Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCompareAGreaterThanMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPA_Msk);
}

/**
  * @brief  Slave PWMx Triggered Half Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableTriggeredHalfMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_TRGHLF_Msk);
}

/**
  * @brief  Slave PWMx Triggered Half Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableTriggeredHalfMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_TRGHLF_Msk);
}

/**
  * @brief  Slave PWMx CMPD Auto Delayed Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode CMPD Auto Delayed Mode @ref LL_HRPWM_Slv_CmpDAutoDlyTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCompareDAutoDelayMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_DELCMPD_Msk, (((Mode) & HRPWM_SLV0_PWMCR0_DELCMPD_Val) << HRPWM_SLV0_PWMCR0_DELCMPD_Pos));
}

/**
  * @brief  Slave PWMx CMPB Auto Delayed Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx CMPB Auto Delayed Mode @ref LL_HRPWM_Slv_CmpBAutoDlyTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCompareBAutoDelayMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_DELCMPB_Msk, (((Mode) & HRPWM_SLV0_PWMCR0_DELCMPB_Val) << HRPWM_SLV0_PWMCR0_DELCMPB_Pos));
}

/**
  * @brief  Slave PWMx Sync Event Start PWMx Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableStartOnSync(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCSTRT_Msk);
}

/**
  * @brief  Slave PWMx Sync Event Start PWMx Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableStartOnSync(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCSTRT_Msk);
}

/**
  * @brief  Slave PWMx Sync Event Reset PWMx Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableResetOnSync(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCRST_Msk);
}

/**
  * @brief  Slave PWMx Sync Event Reset PWMx Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableResetOnSync(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCRST_Msk);
}

/**
  * @brief  Slave PWMx ReSync Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx ReSync Mode @ref LL_HRPWM_Slv_ReSyncModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableResyncUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_RSYNCU_Msk, (((Mode) & HRPWM_SLV0_PWMCR0_RSYNCU_Val) << HRPWM_SLV0_PWMCR0_RSYNCU_Pos));
}

/**
  * @brief  Slave PWMx Push-Pull Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnablePushPullMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PSHPLL_Msk);
}

/**
  * @brief  Slave PWMx Push-Pull Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisablePushPullMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PSHPLL_Msk);
}

/**
  * @brief  Slave PWMx Interleaved Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Interleaved Mode @ref LL_HRPWM_IntlvdModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetInterleavedMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_INTLVD_Msk, (((Mode) & HRPWM_SLV0_PWMCR0_INTLVD_Val) << HRPWM_SLV0_PWMCR0_INTLVD_Pos));
}

/**
  * @brief  Slave PWMx Half Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableHalfMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_HALF_Msk);
}

/**
  * @brief  Slave PWMx Half Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableHalfMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_HALF_Msk);
}

/**
  * @brief  Slave PWMx Repeat Trigger Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableRetriggerMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_RETRIG_Msk);
}

/**
  * @brief  Slave PWMx Repeat Trigger Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableRetriggerMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_RETRIG_Msk);
}

/**
  * @brief  Slave PWMx Work Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param Mode Slave PWMx Work Mode
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCounterMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_CONT_Msk, (((Mode) & HRPWM_SLV0_PWMCR0_CONT_Val) << HRPWM_SLV0_PWMCR0_CONT_Pos));
}

/**
  * @brief  Slave PWMx Clock Division Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param Div Slave PWMx Clock Division
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetPrescaler(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0, 
            HRPWM_SLV0_PWMCR0_CKPSC_Msk, (((Div) & HRPWM_SLV0_PWMCR0_CKPSC_Val) << HRPWM_SLV0_PWMCR0_CKPSC_Pos));
}

/**
  * @brief  Slave PWMx Burst DMA Disable Assert
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_AssertPWMxBurstDMADisable(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_BDMADIS_Msk);
}

/**
  * @brief  Slave PWMx Burst DMA Disable Release
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ReleasePWMxBurstDMADisable(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_BDMADIS_Msk);
}

/**
  * @brief  Slave PWM Burst DMA Disable Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0: Slave PWM Burst DMA Disable Release
  * @retval 1: Slave PWM Burst DMA Disable Assert
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsPWMxBurstDMADisableAsserted(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_BDMADIS_Msk, HRPWM_SLV0_PWMCR1_BDMADIS_Pos));
}

/**
  * @brief  Slave PWM7 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM7(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD7_Msk);
}

/**
  * @brief  Slave PWM7 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM7(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD7_Msk);
}

/**
  * @brief  Slave PWM6 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM6(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD6_Msk);
}

/**
  * @brief  Slave PWM6 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM6(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD6_Msk);
}

/**
  * @brief  Slave PWM5 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM5(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD5_Msk);
}

/**
  * @brief  Slave PWM5 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM5(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD5_Msk);
}

/**
  * @brief  Slave PWM4 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM4(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD4_Msk);
}

/**
  * @brief  Slave PWM4 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM4(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD4_Msk);
}

/**
  * @brief  Slave PWM3 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM3(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD3_Msk);
}

/**
  * @brief  Slave PWM3 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM3(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD3_Msk);
}

/**
  * @brief  Slave PWM2 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM2(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD2_Msk);
}

/**
  * @brief  Slave PWM2 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM2(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD2_Msk);
}

/**
  * @brief  Slave PWM1 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM1(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD1_Msk);
}

/**
  * @brief  Slave PWM1 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM1(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD1_Msk);
}

/**
  * @brief  Slave PWM0 Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerPWM0(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD0_Msk);
}

/**
  * @brief  Slave PWM0 Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerPWM0(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD0_Msk);
}

/**
  * @brief  Slave Master PWM Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateTriggerMST(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_MUPD_Msk);
}

/**
  * @brief  Slave Master PWM Update Event Trigger PWMx Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateTriggerMST(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_MUPD_Msk);
}

/**
  * @brief  Slave PWM Update Event Trigger PWMx Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  UpdTrg PWM Update Event Trigger @ref LL_HRPWM_Slv_PWMUpdTrigTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetUpdateTrigPWMx(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t UpdTrg)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            LL_HRPWM_PWMCR1_UPD_TRG_PWMx_MSK, ((UpdTrg) & LL_HRPWM_PWMCR1_UPD_TRG_PWMx_MSK));
}

/**
  * @brief  Slave PWMx Fault Roll-Over Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Fault Roll-Over Mode @ref LL_HRPWM_Slv_RollOverModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetFaultEventRollOverMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_FLTROM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_FLTROM_Val) << HRPWM_SLV0_PWMCR1_FLTROM_Pos));
}

/**
  * @brief  Slave PWMx Event Roll-Over Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Event Roll-Over Mode @ref LL_HRPWM_Slv_RollOverModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetEventRollOverMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_EEVROM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_EEVROM_Val) << HRPWM_SLV0_PWMCR1_EEVROM_Pos));
}

/**
  * @brief  Slave PWMx ADC Roll-Over Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx ADC Roll-Over Mode @ref LL_HRPWM_Slv_RollOverModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetADCRollOverMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_ADROM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_ADROM_Val) << HRPWM_SLV0_PWMCR1_ADROM_Pos));
}

/**
  * @brief  Slave PWMx Output Roll-Over Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Output Roll-Over Mode @ref LL_HRPWM_Slv_RollOverModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetOutputRollOverMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_OUTROM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_OUTROM_Val) << HRPWM_SLV0_PWMCR1_OUTROM_Pos));
}

/**
  * @brief  Slave PWMx Counter Roll-Over Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Counter Roll-Over Mode @ref LL_HRPWM_Slv_RollOverModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetRollOverMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_ROM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_ROM_Val) << HRPWM_SLV0_PWMCR1_ROM_Pos));
}

/**
  * @brief  Slave PWMx Capture B Mode Set
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Capture B Mode @ref LL_HRPWM_Slv_CapModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCaptureBMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_CAPBM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_CAPBM_Val) << HRPWM_SLV0_PWMCR1_CAPBM_Pos));
}

/**
  * @brief  Slave PWMx Capture B Mode Get
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return PWMx Capture B Mode @ref LL_HRPWM_Slv_CapModeTypeDef
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCaptureBMode(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_CAPBM_Msk, HRPWM_SLV0_PWMCR1_CAPBM_Pos));
}

/**
  * @brief  Slave PWMx Counter Direction Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Counter Direction Mode @ref LL_HRPWM_Slv_DirModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCountingMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_UDM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_UDM_Val) << HRPWM_SLV0_PWMCR1_UDM_Pos));
}

/**
  * @brief  Slave PWMx Capture A Mode Set
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx Capture A Mode @ref LL_HRPWM_Slv_CapModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCaptureAMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_CAPAM_Msk, (((Mode) & HRPWM_SLV0_PWMCR1_CAPAM_Val) << HRPWM_SLV0_PWMCR1_CAPAM_Pos));
}

/**
  * @brief  Slave PWMx Capture A Mode Get
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return PWMx Capture A Mode @ref LL_HRPWM_Slv_CapModeTypeDef
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCaptureAMode(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_CAPAM_Msk, HRPWM_SLV0_PWMCR1_CAPAM_Pos));
}

/**
  * @brief  Slave PWMx DAC Reset Trigger Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Src PWMx DAC Reset Trigger Source @ref LL_HRPWM_Slv_DACRstTrigSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetDualDacResetTrigger(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
            HRPWM_SLV0_PWMCR1_DCDR_Msk, (((Src) & HRPWM_SLV0_PWMCR1_DCDR_Val) << HRPWM_SLV0_PWMCR1_DCDR_Pos));
}

/**
  * @brief  Slave PWMx DAC Step Trigger Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Src PWMx DAC Step Trigger Source @ref LL_HRPWM_Slv_DACStepTrigSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetDualDacStepTrigger(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, 
    HRPWM_SLV0_PWMCR1_DCDS_Msk, (((Src) & HRPWM_SLV0_PWMCR1_DCDS_Val) << HRPWM_SLV0_PWMCR1_DCDS_Pos));
}

/**
  * @brief  Slave PWMx DAC Reset/Step Trigger Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableDualDacTrigger(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_DCDE_Msk);
}

/**
  * @brief  Slave PWMx DAC Reset/Step Trigger Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableDualDacTrigger(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_DCDE_Msk);
}

/**
  * @brief  Slave PWMx OUTB Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return PWMx OUTB Level
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetOutputB(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_OUTB_Msk, HRPWM_SLV0_PWMISR_OUTB_Pos));
}

/**
  * @brief  Slave PWMx OUTA Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return PWMx OUTA Level
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetOutputA(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_OUTA_Msk, HRPWM_SLV0_PWMISR_OUTA_Pos));
}

/**
  * @brief  Slave PWMx OUTB Protection Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return PWMx OUTB Protection Level
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetOutputBProtection(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_OUTBSTA_Msk, HRPWM_SLV0_PWMISR_OUTBSTA_Pos));
}

/**
  * @brief  Slave PWMx OUTA Protection Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return PWMx OUTA Protection Level
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetOutputAProtection(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_OUTASTA_Msk, HRPWM_SLV0_PWMISR_OUTASTA_Pos));
}

/**
  * @brief  Slave PWMx Push-Pull Output Status Protection Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 OUTA Push-Pull Output, OUTB Force Invalid
  * @retval 1 OUTB Push-Pull Output, OUTA Force Invalid
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetIdlePushPullStatus(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_IPPSTA_Msk, HRPWM_SLV0_PWMISR_IPPSTA_Pos));
}

/**
  * @brief  Slave PWMx Push-Pull Output Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 OUTA Push-Pull Output, OUTB Force Invalid
  * @retval 1 OUTB Push-Pull Output, OUTA Force Invalid
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCurrentPushPullStatus(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_CPPSTA_Msk, HRPWM_SLV0_PWMISR_CPPSTA_Pos));
}

/**
  * @brief  Judge is Slave PWMx Delayed Protection Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Delayed Protection Interrupt Pending
  * @retval 1 is Slave PWMx Delayed Protection Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_DLYPRT(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_DLYPRT_Msk, HRPWM_SLV0_PWMISR_DLYPRT_Pos));
}

/**
  * @brief  Slave PWMx Delayed Protection Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_DLYPRT(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_DLYPRT_Msk);
}

/**
  * @brief  Judge is Slave PWMx Capture B Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Capture B Interrupt Pending
  * @retval 1 is Slave PWMx Capture B Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CAPB(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_CAPB_Msk, HRPWM_SLV0_PWMISR_CAPB_Pos));
}

/**
  * @brief  Slave PWMx Capture B Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CAPB(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CAPB_Msk);
}

/**
  * @brief  Judge is Slave PWMx Capture A Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Capture A Interrupt Pending
  * @retval 1 is Slave PWMx Capture A Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CAPA(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_CAPA_Msk, HRPWM_SLV0_PWMISR_CAPA_Pos));
}

/**
  * @brief  Slave PWMx Capture A Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CAPA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CAPA_Msk);
}

/**
  * @brief  Judge is Slave PWMx Repetition Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Repetition Interrupt Pending
  * @retval 1 is Slave PWMx Repetition Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_REP(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_REP_Msk, HRPWM_SLV0_PWMISR_REP_Pos));
}

/**
  * @brief  Slave PWMx Repetition Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_REP(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_REP_Msk);
}

/**
  * @brief  Judge is Slave PWMx Reset Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Reset Interrupt Pending
  * @retval 1 is Slave PWMx Reset Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_RST(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_RST_Msk, HRPWM_SLV0_PWMISR_RST_Pos));
}

/**
  * @brief  Slave PWMx Reset Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_RST(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_RST_Msk);
}

/**
  * @brief  Judge is Slave PWMx OutB Clear Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx OutB Clear Interrupt Pending
  * @retval 1 is Slave PWMx OutB Clear Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CLRB(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_CLRB_Msk, HRPWM_SLV0_PWMISR_CLRB_Pos));
}

/**
  * @brief  Slave PWMx OutB Clear Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CLRB(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CLRB_Msk);
}

/**
  * @brief  Judge is Slave PWMx OutB Set Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx OutB Set Interrupt Pending
  * @retval 1 is Slave PWMx OutB Set Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_SETB(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_SETB_Msk, HRPWM_SLV0_PWMISR_SETB_Pos));
}

/**
  * @brief  Slave PWMx OutB Set Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_SETB(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_SETB_Msk);
}

/**
  * @brief  Judge is Slave PWMx OutA Clear Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx OutA Clear Interrupt Pending
  * @retval 1 is Slave PWMx OutA Clear Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CLRA(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_CLRA_Msk, HRPWM_SLV0_PWMISR_CLRA_Pos));
}

/**
  * @brief  Slave PWMx OutA Clear Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CLRA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CLRA_Msk);
}

/**
  * @brief  Judge is Slave PWMx OutA Set Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx OutA Set Interrupt Pending
  * @retval 1 is Slave PWMx OutA Set Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_SETA(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_SETA_Msk, HRPWM_SLV0_PWMISR_SETA_Pos));
}

/**
  * @brief  Slave PWMx OutA Set Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_SETA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_SETA_Msk);
}

/**
  * @brief  Judge is Slave PWMx Update Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Update Interrupt Pending
  * @retval 1 is Slave PWMx Update Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_UPD(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_UPD_Msk, HRPWM_SLV0_PWMISR_UPD_Pos));
}

/**
  * @brief  Slave PWMx Update Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_UPD(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_UPD_Msk);
}

/**
  * @brief  Judge is Slave PWMx Period/Roll-Over Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Period/Roll-Over Interrupt Pending
  * @retval 1 is Slave PWMx Period/Roll-Over Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_PER(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_PER_Msk, HRPWM_SLV0_PWMISR_PER_Pos));
}

/**
  * @brief  Slave PWMx Period/Roll-Over Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_PER(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_PER_Msk);
}

/**
  * @brief  Judge is Slave PWMx Compare D Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Compare D Interrupt Pending
  * @retval 1 is Slave PWMx Compare D Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CMPD(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPD_Msk, HRPWM_SLV0_PWMISR_CMPD_Pos));
}

/**
  * @brief  Slave PWMx Compare D Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CMPD(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPD_Msk);
}

/**
  * @brief  Judge is Slave PWMx Compare C Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Compare C Interrupt Pending
  * @retval 1 is Slave PWMx Compare C Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CMPC(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPC_Msk, HRPWM_SLV0_PWMISR_CMPC_Pos));
}

/**
  * @brief  Slave PWMx Compare C Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CMPC(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPC_Msk);
}

/**
  * @brief  Judge is Slave PWMx Compare B Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Compare B Interrupt Pending
  * @retval 1 is Slave PWMx Compare B Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CMPB(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_CMPB_Msk, HRPWM_SLV0_PWMISR_CMPB_Pos));
}

/**
  * @brief  Slave PWMx Compare B Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CMPB(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPB_Msk);
}

/**
  * @brief  Judge is Slave PWMx Compare A Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 isn't Slave PWMx Compare A Interrupt Pending
  * @retval 1 is Slave PWMx Compare A Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsActiveFlag_CMPA(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, 
            HRPWM_SLV0_PWMISR_CMPA_Msk, HRPWM_SLV0_PWMISR_CMPA_Pos));
}

/**
  * @brief  Slave PWMx Compare A Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ClearFlag_CMPA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPA_Msk);
}

/**
  * @brief  HRPWM Slave PWMx All Interrupt Pending Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return HRPWM Slave PWMx All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetAllITPending(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMISR, LL_HRPWM_PWMISR_PWMx_IT_FLAG_MSK));
}

/**
  * @brief  Slave PWMx Delayed Protection DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableDelayProtectionDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTDE_Msk);
}

/**
  * @brief  Slave PWMx Delayed Protection DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableDelayProtectionDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTDE_Msk);
}

/**
  * @brief  Slave PWMx Capture B DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCaptureBDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBDE_Msk);
}

/**
  * @brief  Slave PWMx Capture B DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCaptureBDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBDE_Msk);
}

/**
  * @brief  Slave PWMx Capture A DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCaptureADMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPADE_Msk);
}

/**
  * @brief  Slave PWMx Capture A DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCaptureADMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPADE_Msk);
}

/**
  * @brief  Slave PWMx Repetition DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableRepetitionDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPDE_Msk);
}

/**
  * @brief  Slave PWMx Repetition DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableRepetitionDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPDE_Msk);
}

/**
  * @brief  Slave PWMx Reset DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableResetDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTDE_Msk);
}

/**
  * @brief  Slave PWMx Reset DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableResetDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTDE_Msk);
}

/**
  * @brief  Slave PWMx OutB Clear DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputBClearDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBDE_Msk);
}

/**
  * @brief  Slave PWMx OutB Clear DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputBClearDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBDE_Msk);
}

/**
  * @brief  Slave PWMx OutB Set DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputBSetDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBDE_Msk);
}

/**
  * @brief  Slave PWMx OutB Set DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputBSetDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBDE_Msk);
}

/**
  * @brief  Slave PWMx OutA Clear DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputAClearDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRADE_Msk);
}

/**
  * @brief  Slave PWMx OutA Clear DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputAClearDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRADE_Msk);
}

/**
  * @brief  Slave PWMx OutA Set DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputASetDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETADE_Msk);
}

/**
  * @brief  Slave PWMx OutA Set DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputASetDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETADE_Msk);
}

/**
  * @brief  Slave PWMx Update DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableUpdateDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDDE_Msk);
}

/**
  * @brief  Slave PWMx Update DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableUpdateDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDDE_Msk);
}

/**
  * @brief  Slave PWMx Period/Roll-Over DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnablePeriodDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERDE_Msk);
}

/**
  * @brief  Slave PWMx Period/Roll-Over DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisablePeriodDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERDE_Msk);
}

/**
  * @brief  Slave PWMx Compare D DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCompareDDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDDE_Msk);
}

/**
  * @brief  Slave PWMx Compare D DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCompareDDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDDE_Msk);
}

/**
  * @brief  Slave PWMx Compare C DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCompareCDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCDE_Msk);
}

/**
  * @brief  Slave PWMx Compare C DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCompareCDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCDE_Msk);
}

/**
  * @brief  Slave PWMx Compare B DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCompareBDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBDE_Msk);
}

/**
  * @brief  Slave PWMx Compare B DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCompareBDMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBDE_Msk);
}

/**
  * @brief  Slave PWMx Compare A DMA Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableCompareADMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPADE_Msk);
}

/**
  * @brief  Slave PWMx Compare A DMA Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableCompareADMA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPADE_Msk);
}

/**
  * @brief  Slave PWMx DMA Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Msk DMA Mask Combination @ref LL_HRPWM_Slv_DMATypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetMultiDMAEnable(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Msk)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, 
            LL_HRPWM_PWMDIER_PWMx_DMA_EN_MSK, ((Msk) & LL_HRPWM_SLV_DMA_ALL_MASK));
}

/**
  * @brief  Slave PWMx Delayed Protection Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_DLYPRTIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTIE_Msk);
}

/**
  * @brief  Slave PWMx Delayed Protection Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_DLYPRTIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTIE_Msk);
}

/**
  * @brief  Slave PWMx Capture B Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CAPBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBIE_Msk);
}

/**
  * @brief  Slave PWMx Capture B Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CAPBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBIE_Msk);
}

/**
  * @brief  Slave PWMx Capture A Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CAPAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPAIE_Msk);
}

/**
  * @brief  Slave PWMx Capture A Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CAPAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPAIE_Msk);
}

/**
  * @brief  Slave PWMx Repetition Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_REPIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPIE_Msk);
}

/**
  * @brief  Slave PWMx Repetition Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_REPIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPIE_Msk);
}

/**
  * @brief  Slave PWMx Reset Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_RSTIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTIE_Msk);
}

/**
  * @brief  Slave PWMx Reset Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_RSTIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTIE_Msk);
}

/**
  * @brief  Slave PWMx OutB Clear Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CLRBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBIE_Msk);
}

/**
  * @brief  Slave PWMx OutB Clear Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CLRBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBIE_Msk);
}

/**
  * @brief  Slave PWMx OutB Set Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_SETBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBIE_Msk);
}

/**
  * @brief  Slave PWMx OutB Set Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_SETBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBIE_Msk);
}

/**
  * @brief  Slave PWMx OutA Clear Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CLRAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRAIE_Msk);
}

/**
  * @brief  Slave PWMx OutA Clear Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CLRAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRAIE_Msk);
}

/**
  * @brief  Slave PWMx OutA Set Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_SETAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETAIE_Msk);
}

/**
  * @brief  Slave PWMx OutA Set Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_SETAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETAIE_Msk);
}

/**
  * @brief  Slave PWMx Update Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_UPDIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDIE_Msk);
}

/**
  * @brief  Slave PWMx Update Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_UPDIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDIE_Msk);
}

/**
  * @brief  Slave PWMx Period/Roll-Over Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_PERIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERIE_Msk);
}

/**
  * @brief  Slave PWMx Period/Roll-Over Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_PERIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERIE_Msk);
}

/**
  * @brief  Slave PWMx Compare D Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CMPDIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDIE_Msk);
}

/**
  * @brief  Slave PWMx Compare D Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CMPDIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDIE_Msk);
}

/**
  * @brief  Slave PWMx Compare C Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CMPCIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCIE_Msk);
}

/**
  * @brief  Slave PWMx Compare C Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CMPCIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCIE_Msk);
}

/**
  * @brief  Slave PWMx Compare B Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CMPBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBIE_Msk);
}

/**
  * @brief  Slave PWMx Compare B Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CMPBIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBIE_Msk);
}

/**
  * @brief  Slave PWMx Compare A Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT_CMPAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPAIE_Msk);
}

/**
  * @brief  Slave PWMx Compare A Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT_CMPAIE(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPAIE_Msk);
}

/**
  * @brief  HRPWM Slave PWMx All Interrupt Enable Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return HRPWM Slave PWMx All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetAllEnabledIT(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, LL_HRPWM_PWMDIER_PWMx_IT_EN_MSK));
}

/**
  * @brief  Slave PWMx Counter Write
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Cnt Slave PWMx Counter
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCounter(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Cnt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CNTR, HRPWM_SLV0_CNTR_CNTWR_Msk | ((Cnt) & HRPWM_SLV0_CNTR_CNT_Val));
    while (READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CNTR, 
            HRPWM_SLV0_CNTR_CNTWR_Msk, HRPWM_SLV0_CNTR_CNTWR_Pos));
}

/**
  * @brief  Slave PWMx Counter Read
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx Counter
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCounter(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CNTR, 
            HRPWM_SLV0_CNTR_CNT_Msk, HRPWM_SLV0_CNTR_CNT_Pos));
}

/**
  * @brief  Slave PWMx Counter Period Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Prd Slave PWMx Counter Period
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetPeriod(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Prd)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PERR, ((Prd) & HRPWM_SLV0_PERR_PER_Val));
}

/**
  * @brief  Slave PWMx Counter Period Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx Counter Period
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetPeriod(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PERR));
}

/**
  * @brief  Slave PWMx Repetition Period Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Prd Slave PWMx Repetition Period
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetRepetition(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Prd)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.REPR, ((Prd) & 0xffUL));
}

/**
  * @brief  Slave PWMx Repetition Period Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx Repetition Period
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetRepetition(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.REPR));
}

/**
  * @brief  Slave PWMx Compare A Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Val Slave PWMx Compare A Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCompareA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPAR, ((Val) & HRPWM_SLV0_CMPAR_CMPA_Val));
}

/**
  * @brief  Slave PWMx Compare A Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx Compare A Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCompareA(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPAR));
}

/**
  * @brief  Slave PWMx Compare B Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Val Slave PWMx Compare B Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCompareB(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPBR, ((Val) & HRPWM_SLV0_CMPBR_CMPB_Val));
}

/**
  * @brief  Slave PWMx Compare B Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx Compare B Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCompareB(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPBR));
}

/**
  * @brief  Slave PWMx Compare C Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Val Slave PWMx Compare C Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCompareC(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPCR, ((Val) & HRPWM_SLV0_CMPCR_CMPC_Val));
}

/**
  * @brief  Slave PWMx Compare C Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx Compare C Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCompareC(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPCR));
}

/**
  * @brief  Slave PWMx Compare D Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Val Slave PWMx Compare D Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCompareD(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPDR, ((Val) & HRPWM_SLV0_CMPDR_CMPD_Val));
}

/**
  * @brief  Slave PWMx Compare D Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx Compare D Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCompareD(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CMPDR));
}

/**
  * @brief  Slave PWMx Capture A Counter Direction Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Capture A Counter Direction Up
  * @retval 1 Capture A Counter Direction Down
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCaptureADirection(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPAR, 
            HRPWM_SLV0_CAPAR_DIR_Msk, HRPWM_SLV0_CAPAR_DIR_Pos));
}

/**
  * @brief  Slave PWMx Capture A Counter Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Capture A Counter Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCaptureA(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPAR, 
            HRPWM_SLV0_CAPAR_CAPA_Msk, HRPWM_SLV0_CAPAR_CAPA_Pos));
}

/**
  * @brief  Slave PWMx Capture A Counter Value and Direction Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  pVal Save Counter Value
  * @param  pDir Save Counter Direction @ref LL_HRPWM_Slv_CapDirTypeDef
  * @return Capture A Counter Value
  */
__STATIC_INLINE void LL_HRPWM_SLV_GetCaptureAValueAndDirection(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t *pVal, uint32_t *pDir)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));
    ASSERT_INLINE_PARAM(pVal != NULL);
    ASSERT_INLINE_PARAM(pDir != NULL);

    uint32_t tmp = READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPAR);
    *pVal = (READ_BIT_SHIFT(tmp, HRPWM_SLV0_CAPAR_CAPA_Msk, HRPWM_SLV0_CAPAR_CAPA_Pos)); 
    *pDir = (READ_BIT_SHIFT(tmp, HRPWM_SLV0_CAPAR_DIR_Msk, HRPWM_SLV0_CAPAR_DIR_Pos)); 
}

/**
  * @brief  Slave PWMx Capture B Counter Direction Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Capture B Counter Direction Up
  * @retval 1 Capture B Counter Direction Down
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCaptureBDirection(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPBR, 
            HRPWM_SLV0_CAPBR_DIR_Msk, HRPWM_SLV0_CAPBR_DIR_Pos));
}

/**
  * @brief  Slave PWMx Capture B Counter Value Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Capture B Counter Value
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetCaptureB(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPBR, 
            HRPWM_SLV0_CAPBR_CAPB_Msk, HRPWM_SLV0_CAPBR_CAPB_Pos));
}

/**
  * @brief  Slave PWMx Capture B Counter Value and Direction Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  pVal Save Counter Value
  * @param  pDir Save Counter Direction @ref LL_HRPWM_Slv_CapDirTypeDef
  * @return Capture B Counter Value
  */
__STATIC_INLINE void LL_HRPWM_SLV_GetCaptureBValueAndDirection(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t *pVal, uint32_t *pDir)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));
    ASSERT_INLINE_PARAM(pVal != NULL);
    ASSERT_INLINE_PARAM(pDir != NULL);

    uint32_t tmp = READ_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPBR);
    *pVal = (READ_BIT_SHIFT(tmp, HRPWM_SLV0_CAPBR_CAPB_Msk, HRPWM_SLV0_CAPBR_CAPB_Pos)); 
    *pDir = (READ_BIT_SHIFT(tmp, HRPWM_SLV0_CAPBR_DIR_Msk, HRPWM_SLV0_CAPBR_DIR_Pos)); 
}

/**
  * @brief  Slave PWMx Falling Edge DeadTime Direction Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Dir PWMx Falling Edge DeadTime Direction @ref HAL_HRPWM_Slv_DtDirTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DT_SetFallingSign(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DTR, 
            HRPWM_SLV0_DTR_SDTF_Msk, (((Dir) & HRPWM_SLV0_DTR_SDTF_Val) << HRPWM_SLV0_DTR_SDTF_Pos));
}

/**
  * @brief  Slave PWMx Falling Edge DeadTime Time Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Time PWMx Falling Edge DeadTime Time
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DT_SetFallingValue(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Time)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DTR, 
            HRPWM_SLV0_DTR_DTF_Msk, (((Time) & HRPWM_SLV0_DTR_DTF_Val) << HRPWM_SLV0_DTR_DTF_Pos));
}

/**
  * @brief  Slave PWMx Rising Edge DeadTime Direction Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Dir PWMx Rising Edge DeadTime Direction @ref LL_HRPWM_Slv_DtDirTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DT_SetRisingSign(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Dir)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DTR, 
            HRPWM_SLV0_DTR_SDTR_Msk, (((Dir) & HRPWM_SLV0_DTR_SDTR_Val) << HRPWM_SLV0_DTR_SDTR_Pos));
}

/**
  * @brief  Slave PWMx Rising Edge DeadTime Time Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Time PWMx Rising Edge DeadTime Time
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DT_SetRisingValue(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Time)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DTR, 
            HRPWM_SLV0_DTR_DTR_Msk, (((Time) & HRPWM_SLV0_DTR_DTR_Val) << HRPWM_SLV0_DTR_DTR_Pos));
}

/**
  * @brief  Slave PWMx OUTA Set Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt PWMx OUTA Set Event @ref LL_HRPWM_Slv_OutCtrlEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetOutputASetSrc(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.SETAR, Evt & LL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK);
}

/**
  * @brief  Slave PWMx OUTA Clear Event Enable  Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt PWMx OUTA Clear Event @ref LL_HRPWM_Slv_OutCtrlEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetOutputAClrSrc(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CLRAR, Evt & LL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK);
}

/**
  * @brief  Slave PWMx OUTB Set Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt PWMx OUTB Set Event @ref LL_HRPWM_Slv_OutCtrlEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetOutputBSetSrc(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.SETBR, Evt & LL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK);
}

/**
  * @brief  Slave PWMx OUTB Clear Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt PWMx OUTB Clear Event @ref LL_HRPWM_Slv_OutCtrlEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetOutputBClrSrc(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CLRBR, Evt & LL_HRPWM_SLV_OUT_CTRL_EVT_ALL_MASK);
}

/**
  * @brief  Slave PWMx External Event x Filter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt_x PWMx External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @param  Fil PWMx External Event x Filter @ref LL_HRPWM_Slv_ExtEvtFilTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetEventFilter(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Evt_x, uint32_t Fil)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(LL_HRPWM_REG_OFFSET(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR0, (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), 
            0xfUL << (1 + ((Evt_x) % 5) * 5), (((Fil) & 0xfUL) << (1 + ((Evt_x) % 5) * 5)));
}

/**
  * @brief  Slave PWMx External Event x Blank Latch Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt_x PWMx External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableEventBlankLatch(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Evt_x)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(LL_HRPWM_REG_OFFSET(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR0, 
            (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), BIT(((Evt_x) % 5) * 5));
}

/**
  * @brief  Slave PWMx External Event x Blank Latch Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt_x PWMx External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableEventBlankLatch(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Evt_x)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(LL_HRPWM_REG_OFFSET(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR0, 
            (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), BIT(((Evt_x) % 5) * 5));
}

/**
  * @brief  Slave PWMx External Event A Counter Threshold Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Thres PWMx External Event A Count Threshold
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetEventCounterThreshold(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Thres)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR2, 
            HRPWM_SLV0_EEFR2_EEVACNT_Msk, (((Thres) & HRPWM_SLV0_EEFR2_EEVACNT_Val) << HRPWM_SLV0_EEFR2_EEVACNT_Pos));
}

/**
  * @brief  Slave PWMx External Event A Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Src PWMx External Event A Source @ref LL_HRPWM_ExtEvtNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetEventCounterSource(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR2, 
            HRPWM_SLV0_EEFR2_EEVASEL_Msk, (((Src) & HRPWM_SLV0_EEFR2_EEVASEL_Val) << HRPWM_SLV0_EEFR2_EEVASEL_Pos));
}

/**
  * @brief  Slave PWMx External Event A Counter Reset Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mode PWMx External Event A Counter Reset Mode @ref LL_HRPWM_Slv_EvtACntrRstModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetEventCounterResetMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR2, 
            HRPWM_SLV0_EEFR2_EEVARSTM_Msk, (((Mode) & HRPWM_SLV0_EEFR2_EEVARSTM_Val) << HRPWM_SLV0_EEFR2_EEVARSTM_Pos));
}

/**
  * @brief  Slave PWMx External Event A Counter Reset
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_ResetEventCounter(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR2, HRPWM_SLV0_EEFR2_EEVACRES_Msk);
}

/**
  * @brief  Slave PWMx External Event A Counter Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableEventCounter(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR2, HRPWM_SLV0_EEFR2_EEVACE_Msk);
}

/**
  * @brief  Slave PWMx External Event A Counter Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableEventCounter(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.EEFR2, HRPWM_SLV0_EEFR2_EEVACE_Msk);
}

/**
  * @brief  Slave PWMx Counter Reset Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt PWMx Counter Reset Event @ref LL_HRPWM_Slv_CntrRstEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetResetTrig(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.RSTR, ((Evt) & 0xFFFFFFFFUL));
    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.RSTER, ((Evt) >> 32ULL));
}

/**
  * @brief  Slave PWMx Chopper Start Pulse Width Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Width PWMx Chopper Start Pulse Width @ref LL_HRWPM_Slv_PC_PulseWidthTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_CHP_SetPulseWidth(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CHPR, 
            HRPWM_SLV0_CHPR_STRPW_Msk, (((Width) & HRPWM_SLV0_CHPR_STRPW_Val) << HRPWM_SLV0_CHPR_STRPW_Pos));
}

/**
  * @brief  Slave PWMx Chopper Duty Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Duty PWMx Chopper Duty @ref LL_HRPWM_Slv_PC_DutyTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_CHP_SetDutyCycle(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Duty)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CHPR, 
            HRPWM_SLV0_CHPR_CARDTY_Msk, (((Duty) & HRPWM_SLV0_CHPR_CARDTY_Val) << HRPWM_SLV0_CHPR_CARDTY_Pos));
}

/**
  * @brief  Slave PWMx Chopper Frequency Division Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Div PWMx Chopper Frequency Division @ref LL_HRPWM_Slv_PC_FreqDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_CHP_SetPrescaler(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CHPR, 
            HRPWM_SLV0_CHPR_CARFRQ_Msk, (((Div) & HRPWM_SLV0_CHPR_CARFRQ_Val) << HRPWM_SLV0_CHPR_CARFRQ_Pos));
}

/**
  * @brief  Slave PWMx Capture A Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt PWMx Capture A Event @ref LL_HRPWM_Slv_CapTrigEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCaptureATrig(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPACR, ((Evt) & 0xFFFFFFFFUL));
    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPACER, ((Evt) >> 32ULL));
}

/**
  * @brief  Slave PWMx Capture B Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Evt PWMx Capture B Event @ref LL_HRPWM_Slv_CapTrigEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetCaptureBTrig(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPBCR, ((Evt) & 0xFFFFFFFFUL));
    WRITE_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.CAPBCER, ((Evt) >> 32ULL));
}

/**
  * @brief  Slave PWMx DeadTime Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableDeadTime(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DTEN_Msk);
}

/**
  * @brief  Slave PWMx DeadTime Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableDeadTime(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DTEN_Msk);
}

/**
  * @brief  Slave PWMx Delay Protection Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableDLYPRT(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DLYPRTEN_Msk);
}

/**
  * @brief  Slave PWMx Delay Protection Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableDLYPRT(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DLYPRTEN_Msk);
}

/**
  * @brief  Slave PWMx Delay Protection Mechanism Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mech PWMx Delay Protection Mechanism @ref LL_HRPWM_Slv_DlyProtMechTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetDLYPRTMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mech)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_DLYPRT_Msk, (((Mech) & HRPWM_SLV0_OUTR_DLYPRT_Val) << HRPWM_SLV0_OUTR_DLYPRT_Pos));
}

/**
  * @brief  Slave PWMx Balance Idle Auto Recover Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableBIAR(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_BIAR_Msk);
}

/**
  * @brief  Slave PWMx Balance Idle Auto Recover Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableBIAR(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_BIAR_Msk);
}

/**
  * @brief  Slave PWMx OutB Idle DeadTime Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputBIdleDeadTime(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLB_Msk);
}

/**
  * @brief  Slave PWMx OutB Idle DeadTime Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputBIdleDeadTime(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLB_Msk);
}

/**
  * @brief  Slave PWMx OutB Burst Mode Idle Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputBBurstModeIdle(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMB_Msk);
}

/**
  * @brief  Slave PWMx OutB Burst Mode Idle Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputBBurstModeIdle(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMB_Msk);
}

/**
  * @brief  Slave PWMx OutB Chopper Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputBChopper(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPB_Msk);
}

/**
  * @brief  Slave PWMx OutB Chopper Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputBChopper(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPB_Msk);
}

/**
  * @brief  Slave PWMx OutB Idle Status Level Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Lvl PWMx OutB Idle Status Level @ref LL_HRPWM_Slv_OutIdleLvlTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_OUT_SetBIdleLevel(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Lvl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_IDLESB_Msk, (((Lvl) & HRPWM_SLV0_OUTR_IDLESB_Val) << HRPWM_SLV0_OUTR_IDLESB_Pos));
}

/**
  * @brief  Slave PWMx OutB Fault Status Level Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Lvl PWMx OutB Fault Status Level @ref LL_HRPWM_Slv_OutFaultLvlTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_OUT_SetBFaultState(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Lvl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_FAULTB_Msk, (((Lvl) & HRPWM_SLV0_OUTR_FAULTB_Val) << HRPWM_SLV0_OUTR_FAULTB_Pos));
}

/**
  * @brief  Slave PWMx OutB Polarity Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Pol PWMx OutB Polarity @ref LL_HRPWM_Slv_OutPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_OUT_SetBPolarity(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_POLB_Msk, (((Pol) & HRPWM_SLV0_OUTR_POLB_Val) << HRPWM_SLV0_OUTR_POLB_Pos));
}

/**
  * @brief  Slave PWMx OutB Polarity and Idle Status Level Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Pol PWMx OutB Polarity @ref LL_HRPWM_Slv_OutPolTypeDef
  * @param  Lvl PWMx OutB Idle Status Level @ref LL_HRPWM_Slv_OutIdleLvlTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetOutputBPolarityAndIdleLevel(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Pol, uint32_t Lvl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_POLB_Msk | HRPWM_SLV0_OUTR_IDLESB_Msk, 
            ((((Pol) & HRPWM_SLV0_OUTR_POLB_Val) << HRPWM_SLV0_OUTR_POLB_Pos) | 
            (((Lvl) & HRPWM_SLV0_OUTR_IDLESB_Val) << HRPWM_SLV0_OUTR_IDLESB_Pos)));
}

/**
  * @brief  Slave PWMx OutA Idle DeadTime Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputAIdleDeadTime(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLA_Msk);
}

/**
  * @brief  Slave PWMx OutA Idle DeadTime Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputAIdleDeadTime(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLA_Msk);
}

/**
  * @brief  Slave PWMx OutA Burst Mode Idle Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputABurstModeIdle(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMA_Msk);
}

/**
  * @brief  Slave PWMx OutA Burst Mode Idle Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputABurstModeIdle(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMA_Msk);
}

/**
  * @brief  Slave PWMx OutA Chopper Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableOutputAChopper(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPA_Msk);
}

/**
  * @brief  Slave PWMx OutA Chopper Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableOutputAChopper(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPA_Msk);
}

/**
  * @brief  Slave PWMx OutA Idle Status Level Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Lvl PWMx OutA Idle Status Level @ref LL_HRPWM_Slv_OutIdleLvlTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_OUT_SetAIdleLevel(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Lvl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_IDLESA_Msk, (((Lvl) & HRPWM_SLV0_OUTR_IDLESA_Val) << HRPWM_SLV0_OUTR_IDLESA_Pos));
}

/**
  * @brief  Slave PWMx OutA Fault Status Level Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Lvl PWMx OutA Fault Status Level @ref LL_HRPWM_Slv_OutFaultLvlTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_OUT_SetAFaultState(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Lvl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_FAULTA_Msk, (((Lvl) & HRPWM_SLV0_OUTR_FAULTA_Val) << HRPWM_SLV0_OUTR_FAULTA_Pos));
}

/**
  * @brief  Slave PWMx OutA Polarity Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Pol PWMx OutA Polarity @ref LL_HRPWM_Slv_OutPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_OUT_SetAPolarity(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_POLA_Msk, (((Pol) & HRPWM_SLV0_OUTR_POLA_Val) << HRPWM_SLV0_OUTR_POLA_Pos));
}

/**
  * @brief  Slave PWMx OutA Polarity and Idle Status Level Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Pol PWMx OutA Polarity @ref LL_HRPWM_Slv_OutPolTypeDef
  * @param  Lvl PWMx OutA Idle Status Level @ref LL_HRPWM_Slv_OutIdleLvlTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetOutputAPolarityAndIdleLevel(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Pol, uint32_t Lvl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.OUTR, 
            HRPWM_SLV0_OUTR_POLA_Msk | HRPWM_SLV0_OUTR_IDLESA_Msk, 
            ((((Pol) & HRPWM_SLV0_OUTR_POLA_Val) << HRPWM_SLV0_OUTR_POLA_Pos) | 
            (((Lvl) & HRPWM_SLV0_OUTR_IDLESA_Val) << HRPWM_SLV0_OUTR_IDLESA_Pos)));
}

/**
  * @brief  Slave PWMx Fault 7 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault7(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT7EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 7 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault7(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT7EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 6 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault6(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT6EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 6 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault6(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT6EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 5 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault5(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT5EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 5 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault5(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT5EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 4 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault4(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT4EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 4 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault4(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT4EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 3 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault3(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT3EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 3 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault3(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT3EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 2 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault2(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT2EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 2 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault2(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT2EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 1 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault1(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT1EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 1 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault1(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT1EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 0 Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFault0(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT0EN_Msk);
}

/**
  * @brief  Slave PWMx Fault 0 Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFault0(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT0EN_Msk);
}

/**
  * @brief  Slave PWMx Fault x Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableFaultX(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, BIT((Fltx) % LL_HRPWM_FLT_NUMS));
}

/**
  * @brief  Slave PWMx Fault x Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableFaultX(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, BIT((Fltx) % LL_HRPWM_FLT_NUMS));
}

/**
  * @brief  Slave PWMx Fault x Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Faults PWMx Fault Number Mask, combination of @ref LL_HRPWM_Slv_FltMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_SetFaultChannel(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Faults)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, LL_HRPWM_FLTR_PWMx_FLTx_EN_MSK, ((Faults) & LL_HRPWM_ALL_FLT_PWM_MASK));
}

/**
  * @brief  Slave PWMx Register Support that System DMA Write into DMADR and Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Reg Register Type Mask @ref LL_HRPWM_Comm_BurstDMASlvRegUpdTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableSysDMAWriteUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Reg)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DMAUR, Reg);
}

/**
  * @brief  Slave PWMx Register Support that System DMA Write into DMADR and Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Reg Register Type Mask @ref LL_HRPWM_Comm_BurstDMASlvRegUpdTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableSysDMAWriteUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Reg)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DMAUR, Reg);
}

/**
  * @brief  Get Slave PWMx Register Support Update Register
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Register Type Mask @ref LL_HRPWM_Comm_BurstDMASlvRegUpdTypeDef
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_GetSysDMAWriteUpdate(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DMAUR, 0x3fffffffUL, 0));
}

/**
  * @brief  Slave PWMx System DMA Data Address Read
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return Slave PWMx System DMA Data Address
  */
__STATIC_INLINE uint32_t* LL_HRPWM_SLV_GetSysDMADataAddr(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t*)(&(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.DMADR));
}

/**
  * @brief  Common ADC Trigger 3 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 3 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger3UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR0, HRPWM_COM_CR0_USRC3_Msk, 
            (((Src) & HRPWM_COM_CR0_USRC3_Val) << HRPWM_COM_CR0_USRC3_Pos));
}

/**
  * @brief  Common ADC Trigger 2 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 2 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger2UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR0, HRPWM_COM_CR0_USRC2_Msk, 
            (((Src) & HRPWM_COM_CR0_USRC2_Val) << HRPWM_COM_CR0_USRC2_Pos));
}

/**
  * @brief  Common ADC Trigger 1 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 1 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger1UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR0, HRPWM_COM_CR0_USRC1_Msk, 
            (((Src) & HRPWM_COM_CR0_USRC1_Val) << HRPWM_COM_CR0_USRC1_Pos));
}

/**
  * @brief  Common ADC Trigger 0 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 0 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger0UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR0, HRPWM_COM_CR0_USRC0_Msk, 
            (((Src) & HRPWM_COM_CR0_USRC0_Val) << HRPWM_COM_CR0_USRC0_Pos));
}

/**
  * @brief  Common ADC Trigger X Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Trigx ADC Trigger Number @ref LL_HRPWM_ADCTrigNumTypeDef (X=0~3)
  * @param  Src ADC Trigger X Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger0To3UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Trigx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR0, HRPWM_COM_CR0_USRC0_Msk << (((Trigx) % 4) * 4), 
            (((Src) & HRPWM_COM_CR0_USRC0_Val) << (HRPWM_COM_CR0_USRC0_Pos + ((Trigx) % 4) * 4)));
}

/**
  * @brief  Common Burst Mode Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableBurstModeRegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_BMUDIS_Msk);
}

/**
  * @brief  Common Burst Mode Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableBurstModeRegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_BMUDIS_Msk);
}

/**
  * @brief  Common PWM7 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM7RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS7_Msk);
}

/**
  * @brief  Common PWM7 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM7RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS7_Msk);
}

/**
  * @brief  Common PWM6 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM6RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS6_Msk);
}

/**
  * @brief  Common PWM6 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM6RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS6_Msk);
}

/**
  * @brief  Common PWM5 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM5RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS5_Msk);
}

/**
  * @brief  Common PWM5 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM5RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS5_Msk);
}

/**
  * @brief  Common PWM4 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM4RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS4_Msk);
}

/**
  * @brief  Common PWM4 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM4RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS4_Msk);
}

/**
  * @brief  Common PWM3 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM3RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS3_Msk);
}

/**
  * @brief  Common PWM3 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM3RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS3_Msk);
}

/**
  * @brief  Common PWM2 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM2RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS2_Msk);
}

/**
  * @brief  Common PWM2 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM2RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS2_Msk);
}

/**
  * @brief  Common PWM1 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM1RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS1_Msk);
}

/**
  * @brief  Common PWM1 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM1RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS1_Msk);
}

/**
  * @brief  Common PWM0 Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM0RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS0_Msk);
}

/**
  * @brief  Common PWM0 Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM0RegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_UDIS0_Msk);
}

/**
  * @brief  Common PWMx Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWMxRegUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR0_UDIS0_Pos));
}

/**
  * @brief  Common PWMx Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWMxRegUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR0_UDIS0_Pos));
}

/**
  * @brief  Common Master PWM Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableMasterPWMRegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_MUDIS_Msk);
}

/**
  * @brief  Common Master PWM Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableMasterPWMRegUpdate(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, HRPWM_COM_CR0_MUDIS_Msk);
}

/**
  * @brief  Common Multi PWM Register Update Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableMultiPWMRegUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR0, ((Pwmxs) & LL_HRPWM_CR0_UPD_DIS_MSK));
}

/**
  * @brief  Common Multi PWM Register Update Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableMultiPWMRegUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR0, ((Pwmxs) & LL_HRPWM_CR0_UPD_DIS_MSK));
}

/**
  * @brief  Common ADC Trigger 3 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 3 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger3EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR1, HRPWM_COM_CR1_TLEN3_Msk, (((Len) & HRPWM_COM_CR1_TLEN3_Val) << HRPWM_COM_CR1_TLEN3_Pos));
}

/**
  * @brief  Common ADC Trigger 2 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 2 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger2EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR1, HRPWM_COM_CR1_TLEN2_Msk, (((Len) & HRPWM_COM_CR1_TLEN2_Val) << HRPWM_COM_CR1_TLEN2_Pos));
}

/**
  * @brief  Common ADC Trigger 1 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 1 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger1EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR1, HRPWM_COM_CR1_TLEN1_Msk, (((Len) & HRPWM_COM_CR1_TLEN1_Val) << HRPWM_COM_CR1_TLEN1_Pos));
}

/**
  * @brief  Common ADC Trigger 0 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 0 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger0EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR1, HRPWM_COM_CR1_TLEN0_Msk, (((Len) & HRPWM_COM_CR1_TLEN0_Val) << HRPWM_COM_CR1_TLEN0_Pos));
}

/**
  * @brief  Common ADC Trigger X Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Trigx ADC Trigger X Number @ref LL_HRPWM_ADCTrigNumTypeDef (X=0~3)
  * @param  Len ADC Trigger X Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger0To3EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Trigx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.CR1, HRPWM_COM_CR1_TLEN0_Msk << (((Trigx) % 4) * 4), 
            (((Len) & HRPWM_COM_CR1_TLEN0_Val) << (HRPWM_COM_CR1_TLEN0_Pos + ((Trigx) % 4) * 4)));
}

/**
  * @brief  Common PWM7 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM7OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP7_Msk);
}

/**
  * @brief  Common PWM7 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM7OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP7_Msk);
}

/**
  * @brief  Common PWM6 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM6OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP6_Msk);
}

/**
  * @brief  Common PWM6 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM6OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP6_Msk);
}

/**
  * @brief  Common PWM5 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM5OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP5_Msk);
}

/**
  * @brief  Common PWM5 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM5OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP5_Msk);
}

/**
  * @brief  Common PWM4 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM4OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP4_Msk);
}

/**
  * @brief  Common PWM4 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM4OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP4_Msk);
}

/**
  * @brief  Common PWM3 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM3OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP3_Msk);
}

/**
  * @brief  Common PWM3 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM3OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP3_Msk);
}

/**
  * @brief  Common PWM2 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM2OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP2_Msk);
}

/**
  * @brief  Common PWM2 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM2OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP2_Msk);
}

/**
  * @brief  Common PWM1 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM1OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP1_Msk);
}

/**
  * @brief  Common PWM1 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM1OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP1_Msk);
}

/**
  * @brief  Common PWM0 Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM0OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP0_Msk);
}

/**
  * @brief  Common PWM0 Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM0OutputSwap(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, HRPWM_COM_CR1_SWP0_Msk);
}

/**
  * @brief  Common PWMx Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableSwapOutputs(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR1_SWP0_Pos));
}

/**
  * @brief  Common PWMx Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableSwapOutputs(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR1_SWP0_Pos));
}

/**
  * @brief  Common Multi PWMx Output Swap Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, not include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableMultiPWMOutputSwap(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR1, ((Pwmxs) & LL_HRPWM_ALL_PWM_MASK) >> 1);
}

/**
  * @brief  Common Multi PWMx Output Swap Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, not include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableMultiPWMOutputSwap(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.CR1, ((Pwmxs) & LL_HRPWM_ALL_PWM_MASK) >> 1);
}

/**
  * @brief  Common PWM7 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM7Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST7_Msk);
}

/**
  * @brief  Common PWM6 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM6Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST6_Msk);
}

/**
  * @brief  Common PWM5 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM5Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST5_Msk);
}

/**
  * @brief  Common PWM4 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM4Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST4_Msk);
}

/**
  * @brief  Common PWM3 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM3Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST3_Msk);
}

/**
  * @brief  Common PWM2 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM2Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST2_Msk);
}

/**
  * @brief  Common PWM1 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM1Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST1_Msk);
}

/**
  * @brief  Common PWM0 Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWM0Counter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_RST0_Msk);
}

/**
  * @brief  Common PWMx Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetPWMxCounter(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR2_RST0_Pos));
}

/**
  * @brief  Common PWMx Software Reset Counter Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Reset has completed
  * @retval 1 Reset hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWMxCounterResetting(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, 
            BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR2_RST0_Pos), 
            (((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR2_RST0_Pos)));
}

/**
  * @brief  Common Master PWM Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetMasterPWMCounter(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_MRST_Msk);
}

/**
  * @brief  Common Master PWM Software Reset Counter Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Reset has completed
  * @retval 1 Reset hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsMasterPWMCounterResetting(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_MRST_Msk, HRPWM_COM_CR2_MRST_Pos));
}

/**
  * @brief  Common Multi PWMx Software Reset Counter Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ResetMultiPWMCounters(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, ((Pwmxs) & LL_HRPWM_ALL_PWM_MASK) << HRPWM_COM_CR2_MRST_Pos);
}

/**
  * @brief  Common Multi PWMx Software Reset Counter Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @retval 0 Reset has completed
  * @retval 1 Reset hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsMultiPWMCountersResetting(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)((!!READ_BIT_SHIFT(HRPWMx->Common.CR2, 
            ((Pwmxs) & LL_HRPWM_ALL_PWM_MASK) << HRPWM_COM_CR2_MRST_Pos, HRPWM_COM_CR2_MRST_Pos)));
}

/**
  * @brief  Common PWM7 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM7(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU7_Msk);
}

/**
  * @brief  Common PWM7 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM7UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU7_Msk, HRPWM_COM_CR2_SWU7_Pos));
}

/**
  * @brief  Common PWM6 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM6(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU6_Msk);
}

/**
  * @brief  Common PWM6 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM6UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU6_Msk, HRPWM_COM_CR2_SWU6_Pos));
}

/**
  * @brief  Common PWM5 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM5(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU5_Msk);
}

/**
  * @brief  Common PWM5 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM5UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU5_Msk, HRPWM_COM_CR2_SWU5_Pos));
}

/**
  * @brief  Common PWM4 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM4(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU4_Msk);
}

/**
  * @brief  Common PWM4 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM4UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU4_Msk, HRPWM_COM_CR2_SWU4_Pos));
}

/**
  * @brief  Common PWM3 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM3(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU3_Msk);
}

/**
  * @brief  Common PWM3 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM3UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU3_Msk, HRPWM_COM_CR2_SWU3_Pos));
}

/**
  * @brief  Common PWM2 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM2(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU2_Msk);
}

/**
  * @brief  Common PWM2 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM2UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU2_Msk, HRPWM_COM_CR2_SWU2_Pos));
}

/**
  * @brief  Common PWM1 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM1(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU1_Msk);
}

/**
  * @brief  Common PWM1 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM1UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU1_Msk, HRPWM_COM_CR2_SWU1_Pos));
}

/**
  * @brief  Common PWM0 Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWM0(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU0_Msk);
}

/**
  * @brief  Common PWM0 Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM0UpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_SWU0_Msk, HRPWM_COM_CR2_SWU0_Pos));
}

/**
  * @brief  Common PWMx Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdatePWMx(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR2_SWU0_Pos));
}

/**
  * @brief  Common PWMx Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWMxUpdateBusy(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, 
            BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR2_SWU0_Pos), 
            (((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_CR2_SWU0_Pos)));
}

/**
  * @brief  Common Master PWM Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SoftwareUpdateMasterPWM(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, HRPWM_COM_CR2_MSWU_Msk);
}

/**
  * @brief  Common Master PWM Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsMasterPWMUpdateBusy(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.CR2, HRPWM_COM_CR2_MSWU_Msk, HRPWM_COM_CR2_MSWU_Pos));
}

/**
  * @brief  Common Multi PWMx Software Update Register Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ForceUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.CR2, ((Pwmxs) & LL_HRPWM_CR2_SW_UPD_MSK));
}

/**
  * @brief  Common Multi PWMx Software Update Register Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmxs Multi PWMx Mask, include Master PWM, combination of @ref LL_HRPWM_PWMMaskTypeDef
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsMultiPWMUpdateBusy(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmxs)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)((!!READ_BIT(HRPWMx->Common.CR2, ((Pwmxs) & LL_HRPWM_CR2_SW_UPD_MSK))));
}

/**
  * @brief  Judge is Common Burst Mode Period Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Burst Mode Period Interrupt Pending
  * @retval 1 is Common Burst Mode Period Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_BMPER(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_BMPER_Msk, HRPWM_COM_ISR_BMPER_Pos));
}

/**
  * @brief  Common Burst Mode Period Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_BMPER(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_BMPER_Msk);
}

/**
  * @brief  Judge is Common Fault 7 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 7 Interrupt Pending
  * @retval 1 is Common Fault 7 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT7(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT7_Msk, HRPWM_COM_ISR_FLT7_Pos));
}

/**
  * @brief  Common Fault 7 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT7(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT7_Msk);
}

/**
  * @brief  Judge is Common Fault 6 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 6 Interrupt Pending
  * @retval 1 is Common Fault 6 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT6(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT6_Msk, HRPWM_COM_ISR_FLT6_Pos));
}

/**
  * @brief  Common Fault 6 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT6(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT6_Msk);
}

/**
  * @brief  Judge is Common Fault 5 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 5 Interrupt Pending
  * @retval 1 is Common Fault 5 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT5(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT5_Msk, HRPWM_COM_ISR_FLT5_Pos));
}

/**
  * @brief  Common Fault 5 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT5(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT5_Msk);
}

/**
  * @brief  Judge is Common Fault 4 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 4 Interrupt Pending
  * @retval 1 is Common Fault 4 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT4(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT4_Msk, HRPWM_COM_ISR_FLT4_Pos));
}

/**
  * @brief  Common Fault 4 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT4(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT4_Msk);
}

/**
  * @brief  Judge is Common Fault 3 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 3 Interrupt Pending
  * @retval 1 is Common Fault 3 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT3(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT3_Msk, HRPWM_COM_ISR_FLT3_Pos));
}

/**
  * @brief  Common Fault 3 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT3(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT3_Msk);
}

/**
  * @brief  Judge is Common Fault 2 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 2 Interrupt Pending
  * @retval 1 is Common Fault 2 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT2(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT2_Msk, HRPWM_COM_ISR_FLT2_Pos));
}

/**
  * @brief  Common Fault 2 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT2(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT2_Msk);
}

/**
  * @brief  Judge is Common Fault 1 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 1 Interrupt Pending
  * @retval 1 is Common Fault 1 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT1(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT1_Msk, HRPWM_COM_ISR_FLT1_Pos));
}

/**
  * @brief  Common Fault 1 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT1(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT1_Msk);
}

/**
  * @brief  Judge is Common Fault 0 Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 0 Interrupt Pending
  * @retval 1 is Common Fault 0 Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLT0(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT0_Msk, HRPWM_COM_ISR_FLT0_Pos));
}

/**
  * @brief  Common Fault 0 Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLT0(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_FLT0_Msk);
}

/**
  * @brief  Judge is Common Fault X Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @retval 0 isn't Common Fault X Interrupt Pending
  * @retval 1 is Common Fault X Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_FLTx(const HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, 
            BIT(((Fltx) % LL_HRPWM_FLT_NUMS) + HRPWM_COM_ISR_FLT0_Pos), 
            (((Fltx) % LL_HRPWM_FLT_NUMS) + HRPWM_COM_ISR_FLT0_Pos)));
}

/**
  * @brief  Common Fault X Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_FLTx(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, BIT(((Fltx) % LL_HRPWM_FLT_NUMS) + HRPWM_COM_ISR_FLT0_Pos));
}

/**
  * @brief  Judge is Common System Fault Interrupt Pending or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 isn't Common System Fault Interrupt Pending
  * @retval 1 is Common System Fault Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsActiveFlag_SYSFLT(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ISR, HRPWM_COM_ISR_SYSFLT_Msk, HRPWM_COM_ISR_SYSFLT_Pos));
}

/**
  * @brief  Common System Fault Interrupt Pending Clear
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ClearFlag_SYSFLT(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ISR, HRPWM_COM_ISR_SYSFLT_Msk);
}

/**
  * @brief  HRPWM Common All Interrupt Pending Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return HRPWM Common All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_GetAllITPending(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT(HRPWMx->Common.ISR, LL_HRPWM_ISR_COM_IT_FLAG_MSK));
}

/**
  * @brief  Common Burst Mode Period Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_BMPERIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_BMPERIE_Msk);
}

/**
  * @brief  Common Burst Mode Period Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_BMPERIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_BMPERIE_Msk);
}

/**
  * @brief  Common Fault 7 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT7IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT7IE_Msk);
}

/**
  * @brief  Common Fault 7 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT7IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT7IE_Msk);
}

/**
  * @brief  Common Fault 6 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT6IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT6IE_Msk);
}

/**
  * @brief  Common Fault 6 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT6IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT6IE_Msk);
}

/**
  * @brief  Common Fault 5 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT5IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT5IE_Msk);
}

/**
  * @brief  Common Fault 5 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT5IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT5IE_Msk);
}

/**
  * @brief  Common Fault 4 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT4IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT4IE_Msk);
}

/**
  * @brief  Common Fault 4 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT4IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT4IE_Msk);
}

/**
  * @brief  Common Fault 3 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT3IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT3IE_Msk);
}

/**
  * @brief  Common Fault 3 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT3IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT3IE_Msk);
}

/**
  * @brief  Common Fault 2 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT2IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT2IE_Msk);
}

/**
  * @brief  Common Fault 2 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT2IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT2IE_Msk);
}

/**
  * @brief  Common Fault 1 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT1IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT1IE_Msk);
}

/**
  * @brief  Common Fault 1 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT1IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT1IE_Msk);
}

/**
  * @brief  Common Fault 0 Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLT0IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT0IE_Msk);
}

/**
  * @brief  Common Fault 0 Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLT0IE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_FLT0IE_Msk);
}

/**
  * @brief  Common Fault X Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_FLTxIE(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, BIT(((Fltx) % LL_HRPWM_FLT_NUMS) + HRPWM_COM_IER_FLT0IE_Pos));
}

/**
  * @brief  Common Fault X Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_FLTxIE(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, BIT(((Fltx) % LL_HRPWM_FLT_NUMS) + HRPWM_COM_IER_FLT0IE_Pos));
}

/**
  * @brief  Common System Fault Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT_SYSFLTIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_SYSFLTIE_Msk);
}

/**
  * @brief  Common System Fault Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT_SYSFLTIE(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, HRPWM_COM_IER_SYSFLTIE_Msk);
}

/**
  * @brief  HRPWM Common All Interrupt Enable Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return HRPWM Common All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_GetAllEnabledIT(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT(HRPWMx->Common.IER, LL_HRPWM_IER_COM_IT_EN_MSK));
}

/**
  * @brief  Common PWM7 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM7OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN7B_Msk);
}

/**
  * @brief  Judge is Common PWM7 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM7 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM7OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN7B_Msk, HRPWM_COM_OENR_OEN7B_Pos));
}

/**
  * @brief  Common PWM7 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM7OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN7A_Msk);
}

/**
  * @brief  Judge is Common PWM7 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM7 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM7OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN7A_Msk, HRPWM_COM_OENR_OEN7A_Pos));
}

/**
  * @brief  Common PWM6 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM6OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN6B_Msk);
}

/**
  * @brief  Judge is Common PWM6 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM6 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM6OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN6B_Msk, HRPWM_COM_OENR_OEN6B_Pos));
}

/**
  * @brief  Common PWM6 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM6OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN6A_Msk);
}

/**
  * @brief  Judge is Common PWM6 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM6 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM6OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN6A_Msk, HRPWM_COM_OENR_OEN6A_Pos));
}

/**
  * @brief  Common PWM5 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM5OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN5B_Msk);
}

/**
  * @brief  Judge is Common PWM5 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM5 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM5OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN5B_Msk, HRPWM_COM_OENR_OEN5B_Pos));
}

/**
  * @brief  Common PWM5 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM5OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN5A_Msk);
}

/**
  * @brief  Judge is Common PWM5 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM5 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM5OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN5A_Msk, HRPWM_COM_OENR_OEN5A_Pos));
}

/**
  * @brief  Common PWM4 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM4OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN4B_Msk);
}

/**
  * @brief  Judge is Common PWM4 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM4 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM4OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN4B_Msk, HRPWM_COM_OENR_OEN4B_Pos));
}

/**
  * @brief  Common PWM4 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM4OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN4A_Msk);
}

/**
  * @brief  Judge is Common PWM4 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM4 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM4OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN4A_Msk, HRPWM_COM_OENR_OEN4A_Pos));
}

/**
  * @brief  Common PWM3 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM3OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN3B_Msk);
}

/**
  * @brief  Judge is Common PWM3 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM3 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM3OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN3B_Msk, HRPWM_COM_OENR_OEN3B_Pos));
}

/**
  * @brief  Common PWM3 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM3OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN3A_Msk);
}

/**
  * @brief  Judge is Common PWM3 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM3 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM3OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN3A_Msk, HRPWM_COM_OENR_OEN3A_Pos));
}

/**
  * @brief  Common PWM2 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM2OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN2B_Msk);
}

/**
  * @brief  Judge is Common PWM2 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM2 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM2OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN2B_Msk, HRPWM_COM_OENR_OEN2B_Pos));
}

/**
  * @brief  Common PWM2 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM2OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN2A_Msk);
}

/**
  * @brief  Judge is Common PWM2 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM2 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM2OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN2A_Msk, HRPWM_COM_OENR_OEN2A_Pos));
}

/**
  * @brief  Common PWM1 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM1OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN1B_Msk);
}

/**
  * @brief  Judge is Common PWM1 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM1 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM1OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN1B_Msk, HRPWM_COM_OENR_OEN1B_Pos));
}

/**
  * @brief  Common PWM1 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM1OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN1A_Msk);
}

/**
  * @brief  Judge is Common PWM1 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM1 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM1OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN1A_Msk, HRPWM_COM_OENR_OEN1A_Pos));
}

/**
  * @brief  Common PWM0 OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM0OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN0B_Msk);
}

/**
  * @brief  Judge is Common PWM0 OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM0 OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM0OutputBEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN0B_Msk, HRPWM_COM_OENR_OEN0B_Pos));
}

/**
  * @brief  Common PWM0 OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWM0OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN0A_Msk);
}

/**
  * @brief  Judge is Common PWM0 OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM0 OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM0OutputAEnabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, HRPWM_COM_OENR_OEN0A_Msk, HRPWM_COM_OENR_OEN0A_Pos));
}

/**
  * @brief  Common PWMx OutB Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWMxOutputB(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0B_Pos));
}

/**
  * @brief  Judge is Common PWMx OutB Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Common PWMx OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWMx OutB is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWMxOutputBEnabled(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, 
            BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0B_Pos), 
            (((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0B_Pos)));
}

/**
  * @brief  Common PWMx OutA Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnablePWMxOutputA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.OENR, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0A_Pos));
}

/**
  * @brief  Judge is Common PWMx OutA Running or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Common PWMx OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWMx OutA is Running
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWMxOutputAEnabled(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.OENR, 
            BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0A_Pos), 
            (((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0A_Pos)));
}

/**
  * @brief  Common Multi PWMx Output Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Multi PWMx Output Start Mask, combination of @ref LL_HRPWM_PWMOutputMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableOutput(HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.OENR, ((Mask) & LL_HRPWM_OENR_OUTx_START_MSK));
}

/**
  * @brief  Common PWM7 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM7OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS7B_Msk);
}

/**
  * @brief  Common PWM7 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutB is Idle
  * @retval 1 Common PWM7 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM7OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS7B_Msk, HRPWM_COM_ODISR_ODIS7B_Pos));
}

/**
  * @brief  Common PWM7 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM7OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS7A_Msk);
}

/**
  * @brief  Common PWM7 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutA is Idle
  * @retval 1 Common PWM7 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM7OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS7A_Msk, HRPWM_COM_ODISR_ODIS7A_Pos));
}

/**
  * @brief  Common PWM6 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM6OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS6B_Msk);
}

/**
  * @brief  Common PWM6 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutB is Idle
  * @retval 1 Common PWM6 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM6OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS6B_Msk, HRPWM_COM_ODISR_ODIS6B_Pos));
}

/**
  * @brief  Common PWM6 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM6OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS6A_Msk);
}

/**
  * @brief  Common PWM6 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutA is Idle
  * @retval 1 Common PWM6 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM6OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS6A_Msk, HRPWM_COM_ODISR_ODIS6A_Pos));
}

/**
  * @brief  Common PWM5 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM5OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS5B_Msk);
}

/**
  * @brief  Common PWM5 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutB is Idle
  * @retval 1 Common PWM5 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM5OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS5B_Msk, HRPWM_COM_ODISR_ODIS5B_Pos));
}

/**
  * @brief  Common PWM5 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM5OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS5A_Msk);
}

/**
  * @brief  Common PWM5 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutA is Idle
  * @retval 1 Common PWM5 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM5OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS5A_Msk, HRPWM_COM_ODISR_ODIS5A_Pos));
}

/**
  * @brief  Common PWM4 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM4OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS4B_Msk);
}

/**
  * @brief  Common PWM4 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutB is Idle
  * @retval 1 Common PWM4 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM4OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS4B_Msk, HRPWM_COM_ODISR_ODIS4B_Pos));
}

/**
  * @brief  Common PWM4 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM4OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS4A_Msk);
}

/**
  * @brief  Common PWM4 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutA is Idle
  * @retval 1 Common PWM4 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM4OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS4A_Msk, HRPWM_COM_ODISR_ODIS4A_Pos));
}

/**
  * @brief  Common PWM3 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM3OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS3B_Msk);
}

/**
  * @brief  Common PWM3 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutB is Idle
  * @retval 1 Common PWM3 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM3OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS3B_Msk, HRPWM_COM_ODISR_ODIS3B_Pos));
}

/**
  * @brief  Common PWM3 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM3OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS3A_Msk);
}

/**
  * @brief  Common PWM3 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutA is Idle
  * @retval 1 Common PWM3 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM3OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS3A_Msk, HRPWM_COM_ODISR_ODIS3A_Pos));
}

/**
  * @brief  Common PWM2 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM2OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS2B_Msk);
}

/**
  * @brief  Common PWM2 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutB is Idle
  * @retval 1 Common PWM2 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM2OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS2B_Msk, HRPWM_COM_ODISR_ODIS2B_Pos));
}

/**
  * @brief  Common PWM2 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM2OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS2A_Msk);
}

/**
  * @brief  Common PWM2 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutA is Idle
  * @retval 1 Common PWM2 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM2OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS2A_Msk, HRPWM_COM_ODISR_ODIS2A_Pos));
}

/**
  * @brief  Common PWM1 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM1OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS1B_Msk);
}

/**
  * @brief  Common PWM1 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutB is Idle
  * @retval 1 Common PWM1 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM1OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS1B_Msk, HRPWM_COM_ODISR_ODIS1B_Pos));
}

/**
  * @brief  Common PWM1 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM1OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS1A_Msk);
}

/**
  * @brief  Common PWM1 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutA is Idle
  * @retval 1 Common PWM1 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM1OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS1A_Msk, HRPWM_COM_ODISR_ODIS1A_Pos));
}

/**
  * @brief  Common PWM0 OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM0OutputB(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS0B_Msk);
}

/**
  * @brief  Common PWM0 OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutB is Idle
  * @retval 1 Common PWM0 OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM0OutputBDisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS0B_Msk, HRPWM_COM_ODISR_ODIS0B_Pos));
}

/**
  * @brief  Common PWM0 OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWM0OutputA(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS0A_Msk);
}

/**
  * @brief  Common PWM0 OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutA is Idle
  * @retval 1 Common PWM0 OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWM0OutputADisabled(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, HRPWM_COM_ODISR_ODIS0A_Msk, HRPWM_COM_ODISR_ODIS0A_Pos));
}

/**
  * @brief  Common PWMx OutB Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWMxOutputB(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0B_Pos));
}

/**
  * @brief  Common PWMx OutB Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Common PWMx OutB is Idle
  * @retval 1 Common PWMx OutB is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWMxOutputBDisabled(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, 
            BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0B_Pos), 
            (((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0B_Pos)));
}

/**
  * @brief  Common PWMx OutA Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisablePWMxOutputA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.ODISR, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0A_Pos));
}

/**
  * @brief  Common PWMx OutA Stop Status Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @retval 0 Common PWMx OutA is Idle
  * @retval 1 Common PWMx OutA is Fault
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsPWMxOutputADisabled(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.ODISR, 
            BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0A_Pos), 
            (((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0A_Pos)));
}

/**
  * @brief  Common Multi PWMx Output Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Multi PWMx Output Stop Mask, combination of @ref LL_HRPWM_PWMOutputMaskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableOutput(HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ODISR, ((Mask) & LL_HRPWM_ODISR_OUTx_STOP_MSK));
}

/**
  * @brief  Common External Event X Fast Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt_x External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EE_EnableFastMode(HRPWM_TypeDef *HRPWMx, uint32_t Evt_x)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(LL_HRPWM_REG_OFFSET(HRPWMx->Common.EECR0, (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), 
            BIT(((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0FAST_Pos));
}

/**
  * @brief  Common External Event X Fast Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt_x External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EE_DisableFastMode(HRPWM_TypeDef *HRPWMx, uint32_t Evt_x)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(LL_HRPWM_REG_OFFSET(HRPWMx->Common.EECR0, (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), 
            BIT(((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0FAST_Pos));
}

/**
  * @brief  Common External Event X Input Active Edge Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt_x External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @param  Edge External Event X Input Active Edge @ref LL_HRPWM_Comm_ExtEvtInputEdgeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EE_SetSensitivity(HRPWM_TypeDef *HRPWMx, uint32_t Evt_x, uint32_t Edge)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(LL_HRPWM_REG_OFFSET(HRPWMx->Common.EECR0, (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)),
            0x3UL << (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SNS_Pos), 
            (((Edge) & 0x3UL) << (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SNS_Pos)));
}

/**
  * @brief  Common External Event X Input Polarity Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt_x External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @param  Pol External Event X Input Polarity @ref LL_HRPWM_Comm_ExtEvtInputPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EE_SetPolarity(HRPWM_TypeDef *HRPWMx, uint32_t Evt_x, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(LL_HRPWM_REG_OFFSET(HRPWMx->Common.EECR0, (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), 
            0x1UL << (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0POL_Pos), 
            (((Pol) & 0x1UL) << (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0POL_Pos)));
}

/**
  * @brief  Common External Event Sample Clock Division Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Div External Event Sample Clock Division
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EE_SetPrescaler(HRPWM_TypeDef *HRPWMx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.EECR2, HRPWM_COM_EECR2_EEVSD_Msk, (((Div) & HRPWM_COM_EECR2_EEVSD_Val) << HRPWM_COM_EECR2_EEVSD_Pos));
}

/**
  * @brief  Common External Event X Filter Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt_x External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @param  Len External Event X Filter Length
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EE_SetFilter(HRPWM_TypeDef *HRPWMx, uint32_t Evt_x, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(LL_HRPWM_REG_OFFSET(HRPWMx->Common.EECR2, (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), 
            0xfUL << (((Evt_x) % 5) * 4 + HRPWM_COM_EECR2_EE0F_Pos), 
            (((Len) & 0xfUL) << (((Evt_x) % 5) * 4 + HRPWM_COM_EECR2_EE0F_Pos)));
}

/**
  * @brief  Common ADC Trigger 0 Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 0 Event, combination of @ref LL_HRPWM_Comm_ADC02TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ConfigADCTrigger0Event(HRPWM_TypeDef *HRPWMx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ADC0R, ((Evt) & 0xFFFFFFFFUL)); 
    WRITE_REG(HRPWMx->Common.ADC0ER, ((Evt) >> 32ULL));
}

/**
  * @brief  Common ADC Trigger 1 Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 1 Event, combination of @ref LL_HRPWM_Comm_ADC13TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ConfigADCTrigger1Event(HRPWM_TypeDef *HRPWMx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ADC1R, ((Evt) & 0xFFFFFFFFUL));
    WRITE_REG(HRPWMx->Common.ADC1ER, ((Evt) >> 32ULL));
}

/**
  * @brief  Common ADC Trigger 2 Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 2 Event, combination of @ref LL_HRPWM_Comm_ADC02TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ConfigADCTrigger2Event(HRPWM_TypeDef *HRPWMx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ADC2R, ((Evt) & 0xFFFFFFFFUL));
    WRITE_REG(HRPWMx->Common.ADC2ER, ((Evt) >> 32ULL));
}

/**
  * @brief  Common ADC Trigger 3 Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 3 Event, combination of @ref LL_HRPWM_Comm_ADC13TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ConfigADCTrigger3Event(HRPWM_TypeDef *HRPWMx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.ADC3R, ((Evt) & 0xFFFFFFFFUL));
    WRITE_REG(HRPWMx->Common.ADC3ER, ((Evt) >> 32ULL));
}

/**
  * @brief  Common ADC Trigger 4 Event Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 4 Event @ref LL_HRPWM_Comm_ADC468TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger4EventSource(HRPWM_TypeDef *HRPWMx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADC4R, HRPWM_COM_ADC4R_ADC4TRG_Msk, 
            (((Evt) & HRPWM_COM_ADC4R_ADC4TRG_Val) << HRPWM_COM_ADC4R_ADC4TRG_Pos));
}

/**
  * @brief  Common ADC Trigger 5 Event Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 5 Event @ref LL_HRPWM_Comm_ADC579TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger5EventSource(HRPWM_TypeDef *HRPWMx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADC4R, HRPWM_COM_ADC4R_ADC5TRG_Msk, 
            (((Evt) & HRPWM_COM_ADC4R_ADC5TRG_Val) << HRPWM_COM_ADC4R_ADC5TRG_Pos));
}

/**
  * @brief  Common ADC Trigger 6 Event Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 6 Event @ref LL_HRPWM_Comm_ADC468TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger6EventSource(HRPWM_TypeDef *HRPWMx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADC4R, HRPWM_COM_ADC4R_ADC6TRG_Msk, 
            (((Evt) &  HRPWM_COM_ADC4R_ADC6TRG_Val) << HRPWM_COM_ADC4R_ADC6TRG_Pos));
}

/**
  * @brief  Common ADC Trigger 7 Event Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 7 Event @ref LL_HRPWM_Comm_ADC579TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger7EventSource(HRPWM_TypeDef *HRPWMx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADC5R, HRPWM_COM_ADC5R_ADC7TRG_Msk, 
            (((Evt) & HRPWM_COM_ADC5R_ADC7TRG_Val) << HRPWM_COM_ADC5R_ADC7TRG_Pos));
}

/**
  * @brief  Common ADC Trigger 8 Event Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 8 Event @ref LL_HRPWM_Comm_ADC468TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger8EventSource(HRPWM_TypeDef *HRPWMx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADC5R, HRPWM_COM_ADC5R_ADC8TRG_Msk, 
            (((Evt) & HRPWM_COM_ADC5R_ADC8TRG_Val) << HRPWM_COM_ADC5R_ADC8TRG_Pos));
}

/**
  * @brief  Common ADC Trigger 9 Event Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt ADC Trigger 9 Event @ref LL_HRPWM_Comm_ADC579TrigEvtSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger9EventSource(HRPWM_TypeDef *HRPWMx, uint32_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADC5R, HRPWM_COM_ADC5R_ADC9TRG_Msk, 
            (((Evt) & HRPWM_COM_ADC5R_ADC9TRG_Val) << HRPWM_COM_ADC5R_ADC9TRG_Pos));
}

/**
  * @brief  Common ADC Trigger X Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Trigx ADC Trigger X Number @ref LL_HRPWM_ADCTrigNumTypeDef (X=4~9)
  * @param  Src ADC Trigger X Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger4To9UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Trigx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCUR, HRPWM_COM_ADCUR_USRC4_Msk << ((((Trigx) % LL_HRPWM_ADC_TRIG_NUMS) - 4) * 4), 
            (((Src) & HRPWM_COM_ADCUR_USRC4_Val) << (HRPWM_COM_ADCUR_USRC4_Pos + (((Trigx) % LL_HRPWM_ADC_TRIG_NUMS) - 4) * 4)));
}

/**
  * @brief  Common ADC Trigger 4 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 4 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger4UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCUR, HRPWM_COM_ADCUR_USRC4_Msk, (((Src) & HRPWM_COM_ADCUR_USRC4_Val) << HRPWM_COM_ADCUR_USRC4_Pos));
}

/**
  * @brief  Common ADC Trigger 5 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 5 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger5UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCUR, HRPWM_COM_ADCUR_USRC5_Msk, (((Src) & HRPWM_COM_ADCUR_USRC5_Val) << HRPWM_COM_ADCUR_USRC5_Pos));
}

/**
  * @brief  Common ADC Trigger 6 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 6 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger6UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCUR, HRPWM_COM_ADCUR_USRC6_Msk, (((Src) & HRPWM_COM_ADCUR_USRC6_Val) << HRPWM_COM_ADCUR_USRC6_Pos));
}

/**
  * @brief  Common ADC Trigger 7 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 7 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger7UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCUR, HRPWM_COM_ADCUR_USRC7_Msk, (((Src) & HRPWM_COM_ADCUR_USRC7_Val) << HRPWM_COM_ADCUR_USRC7_Pos));
}

/**
  * @brief  Common ADC Trigger 8 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 8 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger8UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCUR, HRPWM_COM_ADCUR_USRC8_Msk, (((Src) & HRPWM_COM_ADCUR_USRC8_Val) << HRPWM_COM_ADCUR_USRC8_Pos));
}

/**
  * @brief  Common ADC Trigger 9 Update Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src ADC Trigger 9 Update Source @ref LL_HRPWM_Comm_ADCTrigUpdSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger9UpdateSource(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCUR, HRPWM_COM_ADCUR_USRC9_Msk, (((Src) & HRPWM_COM_ADCUR_USRC9_Val) << HRPWM_COM_ADCUR_USRC9_Pos));
}

/**
  * @brief  Common ADC Trigger X Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Trigx ADC Trigger X Number @ref LL_HRPWM_ADCTrigNumTypeDef (X=4~9)
  * @param  Len ADC Trigger X Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger4To9EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Trigx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCLR, HRPWM_COM_ADCLR_TLEN4_Msk << ((((Trigx) % LL_HRPWM_ADC_TRIG_NUMS) - 4) * 4), 
            (((Len) & HRPWM_COM_ADCLR_TLEN4_Val) << (HRPWM_COM_ADCLR_TLEN4_Pos + ((((Trigx) % LL_HRPWM_ADC_TRIG_NUMS) - 4) * 4))));
}

/**
  * @brief  Common ADC Trigger 4 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 4 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger4EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCLR, HRPWM_COM_ADCLR_TLEN4_Msk, (((Len) & HRPWM_COM_ADCLR_TLEN4_Val) << HRPWM_COM_ADCLR_TLEN4_Pos));
}

/**
  * @brief  Common ADC Trigger 5 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 5 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger5EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCLR, HRPWM_COM_ADCLR_TLEN5_Msk, (((Len) & HRPWM_COM_ADCLR_TLEN5_Val) << HRPWM_COM_ADCLR_TLEN5_Pos));
}

/**
  * @brief  Common ADC Trigger 6 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 6 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger6EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCLR, HRPWM_COM_ADCLR_TLEN6_Msk, (((Len) & HRPWM_COM_ADCLR_TLEN6_Val) << HRPWM_COM_ADCLR_TLEN6_Pos));
}

/**
  * @brief  Common ADC Trigger 7 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 7 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger7EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCLR, HRPWM_COM_ADCLR_TLEN7_Msk, (((Len) & HRPWM_COM_ADCLR_TLEN7_Val) << HRPWM_COM_ADCLR_TLEN7_Pos));
}

/**
  * @brief  Common ADC Trigger 8 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 8 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger8EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCLR, HRPWM_COM_ADCLR_TLEN8_Msk, (((Len) & HRPWM_COM_ADCLR_TLEN8_Val) << HRPWM_COM_ADCLR_TLEN8_Pos));
}

/**
  * @brief  Common ADC Trigger 9 Event Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Len ADC Trigger 9 Event Length @ref LL_HRPWM_Comm_ADCTrigEvtLenTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTrigger9EventLength(HRPWM_TypeDef *HRPWMx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.ADCLR, HRPWM_COM_ADCLR_TLEN9_Msk, (((Len) & HRPWM_COM_ADCLR_TLEN9_Val) << HRPWM_COM_ADCLR_TLEN9_Pos));
}

/**
  * @brief  Common ADC Trigger X Post Scaler Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Tirgx ADC Trigger Number @ref LL_HRPWM_ADCTrigNumTypeDef
  * @param  Scl ADC Trigger X Post Scaler
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetADCTriggerPostScaler(HRPWM_TypeDef *HRPWMx, uint32_t Tirgx, uint32_t Scl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(LL_HRPWM_REG_OFFSET(HRPWMx->Common.ADPSR0, (Tirgx) / 5 % ((LL_HRPWM_ADC_TRIG_NUMS + 4) / 5)), 
            HRPWM_COM_ADPSR0_PSC0_Msk << (((Tirgx) % 5) * 6), (((Scl) & 0x1fUL) << (((Tirgx) % 5) * 6 + HRPWM_COM_ADPSR0_PSC0_Pos)));
}

/**
  * @brief  Common DLL Start
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_StartDLLCalibration(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.DLLCR, HRPWM_COM_DLLCR_DLLSTART_Msk);
}

/**
  * @brief  Common DLL Stop
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_StopDLLCalibration(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.DLLCR, HRPWM_COM_DLLCR_DLLSTART_Msk);
}

/**
  * @brief  Common DLL Current Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Cur DLL Current
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetDLLCurrent(HRPWM_TypeDef *HRPWMx, uint32_t Cur)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.DLLCR, HRPWM_COM_DLLCR_DLLGCP_Msk, (((Cur) & HRPWM_COM_DLLCR_DLLGCP_Val) << HRPWM_COM_DLLCR_DLLGCP_Pos));
}

/**
  * @brief  Common DLL Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableDLL(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.DLLCR, HRPWM_COM_DLLCR_DLLEN_Msk);
}

/**
  * @brief  Common DLL Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableDLL(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.DLLCR, HRPWM_COM_DLLCR_DLLEN_Msk);
}

/**
  * @brief  Common PWMx EventX Source Extended Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt_x PWMx External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @param  Src PWMx EventX Source @ref LL_HRPWM_Comm_ExtEvtXInputSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EE_SetSrc(HRPWM_TypeDef *HRPWMx, uint32_t Evt_x, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(LL_HRPWM_REG_OFFSET(HRPWMx->Common.EECR0, (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), 
        0x3UL << (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos), 
        (((Src) & 0x3UL) << (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos))); 
    MODIFY_REG(HRPWMx->Common.EECER, 0x3UL << (((Evt_x) % 10) * 2), ((((Src) & 0xcUL) >> 0x2UL) << (((Evt_x) % 10) * 2)));
}

/**
  * @brief  Common PWMx EventX Source Extended Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt_x PWMx External Event Number @ref LL_HRPWM_ExtEvtNumTypeDef
  * @return PWMx EventX Source @ref LL_HRPWM_Comm_ExtEvtXInputSrcTypeDef
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_EE_GetSrc(const HRPWM_TypeDef *HRPWMx, uint32_t Evt_x)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)((((READ_BIT_SHIFT(HRPWMx->Common.EECER, 0x3UL << (((Evt_x) % 10) * 2), 
        (((Evt_x) % 10) * 2))) << 2UL) | ((READ_BIT_SHIFT(LL_HRPWM_REG_OFFSET(HRPWMx->Common.EECR0, 
        (Evt_x) / 5 % ((LL_HRPWM_EXT_EVT_NUMS + 4) / 5)), 0x3UL << (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos), 
        (((Evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos))) & 0x3UL)));
}

/**
  * @brief  Common Fault X Input Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @param  Src Common Fault X Input Source @ref LL_HRPWM_Comm_FltXInputSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_SetSrc(HRPWM_TypeDef *HRPWMx, uint32_t Fltx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.FLTINR0, HRPWM_COM_FLTINR0_FLT0SRC_Msk << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4), 
            (((Src) & HRPWM_COM_FLTINR0_FLT0SRC_Val) << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0SRC_Pos)));
}

/**
  * @brief  Common Fault X Input Polarity Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @param  Pol Common Fault X Input Polarity @ref LL_HRPWM_Comm_FltInputPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_SetPolarity(HRPWM_TypeDef *HRPWMx, uint32_t Fltx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.FLTINR0, HRPWM_COM_FLTINR0_FLT0P_Msk << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4), 
            (((Pol) & HRPWM_COM_FLTINR0_FLT0P_Val) << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0P_Pos)));
}

/**
  * @brief  Common Fault X Input Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_LL_HRTIM_FLT_Enable(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.FLTINR0, BIT((((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0E_Pos)));
}

/**
  * @brief  Common Fault X Input Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx PWMx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_LL_HRTIM_FLT_Disable(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.FLTINR0, BIT((((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0E_Pos)));
}

/**
  * @brief  Common Fault Sample Clock Division Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Div Fault Sample Clock Division
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_SetPrescaler(HRPWM_TypeDef *HRPWMx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.FLTINR1, HRPWM_COM_FLTINR1_FLTSD_Msk, 
            (((Div) & HRPWM_COM_FLTINR1_FLTSD_Val) << HRPWM_COM_FLTINR1_FLTSD_Pos));
}

/**
  * @brief  Common Fault X Filter Length Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @param  Len Fault X Filter Length
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_SetFilter(HRPWM_TypeDef *HRPWMx, uint32_t Fltx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(LL_HRPWM_REG_OFFSET(HRPWMx->Common.FLTINR1, (Fltx) / 6 % ((LL_HRPWM_FLT_NUMS + 5) / 6)), 
            HRPWM_COM_FLTINR1_FLT0F_Msk << (((Fltx) % 6) * 4), 
            (((Len) & 0xfUL) << (((Fltx) % 6) * 4 + HRPWM_COM_FLTINR1_FLT0F_Pos)));
}

/**
  * @brief  Common Fault X Counter Reset Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @param  Mode Fault X Counter Reset Mode @ref LL_HRPWM_Comm_FltCntrRstModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_SetResetMode(HRPWM_TypeDef *HRPWMx, uint32_t Fltx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.FLTINR2, HRPWM_COM_FLTINR2_FLT0RSTM_Msk << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4), 
            (((Mode) & HRPWM_COM_FLTINR2_FLT0RSTM_Val) << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0RSTM_Pos)));
}

/**
  * @brief  Common Fault X Counter Reset
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_ResetCounter(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.FLTINR2, BIT((((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0CRES_Pos)));
}

/**
  * @brief  Judge is Common Fault X Counter Resetting or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @retval 0 Common Fault X Counter isn't Resetting
  * @retval 1 Common Fault X Counter is Resetting
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_FLT_IsCounterResetting(const HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.FLTINR2, 
            BIT((((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0CRES_Pos)), 
            (((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0CRES_Pos)));
}

/**
  * @brief  Common Fault X Blank Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @param  Src Fault X Blank Source @ref LL_HRPWM_Comm_FltBlkSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_SetBlankingSrc(HRPWM_TypeDef *HRPWMx, uint32_t Fltx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.FLTINR2, HRPWM_COM_FLTINR2_FLT0BLKS_Msk << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4), 
            (((Src) & HRPWM_COM_FLTINR2_FLT0BLKS_Val) << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0BLKS_Pos)));
}

/**
  * @brief  Common Fault X Blank Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_EnableBlanking(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.FLTINR2, BIT((((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0BLKE_Pos)));
}

/**
  * @brief  Common Fault X Blank Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_DisableBlanking(HRPWM_TypeDef *HRPWMx, uint32_t Fltx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.FLTINR2, BIT((((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0BLKE_Pos)));
}

/**
  * @brief  Common Fault X Counter Threshold Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Fltx Fault Number @ref LL_HRPWM_FltNumTypeDef
  * @param  Thres Fault X Counter Threshold
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_FLT_SetCounterThreshold(HRPWM_TypeDef *HRPWMx, uint32_t Fltx, uint32_t Thres)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.FLTINR3, HRPWM_COM_FLTINR3_FLT0CNT_Msk << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4), 
            (((Thres) & HRPWM_COM_FLTINR3_FLT0CNT_Val) << (((Fltx) % LL_HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR3_FLT0CNT_Pos)));
}

/**
  * @brief  Judge is Common Burst Mode Active or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common Burst Mode is Inactive
  * @retval 1 Common Burst Mode is Active
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_BM_GetStatus(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMSTAT_Msk, HRPWM_COM_BMCR_BMSTAT_Pos));
}

/**
  * @brief  Common Burst Mode Force Exit
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_ForceExitBurstMode(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMEXIT_Msk);
}

/**
  * @brief  Judge is Common Burst Mode Exiting or not
  * @param  HRPWMx Specifies HRPWM peripheral
  * @retval 0 Common Burst Mode isn't Exiting
  * @retval 1 Common Burst Mode is Exiting
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsBurstModeExiting(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMEXIT_Msk, HRPWM_COM_BMCR_BMEXIT_Pos));
}

/**
  * @brief  Common PWM7 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM7CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS7_Msk);
}

/**
  * @brief  Common PWM7 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM7CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS7_Msk);
}

/**
  * @brief  Common PWM6 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM6CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS6_Msk);
}

/**
  * @brief  Common PWM6 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM6CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS6_Msk);
}

/**
  * @brief  Common PWM5 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM5CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS5_Msk);
}

/**
  * @brief  Common PWM5 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM5CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS5_Msk);
}

/**
  * @brief  Common PWM4 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM4CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS4_Msk);
}

/**
  * @brief  Common PWM4 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM4CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS4_Msk);
}

/**
  * @brief  Common PWM3 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM3CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS3_Msk);
}

/**
  * @brief  Common PWM3 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM3CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS3_Msk);
}

/**
  * @brief  Common PWM2 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM2CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS2_Msk);
}

/**
  * @brief  Common PWM2 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM2CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS2_Msk);
}

/**
  * @brief  Common PWM1 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM1CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS1_Msk);
}

/**
  * @brief  Common PWM1 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM1CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS1_Msk);
}

/**
  * @brief  Common PWM0 Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWM0CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS0_Msk);
}

/**
  * @brief  Common PWM0 Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWM0CounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMDIS0_Msk);
}

/**
  * @brief  Common PWMx Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePWMxCounterStop(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_BMCR_BMDIS0_Pos));
}

/**
  * @brief  Common PWMx Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePWMxCounterStop(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) + HRPWM_COM_BMCR_BMDIS0_Pos));
}

/**
  * @brief  Common Master PWM Counter Stop In Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnableMasterPWMCounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_MBMDIS_Msk);
}

/**
  * @brief  Common Master PWM Counter Stop In Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisableMasterPWMCounterStop(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_MBMDIS_Msk);
}

/**
  * @brief  Common Burst Mode Trigger Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mode Burst Mode Trigger Mode @ref LL_HRPWM_Comm_BurstTrigModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_SetTrigMode(HRPWM_TypeDef *HRPWMx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMTM_Msk, (((Mode) & HRPWM_COM_BMCR_BMTM_Val) << HRPWM_COM_BMCR_BMTM_Pos));
}

/**
  * @brief  Common Burst Mode Trigger Mode Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Burst Mode Trigger Mode @ref LL_HRPWM_Comm_BurstTrigModeTypeDef
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_BM_GetTrigMode(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMTM_Msk, HRPWM_COM_BMCR_BMTM_Pos));
}

/**
  * @brief  Common Burst Mode Preload Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_EnablePreload(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMPREN_Msk);
}

/**
  * @brief  Common Burst Mode Preload Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_DisablePreload(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMPREN_Msk);
}

/**
  * @brief  Common Burst Mode Clock Prescaler Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Scl Burst Mode Clock Prescaler @ref LL_HRPWM_Comm_BurstClkPresclTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_SetPrescaler(HRPWM_TypeDef *HRPWMx, uint32_t Scl)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMPRSC_Msk, (((Scl) & HRPWM_COM_BMCR_BMPRSC_Val) << HRPWM_COM_BMCR_BMPRSC_Pos));
}

/**
  * @brief  Common Burst Mode Clock Source Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Src Burst Mode Clock Source @ref LL_HRPWM_Comm_BurstClkSrcTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_SetClockSrc(HRPWM_TypeDef *HRPWMx, uint32_t Src)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMCLK_Msk, (((Src) & HRPWM_COM_BMCR_BMCLK_Val) << HRPWM_COM_BMCR_BMCLK_Pos));
}

/**
  * @brief  Common Burst Work Mode Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mode Burst Work Mode @ref LL_HRPWM_WorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_SetMode(HRPWM_TypeDef *HRPWMx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    MODIFY_REG(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BMOM_Msk, (((Mode) & HRPWM_COM_BMCR_BMOM_Val) << HRPWM_COM_BMCR_BMOM_Pos));
}

/**
  * @brief  Common Burst Mode Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_Enable(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BME_Msk);
}

/**
  * @brief  Common Burst Mode Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_Disable(HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.BMCR, HRPWM_COM_BMCR_BME_Msk);
}

/**
  * @brief  Common Burst Mode Trigger Event Enable Config
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Evt Burst Mode Trigger Event @ref LL_HRPWM_Comm_BurstTrigEvtTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_SetTrigEvt(HRPWM_TypeDef *HRPWMx, uint64_t Evt)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.BMTRGR0, ((Evt) & 0xFFFFFFFFUL)); 
    WRITE_REG(HRPWMx->Common.BMTRGR1, ((Evt) >> 32ULL));
}

/**
  * @brief  Common Burst Mode Period Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Prd Burst Mode Period
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_SetPeriod(HRPWM_TypeDef *HRPWMx, uint32_t Prd)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.BMPER, ((Prd) & HRPWM_COM_BMPER_BMPER_Val));
}

/**
  * @brief  Common Burst Mode Compare Value Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Val Burst Mode Compare Value
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_BM_SetCompare(HRPWM_TypeDef *HRPWMx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.BMCMPR, ((Val) & HRPWM_COM_BMCMPR_BMCMP_Val));
}

/**
  * @brief  Common Burst DMA Master PWM Register Update Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Reg_upd Master PWM Register Update Mask @ref LL_HRPWM_Comm_BurstDMAMstRegUpdTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetBurstDMAMasterPWMRegUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Reg_upd)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.BDMUPR, Reg_upd);
}

/**
  * @brief  Common Burst DMA Slave PWMx Register Update Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Reg_upd Slave PWMx Register Update Mask @ref LL_HRPWM_Comm_BurstDMASlvRegUpdTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetBurstDMASlavePWMxRegUpdate(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Reg_upd)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(LL_HRPWM_REG_OFFSET(HRPWMx->Common.BDUPR0, (Pwmx) % LL_HRPWM_PWMx_NUMS), Reg_upd);
}

/**
  * @brief  Common Burst DMA Write Address Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Addr Burst DMA Write Address
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetBurstDMAWriteAddress(HRPWM_TypeDef *HRPWMx, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.BDMWADR, Addr);
}

/**
  * @brief  Common Burst DMA Write Address Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Burst DMA Write Address
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_GetBurstDMAWriteAddress(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.BDMWADR, HRPWM_COM_BDMWADR_BDMADR_Msk, HRPWM_COM_BDMWADR_BDMADR_Pos));
}

/**
  * @brief  Common Burst DMA Read Address Set
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Addr Burst DMA Read Address
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_SetBurstDMAReadAddress(HRPWM_TypeDef *HRPWMx, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    WRITE_REG(HRPWMx->Common.BDMADR, Addr);
}

/**
  * @brief  Common Burst DMA Read Address Get
  * @param  HRPWMx Specifies HRPWM peripheral
  * @return Burst DMA Write Address
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_GetBurstDMAReadAddress(const HRPWM_TypeDef *HRPWMx)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    return (uint32_t)(READ_BIT_SHIFT(HRPWMx->Common.BDMADR, HRPWM_COM_BDMADR_BDMADR_Msk, HRPWM_COM_BDMADR_BDMADR_Pos));
}
/**
  * @}
  */ /* HRPWM_LL_EF_Configuration */

/** @defgroup HRPWM_LL_EF_IT_Management LL HRPWM Interrupt Management
  * @brief LL HRPWM Interrupt Management
  * @{
  */

/**
  * @brief  HRPWM Master Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Mask to enable @ref LL_HRPWM_MST_MDIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_EnableIT(HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Master.MDIER, Mask);
}

/**
  * @brief  HRPWM Master Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Mask to disable @ref LL_HRPWM_MST_MDIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_MST_DisableIT(HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Master.MDIER, Mask);
}

/**
  * @brief  Check if HRPWM Master Interrupt is enabled or disabled
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Mask to check @ref LL_HRPWM_MST_MDIER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_HRPWM_MST_IsEnabledIT(const HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(HRPWMx->Master.MDIER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  HRPWM Slave PWMx Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mask Mask to enable @ref LL_HRPWM_SLV_PWMDIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_EnableIT(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, Mask);
}

/**
  * @brief  HRPWM Slave PWMx Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mask Mask to disable @ref LL_HRPWM_SLV_PWMDIER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_SLV_DisableIT(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, Mask);
}

/**
  * @brief  Check if HRPWM Slave PWMx Interrupt is enabled or disabled
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Pwmx PWMx Number @ref LL_HRPWM_PWMIdxTypeDef
  * @param  Mask Mask to check @ref LL_HRPWM_SLV_PWMDIER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_HRPWM_SLV_IsEnabledIT(const HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMDIER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  HRPWM Common Interrupt Enable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Mask to enable @ref LL_HRPWM_COM_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_EnableIT(HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    SET_BIT(HRPWMx->Common.IER, Mask);
}

/**
  * @brief  Common Interrupt Disable
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Mask to disable @ref LL_HRPWM_COM_IER_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_HRPWM_COM_DisableIT(HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_HRPWM_ALL_INSTANCE(HRPWMx));

    CLEAR_BIT(HRPWMx->Common.IER, Mask);
}

/**
  * @brief  Check if HRPWM Common Interrupt is enabled or disabled
  * @param  HRPWMx Specifies HRPWM peripheral
  * @param  Mask Mask to check @ref LL_HRPWM_COM_IER_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_HRPWM_COM_IsEnabledIT(const HRPWM_TypeDef *HRPWMx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(HRPWMx->Common.IER, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @}
  */ /* HRPWM_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* HRPWM_LL_Exported_Functions */


/**
  * @}
  */ /* HRPWM_LL */

#endif /* HRPWM */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_HRPWM_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

