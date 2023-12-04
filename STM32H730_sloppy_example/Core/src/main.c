#include "main.h"


#include "stm32h7xx_usbdfs_cdc.h"
#include "stm32h7xx_usbdfs_macros.h"

volatile uint32_t THE_TIMEOUT = 0x00FFFFFF;

int main(void){
	if(ClockInit() == CLOCK_ERROR){ /* Start HSE, PLL, Flash latency, all the RCC configuration */
		NVIC_SystemReset();
	}
	EnablePeripherals();
	
	USB_OTG_HS_init_pinout();
	USB_OTG_HS_init_device();
	
	__enable_irq();
	
	
	/***************************************/
	/************** PG 0 *******************/
	/***************************************/
	GPIOG->MODER &= ~GPIO_MODER_MODE0;
	GPIOG->MODER |= GPIO_MODER_MODE0_0;
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPD0;
	GPIOG->PUPDR |= GPIO_PUPDR_PUPD0_1;
	GPIOG->AFR[0] |= GPIO_AFRL_AFSEL0_0;
	
	#define G0_ON (GPIOG->ODR & GPIO_ODR_OD0)
	#define TOGGLE_G0 ((GPIOG->ODR & GPIO_ODR_OD0) ? (GPIOG->BSRR |= GPIO_BSRR_BR0) : (GPIOG->BSRR |= GPIO_BSRR_BS0))

	/***************************************/
	/************** PG 1 *******************/
	/***************************************/
	GPIOG->MODER &= ~GPIO_MODER_MODE1;
	GPIOG->MODER |= GPIO_MODER_MODE1_0;
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOG->PUPDR |= GPIO_PUPDR_PUPD1_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL1_0;
	
	#define G1_ON (GPIOG->ODR & GPIO_ODR_OD1)
	#define TOGGLE_G1 ((GPIOG->ODR & GPIO_ODR_OD1) ? (GPIOG->BSRR |= GPIO_BSRR_BR1) : (GPIOG->BSRR |= GPIO_BSRR_BS1))
	
	/***************************************/
	/************** PF 15 ******************/
	/***************************************/
	GPIOF->MODER &= ~GPIO_MODER_MODE15;
	GPIOF->MODER |= GPIO_MODER_MODE15_0;
	GPIOF->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED15;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOF->PUPDR &= ~GPIO_PUPDR_PUPD15;
	GPIOF->PUPDR |= GPIO_PUPDR_PUPD15_1;
	GPIOF->AFR[1] |= GPIO_AFRH_AFSEL15_0;
	
	#define F15_ON (GPIOF->ODR & GPIO_ODR_OD15)
	#define TOGGLE_F15 ((GPIOF->ODR & GPIO_ODR_OD15) ? (GPIOF->BSRR |= GPIO_BSRR_BR15) : (GPIOF->BSRR |= GPIO_BSRR_BS15))
	
	
	while(1){
		volatile uint32_t timeout = THE_TIMEOUT;
		while(timeout-- != 0) {}
			
		TOGGLE_G0;
		TOGGLE_G1;
		TOGGLE_F15;
			
	}
}

