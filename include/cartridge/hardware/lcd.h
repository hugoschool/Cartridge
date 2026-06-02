#ifndef CARTRIDGE_HARDWARE_LCD_H_
    #define CARTRIDGE_HARDWARE_LCD_H_

    #include "cartridge/utils.h"
    #include <stdint.h>

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
    // DISPGW: Green-swap (undocumented register)
    word_union(DISPGW,
        uint16_t SWAP   :1;     // Enable green SWAP
        uint16_t        :15;    // reserved
    );
    // General LCD Status
    word_union(DISPSTAT,
        uint16_t const VBF  :1; // V - Blank Flag
        uint16_t const HBF  :1; // H - Blank Flag
        uint16_t const VCF  :1; // V - Counter Flag
        uint16_t VBIE       :1; // V - Blank IRQ Enable
        uint16_t HBIE       :1; // H - Blank IRQ Enable
        uint16_t VCIE       :1; // V - Counter IRQ Enable
        uint16_t const      :1; // reserved
        uint16_t const      :1; // reserved
        uint16_t VCSET      :8; // V - Count Setting
    );
    // TODO: only use what's interesting for now, rest later
} MYPACKED(2) GBA_lcd_t;

#define GBA_LCD (*(volatile GBA_lcd_t *)0x04000000)

// Must be uint16_t, not a pointer
#define GBA_VRAM (volatile uint16_t *)0x06000000

extern void gba_lcd_vram_clear(uint16_t color);
extern void gba_lcd_vram_dpixel(int16_t x, int16_t y, uint16_t color);

// Default configuration of DISPCNT
#define DISPCNT_CONFIG 0x0403

// The default screen width / height of the GBA
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#endif
