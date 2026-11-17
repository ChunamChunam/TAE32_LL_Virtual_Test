/* Minimal freestanding CRT for host LL harness (no Windows SDK required). */
#ifndef TAE32_HOST_CRT_STDDEF_H
#define TAE32_HOST_CRT_STDDEF_H

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

typedef unsigned long long size_t;
typedef long long ptrdiff_t;

#define offsetof(type, member) ((size_t)&(((type *)0)->member))

#endif /* TAE32_HOST_CRT_STDDEF_H */
