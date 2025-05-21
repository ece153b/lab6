/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6C
 */

#include "SysTimer.h"

static uint32_t volatile step;

void SysTick_Init(void) {
	// SysTick Control & Status Register
	SysTick->CTRL = 0; // Disable SysTick IRQ and SysTick Counter

	
	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Select clock source
	// If CLKSOURCE = 0, the external clock is used. The frequency of SysTick clock is the frequency of the AHB clock divided by 8.
	// If CLKSOURCE = 1, the processor clock is used.
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 
	
	// Configure and Enable SysTick interrupt in NVIC
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 1); // Set Priority to 1
}

void SysTick_Handler(void) {
	++step;
}

void delay(uint32_t us) {
	step = 0; 						//Reset counter
	SysTick->VAL = 0;				//Set SysTick value to 0
	SysTick->LOAD = 79; 	//Set SysTick load value (TODO - DOUBLE CHECK WHAT THIS VALUE SHOULD BE)
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  //Enable SysTick
	while(step < us){} 
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);  //Disable SysTick
}

void startTimer(void) {
	step = 0; 						//Reset counter
	SysTick->VAL = 0;				//Set SysTick value to 0
	SysTick->LOAD = 799; 	//Set SysTick load value (TODO - DOUBLE CHECK WHAT THIS VALUE SHOULD BE)
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  //Enable SysTick
}

uint32_t endTimer(void) {
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);  //Disable SysTick
	return (step*10 + ((1/(8*10e7))*(SysTick->LOAD - SysTick->VAL)));
}
