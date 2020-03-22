/*
 * ARMadillo/kernel/sys.S
 *
 * Provides core functionality in assembly.
 */

.section ".text"
.thumb

@ Gets a word from the memory location indicated by r0 and returns it.
.thumb_func
.globl GET32
GET32:
	ldr	r0, [r0]
	bx	lr

@ Puts a word to the memory location indicated by r0.
.thumb_func
.globl PUT32
PUT32:
	str	r1, [r0]
	bx	lr

@ Halts
.thumb_func
.globl halt
halt:
	b	halt
