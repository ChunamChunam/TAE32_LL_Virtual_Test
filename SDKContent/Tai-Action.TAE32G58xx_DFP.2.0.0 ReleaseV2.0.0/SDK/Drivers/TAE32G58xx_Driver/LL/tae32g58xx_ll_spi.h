/**
  ******************************************************************************
  * @file    tae32g58xx_ll_spi.h
  * @author  Tai-Action SD Team
  * @brief   Header file of SPI LL module.
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
#ifndef _TAE32G58XX_LL_SPI_H_
#define _TAE32G58XX_LL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined (SPI0) || defined (SPI1)

/** @defgroup SPI_LL SPI Low Layer Driver
  * @brief Low Layer driver for SPI module.
  * @{
  */


/* Exported Constants --------------------------------------------------------*/

/** @defgroup SPI_LL_Private_Macros SPI LL Private Macros
  * @brief    SPI LL Private Macros
  * @{
  */

/* IS_SPI_ALL_INSTANCE is defined in tae32g58xx.h (device header).
   The LL header includes the device header, so no need to redefine here. */

/**
  * @}
  */

/** @defgroup SPI_LL_EC_Instance LL SPI SPI Instance Definition
  * @brief    LL SPI SPI Instance Definition
  * @{
  */

/** @defgroup SPI_LL_Exported_Constants SPI LL Exported Constants
  * @brief    SPI LL Exported Constants
  * @{
  */

/**
  * @brief SPI Instance Definition
  * @note  LL layer uses #define for register-mapped values (no enum)
  */
