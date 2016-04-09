#ifndef IOEXT_H
#define IOEXT_H
#define mfree(p) { free(p); p = NULL; }

int vmsprintf(char **strp, const char *fmt, va_list ap);
int msprintf(char **strp, const char *fmt, ...);
#endif
