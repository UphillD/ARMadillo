/*
 * ARMadillo/common/string.c
 *
 * Provides any required string-related functionality.
 *
 */

#include "common/string.h"

/* Copies bytes of memory from src to dest. */
void memcpy (void * dst, const void * src, int bytes)
{
	char * d = dst;
	const char * s = src;
	while (bytes--)
		*d++ = *s++;
}

/* Compares two strings. */
int strcmp (char * str1, char * str2)
{
	int i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0')
		i++;

	return (str1[i] - str2[i]);
}