#define LL_SPI_INSTANCE_0       ((uint32_t)0x00000000UL) /*!< SPI Instance 0         */
#define LL_SPI_INSTANCE_1       ((uint32_t)0x00000001UL) /*!< SPI Instance 1         */
#define LL_SPI_INSTANCE_NUMS    ((uint32_t)0x00000002UL) /*!< SPI Instance Numbers   */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_CSInputMode LL SPI SPI Slave CS Input Mode
  * @brief    LL SPI SPI Slave CS Input Mode
  * @{
  */

/**
  * @brief SPI Slave CS Input Mode Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_CS_INPUT_MODE_GPIO   ((uint32_t)0x00000000UL) /*!< SPI Slave CS Input Mode GPIO   */
#define LL_SPI_CS_INPUT_MODE_CSI    ((uint32_t)0x00000001UL) /*!< SPI Slave CS Input Mode CSI    */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_CSPolarity LL SPI SPI CS Polarity
  * @brief    LL SPI SPI CS Polarity
  * @{
  */

/**
  * @brief SPI CS Polarity Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_CS_POL_INACT_HIGH    ((uint32_t)0x00000000UL) /*!< SPI CS Polarity Inactive High  */
#define LL_SPI_CS_POL_INACT_LOW     ((uint32_t)0x00000001UL) /*!< SPI CS Polarity Inactive Low   */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_CSMode LL SPI SPI CS Mode
  * @brief    LL SPI SPI CS Mode
  * @{
  */

/**
  * @brief SPI CS Mode Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_CS_MODE_CONTINUE     ((uint32_t)0x00000000UL) /*!< SPI CS Mode Continue   */
#define LL_SPI_CS_MODE_ONE          ((uint32_t)0x00000001UL) /*!< SPI CS Mode One        */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_WireMode LL SPI SPI Wire Mode
  * @brief    LL SPI SPI Wire Mode
  * @{
  */

/**
  * @brief SPI Wire Mode Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_WIRE_MODE_4          ((uint32_t)0x00000000UL) /*!< SPI 4 Wire Mode */
#define LL_SPI_WIRE_MODE_3          ((uint32_t)0x00000001UL) /*!< SPI 3 Wire Mode */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_DataWidth LL SPI SPI Data Width
  * @brief    LL SPI SPI Data Width
  * @{
  */

/**
  * @brief SPI Data Width Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_DATA_WIDTH_RSV       ((uint32_t)0x00000000UL) /*!< SPI Data Width Reserve */
#define LL_SPI_DATA_WIDTH_2BIT      ((uint32_t)0x00000001UL) /*!< SPI Data Width 2bit    */
#define LL_SPI_DATA_WIDTH_3BIT      ((uint32_t)0x00000002UL) /*!< SPI Data Width 3bit    */
#define LL_SPI_DATA_WIDTH_4BIT      ((uint32_t)0x00000003UL) /*!< SPI Data Width 4bit    */
#define LL_SPI_DATA_WIDTH_5BIT      ((uint32_t)0x00000004UL) /*!< SPI Data Width 5bit    */
#define LL_SPI_DATA_WIDTH_6BIT      ((uint32_t)0x00000005UL) /*!< SPI Data Width 6bit    */
#define LL_SPI_DATA_WIDTH_7BIT      ((uint32_t)0x00000006UL) /*!< SPI Data Width 7bit    */
#define LL_SPI_DATA_WIDTH_8BIT      ((uint32_t)0x00000007UL) /*!< SPI Data Width 8bit    */
#define LL_SPI_DATA_WIDTH_9BIT      ((uint32_t)0x00000008UL) /*!< SPI Data Width 9bit    */
#define LL_SPI_DATA_WIDTH_10BIT     ((uint32_t)0x00000009UL) /*!< SPI Data Width 10bit   */
#define LL_SPI_DATA_WIDTH_11BIT     ((uint32_t)0x0000000AUL) /*!< SPI Data Width 11bit   */
#define LL_SPI_DATA_WIDTH_12BIT     ((uint32_t)0x0000000BUL) /*!< SPI Data Width 12bit   */
#define LL_SPI_DATA_WIDTH_13BIT     ((uint32_t)0x0000000CUL) /*!< SPI Data Width 13bit   */
#define LL_SPI_DATA_WIDTH_14BIT     ((uint32_t)0x0000000DUL) /*!< SPI Data Width 14bit   */
#define LL_SPI_DATA_WIDTH_15BIT     ((uint32_t)0x0000000EUL) /*!< SPI Data Width 15bit   */
#define LL_SPI_DATA_WIDTH_16BIT     ((uint32_t)0x0000000FUL) /*!< SPI Data Width 16bit   */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_BitOrder LL SPI SPI Bit Order
  * @brief    LL SPI SPI Bit Order
  * @{
  */

/**
  * @brief SPI Bit Order Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_BIT_ORDER_MSB        ((uint32_t)0x00000000UL) /*!< SPI Bit Order MSB  */
#define LL_SPI_BIT_ORDER_LSB        ((uint32_t)0x00000001UL) /*!< SPI Bit Order LSB  */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_SclkPolarity LL SPI SPI SCLK Polarity
  * @brief    LL SPI SPI SCLK Polarity
  * @{
  */

/**
  * @brief SPI SCLK Polarity Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_SCLK_POL_IDLE_LOW    ((uint32_t)0x00000000UL) /*!< SPI SCLK Polarity Idle Low     */
#define LL_SPI_SCLK_POL_IDLE_HIGH   ((uint32_t)0x00000001UL) /*!< SPI SCLK Polarity Idle High    */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_SclkPhase LL SPI SPI SCLK Phase
  * @brief    LL SPI SPI SCLK Phase
  * @{
  */

/**
  * @brief SPI SCLK Phase Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_SCLK_PHASE_CAP_EDGE_0  ((uint32_t)0x00000000UL) /*!< SPI SCLK Phase Capture at 0 Edge */
#define LL_SPI_SCLK_PHASE_CAP_EDGE_1  ((uint32_t)0x00000001UL) /*!< SPI SCLK Phase Capture at 1 Edge */
/**
  * @}
  */


/** @defgroup SPI_LL_EC_Role LL SPI SPI Role
  * @brief    LL SPI SPI Role
  * @{
  */

/**
  * @brief SPI Role Definition
  * @note  LL layer uses #define for register-mapped values
  */
#define LL_SPI_ROLE_SLAVE           ((uint32_t)0x00000000UL) /*!< SPI Role Slave     */
#define LL_SPI_ROLE_MASTER          ((uint32_t)0x00000001UL) /*!< SPI Role Master    */
/**
  * @}
  */

/* ------------------------------------------------------------------------- */
/** @defgroup SPI_LL_EC_BaudRate LL SPI Baud Rate Divider
  * @brief    LL SPI Baud Rate Divider (PCLK / N)
  * @{
  */
#define LL_SPI_BAUDRATE_DIV_2       (2UL)     /*!< PCLK / 2    */
#define LL_SPI_BAUDRATE_DIV_4       (4UL)     /*!< PCLK / 4    */
#define LL_SPI_BAUDRATE_DIV_8       (8UL)     /*!< PCLK / 8    */
#define LL_SPI_BAUDRATE_DIV_16      (16UL)    /*!< PCLK / 16   */
#define LL_SPI_BAUDRATE_DIV_32      (32UL)    /*!< PCLK / 32   */
#define LL_SPI_BAUDRATE_DIV_64      (64UL)    /*!< PCLK / 64   */
#define LL_SPI_BAUDRATE_DIV_128     (128UL)   /*!< PCLK / 128  */
#define LL_SPI_BAUDRATE_DIV_256     (256UL)   /*!< PCLK / 256  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_TransferDirection LL SPI Transfer Direction
  * @brief    LL SPI Transfer Direction
  * @{
  */
#define LL_SPI_FULL_DUPLEX          ((uint32_t)(SPI0_CTRL_RXEN_Msk | SPI0_CTRL_TXEN_Msk)) /*!< Full duplex: Tx and Rx */
#define LL_SPI_HALF_DUPLEX_RX       ((uint32_t)(SPI0_CTRL_RXEN_Msk))                     /*!< Rx only                */
#define LL_SPI_HALF_DUPLEX_TX       ((uint32_t)(SPI0_CTRL_TXEN_Msk))                     /*!< Tx only                */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_CS LL SPI CS Management
  * @brief    LL SPI CS Management
  * @{
  */
#define LL_SPI_CS_SOFT                 (0UL) /*!< Software CS management */
#define LL_SPI_CS_HARD                 (1UL) /*!< Hardware CS management */
/**
  * @}
  */

/* Parameter check macros ---------------------------------------------------*/
#define IS_LL_SPI_ROLE(__VAL__)                     (((__VAL__) == LL_SPI_ROLE_SLAVE)  || \
                                                     ((__VAL__) == LL_SPI_ROLE_MASTER))

#define IS_LL_SPI_WIRE_MODE(__VAL__)                (((__VAL__) == LL_SPI_WIRE_MODE_3) || \
                                                     ((__VAL__) == LL_SPI_WIRE_MODE_4))

#define IS_LL_SPI_DATA_WIDTH(__VAL__)               (((__VAL__) >= LL_SPI_DATA_WIDTH_2BIT) && \
                                                     ((__VAL__) <= LL_SPI_DATA_WIDTH_16BIT))

#define IS_LL_SPI_BIT_ORDER(__VAL__)                (((__VAL__) == LL_SPI_BIT_ORDER_MSB) || \
                                                     ((__VAL__) == LL_SPI_BIT_ORDER_LSB))

#define IS_LL_SPI_SCLK_POLARITY(__VAL__)            (((__VAL__) == LL_SPI_SCLK_POL_IDLE_LOW) || \
                                                     ((__VAL__) == LL_SPI_SCLK_POL_IDLE_HIGH))

#define IS_LL_SPI_SCLK_PHASE(__VAL__)               (((__VAL__) == LL_SPI_SCLK_PHASE_CAP_EDGE_0) || \
                                                     ((__VAL__) == LL_SPI_SCLK_PHASE_CAP_EDGE_1))

#define IS_LL_SPI_CS_MODE(__VAL__)                  (((__VAL__) == LL_SPI_CS_MODE_CONTINUE) || \
                                                     ((__VAL__) == LL_SPI_CS_MODE_ONE))

#define IS_LL_SPI_CS_INPUT_MODE(__VAL__)            (((__VAL__) == LL_SPI_CS_INPUT_MODE_GPIO) || \
                                                     ((__VAL__) == LL_SPI_CS_INPUT_MODE_CSI))

#define IS_LL_SPI_CS_POLARITY(__VAL__)              (((__VAL__) == LL_SPI_CS_POL_INACT_HIGH) || \
                                                     ((__VAL__) == LL_SPI_CS_POL_INACT_LOW))

#define IS_LL_SPI_TRANSFER_DIRECTION(__VAL__)       (((__VAL__) == LL_SPI_FULL_DUPLEX) || \
                                                     ((__VAL__) == LL_SPI_HALF_DUPLEX_RX) || \
                                                     ((__VAL__) == LL_SPI_HALF_DUPLEX_TX))

#define IS_LL_SPI_CS(__VAL__)                      (((__VAL__) == LL_SPI_CS_SOFT) || \
                                                     ((__VAL__) == LL_SPI_CS_HARD))

#define IS_LL_SPI_BAUDRATE_DIV(__VAL__)             (((__VAL__) >= 1UL) && \
                                                     ((__VAL__) <= 2048UL))    /*!< BAUD is an 11-bit divider field */

#define IS_LL_SPI_FIFO_THRESHOLD(__VAL__)           (((__VAL__) >= 1UL) && ((__VAL__) <= 16UL))

#define IS_LL_SPI_DMA_REG_DATA(__VAL__)             (((__VAL__) == LL_SPI_DMA_REG_DATA_TRANSMIT) || \
                                                     ((__VAL__) == LL_SPI_DMA_REG_DATA_RECEIVE))



/** @defgroup SPI_LL_EC_InterruptFlag LL SPI SPI Interrupt/Status Flag Mask
  * @brief    LL SPI SPI Interrupt/Status Flag Mask
  * @{
  */

/**
  * @brief SPI Interrupt/Status Register Bit Mask Definition
  */
