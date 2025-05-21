/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6C
 */

#include "LED.h"

void LED_Init(void){
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Initialize Green LED
	GPIOA->MODER &= ~(GPIO_MODER_MODE5); //Clear the mode register
	GPIOA->MODER  |= GPIO_MODER_MODE5_0; //Set to output
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5); //Set output type to push-pull
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5); //Set pull-up/pull-down to no pull-up/pull-down
}

void LED_On(void){
	GPIOA -> ODR |= GPIO_ODR_OD5;
}

void LED_Off(void){
	GPIOA -> ODR &= ~(GPIO_ODR_OD5);
}

void LED_Toggle(void){
	if((GPIOA -> ODR & GPIO_ODR_OD5) == GPIO_ODR_OD5)
	{
		LED_Off(); 
	}
	else
	{
		LED_On(); 
	}
}
