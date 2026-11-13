/* Host-only: fix 32-bit truncated REG_OFFSET macros when running LL on 64-bit Windows.
 * Include after the peripheral LL header (and device types). Do not modify vendor SDK. */
#ifndef TAE32_LL_HOST_SHIM_H
#define TAE32_LL_HOST_SHIM_H

#include <stdint.h>
#include <stddef.h>

#ifndef TAE32_LL_HOST_REG_OFFSET
#define TAE32_LL_HOST_REG_OFFSET(__REG__, offset, elemBits) \
    (*(volatile uint32_t *)((uintptr_t)(&(__REG__)) + ((uintptr_t)(offset) * ((elemBits) / 8u))))
#endif

#undef LL_ADC_DMA_REG_OFFSET
#define LL_ADC_DMA_REG_OFFSET(__REG__, offset) \
    (*(volatile ADC_DMA_TypeDef *)((uintptr_t)(&(__REG__)) + ((uintptr_t)(offset) * sizeof(ADC_DMA_TypeDef))))

#undef LL_ADC_REG_OFFSET
#define LL_ADC_REG_OFFSET(__REG__, offset) \
    TAE32_HOST_REG_OFFSET(__REG__, (offset), 32)

#undef LL_ADTMR_REG_OFFSET
#define LL_ADTMR_REG_OFFSET(__REG__, offset) TAE32_LL_HOST_REG_OFFSET(__REG__, offset, 32)

#undef LL_GPTMRX_REG_OFFSET
#define LL_GPTMRX_REG_OFFSET(__REG__, offset) TAE32_LL_HOST_REG_OFFSET(__REG__, offset, 32)

#undef LL_GPTMRY_REG_OFFSET
#define LL_GPTMRY_REG_OFFSET(__REG__, offset) TAE32_LL_HOST_REG_OFFSET(__REG__, offset, 32)

#undef LL_LPTMR_REG_OFFSET
#define LL_LPTMR_REG_OFFSET(__REG__, offset) TAE32_LL_HOST_REG_OFFSET(__REG__, offset, 32)

#undef LL_IIR_COEF_REG_OFFSET
#define LL_IIR_COEF_REG_OFFSET(__REG__, offset) \
    (*(volatile IIR_Coef_TypeDef *)((uintptr_t)(&(__REG__)) + ((uintptr_t)(offset) * sizeof(IIR_Coef_TypeDef))))

#undef LL_HRPWM_REG_OFFSET
#define LL_HRPWM_REG_OFFSET(__REG__, offset) TAE32_HOST_REG_OFFSET(__REG__, offset, 32)

#endif
