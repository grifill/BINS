/*!
 * \file		SYS_init.c
 * \author
 * \version
 * \date
 * \details		GPIO initialisation
 */
#include "SYS_init.h"
#include "usart_op.h"
#include "debug_trace.h"
void init()
{

	//	Sleep
	GPIO_config(	GPIOA_BASE,
					GPIO_Pin_12,
					GPIO_Mode_IN,
					GPIO_Speed_100MHz,
					GPIO_OType_PP,
					GPIO_PuPd_DOWN,
					-1);
	//	nRST
	GPIO_config(	GPIOA_BASE,
					GPIO_Pin_8,
					GPIO_Mode_OUT,
					GPIO_Speed_100MHz,
					GPIO_OType_PP,
					GPIO_PuPd_UP,
					-1);
	M_PIO_RST(GPIOA_BASE, GPIO_Pin_8);
	for(uint32_t i = 0; i < 0xFFFFF;i++);
	M_PIO_SET(GPIOA_BASE, GPIO_Pin_8);

	//	Init debug output - UART6
	GPIO_config(	GPIOC_BASE,
					GPIO_Pin_6 | GPIO_Pin_7,
					GPIO_Mode_AF,
					GPIO_Speed_50MHz,
					GPIO_OType_PP,
					GPIO_PuPd_UP,
					GPIO_AF_USART6);
   	//	Tx/nRx - Tx default
	GPIO_config(	GPIOC_BASE,
					GPIO_Pin_8,
					GPIO_Mode_OUT,
					GPIO_Speed_50MHz,
					GPIO_OType_PP,
					GPIO_PuPd_UP,
					-1);
	M_PIO_RST(GPIOC_BASE,GPIO_Pin_8);
	UART_config(USART6_BASE, 115200, USART_Mode_Tx | USART_Mode_Rx, USART_IT_RXNE);
	pluAddUSART(USART6_BASE);
	UARTStdioInit(USART6_BASE);

	//	DMA initialisation for USART6-TX
	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_DMA2EN, ENABLE);
	// Enable the USART Tx DMA request
	USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
	USART_ClearFlag(USART6, USART_FLAG_TC);
	//	NVIC init
	NVIC_InitTypeDef dma_nvic;
	dma_nvic.NVIC_IRQChannel = DMA2_Stream6_IRQn;
	dma_nvic.NVIC_IRQChannelCmd = ENABLE;
	dma_nvic.NVIC_IRQChannelPreemptionPriority = 15;
	dma_nvic.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&dma_nvic);
	DMA_ITConfig(DMA2_Stream6,DMA_IT_TC,ENABLE);

	//	LED
	GPIO_config(	GPIOD_BASE,
					GPIO_Pin_0,
					GPIO_Mode_OUT,
					GPIO_Speed_50MHz,
					GPIO_OType_PP,
					GPIO_PuPd_DOWN,
					-1);

	//	---------
	//	1ms timer
	TIM_config(TIM4_BASE,3000,12,TIM4_IRQn,TIM_IT_Update,2,1);
}
