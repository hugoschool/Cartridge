#ifndef CARTRIDGE_HARDWARE_KEYPAD_H_
    #define CARTRIDGE_HARDWARE_KEYPAD_H_

    #include "cartridge/utils.h"
    #include <stdbool.h>
    #include <stdint.h>

typedef enum {
    // Order is preserved with the KEYINPUT and KEYCNT
    KEY_A       = 0,
    KEY_B       = 1,
    KEY_SELECT  = 2,
    KEY_START   = 3,
    KEY_RIGHT   = 4,
    KEY_LEFT    = 5,
    KEY_UP      = 6,
    KEY_DOWN    = 7,
    KEY_R       = 8,
    KEY_L       = 9,
} key_t;

#define KEY_AMOUNT 10

typedef void (*gba_keypad_callback_func)(void);

struct gba_keypad_callback_s {
    key_t key;
    gba_keypad_callback_func callback;
};

extern struct gba_keypad_callback_s gba_keypad_callbacks[];

extern int gba_keypad_map(key_t key, gba_keypad_callback_func callback);
extern bool gba_keypad_is_pressed(key_t key);

typedef struct {
    word_union(KEYINPUT,
        // 0 = pressed, 1 = released
        uint16_t const A : 1;             // A button
        uint16_t const B : 1;             // B button
        uint16_t const SELECT : 1;        // Select button
        uint16_t const START : 1;         // Start button
        uint16_t const RIGHT : 1;         // Right button
        uint16_t const LEFT : 1;          // Left button
        uint16_t const UP : 1;            // Up button
        uint16_t const DOWN : 1;          // Down button
        uint16_t const R : 1;             // R button
        uint16_t const L : 1;             // L button
        uint16_t const   : 6;             // Unused
    );
    word_union(KEYCNT,
        // 0 = ignore, 1 = enable
        uint16_t A : 1;             // A button
        uint16_t B : 1;             // B button
        uint16_t SELECT : 1;        // Select button
        uint16_t START : 1;         // Start button
        uint16_t RIGHT : 1;         // Right button
        uint16_t LEFT : 1;          // Left button
        uint16_t UP : 1;            // Up button
        uint16_t DOWN : 1;          // Down button
        uint16_t R : 1;             // R button
        uint16_t L : 1;             // L button
        uint16_t   : 4;             // Unused
        uint16_t IRQ_ENABLE : 1;    // IRQ enable (0 = disable, 1 = enable)
        uint16_t IRQ_COND : 1;      // IRQ condition (0 = OR, 1 = AND)
    );
} MYPACKED(2) GBA_keypad_t;

#define GBA_KEYPAD (*(volatile GBA_keypad_t *)0x04000130)

#endif
