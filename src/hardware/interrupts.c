#include "cartridge/display.h"
#include "cartridge/drivers.h"
#include "cartridge/hardware/keypad.h"
#include <stdint.h>
#include "cartridge/hardware/interrupts.h"

static void gba_intc_handler(void)
{
    for (size_t i = 0; i < KEY_AMOUNT; i++) {
        if (gba_keypad_is_pressed(gba_keypad_callbacks[i].key) == true
            && gba_keypad_callbacks[i].callback != NULL) {
            gba_keypad_callbacks[i].callback();
        }
    }
    GBA_INTC.IF.KEYPAD = 1;
}

static void gba_intc_configure(void)
{
    // Setup the handler
    GBA_INTERRUPTIONS_HANDLER = (volatile uintptr_t *)&gba_intc_handler;

    // Enable IME
    GBA_INTC.IME.DISABLE = 1;

    // Disable all IE interrupts except for the ones needed
    GBA_INTC.IE.word = 0;
    GBA_INTC.IE.KEYPAD = 1;
}

CARTRIDGE_DECLARE_DRIVER(00, gba_intc,
    .name = "INTC",
    .configure = &gba_intc_configure,
);
