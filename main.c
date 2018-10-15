//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "adc.h"
#include <stdint.h>


volatile uint16_t pointer[Num_of_Results];
volatile uint16_t middle[Num_of_Results];
volatile uint16_t ring[Num_of_Results];
volatile uint16_t pinky[Num_of_Results];


void main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	ConfigureADC();
    __enable_irq();

    while(1){
    	 ADC14->CTL0 |= ADC14_CTL0_ENC |
    	     ADC14_CTL0_SC;				// Enable the adc and start conversion
    }


}
