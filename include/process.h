#ifndef PROCESS_H
#define PROCESS_H

/* Header for process.c & proc.S */

#include "common/list.h"

typedef void (*kthread_function_f)(void);

struct proc_saved_state_t {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t cpsr;
	uint32_t sp;
	uint32_t lr;
};

/* Creates list for the PCBs. */
DEFINE_LIST(pcb);

/* Creates a struct for each PCB. */
typedef struct pcb {
	struct proc_saved_state_t * saved_state;	/* Points to the pushed registers of the process in the stack. */
						/* Becomes invalid once the process is running. */
	void * stack_page;			/* The stack for this process. */
						/* The stack starts at the end of this page. */
	uint32_t pid;				/* The process' ID number. */
	DEFINE_LINK(pcb);			/* Link the PCB struct in the PCB list. */
	char proc_name[20];			/* The process' name. */
} process_control_block_t;

void process_init (void);

void create_kernel_thread (kthread_function_f, char *, int);
void schedule (void);

void switch_to_thread (process_control_block_t * old,	\
	process_control_block_t * new);

#endif
