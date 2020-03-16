/*
 * ARMadillo/kernel/kernel.c
 *
 * Main kernel function
 *
 */

#include "common/types.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "console.h"
#include "process.h"
#include "system.h"

void test (void)
{
	while (1) {
		uart_printstr("test\n");
		sleep(1000);
	}
}

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;

	init_all(atags);

	//console();
	timer_init();
	timer_set(3000000);

	int start = 12;

	kprintf ("Greetings!\n");
	kprintf ("Welcome to the kernel! %d\n", start);

	create_kernel_thread(test, "TEST", 4);

	while(1) {
		uart_printstr("main\n");
		sleep(1000);
	}

	return 0;
}
