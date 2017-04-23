#ifndef __STM32F4_DISCOVERY_H
#define __STM32F4_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif
#include 	<local_init.h>
#include 	<stm32f4xx_conf.h>
#include 	<stm32f4xx.h>
/************************************************************************
 * RS485_1:
 * 			RX_Uart_4 - PA1
 * 			TX_Uart_4 - PA0
 * 			DE1		   - PE2
 *
 * RS485_2:
 * 			RX_Usart_6 - PC7
 * 			TX_Usart_6 - PC6
 * 			DE2		   - PE4
 *
 * RS485_3:
 * 			RX_Usart_7 - PE8
 * 			TX_Usart_7 - PE7
 * 			DE3		   - PE6
 *
 * RS485_4:
 * 			RX_Usart_8 - PE1
 * 			TX_Usart_8 - PE0
 * 			DE4		   - PE11
 *
 * GPS_NV08C-CSM:
 * 			GPS_RST    - PA11
 * 			GPS_SLEEP  - PA12
 * 			GPS_PPS    - PB10
 * 			RX_Usart_1 - PA10
 * 			RX_Usart_1 - PA9
 *
 ************************************************************************/
 void init();
// Define TRUE, FALSE and bool if not defined
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#ifdef __cplusplus
}
#endif

#endif
