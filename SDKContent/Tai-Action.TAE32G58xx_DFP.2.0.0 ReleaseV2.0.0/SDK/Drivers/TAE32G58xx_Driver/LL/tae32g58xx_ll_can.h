/**
  ******************************************************************************
  * @file    tae32g58xx_ll_can.h
  * @author  Tai-Action SD Team
  * @brief   Header file for CAN LL module
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
#ifndef _TAE32G58XX_LL_CAN_H_
#define _TAE32G58XX_LL_CAN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

#if defined(CAN0) || defined(CAN1)

/** @addtogroup CAN_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Constants CAN LL Exported Constants
  * @brief    CAN LL Exported Constants
  * @{
  */



/** @defgroup CAN_LL_EC_Information LL CAN Information
  * @brief LL CAN Information
  * @{
  */

/**
  * @brief CAN 2.0 Max Data Length Definition
  */
#define LL_CAN_20_DAT_LEN_MAX               (8UL)

/**
  * @brief CAN FD Max Data Length Definition
  */
#define LL_CAN_FD_DAT_LEN_MAX               (64UL)

/**
  * @brief PRB Data Buffer Layer Level
  */
#define LL_CAN_RBUFDT_WORD_LAYER_LEVEL      (16UL)

/**
  * @brief SRB Data Buffer Layer Level
  */
#define LL_CAN_SBUFDT_WORD_LAYER_LEVEL      (16UL)

/**
  * @brief Tx Data Buffer Layer Level
  */
#define LL_CAN_TBUFDT_WORD_LAYER_LEVEL      (16UL)

/**
  * @brief PRB Message Buffer Level
  */
#define LL_CAN_PRB_DEPTH_MAX                (3UL)

/**
  * @brief SRB Message Buffer Level
  */
#define LL_CAN_SRB_DEPTH_MAX                (3UL)

/**
  * @brief ETB Message Buffer Level
  */
#define LL_CAN_ETB_DEPTH_MAX                (3UL)

/**
  * @brief CAN RX Identifier Data Mask definition.
  */
#define LL_CAN_RX_ID_DATA_ID_MSK                (0x1FFFFFFFUL)  /*!< RX Identifier Data ID                      */
#define LL_CAN_RX_ID_DATA_ESI_MSK               (0x80000000UL)  /*!< RX Identifier Data ESI                     */

/**
  * @brief CAN RX Control Data Mask definition.
  */
#define LL_CAN_RX_CTRL_DATA_DLC_MSK             (0x000FUL)      /*!< RX Control Data DLC                        */
#define LL_CAN_RX_CTRL_DATA_BRS_MSK             (0x0010UL)      /*!< RX Control Data BRS                        */
#define LL_CAN_RX_CTRL_DATA_FDF_MSK             (0x0020UL)      /*!< RX Control Data FDF                        */
#define LL_CAN_RX_CTRL_DATA_RTR_MSK             (0x0040UL)      /*!< RX Control Data RTR                        */
#define LL_CAN_RX_CTRL_DATA_IDE_MSK             (0x0080UL)      /*!< RX Control Data IDE                        */

#define LL_CAN_RX_CTRL_DATA_TIMESTAMP_MSK       (0x00FFFF00UL)  /*!< RX Control Data Timestamp                  */
#define LL_CAN_RX_CTRL_DATA_ACCEPT_DATA_MSK     (0x0F000000UL)  /*!< RX Control Data Acceptance Data            */

/**
  * @brief CAN TX Identifier Data Mask definition.
  */
#define LL_CAN_TX_ID_DATA_ID_MSK                (0x1FFFFFFFUL)  /*!< TX Identifier Data ID                      */

/**
  * @brief CAN TX Control Data Mask definition.
  */
#define LL_CAN_TX_CTRL_DATA_DLC_MSK             (0x000FUL)      /*!< TX Control Data DLC                        */
#define LL_CAN_TX_CTRL_DATA_BRS_MSK             (0x0010UL)      /*!< TX Control Data BRS                        */
#define LL_CAN_TX_CTRL_DATA_FDF_MSK             (0x0020UL)      /*!< TX Control Data FDF                        */
#define LL_CAN_TX_CTRL_DATA_RTR_MSK             (0x0040UL)      /*!< TX Control Data RTR                        */
#define LL_CAN_TX_CTRL_DATA_IDE_MSK             (0x0080UL)      /*!< TX Control Data IDE                        */

#define LL_CAN_TX_CTRL_DATA_MESG_MARKER_MSK     (0xFF00UL)      /*!< TX Control Data Message Marker             */
#define LL_CAN_TX_CTRL_DATA_TX_EVT_MSK          (0x80000000UL)  /*!< TX Control Data TX Event                   */

/**
  * @brief CAN Tx Event Identifier Data Mask definition.
  */
#define LL_CAN_TX_EVT_ID_DATA_ID_MSK            (0x1FFFFFFFUL)  /*!< Tx Event Identifier Data ID                */
#define LL_CAN_TX_EVT_ID_DATA_ESI_MSK           (0x80000000UL)  /*!< Tx Event Identifier Data ESI               */

/**
  * @brief CAN Tx Event Control Data Mask definition.
  */
#define LL_CAN_TX_EVT_DATA_DLC_MSK              (0x000FUL)      /*!< Tx Event Control Data DLC                  */
#define LL_CAN_TX_EVT_DATA_BRS_MSK              (0x0010UL)      /*!< Tx Event Control Data BRS                  */
#define LL_CAN_TX_EVT_DATA_FDF_MSK              (0x0020UL)      /*!< Tx Event Control Data FDF                  */
#define LL_CAN_TX_EVT_DATA_RTR_MSK              (0x0040UL)      /*!< Tx Event Control Data RTR                  */
#define LL_CAN_TX_EVT_DATA_IDE_MSK              (0x0080UL)      /*!< Tx Event Control Data IDE                  */

#define LL_CAN_TX_EVT_DATA_TIMESTAMP_MSK        (0x00FFFF00UL)  /*!< Tx Event Control Data Timestamp            */
#define LL_CAN_TX_EVT_DATA_MESG_MARKER_MSK      (0xFF000000UL)  /*!< Tx Event Control Data Message Marker       */

/**
  * @brief LL CAN CTRL Operating Mode Mask Definition
  */
#define LL_CAN_CTRL_OP_MODE_MSK                             ((CAN0_CTRL_LOM_Msk       | CAN0_CTRL_LBME_Msk     | \
                                                              CAN0_CTRL_LBMI_Msk      ))

/**
  * @brief LL CAN Rx Interrupt Enable Mask Definition
  */
#define LL_CAN_INTREN_RX_IT_EN_MSK                          ((CAN0_INTREN_RTOIE_Msk   | CAN0_INTREN_STOIE_Msk  | \
                                                              CAN0_INTREN_SOIE_Msk    | CAN0_INTREN_SFIE_Msk   | \
                                                              CAN0_INTREN_SAFIE_Msk   | CAN0_INTREN_SRIE_Msk   | \
                                                              CAN0_INTREN_RIE_Msk     | CAN0_INTREN_ROIE_Msk   | \
                                                              CAN0_INTREN_RFIE_Msk    | CAN0_INTREN_RAFIE_Msk))

/**
  * @brief LL CAN Tx Interrupt Enable All Mask Definition
  */
#define LL_CAN_INTREN_TX_IT_EN_MSK                          ((CAN0_INTREN_TEIE_Msk    | CAN0_INTREN_TAEIE_Msk  | \
                                                              CAN0_INTREN_ETOIE_Msk   | CAN0_INTREN_EOIE_Msk   | \
                                                              CAN0_INTREN_EFIE_Msk    | CAN0_INTREN_EAFIE_Msk  | \
                                                              CAN0_INTREN_ERIE_Msk    | CAN0_INTREN_TPIE_Msk   | \
                                                              CAN0_INTREN_TSIE_Msk    ))

/**
  * @brief LL CAN INTREN Interrupt Enable All Mask Definition
  */
#define LL_CAN_INTREN_IT_EN_MSK                             ((CAN0_INTREN_TEIE_Msk    | CAN0_INTREN_TAEIE_Msk  | \
                                                              CAN0_INTREN_PMIE_Msk    | CAN0_INTREN_TSCIE_Msk  | \
                                                              CAN0_INTREN_RTOIE_Msk   | CAN0_INTREN_STOIE_Msk  | \
                                                              CAN0_INTREN_ETOIE_Msk   | CAN0_INTREN_CTOIE_Msk  | \
                                                              CAN0_INTREN_SOIE_Msk    | CAN0_INTREN_SFIE_Msk   | \
                                                              CAN0_INTREN_SAFIE_Msk   | CAN0_INTREN_EOIE_Msk   | \
                                                              CAN0_INTREN_EFIE_Msk    | CAN0_INTREN_EAFIE_Msk  | \
                                                              CAN0_INTREN_AIE_Msk     | CAN0_INTREN_SRIE_Msk   | \
                                                              CAN0_INTREN_ERIE_Msk    | CAN0_INTREN_ECIE_Msk   | \
                                                              CAN0_INTREN_EPIE_Msk    | CAN0_INTREN_ALIE_Msk   | \
                                                              CAN0_INTREN_BEIE_Msk    | CAN0_INTREN_RIE_Msk    | \
                                                              CAN0_INTREN_ROIE_Msk    | CAN0_INTREN_RFIE_Msk   | \
                                                              CAN0_INTREN_RAFIE_Msk   | CAN0_INTREN_TPIE_Msk   | \
                                                              CAN0_INTREN_TSIE_Msk    | CAN0_INTREN_EIE_Msk))

/**
  * @brief LL CAN INTREN Interrupt Enable Mask Definition
  */
#define LL_CAN_INTREN_ITEnMskTypeDef                        uint32_t

#define LL_CAN_INTREN_TEIE                   (CAN0_INTREN_TEIE_Msk)               /*!< TEIE Mask                */
#define LL_CAN_INTREN_TAEIE                  (CAN0_INTREN_TAEIE_Msk)              /*!< TAEIE Mask               */
#define LL_CAN_INTREN_PMIE                   (CAN0_INTREN_PMIE_Msk)               /*!< PMIE Mask                */
#define LL_CAN_INTREN_TSCIE                  (CAN0_INTREN_TSCIE_Msk)              /*!< TSCIE Mask               */
#define LL_CAN_INTREN_RTOIE                  (CAN0_INTREN_RTOIE_Msk)              /*!< RTOIE Mask               */
#define LL_CAN_INTREN_STOIE                  (CAN0_INTREN_STOIE_Msk)              /*!< STOIE Mask               */
#define LL_CAN_INTREN_ETOIE                  (CAN0_INTREN_ETOIE_Msk)              /*!< ETOIE Mask               */
#define LL_CAN_INTREN_CTOIE                  (CAN0_INTREN_CTOIE_Msk)              /*!< CTOIE Mask               */
#define LL_CAN_INTREN_SOIE                   (CAN0_INTREN_SOIE_Msk)               /*!< SOIE Mask                */
#define LL_CAN_INTREN_SFIE                   (CAN0_INTREN_SFIE_Msk)               /*!< SFIE Mask                */
#define LL_CAN_INTREN_SAFIE                  (CAN0_INTREN_SAFIE_Msk)              /*!< SAFIE Mask               */
#define LL_CAN_INTREN_EOIE                   (CAN0_INTREN_EOIE_Msk)               /*!< EOIE Mask                */
#define LL_CAN_INTREN_EFIE                   (CAN0_INTREN_EFIE_Msk)               /*!< EFIE Mask                */
#define LL_CAN_INTREN_EAFIE                  (CAN0_INTREN_EAFIE_Msk)              /*!< EAFIE Mask               */
#define LL_CAN_INTREN_AIE_SP                 (CAN0_INTREN_AIE_Msk)                /*!< AIE Mask                 */
#define LL_CAN_INTREN_SRIE                   (CAN0_INTREN_SRIE_Msk)               /*!< SRIE Mask                */
#define LL_CAN_INTREN_ERIE                   (CAN0_INTREN_ERIE_Msk)               /*!< ERIE Mask                */
#define LL_CAN_INTREN_ECIE                   (CAN0_INTREN_ECIE_Msk)               /*!< ECIE Mask                */
#define LL_CAN_INTREN_EPIE                   (CAN0_INTREN_EPIE_Msk)               /*!< EPIE Mask                */
#define LL_CAN_INTREN_ALIE                   (CAN0_INTREN_ALIE_Msk)               /*!< ALIE Mask                */
#define LL_CAN_INTREN_BEIE                   (CAN0_INTREN_BEIE_Msk)               /*!< BEIE Mask                */
#define LL_CAN_INTREN_RIE                    (CAN0_INTREN_RIE_Msk)                /*!< RIE Mask                 */
#define LL_CAN_INTREN_ROIE                   (CAN0_INTREN_ROIE_Msk)               /*!< ROIE Mask                */
#define LL_CAN_INTREN_RFIE                   (CAN0_INTREN_RFIE_Msk)               /*!< RFIE Mask                */
#define LL_CAN_INTREN_RAFIE                  (CAN0_INTREN_RAFIE_Msk)              /*!< RAFIE Mask               */
#define LL_CAN_INTREN_TPIE                   (CAN0_INTREN_TPIE_Msk)               /*!< TPIE Mask                */
#define LL_CAN_INTREN_TSIE                   (CAN0_INTREN_TSIE_Msk)               /*!< TSIE Mask                */
#define LL_CAN_INTREN_EIE                    (CAN0_INTREN_EIE_Msk)                /*!< EIE Mask                 */

/**
  * @brief LL CAN Rx Interrupt Flag Mask Definition
  */
#define LL_CAN_INTRST_RX_IT_FLAG_MSK                        ((CAN0_INTRST_RTOIF_Msk   | CAN0_INTRST_STOIF_Msk  | \
                                                              CAN0_INTRST_SOIF_Msk    | CAN0_INTRST_SFIF_Msk   | \
                                                              CAN0_INTRST_SAFIF_Msk   | CAN0_INTRST_SRIF_Msk   | \
                                                              CAN0_INTRST_RIF_Msk     | CAN0_INTRST_ROIF_Msk   | \
                                                              CAN0_INTRST_RFIF_Msk    | CAN0_INTRST_RAFIF_Msk  ))

/**
  * @brief LL CAN PRB Interrupt Flag Mask Definition
  */
#define LL_CAN_INTRST_PRB_IT_FLAG_MSK                       ((CAN0_INTRST_RTOIF_Msk   |                          \
                                                              CAN0_INTRST_RIF_Msk     | CAN0_INTRST_ROIF_Msk   | \
                                                              CAN0_INTRST_RFIF_Msk    | CAN0_INTRST_RAFIF_Msk  ))

/**
  * @brief LL CAN SRB Interrupt Flag Mask Definition
  */
#define LL_CAN_INTRST_SRB_IT_FLAG_MSK                       ((CAN0_INTRST_STOIF_Msk   |                          \
                                                              CAN0_INTRST_SOIF_Msk    | CAN0_INTRST_SFIF_Msk   | \
                                                              CAN0_INTRST_SAFIF_Msk   | CAN0_INTRST_SRIF_Msk   ))

/**
  * @brief LL CAN Tx Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_TX_IT_FLAG_MSK                        ((CAN0_INTRST_TEIF_Msk    | CAN0_INTRST_TAEIF_Msk  | \
                                                              CAN0_INTRST_ETOIF_Msk   | CAN0_INTRST_EOIF_Msk   | \
                                                              CAN0_INTRST_EFIF_Msk    | CAN0_INTRST_EAFIF_Msk  | \
                                                              CAN0_INTRST_ERIF_Msk    | CAN0_INTRST_TPIF_Msk   | \
                                                              CAN0_INTRST_TSIF_Msk    ))

/**
  * @brief LL CAN PTB Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_PTB_IT_FLAG_MSK                       (CAN0_INTRST_TPIF_Msk)

/**
  * @brief LL CAN STB Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_STB_IT_FLAG_MSK                       ((CAN0_INTRST_TEIF_Msk    | CAN0_INTRST_TAEIF_Msk  | \
                                                              CAN0_INTRST_TSIF_Msk    ))

/**
  * @brief LL CAN ETB Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_ETB_IT_FLAG_MSK                       ((CAN0_INTRST_ETOIF_Msk   | CAN0_INTRST_EOIF_Msk   | \
                                                              CAN0_INTRST_EFIF_Msk    | CAN0_INTRST_EAFIF_Msk  | \
                                                              CAN0_INTRST_ERIF_Msk    ))

/**
  * @brief LL CAN Error Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_ERR_IT_FLAG_MSK                       ((CAN0_INTRST_ECIF_Msk    | CAN0_INTRST_EPIF_Msk   | \
                                                              CAN0_INTRST_ALIF_Msk    | CAN0_INTRST_BEIF_Msk   | \
                                                              CAN0_INTRST_EIF_Msk     ))

/**
  * @brief LL CAN Timestamp Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_TMS_IT_FLAG_MSK                       ((CAN0_INTRST_TSCIF_Msk   ))

/**
  * @brief LL CAN Timeout Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_TMO_IT_FLAG_MSK                       ((CAN0_INTRST_RTOIF_Msk   | CAN0_INTRST_STOIF_Msk  | \
                                                              CAN0_INTRST_ETOIF_Msk   | CAN0_INTRST_CTOIF_Msk  ))

/**
  * @brief LL CAN High Priority Message Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_HPM_IT_FLAG_MSK                       (CAN0_INTRST_PMIF_Msk)


/**
  * @brief LL CAN INTRST Interrupt Flag All Mask Definition
  */
#define LL_CAN_INTRST_IT_FLAG_MSK                           ((CAN0_INTRST_TEIF_Msk    | CAN0_INTRST_TAEIF_Msk  | \
                                                              CAN0_INTRST_PMIF_Msk    | CAN0_INTRST_TSCIF_Msk  | \
                                                              CAN0_INTRST_RTOIF_Msk   | CAN0_INTRST_STOIF_Msk  | \
                                                              CAN0_INTRST_ETOIF_Msk   | CAN0_INTRST_CTOIF_Msk  | \
                                                              CAN0_INTRST_SOIF_Msk    | CAN0_INTRST_SFIF_Msk   | \
                                                              CAN0_INTRST_SAFIF_Msk   | CAN0_INTRST_EOIF_Msk   | \
                                                              CAN0_INTRST_EFIF_Msk    | CAN0_INTRST_EAFIF_Msk  | \
                                                              CAN0_INTRST_EWARN_Msk   | CAN0_INTRST_EPASS_Msk  | \
                                                              CAN0_INTRST_SRIF_Msk    | CAN0_INTRST_ERIF_Msk   | \
                                                              CAN0_INTRST_ECIF_Msk    | CAN0_INTRST_EPIF_Msk   | \
                                                              CAN0_INTRST_ALIF_Msk    | CAN0_INTRST_BEIF_Msk   | \
                                                              CAN0_INTRST_RIF_Msk     | CAN0_INTRST_ROIF_Msk   | \
                                                              CAN0_INTRST_RFIF_Msk    | CAN0_INTRST_RAFIF_Msk  | \
                                                              CAN0_INTRST_TPIF_Msk    | CAN0_INTRST_TSIF_Msk   | \
                                                              CAN0_INTRST_EIF_Msk     | CAN0_INTRST_AIF_Msk    ))

/**
  * @brief LL CAN INTRST Interrupt Flag W1C Mask Definition
  */
