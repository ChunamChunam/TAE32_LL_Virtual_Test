/**
  ******************************************************************************
  * @file    tae32g58xx_hal_dma.c
  * @author  Tai-Action SD Team
  * @brief   DMA HAL module driver.
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

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_hal.h"

#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_DMA_MODULE_ENABLED) && (HAL_DMA_MODULE_ENABLED == 1)

/** @addtogroup TAE32G58xx_HAL_Driver
  * @{
  */

/** @defgroup DMA_HAL Hardware Abstraction Layer
  * @brief HAL layer driver for DMA module.
  * @{
  */

/* Private Typedef -----------------------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/
/** @defgroup DMA_HAL_Private_Constants DMA HAL Private Constants
  * @brief    DMA HAL Private Constants
  * @{
  */

/**
  * @brief  Default timeout value used by blocking DMA operations.
  * @note   The timeout is expressed in milliseconds. It is used, for example,
  *         when waiting for the DMA to be enabled or disabled, or when waiting
  *         for a conversion to start or stop.
  */
#define DMA_DEFAULT_TIMEOUT         (10)

/**
  * @}
  */ /* DMA_HAL_Private_Constants */

/* Private Macro -------------------------------------------------------------*/
/** @brief DMA_HAL_Private_Macros DMA HAL Private Macros
  * @{
  */

#define IS_DMA_TRANS_DIRECTION(__VAL__)                     (((__VAL__) == HAL_DMA_TRANS_TYPE_M2M) || \
                                                             ((__VAL__) == HAL_DMA_TRANS_TYPE_M2P) || \
                                                             ((__VAL__) == HAL_DMA_TRANS_TYPE_P2M) || \
                                                             ((__VAL__) == HAL_DMA_TRANS_TYPE_P2P))

#define IS_DMA_PERIPH_ADDR_MODE(__VAL__)                    (((__VAL__) == HAL_DMA_ADDR_MODE_INC) || \
                                                             ((__VAL__) == HAL_DMA_ADDR_MODE_FIX))

#define IS_DMA_MEM_ADDR_MODE(__VAL__)                       (((__VAL__) == HAL_DMA_ADDR_MODE_INC) || \
                                                             ((__VAL__) == HAL_DMA_ADDR_MODE_FIX))

#define IS_DMA_PERIPH_DATA_ALIGN(__VAL__)                   (((__VAL__) == HAL_DMA_DATA_WIDTH_BYTE) || \
                                                             ((__VAL__) == HAL_DMA_DATA_WIDTH_HALFWORD) || \
                                                             ((__VAL__) == HAL_DMA_DATA_WIDTH_WORD))

#define IS_DMA_MEM_DATA_ALIGN(__VAL__)                      (((__VAL__) == HAL_DMA_DATA_WIDTH_BYTE) || \
                                                             ((__VAL__) == HAL_DMA_DATA_WIDTH_HALFWORD) || \
                                                             ((__VAL__) == HAL_DMA_DATA_WIDTH_WORD))

#define IS_DMA_TRANS_MODE(__VAL__)                          (((__VAL__) == HAL_DMA_TRANS_MODE_SINGLE) || \
                                                             ((__VAL__) == HAL_DMA_TRANS_MODE_CONTINUE))

#define IS_DMA_PRIORITY(__VAL__)                            (((__VAL__) >= HAL_DMA_PRIORITY_LEVEL_0) && \
                                                             ((__VAL__) <= HAL_DMA_PRIORITY_LEVEL_7))

#define IS_DMA_CHANNEL_CONFIG(__VAL__)                      ((((__VAL__) >= HAL_DMA_CHANNEL_0) && ((__VAL__) <= HAL_DMA_CHANNEL_5)) || \
                                                             ((__VAL__) == HAL_DMA_CHANNEL_INVALID))

#define IS_DMA_VALID_CHANNEL(__VAL__)                       ((((__VAL__) >= HAL_DMA_CHANNEL_0) && ((__VAL__) <= HAL_DMA_CHANNEL_5)))

#define IS_DMA_BURST_LEN(__VAL__)                           (((__VAL__) == HAL_DMA_BURST_LEN_1) || \
                                                             ((__VAL__) == HAL_DMA_BURST_LEN_4) || \
                                                             ((__VAL__) == HAL_DMA_BURST_LEN_8) || \
                                                             ((__VAL__) == HAL_DMA_BURST_LEN_16))

#define IS_DMA_PERIPH_BUS(__VAL__)                          (((__VAL__) == HAL_DMA_PERIPH_BUS_AHB_MST1) || \
                                                             ((__VAL__) == HAL_DMA_PERIPH_BUS_AHB_MST2)) 

