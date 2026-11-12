/**
  ******************************************************************************
  * @file    tae32g58xx_ll_uart.h
  * @author  Tai-Action
  * @brief   Header file of UART LL module.
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
#ifndef _TAE32G58XX_LL_UART_H_
#define _TAE32G58XX_LL_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(UART0) || defined(UART1) || defined(UART2) || defined(UART3) || defined(UART4)

/** @defgroup UART_LL UART LL
  * @brief    UART LL Module Driver
  * @{
  */

/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Constants UART LL Exported Constants
  * @brief    UART LL Exported Constants
  * @{
  */

/** @defgroup UART_LL_EC_WORDLENGTH LL UART Word Length
  * @{
  */
#define LL_UART_DATAWIDTH_5B                 (0x0UL)  /*!< 5 bits */
#define LL_UART_DATAWIDTH_6B                 (0x1UL)  /*!< 6 bits */
#define LL_UART_DATAWIDTH_7B                 (0x2UL)  /*!< 7 bits */
#define LL_UART_DATAWIDTH_8B                 (0x3UL)  /*!< 8 bits */

#define IS_LL_UART_DATAWIDTH(__VALUE__)                                      \
    (((__VALUE__) == LL_UART_DATAWIDTH_5B) || ((__VALUE__) == LL_UART_DATAWIDTH_6B) || \
     ((__VALUE__) == LL_UART_DATAWIDTH_7B) || ((__VALUE__) == LL_UART_DATAWIDTH_8B))
/**
  * @}
  */ /* UART_LL_EC_WORDLENGTH */

/** @defgroup UART_LL_EC_PARITY LL UART Parity
  * @{
  */
#define LL_UART_PARITY_NONE                (0x0UL)  /*!< No parity   */
#define LL_UART_PARITY_EVEN                (0x1UL)  /*!< Even parity */
#define LL_UART_PARITY_ODD                 (0x2UL)  /*!< Odd parity  */

#define IS_LL_UART_PARITY(__VALUE__)                                       \
    (((__VALUE__) == LL_UART_PARITY_NONE) || ((__VALUE__) == LL_UART_PARITY_EVEN) || \
     ((__VALUE__) == LL_UART_PARITY_ODD))

/**
  * @}
  */ /* UART_LL_EC_PARITY */

/** @defgroup UART_LL_EC_STOPBITS LL UART Stop Bits
  * @{
  */
#define LL_UART_STOPBITS_1                (0x0UL)  /*!< 1 stop bit   */
#define LL_UART_STOPBITS_2                (0x1UL)  /*!< 2 stop bits  */

#define IS_LL_UART_STOPBITS(__VALUE__)                                     \
    (((__VALUE__) == LL_UART_STOPBITS_1) || ((__VALUE__) == LL_UART_STOPBITS_2))
/**
  * @}
  */ /* UART_LL_EC_STOPBITS */

/** @defgroup UART_LL_EC_OVERSAMPLING LL UART Oversampling
  * @{
  */
#define LL_UART_OVERSAMPLING_16              (0x0UL)  /*!< Oversampling by 16 */
#define LL_UART_OVERSAMPLING_8               (0x1UL)  /*!< Oversampling by 8  */

#define IS_LL_UART_OVERSAMPLING(__VALUE__)                                    \
    (((__VALUE__) == LL_UART_OVERSAMPLING_16) || ((__VALUE__) == LL_UART_OVERSAMPLING_8))
/**
  * @}
  */ /* UART_LL_EC_OVERSAMPLING */

/** @defgroup UART_LL_EC_PIN_LEVEL LL UART Pin Level Inversion
  * @{
  */
#define LL_UART_TXPIN_LEVEL_STANDARD       (0x0UL)                /*!< TX pin signal works using the standard logic */
#define LL_UART_TXPIN_LEVEL_INVERTED       (UART0_CR0_TPOL_Msk)   /*!< TX pin signal values are inverted */
#define LL_UART_RXPIN_LEVEL_STANDARD       (0x0UL)                /*!< RX pin signal works using the standard logic */
#define LL_UART_RXPIN_LEVEL_INVERTED       (UART0_CR0_RPOL_Msk)   /*!< RX pin signal values are inverted */

#define IS_LL_UART_PIN_LEVEL(__VALUE__)                                    \
    (((__VALUE__) == LL_UART_TXPIN_LEVEL_STANDARD) || ((__VALUE__) == LL_UART_TXPIN_LEVEL_INVERTED) || \
     ((__VALUE__) == LL_UART_RXPIN_LEVEL_STANDARD) || ((__VALUE__) == LL_UART_RXPIN_LEVEL_INVERTED))
/**
  * @}
  */ /* UART_LL_EC_PIN_LEVEL */

/** @defgroup UART_LL_EC_TXRX_SWAP LL UART TX/RX Pin Swap
  * @{
  */
#define LL_UART_TXRX_STANDARD              (0x0UL)                /*!< TX/RX pins used as defined in standard pinout */
#define LL_UART_TXRX_SWAPPED               (UART0_CR0_SWAP_Msk)   /*!< TX and RX pins functions are swapped */

#define IS_LL_UART_TXRX_SWAP(__VALUE__)                                    \
    (((__VALUE__) == LL_UART_TXRX_STANDARD) || ((__VALUE__) == LL_UART_TXRX_SWAPPED))
/**
  * @}
  */ /* UART_LL_EC_TXRX_SWAP */


/** @defgroup UART_LL_EC_RXTO_MODE LL UART RX Timeout Mode
  * @{
  */
#define LL_UART_RXTO_MODE_FIFO             (0x0UL)  /*!< Timeout counter reset on FIFO read   */
#define LL_UART_RXTO_MODE_IDLE             (0x1UL)  /*!< Timeout counter reset on data receive */

#define IS_LL_UART_RXTO_MODE(__VALUE__)                                    \
    (((__VALUE__) == LL_UART_RXTO_MODE_FIFO) || ((__VALUE__) == LL_UART_RXTO_MODE_IDLE))
/**
  * @}
  */ /* UART_LL_EC_RXTO_MODE */

/** @defgroup UART_LL_EC_RX_FIFO_THRESHOLD LL UART RX FIFO Threshold
  * @{
  */
#define LL_UART_RX_FIFO_TH_1               (0x0UL)  /*!< RX FIFO reaches 1/  level */
#define LL_UART_RX_FIFO_TH_2               (0x1UL)  /*!< RX FIFO reaches 2  levels */
#define LL_UART_RX_FIFO_TH_4               (0x3UL)  /*!< RX FIFO reaches 4  levels */
#define LL_UART_RX_FIFO_TH_8               (0x7UL)  /*!< RX FIFO reaches 8  levels */
#define LL_UART_RX_FIFO_TH_12              (0xBUL)  /*!< RX FIFO reaches 12 levels */
#define LL_UART_RX_FIFO_TH_14              (0xDUL)  /*!< RX FIFO reaches 14 levels */


#define IS_LL_UART_RX_FIFO_THRESHOLD(__VALUE__)  ((__VALUE__) <= 0xFUL)
/**
  * @}
  */ /* UART_LL_EC_RX_FIFO_THRESHOLD */

/** @defgroup UART_LL_EC_TX_FIFO_THRESHOLD LL UART TX FIFO Threshold
  * @{
  */
#define LL_UART_TX_FIFO_TH_1               (0x0UL)  /*!< TX FIFO reaches 1  level  */
#define LL_UART_TX_FIFO_TH_2               (0x1UL)  /*!< TX FIFO reaches 2  levels */
#define LL_UART_TX_FIFO_TH_4               (0x3UL)  /*!< TX FIFO reaches 4  levels */
#define LL_UART_TX_FIFO_TH_8               (0x7UL)  /*!< TX FIFO reaches 8  levels */
#define LL_UART_TX_FIFO_TH_12              (0xBUL)  /*!< TX FIFO reaches 12 levels */
#define LL_UART_TX_FIFO_TH_14              (0xDUL)  /*!< TX FIFO reaches 14 levels */

#define IS_LL_UART_TX_FIFO_THRESHOLD(__VALUE__)  ((__VALUE__) <= 0xFUL)
/**
  * @}
  */ /* UART_LL_EC_TX_FIFO_THRESHOLD */

/** @defgroup UART_LL_EC_DE_POLARITY LL UART RS485 DE Polarity
  * @{
  */
#define LL_UART_DE_POLARITY_LOW            (0x0UL)  /*!< DE signal is active low   */
#define LL_UART_DE_POLARITY_HIGH           (0x1UL)  /*!< DE signal is active high  */


#define IS_LL_UART_DE_POLARITY(__VALUE__)                                  \
    (((__VALUE__) == LL_UART_DE_POLARITY_HIGH) || ((__VALUE__) == LL_UART_DE_POLARITY_LOW))
/**
  * @}
  */ /* UART_LL_EC_DE_POLARITY */

/** @defgroup UART_LL_EC_RE_POLARITY LL UART RE Polarity
  * @{
  */
#define LL_UART_RE_POLARITY_LOW           (0x0UL)  /*!< RE signal is active low  */
#define LL_UART_RE_POLARITY_HIGH          (0x1UL)  /*!< RE signal is active high */

#define IS_LL_UART_RE_POLARITY(__VALUE__)                                 \
    (((__VALUE__) == LL_UART_RE_POLARITY_LOW) || ((__VALUE__) == LL_UART_RE_POLARITY_HIGH))

/**
  * @}
  */ /* UART_LL_EC_RE_POLARITY */

/** @defgroup UART_LL_EC_AUTOBAUD_MODE LL UART Auto Baud Rate Mode
  * @{
  */
#define LL_UART_AUTOBAUD_MODE_1FALLING      (0x0UL) /*!< 1 falling edge measurement   */
#define LL_UART_AUTOBAUD_MODE_1RISING       (0x1UL) /*!< 1 rising edge measurement    */
#define LL_UART_AUTOBAUD_MODE_2FALLING      (0x2UL) /*!< 2 falling edges measurement  */
#define LL_UART_AUTOBAUD_MODE_2RISING       (0x3UL) /*!< 2 rising edges measurement   */
/**
  * @}
  */ /* UART_LL_EC_AUTOBAUD_MODE */

/** @defgroup UART_LL_EC_BIT_ORDER LL UART Transfer Bit Order
  * @{
  */
#define LL_UART_TRANSFER_BIT_ORDER_LSB     (0x0UL)                /*!< Data is transmitted/received with the LSB first */
#define LL_UART_TRANSFER_BIT_ORDER_MSB     (UART0_CR1_MSB_Msk)    /*!< Data is transmitted/received with the MSB first */

#define IS_LL_UART_BIT_ORDER(__VALUE__)                                    \
    (((__VALUE__) == LL_UART_TRANSFER_BIT_ORDER_LSB) || ((__VALUE__) == LL_UART_TRANSFER_BIT_ORDER_MSB))
/**
  * @}
  */ /* UART_LL_EC_BIT_ORDER */

/** @defgroup UART_LL_EC_DIRECTION LL UART Transfer Direction
  * @{
  */
#define LL_UART_DIRECTION_NONE             (0x0UL)  /*!< No transfer direction            */
#define LL_UART_DIRECTION_TX               (0x1UL)  /*!< Transmitter enabled              */
#define LL_UART_DIRECTION_RX               (0x2UL)  /*!< Receiver enabled                 */
#define LL_UART_DIRECTION_TX_RX            (LL_UART_DIRECTION_TX | LL_UART_DIRECTION_RX)  /*!< Transmitter and receiver enabled */

#define IS_LL_UART_DIRECTION(__VALUE__)                                    \
    (((__VALUE__) == LL_UART_DIRECTION_NONE) || ((__VALUE__) == LL_UART_DIRECTION_TX) || \
     ((__VALUE__) == LL_UART_DIRECTION_RX) || ((__VALUE__) == LL_UART_DIRECTION_TX_RX))
/**
  * @}
  */ /* UART_LL_EC_DIRECTION */

/** @defgroup UART_LL_EC_DMA_REG LL UART DMA Data Register
  * @{
  */
#define LL_UART_DMA_REG_DATA_TRANSMIT      (0x0UL)  /*!< Transmit data register (TDR) */
#define LL_UART_DMA_REG_DATA_RECEIVE       (0x1UL)  /*!< Receive data register (RDR)  */

#define IS_LL_UART_DMA_REG_DATA(__VALUE__)                                 \
    (((__VALUE__) == LL_UART_DMA_REG_DATA_TRANSMIT) || ((__VALUE__) == LL_UART_DMA_REG_DATA_RECEIVE))
/**
  * @}
  */ /* UART_LL_EC_DMA_REG */

/** @defgroup UART_LL_EC_IT LL UART Interrupt Enable Masks
  * @{
  */

#define LL_UART_INTEN_ITEnMskTypeDef                      uint32_t

#define LL_UART_IT_ABRE                   (UART0_INTEN_ABRE_Msk)               /*!< ABRE Mask                */
#define LL_UART_IT_AMIE                   (UART0_INTEN_AMIE_Msk)               /*!< AMIE Mask                */
#define LL_UART_IT_IDLE                   (UART0_INTEN_IDLE_Msk)               /*!< IDLE Mask                */
#define LL_UART_IT_TBIE                   (UART0_INTEN_TBIE_Msk)               /*!< TBIE Mask                */
#define LL_UART_IT_TDIE                   (UART0_INTEN_TDIE_Msk)               /*!< TDIE Mask                */
#define LL_UART_IT_RTIE                   (UART0_INTEN_RTIE_Msk)               /*!< RTIE Mask                */
#define LL_UART_IT_BKIE                   (UART0_INTEN_BKIE_Msk)               /*!< BKIE Mask                */
#define LL_UART_IT_FEIE                   (UART0_INTEN_FEIE_Msk)               /*!< FEIE Mask                */
#define LL_UART_IT_PEIE                   (UART0_INTEN_PEIE_Msk)               /*!< PEIE Mask                */
#define LL_UART_IT_NOIE                   (UART0_INTEN_NOIE_Msk)               /*!< NOIE Mask                */
#define LL_UART_IT_IDIE                   (UART0_INTEN_IDIE_Msk)               /*!< IDIE Mask                */
#define LL_UART_IT_TOIE                   (UART0_INTEN_TOIE_Msk)               /*!< TOIE Mask                */
#define LL_UART_IT_RUIE                   (UART0_INTEN_RUIE_Msk)               /*!< RUIE Mask                */
#define LL_UART_IT_ROIE                   (UART0_INTEN_ROIE_Msk)               /*!< ROIE Mask                */
#define LL_UART_IT_TEIE                   (UART0_INTEN_TEIE_Msk)               /*!< TEIE Mask                */
#define LL_UART_IT_RFIE                   (UART0_INTEN_RFIE_Msk)               /*!< RFIE Mask                */

/**
  * @}
  */ /* UART_LL_EC_IT */

/** @defgroup UART_LL_EC_FLAG LL UART Interrupt Pending Flags
  * @{
  */
#define LL_UART_INT_ITPendingMskTypeDef                   uint32_t

#define LL_UART_FLAG_ABRF                     (UART0_INT_ABRF_Msk)                 /*!< ABRF Mask                */
#define LL_UART_FLAG_AMIF                     (UART0_INT_AMIF_Msk)                 /*!< AMIF Mask                */
#define LL_UART_FLAG_IDLF                     (UART0_INT_IDLF_Msk)                 /*!< IDLF Mask                */
#define LL_UART_FLAG_TBIF                     (UART0_INT_TBIF_Msk)                 /*!< TBIF Mask                */
#define LL_UART_FLAG_TDIF                     (UART0_INT_TDIF_Msk)                 /*!< TDIF Mask                */
#define LL_UART_FLAG_RTOI                     (UART0_INT_RTOI_Msk)                 /*!< RTOI Mask                */
#define LL_UART_FLAG_BKIF                     (UART0_INT_BKIF_Msk)                 /*!< BKIF Mask                */
#define LL_UART_FLAG_FEIF                     (UART0_INT_FEIF_Msk)                 /*!< FEIF Mask                */
#define LL_UART_FLAG_PEIF                     (UART0_INT_PEIF_Msk)                 /*!< PEIF Mask                */
#define LL_UART_FLAG_NOIF                     (UART0_INT_NOIF_Msk)                 /*!< NOIF Mask                */
#define LL_UART_FLAG_IDIF                     (UART0_INT_IDIF_Msk)                 /*!< IDIF Mask                */
#define LL_UART_FLAG_TOIF                     (UART0_INT_TOIF_Msk)                 /*!< TOIF Mask                */
#define LL_UART_FLAG_RUIF                     (UART0_INT_RUIF_Msk)                 /*!< RUIF Mask                */
#define LL_UART_FLAG_ROIF                     (UART0_INT_ROIF_Msk)                 /*!< ROIF Mask                */
#define LL_UART_FLAG_TXEI                     (UART0_INT_TXEI_Msk)                 /*!< TXEI Mask                */
#define LL_UART_FLAG_RXFI                     (UART0_INT_RXFI_Msk)                 /*!< RXFI Mask                */

/**
  * @}
  */ /* UART_LL_EC_FLAG */



/**
  * @}
  */ /* UART_LL_Exported_Constants */

/* Exported Macros -----------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Functions UART LL Exported Functions
  * @brief    UART LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_UART_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_UART_ASSERT_INLINE_PARAM == 1)
extern void LL_UART_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_UART_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_UART_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_UART_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup UART_LL_EF_Configuration LL UART Configuration
  * @{
  */


/** @brief  Check whether the UART peripheral is clocked from APB1.
  * @param  UARTx Specifies UART peripheral
  * @retval 1 if the instance is on APB1, 0 otherwise (APB0).
  */
__STATIC_INLINE uint32_t LL_UART_IsOnAPB1(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

#if defined(UART3) && defined(UART4)
    if (((UARTx) == UART3) || ((UARTx) == UART4)) {
        return (uint32_t)1;
    } else if (((UARTx) == UART0) || ((UARTx) == UART1) || ((UARTx) == UART2)){
        return (uint32_t)0;
    } else {
        return (uint32_t)0;
    }
#else
    return (uint32_t)0;
#endif
}


/**
  * @brief  UART Enable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_Enable(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_UE_Msk);
}

/**
  * @brief  UART Disable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_Disable(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_UE_Msk);
}

/**
  * @brief  Check whether the UART peripheral is enabled (UE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 UART disabled, 1 UART enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabled(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_UE_Msk, UART0_CR0_UE_Pos));
}

/**
  * @brief  TX Enable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableDirectionTx(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_TE_Msk);
}

/**
  * @brief  TX Disable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableDirectionTx(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_TE_Msk);
}

/**
  * @brief  RX Enable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableDirectionRx(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_RE_Msk);
}

/**
  * @brief  RX Disable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableDirectionRx(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_RE_Msk);
}

/**
  * @brief  Check whether the transmitter is enabled (TE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 transmitter disabled, 1 transmitter enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledDirectionTx(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_TE_Msk, UART0_CR0_TE_Pos));
}

/**
  * @brief  Check whether the receiver is enabled (RE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 receiver disabled, 1 receiver enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledDirectionRx(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_RE_Msk, UART0_CR0_RE_Pos));
}

/**
  * @brief  Set the transfer direction at once (TE[2] / RE[1])
  * @param  UARTx Specifies UART peripheral
  * @param  Direction @ref LL_UART_DIRECTION_NONE / _TX / _RX / _TX_RX
  * @return None
  */
__STATIC_INLINE void LL_UART_SetTransferDirection(UART_TypeDef *UARTx, uint32_t Direction)
{
    volatile uint32_t tmp;

    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    ASSERT_INLINE_PARAM(IS_LL_UART_DIRECTION(Direction));

    tmp = ((Direction) & LL_UART_DIRECTION_TX) ? UART0_CR0_TE_Msk : 0UL;
    tmp |= ((Direction) & LL_UART_DIRECTION_RX) ? UART0_CR0_RE_Msk : 0UL;

    MODIFY_REG(UARTx->CR0, (UART0_CR0_TE_Msk | UART0_CR0_RE_Msk), tmp);
}

/**
  * @brief  Get the transfer direction
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_DIRECTION_NONE / _TX / _RX / _TX_RX
  */
__STATIC_INLINE uint32_t LL_UART_GetTransferDirection(const UART_TypeDef *UARTx)
{
    volatile uint32_t tmp;

    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    tmp = (READ_BIT(UARTx->CR0, UART0_CR0_TE_Msk) != 0UL) ? LL_UART_DIRECTION_TX : 0UL;
    tmp |= (READ_BIT(UARTx->CR0, UART0_CR0_RE_Msk) != 0UL) ? LL_UART_DIRECTION_RX : 0UL;

    return tmp;
}

/**
  * @brief  TX FIFO Reset
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_ResetTxFIFO(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_TFR_Msk);
}

/**
  * @brief  RX FIFO Reset
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_ResetRxFIFO(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_RFR_Msk);
}

/**
  * @brief  Enable DMA mode for reception
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableDMAReq_RX(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_DRE_Msk);
}

/**
  * @brief  Disable DMA mode for reception
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableDMAReq_RX(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_DRE_Msk);
}

/**
  * @brief  Enable DMA mode for transmission
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableDMAReq_TX(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_DTE_Msk);
}

/**
  * @brief  Disable DMA mode for transmission
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableDMAReq_TX(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_DTE_Msk);
}

/**
  * @brief  Check whether the DMA transmit request is enabled (DTE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledDMAReq_TX(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_DTE_Msk, UART0_CR0_DTE_Pos));
}

/**
  * @brief  Check whether the DMA receive request is enabled (DRE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledDMAReq_RX(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_DRE_Msk, UART0_CR0_DRE_Pos));
}

/**
  * @brief  Return the UART data register address, used for DMA programming
  * @param  UARTx Specifies UART peripheral
  * @param  Direction @ref LL_UART_DMA_REG_DATA_TRANSMIT or @ref LL_UART_DMA_REG_DATA_RECEIVE
  * @return The data register address (TDR or RDR)
  */
__STATIC_INLINE uint32_t LL_UART_DMA_GetRegAddr(const UART_TypeDef *UARTx, uint32_t Direction)
{
    uint32_t addr;

    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_DMA_REG_DATA(Direction));

    if ((Direction) == LL_UART_DMA_REG_DATA_TRANSMIT) {
        addr = (uint32_t)(uintptr_t)(&UARTx->TDR);
    } else {
        addr = (uint32_t)(uintptr_t)(&UARTx->RDR);
    }

    return addr;
}

