#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        ((uint8_t *)(dest))[i] = ((uint8_t *)(src))[i];
    }
    return NULL;
}