#define LL_SPI_INT_RXFI             (SPI0_INT_RXFI_Msk)      /*!< RxFIFO full interrupt flag        */
#define LL_SPI_INT_TXEI             (SPI0_INT_TXEI_Msk)      /*!< TxFIFO empty interrupt flag       */
#define LL_SPI_INT_RXOFI            (SPI0_INT_RXOFI_Msk)     /*!< RxFIFO overflow interrupt flag    */
#define LL_SPI_INT_RXUFI            (SPI0_INT_RXUFI_Msk)     /*!< RxFIFO underflow interrupt flag   */
#define LL_SPI_INT_TXOFI            (SPI0_INT_TXOFI_Msk)     /*!< TxFIFO overflow interrupt flag    */
#define LL_SPI_INT_TXUFI            (SPI0_INT_TXUFI_Msk)     /*!< TxFIFO underflow interrupt flag   */
#define LL_SPI_INT_OPFI             (SPI0_INT_OPFI_Msk)      /*!< Operation fault interrupt flag    */
#define LL_SPI_INT_MDFI             (SPI0_INT_MDFI_Msk)      /*!< Mode fault interrupt flag         */
#define LL_SPI_INT_TXDEI            (SPI0_INT_TXDEI_Msk)     /*!< Tx data empty interrupt flag      */
#define LL_SPI_INT_RXDEI            (SPI0_INT_RXDEI_Msk)     /*!< Rx data empty interrupt flag      */
#define LL_SPI_INT_TXCI             (SPI0_INT_TXCI_Msk)      /*!< Tx complete interrupt flag        */
#define LL_SPI_INT_RXCI             (SPI0_INT_RXCI_Msk)      /*!< Rx complete interrupt flag        */

#define LL_SPI_INT_IT_FLAG_MSK      ((SPI0_INT_RXCI_Msk  | SPI0_INT_TXCI_Msk  | \
                                      SPI0_INT_RXDEI_Msk | SPI0_INT_TXDEI_Msk | \
                                      SPI0_INT_MDFI_Msk  | SPI0_INT_OPFI_Msk  | \
                                      SPI0_INT_TXUFI_Msk | SPI0_INT_TXOFI_Msk | \
                                      SPI0_INT_RXUFI_Msk | SPI0_INT_RXOFI_Msk | \
                                      SPI0_INT_TXEI_Msk  | SPI0_INT_RXFI_Msk))
#define LL_SPI_INT_ITPendingMskTypeDef                  uint32_t
/**
  * @}
  */


/** @defgroup SPI_LL_EC_InterruptEnable LL SPI SPI Interrupt Enable Mask
  * @brief    LL SPI SPI Interrupt Enable Mask
  * @{
  */

#define LL_SPI_INTEN_RXFIE          (SPI0_INTEN_RXFIE_Msk)   /*!< RxFIFO full interrupt enable       */
#define LL_SPI_INTEN_TXEIE          (SPI0_INTEN_TXEIE_Msk)   /*!< TxFIFO empty interrupt enable      */
#define LL_SPI_INTEN_RXOFIE         (SPI0_INTEN_RXOFIE_Msk)  /*!< RxFIFO overflow interrupt enable   */
#define LL_SPI_INTEN_RXUFIE         (SPI0_INTEN_RXUFIE_Msk)  /*!< RxFIFO underflow interrupt enable  */
#define LL_SPI_INTEN_TXOFIE         (SPI0_INTEN_TXOFIE_Msk)  /*!< TxFIFO overflow interrupt enable   */
#define LL_SPI_INTEN_TXUFIE         (SPI0_INTEN_TXUFIE_Msk)  /*!< TxFIFO underflow interrupt enable  */
#define LL_SPI_INTEN_OPFIE          (SPI0_INTEN_OPFIE_Msk)   /*!< Operation fault interrupt enable   */
#define LL_SPI_INTEN_MDFIE          (SPI0_INTEN_MDFIE_Msk)   /*!< Mode fault interrupt enable        */
#define LL_SPI_INTEN_TXDEIE         (SPI0_INTEN_TXDEIE_Msk)  /*!< Tx data empty interrupt enable     */
#define LL_SPI_INTEN_RXDEIE         (SPI0_INTEN_RXDEIE_Msk)  /*!< Rx data empty interrupt enable     */
#define LL_SPI_INTEN_TXCIE          (SPI0_INTEN_TXCIE_Msk)   /*!< Tx complete interrupt enable       */
#define LL_SPI_INTEN_RXCIE          (SPI0_INTEN_RXCIE_Msk)   /*!< Rx complete interrupt enable       */

#define LL_SPI_INTEN_IT_EN_MSK      ((SPI0_INTEN_RXCIE_Msk  | SPI0_INTEN_TXCIE_Msk  | \
                                      SPI0_INTEN_RXDEIE_Msk | SPI0_INTEN_TXDEIE_Msk | \
                                      SPI0_INTEN_MDFIE_Msk  | SPI0_INTEN_OPFIE_Msk  | \
                                      SPI0_INTEN_TXUFIE_Msk | SPI0_INTEN_TXOFIE_Msk | \
                                      SPI0_INTEN_RXUFIE_Msk | SPI0_INTEN_RXOFIE_Msk | \
                                      SPI0_INTEN_TXEIE_Msk  | SPI0_INTEN_RXFIE_Msk))
#define LL_SPI_INTEN_ERR_MSK        ((SPI0_INTEN_RXOFIE_Msk | SPI0_INTEN_RXUFIE_Msk | \
                                      SPI0_INTEN_TXOFIE_Msk | SPI0_INTEN_TXUFIE_Msk | \
                                      SPI0_INTEN_OPFIE_Msk  | SPI0_INTEN_MDFIE_Msk))  /*!< Error type interrupt enable bits */

#define LL_SPI_INTEN_ITEnMskTypeDef                     uint32_t
/**
  * @}
  */


/** @defgroup SPI_LL_EC_DMAReg LL SPI Data Register Selection for DMA
  * @brief    LL SPI Data Register Selection for DMA
  * @{
  */
#define LL_SPI_DMA_REG_DATA_TRANSMIT    (0x0UL) /*!< Transmit data register (TDR) */
#define LL_SPI_DMA_REG_DATA_RECEIVE     (0x1UL) /*!< Receive data register (RDR)  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_Status LL SPI SPI Status Flag Mask
  * @brief    LL SPI SPI Status Flag Mask
  * @{
  */

#define LL_SPI_STATUS_BUSY          (SPI0_STATUS_BUSY_Msk)   /*!< SPI busy flag                      */
#define LL_SPI_STATUS_TFE           (SPI0_STATUS_TFE_Msk)    /*!< TxFIFO empty flag                  */
#define LL_SPI_STATUS_TFF           (SPI0_STATUS_TFF_Msk)    /*!< TxFIFO full flag                   */
#define LL_SPI_STATUS_RFE           (SPI0_STATUS_RFE_Msk)    /*!< RxFIFO empty flag                  */
#define LL_SPI_STATUS_RFF           (SPI0_STATUS_RFF_Msk)    /*!< RxFIFO full flag                   */
#define LL_SPI_STATUS_TXFLR         (SPI0_STATUS_TXFLR_Msk)  /*!< TxFIFO level (multi-bit: 0..31)    */
#define LL_SPI_STATUS_RXFLR         (SPI0_STATUS_RXFLR_Msk)  /*!< RxFIFO level (multi-bit: 0..31)    */
/**
  * @}
  */


/**
  * @}
  */

/* Exported Functions -----------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Functions SPI LL Exported Functions
  * @brief    SPI LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_SPI_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_SPI_ASSERT_INLINE_PARAM == 1)
extern void LL_SPI_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_SPI_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_SPI_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_SPI_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @brief  Slave CS Software Input Status Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return Slave CS Software Input Status
  */
__STATIC_INLINE uint32_t LL_SPI_GetCSSlaveSwInputStatus(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_CSI_Msk, SPI0_ENABLE_CSI_Pos);
}


