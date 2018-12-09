/*
 * acl.c
 *
 *  Created on: Nov 13, 2018
 *      Author: Cary Goeller
 */

#include "msp.h"
#include "acl.h"
#include "spi.h"
#include "gpio.h"
#include "interrupt.h"
#include <stdint.h>

extern const eUSCI_SPI_MasterConfig spiMasterConfig;

void initializeSPIACL(void){
	P5->DIR |= BIT0;
	P5->OUT |= BIT0;
//	P3->OUT |= BIT6;
//	P3->DIR &= ~BIT6;
	P3->OUT |= BIT5 | BIT7;
	P3->DIR |= BIT5 | BIT7;

	/* Selecting P3.5 P3.6 P3.7 in SPI mode */
	GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN6);
//
//    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN5 | GPIO_PIN7 , GPIO_PRIMARY_MODULE_FUNCTION);
//
//	SPI_initMaster(EUSCI_B2_BASE, &spiMasterConfig);
//	SPI_enableModule(EUSCI_B2_BASE);
//	EUSCI_B_SPI_masterChangeClock(EUSCI_B2_BASE, 500000,500000);

	/* Enabling interrupts */
//	SPI_enableInterrupt(EUSCI_B2_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
//	Interrupt_enableInterrupt(INT_EUSCIB2);

	int i;
	for(i=0;i<1000;i++);
}

void sendByteACL(unsigned int val){
//     EUSCI_B_SPI_transmitData(EUSCI_B2_BASE, val);
        int i = 0;
        unsigned char byte = val;

         P3->OUT &= ~BIT5;
         for(i = 0;i < 8;i++){
            if(byte>>7 == 1){
                P3->OUT |= BIT7;
            }
            else{
                P3->OUT &= ~BIT7;
            }
            byte = byte<<1;
            P3->OUT ^= BIT5;
//            int z = 0;
//            while(z < 10){
//                z++;
//            }
            P3->OUT ^= BIT5;
         }
//         P3->OUT &= ~BIT7;
//         P3->OUT &= ~BIT5;
}

unsigned char receiveByteACL(void)
{

    unsigned int i = 0;
    unsigned char received = 0;
    P3->OUT &= ~BIT5;

    for(i = 0;i < 8;i++){
        unsigned char MISO = P3->IN & BIT6;
        MISO = MISO>>6;
        received = received<<1;
        received |= MISO;
        P3->OUT ^= BIT5;
//        int z = 0;
//        while(z < 10){
//            z++;
//        }
        P3->OUT ^= BIT5;
    }
    return received;
}
