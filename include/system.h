#ifndef SYSTEM_H
#define SYSTEM_H

#include "common/types.h"

void init_all (uint32_t);

void kprintf (const char *, ...);

void _halt (void);

/* include the assembly functions from asm.c. */
uint32_t GET32 (uint32_t);
void PUT32 (uint32_t, uint32_t);

#endif
