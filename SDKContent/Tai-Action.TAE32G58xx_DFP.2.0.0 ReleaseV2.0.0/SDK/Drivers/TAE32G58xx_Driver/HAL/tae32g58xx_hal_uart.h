/**
  ******************************************************************************
  * @file    tae32g58xx_hal_uart.h
  * @author  Tai-Action SD Team
  * @brief   Header file of UART HAL module.
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
#ifndef _TAE32G58XX_HAL_UART_H_
#define _TAE32G58XX_HAL_UART_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_uart.h"

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @defgroup UART_HAL UART HAL
  * @brief    UART HAL Module Driver
  * @{
  */

/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup UART_HAL_Exported_Macros UART HAL Exported Macros
  * @brief    UART HAL Exported Macros
  * @{
  */

#ifndef TAE32_USE_HAL_UART_CHECK_PARAM
#define TAE32_USE_HAL_UART_CHECK_PARAM     0
#elif (TAE32_USE_HAL_UART_CHECK_PARAM != 1) && (TAE32_USE_HAL_UART_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_UART_CHECK_PARAM
#define TAE32_USE_HAL_UART_CHECK_PARAM     0
#endif

#define HAL_UART_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_UART_CHECK_PARAM) { \
            expression;                       \
        }

/** @defgroup UART_HAL_Interrupt_Mask UART HAL Interrupt Mask
  * @brief    UART HAL Interrupt Mask
  * @{
  */

#define HAL_UART_INTEN_AUTO_BAUDRATE_ERROR_IT_EN            LL_UART_IT_ABRE                                 /*!< ABRE Mask                */
#define HAL_UART_INTEN_RX_ADDRESS_MATCH_IT_EN               LL_UART_IT_AMIE                                 /*!< AMIE Mask                */
#define HAL_UART_INTEN_TX_IDLE_DONE_IT_EN                   LL_UART_IT_IDLE                                 /*!< IDLE Mask                */
#define HAL_UART_INTEN_TX_BREAK_DONE_IT_EN                  LL_UART_IT_TBIE                                 /*!< TBIE Mask                */
#define HAL_UART_INTEN_TX_DONE_IT_EN                        LL_UART_IT_TDIE                                 /*!< TDIE Mask                */
#define HAL_UART_INTEN_RX_TIMEOUT_IT_EN                     LL_UART_IT_RTIE                                 /*!< RTIE Mask                */
#define HAL_UART_INTEN_RX_BREAK_IT_EN                       LL_UART_IT_BKIE                                 /*!< BKIE Mask                */
#define HAL_UART_INTEN_FRAME_ERROR_IT_EN                    LL_UART_IT_FEIE                                 /*!< FEIE Mask                */
#define HAL_UART_INTEN_PARITY_ERROR_IT_EN                   LL_UART_IT_PEIE                                 /*!< PEIE Mask                */
#define HAL_UART_INTEN_NOISE_DETECTION_IT_EN                LL_UART_IT_NOIE                                 /*!< NOIE Mask                */
#define HAL_UART_INTEN_IDLE_IT_EN                           LL_UART_IT_IDIE                                 /*!< IDIE Mask                */
#define HAL_UART_INTEN_TX_FIFO_OVERFLOW_IT_EN               LL_UART_IT_TOIE                                 /*!< TOIE Mask                */
#define HAL_UART_INTEN_RX_FIFO_UNDERFLOW_IT_EN              LL_UART_IT_RUIE                                 /*!< RUIE Mask                */
#define HAL_UART_INTEN_RX_FIFO_OVERFLOW_IT_EN               LL_UART_IT_ROIE                                 /*!< ROIE Mask                */
#define HAL_UART_INTEN_TX_FIFO_EMPTY_IT_EN                  LL_UART_IT_TEIE                                 /*!< TEIE Mask                */
#define HAL_UART_INTEN_RX_FIFO_FULL_IT_EN                   LL_UART_IT_RFIE                                 /*!< RFIE Mask                */

/**
  * @}
  */ /* UART_HAL_Interrupt_Mask */

/** @defgroup UART_HAL_Flag UART flags (for HAL_UART_GET_FLAG / CLEAR_FLAG)
  * @{
  */

