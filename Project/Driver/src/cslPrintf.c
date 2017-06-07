#include "cslPrintf.h"


PUTCHAR_PROTOTYPE
{
  CslUSART_SendByte(CSLPRINTF_MAP_UART, (uint8_t) ch);
  return ch;
}