/**
  * @brief  Enable single wire half-duplex mode
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableOneWire(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_OWE_Msk);
}

/**
  * @brief  Disable single wire half-duplex mode
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableOneWire(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_OWE_Msk);
}

/**
  * @brief  Check whether the single wire half-duplex mode is enabled (OWE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledOneWire(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_OWE_Msk, UART0_CR0_OWE_Pos));
}

/**
  * @brief  Oversample mode Set
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @param  Mode Oversample mode @ref LL_UART_OVERSAMPLING_16 or @ref LL_UART_OVERSAMPLING_8
  * @return None
  */
__STATIC_INLINE void LL_UART_SetOverSampling(UART_TypeDef *UARTx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    ASSERT_INLINE_PARAM(IS_LL_UART_OVERSAMPLING(Mode));

    MODIFY_REG(UARTx->CR0, UART0_CR0_OVER8_Msk, (((Mode) & UART0_CR0_OVER8_Val) << UART0_CR0_OVER8_Pos));
}

/**
  * @brief  Get the oversample mode
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_OVERSAMPLING_16 or @ref LL_UART_OVERSAMPLING_8
  */
__STATIC_INLINE uint32_t LL_UART_GetOverSampling(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_OVER8_Msk, UART0_CR0_OVER8_Pos));
}

