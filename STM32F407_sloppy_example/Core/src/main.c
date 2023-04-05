/****************************************************************
* A device based on STM32F205
*
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*
*****************************************************************/

#include "main.h"



uint32_t USB_CDC_recieve_data(uint16_t length){
	uint8_t *data = EndPoint[1].rxBuffer_ptr;
	for(uint32_t i = 0; i < length; i++){
		data[i] = data[i] + 1;
	}
	
	USB_CDC_send_data(data, length);
	return length;
}


int main(void){

   	/* Start HSE, PLL, Flash latency, all the RCC configuration */
	/* Enable all the Peripherial clocks */
	if(ClockInit() == CLOCK_ERROR){ /* Start HSE, PLL, Flash latency, all the RCC configuration */
		NVIC_SystemReset();
	}
	
	EnablePeripherals();
	__disable_irq ();

	
	USB_OTG_FS_init_pinout();
	USB_OTG_FS_init_device();
	
	
	volatile static uint32_t timeout = 0xFFFF;
	
	__enable_irq ();
	
	while(1){
		timeout = 0xFFFF;
		while(timeout-- > 0){
		}
			
	}
}

