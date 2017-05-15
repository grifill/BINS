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
#include "func_tools.h"
#include "stm32f3_discovery.h"
#include "l3gd20.h"
#include "lsm303dlhc.h"
#include "complementary_filter.h"
#include "kalman_filter.h"


int main()
{
  SysTick_Config(720000);
  clk_init();
  led_init();
  usart1_init();
  
  l3gd20Setup();
  lsm303dlhcSetup();
  
  orientationReset();
  complementaryFilterSetFactor(0.975);
  kalmanFilterInit();
  
  PRINT(">>> Program Start (%s %s)\n",__DATE__,__TIME__);
  //PRINT("xa;ya;za;xg;yg;zg\n"); // - DATA
  PRINT("t;tf;k;kf\n"); // - Filtr
  
  while(1)
  {
   
  }
}