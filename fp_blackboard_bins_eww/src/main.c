/*!
 * \file		main.c
 * \author		Ванин А.В.
 * \version
 * \date		16.09.2015
 * \details
 */
#include "SYS_init.h"
#include "usart_op.h"
#include 	"proto_parcer_cp9ba.h"

#include 	"plist.h"
#include 	"param.h"
#ifdef	ENABLE_DYNAMIC_ARRAY
extern TParam* 	plist;
#else
extern TParam 	plist[MAX_PLIST_CNT];
#endif
extern long		pcnt;
//	---------------------------------------------------------------------------
uint8_t	cp9baGetByte(uint8_t* ch)
{
	return pluGetByte(0,ch);
}
//	---------------------------------------------------------------------------
int16_t		cp9baWriteData(unsigned char *dst, int cnt)
{
	M_PIO_SET(GPIOC_BASE,GPIO_Pin_8);
	return pluWriteDataDMA(6,(const char *)dst,cnt+2);
}
//	---------------------------------------------------------------------------
uint16_t cp9baSetData(uint16_t data_id, uint8_t* data, int16_t data_cnt)
{
	if(data_id >= pcnt)
	{
		TRACE_ERROR("%d > %d\n",data_id,pcnt);
		return 0;
	}
	uint16_t cnt = data_cnt > plist[data_id].size ? plist[data_id].size : data_cnt;
	memcpy(plist[data_id].val,data,cnt);
	return cnt;
}
//	---------------------------------------------------------------------------
uint16_t cp9baGetData(uint16_t data_id, uint8_t* data, int16_t data_cnt)
{
	if(data_id >= pcnt)
	{
		TRACE_ERROR("%d > %d\n",data_id,pcnt);
		return 0;
	}
	uint16_t cnt = data_cnt > plist[data_id].size ? plist[data_id].size : data_cnt;
	memcpy(data,plist[data_id].val,cnt);
	return cnt;
}
//	---------------------------------------------------------------------------
void main(void)
{
	PList();
	init();
	while(1)
	{
    	cp9baProcess(pSID,cp9baGetByte,cp9baWriteData,cp9baSetData,cp9baGetData);
	}
}
