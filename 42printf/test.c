#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"
#include <string.h>
#include <locale.h>

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
  
  long int d = 31415926535;
  test_func("long integer test", "31415926535", "%ld", d);
  test_func("hash float test", "42.", "%#.0f", 42.0);
  test_func("hash hex lower test - input: 16000", "3e80", "%x", 16000);
  test_func("hash hex upper test - input: 16000", "3E80", "%X", 16000);
  test_func("hash hex test - input: 161", "0XA1", "%#X", 161);

  int num;
  test_func("test stored number of chars", "hello", "hello%n", &num);
  test_func("test stored number of chars int", "5", "%d", num);

  test_func("char test", "c", "%c", 'c');
  test_func("integer alias test", "123456", "%i", 123456);
  test_func("unsigned int test", "123456", "%u", 123456);
  test_func("unsigned int test", "4294843840", "%u", -123456);
  test_func("octal test", "6212", "%o", 3210);

  char a = 'a';
  char addressbuf[512];
  sprintf(addressbuf, "%p", &a);
  test_func("pointer test", addressbuf, "%p", &a);

  test_func("short int 'h' length modifier test", "-7616", "%hd", 123456);  

  test_func("long double 'Lf' test", "1234567890.1234567889", "%.10Lf", 1234567890.1234567890L);

  test_func("padding test", "   28", "%5d", 28);
  test_func("width and precision test", " 0028", "%05.4d", 28);

//WIDE CHAR TEST
  setlocale(LC_CTYPE, "");
  test_func("test wide char", "Ñ", "%lc", L'Ñ');
  test_func("test wide char string", "あああ", "%ls", L"あああ");

//  test_func("wide char test", "@", "%lc", 'L@');

//  ft_printf("1 ft: %C\n", L'@');
//  printf("2 pf: %C\n", L'AAA');

//  printf("3 pf: %lc\n", L'@@');
  
//  printf("\n");

  return (0);
}
