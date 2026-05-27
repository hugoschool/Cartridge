#include "cartridge/hardware/lcd.h"
#include "cartridge/display.h"
#include "cartridge/utils.h"
#include <stdint.h>

void main(void)
{
    uint32_t stack_addr = cpu_get_stack();
    uint32_t rom_size = rom_get_size();
    uint32_t code_size = code_get_size();
    uint32_t const_size = const_get_size();

    dinit();
    dclear(TFT_BLACK);
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
    // dprint_opt(1, 68, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "CPSR: %x", CPSR);
    // dprint_opt(1, 80, TFT_WHITE, TFT_BLACK, DTEXT_HALIGN_TOP, DTEXT_VALIGN_LEFT, "IME: %x", IME);
    while (1);
}
