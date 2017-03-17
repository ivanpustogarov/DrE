#include <msp430.h>

uint16_t a = 0;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_1;                       // input A1
  ADC10AE0 |= 0x02;                         // PA.1 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
  ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
  if (a < 511)
  {
    P1OUT &= ~0x01;                       // Clear P1.0 LED off
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    if (a > 1023)
      assert(0);
  }
  else
    P1OUT |= 0x01;                        // Set P1.0 LED on
}

// ADC10 interrupt service routine
//#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
//#pragma vector=ADC10_VECTOR
//__interrupt void ADC10_ISR(void)
//#elif defined(__GNUC__)
//void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
void ADC10_ISR (void)
//ISR(ADC10, ADC10_ISR)
//#else
//#error Compiler not supported!
//#endif
{
  a = ADC10MEM;
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