/**
  * @brief  Enable the receiver timeout feature (RXNE behaviour)
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableRxTimeout(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_RTOE_Msk);
}

/**
  * @brief  Disable the receiver timeout feature
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableRxTimeout(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_RTOE_Msk);
}

/**
  * @brief  Check whether the receiver timeout feature is enabled (RTOE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledRxTimeout(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_RTOE_Msk, UART0_CR0_RTOE_Pos));
}

/**
  * @brief  Enable loopback mode
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableLoopback(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    /* CR0.LOOP is write-only while UE==0; toggle UE around the write. */
    const uint32_t ue = READ_REG(UARTx->CR0) & UART0_CR0_UE_Msk;

    CLEAR_BIT(UARTx->CR0, UART0_CR0_UE_Msk);///TODO
    SET_BIT(UARTx->CR0, UART0_CR0_LOOP_Msk);

    if (ue) {
        SET_BIT(UARTx->CR0, UART0_CR0_UE_Msk);
    }
}

/**
  * @brief  Disable loopback mode
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableLoopback(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    /* Same UE-toggle trick as EnableLoopback (CR0.LOOP write-only at UE==0). */
    const uint32_t ue = READ_REG(UARTx->CR0) & UART0_CR0_UE_Msk;

    CLEAR_BIT(UARTx->CR0, UART0_CR0_UE_Msk);///TODO
    CLEAR_BIT(UARTx->CR0, UART0_CR0_LOOP_Msk);

    if (ue) {
        SET_BIT(UARTx->CR0, UART0_CR0_UE_Msk);
    }
}

