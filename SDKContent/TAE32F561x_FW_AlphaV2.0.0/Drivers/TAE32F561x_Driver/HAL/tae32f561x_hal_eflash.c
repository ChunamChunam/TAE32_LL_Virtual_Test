/**
  ******************************************************************************
  * @file    tae32f561x_hal_eflash.c
  * @author  Tai-Action SD Team
  * @brief   EFLASH HAL module driver
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
#include "tae32f561x_hal.h"


/** @addtogroup TAE32F561x_HAL_Driver
  * @{
  */

#if defined(EFLASH) 
#if defined(HAL_MODULE_ENABLED) && (HAL_MODULE_ENABLED == 1)
#if defined(HAL_EFLASH_MODULE_ENABLED) && (HAL_EFLASH_MODULE_ENABLED == 1)

/** @defgroup EFLASH_HAL EFLASH HAL
  * @brief    EFLASH HAL Module Driver
  * @{
  */

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup EFLASH_HAL_Private_Macros EFLASH HAL Private Macros
  * @brief    EFLASH HAL Private Macros
  * @{
  */

#define EFLASH_GET_INSTANCE                           (EFLASH)


/** @defgroup EFLASH_HAL_PM_Discriminant EFLASH HAL Discriminant
  * @brief    EFLASH HAL Discriminant
  * @{
  */

#define IS_EFLASH_READ_PROT_LVL(__VAL__)                (((__VAL__) == HAL_EFLASH_READ_PROT_LVL_0)       || \
                                                         ((__VAL__) == HAL_EFLASH_READ_PROT_LVL_1)       || \
                                                         ((__VAL__) == HAL_EFLASH_READ_PROT_LVL_2))

#define IS_EFLASH_WRITE_PROT_AREA(__VAL__)              (((__VAL__) & HAL_EFLASH_WRITE_PROT_AREA_MSK) != 0UL)

#define IS_EFLASH_WRITE_PROT_EN(__VAL__)                (((__VAL__) == HAL_EFLASH_WRITE_PROT_DISABLE)    || \
                                                         ((__VAL__) == HAL_EFLASH_WRITE_PROT_ENABLE))

#define IS_EFLASH_ERASE_MODE(__VAL__)                   (((__VAL__) == HAL_EFLASH_ERASE_MODE_SECTOR)       || \
                                                         ((__VAL__) == HAL_EFLASH_ERASE_MODE_BANK0)        || \
                                                         ((__VAL__) == HAL_EFLASH_ERASE_MODE_BANK1)        || \
                                                         ((__VAL__) == HAL_EFLASH_ERASE_MODE_CHIP))

#define IS_EFLASH_BANK_ADDR_MAP(__VAL__)                (((__VAL__) == HAL_EFLASH_BANK_ADDR_MAP_BANK0)   || \
                                                         ((__VAL__) == HAL_EFLASH_BANK_ADDR_MAP_BANK1))  

#define IS_EFLASH_BANK_MODE(__VAL__)                    (((__VAL__) == HAL_EFLASH_BANK_MODE_SINGLE)         || \
                                                         ((__VAL__) == HAL_EFLASH_BANK_MODE_DOUBLE))   

#define IS_EFLASH_BOR_VOL_LIMIT(__VAL__)                (((__VAL__) == HAL_EFLASH_BOR_VOL_LIMIT_2V4)     || \
                                                         ((__VAL__) == HAL_EFLASH_BOR_VOL_LIMIT_2V55)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOR_VOL_LIMIT_2V7)     || \
                                                         ((__VAL__) == HAL_EFLASH_BOR_VOL_LIMIT_2V85))

#define IS_EFLASH_BOOT_SEL(__VAL__)                     (((__VAL__) == HAL_EFLASH_BOOT_SEL_0)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_SEL_1)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_SEL_2)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_SEL_3)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_SEL_4)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_SEL_5)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_SEL_6)    || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_SEL_7))

#define IS_EFLASH_WWDG_DEFAULT(__VAL__)                 (((__VAL__) == HAL_EFLASH_WWDG_DEFAULT_DISABLE)    || \
                                                         ((__VAL__) == HAL_EFLASH_WWDG_DEFAULT_ENABLE))

#define IS_EFLASH_IWDG_DEFAULT(__VAL__)                 (((__VAL__) == HAL_EFLASH_IWDG_DEFAULT_DISABLE)    || \
                                                         ((__VAL__) == HAL_EFLASH_IWDG_DEFAULT_ENABLE))

#define IS_EFLASH_PWRON_ECC_BYPASS(__VAL__)             (((__VAL__) == HAL_EFLASH_PWRON_ECC_BYPASS_DISABLE)   || \
                                                         ((__VAL__) == HAL_EFLASH_PWRON_ECC_BYPASS_ENABLE))

#define IS_EFLASH_BOOT_LOCK_CFG(__VAL__)                (((__VAL__) == HAL_EFLASH_BOOT_LOCK_CFG_UNLOCK)  || \
                                                         ((__VAL__) == HAL_EFLASH_BOOT_LOCK_CFG_LOCK))

#define IS_EFLASH_OPT_BYTE_OP(__VAL__)                  (((__VAL__) == HAL_EFLASH_OB_OP_BOOT_LOCK_CFG)     || \
                                                         ((__VAL__) == HAL_EFLASH_OB_OP_BOOT_SEL)          || \
                                                         ((__VAL__) == HAL_EFLASH_OB_OP_BOR_VOL_LMT_CFG)   || \
                                                         ((__VAL__) == HAL_EFLASH_OB_OP_PWRON_ECC_BYPASS)  || \
                                                         ((__VAL__) == HAL_EFLASH_OB_OP_IWDG_DEFAULT_EN)   || \
                                                         ((__VAL__) == HAL_EFLASH_OB_OP_WWDG_DEFAULT_EN)   || \
                                                         ((__VAL__) == HAL_EFLASH_OB_OP_BANK_MODE_CFG)     || \
                                                         ((__VAL__) == HAL_EFLASH_OB_OP_BANK_MAP_CFG))

#define IS_EFLASH_OPT_BYTE_CFG(__VAL__)                 (((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_LOCK_CFG_UNLOCK)       || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_LOCK_CFG_LOCK)         || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_0)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_1)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_2)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_3)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_4)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_5)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_6)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOOT_SEL_7)                 || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V4)          || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V55)         || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V7)          || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BOR_VOL_LIMIT_2V85)         || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_PWRON_ECC_BYPASS_DISABLE)   || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_PWRON_ECC_BYPASS_ENABLE)    || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_IWDG_DEFAULT_DISABLE)       || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_IWDG_DEFAULT_ENABLE)        || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_WWDG_DEFAULT_DISABLE)       || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_WWDG_DEFAULT_ENABLE)        || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BANK_MODE_SINGLE)           || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BANK_MODE_DOUBLE)           || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BANK_ADDR_MAP_BANK0)        || \
                                                         ((__VAL__) == HAL_EFLASH_OB_CFG_BANK_ADDR_MAP_BANK1))

/**
  * @}
  */ /* EFLASH_HAL_PM_Discriminant */

/**
  * @}
  */ /* EFLASH_HAL_Private_Macros */

