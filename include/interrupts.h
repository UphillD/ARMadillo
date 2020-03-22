#ifndef INTERRUPTS_H
#define INTERRUPTS_H

/* Header for interrupts.c & intr.S */

#include "common/types.h"

#define NUM_IRQS 72

uint32_t exception_vector;
void move_exception_vector (void);

/* Checks whether interrupts are enabled.
 * Does so by loading the Current Program Status Register
 *  and checking if bit 7 is clear. */
inline bool INTERRUPTS_ENABLED (void)
{
	int res;
	asm volatile ("mrs %[res], CPSR": [res] "=r" (res)::);
	return (((res >> 7) & 1) == 0);
}

/* Enables IRQs. */
inline void ENABLE_INTERRUPTS (void)
{
	if (!INTERRUPTS_ENABLED())
		asm volatile ("cpsie i");
}

/* Disables IRQs. */
inline void DISABLE_INTERRUPTS (void)
{
	if (INTERRUPTS_ENABLED())
		asm volatile ("cpsid i");
}

typedef void (*interrupt_handler_f)(void);
typedef void (*interrupt_clearer_f)(void);

/* Enum for the number of IRQs. */
enum irq_number_t {
	SYSTEM_TIMER_1 = 1,
	USB_CONTROLLER = 9,
	ARM_TIMER = 64,
};

/* Struct for the IRQ peripheral. */
struct interrupt_registers_t {
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
};

void interrupts_init (void);

void register_irq_handler (enum irq_number_t,	\
	interrupt_handler_f, interrupt_clearer_f);
void unregister_irq_handler (enum irq_number_t);

#endif
