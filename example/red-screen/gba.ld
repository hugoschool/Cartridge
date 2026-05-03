/* custom linker script in order to generate a GameBoyAdvance binary */
OUTPUT_FORMAT("elf32-littlearm","elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_bootstrap)

/* address only the cartridge memory area
* @notes :
* - skip the cartridge header
* - other memory area will be cover soon .. */
MEMORY {
    game_pack (rx) : ORIGIN = 0x080000c0, LENGTH = 32M
}

SECTIONS {
    .text : {
        /* Force _bootstrap to be loaded first */
        /* For more info, see `info ld` section 3.5.1 */
        /* Can verify the order of symbols / sections with `arm-none-eabi-objdump -D <filename>.elf` */
        _bootstrap = .;

        /* Rest of the code binary */
        KEEP(*(.text));
    } > game_pack
}
