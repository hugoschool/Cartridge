#include "cartridge/hardware/lcd.h"

void gba_lcd_vram_clear(uint16_t color)
{
    uint16_t volatile *VRAM = GBA_VRAM;

    for (uint16_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VRAM[i] = color;
    }
}

void gba_lcd_vram_dpixel(int16_t x, int16_t y, uint16_t color)
{
    uint16_t volatile *VRAM = GBA_VRAM;
    uint16_t size = SCREEN_WIDTH * y;

    size += x;
    VRAM[size] = color;
}

