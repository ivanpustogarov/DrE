#include <msp430.h>

int g(int x, int y)
{
  if((x*y)>40 && (y+x)>4)
    assert(0);
  else
    return 0;
}

int f(int x, int y)
{
  if( (2*x+4 == 8) && y>0)
    g(x+y,y);
  else
    return 0;
}

int inner2(int a, int b)
{
  if(a > b) 
    return 3;
  return 0;
}

int inner1(int a, int b)
{
  int res = 0;
  if((a+b>=3) && ((a-b) <= 2))
    res = inner2(a+b,a-b);
  if(res==3)
    return 3;
  return 0;
}

int main()
{
  int m,n,p;
  klee_make_symbolic(&m,sizeof(m),"m");
  klee_make_symbolic(&n,sizeof(n),"n");
  klee_make_symbolic(&p,sizeof(p),"p");
  if(m>0 && n>0 )
  {
    int x = inner1(22,21); 
    if(x==3)
      f(m+n,m);
 }
  return 0;
}
    
