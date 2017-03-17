/* ============================================================================ */
/* Copyright (c) 2013, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */

/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430FR5739 devices.
*
* Texas Instruments, Version 1.23
*
* Rev. 1.0, Setup
* Rev. 1.1  Fixed definition of RTCTEV__0000 and RTCTEV__1200
*           Removed not availabe bits RTCMODE and RTCSSELx
*           Added PxSELC registers
* Rev. 1.2  Removed Port Drive Strenght Registers
* Rev. 1.3  updated PxSELC register address to offset 0x16 (instead of 0x10)
*
********************************************************************/

#ifndef __MSP430FR5739
#define __MSP430FR5739

#define __MSP430_HEADER_VERSION__ 1073

#define __MSP430_TI_HEADERS__

#ifdef __cplusplus
extern "C" {
#endif

#include <iomacros.h>

/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)

/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                   (0x0001)
#define Z                   (0x0002)
#define N                   (0x0004)
#define V                   (0x0100)
#define GIE                 (0x0008)
#define CPUOFF              (0x0010)
#define OSCOFF              (0x0020)
#define SCG0                (0x0040)
#define SCG1                (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#ifndef __STDC__ /* Begin #defines for assembler */
#define LPM0                (CPUOFF)
#define LPM1                (SCG0+CPUOFF)
#define LPM2                (SCG1+CPUOFF)
#define LPM3                (SCG1+SCG0+CPUOFF)
#define LPM4                (SCG1+SCG0+OSCOFF+CPUOFF)
/* End #defines for assembler */

#else /* Begin #defines for C */
#define LPM0_bits           (CPUOFF)
#define LPM1_bits           (SCG0+CPUOFF)
#define LPM2_bits           (SCG1+CPUOFF)
#define LPM3_bits           (SCG1+SCG0+CPUOFF)
#define LPM4_bits           (SCG1+SCG0+OSCOFF+CPUOFF)

#include "in430.h"

#define LPM0      _BIS_SR(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT _BIC_SR_IRQ(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      _BIS_SR(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT _BIC_SR_IRQ(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      _BIS_SR(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT _BIC_SR_IRQ(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      _BIS_SR(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT _BIC_SR_IRQ(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      _BIS_SR(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT _BIC_SR_IRQ(LPM4_bits) /* Exit Low Power Mode 4 */
#endif /* End #defines for C */

/************************************************************
* CPU
************************************************************/
#define __MSP430_HAS_MSP430XV2_CPU__  /* Definition to show that it has MSP430XV2 CPU */

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/


/************************************************************
* ADC10_B
************************************************************/
#define __MSP430_HAS_ADC10_B__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_ADC10_B__ 0x0700
#define ADC10_B_BASE __MSP430_BASEADDRESS_ADC10_B__

#define ADC10CTL0_            0x0700    /* ADC10 Control 0 */
#define ADC10CTL0_L (*(volatile uint8_t *)0x700)
#define ADC10CTL0 (*(volatile uint16_t *)0x700)
#define ADC10CTL0_H (*(volatile uint8_t *)0x701)
#define ADC10CTL0_L (*(volatile uint8_t *)0x700)
#define ADC10CTL0 (*(volatile uint16_t *)0x700)
#define ADC10CTL1_            0x0702    /* ADC10 Control 1 */
#define ADC10CTL1_L (*(volatile uint8_t *)0x702)
#define ADC10CTL1 (*(volatile uint16_t *)0x702)
#define ADC10CTL1_H (*(volatile uint8_t *)0x703)
#define ADC10CTL1_L (*(volatile uint8_t *)0x702)
#define ADC10CTL1 (*(volatile uint16_t *)0x702)
#define ADC10CTL2_            0x0704    /* ADC10 Control 2 */
#define ADC10CTL2_L (*(volatile uint8_t *)0x704)
#define ADC10CTL2 (*(volatile uint16_t *)0x704)
#define ADC10CTL2_H (*(volatile uint8_t *)0x705)
#define ADC10CTL2_L (*(volatile uint8_t *)0x704)
#define ADC10CTL2 (*(volatile uint16_t *)0x704)
#define ADC10LO_              0x0706    /* ADC10 Window Comparator High Threshold */
#define ADC10LO_L (*(volatile uint8_t *)0x706)
#define ADC10LO (*(volatile uint16_t *)0x706)
#define ADC10LO_H (*(volatile uint8_t *)0x707)
#define ADC10LO_L (*(volatile uint8_t *)0x706)
#define ADC10LO (*(volatile uint16_t *)0x706)
#define ADC10HI_              0x0708    /* ADC10 Window Comparator High Threshold */
#define ADC10HI_L (*(volatile uint8_t *)0x708)
#define ADC10HI (*(volatile uint16_t *)0x708)
#define ADC10HI_H (*(volatile uint8_t *)0x709)
#define ADC10HI_L (*(volatile uint8_t *)0x708)
#define ADC10HI (*(volatile uint16_t *)0x708)
#define ADC10MCTL0_           0x070A    /* ADC10 Memory Control 0 */
#define ADC10MCTL0_L (*(volatile uint8_t *)0x70a)
#define ADC10MCTL0 (*(volatile uint16_t *)0x70a)
#define ADC10MCTL0_H (*(volatile uint8_t *)0x70b)
#define ADC10MCTL0_L (*(volatile uint8_t *)0x70a)
#define ADC10MCTL0 (*(volatile uint16_t *)0x70a)
#define ADC10MEM0_            0x0712    /* ADC10 Conversion Memory 0 */
#define ADC10MEM0_L (*(volatile uint8_t *)0x712)
#define ADC10MEM0 (*(volatile uint16_t *)0x712)
#define ADC10MEM0_H (*(volatile uint8_t *)0x713)
#define ADC10MEM0_L (*(volatile uint8_t *)0x712)
#define ADC10MEM0 (*(volatile uint16_t *)0x712)
#define ADC10IE_              0x071A    /* ADC10 Interrupt Enable */
#define ADC10IE_L (*(volatile uint8_t *)0x71a)
#define ADC10IE (*(volatile uint16_t *)0x71a)
#define ADC10IE_H (*(volatile uint8_t *)0x71b)
#define ADC10IE_L (*(volatile uint8_t *)0x71a)
#define ADC10IE (*(volatile uint16_t *)0x71a)
#define ADC10IFG_             0x071C    /* ADC10 Interrupt Flag */
#define ADC10IFG_L (*(volatile uint8_t *)0x71c)
#define ADC10IFG (*(volatile uint16_t *)0x71c)
#define ADC10IFG_H (*(volatile uint8_t *)0x71d)
#define ADC10IFG_L (*(volatile uint8_t *)0x71c)
#define ADC10IFG (*(volatile uint16_t *)0x71c)
#define ADC10IV_              0x071E    /* ADC10 Interrupt Vector Word */
#define ADC10IV_L (*(volatile uint8_t *)0x71e)
#define ADC10IV (*(volatile uint16_t *)0x71e)
#define ADC10IV_H (*(volatile uint8_t *)0x71f)
#define ADC10IV_L (*(volatile uint8_t *)0x71e)
#define ADC10IV (*(volatile uint16_t *)0x71e)

/* ADC10CTL0 Control Bits */
#define ADC10SC             (0x0001)  /* ADC10 Start Conversion */
#define ADC10ENC            (0x0002)  /* ADC10 Enable Conversion */
#define ADC10ON             (0x0010)  /* ADC10 On/enable */
#define ADC10MSC            (0x0080)  /* ADC10 Multiple SampleConversion */
#define ADC10SHT0           (0x0100)  /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1           (0x0200)  /* ADC10 Sample Hold Select Bit: 1 */
#define ADC10SHT2           (0x0400)  /* ADC10 Sample Hold Select Bit: 2 */
#define ADC10SHT3           (0x0800)  /* ADC10 Sample Hold Select Bit: 3 */

/* ADC10CTL0 Control Bits */
#define ADC10SC_L           (0x0001)  /* ADC10 Start Conversion */
#define ADC10ENC_L          (0x0002)  /* ADC10 Enable Conversion */
#define ADC10ON_L           (0x0010)  /* ADC10 On/enable */
#define ADC10MSC_L          (0x0080)  /* ADC10 Multiple SampleConversion */

/* ADC10CTL0 Control Bits */
#define ADC10SHT0_H         (0x0001)  /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1_H         (0x0002)  /* ADC10 Sample Hold Select Bit: 1 */
#define ADC10SHT2_H         (0x0004)  /* ADC10 Sample Hold Select Bit: 2 */
#define ADC10SHT3_H         (0x0008)  /* ADC10 Sample Hold Select Bit: 3 */

#define ADC10SHT_0          (0x0000) /* ADC10 Sample Hold Select 0 */
#define ADC10SHT_1          (0x0100) /* ADC10 Sample Hold Select 1 */
#define ADC10SHT_2          (0x0200) /* ADC10 Sample Hold Select 2 */
#define ADC10SHT_3          (0x0300) /* ADC10 Sample Hold Select 3 */
#define ADC10SHT_4          (0x0400) /* ADC10 Sample Hold Select 4 */
#define ADC10SHT_5          (0x0500) /* ADC10 Sample Hold Select 5 */
#define ADC10SHT_6          (0x0600) /* ADC10 Sample Hold Select 6 */
#define ADC10SHT_7          (0x0700) /* ADC10 Sample Hold Select 7 */
#define ADC10SHT_8          (0x0800) /* ADC10 Sample Hold Select 8 */
#define ADC10SHT_9          (0x0900) /* ADC10 Sample Hold Select 9 */
#define ADC10SHT_10         (0x0A00) /* ADC10 Sample Hold Select 10 */
#define ADC10SHT_11         (0x0B00) /* ADC10 Sample Hold Select 11 */
#define ADC10SHT_12         (0x0C00) /* ADC10 Sample Hold Select 12 */
#define ADC10SHT_13         (0x0D00) /* ADC10 Sample Hold Select 13 */
#define ADC10SHT_14         (0x0E00) /* ADC10 Sample Hold Select 14 */
#define ADC10SHT_15         (0x0F00) /* ADC10 Sample Hold Select 15 */

/* ADC10CTL1 Control Bits */
#define ADC10BUSY           (0x0001)    /* ADC10 Busy */
#define ADC10CONSEQ0        (0x0002)    /* ADC10 Conversion Sequence Select 0 */
#define ADC10CONSEQ1        (0x0004)    /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0          (0x0008)    /* ADC10 Clock Source Select 0 */
#define ADC10SSEL1          (0x0010)    /* ADC10 Clock Source Select 1 */
#define ADC10DIV0           (0x0020)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV1           (0x0040)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV2           (0x0080)    /* ADC10 Clock Divider Select 2 */
#define ADC10ISSH           (0x0100)    /* ADC10 Invert Sample Hold Signal */
#define ADC10SHP            (0x0200)    /* ADC10 Sample/Hold Pulse Mode */
#define ADC10SHS0           (0x0400)    /* ADC10 Sample/Hold Source 0 */
#define ADC10SHS1           (0x0800)    /* ADC10 Sample/Hold Source 1 */

/* ADC10CTL1 Control Bits */
#define ADC10BUSY_L         (0x0001)    /* ADC10 Busy */
#define ADC10CONSEQ0_L      (0x0002)    /* ADC10 Conversion Sequence Select 0 */
#define ADC10CONSEQ1_L      (0x0004)    /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0_L        (0x0008)    /* ADC10 Clock Source Select 0 */
#define ADC10SSEL1_L        (0x0010)    /* ADC10 Clock Source Select 1 */
#define ADC10DIV0_L         (0x0020)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV1_L         (0x0040)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV2_L         (0x0080)    /* ADC10 Clock Divider Select 2 */

/* ADC10CTL1 Control Bits */
#define ADC10ISSH_H         (0x0001)    /* ADC10 Invert Sample Hold Signal */
#define ADC10SHP_H          (0x0002)    /* ADC10 Sample/Hold Pulse Mode */
#define ADC10SHS0_H         (0x0004)    /* ADC10 Sample/Hold Source 0 */
#define ADC10SHS1_H         (0x0008)    /* ADC10 Sample/Hold Source 1 */

#define ADC10CONSEQ_0        (0x0000)      /* ADC10 Conversion Sequence Select: 0 */
#define ADC10CONSEQ_1        (0x0002)      /* ADC10 Conversion Sequence Select: 1 */
#define ADC10CONSEQ_2        (0x0004)      /* ADC10 Conversion Sequence Select: 2 */
#define ADC10CONSEQ_3        (0x0006)      /* ADC10 Conversion Sequence Select: 3 */

#define ADC10SSEL_0          (0x0000)      /* ADC10 Clock Source Select: 0 */
#define ADC10SSEL_1          (0x0008)      /* ADC10 Clock Source Select: 1 */
#define ADC10SSEL_2          (0x0010)      /* ADC10 Clock Source Select: 2 */
#define ADC10SSEL_3          (0x0018)      /* ADC10 Clock Source Select: 3 */

#define ADC10DIV_0           (0x0000)   /* ADC10 Clock Divider Select: 0 */
#define ADC10DIV_1           (0x0020)   /* ADC10 Clock Divider Select: 1 */
#define ADC10DIV_2           (0x0040)   /* ADC10 Clock Divider Select: 2 */
#define ADC10DIV_3           (0x0060)   /* ADC10 Clock Divider Select: 3 */
#define ADC10DIV_4           (0x0080)   /* ADC10 Clock Divider Select: 4 */
#define ADC10DIV_5           (0x00A0)   /* ADC10 Clock Divider Select: 5 */
#define ADC10DIV_6           (0x00C0)   /* ADC10 Clock Divider Select: 6 */
#define ADC10DIV_7           (0x00E0)   /* ADC10 Clock Divider Select: 7 */

#define ADC10SHS_0           (0x0000)  /* ADC10 Sample/Hold Source: 0 */
#define ADC10SHS_1           (0x0400)  /* ADC10 Sample/Hold Source: 1 */
#define ADC10SHS_2           (0x0800)  /* ADC10 Sample/Hold Source: 2 */
#define ADC10SHS_3           (0x0C00)  /* ADC10 Sample/Hold Source: 3 */

/* ADC10CTL2 Control Bits */
#define ADC10REFBURST       (0x0001)    /* ADC10 Reference Burst */
#define ADC10SR             (0x0004)    /* ADC10 Sampling Rate */
#define ADC10DF             (0x0008)    /* ADC10 Data Format */
#define ADC10RES            (0x0010)    /* ADC10 Resolution Bit */
#define ADC10PDIV0          (0x0100)    /* ADC10 predivider Bit: 0 */
#define ADC10PDIV1          (0x0200)    /* ADC10 predivider Bit: 1 */

/* ADC10CTL2 Control Bits */
#define ADC10REFBURST_L     (0x0001)    /* ADC10 Reference Burst */
#define ADC10SR_L           (0x0004)    /* ADC10 Sampling Rate */
#define ADC10DF_L           (0x0008)    /* ADC10 Data Format */
#define ADC10RES_L          (0x0010)    /* ADC10 Resolution Bit */

/* ADC10CTL2 Control Bits */
#define ADC10PDIV0_H        (0x0001)    /* ADC10 predivider Bit: 0 */
#define ADC10PDIV1_H        (0x0002)    /* ADC10 predivider Bit: 1 */

#define ADC10PDIV_0         (0x0000)    /* ADC10 predivider /1 */
#define ADC10PDIV_1         (0x0100)    /* ADC10 predivider /2 */
#define ADC10PDIV_2         (0x0200)    /* ADC10 predivider /64 */
#define ADC10PDIV_3         (0x0300)    /* ADC10 predivider reserved */

#define ADC10PDIV__1        (0x0000)    /* ADC10 predivider /1 */
#define ADC10PDIV__4        (0x0100)    /* ADC10 predivider /2 */
#define ADC10PDIV__64       (0x0200)    /* ADC10 predivider /64 */

/* ADC10MCTL0 Control Bits */
#define ADC10INCH0          (0x0001)    /* ADC10 Input Channel Select Bit 0 */
#define ADC10INCH1          (0x0002)    /* ADC10 Input Channel Select Bit 1 */
#define ADC10INCH2          (0x0004)    /* ADC10 Input Channel Select Bit 2 */
#define ADC10INCH3          (0x0008)    /* ADC10 Input Channel Select Bit 3 */
#define ADC10SREF0          (0x0010)    /* ADC10 Select Reference Bit 0 */
#define ADC10SREF1          (0x0020)    /* ADC10 Select Reference Bit 1 */
#define ADC10SREF2          (0x0040)    /* ADC10 Select Reference Bit 2 */

/* ADC10MCTL0 Control Bits */
#define ADC10INCH0_L        (0x0001)    /* ADC10 Input Channel Select Bit 0 */
#define ADC10INCH1_L        (0x0002)    /* ADC10 Input Channel Select Bit 1 */
#define ADC10INCH2_L        (0x0004)    /* ADC10 Input Channel Select Bit 2 */
#define ADC10INCH3_L        (0x0008)    /* ADC10 Input Channel Select Bit 3 */
#define ADC10SREF0_L        (0x0010)    /* ADC10 Select Reference Bit 0 */
#define ADC10SREF1_L        (0x0020)    /* ADC10 Select Reference Bit 1 */
#define ADC10SREF2_L        (0x0040)    /* ADC10 Select Reference Bit 2 */

/* ADC10MCTL0 Control Bits */

#define ADC10INCH_0         (0)         /* ADC10 Input Channel 0 */
#define ADC10INCH_1         (1)         /* ADC10 Input Channel 1 */
#define ADC10INCH_2         (2)         /* ADC10 Input Channel 2 */
#define ADC10INCH_3         (3)         /* ADC10 Input Channel 3 */
#define ADC10INCH_4         (4)         /* ADC10 Input Channel 4 */
#define ADC10INCH_5         (5)         /* ADC10 Input Channel 5 */
#define ADC10INCH_6         (6)         /* ADC10 Input Channel 6 */
#define ADC10INCH_7         (7)         /* ADC10 Input Channel 7 */
#define ADC10INCH_8         (8)         /* ADC10 Input Channel 8 */
#define ADC10INCH_9         (9)         /* ADC10 Input Channel 9 */
#define ADC10INCH_10        (10)        /* ADC10 Input Channel 10 */
#define ADC10INCH_11        (11)        /* ADC10 Input Channel 11 */
#define ADC10INCH_12        (12)        /* ADC10 Input Channel 12 */
#define ADC10INCH_13        (13)        /* ADC10 Input Channel 13 */
#define ADC10INCH_14        (14)        /* ADC10 Input Channel 14 */
#define ADC10INCH_15        (15)        /* ADC10 Input Channel 15 */

#define ADC10SREF_0         (0x0000)    /* ADC10 Select Reference 0 */
#define ADC10SREF_1         (0x0010)    /* ADC10 Select Reference 1 */
#define ADC10SREF_2         (0x0020)    /* ADC10 Select Reference 2 */
#define ADC10SREF_3         (0x0030)    /* ADC10 Select Reference 3 */
#define ADC10SREF_4         (0x0040)    /* ADC10 Select Reference 4 */
#define ADC10SREF_5         (0x0050)    /* ADC10 Select Reference 5 */
#define ADC10SREF_6         (0x0060)    /* ADC10 Select Reference 6 */
#define ADC10SREF_7         (0x0070)    /* ADC10 Select Reference 7 */

/* ADC10IE Interrupt Enable Bits */
#define ADC10IE0            (0x0001)    /* ADC10_A Interrupt enable */
#define ADC10INIE           (0x0002)    /* ADC10_A Interrupt enable for the inside of window of the Window comparator */
#define ADC10LOIE           (0x0004)    /* ADC10_A Interrupt enable for lower threshold of the Window comparator */
#define ADC10HIIE           (0x0008)    /* ADC10_A Interrupt enable for upper threshold of the Window comparator */
#define ADC10OVIE           (0x0010)    /* ADC10_A ADC10MEM overflow Interrupt enable */
#define ADC10TOVIE          (0x0020)    /* ADC10_A conversion-time-overflow Interrupt enable */

/* ADC10IE Interrupt Enable Bits */
#define ADC10IE0_L          (0x0001)    /* ADC10_A Interrupt enable */
#define ADC10INIE_L         (0x0002)    /* ADC10_A Interrupt enable for the inside of window of the Window comparator */
#define ADC10LOIE_L         (0x0004)    /* ADC10_A Interrupt enable for lower threshold of the Window comparator */
#define ADC10HIIE_L         (0x0008)    /* ADC10_A Interrupt enable for upper threshold of the Window comparator */
#define ADC10OVIE_L         (0x0010)    /* ADC10_A ADC10MEM overflow Interrupt enable */
#define ADC10TOVIE_L        (0x0020)    /* ADC10_A conversion-time-overflow Interrupt enable */

/* ADC10IE Interrupt Enable Bits */

/* ADC10IFG Interrupt Flag Bits */
#define ADC10IFG0           (0x0001)    /* ADC10_A Interrupt Flag */
#define ADC10INIFG          (0x0002)    /* ADC10_A Interrupt Flag for the inside of window of the Window comparator */
#define ADC10LOIFG          (0x0004)    /* ADC10_A Interrupt Flag for lower threshold of the Window comparator */
#define ADC10HIIFG          (0x0008)    /* ADC10_A Interrupt Flag for upper threshold of the Window comparator */
#define ADC10OVIFG          (0x0010)    /* ADC10_A ADC10MEM overflow Interrupt Flag */
#define ADC10TOVIFG         (0x0020)    /* ADC10_A conversion-time-overflow Interrupt Flag */

/* ADC10IFG Interrupt Flag Bits */
#define ADC10IFG0_L         (0x0001)    /* ADC10_A Interrupt Flag */
#define ADC10INIFG_L        (0x0002)    /* ADC10_A Interrupt Flag for the inside of window of the Window comparator */
#define ADC10LOIFG_L        (0x0004)    /* ADC10_A Interrupt Flag for lower threshold of the Window comparator */
#define ADC10HIIFG_L        (0x0008)    /* ADC10_A Interrupt Flag for upper threshold of the Window comparator */
#define ADC10OVIFG_L        (0x0010)    /* ADC10_A ADC10MEM overflow Interrupt Flag */
#define ADC10TOVIFG_L       (0x0020)    /* ADC10_A conversion-time-overflow Interrupt Flag */

/* ADC10IFG Interrupt Flag Bits */

/* ADC10IV Definitions */
#define ADC10IV_NONE        (0x0000)    /* No Interrupt pending */
#define ADC10IV_ADC10OVIFG  (0x0002)    /* ADC10OVIFG */
#define ADC10IV_ADC10TOVIFG (0x0004)    /* ADC10TOVIFG */
#define ADC10IV_ADC10HIIFG  (0x0006)    /* ADC10HIIFG */
#define ADC10IV_ADC10LOIFG  (0x0008)    /* ADC10LOIFG */
#define ADC10IV_ADC10INIFG  (0x000A)    /* ADC10INIFG */
#define ADC10IV_ADC10IFG    (0x000C)    /* ADC10IFG */

/************************************************************
* CLOCK SYSTEM
************************************************************/
#define __MSP430_HAS_CS__              /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CS__ 0x0160
#define CS_BASE __MSP430_BASEADDRESS_CS__

#define CSCTL0_               0x0160    /* CS Control Register 0 */
#define CSCTL0_L (*(volatile uint8_t *)0x160)
#define CSCTL0 (*(volatile uint16_t *)0x160)
#define CSCTL0_H (*(volatile uint8_t *)0x161)
#define CSCTL0_L (*(volatile uint8_t *)0x160)
#define CSCTL0 (*(volatile uint16_t *)0x160)
#define CSCTL1_               0x0162    /* CS Control Register 1 */
#define CSCTL1_L (*(volatile uint8_t *)0x162)
#define CSCTL1 (*(volatile uint16_t *)0x162)
#define CSCTL1_H (*(volatile uint8_t *)0x163)
#define CSCTL1_L (*(volatile uint8_t *)0x162)
#define CSCTL1 (*(volatile uint16_t *)0x162)
#define CSCTL2_               0x0164    /* CS Control Register 2 */
#define CSCTL2_L (*(volatile uint8_t *)0x164)
#define CSCTL2 (*(volatile uint16_t *)0x164)
#define CSCTL2_H (*(volatile uint8_t *)0x165)
#define CSCTL2_L (*(volatile uint8_t *)0x164)
#define CSCTL2 (*(volatile uint16_t *)0x164)
#define CSCTL3_               0x0166    /* CS Control Register 3 */
#define CSCTL3_L (*(volatile uint8_t *)0x166)
#define CSCTL3 (*(volatile uint16_t *)0x166)
#define CSCTL3_H (*(volatile uint8_t *)0x167)
#define CSCTL3_L (*(volatile uint8_t *)0x166)
#define CSCTL3 (*(volatile uint16_t *)0x166)
#define CSCTL4_               0x0168    /* CS Control Register 4 */
#define CSCTL4_L (*(volatile uint8_t *)0x168)
#define CSCTL4 (*(volatile uint16_t *)0x168)
#define CSCTL4_H (*(volatile uint8_t *)0x169)
#define CSCTL4_L (*(volatile uint8_t *)0x168)
#define CSCTL4 (*(volatile uint16_t *)0x168)
#define CSCTL5_               0x016A    /* CS Control Register 5 */
#define CSCTL5_L (*(volatile uint8_t *)0x16a)
#define CSCTL5 (*(volatile uint16_t *)0x16a)
#define CSCTL5_H (*(volatile uint8_t *)0x16b)
#define CSCTL5_L (*(volatile uint8_t *)0x16a)
#define CSCTL5 (*(volatile uint16_t *)0x16a)
#define CSCTL6_               0x016C    /* CS Control Register 6 */
#define CSCTL6_L (*(volatile uint8_t *)0x16c)
#define CSCTL6 (*(volatile uint16_t *)0x16c)
#define CSCTL6_H (*(volatile uint8_t *)0x16d)
#define CSCTL6_L (*(volatile uint8_t *)0x16c)
#define CSCTL6 (*(volatile uint16_t *)0x16c)

/* CSCTL0 Control Bits */

/* CSCTL0 Control Bits */

/* CSCTL0 Control Bits */
#define CSKEY                (0xA500)    /* CS Password */

/* CSCTL1 Control Bits */
#define DCOFSEL0            (0x0002)    /* DCO frequency select Bit: 0 */
#define DCOFSEL1            (0x0004)    /* DCO frequency select Bit: 1 */
#define DCORSEL             (0x0080)    /* DCO range select. */

/* CSCTL1 Control Bits */
#define DCOFSEL0_L          (0x0002)    /* DCO frequency select Bit: 0 */
#define DCOFSEL1_L          (0x0004)    /* DCO frequency select Bit: 1 */
#define DCORSEL_L           (0x0080)    /* DCO range select. */

/* CSCTL1 Control Bits */

#define DCOFSEL_0           (0x0000)    /* DCO frequency select: 0 */
#define DCOFSEL_1           (0x0002)    /* DCO frequency select: 1 */
#define DCOFSEL_2           (0x0004)    /* DCO frequency select: 2 */
#define DCOFSEL_3           (0x0006)    /* DCO frequency select: 3 */


/* CSCTL2 Control Bits */
#define SELM0               (0x0001)   /* MCLK Source Select Bit: 0 */
#define SELM1               (0x0002)   /* MCLK Source Select Bit: 1 */
#define SELM2               (0x0004)   /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
#define SELS0               (0x0010)   /* SMCLK Source Select Bit: 0 */
#define SELS1               (0x0020)   /* SMCLK Source Select Bit: 1 */
#define SELS2               (0x0040)   /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
#define SELA0               (0x0100)   /* ACLK Source Select Bit: 0 */
#define SELA1               (0x0200)   /* ACLK Source Select Bit: 1 */
#define SELA2               (0x0400)   /* ACLK Source Select Bit: 2 */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* CSCTL2 Control Bits */
#define SELM0_L             (0x0001)   /* MCLK Source Select Bit: 0 */
#define SELM1_L             (0x0002)   /* MCLK Source Select Bit: 1 */
#define SELM2_L             (0x0004)   /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
#define SELS0_L             (0x0010)   /* SMCLK Source Select Bit: 0 */
#define SELS1_L             (0x0020)   /* SMCLK Source Select Bit: 1 */
#define SELS2_L             (0x0040)   /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* CSCTL2 Control Bits */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
#define SELA0_H             (0x0001)   /* ACLK Source Select Bit: 0 */
#define SELA1_H             (0x0002)   /* ACLK Source Select Bit: 1 */
#define SELA2_H             (0x0004)   /* ACLK Source Select Bit: 2 */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

#define SELM_0              (0x0000)   /* MCLK Source Select 0 */
#define SELM_1              (0x0001)   /* MCLK Source Select 1 */
#define SELM_2              (0x0002)   /* MCLK Source Select 2 */
#define SELM_3              (0x0003)   /* MCLK Source Select 3 */
#define SELM_4              (0x0004)   /* MCLK Source Select 4 */
#define SELM_5              (0x0005)   /* MCLK Source Select 5 */
#define SELM_6              (0x0006)   /* MCLK Source Select 6 */
#define SELM_7              (0x0007)   /* MCLK Source Select 7 */
#define SELM__XT1CLK        (0x0000)   /* MCLK Source Select XT1CLK */
#define SELM__VLOCLK        (0x0001)   /* MCLK Source Select VLOCLK */
#define SELM__DCOCLK        (0x0003)   /* MCLK Source Select DCOCLK */
#define SELM__XT2CLK        (0x0005)   /* MCLK Source Select XT2CLK */

#define SELS_0              (0x0000)   /* SMCLK Source Select 0 */
#define SELS_1              (0x0010)   /* SMCLK Source Select 1 */
#define SELS_2              (0x0020)   /* SMCLK Source Select 2 */
#define SELS_3              (0x0030)   /* SMCLK Source Select 3 */
#define SELS_4              (0x0040)   /* SMCLK Source Select 4 */
#define SELS_5              (0x0050)   /* SMCLK Source Select 5 */
#define SELS_6              (0x0060)   /* SMCLK Source Select 6 */
#define SELS_7              (0x0070)   /* SMCLK Source Select 7 */
#define SELS__XT1CLK        (0x0000)   /* SMCLK Source Select XT1CLK */
#define SELS__VLOCLK        (0x0010)   /* SMCLK Source Select VLOCLK */
#define SELS__DCOCLK        (0x0030)   /* SMCLK Source Select DCOCLK */
#define SELS__XT2CLK        (0x0050)   /* SMCLK Source Select XT2CLK */

#define SELA_0              (0x0000)   /* ACLK Source Select 0 */
#define SELA_1              (0x0100)   /* ACLK Source Select 1 */
#define SELA_2              (0x0200)   /* ACLK Source Select 2 */
#define SELA_3              (0x0300)   /* ACLK Source Select 3 */
#define SELA_4              (0x0400)   /* ACLK Source Select 4 */
#define SELA_5              (0x0500)   /* ACLK Source Select 5 */
#define SELA_6              (0x0600)   /* ACLK Source Select 6 */
#define SELA_7              (0x0700)   /* ACLK Source Select 7 */
#define SELA__XT1CLK        (0x0000)   /* ACLK Source Select XT1CLK */
#define SELA__VLOCLK        (0x0100)   /* ACLK Source Select VLOCLK */
#define SELA__DCOCLK        (0x0300)   /* ACLK Source Select DCOCLK */
#define SELA__XT2CLK        (0x0500)   /* ACLK Source Select XT2CLK */

/* CSCTL3 Control Bits */
#define DIVM0               (0x0001)   /* MCLK Divider Bit: 0 */
#define DIVM1               (0x0002)   /* MCLK Divider Bit: 1 */
#define DIVM2               (0x0004)   /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
#define DIVS0               (0x0010)   /* SMCLK Divider Bit: 0 */
#define DIVS1               (0x0020)   /* SMCLK Divider Bit: 1 */
#define DIVS2               (0x0040)   /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
#define DIVA0               (0x0100)   /* ACLK Divider Bit: 0 */
#define DIVA1               (0x0200)   /* ACLK Divider Bit: 1 */
#define DIVA2               (0x0400)   /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* CSCTL3 Control Bits */
#define DIVM0_L             (0x0001)   /* MCLK Divider Bit: 0 */
#define DIVM1_L             (0x0002)   /* MCLK Divider Bit: 1 */
#define DIVM2_L             (0x0004)   /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
#define DIVS0_L             (0x0010)   /* SMCLK Divider Bit: 0 */
#define DIVS1_L             (0x0020)   /* SMCLK Divider Bit: 1 */
#define DIVS2_L             (0x0040)   /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* CSCTL3 Control Bits */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
#define DIVA0_H             (0x0001)   /* ACLK Divider Bit: 0 */
#define DIVA1_H             (0x0002)   /* ACLK Divider Bit: 1 */
#define DIVA2_H             (0x0004)   /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

#define DIVM_0              (0x0000)    /* MCLK Source Divider 0 */
#define DIVM_1              (0x0001)    /* MCLK Source Divider 1 */
#define DIVM_2              (0x0002)    /* MCLK Source Divider 2 */
#define DIVM_3              (0x0003)    /* MCLK Source Divider 3 */
#define DIVM_4              (0x0004)    /* MCLK Source Divider 4 */
#define DIVM_5              (0x0005)    /* MCLK Source Divider 5 */
#define DIVM__1             (0x0000)    /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2             (0x0001)    /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4             (0x0002)    /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8             (0x0003)    /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16            (0x0004)    /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32            (0x0005)    /* MCLK Source Divider f(MCLK)/32 */

