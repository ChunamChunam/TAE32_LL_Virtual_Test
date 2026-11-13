/* Shared host peri RAM: chip singletons must match PERIx before LL headers are included. */
#ifndef TAE32_LL_HOST_PERI_GLOB_H
#define TAE32_LL_HOST_PERI_GLOB_H

#include <stdint.h>
#include <string.h>

#ifndef TAE32_HOST_PERI_IMAGE_BYTES
#define TAE32_HOST_PERI_IMAGE_BYTES (512u * 1024u)
#endif

#ifndef TAE32_HOST_PERI_GLOB_DEFINED
#define TAE32_HOST_PERI_GLOB_DEFINED 1
static uint8_t tae32_host_peri_image[TAE32_HOST_PERI_IMAGE_BYTES];
#endif

#define TAE32_HOST_PERI_CAST(T) ((T *)tae32_host_peri_image)

#undef SYSCTRL
#undef RCU
#undef ADC0
#undef ADC1
#undef ADC2
#undef ADC3
#undef IIR0
#undef IIR1
#undef IIR2
#undef IIR3
#undef IIR4
#undef IIR5
#undef HRPWM
#undef TMR0
#undef TMR1
#undef TMR2
#undef TMR9
#undef TMR10

#define SYSCTRL  TAE32_HOST_PERI_CAST(SYSCTRL_TypeDef)
#define RCU      TAE32_HOST_PERI_CAST(RCU_TypeDef)
#define ADC0     TAE32_HOST_PERI_CAST(ADC_TypeDef)
#define ADC1     TAE32_HOST_PERI_CAST(ADC_TypeDef)
#define ADC2     TAE32_HOST_PERI_CAST(ADC_TypeDef)
#define ADC3     TAE32_HOST_PERI_CAST(ADC_TypeDef)
#define IIR0     TAE32_HOST_PERI_CAST(IIR_TypeDef)
#define IIR1     TAE32_HOST_PERI_CAST(IIR_TypeDef)
#define IIR2     TAE32_HOST_PERI_CAST(IIR_TypeDef)
#define IIR3     TAE32_HOST_PERI_CAST(IIR_TypeDef)
#define IIR4     TAE32_HOST_PERI_CAST(IIR_TypeDef)
#define IIR5     TAE32_HOST_PERI_CAST(IIR_TypeDef)
#define HRPWM    TAE32_HOST_PERI_CAST(HRPWM_TypeDef)
#define TMR0     TAE32_HOST_PERI_CAST(GPTMRx_TypeDef)
#define TMR1     TAE32_HOST_PERI_CAST(GPTMRx_TypeDef)
#define TMR2     TAE32_HOST_PERI_CAST(GPTMRx_TypeDef)
#define TMR9     TAE32_HOST_PERI_CAST(ADTMR_TypeDef)
#define TMR10    TAE32_HOST_PERI_CAST(ADTMR_TypeDef)

static inline void tae32_host_peri_load(const uint8_t *src, uint32_t n)
{
    if (src == NULL || n == 0u) return;
    if (n > TAE32_HOST_PERI_IMAGE_BYTES) n = TAE32_HOST_PERI_IMAGE_BYTES;
    memcpy(tae32_host_peri_image, src, n);
}

static inline void tae32_host_peri_store(uint8_t *dst, uint32_t n)
{
    if (dst == NULL || n == 0u) return;
    if (n > TAE32_HOST_PERI_IMAGE_BYTES) n = TAE32_HOST_PERI_IMAGE_BYTES;
    memcpy(dst, tae32_host_peri_image, n);
}

#endif
