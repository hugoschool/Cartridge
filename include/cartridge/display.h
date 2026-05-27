#ifndef CARTRIDGE_DISPLAY_H_
    #define CARTRIDGE_DISPLAY_H_

    #include <stddef.h>
    #include <stdint.h>

// Font handling
// ---------------------------------------------------------------------------

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

// Display handling
// ---------------------------------------------------------------------------

// Initializes the entire screen
extern void dinit(void);

// Clears the whole screen with a specified color
extern void dclear(uint16_t color);

// Places a singular pixel on the screen
extern void dpixel(int16_t x, int16_t y, uint16_t color);

// Displays a singular char to the screen with a transparent background
void dchar(int32_t x, int32_t y, uint16_t fg, uint8_t c);
// Displays a singular char to the screen
void dchar_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t c);

// Displays a string to the screen
extern void dtext_opt(
    int32_t x, int32_t y,
    uint16_t fg, uint16_t bg,
    uint8_t halign,
    uint8_t valign,
    char const *str
);

// dtext_opt with default parameters:
// bg = C_NONE, halign = DTEXT_LEFT and valign = DTEXT_TOP
extern void dtext(int32_t x, int32_t y, uint16_t fg, char const *text);

// Similarily as how printf works
void dprint_opt(
    int32_t x, int32_t y,
    uint16_t fg, uint16_t bg,
    uint8_t halign,
    uint8_t valign,
    char const *format,
    ...
);

// dprint_opt with default parameters:
// bg = C_NONE, halign = DTEXT_LEFT and valign = DTEXT_TOP
extern void dprint(int x, int y, int fg, char const *format, ...);

// Get the width and height of rendered text
extern void dtext_size(
    int32_t *width,
    int32_t *height,
    char const *str
);

// Get the width and height of rendered formatted string
extern void dprint_size(
    int32_t *width,
    int32_t *height,
    char const *format,
    ...
);
#endif
