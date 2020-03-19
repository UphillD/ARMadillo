/*
 * ARMadillo/kernel/kernel.c
 *
 * Main kernel function
 *
 */

#include "common/types.h"
#include "console.h"
#include "system.h"

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	/* Void out the unused variables. */
	(void) r0;
	(void) r1;

	/* Initialize everything. */
	init_all(atags);

	/* Call the demo console. */
	console();

	return 0;
}
