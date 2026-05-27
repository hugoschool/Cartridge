.text

.section .text.utils, "x"
.global cpu_get_stack
cpu_get_stack:
    mov r0, sp
    bx lr
