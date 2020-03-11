#include "common/stdint.h"
#include "kernel/asm_utils.h"
#include "kernel/peripherals.h"
#include "kernel/timer.h"

// Sleep function
// sleep for msec millisecond
void sleep (uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTIMERCLO) + msec * 977;
	while (GET32(SYSTIMERCLO) < wakeTime);

	return;
}
