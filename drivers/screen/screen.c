#include "drivers/screen/screen.h"
#include "drivers/fonts/fonts.h"
#include <stdarg.h>

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

void dchar_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t c)
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

void dchar(int32_t x, int32_t y, uint16_t fg, uint8_t c)
{
    int32_t width = font.mono.glyph.width;
    int32_t height = font.mono.glyph.height;
    int32_t posy = height * c;
    uint8_t bit = 0;
    uint8_t mask = 0;

    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {
            mask = 1 << (width - 1 - j);
            bit = (font.mono.bitmap[posy + i] & mask) >> (width - 1 - j);
            if (bit) {
                dpixel(x + j, y + i, fg);
            }
        }
    }
}

void dtext_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t halign, uint8_t valign, const char *str)
{
}

void dtext(int32_t x, int32_t y, uint16_t fg, const char *text)
{
    for (int32_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            y += font.mono.glyph.height;
            x -= ((i + 1) * font.mono.glyph.width);
        }
        dchar(x + (i * font.mono.glyph.width), y, fg, text[i]);
    }
}

void dprint_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t halign, uint8_t valign, const char *format, ...)
{}

void dtext_size(int32_t *width, int32_t *height, const char *str)
{}

void updateBufferstr(char *arg, char *buffer, int *count)
{
    for (int j = 0; arg[j] != '\0'; j++) {
        buffer[*count] = arg[j];
        (*count)++;
    }
}

void updateBuffernb(int32_t nb, char *buffer, int *count)
{
    if (nb < 0) {
        buffer[*count] = ('-');
        (*count)++;
        nb = nb * -1;
    }
    if (nb > 9) {
        updateBuffernb(nb / 10, buffer, count);
    }
    buffer[*count] = nb % 10 + '0';
    (*count)++;
}

static char handle_hex_char(int nb)
{
    if (nb == 10)
        return 'a';
    if (nb == 11)
        return 'b';
    if (nb == 12)
        return 'c';
    if (nb == 13)
        return 'd';
    if (nb == 14)
        return 'e';
    if (nb == 15)
        return 'f';
    return nb + '0';
}

void updateBufferhex(uint32_t nb, char *buffer, int *count)
{
    if (nb > 16) {
        updateBufferhex(nb / 16, buffer, count);
    }
    buffer[*count] = handle_hex_char(nb % 16);
    (*count)++;
}

void dprint(int x, int y, int fg, const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = '\0';
    int count = 0;
    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] == 's') {
            char *tempbuff = va_arg(args, char *);
            updateBufferstr(tempbuff, buffer, &count);
            i++;
        } else if (format[i] == '%' && format[i + 1] == 'd') {
            int32_t nbr = va_arg(args, int);
            updateBuffernb(nbr, buffer, &count);
            i++;
        } else if (format[i] == '%' && format[i + 1] == 'x') {
            int32_t nbr = va_arg(args, int);
            updateBufferhex(nbr, buffer, &count);
            i++;
        } else if (format[i] == '%' && format[i + 1] == 'p') {
            void *p = va_arg(args, void *);
            updateBufferhex((uint32_t)p, buffer, &count);
            i++;
        } else {
            buffer[count] = format[i];
            count++;
        }
    }
    va_end(args);
    dtext(x, y, fg, buffer);
}

void dprint_size(int32_t *width, int32_t *height, const char *format, ...)
{}
