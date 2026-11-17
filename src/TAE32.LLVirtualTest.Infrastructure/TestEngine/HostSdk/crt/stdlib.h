/* Minimal freestanding CRT for host LL harness (no Windows SDK required). */
#ifndef TAE32_HOST_CRT_STDLIB_H
#define TAE32_HOST_CRT_STDLIB_H

#include <stddef.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

/* Host harness does not allocate; stubs keep accidental includes compiling. */
static inline void abort(void)
{
    for (;;)
    {
    }
}

static inline void *malloc(size_t size)
{
    (void)size;
    return NULL;
}

static inline void free(void *ptr)
{
    (void)ptr;
}

static inline void *calloc(size_t nmemb, size_t size)
{
    (void)nmemb;
    (void)size;
    return NULL;
}

static inline void *realloc(void *ptr, size_t size)
{
    (void)ptr;
    (void)size;
    return NULL;
}

#endif /* TAE32_HOST_CRT_STDLIB_H */
