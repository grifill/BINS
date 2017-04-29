/**
  ******************************************************************************
  * @file    sys_init.h
  * @author  Filatov Grigoriy
  * @date    29-April-2017
  ******************************************************************************
  *
  * Copyright(C) Grifill, 2017
  * All rights reserved
  * 
  ******************************************************************************
  */
#ifndef SYS_INIT_H_
#define SYS_INIT_H_

#include        "stm32f4xx_conf.h"
#include 	"stm32f4xx.h"

#include        <stdint.h>


void clk_init();
void led_init();
void gps_init();
void usart1_init();




// Define TRUE, FALSE and bool if not defined
typedef enum {FALSE = 0, TRUE = !FALSE} bool;



#endif //SYS_INIT_H_
