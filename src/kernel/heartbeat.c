#include "addr.h"
#include "asm.h"
#include "heartbeat.h"
#include "timer.h"
#include "types.h"

// Initialize LED light
void led_init (void)
{
	uint32_t cfg;

	cfg = GET32(GPFSEL4);
	cfg &= ~(7 << 21);
	cfg |= (1 << 21);
	PUT32(GPFSEL4, cfg);

	return;
}

// Produce heartbeat pulse on the LED
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
