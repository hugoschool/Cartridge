.text
.global _bootstrap

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
    ldr r0, =stack_pointer_user
    ldr sp, [r0]

    // Calling into our own C main function
    // Passing CPSR as the first argument
    mrs r0, cpsr
    // Passing IME as the second argument
    ldr r1, =ime_addr
    ldr r1, [r1]
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
ime_addr:
    .long 0x04000208
reg_dispcnt_config:
    .word 0x0403
