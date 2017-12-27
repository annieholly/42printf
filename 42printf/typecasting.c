#include <stdio.h>

int main()
{
  int (*typecast) = (int);
  int v = (typecast)10;
}
