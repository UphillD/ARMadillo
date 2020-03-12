CPU 	= arm1176jzf-s

ARMGNU	= arm-none-eabi
AS	= $(ARMGNU)-as
CC	= $(ARMGNU)-gcc
LD	= $(ARMGNU)-ld
OBJCOPY	= $(ARMGNU)-objcopy
OBJDUMP	= $(ARMGNU)-objdump

ASFLAGS = -mcpu=$(CPU) -g
CFLAGS	= -mcpu=$(CPU) -Wall -Werror -O2 -nostdlib -nostartfiles \
	-ffreestanding -I ../include

KERNEL_DIR = ../src/kernel
COMMON_DIR = ../src/common
ASM_SRC = $(wildcard $(KERNEL_DIR)/*.S)
ASM_OBJ = $(ASM_SRC:.S=.o)
GCC_SRC = $(wildcard $(KERNEL_DIR)/*.c)
GCC_OBJ = $(GCC_SRC:.c=.o)
COM_SRC = $(wildcard $(COMMON_DIR)/*.c)
COM_OBJ = $(COM_SRC:.c=.o)

all: kernel.img

kernel.elf : linker.ld $(ASM_OBJ) $(GCC_OBJ) $(COM_OBJ)
	$(LD) $(ASM_OBJ) $(GCC_OBJ) $(COM_OBJ) -T linker.ld -o kernel.elf
	$(OBJDUMP) -D kernel.elf > kernel.list

kernel.img : kernel.elf
	$(OBJCOPY) --srec-forceS3 kernel.elf -O srec kernel.srec
	$(OBJCOPY) kernel.elf -O binary kernel.img

clean:
	@rm -f $(ASM_OBJ)
	@rm -f $(GCC_OBJ)
	@rm -f $(COM_OBJ)
	@rm -f *.elf
	@rm -f *.list
	@rm -f *.srec
	@rm -f *.img
