/* Includes ------------------------------------------------------------------*/
#include 	"stm32f4xx_it.h"
#include 	<string.h>
#include 	<time.h>
#include 	"binr_parse.h"

#include "mems.h"
#include "lsm303dlhc_driver.h"
#include "l3g4200d_driver.h"
#include "func_tools.h"

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
      GPIOB->ODR^=GPIO_Pin_15;
      break;
    default:
      GPIOC->ODR^=GPIO_Pin_13; //LED
      break;
  }
  EXTI_ClearITPendingBit(EXTI_Line0);
}*/

extern uint8_t response;
extern L3GAxesRaw_t data_l3g;
extern AccAxesRaw_t data_a;
extern MagAxesRaw_t data_m;
//--- gyroscope -------------
int32_t xg=0;
int32_t yg=0;
int32_t zg=0;


void TIM2_IRQHandler(void)
{
  switch (TIM_GetITStatus(TIM2, TIM_IT_Update))
  {
    case 0:
      break;
    default:
      L3G4200D_GetAngRateRaw(&data_l3g);
      xg = data_l3g.AXIS_X;
      yg = data_l3g.AXIS_Y;
      zg = data_l3g.AXIS_Z;
      PRINT(">>> Gyro data: (%d, %d, %d)\n",xg,yg,zg);
      GPIOB->ODR^=GPIO_Pin_14;
  }
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}