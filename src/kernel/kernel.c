#include "kernel/heartbeat.h"
#include "kernel/uart.h"

int kernel_main (void)
{
	init_led();
	heartbeat();

	uart_init();
	uart_printstr ("Greetings!\n");
	uart_printstr ("Welcome to the kernel!\n");

	while (1) {
		heartbeat();
	}
	return 0;
}
