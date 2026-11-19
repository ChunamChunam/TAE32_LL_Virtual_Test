/**
  ******************************************************************************
  * @file    tae32f561x_ll_eflash.h
  * @author  Tai-Action SD Team
  * @brief   Header file for EFLASH LL module
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
#ifndef _TAE32F561X_LL_EFLASH_H_
#define _TAE32F561X_LL_EFLASH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_ll_def.h"


/** @addtogroup TAE32F561x_LL_Driver
  * @{
  */

#if defined(EFLASH)

/** @defgroup EFLASH_LL EFLASH LL
  * @brief    EFLASH LL Module Driver
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup EFLASH_LL_Exported_Constants EFLASH LL Exported Constants
  * @brief    EFLASH LL Exported Constants
  * @{
  */

/** @defgroup EFLASH_LL_EC_Information LL EFLASH Information
  * @brief LL EFLASH Information 
  * @{
  */

/**
  * @brief EFLASH Sector Size and Sector Number Definition
  */
#define LL_EFLASH_SECTOR_SIZE_256_S             (8192U)     /*!< EFLASH 256K Single Bank Sector Size Definition     */
#define LL_EFLASH_SECTOR_NUM_256_S              (32U)       /*!< EFLASH 256K Single Bank Sector Number Definition   */
#define LL_EFLASH_SECTOR_SIZE_256_D             (4096U)     /*!< EFLASH 256K Double Bank Sector Size Definition     */
#define LL_EFLASH_SECTOR_NUM_256_D              (64U)       /*!< EFLASH 256K Double Bank Sector Number Definition   */
#define LL_EFLASH_SECTOR_SIZE_128               (4096U)     /*!< EFLASH 128K Bank Sector Size Definition            */
#define LL_EFLASH_SECTOR_NUM_128                (32U)       /*!< EFLASH 128K Bank Sector Number Definition          */

/**
  * @brief EFLASH Program Size in a single programming operation, in byte Unit
  */
#define LL_EFLASH_PROG_SINGLE_SIZE              (8U)

/**
  * @brief EFLASH Write Protect Control Unit, 2 Sectors
  */
#define LL_EFLASH_WRITE_PROTECT_UNIT            (2U)

/**
  * @brief EFLASH Chip Size Mode Register
  */
#define LL_EFLASH_REG_ADDR_CHIP_SIZE_MODE        (0x40023048UL)            /*!< EFLASH Chip Size Mode Register                   */
#define LL_EFLASH_REG_CHIP_SIZE_MODE_MSK         (0xFFFF0000UL)            /*!< EFLASH Chip Size Mode Mask                       */
#define LL_EFLASH_REG_CHIP_SIZE_MODE_POS         (16UL)                    /*!< EFLASH Chip Size Mode Position                   */
#define LL_EFLASH_CHIP_SIZE_MODE_128K            (0xA5A5UL)                /*!< EFLASH Chip Size Mode 128K                       */
/**
  * @}
  */ /* EFLASH_LL_EC_Information */


/** @defgroup EFLASH_LL_EC_Keys LL EFLASH Keys
  * @brief LL EFLASH Keys 
  * @{
  */

/**
  * @brief EFLASH Program/Erase unlock KEY1
  */
#define LL_EFLASH_PROG_ERASE_KEY1               (0x3FACUL)

/**
  * @brief EFLASH Program/Erase unlock KEY2
  * @note  Used with KEY1 to unlock the EFLASH Program/Erase features
  */
#define LL_EFLASH_PROG_ERASE_KEY2               (0x87E4UL)

/**
  * @brief EFLASH Read/Write Protection / Option Data unlock Operation KEY1
  */
#define LL_EFLASH_RW_PROTECT_OPT_DAT_KEY1       (0x124AUL)

/**
  * @brief EFLASH Read/Write Protection / Option Data unlock Operation KEY2
  * @note  Used with KEY1 to unlock the operation of EFLASH Read/Write Protection Register
  */
#define LL_EFLASH_RW_PROTECT_OPT_DAT_KEY2       (0xBC7FUL)
/**
  * @}
  */ /* EFLASH_LL_EC_Keys */


/** @defgroup EFLASH_LL_EC_Flags LL EFLASH Flags
  * @brief LL EFLASH Flags 
  * @{
  */


/** @name LL_EFLASH_SR_ErrStaMskTypeDef
  * @brief LL EFLASH SR Error Status Mask Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_SR_ErrStaMskTypeDef                       uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_SR_ErrStaMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_SR_OPE                   (FLASH_SR_OPE_Msk)          /*!< EFLASH OPDR Operation Error                      */
#define LL_EFLASH_SR_PES                   (FLASH_SR_PES_Msk)          /*!< EFLASH Program/Erase Operation Error             */
#define LL_EFLASH_SR_PGE                   (FLASH_SR_PGE_Msk)          /*!< EFLASH Program Error                             */
#define LL_EFLASH_SR_DBC                   (FLASH_SR_DBC_Msk)          /*!< EFLASH Double Bit Error Pending                  */
#define LL_EFLASH_SR_SBC                   (FLASH_SR_SBC_Msk)          /*!< EFLASH Single Bit Error Pending                  */
#define LL_EFLASH_SR_IOS                   (FLASH_SR_IOS_Msk)          /*!< EFLASH Illegal Operation Error                   */
#define LL_EFLASH_SR_WPS                   (FLASH_SR_WPS_Msk)          /*!< EFLASH Write Protect Error                       */
#define LL_EFLASH_SR_OES                   (FLASH_SR_OES_Msk)          /*!< EFLASH Operation Error                           */

/**
  * @brief EFLASH SR Error Flags
  */
#define LL_EFLASH_SR_ERROR_FLAG_MSK                         ((FLASH_SR_OPE_Msk                | FLASH_SR_PES_Msk                | \
                                                              FLASH_SR_PGE_Msk                | FLASH_SR_DBC_Msk                | \
                                                              FLASH_SR_SBC_Msk                | FLASH_SR_IOS_Msk                | \
                                                              FLASH_SR_WPS_Msk                | FLASH_SR_OES_Msk ))

/**
  * @brief EFLASH SR Error Interrupt Flags
  */
