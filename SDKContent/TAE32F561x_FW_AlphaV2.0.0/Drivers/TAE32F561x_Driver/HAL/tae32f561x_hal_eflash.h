/**
  ******************************************************************************
  * @file    tae32f561x_hal_eflash.h
  * @author  Tai-Action SD Team
  * @brief   Header file for EFLASH HAL module
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
#ifndef _TAE32F561X_HAL_EFLASH_H_
#define _TAE32F561X_HAL_EFLASH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f561x_hal_def.h"
#include "tae32f561x_ll_eflash.h"


/** @addtogroup TAE32F561x_HAL_Driver
  * @{
  */

#if defined(EFLASH)

/** @addtogroup EFLASH_HAL EFLASH HAL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup EFLASH_HAL_Exported_Constants EFLASH HAL Exported Constants
  * @brief    EFLASH HAL Exported Constants
  * @{
  */

/** 
  * @brief EFLASH Default Timeout Definition, 300ms
  */
#define HAL_EFLASH_DEFAULT_TIMEOUT              (300UL)

/** 
  * @brief EFLASH Write Protect Operation Timeout Definition, 1500ms
  */
#define HAL_EFLASH_WRITE_PROTECT_TIMEOUT        (1500UL)

/** 
  * @brief EFLASH Program address mask Definition
  */
#define HAL_EFLASH_PROG_ADDRESS_MASK            (0x00FFFFFFUL)

/** 
  * @brief EFLASH Option Data Value Safety
  */
#define HAL_EFLASH_OPT_DAT_VAL_RANGE            (0x100UL)
#define HAL_EFLASH_OPT_DAT_VAL_BASE             (0x8000UL)

/**
  * @brief EFLASH Option Data Definition
  */
#define HAL_EFLASH_OPT_DAT_BOOT_LOCK_CFG        (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*0)  /*!< Boot Lock Config       */
#define HAL_EFLASH_OPT_DAT_BOOT_SEL             (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*1)  /*!< Boot Selection         */
#define HAL_EFLASH_OPT_DAT_BOR_VOL_LMT_CFG      (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*2)  /*!< BOR Vol Limit Config   */
#define HAL_EFLASH_OPT_DAT_PWRON_ECC_BYPASS     (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*3)  /*!< Power On ECC Bypass    */
#define HAL_EFLASH_OPT_DAT_IWDG_DEFAULT_EN      (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*4)  /*!< IWDG Default Enable    */
#define HAL_EFLASH_OPT_DAT_WWDG_DEFAULT_EN      (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*5)  /*!< WWDG Default Enable    */
#define HAL_EFLASH_OPT_DAT_BANK_MODE_CFG        (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*6)  /*!< Bank Mode Config       */
#define HAL_EFLASH_OPT_DAT_BANK_MAP_CFG         (HAL_EFLASH_OPT_DAT_VAL_BASE + HAL_EFLASH_OPT_DAT_VAL_RANGE*7)  /*!< Bank Mapping Config    */

