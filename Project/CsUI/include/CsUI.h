#ifndef __CSUI_H__
#define __CSUI_H__

/*
** This is Cloud Standard User Interface Library.
** Author : Cloud
** Orgnaztion : Cloud Studio
** Version : V0.0.1
*/

#include "CsUI_Config.h"

#define CsUI_Version  0x00000100

typedef unsigned short TCsUI_PointBase;
typedef unsigned int TCsUI_TypeBase;
typedef unsigned short TCsUI_Color;           //565 support only

/* Point define */
typedef struct TCsUI_Point
{
	TCsUI_PointBase X;
	TCsUI_PointBase Y;
}TCsUI_Point;

/* Rect define */
typedef struct TCsUI_Rect
{
	TCsUI_PointBase Left;
	TCsUI_PointBase Top;
	TCsUI_PointBase Right;
	TCsUI_PointBase Bottom;
}TCsUI_Rect;

/* Font define */
typedef struct TCsUI_Font
{
	TCsUI_TypeBase XSize;
	TCsUI_TypeBase YSize;
	unsigned char* pFontMatrixData;
}TCsUI_Font;

/* Draw call back function define */
typedef TCsUI_TypeBase(*TCsUI_Draw)(void* Self);

/* Base UI object */
typedef struct TCsUI_BaseObject
{
	TCsUI_Rect Rect;
	TCsUI_Draw Draw;
}TCsUI_BaseObject;

typedef TCsUI_BaseObject* TCsUI_BaseObjectTable;

/* Frame */
typedef struct TCsUI_Frame
{
	TCsUI_BaseObject Obj;
	TCsUI_Color BackColor;
	struct TCsUI_Frame* Parent;
	TCsUI_BaseObjectTable* Childs;
	TCsUI_TypeBase ChildCount;
}TCsUI_Frame;

/* Lable */
typedef struct TCsUI_Lable
{
	TCsUI_BaseObject Obj;
	TCsUI_Font Font;
	TCsUI_Color FrontColor;
	TCsUI_Color BackColor;
	char *Text;
}TCsUI_Lable;



/* Functions */
extern TCsUI_TypeBase CsUI_Init(void);
extern TCsUI_TypeBase TCsUI_Frame_Draw(TCsUI_Frame* Self);
extern TCsUI_TypeBase TCsUI_Lable_Draw(TCsUI_Lable* Self);




#endif