#define LL_CAN_INTRST_IT_W1C_FLAG_MSK                       ((CAN0_INTRST_PMIF_Msk    | CAN0_INTRST_TSCIF_Msk  | \
                                                              CAN0_INTRST_RTOIF_Msk   | CAN0_INTRST_STOIF_Msk  | \
                                                              CAN0_INTRST_ETOIF_Msk   | CAN0_INTRST_CTOIF_Msk  | \
                                                              CAN0_INTRST_SOIF_Msk    | CAN0_INTRST_SFIF_Msk   | \
                                                              CAN0_INTRST_SAFIF_Msk   | CAN0_INTRST_EOIF_Msk   | \
                                                              CAN0_INTRST_EFIF_Msk    | CAN0_INTRST_EAFIF_Msk  | \
                                                              CAN0_INTRST_SRIF_Msk    | CAN0_INTRST_ERIF_Msk   | \
                                                              CAN0_INTRST_ECIF_Msk    | CAN0_INTRST_EPIF_Msk   | \
                                                              CAN0_INTRST_ALIF_Msk    | CAN0_INTRST_BEIF_Msk   | \
                                                              CAN0_INTRST_RIF_Msk     | CAN0_INTRST_ROIF_Msk   | \
                                                              CAN0_INTRST_RFIF_Msk    | CAN0_INTRST_RAFIF_Msk  | \
                                                              CAN0_INTRST_TPIF_Msk    | CAN0_INTRST_TSIF_Msk   | \
                                                              CAN0_INTRST_EIF_Msk     | CAN0_INTRST_AIF_Msk    ))

/**
  * @brief LL CAN INTRST Interrupt Pending Mask Definition
  */
#define LL_CAN_INTRST_ITPendingMskTypeDef                   uint32_t

#define LL_CAN_INTRST_TEIF                   (CAN0_INTRST_TEIF_Msk)               /*!< TEIF Mask                */
#define LL_CAN_INTRST_TAEIF                  (CAN0_INTRST_TAEIF_Msk)              /*!< TAEIF Mask               */
#define LL_CAN_INTRST_PMIF                   (CAN0_INTRST_PMIF_Msk)               /*!< PMIF Mask                */
#define LL_CAN_INTRST_TSCIF                  (CAN0_INTRST_TSCIF_Msk)              /*!< TSCIF Mask               */
#define LL_CAN_INTRST_RTOIF                  (CAN0_INTRST_RTOIF_Msk)              /*!< RTOIF Mask               */
#define LL_CAN_INTRST_STOIF                  (CAN0_INTRST_STOIF_Msk)              /*!< STOIF Mask               */
#define LL_CAN_INTRST_ETOIF                  (CAN0_INTRST_ETOIF_Msk)              /*!< ETOIF Mask               */
#define LL_CAN_INTRST_CTOIF                  (CAN0_INTRST_CTOIF_Msk)              /*!< CTOIF Mask               */
#define LL_CAN_INTRST_SOIF                   (CAN0_INTRST_SOIF_Msk)               /*!< SOIF Mask                */
#define LL_CAN_INTRST_SFIF                   (CAN0_INTRST_SFIF_Msk)               /*!< SFIF Mask                */
#define LL_CAN_INTRST_SAFIF                  (CAN0_INTRST_SAFIF_Msk)              /*!< SAFIF Mask               */
#define LL_CAN_INTRST_EOIF                   (CAN0_INTRST_EOIF_Msk)               /*!< EOIF Mask                */
#define LL_CAN_INTRST_EFIF                   (CAN0_INTRST_EFIF_Msk)               /*!< EFIF Mask                */
#define LL_CAN_INTRST_EAFIF                  (CAN0_INTRST_EAFIF_Msk)              /*!< EAFIF Mask               */
#define LL_CAN_INTRST_EWARN_SP               (CAN0_INTRST_EWARN_Msk)              /*!< EWARN Mask               */
#define LL_CAN_INTRST_EPASS_SP               (CAN0_INTRST_EPASS_Msk)              /*!< EPASS Mask               */
#define LL_CAN_INTRST_SRIF                   (CAN0_INTRST_SRIF_Msk)               /*!< SRIF Mask                */
#define LL_CAN_INTRST_ERIF                   (CAN0_INTRST_ERIF_Msk)               /*!< ERIF Mask                */
#define LL_CAN_INTRST_ECIF                   (CAN0_INTRST_ECIF_Msk)               /*!< ECIF Mask                */
#define LL_CAN_INTRST_EPIF                   (CAN0_INTRST_EPIF_Msk)               /*!< EPIF Mask                */
#define LL_CAN_INTRST_ALIF                   (CAN0_INTRST_ALIF_Msk)               /*!< ALIF Mask                */
#define LL_CAN_INTRST_BEIF                   (CAN0_INTRST_BEIF_Msk)               /*!< BEIF Mask                */
#define LL_CAN_INTRST_RIF                    (CAN0_INTRST_RIF_Msk)                /*!< RIF Mask                 */
#define LL_CAN_INTRST_ROIF                   (CAN0_INTRST_ROIF_Msk)               /*!< ROIF Mask                */
#define LL_CAN_INTRST_RFIF                   (CAN0_INTRST_RFIF_Msk)               /*!< RFIF Mask                */
#define LL_CAN_INTRST_RAFIF                  (CAN0_INTRST_RAFIF_Msk)              /*!< RAFIF Mask               */
#define LL_CAN_INTRST_TPIF                   (CAN0_INTRST_TPIF_Msk)               /*!< TPIF Mask                */
#define LL_CAN_INTRST_TSIF                   (CAN0_INTRST_TSIF_Msk)               /*!< TSIF Mask                */
#define LL_CAN_INTRST_EIF                    (CAN0_INTRST_EIF_Msk)                /*!< EIF Mask                 */
#define LL_CAN_INTRST_AIF_SP                 (CAN0_INTRST_AIF_Msk)                /*!< AIF Mask                 */

/**
  * @brief LL CAN INTRLS Interrupt Line Mask Definition
  */
#define LL_CAN_INTRLS_ITLineMskTypeDef                      uint32_t

#define LL_CAN_INTRLS_TEILS                  (CAN0_INTRLS_TEILS_Msk)              /*!< TEILS Mask               */
#define LL_CAN_INTRLS_TAEILS                 (CAN0_INTRLS_TAEILS_Msk)             /*!< TAEILS Mask              */
#define LL_CAN_INTRLS_PMILS                  (CAN0_INTRLS_PMILS_Msk)              /*!< PMILS Mask               */
#define LL_CAN_INTRLS_TSCILS                 (CAN0_INTRLS_TSCILS_Msk)             /*!< TSCILS Mask              */
#define LL_CAN_INTRLS_RTOILS                 (CAN0_INTRLS_RTOILS_Msk)             /*!< RTOILS Mask              */
#define LL_CAN_INTRLS_STOILS                 (CAN0_INTRLS_STOILS_Msk)             /*!< STOILS Mask              */
#define LL_CAN_INTRLS_ETOILS                 (CAN0_INTRLS_ETOILS_Msk)             /*!< ETOILS Mask              */
#define LL_CAN_INTRLS_CTOILS                 (CAN0_INTRLS_CTOILS_Msk)             /*!< CTOILS Mask              */
#define LL_CAN_INTRLS_SOILS                  (CAN0_INTRLS_SOILS_Msk)              /*!< SOILS Mask               */
#define LL_CAN_INTRLS_SFILS                  (CAN0_INTRLS_SFILS_Msk)              /*!< SFILS Mask               */
#define LL_CAN_INTRLS_SAFILS                 (CAN0_INTRLS_SAFILS_Msk)             /*!< SAFILS Mask              */
#define LL_CAN_INTRLS_EOILS                  (CAN0_INTRLS_EOILS_Msk)              /*!< EOILS Mask               */
#define LL_CAN_INTRLS_EFILS                  (CAN0_INTRLS_EFILS_Msk)              /*!< EFILS Mask               */
#define LL_CAN_INTRLS_EAFILS                 (CAN0_INTRLS_EAFILS_Msk)             /*!< EAFILS Mask              */
#define LL_CAN_INTRLS_SRILS                  (CAN0_INTRLS_SRILS_Msk)              /*!< SRILS Mask               */
#define LL_CAN_INTRLS_ERILS                  (CAN0_INTRLS_ERILS_Msk)              /*!< ERILS Mask               */
#define LL_CAN_INTRLS_ECILS                  (CAN0_INTRLS_ECILS_Msk)              /*!< ECILS Mask               */
#define LL_CAN_INTRLS_EPILS                  (CAN0_INTRLS_EPILS_Msk)              /*!< EPILS Mask               */
#define LL_CAN_INTRLS_ALILS                  (CAN0_INTRLS_ALILS_Msk)              /*!< ALILS Mask               */
#define LL_CAN_INTRLS_BEILS                  (CAN0_INTRLS_BEILS_Msk)              /*!< BEILS Mask               */
#define LL_CAN_INTRLS_RILS                   (CAN0_INTRLS_RILS_Msk)               /*!< RILS Mask                */
#define LL_CAN_INTRLS_ROILS                  (CAN0_INTRLS_ROILS_Msk)              /*!< ROILS Mask               */
#define LL_CAN_INTRLS_RFILS                  (CAN0_INTRLS_RFILS_Msk)              /*!< RFILS Mask               */
#define LL_CAN_INTRLS_RAFILS                 (CAN0_INTRLS_RAFILS_Msk)             /*!< RAFILS Mask              */
#define LL_CAN_INTRLS_TPILS                  (CAN0_INTRLS_TPILS_Msk)              /*!< TPILS Mask               */
#define LL_CAN_INTRLS_TSILS                  (CAN0_INTRLS_TSILS_Msk)              /*!< TSILS Mask               */
#define LL_CAN_INTRLS_EILS                   (CAN0_INTRLS_EILS_Msk)               /*!< EILS Mask                */
#define LL_CAN_INTRLS_AILS                   (CAN0_INTRLS_AILS_Msk)               /*!< AILS Mask                */

/**
  * @brief LL CAN INTRLS Interrupt Line Select All Mask Definition
  */
#define LL_CAN_INTRLS_ALL_MSK                               ((CAN0_INTRLS_TEILS_Msk    | CAN0_INTRLS_TAEILS_Msk  | \
                                                              CAN0_INTRLS_PMILS_Msk    | CAN0_INTRLS_TSCILS_Msk  | \
                                                              CAN0_INTRLS_RTOILS_Msk   | CAN0_INTRLS_STOILS_Msk  | \
                                                              CAN0_INTRLS_ETOILS_Msk   | CAN0_INTRLS_CTOILS_Msk  | \
                                                              CAN0_INTRLS_SOILS_Msk    | CAN0_INTRLS_SFILS_Msk   | \
                                                              CAN0_INTRLS_SAFILS_Msk   | CAN0_INTRLS_EOILS_Msk   | \
                                                              CAN0_INTRLS_EFILS_Msk    | CAN0_INTRLS_EAFILS_Msk  | \
                                                              CAN0_INTRLS_SRILS_Msk    | CAN0_INTRLS_ERILS_Msk   | \
                                                              CAN0_INTRLS_ECILS_Msk    | CAN0_INTRLS_EPILS_Msk   | \
                                                              CAN0_INTRLS_ALILS_Msk    | CAN0_INTRLS_BEILS_Msk   | \
                                                              CAN0_INTRLS_RILS_Msk     | CAN0_INTRLS_ROILS_Msk   | \
                                                              CAN0_INTRLS_RFILS_Msk    | CAN0_INTRLS_RAFILS_Msk  | \
                                                              CAN0_INTRLS_TPILS_Msk    | CAN0_INTRLS_TSILS_Msk   | \
                                                              CAN0_INTRLS_EILS_Msk     | CAN0_INTRLS_AILS_Msk))



/**
  * @}
  */ /* CAN_LL_EC_Information */

/** @defgroup CAN_LL_EC_Configuration LL CAN Configuration
  * @brief LL CAN Configuration 
  * @{
  */

/**
  * @brief CAN Rx Receive Multiplexer definition
  */
#define LL_CAN_RxMuxSelTypeDef                              LL_RSV_DATA_TYPE    

#define LL_CAN_RX_MUXSEL_DISABLE                            (0UL)                /*!< CAN RX Receive Multiplexer Disabled: For CAN0 :  \
                                                                                      CAN0_RX used as the receive signal source. For   \
                                                                                      CAN1 : CAN1_RX used as the receive signal        \
                                                                                      source.                                          */
#define LL_CAN_RX_MUXSEL_ENABLE                             (1UL)                /*!< CAN RX Receive Multiplexer Enabled: For CAN0 :   \
                                                                                      CAN1_RX used as the receive signal source. For   \
                                                                                      CAN1 : CAN0_RX used as the receive signal        \
                                                                                      source. Note: When CAN is configured in          \
                                                                                      listen-only mode(LOM=1), the CAN RX Receive      \
                                                                                      Multiplexer can be enabled.                      */

#define IS_LL_CAN_RX_MUXSEL(__VAL__)                        (((__VAL__) == LL_CAN_RX_MUXSEL_DISABLE) || \
                                                             ((__VAL__) == LL_CAN_RX_MUXSEL_ENABLE)  )

/**
  *@brief CAN RX buffer status enum type define
  */
#define LL_CAN_RxBufStaTypeDef                              LL_RSV_DATA_TYPE    

#define LL_CAN_RX_BUF_STA_EMPTY                             (0UL)                /*!< CAN RX buffer empty                              */
#define LL_CAN_RX_BUF_STA_FEW                               (1UL)                /*!< CAN RX buffer few                                */
#define LL_CAN_RX_BUF_STA_ALMOST_FULL                       (2UL)                /*!< CAN RX buffer almost full                        */
#define LL_CAN_RX_BUF_STA_FULL                              (3UL)                /*!< CAN RX buffer full                               */

#define IS_LL_CAN_RX_BUF_STA(__VAL__)                       (((__VAL__) == LL_CAN_RX_BUF_STA_EMPTY)       || \
                                                             ((__VAL__) == LL_CAN_RX_BUF_STA_FEW)         || \
                                                             ((__VAL__) == LL_CAN_RX_BUF_STA_ALMOST_FULL) || \
                                                             ((__VAL__) == LL_CAN_RX_BUF_STA_FULL)        )

/**
  * @brief CAN acceptance filter slot definition.
  */
#define LL_CAN_AcceptFilSlotTypeDef                         LL_RSV_DATA_TYPE    

#define LL_CAN_ACCEPT_FILT_SLOT_0                           (0UL)                /*!< CAN acceptance filter slot 0                     */
#define LL_CAN_ACCEPT_FILT_SLOT_1                           (1UL)                /*!< CAN acceptance filter slot 1                     */
#define LL_CAN_ACCEPT_FILT_SLOT_2                           (2UL)                /*!< CAN acceptance filter slot 2                     */
#define LL_CAN_ACCEPT_FILT_SLOT_3                           (3UL)                /*!< CAN acceptance filter slot 3                     */
#define LL_CAN_ACCEPT_FILT_SLOT_4                           (4UL)                /*!< CAN acceptance filter slot 4                     */
#define LL_CAN_ACCEPT_FILT_SLOT_5                           (5UL)                /*!< CAN acceptance filter slot 5                     */
#define LL_CAN_ACCEPT_FILT_SLOT_6                           (6UL)                /*!< CAN acceptance filter slot 6                     */
#define LL_CAN_ACCEPT_FILT_SLOT_7                           (7UL)                /*!< CAN acceptance filter slot 7                     */
#define LL_CAN_ACCEPT_FILT_SLOT_8                           (8UL)                /*!< CAN acceptance filter slot 8                     */
#define LL_CAN_ACCEPT_FILT_SLOT_9                           (9UL)                /*!< CAN acceptance filter slot 9                     */
#define LL_CAN_ACCEPT_FILT_SLOT_10                          (10UL)               /*!< CAN acceptance filter slot 10                    */
#define LL_CAN_ACCEPT_FILT_SLOT_11                          (11UL)               /*!< CAN acceptance filter slot 11                    */
#define LL_CAN_ACCEPT_FILT_SLOT_12                          (12UL)               /*!< CAN acceptance filter slot 12                    */
#define LL_CAN_ACCEPT_FILT_SLOT_13                          (13UL)               /*!< CAN acceptance filter slot 13                    */
#define LL_CAN_ACCEPT_FILT_SLOT_14                          (14UL)               /*!< CAN acceptance filter slot 14                    */
#define LL_CAN_ACCEPT_FILT_SLOT_15                          (15UL)               /*!< CAN acceptance filter slot 15                    */
#define LL_CAN_ACCEPT_FILT_SLOT_NUMS                        (16UL)               /*!< CAN acceptance filter slot Numbers               */

#define IS_LL_CAN_ACCEPT_FILT_SLOT(__VAL__)                 (((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_0)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_1)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_2)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_3)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_4)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_5)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_6)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_7)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_8)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_9)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_10)   || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_11)   || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_12)   || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_13)   || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_14)   || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_SLOT_15)   )

/**
  * @brief CAN acceptance filter Rx frame type definition.
  */
#define LL_CAN_AcceptFilRxFrmTypeDef                        LL_RSV_DATA_TYPE    

#define LL_CAN_ACCEPT_FILT_FRM_STD_EXT                      (0UL)                /*!< CAN acceptance filter Rx frame type Standard and \
                                                                                      Extend                                           */
#define LL_CAN_ACCEPT_FILT_FRM_STD                          (2UL)                /*!< CAN acceptance filter Rx frame type Standard     */
#define LL_CAN_ACCEPT_FILT_FRM_EXT                          (3UL)                /*!< CAN acceptance filter Rx frame type Extend       */

#define IS_LL_CAN_ACCEPT_FILT_FRM(__VAL__)                  (((__VAL__) == LL_CAN_ACCEPT_FILT_FRM_STD_EXT) || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_FRM_STD)     || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_FILT_FRM_EXT)     )

/**
  * @brief CAN buffer almost full warnning limit definition
  */
#define LL_CAN_BufAlmostFullLimitTypeDef                    LL_RSV_DATA_TYPE    

#define LL_CAN_BUF_ALMOST_FULL_LIMIT_0                      (0UL)                /*!< CAN buffer almost full warnning limit: 0 Frame   */
#define LL_CAN_BUF_ALMOST_FULL_LIMIT_1                      (1UL)                /*!< CAN buffer almost full warnning limit: 1 Frame   */
#define LL_CAN_BUF_ALMOST_FULL_LIMIT_2                      (2UL)                /*!< CAN buffer almost full warnning limit: 2 Frame   */
#define LL_CAN_BUF_ALMOST_FULL_LIMIT_3                      (3UL)                /*!< CAN buffer almost full warnning limit: 3 Frame   */

#define IS_LL_CAN_BUF_ALMOST_FULL_LIMIT(__VAL__)            (((__VAL__) == LL_CAN_BUF_ALMOST_FULL_LIMIT_0) || \
                                                             ((__VAL__) == LL_CAN_BUF_ALMOST_FULL_LIMIT_1) || \
                                                             ((__VAL__) == LL_CAN_BUF_ALMOST_FULL_LIMIT_2) || \
                                                             ((__VAL__) == LL_CAN_BUF_ALMOST_FULL_LIMIT_3) )

/**
  * @brief CAN buffer almost empty warnning limit definition
  */
#define LL_CAN_BufAlmostEmptyLimitTypeDef                   LL_RSV_DATA_TYPE    

#define LL_CAN_BUF_ALMOST_EMPTY_LIMIT_0                     (0UL)                /*!< CAN buffer almost empty warnning limit: 0 Frame  */
#define LL_CAN_BUF_ALMOST_EMPTY_LIMIT_1                     (1UL)                /*!< CAN buffer almost empty warnning limit: 1 Frame  */
#define LL_CAN_BUF_ALMOST_EMPTY_LIMIT_2                     (2UL)                /*!< CAN buffer almost empty warnning limit: 2 Frame  */

