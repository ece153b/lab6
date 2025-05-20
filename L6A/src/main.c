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

int main(void) {
	
	// Switch System Clock = 80 MHz
	System_Clock_Init(); 
	// TODO initialize modules
	SysTick_Init(); 
	LED_Init();
	UART2_Init();
	UART2_GPIO_Init(); 
	
	while(1) {
		LED_Toggle();
		// initialize CRC - TODO, check what this is
		
		// start timer
		startTimer(); 
		// compute CRC
		uint32_t initialCRCValue = INITIAL_CRC_VALUE; 
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			CrcSoftwareFunc(initialCRCValue, DataBuffer[i], POLYNOME); 
		}
		// end timer
		uint32_t time = endTimer(); 
		// check CRC TODO - figure out where expected values come from/what calculated value should be
		// print time
		printf("Time: %i", time); 
		// delay
		delay(1000); 
	}
}
