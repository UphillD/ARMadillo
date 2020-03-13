/*
 * ARMadillo/common/string.c
 *
 * Implements any required string-related functionality
 *
 */

#include "common/string.h"

/* Compares two strings. */
int strcmp (char * str1, char * str2)
{
	int i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0')
		i++;

	return (str1[i] - str2[i]);
}
