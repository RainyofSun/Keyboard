// StringKeyboard.cpp : 实现文件
//

#include "stdafx.h"
#include "Keyboard.h"
#include "StringKeyboard.h"
#include "afxdialogex.h"


// CStringKeyboard 对话框

IMPLEMENT_DYNAMIC(CStringKeyboard, CDialogEx)

CStringKeyboard::CStringKeyboard(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStringKeyboard::IDD, pParent)
{
	ntype = 1;
}

CStringKeyboard::~CStringKeyboard()
{
}

void CStringKeyboard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEWVALUE_EDIT, m_ctlNewValueEdit);
	DDX_Text(pDX, IDC_NEWVALUE_EDIT, m_tempString);
}


BEGIN_MESSAGE_MAP(CStringKeyboard, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEACTIVATE()
ON_WM_ACTIVATE()
ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CStringKeyboard 消息处理程序


HBRUSH CStringKeyboard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (CTLCOLOR_STATIC == nCtlColor && pWnd->IsWindowEnabled() && !(::GetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE)&ES_READONLY))
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	
	if (IDC_NUMBER_TITLE_STATIC == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
		return hbr;
	}

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_Brush;
	}
	return hbr;
}


void CStringKeyboard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(IDC_RED_DLG, IDC_GREEN_DLG, IDC_BLUE_DLG));

	CPaintDC dc1(GetDlgItem(IDC_NUMBER_TITLE_STATIC));
	CRect rectClient;
	CDC dcMen, dcBkground;
	CBitmap bitmapTemp, *oldBitmap;

	GetDlgItem(IDC_NUMBER_TITLE_STATIC)->GetClientRect(&rectClient);
	bitmapTemp.CreateCompatibleBitmap(&dc1, rectClient.Width(), rectClient.Height());
	dcMen.CreateCompatibleDC(&dc1);
	oldBitmap = dcMen.SelectObject(&bitmapTemp);

	// 绘制渐变色
	int r1=0,g1=25,b1=52;
	int r2=204,g2=229,b2=235;
	for (int i=0;i<rectClient.Width();i++)
	{
		int r,g,b;
		r=r1+(i*(r2-r1))/rectClient.Width();
		g=g1+(i*(g2-g1))/rectClient.Width();
		b=b1+(i*(b2-b1))/rectClient.Width();
		dcMen.FillSolidRect(i,0,1,rectClient.Height(),RGB(r,g,b));
	}

	dc1.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &dcMen, 0, 0, SRCCOPY);
	dcMen.SelectObject(oldBitmap);
	bitmapTemp.DeleteObject();

	DrawKeyboard(strStatic, ntype, m_strClient);
	DrawKeyboard(funcStatic, 2, m_funcClient);
}


BOOL CStringKeyboard::DestroyWindow()
{
	if (m_dlgFont.m_hObject != NULL)
	{
		m_dlgFont.DeleteObject();
	}

	if (m_textFont.m_hObject != NULL)
	{
		m_textFont.DeleteObject();
	}

	DeleteObject(m_brush);

	if (m_Brush != NULL)
	{
		DeleteObject(m_Brush);
	}

	FreeBkBrushColor();

	return CDialogEx::DestroyWindow();
}


