#ifndef UART_H
#define UART_H

#include "common/types.h"

void uart_putc (const uint32_t);
void uart_printc (const char);
void uart_printstr (const char *);

uint32_t uart_getc (void);
char uart_scanc (void);
char * uart_scanstr (void);

void uart_init (void);
void uart_printhex (const uint32_t);

#endif
