#include "libft.h"
#include <stdio.h>


int main()
{
  float n = 42.5;
  char *s = ft_ftoa(n, 6);
  printf("float: %s\n", s);
  printf("correct float: %f\n", n);
}
