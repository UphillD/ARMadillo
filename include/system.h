#ifndef SYSTEM_H
#define SYSTEM_H

#include "common/types.h"

void init_all (uint32_t);

void kprintf (const char *, ...);

void _halt (void);

/* include the assembly functions from asm.S. */
uint32_t GET32 (uint32_t);
void PUT32 (uint32_t, uint32_t);

/* include the try_lock function from lock.S. */
int try_lock (int *);

/* include the fpu_init function from fpu.S. */
void fpu_init (void);

#endif
