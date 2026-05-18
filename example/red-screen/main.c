#include "drivers/screen/screen.h"
#include <stdint.h>

int main(void)
{
    dinit();
    dclear(TFT_RED);
    dchar(120, 80, TFT_BLACK, 'P');
    dchar(128, 80, TFT_BLACK, 'D');
    while (1);
    return 0;
}