BOOL CStringKeyboard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_dlgFont.m_hObject == NULL)
	{
		m_dlgFont.CreateFontA(FONT_MAINTAIN_DLG_TEXT);
	}

	SendMessageToDescendants(WM_SETFONT, (WPARAM)HFONT(m_dlgFont), MAKELPARAM(false, 0), false);
	GetDlgItem(IDC_NUMBER_TITLE_STATIC)->SetWindowPos(NULL, HULF_TITLE_POS, SWP_NOZORDER);
	GetDlgItem(IDC_NUMBER_TITLE_STATIC)->SetWindowText(m_stringkeyInfo.strTitle);
	GetDlgItem(IDC_DEFAULT_EDIT)->SetWindowText(m_stringkeyInfo.strTitle);
	GetDlgItem(IDC_CURRENT_EDIT)->SetWindowText(m_stringkeyInfo.strTitle);

	m_brush.CreateSolidBrush(RGB(220, 220, 220));
	m_Brush = CreateSolidBrush(RGB(IDC_RED_DLG, IDC_GREEN_DLG, IDC_BLUE_DLG));
	SetWindowText(m_stringkeyInfo.strTitle);

	InitTextFont();
	FillBKBrushColor();

	strStatic = GetDlgItem(IDC_NUM_STATIC);
	funcStatic = GetDlgItem(IDC_FUNCTION_STATIC);

	AddKey(0x00,0x00,0,0);	
	AddKey('(',0,10,0);
	AddKey('1',0,10,0);
	AddKey('2',0,10,0);
	AddKey('3',0,10,0);
	AddKey('/',0,10,0);
	//AddKey(0x00,CLR,11,0);

	AddKey(0x00,0x00,1,0);	
	AddKey(')',0,10,0);
	AddKey('4',0,10,0);
	AddKey('5',0,10,0);
	AddKey('6',0,10,0);
	AddKey('*',0,10,0);
	//AddKey(0x00,BSPACE,11,0);

	AddKey(0x00,0x00,2,0);
	AddKey('[',0,10,0);
	AddKey('7',0,10,0);
	AddKey('8',0,10,0);
	AddKey('9',0,10,0);
	AddKey('-',0,10,0);
	//AddKey(0x00,INC,11,0);

	AddKey(0x00,0x00,3,0);
	AddKey(']',0,10,0);
	AddKey('0',0,10,0);
	AddKey('.',0,10,0);
	AddKey ('=',0,10,0);
	AddKey('+',0,10,0);
	//AddKey(0x00,DEC,11,0);
	AddKey(0x00,0x00,4,0);
	AddKey('<',0,10,0);
	AddKey(',',0,10,0);
	AddKey('#',0,10,0);
	AddKey ('_',0,10,0);
	AddKey(0x00,SPACE,10,0);

	AddKey(0x00,0x00,5,0);
	AddKey('>',0,10,0);
	AddKey(0x00,CLR,10,0);
	AddKey(0x00,BSPACE,10,0);
	AddKey(0x00,ABC,10,0);
	AddKey(0x00,abc,10,0);


	AddKey(0x00,0x00,0,1);	
	AddKey('A',0,10,1);
	AddKey('B',0,10,1);
	AddKey('C',0,10,1);
	AddKey('D',0,10,1);
	AddKey('E',0,10,1);


	AddKey(0x00,0x00,1,1);	
	AddKey('F',0,10,1);
	AddKey('G',0,10,1);
	AddKey('H',0,10,1);
	AddKey('I',0,10,1);
	AddKey('J',0,10,1);

	AddKey(0x00,0x00,2,1);	
	AddKey('K',0,10,1);
	AddKey('L',0,10,1);
	AddKey('M',0,10,1);
	AddKey('N',0,10,1);
	AddKey('O',0,10,1);

	AddKey(0x00,0x00,3,1);
	AddKey('P',0,10,1);
	AddKey('Q',0,10,1);
	AddKey('R',0,10,1);
	AddKey('S',0,10,1);
	AddKey('T',0,10,1);

	AddKey(0x00,0x00,4,1);
	AddKey('U',0,10,1);
	AddKey('V',0,10,1);
	AddKey('W',0,10,1);
	AddKey('X',0,10,1);
	AddKey('Y',0,10,1);

	AddKey(0x00,0x00,5,1);
	AddKey('Z',0,10,1);
	AddKey(0x00,CLR,10,1);
	AddKey(0x00,BSPACE,10,1);
	AddKey(0x00,abc,10,1);
	AddKey(0x00,NUM,10,1);

	AddKey(0x00,0x00,0,3);	
	AddKey('a',0,10,3);
	AddKey('b',0,10,3);
	AddKey('c',0,10,3);
	AddKey('d',0,10,3);
	AddKey('e',0,10,3);

	AddKey(0x00,0x00,1,3);	
	AddKey('f',0,10,3);
	AddKey('g',0,10,3);
	AddKey('h',0,10,3);
	AddKey('i',0,10,3);
	AddKey('j',0,10,3);

	AddKey(0x00,0x00,2,3);	
	AddKey('k',0,10,3);
	AddKey('l',0,10,3);
	AddKey('m',0,10,3);
	AddKey('n',0,10,3);
	AddKey('o',0,10,3);

	AddKey(0x00,0x00,3,3);
	AddKey('p',0,10,3);
	AddKey('q',0,10,3);
	AddKey('r',0,10,3);
	AddKey('s',0,10,3);
	AddKey('t',0,10,3);

	AddKey(0x00,0x00,4,3);
	AddKey('u',0,10,3);
	AddKey('v',0,10,3);
	AddKey('w',0,10,3);
	AddKey('x',0,10,3);
	AddKey('y',0,10,3);

	AddKey(0x00,0x00,5,3);
	AddKey('z',0,10,3);
	AddKey(0x00,CLR,10,3);
	AddKey(0x00,BSPACE,10,3);
	AddKey(0x00,ABC,10,3);
	AddKey(0x00,NUM,10,3);

	::GetWindowRect(strStatic->m_hWnd, m_strClient);
	ScreenToClient(m_strClient);
	
	CalcWidthAndHeight(strStatic, 1);
	CalcKeycapRect(m_strClient, 1);

	AddKey(0x00,0x00,1,2);//功能键
	AddKey(0x00,OK,3,2);
	AddKey(0x00,CANCEL,3,2);

	::GetWindowRect(funcStatic->m_hWnd, m_funcClient);
	ScreenToClient(m_funcClient);
	
	CalcWidthAndHeight(funcStatic, 2);
	CalcKeycapRect(m_funcClient, 2);

	int x=0,y=0;
	CRect rcDlgs;
	GetWindowRect(rcDlgs);  //得到对话框的Rect 对话框的大小
	int cx = GetSystemMetrics(SM_CXSCREEN)/2;   //屏幕大小用于判断是否超出屏幕
	int cy = GetSystemMetrics(SM_CYSCREEN);
	CPoint point_g;
	GetCursorPos(&point_g);
	if (point_g.x > cx )
	{
		x = POS_DLG_X_L;
	} 
	else
	{
		x = rcDlgs.Width()+POS_DLG_X_R;
	}

	y=POS_DLG_Y;
	SetWindowPos(&wndTopMost,x,y,rcDlgs.Width(),rcDlgs.Height(),SWP_SHOWWINDOW | SWP_NOACTIVATE);//wndTopMost//设置位置大小
	GetDlgItem(IDC_NEWVALUE_EDIT)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CStringKeyboard::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

