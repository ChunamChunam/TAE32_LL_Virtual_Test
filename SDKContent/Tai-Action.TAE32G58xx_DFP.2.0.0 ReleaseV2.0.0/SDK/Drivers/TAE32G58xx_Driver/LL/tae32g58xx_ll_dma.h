/**
  ******************************************************************************
  * @file    tae32g58xx_ll_dma.h
  * @author  Tai-Action SD Team
  * @brief   Header file of DMA LL module.
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
#ifndef _TAE32G58XX_LL_DMA_H_
#define _TAE32G58XX_LL_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"
#include "tae32g58xx.h"

/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(DMA) 

/** @addtogroup DMA_LL DMA Low-Layer
  * @brief DMA LL module driver
  * @{
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Macros DMA LL Exported Macros
  * @{
  */



/** 
  * @brief DMA_LL_EC_BLOCK_SIZE DMA Block Transfer Size Limit
  * @{
  */
#define LL_DMA_BLOCK_SIZE_MAX                (DMA0_DBL_BL_Val)  /*!< Max block transfer count (DBL.BL is 12-bit) */

#define LL_DMA_CTR_ITEnMskTypeDef            uint32_t
#define LL_DMA_CTR_IT_EN_MSK                 (DMA0_CTR_CIE_Msk | DMA0_CTR_HCIE_Msk | DMA0_CTR_EIE_Msk)

#define LL_DMA_CTR_CIE                       (DMA0_CTR_CIE_Msk)                   /*!< CIE Mask                 */
#define LL_DMA_CTR_HCIE                      (DMA0_CTR_HCIE_Msk)                  /*!< HCIE Mask                */
#define LL_DMA_CTR_EIE                       (DMA0_CTR_EIE_Msk)                   /*!< EIE Mask                 */

#define LL_DMA_STR_IT_FLAG_MSK               (DMA0_STR_CS_Msk  | DMA0_STR_HS_Msk   | DMA0_STR_ES_Msk)

#define LL_DMA_STR_CS                        (DMA0_STR_CS_Msk)                    /*!< CS Mask                  */
#define LL_DMA_STR_HS                        (DMA0_STR_HS_Msk)                    /*!< HS Mask                  */
#define LL_DMA_STR_ES                        (DMA0_STR_ES_Msk)                    /*!< ES Mask                  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Constants DMA LL Exported Constants
  * @{
  */



/** @defgroup DMA_LL_EC_CHANNEL DMA Channel Index
  * @{
  */
#define LL_DMA_CHANNEL_0               0x00000000UL  /*!< DMA Channel 0 */
#define LL_DMA_CHANNEL_1               0x00000001UL  /*!< DMA Channel 1 */
#define LL_DMA_CHANNEL_2               0x00000002UL  /*!< DMA Channel 2 */
#define LL_DMA_CHANNEL_3               0x00000003UL  /*!< DMA Channel 3 */
#define LL_DMA_CHANNEL_4               0x00000004UL  /*!< DMA Channel 4 */
#define LL_DMA_CHANNEL_5               0x00000005UL  /*!< DMA Channel 5 */
#define LL_DMA_CHANNEL_NUMS            0x00000006UL  /*!< Total DMA channels */

#define IS_LL_DMA_CHANNEL(__VAL__)     (((__VAL__) >= LL_DMA_CHANNEL_0) && \
                                        ((__VAL__) < LL_DMA_CHANNEL_NUMS))
/**
  * @}
  */


/** @defgroup DMA_LL_EC_PERIPH_BUS DMA Peripheral Bus Selection
  * @{
  */
#define LL_DMA_PERIPH_BUS_AHB_MST1     0x00000000UL  /*!< AHB master bus 1 */
#define LL_DMA_PERIPH_BUS_AHB_MST2     0x00000001UL  /*!< AHB master bus 2 */

#define IS_LL_DMA_PERIPH_BUS(__VAL__)  (((__VAL__) == LL_DMA_PERIPH_BUS_AHB_MST1) || \
                                        ((__VAL__) == LL_DMA_PERIPH_BUS_AHB_MST2))
