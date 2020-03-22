/*
 * ARMadillo/common/string.c
 *
 * Provides string and memory related functionality.
 */

#include "common/types.h"
#include "common/string.h"

/* Sets bytes of memory to value passed in src. */
void memset (void *dst, const uint8_t src, int bytes)
{
	uint8_t *d = dst;
	while (bytes--)
		*d++ = src;
}

/* Copies bytes of memory from src to dest. */
void memcpy (void *dst, const void *src, int bytes)
{
	char *d = dst;
	const char *s = src;
	while (bytes--)
		*d++ = *s++;
}

/* Compares two strings. */
int strcmp (const char *str1, const char *str2)
{
	int i = 0;

	while ((str1[i] == str2[i]) && (str1[i] != '\0'))
		i++;

	return (str1[i] - str2[i]);
}

/* Returns the length of a string. */
size_t strlen (const char *str)
{
	const char *ch;
	ch = str;

	while (*ch)
		ch++;

	return (ch - str);
}

/* Reverses a string (in place). */
void strrev (char *str)
{
	char *rev;
	char tmp;

	rev = str + strlen(str) - 1;
	while (str < rev) {
		tmp = *str;
		*str = *rev;
		*rev = tmp;
		str++;
		rev--;
	}
}