#define IS_DMA_HS_IFC(__VAL__)                              (((__VAL__) == HAL_DMA_HS_IFC_MEM)           || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_I2C0_TX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_I2C0_RX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_I2C1_TX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_I2C1_RX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_I2C2_TX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_I2C2_RX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART0_TX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART0_RX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART1_TX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART1_RX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART2_TX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART2_RX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART3_TX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART3_RX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART4_TX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_UART4_RX)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_SPI0_TX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_SPI0_RX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_SPI1_TX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_SPI1_RX)       || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_XIF_TX)        || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_XIF_RX)        || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV7)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV6)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV5)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV4)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV3)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV2)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV1)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_SLV0)    || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_HRPWM_MST)     || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_ADC3)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_ADC2)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_ADC1)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_ADC0)      || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_PDM0_RX)   || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_PDM1_RX)   || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_PDM2_RX)   || \
                                                             ((__VAL__) == HAL_DMA_HS_IFC_MUX_PDM3_RX))

#define IS_DMA_COMPLETE_LEVEL(__VAL__)                      (((__VAL__) == HAL_DMA_FULL_TRANSFER) || \
                                                             ((__VAL__) == HAL_DMA_HALF_TRANSFER))

/**
  * @}
  */

/* Private Variables ---------------------------------------------------------*/
/** @brief  DMA handle database, indexed by channel, used for IRQ lookup. */
static HAL_DMA_HandleTypeDef *DMA_Handle[LL_DMA_CHANNEL_NUMS] = {NULL};

/* Private Function Prototypes -----------------------------------------------*/
static HAL_StatusTypeDef DMA_ChannelReset(DMA_TypeDef *DMAx, uint32_t Channel);
static uint32_t DMA_AllocateChannel(uint32_t PreferredChannel);


/* Exported Functions --------------------------------------------------------*/
/** @defgroup DMA_HAL_Exported_Functions DMA HAL Exported Functions
  * @{
  */

/** @defgroup DMA_HAL_EF_Configuration DMA HAL Configuration Functions
  * @brief    DMA HAL configuration functions
  * @{
  */

