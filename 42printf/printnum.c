#include "libft.h"
#include "ft_printf.h"
#include <inttypes.h> 

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

int printintmax_t(format_options options, va_list args, FILE *out)
{
  intmax_t num = va_arg(args, intmax_t);
  char *str = ft_jtoa(num);
  int i = 0;
  int count = 0;
  int strlen = 0;

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, num > 0 ? '+' : '-');
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

int printsize_t(format_options options, va_list args, FILE *out)
{
  size_t num = va_arg(args, size_t);
  char *str = ft_ztoa(num);
  int i = 0;
  int count = 0;
  int strlen = 0;

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, num > 0 ? '+' : '-');
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

int printlonglong(format_options options, va_list args, FILE *out)
{
  long long int num = va_arg(args, long long int);
  char *str = ft_lltoa(num);
  int i = 0;
  int count = 0;
  int strlen = 0;

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, num > 0 ? '+' : '-');
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

int printshort(format_options options, va_list args, FILE *out)
{
  short int shortnum = va_arg(args, int);
  char *str = ft_itoa(shortnum);
  int i = 0;
  int count = 0;
  int strlen = 0;

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, shortnum > 0 ? '+' : '-');
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


int printunsignedint(format_options options, va_list args, FILE *out)
{
  int integer;
  char *str;
  int i = 0;
  int count = 0;
  int strlen = 0;

  if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
      return printlong(options, args, out);

  integer = va_arg(args, unsigned int);

  str = ft_unsigneditoa(integer);

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

int printlongdouble(format_options options, va_list args, FILE *out)
{
  long double n = va_arg(args, long double);
  int precision = 6;
  int strlen = 0;
  int i = 0;
  int count = 0;
  char *str;

  if (options.flags & FLAG_PRECISION)
      precision = options.precision;
  
  if (options.flags & FLAG_ADDHASH)
      str = ft_Lftoa(n, precision, 1);
  else
      str = ft_Lftoa(n, precision, 0);

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
