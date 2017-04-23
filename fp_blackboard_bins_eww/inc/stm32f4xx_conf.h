/**
  ******************************************************************************
  * @file    stm32f4xx_conf.h  
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   Library configuration file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_CONF_H
#define __STM32F4xx_CONF_H

/* Includes ------------------------------------------------------------------*/
typedef unsigned long long uint64;
typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed long long int64;
typedef signed long int32;
typedef signed short int16;
typedef signed char int8;
/* Uncomment the line below to enable peripheral header file inclusion */
#include "stm32f4xx_adc.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_crc.h"
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dbgmcu.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_wwdg.h"
#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* If an external clock source is used, then the value of the following define 
   should be set to the value of the external clock source, else, if no external 
   clock is used, keep this define commented */
/*#define I2S_EXTERNAL_CLOCK_VAL   12288000 */ /* Value of the external clock in Hz */


/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed. 
  *   If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else

#endif /* USE_FULL_ASSERT */

#define	M_RCC_APB1PeriphClockEnable(RCC_APB1Periph)		RCC->APB1ENR |= RCC_APB1Periph
#define	M_RCC_APB1PeriphClockDisable(RCC_APB1Periph)	RCC->APB1ENR &= ~RCC_APB1Periph

#define	M_RCC_APB2PeriphClockEnable(RCC_APB2Periph)		RCC->APB2ENR |= RCC_APB2Periph
#define	M_RCC_APB2PeriphClockDisable(RCC_APB2Periph)	RCC->APB2ENR &= ~RCC_APB2Periph

#define M_PIO_SET(_base,_pins) (((GPIO_TypeDef *) _base)->BSRRL = _pins)
#define M_PIO_RST(_base,_pins) (((GPIO_TypeDef *) _base)->BSRRH = _pins)
#define M_PIO_Trigg(_base,_pins) (((GPIO_TypeDef *) _base)->ODR ^= _pins)
#define	M_PIO_Get(_base,pins)	((((GPIO_TypeDef *)_base)->IDR) & pins)

//	USART
#define 		M_UARTCharPut(g_ulBase, ch)		{  	USART_SendData((USART_TypeDef *)g_ulBase ,ch);\
													while(USART_GetFlagStatus((USART_TypeDef *)g_ulBase , USART_FLAG_TC)==RESET);\
													USART_ClearFlag((USART_TypeDef *)g_ulBase , USART_FLAG_TC);	}

#define			M_UARTCharGet(g_ulBase)				(uint16_t)(((USART_TypeDef *)g_ulBase)->DR & (uint16_t)0x01FF)

#define			M_USART_RX_ENABLE(g_ulBase)			((USART_TypeDef *)g_ulBase)->CR1 |= USART_Mode_Rx
#define			M_USART_RX_DISABLE(g_ulBase)		((USART_TypeDef *)g_ulBase)->CR1 &= (uint16_t)~((uint16_t)USART_Mode_Rx)
#define			M_USART_TX_ENABLE(g_ulBase)			((USART_TypeDef *)g_ulBase)->CR1 |= USART_Mode_Tx
#define			M_USART_TX_DISABLE(g_ulBase)		((USART_TypeDef *)g_ulBase)->CR1 &= (uint16_t)~((uint16_t)USART_Mode_Tx)

#define 		M_USART_DISABLE(g_ulBase) 			((USART_TypeDef *)g_ulBase)->CR1 &= (uint16_t)~((uint16_t)USART_CR1_UE)
#define 		M_USART_ENABLE(g_ulBase) 			((USART_TypeDef *)g_ulBase)->CR1 |= USART_CR1_UE
#define			M_USART_DMA_Enable(USARTx)			USARTx->CR3 |= (uint16_t) USART_DMAReq
#define			M_USART_DMA_Disable(USARTx)			USARTx->CR3 &= (uint16_t)~USART_DMAReq

//	Timers
#define			M_TIM_ClearITPendingBit(TIMx, TIM_IT)	TIMx->SR = (uint16_t)~TIM_IT
#define			M_TIM_GetITStatus_IT(TIMx, TIM_IT)		TIMx->SR & TIM_IT
#define			M_TIM_GetITStatus_DMA(TIMx, TIM_IT)		TIMx->DIER & TIM_IT
#define 		M_TIM_SetCounter(TIMx, Counter)			TIMx->CNT = Counter
#define 		M_TIM_Counter(TIMx)						TIMx->CNT
#define			M_TIM_SetPeriod(TIMx,Period)			TIMx->ARR = ((uint32_t)Period)
#define			M_TIM_Period(TIMx)						TIMx->ARR
#define 		M_TIM_Enable(TIMx)						TIMx->CR1 |= TIM_CR1_CEN
#define 		M_TIM_Disable(TIMx)						TIMx->CR1 &= (uint16_t)~TIM_CR1_CEN