/**
  * @brief  Initialize the DMA peripheral according to the specified parameters
  *         in the HAL_DMA_InitTypeDef structure.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @param  DMAx Pointer to the DMA peripheral instance.
  * @param  pInit Pointer to a HAL_DMA_InitTypeDef structure that contains
  *              the configuration parameters.
  * @return HAL status
  */
  HAL_StatusTypeDef HAL_DMA_Init(HAL_DMA_HandleTypeDef *hdma, 
                                 DMA_TypeDef *DMAx,
                                 HAL_DMA_InitTypeDef *pInit)
{
    uint32_t ch;
    uint32_t src_width;
    uint32_t dst_width;

    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(DMAx));
    ASSERT_FUNC_PARAM(pInit != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_CHANNEL_CONFIG(pInit->Channel));
    ASSERT_FUNC_PARAM(IS_DMA_TRANS_DIRECTION(pInit->Direction));
    ASSERT_FUNC_PARAM(IS_DMA_PERIPH_ADDR_MODE(pInit->PeriphInc));
    ASSERT_FUNC_PARAM(IS_DMA_MEM_ADDR_MODE(pInit->MemInc));
    ASSERT_FUNC_PARAM(IS_DMA_PERIPH_DATA_ALIGN(pInit->PeriphDataAlignment));
    ASSERT_FUNC_PARAM(IS_DMA_MEM_DATA_ALIGN(pInit->MemDataAlignment));
    ASSERT_FUNC_PARAM(IS_DMA_TRANS_MODE(pInit->Mode));
    ASSERT_FUNC_PARAM(IS_DMA_PRIORITY(pInit->Priority));
    ASSERT_FUNC_PARAM(IS_DMA_BURST_LEN(pInit->SrcBurstLen));
    ASSERT_FUNC_PARAM(IS_DMA_BURST_LEN(pInit->DstBurstLen));
    ASSERT_FUNC_PARAM(IS_DMA_PERIPH_BUS(pInit->SrcPeriphBus));
    ASSERT_FUNC_PARAM(IS_DMA_PERIPH_BUS(pInit->DstPeriphBus));
    ASSERT_FUNC_PARAM(IS_DMA_HS_IFC(pInit->SrcHandshakeIfc));
    ASSERT_FUNC_PARAM(IS_DMA_HS_IFC(pInit->DstHandshakeIfc));

    HAL_DMA_PARAM_CHECK({
        if ((pInit == NULL)                                          ||
            (!IS_DMA_CHANNEL_CONFIG(pInit->Channel))                 ||
            (!IS_DMA_TRANS_DIRECTION(pInit->Direction))              ||
            (!IS_DMA_PERIPH_ADDR_MODE(pInit->PeriphInc))             ||
            (!IS_DMA_MEM_ADDR_MODE(pInit->MemInc))                   ||
            (!IS_DMA_PERIPH_DATA_ALIGN(pInit->PeriphDataAlignment))  ||
            (!IS_DMA_MEM_DATA_ALIGN(pInit->MemDataAlignment))        ||
            (!IS_DMA_TRANS_MODE(pInit->Mode))                        ||
            (!IS_DMA_PRIORITY(pInit->Priority))                      ||
            (!IS_DMA_BURST_LEN(pInit->SrcBurstLen))                  ||
            (!IS_DMA_BURST_LEN(pInit->DstBurstLen))                  ||
            (!IS_DMA_PERIPH_BUS(pInit->SrcPeriphBus))                ||
            (!IS_DMA_PERIPH_BUS(pInit->DstPeriphBus))                ||
            (!IS_DMA_HS_IFC(pInit->SrcHandshakeIfc))                 ||
            (!IS_DMA_HS_IFC(pInit->DstHandshakeIfc))) {
                return HAL_INVALID;
        }
    });

     /* Check NULL pointers */
    if ((hdma == NULL) || (pInit == NULL)) {
        return HAL_INVALID;
    }

    /* Check Instance validity */
    if (!IS_DMA_ALL_INSTANCE(DMAx)) {
        return HAL_INVALID;
    }


    /* Bind the instance passed by the caller */
    hdma->Instance = DMAx;
    hdma->Channel = HAL_DMA_CHANNEL_INVALID;

    /* Default callback */
    hdma->XferHalfCpltCallback = HAL_DMA_XferHalfCpltCallback;
    hdma->XferCpltCallback     = HAL_DMA_XferCpltCallback;
    hdma->XferAbortCallback    = HAL_DMA_XferAbortCallback;
    hdma->XferErrorCallback    = HAL_DMA_XferErrorCallback;

    /* MSP initialization (clock, NVIC, ...) */
    HAL_DMA_MspInit(hdma);

    /* Allocate a channel (auto or specific) */
    ch = DMA_AllocateChannel(pInit->Channel);
    if ((ch == HAL_DMA_CHANNEL_INVALID) || (ch >= HAL_DMA_CHANNEL_NUMS)) {
        return HAL_FAILED;
    }

    /* Retain the resolved channel for later Start/Abort/IRQ operations */
    hdma->Channel = ch;
    DMA_Handle[ch] = hdma;

    /* Reset the channel registers */
    if (DMA_ChannelReset(hdma->Instance, ch) != HAL_OK) {
        hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

        if (DMA_Handle[ch] == hdma) {
            DMA_Handle[ch] = NULL;
        }

        hdma->Channel = HAL_DMA_CHANNEL_INVALID;
        hdma->State = HAL_DMA_STATE_RESET;
        return HAL_ERROR;
    }

    /* Transfer type and mode */
    LL_DMA_SetTransType(hdma->Instance, ch, pInit->Direction);
    LL_DMA_SetMode(hdma->Instance, ch, pInit->Mode);

    /* Derive source / destination address mode and data width from the
       Periph/Mem role fields, based on transfer direction. */
    if (pInit->Direction == HAL_DMA_TRANS_TYPE_M2P) {
        LL_DMA_SetSrcAddrMode(hdma->Instance, ch, pInit->MemInc);
        LL_DMA_SetDstAddrMode(hdma->Instance, ch, pInit->PeriphInc);
        src_width = pInit->MemDataAlignment;
        dst_width = pInit->PeriphDataAlignment;
    } else if (pInit->Direction == HAL_DMA_TRANS_TYPE_P2M) {
        LL_DMA_SetSrcAddrMode(hdma->Instance, ch, pInit->PeriphInc);
        LL_DMA_SetDstAddrMode(hdma->Instance, ch, pInit->MemInc);
        src_width = pInit->PeriphDataAlignment;
        dst_width = pInit->MemDataAlignment;
    } else if (pInit->Direction == HAL_DMA_TRANS_TYPE_M2M) {
        LL_DMA_SetSrcAddrMode(hdma->Instance, ch, pInit->MemInc);
        LL_DMA_SetDstAddrMode(hdma->Instance, ch, pInit->MemInc);
        src_width = pInit->MemDataAlignment;
        dst_width = pInit->MemDataAlignment;
    } else { /* HAL_DMA_TRANS_TYPE_P2P */
        LL_DMA_SetSrcAddrMode(hdma->Instance, ch, pInit->PeriphInc);
        LL_DMA_SetDstAddrMode(hdma->Instance, ch, pInit->PeriphInc);
        src_width = pInit->PeriphDataAlignment;
        dst_width = pInit->PeriphDataAlignment;
    }

    LL_DMA_SetSrcTransWidth(hdma->Instance, ch, src_width);
    LL_DMA_SetDstTransWidth(hdma->Instance, ch, dst_width);

    /* Burst length and peripheral bus */
    LL_DMA_SetSrcBurstLen(hdma->Instance, ch, pInit->SrcBurstLen);
    LL_DMA_SetDstBurstLen(hdma->Instance, ch, pInit->DstBurstLen);
    LL_DMA_SetSrcPeriphBus(hdma->Instance, ch, pInit->SrcPeriphBus);
    LL_DMA_SetDstPeriphBus(hdma->Instance, ch, pInit->DstPeriphBus);
    LL_DMA_SetChannelPriorityLevel(hdma->Instance, ch, pInit->Priority);

    /* Handshake interface */
    if (pInit->SrcHandshakeIfc != HAL_DMA_HS_IFC_MEM) {
        if (pInit->SrcIfcMuxEnable == HAL_DMA_IFS_MUX_ENABLE) {
            HAL_SYSCTRL_SetDMARequestConfig(HAL_SYSCTRL_DMA_HS_IFS_NUM_TO_MASK(pInit->SrcHandshakeIfc));
        } else {
            HAL_SYSCTRL_ResetDMARequestConfig(HAL_SYSCTRL_DMA_HS_IFS_NUM_TO_MASK(pInit->SrcHandshakeIfc));
        }

        LL_DMA_SetSrcHandshakeIfc(hdma->Instance, ch, pInit->SrcHandshakeIfc);
    }

    if (pInit->DstHandshakeIfc != HAL_DMA_HS_IFC_MEM) {
        if (pInit->DstIfcMuxEnable == HAL_DMA_IFS_MUX_ENABLE) {
            HAL_SYSCTRL_SetDMARequestConfig(HAL_SYSCTRL_DMA_HS_IFS_NUM_TO_MASK(pInit->DstHandshakeIfc));
        } else {
            HAL_SYSCTRL_ResetDMARequestConfig(HAL_SYSCTRL_DMA_HS_IFS_NUM_TO_MASK(pInit->DstHandshakeIfc));
        }

        LL_DMA_SetDstHandshakeIfc(hdma->Instance, ch, pInit->DstHandshakeIfc);
    }

    hdma->State     = HAL_DMA_STATE_READY;
    hdma->ErrorCode = HAL_DMA_ERROR_NONE;

    return HAL_OK;
}

