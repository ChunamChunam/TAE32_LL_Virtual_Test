/**
  ******************************************************************************
  * @file    tae32g58xx_ll_qei.h
  * @author  Tai-Action SD Team
  * @brief   Header file for QEI LL module
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
#ifndef _TAE32G58XX_LL_QEI_H_
#define _TAE32G58XX_LL_QEI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(QEI0) || defined(QEI1) || defined(QEI2)

/** @defgroup QEI_LL QEI LL
  * @brief    QEI LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup QEI_LL_Exported_Constants QEI LL Exported Constants
  * @brief    QEI LL Exported Constants
  * @{
  */

/** @defgroup QEI_LL_EC_Information LL QEI Information
  * @brief LL QEI Information
  * @{
  */

/**
  * @brief LL QEI IENR Interrupt Enable Mask Definition
  */
#define LL_QEI_IENR_ITEnMskTypeDef                          uint32_t

#define LL_QEI_IENR_CDS                        (QEI0_IENR_CDS_Msk)                  /*!< CDS Mask                 */
#define LL_QEI_IENR_PRS                        (QEI0_IENR_PRS_Msk)                  /*!< PRS Mask                 */
#define LL_QEI_IENR_PIS                        (QEI0_IENR_PIS_Msk)                  /*!< PIS Mask                 */
#define LL_QEI_IENR_UTO                        (QEI0_IENR_UTO_Msk)                  /*!< UTO Mask                 */
#define LL_QEI_IENR_IEL                        (QEI0_IENR_IEL_Msk)                  /*!< IEL Mask                 */
#define LL_QEI_IENR_PCM                        (QEI0_IENR_PCM_Msk)                  /*!< PCM Mask                 */
#define LL_QEI_IENR_PCO                        (QEI0_IENR_PCO_Msk)                  /*!< PCO Mask                 */
#define LL_QEI_IENR_PCU                        (QEI0_IENR_PCU_Msk)                  /*!< PCU Mask                 */
#define LL_QEI_IENR_QDC                        (QEI0_IENR_QDC_Msk)                  /*!< QDC Mask                 */
#define LL_QEI_IENR_QPE                        (QEI0_IENR_QPE_Msk)                  /*!< QPE Mask                 */
#define LL_QEI_IENR_PCE                        (QEI0_IENR_PCE_Msk)                  /*!< PCE Mask                 */

#define LL_QEI_IENR_IT_EN_MSK                               ((QEI0_IENR_CDS_Msk               | QEI0_IENR_PRS_Msk               | \
                                                              QEI0_IENR_PIS_Msk               | QEI0_IENR_UTO_Msk               | \
                                                              QEI0_IENR_IEL_Msk               | QEI0_IENR_PCM_Msk               | \
                                                              QEI0_IENR_PCO_Msk               | QEI0_IENR_PCU_Msk               | \
                                                              QEI0_IENR_QDC_Msk               | QEI0_IENR_QPE_Msk               | \
                                                              QEI0_IENR_PCE_Msk               ))

/**
  * @brief LL QEI STSR Interrupt Pending Mask Definition
  */
#define LL_QEI_STSR_ITPendingMskTypeDef                     uint32_t

#define LL_QEI_STSR_CDS                        (QEI0_STSR_CDS_Msk)                  /*!< CDS Mask                 */
#define LL_QEI_STSR_PRS                        (QEI0_STSR_PRS_Msk)                  /*!< PRS Mask                 */
#define LL_QEI_STSR_PIS                        (QEI0_STSR_PIS_Msk)                  /*!< PIS Mask                 */
#define LL_QEI_STSR_UTO                        (QEI0_STSR_UTO_Msk)                  /*!< UTO Mask                 */
#define LL_QEI_STSR_IEL                        (QEI0_STSR_IEL_Msk)                  /*!< IEL Mask                 */
#define LL_QEI_STSR_PCM                        (QEI0_STSR_PCM_Msk)                  /*!< PCM Mask                 */
#define LL_QEI_STSR_PCO                        (QEI0_STSR_PCO_Msk)                  /*!< PCO Mask                 */
#define LL_QEI_STSR_PCU                        (QEI0_STSR_PCU_Msk)                  /*!< PCU Mask                 */
#define LL_QEI_STSR_QDC                        (QEI0_STSR_QDC_Msk)                  /*!< QDC Mask                 */
#define LL_QEI_STSR_PHE                        (QEI0_STSR_PHE_Msk)                  /*!< PHE Mask                 */
#define LL_QEI_STSR_PCE                        (QEI0_STSR_PCE_Msk)                  /*!< PCE Mask                 */

#define LL_QEI_STSR_IT_FLAG_MSK                             ((QEI0_STSR_CDS_Msk               | QEI0_STSR_PRS_Msk               | \
                                                              QEI0_STSR_PIS_Msk               | QEI0_STSR_UTO_Msk               | \
                                                              QEI0_STSR_IEL_Msk               | QEI0_STSR_PCM_Msk               | \
                                                              QEI0_STSR_PCO_Msk               | QEI0_STSR_PCU_Msk               | \
                                                              QEI0_STSR_QDC_Msk               | QEI0_STSR_PHE_Msk               | \
                                                              QEI0_STSR_PCE_Msk               ))

/**
  * @}
  */ /* QEI_LL_EC_Information */



/** @defgroup QEI_LL_EC_Configuration LL QEI Configuration
  * @brief LL QEI Configuration 
  * @{
  */

