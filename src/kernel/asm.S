.section ".text"

.globl GET32
GET32:
	ldr r0, [r0]
	bx lr

.globl PUT32
PUT32:
	str r1, [r0]
	bx lr

.globl halt
halt:
	wfe
	b halt

/* IRQ Enabler (ASM) */
.globl enable_irq
enable_irq:
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c, r0
	bx lr