/**
  * @brief  De-initialize the DMA peripheral registers to their default reset
  *         values and release the channel.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_DeInit(HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));

    HAL_DMA_PARAM_CHECK({
        if (((hdma == NULL)) || (!IS_DMA_ALL_INSTANCE(hdma->Instance))) {
            return HAL_INVALID;
        }
    });

    const uint32_t ch = hdma->Channel;

    /* Release the channel from the handle database */
    if ((ch < LL_DMA_CHANNEL_NUMS) && (DMA_Handle[ch] == hdma)) {
        (void) DMA_ChannelReset(hdma->Instance, ch);
        DMA_Handle[ch] = NULL;
    }

    /* MSP de-initialization */
    HAL_DMA_MspDeInit(hdma);

    hdma->XferHalfCpltCallback = NULL;
    hdma->XferCpltCallback     = NULL;
    hdma->XferAbortCallback    = NULL;
    hdma->XferErrorCallback    = NULL;

    hdma->Channel   = HAL_DMA_CHANNEL_INVALID;
    hdma->State     = HAL_DMA_STATE_RESET;
    hdma->ErrorCode = HAL_DMA_ERROR_NONE;
    return HAL_OK;
}

/**
  * @brief  Start the DMA transfer in polling mode (no interrupt).
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @param  SrcAddress Source address.
  * @param  DstAddress Destination address.
  * @param  DataLength Total transfer length in bytes.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_Start(HAL_DMA_HandleTypeDef *hdma, uint32_t SrcAddress,
                                uint32_t DstAddress, uint32_t DataLength)
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM(IS_DMA_VALID_CHANNEL(hdma->Channel));

    HAL_DMA_PARAM_CHECK({
        if ((hdma == NULL)                          || 
            (!IS_DMA_ALL_INSTANCE(hdma->Instance))  || 
            (!IS_DMA_VALID_CHANNEL(hdma->Channel))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hdma->State, HAL_DMA_STATE_READY);

    const uint32_t ch = hdma->Channel;
    uint32_t src_width_bytes, dst_width_bytes;
    uint32_t block_size;

    if (hdma->State != HAL_DMA_STATE_READY) {
        return HAL_BUSY;
    }

    if (DataLength == 0U) {
        return HAL_INVALID;
    }

    src_width_bytes = LL_DMA_GetSrcTransWidthBytes(hdma->Instance, ch);
    if (src_width_bytes == 0U) { 
        return HAL_INVALID;
    }

    HAL_DMA_PARAM_CHECK({
        if ((SrcAddress % src_width_bytes) != 0U) {
            return HAL_INVALID;
        } 

    });

    dst_width_bytes = LL_DMA_GetDstTransWidthBytes(hdma->Instance, ch);
    if (dst_width_bytes == 0U) {
        return HAL_INVALID;
    }

    HAL_DMA_PARAM_CHECK({
        if ((DstAddress % dst_width_bytes) != 0U) {
            return HAL_INVALID;
        } 

        if (src_width_bytes != dst_width_bytes) {
            return HAL_INVALID;
        } 
    });

    if ((DataLength % src_width_bytes) != 0U) {
        return HAL_INVALID;
    }        


    block_size = DataLength / src_width_bytes;
    HAL_DMA_PARAM_CHECK({
        if (block_size > LL_DMA_BLOCK_SIZE_MAX) {
            return HAL_INVALID;
        }
    });

    HAL_DMA_PARAM_UPDATE(hdma->State, HAL_DMA_STATE_READY, HAL_DMA_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Polling mode: make sure the interrupt request line is masked and no
       stale status is latched, otherwise a pending CS/HS/ES would still
       raise the channel interrupt. */
    LL_DMA_DisableIT_CIE(hdma->Instance, ch);
    LL_DMA_DisableIT_HCIE(hdma->Instance, ch);
    LL_DMA_DisableIT_EIE(hdma->Instance, ch);
    LL_DMA_ClearAllFlags(hdma->Instance, ch);

    /* Configure source / destination address and block size */
    LL_DMA_SetSrcAddress(hdma->Instance, ch, SrcAddress);
    LL_DMA_SetDstAddress(hdma->Instance, ch, DstAddress);
    LL_DMA_SetBlockTransCnt(hdma->Instance, ch, block_size);

    hdma->State = HAL_DMA_STATE_BUSY;

    /* Enable the channel */
    LL_DMA_EnableChannel(hdma->Instance, ch);

    return HAL_OK;
}

