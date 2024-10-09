// FullKeyboard.cpp : 实现文件
//

#include "stdafx.h"
#include "Keyboard.h"
#include "FullKeyboard.h"
#include "afxdialogex.h"


// CFullKeyboard 对话框

IMPLEMENT_DYNAMIC(CFullKeyboard, CDialogEx)

CFullKeyboard::CFullKeyboard(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFullKeyboard::IDD, pParent)
{
	nType = 0;
	TempString = "";
}

CFullKeyboard::~CFullKeyboard()
{
	if (m_dlgFont.m_hObject != nullptr)
	{
		m_dlgFont.DeleteObject();
	}

	if (m_textFont.m_hObject != nullptr)
	{
		m_textFont.DeleteObject();
	}

	DeleteObject(m_brush);
	if (m_Brush != NULL)
	{
		DeleteObject(m_Brush);
	}

	if (m_BrushBlue != NULL)
	{
		DeleteObject(m_BrushBlue);
	}

	FreeBkBrushColor();
}

void CFullKeyboard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	nType = 0;
	DDX_Control(pDX, IDC_SURE_BUTTON, m_btnOK);
	DDX_Control(pDX, IDC_CANCEL_BUTTON, m_btnCancel);
	DDX_Text(pDX, IDC_NEWVALUE_EDIT, TempString);
}


BEGIN_MESSAGE_MAP(CFullKeyboard, CDialogEx)
	ON_WM_ACTIVATE()
	ON_WM_CTLCOLOR()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEACTIVATE()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SURE_BUTTON, &CFullKeyboard::OnBnClickedSureButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CFullKeyboard::OnBnClickedCancelButton)
END_MESSAGE_MAP()


// CFullKeyboard 消息处理程序


void CFullKeyboard::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if (nState == WA_CLICKACTIVE && pWndOther != nullptr)
	{
		::SetActiveWindow(pWndOther->GetSafeHwnd());
		return;
	}

	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}


HBRUSH CFullKeyboard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (CTLCOLOR_STATIC == nCtlColor && pWnd->IsWindowEnabled() && !(::GetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE)&ES_READONLY))
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	if (IDC_NUM_STATIC == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
		return hbr;
	}

	if (IDC_NEWVALUE_EDIT == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return m_BrushBlue;
	}

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_Brush;
	}

	return hbr;
}


void CFullKeyboard::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnMButtonDblClk(nFlags, point);
}


