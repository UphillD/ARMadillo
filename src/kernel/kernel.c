#include "addr.h"
#include "asm.h"
#include "heartbeat.h"
#include "interrupts.h"
#include "std.h"
#include "timer.h"
#include "types.h"
#include "uart.h"

void c_enable_irq (uint32_t usec)
{
	PUT32(IRQ_DISABLE_BASIC, 1);
	timer_init(usec);
	PUT32(IRQ_ENABLE_BASIC, 1);
	enable_irq();
	return;
}

void init_all(void)
{
	sleep(1000);
	led_init();
	uart_init();
	uart_printstr("Greetings!\n");
	uart_printstr("Welcome to the kernel!\n");
	return;
}

void console (void)
{
	while(1) {
		char *str;
		str = uart_scanstr();
		if (!(strcmp(str, "help"))) {
			uart_printstr("Available Commands:\n");
			uart_printstr("intr : sparks an interrupt\n");
		} else if (!(strcmp(str, "intr"))) {
			c_enable_irq(1000000);
			uart_printstr("INTR sparked!\n");
		} else {
			uart_printstr("Command not recognized!\n");
		}
	}
}

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;

	init_all();

	console();

	return 0;
}
