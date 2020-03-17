#ifndef VIRTMEM_H
#define VIRTMEM_H

#include "common/types.h"

void mmu_init (void);

void mmu_start (uint32_t, uint32_t);
void mmu_stop (void);

void tlbs_invalidate (void);

#endif
