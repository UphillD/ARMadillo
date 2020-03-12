#include "asm.h"
#include "addr.h"
#include "led.h"
#include "timer.h"

void c_irq_handler (void)
{
	led_pulse();
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
