/*
 * ARMadillo/kernel/process.c
 *
 * Provides process functionality.
 */

#include "common/stdlib.h"
#include "common/string.h"
#include "drivers/timer.h"
#include "interrupts.h"
#include "lock.h"
#include "mem.h"
#include "mutex.h"
#include "process.h"
#include "spinlock.h"
#include "system.h"

static uint32_t curr_pid = 1;
#define NEW_PID curr_pid++;

extern uint8_t __end;

IMPLEMENT_LIST(pcb);
pcb_list_t run_queue;
pcb_list_t all_proc_list;

process_control_block_t *current_process;

/* Schedule a context switch from one process to another. */
void schedule (void)
{
	DISABLE_INTERRUPTS();
	process_control_block_t *new_thread;
	process_control_block_t *old_thread;

	/* If the run queue is empty, just reschedule. */
	if (size_pcb_list(&run_queue) == 0) {
		timer_set(10000);
		ENABLE_INTERRUPTS();
		return;
	}

	/* Get the next thread to run, pick thread using round-robin. */
	new_thread = pop_pcb_list(&run_queue);
	old_thread = current_process;
	current_process = new_thread;

	/* Put the current thread back in the run queue. */
	append_pcb_list(&run_queue, old_thread);

	/* Context Switch! */
	switch_to_thread(old_thread, new_thread);
	ENABLE_INTERRUPTS();
}

/* Initialize processes. */
void process_init (void)
{
	process_control_block_t *main_pcb;
	INITIALIZE_LIST(run_queue);
	INITIALIZE_LIST(all_proc_list);

	/* Allocate and initialize the pcb. */
	main_pcb = kmalloc(sizeof(process_control_block_t));
	main_pcb->stack_page = (void *)&__end;
	main_pcb->pid = NEW_PID;
	memcpy(main_pcb->proc_name, "Console", 8);

	/* Add main to the  process list.
	 * No need to add it to the run queue. */
	append_pcb_list(&all_proc_list, main_pcb);

	current_process = main_pcb;

	/* Set the scheduler for every 10 ms (repeatable). */
	timer_set(10000);
}

static void reap (void)
{
	DISABLE_INTERRUPTS();
	process_control_block_t *new_thread;
	process_control_block_t *old_thread;

	/* Wait for something to appear in the run queue. */
	while (size_pcb_list(&run_queue) == 0);

	/* Get the next thread to run, pick it using round-robin. */
	new_thread = pop_pcb_list(&run_queue);
	old_thread = current_process;
	current_process = new_thread;

	/* Free the resources used by the old process.
	 * Little clumsy with the dangling pointers. */
	free_page(old_thread->stack_page);
	kfree(old_thread);

	remove_pcb(&all_proc_list, old_thread);

	/* Context Switch! */
	switch_to_thread(old_thread, new_thread);
}

/* Creates a new process. */
void create_kernel_thread (kthread_function_f thread_func,	\
	char *name, int name_len)
{
	process_control_block_t *pcb;
	struct proc_saved_state_t *new_proc_state;

	/* Allocate and initialize the PCB. */
	pcb = kmalloc(sizeof(process_control_block_t));
	pcb->stack_page = alloc_page();
	pcb->pid = NEW_PID;
	memcpy(pcb->proc_name, name, min(name_len,19));
	pcb->proc_name[min(name_len,19)] = 0;

	/* Get the location the stack pointer should be at when this is run. */
	new_proc_state = pcb->stack_page + PAGE_SIZE -		\
		sizeof(struct proc_saved_state_t);
	pcb->saved_state = new_proc_state;

	/* Set up the stack that will be restored during a context switch. */
	memset(new_proc_state, 0, sizeof(struct proc_saved_state_t));

	/* lr is used as return address in switch_to_thread. */
	new_proc_state->lr = (uint32_t)thread_func;
	/* When the thread function returns,
	 * this reaper routine will clean it up */
	new_proc_state->sp = (uint32_t)reap;

	/* Sets the thread to run in supervisor mode with IRQs enabled. */
	new_proc_state->cpsr = 0x13 | (8 << 1);

	/* Add the thread to the all process list and the run queue. */
	append_pcb_list(&all_proc_list, pcb);
	append_pcb_list(&run_queue, pcb);
}

/*
 * Spinlocks
 */

void spinlock_init (spinlock_t *lock)
{
	*lock = 1;
}

void spinlock_lock (spinlock_t *lock)
{
	while (!lock_try(lock))
		;
}

void spinlock_unlock (spinlock_t *lock)
{
	*lock = 1;
}

/*
 * Mutex
 */

void mutex_init (struct mutex_t *lock)
{
	lock->lock = 1;
	lock->locker = 0;
	INITIALIZE_LIST(lock->wait_queue);
}

void mutex_lock (struct mutex_t *lock)
{
	process_control_block_t *new_thread;
	process_control_block_t *old_thread;

	/* If you don't get the lock, take self off run queue
	 * and put on to mutex wait queue. */
	while (!lock_try(&lock->lock)) {

		/* Get the next thread to run using round robin. */
		DISABLE_INTERRUPTS();
		new_thread = pop_pcb_list(&run_queue);
		old_thread = current_process;
		current_process = new_thread;

		/* Put the current thread back of this mutex's wait queue,
		 *  not on the run queue. */
		append_pcb_list(&lock->wait_queue, old_thread);

		/* Context Switch. */
		switch_to_thread(old_thread, new_thread);
		ENABLE_INTERRUPTS();
	}
	lock->locker = current_process;
}

void mutex_unlock (struct mutex_t *lock)
{
	process_control_block_t *thread;

	lock->lock = 1;
	lock->locker = 0;

	/* If there is any process waiting on this lock,
	 * put them back in the run queue. */
	if (size_pcb_list(&lock->wait_queue)) {
		thread = pop_pcb_list(&lock->wait_queue);
		push_pcb_list(&run_queue, thread);
	}
}
