/*
 * ARMadillo/kernel/console.c
 *
 * Provides a serial console over UART0 for demo purposes
 *
 */

#include "common/string.h"
#include "drivers/uart.h"
#include "system.h"

static int cmd_option (char * str)
{
	if (!strcmp(str, "help")) return 0;
	else if (!strcmp(str, "intr")) return 1;
	else if (!strcmp(str, "proc")) return 2;
	else if (!strcmp(str, "halt")) return 9;
	else return -1;
}

void console (void)
{
	while(1) {
		uart_printstr("$ ");
		char *str;
		str = uart_scanstr();
		int option = cmd_option(str);
		switch (option) {
		case (0):
			break;
		case (1):
			break;
		case (2):
			break;
		case (9):
			kprintf("Goodbye!\n");
			_halt();
			break;
		case (-1):
			kprintf("Unrecognized command!\n");
			break;
		}
	}

	return;
}