#define IS_LL_CAN_BUF_ALMOST_EMPTY_LIMIT(__VAL__)           (((__VAL__) == LL_CAN_BUF_ALMOST_EMPTY_LIMIT_0) || \
                                                             ((__VAL__) == LL_CAN_BUF_ALMOST_EMPTY_LIMIT_1) || \
                                                             ((__VAL__) == LL_CAN_BUF_ALMOST_EMPTY_LIMIT_2) )

/**
  * @brief CAN programmable error warning limit definition
  */
#define LL_CAN_ErrWarnLimitTypeDef                          LL_RSV_DATA_TYPE    

#define LL_CAN_ERR_WARN_LIMIT_8                             (0UL)                /*!< CAN programmable error warning limit: 8 bytes    */
#define LL_CAN_ERR_WARN_LIMIT_16                            (1UL)                /*!< CAN programmable error warning limit: 16 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_24                            (2UL)                /*!< CAN programmable error warning limit: 24 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_32                            (3UL)                /*!< CAN programmable error warning limit: 32 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_40                            (4UL)                /*!< CAN programmable error warning limit: 40 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_48                            (5UL)                /*!< CAN programmable error warning limit: 48 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_56                            (6UL)                /*!< CAN programmable error warning limit: 56 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_64                            (7UL)                /*!< CAN programmable error warning limit: 64 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_72                            (8UL)                /*!< CAN programmable error warning limit: 72 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_80                            (9UL)                /*!< CAN programmable error warning limit: 80 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_88                            (10UL)               /*!< CAN programmable error warning limit: 88 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_96                            (11UL)               /*!< CAN programmable error warning limit: 96 bytes   */
#define LL_CAN_ERR_WARN_LIMIT_104                           (12UL)               /*!< CAN programmable error warning limit: 104 bytes  */
#define LL_CAN_ERR_WARN_LIMIT_112                           (13UL)               /*!< CAN programmable error warning limit: 112 bytes  */
#define LL_CAN_ERR_WARN_LIMIT_120                           (14UL)               /*!< CAN programmable error warning limit: 120 bytes  */
#define LL_CAN_ERR_WARN_LIMIT_128                           (15UL)               /*!< CAN programmable error warning limit: 128 bytes  */

#define IS_LL_CAN_ERR_WARN_LIMIT(__VAL__)                   (((__VAL__) == LL_CAN_ERR_WARN_LIMIT_8)   || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_16)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_24)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_32)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_40)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_48)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_56)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_64)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_72)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_80)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_88)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_96)  || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_104) || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_112) || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_120) || \
                                                             ((__VAL__) == LL_CAN_ERR_WARN_LIMIT_128) )

/**
  * @brief CAN Data Length Code definition
  */
#define LL_CAN_DatLenCodeTypeDef                            LL_RSV_DATA_TYPE    

#define LL_CAN_DAT_LEN_CODE_BYTE_0                          (0UL)                /*!< CAN Data Length 0 Byte                           */
#define LL_CAN_DAT_LEN_CODE_BYTE_1                          (1UL)                /*!< CAN Data Length 1 Byte                           */
#define LL_CAN_DAT_LEN_CODE_BYTES_2                         (2UL)                /*!< CAN Data Length 2 Bytes                          */
#define LL_CAN_DAT_LEN_CODE_BYTES_3                         (3UL)                /*!< CAN Data Length 3 Bytes                          */
#define LL_CAN_DAT_LEN_CODE_BYTES_4                         (4UL)                /*!< CAN Data Length 4 Bytes                          */
#define LL_CAN_DAT_LEN_CODE_BYTES_5                         (5UL)                /*!< CAN Data Length 5 Bytes                          */
#define LL_CAN_DAT_LEN_CODE_BYTES_6                         (6UL)                /*!< CAN Data Length 6 Bytes                          */
#define LL_CAN_DAT_LEN_CODE_BYTES_7                         (7UL)                /*!< CAN Data Length 7 Bytes                          */
#define LL_CAN_DAT_LEN_CODE_BYTES_8                         (8UL)                /*!< CAN Data Length 8 Bytes                          */
#define LL_CAN_DAT_LEN_CODE_BYTES_12                        (9UL)                /*!< CAN Data Length 12 Bytes                         */
#define LL_CAN_DAT_LEN_CODE_BYTES_16                        (10UL)               /*!< CAN Data Length 16 Bytes                         */
#define LL_CAN_DAT_LEN_CODE_BYTES_20                        (11UL)               /*!< CAN Data Length 20 Bytes                         */
#define LL_CAN_DAT_LEN_CODE_BYTES_24                        (12UL)               /*!< CAN Data Length 24 Bytes                         */
#define LL_CAN_DAT_LEN_CODE_BYTES_32                        (13UL)               /*!< CAN Data Length 32 Bytes                         */
#define LL_CAN_DAT_LEN_CODE_BYTES_48                        (14UL)               /*!< CAN Data Length 48 Bytes                         */
#define LL_CAN_DAT_LEN_CODE_BYTES_64                        (15UL)               /*!< CAN Data Length 64 Bytes                         */

#define IS_LL_CAN_DAT_LEN_CODE(__VAL__)                     (((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTE_0)   || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTE_1)   || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_2)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_3)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_4)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_5)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_6)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_7)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_8)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_12) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_16) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_20) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_24) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_32) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_48) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_CODE_BYTES_64) )

/**
  * @brief CAN Data Length Bytes definition
  */
#define LL_CAN_DatLenBytesTypeDef                           LL_RSV_DATA_TYPE    

#define LL_CAN_DAT_LEN_BYTES_CODE_0                         (0UL)                /*!< CAN Data Length Code 0 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_1                         (1UL)                /*!< CAN Data Length Code 1 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_2                         (2UL)                /*!< CAN Data Length Code 2 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_3                         (3UL)                /*!< CAN Data Length Code 3 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_4                         (4UL)                /*!< CAN Data Length Code 4 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_5                         (5UL)                /*!< CAN Data Length Code 5 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_6                         (6UL)                /*!< CAN Data Length Code 6 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_7                         (7UL)                /*!< CAN Data Length Code 7 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_8                         (8UL)                /*!< CAN Data Length Code 8 Bytes                     */
#define LL_CAN_DAT_LEN_BYTES_CODE_9                         (12UL)               /*!< CAN Data Length Code 12 Bytes                    */
#define LL_CAN_DAT_LEN_BYTES_CODE_10                        (16UL)               /*!< CAN Data Length Code 16 Bytes                    */
#define LL_CAN_DAT_LEN_BYTES_CODE_11                        (20UL)               /*!< CAN Data Length Code 20 Bytes                    */
#define LL_CAN_DAT_LEN_BYTES_CODE_12                        (24UL)               /*!< CAN Data Length Code 24 Bytes                    */
#define LL_CAN_DAT_LEN_BYTES_CODE_13                        (32UL)               /*!< CAN Data Length Code 32 Bytes                    */
#define LL_CAN_DAT_LEN_BYTES_CODE_14                        (48UL)               /*!< CAN Data Length Code 48 Bytes                    */
#define LL_CAN_DAT_LEN_BYTES_CODE_15                        (64UL)               /*!< CAN Data Length Code 64 Bytes                    */

#define IS_LL_CAN_DAT_LEN_BYTES(__VAL__)                    (((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_0)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_1)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_2)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_3)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_4)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_5)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_6)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_7)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_8)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_9)  || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_10) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_11) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_12) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_13) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_14) || \
                                                             ((__VAL__) == LL_CAN_DAT_LEN_BYTES_CODE_15) )

/**
  * @brief CAN Error Status definition.
  */
#define LL_CAN_ErrStatusTypeDef                             LL_RSV_DATA_TYPE    

#define LL_CAN_ERROR_STATUS_NONE                            (0UL)                /*!< CAN no error                                     */
#define LL_CAN_ERROR_STATUS_BIT_NOT_DAT_FIELD               (1UL)                /*!< CAN bit error of not data field                  */
#define LL_CAN_ERROR_STATUS_FORMAT_NOT_DAT_FIELD            (2UL)                /*!< CAN format error of not data field               */
#define LL_CAN_ERROR_STATUS_BIT_STUFFING_NOT_DAT_FIELD      (3UL)                /*!< CAN bit stuffing error of not data field         */
#define LL_CAN_ERROR_STATUS_ACK                             (4UL)                /*!< CAN acknowledgement error                        */
#define LL_CAN_ERROR_STATUS_CRC                             (5UL)                /*!< CAN CRC error                                    */
#define LL_CAN_ERROR_STATUS_OTHER                           (6UL)                /*!< CAN other error                                  */


#define IS_LL_CAN_ERROR_STATUS(__VAL__)                     (((__VAL__) == LL_CAN_ERROR_STATUS_NONE)                        || \
                                                             ((__VAL__) == LL_CAN_ERROR_STATUS_BIT_NOT_DAT_FIELD)           || \
                                                             ((__VAL__) == LL_CAN_ERROR_STATUS_FORMAT_NOT_DAT_FIELD)        || \
                                                             ((__VAL__) == LL_CAN_ERROR_STATUS_BIT_STUFFING_NOT_DAT_FIELD)  || \
                                                             ((__VAL__) == LL_CAN_ERROR_STATUS_ACK)                         || \
                                                             ((__VAL__) == LL_CAN_ERROR_STATUS_CRC)                         || \
                                                             ((__VAL__) == LL_CAN_ERROR_STATUS_OTHER)                       )

/**
  * @brief CAN frame store mode definition.
  */
#define LL_CAN_FrmStoreModeTypeDef                          LL_RSV_DATA_TYPE    

#define LL_CAN_FRAME_STORE_MODE_NONE                        (0UL)                /*!< CAN frame store none                             */
#define LL_CAN_FRAME_STORE_MODE_PRB                         (1UL)                /*!< CAN frame store with PRB                         */
#define LL_CAN_FRAME_STORE_MODE_SRB                         (2UL)                /*!< CAN frame store with SRB                         */

#define IS_LL_CAN_FRAME_STORE_MODE(__VAL__)                 (((__VAL__) == LL_CAN_FRAME_STORE_MODE_NONE) || \
                                                             ((__VAL__) == LL_CAN_FRAME_STORE_MODE_PRB)  || \
                                                             ((__VAL__) == LL_CAN_FRAME_STORE_MODE_SRB)  )

/**
  * @brief CAN node status definition.
  */
#define LL_CAN_NodeStaTypeDef                               LL_RSV_DATA_TYPE    

#define LL_CAN_NODE_STA_SYNC                                (0UL)                /*!< CAN node Synchronization status                  */
#define LL_CAN_NODE_STA_IDLE                                (1UL)                /*!< CAN node Idle status                             */
#define LL_CAN_NODE_STA_RECV                                (2UL)                /*!< CAN node Receive status                          */
#define LL_CAN_NODE_STA_SEND                                (3UL)                /*!< CAN node Transmission status                     */

#define IS_LL_CAN_NODE_STA(__VAL__)                         (((__VAL__) == LL_CAN_NODE_STA_SYNC) || \
                                                             ((__VAL__) == LL_CAN_NODE_STA_IDLE) || \
                                                             ((__VAL__) == LL_CAN_NODE_STA_RECV) || \
                                                             ((__VAL__) == LL_CAN_NODE_STA_SEND) )

/**
  * @brief CAN Data Field Error definition.
  */
#define LL_CAN_DatFieldErrTypeDef                           LL_RSV_DATA_TYPE    

#define LL_CAN_DATA_FIELD_ERR_NONE                          (0UL)                /*!< CAN data field no error                          */
#define LL_CAN_DATA_FIELD_ERR_BIT                           (1UL)                /*!< CAN data field Bit error                         */
#define LL_CAN_DATA_FIELD_ERR_BIT_STUFFING                  (2UL)                /*!< CAN data field Bit Stuffing error                */
#define LL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT              (3UL)                /*!< CAN data field Acc Accelerated Frame Bit error   */
#define LL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT_STUFFING     (4UL)                /*!< CAN data field Acc Accelerated Frame Bit         \
                                                                                      Stuffing error                                   */

#define IS_LL_CAN_DATA_FIELD_ERR(__VAL__)                   (((__VAL__) == LL_CAN_DATA_FIELD_ERR_NONE)                      || \
                                                             ((__VAL__) == LL_CAN_DATA_FIELD_ERR_BIT)                       || \
                                                             ((__VAL__) == LL_CAN_DATA_FIELD_ERR_BIT_STUFFING)              || \
                                                             ((__VAL__) == LL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT)          || \
                                                             ((__VAL__) == LL_CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT_STUFFING) )

/**
  * @brief CAN Interrupt Line definition.
  */
#define LL_CAN_IntLineTypeDef                               LL_RSV_DATA_TYPE    

#define LL_CAN_INT_LINE_0                                   (0UL)                /*!< CAN Interrupt Line CANx_INT0                     */
#define LL_CAN_INT_LINE_1                                   (1UL)                /*!< CAN Interrupt Line CANx_INT1                     */

#define IS_LL_CAN_INT_LINE(__VAL__)                         (((__VAL__) == LL_CAN_INT_LINE_0) || \
                                                             ((__VAL__) == LL_CAN_INT_LINE_1) )

/**
  * @brief CAN Acceptance Mode definition.
  */
#define LL_CAN_AcceptModeTypeDef                            LL_RSV_DATA_TYPE    

#define LL_CAN_ACCEPT_MODE_AND                              (1UL)                /*!< Range of CAN filter matching is ID=ACODE_X &     \
                                                                                      ~AMASK_X                                         */
#define LL_CAN_ACCEPT_MODE_OR                               (2UL)                /*!< Range of CAN filter matching is ID=ACODE_X or    \
                                                                                      ID=AMASK_X                                       */
#define LL_CAN_ACCEPT_MODE_RANGE                            (4UL)                /*!< Range of CAN filter matching is ACODE_X <= ID <= \
                                                                                      AMASK_X                                          */
#define LL_CAN_ACCEPT_MODE_AND_EIDM                         (9UL)                /*!< Range of CAN filter matching is ID=(ACODE_X &    \
                                                                                      ~AMASK_X) and support EIDM                       */
#define LL_CAN_ACCEPT_MODE_OR_EIDM                          (10UL)               /*!< Range of CAN filter matching is ID=ACODE_X or    \
                                                                                      ID=AMASK_X and support EIDM                      */
#define LL_CAN_ACCEPT_MODE_RANGE_EIDM                       (12UL)               /*!< Range of CAN filter matching is ACODE_X <= ID <= \
                                                                                      AMASK_X and support EIDM                         */

#define IS_LL_CAN_ACCEPT_MODE(__VAL__)                      (((__VAL__) == LL_CAN_ACCEPT_MODE_AND)        || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_MODE_OR)         || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_MODE_RANGE)      || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_MODE_AND_EIDM)   || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_MODE_OR_EIDM)    || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_MODE_RANGE_EIDM) )

/**
  * @brief CAN Acceptance Control definition.
  */
#define LL_CAN_AcceptCtrlTypeDef                            LL_RSV_DATA_TYPE    

#define LL_CAN_ACCEPT_CTRL_NONE                             (0UL)                /*!< CAN filter match, no action                      */
#define LL_CAN_ACCEPT_CTRL_STORE_PRB                        (1UL)                /*!< CAN filter match, data store in PRB              */
#define LL_CAN_ACCEPT_CTRL_STORE_SRB                        (2UL)                /*!< CAN filter match, data store in SRB              */
#define LL_CAN_ACCEPT_CTRL_UPD_PRIO_STA_REG                 (4UL)                /*!< CAN filter match, update priority status         \
                                                                                      register                                         */
#define LL_CAN_ACCEPT_CTRL_STORE_PRB_UPD_PRIO_STA_REG       (5UL)                /*!< CAN filter match, data store in PRB and update   \
                                                                                      priority status register                         */
#define LL_CAN_ACCEPT_CTRL_STORE_SRB_UPD_PRIO_STA_REG       (6UL)                /*!< CAN filter match, data store in SRB and update   \
                                                                                      priority status register                         */

#define IS_LL_CAN_ACCEPT_CTRL(__VAL__)                      (((__VAL__) == LL_CAN_ACCEPT_CTRL_NONE)                       || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_CTRL_STORE_PRB)                  || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_CTRL_STORE_SRB)                  || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_CTRL_UPD_PRIO_STA_REG)           || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_CTRL_STORE_PRB_UPD_PRIO_STA_REG) || \
                                                             ((__VAL__) == LL_CAN_ACCEPT_CTRL_STORE_SRB_UPD_PRIO_STA_REG) )

/**
  * @brief CAN Timestamp Timebase definition.
  */
#define LL_CAN_TimestampTimebaseTypeDef                     LL_RSV_DATA_TYPE    

#define LL_CAN_TIMESTAMP_TIMEBASE_CLOSE                     (0UL)                /*!< CAN Timestamp Timebase close                     */
#define LL_CAN_TIMESTAMP_TIMEBASE_INT_TSC                   (1UL)                /*!< CAN Timestamp Timebase interior TSC              */
#define LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR0                  (2UL)                /*!< CAN Timestamp Timebase external timer 0          */
#define LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR1                  (4UL)                /*!< CAN Timestamp Timebase external timer 1          */
#define LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR2                  (8UL)                /*!< CAN Timestamp Timebase external timer 2          */

#define IS_LL_CAN_TIMESTAMP_TIMEBASE(__VAL__)               (((__VAL__) == LL_CAN_TIMESTAMP_TIMEBASE_CLOSE)    || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_TIMEBASE_INT_TSC)  || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR0) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR1) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_TIMEBASE_EXT_TMR2) )

/**
  * @brief CAN Timestamp Prescaler definition.
  */
#define LL_CAN_TimestampPrescalerTypeDef                    LL_RSV_DATA_TYPE    

#define LL_CAN_TIMESTAMP_PRESCALER_1                        (0UL)                /*!< Timestamp Prescaler 1                            */
#define LL_CAN_TIMESTAMP_PRESCALER_2                        (1UL)                /*!< Timestamp Prescaler 2                            */
#define LL_CAN_TIMESTAMP_PRESCALER_3                        (2UL)                /*!< Timestamp Prescaler 3                            */
#define LL_CAN_TIMESTAMP_PRESCALER_4                        (3UL)                /*!< Timestamp Prescaler 4                            */
#define LL_CAN_TIMESTAMP_PRESCALER_5                        (4UL)                /*!< Timestamp Prescaler 5                            */
#define LL_CAN_TIMESTAMP_PRESCALER_6                        (5UL)                /*!< Timestamp Prescaler 6                            */
#define LL_CAN_TIMESTAMP_PRESCALER_7                        (6UL)                /*!< Timestamp Prescaler 7                            */
#define LL_CAN_TIMESTAMP_PRESCALER_8                        (7UL)                /*!< Timestamp Prescaler 8                            */
#define LL_CAN_TIMESTAMP_PRESCALER_9                        (8UL)                /*!< Timestamp Prescaler 9                            */
#define LL_CAN_TIMESTAMP_PRESCALER_10                       (9UL)                /*!< Timestamp Prescaler 10                           */
#define LL_CAN_TIMESTAMP_PRESCALER_11                       (10UL)               /*!< Timestamp Prescaler 11                           */
#define LL_CAN_TIMESTAMP_PRESCALER_12                       (11UL)               /*!< Timestamp Prescaler 12                           */
#define LL_CAN_TIMESTAMP_PRESCALER_13                       (12UL)               /*!< Timestamp Prescaler 13                           */
#define LL_CAN_TIMESTAMP_PRESCALER_14                       (13UL)               /*!< Timestamp Prescaler 14                           */
#define LL_CAN_TIMESTAMP_PRESCALER_15                       (14UL)               /*!< Timestamp Prescaler 15                           */
#define LL_CAN_TIMESTAMP_PRESCALER_16                       (15UL)               /*!< Timestamp Prescaler 16                           */

