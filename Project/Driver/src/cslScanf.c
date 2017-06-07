#include "cslScanf.h"



FGETC_PROTOTYPE
{
	static char t_sc[4];
	static char t_sct = 0;
	
	uint8_t tmpChar;
  tmpChar = CslUSART_ReciveByte(CSLSCANF_MAP_UART);
	//printf("[%d]", tmpChar);
	switch(t_sct)
	{
		case 0:
			switch(tmpChar)
			{
				case 0x03: //Ctrl+C
					break;
				case '\b':
					break;
				case '\r':
					CslUSART_SendByte(CSLPRINTF_MAP_UART, '\r');
					CslUSART_SendByte(CSLPRINTF_MAP_UART, '\n');
					break;
				case '\t':
					break;
				case 0x1B:
					t_sc[0] = 0x1B;
					t_sct = 1;
					break;
				default:
					CslUSART_SendByte(CSLPRINTF_MAP_UART, tmpChar);
					break;
			}
			break;
		case 1:
			switch(tmpChar)
			{
				case 0x5B: //Up Down Right Left
					t_sc[1] = 0x5B;
					t_sct = 2;
					break;
				case 0x4F: //F1-F4
					t_sc[1] = 0x4F;
					t_sct = 2;
					break;
			}
			break;
		case 2:
			switch(tmpChar)
			{
				case 'A': //Up
				case 'B': //Down
				case 'C': //Right
				case 'D': //Left
					t_sct = 0;
					break;
				case 'P': //F1
				case 'Q': //F2
				case 'R': //F3
				case 'S': //F4
					t_sct = 0;
					break;
			}
			break;
	}

	return tmpChar;
}
