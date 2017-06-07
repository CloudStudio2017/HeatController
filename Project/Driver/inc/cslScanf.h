#ifndef __CSL_SCANF_H__
#define __CSL_SCANF_H__

#define CSLSCANF_MAP_UART   CSLUSART1

#if defined CSLSCANF_MAP_UART

#include <stdio.h>
#include "stm32f10x.h"
#include "CslUSART.h"
#include "CslPrintf.h"

#ifdef __GNUC__
  #define FGETC_PROTOTYPE int __io_fgetc(int ch)
#else
  #define FGETC_PROTOTYPE int fgetc(FILE *f)
#endif



#endif


#endif