/**
  * @brief QEI Direction Counter Mode Definition
  */
#define LL_QEI_DirCntModeTypeDef                      LL_RSV_DATA_TYPE    

#define LL_QEI_DIR_CNT_MODE0                          (0UL)                /*!< QEI Direction Counter Mode 0                     */
#define LL_QEI_DIR_CNT_MODE1                          (1UL)                /*!< QEI Direction Counter Mode 1                     */

#define IS_LL_QEI_DIR_CNT(__VAL__)                    (((__VAL__) == LL_QEI_DIR_CNT_MODE0) || \
                                                       ((__VAL__) == LL_QEI_DIR_CNT_MODE1) )

/**
  * @brief QEI Position Counter Work Mode Definition
  */
#define LL_QEI_PosCntWorkModeTypeDef                  LL_RSV_DATA_TYPE    

#define LL_QEI_POS_CNT_WORK_MODE_QUAD                 (0UL)                /*!< QEI Position Counter Work Mode Quadrature        */
#define LL_QEI_POS_CNT_WORK_MODE_DIR                  (1UL)                /*!< QEI Position Counter Work Mode Direction         */
#define LL_QEI_POS_CNT_WORK_MODE_UP                   (2UL)                /*!< QEI Position Counter Work Mode Up                */
#define LL_QEI_POS_CNT_WORK_MODE_DOWN                 (3UL)                /*!< QEI Position Counter Work Mode Down              */

#define IS_LL_QEI_POS_CNT_WORK_MODE(__VAL__)          (((__VAL__) == LL_QEI_POS_CNT_WORK_MODE_QUAD) || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_WORK_MODE_DIR)  || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_WORK_MODE_UP)   || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_WORK_MODE_DOWN) )

/**
  * @brief QEI Position Counter Clock Rate Mode Definition
  */
#define LL_QEI_ClkRateModeTypeDef                     LL_RSV_DATA_TYPE    

#define LL_QEI_CLK_RATE_MODE_X1                       (0UL)                /*!< QEI Position Counter Clock Rate Mode X1          */
#define LL_QEI_CLK_RATE_MODE_X2                       (1UL)                /*!< QEI Position Counter Clock Rate Mode X2          */

#define IS_LL_QEI_CLK_RATE_MODE(__VAL__)              (((__VAL__) == LL_QEI_CLK_RATE_MODE_X1) || \
                                                       ((__VAL__) == LL_QEI_CLK_RATE_MODE_X2) )

/**
  * @brief QEI QEA/QEB/Index Input Polarity Definition
  */
#define LL_QEI_InputPolTypeDef                        LL_RSV_DATA_TYPE    

#define LL_QEI_INPUT_POL_ACT_HIGH                     (0UL)                /*!< QEI QEA/QEB/Index Input Polarity Active High     */
#define LL_QEI_INPUT_POL_ACT_LOW                      (1UL)                /*!< QEI QEA/QEB/Index Input Polarity Active Low      */

#define IS_LL_QEI_INPUT_POL_ACT(__VAL__)              (((__VAL__) == LL_QEI_INPUT_POL_ACT_HIGH) || \
                                                       ((__VAL__) == LL_QEI_INPUT_POL_ACT_LOW)  )

/**
  * @brief QEI Position Counter Reset Mode Definition
  * @note  Up and Down Overflow Reset are included in every mode
  */
#define LL_QEI_PosCntRstModeTypeDef                   LL_RSV_DATA_TYPE    

#define LL_QEI_POS_CNT_RST_MODE_EVERY_IDX             (0UL)                /*!< QEI Position Counter Reset Mode Every Index      */
#define LL_QEI_POS_CNT_RST_MODE_MAX                   (1UL)                /*!< QEI Position Counter Reset Mode MAX              */
#define LL_QEI_POS_CNT_RST_MODE_FIRDT_IDX             (2UL)                /*!< QEI Position Counter Reset Mode First Index      */
#define LL_QEI_POS_CNT_RST_MODE_TMR_EVT               (3UL)                /*!< QEI Position Counter Reset Mode Timer Event      */

#define IS_LL_QEI_POS_CNT_RST_MODE(__VAL__)           (((__VAL__) == LL_QEI_POS_CNT_RST_MODE_EVERY_IDX) || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_RST_MODE_MAX)       || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_RST_MODE_FIRDT_IDX) || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_RST_MODE_TMR_EVT)   )

/**
  * @brief QEI Position Counter Index Initial Edge Definition
  */
#define LL_QEI_PosCntIdxInitEdgeTypeDef               LL_RSV_DATA_TYPE    

#define LL_QEI_POS_CNT_INIT_IDX_EDGE_DIS              (1UL)                /*!< QEI Position Counter Index Initial Edge Disable  */
#define LL_QEI_POS_CNT_INIT_IDX_EDGE_RISING           (2UL)                /*!< QEI Position Counter Index Initial Edge Rising   */
#define LL_QEI_POS_CNT_INIT_IDX_EDGE_FALLING          (3UL)                /*!< QEI Position Counter Index Initial Edge Falling  */

#define IS_LL_QEI_POS_CNT_INIT_IDX_EDGE(__VAL__)      (((__VAL__) == LL_QEI_POS_CNT_INIT_IDX_EDGE_DIS)     || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_INIT_IDX_EDGE_RISING)  || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_INIT_IDX_EDGE_FALLING) )

/**
  * @brief QEI Position Counter Index Latch Edge Definition
  */