#define DIVS_0              (0x0000)    /* SMCLK Source Divider 0 */
#define DIVS_1              (0x0010)    /* SMCLK Source Divider 1 */
#define DIVS_2              (0x0020)    /* SMCLK Source Divider 2 */
#define DIVS_3              (0x0030)    /* SMCLK Source Divider 3 */
#define DIVS_4              (0x0040)    /* SMCLK Source Divider 4 */
#define DIVS_5              (0x0050)    /* SMCLK Source Divider 5 */
#define DIVS__1             (0x0000)    /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2             (0x0010)    /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4             (0x0020)    /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8             (0x0030)    /* SMCLK Source Divider f(SMCLK)/8 */
#define DIVS__16            (0x0040)    /* SMCLK Source Divider f(SMCLK)/16 */
#define DIVS__32            (0x0050)    /* SMCLK Source Divider f(SMCLK)/32 */

#define DIVA_0              (0x0000)    /* ACLK Source Divider 0 */
#define DIVA_1              (0x0100)    /* ACLK Source Divider 1 */
#define DIVA_2              (0x0200)    /* ACLK Source Divider 2 */
#define DIVA_3              (0x0300)    /* ACLK Source Divider 3 */
#define DIVA_4              (0x0400)    /* ACLK Source Divider 4 */
#define DIVA_5              (0x0500)    /* ACLK Source Divider 5 */
#define DIVA__1             (0x0000)    /* ACLK Source Divider f(ACLK)/1 */
#define DIVA__2             (0x0100)    /* ACLK Source Divider f(ACLK)/2 */
#define DIVA__4             (0x0200)    /* ACLK Source Divider f(ACLK)/4 */
#define DIVA__8             (0x0300)    /* ACLK Source Divider f(ACLK)/8 */
#define DIVA__16            (0x0400)    /* ACLK Source Divider f(ACLK)/16 */
#define DIVA__32            (0x0500)    /* ACLK Source Divider f(ACLK)/32 */


/* CSCTL4 Control Bits */
#define XT1OFF              (0x0001)    /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF            (0x0002)    /* SMCLK Off */
#define XT1BYPASS           (0x0010)    /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS                 (0x0020)    /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0           (0x0040)    /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1           (0x0080)    /* XT1 Drive Level mode Bit 1 */
#define XT2OFF              (0x0100)    /* High Frequency Oscillator 2 (XT2) disable */
#define XT2BYPASS           (0x1000)    /* XT2 bypass mode : 0: internal 1:sourced from external pin */
#define XT2DRIVE0           (0x4000)    /* XT2 Drive Level mode Bit 0 */
#define XT2DRIVE1           (0x8000)    /* XT2 Drive Level mode Bit 1 */

/* CSCTL4 Control Bits */
#define XT1OFF_L            (0x0001)    /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF_L          (0x0002)    /* SMCLK Off */
#define XT1BYPASS_L         (0x0010)    /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS_L               (0x0020)    /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0_L         (0x0040)    /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1_L         (0x0080)    /* XT1 Drive Level mode Bit 1 */

/* CSCTL4 Control Bits */
#define XT2OFF_H            (0x0001)    /* High Frequency Oscillator 2 (XT2) disable */
#define XT2BYPASS_H         (0x0010)    /* XT2 bypass mode : 0: internal 1:sourced from external pin */
#define XT2DRIVE0_H         (0x0040)    /* XT2 Drive Level mode Bit 0 */
#define XT2DRIVE1_H         (0x0080)    /* XT2 Drive Level mode Bit 1 */

#define XT1DRIVE_0          (0x0000)    /* XT1 Drive Level mode: 0 */
#define XT1DRIVE_1          (0x0040)    /* XT1 Drive Level mode: 1 */
#define XT1DRIVE_2          (0x0080)    /* XT1 Drive Level mode: 2 */
#define XT1DRIVE_3          (0x00C0)    /* XT1 Drive Level mode: 3 */
#define XT2DRIVE_0          (0x0000)    /* XT2 Drive Level mode: 0 */
#define XT2DRIVE_1          (0x4000)    /* XT2 Drive Level mode: 1 */
#define XT2DRIVE_2          (0x8000)    /* XT2 Drive Level mode: 2 */
#define XT2DRIVE_3          (0xC000)    /* XT2 Drive Level mode: 3 */


/* CSCTL5 Control Bits */
#define XT1OFFG             (0x0001)    /* XT1 Low Frequency Oscillator Fault Flag */
#define XT2OFFG             (0x0002)    /* High Frequency Oscillator 2 Fault Flag */
#define ENSTFCNT1           (0x0040)    /* Enable start counter for XT1 */
#define ENSTFCNT2           (0x0080)    /* Enable start counter for XT2 */

/* CSCTL5 Control Bits */
#define XT1OFFG_L           (0x0001)    /* XT1 Low Frequency Oscillator Fault Flag */
#define XT2OFFG_L           (0x0002)    /* High Frequency Oscillator 2 Fault Flag */
#define ENSTFCNT1_L         (0x0040)    /* Enable start counter for XT1 */
#define ENSTFCNT2_L         (0x0080)    /* Enable start counter for XT2 */

/* CSCTL5 Control Bits */

/* CSCTL6 Control Bits */
#define ACLKREQEN           (0x0001)    /* ACLK Clock Request Enable */
#define MCLKREQEN           (0x0002)    /* MCLK Clock Request Enable */
#define SMCLKREQEN          (0x0004)    /* SMCLK Clock Request Enable */
#define MODCLKREQEN         (0x0008)    /* MODOSC Clock Request Enable */

/* CSCTL6 Control Bits */
#define ACLKREQEN_L         (0x0001)    /* ACLK Clock Request Enable */
#define MCLKREQEN_L         (0x0002)    /* MCLK Clock Request Enable */
#define SMCLKREQEN_L        (0x0004)    /* SMCLK Clock Request Enable */
#define MODCLKREQEN_L       (0x0008)    /* MODOSC Clock Request Enable */

/* CSCTL6 Control Bits */

/************************************************************
* Comparator D
************************************************************/
#define __MSP430_HAS_COMPD__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_COMPD__ 0x08C0
#define COMP_D_BASE __MSP430_BASEADDRESS_COMPD__

#define CDCTL0_               0x08C0    /* Comparator D Control Register 0 */
#define CDCTL0_L (*(volatile uint8_t *)0x8c0)
#define CDCTL0 (*(volatile uint16_t *)0x8c0)
#define CDCTL0_H (*(volatile uint8_t *)0x8c1)
#define CDCTL0_L (*(volatile uint8_t *)0x8c0)
#define CDCTL0 (*(volatile uint16_t *)0x8c0)
#define CDCTL1_               0x08C2    /* Comparator D Control Register 1 */
#define CDCTL1_L (*(volatile uint8_t *)0x8c2)
#define CDCTL1 (*(volatile uint16_t *)0x8c2)
#define CDCTL1_H (*(volatile uint8_t *)0x8c3)
#define CDCTL1_L (*(volatile uint8_t *)0x8c2)
#define CDCTL1 (*(volatile uint16_t *)0x8c2)
#define CDCTL2_               0x08C4    /* Comparator D Control Register 2 */
#define CDCTL2_L (*(volatile uint8_t *)0x8c4)
#define CDCTL2 (*(volatile uint16_t *)0x8c4)
#define CDCTL2_H (*(volatile uint8_t *)0x8c5)
#define CDCTL2_L (*(volatile uint8_t *)0x8c4)
#define CDCTL2 (*(volatile uint16_t *)0x8c4)
#define CDCTL3_               0x08C6    /* Comparator D Control Register 3 */
#define CDCTL3_L (*(volatile uint8_t *)0x8c6)
#define CDCTL3 (*(volatile uint16_t *)0x8c6)
#define CDCTL3_H (*(volatile uint8_t *)0x8c7)
#define CDCTL3_L (*(volatile uint8_t *)0x8c6)
#define CDCTL3 (*(volatile uint16_t *)0x8c6)
#define CDINT_                0x08CC    /* Comparator D Interrupt Register */
#define CDINT_L (*(volatile uint8_t *)0x8cc)
#define CDINT (*(volatile uint16_t *)0x8cc)
#define CDINT_H (*(volatile uint8_t *)0x8cd)
#define CDINT_L (*(volatile uint8_t *)0x8cc)
#define CDINT (*(volatile uint16_t *)0x8cc)
#define CDIV_                 0x08CE    /* Comparator D Interrupt Vector Word */
#define CDIV_L (*(volatile uint8_t *)0x8ce)
#define CDIV (*(volatile uint16_t *)0x8ce)
#define CDIV_H (*(volatile uint8_t *)0x8cf)
#define CDIV_L (*(volatile uint8_t *)0x8ce)
#define CDIV (*(volatile uint16_t *)0x8ce)


/* CDCTL0 Control Bits */
#define CDIPSEL0            (0x0001)  /* Comp. D Pos. Channel Input Select 0 */
#define CDIPSEL1            (0x0002)  /* Comp. D Pos. Channel Input Select 1 */
#define CDIPSEL2            (0x0004)  /* Comp. D Pos. Channel Input Select 2 */
#define CDIPSEL3            (0x0008)  /* Comp. D Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010)  /* Comp. D */
//#define RESERVED            (0x0020)  /* Comp. D */
//#define RESERVED            (0x0040)  /* Comp. D */
#define CDIPEN              (0x0080)  /* Comp. D Pos. Channel Input Enable */
#define CDIMSEL0            (0x0100)  /* Comp. D Neg. Channel Input Select 0 */
#define CDIMSEL1            (0x0200)  /* Comp. D Neg. Channel Input Select 1 */
#define CDIMSEL2            (0x0400)  /* Comp. D Neg. Channel Input Select 2 */
#define CDIMSEL3            (0x0800)  /* Comp. D Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000)  /* Comp. D */
//#define RESERVED            (0x2000)  /* Comp. D */
//#define RESERVED            (0x4000)  /* Comp. D */
#define CDIMEN              (0x8000)  /* Comp. D Neg. Channel Input Enable */

/* CDCTL0 Control Bits */
#define CDIPSEL0_L          (0x0001)  /* Comp. D Pos. Channel Input Select 0 */
#define CDIPSEL1_L          (0x0002)  /* Comp. D Pos. Channel Input Select 1 */
#define CDIPSEL2_L          (0x0004)  /* Comp. D Pos. Channel Input Select 2 */
#define CDIPSEL3_L          (0x0008)  /* Comp. D Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010)  /* Comp. D */
//#define RESERVED            (0x0020)  /* Comp. D */
//#define RESERVED            (0x0040)  /* Comp. D */
#define CDIPEN_L            (0x0080)  /* Comp. D Pos. Channel Input Enable */
//#define RESERVED            (0x1000)  /* Comp. D */
//#define RESERVED            (0x2000)  /* Comp. D */
//#define RESERVED            (0x4000)  /* Comp. D */

/* CDCTL0 Control Bits */
//#define RESERVED            (0x0010)  /* Comp. D */
//#define RESERVED            (0x0020)  /* Comp. D */
//#define RESERVED            (0x0040)  /* Comp. D */
#define CDIMSEL0_H          (0x0001)  /* Comp. D Neg. Channel Input Select 0 */
#define CDIMSEL1_H          (0x0002)  /* Comp. D Neg. Channel Input Select 1 */
#define CDIMSEL2_H          (0x0004)  /* Comp. D Neg. Channel Input Select 2 */
#define CDIMSEL3_H          (0x0008)  /* Comp. D Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000)  /* Comp. D */
//#define RESERVED            (0x2000)  /* Comp. D */
//#define RESERVED            (0x4000)  /* Comp. D */
#define CDIMEN_H            (0x0080)  /* Comp. D Neg. Channel Input Enable */

#define CDIPSEL_0           (0x0000)  /* Comp. D V+ terminal Input Select: Channel 0 */
#define CDIPSEL_1           (0x0001)  /* Comp. D V+ terminal Input Select: Channel 1 */
#define CDIPSEL_2           (0x0002)  /* Comp. D V+ terminal Input Select: Channel 2 */
#define CDIPSEL_3           (0x0003)  /* Comp. D V+ terminal Input Select: Channel 3 */
#define CDIPSEL_4           (0x0004)  /* Comp. D V+ terminal Input Select: Channel 4 */
#define CDIPSEL_5           (0x0005)  /* Comp. D V+ terminal Input Select: Channel 5 */
#define CDIPSEL_6           (0x0006)  /* Comp. D V+ terminal Input Select: Channel 6 */
#define CDIPSEL_7           (0x0007)  /* Comp. D V+ terminal Input Select: Channel 7 */
#define CDIPSEL_8           (0x0008)  /* Comp. D V+ terminal Input Select: Channel 8 */
#define CDIPSEL_9           (0x0009)  /* Comp. D V+ terminal Input Select: Channel 9 */
#define CDIPSEL_10          (0x000A)  /* Comp. D V+ terminal Input Select: Channel 10 */
#define CDIPSEL_11          (0x000B)  /* Comp. D V+ terminal Input Select: Channel 11 */
#define CDIPSEL_12          (0x000C)  /* Comp. D V+ terminal Input Select: Channel 12 */
#define CDIPSEL_13          (0x000D)  /* Comp. D V+ terminal Input Select: Channel 13 */
#define CDIPSEL_14          (0x000E)  /* Comp. D V+ terminal Input Select: Channel 14 */
#define CDIPSEL_15          (0x000F)  /* Comp. D V+ terminal Input Select: Channel 15 */

#define CDIMSEL_0           (0x0000)  /* Comp. D V- Terminal Input Select: Channel 0 */
#define CDIMSEL_1           (0x0100)  /* Comp. D V- Terminal Input Select: Channel 1 */
#define CDIMSEL_2           (0x0200)  /* Comp. D V- Terminal Input Select: Channel 2 */
#define CDIMSEL_3           (0x0300)  /* Comp. D V- Terminal Input Select: Channel 3 */
#define CDIMSEL_4           (0x0400)  /* Comp. D V- Terminal Input Select: Channel 4 */
#define CDIMSEL_5           (0x0500)  /* Comp. D V- Terminal Input Select: Channel 5 */
#define CDIMSEL_6           (0x0600)  /* Comp. D V- Terminal Input Select: Channel 6 */
#define CDIMSEL_7           (0x0700)  /* Comp. D V- Terminal Input Select: Channel 7 */
#define CDIMSEL_8           (0x0800)  /* Comp. D V- terminal Input Select: Channel 8 */
#define CDIMSEL_9           (0x0900)  /* Comp. D V- terminal Input Select: Channel 9 */
#define CDIMSEL_10          (0x0A00)  /* Comp. D V- terminal Input Select: Channel 10 */
#define CDIMSEL_11          (0x0B00)  /* Comp. D V- terminal Input Select: Channel 11 */
#define CDIMSEL_12          (0x0C00)  /* Comp. D V- terminal Input Select: Channel 12 */
#define CDIMSEL_13          (0x0D00)  /* Comp. D V- terminal Input Select: Channel 13 */
#define CDIMSEL_14          (0x0E00)  /* Comp. D V- terminal Input Select: Channel 14 */
#define CDIMSEL_15          (0x0F00)  /* Comp. D V- terminal Input Select: Channel 15 */

/* CDCTL1 Control Bits */
#define CDOUT               (0x0001)  /* Comp. D Output */
#define CDOUTPOL            (0x0002)  /* Comp. D Output Polarity */
#define CDF                 (0x0004)  /* Comp. D Enable Output Filter */
#define CDIES               (0x0008)  /* Comp. D Interrupt Edge Select */
#define CDSHORT             (0x0010)  /* Comp. D Input Short */
#define CDEX                (0x0020)  /* Comp. D Exchange Inputs */
#define CDFDLY0             (0x0040)  /* Comp. D Filter delay Bit 0 */
#define CDFDLY1             (0x0080)  /* Comp. D Filter delay Bit 1 */
//#define RESERVED            (0x0100)  /* Comp. D */
//#define RESERVED            (0x0200)  /* Comp. D */
#define CDON                (0x0400)  /* Comp. D enable */
#define CDMRVL              (0x0800)  /* Comp. D CDMRV Level */
#define CDMRVS              (0x1000)  /* Comp. D Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000)  /* Comp. D */
//#define RESERVED            (0x4000)  /* Comp. D */
//#define RESERVED            (0x8000)  /* Comp. D */

/* CDCTL1 Control Bits */
#define CDOUT_L             (0x0001)  /* Comp. D Output */
#define CDOUTPOL_L          (0x0002)  /* Comp. D Output Polarity */
#define CDF_L               (0x0004)  /* Comp. D Enable Output Filter */
#define CDIES_L             (0x0008)  /* Comp. D Interrupt Edge Select */
#define CDSHORT_L           (0x0010)  /* Comp. D Input Short */
#define CDEX_L              (0x0020)  /* Comp. D Exchange Inputs */
#define CDFDLY0_L           (0x0040)  /* Comp. D Filter delay Bit 0 */
#define CDFDLY1_L           (0x0080)  /* Comp. D Filter delay Bit 1 */
//#define RESERVED            (0x0100)  /* Comp. D */
//#define RESERVED            (0x0200)  /* Comp. D */
//#define RESERVED            (0x2000)  /* Comp. D */
//#define RESERVED            (0x4000)  /* Comp. D */
//#define RESERVED            (0x8000)  /* Comp. D */

/* CDCTL1 Control Bits */
//#define RESERVED            (0x0100)  /* Comp. D */
//#define RESERVED            (0x0200)  /* Comp. D */
#define CDON_H              (0x0004)  /* Comp. D enable */
#define CDMRVL_H            (0x0008)  /* Comp. D CDMRV Level */
#define CDMRVS_H            (0x0010)  /* Comp. D Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000)  /* Comp. D */
//#define RESERVED            (0x4000)  /* Comp. D */
//#define RESERVED            (0x8000)  /* Comp. D */

#define CDFDLY_0           (0x0000)  /* Comp. D Filter delay 0 : 450ns */
#define CDFDLY_1           (0x0040)  /* Comp. D Filter delay 1 : 900ns */
#define CDFDLY_2           (0x0080)  /* Comp. D Filter delay 2 : 1800ns */
#define CDFDLY_3           (0x00C0)  /* Comp. D Filter delay 3 : 3600ns */


/* CDCTL2 Control Bits */
#define CDREF00             (0x0001)  /* Comp. D Reference 0 Resistor Select Bit : 0 */
#define CDREF01             (0x0002)  /* Comp. D Reference 0 Resistor Select Bit : 1 */
#define CDREF02             (0x0004)  /* Comp. D Reference 0 Resistor Select Bit : 2 */
#define CDREF03             (0x0008)  /* Comp. D Reference 0 Resistor Select Bit : 3 */
#define CDREF04             (0x0010)  /* Comp. D Reference 0 Resistor Select Bit : 4 */
#define CDRSEL              (0x0020)  /* Comp. D Reference select */
#define CDRS0               (0x0040)  /* Comp. D Reference Source Bit : 0 */
#define CDRS1               (0x0080)  /* Comp. D Reference Source Bit : 1 */
#define CDREF10             (0x0100)  /* Comp. D Reference 1 Resistor Select Bit : 0 */
#define CDREF11             (0x0200)  /* Comp. D Reference 1 Resistor Select Bit : 1 */
#define CDREF12             (0x0400)  /* Comp. D Reference 1 Resistor Select Bit : 2 */
#define CDREF13             (0x0800)  /* Comp. D Reference 1 Resistor Select Bit : 3 */
#define CDREF14             (0x1000)  /* Comp. D Reference 1 Resistor Select Bit : 4 */
#define CDREFL0             (0x2000)  /* Comp. D Reference voltage level Bit : 0 */
#define CDREFL1             (0x4000)  /* Comp. D Reference voltage level Bit : 1 */
#define CDREFACC            (0x8000)  /* Comp. D Reference Accuracy */

/* CDCTL2 Control Bits */
#define CDREF00_L           (0x0001)  /* Comp. D Reference 0 Resistor Select Bit : 0 */
#define CDREF01_L           (0x0002)  /* Comp. D Reference 0 Resistor Select Bit : 1 */
#define CDREF02_L           (0x0004)  /* Comp. D Reference 0 Resistor Select Bit : 2 */
#define CDREF03_L           (0x0008)  /* Comp. D Reference 0 Resistor Select Bit : 3 */
#define CDREF04_L           (0x0010)  /* Comp. D Reference 0 Resistor Select Bit : 4 */
#define CDRSEL_L            (0x0020)  /* Comp. D Reference select */
#define CDRS0_L             (0x0040)  /* Comp. D Reference Source Bit : 0 */
#define CDRS1_L             (0x0080)  /* Comp. D Reference Source Bit : 1 */

/* CDCTL2 Control Bits */
#define CDREF10_H           (0x0001)  /* Comp. D Reference 1 Resistor Select Bit : 0 */
#define CDREF11_H           (0x0002)  /* Comp. D Reference 1 Resistor Select Bit : 1 */
#define CDREF12_H           (0x0004)  /* Comp. D Reference 1 Resistor Select Bit : 2 */
#define CDREF13_H           (0x0008)  /* Comp. D Reference 1 Resistor Select Bit : 3 */
#define CDREF14_H           (0x0010)  /* Comp. D Reference 1 Resistor Select Bit : 4 */
#define CDREFL0_H           (0x0020)  /* Comp. D Reference voltage level Bit : 0 */
#define CDREFL1_H           (0x0040)  /* Comp. D Reference voltage level Bit : 1 */
#define CDREFACC_H          (0x0080)  /* Comp. D Reference Accuracy */

#define CDREF0_0            (0x0000)  /* Comp. D Int. Ref.0 Select 0 : 1/32 */
#define CDREF0_1            (0x0001)  /* Comp. D Int. Ref.0 Select 1 : 2/32 */
#define CDREF0_2            (0x0002)  /* Comp. D Int. Ref.0 Select 2 : 3/32 */
#define CDREF0_3            (0x0003)  /* Comp. D Int. Ref.0 Select 3 : 4/32 */
#define CDREF0_4            (0x0004)  /* Comp. D Int. Ref.0 Select 4 : 5/32 */
#define CDREF0_5            (0x0005)  /* Comp. D Int. Ref.0 Select 5 : 6/32 */
#define CDREF0_6            (0x0006)  /* Comp. D Int. Ref.0 Select 6 : 7/32 */
#define CDREF0_7            (0x0007)  /* Comp. D Int. Ref.0 Select 7 : 8/32 */
#define CDREF0_8            (0x0008)  /* Comp. D Int. Ref.0 Select 0 : 9/32 */
#define CDREF0_9            (0x0009)  /* Comp. D Int. Ref.0 Select 1 : 10/32 */
#define CDREF0_10           (0x000A)  /* Comp. D Int. Ref.0 Select 2 : 11/32 */
#define CDREF0_11           (0x000B)  /* Comp. D Int. Ref.0 Select 3 : 12/32 */
#define CDREF0_12           (0x000C)  /* Comp. D Int. Ref.0 Select 4 : 13/32 */
#define CDREF0_13           (0x000D)  /* Comp. D Int. Ref.0 Select 5 : 14/32 */
#define CDREF0_14           (0x000E)  /* Comp. D Int. Ref.0 Select 6 : 15/32 */
#define CDREF0_15           (0x000F)  /* Comp. D Int. Ref.0 Select 7 : 16/32 */
#define CDREF0_16           (0x0010)  /* Comp. D Int. Ref.0 Select 0 : 17/32 */
#define CDREF0_17           (0x0011)  /* Comp. D Int. Ref.0 Select 1 : 18/32 */
#define CDREF0_18           (0x0012)  /* Comp. D Int. Ref.0 Select 2 : 19/32 */
#define CDREF0_19           (0x0013)  /* Comp. D Int. Ref.0 Select 3 : 20/32 */
#define CDREF0_20           (0x0014)  /* Comp. D Int. Ref.0 Select 4 : 21/32 */
#define CDREF0_21           (0x0015)  /* Comp. D Int. Ref.0 Select 5 : 22/32 */
#define CDREF0_22           (0x0016)  /* Comp. D Int. Ref.0 Select 6 : 23/32 */
#define CDREF0_23           (0x0017)  /* Comp. D Int. Ref.0 Select 7 : 24/32 */
#define CDREF0_24           (0x0018)  /* Comp. D Int. Ref.0 Select 0 : 25/32 */
#define CDREF0_25           (0x0019)  /* Comp. D Int. Ref.0 Select 1 : 26/32 */
#define CDREF0_26           (0x001A)  /* Comp. D Int. Ref.0 Select 2 : 27/32 */
#define CDREF0_27           (0x001B)  /* Comp. D Int. Ref.0 Select 3 : 28/32 */
#define CDREF0_28           (0x001C)  /* Comp. D Int. Ref.0 Select 4 : 29/32 */
#define CDREF0_29           (0x001D)  /* Comp. D Int. Ref.0 Select 5 : 30/32 */
#define CDREF0_30           (0x001E)  /* Comp. D Int. Ref.0 Select 6 : 31/32 */
#define CDREF0_31           (0x001F)  /* Comp. D Int. Ref.0 Select 7 : 32/32 */

#define CDRS_0              (0x0000)  /* Comp. D Reference Source 0 : Off */
#define CDRS_1              (0x0040)  /* Comp. D Reference Source 1 : Vcc */
#define CDRS_2              (0x0080)  /* Comp. D Reference Source 2 : Shared Ref. */
#define CDRS_3              (0x00C0)  /* Comp. D Reference Source 3 : Shared Ref. / Off */

#define CDREF1_0            (0x0000)  /* Comp. D Int. Ref.1 Select 0 : 1/32 */
#define CDREF1_1            (0x0100)  /* Comp. D Int. Ref.1 Select 1 : 2/32 */
#define CDREF1_2            (0x0200)  /* Comp. D Int. Ref.1 Select 2 : 3/32 */
#define CDREF1_3            (0x0300)  /* Comp. D Int. Ref.1 Select 3 : 4/32 */
#define CDREF1_4            (0x0400)  /* Comp. D Int. Ref.1 Select 4 : 5/32 */
#define CDREF1_5            (0x0500)  /* Comp. D Int. Ref.1 Select 5 : 6/32 */
#define CDREF1_6            (0x0600)  /* Comp. D Int. Ref.1 Select 6 : 7/32 */
#define CDREF1_7            (0x0700)  /* Comp. D Int. Ref.1 Select 7 : 8/32 */
#define CDREF1_8            (0x0800)  /* Comp. D Int. Ref.1 Select 0 : 9/32 */
#define CDREF1_9            (0x0900)  /* Comp. D Int. Ref.1 Select 1 : 10/32 */
#define CDREF1_10           (0x0A00)  /* Comp. D Int. Ref.1 Select 2 : 11/32 */
#define CDREF1_11           (0x0B00)  /* Comp. D Int. Ref.1 Select 3 : 12/32 */
#define CDREF1_12           (0x0C00)  /* Comp. D Int. Ref.1 Select 4 : 13/32 */
#define CDREF1_13           (0x0D00)  /* Comp. D Int. Ref.1 Select 5 : 14/32 */
#define CDREF1_14           (0x0E00)  /* Comp. D Int. Ref.1 Select 6 : 15/32 */
#define CDREF1_15           (0x0F00)  /* Comp. D Int. Ref.1 Select 7 : 16/32 */
#define CDREF1_16           (0x1000)  /* Comp. D Int. Ref.1 Select 0 : 17/32 */
#define CDREF1_17           (0x1100)  /* Comp. D Int. Ref.1 Select 1 : 18/32 */
#define CDREF1_18           (0x1200)  /* Comp. D Int. Ref.1 Select 2 : 19/32 */
#define CDREF1_19           (0x1300)  /* Comp. D Int. Ref.1 Select 3 : 20/32 */
#define CDREF1_20           (0x1400)  /* Comp. D Int. Ref.1 Select 4 : 21/32 */
#define CDREF1_21           (0x1500)  /* Comp. D Int. Ref.1 Select 5 : 22/32 */
#define CDREF1_22           (0x1600)  /* Comp. D Int. Ref.1 Select 6 : 23/32 */
#define CDREF1_23           (0x1700)  /* Comp. D Int. Ref.1 Select 7 : 24/32 */
#define CDREF1_24           (0x1800)  /* Comp. D Int. Ref.1 Select 0 : 25/32 */
#define CDREF1_25           (0x1900)  /* Comp. D Int. Ref.1 Select 1 : 26/32 */
#define CDREF1_26           (0x1A00)  /* Comp. D Int. Ref.1 Select 2 : 27/32 */
#define CDREF1_27           (0x1B00)  /* Comp. D Int. Ref.1 Select 3 : 28/32 */
#define CDREF1_28           (0x1C00)  /* Comp. D Int. Ref.1 Select 4 : 29/32 */
#define CDREF1_29           (0x1D00)  /* Comp. D Int. Ref.1 Select 5 : 30/32 */
#define CDREF1_30           (0x1E00)  /* Comp. D Int. Ref.1 Select 6 : 31/32 */
#define CDREF1_31           (0x1F00)  /* Comp. D Int. Ref.1 Select 7 : 32/32 */

#define CDREFL_0            (0x0000)  /* Comp. D Reference voltage level 0 : None */
#define CDREFL_1            (0x2000)  /* Comp. D Reference voltage level 1 : 1.5V */
#define CDREFL_2            (0x4000)  /* Comp. D Reference voltage level 2 : 2.0V  */
#define CDREFL_3            (0x6000)  /* Comp. D Reference voltage level 3 : 2.5V  */


#define CDPD0               (0x0001)  /* Comp. D Disable Input Buffer of Port Register .0 */
#define CDPD1               (0x0002)  /* Comp. D Disable Input Buffer of Port Register .1 */
#define CDPD2               (0x0004)  /* Comp. D Disable Input Buffer of Port Register .2 */
#define CDPD3               (0x0008)  /* Comp. D Disable Input Buffer of Port Register .3 */
#define CDPD4               (0x0010)  /* Comp. D Disable Input Buffer of Port Register .4 */
#define CDPD5               (0x0020)  /* Comp. D Disable Input Buffer of Port Register .5 */
#define CDPD6               (0x0040)  /* Comp. D Disable Input Buffer of Port Register .6 */
#define CDPD7               (0x0080)  /* Comp. D Disable Input Buffer of Port Register .7 */
#define CDPD8               (0x0100)  /* Comp. D Disable Input Buffer of Port Register .8 */
#define CDPD9               (0x0200)  /* Comp. D Disable Input Buffer of Port Register .9 */
#define CDPD10              (0x0400)  /* Comp. D Disable Input Buffer of Port Register .10 */
#define CDPD11              (0x0800)  /* Comp. D Disable Input Buffer of Port Register .11 */
#define CDPD12              (0x1000)  /* Comp. D Disable Input Buffer of Port Register .12 */
#define CDPD13              (0x2000)  /* Comp. D Disable Input Buffer of Port Register .13 */
#define CDPD14              (0x4000)  /* Comp. D Disable Input Buffer of Port Register .14 */
#define CDPD15              (0x8000)  /* Comp. D Disable Input Buffer of Port Register .15 */

#define CDPD0_L             (0x0001)  /* Comp. D Disable Input Buffer of Port Register .0 */
#define CDPD1_L             (0x0002)  /* Comp. D Disable Input Buffer of Port Register .1 */
#define CDPD2_L             (0x0004)  /* Comp. D Disable Input Buffer of Port Register .2 */
#define CDPD3_L             (0x0008)  /* Comp. D Disable Input Buffer of Port Register .3 */
#define CDPD4_L             (0x0010)  /* Comp. D Disable Input Buffer of Port Register .4 */
#define CDPD5_L             (0x0020)  /* Comp. D Disable Input Buffer of Port Register .5 */
#define CDPD6_L             (0x0040)  /* Comp. D Disable Input Buffer of Port Register .6 */
#define CDPD7_L             (0x0080)  /* Comp. D Disable Input Buffer of Port Register .7 */

#define CDPD8_H             (0x0001)  /* Comp. D Disable Input Buffer of Port Register .8 */
#define CDPD9_H             (0x0002)  /* Comp. D Disable Input Buffer of Port Register .9 */
#define CDPD10_H            (0x0004)  /* Comp. D Disable Input Buffer of Port Register .10 */
#define CDPD11_H            (0x0008)  /* Comp. D Disable Input Buffer of Port Register .11 */
#define CDPD12_H            (0x0010)  /* Comp. D Disable Input Buffer of Port Register .12 */
#define CDPD13_H            (0x0020)  /* Comp. D Disable Input Buffer of Port Register .13 */
#define CDPD14_H            (0x0040)  /* Comp. D Disable Input Buffer of Port Register .14 */
#define CDPD15_H            (0x0080)  /* Comp. D Disable Input Buffer of Port Register .15 */


/* CDINT Control Bits */
#define CDIFG                (0x0001)  /* Comp. D Interrupt Flag */
#define CDIIFG               (0x0002)  /* Comp. D Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004)  /* Comp. D */
//#define RESERVED             (0x0008)  /* Comp. D */
//#define RESERVED             (0x0010)  /* Comp. D */
//#define RESERVED             (0x0020)  /* Comp. D */
//#define RESERVED             (0x0040)  /* Comp. D */
//#define RESERVED             (0x0080)  /* Comp. D */
#define CDIE                 (0x0100)  /* Comp. D Interrupt Enable */
#define CDIIE                (0x0200)  /* Comp. D Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400)  /* Comp. D */
//#define RESERVED             (0x0800)  /* Comp. D */
//#define RESERVED             (0x1000)  /* Comp. D */
//#define RESERVED             (0x2000)  /* Comp. D */
//#define RESERVED             (0x4000)  /* Comp. D */
//#define RESERVED             (0x8000)  /* Comp. D */

/* CDINT Control Bits */
#define CDIFG_L             (0x0001)  /* Comp. D Interrupt Flag */
#define CDIIFG_L            (0x0002)  /* Comp. D Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004)  /* Comp. D */
//#define RESERVED             (0x0008)  /* Comp. D */
//#define RESERVED             (0x0010)  /* Comp. D */
//#define RESERVED             (0x0020)  /* Comp. D */
//#define RESERVED             (0x0040)  /* Comp. D */
//#define RESERVED             (0x0080)  /* Comp. D */
//#define RESERVED             (0x0400)  /* Comp. D */
//#define RESERVED             (0x0800)  /* Comp. D */
//#define RESERVED             (0x1000)  /* Comp. D */
//#define RESERVED             (0x2000)  /* Comp. D */
//#define RESERVED             (0x4000)  /* Comp. D */
//#define RESERVED             (0x8000)  /* Comp. D */

