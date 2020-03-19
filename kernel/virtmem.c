/*
 * ARMadillo/kernel/virtmem.c
 *
 * Provides Virtual Memory Functionality.
 *
 */

#include "common/types.h"
#include "addr.h"
#include "virtmem.h"
#include "system.h"

/* Links the virtual address vadd with the physical address padd using flags. */
static void mmu_section (uint32_t vadd, uint32_t padd, uint32_t flags)
{
	uint32_t rx, ry, rz;

	rx = vadd >> 20;
	ry = MMUTABLEBASE | (rx << 2);
	rz = (padd & 0xFFF00000) | 0xC00 | flags | 2;
	PUT32(ry, rz);
}

/* Initializes the virtual memory. */
void mmu_init (void)
{
	/* Code,
	 * Virtual == Physical Address,
	 * Enable cache & buffer. */
	mmu_section(0x00000000, 0x00000000, 0x0000|8|4);

	/* Rest of RAM,
	 * Virtual == Physical Address
	 * Disable Cache & Buffer. */
	uint32_t addr = 0x00100000;
	while (addr < 0x20000000) {
		mmu_section(addr, addr, 0x0000);
		addr += 0x00100000;
	}

	/* Peripherals,
	 * Virtual == Physical Address,
	 * Disable Cache & Buffer. */
	mmu_section(0x20000000, 0x20000000, 0x0000);
	mmu_section(0x20200000, 0x20200000, 0x0000);

	/* Start the MMU Peripheral. */
	mmu_start(MMUTABLEBASE, 0x00000001|0x1000|0x0004);

}
