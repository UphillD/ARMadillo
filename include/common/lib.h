#ifndef LIB_H
#define LIB_H

#include "common/types.h"

int min (const int, const int);
int max (const int, const int);

char * itoa (int);
int atoi (const char *);

uint32_t fpu_mult (uint32_t, float);

#endif
