#ifndef __CSL_PRINTF_H__
#define __CSL_PRINTF_H__

#define CSLPRINTF_MAP_UART   CSLUSART1

#if defined CSLPRINTF_MAP_UART

#include <stdio.h>
#include "stm32f10x.h"
#include "CslUSART.h"

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif


#endif


#endif