#define IS_CAN_TIMESTAMP_PRESCALER(__VAL__)                 (((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_1 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_2 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_3 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_4 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_5 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_6 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_7 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_8 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_9 ) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_10) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_11) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_12) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_13) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_14) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_15) || \
                                                             ((__VAL__) == LL_CAN_TIMESTAMP_PRESCALER_16) )

/**
  * @brief CAN Timeout Counter definition.
  */
#define LL_CAN_TimeoutCntrTypeDef                           LL_RSV_DATA_TYPE    

#define LL_CAN_TIMEOUT_CNTR_CONT                            (0UL)                /*!< CAN Timeout Counter Continuous                   */
#define LL_CAN_TIMEOUT_CNTR_PRB                             (1UL)                /*!< CAN Timeout Counter PRB                          */
#define LL_CAN_TIMEOUT_CNTR_SRB                             (2UL)                /*!< CAN Timeout Counter SRB                          */
#define LL_CAN_TIMEOUT_CNTR_ETB                             (3UL)                /*!< CAN Timeout Counter Tx Event                     */

#define IS_LL_CAN_TIMEOUT_CNTR(__VAL__)                     (((__VAL__) == LL_CAN_TIMEOUT_CNTR_CONT) || \
                                                             ((__VAL__) == LL_CAN_TIMEOUT_CNTR_PRB)  || \
                                                             ((__VAL__) == LL_CAN_TIMEOUT_CNTR_SRB)  || \
                                                             ((__VAL__) == LL_CAN_TIMEOUT_CNTR_ETB)  )

/**
  * @brief CAN Rx Buffer Work Mode definition.
  */
#define LL_CAN_RxBufWorkModeTypeDef                         LL_RSV_DATA_TYPE    

#define LL_CAN_RX_BUF_WORK_MODE_COVER                       (0UL)                /*!< Rx buffer work mode Cover                        */
#define LL_CAN_RX_BUF_WORK_MODE_BLOCK                       (1UL)                /*!< Rx buffer work mode Block                        */

#define IS_LL_CAN_RX_BUF_WORK_MODE(__VAL__)                 (((__VAL__) == LL_CAN_RX_BUF_WORK_MODE_COVER) || \
                                                             ((__VAL__) == LL_CAN_RX_BUF_WORK_MODE_BLOCK) )

/**
  * @brief CAN Reset State definition.
  */
#define LL_CAN_RstStateTypeDef                              LL_RSV_DATA_TYPE    

#define LL_CAN_RST_STATE_NOT_RESET                          (0UL)                /*!< CAN no reset occurred                            */
#define LL_CAN_RST_STATE_HAS_RESET                          (1UL)                /*!< CAN already reset                                */

#define IS_LL_CAN_RST_STATE(__VAL__)                        (((__VAL__) == LL_CAN_RST_STATE_NOT_RESET) || \
                                                             ((__VAL__) == LL_CAN_RST_STATE_HAS_RESET) )

/**
  * @brief CAN Bus State definition.
  */
#define LL_CAN_BusStateTypeDef                              LL_RSV_DATA_TYPE    

#define LL_CAN_BUS_STATE_BUSON                              (0UL)                /*!< Bus state bus-on                                 */
#define LL_CAN_BUS_STATE_BUSOFF                             (1UL)                /*!< Bus state bus-off                                */

#define IS_LL_CAN_BUS_STATE(__VAL__)                        (((__VAL__) == LL_CAN_BUS_STATE_BUSON)  || \
                                                             ((__VAL__) == LL_CAN_BUS_STATE_BUSOFF) )

/**
  * @brief CAN RX FD Status definition.
  */
#define LL_CAN_RxFDStatusTypeDef                            LL_RSV_DATA_TYPE    

#define LL_CAN_RX_FD_STATUS_DATA_FRAME                      (BIT(1))             /*!< CAN FD data frame                                */
#define LL_CAN_RX_FD_STATUS_ACC_FRAME                       (BIT(0))             /*!< CAN FD accelerated frame                         */
#define LL_CAN_RX_FD_STATUS_EXT_FRAME                       (BIT(3))             /*!< CAN FD extend frame                              */
#define LL_CAN_RX_FD_STATUS_DATA_FRAME_PROT_MISMATCH        (BIT(2))             /*!< CAN FD data frame protocol mismatching           */


/**
  * @brief CAN Frame Format definition.
  */
#define LL_CAN_FrmFmtTypeDef                                LL_RSV_DATA_TYPE    

#define LL_CAN_FRAME_FORMAT_STD_CAN                         (0UL)                /*!< CAN 2.0 Frame Format                             */
#define LL_CAN_FRAME_FORMAT_FD_CAN                          (1UL)                /*!< CAN FD Frame Format                              */

#define IS_LL_CAN_FRAME_FORMAT(__VAL__)                     (((__VAL__) == LL_CAN_FRAME_FORMAT_STD_CAN) || \
                                                             ((__VAL__) == LL_CAN_FRAME_FORMAT_FD_CAN)  )

/**
  * @brief CAN ID Extension type definition.
  */
#define LL_CAN_IdExtTypeDef                                 LL_RSV_DATA_TYPE    

#define LL_CAN_ID_EXT_STANDARD                              (0UL)                /*!< CAN Standard Frame                             */
#define LL_CAN_ID_EXT_EXTENDED                              (1UL)                /*!< CAN Extended Frame                             */

#define IS_LL_CAN_ID_EXT(__VAL__)                           (((__VAL__) == LL_CAN_ID_EXT_STANDARD)  || \
                                                             ((__VAL__) == LL_CAN_ID_EXT_EXTENDED)  )

/**
  * @brief CAN Transmission Request type definition.
  */
#define LL_CAN_TransReqTypeDef                              LL_RSV_DATA_TYPE    

#define LL_CAN_TRANS_REQ_DATA                               (0UL)                /*!< CAN Data Frame                                  */
#define LL_CAN_TRANS_REQ_REMOTE                             (1UL)                /*!< CAN Remote Frame                                */

#define IS_LL_CAN_TRANS_REQ(__VAL__)                        (((__VAL__) == LL_CAN_TRANS_REQ_DATA)   || \
                                                             ((__VAL__) == LL_CAN_TRANS_REQ_REMOTE) )

/**
  * @brief CAN Bit Rate Switch type definition.
  */
#define LL_CAN_BitRateSwTypeDef                             LL_RSV_DATA_TYPE    

#define LL_CAN_BIT_RATE_SWITCH_OFF                          (0UL)                /*!< CAN Bit Rate Switch Off                         */
#define LL_CAN_BIT_RATE_SWITCH_ON                           (1UL)                /*!< CAN Bit Rate Switch On                          */

#define IS_LL_CAN_BIT_RATE_SWITCH(__VAL__)                  (((__VAL__) == LL_CAN_BIT_RATE_SWITCH_OFF) || \
                                                             ((__VAL__) == LL_CAN_BIT_RATE_SWITCH_ON)  )

/**
  * @brief CAN Tx Event type definition.
  */
#define LL_CAN_TxEvtTypeDef                                 LL_RSV_DATA_TYPE    

#define LL_CAN_TX_EVT_NO                                    (0UL)                /*!< CAN Do not store Tx events                     */
#define LL_CAN_TX_EVT_STORE                                 (1UL)                /*!< CAN Store Tx events                            */

#define IS_LL_CAN_TX_EVT(__VAL__)                           (((__VAL__) == LL_CAN_TX_EVT_NO)    || \
                                                             ((__VAL__) == LL_CAN_TX_EVT_STORE) )

/**
  * @brief CAN Error State Indicator definition.
  */
#define LL_CAN_ErrStaIndTypeDef                             LL_RSV_DATA_TYPE    

#define LL_CAN_ERR_STATE_IND_ACTIVE                         (0UL)                /*!< CAN FD Error State Indicator Active              */
#define LL_CAN_ERR_STATE_IND_PASSIVE                        (1UL)                /*!< CAN FD Error State Indicator Passive             */

#define IS_LL_CAN_ERR_STATE_IND(__VAL__)                    (((__VAL__) == LL_CAN_ERR_STATE_IND_ACTIVE)  || \
                                                             ((__VAL__) == LL_CAN_ERR_STATE_IND_PASSIVE) )


/**
  * @}
  */ /* CAN_LL_EC_Configuration */

/**
  * @}
  */ /* CAN_LL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Macros CAN LL Exported Macros
  * @brief    CAN LL Exported Macros
  * @{
  */

/**
  * @brief CAN frame ID format to 11 bits
  */
#define LL_CAN_FRAME_ID_FORMAT_11BITS(__VAL__)              ((__VAL__) & 0x7FFUL)

/**
  * @brief CAN frame ID format to 29 bits
  */
#define LL_CAN_FRAME_ID_FORMAT_29BITS(__VAL__)              ((__VAL__) & 0x1FFFFFFFUL)

/**
  * @}
  */ /* CAN_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Functions CAN LL Functions
  * @brief    CAN LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_CAN_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_CAN_ASSERT_INLINE_PARAM == 1)
extern void LL_CAN_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_CAN_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_CAN_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_CAN_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup CAN_LL_EF_Configuration LL CAN Configuration
  * @brief    LL CAN Configuration
  * @{
  */

/**
  * @brief  RX buffer almost full warning limit set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value @ref LL_CAN_BufAlmostFullLimitTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetAlmostFullWarningLimit(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->CTRL, CAN0_CTRL_AFWL_Msk, (((Val) & CAN0_CTRL_AFWL_Val) << CAN0_CTRL_AFWL_Pos));
}

/**
  * @brief  Error warning limit set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value @ref LL_CAN_ErrWarnLimitTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetErrorWarningLimit(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->CTRL, CAN0_CTRL_EWL_Msk, (((Val) & CAN0_CTRL_EWL_Val) << CAN0_CTRL_EWL_Pos));
}

/**
  * @brief  ETB buffer release
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_ReleaseBuffer(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_EREL_Msk);
}

/**
  * @brief  Judge is ETB buffer release complete or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 ETB buffer release doing
  * @retval 1 ETB buffer release done
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_IsBufferReleaseDone(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((!READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_EREL_Msk, CAN0_CTRL_EREL_Pos)));
}

/**
  * @brief  ETB buffer release wait
  * @note   Do not define local variables inside this macro.
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_WaitBufferRelease(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_EREL_Msk); 
    while (READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_EREL_Msk, CAN0_CTRL_EREL_Pos)); 
}

/**
  * @brief  SRB buffer release
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_ReleaseBuffer(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_SREL_Msk);
}

/**
  * @brief  Judge is SRB buffer release complete or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 SRB buffer release doing
  * @retval 1 SRB buffer release done
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_IsBufferReleaseDone(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((!READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_SREL_Msk, CAN0_CTRL_SREL_Pos)));
}

/**
  * @brief  SRB buffer release wait
  * @note   Do not define local variables inside this macro.
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_WaitBufferRelease(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_SREL_Msk); 
    while (READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_SREL_Msk, CAN0_CTRL_SREL_Pos));
}

/**
  * @brief  PRB buffer release
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_ReleaseBuffer(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_RREL_Msk);
}

/**
  * @brief  Judge is PRB buffer release complete or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 PRB buffer release doing
  * @retval 1 PRB buffer release done
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_IsBufferReleaseDone(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((!READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_RREL_Msk, CAN0_CTRL_RREL_Pos)));
}

/**
  * @brief  PRB buffer release wait
  * @note   Do not define local variables inside this macro.
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_WaitBufferRelease(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_RREL_Msk); 
    while (READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_RREL_Msk, CAN0_CTRL_RREL_Pos));
}

/**
  * @brief  CAN FD Enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableFD(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_FD_EN_Msk);
}

/**
  * @brief  CAN FD Disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableFD(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_FD_EN_Msk);
}

/**
  * @brief  Judge is CAN FD Enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 CAN FD is Disable
  * @retval 1 CAN FD is Enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsFDEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_FD_EN_Msk, CAN0_CTRL_FD_EN_Pos));
}

/**
  * @brief  CAN FD ISO Enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableFD_ISO(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_FD_ISO_Msk);
}

/**
  * @brief  CAN FD ISO Disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableFD_ISO(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_FD_ISO_Msk);
}

/**
  * @brief  TX secondary buffer next set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_SetBufferNext(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TSNEXT_Msk);
}

/**
  * @brief  TX secondary buffer next get
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Not action
  * @retval 1 TX secondary buffer next
  */
__STATIC_INLINE uint32_t LL_CAN_STB_GetBufferNext(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_TSNEXT_Msk, CAN0_CTRL_TSNEXT_Pos));
}

/**
  * @brief  Protocol Exception Detect Disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_AssertProtocolExceptionDetectDisable(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_PEDT_Msk);
}

/**
  * @brief  Protocol Exception Detect Enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ReleaseProtocolExceptionDetectDisable(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_PEDT_Msk);
}

/**
  * @brief  Judge is Protocol Exception Detect Disable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Protocol Exception Detect Enable
  * @retval 1 Protocol Exception Detect Disable
  */
__STATIC_INLINE uint32_t LL_CAN_IsProtocolExceptionDetectDisabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_PEDT_Msk, CAN0_CTRL_PEDT_Pos));
}

/**
  * @brief  RX Receive Multiplexer Set
  * @param  CANx Specifies CAN peripheral
  * @param  Muxsel Rx Receive Multiplexer select @ref LL_CAN_RxMuxSelTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetRxMuxSelect(CAN_TypeDef *CANx, uint32_t Muxsel)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->CTRL, CAN0_CTRL_MUXSEL_Msk, (((Muxsel) & CAN0_CTRL_MUXSEL_Val) << CAN0_CTRL_MUXSEL_Pos));
}

/**
  * @brief  TX buffer select PTB
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SelectTxBufferPTB(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_TBSEL_Msk);
    (void)READ_REG(CANx->CTRL);
}

/**
  * @brief  TX buffer select STB
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SelectTxBufferSTB(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TBSEL_Msk);
    (void)READ_REG(CANx->CTRL);
}

/**
  * @brief  TX buffer select PTB or not
  * @param  CANx Specifies CAN peripheral
  * @retval 1 Select PTB Buffer
  * @retval 0 Select STB Buffer
  */
__STATIC_INLINE uint32_t LL_CAN_IsTxBufferSelectPTB(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((!READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_TBSEL_Msk, CAN0_CTRL_TBSEL_Pos)));
}

/**
  * @brief  Listen only mode enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableListenOnlyMode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_LOM_Msk);
}

/**
  * @brief  Listen only mode disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableListenOnlyMode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_LOM_Msk);
}

/**
  * @brief  Judge is Listen only mode enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Listen only mode enable
  * @retval 1 Is Listen only mode enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsListenOnlyModeEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((READ_BIT(CANx->CTRL, CAN0_CTRL_LOM_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  TX primary enable set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PTB_StartTransmission(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TPE_Msk);
}

/**
  * @brief  TX primary enable get
  * @param  CANx Specifies CAN peripheral
  * @return TX primary enable status
  */
__STATIC_INLINE uint32_t LL_CAN_PTB_IsTransmissionStarted(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_TPE_Msk, CAN0_CTRL_TPE_Pos));
}

/**
  * @brief  TX primary abort set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PTB_SetTransmissionAbort(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->CTRL, CAN0_CTRL_TPA_Msk | CAN0_CTRL_TPE_Msk, CAN0_CTRL_TPA_Msk);
}

/**
  * @brief  TX secondary one frame set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_StartTransmitOneFrame(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TSONE_Msk);
}

/**
  * @brief  TX secondary one frame status get
  * @param  CANx Specifies CAN peripheral
  * @return TX secondary one status
  */
__STATIC_INLINE uint32_t LL_CAN_STB_IsTransmitOneFrameComplete(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_TSONE_Msk, CAN0_CTRL_TSONE_Pos));
}

/**
  * @brief  TX secondary all set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_StartTransmitAllFrames(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TSALL_Msk);
}

/**
  * @brief  TX secondary all get
  * @param  CANx Specifies CAN peripheral
  * @return TX secondary send all status
  */
__STATIC_INLINE uint32_t LL_CAN_STB_IsTransmitAllFramesComplete(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_TSALL_Msk, CAN0_CTRL_TSALL_Pos));
}

/**
  * @brief  TX secondary abort set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_SetTransmissionAbort(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->CTRL, CAN0_CTRL_TSA_Msk | CAN0_CTRL_TSALL_Msk | CAN0_CTRL_TSONE_Msk, CAN0_CTRL_TSA_Msk);
}

/**
  * @brief  CAN reset set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetReset(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_RESET_Msk);
}

/**
  * @brief  CAN reset clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearReset(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_RESET_Msk);
}

/**
  * @brief  CAN reset status get
  * @param  CANx Specifies CAN peripheral
  * @return Reset status @ref LL_CAN_RstStateTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetResetState(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTRL, CAN0_CTRL_RESET_Msk, CAN0_CTRL_RESET_Pos));
}

/**
  * @brief  CAN loop back mode external enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableLoopBackModeExternal(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_LBME_Msk);
}

/**
  * @brief  CAN loop back mode external disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableLoopBackModeExternal(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_LBME_Msk);
}

/**
  * @brief  CAN loop back mode internal enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableLoopBackModeInternal(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_LBMI_Msk);
}

/**
  * @brief  CAN loop back mode internal disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableLoopBackModeInternal(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_LBMI_Msk);
}

/**
  * @brief  CAN operating  mode reset
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ResetOperationMode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, LL_CAN_CTRL_OP_MODE_MSK);
}

/**
  * @brief  CAN TX primary single shot enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PTB_EnableSingleShotMode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TPSS_Msk);
}

/**
  * @brief  CAN TX primary single shot disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PTB_DisableSingleShotMode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_TPSS_Msk);
}

/**
  * @brief  CAN TX secondary single shot enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_EnableSingleShotMode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TSSS_Msk);
}

/**
  * @brief  CAN TX secondary single shot disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_DisableSingleShotMode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTRL, CAN0_CTRL_TSSS_Msk);
}

/**
  * @brief  SRB Almost Full Warning Limit set
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the SFIF flag is also set.
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value @ref LL_CAN_BufAlmostFullLimitTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetAlmostFullWarningLimit(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->STATUS, CAN0_STATUS_SAFWL_Msk, (((Val) & CAN0_STATUS_SAFWL_Val) << CAN0_STATUS_SAFWL_Pos));
}

/**
  * @brief  SRB Almost Full Warning Limit get
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the SFIF flag is also set.
  * @param  CANx Specifies CAN peripheral
  * @return SRB Message Max Quantity @ref LL_CAN_BufAlmostFullLimitTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetAlmostFullWarningLimit(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_SAFWL_Msk, CAN0_STATUS_SAFWL_Pos));
}

/**
  * @brief  ETB Almost Full Warning Limit set
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the EFIF flag is also set.
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value @ref LL_CAN_BufAlmostFullLimitTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_SetAlmostFullWarningLimit(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->STATUS, CAN0_STATUS_EAFWL_Msk, (((Val) & CAN0_STATUS_EAFWL_Val) << CAN0_STATUS_EAFWL_Pos));
}

/**
  * @brief  ETB Almost Full Warning Limit get
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the EFIF flag is also set.
  * @param  CANx Specifies CAN peripheral
  * @return ETB Message Max Quantity @ref LL_CAN_BufAlmostFullLimitTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetAlmostFullWarningLimit(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_EAFWL_Msk, CAN0_STATUS_EAFWL_Pos));
}

/**
  * @brief  STB Almost Empty Warning Limit set
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the TAEIF flag is also set.
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value @ref LL_CAN_BufAlmostEmptyLimitTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_SetAlmostEmptyWarningLimit(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->STATUS, CAN0_STATUS_AEWL_Msk, (((Val) & CAN0_STATUS_AEWL_Val) << CAN0_STATUS_AEWL_Pos));
}

/**
  * @brief  STB Almost Empty Warning Limit get
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the TAEIF flag is also set.
  * @param  CANx Specifies CAN peripheral
  * @return STB Message Max Quantity @ref LL_CAN_BufAlmostEmptyLimitTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_STB_GetAlmostEmptyWarningLimit(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_AEWL_Msk, CAN0_STATUS_AEWL_Pos));
}

/**
  * @brief  Judge is PRB buffer overflow or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't PRB buffer overflow
  * @retval 1 Is PRB buffer overflow
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_IsRxBufferOverflow(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_ROV_Msk, CAN0_STATUS_ROV_Pos));
}

/**
  * @brief  PRB buffer status get
  * @param  CANx Specifies CAN peripheral
  * @return PRB buffer status @ref LL_CAN_RxBufStaTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetRxBufferStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_RSTAT_Msk, CAN0_STATUS_RSTAT_Pos));
}

/**
  * @brief  Judge is SRB Receive Buffer Overflow or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Receive Buffer Overflow
  * @retval 1 Is SRB Receive Buffer Overflow
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_IsRxBufferOverflow(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_SOV_Msk, CAN0_STATUS_SOV_Pos));
}

/**
  * @brief  SRB Receive Buffer Overflow status get
  * @param  CANx Specifies CAN peripheral
  * @return SRB buffer status @ref LL_CAN_RxBufStaTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetRxBufferStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_SSTAT_Msk, CAN0_STATUS_SSTAT_Pos));
}

/**
  * @brief  TX secondary status get
  * @param  CANx Specifies CAN peripheral
  * @return Number of secondary buffer filled messages
  */
