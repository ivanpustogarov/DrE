#include <msp430.h>


int global1 = 0;
int global2 = 0;
long tempMeasured[8];
unsigned char tempMeasuredPosition=0;

int g(int x, int y)
{
  if(x>40 && y>4)
    assert(0);
  else
    return 0;
}

int inner3(int a, int b)
{
  return a+b;
}

int inner2(int a, int b)
{
  global1 = 1;
  tempMeasured[tempMeasuredPosition++] = ADC10MEM;
  if (tempMeasuredPosition == 8)
    tempMeasuredPosition = 0;
  return inner3(a,b);
}

int inner1(int a, int b)
{
  int res = 0;
  if((a+b>=3) && ((a-b) <= 2))
    res = inner2(a+b,a-b);
  if(res==144) // a+b+res
    return res-141; // a+b+res
  return 0;
}

int main()
{
  int m,n,p;

  klee_make_symbolic(&m,sizeof(m),"m");
  klee_make_symbolic(&n,sizeof(n),"n");
  klee_make_symbolic(&p,sizeof(p),"p");
  global1 = 1;
  global2 = 1;
  tempMeasured[0] = ADC10MEM;

  if(m>0 && n>0 )
  {
    int x = inner1(n,m); 
    int y = inner1(n,m); 
    //if((x==3) && (y==3))
    if((x+y)==6)
      g(m+n,m);
  }

  return 0;
}
    