/**
  * @brief  Start the DMA transfer in interrupt mode.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @param  SrcAddress Source address.
  * @param  DstAddress Destination address.
  * @param  DataLength Total transfer length in bytes.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_Start_IT(HAL_DMA_HandleTypeDef *hdma, uint32_t SrcAddress,
                                   uint32_t DstAddress, uint32_t DataLength)
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM(IS_DMA_VALID_CHANNEL(hdma->Channel));

    HAL_DMA_PARAM_CHECK({
        if ((hdma == NULL)                          || 
            (!IS_DMA_ALL_INSTANCE(hdma->Instance))  || 
            (!IS_DMA_VALID_CHANNEL(hdma->Channel))) {
            return HAL_INVALID;
        }
    });

    ASSERT_FUNC_STATE(hdma->State, HAL_DMA_STATE_READY);

    const uint32_t ch = hdma->Channel;
    uint32_t src_width_bytes, dst_width_bytes;
    uint32_t block_size;

    if (hdma->State != HAL_DMA_STATE_READY) {
        return HAL_BUSY;
    }

    if (DataLength == 0U) {

        return HAL_INVALID;
    }

    src_width_bytes = LL_DMA_GetSrcTransWidthBytes(hdma->Instance, ch);
    if (src_width_bytes == 0U) { 
        return HAL_INVALID;
    }

    HAL_DMA_PARAM_CHECK({
        if ((SrcAddress % src_width_bytes) != 0U) {
            return HAL_INVALID;
        } 

    });

    dst_width_bytes = LL_DMA_GetDstTransWidthBytes(hdma->Instance, ch);
    if (dst_width_bytes == 0U) {
        return HAL_INVALID;
    }

    HAL_DMA_PARAM_CHECK({
        if ((DstAddress % dst_width_bytes) != 0U) {
            return HAL_INVALID;
        } 

        if (src_width_bytes != dst_width_bytes) {
            return HAL_INVALID;
        } 
    });


    if ((DataLength % src_width_bytes) != 0U) {
        return HAL_INVALID;
    }        


    block_size = DataLength / src_width_bytes;
    HAL_DMA_PARAM_CHECK({
        if (block_size > LL_DMA_BLOCK_SIZE_MAX) {
            return HAL_INVALID;
        }
    });

    HAL_DMA_PARAM_UPDATE(hdma->State, HAL_DMA_STATE_READY, HAL_DMA_STATE_BUSY, {
        return HAL_BUSY;
    });

    /* Clear the latched status of any previous transfer before enabling the
       interrupt request line */
    LL_DMA_ClearAllFlags(hdma->Instance, ch);

    /* HCIE is enabled only when a half-complete callback has been registered, 
       so that a transfer never raises the half-transfer interrupt needlessly. */
    LL_DMA_EnableIT_CIE(hdma->Instance, ch);
    LL_DMA_EnableIT_EIE(hdma->Instance, ch);
    if (hdma->XferHalfCpltCallback != NULL) {
        LL_DMA_EnableIT_HCIE(hdma->Instance, ch);
    } else {
        LL_DMA_DisableIT_HCIE(hdma->Instance, ch);
    }

    /* Configure source / destination address and block size */
    LL_DMA_SetSrcAddress(hdma->Instance, ch, SrcAddress);
    LL_DMA_SetDstAddress(hdma->Instance, ch, DstAddress);
    LL_DMA_SetBlockTransCnt(hdma->Instance, ch, block_size);

    /* Enable the channel */
    LL_DMA_EnableChannel(hdma->Instance, ch);

    return HAL_OK;
}