/**
  * @}
  */

/** @defgroup DMA_LL_EC_PRIORITY DMA Channel Priority
  * @{
  */
#define LL_DMA_PRIORITY_LEVEL_0       0x00000000UL  /*!< Priority level 0 */
#define LL_DMA_PRIORITY_LEVEL_1       0x00000001UL  /*!< Priority level 1 */
#define LL_DMA_PRIORITY_LEVEL_2       0x00000002UL  /*!< Priority level 2 */
#define LL_DMA_PRIORITY_LEVEL_3       0x00000003UL  /*!< Priority level 3 */
#define LL_DMA_PRIORITY_LEVEL_4       0x00000004UL  /*!< Priority level 4 */
#define LL_DMA_PRIORITY_LEVEL_5       0x00000005UL  /*!< Priority level 5 */
#define LL_DMA_PRIORITY_LEVEL_6       0x00000006UL  /*!< Priority level 6 */
#define LL_DMA_PRIORITY_LEVEL_7       0x00000007UL  /*!< Priority level 7 */

#define IS_LL_DMA_PRIORITY(__VAL__)    (((__VAL__) >= LL_DMA_PRIORITY_LEVEL_0) && \
                                        ((__VAL__) <= LL_DMA_PRIORITY_LEVEL_7))

/**
  * @}
  */

/** @defgroup DMA_LL_EC_BURST_LEN DMA Burst Length
  * @{
  */
#define LL_DMA_BURST_LEN_1             0x00000000UL  /*!< 1-beat burst */
#define LL_DMA_BURST_LEN_4             0x00000001UL  /*!< 4-beat burst */
#define LL_DMA_BURST_LEN_8             0x00000002UL  /*!< 8-beat burst */
#define LL_DMA_BURST_LEN_16            0x00000003UL  /*!< 16-beat burst */

#define IS_LL_DMA_BURST_LEN(__VAL__)   (((__VAL__) == LL_DMA_BURST_LEN_1)  || \
                                        ((__VAL__) == LL_DMA_BURST_LEN_4)  || \
                                        ((__VAL__) == LL_DMA_BURST_LEN_8)  || \
                                        ((__VAL__) == LL_DMA_BURST_LEN_16))
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRANS_TYPE DMA Transfer Type
  * @{
  */
#define LL_DMA_TRANS_TYPE_M2M          0x00000000UL  /*!< Memory to Memory */
#define LL_DMA_TRANS_TYPE_M2P          0x00000001UL  /*!< Memory to Peripheral */
#define LL_DMA_TRANS_TYPE_P2M          0x00000002UL  /*!< Peripheral to Memory */
#define LL_DMA_TRANS_TYPE_P2P          0x00000003UL  /*!< Peripheral to Peripheral */

#define IS_LL_DMA_TRANS_TYPE(__VAL__)  (((__VAL__) == LL_DMA_TRANS_TYPE_M2M) || \
                                        ((__VAL__) == LL_DMA_TRANS_TYPE_M2P) || \
                                        ((__VAL__) == LL_DMA_TRANS_TYPE_P2M) || \
                                        ((__VAL__) == LL_DMA_TRANS_TYPE_P2P))
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRANS_MODE DMA Transfer Mode
  * @{
  */
#define LL_DMA_TRANS_MODE_SINGLE       0x00000000UL  /*!< Single transfer */
#define LL_DMA_TRANS_MODE_CONTINUE     0x00000001UL  /*!< Continuous transfer */

#define IS_LL_DMA_TRANS_MODE(__VAL__)  (((__VAL__) == LL_DMA_TRANS_MODE_SINGLE) || \
                                        ((__VAL__) == LL_DMA_TRANS_MODE_CONTINUE))
/**
  * @}
  */

/** @defgroup DMA_LL_EC_ADDR_MODE DMA Address Mode
  * @{
  */
#define LL_DMA_ADDR_MODE_INC           0x00000000UL  /*!< Address increment */
#define LL_DMA_ADDR_MODE_FIX           0x00000001UL  /*!< Address fixed */

