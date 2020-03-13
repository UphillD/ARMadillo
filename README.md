# ARMadillo

![status: work in progress](https://img.shields.io/badge/status-work%20in%20progress-orange)
![build: passing](https://img.shields.io/badge/build-passing-green)

A minimal ARM OS for the Raspberry Pi Zero.

### Features

Currently, it:

* Boots
* Communicates using the serial port UART0
* Utilizes some peripherals (ARM Timer, 64-bit Timer, LED light)
* Supports IRQ interrupts
* Manages the memory


### Essential Reading

[ARM Architecture Reference Manual, ARMv7-A and ARMv7-R edition](https://static.docs.arm.com/ddi0406/c/DDI0406C_C_arm_architecture_reference_manual.pdf)

[ARM1176JZF-S Technical Reference Manual, revision r0p7](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0301h/DDI0301H_arm1176jzfs_r0p7_trm.pdf)

[BCM2835 ARM Peripherals](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf)
