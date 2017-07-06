#include "UI_Sources.h"
#include "FlashControl.h"

static U8 _acBuffer[480*4];
const U32 SRC_BMP_Map[] = 
{
	0x00000000,   //Cloud bmp
	0x00010000,   //----
};


int GetUISourceData(void * p, const U8 ** ppData, unsigned NumBytes, U32 Off)
{
	U32 DataAddr;
	
	if(NumBytes > sizeof(_acBuffer))
	{
		NumBytes = sizeof(_acBuffer);
	}
	
	DataAddr = SRC_BMP_Map[*(U32*)p];               //Get bmp data from map list
	
	FlashControl_Read(_acBuffer, DataAddr + Off, NumBytes);
	
	*ppData = _acBuffer;
	
	return NumBytes;
}



