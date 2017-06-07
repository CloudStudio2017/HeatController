#ifndef __CSL_CONSOLE_H__
#define __CSL_CONSOLE_H__


#include "cslCommon.h"
#include "cslPrintf.h"
#include "cslScanf.h"


struct CslConsole_Cmd_s
{
	char* CmdName;
	char  MaxParameter;
	char* help;
	int (*Cmd)(struct CslConsole_Cmd_s *, int, int, char* []);
	int (*AutoComplete)(int argc, char* argv[],char last_char, int maxv, char *cmdv[]);
};

typedef void (*do_FunType)(int argc, char * Argv[]);
typedef struct CslConsole_Cmd_s CslConsole_Cmd_t;
typedef struct CslConsole_Cmd_s* pCslConsole_Cmd_t;

extern void CslConsole_Init(void);
extern void CslConsole_Process(void);


#endif
