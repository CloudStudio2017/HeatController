#include "cslConsole.h"
#include "cslConsoleCmd_md.h"
#include "string.h"

int CslConsole_Cmd_md(pCslConsole_Cmd_t st, int flag, int argc, char* argv[])
{
	unsigned int i,j;
	unsigned int Memory_Addr;
	
	if(argc == 1)
	{
		printf("%s\r\n", st->help);
		return 0;
	}
	if((argv[1][0] == '0') && ((argv[1][1] == 'x') || (argv[1][1] == 'X')) )
	{
		sscanf(argv[1]+2, "%X", &Memory_Addr);
		printf("dump memory from 0x%08X -- 0x%08X\r\n", Memory_Addr, Memory_Addr + 0x100 -1);
		
		for(i=0;i<16;i++)
		{
			printf("0x%08X ", Memory_Addr);
			for(j=0;j<4;j++)
			{
				printf(" 0x%08X", *(volatile unsigned int *)Memory_Addr);
				Memory_Addr += 4;
			}
			printf("\r\n");
		}
		
		return 0;
	}
	
	
	return 0;
}

const CslConsole_Cmd_t CONSOLECMD_MD_CONFIG = {"md", 6, "Example md 0x40000", CslConsole_Cmd_md, NULL};
