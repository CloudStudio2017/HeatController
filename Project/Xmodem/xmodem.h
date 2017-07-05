#ifndef __XMODEM_H__
#define __XMODEM_H__

#include "stm32f10x.h"

#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define CTRLZ 0x1A

#define CHECK_CRC		0x01
#define CHECK_SUM		0x02

#define SUCCESSFULL     0X00
#define TIME_OUT        0X01
#define USER_CANCELED   0X02
#define PARAMETER_ERROR 0X03

#define DLY_1S 1000
#define MAXRETRANS 25

#define	NO_DATA		0
#define	HAVE_DATA	1

typedef struct
{
  uint8_t HaveLastData;     //上帧数据未读取完标志
  uint8_t LastDataNum;      //上帧未读取完毕的数据量，以字节为单位包括所有的数据
  uint8_t LastDataTemp[45]; //存储上帧未读取完的数据
}LAST_DATA_INFO;

typedef struct
{
	uint8_t	*p_LastData;
	uint8_t	DataTemp[1024];
}HEX_DATA_TEMP;

typedef void (*xmodemWrite_cbType)(uint8_t* pBuffer, uint32_t Size);

extern uint8_t xmodemReceive(uint8_t checkType, xmodemWrite_cbType WriteCB);
extern uint32_t port_inbyte(uint32_t Time);


#endif