#define LL_QEI_PosCntIdxLatchEdgeTypeDef              LL_RSV_DATA_TYPE    

#define LL_QEI_POS_CNT_LATCH_IDX_EDGE_DIS             (0UL)                /*!< QEI Position Counter Index Latch Edge Disable    */
#define LL_QEI_POS_CNT_LATCH_IDX_EDGE_RISING          (1UL)                /*!< QEI Position Counter Index Latch Edge Rising     */
#define LL_QEI_POS_CNT_LATCH_IDX_EDGE_FALLING         (2UL)                /*!< QEI Position Counter Index Latch Edge Falling    */
#define LL_QEI_POS_CNT_LATCH_IDX_EDGE_FIRST           (3UL)                /*!< QEI Position Counter Index Latch Edge First Quad */

#define IS_LL_QEI_POS_CNT_LATCH_IDX_EDGE(__VAL__)     (((__VAL__) == LL_QEI_POS_CNT_LATCH_IDX_EDGE_DIS)     || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_LATCH_IDX_EDGE_RISING)  || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_LATCH_IDX_EDGE_FALLING) || \
                                                       ((__VAL__) == LL_QEI_POS_CNT_LATCH_IDX_EDGE_FIRST)   )

/**
  * @brief QEI Capture Event Division Definition
  */
#define LL_QEI_CapEvtDivTypeDef                       LL_RSV_DATA_TYPE    

#define LL_QEI_CAP_EVT_DIV_1                          (0UL)                /*!< QEI Capture Event Division 1                     */
#define LL_QEI_CAP_EVT_DIV_2                          (1UL)                /*!< QEI Capture Event Division 2                     */
#define LL_QEI_CAP_EVT_DIV_4                          (2UL)                /*!< QEI Capture Event Division 4                     */
#define LL_QEI_CAP_EVT_DIV_8                          (3UL)                /*!< QEI Capture Event Division 8                     */
#define LL_QEI_CAP_EVT_DIV_16                         (4UL)                /*!< QEI Capture Event Division 16                    */
#define LL_QEI_CAP_EVT_DIV_32                         (5UL)                /*!< QEI Capture Event Division 32                    */
#define LL_QEI_CAP_EVT_DIV_64                         (6UL)                /*!< QEI Capture Event Division 64                    */
#define LL_QEI_CAP_EVT_DIV_128                        (7UL)                /*!< QEI Capture Event Division 128                   */
#define LL_QEI_CAP_EVT_DIV_256                        (8UL)                /*!< QEI Capture Event Division 256                   */
#define LL_QEI_CAP_EVT_DIV_512                        (9UL)                /*!< QEI Capture Event Division 512                   */
#define LL_QEI_CAP_EVT_DIV_1024                       (10UL)               /*!< QEI Capture Event Division 1024                  */
#define LL_QEI_CAP_EVT_DIV_2048                       (11UL)               /*!< QEI Capture Event Division 2048                  */

#define IS_LL_QEI_CAP_EVT_DIV(__VAL__)                (((__VAL__) == LL_QEI_CAP_EVT_DIV_1)    || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_2)    || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_4)    || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_8)    || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_16)   || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_32)   || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_64)   || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_128)  || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_256)  || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_512)  || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_1024) || \
                                                       ((__VAL__) == LL_QEI_CAP_EVT_DIV_2048) )

/**
  * @brief QEI Capture Timer Clock Division Definition
  */
#define LL_QEI_CapTmrClkDivTypeDef                    LL_RSV_DATA_TYPE    

#define LL_QEI_CAP_TMR_CLK_DIV_1                      (0UL)                /*!< QEI Capture Timer Clock Division 1               */
#define LL_QEI_CAP_TMR_CLK_DIV_2                      (1UL)                /*!< QEI Capture Timer Clock Division 2               */
#define LL_QEI_CAP_TMR_CLK_DIV_4                      (2UL)                /*!< QEI Capture Timer Clock Division 4               */
#define LL_QEI_CAP_TMR_CLK_DIV_8                      (3UL)                /*!< QEI Capture Timer Clock Division 8               */
#define LL_QEI_CAP_TMR_CLK_DIV_16                     (4UL)                /*!< QEI Capture Timer Clock Division 16              */
#define LL_QEI_CAP_TMR_CLK_DIV_32                     (5UL)                /*!< QEI Capture Timer Clock Division 32              */
#define LL_QEI_CAP_TMR_CLK_DIV_64                     (6UL)                /*!< QEI Capture Timer Clock Division 64              */
#define LL_QEI_CAP_TMR_CLK_DIV_128                    (7UL)                /*!< QEI Capture Timer Clock Division 128             */

