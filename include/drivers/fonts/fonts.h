#ifndef CARTRIDGE_DRIVER_FONTS_H_
    #define CARTRIDGE_DRIVER_FONTS_H_

    #include <stddef.h>
    #include <stdint.h>

struct gba_font_monospaced_s {
    struct {
        size_t width;
        size_t height;
    } glyph;
    uint8_t *bitmap;
};

struct gba_font_proportional_s {
    struct {
        size_t width;
        size_t height;
    } glyph[128];
    uint8_t *bitmap;
};

enum gba_font_type {
    MONOSPACED,
    PROPORTIONAL
};

typedef struct gba_font_s {
    enum gba_font_type type;
    union {
        struct gba_font_monospaced_s mono;
        struct gba_font_proportional_s prop;
    };
} gba_font_t;

extern const gba_font_t font;

#endif
