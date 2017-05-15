#include "mems.h"


/*******************************************************************************
* Function Name  : SPI_3W_Mems_Init
* Description    : Initializes the peripherals used by the 3 wires SPI Mems driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Mems_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable SPI and GPIO clocks */
  RCC_APB1PeriphClockCmd(SPI2_CLK, ENABLE);

    /* Configure SPI pins: SCK, MISO and MOSI */
    GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_PIN|SPI2_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI2_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = SPI2_CLK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI2_CLK_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(SPI2_PORT,GPIO_PinSource2,GPIO_AF_SPI2);
    GPIO_PinAFConfig(SPI2_PORT,GPIO_PinSource3,GPIO_AF_SPI2);
    GPIO_PinAFConfig(SPI2_CLK_PORT,GPIO_PinSource13,GPIO_AF_SPI2);

  /* Configure I/O for MEMS Chip select */
  GPIO_InitStructure.GPIO_Pin = NSS1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(NSS1_PORT, &GPIO_InitStructure);

  /* Configure I/O for MEMS Chip select */
  //GPIO_InitStructure.GPIO_Pin = NSS2_PIN;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  //GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  //GPIO_Init(NSS2_PORT, &GPIO_InitStructure);

  /* Deselect Mems Sensor: Chip Select high */
  Pin_Set(NSS1_PORT,NSS1_PIN);
 // Pin_Set(NSS2_PORT,NSS2_PIN);

  /* SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;		// Fclk=5.25 MHz /2
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* Enable the SPI  */
  SPI_Cmd(SPI2, ENABLE);
}

/*******************************************************************************
* Function Name  : SPI_Mems_DeInit
* Description    : DeInitializes the peripherals used by the SPI Mems driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Mems_DeInit(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin =SPI2_MOSI_PIN|SPI2_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(SPI2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =SPI2_CLK_PIN ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(SPI2_CLK_PORT, &GPIO_InitStructure);

  /* Configure I/O for MEMS Chip select */
    GPIO_InitStructure.GPIO_Pin = NSS1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(NSS1_PORT, &GPIO_InitStructure);

    /* Configure I/O for MEMS Chip select */
   // GPIO_InitStructure.GPIO_Pin = NSS2_PIN;
   // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   // GPIO_Init(NSS2_PORT, &GPIO_InitStructure);

}


