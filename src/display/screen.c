#include "cartridge/hardware/lcd.h"
#include "cartridge/display.h"
#include <stdarg.h>

void dclear(uint16_t color)
{
    gba_lcd_vram_clear(color);
}

void dpixel(int16_t x, int16_t y, uint16_t color)
{
    gba_lcd_vram_dpixel(x, y, color);
}

void dchar_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t c)
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

uint32_t my_strlen(const char *s)
{
    uint32_t size = 0;

    for (; s[size] != '\0'; size++) {
    }
    return size;
}

void dtext_size(int32_t *width, int32_t *height, const char *str)
{
    (*width) = font.mono.glyph.width * my_strlen(str);
    (*height) = font.mono.glyph.height;
}

void dtext_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t halign, uint8_t valign, const char *str)
{
    uint32_t width = font.mono.glyph.width;
    uint32_t height = font.mono.glyph.height;
    int32_t hlen = 0;
    int32_t vlen = 0;
    dtext_size(&hlen, &vlen, str);

    if (valign == DTEXT_VALIGN_RIGHT) {
        x -= hlen;
    } else if (valign == DTEXT_VALIGN_CENTER) {
        x -= hlen/2;
    }

    if (halign == DTEXT_HALIGN_BOTTOM)
        y -= vlen;
    else if (halign == DTEXT_HALIGN_MIDDLE)
        y -= vlen/2;

    for (int32_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            y += height;
            x -= ((i + 1) * width);
        }
        dchar_opt(x + (i * width), y, fg, bg, str[i]);
    }
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

static void dprint_update_buffer_str(char *arg, char *buffer, int *count)
{
    for (int j = 0; arg[j] != '\0'; j++) {
        buffer[*count] = arg[j];
        (*count)++;
    }
}

static void dprint_update_buffer_nb(int32_t nb, char *buffer, int *count)
{
    if (nb < 0) {
        buffer[*count] = ('-');
        (*count)++;
        nb = nb * -1;
    }
    if (nb > 9) {
        dprint_update_buffer_nb(nb / 10, buffer, count);
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

static void dprint_update_buffer_hex(uint32_t nb, char *buffer, int *count)
{
    if (nb > 15) {
        dprint_update_buffer_hex(nb / 16, buffer, count);
    }
    buffer[*count] = handle_hex_char(nb % 16);
    (*count)++;
}

static void dvsprint_opt(char *buffer, const char *format, va_list *args)
{
    int count = 0;

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] == 's') {
            char *tempbuff = va_arg(*args, char *);
            dprint_update_buffer_str(tempbuff, buffer, &count);
            i++;
        } else if (format[i] == '%' && format[i + 1] == 'd') {
            int32_t nbr = va_arg(*args, int);
            dprint_update_buffer_nb(nbr, buffer, &count);
            i++;
        } else if (format[i] == '%' && format[i + 1] == 'x') {
            uint32_t nbr = va_arg(*args, int);
            dprint_update_buffer_hex(nbr, buffer, &count);
            i++;
        } else if (format[i] == '%' && format[i + 1] == 'p') {
            void *p = va_arg(*args, void *);
            dprint_update_buffer_hex((uint32_t)p, buffer, &count);
            i++;
        } else {
            buffer[count] = format[i];
            count++;
        }
    }
}

static void dvprint_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t halign, uint8_t valign, const char *format, va_list *args)
{
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = '\0';
    dvsprint_opt(buffer, format, args);
    dtext_opt(x, y, fg, bg, halign, valign, buffer);
}

void dprint_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t halign, uint8_t valign, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    dvprint_opt(x, y, fg, bg, halign, valign, format, &args);
    va_end(args);
}

void dprint(int x, int y, int fg, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    dvprint_opt(x, y, fg, TFT_WHITE, DTEXT_VALIGN_LEFT, DTEXT_HALIGN_TOP, format, &args);
    va_end(args);
}

void dprint_size(int32_t *width, int32_t *height, const char *format, ...)
{
    va_list args;

    char buffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = '\0';

    va_start(args, format);
    dvsprint_opt(buffer, format, &args);
    va_end(args);

    dtext_size(width, height, buffer);
}