/**
  * @brief  Check whether the loopback mode is enabled (LOOP)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledLoopback(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_LOOP_Msk, UART0_CR0_LOOP_Pos));
}

/**
  * @brief  Set the TX/RX pin swap configuration (CR0.SWAP)
  * @param  UARTx Specifies UART peripheral
  * @param  SwapConfig @ref LL_UART_TXRX_STANDARD or @ref LL_UART_TXRX_SWAPPED
  * @return None
  */
__STATIC_INLINE void LL_UART_SetTXRXSwap(UART_TypeDef *UARTx, uint32_t SwapConfig)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->CR0, UART0_CR0_SWAP_Msk, (SwapConfig) & UART0_CR0_SWAP_Msk);
}

/**
  * @brief  Return the TX/RX pin swap configuration (CR0.SWAP)
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_TXRX_STANDARD or @ref LL_UART_TXRX_SWAPPED
  */
__STATIC_INLINE uint32_t LL_UART_GetTXRXSwap(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT(UARTx->CR0, UART0_CR0_SWAP_Msk));
}

/**
  * @brief  Set the TX pin level inversion method (CR0.TPOL)
  * @param  UARTx Specifies UART peripheral
  * @param  PinInvMethod @ref LL_UART_TXPIN_LEVEL_STANDARD or @ref LL_UART_TXPIN_LEVEL_INVERTED
  * @return None
  */
__STATIC_INLINE void LL_UART_SetTXPinLevel(UART_TypeDef *UARTx, uint32_t PinInvMethod)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->CR0, UART0_CR0_TPOL_Msk, (PinInvMethod) & UART0_CR0_TPOL_Msk);
}

/**
  * @brief  Return the TX pin level inversion method (CR0.TPOL)
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_TXPIN_LEVEL_STANDARD or @ref LL_UART_TXPIN_LEVEL_INVERTED
  */
__STATIC_INLINE uint32_t LL_UART_GetTXPinLevel(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT(UARTx->CR0, UART0_CR0_TPOL_Msk));
}

/**
  * @brief  Set the RX pin level inversion method (CR0.RPOL)
  * @param  UARTx Specifies UART peripheral
  * @param  PinInvMethod @ref LL_UART_RXPIN_LEVEL_STANDARD or @ref LL_UART_RXPIN_LEVEL_INVERTED
  * @return None
  */
__STATIC_INLINE void LL_UART_SetRXPinLevel(UART_TypeDef *UARTx, uint32_t PinInvMethod)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->CR0, UART0_CR0_RPOL_Msk, (PinInvMethod) & UART0_CR0_RPOL_Msk);
}

/**
  * @brief  Return the RX pin level inversion method (CR0.RPOL)
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_RXPIN_LEVEL_STANDARD or @ref LL_UART_RXPIN_LEVEL_INVERTED
  */
__STATIC_INLINE uint32_t LL_UART_GetRXPinLevel(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT(UARTx->CR0, UART0_CR0_RPOL_Msk));
}

/**
  * @brief  Enable one-bit sampling method
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableOneBitSamp(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_ONEBIT_Msk);
}

/**
  * @brief  Disable one-bit sampling method
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableOneBitSamp(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_ONEBIT_Msk);
}

/**
  * @brief  Check whether the one-bit sampling method is enabled (ONEBIT)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledOneBitSamp(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_ONEBIT_Msk, UART0_CR0_ONEBIT_Pos));
}

/**
  * @brief  Set receive timeout detection mode
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @param  Mode Timeout mode selection
  *         @arg @ref LL_UART_RXTO_MODE_FIFO: Timeout counts from last FIFO read
  *         @arg @ref LL_UART_RXTO_MODE_IDLE: Timeout counts from last data received
  * @return None
  */
__STATIC_INLINE void LL_UART_SetRxTimeoutMode(UART_TypeDef *UARTx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_RXTO_MODE(Mode));

    MODIFY_REG(UARTx->CR0, UART0_CR0_RTOM_Msk, (((Mode) & UART0_CR0_RTOM_Val) << UART0_CR0_RTOM_Pos));
}

/**
  * @brief  Get the receive timeout detection mode
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_RXTO_MODE_FIFO or @ref LL_UART_RXTO_MODE_IDLE
  */
__STATIC_INLINE uint32_t LL_UART_GetRxTimeoutMode(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_RTOM_Msk, UART0_CR0_RTOM_Pos));
}

/**
  * @brief  Set TX FIFO threshold
  * @param  UARTx Specifies UART peripheral
  * @param  Thr Threshold value @ref IS_LL_UART_TX_FIFO_THRESHOLD (0..15)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetTXFIFOThreshold(UART_TypeDef *UARTx, uint32_t Thr)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_TX_FIFO_THRESHOLD(Thr));

    MODIFY_REG(UARTx->FIFOCTRL, UART0_FIFOCTRL_TXFT_Msk, (((Thr) & 0xFUL) << UART0_FIFOCTRL_TXFT_Pos));
}

/**
  * @brief  Set RX FIFO threshold
  * @param  UARTx Specifies UART peripheral
  * @param  Thr Threshold value @ref IS_LL_UART_RX_FIFO_THRESHOLD (0..15)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetRXFIFOThreshold(UART_TypeDef *UARTx, uint32_t Thr)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_RX_FIFO_THRESHOLD(Thr));

    MODIFY_REG(UARTx->FIFOCTRL, UART0_FIFOCTRL_RXFT_Msk, (((Thr) & 0xFUL) << UART0_FIFOCTRL_RXFT_Pos));
}

/**
  * @brief  Get TX FIFO threshold
  * @param  UARTx Specifies UART peripheral
  * @return TX FIFO threshold (0..15)
  */
__STATIC_INLINE uint32_t LL_UART_GetTXFIFOThreshold(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->FIFOCTRL, UART0_FIFOCTRL_TXFT_Msk, UART0_FIFOCTRL_TXFT_Pos));
}

/**
  * @brief  Get RX FIFO threshold
  * @param  UARTx Specifies UART peripheral
  * @return RX FIFO threshold (0..15)
  */
__STATIC_INLINE uint32_t LL_UART_GetRXFIFOThreshold(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->FIFOCTRL, UART0_FIFOCTRL_RXFT_Msk, UART0_FIFOCTRL_RXFT_Pos));
}

/**
  * @brief  Set TX and RX FIFO thresholds at once
  * @param  UARTx Specifies UART peripheral
  * @param  TxThr TX FIFO threshold (0..15)
  * @param  RxThr RX FIFO threshold (0..15)
  * @return None
  */
__STATIC_INLINE void LL_UART_ConfigFIFOsThreshold(UART_TypeDef *UARTx, uint32_t TxThr, uint32_t RxThr)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_TX_FIFO_THRESHOLD(TxThr));
    ASSERT_INLINE_PARAM(IS_LL_UART_RX_FIFO_THRESHOLD(RxThr));

    MODIFY_REG(UARTx->FIFOCTRL, (UART0_FIFOCTRL_TXFT_Msk | UART0_FIFOCTRL_RXFT_Msk),
               (((TxThr) & 0xFUL) << UART0_FIFOCTRL_TXFT_Pos) | (((RxThr) & 0xFUL) << UART0_FIFOCTRL_RXFT_Pos));
}