/* CDINT Control Bits */
//#define RESERVED             (0x0004)  /* Comp. D */
//#define RESERVED             (0x0008)  /* Comp. D */
//#define RESERVED             (0x0010)  /* Comp. D */
//#define RESERVED             (0x0020)  /* Comp. D */
//#define RESERVED             (0x0040)  /* Comp. D */
//#define RESERVED             (0x0080)  /* Comp. D */
#define CDIE_H              (0x0001)  /* Comp. D Interrupt Enable */
#define CDIIE_H             (0x0002)  /* Comp. D Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400)  /* Comp. D */
//#define RESERVED             (0x0800)  /* Comp. D */
//#define RESERVED             (0x1000)  /* Comp. D */
//#define RESERVED             (0x2000)  /* Comp. D */
//#define RESERVED             (0x4000)  /* Comp. D */
//#define RESERVED             (0x8000)  /* Comp. D */

/* CDIV Definitions */
#define CDIV_NONE           (0x0000)    /* No Interrupt pending */
#define CDIV_CDIFG          (0x0002)    /* CDIFG */
#define CDIV_CDIIFG         (0x0004)    /* CDIIFG */

/*************************************************************
* CRC Module
*************************************************************/
#define __MSP430_HAS_CRC__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CRC__ 0x0150
#define CRC_BASE __MSP430_BASEADDRESS_CRC__

#define CRCDI_                0x0150    /* CRC Data In Register */
#define CRCDI_L (*(volatile uint8_t *)0x150)
#define CRCDI (*(volatile uint16_t *)0x150)
#define CRCDI_H (*(volatile uint8_t *)0x151)
#define CRCDI_L (*(volatile uint8_t *)0x150)
#define CRCDI (*(volatile uint16_t *)0x150)
#define CRCDIRB_              0x0152    /* CRC data in reverse byte Register */
#define CRCDIRB_L (*(volatile uint8_t *)0x152)
#define CRCDIRB (*(volatile uint16_t *)0x152)
#define CRCDIRB_H (*(volatile uint8_t *)0x153)
#define CRCDIRB_L (*(volatile uint8_t *)0x152)
#define CRCDIRB (*(volatile uint16_t *)0x152)
#define CRCINIRES_            0x0154    /* CRC Initialisation Register and Result Register */
#define CRCINIRES_L (*(volatile uint8_t *)0x154)
#define CRCINIRES (*(volatile uint16_t *)0x154)
#define CRCINIRES_H (*(volatile uint8_t *)0x155)
#define CRCINIRES_L (*(volatile uint8_t *)0x154)
#define CRCINIRES (*(volatile uint16_t *)0x154)
#define CRCRESR_              0x0156    /* CRC reverse result Register */
#define CRCRESR_L (*(volatile uint8_t *)0x156)
#define CRCRESR (*(volatile uint16_t *)0x156)
#define CRCRESR_H (*(volatile uint8_t *)0x157)
#define CRCRESR_L (*(volatile uint8_t *)0x156)
#define CRCRESR (*(volatile uint16_t *)0x156)

/************************************************************
* DMA_X
************************************************************/
#define __MSP430_HAS_DMAX_3__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_DMAX_3__ 0x0500
#define DMA_BASE __MSP430_BASEADDRESS_DMAX_3__

#define DMACTL0_              0x0500    /* DMA Module Control 0 */
#define DMACTL0_L (*(volatile uint8_t *)0x500)
#define DMACTL0 (*(volatile uint16_t *)0x500)
#define DMACTL0_H (*(volatile uint8_t *)0x501)
#define DMACTL0_L (*(volatile uint8_t *)0x500)
#define DMACTL0 (*(volatile uint16_t *)0x500)
#define DMACTL1_              0x0502    /* DMA Module Control 1 */
#define DMACTL1_L (*(volatile uint8_t *)0x502)
#define DMACTL1 (*(volatile uint16_t *)0x502)
#define DMACTL1_H (*(volatile uint8_t *)0x503)
#define DMACTL1_L (*(volatile uint8_t *)0x502)
#define DMACTL1 (*(volatile uint16_t *)0x502)
#define DMACTL2_              0x0504    /* DMA Module Control 2 */
#define DMACTL2_L (*(volatile uint8_t *)0x504)
#define DMACTL2 (*(volatile uint16_t *)0x504)
#define DMACTL2_H (*(volatile uint8_t *)0x505)
#define DMACTL2_L (*(volatile uint8_t *)0x504)
#define DMACTL2 (*(volatile uint16_t *)0x504)
#define DMACTL3_              0x0506    /* DMA Module Control 3 */
#define DMACTL3_L (*(volatile uint8_t *)0x506)
#define DMACTL3 (*(volatile uint16_t *)0x506)
#define DMACTL3_H (*(volatile uint8_t *)0x507)
#define DMACTL3_L (*(volatile uint8_t *)0x506)
#define DMACTL3 (*(volatile uint16_t *)0x506)
#define DMACTL4_              0x0508    /* DMA Module Control 4 */
#define DMACTL4_L (*(volatile uint8_t *)0x508)
#define DMACTL4 (*(volatile uint16_t *)0x508)
#define DMACTL4_H (*(volatile uint8_t *)0x509)
#define DMACTL4_L (*(volatile uint8_t *)0x508)
#define DMACTL4 (*(volatile uint16_t *)0x508)
#define DMAIV_                0x050E    /* DMA Interrupt Vector Word */
#define DMAIV_L (*(volatile uint8_t *)0x50e)
#define DMAIV (*(volatile uint16_t *)0x50e)
#define DMAIV_H (*(volatile uint8_t *)0x50f)
#define DMAIV_L (*(volatile uint8_t *)0x50e)
#define DMAIV (*(volatile uint16_t *)0x50e)

#define DMA0CTL_              0x0510    /* DMA Channel 0 Control */
#define DMA0CTL_L (*(volatile uint8_t *)0x510)
#define DMA0CTL (*(volatile uint16_t *)0x510)
#define DMA0CTL_H (*(volatile uint8_t *)0x511)
#define DMA0CTL_L (*(volatile uint8_t *)0x510)
#define DMA0CTL (*(volatile uint16_t *)0x510)
#define DMA0SA_               0x0512    /* DMA Channel 0 Source Address */
#define DMA0SA (*(volatile uint32_t *)0x512)
#define DMA0DA_               0x0516    /* DMA Channel 0 Destination Address */
#define DMA0DA (*(volatile uint32_t *)0x516)
#define DMA0SZ_               0x051A    /* DMA Channel 0 Transfer Size */
#define DMA0SZ (*(volatile uint16_t *)0x51a)

#define DMA1CTL_              0x0520    /* DMA Channel 1 Control */
#define DMA1CTL_L (*(volatile uint8_t *)0x520)
#define DMA1CTL (*(volatile uint16_t *)0x520)
#define DMA1CTL_H (*(volatile uint8_t *)0x521)
#define DMA1CTL_L (*(volatile uint8_t *)0x520)
#define DMA1CTL (*(volatile uint16_t *)0x520)
#define DMA1SA_               0x0522    /* DMA Channel 1 Source Address */
#define DMA1SA (*(volatile uint32_t *)0x522)
#define DMA1DA_               0x0526    /* DMA Channel 1 Destination Address */
#define DMA1DA (*(volatile uint32_t *)0x526)
#define DMA1SZ_               0x052A    /* DMA Channel 1 Transfer Size */
#define DMA1SZ (*(volatile uint16_t *)0x52a)

#define DMA2CTL_              0x0530    /* DMA Channel 2 Control */
#define DMA2CTL_L (*(volatile uint8_t *)0x530)
#define DMA2CTL (*(volatile uint16_t *)0x530)
#define DMA2CTL_H (*(volatile uint8_t *)0x531)
#define DMA2CTL_L (*(volatile uint8_t *)0x530)
#define DMA2CTL (*(volatile uint16_t *)0x530)
#define DMA2SA_               0x0532    /* DMA Channel 2 Source Address */
#define DMA2SA (*(volatile uint32_t *)0x532)
#define DMA2DA_               0x0536    /* DMA Channel 2 Destination Address */
#define DMA2DA (*(volatile uint32_t *)0x536)
#define DMA2SZ_               0x053A    /* DMA Channel 2 Transfer Size */
#define DMA2SZ (*(volatile uint16_t *)0x53a)

/* DMACTL0 Control Bits */
#define DMA0TSEL0           (0x0001)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1           (0x0002)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2           (0x0004)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3           (0x0008)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4           (0x0010)    /* DMA channel 0 transfer select bit 4 */
#define DMA1TSEL0           (0x0100)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1           (0x0200)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2           (0x0400)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3           (0x0800)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4           (0x1000)    /* DMA channel 1 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA0TSEL0_L         (0x0001)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1_L         (0x0002)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2_L         (0x0004)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3_L         (0x0008)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4_L         (0x0010)    /* DMA channel 0 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA1TSEL0_H         (0x0001)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1_H         (0x0002)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2_H         (0x0004)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3_H         (0x0008)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4_H         (0x0010)    /* DMA channel 1 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0           (0x0001)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1           (0x0002)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2           (0x0004)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3           (0x0008)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4           (0x0010)    /* DMA channel 2 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0_L         (0x0001)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1_L         (0x0002)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2_L         (0x0004)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3_L         (0x0008)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4_L         (0x0010)    /* DMA channel 2 transfer select bit 4 */

/* DMACTL01 Control Bits */

/* DMACTL4 Control Bits */
#define ENNMI               (0x0001)    /* Enable NMI interruption of DMA */
#define ROUNDROBIN          (0x0002)    /* Round-Robin DMA channel priorities */
#define DMARMWDIS           (0x0004)    /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMACTL4 Control Bits */
#define ENNMI_L             (0x0001)    /* Enable NMI interruption of DMA */
#define ROUNDROBIN_L        (0x0002)    /* Round-Robin DMA channel priorities */
#define DMARMWDIS_L         (0x0004)    /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMACTL4 Control Bits */


/* DMAxCTL Control Bits */
#define DMAREQ              (0x0001)    /* Initiate DMA transfer with DMATSEL */
#define DMAABORT            (0x0002)    /* DMA transfer aborted by NMI */
#define DMAIE               (0x0004)    /* DMA interrupt enable */
#define DMAIFG              (0x0008)    /* DMA interrupt flag */
#define DMAEN               (0x0010)    /* DMA enable */
#define DMALEVEL            (0x0020)    /* DMA level sensitive trigger select */
#define DMASRCBYTE          (0x0040)    /* DMA source byte */
#define DMADSTBYTE          (0x0080)    /* DMA destination byte */
#define DMASRCINCR0         (0x0100)    /* DMA source increment bit 0 */
#define DMASRCINCR1         (0x0200)    /* DMA source increment bit 1 */
#define DMADSTINCR0         (0x0400)    /* DMA destination increment bit 0 */
#define DMADSTINCR1         (0x0800)    /* DMA destination increment bit 1 */
#define DMADT0              (0x1000)    /* DMA transfer mode bit 0 */
#define DMADT1              (0x2000)    /* DMA transfer mode bit 1 */
#define DMADT2              (0x4000)    /* DMA transfer mode bit 2 */

/* DMAxCTL Control Bits */
#define DMAREQ_L            (0x0001)    /* Initiate DMA transfer with DMATSEL */
#define DMAABORT_L          (0x0002)    /* DMA transfer aborted by NMI */
#define DMAIE_L             (0x0004)    /* DMA interrupt enable */
#define DMAIFG_L            (0x0008)    /* DMA interrupt flag */
#define DMAEN_L             (0x0010)    /* DMA enable */
#define DMALEVEL_L          (0x0020)    /* DMA level sensitive trigger select */
#define DMASRCBYTE_L        (0x0040)    /* DMA source byte */
#define DMADSTBYTE_L        (0x0080)    /* DMA destination byte */

/* DMAxCTL Control Bits */
#define DMASRCINCR0_H       (0x0001)    /* DMA source increment bit 0 */
#define DMASRCINCR1_H       (0x0002)    /* DMA source increment bit 1 */
#define DMADSTINCR0_H       (0x0004)    /* DMA destination increment bit 0 */
#define DMADSTINCR1_H       (0x0008)    /* DMA destination increment bit 1 */
#define DMADT0_H            (0x0010)    /* DMA transfer mode bit 0 */
#define DMADT1_H            (0x0020)    /* DMA transfer mode bit 1 */
#define DMADT2_H            (0x0040)    /* DMA transfer mode bit 2 */

#define DMASWDW             (0x0000)  /* DMA transfer: source word to destination word */
#define DMASBDW             (0x0040)  /* DMA transfer: source byte to destination word */
#define DMASWDB             (0x0080)  /* DMA transfer: source word to destination byte */
#define DMASBDB             (0x00C0)  /* DMA transfer: source byte to destination byte */

#define DMASRCINCR_0        (0x0000)  /* DMA source increment 0: source address unchanged */
#define DMASRCINCR_1        (0x0100)  /* DMA source increment 1: source address unchanged */
#define DMASRCINCR_2        (0x0200)  /* DMA source increment 2: source address decremented */
#define DMASRCINCR_3        (0x0300)  /* DMA source increment 3: source address incremented */

#define DMADSTINCR_0        (0x0000)  /* DMA destination increment 0: destination address unchanged */
#define DMADSTINCR_1        (0x0400)  /* DMA destination increment 1: destination address unchanged */
#define DMADSTINCR_2        (0x0800)  /* DMA destination increment 2: destination address decremented */
#define DMADSTINCR_3        (0x0C00)  /* DMA destination increment 3: destination address incremented */

#define DMADT_0             (0x0000)  /* DMA transfer mode 0: Single transfer */
#define DMADT_1             (0x1000)  /* DMA transfer mode 1: Block transfer */
#define DMADT_2             (0x2000)  /* DMA transfer mode 2: Burst-Block transfer */
#define DMADT_3             (0x3000)  /* DMA transfer mode 3: Burst-Block transfer */
#define DMADT_4             (0x4000)  /* DMA transfer mode 4: Repeated Single transfer */
#define DMADT_5             (0x5000)  /* DMA transfer mode 5: Repeated Block transfer */
#define DMADT_6             (0x6000)  /* DMA transfer mode 6: Repeated Burst-Block transfer */
#define DMADT_7             (0x7000)  /* DMA transfer mode 7: Repeated Burst-Block transfer */

/* DMAIV Definitions */
#define DMAIV_NONE           (0x0000)    /* No Interrupt pending */
#define DMAIV_DMA0IFG        (0x0002)    /* DMA0IFG*/
#define DMAIV_DMA1IFG        (0x0004)    /* DMA1IFG*/
#define DMAIV_DMA2IFG        (0x0006)    /* DMA2IFG*/

#define DMA0TSEL_0          (0x0000)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL_1          (0x0001)  /* DMA channel 0 transfer select 1:  */
#define DMA0TSEL_2          (0x0002)  /* DMA channel 0 transfer select 2:  */
#define DMA0TSEL_3          (0x0003)  /* DMA channel 0 transfer select 3:  */
#define DMA0TSEL_4          (0x0004)  /* DMA channel 0 transfer select 4:  */
#define DMA0TSEL_5          (0x0005)  /* DMA channel 0 transfer select 5:  */
#define DMA0TSEL_6          (0x0006)  /* DMA channel 0 transfer select 6:  */
#define DMA0TSEL_7          (0x0007)  /* DMA channel 0 transfer select 7:  */
#define DMA0TSEL_8          (0x0008)  /* DMA channel 0 transfer select 8:  */
#define DMA0TSEL_9          (0x0009)  /* DMA channel 0 transfer select 9:  */
#define DMA0TSEL_10         (0x000A) /* DMA channel 0 transfer select 10: */
#define DMA0TSEL_11         (0x000B) /* DMA channel 0 transfer select 11: */
#define DMA0TSEL_12         (0x000C) /* DMA channel 0 transfer select 12: */
#define DMA0TSEL_13         (0x000D) /* DMA channel 0 transfer select 13: */
#define DMA0TSEL_14         (0x000E) /* DMA channel 0 transfer select 14: */
#define DMA0TSEL_15         (0x000F) /* DMA channel 0 transfer select 15: */
#define DMA0TSEL_16         (0x0010) /* DMA channel 0 transfer select 16: */
#define DMA0TSEL_17         (0x0011) /* DMA channel 0 transfer select 17: */
#define DMA0TSEL_18         (0x0012) /* DMA channel 0 transfer select 18: */
#define DMA0TSEL_19         (0x0013) /* DMA channel 0 transfer select 19: */
#define DMA0TSEL_20         (0x0014) /* DMA channel 0 transfer select 20: */
#define DMA0TSEL_21         (0x0015) /* DMA channel 0 transfer select 21: */
#define DMA0TSEL_22         (0x0016) /* DMA channel 0 transfer select 22: */
#define DMA0TSEL_23         (0x0017) /* DMA channel 0 transfer select 23: */
#define DMA0TSEL_24         (0x0018) /* DMA channel 0 transfer select 24: */
#define DMA0TSEL_25         (0x0019) /* DMA channel 0 transfer select 25: */
#define DMA0TSEL_26         (0x001A) /* DMA channel 0 transfer select 26: */
#define DMA0TSEL_27         (0x001B) /* DMA channel 0 transfer select 27: */
#define DMA0TSEL_28         (0x001C) /* DMA channel 0 transfer select 28: */
#define DMA0TSEL_29         (0x001D) /* DMA channel 0 transfer select 29: */
#define DMA0TSEL_30         (0x001E) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL_31         (0x001F) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL_0          (0x0000)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL_1          (0x0100)  /* DMA channel 1 transfer select 1:  */
#define DMA1TSEL_2          (0x0200)  /* DMA channel 1 transfer select 2:  */
#define DMA1TSEL_3          (0x0300)  /* DMA channel 1 transfer select 3:  */
#define DMA1TSEL_4          (0x0400)  /* DMA channel 1 transfer select 4:  */
#define DMA1TSEL_5          (0x0500)  /* DMA channel 1 transfer select 5:  */
#define DMA1TSEL_6          (0x0600)  /* DMA channel 1 transfer select 6:  */
#define DMA1TSEL_7          (0x0700)  /* DMA channel 1 transfer select 7:  */
#define DMA1TSEL_8          (0x0800)  /* DMA channel 1 transfer select 8:  */
#define DMA1TSEL_9          (0x0900)  /* DMA channel 1 transfer select 9:  */
#define DMA1TSEL_10         (0x0A00) /* DMA channel 1 transfer select 10: */
#define DMA1TSEL_11         (0x0B00) /* DMA channel 1 transfer select 11: */
#define DMA1TSEL_12         (0x0C00) /* DMA channel 1 transfer select 12: */
#define DMA1TSEL_13         (0x0D00) /* DMA channel 1 transfer select 13: */
#define DMA1TSEL_14         (0x0E00) /* DMA channel 1 transfer select 14: */
#define DMA1TSEL_15         (0x0F00) /* DMA channel 1 transfer select 15: */
#define DMA1TSEL_16         (0x1000) /* DMA channel 1 transfer select 16: */
#define DMA1TSEL_17         (0x1100) /* DMA channel 1 transfer select 17: */
#define DMA1TSEL_18         (0x1200) /* DMA channel 1 transfer select 18: */
#define DMA1TSEL_19         (0x1300) /* DMA channel 1 transfer select 19: */
#define DMA1TSEL_20         (0x1400) /* DMA channel 1 transfer select 20: */
#define DMA1TSEL_21         (0x1500) /* DMA channel 1 transfer select 21: */
#define DMA1TSEL_22         (0x1600) /* DMA channel 1 transfer select 22: */
#define DMA1TSEL_23         (0x1700) /* DMA channel 1 transfer select 23: */
#define DMA1TSEL_24         (0x1800) /* DMA channel 1 transfer select 24: */
#define DMA1TSEL_25         (0x1900) /* DMA channel 1 transfer select 25: */
#define DMA1TSEL_26         (0x1A00) /* DMA channel 1 transfer select 26: */
#define DMA1TSEL_27         (0x1B00) /* DMA channel 1 transfer select 27: */
#define DMA1TSEL_28         (0x1C00) /* DMA channel 1 transfer select 28: */
#define DMA1TSEL_29         (0x1D00) /* DMA channel 1 transfer select 29: */
#define DMA1TSEL_30         (0x1E00) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL_31         (0x1F00) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL_0          (0x0000)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL_1          (0x0001)  /* DMA channel 2 transfer select 1:  */
#define DMA2TSEL_2          (0x0002)  /* DMA channel 2 transfer select 2:  */
#define DMA2TSEL_3          (0x0003)  /* DMA channel 2 transfer select 3:  */
#define DMA2TSEL_4          (0x0004)  /* DMA channel 2 transfer select 4:  */
#define DMA2TSEL_5          (0x0005)  /* DMA channel 2 transfer select 5:  */
#define DMA2TSEL_6          (0x0006)  /* DMA channel 2 transfer select 6:  */
#define DMA2TSEL_7          (0x0007)  /* DMA channel 2 transfer select 7:  */
#define DMA2TSEL_8          (0x0008)  /* DMA channel 2 transfer select 8:  */
#define DMA2TSEL_9          (0x0009)  /* DMA channel 2 transfer select 9:  */
#define DMA2TSEL_10         (0x000A) /* DMA channel 2 transfer select 10: */
#define DMA2TSEL_11         (0x000B) /* DMA channel 2 transfer select 11: */
#define DMA2TSEL_12         (0x000C) /* DMA channel 2 transfer select 12: */
#define DMA2TSEL_13         (0x000D) /* DMA channel 2 transfer select 13: */
#define DMA2TSEL_14         (0x000E) /* DMA channel 2 transfer select 14: */
#define DMA2TSEL_15         (0x000F) /* DMA channel 2 transfer select 15: */
#define DMA2TSEL_16         (0x0010) /* DMA channel 2 transfer select 16: */
#define DMA2TSEL_17         (0x0011) /* DMA channel 2 transfer select 17: */
#define DMA2TSEL_18         (0x0012) /* DMA channel 2 transfer select 18: */
#define DMA2TSEL_19         (0x0013) /* DMA channel 2 transfer select 19: */
#define DMA2TSEL_20         (0x0014) /* DMA channel 2 transfer select 20: */
#define DMA2TSEL_21         (0x0015) /* DMA channel 2 transfer select 21: */
#define DMA2TSEL_22         (0x0016) /* DMA channel 2 transfer select 22: */
#define DMA2TSEL_23         (0x0017) /* DMA channel 2 transfer select 23: */
#define DMA2TSEL_24         (0x0018) /* DMA channel 2 transfer select 24: */
#define DMA2TSEL_25         (0x0019) /* DMA channel 2 transfer select 25: */
#define DMA2TSEL_26         (0x001A) /* DMA channel 2 transfer select 26: */
#define DMA2TSEL_27         (0x001B) /* DMA channel 2 transfer select 27: */
#define DMA2TSEL_28         (0x001C) /* DMA channel 2 transfer select 28: */
#define DMA2TSEL_29         (0x001D) /* DMA channel 2 transfer select 29: */
#define DMA2TSEL_30         (0x001E) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL_31         (0x001F) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

#define DMA0TSEL__DMAREQ     (0x0000)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL__TA0CCR0    (0x0001)  /* DMA channel 0 transfer select 1:  TA0CCR0 */
#define DMA0TSEL__TA0CCR2    (0x0002)  /* DMA channel 0 transfer select 2:  TA0CCR2 */
#define DMA0TSEL__TA1CCR0    (0x0003)  /* DMA channel 0 transfer select 3:  TA1CCR0 */
#define DMA0TSEL__TA1CCR2    (0x0004)  /* DMA channel 0 transfer select 4:  TA1CCR2 */
#define DMA0TSEL__RES5       (0x0005)  /* DMA channel 0 transfer select 5:  RES5 */
#define DMA0TSEL__RES6       (0x0006)  /* DMA channel 0 transfer select 6:  RES6 */
#define DMA0TSEL__TB0CCR0    (0x0007)  /* DMA channel 0 transfer select 7:  TB0CCR0 */
#define DMA0TSEL__TB0CCR2    (0x0008)  /* DMA channel 0 transfer select 8:  TB0CCR2 */
#define DMA0TSEL__TB1CCR0    (0x0009)  /* DMA channel 0 transfer select 9:  TB1CCR0 */
#define DMA0TSEL__TB1CCR2    (0x000A) /* DMA channel 0 transfer select 10: TB1CCR2 */
#define DMA0TSEL__TB2CCR0    (0x000B) /* DMA channel 0 transfer select 11: TB2CCR0 */
#define DMA0TSEL__TB2CCR2    (0x000C) /* DMA channel 0 transfer select 12: TB2CCR2 */
#define DMA0TSEL__RES13      (0x000D) /* DMA channel 0 transfer select 13: RES13 */
#define DMA0TSEL__UCA0RXIFG  (0x000E) /* DMA channel 0 transfer select 14: UCA0RXIFG */
#define DMA0TSEL__UCA0TXIFG  (0x000F) /* DMA channel 0 transfer select 15: UCA0TXIFG */
#define DMA0TSEL__UCA1RXIFG  (0x0010) /* DMA channel 0 transfer select 16: UCA1RXIFG */
#define DMA0TSEL__UCA1TXIFG  (0x0011) /* DMA channel 0 transfer select 17: UCA1TXIFG */
#define DMA0TSEL__UCB0RXIFG0 (0x0012) /* DMA channel 0 transfer select 18: UCB0RXIFG0 */
#define DMA0TSEL__UCB0TXIFG0 (0x0013) /* DMA channel 0 transfer select 19: UCB0TXIFG0 */
#define DMA0TSEL__UCB0RXIFG1 (0x0014) /* DMA channel 0 transfer select 20: UCB0RXIFG1 */
#define DMA0TSEL__UCB0TXIFG1 (0x0015) /* DMA channel 0 transfer select 21: UCB0TXIFG1 */
#define DMA0TSEL__UCB0RXIFG2 (0x0016) /* DMA channel 0 transfer select 22: UCB0RXIFG2 */
#define DMA0TSEL__UCB0TXIFG2 (0x0017) /* DMA channel 0 transfer select 23: UCB0TXIFG2 */
#define DMA0TSEL__UCB0RXIFG3 (0x0018) /* DMA channel 0 transfer select 24: UCB0RXIFG3 */
#define DMA0TSEL__UCB0TXIFG3 (0x0019) /* DMA channel 0 transfer select 25: UCB0TXIFG3 */
#define DMA0TSEL__ADC10IFG   (0x001A) /* DMA channel 0 transfer select 26: ADC10IFG */
#define DMA0TSEL__RES27      (0x001B) /* DMA channel 0 transfer select 27: RES27 */
#define DMA0TSEL__RES28      (0x001C) /* DMA channel 0 transfer select 28: RES28 */
#define DMA0TSEL__MPY        (0x001D) /* DMA channel 0 transfer select 29: MPY */
#define DMA0TSEL__DMA2IFG    (0x001E) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL__DMAE0      (0x001F) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL__DMAREQ     (0x0000)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL__TA0CCR0    (0x0100)  /* DMA channel 1 transfer select 1:  TA0CCR0 */
#define DMA1TSEL__TA0CCR2    (0x0200)  /* DMA channel 1 transfer select 2:  TA0CCR2 */
#define DMA1TSEL__TA1CCR0    (0x0300)  /* DMA channel 1 transfer select 3:  TA1CCR0 */
#define DMA1TSEL__TA1CCR2    (0x0400)  /* DMA channel 1 transfer select 4:  TA1CCR2 */
#define DMA1TSEL__RES5       (0x0500)  /* DMA channel 1 transfer select 5:  RES5 */
#define DMA1TSEL__RES6       (0x0600)  /* DMA channel 1 transfer select 6:  RES6 */
#define DMA1TSEL__TB0CCR0    (0x0700)  /* DMA channel 1 transfer select 7:  TB0CCR0 */
#define DMA1TSEL__TB0CCR2    (0x0800)  /* DMA channel 1 transfer select 8:  TB0CCR2 */
#define DMA1TSEL__TB1CCR0    (0x0900)  /* DMA channel 1 transfer select 9:  TB1CCR0 */
#define DMA1TSEL__TB1CCR2    (0x0A00) /* DMA channel 1 transfer select 10: TB1CCR2 */
#define DMA1TSEL__TB2CCR0    (0x0B00) /* DMA channel 1 transfer select 11: TB2CCR0 */
#define DMA1TSEL__TB2CCR2    (0x0C00) /* DMA channel 1 transfer select 12: TB2CCR2 */
#define DMA1TSEL__RES13      (0x0D00) /* DMA channel 1 transfer select 13: RES13 */
#define DMA1TSEL__UCA0RXIFG  (0x0E00) /* DMA channel 1 transfer select 14: UCA0RXIFG */
#define DMA1TSEL__UCA0TXIFG  (0x0F00) /* DMA channel 1 transfer select 15: UCA0TXIFG */
#define DMA1TSEL__UCA1RXIFG  (0x1000) /* DMA channel 1 transfer select 16: UCA1RXIFG */
#define DMA1TSEL__UCA1TXIFG  (0x1100) /* DMA channel 1 transfer select 17: UCA1TXIFG */
#define DMA1TSEL__UCB0RXIFG0 (0x1200) /* DMA channel 1 transfer select 18: UCB0RXIFG0 */
#define DMA1TSEL__UCB0TXIFG0 (0x1300) /* DMA channel 1 transfer select 19: UCB0TXIFG0 */
#define DMA1TSEL__UCB0RXIFG1 (0x1400) /* DMA channel 1 transfer select 20: UCB0RXIFG1 */
#define DMA1TSEL__UCB0TXIFG1 (0x1500) /* DMA channel 1 transfer select 21: UCB0TXIFG1 */
#define DMA1TSEL__UCB0RXIFG2 (0x1600) /* DMA channel 1 transfer select 22: UCB0RXIFG2 */
#define DMA1TSEL__UCB0TXIFG2 (0x1700) /* DMA channel 1 transfer select 23: UCB0TXIFG2 */
#define DMA1TSEL__UCB0RXIFG3 (0x1800) /* DMA channel 1 transfer select 24: UCB0RXIFG3 */
#define DMA1TSEL__UCB0TXIFG3 (0x1900) /* DMA channel 1 transfer select 25: UCB0TXIFG3 */
#define DMA1TSEL__ADC10IFG   (0x1A00) /* DMA channel 1 transfer select 26: ADC10IFG */
#define DMA1TSEL__RES27      (0x1B00) /* DMA channel 1 transfer select 27: RES27 */
#define DMA1TSEL__RES28      (0x1C00) /* DMA channel 1 transfer select 28: RES28 */
#define DMA1TSEL__MPY        (0x1D00) /* DMA channel 1 transfer select 29: MPY */
#define DMA1TSEL__DMA0IFG    (0x1E00) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL__DMAE0      (0x1F00) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL__DMAREQ     (0x0000)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL__TA0CCR0    (0x0001)  /* DMA channel 2 transfer select 1:  TA0CCR0 */
#define DMA2TSEL__TA0CCR2    (0x0002)  /* DMA channel 2 transfer select 2:  TA0CCR2 */
#define DMA2TSEL__TA1CCR0    (0x0003)  /* DMA channel 2 transfer select 3:  TA1CCR0 */
#define DMA2TSEL__TA1CCR2    (0x0004)  /* DMA channel 2 transfer select 4:  TA1CCR2 */
#define DMA2TSEL__RES5       (0x0005)  /* DMA channel 2 transfer select 5:  RES5 */
#define DMA2TSEL__RES6       (0x0006)  /* DMA channel 2 transfer select 6:  RES6 */
#define DMA2TSEL__TB0CCR0    (0x0007)  /* DMA channel 2 transfer select 7:  TB0CCR0 */
#define DMA2TSEL__TB0CCR2    (0x0008)  /* DMA channel 2 transfer select 8:  TB0CCR2 */
#define DMA2TSEL__TB1CCR0    (0x0009)  /* DMA channel 2 transfer select 9:  TB1CCR0 */
#define DMA2TSEL__TB1CCR2    (0x000A) /* DMA channel 2 transfer select 10: TB1CCR2 */
#define DMA2TSEL__TB2CCR0    (0x000B) /* DMA channel 2 transfer select 11: TB2CCR0 */
#define DMA2TSEL__TB2CCR2    (0x000C) /* DMA channel 2 transfer select 12: TB2CCR2 */
#define DMA2TSEL__RES13      (0x000D) /* DMA channel 2 transfer select 13: RES13 */
#define DMA2TSEL__UCA0RXIFG  (0x000E) /* DMA channel 2 transfer select 14: UCA0RXIFG */
#define DMA2TSEL__UCA0TXIFG  (0x000F) /* DMA channel 2 transfer select 15: UCA0TXIFG */
#define DMA2TSEL__UCA1RXIFG  (0x0010) /* DMA channel 2 transfer select 16: UCA1RXIFG */
#define DMA2TSEL__UCA1TXIFG  (0x0011) /* DMA channel 2 transfer select 17: UCA1TXIFG */
#define DMA2TSEL__UCB0RXIFG0 (0x0012) /* DMA channel 2 transfer select 18: UCB0RXIFG0 */
#define DMA2TSEL__UCB0TXIFG0 (0x0013) /* DMA channel 2 transfer select 19: UCB0TXIFG0 */
#define DMA2TSEL__UCB0RXIFG1 (0x0014) /* DMA channel 2 transfer select 20: UCB0RXIFG1 */
#define DMA2TSEL__UCB0TXIFG1 (0x0015) /* DMA channel 2 transfer select 21: UCB0TXIFG1 */
#define DMA2TSEL__UCB0RXIFG2 (0x0016) /* DMA channel 2 transfer select 22: UCB0RXIFG2 */
#define DMA2TSEL__UCB0TXIFG2 (0x0017) /* DMA channel 2 transfer select 23: UCB0TXIFG2 */
#define DMA2TSEL__UCB0RXIFG3 (0x0018) /* DMA channel 2 transfer select 24: UCB0RXIFG3 */
#define DMA2TSEL__UCB0TXIFG3 (0x0019) /* DMA channel 2 transfer select 25: UCB0TXIFG3 */
#define DMA2TSEL__ADC10IFG   (0x001A) /* DMA channel 2 transfer select 26: ADC10IFG */
#define DMA2TSEL__RES27      (0x001B) /* DMA channel 2 transfer select 27: RES27 */
#define DMA2TSEL__RES28      (0x001C) /* DMA channel 2 transfer select 28: RES28 */
#define DMA2TSEL__MPY        (0x001D) /* DMA channel 2 transfer select 29: MPY */
#define DMA2TSEL__DMA1IFG    (0x001E) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL__DMAE0      (0x001F) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

