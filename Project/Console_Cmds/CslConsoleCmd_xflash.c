#include "cslConsole.h"
#include "cslConsoleCmd_xflash.h"
#include "string.h"
#include "xmodem.h"
#include "FreeRTOS.h"
#include "FlashControl.h"

static uint32_t Str2Dec(char* pStr)
{
	uint32_t tmpResult;
	
	if(pStr[0] == '0' && ((pStr[1] == 'x') || (pStr[1] == 'X')))
	{
		//Hex format
		if(sscanf(pStr, "%x", &tmpResult) == -1)
		{
			return (uint32_t)-1;
		}
	}
	else
	{
		//Dec format
		if(sscanf(pStr, "%d", &tmpResult) == -1)
		{
			return (uint32_t)-1;
		}
	}
	
	return tmpResult;
}

static volatile uint32_t write_addr;
static void xflash_Write_cb(uint8_t* pBuffer, uint32_t Size)
{
	FlashControl_Write(pBuffer, write_addr, Size);
	write_addr += Size;
}

static int xflash_Write(char* AddrString)
{
	uint32_t Addr;
	
	Addr = Str2Dec(AddrString);
	if(Addr == (uint32_t)-1)
	{
		printf("Write param error\n");
		return -1;
	}
	
	write_addr = Addr;
	
	portENTER_CRITICAL();
	xmodemReceive('C', xflash_Write_cb);
	portEXIT_CRITICAL();
	
	printf("Write done\r\n");
	
	return 0;
}

static int xflash_Read(char* AddrString, char* SizeString)
{
	uint32_t Addr, Size;
	uint8_t tmpBuf[16];
	uint8_t i;
	
	Addr = Str2Dec(AddrString);
	if(Addr == (uint32_t)-1)
	{
		printf("Read param error\r\n");
		return -1;
	}
	Size = Str2Dec(SizeString);
	if(Size == (uint32_t)-1)
	{
		printf("Read param error\r\n");
		return -1;
	}
	
	while(Size >= 16)
	{
		FlashControl_Read(tmpBuf, Addr, 16);
		printf("\r\n %08X:", Addr);
		for(i=0;i<16;i++)
		{
			printf(" 0x%02X", tmpBuf[i]);
		}
		Addr += 16;
		Size -= 16;
	}
	if(Size)
	{
		FlashControl_Read(tmpBuf, Addr, Size);
		printf("\r\n %08X:", Addr);
		for(i=0;i<Size;i++)
		{
			printf(" 0x%02X", tmpBuf[i]);
		}
	}
	printf("\r\n");
	printf("Read done\r\n");
	
	return 0;	
}

static int xflash_Erase(char* AddrString, char* SizeString)
{
	uint32_t Addr, Size;
	
	Addr = Str2Dec(AddrString);
	if(Addr == (uint32_t)-1)
	{
		printf("Erase param error\r\n");
		return -1;
	}
	Size = Str2Dec(SizeString);
	if(Size == (uint32_t)-1)
	{
		printf("Erase param error\r\n");
		return -1;
	}
	FlashControl_Erase(Addr, Size);
	printf("Erase done\r\n");
	
	return 0;	
}

static int xflash_Info(void)
{
	uint32_t ID;
	
	ID = FlashControl_ReadID();
	printf("Flash ID: 0x%X\r\n", ID);
	
	return 0;
}

int CslConsole_Cmd_xflash(pCslConsole_Cmd_t st, int flag, int argc, char* argv[])
{	
	if(strcmp(argv[1], "write") == 0)
	{
		if(argc <= 2)
		{
			printf("Params missing\r\n");
			return 0;
		}
		xflash_Write(argv[2]);
	}
	else if(strcmp(argv[1], "read") == 0)
	{
		if(argc <= 3)
		{
			printf("Params missing\r\n");
			return 0;
		}
		xflash_Read(argv[2], argv[3]);
	}
	else if(strcmp(argv[1], "erase") == 0)
	{
		if(argc <= 3)
		{
			printf("Params missing\r\n");
			return 0;
		}
		xflash_Erase(argv[2], argv[3]);
	}
	else if(strcmp(argv[1], "info") == 0)
	{
		xflash_Info();
	}
	
	return 0;
}


const CslConsole_Cmd_t CONSOLECMD_XFLASH_CONFIG = {"xflash", 5, "Xflash Program Help ?", CslConsole_Cmd_xflash, NULL};
