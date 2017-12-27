#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE_COUNT 127
#define FORMAT_MODE 1
#define NORMAL_MODE 0
#define FLAG_ZERO_MODE 2
#define PRECISION_MODE 3
#define LENGTH_MODE 4
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

typedef struct s_format
{
  int flags;
  int width;
  int precision;
  char length[3];
} format_options;

void ft_putchar_file(FILE *fd, char c)
{
  write(fileno(fd), &c, sizeof(char));
}


int printstring(format_options options, va_list args, FILE *out)
{
  int i;
  char *string = va_arg(args, char*);
  int strlen = ft_strlen(string);
  i = 0;
  if (options.flags & FLAG_PRECISION)
    strlen = options.precision;
  while (i < strlen)
  {
    ft_putchar_file(out, string[i]);
    i++;
  }
  return strlen;
}


int printlong(format_options options, va_list args, FILE *out)
{
  long int longnum = va_arg(args, long int);
  char *str = ft_ltoa(longnum);
  int i = 0;
  int count = 0;
  int strlen = 0;

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, longnum > 0 ? '+' : '-');
      count++;
    }

  if (options.flags & FLAG_ADDSPACE)
    {
      ft_putchar_file(out, ' ');
      count++;
    }
  if (options.flags & FLAG_ADDZERO)
    {
      strlen = ft_strlen(str);
      i = options.width - strlen;
      while (i > 0)
	{
	  ft_putchar_file(out, '0');
	  i--;
	  count++;
	}
    }
  
  i = 0;
  while (str[i] != '\0')
    {
      ft_putchar_file(out, str[i]);
      i++;
      count++;
    }

  free(str);
  return count;
}



int printint(format_options options, va_list args, FILE *out)
{
  int integer;
  char *str;
  int i = 0;
  int count = 0;
  int strlen = 0;

  if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
    {
      return printlong(options, args, out);
    }

  integer = va_arg(args, int);
  str = ft_itoa(integer);

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, integer > 0 ? '+' : '-');
      count++;
    }

  if (options.flags & FLAG_ADDSPACE)
    {
      ft_putchar_file(out, ' ');
      count++;
    }
  if (options.flags & FLAG_ADDZERO)
    {
      strlen = ft_strlen(str);
      i = options.width - strlen;
      while (i > 0)
	{
	  ft_putchar_file(out, '0');
	  i--;
	  count++;
	}
    }
  
  i = 0;
  while (str[i] != '\0')
    {
      ft_putchar_file(out, str[i]);
      i++;
      count++;
    }

  free(str);
  return count;
}

int printfloat(format_options options, va_list args, FILE *out)
{
  float n = (float)va_arg(args, double);
  int precision = 6;
  int strlen = 0;
  int i = 0;
  int count = 0;
  char *str;

  if (options.flags & FLAG_PRECISION)
    {
      precision = options.precision;
    }

  if (options.flags & FLAG_ADDHASH)
    {
      str = ft_ftoa(n, precision, 1);
    }
  else
    {
      str = ft_ftoa(n, precision, 0);
    }
  
  strlen = ft_strlen(str);

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, n > 0 ? '+' : '-');
      count++;
    }

  if (options.flags & FLAG_ADDSPACE)
    {
      ft_putchar_file(out, ' ');
      count++;
    }

  if (options.flags & FLAG_ADDZERO)
    {
      i = options.width - strlen;
      while (i > 0)
	{
	  ft_putchar_file(out, '0');
	  i--;
	  count++;
	}
    }

  
  i = 0;
  while (i < strlen)
    {
      ft_putchar_file(out, str[i]);
      i++;
      count++;
    }
  free(str);
  return count;
}

int hash(const char *c)
{
  return *c;
}


void inittypes(int (*types[])(format_options, va_list, FILE *))
{
  types[hash("s")] = printstring;
  types[hash("d")] = printint;
  types[hash("f")] = printfloat;
}

