#include "common/types.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "console.h"
#include "init.h"

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;

	init_all(atags);

	//console();
	timer_init();
	timer_set(3000000);

	uart_printstr("Greetings!\n");
	uart_printstr("Welcome to the kernel!\n");

	while(1) {
		uart_printstr("main\n");
		sleep(1000);
	}

	return 0;
}
