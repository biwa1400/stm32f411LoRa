#include "DBuart.h"
#include "config.h"

uint8_t dbPortInit = 0;

void dbPort_init(uint32_t boudRate)
{  	 
  // calculate boundRate
	float usartDiv=(float)(APB2_FREQUENCY)/(boudRate*16);      // get USARTDIV
	uint16_t usartDiv_mantissa=usartDiv;				                //get USARTDIV mantissa
	uint16_t usartDiv_fraction=(usartDiv-usartDiv_mantissa)*16; //get USARTDIV fraction
  usartDiv_mantissa<<=4;                                      // matching USART_BRR
	uint16_t divValue = usartDiv_mantissa+usartDiv_fraction; 
	
	// config I/O
	//Enable PA_9->Tx
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  
 // config GPIO mode to alternate  
	GPIOA -> MODER &= ~GPIO_MODER_MODER9;  
	GPIOA -> MODER |= (GPIO_MODER_MODER9_1);
	// config GPIO speed
	GPIOA -> OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR9;  		
	GPIOA -> OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR9_0|GPIO_OSPEEDER_OSPEEDR9_1);
 // config alternate number -> 0
	GPIOA -> AFR[1] &= ~(uint32_t)(0x0f<<1*4);
	GPIOA -> AFR[1] |=  (uint32_t)(0x07<<1*4);    	
	
	
	// config USART1
	// enable USART1
	RCC->APB2ENR|=RCC_APB2ENR_USART1EN;  
	// reset USART1
	RCC->APB2RSTR|=RCC_APB2RSTR_USART1RST;   //复位串口1
	RCC->APB2RSTR &=~RCC_APB2RSTR_USART1RST; //停止复位	   	   
	
	
	//Config boundRate
 	USART1->BRR=divValue;
	//enable USART
	USART1->CR1 |=USART_CR1_UE;
	//enable Tx
	USART1->CR1 |=USART_CR1_TE;
	
	dbPortInit = 1;
}

void uart_send(uint8_t data)
{
	if (dbPortInit == 1)
	{
		while(READ_BIT(USART1->SR,USART_SR_TXE) == 0);//等待上一次串口数据发送完成  
		USART1->DR = data;      	//写DR,串口1将发送数据
	}
	else
	{
		dbPort_init(DEBUG_PORT_BAUDRATE);
		uart_send(data);
	}
}

int fputc(int ch, FILE *f)
{      
	uart_send((uint8_t) ch);
	return ch;
}