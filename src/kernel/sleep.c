extern unsigned int GET32 (unsigned int);

#define SYSTIMER 0x20003004

void sleep (unsigned int msec)
{
	unsigned int currTime;
	unsigned int sleepTime = msec * 977;

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
