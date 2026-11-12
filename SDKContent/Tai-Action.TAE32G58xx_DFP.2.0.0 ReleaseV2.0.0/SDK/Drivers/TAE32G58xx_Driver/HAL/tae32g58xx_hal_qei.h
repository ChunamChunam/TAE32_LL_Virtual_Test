/**
  ******************************************************************************
  * @file    tae32g58xx_hal_qei.h
  * @author  Tai-Action SD Team
  * @brief   Header file for QEI HAL module
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
#ifndef _TAE32G58XX_HAL_QEI_H_
#define _TAE32G58XX_HAL_QEI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_qei.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(QEI0) || defined(QEI1) || defined(QEI2)

/** @addtogroup QEI_HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup QEI_HAL_Exported_Macros QEI HAL Exported Macros
  * @brief    QEI HAL Exported Macros
  * @{
  */

/** @defgroup QEI_HAL_EM_Assert QEI HAL Assert 
  * @brief    QEI HAL Assert
  * @{
  */

/**
  * @brief  The HAL_QEI_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_QEI_CHECK_PARAM
#define TAE32_USE_HAL_QEI_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_QEI_CHECK_PARAM != 1) && (TAE32_USE_HAL_QEI_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_QEI_CHECK_PARAM
#define TAE32_USE_HAL_QEI_CHECK_PARAM   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_QEI_CHECK_PARAM */

/**
  * @brief  The HAL_QEI_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_QEI_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_QEI_CHECK_PARAM) { \
            expression;                      \
        }
/**
  * @}
  */ /* QEI_HAL_EM_Assert */

/** @defgroup QEI_HAL_EM_Mask QEI HAL Mask
  * @brief    QEI HAL Mask
  * @{
  */

/** @name HAL_QEI_ITEnMskTypeDef
  * @brief QEI Interrupt Enable Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_QEI_ITEnMskTypeDef                              LL_QEI_IENR_ITEnMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_QEI_IENR_ITEnMskTypeDef HAL_QEI_ITEnMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_QEI_IENR_CAPTURE_DONE_IT_EN                     LL_QEI_IENR_CDS                  /*!< CDS Mask                 */
#define HAL_QEI_IENR_POSI_CNTR_RESET_IT_EN                  LL_QEI_IENR_PRS                  /*!< PRS Mask                 */
#define HAL_QEI_IENR_POSI_CNTR_INIT_IT_EN                   LL_QEI_IENR_PIS                  /*!< PIS Mask                 */
#define HAL_QEI_IENR_TIMER_OVERFLOW_IT_EN                   LL_QEI_IENR_UTO                  /*!< UTO Mask                 */
#define HAL_QEI_IENR_POSI_CNTR_LATCH_IT_EN                  LL_QEI_IENR_IEL                  /*!< IEL Mask                 */
#define HAL_QEI_IENR_POSI_CNTR_COMPARE_IT_EN                LL_QEI_IENR_PCM                  /*!< PCM Mask                 */
#define HAL_QEI_IENR_POSI_CNTR_OVERFLOW_IT_EN               LL_QEI_IENR_PCO                  /*!< PCO Mask                 */
#define HAL_QEI_IENR_POSI_CNTR_UNDERFLOW_IT_EN              LL_QEI_IENR_PCU                  /*!< PCU Mask                 */
#define HAL_QEI_IENR_DIRECTION_CHANGE_IT_EN                 LL_QEI_IENR_QDC                  /*!< QDC Mask                 */
#define HAL_QEI_IENR_PHASE_ERROR_IT_EN                      LL_QEI_IENR_QPE                  /*!< QPE Mask                 */
#define HAL_QEI_IENR_POSI_CNTR_ERROR_IT_EN                  LL_QEI_IENR_PCE                  /*!< PCE Mask                 */
/** @} */