/*************************************************************
* FRAM Memory
*************************************************************/
#define __MSP430_HAS_FRAM_FR5XX__     /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_FRAM_FR5XX__ 0x0140
#define FRAM_BASE __MSP430_BASEADDRESS_FRAM_FR5XX__

#define FRCTL0_               0x0140    /* FRAM Controller Control 0 */
#define FRCTL0_L (*(volatile uint8_t *)0x140)
#define FRCTL0 (*(volatile uint16_t *)0x140)
#define FRCTL0_H (*(volatile uint8_t *)0x141)
#define FRCTL0_L (*(volatile uint8_t *)0x140)
#define FRCTL0 (*(volatile uint16_t *)0x140)
#define GCCTL0_               0x0144    /* General Control 0 */
#define GCCTL0_L (*(volatile uint8_t *)0x144)
#define GCCTL0 (*(volatile uint16_t *)0x144)
#define GCCTL0_H (*(volatile uint8_t *)0x145)
#define GCCTL0_L (*(volatile uint8_t *)0x144)
#define GCCTL0 (*(volatile uint16_t *)0x144)
#define GCCTL1_               0x0146    /* General Control 1 */
#define GCCTL1_L (*(volatile uint8_t *)0x146)
#define GCCTL1 (*(volatile uint16_t *)0x146)
#define GCCTL1_H (*(volatile uint8_t *)0x147)
#define GCCTL1_L (*(volatile uint8_t *)0x146)
#define GCCTL1 (*(volatile uint16_t *)0x146)

#define FRPW                (0x9600)  /* FRAM password returned by read */
#define FWPW                (0xA500)  /* FRAM password for write */
#define FXPW                (0x3300)  /* for use with XOR instruction */

/* FRCTL0 Control Bits */
#define NPRECHG0            (0x0001)  /* FRAM Wait state Generator Precharge Time control Bit: 0 */
#define NPRECHG1            (0x0002)  /* FRAM Wait state Generator Precharge Time control Bit: 1 */
#define NPRECHG2            (0x0004)  /* FRAM Wait state Generator Precharge Time control Bit: 2 */
#define NAUTO               (0x0008)  /* FRAM Disables the wait state generator */
#define NACCESS0            (0x0010)  /* FRAM Wait state Generator Access Time control Bit: 0 */
#define NACCESS1            (0x0020)  /* FRAM Wait state Generator Access Time control Bit: 1 */
#define NACCESS2            (0x0040)  /* FRAM Wait state Generator Access Time control Bit: 2 */
//#define RESERVED            (0x0080)  /* RESERVED */

/* FRCTL0 Control Bits */
#define NPRECHG0_L          (0x0001)  /* FRAM Wait state Generator Precharge Time control Bit: 0 */
#define NPRECHG1_L          (0x0002)  /* FRAM Wait state Generator Precharge Time control Bit: 1 */
#define NPRECHG2_L          (0x0004)  /* FRAM Wait state Generator Precharge Time control Bit: 2 */
#define NAUTO_L             (0x0008)  /* FRAM Disables the wait state generator */
#define NACCESS0_L          (0x0010)  /* FRAM Wait state Generator Access Time control Bit: 0 */
#define NACCESS1_L          (0x0020)  /* FRAM Wait state Generator Access Time control Bit: 1 */
#define NACCESS2_L          (0x0040)  /* FRAM Wait state Generator Access Time control Bit: 2 */
//#define RESERVED            (0x0080)  /* RESERVED */

/* FRCTL0 Control Bits */
//#define RESERVED            (0x0080)  /* RESERVED */

#define NPRECHG_0           (0x0000)  /* FRAM Wait state Generator Precharge Time control: 0 */
#define NPRECHG_1           (0x0001)  /* FRAM Wait state Generator Precharge Time control: 1 */
#define NPRECHG_2           (0x0002)  /* FRAM Wait state Generator Precharge Time control: 2 */
#define NPRECHG_3           (0x0003)  /* FRAM Wait state Generator Precharge Time control: 3 */
#define NPRECHG_4           (0x0004)  /* FRAM Wait state Generator Precharge Time control: 4 */
#define NPRECHG_5           (0x0005)  /* FRAM Wait state Generator Precharge Time control: 5 */
#define NPRECHG_6           (0x0006)  /* FRAM Wait state Generator Precharge Time control: 6 */
#define NPRECHG_7           (0x0007)  /* FRAM Wait state Generator Precharge Time control: 7 */

#define NACCESS_0           (0x0000)  /* FRAM Wait state Generator Access Time control: 0 */
#define NACCESS_1           (0x0010)  /* FRAM Wait state Generator Access Time control: 1 */
#define NACCESS_2           (0x0020)  /* FRAM Wait state Generator Access Time control: 2 */
#define NACCESS_3           (0x0030)  /* FRAM Wait state Generator Access Time control: 3 */
#define NACCESS_4           (0x0040)  /* FRAM Wait state Generator Access Time control: 4 */
#define NACCESS_5           (0x0050)  /* FRAM Wait state Generator Access Time control: 5 */
#define NACCESS_6           (0x0060)  /* FRAM Wait state Generator Access Time control: 6 */
#define NACCESS_7           (0x0070)  /* FRAM Wait state Generator Access Time control: 7 */


/* GCCTL0 Control Bits */
#define BUSY                (0x0001)  /* FRAM is currently busy programming */
//#define RESERVED            (0x0002)  /* RESERVED */
//#define RESERVED            (0x0004)  /* RESERVED */
#define ACCTEIE             (0x0008)  /* Enable NMI event if Access time error occurs */
#define ACCVIE              (0x0010)  /* Enable NMI event if Access Violation occurs */
#define CBDIE               (0x0020)  /* Enable NMI event if correctable bit error detected */
#define UBDIE               (0x0040)  /* Enable NMI event if uncorrectable bit error detected */
#define UBDRSTEN            (0x0080)  /* Enable Power Up Clear on uncorrectable bit error */

/* GCCTL0 Control Bits */
#define BUSY_L              (0x0001)  /* FRAM is currently busy programming */
//#define RESERVED            (0x0002)  /* RESERVED */
//#define RESERVED            (0x0004)  /* RESERVED */
#define ACCTEIE_L           (0x0008)  /* Enable NMI event if Access time error occurs */
#define ACCVIE_L            (0x0010)  /* Enable NMI event if Access Violation occurs */
#define CBDIE_L             (0x0020)  /* Enable NMI event if correctable bit error detected */
#define UBDIE_L             (0x0040)  /* Enable NMI event if uncorrectable bit error detected */
#define UBDRSTEN_L          (0x0080)  /* Enable Power Up Clear on uncorrectable bit error */

/* GCCTL0 Control Bits */
//#define RESERVED            (0x0002)  /* RESERVED */
//#define RESERVED            (0x0004)  /* RESERVED */

/* GCCTL1 Control Bits */
#define ACCVIFG             (0x0001)  /* Access Violation Interrupt Flag */
#define CBDIFG              (0x0002)  /* FRAM correctable bit error flag */
#define UBDIFG              (0x0004)  /* FRAM uncorrectable bit error flag */
#define ACCTEIFG            (0x0008)  /* Access time error flag */

/* GCCTL1 Control Bits */
#define ACCVIFG_L           (0x0001)  /* Access Violation Interrupt Flag */
#define CBDIFG_L            (0x0002)  /* FRAM correctable bit error flag */
#define UBDIFG_L            (0x0004)  /* FRAM uncorrectable bit error flag */
#define ACCTEIFG_L          (0x0008)  /* Access time error flag */

/* GCCTL1 Control Bits */

/* Legacy Definitions */
#define SBDIEN              (0x0020)  /* Enable NMI event if single bit error detected */
#define DBDIEN              (0x0040)  /* Enable NMI event if double bit error detected */
#define DBDRSTEN            (0x0080)  /* Enable Power Up Clear on double bit error */
#define SBDIFG              (0x0002)  /* FRAM single bit error flag */
#define DBDIFG              (0x0004)  /* FRAM double bit error flag */

/************************************************************
* Memory Protection Unit
************************************************************/
#define __MSP430_HAS_MPU__             /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_MPU__ 0x05A0
#define MPU_BASE __MSP430_BASEADDRESS_MPU__

#define MPUCTL0_              0x05A0    /* MPU Control Register 0 */
#define MPUCTL0_L (*(volatile uint8_t *)0x5a0)
#define MPUCTL0 (*(volatile uint16_t *)0x5a0)
#define MPUCTL0_H (*(volatile uint8_t *)0x5a1)
#define MPUCTL0_L (*(volatile uint8_t *)0x5a0)
#define MPUCTL0 (*(volatile uint16_t *)0x5a0)
#define MPUCTL1_              0x05A2    /* MPU Control Register 1 */
#define MPUCTL1_L (*(volatile uint8_t *)0x5a2)
#define MPUCTL1 (*(volatile uint16_t *)0x5a2)
#define MPUCTL1_H (*(volatile uint8_t *)0x5a3)
#define MPUCTL1_L (*(volatile uint8_t *)0x5a2)
#define MPUCTL1 (*(volatile uint16_t *)0x5a2)
#define MPUSEG_               0x05A4    /* MPU Segmentation Register */
#define MPUSEG_L (*(volatile uint8_t *)0x5a4)
#define MPUSEG (*(volatile uint16_t *)0x5a4)
#define MPUSEG_H (*(volatile uint8_t *)0x5a5)
#define MPUSEG_L (*(volatile uint8_t *)0x5a4)
#define MPUSEG (*(volatile uint16_t *)0x5a4)
#define MPUSAM_               0x05A6    /* MPU Access Management Register */
#define MPUSAM_L (*(volatile uint8_t *)0x5a6)
#define MPUSAM (*(volatile uint16_t *)0x5a6)
#define MPUSAM_H (*(volatile uint8_t *)0x5a7)
#define MPUSAM_L (*(volatile uint8_t *)0x5a6)
#define MPUSAM (*(volatile uint16_t *)0x5a6)


/* MPUCTL0 Control Bits */
#define MPUENA               (0x0001)  /* MPU Enable */
#define MPUSEGIE             (0x0010)  /* MPU Enable NMI on Segment violation */

/* MPUCTL0 Control Bits */
#define MPUENA_L            (0x0001)  /* MPU Enable */
#define MPUSEGIE_L          (0x0010)  /* MPU Enable NMI on Segment violation */

/* MPUCTL0 Control Bits */
#define MPUPW                (0xA500)  /* MPU Access Password */
#define MPUPW_H              (0xA5)    /* MPU Access Password */

/* MPUCTL1 Control Bits */
#define MPUSEG1IFG           (0x0001)  /* MPU Main Memory Segment 1 violation interupt flag */
#define MPUSEG2IFG           (0x0002)  /* MPU Main Memory Segment 2 violation interupt flag */
#define MPUSEG3IFG           (0x0004)  /* MPU Main Memory Segment 3 violation interupt flag */
#define MPUSEGIIFG           (0x0008)  /* MPU Info Memory Segment violation interupt flag */

/* MPUCTL1 Control Bits */
#define MPUSEG1IFG_L        (0x0001)  /* MPU Main Memory Segment 1 violation interupt flag */
#define MPUSEG2IFG_L        (0x0002)  /* MPU Main Memory Segment 2 violation interupt flag */
#define MPUSEG3IFG_L        (0x0004)  /* MPU Main Memory Segment 3 violation interupt flag */
#define MPUSEGIIFG_L        (0x0008)  /* MPU Info Memory Segment violation interupt flag */

/* MPUCTL1 Control Bits */

/* MPUSEG Control Bits */
#define MPUSB10              (0x0001)  /* MPU Segment Border 1 Bit: 0 */
#define MPUSB11              (0x0002)  /* MPU Segment Border 1 Bit: 1 */
#define MPUSB12              (0x0004)  /* MPU Segment Border 1 Bit: 2 */
#define MPUSB13              (0x0008)  /* MPU Segment Border 1 Bit: 3 */
#define MPUSB14              (0x0010)  /* MPU Segment Border 1 Bit: 4 */
#define MPUSB20              (0x0100)  /* MPU Segment Border 2 Bit: 0 */
#define MPUSB21              (0x0200)  /* MPU Segment Border 2 Bit: 1 */
#define MPUSB22              (0x0400)  /* MPU Segment Border 2 Bit: 2 */
#define MPUSB23              (0x0800)  /* MPU Segment Border 2 Bit: 3 */
#define MPUSB24              (0x1000)  /* MPU Segment Border 2 Bit: 4 */

/* MPUSEG Control Bits */
#define MPUSB10_L           (0x0001)  /* MPU Segment Border 1 Bit: 0 */
#define MPUSB11_L           (0x0002)  /* MPU Segment Border 1 Bit: 1 */
#define MPUSB12_L           (0x0004)  /* MPU Segment Border 1 Bit: 2 */
#define MPUSB13_L           (0x0008)  /* MPU Segment Border 1 Bit: 3 */
#define MPUSB14_L           (0x0010)  /* MPU Segment Border 1 Bit: 4 */

/* MPUSEG Control Bits */
#define MPUSB20_H           (0x0001)  /* MPU Segment Border 2 Bit: 0 */
#define MPUSB21_H           (0x0002)  /* MPU Segment Border 2 Bit: 1 */
#define MPUSB22_H           (0x0004)  /* MPU Segment Border 2 Bit: 2 */
#define MPUSB23_H           (0x0008)  /* MPU Segment Border 2 Bit: 3 */
#define MPUSB24_H           (0x0010)  /* MPU Segment Border 2 Bit: 4 */

/* MPUSAM Control Bits */
#define MPUSEG1RE            (0x0001)  /* MPU Main memory Segment 1 Read enable */
#define MPUSEG1WE            (0x0002)  /* MPU Main memory Segment 1 Write enable */
#define MPUSEG1XE            (0x0004)  /* MPU Main memory Segment 1 Execute enable */
#define MPUSEG1VS            (0x0008)  /* MPU Main memory Segment 1 Violation select */
#define MPUSEG2RE            (0x0010)  /* MPU Main memory Segment 2 Read enable */
#define MPUSEG2WE            (0x0020)  /* MPU Main memory Segment 2 Write enable */
#define MPUSEG2XE            (0x0040)  /* MPU Main memory Segment 2 Execute enable */
#define MPUSEG2VS            (0x0080)  /* MPU Main memory Segment 2 Violation select */
#define MPUSEG3RE            (0x0100)  /* MPU Main memory Segment 3 Read enable */
#define MPUSEG3WE            (0x0200)  /* MPU Main memory Segment 3 Write enable */
#define MPUSEG3XE            (0x0400)  /* MPU Main memory Segment 3 Execute enable */
#define MPUSEG3VS            (0x0800)  /* MPU Main memory Segment 3 Violation select */
#define MPUSEGIRE            (0x1000)  /* MPU Info memory Segment Read enable */
#define MPUSEGIWE            (0x2000)  /* MPU Info memory Segment Write enable */
#define MPUSEGIXE            (0x4000)  /* MPU Info memory Segment Execute enable */
#define MPUSEGIVS            (0x8000)  /* MPU Info memory Segment Violation select */

/* MPUSAM Control Bits */
#define MPUSEG1RE_L         (0x0001)  /* MPU Main memory Segment 1 Read enable */
#define MPUSEG1WE_L         (0x0002)  /* MPU Main memory Segment 1 Write enable */
#define MPUSEG1XE_L         (0x0004)  /* MPU Main memory Segment 1 Execute enable */
#define MPUSEG1VS_L         (0x0008)  /* MPU Main memory Segment 1 Violation select */
#define MPUSEG2RE_L         (0x0010)  /* MPU Main memory Segment 2 Read enable */
#define MPUSEG2WE_L         (0x0020)  /* MPU Main memory Segment 2 Write enable */
#define MPUSEG2XE_L         (0x0040)  /* MPU Main memory Segment 2 Execute enable */
#define MPUSEG2VS_L         (0x0080)  /* MPU Main memory Segment 2 Violation select */

/* MPUSAM Control Bits */
#define MPUSEG3RE_H         (0x0001)  /* MPU Main memory Segment 3 Read enable */
#define MPUSEG3WE_H         (0x0002)  /* MPU Main memory Segment 3 Write enable */
#define MPUSEG3XE_H         (0x0004)  /* MPU Main memory Segment 3 Execute enable */
#define MPUSEG3VS_H         (0x0008)  /* MPU Main memory Segment 3 Violation select */
#define MPUSEGIRE_H         (0x0010)  /* MPU Info memory Segment Read enable */
#define MPUSEGIWE_H         (0x0020)  /* MPU Info memory Segment Write enable */
#define MPUSEGIXE_H         (0x0040)  /* MPU Info memory Segment Execute enable */
#define MPUSEGIVS_H         (0x0080)  /* MPU Info memory Segment Violation select */

/************************************************************
* HARDWARE MULTIPLIER 32Bit
************************************************************/
#define __MSP430_HAS_MPY32__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_MPY32__ 0x04C0
#define MPY32_BASE __MSP430_BASEADDRESS_MPY32__

#define MPY_                  0x04C0    /* Multiply Unsigned/Operand 1 */
#define MPY_L (*(volatile uint8_t *)0x4c0)
#define MPY (*(volatile uint16_t *)0x4c0)
#define MPY_H (*(volatile uint8_t *)0x4c1)
#define MPY_L (*(volatile uint8_t *)0x4c0)
#define MPY (*(volatile uint16_t *)0x4c0)
#define MPYS_                 0x04C2    /* Multiply Signed/Operand 1 */
#define MPYS_L (*(volatile uint8_t *)0x4c2)
#define MPYS (*(volatile uint16_t *)0x4c2)
#define MPYS_H (*(volatile uint8_t *)0x4c3)
#define MPYS_L (*(volatile uint8_t *)0x4c2)
#define MPYS (*(volatile uint16_t *)0x4c2)
#define MAC_                  0x04C4    /* Multiply Unsigned and Accumulate/Operand 1 */
#define MAC_L (*(volatile uint8_t *)0x4c4)
#define MAC (*(volatile uint16_t *)0x4c4)
#define MAC_H (*(volatile uint8_t *)0x4c5)
#define MAC_L (*(volatile uint8_t *)0x4c4)
#define MAC (*(volatile uint16_t *)0x4c4)
#define MACS_                 0x04C6    /* Multiply Signed and Accumulate/Operand 1 */
#define MACS_L (*(volatile uint8_t *)0x4c6)
#define MACS (*(volatile uint16_t *)0x4c6)
#define MACS_H (*(volatile uint8_t *)0x4c7)
#define MACS_L (*(volatile uint8_t *)0x4c6)
#define MACS (*(volatile uint16_t *)0x4c6)
#define OP2_                  0x04C8    /* Operand 2 */
#define OP2_L (*(volatile uint8_t *)0x4c8)
#define OP2 (*(volatile uint16_t *)0x4c8)
#define OP2_H (*(volatile uint8_t *)0x4c9)
#define OP2_L (*(volatile uint8_t *)0x4c8)
#define OP2 (*(volatile uint16_t *)0x4c8)
#define RESLO_                0x04CA    /* Result Low Word */
#define RESLO_L (*(volatile uint8_t *)0x4ca)
#define RESLO (*(volatile uint16_t *)0x4ca)
#define RESLO_H (*(volatile uint8_t *)0x4cb)
#define RESLO_L (*(volatile uint8_t *)0x4ca)
#define RESLO (*(volatile uint16_t *)0x4ca)
#define RESHI_                0x04CC    /* Result High Word */
#define RESHI_L (*(volatile uint8_t *)0x4cc)
#define RESHI (*(volatile uint16_t *)0x4cc)
#define RESHI_H (*(volatile uint8_t *)0x4cd)
#define RESHI_L (*(volatile uint8_t *)0x4cc)
#define RESHI (*(volatile uint16_t *)0x4cc)
#define SUMEXT_               0x04CE    /* Sum Extend */
#define SUMEXT_L (*(volatile uint8_t *)0x4ce)
#define SUMEXT (*(volatile uint16_t *)0x4ce)
#define SUMEXT_H (*(volatile uint8_t *)0x4cf)
#define SUMEXT_L (*(volatile uint8_t *)0x4ce)
#define SUMEXT (*(volatile uint16_t *)0x4ce)

#define MPY32L_               0x04D0    /* 32-bit operand 1 - multiply - low word */
#define MPY32L_L (*(volatile uint8_t *)0x4d0)
#define MPY32L (*(volatile uint16_t *)0x4d0)
#define MPY32L_H (*(volatile uint8_t *)0x4d1)
#define MPY32L_L (*(volatile uint8_t *)0x4d0)
#define MPY32L (*(volatile uint16_t *)0x4d0)
#define MPY32H_               0x04D2    /* 32-bit operand 1 - multiply - high word */
#define MPY32H_L (*(volatile uint8_t *)0x4d2)
#define MPY32H (*(volatile uint16_t *)0x4d2)
#define MPY32H_H (*(volatile uint8_t *)0x4d3)
#define MPY32H_L (*(volatile uint8_t *)0x4d2)
#define MPY32H (*(volatile uint16_t *)0x4d2)
#define MPYS32L_              0x04D4    /* 32-bit operand 1 - signed multiply - low word */
#define MPYS32L_L (*(volatile uint8_t *)0x4d4)
#define MPYS32L (*(volatile uint16_t *)0x4d4)
#define MPYS32L_H (*(volatile uint8_t *)0x4d5)
#define MPYS32L_L (*(volatile uint8_t *)0x4d4)
#define MPYS32L (*(volatile uint16_t *)0x4d4)
#define MPYS32H_              0x04D6    /* 32-bit operand 1 - signed multiply - high word */
#define MPYS32H_L (*(volatile uint8_t *)0x4d6)
#define MPYS32H (*(volatile uint16_t *)0x4d6)
#define MPYS32H_H (*(volatile uint8_t *)0x4d7)
#define MPYS32H_L (*(volatile uint8_t *)0x4d6)
#define MPYS32H (*(volatile uint16_t *)0x4d6)
#define MAC32L_               0x04D8    /* 32-bit operand 1 - multiply accumulate - low word */
#define MAC32L_L (*(volatile uint8_t *)0x4d8)
#define MAC32L (*(volatile uint16_t *)0x4d8)
#define MAC32L_H (*(volatile uint8_t *)0x4d9)
#define MAC32L_L (*(volatile uint8_t *)0x4d8)
#define MAC32L (*(volatile uint16_t *)0x4d8)
#define MAC32H_               0x04DA    /* 32-bit operand 1 - multiply accumulate - high word */
#define MAC32H_L (*(volatile uint8_t *)0x4da)
#define MAC32H (*(volatile uint16_t *)0x4da)
#define MAC32H_H (*(volatile uint8_t *)0x4db)
#define MAC32H_L (*(volatile uint8_t *)0x4da)
#define MAC32H (*(volatile uint16_t *)0x4da)
#define MACS32L_              0x04DC    /* 32-bit operand 1 - signed multiply accumulate - low word */
#define MACS32L_L (*(volatile uint8_t *)0x4dc)
#define MACS32L (*(volatile uint16_t *)0x4dc)
#define MACS32L_H (*(volatile uint8_t *)0x4dd)
#define MACS32L_L (*(volatile uint8_t *)0x4dc)
#define MACS32L (*(volatile uint16_t *)0x4dc)
#define MACS32H_              0x04DE    /* 32-bit operand 1 - signed multiply accumulate - high word */
#define MACS32H_L (*(volatile uint8_t *)0x4de)
#define MACS32H (*(volatile uint16_t *)0x4de)
#define MACS32H_H (*(volatile uint8_t *)0x4df)
#define MACS32H_L (*(volatile uint8_t *)0x4de)
#define MACS32H (*(volatile uint16_t *)0x4de)
#define OP2L_                 0x04E0    /* 32-bit operand 2 - low word */
#define OP2L_L (*(volatile uint8_t *)0x4e0)
#define OP2L (*(volatile uint16_t *)0x4e0)
#define OP2L_H (*(volatile uint8_t *)0x4e1)
#define OP2L_L (*(volatile uint8_t *)0x4e0)
#define OP2L (*(volatile uint16_t *)0x4e0)
#define OP2H_                 0x04E2    /* 32-bit operand 2 - high word */
#define OP2H_L (*(volatile uint8_t *)0x4e2)
#define OP2H (*(volatile uint16_t *)0x4e2)
#define OP2H_H (*(volatile uint8_t *)0x4e3)
#define OP2H_L (*(volatile uint8_t *)0x4e2)
#define OP2H (*(volatile uint16_t *)0x4e2)
#define RES0_                 0x04E4    /* 32x32-bit result 0 - least significant word */
#define RES0_L (*(volatile uint8_t *)0x4e4)
#define RES0 (*(volatile uint16_t *)0x4e4)
#define RES0_H (*(volatile uint8_t *)0x4e5)
#define RES0_L (*(volatile uint8_t *)0x4e4)
#define RES0 (*(volatile uint16_t *)0x4e4)
#define RES1_                 0x04E6    /* 32x32-bit result 1 */
#define RES1_L (*(volatile uint8_t *)0x4e6)
#define RES1 (*(volatile uint16_t *)0x4e6)
#define RES1_H (*(volatile uint8_t *)0x4e7)
#define RES1_L (*(volatile uint8_t *)0x4e6)
#define RES1 (*(volatile uint16_t *)0x4e6)
#define RES2_                 0x04E8    /* 32x32-bit result 2 */
#define RES2_L (*(volatile uint8_t *)0x4e8)
#define RES2 (*(volatile uint16_t *)0x4e8)
#define RES2_H (*(volatile uint8_t *)0x4e9)
#define RES2_L (*(volatile uint8_t *)0x4e8)
#define RES2 (*(volatile uint16_t *)0x4e8)
#define RES3_                 0x04EA    /* 32x32-bit result 3 - most significant word */
#define RES3_L (*(volatile uint8_t *)0x4ea)
#define RES3 (*(volatile uint16_t *)0x4ea)
#define RES3_H (*(volatile uint8_t *)0x4eb)
#define RES3_L (*(volatile uint8_t *)0x4ea)
#define RES3 (*(volatile uint16_t *)0x4ea)
#define MPY32CTL0_            0x04EC    /* MPY32 Control Register 0 */
#define MPY32CTL0_L (*(volatile uint8_t *)0x4ec)
#define MPY32CTL0 (*(volatile uint16_t *)0x4ec)
#define MPY32CTL0_H (*(volatile uint8_t *)0x4ed)
#define MPY32CTL0_L (*(volatile uint8_t *)0x4ec)
#define MPY32CTL0 (*(volatile uint16_t *)0x4ec)

#define MPY_B               MPY_L      /* Multiply Unsigned/Operand 1 (Byte Access) */
#define MPYS_B              MPYS_L     /* Multiply Signed/Operand 1 (Byte Access) */
#define MAC_B               MAC_L      /* Multiply Unsigned and Accumulate/Operand 1 (Byte Access) */
#define MACS_B              MACS_L     /* Multiply Signed and Accumulate/Operand 1 (Byte Access) */
#define OP2_B               OP2_L      /* Operand 2 (Byte Access) */
#define MPY32L_B            MPY32L_L   /* 32-bit operand 1 - multiply - low word (Byte Access) */
#define MPY32H_B            MPY32H_L   /* 32-bit operand 1 - multiply - high word (Byte Access) */
#define MPYS32L_B           MPYS32L_L  /* 32-bit operand 1 - signed multiply - low word (Byte Access) */
#define MPYS32H_B           MPYS32H_L  /* 32-bit operand 1 - signed multiply - high word (Byte Access) */
#define MAC32L_B            MAC32L_L   /* 32-bit operand 1 - multiply accumulate - low word (Byte Access) */
#define MAC32H_B            MAC32H_L   /* 32-bit operand 1 - multiply accumulate - high word (Byte Access) */
#define MACS32L_B           MACS32L_L  /* 32-bit operand 1 - signed multiply accumulate - low word (Byte Access) */
#define MACS32H_B           MACS32H_L  /* 32-bit operand 1 - signed multiply accumulate - high word (Byte Access) */
#define OP2L_B              OP2L_L     /* 32-bit operand 2 - low word (Byte Access) */
#define OP2H_B              OP2H_L     /* 32-bit operand 2 - high word (Byte Access) */


/* MPY32CTL0 Control Bits */
#define MPYC                (0x0001)  /* Carry of the multiplier */
//#define RESERVED            (0x0002)  /* Reserved */
#define MPYFRAC             (0x0004)  /* Fractional mode */
#define MPYSAT              (0x0008)  /* Saturation mode */
#define MPYM0               (0x0010)  /* Multiplier mode Bit:0 */
#define MPYM1               (0x0020)  /* Multiplier mode Bit:1 */
#define OP1_32              (0x0040)  /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32              (0x0080)  /* Bit-width of operand 2 0:16Bit / 1:32Bit */
#define MPYDLYWRTEN         (0x0100)  /* Delayed write enable */
#define MPYDLY32            (0x0200)  /* Delayed write mode */

/* MPY32CTL0 Control Bits */
#define MPYC_L              (0x0001)  /* Carry of the multiplier */
//#define RESERVED            (0x0002)  /* Reserved */
#define MPYFRAC_L           (0x0004)  /* Fractional mode */
#define MPYSAT_L            (0x0008)  /* Saturation mode */
#define MPYM0_L             (0x0010)  /* Multiplier mode Bit:0 */
#define MPYM1_L             (0x0020)  /* Multiplier mode Bit:1 */
#define OP1_32_L            (0x0040)  /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32_L            (0x0080)  /* Bit-width of operand 2 0:16Bit / 1:32Bit */

/* MPY32CTL0 Control Bits */
//#define RESERVED            (0x0002)  /* Reserved */
#define MPYDLYWRTEN_H       (0x0001)  /* Delayed write enable */
#define MPYDLY32_H          (0x0002)  /* Delayed write mode */

#define MPYM_0              (0x0000)  /* Multiplier mode: MPY */
#define MPYM_1              (0x0010)  /* Multiplier mode: MPYS */
#define MPYM_2              (0x0020)  /* Multiplier mode: MAC */
#define MPYM_3              (0x0030)  /* Multiplier mode: MACS */
#define MPYM__MPY           (0x0000)  /* Multiplier mode: MPY */
#define MPYM__MPYS          (0x0010)  /* Multiplier mode: MPYS */
#define MPYM__MAC           (0x0020)  /* Multiplier mode: MAC */
#define MPYM__MACS          (0x0030)  /* Multiplier mode: MACS */

/************************************************************
* PMM - Power Management System
************************************************************/
#define __MSP430_HAS_PMM_FR5xx__      /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PMM_FR5xx__ 0x0120
#define PMM_BASE __MSP430_BASEADDRESS_PMM_FR5xx__

#define PMMCTL0_              0x0120    /* PMM Control 0 */
#define PMMCTL0_L (*(volatile uint8_t *)0x120)
#define PMMCTL0 (*(volatile uint16_t *)0x120)
#define PMMCTL0_H (*(volatile uint8_t *)0x121)
#define PMMCTL0_L (*(volatile uint8_t *)0x120)
#define PMMCTL0 (*(volatile uint16_t *)0x120)
#define PMMIFG_               0x012A    /* PMM Interrupt Flag */
#define PMMIFG_L (*(volatile uint8_t *)0x12a)
#define PMMIFG (*(volatile uint16_t *)0x12a)
#define PMMIFG_H (*(volatile uint8_t *)0x12b)
#define PMMIFG_L (*(volatile uint8_t *)0x12a)
#define PMMIFG (*(volatile uint16_t *)0x12a)
#define PM5CTL0_              0x0130    /* PMM Power Mode 5 Control Register 0 */
#define PM5CTL0_L (*(volatile uint8_t *)0x130)
#define PM5CTL0 (*(volatile uint16_t *)0x130)
#define PM5CTL0_H (*(volatile uint8_t *)0x131)
#define PM5CTL0_L (*(volatile uint8_t *)0x130)
#define PM5CTL0 (*(volatile uint16_t *)0x130)

#define PMMPW               (0xA500)  /* PMM Register Write Password */
#define PMMPW_H             (0xA5)    /* PMM Register Write Password for high word access */

/* PMMCTL0 Control Bits */
#define PMMSWBOR            (0x0004)  /* PMM Software BOR */
#define PMMSWPOR            (0x0008)  /* PMM Software POR */
#define PMMREGOFF           (0x0010)  /* PMM Turn Regulator off */
#define SVSLE               (0x0020)  /* SVS low side enable */
#define SVSHE               (0x0040)  /* SVS high side enable */