#define IS_LL_QEI_CAP_TMR_CLK_DIV(__VAL__)            (((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_1)   || \
                                                       ((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_2)   || \
                                                       ((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_4)   || \
                                                       ((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_8)   || \
                                                       ((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_16)  || \
                                                       ((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_32)  || \
                                                       ((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_64)  || \
                                                       ((__VAL__) == LL_QEI_CAP_TMR_CLK_DIV_128) )

/**
  * @brief QEI Capture Latch Mode Definition
  */
#define LL_QEI_CapLatchModeTypeDef                    LL_RSV_DATA_TYPE    

#define LL_QEI_CAP_LATCH_MODE_CPU_READ                (0UL)                /*!< QEI Capture Latch Mode CPU Read                  */
#define LL_QEI_CAP_LATCH_MODE_TMR_TO                  (1UL)                /*!< QEI Capture Latch Mode Timer Timeout             */

#define IS_LL_QEI_CAP_LATCH_MODE(__VAL__)             (((__VAL__) == LL_QEI_CAP_LATCH_MODE_CPU_READ) || \
                                                       ((__VAL__) == LL_QEI_CAP_LATCH_MODE_TMR_TO)   )

/**
  * @brief QEI Direction First Index Status Definition
  */
#define LL_QEI_DirFstIdxStaTypeDef                    LL_RSV_DATA_TYPE

#define LL_QEI_DIR_FIRST_IDX_STS_REV                  (0UL)                /*!< Motor direction is reverse when the first index   \
                                                                                quadrature pulse is valid                        */
#define LL_QEI_DIR_FIRST_IDX_STS_FWD                  (1UL)                /*!< Motor direction is forward when the first index   \
                                                                                quadrature pulse is valid                        */

#define IS_LL_QEI_DIR_FIRST_IDX_STS(__VAL__)          (((__VAL__) == LL_QEI_DIR_FIRST_IDX_STS_REV) || \
                                                       ((__VAL__) == LL_QEI_DIR_FIRST_IDX_STS_FWD)   )

/**
  * @brief QEI Direction Index Latch Status Definition
  */
#define LL_QEI_DirIdxLchStaTypeDef                    LL_RSV_DATA_TYPE

#define LL_QEI_DIR_IDX_LCH_STS_REV                    (0UL)                /*!< Motor direction is reverse when each index        \
                                                                                quadrature pulse is valid                        */
#define LL_QEI_DIR_IDX_LCH_STS_FWD                    (1UL)                /*!< Motor direction is forward when each index        \
                                                                                quadrature pulse is valid                        */

#define IS_LL_QEI_DIR_IDX_LCH_STS(__VAL__)            (((__VAL__) == LL_QEI_DIR_IDX_LCH_STS_REV) || \
                                                       ((__VAL__) == LL_QEI_DIR_IDX_LCH_STS_FWD)   )

/**
  * @brief QEI Direction Status Definition
  */
#define LL_QEI_DirStaTypeDef                          LL_RSV_DATA_TYPE

#define LL_QEI_DIR_STS_REV                            (0UL)                /*!< Motor direction is reverse                        */
#define LL_QEI_DIR_STS_FWD                            (1UL)                /*!< Motor direction is forward                        */

#define IS_LL_QEI_DIR_STS(__VAL__)                    (((__VAL__) == LL_QEI_DIR_STS_REV) || \
                                                       ((__VAL__) == LL_QEI_DIR_STS_FWD)   )

/**
  * @brief QEI Capture Overflow Error Status Definition
  */
#define LL_QEI_CapOvfErrStaTypeDef                    LL_RSV_DATA_TYPE

#define LL_QEI_CAP_OVF_ERR_STS_NO_ERR                 (0UL)                /*!< No capture overflow error                         */
#define LL_QEI_CAP_OVF_ERR_STS_ERR                    (1UL)                /*!< Capture counter overflow error occurred           */

#define IS_LL_QEI_CAP_OVF_ERR_STS(__VAL__)            (((__VAL__) == LL_QEI_CAP_OVF_ERR_STS_NO_ERR) || \
                                                       ((__VAL__) == LL_QEI_CAP_OVF_ERR_STS_ERR)   )

/**
  * @brief QEI Capture Direction Error Status Definition
  */
#define LL_QEI_CapDirErrStaTypeDef                    LL_RSV_DATA_TYPE

#define LL_QEI_CAP_DIR_ERR_STS_NO_ERR                 (0UL)                /*!< No capture direction error                        */
#define LL_QEI_CAP_DIR_ERR_STS_ERR                    (1UL)                /*!< Direction changed between two capture events      */

#define IS_LL_QEI_CAP_DIR_ERR_STS(__VAL__)            (((__VAL__) == LL_QEI_CAP_DIR_ERR_STS_NO_ERR) || \
                                                       ((__VAL__) == LL_QEI_CAP_DIR_ERR_STS_ERR)   )

/**
  * @brief QEI The First Index Status Definition
  */
#define LL_QEI_FstIdxStaTypeDef                       LL_RSV_DATA_TYPE

#define LL_QEI_FIRST_IDX_STS_NOT_DET                  (0UL)                /*!< The first index quadrature pulse has not been     \
                                                                                detected                                         */
#define LL_QEI_FIRST_IDX_STS_DET                      (1UL)                /*!< The first index quadrature pulse has been         \
                                                                                detected                                         */

#define IS_LL_QEI_FIRST_IDX_STS(__VAL__)              (((__VAL__) == LL_QEI_FIRST_IDX_STS_NOT_DET) || \
                                                       ((__VAL__) == LL_QEI_FIRST_IDX_STS_DET)   )

/**
  * @}
  */ /* QEI_LL_EC_Configuration */

/**
  * @}
  */ /* QEI_LL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup QEI_LL_Exported_Functions QEI LL Functions
  * @brief    QEI LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_QEI_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_QEI_ASSERT_INLINE_PARAM == 1)
extern void LL_QEI_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_QEI_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_QEI_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_QEI_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup QEI_LL_EF_Configuration LL QEI Configuration
  * @brief    LL QEI Configuration
  * @{
  */