void CFullKeyboard::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);

	KeycapDefine *key;
	POSITION pos;

	CRect numRect, qweRect, asdRect, zxcRect, spaceRect, funcRect;

	int tempType = nType;
	str123Static->GetWindowRect(&numRect);
	qweStatic->GetWindowRect(&qweRect);
	asdStatic->GetWindowRect(&asdRect);
	zxcStatic->GetWindowRect(&zxcRect);
	spaceStatic->GetWindowRect(&spaceRect);
	funcStatic->GetWindowRect(&funcRect);

	ScreenToClient(numRect);
	ScreenToClient(qweRect);
	ScreenToClient(asdRect);
	ScreenToClient(zxcRect);
	ScreenToClient(spaceRect);
	ScreenToClient(funcRect);

	if (numRect.PtInRect(point))
	{
		tempType = nType;
	}
	else if (qweRect.PtInRect(point))
	{
		tempType = 1 + nType;
	}
	else if (asdRect.PtInRect(point))
	{
		tempType = 2 + nType;
	}
	else if (zxcRect.PtInRect(point))
	{
		tempType = 3 + nType;
	}
	else if (spaceRect.PtInRect(point))
	{
		tempType = 4;
	}
	else if (funcRect.PtInRect(point))
	{
		tempType = 5;
	}
	else 
	{
		return;
	}

	switch (tempType)
	{
	case 0:
		pos = m_num123KeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_QWEKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_ASDKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_ZXCKeysList.GetHeadPosition();
		break;
	case 4:
		pos = m_SPACEKeysList.GetHeadPosition();
		break;
	case 5:
		pos = m_FuncKeysList.GetHeadPosition();
		break;
	case 6:
		pos = m_num123KeysListSf.GetHeadPosition();
		break;
	case 7:
		pos = m_QWEKeysListSf.GetHeadPosition();
		break;
	case 8:
		pos = m_ASDKeysListSf.GetHeadPosition();
		break;
	case 9:
		pos = m_ZXCKeysListSf.GetHeadPosition();
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
			key = m_num123KeysList.GetNext(pos);
			break;
		case 1:
			key = m_QWEKeysList.GetNext(pos);
			break;
		case 2:
			key = m_ASDKeysList.GetNext(pos);
			break;
		case 3:
			key = m_ZXCKeysList.GetNext(pos);
			break;
		case 4:
			key = m_SPACEKeysList.GetNext(pos);
			break;
		case 5:
			key = m_FuncKeysList.GetNext(pos);
			break;
		case 6:
			key = m_num123KeysListSf.GetNext(pos);
			break;
		case 7:
			key = m_QWEKeysListSf.GetNext(pos);
			break;
		case 8:
			key = m_ASDKeysListSf.GetNext(pos);
			break;
		case 9:
			key = m_ZXCKeysListSf.GetNext(pos);
			break;
		default:
			break;
		}

		if (key->rect.PtInRect(point))
		{
			if (!key->bHighlight)
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

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CFullKeyboard::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);

	KeycapDefine *key;
	POSITION pos;
	CRect numRect, qweRect, asdRect, zxcRect, spaceRect, funcRect;

	int tempType = nType;
	str123Static->GetWindowRect(&numRect);
	qweStatic->GetWindowRect(&qweRect);
	asdStatic->GetWindowRect(&asdRect);
	zxcStatic->GetWindowRect(&zxcRect);
	spaceStatic->GetWindowRect(&spaceRect);
	funcStatic->GetWindowRect(&funcRect);

	ScreenToClient(numRect);
	ScreenToClient(qweRect);
	ScreenToClient(asdRect);
	ScreenToClient(zxcRect);
	ScreenToClient(spaceRect);
	ScreenToClient(funcRect);

	if (numRect.PtInRect(point))
	{
		tempType = nType;
	}
	else if (qweRect.PtInRect(point))
	{
		tempType = 1 + nType;
	}
	else if (asdRect.PtInRect(point))
	{
		tempType = 2 + nType;
	}
	else if (zxcRect.PtInRect(point))
	{
		tempType = 3 + nType;
	}
	else if (spaceRect.PtInRect(point))
	{
		tempType = 4;
	}
	else if (funcRect.PtInRect(point))
	{
		tempType = 5;
	}
	else
	{
		return;
	}

	switch (tempType)
	{
	case 0:
		pos = m_num123KeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_QWEKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_ASDKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_ZXCKeysList.GetHeadPosition();
		break;
	case 4:
		pos = m_SPACEKeysList.GetHeadPosition();
		break;
	case 5:
		pos = m_FuncKeysList.GetHeadPosition();
		break;
	case 6:
		pos = m_num123KeysListSf.GetHeadPosition();
		break;
	case 7:
		pos = m_ASDKeysListSf.GetHeadPosition();
		break;
	case 8:
		pos = m_ASDKeysListSf.GetHeadPosition();
		break;
	case 9:
		pos = m_ZXCKeysListSf.GetHeadPosition();
		break;
	default:
		break;
	}

	while (pos)
	{
		switch (tempType)
		{
		case 0:
			key = m_num123KeysList.GetNext(pos);
			break;
		case 1:
			key = m_QWEKeysList.GetNext(pos);
			break;
		case 2:
			key = m_ASDKeysList.GetNext(pos);
			break;
		case 3:
			key = m_ZXCKeysList.GetNext(pos);
			break;
		case 4:
			key = m_SPACEKeysList.GetNext(pos);
			break;
		case 5:
			key = m_FuncKeysList.GetNext(pos);
			break;
		case 6:
			key = m_num123KeysListSf.GetNext(pos);
			break;
		case 7:
			key = m_QWEKeysListSf.GetNext(pos);
			break;
		case 8:
			key = m_ASDKeysListSf.GetNext(pos);
			break;
		case 9:
			key = m_ZXCKeysListSf.GetNext(pos);
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


int CFullKeyboard::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return MA_NOACTIVATE;
}


void CFullKeyboard::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnMouseMove(nFlags, point);
}


