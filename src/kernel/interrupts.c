#include "asm.h"
#include "addr.h"
#include "timer.h"

void c_irq_handler (void)
{
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(100);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(100);
	PUT32(ARM_TIMER_CLI, 0);
	return;
}
