#include <msp430.h>
#define THRESHOLD 15

int adc = 0;

get_acceleration(int mode)
{
  int i = 0;
  __bis_SR_register(CPUOFF + GIE);
  while(adc >= 15)
  {
    /* some computations */
    i++;
    __bis_SR_register(CPUOFF + GIE);
  }
  if(i > 15 && (mode == 'a'))
    return 1;
  else if(mode == 'a')
    return 2;
  else
    return 3;
}


/* The purpos of this example is to demostrate the following limitations of Fie:
   1. Not connecting res/args which leads to path explosion
*/

int main()
{
  int val = 0, val_repv = 0;
  int tick = 0;
  int acceleration[] = {0, 0, 0};
  int j = 0;
  int mode;
  klee_make_symbolic(&mode, sizeof(mode), "mode");
  while(1)
  {
    acceleration[j] = get_acceleration(mode);
    j++;
    if(j==3) j=0;
    if( (acceleration[0] == 1) &&
        (acceleration[1] == 1) &&
        (acceleration[2] == 1))
      break;
  }
  assert(0);
  return 0;
}

int num_of_adc_reads = 0;
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  adc = ADC10MEM;
  /* Some heavy computation */
  num_of_adc_reads++;
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

