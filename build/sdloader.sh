#!/bin/bash

# Unmount the SD Card if it was automatically mounted
umount /dev/mmcblk0p1
umount /dev/mmcblk0p2

# Create directory /mount/raspberry
mkdir -p /mount/raspberry

# Mount the boot partition of the SD Card to /mount/raspberry
mount /dev/mmcblk0p1 /mount/raspberry

# Copy the kernel image to the SD Card
cp kernel.img /mount/raspberry/kernel.img

# Make sure that the file is written to the SD Card and not in some buffer
sync

# Unmount the SD Card
umount /dev/mmcblk0p1

# Easy way to check if the SD Card is safe to remove
lsblk -p
