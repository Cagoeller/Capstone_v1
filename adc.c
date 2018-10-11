/*
 * adc.c
 *
 *  Created on: Oct 11, 2018
 *      Author: Cary Goeller
 */


#include "msp.h"
#include "adc.h"

volatile uint16_t A0results[Num_of_Results];
volatile uint16_t A1results[Num_of_Results];
volatile uint16_t A2results[Num_of_Results];
volatile uint16_t A3results[Num_of_Results];
static uint8_t index;

void ConfigureADC(void){
	 P5->SEL1 |= BIT5 | BIT4 | BIT3 |BIT2;   // Enable A/D channel A0-A3
	 P5->SEL0 |= BIT5 | BIT4 | BIT3 |BIT2;

	    // Enable global interrupt
	    __enable_irq();

	    //NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);// Enable ADC interrupt in NVIC module
	    NVIC_EnableIRQ(ADC14_IRQn);

	    // Turn on ADC14, extend sampling time to avoid overflow of results
	    ADC14->CTL0 = ADC14_CTL0_ON |
	            ADC14_CTL0_MSC |
	            ADC14_CTL0_SHT0__192 |
	            ADC14_CTL0_SHP |
	            ADC14_CTL0_CONSEQ_3;

	    ADC14->MCTL[0] = ADC14_MCTLN_INCH_0;    // ref+=AVcc, channel = A0				P5.5
	    ADC14->MCTL[1] = ADC14_MCTLN_INCH_1;    // ref+=AVcc, channel = A1				P5.4
	    ADC14->MCTL[2] = ADC14_MCTLN_INCH_2;    // ref+=AVcc, channel = A2				P5.3
	    ADC14->MCTL[3] = ADC14_MCTLN_INCH_3|    // ref+=AVcc, channel = A3, end seq.	P5.2
	            ADC14_MCTLN_EOS;

	    ADC14->IER0 = ADC14_IER0_IE3;           // Enable ADC14IFG.3

	    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;   // Wake up on exit from ISR

	    // Ensures SLEEPONEXIT takes effect immediately
	    //__DSB();
}

void ADC14_IRQHandler(void){
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG3)
    {
        A0results[index] = ADC14->MEM[0];   // Move A0 results, IFG is cleared
        A1results[index] = ADC14->MEM[1];   // Move A1 results, IFG is cleared
        A2results[index] = ADC14->MEM[2];   // Move A2 results, IFG is cleared
        A3results[index] = ADC14->MEM[3];   // Move A3 results, IFG is cleared
        index = (index + 1) & 0x7;          // Increment results index, modulo
        __no_operation();                   // Set Breakpoint1 here
    }
}