/**
  * @brief  Abort the DMA transfer in polling mode.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_Abort(HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM(IS_DMA_VALID_CHANNEL(hdma->Channel));

    HAL_DMA_PARAM_CHECK({
        if ((hdma == NULL)                          || 
            (!IS_DMA_ALL_INSTANCE(hdma->Instance))  || 
            (!IS_DMA_VALID_CHANNEL(hdma->Channel))) {
            return HAL_INVALID;
        }
    });

    const uint32_t ch = hdma->Channel;

    /* Disable the channel and mask the interrupt request line: masking the
       enables plus clearing the pending status guarantees the channel can no
       longer raise an interrupt after the abort. */
    LL_DMA_DisableChannel(hdma->Instance, ch);
    LL_DMA_DisableAllIT(hdma->Instance, ch);
    LL_DMA_ClearAllFlags(hdma->Instance, ch);

    hdma->State = HAL_DMA_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Abort the DMA transfer in interrupt mode.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_Abort_IT(HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM(IS_DMA_VALID_CHANNEL(hdma->Channel));

    HAL_DMA_PARAM_CHECK({
        if ((hdma == NULL)                          || 
            (!IS_DMA_ALL_INSTANCE(hdma->Instance))  || 
            (!IS_DMA_VALID_CHANNEL(hdma->Channel))) {
            return HAL_INVALID;
        }
    });

    const uint32_t ch = hdma->Channel;

    /* Disable the channel and disable interrupts */
    LL_DMA_DisableChannel(hdma->Instance, ch);
    LL_DMA_DisableAllIT(hdma->Instance, ch);
    LL_DMA_ClearAllFlags(hdma->Instance, ch);

    hdma->State = HAL_DMA_STATE_READY;

    /* Notify the completion of the abort sequence */
    if (hdma->XferAbortCallback != NULL) {
        hdma->XferAbortCallback(hdma);
    } else {
        HAL_DMA_XferAbortCallback(hdma);
    }

    return HAL_OK;
}

/**
  * @brief  Poll for DMA transfer complete.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @param  CompleteLevel Specifies the DMA level complete (HAL_DMA_FULL_TRANSFER / HAL_DMA_HALF_TRANSFER).
  * @param  Timeout Timeout duration in millisecond.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_PollForTransfer(HAL_DMA_HandleTypeDef *hdma, uint32_t CompleteLevel,
                                          uint32_t Timeout)
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM(IS_DMA_VALID_CHANNEL(hdma->Channel));
    ASSERT_FUNC_PARAM(IS_DMA_COMPLETE_LEVEL(CompleteLevel));

    HAL_DMA_PARAM_CHECK({
        if ((hdma == NULL)                          || 
            (!IS_DMA_ALL_INSTANCE(hdma->Instance))  || 
            (!IS_DMA_VALID_CHANNEL(hdma->Channel))  ||
            (!IS_DMA_COMPLETE_LEVEL(CompleteLevel))) {
            return HAL_INVALID;
        }
    });

    const uint32_t ch = hdma->Channel;
    uint32_t tickstart = HAL_GetTick();

    if (hdma->State != HAL_DMA_STATE_BUSY) {
        return HAL_FAILED;
    }

    if (CompleteLevel == HAL_DMA_HALF_TRANSFER) {
        /* Wait for the half-transfer event , then clear it so that a following 
           full-transfer poll starts from a clean status. The state is
           left untouched because the transfer is still running. */
        while (LL_DMA_IsActiveFlag_HS(hdma->Instance, ch) == 0U) {
            if (LL_DMA_IsActiveFlag_ES(hdma->Instance, ch) != 0U) {
                hdma->State = HAL_DMA_STATE_ERROR;
                hdma->ErrorCode = HAL_DMA_ERROR_TE;
                return HAL_ERROR;
            }
#if 1///TODO:TEST
            if (LL_DMA_IsActiveFlag_CS(hdma->Instance, ch) != 0U) {
                /* The transmission has been completed. 
                    The HS flag will never be set again. */
                LL_DMA_ClearFlag_CS(hdma->Instance, ch);
                return HAL_OK;
            }
#endif
            if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) > Timeout)) {
                hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;
                return HAL_TIMEOUT;
            }


        }
        LL_DMA_ClearFlag_HS(hdma->Instance, ch);
        return HAL_OK;
    } else if (CompleteLevel == HAL_DMA_FULL_TRANSFER){
        while (LL_DMA_IsActiveFlag_BUSY(hdma->Instance, ch) != 0U) {
            if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) > Timeout)) {
                hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;
                return HAL_TIMEOUT;
            }
        }
    } else {
        return HAL_INVALID;
    }
    

    if (LL_DMA_IsActiveFlag_ES(hdma->Instance, ch) != 0U) {
        hdma->State = HAL_DMA_STATE_ERROR;
        hdma->ErrorCode = HAL_DMA_ERROR_TE;
        return HAL_ERROR;
    }

    hdma->State = HAL_DMA_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  Handle DMA interrupt request.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