/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup EFLASH_HAL_Private_Functions EFLASH HAL Private Functions
  * @brief    EFLASH HAL Private Functions
  * @{
  */
__STATIC_INLINE uint32_t EFLASH_GetChipSize(EFLASH_TypeDef *Instance);
__STATIC_INLINE uint32_t EFLASH_GetSectorSize(EFLASH_TypeDef *Instance);
__STATIC_INLINE uint32_t EFLASH_GetSectorNums(EFLASH_TypeDef *Instance);

__STATIC_INLINE uint32_t EFLASH_LastOptSta_Get(EFLASH_TypeDef *Instance, HAL_EFLASH_OpTypeDef LastOp);
__STATIC_INLINE HAL_StatusTypeDef EFLASH_EraseCommon(EFLASH_TypeDef *Instance, HAL_EFLASH_EraseModeTypeDef EraseMode);

static HAL_StatusTypeDef EFLASH_OB_CheckReadyAndUnlock(EFLASH_TypeDef *Instance, uint32_t Timeout);
static HAL_StatusTypeDef EFLASH_OB_CheckIdleAndLock(EFLASH_TypeDef *Instance, uint32_t Timeout);

__STATIC_INLINE HAL_StatusTypeDef EFLASH_ProgErase_Unlock(EFLASH_TypeDef *Instance);
__STATIC_INLINE HAL_StatusTypeDef EFLASH_ProgErase_Lock(EFLASH_TypeDef *Instance);
__STATIC_INLINE HAL_StatusTypeDef EFLASH_RWProtOptDat_Unlock(EFLASH_TypeDef *Instance);
__STATIC_INLINE HAL_StatusTypeDef EFLASH_RWProtOptDat_Lock(EFLASH_TypeDef *Instance);

__STATIC_INLINE HAL_StatusTypeDef EFLASH_WaitForBusyState(EFLASH_TypeDef *Instance, 
                                                          uint32_t Timeout);

__STATIC_INLINE HAL_StatusTypeDef EFLASH_WaitForLastOpCplt(EFLASH_TypeDef *Instance, 
                                                           HAL_EFLASH_OpTypeDef LastOp, 
                                                           uint32_t Timeout);

__STATIC_INLINE uint32_t EFLASH_EraseMultiSector(EFLASH_TypeDef *Instance, 
                                                 uint32_t SectorStart, 
                                                 uint32_t Number);

/**
  * @}
  */ /* EFLASH_HAL_Private_Functions */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup EFLASH_HAL_Exported_Functions EFLASH HAL Exported Functions
  * @brief    EFLASH HAL Exported Functions
  * @{
  */

/** @defgroup EFLASH_HAL_EF_Configuration EFLASH Configuration Functions
  * @brief    EFLASH Configuration Functions
  * @{
  */

/**
  * @brief  Configure the read protection level of the EFLASH.
  * @note   This function waits for the flash to be idle, unlocks the read/write
  *         protection configuration, sets the protection level, waits for the
  *         operation to complete, launches the configuration to take effect,
  *         and then locks the protection again.
  * @param  Level Read protection level to be configured.
  *         This parameter can be a value of @ref HAL_EFLASH_ReadProtLvlTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_ReadProtectLevelConfig(HAL_EFLASH_ReadProtLvlTypeDef Level)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_READ_PROT_LVL(Level));

    HAL_StatusTypeDef ret;
    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;

    /* Wait for EFLASH Idle */
    ret = EFLASH_WaitForBusyState(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT);

    if (ret == HAL_OK) {
        /* Unlock Read/Write Protect Config */
        if (EFLASH_RWProtOptDat_Unlock(p_instance) != HAL_OK) {
            return HAL_FAILED;
        }

        /* Set Read Protect Level */
        LL_EFLASH_SetReadProt(p_instance, (uint32_t)Level);

        /* Wait for Operation Complete */
        ret = EFLASH_WaitForLastOpCplt(p_instance, HAL_EFLASH_OP_RW_PROT, HAL_EFLASH_DEFAULT_TIMEOUT);

        /* Error has been cleared. */
        if (ret != HAL_TIMEOUT) {
            ret = HAL_OK;
        }

        /* Lock Read/Write Protect Config */
        EFLASH_RWProtOptDat_Lock(p_instance);
    }

    return ret;
}

/**
  * @brief  Enable or disable write protection for specified sectors (areas).
  * @note   This function waits for the flash to be idle, unlocks the protection
  *         configuration, then enables or disables write protection for the
  *         given area(s). It also waits for the operation to complete and
  *         launches the configuration.
  * @param  Area Write protection area(s) to configure.
  *         This parameter can be a combination of @ref HAL_EFLASH_WRITE_PROT_AREA_MSK values.
  * @param  IsProt Enable or disable write protection.
  *         This parameter can be a value of @ref HAL_EFLASH_WriteProtEnTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_WriteProtectAreaConfig(HAL_EFLASH_WriteProtAreaTypeDef Area, 
                                                    HAL_EFLASH_WriteProtEnTypeDef IsProt)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_WRITE_PROT_AREA(Area));
    ASSERT_FUNC_PARAM(IS_EFLASH_WRITE_PROT_EN(IsProt));

    HAL_StatusTypeDef ret;
    uint32_t is_enable;
    uint32_t area_32 = (uint32_t)Area;
    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;

    /* Wait for EFLASH Idle */
    ret = EFLASH_WaitForBusyState(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT);

    if (ret == HAL_OK) {
        /* Unlock Read/Write Protect Config */
        if (EFLASH_RWProtOptDat_Unlock(p_instance) != HAL_OK) {
            return HAL_FAILED;
        }

        ret = EFLASH_WaitForLastOpCplt(p_instance, HAL_EFLASH_OP_RW_PROT, HAL_EFLASH_DEFAULT_TIMEOUT);
        if (ret != HAL_OK) {
            if (EFLASH_RWProtOptDat_Lock(p_instance) != HAL_OK) {
                return HAL_FAILED;
            } else {
                return ret;
            }
        }

        /* Write Protect Config */
        (void)LL_EFLASH_GetWriteProtArea(p_instance);
        is_enable = HAL_JUDGE_IS(IsProt, HAL_EFLASH_WRITE_PROT_ENABLE);
        HAL_FUNC_ALTER(is_enable, LL_EFLASH_EnableWriteProtArea(p_instance, area_32), LL_EFLASH_DisableWriteProtArea(p_instance, area_32));

        /* Wait for Operation Complete */
        ret = EFLASH_WaitForLastOpCplt(p_instance, HAL_EFLASH_OP_RW_PROT, HAL_EFLASH_WRITE_PROTECT_TIMEOUT);

        /* Error has been cleared. */
        if (ret != HAL_TIMEOUT) {
            ret = HAL_OK;
        }

        /* Lock Read/Write Protect Config */
        EFLASH_RWProtOptDat_Lock(p_instance);
    }

    return ret;
}