__STATIC_INLINE uint32_t LL_CAN_STB_GetTxBufferStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_TSSTAT_Msk, CAN0_STATUS_TSSTAT_Pos));
}

/**
  * @brief  Judge is ETB Receive Buffer Overflow or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Receive Buffer Overflow
  * @retval 1 Is ETB Receive Buffer Overflow
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_IsRxBufferOverflow(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_EOV_Msk, CAN0_STATUS_EOV_Pos));
}

/**
  * @brief  ETB Receive Buffer Overflow status get
  * @param  CANx Specifies CAN peripheral
  * @return ETB buffer status @ref LL_CAN_RxBufStaTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetRxBufferStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_ESTAT_Msk, CAN0_STATUS_ESTAT_Pos));
}

/**
  * @brief  Judge is RX active or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't RX active
  * @retval 1 Is RX active
  */
__STATIC_INLINE uint32_t LL_CAN_IsReceiveActive(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_RACTIVE_Msk, CAN0_STATUS_RACTIVE_Pos));
}

/**
  * @brief  Judge is TX active or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't TX active
  * @retval 1 Is TX active
  */
__STATIC_INLINE uint32_t LL_CAN_IsTransmitActive(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_TACTIVE_Msk, CAN0_STATUS_TACTIVE_Pos));
}

/**
  * @brief  Judge is bus off or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Is bus on
  * @retval 1 Is bus off 
  */
__STATIC_INLINE uint32_t LL_CAN_IsBusOffState(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STATUS, CAN0_STATUS_BUSOFF_Msk, CAN0_STATUS_BUSOFF_Pos));
}

/**
  * @brief  STB Empty Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_TEIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_TEIE_Msk);
}

/**
  * @brief  STB Empty Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_TEIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_TEIE_Msk);
}

/**
  * @brief  Judge is STB Empty Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't STB Empty Interrupt enable
  * @retval 1 Is STB Empty Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_TEIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_TEIE_Msk, CAN0_INTREN_TEIE_Pos));
}

/**
  * @brief  STB Almost Empty Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_TAEIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_TAEIE_Msk);
}

/**
  * @brief  STB Almost Empty Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_TAEIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_TAEIE_Msk);
}

/**
  * @brief  Judge is STB Almost Empty Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't STB Almost Empty Interrupt enable
  * @retval 1 Is STB Almost Empty Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_TAEIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_TAEIE_Msk, CAN0_INTREN_TAEIE_Pos));
}

/**
  * @brief  Priority Message Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_PMIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_PMIE_Msk);
}

/**
  * @brief  Priority Message Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_PMIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_PMIE_Msk);
}

/**
  * @brief  Judge is Priority Message Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Priority Message Interrupt enable
  * @retval 1 Is Priority Message Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_PMIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_PMIE_Msk, CAN0_INTREN_PMIE_Pos));
}

/**
  * @brief  Timestamp Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_TSCIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_TSCIE_Msk);
}

/**
  * @brief  Timestamp Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_TSCIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_TSCIE_Msk);
}

/**
  * @brief  Judge is Timestamp Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Timestamp Interrupt enable
  * @retval 1 Is Timestamp Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_TSCIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_TSCIE_Msk, CAN0_INTREN_TSCIE_Pos));
}

/**
  * @brief  PRB Timeout Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_RTOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_RTOIE_Msk);
}

/**
  * @brief  PRB Timeout Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_RTOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_RTOIE_Msk);
}

/**
  * @brief  Judge is PRB Timeout Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't PRB Timeout Interrupt enable
  * @retval 1 Is PRB Timeout Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_RTOIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_RTOIE_Msk, CAN0_INTREN_RTOIE_Pos));
}

/**
  * @brief  SRB Timeout Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_STOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_STOIE_Msk);
}

/**
  * @brief  SRB Timeout Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_STOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_STOIE_Msk);
}

/**
  * @brief  Judge is SRB Timeout Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Timeout Interrupt enable
  * @retval 1 Is SRB Timeout Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_STOIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_STOIE_Msk, CAN0_INTREN_STOIE_Pos));
}

/**
  * @brief  ETB Timeout Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_ETOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_ETOIE_Msk);
}

/**
  * @brief  ETB Timeout Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_ETOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_ETOIE_Msk);
}

/**
  * @brief  Judge is ETB Timeout Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Timeout Interrupt enable
  * @retval 1 Is ETB Timeout Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_ETOIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_ETOIE_Msk, CAN0_INTREN_ETOIE_Pos));
}

/**
  * @brief  Continuous Count Timeout Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_CTOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_CTOIE_Msk);
}

/**
  * @brief  Continuous Count Timeout Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_CTOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_CTOIE_Msk);
}

/**
  * @brief  Judge is Continuous Count Timeout Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Continuous Count Timeout Interrupt enable
  * @retval 1 Is Continuous Count Timeout Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_CTOIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_CTOIE_Msk, CAN0_INTREN_CTOIE_Pos));
}

/**
  * @brief  SRB Overrun Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_SOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_SOIE_Msk);
}

/**
  * @brief  SRB Overrun Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_SOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_SOIE_Msk);
}

/**
  * @brief  Judge is SRB Overrun Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Overrun Interrupt enable
  * @retval 1 Is SRB Overrun Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_SOIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_SOIE_Msk, CAN0_INTREN_SOIE_Pos));
}

/**
  * @brief  SRB Full Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_SFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_SFIE_Msk);
}

/**
  * @brief  SRB Full Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_SFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_SFIE_Msk);
}

/**
  * @brief  Judge is SRB Full Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Full Interrupt enable
  * @retval 1 Is SRB Full Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_SFIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_SFIE_Msk, CAN0_INTREN_SFIE_Pos));
}

/**
  * @brief  SRB Almost Full Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_SAFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_SAFIE_Msk);
}

/**
  * @brief  SRB Almost Full Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_SAFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_SAFIE_Msk);
}

/**
  * @brief  Judge is SRB Almost Full Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Almost Full Interrupt enable
  * @retval 1 Is SRB Almost Full Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_SAFIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_SAFIE_Msk, CAN0_INTREN_SAFIE_Pos));
}

/**
  * @brief  ETB Overrun Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_EOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_EOIE_Msk);
}

/**
  * @brief  ETB Overrun Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_EOIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_EOIE_Msk);
}

/**
  * @brief  Judge is ETB Overrun Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Overrun Interrupt enable
  * @retval 1 Is ETB Overrun Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_EOIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_EOIE_Msk, CAN0_INTREN_EOIE_Pos));
}

/**
  * @brief  ETB Full Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_EFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_EFIE_Msk);
}

/**
  * @brief  ETB Full Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_EFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_EFIE_Msk);
}

/**
  * @brief  Judge is ETB Full Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Full Interrupt enable
  * @retval 1 Is ETB Full Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_EFIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_EFIE_Msk, CAN0_INTREN_EFIE_Pos));
}

/**
  * @brief  ETB Almost Full Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_EAFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_EAFIE_Msk);
}

/**
  * @brief  ETB Almost Full Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_EAFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_EAFIE_Msk);
}

/**
  * @brief  Judge is ETB Almost Full Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Almost Full Interrupt enable
  * @retval 1 Is ETB Almost Full Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_EAFIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_EAFIE_Msk, CAN0_INTREN_EAFIE_Pos));
}

/**
  * @brief  Abort Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_AIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_AIE_Msk);
}

/**
  * @brief  Abort Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_AIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_AIE_Msk);
}

/**
  * @brief  Judge is Abort Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Abort Interrupt enable
  * @retval 1 Is Abort Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_AIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_AIE_Msk, CAN0_INTREN_AIE_Pos));
}

/**
  * @brief  SRB Receive Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_SRIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_SRIE_Msk);
}

/**
  * @brief  SRB Receive Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_SRIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_SRIE_Msk);
}

/**
  * @brief  Judge is SRB Receive Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Receive Interrupt enable
  * @retval 1 Is SRB Receive Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_SRIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_SRIE_Msk, CAN0_INTREN_SRIE_Pos));
}

/**
  * @brief  ETB Receive Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_ERIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_ERIE_Msk);
}

/**
  * @brief  ETB Receive Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_ERIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_ERIE_Msk);
}

/**
  * @brief  Judge is ETB Receive Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Receive Interrupt enable
  * @retval 1 Is ETB Receive Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_ERIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_ERIE_Msk, CAN0_INTREN_ERIE_Pos));
}

/**
  * @brief  Error Counter Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_ECIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_ECIE_Msk);
}

/**
  * @brief  Error Counter Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_ECIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_ECIE_Msk);
}

/**
  * @brief  Judge is Error Counter Interrupt enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Error Counter Interrupt enable
  * @retval 1 Is Error Counter Interrupt enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT_ECIE(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTREN, CAN0_INTREN_ECIE_Msk, CAN0_INTREN_ECIE_Pos));
}

/**
  * @brief  Error passive interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_EPIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_EPIE_Msk);
}

/**
  * @brief  Error passive interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_EPIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_EPIE_Msk);
}

/**
  * @brief  Arbitration lost interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_ALIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_ALIE_Msk);
}

/**
  * @brief  Arbitration lost interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_ALIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_ALIE_Msk);
}

/**
  * @brief  Bus error interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_BEIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_BEIE_Msk);
}

/**
  * @brief  Bus error interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_BEIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_BEIE_Msk);
}

/**
  * @brief  PRB interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_RIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_RIE_Msk);
}

/**
  * @brief  PRB interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_RIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_RIE_Msk);
}

/**
  * @brief  PRB buffer overrun interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_ROIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_ROIE_Msk);
}

/**
  * @brief  PRB buffer overrun interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_ROIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_ROIE_Msk);
}

/**
  * @brief  PRB buffer full interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_RFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_RFIE_Msk);
}

/**
  * @brief  PRB buffer full interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_RFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_RFIE_Msk);
}

/**
  * @brief  PRB buffer almost full interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_RAFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_RAFIE_Msk);
}

/**
  * @brief  PRB buffer almost full interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_RAFIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_RAFIE_Msk);
}

/**
  * @brief  TX primary interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_TPIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_TPIE_Msk);
}

/**
  * @brief  TX primary interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_TPIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_TPIE_Msk);
}

/**
  * @brief  TX secondary interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_TSIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_TSIE_Msk);
}

/**
  * @brief  TX secondary interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_TSIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_TSIE_Msk);
}

/**
  * @brief  Error interrupt enalbe
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT_EIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, CAN0_INTREN_EIE_Msk);
}

/**
  * @brief  Error interrupt disalbe
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT_EIE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, CAN0_INTREN_EIE_Msk);
}

/**
  * @brief  All Interrupt Disbale
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableAllInterrupts(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, LL_CAN_INTREN_IT_EN_MSK);
}

/**
  * @brief  All Interrupt Enable Status Get
  * @param  CANx Specifies CAN peripheral
  * @return All Interrupt Enable Status
  */
__STATIC_INLINE uint32_t LL_CAN_GetAllInterruptEnable(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT(CANx->INTREN, LL_CAN_INTREN_IT_EN_MSK));
}


/**
  * @brief  Judge is STB Empty Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't STB Empty Interrupt Pending
  * @retval 1 Is STB Empty Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_TEIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_TEIF_Msk, CAN0_INTRST_TEIF_Pos));
}

/**
  * @brief  STB Empty Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_TEIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TSNEXT_Msk);
}

/**
  * @brief  Judge is STB Almost Empty Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't STB Almost Empty Interrupt Pending
  * @retval 1 Is STB Almost Empty Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_TAEIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_TAEIF_Msk, CAN0_INTRST_TAEIF_Pos));
}

/**
  * @brief  STB Almost Empty Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_TAEIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTRL, CAN0_CTRL_TSNEXT_Msk);
}

/**
  * @brief  Judge is Priority Message Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Priority Message Interrupt Pending
  * @retval 1 Is Priority Message Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_PMIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_PMIF_Msk, CAN0_INTRST_PMIF_Pos));
}

/**
  * @brief  Priority Message Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_PMIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_PMIF_Msk);
}

/**
  * @brief  Judge is Timestamp Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Timestamp Interrupt Pending
  * @retval 1 Is Timestamp Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_TSCIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_TSCIF_Msk, CAN0_INTRST_TSCIF_Pos));
}

/**
  * @brief  Timestamp Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_TSCIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_TSCIF_Msk);
}

/**
  * @brief  Judge is PRB Timeout Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't PRB Timeout Interrupt Pending
  * @retval 1 Is PRB Timeout Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_RTOIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_RTOIF_Msk, CAN0_INTRST_RTOIF_Pos));
}

/**
  * @brief  PRB Timeout Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_RTOIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_RTOIF_Msk);
}

/**
  * @brief  Judge is SRB Timeout Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Timeout Interrupt Pending
  * @retval 1 Is SRB Timeout Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_STOIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_STOIF_Msk, CAN0_INTRST_STOIF_Pos));
}

/**
  * @brief  SRB Timeout Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_STOIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_STOIF_Msk);
}

/**
  * @brief  Judge is ETB Timeout Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Timeout Interrupt Pending
  * @retval 1 Is ETB Timeout Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_ETOIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_ETOIF_Msk, CAN0_INTRST_ETOIF_Pos));
}

/**
  * @brief  ETB Timeout Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_ETOIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_ETOIF_Msk);
}

/**
  * @brief  Judge is Continuous Count Timeout Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Continuous Count Timeout Interrupt Pending
  * @retval 1 Is Continuous Count Timeout Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_CTOIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_CTOIF_Msk, CAN0_INTRST_CTOIF_Pos));
}

/**
  * @brief  Continuous Count Timeout Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_CTOIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_CTOIF_Msk);
}

/**
  * @brief  Judge is SRB Overflow Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Overflow Interrupt Pending
  * @retval 1 Is SRB Overflow Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_SOIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_SOIF_Msk, CAN0_INTRST_SOIF_Pos));
}

/**
  * @brief  SRB Overflow Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_SOIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_SOIF_Msk);
}

/**
  * @brief  Judge is SRB Full Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Full Interrupt Pending
  * @retval 1 Is SRB Full Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_SFIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_SFIF_Msk, CAN0_INTRST_SFIF_Pos));
}

/**
  * @brief  SRB Full Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_SFIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_SFIF_Msk);
}

/**
  * @brief  Judge is SRB Almost Full Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Almost Full Interrupt Pending
  * @retval 1 Is SRB Almost Full Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_SAFIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_SAFIF_Msk, CAN0_INTRST_SAFIF_Pos));
}

/**
  * @brief  SRB Almost Full Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_SAFIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_SAFIF_Msk);
}

/**
  * @brief  Judge is ETB Overflow Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Overflow Interrupt Pending
  * @retval 1 Is ETB Overflow Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_EOIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_EOIF_Msk, CAN0_INTRST_EOIF_Pos));
}

/**
  * @brief  ETB Overflow Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_EOIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_EOIF_Msk);
}

/**
  * @brief  Judge is ETB Full Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Full Interrupt Pending
  * @retval 1 Is ETB Full Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_EFIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_EFIF_Msk, CAN0_INTRST_EFIF_Pos));
}

/**
  * @brief  ETB Full Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_EFIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_EFIF_Msk);
}

/**
  * @brief  Judge is ETB Almost Full Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Almost Full Interrupt Pending
  * @retval 1 Is ETB Almost Full Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_EAFIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_EAFIF_Msk, CAN0_INTRST_EAFIF_Pos));
}

/**
  * @brief  ETB Almost Full Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_EAFIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_EAFIF_Msk);
}

/**
  * @brief  Judge is error warning limit reached or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't error warning limit reached
  * @retval 1 Is error warning limit reached
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_EWARN(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_EWARN_Msk, CAN0_INTRST_EWARN_Pos));
}

/**
  * @brief  Judge is error passive mode active or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Error passive mode isn't active
  * @retval 1 Error passive mode is active
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_EPASS(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_EPASS_Msk, CAN0_INTRST_EPASS_Pos));
}

/**
  * @brief  Judge is SRB Receive Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't SRB Receive Interrupt Pending
  * @retval 1 Is SRB Receive Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_SRIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_SRIF_Msk, CAN0_INTRST_SRIF_Pos));
}

/**
  * @brief  SRB Receive Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_SRIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_SRIF_Msk);
}

/**
  * @brief  Judge is ETB Receive Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't ETB Receive Interrupt Pending
  * @retval 1 Is ETB Receive Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_ERIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_ERIF_Msk, CAN0_INTRST_ERIF_Pos));
}

/**
  * @brief  ETB Receive Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_ERIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_ERIF_Msk);
}

/**
  * @brief  Judge is Error Counter Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Error Counter Interrupt Pending
  * @retval 1 Is Error Counter Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_ECIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_ECIF_Msk, CAN0_INTRST_ECIF_Pos));
}

/**
  * @brief  Error Counter Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_ECIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_ECIF_Msk);
}

/**
  * @brief  Judge is Error Passive Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Error Passive Interrupt Pending
  * @retval 1 Is Error Passive Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_EPIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_EPIF_Msk, CAN0_INTRST_EPIF_Pos));
}

/**
  * @brief  Error Passive Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_EPIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_EPIF_Msk);
}

/**
  * @brief  Judge is Arbitration Lost Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Arbitration Lost Interrupt Pending
  * @retval 1 Is Arbitration Lost Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_ALIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_ALIF_Msk, CAN0_INTRST_ALIF_Pos));
}

/**
  * @brief  Arbitration Lost Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_ALIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_ALIF_Msk);
}

/**
  * @brief  Judge is Bus Error Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Bus Error Interrupt Pending
  * @retval 1 Is Bus Error Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_BEIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_BEIF_Msk, CAN0_INTRST_BEIF_Pos));
}

/**
  * @brief  Bus Error Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_BEIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_BEIF_Msk);
}

/**
  * @brief  Judge is PRB Receive Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't PRB Receive Interrupt Pending
  * @retval 1 Is PRB Receive Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_RIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_RIF_Msk, CAN0_INTRST_RIF_Pos));
}

/**
  * @brief  PRB Receive Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_RIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_RIF_Msk);
}

/**
  * @brief  Judge is PRB Buffer Overflow Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't PRB Buffer Overflow Interrupt Pending
  * @retval 1 Is PRB Buffer Overflow Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_ROIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_ROIF_Msk, CAN0_INTRST_ROIF_Pos));
}

/**
  * @brief  PRB Buffer Overflow Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_ROIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_ROIF_Msk);
}

/**
  * @brief  Judge is PRB Buffer Full Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't RPRBx Buffer Full Interrupt Pending
  * @retval 1 Is PRB Buffer Full Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_RFIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_RFIF_Msk, CAN0_INTRST_RFIF_Pos));
}

/**
  * @brief  PRB Buffer Full Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_RFIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_RFIF_Msk);
}

/**
  * @brief  Judge is PRB Buffer Almost Full Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't PRB Buffer Almost Full Interrupt Pending
  * @retval 1 Is PRB Buffer Almost Full Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_RAFIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_RAFIF_Msk, CAN0_INTRST_RAFIF_Pos));
}

/**
  * @brief  PRB Buffer Almost Full Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_RAFIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_RAFIF_Msk);
}

/**
  * @brief  Judge is Transmission Primary Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Transmission Primary Interrupt Pending
  * @retval 1 Is Transmission Primary Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_TPIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_TPIF_Msk, CAN0_INTRST_TPIF_Pos));
}

/**
  * @brief  Transmission Primary Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_TPIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_TPIF_Msk);
}

/**
  * @brief  Judge is Transmission Secondary Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Transmission Secondary Interrupt Pending
  * @retval 1 Is Transmission Secondary Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_TSIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_TSIF_Msk, CAN0_INTRST_TSIF_Pos));
}

/**
  * @brief  Transmission Secondary Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_TSIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_TSIF_Msk);
}

/**
  * @brief  Judge is Error Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Error Interrupt Pending
  * @retval 1 Is Error Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_EIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_EIF_Msk, CAN0_INTRST_EIF_Pos));
}

/**
  * @brief  Error Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_EIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_EIF_Msk);
}

/**
  * @brief  Judge is Abort Interrupt Pending or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Isn't Abort Interrupt Pending
  * @retval 1 Is Abort Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag_AIF(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRST, CAN0_INTRST_AIF_Msk, CAN0_INTRST_AIF_Pos));
}

/**
  * @brief  Abort Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag_AIF(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, CAN0_INTRST_AIF_Msk);
}

/**
  * @brief  Interrupt status get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt status
  */
