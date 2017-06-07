#include "cslConsole.h"
#include "cslConsole_Cmd_config.h"
#include "string.h"

#define CSL_CONSOLE_CHAR_MAX_COUNT 10

char CslConsole_tmpChar[CSL_CONSOLE_CHAR_MAX_COUNT][100];
char *CslConsole_pChar[CSL_CONSOLE_CHAR_MAX_COUNT];

uint8_t CslConsole_InputCountX = 0;
uint8_t CslConsole_InputCountY = 0;

pCslConsole_Cmd_t CslConsole_FindCmd(char *CmdStr)
{
	uint32_t i;
	uint32_t MaxCmdCount;
	
	MaxCmdCount = sizeof(CslConsole_Cmds)/sizeof(pCslConsole_Cmd_t);
	
	for(i=0; i< MaxCmdCount; i++)
	{
		if(0 == strcmp(CslConsole_Cmds[i]->CmdName, CmdStr))
		{
			return CslConsole_Cmds[i];
		}
	}
	return NULL;
}

void CslConsole_Init(void)
{
	uint8_t i;
	
	CslUSART_RegType CslUSART_Struct;
	CslUSART_Struct.USART_BaudRate = 115200;
	CslUSART_Struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	CslUSART_Struct.USART_Parity = USART_Parity_No;
	CslUSART_Struct.USART_RxHandler = NULL;
	CslUSART_Struct.USART_TxHandler = NULL;
	CslUSART_Reg(CSLUSART1, &CslUSART_Struct);
	
	for(i=0;i<CSL_CONSOLE_CHAR_MAX_COUNT;i++)
		CslConsole_pChar[i] = CslConsole_tmpChar[i];
	printf("\r\n");
}

void CslConsole_Process(void)
{
	char tempChar;
	pCslConsole_Cmd_t pCmd;
	
	printf(">>");
	while(1)
	{
		tempChar = getchar();
		switch(tempChar)
		{
			case '\b':
				if(CslConsole_InputCountX > 0)
				{
					putchar('\b');
					putchar(' ');
					putchar('\b');
					CslConsole_InputCountX--;
				}
				break;
			case '\t':
				if(0 == CslConsole_InputCountX)
				{
					break;
				}
			case ' ':
				if(CslConsole_InputCountX)
				{
					CslConsole_pChar[CslConsole_InputCountY][CslConsole_InputCountX] = 0;
					CslConsole_InputCountX = 0;
					CslConsole_InputCountY++;
				}
				break;
			case '\r':
				if((0 == CslConsole_InputCountY) && (0 == CslConsole_InputCountX))
				{
					
				}
				else
				{
					CslConsole_pChar[CslConsole_InputCountY][CslConsole_InputCountX] = 0;
					CslConsole_InputCountY++;
					pCmd = CslConsole_FindCmd(CslConsole_pChar[0]);
					if(pCmd != NULL)
					{
						pCmd->Cmd(pCmd, pCmd->MaxParameter, CslConsole_InputCountY, CslConsole_pChar);
					}
					else
					{
						printf("command: '%s' not found, please check again.\r\n", CslConsole_pChar[0]);
					}
					CslConsole_InputCountX = 0;
					CslConsole_InputCountY = 0;
				}
				putchar('>');
				putchar('>');
				break;
			default:
				CslConsole_pChar[CslConsole_InputCountY][CslConsole_InputCountX] = tempChar;
				CslConsole_InputCountX++;
				break;
		}
	}
}