/**
  * @brief  Enable the FIFO mode (clear the non-FIFO mode bit CR0.NFE)
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableFIFO(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_NFE_Msk);
}

/**
  * @brief  Disable the FIFO mode (set the non-FIFO mode bit CR0.NFE)
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableFIFO(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_NFE_Msk);
}

/**
  * @brief  Check whether the FIFO mode is enabled
  * @param  UARTx Specifies UART peripheral
  * @return 0 FIFO mode disabled (non-FIFO), 1 FIFO mode enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledFIFO(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_NFE_Msk, UART0_CR0_NFE_Pos) ^ 0x1UL);
}

/**
  * @brief  Extend-Bit Enable (9-bit / multiprocessor)
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableExtBit(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_EBE_Msk);
}

/**
  * @brief  Extend-Bit Disable
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableExtBit(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR1, UART0_CR1_EBE_Msk);
}

/**
  * @brief  Check whether the extend-bit (9-bit) mode is enabled (EBE)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledExtBit(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_EBE_Msk, UART0_CR1_EBE_Pos));
}

/**
  * @brief  Enable the RX extend mode (CR1.REM: 9th bit used as address/data flag)
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableRxExtendMode(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_REM_Msk);
}

/**
  * @brief  Disable the RX extend mode (CR1.REM)
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableRxExtendMode(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR1, UART0_CR1_REM_Msk);
}

/**
  * @brief  Check whether the RX extend mode is enabled (CR1.REM)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledRxExtendMode(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_REM_Msk, UART0_CR1_REM_Pos));
}

/**
  * @brief  Enable the TX extend mode (CR1.TEM: 9th bit used as address/tag flag)
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableTxExtendMode(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_TEM_Msk);
}

/**
  * @brief  Disable the TX extend mode (CR1.TEM)
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableTxExtendMode(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR1, UART0_CR1_TEM_Msk);
}

/**
  * @brief  Check whether the TX extend mode is enabled (CR1.TEM)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledTxExtendMode(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_TEM_Msk, UART0_CR1_TEM_Pos));
}

/**
  * @brief  Set the parity control (CR1.PEN / CR1.PSEL) in one call
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @param  Parity @ref LL_UART_PARITY_NONE / @ref LL_UART_PARITY_EVEN / @ref LL_UART_PARITY_ODD
  * @return None
  */
__STATIC_INLINE void LL_UART_SetParity(UART_TypeDef *UARTx, uint32_t Parity)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_PARITY(Parity));

    if ((Parity) == LL_UART_PARITY_NONE) {
        CLEAR_BIT(UARTx->CR1, UART0_CR1_PEN_Msk);
    } else {
        /* PSEL is a single bit: 0 = Even parity, 1 = Odd parity */
        MODIFY_REG(UARTx->CR1, (UART0_CR1_PEN_Msk | UART0_CR1_PSEL_Msk),
                   UART0_CR1_PEN_Msk |
                   (((Parity) == LL_UART_PARITY_ODD) ? (1UL << UART0_CR1_PSEL_Pos) : 0UL));
    }
}

/**
  * @brief  Get the parity configuration (PEN / PSEL)
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_PARITY_NONE / EVEN / ODD
  */
__STATIC_INLINE uint32_t LL_UART_GetParity(const UART_TypeDef *UARTx)
{
    uint32_t tmp;

    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    if (READ_BIT(UARTx->CR1, UART0_CR1_PEN_Msk) == 0UL) {
        tmp = LL_UART_PARITY_NONE;
    } else {
        tmp = (READ_BIT(UARTx->CR1, UART0_CR1_PSEL_Msk) != 0UL) ? LL_UART_PARITY_ODD : LL_UART_PARITY_EVEN;
    }

    return tmp;
}

/**
  * @brief  Enable the stick parity (CR1.SPE)
  * @note   Force the parity bit to a fixed value while parity is enabled
  *         (PSEL = 1: force logic 1, PSEL = 0: force logic 0)
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableStickParity(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_SPE_Msk);
}

/**
  * @brief  Disable the stick parity (CR1.SPE)
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableStickParity(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR1, UART0_CR1_SPE_Msk);
}

/**
  * @brief  Judge is Stick Parity enabled or not (CR1.SPE)
  * @param  UARTx Specifies UART peripheral
  * @retval 0 Stick Parity isn't Enable
  * @retval 1 Stick Parity is Enable
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledStickParity(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_SPE_Msk, UART0_CR1_SPE_Pos));
}

/**
  * @brief  Stop Length Set
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @param  Len Stop Length @ref LL_UART_STOPBITS_1 or @ref LL_UART_STOPBITS_2
  * @return None
  */
__STATIC_INLINE void LL_UART_SetStopBitsLength(UART_TypeDef *UARTx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->CR1, UART0_CR1_STP_Msk, (((Len) & UART0_CR1_STP_Val) << UART0_CR1_STP_Pos));
}

/**
  * @brief  Stop Length Get
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_STOPBITS_1 or @ref LL_UART_STOPBITS_2
  */
__STATIC_INLINE uint32_t LL_UART_GetStopBitsLength(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_STP_Msk, UART0_CR1_STP_Pos));
}

/**
  * @brief  Data length Set
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @param  Len Data length @ref LL_UART_DATAWIDTH_5B .. @ref LL_UART_DATAWIDTH_8B
  * @return None
  */
__STATIC_INLINE void LL_UART_SetDataWidth(UART_TypeDef *UARTx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->CR1, UART0_CR1_LEN_Msk, (((Len) & UART0_CR1_LEN_Val) << UART0_CR1_LEN_Pos));
}

/**
  * @brief  Data length Get
  * @param  UARTx Specifies UART peripheral
  * @retval 0 Data length is 5bits
  * @retval 1 Data length is 6bits
  * @retval 2 Data length is 7bits
  * @retval 3 Data length is 8bits
  */
__STATIC_INLINE uint32_t LL_UART_GetDataWidth(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_LEN_Msk, UART0_CR1_LEN_Pos));
}

/**
  * @brief  Set the transfer bit order (CR1.MSB)
  * @param  UARTx Specifies UART peripheral
  * @param  BitOrder @ref LL_UART_TRANSFER_BIT_ORDER_LSB or @ref LL_UART_TRANSFER_BIT_ORDER_MSB
  * @return None
  */
__STATIC_INLINE void LL_UART_SetTransferBitOrder(UART_TypeDef *UARTx, uint32_t BitOrder)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_BIT_ORDER(BitOrder));

    MODIFY_REG(UARTx->CR1, UART0_CR1_MSB_Msk, (BitOrder) & UART0_CR1_MSB_Msk);
}

/**
  * @brief  Return the transfer bit order (CR1.MSB)
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_TRANSFER_BIT_ORDER_LSB or @ref LL_UART_TRANSFER_BIT_ORDER_MSB
  */
__STATIC_INLINE uint32_t LL_UART_GetTransferBitOrder(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT(UARTx->CR1, UART0_CR1_MSB_Msk));
}

/**
  * @brief  RS485 mode enable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableRS485(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_RS485E_Msk);
}

/**
  * @brief  RS485 mode disable
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableRS485(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR1, UART0_CR1_RS485E_Msk);
}

/**
  * @brief  Check whether the RS485 mode is enabled (RS485E)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledRS485(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_RS485E_Msk, UART0_CR1_RS485E_Pos));
}

/**
  * @brief  Set RS485 Driver Enable polarity
  * @param  UARTx Specifies UART peripheral
  * @param  Polarity @ref LL_UART_DE_POLARITY_HIGH or @ref LL_UART_DE_POLARITY_LOW
  * @return None
  */
__STATIC_INLINE void LL_UART_SetDESignalPolarity(UART_TypeDef *UARTx, uint32_t Polarity)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_DE_POLARITY(Polarity));

    MODIFY_REG(UARTx->CR1, UART0_CR1_DEP_Msk, (((Polarity) & UART0_CR1_DEP_Val) << UART0_CR1_DEP_Pos));
}

/**
  * @brief  Get the RS485 Driver Enable polarity
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_DE_POLARITY_HIGH or @ref LL_UART_DE_POLARITY_LOW
  */
__STATIC_INLINE uint32_t LL_UART_GetDESignalPolarity(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_DEP_Msk, UART0_CR1_DEP_Pos));
}

/**
  * @brief  Set the RE signal polarity (CR1.REP)
  * @param  UARTx Specifies UART peripheral
  * @param  Polarity @ref LL_UART_RE_POLARITY_LOW or @ref LL_UART_RE_POLARITY_HIGH
  * @return None
  */
__STATIC_INLINE void LL_UART_SetREPolarity(UART_TypeDef *UARTx, uint32_t Polarity)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_RE_POLARITY(Polarity));

    MODIFY_REG(UARTx->CR1, UART0_CR1_REP_Msk, (((Polarity) & UART0_CR1_REP_Val) << UART0_CR1_REP_Pos));
}

