#include  <msp430.h>

//int assert(int a);

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 
  P1DIR |= 0x01;                             
  unsigned int i = 0;                         
  for (;;)                                  
  {
    P1OUT ^= 0x01;                          
    for(i=0; i< 20; i++);                
    assert(0);
  }
}
