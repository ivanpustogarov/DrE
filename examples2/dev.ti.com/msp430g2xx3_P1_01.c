//******************************************************************************
//  MSP430G2xx3 Demo - Software Poll P1.4, Set P1.0 if P1.4 = 1
//
//  Description: Poll P1.4 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430G2xx3
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P1.0|-->LED
//     \|/
//
//  D. Dang
//  Texas Instruments, Inc
//  December 2010
//   Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction


  __bis_SR_register(GIE);        // LPM0, ADC10_ISR will force exit
  __bis_SR_register(CPUOFF);        // LPM0, ADC10_ISR will force exit
  __bic_SR_register(CPUOFF);
  __bic_SR_register(GIE);
  while (1)                                 // Test P1.4
  {
    if ((0x10 & P1IN))
      P1OUT |= 0x01;       // if P1.4 set, set P1.0
    else 
    {
      P1OUT &= ~0x01;                    // else reset
      assert(0);
    }
  }
}
