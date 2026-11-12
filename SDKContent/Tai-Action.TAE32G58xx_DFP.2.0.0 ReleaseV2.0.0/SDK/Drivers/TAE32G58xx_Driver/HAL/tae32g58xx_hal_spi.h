/**
  ******************************************************************************
  * @file    tae32g58xx_hal_spi.h
  * @author  Tai-Action SD Team
  * @brief   Header file for SPI HAL module
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
#ifndef _TAE32G58XX_HAL_SPI_H_
#define _TAE32G58XX_HAL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal_def.h"
#include "tae32g58xx_ll_spi.h"


/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

#if defined(SPI0) || defined(SPI1)

/** @addtogroup SPI_HAL
  * @{
  */


/** @defgroup SPI_HAL_Private_Configuration SPI HAL Private Configuration
  * @brief    SPI HAL build-time configuration
  * @note     Kept ahead of the exported constants because the option below
  *           guards HAL_SPI_ERROR_INVALID_CALLBACK and the callback ID enum.
  * @{
  */
/**
  * @brief  Enable (1) or disable (0) the SPI callback registration feature
  */
#ifndef USE_HAL_SPI_REGISTER_CALLBACKS
#define USE_HAL_SPI_REGISTER_CALLBACKS                  (0U)
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @}
  */ /* SPI_HAL_Private_Configuration */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup SPI_HAL_Exported_Constants SPI HAL Exported Constants
  * @brief    SPI HAL Exported Constants
  * @{
  */

/** @defgroup HAL_SPI_EC_Error_Code SPI HAL Error Code
  * @brief    SPI HAL Error Code
  * @{
  */
#define HAL_SPI_ERROR_NONE                              (0x00000000UL)  /*!< No error                         */
#define HAL_SPI_ERROR_MODF                              (0x00000001UL)  /*!< Mode fault error                 */
#define HAL_SPI_ERROR_OVR                               (0x00000002UL)  /*!< Overrun error (RxFIFO overflow)  */
#define HAL_SPI_ERROR_UDR                               (0x00000004UL)  /*!< Underrun error (TxFIFO underflow)*/
#define HAL_SPI_ERROR_DMA                               (0x00000008UL)  /*!< DMA transfer error               */
#define HAL_SPI_ERROR_FLAG                              (0x00000010UL)  /*!< Error flag check failure         */
#define HAL_SPI_ERROR_ABORT                             (0x00000020UL)  /*!< Abort error                      */
#define HAL_SPI_ERROR_OPF                               (0x00000040UL)  /*!< Operation fault error            */
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
#define HAL_SPI_ERROR_INVALID_CALLBACK                  (0x00000080UL)  /*!< Invalid callback error           */
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
#define HAL_SPI_ERROR_TIMEOUT                           (0x00000100UL)  /*!< Timeout error                    */
/**
  * @}
  */ /* HAL_SPI_EC_Error_Code */


/** @defgroup HAL_SPI_EC_Mode SPI HAL Operating Mode
  * @brief    SPI HAL Operating Mode
  * @{
  */
typedef enum
{
    HAL_SPI_MODE_SLAVE  = LL_SPI_ROLE_SLAVE,  /*!< SPI slave mode  */
    HAL_SPI_MODE_MASTER = LL_SPI_ROLE_MASTER  /*!< SPI master mode */
} HAL_SPI_ModeTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_Mode */


/** @defgroup HAL_SPI_EC_Direction SPI HAL Data Direction Mode
  * @brief    SPI HAL Data Direction Mode
  * @{
  */
typedef enum
{
    HAL_SPI_DIRECTION_2LINES        = LL_SPI_FULL_DUPLEX,  /*!< 2 lines: full duplex        */
    HAL_SPI_DIRECTION_2LINES_RXONLY = LL_SPI_HALF_DUPLEX_RX,  /*!< 2 lines: receive only       */
    HAL_SPI_DIRECTION_1LINE         = LL_SPI_HALF_DUPLEX_TX  /*!< 1 line : transmit only (3-wire) */
} HAL_SPI_DirectionTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_Direction */


/** @defgroup HAL_SPI_EC_DataSize SPI HAL Data Size
  * @brief    SPI HAL Data Size
  * @{
  */
typedef enum
{
    HAL_SPI_DATASIZE_4BIT  = LL_SPI_DATA_WIDTH_4BIT,  /*!< 4-bit data size  */
    HAL_SPI_DATASIZE_5BIT  = LL_SPI_DATA_WIDTH_5BIT,  /*!< 5-bit data size  */
    HAL_SPI_DATASIZE_6BIT  = LL_SPI_DATA_WIDTH_6BIT,  /*!< 6-bit data size  */
    HAL_SPI_DATASIZE_7BIT  = LL_SPI_DATA_WIDTH_7BIT,  /*!< 7-bit data size  */
    HAL_SPI_DATASIZE_8BIT  = LL_SPI_DATA_WIDTH_8BIT,  /*!< 8-bit data size  */
    HAL_SPI_DATASIZE_9BIT  = LL_SPI_DATA_WIDTH_9BIT,  /*!< 9-bit data size  */
    HAL_SPI_DATASIZE_10BIT = LL_SPI_DATA_WIDTH_10BIT,  /*!< 10-bit data size */
    HAL_SPI_DATASIZE_11BIT = LL_SPI_DATA_WIDTH_11BIT,  /*!< 11-bit data size */
    HAL_SPI_DATASIZE_12BIT = LL_SPI_DATA_WIDTH_12BIT,  /*!< 12-bit data size */
    HAL_SPI_DATASIZE_13BIT = LL_SPI_DATA_WIDTH_13BIT,  /*!< 13-bit data size */
    HAL_SPI_DATASIZE_14BIT = LL_SPI_DATA_WIDTH_14BIT,  /*!< 14-bit data size */
    HAL_SPI_DATASIZE_15BIT = LL_SPI_DATA_WIDTH_15BIT,  /*!< 15-bit data size */
    HAL_SPI_DATASIZE_16BIT = LL_SPI_DATA_WIDTH_16BIT  /*!< 16-bit data size */
} HAL_SPI_DataSizeTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_DataSize */


/** @defgroup HAL_SPI_EC_ClockPolarity SPI HAL Clock Polarity
  * @brief    SPI HAL Clock Polarity
  * @{
  */
typedef enum
{
    HAL_SPI_POLARITY_LOW  = LL_SPI_SCLK_POL_IDLE_LOW,  /*!< SCK idle low  */
    HAL_SPI_POLARITY_HIGH = LL_SPI_SCLK_POL_IDLE_HIGH  /*!< SCK idle high */
} HAL_SPI_ClockPolarityTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_ClockPolarity */


/** @defgroup HAL_SPI_EC_ClockPhase SPI HAL Clock Phase
  * @brief    SPI HAL Clock Phase
  * @{
  */
typedef enum
{
    HAL_SPI_PHASE_1EDGE = LL_SPI_SCLK_PHASE_CAP_EDGE_0,  /*!< Data sampled on first edge  */
    HAL_SPI_PHASE_2EDGE = LL_SPI_SCLK_PHASE_CAP_EDGE_1  /*!< Data sampled on second edge */
} HAL_SPI_ClockPhaseTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_ClockPhase */


/** @defgroup HAL_SPI_EC_CS SPI HAL Chip Select Management
  * @brief    SPI HAL Chip Select Management
  * @{
  */
typedef enum
{
    HAL_SPI_CS_SOFT = LL_SPI_CS_SOFT,  /*!< Software CS management */
    HAL_SPI_CS_HARD = LL_SPI_CS_HARD  /*!< Hardware CS management */
} HAL_SPI_CSTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_CS */


/** @defgroup HAL_SPI_EC_BaudRatePrescaler SPI HAL BaudRate Prescaler
  * @brief    SPI HAL BaudRate Prescaler
  * @note     The communication clock is derived from PCLK, baud rate = PCLK / prescaler.
  * @{
  */
typedef enum
{
    HAL_SPI_BAUDRATEPRESCALER_2   = LL_SPI_BAUDRATE_DIV_2,  /*!< PCLK / 2   */
    HAL_SPI_BAUDRATEPRESCALER_4   = LL_SPI_BAUDRATE_DIV_4,  /*!< PCLK / 4   */
    HAL_SPI_BAUDRATEPRESCALER_8   = LL_SPI_BAUDRATE_DIV_8,  /*!< PCLK / 8   */
    HAL_SPI_BAUDRATEPRESCALER_16  = LL_SPI_BAUDRATE_DIV_16,  /*!< PCLK / 16  */
    HAL_SPI_BAUDRATEPRESCALER_32  = LL_SPI_BAUDRATE_DIV_32,  /*!< PCLK / 32  */
    HAL_SPI_BAUDRATEPRESCALER_64  = LL_SPI_BAUDRATE_DIV_64,  /*!< PCLK / 64  */
    HAL_SPI_BAUDRATEPRESCALER_128 = LL_SPI_BAUDRATE_DIV_128,  /*!< PCLK / 128 */
    HAL_SPI_BAUDRATEPRESCALER_256 = LL_SPI_BAUDRATE_DIV_256  /*!< PCLK / 256 */
} HAL_SPI_BaudRatePrescalerTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_BaudRatePrescaler */


/** @defgroup HAL_SPI_EC_FirstBit SPI HAL MSB/LSB Transmission
  * @brief    SPI HAL MSB/LSB Transmission
  * @{
  */
typedef enum
{
    HAL_SPI_FIRSTBIT_MSB = LL_SPI_BIT_ORDER_MSB,  /*!< MSB transmitted first */
    HAL_SPI_FIRSTBIT_LSB = LL_SPI_BIT_ORDER_LSB  /*!< LSB transmitted first */
} HAL_SPI_FirstBitTypeDef;
/**
  * @}
  */ /* HAL_SPI_EC_FirstBit */


/** @defgroup HAL_SPI_EC_CSMode SPI HAL CS Mode
  * @brief    SPI HAL CS Mode
  * @{
  */
#define HAL_SPI_CS_MODE_CONTINUE                        (LL_SPI_CS_MODE_CONTINUE)     /*!< CS kept active between frames */
#define HAL_SPI_CS_MODE_ONE                             (LL_SPI_CS_MODE_ONE)          /*!< CS deasserted between frames  */
#define HAL_SPI_CS_POL_INACT_HIGH                       (LL_SPI_CS_POL_INACT_HIGH)    /*!< CS inactive level is high     */
#define HAL_SPI_CS_POL_INACT_LOW                        (LL_SPI_CS_POL_INACT_LOW)     /*!< CS inactive level is low      */
/**
  * @}
  */ /* HAL_SPI_EC_CSMode */


/** @defgroup HAL_SPI_EC_Flag SPI HAL Status Flags
  * @brief    SPI HAL Status Flags
  * @{
  */
#define HAL_SPI_FLAG_TXE                                (LL_SPI_INT_TXEI)         /*!< Tx FIFO empty flag   */
#define HAL_SPI_FLAG_RXNE                               (LL_SPI_INT_RXFI)         /*!< Rx FIFO full flag    */
#define HAL_SPI_FLAG_BUSY                               (LL_SPI_STATUS_BUSY)      /*!< Busy flag            */
#define HAL_SPI_FLAG_MODF                               (LL_SPI_INT_MDFI)         /*!< Mode fault flag      */
#define HAL_SPI_FLAG_OVR                                (LL_SPI_INT_RXOFI)        /*!< Rx overflow flag     */
#define HAL_SPI_FLAG_OPF                                (LL_SPI_INT_OPFI)         /*!< Operation fault flag */
/**
  * @}
  */ /* HAL_SPI_EC_Flag */
/** @defgroup SPI_HAL_EM_Mask SPI HAL Mask
  * @brief    SPI HAL Mask
  * @{
  */

/**
  * @brief  Check SPI operating mode.
  * @param  mode SPI operating mode
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_MODE(mode)                                               \
        (((mode) == HAL_SPI_MODE_SLAVE)  || ((mode) == HAL_SPI_MODE_MASTER))

/**
  * @brief  Check SPI data direction mode.
  * @param  mode SPI data direction mode
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_DIRECTION(mode)                                          \
        (((mode) == HAL_SPI_DIRECTION_2LINES)          ||                   \
         ((mode) == HAL_SPI_DIRECTION_2LINES_RXONLY)   ||                   \
         ((mode) == HAL_SPI_DIRECTION_1LINE))

/**
  * @brief  Check SPI data size value.
  * @param  datasize SPI data size
  * @return 0: Invalid, 1: Valid
  * @note   Valid range: HAL_SPI_DATASIZE_4BIT to HAL_SPI_DATASIZE_16BIT.
  */
#define IS_HAL_SPI_DATASIZE(datasize)                                       \
        (((datasize) >= HAL_SPI_DATASIZE_4BIT) && ((datasize) <= HAL_SPI_DATASIZE_16BIT))

/**
  * @brief  Check SPI clock polarity.
  * @param  cpol SPI clock polarity
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_CPOL(cpol)                                               \
        (((cpol) == HAL_SPI_POLARITY_LOW) || ((cpol) == HAL_SPI_POLARITY_HIGH))

/**
  * @brief  Check SPI clock phase.
  * @param  cpha SPI clock phase
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_CPHA(cpha)                                               \
        (((cpha) == HAL_SPI_PHASE_1EDGE)  || ((cpha) == HAL_SPI_PHASE_2EDGE))

/**
  * @brief  Check SPI CS management mode.
  * @param  cs SPI CS configuration
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_CS(cs)                                                   \
        (((cs) == HAL_SPI_CS_SOFT) || ((cs) == HAL_SPI_CS_HARD))

/**
  * @brief  Check SPI baud rate prescaler.
  * @param  prescaler SPI baud rate prescaler
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_BAUDRATE_PRESCALER(prescaler)                            \
        (((prescaler) == HAL_SPI_BAUDRATEPRESCALER_2)    ||                 \
         ((prescaler) == HAL_SPI_BAUDRATEPRESCALER_4)    ||                 \
         ((prescaler) == HAL_SPI_BAUDRATEPRESCALER_8)    ||                 \
         ((prescaler) == HAL_SPI_BAUDRATEPRESCALER_16)   ||                 \
         ((prescaler) == HAL_SPI_BAUDRATEPRESCALER_32)   ||                 \
         ((prescaler) == HAL_SPI_BAUDRATEPRESCALER_64)   ||                 \
         ((prescaler) == HAL_SPI_BAUDRATEPRESCALER_128)  ||                 \
         ((prescaler) == HAL_SPI_BAUDRATEPRESCALER_256))

/**
  * @brief  Check SPI first bit (MSB/LSB) configuration.
  * @param  bit SPI first bit mode
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_FIRST_BIT(bit)                                           \
        (((bit) == HAL_SPI_FIRSTBIT_MSB) || ((bit) == HAL_SPI_FIRSTBIT_LSB))

/**
  * @brief  Check whether the direction has a TX phase.
  * @param  init Pointer to a HAL_SPI_InitTypeDef structure
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_HAS_TX_PHASE(init)                                       \
        (((init)->Direction == HAL_SPI_DIRECTION_2LINES) ||                 \
         ((init)->Direction == HAL_SPI_DIRECTION_1LINE))

/**
  * @brief  Check whether the direction has an RX phase.
  * @param  init Pointer to a HAL_SPI_InitTypeDef structure
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_HAS_RX_PHASE(init)                                       \
        (((init)->Direction == HAL_SPI_DIRECTION_2LINES) ||                 \
         ((init)->Direction == HAL_SPI_DIRECTION_2LINES_RXONLY))

/**
  * @brief  Check whether the direction is full duplex transmit only.
  * @param  mode SPI data direction mode
  * @return 0: Invalid, 1: Valid
  */
#define IS_HAL_SPI_DIRECTION_2LINES_TX_ONLY(mode)                           \
        ((mode) == HAL_SPI_DIRECTION_2LINES)
/**
  * @}
  */ /* SPI_HAL_EM_Mask */

/**
  * @}
  */ /* SPI_HAL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/

/** @defgroup SPI_HAL_EM_Assert SPI HAL Assert
  * @brief    SPI HAL Assert
  * @{
  */

/**
  * @brief  The HAL_SPI_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_SPI_CHECK_PARAM
#define TAE32_USE_HAL_SPI_CHECK_PARAM                   HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_SPI_CHECK_PARAM != 1) && (TAE32_USE_HAL_SPI_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_SPI_CHECK_PARAM
#define TAE32_USE_HAL_SPI_CHECK_PARAM                   HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_SPI_CHECK_PARAM */

/**
  * @brief  The HAL_SPI_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_SPI_PARAM_CHECK(expression)                     \
        if (TAE32_USE_HAL_SPI_CHECK_PARAM) {                \
            expression;                                     \
        }
/**
  * @}
  */ /* SPI_HAL_EM_Assert */


/** @defgroup SPI_HAL_Exported_Macros SPI HAL Exported Macros
  * @brief    SPI HAL Exported Macros
  * @{
  */

/**
  * @brief  Reset SPI handle state.
  * @param  hspi Pointer to a HAL_SPI_HandleTypeDef structure
  * @return None
  * @note   Resets State and ErrorCode. Use to fully tear down a handle before re-Init.
  */
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
#define HAL_SPI_RESET_HANDLE_STATE(hspi)                                    \
        do {                                                                \
            (hspi)->State = HAL_SPI_STATE_RESET;                            \
            (hspi)->ErrorCode = HAL_SPI_ERROR_NONE;                         \
            (hspi)->MspInitCallback = NULL;                                 \
            (hspi)->MspDeInitCallback = NULL;                               \
        } while (0)
#else
#define HAL_SPI_RESET_HANDLE_STATE(hspi)                                    \
        do {                                                                \
            (hspi)->State = HAL_SPI_STATE_RESET;                            \
            (hspi)->ErrorCode = HAL_SPI_ERROR_NONE;                         \
        } while (0)
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @brief  Enable the SPI peripheral.
  * @param  hspi Pointer to a HAL_SPI_HandleTypeDef structure
  * @return None
  */
#define HAL_SPI_ENABLE(hspi)                            (LL_SPI_Enable((hspi)->Instance))

/**
  * @brief  Disable the SPI peripheral.
  * @param  hspi Pointer to a HAL_SPI_HandleTypeDef structure
  * @return None
  */
#define HAL_SPI_DISABLE(hspi)                           (LL_SPI_Disable((hspi)->Instance))

/**
  * @brief  Check whether the specified SPI flag is set or not.
  * @param  hspi Pointer to a HAL_SPI_HandleTypeDef structure
  * @param  flag Flag to check, refer to @ref HAL_SPI_EC_Flag
  * @return 0: Reset, 1: Set
  */
#define HAL_SPI_GET_FLAG(hspi, flag)                                        \
        ((LL_SPI_IsActiveFlag((hspi)->Instance, (flag)) != 0UL) ? 1UL : 0UL)

/**
  * @brief  Clear the specified SPI interrupt pending flag.
  * @param  hspi Pointer to a HAL_SPI_HandleTypeDef structure
  * @param  flag Pending flag to clear
  * @return None
  */
#define HAL_SPI_CLEAR_FLAG(hspi, flag)                  (LL_SPI_ClearFlag((hspi)->Instance, (flag)))

/**
  * @brief  Wait for a SPI flag state until timeout.
  * @param  hspi      Pointer to a HAL_SPI_HandleTypeDef structure
  * @param  flag      SPI flag to check
  * @param  status    Expected flag value (SET or RESET)
  * @param  timeout   Timeout duration in milliseconds
  * @param  tickstart Tick start value for timeout calculation
  * @return None
  * @note   Internal helper used by the blocking transfer functions.
  */
#define HAL_SPI_WAIT_ON_FLAG_UNTIL_TIMEOUT(hspi, flag, status, timeout, tickstart) \
        do {                                                                \
            (tickstart) = HAL_GetTick();                                    \
            while (((hspi)->TxXferCount > 0U) && ((status) == RESET)) {     \
                if ((timeout) != LL_MAX_DELAY) {                            \
                    if ((((HAL_GetTick() - (tickstart)) >= (timeout)) ||    \
                         ((timeout) == 0U))) {                              \
                        (hspi)->ErrorCode |= HAL_SPI_ERROR_TIMEOUT;         \
                        (hspi)->State = HAL_SPI_STATE_READY;                \
                        break;                                              \
                    }                                                       \
                }                                                           \
            }                                                               \
        } while (0)
/**
  * @}
  */ /* SPI_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup SPI_HAL_Exported_Types SPI HAL Exported Types
  * @brief    SPI HAL Exported Types
  * @{
  */

/**
  * @brief  SPI handle forward declaration
  */
struct HAL_SPI_HandleStructDef;

/**
  * @brief  SPI user callback function pointer definition
  */
typedef void (*HAL_SPI_UserCallbackTypeDef)(struct HAL_SPI_HandleStructDef *hspi);

/**
  * @brief SPI Callback ID definition
  */
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
typedef enum
{
    HAL_SPI_TX_COMPLETE_CB_ID             = 0x00UL,  /*!< SPI Tx Transfer completed callback ID     */
    HAL_SPI_RX_COMPLETE_CB_ID             = 0x01UL,  /*!< SPI Rx Transfer completed callback ID     */
    HAL_SPI_TX_RX_COMPLETE_CB_ID          = 0x02UL,  /*!< SPI TxRx Transfer completed callback ID   */
    HAL_SPI_TX_HALF_COMPLETE_CB_ID        = 0x03UL,  /*!< SPI Tx Half Transfer callback ID          */
    HAL_SPI_RX_HALF_COMPLETE_CB_ID        = 0x04UL,  /*!< SPI Rx Half Transfer callback ID          */
    HAL_SPI_TX_RX_HALF_COMPLETE_CB_ID     = 0x05UL,  /*!< SPI TxRx Half Transfer callback ID        */
    HAL_SPI_ERROR_CB_ID                   = 0x06UL,  /*!< SPI Error callback ID                     */
    HAL_SPI_ABORT_CB_ID                   = 0x07UL,  /*!< SPI Abort callback ID                     */
    HAL_SPI_MSPINIT_CB_ID                 = 0x08UL,  /*!< SPI Msp Init callback ID                  */
    HAL_SPI_MSPDEINIT_CB_ID               = 0x09UL   /*!< SPI Msp DeInit callback ID                */
} HAL_SPI_CallbackIDTypeDef;
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @brief SPI State definition
  * @note  The value is a 32-bit mask, not a compact index: Keil builds with
  *        short-enums, so the members must span past bit 23 to keep the enum
  *        4 bytes wide (see the _Static_assert below and the same scheme in
  *        HAL_CAN_StateTypeDef / HAL_ADC_StateTypeDef).
  */
#define HAL_SPI_StateMaskTypeDef                        uint32_t

#define HAL_SPI_STATE_MASK_RESET                        (0U)            /*!< SPI not yet initialized              */
#define HAL_SPI_STATE_MASK_READY                        (1U << 30U)     /*!< SPI initialized and ready for use    */
#define HAL_SPI_STATE_MASK_BUSY                         (1U << 29U)     /*!< SPI internal process is ongoing      */
#define HAL_SPI_STATE_MASK_BUSY_TX                      (1U << 29U)     /*!< SPI transmission process is ongoing  */
#define HAL_SPI_STATE_MASK_BUSY_RX                      (1U << 28U)     /*!< SPI reception process is ongoing     */
#define HAL_SPI_STATE_MASK_BUSY_TX_RX                   (1U << 27U)     /*!< SPI Tx/Rx process is ongoing         */
#define HAL_SPI_STATE_MASK_ABORT                        (1U << 26U)     /*!< SPI abort user request ongoing       */
#define HAL_SPI_STATE_MASK_TIMEOUT                      (1U << 25U)     /*!< SPI timeout state                    */
#define HAL_SPI_STATE_MASK_ERROR                        (1U << 24U)     /*!< SPI error state                      */

#ifndef TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE
typedef enum
{
    HAL_SPI_STATE_RESET             = HAL_SPI_STATE_MASK_RESET,         /*!< Peripheral is not yet initialized            */
    HAL_SPI_STATE_READY             = HAL_SPI_STATE_MASK_READY,         /*!< Peripheral initialized and ready for use     */
    HAL_SPI_STATE_BUSY              = HAL_SPI_STATE_MASK_BUSY,          /*!< An internal process is ongoing               */
    HAL_SPI_STATE_BUSY_TX           = HAL_SPI_STATE_MASK_BUSY_TX,       /*!< Data transmission process is ongoing         */
    HAL_SPI_STATE_BUSY_RX           = HAL_SPI_STATE_MASK_BUSY_RX,       /*!< Data reception process is ongoing            */
    HAL_SPI_STATE_BUSY_TX_RX        = HAL_SPI_STATE_MASK_BUSY_TX_RX,    /*!< Data transmission/reception process ongoing  */
    HAL_SPI_STATE_ABORT             = HAL_SPI_STATE_MASK_ABORT,         /*!< Abort user request ongoing                   */
    HAL_SPI_STATE_TIMEOUT           = HAL_SPI_STATE_MASK_TIMEOUT,       /*!< Timeout state                                */
    HAL_SPI_STATE_ERROR             = HAL_SPI_STATE_MASK_ERROR          /*!< Error state                                  */
} HAL_SPI_StateTypeDef;

_Static_assert(sizeof(HAL_SPI_StateTypeDef) == 4,
               "Some HAL enum must be 32-bit, please define TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE");

#else /* TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */
typedef HAL_SPI_StateMaskTypeDef                HAL_SPI_StateTypeDef;
#define HAL_SPI_STATE_RESET                     HAL_SPI_STATE_MASK_RESET
#define HAL_SPI_STATE_READY                     HAL_SPI_STATE_MASK_READY
#define HAL_SPI_STATE_BUSY                      HAL_SPI_STATE_MASK_BUSY
#define HAL_SPI_STATE_BUSY_TX                   HAL_SPI_STATE_MASK_BUSY_TX
#define HAL_SPI_STATE_BUSY_RX                   HAL_SPI_STATE_MASK_BUSY_RX
#define HAL_SPI_STATE_BUSY_TX_RX                HAL_SPI_STATE_MASK_BUSY_TX_RX
#define HAL_SPI_STATE_ABORT                     HAL_SPI_STATE_MASK_ABORT
#define HAL_SPI_STATE_TIMEOUT                   HAL_SPI_STATE_MASK_TIMEOUT
#define HAL_SPI_STATE_ERROR                     HAL_SPI_STATE_MASK_ERROR
#endif /* !TAE32_GLOBAL_HAL_U32_ENUM_REDEFINE */

/**
  * @brief SPI Function Enable/Disable definition
  */
typedef enum
{
    HAL_SPI_FUNC_DISABLE            = 0U,      /*!< SPI function disabled                        */
    HAL_SPI_FUNC_ENABLE             = 1U       /*!< SPI function enabled                         */
} HAL_SPI_EnableTypeDef;

/**
  * @brief SPI Init structure definition
  */
typedef struct
{
    HAL_SPI_ModeTypeDef                 Mode;               /*!< Specifies the SPI operating mode.
                                                                 This parameter can be a value of @ref HAL_SPI_EC_Mode. */
    HAL_SPI_DirectionTypeDef            Direction;          /*!< Specifies the SPI data direction mode.
                                                                 This parameter can be a value of @ref HAL_SPI_EC_Direction. */
    HAL_SPI_DataSizeTypeDef             DataSize;           /*!< Specifies the SPI data size (4 to 16 bits).
                                                                 This parameter can be a value of @ref HAL_SPI_EC_DataSize. */
    HAL_SPI_ClockPolarityTypeDef        CLKPolarity;        /*!< Specifies the serial clock steady state.
                                                                 This parameter can be a value of @ref HAL_SPI_EC_ClockPolarity. */
    HAL_SPI_ClockPhaseTypeDef           CLKPhase;           /*!< Specifies the clock active edge for bit capture.
                                                                 This parameter can be a value of @ref HAL_SPI_EC_ClockPhase. */
    HAL_SPI_CSTypeDef                   CS;                 /*!< Specifies whether the CS signal is managed by hardware
                                                                 or by software.
                                                                 This parameter can be a value of @ref HAL_SPI_EC_CS. */
    HAL_SPI_BaudRatePrescalerTypeDef    BaudRatePrescaler;  /*!< Specifies the baud rate prescaler value.
                                                                 This parameter can be a value of @ref HAL_SPI_EC_BaudRatePrescaler.
                                                                 @note The actual baud rate = PCLK / BaudRatePrescaler. */
    HAL_SPI_FirstBitTypeDef             FirstBit;           /*!< Specifies whether data transfers start from MSB or LSB bit.
                                                                 This parameter can be a value of @ref HAL_SPI_EC_FirstBit. */
} HAL_SPI_InitTypeDef;

/**
  * @brief SPI LL config structure definition
  */
typedef struct 
{
    uint32_t                WireMode;               /*!< Wire mode                       */
    uint32_t                CSMode;                 /*!< CS mode                         */
    uint32_t                CSPolarity;             /*!< CS polarity                     */
    uint32_t                CSInputMode;            /*!< CS input mode                   */
    uint32_t                BitOrder;               /*!< Bit order                       */

    HAL_SPI_EnableTypeDef   CSSwOut;                /*!< CS software output enable       */
    HAL_SPI_EnableTypeDef   MOSIMISOSwap;           /*!< MOSI/MISO pin swap enable       */
    uint8_t                 TxFifoEmptyThres;       /*!< TxFIFO empty threshold          */
    uint8_t                 RxFifoFullThres;        /*!< RxFIFO full threshold           */
    uint8_t                 MstRxDelay;             /*!< Master Rx delay                 */
    uint16_t                MstSSIdleness;          /*!< Master SS idleness              */
    uint16_t                MstInterDatIdleness;    /*!< Master inter-data idleness      */

    HAL_SPI_EnableTypeDef   Loopback;               /*!< Loopback enable                 */
} HAL_SPI_DefaultCfgTypeDef;

/**
  * @brief  Default SPI LL config (returned by LL_SPI_GetDefaultCfg)
  */
__STATIC_INLINE const HAL_SPI_DefaultCfgTypeDef* LL_SPI_GetDefaultCfg(void)
{
    static const HAL_SPI_DefaultCfgTypeDef def = {
        LL_SPI_WIRE_MODE_4, LL_SPI_CS_MODE_CONTINUE, LL_SPI_CS_POL_INACT_HIGH,
        LL_SPI_CS_INPUT_MODE_GPIO, LL_SPI_BIT_ORDER_MSB,
        HAL_SPI_FUNC_ENABLE, HAL_SPI_FUNC_DISABLE, 1UL, 1UL, 0UL, 1UL, 1UL, HAL_SPI_FUNC_DISABLE
    };
    return &def;
}

/**
  * @brief SPI user config structure definition
  */
typedef struct __HAL_SPI_UserCfgTypeDef
{
    uint32_t                Role;                   /*!< Role                            */
    uint32_t                SCLKPolarity;           /*!< SCLK polarity                   */
    uint32_t                SCLKPhase;              /*!< SCLK phase                      */
    uint32_t                DataWidth;              /*!< Serial data width               */
    uint32_t                Baudrate;               /*!< Baudrate                        */
    HAL_SPI_DefaultCfgTypeDef   *DefaultCfg;                  /*!< Optional LL config pointer      */
} HAL_SPI_UserCfgTypeDef;

/**
  * @brief SPI Handle Structure definition
  */
typedef struct HAL_SPI_HandleStructDef
{
    SPI_TypeDef                *Instance;           /*!< SPI registers base address                  */

    uint8_t                    *pTxBuffPtr;         /*!< Pointer to SPI Tx transfer buffer.
                                                         Used internally to track the current position
                                                         in the TX data buffer.                      */

    uint16_t                    TxXferSize;         /*!< SPI Tx transfer size, total number of
                                                         data to be transmitted.                     */

    volatile uint16_t           TxXferCount;        /*!< SPI Tx transfer counter, remaining number of
                                                         data to be transmitted.                     */

    uint8_t                    *pRxBuffPtr;         /*!< Pointer to SPI Rx transfer buffer.
                                                         Used internally to track the current position
                                                         in the RX data buffer.                      */

    uint16_t                    RxXferSize;         /*!< SPI Rx transfer size, total number of
                                                         data to be received.                        */

    volatile uint16_t           RxXferCount;        /*!< SPI Rx transfer counter, remaining number of
                                                         data to be received.                        */

    volatile HAL_SPI_StateTypeDef State;            /*!< SPI communication state,
                                                         refer to @ref HAL_SPI_StateTypeDef.
                                                         @ref HAL_SPI_GetState can be used to read it. */

    volatile uint32_t           ErrorCode;          /*!< SPI error code, a combination of
                                                         @ref HAL_SPI_EC_Error_Code.
                                                         @ref HAL_SPI_GetError can be used to read it. */

    HAL_SPI_DefaultCfgTypeDef        DefaultCfg;              /*!< SPI LL extended configuration, contains CS mode,
                                                         CS polarity, FIFO thresholds, timing parameters
                                                         and pin swap settings.                      */

    HAL_SPI_EnableTypeDef       TxDMAEnable;        /*!< SPI Tx DMA enable state,
                                                         HAL_SPI_FUNC_ENABLE when TX DMA is active.  */

    HAL_SPI_EnableTypeDef       RxDMAEnable;        /*!< SPI Rx DMA enable state,
                                                         HAL_SPI_FUNC_ENABLE when RX DMA is active.  */

    HAL_SPI_EnableTypeDef       LoopbackEnable;     /*!< SPI loopback enable state,
                                                         HAL_SPI_FUNC_ENABLE when loopback is active.*/

    HAL_SPI_EnableTypeDef       PinSwapEnable;      /*!< SPI MOSI/MISO pin swap enable state,
                                                         HAL_SPI_FUNC_ENABLE when pin swap is active.*/

    const void                 *pUserData;          /*!< Pointer to user data                       */

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
    void (* TxCpltCallback)(struct HAL_SPI_HandleStructDef *hspi);       /*!< SPI Tx completed callback        */
    void (* RxCpltCallback)(struct HAL_SPI_HandleStructDef *hspi);       /*!< SPI Rx completed callback        */
    void (* TxRxCpltCallback)(struct HAL_SPI_HandleStructDef *hspi);     /*!< SPI TxRx completed callback      */
    void (* TxHalfCpltCallback)(struct HAL_SPI_HandleStructDef *hspi);   /*!< SPI Tx half completed callback   */
    void (* RxHalfCpltCallback)(struct HAL_SPI_HandleStructDef *hspi);   /*!< SPI Rx half completed callback   */
    void (* TxRxHalfCpltCallback)(struct HAL_SPI_HandleStructDef *hspi); /*!< SPI TxRx half completed callback  */
    void (* ErrorCallback)(struct HAL_SPI_HandleStructDef *hspi);        /*!< SPI error callback               */
    void (* AbortCpltCallback)(struct HAL_SPI_HandleStructDef *hspi);    /*!< SPI abort completed callback     */
    void (* MspInitCallback)(struct HAL_SPI_HandleStructDef *hspi);      /*!< SPI Msp init callback            */
    void (* MspDeInitCallback)(struct HAL_SPI_HandleStructDef *hspi);    /*!< SPI Msp DeInit callback          */
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
} HAL_SPI_HandleTypeDef;
/**
  * @}
  */ /* SPI_HAL_Exported_Types */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup SPI_HAL_Exported_Functions SPI HAL Exported Functions
  * @brief    SPI HAL Exported Functions
  * @{
  */

/** @defgroup SPI_HAL_EF_Initialization SPI HAL Initialization Functions
  * @brief    SPI HAL Initialization Functions
  * @{
  */
HAL_StatusTypeDef HAL_SPI_Init(HAL_SPI_HandleTypeDef *hspi, SPI_TypeDef *SPIx,
                               HAL_SPI_InitTypeDef *Init);
HAL_StatusTypeDef HAL_SPI_DeInit(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_MspInit(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(HAL_SPI_HandleTypeDef *hspi);
/**
  * @}
  */ /* SPI_HAL_EF_Initialization */


/** @defgroup SPI_HAL_EF_Configuration SPI HAL Configuration Functions
  * @brief    SPI HAL Configuration Functions
  * @note     Previously named HAL_SPIEx_xxx; the "Ex" prefix was dropped so the
  *           naming matches the rest of the HAL (see HAL_CAN_ConfigXxx).
  * @{
  */
HAL_StatusTypeDef HAL_SPI_ConfigFIFOThreshold(HAL_SPI_HandleTypeDef *hspi, uint8_t TxThreshold,
                                              uint8_t RxThreshold);
HAL_StatusTypeDef HAL_SPI_ConfigLoopback(HAL_SPI_HandleTypeDef *hspi, HAL_SPI_EnableTypeDef NewState);
HAL_StatusTypeDef HAL_SPI_ConfigPinSwap(HAL_SPI_HandleTypeDef *hspi, HAL_SPI_EnableTypeDef NewState);
HAL_StatusTypeDef HAL_SPI_ConfigCSMode(HAL_SPI_HandleTypeDef *hspi, uint32_t CSMode,
                                       uint32_t CSPolarity);
HAL_StatusTypeDef HAL_SPI_ConfigTiming(HAL_SPI_HandleTypeDef *hspi, uint8_t MstRxDelay,
                                       uint16_t SSIdleness, uint16_t InterDataIdleness);
HAL_StatusTypeDef HAL_SPI_FlushTxFifo(HAL_SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_FlushRxFifo(HAL_SPI_HandleTypeDef *hspi);
uint16_t HAL_SPI_GetRxFifoLevel(HAL_SPI_HandleTypeDef *hspi);
uint16_t HAL_SPI_GetTxFifoLevel(HAL_SPI_HandleTypeDef *hspi);
/**
  * @}
  */ /* SPI_HAL_EF_Configuration */


/** @defgroup SPI_HAL_EF_Transfer SPI HAL Transfer Functions
  * @brief    SPI HAL Transfer Functions
  * @{
  */
HAL_StatusTypeDef HAL_SPI_Transmit(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size,
                                   uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Receive(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size,
                                  uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_TransmitReceive(HAL_SPI_HandleTypeDef *hspi, uint8_t *pTxData,
                                          uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Transmit_IT(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_IT(HAL_SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(HAL_SPI_HandleTypeDef *hspi, uint8_t *pTxData,
                                             uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdma,
                                       uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_DMA(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdma,
                                      uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(HAL_SPI_HandleTypeDef *hspi,
                                              HAL_DMA_HandleTypeDef *hdmatx,
                                              HAL_DMA_HandleTypeDef *hdmarx, uint8_t *pTxData,
                                              uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_DMAPause(HAL_SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAResume(HAL_SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAStop(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdmatx,
                                  HAL_DMA_HandleTypeDef *hdmarx);
HAL_StatusTypeDef HAL_SPI_Abort(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdmatx,
                                HAL_DMA_HandleTypeDef *hdmarx);
HAL_StatusTypeDef HAL_SPI_Abort_IT(HAL_SPI_HandleTypeDef *hspi, HAL_DMA_HandleTypeDef *hdmatx,
                                   HAL_DMA_HandleTypeDef *hdmarx);
/**
  * @}
  */ /* SPI_HAL_EF_Transfer */


/** @defgroup SPI_HAL_EF_Interrupt SPI HAL Interrupt Functions
  * @brief    SPI HAL Interrupt Functions
  * @{
  */
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_SPI_RegisterCallback(HAL_SPI_HandleTypeDef *hspi,
                                           HAL_SPI_CallbackIDTypeDef CallbackID,
                                           HAL_SPI_UserCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_SPI_UnRegisterCallback(HAL_SPI_HandleTypeDef *hspi,
                                             HAL_SPI_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @brief  Handle SPI interrupt request.
  * @param  hspi Pointer to a HAL_SPI_HandleTypeDef structure
  * @return None
  * @note   Handles TX empty, RX full, TX/RX complete, mode fault and operation
  *         fault interrupts. Call it from the SPI interrupt service routine.
  */
void HAL_SPI_IRQHandler(HAL_SPI_HandleTypeDef *hspi);

void HAL_SPI_TxCpltCallback(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_RxCpltCallback(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxCpltCallback(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_TxHalfCpltCallback(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_RxHalfCpltCallback(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxHalfCpltCallback(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_ErrorCallback(HAL_SPI_HandleTypeDef *hspi);
void HAL_SPI_AbortCpltCallback(HAL_SPI_HandleTypeDef *hspi);
/**
  * @}
  */ /* SPI_HAL_EF_Interrupt */


/** @defgroup SPI_HAL_EF_State SPI HAL State Functions
  * @brief    SPI HAL State Functions
  * @{
  */
HAL_SPI_StateTypeDef HAL_SPI_GetState(HAL_SPI_HandleTypeDef *hspi);
uint32_t 			 HAL_SPI_GetError(HAL_SPI_HandleTypeDef *hspi);
/**
  * @}
  */ /* SPI_HAL_EF_State */
/**
  * @}
  */ /* SPI_HAL_Exported_Functions */


/**
  * @}
  */ /* SPI_HAL */

#endif /* SPI0 || SPI1 */

/**
  * @}
  */ /* TAE32G58xx_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_HAL_SPI_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
