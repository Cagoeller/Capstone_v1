/*
 * adc.h
 *
 *  Created on: Oct 11, 2018
 *      Author: Cary Goeller
 */

#ifndef ADC_H_
#define ADC_H_

#include "msp.h"
#include <stdint.h>

#define   Num_of_Results   8

void ConfigureADC(void);

void ADC14_IRQHandler(void);

#endif /* ADC_H_ */