/**
  * @brief  Position Counter Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Cnt Position Counter
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetPosition(QEI_TypeDef *QEIx, uint32_t Cnt)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->POSCNT, Cnt);
}

/**
  * @brief  Position Counter Get
  * @param  QEIx Specifies QEI peripheral
  * @return Position Counter
  */
__STATIC_INLINE uint32_t LL_QEI_GetPosition(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->POSCNT));
}

/**
  * @brief  Position Counter Initial Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Init Position Counter Initial
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetInitialPosition(QEI_TypeDef *QEIx, uint32_t Init)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->POSINIT, Init);
}

/**
  * @brief  Position Counter Initial Get
  * @param  QEIx Specifies QEI peripheral
  * @return Position Counter Initial
  */
__STATIC_INLINE uint32_t LL_QEI_GetInitialPosition(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->POSINIT));
}

/**
  * @brief  Position Counter Max Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Max Position Counter Max
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetPositionMax(QEI_TypeDef *QEIx, uint32_t Max)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->POSMAX, Max);
}

/**
  * @brief  Position Counter Max Get
  * @param  QEIx Specifies QEI peripheral
  * @return Position Counter Max
  */
__STATIC_INLINE uint32_t LL_QEI_GetPositionMax(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->POSMAX));
}

/**
  * @brief  Position Counter Compare Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Cmp Position Counter Compare
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetCompareValue(QEI_TypeDef *QEIx, uint32_t Cmp)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->POSCMP, Cmp);
}

/**
  * @brief  Position Counter Compare Get
  * @param  QEIx Specifies QEI peripheral
  * @return Position Counter Compare
  */
__STATIC_INLINE uint32_t LL_QEI_GetCompareValue(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->POSCMP));
}

/**
  * @brief  Position Counter Index Latch Get
  * @param  QEIx Specifies QEI peripheral
  * @return Position Counter Index Latch
  */
__STATIC_INLINE uint32_t LL_QEI_GetIndexPositionLatch(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->POSILAT));
}

/**
  * @brief  Position Counter Timer Latch Get
  * @param  QEIx Specifies QEI peripheral
  * @return Position Counter Timer Latch
  */
__STATIC_INLINE uint32_t LL_QEI_GetPositionLatch(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->POSLAT));
}

/**
  * @brief  Timer Counter Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Cnt Timer Counter
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetUnitTimerValue(QEI_TypeDef *QEIx, uint32_t Cnt)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->UTMR, Cnt);
}

/**
  * @brief  Timer Counter Get
  * @param  QEIx Specifies QEI peripheral
  * @return Timer Counter
  */
__STATIC_INLINE uint32_t LL_QEI_GetUnitTimerValue(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->UTMR));
}

/**
  * @brief  Timer Counter Period Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Period Timer Counter Period
  * @return None
  */
__STATIC_INLINE void LL_QEI_LoadUnitTimer(QEI_TypeDef *QEIx, uint32_t Period)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->UPRD, Period);
}

/**
  * @brief  Timer Counter Period Get
  * @param  QEIx Specifies QEI peripheral
  * @return Timer Counter Period
  */
__STATIC_INLINE uint32_t LL_QEI_GetUnitTimerPeriod(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->UPRD));
}

