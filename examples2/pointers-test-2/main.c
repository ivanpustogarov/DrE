#include <msp430.h>

char *b;

int foo(int a)
{
  if(a == 1)
    return 1;
  else
    return 0;
}

int boo(char *y)
{
  int a = 0;
  a++;
  //*y = 2;
  //int f = foo(1);
  if(*y == 2)
    return 1;
  else  
    return 0;
}

int main()
{
  int a;
  char *y = &a;
  char x;
  klee_make_symbolic(&x, sizeof(char), "x");
  boo(y);
  if(x == 3)
    assert(0);
  return 0;
}
