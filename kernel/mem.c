/*
 * ARMadillo/kernel/mem.c
 *
 * Provides memory management functionality.
 *
 */

#include "mem.h"
#include "atag.h"
#include "common/lib.h"
#include "common/string.h"
#include "common/types.h"

/*
 * Heap Related
 */

/* Initializes the heap. Definition below */
static void heap_init(uint32_t heap_start);

 /* Struct for each heap segment. */
typedef struct heap_segment {
	struct heap_segment * next;
	struct heap_segment * prev;
	uint32_t is_allocated;		/* This segment is allocated. */
	uint32_t segment_size;		/* Size of this segment, includes this header. */
} heap_segment_t;

static heap_segment_t * heap_segment_list_head;

/*
 * Memory Related
 */

extern uint8_t __end;
static uint32_t num_pages;

IMPLEMENT_LIST(page);

static page_t * all_pages_array;
page_list_t free_pages;

/* Gets the total memory size from the atags. */
uint32_t get_mem_size (atag_t * tag) {
	while (tag->tag != NONE) {
		if (tag->tag == MEM)
			return tag->mem.size;
	tag = (atag_t *)(((uint32_t *)tag) + tag->tag_size);
	}
	return 0;
}

/* Initializes the memory. */
void mem_init (atag_t * atags) {
	uint32_t mem_size, page_array_len, kernel_pages, page_array_end, i;

	/* Calculate the total number of pages. */
	mem_size = get_mem_size(atags);
	num_pages = mem_size / PAGE_SIZE;

	/* Allocate space for all those pages' metadata.
	 * Start this block just after the stack. */
	page_array_len = sizeof(page_t) * num_pages;
	all_pages_array = (page_t *)((uint32_t)&__end + KERNEL_STACK_SIZE);
	memset(all_pages_array, 0, page_array_len);
	INITIALIZE_LIST(free_pages);

	/* Find where the page metadata ends and round up to the nearest page. */
	page_array_end = (uint32_t)all_pages_array + page_array_len;
	page_array_end += page_array_end % PAGE_SIZE ? PAGE_SIZE - (page_array_end % PAGE_SIZE) : 0;

	/* Iterate over all pages and mark them with the appropriate flags.
	 * Start with kernel pages, stacks, and page metadata. */
	kernel_pages = (page_array_end) / PAGE_SIZE;
	for (i = 0; i < kernel_pages; i++) {
		all_pages_array[i].vaddr_mapped = i * PAGE_SIZE;    /* Identity map the kernel pages. */
		all_pages_array[i].flags.allocated = 1;
		all_pages_array[i].flags.kernel_page = 1;
	}
	/* Reserve 1 MB for the kernel heap. */
	for (; i < kernel_pages + (KERNEL_HEAP_SIZE / PAGE_SIZE); i++) {
		all_pages_array[i].vaddr_mapped = i * PAGE_SIZE;    /* Identity map the kernel heap pages. */
		all_pages_array[i].flags.allocated = 1;
		all_pages_array[i].flags.kernel_heap_page = 1;
	}
	/* Map the rest of the pages as unallocated, and add them to the free list. */
	for (; i < num_pages; i++) {
		all_pages_array[i].flags.allocated = 0;
		append_page_list(&free_pages, &all_pages_array[i]);
	}

	/* Initialize the heap. */
	heap_init(page_array_end);
	return;
}

/* Allocates a page. */
void * alloc_page (void)
{
	page_t * page;
	void * page_mem;

	/* If no free pages, return 0. */
	if (size_page_list(&free_pages) == 0)
		return 0;

	/* Pop a free page. */
	page = pop_page_list(&free_pages);
	page->flags.kernel_page = 1;
	page->flags.allocated = 1;

	/* Get the address the physical page metadata refers to. */
	page_mem = (void *)((page - all_pages_array) * PAGE_SIZE);

	/* Zero out the page. */
	memset(page_mem, 0, PAGE_SIZE);

	/* Return a pointer to the page. */
	return page_mem;
}

/* Frees a page. */
void free_page (void * ptr)
{
    page_t * page;

    /* Get page metadata from the physical address. */
    page = all_pages_array + ((uint32_t)ptr / PAGE_SIZE);

    /* Mark the page as free. */
    page->flags.allocated = 0;
    append_page_list(&free_pages, page);

    return;
}

static void heap_init(uint32_t heap_start) {
	heap_segment_list_head = (heap_segment_t *) heap_start;
	memset(heap_segment_list_head, 0, sizeof(heap_segment_t));
	heap_segment_list_head->segment_size = KERNEL_HEAP_SIZE;
}

/* Implement kmalloc as a linked list of allocated segments.
 * Uses best fit algorithm, segments are 4B aligned. */
void * kmalloc(uint32_t bytes)
{
	heap_segment_t * curr, *best = NULL;
	int diff, best_diff = 0x7fffffff;

	/* Add the header to the number of bytes we need and make the size 16 byte aligned. */
	bytes += sizeof(heap_segment_t);
	bytes += bytes % 16 ? 16 - (bytes % 16) : 0;

	/* Find the allocation that is closest in size to this request. */
	for (curr = heap_segment_list_head; curr != NULL; curr = curr->next) {
		diff = curr->segment_size - bytes;
		if (!curr->is_allocated && diff < best_diff && diff >= 0) {
			best = curr;
			best_diff = diff;
		}
	}

	/* No free memory. */
	if (best == NULL)
		return NULL;

	/* If the best difference we could come up with was large, split up this segment into two.
	 * Since our segment headers are rather large, the criterion for splitting the segment is that
	 * when split, the segment not being requested should be twice a header size. */
	if (best_diff > (int)(2 * sizeof(heap_segment_t))) {
		memset(((void*)(best)) + bytes, 0, sizeof(heap_segment_t));
		curr = best->next;
		best->next = ((void*)(best)) + bytes;
		best->next->next = curr;
		best->next->prev = best;
		best->next->segment_size = best->segment_size - bytes;
		best->segment_size = bytes;
	}

	best->is_allocated = 1;

	return best + 1;
}

/* Frees memory. */
void kfree (void *ptr)
{
	heap_segment_t * seg;

	if (!ptr)
		return;

	/* Free the memory. */
	seg = ptr - sizeof(heap_segment_t);
	seg->is_allocated = 0;

	/* try to coalesce segments to the left. */
	while(seg->prev != NULL && !seg->prev->is_allocated) {
		seg->prev->next = seg->next;
		seg->next->prev = seg->prev;
		seg->prev->segment_size += seg->segment_size;
		seg = seg->prev;
	}
	/* try to coalesce segments to the right. */
	while(seg->next != NULL && !seg->next->is_allocated) {
		seg->segment_size += seg->next->segment_size;
		if (seg->next->next != NULL) {
			seg->next->next->prev = seg;
		}
		seg->next = seg->next->next;
	}
	return;
}