/**
  * @brief  Get the RE signal polarity (CR1.REP)
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_RE_POLARITY_LOW or @ref LL_UART_RE_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_UART_GetREPolarity(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_REP_Msk, UART0_CR1_REP_Pos));
}

/**
  * @brief  Set the RS485 driver enable assertion time (DEAT)
  * @param  UARTx Specifies UART peripheral
  * @param  Time Assertion time value (0..0xFFFF)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetDEAssertionTime(UART_TypeDef *UARTx, uint32_t Time)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->TIMING0, UART0_TIMING0_DEAT_Msk, (((Time) & 0xFFFFUL) << UART0_TIMING0_DEAT_Pos));
}

/**
  * @brief  Set the RS485 driver enable de-assertion time (DEDT)
  * @param  UARTx Specifies UART peripheral
  * @param  Time De-assertion time value (0..0xFFFF)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetDEDeassertionTime(UART_TypeDef *UARTx, uint32_t Time)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->TIMING0, UART0_TIMING0_DEDT_Msk, (((Time) & 0xFFFFUL) << UART0_TIMING0_DEDT_Pos));
}

/**
  * @brief  Get the RS485 driver enable assertion time (DEAT)
  * @param  UARTx Specifies UART peripheral
  * @return Assertion time value (0..0xFFFF)
  */
__STATIC_INLINE uint32_t LL_UART_GetDEAssertionTime(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->TIMING0, UART0_TIMING0_DEAT_Msk, UART0_TIMING0_DEAT_Pos));
}

/**
  * @brief  Get the RS485 driver enable de-assertion time (DEDT)
  * @param  UARTx Specifies UART peripheral
  * @return De-assertion time value (0..0xFFFF)
  */
__STATIC_INLINE uint32_t LL_UART_GetDEDeassertionTime(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->TIMING0, UART0_TIMING0_DEDT_Msk, UART0_TIMING0_DEDT_Pos));
}

/**
  * @brief  Set the RE to DE turn-around time (TIMING1.RDET)
  * @note   Time between the RE signal de-assertion and the DE signal assertion
  * @param  UARTx Specifies UART peripheral
  * @param  Time Turn-around time value (0..0xFFFF, PCLK cycles)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetRDETime(UART_TypeDef *UARTx, uint32_t Time)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->TIMING1, UART0_TIMING1_RDET_Msk, (((Time) & 0xFFFFUL) << UART0_TIMING1_RDET_Pos));
}

/**
  * @brief  Set the DE to RE turn-around time (TIMING1.DRET)
  * @note   Time between the DE signal de-assertion and the RE signal assertion
  * @param  UARTx Specifies UART peripheral
  * @param  Time Turn-around time value (0..0xFFFF, PCLK cycles)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetDRETime(UART_TypeDef *UARTx, uint32_t Time)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->TIMING1, UART0_TIMING1_DRET_Msk, (((Time) & 0xFFFFUL) << UART0_TIMING1_DRET_Pos));
}

/**
  * @brief  Get the RE to DE turn-around time (TIMING1.RDET)
  * @param  UARTx Specifies UART peripheral
  * @return Turn-around time value (0..0xFFFF, PCLK cycles)
  */
__STATIC_INLINE uint32_t LL_UART_GetRDETime(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->TIMING1, UART0_TIMING1_RDET_Msk, UART0_TIMING1_RDET_Pos));
}

/**
  * @brief  Get the DE to RE turn-around time (TIMING1.DRET)
  * @param  UARTx Specifies UART peripheral
  * @return Turn-around time value (0..0xFFFF, PCLK cycles)
  */
__STATIC_INLINE uint32_t LL_UART_GetDRETime(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->TIMING1, UART0_TIMING1_DRET_Msk, UART0_TIMING1_DRET_Pos));
}

/**
  * @brief  Enable auto baud rate detection
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableAutoBaudRate(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_ABR_Msk);
}

/**
  * @brief  Disable auto baud rate detection
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableAutoBaudRate(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR1, UART0_CR1_ABR_Msk);
}

/**
  * @brief  Check whether the auto baud rate detection is enabled (ABR)
  * @param  UARTx Specifies UART peripheral
  * @return 0 disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledAutoBaud(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_ABR_Msk, UART0_CR1_ABR_Pos));
}

/**
  * @brief  Set auto baud rate mode
  * @param  UARTx Specifies UART peripheral
  * @param  Mode @ref LL_UART_AUTOBAUD_MODE_1FALLING ..
  * @return None
  */
__STATIC_INLINE void LL_UART_SetAutoBaudRateMode(UART_TypeDef *UARTx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->CR0, UART0_CR0_ABRM_Msk, (((Mode) & UART0_CR0_ABRM_Val) << UART0_CR0_ABRM_Pos));
}

/**
  * @brief  Get the auto baud rate detection mode
  * @param  UARTx Specifies UART peripheral
  * @return @ref LL_UART_AUTOBAUD_MODE_1FALLING .. @ref LL_UART_AUTOBAUD_MODE_2RISING
  */
__STATIC_INLINE uint32_t LL_UART_GetAutoBaudRateMode(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_ABRM_Msk, UART0_CR0_ABRM_Pos));
}

/**
  * @brief  Configure the UART in asynchronous mode (8 data bits, no parity, 1 stop bit, LSB first)
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_ConfigAsyncMode(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    LL_UART_SetDataWidth(UARTx, LL_UART_DATAWIDTH_8B);
    LL_UART_SetParity(UARTx, LL_UART_PARITY_NONE);
    LL_UART_SetStopBitsLength(UARTx, LL_UART_STOPBITS_1);
    LL_UART_SetTransferBitOrder(UARTx, LL_UART_TRANSFER_BIT_ORDER_LSB);
}

/**
  * @brief  Request a break character transmission
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_RequestBreakSending(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_BKR_Msk);
}

/**
  * @brief  Stop break character transmission
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_StopBreakSending(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR1, UART0_CR1_BKR_Msk);
}

/**
  * @brief  Request an IDLE frame (CR1.IDR)
  * @note   Write '1' to this bit to request the IDLE frame (and reset the IDLE
  *         detection state machine)
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_RequestIdleSending(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR1, UART0_CR1_IDR_Msk);
}

/**
  * @brief  Judge is the IDLE frame request still pending or not (CR1.IDR)
  * @note   Set by LL_UART_RequestIdleSending(), cleared by hardware when the IDLE frame
  *         has been sent
  * @param  UARTx Specifies UART peripheral
  * @retval 0 IDLE frame request is done (IDR cleared)
  * @retval 1 IDLE frame request is still pending (IDR set)
  */
__STATIC_INLINE uint32_t LL_UART_IsIdleRequest(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_IDR_Msk, UART0_CR1_IDR_Pos));
}

/**
  * @brief  Judge is the Break frame request still pending or not (CR1.BKR)
  * @note   Set by LL_UART_RequestBreakSending(), cleared by hardware when the Break frame
  *         has been sent
  * @param  UARTx Specifies UART peripheral
  * @retval 0 Break frame request is done (BKR cleared)
  * @retval 1 Break frame request is still pending (BKR set)
  */
__STATIC_INLINE uint32_t LL_UART_IsBreakRequest(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR1, UART0_CR1_BKR_Msk, UART0_CR1_BKR_Pos));
}

/**
  * @brief  Baudrate Value Set
  * @note   Can only be config in UART Disable state
  * @param  UARTx Specifies UART peripheral
  * @param  Val Baudrate divider Value
  * @return None
  */
__STATIC_INLINE void LL_UART_SetBaudRate(UART_TypeDef *UARTx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->BAUD, UART0_BAUD_BAUD_Msk, (((Val) & UART0_BAUD_BAUD_Val) << UART0_BAUD_BAUD_Pos));
}

/**
  * @brief  Baudrate Value Read
  * @param  UARTx Specifies UART peripheral
  * @return Baudrate divider Value
  */
__STATIC_INLINE uint32_t LL_UART_GetBaudRate(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->BAUD, UART0_BAUD_BAUD_Msk, UART0_BAUD_BAUD_Pos));
}

