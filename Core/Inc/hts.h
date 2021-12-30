/*
 * hts.h
 *
 *  Created on: 22. 12. 2021
 *      Author: Molnar & Nyiri
 *
 *      Cerpane z
 *      https://www.st.com/resource/en/datasheet/hts221.pdf
 *      strana 20.
 */

#ifndef SENSORS_HTS_H_
#define SENSORS_HTS_H_



#endif /* SENSORS_HTS_H_ */


#include "main.h"
#include "i2c.h"

#define HTS_ADDRESS					0xBE
#define HTS_WHO_AM_I_DEFAULT		0xBC
#define HTS_WHO_AM_I				0x0F

#define HTS_CTRL_REG1				0x20
#define HTS_CTRL_REG_SETUP			0x81
#define HTS_STATUS_REG				0x27
#define HTS_TO_DEGC_REG				0x32
#define HTS_MSB_T1_T0				0x35

#define HTS_T0_OUT					0x3C
#define HTS_T1_OUT					0x3E
#define HTS_T_OUT_Low				0x2A
#define	HTS_T_OUT_High				0x2B//znamienko teploty 1=minusova teplota, 0 kladna teplota

#define	HTS_H0_RH_X2				0x30
#define	HTS_H0_T0_OUT_L				0x36
#define	HTS_H1_T0_OUT_L				0x3A
#define HTS_H_OUT					0x28

uint8_t hts_sensore_init(void);
uint8_t temperature_read_byte(uint8_t reg_addr);
void temperature_readArray(uint8_t * data, uint8_t reg, uint8_t length);
void temperature_write_byte(uint8_t reg_addr, uint8_t value);
int16_t HTS221_Get_Temperature();

/*uint8_t humidity_read_byte(uint8_t reg_addr);
void humidity_readArray(uint8_t * data, uint8_t reg, uint8_t length);
void humidity_write_byte(uint8_t reg_addr, uint8_t value);*/
int16_t HTS221_Get_Humidity();
