ROOT_DIR	:=	../..

CC	:=	arm-none-eabi-gcc
OBJCOPY	:=	arm-none-eabi-objcopy
CARTRIDGE	:=	$(ROOT_DIR)/cartridge

CPU	:=	arm7tdmi

# Remove warnings about the main function, see bootstrap.S
CFLAGS	:=	-Wall -Wextra -Wno-main
CPPFLAGS	:=	-I $(ROOT_DIR)/include

LIBKERNEL	:=	libkernel.a

LDFLAGS	:=	-L $(ROOT_DIR)/src
LDLIBS	:=	-l:$(LIBKERNEL)

default:	redscreen.gba

redscreen.elf:	main.o $(ROOT_DIR)/src/$(LIBKERNEL)
	$(CC) -mcpu=$(CPU) -mlittle-endian -nostdlib -T $(ROOT_DIR)/src/gba.ld -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(ROOT_DIR)/src/$(LIBKERNEL):
	$(MAKE) -C $(ROOT_DIR)/src $(LIBKERNEL)

main.o:	main.c
	$(CC) -mcpu=$(CPU) $(CFLAGS) $(CPPFLAGS) -o $@ -c $^ $(LDFLAGS) $(LDLIBS)

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