void CStringKeyboard::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);

	KeycapDefine *key;
	POSITION pos;

	CRect funcRect, strRect;
	int tempType = ntype;
	funcStatic->GetWindowRect(&funcRect);
	ScreenToClient(funcRect);
	strStatic->GetWindowRect(&strRect);
	ScreenToClient(strRect);

	if (funcRect.PtInRect(point))
	{
		tempType = 2;
	}
	else if (strRect.PtInRect(point))
	{
		tempType = ntype;
	}
	else 
	{
		return;
	}

	switch (tempType)
	{
	case 0:
		pos = m_numKeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_ABCKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_funcKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_abcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	m_currentState = DescribeKeycapState();
	int state = m_currentState;

	while (pos)
	{
		switch (tempType)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_ABCKeysList.GetNext(pos);
			break;
		case 2:
			key = m_funcKeysList.GetNext(pos);
			break;
		case 3:
			key = m_abcKeysList.GetNext(pos);
			break;
		default: 
			break;
		}

		if (key->rect.PtInRect(point))
		{
			if (key->bHighlight == false)
			{
				key->bHighlight = true;
				DrawKeycap(&dc, key);
			}
		}
		else if (key->bHighlight)
		{
			if (key->cNormal == 0x00)
			{
				switch (key->cShifted)
				{
				case CAPSLOCK:
					if (!(state & 0x01))
					{
						key->bHighlight = false;
						DrawKeycap(&dc, key);
					}
					break;
				default:
					key->bHighlight = false;
					DrawKeycap(&dc, key);
					break;
				}
			}
			else
			{
				key->bHighlight = false;
				DrawKeycap(&dc, key);
			}
		}
	}
}


