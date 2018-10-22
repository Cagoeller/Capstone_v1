//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "adc.h"
#include <stdint.h>


volatile unsigned int pointer[Num_of_Results];
volatile unsigned int middle[Num_of_Results];
volatile unsigned int ring[Num_of_Results];
volatile unsigned int pinky[Num_of_Results];

volatile unsigned int pointersum;
volatile unsigned int middlesum;
volatile unsigned int ringsum;
volatile unsigned int pinkysum;

volatile unsigned int pointerval;
volatile unsigned int middleval;
volatile unsigned int ringval;
volatile unsigned int pinkyval;

void main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	ConfigureADC();
    __enable_irq();

    while(1){
    	 ADC14->CTL0 |= ADC14_CTL0_ENC |
    	     ADC14_CTL0_SC;				// Enable the adc and start conversion
    	 //printf(" %d \n", pointerval);
    }


}
