#include "delay.h"
#include "config.h"
uint32_t delay_count = 0;
void SysTick_Handler(void)
{
	delay_count--;
}


void delay(float s)
{
	delay_count = s*1000;
	SysTick_Config(HCLK_FREQUENCY/1000-1);
	while(delay_count>0);
	// stop system tick
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;
}
