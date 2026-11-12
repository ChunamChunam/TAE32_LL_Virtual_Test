/**
  ******************************************************************************
  * @file    tae32g58xx_ll_def.h
  * @author  Tai-Action SD Team
  * @brief   This file contains LL common defines, enumeration, macros and
  *          structures definitions.
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
#ifndef _TAE32G58XX_LL_DEF_H_
#define _TAE32G58XX_LL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "tae32g58xx.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup DEFINE_LL DEFINE LL
  * @brief    DEFINE LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup DEFINE_LL_Exported_Constants DEFINE LL Exported Constants
  * @brief    DEFINE LL Exported Constants
  * @{
  */

/**
  * @brief LL wait max delay time definition
  * @note  The exact time depends on the timing unit of the timer
  */
#define LL_MAX_DELAY                        (0xFFFFFFFEUL)

/**
  * @}
  */ /* DEFINE_LL_Exported_Constants */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup DEFINE_LL_Exported_Types DEFINE LL Exported Types
  * @brief    DEFINE LL Exported Types
  * @{
  */

/* LL Reserved Data Type */
#if defined(TAE32_USE_LL_RSV_DATA_TYPE) && (TAE32_USE_LL_RSV_DATA_TYPE == 1)
#if defined(TAE32_USE_LL_RSV_DATA_TYPE_CUSTOM)
#define LL_RSV_DATA_TYPE  TAE32_USE_LL_RSV_DATA_TYPE_CUSTOM
#else
#define LL_RSV_DATA_TYPE  uint32_t
#endif /* TAE32_USE_LL_RSV_DATA_TYPE_CUSTOM */
#else
#define LL_RSV_DATA_TYPE  uint32_t
#endif /* TAE32_USE_LL_RSV_DATA_TYPE */

/**
  * @}
  */ /* DEFINE_LL_Exported_Types */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup DEFINE_LL_Exported_Macros DEFINE LL Exported Macros
  * @brief    DEFINE LL Exported Macros
  * @{
  */

/** @defgroup DEFINE_LL_EM_Compiler DEFINE LL Compiler Attribute
  * @brief    DEFINE LL Compiler Attribute
  * @{
  */

/* Check CMSIS Version */
#if defined(__CM_CMSIS_VERSION_MAIN) && (__CM_CMSIS_VERSION_MAIN >= 6)
#if defined(__CC_ARM)
#error "CMSIS 6 does not support Arm Compiler 5 (AC5). Please use Arm Compiler 6 or GCC."
#endif
#endif /* __CM_CMSIS_VERSION_MAIN */


/* Compiler __NOINLINE attribute definition */
#ifndef __NOINLINE
#if defined (__CC_ARM) || defined (__GNUC__)          /* ARM & GNUCompiler */
#define __NOINLINE                              __attribute__((noinline))
#elif defined (__ICCARM__)                              /* ICCARM Compiler */
#define __NOINLINE                              _Pragma("optimize = no_inline")
#endif
#endif /* __NOINLINE */


/* Compiler __NO_INIT attribute definition */
#ifndef __NO_INIT
#if defined (__CC_ARM)                                        /*!< AC5 Compiler */
#define __NO_INIT                               __attribute__((zero_init))
#elif defined (__ICCARM__)                                      /*!< IAR Compiler */
#define __NO_INIT                               __no_init
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  /*!< AC6 Compiler */
#define __NO_INIT
#elif defined (__GNUC__)                                        /*!< GCC Compiler */
#define __NO_INIT                               __attribute__((zero_init))
#endif
#endif /* __NO_INIT */


/* Compiler __AT attribute definition */
#ifndef __AT
#if defined (__CC_ARM)                                        /*!< AC5 Compiler */
#define __AT(n)                                 __attribute__((at(n)))
#elif defined (__ICCARM__)                                      /*!< IAR Compiler */
#define __AT(n)                                 @(n)
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  /*!< AC6 Compiler */
#define __AT(n)                                 __attribute__((section(".ARM.__at_"#n)))
#elif defined (__GNUC__)                                        /*!< GCC Compiler */
#define __AT(n)
#endif
#endif /* __AT */


/* Compiler __SECTION attribute definition */
#ifndef __SECTION
#if defined (__CC_ARM) || defined(__ARMCC_VERSION) || defined (__GNUC__)
#define __SECTION(SECT)                         __attribute__((section(#SECT)))
#elif defined (__ICCARM__)
//...
#endif
#endif /* __SECTION */


/* Compiler ALIAS and WEAK attribute definition */
#if   defined (__CC_ARM)                                        /*!< AC5 Compiler */
#define __ALIAS_FUNC(FUNC)                      __attribute__ ((weak, alias(#FUNC)))
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void) __attribute__ ((weak, alias(#FUNC_ALIAS)));
#elif defined (__ICCARM__)                                      /*!< IAR Compiler */
#define WEAK_STRINGIFY(x)                       #x
#define WEAK_STR(x)                             WEAK_STRINGIFY(x)
#define WEAK_ALIAS_PRAGMA(x)                    _Pragma(WEAK_STR(x))
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void);WEAK_ALIAS_PRAGMA(weak FUNC=FUNC_ALIAS)
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  /*!< AC6 Compiler */
#define __ALIAS_FUNC(FUNC)                      __attribute__ ((weak, alias(#FUNC)))
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void) __attribute__ ((weak, alias(#FUNC_ALIAS)));
#elif defined (__GNUC__)                                        /*!< GCC Compiler */
#define __ALIAS_FUNC(FUNC)                      __attribute__ ((weak, alias(#FUNC)))
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void) __attribute__ ((weak, alias(#FUNC_ALIAS)));
#else
#error Not supported compiler type
#endif


/* Macro to get variable aligned on 4-bytes, for __ICCARM__ the directive "#pragma data_alignment=4" must be used instead */
/* Compiler aligned on 4-bytes attribute definition */
#if defined ( __GNUC__ ) && !defined (__CC_ARM)         /* GNU Compiler */
#ifndef __ALIGN_END
#define __ALIGN_END                             __attribute__ ((aligned (4)))
#endif

#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif

#else

#ifndef __ALIGN_END
#define __ALIGN_END
#endif

#ifndef __ALIGN_BEGIN
#if defined   (__CC_ARM)                        /* ARM Compiler */
#define __ALIGN_BEGIN                           __align(4)
#elif defined (__ICCARM__)                      /* IAR Compiler */
#define __ALIGN_BEGIN
#endif
#endif
#endif


/* Workaround linked to CMSIS IAR issue EWARM-11901; a fix is expected from CMSIS Core. */
#if defined(__ICCARM__)
#define TAE32_CLREX_TO_DEPRECATE()              __ASM volatile("CLREX" ::: "memory")
#else
#define TAE32_CLREX_TO_DEPRECATE()              __CLREX()
#endif /* __ICCARM__ */

/**
  * @}
  */ /* DEFINE_LL_EM_Compiler */


/** @defgroup DEFINE_LL_EM_Operation DEFINE LL Operation
  * @brief    DEFINE LL Operation
  * @{
  */

/**
  * @brief  Bit left shift definition
  * @param  pos left shift position
  * @return Bit left shift value
  */
#define BIT(pos)                            (1UL << (pos))

/**
  * @brief  Bit Long Long Type left shift definition
  * @param  pos left shift position
  * @return Bit Long Long Type left shift value
  */
#define BITLL(pos)                          (1ULL << (pos))

/**
  * @brief  Set bit definition
  * @param  reg register
  * @param  bit Bit to set
  * @return None
  */
#define SET_BIT(reg, bit)                   ((reg) |= (bit))

/**
  * @brief  Clear bit definition
  * @param  reg register
  * @param  bit Bit to clear
  * @return None
  */
#define CLEAR_BIT(reg, bit)                 ((reg) &= ~(bit))

/**
  * @brief  Read bit definition
  * @param  reg register
  * @param  bit Bit to read
  * @return Read bit value
  */
#define READ_BIT(reg, bit)                  ((reg) & (bit))

/**
  * @brief  Read bit shift definition
  * @param  reg register
  * @param  bit Bit to read
  * @param  shift right shift after read
  * @return Read bit shift value
  */
#define READ_BIT_SHIFT(reg, bit, shift)     (((reg) & (bit)) >> (shift))

/**
  * @brief  Clear register definiton
  * @param  reg register
  * @return None
  */
#define CLEAR_REG(reg)                      ((reg) = (0x0))

/**
  * @brief  Write register definiton
  * @param  reg register
  * @param  val write value
  * @return None
  */
#define WRITE_REG(reg, val)                 ((reg) = (val))

/**
  * @brief  Read register definition
  * @param  reg register
  * @return Read register Value
  */
#define READ_REG(reg)                       ((reg))

/**
  * @brief  Modify register definition
  * @param  reg register
  * @param  clrmsk clear mask
  * @param  setmsk set mask
  * @return None
  */
#define MODIFY_REG(reg, clrmsk, setmsk) WRITE_REG((reg), (((READ_REG(reg)) & (~(clrmsk))) | ((setmsk) & (clrmsk))))

/**
  * @brief  Position value definition
  * @param  val value
  * @return Position value
  */
#define POSITION_VAL(val)                   (__CLZ(__RBIT(val)))

/**
  * @brief  Atomic 32-bit register set bit definition
  * @param  reg register
  * @param  bit Bit to set
  * @return None
  */
#define ATOMIC_SET_BIT(reg, bit)                                                      \
        do {                                                                          \
            uint32_t _tae32_inpa_val;                                                 \
            do {                                                                      \
                _tae32_inpa_val = __LDREXW((volatile uint32_t *)&(reg)) | (bit);      \
            } while ((__STREXW(_tae32_inpa_val,(volatile uint32_t *)&(reg))) != 0U);  \
        } while(0)

/**
  * @brief  Atomic 32-bit register clear bit definiton
  * @param  reg register
  * @param  bit Bit to clear
  * @return None
  */
#define ATOMIC_CLEAR_BIT(reg, bit)                                                    \
        do {                                                                          \
            uint32_t _tae32_inpa_val;                                                 \
            do {                                                                      \
                _tae32_inpa_val = __LDREXW((__IO uint32_t *)&(reg)) & ~(bit);         \
            } while ((__STREXW(_tae32_inpa_val,(__IO uint32_t *)&(reg))) != 0U);      \
        } while(0)

/**
  * @brief  Atomic 32-bit register modify definition
  * @param  reg register
  * @param  clrmsk clear mask
  * @param  setmsk set mask
  * @return None
  */
#define ATOMIC_MODIFY_REG(reg, clrmsk, setmsk)                                                \
        do {                                                                                  \
            uint32_t _tae32_inpa_val;                                                         \
            do {                                                                              \
                _tae32_inpa_val = (__LDREXW((__IO uint32_t *)&(reg)) & ~(clrmsk)) | (setmsk); \
            } while ((__STREXW(_tae32_inpa_val,(__IO uint32_t *)&(reg))) != 0U);              \
        } while(0)

/**
  * @brief  Extract the raw integer value of that field
  * @param  bits bits in register 32 bits
  * @param  mask mask in register 32 bits
  * @retval Bits in register 32 bits
  */
#define MASK_SHIFT(bits, mask)              (((bits) & (mask)) >> POSITION_VAL((mask)))

/**
  * @brief  Macro for counting the element number of an array
  * @param  array Array to be Counted
  * @return size of Array
  */
#define ARRAY_SIZE(array)                   (sizeof((array)) / sizeof((array)[0]))

/**
  * @brief  To avoid gcc/g++ warnings
  * @param  x avoid warning param
  * @return None
  */
#define PARAM_UNUSED(x)                     (void)(x)

/**
  * @}
  */ /* DEFINE_LL_EM_Operation */


/** @defgroup DEFINE_LL_EM_Assert DEFINE LL Assert
  * @brief    DEFINE LL Assert
  * @{
  */

#if defined(TAE32_GLOBAL_ASSERT_INLINE_PARAM)
extern void LL_Assert_Inline_Failed(uint8_t *File, uint32_t Line);

/**
  * @brief  The ASSERT_INLINE_PARAM macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls LL_Assert_Inline_Failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define ASSERT_INLINE_PARAM(expr)      ((expr) ? (void)0U : LL_Assert_Inline_Failed((uint8_t *)__FILE__, __LINE__))
#else
#define ASSERT_INLINE_PARAM(expr)      ((void)0U)
#endif


/**
  * @brief Atomically updates a volatile 32-bit variable with a masked conditional check and masked write.
  *
  * This macro performs an atomic compare-and-swap-like operation using ARM LDREX/STREX (exclusive access).
  * It reads the current value of \a upd_parm under exclusive access, checks whether the bits selected by
  * \a check_mask match \a check_value, and if the condition holds, writes a new value back where only
  * the bits set in \a new_mask are taken from \a new_value; all other bits remain unchanged (bitwise
  * update). If the check fails, the exclusive monitor is cleared and \a failed_expression is executed.
  * The entire sequence is protected by data memory barriers and retried until the store succeeds.
  *
  * @param[in,out] upd_parm          Variable to be updated. Must be of type `volatile uint32_t` and
  *                                  located in memory supporting ARM exclusive access (ARMv6+).
  *                                  This macro evaluates the address of \a upd_parm exactly once
  *                                  by storing it in a temporary pointer.
  * @param[in]     check_mask        Bitmask applied to the current value before comparison.
  *                                  Only the bits set in this mask are examined.
  * @param[in]     check_value       Expected value of the masked bits. The operation proceeds only if
  *                                  `(current_value & check_mask) == (check_value & check_mask)`.
  * @param[in]     new_mask          Bitmask that selects which bits of \a new_value will be written into
  *                                  \a upd_parm. Bits not set in \a new_mask are preserved.
  * @param[in]     new_value         The value whose bits (as selected by \a new_mask) will be stored.
  *                                  Bit positions not covered by \a new_mask are ignored.
  * @param[in]     failed_expression An expression (usually a control-flow statement like `return`,
  *                                  `break`, `goto`, or a function call) that is executed when the
  *                                  initial condition fails. This expression is placed inside the macro's
  *                                  scope and is expected to change program flow appropriately; otherwise
  *                                  execution continues after the macro.
  *
  * @note This macro uses ARM-specific intrinsics:
  *       - @c __LDREXW – load exclusive word
  *       - @c __STREXW – store exclusive word (returns 0 on success)
  *       - @c __DMB    – data memory barrier
  *       - @c TAE32_CLREX_TO_DEPRECATE – clears the exclusive monitor (resolves to @c __CLREX()
  *         or a platform-specific inline assembly for IAR).
  *
  * @warning **Busy‑wait loop**: The inner @c do-while retries until @c __STREXW returns 0.
  *          This is hardware‑dependent and may cause livelock if the exclusive monitor is repeatedly
  *          cleared by interrupts or other processors. Ensure critical sections are short.
  * @warning **No implicit memory fence before looping**: The `__DMB()` before the outer loop provides
  *          ordering, but the retry loop itself does not include additional barriers; this is acceptable
  *          because the exclusive access mechanism enforces necessary ordering.
  * @warning **Check failure does not write back**: When the check fails, `TAE32_CLREX_TO_DEPRECATE()` is
  *          called and then `failed_expression` is executed. A `break` statement inside the inner loop
  *          prevents any subsequent `__STREXW` from being attempted. The variable is not modified.
  * @warning **Parameter side‑effects are avoided**: All macro arguments are evaluated exactly once
  *          (address of \a upd_parm is taken, masks and values are used in expressions without
  *          duplication), so expressions like `reg++` or `func()` are safe.
  *
  * @code
  * volatile uint32_t ctrl_reg = 0x12345678;
  *
  * // Atomically clear bit 7 if bits [3:0] equal 0x08, otherwise return error.
  * UPDATE_CHECK_PARAM(ctrl_reg,
  *                    0x0F,       // check_mask – examine lower 4 bits
  *                    0x08,       // check_value – expect 0x8
  *                    0xFFFFFF7F, // new_mask – all bits except bit 7
  *                    0x00,       // new_value – bit 7 is 0, other bits are ignored because mask has 0
  *                    return -1); // failure expression
  * @endcode
  */
#define PARAM_UPDATE_CHECK_MASK(upd_parm, check_mask, check_value, new_mask, new_value, failed_expression)  \
    do {                                                                                               \
        volatile uint32_t *_ate32_inpa_ptr = &(upd_parm);                                              \
        uint32_t _ate32_inpa_old, _ate32_inpa_new;                                                     \
        __DMB();                                                                                       \
        do {                                                                                           \
            _ate32_inpa_old = __LDREXW(_ate32_inpa_ptr);                                               \
            if ((_ate32_inpa_old & (check_mask)) != (uint32_t)(check_value)) {                         \
                TAE32_CLREX_TO_DEPRECATE();                                                            \
                failed_expression;                                                                     \
                break;                                                                                 \
            }                                                                                          \
            _ate32_inpa_new = (_ate32_inpa_old & ~(new_mask)) | ((new_value) & (new_mask));            \
        } while (__STREXW(_ate32_inpa_new, _ate32_inpa_ptr) != 0U);                                    \
        __DMB();                                                                                       \
    } while (0)


/**
 * @brief   Atomically updates a 32-bit variable if its current value matches an expected check.
 *
 * @details This macro implements a Compare-And-Swap (CAS) operation using ARM's exclusive access
 *          instructions (LDREX/STREX). It checks whether the current value of \c upd_parm equals
 *          \c check_value. If so, it attempts to write \c new_value using a store-exclusive
 *          instruction, retrying until the store succeeds (i.e., the exclusive monitor is still
 *          valid). If the initial load indicates a mismatch, the macro releases the exclusive lock
 *          by calling \c TAE32_CLREX_TO_DEPRECATE() (which handles an IAR-specific workaround)
 *          and then executes the \c failed_expression.
 *
 *          The macro ensures proper memory ordering by inserting \c __DMB() barriers before and
 *          after the atomic sequence, guaranteeing that all preceding and subsequent memory accesses
 *          are observed in the correct order by other processors or peripherals.
 *
 * @note    This macro is intended for multi-core or interrupt-driven environments where atomic
 *          updates are required. It does not enforce a maximum retry count; if the exclusive
 *          store repeatedly fails (e.g., due to continuous contention), the loop may spin
 *          indefinitely. In a well-designed system, contention should be rare and transient.
 *
 * @param[in]   upd_parm           Reference to the volatile \c uint32_t variable to be conditionally updated.
 * @param[in]   check_value        Expected current value of \c upd_parm (compared as \c uint32_t ).
 * @param[in]   new_value          Desired new value to write if the check succeeds.
 * @param[in]   failed_expression  An expression (typically a break, return, or error handling statement)
 *                                 executed when the check fails (i.e., \c upd_parm != \c check_value ).
 *                                 This expression is not evaluated under any other condition.
 *
 * @warning Use of this macro requires that the target architecture supports ARMv6+ exclusive access
 *          instructions (LDREX/STREX). The definition of \c TAE32_CLREX_TO_DEPRECATE() contains a
 *          workaround for IAR Embedded Workbench (see EWARM-11901). On other compilers it falls back
 *          to \c __CLREX().
 *
 * @hideinitializer
 *
 * @see     __LDREXW(), __STREXW(), __DMB(), TAE32_CLREX_TO_DEPRECATE()
 */
#define PARAM_UPDATE_CHECK(upd_parm, check_value, new_value, failed_expression)                        \
    do {                                                                                               \
        volatile uint32_t *_ate32_inpa_ptr = (volatile uint32_t*)&(upd_parm);                          \
        __DMB();                                                                                       \
        do {                                                                                           \
            if ((__LDREXW(_ate32_inpa_ptr)) != (uint32_t)(check_value)) {                              \
                TAE32_CLREX_TO_DEPRECATE();                                                            \
                failed_expression;                                                                     \
                break;                                                                                 \
            }                                                                                          \
        } while (__STREXW(new_value, _ate32_inpa_ptr) != 0U);                                          \
        __DMB();                                                                                       \
    } while (0)

/**
  * @}
  */ /* DEFINE_LL_EM_Assert */

/**
  * @}
  */ /* DEFINE_LL_Exported_Macros */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/**
  * @}
  */ /* DEFINE_LL */

/**
  * @}
  */ /* TAE32G58xx_LL_Driver */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32G58XX_LL_DEF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

