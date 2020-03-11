#include "common/stdint.h"
#include "kernel/asm_utils.h"
#include "kernel/timer.h"

// Sleep function
// sleep for msec millisecond
void sleep (uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTIMER) + msec * 977;
	while (GET32(SYSTIMER) < wakeTime);

	return;
}