#define IS_LL_DMA_ADDR_MODE(__VAL__)   (((__VAL__) == LL_DMA_ADDR_MODE_INC) || \
                                        ((__VAL__) == LL_DMA_ADDR_MODE_FIX))
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DATA_WIDTH DMA Data Width
  * @{
  */
#define LL_DMA_DATA_WIDTH_BYTE         0x00000000UL  /*!< 8-bit  transfer width */
#define LL_DMA_DATA_WIDTH_HALFWORD     0x00000001UL  /*!< 16-bit transfer width */
#define LL_DMA_DATA_WIDTH_WORD         0x00000002UL  /*!< 32-bit transfer width */

#define IS_LL_DMA_DATA_WIDTH(__VAL__)  (((__VAL__) == LL_DMA_DATA_WIDTH_BYTE)     || \
                                        ((__VAL__) == LL_DMA_DATA_WIDTH_HALFWORD) || \
                                        ((__VAL__) == LL_DMA_DATA_WIDTH_WORD))
/**
  * @}
  */

/** @defgroup DMA_LL_EC_HS_IFC DMA Handshake Interface
  * @{
  */
#define LL_DMA_HS_IFC_MEM              0x7FFFFFFFUL  

#define LL_DMA_HS_IFC_I2C0_TX          0x00000000UL  /*!< I2C0 TX handshake */
#define LL_DMA_HS_IFC_I2C0_RX          0x00000001UL  /*!< I2C0 RX handshake */
#define LL_DMA_HS_IFC_I2C1_TX          0x00000002UL  /*!< I2C1 TX handshake */
#define LL_DMA_HS_IFC_I2C1_RX          0x00000003UL  /*!< I2C1 RX handshake */
#define LL_DMA_HS_IFC_I2C2_TX          0x00000004UL  /*!< I2C2 TX handshake */
#define LL_DMA_HS_IFC_I2C2_RX          0x00000005UL  /*!< I2C2 RX handshake */
#define LL_DMA_HS_IFC_UART0_TX         0x00000006UL  /*!< UART0 TX handshake */
#define LL_DMA_HS_IFC_UART0_RX         0x00000007UL  /*!< UART0 RX handshake */
#define LL_DMA_HS_IFC_UART1_TX         0x00000008UL  /*!< UART1 TX handshake */
#define LL_DMA_HS_IFC_UART1_RX         0x00000009UL  /*!< UART1 RX handshake */
#define LL_DMA_HS_IFC_UART2_TX         0x0000000AUL  /*!< UART2 TX handshake */
#define LL_DMA_HS_IFC_UART2_RX         0x0000000BUL  /*!< UART2 RX handshake */
#define LL_DMA_HS_IFC_UART3_TX         0x0000000CUL  /*!< UART3 TX handshake */
#define LL_DMA_HS_IFC_UART3_RX         0x0000000DUL  /*!< UART3 RX handshake */
#define LL_DMA_HS_IFC_UART4_TX         0x0000000EUL  /*!< UART4 TX handshake */
#define LL_DMA_HS_IFC_UART4_RX         0x0000000FUL  /*!< UART4 RX handshake */
#define LL_DMA_HS_IFC_SPI0_TX          0x00000010UL  /*!< SPI0 TX handshake */
#define LL_DMA_HS_IFC_SPI0_RX          0x00000011UL  /*!< SPI0 RX handshake */
#define LL_DMA_HS_IFC_SPI1_TX          0x00000012UL  /*!< SPI1 TX handshake */
#define LL_DMA_HS_IFC_SPI1_RX          0x00000013UL  /*!< SPI1 RX handshake */
#define LL_DMA_HS_IFC_XIF_TX           0x00000014UL  /*!< XIF TX handshake */
#define LL_DMA_HS_IFC_XIF_RX           0x00000015UL  /*!< XIF RX handshake */

