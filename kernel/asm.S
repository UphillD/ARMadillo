/*
 * ARMadillo/kernel/asm.S
 *
 * Provides any required miscellaneous functionality in assembly
 *
 */

.section ".text"
.thumb

@ GET32 Function
@ uint32_t GET32 (uint32_t r0)
@ Gets a word (4B) from the memory location indicated by r0 and returns it.
.thumb_func
.globl GET32
GET32:
	ldr r0, [r0]
	bx lr

@ PUT32 Function
@ void GET32 (uint32_t r0, uint32_t r1)
@ Puts a word (4B) to the memory location indicated by r0.
.thumb_func
.globl PUT32
PUT32:
	str r1, [r0]
	bx lr
