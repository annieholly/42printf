#include <stdio.h>

int main(void)
{
  char buffer[1024];
  FILE *out = fmemopen(buffer, 1024, "w");
  fprintf(out, "Hello world\n");
  printf("Contents of buffer: %s", buffer);
  fclose(out);
  return 0;
}