#define LL_DMA_HS_IFC_HRPWM_SLV7       0x00000017UL  /*!< HRPWM_SLV7 handshake */
#define LL_DMA_HS_IFC_HRPWM_SLV6       0x00000018UL  /*!< HRPWM_SLV6 handshake */
#define LL_DMA_HS_IFC_HRPWM_SLV5       0x00000019UL  /*!< HRPWM_SLV5 handshake */
#define LL_DMA_HS_IFC_HRPWM_SLV4       0x0000001AUL  /*!< HRPWM_SLV4 handshake */
#define LL_DMA_HS_IFC_HRPWM_SLV3       0x0000001BUL  /*!< HRPWM_SLV3 handshake */
#define LL_DMA_HS_IFC_HRPWM_SLV2       0x0000001CUL  /*!< HRPWM_SLV2 handshake */
#define LL_DMA_HS_IFC_HRPWM_SLV1       0x0000001DUL  /*!< HRPWM_SLV1 handshake */
#define LL_DMA_HS_IFC_HRPWM_SLV0       0x0000001EUL  /*!< HRPWM_SLV0 handshake */
#define LL_DMA_HS_IFC_HRPWM_MST        0x0000001FUL  /*!< HRPWM_MST  handshake */

#define IS_LL_DMA_HS_IFC(__VAL__)      (((__VAL__) == LL_DMA_HS_IFC_MEM)          || \
                                        ((__VAL__) == LL_DMA_HS_IFC_I2C0_TX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_I2C0_RX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_I2C1_TX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_I2C1_RX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_I2C2_TX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_I2C2_RX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART0_TX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART0_RX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART1_TX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART1_RX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART2_TX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART2_RX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART3_TX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART3_RX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART4_TX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_UART4_RX)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_SPI0_TX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_SPI0_RX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_SPI1_TX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_SPI1_RX)     || \
                                        ((__VAL__) == LL_DMA_HS_IFC_XIF_TX)      || \
                                        ((__VAL__) == LL_DMA_HS_IFC_XIF_RX)      || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV7)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV6)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV5)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV4)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV3)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV2)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV1)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_SLV0)  || \
                                        ((__VAL__) == LL_DMA_HS_IFC_HRPWM_MST))
/**
  * @}
  */

/** @defgroup DMA_LL_EC_HS_IFC_MUX DMA Handshake Mux Selector
  * @{
  */
#define LL_DMA_HS_IFC_MUX_ADC3         0x00000013UL  /*!< ADC3 mux selector */
#define LL_DMA_HS_IFC_MUX_ADC2         0x00000014UL  /*!< ADC2 mux selector */
#define LL_DMA_HS_IFC_MUX_ADC1         0x00000015UL  /*!< ADC1 mux selector */
#define LL_DMA_HS_IFC_MUX_ADC0         0x00000016UL  /*!< ADC0 mux selector */
#define LL_DMA_HS_IFC_MUX_PDM0_RX      0x00000017UL  /*!< PDM0 mux selector */
#define LL_DMA_HS_IFC_MUX_PDM1_RX      0x00000019UL  /*!< PDM1 mux selector */
#define LL_DMA_HS_IFC_MUX_PDM2_RX      0x0000001BUL  /*!< PDM2 mux selector */
#define LL_DMA_HS_IFC_MUX_PDM3_RX      0x0000001DUL  /*!< PDM3 mux selector */

