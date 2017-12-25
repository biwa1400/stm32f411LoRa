#ifndef __DBPORT_H_
#define __DBPORT_H_

#include "stm32f4xx.h"
#include "stdio.h"	 

void dbPort_init(uint32_t boudRate);
void uart_send(uint8_t data);

#endif