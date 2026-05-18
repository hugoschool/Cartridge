#ifndef CARTRIDGE_DRIVER_SCREEN_H_
    #define CARTRIDGE_DRIVER_SCREEN_H_

    #include "utils.h"
    #include <stdint.h>

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

/* Alignment settings for dtext_opt () and dprint_opt () . Combining a vertical
and a horizontal alignment option specifies where a given point (x , y ) should
be relative to the rendered string . */
enum {
    /* Horizontal settings : default in dtext () is DTEXT_LEFT */
    DTEXT_VALIGN_LEFT = 0 ,
    DTEXT_VALIGN_CENTER = 1 ,
    DTEXT_VALIGN_RIGHT = 2 ,
    /* Vertical settings : default in dtext () is DTEXT_TOP */
    DTEXT_HALIGN_TOP = 0 ,
    DTEXT_HALIGN_MIDDLE = 1 ,
    DTEXT_HALIGN_BOTTOM = 2 ,
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

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define VRAM_ADDR (uint16_t *)0x06000000

extern void dinit(void);
extern void dclear(uint16_t color);
extern void dpixel(int16_t x, int16_t y, uint16_t color);
void dchar(int32_t x, int32_t y, uint16_t fg, uint8_t c);
void dchar_opt(int32_t x, int32_t y, uint16_t fg, uint16_t bg, uint8_t c);

/* dtext_opt () : Display a string of text
This function is the core of the text rendering interface */
extern void dtext_opt (
    int32_t x , int32_t y , // Coordinates of the anchor of the rendered string
    uint16_t fg , uint16_t bg , // Text color and background color
    uint8_t halign , // Where x should be relative to the rendered string
    uint8_t valign , // Where y should be relative to the rendered string
    char const * str // String to display
);
/* dtext () : Simple version of dtext_opt () with defaults
Calls dtext_opt () with bg = C_NONE , halign = DTEXT_LEFT and valign = DTEXT_TOP . */
extern void dtext ( int32_t x , int32_t y , uint16_t fg , char const * text );
/* dprint_opt () : Display a formatted string
This function is exactly like dtext_opt () , but accepts printf - like formats with
arguments . */
void dprint_opt (
    int32_t x , int32_t y , // Coordinates of the anchor of the rendered string
    uint16_t fg , uint16_t bg , // Text color and background color
    uint8_t halign , // Where x should be relative to the rendered string
    uint8_t valign , // Where y should be relative to the rendered string
    char const * format , // Printf - like format string to display
    ... // Potential variadic arguments
);
/* dprint () : Simple version of dprint_op () with defaults
Calls dprint_opt () with bg = C_NONE , halign = DTEXT_LEFT and valign = DTEXT_TOP */
extern void dprint ( int x , int y , int fg , char const * format , ...) ;
/* dtext_size () : Get the width and height of rendered text
This function computes the size that the given string would take up if
rendered */
extern void dtext_size (
    int32_t * width , // Rendered width
    int32_t * height , // Rendered height
    char const * str // String to display
);
/* dprint_size () : Get the width and height of rendered formatted string
This function is exactly like dtext_size () , but accepts printf - like formats
with arguments . */
extern void dprint_size (
    int32_t * width , // Rendered width
    int32_t * height , // Rendered height
    char const * format , // Printf - like format string to display
    ... // Potential variadic arguments
);
#endif