/**
  * @brief  Configure the EFLASH bank address mapping.
  * @note   This function waits for the flash to be ready and unlocked, then
  *         sets the bank mapping and polls until the change is effective.
  *         Finally, it waits for the flash to be idle again and locks the
  *         option data.
  * @param  BankMap Bank mapping to configure.
  *         This parameter can be a value of @ref HAL_EFLASH_BankAddrMapTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_BankMapConfig(HAL_EFLASH_BankAddrMapTypeDef BankMap)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_BANK_ADDR_MAP(BankMap));

    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();

    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH bank mapping config */
    (void)LL_EFLASH_OPDR_Read(p_instance);
    LL_EFLASH_OB_SetBankMap(p_instance, BankMap);
    while (LL_EFLASH_OB_GetBankMap(p_instance) != LL_EFLASH_BANK_MAP_VAL_MSK(BankMap)) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the EFLASH bank mode (single or double).
  * @note   Only valid when the flash size is 256KB. This function waits for
  *         the flash to be ready and unlocked, sets the bank mode, polls
  *         until effective, then waits for idle and locks.
  * @param  BankMode Bank mode to configure.
  *         This parameter can be a value of @ref HAL_EFLASH_BankModeTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_BankModeConfig(HAL_EFLASH_BankModeTypeDef BankMode)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_BANK_MODE(BankMode));
    
    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();

    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH bank mode config */
    (void)LL_EFLASH_OPDR_Read(p_instance);
    LL_EFLASH_OB_SetBankMode(p_instance, BankMode);
    while (LL_EFLASH_OB_GetBankMode(p_instance) != LL_EFLASH_BANK_MODE_VAL_MSK(BankMode)) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the EFLASH boot selection.
  * @note   Determines which memory is mapped at boot. This function waits for
  *         the flash to be ready and unlocked, sets the boot selection, polls
  *         until effective, then waits for idle and locks.
  * @param  BootSel Boot selection to configure.
  *         This parameter can be a value of @ref HAL_EFLASH_BootSelTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_BootSelectConfig(HAL_EFLASH_BootSelTypeDef BootSel)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_BOOT_SEL(BootSel));

    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();

    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH boot selection config */
    (void)LL_EFLASH_OPDR_Read(p_instance);
    LL_EFLASH_OB_SetBootSelect(p_instance, BootSel);
    while (LL_EFLASH_OB_GetBootSelect(p_instance) != LL_EFLASH_BOOT_SEL_VAL_MSK(BootSel)) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the BOR (Brown-Out Reset) voltage limit.
  * @note   This function waits for the flash to be ready and unlocked, sets
  *         the BOR voltage limit, polls until effective, then waits for idle
  *         and locks.
  * @param  VolLimit BOR voltage limit to configure.
  *         This parameter can be a value of @ref HAL_EFLASH_BORVolLimitTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_BORVoltageLimitConfig(HAL_EFLASH_BORVolLimitTypeDef VolLimit)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_BOR_VOL_LIMIT(VolLimit));

    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();
    
    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH BOR Voltage Limit Config */
    (void)LL_EFLASH_OPDR_Read(p_instance);
    LL_EFLASH_OB_SetBORVoltageLimit(p_instance, VolLimit);
    while (LL_EFLASH_OB_GetBORVoltageLimit(p_instance) != LL_EFLASH_BOR_VOL_LIMIT_VAL_MSK(VolLimit)) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the WWDG default enable state (set in option bytes).
  * @note   This function waits for the flash to be ready and unlocked, then
  *         enables or disables the WWDG default, polls until effective, then
  *         waits for idle and locks.
  * @param  IsEnable WWDG default enable or disable.
  *         This parameter can be a value of @ref HAL_EFLASH_WWDGDefEnTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_WWDGDefaultEnableConfig(HAL_EFLASH_WWDGDefEnTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_WWDG_DEFAULT(IsEnable));

    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();
    uint32_t is_enable;
    
    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH WWDG Default Enable Config */
    (void)LL_EFLASH_OPDR_Read(p_instance);

    is_enable = HAL_JUDGE_IS(IsEnable, HAL_EFLASH_WWDG_DEFAULT_ENABLE);
    HAL_FUNC_ALTER(is_enable, LL_EFLASH_OB_WWDGDefaultEnable(p_instance), LL_EFLASH_OB_WWDGDefaultDisable(p_instance));

    while (LL_EFLASH_OB_IsWWDGDefaultEnable(p_instance) != is_enable) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the IWDG default enable state (set in option bytes).
  * @note   This function waits for the flash to be ready and unlocked, then
  *         enables or disables the IWDG default, polls until effective, then
  *         waits for idle and locks.
  * @param  IsEnable IWDG default enable or disable.
  *         This parameter can be a value of @ref HAL_EFLASH_IWDGDefEnTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_IWDGDefaultEnableConfig(HAL_EFLASH_IWDGDefEnTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_IWDG_DEFAULT(IsEnable));

    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();
    uint32_t is_enable;
    
    ASSERT_FUNC_PARAM(IS_EFLASH_ALL_INSTANCE(p_instance));

    HAL_EFLASH_PARAM_CHECK({
        if (!IS_EFLASH_ALL_INSTANCE(p_instance)) {
            return HAL_INVALID;
        }
    })

    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH IWDG Default Enable Config */
    (void)LL_EFLASH_OPDR_Read(p_instance);

    is_enable = HAL_JUDGE_IS(IsEnable, HAL_EFLASH_IWDG_DEFAULT_ENABLE);
    HAL_FUNC_ALTER(is_enable, LL_EFLASH_OB_IWDGDefaultEnable(p_instance), LL_EFLASH_OB_IWDGDefaultDisable(p_instance));

    while (LL_EFLASH_OB_IsIWDGDefaultEnable(p_instance) != is_enable) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the boot lock enable state (set in option bytes).
  * @note   This function waits for the flash to be ready and unlocked, then
  *         locks or unlocks the boot, polls until effective, then waits for
  *         idle and locks.
  * @param  IsEnable Boot lock enable or disable.
  *         This parameter can be a value of @ref HAL_EFLASH_BootLockCfgTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_BootLockEnableConfig(HAL_EFLASH_BootLockCfgTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_BOOT_LOCK_CFG(IsEnable));

    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();
    uint32_t is_enable;
    
    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH Boot Lock Enable Config */
    (void)LL_EFLASH_OPDR_Read(p_instance);

    is_enable = HAL_JUDGE_IS(IsEnable, HAL_EFLASH_BOOT_LOCK_CFG_LOCK);
    HAL_FUNC_ALTER(is_enable, LL_EFLASH_OB_LockBoot(p_instance), LL_EFLASH_OB_UnlockBoot(p_instance));

    while (LL_EFLASH_OB_IsBootLock(p_instance) != is_enable) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure the power-on ECC bypass enable state (set in option bytes).
  * @note   This function waits for the flash to be ready and unlocked, then
  *         enables or disables the ECC bypass, polls until effective, then
  *         waits for idle and locks.
  * @param  IsEnable Power-on ECC bypass enable or disable.
  *         This parameter can be a value of @ref HAL_EFLASH_PwrOnEccBypassTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_PowerOnECCBypassEnableConfig(HAL_EFLASH_PwrOnEccBypassTypeDef IsEnable)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_PWRON_ECC_BYPASS(IsEnable));

    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t tickstart = HAL_GetTick();
    uint32_t is_enable;

    /* Wait for the flash to be idle and unlocked. */
    if (EFLASH_OB_CheckReadyAndUnlock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* EFLASH FLASH Power-On ECC Bypass Enable Config */
    (void)LL_EFLASH_OPDR_Read(p_instance);

    is_enable = HAL_JUDGE_IS(IsEnable, HAL_EFLASH_PWRON_ECC_BYPASS_ENABLE);
    HAL_FUNC_ALTER(is_enable, LL_EFLASH_OB_EnablePowerOnECCBypass(p_instance), LL_EFLASH_OB_DisablePowerOnECCBypass(p_instance));

    while (LL_EFLASH_OB_IsPowerOnECCBypassEnable(p_instance) != is_enable) {
        if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
            return HAL_TIMEOUT;
        }
    }

    /* Wait for the flash to be idle and locked. */
    if (EFLASH_OB_CheckIdleAndLock(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Configure a user option byte based on the operation type and value.
  * @note   This is a high-level wrapper that dispatches to the specific option
  *         configuration function based on the operation type. The parameter
  *         CfgVal must be a value from @ref HAL_EFLASH_OptByteCfgTypeDef
  *         that corresponds to the given operation.
  * @param  UsrOpt User option operation type.
  *         This parameter can be a value of @ref HAL_EFLASH_OptByteOpTypeDef
  * @param  CfgVal Option configuration value.
  *         This parameter can be a value of @ref HAL_EFLASH_OptByteCfgTypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_OB_UserOptionByteConfig(HAL_EFLASH_OptByteOpTypeDef UsrOpt, 
                                                     HAL_EFLASH_OptByteCfgTypeDef CfgVal)
{
    ASSERT_FUNC_PARAM(IS_EFLASH_OPT_BYTE_OP(UsrOpt));
    ASSERT_FUNC_PARAM(IS_EFLASH_OPT_BYTE_CFG(CfgVal));


    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t opt_param = (uint32_t)CfgVal - (uint32_t)UsrOpt;

    /* EFLASH Option Bytes Config */
    switch (UsrOpt) {
        case HAL_EFLASH_OB_OP_BOOT_LOCK_CFG:
            if (HAL_EFLASH_OB_BootLockEnableConfig((HAL_EFLASH_BootLockCfgTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        case HAL_EFLASH_OB_OP_BOOT_SEL:
            if (HAL_EFLASH_OB_BootSelectConfig((HAL_EFLASH_BootSelTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        case HAL_EFLASH_OB_OP_BOR_VOL_LMT_CFG:
            if (HAL_EFLASH_OB_BORVoltageLimitConfig((HAL_EFLASH_BORVolLimitTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        case HAL_EFLASH_OB_OP_PWRON_ECC_BYPASS:
            if (HAL_EFLASH_OB_PowerOnECCBypassEnableConfig((HAL_EFLASH_PwrOnEccBypassTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        case HAL_EFLASH_OB_OP_IWDG_DEFAULT_EN:
            if (HAL_EFLASH_OB_IWDGDefaultEnableConfig((HAL_EFLASH_IWDGDefEnTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        case HAL_EFLASH_OB_OP_WWDG_DEFAULT_EN:
            if (HAL_EFLASH_OB_WWDGDefaultEnableConfig((HAL_EFLASH_WWDGDefEnTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        case HAL_EFLASH_OB_OP_BANK_MODE_CFG:
            if (HAL_EFLASH_OB_BankModeConfig((HAL_EFLASH_BankModeTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        case HAL_EFLASH_OB_OP_BANK_MAP_CFG:
            if (HAL_EFLASH_OB_BankMapConfig((HAL_EFLASH_BankAddrMapTypeDef)opt_param) != HAL_OK) {
                goto invalid;
            }
            break;

        default:
            /* Invalid user option operation code */
            goto invalid;
    }

    return HAL_OK;

invalid:
    /* Wait for EFLASH Idle */
    if (EFLASH_WaitForBusyState(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_TIMEOUT;
    }

    /* Lock Option Data Config */
    EFLASH_RWProtOptDat_Lock(p_instance);

    return HAL_INVALID;
}

/**
  * @}
  */ /* EFLASH_HAL_EF_Configuration */


/** @defgroup EFLASH_HAL_EF_State EFLASH State Functions
  * @brief    EFLASH State Functions
  * @{
  */

/**
  * @brief  Wait until the EFLASH is idle (no ongoing operations) or timeout.
  * @note   This function checks all operation done flags (program, erase,
  *         standby, wakeup, read/write protection) and the idle flag.
  *         If any error flag is set, it clears them and returns HAL_ERROR.
  * @param  Timeout Maximum waiting time in ms. Use HAL_WAIT_FOREVER for infinite wait.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_WaitForLastOperation(uint32_t Timeout)
{
    return EFLASH_WaitForBusyState(EFLASH_GET_INSTANCE, Timeout);
}

/**
  * @brief  Get flash error status
  * @retval Flash Error Mask @ref HAL_EFLASH_SR_ErrorStatusMskTypeDef
  */
uint32_t HAL_EFLASH_GetError(void)
{
    return LL_EFLASH_GetErrorStatus(EFLASH_GET_INSTANCE);
}

/**
  * @}
  */ /* EFLASH_HAL_EF_State */


/** @defgroup EFLASH_HAL_EF_Information EFLASH Information Functions
  * @brief    EFLASH Information Functions
  * @{
  */

/**
  * @brief  Get the total EFLASH chip size in bytes.
  * @note   The size is determined by reading the hardware configuration.
  *         For this implementation: 128KB or 256KB.
  * @retval Chip size in bytes
  */
uint32_t HAL_EFLASH_GetChipSize(void)
{
    return EFLASH_GetChipSize(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Get the EFLASH sector size in bytes.
  * @note   Sector size depends on chip size and bank mode.
  * @retval Sector size in bytes
  */
uint32_t HAL_EFLASH_GetSectorSize(void)
{
    return EFLASH_GetSectorSize(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Get the number of sectors in the EFLASH.
  * @note   Sector count depends on chip size and bank mode.
  * @retval Number of sectors
  */
uint32_t HAL_EFLASH_GetSectorNums(void)
{
    return EFLASH_GetSectorNums(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Get the Bank address map from the EFLASH option bytes.
  * @return Bank address map type.
  */
HAL_EFLASH_BankAddrMapTypeDef HAL_EFLASH_OB_GetBankMap(void)
{
    return (HAL_EFLASH_BankAddrMapTypeDef)LL_EFLASH_OB_GetBankMap(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Get the Bank mode from the EFLASH option bytes.
  * @return Bank mode type.
  */
HAL_EFLASH_BankModeTypeDef HAL_EFLASH_OB_GetBankMode(void)
{
    return (HAL_EFLASH_BankModeTypeDef)LL_EFLASH_OB_GetBankMode(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Get the Boot selection from the EFLASH option bytes.
  * @return Boot selection type.
  */
HAL_EFLASH_BootSelTypeDef HAL_EFLASH_OB_GetBootSelect(void)
{
    return (HAL_EFLASH_BootSelTypeDef)LL_EFLASH_OB_GetBootSelect(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Get the BOR voltage limit from the EFLASH option bytes.
  * @return BOR voltage limit type.
  */
HAL_EFLASH_BORVolLimitTypeDef HAL_EFLASH_OB_GetBORVoltageLimit(void)
{
    return (HAL_EFLASH_BORVolLimitTypeDef)LL_EFLASH_OB_GetBORVoltageLimit(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Get the WWDG default enable status from the EFLASH option bytes.
  * @return WWDG default enable status.
  */
HAL_EFLASH_WWDGDefEnTypeDef HAL_EFLASH_OB_GetWWDGDefaultEnableStatus(void)
{
    return ((LL_EFLASH_OB_IsWWDGDefaultEnable(EFLASH_GET_INSTANCE)) ?
                (HAL_EFLASH_WWDG_DEFAULT_ENABLE) :
                    (HAL_EFLASH_WWDG_DEFAULT_DISABLE));
}

/**
  * @brief  Get the IWDG default enable status from the EFLASH option bytes.
  * @return IWDG default enable status.
  */
HAL_EFLASH_IWDGDefEnTypeDef HAL_EFLASH_OB_GetIWDGDefaultEnableStatus(void)
{
    return ((LL_EFLASH_OB_IsIWDGDefaultEnable(EFLASH_GET_INSTANCE)) ?
                (HAL_EFLASH_IWDG_DEFAULT_ENABLE) :
                    (HAL_EFLASH_IWDG_DEFAULT_DISABLE));
}

/**
  * @brief  Get the Boot lock status from the EFLASH option bytes.
  * @return Boot lock configuration status.
  */
HAL_EFLASH_BootLockCfgTypeDef HAL_EFLASH_OB_GetBootLockStatus(void)
{
    return ((LL_EFLASH_OB_IsBootLock(EFLASH_GET_INSTANCE)) ?
                (HAL_EFLASH_BOOT_LOCK_CFG_LOCK) :
                    (HAL_EFLASH_BOOT_LOCK_CFG_UNLOCK));
}

/**
  * @brief  Get the Power-on ECC bypass status from the EFLASH option bytes.
  * @return Power-on ECC bypass status.
  */
HAL_EFLASH_PwrOnEccBypassTypeDef HAL_EFLASH_OB_GetPowerOnECCBypassStatus(void)
{
    return ((LL_EFLASH_OB_IsPowerOnECCBypassEnable(EFLASH_GET_INSTANCE)) ?
                (HAL_EFLASH_PWRON_ECC_BYPASS_ENABLE) :
                    (HAL_EFLASH_PWRON_ECC_BYPASS_DISABLE));
}

/**
  * @}
  */ /* EFLASH_HAL_EF_Information */


/** @defgroup EFLASH_HAL_EF_Operation EFLASH Operation Functions
  * @brief    EFLASH Operation Functions
  * @{
  */

/**
  * @brief  Program an amount of data at a specified address in CPU blocking mode.
  * @note   The address and size must be aligned to 8 bytes. Data is programmed
  *         8 bytes at a time (two 32-bit words). The function waits for each
  *         program operation to complete before proceeding.
  * @param  Address Program start relative address (must be 8-byte aligned)
  * @param  Buff Pointer to the data buffer to be programmed
  * @param  Size Program data size in bytes (must be a multiple of 8)
  * @retval Number of bytes successfully programmed (0 on error)
  */
uint32_t HAL_EFLASH_Program(uint32_t Address, uint8_t *Buff, uint32_t Size)
{
    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    Address &= HAL_EFLASH_PROG_ADDRESS_MASK;
    uint32_t i, *buf_32, cnt = 0, chip_size = EFLASH_GetChipSize(EFLASH_GET_INSTANCE);

    ASSERT_FUNC_PARAM(LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(Address));
    ASSERT_FUNC_PARAM(LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(Size));
    ASSERT_FUNC_PARAM(Buff != NULL);
    ASSERT_FUNC_PARAM(Address < chip_size);
    ASSERT_FUNC_PARAM((Address + Size) <= chip_size);

    HAL_EFLASH_PARAM_CHECK({
        if (!IS_EFLASH_ALL_INSTANCE(p_instance) || !LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(Address) ||
            !LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(Size) || Buff == NULL || Address >= chip_size ||
            (Address + Size) > chip_size) {
            return 0;
        }
    });

    /* Wait for EFLASH Idle */
    if (EFLASH_WaitForBusyState(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return 0;
    }

    buf_32 = (uint32_t *)Buff;

    /* Unlock Program/Erase access */
    EFLASH_ProgErase_Unlock(p_instance);

    for (i = 0; i < Size / LL_EFLASH_PROG_SINGLE_SIZE; i++) {
        /* Program data Config */
        LL_EFLASH_SetProgramData0(p_instance, *buf_32++);
        LL_EFLASH_SetProgramData1(p_instance, *buf_32++);

        /* Program address Config */
        LL_EFLASH_SetProgramAddress(p_instance, Address);

        /* Program Start */
        LL_EFLASH_ProgramStart(p_instance);

        /* Wait for Programming Complete */
        if (EFLASH_WaitForLastOpCplt(p_instance, HAL_EFLASH_OP_PROG, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
            goto exit;
        }

        Address += LL_EFLASH_PROG_SINGLE_SIZE;
        cnt  += LL_EFLASH_PROG_SINGLE_SIZE;
    }

exit:
    /* Lock Program/Erase access */
    EFLASH_ProgErase_Lock(p_instance);

    return cnt;
}

/**
  * @brief  Erase multiple sectors in CPU blocking mode.
  * @note   The function sets the erase mode to sector, then iteratively erases
  *         each sector from SectorStart for Number sectors. It waits for each
  *         sector erase to complete.
  * @param  SectorStart The first sector number to erase (0-based)
  * @param  Number Number of sectors to erase
  * @retval Number of sectors successfully erased
  */
uint32_t HAL_EFLASH_EraseMultiSector(uint32_t SectorStart, uint32_t Number)
{
    uint32_t sec_nums = EFLASH_GetSectorNums(EFLASH_GET_INSTANCE);

    ASSERT_FUNC_PARAM(SectorStart < sec_nums);
    ASSERT_FUNC_PARAM((SectorStart + Number - 1) < sec_nums);

    HAL_EFLASH_PARAM_CHECK({
        if (SectorStart >= sec_nums || (SectorStart + Number - 1) >= sec_nums) {
            return 0;
        }        
    });

    return EFLASH_EraseMultiSector(EFLASH_GET_INSTANCE, SectorStart, Number);
}

/**
  * @brief  Erase a single sector in CPU blocking mode.
  * @param  SectorNumber The sector number to erase (0-based)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_EraseSector(uint32_t SectorNumber)
{
    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;
    uint32_t sec_nums = EFLASH_GetSectorNums(EFLASH_GET_INSTANCE);

    ASSERT_FUNC_PARAM(SectorNumber < sec_nums);

    if (SectorNumber >= sec_nums) {
        return HAL_INVALID;
    }

    if (EFLASH_WaitForBusyState(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    if (EFLASH_EraseMultiSector(p_instance, SectorNumber, 1) == 1) {
        return HAL_OK;
    } else {
        return HAL_ERROR;
    }
}

/**
  * @brief  Erase the entire chip in CPU blocking mode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_EraseChip(void)
{
    return EFLASH_EraseCommon(EFLASH_GET_INSTANCE, HAL_EFLASH_ERASE_MODE_CHIP);
}

/**
  * @brief  Erase Bank0 in CPU blocking mode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_EraseBank0(void)
{
    return EFLASH_EraseCommon(EFLASH_GET_INSTANCE, HAL_EFLASH_ERASE_MODE_BANK0);
}

/**
  * @brief  Erase Bank1 in CPU blocking mode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_EFLASH_EraseBank1(void)
{
    return EFLASH_EraseCommon(EFLASH_GET_INSTANCE, HAL_EFLASH_ERASE_MODE_BANK1);
}


/**
  * @brief  Verify data at a specified address by comparing with a buffer.
  * @note   This function performs a byte-by-byte comparison between the
  *         content of the EFLASH (starting from the given address) and the
  *         user buffer. It returns the number of matching bytes.
  * @param  Address Verify start relative address
  * @param  Buff Pointer to the data buffer to compare
  * @param  Size Number of bytes to verify
  * @retval Number of bytes that matched successfully (0 on invalid parameters)
  */
uint32_t HAL_EFLASH_Verify(uint32_t Address, uint8_t *Buff, uint32_t Size)
{
    Address &= HAL_EFLASH_PROG_ADDRESS_MASK;

    uint32_t chip_size = EFLASH_GetChipSize(EFLASH_GET_INSTANCE);

    ASSERT_FUNC_PARAM(Buff != NULL);
    ASSERT_FUNC_PARAM(Address < chip_size);
    ASSERT_FUNC_PARAM((Address + Size) <= chip_size);

    HAL_EFLASH_PARAM_CHECK({
        if (Buff == NULL || Address >= chip_size || (Address + Size) > chip_size) {
            return 0;
        }    
    });

    uint32_t cnt, cmp_addr;

    for (cnt = 0, cmp_addr = Address + EFLASH_MEM_BASE; cnt < Size; cnt++, cmp_addr++) {
        if (*((uint8_t *)cmp_addr) != Buff[cnt]) {
            break;
        }
    }

    return cnt;
}

/**
  * @brief  Launch the read/write protection feature reloading.
  * @note   This function triggers the reload of protection settings from the
  *         option bytes to make them effective.
  * @retval None
  */
HAL_StatusTypeDef HAL_EFLASH_ReadWriteProtect_Launch(void)
{

    HAL_StatusTypeDef ret;
    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;

    /* Wait for EFLASH Idle */
    ret = EFLASH_WaitForBusyState(p_instance, HAL_EFLASH_DEFAULT_TIMEOUT);

    if (ret == HAL_OK) {
        /* Unlock Read/Write Protect Config */
        if (EFLASH_RWProtOptDat_Unlock(p_instance) != HAL_OK) {
            return HAL_FAILED;
        }

        LL_EFLASH_LaunchRWProtectUpdate(p_instance);

        /* Wait for Operation Complete */
        ret = EFLASH_WaitForLastOpCplt(p_instance, HAL_EFLASH_OP_RW_PROT, HAL_EFLASH_DEFAULT_TIMEOUT);

        /* Error has been cleared. */
        if (ret != HAL_TIMEOUT) {
            ret = HAL_OK;
        }

        /* Lock Read/Write Protect Config */
        EFLASH_RWProtOptDat_Lock(p_instance);
    }

    return ret;
}

/**
  * @}
  */ /* EFLASH_HAL_EF_Operation */

/** @defgroup EFLASH_HAL_EF_Interrupt EFLASH Interrupt Handler and Callback
  * @brief    EFLASH Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  Enable the EFLASH error interrupt.
  * @retval None
  */
void HAL_EFLASH_ErrorInterruptEnable(void)
{
    LL_EFLASH_EnableIT_EIE(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Disable the EFLASH error interrupt.
  * @retval None
  */
void HAL_EFLASH_ErrorInterruptDisable(void)
{
    LL_EFLASH_DisableIT_EIE(EFLASH_GET_INSTANCE);
}

/**
  * @brief  Handle EFLASH interrupt requests.
  * @note   This function checks all interrupt pending flags (operation error,
  *         write protect error, illegal operation error, single bit error)
  *         and calls the corresponding callbacks. It is expected to be called
  *         from the EFLASH interrupt handler.
  * @retval None
  */
void HAL_EFLASH_IRQHandler(void)
{
    EFLASH_TypeDef *p_instance = EFLASH_GET_INSTANCE;

    /* Check Error Interrupt Enable or not */
    if (!LL_EFLASH_IsEnabledIT_EIE(p_instance)) {
        return;
    }

    /* All Interrupt Pending Get */
    const uint32_t int_pending = LL_EFLASH_GetInterruptFlags(p_instance);

    /* Operation Error Interrupt Handler */
    if (int_pending & LL_EFLASH_SR_OES) {
        /* Clear Interrupt Pending */
        LL_EFLASH_ClearFlag_OES(p_instance);

        /* Callback */
        HAL_EFLASH_OperationErrorCallback(p_instance);
    }

    /* Write Protect Error Interrupt Handler */
    if (int_pending & LL_EFLASH_SR_WPS) {
        /* Clear Interrupt Pending */
        LL_EFLASH_ClearFlag_WPS(p_instance);

        /* Callback */
        HAL_EFLASH_WriteProtectErrorCallback(p_instance);
    }

    /* Illegal Operation Error Interrupt Handler */
    if (int_pending & LL_EFLASH_SR_IOS) {
        /* Clear Interrupt Pending */
        LL_EFLASH_ClearFlag_IOS(p_instance);

        /* Callback */
        HAL_EFLASH_IllegalOperationErrorCallback(p_instance);
    }

    /* Single Bit Error Interrupt Handler */
    if (int_pending & LL_EFLASH_SR_SBC) {
        /* Clear Interrupt Pending */
        LL_EFLASH_ClearFlag_SBC(p_instance);

        /* Callback */
        HAL_EFLASH_SingleBitErrorCallback(p_instance);
    }
}

/**
  * @brief  EFLASH Operation Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void HAL_EFLASH_OperationErrorCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_EFLASH_OperationErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  EFLASH Write Protect Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void HAL_EFLASH_WriteProtectErrorCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_EFLASH_WriteProtectErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  EFLASH Illegal Operation Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void HAL_EFLASH_IllegalOperationErrorCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_EFLASH_IllegalOperationErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  EFLASH Single Bit Error Interrupt Callback
  * @param  Instance Specifies EFLASH peripheral
  * @return None
  */
__WEAK void HAL_EFLASH_SingleBitErrorCallback(EFLASH_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    HAL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_EFLASH_SingleBitErrorCallback could be implemented in the user file
     */
}

/**
  * @}
  */ /* EFLASH_HAL_EF_Interrupt */

/**
  * @}
  */ /* EFLASH_HAL_Exported_Functions */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup EFLASH_HAL_Private_Functions
  * @{
  */

/**
  * @brief  Get the total EFLASH chip size in bytes.
  * @note   The size is determined by reading the hardware configuration.
  *         For this implementation: 128KB or 256KB.
  * @param  Instance Specifies EFLASH peripheral
  * @retval Chip size in bytes
  */
__STATIC_INLINE uint32_t EFLASH_GetChipSize(EFLASH_TypeDef *Instance)
{
    if (LL_EFLASH_IsSize128KB(Instance) == 1UL) {
        return 128 * 1024;  
    } else {
        return 256 * 1024;  
    }
}

/**
  * @brief  Get the number of sectors in the EFLASH.
  * @note   Sector count depends on chip size and bank mode.
  * @param  Instance Specifies EFLASH peripheral
  * @retval Number of sectors
  */
__STATIC_INLINE uint32_t EFLASH_GetSectorNums(EFLASH_TypeDef *Instance)
{
    uint32_t chip_size = EFLASH_GetChipSize(Instance);

    if (chip_size == 128 * 1024) {
        return LL_EFLASH_SECTOR_NUM_128;
    } else if (chip_size == 256 * 1024) {
        if ((HAL_EFLASH_BankModeTypeDef)LL_EFLASH_OB_GetBankMode(Instance) == HAL_EFLASH_BANK_MODE_DOUBLE) {
            return LL_EFLASH_SECTOR_NUM_256_D;
        } else {
            return LL_EFLASH_SECTOR_NUM_256_S;
        }
    }

    return 0;
}

/**
  * @brief  Get the EFLASH sector size in bytes.
  * @note   Sector size depends on chip size and bank mode.
  * @param  Instance Specifies EFLASH peripheral
  * @retval Sector size in bytes
  */
__STATIC_INLINE uint32_t EFLASH_GetSectorSize(EFLASH_TypeDef *Instance)
{
    uint32_t chip_size = EFLASH_GetChipSize(Instance);

    if (chip_size == 128 * 1024) {
        return LL_EFLASH_SECTOR_SIZE_128;
    } else if (chip_size == 256 * 1024) {
        if ((HAL_EFLASH_BankModeTypeDef)LL_EFLASH_OB_GetBankMode(Instance) == HAL_EFLASH_BANK_MODE_DOUBLE) {
            return LL_EFLASH_SECTOR_SIZE_256_D;
        } else {
            return LL_EFLASH_SECTOR_SIZE_256_S;
        }
    }

    return 0;
}


/**
  * @brief  EFLASH last operation status get
  * @param  Instance Specifies EFLASH peripheral
  * @param  LastOp last operation
  * @retval 0: last operation isn't Done
  * @retval 1: last operation is Done
  */
__STATIC_INLINE uint32_t EFLASH_LastOptSta_Get(EFLASH_TypeDef *Instance, 
                                               HAL_EFLASH_OpTypeDef LastOp)
{
    if(!LL_EFLASH_IsIdle(Instance)) {
        return 0UL;
    }

    switch (LastOp) {
        case HAL_EFLASH_OP_PROG:
            return LL_EFLASH_IsProgramOpDone(Instance);

        case HAL_EFLASH_OP_ERASE:
            return LL_EFLASH_IsEraseOpDone(Instance);

        case HAL_EFLASH_OP_STDBY:
            return LL_EFLASH_IsStdbyOpDone(Instance);

        case HAL_EFLASH_OP_WAKEUP:
            return LL_EFLASH_IsWakeupOpDone(Instance);

        case HAL_EFLASH_OP_RW_PROT:
        case HAL_EFLASH_OP_OPT_DAT:
            return LL_EFLASH_IsRwProtOptDatOpDone(Instance);                

        default:
            return 1UL;
    }
}

/**
  * @brief  Wait until the EFLASH is idle (no ongoing operations) or timeout.
  * @note   This function checks all operation done flags (program, erase,
  *         standby, wakeup, read/write protection) and the idle flag.
  *         If any error flag is set, it clears them and returns HAL_ERROR.
  * @param  Instance Specifies EFLASH peripheral
  * @param  Timeout Maximum waiting time in ms. Use HAL_WAIT_FOREVER for infinite wait.
  * @retval HAL status
  */
__STATIC_INLINE HAL_StatusTypeDef EFLASH_WaitForBusyState(EFLASH_TypeDef *Instance, 
                                                          uint32_t Timeout)
{
    uint32_t tickstart = HAL_GetTick();
    volatile uint32_t oper_done = 0UL;

    /* Wait for All Operation Done */
    do {
        oper_done = LL_EFLASH_IsProgramOpDone(Instance)      & LL_EFLASH_IsEraseOpDone(Instance)  &
                    LL_EFLASH_IsStdbyOpDone(Instance)        & LL_EFLASH_IsWakeupOpDone(Instance) &
                    LL_EFLASH_IsRwProtOptDatOpDone(Instance) & LL_EFLASH_IsIdle(Instance);
        if (Timeout != HAL_WAIT_FOREVER && (HAL_GetTick() - tickstart) > Timeout) {
            return HAL_TIMEOUT;
        }
    } while (oper_done == (uint32_t)0);

    /* Check if any errors occurred */
    if (LL_EFLASH_IsAnyErrorActive(Instance)) {
        LL_EFLASH_ClearAllErrorFlags(Instance);
        return HAL_ERROR;
    }

    return HAL_OK;
}

/**
  * @brief  Wait for the last specific operation to complete, checking for errors.
  * @note   This function polls the status of the given operation type. It checks
  *         for errors first, as the operation may not have started if an error
  *         already occurred. When the operation is done, it returns HAL_OK.
  * @param  Instance Specifies EFLASH peripheral
  * @param  LastOp The operation type to wait for.
  *         This parameter can be a value of @ref HAL_EFLASH_OpTypeDef
  * @param  Timeout Maximum waiting time in ms. Use HAL_WAIT_FOREVER for infinite wait.
  * @retval HAL status
  */
__STATIC_INLINE HAL_StatusTypeDef EFLASH_WaitForLastOpCplt(EFLASH_TypeDef *Instance, 
                                                           HAL_EFLASH_OpTypeDef LastOp, 
                                                           uint32_t Timeout)
{
    uint32_t tickstart = HAL_GetTick();

    /* Wait for Done flag, check any error occurred first, because operation may not start and error occured */
    do {
        /* Check if any errors occurred */
        if (LL_EFLASH_IsAnyErrorActive(Instance)) {
            LL_EFLASH_ClearAllErrorFlags(Instance);
            return HAL_ERROR;
        }

        if (Timeout != HAL_WAIT_FOREVER && (HAL_GetTick() - tickstart) > Timeout) {
            return HAL_TIMEOUT;
        }
    } while (EFLASH_LastOptSta_Get(Instance, LastOp) == (uint32_t)0);        

    return HAL_OK;
}

/**
  * @brief  EFLASH Check Ready Status before Unlock
  * @param  Instance Specifies EFLASH peripheral
  * @param  Timeout Timeout duration for each wait operation
  * @return HAL Status
  */
static HAL_StatusTypeDef EFLASH_OB_CheckReadyAndUnlock(EFLASH_TypeDef *Instance, 
                                                       uint32_t Timeout)
{
    /* Wait for EFLASH Idle */
    if (EFLASH_WaitForBusyState(Instance, Timeout) != HAL_OK) {
        return HAL_ERROR;
    }

    /* Unlock Option Data Config */
    if (EFLASH_RWProtOptDat_Unlock(Instance) != HAL_OK) {
        return HAL_FAILED;
    }

    /* Wait for EFLASH operation to complete */
    if (EFLASH_WaitForLastOpCplt(Instance, HAL_EFLASH_OP_OPT_DAT, Timeout) != HAL_OK) {
        return HAL_BUSY;
    } else {
        return HAL_OK;
    }
}

/**
  * @brief  Check if the EFLASH is idle and lock the option data access.
  * @param  Instance Specifies EFLASH peripheral
  * @param  Timeout Timeout duration for each wait operation
  * @return HAL Status
  */
static HAL_StatusTypeDef EFLASH_OB_CheckIdleAndLock(EFLASH_TypeDef *Instance, 
                                                    uint32_t Timeout)
{
    /* Wait for EFLASH Idle */
    if (EFLASH_WaitForBusyState(Instance, Timeout) != HAL_OK) {
        return HAL_BUSY;
    }

    /* Lock Option Data Config */
    if (EFLASH_RWProtOptDat_Lock(Instance) != HAL_OK) {
        return HAL_FAILED;///TODO
    }

    /* Wait for Option Data Operation Complete */
    if (EFLASH_WaitForLastOpCplt(Instance, HAL_EFLASH_OP_OPT_DAT, Timeout) != HAL_OK) {
        return HAL_TIMEOUT;
    }

    return HAL_OK;
}

/**
  * @brief  Perform a chip or bank erase in CPU blocking mode.
  * @note   This function only supports erase modes other than sector erase.
  * @param  Instance Specifies EFLASH peripheral
  * @param  EraseMode Erase mode (chip, bank0, bank1)
  * @return HAL status
  */
__STATIC_INLINE HAL_StatusTypeDef EFLASH_EraseCommon(EFLASH_TypeDef *Instance, 
                                                     HAL_EFLASH_EraseModeTypeDef EraseMode)
{
    /* Check Erase Mode */
    if (EraseMode == HAL_EFLASH_ERASE_MODE_SECTOR) {
        /* This interface don't support SECTOR erase mode */
        return HAL_INVALID;
    }

    /* Wait for EFLASH Idle */
    if (EFLASH_WaitForBusyState(Instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return HAL_BUSY;
    }

    /* Unlock Program/Erase access */
    if (EFLASH_ProgErase_Unlock(Instance) != HAL_OK) {
        return HAL_FAILED;
    }

    /* Erase mode Set */
    LL_EFLASH_SetEraseMode(Instance, EraseMode);

    /* Erase Start */
    LL_EFLASH_EraseStart(Instance);

    /* Wait for Erase Complete */
    if (EFLASH_WaitForLastOpCplt(Instance, HAL_EFLASH_OP_ERASE, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        /* Lock Program/Erase access */
        EFLASH_ProgErase_Lock(Instance);
        return HAL_ERROR;
    }

    /* Flush the caches to be sure of the data consistency */
    LL_EFLASH_CacheRefresh(Instance);

    /* Lock Program/Erase access */
    if (EFLASH_ProgErase_Lock(Instance) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}


/**
  * @brief  Unlock the EFLASH program/erase access.
  * @note   This function writes the two key values to unlock the program/erase
  *         lock bit. If the lock is already released, it does nothing.
  * @param  Instance Specifies EFLASH peripheral
  * @retval HAL status
  */
__STATIC_INLINE HAL_StatusTypeDef EFLASH_ProgErase_Unlock(EFLASH_TypeDef *Instance)
{
    if (LL_EFLASH_IsProgramEraseLock(Instance)) {
        /* Authorize the FLASH Program/Erase access */
        LL_EFLASH_SetKey(Instance, LL_EFLASH_PROG_ERASE_KEY1);
        LL_EFLASH_SetKey(Instance, LL_EFLASH_PROG_ERASE_KEY2);

        /* Verify EFLASH is unlocked */
        if (LL_EFLASH_IsProgramEraseLock(Instance)) {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Lock the EFLASH program/erase access.
  * @note   This function sets the program/erase lock bit. If already locked,
  *         it does nothing.
  * @param  Instance Specifies EFLASH peripheral
  * @retval HAL status
  */
__STATIC_INLINE HAL_StatusTypeDef EFLASH_ProgErase_Lock(EFLASH_TypeDef *Instance)
{
    if (!LL_EFLASH_IsProgramEraseLock(Instance)) {
        /* Set the LOCK Bit to lock the EFLASH Program/Erase access */
        LL_EFLASH_SetProgramEraseLock(Instance);

        /* Verify EFLASH is Locked */
        if (!LL_EFLASH_IsProgramEraseLock(Instance)) {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Unlock the EFLASH read/write protection and option data access.
  * @note   This function writes the two key values to unlock the RW protection
  *         and option data lock bit. It also waits for the unlock to take effect.
  * @param  Instance Specifies EFLASH peripheral
  * @retval HAL status
  */
__STATIC_INLINE HAL_StatusTypeDef EFLASH_RWProtOptDat_Unlock(EFLASH_TypeDef *Instance)
{
    uint32_t tickstart = HAL_GetTick();

    if (LL_EFLASH_IsRwProtOptDatConfigLock(Instance)) {
        /* Authorize the EFLASH Read/Write Protect access */
        LL_EFLASH_SetKey(Instance, LL_EFLASH_RW_PROTECT_OPT_DAT_KEY1);
        LL_EFLASH_SetKey(Instance, LL_EFLASH_RW_PROTECT_OPT_DAT_KEY2);

        /* Verify EFLASH is unlocked */
        while (LL_EFLASH_IsRwProtOptDatConfigLock(Instance)) {
            if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
                return HAL_ERROR;
            }
        }
    }

    return HAL_OK;
}

/**
  * @brief  Lock the EFLASH read/write protection and option data access.
  * @note   This function sets the lock bit for RW protection and option data.
  *         It also waits for the lock to take effect.
  * @param  Instance Specifies EFLASH peripheral
  * @retval HAL status
  */
__STATIC_INLINE HAL_StatusTypeDef EFLASH_RWProtOptDat_Lock(EFLASH_TypeDef *Instance)
{
    uint32_t tickstart = HAL_GetTick();

    if (!LL_EFLASH_IsRwProtOptDatConfigLock(Instance)) {
        /* Set the LOCK Bit to lock the EFLASH Read/Write Protect access */
        LL_EFLASH_LockRwProtOptDatConfig(Instance);

        /* Verify EFLASH is Locked */
        while (!LL_EFLASH_IsRwProtOptDatConfigLock(Instance)) {
            if ((HAL_GetTick() - tickstart) > HAL_EFLASH_DEFAULT_TIMEOUT) {
                return HAL_ERROR;
            }
        }
    }

    return HAL_OK;
}


/**
  * @brief  Erase multiple sectors in CPU blocking mode.
  * @note   The function sets the erase mode to sector, then iteratively erases
  *         each sector from SectorStart for Number sectors. It waits for each
  *         sector erase to complete.
  * @param  Instance Specifies EFLASH peripheral
  * @param  SectorStart The first sector number to erase (0-based)
  * @param  Number Number of sectors to erase
  * @retval Number of sectors successfully erased
  */
__STATIC_INLINE uint32_t EFLASH_EraseMultiSector(EFLASH_TypeDef *Instance, 
                                                 uint32_t SectorStart, 
                                                 uint32_t Number)
{
    uint32_t i, sec_nums = EFLASH_GetSectorNums(Instance);

    if (SectorStart >= sec_nums || (SectorStart + Number - 1) >= sec_nums) {
        return 0;
    }        

    /* Wait for EFLASH Idle */
    if (EFLASH_WaitForBusyState(Instance, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
        return 0;
    }

    /* Set to Sector Erase mode */
    LL_EFLASH_SetEraseMode(Instance, HAL_EFLASH_ERASE_MODE_SECTOR);

    /* Unlock Program/Erase access */
    EFLASH_ProgErase_Unlock(Instance);

    for (i = 0; i < Number; i++) {
        /* Sector number Config */
        LL_EFLASH_SetEraseSectorNumber(Instance, (SectorStart + i));

        /* Erase Start */
        LL_EFLASH_EraseStart(Instance);

        /* Wait for Sector Erase Complete */
        if (EFLASH_WaitForLastOpCplt(Instance, HAL_EFLASH_OP_ERASE, HAL_EFLASH_DEFAULT_TIMEOUT) != HAL_OK) {
            goto exit;
        }
    }

    /* Flush the caches to be sure of the data consistency */
    LL_EFLASH_CacheRefresh(Instance);

exit:
    /* Lock Program/Erase access */
    EFLASH_ProgErase_Lock(Instance);

    return i;
}

/**
  * @}
  */ /* EFLASH_HAL_Private_Functions */

/**
  * @}
  */ /* EFLASH_HAL */

#endif /* HAL_EFLASH_MODULE_ENABLED */
#endif /* HAL_MODULE_ENABLED */
#endif /* EFLASH */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

