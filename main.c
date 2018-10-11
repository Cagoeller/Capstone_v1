//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "adc.h"
#include <stdint.h>

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
