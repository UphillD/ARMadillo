#ifndef MEM_H
#define MEM_H

#include "common/list.h"
#include "common/types.h"
#include "atag.h"

// Set Page Size to 4KB
#define PAGE_SIZE 4096
// Set Kernel Heap Size to 1MB
#define KERNEL_HEAP_SIZE (1024 * 1024)
#define KERNEL_STACK_SIZE PAGE_SIZE
#define IRQ_STACK_SIZE PAGE_SIZE

typedef struct {
	uint8_t allocated: 1;			// This page is allocated to something
	uint8_t kernelPage: 1;			// This page is a part of the kernel
	uint8_t kernelHeapPage: 1;		// This page is a part of the kernel heap
	uint32_t reserved: 29;
} page_flags_t;

typedef struct page {
	uint32_t vaddr_mapped;			// The virtual address that maps to this page
	page_flags_t flags;
	define_link(page);
} page_t;

typedef struct heap_segment {
    struct heap_segment * next;
    struct heap_segment * prev;
    uint32_t isAllocated;
    uint32_t segmentSize;  // Includes this header
} heap_segment_t;


uint32_t mem_getSize (atag_t *);
void mem_init (atag_t *);

void * alloc_page (void);
void free_page (void *);

void * kmalloc (uint32_t);
void kfree (void *);

#endif