__STATIC_INLINE uint32_t LL_CAN_GetAllITPending(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT(CANx->INTRST, LL_CAN_INTRST_IT_FLAG_MSK));
}

/**
  * @brief  All Interrupt Pending Clear
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearAllITPending(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, LL_CAN_INTRST_IT_W1C_FLAG_MSK);
}

/**
  * @brief  Fast speed bit timing segment1 set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_FS_SetBitTimingSeg1(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->BITTIME, CAN0_BITTIME_F_SEG1_Msk, (((Val) & CAN0_BITTIME_F_SEG1_Val) << CAN0_BITTIME_F_SEG1_Pos));
}

/**
  * @brief  Slow speed synchronization jump width set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_SS_SetSyncJumpWidth(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->BITTIME, CAN0_BITTIME_S_SJW_Msk, (((Val) & CAN0_BITTIME_S_SJW_Val) << CAN0_BITTIME_S_SJW_Pos));
}

/**
  * @brief  Fast speed bit timing segment2 set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_FS_SetBitTimingSeg2(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->BITTIME, CAN0_BITTIME_F_SEG2_Msk, (((Val) & CAN0_BITTIME_F_SEG2_Val) << CAN0_BITTIME_F_SEG2_Pos));
}

/**
  * @brief  Slow speed bit timing segment2 set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_SS_SetBitTimingSeg2(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->BITTIME, CAN0_BITTIME_S_SEG2_Msk, (((Val) & CAN0_BITTIME_S_SEG2_Val) << CAN0_BITTIME_S_SEG2_Pos));
}

/**
  * @brief  Fast speed synchronization jump width set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_FS_SetSyncJumpWidth(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->BITTIME, CAN0_BITTIME_F_SJW_Msk, (((Val) & CAN0_BITTIME_F_SJW_Val) << CAN0_BITTIME_F_SJW_Pos));
}

/**
  * @brief  Slow speed bit timing segment1 set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_SS_SetBitTimingSeg1(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->BITTIME, CAN0_BITTIME_S_SEG1_Msk, (((Val) & CAN0_BITTIME_S_SEG1_Val) << CAN0_BITTIME_S_SEG1_Pos));
}

/**
  * @brief  Fast speed prescaler set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_FS_SetPrescaler(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->PRESC, CAN0_PRESC_F_PRESC_Msk, (((Val) & CAN0_PRESC_F_PRESC_Val) << CAN0_PRESC_F_PRESC_Pos));
}

/**
  * @brief  Slow speed prescaler set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_SS_SetPrescaler(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->PRESC, CAN0_PRESC_S_PRESC_Msk, (((Val) & CAN0_PRESC_S_PRESC_Val) << CAN0_PRESC_S_PRESC_Pos));
}

/**
  * @brief  RX error count get
  * @param  CANx Specifies CAN peripheral
  * @return RX error count
  */
__STATIC_INLINE uint32_t LL_CAN_GetRxErrorCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ERRST, CAN0_ERRST_RECNT_Msk, CAN0_ERRST_RECNT_Pos));
}

/**
  * @brief  TX error count get
  * @param  CANx Specifies CAN peripheral
  * @return TX error count
  */
__STATIC_INLINE uint32_t LL_CAN_GetTxErrorCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ERRST, CAN0_ERRST_TECNT_Msk, CAN0_ERRST_TECNT_Pos));
}

/**
  * @brief  RX and TX error count get
  * @param  CANx Specifies CAN peripheral
  * @return TX error count
  */
__STATIC_INLINE uint32_t LL_CAN_GetRxTxErrorCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ERRST, CAN0_ERRST_ECNT_Msk, CAN0_ERRST_ECNT_Pos));
}

/**
  * @brief  Error code get
  * @param  CANx Specifies CAN peripheral
  * @return Error Status @ref LL_CAN_ErrStatusTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetErrorCode(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ERRST, CAN0_ERRST_KOER_Msk, CAN0_ERRST_KOER_Pos));
}

/**
  * @brief  Arbitration lost capture get
  * @param  CANx Specifies CAN peripheral
  * @return bit position in the frame where the arbitration has been lost
  */
__STATIC_INLINE uint32_t LL_CAN_GetArbitrationLostCapture(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ERRST, CAN0_ERRST_ALC_Msk, CAN0_ERRST_ALC_Pos));
}

/**
  * @brief  Data Kind Of Error get
  * @param  CANx Specifies CAN peripheral
  * @return Data Kind Of Error @ref LL_CAN_DatFieldErrTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetDataErrorType(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->PRTST, CAN0_PRTST_DKOER_Msk, CAN0_PRTST_DKOER_Pos));
}

/**
  * @brief  Data Kind Of Error Extract
  * @param  Info CAN Protocol Status @ref LL_CAN_ReadProtocolStatusRegister
  * @return Data Kind Of Error @ref LL_CAN_DatFieldErrTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractDataErrorType(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, CAN0_PRTST_DKOER_Msk, CAN0_PRTST_DKOER_Pos));
}

/**
  * @brief  CAN RX FD Status get
  * @param  CANx Specifies CAN peripheral
  * @retval 0010b CAN FD Data Frame
  * @retval 0011b CAN FD Accelerated Data Frame
  * @retval 1010b CAN FD Extend Data Frame
  * @retval 1011b CAN FD Extend Accelerated Data Frame
  * @retval x1xxb CAN FD Data Frame Protocol Error
  */
__STATIC_INLINE uint32_t LL_CAN_GetRxFDDatFrameType(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->PRTST, CAN0_PRTST_FDSTS_Msk, CAN0_PRTST_FDSTS_Pos));
}

/**
  * @brief  CAN RX FD Status Extract
  * @param  Info CAN Protocol Status 
  *             @ref LL_CAN_ReadProtocolStatusRegister 
  *             @ref LL_CAN_RxFDStatusTypeDef
  * @retval 0010b CAN FD Data Frame
  * @retval 0011b CAN FD Accelerated Data Frame
  * @retval 1010b CAN FD Extend Data Frame
  * @retval 1011b CAN FD Extend Accelerated Data Frame
  * @retval x1xxb CAN FD Data Frame Protocol Error
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxFDDatFrameType(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, CAN0_PRTST_FDSTS_Msk, CAN0_PRTST_FDSTS_Pos));
}

/**
  * @brief  CAN Node Status get
  * @param  CANx Specifies CAN peripheral
  * @return CAN Node Status @ref LL_CAN_NodeStaTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetNodeStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->PRTST, CAN0_PRTST_NDSTS_Msk, CAN0_PRTST_NDSTS_Pos));
}

/**
  * @brief  CAN Node Status Extract
  * @param  Info CAN Protocol Status @ref LL_CAN_ReadProtocolStatusRegister
  * @return CAN Node Status @ref LL_CAN_NodeStaTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractNodeStatus(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, CAN0_PRTST_NDSTS_Msk, CAN0_PRTST_NDSTS_Pos));
}

/**
  * @brief  CAN RX Frame Store Mode get
  * @param  CANx Specifies CAN peripheral
  * @return CAN RX Frame Store Mode @ref LL_CAN_FrmStoreModeTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetRxFrameStoreMode(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->PRTST, CAN0_PRTST_RBSTS_Msk, CAN0_PRTST_RBSTS_Pos));
}

/**
  * @brief  CAN RX Frame Store Mode Extract
  * @param  Info CAN Protocol Status @ref LL_CAN_ReadProtocolStatusRegister
  * @return CAN RX Frame Store Mode @ref LL_CAN_FrmStoreModeTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxFrameStoreMode(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, CAN0_PRTST_RBSTS_Msk, CAN0_PRTST_RBSTS_Pos));
}

/**
  * @brief  CAN Protocol Status Register read
  * @param  CANx Specifies CAN peripheral
  * @return CAN Protocol Status
  */
__STATIC_INLINE uint32_t LL_CAN_ReadProtocolStatusRegister(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->PRTST));
}

/**
  * @brief  STB Empty Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_SetEmptyInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_TEILS_Msk, (((Line) & CAN0_INTRLS_TEILS_Val) << CAN0_INTRLS_TEILS_Pos));
}

/**
  * @brief  STB Empty Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_STB_GetEmptyInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_TEILS_Msk, CAN0_INTRLS_TEILS_Pos));
}

/**
  * @brief  STB Almost Empty Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_SetAlmostEmptyInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_TAEILS_Msk, (((Line) & CAN0_INTRLS_TAEILS_Val) << CAN0_INTRLS_TAEILS_Pos));
}

/**
  * @brief  STB Almost Empty Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_STB_GetAlmostEmptyInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_TAEILS_Msk, CAN0_INTRLS_TAEILS_Pos));
}

/**
  * @brief  Priority Message Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetPriorityMessageInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_PMILS_Msk, (((Line) & CAN0_INTRLS_PMILS_Val) << CAN0_INTRLS_PMILS_Pos));
}

/**
  * @brief  Priority Message Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetPriorityMessageInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_PMILS_Msk, CAN0_INTRLS_PMILS_Pos));
}

/**
  * @brief  Timestamp Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetTimestampInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_TSCILS_Msk, (((Line) & CAN0_INTRLS_TSCILS_Val) << CAN0_INTRLS_TSCILS_Pos));
}

/**
  * @brief  Timestamp Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref 
  */
__STATIC_INLINE uint32_t LL_CAN_GetTimestampInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_TSCILS_Msk, CAN0_INTRLS_TSCILS_Pos));
}

/**
  * @brief  PRB Timeout Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetTimeoutInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_RTOILS_Msk, (((Line) & CAN0_INTRLS_RTOILS_Val) << CAN0_INTRLS_RTOILS_Pos));
}

/**
  * @brief  PRB Timeout Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetTimeoutInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_RTOILS_Msk, CAN0_INTRLS_RTOILS_Pos));
}

/**
  * @brief  SRB Timeout Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetTimeoutInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_STOILS_Msk, (((Line) & CAN0_INTRLS_STOILS_Val) << CAN0_INTRLS_STOILS_Pos));
}

/**
  * @brief  SRB Timeout Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetTimeoutInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_STOILS_Msk, CAN0_INTRLS_STOILS_Pos));
}

/**
  * @brief  ETB Timeout Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_SetTimeoutInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_ETOILS_Msk, (((Line) & CAN0_INTRLS_ETOILS_Val) << CAN0_INTRLS_ETOILS_Pos));
}

/**
  * @brief  ETB Timeout Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetTimeoutInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_ETOILS_Msk, CAN0_INTRLS_ETOILS_Pos));
}

/**
  * @brief  Continuous Count Timeout Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetContinuousCountTimeoutInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_CTOILS_Msk, (((Line) & CAN0_INTRLS_CTOILS_Val) << CAN0_INTRLS_CTOILS_Pos));
}

/**
  * @brief  Continuous Count Timeout Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetContinuousCountTimeoutInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_CTOILS_Msk, CAN0_INTRLS_CTOILS_Pos));
}

/**
  * @brief  SRB Overrun Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetOverrunInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_SOILS_Msk, (((Line) & CAN0_INTRLS_SOILS_Val) << CAN0_INTRLS_SOILS_Pos));
}

/**
  * @brief  SRB Overrun Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetOverrunInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_SOILS_Msk, CAN0_INTRLS_SOILS_Pos));
}

/**
  * @brief  SRB Full Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetFullInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_SFILS_Msk, (((Line) & CAN0_INTRLS_SFILS_Val) << CAN0_INTRLS_SFILS_Pos));
}

/**
  * @brief  SRB Full Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetFullInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_SFILS_Msk, CAN0_INTRLS_SFILS_Pos));
}

/**
  * @brief  SRB Almost Full Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetAlmostFullInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_SAFILS_Msk, (((Line) & CAN0_INTRLS_SAFILS_Val) << CAN0_INTRLS_SAFILS_Pos));
}

/**
  * @brief  SRB Almost Full Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetAlmostFullInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_SAFILS_Msk, CAN0_INTRLS_SAFILS_Pos));
}

/**
  * @brief  ETB Overrun Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_SetOverflowInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_EOILS_Msk, (((Line) & CAN0_INTRLS_EOILS_Val) << CAN0_INTRLS_EOILS_Pos));
}

/**
  * @brief  ETB Overrun Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetOverflowInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_EOILS_Msk, CAN0_INTRLS_EOILS_Pos));
}

/**
  * @brief  ETB Full Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_SetFullInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_EFILS_Msk, (((Line) & CAN0_INTRLS_EFILS_Val) << CAN0_INTRLS_EFILS_Pos));
}

/**
  * @brief  ETB Full Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetFullInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_EFILS_Msk, CAN0_INTRLS_EFILS_Pos));
}

/**
  * @brief  ETB Almost Full Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_SetAlmostFullInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_EAFILS_Msk, (((Line) & CAN0_INTRLS_EAFILS_Val) << CAN0_INTRLS_EAFILS_Pos));
}

/**
  * @brief  ETB Almost Full Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetAlmostFullInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_EAFILS_Msk, CAN0_INTRLS_EAFILS_Pos));
}

/**
  * @brief  SRB Receive Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetRxInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_SRILS_Msk, (((Line) & CAN0_INTRLS_SRILS_Val) << CAN0_INTRLS_SRILS_Pos));
}

/**
  * @brief  SRB Receive Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef 
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetRxInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_SRILS_Msk, CAN0_INTRLS_SRILS_Pos));
}

/**
  * @brief  ETB Receive Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_SetRxInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_ERILS_Msk, (((Line) & CAN0_INTRLS_ERILS_Val) << CAN0_INTRLS_ERILS_Pos));
}

/**
  * @brief  ETB Receive Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetRxInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_ERILS_Msk, CAN0_INTRLS_ERILS_Pos));
}

/**
  * @brief  Error Counter Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetErrorCountInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_ECILS_Msk, (((Line) & CAN0_INTRLS_ECILS_Val) << CAN0_INTRLS_ECILS_Pos));
}

/**
  * @brief  Error Counter Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetErrorCountInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_ECILS_Msk, CAN0_INTRLS_ECILS_Pos));
}

/**
  * @brief  Error Passive Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetErrorPassiveInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_EPILS_Msk, (((Line) & CAN0_INTRLS_EPILS_Val) << CAN0_INTRLS_EPILS_Pos));
}

/**
  * @brief  Error Passive Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetErrorPassiveInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_EPILS_Msk, CAN0_INTRLS_EPILS_Pos));
}

/**
  * @brief  Arbitration Lost Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetArbitrationLostInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_ALILS_Msk, (((Line) & CAN0_INTRLS_ALILS_Val) << CAN0_INTRLS_ALILS_Pos));
}

/**
  * @brief  Arbitration Lost Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetArbitrationLostInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_ALILS_Msk, CAN0_INTRLS_ALILS_Pos));
}

/**
  * @brief  Bus Error Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetBusErrorInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_BEILS_Msk, (((Line) & CAN0_INTRLS_BEILS_Val) << CAN0_INTRLS_BEILS_Pos));
}

/**
  * @brief  Bus Error Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetBusErrorInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_BEILS_Msk, CAN0_INTRLS_BEILS_Pos));
}

/**
  * @brief  PRB Receive Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetRxInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_RILS_Msk, (((Line) & CAN0_INTRLS_RILS_Val) << CAN0_INTRLS_RILS_Pos));
}

/**
  * @brief  PRB Receive Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetRxInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_RILS_Msk, CAN0_INTRLS_RILS_Pos));
}

/**
  * @brief  PRB Overrun Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetOverrunInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_ROILS_Msk, (((Line) & CAN0_INTRLS_ROILS_Val) << CAN0_INTRLS_ROILS_Pos));
}

/**
  * @brief  PRB Overrun Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetOverrunInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_ROILS_Msk, CAN0_INTRLS_ROILS_Pos));
}

/**
  * @brief  PRB Full Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetFullInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_RFILS_Msk, (((Line) & CAN0_INTRLS_RFILS_Val) << CAN0_INTRLS_RFILS_Pos));
}

/**
  * @brief  PRB Full Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetFullInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_RFILS_Msk, CAN0_INTRLS_RFILS_Pos));
}

/**
  * @brief  PRB Almost Full Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetAlmostFullInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_RAFILS_Msk, (((Line) & CAN0_INTRLS_RAFILS_Val) << CAN0_INTRLS_RAFILS_Pos));
}

/**
  * @brief  PRB Almost Full Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetAlmostFullInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_RAFILS_Msk, CAN0_INTRLS_RAFILS_Pos));
}

/**
  * @brief  PTB Transmission Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PTB_SetTxInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_TPILS_Msk, (((Line) & CAN0_INTRLS_TPILS_Val) << CAN0_INTRLS_TPILS_Pos));
}

/**
  * @brief  PTB Transmission Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PTB_GetTxInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_TPILS_Msk, CAN0_INTRLS_TPILS_Pos));
}

/**
  * @brief  STB Transmission Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_STB_SetTxInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_TSILS_Msk, (((Line) & CAN0_INTRLS_TSILS_Val) << CAN0_INTRLS_TSILS_Pos));
}

/**
  * @brief  STB Transmission Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_STB_GetTxInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_TSILS_Msk, CAN0_INTRLS_TSILS_Pos));
}

/**
  * @brief  Error Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetErrorInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_EILS_Msk, (((Line) & CAN0_INTRLS_EILS_Val) << CAN0_INTRLS_EILS_Pos));
}

/**
  * @brief  Error Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetErrorInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_EILS_Msk, CAN0_INTRLS_EILS_Pos));
}

/**
  * @brief  Abort Interrupt Line Select set
  * @param  CANx Specifies CAN peripheral
  * @param  Line Interrupt Line @ref LL_CAN_IntLineTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetAbortInterruptLine(CAN_TypeDef *CANx, uint32_t Line)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, CAN0_INTRLS_AILS_Msk, (((Line) & CAN0_INTRLS_AILS_Val) << CAN0_INTRLS_AILS_Pos));
}

/**
  * @brief  Abort Interrupt Line Select get
  * @param  CANx Specifies CAN peripheral
  * @return Interrupt Line @ref LL_CAN_IntLineTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetAbortInterruptLine(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->INTRLS, CAN0_INTRLS_AILS_Msk, CAN0_INTRLS_AILS_Pos));
}

/**
  * @brief  All Interrupt Line Select
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Interrupt Line Select Bit @ref LL_CAN_INTRLS_ITLineMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SelectInterruptLines(CAN_TypeDef *CANx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, LL_CAN_INTRLS_ALL_MSK, (Mask & LL_CAN_INTRLS_ALL_MSK));
}

/**
  * @brief  Interrupt Line Set, set to line 1
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Interrupt Line Select Bit @ref LL_CAN_INTRLS_ITLineMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetInterruptLines(CAN_TypeDef *CANx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTRLS, (Mask & LL_CAN_INTRLS_ALL_MSK));
}

/**
  * @brief  Interrupt Line Clear, set to line 0
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Interrupt Line Select Bit @ref LL_CAN_INTRLS_ITLineMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_IntLine_Clr(CAN_TypeDef *CANx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTRLS, (Mask & LL_CAN_INTRLS_ALL_MSK));
}

/**
  * @brief  All Interrupt Line Set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetAllInterruptLine(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, LL_CAN_INTRLS_ALL_MSK, LL_CAN_INTRLS_ALL_MSK);
}

/**
  * @brief  All Interrupt Line Reset
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_AllIntLine_Clr(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->INTRLS, LL_CAN_INTRLS_ALL_MSK, 0x00000000UL);
}

/**
  * @brief  All Interrupt Line Get
  * @param  CANx Specifies CAN peripheral
  * @return All Interrupt Line @ref LL_CAN_INTRLS_ITLineMskTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetAllInterruptLine(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((READ_REG(CANx->INTRLS) & LL_CAN_INTRLS_ALL_MSK));
}

/**
  * @brief  Standard Remote Frames Reject enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableStandardRemoteFrameReject(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->GFCR, CAN0_GFCR_SRFR_Msk);
}

/**
  * @brief  Standard Remote Frames Reject disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableStandardRemoteFrameReject(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->GFCR, CAN0_GFCR_SRFR_Msk);
}

/**
  * @brief  Judge is Standard Remote Frames Reject enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Standard Remote Frames Reject disable
  * @retval 1 Standard Remote Frames Reject enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsStandardRemoteFrameRejectEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->GFCR, CAN0_GFCR_SRFR_Msk, CAN0_GFCR_SRFR_Pos));
}

/**
  * @brief  Extended Remote Frames Reject enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableExtendedRemoteFrameReject(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->GFCR, CAN0_GFCR_ERFR_Msk);
}

/**
  * @brief  Extended Remote Frames Reject disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableExtendedRemoteFrameReject(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->GFCR, CAN0_GFCR_ERFR_Msk);
}

/**
  * @brief  Judge is Extended Remote Frames Reject enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Extended Remote Frames Reject disable
  * @retval 1 Extended Remote Frames Reject enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsExtendedRemoteFrameRejectEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->GFCR, CAN0_GFCR_ERFR_Msk, CAN0_GFCR_ERFR_Pos));
}

/**
  * @brief  PRB Working Mode set
  * @param  CANx Specifies CAN peripheral
  * @param Mode Working Mode @ref LL_CAN_RxBufWorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetWorkMode(CAN_TypeDef *CANx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->GFCR, CAN0_GFCR_PRBM_Msk, (((Mode) & CAN0_GFCR_PRBM_Val) << CAN0_GFCR_PRBM_Pos));
}

/**
  * @brief  PRB Working Mode Cover set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetWorkModeCover(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->GFCR, CAN0_GFCR_PRBM_Msk);
}

/**
  * @brief  PRB Working Mode Block set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetWorkModeBlock(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->GFCR, CAN0_GFCR_PRBM_Msk);
}

/**
  * @brief  PRB Working Mode get
  * @param  CANx Specifies CAN peripheral
  * @return Working Mode @ref LL_CAN_RxBufWorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetWorkMode(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->GFCR, CAN0_GFCR_PRBM_Msk, CAN0_GFCR_PRBM_Pos));
}

/**
  * @brief  SRB Working Mode set
  * @param  CANx Specifies CAN peripheral
  * @param Mode Working Mode @ref LL_CAN_RxBufWorkModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetWorkMode(CAN_TypeDef *CANx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->GFCR, CAN0_GFCR_SRBM_Msk, (((Mode) & CAN0_GFCR_SRBM_Val) << CAN0_GFCR_SRBM_Pos));
}

/**
  * @brief  SRB Working Mode Cover set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetWorkModeCover(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->GFCR, CAN0_GFCR_SRBM_Msk);
}

/**
  * @brief  SRB Working Mode Block set
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetWorkModeBlock(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->GFCR, CAN0_GFCR_SRBM_Msk);
}

/**
  * @brief  SRB Working Mode get
  * @param  CANx Specifies CAN peripheral
  * @return Working Mode @ref LL_CAN_RxBufWorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetWorkMode(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->GFCR, CAN0_GFCR_SRBM_Msk, CAN0_GFCR_SRBM_Pos));
}

/**
  * @brief  Extended ID Mask set
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Extended ID Mask
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetExtendedIdMask(CAN_TypeDef *CANx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->EMCR, CAN0_EMCR_EIDM_Msk, (((Mask) & CAN0_EMCR_EIDM_Val) << CAN0_EMCR_EIDM_Pos));
}

/**
  * @brief  Extended ID Mask get
  * @param  CANx Specifies CAN peripheral
  * @return Extended ID Mask
  */
