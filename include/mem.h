#ifndef MEM_H
#define MEM_H

#include "common/list.h"
#include "common/types.h"
#include "atag.h"

/* Base memory structure:
 * 4KB Page size
 * 4KB Kernel stack
 * 1MB Kernel heap
 */
enum {
	PAGE_SIZE		= 4096,
	KERNEL_HEAP_SIZE	= (1024*1024),
	KERNEL_STACK_SIZE	= PAGE_SIZE,
};

/* Flag struct for each memory page. */
struct page_flags_t {
	uint8_t allocated: 1;		/* This page is currently allocated. */
	uint8_t kernel_page: 1;		/* This page is part of the kernel. */
	uint8_t kernel_heap_page: 1;	/* This page is part of the kernel heap. */
	uint32_t reserved: 29;
};

/* Create list for the memory pages. */
DEFINE_LIST(page);

/* Struct for each memory page. */
typedef struct page {
	uint32_t vaddr_mapped;		/* The virtual address of the page. */
	struct page_flags_t flags;	/* The flags struct. */
	DEFINE_LINK(page);		/* Link the page in the page list. */
} page_t;

void mem_init (struct atag_t *);
uint32_t get_mem_size (struct atag_t *);

void * alloc_page (void);
void free_page (void *);

void * kmalloc (uint32_t);
void kfree (void *);

#endif
