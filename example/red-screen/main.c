#include "drivers/screen/screen.h"
#include <stdint.h>

int main(void)
{
    dinit();
    dclear(TFT_RED);
    dtext(120, 80, TFT_PURPLE, "Tu suce ?");
    while (1);
    return 0;
}
