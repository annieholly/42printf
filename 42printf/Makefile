CC='cc'
INCLUDES='libftah/'

test: test.c ft_printf.c
	$(CC) -I $(INCLUDES) test.c ft_printf.c printnum.c ft_printf_rewrite.c $(INCLUDES)/*.c -o test
	./test