/* PMMCTL0 Control Bits */
#define PMMSWBOR_L          (0x0004)  /* PMM Software BOR */
#define PMMSWPOR_L          (0x0008)  /* PMM Software POR */
#define PMMREGOFF_L         (0x0010)  /* PMM Turn Regulator off */
#define SVSLE_L             (0x0020)  /* SVS low side enable */
#define SVSHE_L             (0x0040)  /* SVS high side enable */

/* PMMCTL0 Control Bits */

/* PMMIFG Control Bits */
#define PMMBORIFG           (0x0100)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG           (0x0200)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG           (0x0400)  /* PMM Software POR interrupt flag */
#define SVSLIFG             (0x1000)  /* SVS high side interrupt flag */
#define SVSHIFG             (0x2000)  /* SVS low side interrupt flag */
#define PMMLPM5IFG          (0x8000)  /* LPM5 indication Flag */

/* PMMIFG Control Bits */

/* PMMIFG Control Bits */
#define PMMBORIFG_H         (0x0001)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG_H         (0x0002)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG_H         (0x0004)  /* PMM Software POR interrupt flag */
#define SVSLIFG_H           (0x0010)  /* SVS high side interrupt flag */
#define SVSHIFG_H           (0x0020)  /* SVS low side interrupt flag */
#define PMMLPM5IFG_H        (0x0080)  /* LPM5 indication Flag */


/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5            (0x0001)  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5_L          (0x0001)  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/* PM5CTL0 Power Mode 5 Control Bits */

/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_R__ 0x0200
#define P1_BASE __MSP430_BASEADDRESS_PORT1_R__
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT2_R__ 0x0200
#define P2_BASE __MSP430_BASEADDRESS_PORT2_R__
#define __MSP430_HAS_PORTA_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTA_R__ 0x0200
#define PA_BASE __MSP430_BASEADDRESS_PORTA_R__

#define PAIN_                 0x0200    /* Port A Input */
#define PAIN_L (*(volatile uint8_t *)0x200)
#define PAIN (*(volatile uint16_t *)0x200)
#define PAIN_H (*(volatile uint8_t *)0x201)
#define PAIN_L (*(volatile uint8_t *)0x200)
#define PAIN (*(volatile uint16_t *)0x200)
#define PAOUT_                0x0202    /* Port A Output */
#define PAOUT_L (*(volatile uint8_t *)0x202)
#define PAOUT (*(volatile uint16_t *)0x202)
#define PAOUT_H (*(volatile uint8_t *)0x203)
#define PAOUT_L (*(volatile uint8_t *)0x202)
#define PAOUT (*(volatile uint16_t *)0x202)
#define PADIR_                0x0204    /* Port A Direction */
#define PADIR_L (*(volatile uint8_t *)0x204)
#define PADIR (*(volatile uint16_t *)0x204)
#define PADIR_H (*(volatile uint8_t *)0x205)
#define PADIR_L (*(volatile uint8_t *)0x204)
#define PADIR (*(volatile uint16_t *)0x204)
#define PAREN_                0x0206    /* Port A Resistor Enable */
#define PAREN_L (*(volatile uint8_t *)0x206)
#define PAREN (*(volatile uint16_t *)0x206)
#define PAREN_H (*(volatile uint8_t *)0x207)
#define PAREN_L (*(volatile uint8_t *)0x206)
#define PAREN (*(volatile uint16_t *)0x206)
#define PASEL0_               0x020A    /* Port A Selection 0 */
#define PASEL0_L (*(volatile uint8_t *)0x20a)
#define PASEL0 (*(volatile uint16_t *)0x20a)
#define PASEL0_H (*(volatile uint8_t *)0x20b)
#define PASEL0_L (*(volatile uint8_t *)0x20a)
#define PASEL0 (*(volatile uint16_t *)0x20a)
#define PASEL1_               0x020C    /* Port A Selection 1 */
#define PASEL1_L (*(volatile uint8_t *)0x20c)
#define PASEL1 (*(volatile uint16_t *)0x20c)
#define PASEL1_H (*(volatile uint8_t *)0x20d)
#define PASEL1_L (*(volatile uint8_t *)0x20c)
#define PASEL1 (*(volatile uint16_t *)0x20c)
#define PASELC_               0x0216    /* Port A Complement Selection */
#define PASELC_L (*(volatile uint8_t *)0x216)
#define PASELC (*(volatile uint16_t *)0x216)
#define PASELC_H (*(volatile uint8_t *)0x217)
#define PASELC_L (*(volatile uint8_t *)0x216)
#define PASELC (*(volatile uint16_t *)0x216)
#define PAIES_                0x0218    /* Port A Interrupt Edge Select */
#define PAIES_L (*(volatile uint8_t *)0x218)
#define PAIES (*(volatile uint16_t *)0x218)
#define PAIES_H (*(volatile uint8_t *)0x219)
#define PAIES_L (*(volatile uint8_t *)0x218)
#define PAIES (*(volatile uint16_t *)0x218)
#define PAIE_                 0x021A    /* Port A Interrupt Enable */
#define PAIE_L (*(volatile uint8_t *)0x21a)
#define PAIE (*(volatile uint16_t *)0x21a)
#define PAIE_H (*(volatile uint8_t *)0x21b)
#define PAIE_L (*(volatile uint8_t *)0x21a)
#define PAIE (*(volatile uint16_t *)0x21a)
#define PAIFG_                0x021C    /* Port A Interrupt Flag */
#define PAIFG_L (*(volatile uint8_t *)0x21c)
#define PAIFG (*(volatile uint16_t *)0x21c)
#define PAIFG_H (*(volatile uint8_t *)0x21d)
#define PAIFG_L (*(volatile uint8_t *)0x21c)
#define PAIFG (*(volatile uint16_t *)0x21c)























#define P1IV_                 0x020E    /* Port 1 Interrupt Vector Word */
#define P1IV (*(volatile uint16_t *)0x20e)
#define P2IV_                 0x021E    /* Port 2 Interrupt Vector Word */
#define P2IV (*(volatile uint16_t *)0x21e)
#define P1IN                (PAIN_L)  /* Port 1 Input */
#define P1OUT               (PAOUT_L) /* Port 1 Output */
#define P1DIR               (PADIR_L) /* Port 1 Direction */
#define P1REN               (PAREN_L) /* Port 1 Resistor Enable */
#define P1SEL0              (PASEL0_L) /* Port 1 Selection 0 */
#define P1SEL1              (PASEL1_L) /* Port 1 Selection 1 */
#define P1SELC              (PASELC_L) /* Port 1 Complement Selection */
#define P1IES               (PAIES_L) /* Port 1 Interrupt Edge Select */
#define P1IE                (PAIE_L)  /* Port 1 Interrupt Enable */
#define P1IFG               (PAIFG_L) /* Port 1 Interrupt Flag */

//Definitions for P1IV
#define P1IV_NONE            (0x0000)    /* No Interrupt pending */
#define P1IV_P1IFG0          (0x0002)    /* P1IV P1IFG.0 */
#define P1IV_P1IFG1          (0x0004)    /* P1IV P1IFG.1 */
#define P1IV_P1IFG2          (0x0006)    /* P1IV P1IFG.2 */
#define P1IV_P1IFG3          (0x0008)    /* P1IV P1IFG.3 */
#define P1IV_P1IFG4          (0x000A)    /* P1IV P1IFG.4 */
#define P1IV_P1IFG5          (0x000C)    /* P1IV P1IFG.5 */
#define P1IV_P1IFG6          (0x000E)    /* P1IV P1IFG.6 */
#define P1IV_P1IFG7          (0x0010)    /* P1IV P1IFG.7 */


#define P2IN                (PAIN_H)  /* Port 2 Input */
#define P2OUT               (PAOUT_H) /* Port 2 Output */
#define P2DIR               (PADIR_H) /* Port 2 Direction */
#define P2REN               (PAREN_H) /* Port 2 Resistor Enable */
#define P2SEL0              (PASEL0_H) /* Port 2 Selection 0 */
#define P2SEL1              (PASEL1_H) /* Port 2 Selection 1 */
#define P2SELC              (PASELC_H) /* Port 2 Complement Selection */
#define P2IES               (PAIES_H) /* Port 2 Interrupt Edge Select */
#define P2IE                (PAIE_H)  /* Port 2 Interrupt Enable */
#define P2IFG               (PAIFG_H) /* Port 2 Interrupt Flag */

//Definitions for P2IV
#define P2IV_NONE            (0x0000)    /* No Interrupt pending */
#define P2IV_P2IFG0          (0x0002)    /* P2IV P2IFG.0 */
#define P2IV_P2IFG1          (0x0004)    /* P2IV P2IFG.1 */
#define P2IV_P2IFG2          (0x0006)    /* P2IV P2IFG.2 */
#define P2IV_P2IFG3          (0x0008)    /* P2IV P2IFG.3 */
#define P2IV_P2IFG4          (0x000A)    /* P2IV P2IFG.4 */
#define P2IV_P2IFG5          (0x000C)    /* P2IV P2IFG.5 */
#define P2IV_P2IFG6          (0x000E)    /* P2IV P2IFG.6 */
#define P2IV_P2IFG7          (0x0010)    /* P2IV P2IFG.7 */



/************************************************************
* DIGITAL I/O Port3/4 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT3_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT3_R__ 0x0220
#define P3_BASE __MSP430_BASEADDRESS_PORT3_R__
#define __MSP430_HAS_PORT4_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT4_R__ 0x0220
#define P4_BASE __MSP430_BASEADDRESS_PORT4_R__
#define __MSP430_HAS_PORTB_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTB_R__ 0x0220
#define PB_BASE __MSP430_BASEADDRESS_PORTB_R__

#define PBIN_                 0x0220    /* Port B Input */
#define PBIN_L (*(volatile uint8_t *)0x220)
#define PBIN (*(volatile uint16_t *)0x220)
#define PBIN_H (*(volatile uint8_t *)0x221)
#define PBIN_L (*(volatile uint8_t *)0x220)
#define PBIN (*(volatile uint16_t *)0x220)
#define PBOUT_                0x0222    /* Port B Output */
#define PBOUT_L (*(volatile uint8_t *)0x222)
#define PBOUT (*(volatile uint16_t *)0x222)
#define PBOUT_H (*(volatile uint8_t *)0x223)
#define PBOUT_L (*(volatile uint8_t *)0x222)
#define PBOUT (*(volatile uint16_t *)0x222)
#define PBDIR_                0x0224    /* Port B Direction */
#define PBDIR_L (*(volatile uint8_t *)0x224)
#define PBDIR (*(volatile uint16_t *)0x224)
#define PBDIR_H (*(volatile uint8_t *)0x225)
#define PBDIR_L (*(volatile uint8_t *)0x224)
#define PBDIR (*(volatile uint16_t *)0x224)
#define PBREN_                0x0226    /* Port B Resistor Enable */
#define PBREN_L (*(volatile uint8_t *)0x226)
#define PBREN (*(volatile uint16_t *)0x226)
#define PBREN_H (*(volatile uint8_t *)0x227)
#define PBREN_L (*(volatile uint8_t *)0x226)
#define PBREN (*(volatile uint16_t *)0x226)
#define PBSEL0_               0x022A    /* Port B Selection 0 */
#define PBSEL0_L (*(volatile uint8_t *)0x22a)
#define PBSEL0 (*(volatile uint16_t *)0x22a)
#define PBSEL0_H (*(volatile uint8_t *)0x22b)
#define PBSEL0_L (*(volatile uint8_t *)0x22a)
#define PBSEL0 (*(volatile uint16_t *)0x22a)
#define PBSEL1_               0x022C    /* Port B Selection 1 */
#define PBSEL1_L (*(volatile uint8_t *)0x22c)
#define PBSEL1 (*(volatile uint16_t *)0x22c)
#define PBSEL1_H (*(volatile uint8_t *)0x22d)
#define PBSEL1_L (*(volatile uint8_t *)0x22c)
#define PBSEL1 (*(volatile uint16_t *)0x22c)
#define PBSELC_               0x0236    /* Port B Complement Selection */
#define PBSELC_L (*(volatile uint8_t *)0x236)
#define PBSELC (*(volatile uint16_t *)0x236)
#define PBSELC_H (*(volatile uint8_t *)0x237)
#define PBSELC_L (*(volatile uint8_t *)0x236)
#define PBSELC (*(volatile uint16_t *)0x236)
#define PBIES_                0x0238    /* Port B Interrupt Edge Select */
#define PBIES_L (*(volatile uint8_t *)0x238)
#define PBIES (*(volatile uint16_t *)0x238)
#define PBIES_H (*(volatile uint8_t *)0x239)
#define PBIES_L (*(volatile uint8_t *)0x238)
#define PBIES (*(volatile uint16_t *)0x238)
#define PBIE_                 0x023A    /* Port B Interrupt Enable */
#define PBIE_L (*(volatile uint8_t *)0x23a)
#define PBIE (*(volatile uint16_t *)0x23a)
#define PBIE_H (*(volatile uint8_t *)0x23b)
#define PBIE_L (*(volatile uint8_t *)0x23a)
#define PBIE (*(volatile uint16_t *)0x23a)
#define PBIFG_                0x023C    /* Port B Interrupt Flag */
#define PBIFG_L (*(volatile uint8_t *)0x23c)
#define PBIFG (*(volatile uint16_t *)0x23c)
#define PBIFG_H (*(volatile uint8_t *)0x23d)
#define PBIFG_L (*(volatile uint8_t *)0x23c)
#define PBIFG (*(volatile uint16_t *)0x23c)























#define P3IV_                 0x022E    /* Port 3 Interrupt Vector Word */
#define P3IV (*(volatile uint16_t *)0x22e)
#define P4IV_                 0x023E    /* Port 4 Interrupt Vector Word */
#define P4IV (*(volatile uint16_t *)0x23e)
#define P3IN                (PBIN_L)  /* Port 3 Input */
#define P3OUT               (PBOUT_L) /* Port 3 Output */
#define P3DIR               (PBDIR_L) /* Port 3 Direction */
#define P3REN               (PBREN_L) /* Port 3 Resistor Enable */
#define P3SEL0              (PBSEL0_L) /* Port 3 Selection 0 */
#define P3SEL1              (PBSEL1_L) /* Port 3 Selection 1 */
#define P3SELC              (PBSELC_L) /* Port 3 Complement Selection */
#define P3IES               (PBIES_L) /* Port 3 Interrupt Edge Select */
#define P3IE                (PBIE_L)  /* Port 3 Interrupt Enable */
#define P3IFG               (PBIFG_L) /* Port 3 Interrupt Flag */

//Definitions for P3IV
#define P3IV_NONE            (0x0000)    /* No Interrupt pending */
#define P3IV_P3IFG0          (0x0002)    /* P3IV P3IFG.0 */
#define P3IV_P3IFG1          (0x0004)    /* P3IV P3IFG.1 */
#define P3IV_P3IFG2          (0x0006)    /* P3IV P3IFG.2 */
#define P3IV_P3IFG3          (0x0008)    /* P3IV P3IFG.3 */
#define P3IV_P3IFG4          (0x000A)    /* P3IV P3IFG.4 */
#define P3IV_P3IFG5          (0x000C)    /* P3IV P3IFG.5 */
#define P3IV_P3IFG6          (0x000E)    /* P3IV P3IFG.6 */
#define P3IV_P3IFG7          (0x0010)    /* P3IV P3IFG.7 */


#define P4IN                (PBIN_H)  /* Port 4 Input */
#define P4OUT               (PBOUT_H) /* Port 4 Output */
#define P4DIR               (PBDIR_H) /* Port 4 Direction */
#define P4REN               (PBREN_H) /* Port 4 Resistor Enable */
#define P4SEL0              (PBSEL0_H) /* Port 4 Selection 0 */
#define P4SEL1              (PBSEL1_H) /* Port 4 Selection 1 */
#define P4SELC              (PBSELC_H) /* Port 4 Complement Selection */
#define P4IES               (PBIES_H) /* Port 4 Interrupt Edge Select */
#define P4IE                (PBIE_H)  /* Port 4 Interrupt Enable */
#define P4IFG               (PBIFG_H) /* Port 4 Interrupt Flag */

//Definitions for P4IV
#define P4IV_NONE            (0x0000)    /* No Interrupt pending */
#define P4IV_P4IFG0          (0x0002)    /* P4IV P4IFG.0 */
#define P4IV_P4IFG1          (0x0004)    /* P4IV P4IFG.1 */
#define P4IV_P4IFG2          (0x0006)    /* P4IV P4IFG.2 */
#define P4IV_P4IFG3          (0x0008)    /* P4IV P4IFG.3 */
#define P4IV_P4IFG4          (0x000A)    /* P4IV P4IFG.4 */
#define P4IV_P4IFG5          (0x000C)    /* P4IV P4IFG.5 */
#define P4IV_P4IFG6          (0x000E)    /* P4IV P4IFG.6 */
#define P4IV_P4IFG7          (0x0010)    /* P4IV P4IFG.7 */




/************************************************************
* DIGITAL I/O PortJ Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORTJ_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTJ_R__ 0x0320
#define PJ_BASE __MSP430_BASEADDRESS_PORTJ_R__

#define PJIN_                 0x0320    /* Port J Input */
#define PJIN_L (*(volatile uint8_t *)0x320)
#define PJIN (*(volatile uint16_t *)0x320)
#define PJIN_H (*(volatile uint8_t *)0x321)
#define PJIN_L (*(volatile uint8_t *)0x320)
#define PJIN (*(volatile uint16_t *)0x320)
#define PJOUT_                0x0322    /* Port J Output */
#define PJOUT_L (*(volatile uint8_t *)0x322)
#define PJOUT (*(volatile uint16_t *)0x322)
#define PJOUT_H (*(volatile uint8_t *)0x323)
#define PJOUT_L (*(volatile uint8_t *)0x322)
#define PJOUT (*(volatile uint16_t *)0x322)
#define PJDIR_                0x0324    /* Port J Direction */
#define PJDIR_L (*(volatile uint8_t *)0x324)
#define PJDIR (*(volatile uint16_t *)0x324)
#define PJDIR_H (*(volatile uint8_t *)0x325)
#define PJDIR_L (*(volatile uint8_t *)0x324)
#define PJDIR (*(volatile uint16_t *)0x324)
#define PJREN_                0x0326    /* Port J Resistor Enable */
#define PJREN_L (*(volatile uint8_t *)0x326)
#define PJREN (*(volatile uint16_t *)0x326)
#define PJREN_H (*(volatile uint8_t *)0x327)
#define PJREN_L (*(volatile uint8_t *)0x326)
#define PJREN (*(volatile uint16_t *)0x326)
#define PJSEL0_               0x032A    /* Port J Selection 0 */
#define PJSEL0_L (*(volatile uint8_t *)0x32a)
#define PJSEL0 (*(volatile uint16_t *)0x32a)
#define PJSEL0_H (*(volatile uint8_t *)0x32b)
#define PJSEL0_L (*(volatile uint8_t *)0x32a)
#define PJSEL0 (*(volatile uint16_t *)0x32a)
#define PJSEL1_               0x032C    /* Port J Selection 1 */
#define PJSEL1_L (*(volatile uint8_t *)0x32c)
#define PJSEL1 (*(volatile uint16_t *)0x32c)
#define PJSEL1_H (*(volatile uint8_t *)0x32d)
#define PJSEL1_L (*(volatile uint8_t *)0x32c)
#define PJSEL1 (*(volatile uint16_t *)0x32c)
#define PJSELC_               0x0336    /* Port J Complement Selection */
#define PJSELC_L (*(volatile uint8_t *)0x336)
#define PJSELC (*(volatile uint16_t *)0x336)
#define PJSELC_H (*(volatile uint8_t *)0x337)
#define PJSELC_L (*(volatile uint8_t *)0x336)
#define PJSELC (*(volatile uint16_t *)0x336)













/************************************************************
* Shared Reference
************************************************************/
#define __MSP430_HAS_REF__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_REF__ 0x01B0
#define REF_BASE __MSP430_BASEADDRESS_REF__

#define REFCTL0_              0x01B0    /* REF Shared Reference control register 0 */
#define REFCTL0_L (*(volatile uint8_t *)0x1b0)
#define REFCTL0 (*(volatile uint16_t *)0x1b0)
#define REFCTL0_H (*(volatile uint8_t *)0x1b1)
#define REFCTL0_L (*(volatile uint8_t *)0x1b0)
#define REFCTL0 (*(volatile uint16_t *)0x1b0)

/* REFCTL0 Control Bits */
#define REFON               (0x0001)  /* REF Reference On */
//#define RESERVED            (0x0002)  /* Reserved */
//#define RESERVED            (0x0004)  /* Reserved */
#define REFTCOFF            (0x0008)  /* REF Temp.Sensor off */
#define REFVSEL0            (0x0010)  /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1            (0x0020)  /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040)  /* Reserved */
//#define RESERVED            (0x0080)  /* Reserved */
#define REFGENACT           (0x0100)  /* REF Reference generator active */
#define REFBGACT            (0x0200)  /* REF Reference bandgap active */
#define REFGENBUSY          (0x0400)  /* REF Reference generator busy */
#define BGMODE              (0x0800)  /* REF Bandgap mode */
//#define RESERVED            (0x1000)  /* Reserved */
//#define RESERVED            (0x2000)  /* Reserved */
//#define RESERVED            (0x4000)  /* Reserved */
//#define RESERVED            (0x8000)  /* Reserved */

/* REFCTL0 Control Bits */
#define REFON_L             (0x0001)  /* REF Reference On */
//#define RESERVED            (0x0002)  /* Reserved */
//#define RESERVED            (0x0004)  /* Reserved */
#define REFTCOFF_L          (0x0008)  /* REF Temp.Sensor off */
#define REFVSEL0_L          (0x0010)  /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1_L          (0x0020)  /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040)  /* Reserved */
//#define RESERVED            (0x0080)  /* Reserved */
//#define RESERVED            (0x1000)  /* Reserved */
//#define RESERVED            (0x2000)  /* Reserved */
//#define RESERVED            (0x4000)  /* Reserved */
//#define RESERVED            (0x8000)  /* Reserved */

/* REFCTL0 Control Bits */
//#define RESERVED            (0x0002)  /* Reserved */
//#define RESERVED            (0x0004)  /* Reserved */
//#define RESERVED            (0x0040)  /* Reserved */
//#define RESERVED            (0x0080)  /* Reserved */
#define REFGENACT_H         (0x0001)  /* REF Reference generator active */
#define REFBGACT_H          (0x0002)  /* REF Reference bandgap active */
#define REFGENBUSY_H        (0x0004)  /* REF Reference generator busy */
#define BGMODE_H            (0x0008)  /* REF Bandgap mode */
//#define RESERVED            (0x1000)  /* Reserved */
//#define RESERVED            (0x2000)  /* Reserved */
//#define RESERVED            (0x4000)  /* Reserved */
//#define RESERVED            (0x8000)  /* Reserved */

#define REFVSEL_0           (0x0000)  /* REF Reference Voltage Level Select 1.5V */
#define REFVSEL_1           (0x0010)  /* REF Reference Voltage Level Select 2.0V */
#define REFVSEL_2           (0x0020)  /* REF Reference Voltage Level Select 2.5V */
#define REFVSEL_3           (0x0030)  /* REF Reference Voltage Level Select 2.5V */

/************************************************************
* Real Time Clock
************************************************************/
#define __MSP430_HAS_RTC_B__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RTC_B__ 0x04A0
#define RTC_B_BASE __MSP430_BASEADDRESS_RTC_B__

#define RTCCTL01_             0x04A0    /* Real Timer Control 0/1 */
#define RTCCTL01_L (*(volatile uint8_t *)0x4a0)
#define RTCCTL01 (*(volatile uint16_t *)0x4a0)
#define RTCCTL01_H (*(volatile uint8_t *)0x4a1)
#define RTCCTL01_L (*(volatile uint8_t *)0x4a0)
#define RTCCTL01 (*(volatile uint16_t *)0x4a0)
#define RTCCTL23_             0x04A2    /* Real Timer Control 2/3 */
#define RTCCTL23_L (*(volatile uint8_t *)0x4a2)
#define RTCCTL23 (*(volatile uint16_t *)0x4a2)
#define RTCCTL23_H (*(volatile uint8_t *)0x4a3)
#define RTCCTL23_L (*(volatile uint8_t *)0x4a2)
#define RTCCTL23 (*(volatile uint16_t *)0x4a2)
#define RTCPS0CTL_            0x04A8    /* Real Timer Prescale Timer 0 Control */
#define RTCPS0CTL_L (*(volatile uint8_t *)0x4a8)
#define RTCPS0CTL (*(volatile uint16_t *)0x4a8)
#define RTCPS0CTL_H (*(volatile uint8_t *)0x4a9)
#define RTCPS0CTL_L (*(volatile uint8_t *)0x4a8)
#define RTCPS0CTL (*(volatile uint16_t *)0x4a8)
#define RTCPS1CTL_            0x04AA    /* Real Timer Prescale Timer 1 Control */
#define RTCPS1CTL_L (*(volatile uint8_t *)0x4aa)
#define RTCPS1CTL (*(volatile uint16_t *)0x4aa)
#define RTCPS1CTL_H (*(volatile uint8_t *)0x4ab)
#define RTCPS1CTL_L (*(volatile uint8_t *)0x4aa)
#define RTCPS1CTL (*(volatile uint16_t *)0x4aa)
#define RTCPS_                0x04AC    /* Real Timer Prescale Timer Control */
#define RTCPS_L (*(volatile uint8_t *)0x4ac)
#define RTCPS (*(volatile uint16_t *)0x4ac)
#define RTCPS_H (*(volatile uint8_t *)0x4ad)
#define RTCPS_L (*(volatile uint8_t *)0x4ac)
#define RTCPS (*(volatile uint16_t *)0x4ac)
#define RTCIV_                0x04AE    /* Real Time Clock Interrupt Vector */
#define RTCIV (*(volatile uint16_t *)0x4ae)
#define RTCTIM0_              0x04B0    /* Real Time Clock Time 0 */
#define RTCTIM0_L (*(volatile uint8_t *)0x4b0)
#define RTCTIM0 (*(volatile uint16_t *)0x4b0)
#define RTCTIM0_H (*(volatile uint8_t *)0x4b1)
#define RTCTIM0_L (*(volatile uint8_t *)0x4b0)
#define RTCTIM0 (*(volatile uint16_t *)0x4b0)
#define RTCTIM1_              0x04B2    /* Real Time Clock Time 1 */
#define RTCTIM1_L (*(volatile uint8_t *)0x4b2)
#define RTCTIM1 (*(volatile uint16_t *)0x4b2)
#define RTCTIM1_H (*(volatile uint8_t *)0x4b3)
#define RTCTIM1_L (*(volatile uint8_t *)0x4b2)
#define RTCTIM1 (*(volatile uint16_t *)0x4b2)
#define RTCDATE_              0x04B4    /* Real Time Clock Date */
#define RTCDATE_L (*(volatile uint8_t *)0x4b4)
#define RTCDATE (*(volatile uint16_t *)0x4b4)
#define RTCDATE_H (*(volatile uint8_t *)0x4b5)
#define RTCDATE_L (*(volatile uint8_t *)0x4b4)
#define RTCDATE (*(volatile uint16_t *)0x4b4)
#define RTCYEAR_              0x04B6    /* Real Time Clock Year */
#define RTCYEAR_L (*(volatile uint8_t *)0x4b6)
#define RTCYEAR (*(volatile uint16_t *)0x4b6)
#define RTCYEAR_H (*(volatile uint8_t *)0x4b7)
#define RTCYEAR_L (*(volatile uint8_t *)0x4b6)
#define RTCYEAR (*(volatile uint16_t *)0x4b6)
#define RTCAMINHR_            0x04B8    /* Real Time Clock Alarm Min/Hour */
#define RTCAMINHR_L (*(volatile uint8_t *)0x4b8)
#define RTCAMINHR (*(volatile uint16_t *)0x4b8)
#define RTCAMINHR_H (*(volatile uint8_t *)0x4b9)
#define RTCAMINHR_L (*(volatile uint8_t *)0x4b8)
#define RTCAMINHR (*(volatile uint16_t *)0x4b8)
#define RTCADOWDAY_           0x04BA    /* Real Time Clock Alarm day of week/day */
#define RTCADOWDAY_L (*(volatile uint8_t *)0x4ba)
#define RTCADOWDAY (*(volatile uint16_t *)0x4ba)
#define RTCADOWDAY_H (*(volatile uint8_t *)0x4bb)
#define RTCADOWDAY_L (*(volatile uint8_t *)0x4ba)
#define RTCADOWDAY (*(volatile uint16_t *)0x4ba)
#define BIN2BCD_              0x04BC    /* Real Time Binary-to-BCD conversion register */
#define BIN2BCD (*(volatile uint16_t *)0x4bc)
#define BCD2BIN_              0x04BE    /* Real Time BCD-to-binary conversion register */
#define BCD2BIN (*(volatile uint16_t *)0x4be)

#define RTCCTL0             RTCCTL01_L  /* Real Time Clock Control 0 */
#define RTCCTL1             RTCCTL01_H  /* Real Time Clock Control 1 */
#define RTCCTL2             RTCCTL23_L  /* Real Time Clock Control 2 */
#define RTCCTL3             RTCCTL23_H  /* Real Time Clock Control 3 */
#define RTCNT12             RTCTIM0
#define RTCNT34             RTCTIM1
#define RTCNT1              RTCTIM0_L
#define RTCNT2              RTCTIM0_H
#define RTCNT3              RTCTIM1_L
#define RTCNT4              RTCTIM1_H
#define RTCSEC              RTCTIM0_L
#define RTCMIN              RTCTIM0_H
#define RTCHOUR             RTCTIM1_L
#define RTCDOW              RTCTIM1_H
#define RTCDAY              RTCDATE_L
#define RTCMON              RTCDATE_H
#define RTCYEARL            RTCYEAR_L
#define RTCYEARH            RTCYEAR_H
#define RT0PS               RTCPS_L
#define RT1PS               RTCPS_H
#define RTCAMIN             RTCAMINHR_L  /* Real Time Clock Alarm Min */
#define RTCAHOUR            RTCAMINHR_H  /* Real Time Clock Alarm Hour */
#define RTCADOW             RTCADOWDAY_L /* Real Time Clock Alarm day of week */
#define RTCADAY             RTCADOWDAY_H /* Real Time Clock Alarm day */

/* RTCCTL01 Control Bits */
#define RTCBCD              (0x8000)     /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD             (0x4000)     /* RTC Hold */
//#define RESERVED            (0x2000)     /* RESERVED */
#define RTCRDY              (0x1000)     /* RTC Ready */
//#define RESERVED            (0x0800)     /* RESERVED */
//#define RESERVED            (0x0400)     /* RESERVED */
#define RTCTEV1             (0x0200)     /* RTC Time Event 1 */
#define RTCTEV0             (0x0100)     /* RTC Time Event 0 */
#define RTCOFIE             (0x0080)     /* RTC 32kHz cyrstal oscillator fault interrupt enable */
#define RTCTEVIE            (0x0040)     /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE              (0x0020)     /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE            (0x0010)     /* RTC Ready Interrupt Enable Flag */
#define RTCOFIFG            (0x0008)     /* RTC 32kHz cyrstal oscillator fault interrupt flag */
#define RTCTEVIFG           (0x0004)     /* RTC Time Event Interrupt Flag */
#define RTCAIFG             (0x0002)     /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG           (0x0001)     /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
//#define RESERVED            (0x2000)     /* RESERVED */
//#define RESERVED            (0x0800)     /* RESERVED */
//#define RESERVED            (0x0400)     /* RESERVED */
#define RTCOFIE_L           (0x0080)     /* RTC 32kHz cyrstal oscillator fault interrupt enable */
#define RTCTEVIE_L          (0x0040)     /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE_L            (0x0020)     /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE_L          (0x0010)     /* RTC Ready Interrupt Enable Flag */
#define RTCOFIFG_L          (0x0008)     /* RTC 32kHz cyrstal oscillator fault interrupt flag */
#define RTCTEVIFG_L         (0x0004)     /* RTC Time Event Interrupt Flag */
#define RTCAIFG_L           (0x0002)     /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG_L         (0x0001)     /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
#define RTCBCD_H            (0x0080)     /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD_H           (0x0040)     /* RTC Hold */
//#define RESERVED            (0x2000)     /* RESERVED */
#define RTCRDY_H            (0x0010)     /* RTC Ready */
//#define RESERVED            (0x0800)     /* RESERVED */
//#define RESERVED            (0x0400)     /* RESERVED */
#define RTCTEV1_H           (0x0002)     /* RTC Time Event 1 */
#define RTCTEV0_H           (0x0001)     /* RTC Time Event 0 */

#define RTCTEV_0            (0x0000)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV_1            (0x0100)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV_2            (0x0200)     /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV_3            (0x0300)     /* RTC Time Event: 3 (00:00 changed) */
#define RTCTEV__MIN         (0x0000)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV__HOUR        (0x0100)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV__0000        (0x0200)     /* RTC Time Event: 2 (00:00 changed) */
#define RTCTEV__1200        (0x0300)     /* RTC Time Event: 3 (12:00 changed) */

/* RTCCTL23 Control Bits */
#define RTCCALF1            (0x0200)     /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0            (0x0100)     /* RTC Calibration Frequency Bit 0 */
#define RTCCALS             (0x0080)     /* RTC Calibration Sign */
//#define Reserved          (0x0040)
#define RTCCAL5             (0x0020)     /* RTC Calibration Bit 5 */
#define RTCCAL4             (0x0010)     /* RTC Calibration Bit 4 */
#define RTCCAL3             (0x0008)     /* RTC Calibration Bit 3 */
#define RTCCAL2             (0x0004)     /* RTC Calibration Bit 2 */
#define RTCCAL1             (0x0002)     /* RTC Calibration Bit 1 */
#define RTCCAL0             (0x0001)     /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALS_L           (0x0080)     /* RTC Calibration Sign */
//#define Reserved          (0x0040)
#define RTCCAL5_L           (0x0020)     /* RTC Calibration Bit 5 */
#define RTCCAL4_L           (0x0010)     /* RTC Calibration Bit 4 */
#define RTCCAL3_L           (0x0008)     /* RTC Calibration Bit 3 */
#define RTCCAL2_L           (0x0004)     /* RTC Calibration Bit 2 */
#define RTCCAL1_L           (0x0002)     /* RTC Calibration Bit 1 */
#define RTCCAL0_L           (0x0001)     /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALF1_H          (0x0002)     /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0_H          (0x0001)     /* RTC Calibration Frequency Bit 0 */
//#define Reserved          (0x0040)

