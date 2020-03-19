/*
 * ARMadillo/drivers/fpu.S
 *
 * Initializes the floating point coprocessor.
 *
 */

.section ".text"

.globl fpu_init
fpu_init:
	mrc	p15, 0, r0, c1, c0, 2
	orr	r0, r0, #0x300000	@ Single Precision
	orr	r0, r0, #0xC00000	@ Double Precision
	mcr	p15, 0, r0, c1, c0, 2
	mov	r0, #0x40000000
	fmxr	fpexc, r0
	bx	lr
