#include <stdint.h>

extern void main(void);
extern void dinit(void);
extern void dclear(uint16_t color);
extern void dpixel(int16_t x, int16_t y, uint16_t color);

void main(void)
{
    // dinit();
    // dpixel(240, 160, 31);
    dclear(31);
    while (1);
}

struct DISPCNT {
    union {
        uint16_t WORD;
        struct {
            uint16_t MODE      : 2;
            uint16_t BG_MODE   : 1;
            uint16_t DISP_SEL  : 1;
            uint16_t SCRN_DIH  : 12; // todo
        };
    };
};

void dinit(void)
{
    uint8_t volatile *ime = (uint8_t *)0x4000208;
    (*ime) = 0;

    struct DISPCNT volatile *DISPCNT = (struct DISPCNT *)0x0400000;
    DISPCNT->WORD = 0x0403;
    // DISPCNT->MODE = 0b011;
    // DISPCNT->BG_MODE = 0;
}

void dclear(uint16_t color)
{
    uint16_t volatile *VRAM = (uint16_t *)0x06000000;
    for (uint16_t i = 0; i < 240*160; i++) {
        VRAM[i] = color;
    }
}

void dpixel(int16_t x, int16_t y, uint16_t color)
{
    uint16_t volatile *VRAM = (uint16_t *)0x06000000;
    uint16_t size = x * y;
    VRAM[size] = color;
}

//test
