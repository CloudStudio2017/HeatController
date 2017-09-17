#include "CsUI.h"
#include "CsUI_Font.h"


TCsUI_TypeBase CsUI_Init(void)
{
	CsUI_LowDeviceInit();
	return 0;
}


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
	AbsRect.Bottom = AbsRect.Bottom + Height;
	
	CsUI_FillRect(Self->Obj.Rect.Left,
	              Self->Obj.Rect.Top,
	              Self->Obj.Rect.Right,
	              Self->Obj.Rect.Bottom,
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
	char Char;
	unsigned char* pData;
	unsigned int i,j;
	
	Char = 'A' - '0';
	pData = CsUI_FontData_ASCII_1218;
	pData += (Char * 36);
	
	CsUI_BlockBegin(0,0,12,18);
	for(i=0;i<18*12/8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(*pData & (1<<j))
			{
				CsUI_BlockWriteData(0xFFF0);
			}
			else
			{
				CsUI_BlockWriteData(0x0000);
			}
		}
		pData++;
	}
	CsUI_BlockEnd();
	return 0;
}





