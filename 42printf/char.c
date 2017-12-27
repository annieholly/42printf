#include <unistd.h>
#include <stdio.h>

void ft_putchar_fd(FILE *fd, char c)
{
  printf("file no: %d \n", fileno(fd));
  write(fileno(fd), &c, 1);
}

int main()
{
  char *string = "Hello World";
  int i;
  FILE *out;
  char buf[1024];

  out = fmemopen(buf, 1024, "w");
  i = 0;
  while (string[i] != '\0')
    {
      ft_putchar_fd(out, string[i]);
      //fputc(string[i], out);
      i++;
    }
  printf("buf: %s \n", buf);
}
