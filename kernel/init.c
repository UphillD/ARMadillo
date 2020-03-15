/*
 * ARMadillo/kernel/init.c
 *
 * Initializes required functions
 *
 */

#include "common/types.h"
#include "drivers/led.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "mem.h"
#include "interrupts.h"
#include "process.h"

/* Initializes everything. */
void init_all (uint32_t atags)
{
	/* Sleep for 1 second. */
	/* Useful for providing a time buffer between plugging the pi in
	 * and connecting to the serial port. */
	sleep(1000);

	/* Initialize UART0. */
	uart_init();
	uart_printstr("UART0 initialized.\n");

	/* Initialize LED. */
	led_init();
	uart_printstr("LED initialized.\n");

	/* Initialize Memory Management. */
	mem_init((atag_t *) atags);
	uart_printstr("Memory Management initialized.\n");

	/* Initialize Interrupts. */
	interrupts_init();
	uart_printstr("Interrupts initialized.\n");

	/* Initialize Processes. */
	process_init();
	uart_printstr("Processes initialized.\n");

	return;
}
