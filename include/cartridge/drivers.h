#ifndef CARTRIDGE_DRIVERS_H_
    #define CARTRIDGE_DRIVERS_H_

typedef struct {
    char const *name;
    void (*configure)(void);
} cartridge_driver_t;

#define CARTRIDGE_DECLARE_DRIVER(level, name, ...) \
    __attribute__((unused)) \
    __attribute__((section((".cartridge.drivers." #level "." #name)))) \
    static const cartridge_driver_t __cartridge_driver__##name = { \
        __VA_ARGS__ \
    }

extern cartridge_driver_t __cartridge_drivers_start[];
extern cartridge_driver_t __cartridge_drivers_end[];

#define CARTRIDGE_DRIVER_COUNT() ((cartridge_driver_t *)&__cartridge_drivers_end - (cartridge_driver_t *)&__cartridge_drivers_start)

#endif
