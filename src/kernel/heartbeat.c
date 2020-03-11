#include "common/stdint.h"
#include "kernel/heartbeat.h"
#include "kernel/timer.h"
extern uint32_t GET32 (uint32_t);
extern uint32_t PUT32 (uint32_t, uint32_t);

void init_led (void)
{
	uint32_t cfg;

	cfg = GET32(GPFSEL4);
	cfg &= ~(7 << 21);
	cfg |= (1 << 21);
	PUT32(GPFSEL4, cfg);

	return;
}

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
