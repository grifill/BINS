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
  * @brief: ������� ���������� �������� � ����������������.
  * @param ms:  ����� � �������������
*/
__weak void delay_ms(uint32_t ms)
{
  int32_t ms_count_tick =  ms * (SystemCoreClock/1000);                         // ������ ������� �� ������� ������������
  SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;                                      // �������� �������
  DWT_CYCCNT  = 0;                                                              // �������� �������
  DWT_CONTROL|= DWT_CTRL_CYCCNTENA_Msk;                                         // ������ ������ 
  while(DWT_CYCCNT < ms_count_tick);                                            // ��������� 
  DWT_CONTROL &= ~DWT_CTRL_CYCCNTENA_Msk;
}