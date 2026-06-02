#include "cartridge/display.h"
#include "cartridge/drivers.h"
#include <stdint.h>
#include "cartridge/hardware/interrupts.h"

static void gba_intc_handler(void)
{
    dclear(TFT_RED);
    while (1) {}
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
