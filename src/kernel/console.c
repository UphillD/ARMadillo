/*
 * ARMadillo/kernel/console.c
 *
 * Provides a serial console over UART0 for I/O
 *
 */

#include "asm.h"
#include "interrupts.h"
#include "common/string.h"
#include "uart.h"

void console (void)
{
	while(1) {
		char *str;
		str = uart_scanstr();
		if (!(strcmp(str, "help"))) {
			uart_printstr("Available Commands:\n");
			uart_printstr("intr : sparks an interrupt\n");
			uart_printstr("halt : shuts down the machine\n");
		} else if (!(strcmp(str, "intr"))) {
			c_enable_irq(1000000);
			uart_printstr("INTR sparked!\n");
		} else if (!(strcmp(str, "halt"))) {
			halt();

		} else {
			uart_printstr("Command not recognized!\n");
		}
	}

	return;
}
