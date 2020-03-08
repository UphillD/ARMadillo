ARMGNU = arm-none-eabi

AS = $(ARMGNU)-as
GCC = $(ARMGNU)-gcc
LD = $(ARMGNU)-ld
OBJCOPY = $(ARMGNU)-objcopy
OBJDUMP = $(ARMGNU)-objdump

ASMOPS = --warn --fatal-warnings
GCCOPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

all: kernel.img

boot.o : boot.S
	$(AS) $(ASMOPS) boot.S -o boot.o

kernel.o : kernel.c
	$(GCC) $(GCCOPS) -c kernel.c -o kernel.o

kernel.elf : linker.ld boot.o kernel.o
	$(LD) boot.o kernel.o -T linker.ld -o kernel.elf
	$(OBJDUMP) -D kernel.elf > kernel.list

kernel.img : kernel.elf
	$(OBJCOPY) --srec-forceS3 kernel.elf -O srec kernel.srec
	$(OBJCOPY) kernel.elf -O binary kernel.img

clean:
	@rm -f *.o
	@rm -f *.bin
	@rm -f *.hex
	@rm -f *.srec
	@rm -f *.elf
	@rm -f *.list
	@rm -f *.img
