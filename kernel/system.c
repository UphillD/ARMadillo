/*
 * ARMadillo/kernel/system.c
 *
 * Provides some core functionality.
 *
 */

#include <stdarg.h>

#include "common/lib.h"
#include "common/types.h"
#include "drivers/led.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "interrupts.h"
#include "mem.h"
#include "process.h"
#include "system.h"
#include "virtmem.h"

/* Implementation of printf. */
/* Utilizes stdarg.h to handle variable number of arguments. */
void kprintf (const char * str, ...)
{
	va_list args;
	va_start(args, str);

	while (*str != '\0') {
		if (*str == '%') {
			switch (*(++str)) {
			case '%':
				uart_printc('%');
				break;
			case 'd':
				uart_printstr(itoa(va_arg(args, int)));
				break;
			case 's':
				uart_printstr(va_arg(args, char *));
				break;
			}
		} else if (*str == '\n') {
			uart_printc('\n');
			uart_printc('\r');
		} else {
			uart_printc(*str);
		}
		str++;
	}
	va_end(args);
	return;
}

/* Initializes everything. */
void init_all (uint32_t atags)
{
	/* Sleep for 1 second. */
	/* Useful for providing a time buffer between plugging the pi in
	 * and connecting to the serial port. */
	sleep(1000);

	/* Initialize UART0. */
	uart_init();
	kprintf("[ OK ] UART0 initialized.\n");

	/* Initialize FPU. */
	fpu_init();
	kprintf("[ OK ] FPU initialized.\n");

	/* Initialize LED. */
	led_init();
	kprintf("[ OK ] LED initialized.\n");

	/* Initialize Memory Management. */
	mem_init((atag_t *) atags);
	kprintf("[ OK ] Memory Management initialized.\n");

	/* Initialize Interrupts. */
	interrupts_init();
	kprintf("[ OK ] Interrupts initialized.\n");

	/* Initialize Processes. */
	process_init();
	kprintf("[ OK ] Processes initialized.\n");

	/* Initialize Virtual Memory. */
	mmu_init();
	kprintf("[ OK ] Virtual Memory initialized.\n");

	kprintf("\n");

	return;
}

