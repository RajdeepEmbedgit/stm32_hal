/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "max7219.h"
#include "max7219_digits.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

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
 SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
 uint8_t val = 0;
 uint8_t final;
 uint8_t cnt = 0;
 uint8_t value = 0;
 char msg[5] = {0};
 char msg2[5] = {0};
 uint8_t rand_val = 0;
 uint8_t rand_val_final;
 uint8_t val_setled = 0;
 uint8_t str_len = 0;
 uint8_t str_len2 = 0;
 uint8_t len_flag = 0;
 uint8_t len_flag2 = 0;
// float string_pass = 0.0;
 float string_pass_extr = 0.0;
// float string_pass2 = 0.0;
 float string_pass_extr2 = 0.0;

 int i = 0,j = 0,k=0,m = 0,n = 0;

 int numberArray[8];
 uint8_t maxDevice =1;

 volatile uint8_t displayColon = 0;

 uint8_t SYMBOLS[] = {
 		0x00,	// numeric 0
 		0x01,	// numeric 1
 		0x02,	// numeric 2
 		0x03,	// numeric 3
 		0x04,	// numeric 4
 		0x05,	// numeric 5
 		0x06,	// numeric 6
 		0x07,	// numeric 7
 		0x08,	// numeric 8
 		0x09,	// numeric 9
 		0x01,	// minus
 		0x4F,	// letter E
 		0x37,	// letter H
 		0x0E,	// letter L
 		0x67,	// letter P
 		0x00	// blank
 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

static uint8_t number_loop (void);
uint8_t getSymbol(uint8_t number);
uint8_t setLed(int state);
void hart_sendDataSPI(uint8_t reg, uint8_t data);
void InitSPI(void);
void MAX7219_DisplayDecimal(int v, int displaySeparator);

void apc_volt(float string_pass);
void apc_current(float string_pass2);

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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  max7219_Init(NUM_6);
  MAX7219_Init(&hspi1);
  InitSPI();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

/*	  value = number_loop();

	  if(value < 10)
	  {
		  final = getSymbol(value);

		  if(j < final)
		  {
			  k = j+1;
			  max7219_PrintDigit(k, final, 0);
			  HAL_Delay(200);
			  MAX7219_ClearAll();
			  j++;
		  }
		  else
		  {
			  j = 0;
		  }

//		  	  HAL_Delay(500);
	  }
	  else
	  {
		  for(i = -11; i < 22; i++)
			  	  {
			  		  MAX7219_ClearAll();
			  		  MAX7219_PutString(i, "Rajdeep");
			  		  HAL_Delay(200);
			  	  }

			  HAL_Delay(100);


			  MAX7219_PutStringCenterAdjust("HARTIANS");
			  HAL_Delay(500);
			  MAX7219_ClearAll();
	  }*/


//	  MAX7219_ClearAll();
/*

	  if(string_pass < 15.00 && len_flag == 0)
	  {
			  sprintf(msg,"%0.2f",string_pass);
//			  MAX7219_ClearAll();
			  MAX7219_PutStringLeftAdjust(msg);
			  str_len = strlen(msg);
			  string_pass+=0.02;
			  HAL_Delay(20);
			  string_pass_extr = string_pass;
	  }
	  else
	  {
//		  string_pass_extr = string_pass;
	  }

	  if(str_len <= 5)
	  {
		  	  if(string_pass_extr < 210.00)
		  	  {
//				  string_pass =
				  len_flag = 1;
				  sprintf(msg,"%0.01f",string_pass_extr);
				  //			  MAX7219_ClearAll();
				   MAX7219_PutStringLeftAdjust(msg);
				   string_pass_extr+=0.02;
				   HAL_Delay(10);
		  	  }
		  	else
		  	  {
		  		  string_pass = 0.0;
		  		  len_flag = 0;
		  	  }
	  }
	  else
	  {
//		  len_flag = 0;
	  }
*/

	  apc_volt(0.0);
	  apc_current(0.0);


//
//	  	  if(string_pass2 < 100.00)
//	  	  {
//	  			  sprintf(msg2,"%0.2f",string_pass2);
//	  			  MAX7219_PutString(4, msg2);
//	  			  string_pass2+=0.02;
////	  			  HAL_Delay(100);
//	  	  }
//	  	  else
//	  	  {
//	  		  string_pass2 = 0.0;
//	  	  }





/*

			if(i < 9)
			{
//				hart_sendDataSPI(i+1, numberArray[i]);
//				 MAX7219_ClearAll();
				val_setled = setLed(0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);
				max7219_SendData(4, Max7219_Digits[i]);
				i++;
				HAL_Delay(200);
			}
//			else if( i < 15)
//			{
//				setLed(1);
//				max7219_SendData(i+1, numberArray[i]);
//				i++;
//			}

			else
			{
				 MAX7219_ClearAll();
				i = 0;
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);
//				 HAL_Delay(200);
			}
*/

//			  HAL_Delay(1000);




//
//	  if(cnt < 1)
//	  {
//		  max7219_PrintDigit(DIGIT_3, NUM_0, cnt);
//		  cnt++;
//	  }
//	  else
//	  {
//		  max7219_PrintDigit(DIGIT_3, NUM_0, cnt);
//		  cnt = 0;
//	  }
//
//	  max7219_PrintDigit(DIGIT_6, LETTER_A, cnt);
//
//	  HAL_Delay(500);
//	  max7219_Clean();




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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_MAX7219_GPIO_Port, CS_MAX7219_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_MAX7219_Pin */
  GPIO_InitStruct.Pin = CS_MAX7219_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_MAX7219_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//
void InitSPI(void)
{
	// Set displays

	for(uint8_t j =0; j< maxDevice ; j++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // SELECT SLAVE
//		max7219_SendData(0x09,0xFF);  // Decode Mode --Code B decode for digits 7–0
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // END OF COMMUNICATION
	}
	for(uint8_t j =0; j< maxDevice ; j++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // SELECT SLAVE
//		max7219_SendData(0x0A,0x00);  // Intensity  --- low
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // END OF COMMUNICATION
	}
	for(uint8_t j =0; j< maxDevice ; j++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // SELECT SLAVE
//		max7219_SendData(0x0B,0x07);  // Scan Limit  --- 0-7
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // END OF COMMUNICATION
	}
	for(uint8_t j =0; j< maxDevice ; j++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // SELECT SLAVE
//		max7219_SendData(0x0C,0x01);  // Shutdown  --- no
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // END OF COMMUNICATION
	}
	for(uint8_t j =0; j< maxDevice ; j++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // SELECT SLAVE
//		max7219_SendData(0x0F,0x00);  // Display Test  --- no
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // END OF COMMUNICATION
	}


	MAX7219_ClearAll();

	numberArray[0]= 0;		//0x7E;
	numberArray[1]= 0;		//0x30;	// numeric 1;
	numberArray[2]= 0;		//0x6D;	// numeric 2;
	numberArray[3]= 0;		//0x79;	// numeric 3;
	numberArray[4]= 0;		//0x33;	// numeric 4;
	numberArray[5]= 0;		//0x5B;	// numeric 5;
	numberArray[6]= 0;		//0x5F;	// numeric 6;
	numberArray[7]= 0;		//0x70;	// numeric 7;
}


uint8_t setLed(int state)
{
	switch(state)
	{
		case 0:
			numberArray[0] +=1;
			if(numberArray[0] > 9)
			{
				numberArray[0]=0;
				numberArray[1] +=1;
			}

		break;
		case 1:
//			HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_7);
		numberArray[0] -=1;
		if(numberArray[0]<0)
			{
				numberArray[0]=9;
				numberArray[1] -=1;
			}
		break;
	}

}

void hart_sendDataSPI(uint8_t reg, uint8_t data)
{

		HAL_SPI_Transmit(&hspi1, (uint8_t*)&reg ,1, 1000);
		while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);  // wait untill spi be free
		HAL_SPI_Transmit(&hspi1, (uint8_t*)&data ,1, 1000);
		while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);  // waint untill spi be free

}