void CStringKeyboard::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDown(nFlags, point);
}


void CStringKeyboard::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetDlgItem(IDC_NEWVALUE_EDIT)->SetFocus();
}


void CStringKeyboard::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);

	KeycapDefine *key;
	POSITION pos;
	CRect funcRect, strRect;

	int tempType = ntype;
	funcStatic->GetWindowRect(&funcRect);
	ScreenToClient(funcRect);
	strStatic->GetWindowRect(&strRect);
	ScreenToClient(strRect);

	if (funcRect.PtInRect(point))
	{
		tempType = 2;
	}
	else if (strRect.PtInRect(point))
	{
		tempType = ntype;
	}
	else
	{
		return;
	}

	switch (tempType)
	{
	case 0:
		pos = m_numKeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_ABCKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_funcKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_abcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	while (pos)
	{
		switch (tempType)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_ABCKeysList.GetNext(pos);
			break;
		case 2:
			key = m_funcKeysList.GetNext(pos);
			break;
		case 3:
			key = m_abcKeysList.GetNext(pos);
			break;
		default:
			break;
		}

		if (key->rect.PtInRect(point))
		{
			SendKey(key);
			key->bHighlight = false;
			DrawKeycap(&dc, key);
			return;
		}
	}
}


int CStringKeyboard::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return MA_NOACTIVATE;
}


void CStringKeyboard::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if (nState == WA_CLICKACTIVE && pWndOther != nullptr)
	{
		::SetActiveWindow(pWndOther->GetSafeHwnd());
		return;
	}
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}


BOOL CStringKeyboard::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

void CStringKeyboard::InitTextFont()
{
	LOGFONT temp;
	memset(&temp, 0, sizeof(LOGFONT));
	temp.lfHeight = FONT_HIGHT;
	temp.lfWeight = FONT_WIGHT;
	temp.lfCharSet = SHIFTJIS_CHARSET;
	temp.lfQuality = 1;
	temp.lfPitchAndFamily = 1;
	strcpy((char *)temp.lfFaceName, "Arial");
	VERIFY(m_textFont.CreatePointFontIndirect(&temp));
}

void CStringKeyboard::FillBKBrushColor()
{
	for (int i = 0; i < 64; i ++)
	{
		m_btBkColor[i].CreateSolidBrush(RGB(190, 192, 194));
	}
}

