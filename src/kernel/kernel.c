#include <stdlib.h>

extern void heartbeat (void);
extern void uart_init (void);
extern void uart_printstr (char *str);

int kernel_main (void)
{
	heartbeat();

	uart_init();
	heartbeat();
	uart_printstr ("Greetings!\n");

	return 0;
}
