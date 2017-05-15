/**
  ******************************************************************************
  * @file    func_tools.c
  * @author  Filatov Grigoriy
  * @date    29-April-2017
  ******************************************************************************
  *
  * Copyright(C) Grifill, 2017
  * All rights reserved
  * 
  ******************************************************************************
  */
#include "func_tools.h"

//-------------------------- PrintF ------------------------------------------//
// *Uncomment your choise in <func_tools.h>
#if defined(PRINTF_CAN_USED)
int putchar(int x)
{
  while(USART_GetFlagStatus(USART_CONSOLE, USART_FLAG_TXE) == RESET);
  USART_SendData(USART_CONSOLE, x);
  return x;
}
#endif


/**
  * @brief: Функция реализации задержки в микроконтроллере.
  * @param ms:  время в миллисекундах
*/
__weak void delay_ms(uint32_t ms)
{
  int32_t ms_count_tick =  ms * (SystemCoreClock/1000);                         // Расчет времени от частоты тактирования
  SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;                                      // Включить счетчик
  DWT_CYCCNT  = 0;                                                              // Обнулить счетчик
  DWT_CONTROL|= DWT_CTRL_CYCCNTENA_Msk;                                         // Начать отсчет 
  while(DWT_CYCCNT < ms_count_tick);                                            // Обработка 
  DWT_CONTROL &= ~DWT_CTRL_CYCCNTENA_Msk;
}