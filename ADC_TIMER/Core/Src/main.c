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
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "reg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RES 						100
#define CURRENT_SETPOINT			325000
#define BACK_EMF					1.65
#define K 							1000
#define	RES_MIN						0.0
#define RAWRES_WINDOW				1800
#define ONE_MINUTE					600
#define THREE_MINUTE				1800
#define ONE_H_MSEC					1




void uprintf(char *str);
float Raw_volt_adc(void);
float Raw_volt_Avg (void);
float RAW_VOLTAGE (void);
float Raw_Current_adc(void);
float Raw_Current_Avg (void);
float Raw_Resistance(void);
float Sum_Raw_Res (void);
float Smooth_Resistance(void);
float SumSmooth_Resistance(void);
void convert_avg(char* outStr);
char store_char(void);



void ADC_Select_CH0 (void);
void ADC_Select_CH1 (void);


extern ADC_HandleTypeDef hadc2;

uint16_t m = 0;
uint16_t cnt = 0,cnt1 = 0;

float Raw_curr = 0.0;
float resistor_value;

float voltage_val[10]={0};
float current_val[10]={0};
float Resistance_val[4] = {0};

//double smooth_res[600] = {0};			//600 means = 1min stored data for smooth resistanace
float smooth_res = 0.0;

float volt_final = 0.0, fval = 0.0;
float Current_final = 0.0;
float Resistance_final = 0.0;
float resistance = 0.0;
float smoothResistance_sum = 0.0;
float SumSmooth_res;
float Resistance_sum2 = 0.0;

	float Raw_avg_volt;
	float Raw_avg_curr;
	float Raw_voltage_adc;
	float Raw_current_val_adc,Volt_curr;


float Resistance_sum = 0.0;

float Raw_voltage = 0.0,Raw_current;
float volt_val = 0.0,curr_val = 0.0;

volatile char RawResistance[30],res[30],curr[15], msg[30];

uint16_t FLAG = 0;
//volatile char Smoothres[50];

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int i = 0, j = 0;
volatile uint32_t x = 0;
volatile uint16_t volt,current;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void ADC_Select_CH0 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_3;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

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
  MX_ADC1_Init();
  MX_TIM6_Init();
  MX_USART3_UART_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		  	  sprintf(msg,"%hu",raw);
		      HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	  	  	  //uprintf("Rajdeep\r\n");

/*
	  	  	  ADC_Select_CH1();
			  HAL_ADC_Start(&hadc1);
			  HAL_ADC_PollForConversion(&hadc1, 1000);
			  volt = HAL_ADC_GetValue(&hadc1);
			  HAL_ADC_Stop(&hadc1);

			  sprintf(msg,"%hu",volt);
			  uprintf(msg);
			  HAL_Delay(3000);

			  	  	  	  ADC_Select_CH0();
			  			  HAL_ADC_Start(&hadc1);
			  			  HAL_ADC_PollForConversion(&hadc1, 1000);
			  			  current = HAL_ADC_GetValue(&hadc1);
			  			  HAL_ADC_Stop(&hadc1);

			  			  sprintf(msg2,"%hu",current);
			  			  uprintf(msg2);
			  			  HAL_Delay(1000);*/

//////////////////// for testing VOLT & CURRENT ////////////////////////


	 if (cnt == 10)		//1sEC loop
		  {
			  sprintf(res,"volt : %0.2f \r\n",Raw_voltage_adc); 	//<---- working for SmoothRes				A0
			  uprintf(res);
			 // cnt = 0;

			  sprintf(RawResistance,"current : %0.2f \r\n",Volt_curr); 	//<---- working for SmoothRes		A3
			  uprintf(RawResistance);
			  cnt = 0;
		  }


/////////////////////////////////////////////////////////

////////////	FINAL SUMRAW	//////////////////////////

	 /* if (cnt == 50)		//100ms loop		//5 sec --- 50
	  {
		  sprintf(res,"SumRawRes : %0.2f \r\n",fval); 	//<---- working for SmoothRes
		  uprintf(res);
		  cnt = 0;
	  }*/

/////////////	FINAL SUMRAW END	/////////////////////

	  //////////////////////	FINAL EWMA	  /////////////////////////////

	 /* if (cnt1 == 600)		//1 Min loop		600
	  {
		  	  float RSM_Val = 0.0;
		  	  smooth_res = 0;
		  	  RSM_Val = ewma(SumSmooth_res);
			  sprintf(msg,"EWMA : %0.6f \r\n",RSM_Val); 	//<---- working for SumResistance
			  uprintf(msg);
			  cnt1 = 0;
	  }*/

	  /////////////////////	  FINAL EWMA END	//////////////////////////


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
//
//void convert_avg(char* outStr)
//{
//	 char str[10];
//
//}


