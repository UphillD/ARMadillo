/*
 * ARMadillo/drivers/uart.c
 *
 * Provides UART0 functionality
 *
 */

#include "common/types.h"
#include "drivers/uart.h"
#include "addr.h"
#include "asm.h"

/* Prints a raw character in raw uint32_t format to the console. */
void uart_putc (uint32_t c)
{
	while (!(GET32(AUX_MU_LSR_REG) & 0x20));
	PUT32(AUX_MU_IO_REG, c);
	return;
}

/* Prints a character to the console. */
void uart_printc (char ch)
{
	uart_putc((uint32_t)(ch));
	return;
}

/* Prints a string to the console. */
void uart_printstr (char *str)
{
	int i = 0;
	while (str[i] != '\0') {
		uart_printc(str[i]);
		if (str[i] == '\n') {
			uart_printc('\r');
		}
		i++;
	}
	return;
}

/* Gets a character in raw uint32_t format from the console. */
uint32_t uart_getc (void)
{
	while (!(GET32(AUX_MU_LSR_REG) & 0x01));
	return GET32(AUX_MU_IO_REG);
}

/* Gets a character from the console. */
char uart_scanc (void)
{
	return (char)(uart_getc());
}

/* Gets a string from the console. */
/* !! Needs work !! */
char * uart_scanstr (void)
{
	static char str[256];
	char tmp;
	uint32_t i;

	for (i = 0; i < 256; i++) {
		tmp = uart_scanc();
		if (tmp != '\r' && tmp != '\n') {
			uart_printc(tmp);
			str[i] = tmp;
		} else {
			uart_printc('\r');
			str[i] = '\0';
			break;
		}
	}
	return str;
}

/* Initializes the UART0 serial port. */
void uart_init (void)
{
	PUT32(AUX_ENABLES, 1);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_CNTL_REG, 0);
	PUT32(AUX_MU_LCR_REG, 3);
	PUT32(AUX_MU_MCR_REG, 0);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_IIR_REG, 0xC6);
	PUT32(AUX_MU_BAUD_REG, 270);

	uint32_t cfg;
	cfg = GET32(GPFSEL1);
	cfg &= ~(7 << 12); //gpio14
	cfg |= 2 << 12;    //alt5
	cfg &= ~(7 << 15); //gpio15
	cfg |= 2 << 15;    //alt5
	PUT32(GPFSEL1, cfg);

	PUT32(AUX_MU_CNTL_REG,3);

	return;
}

/* Prints an 8 digit hex number to the console */
void uart_printhex (uint32_t hex)
{
	uint32_t i = 32;
	uint32_t out;

	do {
		i -= 4;
		out = (hex >> i) & 0xF;
		if (out > 9) {
			out += 0x37;
		} else {
			out += 0x30;
		}
		uart_putc(out);
	} while (i != 0);
	uart_putc(0x20);

	return;
}
