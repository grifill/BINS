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
#include "usart_tools.h"

#include "binr_parse.h"

#include "mems.h"
#include "lsm303dlhc_driver.h"
#include "l3g4200d_driver.h"
//-----------------------------------------------------------------------------
status_t gyro_init(L3G4200D_ODR_t drg1,L3G4200D_Fullscale_t fg);
//==============================================================================
uint8_t response;
L3GAxesRaw_t data_l3g;
AccAxesRaw_t data_a;
MagAxesRaw_t data_m;

extern struct NV08C_InitTypeDef nv08c; 

int main()
{
  clk_init();
  //RCC_ClocksTypeDef RCC_ClocksStatus;
  //RCC_GetClocksFreq(&RCC_ClocksStatus);
  
  led_init();
  gps_init();
  
  console_init();
  usart1_init();
  
  NV08C_Soft_Reset(&nv08c);
  PRINT(">>> Program Start (%s %s)\n",__DATE__,__TIME__);
  
 // I2C_MEMS_Init();
 // SPI_Mems_Init();

 // gyro_init(L3G4200D_ODR_800Hz_BW_110, L3G4200D_FULLSCALE_250);
  
  timer2_init();
  while(1)
  {
   BINR_Parse(&nv08c);
  }
}

status_t gyro_init(L3G4200D_ODR_t drg1,L3G4200D_Fullscale_t fg)
{
  response = L3G4200D_SetODR(drg1);
  //set PowerMode
  response = L3G4200D_SetMode(L3G4200D_NORMAL);
  //set Fullscale
  response = L3G4200D_SetFullScale(fg);
  //set axis Enable
  response = L3G4200D_SetAxis(L3G4200D_X_ENABLE | L3G4200D_Y_ENABLE | L3G4200D_Z_ENABLE);
  return (status_t)response;
}