/**
  * @brief  Slave CS Input Mode Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  mode Slave CS Input Mode
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetCSSlaveInputMode(SPI_TypeDef *SPIx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_CS_INPUT_MODE(Mode));

    MODIFY_REG((SPIx)->ENABLE, SPI0_ENABLE_CSIS_Msk, (((Mode) & 0x1UL) << SPI0_ENABLE_CSIS_Pos));
}

/**
  * @brief  Get Slave CS Input Mode (CASE_305b/203a Slave Software CS Input Select)
  * @param  __SPI__ Specifies SPI peripheral
  * @return Slave CS Input Mode
  */
__STATIC_INLINE uint32_t LL_SPI_GetCSSlaveInputMode(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_CSIS_Msk, SPI0_ENABLE_CSIS_Pos);
}


/**
  * @brief  CS Software Output Inactive
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_CSSwOutInactive(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_CSO_Msk);
}


/**
  * @brief  CS Software Output Active
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_CSSwOutActive(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_CSO_Msk);
}

/**
  * @brief  Get CS Software Output Status (CASE_305a Master Soft CS Output Value)
  * @param  __SPI__ Specifies SPI peripheral
  * @return CS Software Output Status (0: Active, 1: Inactive)
  */
__STATIC_INLINE uint32_t LL_SPI_GetCSSwOutStatus(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_CSO_Msk, SPI0_ENABLE_CSO_Pos);
}


/**
  * @brief  CS Software Output Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableCSSwOut(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_CSOS_Msk);
}


/**
  * @brief  CS Software Output Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableCSSwOut(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_CSOS_Msk);
}


/**
  * @brief  Judge is CS Software Output Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 CS Software Output Disable
  * @retval 1 CS Software Output Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledCSSwOut(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_CSOS_Msk, SPI0_ENABLE_CSOS_Pos);
}


/**
  * @brief  TX DMA Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_TX(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_DTE_Msk);
}

/**
  * @brief  Judge is TX DMA Enable or not (CASE_310 DMA)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX DMA isn't Enable
  * @retval 1 TX DMA is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_TX(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_DTE_Msk, SPI0_ENABLE_DTE_Pos);
}


/**
  * @brief  TX DMA Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_TX(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_DTE_Msk);
}


/**
  * @brief  RX DMA Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_RX(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_DRE_Msk);
}

/**
  * @brief  Judge is RX DMA Enable or not (CASE_310 DMA)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX DMA isn't Enable
  * @retval 1 RX DMA is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_RX(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_DRE_Msk, SPI0_ENABLE_DRE_Pos);
}


/**
  * @brief  RX DMA Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_RX(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_DRE_Msk);
}


/**
  * @brief  Return the SPI data register address, used for DMA programming
  * @param  __SPI__ Specifies SPI peripheral
  * @param  Direction @ref LL_SPI_DMA_REG_DATA_TRANSMIT or @ref LL_SPI_DMA_REG_DATA_RECEIVE
  * @return The data register address (TDR or RDR)
  */
__STATIC_INLINE uint32_t LL_SPI_DMA_GetRegAddr(const SPI_TypeDef *SPIx, uint32_t Direction)
{
    uint32_t addr;

    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_DMA_REG_DATA(Direction));

    if ((Direction) == LL_SPI_DMA_REG_DATA_TRANSMIT) {
        addr = (uint32_t)(uintptr_t)(&SPIx->TDR);
    } else {
        addr = (uint32_t)(uintptr_t)(&SPIx->RDR);
    }

    return addr;
}


/**
  * @brief  Loopback Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableLoopback(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_LOOP_Msk);
}


/**
  * @brief  Loopback Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableLoopback(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_LOOP_Msk);
}


/**
  * @brief  Judge is Loopback Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Loopback isn't Enable
  * @retval 1 Loopback is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledLoopback(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_LOOP_Msk, SPI0_ENABLE_LOOP_Pos);
}


/**
  * @brief  MOSI/MISO Pin Swap Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableMOSIMISOSwap(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_SWAP_Msk);
}

/**
  * @brief  Judge is MOSI/MISO Pin Swap Enable or not (CASE_302 Pin Swap)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Pin Swap isn't Enable
  * @retval 1 Pin Swap is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledSwap(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_SWAP_Msk, SPI0_ENABLE_SWAP_Pos);
}


/**
  * @brief  MOSI/MISO Pin Swap Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableMOSIMISOSwap(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_SWAP_Msk);
}


/**
  * @brief  CS Polarity Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  pol CS Polarity
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetCSPolarity(SPI_TypeDef *SPIx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_CS_POLARITY(Pol));

    MODIFY_REG((SPIx)->ENABLE, SPI0_ENABLE_CSPOL_Msk, (((Pol) & 0x1UL) << SPI0_ENABLE_CSPOL_Pos));
}

/**
  * @brief  Get CS Polarity (CASE_304b)
  * @param  __SPI__ Specifies SPI peripheral
  * @return CS Polarity
  */
__STATIC_INLINE uint32_t LL_SPI_GetCSPolarity(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_CSPOL_Msk, SPI0_ENABLE_CSPOL_Pos);
}


/**
  * @brief  CS Pulse Management Enable (CS is pulled high between two data frames)
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableCSPulseMgt(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_CSSEL_Msk);
}

/**
  * @brief  CS Pulse Management Disable (CS keeps active until the transfer is stopped)
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableCSPulseMgt(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_CSSEL_Msk);
}

/**
  * @brief  Judge is CS Pulse Management Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 CS Pulse Management isn't Enable
  * @retval 1 CS Pulse Management is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledCSPulse(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_CSSEL_Msk, SPI0_ENABLE_CSSEL_Pos);
}


/**
  * @brief  Wire Mode Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  mode Wire Mode @ref LL_SPI_WIRE_MODE_4, LL_SPI_WIRE_MODE_3
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetStandard(SPI_TypeDef *SPIx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_WIRE_MODE(Mode));

    MODIFY_REG((SPIx)->ENABLE, SPI0_ENABLE_TWE_Msk, (((Mode) & 0x1UL) << SPI0_ENABLE_TWE_Pos));
}


/**
  * @brief  Wire Mode Set
  * @param  __SPI__ Specifies SPI peripheral
  * @return Wire Mode @ref LL_SPI_WIRE_MODE_4, LL_SPI_WIRE_MODE_3
  */
