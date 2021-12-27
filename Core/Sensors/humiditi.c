/*
 * huminiti.c
 *
 *  Created on: 23. 12. 2021
 *      Author: Molnar & Nyiri
 *	Cerpane z
 *	(strana 7)
 *	https://www.st.com/resource/en/technical_note/tn1218-interpreting-humidity-and-temperature-readings-in-the-hts221-digital-humidity-sensor-stmicroelectronics.pdf
 */

#include "hts.h"

humiditiS_addres=HTS_ADDRESS;

uint8_t humidity_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, humiditiS_addres, 0));
}


void humidity_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, humiditiS_addres, 1);
}

void humidity_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, humiditiS_addres, 0);
}


uint8_t humidity_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = humidity_read_byte(HTS_WHO_AM_I	);

	if(val == HTS_WHO_AM_I_DEFAULT)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
			status = 0;
			//return status;
	}

	//acc device init

	uint8_t ctrl1 = 8 << 4; // +-2g res
	humidity_write_byte(HTS_CTRL_REG1, ctrl1);

	return status;
}

int16_t HTS221_Get_Humidity()
{
	int16_t H0_T0_out, H1_T0_out, H_T_out;
	int16_t H0_rh, H1_rh,value;
	uint8_t buffer[2];
	int32_t tmp;

/* 1. Read H0_rH and H1_rH coefficients*/

	humidity_readArray(buffer,HTS_H0_RH_X2,2);
	H0_rh = buffer[0]>>1;
	H1_rh = buffer[1]>>1;
/*2. Read H0_T0_OUT */

	humidity_readArray(buffer,HTS_H0_T0_OUT_L,2);
	H0_T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

/*3. Read H1_T0_OUT */
	humidity_readArray(buffer,HTS_H1_T0_OUT_L,2);
	H1_T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

/*4. Read H_T_OUT */

	humidity_readArray(buffer,HTS_H_OUT,2);
	H_T_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

/*5. Compute the RH [%] value by linear interpolation */

	tmp = ((int32_t)(H_T_out - H0_T0_out)) * ((int32_t)(H1_rh - H0_rh)*10);
	value = (tmp/(H1_T0_out - H0_T0_out) + H0_rh*10);//delenie bacha nan :D


/* Saturation condition*/
	if(value>1000) {
		value = 1000;
	}

	return value;
}
