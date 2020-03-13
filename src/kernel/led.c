/*
 * ARMadillo/kernel/led.c
 *
 * Provides LED functionality
 */

#include "addr.h"
#include "asm.h"
#include "led.h"
#include "timer.h"
#include "common/types.h"

/* Initializes the LED. */
void led_init (void)
{
	uint32_t cfg;

	cfg = GET32(GPFSEL4);
	cfg &= ~(7 << 21);
	cfg |= (1 << 21);
	PUT32(GPFSEL4, cfg);

	return;
}

/* Produces a single pulse on the LED. */
void led_pulse (void)
{
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(100);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(100);

	return;
}

/* Produces a single heartbeat pulse on the LED. */
void heartbeat (void)
{
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(150);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(150);
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(150);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(600);

	return;
}