/** @name HAL_QEI_ITPendingMskTypeDef
  * @brief QEI Interrupt Pending Mask Definition
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_QEI_ITPendingMskTypeDef                         LL_QEI_STSR_ITPendingMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_QEI_STSR_ITPendingMskTypeDef HAL_QEI_ITPendingMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_QEI_STSR_CAPTURE_DONE_IT_FLAG                   LL_QEI_STSR_CDS                  /*!< CDS Mask                 */
#define HAL_QEI_STSR_POSI_CNTR_RESET_IT_FLAG                LL_QEI_STSR_PRS                  /*!< PRS Mask                 */
#define HAL_QEI_STSR_POSI_CNTR_INIT_IT_FLAG                 LL_QEI_STSR_PIS                  /*!< PIS Mask                 */
#define HAL_QEI_STSR_TIMER_OVERFLOW_IT_FLAG                 LL_QEI_STSR_UTO                  /*!< UTO Mask                 */
#define HAL_QEI_STSR_POSI_CNTR_LATCH_IT_FLAG                LL_QEI_STSR_IEL                  /*!< IEL Mask                 */
#define HAL_QEI_STSR_POSI_CNTR_COMPARE_IT_FLAG              LL_QEI_STSR_PCM                  /*!< PCM Mask                 */
#define HAL_QEI_STSR_POSI_CNTR_OVERFLOW_IT_FLAG             LL_QEI_STSR_PCO                  /*!< PCO Mask                 */
#define HAL_QEI_STSR_POSI_CNTR_UNDERFLOW_IT_FLAG            LL_QEI_STSR_PCU                  /*!< PCU Mask                 */
#define HAL_QEI_STSR_DIRECTION_CHANGE_IT_FLAG               LL_QEI_STSR_QDC                  /*!< QDC Mask                 */
#define HAL_QEI_STSR_PHASE_ERROR_IT_FLAG                    LL_QEI_STSR_PHE                  /*!< PHE Mask                 */
#define HAL_QEI_STSR_POSI_CNTR_ERROR_IT_FLAG                LL_QEI_STSR_PCE                  /*!< PCE Mask                 */
/** @} */

/**
  * @}
  */ /* QEI_HAL_EM_Mask */

/**
  * @}
  */ /* QEI_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup QEI_HAL_Exported_Types QEI HAL Exported Types
  * @brief    QEI HAL Exported Types
  * @{
  */

/**
  * @brief QEI Global state
  */
typedef enum
{
    HAL_QEI_STATE_RESET                  = 0UL,              /*!< QEI not yet initialized                   */
    HAL_QEI_STATE_INIT                   = (1UL << 30U),     /*!< QEI initialized but not yet configured    */
    HAL_QEI_STATE_IDLE                   = (1UL << 29U),     /*!< QEI configured and ready to be activated  */
    HAL_QEI_STATE_ACTIVE                 = (1UL << 28U),     /*!< QEI activated, ready to operate           */
} HAL_QEI_StateTypeDef;

/**
  * @brief QEI Function Enable Definition
  */
typedef enum
{
    HAL_QEI_FUNC_DISABLE  = 0U,    /*!< QEI Function Disable  */
    HAL_QEI_FUNC_ENABLE   = 1U     /*!< QEI Function Enable   */
} HAL_QEI_EnableTypeDef;

/**
  * @brief QEI Direction Counter Mode Definition
  */
typedef enum
{
    HAL_QEI_DIR_CNT_MODE0  = LL_QEI_DIR_CNT_MODE0,   /*!< QEI Direction Counter Mode 0   */
    HAL_QEI_DIR_CNT_MODE1  = LL_QEI_DIR_CNT_MODE1    /*!< QEI Direction Counter Mode 1   */
} HAL_QEI_DirCntModeTypeDef;

/**
  * @brief QEI Position Counter Work Mode Definition
  */
typedef enum
{
    HAL_QEI_POS_CNT_WORK_MODE_QUAD  = LL_QEI_POS_CNT_WORK_MODE_QUAD,   /*!< QEI Position Counter Work Mode Quadrature   */
    HAL_QEI_POS_CNT_WORK_MODE_DIR   = LL_QEI_POS_CNT_WORK_MODE_DIR,    /*!< QEI Position Counter Work Mode Direction    */
    HAL_QEI_POS_CNT_WORK_MODE_UP    = LL_QEI_POS_CNT_WORK_MODE_UP,     /*!< QEI Position Counter Work Mode Up           */
    HAL_QEI_POS_CNT_WORK_MODE_DOWN  = LL_QEI_POS_CNT_WORK_MODE_DOWN    /*!< QEI Position Counter Work Mode Down         */
} HAL_QEI_PosCntWorkModeTypeDef;