__STATIC_INLINE uint32_t LL_CAN_GetExtendedIdMask(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->EMCR, CAN0_EMCR_EIDM_Msk, CAN0_EMCR_EIDM_Pos));
}

/**
  * @brief  Priority Message Acceptance Status get
  * @param  CANx Specifies CAN peripheral
  * @return Acceptance filter sequence number @ref LL_CAN_AcceptFilSlotTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetPriorityMessageAcceptStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->PMST, CAN0_PMST_PMAS_Msk, CAN0_PMST_PMAS_Pos));
}

/**
  * @brief  Priority Message Buffer Status get
  * @param  CANx Specifies CAN peripheral
  * @return Priority Message Buffer Status @ref LL_CAN_FrmStoreModeTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetPriorityMessageBufferStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->PMST, CAN0_PMST_PMBS_Msk, CAN0_PMST_PMBS_Pos));
}

/**
  * @brief  Priority Message IDE Status get
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Priority Message is Standard Frame
  * @retval 1 Priority Message is Extended Frame
  */
__STATIC_INLINE uint32_t LL_CAN_GetPriorityMessageIDEStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->PMST, CAN0_PMST_PMIS_Msk, CAN0_PMST_PMIS_Pos));
}

/**
  * @brief  Priority Message Acceptance Status Extract
  * @param  Info Priority Message Status @ref LL_CAN_ReadPriorityMessageStatus
  * @return Acceptance filter sequence number @ref LL_CAN_AcceptFilSlotTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractPriorityMessageAcceptStatus(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, CAN0_PMST_PMAS_Msk, CAN0_PMST_PMAS_Pos));
}

/**
  * @brief  Priority Message Buffer Store Mode Extract
  * @param  Info Priority Message Status @ref LL_CAN_ReadPriorityMessageStatus
  * @return Priority Message Buffer Store Mode @ref LL_CAN_FrmStoreModeTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractPriorityMessageBufferStatus(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, CAN0_PMST_PMBS_Msk, CAN0_PMST_PMBS_Pos));
}

/**
  * @brief  Priority Message IDE Status Extract
  * @param  Info Priority Message Status @ref LL_CAN_ReadPriorityMessageStatus
  * @retval 0 Priority Message is Standard Frame
  * @retval 1 Priority Message is Extended Frame
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractPriorityMessageIDEStatus(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, CAN0_PMST_PMIS_Msk, CAN0_PMST_PMIS_Pos));
}

/**
  * @brief  Priority Message Status Read
  * @param  CANx Specifies CAN peripheral
  * @return Priority Message Status 
  */
__STATIC_INLINE uint32_t LL_CAN_ReadPriorityMessageStatus(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->PMST));
}


/**
  * @brief  Acceptance filter enable
  * @param  CANx Specifies CAN peripheral
  * @param  Fil_num Acceptance filter slot number
  * @note   fil_num value range @ref LL_CAN_AcceptFilSlotTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableAcceptanceFilter(CAN_TypeDef *CANx, uint32_t Fil_num)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->ACFEN, BIT(Fil_num % LL_CAN_ACCEPT_FILT_SLOT_NUMS));
}

/**
  * @brief  Acceptance filter disable
  * @param  CANx Specifies CAN peripheral
  * @param  Fil_num Acceptance filter slot number
  * @note   fil_num value range @ref LL_CAN_AcceptFilSlotTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableAcceptanceFilter(CAN_TypeDef *CANx, uint32_t Fil_num)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->ACFEN, BIT(Fil_num));
}

/**
  * @brief  Acceptance filter content select mask
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SelectAcceptanceFilterContentMask(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->ACFCTRL, CAN0_ACFCTRL_SELMASK_Msk);
}

/**
  * @brief  Acceptance filter content select code
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SelectAcceptanceFilterContentCode(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->ACFCTRL, CAN0_ACFCTRL_SELMASK_Msk);
}

/**
  * @brief  Acceptance filter address set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value @ref LL_CAN_AcceptFilSlotTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetAcceptanceFilterAddress(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->ACFCTRL, CAN0_ACFCTRL_ACFADR_Msk, (((Val) & CAN0_ACFCTRL_ACFADR_Val) << CAN0_ACFCTRL_ACFADR_Pos));
}

/**
  * @brief  Acceptance filter address read
  * @param  CANx Specifies CAN peripheral
  * @return Acceptance filter address  @ref LL_CAN_AcceptFilSlotTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_ReadAcceptanceFilterAddress(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ACFCTRL, CAN0_ACFCTRL_ACFADR_Msk, CAN0_ACFCTRL_ACFADR_Pos));
}

/**
  * @brief  Acceptance mask IDE bit check enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableAcceptanceFilterMaskIDE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->ACF, CAN0_ACF_AIDEE_Msk);
}

/**
  * @brief  Acceptance mask IDE bit check disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableAcceptanceFilterMaskIDE(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->ACF, CAN0_ACF_AIDEE_Msk);
}

/**
  * @brief  Acceptance filter accepts only extended frames
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SelectAcceptanceFilterMaskIDEExtended(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->ACF, CAN0_ACF_AIDE_Msk);
}

/**
  * @brief  Acceptance filter accepts only standard frames
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SelectAcceptanceFilterMaskIDEStandard(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->ACF, CAN0_ACF_AIDE_Msk);
}

/**
  * @brief  Acceptance filter Rx frame type set
  * @param  CANx Specifies CAN peripheral
  * @param  Frm_type Rx frame type @ref LL_CAN_AcceptFilRxFrmTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetAcceptanceFilterRxFrame(CAN_TypeDef *CANx, uint32_t Frm_type)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->ACF, CAN0_ACF_AIDEE_Msk | CAN0_ACF_AIDE_Msk, 
        ((Frm_type) & ((CAN0_ACF_AIDEE_Msk | CAN0_ACF_AIDE_Msk) >> CAN0_ACF_AIDE_Pos)) << CAN0_ACF_AIDE_Pos);
}

/**
  * @brief  Acceptance filter code or mask set
  * @param  CANx Specifies CAN peripheral
  * @param  Val set value
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetAcceptanceFilterCodeOrMaskValue(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->ACF, CAN0_ACF_ACF_X_Msk, (((Val) & CAN0_ACF_ACF_X_Val) << CAN0_ACF_ACF_X_Pos));
}

/**
  * @brief  CAN Acceptance Mode set
  * @param  CANx Specifies CAN peripheral
  * @param  Mode CAN Acceptance Mode @ref LL_CAN_AcceptModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetAcceptanceMode(CAN_TypeDef *CANx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->ACFE, CAN0_ACFE_ACF_M_Msk, (((Mode) & CAN0_ACFE_ACF_M_Val) << CAN0_ACFE_ACF_M_Pos));
}

/**
  * @brief  CAN Acceptance Mode get
  * @param  CANx Specifies CAN peripheral
  * @return CAN Acceptance Mode @ref LL_CAN_AcceptModeTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetAcceptanceMode(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ACFE, CAN0_ACFE_ACF_M_Msk, CAN0_ACFE_ACF_M_Pos));
}

/**
  * @brief  CAN Acceptance Control set
  * @param  CANx Specifies CAN peripheral
  * @param  Ctrl CAN Acceptance Control @ref LL_CAN_AcceptCtrlTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetAcceptanceControl(CAN_TypeDef *CANx, uint32_t Ctrl)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->ACFE, CAN0_ACFE_ACF_C_Msk, (((Ctrl) & CAN0_ACFE_ACF_C_Val) << CAN0_ACFE_ACF_C_Pos));
}

/**
  * @brief  CAN Acceptance Control get
  * @param  CANx Specifies CAN peripheral
  * @return CAN Acceptance Control @ref LL_CAN_AcceptCtrlTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetAcceptanceControl(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ACFE, CAN0_ACFE_ACF_C_Msk, CAN0_ACFE_ACF_C_Pos));
}

/**
  * @brief  PRB Buffer ID Register Read
  * @param  CANx Specifies CAN peripheral
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_ReadBufferRegisterID(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->RBUFID));
}

/**
  * @brief  PRB Buffer Control Register Read
  * @param  CANx Specifies CAN peripheral
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_ReadBufferRegisterControl(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->RBUFCR));
}

/**
  * @brief  PRB Buffer Data Register Read
  * @param  CANx Specifies CAN peripheral
  * @param  Num Data Register Number range [0, LL_CAN_RBUFDT_WORD_LAYER_LEVEL - 1]
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_ReadBufferRegisterData(const CAN_TypeDef *CANx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->RBUFDT[((uint32_t)(Num) % LL_CAN_RBUFDT_WORD_LAYER_LEVEL)]));
}

/**
  * @brief  PRB Buffer Data Register Address Get
  * @param  CANx Specifies CAN peripheral
  * @return PRB Buffer Data Register Address
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetDataBufferAddress(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(&CANx->RBUFDT[0]);
}

/**
  * @brief  Tx Buffer ID Register Write
  * @param  CANx Specifies CAN peripheral
  * @param  Val Write Value
  * @return None
  */
__STATIC_INLINE void LL_CAN_WriteTxBufferRegisterID(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->TBUFID, Val);
}

/**
  * @brief  Tx Buffer Control Register Write
  * @param  CANx Specifies CAN peripheral
  * @param  Val Write Value
  * @return None
  */
__STATIC_INLINE void LL_CAN_WriteTxBufferRegisterControl(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->TBUFCR, Val);
}

/**
  * @brief  Tx Buffer Data Register Write
  * @param  CANx Specifies CAN peripheral
  * @param  Num Data Register Number range [0, LL_CAN_TBUFDT_WORD_LAYER_LEVEL - 1]
  * @param  Val Write Value
  * @return None
  */
__STATIC_INLINE void LL_CAN_WriteTxBufferRegisterData(CAN_TypeDef *CANx, uint32_t Num, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->TBUFDT[((uint32_t)(Num) % LL_CAN_TBUFDT_WORD_LAYER_LEVEL)], Val);
}

/**
  * @brief  ETB Buffer ID Register Read
  * @param  CANx Specifies CAN peripheral
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_ReadBufferRegisterID(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->EBUFID));
}

/**
  * @brief  ETB Buffer Data Register Read
  * @param  CANx Specifies CAN peripheral
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_ReadBufferRegisterData(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->EBUFDT));
}

/**
  * @brief  SRB Identifier Data Extract about ESI
  * @param  Info SRB Identifier Data @ref LL_CAN_SRB_ReadBufferRegisterID
  * @retval 0 Received CAN FD message did not have its ESI flag set
  * @retval 1 Received CAN FD message had its ESI flag set
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_ExtractBufferRegisterESI(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_RX_ID_DATA_ESI_MSK));
}

/**
  * @brief  SRB Identifier Data Extract about CAN ID
  * @param  Info SRB Identifier Data @ref LL_CAN_SRB_ReadBufferRegisterID
  * @retval SRB Rx Frame CAN ID
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_ExtractBufferRegisterID(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_RX_ID_DATA_ID_MSK, POSITION_VAL(LL_CAN_RX_ID_DATA_ID_MSK)));
}

/**
  * @brief  SRB Buffer ID Register Read
  * @param  CANx Specifies CAN peripheral
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_ReadBufferRegisterID(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->SBUFID));
}

/**
  * @brief  SRB Buffer Control Register Read
  * @param  CANx Specifies CAN peripheral
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_ReadBufferRegisterControl(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->SBUFCR));
}

/**
  * @brief  SRB Buffer Data Register Read
  * @param  CANx Specifies CAN peripheral
  * @param  Num Data Register Number range [0, LL_CAN_SBUFDT_WORD_LAYER_LEVEL - 1]
  * @return Read Value
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_ReadBufferRegisterData(const CAN_TypeDef *CANx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_REG(CANx->SBUFDT[((uint32_t)(Num) % LL_CAN_SBUFDT_WORD_LAYER_LEVEL)]));
}

/**
  * @brief  SRB Buffer Data Register Address Get
  * @param  CANx Specifies CAN peripheral
  * @return SRB Buffer Data Register Address
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetDataBufferAddress(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(&CANx->SBUFDT[0]);
}

/**
  * @brief  Timestamp Prescaler set
  * @note   The actual value is equal to the configured value +1
  * @param  CANx Specifies CAN peripheral
  * @param  Val Timestamp Prescaler @ref LL_CAN_TimestampPrescalerTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetTimestampPrescaler(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->TSCR, CAN0_TSCR_TSP_Msk, (((Val) & CAN0_TSCR_TSP_Val) << CAN0_TSCR_TSP_Pos));
}

/**
  * @brief  Timestamp Prescaler get
  * @note   The actual value is equal to the configured value +1
  * @param  CANx Specifies CAN peripheral
  * @return Timestamp Prescaler
  */
__STATIC_INLINE uint32_t LL_CAN_GetTimestampPrescaler(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->TSCR, CAN0_TSCR_TSP_Msk, CAN0_TSCR_TSP_Pos));
}

/**
  * @brief  Timestamp Timebase set
  * @param  CANx Specifies CAN peripheral
  * @param  Tb Timestamp Timebase @ref LL_CAN_TimestampTimebaseTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetTimestampTimebase(CAN_TypeDef *CANx, uint32_t Tb)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->TSCR, CAN0_TSCR_TSS_Msk, (((Tb) & CAN0_TSCR_TSS_Val) << CAN0_TSCR_TSS_Pos));
}

/**
  * @brief  Timestamp Timebase get
  * @param  CANx Specifies CAN peripheral
  * @return Timestamp Timebase @ref LL_CAN_TimestampTimebaseTypeDef
  */
