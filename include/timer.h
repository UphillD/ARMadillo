#ifndef TIMER_H
#define TIMER_H

#include "common/types.h"

#define SYSTEM_TIMER_OFFSET 0x3000
#define PERIPHERAL_BASE 0x20000000

#define SYSTEM_TIMER_BASE (SYSTEM_TIMER_OFFSET + PERIPHERAL_BASE)

void timer_init(void);

void timer_set(uint32_t usecs);

void udelay(uint32_t usecs);

typedef struct {
    uint8_t timer0_matched: 1;
    uint8_t timer1_matched: 1;
    uint8_t timer2_matched: 1;
    uint8_t timer3_matched: 1;
    uint32_t reserved: 28;
} timer_control_reg_t;

typedef struct {
    timer_control_reg_t control;
    uint32_t counter_low;
    uint32_t counter_high;
    uint32_t timer0;
    uint32_t timer1;
    uint32_t timer2;
    uint32_t timer3;
} timer_registers_t;

void sleep (uint32_t);

#endif