/**
  * @brief QEI Position Counter Clock Rate Mode Definition
  */
typedef enum
{
    HAL_QEI_CLK_RATE_MODE_X1  = LL_QEI_CLK_RATE_MODE_X1,   /*!< QEI Position Counter Clock Rate Mode X1   */
    HAL_QEI_CLK_RATE_MODE_X2  = LL_QEI_CLK_RATE_MODE_X2    /*!< QEI Position Counter Clock Rate Mode X2   */
} HAL_QEI_ClkRateModeTypeDef;

/**
  * @brief QEI QEA/QEB/Index Input Polarity Definition
  */
typedef enum
{
    HAL_QEI_INPUT_POL_ACT_HIGH  = LL_QEI_INPUT_POL_ACT_HIGH,   /*!< QEI QEA/QEB/Index Input Polarity Active High   */
    HAL_QEI_INPUT_POL_ACT_LOW   = LL_QEI_INPUT_POL_ACT_LOW     /*!< QEI QEA/QEB/Index Input Polarity Active Low    */
} HAL_QEI_InputPolTypeDef;

/**
  * @brief QEI Position Counter Reset Mode Definition
  * @note  Up and Down Overflow Reset are included in every mode
  */
typedef enum
{
    HAL_QEI_POS_CNT_RST_MODE_EVERY_IDX  = LL_QEI_POS_CNT_RST_MODE_EVERY_IDX,   /*!< QEI Position Counter Reset Mode Every Index   */
    HAL_QEI_POS_CNT_RST_MODE_MAX        = LL_QEI_POS_CNT_RST_MODE_MAX,         /*!< QEI Position Counter Reset Mode MAX           */
    HAL_QEI_POS_CNT_RST_MODE_FIRDT_IDX  = LL_QEI_POS_CNT_RST_MODE_FIRDT_IDX,   /*!< QEI Position Counter Reset Mode First Index   */
    HAL_QEI_POS_CNT_RST_MODE_TMR_EVT    = LL_QEI_POS_CNT_RST_MODE_TMR_EVT      /*!< QEI Position Counter Reset Mode Timer Event   */
} HAL_QEI_PosCntRstModeTypeDef;

/**
  * @brief QEI Position Counter Index Initial Edge Definition
  */
typedef enum
{
    HAL_QEI_POS_CNT_INIT_IDX_EDGE_DIS      = LL_QEI_POS_CNT_INIT_IDX_EDGE_DIS,      /*!< QEI Position Counter Index Initial Edge Disable  */
    HAL_QEI_POS_CNT_INIT_IDX_EDGE_RISING   = LL_QEI_POS_CNT_INIT_IDX_EDGE_RISING,   /*!< QEI Position Counter Index Initial Edge Rising   */
    HAL_QEI_POS_CNT_INIT_IDX_EDGE_FALLING  = LL_QEI_POS_CNT_INIT_IDX_EDGE_FALLING   /*!< QEI Position Counter Index Initial Edge Falling  */
} HAL_QEI_PosCntIdxInitEdgeTypeDef;

/**
  * @brief QEI Position Counter Index Latch Edge Definition
  */
typedef enum
{
    HAL_QEI_POS_CNT_LATCH_IDX_EDGE_DIS      = LL_QEI_POS_CNT_LATCH_IDX_EDGE_DIS,       /*!< QEI Position Counter Index Latch Edge Disable    */
    HAL_QEI_POS_CNT_LATCH_IDX_EDGE_RISING   = LL_QEI_POS_CNT_LATCH_IDX_EDGE_RISING,    /*!< QEI Position Counter Index Latch Edge Rising     */
    HAL_QEI_POS_CNT_LATCH_IDX_EDGE_FALLING  = LL_QEI_POS_CNT_LATCH_IDX_EDGE_FALLING,   /*!< QEI Position Counter Index Latch Edge Falling    */
    HAL_QEI_POS_CNT_LATCH_IDX_EDGE_FIRST    = LL_QEI_POS_CNT_LATCH_IDX_EDGE_FIRST      /*!< QEI Position Counter Index Latch Edge First Quad */
} HAL_QEI_PosCntIdxLatchEdgeTypeDef;