#define			M_RCC1_Disable(perif)				RCC->APB1ENR &= ~perif
#define			M_RCC2_Disable(perif)				RCC->APB2ENR &= ~perif
#define			M_RCC1_Enable(perif)				RCC->APB1ENR |= perif
#define			M_RCC2_Enable(perif)				RCC->APB2ENR |= perif

#define 		M_TIM_GenerateEvent(TIMx, TIM_EvSrc)	TIMx->EGR = TIM_EvSrc

//	EXTI
#define 		M_EXTI_ClearITPendingBit(EXTI_Line)		EXTI->PR = EXTI_Line
#define			M_EXTI_GetITStatus(EXTI_Line)			((EXTI->PR & EXTI_Line) && (EXTI->IMR & EXTI_Line))

//	Ethernet
#define M_ETH_SoftwareReset()			(ETH->DMABMR |= ETH_DMABMR_SR)
#define M_ETH_GetSoftwareResetStatus()	(ETH->DMABMR & ETH_DMABMR_SR)
#define	M_ETH_FlushTransmitFIFO()		ETH->DMAOMR |= ETH_DMAOMR_FTF

//	DMA
//#define 	HIGH_ISR_MASK           (uint32_t)0x20000000
//#define 	RESERVED_MASK           (uint32_t)0x0F7D0F7D
#define M_DMA1_GetITStatus(DMA_IT) 	(uint32_t)\
									((DMA1->HISR & (DMA_IT & (uint32_t)0x0F7D0F7D))\
									|\
									(DMA1->LISR & (DMA_IT & (uint32_t)0x0F7D0F7D)))
#define M_DMA2_GetITStatus(DMA_IT) 	(uint32_t)\
									((DMA2->HISR & (DMA_IT & (uint32_t)0x0F7D0F7D))\
									|\
									(DMA2->LISR & (DMA_IT & (uint32_t)0x0F7D0F7D)))
#define 	M_DMA1_ClearITPendingBit(DMA_IT) \
						switch(DMA_IT & (uint32_t)0x20000000)\
						{\
						case 0:\
						DMA1->LIFCR = (uint32_t)(DMA_IT & (uint32_t)0x0F7D0F7D);\
						break;\
						default:\
						DMA1->HIFCR = (uint32_t)(DMA_IT & (uint32_t)0x0F7D0F7D);\
						break;\
						}
#define 	M_DMA2_ClearITPendingBit(DMA_IT) \
						switch(DMA_IT & (uint32_t)0x20000000)\
						{\
						case 0:\
						DMA2->LIFCR = (uint32_t)(DMA_IT & (uint32_t)0x0F7D0F7D);\
						break;\
						default:\
						DMA2->HIFCR = (uint32_t)(DMA_IT & (uint32_t)0x0F7D0F7D);\
						break;\
						}
#define	M_DMA_Set_BufferSize(DMAy_Streamx,size)					\
											DMAy_Streamx->NDTR 	= size
#define	M_DMA_Set_PeripheralBaseAddr(DMAy_Streamx,addr)	\
											DMAy_Streamx->PAR 	= addr
#define	M_DMA_Set_Memory0BaseAddr(DMAy_Streamx,mem0)			\
											DMAy_Streamx->M0AR 	= mem0
#define	M_DMA_Enable(DMAy_Streamx)	DMAy_Streamx->CR |=  (uint32_t)DMA_SxCR_EN
#define	M_DMA_Disable(DMAy_Streamx)	DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_EN

//	SPI
#define	M_SPI_Enable(SPIx_base)				((((SPI_TypeDef* )SPIx_base)->CR1) |= SPI_CR1_SPE)
#define	M_SPI_Disable(SPIx_base)			((((SPI_TypeDef* )SPIx_base)->CR1) &= (uint16_t)~((uint16_t)SPI_CR1_SPE))
#define M_SPI_GetData(SPIx_base)			(((SPI_TypeDef* )SPIx_base)->DR)
#define	M_SPI_SetData(SPIx_base,data)		((((SPI_TypeDef* )SPIx_base)->DR) = data)
#define	M_SPI_GetFlag(SPIx_base, FLAG)		((((SPI_TypeDef* )SPIx_base)->SR) & FLAG)
#define	M_SPI_ClearFlag(SPIx_base, FLAG)	((((SPI_TypeDef* )SPIx_base)->SR) = (uint16_t)~FLAG)

#endif /* __STM32F4xx_CONF_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
