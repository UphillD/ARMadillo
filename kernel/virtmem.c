/*
 * ARMadillo/kernel/virtmem.c
 *
 * Setups the virtual memory.
 */

#include "common/types.h"
#include "drivers/mmu.h"
#include "system.h"
#include "virtmem.h"

/* Links a virtual address with a physical address using flags. */
static void mmu_section (const uint32_t vaddr, const uint32_t paddr, \
	const uint32_t flags)
{
	uint32_t rx;
	uint32_t ry;
	uint32_t rz;

	rx = vaddr >> 20;
	ry = MMU_TABLE | (rx << 2);
	rz = (paddr & 0xFFF00000) | 0xC00 | flags | 2;
	PUT32(ry, rz);
}

/* Initializes the virtual memory. */
void mmu_init (void)
{
	/* Code:
	 * Virtual == Physical Address,
	 * Enable cache & buffer. */
	mmu_section(0x00000000, 0x00000000, 0x0000|8|4);

	/* Rest of RAM:
	 * Virtual == Physical Address
	 * Disable Cache & Buffer. */
	uint32_t addr = 0x00100000;
	while (addr < 0x20000000) {
		mmu_section(addr, addr, 0x0000);
		addr += 0x00100000;
	}

	/* Peripherals:
	 * Virtual == Physical Address,
	 * Disable Cache & Buffer. */
	mmu_section(0x20000000, 0x20000000, 0x0000);
	mmu_section(0x20200000, 0x20200000, 0x0000);

	/* Start the MMU Peripheral. */
	mmu_start(MMU_TABLE, 0x00000001|0x1000|0x0004);
}