/**
  * @brief QEI Capture Event Division Definition
  */
typedef enum
{
    HAL_QEI_CAP_EVT_DIV_1     = LL_QEI_CAP_EVT_DIV_1,      /*!< QEI Capture Event Division 1      */
    HAL_QEI_CAP_EVT_DIV_2     = LL_QEI_CAP_EVT_DIV_2,      /*!< QEI Capture Event Division 2      */
    HAL_QEI_CAP_EVT_DIV_4     = LL_QEI_CAP_EVT_DIV_4,      /*!< QEI Capture Event Division 4      */
    HAL_QEI_CAP_EVT_DIV_8     = LL_QEI_CAP_EVT_DIV_8,      /*!< QEI Capture Event Division 8      */
    HAL_QEI_CAP_EVT_DIV_16    = LL_QEI_CAP_EVT_DIV_16,     /*!< QEI Capture Event Division 16     */
    HAL_QEI_CAP_EVT_DIV_32    = LL_QEI_CAP_EVT_DIV_32,     /*!< QEI Capture Event Division 32     */
    HAL_QEI_CAP_EVT_DIV_64    = LL_QEI_CAP_EVT_DIV_64,     /*!< QEI Capture Event Division 64     */
    HAL_QEI_CAP_EVT_DIV_128   = LL_QEI_CAP_EVT_DIV_128,    /*!< QEI Capture Event Division 128    */
    HAL_QEI_CAP_EVT_DIV_256   = LL_QEI_CAP_EVT_DIV_256,    /*!< QEI Capture Event Division 256    */
    HAL_QEI_CAP_EVT_DIV_512   = LL_QEI_CAP_EVT_DIV_512,    /*!< QEI Capture Event Division 512    */
    HAL_QEI_CAP_EVT_DIV_1024  = LL_QEI_CAP_EVT_DIV_1024,   /*!< QEI Capture Event Division 1024   */
    HAL_QEI_CAP_EVT_DIV_2048  = LL_QEI_CAP_EVT_DIV_2048    /*!< QEI Capture Event Division 2048   */
} HAL_QEI_CapEvtDivTypeDef;

/**
  * @brief QEI Capture Timer Clock Division Definition
  */
typedef enum
{
    HAL_QEI_CAP_TMR_CLK_DIV_1    = LL_QEI_CAP_TMR_CLK_DIV_1,    /*!< QEI Capture Timer Clock Division 1     */
    HAL_QEI_CAP_TMR_CLK_DIV_2    = LL_QEI_CAP_TMR_CLK_DIV_2,    /*!< QEI Capture Timer Clock Division 2     */
    HAL_QEI_CAP_TMR_CLK_DIV_4    = LL_QEI_CAP_TMR_CLK_DIV_4,    /*!< QEI Capture Timer Clock Division 4     */
    HAL_QEI_CAP_TMR_CLK_DIV_8    = LL_QEI_CAP_TMR_CLK_DIV_8,    /*!< QEI Capture Timer Clock Division 8     */
    HAL_QEI_CAP_TMR_CLK_DIV_16   = LL_QEI_CAP_TMR_CLK_DIV_16,   /*!< QEI Capture Timer Clock Division 16    */
    HAL_QEI_CAP_TMR_CLK_DIV_32   = LL_QEI_CAP_TMR_CLK_DIV_32,   /*!< QEI Capture Timer Clock Division 32    */
    HAL_QEI_CAP_TMR_CLK_DIV_64   = LL_QEI_CAP_TMR_CLK_DIV_64,   /*!< QEI Capture Timer Clock Division 64    */
    HAL_QEI_CAP_TMR_CLK_DIV_128  = LL_QEI_CAP_TMR_CLK_DIV_128   /*!< QEI Capture Timer Clock Division 128   */
} HAL_QEI_CapTmrClkDivTypeDef;

/**
  * @brief QEI Capture Latch Mode Definition
  */
