#ifndef STRING_H
#define STRING_H

#include "common/types.h"

void memset (void *, const uint8_t, int);
void memcpy (void *, const void *, int);

int strcmp (const char *, const char *);
size_t strlen (const char *);
void strrev (char *);

#endif