void uprintf(char *str)
{
	HAL_UART_Transmit(&huart3, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

float Raw_volt_adc(void)
{
	///////////////////////volt collect		A0  /////////////////////////////

		  ADC_Select_CH0();
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, 1000);
		  volt = HAL_ADC_GetValue(&hadc1);
		  HAL_ADC_Stop(&hadc1);

	///////////////////////////////////////////////////////////////

       fval = (float)volt;						//<---- working for float

       return fval;
}

float Raw_current_adc(void)
{


	///////////////////////Current collect 	 A3  /////////////////////////////

		  //ADC_Select_CH1();
		  HAL_ADC_Start(&hadc3);
		  HAL_ADC_PollForConversion(&hadc3, 1000);
		  current = HAL_ADC_GetValue(&hadc3);
		  HAL_ADC_Stop(&hadc3);

	///////////////////////////////////////////////////////////////

       Raw_curr = (float)current;						//<---- working for float

       return Raw_curr;
}

float Raw_Resistance(void)
{



	if (i != 5)
		{
			Raw_volt_adc();
			Raw_current_adc();
			voltage_val[i] = fval;
			current_val[i] = Raw_curr;
			Raw_voltage = Raw_voltage + voltage_val[i];
			Raw_current = Raw_current + current_val[i];
			voltage_val[i] = 0;
			current_val[i] = 0;
			i++;
		}
		else
		{
			Raw_avg_volt = (Raw_voltage/5);
			Raw_voltage_adc = ((Raw_avg_volt/4096) * 60.00);

			Raw_avg_curr = (Raw_current/5);
			Volt_curr = ((Raw_avg_curr/4096) * 325.00);
			//Raw_current_val_adc = Volt_curr / 10 * K;

	//******	<Raw_Resistance> t = ( <Raw_Voltage> t – [BACK_EMF] ) / <Raw_Current> t – [V_KA_TIMESHIFT]	 *******//

			resistor_value =  ((Raw_voltage_adc - BACK_EMF) / Volt_curr * K);

	//**************************************************************************************************************//

			if (resistor_value < RES_MIN)
			{
				resistor_value = 0.0;
			}

			i = 0;
			j = 0;
			Raw_voltage = 0.0;
			Raw_current = 0.0;

		}


	return resistor_value;
}

////********************************* SUM OF RAW_RESISTANCE FOR 100ms ******************************//


float Sum_Raw_Res (void)
{
	float Store_res;

	if (j != 1800)		//fixed for 4 sample			1800
	{

			Raw_Resistance();
			Store_res = resistor_value;		//Resistance_val[j] =  resistor_value;
			Resistance_sum2 = Resistance_sum2 + Store_res;		//Resistance_val[j];
			//Resistance_val[j] = 0;
			j++;		// newly added
	}

	Resistance_sum = Resistance_sum2;		// sum of all values 100 times

	Resistance_sum2 = 0.0;		//modify

	return Resistance_sum;
}

//********************************* RAW_RESISTANCE STORE FOR 180 sec ******************************//

float Smooth_Resistance(void)
{

	//smoothResistance_sum = 0.0; //new

	if (m != 1799)			//For 600 sample				1799
			{
				Sum_Raw_Res();
				smooth_res = Resistance_sum;
				smoothResistance_sum += smooth_res;
//				m++;
			}

	resistance = smoothResistance_sum;


	return resistance;
}


//********************************* SUM OF RAW_RESISTANCE STORE FOR 180 sec ******************************//

float SumSmooth_Resistance(void)
{
			Smooth_Resistance();

							/*	resistance = smoothResistance_sum / RAWRES_WINDOW;	*/
			smoothResistance_sum = 0.0;		//clear data

			SumSmooth_res = 0.0;		//reset smoothRes
			SumSmooth_res = resistance / RAWRES_WINDOW;

			resistance = 0.0;

	return SumSmooth_res;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{


	if(htim->Instance == TIM6)
	{

										/*		Raw_Resistance collect	100ms	*/

		Raw_volt_adc();
		Raw_current_adc();
		Raw_Resistance();			//RAW_RESINTANCE
		Sum_Raw_Res();				//SUM_OF_RAW_RESISTANCE   FOR 100 MILISEC


		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

		x++;
		if (x != 300)					// 60 means 6sec;	//300 means 30sec  //600 means 1min	//1800 means 3min
		{
			//x = 0; // reset x

//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);	//Reset for 1Min Duration
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

			Smooth_Resistance();

			m++;
     		cnt++;	//	for 100mSec
     		cnt1++;
		}
		else
		{
											/*		SumSmooth_Resistance collect 1 Min		*/

			x = 0; // reset x
			m = 0;
//			Smooth_Resistance();
			SumSmooth_Resistance();
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);		//set for 1Min Duration
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

		}

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
