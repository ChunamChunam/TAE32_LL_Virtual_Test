/* Minimal freestanding CRT for host LL harness (no Windows SDK required). */
#ifndef TAE32_HOST_CRT_STDBOOL_H
#define TAE32_HOST_CRT_STDBOOL_H

#ifndef __cplusplus
#define bool _Bool
#define true 1
#define false 0
#endif

#define __bool_true_false_are_defined 1

#endif /* TAE32_HOST_CRT_STDBOOL_H */
