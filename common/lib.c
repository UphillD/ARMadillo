/*
 * ARMadillo/common/lib.c
 *
 * Provides any required miscellaneous functionality.
 *
 */

#include "common/lib.h"
#include "common/types.h"

/* Zeroes out bytes starting at dest. */
void bzero (void * dest, int bytes)
{
	char * d = dest;
	while (bytes--) {
		*d++ = 0;
	}
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
int atoi (char * num)
{
	int res = 0, power = 0, digit, i;
	char * start = num;

	/* Find the end of the number. */
	while (*num >= '0' && *num <= '9')
		num++;

	num--;

	while (num != start) {
		digit = *num - '0';
		for (i = 0; i < power; i++) {
			digit *= 10;
		}
		res += digit;
		power++;
		num--;
	}

	return res;
}