/** @name HAL_EFLASH_WriteProtAreaTypeDef
  * @brief EFLASH Write Protect Area Enum definition
  * @note  Each area control 2 sectors
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_EFLASH_WriteProtAreaTypeDef         LL_EFLASH_WriteProtAreaTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_EFLASH_WriteProtAreaTypeDef HAL_EFLASH_WriteProtAreaTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_EFLASH_WRITE_PROT_AREA_0_1          LL_EFLASH_WRITE_PROT_AREA_0_1       /*!< EFLASH Write Protection Area 0~1    */
#define HAL_EFLASH_WRITE_PROT_AREA_2_3          LL_EFLASH_WRITE_PROT_AREA_2_3       /*!< EFLASH Write Protection Area 2~3    */
#define HAL_EFLASH_WRITE_PROT_AREA_4_5          LL_EFLASH_WRITE_PROT_AREA_4_5       /*!< EFLASH Write Protection Area 4~5    */
#define HAL_EFLASH_WRITE_PROT_AREA_6_7          LL_EFLASH_WRITE_PROT_AREA_6_7       /*!< EFLASH Write Protection Area 6~7    */
#define HAL_EFLASH_WRITE_PROT_AREA_8_9          LL_EFLASH_WRITE_PROT_AREA_8_9       /*!< EFLASH Write Protection Area 8~9    */
#define HAL_EFLASH_WRITE_PROT_AREA_10_11        LL_EFLASH_WRITE_PROT_AREA_10_11     /*!< EFLASH Write Protection Area 10~11  */
#define HAL_EFLASH_WRITE_PROT_AREA_12_13        LL_EFLASH_WRITE_PROT_AREA_12_13     /*!< EFLASH Write Protection Area 12~13  */
#define HAL_EFLASH_WRITE_PROT_AREA_14_15        LL_EFLASH_WRITE_PROT_AREA_14_15     /*!< EFLASH Write Protection Area 14~15  */
#define HAL_EFLASH_WRITE_PROT_AREA_16_17        LL_EFLASH_WRITE_PROT_AREA_16_17     /*!< EFLASH Write Protection Area 16~17  */
#define HAL_EFLASH_WRITE_PROT_AREA_18_19        LL_EFLASH_WRITE_PROT_AREA_18_19     /*!< EFLASH Write Protection Area 18~19  */
#define HAL_EFLASH_WRITE_PROT_AREA_20_21        LL_EFLASH_WRITE_PROT_AREA_20_21     /*!< EFLASH Write Protection Area 20~21  */
#define HAL_EFLASH_WRITE_PROT_AREA_22_23        LL_EFLASH_WRITE_PROT_AREA_22_23     /*!< EFLASH Write Protection Area 22~23  */
#define HAL_EFLASH_WRITE_PROT_AREA_24_25        LL_EFLASH_WRITE_PROT_AREA_24_25     /*!< EFLASH Write Protection Area 24~25  */
#define HAL_EFLASH_WRITE_PROT_AREA_26_27        LL_EFLASH_WRITE_PROT_AREA_26_27     /*!< EFLASH Write Protection Area 26~27  */
#define HAL_EFLASH_WRITE_PROT_AREA_28_29        LL_EFLASH_WRITE_PROT_AREA_28_29     /*!< EFLASH Write Protection Area 28~29  */
#define HAL_EFLASH_WRITE_PROT_AREA_30_31        LL_EFLASH_WRITE_PROT_AREA_30_31     /*!< EFLASH Write Protection Area 30~31  */
#define HAL_EFLASH_WRITE_PROT_AREA_32_33        LL_EFLASH_WRITE_PROT_AREA_32_33     /*!< EFLASH Write Protection Area 32~33  */
#define HAL_EFLASH_WRITE_PROT_AREA_34_35        LL_EFLASH_WRITE_PROT_AREA_34_35     /*!< EFLASH Write Protection Area 34~35  */
#define HAL_EFLASH_WRITE_PROT_AREA_36_37        LL_EFLASH_WRITE_PROT_AREA_36_37     /*!< EFLASH Write Protection Area 36~37  */
#define HAL_EFLASH_WRITE_PROT_AREA_38_39        LL_EFLASH_WRITE_PROT_AREA_38_39     /*!< EFLASH Write Protection Area 38~39  */
#define HAL_EFLASH_WRITE_PROT_AREA_40_41        LL_EFLASH_WRITE_PROT_AREA_40_41     /*!< EFLASH Write Protection Area 40~41  */
#define HAL_EFLASH_WRITE_PROT_AREA_42_43        LL_EFLASH_WRITE_PROT_AREA_42_43     /*!< EFLASH Write Protection Area 42~43  */
#define HAL_EFLASH_WRITE_PROT_AREA_44_45        LL_EFLASH_WRITE_PROT_AREA_44_45     /*!< EFLASH Write Protection Area 44~45  */
#define HAL_EFLASH_WRITE_PROT_AREA_46_47        LL_EFLASH_WRITE_PROT_AREA_46_47     /*!< EFLASH Write Protection Area 46~47  */
#define HAL_EFLASH_WRITE_PROT_AREA_48_49        LL_EFLASH_WRITE_PROT_AREA_48_49     /*!< EFLASH Write Protection Area 48~49  */
#define HAL_EFLASH_WRITE_PROT_AREA_50_51        LL_EFLASH_WRITE_PROT_AREA_50_51     /*!< EFLASH Write Protection Area 50~51  */
#define HAL_EFLASH_WRITE_PROT_AREA_52_53        LL_EFLASH_WRITE_PROT_AREA_52_53     /*!< EFLASH Write Protection Area 52~53  */
#define HAL_EFLASH_WRITE_PROT_AREA_54_55        LL_EFLASH_WRITE_PROT_AREA_54_55     /*!< EFLASH Write Protection Area 54~55  */
#define HAL_EFLASH_WRITE_PROT_AREA_56_57        LL_EFLASH_WRITE_PROT_AREA_56_57     /*!< EFLASH Write Protection Area 56~57  */
#define HAL_EFLASH_WRITE_PROT_AREA_58_59        LL_EFLASH_WRITE_PROT_AREA_58_59     /*!< EFLASH Write Protection Area 58~59  */
#define HAL_EFLASH_WRITE_PROT_AREA_60_61        LL_EFLASH_WRITE_PROT_AREA_60_61     /*!< EFLASH Write Protection Area 60~61  */
#define HAL_EFLASH_WRITE_PROT_AREA_62_63        LL_EFLASH_WRITE_PROT_AREA_62_63     /*!< EFLASH Write Protection Area 62~63  */
#define HAL_EFLASH_WRITE_PROT_AREA_ALL          LL_EFLASH_WRITE_PROT_AREA_ALL       /*!< EFLASH Write Protection Area ALL    */
#define HAL_EFLASH_WRITE_PROT_AREA_MSK          LL_EFLASH_WRITE_PROT_AREA_MSK       /*!< EFLASH Write Protection Area Mask   */
/** @} */

