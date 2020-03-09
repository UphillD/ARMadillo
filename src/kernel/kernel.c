#include "kernel/uart.h"

extern void heartbeat (void);
extern void init_led(void);

int kernel_main (void)
{
	init_led();
	heartbeat();

	uart_init();
	uart_printstr ("Greetings!\n");

	while (1) {
		heartbeat();
	}
	return 0;
}
