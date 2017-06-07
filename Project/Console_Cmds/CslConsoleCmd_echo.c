#include "cslConsole.h"
#include "cslConsoleCmd_echo.h"



int CslConsole_Cmd_echo(pCslConsole_Cmd_t st, int flag, int argc, char* argv[])
{
	uint8_t i;
	
	if(argc == 1)
	{
		printf("%s\r\n", st->help);
		return 0;
	}
	printf("Echo Test\r\n");
	printf("flag=%d,Argc=%d\r\n", flag, argc);
	
	for(i=0;i<argc;i++)
	{
		printf("Argv[%d]=%s\r\n", i, argv[i]);
	}
	return 0;
}


const CslConsole_Cmd_t CONSOLECMD_ECHO_CONFIG = {"echo", 5, "Echo Program Help ?", CslConsole_Cmd_echo, NULL};