/**
  * @brief  Debounce Value Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Val Debounce Value (Val * (1/SYSCLK))
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetDebounceValue(QEI_TypeDef *QEIx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->DECCTL, QEI0_DECCTL_DBC_Msk, (((Val) & QEI0_DECCTL_DBC_Val) << QEI0_DECCTL_DBC_Pos));
}

/**
  * @brief  Direction Counter Mode Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Mode Direction Counter Mode @ref LL_QEI_DirCntModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetDirectionCounterMode(QEI_TypeDef *QEIx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->DECCTL, QEI0_DECCTL_DCM_Msk, (((Mode) & QEI0_DECCTL_DCM_Val) << QEI0_DECCTL_DCM_Pos));
}

/**
  * @brief  Position Counter Work Mode Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Mode Position Counter Work Mode @ref LL_QEI_PosCntWorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetPositionCounterWorkMode(QEI_TypeDef *QEIx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->DECCTL, QEI0_DECCTL_QSRC_Msk, (((Mode) & QEI0_DECCTL_QSRC_Val) << QEI0_DECCTL_QSRC_Pos));
}

/**
  * @brief  Position Counter Clock Rate Mode Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Mode Position Counter Clock Rate Mode @ref LL_QEI_ClkRateModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetClockRateMode(QEI_TypeDef *QEIx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->DECCTL, QEI0_DECCTL_XCR_Msk, (((Mode) & QEI0_DECCTL_XCR_Val) << QEI0_DECCTL_XCR_Pos));
}

/**
  * @brief  Index Reset Position Counter Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIndexResetPosition(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->DECCTL, QEI0_DECCTL_IGATE_Msk);
}

/**
  * @brief  Index Reset Position Counter Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIndexResetPosition(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->DECCTL, QEI0_DECCTL_IGATE_Msk);
}

/**
  * @brief  QEA/QEB Swap Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableSwapQEA_B(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->DECCTL, QEI0_DECCTL_SWAP_Msk);
}

/**
  * @brief  QEA/QEB Swap Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableSwapQEA_B(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->DECCTL, QEI0_DECCTL_SWAP_Msk);
}

/**
  * @brief  QEB Input Polarity Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Pol QEB Input Polarity @ref LL_QEI_InputPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetQEBInputPolarity(QEI_TypeDef *QEIx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->DECCTL, QEI0_DECCTL_QBP_Msk, (((Pol) & QEI0_DECCTL_QBP_Val) << QEI0_DECCTL_QBP_Pos));
}

/**
  * @brief  QEA Input Polarity Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Pol QEA Input Polarity @ref LL_QEI_InputPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetQEAInputPolarity(QEI_TypeDef *QEIx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->DECCTL, QEI0_DECCTL_QAP_Msk, (((Pol) & QEI0_DECCTL_QAP_Val) << QEI0_DECCTL_QAP_Pos));
}

/**
  * @brief  Index Input Polarity Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Pol Index Input Polarity @ref LL_QEI_InputPolTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetIndexInputPolarity(QEI_TypeDef *QEIx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->DECCTL, QEI0_DECCTL_QIP_Msk, (((Pol) & QEI0_DECCTL_QIP_Val) << QEI0_DECCTL_QIP_Pos));
}

/**
  * @brief  Position Counter Reset Mode Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Mode Position Counter Reset Mode @ref LL_QEI_PosCntRstModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetPositionResetMode(QEI_TypeDef *QEIx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->QEPCTL, QEI0_QEPCTL_PCRM_Msk, (((Mode) & QEI0_QEPCTL_PCRM_Val) << QEI0_QEPCTL_PCRM_Pos));
}

/**
  * @brief  Position Counter Software Initial Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetSWPositionInit(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->QEPCTL, QEI0_QEPCTL_SWI_Msk);
}

/**
  * @brief  Position Counter Index Initial Edge Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Edge Position Counter Index Initial Edge @ref LL_QEI_PosCntIdxInitEdgeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetPositionInitMode(QEI_TypeDef *QEIx, uint32_t Edge)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->QEPCTL, QEI0_QEPCTL_IEI_Msk, (((Edge) & QEI0_QEPCTL_IEI_Val) << QEI0_QEPCTL_IEI_Pos));
}

/**
  * @brief  Position Counter Index Latch Edge Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Edge Position Counter Index Latch Edge @ref LL_QEI_PosCntIdxLatchEdgeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetLatchMode(QEI_TypeDef *QEIx, uint32_t Edge)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->QEPCTL, QEI0_QEPCTL_IEL_Msk, (((Edge) & QEI0_QEPCTL_IEL_Val) << QEI0_QEPCTL_IEL_Pos));
}

/**
  * @brief  QEI Timer Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableUnitTimer(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->QEPCTL, QEI0_QEPCTL_UTE_Msk);
}

/**
  * @brief  QEI Timer Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableUnitTimer(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->QEPCTL, QEI0_QEPCTL_UTE_Msk);
}

/**
  * @brief  QEI Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_Enable(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->QEPCTL, QEI0_QEPCTL_QPE_Msk);
}

/**
  * @brief  QEI Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_Disable(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->QEPCTL, QEI0_QEPCTL_QPE_Msk);
}

/**
  * @brief  Position Counter Compare Shadow Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableCompareShadow(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->POSCTL, QEI0_POSCTL_PSE_Msk);
}

/**
  * @brief  Position Counter Compare Shadow Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableCompareShadow(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->POSCTL, QEI0_POSCTL_PSE_Msk);
}

/**
  * @brief  Position Counter Compare Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableCompare(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->POSCTL, QEI0_POSCTL_CCE_Msk);
}

/**
  * @brief  Position Counter Compare Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableCompare(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->POSCTL, QEI0_POSCTL_CCE_Msk);
}

/**
  * @brief  Capture Event Division Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Div Capture Event Division @ref LL_QEI_CapEvtDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetCaptureEventPrescale(QEI_TypeDef *QEIx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->CAPCTL, QEI0_CAPCTL_UPPS_Msk, (((Div) & QEI0_CAPCTL_UPPS_Val) << QEI0_CAPCTL_UPPS_Pos));
}

/**
  * @brief  Capture Timer Clock Division Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Div Capture Timer Clock Division @ref LL_QEI_CapTmrClkDivTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetCaptureTimerClockPrescale(QEI_TypeDef *QEIx, uint32_t Div)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->CAPCTL, QEI0_CAPCTL_CCPS_Msk, (((Div) & QEI0_CAPCTL_CCPS_Val) << QEI0_CAPCTL_CCPS_Pos));
}

/**
  * @brief  Capture Latch Mode Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Mode Capture Latch Mode @ref LL_QEI_CapLatchModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetCaptureLatchMode(QEI_TypeDef *QEIx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    MODIFY_REG(QEIx->CAPCTL, QEI0_CAPCTL_CMD_Msk, (((Mode) & QEI0_CAPCTL_CMD_Val) << QEI0_CAPCTL_CMD_Pos));
}

/**
  * @brief  QEI Capture Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableCapture(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->CAPCTL, QEI0_CAPCTL_CEN_Msk);
}

/**
  * @brief  QEI Capture Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableCapture(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->CAPCTL, QEI0_CAPCTL_CEN_Msk);
}

/**
  * @brief  Capture Counter Set
  * @param  QEIx Specifies QEI peripheral
  * @param  Cnt Capture Counter
  * @return None
  */
__STATIC_INLINE void LL_QEI_SetCaptureTimer(QEI_TypeDef *QEIx, uint32_t Cnt)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->QCTMR, Cnt);
}

/**
  * @brief  Capture Counter Get
  * @param  QEIx Specifies QEI peripheral
  * @return Capture Counter
  */
__STATIC_INLINE uint32_t LL_QEI_GetCaptureTimer(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->QCTMR));
}

