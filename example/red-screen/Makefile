CC	:=	arm-none-eabi-gcc
OBJCOPY	:=	arm-none-eabi-objcopy
CARTRIDGE	:=	../../cartridge
CPU	:=	arm7tdmi

default:	redscreen.gba

redscreen.elf:	bootstrap.S main.o
	$(CC) -Wl,-Map=redscreen.map -mcpu=$(CPU) -mlittle-endian -nostdlib -T gba.ld -o $@ $^

main.o:	main.c
	$(CC) -mcpu=$(CPU) -o $@ -c $^

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
