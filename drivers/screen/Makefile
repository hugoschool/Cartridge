CC	:=	arm-none-eabi-gcc
OBJCOPY	:=	arm-none-eabi-objcopy
AR	:=	arm-none-eabi-ar

CPU	:=	arm7tdmi

CPPFLAGS	:=	-I ../../include

libscreen.a:	screen.o
	$(AR) rc $@ $^

screen.o:	screen.c
	$(CC) -mcpu=$(CPU) $(CPPFLAGS) -o $@ -c $^

clean:
	$(RM) screen.o

fclean:	clean
	$(RM) libscreen.a

re:	fclean default

.PHONY:	default	clean fclean re