#define LL_EFLASH_SR_ERROR_IT_FLAG_MSK                      ((FLASH_SR_SBC_Msk                | FLASH_SR_IOS_Msk                | \
                                                              FLASH_SR_WPS_Msk                | FLASH_SR_OES_Msk ))
/** @} */

/**
  * @}
  */ /* EFLASH_LL_EC_Flags */


/** @defgroup EFLASH_LL_EC_Configuration LL EFLASH Configuration 
  * @brief LL EFLASH Configuration 
  * @{
  */

/** @name LL_EFLASH_BankMapTypeDef
  * @brief EFLASH Bank Map Status definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_BankMapTypeDef                   uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_BankMapTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_BANK_MAP_BANK0                   (0UL)                   /*!< Bank Mapping Bank 0                               */
#define LL_EFLASH_BANK_MAP_BANK1                   (1UL)                   /*!< Bank Mapping Bank 1                               */

#define IS_LL_EFLASH_BANK_MAP(__VAL__)             (((__VAL__) == LL_EFLASH_BANK_MAP_BANK0) || \
                                                    ((__VAL__) == LL_EFLASH_BANK_MAP_BANK1) )
/** @} */

/** @name LL_EFLASH_WorkModeTypeDef
  * @brief EFLASH Work Mode Status definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_WorkModeTypeDef                  uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_WorkModeTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_WORK_MODE_EMPTY                  (0UL)                   /*!< All calibration parameters are normal during self-check.  */
#define LL_EFLASH_WORK_MODE_NORMAL                 (1UL)                   /*!< All calibration parameters are empty during self-check.   */

#define IS_LL_EFLASH_MODE_MAP(__VAL__)             (((__VAL__) == LL_EFLASH_WORK_MODE_EMPTY) || \
                                                    ((__VAL__) == LL_EFLASH_WORK_MODE_NORMAL) )
/** @} */

/** @name LL_EFLASH_ReadProtLvlTypeDef
  * @brief EFLASH Read Protection Level Definition
  * @note When set read protection to level 2, it's no more possible to go back to level 1 or 0
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_ReadProtLvlTypeDef               uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_ReadProtLvlTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_READ_PROT_LVL_0                  (0xAAUL)                  /*!< EFLASH Read Protection Level 0                   */
#define LL_EFLASH_READ_PROT_LVL_1                  (0xFFUL)                  /*!< EFLASH Read Protection Level 1                   */
#define LL_EFLASH_READ_PROT_LVL_2                  (0xCCUL)                  /*!< EFLASH Read Protection Level 2                    \
                                                                                  Warning: when set read protection to level 2,     \
                                                                                  it's no more possible to go back to level 1 or 0 */

#define IS_LL_EFLASH_READ_PROT_LVL(__VAL__)        (((__VAL__) == LL_EFLASH_READ_PROT_LVL_0) || \
                                                    ((__VAL__) == LL_EFLASH_READ_PROT_LVL_1) || \
                                                    ((__VAL__) == LL_EFLASH_READ_PROT_LVL_2) )
/** @} */

/** @name LL_EFLASH_WriteProtAreaTypeDef
  * @brief EFLASH Write Protect Area definition
  * @note  Each area control 2 sectors
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_WriteProtAreaTypeDef             uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_WriteProtAreaTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_WRITE_PROT_AREA_0_1              (BIT(0))                  /*!< EFLASH Write Protection Area 0~1                 */
#define LL_EFLASH_WRITE_PROT_AREA_2_3              (BIT(1))                  /*!< EFLASH Write Protection Area 2~3                 */
#define LL_EFLASH_WRITE_PROT_AREA_4_5              (BIT(2))                  /*!< EFLASH Write Protection Area 4~5                 */
#define LL_EFLASH_WRITE_PROT_AREA_6_7              (BIT(3))                  /*!< EFLASH Write Protection Area 6~7                 */
#define LL_EFLASH_WRITE_PROT_AREA_8_9              (BIT(4))                  /*!< EFLASH Write Protection Area 8~9                 */
#define LL_EFLASH_WRITE_PROT_AREA_10_11            (BIT(5))                  /*!< EFLASH Write Protection Area 10~11               */
#define LL_EFLASH_WRITE_PROT_AREA_12_13            (BIT(6))                  /*!< EFLASH Write Protection Area 12~13               */
#define LL_EFLASH_WRITE_PROT_AREA_14_15            (BIT(7))                  /*!< EFLASH Write Protection Area 14~15               */
#define LL_EFLASH_WRITE_PROT_AREA_16_17            (BIT(8))                  /*!< EFLASH Write Protection Area 16~17               */
#define LL_EFLASH_WRITE_PROT_AREA_18_19            (BIT(9))                  /*!< EFLASH Write Protection Area 18~19               */
#define LL_EFLASH_WRITE_PROT_AREA_20_21            (BIT(10))                 /*!< EFLASH Write Protection Area 20~21               */
#define LL_EFLASH_WRITE_PROT_AREA_22_23            (BIT(11))                 /*!< EFLASH Write Protection Area 22~23               */
#define LL_EFLASH_WRITE_PROT_AREA_24_25            (BIT(12))                 /*!< EFLASH Write Protection Area 24~25               */
#define LL_EFLASH_WRITE_PROT_AREA_26_27            (BIT(13))                 /*!< EFLASH Write Protection Area 26~27               */
#define LL_EFLASH_WRITE_PROT_AREA_28_29            (BIT(14))                 /*!< EFLASH Write Protection Area 28~29               */
#define LL_EFLASH_WRITE_PROT_AREA_30_31            (BIT(15))                 /*!< EFLASH Write Protection Area 30~31               */
#define LL_EFLASH_WRITE_PROT_AREA_32_33            (BIT(16))                 /*!< EFLASH Write Protection Area 32~33               */
#define LL_EFLASH_WRITE_PROT_AREA_34_35            (BIT(17))                 /*!< EFLASH Write Protection Area 34~35               */
#define LL_EFLASH_WRITE_PROT_AREA_36_37            (BIT(18))                 /*!< EFLASH Write Protection Area 36~37               */
#define LL_EFLASH_WRITE_PROT_AREA_38_39            (BIT(19))                 /*!< EFLASH Write Protection Area 38~39               */
#define LL_EFLASH_WRITE_PROT_AREA_40_41            (BIT(20))                 /*!< EFLASH Write Protection Area 40~41               */
#define LL_EFLASH_WRITE_PROT_AREA_42_43            (BIT(21))                 /*!< EFLASH Write Protection Area 42~43               */
#define LL_EFLASH_WRITE_PROT_AREA_44_45            (BIT(22))                 /*!< EFLASH Write Protection Area 44~45               */
#define LL_EFLASH_WRITE_PROT_AREA_46_47            (BIT(23))                 /*!< EFLASH Write Protection Area 46~47               */
#define LL_EFLASH_WRITE_PROT_AREA_48_49            (BIT(24))                 /*!< EFLASH Write Protection Area 48~49               */
#define LL_EFLASH_WRITE_PROT_AREA_50_51            (BIT(25))                 /*!< EFLASH Write Protection Area 50~51               */
#define LL_EFLASH_WRITE_PROT_AREA_52_53            (BIT(26))                 /*!< EFLASH Write Protection Area 52~53               */
#define LL_EFLASH_WRITE_PROT_AREA_54_55            (BIT(27))                 /*!< EFLASH Write Protection Area 54~55               */
#define LL_EFLASH_WRITE_PROT_AREA_56_57            (BIT(28))                 /*!< EFLASH Write Protection Area 56~57               */
#define LL_EFLASH_WRITE_PROT_AREA_58_59            (BIT(29))                 /*!< EFLASH Write Protection Area 58~59               */
#define LL_EFLASH_WRITE_PROT_AREA_60_61            (BIT(30))                 /*!< EFLASH Write Protection Area 60~61               */
#define LL_EFLASH_WRITE_PROT_AREA_62_63            (BIT(31))                 /*!< EFLASH Write Protection Area 62~63               */
#define LL_EFLASH_WRITE_PROT_AREA_ALL              (0xFFFFFFFFUL)            /*!< EFLASH Write Protection Area ALL                 */
#define LL_EFLASH_WRITE_PROT_AREA_MSK              (0xFFFFFFFFUL)            /*!< EFLASH Write Protection Area Mask                */

