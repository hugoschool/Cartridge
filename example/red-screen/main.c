#include "drivers/screen/screen.h"
#include <stdint.h>

int main(void)
{
    dinit();
    dclear(TFT_RED);
    dchar(120, 80, TFT_BLACK, TFT_WHITE, 'P');
    dchar(128, 80, TFT_BLACK, TFT_WHITE, 'D');
    dchar(136, 80, TFT_BLACK, TFT_WHITE, 'F');
    while (1);
    return 0;
}
