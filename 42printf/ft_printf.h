#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#define TYPE_COUNT 127
#define NORMAL_MODE 0
#define FORMAT_MODE 1
#define FLAG_ZERO_MODE 2
#define PRECISION_MODE 3
#define LENGTH_MODE 4
#define WIDTH_MODE 5
#define LENGTH_CHAR 'h'
#define LENGTH_LONG 'l'
#define LENGTH_DOUBLE 'L'
#define LENGTH_SIZET 'z'
#define LENGTH_INTMAX 'j'
#define LENGTH_PTR 't'
#define PRECISION_DOT '.'
#define FLAG_MINUS '-'
#define FLAG_PLUS '+'
#define FLAG_SPACE ' '
#define FLAG_ZERO '0'
#define FLAG_HASH '#'
#define FLAG_LEFTALIGN 1
#define FLAG_ADDSIGN 2
#define FLAG_ADDSPACE 4
#define FLAG_ADDZERO 8
#define FLAG_ADDHASH 16
#define FLAG_PRECISION 32
#define FLAG_WIDTH 64


typedef struct s_format
{
    int     flags;
    int     width;
    int     precision;
    char    length[3];
    char    type;
    int     chcount;
}           format_options;

int ahprintf(FILE *out, const char *format, va_list args);
int ft_printf(const char *format, ...);

void ft_putchar_file(FILE *fd, char c);

int printlong(format_options options, va_list args, FILE *out);
int printlonglong(format_options options, va_list args, FILE *out)
int printshort(format_options options, va_list args, FILE *out);
int printunsignedint(format_options options, va_list args, FILE *out);

int printint(format_options options, va_list args, FILE *out);
int printfloat(format_options options, va_list args, FILE *out);
int printhex(format_options options, va_list args, FILE *out);
int printptr(format_options options, va_list args, FILE *out);
int printoctal(format_options options, va_list args, FILE *out);

int printlongdouble(format_options options, va_list args, FILE *out);

#endif
