#include <msp430.h>
#define THRESHOLD 15

int adc = 0;

int process_adc()
{
  int val = 0, val_prev = 0, i = 0, diff = 0, j = 0;
  __bis_SR_register(CPUOFF + GIE);
  val = adc;
  while(diff < THRESHOLD)
  {
    val = adc;
    diff = val-val_prev;
    if(i == 10) // Non-cpu model failes here
    {
      i = 0;
      j++;
    }
    i++;
    val_prev = val;
    __bis_SR_register(CPUOFF + GIE);
  }
  if(diff <= 20)
    return 20;
  if(diff <= 100)
    return 100;
  if(diff <= 300)
    return 300;
  return 500;
}


/* The purpos of this example is to demostrate the following limitations of Fie:
   1. Generating too many interrupt forks.
   2. Not connecting res/args
*/

int main()
{
  int val = 0, val_repv = 0;
  int tick = 0;
  int acceleration = 0;
  __bis_SR_register(CPUOFF + GIE);
  while(1)
  {
    if(tick >= 1000) // (Wait for settling down) This is to generate many interrpts in FiE
    {
        acceleration = process_adc();
        if(acceleration == 20)
          assert(0);
    }
    tick++;
  }
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

