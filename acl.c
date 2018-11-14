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

	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);

	/* Selecting P3.5 P3.6 P3.7 in SPI mode */
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
	GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7 , GPIO_PRIMARY_MODULE_FUNCTION);

	SPI_initMaster(EUSCI_B2_BASE, &spiMasterConfig);

	SPI_enableModule(EUSCI_B2_BASE);
	EUSCI_B_SPI_masterChangeClock(EUSCI_B2_BASE, 500000,500000);
	/* Enabling interrupts */
	//SPI_enableInterrupt(EUSCI_B2_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
	//Interrupt_enableInterrupt(INT_EUSCIB2);

	int i;
	for(i=0;i<1000;i++);
}

