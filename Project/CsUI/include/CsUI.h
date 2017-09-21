#ifndef __CSUI_H__
#define __CSUI_H__

/*
** This is Cloud Standard User Interface Library.
** Author : Cloud
** Orgnaztion : Cloud Studio
** Version : V0.0.1
**
** 2D Graphic code is from uGUI (C)Achim Doble, 2015
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
typedef struct
{
	TCsUI_TypeBase XSize;
	TCsUI_TypeBase YSize;
	unsigned char* pFontMatrixData;
}TCsUI_Font;

/* Bit draw mode define */
typedef struct TCsUI_BitDrawMode
{
	unsigned char xDir : 1;   //0:Left to right 1:Right to left
	unsigned char yDir : 1;   //0:Top to bottom 1:Bottom to Top
}TCsUI_BitDrawMode;


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
	struct TCsUI_Frame* Parent;
	TCsUI_BaseObjectTable* Childs;
	TCsUI_TypeBase ChildCount;
	TCsUI_Color BackColor;
}TCsUI_Frame;

/* Lable */
typedef struct
{
	TCsUI_BaseObject Obj;
	struct TCsUI_Frame* Parent;
	TCsUI_Font Font;
	TCsUI_Color FrontColor;
	TCsUI_Color BackColor;
	char *Text;
}TCsUI_Lable;

/* Bitmap struct type */
__packed typedef struct TBitmap_Head
{
	unsigned short bfType;            //00   //'B' 'M'
	unsigned int   bfSize;            //02   //File size in byte
	unsigned short bfReserved1;       //06   //0
	unsigned short bfReserved2;       //08   //0
	unsigned int   bfOffBits;         //0A   //Bitmap data offset from head
	unsigned int   biSize;            //0E   //Size of struct 'BitmapInfoHead'
	unsigned int   biWidth;           //12   //Witdh of Bitmap
	unsigned int   biHeight;          //16   //Height of Bitmap
	unsigned short biPlanes;          //1A   //1
	unsigned short biBitCount;        //1C   //Bits per pixcel  1/4/8/16/24/32
	unsigned int   biCompression;     //1E   //Compression type 0:RGB 1:RLE8 2:RLE4 3:Bitfields 4:JPEG 5:PNG
	unsigned int   biSizeImage;       //22   //Size of Picture  0 in RGB mode
	unsigned int   biXPelsPerMeter;   //26   //XSize
	unsigned int   biYPelsPerMeter;   //2A   //YSize
	unsigned int   biClrUsed;         //2E
	unsigned int   biClrImportant;    //32
}TBitmap_Head;

/* Picture */
typedef struct TCsUI_Bitmap
{
	TCsUI_BaseObject Obj;
	struct TCsUI_Frame* Parent;
	TCsUI_Color FrontColor;
	TCsUI_Color BackColor;
	TBitmap_Head* pBmp;
}TCsUI_Bitmap;


/* Functions */
extern void CsUI_DrawCircle(TCsUI_TypeBase x0, TCsUI_TypeBase y0, TCsUI_TypeBase r, TCsUI_Color Color);
extern void CsUI_FillCircle(TCsUI_TypeBase x0, TCsUI_TypeBase y0, TCsUI_TypeBase r, TCsUI_Color Color);
extern void CsUI_DrawArc(TCsUI_TypeBase x0, TCsUI_TypeBase y0, TCsUI_TypeBase r, TCsUI_TypeBase s, TCsUI_Color Color);
extern void CsUI_DrawLine(TCsUI_TypeBase x1, TCsUI_TypeBase y1, TCsUI_TypeBase x2, TCsUI_TypeBase y2, TCsUI_Color Color);

extern TCsUI_TypeBase CsUI_Init(void);
extern TCsUI_TypeBase TCsUI_Frame_Draw(TCsUI_Frame* Self);
extern TCsUI_TypeBase TCsUI_Lable_Draw(TCsUI_Lable* Self);
extern TCsUI_TypeBase TCsUI_Bitmap_Draw(TCsUI_Bitmap* Self);
extern TCsUI_TypeBase TCsUI_Bitmap_Draw_Ext(TCsUI_Bitmap* Self);







/* Object define macros */
#define CS_FRAME(ObjName, xParent, L, R, T, B, xBackColor, xChilds) \
  TCsUI_Frame ObjName ={     \
		.BackColor = xBackColor, \
		.Parent = xParent,       \
		.Childs = xChilds,       \
		.ChildCount = sizeof(xChilds) / sizeof(TCsUI_BaseObjectTable), \
		.Obj.Rect.Left = L,     \
		.Obj.Rect.Right = R,    \
		.Obj.Rect.Top = T,      \
		.Obj.Rect.Bottom = B,   \
		.Obj.Draw = (TCsUI_Draw)TCsUI_Frame_Draw \
	}

#define CS_LABLE(ObjName, xParent, L, R, T, B, xFrontColor, xBackColor, xText, xFont) \
	TCsUI_Lable ObjName ={       \
		.FrontColor = xFrontColor, \
		.BackColor = xBackColor,   \
		.Parent = xParent,         \
		.Text = xText,             \
		.Font = xFont,             \
		.Obj.Rect.Left = L,        \
		.Obj.Rect.Right = R,       \
		.Obj.Rect.Top = T,         \
		.Obj.Rect.Bottom = B,      \
		.Obj.Draw = (TCsUI_Draw)TCsUI_Lable_Draw \
	}

#define CS_BITMAP(ObjName, xParent, L, R, T, B, xFrontColor, xBackColor, xpBmp) \
	TCsUI_Bitmap ObjName ={        \
		.FrontColor = xFrontColor,   \
		.BackColor = xBackColor,     \
		.pBmp = (TBitmap_Head*)xpBmp, \
		.Obj.Rect.Left = L,          \
		.Obj.Rect.Right = R,         \
		.Obj.Rect.Top = T,           \
		.Obj.Rect.Bottom = B,        \
		.Obj.Draw = (TCsUI_Draw)TCsUI_Bitmap_Draw \
	}


#endif

