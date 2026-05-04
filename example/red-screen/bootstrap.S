.text
.global _bootstrap
// Bootstrap code, aggressively request a RED screen
// @notes
// - do not try this code on real hardware unless you want to destroy your
// batteries' life ...
// - this code is located right after the CARTRIDGE header
// - no interruption handler setup ... So, aggressively mask all possible
// interrupt to avoid hardware crash
// - no stack setup, be careful

_bootstrap:
    // make sure the instruction set is ARM and not THUMB
    // see `info as` but this effectively does the same as `.code 32`
    .arm

    // disable hardware interrupts
    // a good explanation of the CPSR register can be found here [1]
    // MRS and MSR instructions allow us to manipulate the CPSR register
    //
    // [1]: https://developer.arm.com/documentation/den0042/0100/ARM-Processor-modes-and-Registers/Registers/Program-Status-Registers
    mrs r0, cpsr
	orr r0, r0, #0x40 // Disabling FIQ
	orr r0, r0, #0xc0 // Disabling IRQ
	msr cpsr, r0

    // set the stack pointer to the user system mode
    ldr sp, =stack_pointer_user

    // screen configuration
    // @note
    // - select the video mode 3 which is configure a basic VRAM
    // - enable the screen display background 2 (as requested with mode 3)
    // @out
    // - r3 -> new display register configuration
    // - r4 -> old display register configuration
    ldr r0, =reg_dispcnt_addr
    ldr r0, [r0]
    ldr r4, [r0]
    ldr r2, =reg_dispcnt_config
    ldr r2, [r2]
    strh r2, [r0]
    ldr r3, [r0]

    // VRAM color fill
    // @note
    // - very, very, very slow VRAM update
    // - color the whole VRAM in RED
    // - screen size (w=240, h=160)
    ldr r0, =vram_addr
    ldr r0, [r0]
    mov r2, #31
    mov r1, #(240*160)

color_loop:
    strh r2, [r0]
    sub r1, #1
    add r0, #2
    cmp r1, #0
    bne color_loop

// Calling into our own C main function
    b main

// ---
// Data area
// ---
.balign 4
stack_pointer_user:
    .long 0x03007F00
vram_addr:
    .long 0x06000000
reg_dispcnt_addr:
    .long 0x04000000
reg_dispcnt_config:
    .word 0x0403