#define IS_LL_EFLASH_WRITE_PROT_AREA(__VAL__)      (((__VAL__) & LL_EFLASH_WRITE_PROT_AREA_MSK) != 0UL)
/** @} */

/** @name LL_EFLASH_EraseModeTypeDef
  * @brief EFLASH Erase Mode Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_EraseModeTypeDef                 uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_EraseModeTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_ERASE_MODE_SECTOR                (0UL)                     /*!< Erase Mode Sector                                */
#define LL_EFLASH_ERASE_MODE_BANK0                 (1UL)                     /*!< Erase Mode Bank0                                 */
#define LL_EFLASH_ERASE_MODE_BANK1                 (2UL)                     /*!< Erase Mode Bank1                                 */
#define LL_EFLASH_ERASE_MODE_CHIP                  (3UL)                     /*!< Erase Mode Chip                                  */

#define IS_LL_EFLASH_ERASE_MODE(__VAL__)           (((__VAL__) == LL_EFLASH_ERASE_MODE_SECTOR) || \
                                                    ((__VAL__) == LL_EFLASH_ERASE_MODE_BANK0)  || \
                                                    ((__VAL__) == LL_EFLASH_ERASE_MODE_BANK1)  || \
                                                    ((__VAL__) == LL_EFLASH_ERASE_MODE_CHIP)   )
/** @} */

/** @name LL_EFLASH_BankAddrMapTypeDef
  * @brief EFLASH Bank Address Mapping Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_BankAddrMapTypeDef               uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_BankAddrMapTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_BANK_ADDR_MAP_BANK0              (0xFUL)                   /*!< Bank Address Mapping Bank 0                      */
#define LL_EFLASH_BANK_ADDR_MAP_BANK1              (0xAUL)                   /*!< Bank Address Mapping Bank 1                      */

#define IS_LL_EFLASH_BANK_ADDR_MAP(__VAL__)        (((__VAL__) == LL_EFLASH_BANK_ADDR_MAP_BANK0) || \
                                                    ((__VAL__) == LL_EFLASH_BANK_ADDR_MAP_BANK1) )
/** @} */

/** @name LL_EFLASH_BankModeTypeDef
  * @brief EFLASH Bank Mode Definition
  * @note  Only Valid in 256K Mode
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_BankModeTypeDef                  uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_BankModeTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_BANK_MODE_SINGLE                 (0xFUL)                   /*!< Bank Mode Single                                 */
#define LL_EFLASH_BANK_MODE_DOUBLE                 (0xAUL)                   /*!< Bank Mode Double                                 */

#define IS_LL_EFLASH_BANK_MODE(__VAL__)            (((__VAL__) == LL_EFLASH_BANK_MODE_SINGLE) || \
                                                    ((__VAL__) == LL_EFLASH_BANK_MODE_DOUBLE) )
/** @} */

/** @name LL_EFLASH_BORVolLimitTypeDef
  * @brief EFLASH BOR Voltage Limit Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_BORVolLimitTypeDef               uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_BORVolLimitTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_BOR_VOL_LIMIT_2V4                (0UL)                     /*!< BOR Voltage Limit 2.4V                           */
#define LL_EFLASH_BOR_VOL_LIMIT_2V55               (1UL)                     /*!< BOR Voltage Limit 2.55V                          */
#define LL_EFLASH_BOR_VOL_LIMIT_2V7                (2UL)                     /*!< BOR Voltage Limit 2.7V                           */
#define LL_EFLASH_BOR_VOL_LIMIT_2V85               (3UL)                     /*!< BOR Voltage Limit 2.85V                          */

#define IS_LL_EFLASH_BOR_VOL_LIMIT(__VAL__)        (((__VAL__) == LL_EFLASH_BOR_VOL_LIMIT_2V4)  || \
                                                    ((__VAL__) == LL_EFLASH_BOR_VOL_LIMIT_2V55) || \
                                                    ((__VAL__) == LL_EFLASH_BOR_VOL_LIMIT_2V7)  || \
                                                    ((__VAL__) == LL_EFLASH_BOR_VOL_LIMIT_2V85) )
/** @} */

/** @name LL_EFLASH_BootSelTypeDef
  * @brief EFLASH Boot Selection Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_BootSelTypeDef                   uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_BootSelTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_BOOT_SEL_0                       (0UL)                     /*!< Boot Selection 0                                 */
