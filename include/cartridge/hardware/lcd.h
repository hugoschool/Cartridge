#ifndef CARTRIDGE_HARDWARE_LCD_H_
    #define CARTRIDGE_HARDWARE_LCD_H_

    #include "cartridge/utils.h"
    #include <stdint.h>

// Display handling
#define COLOR(r, g, b) 0x0000 | b << 11 | g << 5 | r << 1

#define BUFFER_SIZE 256

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

// Alignment settings for dtext_opt() and dprint_opt().
// Combining a vertical and a horizontal alignment option
// specifies where a given point (x, y) should be relative to the rendered string
enum {
    // Horizontal settings: default in dtext() is DTEXT_LEFT
    DTEXT_VALIGN_LEFT = 0,
    DTEXT_VALIGN_CENTER = 1,
    DTEXT_VALIGN_RIGHT = 2,

    // Vertical settings: default in dtext() is DTEXT_TOP
    DTEXT_HALIGN_TOP = 0,
    DTEXT_HALIGN_MIDDLE = 1,
    DTEXT_HALIGN_BOTTOM = 2,
};

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

// The default screen width / height of the GBA
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define VRAM_ADDR (uint16_t *)0x06000000

#endif