#define HAL_UART_INT_AUTO_BAUDRATE_ERROR_IT_FLAG            LL_UART_FLAG_ABRF                                   /*!< ABRF Mask                */
#define HAL_UART_INT_RX_ADDRESS_MATCH_IT_FLAG               LL_UART_FLAG_AMIF                                   /*!< AMIF Mask                */
#define HAL_UART_INT_TX_IDLE_DONE_IT_FLAG                   LL_UART_FLAG_IDLF                                   /*!< IDLF Mask                */
#define HAL_UART_INT_TX_BREAK_DONE_IT_FLAG                  LL_UART_FLAG_TBIF                                   /*!< TBIF Mask                */
#define HAL_UART_INT_TX_DONE_IT_FLAG                        LL_UART_FLAG_TDIF                                   /*!< TDIF Mask                */
#define HAL_UART_INT_RX_TIMEOUT_IT_FLAG                     LL_UART_FLAG_RTOI                                   /*!< RTOI Mask                */
#define HAL_UART_INT_RX_BREAK_IT_FLAG                       LL_UART_FLAG_BKIF                                   /*!< BKIF Mask                */
#define HAL_UART_INT_FRAME_ERROR_IT_FLAG                    LL_UART_FLAG_FEIF                                   /*!< FEIF Mask                */
#define HAL_UART_INT_PARITY_ERROR_IT_FLAG                   LL_UART_FLAG_PEIF                                   /*!< PEIF Mask                */
#define HAL_UART_INT_NOISE_DETECTION_IT_FLAG                LL_UART_FLAG_NOIF                                   /*!< NOIF Mask                */
#define HAL_UART_INT_IDLE_IT_FLAG                           LL_UART_FLAG_IDIF                                   /*!< IDIF Mask                */
#define HAL_UART_INT_TX_FIFO_OVERFLOW_IT_FLAG               LL_UART_FLAG_TOIF                                   /*!< TOIF Mask                */
#define HAL_UART_INT_RX_FIFO_UNDERFLOW_IT_FLAG              LL_UART_FLAG_RUIF                                   /*!< RUIF Mask                */
#define HAL_UART_INT_RX_FIFO_OVERFLOW_IT_FLAG               LL_UART_FLAG_ROIF                                   /*!< ROIF Mask                */
#define HAL_UART_INT_TX_FIFO_EMPTY_IT_FLAG                  LL_UART_FLAG_TXEI                                   /*!< TXEI Mask                */
#define HAL_UART_INT_RX_FIFO_FULL_IT_FLAG                   LL_UART_FLAG_RXFI                                   /*!< RXFI Mask                */

/**
  * @}
  */ /* UART_HAL_Flag */

/** @defgroup UART_HAL_Mode UART mode
  * @brief  Mode is a bit mask (RX | TX), so it is intentionally kept as #define.
  * @{
  */
#define HAL_UART_MODE_RX                  (0x1UL)  /*!< RX mode        */
#define HAL_UART_MODE_TX                  (0x2UL)  /*!< TX mode        */
#define HAL_UART_MODE_TX_RX               (0x3UL)  /*!< RX and TX mode */

/* Error codes */
#ifndef HAL_UART_ERROR_NONE
#define HAL_UART_ERROR_NONE                  0x00000000UL
#define HAL_UART_ERROR_PE                    0x00000001UL
#define HAL_UART_ERROR_NE                    0x00000002UL
#define HAL_UART_ERROR_FE                    0x00000004UL
#define HAL_UART_ERROR_ORE                   0x00000008UL
#define HAL_UART_ERROR_DMA                   0x00000010UL
#define HAL_UART_ERROR_RTO                   0x00000020UL
#define HAL_UART_ERROR_INVALID_CALLBACK      0x00000040UL
#define HAL_UART_ERROR_ABORT                 0x00000080UL
#endif
/**
  * @}
  */ /* UART_HAL_Mode */

/**
  * @brief UART State definition
  */
#define HAL_UART_StateMaskTypeDef                            uint32_t

