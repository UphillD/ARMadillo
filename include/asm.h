#ifndef ASM_H
#define ASM_H

#include "types.h"

uint32_t GET32 (uint32_t);
void PUT32 (uint32_t, uint32_t);

void halt (void);

void enable_irq (void);
void enable_fiq (void);

#endif
