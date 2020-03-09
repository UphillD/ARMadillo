extern void heartbeat (void);

int kernel_main (void)
{
	while (1) {
		heartbeat();
	}
	return 0;
}
