ROOT_DIR	:=	..

CC	:=	arm-none-eabi-gcc
AR	:=	arm-none-eabi-ar
CPU	:=	arm7tdmi

CFLAGS	:=	-Wall -Wextra
CPPFLAGS	:=	-I $(ROOT_DIR)/include

# Kernel
KERNEL_ASM_SRC	:=	kernel/bootstrap.S

# Display
DISPLAY_SRC	:=	display/font.c \
				display/screen.c

# Utils
UTILS_SRC	:=	utils/utils.c

OBJ	:=	$(KERNEL_ASM_SRC:.S=.o) \
		$(DISPLAY_SRC:.c=.o) \
		$(UTILS_SRC:.c=.o)

default:	libkernel.a

libkernel.a:	$(OBJ)
	$(AR) rc $@ $^

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) libkernel.a

re:	fclean default

.PHONY:	default	clean fclean re
