#!/bin/bash
mount /dev/mmcblk0p1 /mount/raspberry
cp kernel.img /mount/raspberry/kernel.img
sync
umount /dev/mmcblk0p1
lsblk -p
