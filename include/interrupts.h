#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "common/types.h"

#define NUM_IRQS 72

/* Checks whether interrupts are enabled.
 * Does so by loading the Current Program Status Register
 *  and checking if bit 7 is clear. */
__inline__ int INTERRUPTS_ENABLED (void)
{
	int res;
	__asm__ __volatile__("mrs %[res], CPSR": [res] "=r" (res)::);
	return ((res >> 7) & 1) == 0;
}

/* Enables IRQs.
 * Executes Change Processor State instruction with flag i. */
__inline__ void ENABLE_INTERRUPTS (void)
{
	if (!INTERRUPTS_ENABLED())
		__asm__ __volatile__("cpsie i");
}

/* Disables IRQs. */
__inline__ void DISABLE_INTERRUPTS(void)
{
	if (INTERRUPTS_ENABLED())
		__asm__ __volatile__("cpsid i");
}

typedef void (*interrupt_handler_f)(void);
typedef void (*interrupt_clearer_f)(void);

/* Enum for the number of IRQs. */
typedef enum {
	SYSTEM_TIMER_1 = 1,
	USB_CONTROLLER = 9,
	ARM_TIMER = 64
} irq_number_t;

/* Struct for the IRQ peripheral. */
typedef struct {
	uint32_t irq_basic_pending;
	uint32_t irq_gpu_pending1;
	uint32_t irq_gpu_pending2;
	uint32_t fiq_control;
	uint32_t irq_gpu_enable1;
	uint32_t irq_gpu_enable2;
	uint32_t irq_basic_enable;
	uint32_t irq_gpu_disable1;
	uint32_t irq_gpu_disable2;
	uint32_t irq_basic_disable;
} interrupt_registers_t;

void interrupts_init (void);

void register_irq_handler (irq_number_t, interrupt_handler_f, interrupt_clearer_f);
void unregister_irq_handler (irq_number_t);

#endif