__STATIC_INLINE uint32_t LL_SPI_GetStandard(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->ENABLE, SPI0_ENABLE_TWE_Msk, SPI0_ENABLE_TWE_Pos);
}


/**
  * @brief  TXFIFO Reset
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ResetTxFIFO(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_TFR_Msk);
}


/**
  * @brief  RXFIFO Reset
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ResetRxFIFO(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_RFR_Msk);
}


/**
  * @brief  SPI Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_Enable(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->ENABLE, SPI0_ENABLE_SPIEN_Msk);
}


/**
  * @brief  SPI Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_Disable(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->ENABLE, SPI0_ENABLE_SPIEN_Msk);
}


/**
  * @brief  Judge is SPI Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 SPI isn't Enable
  * @retval 1 SPI is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabled(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return ((READ_BIT((SPIx)->ENABLE, SPI0_ENABLE_SPIEN_Msk) != 0UL) ? 1UL : 0UL);
}



/**
  * @brief  Master RX Delay Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  pclk_cnt RX Delay pclk count
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetMasterRxDelay(SPI_TypeDef *SPIx, uint32_t PclkCnt)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    MODIFY_REG((SPIx)->CTRL, SPI0_CTRL_RXDLY_Msk, (((PclkCnt) & 0x7UL) << SPI0_CTRL_RXDLY_Pos));
}

/**
  * @brief  Get Master RX Delay (CASE_309, return pclk delay count)
  * @param  __SPI__ Specifies SPI peripheral
  * @return RX Delay pclk count
  */
__STATIC_INLINE uint32_t LL_SPI_GetMasterRxDelay(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_RXDLY_Msk, SPI0_CTRL_RXDLY_Pos);
}


/**
  * @brief  Serial Data Length Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  len Serial Data Length
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t Len)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_DATA_WIDTH(Len));

    MODIFY_REG((SPIx)->CTRL, SPI0_CTRL_LEN_Msk, (((Len) & 0xfUL) << SPI0_CTRL_LEN_Pos));
}


/**
  * @brief  Serial Data Length Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return Serial Data Length
  */
__STATIC_INLINE uint32_t LL_SPI_GetDataWidth(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_LEN_Msk, SPI0_CTRL_LEN_Pos);
}


/**
  * @brief  SPI Slave Tx underrun last frame
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_SlaveTxUnderrunLastFrame(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->CTRL, SPI0_CTRL_UDRCFG_Msk);
}


/**
  * @brief  SPI Slave Tx underrun user data
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_SlaveTxUnderrunUserDat(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->CTRL, SPI0_CTRL_UDRCFG_Msk);
}

/**
  * @brief  Get Slave Underflow Behavior Config (CASE_200a/200b Underflow Behavior)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Slave underrun sends User Data
  * @retval 1 Slave underrun holds Last Frame
  */
__STATIC_INLINE uint32_t LL_SPI_GetSlaveUDRCFG(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_UDRCFG_Msk, SPI0_CTRL_UDRCFG_Pos);
}


/**
  * @brief  Bit Order Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  order Bit Order
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t Order)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_BIT_ORDER(Order));

    MODIFY_REG((SPIx)->CTRL, SPI0_CTRL_LSB_Msk, (((Order) & 0x1UL) << SPI0_CTRL_LSB_Pos));
}

/**
  * @brief  Get Transfer Bit Order (CASE_303)
  * @param  __SPI__ Specifies SPI peripheral
  * @return Bit Order @ref LL_SPI_BIT_ORDER_MSB, LL_SPI_BIT_ORDER_LSB
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferBitOrder(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_LSB_Msk, SPI0_CTRL_LSB_Pos);
}


/**
  * @brief  Set Transfer Direction
  * @param  __SPI__ Specifies SPI peripheral
  * @param  Direction @ref LL_SPI_FULL_DUPLEX, LL_SPI_HALF_DUPLEX_RX, LL_SPI_HALF_DUPLEX_TX
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t Direction)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_TRANSFER_DIRECTION(Direction));

    MODIFY_REG((SPIx)->CTRL, (SPI0_CTRL_RXEN_Msk | SPI0_CTRL_TXEN_Msk), Direction);
}

/**
  * @brief  Get Transfer Direction
  * @param  __SPI__ Specifies SPI peripheral
  * @return Transfer Direction @ref LL_SPI_FULL_DUPLEX, LL_SPI_HALF_DUPLEX_RX, LL_SPI_HALF_DUPLEX_TX
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferDirection(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT((SPIx)->CTRL, (SPI0_CTRL_RXEN_Msk | SPI0_CTRL_TXEN_Msk));
}

/**
  * @brief  TX Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableTx(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->CTRL, SPI0_CTRL_TXEN_Msk);
}


/**
  * @brief  TX Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableTx(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->CTRL, SPI0_CTRL_TXEN_Msk);
}


/**
  * @brief  RX Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableRx(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->CTRL, SPI0_CTRL_RXEN_Msk);
}


/**
  * @brief  RX Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableRx(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->CTRL, SPI0_CTRL_RXEN_Msk);
}


/**
  * @brief  Judge is TX Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX isn't Enable
  * @retval 1 TX is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledTx(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_TXEN_Msk, SPI0_CTRL_TXEN_Pos);
}


/**
  * @brief  Judge is RX Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX isn't Enable
  * @retval 1 RX is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledRx(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_RXEN_Msk, SPI0_CTRL_RXEN_Pos);
}


/**
  * @brief  Slave High-Z Output Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableSlaveHighZOut(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->CTRL, SPI0_CTRL_SHZOE_Msk);
}

/**
  * @brief  Judge is Slave High-Z Output Enable or not (CASE_204 Slave High-Z)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Slave High-Z Output isn't Enable
  * @retval 1 Slave High-Z Output is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledSlvOutputHiZ(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_SHZOE_Msk, SPI0_CTRL_SHZOE_Pos);
}


/**
  * @brief  Slave High-Z Output Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableSlaveHighZOut(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->CTRL, SPI0_CTRL_SHZOE_Msk);
}


/**
  * @brief  SCLK Polarity Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  pol SCLK Polarity
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t Pol)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_SCLK_POLARITY(Pol));

    MODIFY_REG((SPIx)->CTRL, SPI0_CTRL_CPOL_Msk, (((Pol) & 0x1UL) << SPI0_CTRL_CPOL_Pos));
}


/**
  * @brief  SCLK Phase Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  phase SCLK Phase
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t Phase)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_SCLK_PHASE(Phase));

    MODIFY_REG((SPIx)->CTRL, SPI0_CTRL_CPHA_Msk, (((Phase) & 0x1UL) << SPI0_CTRL_CPHA_Pos));
}


/**
  * @brief  SCLK Polarity Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return SCLK Polarity
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPolarity(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_CPOL_Msk, SPI0_CTRL_CPOL_Pos);
}


/**
  * @brief  SCLK Phase Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return SCLK Phase
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPhase(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_CPHA_Msk, SPI0_CTRL_CPHA_Pos);
}


/**
  * @brief  SPI Role Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  role SPI Role
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetMode(SPI_TypeDef *SPIx, uint32_t Role)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_ROLE(Role));

    MODIFY_REG((SPIx)->CTRL, SPI0_CTRL_MSTEN_Msk, (((Role) & 0x1UL) << SPI0_CTRL_MSTEN_Pos));
}


/**
 * @brief  SPI Role Get
 * @param  __SPI__ Specifies SPI peripheral
 * @return SPI Role @ref LL_SPI_ROLE_SLAVE, LL_SPI_ROLE_MASTER
 */
