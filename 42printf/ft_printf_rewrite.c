#include "ft_printf.h" 
#include "libft.h" 

int is_special_char(char ch)
{
	if (ch == FLAG_MINUS || ch == FLAG_PLUS || ch == FLAG_SPACE || ch == FLAG_ZERO ||
		ch == FLAG_HASH || ch == PRECISION_DOT || ft_isdigit(ch))
		return (1); 
	return (0);
}

void set_special_flag(char ch, t_format *options)
{
//	printf("set special flag for: %c\n", ch);
	if (ch == FLAG_MINUS)
		options->flags = options->flags | FLAG_LEFTALIGN;
	else if (ch == FLAG_PLUS)
		options->flags = options->flags | FLAG_ADDSIGN;
	else if (ch == FLAG_SPACE)
		options->flags = options->flags | FLAG_ADDSPACE;
	else if (ch == FLAG_HASH)
		options->flags = options->flags | FLAG_ADDHASH;
	else if (ch == PRECISION_DOT) 
		options->state = PRECISION_MODE;
	else if (ch == FLAG_ZERO && options->flags != FLAG_ADDZERO)
	{
		options->flags = options->flags | FLAG_ADDZERO;
		options->state = WIDTH_MODE;
	}
	else if (ft_isdigit(ch) && ch != '0') 
	{
		options->flags = options->flags | FLAG_WIDTH;
		options->state = WIDTH_MODE;
	}
}

void width_mode(const char *format, t_format *options, int i)
{
	options->width = ft_atoi(&format[i]);
	options->state = FORMAT_MODE;
}

void precision_mode(const char *format, t_format *options, int i)
{
	options->precision = ft_atoi(&format[i]);
	options->flags = options->flags | FLAG_PRECISION;
	options->state = FORMAT_MODE;
}

void set_length_chars(const char *format, t_format *options, char ch)
{
	int i; 
	i = -1;
	if (islengthmod(options->length[0]))
		options->length[++i] = ch;
	options->length[++i] = ch;
	options->length[++i] = '\0'; 
//	printf("length: %s\n", options->length);
//	printf("strlen: %zu\n", ft_strlen(options->length));
}

int format_mode(t_format *options, const char *format, va_list args, char ch, FILE *out) 
{
	int count;
	int (*types[TYPE_COUNT])(t_format, va_list, FILE *) = {0};
	int (*typefunc)(t_format, va_list, FILE *) = 0;

	inittypes(types);
	count = 0;
	if (ch == '%') 
	{
		ft_putchar_file(out, ch);
		count++;
		options->state = NORMAL_MODE;
	}
	if (is_special_char(ch)) 
		set_special_flag(ch, options);
	if (islengthmod(ch))
		set_length_chars(format, options, ch);
	if ((typefunc = types[hash(&ch)]) != 0)
	{
		options->type = ch;
		options->chcount = count;
		count += typefunc(*options, args, out);
		*options = (t_format){0};
		options->state = NORMAL_MODE;
	}

	return (count);
}

int ahprintf(FILE *out, const char *format, va_list args)
{
	char ch;
	int i;
	int count;
	static int state; 
	static t_format options;

	i = 0;
	count = 0;
	ch = format[i];
	options.state = NORMAL_MODE;
	while (ch != '\0')
	{
		if (options.state == NORMAL_MODE && ch == '%')
			options.state = FORMAT_MODE;
		else if (options.state == FORMAT_MODE)
			count += format_mode(&options, format, args, ch, out);
		else if (options.state == WIDTH_MODE) 
			width_mode(format, &options, i);
		else if (options.state == PRECISION_MODE) 
			precision_mode(format, &options, i);
		else if (options.state == NORMAL_MODE) 
		{
			ft_putchar_file(out, ch);
			count++;
		}
		i++;
		ch = format[i];
	}
	ft_putchar_file(out, '\0');
//	printf("count: %d\n", count);
//	options.chcount = count;
	return count;
}
