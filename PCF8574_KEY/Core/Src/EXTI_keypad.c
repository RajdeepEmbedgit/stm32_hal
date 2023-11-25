/*
 * EXTI_keypad.c
 *
 *  Created on: Sep 29, 2022
 *      Author: rajdeep
 */

#include "stm32f429xx.h"

void EXTI_Keypad(void)
{
	 //************************	Interrupt	***************************//
   	  __disable_irq();

   // setup LEDs
     RCC->AHB1ENR |= (1<<1);		// FOR PORT B
     RCC->AHB1ENR |= (1<<2);		// FOR PORT C
     RCC->AHB1ENR |= (1<<6);		// FOR PORT G
     					      /*****	   LED	  *****/
//  	  GPIOB->MODER |= (1<<0);		//	General purpose output mode PIN 0
//  	  GPIOB->MODER |= (1<<14);		//	General purpose output mode PIN 7
//  	  GPIOB->MODER |= (1<<28);		//	General purpose output mode PIN 14
  	  	  	  	  	      /*****	  BUTTONS		*****/
  	  GPIOC->MODER |= (1<<26);		//	General purpose output mode PIN 13 ((USER BUTTON))
//  	  GPIOC->OTYPER &= ~(1<<13);
//  	  GPIOC->PUPDR |= ((0<<27) | (1<<26));  // Pin PC13 (bits 27:26) are 0:0 --> no pull up or pulldown
  	  GPIOC->ODR |= 1<<13; // Set the Pin PC13
  					     /*******	 FOR PG1	*******/
//  	 	  GPIOG->MODER |= (1<<1);		//	General purpose output mode PIN 1   ((EXT BUTTON))
//  	 	  GPIOG->PUPDR	&=	~(GPIO_PUPDR_PUPDR1);




  	  	  	  	  	  	  	  	      /*****	 INTERRUPT		*****/
  	  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  	  	  	  	  	  	  	  /*****	 INTERRUPT FOR PC13	BUTTON		*****/
  	  SYSCFG->EXTICR[3] |= 0x0020;

  	  EXTI->IMR |= 0x2000;		//Interrupt mask register
  	  EXTI->FTSR |=	0x2000;		//Falling trigger selection register
//  	 EXTI->RTSR |=	0x2000;			//Rising trigger selection register

  	  //////////////////////////  2nd button ///////////////////////

//  	  	 SYSCFG->EXTICR[0] &= ~(0xF << 4);
//  	  	 	  	  	  	  	  	  	  	  	  /*******	 FOR PG1	*******/
//  	  	 	  SYSCFG->EXTICR[0] |= (0<<7);		//external interrupt configuration register
//  	  	 	  SYSCFG->EXTICR[0] |= (1<<6);
//  	  	 	  SYSCFG->EXTICR[0] |= (1<<5);
//  	  	 	  SYSCFG->EXTICR[0] |= (0<<4);
//
//  	  	 	  EXTI->IMR |= (1<<1);		//Interrupt mask register
//  	  	 	  EXTI->FTSR |=	(1<<1);		//Falling trigger selection register
//
//  	  	 	  NVIC_EnableIRQ(EXTI1_IRQn);	//Interrupt Handler
//  	  	  	  NVIC_SetPriority(EXTI1_IRQn, 0);

  	  /////////////////////////// 2nd button end ///////////////////////////

  	  NVIC_EnableIRQ(EXTI15_10_IRQn);	//Interrupt Handler
  	  NVIC_SetPriority(EXTI15_10_IRQn, 1);

  	  __enable_irq();


      	 //**********************************************************//

}