/*******************************************************************************
* Function Name  : I2C_MEMS_Init
* Description    : I2C Initialization
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_MEMS_Init(void)
{

    /* I2C Periph clock enable */
    RCC_APB1PeriphClockCmd(I2C1_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(I2C2_CLK, ENABLE);

    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Configure I2C_EE pins: SCL and SDA */
    GPIO_InitStructure.GPIO_Pin =  I2C1_SCL_PIN | I2C1_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_Init(I2C1_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(I2C1_PORT,GPIO_PinSource6,GPIO_AF_I2C1);
    GPIO_PinAFConfig(I2C1_PORT,GPIO_PinSource7,GPIO_AF_I2C1);

    /* Configure I2C_EE pins: SCL and SDA */
    GPIO_InitStructure.GPIO_Pin =  I2C2_SCL_PIN | I2C2_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_Init(I2C2_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(I2C2_PORT,GPIO_PinSource10,GPIO_AF_I2C2);
    GPIO_PinAFConfig(I2C2_PORT,GPIO_PinSource11,GPIO_AF_I2C2);

    /* Configure the GPIO_SA0 pin */
    GPIO_InitStructure.GPIO_Pin = SA0_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SA0_PORT, &GPIO_InitStructure);

    I2C_InitTypeDef  I2C_InitStructure;

    /* I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS7;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
    /* I2C Peripheral Enable */
    I2C_Cmd(I2C1, ENABLE);
    /* Apply I2C configuration after enabling it */
    I2C_Init(I2C1, &I2C_InitStructure);

    /* I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS7;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
    /* I2C Peripheral Enable */
    I2C_Cmd(I2C2, ENABLE);
    /* Apply I2C configuration after enabling it */
    I2C_Init(I2C2, &I2C_InitStructure);

    Pin_Set(SA0_PORT,SA0_PIN);
}

void I2C_MEMS_DeInit()
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* UnConfigure I2C_MEMS pins: SCL and SDA */
    GPIO_InitStructure.GPIO_Pin =  I2C2_SCL_PIN | I2C2_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(I2C2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  I2C1_SCL_PIN | I2C1_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(I2C1_PORT, &GPIO_InitStructure);

}


/*******************************************************************************
* Function Name  : I2C_BufferRead
* Description    : read a numByteToRead bytes from I2C Bus
* Input          : deviceAddr is the I2C address of the device
*                  readAddr is the register address you want to read from
*                  numByteToRead is the number of bytes to read
* Output         : pBuffer is the buffer that contains bytes read
* Return         : None
*******************************************************************************/
uint8_t I2C_BufferRead(uint8_t* pBuffer, uint8_t deviceAddr, uint8_t readAddr, uint16_t numByteToRead)
{
  //uint8_t i2cTimeOut = 0;
  //uint8_t i2cTimeOut2 = 0;
    __IO uint32_t temp = 0;

    if(numByteToRead > 1) {
      readAddr |= 0x80;
    }

  // /* While the bus is busy * /
  while(I2C_GetFlagStatus(I2C_num, I2C_FLAG_BUSY));

  // * Send START condition * /
  I2C_GenerateSTART(I2C_num, ENABLE);

  // / * Test on EV5 and clear it * /
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_MODE_SELECT));

  // / * Send EEPROM address for write  * /
  I2C_Send7bitAddress(I2C_num, deviceAddr, I2C_Direction_Transmitter);

  // / * Test on EV6 and clear it * /
  //while(!I2C_CheckEvent(I2C_MEMS, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) ;

  // / * Send the EEPROM's internal address to read from: Only one byte address  * /
  I2C_SendData(I2C_num, readAddr);

  /// * Test on EV8 and clear it * /
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /// * Send STRAT condition a second time * /
  I2C_GenerateSTART(I2C_num, ENABLE);

  /// * Test on EV5 and clear it * /
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_MODE_SELECT));

    // * Send EEPROM address for read * /
  I2C_Send7bitAddress(I2C_num, deviceAddr, I2C_Direction_Receiver);

  if (numByteToRead == 1)  {
    /* Wait until ADDR is set */
    while ((I2C_num->SR1&0x0002) != 0x0002);
   /* Clear ACK bit */
    I2C_num->CR1 &= CR1_ACK_Reset;
    /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
    software sequence must complete before the current byte end of transfer */
    __disable_irq();
    /* Clear ADDR flag */
    temp = I2C_num->SR2;
    /* Program the STOP */
   I2C_GenerateSTOP(I2C_num, ENABLE);
    /* Re-enable IRQs */
    __enable_irq();
    /* Wait until a data is received in DR register (RXNE = 1) EV7 */
     while ((I2C_num->SR1 & 0x00040) != 0x000040);
    /* Read the data */
      *pBuffer = I2C_num->DR;

  }
  else if (numByteToRead == 2) {

    /* Set POS bit */
      I2C_num->CR1 |= CR1_POS_Set;
    /* Wait until ADDR is set: EV6 */
    while ((I2C_num->SR1&0x0002) != 0x0002);
    /* EV6_1: The acknowledge disable should be done just after EV6,
    that is after ADDR is cleared, so disable all active IRQs around ADDR clearing and
    ACK clearing */
    __disable_irq();
    /* Clear ADDR by reading SR2 register  */
    temp = I2C_num->SR2;
    /* Clear ACK */
    I2C_num->CR1 &= CR1_ACK_Reset;
    /*Re-enable IRQs */
    __enable_irq();
    /* Wait until BTF is set */
    while ((I2C_num->SR1 & 0x00004) != 0x000004);
    /* Disable IRQs around STOP programming and data reading */
    __disable_irq();
    /* Program the STOP */
    I2C_GenerateSTOP(I2C_num, ENABLE);
    /* Read first data */
    *pBuffer = I2C_num->DR;
    /* Re-enable IRQs */
    __enable_irq();
    /**/
    pBuffer++;
    /* Read second data */
    *pBuffer = I2C_num->DR;
    /* Clear POS bit */
    I2C_num->CR1  &= CR1_POS_Reset;
  }


  else { //numByteToRead > 2
    // * Test on EV6 and clear it * /
    while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    // * While there is data to be read * /
    while(numByteToRead)   {
      /* Receive bytes from first byte until byte N-3 */
      if (numByteToRead != 3) {
        /* Poll on BTF to receive data because in polling mode we can not guarantee the
        EV7 software sequence is managed before the current byte transfer completes */
        while ((I2C_num->SR1 & 0x00004) != 0x000004);
        /* Read data */
        *pBuffer = I2C_num->DR;
         pBuffer++;
        /* Decrement the read bytes counter */
        numByteToRead--;
      }

      /* it remains to read three data: data N-2, data N-1, Data N */
      if (numByteToRead == 3) {
        /* Wait until BTF is set: Data N-2 in DR and data N -1 in shift register */
        while ((I2C_num->SR1 & 0x00004) != 0x000004);
        /* Clear ACK */
        I2C_num->CR1 &= CR1_ACK_Reset;

        /* Disable IRQs around data reading and STOP programming */
        __disable_irq();
        /* Read Data N-2 */
        *pBuffer = I2C_num->DR;
        /* Increment */
        pBuffer++;
        /* Program the STOP */
        I2C_num->CR1 |= CR1_STOP_Set;
        /* Read DataN-1 */
        *pBuffer = I2C_num->DR;
        /* Re-enable IRQs */
        __enable_irq();
        /* Increment */
        pBuffer++;
        /* Wait until RXNE is set (DR contains the last data) */
        while ((I2C_num->SR1 & 0x00040) != 0x000040);
        /* Read DataN */
        *pBuffer = I2C_num->DR;
        /* Reset the number of bytes to be read by master */
        numByteToRead = 0;
      }
    }
  }

  /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
  while ((I2C_num->CR1&0x200) == 0x200);

  // * Enable Acknowledgement to be ready for another reception * /
  I2C_AcknowledgeConfig(I2C_num, ENABLE);

  return 1;

}

