/*
 * lps25hb.h
 *
 *  Created on: Dec 15, 2021
 *      Author: Molnar a Nyiri
 */

#ifndef INC_LPS25HB_H_
#define INC_LPS25HB_H_

#include "main.h"
#include "i2c.h"


#define 	LSM6DS0_DEVICE_ADDRESS_0				0xD4
#define 	LSM6DS0_DEVICE_ADDRESS_1				0xD6

#define 	LSM6DS0_WHO_AM_I_VALUE					0x68
#define 	LSM6DS0_WHO_AM_I_ADDRES					0x0F

#define 	LSM6DS0_ADDRESS_CTRL1					0x10

#define 	LSM6DS0_ADDRESS_ACCX					0x28
#define 	LSM6DS0_ADDRESS_ACCY					0x2A
#define 	LSM6DS0_ADDRESS_ACCZ					0x2C

#define 	LSM6DS0_ADDRESS_TEMP_L					0x20

uint8_t lsm6ds0_init(void);
void lsm6ds0_get_acc(float* x, float * y, float * z);
uint8_t lsm6ds0_read_byte(uint8_t reg_addr);
void lsm6ds0_write_byte(uint8_t reg_addr, uint8_t value);
int8_t lsm6ds0_get_temp();

#endif /* INC_LPS25HB_H_ */
