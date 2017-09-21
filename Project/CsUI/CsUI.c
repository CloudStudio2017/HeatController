#include "CsUI.h"
#include "CsUI_Font.h"
#include "FlashControl.h"

#define CSUI_BUFFER_MAX 256
static unsigned short CsUI_Buffer[CSUI_BUFFER_MAX / 2];

TCsUI_TypeBase CsUI_Init(void)
{
	CsUI_LowDeviceInit();
	return 0;
}

/* 2D Graphic code */

void CsUI_DrawCircle(TCsUI_TypeBase x0, TCsUI_TypeBase y0, TCsUI_TypeBase r, TCsUI_Color Color)
{
	int x,y,xd,yd,e;

	if ( r<=0 ) return;

	xd = 1 - (r << 1);
	yd = 0;
	e = 0;
	x = r;
	y = 0;

	while ( x >= y )
	{
		CsUI_SetPixel(x0 - x, y0 + y, Color);
		CsUI_SetPixel(x0 - x, y0 - y, Color);
		CsUI_SetPixel(x0 + x, y0 + y, Color);
		CsUI_SetPixel(x0 + x, y0 - y, Color);
		CsUI_SetPixel(x0 - y, y0 + x, Color);
		CsUI_SetPixel(x0 - y, y0 - x, Color);
		CsUI_SetPixel(x0 + y, y0 + x, Color);
		CsUI_SetPixel(x0 + y, y0 - x, Color);

		y++;
		e += yd;
		yd += 2;
		if ( ((e << 1) + xd) > 0 )
		{
			x--;
			e += xd;
			xd += 2;
		}
	}
}

void CsUI_FillCircle(TCsUI_TypeBase x0, TCsUI_TypeBase y0, TCsUI_TypeBase r, TCsUI_Color Color)
{
   int  x,y,xd;

   if ( r<=0 ) return;

   xd = 3 - (r << 1);
   x = 0;
   y = r;

   while ( x <= y )
   {
     if( y > 0 )
     {
        CsUI_DrawLine(x0 - x, y0 - y,x0 - x, y0 + y, Color);
        CsUI_DrawLine(x0 + x, y0 - y,x0 + x, y0 + y, Color);
     }
     if( x > 0 )
     {
        CsUI_DrawLine(x0 - y, y0 - x,x0 - y, y0 + x, Color);
        CsUI_DrawLine(x0 + y, y0 - x,x0 + y, y0 + x, Color);
     }
     if ( xd < 0 )
     {
        xd += (x << 2) + 6;
     }
     else
     {
        xd += ((x - y) << 2) + 10;
        y--;
     }
     x++;
   }
   CsUI_DrawCircle(x0, y0, r,Color);
}

void CsUI_DrawArc(TCsUI_TypeBase x0, TCsUI_TypeBase y0, TCsUI_TypeBase r, TCsUI_TypeBase s, TCsUI_Color Color)
{
	int x,y,xd,yd,e;
	
	if ( r<=0 ) return;

   xd = 1 - (r << 1);
   yd = 0;
   e = 0;
   x = r;
   y = 0;

	while ( x >= y )
	{
		// Q1
		if ( s & 0x01 ) CsUI_SetPixel(x0 + x, y0 - y, Color);
		if ( s & 0x02 ) CsUI_SetPixel(x0 + y, y0 - x, Color);
		// Q2
		if ( s & 0x04 ) CsUI_SetPixel(x0 - y, y0 - x, Color);
		if ( s & 0x08 ) CsUI_SetPixel(x0 - x, y0 - y, Color);
		// Q3
		if ( s & 0x10 ) CsUI_SetPixel(x0 - x, y0 + y, Color);
		if ( s & 0x20 ) CsUI_SetPixel(x0 - y, y0 + x, Color);
		// Q4
		if ( s & 0x40 ) CsUI_SetPixel(x0 + y, y0 + x, Color);
		if ( s & 0x80 ) CsUI_SetPixel(x0 + x, y0 + y, Color);
		y++;
		e += yd;
		yd += 2;
		if ( ((e << 1) + xd) > 0 )
		{
			x--;
			e += xd;
			xd += 2;
		}
	}
}

