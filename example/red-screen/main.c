#include "drivers/screen/screen.h"
#include "utils.h"
#include <stdint.h>

int main(uint32_t CPSR, uint32_t IME)
{
    uint32_t stack_addr = cpu_get_stack();

    dinit();
    dclear(TFT_RED);
    dprint_opt(120, 80, TFT_PURPLE, TFT_GREEN, 1, 1, "BAKAAAAAAAA %s", "HUGO");
    while (1);
    return 0;
}
