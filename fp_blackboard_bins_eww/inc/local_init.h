/*!
 * \file		init.h
 * \author		����� �.�.
 * \version
 * \date		25.07.2012
 * \details		
 */


#ifndef INIT_H_
#define INIT_H_

#include <stm32f4xx.h>
#include <stm32f4xx_conf.h>
//#include <debug_trace.h>

#define NVIC_GROUPING	NVIC_PriorityGroup_4

/*!	\defgroup 	init	�������������
 * 	\breif	������ �������, ������������ ��� ������������� ��������� �����������, ����������,
 * 	���������� � ������. ��������� ��������� ���������� �������������� ��� ������������
 * 	�����������. ��� ��������� � ������� ������ �� �����������.
 */
/*!
 * \ingroup init
 * \breif	������������� ����� ����� �����������.
 *
 * \param	_base	������� ����� �����
 * \param	_pins	������������� �����
 * \param	_mode	����� ������ �����
 * \param	_speed	������� ������������ �����
 * \param	_oType	��� ��������� �������
 * \param	_PuPd	��������
 * \param	_afunc	�������������� ������� ����� (-1 - ���� �� ���������)
 *
 * ������������ ��������� ���������� ��������� �����.
 */
void	GPIO_config(	uint32_t _base,
						uint32_t _pins,
						GPIOMode_TypeDef _mode,
						GPIOSpeed_TypeDef _speed,
						GPIOOType_TypeDef _oType,
						GPIOPuPd_TypeDef _PuPd,
						int8_t	 _afunc
						);
/*!
 * \ingroup init
 * \breif	������������� ���������� ����� �����������.
 *
 * \param	_EXTI_PortSourceGPIOx	���� - �������� ����������
 * \param	_EXTI_PinSource			������� - �������� ����������
 * \param	_trigger				��� �������� ����������
 * \param	_prio					��������� ���������� (&0�07)
 * \param	_type					��� ����������
 *
 * ������������ ��������� ���������� ���������� ��������� �����.
 */
void	GPIO_IT_config(	uint8_t  			_EXTI_PortSourceGPIOx,
						uint32_t 			_EXTI_PinSource,
						EXTITrigger_TypeDef _trigger,
						uint16_t 			_prio,
						IRQn_Type 			_type);
/*!
 * \ingroup init
 * \breif	������������� UART
 *
 * \param	_base	������� ����� �����
 * \param	_baud	�������� �������� ������
 * \param	_mode	����� ������ ������-�����������
 * \param	_flags	����� ������� ���������� (0 - ���� �� ������������)
 *
 * ������������ ��������� ���������� ���������� ����� UART.
 */
void	UART_config(uint32_t _base, uint32_t _baud,uint16_t _mode, uint16_t _flags);
/*!
 * \ingroup init
 * \breif	������������� SPI
 *
 * \param	_base	������� ����� �����
 * \param	_baud	�������� �������� ������ (��. @ref SPI_BaudRate_Prescaler)
 * \param	_flags	����� ������� ���������� (0 - ���� �� ������������)
 * \param	_data_size ������ ������ 8/16 ���
 *
 * ������������ ��������� ���������� ���������� ����� UART.
 */
void SPI_config(uint32_t _base, uint32_t _baud, uint16_t _data_size, uint16_t _flags);
/*!
 * \ingroup init
 * \breif	������������� ��������
 *
 * \param	_base	������� ����� �����
 * \param	_cnt	������� �������
 * \param	_presc	������������ �������
 * \param	irq_type	��� ����������
 * \param	_flags	����� ������� ���������� (0 - ���� �� ������������)
 * \param	_prio	��������� ���������� (&0�07)
 * \param	_state	��������� �������������
 *
 * ������������ ��������� ���������� ���������� ����� UART.
 */
void	TIM_config(	uint32_t _base,
					uint32_t _cnt,
					uint16_t _presc,
					IRQn_Type irq_type,
					uint16_t _flags,
					uint16_t _prio,
					uint8_t	 _state);

#endif /* INIT_H_ */
