#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE_COUNT 52
#define FORMAT_MODE 1
#define NORMAL_MODE 0
#define FLAG_MODE 2
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



void ft_putchar_file(FILE *fd, char c)
{
  write(fileno(fd), &c, sizeof(char));
}


void printstring(int flags, int width, int precision, int length, void *param, FILE *out)
{
  int i;
  char *string = (char *)param;
  i = 0;
  while (string[i] != '\0')
  {
    ft_putchar_file(out, string[i]);
    i++;
  }

}

void printint(int flags, int width, int precision, int length, void *param, FILE *out)
{
  int *integer = (int *)param;
  char *str = ft_itoa(*integer);
  int i = 0;
  if (flags & FLAG_ADDSIGN)
    ft_putchar_file(out, *integer > 0 ? '+' : '-');
  if (flags & FLAG_ADDSPACE)
    ft_putchar_file(out, ' ');
  while (str[i] != '\0')
    {
      ft_putchar_file(out, str[i]);
      i++;
    }

  free(str);
}

int hash(const char *c)
{
  return *c % TYPE_COUNT;
}


void inittypes(void (*types[])(int, int, int, int, void*, FILE *))
{
  types[hash("s")] = (void *)printstring;
  types[hash("d")] = (void *)printint;
}

int ahprintf(FILE *out, const char *format, va_list args)
{
  void (*types[TYPE_COUNT])(int, int, int, int, void*, FILE *);
  char ch;
  int i;
  int state;
  int flags;

  i = 0;
  state = NORMAL_MODE;
  inittypes(types);
  ch = format[i];
  flags = 0;
  while (ch != '\0')
  {

    if (state == NORMAL_MODE && ch == '%')
      {
	state = FORMAT_MODE;
      }
    else if (state == FORMAT_MODE && ch == '%')
      {
	ft_putchar_file(out, ch);
	state = NORMAL_MODE;
      }
    else if (state == FORMAT_MODE && ch == 's')
      {
	const char *param = va_arg(args, const char*);
	types[hash(&ch)](flags, 0, 0, 0, (void *)param, out);
	flags = 0;
	state = NORMAL_MODE;
      }
    else if (state == FORMAT_MODE && ch == 'd')
      {
    	int param = va_arg(args, int);
    	types[hash(&ch)](flags, 0, 0, 0, &param, out);
	flags = 0;
	state = NORMAL_MODE;
      }
    else if (state == NORMAL_MODE)
      {
	ft_putchar_file(out, ch);
      }
    else if (state == FORMAT_MODE && ch == FLAG_MINUS)
      {
	flags = flags | FLAG_LEFTALIGN;
      }
    else if (state == FORMAT_MODE && ch == FLAG_PLUS)
      {
	flags = flags | FLAG_ADDSIGN;
      }
    else if (state == FORMAT_MODE && ch == FLAG_SPACE)
      {
	flags = flags | FLAG_ADDSPACE;
      }
    else if (state == FORMAT_MODE && ch == FLAG_ZERO)
      {
	flags = flags | FLAG_ADDZERO;
      }
      i++;
    ch = format[i];
  }
  ft_putchar_file(out, '\0');
  return i;
}
