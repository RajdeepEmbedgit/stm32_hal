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
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"i2c-lcd.h"
#include"UartRingbuffer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t text[10] = "WELCOME \n";
uint8_t num_of_byte = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

char time[10];
char date[10];
uint16_t position;
char buffer[20],buffer2[3];
char hex[5],start=1,end=1;
int data,k,j,cnt,status;
uint8_t hrs=0x10,min=0x32,sec=0x21,dt=0x01,mnth=0x01,yr=0x16;
int dataChar=0;
uint8_t num=0;
int bFlag = 0;
int iDataCounter=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void decToHexa(int n);

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
///////////////////////////////////////////////////////////////////////////////////////////////////////
void set_time (void)
{
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

  sTime.Hours = hrs;	// hour; // set hours
  sTime.Minutes = min; // set minutes
  sTime.Seconds = sec; // set seconds
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
	  Error_Handler();
  }

    sDate.WeekDay = RTC_WEEKDAY_MONDAY; //day
    sDate.Month = mnth;		//0x05;			//RTC_MONTH_MAY; //month
    sDate.Date = dt;		//0x16; 			// date
    sDate.Year = yr;		//0x22; 			// year
    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
    	Error_Handler();
    }
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // backup register
}


void get_time(void)
{
 RTC_DateTypeDef gDate;
 RTC_TimeTypeDef gTime;
// Get the RTC current Time
 HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
// Get the RTC current Date
 HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
// Display time Format: hh:mm:ss
 //sprintf((char*)time,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);
 //gTime.Hours=hrs;		// Set hour via usart
 //gTime.Minutes = min;	// Set min via usart
 //gTime.Seconds = sec;	// Set sec via usart
 sprintf((char*)time,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);
 //Display date Format: dd-mm-yy
 sprintf((char*)date,"%02d-%02d-%02d",gDate.Date, gDate.Month, 2000 + gDate.Year);
 }


void display_time (void)
{

 lcd_clear();
 lcd_send_cmd (0x80); // send cursor to 0,0
 lcd_send_string (time);
 lcd_send_cmd (0xc0); // send cursor to 1,0
 lcd_send_string (date);
 hrs=min=sec=0;
 dt=mnth=yr=0;
}

void setCursor(int a, int b)
{
	int i=0;
	switch(b){
	case 0:lcd_send_cmd(0x80);break;
	case 1:lcd_send_cmd(0xC0);break;
	case 2:lcd_send_cmd(0x94);break;
	case 3:lcd_send_cmd(0xd4);break;}
	for(i=0;i<a;i++)
	lcd_send_cmd(0x14);
}


int charToInt(char* c,int j){

	 int i=0;
	 switch(j){
	 	 case 0:
	 		 i = (*c - 48)*10;
	 		 break;
	 	 case 1:
	 		 i = *(c+1)-48;

	 		 break;

	 	 default:
	 		 break;
	 }
	return i;

}

///////////////////////////////////////////////////////////////////////////////////////


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
  MX_USART3_UART_Init();
  MX_I2C2_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();
  Ringbuf_init();


 // lcd_send_string("**** HELLO ****");
  set_time();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if(iDataCounter >= 8)
	  {
	  	//c = buffer[1];

	  	hrs += (buffer[0] - 48)*10;
	  	hrs += (buffer[1]-48);

	  	min += (buffer[3] - 48)*10;
   	  	min += (buffer[4]-48);

		sec += (buffer[6] - 48)*10;
	  	sec += (buffer[7]-48);

	  			dt += (buffer[9] - 48)*10;
	  		  	dt += (buffer[10]-48);

	  		  	mnth += (buffer[12] - 48)*10;
	  	   	  	mnth += (buffer[13]-48);

	  			yr += (buffer[17] - 48)*10;
	  		  	yr += (buffer[18]-48);

	  	iDataCounter=0;
	  	set_time();
	  }


	  get_time();
	  display_time();

	//  for(k=0;k<9;k++) 	  buffer2[k]=0 ;
	  HAL_Delay(800);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
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
