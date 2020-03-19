#!/bin/bash

# Helper script for compiling the kernel image and moving it to the SD Card.
# Don't sudo it, it will ask for root when it's needed.
# The juggle remains!

# Compile the kernel image
cd ../build
make clean
make

# Unmount the SD Card if it was automatically mounted
sudo umount /dev/mmcblk0p1 &> /dev/null
sudo umount /dev/mmcblk0p2 &> /dev/null

# Create directory /mount/raspberry
sudo mkdir -p /mount/raspberry

# Mount the boot partition of the SD Card to /mount/raspberry
sudo mount /dev/mmcblk0p1 /mount/raspberry

# Copy the kernel image to the SD Card
sudo cp kernel.img /mount/raspberry/kernel.img

# Make sure that the file is written to the SD Card and not in some buffer
sudo sync

# Unmount the SD Card
sudo umount /dev/mmcblk0p1

# Easy way to check if the SD Card is safe to remove
lsblk -p
