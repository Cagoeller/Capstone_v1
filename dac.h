/*
 * dac.h
 *
 *  Created on: Oct 22, 2018
 *      Author: Cary Goeller
 */

#ifndef DAC_H_
#define DAC_H_

#include "msp.h"
#include <stdint.h>

/* Our DAC is the LTC2614, with a precision of 14 bits
 *
 * message broken into 4 bits of the command, 4 bit address then
 * 14 data bits with 2 don't care bits
 * everything is read on the rising edge of the SCLK
 *
 * cs/LD must be low in order to load in command, switch to high to execute command
 * Sck - the clock
 * SDI - data input
 * CS/LD - 	P3.0
 * SDI -> 	P1.6
 * SCLK -> 	P1.5
 */




void initializeSPIDAC(void);

void sendByte(unsigned int val);




#endif /* DAC_H_ */