/**
  * @brief  Get the actual baud rate in bps (e.g. 115200)
  * @note   Inverse of the divider programmed by LL_UART_SetBaudRate(): BAUD = PCLK / baud rate,
  *         the result is rounded to the nearest integer
  * @note   The UART clock is PCLK0 for UART0..UART2 and PCLK1 for UART3/UART4
  *         (see LL_UART_IsOnAPB1()), so the caller passes it in, e.g. with
  *         HAL_RCU_GetPCLK0Freq() / HAL_RCU_GetPCLK1Freq()
  * @param  UARTx Specifies UART peripheral
  * @param  PclkHz UART peripheral clock in Hz
  * @return Actual baud rate in bps (0 if the divider is not programmed yet)
  */
__STATIC_INLINE uint32_t LL_UART_GetBaudRateHz(const UART_TypeDef *UARTx, uint32_t PclkHz)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    uint32_t reg = (uint32_t)(READ_BIT_SHIFT(UARTx->BAUD, UART0_BAUD_BAUD_Msk, UART0_BAUD_BAUD_Pos));

    return ((reg != 0UL) ? ((PclkHz + (reg / 2UL)) / reg) : 0UL);
}

/**
  * @brief  Set the baud rate in bps (e.g. 115200)
  * @note   Programs the divider as BAUD = PCLK / baud rate, rounded to the nearest integer
  * @note   The UART clock is PCLK0 for UART0..UART2 and PCLK1 for UART3/UART4
  *         (see LL_UART_IsOnAPB1()), so the caller passes it in, e.g. with
  *         HAL_RCU_GetPCLK0Freq() / HAL_RCU_GetPCLK1Freq()
  * @param  UARTx Specifies UART peripheral
  * @param  PclkHz UART peripheral clock in Hz
  * @param  BaudRate Expected baud rate in bps (must not be 0)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetBaudRateHz(UART_TypeDef *UARTx, uint32_t PclkHz, uint32_t BaudRate)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    uint32_t div;

    if (BaudRate != 0UL) {
        div = (PclkHz + (BaudRate / 2UL)) / BaudRate;
        MODIFY_REG(UARTx->BAUD, UART0_BAUD_BAUD_Msk, ((div) & UART0_BAUD_BAUD_Val) << UART0_BAUD_BAUD_Pos);
    }
}

/**
 * @brief  Set the receive timeout value (RTO)
  * @param  UARTx Specifies UART peripheral
  * @param  Val Receive timeout value (0..0xFFFF)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetRxTimeout(UART_TypeDef *UARTx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->RTO, UART0_RTO_RTO_Msk, ((Val) & 0xFFFFUL));
}

/**
  * @brief  Get the receive timeout value
  * @param  UARTx Specifies UART peripheral
  * @return Receive timeout value (0..0xFFFF)
  */
__STATIC_INLINE uint32_t LL_UART_GetRxTimeout(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->RTO, UART0_RTO_RTO_Msk, UART0_RTO_RTO_Pos));
}

/**
  * @brief  Set TX address (9-bit / multiprocessor)
  * @param  UARTx Specifies UART peripheral
  * @param  Addr TX address (0..0xFF)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetTxAddress(UART_TypeDef *UARTx, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->TAR, UART0_TAR_TAR_Msk, ((Addr) & 0xFFUL));
}

/**
  * @brief  Get TX address (9-bit / multiprocessor)
  * @param  UARTx Specifies UART peripheral
  * @return TX address (0..0xFF)
  */
__STATIC_INLINE uint32_t LL_UART_GetTxAddress(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->TAR, UART0_TAR_TAR_Msk, UART0_TAR_TAR_Pos));
}

/**
  * @brief  Set RX address (9-bit / multiprocessor)
  * @param  UARTx Specifies UART peripheral
  * @param  Addr RX address (0..0xFF)
  * @return None
  */
__STATIC_INLINE void LL_UART_SetRxAddress(UART_TypeDef *UARTx, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    MODIFY_REG(UARTx->RAR, UART0_RAR_RAR_Msk, ((Addr) & 0xFFUL));
}

/**
  * @brief  Get RX address (9-bit / multiprocessor)
  * @param  UARTx Specifies UART peripheral
  * @return RX address (0..0xFF)
  */
__STATIC_INLINE uint32_t LL_UART_GetRxAddress(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->RAR, UART0_RAR_RAR_Msk, UART0_RAR_RAR_Pos));
}

/**
  * @brief  Enable the overrun detection (clear the overrun disable bit CR0.OVDIS)
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableOverrunDetect(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->CR0, UART0_CR0_OVDIS_Msk);
}

/**
  * @brief  Disable the overrun detection (set the overrun disable bit CR0.OVDIS)
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableOverrunDetect(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->CR0, UART0_CR0_OVDIS_Msk);
}

/**
  * @brief  Check whether the overrun detection is enabled
  * @param  UARTx Specifies UART peripheral
  * @return 0 overrun detection disabled, 1 overrun detection enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledOverrunDetect(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->CR0, UART0_CR0_OVDIS_Msk, UART0_CR0_OVDIS_Pos) ^ 0x1UL);
}

/**
  * @brief  Configure the UART in multi-processor mode (extend bit + node address)
  * @param  UARTx Specifies UART peripheral
  * @param  NodeAddress Node address to be matched (0..0xFF)
  * @return None
  */
__STATIC_INLINE void LL_UART_ConfigMultiProcessMode(UART_TypeDef *UARTx, uint32_t NodeAddress)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    LL_UART_EnableExtBit(UARTx);
    LL_UART_SetRxAddress(UARTx, NodeAddress);
    LL_UART_EnableRxExtendMode(UARTx);
}

/**
  * @brief  Configure the character frame (data length, parity, stop bits)
  * @param  UARTx Specifies UART peripheral
  * @param  DataLen @ref LL_UART_DATAWIDTH_5B .. @ref LL_UART_DATAWIDTH_8B
  * @param  Parity @ref LL_UART_PARITY_NONE / EVEN / ODD
  * @param  StopLen @ref LL_UART_STOPBITS_1 or @ref LL_UART_STOPBITS_2
  * @return None
  */
__STATIC_INLINE void LL_UART_ConfigCharacter(UART_TypeDef *UARTx, uint32_t DataLen, uint32_t Parity, uint32_t StopLen)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));
    ASSERT_INLINE_PARAM(IS_LL_UART_DATAWIDTH(DataLen));
    ASSERT_INLINE_PARAM(IS_LL_UART_PARITY(Parity));
    ASSERT_INLINE_PARAM(IS_LL_UART_STOPBITS(StopLen));

    LL_UART_SetDataWidth(UARTx, DataLen);

    LL_UART_SetParity(UARTx, Parity);

    LL_UART_SetStopBitsLength(UARTx, StopLen);
}

/**
  * @}
  */ /* UART_LL_EF_Configuration */

/** @defgroup UART_LL_EF_DataTransfer LL UART Data Transfer
  * @{
  */

/**
  * @brief  TX data 8bits write
  * @param  UARTx Specifies UART peripheral
  * @param  Dat 8bits write data
  * @return None
  */
__STATIC_INLINE void LL_UART_TransmitData8(UART_TypeDef *UARTx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    WRITE_REG(UARTx->TDR, ((Dat) & 0xffUL));
}

/**
  * @brief  TX data 9bits write
  * @param  UARTx Specifies UART peripheral
  * @param  Dat 9bits write data
  * @return None
  */
__STATIC_INLINE void LL_UART_TransmitData9(UART_TypeDef *UARTx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    WRITE_REG(UARTx->TDR, ((Dat) & 0x1ffUL));
}

/**
  * @brief  RX data 8bits read
  * @param  UARTx Specifies UART peripheral
  * @return 8bits read data
  */
__STATIC_INLINE uint32_t LL_UART_ReceiveData8(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)((READ_BIT(UARTx->RDR, 0xffUL)));
}

/**
  * @brief  RX data 9bits read
  * @param  UARTx Specifies UART peripheral
  * @return 9bits read data
  */
__STATIC_INLINE uint32_t LL_UART_ReceiveData9(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)((READ_BIT(UARTx->RDR, 0x1ffUL)));
}

/**
  * @brief  Read the whole RX data register word (data + frame/parity/overrun status)
  * @note   RDR is a FIFO read port: one read pops the oldest data together with its status
  *         bits. When the status of the received frame is needed, read the word once with
  *         this API and then decode it with LL_UART_IsRxStopBitError() /
  *         LL_UART_IsRxParityBitError() / LL_UART_GetRxOverrunData()
  * @param  UARTx Specifies UART peripheral
  * @return RDR word (RD[8:0] + PRST[9] + FMST[10] + OVDA[26:16])
  */
