#include "common/stdint.h"
#include "kernel/asm_utils.h"
#include "kernel/peripherals.h"
#include "kernel/timer.h"

void timer_init (void)
{
	PUT32(ARM_TIMER_CTL, 0x003E0000);
	PUT32(ARM_TIMER_LOD, 1000000 - 1);
	PUT32(ARM_TIMER_RLD, 1000000 - 1);
	PUT32(ARM_TIMER_DIV, 0x000000F9);
	PUT32(ARM_TIMER_CLI, 0);
	PUT32(ARM_TIMER_CTL, 0x003E00A2);

	return;
}

// Sleep function
// sleep for msec millisecond
void sleep (uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTIMERCLO) + msec * 977;
	while (GET32(SYSTIMERCLO) < wakeTime);

	return;
}
