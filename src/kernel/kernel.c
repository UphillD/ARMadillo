#include "console.h"
#include "heartbeat.h"
#include "timer.h"
#include "types.h"
#include "uart.h"

void init_all(void)
{
	sleep(1000);
	led_init();
	uart_init();
	uart_printstr("Greetings!\n");
	uart_printstr("Welcome to the kernel!\n");
	return;
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