__STATIC_INLINE uint32_t LL_CAN_GetTimestampTimebase(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->TSCR, CAN0_TSCR_TSS_Msk, CAN0_TSCR_TSS_Pos));
}

/**
  * @brief  Timestamp Count get
  * @param  CANx Specifies CAN peripheral
  * @return Timestamp Count
  */
__STATIC_INLINE uint32_t LL_CAN_GetTimestampCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->TSC, CAN0_TSC_TSC_Msk, CAN0_TSC_TSC_Pos));
}

/**
  * @brief  PRB Timeout enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_EnableTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->RTOP, CAN0_RTOP_RTOE_Msk);
}

/**
  * @brief  PRB Timeout disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_DisableTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->RTOP, CAN0_RTOP_RTOE_Msk);
}

/**
  * @brief  Judge is PRB Timeout enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 PRB Timeout disable
  * @retval 1 PRB Timeout enable
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_IsTimeoutEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->RTOP, CAN0_RTOP_RTOE_Msk, CAN0_RTOP_RTOE_Pos));
}

/**
  * @brief  PRB Timeout Period set 
  * @param  CANx Specifies CAN peripheral
  * @param  Val PRB Timeout Period
  * @return None
  */
__STATIC_INLINE void LL_CAN_PRB_SetTimeoutPeriod(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->RTOP, CAN0_RTOP_RTOP_Msk, (((Val) & CAN0_RTOP_RTOP_Val) << CAN0_RTOP_RTOP_Pos));
}

/**
  * @brief  PRB Timeout Period get
  * @param  CANx Specifies CAN peripheral
  * @return PRB Timeout Period
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetTimeoutPeriod(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->RTOP, CAN0_RTOP_RTOP_Msk, CAN0_RTOP_RTOP_Pos));
}

/**
  * @brief  PRB Timeout Count get
  * @param  CANx Specifies CAN peripheral
  * @return PRB Timeout Count
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetTimeoutCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->RTOC, CAN0_RTOC_RTOC_Msk, CAN0_RTOC_RTOC_Pos));
}

/**
  * @brief  SRB Timeout enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_EnableTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->STOP, CAN0_STOP_STOE_Msk);
}

/**
  * @brief  SRB Timeout disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_DisableTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->STOP, CAN0_STOP_STOE_Msk);
}

/**
  * @brief  Judge is SRB Timeout enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 SRB Timeout disable
  * @retval 1 SRB Timeout enable
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_IsTimeoutEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STOP, CAN0_STOP_STOE_Msk, CAN0_STOP_STOE_Pos));
}

/**
  * @brief  SRB Timeout Period set
  * @note   
  * @param  CANx Specifies CAN peripheral
  * @param  Val SRB Timeout Period
  * @return None
  */
__STATIC_INLINE void LL_CAN_SRB_SetTimeoutPeriod(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->STOP, CAN0_STOP_STOP_Msk, (((Val) & CAN0_STOP_STOP_Val) << CAN0_STOP_STOP_Pos));
}

/**
  * @brief  SRB Timeout Period get
  * @param  CANx Specifies CAN peripheral
  * @return SRB Timeout Period
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetTimeoutPeriod(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STOP, CAN0_STOP_STOP_Msk, CAN0_STOP_STOP_Pos));
}

/**
  * @brief  SRB Timeout Count get
  * @param  CANx Specifies CAN peripheral
  * @return SRB Timeout Count
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetTimeoutCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->STOC, CAN0_STOC_STOC_Msk, CAN0_STOC_STOC_Pos));
}

/**
  * @brief  ETB Timeout enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_EnableTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->ETOP, CAN0_ETOP_ETOE_Msk);
}

/**
  * @brief  ETB Timeout disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_DisableTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->ETOP, CAN0_ETOP_ETOE_Msk);
}

/**
  * @brief  Judge is ETB Timeout enable or not
  * @param  CANx Specifies CAN peripheral
  * @retval 0 ETB Timeout disable
  * @retval 1 ETB Timeout enable
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_IsTimeoutEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ETOP, CAN0_ETOP_ETOE_Msk, CAN0_ETOP_ETOE_Pos));
}

/**
  * @brief  ETB Timeout Period set
  * @note   
  * @param  CANx Specifies CAN peripheral
  * @param  Val ETB Timeout Period
  * @return None
  */
__STATIC_INLINE void LL_CAN_ETB_SetTimeoutPeriod(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->ETOP, CAN0_ETOP_ETOP_Msk, (((Val) & CAN0_ETOP_ETOP_Val) << CAN0_ETOP_ETOP_Pos));
}

/**
  * @brief  ETB Timeout Period get
  * @param  CANx Specifies CAN peripheral
  * @return ETB Timeout Period
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetTimeoutPeriod(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ETOP, CAN0_ETOP_ETOP_Msk, CAN0_ETOP_ETOP_Pos));
}

/**
  * @brief  ETB Timeout Count get
  * @param  CANx Specifies CAN peripheral
  * @return ETB Timeout Count
  */
__STATIC_INLINE uint32_t LL_CAN_ETB_GetTimeoutCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->ETOC, CAN0_ETOC_ETOC_Msk, CAN0_ETOC_ETOC_Pos));
}

/**
  * @brief  Continuous Count Timeout enable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableContinuousCountTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->CTOP, CAN0_CTOP_CTOE_Msk);
}

/**
  * @brief  Continuous Count Timeout disable
  * @param  CANx Specifies CAN peripheral
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableContinuousCountTimeout(CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->CTOP, CAN0_CTOP_CTOE_Msk);
}

/**
  * @brief  Continuous Count Timeout enable
  * @param  CANx Specifies CAN peripheral
  * @retval 0 Continuous Count Timeout disable
  * @retval 1 Continuous Count Timeout enable
  */
__STATIC_INLINE uint32_t LL_CAN_IsContinuousCountTimeoutEnabled(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTOP, CAN0_CTOP_CTOE_Msk, CAN0_CTOP_CTOE_Pos));
}

/**
  * @brief  Continuous Timeout Period set
  * @note   
  * @param  CANx Specifies CAN peripheral
  * @param  Val Continuous Timeout Period
  * @return None
  */
__STATIC_INLINE void LL_CAN_SetContinuousTimeoutPeriod(CAN_TypeDef *CANx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    MODIFY_REG(CANx->CTOP, CAN0_CTOP_CTOP_Msk, (((Val) & CAN0_CTOP_CTOP_Val) << CAN0_CTOP_CTOP_Pos));
}

/**
  * @brief  Continuous Timeout Period get
  * @param  CANx Specifies CAN peripheral
  * @return Continuous Timeout Period
  */
__STATIC_INLINE uint32_t LL_CAN_GetContinuousTimeoutPeriod(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTOP, CAN0_CTOP_CTOP_Msk, CAN0_CTOP_CTOP_Pos));
}

/**
  * @brief  Continuous Timeout Count get
  * @param  CANx Specifies CAN peripheral
  * @return Continuous Timeout Count
  */
__STATIC_INLINE uint32_t LL_CAN_GetContinuousTimeoutCount(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)(READ_BIT_SHIFT(CANx->CTOC, CAN0_CTOC_CTOC_Msk, CAN0_CTOC_CTOC_Pos));
}

/**
  * @brief CAN TxFIFO Size Get
  * @param  CANx Specifies CAN peripheral
  * @return CAN TxFIFO Size in Byte Unit
  */
__STATIC_INLINE uint32_t LL_CAN_GetTxFIFOSize(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((sizeof(CANx->TBUFDT)));
}

/**
  * @brief CAN RxFIFO Size Get
  * @param  CANx Specifies CAN peripheral
  * @return CAN RxFIFO Size in Byte Unit
  */
__STATIC_INLINE uint32_t LL_CAN_PRB_GetFIFOSize(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((sizeof(CANx->RBUFDT)));
}

/**
  * @brief CAN SRB FIFO Size Get
  * @param  CANx Specifies CAN peripheral
  * @return CAN SRB FIFO Size in Byte Unit
  */
__STATIC_INLINE uint32_t LL_CAN_SRB_GetFIFOSize(const CAN_TypeDef *CANx)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    return (uint32_t)((sizeof(CANx->SBUFDT)));
}

/**
  * @brief  Rx Identifier Data Extract about CAN ID
  * @param  Info Rx Identifier Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterID
  *             @ref LL_CAN_SRB_ReadBufferRegisterID
  * @retval Rx Frame CAN ID
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxIdData_ID(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_RX_ID_DATA_ID_MSK, POSITION_VAL(LL_CAN_RX_ID_DATA_ID_MSK)));
}

/**
  * @brief  Rx Identifier Data Extract about ESI
  * @param  Info Rx Identifier Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterID
  *             @ref LL_CAN_SRB_ReadBufferRegisterID
  * @retval 0 Received CAN FD message did not have its ESI flag set
  * @retval 1 Received CAN FD message had its ESI flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxIdData_ESI(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_RX_ID_DATA_ESI_MSK));
}

/**
  * @brief  Rx Control Data Extract about CAN ID
  * @param  Info Rx Control Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterControl 
  *             @ref LL_CAN_SRB_ReadBufferRegisterControl
  * @retval Rx Frame CAN ID
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxControlData_DLC(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_RX_CTRL_DATA_DLC_MSK, POSITION_VAL(LL_CAN_RX_CTRL_DATA_DLC_MSK)));
}

/**
  * @brief  Rx Control Data Extract about BRS
  * @param  Info Rx Control Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterControl 
  *             @ref LL_CAN_SRB_ReadBufferRegisterControl
  * @retval 0 Received CAN FD message did not have its BRS flag set
  * @retval 1 Received CAN FD message had its BRS flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxControlData_BRS(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_RX_CTRL_DATA_BRS_MSK));
}

/**
  * @brief  Rx Control Data Extract about FDF
  * @param  Info Rx Control Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterControl 
  *             @ref LL_CAN_SRB_ReadBufferRegisterControl
  * @retval 0 Received CAN FD message did not have its FDF flag set
  * @retval 1 Received CAN FD message had its FDF flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxControlData_FDF(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_RX_CTRL_DATA_FDF_MSK));
}

/**
  * @brief  Rx Control Data Extract about RTR
  * @param  Info Rx Control Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterControl 
  *             @ref LL_CAN_SRB_ReadBufferRegisterControl
  * @retval 0 Received CAN message did not have its RTR flag set
  * @retval 1 Received CAN message had its RTR flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxControlData_RTR(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_RX_CTRL_DATA_RTR_MSK));
}

/**
  * @brief  Rx Control Data Extract about IDE
  * @param  Info Rx Control Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterControl 
  *             @ref LL_CAN_SRB_ReadBufferRegisterControl
  * @retval 0 Received CAN message did not have its IDE flag set
  * @retval 1 Received CAN message had its IDE flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxControlData_IDE(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_RX_CTRL_DATA_IDE_MSK));
}

/**
  * @brief  Rx Control Data Extract about Timestamp
  * @param  Info Rx Control Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterControl 
  *             @ref LL_CAN_SRB_ReadBufferRegisterControl
  * @retval Rx Frame Timestamp
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxControlData_Timestamp(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_RX_CTRL_DATA_TIMESTAMP_MSK, POSITION_VAL(LL_CAN_RX_CTRL_DATA_TIMESTAMP_MSK)));
}

/**
  * @brief  Rx Control Data Extract about Acceptance Data
  * @param  Info Rx Control Data 
  *             @ref LL_CAN_PRB_ReadBufferRegisterControl 
  *             @ref LL_CAN_SRB_ReadBufferRegisterControl
  * @retval Rx Frame Acceptance Data
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractRxControlData_AcceptData(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_RX_CTRL_DATA_ACCEPT_DATA_MSK, POSITION_VAL(LL_CAN_RX_CTRL_DATA_ACCEPT_DATA_MSK)));
}

/**
  * @brief  Tx Identifier Data Insert CAN ID
  * @param  Addr Destination Address
  * @param  Dat CAN ID value
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxIdData_ID(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_ID_DATA_ID_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_ID_DATA_ID_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_ID_DATA_ID_MSK;
    *tmp |= val;
}

/**
  * @brief  Tx Control Data Insert DLC
  * @param  Addr Destination Address
  * @param  Dat Data Length Code
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxControlData_DLC(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_CTRL_DATA_DLC_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_CTRL_DATA_DLC_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_CTRL_DATA_DLC_MSK;
    *tmp |= val;
}

/**
  * @brief  Tx Control Data Insert BRS
  * @param  Addr Destination Address
  * @param  Dat BRS value (0 or 1)
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxControlData_BRS(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_CTRL_DATA_BRS_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_CTRL_DATA_BRS_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_CTRL_DATA_BRS_MSK;
    *tmp |= val;
}

/**
  * @brief  Tx Control Data Insert FDF
  * @param  Addr Destination Address
  * @param  Dat FDF value (0 or 1)
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxControlData_FDF(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_CTRL_DATA_FDF_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_CTRL_DATA_FDF_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_CTRL_DATA_FDF_MSK;
    *tmp |= val;
}

/**
  * @brief  Tx Control Data Insert RTR
  * @param  Addr Destination Address
  * @param  Dat RTR value (0 or 1)
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxControlData_RTR(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_CTRL_DATA_RTR_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_CTRL_DATA_RTR_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_CTRL_DATA_RTR_MSK;
    *tmp |= val;
}

/**
  * @brief  Tx Control Data Insert IDE
  * @param  Addr Destination Address
  * @param  Dat IDE value (0 or 1)
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxControlData_IDE(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_CTRL_DATA_IDE_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_CTRL_DATA_IDE_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_CTRL_DATA_IDE_MSK;
    *tmp |= val;
}

/**
  * @brief  Tx Control Data Insert Message Marker
  * @param  Addr Destination Address
  * @param  Dat Message Marker value (8-bit)
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxControlData_MessageMarker(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_CTRL_DATA_MESG_MARKER_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_CTRL_DATA_MESG_MARKER_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_CTRL_DATA_MESG_MARKER_MSK;
    *tmp |= val;
}

/**
  * @brief  Tx Control Data Insert TX Event
  * @param  Addr Destination Address
  * @param  Dat TX Event value (0 or 1)
  * @return None
  */
__STATIC_INLINE void LL_CAN_InsertTxControlData_TxEvent(uint32_t *Addr, uint32_t Dat)
{
    volatile uint32_t *tmp = (volatile uint32_t *)Addr;
    uint32_t pos = POSITION_VAL(LL_CAN_TX_CTRL_DATA_TX_EVT_MSK);
    uint32_t val = (Dat & (LL_CAN_TX_CTRL_DATA_TX_EVT_MSK >> pos)) << pos;

    *tmp &= ~LL_CAN_TX_CTRL_DATA_TX_EVT_MSK;
    *tmp |= val;
}
/**
  * @brief  Tx Event Identifier Data Extract about CAN ID
  * @param  Info Tx Event Identifier Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterID
  * @retval Tx Frame CAN ID
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventIdData_ID(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_TX_EVT_ID_DATA_ID_MSK, POSITION_VAL(LL_CAN_TX_EVT_ID_DATA_ID_MSK)));
}

/**
  * @brief  Tx Event Identifier Data Extract about ESI
  * @param  Info Tx Event Identifier Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterID
  * @retval 0 Received CAN FD message did not have its ESI flag set
  * @retval 1 Received CAN FD message had its ESI flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventIdData_ESI(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_TX_EVT_ID_DATA_ESI_MSK));
}

/**
  * @brief  Tx Event Control Data Extract about CAN ID
  * @param  Info Tx Event Control Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterData 
  * @retval Tx Event Frame CAN ID
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventControlData_DLC(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_TX_EVT_DATA_DLC_MSK, POSITION_VAL(LL_CAN_TX_EVT_DATA_DLC_MSK)));
}

/**
  * @brief  Tx Event Control Data Extract about BRS
  * @param  Info Tx Event Control Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterData 
  * @retval 0 Transmitted CAN FD message did not have its BRS flag set
  * @retval 1 Transmitted CAN FD message had its BRS flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventControlData_BRS(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_TX_EVT_DATA_BRS_MSK));
}

/**
  * @brief  Tx Event Control Data Extract about FDF
  * @param  Info Tx Event Control Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterData 
  * @retval 0 Transmitted CAN FD message did not have its FDF flag set
  * @retval 1 Transmitted CAN FD message had its FDF flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventControlData_FDF(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_TX_EVT_DATA_FDF_MSK));
}

/**
  * @brief  Tx Event Control Data Extract about RTR
  * @param  Info Tx Event Control Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterData 
  * @retval 0 Transmitted CAN message did not have its RTR flag set
  * @retval 1 Transmitted CAN message had its RTR flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventControlData_RTR(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_TX_EVT_DATA_RTR_MSK));
}

/**
  * @brief  Tx Event Control Data Extract about IDE
  * @param  Info Tx Event Control Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterData 
  * @retval 0 Transmitted CAN message did not have its IDE flag set
  * @retval 1 Transmitted CAN message had its IDE flag set
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventControlData_IDE(uint32_t Info)
{
    return (uint32_t)(!!READ_BIT(Info, LL_CAN_TX_EVT_DATA_IDE_MSK));
}

/**
  * @brief  Tx Event Control Data Extract about Timestamp
  * @param  Info Tx Event Control Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterData 
  * @retval Transmitted Frame Timestamp
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventControlData_Timestamp(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_TX_EVT_DATA_TIMESTAMP_MSK, POSITION_VAL(LL_CAN_TX_EVT_DATA_TIMESTAMP_MSK)));
}

/**
  * @brief  Tx Event Control Data Extract about Message Marker 
  * @param  Info Tx Event Control Data 
  *             @ref LL_CAN_ETB_ReadBufferRegisterData 
  * @retval Transmitted Frame Message Marker
  */
__STATIC_INLINE uint32_t LL_CAN_ExtractTxEventControlData_MessageMarker(uint32_t Info)
{
    return (uint32_t)(READ_BIT_SHIFT(Info, LL_CAN_TX_EVT_DATA_MESG_MARKER_MSK, POSITION_VAL(LL_CAN_TX_EVT_DATA_MESG_MARKER_MSK)));
}


/**
  * @}
  */ /* CAN_LL_EF_Configuration */

/** @defgroup CAN_LL_EF_IT_Management LL CAN Interrupt Management
  * @brief LL CAN Interrupt Management
  * @{
  */

/**
  * @brief  CAN Interrupt enable
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Mask to enable @ref LL_CAN_INTREN_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_EnableIT(CAN_TypeDef *CANx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    SET_BIT(CANx->INTREN, Mask);
}

/**
  * @brief  CAN Interrupt disable
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Mask to disable @ref LL_CAN_INTREN_ITEnMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_DisableIT(CAN_TypeDef *CANx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    CLEAR_BIT(CANx->INTREN, Mask);
}

/**
  * @brief  Check if CAN Interrupt is enabled or disabled
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Mask to check @ref LL_CAN_INTREN_ITEnMskTypeDef
  * @return State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_CAN_IsEnabledIT(const CAN_TypeDef *CANx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(CANx->INTREN, Mask) == (Mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Interrupt Pending
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Mask to check @ref LL_CAN_INTRST_ITPendingMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_CAN_ClearFlag(CAN_TypeDef *CANx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_CAN_ALL_INSTANCE(CANx));

    WRITE_REG(CANx->INTRST, Mask);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  CANx Specifies CAN peripheral
  * @param  Mask Mask to check @ref LL_CAN_INTRST_ITPendingMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CAN_IsActiveFlag(const CAN_TypeDef *CANx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(CANx->INTRST, Mask) == (Mask)) ? 1UL : 0UL);
}


/**
  * @}
  */ /* CAN_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* CAN_LL_Exported_Functions */

/**
  * @}
  */ /* CAN_LL */

#endif /* CAN */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_CAN_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