#define IS_LL_DMA_HS_IFC_MUX(__VAL__)  (((__VAL__) == LL_DMA_HS_IFC_MUX_ADC3)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_MUX_ADC2)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_MUX_ADC1)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_MUX_ADC0)    || \
                                        ((__VAL__) == LL_DMA_HS_IFC_MUX_PDM0_RX) || \
                                        ((__VAL__) == LL_DMA_HS_IFC_MUX_PDM1_RX) || \
                                        ((__VAL__) == LL_DMA_HS_IFC_MUX_PDM2_RX) || \
                                        ((__VAL__) == LL_DMA_HS_IFC_MUX_PDM3_RX))
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Functions DMA LL Exported Functions
  * @{
  */

/** @defgroup DMA_LL_EF_Reset DMA LL Reset Functions
  * @brief    DMA LL Reset functions
  * @{
  */

/**
  * @brief  Reset the DMA control registers to their default values.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_ResetControl(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    WRITE_REG(DMAx->CH[Channel].REG.CTR,  0x80000000UL);
}

/**
  * @}
  */

/** @defgroup DMA_LL_EF_Enable DMA Channel Enable/Disable Functions
  * @{
  */

/**
  * @brief  Check whether the specified DMA channel is enabled.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @retval 0 if disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.CER, DMA0_CER_CEN_Msk) == DMA0_CER_CEN_Msk) ? 1UL : 0UL);
}

/**
  * @brief  Enable the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_EnableChannel(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    SET_BIT(DMAx->CH[Channel].REG.CER, DMA0_CER_CEN_Msk);
}

/**
  * @brief  Disable the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_DisableChannel(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    CLEAR_BIT(DMAx->CH[Channel].REG.CER, DMA0_CER_CEN_Msk);
}

/**
  * @}
  */

/** @defgroup DMA_LL_EF_Configuration DMA Channel Configuration Functions
  * @brief    DMA channel configuration functions (atomic register writes)
  * @{
  */

/**
  * @brief  Set the block transfer count of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Block Block transfer count (in data-width unit, max 0xFFF).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetBlockTransCnt(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Block)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.DBL, DMA0_DBL_BL_Msk, (Block) << DMA0_DBL_BL_Pos);
}

/**
  * @brief  Return the block transfer count of the selected DMA channel.
  * @param  DMAx DMA instance
  * @param  Channel Channel number
  * @return Block transfer count
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlockTransCnt(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return (uint32_t)(READ_BIT(DMAx->CH[Channel].REG.DBL, DMA0_DBL_BL_Msk) >> DMA0_DBL_BL_Pos);
}

/**
  * @brief  Set the source transfer width of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Width Source transfer width (see @ref DMA_LL_EC_DATA_WIDTH).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetSrcTransWidth(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_SDS_Msk, ((Width) << DMA0_CTR_SDS_Pos));
}

/**
  * @brief  Get the source transfer width of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return Source transfer width (see @ref DMA_LL_EC_DATA_WIDTH).
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcTransWidth(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return (uint32_t)(READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_SDS_Msk) >> DMA0_CTR_SDS_Pos);
}

/**
  * @brief  Get the source transfer width ( in bytes) of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return Source transfer width in bytes
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcTransWidthBytes(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    uint32_t code = (uint32_t)(READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_SDS_Msk) >> DMA0_CTR_SDS_Pos);

    return (uint32_t)((code <= LL_DMA_DATA_WIDTH_WORD) ? (1UL << code) : (0UL));
}

/**
  * @brief  Set the destination transfer width of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Width Destination transfer width (see @ref DMA_LL_EC_DATA_WIDTH).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetDstTransWidth(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Width)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_DDS_Msk, ((Width) << DMA0_CTR_DDS_Pos));
}

/**
  * @brief  Get the destination transfer width of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return Destination transfer width (see @ref DMA_LL_EC_DATA_WIDTH).
  */
__STATIC_INLINE uint32_t LL_DMA_GetDstTransWidth(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return (uint32_t)(READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_DDS_Msk) >> DMA0_CTR_DDS_Pos);
}

/**
  * @brief  Get the destination transfer width ( in bytes) of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return Destination transfer width in bytes
  */
__STATIC_INLINE uint32_t LL_DMA_GetDstTransWidthBytes(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    uint32_t code = (uint32_t)(READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_DDS_Msk) >> DMA0_CTR_DDS_Pos);

    return (uint32_t)((code <= LL_DMA_DATA_WIDTH_WORD) ? (1UL << code) : (0UL));
}

