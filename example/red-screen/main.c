#include "drivers/screen/screen.h"
#include <stdint.h>

int main(void)
{
    dinit();
    dclear(TFT_RED);
    dprint(0, 0, TFT_PURPLE, "BASSEM BASSEM %s", "BASSEM");
    dprint(0, 12, TFT_BLUE, "BASSEM BASSEM %d", 26);
    dprint(0, 24, TFT_GOLD, "BASSEM BASSEM %x", 15);
    dprint(0, 36, TFT_GREEN, "BASSEM BASSEM %p", 0x0);
    while (1);
    return 0;
}