#define LL_EFLASH_BOOT_SEL_1                       (1UL)                     /*!< Boot Selection 1                                 */
#define LL_EFLASH_BOOT_SEL_2                       (2UL)                     /*!< Boot Selection 2                                 */
#define LL_EFLASH_BOOT_SEL_3                       (3UL)                     /*!< Boot Selection 3                                 */
#define LL_EFLASH_BOOT_SEL_4                       (4UL)                     /*!< Boot Selection 4                                 */
#define LL_EFLASH_BOOT_SEL_5                       (5UL)                     /*!< Boot Selection 5                                 */
#define LL_EFLASH_BOOT_SEL_6                       (6UL)                     /*!< Boot Selection 6                                 */
#define LL_EFLASH_BOOT_SEL_7                       (7UL)                     /*!< Boot Selection 7                                 */

#define IS_LL_EFLASH_BOOT_SEL(__VAL__)             (((__VAL__) == LL_EFLASH_BOOT_SEL_0) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_SEL_1) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_SEL_2) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_SEL_3) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_SEL_4) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_SEL_5) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_SEL_6) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_SEL_7) )
/** @} */

/** @name LL_EFLASH_WWDGDefEnTypeDef
  * @brief EFLASH WWDG Default Enable Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_WWDGDefEnTypeDef                 uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_WWDGDefEnTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_WWDG_DEFAULT_DISABLE             (0xFUL)                   /*!< WWDG Default Disable                             */
#define LL_EFLASH_WWDG_DEFAULT_ENABLE              (0xAUL)                   /*!< WWDG Default Enable                              */

#define IS_LL_EFLASH_WWDG_DEFAULT(__VAL__)         (((__VAL__) == LL_EFLASH_WWDG_DEFAULT_DISABLE) || \
                                                    ((__VAL__) == LL_EFLASH_WWDG_DEFAULT_ENABLE)  )
/** @} */

/** @name LL_EFLASH_IWDGDefEnTypeDef
  * @brief EFLASH IWDG Default Enable Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_IWDGDefEnTypeDef                 uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_IWDGDefEnTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_IWDG_DEFAULT_DISABLE             (0xFUL)                   /*!< IWDG Default Disable                             */
#define LL_EFLASH_IWDG_DEFAULT_ENABLE              (0xAUL)                   /*!< IWDG Default Enable                              */

#define IS_LL_EFLASH_IWDG_DEFAULT(__VAL__)         (((__VAL__) == LL_EFLASH_IWDG_DEFAULT_DISABLE) || \
                                                    ((__VAL__) == LL_EFLASH_IWDG_DEFAULT_ENABLE)  )
/** @} */

/** @name LL_EFLASH_PwrOnEccBypassTypeDef
  * @brief EFLASH FLASH Power-On ECC Bypass Enable Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_PwrOnEccBypassTypeDef            uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_PwrOnEccBypassTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_PWRON_ECC_BYPASS_DISABLE         (0xAUL)                   /*!< FLASH Power-On ECC Bypass Disable                */
#define LL_EFLASH_PWRON_ECC_BYPASS_ENABLE          (0xFUL)                   /*!< FLASH Power-On ECC Bypass Enable                 */

#define IS_LL_EFLASH_PWRON_ECC_BYPASS(__VAL__)     (((__VAL__) == LL_EFLASH_PWRON_ECC_BYPASS_DISABLE) || \
                                                    ((__VAL__) == LL_EFLASH_PWRON_ECC_BYPASS_ENABLE)  )
/** @} */

/** @name LL_EFLASH_BootLockCfgTypeDef
  * @brief EFLASH Boot Lock Config Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define LL_EFLASH_BootLockCfgTypeDef               uint32_t         
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t LL_EFLASH_BootLockCfgTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define LL_EFLASH_BOOT_LOCK_CFG_UNLOCK             (0xFUL)                   /*!< Boot Lock Config Unlock                          */
#define LL_EFLASH_BOOT_LOCK_CFG_LOCK               (0xAUL)                   /*!< Boot Lock Config Lock                            */

#define IS_LL_EFLASH_BOOT_LOCK_CFG(__VAL__)        (((__VAL__) == LL_EFLASH_BOOT_LOCK_CFG_UNLOCK) || \
                                                    ((__VAL__) == LL_EFLASH_BOOT_LOCK_CFG_LOCK)   )
/** @} */

/**
  * @}
  */ /* EFLASH_LL_EC_Configuration */

/**
  * @}
  */ /* EFLASH_LL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup EFLASH_LL_Exported_Macros EFLASH LL Exported Macros
  * @brief    EFLASH LL Exported Macros
  * @{
  */

/**
  * @brief EFLASH Bank Map Value Mask
  */
#define LL_EFLASH_BANK_MAP_VAL_MSK(Val)             (Val & FLASH_OPDR_MAP_Val)

/**
  * @brief EFLASH Bank Mode Value Mask
  */
#define LL_EFLASH_BANK_MODE_VAL_MSK(Val)            (Val & FLASH_OPDR_BMD_Val)

/**
  * @brief EFLASH Boot Select Value Mask
  */
#define LL_EFLASH_BOOT_SEL_VAL_MSK(Val)             (Val & FLASH_OPDR_BSEL_Val)

/**
  * @brief EFLASH BOR Voltage Limit Mask
  */
#define LL_EFLASH_BOR_VOL_LIMIT_VAL_MSK(Val)        (Val & FLASH_OPDR_BORLV_Val)

/**
  * @}
  */ /* EFLASH_LL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup EFLASH_LL_Exported_Functions EFLASH LL Functions
  * @brief    EFLASH LL Exported Functions
  * @{
  */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#pragma push_macro("ASSERT_INLINE_PARAM")
#undef ASSERT_INLINE_PARAM
#if defined(TAE32_USE_LL_EFLASH_ASSERT_INLINE_PARAM) && (TAE32_USE_LL_EFLASH_ASSERT_INLINE_PARAM == 1)
extern void LL_EFLASH_Assert_Inline_Failed(uint8_t *File, uint32_t Line);
#define ASSERT_INLINE_PARAM(expr) ((expr) ? (void)0U : LL_EFLASH_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else  /* TAE32_USE_LL_EFLASH_ASSERT_INLINE_PARAM */
#define ASSERT_INLINE_PARAM(expr) ((void)0U)
#endif /* TAE32_USE_LL_EFLASH_ASSERT_INLINE_PARAM */
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/** @defgroup EFLASH_LL_EF_Configuration LL EFLASH Configuration
  * @brief    LL EFLASH Configuration
  * @{
  */

