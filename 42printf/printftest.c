//#include "ft_printf.h"
#include <stdio.h>
#include <inttypes.h>

int main()
{
//  ft_printf("%s\n", "Hello WOlrd \n");
//  ft_printf("%d\n", 123);
//  ft_printf("%f\n", 42.0);
  
	printf("size of char: %lu\n", sizeof(char));
	printf("size of short: %lu\n", sizeof(short));
	printf("size of int: %lu\n", sizeof(int));
	printf("size of long: %lu\n", sizeof(long));
	printf("size of long long: %lu\n", sizeof(long long));
	printf("size of float: %lu\n", sizeof(float));
	printf("size of double: %lu\n", sizeof(double));
	printf("size of long double: %lu\n", sizeof(long double));
	printf("size of void *: %lu\n", sizeof(void *));
	printf("size of intmax_t: %lu\n", sizeof(intmax_t));
	printf("size of size_t: %lu \n", sizeof(size_t));
  
}