__STATIC_INLINE uint32_t LL_UART_ReadRxDataWord(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_REG(UARTx->RDR));
}

/**
  * @brief  Judge the stop bit status of the word read back from RDR (RDR.FMST)
  * @param  RxWord Word returned by LL_UART_ReadRxDataWord()
  * @retval 0 Stop bit is correct
  * @retval 1 Stop bit error
  */
__STATIC_INLINE uint32_t LL_UART_IsRxStopBitError(uint32_t RxWord)
{
    return (uint32_t)(READ_BIT_SHIFT(RxWord, UART0_RDR_FMST_Msk, UART0_RDR_FMST_Pos));
}

/**
  * @brief  Judge the parity status of the word read back from RDR (RDR.PRST)
  * @param  RxWord Word returned by LL_UART_ReadRxDataWord()
  * @retval 0 Parity bit is correct
  * @retval 1 Parity bit error
  */
__STATIC_INLINE uint32_t LL_UART_IsRxParityBitError(uint32_t RxWord)
{
    return (uint32_t)(READ_BIT_SHIFT(RxWord, UART0_RDR_PRST_Msk, UART0_RDR_PRST_Pos));
}

/**
  * @brief  Get the overrun data of the word read back from RDR (RDR.OVDA)
  * @note   Only meaningful when the overrun-disabled mode is enabled (CR0.OVDIS = 1):
  *         after the RX FIFO is full, further received data is stored here instead of
  *         raising an overrun flag
  * @param  RxWord Word returned by LL_UART_ReadRxDataWord()
  * @return Overrun data (RD width, up to 9 bits)
  */
__STATIC_INLINE uint32_t LL_UART_GetRxOverrunData(uint32_t RxWord)
{
    return (uint32_t)(READ_BIT_SHIFT(RxWord, UART0_RDR_OVDA_Msk, UART0_RDR_OVDA_Pos));
}

/**
  * @}
  */ /* UART_LL_EF_DataTransfer */

/** @defgroup UART_LL_EF_Interrupt LL UART Interrupt Control
  * @{
  */

/**
  * @brief  Enable the specified UART interrupt source
  * @param  UARTx Specifies UART peripheral
  * @param  IntIt Source to enable @ref LL_UART_INTEN_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_UART_EnableIT(UART_TypeDef *UARTx, uint32_t IntIt)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    SET_BIT(UARTx->INTEN, IntIt);
}

/**
  * @brief  Disable the specified UART interrupt source
  * @param  UARTx Specifies UART peripheral
  * @param  IntIt Source to disable @ref LL_UART_INTEN_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_UART_DisableIT(UART_TypeDef *UARTx, uint32_t IntIt)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    CLEAR_BIT(UARTx->INTEN, IntIt);
}

/**
  * @brief  Check whether the specified UART interrupt source is enabled
  * @param  UARTx Specifies UART peripheral
  * @param  IntIt Source to check @ref LL_UART_INTEN_ITEnMskTypeDef
  * @return 0 interrupt disabled, 1 enabled
  */
__STATIC_INLINE uint32_t LL_UART_IsEnabledIT(const UART_TypeDef *UARTx, uint32_t IntIt)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT(UARTx->INTEN, IntIt) == (IntIt));
}

/**
  * @brief  Read UART interrupt enable mask
  * @param  UARTx Specifies UART peripheral
  * @return INTEN register value
  */
__STATIC_INLINE uint32_t LL_UART_ReadInterruptMask(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_REG(UARTx->INTEN));
}

/**
  * @}
  */ /* UART_LL_EF_Interrupt */

/** @defgroup UART_LL_EF_FLAG LL UART Flags
  * @{
  */

/**
  * @brief  Read the UART interrupt pending register
  * @param  UARTx Specifies UART peripheral
  * @return INT register value
  */
__STATIC_INLINE uint32_t LL_UART_ReadInterruptPending(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_REG(UARTx->INT));
}

/**
  * @brief  All Interrupt Pending Clear
  * @param  UARTx Specifies UART peripheral
  * @return None
  */
__STATIC_INLINE void LL_UART_ClearFlag_All(UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    WRITE_REG(UARTx->INT, 0xffffffffUL);
}

/**
  * @brief  Clear the specified interrupt pending bit(s)
  * @param  UARTx Specifies UART peripheral
  * @param  IntPnd Pending bits to clear @ref LL_UART_INT_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_UART_ClearFlag(UART_TypeDef *UARTx, uint32_t IntPnd)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    WRITE_REG(UARTx->INT, (IntPnd));
}

/**
  * @brief  Judge is RXFIFO Full or not
  * @retval 0 RXFIFO isn't Full, 1 RXFIFO is Full
  */
__STATIC_INLINE uint32_t LL_UART_IsRxFIFOFull(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_RFF_Msk, UART0_STATUS_RFF_Pos));
}

/**
  * @brief  Judge is RXFIFO Empty or not
  * @retval 0 RXFIFO isn't Empty, 1 RXFIFO is Empty
  */
__STATIC_INLINE uint32_t LL_UART_IsRxFIFOEmpty(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_RFE_Msk, UART0_STATUS_RFE_Pos));
}

/**
  * @brief  Judge is Rx Busy or not
  * @retval 0 Rx is Idle, 1 Rx is Busy
  */
__STATIC_INLINE uint32_t LL_UART_IsRxBusy(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_RBSY_Msk, UART0_STATUS_RBSY_Pos));
}

/**
  * @brief  Judge is TXFIFO Full or not
  * @retval 0 TXFIFO isn't Full, 1 TXFIFO is Full
  */
__STATIC_INLINE uint32_t LL_UART_IsTxFIFOFull(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_TFF_Msk, UART0_STATUS_TFF_Pos));
}

/**
  * @brief  Judge is TXFIFO Empty or not
  * @retval 0 TXFIFO isn't Empty, 1 TXFIFO is Empty
  */
__STATIC_INLINE uint32_t LL_UART_IsTxFIFOEmpty(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_TFE_Msk, UART0_STATUS_TFE_Pos));
}

/**
  * @brief  Judge is Tx Busy or not
  * @retval 0 Tx is Idle, 1 Tx is Busy
  */
__STATIC_INLINE uint32_t LL_UART_IsTxBusy(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_TBSY_Msk, UART0_STATUS_TBSY_Pos));
}

/**
  * @brief  Judge is RX-Start error detected or not (STATUS.RSE)
  * @note   Set by hardware when the received start bit is not valid
  * @param  UARTx Specifies UART peripheral
  * @retval 0 RX-Start error isn't detected
  * @retval 1 RX-Start error is detected
  */
__STATIC_INLINE uint32_t LL_UART_IsRxStartError(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_RSE_Msk, UART0_STATUS_RSE_Pos));
}

/**
  * @brief  Get the real-time level (data count) of the RX FIFO (STATUS.RFL)
  * @param  UARTx Specifies UART peripheral
  * @return RX FIFO level (0..31)
  */
__STATIC_INLINE uint32_t LL_UART_GetRxFIFOLevel(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_RFL_Msk, UART0_STATUS_RFL_Pos));
}

/**
  * @brief  Get the real-time level (data count) of the TX FIFO (STATUS.TFL)
  * @param  UARTx Specifies UART peripheral
  * @return TX FIFO level (0..31)
  */
__STATIC_INLINE uint32_t LL_UART_GetTxFIFOLevel(const UART_TypeDef *UARTx)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(READ_BIT_SHIFT(UARTx->STATUS, UART0_STATUS_TFL_Msk, UART0_STATUS_TFL_Pos));
}

/**
  * @brief  Check whether the specified interrupt/error flag is set
  * @param  UARTx Specifies UART peripheral
  * @param  IntPnd Flag to check @ref LL_UART_INT_ITPendingMskTypeDef
  * @return 0 flag not set, 1 flag set
  */
__STATIC_INLINE uint32_t LL_UART_IsActiveFlag(const UART_TypeDef *UARTx, uint32_t IntPnd)
{
    ASSERT_INLINE_PARAM(IS_UART_ALL_INSTANCE(UARTx));

    return (uint32_t)(((READ_REG(UARTx->INT)) & (IntPnd)) == (IntPnd));
}

/**
  * @}
  */ /* UART_LL_EF_FLAG */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* UART_LL_Exported_Functions */

/**
  * @}
  */ /* UART_LL */

#endif /* UART */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_UART_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
