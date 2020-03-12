#include "common/stdint.h"
#include "kernel/asm_utils.h"
#include "kernel/heartbeat.h"
#include "kernel/peripherals.h"
#include "kernel/timer.h"
#include "kernel/uart.h"

volatile uint32_t irq_count;

extern void enable_irq (void);
extern void enable_fiq (void);

void c_irq_handler (void)
{
	PUT32(GPCLR1, 1 << (47 - 32));
	sleep(100);
	PUT32(GPSET1, 1 << (47 - 32));
	sleep(100);
	PUT32(ARM_TIMER_CLI, 0);
	return;
}

int kernel_main (uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;

	PUT32(IRQ_DISABLE_BASIC, 1);

	init_led();
	uart_init();
	uart_printstr ("Greetings!\n");
	uart_printstr ("Welcome to the kernel!\n");

	timer_init();
	PUT32(IRQ_ENABLE_BASIC, 1);
	irq_count = 0;
	enable_irq();
	char *str;
	uart_printc('$');
	uart_printc(' ');
	while(1) {
		str = uart_scanstr();
		str[30] = '0';
		continue;
	}
	return 0;
}
