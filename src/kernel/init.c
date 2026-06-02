#include "cartridge/display.h"
#include "cartridge/drivers.h"
#include <stdbool.h>

extern int main(void);

// Force loading of gba_intc symbols
extern const cartridge_driver_t __cartridge_driver__gba_intc;

static void kernel_initialize_drivers(void)
{
    __cartridge_driver__gba_intc.configure();

    for (int i = 0; i < CARTRIDGE_DRIVER_COUNT(); i++) {
        cartridge_driver_t *driver = &__cartridge_drivers_start[i];
        if (driver->configure)
            driver->configure();
    }
}

__attribute__((section(".text.init")))
void kernel_init(void)
{
    kernel_initialize_drivers();

    main();

    // Red screen of death
    dclear(TFT_RED);
    while (true) {
        __asm__ volatile("nop");
    }
}
