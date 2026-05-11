#include "drivers/screen/screen.h"

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
