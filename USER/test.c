#include "stm32f4xx.h"
#include "config.h"
#include "delay.h"
#include "stdio.h"

void outputClock()
{
	// select clock source output to MCO2 ()
	RCC->CFGR &= ~RCC_CFGR_MCO2;
	RCC->CFGR |= (RCC_CFGR_MCO2_0|RCC_CFGR_MCO2_1);
	// select prescaler = 5
	RCC->CFGR &= ~(RCC_CFGR_MCO2PRE);
	RCC->CFGR |= (RCC_CFGR_MCO2PRE_0|RCC_CFGR_MCO2PRE_1|RCC_CFGR_MCO2PRE_2);
	
	// config GPIO (PC9)
	// enable GPIO module
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	// config GPIO mode to alternate
	GPIOC -> MODER &= ~GPIO_MODER_MODER9;
	GPIOC -> MODER |= (GPIO_MODER_MODER9_1);
	// config GPIO speed
	GPIOC -> OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR9;
	GPIOC -> OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR9_0|GPIO_OSPEEDER_OSPEEDR9_1);
	// config alternate number -> 0
	GPIOC -> AFR[1] &= ~(uint32_t)(0x0f);
}

// init GPIO_A analog in
void init_gpio()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA -> MODER |= ~0x00;
	#ifdef DEBUG
		// GPIO13 debug
		GPIOA -> MODER &= ~GPIO_MODER_MODER13;
		GPIOA -> MODER |= (GPIO_MODER_MODER13_1);
		// GPIO14 debug
		GPIOA -> MODER &= ~GPIO_MODER_MODER14;
		GPIOA -> MODER |= (GPIO_MODER_MODER14_1);
	#endif
}

void ioInterrupt()
{

	
	// IO init
	// config GPIO (PC13)
	// enable GPIO module
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	// config GPIO mode to input (00)
	GPIOC -> MODER &= ~GPIO_MODER_MODER13;
	// config GPIO speed
	GPIOC -> OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13;
	GPIOC -> OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13_0|GPIO_OSPEEDER_OSPEEDR13_1);
	// config GPIO pull up
	GPIOC -> PUPDR &= ~GPIO_PUPDR_PUPDR13;
	GPIOC -> PUPDR |= GPIO_OSPEEDER_OSPEEDR13_0;

	
	// EXTI init
	//enable SYSCFG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	// config EXTI0 as GPIOA interrupt
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC; 
	// not mask EXTI0
	EXTI->IMR |= EXTI_IMR_MR13;
	// down edge trigger
	EXTI->FTSR |= EXTI_FTSR_TR13;
	//enable interrupt on EXTI0 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	// set priority for EXTI0
	NVIC_SetPriority(EXTI15_10_IRQn, 50);
}

void EXTI15_10_IRQHandler(void)
{
	printf("interrupt!!!\n  ");
	EXTI->PR |= EXTI_PR_PR0;
	//delay(1);
}


int main(void)
{
	//init_gpio();
 	printf("start\n");

	ioInterrupt();
	while(1);
}