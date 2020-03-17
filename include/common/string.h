#ifndef STRING_H
#define STRING_H

#include "common/types.h"

void memset (void *, uint8_t, int);
void memcpy (void *, const void *, int);

int strcmp (char *, char *);
size_t strlen (const char * str);
void strrev (char *str);

#endif
