/*
 * ARMadillo/kernel/console.c
 *
 * Provides a serial console over UART0 for demo purposes
 *
 */

#include "common/string.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "mutex.h"
#include "process.h"
#include "system.h"

static int cmd_option (char * str)
{
	if (!strcmp(str, "help")) return 0;
	else if (!strcmp(str, "intr")) return 1;
	else if (!strcmp(str, "proc")) return 2;
	else if (!strcmp(str, "lock")) return 3;
	else if (!strcmp(str, "halt")) return 9;
	else return -1;
}

mutex_t test_mutex;

void user_process (void)
{
	static int i = 0;
	while (1) {
		kprintf("This is a user process on its execution #%d!\n", i++);
		sleep(2000);
	}
	return;
}

void kernel_process (void)
{
	static int i = 0;
	while (1) {
		kprintf("This is a kernel process on its execution #%d!\n", i++);
		sleep(2000);
	}
	return;
}

void user_process_mutex (void)
{
	static int i = 0;
	while (1) {
		if (i % 3 == 0)
			mutex_lock(&test_mutex);
		else if (i % 3 == 2)
			mutex_unlock(&test_mutex);

		kprintf("This is a user process on its execution #%d!\n", i++);
		sleep(1000);
	}
}

void kernel_process_mutex (void)
{
	static int i = 0;
	while (1) {
		if (i % 3 == 0)
			mutex_lock(&test_mutex);
		else if (i % 3 == 2)
			mutex_unlock(&test_mutex);

		kprintf("This is a kernel process on its execution #%d!\n", i++);
		sleep(1000);
	}
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
			kprintf("intr: sparks a repeatable interrupt.\n");
			kprintf("proc: displays context switching capability.\n");
			kprintf("lock: displays context switching capability /w locks.\n");
			kprintf("halt: halts.\n");
			break;
		case (1):
			kprintf("Setting interrupt..\n");
			kprintf("You should see the LED pulsing.\n");
			timer_init();
			timer_set(500000);
			break;
		case (2):
			kprintf("Launching user process..\n");
			scheduler_init();
			scheduler(1000000);
			create_kernel_thread(user_process, "USER", 4);
			kprintf("Launching kernel process..\n");
			kernel_process();
			break;
		case (3):
			kprintf("Launching user process /w lock..\n");
			mutex_init(&test_mutex);
			scheduler_init();
			scheduler(1000000);
			create_kernel_thread(user_process_mutex, "USER_LOCK", 9);
			kprintf("Launching kernel process /w lock..\n");
			kernel_process_mutex();
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
