CC	:=	arm-none-eabi-gcc
OBJCOPY	:=	arm-none-eabi-objcopy
CARTRIDGE	:=	../../cartridge

CPU	:=	arm7tdmi

CFLAGS	:=	-Wall -Wextra
CPPFLAGS	:=	-I ../../include
LDFLAGS	:=	-L ../../drivers
LDLIBS	:=	-l:screen/libscreen.a

default:	redscreen.gba

redscreen.elf:	bootstrap.S main.o
	$(CC) -mcpu=$(CPU) -mlittle-endian -nostdlib -T gba.ld -o $@ $^ $(LDFLAGS) $(LDLIBS)

main.o:	main.c
	$(CC) -mcpu=$(CPU) $(CFLAGS) $(CPPFLAGS) -o $@ -c $^

redscreen.bin:	redscreen.elf
	$(OBJCOPY) -O binary $^ $@

redscreen.gba:	redscreen.bin
	$(CARTRIDGE) header generate -o $@ -b $^

clean:
	$(RM) main.o
	$(RM) redscreen.bin
	$(RM) redscreen.elf

fclean:	clean
	$(RM) redscreen.gba

re:	fclean default

.PHONY:	default	clean fclean re
