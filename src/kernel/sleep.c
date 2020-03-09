#include "stdint.h"

extern unsigned int GET32 (uint32_t);

#define SYSTIMER 0x20003004

void sleep (uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTIMER) + msec * 977;
	while (GET32(SYSTIMER) < wakeTime);

	return;
}
