/*
 * temperature.c
 *
 *  Created on: 22. 12. 2021
 *      Author: Molnar & Nyiri
 *	Cerpane z
 *	(strana 7)
 *	https://www.st.com/resource/en/technical_note/tn1218-interpreting-humidity-and-temperature-readings-in-the-hts221-digital-humidity-sensor-stmicroelectronics.pdf
 *
 */

#include "hts.h"

uint8_t hts221_addres = HTS_ADDRESS;

uint8_t temperature_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, hts221_addres, 0));
}


void temperature_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, hts221_addres, 1);
}

void temperature_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, hts221_addres, 0);
}

uint8_t temperature_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = temperature_read_byte(HTS221_WHO_AM_I	);

	if(val == HTS221_WHO_AM_I_DEFAULT)
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
	temperature_write_byte(HTS221_CTRL_REG1, ctrl1);

	return status;
}

int16_t HTS221_Get_Temperature()
{
 int16_t T0_out, T1_out, T_out, T0_degC_x8_u16, T1_degC_x8_u16;
 int16_t T0_degC, T1_degC, value;
 uint8_t buffer[4], tmp;
 int32_t tmp32;

/*1. Read from 0x32 & 0x33 registers the value of coefficients T0_degC_x8 and T1_degC_x8*/
 temperature_readArray(buffer,HTS221_TO_DEGC_REG,2);

/*2. Read from 0x35 register the value of the MSB bits of T1_degC and T0_degC */
 tmp=temperature_read_byte(HTS221_MSB_T1_T0);


/*Calculate the T0_degC and T1_degC values*/
 T0_degC_x8_u16 = (((uint16_t)(tmp & 0x03)) << 8) | ((uint16_t)buffer[0]);
 T1_degC_x8_u16 = (((uint16_t)(tmp & 0x0C)) << 6) | ((uint16_t)buffer[1]);
 T0_degC = T0_degC_x8_u16>>3;
 T1_degC = T1_degC_x8_u16>>3;

/*3. Read from 0x3C & 0x3D registers the value of T0_OUT*/
 temperature_readArray(buffer,HTS221_T0_OUT,4 );
 T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

 /*4. Read from 0x3E & 0x3F registers the value of T1_OUT*/
 temperature_readArray(buffer,HTS221_T1_OUT,4 );
 T1_out = (((uint16_t)buffer[3])<<8) | (uint16_t)buffer[2];

/* 5.Read from 0x2A & 0x2B registers the value T_OUT (ADC_OUT).*/
 temperature_readArray(buffer,HTS221_T0_OUT,2 );
 T_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];


/* 6. Compute the Temperature value by linear interpolation*/
 tmp32 = ((int32_t)(T_out - T0_out)) * ((int32_t)(T1_degC - T0_degC)*10);
 value = tmp32 /(T1_out - T0_out) + T0_degC*10;

// temperature_write_byte(HTS221_CTRL_REG1,value);//neni som si isty reg_addresou
 return value;
}



