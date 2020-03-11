#ifndef TIMER_H
#define TIMER_H

#include "common/stdint.h"

enum {
	SYSTIMER = 0x20003004
};

void sleep (uint32_t);

#endif
