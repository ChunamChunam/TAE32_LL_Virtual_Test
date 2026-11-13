/* After tae32g58xx.h: remap CMSIS SCS (NVIC/SCB/…) off 0xE000xxxx onto host RAM. */
#ifndef TAE32_LL_HOST_SCS_REMAP_H
#define TAE32_LL_HOST_SCS_REMAP_H

#include <stdint.h>

#ifndef TAE32_HOST_SCS_DEFINED
#include "tae32_ll_host_scs_buf.h"
#endif

#undef ITM
#undef DWT
#undef TPI
#undef CoreDebug
#undef FPU
#undef MPU
#undef NVIC
#undef SCB
#undef SysTick
#undef SCnSCB

#define SCS_BASE      ((uintptr_t)tae32_host_scs)
#define SysTick_BASE  (SCS_BASE + 0x0010UL)
#define NVIC_BASE     (SCS_BASE + 0x0100UL)
#define SCB_BASE      (SCS_BASE + 0x0D00UL)

#define SCnSCB        ((SCnSCB_Type *)SCS_BASE)
#define SysTick       ((SysTick_Type *)SysTick_BASE)
#define NVIC          ((NVIC_Type *)NVIC_BASE)
#define SCB           ((SCB_Type *)SCB_BASE)

#endif
