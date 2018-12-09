/*
 * acl.h
 *
 *  Created on: Nov 13, 2018
 *      Author: Cary Goeller
 */

#ifndef TARGETCONFIGS_ACL_H_
#define TARGETCONFIGS_ACL_H_

/*
 * Accelerometer and gyro combo BMI 160
 *
 * Initiate SPI mode for the Accel in place of I2C, rising edge on CSB(pin12 on accel)  after startup
 * Max clock frequency is 10 MHz
 *
 * Currently using 3 wire mode where the sdi is both the input and the output
 * CSB pulled low initiates spi with SCLK high
 * Message is sent including which register to read from
 * then after the 8th bit (1 RW bit and 7 control bits)
 * message is sent from specfifed register
 * finally CSB should be raise high
 *
 * P3.5	sclk
 * P3.6 SDI
 * P3.7 SDO
 * P5.0 CSE
 */

void initializeSPIACL(void);

void sendByteACL(unsigned int val);
unsigned char receiveByteACL(void);



#endif /* TARGETCONFIGS_ACL_H_ */
