extern unsigned int GET32 (unsigned int);

#define SYSTIMER 0x20003004

void sleep (unsigned int msec)
{

	unsigned int currTime = GET32(SYSTIMER);
	unsigned int sleepTime = msec * 977;
	unsigned int wakeTime = currTime + sleepTime;
	while ((currTime = GET32(SYSTIMER)) < wakeTime);

	return;

}
