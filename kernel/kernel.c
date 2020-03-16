/*
 * ARMadillo/kernel/kernel.c
 *
 * Main kernel function
 *
 */

#include "common/types.h"
#include "drivers/timer.h"
#include "console.h"
#include "system.h"

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;

	init_all(atags);

	console();

	return 0;
}
