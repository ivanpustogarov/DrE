#include <msp430.h>

int f(int m, int n)
{
  int i, a, sum = 0;
  for(i=0; i<6; i++)
  {
    a = n%2;
    if(a) sum += a+1;
    n/=2;
  }
  while(1) {
    if(sum == 0 && m==57)
      assert(0);
    i++;
  }
}

void g(int m, int n)
{
  int i;
  for(i=0;i<1000;i++)
    if(m == i)
      f(m,n);
}

int main()
{
  int m,n,i;
  klee_make_symbolic(&m, sizeof(m), "m");
  klee_make_symbolic(&n, sizeof(n), "n");
  if(m >= 30) g(m,n);
  return 0;
}