__STATIC_INLINE uint32_t LL_SPI_GetMode(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CTRL, SPI0_CTRL_MSTEN_Msk, SPI0_CTRL_MSTEN_Pos);
}



/**
  * @brief  SPI Baud Rate Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  br SPI Baud Rate Reg Value
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetBaudRatePrescaler(SPI_TypeDef *SPIx, uint32_t Br)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_BAUDRATE_DIV(Br));

    MODIFY_REG((SPIx)->BAUD, SPI0_BAUD_BAUD_Msk, (((Br) & 0x7ffUL) << SPI0_BAUD_BAUD_Pos));
}


/**
  * @brief  SPI Baud Rate Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return SPI Baud Rate
  */
__STATIC_INLINE uint32_t LL_SPI_GetBaudRatePrescaler(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->BAUD, SPI0_BAUD_BAUD_Msk, SPI0_BAUD_BAUD_Pos);
}



/**
  * @brief  RxFIFO Full Threshold Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  thres RxFIFO Full Threshold
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetRxFIFOThreshold(SPI_TypeDef *SPIx, uint32_t Thres)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_FIFO_THRESHOLD(Thres));

    MODIFY_REG((SPIx)->FIFOCTRL, SPI0_FIFOCTRL_RXFTLR_Msk, (((Thres-1) & 0xfUL) << SPI0_FIFOCTRL_RXFTLR_Pos));
}


/**
  * @brief  RxFIFO Full Threshold Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return RxFIFO Full Threshold
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxFIFOThreshold(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->FIFOCTRL, SPI0_FIFOCTRL_RXFTLR_Msk, SPI0_FIFOCTRL_RXFTLR_Pos) + 1;
}


/**
  * @brief  TxFIFO Empty Threshold Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  thres TxFIFO Empty Threshold
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetTxFIFOEmptyThreshold(SPI_TypeDef *SPIx, uint32_t Thres)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));
    ASSERT_INLINE_PARAM(IS_LL_SPI_FIFO_THRESHOLD(Thres));

    MODIFY_REG((SPIx)->FIFOCTRL, SPI0_FIFOCTRL_TXFTLR_Msk, (((Thres) & 0xfUL) << SPI0_FIFOCTRL_TXFTLR_Pos));
}


/**
  * @brief  TxFIFO Empty Threshold Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return TxFIFO Empty Threshold
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxFIFOEmptyThreshold(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->FIFOCTRL, SPI0_FIFOCTRL_TXFTLR_Msk, SPI0_FIFOCTRL_TXFTLR_Pos);
}



/**
  * @brief  Master TxRx Count Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  cnt TxRx Count
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetMasterTxRxCount(SPI_TypeDef *SPIx, uint32_t Cnt)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    MODIFY_REG((SPIx)->CNT, SPI0_CNT_DCNT_Msk, (((Cnt) & 0xffffUL) << SPI0_CNT_DCNT_Pos));
}



/**
  * @brief  Master TxRx Count Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return Master TxRx Count
  */
__STATIC_INLINE uint32_t LL_SPI_GetMasterTxRxCount(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->CNT, SPI0_CNT_DCNT_Msk, SPI0_CNT_DCNT_Pos);
}



/**
  * @brief  Master TxRx Remain Count Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return Master TxRx Remain Count
  */
__STATIC_INLINE uint32_t LL_SPI_GetMasterTxRxRemainCount(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_REG((SPIx)->RCNT);
}



/**
  * @brief  Master TxRx Stop
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_StopMasterTxRx(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->START, SPI0_START_STOP_Msk);
}

/**
  * @brief  Judge is Master TxRx Stopped or not (CASE_306e/311 STOP auto-clear)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Master TxRx isn't Stopped
  * @retval 1 Master TxRx is Stopped
  */
__STATIC_INLINE uint32_t LL_SPI_MasterTxRxIsStopped(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->START, SPI0_START_STOP_Msk, SPI0_START_STOP_Pos);
}


/**
  * @brief  Master TxRx Start
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_StartMasterTxRx(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->START, SPI0_START_START_Msk);
}



/**
  * @brief  Judge is Master TxRx Started or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Master TxRx isn't Started
  * @retval 1 Master TxRx is Started
  */
__STATIC_INLINE uint32_t LL_SPI_MasterTxRxIsStarted(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->START, SPI0_START_START_Msk, SPI0_START_START_Pos);
}



/**
  * @brief  Master SS Idleness Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  idle Master SS Idleness
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetMasterSSIdleness(SPI_TypeDef *SPIx, uint32_t Idle)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    MODIFY_REG((SPIx)->TIMING, SPI0_TIMING_MCSI_Msk, (((Idle - 1) & 0x1fUL) << SPI0_TIMING_MCSI_Pos));
}

/**
  * @brief  Get Master SS Idleness (CASE_307/504, return number of half-cycles + 1)
  * @param  __SPI__ Specifies SPI peripheral
  * @return Master SS idleness value (half-cycle count + 1)
  */
__STATIC_INLINE uint32_t LL_SPI_GetMasterSSIdleness(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->TIMING, SPI0_TIMING_MCSI_Msk, SPI0_TIMING_MCSI_Pos) + 1UL;
}


/**
  * @brief  Master Inter-Data Idleness Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  idle Master SS Idleness
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetMasterInterDatIdleness(SPI_TypeDef *SPIx, uint32_t Idle)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    MODIFY_REG((SPIx)->TIMING, SPI0_TIMING_MIDI_Msk, (((Idle - 1) & 0x1fUL) << SPI0_TIMING_MIDI_Pos));
}

/**
  * @brief  Get Master Inter-Data Idleness (CASE_307/504, return number of half-cycles + 1)
  * @param  __SPI__ Specifies SPI peripheral
  * @return Inter-data idleness value (half-cycle count + 1)
  */
__STATIC_INLINE uint32_t LL_SPI_GetMasterInterDatIdleness(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->TIMING, SPI0_TIMING_MIDI_Msk, SPI0_TIMING_MIDI_Pos) + 1UL;
}



