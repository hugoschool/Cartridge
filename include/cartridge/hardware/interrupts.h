#ifndef CARTRIDGE_HARDWARE_INTERRUPTS_H_
    #define CARTRIDGE_HARDWARE_INTERRUPTS_H_

    #include "cartridge/utils.h"
    #include <stdint.h>

typedef struct {
    word_union(IE,
        uint16_t LCD_V : 1;     // LCD V-Blank
        uint16_t LCD_H : 1;     // LCD H-Blank
        uint16_t LCD_VC : 1;    // LCD V-Counter Match
        uint16_t TIMER0 : 1;    // Timer 0 Overflow
        uint16_t TIMER1 : 1;    // Timer 1 Overflow
        uint16_t TIMER2 : 1;    // Timer 2 Overflow
        uint16_t TIMER3 : 1;    // Timer 3 Overflow
        uint16_t SERIAL : 1;    // Serial Communication
        uint16_t DMA0 : 1;      // DMA 0
        uint16_t DMA1 : 1;      // DMA 1
        uint16_t DMA2 : 1;      // DMA 2
        uint16_t DMA3 : 1;      // DMA 3
        uint16_t KEYPAD : 1;    // Keypad
        uint16_t GAMEPAK : 1;   // Game Pak
        uint16_t : 2;           // Unused
    );
    word_union(IF,
        uint16_t LCD_V : 1;     // LCD V-Blank
        uint16_t LCD_H : 1;     // LCD H-Blank
        uint16_t LCD_VC : 1;    // LCD V-Counter Match
        uint16_t TIMER0 : 1;    // Timer 0 Overflow
        uint16_t TIMER1 : 1;    // Timer 1 Overflow
        uint16_t TIMER2 : 1;    // Timer 2 Overflow
        uint16_t TIMER3 : 1;    // Timer 3 Overflow
        uint16_t SERIAL : 1;    // Serial Communication
        uint16_t DMA0 : 1;      // DMA 0
        uint16_t DMA1 : 1;      // DMA 1
        uint16_t DMA2 : 1;      // DMA 2
        uint16_t DMA3 : 1;      // DMA 3
        uint16_t KEYPAD : 1;    // Keypad
        uint16_t GAMEPAK : 1;   // Game Pak
        uint16_t : 2;           // Unused
    );
    word_union(WAITCNT,
        uint32_t SRAM : 2;          // SRAM Wait Control
        uint32_t WAIT0_FIRST : 2;   // Wait State 0 First Access
        uint32_t WAIT0_SECOND : 1;  // Wait State 0 Second Access
        uint32_t WAIT1_FIRST : 2;   // Wait State 1 First Access
        uint32_t WAIT1_SECOND : 1;  // Wait State 1 Second Access
        uint32_t WAIT2_FIRST : 2;   // Wait State 2 First Access
        uint32_t WAIT2_SECOND : 1;  // Wait State 2 Second Access
        uint32_t PHI : 2;           // PHI Terminal Output
        uint32_t : 1;               // Unused
        uint32_t PREFETCH : 1;      // Game Pak Prefetch Buffer
        uint32_t TYPE_FLAG : 1;     // Game Pak Type Flag
        uint32_t : 1;               // Unused
    );
    word_union(IME,
        uint32_t DISABLE : 1;    // Disable all interrupts
        uint32_t : 31;           // Unused
    );
} MYPACKED(2) GBA_interrupts_t;

#define GBA_INTC (*(volatile GBA_interrupts_t *)0x04000200)
#define GBA_INTERRUPTIONS_HANDLER (*(volatile uintptr_t **)0x03FFFFFC)

#endif
