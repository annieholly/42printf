#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stddef.h>
//#include <wchar.h>

void ft_putchar_file(FILE *fd, char c)
{
  write(fileno(fd), &c, sizeof(char));
}

void ft_putcharnum_file(FILE *fd, signed char c)
{
  write(fileno(fd), &c, sizeof(signed char));
}

void ft_putwidechar_file(FILE *fd, wchar_t wc)
{
	write(fileno(fd), &wc, sizeof(wchar_t));
}

int printwidechar(format_options options, va_list args, FILE *out) 
{
	int i;
	int wc_int;
	char wc;

	if ((wc_int = va_arg(args, int)) > 255)
		return (-1);
	wc = (char)wc_int;
	ft_putchar_file(out, wc);
	return (1);
}

int ft_wcstrlen(wchar_t *str) 
{
	int i; 
	i = 0;
	while (str[i] != '\0') 
		i++; 
	return (i);
}


int printwidestring(format_options options, va_list args, FILE *out) 
{
	int i;
	wchar_t *wc_string = va_arg(args, wchar_t*);
	int wclen = ft_wcstrlen(wc_string);
	i = 0; 
	while (i < wclen)
	{
		ft_putchar_file(out, wc_string[i]);
		i++;
	}
	return (wclen);
}

int printchar(format_options options, va_list args, FILE *out)
{
	int i; 
	char c;

	if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
		return printwidechar(options, args, out);

	c = va_arg(args, int);
	ft_putchar_file(out, c);
	return (1);
}

int printsignedchar(format_options options, va_list args, FILE *out)
{
	int i; 
	int count;
	char c;
	char *str;

	count = 0;
	c = va_arg(args, int);
	str = ft_itoa(c);

	i = 0;
	while (str[i] != '\0')
    {
      ft_putchar_file(out, str[i]);
      i++;
      count++;
    }
	free(str);
	return (count);
}

int printstring(format_options options, va_list args, FILE *out)
{
	int i;
	char *string;
	int strlen;

	if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
		return printwidestring(options, args, out);

	i = 0;
	string = va_arg(args, char*);
	strlen = ft_strlen(string);
  if (options.flags & FLAG_PRECISION)
    strlen = options.precision;
  while (i < strlen)
  {
    ft_putchar_file(out, string[i]);
    i++;
  }
  return strlen;
}

