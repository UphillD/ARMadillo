#ifndef TIMER_H
#define TIMER_H

#include "common/types.h"

void sleep (uint32_t);

void timer_set (uint32_t);
void timer_init (void);

void scheduler (uint32_t);
void scheduler_init (void);

struct timer_control_reg_t {
	uint8_t timer0_matched: 1;
	uint8_t timer1_matched: 1;
	uint8_t timer2_matched: 1;
	uint8_t timer3_matched: 1;
	uint32_t reserved: 28;
};

struct timer_registers_t {
	struct timer_control_reg_t control;
	uint32_t counter_low;
	uint32_t counter_high;
	uint32_t timer0;
	uint32_t timer1;
	uint32_t timer2;
	uint32_t timer3;
};

#endif
