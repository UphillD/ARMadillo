#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "common/types.h"

void c_irq_handler (void);
void c_enable_irq (uint32_t);

#endif
