/*
 * ARMadillo/drivers/timer.c
 *
 * Setups and utilizes the ARM timer.
 */

#include "common/types.h"
#include "drivers/led.h"
#include "drivers/timer.h"
#include "addr.h"
#include "interrupts.h"
#include "process.h"
#include "sys.h"

/* Sleeps for msec millisecond */
/* Utilizes the 64-bit free running timer */
void sleep (const uint32_t msec)
{
	uint32_t wakeTime = GET32(SYSTEM_TIMER_CLOCK) + msec * 977;
	while (GET32(SYSTEM_TIMER_CLOCK) < wakeTime)
		;
}

/*
 * IRQ
 */

static struct timer_registers_t * timer_regs;

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


/* Registers the timer_irq_handler function as the IRQ handler. */
void timer_init (void)
{
	timer_regs = (struct timer_registers_t *) SYSTEM_TIMER_BASE;
	register_irq_handler(SYSTEM_TIMER_1, timer_irq_handler, timer_irq_clearer);
}

/* Sets the timer. */
void timer_set (const uint32_t usecs)
{
	timer_regs->timer1 = timer_regs->counter_low + usecs;
}

/*
 * Scheduler
 */

/* Registers the scheduler as the IRQ handler. */
void scheduler_init (void)
{
	timer_regs = (struct timer_registers_t *) SYSTEM_TIMER_BASE;
	register_irq_handler(SYSTEM_TIMER_1, schedule, timer_irq_clearer);
}