void HAL_DMA_IRQHandler(HAL_DMA_HandleTypeDef *hdma)
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(IS_DMA_ALL_INSTANCE(hdma->Instance));
    ASSERT_FUNC_PARAM(IS_DMA_VALID_CHANNEL(hdma->Channel));

    HAL_DMA_PARAM_CHECK({
        if ((hdma == NULL)                          || 
            (!IS_DMA_ALL_INSTANCE(hdma->Instance))  || 
            (!IS_DMA_VALID_CHANNEL(hdma->Channel))) {
            return ;
        }
    });

    const uint32_t ch = hdma->Channel;

    /* Read the currently enabled interrupt sources and the pending flags. */
    const uint32_t int_en = LL_DMA_GetAllEnabledIT(hdma->Instance, ch);
    const uint32_t int_pending = LL_DMA_GetAllITPending(hdma->Instance, ch);

    const uint32_t is_err  = (int_en & LL_DMA_CTR_EIE) && (int_pending & LL_DMA_STR_ES);
    const uint32_t is_half = (int_en & LL_DMA_CTR_HCIE) && (int_pending & LL_DMA_STR_HS);
    const uint32_t is_cplt = (int_en & LL_DMA_CTR_CIE) && (int_pending & LL_DMA_STR_CS);
    
    /* Transfer error */
    if (is_err != 0U) {
        /* Incorrect data will no longer be processed. Clear other interrupt 
        flags to prevent re-entering the interrupt before the error is handled. */
        LL_DMA_ClearAllFlags(hdma->Instance, ch);

        hdma->State = HAL_DMA_STATE_ERROR;
        hdma->ErrorCode = HAL_DMA_ERROR_TE;

        if (hdma->XferErrorCallback != NULL) {
            hdma->XferErrorCallback(hdma);
        }
        return;
    }

    /* Half transfer complete: The transfer is still running, so the
       state is left untouched. */
    if (is_half != 0U) {
        LL_DMA_ClearFlag_HS(hdma->Instance, ch);

        if (hdma->XferHalfCpltCallback != NULL) {
            hdma->XferHalfCpltCallback(hdma);
        }
    }

    /* Transfer complete */
    if (is_cplt != 0U) {
        LL_DMA_ClearFlag_CS(hdma->Instance, ch);

        hdma->State = HAL_DMA_STATE_READY;

        if (hdma->XferCpltCallback != NULL) {
            hdma->XferCpltCallback(hdma);
        }
    }
}

/**
  * @brief  Register a user callback for the specified DMA transfer event.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @param  CallbackID Callback identifier (HAL_DMA_CallbackIDTypeDef).
  * @param  pCallback Pointer to the callback function.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_RegisterCallback(HAL_DMA_HandleTypeDef *hdma,
                                           HAL_DMA_CallbackIDTypeDef CallbackID,
                                           void (*pCallback)(HAL_DMA_HandleTypeDef *))
{
    ASSERT_FUNC_PARAM(hdma != NULL);
    ASSERT_FUNC_PARAM(pCallback != NULL);

    HAL_StatusTypeDef status = HAL_OK;

    HAL_DMA_PARAM_CHECK({
        if ((hdma == NULL) || (pCallback == NULL)) {
            return HAL_INVALID;
        }
    });
    switch (CallbackID) {
        case HAL_DMA_XFER_CPLT_CB_ID:
            hdma->XferCpltCallback = pCallback;
            break;
        case HAL_DMA_XFER_HALFCPLT_CB_ID:
            hdma->XferHalfCpltCallback = pCallback;
            break;
        case HAL_DMA_XFER_ERROR_CB_ID:
            hdma->XferErrorCallback = pCallback;
            break;
        case HAL_DMA_XFER_ABORT_CB_ID:
            hdma->XferAbortCallback = pCallback;
            break;
        case HAL_DMA_XFER_ALL_CB_ID:
            hdma->XferCpltCallback = pCallback;
            hdma->XferHalfCpltCallback = pCallback;
            hdma->XferErrorCallback = pCallback;
            hdma->XferAbortCallback = pCallback;
            break;
        default:
            status = HAL_ERROR;
            break;
    }
    return status;
}

/**
  * @brief  Unregister the DMA callback and restore the default behaviour.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @param  CallbackID Callback identifier.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(HAL_DMA_HandleTypeDef *hdma,
                                             HAL_DMA_CallbackIDTypeDef CallbackID)
{
    HAL_StatusTypeDef status = HAL_OK;

    if (hdma == NULL) {
        return HAL_INVALID;
    }

    switch (CallbackID) {
        case HAL_DMA_XFER_CPLT_CB_ID:
            hdma->XferCpltCallback = NULL;
            break;
        case HAL_DMA_XFER_HALFCPLT_CB_ID:
            hdma->XferHalfCpltCallback = NULL;
            break;
        case HAL_DMA_XFER_ERROR_CB_ID:
            hdma->XferErrorCallback = NULL;
            hdma->XferAbortCallback = NULL;
            break;
        case HAL_DMA_XFER_ABORT_CB_ID:
            hdma->XferAbortCallback = NULL;
            break;
        case HAL_DMA_XFER_ALL_CB_ID:
            hdma->XferCpltCallback = NULL;
            hdma->XferHalfCpltCallback = NULL;
            hdma->XferErrorCallback = NULL;
            hdma->XferAbortCallback = NULL;
            break;
        default:
            status = HAL_ERROR;
            break;
    }

    return status;
}

/**
  * @brief  Return the DMA handle state.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return HAL state
  */
