/* custom linker script in order to generate a GameBoyAdvance binary */
OUTPUT_FORMAT("elf32-littlearm","elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(kernel_init)

/* address only the cartridge memory area
* @notes :
* - skip the cartridge header
* - other memory area will be cover soon .. */
MEMORY {
    game_pack (rx) : ORIGIN = 0x080000c0, LENGTH = 32M
}

SECTIONS {
    .text : {
        /* Force kernel_init to be loaded first */
        /* For more info, see `info ld` section 3.5.1 */
        /* Can verify the order of symbols / sections with `arm-none-eabi-objdump -D <filename>.elf` */
        KEEP(*(.text.init));

        /* Rest of the code binary */
        KEEP(*(.text.*));
        KEEP(*(.text));
    } > game_pack

    .rodata : {
        /* Define the start of the array pointer */
        __cartridge_drivers_start = .;

        KEEP(*(SORT_BY_NAME(.cartridge.drivers.*)));

        /* Define the end of the array pointer */
        __cartridge_drivers_end = .;

        KEEP(*(.rodata));
    } > game_pack
}

/* Very useful to determine this:
* https://blog.thea.codes/the-most-thoroughly-commented-linker-script/ */
ROM_SIZE = LENGTH(game_pack);
CODE_SIZE = SIZEOF(.text);
RODATA_SIZE = SIZEOF(.rodata);
