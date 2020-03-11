#include "common/stdint.h"
#include "kernel/heartbeat.h"
#include "kernel/uart.h"

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;

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
