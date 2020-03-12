#include "console.h"
#include "led.h"
#include "common/lib.h"
#include "mem.h"
#include "timer.h"
#include "types.h"
#include "uart.h"

void init_all(uint32_t atags)
{
	sleep(1000);
	led_init();
	uart_init();
	mem_init((atag_t * )atags);
	uart_printstr("Greetings!\n");
	uart_printstr("Welcome to the kernel!\n");
	return;
}

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;

	init_all(atags);

	console();

	return 0;
}
