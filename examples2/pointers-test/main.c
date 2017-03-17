#include <msp430.h>

char *b;

int foo(char *x)
{
  int a = 0;
  a++;
  if(*x == 2)
    assert(0);
  return 0;
}

int boo()
{
  b = malloc(4);
  return 0;
}

int main()
{
  //b = malloc(sizeof(int));
  boo();
  *b = 1;
  *(b+1) = 2;
  char x = 2;
  klee_make_symbolic(&x, sizeof(char), "x");
  foo(&x);
  return 0;
}
