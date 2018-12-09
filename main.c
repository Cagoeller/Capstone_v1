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

unsigned char RXData;

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




void main(void){
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	ConfigureADC();
	initializeSPIDAC();
	ConfigureADC();
	//sendByteDAC(0x55);
	initializeSPIACL();
    __enable_irq();

    int ii = 0;
    int z = 0;
    int throttle = 0x00 << 13;
    int yaw = 0x01 << 13;
    int roll = 0x01 << 13;
    int pitch = 0x01 << 13;
    int mid = 8192;

    P5->OUT &= ~BIT0;
    sendByteACL(0xFF);
    receiveByteACL();
    P5->OUT |= BIT0;

    P5->OUT &= ~BIT0;
    sendByteACL(0x7E);
    sendByteACL(0x11);
    P5->OUT |= BIT0;

//    for(z = 0; z < 1;z++);

    P5->OUT &= ~BIT0;
    sendByteACL(0x7E);
    sendByteACL(0x15);
    P5->OUT |= BIT0;

//    P5->OUT &= ~BIT0;
//    sendByteACL(0x65);
//    sendByteACL(0x10);
//    P5->OUT |= BIT0;

//    P5->OUT &= ~BIT0;
//    sendByteACL(0x66);
//    sendByteACL(0x48);
//    P5->OUT |= BIT0;

    while(1){
    	throttle = (pointerval-5500)<<1;   //Sets to zero
    	yaw = (middleval-2505);            //3
    	roll = (ringval-2100);                  //
    	pitch = (pinkyval-2505);                //

    	if(yaw > (mid-1000) && yaw < (mid+1000)){
    	    yaw = mid;
    	}
    	else if(yaw < (mid-1000)){
    	    yaw += 1000;
    	}
    	else{
    	    yaw -= 1000;
    	}
        if(roll > (mid-1500) && roll < (mid+500)){
            roll = mid;
        }
        else if(roll < (mid-1500)){
            roll += 1500;
        }
        else{
            roll -= 500;
        }
        if(pitch > (mid-2000) && pitch < (mid-1000)){
            pitch = mid;
        }
        else if(pitch < (mid-2000)){
            pitch += 2000;
        }
        else{
            pitch += 1000;
        }
        if(throttle > 16380){
            throttle = 16380;
        }
//        P3->OUT &= ~BIT0;
//        sendByteDAC(0x30);
//        sendByteDAC(ii >> 6);
//        sendByteDAC(ii << 2);
//        P3->OUT |= BIT0;
    	sendDACinfo(throttle,yaw,roll,pitch);
    	/*
    	P5->OUT &= ~BIT0;
    	EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, (0x80 | 0x02)); // y address

    	EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, 0x0F);
    	//EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, 0x00);
    	//EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, 0x00);
    	P5->OUT |= BIT0;
    	*/
		//sendByteDAC(0x23);
    	ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;				// Enable the adc and start conversion

        P5->OUT &= ~BIT0;
        sendByteACL(0xE5);
        RXData = receiveByteACL();
        P5->OUT |= BIT0;

//        for(z = 0; z < 1;z++);

    }
}