void CStringKeyboard::DrawKeycap(CDC *dc, KeycapDefine *key)
{
	CString label = "";
	BOOL special = FALSE;
	CRect rc = key->rect;

	if (key->cNormal == 0x00 && key->cShifted == 0x00)
	{
		return;
	}

	COLORREF oldColor = dc->GetTextColor();
	CPen pen, textPen, *oldPen = nullptr;

	if (!key->bHighlight)
	{
		rc.DeflateRect(1, 1);
		DrawGradientFill(dc, &rc);
		dc->Draw3dRect(rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DSHADOW));
		rc.DeflateRect(1, 1);
		dc->Draw3dRect(rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
	}
	else
	{
		rc.DeflateRect(1, 1);
		dc->FillSolidRect(rc, RGB(187, 225, 225));
		dc->Draw3dRect(rc, RGB(0, 0, 0), RGB(0,0,0));
		rc.DeflateRect(1, 1);
		dc->Draw3dRect(rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));
	}

	rc.DeflateRect(3, 1);

	CFont *oldFont = dc->SelectObject(&m_textFont);
	dc->SetTextColor(GetSysColor(COLOR_BTNTEXT));
	textPen.CreatePen(PS_SOLID, 2, GetSysColor(COLOR_BTNTEXT));
	oldPen = dc->SelectObject(&textPen);
	
	if (key->cNormal == 0x00)
	{
		if (key->cShifted < 0x6F)
		{
			switch(key->cShifted )
			{
			case CAPSLOCK:
				label="Cap";//考虑贴合6340改为Shift,功能是大写
				break;
			case ENTER:
				label="Enter";
				break;
			case DEL:
				label="Del";
				break;
			case CLR:	//0x20
				label="Clr";
				break;
			case BSPACE:    // 0x06
				label = "BK";
				break;
			case INC:    // 0x21
				label = "INC";
				break;
			case DEC:    // 0x22
				label = "DEC";
				break;
			case OK:    // 0x23
				label = "OK";
				break;
			case CANCEL:    // 0x24
				label = "CANCEL";
				break;
			case abc:    // 0x23
				label = "abc";
				break;
			case ABC:    // 0x23
				label = "ABC";
				break;
			case NUM:    // 0x24
				label = "123";
				break;
			default:
				break;
			}
		}

		if (!special)
		{
			CSize size;
			size = dc->GetTextExtent(label);
			dc->TextOut((rc.left + rc.right)/2 - size.cx/2, (rc.top + rc.bottom)/2 - size.cy/2, label);
		}
	}
	else
	{
		if ((key->cShifted >= 'A' && key->cShifted < 'Z') || (key->cShifted >= 'a' && key->cShifted <= 'z'))
		{
			CSize size;
			label.Format("%c", key->cShifted);
			size = dc->GetTextExtent(label);
			dc->TextOut((rc.left + rc.right)/2 - size.cx/2, (rc.top + rc.bottom)/2 - size.cy/2, label);
		}
		else
		{
			CSize size;
			if (key->cNormal == '-')
			{
				size = dc->GetTextExtent("M");
				int cx = (rc.left + rc.right)/2;
				int cy = (rc.top + rc.bottom)/2;
				int s_size = (rc.Width()/8);
				dc->MoveTo(cx - s_size, cy + s_size);
				dc->LineTo(cx + s_size, cy + s_size);
			}
			else
			{
				size = dc->GetTextExtent (_T("M"));
				label.Format (_T("%c"),key->cNormal );
				dc->TextOut (((rc.left +rc.right )/2)-(size.cx/2), ((rc.top + rc.bottom)/2 - (size.cy)/2), label);
			}
		}
	}

	dc->SetTextColor(oldColor);
	dc->SelectObject (oldFont);
	if(oldPen)
		dc->SelectObject (oldPen);
}

void CStringKeyboard::DrawGradientFill(CDC *pdc, CRect *rect)
{
	CRect pRect;
	int height = rect->Height();
	for (int i = rect->top; i <= rect->bottom; i ++)
	{
		pRect.SetRect(rect->left, i, rect->right, i+1);
		pdc->FillRect(&pRect, &m_btBkColor[((i-rect->top) * 63)/height]);
	}
}

void CStringKeyboard::DrawKeyboard(CWnd *pWnd, int list, CRect client)
{
	CClientDC dc(pWnd->GetParent());
	CRgn clipRgn;
	clipRgn.CreateRectRgnIndirect(&client);
	dc.SelectClipRgn(&clipRgn);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);

	KeycapDefine *key;
	POSITION pos;
	switch (list)
	{
	case 0:
		pos = m_numKeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_ABCKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_funcKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_abcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	m_currentState = DescribeKeycapState();
	int state = m_currentState;

	while (pos)
	{
		switch (list)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_ABCKeysList.GetNext(pos);
			break;
		case 2:
			key = m_funcKeysList.GetNext(pos);
			break;
		case 3:
			key = m_abcKeysList.GetNext(pos);
			break;
		default:
			break;
		}

		if (key->cNormal == 0x00)
		{
			switch (key->cShifted)
			{
			case CAPSLOCK:
				key->bHighlight = false;
				if (state & 0x01)
				{
					key->bHighlight = true;
				}
				break;
			default:
				break;
			}
		}

		DrawKeycap(&dc, key);
	}
}

