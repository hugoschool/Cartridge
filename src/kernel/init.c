#include "cartridge/display.h"
#include "cartridge/drivers.h"
#include <stdbool.h>

extern int main(void);

static void kernel_initialize_drivers(void)
{
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
