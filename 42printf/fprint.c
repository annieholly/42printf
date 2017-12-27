#include <stdio.h>

int main() {
  FILE *fp;
  int nchars;
  char buf[1024];

  fp = fopen("test_output.txt", "w+");

  nchars = fprintf(fp, "Hello world\n");
  fseek(fp, 0, SEEK_SET);
  fread(buf, nchars + 1, 1, fp);
  fclose(fp);

  printf("buf: %s", buf);
}
