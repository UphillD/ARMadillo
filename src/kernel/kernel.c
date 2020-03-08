extern void PUT32 (unsigned int, unsigned int);
extern unsigned int GET32 (unsigned int);
extern void delay (unsigned int);

#define SYSTIMER 0x20003004
#define GPFSEL3	0x2020000C
#define GPFSEL4	0x20200010
#define GPSET1	0x20200020
#define GPCLR1	0x2020002C

void sleep (unsigned int msec)
{
	unsigned int sleepTime = msec * 977;
	unsigned int currTime;

	while (1) {
		currTime = GET32(SYSTIMER);
		if ((currTime &= sleepTime) == sleepTime) break;
	}
	while (1) {
		currTime = GET32(SYSTIMER);
		if ((currTime &= sleepTime) == 0) break;
	}
	return;
}

void init_led (void)
{
	unsigned int ra;

	ra = GET32(GPFSEL4);
	ra &= ~(7 << 21);
	ra |= (1 << 21);
	PUT32(GPFSEL4, ra);
}

int kernel_main (void)
{

	init_led();

	while (1) {
		PUT32(GPCLR1, 1 << (47 - 32));
		sleep(120);
		PUT32(GPSET1, 1 << (47 - 32));
		sleep(120);
		PUT32(GPCLR1, 1 << (47 - 32));
		sleep(120);
		PUT32(GPSET1, 1 << (47 - 32));
		sleep(1200);
	}
	return 0;
}
