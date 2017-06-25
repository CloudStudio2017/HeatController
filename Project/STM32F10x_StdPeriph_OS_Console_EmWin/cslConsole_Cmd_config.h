#ifndef __CSL_CONSOLE_CMD_CONFIG_H__
#define __CSL_CONSOLE_CMD_CONFIG_H__

#include "CslConsole.h"
#include "CslConsoleCmd_echo.h"
#include "CslConsoleCmd_md.h"

pCslConsole_Cmd_t CslConsole_Cmds[] = 
{
	(pCslConsole_Cmd_t)&CONSOLECMD_ECHO_CONFIG,
	(pCslConsole_Cmd_t)&CONSOLECMD_MD_CONFIG,
};

#endif
