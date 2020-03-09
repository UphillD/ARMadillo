#include "stdint.h"
extern uint32_t GET32 (uint32_t);
extern uint32_t PUT32 (uint32_t, uint32_t);
extern void sleep (uint32_t);

#define GPFSEL3	0x2020000C
#define GPFSEL4	0x20200010
#define GPSET1	0x20200020
#define GPCLR1	0x2020002C

void init_led (void)
{
	uint32_t ra;

	ra = GET32(GPFSEL4);
	ra &= ~(7 << 21);
	ra |= (1 << 21);
	PUT32(GPFSEL4, ra);

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
