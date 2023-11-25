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
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "pcf8574.h"
#include "uart_apc.h"

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
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN PV */


#define R3 0X80
#define R2 0x40
#define R1 0X20
#define R0 0x10

#define C3 0X00
#define C2 0x00
#define C1 0X00
#define C0 0x00

#define ROWS 4
#define COLS 4

const char keymap2[4][4] = {
  {'E','F','G','H'},
  {'I','J','K','L'},
  {'M','N','O','P'},
  {'Q','R','S','T'}
};

uint8_t keyx;


/////////////////////////////////////////////////////////////////////////////////


	const char keymap[4][4] = {
							  {'1','2','3','A'},
		  	  	  	  	  	  {'4','5','6','B'},
							  {'7','8','9','C'},
							  {'*','0','#','D'}
	};

 const char columnMask[4]; //= { 2, 1, 3, 4 };	//column select values


 char keypad_val;
 char keypad_val2;

 uint8_t val;
 uint8_t final_key_val = 0;

 uint8_t val2;
 uint8_t final_key_val2 = 0;

 uint8_t key1_flag = 0;
 uint8_t key2_flag = 0;

 uint8_t key_scan_flag1 = 0;
 uint8_t key_scan_flag2 = 0;

 //////////////////////////////////////////////
 char j = 0;
 	char k = 0;
 	uint8_t temp;
 	uint8_t temp_2;
 	uint8_t final_col[1] = {0};
 	uint8_t final_col2[1] = {0};
 	uint8_t a = 0;
/////////////////////////////////////////////////

 	 uint8_t data;
 	uint8_t rdata[1] = {0};
 	 uint8_t rdata2[1] = {0};
 	 uint8_t receieve_data = 0;

 	 char keypad_char_value;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void master_write(void);
char keypad_i2c(void);
char scan(void);
void uart_key_print(char val);

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
  MX_I2C2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  uart3_pin_conf();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  master_write();
	  keypad_char_value = keypad_i2c();
	  uart_key_print(keypad_char_value);
//	  keypad_char_value = '0';

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

/* USER CODE BEGIN 4 */


void master_write(void)
{

	uint8_t i = 0;
	uint8_t tx_data[4] = {0xAA,0x13,0xFF,0xDD};
	uint8_t tx_data2[4] = {0xAA,0x91,0xA7,0xDD};
	uint8_t tx_data3[4] = {0xAA,0x13,0x86,0xDD};
//	uint8_t tx_data4[4] = {0xAA,0x13,0xF6,0xDD};
//	uint8_t tx_data5[4] = {0xAA,0x93,0xA2,0xDD};

	for (i = 0; i < 4; i++)
	{
		HAL_SPI_Transmit(&hspi1, &tx_data[i], sizeof(tx_data[i]), 1000);
	}

	HAL_Delay(30);


	for (i = 0; i < 4; i++)
		{
			HAL_SPI_Transmit(&hspi1, &tx_data2[i], sizeof(tx_data2[i]), 1000);
		}
	HAL_Delay(10);

	for (i = 0; i < 4; i++)
			{
				HAL_SPI_Transmit(&hspi1, &tx_data3[i], sizeof(tx_data3[i]), 1000);
			}
		HAL_Delay(30);

//		for (i = 0; i < 4; i++)
//				{
//					HAL_SPI_Transmit(&hspi1, &tx_data4[i], sizeof(tx_data4[i]), 1000);
//				}
//			HAL_Delay(50);
//
//
//			for (i = 0; i < 4; i++)
//					{
//						HAL_SPI_Transmit(&hspi1, &tx_data5[i], sizeof(tx_data5[i]), 1000);
//					}
//				HAL_Delay(50);


				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
}