void CFullKeyboard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;

	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(IDC_RED_DLG, IDC_GREEN_DLG, IDC_BLUE_DLG));
	ReleaseDC(&dc);

	CPaintDC dc1(GetDlgItem(IDC_NUMBER_BORDER_STATIC));
	CRect rectCliet;
	CDC dcMen, dcBkgrand;
	CBitmap bitmapTemp, *oldBitMap;

	GetDlgItem(IDC_NUMBER_BORDER_STATIC)->GetClientRect(&rectCliet);
	bitmapTemp.CreateCompatibleBitmap(&dc1, rectCliet.Width(), rectCliet.Height());
	dcMen.CreateCompatibleDC(&dc1);
	oldBitMap = dcMen.SelectObject(&bitmapTemp);

	int r1 = 0, g1 = 25, b1 = 52;
	int r2 = 204, g2 = 229, b2 = 235;

	for (int i = 0; i < rectCliet.Width() ; i++)
	{
		int r,g,b;
		r = r1 + (i * (r2-r1))/rectCliet.Width();
		g = g1 + (i * (g2 - g1))/rectCliet.Width();
		b = b1 + (i * (b2 - b1))/rectCliet.Width();

		dcMen.FillSolidRect(i, 0, 1, rectCliet.Height(), RGB(r, g, b));
	}

	dc1.BitBlt(0, 0, rectCliet.Width(), rectCliet.Height(), &dcMen, 0, 0, SRCCOPY);
	dcMen.SelectObject(oldBitMap);
	bitmapTemp.DeleteObject();

	DrawKeyboard(str123Static, nType, m_str123Client);
	DrawKeyboard(qweStatic, 1 + nType, m_QWEClient);
	DrawKeyboard(asdStatic, 2 + nType, m_ASDClient);
	DrawKeyboard(zxcStatic, 3 + nType, m_ZXCClient);
	DrawKeyboard(spaceStatic, 4, m_SPACEClient);
	DrawKeyboard(funcStatic, 5, m_FunClient);
}


void CFullKeyboard::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


