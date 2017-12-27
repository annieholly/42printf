#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"
#include <string.h>

#define TEST_FUNC ahprintf

void test_func(char *description, char *correctoutput, char *text, ...)
{
  FILE *fp;
  int nchars;
  char buf[1024] = {0};
  char *filename = "test_output.txt";
  va_list args;

  va_start(args, text);

  fp = fopen(filename, "w+");
  nchars = TEST_FUNC(fp, text, args);
  fseek(fp, 0, SEEK_SET);
  fread(buf, nchars + 1, 1, fp);
  fclose(fp);

  if (strcmp(buf, correctoutput) != 0)
    {
      printf("Test %s failed: %s != %s\n", description, buf, correctoutput);
    }
  else
    {
      printf(".\n");
    }
}



int main()
{
  test_func("integer test", "9", "%d", 9);
  test_func("should pass", "foo", "foo");
  test_func("string test", "foo", "%s", "foo");
  test_func("flag left align test", "foo", "%-s", "foo");
  test_func("flag add sign test", "+10", "%+d", 10);
  test_func("flag add space test", " 10", "% d", 10);
  test_func("flag leading zero test", "0002", "%04d", 2);
  test_func("flag leading zero test", "4000", "%03d", 4000);
  test_func("string length test", "abc", "%.3s", "abcdefgh");
  test_func("float test", "42.500000", "%f", 42.5);
  test_func("float precision test", "3.14", "%.2f", 3.14372371);
  test_func("float leading zero test", "03.14", "%05.2f", 3.14372371);
  test_func("float add space test", " 10.21", "% .2f", 10.21);
  test_func("float add sign test", "+10.21", "%+.2f", 10.21);
  printf("\n");
  return (0);
}
