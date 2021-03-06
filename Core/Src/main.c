/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "display.h"
#include "lps25hb.h"
#include "altitudePressure.h"
#include "hts.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t temp = 0;
float mag[3], acc[3];
char displayText[15];
uint8_t mode = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  //LL_TIM_EnableIT_CC2(TIM2);
  LL_TIM_EnableIT_UPDATE(TIM2);
  LL_TIM_EnableCounter(TIM2);

  uint8_t htsSensorStatus = hts_sensore_init();
  uint8_t pressureSensorStatus = pressure_init();

  resetAllDigits();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //lsm6ds0_get_acc(acc, (acc+1), (acc+2));
	  if(mode == 0){
		  if(htsSensorStatus == 1){
			  printTemperature();
		  }
		  else if(htsSensorStatus == 0){
			  mode +=1;
		  }
	  }
	  else if(mode == 1){
		  if(htsSensorStatus == 1){
			  printHumidity();
		  }
		  else if(htsSensorStatus == 0){
			  mode +=1;
		  }
	  }
	  else if(mode == 2){
		  if(pressureSensorStatus == 1){
			  printPressure();
		  }
		  else if(pressureSensorStatus == 0){
			  mode +=1;
		  }
	  }
	  else if(mode == 3){
		  if(pressureSensorStatus == 1 && htsSensorStatus == 1){
			  printAltitude();
		  }
		  else if(pressureSensorStatus == 0 || htsSensorStatus == 0){
			  mode +=1;
		  }
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_Init1msTick(8000000);
  LL_SetSystemCoreClock(8000000);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
}

/* USER CODE BEGIN 4 */
void printTemperature(void){
	char valueString[15];
	int16_t temperature = HTS221_Get_Temperature();
	sprintf(valueString, "%d", temperature);
	memset(displayText, '\0', 15);
	strcat(displayText, "tEMP_");
	if(valueString[0]=='-'){
		strncat(displayText, valueString, 3);
		strcat(displayText, ".");
		strncat(displayText, &valueString[3],1);
	}
	else if(temperature > 999){
		strcat(displayText, "99.9");
	}
	else if(temperature < (-999)){
		strcat(displayText, "-99.9");
	}
	else{
		strncat(displayText, valueString, 2);
		strcat(displayText, ".");
		strncat(displayText, &valueString[2],1);
	}
	setDisplayText(displayText);
}

void printHumidity(void){
	char valueString[15];
	int16_t humidity = HTS221_Get_Humidity();
	sprintf(valueString, "%d", humidity);
	memset(displayText, '\0', 15);
	strcat(displayText, "HUM_");
	strncat(displayText, valueString, 2);
	setDisplayText(displayText);
}

void printPressure(void){
	char valueString[15];
	float pressure = 0;
	pressure = (float)get_pressure();
	gcvt(pressure, 6, valueString);
	memset(displayText, '\0', 15);
	strcat(displayText, "bar_");
	strcat(displayText, valueString);
	setDisplayText(displayText);
}

void printAltitude(void){
	char valueString[15];
	int16_t temperature = HTS221_Get_Temperature();
	float pressure = (float)get_pressure();

	float tempVar1 = powf((1013.25/pressure),1/5.257)-1;
	float tempVar2 = (float)temperature/10+273.15;
	float altitude = (tempVar1*tempVar2)/0.0065;

	memset(displayText, '\0', 15);
	int altitudeInt = (int)floor(10*altitude);
	if(altitudeInt>=0){
		sprintf(valueString, "%05d", altitudeInt);
		strcat(displayText, "ALt_");
		strncat(displayText, valueString, 4);
		strcat(displayText, ".");
		strncat(displayText, &valueString[4],1);
	}
	else if(altitudeInt<0){
		sprintf(valueString, "%06d", altitudeInt);
		strcat(displayText, "ALt_");
		strncat(displayText, valueString, 5);
		strcat(displayText, ".");
		strncat(displayText, &valueString[5],1);
	}
	setDisplayText(displayText);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
