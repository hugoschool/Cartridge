#include "drivers/screen/screen.h"
#include <stdint.h>

int main(void)
{
    dinit();
    dclear(TFT_RED);
    dprint_opt(120, 80, TFT_PURPLE, TFT_GREEN, 1, 1, "BAKAAAAAAAA %s", "HUGO");
    while (1);
    return 0;
}
