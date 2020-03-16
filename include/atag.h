#ifndef ATAG_H
#define ATAG_H

#include "common/types.h"

typedef enum {
	NONE		= 0x00000000,
	CORE		= 0x54410001,
	MEM		= 0x54410002,
	VIDEOTEXT	= 0x54410003,
	RAMDISK		= 0x54410004,
	INITRD2		= 0x54420005,
	SERIAL		= 0x54420006,
	REVISION	= 0x54420007,
	VIDEOLFB	= 0x54420008,
	CMDLINE 	= 0x54410009,
} atag_tag_t;

typedef struct {
	uint32_t size;
	uint32_t start;
} mem_t;

typedef struct {
	uint32_t start;
	uint32_t size;
} initrd2_t;

typedef struct {
	char line[1];
} cmdline_t;

typedef struct atag {
	uint32_t tag_size;
	atag_tag_t tag;
	union {
		mem_t mem;
		initrd2_t initrd2;
		cmdline_t cmdline;
	};
} atag_t;

#endif
