#include "ft_printf.h" 
#include "libft.h" 

int is_special_char(char ch)
{
	if (ch == FLAG_MINUS || ch == FLAG_PLUS || ch == FLAG_SPACE || ch == FLAG_ZERO) 
		return (1); 
	return (0);
}

void set_special_flag(char ch, t_format options, int state)
{
	if (ch == FLAG_MINUS)
		options.flags = options.flags | FLAG_LEFTALIGN;
	else if (ch == FLAG_PLUS)
		options.flags = options.flags | FLAG_ADDSIGN;
	else if (ch == FLAG_SPACE)
		options.flags = options.flags | FLAG_ADDSPACE;
	else if (ch == FLAG_HASH)
		options.flags = options.flags | FLAG_ADDHASH;
	else if (ch == PRECISION_DOT) 
		state = PRECISION_MODE;
	else if (islengthmod(ch))
		state = LENGTH_MODE;
	else if (ch == FLAG_ZERO)
	{
		options.flags = options.flags | FLAG_ADDZERO;
		state = FLAG_ZERO_MODE;
//		startdigit = i;
	}
	else if (ft_isdigit(ch) && ch != '0') 
	{
		options.flags = options.flags | FLAG_WIDTH;
		state = WIDTH_MODE;
	}
}

void width_mode(const char *format, t_format options, int i, int state)
{
	char ch; 
	int startdigit; 

	ch = format[i];
	startdigit = i;
	if (ft_isdigit(ch))
		startdigit++;
	else
	{
		options.width = ft_atoin(&format[startdigit], i);
		state = FORMAT_MODE;
	}
}

void precision_mode(const char *format, t_format options, int i, int state)
{
	char ch; 
	int startdigit; 

	ch = format[i];
	startdigit = i;
	if (ft_isdigit(ch))
		startdigit++;
	else
	{
		options.precision = ft_atoin(&format[startdigit], i);
		options.flags = options.flags | FLAG_PRECISION;
		state = FORMAT_MODE;
	}
}

void length_mode(const char *format, t_format options, int i, int state)
{
	char ch; 
	int startdigit; 

	ch = format[i];
	startdigit = i;
	if (islengthmod(ch))
	{
		options.length[0] = format[startdigit];
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
	}
}


int format_mode(FILE *out, const char *format, va_list args, int i, int state) 
{
	int count;
	int (*types[TYPE_COUNT])(t_format, va_list, FILE *) = {0};
	int (*typefunc)(t_format, va_list, FILE *) = 0;
	static t_format options;
	char ch;
 
	inittypes(types);
	count = 0;
	ch = format[i];
	if (ch == '%') 
	{
		ft_putchar_file(out, ch);
		count++;
		state = NORMAL_MODE;
	}

	else if ((typefunc = types[hash(&ch)]) != 0)
	{
		options.type = ch;
		options.chcount = count;
		count += typefunc(options, args, out);
		options = (format_options){0};
		state = NORMAL_MODE;
	}

	if (is_special_char(ch)) 
		set_special_flag(ch, options, state);


	return (count);
}

int ahprintf(FILE *out, const char *format, va_list args)
{
//	int (*types[TYPE_COUNT])(format_options, va_list, FILE *) = {0};
	char ch; //1?
	int i; //2
	int count = 0; //3
	static int state; //5?
	static t_format options; //4?
//	int startdigit = 0;
//	int (*typefunc)(format_options, va_list, FILE *) = 0;

	i = 0;
	state = NORMAL_MODE;
//	inittypes(types);
	ch = format[i];

	while (ch != '\0')
	{
		/*
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
		*/

		/*
		if (state == PRECISION_MODE && ft_isdigit(ch) == 0)
		{
			options.precision = ft_atoin(&format[startdigit], i);
			options.flags = options.flags | FLAG_PRECISION;
			state = FORMAT_MODE;
		}
		*/
		/*
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
		*/
		if (state == NORMAL_MODE && ch == '%')
			state = FORMAT_MODE;
		else if (state == FORMAT_MODE) 
			format_mode(out, format, args, ch, state);


		/*
		else if (state == FORMAT_MODE)
		{
			options.chcount = count;
			count = format_mode(out, format, args, ch, state);
		}
		*/
		/*
		else if (state == FORMAT_MODE && ch == '%')
		{
			ft_putchar_file(out, ch);
			state = NORMAL_MODE;
		}
		*/

		/*
		else if (state == FORMAT_MODE && (typefunc = types[hash(&ch)]) != 0)
		{
			options.type = ch;
			options.chcount = count;
			count += typefunc(options, args, out);
			options = (format_options){0};
			state = NORMAL_MODE;
		}
		*/
		/*
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
		*/
		else if (state == FLAG_ZERO_MODE || state == WIDTH_MODE) 
			width_mode(format, options, i);
		else if (state == PRECISION_MODE) 
			precision_mode(format, options, i);
		else if (state == LENGTH_MODE) 
			length_mode(format, options, i);
		else if (state == NORMAL_MODE) 
		{
			ft_putchar_file(out, ch) ;
			count++;
		}

		/*
		else if (state == FLAG_ZERO_MODE && ch == ft_isdigit(ch))
		{
			startdigit++;
		}
		*/
		/*
		else if (state == WIDTH_MODE && ft_isdigit(ch))
		{
			printf("in width mode \n");
			startdigit++;
		}
		*/
		/*
		else if (state == FORMAT_MODE && ch == PRECISION_DOT)
		{
			state = PRECISION_MODE;
			startdigit = i + 1; //test to check if there's a digit
		}
		*/
		/*
		else if (state == PRECISION_MODE && ch == ft_isdigit(ch))
		{
			startdigit++;
		}
		*/
		/*
		else if (state == FORMAT_MODE && islengthmod(ch))
		{
			state = LENGTH_MODE;
			startdigit = i;
		}
		*/
		/*
		else if (state == FORMAT_MODE && ch == FLAG_HASH)
		{
			options.flags = options.flags | FLAG_ADDHASH;
		}
		*/
		/*
		else if (state == FORMAT_MODE && ft_isdigit(ch) && ch != '0')
		{
			state = WIDTH_MODE;
			options.flags = options.flags | FLAG_WIDTH;
			startdigit = i;
		}
		*/
		i++;
		ch = format[i];
	}
	ft_putchar_file(out, '\0');
	return count;
}
