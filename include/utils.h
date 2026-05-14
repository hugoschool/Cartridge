#ifndef CARTRIDGE_UTIL_H_
    #define CARTRIDGE_UTIL_H_

    #include <stdint.h>

/* Packed structures. I require explicit alignment because if it's unspecified,
   GCC cannot optimize access size, and reads to memory-mapped I/O with invalid
   access sizes silently fail - honestly you don't want this to happen */
#define MYPACKED(x)     __attribute__((packed, aligned(x)))

/* Giving a type to padding bytes is misguiding, let's hide it in a macro */
#define pad_nam2(c) _ ## c
#define pad_name(c) pad_nam2(c)
#define pad(bytes) uint8_t pad_name(__COUNTER__)[bytes]

/* word_union() - union between an uint16_t 'word' element and a bit field */
#define word_union(name, fields)    \
    union {                           \
        uint16_t word;                  \
        struct { fields } MYPACKED(2);  \
    } MYPACKED(2) name

extern uint32_t cpu_get_stack();

#endif
