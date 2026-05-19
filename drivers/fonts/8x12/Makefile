CC	:=	arm-none-eabi-gcc
OBJCOPY	:=	arm-none-eabi-objcopy
AR	:=	arm-none-eabi-ar

CPU	:=	arm7tdmi

CFLAGS	:=	-Wall -Wextra
CPPFLAGS	:=	-I ../../../include

default:	libfont.a

libfont.a:	font.o
	$(AR) rc $@ $^

font.o:	font.c
	$(CC) -mcpu=$(CPU) $(CFLAGS) $(CPPFLAGS) -o $@ -c $^

clean:
	$(RM) font.o

fclean:	clean
	$(RM) libfont.a

re:	fclean default

.PHONY:	default	clean fclean re
