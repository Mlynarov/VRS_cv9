/*
 * altitudePressure.h
 *
 *  Created on: 23. 12. 2021
 *      Author: Molnar & Nyiri
 *      www.st.com/en/mems-and-sensors/lps25hb.html
 */

#include "main.h"
#include "i2c.h"

#ifndef SENSORS_ALTITUDEPRESSURE_H_
#define SENSORS_ALTITUDEPRESSURE_H_

#define  LPS_DEVICE_ADDRESS		0xBB
#define  LPS_WHO_AM_I_DEFAULT	0xBD
#define  LPS_WHO_AM_I			0x0F
#define	 LPS_CTRL_REG1_SETUP	0x90
#define	 LPS_CTRL_REG1			0x20
#define	 LPS_STATUS_REG			0x27
#define	 LPS_PRESS_OUT_XL		0x28
#define	 LPS_PRESS_OUT_L		0x29
#define	 LPS_PRESS_OUT_H		0x2A

uint8_t altPress_read_byte(uint8_t reg_addr);
void altPress_readArray(uint8_t * data, uint8_t reg, uint8_t length);
void altPress_write_byte(uint8_t reg_addr, uint8_t value);
uint8_t pressure_init(void);

float get_pressure();
int16_t get_altitude();

#endif /* SENSORS_ALTITUDEPRESSURE_H_ */


