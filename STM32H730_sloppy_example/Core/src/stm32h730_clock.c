/****************************************************************
* Functions for initial STM32H730 configuration
* e.g. clocking
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
****************************************************************/

#include "stm32h730_clock.h"
#include "stm32h730xx.h"

#define HSEStartUp_TimeOut   ((uint16_t)0x05000) /*!< Time out for HSE start up */


/**
 * brief ClockInit - Enable clocking of the STM32H730.
 * brief Inside this function we set configuration bits in RCC_CR and RCC_CFGR.
 * brief Our purpose is to configure HSE, PLL and all the Clock Control except certain Peripherials.
 * param  
 * param  
 * retval OK / Error
 */
eClockState ClockInit(void){
	volatile uint32_t HSE_Status = 0;
	volatile uint32_t HSE_TimeoutCounter = 0;
	
	PWR->CR3 |= PWR_CR3_USB33DEN;
	PWR->D3CR |= PWR_D3CR_VOS_1 | PWR_D3CR_VOS_0;
	
	volatile uint32_t timeout = HSEStartUp_TimeOut;
	while (((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) && (timeout != 0)) {
		timeout--;
	}
	if(timeout != 0) HSE_Status = 1;
	else HSE_Status = 0;
		

	//*********** HSE ***********	
	RCC->CR |= RCC_CR_HSEON;
	timeout = HSEStartUp_TimeOut;
	while (((RCC->CR & RCC_CR_HSERDY)==0) && (timeout != 0)) {
		timeout--;
	}
	if(timeout != 0) HSE_Status = 1;
	else HSE_Status = 0;
	
	
	//*********** FLASH ***********
	FLASH->ACR = (uint32_t)FLASH_ACR_LATENCY_1WS;
	FLASH->ACR |= (uint32_t)FLASH_ACR_WRHIGHFREQ;

		
	//*********** PLL PSC ***********		
	RCC->PLLCKSELR &= ~(RCC_PLLCKSELR_PLLSRC|RCC_PLLCKSELR_DIVM1 | RCC_PLLCKSELR_DIVM2 | RCC_PLLCKSELR_DIVM3);
		
	// PLLCKSELR        0x02020042
	// PLLSRC           0x02
	// DIVM1            0x04	
	// DIVM2            0x20
	// DIVM3            0x20
	RCC->PLLCKSELR |= 0x02020042;

	//*********** PLL1 ***********
	/* Select PLL1 output frequency range : VCO */
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLL1VCOSEL;
	RCC->PLL1DIVR &= ~(RCC_PLL1DIVR_P1_Pos|RCC_PLL1DIVR_N1|RCC_PLL1DIVR_R1|RCC_PLL1DIVR_Q1);

	// PLL1DIVR         0x0101038F
	// DIVN1            0x018F
	// DIVP1            0x01	
	// DIVQ1            0x01
	// DIVR1            0x01
	RCC->PLL1DIVR |= 0x0101038F;
	RCC->PLL1FRACR &= ~RCC_PLL1FRACR_FRACN1; 

	//*********** PLL2 ***********
	RCC->PLL2DIVR &= ~(RCC_PLL2DIVR_P2_Pos | RCC_PLL2DIVR_N2 | RCC_PLL2DIVR_R2 | RCC_PLL2DIVR_Q2);
	
	// PLL2DIVR         0x01010280
	// DIVN1            0x018F
	// DIVP1            0x01	
	// DIVQ1            0x01
	// DIVR1            0x01
	RCC->PLL2DIVR |= 0x01010280;
	RCC->PLL2FRACR &= ~RCC_PLL2FRACR_FRACN2;

	//*********** PLL3 ***********	
	RCC->PLL3DIVR &= ~(RCC_PLL3DIVR_P3 | RCC_PLL3DIVR_N3 | RCC_PLL3DIVR_R3 | RCC_PLL3DIVR_Q3);
	
	// PLL3DIVR         0x01010280
	// DIVN3            0x018F
	// DIVP3            0x01	
	// DIVQ3            0x01
	// DIVR3            0x01
	RCC->PLL3DIVR |= 0x01010280;
	RCC->PLL3FRACR &= ~RCC_PLL3FRACR_FRACN3;
	
	RCC->PLLCFGR |= RCC_PLLCFGR_PLL1RGE_1;
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLL1VCOSEL | RCC_PLLCFGR_PLL2VCOSEL | RCC_PLLCFGR_PLL3VCOSEL);
		
	RCC->PLLCFGR |= (RCC_PLLCFGR_DIVP1EN | \
                    RCC_PLLCFGR_DIVQ1EN | \
                    RCC_PLLCFGR_DIVR1EN | \
                    RCC_PLLCFGR_PLL1FRACEN | \
                    RCC_PLLCFGR_DIVP2EN | \
                    RCC_PLLCFGR_DIVQ2EN | \
                    RCC_PLLCFGR_DIVR2EN | \
                    //RCC_PLLCFGR_PLL2FRACEN|
                    RCC_PLLCFGR_DIVP3EN | \
                    RCC_PLLCFGR_DIVQ3EN | \
                    RCC_PLLCFGR_DIVR3EN
                    //RCC_PLLCFGR_PLL3FRACEN
										);
		
		
	//*********** Enable PLL ***********
	RCC->CR |= RCC_CR_PLL1ON;		
	timeout = HSEStartUp_TimeOut;
	while (((RCC->CR & RCC_CR_PLL1RDY)==0) && (timeout != 0)) {
		timeout--;
	}
	if(timeout != 0) HSE_Status = 1;
	else HSE_Status = 0;
	
		
	//RCC->CR |= RCC_CR_PLL2ON;
	//while((RCC->CR & RCC_CR_PLL2RDY)==0){};
		
	//RCC->CR |= RCC_CR_PLL3ON;
	//while((RCC->CR & RCC_CR_PLL3RDY)==0){};	
		

	//HPRE[3:0]: D1 domain AHB prescaler
	//1000: rcc_hclk3 = sys_d1cpre_ck / 2
	//HPRE   = 0x09	
	//D1PPRE = 0x04
	//D1CPRE = 0x00
	RCC->D1CFGR = 0x00000049;
	
	//PCLK1 Configuration
	//Bits 6:4 D2PPRE1[2:0]: D2 domain APB1 prescaler
	//100: rcc_pclk1 = rcc_hclk1 / 2
	RCC -> D2CFGR |=  RCC_D2CFGR_D2PPRE1_2;
	RCC -> D2CFGR &= ~RCC_D2CFGR_D2PPRE1_1;
	RCC -> D2CFGR &= ~RCC_D2CFGR_D2PPRE1_0;
	
	//PCLK2 Configuration
	//Bits 10:8 D2PPRE2[2:0]: D2 domain APB2 prescaler
	//100: rcc_pclk2 = rcc_hclk1 / 2
	RCC -> D2CFGR |=  RCC_D2CFGR_D2PPRE2_2;
	RCC -> D2CFGR &= ~RCC_D2CFGR_D2PPRE2_1;
	RCC -> D2CFGR &= ~RCC_D2CFGR_D2PPRE2_0;
		
	//D3PCLK1 Configuration
	//Bits 6:4 D3PPRE[2:0]: D3 domain APB4 prescaler
	//100: rcc_pclk4 = rcc_hclk4 / 2
	RCC -> D3CFGR |=  RCC_D3CFGR_D3PPRE_2;
	RCC -> D3CFGR &= ~RCC_D3CFGR_D3PPRE_1;
	RCC -> D3CFGR &= ~RCC_D3CFGR_D3PPRE_0;

		
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL1;

	timeout = HSEStartUp_TimeOut;
	while (((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL1) && (timeout != 0)) {
		timeout--;
	}
	if(timeout != 0) HSE_Status = 1;
	else HSE_Status = 0;	
	
	
  timeout = HSEStartUp_TimeOut;
	while((!(RCC->CR & RCC_CR_D1CKRDY)) && (timeout != 0)) {
		timeout--;
	}
	if(timeout != 0) HSE_Status = 1;
	else HSE_Status = 0;  
		
	// SW DIO
	GPIOA->MODER &= ~GPIO_MODER_MODE13;
	GPIOA->MODER |= GPIO_MODER_MODE13_1;
	//GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL13_0;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE14;
	GPIOA->MODER |= GPIO_MODER_MODE14_1;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED14;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED14;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD14;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL14_1;
	
	//SYSCFG
	RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;
	
	//************** USB **************
	RCC->CR |= RCC_CR_HSI48ON;
	RCC->D2CCIP2R |= RCC_D2CCIP2R_USBSEL;
	
	
	if(HSE_Status == 1){
		return CLOCK_OK; // RCC has started for good!!! 
	}
	else{
		return CLOCK_ERROR; // RCC hasn`t started and we need to sort this out. 
	}	
}

/**
 * brief  EnablePeripherals - Enable clocking of the peripherals that will be used
 * param  
 * param  
 * retval
 */
void EnablePeripherals(void){

	//GPIO	
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOGEN;
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOFEN;
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOHEN;
	
	//USB
	RCC->AHB1ENR |= RCC_AHB1ENR_USB1OTGHSEN;	
}


