/*
 * ARMadillo/kernel/console.c
 *
 * Provides a serial console over UART0 for demo purposes
 *
 */

#include "common/string.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "process.h"
#include "system.h"

static int cmd_option (char * str)
{
	if (!strcmp(str, "help")) return 0;
	else if (!strcmp(str, "intr")) return 1;
	else if (!strcmp(str, "proc")) return 2;
	else if (!strcmp(str, "halt")) return 9;
	else return -1;
}

void user_process (void)
{
	while (1) {
		kprintf("This is a user process!.\n");
		sleep(2000);
	}
	return;
}

void kernel_process (void)
{
	while (1) {
		kprintf("This is a kernel process!.\n");
		sleep(2000);
	}
	return;
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
			kprintf("Available commands:\n");
			kprintf("help: prints this message.\n");
			kprintf("intr: demo is a WIP.\n");
			kprintf("proc: displays context switching capability.\n");
			kprintf("halt: halts.\n");
			break;
		case (1):
			break;
		case (2):
			kprintf("Launching user process..\n");
			timer_set(1000000);
			create_kernel_thread(user_process, "USER", 4);
			kprintf("Launching kernel process..\n");
			kernel_process();
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
