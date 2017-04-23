/*!
 * \file		init.c
 * \author		Ванин А.В.
 * \version
 * \date		25.07.2012
 * \details		
 */

#include "local_init.h"
//#include "usart_op.h"

//
void	GPIO_config(	uint32_t _base,
						uint32_t _pins,
						GPIOMode_TypeDef _mode,
						GPIOSpeed_TypeDef _speed,
						GPIOOType_TypeDef _oType,
						GPIOPuPd_TypeDef _PuPd,
						int8_t	 _afunc
						)
{
	if((_base > GPIOI_BASE))		return;
	//	Enable clocking
	uint32_t arb_addr = 0;
	arb_addr = 1 << ((_base - GPIOA_BASE)/0x400);

	RCC_AHB1PeriphClockCmd(arb_addr, ENABLE);

	//	Structure init
	GPIO_InitTypeDef _init;
	_init.GPIO_Pin = _pins;
	_init.GPIO_Mode = _mode;
	_init.GPIO_OType = _oType;
	_init.GPIO_PuPd = _PuPd;
	_init.GPIO_Speed = _speed;
	GPIO_Init((GPIO_TypeDef *)_base, &_init);

	//	Alternate pins function
	if(_afunc >= 0)
	{
		for(int i = 0; i < GPIO_Pin_15; i++)
		{
			if((_pins&0x0001))
			{
				GPIO_PinAFConfig(((GPIO_TypeDef *)_base),i,_afunc);
			}
			_pins /=2;
		}
	}
}
void	GPIO_IT_config(	uint8_t  			_EXTI_PortSourceGPIOx,
						uint32_t 			_EXTI_PinSource,
						EXTITrigger_TypeDef _trigger,
						uint16_t 			_prio,
						IRQn_Type 			_type)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Connect EXTI Line to pin */
	SYSCFG_EXTILineConfig(_EXTI_PortSourceGPIOx, _EXTI_PinSource);

	/* Configure EXTI Line */
	EXTI_InitStructure.EXTI_Line = 1 << _EXTI_PinSource;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = _trigger;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = _type;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _prio;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//
