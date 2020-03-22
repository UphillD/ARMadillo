/*
 * ARMadillo/drivers/led.c
 *
 * Provides LED functionality
 */

#include "common/types.h"
#include "drivers/led.h"
#include "drivers/timer.h"
#include "addr.h"
#include "system.h"

/* Initializes the LED. */
void led_init (void)
{
	uint32_t cfg;
	cfg = GET32(GPFSEL4);
	cfg &= ~(7 << 21);
	cfg |= (1 << 21);
	PUT32(GPFSEL4, cfg);
}

/* Produces a single pulse on the LED. */
void led_pulse (void)
{
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(100);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(100);
}

/* Produces a single heartbeat pulse on the LED. */
void led_heartbeat (void)
{
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(150);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(150);
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(150);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(600);
}