BOOL CFullKeyboard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_dlgFont.m_hObject == nullptr)
	{
		m_dlgFont.CreateFont(FONT_MAINTAIN_DLG_TEXT);
	}

	SendMessageToDescendants(WM_SETFONT, (WPARAM)HFONT(m_dlgFont), MAKELPARAM(false, 0), false);
	
	GetDlgItem(IDC_NUMBER_BORDER_STATIC)->SetWindowPos(NULL, FULL_TITLE_POS, SWP_NOZORDER);
	GetDlgItem(IDC_NUMBER_TITLE_STATIC)->SetWindowText(m_strkeyInfo.strTitle);

	m_brush.CreateSolidBrush(RGB(220, 200, 220));
	m_Brush = CreateSolidBrush(RGB(IDC_RED_DLG, IDC_GREEN_DLG, IDC_BLUE_DLG));
	m_BrushBlue = CreateSolidBrush(RGB(0, 0, 255));
	SetWindowText(m_strkeyInfo.strTitle);

	InitTextFont();
	FillBKBrushColor();

	str123Static = GetDlgItem(IDC_NUM123_STATIC);
	qweStatic = GetDlgItem(IDC_QWE_STATIC);
	asdStatic = GetDlgItem(IDC_ASD_STATIC);
	zxcStatic = GetDlgItem(IDC_ZXC_STATIC);
	spaceStatic = GetDlgItem(IDC_SPACE_STATIC);
	funcStatic = GetDlgItem(IDC_FUNC_STATIC);

	AddKey(0x00,0x00,0,0);	
	AddKey('1',0,2,0);
	AddKey('2',0,2,0);
	AddKey('3',0,2,0);
	AddKey('4',0,2,0);
	AddKey('5',0,2,0);
	AddKey('6',0,2,0);
	AddKey('7',0,2,0);
	AddKey('8',0,2,0);
	AddKey('9',0,2,0);
	AddKey('0',0,2,0);
	AddKey('-',0,2,0);
	AddKey('=',0,2,0);
	AddKey(0x00,EMPTY,2,0);

	AddKey(0x00,0x00,0,6);	
	AddKey('!',0,2,6);
	AddKey('@',0,2,6);
	AddKey('#',0,2,6);
	AddKey('$',0,2,6);
	AddKey('%',0,2,6);
	AddKey('^',0,2,6);
	AddKey('&',0,2,6);
	AddKey('*',0,2,6);
	AddKey('(',0,2,6);
	AddKey(')',0,2,6);
	AddKey('_',0,2,6);
	AddKey('+',0,2,6);
	AddKey(0x00,EMPTY,2,6);
	//	AddKey(0x00,BSPACE,3,0);

	::GetWindowRect(str123Static->m_hWnd ,m_str123Client);
	ScreenToClient(m_str123Client);

	CalcWidthAndHeight(str123Static,0);//字母
	CalcKeycapRect(m_str123Client,0);

	AddKey(0x00,0x00,0,1);	
	AddKey('Q',0,2,1);
	AddKey('W',0,2,1);
	AddKey('E',0,2,1);
	AddKey('R',0,2,1);
	AddKey('T',0,2,1);
	AddKey('Y',0,2,1);
	AddKey('U',0,2,1);
	AddKey('I',0,2,1);
	AddKey('O',0,2,1);
	AddKey('P',0,2,1);
	AddKey('[',0,2,1);
	AddKey(']',0,2,1);
	//AddKey(0x00,EMPTY,1,1);
	//AddKey(0x00,CLR,3,1);
	AddKey(0x00,0x00,0,7);	
	AddKey('q',0,2,7);
	AddKey('w',0,2,7);
	AddKey('e',0,2,7);
	AddKey('r',0,2,7);
	AddKey('t',0,2,7);
	AddKey('y',0,2,7);
	AddKey('u',0,2,7);
	AddKey('i',0,2,7);
	AddKey('o',0,2,7);
	AddKey('p',0,2,7);
	AddKey('{',0,2,7);
	AddKey('}',0,2,7);

	::GetWindowRect(qweStatic->m_hWnd ,m_QWEClient);
	ScreenToClient(m_QWEClient);

	CalcWidthAndHeight(qweStatic,1);//字母
	CalcKeycapRect(m_QWEClient,1);

	AddKey(0x00,0x00,0,2);	
	AddKey('A',0,2,2);
	AddKey('S',0,2,2);
	AddKey('D',0,2,2);
	AddKey('F',0,2,2);
	AddKey('G',0,2,2);
	AddKey('H',0,2,2);
	AddKey('J',0,2,2);
	AddKey('K',0,2,2);
	AddKey('L',0,2,2);
	AddKey(';',0,2,2);
	AddKey(0x00,EMPTY,2,2);
	AddKey(0x00,EMPTY,2,2);

	AddKey(0x00,0x00,0,8);	
	AddKey('a',0,2,8);
	AddKey('s',0,2,8);
	AddKey('d',0,2,8);
	AddKey('f',0,2,8);
	AddKey('g',0,2,8);
	AddKey('h',0,2,8);
	AddKey('j',0,2,8);
	AddKey('k',0,2,8);
	AddKey('l',0,2,8);
	AddKey(':',0,2,8);
	AddKey(0x00,EMPTY,2,8);
	AddKey(0x00,EMPTY,2,8);

	::GetWindowRect(asdStatic->m_hWnd ,m_ASDClient);
	ScreenToClient(m_ASDClient);

	CalcWidthAndHeight(asdStatic,2);//字母
	CalcKeycapRect(m_ASDClient,2);

	AddKey(0x00,0x00,0,3);	
	AddKey('Z',0,2,3);
	AddKey('X',0,2,3);
	AddKey('C',0,2,3);
	AddKey('V',0,2,3);
	AddKey('B',0,2,3);
	AddKey('N',0,2,3);
	AddKey('M',0,2,3);
	AddKey(',',0,2,3);
	AddKey('.',0,2,3);
	AddKey('/',0,2,3);
	AddKey(0x00,EMPTY,2,3);

	AddKey(0x00,0x00,0,9);	
	AddKey('z',0,2,9);
	AddKey('x',0,2,9);
	AddKey('c',0,2,9);
	AddKey('v',0,2,9);
	AddKey('b',0,2,9);
	AddKey('n',0,2,9);
	AddKey('m',0,2,9);
	AddKey('<',0,2,9);
	AddKey('>',0,2,9);
	AddKey('?',0,2,9);
	AddKey(0x00,EMPTY,2,9);
	
	::GetWindowRect(zxcStatic->m_hWnd ,m_ZXCClient);
	ScreenToClient(m_ZXCClient);
	CalcWidthAndHeight(zxcStatic,3);//字母
	CalcKeycapRect(m_ZXCClient,3);

	AddKey(0x00,0x00,0,4);	
	AddKey(0x00,SPACE,10,4);

	::GetWindowRect(spaceStatic->m_hWnd ,m_SPACEClient);
	ScreenToClient(m_SPACEClient);
	CalcWidthAndHeight(spaceStatic,4);//字母
	CalcKeycapRect(m_SPACEClient,4);

	AddKey(0x00,0x00,0,5);	
	AddKey(0x00,BSPACE,10,5);
	AddKey(0x00,0x00,1,5);	
	AddKey(0x00,CLR,10,5);
	AddKey(0x00,0x00,2,5);	
	AddKey(0x00,SHIFT,10,5);

	::GetWindowRect(funcStatic->m_hWnd ,m_FunClient);
	ScreenToClient(m_FunClient);
	CalcWidthAndHeight(funcStatic,5);
	CalcKeycapRect(m_FunClient,5);

	CRect rcDlgs;
	GetWindowRect(rcDlgs);  
	SetWindowPos(&wndTopMost,100,POS_DLG_Y + 100,rcDlgs.Width(),rcDlgs.Height(),SWP_SHOWWINDOW | SWP_NOACTIVATE);//wndTopMost//设置位置大小
	GetDlgItem(IDC_NEWVALUE_EDIT)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CFullKeyboard::OnBnClickedSureButton()
{
	OnCancel();
}


