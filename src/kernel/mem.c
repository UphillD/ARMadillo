#include "common/lib.h"
#include "atag.h"
#include "mem.h"
#include "types.h"

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

void mem_init (atag_t * atags) {
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

	// Map the rest of the pages as unallocated, and add them to the free page list
	for (; i < numPages; i++) {
		pagesArray[i].flags.allocated = 0;
		append_page_list(&freePages, &pagesArray[i]);
	}
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
