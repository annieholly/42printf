#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>

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
	int		state;
    int     chcount;
}           t_format;

int ahprintf(FILE *out, const char *format, va_list args);
int ft_printf(const char *format, ...);

void ft_putchar_file(FILE *fd, char c);

int islengthmod(char ch);
void inittypes(int (*types[])(t_format, va_list, FILE *));
int hash(const char *c);


int printlong(t_format options, va_list args, FILE *out);
int printlonglong(t_format options, va_list args, FILE *out);
int printintmax_t(t_format options, va_list args, FILE *out);
int printsize_t(t_format options, va_list args, FILE *out);
int printshort(t_format options, va_list args, FILE *out);
int printunsignedint(t_format options, va_list args, FILE *out);

int printint(t_format options, va_list args, FILE *out);
int printfloat(t_format options, va_list args, FILE *out);
int printhex(t_format options, va_list args, FILE *out);
int printptr(t_format options, va_list args, FILE *out);
int printoctal(t_format options, va_list args, FILE *out);

int printlongdouble(t_format options, va_list args, FILE *out);

#endif
