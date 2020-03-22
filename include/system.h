#ifndef SYSTEM_H
#define SYSTEM_H

/* Header for system.c & sys.S */

#include "common/types.h"

void kprintf (const char *, ...);

void init_all (const uint32_t);

uint32_t GET32 (uint32_t);
void PUT32 (uint32_t, uint32_t);

void halt (void);

#endif
