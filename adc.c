/*
 * adc.c
 *
 *  Created on: Oct 11, 2018
 *      Author: Cary Goeller
 */


#include "msp.h"
#include "adc.h"

static uint8_t index;
extern volatile uint16_t pointer[Num_of_Results];
extern volatile uint16_t middle[Num_of_Results];
extern volatile uint16_t ring[Num_of_Results];
extern volatile uint16_t pinky[Num_of_Results];


void ConfigureADC(void){
	 //P5->SEL1 |= BIT5 | BIT4 | BIT3 |BIT2;   // Enable A/D channel A0-A3
	 //P5->SEL0 |= BIT5 | BIT4 | BIT3 |BIT2;
		P6->SEL1 |= BIT1;
		P6->SEL0 |= BIT1;
		P4->SEL1 |= BIT0 | BIT2 | BIT4;
		P4->SEL0 |= BIT0 | BIT2 | BIT4;
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


	    /*
	     * current pins
	     * P6.1 -> A14 (4)
	     * P4.0 -> A13 (3)
	     * P4.2 -> A11 (2)
	     * P4.4 -> A9  (1)
	     */
	    ADC14->MCTL[0] = ADC14_MCTLN_INCH_9;    // ref+=AVcc, channel =  A9				PP4.4
	    ADC14->MCTL[1] = ADC14_MCTLN_INCH_11;    // ref+=AVcc, channel = A11			P4.2
	    ADC14->MCTL[2] = ADC14_MCTLN_INCH_13;    // ref+=AVcc, channel = A13			P4.0
	    ADC14->MCTL[3] = ADC14_MCTLN_INCH_14|    // ref+=AVcc, channel = A14, end seq.	P14
	            ADC14_MCTLN_EOS;

	    ADC14->IER0 = ADC14_IER0_IE3;           // Enable ADC14IFG.3

	    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;   // Wake up on exit from ISR

	    // Ensures SLEEPONEXIT takes effect immediately
	    //__DSB();
}

void ADC14_IRQHandler(void){
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG3)
    {
        pointer[index] = ADC14->MEM[0];   // Move A0 results, IFG is cleared
        middle[index] = ADC14->MEM[1];   // Move A1 results, IFG is cleared
        ring[index] = ADC14->MEM[2];   // Move A2 results, IFG is cleared
        pinky[index] = ADC14->MEM[3];   // Move A3 results, IFG is cleared
        index = (index + 1) & 0x7;          // Increment results index, modulo
    }
}