void CFullKeyboard::OnBnClickedCancelButton()
{
	OnCancel();
}

void CFullKeyboard::InitTextFont()
{
	LOGFONT temp;
	memset(&temp, 0, sizeof(LOGFONT));
	temp.lfHeight = FONT_HIGHT;
	temp.lfWidth = FONT_WIGHT;
	temp.lfCharSet = SHIFTJIS_CHARSET;
	temp.lfQuality = 1;
	temp.lfPitchAndFamily = 1;
	strcpy((char*)temp.lfFaceName, "Arial");
	VERIFY(m_textFont.CreateFontIndirect(&temp));
}

void CFullKeyboard::FillBKBrushColor()
{
	for (int i = 0; i < 64; i ++)
	{
		m_btBkColor[i].CreateSolidBrush(RGB(190, 192, 194));
	}
}

void CFullKeyboard::DrawKeycap(CDC *dc, KeycapDefine *key)
{
	CString label = " ";
	BOOL special = FALSE;
	CRect rc = key->rect;

	if (key->cNormal == 0x00 && key->cShifted == 0x00)
	{
		return;
	}

	COLORREF oldColor = dc->GetTextColor();
	CPen Pen, textPen, *oldPen = nullptr;

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
		dc->Draw3dRect(rc, RGB(0, 0, 0), RGB(0, 0, 0));
		rc.DeflateRect(1, 1);
		dc->Draw3dRect(rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DDKSHADOW));
	}

	rc.DeflateRect(3, 1);
	CFont *pOldFont = dc->SelectObject(&m_textFont);
	dc->SetTextColor(GetSysColor(COLOR_BTNTEXT));
	textPen.CreatePen(PS_SOLID, 2, GetSysColor(COLOR_BTNTEXT));
	oldPen = dc->SelectObject(&textPen);

	if (key->cNormal == 0x00)
	{
		if (key->cShifted < 0x6F)
		{
			switch (key->cShifted)
			{
			case CAPSLOCK:
				label = "Cap";
				break;
			case ENTER:
				label = "Enter";
				break;
			case SPACE:
				label = "Space";
				break;
			case DEL:
				label = "Del";
				break;
			case CLR:
				label = "Clr";
				break;
			case BSPACE:
				label = "BK";
				break;
			case INC:
				label = "INC";
				break;
			case DEC:
				label = "DEC";
				break;
			case OK:
				label = "OK";
				break;
			case CANCEL:
				label = "CANCEL";
				break;
			case abc:
				label = "abc";
				break;
			case ABC:
				label = "ABC";
				break;
			case NUM:
				label = "123";
				break;
			case SHIFT:
				label = "SHIFT";
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
		if ((key->cShifted >= 'A' && key->cShifted <= 'Z') || (key->cShifted >= 'a' && key->cShifted <= 'z'))
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
				size = dc->GetTextExtent(label);
				int cx = (rc.left + rc.right)/2;
				int cy = (rc.top + rc.bottom)/2;
				int size = rc.Width()/8;

				dc->MoveTo(cx - size, cy + size);
				dc->LineTo(cx + size, cy + size);
			}
			else
			{
				size = dc->GetTextExtent("M");
				label.Format("%c", key->cNormal);
				dc->TextOut((rc.left + rc.right)/2 - size.cx/2, (rc.top + rc.bottom)/2 - size.cy/2, label);
			}
		}
	}

	dc->SetTextColor(oldColor);
	dc->SelectObject(pOldFont);
	if (oldPen)
	{
		dc->SelectObject(oldPen);
	}
}