typedef enum
{
    HAL_QEI_CAP_LATCH_MODE_CPU_READ  = LL_QEI_CAP_LATCH_MODE_CPU_READ,   /*!< QEI Capture Latch Mode CPU Read        */
    HAL_QEI_CAP_LATCH_MODE_TMR_TO    = LL_QEI_CAP_LATCH_MODE_TMR_TO      /*!< QEI Capture Latch Mode Timer Timeout   */
} HAL_QEI_CapLatchModeTypeDef;

/**
  * @brief QEI Direction First Index Status Definition
  */
typedef enum
{
    HAL_QEI_DIR_FIRST_IDX_STS_REV = LL_QEI_DIR_FIRST_IDX_STS_REV,   /*!< Motor direction is reverse when the first index quadrature pulse is valid */
    HAL_QEI_DIR_FIRST_IDX_STS_FWD = LL_QEI_DIR_FIRST_IDX_STS_FWD    /*!< Motor direction is forward when the first index quadrature pulse is valid */
} HAL_QEI_DirFstIdxStaTypeDef;

/**
  * @brief QEI Direction Index Latch Status Definition
  */
typedef enum
{
    HAL_QEI_DIR_IDX_LCH_STS_REV = LL_QEI_DIR_IDX_LCH_STS_REV,   /*!< Motor direction is reverse when each index quadrature pulse is valid */
    HAL_QEI_DIR_IDX_LCH_STS_FWD = LL_QEI_DIR_IDX_LCH_STS_FWD    /*!< Motor direction is forward when each index quadrature pulse is valid */
} HAL_QEI_DirIdxLchStaTypeDef;

/**
  * @brief QEI Direction Status Definition
  */
typedef enum
{
    HAL_QEI_DIR_STS_REV = LL_QEI_DIR_STS_REV,   /*!< Motor direction is reverse */
    HAL_QEI_DIR_STS_FWD = LL_QEI_DIR_STS_FWD    /*!< Motor direction is forward */
} HAL_QEI_DirStaTypeDef;

/**
  * @brief QEI Capture Overflow Error Status Definition
  */
typedef enum
{
    HAL_QEI_CAP_OVF_ERR_STS_NO_ERR = LL_QEI_CAP_OVF_ERR_STS_NO_ERR,   /*!< No capture overflow error                */
    HAL_QEI_CAP_OVF_ERR_STS_ERR    = LL_QEI_CAP_OVF_ERR_STS_ERR       /*!< Capture counter overflow error occurred  */
} HAL_QEI_CapOvfErrStaTypeDef;

/**
  * @brief QEI Capture Direction Error Status Definition
  */
typedef enum
{
    HAL_QEI_CAP_DIR_ERR_STS_NO_ERR = LL_QEI_CAP_DIR_ERR_STS_NO_ERR,   /*!< No capture direction error                   */
    HAL_QEI_CAP_DIR_ERR_STS_ERR    = LL_QEI_CAP_DIR_ERR_STS_ERR       /*!< Direction changed between two capture events */
} HAL_QEI_CapDirErrStaTypeDef;

/**
  * @brief QEI The First Index Status Definition
  */
typedef enum
{
    HAL_QEI_FIRST_IDX_STS_NOT_DET = LL_QEI_FIRST_IDX_STS_NOT_DET,   /*!< The first index quadrature pulse has not been detected */
    HAL_QEI_FIRST_IDX_STS_DET     = LL_QEI_FIRST_IDX_STS_DET        /*!< The first index quadrature pulse has been detected     */
} HAL_QEI_FstIdxStaTypeDef;


/**
  * @brief QEI Position Counter Configuration Definition
  */
