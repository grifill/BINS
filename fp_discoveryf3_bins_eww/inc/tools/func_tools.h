/**
  ******************************************************************************
  * @file    func_tools.h
  * @author  Filatov Grigoriy
  * @date    29-April-2017
  ******************************************************************************
  *
  * Copyright(C) Grifill, 2017
  * All rights reserved
  * 
  ******************************************************************************
  */
#ifndef FUNC_TOOLS_H_
#define FUNC_TOOLS_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include        "stm32f30x_conf.h"
#include 	"stm32f30x.h"


// CONFIG
#define PRINTF_CAN_USED
#define ENABLE_DEBUG_PRINT
#define USART_CONSOLE USART1
#define CONSOLE_SPEED 115200


#define DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC


#ifdef PRINTF_CAN_USED
#define PRINT(...)                 {printf(__VA_ARGS__);}
#else
//без отладочного вывода
#define PRINT(...)                                                                                                            
#endif



void delay_ms(uint32_t ms);





#endif /* FUNC_TOOLS_H_ */
