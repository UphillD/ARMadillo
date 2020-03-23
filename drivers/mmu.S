/*
 * ARMadillo/drivers/mmu.S
 *
 * Setups the memory management unit.
 */

.section ".text"

@ Starts the MMU.
.globl mmu_start
mmu_start:
	mov	r2, #0
	mcr	p15, 0, r2, c7, c7, 0	@ Invalidate caches
	mcr	p15, 0, r2, c8, c7, 0	@ Invalidate TLB
	mcr	p15, 0, r2, c7, c10, 4	@ DSB ??

	mvn	r2, #0
	bic	r2, #0xC
	mcr	p15, 0, r2, c3, c0, 0	@ Domain

	mcr	p15, 0, r0, c2, c0, 0	@ TLB base
	mcr	p15, 0, r0, c2, c0, 1	@ TLB base

	mrc	p15, 0, r2, c1, c0, 0
	orr	r2, r2, r1
	mcr	p15, 0, r2, c1, c0, 0

	bx	lr

@ Stops the MMU.
.globl mmu_stop
mmu_stop:
	mcr	p15, 0, r2, c1, c0, 0
	bic	r2, #0x1000
	bic	r2, #0x0004
	bic	r2, #0x0001
	mcr	p15, 0, r2, c1, c0, 0
	bx	lr
