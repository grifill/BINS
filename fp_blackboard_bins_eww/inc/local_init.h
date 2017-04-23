/*!
 * \file		init.h
 * \author		Ванин А.В.
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

/*!	\defgroup 	init	Инициализация
 * 	\breif	Группа комманд, используемых для инициализации периферии контроллера, протоколов,
 * 	параметров и данных. Начальная установка параметров осуществляется при перезагрузке
 * 	контроллера. Все настройки в текущей весрии не сохраняются.
 */
/*!
 * \ingroup init
 * \breif	Инициализация групп ножек контроллера.
 *
 * \param	_base	Базовый адрес порта
 * \param	_pins	Настраиваемые ножки
 * \param	_mode	Режим работы ножек
 * \param	_speed	Частота тактирования ножек
 * \param	_oType	Тип выходного каскада
 * \param	_PuPd	Подтяжка
 * \param	_afunc	Альтернативная функция ножки (-1 - если не требуется)
 *
 * Производится настройка параметров указанных ножек.
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
 * \breif	Инициализация прерываний ножек контроллера.
 *
 * \param	_EXTI_PortSourceGPIOx	Порт - источник прерывания
 * \param	_EXTI_PinSource			Контакт - источник прерывания
 * \param	_trigger				Тип триггера прерывания
 * \param	_prio					Приоритет прерываний (&0х07)
 * \param	_type					Тип прерываний
 *
 * Производится настройка параметров прерываний указанных ножек.
 */
void	GPIO_IT_config(	uint8_t  			_EXTI_PortSourceGPIOx,
						uint32_t 			_EXTI_PinSource,
						EXTITrigger_TypeDef _trigger,
						uint16_t 			_prio,
						IRQn_Type 			_type);
/*!
 * \ingroup init
 * \breif	Инициализация UART
 *
 * \param	_base	Базовый адрес порта
 * \param	_baud	Скорость передачи данных
 * \param	_mode	Режим работы приемо-передатчика
 * \param	_flags	Флаги запуска прерываний (0 - если не используется)
 *
 * Производится настройка параметров указанного порта UART.
 */
void	UART_config(uint32_t _base, uint32_t _baud,uint16_t _mode, uint16_t _flags);
/*!
 * \ingroup init
 * \breif	Инициализация SPI
 *
 * \param	_base	Базовый адрес порта
 * \param	_baud	Скорость передачи данных (см. @ref SPI_BaudRate_Prescaler)
 * \param	_flags	Флаги запуска прерываний (0 - если не используется)
 * \param	_data_size Размер данных 8/16 бит
 *
 * Производится настройка параметров указанного порта UART.
 */
void SPI_config(uint32_t _base, uint32_t _baud, uint16_t _data_size, uint16_t _flags);
/*!
 * \ingroup init
 * \breif	Инициализация таймеров
 *
 * \param	_base	Базовый адрес порта
 * \param	_cnt	Счетчик таймера
 * \param	_presc	Предделитель частоты
 * \param	irq_type	Тип прерываний
 * \param	_flags	Флаги запуска прерываний (0 - если не используется)
 * \param	_prio	Приоритет прерываний (&0х07)
 * \param	_state	Состояние инициализации
 *
 * Производится настройка параметров указанного порта UART.
 */
void	TIM_config(	uint32_t _base,
					uint32_t _cnt,
					uint16_t _presc,
					IRQn_Type irq_type,
					uint16_t _flags,
					uint16_t _prio,
					uint8_t	 _state);

#endif /* INIT_H_ */
