#ifndef MEM_H
#define MEM_H

#include "atag.h"
#include "common/list.h"
#include "types.h"

#define PAGE_SIZE 4096

typedef struct {
	uint8_t allocated: 1;			// This page is allocated to something
	uint8_t kernelPage: 1;			// This page is a part of the kernel
	uint32_t reserved: 30;
} page_flags_t;

typedef struct page {
	uint32_t vaddr_mapped;			// The virtual address that maps to this page
	page_flags_t flags;
	define_link(page);
} page_t;


uint32_t mem_getSize (atag_t * atags);
void mem_init (atag_t * atags);

void * alloc_page(void);
void free_page(void * ptr);

#endif
