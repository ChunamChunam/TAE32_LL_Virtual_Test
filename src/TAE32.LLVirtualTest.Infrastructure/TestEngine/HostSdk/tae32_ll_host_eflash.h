/* Backing store for LL_EFLASH_IsSize128KB chip-size mode (SDK uses abs. 0x40023048). Patched in HostHarnessPointerFix. */
#ifndef TAE32_LL_HOST_EFLASH_H
#define TAE32_LL_HOST_EFLASH_H

#include <stdint.h>

static volatile uint32_t tae32_host_eflash_chip_size_mode;

#endif
