ARCH	= armv6zk+fp
CPU 	= arm1176jzf-s

# Setup the toolchain.
ARMGNU	= arm-none-eabi
AS	= $(ARMGNU)-as
CC	= $(ARMGNU)-gcc
LD	= $(ARMGNU)-ld
OBJCOPY	= $(ARMGNU)-objcopy
OBJDUMP	= $(ARMGNU)-objdump

# Setup the compiler flags.
ASFLAGS = -mcpu=$(CPU) -mfpu=vfp -march=$(ARCH) 	 	\
	-g -Wall -Werror -Wextra
CFLAGS	= -mcpu=$(CPU) -mfpu=vfp -march=$(ARCH) -mtune=$(CPU)	\
	-g -Wall -Werror -Wextra -O2 -fpic			\
	-nostdlib -nostartfiles -ffreestanding 			\
	-mhard-float -I ../include

# Set the workspace directories.
COMMON_DIR = ../common
DRIVER_DIR = ../drivers
KERNEL_DIR = ../kernel

# Build the source lists.
COM_GCC = $(wildcard $(COMMON_DIR)/*.c)
DRI_ASM = $(wildcard $(DRIVER_DIR)/*.S)
DRI_GCC = $(wildcard $(DRIVER_DIR)/*.c)
KER_ASM = $(wildcard $(KERNEL_DIR)/*.S)
KER_GCC = $(wildcard $(KERNEL_DIR)/*.c)

# Build the object list.
OBJ = $(COM_GCC:.c=.o)
OBJ += $(DRI_ASM:.S=.o)
OBJ += $(DRI_GCC:.c=.o)
OBJ += $(KER_ASM:.S=.o)
OBJ += $(KER_GCC:.c=.o)

all: kernel.img

kernel.elf : linker.ld $(OBJ)
	$(LD) $(OBJ) -T linker.ld -o kernel.elf
	$(OBJDUMP) -D kernel.elf > kernel.list

kernel.img : kernel.elf
	$(OBJCOPY) --srec-forceS3 kernel.elf -O srec kernel.srec
	$(OBJCOPY) kernel.elf -O binary kernel.img

clean:
	@rm -f $(OBJ)
	@rm -f *.elf
	@rm -f *.list
	@rm -f *.srec
	@rm -f *.img
