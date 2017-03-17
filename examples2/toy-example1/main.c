#include <msp430.h>

#define AVG_LEN (64)
#define AVG_MASK (AVG_LEN - 1)
int avg_buf[AVG_LEN] = {0};

int diff = 0;

int printGesture(int gesture1, int gesture2);
int classify_subgesture(int a);
int avg(int);

int printGesture(int gesture1, int gesture2)
{
  int a = 0;
  if ((gesture1 == 1) && (gesture2 == 2))
  {
    assert(0);
    a = 1;
  }
  else if ((gesture1 == 2) && (gesture2 == 3))
  {
    a = 2;
  }
  return 0;
}

int classify_subgesture(int a)
{
  return a;
}

//#define AVG_LEN (64)
//#define AVG_MASK (AVG_LEN - 1)
int avg(int newVal) {
  //static int avg_buf[AVG_LEN] = {0};
  static int index = 0;
  static int sum = 0;  // TODO: change to 16 bits?
  sum -= avg_buf[index & AVG_MASK];
  sum += avg_buf[index++ & AVG_MASK] = newVal;
  return sum / AVG_LEN;    // TODO: Check ASM to make sure it's a shift.
}

int getGesture()
{
  int a = 1;
  __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
  if(diff == 1)
  {
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    if(diff == 3)
    {
      int res1 = classify_subgesture(a);
      return res1;
    }
    else
    {
      int res2 = classify_subgesture(a+1);
      return res2;
    }
  }
  int res3 = classify_subgesture(a+2);
  return res3;
}

//int main(int argc, char *argv[])
int main()
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_1;                       // input A1
  ADC10AE0 |= 0x02;                         // PA.1 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  int gesture1 = getGesture();
  int gesture2 = getGesture();

  if((gesture1 == 0) || (gesture2 == 10))
    return 1;
  printGesture(gesture1, gesture2);
  return 2;
}

// ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  diff = ADC10MEM;
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
