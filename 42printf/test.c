#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"
#include <string.h>

#define TEST_FUNC ahprintf

void test_func(char *description, char *correctoutput, char *test, ...)
{
  char outputbuf[1024];
  va_list testargs;
  FILE *out;
  //  out = fmemopen(outputbuf, 1024, "w");

  va_start(testargs, test);
  TEST_FUNC(out, test, testargs);
  if (strcmp(outputbuf, correctoutput) != 0)
    {
      printf("Test %s failed: %s != %s\n", description, outputbuf,
	     correctoutput);
    }
  else
    printf(".");
  fclose(out);
}



int main()
{
  test_func("basic input test", "foo", "bar");
  test_func("integer test", "1", "%d", 1); 
  test_func("should pass", "foo", "foo");
  test_func("string test", "foo", "%s", "foo");


  printf("\n");
  return (0);
}
