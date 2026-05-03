CC	:=	arm-none-eabi-gcc
OBJCOPY	:=	arm-none-eabi-objcopy
CARTRIDGE	:=	../../cartridge

default:	redscreen.gba

redscreen.elf:	bootstrap.S main.o
	$(CC) -mcpu=arm7tdmi -mlittle-endian -nostdlib -T gba.ld -o $@ $^

main.o:	main.c
	$(CC) -mcpu=arm7tdmi -o $@ -c $^

redscreen.bin:	redscreen.elf
	$(OBJCOPY) -O binary $^ $@

redscreen.gba:	redscreen.bin
	$(CARTRIDGE) header generate -o $@ -b $^

clean:
	$(RM) redscreen.bin
	$(RM) redscreen.elf

fclean:	clean
	$(RM) redscreen.gba
