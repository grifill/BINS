/**
  ******************************************************************************
  * @file    main.c
  * @author  Filatov Grigoriy
  * @date    29-April-2017
  ******************************************************************************
  *
  * Copyright(C) Grifill, 2017
  * All rights reserved
  * 
  ******************************************************************************
  */

#include "sys_init.h"

int main()
{
  clk_init();
  led_init();
  gps_init();
  usart1_init();
  
  
  while(1)
  {
    
  }
}