/**
  * @brief  Set the transfer type of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Type Transfer type (see @ref DMA_LL_EC_TRANS_TYPE).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetTransType(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Type)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_TC_Msk, ((Type) << DMA0_CTR_TC_Pos));
}

/**
  * @brief  Set the transfer mode of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Mode Transfer mode (see @ref DMA_LL_EC_TRANS_MODE).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_TM_Msk, ((Mode) << DMA0_CTR_TM_Pos));
}

/**
  * @brief  Get the transfer mode of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return Transfer mode (see @ref DMA_LL_EC_TRANS_MODE).
  */
__STATIC_INLINE uint32_t LL_DMA_GetMode(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return (uint32_t)(READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_TM_Msk) >> DMA0_CTR_TM_Pos);
}

/**
  * @brief  Set the source address mode of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Mode Address mode (see @ref DMA_LL_EC_ADDR_MODE).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetSrcAddrMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_SAI_Msk, ((Mode) << DMA0_CTR_SAI_Pos));
}

/**
  * @brief  Set the destination address mode of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Mode Address mode (see @ref DMA_LL_EC_ADDR_MODE).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetDstAddrMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_DAI_Msk, ((Mode) << DMA0_CTR_DAI_Pos));
}

/**
  * @brief  Set the source burst length of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Burst Source burst length (see @ref DMA_LL_EC_BURST_LEN).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetSrcBurstLen(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Burst)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_SBL_Msk, ((Burst) << DMA0_CTR_SBL_Pos));
}

/**
  * @brief  Set the destination burst length of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Burst Destination burst length (see @ref DMA_LL_EC_BURST_LEN).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetDstBurstLen(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Burst)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_DBL_Msk, ((Burst) << DMA0_CTR_DBL_Pos));
}

/**
  * @brief  Set the source peripheral bus of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Bus Source peripheral bus (see @ref DMA_LL_EC_PERIPH_BUS).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetSrcPeriphBus(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Bus)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_SMS_Msk, ((Bus) << DMA0_CTR_SMS_Pos));
}

/**
  * @brief  Set the destination peripheral bus of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Bus Destination peripheral bus (see @ref DMA_LL_EC_PERIPH_BUS).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetDstPeriphBus(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Bus)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_DMS_Msk, ((Bus) << DMA0_CTR_DMS_Pos));
}

/**
  * @brief  Set the priority of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Priority Channel priority (see @ref DMA_LL_EC_PRIORITY).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetChannelPriorityLevel(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Priority)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_PRI_Msk, ((Priority) << DMA0_CTR_PRI_Pos));
}

/**
  * @brief  Get the priority of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return Channel priority (see @ref DMA_LL_EC_PRIORITY).
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelPriorityLevel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return (uint32_t)(READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_PRI_Msk) >> DMA0_CTR_PRI_Pos);
}

/**
  * @brief  Set the source handshake interface of the specified DMA channel.
  * @note   Only the low 5 bits are written to the hardware field; the higher
  *         bits of the handshake interface value are used by the HAL layer to
  *         configure external/GPR mux routing.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Ifc Source handshake interface (see @ref DMA_LL_EC_HS_IFC).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetSrcHandshakeIfc(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Ifc)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_SHF_Msk, ((Ifc & 0x1FUL) << DMA0_CTR_SHF_Pos));
}

/**
  * @brief  Set the destination handshake interface of the specified DMA channel.
  * @note   Only the low 5 bits are written to the hardware field; the higher
  *         bits of the handshake interface value are used by the HAL layer to
  *         configure external/GPR mux routing.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Ifc Destination handshake interface (see @ref DMA_LL_EC_HS_IFC).
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetDstHandshakeIfc(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Ifc)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    MODIFY_REG(DMAx->CH[Channel].REG.CTR, DMA0_CTR_DHF_Msk, ((Ifc & 0x1FUL) << DMA0_CTR_DHF_Pos));
}

/**
  * @brief  Set the source address of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Addr Source address.
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetSrcAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    WRITE_REG(DMAx->CH[Channel].REG.SAR, (Addr));
}

/**
  * @brief  Return the source address of the selected DMA channel.
  * @param  DMAx DMA instance
  * @param  Channel Channel number
  * @return Source address
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcAddress(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return READ_REG(DMAx->CH[Channel].REG.SAR);
}

/**
  * @brief  Set the destination address of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @param  Addr Destination address.
  * @return None
  */
