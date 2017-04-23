/* Includes ------------------------------------------------------------------*/
#include 	"stm32f4xx_it.h"
#include 	"debug_trace.h"
#include 	<string.h>
#include 	"usart_op.h"
#include 	<time.h>
#include 	"SYS_init.h"
#include 	"vu_tools.h"
#include 	"proto_tlm.h"
#include 	"proto_ntp.h"
#include	"crc.h"
#include	<math.h>

#include 	"plist.h"
#include 	"param.h"
#ifdef	ENABLE_DYNAMIC_ARRAY
extern TParam* 	plist;
#else
extern TParam 	plist[MAX_PLIST_CNT];
#endif
extern long		pcnt;

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//	---------------------------------------------------------------------------
void HardFault_Handler(void)
{
	TRACE_ERROR("Hard Fault\n");
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}
//	---------------------------------------------------------------------------
void MemManage_Handler(void)
{
	TRACE_ERROR("Mem Manage Fault\n");
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}
//	---------------------------------------------------------------------------
void BusFault_Handler(void)
{
	TRACE_ERROR("Bus Fault\n");
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}
//	---------------------------------------------------------------------------
void UsageFault_Handler(void)
{
	TRACE_ERROR("Usage Fault\n");
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}
//	---------------------------------------------------------------------------
uint16_t	send_cnt = 0;
uint16_t	data[6] = {0,0,0,0,0,0};
uint8_t		TIM4_ntp_local_sign = 0;
uint32_t	TIM4_add_ntp = 4294967;

void TIM4_IRQHandler(void)
{
	switch (M_TIM_GetITStatus_IT(TIM4, TIM_IT_Update))
	{
	case 0:
		break;
	default:
		M_TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

		TIM4_ntp_local_sign = pNTPCur[NTP_PSEC] / 0x7FFFFFFF;

		pNTPCur[NTP_PSEC] += TIM4_add_ntp;

		switch(pNTPCur[NTP_PSEC] / 0x7FFFFFFF)
		{
		case 0:
			switch(TIM4_ntp_local_sign)
			{
			case 1:

				TIM4_ntp_local_sign = 0;
				pNTPCur[NTP_SEC]++;
				pNTPCur[NTP_PSEC] %= 0x7FFFFFFF;
				M_PIO_Trigg(GPIOD_BASE,GPIO_Pin_0);
				break;
			}
			break;
		default:
			break;
		}

		break;
	}
}
//	---------------------------------------------------------------------------
//				USART6 - Debug output
//	---------------------------------------------------------------------------
void USART6_IRQHandler(void)
{
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{
		uint8_t ch = (USART6->DR) & 0xFF;
		pluAppendByte(0,ch);
	}
}
void DMA2_Stream6_IRQHandler(void)
{
	switch(DMA_GetITStatus(DMA2_Stream6,DMA_IT_TCIF6))
	{
	case 0:
		break;
	default:
		M_DMA2_ClearITPendingBit(DMA_IT_TCIF6);
		M_DMA_Disable(DMA2_Stream6);
		M_PIO_RST(GPIOC_BASE,GPIO_Pin_8);
		break;
   }
}
