#include <stdio.h>
#include <stdlib.h>

void hello(const char *name, int age)
{
  printf("Hello %s is %d\n", name, age);
}

int hash(const char *c)
{

  return atoi(c) % 52;
}

int main()
{
  void (*types[52])(const char*);
  types[hash("s")] = hello;
  types[hash("s")]("Annie", 45);

}