__STATIC_INLINE void LL_DMA_SetDstAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    WRITE_REG(DMAx->CH[Channel].REG.DAR, (Addr));
}

/**
  * @brief  Return the destination address of the selected DMA channel.
  * @param  DMAx DMA instance
  * @param  Channel Channel number
  * @return Destination address
  */
__STATIC_INLINE uint32_t LL_DMA_GetDstAddress(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return READ_REG(DMAx->CH[Channel].REG.DAR);
}

/**
  * @}
  */

/** @defgroup DMA_LL_EF_IT_Management DMA Interrupt Enable Functions
  * @brief    These enable the DMA interrupt request line (CTR.CIE/HCIE/EIE).
  *           The matching events are latched in the per-channel STR status
  *           word (CS/HS/ES) and are cleared by writing 1; use the flag
  *           management functions below to read and clear them.
  * @{
  */

/**
  * @brief  Enable the transfer complete interrupt of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_EnableIT_CIE(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    SET_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_CIE_Msk);
}

/**
  * @brief  Disable the transfer complete interrupt of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_DisableIT_CIE(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    CLEAR_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_CIE_Msk);
}

/**
  * @brief  Check if the DMA CS interrupt is enabled.
  * @param  DMAx DMA instance
  * @param  Channel Channel number
  * @return 1 if enabled, 0 otherwise
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_CIE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_CIE_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Enable the transfer error interrupt of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_EnableIT_EIE(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    SET_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_EIE_Msk);
}

/**
  * @brief  Disable the transfer error interrupt of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_DisableIT_EIE(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    CLEAR_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_EIE_Msk);
}

/**
  * @brief  Check if the DMA ES interrupt is enabled.
  * @param  DMAx DMA instance
  * @param  Channel Channel number
  * @return 1 if enabled, 0 otherwise
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_EIE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_EIE_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Enable the transfer half-complete interrupt of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_EnableIT_HCIE(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    SET_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_HCIE_Msk);
}

/**
  * @brief  Disable the transfer half-complete interrupt of the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_DisableIT_HCIE(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    CLEAR_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_HCIE_Msk);
}

/**
  * @brief  Check if the DMA HS interrupt is enabled.
  * @param  DMAx DMA instance
  * @param  Channel Channel number
  * @return 1 if enabled, 0 otherwise
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_HCIE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.CTR, DMA0_CTR_HCIE_Msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  DMA Interrupt All Enable Get
  * @param  DMAx Specifies DMA peripheral
  * @param  Channel Channel number
  * @return Interrupt Enable Bit
  */
__STATIC_INLINE uint32_t LL_DMA_GetAllEnabledIT(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return (READ_BIT(DMAx->CH[Channel].REG.CTR, LL_DMA_CTR_IT_EN_MSK));
}

/**
  * @brief  DMA All Interrupt enable
  * @param  DMAx Specifies DMA peripheral
  * @param  Channel Channel number
  * @return None
  */
__STATIC_INLINE void LL_DMA_EnableAllIT(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    SET_BIT(DMAx->CH[Channel].REG.CTR, LL_DMA_CTR_IT_EN_MSK);
}

/**
  * @brief  DMA All Interrupt disable
  * @param  DMAx Specifies DMA peripheral
  * @param  Channel Channel number
  * @return None
  */
__STATIC_INLINE void LL_DMA_DisableAllIT(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    CLEAR_BIT(DMAx->CH[Channel].REG.CTR, LL_DMA_CTR_IT_EN_MSK);
}

