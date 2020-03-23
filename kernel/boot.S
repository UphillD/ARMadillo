/*
 * ARMadillo/kernel/boot.S
 *
 * The bootloader.
 */

.section ".text.boot"

@ Set the kernel stack size.
@ Currently 4KB.
.equ KERNEL_STACK_SIZE, 4096

@ Boot entry function.
.globl _start
_start:

	@ Setup the stack.
	ldr	sp, =__end
	mov	r4, #(KERNEL_STACK_SIZE)
	add	sp, sp, r4

	@ Clear bss section.
	ldr	r4, =__bss_start
	ldr	r9, =__bss_end
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	mov	r8, #0
	b	2f
1:
	stmia	r4!, {r5 - r8}
2:
	cmp	r4, r9
	blo	1b

	@ Load the atags location on r2
	mov	r2, #0x100
	@ Move execution to kernel_main
	bl	kernel_main

