/*
 * altitudePressure.c
 *
 *  Created on: 23. 12. 2021
 *       Author: Molnar & Nyiri
 */

#include "altitudePressure.h"
#include <math.h>

uint8_t LPS_addres = LPS_DEVICE_ADDRESS	;

uint8_t altPress_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, LPS_addres, 0));
}


void altPress_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, LPS_addres, 1);
}

void altPress_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, LPS_addres, 0);
}

uint8_t pressure_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = altPress_read_byte(LPS_WHO_AM_I);

	if(val == LPS_WHO_AM_I_DEFAULT)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
			status = 0;
			//return status;
	}

	//acc device init

	altPress_write_byte(LPS_CTRL_REG1, LPS_CTRL_REG1_SETUP);

	return status;
}

float get_pressure()
{
 uint8_t pressure_low,pressure_mid,pressure_high;
 float pressure,tmp=0;

 pressure_low=LPS_PRESS_OUT_XL;
 pressure_mid= LPS_PRESS_OUT_L;
 pressure_high=LPS_PRESS_OUT_H;

 //vypocitanie tlaku strana 15 v datasheete uvedenom v altitudePressure.h
 tmp=pressure_high << 16|pressure_mid<<8|pressure_low;
 pressure=tmp/4096;

 return pressure;
}

int16_t get_altitude(){
	//https://physics.stackexchange.com/questions/333475/how-to-calculate-altitude-from-current-temperature-and-pressure
	//H = altitude (m)
	//P = measured pressure (Pa) from the sensor
	//p0 = reference pressure at sea level (e.g. 1013.25hPa)
	//altitude = 44330 *(1 - (P/p0)^(1/5.255));

	float p0=1013.25;
	float P=get_pressure();
	float altitude;
	float result;

	result=powf((P/p0),(1/5.255));// powf mocnitel floatu neviem ale ci nebude lepsie to prehodit na int a normalne to umocnit


	altitude = 44330 *(1 - result);

	return altitude;
}
