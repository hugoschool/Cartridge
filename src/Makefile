ROOT_DIR	:=	..

CC	:=	arm-none-eabi-gcc
AR	:=	arm-none-eabi-ar
CPU	:=	arm7tdmi

CFLAGS	:=	-Wall -Wextra
CPPFLAGS	:=	-I $(ROOT_DIR)/include

# Kernel
KERNEL_SRC	:=	kernel/init.c

# Hardware
HARDWARE_LCD_SRC	:=	hardware/lcd.c \
						hardware/interrupts.c \
						hardware/keypad.c

# Display
DISPLAY_SRC	:=	display/font.c \
				display/screen.c

# Utils
UTILS_SRC	:=	utils/utils.c \
				utils/memcpy.c
UTILS_ASM_SRC	:=	utils/cpu_get_stack.S

OBJ	:=	$(KERNEL_SRC:.c=.o) \
		$(HARDWARE_LCD_SRC:.c=.o) \
		$(DISPLAY_SRC:.c=.o) \
		$(UTILS_SRC:.c=.o) \
		$(UTILS_ASM_SRC:.S=.o)

default:	libkernel.a

libkernel.a:	$(OBJ)
	$(AR) rc $@ $^

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) libkernel.a

re:	fclean default

.PHONY:	default	clean fclean re
