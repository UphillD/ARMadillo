#ifndef MUTEX_H
#define MUTEX_H

#include "process.h"

/* Struct for the mutex lock. */
struct mutex_t {
	int lock;
	process_control_block_t * locker;
	pcb_list_t wait_queue;
};

void mutex_init (struct mutex_t *);
void mutex_lock (struct mutex_t *);
void mutex_unlock (struct mutex_t *);

#endif