/**
  * @brief  Program/Erase Lock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetProgramEraseLock(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_LCK_Msk);
}

/**
  * @brief  Judge Program/Erase is Lock or Unlock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Program/Erase is Unlock
  * @retval 1 Program/Erase is Lock
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsProgramEraseLock(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->CR, FLASH_CR_LCK_Msk, FLASH_CR_LCK_Pos));
}

/**
  * @brief  FLASH nBits ECC NMI Interrupt Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EnableIT_NMIE(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_NMIE_Msk);
}

/**
  * @brief  FLASH nBits ECC NMI Interrupt Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_DisableIT_NMIE(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->CR, FLASH_CR_NMIE_Msk);
}

/**
  * @brief  Judge is nBits ECC NMI Interrupt Enable or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 ECC NMI Interrupt is Disable
  * @retval 1 ECC NMI Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsEnabledIT_NMIE(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->CR, FLASH_CR_NMIE_Msk, FLASH_CR_NMIE_Pos));
}

/**
  * @brief  Error Interrupt Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EnableIT_EIE(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_EIE_Msk);
}

/**
  * @brief  Error Interrupt Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_DisableIT_EIE(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->CR, FLASH_CR_EIE_Msk);
}

/**
  * @brief  Judge is Error Interrupt Enable or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Error Interrupt is Disable
  * @retval 1 Error Interrupt is Enable
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsEnabledIT_EIE(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->CR, FLASH_CR_EIE_Msk, FLASH_CR_EIE_Pos));
}

/**
  * @brief  Launch Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_LaunchRWProtectUpdate(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_FLE_Msk);
}

/**
  * @brief  EFLASH D BUS Prefetch feature Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @note   Prefetch feature should not be enabled when CPU frequency is lower than 40MHz
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EnableDBusPrefetch(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_DPE_Msk);
}

/**
  * @brief  EFLASH D BUS Prefetch feature Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_DisableDBusPrefetch(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->CR, FLASH_CR_DPE_Msk);
}

/**
  * @brief  Judge is EFLASH D BUS Prefetch feature Enable or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 EFLASH D BUS Prefetch feature is Disable
  * @retval 1 EFLASH D BUS Prefetch feature is Enable
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsDBusPrefetchEnable(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->CR, FLASH_CR_DPE_Msk, FLASH_CR_DPE_Pos));
}

/**
  * @brief  EFLASH I BUS Prefetch feature Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @note   Prefetch feature should not be enabled when CPU frequency is lower than 40MHz
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EnableIBusPrefetch(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_IPE_Msk);
}

/**
  * @brief  EFLASH I BUS Prefetch feature Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_DisableIBusPrefetch(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->CR, FLASH_CR_IPE_Msk);
}

/**
  * @brief  Judge is EFLASH I BUS Prefetch feature Enable or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 EFLASH I BUS Prefetch feature is Disable
  * @retval 1 EFLASH I BUS Prefetch feature is Enable
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsIBusPrefetchEnable(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->CR, FLASH_CR_IPE_Msk, FLASH_CR_IPE_Pos));
}

/**
  * @brief  Flash Cache Refresh
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_CacheRefresh(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_CRS_Msk);
}

/**
  * @brief  Erase Start
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EraseStart(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_ES_Msk);
}

/**
  * @brief  Judge is Erase Operation Done or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Erase Operation isn't Done
  * @retval 1 Erase Operation is Done
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsEraseOpDone(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!READ_BIT_SHIFT(EFLASHx->CR, FLASH_CR_ES_Msk, FLASH_CR_ES_Pos)));
}

/**
  * @brief  Program Start
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ProgramStart(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->CR, FLASH_CR_PS_Msk);
}

/**
  * @brief  Judge is Program Operation Done or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Program Operation isn't Done
  * @retval 1 Program Operation is Done
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsProgramOpDone(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!READ_BIT_SHIFT(EFLASHx->CR, FLASH_CR_PS_Msk, FLASH_CR_PS_Pos)));
}

/**
  * @brief  Wakeup/Standby Unlock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_UnlockWakeupStdbyConfig(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->LPR, FLASH_LPR_LCK_Msk);
}

/**
  * @brief  Wakeup/Standby Lock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_LockWakeupStdbyConfig(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->LPR, FLASH_LPR_LCK_Msk);
}

/**
  * @brief  Judge Wakeup/Standby is Lock or Unlock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Wakeup/Standby is Lock
  * @retval 1 Wakeup/Standby is Unlock
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsWakeupStdbyConfigUnlock(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->LPR, FLASH_LPR_LCK_Msk, FLASH_LPR_LCK_Pos));
}

/**
  * @brief  Bank0 Lowpower Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EnableBank0LowPower(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->LPR, BIT(2));///TODO
}

/**
  * @brief  Bank0 Lowpower Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_DisableBank0LowPower(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->LPR, BIT(2));
}

/**
  * @brief  Bank1 Lowpower Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EnableBank1LowPower(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->LPR, BIT(3));
}

/**
  * @brief  Bank1 Lowpower Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_DisableBank1LowPower(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->LPR, BIT(3));
}

/**
  * @brief  Wakeup Start
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_WakeupStart(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->LPR, FLASH_LPR_LW_Msk);
}

/**
  * @brief  Judge is Wakeup Operation Done or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Wakeup Operation isn't Done
  * @retval 1 Wakeup Operation is Done
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsWakeupOpDone(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!READ_BIT_SHIFT(EFLASHx->LPR, FLASH_LPR_LW_Msk, FLASH_LPR_LW_Pos)));
}

/**
  * @brief  Standby Start
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_StdbyStart(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->LPR, FLASH_LPR_LS_Msk);
}

/**
  * @brief  Judge is Standby Operation Done or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Standby Operation isn't Done
  * @retval 1 Standby Operation is Done
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsStdbyOpDone(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!READ_BIT_SHIFT(EFLASHx->LPR, FLASH_LPR_LS_Msk, FLASH_LPR_LS_Pos)));
}

/**
  * @brief  Judge is Program/Erase & Low Power & Read/Write Protect & Option Data Operation Done or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Program/Erase & Low Power & Read/Write Protect & Option Data Operation isn't Done
  * @retval 1 Program/Erase & Low Power & Read/Write Protect & Option Data Operation is Done
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsIdle(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_BST_Msk, FLASH_SR_BST_Pos)));
}

/**
  * @brief  Bank Map Status Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return Bank Number @ref LL_EFLASH_BankMapTypeDef
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetBankMapping(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_BMS_Msk, FLASH_SR_BMS_Pos));
}

/**
  * @brief  Judge is Read/Write Protect / Option Data Operation Error Status or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Read/Write Protect / Option Data Operation Error Status
  * @retval 1 is Read/Write Protect / Option Data Operation Error Status
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_OPE(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_OPE_Msk, FLASH_SR_OPE_Pos));
}

/**
  * @brief  Read/Write Protect / Option Data Operation Error Status Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_OPE(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_OPE_Msk);
}

/**
  * @brief  Judge is Program/Erase Operation Error Status or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Program/Erase Operation Error Status
  * @retval 1 is Program/Erase Operation Error Status
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_PES(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_PES_Msk, FLASH_SR_PES_Pos));
}

/**
  * @brief  Program/Erase Operation Error Status Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_PES(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_PES_Msk);
}

/**
  * @brief  Judge is Program Error Status or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Program Error Status
  * @retval 1 is Program Error Status
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_PGE(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_PGE_Msk, FLASH_SR_PGE_Pos));
}

/**
  * @brief  Program Error Status Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_PGE(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_PGE_Msk);
}

/**
  * @brief  Option Bank Map Status Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return Bank Number @ref LL_EFLASH_BankMapTypeDef
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetOptionBankMap(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_BM_Msk, FLASH_SR_BM_Pos));
}

/**
  * @brief  Work Mode Status Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return Work Mode Status @ref LL_EFLASH_WorkModeTypeDef
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetWorkMode(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_WM_Msk, FLASH_SR_WM_Pos));
}

/**
  * @brief  Judge is Double Bit Error Pending or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Double Bit Error Pending
  * @retval 1 is Double Bit Error Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_DBC(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_DBC_Msk, FLASH_SR_DBC_Pos));
}

/**
  * @brief  Double Bit Error Pending Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_DBC(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_DBC_Msk);
}

/**
  * @brief  Judge is Single Bit Error Pending or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Single Bit Error Pending
  * @retval 1 is Single Bit Error Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_SBC(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_SBC_Msk, FLASH_SR_SBC_Pos));
}

/**
  * @brief  Single Bit Error Pending Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_SBC(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_SBC_Msk);
}

/**
  * @brief  Judge is Read/Write Protect / Option Data Operation Done or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Read/Write Protect / Option Data Operation isn't Done
  * @retval 1 Read/Write Protect / Option Data Operation is Done
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsRwProtOptDatOpDone(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_BSY_Msk, FLASH_SR_BSY_Pos)));
}

/**
  * @brief  Judge is Illegal Operation Error Pending or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Illegal Operation Error Pending
  * @retval 1 is Illegal Operation Error Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_IOS(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_IOS_Msk, FLASH_SR_IOS_Pos));
}

/**
  * @brief  Illegal Operation Error Pending Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_IOS(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_IOS_Msk);
}

/**
  * @brief  Judge is Write Protect Error Pending or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Write Protect Error Pending
  * @retval 1 is Write Protect Error Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_WPS(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_WPS_Msk, FLASH_SR_WPS_Pos));
}

/**
  * @brief  Write Protect Error Pending Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_WPS(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_WPS_Msk);
}

/**
  * @brief  Judge is Operation Error Pending or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 isn't Operation Error Pending
  * @retval 1 is Operation Error Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag_OES(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->SR, FLASH_SR_OES_Msk, FLASH_SR_OES_Pos));
}

/**
  * @brief  Operation Error Pending Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag_OES(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, FLASH_SR_OES_Msk);
}

/**
  * @brief  Judge has Any Error Pending or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 hasn't Any Error Pending
  * @retval 1 has Any Error Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsAnyErrorActive(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!!READ_BIT(EFLASHx->SR, LL_EFLASH_SR_ERROR_FLAG_MSK)) ? 1UL : 0UL);
}

/**
  * @brief  All Error Pending Clear
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearAllErrorFlags(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, LL_EFLASH_SR_ERROR_FLAG_MSK);
}

/**
  * @brief  All Interrupt Pending Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetErrorStatus(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT(EFLASHx->SR, LL_EFLASH_SR_ERROR_FLAG_MSK));
}

/**
  * @brief  All Interrupt Pending Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return All Interrupt Pending
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetInterruptFlags(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_REG(EFLASHx->SR));
}

/**
  * @brief  Program Data 0 Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Dat Program Data 0
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetProgramData0(EFLASH_TypeDef *EFLASHx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->PDR0, Dat);
}

/**
  * @brief  Program Data 1 Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Dat Program Data 1
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetProgramData1(EFLASH_TypeDef *EFLASHx, uint32_t Dat)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->PDR1, Dat);
}

/**
  * @brief  Erase Mode Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Mode Erase Mode @ref LL_EFLASH_EraseModeTypeDef
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetEraseMode(EFLASH_TypeDef *EFLASHx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->PAR, FLASH_PAR_EM_Msk, (((Mode) & FLASH_PAR_EM_Val) << FLASH_PAR_EM_Pos));
}

/**
  * @brief  Erase Sector Number Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Num Erase Sector Number
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetEraseSectorNumber(EFLASH_TypeDef *EFLASHx, uint32_t Num)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->PAR, FLASH_PAR_PA_Msk, (((Num) & 0x3fUL) << FLASH_PAR_PA_Pos));
}

/**
  * @brief  Erase Sector Number Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return Erase Sector Number
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetEraseSectorNumber(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->PAR, FLASH_PAR_PA_Msk, FLASH_PAR_PA_Pos));
}

/**
  * @brief  Program Address Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Addr Program Address
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetProgramAddress(EFLASH_TypeDef *EFLASHx, uint32_t Addr)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->PAR, FLASH_PAR_PA_Msk, (((Addr) & FLASH_PAR_PA_Val) << FLASH_PAR_PA_Pos));
}

/**
  * @brief  Read/Write Protect / Option Data Lock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_LockRwProtOptDatConfig(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->KR, FLASH_KR_PLK_Msk);
}

/**
  * @brief  Judge Read/Write Protect / Option Data is Lock or Unlock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Read/Write Protect / Option Data is Unlock
  * @retval 1 Read/Write Protect / Option Data is Lock
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsRwProtOptDatConfigLock(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!READ_BIT_SHIFT(EFLASHx->KR, FLASH_KR_PLK_Msk, FLASH_KR_PLK_Pos)));
}

/**
  * @brief  Key Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Key Key @ref EFLASH_LL_EC_Keys
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetKey(EFLASH_TypeDef *EFLASHx, uint32_t Key)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->KR, FLASH_KR_KEY_Msk & (((Key) & FLASH_KR_KEY_Val) << FLASH_KR_KEY_Pos));
}

/**
  * @brief  Key get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return Key @ref EFLASH_LL_EC_Keys
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetKey(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->KR, FLASH_KR_KEY_Msk, FLASH_KR_KEY_Pos));
}

/**
  * @brief  Read Protect Register Value Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Val Read Protect Register Value
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetReadProt(EFLASH_TypeDef *EFLASHx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->RPR, ((Val) & FLASH_RPR_RPLV_Val));
}

/**
  * @brief  Write Protect Register Value Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Val Write Protect Register Value
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_SetWriteProt(EFLASH_TypeDef *EFLASHx, uint32_t Val)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->WPR, Val & FLASH_WPR_WRPC_Val);
}

/**
  * @brief  Write Protect Area Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Area Write Protect Area @ref LL_EFLASH_WriteProtAreaTypeDef
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_EnableWriteProtArea(EFLASH_TypeDef *EFLASHx, uint32_t Area)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    CLEAR_BIT(EFLASHx->WPR, Area & FLASH_WPR_WRPC_Val);
}

/**
  * @brief  Write Protect Register Value Read
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return Write Protect Register Value
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetWriteProtArea(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_REG(EFLASHx->WPR));
}

/**
  * @brief  Write Protect Area Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Area Write Protect Area  @ref LL_EFLASH_WriteProtAreaTypeDef
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_DisableWriteProtArea(EFLASH_TypeDef *EFLASHx, uint32_t Area)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    SET_BIT(EFLASHx->WPR, Area);
}

/**
  * @brief  Bank Address Mapping Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Bank Bank Address Mapping bank @ref LL_EFLASH_BankAddrMapTypeDef
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_SetBankMap(EFLASH_TypeDef *EFLASHx, uint32_t Bank)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_MAP_Msk, (((Bank) & FLASH_OPDR_MAP_Val) << FLASH_OPDR_MAP_Pos));
}

/**
  * @brief  Bank Address Mapping Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0xA   Bank1 Mapping
  * @retval Other Bank0 Mapping
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_GetBankMap(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_MAP_Msk, FLASH_OPDR_MAP_Pos));
}

/**
  * @brief  Bank Mode Config
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Mode Bank mode
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_SetBankMode(EFLASH_TypeDef *EFLASHx, uint32_t Mode)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_BMD_Msk, (((Mode) & FLASH_OPDR_BMD_Val) << FLASH_OPDR_BMD_Pos));
}

/**
  * @brief  Bank Mode Get
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0xA   Bank mode Double
  * @retval Other Bank mode Single
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_GetBankMode(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_BMD_Msk, FLASH_OPDR_BMD_Pos));
}

/**
  * @brief  WWDG Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_WWDGDefaultEnable(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_WWEN_Msk, LL_EFLASH_WWDG_DEFAULT_ENABLE << FLASH_OPDR_WWEN_Pos);
}

/**
  * @brief  WWDG Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_WWDGDefaultDisable(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_WWEN_Msk, LL_EFLASH_WWDG_DEFAULT_DISABLE << FLASH_OPDR_WWEN_Pos);
}

/**
  * @brief  Judge is WWDG Enable or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 WWDG is Disable
  * @retval 1 WWDG is Enable
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_IsWWDGDefaultEnable(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(((READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_WWEN_Msk, FLASH_OPDR_WWEN_Pos) == LL_EFLASH_WWDG_DEFAULT_ENABLE)) ? 1UL : 0UL);
}

/**
  * @brief  IWDG Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_IWDGDefaultEnable(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_IWEN_Msk, LL_EFLASH_IWDG_DEFAULT_ENABLE << FLASH_OPDR_IWEN_Pos);
}


/**
  * @brief  IWDG Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_IWDGDefaultDisable(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_IWEN_Msk, LL_EFLASH_IWDG_DEFAULT_DISABLE << FLASH_OPDR_IWEN_Pos);
}

/**
  * @brief  Judge is IWDG Enable or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 IWDG is Disable
  * @retval 1 IWDG is Enable
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_IsIWDGDefaultEnable(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(((READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_IWEN_Msk, FLASH_OPDR_IWEN_Pos) == LL_EFLASH_IWDG_DEFAULT_ENABLE)) ? 1UL : 0UL);
}

/**
  * @brief  Power On ECC Bypass Enable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_EnablePowerOnECCBypass(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_EBP_Msk, LL_EFLASH_PWRON_ECC_BYPASS_ENABLE << FLASH_OPDR_EBP_Pos);
}

/**
  * @brief  Power On ECC Bypass Disable
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_DisablePowerOnECCBypass(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_EBP_Msk, LL_EFLASH_PWRON_ECC_BYPASS_DISABLE << FLASH_OPDR_EBP_Pos);
}

/**
  * @brief  Judge is Power On ECC Bypass Enable or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Power On ECC Bypass is Disable
  * @retval 1 Power On ECC Bypass is Enable
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_IsPowerOnECCBypassEnable(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)((!(READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_EBP_Msk, FLASH_OPDR_EBP_Pos) == LL_EFLASH_PWRON_ECC_BYPASS_DISABLE)) ? 1UL : 0UL);
}

/**
  * @brief  BOR Voltage Limit Config
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Vol BOR Voltage Limit @ref LL_EFLASH_BORVolLimitTypeDef
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_SetBORVoltageLimit(EFLASH_TypeDef *EFLASHx, uint32_t Vol)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_BORLV_Msk, (((Vol) & FLASH_OPDR_BORLV_Val) << FLASH_OPDR_BORLV_Pos));
}

/**
  * @brief  BOR Voltage Limit Read
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return BOR Voltage Limit
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_GetBORVoltageLimit(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_BORLV_Msk, FLASH_OPDR_BORLV_Pos));
}

/**
  * @brief  Boot Selection Set
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Sel Boot Selection @ref LL_EFLASH_BootSelTypeDef
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_SetBootSelect(EFLASH_TypeDef *EFLASHx, uint32_t Sel)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_BSEL_Msk, (((Sel) & FLASH_OPDR_BSEL_Val) << FLASH_OPDR_BSEL_Pos));
}

/**
  * @brief  Boot Selection Read
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return Boot Selection
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_GetBootSelect(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_BSEL_Msk, FLASH_OPDR_BSEL_Pos));
}

/**
  * @brief  Boot Lock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_LockBoot(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_BLK_Msk, LL_EFLASH_BOOT_LOCK_CFG_LOCK << FLASH_OPDR_BLK_Pos);
}

/**
  * @brief  Boot Unlock
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OB_UnlockBoot(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    MODIFY_REG(EFLASHx->OPDR, FLASH_OPDR_BLK_Msk, LL_EFLASH_BOOT_LOCK_CFG_UNLOCK << FLASH_OPDR_BLK_Pos);
}

/**
  * @brief  Judge is Boot Lock or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0 Boot is Unlock
  * @retval 1 Boot is Lock
  */
