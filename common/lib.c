/*
 * ARMadillo/common/lib.c
 *
 * Provides any required generic functionality.
 *
 */

#include "common/lib.h"
#include "common/string.h"
#include "common/types.h"

/* Returns the minimum of two numbers. */
int min (const int int1, const int int2)
{
	if (int1 < int2)
		return int1;
	else
		return int2;
}

/* Returns the maximum of two numbers. */
int max (const int int1, const int int2)
{
	if (int1 < int2)
		return int2;
	else
		return int1;
}

/* Turns integer into string. */
char * itoa (int n)
{
	static char str[12];
	int i = 0;

	bool neg = (n < 0);

	do {
		str[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (neg)
		str[i++] = '-';

	str[i] = '\0';
	strrev(str);

	return str;
}

/* Turns string into integer. */
int atoi (const char * str)
{
	int n = 0;
	int i = 0;

	while (str[i] && (str[i] >= '0' && str[i] <= '9')) {
		n = n * 10 + (str[i] - '0');
		i++;
	}

	return n;
}

/* Performs a multiplication between an unsigned int and a float.
 * Utilizes the floating coprocessor. Has to be a separate function,
 * otherwise the compiler just optimizes it away. */
uint32_t fpu_mult (uint32_t c, float f)
{
	return c * f;
}
