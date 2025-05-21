/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6A
 */

#include "stm32l476xx.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "LED.h"
#include "CRC.h"
#include "UART.h"
#include <stdio.h>

/* Expected CRC Value */
#define uwExpectedCRCValue 0x5A60861E

static volatile uint32_t Software_ComputedCRC;

void Init_USARTx(int x) {
	if(x == 1) {
		UART1_Init();
		UART1_GPIO_Init();
		USART_Init(USART1);
	} else if(x == 2) {
		UART2_Init();
		UART2_GPIO_Init();
		USART_Init(USART2);
	} else {
		// Do nothing...
	}
}

int main(void) {
	
	// Switch System Clock = 80 MHz
	System_Clock_Init(); 
	// Initialize modules
	SysTick_Init(); 
	LED_Init();
	Init_USARTx(2);
	
	while(1) {
		LED_Toggle();
		// initialize CRC 
		Software_ComputedCRC = INITIAL_CRC_VALUE; 

		// start timer
		startTimer(); 
		// compute CRC

		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			Software_ComputedCRC = CrcSoftwareFunc(Software_ComputedCRC, DataBuffer[i], POLYNOME); 
		}
		// end timer
		uint32_t time = endTimer(); 
		// check CRC 
		if(Software_ComputedCRC != uwExpectedCRCValue)
		{
			LED_Off(); 
			break; 
		}
		// print time
		printf("Time: %i us\n", time);  
		// delay
		delay(1000); 
	}
}