void CFullKeyboard::DrawGradientFill(CDC *pdc, CRect *rect)
{
	CRect pRect;
	int nHeight = rect->Height();
	for (int i = rect->top; i <= rect->bottom; i ++)
	{
		pRect.SetRect(rect->left, i, rect->right, i + 1);
		pdc->FillRect(&pRect, &m_btBkColor[((i-rect->top) * 63)/nHeight]);
	}
}

void CFullKeyboard::DrawKeyboard(CWnd *pWnd, int list, CRect client)
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
		pos = m_num123KeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_QWEKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_ASDKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_ZXCKeysList.GetHeadPosition();
		break;
	case 4:
		pos = m_SPACEKeysList.GetHeadPosition();
		break;
	case 5:
		pos = m_FuncKeysList.GetHeadPosition();
		break;
	case 6:
		pos = m_num123KeysListSf.GetHeadPosition();
		break;
	case 7:
		pos = m_QWEKeysListSf.GetHeadPosition();
		break;
	case 8:
		pos = m_ASDKeysListSf.GetHeadPosition();
		break;
	case 9:
		pos = m_ZXCKeysListSf.GetHeadPosition();
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
			key = m_num123KeysList.GetNext(pos);
			break;
		case 1:
			key = m_QWEKeysList.GetNext(pos);
			break;
		case 2:
			key = m_ASDKeysList.GetNext(pos);
			break;
		case 3:
			key = m_ZXCKeysList.GetNext(pos);
			break;
		case 4:
			key = m_SPACEKeysList.GetNext(pos);
			break;
		case 5:
			key = m_FuncKeysList.GetNext(pos);
			break;
		case 6:
			key = m_num123KeysListSf.GetNext(pos);
			break;
		case 7:
			key = m_QWEKeysListSf.GetNext(pos);
			break;
		case 8:
			key = m_ASDKeysListSf.GetNext(pos);
			break;
		case 9:
			key = m_ZXCKeysListSf.GetNext(pos);
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

int CFullKeyboard::DescribeKeycapState()
{
	int state = 0;
	short ks = GetKeyState(VK_CAPITAL);
	if (ks & 0x000F)
	{
		state += 0x01;
	}

	return state;
}

