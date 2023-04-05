#ifndef STM32F105_CLOCK_H_INCLUDED
#define STM32F105_CLOCK_H_INCLUDED

/****************************************************************
* Functions for initial STM32F205 configuration
* e.g. clocking
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
****************************************************************/


#include "stm32f407xx.h"

typedef enum{
	CLOCK_OK = 0,
	CLOCK_ERROR = 1 } eClockState;


eClockState ClockInit(void);			/* Configuring initial clocks and prescalers */
void EnablePeripherals(void);			/* Choose the peripherals to be used in the project and set clocking */
	
#endif /* STM32F105_CLOCK_H_INCLUDED*/