void	UART_config(uint32_t _base, uint32_t _baud,uint16_t _mode, uint16_t _flags)
{
	/* Configure the Priority Group to 1 bit */
	NVIC_InitTypeDef nvic_init;
	/* Configure the SPI interrupt priority */
	NVIC_PriorityGroupConfig(NVIC_GROUPING);
	//	Clocking
	switch(_base)
	{
	case USART1_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);
		nvic_init.NVIC_IRQChannel = USART1_IRQn;
		break;
	case USART2_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
		nvic_init.NVIC_IRQChannel = USART2_IRQn;
		break;
	case USART3_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
		nvic_init.NVIC_IRQChannel = USART3_IRQn;
		break;
	case UART4_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE);
		nvic_init.NVIC_IRQChannel = UART4_IRQn;
		break;
	case UART5_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 , ENABLE);
		nvic_init.NVIC_IRQChannel = UART5_IRQn;
		break;
	case USART6_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6 , ENABLE);
		nvic_init.NVIC_IRQChannel = USART6_IRQn;
		break;
	case UART7_BASE:
		 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7 , ENABLE);
		 nvic_init.NVIC_IRQChannel = UART7_IRQn;
		 break;
	case UART8_BASE:
		 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8 , ENABLE);
		 nvic_init.NVIC_IRQChannel = UART8_IRQn;
		 break;
	default:
		return;
	}

	//	TuneUp
	USART_InitTypeDef usart_par;
	usart_par.USART_BaudRate = _baud;
	usart_par.USART_WordLength = USART_WordLength_8b;
	usart_par.USART_StopBits = USART_StopBits_1;
	usart_par.USART_Parity = USART_Parity_No;
	usart_par.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_par.USART_Mode = _mode;
	USART_Init((USART_TypeDef *) _base, &usart_par);
	//	Interrupt
	if(_flags)
	{
		nvic_init.NVIC_IRQChannelPreemptionPriority = 15;
		nvic_init.NVIC_IRQChannelSubPriority = 0;
		nvic_init.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic_init);
		USART_ITConfig((USART_TypeDef *) _base,_flags,ENABLE);
		USART_ClearFlag((USART_TypeDef *) _base,_flags);
	}
	USART_Cmd((USART_TypeDef *) _base, ENABLE);
}
//
void SPI_config(uint32_t _base, uint32_t _baud, uint16_t _data_size, uint16_t _flags)
{
	/* Configure the Priority Group to 1 bit */
	NVIC_InitTypeDef nvic_init;
	/* Configure the SPI interrupt priority */
	NVIC_PriorityGroupConfig(NVIC_GROUPING);
	//	Clocking
	switch(_base)
	{
	case SPI1_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		nvic_init.NVIC_IRQChannel = SPI1_IRQn;
		break;
	case SPI2_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		nvic_init.NVIC_IRQChannel = SPI2_IRQn;
		break;
	case SPI3_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
		nvic_init.NVIC_IRQChannel = SPI3_IRQn;
	case SPI4_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
		nvic_init.NVIC_IRQChannel = SPI4_IRQn;
	case SPI5_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
		nvic_init.NVIC_IRQChannel = SPI5_IRQn;
	case SPI6_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI6, ENABLE);
		nvic_init.NVIC_IRQChannel = SPI6_IRQn;
		break;
	default:
		return;
	}

	SPI_InitTypeDef 				SPI_par;
	SPI_par.SPI_Direction 			= SPI_Direction_2Lines_FullDuplex;
	SPI_par.SPI_Mode 				= SPI_Mode_Master;
	SPI_par.SPI_DataSize 			= _data_size;
	SPI_par.SPI_CPOL 				= SPI_CPOL_High;
	SPI_par.SPI_CPHA 				= SPI_CPHA_2Edge;
	SPI_par.SPI_NSS 				= SPI_NSS_Soft;
	SPI_par.SPI_BaudRatePrescaler 	= _baud;
	SPI_par.SPI_FirstBit 			= SPI_FirstBit_MSB;
	SPI_par.SPI_CRCPolynomial 		= 0x07;
	SPI_Init((SPI_TypeDef *) _base, &SPI_par);

	if(_flags)
	{
		nvic_init.NVIC_IRQChannelPreemptionPriority = 3;
		nvic_init.NVIC_IRQChannelSubPriority = 0;
		nvic_init.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic_init);
		SPI_I2S_ITConfig((SPI_TypeDef *) _base,_flags,ENABLE);
		SPI_I2S_ClearFlag((SPI_TypeDef *) _base, _flags);
	}
	M_SPI_Enable(SPI1_BASE);
}
//
void	TIM_config(	uint32_t _base,
					uint32_t _cnt,
					uint16_t _presc,
					IRQn_Type irq_type,
					uint16_t _flags,
					uint16_t _prio,
					uint8_t	 _state)
{
	switch(_base)
	{
	case TIM1_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
		break;
	case TIM2_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
		break;
	case TIM3_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
		break;
	case TIM4_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
		break;
	case TIM5_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);
		break;
	case TIM6_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
		break;
	case TIM7_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);
		break;
	case TIM8_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);
		break;
	case TIM9_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9 , ENABLE);
		break;
	case TIM10_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10 , ENABLE);
		break;
	case TIM11_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11 , ENABLE);
		break;
	default:
		return;
	}
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = _cnt-1;//count;
	TIM_TimeBaseStructure.TIM_Prescaler = _presc-1;//PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit((TIM_TypeDef *)_base, &TIM_TimeBaseStructure);

	if(_flags)
	{
		NVIC_PriorityGroupConfig(NVIC_GROUPING);
		NVIC_InitTypeDef 	NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = irq_type;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _prio;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		TIM_ITConfig((TIM_TypeDef *)_base,_flags, ENABLE);
		TIM_ClearITPendingBit((TIM_TypeDef *)_base, _flags);
	}
	TIM_Cmd((TIM_TypeDef *)_base, _state);
}
