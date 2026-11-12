/*
  ******************************************************************************
  * @file    tae32g5800_math.h
  * @author  Tai-Action Team
  * @brief   TAE32 Series Math Library - Hardware-Accelerated Trigonometric Functions.
  *          This file provides firmware functions to manage the following
  *          functionalities of the TAE32 Math Library:
  *           + Initialization and de-initialization functions
  *           + Floating-point trigonometric functions (for specific chips)
  *           + Fixed-point trigonometric functions (for specific chips)
  *
  @verbatim
  ==============================================================================
                        ##### How to use this library #####
  ==============================================================================
    [..]
    ​**​* How to configure and use Math Library ​**​*
    =============================================
    [..]
    This section provides guidelines for using the TAE32G5800 Math Library.

    (#) Configure the math computation type using __tae32_math_init() function.

    (#) For floating-point functions
        (++) Include __sinpuf32(), __cospuf32(), __atanpuf32() functions
        (++) Input range: x ∈ [-1.0, 1.0]
        (++) Computes sin(x*π), cos(x*π), atan(x) respectively

    (#) For fixed-point functions
        (++) Include Q15 (16-bit) and Q31 (32-bit) versions
        (++) Input range: x ∈ [-1.0, 1.0) mapped to radian values in [-π, π)
        (++) Functions: __sin_q15, __cos_q15, __atan_q15, __sin_q31, __cos_q31, __atan_q31

    (#) Make sure GNU extensions are enabled in your compiler settings.

    [..]
    ​**​* Usage Examples ​**​*
    ======================
    [..]
    Example for fixed-point usage 

    @code
    #include "tae32g5800_math.h"

    // Initialize math library for Q15 operations
    __tae32_math_init(TAE_FIXED_Q15);

    // Calculate sin using Q15 format
    short int result_q15 = __sin_q15(0x4000);
    @endcode

  @endverbatim
  ​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 Tai-Action.
  * All rights reserved.</center></h2>
  *
  ​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*​**​*
*/
#ifndef __TAE32_MATH_TAE32G5800_H
#define __TAE32_MATH_TAE32G5800_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum{
    TAE_FIXED_Q15,
    TAE_FIXED_Q31,
}tae32_math_data_type_t;

void __tae32_math_init(tae32_math_data_type_t type);

/**
 * @brief Calculate the value of sin(x) for Q15 data.
 * @param[in] x Input value in the range [-1, 1) and is mapped to a radian value in the range [-PI,PI)
 * @return sin(x)
 */
short int __sin_q15(short int x);

/**
 * @brief Calculate the value of cos(x) for Q15 data.
 * @param[in] x Input value in the range [-1, 1) and is mapped to a radian value in the range [-PI,PI)
 * @return cos(x)
 */
short int __cos_q15(short int x);

/**
 * @brief Calculate the value of atan(x) for Q15 data.
 * @param[in] x Input value in the range [-1, 1)
 * @return atan(x)
 */
short int __atan_q15(short int x);

/**
 * @brief Calculate the value of sin(x) for Q31 data.
 * @param[in] x Input value in the range [-1, 1) and is mapped to a radian value in the range [-PI,PI)
 * @return sin(x)
 */
int __sin_q31(int x);

/**
 * @brief Calculate the value of cos(x) for Q31 data.
 * @param[in] x Input value in the range [-1, 1) and is mapped to a radian value in the range [-PI,PI)
 * @return cos(x)
 */
int __cos_q31(int x);

/**
 * @brief Calculate the value of atan(x) for Q31 data.
 * @param[in] x Input value in the range [-1, 1)
 * @return atan(x)
 */
int __atan_q31(int x);

/**
 * @brief Calculate both sin(x) and cos(x) in Q15 (normalized input).
 * @param[in] x Input value in Q15 format, range [-1, 1).
 *            Internally mapped to radians: value = x * π.
 * @param[out] p_outx Output value sin(x) in Q15.
 * @param[out] p_outy Output value cos(x) in Q15.
 * @return None
 */
void __sinNcos_q15(short int x, short int *p_outx, short int *p_outy);

/**
 * @brief Calculate both sin(x) and cos(x) in Q31 (normalized input).
 * @param[in] x Input value in Q31 format, range [-1, 1).
 *            Internally mapped to radians: value = x * π.
 * @param[out] p_outx Output value sin(x) in Q31.
 * @param[out] p_outy Output value cos(x) in Q31.
 * @return None
 */
void __sinNcos_q31(int x, int *p_outx, int *p_outy);

#if defined(__cplusplus)
}
#endif

#endif
