/* Host SCS backing store — must exist before CMSIS_NVIC_VIRTUAL (device header pulls in core_cm4). */
#ifndef TAE32_LL_HOST_SCS_BUF_H
#define TAE32_LL_HOST_SCS_BUF_H

#include <stdint.h>

#ifndef TAE32_HOST_SCS_DEFINED
#define TAE32_HOST_SCS_DEFINED 1
static uint8_t tae32_host_scs[0x10000];
#endif

#endif
