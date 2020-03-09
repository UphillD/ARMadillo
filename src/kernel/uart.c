#include "kernel/uart.h"
#include "common/stdint.h"

extern uint32_t GET32 (uint32_t);
extern uint32_t PUT32 (uint32_t, uint32_t);

void uart_putc (uint32_t ch)
{
	while (!(GET32(AUX_MU_LSR_REG)&0x20));
	PUT32(AUX_MU_IO_REG, ch);
	return;
}

void uart_printc (char ch)
{
	uart_putc((uint32_t)(ch));
	return;
}

void uart_printstr (char *str)
{
	for (uint32_t i = 0; str[i] != '\0'; i++) {
		uart_printc(str[i]);
		if (str[i] == '\n') {
			uart_printc('\r');
		}
	}
	return;
}

uint32_t uart_getc (void)
{
	while (!(GET32(AUX_MU_LSR_REG)&0x01));
	return GET32(AUX_MU_IO_REG);
}

char uart_scanc (void)
{
	return (char)(uart_getc());
}

void uart_init (void)
{
	unsigned int ra;

	PUT32(AUX_ENABLES, 1);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_CNTL_REG, 0);
	PUT32(AUX_MU_LCR_REG, 3);
	PUT32(AUX_MU_MCR_REG, 0);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_IIR_REG, 0xC6);
	PUT32(AUX_MU_BAUD_REG, 270);

	ra = GET32(GPFSEL1);
	ra &= ~(7 << 12); //gpio14
	ra |= 2 << 12;    //alt5
	ra &= ~(7 << 15); //gpio15
	ra |= 2 << 15;    //alt5
	PUT32(GPFSEL1, ra);

	PUT32(AUX_MU_CNTL_REG,3);

	return;
}

void uart_printhex (unsigned int hex)
{
	unsigned int i;
	unsigned int out;

	i = 32;
	while (1)
	{
		i -= 4;
		out = (hex >> i)&0xF;
		if (out > 9) {
			out += 0x37;
		} else {
			out += 0x30;
		}
		uart_putc(out);
		if (i == 0) break;
	}
	uart_putc(0x20);
	return;
}
