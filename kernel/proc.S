/*
 * ARMadillo/kernel/proc.S
 *
 * Performs context switches.
 */

.section ".text"

@ Removes old thread off CPU and puts on a new one.
.globl switch_to_thread
switch_to_thread:
	@ Save the current thread's state
	push	{lr}		@ Push stack pointer and link register
	push	{sp}
	mrs	r12, cpsr   	@ Get the current program state register
	push	{r0 - r12}    	@ Save all general purpose registers
				@  and program state
	str	sp, [r0]    	@ Store the stack pointer into the
				@  saved_state field of the current process

	@ Restore the new thread's state
	ldr	sp, [r1]    	@ Load the stack pointer of the new process
	ldr	r0, =#(10000)	@ Set Quantum time to 10 ms (10000 us)
	bl	timer_set   	@ reset the timer to go off in another quantum
	pop	{r0 - r12}    	@ restore the general purpose registers
	msr	cpsr_c, r12   	@ Restore the new thread's
				@  program status register
	pop	{lr, pc}    	@ LR receives dummy value, PC receives
				@  the stored LR in order to return properly.
