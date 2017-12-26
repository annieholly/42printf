#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE_COUNT 52
#define FORMAT_MODE 1
#define NORMAL_MODE 0

void ft_putchar_fd(FILE *fd, char c)
{
  write(1, &c, 1);
}

void printstring(int flags, int width, int precision, int length, const char* string, FILE *out)
{
  int i;
  i = 0;
  while (string[i] != '\0')
  {
    ft_putchar_fd(out, string[i]);
    i++;
  }

}  

int hash(const char *c)
{
  return atoi(c) % TYPE_COUNT;
}

/*
void inittypes(void (*types))
{
    types[hash("s")] = printstring;
}
*/

void ahprintf(FILE *out, const char *format, va_list args)
{
  void (*types[TYPE_COUNT])(int, int, int, int, const char*, FILE *);
  char ch;
  int i;
  int state;

  i = 0;
  state = NORMAL_MODE;
  //inittypes(types);
  types[hash("s")] = printstring;
  ch = format[i];
  while (ch != '\0')
  {
    if (state == NORMAL_MODE && ch == '%')
      {
	state = FORMAT_MODE;
      }
    else if (state == FORMAT_MODE && ch == '%')
      {
	ft_putchar_fd(out, ch);
	state = NORMAL_MODE; 
      }
    else if (state == FORMAT_MODE && ch == 's')
      {
	types[hash(&ch)](0, 0, 0, 0, va_arg(args, const char*), out);
	state = NORMAL_MODE;
      }
    else if (state == NORMAL_MODE)
      {
	ft_putchar_fd(out, ch);
      }
    i++;
  }
}
