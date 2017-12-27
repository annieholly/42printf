#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int ahprintf(FILE *out, const char *format, va_list args);
int ft_printf(const char *format, ...);



#endif