static uint8_t number_loop (void)
{

	val++;

	if(val < 10)
	{
		return val;
	}
	else {
		val = 0;
	}

	HAL_Delay(500);
}

uint8_t getSymbol(uint8_t number)
{
	return SYMBOLS[number];
}

void apc_volt(float string_pass)
{

	  if(string_pass < 15.00 && len_flag == 0)
	  {
			  sprintf(msg,"%0.2f",string_pass);
			  MAX7219_ClearAll();
			  MAX7219_PutStringLeftAdjust(msg);
			  str_len = strlen(msg);
			  string_pass+=0.02;
			  HAL_Delay(20);
			  string_pass_extr = string_pass;
	  }
	  else
	  {
//		  string_pass_extr = string_pass;
	  }

	  if(str_len <= 5)
	  {
		  	  if(string_pass_extr < 80.00)
		  	  {
//				  string_pass =
				  len_flag = 1;
				  sprintf(msg,"%0.01f",string_pass_extr);
				  //			  MAX7219_ClearAll();
				   MAX7219_PutStringLeftAdjust(msg);
				   string_pass_extr+=0.02;
				   HAL_Delay(10);
		  	  }
		  	else
		  	  {
		  		  string_pass = 0.0;
		  		  len_flag = 0;
		  	  }
	  }
	  else
	  {
//		  len_flag = 0;
	  }

}

void apc_current(float string_pass2)
{
	 if(string_pass2 < 15.00 && len_flag2 == 0)
		  {
				  sprintf(msg2,"%0.2f",string_pass2);
				  MAX7219_ClearAll();
				  MAX7219_PutString(4, msg2);
				  str_len2 = strlen(msg2);
				  string_pass2+=0.08;
				  HAL_Delay(20);
				  string_pass_extr2 = string_pass2;
		  }
		  else
		  {
	//		  string_pass_extr = string_pass;
		  }

		  if(str_len2 <= 5)
		  {
			  	  if(string_pass_extr2 < 610.00)
			  	  {
	//				  string_pass =
					  len_flag2 = 1;
					  sprintf(msg2,"%0.01f",string_pass_extr2);
					  //			  MAX7219_ClearAll();
					  MAX7219_PutString(4, msg2);
					   string_pass_extr2+=0.08;
					   HAL_Delay(10);
			  	  }
			  	else
			  	  {
			  		  string_pass2 = 0.0;
			  		  len_flag2 = 0;
			  	  }
		  }
		  else
		  {
	//		  len_flag = 0;
		  }

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
