#include <stdint.h>

extern void main(void);
extern void dinit(void);
extern void dclear(uint16_t color);
extern void dpixel(int16_t x, int16_t y, uint16_t color);

#define COLOR(r, g, b) 0x0000 | b << 11 | g << 5 | r << 1

typedef enum {
    TFT_BLACK = COLOR(0, 0, 0),
    TFT_BLUE = COLOR(0, 0, 31),
    TFT_RED = COLOR(31, 0, 0),
    TFT_GREEN = COLOR(0, 31, 0),
    TFT_WHITE = COLOR(31, 31, 31),
    TFT_PURPLE = COLOR(15, 0, 30),
    TFT_CYAN = COLOR(16, 22, 31),
    TFT_GOLD = COLOR(30, 25, 16),
} color_full_t;

void main(void)
{
    dinit();
    dclear(TFT_WHITE);
    for (uint16_t i = 120; i < 130; i++) {
        for (uint16_t j = 80; j < 90; j++) {
            dpixel(i, j, TFT_GOLD);
        }
    }
    while (1);
}

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

//---
// GBA LCD peripheral. Refer to:
// "GBATEK : LCD I/O Video Controller"
//---
typedef struct {
    // I/O configuraton
    word_union(DISPCNT,
        uint16_t BG_MODE     :2; // Video Mode
        uint16_t             :1; // reserved
        uint16_t DFS         :1; // Display Frame Select
        uint16_t HBIF        :1; // H-Blank Interval Free
        uint16_t OCVM        :1; // OBJ Character VRAM Mapping
        uint16_t FB          :1; // Force Blank
        uint16_t BG0         :1; // Enable Screen Display Background 0
        uint16_t BG1         :1; // Enable Screen Display Background 1
        uint16_t BG2         :1; // Enable Screen Display Background 2
        uint16_t BG3         :1; // Enable Screen Display Background 3
        uint16_t OBJ         :1; // Enable Screen Display OBJ
        uint16_t WDF0        :1; // Window Display Flag 0
        uint16_t WDF1        :1; // Window Display Flag 1
        uint16_t WDFOBJ      :1; // Window Display Flag OBJ
    );
    // TODO: only use what's interesting for now, rest later
} MYPACKED(2) GBA_lcd_t;

#define GBA_LCD (*(volatile GBA_lcd_t *)0x04000000)

// Default configuration of DISPCNT
#define DISPCNT_CONFIG 0x0403

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define VRAM_ADDR (uint16_t *)0x06000000

void dinit(void)
{
    GBA_LCD.DISPCNT.word = DISPCNT_CONFIG;
}

void dclear(uint16_t color)
{
    uint16_t volatile *VRAM = VRAM_ADDR;

    for (uint16_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VRAM[i] = color;
    }
}

void dpixel(int16_t x, int16_t y, uint16_t color)
{
    uint16_t volatile *VRAM = VRAM_ADDR;
    uint16_t size = SCREEN_WIDTH * y;

    size += x;
    VRAM[size - 1] = color;
}
