#ifndef ADDR_H
#define ADDR_H

/* ARM Timer */
enum {
	ARM_TIMER_LOD	= 0x2000B400,
	ARM_TIMER_VAL	= 0x2000B404,
	ARM_TIMER_CTL	= 0x2000B408,
	ARM_TIMER_CLI	= 0x2000B40C,
	ARM_TIMER_RIS	= 0x2000B410,
	ARM_TIMER_MIS	= 0x2000B414,
	ARM_TIMER_RLD	= 0x2000B418,
	ARM_TIMER_DIV	= 0x2000B41C,
	ARM_TIMER_CNT	= 0x2000B420,
};

/* Interrupts */
enum {
	IRQ_BASIC	  = 0x2000B200,
	IRQ_PEND1	  = 0x2000B204,
	IRQ_PEND2	  = 0x2000B208,
	IRQ_FIQ_CONTROL	  = 0x2000B210,
	IRQ_ENABLE_BASIC  = 0x2000B218,
	IRQ_DISABLE_BASIC = 0x2000B224,
};

/* GPIO */
enum {
	/* The GPIO registers base address. */
	GPIO_BASE	= 0x20200000,
	GPFSEL1		= 0x20200004,
	GPSET0		= 0x2020001C,
	GPCLR0		= 0x20200028,
	GPFSEL3		= 0x2020000C,
	GPFSEL4		= 0x20200010,
	GPSET1		= 0x20200020,
	GPCLR1		= 0x2020002C,
	/* Controls actuation of pull up/down to all GPIO pins. */
	GPPUD		= 0x20200094,
	/* Controls actuation of pull up/down to specific GPIO pin. */
	GPPUDCLK0	= 0x20200098,
};

/* AUX (UART0) */
enum {
	AUX_BASE	= 0x20215000,
	AUX_ENABLES     = 0x20215004,
	AUX_MU_IO_REG   = 0x20215040,
	AUX_MU_IER_REG  = 0x20215044,
	AUX_MU_IIR_REG  = 0x20215048,
	AUX_MU_LCR_REG  = 0x2021504C,
	AUX_MU_MCR_REG  = 0x20215050,
	AUX_MU_LSR_REG  = 0x20215054,
	AUX_MU_MSR_REG  = 0x20215058,
	AUX_MU_SCRATCH  = 0x2021505C,
	AUX_MU_CNTL_REG = 0x20215060,
	AUX_MU_STAT_REG = 0x20215064,
	AUX_MU_BAUD_REG = 0x20215068,
};

/* SYSTEM TIMER */
enum {
	SYSTEM_TIMER_BASE	= 0x20003000,
	SYSTEM_TIMER_CLOCK	= 0x20003004,
};

#endif