HAL_DMA_StateTypeDef HAL_DMA_GetState(HAL_DMA_HandleTypeDef *hdma)
{
    if (hdma == NULL) {
        return HAL_DMA_STATE_RESET;
    }
    return hdma->State;
}

/**
  * @brief  Return the DMA error code.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return DMA error code
  */
uint32_t HAL_DMA_GetError(HAL_DMA_HandleTypeDef *hdma)
{
    if (hdma == NULL) {
        return HAL_DMA_ERROR_NONE;
    }
    return hdma->ErrorCode;
}

/**
  * @brief  Return the handle currently allocated on the given DMA channel.
  * @param  Channel DMA channel index (0 .. LL_DMA_CHANNEL_NUMS-1).
  * @return Handle bound to the channel, or NULL when the channel is unused.
  */
HAL_DMA_HandleTypeDef *HAL_DMA_GetHandleByChannel(uint32_t Channel)
{
    if (Channel >= LL_DMA_CHANNEL_NUMS) {
        return NULL;
    }
    return DMA_Handle[Channel];
}

/**
  * @}
  */

/** @defgroup DMA_HAL_EF_Callbacks DMA HAL Callbacks
  * @brief    DMA HAL callbacks (weak, user-overridable)
  * @{
  */

/**
  * @brief  Initialize the DMA MSP.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__WEAK void HAL_DMA_MspInit(HAL_DMA_HandleTypeDef *hdma)
{
    /* NOTE: This function should be implemented by the user application.
             Typical action: enable the DMA clock. The DMA channel interrupt
             lines are enabled by the application MSP (HAL_MspInit). */
    HAL_UNUSED(hdma);
}

/**
  * @brief  De-initialize the DMA MSP.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__WEAK void HAL_DMA_MspDeInit(HAL_DMA_HandleTypeDef *hdma)
{
    /* NOTE: This function should be implemented by the user application. */
    HAL_UNUSED(hdma);
}

/**
  * @brief  DMA transfer complete callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__WEAK void HAL_DMA_XferCpltCallback(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UNUSED(hdma);
}

/**
  * @brief  DMA transfer half-complete callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__WEAK void HAL_DMA_XferHalfCpltCallback(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UNUSED(hdma);
}

/**
  * @brief  DMA transfer error callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__WEAK void HAL_DMA_XferErrorCallback(HAL_DMA_HandleTypeDef *hdma)
{
    HAL_UNUSED(hdma);
}

/**
  * @brief  Transfer abort callback.
  * @param  hdma Pointer to a HAL_DMA_HandleTypeDef structure.
  * @return None
  */
__WEAK void HAL_DMA_XferAbortCallback(HAL_DMA_HandleTypeDef *hdma)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(hdma);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_DMA_XferAbortCallback can be implemented in the user file.
     */
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup DMA_HAL_Private_Functions DMA HAL Private Functions
  * @{
  */

/**
  * @brief  DMA channel reset
  * @param  DMAx DMA peripheral instance.
  * @param  Channel DMA channel index.
  * @return HAL state
  */
static HAL_StatusTypeDef DMA_ChannelReset(DMA_TypeDef *DMAx, uint32_t Channel)
{
    uint32_t tickstart;  

    LL_DMA_DisableChannel(DMAx, Channel);

    tickstart = HAL_GetTick();
    while (LL_DMA_IsEnabledChannel(DMAx, Channel)) {
        /* Check for timeout. */
        if ((HAL_GetTick() - tickstart) > DMA_DEFAULT_TIMEOUT) {
            /* Re-check to avoid false timeout detection. */
            if (LL_DMA_IsEnabledChannel(DMAx, Channel)) {
                return HAL_TIMEOUT;
            }
        }
    }

    LL_DMA_SetBlockTransCnt(DMAx, Channel, 0UL);
    LL_DMA_SetSrcAddress(DMAx, Channel, 0UL);
    LL_DMA_SetDstAddress(DMAx, Channel, 0UL);

    LL_DMA_ResetControl(DMAx, Channel);

    return HAL_OK;
}

/**
  * @brief  Allocate a DMA channel.
  * @param  PreferredChannel Preferred channel (may be LL_DMA_CHANNEL_INVALID for auto).
  * @return Allocated channel index, or HAL_DMA_CHANNEL_INVALID if none free.
  */
static uint32_t DMA_AllocateChannel(uint32_t PreferredChannel)
{
    uint32_t ch;

    if (PreferredChannel != HAL_DMA_CHANNEL_INVALID) {
        if (PreferredChannel >= HAL_DMA_CHANNEL_NUMS) {
            return HAL_DMA_CHANNEL_INVALID;
        }
        if (DMA_Handle[PreferredChannel] != NULL) {
            return HAL_DMA_CHANNEL_INVALID;
        }
        return PreferredChannel;
    }

    /* Auto-allocate the first free channel */
    for (ch = 0U; ch < HAL_DMA_CHANNEL_NUMS; ch++) {
        if (DMA_Handle[ch] == NULL) {
            return ch;
        }
    }

    return HAL_DMA_CHANNEL_INVALID;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_DMA_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
