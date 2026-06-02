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
    // Screen needs to be cleared first
    dclear(TFT_BLACK);
    functions[current_menu]();
}

static void decrement_menu()
{
    if (current_menu > 0)
        current_menu--;
    display_current_menu();
}

static void increment_menu()
{
    if (current_menu != functions_size() - 1)
        current_menu++;
    display_current_menu();
}

void welcome_menu()
{
    uint32_t stack_addr = cpu_get_stack();
    uint32_t rom_size = rom_get_size();
    uint32_t code_size = code_get_size();
    uint32_t const_size = const_get_size();

    dtext_opt(
        SCREEN_WIDTH / 2, 12,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_MIDDLE, DTEXT_VALIGN_CENTER,
        "Welcome!"
    );
    dprint_opt(1, 20, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "ROM: %d", rom_size);
    dprint_opt(1, 32, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "Code: %d", code_size);
    dprint_opt(1, 44, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "read-only data: %d", const_size);
    dprint_opt(1, 56, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "stack: %p", stack_addr);
}

void example2_menu()
{
    dtext_opt(
        SCREEN_WIDTH / 2, 12,
        TFT_WHITE, TFT_BLACK,
        DTEXT_HALIGN_MIDDLE, DTEXT_VALIGN_CENTER,
        "Nothing to see here..."
    );
}

const menu_functions functions[] = {
    &welcome_menu,
    &example2_menu,
    NULL
};

void main(void)
{
    gba_keypad_map(KEY_L, &decrement_menu);
    gba_keypad_map(KEY_R, &increment_menu);

    display_current_menu();
    while (1);
}
