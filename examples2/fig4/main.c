#include <msp430.h>

int test_global1 = 1;
int test_global2 = 1;

void f(int m, int n)
{
  int i, a, sum = 0;
  int j;
  for(i=0; i<6; i++)
  {
    a = n%2;
    if(a) sum += a+1;
    n/=2;
  }
  while(1) {
    if(sum == 0 && m==157)
      assert(0);
    j++;
  }
}

int main()
{
  int m,n,i;
  klee_make_symbolic(&m, sizeof(m), "m");
  klee_make_symbolic(&n, sizeof(n), "n");

  for(i=0;i<1000;i++)
    if(m==i)
      f(m,n);
}
