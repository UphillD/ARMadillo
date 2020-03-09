#ifndef HEARTBEAT_H
#define HEARTBEAT_H

enum {
	GPFSEL3	= 0x2020000C,
	GPFSEL4	= 0x20200010,
	GPSET1	= 0x20200020,
	GPCLR1	= 0x2020002C,
};

void init_led (void);
void heartbeat (void);

#endif
