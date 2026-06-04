#include "cartridge/hardware/interrupts.h"
#include "cartridge/hardware/keypad.h"
#include "cartridge/hardware/lcd.h"
#include "cartridge/display.h"
#include "cartridge/utils.h"
#include <stdint.h>

typedef void (*menu_functions)(void);

int current_menu = 0;

const menu_functions functions[];

static int functions_size()
{
    int i = 0;
    for (; functions[i] != NULL; i++);
    return i;
}

static void display_current_menu()
{
    functions[current_menu]();
}

static void switch_menu()
{
    dclear(TFT_BLACK);
    display_current_menu();
}

static void decrement_menu()
{
    if (current_menu > 0)
        current_menu--;
    switch_menu();
}

static void increment_menu()
{
    if (current_menu != functions_size() - 1)
        current_menu++;
    switch_menu();
}

void gamepak_menu()
{
    uint32_t stack_addr = cpu_get_stack();
    uint32_t rom_size = rom_get_size();
    uint32_t code_size = code_get_size();
    uint32_t const_size = const_get_size();

    dtext_opt(
        SCREEN_WIDTH / 2, 12,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_MIDDLE, DTEXT_VALIGN_CENTER,
        "GAMEPAK"
    );
    dprint_opt(1, 20, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "ROM: %d", rom_size);
    dprint_opt(1, 32, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "Code: %d", code_size);
    dprint_opt(1, 44, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "read-only data: %d", const_size);
    dprint_opt(1, 56, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "stack: %p", stack_addr);
}

void lcd_menu()
{
    dtext_opt(
        SCREEN_WIDTH / 2, 12,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_MIDDLE, DTEXT_VALIGN_CENTER,
        "LCD"
    );

    dprint_opt(
        1, 20,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "DISPCNT: %x", GBA_LCD.DISPCNT.word
    );
    dprint_opt(
        1, 32,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "DISPGW: %x", GBA_LCD.DISPGW.word
    );
    dprint_opt(
        1, 44,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "DISPSTAT: %x", GBA_LCD.DISPSTAT.word
    );
}

void intc_menu()
{
    dtext_opt(
        SCREEN_WIDTH / 2, 12,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_MIDDLE, DTEXT_VALIGN_CENTER,
        "INTC"
    );

    dprint_opt(
        1, 20,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "IE: %x", GBA_INTC.IE.word
    );
    dprint_opt(
        1, 32,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "IF: %x", GBA_INTC.IF.word
    );
    dprint_opt(
        1, 44,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "WAITCNT: %x", GBA_INTC.WAITCNT.word
    );
    dprint_opt(
        1, 56,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "IME: %x", GBA_INTC.IME.word
    );
}

void keypad_menu()
{
    dtext_opt(
        SCREEN_WIDTH / 2, 12,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_MIDDLE, DTEXT_VALIGN_CENTER,
        "KEYPAD"
    );

    dprint_opt(
        1, 20,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
        "KEYINPUT: %x", GBA_KEYPAD.KEYINPUT.word
    );
    bool pressed = false;
    for (int i = 0; i < KEY_AMOUNT; i++) {
        if (gba_keypad_is_pressed(i) == true) {
            pressed = true;
            break;
        }
    }
    if (pressed == false) {
        dprint_opt(
            1, 32,
            TFT_WHITE, TFT_BLACK,
            DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
            "No key pressed for now..."
        );
    } else {
        dprint_opt(
            1, 32,
            TFT_WHITE, TFT_BLACK,
            DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT,
            "Shit was pressed u know"
        );
    }
}

const menu_functions functions[] = {
    &gamepak_menu,
    &lcd_menu,
    &intc_menu,
    &keypad_menu,
    NULL
};

void main(void)
{
    gba_keypad_map(KEY_L, &decrement_menu);
    gba_keypad_map(KEY_R, &increment_menu);

    dclear(TFT_BLACK);
    while (1) {
        display_current_menu();
    }
}
