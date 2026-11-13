/* Re-apply SCS/NVIC remap after tae32g58xx.h (device headers may restore CM4 absolute bases). */
#ifndef TAE32_LL_HOST_SCS_REMAP_TAIL_H
#define TAE32_LL_HOST_SCS_REMAP_TAIL_H

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
