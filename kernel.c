extern void PUT32 (unsigned int, unsigned int);
extern unsigned int GET32 (unsigned int);
extern void dummy (unsigned int);

#define GPFSEL3	0x2020000C
#define GPFSEL4	0x20200010
#define GPSET1	0x20200020
#define GPCLR1	0x2020002C

int kernel_main (void)
{
	unsigned int ra;

	ra = GET32(GPFSEL4);
	ra &= ~(7 << 21);
	ra |= (1 << 21);
	PUT32(GPFSEL4, ra);

	while (1) {
		PUT32(GPCLR1, 1 << (47 - 32));
		for (ra = 0; ra < 0x80000; ra++) {
			dummy(ra);
		}
		PUT32(GPSET1, 1 << (47 - 32));
		for (ra = 0; ra < 0x80000; ra++) {
			dummy(ra);
		}
		PUT32(GPCLR1, 1 << (47 - 32));
		for (ra = 0; ra < 0x80000; ra++) {
			dummy(ra);
		}
		PUT32(GPSET1, 1 << (47 - 32));
		for (ra = 0; ra < 0x300000; ra++) {
			dummy(ra);
		}
	}
	return 0;
}
