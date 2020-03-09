extern unsigned int GET32 (unsigned int);
extern unsigned int PUT32 (unsigned int, unsigned int);
extern void sleep (unsigned int);

#define GPFSEL3	0x2020000C
#define GPFSEL4	0x20200010
#define GPSET1	0x20200020
#define GPCLR1	0x2020002C

void init_led (void)
{
	unsigned int ra;

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
	sleep(500);

	return;
}