/**
  * @brief  RX Complete Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXCI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_RXCIE_Msk);
}


/**
  * @brief  RX Complete Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXCI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_RXCIE_Msk);
}


/**
  * @brief  Judge is RX Complete Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX Complete Interrupt Disable
  * @retval 1 RX Complete Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXCI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_RXCIE_Msk, SPI0_INTEN_RXCIE_Pos);
}


/**
  * @brief  TX Complete Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXCI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_TXCIE_Msk);
}


/**
  * @brief  TX Complete Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXCI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_TXCIE_Msk);
}


/**
  * @brief  Judge is TX Complete Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX Complete Interrupt Disable
  * @retval 1 TX Complete Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXCI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_TXCIE_Msk, SPI0_INTEN_TXCIE_Pos);
}


/**
  * @brief  Error Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_ERR(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, LL_SPI_INTEN_ERR_MSK);
}

/**
  * @brief  Error Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_ERR(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, LL_SPI_INTEN_ERR_MSK);
}

/**
  * @brief  Judge is Error Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Error Interrupt Disable
  * @retval 1 Error Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_ERR(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return ((READ_BIT((SPIx)->INTEN, LL_SPI_INTEN_ERR_MSK) == LL_SPI_INTEN_ERR_MSK) ? 1UL : 0UL);
}


/**
  * @brief  RX Done Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXDEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_RXDEIE_Msk);
}


/**
  * @brief  RX Done Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXDEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_RXDEIE_Msk);
}


/**
  * @brief  Judge is RX Done Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX Done Interrupt Disable
  * @retval 1 RX Done Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXDEI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_RXDEIE_Msk, SPI0_INTEN_RXDEIE_Pos);
}


/**
  * @brief  TX Done Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXDEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_TXDEIE_Msk);
}


/**
  * @brief  TX Done Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXDEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_TXDEIE_Msk);
}


/**
  * @brief  Judge is TX Done Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX Done Interrupt Disable
  * @retval 1 TX Done Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXDEI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_TXDEIE_Msk, SPI0_INTEN_TXDEIE_Pos);
}


/**
  * @brief  Transmission Operation Fault Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_OPFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_OPFIE_Msk);
}


/**
  * @brief  Transmission Operation Fault Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_OPFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_OPFIE_Msk);
}


/**
  * @brief  Judge is Transmission Operation Fault Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Transmission Operation Fault Interrupt Disable
  * @retval 1 Transmission Operation Fault Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_OPFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_OPFIE_Msk, SPI0_INTEN_OPFIE_Pos);
}


/**
  * @brief  Transmission Mode Fault Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_MDFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_MDFIE_Msk);
}


/**
  * @brief  Transmission Mode Fault Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_MDFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_MDFIE_Msk);
}


/**
  * @brief  Judge is Transmission Mode Fault Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Transmission Mode Fault Interrupt Disable
  * @retval 1 Transmission Mode Fault Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_MDFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_MDFIE_Msk, SPI0_INTEN_MDFIE_Pos);
}


/**
  * @brief  Slave TxFIFO Underflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXUFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_TXUFIE_Msk);
}

/**
  * @brief  Judge is Slave TxFIFO Underflow Interrupt Enable or not (CASE_201/312)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Slave TxFIFO Underflow Interrupt isn't Enable
  * @retval 1 Slave TxFIFO Underflow Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXUFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_TXUFIE_Msk, SPI0_INTEN_TXUFIE_Pos);
}


/**
  * @brief  Slave TxFIFO Underflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXUFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_TXUFIE_Msk);
}


/**
  * @brief  TxFIFO Overflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXOFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_TXOFIE_Msk);
}

/**
  * @brief  Judge is TxFIFO Overflow Interrupt Enable or not (CASE_202)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TxFIFO Overflow Interrupt isn't Enable
  * @retval 1 TxFIFO Overflow Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXOFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_TXOFIE_Msk, SPI0_INTEN_TXOFIE_Pos);
}


/**
  * @brief  TxFIFO Overflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXOFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_TXOFIE_Msk);
}


/**
  * @brief  RxFIFO Underflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXUFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_RXUFIE_Msk);
}

/**
  * @brief  Judge is RxFIFO Underflow Interrupt Enable or not (CASE_201)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RxFIFO Underflow Interrupt isn't Enable
  * @retval 1 RxFIFO Underflow Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXUFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_RXUFIE_Msk, SPI0_INTEN_RXUFIE_Pos);
}


/**
  * @brief  RxFIFO Underflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXUFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_RXUFIE_Msk);
}


/**
  * @brief  RxFIFO Overflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXOFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_RXOFIE_Msk);
}

/**
  * @brief  Judge is RxFIFO Overflow Interrupt Enable or not (CASE_103/312)
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RxFIFO Overflow Interrupt isn't Enable
  * @retval 1 RxFIFO Overflow Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXOFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_RXOFIE_Msk, SPI0_INTEN_RXOFIE_Pos);
}


/**
  * @brief  RxFIFO Overflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXOFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_RXOFIE_Msk);
}


/**
  * @brief  TxFIFO Empty Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_TXEIE_Msk);
}


/**
  * @brief  TxFIFO Empty Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_TXEIE_Msk);
}


/**
  * @brief  Judge is TxFIFO Empty Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TxFIFO Empty Interrupt Disable
  * @retval 1 TxFIFO Empty Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXEI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_TXEIE_Msk, SPI0_INTEN_TXEIE_Pos);
}


/**
  * @brief  RxFIFO Full Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    SET_BIT((SPIx)->INTEN, SPI0_INTEN_RXFIE_Msk);
}


/**
  * @brief  RxFIFO Full Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    CLEAR_BIT((SPIx)->INTEN, SPI0_INTEN_RXFIE_Msk);
}


/**
  * @brief  Judge is RxFIFO Full Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RxFIFO Full Interrupt Disable
  * @retval 1 RxFIFO Full Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INTEN, SPI0_INTEN_RXFIE_Msk, SPI0_INTEN_RXFIE_Pos);
}


/**
  * @brief  All Interrupt Enable Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return All Interrupt Enable
  */
__STATIC_INLINE uint32_t LL_SPI_GetAllIntEn(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_REG((SPIx)->INTEN);
}



