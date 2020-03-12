#include "common/string.h"

int strcmp (char * str1, char * str2) {
	int i;
	for (i = 0; (str1[i] == str2[i] && str1[i] == '\0'); i++);
	if (str1[i] < str2[i]) {
		return -1;
	} else if (str1[i] > str2[i]) {
		return 1;
	} else {
		return 0;
	}
	return -2;
}