#define HAL_UART_STATE_MASK_RESET                            (0U)                                           /*!< 0x0000: Peripheral is not initialized, value is reset */
#define HAL_UART_STATE_MASK_READY                            (1U << 15U)                                    /*!< 0x8000: Peripheral initialized and ready for use     */
#define HAL_UART_STATE_MASK_BUSY                             ((1U << 15U) | (1U << 2U))                     /*!< 0x8004: Internal process is ongoing                  */
#define HAL_UART_STATE_MASK_BUSY_TX                          ((1U << 15U) | (1U << 0U))                     /*!< 0x8001: Data Transmission process is ongoing         */
#define HAL_UART_STATE_MASK_BUSY_RX                          ((1U << 15U) | (1U << 1U))                     /*!< 0x8002: Data Reception process is ongoing            */
#define HAL_UART_STATE_MASK_BUSY_TX_RX                       ((1U << 15U) | (1U << 1U) | (1U << 0U))        /*!< 0x8003: TX and RX process is ongoing                 */
#define HAL_UART_STATE_MASK_TIMEOUT                          ((1U << 17U) | (1U << 5U))                     /*!< 0x020020: Timeout state                                */
#define HAL_UART_STATE_MASK_ERROR                            ((1U << 17U) | (1U << 6U) | (1U << 5U))        /*!< 0x020060: Error state                                  */

/**
  * @brief UART Reception type
  */
#define HAL_UART_ReceptionValueTypeDef                      uint32_t

#define HAL_UART_RECEPTION_VALUE_STANDARD                   (0x00000000UL)  /*!< Standard reception                                */
#define HAL_UART_RECEPTION_VALUE_TOIDLE                     (0x10000000UL)  /*!< Reception until IDLE event                        */
#define HAL_UART_RECEPTION_VALUE_TORTO                      (0x20000000UL)  /*!< Reception until Receiver Timeout                  */
#define HAL_UART_RECEPTION_VALUE_TOCHARMATCH                (0x30000000UL)  /*!< Reception until Character Match                   */

/**
  * @brief UART Receive event type
  */
#define HAL_UART_RxEventValueTypeDef                        uint32_t

#define HAL_UART_RXEVENT_VALUE_TC                           (0x00000000UL)  /*!< Transfer Complete event        */
#define HAL_UART_RXEVENT_VALUE_HT                           (0x10000000UL)  /*!< Half Transfer event            */
#define HAL_UART_RXEVENT_VALUE_IDLE                         (0x20000000UL)  /*!< IDLE line detected event       */

/**
  * @}
  */ /* UART_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup UART_HAL_Exported_Types UART HAL Exported Types
  * @brief    UART HAL Exported Types
  * @{
  */

/** @defgroup UART_HAL_Exported_Enumerations UART HAL Exported Enumerations
  * @{
  */


/**
  * @brief  HAL UART State definition
  * @note   HAL UART State value is a combination of 2 different substates:
  *         gState and RxState (see @ref HAL_UART_StateTypeDef).
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_UART_STATE_RESET             = HAL_UART_STATE_MASK_RESET,        /*!< 0x00: Peripheral is not initialized, value is reset */
    HAL_UART_STATE_READY             = HAL_UART_STATE_MASK_READY,        /*!< 0x20: Peripheral initialized and ready for use     */
    HAL_UART_STATE_BUSY              = HAL_UART_STATE_MASK_BUSY,         /*!< 0x24: Internal process is ongoing                  */
    HAL_UART_STATE_BUSY_TX           = HAL_UART_STATE_MASK_BUSY_TX,      /*!< 0x21: Data Transmission process is ongoing         */
    HAL_UART_STATE_BUSY_RX           = HAL_UART_STATE_MASK_BUSY_RX,      /*!< 0x22: Data Reception process is ongoing            */
    HAL_UART_STATE_BUSY_TX_RX        = HAL_UART_STATE_MASK_BUSY_TX_RX,   /*!< 0x23: TX and RX process is ongoing                 */
    HAL_UART_STATE_TIMEOUT           = HAL_UART_STATE_MASK_TIMEOUT,      /*!< 0xA0: Timeout state                                */
    HAL_UART_STATE_ERROR             = HAL_UART_STATE_MASK_ERROR,        /*!< 0xE0: Error state                                  */
} HAL_UART_StateTypeDef;

