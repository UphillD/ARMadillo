/*
 * ARMadillo/kernel/timer.c
 *
 * Provides timer functionality
 *
 */

#include "addr.h"
#include "asm.h"
#include "timer.h"
#include "common/types.h"

/* Starts an INTR timer */
/* utilizes the ARM timer */
void timer_init (uint32_t usec)
{
	PUT32(ARM_TIMER_CTL, 0x003E0000);
	PUT32(ARM_TIMER_LOD, usec - 1);
	PUT32(ARM_TIMER_RLD, usec - 1);
	PUT32(ARM_TIMER_DIV, 0x000000F9);
	PUT32(ARM_TIMER_CLI, 0);
	PUT32(ARM_TIMER_CTL, 0x003E00A2);

	return;
}

/* Sleeps for msec millisecond */
/* utilizes the 64-bit free running timer */
void sleep (uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTIMERCLO) + msec * 977;
	while (GET32(SYSTIMERCLO) < wakeTime);

	return;
}
