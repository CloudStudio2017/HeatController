#include "CsUI.h"
#include "CsUI_Font.h"



TCsUI_TypeBase CsUI_Init(void)
{
	CsUI_LowDeviceInit();
	return 0;
}

void CsUI_DrawLine(TCsUI_TypeBase x1, TCsUI_TypeBase y1, TCsUI_TypeBase x2, TCsUI_TypeBase y2, TCsUI_Color Color)
{
	int x,y,dx,dy,e;
	int ydir,xdir;
	unsigned int i;
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	if((dx < 0 && dy < 0) || (dy < -dx))
	{
		x = x1;
		x1 = x2;
		x2 = x;
		y = y1;
		y1 = y2;
		y2 = y;
		dx = -dx;
		dy = -dy;
	}
	if(dx == 0)
	{
		for(i=y1;i<=y2;i++)
			CsUI_SetPixel(x1, i, Color);
		return;
	}
	else if(dy == 0)
	{
		for(i=x1;i<=x2;i++)
			CsUI_SetPixel(i, y1, Color);
		return;
	}
	
	e = -dx;
	x = x1;
	y = y1;
	
	if(dy > 0)
		ydir = 1;
	else if(dy < 0)
		ydir = -1;
	if(dx > 0)
		xdir = 1;
	else if(dx < 0)
		xdir = -1;
	
	if(dx >= (ydir * dy))
	{
		for(i=0;i<dx;i++)
		{
			CsUI_SetPixel(x, y, Color);
			x++;
			e = e + 2 * (dy * ydir);
			if(e>=0)
			{
				y += ydir;
				e = e - 2 * dx;
			}
		}
	}
	else
	{
		for(i=0;i<dy;i++)
		{
			CsUI_SetPixel(x, y, Color);
			y++;
			e = e + 2 * (dx * xdir);
			if(e>=0)
			{
				x += xdir;
				e = e - 2 * dy;
			}
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

TCsUI_TypeBase TCsUI_Lable_Draw(TCsUI_Lable* Self)
{
	TCsUI_TypeBase x,y;
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
		CsUI_BlockBegin(AbsRect.Left + CharOffset,
		                AbsRect.Top,
		                AbsRect.Left + CharOffset + XSize - 1,
		                AbsRect.Top + YSize - 1);
		for(y=0;y<YSize;y++)
		{
			x=XSize;
			while(x>8)
			{
				for(i=0;i<8;i++)
				{
					if(*pData & (1<<i))
						CsUI_BlockWriteData(Color1);
					else
						CsUI_BlockWriteData(Color2);
				}
				pData++;
				x-=8;
			}
			for(i=0;i<x;i++)
			{
				if(*pData & (1<<i))
					CsUI_BlockWriteData(Color1);
				else
					CsUI_BlockWriteData(Color2);
			}
			pData++;
		}
		CsUI_BlockEnd();
		pChar++;
		CharOffset += XSize;
	}
	
	return 0;
}





