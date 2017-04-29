/*
 * binr_parse.h
 *
 *  Created on: 15 jan 2015 ã.
 *      Author: grifill
 */

#ifndef INC_BINR_PARSE_H_
#define INC_BINR_PARSE_H_

#include	<math.h>
#include 	"binr_parse.h"
#include 	<float.h>
#include	<time.h>
#include 	<string.h>
#include 	<stdint.h>


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





#endif /* INC_BINR_PARSE_H_ */
