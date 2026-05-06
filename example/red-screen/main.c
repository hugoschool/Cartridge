#include <stdint.h>

extern void main(void);
extern void dinit(void);
extern void dclear(uint16_t color);
extern void dpixel(int16_t x, int16_t y, uint16_t color);

typedef enum color_s {
    TFT_BLACK= 0x000,
    TFT_BLUE = 0xF800,
    TFT_RED = 0x001F,
    TFT_GREEN = 0x07E0,
    TFT_SKYBLUE = 0xFFE0,
    TFT_WHITE = 0xFFFF,
    TFT_PURPLE = 0x780F,
    TFT_CYAN = 0xFDA0,
    TFT_GOLD = 0x867D,
}color_t;

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

//test