/**
  * @brief  Capture Period Get
  * @param  QEIx Specifies QEI peripheral
  * @return Capture Period
  */
__STATIC_INLINE uint32_t LL_QEI_GetCapturePeriod(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->QCPRD));
}

/**
  * @brief  Capture Counter Latch Get
  * @param  QEIx Specifies QEI peripheral
  * @return Capture Counter Latch
  */
__STATIC_INLINE uint32_t LL_QEI_GetCaptureTimerLatch(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->CTMRLAT));
}

/**
  * @brief  Capture Period Latch Get
  * @param  QEIx Specifies QEI peripheral
  * @return Capture Period Latch
  */
__STATIC_INLINE uint32_t LL_QEI_GetCapturePeriodLatch(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->CPRDLAT));
}

/**
  * @brief  Capture Done Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_CDS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_CDS_Msk);
}

/**
  * @brief  Capture Done Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_CDS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_CDS_Msk);
}

/**
  * @brief  Position Counter Reset Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_PRS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_PRS_Msk);
}

/**
  * @brief  Position Counter Reset Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_PRS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_PRS_Msk);
}

/**
  * @brief  Position Counter Initial Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_PIS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_PIS_Msk);
}

/**
  * @brief  Position Counter Initial Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_PIS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_PIS_Msk);
}

/**
  * @brief  Timer Overflow Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_UTO(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_UTO_Msk);
}

/**
  * @brief  Timer Overflow Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_UTO(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_UTO_Msk);
}

/**
  * @brief  Position Counter Latch Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_IEL(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_IEL_Msk);
}

/**
  * @brief  Position Counter Latch Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_IEL(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_IEL_Msk);
}

/**
  * @brief  Position Counter Compare Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_PCM(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_PCM_Msk);
}

/**
  * @brief  Position Counter Compare Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_PCM(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_PCM_Msk);
}

/**
  * @brief  Position Counter Overflow Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_PCO(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_PCO_Msk);
}

/**
  * @brief  Position Counter Overflow Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_PCO(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_PCO_Msk);
}

/**
  * @brief  Position Counter Underflow Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_PCU(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_PCU_Msk);
}

/**
  * @brief  Position Counter Underflow Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_PCU(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_PCU_Msk);
}

/**
  * @brief  Directiont Change Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_QDC(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_QDC_Msk);
}

/**
  * @brief  Directiont Change Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_QDC(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_QDC_Msk);
}

/**
  * @brief  Phase Error Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_QPE(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_QPE_Msk);
}

/**
  * @brief  Phase Error Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_QPE(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_QPE_Msk);
}

/**
  * @brief  Position Counter Error Interrupt Enable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT_PCE(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, QEI0_IENR_PCE_Msk);
}

/**
  * @brief  Position Counter Error Interrupt Disable
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT_PCE(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, QEI0_IENR_PCE_Msk);
}

/**
  * @brief  All Interrupt Enable Get
  * @param  QEIx Specifies QEI peripheral
  * @return All Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_QEI_GetInterruptEnableStatus(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->IENR));
}

/**
  * @brief  First Index Direction Status Get
  * @param  QEIx Specifies QEI peripheral
  * @return Rotation Direction @ref LL_QEI_DirFstIdxStaTypeDef
  */
__STATIC_INLINE uint32_t LL_QEI_GetFirstIndexDirectionStatus(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_QDF_Msk, QEI0_STSR_QDF_Pos));
}

/**
  * @brief  Index Direction Status Get
  * @param  QEIx Specifies QEI peripheral
  * @return Rotation Direction @ref LL_QEI_DirIdxLchStaTypeDef
  */
__STATIC_INLINE uint32_t LL_QEI_GetIndexDirectionStatus(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_QDI_Msk, QEI0_STSR_QDI_Pos));
}

/**
  * @brief  Real Timer Direction Status Get
  * @param  QEIx Specifies QEI peripheral
  * @return Rotation Direction @ref LL_QEI_DirStaTypeDef
  */
__STATIC_INLINE uint32_t LL_QEI_GetDirection(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_QDS_Msk, QEI0_STSR_QDS_Pos));
}

/**
  * @brief  Judge is Capture Overflow Error Status or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Capture Overflow Error Status
  * @retval 1 is Capture Overflow Error Status 
  */
