extern void heartbeat (void);
extern void uart_init (void);
extern void uart_printhex (unsigned int);
extern void uart_putc (unsigned int);

int kernel_main (void)
{
	heartbeat();

	uart_init();
	uart_printhex(0xabcd1234);
	uart_putc(0x0D);
	uart_putc(0x0A);
	uart_putc(0x48);
	uart_putc(0x65);
	uart_putc(0x6c);
	uart_putc(0x6c);
	uart_putc(0x6f);
	uart_putc(0x21);

	return 0;
}
