/****************************************************************
* A device based on STM32F105
*
*
* Alex Svetlichnyy 2018 svetlal@outlook.com
*****************************************************************/

#include "main.h"
// #include <stdint.h>


int main(void){
	ClockInit();   	/* Start HSE, PLL, Flash latency, all the RCC configuration */
	EnablePeripherals(); 	/* Enable all the Peripherial clocks */

	USB_OTG_FS_init_pinout();
	USB_OTG_FS_init_device();
	__enable_irq ();

	while(1){

	}
}
