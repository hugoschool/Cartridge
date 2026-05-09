#include "drivers/screen/screen.h"
#include <stdint.h>

int main(void)
{
    dinit();
    dclear(TFT_WHITE);
    for (uint16_t i = 120; i < 130; i++) {
        for (uint16_t j = 80; j < 90; j++) {
            dpixel(i, j, TFT_GOLD);
        }
    }
    while (1);
    return 0;
}
