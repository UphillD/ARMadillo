![ARMadillo logo](logo.png)

##

![status: working](status-working-green.svg)
![build: passing](build-passing-brightgreen.svg)

A minimal ARM OS for the Raspberry Pi Zero.

This is my personal bonus project for the course "Embedded Systems Design" [ECE1258].

## Table of Contents

1. [Features](#Features)
2. [Demo Console](#Demo-Console)
3. [Requirements](#Requirements)
4. [Installation](#Installation)
5. [Project Tree](#Project-Tree)
6. [References](#References)
7. [Resources](#Resources)
8. [Miscellaneous](#Miscellaneous)

## Features

Currently, it:

* Boots,
* Communicates using the serial port UART0,
* Utilizes peripherals (ARM/64-bit Timer, LED),
* Utilizes the floating point coprocessor,
* Serves interrupts,
* Manages the memory,
* Implements Virtual Memory,
* Performs context switches,
* Utilizes spinlocks and mutex.

## Demo Console

Once the OS is launched and everything is initialized, execution is passed to
a demonstration console that can be accessed through /dev/ttyUSB0.
The demo console accepts a few commands:

	help
		Displays a list of available commands
	intr
		Setups a repeatable IRQ interrupt that blinks the LED light of the Pi once every second.
	proc
		Setups the scheduler, launches a kernel and a user process and switches between them seamlessly.
	lock
		Same as proc, but also utilizes mutex locks.
		Control is still switched continuously between the two processes;
		however, they share a lock, and they sequentially un/lock it.
	fpuo
		Performs a floating point operation using the floating point coprocessor.
		Proof can be found in the kernel.list file that is produced during compilation if one looks for the fpu_mult details.
		Note that separate function must be used to produce the result (fpu_mult in common/stdlib.c),
		otherwise the compiler just precalculates the result.

## Requirements

1. A Raspberry Pi Zero (stock, W or WH model),
2. A USB-to-TTL Serial Cable,
3. A properly formatted SD Card,
4. A Serial Console (dterm, minicom, screen).

## Installation

#### Manual

1. Clone the repository.
2. `cd build`
3. `make`
4. Copy the resulting `kernel.img` to the first partition of your SD Card.

#### Automatic

1. Clone the repository.
2. Plug your SD Card in.
3. `cd scripts`
4. `./makerLoader.sh`

## Project Tree

    $root
    ├ build
    ├ common
    ├ docs
    ├ drivers
    ├ include
    │    ├ common
    │    └ drivers
    ├ kernel
    └ scripts

## References

[ARM Architecture Reference Manual, ARMv7-A and ARMv7-R edition](https://static.docs.arm.com/ddi0406/c/DDI0406C_C_arm_architecture_reference_manual.pdf)

[ARM1176JZF-S Technical Reference Manual, revision r0p7](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0301h/DDI0301H_arm1176jzfs_r0p7_trm.pdf)

[BCM2835 ARM Peripherals](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf)

## Resources

[OSDev.org RaspberryPi Tutorial](https://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C)

[RaspberryPi Zero BareMetal Examples by dwelch67](https://github.com/dwelch67/raspberrypi-zero)

[Building an OS for the RaspberryPi by jsandler18](https://jsandler18.github.io/)

## Miscellaneous

Coding style mostly follows the [linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html).

Shield badges provided by [Shields.IO](https://shields.io/)

[Back to TOC](#Table-of-Contents)
