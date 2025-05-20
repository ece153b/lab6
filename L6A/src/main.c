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
	
	while(1) {
		LED_Toggle();
		// initialize CRC
		// start timer
		// compute CRC
		// end timer
		// check CRC
		// print time
		// delay
	}
}
