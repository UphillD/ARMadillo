/*
 * ARMadillo/kernel/intr.S
 *
 * Creates the exception vector and moves it to 0x0000.
 */

.section ".text"

@ Set the exception vector
exception_vector:
	ldr	pc, reset_handler_abs_addr
	ldr	pc, undefined_instruction_handler_abs_addr
	ldr	pc, software_interrupt_handler_abs_addr
	ldr	pc, prefetch_abort_handler_abs_addr
	ldr	pc, data_abort_handler_abs_addr
	nop						@ Unused handler
	ldr	pc, irq_handler_abs_addr
	ldr	pc, fast_irq_handler_abs_addr

reset_handler_abs_addr:			.word reset_handler
undefined_instruction_handler_abs_addr:	.word undefined_instruction_handler
software_interrupt_handler_abs_addr:	.word software_interrupt_handler
prefetch_abort_handler_abs_addr:	.word prefetch_abort_handler
data_abort_handler_abs_addr:		.word data_abort_handler
irq_handler_abs_addr:			.word irq_handler_asm_wrapper
fast_irq_handler_abs_addr:		.word fast_irq_handler

@ Move the exception vector to 0x0000
.globl move_exception_vector
move_exception_vector:
	push	{r4, r5, r6, r7, r8, r9}
	ldr	r0, =exception_vector
	mov	r1, #0x0000
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8}
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8}
	pop	{r4, r5, r6, r7, r8, r9}
	blx	lr

@ Assembly wrapper for the IRQ Handler
irq_handler_asm_wrapper:
	sub	lr, lr, #4		@ Adjust return address
	srsdb	sp!, #0x13		@ Save irq lr and irq spsp to supervisor stack,
					@ save the resulting stack pointer as the
					@ current stack pointer
	cpsid	if, #0x13		@ Switch to supervisor mode with interrupts disabled
	push	{r0 - r3, r12, lr}	@ Push the caller registers to the stack
	and	r1, sp, #4		@ Make sure stack is 8 byte aligned
	sub	sp, sp, r1
	push	{r1}			@ Save the stack adjustment
	bl	irq_handler		@ Call the IRQ handler
	pop	{r1}			@ Get the stack adjustment
	add	sp, sp, r1
	pop	{r0-r3, r12, lr}	@ Pop the caller registers
	rfeia	sp!			@ Load the saved return address and program
					@ state register from before the interrupt
					@ from the stack and return

@ Data abort interrupt handler
data_abort_handler:

	mov	r6, lr
	ldr	r8, [r6, #-8]
	mrc	p15, 0, r4, c5, c0, 0	@ Data / Combined
	mrc	p15, 0, r5, c5, c0, 1	@ Instructions
	mov	sp, #0x00004000

	b	halt