typedef struct {
    uint32_t                            InitialValue;               /*!< Position Counter Initial Value             */
    uint32_t                            MaxValue;                   /*!< Position Counter Max Value                 */

    uint8_t                             DebounceWindow;             /*!< Debounce Value (n x SYSCLK)                */

    HAL_QEI_EnableTypeDef               IndexResetMode;             /*!< Index Reset Position Counter Enable        */
    HAL_QEI_EnableTypeDef               InputSwap;                  /*!< QEA/B Swap Enable                          */
    HAL_QEI_InputPolTypeDef             IndexPolarity;              /*!< Index Input Polarity                       */
    HAL_QEI_InputPolTypeDef             QEAPolarity;                /*!< QEA Input Polarity                         */
    HAL_QEI_InputPolTypeDef             QEBPolarity;                /*!< QEB Input Polarity                         */

    HAL_QEI_PosCntWorkModeTypeDef       WorkMode;                   /*!< Position Counter Work Mode                 */
    HAL_QEI_DirCntModeTypeDef           DirectionCounterMode;       /*!< Position Counter Direction Counter Mode    */
    HAL_QEI_ClkRateModeTypeDef          ClockRateMode;              /*!< Position Counter Clock Rate                */
    HAL_QEI_PosCntRstModeTypeDef        ResetMode;                  /*!< Position Counter Reset Mode                */
    HAL_QEI_PosCntIdxInitEdgeTypeDef    IndexInitEdge;              /*!< Position Counter Index Init Edge           */
    HAL_QEI_PosCntIdxLatchEdgeTypeDef   IndexLatchEdge;             /*!< Position Counter Index Latch Edge          */
} HAL_QEI_PosCntCfgTypeDef;

/**
  * @brief QEI Timer Counter Configuration Definition
  */
typedef struct {
    HAL_QEI_EnableTypeDef   TimerEnable;    /*!< Timer Enable       */
    uint32_t                StartValue;     /*!< Timer Start Value  */
    uint32_t                Period;         /*!< Timer Period Value */
} HAL_QEI_TmrCntCfgTypeDef;

/**
  * @brief QEI Position Counter Compare Configuration Definition
  */
typedef struct {
    HAL_QEI_EnableTypeDef   CompareEnable;  /*!< Compare Enable         */
    HAL_QEI_EnableTypeDef   ShadowEnable;   /*!< Compare Shadow Enable  */
    uint32_t                CompareValue;   /*!< Compare Value          */
} HAL_QEI_PosCntCmpCfgTypeDef;

/**
  * @brief QEI Capture Configuration Definition
  */
typedef struct {
    HAL_QEI_EnableTypeDef           CaptureEnable;          /*!< Capture Enable                 */
    HAL_QEI_CapEvtDivTypeDef        EventDivision;          /*!< Capture Event Division         */
    HAL_QEI_CapTmrClkDivTypeDef     TimerClockDivision;     /*!< Capture Timer Clock Division   */
    HAL_QEI_CapLatchModeTypeDef     LatchMode;              /*!< Capture Latch Mode             */
} HAL_QEI_CapCfgTypeDef;


typedef struct HAL_QEI_HandleStructDef HAL_QEI_HandleTypeDef; /*!< HAL QEI handle structure type */

/**
  * @brief  QEI Handle Structure definition
  */
struct HAL_QEI_HandleStructDef
{
    QEI_TypeDef                     *Instance;          /*!< Register base address    */
    volatile HAL_QEI_StateTypeDef   State;              /*!< Global state             */
    volatile uint32_t               ErrorCode;          /*!< QEI error code           */
    const void                      *pUserData;         /*!< User data pointer        */
};

/**
  * @}
  */ /* QEI_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup QEI_HAL_Exported_Functions
  * @{
  */

/** @addtogroup QEI_HAL_EF_Initialization
  * @{
  */
