#ifndef MUTEX_H
#define MUTEX_H

#include "process.h"

/* Struct for the mutex lock. */
typedef struct {
	int lock;
	process_control_block_t * locker;
	pcb_list_t wait_queue;
} mutex_t;

void mutex_init (mutex_t *);
void mutex_lock (mutex_t *);
void mutex_unlock (mutex_t *);

#endif
