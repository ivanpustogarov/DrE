#include <msp430.h>

//uint16_t assert(int32_t a);
//uint16_t ADC10MEM0 = 0;

#define MAXARGC 20
//uint16_t argc; uint16_t argv[MAXARGC];
int g = 3;
int boo(char a);
int zoo(char a);

int foo1(int x)
{
  if(x == 20)
    assert(0);
}

int foo(int x)
{
  if((x == 3) || (x == 4) || (x == 5))
  {
    g = 33;
    int var1 = zoo(x);
    if(var1 == 20)
      foo1(var1);
  }
}

int zoo(char a)
{
  if (g == 3)
    return 4;
  if (a == 'b')
    return 3;
  return 20;
}

int boo(char a)
{
  if (a == 'b')
    return zoo(a);
  return 3;
}

uint16_t sub_main(int n)
{
  
  int var = boo(n);
  if((var == 3) || (var == 4)) 
  {
    int var1 = boo(n);
    foo(var1);
  } 
  return 0;
}

int main()
{
  int n;
  klee_make_symbolic(&n, sizeof(n), "n");
  sub_main(n);

}
