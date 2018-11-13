/*
 * dac.c
 *
 *  Created on: Oct 29, 2018
 *      Author: Cary Goeller
 */

#include "dac.h"
#include "spi.h"
#include "gpio.h"
#include "interrupt.h"

extern const eUSCI_SPI_MasterConfig spiMasterConfig;

void initializeSPIDAC(void){
//	P1->DIR |= BIT5 | BIT6; 					// set P1.5 (SCLK) and P1.6 (SDI) as output
	P3->DIR |= BIT0;
//
//	P1->OUT = 0;
	P3->OUT |= BIT0;

	/* Starting and enabling LFXT (32kHz) */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
//    CS_setExternalClockSourceFrequency(32768, 0);
//    CS_initClockSignal(CS_ACLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
//    CS_startLFXT(CS_LFXT_DRIVE0);



	/* Selecting P1.5 P1.6 in SPI mode */
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
	GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7 , GPIO_PRIMARY_MODULE_FUNCTION);

	SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);

	/* Enable SPI module */
	SPI_enableModule(EUSCI_B0_BASE);
	EUSCI_B_SPI_masterChangeClock(EUSCI_B0_BASE, 500000,500000);
	/* Enabling interrupts */
	SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
	Interrupt_enableInterrupt(INT_EUSCIB0);

	int i;
	for(i=0;i<1000;i++);
}

void sendByteDAC(unsigned int val){
//	int i;
//	for(i = 0; i < 8; i++){
//		if(val & 0x80 == 0){
//			P1->OUT &= ~BIT6;
//		}
//		else {
//			P1->OUT |= BIT6;
//		}
//		P1->OUT |= BIT5;
//		P1->OUT &= ~BIT5;
//	}
	 EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, val);
}

void sendDACinfo(unsigned int throttle, unsigned int yaw,
		unsigned int roll, unsigned int pitch){
	unsigned int command = 0x00;
	unsigned int front; unsigned int back;
	unsigned int source;
	int i = 0;
	for(i = 0; i < 4; i++){
//		switch(i){
//		case 0: source = throttle; 	break;
//		case 1: source = yaw ;		break;
//		case 2: source = roll;		break;
//		case 3: source = pitch;
//		command = command | 0x20;
//		break;
//		}
		if(i==0){
			source = throttle;
			command = 0x00;
		}
		else if( i==1){
			source = yaw;
			command = 0x01;
		}
		else if (i == 2){
			source = roll;
			command = 0x02;
		}
		else if (i == 3){
			command |= 0x23;
			source = pitch;
		}
		P3->OUT &= ~BIT0;

		front = source >>6;					// 14 bit depth
		back = source << 2;
		//back  = source;
		sendByteDAC(command);
		sendByteDAC(front);
		sendByteDAC(back);
//		int j;
//		for(j=0; j < 6; j++){
//			if(source & 0x20 == 0){
//					P1->OUT &= ~BIT6;
//				}
//				else {
//					P1->OUT |= BIT6;
//				}
//				P1->OUT |= BIT5;
//				source = source >>1;
//				P1->OUT &= ~BIT5;
//		}
		command++;
		P3->OUT |= BIT0;
	}
}
//
//void EUSCIB0_IRQHandler(void)
//{
//    uint32_t status = SPI_getEnabledInterruptStatus(EUSCI_B0_BASE);
//    uint32_t jj;
//
//    SPI_clearInterruptFlag(EUSCI_B0_BASE, status);
//
//    if(status & EUSCI_B_SPI_RECEIVE_INTERRUPT)
//    {
//        /* USCI_B0 TX buffer ready? */
//        while (!(SPI_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT)));
//
//        //RXData = SPI_receiveData(EUSCI_B0_BASE);
//
//        /* Send the next data packet */
//        //SPI_transmitData(EUSCI_B0_BASE, ++TXData);
//
//        /* Delay between transmissions for slave to process information */
//        for(jj=50;jj<50;jj++);
//    }
//
//}