int CStringKeyboard::DescribeKeycapState()
{
	int state = 0;
	short ks = GetKeyState(VK_CAPITAL);
	if (ks & 0x000F)
	{
		state += 0x01;
	}

	return state;
}

void CStringKeyboard::AddKey(char pNromal, char pShifted, int pWidth, int list)
{
	KeycapDefine *key = new KeycapDefine;
	key->cNormal = pNromal;
	key->cShifted = pShifted;
	key->cWidth = pWidth;
	key->bHighlight = false;

	switch (list)
	{
		// 数字字母键
	case 0:
		m_numKeysList.AddTail(key);
		break;
		// 字母按键
	case 1:
		m_ABCKeysList.AddTail(key);
		break;
		// 功能键
	case 2:
		m_funcKeysList.AddTail(key);
		break;
		// 字母按键
	case 3:
		m_abcKeysList.AddTail(key);
		break;
	default:
		break;
	}

	m_sumKeysList.AddTail(key);
}

void CStringKeyboard::CalcWidthAndHeight(CWnd *pWnd, int list)
{
	m_keycapWidth = m_keycapHeight = 0;
	KeycapDefine *key;
	POSITION pos;

	switch (list)
	{
	case 0:
		pos = m_numKeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_ABCKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_funcKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_abcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	long totalWidth, rows, loggest;
	totalWidth = rows = 0;
	loggest = 10;

	while (pos)
	{
		switch (list)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_ABCKeysList.GetNext(pos);
			break;
		case 2:
			key = m_funcKeysList.GetNext(pos);
			break;
		case 3:
			key = m_abcKeysList.GetNext(pos);
			break;
		default:
			break;
		}

		if (key->cNormal == 0x00 && key->cShifted == 0x00)
		{
			rows ++;
			if (totalWidth > loggest)
			{
				loggest = totalWidth;
			}

			totalWidth = 0;
		}
		else
		{
			totalWidth += abs(key->cWidth);
		}
	}

	CRect rect;
	pWnd->GetClientRect(rect);
	m_keycapHeight = rect.Height() / rows;
	m_keycapWidth = (int)(((double)rect.Width())/((((double)loggest))/10));

	m_keycapHeight -= 3;
	m_keycapWidth -= 3;
}

void CStringKeyboard::CalcKeycapRect(CRect client, int list)
{
	int x = client.left;
	int y = client.top - m_keycapHeight;
	KeycapDefine *key;
	POSITION pos;

	switch (list)
	{
	case 0:
		pos = m_numKeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_ABCKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_funcKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_abcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	while (pos)
	{
		switch(list)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_ABCKeysList.GetNext(pos);
			break;
		case 2:
			key = m_funcKeysList.GetNext(pos);
			break;
		case 3:
			key = m_abcKeysList.GetNext(pos);
			break;
		default:
			break;
		}

		if (key->cNormal == 0x00 && key->cShifted == 0x00)
		{
			x = client.left;
			y += m_keycapHeight;
			y += 3;

			key->rect.TopLeft().x = 0;
			key->rect.TopLeft().y = 0;
			key->rect.BottomRight().x = 0;
			key->rect.BottomRight().y = 0;
		}
		else
		{
			int width = ((abs(key->cWidth) * m_keycapWidth) / 10);
			CRect rc(x, y, x + width, y + m_keycapHeight);
			if (key->cWidth < 0)
			{
				rc.right = client.right;
			}
			else
			{
				x += width;
				if (2 == list)
				{
					x += 110;
				}
				else
				{
					x += 4;
				}

				key->rect = rc;
			}
		}
	}
}

