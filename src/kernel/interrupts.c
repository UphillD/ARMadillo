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

void c_enable_irq (uint32_t usec)
{
	PUT32(IRQ_DISABLE_BASIC, 1);
	timer_init(usec);
	PUT32(IRQ_ENABLE_BASIC, 1);
	enable_irq();
	return;
}
