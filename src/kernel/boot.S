.section ".text.boot"

// Boot entry function
.globl _start
_start:
	// Set stack pointer to 0x8000
	//mov sp, #0x8000

	ldr pc, reset_handler
	ldr pc, undefined_handler
	ldr pc, swi_handler
	ldr pc, prefetch_handler
	ldr pc, data_handler
	ldr pc, unused_handler
	ldr pc, irq_handler
	ldr pc, fiq_handler

reset_handler:		.word reset
undefined_handler:	.word halt
swi_handler:		.word halt
prefetch_handler:	.word halt
data_handler:		.word halt
unused_handler:		.word halt
irq_handler:		.word irq
fiq_handler:		.word halt

reset:
	mov r0, #0x8000
	mov r1, #0x0000
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

	// (PSR_IRQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
	mov r0, #0xD2
	msr cpsr_c, r0
	mov sp, #0x8000

	// (PSR_FIQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
	mov r0, #0xD1
	msr cpsr_c, r0
	mov sp, #0x4000

	// (PSR_SVC_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
	mov r0, #0xD3
	msr cpsr_c, r0
	mov sp, #0x8000000

	// Clear bss section
	ldr r4, =__bss_start
	ldr r9, =__bss_end
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
	b 2f

1:
	stmia r4!, {r5-r8}
2:
	cmp r4, r9
	blo 1b

	// Move execution to kernel_main
	blx kernel_main

halt:
	b halt

.globl enable_irq
enable_irq:
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c, r0
	bx lr

irq:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	bl c_irq_handler
	pop  {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	subs pc, lr, #4