int islengthmod(char ch)
{
  if (ch == LENGTH_CHAR || ch == LENGTH_LONG || ch == LENGTH_DOUBLE ||
      ch == LENGTH_SIZET || ch == LENGTH_INTMAX || ch == LENGTH_PTR)
    return (1);
  return (0);
}

int ahprintf(FILE *out, const char *format, va_list args)
{
  int (*types[TYPE_COUNT])(format_options, va_list, FILE *) = {0};
  char ch;
  int i;
  int count = 0;
  int state;
  format_options options = {0};
  int startdigit = 0;
  int (*typefunc)(format_options, va_list, FILE *) = 0;

  i = 0;
  state = NORMAL_MODE;
  inittypes(types);
  ch = format[i];
  while (ch != '\0')
  {
    if (state == FLAG_ZERO_MODE && ft_isdigit(ch) == 0)
      {
	options.width = ft_atoin(&format[startdigit], i);
	state = FORMAT_MODE;
      }
    if (state == PRECISION_MODE && ft_isdigit(ch) == 0)
      {
	options.precision = ft_atoin(&format[startdigit], i);
	options.flags = options.flags | FLAG_PRECISION;
	state = FORMAT_MODE;
      }
    if (state == LENGTH_MODE && islengthmod(ch) == 0)
      {
	options.length[0] = format[startdigit];
	if ((i - startdigit) > 1)
	  {
	    options.length[1] = format[startdigit + 1];
	    options.length[2] = '\0';
	  }
	else
	  options.length[1] = '\0';

	state = FORMAT_MODE;
      }
    if (state == NORMAL_MODE && ch == '%')
      {
	state = FORMAT_MODE;
      }
    else if (state == FORMAT_MODE && ch == '%')
      {
	ft_putchar_file(out, ch);
	state = NORMAL_MODE;
      }
    else if (state == FORMAT_MODE && (typefunc = types[hash(&ch)]) != 0)
      {
	count += typefunc(options, args, out);
	options = (format_options){0};
	state = NORMAL_MODE;
      }
    else if (state == NORMAL_MODE)
      {
	ft_putchar_file(out, ch);
	count++;
      }
    else if (state == FORMAT_MODE && ch == FLAG_MINUS)
      {
	options.flags = options.flags | FLAG_LEFTALIGN;
      }
    else if (state == FORMAT_MODE && ch == FLAG_PLUS)
      {
	options.flags = options.flags | FLAG_ADDSIGN;
      }
    else if (state == FORMAT_MODE && ch == FLAG_SPACE)
      {
	options.flags = options.flags | FLAG_ADDSPACE;
      }
    else if (state == FORMAT_MODE && ch == FLAG_ZERO)
      {
	options.flags = options.flags | FLAG_ADDZERO;
	state = FLAG_ZERO_MODE;
	startdigit = i;
      }
    else if (state == FLAG_ZERO_MODE && ch == ft_isdigit(ch))
      {
	startdigit++;
      }
    else if (state == FORMAT_MODE && ch == PRECISION_DOT)
      {
	state = PRECISION_MODE;
	startdigit = i + 1; //test to check if there's a digit
      }
    else if (state == PRECISION_MODE && ch == ft_isdigit(ch))
      {
	startdigit++;
      }
    else if (state == FORMAT_MODE && islengthmod(ch))
      {
	state = LENGTH_MODE;
	startdigit = i;
      }
    else if (state == LENGTH_MODE && islengthmod(ch))
      {
	//may need to check for char length - max is 2
	startdigit++;
      }
    else if (state == FORMAT_MODE && ch == FLAG_HASH)
      {
	options.flags = options.flags | FLAG_ADDHASH;
      }
      i++;
    ch = format[i];
  }
  ft_putchar_file(out, '\0');
  return count;
}

int ft_printf(const char * format, ...)
{
  va_list args;
  va_start(args, format);
  return ahprintf(stdout, format, args);
}
