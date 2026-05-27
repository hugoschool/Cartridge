#include "cartridge/hardware/lcd.h"
#include "cartridge/display.h"

extern int main(void);

__attribute__((section(".text.init")))
void kernel_init(void)
{
    dinit();

    main();

    // Red screen of death
    dclear(TFT_RED);
    while (true) {
        __asm__ volatile("nop");
    }
}
