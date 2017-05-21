/**
  ******************************************************************************
  * @file    sys_init.c
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


// CLK 
void clk_init()
{
  SystemCoreClockUpdate();
  for(int delay_clk = 0; delay_clk < 0xFFFF; delay_clk++);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
}

// LEDs
void led_init() 
{
  // HL3 - LED
  GPIO_InitTypeDef port_c_led;
    port_c_led.GPIO_Mode = GPIO_Mode_OUT;
    port_c_led.GPIO_OType = GPIO_OType_PP;
    port_c_led.GPIO_Pin =  GPIO_Pin_13;
    port_c_led.GPIO_Speed = GPIO_Speed_25MHz;
    port_c_led.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC,&port_c_led);

  // HL2,HL1 - LEDs
  GPIO_InitTypeDef port_b_led;
    port_b_led.GPIO_Mode = GPIO_Mode_OUT;
    port_b_led.GPIO_OType = GPIO_OType_PP;
    port_b_led.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15;
    port_b_led.GPIO_Speed = GPIO_Speed_25MHz;
    port_b_led.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB,&port_b_led);
}

// NV08-C (GPS-NAVY) - HardWare
void gps_init() 
{
  // Sleep
  GPIO_InitTypeDef sleep_pin;
    sleep_pin.GPIO_Mode = GPIO_Mode_IN;
    sleep_pin.GPIO_OType = GPIO_OType_PP;
    sleep_pin.GPIO_Pin =  GPIO_Pin_12;
    sleep_pin.GPIO_Speed = GPIO_Speed_100MHz;
    sleep_pin.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA,&sleep_pin);
  
  // nRST
  GPIO_InitTypeDef nrst_pin;
    nrst_pin.GPIO_Mode = GPIO_Mode_OUT;
    nrst_pin.GPIO_OType = GPIO_OType_PP;
    nrst_pin.GPIO_Pin =  GPIO_Pin_8;
    nrst_pin.GPIO_Speed = GPIO_Speed_100MHz;
    nrst_pin.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA,&nrst_pin);
  GPIO_ResetBits(GPIOA,GPIO_Pin_8);
  for(int delay_nrst = 0; delay_nrst < 0xFFFF; delay_nrst++);
  GPIO_SetBits(GPIOA, GPIO_Pin_8);
  
  // PPS
  GPIO_InitTypeDef pps_pin;
    pps_pin.GPIO_Mode = GPIO_Mode_IN;
    pps_pin.GPIO_OType = GPIO_OType_PP;
    pps_pin.GPIO_Pin =  GPIO_Pin_0;
    pps_pin.GPIO_Speed = GPIO_Speed_100MHz;
    pps_pin.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA,&pps_pin);
  
  // EXT - interrupt
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  EXTI_InitTypeDef EXTI_InitStucture_0;
    EXTI_InitStucture_0.EXTI_Line = EXTI_Line0;
    EXTI_InitStucture_0.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStucture_0.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStucture_0.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStucture_0);

  NVIC_InitTypeDef NVIC_InitStructure_EXTI;
    NVIC_InitStructure_EXTI.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure_EXTI.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure_EXTI.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure_EXTI.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure_EXTI);
  EXTI_ClearITPendingBit(EXTI_Line0);
}

// NV08-C (GPS-NAVY) - USART1
void usart1_init()
{  
  // USART1 - interrupt
  NVIC_InitTypeDef NVIC_InitStructure_USART_GPS;
    NVIC_InitStructure_USART_GPS.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure_USART_GPS.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure_USART_GPS.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure_USART_GPS.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure_USART_GPS);
  
  // USART1
  USART_InitTypeDef usart_gps;
    usart_gps.USART_BaudRate = 115200;
    usart_gps.USART_WordLength = USART_WordLength_9b;
    usart_gps.USART_StopBits = USART_StopBits_1;
    usart_gps.USART_Parity = USART_Parity_Odd;
    usart_gps.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_gps.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART1, &usart_gps);
  
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ClearFlag(USART1,USART_FLAG_RXNE);
  USART_Cmd(USART1, ENABLE);
}

void console_init()
{
#if defined(PRINTF_CAN_USED)
  GPIO_InitTypeDef usart6_pin;
    usart6_pin.GPIO_Mode = GPIO_Mode_AF;
    usart6_pin.GPIO_OType = GPIO_OType_PP;
    usart6_pin.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    usart6_pin.GPIO_Speed = GPIO_Speed_50MHz;
    usart6_pin.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC,&usart6_pin);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);//Tx
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);//Rx
  
  GPIO_InitTypeDef de_pin;
    de_pin.GPIO_Mode = GPIO_Mode_OUT;
    de_pin.GPIO_OType = GPIO_OType_PP;
    de_pin.GPIO_Pin =  GPIO_Pin_8;
    de_pin.GPIO_Speed = GPIO_Speed_25MHz;
    de_pin.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC,&de_pin);
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  
  USART_InitTypeDef usart_console;
    usart_console.USART_BaudRate = CONSOLE_SPEED;
    usart_console.USART_WordLength = USART_WordLength_8b;
    usart_console.USART_StopBits = USART_StopBits_1;
    usart_console.USART_Parity = USART_Parity_No;
    usart_console.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_console.USART_Mode = USART_Mode_Tx;
  USART_Init(USART_CONSOLE, &usart_console);
  USART_Cmd(USART_CONSOLE, ENABLE);
  
  GPIO_SetBits(GPIOC, GPIO_Pin_8);
#endif
}

// TIM2
void timer2_init()
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure2;
    TIM_TimeBaseStructure2.TIM_RepetitionCounter = 0;
    TIM_TimeBaseStructure2.TIM_Period = 20000-1;//500 Hz
    TIM_TimeBaseStructure2.TIM_Prescaler = 3600-1;
    TIM_TimeBaseStructure2.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure2.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure2);
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
      NVIC_InitTypeDef 	NVIC_InitStructure2;
      NVIC_InitStructure2.NVIC_IRQChannel = TIM2_IRQn;
      NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 3;
      NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 3;
      NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure2);
    TIM_ITConfig((TIM_TypeDef *)TIM2_BASE,TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit((TIM_TypeDef *)TIM2_BASE, TIM_IT_Update);
    NVIC_EnableIRQ(TIM2_IRQn);
  //------------------------------------------------------------------------
  TIM_Cmd(TIM2, ENABLE);
}