__STATIC_INLINE uint32_t LL_EFLASH_OB_IsBootLock(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(((READ_BIT_SHIFT(EFLASHx->OPDR, FLASH_OPDR_BLK_Msk, FLASH_OPDR_BLK_Pos) == LL_EFLASH_BOOT_LOCK_CFG_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  OPDR Read
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return OPDR
  */
__STATIC_INLINE uint32_t LL_EFLASH_OPDR_Read(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_REG(EFLASHx->OPDR));
}

/**
  * @brief  OPDR Refresh
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_OPDR_Refresh(EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    __DSB();
    __ISB();
    (void)(READ_REG(EFLASHx->OPDR));
}

/**
  * @brief  Judge EFLASH is 128KB Size or not
  * @param  EFLASHx Specifies EFLASH peripheral
  * @retval 0: 256K
  * @retval 1: 128K
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsSize128KB(const EFLASH_TypeDef *EFLASHx)
{
    PARAM_UNUSED(EFLASHx);

    return ((READ_BIT_SHIFT((*(__IO uint32_t *)LL_EFLASH_REG_ADDR_CHIP_SIZE_MODE), 
            LL_EFLASH_REG_CHIP_SIZE_MODE_MSK, LL_EFLASH_REG_CHIP_SIZE_MODE_POS) == LL_EFLASH_CHIP_SIZE_MODE_128K) ? 1UL : 0UL);///TODO
}

/**
  * @brief  ECC 1Bit Address Get
  * @note   Single Bank, align address by 128bit. Double Bank, align address by 64bit.
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return ECC Error Address for one bit
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetOneBitECCErrorAddress(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->EAR0, FLASH_EAR0_EAD1_Msk, FLASH_EAR0_EAD1_Pos));
}

/**
  * @brief  ECC nBit Address Get
  * @note   Single Bank, align address by 128bit. Double Bank, align address by 64bit.
  * @param  EFLASHx Specifies EFLASH peripheral
  * @return ECC Error Address for multi-bit
  */
__STATIC_INLINE uint32_t LL_EFLASH_GetMultiBitECCErrorAddress(const EFLASH_TypeDef *EFLASHx)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    return (uint32_t)(READ_BIT_SHIFT(EFLASHx->EAR1, FLASH_EAR1_EADn_Msk, FLASH_EAR1_EADn_Pos));
}

/**
  * @brief  Judge EFLASH program address or size is align 8bytes or not
  * @param  Num program address or size to judge
  * @retval 0 EFLASH program address or size isn't align 8bytes
  * @retval 1 EFLASH program address or size is align 8bytes
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(uint32_t Num)
{
    return (uint32_t)(!(Num & 7));
}

/**
  * @}
  */ /* EFLASH_LL_EF_Configuration */


/** @defgroup EFLASH_LL_EF_IT_Management LL EFLASH Interrupt Management
  * @brief LL EFLASH Interrupt Management
  * @{
  */


/**
  * @brief  Clear Interrupt Pending
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Mask Mask to check @ref LL_EFLASH_SR_ErrStaMskTypeDef
  * @return None
  */
__STATIC_INLINE void LL_EFLASH_ClearFlag(EFLASH_TypeDef *EFLASHx, uint32_t Mask)
{
    ASSERT_INLINE_PARAM(IS_EFLASH_ALL_INSTANCE(EFLASHx));

    WRITE_REG(EFLASHx->SR, (Mask) & LL_EFLASH_SR_ERROR_IT_FLAG_MSK);
}

/**
  * @brief  Get Interrupt Pending.
  * @param  EFLASHx Specifies EFLASH peripheral
  * @param  Mask Mask to check @ref LL_EFLASH_SR_ErrStaMskTypeDef
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EFLASH_IsActiveFlag(const EFLASH_TypeDef *EFLASHx, uint32_t Mask)
{
    return (uint32_t)((READ_BIT(EFLASHx->SR, Mask) & LL_EFLASH_SR_ERROR_IT_FLAG_MSK) ? 1UL : 0UL);
}


/**
  * @}
  */ /* EFLASH_LL_EF_IT_Management */

#if defined(TAE32_USE_ASSERT_INLINE_MANAGEMENT)
#undef ASSERT_INLINE_PARAM
#pragma pop_macro("ASSERT_INLINE_PARAM")
#endif /* TAE32_USE_ASSERT_INLINE_MANAGEMENT */

/**
  * @}
  */ /* EFLASH_LL_Exported_Functions */

/**
  * @}
  */ /* EFLASH_LL */

#endif /* EFLASH */

/**
  * @}
  */ /* TAE32F561x_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32F561X_LL_EFLASH_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