char keypad_i2c(void)
{

	///////////////////////////////  Transmit & Recieve I2C for 8pins 4x4 Matrix  /////////////////////////////////
		  if(HAL_I2C_IsDeviceReady(&hi2c2,64,1, 100) == HAL_OK)
		    {

			  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

		    	  data = 0x0F;

		    		  j++;
		    		  if(j < 5)
		    		  {
						  data &= ~(0xF0 >> j);
						  temp = data;
						  temp &= 0x07;
						  if(j == 1)
						  {
							  temp = data + 7;
						  }
						  else if(j == 2)
						  {
							  temp = data + 4;
						  }
						  else if(j == 3)
						  {
							  temp = data + 10;
						  }
						  else if(j == 4)
						  {
							  temp = data + 13;
						  }

						  final_col[0] = temp + 240;

						  HAL_I2C_Master_Transmit(&hi2c2, 65, final_col, 1, 100);



						  HAL_I2C_Master_Receive(&hi2c2, 64, rdata, sizeof(rdata), 100);

						  key_scan_flag1 = 1;

		    		   }
		    		  else
		    		  {
		    			  j = 0;
		    		  }



		    	  keypad_val = scan();

//		    	  USART_write(keypad_val);
	//
		    	  HAL_Delay(1);
		    }
		  /////////////////////////////////////////////////////////////////////////////////////////////////////

		  return keypad_val;

}



char scan(void)
{

	val = rdata[0];

	key1_flag = 1;

	if(val < 247)
	{
		final_key_val = val;
	}

		  		switch(final_key_val)
		  		{
		  			case 119:	return keymap[0][0];	//first row pressed
		  			case 123:	return keymap[0][1];	//first row pressed
		  			case 125:	return keymap[0][2];	//first row pressed
		  			case 126:	return keymap[0][3];	//first row pressed

		  			case 183:	return keymap[1][0];	//first row pressed
		  			case 187:	return keymap[1][1];	//first row pressed
		  			case 189:	return keymap[1][2];	//first row pressed
		  			case 190:	return keymap[1][3];	//first row pressed

		  			case 215:	return keymap[2][0];	//third row pressed
		  			case 219:	return keymap[2][1];	//third row pressed
		  			case 221:	return keymap[2][2];	//third row pressed
		  			case 222:	return keymap[2][3];	//third row pressed

		  			case 231:	return keymap[3][0];	//third row pressed
		  			case 235:	return keymap[3][1];	//third row pressed
		  			case 237:	return keymap[3][2];	//third row pressed
		  			case 238:	return keymap[3][3];	//third row pressed

		  			default:	break;					//no pressed button found on this column
		  		}

	 return 0;	//no button pressed => blank 7 segment
}

void uart_key_print(char val)
{
	uint8_t char_to_unsign = 0;

	while(val == '0')
	{
		 char_to_unsign = (uint8_t)atoi(val);
//		 HAL_UART_Transmit(&huart2, (uint8_t*)char_to_unsign, sizeof(char_to_unsign),1000);
		 USART_write(val);
		 break;
	}
	while(val == '1')
		{
//			HAL_UART_Transmit(&huart2,val, sizeof(val),1000);
			 USART_write(val);
			 break;
		}
	while(val == '2')
		{
//			HAL_UART_Transmit(&huart2, (uint8_t*)val, sizeof(val),1000);
			 USART_write(val);
			 break;
		}
	while(val == '3')
		{
//			HAL_UART_Transmit(&huart2, (uint8_t*)val, sizeof(val),1000);
			 USART_write(val);
			 break;
		}
	while(val == '4')
		{
//			HAL_UART_Transmit(&huart2, (uint8_t*)val, sizeof(val),1000);
			 USART_write(val);
			 break;
		}
	while(val == '5')
		{
//			HAL_UART_Transmit(&huart2, (uint8_t*)val, sizeof(val),1000);
			 USART_write(val);
			 break;
		}
	while(val == '6')
		{
//			HAL_UART_Transmit(&huart2, (uint8_t*)val, sizeof(val),1000);
			 USART_write(val);
			 break;
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
