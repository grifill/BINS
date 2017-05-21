/**
  ******************************************************************************
  * @file    usart_tools.h
  * @author  Filatov Grigoriy
  * @date    20-May-2017
  ******************************************************************************
  *
  * Copyright(C) Grifill, 2017
  * All rights reserved
  * 
  ******************************************************************************
  */
#ifndef USART_TOOLS_H_
#define USART_TOOLS_H_  

#include "stm32f4xx_conf.h"
#include "func_tools.h"



#define PROTO_BUF_SIZE 	(512) 
#define USART_TOOL      USART1

/**
\struct Структура с параметрами буфера приема по UART
*/
struct tUSARTcontext
{
	char 		lock_rx;
	uint8_t		rx[PROTO_BUF_SIZE];
	uint16_t	cnt_rx;
	uint16_t	start_rx;
};

// Функции общения по UART -------------------------------------------------->>>
void Add_USART(struct tUSARTcontext* usart);
uint8_t USART_Read_Byte(uint8_t bt);
void USART_Send_Byte(uint8_t byte);
void USART_Send_Buf(uint8_t* buf, uint16_t cnt);
uint8_t	GetByte_t(uint8_t* ch);
uint8_t	Thread_Byte_Get_t(uint8_t* ch);





















#endif //USART_TOOLS_H_