void CFullKeyboard::AddKey(char pNromal, char pShifted, int pWidth, int list)
{
	KeycapDefine *key = new KeycapDefine;
	key->cNormal = pNromal;
	key->cShifted = pShifted;
	key->cWidth = pWidth;
	key->bHighlight = false;

	switch (list)
	{
	case 0:
		m_num123KeysList.AddTail(key);
		break;
	case 1:
		m_QWEKeysList.AddTail(key);
		break;
	case 2:
		m_ASDKeysList.AddTail(key);
		break;
	case 3:
		m_ZXCKeysList.AddTail(key);
		break;
	case 4:
		m_SPACEKeysList.AddTail(key);
		break;
	case 5:
		m_FuncKeysList.AddTail(key);
		break;
	case 6:
		m_num123KeysListSf.AddTail(key);
		break;
	case 7:
		m_QWEKeysListSf.AddTail(key);
		break;
	case 8:
		m_ASDKeysListSf.AddTail(key);
		break;
	case 9:
		m_ZXCKeysListSf.AddTail(key);
		break;
	default:
		break;
	}

	m_sumKeysList.AddTail(key);
}

void CFullKeyboard::CalcWidthAndHeight(CWnd *pWnd, int list)
{
	m_keycapHeight = m_keycapWidth = 0;
	
	KeycapDefine *key;
	POSITION pos;

	switch (list)
	{
	case 0:
		pos = m_num123KeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_QWEKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_ASDKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_ZXCKeysList.GetHeadPosition();
		break;
	case 4:
		pos = m_SPACEKeysList.GetHeadPosition();
		break;
	case 5:
		pos = m_FuncKeysList.GetHeadPosition();
		break;
	case 6:
		pos = m_num123KeysListSf.GetHeadPosition();
		break;
	case 7:
		pos = m_QWEKeysListSf.GetHeadPosition();
		break;
	case 8:
		pos = m_ASDKeysListSf.GetHeadPosition();
		break;
	case 9:
		pos = m_ZXCKeysListSf.GetHeadPosition();
		break;
	default:
		break;
	}

	long totalWidth, rows;
	totalWidth = rows = 0;
	long longest = 10;

	while (pos)
	{
		switch (list)
		{
		case 0:
			key = m_num123KeysList.GetNext(pos);
			longest = 27;
			break;
		case 1:
			key = m_QWEKeysList.GetNext(pos);
			longest = 25;
			break;
		case 2:
			key = m_ASDKeysList.GetNext(pos);
			longest = 25;
			break;
		case 3:
			key = m_ZXCKeysList.GetNext(pos);
			longest = 25;
			break;
		case 4:
			key = m_SPACEKeysList.GetNext(pos);
			break;
		case 5:
			key = m_FuncKeysList.GetNext(pos);
			break;
		case 6:
			key = m_num123KeysListSf.GetNext(pos);
			longest = 27;
			break;
		case 7:
			key = m_QWEKeysListSf.GetNext(pos);
			longest = 25;
			break;
		case 8:
			key = m_ASDKeysListSf.GetNext(pos);
			longest = 25;
			break;
		case 9:
			key = m_ZXCKeysListSf.GetNext(pos);
			longest = 23;
			break;
		default:
			break;
		}

		if (key->cNormal == 0x00 && key->cShifted == 0x00)
		{
			rows ++;
			if (totalWidth > longest)
			{
				longest = totalWidth;
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
	m_keycapHeight = rect.Height()/rows;
	m_keycapWidth = (int)(((double)rect.Width())/(((double)longest)/10));
	m_keycapHeight -= 3;
	if (list == 5)
	{
		m_keycapHeight -= 5;
	}
	m_keycapWidth -= 3;
}

void CFullKeyboard::CalcKeycapRect(CRect client, int list)
{
	int x = client.left;
	int y = client.top - m_keycapHeight;

	KeycapDefine *key;
	POSITION pos;

	switch (list)
	{
	case 0:
		pos = m_num123KeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_QWEKeysList.GetHeadPosition();
		break;
	case 2:
		pos = m_ASDKeysList.GetHeadPosition();
		break;
	case 3:
		pos = m_ZXCKeysList.GetHeadPosition();
		break;
	case 4:
		pos = m_SPACEKeysList.GetHeadPosition();
		break;
	case 5:
		pos = m_FuncKeysList.GetHeadPosition();
		break;
	case 6:
		pos = m_num123KeysListSf.GetHeadPosition();
		break;
	case 7:
		pos = m_QWEKeysListSf.GetHeadPosition();
		break;
	case 8:
		pos = m_ASDKeysListSf.GetHeadPosition();
		break;
	case 9:
		pos = m_ZXCKeysListSf.GetHeadPosition();
		break;
	default:
		break;
	}

	while (pos)
	{
		switch (list)
		{
		case 0:
			key = m_num123KeysList.GetNext(pos);
			break;
		case 1:
			key = m_QWEKeysList.GetNext(pos);
			break;
		case 2:
			key = m_ASDKeysList.GetNext(pos);
			break;
		case 3:
			key = m_ZXCKeysList.GetNext(pos);
			break;
		case 4:
			key = m_SPACEKeysList.GetNext(pos);
			break;
		case 5:
			key = m_FuncKeysList.GetNext(pos);
			break;
		case 6:
			key = m_num123KeysListSf.GetNext(pos);
			break;
		case 7:
			key = m_QWEKeysListSf.GetNext(pos);
			break;
		case 8:
			key = m_ASDKeysListSf.GetNext(pos);
			break;
		case 9:
			key = m_ZXCKeysListSf.GetNext(pos);
			break;
		default:
			break;
		}

		if (key->cNormal == 0x00 && key->cShifted == 0x00)
		{
			x = client.left;
			y += (m_keycapHeight + 3);

			if (5 == list)
			{
				y +=5;
			}

			key->rect.TopLeft().x = 0;
			key->rect.TopLeft().y = 0;
			key->rect.BottomRight().x = 0;
			key->rect.BottomRight().y = 0;
		}
		else
		{
			int width = ((abs(key->cWidth) * m_keycapWidth)/10);
			CRect rc(x, y, x + width, y + m_keycapHeight);
			if (key->cWidth < 0)
			{
				rc.right = client.right;
			}
			else
			{
				x += (width + 4);
				key->rect = rc;
			}
		}
	}
}

void CFullKeyboard::SendKey(KeycapDefine *keyDef)
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
				vk = VK_SPACE;
				break;
			case TAB:
				vk = VK_TAB;
				break;
			case SPACE:
				vk = VK_SPACE;
				break;
			case CLR:
				{
					TempString = "";
					UpdateData(FALSE);
				}
				break;
			case OK:
				break;
			case CANCEL:
				CDialogEx::OnCancel();
				break;
			case SHIFT:
				{
					if (0 == nType)
					{
						nType = 6;
					}
					else
					{
						nType = 0;
					}

					CalcWidthAndHeight(str123Static, nType);
					CalcKeycapRect(m_str123Client, nType);
					CalcWidthAndHeight(qweStatic, 1 + nType);
					CalcKeycapRect(m_QWEClient, 1 + nType);
					CalcWidthAndHeight(asdStatic, 2 + nType);
					CalcKeycapRect(m_ASDClient, 2 + nType);
					CalcWidthAndHeight(zxcStatic, 3 + nType);
					CalcKeycapRect(m_ZXCClient, 3 + nType);
					OnPaint();
				}
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

void CFullKeyboard::FreeBkBrushColor()
{
	for (int i = 0; i < 64; i ++)
	{
		m_btBkColor[i].DeleteObject();
	}
}

void CFullKeyboard::SendDicingMsg(CString strMsg)
{
	HWND pWnd = ::FindWindow(m_strkeyInfo.strProcess,NULL);
	if (pWnd != NULL)
	{
		CString strMessage = "Keyboard$" + strMsg;
		COPYDATASTRUCT stData;
		stData.cbData= strMessage.GetLength()+1;
		stData.lpData= strMessage.GetBuffer(stData.cbData);		
		::SendMessage(pWnd, WM_COPYDATA, 0, (LPARAM)&stData );
	}
}