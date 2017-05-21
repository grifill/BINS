/*
 * binr_parse.c
 *
 *  Created on: 15 янв. 2015 г.
 *      Author: grifill
 */

#include "binr_parse.h"

#ifndef HUGE_VAL
# define HUGE_VAL HUGE
#endif /*HUGE_VAL*/

# define FloatToUnsigned(f)      ((unsigned long)(((long)(f - 2147483648.0)) + 2147483647L) + 1)
# define UnsignedToFloat(u_p)    (((double)((long)(u_p - 2147483647L - 1))) + 2147483648.0)
/***************************************************************************************************
 * Convert FP80 to unsigned char (IEEE-754) in little endian
 *
 * # define FloatToUnsigned(f)      ((unsigned long)(((long)(f - 2147483648.0)) + 2147483647L) + 1)
 * is need
 ****************************************************************************************************/
void FP80_to_unchar_lendian(double num, char* bytes)
{
    int    sign;
    int expon;
    double fMant, fsMant;
    unsigned long hiMant, loMant;

    if (num < 0) {
        sign = 0x8000;
        num *= -1;
    } else {
        sign = 0;
    }

    if (num == 0) {
        expon = 0; hiMant = 0; loMant = 0;
    }
    else {
        fMant = frexp(num, &expon);
        if ((expon > 16384) || !(fMant < 1)) {    /* Infinity or NaN */
            expon = sign|0x7FFF; hiMant = 0; loMant = 0; /* infinity */
        }
        else {    /* Finite */
            expon += 16382;
            if (expon < 0) {    /* denormalized */
                fMant = ldexp(fMant, expon);
                expon = 0;
            }
            expon |= sign;
            fMant = ldexp(fMant, 32);
            fsMant = floor(fMant);
            hiMant = FloatToUnsigned(fsMant);
            fMant = ldexp(fMant - fsMant, 32);
            fsMant = floor(fMant);
            loMant = FloatToUnsigned(fsMant);
        }
    }

    bytes[0] = expon >> 8;
    bytes[1] = expon;
    bytes[2] = hiMant >> 24;
    bytes[3] = hiMant >> 16;
    bytes[4] = hiMant >> 8;
    bytes[5] = hiMant;
    bytes[6] = loMant >> 24;
    bytes[7] = loMant >> 16;
    bytes[8] = loMant >> 8;
    bytes[9] = loMant;
}


/****************************************************************************************************
 * Convert unsigned char to FP80 (IEEE-754) in little endian
 * Output: double
 *
 * # define UnsignedToFloat(u_p)         (((double)((long)(u_p - 2147483647L - 1))) + 2147483648.0)
 * is need
 ****************************************************************************************************/
double  uchar_to_FP80_lendian(unsigned char* bytes)
{
    double    f;
    int    expon;
    unsigned long hiMant, loMant;

    expon = ((bytes[9] & 0x7F) << 8) | (bytes[8] & 0xFF);
    hiMant    =    ((unsigned long)(bytes[7] & 0xFF) << 24)
            |    ((unsigned long)(bytes[6] & 0xFF) << 16)
            |    ((unsigned long)(bytes[5] & 0xFF) << 8)
            |    ((unsigned long)(bytes[4] & 0xFF));
    loMant    =    ((unsigned long)(bytes[3] & 0xFF) << 24)
            |    ((unsigned long)(bytes[2] & 0xFF) << 16)
            |    ((unsigned long)(bytes[1] & 0xFF) << 8)
            |    ((unsigned long)(bytes[0] & 0xFF));

    if (expon == 0 && hiMant == 0 && loMant == 0) {
        f = 0;
    }
    else {
        if (expon == 0x7FFF) {    // Infinity or NaN
            //f = HUGE_VAL;
        	f=0;
        }
        else {
            expon -= 16383;
            f  = ldexp(UnsignedToFloat(hiMant), expon-=31);
            f += ldexp(UnsignedToFloat(loMant), expon-=32);
        }
    }

    if (bytes[0] & 0x80)
        return -f;
    else
        return f;
}
/* Either normalise in place or rename to normalised. */
 gps_time_t normalize_gps_time(gps_time_t t)
 {
  while(t.seconds_per_week < 0) {
  t.seconds_per_week += 3600*24*7;
  t.week_number += 1;
  }

  while(t.seconds_per_week > 3600*24*7) {
  t.seconds_per_week -= 3600*24*7;
  t.week_number -= 1;
  }

  return t;
 }

 time_t gps2time(gps_time_t gps_t)
 {
  //time_t t = GPS_EPOCH - GPS_MINUS_UTC_SECS;
  time_t t = GPS_EPOCH;
  t += 7*24*3600*gps_t.week_number;
  t += (int32_t)gps_t.seconds_per_week;

  return t;
 }

 double gpsdifftime(gps_time_t end, gps_time_t beginning)
 {
  return (end.week_number - beginning.week_number)*7*24*3600 + \
		  end.seconds_per_week - beginning.seconds_per_week;
 }

