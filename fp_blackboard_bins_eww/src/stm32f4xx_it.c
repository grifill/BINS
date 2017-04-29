/* Includes ------------------------------------------------------------------*/
#include 	"stm32f4xx_it.h"
#include 	<string.h>
#include 	<time.h>
#include 	"binr_parse.h"
/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}
//---------------------------------------------------------------------------
//				GPS 1-pps
//---------------------------------------------------------------------------
/*
void EXTI0_IRQHandler(void)
{
  switch(EXTI_GetITStatus(EXTI_Line0))
	{
	case 0:
		break;
	default:
		switch (gps_send_buf)
		{
			case 0:
				for(int y=0; y<9900000;y++);// delay to init navis
				pluWriteDataDMA(1,buf,5);
				gps_send_buf=1;
				break;
			 default:
				 switch(idx)
				 {
				 	case 0:
				 		M_TIM_Enable(TIM4);
				 		break;
				 }
				GPIOC->ODR^=GPIO_Pin_13;//LED
				gps_send_buf = 2;
		}
		M_EXTI_ClearITPendingBit(EXTI_Line0);
		break;
	}
}
//	---------------------------------------------------------------------------
//					GPS - Rx / Tx - BINR
//	---------------------------------------------------------------------------
void USART1_IRQHandler()
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		binr_response = (uint8_t)(USART1->DR & (uint8_t)0xFF);
		if ((binr_response == DLE) && (flag_dle != 1) && (flag_frame != 1))
		{
			buf_binr[id_rx]=binr_response;
			id_rx++;
			flag_dle=1;
		}
		else if ((binr_response == ID) && (flag_dle == 1) && (flag_frame != 1))
		{
			buf_binr[id_rx]=binr_response;
			id_rx++;
			flag_frame=1;
			flag_dle=0;
		}
		else if ((binr_response == DLE) && (flag_dle == 0) && (flag_frame == 1))
		{
			buf_binr[id_rx]=binr_response;
			id_rx++;
			flag_dle=1;
		}
		else if ((binr_response == DLE) && (flag_dle == 1) && (flag_frame == 1))
		{
			flag_dle=0;
		}
		else
		{
			flag_frame=1;
			buf_binr[id_rx]=binr_response;
			id_rx++;
			if ((id_rx==38))
			{
				memmove (&time_week, &buf_binr[2], 12);
				memmove (&time_mcs, &buf_binr[2],10);
				GPIOB->ODR^=GPIO_Pin_14;//LED YELLOW
				union {
							char c[2];
							int16_t f;
						} u;
							u.c[1] = time_week[11];
							u.c[0] = time_week[10];
				time_mc= uchar_to_FP80_lendian((unsigned char*)time_mcs);
				u.f=u.f+1024;// 1024 is need for 1980 year
			 	time_conv.seconds_per_week=time_mc/1000; // seconds needed
			 	time_conv.week_number=(uint16_t)u.f;
			 	timmi = gps2time(time_conv);// timmi's name is unix time

				NTP_frame.second= (uint32_t)(timmi+2208988800);// time plus second 1900 jan
				NTP_frame.fraction=594853;
				//NTPFrameInit(NTP_frame.second, NTP_frame.fraction, (char*)ntp, 10);
				//pluWriteDataDMA(3,ntp,10);//debug
				//TRACE_DEBUG("%s", asctime(localtime(&timmi)));
				id_rx=0;
				flag_frame=0;
				flag_dle=0;
			}
		}
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
	{
		USART_ClearFlag(USART3,	USART_FLAG_TC);
		USART_ClearITPendingBit(USART3, USART_IT_TC);
		switch(idx/10)
		{
		case 0:
			USART3->DR = (ntp[idx] & (uint16_t)0x01FF);
			idx++;
			break;
		default:
			M_USART_DISABLE(USART3_BASE);
			idx = 0;
			break;
		}
	}
}
void TIM4_IRQHandler(void)
{
	switch (TIM_GetITStatus(TIM4, TIM_IT_Update))
	{
	case 0:
		break;
	default:
		NTPFrameInit(NTP_frame.second, NTP_frame.fraction, (char*)ntp, 10);
		GPIOB->ODR^=GPIO_Pin_15;// LED RED;
		USART3->DR = (ntp[idx] & (uint16_t)0x01FF);
		idx++;
		M_USART_ENABLE(USART3_BASE);
		M_TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		M_TIM_Disable(TIM4);
		TIM4->CNT = 0;
		break;
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
//-----------------------------------------------------------------
//		USART1 - GPS module request output on DMA
//-----------------------------------------------------------------
void DMA2_Stream7_IRQHandler(void)
{
	switch(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7))
	{
	case 0:
		break;
	default:
		M_DMA2_ClearITPendingBit(DMA_IT_TCIF7);
		M_DMA_Disable(DMA2_Stream7);
		break;
   }
}
*/