/**
  * @}
  */ /* EFLASH_HAL_Exported_Constants */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup EFLASH_HAL_Exported_Macros EFLASH HAL Exported Macros
  * @brief    EFLASH HAL Exported Macros
  * @{
  */

/** @defgroup EFLASH_HAL_EM_Assert EFLASH HAL Assert 
  * @brief    EFLASH HAL Assert
  * @{
  */

/**
  * @brief  The HAL_EFLASH_PARAM_CHECK function is off by default
  */
#ifndef TAE32_USE_HAL_EFLASH_CHECK_PARAM
#define TAE32_USE_HAL_EFLASH_CHECK_PARAM  HAL_PERI_PARAM_CHECK_DEFAULT
#elif (TAE32_USE_HAL_EFLASH_CHECK_PARAM != 1) && (TAE32_USE_HAL_EFLASH_CHECK_PARAM != 0)
#undef TAE32_USE_HAL_EFLASH_CHECK_PARAM
#define TAE32_USE_HAL_EFLASH_CHECK_PARAM  HAL_PERI_PARAM_CHECK_DEFAULT
#endif /* TAE32_USE_HAL_EFLASH_CHECK_PARAM */

/**
  * @brief  The HAL_EFLASH_PARAM_CHECK macro is used for function's parameters check but do not abort CPU.
  * @param  expression Input Expression
  * @return The return value of the function is determined by the input expression.
  */
#define HAL_EFLASH_PARAM_CHECK(expression)      \
        if (TAE32_USE_HAL_EFLASH_CHECK_PARAM) { \
            expression;                         \
        }
/**
  * @}
  */ /* EFLASH_HAL_EM_Assert */

/** @defgroup EFLASH_HAL_EM_Mask EFLASH HAL Mask 
  * @brief    EFLASH HAL Mask
  * @{
  */

/** @name HAL_EFLASH_SR_ErrorStatusMskTypeDef
  * @brief HAL EFLASH SR Error Status Mask Definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_EFLASH_SR_ErrorStatusMskTypeDef                 LL_EFLASH_SR_ErrStaMskTypeDef
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef LL_EFLASH_SR_ErrStaMskTypeDef HAL_EFLASH_SR_ErrorStatusMskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_EFLASH_SR_OPDR_OPERATION_ERROR                  LL_EFLASH_SR_OPE          /*!< EFLASH OPDR Operation Error                      */
#define HAL_EFLASH_SR_PROGRAM_ERASE_OPERATION_ERROR         LL_EFLASH_SR_PES          /*!< EFLASH Program/Erase Operation Error             */
#define HAL_EFLASH_SR_PROGRAM_ERROR                         LL_EFLASH_SR_PGE          /*!< EFLASH Program Error                             */
#define HAL_EFLASH_SR_DOUBLE_BIT_ERROR                      LL_EFLASH_SR_DBC          /*!< EFLASH Double Bit Error Pending                  */
#define HAL_EFLASH_SR_SINGLE_BIT_ERROR                      LL_EFLASH_SR_SBC          /*!< EFLASH Single Bit Error Pending                  */
#define HAL_EFLASH_SR_ILLEGAL_OPERATION_ERROR               LL_EFLASH_SR_IOS          /*!< EFLASH Illegal Operation Error                   */
#define HAL_EFLASH_SR_WRITE_PROTECT_ERROR                   LL_EFLASH_SR_WPS          /*!< EFLASH Write Protect Error                       */
#define HAL_EFLASH_SR_OPERATION_ERROR                       LL_EFLASH_SR_OES          /*!< EFLASH Operation Error                           */
/** @} */


/** @name HAL_EFLASH_OpMaskTypeDef
  * @brief EFLASH Operation Mask definition
  * @{
  */
#ifndef TAE32_GLOBAL_TYPEDEF_SWITCH
#define HAL_EFLASH_OpMaskTypeDef                            uint32_t
#else  /* TAE32_GLOBAL_TYPEDEF_SWITCH */
typedef uint32_t HAL_EFLASH_OpMaskTypeDef;
#endif /* TAE32_GLOBAL_TYPEDEF_SWITCH */

#define HAL_EFLASH_OP_MASK_PROG                             (1UL << 0U)   /*!< EFLASH Operation Program       */
#define HAL_EFLASH_OP_MASK_ERASE                            (1UL << 1U)   /*!< EFLASH Operation Erase         */
#define HAL_EFLASH_OP_MASK_STDBY                            (1UL << 2U)   /*!< EFLASH Operation Standby       */
#define HAL_EFLASH_OP_MASK_WAKEUP                           (1UL << 3U)   /*!< EFLASH Operation Wakeup        */
#define HAL_EFLASH_OP_MASK_RW_PROT                          (1UL << 4U)   /*!< EFLASH Operation RW Protect    */
#define HAL_EFLASH_OP_MASK_OPT_DAT                          (1UL << 5U)   /*!< EFLASH Operation Option Data   */
/** @} */

/**
  * @}
  */ /* EFLASH_HAL_EM_Mask */

/**
  * @}
  */ /* EFLASH_HAL_Exported_Macros */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup EFLASH_HAL_Exported_Types EFLASH HAL Exported Types
  * @brief    EFLASH HAL Exported Types
  * @{
  */

/**
  * @brief EFLASH Read Protection Level Definition
  * @note When set read protection to level 2, it's no more possible to go back to level 1 or 0
  */
typedef enum
{
    HAL_EFLASH_READ_PROT_LVL_0  = LL_EFLASH_READ_PROT_LVL_0,  /*!< EFLASH Read Protection Level 0                   */
    HAL_EFLASH_READ_PROT_LVL_1  = LL_EFLASH_READ_PROT_LVL_1,  /*!< EFLASH Read Protection Level 1                   */
    HAL_EFLASH_READ_PROT_LVL_2  = LL_EFLASH_READ_PROT_LVL_2   /*!< EFLASH Read Protection Level 2                    \
                                                                  Warning: when set read protection to level 2,      \
                                                                  it's no more possible to go back to level 1 or 0  */
} HAL_EFLASH_ReadProtLvlTypeDef;

/**
  * @brief EFLASH Write Protect Enable Definition
  */
typedef enum
{
    HAL_EFLASH_WRITE_PROT_DISABLE  = 0UL,  /*!< Write Protect Disable   */
    HAL_EFLASH_WRITE_PROT_ENABLE   = 1UL   /*!< Write Protect Enable    */
} HAL_EFLASH_WriteProtEnTypeDef;

/**
  * @brief EFLASH Erase Mode Definition
  */
typedef enum
{
    HAL_EFLASH_ERASE_MODE_SECTOR  = LL_EFLASH_ERASE_MODE_SECTOR,   /*!< Erase Mode Sector   */
    HAL_EFLASH_ERASE_MODE_BANK0   = LL_EFLASH_ERASE_MODE_BANK0,    /*!< Erase Mode Bank0    */
    HAL_EFLASH_ERASE_MODE_BANK1   = LL_EFLASH_ERASE_MODE_BANK1,    /*!< Erase Mode Bank1    */
    HAL_EFLASH_ERASE_MODE_CHIP    = LL_EFLASH_ERASE_MODE_CHIP      /*!< Erase Mode Chip     */
} HAL_EFLASH_EraseModeTypeDef;

/**
  * @brief EFLASH Bank Address Mapping Definition
  */
typedef enum
{
    HAL_EFLASH_BANK_ADDR_MAP_BANK0  = LL_EFLASH_BANK_ADDR_MAP_BANK0,   /*!< Bank Address Mapping Bank 0   */
    HAL_EFLASH_BANK_ADDR_MAP_BANK1  = LL_EFLASH_BANK_ADDR_MAP_BANK1    /*!< Bank Address Mapping Bank 1   */
} HAL_EFLASH_BankAddrMapTypeDef;

/**
  * @brief EFLASH Bank Mode Definition
  * @note  Only Valid in 256K Mode
  */
typedef enum
{
    HAL_EFLASH_BANK_MODE_SINGLE  = LL_EFLASH_BANK_MODE_SINGLE,   /*!< Bank Mode Single   */
    HAL_EFLASH_BANK_MODE_DOUBLE  = LL_EFLASH_BANK_MODE_DOUBLE    /*!< Bank Mode Double   */
} HAL_EFLASH_BankModeTypeDef;

/**
  * @brief EFLASH BOR Voltage Limit Definition
  */
typedef enum
{
    HAL_EFLASH_BOR_VOL_LIMIT_2V4   = LL_EFLASH_BOR_VOL_LIMIT_2V4,    /*!< BOR Voltage Limit 2.4V    */
    HAL_EFLASH_BOR_VOL_LIMIT_2V55  = LL_EFLASH_BOR_VOL_LIMIT_2V55,   /*!< BOR Voltage Limit 2.55V   */
    HAL_EFLASH_BOR_VOL_LIMIT_2V7   = LL_EFLASH_BOR_VOL_LIMIT_2V7,    /*!< BOR Voltage Limit 2.7V    */
    HAL_EFLASH_BOR_VOL_LIMIT_2V85  = LL_EFLASH_BOR_VOL_LIMIT_2V85    /*!< BOR Voltage Limit 2.85V   */
} HAL_EFLASH_BORVolLimitTypeDef;

/**
  * @brief EFLASH Boot Selection Definition
  */
typedef enum
{
    HAL_EFLASH_BOOT_SEL_0  = LL_EFLASH_BOOT_SEL_0,   /*!< Boot Selection 0   */
    HAL_EFLASH_BOOT_SEL_1  = LL_EFLASH_BOOT_SEL_1,   /*!< Boot Selection 1   */
    HAL_EFLASH_BOOT_SEL_2  = LL_EFLASH_BOOT_SEL_2,   /*!< Boot Selection 2   */
    HAL_EFLASH_BOOT_SEL_3  = LL_EFLASH_BOOT_SEL_3,   /*!< Boot Selection 3   */
    HAL_EFLASH_BOOT_SEL_4  = LL_EFLASH_BOOT_SEL_4,   /*!< Boot Selection 4   */
    HAL_EFLASH_BOOT_SEL_5  = LL_EFLASH_BOOT_SEL_5,   /*!< Boot Selection 5   */
    HAL_EFLASH_BOOT_SEL_6  = LL_EFLASH_BOOT_SEL_6,   /*!< Boot Selection 6   */
    HAL_EFLASH_BOOT_SEL_7  = LL_EFLASH_BOOT_SEL_7    /*!< Boot Selection 7   */
} HAL_EFLASH_BootSelTypeDef;

/**
  * @brief EFLASH WWDG Default Enable Definition
  */
typedef enum
{
    HAL_EFLASH_WWDG_DEFAULT_DISABLE  = LL_EFLASH_WWDG_DEFAULT_DISABLE,   /*!< WWDG Default Disable   */
    HAL_EFLASH_WWDG_DEFAULT_ENABLE   = LL_EFLASH_WWDG_DEFAULT_ENABLE     /*!< WWDG Default Enable    */
} HAL_EFLASH_WWDGDefEnTypeDef;

/**
  * @brief EFLASH IWDG Default Enable Definition
  */
typedef enum
{
    HAL_EFLASH_IWDG_DEFAULT_DISABLE  = LL_EFLASH_IWDG_DEFAULT_DISABLE,   /*!< IWDG Default Disable   */
    HAL_EFLASH_IWDG_DEFAULT_ENABLE   = LL_EFLASH_IWDG_DEFAULT_ENABLE     /*!< IWDG Default Enable    */
} HAL_EFLASH_IWDGDefEnTypeDef;

/**
  * @brief EFLASH FLASH Power-On ECC Bypass Enable Definition
  */
typedef enum
{
    HAL_EFLASH_PWRON_ECC_BYPASS_DISABLE  = LL_EFLASH_PWRON_ECC_BYPASS_DISABLE,   /*!< FLASH Power-On ECC Bypass Disable   */
    HAL_EFLASH_PWRON_ECC_BYPASS_ENABLE   = LL_EFLASH_PWRON_ECC_BYPASS_ENABLE     /*!< FLASH Power-On ECC Bypass Enable    */
} HAL_EFLASH_PwrOnEccBypassTypeDef;

/**
  * @brief EFLASH Boot Lock Config Definition
  */
typedef enum
{
    HAL_EFLASH_BOOT_LOCK_CFG_UNLOCK  = LL_EFLASH_BOOT_LOCK_CFG_UNLOCK,   /*!< Boot Lock Config Unlock   */
    HAL_EFLASH_BOOT_LOCK_CFG_LOCK    = LL_EFLASH_BOOT_LOCK_CFG_LOCK      /*!< Boot Lock Config Lock     */
} HAL_EFLASH_BootLockCfgTypeDef;


/**
  * @brief EFLASH User Option Byte Operation Definition
  */
typedef enum
{
    HAL_EFLASH_OB_OP_BOOT_LOCK_CFG      = HAL_EFLASH_OPT_DAT_BOOT_LOCK_CFG,     /*!< Boot Lock Config       */
    HAL_EFLASH_OB_OP_BOOT_SEL           = HAL_EFLASH_OPT_DAT_BOOT_SEL,          /*!< Boot Selection         */
    HAL_EFLASH_OB_OP_BOR_VOL_LMT_CFG    = HAL_EFLASH_OPT_DAT_BOR_VOL_LMT_CFG,   /*!< BOR Vol Limit Config   */
    HAL_EFLASH_OB_OP_PWRON_ECC_BYPASS   = HAL_EFLASH_OPT_DAT_PWRON_ECC_BYPASS,  /*!< Power On ECC Bypass    */
    HAL_EFLASH_OB_OP_IWDG_DEFAULT_EN    = HAL_EFLASH_OPT_DAT_IWDG_DEFAULT_EN,   /*!< IWDG Default Enable    */
    HAL_EFLASH_OB_OP_WWDG_DEFAULT_EN    = HAL_EFLASH_OPT_DAT_WWDG_DEFAULT_EN,   /*!< WWDG Default Enable    */
    HAL_EFLASH_OB_OP_BANK_MODE_CFG      = HAL_EFLASH_OPT_DAT_BANK_MODE_CFG,     /*!< Bank Mode Config       */
    HAL_EFLASH_OB_OP_BANK_MAP_CFG       = HAL_EFLASH_OPT_DAT_BANK_MAP_CFG       /*!< Bank Mapping Config    */
} HAL_EFLASH_OptByteOpTypeDef;


#if ((LL_EFLASH_BOOT_LOCK_CFG_UNLOCK     >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_LOCK_CFG_LOCK       >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_0               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_1               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_2               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_3               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_4               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_5               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_6               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOOT_SEL_7               >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOR_VOL_LIMIT_2V4        >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOR_VOL_LIMIT_2V55       >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOR_VOL_LIMIT_2V7        >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BOR_VOL_LIMIT_2V85       >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_PWRON_ECC_BYPASS_DISABLE >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_PWRON_ECC_BYPASS_ENABLE  >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_IWDG_DEFAULT_DISABLE     >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_IWDG_DEFAULT_ENABLE      >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_WWDG_DEFAULT_DISABLE     >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_WWDG_DEFAULT_ENABLE      >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BANK_MODE_SINGLE         >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BANK_MODE_DOUBLE         >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BANK_ADDR_MAP_BANK0      >= HAL_EFLASH_OPT_DAT_VAL_RANGE) || \
     (LL_EFLASH_BANK_ADDR_MAP_BANK1      >= HAL_EFLASH_OPT_DAT_VAL_RANGE))
#error "EFLASH LL Option Byte Value Over Limit"
#endif

/**
  * @brief EFLASH Option Bytes Config Definition
  */
typedef enum
{
    HAL_EFLASH_OB_CFG_BOOT_LOCK_CFG_UNLOCK      = HAL_EFLASH_OPT_DAT_BOOT_LOCK_CFG + LL_EFLASH_BOOT_LOCK_CFG_UNLOCK,        /*!< Boot Lock Config Unlock            */
    HAL_EFLASH_OB_CFG_BOOT_LOCK_CFG_LOCK        = HAL_EFLASH_OPT_DAT_BOOT_LOCK_CFG + LL_EFLASH_BOOT_LOCK_CFG_LOCK,          /*!< Boot Lock Config Lock              */

    HAL_EFLASH_OB_CFG_BOOT_SEL_0                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_0,                       /*!< Boot Selection 0                   */
    HAL_EFLASH_OB_CFG_BOOT_SEL_1                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_1,                       /*!< Boot Selection 1                   */
    HAL_EFLASH_OB_CFG_BOOT_SEL_2                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_2,                       /*!< Boot Selection 2                   */
    HAL_EFLASH_OB_CFG_BOOT_SEL_3                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_3,                       /*!< Boot Selection 3                   */
    HAL_EFLASH_OB_CFG_BOOT_SEL_4                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_4,                       /*!< Boot Selection 4                   */
    HAL_EFLASH_OB_CFG_BOOT_SEL_5                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_5,                       /*!< Boot Selection 5                   */
    HAL_EFLASH_OB_CFG_BOOT_SEL_6                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_6,                       /*!< Boot Selection 6                   */
    HAL_EFLASH_OB_CFG_BOOT_SEL_7                = HAL_EFLASH_OPT_DAT_BOOT_SEL + LL_EFLASH_BOOT_SEL_7,                       /*!< Boot Selection 7                   */

    HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V4         = HAL_EFLASH_OPT_DAT_BOR_VOL_LMT_CFG + LL_EFLASH_BOR_VOL_LIMIT_2V4,         /*!< BOR Voltage Limit 2.4V             */
    HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V55        = HAL_EFLASH_OPT_DAT_BOR_VOL_LMT_CFG + LL_EFLASH_BOR_VOL_LIMIT_2V55,        /*!< BOR Voltage Limit 2.55V            */
    HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V7         = HAL_EFLASH_OPT_DAT_BOR_VOL_LMT_CFG + LL_EFLASH_BOR_VOL_LIMIT_2V7,         /*!< BOR Voltage Limit 2.7V             */
    HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V85        = HAL_EFLASH_OPT_DAT_BOR_VOL_LMT_CFG + LL_EFLASH_BOR_VOL_LIMIT_2V85,        /*!< BOR Voltage Limit 2.85V            */

    HAL_EFLASH_OB_CFG_PWRON_ECC_BYPASS_DISABLE  = HAL_EFLASH_OPT_DAT_PWRON_ECC_BYPASS + LL_EFLASH_PWRON_ECC_BYPASS_DISABLE, /*!< FLASH Power-On ECC Bypass Disable  */
    HAL_EFLASH_OB_CFG_PWRON_ECC_BYPASS_ENABLE   = HAL_EFLASH_OPT_DAT_PWRON_ECC_BYPASS + LL_EFLASH_PWRON_ECC_BYPASS_ENABLE,  /*!< FLASH Power-On ECC Bypass Enable   */

    HAL_EFLASH_OB_CFG_IWDG_DEFAULT_DISABLE      = HAL_EFLASH_OPT_DAT_IWDG_DEFAULT_EN + LL_EFLASH_IWDG_DEFAULT_DISABLE,      /*!< IWDG Default Disable               */
    HAL_EFLASH_OB_CFG_IWDG_DEFAULT_ENABLE       = HAL_EFLASH_OPT_DAT_IWDG_DEFAULT_EN + LL_EFLASH_IWDG_DEFAULT_ENABLE,       /*!< IWDG Default Enable                */

    HAL_EFLASH_OB_CFG_WWDG_DEFAULT_DISABLE      = HAL_EFLASH_OPT_DAT_WWDG_DEFAULT_EN + LL_EFLASH_WWDG_DEFAULT_DISABLE,      /*!< WWDG Default Disable               */
    HAL_EFLASH_OB_CFG_WWDG_DEFAULT_ENABLE       = HAL_EFLASH_OPT_DAT_WWDG_DEFAULT_EN + LL_EFLASH_WWDG_DEFAULT_ENABLE,       /*!< WWDG Default Enable                */

    HAL_EFLASH_OB_CFG_BANK_MODE_SINGLE          = HAL_EFLASH_OPT_DAT_BANK_MODE_CFG + LL_EFLASH_BANK_MODE_SINGLE,            /*!< Bank Mode Single                   */
    HAL_EFLASH_OB_CFG_BANK_MODE_DOUBLE          = HAL_EFLASH_OPT_DAT_BANK_MODE_CFG + LL_EFLASH_BANK_MODE_DOUBLE,            /*!< Bank Mode Double                   */

    HAL_EFLASH_OB_CFG_BANK_ADDR_MAP_BANK0       = HAL_EFLASH_OPT_DAT_BANK_MAP_CFG + LL_EFLASH_BANK_ADDR_MAP_BANK0,          /*!< Bank Address Mapping Bank 0        */
    HAL_EFLASH_OB_CFG_BANK_ADDR_MAP_BANK1       = HAL_EFLASH_OPT_DAT_BANK_MAP_CFG + LL_EFLASH_BANK_ADDR_MAP_BANK1           /*!< Bank Address Mapping Bank 1        */
} HAL_EFLASH_OptByteCfgTypeDef;

/**
  * @brief EFLASH Operation definition
  */
typedef enum
{
    HAL_EFLASH_OP_PROG      = 0U,   /*!< EFLASH Operation Program       */
    HAL_EFLASH_OP_ERASE     = 1U,   /*!< EFLASH Operation Erase         */
    HAL_EFLASH_OP_STDBY     = 2U,   /*!< EFLASH Operation Standby       */
    HAL_EFLASH_OP_WAKEUP    = 3U,   /*!< EFLASH Operation Wakeup        */
    HAL_EFLASH_OP_RW_PROT   = 4U,   /*!< EFLASH Operation RW Protect    */
    HAL_EFLASH_OP_OPT_DAT   = 5U    /*!< EFLASH Operation Option Data   */
} HAL_EFLASH_OpTypeDef;


/**
  * @}
  */ /* EFLASH_HAL_Exported_Types */

/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup EFLASH_HAL_Exported_Functions
  * @{
  */

/** @addtogroup EFLASH_HAL_EF_Configuration
  * @{
  */
HAL_StatusTypeDef HAL_EFLASH_ReadProtectLevelConfig(HAL_EFLASH_ReadProtLvlTypeDef Level);
HAL_StatusTypeDef HAL_EFLASH_WriteProtectAreaConfig(HAL_EFLASH_WriteProtAreaTypeDef Area, 
                                                    HAL_EFLASH_WriteProtEnTypeDef IsProt);

HAL_StatusTypeDef HAL_EFLASH_OB_BankMapConfig(HAL_EFLASH_BankAddrMapTypeDef BankMap);
HAL_StatusTypeDef HAL_EFLASH_OB_BankModeConfig(HAL_EFLASH_BankModeTypeDef BankMode);
HAL_StatusTypeDef HAL_EFLASH_OB_BootSelectConfig(HAL_EFLASH_BootSelTypeDef BootSel);
HAL_StatusTypeDef HAL_EFLASH_OB_BORVoltageLimitConfig(HAL_EFLASH_BORVolLimitTypeDef VolLimit);
HAL_StatusTypeDef HAL_EFLASH_OB_WWDGDefaultEnableConfig(HAL_EFLASH_WWDGDefEnTypeDef IsEnable);
HAL_StatusTypeDef HAL_EFLASH_OB_IWDGDefaultEnableConfig(HAL_EFLASH_IWDGDefEnTypeDef IsEnable);
HAL_StatusTypeDef HAL_EFLASH_OB_BootLockEnableConfig(HAL_EFLASH_BootLockCfgTypeDef IsEnable);
HAL_StatusTypeDef HAL_EFLASH_OB_PowerOnECCBypassEnableConfig(HAL_EFLASH_PwrOnEccBypassTypeDef IsEnable);
HAL_StatusTypeDef HAL_EFLASH_OB_UserOptionByteConfig(HAL_EFLASH_OptByteOpTypeDef UsrOpt, 
                                                     HAL_EFLASH_OptByteCfgTypeDef CfgVal);
/**
  * @}
  */ /* EFLASH_HAL_EF_Configuration */

/** @addtogroup EFLASH_HAL_EF_State
  * @{
  */
HAL_StatusTypeDef HAL_EFLASH_WaitForLastOperation(uint32_t Timeout);
uint32_t HAL_EFLASH_GetError(void);
/**
  * @}
  */ /* EFLASH_HAL_EF_State */


/** @addtogroup EFLASH_HAL_EF_Information
  * @{
  */
uint32_t HAL_EFLASH_GetChipSize(void);
uint32_t HAL_EFLASH_GetSectorSize(void);
uint32_t HAL_EFLASH_GetSectorNums(void);

HAL_EFLASH_BankAddrMapTypeDef   HAL_EFLASH_OB_GetBankMap(void);
HAL_EFLASH_BankModeTypeDef      HAL_EFLASH_OB_GetBankMode(void);
HAL_EFLASH_BootSelTypeDef       HAL_EFLASH_OB_GetBootSelect(void);
HAL_EFLASH_BORVolLimitTypeDef   HAL_EFLASH_OB_GetBORVoltageLimit(void);
HAL_EFLASH_WWDGDefEnTypeDef     HAL_EFLASH_OB_GetWWDGDefaultEnableStatus(void);
HAL_EFLASH_IWDGDefEnTypeDef     HAL_EFLASH_OB_GetIWDGDefaultEnableStatus(void);
HAL_EFLASH_BootLockCfgTypeDef     HAL_EFLASH_OB_GetBootLockStatus(void);
HAL_EFLASH_PwrOnEccBypassTypeDef  HAL_EFLASH_OB_GetPowerOnECCBypassStatus(void);
/**
  * @}
  */ /* EFLASH_HAL_EF_Information */


/** @addtogroup EFLASH_HAL_EF_Operation
  * @{
  */
uint32_t HAL_EFLASH_Program(uint32_t Address, 
                            uint8_t *Buff, 
                            uint32_t Size);

uint32_t HAL_EFLASH_EraseMultiSector(uint32_t SectorStart, 
                                     uint32_t Number);

HAL_StatusTypeDef HAL_EFLASH_EraseSector(uint32_t SectorNumber);
HAL_StatusTypeDef HAL_EFLASH_EraseChip(void);
HAL_StatusTypeDef HAL_EFLASH_EraseBank0(void);
HAL_StatusTypeDef HAL_EFLASH_EraseBank1(void);

uint32_t HAL_EFLASH_Verify(uint32_t Address, 
                           uint8_t *Buff, 
                           uint32_t Size);

HAL_StatusTypeDef HAL_EFLASH_ReadWriteProtect_Launch(void);
/**
  * @}
  */ /* EFLASH_HAL_EF_Operation */


/**
  * @}
  */ /* EFLASH_HAL_Exported_Functions */


/** @addtogroup EFLASH_HAL_EF_Interrupt
  * @{
  */

void HAL_EFLASH_ErrorInterruptEnable(void);
void HAL_EFLASH_ErrorInterruptDisable(void);

void HAL_EFLASH_IRQHandler(void);

void HAL_EFLASH_OperationErrorCallback(EFLASH_TypeDef *Instance);
void HAL_EFLASH_WriteProtectErrorCallback(EFLASH_TypeDef *Instance);
void HAL_EFLASH_IllegalOperationErrorCallback(EFLASH_TypeDef *Instance);
void HAL_EFLASH_SingleBitErrorCallback(EFLASH_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */ /* EFLASH_HAL */

#endif /* EFLASH */

/**
  * @}
  */ /* TAE32F561x_HAL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32F561X_HAL_EFLASH_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