HAL_StatusTypeDef HAL_QEI_Init(HAL_QEI_HandleTypeDef *Handle, QEI_TypeDef *QEIx);
HAL_StatusTypeDef HAL_QEI_DeInit(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_MspInit(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_MspDeInit(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_IoInit(QEI_TypeDef *QEIx);
void HAL_QEI_IoDeInit(QEI_TypeDef *QEIx);
/**
  * @}
  */ /* QEI_HAL_EF_Initialization */

/** @addtogroup QEI_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_QEI_PositionCounterConfig(HAL_QEI_HandleTypeDef *Handle, 
                                                const HAL_QEI_PosCntCfgTypeDef *pCfg);
HAL_StatusTypeDef HAL_QEI_TimerCounterConfig(HAL_QEI_HandleTypeDef *Handle, 
                                             const HAL_QEI_TmrCntCfgTypeDef *pCfg);
HAL_StatusTypeDef HAL_QEI_PositionCounterCompareConfig(HAL_QEI_HandleTypeDef *Handle, 
                                                       const HAL_QEI_PosCntCmpCfgTypeDef *pCfg);
HAL_StatusTypeDef HAL_QEI_CaptureConfig(HAL_QEI_HandleTypeDef *Handle, 
                                        const HAL_QEI_CapCfgTypeDef *pCfg);
/**
  * @}
  */ /* QEI_HAL_EF_Configuration */

/** @addtogroup QEI_HAL_EF_Operation
  * @{
  */
HAL_StatusTypeDef HAL_QEI_Enable(HAL_QEI_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_QEI_Disable(HAL_QEI_HandleTypeDef *Handle);

HAL_QEI_DirFstIdxStaTypeDef HAL_QEI_GetDirectionFirstIndexStatus(const HAL_QEI_HandleTypeDef *Handle);
HAL_QEI_DirIdxLchStaTypeDef HAL_QEI_GetDirectionIndexStatus(const HAL_QEI_HandleTypeDef *Handle);
HAL_QEI_DirStaTypeDef HAL_QEI_GetDirectionStatus(const HAL_QEI_HandleTypeDef *Handle);

HAL_QEI_CapOvfErrStaTypeDef HAL_QEI_GetCaptureOverflowErrorStatus(const HAL_QEI_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_QEI_ClearCaptureOverflowErrorStatus(const HAL_QEI_HandleTypeDef *Handle);
HAL_QEI_CapDirErrStaTypeDef HAL_QEI_GetCaptureDirectionErrorStatus(const HAL_QEI_HandleTypeDef *Handle);
HAL_StatusTypeDef HAL_QEI_ClearCaptureDirectionErrorStatus(const HAL_QEI_HandleTypeDef *Handle);

HAL_QEI_FstIdxStaTypeDef HAL_QEI_GetFirstIndexStatus(const HAL_QEI_HandleTypeDef *Handle);

uint32_t HAL_QEI_GetIndexEventPosition(const HAL_QEI_HandleTypeDef *Handle);
uint32_t HAL_QEI_GetIndexEventDiretion(const HAL_QEI_HandleTypeDef *Handle);
uint32_t HAL_QEI_GetTimerEventPosition(const HAL_QEI_HandleTypeDef *Handle);
uint32_t HAL_QEI_GetCaptureEventCounter(const HAL_QEI_HandleTypeDef *Handle);
uint32_t HAL_QEI_GetCaptureEventPeriod(const HAL_QEI_HandleTypeDef *Handle);
uint32_t HAL_QEI_GetCurrentPositionCounter(const HAL_QEI_HandleTypeDef *Handle);
/**
  * @}
  */ /* QEI_HAL_EF_Operation */

/** @addtogroup QEI_HAL_EF_Interrupt
  * @{
  */

HAL_StatusTypeDef HAL_QEI_InterruptRequestEnable(HAL_QEI_HandleTypeDef *Handle,
                                                 HAL_QEI_ITEnMskTypeDef InterruptRequests);

HAL_StatusTypeDef HAL_QEI_InterruptRequestDisable(HAL_QEI_HandleTypeDef *Handle,
                                                  HAL_QEI_ITEnMskTypeDef InterruptRequests);

void HAL_QEI_IRQHandler(HAL_QEI_HandleTypeDef *Handle);

void HAL_QEI_CaptureDoneCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PosCntResetCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PosCntInitialCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_TimerOverflowCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PosCntLatchCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PosCntCompareCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PosCntOverflowCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PosCntUnderflowCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_DirectionChangeCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PhaseErrorCallback(HAL_QEI_HandleTypeDef *Handle);
void HAL_QEI_PosCntErrorCallback(HAL_QEI_HandleTypeDef *Handle);
/**
  * @}
  */ /* QEI_HAL_EF_Interrupt */

/**
  * @}
  */ /* QEI_HAL_Exported_Functions */


/**
  * @}
  */ /* QEI_HAL */

#endif /* QEI */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_QEI_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

