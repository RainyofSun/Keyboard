#pragma once

#define FONT_MAINTAIN_DLG_TEXT 17,0,0,0,FW_BOLD,FALSE,FALSE,0,DEFAULT_CHARSET,OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,DRAFT_QUALITY,DEFAULT_PITCH,"等线"
#define IDC_RED_DLG		192
#define IDC_GREEN_DLG	192
#define IDC_BLUE_DLG	192
#define DLG_MAIN_TITLE_BK_COLOR                     RGB(96,96,128)

#define FONT_HIGHT	200
#define FONT_WIGHT	400

#define POS_DLG_X_L	8
#define POS_DLG_X_R	22
#define POS_DLG_Y	95

#define HULF_TITLE_POS 0, 0, 501, 20
#define FULL_TITLE_POS 1, 1, 1012, 20

#define BSPACE		0x06
#define TAB			0x02
#define CAPSLOCK	0x03
#define ENTER		0x07
#define LEFTNUM		0x0A
#define RIGHTNUM	0x0B
#define UPNUM		0x0C
#define DOWNNUM		0x0D
#define HOME		0x11
#define DEL			0x14
#define CLR			0x20//随便定的20
#define INC			0x21
#define DEC			0x22
#define OK			0x23
#define CANCEL		0x24
#define abc			0x25
#define ABC			0x26
#define NUM			0X27
#define SPACE		0x28
#define EMPTY		0x29
#define SHIFT		0x30

struct KeyInfo
{
	CString strTitle;
	CString strDefault;
	CString strCurrent;
	CString strNewValue;
	CString strMaximum;
	CString strMinimum;
	CString strUnit;
	CString strFormat;
	CString strType;
	CString strProcess;

	KeyInfo()
	{
		strTitle = "";
		strDefault = "";
		strCurrent = "";
		strNewValue = "";
		strMaximum = "";
		strMinimum = "";
		strUnit = "";
		strFormat = "";
		strType = "";
		strProcess = "";
	}
};

struct KeycapDefine
{
	// 字符串
	char cNormal;
	// shift按下时的值
	char cShifted;
	// 图标大小
	int cWidth;
	CRect rect;
	// 是否高亮
	bool bHighlight;
};