void CStringKeyboard::SendKey(KeycapDefine *keyDef)
{
	if (keyDef->cNormal == 0x00)
	{
		int vk = 0;
		if (keyDef->cShifted > 0x6F)
		{
			vk = keyDef->cShifted;
		}
		else
		{
			switch (keyDef->cShifted)
			{
			case CAPSLOCK:
				vk = VK_CAPITAL;
				break;
			case ENTER:
				vk = VkKeyScan(0x0D)&0xFF;
				this->ShowWindow(SW_HIDE);
				break;
			case LEFTNUM:
				vk = VK_LEFT;
				break;
			case RIGHTNUM:
				vk = VK_RIGHT;
				break;
			case UPNUM:
				vk = VK_UP;
				break;
			case DOWNNUM:
				vk = VK_DOWN;
				break;
			case HOME:
				vk = VK_HOME;
				break;
			case DEL:
				vk = VK_DELETE;
				break;
			case BSPACE:
				vk = VK_BACK;
				break;
			case TAB:
				vk = VK_TAB;
				break;
			case SPACE:
				vk = VK_SPACE;
				break;
			case CLR:
				{
					m_tempString = "";
					UpdateData(FALSE);
				}
				break;
			case OK:
				{
					UpdateData(TRUE);
					SendDicingMsg(m_tempString);
					OnOK();
				}
				break;
			case CANCEL:
				{
					SendDicingMsg(m_stringkeyInfo.strCurrent);
					OnCancel();
				}
				break;
			case abc:
				{
					ntype = 3;
					CalcWidthAndHeight(strStatic, ntype);
					CalcKeycapRect(m_strClient, ntype);
					OnPaint();
				}
				break;
			case ABC:
				{
					ntype = 1;
					CalcWidthAndHeight(strStatic, ntype);
					CalcKeycapRect(m_strClient, ntype);
					OnPaint();
				}
				break;
			case NUM:
				{
					ntype = 0;
					CalcWidthAndHeight(strStatic, ntype);
					CalcKeycapRect(m_strClient, ntype);
					OnPaint();
				}
				break;
			default:
				break;
			}
		}

		keybd_event(vk, 0, 0, 0);
		keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
	}
	else
	{
		char pChar = keyDef->cNormal;
		SHORT ks = VkKeyScan(pChar);
		BYTE key = ks&0xFF;

		if (ks > 255)
		{
			keybd_event(VK_SHIFT, 0, 0, 0);
			keybd_event(key, 0, 0, 0);
			keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
		}
		else
		{
			keybd_event(key, 0, 0, 0);
		}
	}
}

void CStringKeyboard::FreeBkBrushColor()
{
	for (int i = 0; i < 64 ; i++)
	{
		m_btBkColor[i].DeleteObject();
	}
}

CString CStringKeyboard::LastInOrDec(CString strInput, int type)
{
	CString strOutput = "";
	double dInput = 0;
	dInput = atof(strInput);
	int iInput = 0;
	double dDecimal = 0.0;
	iInput = (int)dInput;
	dDecimal = ((int)((dInput - iInput) * 1000 + 0.5))/1000.000;
	int index = 0;
	if (1 == type)
	{
		index = -1;
	}
	else
	{
		index = 1;
	}

	if (dDecimal < 0.0000001)
	{
		strOutput.Format("%d", iInput + index);
	}
	else
	{
		int dec0, dec00, dec000;
		dec0 = dec00 = dec000 = 0;

		dec0 = (int)(dDecimal * 1000)%10;
		dec00 = (int)(dDecimal * 1000)/10%10;
		dec000 = (int)(dDecimal * 1000)/100%10;
		if (dec0)
		{
			strOutput.Format("%.3f", iInput + dDecimal + index * 0.001);
		}
		else if (dec00)
		{
			strOutput.Format("%.3f", iInput + dDecimal + index * 0.01);
		}
		else if (dec000)
		{
			strOutput.Format("%.3f", iInput + dDecimal + index * 0.1);
		}
	}

	return strOutput;
}

void CStringKeyboard::SendDicingMsg(CString strMsg)
{
	HWND pWnd = ::FindWindow(m_stringkeyInfo.strProcess,NULL);
	if (pWnd != NULL)
	{
		CString strMessage = "Keyboard$" + strMsg;
		COPYDATASTRUCT stData;
		stData.cbData= strMessage.GetLength()+1;
		stData.lpData= strMessage.GetBuffer(stData.cbData);		
		::SendMessage(pWnd, WM_COPYDATA, 0, (LPARAM)&stData );
	}
}