//========================== PROTOCOL ==========================================
struct NV08C_InitTypeDef nv08c; 
extern struct tUSARTcontext usart_pool;
extern uint8_t ch;
uint8_t data_state_t = 0;
uint8_t dle_t = 0;
uint8_t ID_t = 0;


/**
\brief Функция сброс настроек для модуля NV08C 
\param nv08c_res      указатель на структуру с параметрами модуля
*/
__weak void NV08C_Soft_Reset(struct NV08C_InitTypeDef* nv08c_parse)
{
  memset(nv08c_parse->_buf_rx_,0,PROTO_BUF_SIZE);
  memset(nv08c_parse->_buf_tx_,0,PROTO_BUF_SIZE);
  nv08c_parse->_tx_cnt_ = 0;
  nv08c_parse->_rx_cnt_ = 0;

  // Модуль
  Add_USART(&usart_pool);
  
  // Начальное состояние флагов
  data_state_t = 0;
  dle_t = 0;
  ID_t = 0;
}
/**
\brief Функция осуществляет разбор BINR команд от модуля NV08C-GSM.
Выставляет флаг <BINR_parse_ok> когда команда принята и разобрана 
и возвращает флаг <BINR_parse_nrdy> когда команда еще не разобрана
*/
__weak uint16_t BINR_Parse(struct NV08C_InitTypeDef* nv08c_parse)
{
  if (GetByte_t(&ch) == 0)
	return BINR_parse_nrdy;
  if ((ch==BINR_DLE)&&(data_state_t==DATA_NEED)&&(dle_t==DLE_NEED))
  {
    dle_t = DLE_ONE;
    return BINR_parse_nrdy;
  }
  if ((data_state_t==DATA_NEED)&&(dle_t==DLE_ONE))
  {
    ID_t = ch;
    dle_t = DLE_TWO;
    memset(nv08c_parse->_buf_rx_,0,PROTO_BUF_SIZE);
    memset(nv08c_parse->_buf_tx_,0,PROTO_BUF_SIZE);
    nv08c_parse->_tx_cnt_ = 0;
    nv08c_parse->_rx_cnt_ = 0;
    return BINR_parse_nrdy;
  }
  if ((data_state_t==DATA_NEED)&&(dle_t==DLE_TWO)) // Нет контроля, что ID - получен
  {
    switch(ID_t)
    {
    //---------------------------------------------------------
    case ID_PORT: // "Параметры порта"
      nv08c_parse->_buf_rx_[nv08c_parse->_rx_cnt_]=(char)ch;
      nv08c_parse->_rx_cnt_++;
      if (nv08c_parse->_rx_cnt_ >= 6) // 6-байт
      {
        nv08c_parse->_buf_rx_[(nv08c_parse->_rx_cnt_)+1]=0;
        // Далее обработка и в структуру --------------->>>
        PRINT("%s\n",nv08c_parse->_buf_rx_);
        //-----------------------------------------------//
        data_state_t=DATA_READY;
        dle_t=DLE_NEED;
        return BINR_parse_ok;
      }
      return BINR_parse_nrdy;
    //---------------------------------------------------------
    default:
      return BINR_parse_nrdy;
    }
  }
  return BINR_parse_nrdy;
}