int printint(format_options options, va_list args, FILE *out)
{
	int integer;
	char *str;
	int i = 0;
	int count = 0;
	int strlen = 0;
	int width_rem = 0;
	int intlen = 0;
	int precision_rem = 0;


	if (ft_strlen(options.length) == 1 && options.length[0] == 'h')
		return printshort(options, args, out);

	if (ft_strlen(options.length) == 2 && options.length[1] == 'h')
		return printsignedchar(options, args, out);

	if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
		return printlong(options, args, out);

	if (ft_strlen(options.length) == 2 && options.length[1] == 'l')
		return printlonglong(options, args, out);

	if (ft_strlen(options.length) == 1 && options.length[0] == 'j')
		return printintmax_t(options, args, out);

	if (ft_strlen(options.length) == 1 && options.length[0] == 'z')
		return printsize_t(options, args, out);

	integer = va_arg(args, int);
	str = ft_itoa(integer);
	intlen = ft_strlen(str);
	precision_rem = options.precision - intlen;

	if (options.flags & FLAG_WIDTH) 
	{
		if (options.width > intlen) 
		{
			width_rem = options.width - intlen;
			while (width_rem > 0) 
			{
				ft_putchar_file(out, ' ');
				width_rem--;
				count++;
			}
		}
	}

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
		if (options.flags & FLAG_PRECISION)
		{
			i = 0;
			width_rem = options.width - options.precision; 
			while (width_rem > 0) 
			{
				ft_putchar_file(out, ' ');
				width_rem--;
				count++;
			}
		}
		while (i > 0)
		{
			ft_putchar_file(out, '0');
			i--;
			count++;
		}
	}
 

  if (options.flags & FLAG_PRECISION) 
  {
	  while (precision_rem > 0)
	  {
		  ft_putchar_file(out, '0');
		  precision_rem--;
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


  if (ft_strlen(options.length) == 1 && options.length[0] == 'L')
      return printlongdouble(options, args, out);

  if (options.flags & FLAG_PRECISION)
      precision = options.precision;
  
  if (options.flags & FLAG_ADDHASH)
      str = ft_ftoa(n, precision, 1);
  else
      str = ft_ftoa(n, precision, 0);

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

int printhex(format_options options, va_list args, FILE *out)
{
  int integer;
  char *str;
  int i = 0;
  int count = 0;
  int strlen = 0;
  int upper = 0;
  int prepend = 0;

  if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
      return printlong(options, args, out);

  integer = va_arg(args, int);
  if (options.type == 'X')
    upper = 1;
  if (options.flags & FLAG_ADDHASH)
    prepend = 1;
  str = ft_itohex(integer, upper, prepend);

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
  if (options.flags & FLAG_ADDHASH)
    {
      
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

int printptr(format_options options, va_list args, FILE *out)
{
  int integer;
  char *str;
  int i = 0;
  int count = 0;
  int strlen = 0;
  int upper = 0;
  int prepend = 0;

  if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
      return printlong(options, args, out);

  void *ptr;
  ptr = va_arg(args, void *);

  unsigned long long int ptr_num; 
  ptr_num = (unsigned long long int)ptr;

  if (options.type == 'X')
    upper = 1;

  if (options.flags & FLAG_ADDHASH)
    prepend = 1;
  str = ft_uitohex(ptr_num, upper, 1);

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
  if (options.flags & FLAG_ADDHASH)
    {
      
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



int printoctal(format_options options, va_list args, FILE *out)
{
  unsigned int output;
  char *str;
  int i = 0;
  int count = 0;
  int strlen = 0;
  int upper = 0;
  int prepend = 0;

  if (ft_strlen(options.length) == 1 && options.length[0] == 'l')
      output = va_arg(args, unsigned long int);
  else
	  output = va_arg(args, int);

  if (options.flags & FLAG_ADDHASH)
    prepend = 1;

  str = ft_itooct((int)output);

  if (options.flags & FLAG_ADDSIGN)
    {
      ft_putchar_file(out, output > 0 ? '+' : '-');
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
  if (options.flags & FLAG_ADDHASH)
    {
      
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


int printn(format_options options, va_list args, FILE *out)
{
  int *ptr;
  ptr = va_arg(args, int*);
  *ptr = options.chcount;
  return (0);
}


int hash(const char *c)
{
  return *c;
}

void inittypes(int (*types[])(format_options, va_list, FILE *))
{
	types[hash("c")] = printchar;
	types[hash("C")] = printwidechar;
	types[hash("s")] = printstring;
	types[hash("S")] = printwidestring;
	types[hash("p")] = printptr;
	types[hash("d")] = printint;
	types[hash("D")] = printlong;
	types[hash("i")] = printint;
	types[hash("o")] = printoctal;
	types[hash("O")] = printoctal;
	types[hash("u")] = printunsignedint;
	types[hash("U")] = printunsignedint;
	types[hash("f")] = printfloat;
	types[hash("x")] = printhex;
	types[hash("X")] = printhex;
	types[hash("n")] = printn;
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
		
		if (state == WIDTH_MODE && ft_isdigit(ch) == 0)
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
			options.type = ch;
			options.chcount = count;
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
			options.flags = options.flags | FLAG_LEFTALIGN;

		else if (state == FORMAT_MODE && ch == FLAG_PLUS)
			options.flags = options.flags | FLAG_ADDSIGN;

		else if (state == FORMAT_MODE && ch == FLAG_SPACE)
			options.flags = options.flags | FLAG_ADDSPACE;

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
/*
		else if (state == WIDTH_MODE && ft_isdigit(ch))
		{
			printf("in width mode \n");
			startdigit++;
		}
*/
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
			//startdigit++;
		}

		else if (state == FORMAT_MODE && ch == FLAG_HASH)
		{
			options.flags = options.flags | FLAG_ADDHASH;
		}

		else if (state == FORMAT_MODE && ft_isdigit(ch) && ch != '0')
		{
			state = WIDTH_MODE;
			options.flags = options.flags | FLAG_WIDTH;
			startdigit = i;
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
