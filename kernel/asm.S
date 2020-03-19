/*
 * ARMadillo/kernel/asm.S
 *
 * Provides data putting and getting functions.
 *
 */

.section ".text"
.thumb

@ GET32 Function
@ Gets a word (4B) from the memory location indicated by r0 and returns it.
.thumb_func
.globl GET32
GET32:
	ldr	r0, [r0]
	bx	lr

@ PUT32 Function
@ Puts a word (4B) to the memory location indicated by r0.
.thumb_func
.globl PUT32
PUT32:
	str	r1, [r0]
	bx	lr
