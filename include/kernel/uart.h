#ifndef UART_H
#define UART_H

#include "common/stdint.h"

void uart_putc (uint32_t ch);
void uart_printc (char ch);
void uart_printstr (char *str);

uint32_t uart_getc (void);
char uart_scanc (void);
char * uart_scanstr (void);

void uart_init (void);
void uart_printhex (unsigned int hex);
#endif
