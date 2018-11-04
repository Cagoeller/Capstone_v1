/*
 * dac.c
 *
 *  Created on: Oct 29, 2018
 *      Author: Cary Goeller
 */

#include "dac.h"

void initializeSPIDAC(void){
	P1->DIR |= BIT5 | BIT6; 					// set P1.5 (SCLK) and P1.6 (SDI) as output
	P3->DIR |= BIT0;

	P1->OUT = 0;
	P3->OUT |= BIT0;
}

void sendByteDAC(unsigned int val){
	int i;
	for(i = 0; i < 8; i++){
		if(val & 0x80 == 0){
			P1->OUT &= ~BIT6;
		}
		else {
			P1->OUT |= BIT6;
		}
		P1->OUT |= BIT5;
		P1->OUT &= ~BIT5;
	}
}

void sendDACinfo(unsigned int throttle, unsigned int yaw,
		unsigned int roll, unsigned int pitch){
	unsigned int command = 0x00;
	unsigned int front; unsigned int back;
	unsigned int source;
	int i = 0;
	for(i = 0; i < 4; i++){
		switch(i){
		case 0: source = throttle; 	break;
		case 1: source = yaw ;		break;
		case 2: source = roll;		break;
		case 3: source = pitch;
		command |= 0x20;
		break;
		}
//		if (i == 3){
//			command |= 0x20;
//		}
		P3->OUT &= ~BIT0;
		sendByteDAC(command);
		front = source >>8;
		back  = source;

	}
}