_Static_assert(sizeof(HAL_UART_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");
#endif

/**
  * @brief UART Reception type definition
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_UART_RECEPTION_STANDARD    = HAL_UART_RECEPTION_VALUE_STANDARD,    /*!< Standard reception              */
    HAL_UART_RECEPTION_TOIDLE      = HAL_UART_RECEPTION_VALUE_TOIDLE,      /*!< Reception until IDLE event      */
    HAL_UART_RECEPTION_TORTO       = HAL_UART_RECEPTION_VALUE_TORTO,       /*!< Reception until Receiver Timeout*/
    HAL_UART_RECEPTION_TOCHARMATCH = HAL_UART_RECEPTION_VALUE_TOCHARMATCH, /*!< Reception until Character Match */
} HAL_UART_ReceptionTypeDef;

_Static_assert(sizeof(HAL_UART_ReceptionTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");
#endif

/**
  * @brief UART Receive event type definition
  */
#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_UART_RXEVENT_TC   = HAL_UART_RXEVENT_VALUE_TC,    /*!< Transfer Complete event        */
    HAL_UART_RXEVENT_HT   = HAL_UART_RXEVENT_VALUE_HT,    /*!< Half Transfer event            */
    HAL_UART_RXEVENT_IDLE = HAL_UART_RXEVENT_VALUE_IDLE,  /*!< IDLE line detected event       */
} HAL_UART_RxEventTypeDef;

_Static_assert(sizeof(HAL_UART_RxEventTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");
#endif

/**
  * @}
  */ /* UART_HAL_Exported_Enumerations */

/** @defgroup UART_HAL_Advanced_Feature_Initialization Advanced feature initialization
  * @{
  */
typedef enum {
    HAL_UART_ADVFEATURE_NO_INIT = 0UL,    /*!< No advanced feature initialization */
    HAL_UART_ADVFEATURE_INIT    = 1UL     /*!< Advanced feature initialization enabled */
} HAL_UART_AdvFeatureInitTypeDef;
/**
 * @}
 */ /* UART_HAL_Advanced_Feature_Initialization */

/** @defgroup UART_HAL_Advanced_Feature_Option Advanced feature options
  * @{
  */
typedef enum {
    HAL_UART_ADVFEATURE_DISABLE = 0UL,   /*!< Advanced feature disabled */
    HAL_UART_ADVFEATURE_ENABLE  = 1UL    /*!< Advanced feature enabled  */
} HAL_UART_AdvFeatureStateTypeDef;

typedef enum {
    HAL_UART_ADVFEATURE_RS485_DISABLE = 0UL,
    HAL_UART_ADVFEATURE_RS485_ENABLE  = 1UL
} HAL_UART_AdvFeatureRS485TypeDef;

typedef enum {
    HAL_UART_ADVFEATURE_RX_TIMEOUT_DISABLE = 0UL,
    HAL_UART_ADVFEATURE_RX_TIMEOUT_ENABLE  = 1UL
} HAL_UART_AdvFeatureRxTimeoutTypeDef;

typedef enum {
    HAL_UART_ADVFEATURE_TXINV_DISABLE = 0UL,
    HAL_UART_ADVFEATURE_TXINV_ENABLE  = 1UL
} HAL_UART_AdvFeatureTxInvTypeDef;

typedef enum {
    HAL_UART_ADVFEATURE_RXINV_DISABLE = 0UL,
    HAL_UART_ADVFEATURE_RXINV_ENABLE  = 1UL
} HAL_UART_AdvFeatureRxInvTypeDef;

typedef enum {
    HAL_UART_ADVFEATURE_SWAP_DISABLE = 0UL,
    HAL_UART_ADVFEATURE_SWAP_ENABLE  = 1UL
} HAL_UART_AdvFeaturePinSwapTypeDef;

typedef enum {
    HAL_UART_ADVFEATURE_LOOPBACK_DISABLE = 0UL,
    HAL_UART_ADVFEATURE_LOOPBACK_ENABLE  = 1UL
} HAL_UART_AdvFeatureLoopbackTypeDef;

typedef enum {
    HAL_UART_ADVFEATURE_MSBFIRST_DISABLE = 0UL,
    HAL_UART_ADVFEATURE_MSBFIRST_ENABLE  = 1UL
} HAL_UART_AdvFeatureMSBFirstTypeDef;

typedef enum {
    HAL_UART_DE_POLARITY_LOW  = 0x0UL,             /*!< DE signal is active low  (CR1.DEP=0) */
    HAL_UART_DE_POLARITY_HIGH = 0x1UL              /*!< DE signal is active high (CR1.DEP=1) */
} HAL_UART_DepolarityTypeDef;

typedef enum {
    HAL_UART_AUTOBAUD_MODE_1FALLING = 0x0UL,       /*!< 1 falling edge measurement   */
    HAL_UART_AUTOBAUD_MODE_1RISING  = 0x1UL,       /*!< 1 rising edge measurement    */
    HAL_UART_AUTOBAUD_MODE_2FALLING = 0x2UL,       /*!< 2 falling edges measurement  */
    HAL_UART_AUTOBAUD_MODE_2RISING  = 0x3UL        /*!< 2 rising edges measurement   */
} HAL_UART_AutoBaudModeTypeDef;
/**
  * @}
  */ /* UART_HAL_Advanced_Feature_Option */

/** @defgroup UART_HAL_Word_Length Character length
  * @{
  */
typedef enum {
    HAL_UART_WORDLENGTH_5B = LL_UART_DATAWIDTH_5B,   /*!< 5-bit data length */
    HAL_UART_WORDLENGTH_6B = LL_UART_DATAWIDTH_6B,   /*!< 6-bit data length */
    HAL_UART_WORDLENGTH_7B = LL_UART_DATAWIDTH_7B,   /*!< 7-bit data length */
    HAL_UART_WORDLENGTH_8B = LL_UART_DATAWIDTH_8B    /*!< 8-bit data length */
} HAL_UART_WordLengthTypeDef;
/**
  * @}
  */ /* UART_HAL_Word_Length */

/** @defgroup UART_HAL_Stop_Bits Stop bits
  * @{
  */
typedef enum {
    HAL_UART_STOPBITS_1 = LL_UART_STOPBITS_1,     /*!< 1 stop bit  */
    HAL_UART_STOPBITS_2 = LL_UART_STOPBITS_2      /*!< 2 stop bits */
} HAL_UART_StopBitsTypeDef;
/**
  * @}
  */ /* UART_HAL_Stop_Bits */

/** @defgroup UART_HAL_Parity Parity
  * @{
  */
typedef enum {
    HAL_UART_PARITY_NONE = LL_UART_PARITY_NONE,    /*!< No parity   */
    HAL_UART_PARITY_EVEN = LL_UART_PARITY_EVEN,    /*!< Even parity */
    HAL_UART_PARITY_ODD  = LL_UART_PARITY_ODD      /*!< Odd parity  */
} HAL_UART_ParityTypeDef;
/**
  * @}
  */ /* UART_HAL_Parity */

/** @defgroup UART_HAL_Oversampling Oversampling
  * @{
  */
typedef enum {
    HAL_UART_OVERSAMPLING_16 = LL_UART_OVERSAMPLING_16,  /*!< Oversampling by 16 */
    HAL_UART_OVERSAMPLING_8  = LL_UART_OVERSAMPLING_8    /*!< Oversampling by 8  */
} HAL_UART_OverSamplingTypeDef;
/**
  * @}
  */ /* UART_HAL_Oversampling */

  #if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL UART Callback ID enumeration definition
  */
typedef enum {
    HAL_UART_TX_HALFCOMPLETE_CB_ID         = 0x00UL,  /*!< UART Tx Half Complete Callback ID        */
    HAL_UART_TX_COMPLETE_CB_ID             = 0x01UL,  /*!< UART Tx Complete Callback ID             */
    HAL_UART_RX_HALFCOMPLETE_CB_ID         = 0x02UL,  /*!< UART Rx Half Complete Callback ID        */
    HAL_UART_RX_COMPLETE_CB_ID             = 0x03UL,  /*!< UART Rx Complete Callback ID             */
    HAL_UART_ERROR_CB_ID                   = 0x04UL,  /*!< UART Error Callback ID                   */
    HAL_UART_ABORT_COMPLETE_CB_ID          = 0x05UL,  /*!< UART Abort Complete Callback ID          */
    HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID = 0x06UL,  /*!< UART Abort Transmit Complete Callback ID */
    HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID  = 0x07UL,  /*!< UART Abort Receive Complete Callback ID  */
    HAL_UART_RX_FIFO_FULL_CB_ID            = 0x10UL,  /*!< UART Rx FIFO Full Callback ID            */
    HAL_UART_TX_FIFO_EMPTY_CB_ID           = 0x11UL,  /*!< UART Tx FIFO Empty Callback ID           */
    HAL_UART_MSPINIT_CB_ID                 = 0x0BUL,  /*!< UART MspInit callback ID                 */
    HAL_UART_MSPDEINIT_CB_ID               = 0x0CUL,  /*!< UART MspDeInit callback ID               */

    HAL_UART_CB_ID_CLEAR                = 0xFFUL   /*!< UART Callback ID clear to default     */
} HAL_UART_CallbackIDTypeDef;
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

/**
  * @brief  UART advanced feature initialization structure definition
  * @note   These map to the TAE32 hardware RS485 / auto-baud / timeout / pin
  *         options. Only applied when AdvFeatureInit != HAL_UART_ADVFEATURE_NO_INIT.
  */
typedef struct {
    HAL_UART_AdvFeatureRS485TypeDef RS485Mode;       /*!< RS485 mode enable/disable            */
    HAL_UART_DepolarityTypeDef      DEPolarity;      /*!< DE polarity (HAL_UART_DE_POLARITY_*) */
    uint32_t DEAssertionTime;    /*!< DE assertion time, 0..0xFFFF                */
    uint32_t DEDeassertionTime;  /*!< DE de-assertion time, 0..0xFFFF             */
    HAL_UART_AutoBaudModeTypeDef   AutoBaudRateMode; /*!< Auto-baud mode (HAL_UART_AUTOBAUD_MODE_*) */
    HAL_UART_AdvFeatureRxTimeoutTypeDef ReceiverTimeout; /*!< Rx timeout enable/disable        */
    uint32_t RxTimeoutValue;     /*!< Receive timeout value, 0..0xFFFF            */
    HAL_UART_AdvFeatureTxInvTypeDef TxPinInv;        /*!< TX pin inversion enable/disable      */
    HAL_UART_AdvFeatureRxInvTypeDef RxPinInv;        /*!< RX pin inversion enable/disable      */
    HAL_UART_AdvFeaturePinSwapTypeDef PinSwap;       /*!< TX/RX pin swap enable/disable        */
    HAL_UART_AdvFeatureLoopbackTypeDef Loopback;     /*!< Loopback enable/disable              */
    HAL_UART_AdvFeatureMSBFirstTypeDef MSBFirst;     /*!< MSB-first enable/disable              */
} HAL_UART_AdvFeatureTypeDef;


/**
  * @brief  UART Init Structure definition
  */
typedef struct {
    uint32_t BaudRate;           /*!< Configures the UART communication baud rate */

    HAL_UART_WordLengthTypeDef WordLength;         /*!< Specifies the number of data bits transmitted or received
                                       in a frame. @ref HAL_UART_WORDLENGTH_5B .. _8B */

    HAL_UART_StopBitsTypeDef StopBits;           /*!< Specifies the number of stop bits transmitted. @ref HAL_UART_STOPBITS_1 .. _2 */

    HAL_UART_ParityTypeDef Parity;             /*!< Specifies the parity mode. @ref HAL_UART_PARITY_NONE / EVEN / ODD */

    uint32_t Mode;               /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                       @ref HAL_UART_MODE_RX / TX / TX_RX */

    HAL_UART_OverSamplingTypeDef OverSampling;       /*!< Specifies the oversampling. @ref HAL_UART_OVERSAMPLING_16 / _8 */

    HAL_UART_AdvFeatureInitTypeDef AdvFeatureInit;  /*!< Specifies which advanced features are initialized.
                                       HAL_UART_ADVFEATURE_NO_INIT or HAL_UART_ADVFEATURE_INIT */

    HAL_UART_AdvFeatureTypeDef Init;  /*!< Advanced features initialization parameters */
} HAL_UART_InitTypeDef;

typedef struct HAL_UART_HandleStructDef HAL_UART_HandleTypeDef; /*!< HAL UART handle structure type */

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
typedef void (*HAL_UART_CallbackTypeDef)(HAL_UART_HandleTypeDef *huart); /*!< HAL UART Callback pointer definition */
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

/**
  * @brief  UART handle Structure definition
  */
struct HAL_UART_HandleStructDef {
    UART_TypeDef                 *Instance;             /*!< UART registers base address        */

    volatile HAL_UART_StateTypeDef  gState;             /*!< UART state information related to global handle management
                                                          and also related to Tx operations (same as RxState if
                                                          not in parallel mode) */

    volatile HAL_UART_StateTypeDef  RxState;            /*!< UART state information related to Rx operations */

    volatile uint32_t           ErrorCode;              /*!< UART Error code                    */

    const void                  *pUserData;             /*!< User data pointer                  */

    const uint8_t               *pTxBuffPtr;            /*!< Pointer to UART Tx transfer Buffer */
    uint16_t                    TxXferSize;             /*!< UART Tx Transfer size              */
    volatile uint16_t           TxXferCount;            /*!< UART Tx Transfer Counter           */

    uint8_t                     *pRxBuffPtr;            /*!< Pointer to UART Rx transfer Buffer */
    uint16_t                    RxXferSize;             /*!< UART Rx Transfer size              */
    volatile uint16_t           RxXferCount;            /*!< UART Rx Transfer Counter           */

    void (*RxISR)(HAL_UART_HandleTypeDef *huart);       /*!< Function pointer on Rx IRQ handler */

    volatile HAL_UART_ReceptionTypeDef  ReceptionType;  /*!< Reception type.*/
    volatile HAL_UART_RxEventTypeDef    RxEventType;    /*!< Rx event type of the last completed reception.*/

    void (*TxISR)(HAL_UART_HandleTypeDef *huart);       /*!< Function pointer on Tx IRQ handler */

#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
    HAL_DMA_HandleTypeDef       *hTxDMA;                /* Tx DMA handle                        */
    HAL_DMA_HandleTypeDef       *hRxDMA;                /* Rx DMA handle                        */
#endif /* USE_HAL_UART_DMA */

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    HAL_UART_CallbackTypeDef TxCpltCallback;
    HAL_UART_CallbackTypeDef TxHalfCpltCallback;
    HAL_UART_CallbackTypeDef RxCpltCallback;
    HAL_UART_CallbackTypeDef RxHalfCpltCallback;
    HAL_UART_CallbackTypeDef ErrorCallback;
    HAL_UART_CallbackTypeDef AbortCpltCallback;
    HAL_UART_CallbackTypeDef AbortTransmitCpltCallback;
    HAL_UART_CallbackTypeDef AbortReceiveCpltCallback;
    HAL_UART_CallbackTypeDef RxEventCallback;
    HAL_UART_CallbackTypeDef RxFifoFullCallback;
    HAL_UART_CallbackTypeDef TxFifoEmptyCallback;
    HAL_UART_CallbackTypeDef MspInitCallback;
    HAL_UART_CallbackTypeDef MspDeInitCallback;
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
};



/**
  * @}
  */ /* UART_HAL_Exported_Types */





/* Exported Functions --------------------------------------------------------*/
/** @defgroup UART_HAL_Exported_Functions UART HAL Exported Functions
  * @brief    UART HAL Exported Functions
  * @{
  */
  
/** @addtogroup UART_HAL_EF_Init Initialization and de-initialization functions
  * @{
  */
HAL_StatusTypeDef HAL_UART_Init(HAL_UART_HandleTypeDef *huart, UART_TypeDef *UARTx,
                                HAL_UART_InitTypeDef *Init);
HAL_StatusTypeDef HAL_UART_DeInit(HAL_UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UART_SetTxDMA(HAL_UART_HandleTypeDef *huart, HAL_DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_UART_SetRxDMA(HAL_UART_HandleTypeDef *huart, HAL_DMA_HandleTypeDef *hdma);

void HAL_UART_MspInit(HAL_UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(HAL_UART_HandleTypeDef *huart);
/**
  * @}
  */ /* UART_HAL_EF_Init */

/** @addtogroup UART_HAL_EF_IO IO operation functions
  * @{
  */
HAL_StatusTypeDef HAL_UART_Transmit(HAL_UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(HAL_UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
HAL_StatusTypeDef HAL_UART_Transmit_DMA(HAL_UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
#endif /* USE_HAL_UART_DMA */


HAL_StatusTypeDef HAL_UART_FlushRx(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_FlushTx(HAL_UART_HandleTypeDef *huart);
uint32_t HAL_UART_GetFlag(const HAL_UART_HandleTypeDef *huart, uint32_t Flag);

HAL_StatusTypeDef HAL_UART_Abort(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort_IT(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(HAL_UART_HandleTypeDef *huart);
void HAL_UART_IRQHandler(HAL_UART_HandleTypeDef *huart);
/**
  * @}
  */ /* UART_HAL_EF_IO */

/** @addtogroup UART_HAL_EF_State Peripheral state and error functions
  * @{
  */
HAL_UART_StateTypeDef HAL_UART_GetState(const HAL_UART_HandleTypeDef *huart);
uint32_t HAL_UART_GetError(const HAL_UART_HandleTypeDef *huart);
/**
  * @}
  */ /* UART_HAL_EF_State */


/** @addtogroup UART_HAL_EF_Callback Callback registration
  * @{
  */

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_UART_RegisterCallback(HAL_UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
                                            HAL_UART_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_UART_UnRegisterCallback(HAL_UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_UART_RegisterRxEventCallback(HAL_UART_HandleTypeDef *huart, HAL_UART_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_UART_UnRegisterRxEventCallback(HAL_UART_HandleTypeDef *huart);

#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
/**
 * @}
 */ /* UART_HAL_EF_Callback */


/** @defgroup UART_HAL_EF_Timeout_Fifo Receiver Timeout and FIFO Threshold functions
  * @brief    Receiver timeout (RTO) and FIFO threshold configuration functions.
  * @{
  */
/* Receiver timeout (RTO) */
void              HAL_UART_ReceiverTimeout_Config(HAL_UART_HandleTypeDef *huart, uint32_t TimeoutValue);
HAL_StatusTypeDef HAL_UART_EnableReceiverTimeout(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DisableReceiverTimeout(HAL_UART_HandleTypeDef *huart);
/* FIFO thresholds */
HAL_StatusTypeDef HAL_UART_SetTxFifoThreshold(HAL_UART_HandleTypeDef *huart, uint32_t Threshold);
HAL_StatusTypeDef HAL_UART_SetRxFifoThreshold(HAL_UART_HandleTypeDef *huart, uint32_t Threshold);
/* FIFO mode */
HAL_StatusTypeDef HAL_UART_EnableFifoMode(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DisableFifoMode(HAL_UART_HandleTypeDef *huart);
/**
  * @}
  */ /* UART_HAL_EF_Timeout_Fifo */

/** @defgroup UART_HAL_EF_DMA DMA transfer control functions
  * @brief    DMA transfer control functions.
  * @{
  */

#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
HAL_StatusTypeDef HAL_UART_DMAPause(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(HAL_UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(HAL_UART_HandleTypeDef *huart);
#endif /* USE_HAL_UART_DMA */

/**
  * @}
  */ /* UART_HAL_EF_DMA */

/** @defgroup UART_HAL_EF_RxEvent Reception event functions
  * @brief    Reception event functions.
  * @{
  */
HAL_StatusTypeDef HAL_UART_ReceiveToIdle(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size,
                                           uint16_t *RxLen, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_ReceiveToIdle_IT(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

#if defined (USE_HAL_UART_DMA) && (USE_HAL_UART_DMA == 1)
HAL_StatusTypeDef HAL_UART_ReceiveToIdle_DMA(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
#endif /* USE_HAL_UART_DMA */

uint32_t          HAL_UART_GetRxEventType(const HAL_UART_HandleTypeDef *huart);
/**
  * @}
  */ /* UART_HAL_EF_RxEvent */

/** @addtogroup UART_HAL_EF_ITCallback
  * @{
  */
void HAL_UART_TxCpltCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_RxEventCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_RxFifoFullCallback(HAL_UART_HandleTypeDef *huart);
void HAL_UART_TxFifoEmptyCallback(HAL_UART_HandleTypeDef *huart);
/**
  * @}
  */ /* UART_HAL_EF_ITCallback */

/**
  * @brief  Judge whether the UART peripheral is clocked by APB1 (PCLK1).
  * @param  UARTx UART peripheral instance.
  * @retval 1 if the UART is on APB1, 0 otherwise (i.e. on APB0).
  */
__STATIC_INLINE uint32_t HAL_UART_IsOnAPB1(const UART_TypeDef *UARTx)
{
    return LL_UART_IsOnAPB1(UARTx);
}

/**
  * @}
  */ /* UART_HAL_Exported_Functions */


/**
 * @}
 */ /* UART_HAL */

/**
 * @}
 */ /* TAE32G58xx_HAL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_UART_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
