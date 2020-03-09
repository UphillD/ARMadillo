extern unsigned int GET32 (unsigned int);
extern unsigned int PUT32 (unsigned int, unsigned int);

#define GPFSEL1		0x20200004
#define GPSET0		0x2020001C
#define GPCLR0		0x20200028
#define GPPUD		0x20200094
#define GPPUDCLK0	0x20200098

#define AUX_ENABLES     0x20215004
#define AUX_MU_IO_REG   0x20215040
#define AUX_MU_IER_REG  0x20215044
#define AUX_MU_IIR_REG  0x20215048
#define AUX_MU_LCR_REG  0x2021504C
#define AUX_MU_MCR_REG  0x20215050
#define AUX_MU_LSR_REG  0x20215054
#define AUX_MU_MSR_REG  0x20215058
#define AUX_MU_SCRATCH  0x2021505C
#define AUX_MU_CNTL_REG 0x20215060
#define AUX_MU_STAT_REG 0x20215064
#define AUX_MU_BAUD_REG 0x20215068

void uart_putc (unsigned int ch)
{
	while (1) {
		if (GET32(AUX_MU_LSR_REG)&0x20) break;
	}
	PUT32(AUX_MU_IO_REG, ch);
}

unsigned int uart_getc (void)
{
	while (1) {
		if(GET32(AUX_MU_LSR_REG)&0x01) break;
	}

	return GET32(AUX_MU_IO_REG);
}

void uart_init (void)
{
	unsigned int ra;

	PUT32(AUX_ENABLES, 1);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_CNTL_REG, 0);
	PUT32(AUX_MU_LCR_REG, 3);
	PUT32(AUX_MU_MCR_REG, 0);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_IIR_REG, 0xC6);
	PUT32(AUX_MU_BAUD_REG, 270);

	ra = GET32(GPFSEL1);
	ra &= ~(7 << 12); //gpio14
	ra |= 2 << 12;    //alt5
	ra &= ~(7 << 15); //gpio15
	ra |= 2 << 15;    //alt5
	PUT32(GPFSEL1, ra);

	PUT32(AUX_MU_CNTL_REG,3);
}

void uart_printhex (unsigned int hex)
{
	unsigned int i;
	unsigned int out;

	i = 32;
	while (1)
	{
		i -= 4;
		out = (hex >> i)&0xF;
		if (out > 9) {
			out += 0x37;
		} else {
			out += 0x30;
		}
		uart_putc(out);
		if (i == 0) break;
	}
	uart_putc(0x20);
	return;
}
