#include "common/stdint.h"
#include "kernel/asm_utils.h"
#include "kernel/heartbeat.h"
#include "kernel/peripherals.h"
#include "kernel/uart.h"

volatile uint32_t irq_count;

extern void enable_irq (void);
extern void enable_fiq (void);

void c_irq_handler (void)
{
	irq_count++;
	if (irq_count & 1) {
		PUT32(GPSET1, 1 << (47 - 32));
		uart_printstr("INTR!\n");
	} else {
		PUT32(GPCLR1, 1 << (47 - 32));
	}
	PUT32(ARM_TIMER_CLI, 0);
	return;
}

void timer_init (void)
{
	PUT32(ARM_TIMER_CTL, 0x003E0000);
	PUT32(ARM_TIMER_LOD, 5000000 - 1);
	PUT32(ARM_TIMER_RLD, 5000000 - 1);
	PUT32(ARM_TIMER_DIV, 0x000000F9);
	PUT32(ARM_TIMER_CLI, 0);
	PUT32(ARM_TIMER_CTL, 0x003E00A2);

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
	while(1) {
		continue;
	}
	return 0;
}
