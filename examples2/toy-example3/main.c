#include <msp430.h>

uint16_t val;

int printGesture(uint16_t gesture1, uint16_t gesture2)
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

uint16_t getGesture()
{
  __bis_SR_register(LPM3_bits | GIE);
  return val;
}

//int main(int argc, char *argv[])
int main()
{
  uint16_t gesture1 = getGesture();
  uint16_t gesture2 = getGesture();
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
  val = ADC10MEM;
  __bic_SR_register_on_exit(LPM3_bits);
  //__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
