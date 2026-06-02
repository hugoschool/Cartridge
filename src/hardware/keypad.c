#include "cartridge/hardware/keypad.h"
#include "cartridge/drivers.h"

struct gba_keypad_callback_s gba_keypad_callbacks[] = {
    {.key = KEY_A, .callback = NULL},
    {.key = KEY_B, .callback = NULL},
    {.key = KEY_SELECT, .callback = NULL},
    {.key = KEY_START, .callback = NULL},
    {.key = KEY_RIGHT, .callback = NULL},
    {.key = KEY_LEFT, .callback = NULL},
    {.key = KEY_UP, .callback = NULL},
    {.key = KEY_DOWN, .callback = NULL},
    {.key = KEY_R, .callback = NULL},
    {.key = KEY_L, .callback = NULL},
};

int gba_keypad_map(key_t key, gba_keypad_callback_func callback)
{
    for (size_t i = 0; i < KEY_AMOUNT; i++) {
        if (gba_keypad_callbacks[i].key == key) {
            gba_keypad_callbacks[i].callback = callback;
            return 0;
        }
    }
    return -1;
}

bool gba_keypad_is_pressed(key_t key)
{
    // Ouch, definitely can be improved... don't really want to for now though.
    switch (key) {
        case KEY_A:         return GBA_KEYPAD.KEYINPUT.A == 0;
        case KEY_B:         return GBA_KEYPAD.KEYINPUT.B == 0;
        case KEY_SELECT:    return GBA_KEYPAD.KEYINPUT.SELECT == 0;
        case KEY_START:     return GBA_KEYPAD.KEYINPUT.START == 0;
        case KEY_RIGHT:     return GBA_KEYPAD.KEYINPUT.RIGHT == 0;
        case KEY_LEFT:      return GBA_KEYPAD.KEYINPUT.LEFT == 0;
        case KEY_UP:        return GBA_KEYPAD.KEYINPUT.UP == 0;
        case KEY_DOWN:      return GBA_KEYPAD.KEYINPUT.DOWN == 0;
        case KEY_R:         return GBA_KEYPAD.KEYINPUT.R == 0;
        case KEY_L:         return GBA_KEYPAD.KEYINPUT.L == 0;
    }
    return false;
}

static void gba_keypad_configure(void)
{
    // Enable KEYCNT
    GBA_KEYPAD.KEYCNT.word = 0;
    GBA_KEYPAD.KEYCNT.R = 1;
    GBA_KEYPAD.KEYCNT.L = 1;
    GBA_KEYPAD.KEYCNT.IRQ_ENABLE = 1;
}

CARTRIDGE_DECLARE_DRIVER(02, gba_keypad,
    .name = "Keypad",
    .configure = &gba_keypad_configure,
);
