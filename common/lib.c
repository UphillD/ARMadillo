/*
 * ARMadillo/common/lib.c
 *
 * Provides any required miscellaneous functionality.
 *
 */

#include "common/lib.h"
#include "common/types.h"

/* Returns the minimum of two numbers. */
int min (int int1, int int2) {
	if (int1 < int2)
		return int1;
	else
		return int2;
}

/* Returns the maximum of two numbers. */
int max (int int1, int int2) {
	if (int1 < int2)
		return int2;
	else
		return int1;
}

/* Turns integer into string. */
char * itoa (int i)
{
	static char intbuf[12];
	int j = 0;
	int isneg = 0;

	if (i == 0) {
		intbuf[0] = '0';
		intbuf[1] = '\0';
		return intbuf;
	}

	if (i < 0) {
		isneg = 1;
		i = -i;
	}

	while (i != 0) {
		intbuf[j++] = '0' + (i % 10);
		i /= 10;
	}

	if (isneg) {
		intbuf[j++] = '-';
	}

	intbuf[j] = '\0';
	j--;
	i = 0;
	while (i < j) {
		isneg = intbuf[i];
		intbuf[i] = intbuf[j];
		intbuf[j] = isneg;
		i++;
		j--;
	}

	return intbuf;
}

/* Turns string into integer. */
int atoi (char * str)
{
	int res = 0, power = 0;
	int digit, i;
	char * start = str;

	/* Find the end of the number. */
	while (*str >= '0' && *str <= '9')
		str++;

	str--;

	while (str != start) {
		digit = *str - '0';
		for (i = 0; i < power; i++) {
			digit *= 10;
		}
		res += digit;
		power++;
		str--;
	}

	return res;
}

uint32_t float_mul (uint32_t c, float f)
{
	return c * f;
}
