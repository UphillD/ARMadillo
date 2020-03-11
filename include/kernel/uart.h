#ifndef UART_H
#define UART_H

#include "common/stdint.h"

enum {
	// The GPIO registers base address
	GPIO_BASE	= 0x20200000,

	// Controls actuation of pull up/down to all GPIO pins
	GPPUD		= (GPIO_BASE + 0x94),
	// Controls actuation of pull up/down to specific GPIO pin
	GPPUDCLK0	= (GPIO_BASE + 0x98),

	// The UART0 base address
	AUX_BASE	= 0x20215000,

	AUX_ENABLES     = (AUX_BASE + 0x04),
	AUX_MU_IO_REG   = (AUX_BASE + 0x40),
	AUX_MU_IER_REG  = (AUX_BASE + 0x44),
	AUX_MU_IIR_REG  = (AUX_BASE + 0x48),
	AUX_MU_LCR_REG  = (AUX_BASE + 0x4C),
	AUX_MU_MCR_REG  = (AUX_BASE + 0x50),
	AUX_MU_LSR_REG  = (AUX_BASE + 0x54),
	AUX_MU_MSR_REG  = (AUX_BASE + 0x58),
	AUX_MU_SCRATCH  = (AUX_BASE + 0x5C),
	AUX_MU_CNTL_REG = (AUX_BASE + 0x60),
	AUX_MU_STAT_REG = (AUX_BASE + 0x64),
	AUX_MU_BAUD_REG = (AUX_BASE + 0x68),
};

void uart_putc (uint32_t ch);
void uart_printc (char ch);
void uart_printstr (char *str);

uint32_t uart_getc (void);
char uart_scanc (void);

void uart_init (void);
void uart_printhex (unsigned int hex);
#endif
