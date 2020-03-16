![ARMadillo logo](logo.png)

##

![status: work in progress](https://img.shields.io/badge/status-work%20in%20progress-orange)
![build: passing](https://img.shields.io/badge/build-passing-green)

A minimal ARM OS for the Raspberry Pi Zero.

## Features

Currently, it:

* Boots
* Communicates using the serial port UART0
* Utilizes some peripherals (ARM Timer, 64-bit Timer, LED light)
* Utilizes the floating point coprocessor
* Implements IRQ interrupts
* Manages the memory
* Performs context switches
* Utilizes spinlocks and mutex

## Requirements

1. A Raspberry Pi Zero (stock, W or WH model).
2. A USB-to-TTL Serial Cable
3. A properly formatted SD Card
4. A Serial Console (dterm, minicom, screen)

## Installation

1. Clone the repository
2. `cd build`
3. `make`
4. Copy the resulting `kernel.img` to the first partition of your SD Card

## Essential Reading

[ARM Architecture Reference Manual, ARMv7-A and ARMv7-R edition](https://static.docs.arm.com/ddi0406/c/DDI0406C_C_arm_architecture_reference_manual.pdf)

[ARM1176JZF-S Technical Reference Manual, revision r0p7](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0301h/DDI0301H_arm1176jzfs_r0p7_trm.pdf)

[BCM2835 ARM Peripherals](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf)