#define RTCCALF_0           (0x0000)     /* RTC Calibration Frequency: No Output */
#define RTCCALF_1           (0x0100)     /* RTC Calibration Frequency: 512 Hz */
#define RTCCALF_2           (0x0200)     /* RTC Calibration Frequency: 256 Hz */
#define RTCCALF_3           (0x0300)     /* RTC Calibration Frequency: 1 Hz */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT0IP2              (0x0010)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1              (0x0008)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0              (0x0004)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE             (0x0002)     /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG            (0x0001)     /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT0IP2_L            (0x0010)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1_L            (0x0008)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0_L            (0x0004)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE_L           (0x0002)     /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG_L          (0x0001)     /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)

#define RT0IP_0             (0x0000)     /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1             (0x0004)     /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2             (0x0008)     /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3             (0x000C)     /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4             (0x0010)     /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5             (0x0014)     /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6             (0x0018)     /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7             (0x001C)     /* RTC Prescale Timer 0 Interrupt Interval /256 */

#define RT0IP__2            (0x0000)     /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP__4            (0x0004)     /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP__8            (0x0008)     /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP__16           (0x000C)     /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP__32           (0x0010)     /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP__64           (0x0014)     /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP__128          (0x0018)     /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP__256          (0x001C)     /* RTC Prescale Timer 0 Interrupt Interval /256 */


/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT1IP2              (0x0010)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1              (0x0008)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0              (0x0004)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE             (0x0002)     /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG            (0x0001)     /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT1IP2_L            (0x0010)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1_L            (0x0008)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0_L            (0x0004)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE_L           (0x0002)     /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG_L          (0x0001)     /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)

#define RT1IP_0             (0x0000)     /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP_1             (0x0004)     /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP_2             (0x0008)     /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP_3             (0x000C)     /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP_4             (0x0010)     /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP_5             (0x0014)     /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP_6             (0x0018)     /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP_7             (0x001C)     /* RTC Prescale Timer 1 Interrupt Interval /256 */

#define RT1IP__2            (0x0000)     /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP__4            (0x0004)     /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP__8            (0x0008)     /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP__16           (0x000C)     /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP__32           (0x0010)     /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP__64           (0x0014)     /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP__128          (0x0018)     /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP__256          (0x001C)     /* RTC Prescale Timer 1 Interrupt Interval /256 */


/* RTC Definitions */
#define RTCIV_NONE           (0x0000)    /* No Interrupt pending */
#define RTCIV_RTCRDYIFG      (0x0002)    /* RTC ready: RTCRDYIFG */
#define RTCIV_RTCTEVIFG      (0x0004)    /* RTC interval timer: RTCTEVIFG */
#define RTCIV_RTCAIFG        (0x0006)    /* RTC user alarm: RTCAIFG */
#define RTCIV_RT0PSIFG       (0x0008)    /* RTC prescaler 0: RT0PSIFG */
#define RTCIV_RT1PSIFG       (0x000A)    /* RTC prescaler 1: RT1PSIFG */
#define RTCIV_RTCOFIFG       (0x000C)    /* RTC Oscillator fault */

/* Legacy Definitions */
#define RTC_NONE           (0x0000)      /* No Interrupt pending */
#define RTC_RTCRDYIFG      (0x0002)      /* RTC ready: RTCRDYIFG */
#define RTC_RTCTEVIFG      (0x0004)      /* RTC interval timer: RTCTEVIFG */
#define RTC_RTCAIFG        (0x0006)      /* RTC user alarm: RTCAIFG */
#define RTC_RT0PSIFG       (0x0008)      /* RTC prescaler 0: RT0PSIFG */
#define RTC_RT1PSIFG       (0x000A)      /* RTC prescaler 1: RT1PSIFG */
#define RTC_RTCOFIFG       (0x000C)      /* RTC Oscillator fault */

/************************************************************
* SFR - Special Function Register Module
************************************************************/
#define __MSP430_HAS_SFR__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SFR__ 0x0100
#define SFR_BASE __MSP430_BASEADDRESS_SFR__

#define SFRIE1_               0x0100    /* Interrupt Enable 1 */
#define SFRIE1_L (*(volatile uint8_t *)0x100)
#define SFRIE1 (*(volatile uint16_t *)0x100)
#define SFRIE1_H (*(volatile uint8_t *)0x101)
#define SFRIE1_L (*(volatile uint8_t *)0x100)
#define SFRIE1 (*(volatile uint16_t *)0x100)

/* SFRIE1 Control Bits */
#define WDTIE               (0x0001)  /* WDT Interrupt Enable */
#define OFIE                (0x0002)  /* Osc Fault Enable */
//#define Reserved          (0x0004)
#define VMAIE               (0x0008)  /* Vacant Memory Interrupt Enable */
#define NMIIE               (0x0010)  /* NMI Interrupt Enable */
#define JMBINIE             (0x0040)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE            (0x0080)  /* JTAG Mail Box output Interrupt Enable */

#define WDTIE_L             (0x0001)  /* WDT Interrupt Enable */
#define OFIE_L              (0x0002)  /* Osc Fault Enable */
//#define Reserved          (0x0004)
#define VMAIE_L             (0x0008)  /* Vacant Memory Interrupt Enable */
#define NMIIE_L             (0x0010)  /* NMI Interrupt Enable */
#define JMBINIE_L           (0x0040)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L          (0x0080)  /* JTAG Mail Box output Interrupt Enable */

//#define Reserved          (0x0004)

#define SFRIFG1_              0x0102    /* Interrupt Flag 1 */
#define SFRIFG1_L (*(volatile uint8_t *)0x102)
#define SFRIFG1 (*(volatile uint16_t *)0x102)
#define SFRIFG1_H (*(volatile uint8_t *)0x103)
#define SFRIFG1_L (*(volatile uint8_t *)0x102)
#define SFRIFG1 (*(volatile uint16_t *)0x102)
/* SFRIFG1 Control Bits */
#define WDTIFG              (0x0001)  /* WDT Interrupt Flag */
#define OFIFG               (0x0002)  /* Osc Fault Flag */
//#define Reserved          (0x0004)
#define VMAIFG              (0x0008)  /* Vacant Memory Interrupt Flag */
#define NMIIFG              (0x0010)  /* NMI Interrupt Flag */
//#define Reserved          (0x0020)
#define JMBINIFG            (0x0040)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG           (0x0080)  /* JTAG Mail Box output Interrupt Flag */

#define WDTIFG_L            (0x0001)  /* WDT Interrupt Flag */
#define OFIFG_L             (0x0002)  /* Osc Fault Flag */
//#define Reserved          (0x0004)
#define VMAIFG_L            (0x0008)  /* Vacant Memory Interrupt Flag */
#define NMIIFG_L            (0x0010)  /* NMI Interrupt Flag */
//#define Reserved          (0x0020)
#define JMBINIFG_L          (0x0040)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG_L         (0x0080)  /* JTAG Mail Box output Interrupt Flag */

//#define Reserved          (0x0004)
//#define Reserved          (0x0020)

#define SFRRPCR_              0x0104    /* RESET Pin Control Register */
#define SFRRPCR_L (*(volatile uint8_t *)0x104)
#define SFRRPCR (*(volatile uint16_t *)0x104)
#define SFRRPCR_H (*(volatile uint8_t *)0x105)
#define SFRRPCR_L (*(volatile uint8_t *)0x104)
#define SFRRPCR (*(volatile uint16_t *)0x104)
/* SFRRPCR Control Bits */
#define SYSNMI              (0x0001)  /* NMI select */
#define SYSNMIIES           (0x0002)  /* NMI edge select */
#define SYSRSTUP            (0x0004)  /* RESET Pin pull down/up select */
#define SYSRSTRE            (0x0008)  /* RESET Pin Resistor enable */

#define SYSNMI_L            (0x0001)  /* NMI select */
#define SYSNMIIES_L         (0x0002)  /* NMI edge select */
#define SYSRSTUP_L          (0x0004)  /* RESET Pin pull down/up select */
#define SYSRSTRE_L          (0x0008)  /* RESET Pin Resistor enable */


/************************************************************
* SYS - System Module
************************************************************/
#define __MSP430_HAS_SYS__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SYS__ 0x0180
#define SYS_BASE __MSP430_BASEADDRESS_SYS__

#define SYSCTL_               0x0180    /* System control */
#define SYSCTL_L (*(volatile uint8_t *)0x180)
#define SYSCTL (*(volatile uint16_t *)0x180)
#define SYSCTL_H (*(volatile uint8_t *)0x181)
#define SYSCTL_L (*(volatile uint8_t *)0x180)
#define SYSCTL (*(volatile uint16_t *)0x180)
#define SYSBSLC_              0x0182    /* Boot strap configuration area */
#define SYSBSLC_L (*(volatile uint8_t *)0x182)
#define SYSBSLC (*(volatile uint16_t *)0x182)
#define SYSBSLC_H (*(volatile uint8_t *)0x183)
#define SYSBSLC_L (*(volatile uint8_t *)0x182)
#define SYSBSLC (*(volatile uint16_t *)0x182)
#define SYSJMBC_              0x0186    /* JTAG mailbox control */
#define SYSJMBC_L (*(volatile uint8_t *)0x186)
#define SYSJMBC (*(volatile uint16_t *)0x186)
#define SYSJMBC_H (*(volatile uint8_t *)0x187)
#define SYSJMBC_L (*(volatile uint8_t *)0x186)
#define SYSJMBC (*(volatile uint16_t *)0x186)
#define SYSJMBI0_             0x0188    /* JTAG mailbox input 0 */
#define SYSJMBI0_L (*(volatile uint8_t *)0x188)
#define SYSJMBI0 (*(volatile uint16_t *)0x188)
#define SYSJMBI0_H (*(volatile uint8_t *)0x189)
#define SYSJMBI0_L (*(volatile uint8_t *)0x188)
#define SYSJMBI0 (*(volatile uint16_t *)0x188)
#define SYSJMBI1_             0x018A    /* JTAG mailbox input 1 */
#define SYSJMBI1_L (*(volatile uint8_t *)0x18a)
#define SYSJMBI1 (*(volatile uint16_t *)0x18a)
#define SYSJMBI1_H (*(volatile uint8_t *)0x18b)
#define SYSJMBI1_L (*(volatile uint8_t *)0x18a)
#define SYSJMBI1 (*(volatile uint16_t *)0x18a)
#define SYSJMBO0_             0x018C    /* JTAG mailbox output 0 */
#define SYSJMBO0_L (*(volatile uint8_t *)0x18c)
#define SYSJMBO0 (*(volatile uint16_t *)0x18c)
#define SYSJMBO0_H (*(volatile uint8_t *)0x18d)
#define SYSJMBO0_L (*(volatile uint8_t *)0x18c)
#define SYSJMBO0 (*(volatile uint16_t *)0x18c)
#define SYSJMBO1_             0x018E    /* JTAG mailbox output 1 */
#define SYSJMBO1_L (*(volatile uint8_t *)0x18e)
#define SYSJMBO1 (*(volatile uint16_t *)0x18e)
#define SYSJMBO1_H (*(volatile uint8_t *)0x18f)
#define SYSJMBO1_L (*(volatile uint8_t *)0x18e)
#define SYSJMBO1 (*(volatile uint16_t *)0x18e)

#define SYSBERRIV_            0x0198    /* Bus Error vector generator */
#define SYSBERRIV_L (*(volatile uint8_t *)0x198)
#define SYSBERRIV (*(volatile uint16_t *)0x198)
#define SYSBERRIV_H (*(volatile uint8_t *)0x199)
#define SYSBERRIV_L (*(volatile uint8_t *)0x198)
#define SYSBERRIV (*(volatile uint16_t *)0x198)
#define SYSUNIV_              0x019A    /* User NMI vector generator */
#define SYSUNIV_L (*(volatile uint8_t *)0x19a)
#define SYSUNIV (*(volatile uint16_t *)0x19a)
#define SYSUNIV_H (*(volatile uint8_t *)0x19b)
#define SYSUNIV_L (*(volatile uint8_t *)0x19a)
#define SYSUNIV (*(volatile uint16_t *)0x19a)
#define SYSSNIV_              0x019C    /* System NMI vector generator */
#define SYSSNIV_L (*(volatile uint8_t *)0x19c)
#define SYSSNIV (*(volatile uint16_t *)0x19c)
#define SYSSNIV_H (*(volatile uint8_t *)0x19d)
#define SYSSNIV_L (*(volatile uint8_t *)0x19c)
#define SYSSNIV (*(volatile uint16_t *)0x19c)
#define SYSRSTIV_             0x019E    /* Reset vector generator */
#define SYSRSTIV_L (*(volatile uint8_t *)0x19e)
#define SYSRSTIV (*(volatile uint16_t *)0x19e)
#define SYSRSTIV_H (*(volatile uint8_t *)0x19f)
#define SYSRSTIV_L (*(volatile uint8_t *)0x19e)
#define SYSRSTIV (*(volatile uint16_t *)0x19e)

/* SYSCTL Control Bits */
#define SYSRIVECT           (0x0001)  /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002)  /* SYS - Reserved */
#define SYSPMMPE            (0x0004)  /* SYS - PMM access protect */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
#define SYSBSLIND           (0x0010)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN          (0x0020)  /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSCTL Control Bits */
#define SYSRIVECT_L         (0x0001)  /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002)  /* SYS - Reserved */
#define SYSPMMPE_L          (0x0004)  /* SYS - PMM access protect */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
#define SYSBSLIND_L         (0x0010)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN_L        (0x0020)  /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSCTL Control Bits */
//#define RESERVED            (0x0002)  /* SYS - Reserved */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0         (0x0001)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1         (0x0002)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR             (0x0004)  /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
#define SYSBSLOFF           (0x4000)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE            (0x8000)  /* SYS - BSL Memory protection enabled */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0_L       (0x0001)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1_L       (0x0002)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR_L           (0x0004)  /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
#define SYSBSLOFF_H         (0x0040)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE_H          (0x0080)  /* SYS - BSL Memory protection enabled */

/* SYSJMBC Control Bits */
#define JMBIN0FG            (0x0001)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG            (0x0002)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG           (0x0004)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG           (0x0008)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE             (0x0010)  /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
#define JMBCLR0OFF          (0x0040)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF          (0x0080)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
#define JMBIN0FG_L          (0x0001)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG_L          (0x0002)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG_L         (0x0004)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG_L         (0x0008)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE_L           (0x0010)  /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
#define JMBCLR0OFF_L        (0x0040)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF_L        (0x0080)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSUNIV Definitions */
#define SYSUNIV_NONE       (0x0000)    /* No Interrupt pending */
#define SYSUNIV_NMIIFG     (0x0002)    /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG      (0x0004)    /* SYSUNIV : Osc. Fail - OFIFG */

/* SYSSNIV Definitions */
#define SYSSNIV_NONE       (0x0000)    /* No Interrupt pending */
#define SYSSNIV_DBDIFG     (0x0002)    /* SYSSNIV : FRAM Double bit Error */
#define SYSSNIV_ACCTIMIFG  (0x0004)    /* SYSSNIV : Access time error */
#define SYSSNIV_MPUSEGIIFG (0x0006)    /* SYSSNIV : MPUSEGIIFG violation */
#define SYSSNIV_MPUSEG1IFG (0x0008)    /* SYSSNIV : MPUSEG1IFG violation */
#define SYSSNIV_MPUSEG2IFG (0x000A)    /* SYSSNIV : MPUSEG2IFG violation */
#define SYSSNIV_MPUSEG3IFG (0x000C)    /* SYSSNIV : MPUSEG3IFG violation */
#define SYSSNIV_ACCVIFG    (0x000E)    /* SYSSNIV : Access violation */
#define SYSSNIV_VMAIFG     (0x0010)    /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG   (0x0012)    /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG  (0x0014)    /* SYSSNIV : JMBOUTIFG */
#define SYSSNIV_SBDIFG     (0x0016)    /* SYSSNIV : FRAM Single Bit error */


/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE      (0x0000)    /* No Interrupt pending */
#define SYSRSTIV_BOR       (0x0002)    /* SYSRSTIV : BOR */
#define SYSRSTIV_RSTNMI    (0x0004)    /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR     (0x0006)    /* SYSRSTIV : Do BOR */
#define SYSRSTIV_LPM5WU    (0x0008)    /* SYSRSTIV : Port LPM5 Wake Up */
#define SYSRSTIV_SECYV     (0x000A)    /* SYSRSTIV : Security violation */
#define SYSRSTIV_SVSLIFG   (0x000C)    /* SYSRSTIV : SVSLIFG */
#define SYSRSTIV_SVSHIFG   (0x000E)    /* SYSRSTIV : SVSHIFG */
#define SYSRSTIV_RES10     (0x0010)    /* SYSRSTIV : Reserved */
#define SYSRSTIV_RES12     (0x0012)    /* SYSRSTIV : Reserved */
#define SYSRSTIV_DOPOR     (0x0014)    /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO     (0x0016)    /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY    (0x0018)    /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_FRCTLPW   (0x001A)    /* SYSRSTIV : FRAM Key violation */
#define SYSRSTIV_DBDIFG    (0x001C)    /* SYSRSTIV : FRAM Double bit Error */
#define SYSRSTIV_PERF      (0x001E)    /* SYSRSTIV : peripheral/config area fetch */
#define SYSRSTIV_PMMKEY    (0x0020)    /* SYSRSTIV : PMMKEY violation */
#define SYSRSTIV_MPUKEY    (0x0022)    /* SYSRSTIV : MPUKEY violation */
#define SYSRSTIV_CSKEY     (0x0024)    /* SYSRSTIV : CSKEY violation */
#define SYSRSTIV_MPUSEGIIFG (0x0026)   /* SYSRSTIV : MPUSEGIIFG violation */
#define SYSRSTIV_MPUSEG1IFG (0x0028)   /* SYSRSTIV : MPUSEG1IFG violation */
#define SYSRSTIV_MPUSEG2IFG (0x002A)   /* SYSRSTIV : MPUSEG2IFG violation */
#define SYSRSTIV_MPUSEG3IFG (0x002C)   /* SYSRSTIV : MPUSEG3IFG violation */

/************************************************************
* Timer0_A3
************************************************************/
#define __MSP430_HAS_T0A3__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0A3__ 0x0340
#define TIMER_A0_BASE __MSP430_BASEADDRESS_T0A3__

#define TA0CTL_               0x0340    /* Timer0_A3 Control */
#define TA0CTL (*(volatile uint16_t *)0x340)
#define TA0CCTL0_             0x0342    /* Timer0_A3 Capture/Compare Control 0 */
#define TA0CCTL0 (*(volatile uint16_t *)0x342)
#define TA0CCTL1_             0x0344    /* Timer0_A3 Capture/Compare Control 1 */
#define TA0CCTL1 (*(volatile uint16_t *)0x344)
#define TA0CCTL2_             0x0346    /* Timer0_A3 Capture/Compare Control 2 */
#define TA0CCTL2 (*(volatile uint16_t *)0x346)
#define TA0R_                 0x0350    /* Timer0_A3 */
#define TA0R (*(volatile uint16_t *)0x350)
#define TA0CCR0_              0x0352    /* Timer0_A3 Capture/Compare 0 */
#define TA0CCR0 (*(volatile uint16_t *)0x352)
#define TA0CCR1_              0x0354    /* Timer0_A3 Capture/Compare 1 */
#define TA0CCR1 (*(volatile uint16_t *)0x354)
#define TA0CCR2_              0x0356    /* Timer0_A3 Capture/Compare 2 */
#define TA0CCR2 (*(volatile uint16_t *)0x356)
#define TA0IV_                0x036E    /* Timer0_A3 Interrupt Vector Word */
#define TA0IV (*(volatile uint16_t *)0x36e)
#define TA0EX0_               0x0360    /* Timer0_A3 Expansion Register 0 */
#define TA0EX0 (*(volatile uint16_t *)0x360)

/* TAxCTL Control Bits */
#define TASSEL1             (0x0200)  /* Timer A clock source select 1 */
#define TASSEL0             (0x0100)  /* Timer A clock source select 0 */
#define ID1                 (0x0080)  /* Timer A clock input divider 1 */
#define ID0                 (0x0040)  /* Timer A clock input divider 0 */
#define MC1                 (0x0020)  /* Timer A mode control 1 */
#define MC0                 (0x0010)  /* Timer A mode control 0 */
#define TACLR               (0x0004)  /* Timer A counter clear */
#define TAIE                (0x0002)  /* Timer A counter interrupt enable */
#define TAIFG               (0x0001)  /* Timer A counter interrupt flag */

#define MC_0                (0x0000)  /* Timer A mode control: 0 - Stop */
#define MC_1                (0x0010)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (0x0020)  /* Timer A mode control: 2 - Continuous up */
#define MC_3                (0x0030)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0x0000)  /* Timer A input divider: 0 - /1 */
#define ID_1                (0x0040)  /* Timer A input divider: 1 - /2 */
#define ID_2                (0x0080)  /* Timer A input divider: 2 - /4 */
#define ID_3                (0x00C0)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0x0000) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (0x0100) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (0x0200) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (0x0300) /* Timer A clock source select: 3 - INCLK */
#define MC__STOP            (0x0000)  /* Timer A mode control: 0 - Stop */
#define MC__UP              (0x0010)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC__CONTINUOUS      (0x0020)  /* Timer A mode control: 2 - Continuous up */
#define MC__CONTINOUS       (0x0020)  /* Legacy define */
#define MC__UPDOWN          (0x0030)  /* Timer A mode control: 3 - Up/Down */
#define ID__1               (0x0000)  /* Timer A input divider: 0 - /1 */
#define ID__2               (0x0040)  /* Timer A input divider: 1 - /2 */
#define ID__4               (0x0080)  /* Timer A input divider: 2 - /4 */
#define ID__8               (0x00C0)  /* Timer A input divider: 3 - /8 */
#define TASSEL__TACLK       (0x0000) /* Timer A clock source select: 0 - TACLK */
#define TASSEL__ACLK        (0x0100) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL__SMCLK       (0x0200) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL__INCLK       (0x0300) /* Timer A clock source select: 3 - INCLK */

/* TAxCCTLx Control Bits */
#define CM1                 (0x8000)  /* Capture mode 1 */
#define CM0                 (0x4000)  /* Capture mode 0 */
#define CCIS1               (0x2000)  /* Capture input select 1 */
#define CCIS0               (0x1000)  /* Capture input select 0 */
#define SCS                 (0x0800)  /* Capture sychronize */
#define SCCI                (0x0400)  /* Latched capture signal (read) */
#define CAP                 (0x0100)  /* Capture mode: 1 /Compare mode : 0 */
#define OUTMOD2             (0x0080)  /* Output mode 2 */
#define OUTMOD1             (0x0040)  /* Output mode 1 */
#define OUTMOD0             (0x0020)  /* Output mode 0 */
#define CCIE                (0x0010)  /* Capture/compare interrupt enable */
#define CCI                 (0x0008)  /* Capture input signal (read) */
#define OUT                 (0x0004)  /* PWM Output signal if output mode 0 */
#define COV                 (0x0002)  /* Capture/compare overflow flag */
#define CCIFG               (0x0001)  /* Capture/compare interrupt flag */

#define OUTMOD_0            (0x0000)  /* PWM output mode: 0 - output only */
#define OUTMOD_1            (0x0020)  /* PWM output mode: 1 - set */
#define OUTMOD_2            (0x0040)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3            (0x0060)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4            (0x0080)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5            (0x00A0)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6            (0x00C0)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7            (0x00E0)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0              (0x0000) /* Capture input select: 0 - CCIxA */
#define CCIS_1              (0x1000) /* Capture input select: 1 - CCIxB */
#define CCIS_2              (0x2000) /* Capture input select: 2 - GND */
#define CCIS_3              (0x3000) /* Capture input select: 3 - Vcc */
#define CM_0                (0x0000) /* Capture mode: 0 - disabled */
#define CM_1                (0x4000) /* Capture mode: 1 - pos. edge */
#define CM_2                (0x8000) /* Capture mode: 1 - neg. edge */
#define CM_3                (0xC000) /* Capture mode: 1 - both edges */


/* TAxEX0 Control Bits */
#define TAIDEX0             (0x0001)  /* Timer A Input divider expansion Bit: 0 */
#define TAIDEX1             (0x0002)  /* Timer A Input divider expansion Bit: 1 */
#define TAIDEX2             (0x0004)  /* Timer A Input divider expansion Bit: 2 */

#define TAIDEX_0            (0x0000) /* Timer A Input divider expansion : /1 */
#define TAIDEX_1            (0x0001) /* Timer A Input divider expansion : /2 */
#define TAIDEX_2            (0x0002) /* Timer A Input divider expansion : /3 */
#define TAIDEX_3            (0x0003) /* Timer A Input divider expansion : /4 */
#define TAIDEX_4            (0x0004) /* Timer A Input divider expansion : /5 */
#define TAIDEX_5            (0x0005) /* Timer A Input divider expansion : /6 */
#define TAIDEX_6            (0x0006) /* Timer A Input divider expansion : /7 */
#define TAIDEX_7            (0x0007) /* Timer A Input divider expansion : /8 */

/* T0A3IV Definitions */
#define TA0IV_NONE          (0x0000)    /* No Interrupt pending */
#define TA0IV_TA0CCR1       (0x0002)    /* TA0CCR1_CCIFG */
#define TA0IV_TA0CCR2       (0x0004)    /* TA0CCR2_CCIFG */
#define TA0IV_3             (0x0006)    /* Reserved */
#define TA0IV_4             (0x0008)    /* Reserved */
#define TA0IV_5             (0x000A)    /* Reserved */
#define TA0IV_6             (0x000C)    /* Reserved */
#define TA0IV_TA0IFG        (0x000E)    /* TA0IFG */

/************************************************************
* Timer1_A3
************************************************************/
#define __MSP430_HAS_T1A3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T1A3__ 0x0380
#define TIMER_A1_BASE __MSP430_BASEADDRESS_T1A3__

#define TA1CTL_               0x0380    /* Timer1_A3 Control */
#define TA1CTL (*(volatile uint16_t *)0x380)
#define TA1CCTL0_             0x0382    /* Timer1_A3 Capture/Compare Control 0 */
#define TA1CCTL0 (*(volatile uint16_t *)0x382)
#define TA1CCTL1_             0x0384    /* Timer1_A3 Capture/Compare Control 1 */
#define TA1CCTL1 (*(volatile uint16_t *)0x384)
#define TA1CCTL2_             0x0386    /* Timer1_A3 Capture/Compare Control 2 */
#define TA1CCTL2 (*(volatile uint16_t *)0x386)
#define TA1R_                 0x0390    /* Timer1_A3 */
#define TA1R (*(volatile uint16_t *)0x390)
#define TA1CCR0_              0x0392    /* Timer1_A3 Capture/Compare 0 */
#define TA1CCR0 (*(volatile uint16_t *)0x392)
#define TA1CCR1_              0x0394    /* Timer1_A3 Capture/Compare 1 */
#define TA1CCR1 (*(volatile uint16_t *)0x394)
#define TA1CCR2_              0x0396    /* Timer1_A3 Capture/Compare 2 */
#define TA1CCR2 (*(volatile uint16_t *)0x396)
#define TA1IV_                0x03AE    /* Timer1_A3 Interrupt Vector Word */
#define TA1IV (*(volatile uint16_t *)0x3ae)
#define TA1EX0_               0x03A0    /* Timer1_A3 Expansion Register 0 */
#define TA1EX0 (*(volatile uint16_t *)0x3a0)

/* Bits are already defined within the Timer0_Ax */

/* TA1IV Definitions */
#define TA1IV_NONE          (0x0000)    /* No Interrupt pending */
#define TA1IV_TA1CCR1      (0x0002)    /* TA1CCR1_CCIFG */
#define TA1IV_TA1CCR2      (0x0004)    /* TA1CCR2_CCIFG */
#define TA1IV_3             (0x0006)    /* Reserved */
#define TA1IV_4             (0x0008)    /* Reserved */
#define TA1IV_5             (0x000A)    /* Reserved */
#define TA1IV_6             (0x000C)    /* Reserved */
#define TA1IV_TA1IFG       (0x000E)    /* TA1IFG */

/************************************************************
* Timer0_B3
************************************************************/
#define __MSP430_HAS_T0B3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0B3__ 0x03C0
#define TIMER_B0_BASE __MSP430_BASEADDRESS_T0B3__

#define TB0CTL_               0x03C0    /* Timer0_B7 Control */
#define TB0CTL (*(volatile uint16_t *)0x3c0)
#define TB0CCTL0_             0x03C2    /* Timer0_B7 Capture/Compare Control 0 */
#define TB0CCTL0 (*(volatile uint16_t *)0x3c2)
#define TB0CCTL1_             0x03C4    /* Timer0_B7 Capture/Compare Control 1 */
#define TB0CCTL1 (*(volatile uint16_t *)0x3c4)
#define TB0CCTL2_             0x03C6    /* Timer0_B7 Capture/Compare Control 2 */
#define TB0CCTL2 (*(volatile uint16_t *)0x3c6)
#define TB0R_                 0x03D0    /* Timer0_B7 */
#define TB0R (*(volatile uint16_t *)0x3d0)
#define TB0CCR0_              0x03D2    /* Timer0_B7 Capture/Compare 0 */
#define TB0CCR0 (*(volatile uint16_t *)0x3d2)
#define TB0CCR1_              0x03D4    /* Timer0_B7 Capture/Compare 1 */
#define TB0CCR1 (*(volatile uint16_t *)0x3d4)
#define TB0CCR2_              0x03D6    /* Timer0_B7 Capture/Compare 2 */
#define TB0CCR2 (*(volatile uint16_t *)0x3d6)
#define TB0EX0_               0x03E0    /* Timer0_B7 Expansion Register 0 */
#define TB0EX0 (*(volatile uint16_t *)0x3e0)
#define TB0IV_                0x03EE    /* Timer0_B7 Interrupt Vector Word */
#define TB0IV (*(volatile uint16_t *)0x3ee)

/* Legacy Type Definitions for TimerB */
#define TBCTL                TB0CTL    /* Timer0_B7 Control */
#define TBCCTL0              TB0CCTL0  /* Timer0_B7 Capture/Compare Control 0 */
#define TBCCTL1              TB0CCTL1  /* Timer0_B7 Capture/Compare Control 1 */
#define TBCCTL2              TB0CCTL2  /* Timer0_B7 Capture/Compare Control 2 */
#define TBR                  TB0R      /* Timer0_B7 */
#define TBCCR0               TB0CCR0   /* Timer0_B7 Capture/Compare 0 */
#define TBCCR1               TB0CCR1   /* Timer0_B7 Capture/Compare 1 */
#define TBCCR2               TB0CCR2   /* Timer0_B7 Capture/Compare 2 */
#define TBEX0                TB0EX0    /* Timer0_B7 Expansion Register 0 */
#define TBIV                 TB0IV     /* Timer0_B7 Interrupt Vector Word */
#define TIMERB1_VECTOR       TIMER0_B1_VECTOR /* Timer0_B7 CC1-6, TB */
#define TIMERB0_VECTOR       TIMER0_B0_VECTOR /* Timer0_B7 CC0 */


/* TBxCTL Control Bits */
#define TBCLGRP1            (0x4000)  /* Timer0_B7 Compare latch load group 1 */
#define TBCLGRP0            (0x2000)  /* Timer0_B7 Compare latch load group 0 */
#define CNTL1               (0x1000)  /* Counter lenght 1 */
#define CNTL0               (0x0800)  /* Counter lenght 0 */
#define TBSSEL1             (0x0200)  /* Clock source 1 */
#define TBSSEL0             (0x0100)  /* Clock source 0 */
#define TBCLR               (0x0004)  /* Timer0_B7 counter clear */
#define TBIE                (0x0002)  /* Timer0_B7 interrupt enable */
#define TBIFG               (0x0001)  /* Timer0_B7 interrupt flag */

#define SHR1                (0x4000)  /* Timer0_B7 Compare latch load group 1 */
#define SHR0                (0x2000)  /* Timer0_B7 Compare latch load group 0 */