__STATIC_INLINE uint32_t LL_QEI_IsCaptureOverflowErrorActived(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)((!!READ_BIT(QEIx->STSR, QEI0_STSR_COE_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Capture Overflow Error Status Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearCaptureOverflowErrorFlag(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_COE_Msk);
}

/**
  * @brief  Judge is Capture Direction Error Status or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Capture Direction Error Status
  * @retval 1 is Capture Direction Error Status 
  */
__STATIC_INLINE uint32_t LL_QEI_IsCaptureDirectionErrorActived(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)((!!READ_BIT(QEIx->STSR, QEI0_STSR_CDE_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Capture Direction Error Status Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearCaptureDirectionErrorFlag(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_CDE_Msk);
}

/**
  * @brief  Judge is First Index Detected Status or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't First Index Detected Status
  * @retval 1 is First Index Detected Status
  */
__STATIC_INLINE uint32_t LL_QEI_IsFirstIndexActived(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)((!!READ_BIT(QEIx->STSR, QEI0_STSR_FIS_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Judge is Capture Done Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Capture Done Interrupt Pending
  * @retval 1 is Capture Done Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_CDS(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_CDS_Msk, QEI0_STSR_CDS_Pos));
}

/**
  * @brief  Capture Done Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_CDS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_CDS_Msk);
}

/**
  * @brief  Judge is Positon Counter Reset Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Reset Interrupt Pending
  * @retval 1 is Positon Counter Reset Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_PRS(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_PRS_Msk, QEI0_STSR_PRS_Pos));
}

/**
  * @brief  Positon Counter Reset Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_PRS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_PRS_Msk);
}

/**
  * @brief  Judge is Positon Counter Initial Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Initial Interrupt Pending
  * @retval 1 is Positon Counter Initial Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_PIS(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_PIS_Msk, QEI0_STSR_PIS_Pos));
}

/**
  * @brief  Positon Counter Initial Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_PIS(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_PIS_Msk);
}

/**
  * @brief  Judge is Timer Overflow Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Timer Overflow Interrupt Pending
  * @retval 1 is Timer Overflow Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_UTO(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_UTO_Msk, QEI0_STSR_UTO_Pos));
}

/**
  * @brief  Timer Overflow Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_UTO(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_UTO_Msk);
}

/**
  * @brief  Judge is Positon Counter Latch Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Latch Interrupt Pending
  * @retval 1 is Positon Counter Latch Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_IEL(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_IEL_Msk, QEI0_STSR_IEL_Pos));
}

/**
  * @brief  Positon Counter Latch Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_IEL(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_IEL_Msk);
}

/**
  * @brief  Judge is Positon Counter Compare Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Compare Interrupt Pending
  * @retval 1 is Positon Counter Compare Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_PCM(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_PCM_Msk, QEI0_STSR_PCM_Pos));
}

/**
  * @brief  Positon Counter Compare Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_PCM(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_PCM_Msk);
}

/**
  * @brief  Judge is Positon Counter Overflow Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Overflow Interrupt Pending
  * @retval 1 is Positon Counter Overflow Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_PCO(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_PCO_Msk, QEI0_STSR_PCO_Pos));
}

/**
  * @brief  Positon Counter Overflow Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_PCO(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_PCO_Msk);
}

/**
  * @brief  Judge is Positon Counter Underflow Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Underflow Interrupt Pending
  * @retval 1 is Positon Counter Underflow Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_PCU(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_PCU_Msk, QEI0_STSR_PCU_Pos));
}

/**
  * @brief  Positon Counter Underflow Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_PCU(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_PCU_Msk);
}

/**
  * @brief  Judge is Direction Change Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Direction Change Interrupt Pending
  * @retval 1 is Direction Change Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_QDC(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_QDC_Msk, QEI0_STSR_QDC_Pos));
}

/**
  * @brief  Direction Change Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_QDC(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_QDC_Msk);
}

/**
  * @brief  Judge is Phase Error Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Phase Error Interrupt Pending
  * @retval 1 is Phase Error Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_PHE(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_PHE_Msk, QEI0_STSR_PHE_Pos));
}

/**
  * @brief  Phase Error Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_PHE(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_PHE_Msk);
}

/**
  * @brief  Judge is Position Counter Error Interrupt Pending or not
  * @param  QEIx Specifies QEI peripheral
  * @retval 0 isn't Position Counter Error Interrupt Pending
  * @retval 1 is Position Counter Error Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag_PCE(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_BIT_SHIFT(QEIx->STSR, QEI0_STSR_PCE_Msk, QEI0_STSR_PCE_Pos));
}

/**
  * @brief  Position Counter Error Interrupt Pending Clear
  * @param  QEIx Specifies QEI peripheral
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag_PCE(QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, QEI0_STSR_PCE_Msk);
}

/**
  * @brief  All Interrupt Pending Get
  * @param  QEIx Specifies QEI peripheral
  * @return All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_QEI_GetInterruptStatus(const QEI_TypeDef *QEIx)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    return (uint32_t)(READ_REG(QEIx->STSR));
}

/**
  * @}
  */ /* QEI_LL_EF_Configuration */

/** @defgroup QEI_LL_EF_IT_Management LL QEI Interrupt Management
  * @brief LL QEI Interrupt Management
  * @{
  */

/**
  * @brief  QEI Interrupt enable
  * @param  QEIx Specifies QEI peripheral
  * @param  Mask Mask to enable @ref LL_QEI_IENR_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_EnableIT(QEI_TypeDef *QEIx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    SET_BIT(QEIx->IENR, Mask);
}

/**
  * @brief  QEI Interrupt disable
  * @param  QEIx Specifies QEI peripheral
  * @param  Mask Mask to disable @ref LL_QEI_IENR_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_DisableIT(QEI_TypeDef *QEIx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    CLEAR_BIT(QEIx->IENR, Mask);
}

/**
  * @brief  Check if QEI Interrupt is enabled or disabled
  * @param  QEIx Specifies QEI peripheral
  * @param  Mask Mask to check @ref LL_QEI_IENR_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_QEI_IsEnabledIT(const QEI_TypeDef *QEIx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(QEIx->IENR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  QEIx Specifies QEI peripheral
  * @param  Mask Mask to check @ref LL_QEI_STSR_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_QEI_ClearFlag(QEI_TypeDef *QEIx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_QEI_ALL_INSTANCE(QEIx));

    WRITE_REG(QEIx->STSR, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  QEIx Specifies QEI peripheral
  * @param  Mask Mask to check @ref LL_QEI_STSR_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_QEI_IsActiveFlag(const QEI_TypeDef *QEIx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(QEIx->STSR, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @}
  */ /* QEI_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* QEI_LL_Exported_Functions */


/**
  * @}
  */ /* QEI_LL */

#endif /* QEI */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_QEI_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

