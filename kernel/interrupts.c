/*
 * ARMadillo/kernel/interrupts.c
 *
 * Provides interrupt functionality.
 *
 */

#include "common/types.h"
#include "common/string.h"
#include "addr.h"
#include "interrupts.h"
#include "system.h"

static interrupt_registers_t * interrupt_regs;

static interrupt_handler_f handlers[NUM_IRQS];
static interrupt_clearer_f clearers[NUM_IRQS];

extern void move_exception_vector(void);
extern uint32_t exception_vector;

bool IRQ_IS_BASIC (uint32_t irq_num)
{
	return (irq_num >= 64);
}

bool IRQ_IS_GPU2 (uint32_t irq_num)
{
	return ((irq_num >= 32) && (irq_num < 64));
}

bool IRQ_IS_GPU1 (uint32_t irq_num)
{
	return (irq_num < 32);
}

bool IRQ_IS_PENDING (interrupt_registers_t * interrupt_regs, int irq_num)
{
	return ((IRQ_IS_BASIC(irq_num) && ((1 << (irq_num - 64)) & interrupt_regs->irq_basic_pending))	\
		|| (IRQ_IS_GPU2(irq_num) && ((1 << (irq_num - 32)) & interrupt_regs->irq_gpu_pending2))	\
		|| (IRQ_IS_GPU1(irq_num) && ((1 << (irq_num)) & interrupt_regs->irq_gpu_pending1)));
}

/* Initialize the interrupts. */
void interrupts_init (void)
{
	interrupt_regs = (interrupt_registers_t *) IRQ_BASIC;
	memset(handlers, 0, sizeof(interrupt_handler_f) * NUM_IRQS);
	memset(clearers, 0, sizeof(interrupt_clearer_f) * NUM_IRQS);
	/* Disable all interrupts. */
	interrupt_regs->irq_basic_disable = 0xffffffff;
	interrupt_regs->irq_gpu_disable1 = 0xffffffff;
	interrupt_regs->irq_gpu_disable2 = 0xffffffff;
	move_exception_vector();
	ENABLE_INTERRUPTS();
}

 /* IRQ Handler for the CPU. */
 /* Checks if any interrupts are pending, executes the appropriate handler. */
void irq_handler (void)
{
	for (int i = 0; i < NUM_IRQS; i++) {
		/* If the interrupt is pending and there is a handler, execute it. */
		if (IRQ_IS_PENDING(interrupt_regs, i)  && (handlers[i] != 0)) {
			clearers[i]();
			ENABLE_INTERRUPTS();
			handlers[i]();
			DISABLE_INTERRUPTS();
			return;
		}
	}
}

/* Dummy interrupt handlers. */
void __attribute__ ((interrupt ("ABORT"))) reset_handler (void)
{
	kprintf("RESET HANDLER\n");
	while(1);
}
void __attribute__ ((interrupt ("ABORT"))) prefetch_abort_handler (void)
{
	kprintf("PREFETCH ABORT HANDLER\n");
	while(1);
}
void __attribute__ ((interrupt ("UNDEF"))) undefined_instruction_handler (void)
{
	kprintf("UNDEFINED INSTRUCTION HANDLER\n");
	while(1);
}
void __attribute__ ((interrupt ("SWI"))) software_interrupt_handler (void)
{
	kprintf("SWI HANDLER\n");
	while(1);
}
void __attribute__ ((interrupt ("FIQ"))) fast_irq_handler (void)
{
	kprintf("FIQ HANDLER\n");
	while(1);
}

/* Registers the appropriate IRQ handler. */
void register_irq_handler(irq_number_t irq_num, interrupt_handler_f handler, \
	interrupt_clearer_f clearer)
{
	uint32_t irq_pos;
	if (IRQ_IS_BASIC(irq_num)) {
		irq_pos = irq_num - 64;
		handlers[irq_num] = handler;
		clearers[irq_num] = clearer;
		interrupt_regs->irq_basic_enable |= (1 << irq_pos);
	} else if (IRQ_IS_GPU2(irq_num)) {
		irq_pos = irq_num - 32;
		handlers[irq_num] = handler;
		clearers[irq_num] = clearer;
		interrupt_regs->irq_gpu_enable2 |= (1 << irq_pos);
	} else if (IRQ_IS_GPU1(irq_num)) {
		irq_pos = irq_num;
		handlers[irq_num] = handler;
		clearers[irq_num] = clearer;
		interrupt_regs->irq_gpu_enable1 |= (1 << irq_pos);
	} else {
		kprintf("ERROR: CANNOT REGISTER IRQ HANDLER: INVALID IRQ NUMBER: %d\n", irq_num);
	}
}

/* Unregisters the appropriate IRQ handler. */
void unregister_irq_handler(irq_number_t irq_num)
{
	uint32_t irq_pos;
	if (IRQ_IS_BASIC(irq_num)) {
		irq_pos = irq_num - 64;
		handlers[irq_num] = 0;
		clearers[irq_num] = 0;
        /* Setting the disable bit clears the enabled bit. */
		interrupt_regs->irq_basic_disable |= (1 << irq_pos);
	} else if (IRQ_IS_GPU2(irq_num)) {
		irq_pos = irq_num - 32;
		handlers[irq_num] = 0;
		clearers[irq_num] = 0;
		interrupt_regs->irq_gpu_disable2 |= (1 << irq_pos);
	} else if (IRQ_IS_GPU1(irq_num)) {
		irq_pos = irq_num;
		handlers[irq_num] = 0;
		clearers[irq_num] = 0;
		interrupt_regs->irq_gpu_disable1 |= (1 << irq_pos);
	}
	else {
		kprintf("ERROR: CANNOT UNREGISTER IRQ HANDLER: INVALID IRQ NUMBER: %d\n", irq_num);
	}
}
