#include "cartridge/utils.h"
#include <stdint.h>

uint32_t rom_get_size()
{
    return (uint32_t)&ROM_SIZE;
}

uint32_t code_get_size()
{
    return (uint32_t)&CODE_SIZE;
}

uint32_t const_get_size()
{
    return (uint32_t)&RODATA_SIZE;
}
