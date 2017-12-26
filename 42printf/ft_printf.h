#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void ahprintf(FILE *out, const char *format, va_list args);
void ft_putchar(char c);



#endif
