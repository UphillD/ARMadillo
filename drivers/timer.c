/*
 * ARMadillo/drivers/timer.c
 *
 * Provides timer functionality
 *
 */

#include "common/types.h"
#include "drivers/uart.h"
#include "drivers/led.h"
#include "drivers/timer.h"
#include "addr.h"
#include "interrupts.h"
#include "process.h"
#include "system.h"

/* Sleeps for msec millisecond */
/* utilizes the 64-bit free running timer */
void sleep (uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTIMERCLO) + msec * 977;
	while (GET32(SYSTIMERCLO) < wakeTime);
}

/*
 * IRQ Related
 */

static timer_registers_t * timer_regs;

/* The IRQ handler. */
static void timer_irq_handler (void)
{
	led_pulse();
	timer_set(500000);
}

/* The IRQ clearer. */
static void timer_irq_clearer (void)
{
	timer_regs->control.timer1_matched = 1;
}

/* The Scheduler handler. */
static void scheduler_handler (void)
{
	schedule();
}

/* The Scheduler clearer. */
static void scheduler_clearer (void)
{
	timer_regs->control.timer1_matched = 1;
}

/* Registers the timer_irq_handler function as the IRQ handler. */
void timer_init (void)
{
	timer_regs = (timer_registers_t *) SYSTEM_TIMER_BASE;
	register_irq_handler(SYSTEM_TIMER_1, timer_irq_handler, timer_irq_clearer);
	return;
}

void scheduler_init (void)
{
	timer_regs = (timer_registers_t *) SYSTEM_TIMER_BASE;
	register_irq_handler(SYSTEM_TIMER_1, scheduler_handler, scheduler_clearer);
}

/* Sets the timer. */
void timer_set (uint32_t usecs)
{
	timer_regs->timer1 = timer_regs->counter_low + usecs;
}

void scheduler (uint32_t usecs)
{
	timer_regs->timer1 = timer_regs->counter_low + usecs;
}

__attribute__ ((optimize(0))) void udelay (uint32_t usecs) {
    volatile uint32_t curr = timer_regs->counter_low;
    volatile uint32_t x = timer_regs->counter_low - curr;
    while (x < usecs) {
        x = timer_regs->counter_low - curr;
    }
}