/**
  * @brief  DMA Interrupt enable
  * @param  DMAx Specifies DMA peripheral
  * @param  Channel Channel number
  * @param  Mask Mask to enable @ref LL_DMA_CTR_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DMA_EnableIT(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    SET_BIT(DMAx->CH[Channel].REG.CTR, Mask & LL_DMA_CTR_IT_EN_MSK);
}

/**
  * @brief  DMA Interrupt disable
  * @param  DMAx Specifies DMA peripheral
  * @param  Channel Channel number
  * @param  Mask Mask to disable @ref LL_DMA_CTR_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_DMA_DisableIT(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    CLEAR_BIT(DMAx->CH[Channel].REG.CTR, Mask & LL_DMA_CTR_IT_EN_MSK);
}

/**
  * @brief  Check whether the specified DMA channel is busy transferring.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @retval 0 if not busy, 1 if busy.
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_BUSY(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.STR, DMA0_STR_BUSY_Msk) == DMA0_STR_BUSY_Msk) ? 1UL : 0UL);
}

/**
  * @brief  Check whether a transfer error is pending on the specified DMA channel.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @retval 0 if no error, 1 if error.
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_ES(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.STR, DMA0_STR_ES_Msk) == DMA0_STR_ES_Msk) ? 1UL : 0UL);
}

/**
  * @brief  Check whether a transfer complete event is pending on the specified
  *         DMA channel.
  * @note   STR.CS is a write-1-to-clear interrupt status bit; call
  *         LL_DMA_ClearFlag_CS() once the event has been handled.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @retval 0 if no completion pending, 1 if completion pending.
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_CS(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.STR, DMA0_STR_CS_Msk) == DMA0_STR_CS_Msk) ? 1UL : 0UL);
}

/**
  * @brief  Check whether a half transfer complete event is pending on the
  *         specified DMA channel.
  * @note   STR.HS is a write-1-to-clear interrupt status bit; call
  *         LL_DMA_ClearFlag_HS() once the event has been handled.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @retval 0 if no half completion pending, 1 if half completion pending.
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HS(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return ((READ_BIT(DMAx->CH[Channel].REG.STR, DMA0_STR_HS_Msk) == DMA0_STR_HS_Msk) ? 1UL : 0UL);
}

/**
  * @brief  Clear the transfer complete flag of the specified DMA channel.
  * @note   STR.CS is cleared by writing 1 (R/W1C); writing 0 to the other
  *         status bits leaves them unchanged.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_CS(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    WRITE_REG(DMAx->CH[Channel].REG.STR, DMA0_STR_CS_Msk);
}

/**
  * @brief  Clear the half transfer complete flag of the specified DMA channel.
  * @note   STR.HS is cleared by writing 1 (R/W1C).
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_HS(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    WRITE_REG(DMAx->CH[Channel].REG.STR, DMA0_STR_HS_Msk);
}

/**
  * @brief  Clear the transfer error flag of the specified DMA channel.
  * @note   STR.ES is cleared by writing 1 (R/W1C).
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_ClearFlag_ES(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    WRITE_REG(DMAx->CH[Channel].REG.STR, DMA0_STR_ES_Msk);
}

/**
  * @brief  Get interrupt status of the specified DMA channel 
  * @param  DMAx Specifies DMA peripheral
  * @param  Channel DMA channel index.
  * @return Interrupt status
  */
__STATIC_INLINE uint32_t LL_DMA_GetAllITPending(const DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    return (READ_BIT(DMAx->CH[Channel].REG.STR, LL_DMA_STR_IT_FLAG_MSK));
}

/**
  * @brief  Clear all the status flags of the specified DMA channel.
  * @note   STR.CS/HS/ES are write-1-to-clear bits.
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return None
  */
__STATIC_INLINE void LL_DMA_ClearAllFlags(DMA_TypeDef *DMAx, uint32_t Channel)
{
    ASSERT_INLINE_PARAM(IS_DMA_ALL_INSTANCE(DMAx));

    WRITE_REG(DMAx->CH[Channel].REG.STR, LL_DMA_STR_IT_FLAG_MSK);
}

/**
  * @}
  */ /* DMA_LL_EF_IT_Management */

/**
  * @}
  */ /* DMA_LL_Exported_Functions */

/**
  * @}
  */ /* DMA_LL */

#endif /* DMA */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_DMA_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
