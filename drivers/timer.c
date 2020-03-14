/*
 * ARMadillo/drivers/timer.c
 *
 * Provides timer functionality
 *
 */

#include "common/types.h"
#include "addr.h"
#include "asm.h"
#include "timer.h"
#include "interrupts.h"
#include "uart.h"

static timer_registers_t * timer_regs;

static void timer_irq_handler(void) {
    uart_printstr("timeout :)\n");
    timer_set(3000000);
}

static void timer_irq_clearer(void) {
    timer_regs->control.timer1_matched = 1;
}

void timer_init(void) {
    timer_regs = (timer_registers_t *) SYSTEM_TIMER_BASE;
    register_irq_handler(SYSTEM_TIMER_1, timer_irq_handler, timer_irq_clearer);
}

void timer_set(uint32_t usecs) {
        timer_regs->timer1 = timer_regs->counter_low + usecs;
}


__attribute__ ((optimize(0))) void udelay (uint32_t usecs) {
    volatile uint32_t curr = timer_regs->counter_low;
    volatile uint32_t x = timer_regs->counter_low - curr;
    while (x < usecs) {
        x = timer_regs->counter_low - curr;
    }
}

/* Starts an INTR timer */
/* utilizes the ARM timer */
void timer_init2 (uint32_t usec)
{
	PUT32(ARM_TIMER_CTL, 0x003E0000);
	PUT32(ARM_TIMER_LOD, usec - 1);
	PUT32(ARM_TIMER_RLD, usec - 1);
	PUT32(ARM_TIMER_DIV, 0x000000F9);
	PUT32(ARM_TIMER_CLI, 0);
	PUT32(ARM_TIMER_CTL, 0x003E00A2);

	return;
}

/* Sleeps for msec millisecond */
/* utilizes the 64-bit free running timer */
void sleep (uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTIMERCLO) + msec * 977;
	while (GET32(SYSTIMERCLO) < wakeTime);

	return;
}