#define TBSSEL_0            (0x0000)  /* Clock Source: TBCLK */
#define TBSSEL_1            (0x0100)  /* Clock Source: ACLK  */
#define TBSSEL_2            (0x0200)  /* Clock Source: SMCLK */
#define TBSSEL_3            (0x0300)  /* Clock Source: INCLK */
#define CNTL_0              (0x0000)  /* Counter lenght: 16 bit */
#define CNTL_1              (0x0800)  /* Counter lenght: 12 bit */
#define CNTL_2              (0x1000)  /* Counter lenght: 10 bit */
#define CNTL_3              (0x1800)  /* Counter lenght:  8 bit */
#define SHR_0               (0x0000)  /* Timer0_B7 Group: 0 - individually */
#define SHR_1               (0x2000)  /* Timer0_B7 Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2               (0x4000)  /* Timer0_B7 Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3               (0x6000)  /* Timer0_B7 Group: 3 - 1 group (all) */
#define TBCLGRP_0           (0x0000)  /* Timer0_B7 Group: 0 - individually */
#define TBCLGRP_1           (0x2000)  /* Timer0_B7 Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2           (0x4000)  /* Timer0_B7 Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3           (0x6000)  /* Timer0_B7 Group: 3 - 1 group (all) */
#define TBSSEL__TBCLK       (0x0000) /* Timer0_B7 clock source select: 0 - TBCLK */
#define TBSSEL__TACLK       (0x0000) /* Timer0_B7 clock source select: 0 - TBCLK (legacy) */
#define TBSSEL__ACLK        (0x0100) /* Timer0_B7 clock source select: 1 - ACLK  */
#define TBSSEL__SMCLK       (0x0200) /* Timer0_B7 clock source select: 2 - SMCLK */
#define TBSSEL__INCLK       (0x0300) /* Timer0_B7 clock source select: 3 - INCLK */
#define CNTL__16            (0x0000)  /* Counter lenght: 16 bit */
#define CNTL__12            (0x0800)  /* Counter lenght: 12 bit */
#define CNTL__10            (0x1000)  /* Counter lenght: 10 bit */
#define CNTL__8             (0x1800)  /* Counter lenght:  8 bit */

/* Additional Timer B Control Register bits are defined in Timer A */
/* TBxCCTLx Control Bits */
#define CLLD1               (0x0400)  /* Compare latch load source 1 */
#define CLLD0               (0x0200)  /* Compare latch load source 0 */

#define SLSHR1              (0x0400)  /* Compare latch load source 1 */
#define SLSHR0              (0x0200)  /* Compare latch load source 0 */

#define SLSHR_0             (0x0000) /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1             (0x0200) /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2             (0x0400) /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3             (0x0600) /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0              (0x0000) /* Compare latch load sourec : 0 - immediate */
#define CLLD_1              (0x0200) /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2              (0x0400) /* Compare latch load sourec : 2 - up/down */
#define CLLD_3              (0x0600) /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

/* TBxEX0 Control Bits */
#define TBIDEX0             (0x0001)   /* Timer0_B7 Input divider expansion Bit: 0 */
#define TBIDEX1             (0x0002)   /* Timer0_B7 Input divider expansion Bit: 1 */
#define TBIDEX2             (0x0004)   /* Timer0_B7 Input divider expansion Bit: 2 */

#define TBIDEX_0            (0x0000) /* Timer0_B7 Input divider expansion : /1 */
#define TBIDEX_1            (0x0001) /* Timer0_B7 Input divider expansion : /2 */
#define TBIDEX_2            (0x0002) /* Timer0_B7 Input divider expansion : /3 */
#define TBIDEX_3            (0x0003) /* Timer0_B7 Input divider expansion : /4 */
#define TBIDEX_4            (0x0004) /* Timer0_B7 Input divider expansion : /5 */
#define TBIDEX_5            (0x0005) /* Timer0_B7 Input divider expansion : /6 */
#define TBIDEX_6            (0x0006) /* Timer0_B7 Input divider expansion : /7 */
#define TBIDEX_7            (0x0007) /* Timer0_B7 Input divider expansion : /8 */
#define TBIDEX__1           (0x0000) /* Timer0_B7 Input divider expansion : /1 */
#define TBIDEX__2           (0x0001) /* Timer0_B7 Input divider expansion : /2 */
#define TBIDEX__3           (0x0002) /* Timer0_B7 Input divider expansion : /3 */
#define TBIDEX__4           (0x0003) /* Timer0_B7 Input divider expansion : /4 */
#define TBIDEX__5           (0x0004) /* Timer0_B7 Input divider expansion : /5 */
#define TBIDEX__6           (0x0005) /* Timer0_B7 Input divider expansion : /6 */
#define TBIDEX__7           (0x0006) /* Timer0_B7 Input divider expansion : /7 */
#define TBIDEX__8           (0x0007) /* Timer0_B7 Input divider expansion : /8 */

/* TB0IV Definitions */
#define TB0IV_NONE          (0x0000)    /* No Interrupt pending */
#define TB0IV_TB0CCR1       (0x0002)    /* TB0CCR1_CCIFG */
#define TB0IV_TB0CCR2       (0x0004)    /* TB0CCR2_CCIFG */
#define TB0IV_3             (0x0006)    /* Reserved */
#define TB0IV_4             (0x0008)    /* Reserved */
#define TB0IV_5             (0x000A)    /* Reserved */
#define TB0IV_6             (0x000C)    /* Reserved */
#define TB0IV_TB0IFG        (0x000E)    /* TB0IFG */


/************************************************************
* Timer1_B3
************************************************************/
#define __MSP430_HAS_T1B3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T1B3__ 0x0400
#define TIMER_B1_BASE __MSP430_BASEADDRESS_T1B3__

#define TB1CTL_               0x0400    /* Timer1_B3 Control */
#define TB1CTL (*(volatile uint16_t *)0x400)
#define TB1CCTL0_             0x0402    /* Timer1_B3 Capture/Compare Control 0 */
#define TB1CCTL0 (*(volatile uint16_t *)0x402)
#define TB1CCTL1_             0x0404    /* Timer1_B3 Capture/Compare Control 1 */
#define TB1CCTL1 (*(volatile uint16_t *)0x404)
#define TB1CCTL2_             0x0406    /* Timer1_B3 Capture/Compare Control 2 */
#define TB1CCTL2 (*(volatile uint16_t *)0x406)
#define TB1R_                 0x0410    /* Timer1_B3 */
#define TB1R (*(volatile uint16_t *)0x410)
#define TB1CCR0_              0x0412    /* Timer1_B3 Capture/Compare 0 */
#define TB1CCR0 (*(volatile uint16_t *)0x412)
#define TB1CCR1_              0x0414    /* Timer1_B3 Capture/Compare 1 */
#define TB1CCR1 (*(volatile uint16_t *)0x414)
#define TB1CCR2_              0x0416    /* Timer1_B3 Capture/Compare 2 */
#define TB1CCR2 (*(volatile uint16_t *)0x416)
#define TB1IV_                0x042E    /* Timer1_B3 Interrupt Vector Word */
#define TB1IV (*(volatile uint16_t *)0x42e)
#define TB1EX0_               0x0420    /* Timer1_B3 Expansion Register 0 */
#define TB1EX0 (*(volatile uint16_t *)0x420)

/* Bits are already defined within the Timer0_Ax */

/* TB1IV Definitions */
#define TB1IV_NONE          (0x0000)    /* No Interrupt pending */
#define TB1IV_TB1CCR1      (0x0002)    /* TB1CCR1_CCIFG */
#define TB1IV_TB1CCR2      (0x0004)    /* TB1CCR2_CCIFG */
#define TB1IV_3             (0x0006)    /* Reserved */
#define TB1IV_4             (0x0008)    /* Reserved */
#define TB1IV_5             (0x000A)    /* Reserved */
#define TB1IV_6             (0x000C)    /* Reserved */
#define TB1IV_TB1IFG       (0x000E)    /* TB1IFG */

/************************************************************
* Timer2_B3
************************************************************/
#define __MSP430_HAS_T2B3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T2B3__ 0x0440
#define TIMER_B2_BASE __MSP430_BASEADDRESS_T2B3__

#define TB2CTL_               0x0440    /* Timer2_B3 Control */
#define TB2CTL (*(volatile uint16_t *)0x440)
#define TB2CCTL0_             0x0442    /* Timer2_B3 Capture/Compare Control 0 */
#define TB2CCTL0 (*(volatile uint16_t *)0x442)
#define TB2CCTL1_             0x0444    /* Timer2_B3 Capture/Compare Control 1 */
#define TB2CCTL1 (*(volatile uint16_t *)0x444)
#define TB2CCTL2_             0x0446    /* Timer2_B3 Capture/Compare Control 2 */
#define TB2CCTL2 (*(volatile uint16_t *)0x446)
#define TB2R_                 0x0450    /* Timer2_B3 */
#define TB2R (*(volatile uint16_t *)0x450)
#define TB2CCR0_              0x0452    /* Timer2_B3 Capture/Compare 0 */
#define TB2CCR0 (*(volatile uint16_t *)0x452)
#define TB2CCR1_              0x0454    /* Timer2_B3 Capture/Compare 1 */
#define TB2CCR1 (*(volatile uint16_t *)0x454)
#define TB2CCR2_              0x0456    /* Timer2_B3 Capture/Compare 2 */
#define TB2CCR2 (*(volatile uint16_t *)0x456)
#define TB2IV_                0x046E    /* Timer2_B3 Interrupt Vector Word */
#define TB2IV (*(volatile uint16_t *)0x46e)
#define TB2EX0_               0x0460    /* Timer2_B3 Expansion Register 0 */
#define TB2EX0 (*(volatile uint16_t *)0x460)

/* Bits are already defined within the Timer0_Ax */

/* TB2IV Definitions */
#define TB2IV_NONE          (0x0000)    /* No Interrupt pending */
#define TB2IV_TB2CCR1      (0x0002)    /* TB2CCR1_CCIFG */
#define TB2IV_TB2CCR2      (0x0004)    /* TB2CCR2_CCIFG */
#define TB2IV_3             (0x0006)    /* Reserved */
#define TB2IV_4             (0x0008)    /* Reserved */
#define TB2IV_5             (0x000A)    /* Reserved */
#define TB2IV_6             (0x000C)    /* Reserved */
#define TB2IV_TB2IFG       (0x000E)    /* TB2IFG */

/************************************************************
* USCI A0
************************************************************/
#define __MSP430_HAS_EUSCI_A0__      /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_EUSCI_A0__ 0x05C0
#define EUSCI_A0_BASE __MSP430_BASEADDRESS_EUSCI_A0__

#define UCA0CTLW0_            0x05C0    /* USCI A0 Control Word Register 0 */
#define UCA0CTLW0_L (*(volatile uint8_t *)0x5c0)
#define UCA0CTLW0 (*(volatile uint16_t *)0x5c0)
#define UCA0CTLW0_H (*(volatile uint8_t *)0x5c1)
#define UCA0CTLW0_L (*(volatile uint8_t *)0x5c0)
#define UCA0CTLW0 (*(volatile uint16_t *)0x5c0)
#define UCA0CTL1            UCA0CTLW0_L  /* USCI A0 Control Register 1 */
#define UCA0CTL0            UCA0CTLW0_H  /* USCI A0 Control Register 0 */
#define UCA0CTLW1_            0x05C2    /* USCI A0 Control Word Register 1 */
#define UCA0CTLW1_L (*(volatile uint8_t *)0x5c2)
#define UCA0CTLW1 (*(volatile uint16_t *)0x5c2)
#define UCA0CTLW1_H (*(volatile uint8_t *)0x5c3)
#define UCA0CTLW1_L (*(volatile uint8_t *)0x5c2)
#define UCA0CTLW1 (*(volatile uint16_t *)0x5c2)
#define UCA0BRW_              0x05C6    /* USCI A0 Baud Word Rate 0 */
#define UCA0BRW_L (*(volatile uint8_t *)0x5c6)
#define UCA0BRW (*(volatile uint16_t *)0x5c6)
#define UCA0BRW_H (*(volatile uint8_t *)0x5c7)
#define UCA0BRW_L (*(volatile uint8_t *)0x5c6)
#define UCA0BRW (*(volatile uint16_t *)0x5c6)
#define UCA0BR0             UCA0BRW_L /* USCI A0 Baud Rate 0 */
#define UCA0BR1             UCA0BRW_H /* USCI A0 Baud Rate 1 */
#define UCA0MCTLW_            0x05C8    /* USCI A0 Modulation Control */
#define UCA0MCTLW_L (*(volatile uint8_t *)0x5c8)
#define UCA0MCTLW (*(volatile uint16_t *)0x5c8)
#define UCA0MCTLW_H (*(volatile uint8_t *)0x5c9)
#define UCA0MCTLW_L (*(volatile uint8_t *)0x5c8)
#define UCA0MCTLW (*(volatile uint16_t *)0x5c8)
#define UCA0STATW_            0x05CA    /* USCI A0 Status Register */
#define UCA0STATW (*(volatile uint8_t *)0x5ca)
#define UCA0RXBUF_            0x05CC    /* USCI A0 Receive Buffer */
#define UCA0RXBUF_L (*(volatile uint8_t *)0x5cc)
#define UCA0RXBUF (*(volatile uint16_t *)0x5cc)
#define UCA0RXBUF_H (*(volatile uint8_t *)0x5cd)
#define UCA0RXBUF_L (*(volatile uint8_t *)0x5cc)
#define UCA0RXBUF (*(volatile uint16_t *)0x5cc)
#define UCA0TXBUF_            0x05CE    /* USCI A0 Transmit Buffer */
#define UCA0TXBUF_L (*(volatile uint8_t *)0x5ce)
#define UCA0TXBUF (*(volatile uint16_t *)0x5ce)
#define UCA0TXBUF_H (*(volatile uint8_t *)0x5cf)
#define UCA0TXBUF_L (*(volatile uint8_t *)0x5ce)
#define UCA0TXBUF (*(volatile uint16_t *)0x5ce)
#define UCA0ABCTL_            0x05D0    /* USCI A0 LIN Control */
#define UCA0ABCTL (*(volatile uint8_t *)0x5d0)
#define UCA0IRCTL_            0x05D2    /* USCI A0 IrDA Transmit Control */
#define UCA0IRCTL_L (*(volatile uint8_t *)0x5d2)
#define UCA0IRCTL (*(volatile uint16_t *)0x5d2)
#define UCA0IRCTL_H (*(volatile uint8_t *)0x5d3)
#define UCA0IRCTL_L (*(volatile uint8_t *)0x5d2)
#define UCA0IRCTL (*(volatile uint16_t *)0x5d2)
#define UCA0IRTCTL          UCA0IRCTL_L  /* USCI A0 IrDA Transmit Control */
#define UCA0IRRCTL          UCA0IRCTL_H  /* USCI A0 IrDA Receive Control */
#define UCA0IE_               0x05DA    /* USCI A0 Interrupt Enable Register */
#define UCA0IE_L (*(volatile uint8_t *)0x5da)
#define UCA0IE (*(volatile uint16_t *)0x5da)
#define UCA0IE_H (*(volatile uint8_t *)0x5db)
#define UCA0IE_L (*(volatile uint8_t *)0x5da)
#define UCA0IE (*(volatile uint16_t *)0x5da)
#define UCA0IFG_              0x05DC    /* USCI A0 Interrupt Flags Register */
#define UCA0IFG_L (*(volatile uint8_t *)0x5dc)
#define UCA0IFG (*(volatile uint16_t *)0x5dc)
#define UCA0IFG_H (*(volatile uint8_t *)0x5dd)
#define UCA0IFG_L (*(volatile uint8_t *)0x5dc)
#define UCA0IFG (*(volatile uint16_t *)0x5dc)
#define UCA0IV_               0x05DE    /* USCI A0 Interrupt Vector Register */
#define UCA0IV (*(volatile uint16_t *)0x5de)


/************************************************************
* USCI B0
************************************************************/
#define __MSP430_HAS_EUSCI_B0__       /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_EUSCI_B0__ 0x0640
#define EUSCI_B0_BASE __MSP430_BASEADDRESS_EUSCI_B0__


#define UCB0CTLW0_            0x0640    /* USCI B0 Control Word Register 0 */
#define UCB0CTLW0_L (*(volatile uint8_t *)0x640)
#define UCB0CTLW0 (*(volatile uint16_t *)0x640)
#define UCB0CTLW0_H (*(volatile uint8_t *)0x641)
#define UCB0CTLW0_L (*(volatile uint8_t *)0x640)
#define UCB0CTLW0 (*(volatile uint16_t *)0x640)
#define UCB0CTL1            UCB0CTLW0_L  /* USCI B0 Control Register 1 */
#define UCB0CTL0            UCB0CTLW0_H  /* USCI B0 Control Register 0 */
#define UCB0CTLW1_            0x0642    /* USCI B0 Control Word Register 1 */
#define UCB0CTLW1_L (*(volatile uint8_t *)0x642)
#define UCB0CTLW1 (*(volatile uint16_t *)0x642)
#define UCB0CTLW1_H (*(volatile uint8_t *)0x643)
#define UCB0CTLW1_L (*(volatile uint8_t *)0x642)
#define UCB0CTLW1 (*(volatile uint16_t *)0x642)
#define UCB0BRW_              0x0646    /* USCI B0 Baud Word Rate 0 */
#define UCB0BRW_L (*(volatile uint8_t *)0x646)
#define UCB0BRW (*(volatile uint16_t *)0x646)
#define UCB0BRW_H (*(volatile uint8_t *)0x647)
#define UCB0BRW_L (*(volatile uint8_t *)0x646)
#define UCB0BRW (*(volatile uint16_t *)0x646)
#define UCB0BR0             UCB0BRW_L /* USCI B0 Baud Rate 0 */
#define UCB0BR1             UCB0BRW_H /* USCI B0 Baud Rate 1 */
#define UCB0STATW_            0x0648    /* USCI B0 Status Word Register */
#define UCB0STATW_L (*(volatile uint8_t *)0x648)
#define UCB0STATW (*(volatile uint16_t *)0x648)
#define UCB0STATW_H (*(volatile uint8_t *)0x649)
#define UCB0STATW_L (*(volatile uint8_t *)0x648)
#define UCB0STATW (*(volatile uint16_t *)0x648)
#define UCB0STAT            UCB0STATW_L /* USCI B0 Status Register */
#define UCB0BCNT            UCB0STATW_H /* USCI B0 Byte Counter Register */
#define UCB0TBCNT_            0x064A    /* USCI B0 Byte Counter Threshold Register */
#define UCB0TBCNT_L (*(volatile uint8_t *)0x64a)
#define UCB0TBCNT (*(volatile uint16_t *)0x64a)
#define UCB0TBCNT_H (*(volatile uint8_t *)0x64b)
#define UCB0TBCNT_L (*(volatile uint8_t *)0x64a)
#define UCB0TBCNT (*(volatile uint16_t *)0x64a)
#define UCB0RXBUF_            0x064C    /* USCI B0 Receive Buffer */
#define UCB0RXBUF_L (*(volatile uint8_t *)0x64c)
#define UCB0RXBUF (*(volatile uint16_t *)0x64c)
#define UCB0RXBUF_H (*(volatile uint8_t *)0x64d)
#define UCB0RXBUF_L (*(volatile uint8_t *)0x64c)
#define UCB0RXBUF (*(volatile uint16_t *)0x64c)
#define UCB0TXBUF_            0x064E    /* USCI B0 Transmit Buffer */
#define UCB0TXBUF_L (*(volatile uint8_t *)0x64e)
#define UCB0TXBUF (*(volatile uint16_t *)0x64e)
#define UCB0TXBUF_H (*(volatile uint8_t *)0x64f)
#define UCB0TXBUF_L (*(volatile uint8_t *)0x64e)
#define UCB0TXBUF (*(volatile uint16_t *)0x64e)
#define UCB0I2COA0_           0x0654    /* USCI B0 I2C Own Address 0 */
#define UCB0I2COA0_L (*(volatile uint8_t *)0x654)
#define UCB0I2COA0 (*(volatile uint16_t *)0x654)
#define UCB0I2COA0_H (*(volatile uint8_t *)0x655)
#define UCB0I2COA0_L (*(volatile uint8_t *)0x654)
#define UCB0I2COA0 (*(volatile uint16_t *)0x654)
#define UCB0I2COA1_           0x0656    /* USCI B0 I2C Own Address 1 */
#define UCB0I2COA1_L (*(volatile uint8_t *)0x656)
#define UCB0I2COA1 (*(volatile uint16_t *)0x656)
#define UCB0I2COA1_H (*(volatile uint8_t *)0x657)
#define UCB0I2COA1_L (*(volatile uint8_t *)0x656)
#define UCB0I2COA1 (*(volatile uint16_t *)0x656)
#define UCB0I2COA2_           0x0658    /* USCI B0 I2C Own Address 2 */
#define UCB0I2COA2_L (*(volatile uint8_t *)0x658)
#define UCB0I2COA2 (*(volatile uint16_t *)0x658)
#define UCB0I2COA2_H (*(volatile uint8_t *)0x659)
#define UCB0I2COA2_L (*(volatile uint8_t *)0x658)
#define UCB0I2COA2 (*(volatile uint16_t *)0x658)
#define UCB0I2COA3_           0x065A    /* USCI B0 I2C Own Address 3 */
#define UCB0I2COA3_L (*(volatile uint8_t *)0x65a)
#define UCB0I2COA3 (*(volatile uint16_t *)0x65a)
#define UCB0I2COA3_H (*(volatile uint8_t *)0x65b)
#define UCB0I2COA3_L (*(volatile uint8_t *)0x65a)
#define UCB0I2COA3 (*(volatile uint16_t *)0x65a)
#define UCB0ADDRX_            0x065C    /* USCI B0 Received Address Register */
#define UCB0ADDRX_L (*(volatile uint8_t *)0x65c)
#define UCB0ADDRX (*(volatile uint16_t *)0x65c)
#define UCB0ADDRX_H (*(volatile uint8_t *)0x65d)
#define UCB0ADDRX_L (*(volatile uint8_t *)0x65c)
#define UCB0ADDRX (*(volatile uint16_t *)0x65c)
#define UCB0ADDMASK_          0x065E    /* USCI B0 Address Mask Register */
#define UCB0ADDMASK_L (*(volatile uint8_t *)0x65e)
#define UCB0ADDMASK (*(volatile uint16_t *)0x65e)
#define UCB0ADDMASK_H (*(volatile uint8_t *)0x65f)
#define UCB0ADDMASK_L (*(volatile uint8_t *)0x65e)
#define UCB0ADDMASK (*(volatile uint16_t *)0x65e)
#define UCB0I2CSA_            0x0660    /* USCI B0 I2C Slave Address */
#define UCB0I2CSA_L (*(volatile uint8_t *)0x660)
#define UCB0I2CSA (*(volatile uint16_t *)0x660)
#define UCB0I2CSA_H (*(volatile uint8_t *)0x661)
#define UCB0I2CSA_L (*(volatile uint8_t *)0x660)
#define UCB0I2CSA (*(volatile uint16_t *)0x660)
#define UCB0IE_               0x066A    /* USCI B0 Interrupt Enable Register */
#define UCB0IE_L (*(volatile uint8_t *)0x66a)
#define UCB0IE (*(volatile uint16_t *)0x66a)
#define UCB0IE_H (*(volatile uint8_t *)0x66b)
#define UCB0IE_L (*(volatile uint8_t *)0x66a)
#define UCB0IE (*(volatile uint16_t *)0x66a)
#define UCB0IFG_              0x066C    /* USCI B0 Interrupt Flags Register */
#define UCB0IFG_L (*(volatile uint8_t *)0x66c)
#define UCB0IFG (*(volatile uint16_t *)0x66c)
#define UCB0IFG_H (*(volatile uint8_t *)0x66d)
#define UCB0IFG_L (*(volatile uint8_t *)0x66c)
#define UCB0IFG (*(volatile uint16_t *)0x66c)
#define UCB0IV_               0x066E    /* USCI B0 Interrupt Vector Register */
#define UCB0IV (*(volatile uint16_t *)0x66e)


// UCAxCTLW0 UART-Mode Control Bits
#define UCPEN               (0x8000)    /* Async. Mode: Parity enable */
#define UCPAR               (0x4000)    /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB               (0x2000)    /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT              (0x1000)    /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB               (0x0800)    /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1             (0x0400)    /* Async. Mode: USCI Mode 1 */
#define UCMODE0             (0x0200)    /* Async. Mode: USCI Mode 0 */
#define UCSYNC              (0x0100)    /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
#define UCSSEL1             (0x0080)    /* USCI 0 Clock Source Select 1 */
#define UCSSEL0             (0x0040)    /* USCI 0 Clock Source Select 0 */
#define UCRXEIE             (0x0020)    /* RX Error interrupt enable */
#define UCBRKIE             (0x0010)    /* Break interrupt enable */
#define UCDORM              (0x0008)    /* Dormant (Sleep) Mode */
#define UCTXADDR            (0x0004)    /* Send next Data as Address */
#define UCTXBRK             (0x0002)    /* Send next Data as Break */
#define UCSWRST             (0x0001)    /* USCI Software Reset */

// UCAxCTLW0 UART-Mode Control Bits
#define UCSSEL1_L           (0x0080)    /* USCI 0 Clock Source Select 1 */
#define UCSSEL0_L           (0x0040)    /* USCI 0 Clock Source Select 0 */
#define UCRXEIE_L           (0x0020)    /* RX Error interrupt enable */
#define UCBRKIE_L           (0x0010)    /* Break interrupt enable */
#define UCDORM_L            (0x0008)    /* Dormant (Sleep) Mode */
#define UCTXADDR_L          (0x0004)    /* Send next Data as Address */
#define UCTXBRK_L           (0x0002)    /* Send next Data as Break */
#define UCSWRST_L           (0x0001)    /* USCI Software Reset */

// UCAxCTLW0 UART-Mode Control Bits
#define UCPEN_H             (0x0080)    /* Async. Mode: Parity enable */
#define UCPAR_H             (0x0040)    /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB_H             (0x0020)    /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT_H            (0x0010)    /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB_H             (0x0008)    /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1_H           (0x0004)    /* Async. Mode: USCI Mode 1 */
#define UCMODE0_H           (0x0002)    /* Async. Mode: USCI Mode 0 */
#define UCSYNC_H            (0x0001)    /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// UCxxCTLW0 SPI-Mode Control Bits
#define UCCKPH              (0x8000)    /* Sync. Mode: Clock Phase */
#define UCCKPL              (0x4000)    /* Sync. Mode: Clock Polarity */
#define UCMST               (0x0800)    /* Sync. Mode: Master Select */
//#define res               (0x0020)    /* reserved */
//#define res               (0x0010)    /* reserved */
//#define res               (0x0008)    /* reserved */
//#define res               (0x0004)    /* reserved */
#define UCSTEM             (0x0002)    /* USCI STE Mode */

// UCBxCTLW0 I2C-Mode Control Bits
#define UCA10               (0x8000)    /* 10-bit Address Mode */
#define UCSLA10             (0x4000)    /* 10-bit Slave Address Mode */
#define UCMM                (0x2000)    /* Multi-Master Environment */
//#define res               (0x1000)    /* reserved */
//#define res               (0x0100)    /* reserved */
#define UCTXACK             (0x0020)    /* Transmit ACK */
#define UCTR                (0x0010)    /* Transmit/Receive Select/Flag */
#define UCTXNACK            (0x0008)    /* Transmit NACK */
#define UCTXSTP             (0x0004)    /* Transmit STOP */
#define UCTXSTT             (0x0002)    /* Transmit START */

// UCBxCTLW0 I2C-Mode Control Bits
//#define res               (0x1000)    /* reserved */
//#define res               (0x0100)    /* reserved */
#define UCTXACK_L           (0x0020)    /* Transmit ACK */
#define UCTR_L              (0x0010)    /* Transmit/Receive Select/Flag */
#define UCTXNACK_L          (0x0008)    /* Transmit NACK */
#define UCTXSTP_L           (0x0004)    /* Transmit STOP */
#define UCTXSTT_L           (0x0002)    /* Transmit START */

// UCBxCTLW0 I2C-Mode Control Bits
#define UCA10_H             (0x0080)    /* 10-bit Address Mode */
#define UCSLA10_H           (0x0040)    /* 10-bit Slave Address Mode */
#define UCMM_H              (0x0020)    /* Multi-Master Environment */
//#define res               (0x1000)    /* reserved */
//#define res               (0x0100)    /* reserved */

#define UCMODE_0            (0x0000)    /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1            (0x0200)    /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2            (0x0400)    /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3            (0x0600)    /* Sync. Mode: USCI Mode: 3 */

#define UCSSEL_0            (0x0000)    /* USCI 0 Clock Source: 0 */
#define UCSSEL_1            (0x0040)    /* USCI 0 Clock Source: 1 */
#define UCSSEL_2            (0x0080)    /* USCI 0 Clock Source: 2 */
#define UCSSEL_3            (0x00C0)    /* USCI 0 Clock Source: 3 */
#define UCSSEL__UCLK        (0x0000)    /* USCI 0 Clock Source: UCLK */
#define UCSSEL__ACLK        (0x0040)    /* USCI 0 Clock Source: ACLK */
#define UCSSEL__SMCLK       (0x0080)    /* USCI 0 Clock Source: SMCLK */


// UCAxCTLW1 UART-Mode Control Bits
#define UCGLIT1             (0x0002)    /* USCI Deglitch Time Bit 1 */
#define UCGLIT0             (0x0001)    /* USCI Deglitch Time Bit 0 */

// UCAxCTLW1 UART-Mode Control Bits
#define UCGLIT1_L           (0x0002)    /* USCI Deglitch Time Bit 1 */
#define UCGLIT0_L           (0x0001)    /* USCI Deglitch Time Bit 0 */

// UCAxCTLW1 UART-Mode Control Bits

// UCBxCTLW1 I2C-Mode Control Bits
#define UCETXINT            (0x0100)    /* USCI Early UCTXIFG0 */
#define UCCLTO1             (0x0080)    /* USCI Clock low timeout Bit: 1 */
#define UCCLTO0             (0x0040)    /* USCI Clock low timeout Bit: 0 */
#define UCSTPNACK           (0x0020)    /* USCI Acknowledge Stop last byte */
#define UCSWACK             (0x0010)    /* USCI Software controlled ACK */
#define UCASTP1             (0x0008)    /* USCI Automatic Stop condition generation Bit: 1 */
#define UCASTP0             (0x0004)    /* USCI Automatic Stop condition generation Bit: 0 */
#define UCGLIT1             (0x0002)    /* USCI Deglitch time Bit: 1 */
#define UCGLIT0             (0x0001)    /* USCI Deglitch time Bit: 0 */

// UCBxCTLW1 I2C-Mode Control Bits
#define UCCLTO1_L           (0x0080)    /* USCI Clock low timeout Bit: 1 */
#define UCCLTO0_L           (0x0040)    /* USCI Clock low timeout Bit: 0 */
#define UCSTPNACK_L         (0x0020)    /* USCI Acknowledge Stop last byte */
#define UCSWACK_L           (0x0010)    /* USCI Software controlled ACK */
#define UCASTP1_L           (0x0008)    /* USCI Automatic Stop condition generation Bit: 1 */
#define UCASTP0_L           (0x0004)    /* USCI Automatic Stop condition generation Bit: 0 */
#define UCGLIT1_L           (0x0002)    /* USCI Deglitch time Bit: 1 */
#define UCGLIT0_L           (0x0001)    /* USCI Deglitch time Bit: 0 */

// UCBxCTLW1 I2C-Mode Control Bits
#define UCETXINT_H          (0x0001)    /* USCI Early UCTXIFG0 */

#define UCGLIT_0            (0x0000)    /* USCI Deglitch time: 0 */
#define UCGLIT_1            (0x0001)    /* USCI Deglitch time: 1 */
#define UCGLIT_2            (0x0002)    /* USCI Deglitch time: 2 */
#define UCGLIT_3            (0x0003)    /* USCI Deglitch time: 3 */

#define UCASTP_0            (0x0000)    /* USCI Automatic Stop condition generation: 0 */
#define UCASTP_1            (0x0004)    /* USCI Automatic Stop condition generation: 1 */
#define UCASTP_2            (0x0008)    /* USCI Automatic Stop condition generation: 2 */
#define UCASTP_3            (0x000C)    /* USCI Automatic Stop condition generation: 3 */

#define UCCLTO_0            (0x0000)    /* USCI Clock low timeout: 0 */
#define UCCLTO_1            (0x0040)    /* USCI Clock low timeout: 1 */
#define UCCLTO_2            (0x0080)    /* USCI Clock low timeout: 2 */
#define UCCLTO_3            (0x00C0)    /* USCI Clock low timeout: 3 */


/* UCAxMCTLW Control Bits */
#define UCBRS7              (0x8000)    /* USCI Second Stage Modulation Select 7 */
#define UCBRS6              (0x4000)    /* USCI Second Stage Modulation Select 6 */
#define UCBRS5              (0x2000)    /* USCI Second Stage Modulation Select 5 */
#define UCBRS4              (0x1000)    /* USCI Second Stage Modulation Select 4 */
#define UCBRS3              (0x0800)    /* USCI Second Stage Modulation Select 3 */
#define UCBRS2              (0x0400)    /* USCI Second Stage Modulation Select 2 */
#define UCBRS1              (0x0200)    /* USCI Second Stage Modulation Select 1 */
#define UCBRS0              (0x0100)    /* USCI Second Stage Modulation Select 0 */
#define UCBRF3              (0x0080)    /* USCI First Stage Modulation Select 3 */
#define UCBRF2              (0x0040)    /* USCI First Stage Modulation Select 2 */
#define UCBRF1              (0x0020)    /* USCI First Stage Modulation Select 1 */
#define UCBRF0              (0x0010)    /* USCI First Stage Modulation Select 0 */
#define UCOS16              (0x0001)    /* USCI 16-times Oversampling enable */

/* UCAxMCTLW Control Bits */
#define UCBRF3_L            (0x0080)    /* USCI First Stage Modulation Select 3 */
#define UCBRF2_L            (0x0040)    /* USCI First Stage Modulation Select 2 */
#define UCBRF1_L            (0x0020)    /* USCI First Stage Modulation Select 1 */
#define UCBRF0_L            (0x0010)    /* USCI First Stage Modulation Select 0 */
#define UCOS16_L            (0x0001)    /* USCI 16-times Oversampling enable */

