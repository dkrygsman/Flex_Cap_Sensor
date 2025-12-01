/**
  ******************************************************************************
  * @file    fdc1004.c
  * @author  Daniel Krygsman
  * @brief   fdc1004 c file
  *
  ******************************************************************************
  *
  *
  ******************************************************************************
*/
#include <fdc1004.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"




/**
  * @brief
  *
  * @note
  *
  * @param
  * @param
  * @param
  * @retval None
  */
void fdc1004_init(I2C_HandleTypeDef *i2c)
{

	uint8_t buffer[12];
	HAL_StatusTypeDef status;
	uint8_t fdc1004_address = 0x50 << 1;

	// ****************************************************************************************************************************************************
	// I2C read from register 0xFF for FDC 1004 Device ID

	buffer[0] = 0xFF;
	status = HAL_I2C_Master_Transmit(i2c, fdc1004_address, buffer, 1, HAL_MAX_DELAY);
	if ( status != HAL_OK )
	{
		printf("TX Fail\r\n");
	}
	else
	{
		status = HAL_I2C_Master_Receive(i2c, fdc1004_address, buffer, 2, HAL_MAX_DELAY);
		if ( status != HAL_OK )
		{
			printf("RX Fail\r\n");
		}
		else
		{
			printf("FDC Dev ID Read Success!\r\n");
			//printf("%d\r\n", buffer[0]);
			//printf("%d\r\n", buffer[1]);
		}
	}

	// ****************************************************************************************************************************************************
	// I2C Write to Register 0x0C resetting FDC1004

	buffer[0] = 0x0c;
	buffer[1] = 0b10000000;
	buffer[2] = 0b00000000;
	status = HAL_I2C_Master_Transmit(i2c, fdc1004_address, buffer, 3, HAL_MAX_DELAY);
	if ( status != HAL_OK )
	{
		printf("TX Fail\r\n");
	}
	else
	{
		printf("FDC Config Reset Write Success!\r\n");
	}

	// ****************************************************************************************************************************************************
	// I2C Write to Register 0x0C, setting refresh rate to 100 S/s repeat sampling and enabling measure 1

	buffer[0] = 0x0c;
	buffer[1] = 0b00000101;
	buffer[2] = 0b10000000;
	status = HAL_I2C_Master_Transmit(i2c, fdc1004_address, buffer, 3, HAL_MAX_DELAY);
	if ( status != HAL_OK )
	{
		printf("TX Fail\r\n");
	}
	else
	{
		printf("FDC Config Write Success!\r\n");
	}

	// ****************************************************************************************************************************************************
	// I2C Read to Register 0x0C, the measurement config register

	buffer[0] = 0x0C;
	status = HAL_I2C_Master_Transmit(i2c, fdc1004_address, buffer, 1, HAL_MAX_DELAY);
	if ( status != HAL_OK )
	{
		printf("TX Fail\r\n");
	}
	else
	{
		status = HAL_I2C_Master_Receive(i2c, fdc1004_address, buffer, 2, HAL_MAX_DELAY);
		if ( status != HAL_OK )
		{
			printf("RX Fail\r\n");
		}
		else
		{
			printf("FDC Config Read Success!\r\n");
			//printf("%d\r\n", buffer[0]);
			//printf("%d\r\n", buffer[1]);
		}
	}



}

