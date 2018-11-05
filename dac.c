/*
 * dac.c
 *
 *  Created on: Oct 29, 2018
 *      Author: Cary Goeller
 */

#include "dac.h"
#include "spi.h"

void initializeSPIDAC(void){
	P1->DIR |= BIT5 | BIT6; 					// set P1.5 (SCLK) and P1.6 (SDI) as output
	P3->DIR |= BIT0;

	P1->OUT = 0;
	P3->OUT |= BIT0;
}

void sendByteDAC(unsigned int val){
	int i;
	for(i = 0; i < 8; i++){
		if(val & 0x80 != 0){
			P1->OUT |= BIT6;
		}
		else {
			P1->OUT &= ~BIT6;
		}
		P1->OUT |= BIT5;
		val = val >>1;

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







