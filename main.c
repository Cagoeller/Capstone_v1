//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "adc.h"
#include "dac.h"
#include "acl.h"
#include "spi.h"
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

/* SPI Master Configuration Parameter */
const eUSCI_SPI_MasterConfig spiMasterConfig =
{
	EUSCI_B_SPI_CLOCKSOURCE_SMCLK, // ACLK Clock Source
	/* Auxillary clock source, selectable LFXTBLK, VLOCLK, REFCLOCK, Max freq of 128kHz */
	//32768, // ACLK = LFXT = 32.768khz
	0,
	500000, // SPICLK = 500khz
	EUSCI_B_SPI_MSB_FIRST, // MSB First
	EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT, //EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT, // Phase
	EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW, // Low polarity
	EUSCI_B_SPI_3PIN // 3Wire SPI Mode
};




void main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	ConfigureADC();

	initializeSPIDAC();
	ConfigureADC();
	//sendByteDAC(0x55);
	initializeSPIACL();
    __enable_irq();
    int ii = 0;



    while(1){
    	//endDACinfo(0x01, 0x05,0x50, 0x3C);
		//sendByteDAC(0xff);
        P3->OUT &= ~BIT0;

        sendByteDAC(0x30);
        sendByteDAC(0x00);
        sendByteDAC(0x00);
        P3->OUT |= BIT0;

        P3->OUT &= ~BIT0;
        sendByteDAC(0x31);
        sendByteDAC(0xff);
        sendByteDAC(0xff);
        P3->OUT |= BIT0;

        P3->OUT &= ~BIT0;
        sendByteDAC(0x32);
        sendByteDAC(0x00);
        sendByteDAC(0xff);
        P3->OUT |= BIT0;

        P3->OUT &= ~BIT0;
        sendByteDAC(0x33);
        sendByteDAC(0x00);
        sendByteDAC(0x0f);
        P3->OUT |= BIT0;
        for(ii=0; ii <1000 ; ii++);
    	/*
    	P5->OUT &= ~BIT0;
    	EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, (0x80 | 0x02)); // y address

    	EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, 0x0F);
    	//EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, 0x00);
    	//EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, 0x00);
    	P5->OUT |= BIT0;
    	*/
		//sendByteDAC(0x23);
//    	ADC14->CTL0 |= ADC14_CTL0_ENC |
//    	     ADC14_CTL0_SC;				// Enable the adc and start conversion

    }
}




