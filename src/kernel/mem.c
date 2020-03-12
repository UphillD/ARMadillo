#include "common/lib.h"
#include "atag.h"
#include "mem.h"
#include "common/types.h"

static void heap_init (uint32_t heapStart);
/**
 * impliment kmalloc as a linked list of allocated segments.
 * Segments should be 4 byte aligned.
 * Use best fit algorithm to find an allocation
 */

typedef struct heap_segment {
    struct heap_segment * next;
    struct heap_segment * prev;
    uint32_t isAllocated;
    uint32_t segmentSize;  // Includes this header
} heap_segment_t;

static heap_segment_t * heapSegmentList_head;

/**
 * End Heap Stuff
 */

extern uint8_t __end;
static uint32_t numPages;

define_list(page);
implement_list(page);

static page_t * pagesArray;
page_list_t freePages;

uint32_t mem_getSize (atag_t * tag)
{
	while (tag->tag != NONE) {
		if (tag->tag == MEM) {
			return tag->mem.size;
		}
		tag = (atag_t *)(((uint32_t *)tag) + tag->tagSize);
	}

	return 0;
}

void mem_init (atag_t * atags)
{
	uint32_t i;

	//Get the total number of pages
	uint32_t memSize = mem_getSize(atags);
	numPages = memSize / PAGE_SIZE;

	// Allocate space for all those pages' metadata.
	// Start this block after the kernel image
	uint32_t pageArrayLen = sizeof(page_t) * numPages;
	pagesArray = (page_t *)&__end;
	bzero(pagesArray, pageArrayLen);
	init_list(freePages);

	// Iterate over all pages and mark them with the appropriate flags.

	// Start with the kernel pages
	uint32_t kernelPages = ((uint32_t)&__end) / PAGE_SIZE;
	for (i = 0; i < kernelPages; i++) {
		pagesArray[i].vaddr_mapped = i * PAGE_SIZE;
		pagesArray[i].flags.allocated = 1;
		pagesArray[i].flags.kernelPage = 1;
	}

	// Continue with the kernel heap
	for (; i < kernelPages + (KERNEL_HEAP_SIZE / PAGE_SIZE); i++) {
		pagesArray[i].vaddr_mapped = i * PAGE_SIZE;
		pagesArray[i].flags.allocated = 1;
		pagesArray[i].flags.kernelHeapPage = 1;
	}

	// Map the rest of the pages as unallocated, and add them to the free page list
	for (; i < numPages; i++) {
		pagesArray[i].flags.allocated = 0;
		append_page_list(&freePages, &pagesArray[i]);
	}

	// Initialize the kernel heap
	uint32_t pageArrayEnd = (uint32_t)&__end + pageArrayLen;
	heap_init(pageArrayEnd);

	return;
}

void * alloc_page (void)
{
	page_t * page;
	void * pageMem;

	if (size_page_list(&freePages) == 0)
		return 0;

	// Get a free page
	page = pop_page_list(&freePages);
	page->flags.kernelPage = 1;
	page->flags.allocated = 1;

	// Get the address the physical page metadata refers to
	pageMem = (void *)((page - pagesArray) * PAGE_SIZE);

	// Zero out the page, big security flaw to not do this :)
	bzero(pageMem, PAGE_SIZE);

	return pageMem;
}

void free_page (void * pagePtr)
{
	page_t * page;

	// Get page metadata from the physical address
	page = pagesArray + ((uint32_t)pagePtr / PAGE_SIZE);

	// Mark the page as free
	page->flags.allocated = 0;
	append_page_list(&freePages, page);

	return;
}

static void heap_init (uint32_t heapStart)
{
	heapSegmentList_head = (heap_segment_t *) heapStart;
	bzero(heapSegmentList_head, sizeof(heap_segment_t));
	heapSegmentList_head->segmentSize = KERNEL_HEAP_SIZE;

	return;
}


void * kmalloc (uint32_t bytes) {
	heap_segment_t * curr, *best = NULL;
	int diff, best_diff = 0x7fffffff; // Max signed int

	// Add the header to the number of bytes we need and make the size 4 byte aligned
	bytes += sizeof(heap_segment_t);
	bytes += bytes % 16 ? 16 - (bytes % 16) : 0;

	// Find the allocation that is closest in size to this request
	for (curr = heapSegmentList_head; curr != NULL; curr = curr->next) {
		diff = curr->segmentSize - bytes;
		if (!curr->isAllocated && diff < best_diff && diff >= 0) {
			best = curr;
			best_diff = diff;
		}
	}

	// There must be no free memory right now :(
	if (best == NULL) {
		return NULL;
	}

	// If the best difference we could come up with was large, split up this segment into two.
	// Since our segment headers are rather large, the criterion for splitting the segment is that
	// when split, the segment not being requested should be twice a header size
	if (best_diff > (int)(2 * sizeof(heap_segment_t))) {
		bzero(((void*)(best)) + bytes, sizeof(heap_segment_t));
		curr = best->next;
		best->next = ((void*)(best)) + bytes;
		best->next->next = curr;
		best->next->prev = best;
		best->next->segmentSize = best->segmentSize - bytes;
		best->segmentSize = bytes;
	}

	best->isAllocated = 1;

	return best + 1;
}


void kfree (void *ptr)
{
	heap_segment_t * seg;

	if (!ptr)
		return;

	seg = ptr - sizeof(heap_segment_t);
	seg->isAllocated = 0;

	// try to coalesce segements to the left
	while(seg->prev != NULL && !seg->prev->isAllocated) {
		seg->prev->next = seg->next;
		seg->next->prev = seg->prev;
		seg->prev->segmentSize += seg->segmentSize;
		seg = seg->prev;
	}
	// try to coalesce segments to the right
	while(seg->next != NULL && !seg->next->isAllocated) {
		seg->next->next->prev = seg;
		seg->next = seg->next->next;
		seg->segmentSize += seg->next->segmentSize;
	}
}