/* UCAxMCTLW Control Bits */
#define UCBRS7_H            (0x0080)    /* USCI Second Stage Modulation Select 7 */
#define UCBRS6_H            (0x0040)    /* USCI Second Stage Modulation Select 6 */
#define UCBRS5_H            (0x0020)    /* USCI Second Stage Modulation Select 5 */
#define UCBRS4_H            (0x0010)    /* USCI Second Stage Modulation Select 4 */
#define UCBRS3_H            (0x0008)    /* USCI Second Stage Modulation Select 3 */
#define UCBRS2_H            (0x0004)    /* USCI Second Stage Modulation Select 2 */
#define UCBRS1_H            (0x0002)    /* USCI Second Stage Modulation Select 1 */
#define UCBRS0_H            (0x0001)    /* USCI Second Stage Modulation Select 0 */

#define UCBRF_0             (0x00)    /* USCI First Stage Modulation: 0 */
#define UCBRF_1             (0x10)    /* USCI First Stage Modulation: 1 */
#define UCBRF_2             (0x20)    /* USCI First Stage Modulation: 2 */
#define UCBRF_3             (0x30)    /* USCI First Stage Modulation: 3 */
#define UCBRF_4             (0x40)    /* USCI First Stage Modulation: 4 */
#define UCBRF_5             (0x50)    /* USCI First Stage Modulation: 5 */
#define UCBRF_6             (0x60)    /* USCI First Stage Modulation: 6 */
#define UCBRF_7             (0x70)    /* USCI First Stage Modulation: 7 */
#define UCBRF_8             (0x80)    /* USCI First Stage Modulation: 8 */
#define UCBRF_9             (0x90)    /* USCI First Stage Modulation: 9 */
#define UCBRF_10            (0xA0)    /* USCI First Stage Modulation: A */
#define UCBRF_11            (0xB0)    /* USCI First Stage Modulation: B */
#define UCBRF_12            (0xC0)    /* USCI First Stage Modulation: C */
#define UCBRF_13            (0xD0)    /* USCI First Stage Modulation: D */
#define UCBRF_14            (0xE0)    /* USCI First Stage Modulation: E */
#define UCBRF_15            (0xF0)    /* USCI First Stage Modulation: F */


/* UCAxSTATW Control Bits */
#define UCLISTEN            (0x0080)  /* USCI Listen mode */
#define UCFE                (0x0040)  /* USCI Frame Error Flag */
#define UCOE                (0x0020)  /* USCI Overrun Error Flag */
#define UCPE                (0x0010)  /* USCI Parity Error Flag */
#define UCBRK               (0x0008)  /* USCI Break received */
#define UCRXERR             (0x0004)  /* USCI RX Error Flag */
#define UCADDR              (0x0002)  /* USCI Address received Flag */
#define UCBUSY              (0x0001)  /* USCI Busy Flag */
#define UCIDLE              (0x0002)  /* USCI Idle line detected Flag */


/* UCBxSTATW I2C Control Bits */
#define UCBCNT7             (0x8000)  /* USCI Byte Counter Bit 7 */
#define UCBCNT6             (0x4000)  /* USCI Byte Counter Bit 6 */
#define UCBCNT5             (0x2000)  /* USCI Byte Counter Bit 5 */
#define UCBCNT4             (0x1000)  /* USCI Byte Counter Bit 4 */
#define UCBCNT3             (0x0800)  /* USCI Byte Counter Bit 3 */
#define UCBCNT2             (0x0400)  /* USCI Byte Counter Bit 2 */
#define UCBCNT1             (0x0200)  /* USCI Byte Counter Bit 1 */
#define UCBCNT0             (0x0100)  /* USCI Byte Counter Bit 0 */
#define UCSCLLOW            (0x0040)  /* SCL low */
#define UCGC                (0x0020)  /* General Call address received Flag */
#define UCBBUSY             (0x0010)  /* Bus Busy Flag */

/* UCBxTBCNT I2C Control Bits */
#define UCTBCNT7            (0x0080)  /* USCI Byte Counter Bit 7 */
#define UCTBCNT6            (0x0040)  /* USCI Byte Counter Bit 6 */
#define UCTBCNT5            (0x0020)  /* USCI Byte Counter Bit 5 */
#define UCTBCNT4            (0x0010)  /* USCI Byte Counter Bit 4 */
#define UCTBCNT3            (0x0008)  /* USCI Byte Counter Bit 3 */
#define UCTBCNT2            (0x0004)  /* USCI Byte Counter Bit 2 */
#define UCTBCNT1            (0x0002)  /* USCI Byte Counter Bit 1 */
#define UCTBCNT0            (0x0001)  /* USCI Byte Counter Bit 0 */

/* UCAxIRCTL Control Bits */
#define UCIRRXFL5           (0x8000)  /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4           (0x4000)  /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3           (0x2000)  /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2           (0x1000)  /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1           (0x0800)  /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0           (0x0400)  /* IRDA Receive Filter Length 0 */
#define UCIRRXPL            (0x0200)  /* IRDA Receive Input Polarity */
#define UCIRRXFE            (0x0100)  /* IRDA Receive Filter enable */
#define UCIRTXPL5           (0x0080)  /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4           (0x0040)  /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3           (0x0020)  /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2           (0x0010)  /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1           (0x0008)  /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0           (0x0004)  /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK           (0x0002)  /* IRDA Transmit Pulse Clock Select */
#define UCIREN              (0x0001)  /* IRDA Encoder/Decoder enable */

/* UCAxIRCTL Control Bits */
#define UCIRTXPL5_L         (0x0080)  /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4_L         (0x0040)  /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3_L         (0x0020)  /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2_L         (0x0010)  /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1_L         (0x0008)  /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0_L         (0x0004)  /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK_L         (0x0002)  /* IRDA Transmit Pulse Clock Select */
#define UCIREN_L            (0x0001)  /* IRDA Encoder/Decoder enable */

/* UCAxIRCTL Control Bits */
#define UCIRRXFL5_H         (0x0080)  /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4_H         (0x0040)  /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3_H         (0x0020)  /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2_H         (0x0010)  /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1_H         (0x0008)  /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0_H         (0x0004)  /* IRDA Receive Filter Length 0 */
#define UCIRRXPL_H          (0x0002)  /* IRDA Receive Input Polarity */
#define UCIRRXFE_H          (0x0001)  /* IRDA Receive Filter enable */


/* UCAxABCTL Control Bits */
//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1            (0x20)    /* Break Sync Delimiter 1 */
#define UCDELIM0            (0x10)    /* Break Sync Delimiter 0 */
#define UCSTOE              (0x08)    /* Sync-Field Timeout error */
#define UCBTOE              (0x04)    /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN             (0x01)    /* Auto Baud Rate detect enable */

/* UCBxI2COA0 Control Bits */
#define UCGCEN              (0x8000)  /* I2C General Call enable */
#define UCOAEN              (0x0400)  /* I2C Own Address enable */
#define UCOA9               (0x0200)  /* I2C Own Address Bit 9 */
#define UCOA8               (0x0100)  /* I2C Own Address Bit 8 */
#define UCOA7               (0x0080)  /* I2C Own Address Bit 7 */
#define UCOA6               (0x0040)  /* I2C Own Address Bit 6 */
#define UCOA5               (0x0020)  /* I2C Own Address Bit 5 */
#define UCOA4               (0x0010)  /* I2C Own Address Bit 4 */
#define UCOA3               (0x0008)  /* I2C Own Address Bit 3 */
#define UCOA2               (0x0004)  /* I2C Own Address Bit 2 */
#define UCOA1               (0x0002)  /* I2C Own Address Bit 1 */
#define UCOA0               (0x0001)  /* I2C Own Address Bit 0 */

/* UCBxI2COA0 Control Bits */
#define UCOA7_L             (0x0080)  /* I2C Own Address Bit 7 */
#define UCOA6_L             (0x0040)  /* I2C Own Address Bit 6 */
#define UCOA5_L             (0x0020)  /* I2C Own Address Bit 5 */
#define UCOA4_L             (0x0010)  /* I2C Own Address Bit 4 */
#define UCOA3_L             (0x0008)  /* I2C Own Address Bit 3 */
#define UCOA2_L             (0x0004)  /* I2C Own Address Bit 2 */
#define UCOA1_L             (0x0002)  /* I2C Own Address Bit 1 */
#define UCOA0_L             (0x0001)  /* I2C Own Address Bit 0 */

/* UCBxI2COA0 Control Bits */
#define UCGCEN_H            (0x0080)  /* I2C General Call enable */
#define UCOAEN_H            (0x0004)  /* I2C Own Address enable */
#define UCOA9_H             (0x0002)  /* I2C Own Address Bit 9 */
#define UCOA8_H             (0x0001)  /* I2C Own Address Bit 8 */

/* UCBxI2COAx Control Bits */
#define UCOAEN              (0x0400)  /* I2C Own Address enable */
#define UCOA9               (0x0200)  /* I2C Own Address Bit 9 */
#define UCOA8               (0x0100)  /* I2C Own Address Bit 8 */
#define UCOA7               (0x0080)  /* I2C Own Address Bit 7 */
#define UCOA6               (0x0040)  /* I2C Own Address Bit 6 */
#define UCOA5               (0x0020)  /* I2C Own Address Bit 5 */
#define UCOA4               (0x0010)  /* I2C Own Address Bit 4 */
#define UCOA3               (0x0008)  /* I2C Own Address Bit 3 */
#define UCOA2               (0x0004)  /* I2C Own Address Bit 2 */
#define UCOA1               (0x0002)  /* I2C Own Address Bit 1 */
#define UCOA0               (0x0001)  /* I2C Own Address Bit 0 */

/* UCBxI2COAx Control Bits */
#define UCOA7_L             (0x0080)  /* I2C Own Address Bit 7 */
#define UCOA6_L             (0x0040)  /* I2C Own Address Bit 6 */
#define UCOA5_L             (0x0020)  /* I2C Own Address Bit 5 */
#define UCOA4_L             (0x0010)  /* I2C Own Address Bit 4 */
#define UCOA3_L             (0x0008)  /* I2C Own Address Bit 3 */
#define UCOA2_L             (0x0004)  /* I2C Own Address Bit 2 */
#define UCOA1_L             (0x0002)  /* I2C Own Address Bit 1 */
#define UCOA0_L             (0x0001)  /* I2C Own Address Bit 0 */

/* UCBxI2COAx Control Bits */
#define UCOAEN_H            (0x0004)  /* I2C Own Address enable */
#define UCOA9_H             (0x0002)  /* I2C Own Address Bit 9 */
#define UCOA8_H             (0x0001)  /* I2C Own Address Bit 8 */

/* UCBxADDRX Control Bits */
#define UCADDRX9            (0x0200)  /* I2C Receive Address Bit 9 */
#define UCADDRX8            (0x0100)  /* I2C Receive Address Bit 8 */
#define UCADDRX7            (0x0080)  /* I2C Receive Address Bit 7 */
#define UCADDRX6            (0x0040)  /* I2C Receive Address Bit 6 */
#define UCADDRX5            (0x0020)  /* I2C Receive Address Bit 5 */
#define UCADDRX4            (0x0010)  /* I2C Receive Address Bit 4 */
#define UCADDRX3            (0x0008)  /* I2C Receive Address Bit 3 */
#define UCADDRX2            (0x0004)  /* I2C Receive Address Bit 2 */
#define UCADDRX1            (0x0002)  /* I2C Receive Address Bit 1 */
#define UCADDRX0            (0x0001)  /* I2C Receive Address Bit 0 */

/* UCBxADDRX Control Bits */
#define UCADDRX7_L          (0x0080)  /* I2C Receive Address Bit 7 */
#define UCADDRX6_L          (0x0040)  /* I2C Receive Address Bit 6 */
#define UCADDRX5_L          (0x0020)  /* I2C Receive Address Bit 5 */
#define UCADDRX4_L          (0x0010)  /* I2C Receive Address Bit 4 */
#define UCADDRX3_L          (0x0008)  /* I2C Receive Address Bit 3 */
#define UCADDRX2_L          (0x0004)  /* I2C Receive Address Bit 2 */
#define UCADDRX1_L          (0x0002)  /* I2C Receive Address Bit 1 */
#define UCADDRX0_L          (0x0001)  /* I2C Receive Address Bit 0 */

/* UCBxADDRX Control Bits */
#define UCADDRX9_H          (0x0002)  /* I2C Receive Address Bit 9 */
#define UCADDRX8_H          (0x0001)  /* I2C Receive Address Bit 8 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK9            (0x0200)  /* I2C Address Mask Bit 9 */
#define UCADDMASK8            (0x0100)  /* I2C Address Mask Bit 8 */
#define UCADDMASK7            (0x0080)  /* I2C Address Mask Bit 7 */
#define UCADDMASK6            (0x0040)  /* I2C Address Mask Bit 6 */
#define UCADDMASK5            (0x0020)  /* I2C Address Mask Bit 5 */
#define UCADDMASK4            (0x0010)  /* I2C Address Mask Bit 4 */
#define UCADDMASK3            (0x0008)  /* I2C Address Mask Bit 3 */
#define UCADDMASK2            (0x0004)  /* I2C Address Mask Bit 2 */
#define UCADDMASK1            (0x0002)  /* I2C Address Mask Bit 1 */
#define UCADDMASK0            (0x0001)  /* I2C Address Mask Bit 0 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK7_L        (0x0080)  /* I2C Address Mask Bit 7 */
#define UCADDMASK6_L        (0x0040)  /* I2C Address Mask Bit 6 */
#define UCADDMASK5_L        (0x0020)  /* I2C Address Mask Bit 5 */
#define UCADDMASK4_L        (0x0010)  /* I2C Address Mask Bit 4 */
#define UCADDMASK3_L        (0x0008)  /* I2C Address Mask Bit 3 */
#define UCADDMASK2_L        (0x0004)  /* I2C Address Mask Bit 2 */
#define UCADDMASK1_L        (0x0002)  /* I2C Address Mask Bit 1 */
#define UCADDMASK0_L        (0x0001)  /* I2C Address Mask Bit 0 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK9_H        (0x0002)  /* I2C Address Mask Bit 9 */
#define UCADDMASK8_H        (0x0001)  /* I2C Address Mask Bit 8 */

/* UCBxI2CSA Control Bits */
#define UCSA9               (0x0200)  /* I2C Slave Address Bit 9 */
#define UCSA8               (0x0100)  /* I2C Slave Address Bit 8 */
#define UCSA7               (0x0080)  /* I2C Slave Address Bit 7 */
#define UCSA6               (0x0040)  /* I2C Slave Address Bit 6 */
#define UCSA5               (0x0020)  /* I2C Slave Address Bit 5 */
#define UCSA4               (0x0010)  /* I2C Slave Address Bit 4 */
#define UCSA3               (0x0008)  /* I2C Slave Address Bit 3 */
#define UCSA2               (0x0004)  /* I2C Slave Address Bit 2 */
#define UCSA1               (0x0002)  /* I2C Slave Address Bit 1 */
#define UCSA0               (0x0001)  /* I2C Slave Address Bit 0 */

/* UCBxI2CSA Control Bits */
#define UCSA7_L             (0x0080)  /* I2C Slave Address Bit 7 */
#define UCSA6_L             (0x0040)  /* I2C Slave Address Bit 6 */
#define UCSA5_L             (0x0020)  /* I2C Slave Address Bit 5 */
#define UCSA4_L             (0x0010)  /* I2C Slave Address Bit 4 */
#define UCSA3_L             (0x0008)  /* I2C Slave Address Bit 3 */
#define UCSA2_L             (0x0004)  /* I2C Slave Address Bit 2 */
#define UCSA1_L             (0x0002)  /* I2C Slave Address Bit 1 */
#define UCSA0_L             (0x0001)  /* I2C Slave Address Bit 0 */

/* UCBxI2CSA Control Bits */
#define UCSA9_H             (0x0002)  /* I2C Slave Address Bit 9 */
#define UCSA8_H             (0x0001)  /* I2C Slave Address Bit 8 */

/* UCAxIE UART Control Bits */
#define UCTXCPTIE           (0x0008)  /* UART Transmit Complete Interrupt Enable */
#define UCSTTIE             (0x0004)  /* UART Start Bit Interrupt Enalble */
#define UCTXIE              (0x0002)  /* UART Transmit Interrupt Enable */
#define UCRXIE              (0x0001)  /* UART Receive Interrupt Enable */

/* UCAxIE/UCBxIE SPI Control Bits */

/* UCBxIE I2C Control Bits */
#define UCBIT9IE            (0x4000)  /* I2C Bit 9 Position Interrupt Enable 3 */
#define UCTXIE3             (0x2000)  /* I2C Transmit Interrupt Enable 3 */
#define UCRXIE3             (0x1000)  /* I2C Receive Interrupt Enable 3 */
#define UCTXIE2             (0x0800)  /* I2C Transmit Interrupt Enable 2 */
#define UCRXIE2             (0x0400)  /* I2C Receive Interrupt Enable 2 */
#define UCTXIE1             (0x0200)  /* I2C Transmit Interrupt Enable 1 */
#define UCRXIE1             (0x0100)  /* I2C Receive Interrupt Enable 1 */
#define UCCLTOIE            (0x0080)  /* I2C Clock Low Timeout interrupt enable */
#define UCBCNTIE            (0x0040)  /* I2C Automatic stop assertion interrupt enable */
#define UCNACKIE            (0x0020)  /* I2C NACK Condition interrupt enable */
#define UCALIE              (0x0010)  /* I2C Arbitration Lost interrupt enable */
#define UCSTPIE             (0x0008)  /* I2C STOP Condition interrupt enable */
#define UCSTTIE             (0x0004)  /* I2C START Condition interrupt enable */
#define UCTXIE0             (0x0002)  /* I2C Transmit Interrupt Enable 0 */
#define UCRXIE0             (0x0001)  /* I2C Receive Interrupt Enable 0 */

/* UCAxIFG UART Control Bits */
#define UCTXCPTIFG          (0x0008)  /* UART Transmit Complete Interrupt Flag */
#define UCSTTIFG            (0x0004)  /* UART Start Bit Interrupt Flag */
#define UCTXIFG             (0x0002)  /* UART Transmit Interrupt Flag */
#define UCRXIFG             (0x0001)  /* UART Receive Interrupt Flag */

/* UCAxIFG/UCBxIFG SPI Control Bits */
#define UCTXIFG             (0x0002)  /* SPI Transmit Interrupt Flag */
#define UCRXIFG             (0x0001)  /* SPI Receive Interrupt Flag */

/* UCBxIFG Control Bits */
#define UCBIT9IFG           (0x4000)  /* I2C Bit 9 Possition Interrupt Flag 3 */
#define UCTXIFG3            (0x2000)  /* I2C Transmit Interrupt Flag 3 */
#define UCRXIFG3            (0x1000)  /* I2C Receive Interrupt Flag 3 */
#define UCTXIFG2            (0x0800)  /* I2C Transmit Interrupt Flag 2 */
#define UCRXIFG2            (0x0400)  /* I2C Receive Interrupt Flag 2 */
#define UCTXIFG1            (0x0200)  /* I2C Transmit Interrupt Flag 1 */
#define UCRXIFG1            (0x0100)  /* I2C Receive Interrupt Flag 1 */
#define UCCLTOIFG           (0x0080)  /* I2C Clock low Timeout interrupt Flag */
#define UCBCNTIFG           (0x0040)  /* I2C Byte counter interrupt flag */
#define UCNACKIFG           (0x0020)  /* I2C NACK Condition interrupt Flag */
#define UCALIFG             (0x0010)  /* I2C Arbitration Lost interrupt Flag */
#define UCSTPIFG            (0x0008)  /* I2C STOP Condition interrupt Flag */
#define UCSTTIFG            (0x0004)  /* I2C START Condition interrupt Flag */
#define UCTXIFG0            (0x0002)  /* I2C Transmit Interrupt Flag 0 */
#define UCRXIFG0            (0x0001)  /* I2C Receive Interrupt Flag 0 */

/* USCI UART Definitions */
#define USCI_NONE            (0x0000)   /* No Interrupt pending */
#define USCI_UART_UCRXIFG    (0x0002)   /* USCI UCRXIFG */
#define USCI_UART_UCTXIFG    (0x0004)   /* USCI UCTXIFG */
#define USCI_UART_UCSTTIFG   (0x0006)   /* USCI UCSTTIFG */
#define USCI_UART_UCTXCPTIFG (0x0008)   /* USCI UCTXCPTIFG */

/* USCI SPI Definitions */
#define USCI_SPI_UCRXIFG    (0x0002)    /* USCI UCRXIFG */
#define USCI_SPI_UCTXIFG    (0x0004)    /* USCI UCTXIFG */

/* USCI I2C Definitions */
#define USCI_I2C_UCALIFG    (0x0002)    /* USCI I2C Mode: UCALIFG */
#define USCI_I2C_UCNACKIFG  (0x0004)    /* USCI I2C Mode: UCNACKIFG */
#define USCI_I2C_UCSTTIFG   (0x0006)    /* USCI I2C Mode: UCSTTIFG*/
#define USCI_I2C_UCSTPIFG   (0x0008)    /* USCI I2C Mode: UCSTPIFG*/
#define USCI_I2C_UCRXIFG3   (0x000A)    /* USCI I2C Mode: UCRXIFG3 */
#define USCI_I2C_UCTXIFG3   (0x000C)    /* USCI I2C Mode: UCTXIFG3 */
#define USCI_I2C_UCRXIFG2   (0x000E)    /* USCI I2C Mode: UCRXIFG2 */
#define USCI_I2C_UCTXIFG2   (0x0010)    /* USCI I2C Mode: UCTXIFG2 */
#define USCI_I2C_UCRXIFG1   (0x0012)    /* USCI I2C Mode: UCRXIFG1 */
#define USCI_I2C_UCTXIFG1   (0x0014)    /* USCI I2C Mode: UCTXIFG1 */
#define USCI_I2C_UCRXIFG0   (0x0016)    /* USCI I2C Mode: UCRXIFG0 */
#define USCI_I2C_UCTXIFG0   (0x0018)    /* USCI I2C Mode: UCTXIFG0 */
#define USCI_I2C_UCBCNTIFG  (0x001A)    /* USCI I2C Mode: UCBCNTIFG */
#define USCI_I2C_UCCLTOIFG  (0x001C)    /* USCI I2C Mode: UCCLTOIFG */
#define USCI_I2C_UCBIT9IFG  (0x001E)    /* USCI I2C Mode: UCBIT9IFG */















/************************************************************
* USCI A1
************************************************************/
#define __MSP430_HAS_EUSCI_A1__      /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_EUSCI_A1__ 0x05E0
#define EUSCI_A1_BASE __MSP430_BASEADDRESS_EUSCI_A1__

#define UCA1CTLW0_            0x05E0    /* USCI A1 Control Word Register 0 */
#define UCA1CTLW0_L (*(volatile uint8_t *)0x5e0)
#define UCA1CTLW0 (*(volatile uint16_t *)0x5e0)
#define UCA1CTLW0_H (*(volatile uint8_t *)0x5e1)
#define UCA1CTLW0_L (*(volatile uint8_t *)0x5e0)
#define UCA1CTLW0 (*(volatile uint16_t *)0x5e0)
#define UCA1CTL1            UCA1CTLW0_L  /* USCI A1 Control Register 1 */
#define UCA1CTL0            UCA1CTLW0_H  /* USCI A1 Control Register 0 */
#define UCA1CTLW1_            0x05E2    /* USCI A1 Control Word Register 1 */
#define UCA1CTLW1_L (*(volatile uint8_t *)0x5e2)
#define UCA1CTLW1 (*(volatile uint16_t *)0x5e2)
#define UCA1CTLW1_H (*(volatile uint8_t *)0x5e3)
#define UCA1CTLW1_L (*(volatile uint8_t *)0x5e2)
#define UCA1CTLW1 (*(volatile uint16_t *)0x5e2)
#define UCA1BRW_              0x05E6    /* USCI A1 Baud Word Rate 0 */
#define UCA1BRW_L (*(volatile uint8_t *)0x5e6)
#define UCA1BRW (*(volatile uint16_t *)0x5e6)
#define UCA1BRW_H (*(volatile uint8_t *)0x5e7)
#define UCA1BRW_L (*(volatile uint8_t *)0x5e6)
#define UCA1BRW (*(volatile uint16_t *)0x5e6)
#define UCA1BR0             UCA1BRW_L /* USCI A1 Baud Rate 0 */
#define UCA1BR1             UCA1BRW_H /* USCI A1 Baud Rate 1 */
#define UCA1MCTLW_            0x05E8    /* USCI A1 Modulation Control */
#define UCA1MCTLW_L (*(volatile uint8_t *)0x5e8)
#define UCA1MCTLW (*(volatile uint16_t *)0x5e8)
#define UCA1MCTLW_H (*(volatile uint8_t *)0x5e9)
#define UCA1MCTLW_L (*(volatile uint8_t *)0x5e8)
#define UCA1MCTLW (*(volatile uint16_t *)0x5e8)
#define UCA1STATW_            0x05EA    /* USCI A1 Status Register */
#define UCA1STATW (*(volatile uint8_t *)0x5ea)
#define UCA1RXBUF_            0x05EC    /* USCI A1 Receive Buffer */
#define UCA1RXBUF_L (*(volatile uint8_t *)0x5ec)
#define UCA1RXBUF (*(volatile uint16_t *)0x5ec)
#define UCA1RXBUF_H (*(volatile uint8_t *)0x5ed)
#define UCA1RXBUF_L (*(volatile uint8_t *)0x5ec)
#define UCA1RXBUF (*(volatile uint16_t *)0x5ec)
#define UCA1TXBUF_            0x05EE    /* USCI A1 Transmit Buffer */
#define UCA1TXBUF_L (*(volatile uint8_t *)0x5ee)
#define UCA1TXBUF (*(volatile uint16_t *)0x5ee)
#define UCA1TXBUF_H (*(volatile uint8_t *)0x5ef)
#define UCA1TXBUF_L (*(volatile uint8_t *)0x5ee)
#define UCA1TXBUF (*(volatile uint16_t *)0x5ee)
#define UCA1ABCTL_            0x05F0    /* USCI A1 LIN Control */
#define UCA1ABCTL (*(volatile uint8_t *)0x5f0)
#define UCA1IRCTL_            0x05F2    /* USCI A1 IrDA Transmit Control */
#define UCA1IRCTL_L (*(volatile uint8_t *)0x5f2)
#define UCA1IRCTL (*(volatile uint16_t *)0x5f2)
#define UCA1IRCTL_H (*(volatile uint8_t *)0x5f3)
#define UCA1IRCTL_L (*(volatile uint8_t *)0x5f2)
#define UCA1IRCTL (*(volatile uint16_t *)0x5f2)
#define UCA1IRTCTL          UCA1IRCTL_L  /* USCI A1 IrDA Transmit Control */
#define UCA1IRRCTL          UCA1IRCTL_H  /* USCI A1 IrDA Receive Control */
#define UCA1IE_               0x05FA    /* USCI A1 Interrupt Enable Register */
#define UCA1IE_L (*(volatile uint8_t *)0x5fa)
#define UCA1IE (*(volatile uint16_t *)0x5fa)
#define UCA1IE_H (*(volatile uint8_t *)0x5fb)
#define UCA1IE_L (*(volatile uint8_t *)0x5fa)
#define UCA1IE (*(volatile uint16_t *)0x5fa)
#define UCA1IFG_              0x05FC    /* USCI A1 Interrupt Flags Register */
#define UCA1IFG_L (*(volatile uint8_t *)0x5fc)
#define UCA1IFG (*(volatile uint16_t *)0x5fc)
#define UCA1IFG_H (*(volatile uint8_t *)0x5fd)
#define UCA1IFG_L (*(volatile uint8_t *)0x5fc)
#define UCA1IFG (*(volatile uint16_t *)0x5fc)
#define UCA1IV_               0x05FE    /* USCI A1 Interrupt Vector Register */
#define UCA1IV (*(volatile uint16_t *)0x5fe)


/************************************************************
* WATCHDOG TIMER A
************************************************************/
#define __MSP430_HAS_WDT_A__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_WDT_A__ 0x0150
#define WDT_A_BASE __MSP430_BASEADDRESS_WDT_A__

#define WDTCTL_               0x015C    /* Watchdog Timer Control */
#define WDTCTL_L (*(volatile uint8_t *)0x15c)
#define WDTCTL (*(volatile uint16_t *)0x15c)
#define WDTCTL_H (*(volatile uint8_t *)0x15d)
#define WDTCTL_L (*(volatile uint8_t *)0x15c)
#define WDTCTL (*(volatile uint16_t *)0x15c)
/* The bit names have been prefixed with "WDT" */
/* WDTCTL Control Bits */
#define WDTIS0              (0x0001)  /* WDT - Timer Interval Select 0 */
#define WDTIS1              (0x0002)  /* WDT - Timer Interval Select 1 */
#define WDTIS2              (0x0004)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL            (0x0008)  /* WDT - Timer Clear */
#define WDTTMSEL            (0x0010)  /* WDT - Timer Mode Select */
#define WDTSSEL0            (0x0020)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1            (0x0040)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD             (0x0080)  /* WDT - Timer hold */

/* WDTCTL Control Bits */
#define WDTIS0_L            (0x0001)  /* WDT - Timer Interval Select 0 */
#define WDTIS1_L            (0x0002)  /* WDT - Timer Interval Select 1 */
#define WDTIS2_L            (0x0004)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL_L          (0x0008)  /* WDT - Timer Clear */
#define WDTTMSEL_L          (0x0010)  /* WDT - Timer Mode Select */
#define WDTSSEL0_L          (0x0020)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1_L          (0x0040)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD_L           (0x0080)  /* WDT - Timer hold */

/* WDTCTL Control Bits */

#define WDTPW               (0x5A00)

#define WDTIS_0           (0x0000)  /* WDT - Timer Interval Select: /2G */
#define WDTIS_1           (0x0001)  /* WDT - Timer Interval Select: /128M */
#define WDTIS_2           (0x0002)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS_3           (0x0003)  /* WDT - Timer Interval Select: /512k */
#define WDTIS_4           (0x0004)  /* WDT - Timer Interval Select: /32k */
#define WDTIS_5           (0x0005)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS_6           (0x0006)  /* WDT - Timer Interval Select: /512 */
#define WDTIS_7           (0x0007)  /* WDT - Timer Interval Select: /64 */
#define WDTIS__2G         (0x0000)  /* WDT - Timer Interval Select: /2G */
#define WDTIS__128M       (0x0001)  /* WDT - Timer Interval Select: /128M */
#define WDTIS__8192K      (0x0002)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS__512K       (0x0003)  /* WDT - Timer Interval Select: /512k */
#define WDTIS__32K        (0x0004)  /* WDT - Timer Interval Select: /32k */
#define WDTIS__8192       (0x0005)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS__512        (0x0006)  /* WDT - Timer Interval Select: /512 */
#define WDTIS__64         (0x0007)  /* WDT - Timer Interval Select: /64 */

#define WDTSSEL_0         (0x0000)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL_1         (0x0020)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL_2         (0x0040)  /* WDT - Timer Clock Source Select: VLO_CLK */
#define WDTSSEL_3         (0x0060)  /* WDT - Timer Clock Source Select: reserved */
#define WDTSSEL__SMCLK    (0x0000)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL__ACLK     (0x0020)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL__VLO      (0x0040)  /* WDT - Timer Clock Source Select: VLO_CLK */


/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms   " */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms   " */


/************************************************************
* Interrupt Vectors (offset from 0xFF80 + 0x10 for Password)
************************************************************/


#define RTC_VECTOR          (0x003E) /* 0xFFCE RTC */
#define PORT4_VECTOR        (0x0040) /* 0xFFD0 Port 4 */
#define PORT3_VECTOR        (0x0042) /* 0xFFD2 Port 3 */
#define TIMER2_B1_VECTOR    (0x0044) /* 0xFFD4 Timer2_B3 CC1-2, TB */
#define TIMER2_B0_VECTOR    (0x0046) /* 0xFFD6 Timer2_B3 CC0 */
#define PORT2_VECTOR        (0x0048) /* 0xFFD8 Port 2 */
#define TIMER1_B1_VECTOR    (0x004A) /* 0xFFDA Timer1_B3 CC1-2, TB */
#define TIMER1_B0_VECTOR    (0x004C) /* 0xFFDC Timer1_B3 CC0 */
#define PORT1_VECTOR        (0x004E) /* 0xFFDE Port 1 */
#define TIMER1_A1_VECTOR    (0x0050) /* 0xFFE0 Timer1_A3 CC1-2, TA1 */
#define TIMER1_A0_VECTOR    (0x0052) /* 0xFFE2 Timer1_A3 CC0 */
#define DMA_VECTOR          (0x0054) /* 0xFFE4 DMA */
#define USCI_A1_VECTOR      (0x0056) /* 0xFFE6 USCI A1 Receive/Transmit */
#define TIMER0_A1_VECTOR    (0x0058) /* 0xFFE8 Timer0_A5 CC1-4, TA */
#define TIMER0_A0_VECTOR    (0x005A) /* 0xFFEA Timer0_A5 CC0 */
#define ADC10_VECTOR        (0x005C) /* 0xFFEC ADC */
#define USCI_B0_VECTOR      (0x005E) /* 0xFFEE USCI B0 Receive/Transmit */
#define USCI_A0_VECTOR      (0x0060) /* 0xFFF0 USCI A0 Receive/Transmit */
#define WDT_VECTOR          (0x0062) /* 0xFFF2 Watchdog Timer */
#define TIMER0_B1_VECTOR    (0x0064) /* 0xFFF4 Timer0_B3 CC1-2, TB */
#define TIMER0_B0_VECTOR    (0x0066) /* 0xFFF6 Timer0_B3 CC0 */
#define COMP_D_VECTOR       (0x0068) /* 0xFFF8 Comparator D */
#define UNMI_VECTOR         (0x006A) /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR       (0x006C) /* 0xFFFC System Non-maskable */
#define RESET_VECTOR        (0x006E) /* 0xFFFE Reset [Highest Priority] */

/************************************************************
* End of Modules
************************************************************/
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __MSP430FR5739 */