/*******************************************************************************
* Function Name  : I2C_ByteWrite
* Description    : write a Byte to I2C Bus
* Input          : deviceAddr is the I2C address of the device
*                  WriteAddr is the register address you want to write to
*                  pBuffer contains bytes to write
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_ByteWrite(uint8_t* pBuffer, uint8_t deviceAddress, uint8_t WriteAddr)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(I2C_num, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C_num, deviceAddress, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));


  /* Send the EEPROM's internal address to write to : only one byte Address */
  I2C_SendData(I2C_num, WriteAddr);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(I2C_num, *pBuffer);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_num, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STOP condition */
  I2C_GenerateSTOP(I2C_num, ENABLE);
}


/*******************************************************************************
* Function Name  : SPI_Mems_Read_Reg
* Description    : Reads Mems Register
* Input          : Register
* Output         : None
* Return         : Register Content
*******************************************************************************/
uint8_t SPI_Mems_Read_Reg(uint8_t MemsType, uint8_t reg) {
  uint8_t Temp;

  reg += 0x80; //reading procedure has to set the most significant bit
  // Select Mems Sensor: Chip Select low
  switch(MemsType)
      {
  	//case CS_A3G4250D: Pin_Rst(NSS2_PORT,NSS2_PIN);break;
  	case CS_L3G4200D: Pin_Rst(NSS1_PORT,NSS1_PIN);break;
  	default: break;
      }

  // Send Register Address
  SPI_Mems_SendByte(reg);
  /* Read a byte from the MEMS Sensor */
  Temp = SPI_Mems_SendByte(DUMMY_BYTE);

  /* Deselect Mems Sensor: Chip Select high */
  switch(MemsType)
     {
     //  case CS_A3G4250D: Pin_Set(NSS2_PORT,NSS2_PIN);break;
       case CS_L3G4200D: Pin_Set(NSS1_PORT,NSS1_PIN);break;
       default: break;
     }

  return Temp;
}


/*******************************************************************************
* Function Name  : SPI_Mems_Write_Reg
* Description    : Write Data in Mems Register
* Input          : Register, data
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Mems_Write_Reg(uint8_t MemsType,uint8_t regAddr, uint8_t data) {

  // Select Mems Sensor: Chip Select low
  switch(MemsType)
    {
	//case CS_A3G4250D: Pin_Rst(NSS2_PORT,NSS2_PIN);break;
	case CS_L3G4200D: Pin_Rst(NSS1_PORT,NSS1_PIN);break;
	default: break;
    }

  // Send Register Address
  SPI_Mems_SendByte(regAddr);
  /* Write a byte into the MEMS Sensor Register*/
  SPI_Mems_SendByte(data);

  /* Deselect Mems Sensor: Chip Select high */
  switch(MemsType)
   {
   //  case CS_A3G4250D: Pin_Set(NSS2_PORT,NSS2_PIN);break;
     case CS_L3G4200D: Pin_Set(NSS1_PORT,NSS1_PIN);break;
     default: break;
   }
}


/*******************************************************************************
* Function Name  : SPI_Read_MultiData
* Description    : Reads Mems Registers in auto increment mode
* Input          : Start Address, number of register to read, Buffer
* Output         : None
* Return         : Register Content
*******************************************************************************/
void SPI_Read_MultiData(uint8_t MemsType, uint8_t regAddr, uint8_t length, uint8_t* buffer) {
  uint8_t i = 0;

  regAddr += 0xc0; //reading procedure has to set the most significant bit

  // Select Mems Sensor: Chip Select low
    switch(MemsType)
    {
	//case CS_A3G4250D: Pin_Rst(NSS2_PORT,NSS2_PIN);break;
	case CS_L3G4200D: Pin_Rst(NSS1_PORT,NSS1_PIN);break;
	default: break;
    }

  // Send Register Address
  SPI_Mems_SendByte(regAddr);

  while(i < length){
    /* Read a byte from the MEMS Sensor */
    buffer[i] = SPI_Mems_SendByte(DUMMY_BYTE);
    i++;
  }

  /* Deselect Mems Sensor: Chip Select high */
  switch(MemsType)
  {
   // case CS_A3G4250D: Pin_Set(NSS2_PORT,NSS2_PIN);break;
    case CS_L3G4200D: Pin_Set(NSS1_PORT,NSS1_PIN);break;
    default: break;
  }

}

/*******************************************************************************
* Function Name  : SPI_Mems_SendByte
* Description    : Sends a byte through the SPI interface and return the byte
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
uint8_t SPI_Mems_SendByte(uint8_t byte) {

  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI2 peripheral */
  SPI_I2S_SendData(SPI2, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI2);
}