void CsUI_DrawLine(TCsUI_TypeBase x1, TCsUI_TypeBase y1, TCsUI_TypeBase x2, TCsUI_TypeBase y2, TCsUI_Color Color)
{
	int n, dx, dy, sgndx, sgndy, dxabs, dyabs, x, y, drawx, drawy;

	/* Is hardware acceleration available? */
	#if 1
	if(x1 == x2)
	{
		if(y1 < y2)
		{
			CsUI_BlockBegin(x1, y1, x1, y2);
			for(n=0;n<=y2-y1;n++)
				CsUI_BlockWriteData(Color);
		}
		else
		{
			CsUI_BlockBegin(x1, y1, x1, y2);
			for(n=0;n<=y1-y2;n++)
				CsUI_BlockWriteData(Color);
		}
		CsUI_BlockEnd();
	}
	else if(y1 == y2)
	{
		if(x1 < x2)
		{
			CsUI_BlockBegin(x1, y1, x1, y2);
			for(n=0;n<=x2-x1;n++)
				CsUI_BlockWriteData(Color);
		}
		else
		{
			CsUI_BlockBegin(x1, y1, x1, y2);
			for(n=0;n<=x1-x2;n++)
				CsUI_BlockWriteData(Color);
		}
		CsUI_BlockEnd();
	}
	#endif
	
	dx = x2 - x1;
	dy = y2 - y1;
	dxabs = (dx>0)?dx:-dx;
	dyabs = (dy>0)?dy:-dy;
	sgndx = (dx>0)?1:-1;
	sgndy = (dy>0)?1:-1;
	x = dyabs >> 1;
	y = dxabs >> 1;
	drawx = x1;
	drawy = y1;

	CsUI_SetPixel(drawx, drawy, Color);
	if( dxabs >= dyabs )
	{
		for( n=0; n<dxabs; n++ )
		{
			y += dyabs;
			if( y >= dxabs )
			{
				y -= dxabs;
				drawy += sgndy;
			}
			drawx += sgndx;
			CsUI_SetPixel(drawx, drawy, Color);
		}
	}
	else
	{
		for( n=0; n<dyabs; n++ )
		{
			x += dxabs;
			if( x >= dyabs )
			{
				x -= dyabs;
				drawx += sgndx;
			}
			drawy += sgndy;
			CsUI_SetPixel(drawx, drawy, Color);
		}
	}
}

//TCsUI_TypeBase CsUI_GetAbsRect(TCsUI_BaseObject* Obj)

TCsUI_TypeBase TCsUI_Frame_Draw(TCsUI_Frame* Self)
{
	TCsUI_BaseObjectTable pChild;
	TCsUI_Frame* pParent;
	TCsUI_Rect AbsRect;
	TCsUI_TypeBase Width;
	TCsUI_TypeBase Height;
	TCsUI_TypeBase i;
		
	AbsRect.Left = Self->Obj.Rect.Left;
	AbsRect.Top = Self->Obj.Rect.Top;
	Width = Self->Obj.Rect.Right - AbsRect.Left;
	Height = Self->Obj.Rect.Bottom - AbsRect.Top;
	
	pParent = Self->Parent;
	while(pParent != NULL)
	{
		AbsRect.Left += pParent->Obj.Rect.Left;
		AbsRect.Top += pParent->Obj.Rect.Top;
		pParent = pParent->Parent;
	}
	AbsRect.Right = AbsRect.Left + Width;
	AbsRect.Bottom = AbsRect.Top + Height;
	
	CsUI_FillRect(AbsRect.Left,
	              AbsRect.Top,
	              AbsRect.Right,
	              AbsRect.Bottom,
                Self->BackColor);
	if(Self->Childs != NULL)
	{
		for(i=0;i<Self->ChildCount;i++)
		{
			if(Self->Childs[i]->Draw)
			{
				Self->Childs[i]->Draw(Self->Childs[i]);
			}
		}
	}
	return 0;
}

void CsUI_DrawBitmap_Bits(TCsUI_TypeBase Left, TCsUI_TypeBase Top, TCsUI_TypeBase Width, TCsUI_TypeBase Height,
	                        const unsigned char* pDataBits, TCsUI_BitDrawMode Mode,
										      TCsUI_Color FrontColor, TCsUI_Color BackColor)
{
	unsigned int x,y,i;
	
	CsUI_BlockBegin(Left, Top, Left + Width -1, Top + Height -1);
	
	if(Mode.xDir)
	{
		for(y=0;y<Height;y++)
		{
			x=Width;
			while(x>8)
			{
				for(i=0;i<8;i++)
				{
					if(*pDataBits & (1<<(7-i)))
						CsUI_BlockWriteData(BackColor);
					else
						CsUI_BlockWriteData(FrontColor);
				}
				pDataBits++;
				x-=8;
			}
			for(i=0;i<x;i++)
			{
				if(*pDataBits & (1<<(7-i)))
					CsUI_BlockWriteData(BackColor);
				else
					CsUI_BlockWriteData(FrontColor);
			}
			pDataBits++;
		}
	}
	else
	{
		for(y=0;y<Height;y++)
		{
			x=Width;
			while(x>8)
			{
				for(i=0;i<8;i++)
				{
					if(*pDataBits & (1<<(i)))
						CsUI_BlockWriteData(BackColor);
					else
						CsUI_BlockWriteData(FrontColor);
				}
				pDataBits++;
				x-=8;
			}
			for(i=0;i<x;i++)
			{
				if(*pDataBits & (1<<(i)))
					CsUI_BlockWriteData(BackColor);
				else
					CsUI_BlockWriteData(FrontColor);
			}
			pDataBits++;
		}
	}
	CsUI_BlockEnd();
}

