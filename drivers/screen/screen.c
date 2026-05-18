#include "drivers/screen/screen.h"
#include "drivers/fonts/fonts.h"

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
    VRAM[size] = color;
}

void dchar(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t c)
{
    int32_t width = font.mono.glyph.width;
    int32_t height = font.mono.glyph.height;
    int32_t posx = 0;
    int32_t posy = height * c;
    uint8_t bit = 0;
    uint8_t mask = 0;

    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {
            mask = 1 << (width - 1 - j);
            bit = (font.mono.bitmap[posy + i] & mask) >> (width - 1 - j);
            if (bit) {
                dpixel(x + j, y + i, fg);
            } else {
                dpixel(x + j, y + i, bg);
            }
        }
    }
}

void dtext_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t halign, uint8_t valign, const char *str)
{
}

void dtext(int32_t x, int32_t y, uint16_t fg, const char *text)
{}

void dprint_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t halign, uint8_t valign, const char *format, ...)
{}

void dtext_size(int32_t *width, int32_t *height, const char *str)
{}

void dprint(int x, int y, int fg, const char *format, ...)
{}

void dprint_size(int32_t *width, int32_t *height, const char *format, ...)
{}
