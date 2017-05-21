/**
  ******************************************************************************
  * @file    usart_tools.c
  * @author  Filatov Grigoriy
  * @date    20-May-2017
  ******************************************************************************
  *
  * Copyright(C) Grifill, 2017
  * All rights reserved
  * 
  ******************************************************************************
  */
#include "usart_tools.h"

struct tUSARTcontext 	usart_pool;                                             // Структура с параметрами обмена по UART
uint8_t ch;                                                                     // Переменная для хранения принятого байта

/**
\brief Функция заполняет структуру для работы с UART 
*/
__weak void Add_USART(struct tUSARTcontext* usart)
{
  usart->cnt_rx = 0;
  usart->lock_rx = 0;
  usart->start_rx = 0;
  memset(usart_pool.rx,0,PROTO_BUF_SIZE);
}

/**
\brief Функция отправляет байт по USART
\param byte      байт, который необходимо отправить  
*/
__weak void USART_Send_Byte(uint8_t byte)
{
  while(USART_GetFlagStatus(USART_TOOL, USART_FLAG_TXE) == RESET);
  USART_SendData(USART_TOOL, byte);
}

/**
\brief Функция отправляет массив данных побайтно, 
\использует функцию USART_Send_Byte()
\param buf      указатель на массив данных 
\param cnt      количество байт для отправки
*/
__weak void USART_Send_Buf(uint8_t* buf, uint16_t cnt)
{
  for (int i=0; i<cnt; i++)
  {
    USART_Send_Byte(buf[i]);
  } 
}

/**
\brief Функция записывает очередной байт в массив.
\Функция возвращает 1, когда байт записан
\param bt      байт для записи 
*/
__weak uint8_t USART_Read_Byte(uint8_t bt)
{
  usart_pool.rx[usart_pool.cnt_rx] = bt;
  usart_pool.cnt_rx++;
  switch(usart_pool.cnt_rx / PROTO_BUF_SIZE)
  {
  case 0:
	break;
  default:
	usart_pool.cnt_rx = 0;
        break;
  }
  return 1;
}

/**
\brief Функция читает байт из массива.
\Функция возвращает 1, если пришел новый байт
\Функция возвращает 0, если новых байт в массиве не обнаружено
\param ch      текущий байт для чтения 
*/
__weak uint8_t	Thread_Byte_Get_t(uint8_t* ch)
{
  if(usart_pool.start_rx != usart_pool.cnt_rx)
  {
    *ch = usart_pool.rx[usart_pool.start_rx];
    usart_pool.start_rx++;
    if(usart_pool.start_rx >= PROTO_BUF_SIZE)
    {
      usart_pool.start_rx = 0;
    }
    return 1;
  }
  return 0;
}

/**
\brief Функция возвращает значение функции Thread_Byte_Get().
*/
uint8_t	GetByte_t(uint8_t* ch)
{
  return Thread_Byte_Get_t(ch);
}