TCsUI_TypeBase TCsUI_Lable_Draw(TCsUI_Lable* Self)
{
	TCsUI_TypeBase XSize, YSize;
	TCsUI_Frame* pParent;
	TCsUI_Rect AbsRect;
	TCsUI_TypeBase Width;
	TCsUI_TypeBase Height;
	TCsUI_Color Color1,Color2;
	const char* pChar;
	unsigned int OffsetBase;
	unsigned int CharOffset = 0;
	unsigned char* pData;
	unsigned int i;
	TCsUI_BitDrawMode tmpMode;
	
	AbsRect.Left = Self->Obj.Rect.Left;
	AbsRect.Top = Self->Obj.Rect.Top;
	Width = Self->Obj.Rect.Right - AbsRect.Left;
	Height = Self->Obj.Rect.Bottom - AbsRect.Top;
	
	pParent = Self->Parent;
	while(pParent != NULL)
	{
		AbsRect.Left += pParent->Obj.Rect.Left;
		AbsRect.Top += pParent->Obj.Rect.Top;
		pParent = pParent->Parent;
	}
	AbsRect.Right = AbsRect.Left + Width;
	AbsRect.Bottom = AbsRect.Top + Height;
	
	XSize = Self->Font.XSize;
	YSize = Self->Font.YSize;
	OffsetBase = ((XSize-1) / 8 + 1) * YSize;
	
	Color1 = Self->FrontColor;
	Color2 = Self->BackColor;
	
	/* Draw Background */
	CsUI_FillRect(AbsRect.Left,
	              AbsRect.Top,
	              AbsRect.Right,
	              AbsRect.Bottom,
                Self->BackColor);
	
	pChar = Self->Text;
	while(*pChar)
	{
		pData = Self->Font.pFontMatrixData;
		pData += ((*pChar - ' ') * OffsetBase);
		
		tmpMode.xDir = 0;
		tmpMode.yDir = 0;
		CsUI_DrawBitmap_Bits(AbsRect.Left + CharOffset, AbsRect.Top, XSize, YSize, pData, tmpMode, Color2, Color1);
		pChar++;
		CharOffset += XSize;
	}
	
	return 0;
}

TCsUI_TypeBase TCsUI_Bitmap_Draw(TCsUI_Bitmap* Self)
{
	TCsUI_Frame* pParent;
	TCsUI_Rect AbsRect;
	TCsUI_TypeBase Width;
	TCsUI_TypeBase Height;
	int bmpWidth;
	int bmpHeight;
	int i;
	unsigned char* pBitData;
	TCsUI_BitDrawMode tmpMode;
	
	AbsRect.Left = Self->Obj.Rect.Left;
	AbsRect.Top = Self->Obj.Rect.Top;
	Width = Self->Obj.Rect.Right - AbsRect.Left;
	Height = Self->Obj.Rect.Bottom - AbsRect.Top;
	
	pParent = Self->Parent;
	while(pParent != NULL)
	{
		AbsRect.Left += pParent->Obj.Rect.Left;
		AbsRect.Top += pParent->Obj.Rect.Top;
		pParent = pParent->Parent;
	}
	AbsRect.Right = AbsRect.Left + Width;
	AbsRect.Bottom = AbsRect.Top + Height;
	
	bmpWidth = Self->pBmp->biWidth;
	bmpHeight = Self->pBmp->biHeight;
	if(bmpHeight < 0)	bmpHeight = -bmpHeight;
	AbsRect.Right = AbsRect.Left + bmpWidth;
	AbsRect.Bottom = AbsRect.Top + bmpHeight;
	
	/* Draw Background */
	//CsUI_FillRect(AbsRect.Left,
	//              AbsRect.Top,
	//              AbsRect.Right,
	//              AbsRect.Bottom,
  //              Self->BackColor);
	/* Get bitmap data*/
	pBitData = (unsigned char*)((unsigned int)(Self->pBmp) + (unsigned int)(Self->pBmp->bfOffBits));
	switch(Self->pBmp->biBitCount)
	{
		case 1:
			tmpMode.xDir = 1;
		  tmpMode.yDir = 0;
			CsUI_DrawBitmap_Bits(AbsRect.Left, AbsRect.Top, AbsRect.Right - AbsRect.Left, AbsRect.Bottom - AbsRect.Top, pBitData, tmpMode, Self->FrontColor, Self->BackColor);
			break;
		case 4:
		case 8:
		case 16:
			CsUI_BlockBegin(AbsRect.Left, AbsRect.Top, AbsRect.Right -1, AbsRect.Bottom -1);
			for(i=0;i<bmpWidth * bmpHeight;i++)
			{
				CsUI_BlockWriteData(*(unsigned short*)pBitData);
				pBitData+=2;
			}
			CsUI_BlockEnd();
			break;
		case 24:
		case 32:
			break;
	}
	
	return 0;
}

