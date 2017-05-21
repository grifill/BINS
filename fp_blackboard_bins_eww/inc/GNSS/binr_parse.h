/*
 * binr_parse.h
 *
 *  Created on: 15 jan 2015 г.
 *      Author: grifill
 */

#ifndef INC_BINR_PARSE_H_
#define INC_BINR_PARSE_H_

#include	<math.h>
#include 	<float.h>
#include	<time.h>
#include 	<string.h>
#include 	<stdint.h>

#include "stm32f4xx_conf.h"
#include "usart_tools.h"
#include "func_tools.h"


#define GPS_WEEK_CYCLE 1
#define GPS_MINUS_UTC_SECS 16
#define GPS_EPOCH 315964800 // 1980 sec


typedef struct {
    uint32_t   second;
    uint32_t    fraction;
}ntp_time_t;

typedef struct
{
	double seconds_per_week;
	uint16_t week_number;
} gps_time_t;

enum
{
	ETX = 0x03,
	DLE = 0x10,
	ID =  0x72,
};// BINR package words ))

/* GPS time functions */
gps_time_t normalize_gps_time(gps_time_t);
time_t gps2time(gps_time_t t);
double gpsdifftime(gps_time_t end, gps_time_t beginning);


/* Interface Functions */
void FP80_to_unchar_lendian(double num, char* bytes);
double  uchar_to_FP80_lendian(unsigned char* bytes);


// PROTOCOL ===================================================================
struct NV08C_InitTypeDef                                                         
{
  
  
  
  char	    _buf_rx_[PROTO_BUF_SIZE];                                           // Поток приема
  uint16_t  _rx_cnt_;                                                           // Счетчик для потока приема
  char	    _buf_tx_[PROTO_BUF_SIZE];                                           // Поток передачи
  uint16_t  _tx_cnt_;                                                           // Счетчик для потока передачи
};


// Флаги для разборщика команд <BINR>
enum {
	BINR_parse_nrdy     = 0x00,                                             // Флаг "не готово" 
	BINR_parse_ok       = 0x01,                                             // Флаг "готов"
	BINR_parse_timeout  = 0x02,                                             // флаг "истек период ожидания"
        BINR_DLE            = 0x10,
        BINR_ETX            = 0x03,
};

// Флаги для разборщика команд <BINR>
enum {
	DATA_NEED          = 0x00,                                             
	DATA_READY         = 0x01,                                             
};

// Флаги для разборщика команд <BINR>
enum {
	DLE_NEED          = 0x00,                                             
	DLE_ONE           = 0x01,
        DLE_TWO           = 0x02,
};


// Флаги для разборщика команд-ID <BINR>
enum {
        ID_PORT           = 0x50,
  
};



void NV08C_Soft_Reset(struct NV08C_InitTypeDef* nv08c_parse);
uint16_t BINR_Parse(struct NV08C_InitTypeDef* nv08c_parse);


#endif /* INC_BINR_PARSE_H_ */
