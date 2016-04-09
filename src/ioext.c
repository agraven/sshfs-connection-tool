#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "ioext.h"
int msprintf(char **strp, const char *fmt, ...) {
	int length;
	va_list ap;
	va_start(ap, fmt);
	length = vmsprintf(strp, fmt, ap);
	va_end(ap);
	return(length);
}
int vmsprintf(char **strp, const char *fmt, va_list ap) {
	int length = -1, size;

	va_list ap2;
	va_copy(ap2, ap);

	size = vsnprintf(NULL, 0, fmt, ap2);

	if ((size >= 0) && (size < INT_MAX)) {
		*strp = (char *)malloc(size+1);
		if (*strp) {
			length = vsnprintf(*strp, size+1, fmt, ap);
			if ((length < 0) || (length > size)) {
				mfree(*strp);
				length = -1;
			}
		}
    }
	else { *strp = NULL; }

	va_end(ap2);

	return(length);
}