TCsUI_TypeBase TCsUI_Bitmap_Draw_Ext(TCsUI_Bitmap* Self)
{
	TCsUI_Frame* pParent;
	TCsUI_Rect AbsRect;
	TCsUI_TypeBase Width;
	TCsUI_TypeBase Height;
	int bmpWidth;
	int bmpHeight;
	int i,j;
	unsigned int pAddr;
	TCsUI_BitDrawMode tmpMode;
	
	AbsRect.Left = Self->Obj.Rect.Left;
	AbsRect.Top = Self->Obj.Rect.Top;
	Width = Self->Obj.Rect.Right - AbsRect.Left;
	Height = Self->Obj.Rect.Bottom - AbsRect.Top;
	
	pParent = Self->Parent;
	while(pParent != NULL)
	{
		AbsRect.Left += pParent->Obj.Rect.Left;
		AbsRect.Top += pParent->Obj.Rect.Top;
		pParent = pParent->Parent;
	}
	AbsRect.Right = AbsRect.Left + Width;
	AbsRect.Bottom = AbsRect.Top + Height;
	
	TBitmap_Head tmpHead;
	
	FlashControl_Read((uint8_t*)&tmpHead, 0x0, sizeof(tmpHead));
	
	bmpWidth = tmpHead.biWidth;
	bmpHeight = tmpHead.biHeight;
	if(bmpHeight < 0)	bmpHeight = -bmpHeight;
	AbsRect.Right = AbsRect.Left + bmpWidth;
	AbsRect.Bottom = AbsRect.Top + bmpHeight;
	
	/* Draw Background */
	//CsUI_FillRect(AbsRect.Left,
	//              AbsRect.Top,
	//              AbsRect.Right,
	//              AbsRect.Bottom,
  //              Self->BackColor);
	/* Get bitmap data*/
	pAddr = tmpHead.bfOffBits + 0x0;
	switch(Self->pBmp->biBitCount)
	{
		case 1:
			//tmpMode.xDir = 1;
		  //tmpMode.yDir = 0;
			//CsUI_DrawBitmap_Bits(AbsRect.Left, AbsRect.Top, AbsRect.Right - AbsRect.Left, AbsRect.Bottom - AbsRect.Top, pBitData, tmpMode, Self->FrontColor, Self->BackColor);
			break;
		case 4:
		case 8:
		case 16:
			CsUI_BlockBegin(AbsRect.Left, AbsRect.Top, AbsRect.Right -1, AbsRect.Bottom -1);
			i = bmpWidth * bmpHeight * 2;
			while(i > 0)
			{
				if(i > CSUI_BUFFER_MAX)
				{
					FlashControl_Read((uint8_t*)CsUI_Buffer, bmpWidth * bmpHeight * 2 - i + pAddr, CSUI_BUFFER_MAX);
					for(j=0;j<CSUI_BUFFER_MAX/2;j++)
						CsUI_BlockWriteData(CsUI_Buffer[j]);
					i -= CSUI_BUFFER_MAX;
				}
				else
				{
					FlashControl_Read((uint8_t*)CsUI_Buffer, bmpWidth * bmpHeight * 2 - i + pAddr, i);
					for(j=0;j<i/2;j++)
						CsUI_BlockWriteData(CsUI_Buffer[j]);
					i = 0;
				}
			}
			CsUI_BlockEnd();
			break;
		case 24:
		case 32:
			break;
	}
	
	return 0;
}