/**
  * @brief  All Interrupt Enable Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_DisableIT_AllInt(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INTEN, 0UL);
}



/**
  * @brief  Judge is RX Complete Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX hasn't Complete
  * @retval 1 RX has Complete
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXCI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_RXCI_Msk, SPI0_INT_RXCI_Pos);
}


/**
  * @brief  RX Complete Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_RXCI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_RXCI_Msk);
}


/**
  * @brief  Judge is TX Complete Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX hasn't Complete
  * @retval 1 TX has Complete
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXCI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_TXCI_Msk, SPI0_INT_TXCI_Pos);
}


/**
  * @brief  TX Complete Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_TXCI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_TXCI_Msk);
}


/**
  * @brief  Judge is RX Done Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX hasn't Done
  * @retval 1 RX has Done
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXDEI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_RXDEI_Msk, SPI0_INT_RXDEI_Pos);
}


/**
  * @brief  RX Done Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_RXDEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_RXDEI_Msk);
}


/**
  * @brief  Judge is TX Done Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX hasn't Done
  * @retval 1 TX has Done
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXDEI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_TXDEI_Msk, SPI0_INT_TXDEI_Pos);
}


/**
  * @brief  TX Done Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_TXDEI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_TXDEI_Msk);
}


/**
  * @brief  Judge is Transmission Mode Fault Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Transmission Mode hasn't Fault
  * @retval 1 Transmission Mode has Fault
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_MDFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_MDFI_Msk, SPI0_INT_MDFI_Pos);
}


/**
  * @brief  Transmission Mode Fault Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_MDFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_MDFI_Msk);
}


/**
  * @brief  Judge is Transmission Operation Fault Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Transmission Operation hasn't Fault
  * @retval 1 Transmission Operation has Fault
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_OPFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_OPFI_Msk, SPI0_INT_OPFI_Pos);
}


/**
  * @brief  Transmission Operation Fault Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_OPFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_OPFI_Msk);
}


/**
  * @brief  Judge is Slave TX Underflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Slave TX isn't Underflow
  * @retval 1 Slave TX is Underflow
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXUFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_TXUFI_Msk, SPI0_INT_TXUFI_Pos);
}


/**
  * @brief  TX Underflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_TXUFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_TXUFI_Msk);
}


/**
  * @brief  Judge is TX Overflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX isn't Overflow
  * @retval 1 TX is Overflow
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXOFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_TXOFI_Msk, SPI0_INT_TXOFI_Pos);
}


/**
  * @brief  TX Overflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_TXOFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_TXOFI_Msk);
}


/**
  * @brief  Judge is RX Underflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX isn't Underflow
  * @retval 1 RX is Underflow
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXUFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_RXUFI_Msk, SPI0_INT_RXUFI_Pos);
}


/**
  * @brief  RX Underflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_RXUFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_RXUFI_Msk);
}


/**
  * @brief  Judge is RX Overflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX isn't Overflow
  * @retval 1 RX is Overflow
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXOFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_RXOFI_Msk, SPI0_INT_RXOFI_Pos);
}


/**
  * @brief  RX Overflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_RXOFI(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, SPI0_INT_RXOFI_Msk);
}


/**
  * @brief  Judge is TX Empty Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX isn't Empty
  * @retval 1 TX is Empty
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXEI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_TXEI_Msk, SPI0_INT_TXEI_Pos);
}


/**
  * @brief  Judge is RX Full Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX isn't Full
  * @retval 1 RX is Full
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXFI(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->INT, SPI0_INT_RXFI_Msk, SPI0_INT_RXFI_Pos);
}


/**
  * @brief  All Interrupt Pending Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_AllIntPnd(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_REG((SPIx)->INT);
}


/**
  * @brief  All Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_AllIntPnd(SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, 0xffffffffUL);
}

/**
  * @brief  Check whether the specified SPI interrupt pending flag(s) are set.
  * @param  SPIx Specifies SPI peripheral
  * @param  FlagMask SPI interrupt pending bit mask (SPI0_INT_*)
  * @retval 1 if all masked bits are set, 0 otherwise
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag(const SPI_TypeDef *SPIx, uint32_t FlagMask)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return (uint32_t)(((READ_REG((SPIx)->INT)) & (FlagMask)) == (FlagMask));
}

/**
  * @brief  Clear the specified SPI interrupt pending flag(s).
  * @note   SPI INT uses write-1-to-clear semantics.
  * @param  SPIx Specifies SPI peripheral
  * @param  FlagMask SPI interrupt pending bit mask (SPI0_INT_*)
  * @return None
  */
__STATIC_INLINE void LL_SPI_ClearFlag(SPI_TypeDef *SPIx, uint32_t FlagMask)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->INT, FlagMask);
}



/**
  * @brief  Judge RxFIFO is Full or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RxFIFO isn't Full
  * @retval 1 RxFIFO is Full
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RFF(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->STATUS, SPI0_STATUS_RFF_Msk, SPI0_STATUS_RFF_Pos);
}


/**
  * @brief  Judge RxFIFO is Empty or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RxFIFO isn't Empty
  * @retval 1 RxFIFO is Empty
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RFE(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->STATUS, SPI0_STATUS_RFE_Msk, SPI0_STATUS_RFE_Pos);
}


/**
  * @brief  RxFIFO Level Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return RxFIFO Level
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxFIFOLevel(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->STATUS, SPI0_STATUS_RXFLR_Msk, SPI0_STATUS_RXFLR_Pos);
}


/**
  * @brief  Judge TxFIFO is Full or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TxFIFO isn't Full
  * @retval 1 TxFIFO is Full
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TFF(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->STATUS, SPI0_STATUS_TFF_Msk, SPI0_STATUS_TFF_Pos);
}


/**
  * @brief  Judge TxFIFO is Empty or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TxFIFO isn't Empty
  * @retval 1 TxFIFO is Empty
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TFE(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->STATUS, SPI0_STATUS_TFE_Msk, SPI0_STATUS_TFE_Pos);
}


/**
  * @brief  TxFIFO Level Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return TxFIFO Level
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxFIFOLevel(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->STATUS, SPI0_STATUS_TXFLR_Msk, SPI0_STATUS_TXFLR_Pos);
}


/**
  * @brief  Judge is SPI Busy or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 SPI isn't Busy
  * @retval 1 SPI is Busy
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_BSY(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->STATUS, SPI0_STATUS_BUSY_Msk, SPI0_STATUS_BUSY_Pos);
}



/**
  * @brief  SPI Data Write
  * @param  __SPI__ Specifies SPI peripheral
  * @param  dat data to write
  * @return None
  */
__STATIC_INLINE void LL_SPI_WriteData(SPI_TypeDef *SPIx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->TDR, (Dat & 0xffffUL));
}



/**
  * @brief  SPI Data Read
  * @param  __SPI__ Specifies SPI peripheral
  * @return Read data
  */
__STATIC_INLINE uint32_t LL_SPI_ReadData(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->RDR, SPI0_RDR_RD_Msk, SPI0_RDR_RD_Pos);
}



/**
  * @brief  Slave Underrun Data Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  dat Slave Underrun Data
  * @return None
  */
__STATIC_INLINE void LL_SPI_SetSlaveUnderrunDat(SPI_TypeDef *SPIx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    WRITE_REG((SPIx)->UDRDR, (Dat & 0xffffUL));
}

/**
  * @brief  Get Slave Underflow Transmit Data (CASE_200a Underflow Transmit Data)
  * @param  __SPI__ Specifies SPI peripheral
  * @return Slave Underflow Transmit Data
  */
__STATIC_INLINE uint32_t LL_SPI_GetSlaveUDRDR(const SPI_TypeDef *SPIx)
{
    ASSERT_INLINE_PARAM(IS_SPI_ALL_INSTANCE(SPIx));

    return READ_BIT_SHIFT((SPIx)->UDRDR, SPI0_UDRDR_UDRDR_Msk, SPI0_UDRDR_UDRDR_Pos);
}


#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */


/**
  * @}
  */ /* SPI_LL_Exported_Functions */

/**
  * @}
  */ /* SPI_LL */

#endif /* SPI */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_SPI_H_ */



/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

