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

//useless for now
struct DISPCNT {
    union {
        uint16_t WORD;
        struct {
            uint16_t MODE      : 2;
            uint16_t BG_MODE   : 1;
            uint16_t DISP_SEL  : 1;
            uint16_t SCRN_DIH  : 12; // todo
        };
    };
};

void dinit(void)
{
    uint16_t volatile *DISPCNT = (uint16_t *)0x04000000;
    *DISPCNT = 0x0403;
}

void dclear(uint16_t color)
{
    uint16_t volatile *VRAM = (uint16_t *)0x06000000;
    for (uint16_t i = 0; i < 240*160; i++) {
        VRAM[i] = color;
    }
}

void dpixel(int16_t x, int16_t y, uint16_t color)
{
    uint16_t volatile *VRAM = (uint16_t *)0x06000000;
    uint16_t size = 240 * y;
    size += x;
    VRAM[size - 1] = color;
}
