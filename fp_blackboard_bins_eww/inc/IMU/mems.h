#ifndef __mems_H
#define __mems_H

#include        "stm32f4xx_conf.h"



#define TEMP_Sensitivity     	   (float)     1.0f           /*!< temperature sensitivity with *C [LSB] */
#define A3G_Sensitivity_245dps     (float)     114.285f       /*!< gyroscope sensitivity with 245 dps full scale [LSB/dps] */
#define L3G_Sensitivity_250dps     (float)     114.285f       /*!< gyroscope sensitivity with 250 dps full scale [LSB/dps] */
#define L3G_Sensitivity_500dps     (float)     57.1429f       /*!< gyroscope sensitivity with 500 dps full scale [LSB/dps] */
#define L3G_Sensitivity_2000dps    (float)     14.285f	      /*!< gyroscope sensitivity with 2000 dps full scale [LSB/dps] */
#define PI                         (float)     3.14159265f
#define LSM_Acc_Sensitivity_2g     (float)     0.001f            /*!< accelerometer sensitivity with 2 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_4g     (float)     0.0005f            /*!< accelerometer sensitivity with 4 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_8g     (float)     0.00025f           /*!< accelerometer sensitivity with 8 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_16g    (float)     0.0000834f         /*!< accelerometer sensitivity with 12 g full scale [LSB/mg] */



#define	SPI2_CLK	RCC_APB1Periph_SPI2
#define	SPI2_CLK_PIN	GPIO_Pin_13	// SPI A3G4250D and L3G4200D
#define	SPI2_CLK_PORT	GPIOB
#define	SPI2_MISO_PIN	GPIO_Pin_2
#define	SPI2_MOSI_PIN	GPIO_Pin_3
#define	SPI2_PORT	GPIOC

#define	NSS1_PIN	GPIO_Pin_9	// CS L3G4200D
#define	NSS1_PORT	GPIOB
//#define	NSS2_PIN	GPIO_Pin_5	// CS A3G4250D
//#define	NSS2_PORT	GPIOB


#define	INT1_PIN	GPIO_Pin_8	// INT1 LSM303DLM
#define	INT1_PORT	GPIOB
#define	INT2_PIN	GPIO_Pin_4	// INT2 LSM303DLM
#define	INT2_PORT	GPIOC
#define	SA0_PIN		GPIO_Pin_14	// SA0 Acc LSM303DLM
#define	SA0_PORT	GPIOB
#define	DRDY_M_PIN	GPIO_Pin_15	// DRDY Mag LSM303DLM
#define	DRDY_M_PORT	GPIOB

#define	I2C2_SCL_PIN	GPIO_Pin_10	// I2C Acc LSM303DLM
#define	I2C2_SDA_PIN	GPIO_Pin_11	//
#define	I2C2_CLK	RCC_APB1Periph_I2C2
#define	I2C2_PORT	GPIOB
#define	I2C1_SCL_PIN	GPIO_Pin_6	// I2C Mag LSM303DLM
#define	I2C1_SDA_PIN	GPIO_Pin_7	//
#define	I2C1_CLK	RCC_APB1Periph_I2C1
#define	I2C1_PORT	GPIOB

#define	SINT11_PIN	GPIO_Pin_9	// INT L3G4200D
#define	SINT11_PORT	GPIOC
#define	SINT12_PIN	GPIO_Pin_5	// DRDY/INT2 L3G4200D
#define	SINT12_PORT	GPIOC
//#define	SINT21_PIN	GPIO_Pin_2	// INT A3G4250D
//#define	SINT21_PORT	GPIOD
//#define	SINT22_PIN	GPIO_Pin_12	// DRDY/INT2 A3G4250D
//#define	SINT22_PORT	GPIOB






#define I2C_SLAVE_ADDRESS7     0xA0	//
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_Speed              100000
//#define I2C_Speed              100000 //the real freq is 200KHz! (????)
//#define I2C_Speed              200000 //the real freq is KHz! (????)
//#define I2C_Speed              400000
#define I2C_SLAVE_ADDRESS7     0xA0
#define I2C_TIMEOUT             100
/* I2C STOP mask */
#define CR1_STOP_Set            ((uint16_t)0x0200)
#define CR1_STOP_Reset          ((uint16_t)0xFDFF)
/* I2C ACK mask */
#define CR1_ACK_Set             ((uint16_t)0x0400)
#define CR1_ACK_Reset           ((uint16_t)0xFBFF)
/* I2C POS mask */
#define CR1_POS_Set             ((uint16_t)0x0800)
#define CR1_POS_Reset           ((uint16_t)0xF7FF)



#define I2C_Acc		I2C2
#define	I2C_Mag		I2C1

#define CS_A3G4250D	0
#define CS_L3G4200D	1

#define DUMMY_BYTE    0xA5

#define I2C_num         I2C2


void SPI_Mems_Init(void);
void SPI_Mems_DeInit(void);
void I2C_MEMS_Init(void);
void I2C_MEMS_DeInit();
uint8_t I2C_BufferRead(uint8_t* pBuffer, uint8_t deviceAddr, uint8_t readAddr, uint16_t numByteToRead);
void I2C_ByteWrite(uint8_t* pBuffer, uint8_t deviceAddress, uint8_t WriteAddr);
uint8_t SPI_Mems_Read_Reg(uint8_t MemsType, uint8_t reg);
void SPI_Mems_Write_Reg(uint8_t MemsType,uint8_t regAddr, uint8_t data);
void SPI_Read_MultiData(uint8_t MemsType, uint8_t regAddr, uint8_t length, uint8_t* buffer);
uint8_t SPI_Mems_SendByte(uint8_t byte);


#endif
