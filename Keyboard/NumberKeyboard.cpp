// NumberKeyboard.cpp : 实现文件
//

#include "stdafx.h"
#include "Keyboard.h"
#include "NumberKeyboard.h"
#include "afxdialogex.h"


// CNumberKeyboard 对话框

IMPLEMENT_DYNAMIC(CNumberKeyboard, CDialogEx)

CNumberKeyboard::CNumberKeyboard(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNumberKeyboard::IDD, pParent)
{
	
}

CNumberKeyboard::~CNumberKeyboard()
{
}

void CNumberKeyboard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEWVALUE_EDIT, m_tempString);
	DDX_Control(pDX, IDC_NEWVALUE_EDIT, m_CtlNewValueEdit);
}

BEGIN_MESSAGE_MAP(CNumberKeyboard, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MOUSEACTIVATE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

BOOL CNumberKeyboard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_dlgFont.m_hObject == nullptr)
	{
		m_dlgFont.CreateFont(FONT_MAINTAIN_DLG_TEXT);
	}
	
	SendMessageToDescendants(WM_SETFONT, (WPARAM)HFONT(m_dlgFont), MAKELPARAM(false, 0), false);

	m_brush.CreateSolidBrush(RGB(220, 220, 220));
	m_Brush = CreateSolidBrush(RGB(IDC_RED_DLG, IDC_GREEN_DLG, IDC_BLUE_DLG));
	
	GetDlgItem(IDC_NUMBER_TITLE_STATIC)->SetWindowPos(NULL, HULF_TITLE_POS, SWP_NOZORDER);

	SetWindowText(m_keyInfo.strTitle);

	GetDlgItem(IDC_NUMBER_TITLE_STATIC)->SetWindowText(m_keyInfo.strTitle);
	GetDlgItem(IDC_DEFAULT_EDIT)->SetWindowText(m_keyInfo.strDefault);
	GetDlgItem(IDC_CURRENT_EDIT)->SetWindowText(m_keyInfo.strCurrent);
	GetDlgItem(IDC_MAXIMUM_EDIT)->SetWindowText(m_keyInfo.strMaximum);
	GetDlgItem(IDC_MINIMUM_EDIT)->SetWindowText(m_keyInfo.strMinimum);
	GetDlgItem(IDC_UNIT_EDIT)->SetWindowText(m_keyInfo.strUnit);

	InitTextFont();
	FillBKBrushColor();

	numStatic = GetDlgItem(IDC_NUM_STATIC);
	funcStatic = GetDlgItem(IDC_FUNCTION_STATIC);

	AddKey(0x00, 0x00, 0, 0);
	AddKey('1', 0, 10, 0);
	AddKey('2', 0, 10, 0);
	AddKey('3', 0, 10, 0);
	AddKey(0x00, CLR, 11, 0);

	AddKey(0x00,0x00,1,0);	
	AddKey('4',0,10,0);
	AddKey('5',0,10,0);
	AddKey('6',0,10,0);
	AddKey(0x00,BSPACE,11,0);

	AddKey(0x00,0x00,2,0);	
	AddKey('7',0,10,0);
	AddKey('8',0,10,0);
	AddKey('9',0,10,0);
	AddKey(0x00,INC,11,0);

	AddKey(0x00,0x00,3,0);
	AddKey('0',0,10,0);
	AddKey('.',0,10,0);
	AddKey ('-',0,10,0);
	AddKey(0x00,DEC,11,0);

	::GetWindowRect(numStatic->m_hWnd, m_numberClient);
	ScreenToClient(m_numberClient);

	CalcWidthAndHeight(numStatic,0);//功能键
	CalcKeycapRect(m_numberClient,0);

	AddKey(0x00,0x00,1,1);//功能键
	AddKey(0x00,OK,3,1);
	AddKey(0x00,CANCEL,3,1);

	::GetWindowRect(funcStatic->m_hWnd, m_funcClient);
	ScreenToClient(m_funcClient);
	CalcWidthAndHeight(funcStatic,1);//功能键
	CalcKeycapRect(m_funcClient,1);

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

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CNumberKeyboard::DestroyWindow()
{
	if (m_dlgFont.m_hObject != nullptr)
	{
		m_dlgFont.DeleteObject();
	}

	if (m_TextFont.m_hObject != nullptr)
	{
		m_TextFont.DeleteObject();
	}

	DeleteObject(m_brush);

	if (m_Brush != nullptr)
	{
		DeleteObject(m_Brush);
	}

	FreeBkBrushColor();

	return CDialogEx::DestroyWindow();
}

void CNumberKeyboard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(IDC_RED_DLG, IDC_GREEN_DLG, IDC_BLUE_DLG));

	CPaintDC dc1(GetDlgItem(IDC_NUMBER_TITLE_STATIC));
	CRect rectClient;
	CDC dcMen, dcBk;
	CBitmap bitmapTemp, *oldBitTemp;
	GetDlgItem(IDC_NUMBER_BORDER_STATIC)->GetClientRect(&rectClient);
	bitmapTemp.CreateCompatibleBitmap(&dc1, rectClient.Width(), rectClient.Height());
	dcMen.CreateCompatibleDC(&dc1);
	oldBitTemp = dcMen.SelectObject(&bitmapTemp);

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

	dc1.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &dcMen, 0, 0, SRCCOPY);//绘制图片到主DC
	dcMen.SelectObject(oldBitTemp);//内存复位
	bitmapTemp.DeleteObject();

	DrawKeyboard(numStatic, 0, m_numberClient);
	DrawKeyboard(funcStatic, 1, m_funcClient);
}

HBRUSH CNumberKeyboard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (CTLCOLOR_STATIC == nCtlColor && pWnd->IsWindowEnabled() && !(::GetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE)&ES_READONLY))
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_Brush;
	}
	return hbr;
}

/**
 * 功能：释放画刷
 */ 
void CNumberKeyboard::FreeBkBrushColor()
{
	for (int i = 0; i < 64; i ++)
	{
		m_BtBkColor[i].DeleteObject();
	}
}

/**
 * 功能：初始化字体
 */ 
void CNumberKeyboard::InitTextFont()
{
	LOGFONT temp;
	memset(&temp, 0, sizeof(LOGFONT));
	// 24像素高的字体
	temp.lfHeight = FONT_HIGHT;
	// 800像素宽的字体
	temp.lfWeight = FONT_WIGHT;
	// 字体的字符集
	temp.lfCharSet = SHIFTJIS_CHARSET;
	// 字符的输出质量
	temp.lfQuality = 1;
	// 字符间距和字体族
	temp.lfPitchAndFamily = 1;
	// 字体名称
	strcpy((char *)temp.lfFaceName, "Arial");
	VERIFY(m_TextFont.CreatePointFontIndirect(&temp));
}

/**
 * 功能：填充画刷颜色
 */ 
void CNumberKeyboard::FillBKBrushColor()
{
	for (int i = 0; i < 64; i ++)
	{
		m_BtBkColor[i].CreateSolidBrush(RGB(190, 192, 194));
	}
}

/**
 * 功能：添加按钮个数和名称
 */ 
void CNumberKeyboard::AddKey(char pNromal, char pShifted, int pWidth, int list)
{
	KeycapDefine *key = new KeycapDefine;
	key->cNormal = pNromal;
	key->cShifted = pShifted;
	key->cWidth = pWidth;
	key->bHighlight = false;

	switch (list)
	{
	case 0: // 数字字母按键
		m_numKeysList.AddTail(key);
		break;
	case 1: // 功能键
		m_funcKeysList.AddTail(key);
		break;
	default:
		break;
	}

	m_sumKeysList.AddTail(key);
}

/**
 * 功能：计算按钮的宽高
 */ 
void CNumberKeyboard::CalcWidthAndHeight(CWnd *pWnd, int list)
{
	m_pKeycapWidth = m_pKeycapHeight = 0;

	KeycapDefine *key;
	POSITION pos;

	switch (list)
	{
	case 0:
		pos = m_numKeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_funcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	long totalWidth, longest, rows;
	totalWidth = rows = 0;
	longest = 10;

	while (pos)
	{
		switch (list)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_funcKeysList.GetNext(pos);
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
	m_pKeycapHeight = rect.Height() / rows;
	m_pKeycapWidth = (int)(((double)rect.Width())/((((double)(longest))/10)));
	m_pKeycapHeight -= 3;
	m_pKeycapWidth -= 2;
}

/**
 * 功能：计算按键的矩形区域
 */ 
void CNumberKeyboard::CalcKeycapRect(CRect client, int list)
{
	int x = client.left;
	int y = client.top - m_pKeycapHeight;
	KeycapDefine *key;
	POSITION pos;
	switch (list)
	{
	case 0:
		pos = m_numKeysList.GetHeadPosition();
		break;
	case 1:
		pos = m_funcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	while (pos)
	{
		switch (list)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_funcKeysList.GetNext(pos);
			break;
		default:
			break;
		}

		if (key->cNormal == 0x00 && key->cShifted == 0x00)
		{
			x = client.left;
			y += m_pKeycapHeight;
			// 行间隙
			y += 3;
			key->rect.TopLeft().x = 0;
			key->rect.TopLeft().y = 0;
			key->rect.BottomRight().x = 0;
			key->rect.BottomRight().y = 0;
		}
		else
		{
			int width = ((abs(key->cWidth) * m_pKeycapWidth) / 10);
			CRect rc(x, y, x + width, y + m_pKeycapHeight);

			if (key->cWidth < 0)
			{
				rc.right = client.right;
			}
			else
			{
				x += width;
				if (1 == list)
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

/**
 * 功能：发送按键信息
 */ 
void CNumberKeyboard::SendKey(KeycapDefine *keyDef)
{
	if (keyDef->cNormal == 0x00)
	{
		int vk = 0;
		if (keyDef->cShifted > 0x6F) // F1 - F12
		{
			vk = keyDef->cShifted;
		}
		else
		{
			// 判断功能键的类型
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
			case CLR: // 清除编辑框中的内容
				{
					m_tempString = "";
					UpdateData(FALSE);
				}
				break;
			case INC:
				{
					UpdateData(TRUE);
					m_tempString = LastInOrDec(m_tempString, 0);
					UpdateData(FALSE);
					long nLen = m_tempString.GetLength();
					m_CtlNewValueEdit.SetSel(nLen, nLen, FALSE);
					m_CtlNewValueEdit.SetFocus();
				}
				break;
			case DEC:
				{
					UpdateData(TRUE);
					m_tempString = LastInOrDec(m_tempString, 1);
					UpdateData(FALSE);
					long nLen = m_tempString.GetLength();
					m_CtlNewValueEdit.SetSel(nLen, nLen, FALSE);
					m_CtlNewValueEdit.SetFocus();
				}
				break;
			case OK:
				{
					CString strValue;
					int iValue = 0;
					float fValue = 0;
					CString message;

					if ("1" == m_numberKeyInfo.strFormat)
					{
						iValue = GetDlgItemInt(IDC_NEWVALUE_EDIT);
						strValue.Format("%d", iValue);

						if (iValue > atoi(m_numberKeyInfo.strMaximum))
						{
							message.Format("输入值大于最大值 %s", m_numberKeyInfo.strMaximum);
						}
						else if (iValue < atoi(m_numberKeyInfo.strMinimum))
						{
							message.Format("输入值小于最小值 %s", m_numberKeyInfo.strMinimum);
						}
					}
					else
					{
						UpdateData(TRUE);
						fValue = (float)atof(m_tempString);
						strValue.Format("%.3f", fValue);

						if (fValue > atof(m_numberKeyInfo.strMaximum))
						{
							message.Format("输入值大于最大值 %s", m_numberKeyInfo.strMaximum);
						}
						else if (fValue < atof(m_numberKeyInfo.strMinimum))
						{
							message.Format("输入值小于最小值 %s", m_numberKeyInfo.strMinimum);
						}
					}

					if (message.IsEmpty() == FALSE)
					{
						MessageBox(message);
						break;
					}

					SendDicingMsg(m_numberKeyInfo.strCurrent);
					CDialogEx::OnOK();
				}
				break;
			case CANCEL:
				{
					SendDicingMsg(m_numberKeyInfo.strCurrent);
					CDialogEx::OnCancel();
				}
				break;
			default:
				break;
			}

			keybd_event(vk, 0, 0, 0);
			keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
		}
	}
	else
	{
		char pChar = keyDef->cNormal;
		SHORT ks = VkKeyScan(pChar);
		BYTE key = ks&0xFF;

		keybd_event(key,0,0,0);
	}
}

/**
 * 功能：描述按钮状态
 */ 
int CNumberKeyboard::DescribeKeycapState()
{
	int state = 0;
	short ks = GetKeyState(VK_CAPITAL);
	if (ks & 0x000F)
	{
		state += 0x001;
	}

	return state;
}

/**
 * 功能：绘制键盘
 */ 
void CNumberKeyboard::DrawKeyboard(CWnd *pWnd, int list, CRect client)
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
		pos = m_funcKeysList.GetHeadPosition();
		break;
	default:
		break;
	}

	m_currentKeyState = DescribeKeycapState();
	int state = m_currentKeyState;

	while (pos)
	{
		switch (list)
		{
		case 0:
			key = m_numKeysList.GetNext(pos);
			break;
		case 1:
			key = m_funcKeysList.GetNext(pos);
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

	DeleteObject(clipRgn);
}

/**
 * 功能：绘制渐变按钮 
 */ 
void CNumberKeyboard::DrawGradientFill(CDC *pdc, CRect *rect)
{
	CRect pRect;
	int nHeight = rect->Height();
	for (int i = rect->top; i < rect->bottom; i++)
	{
		pRect.SetRect(rect->left, i, rect->right, i + 1);
		pdc->FillRect(&pRect, &m_BtBkColor[((i-rect->top) * 63)/nHeight]);
	}
}

/**
 * 功能：绘制键帽
 */ 
void CNumberKeyboard::DrawKeycap(CDC *dc, KeycapDefine *key)
{
	CString label = " ";
	BOOL special = FALSE;
	CRect rc = key->rect;

	if (key->cNormal == 0x00 && key->cShifted == 0x00)
	{
		return;
	}

	COLORREF oldColor = dc->GetTextColor();
	CPen pen, textPen, *oldPen = nullptr;

	// 没有高亮显示
	if (!key->bHighlight)
	{
		rc.DeflateRect(1,1);
		DrawGradientFill(dc, &rc);
		dc->Draw3dRect(rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DSHADOW));
		rc.DeflateRect(1, 1);
		dc->Draw3dRect(rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DLIGHT));
	}
	else
	// 高亮显示
	{
		rc.DeflateRect(1, 1);
		dc->FillSolidRect(rc, RGB(187, 225, 225)); // 鼠标在上面的时候填充颜色（0x2e, 0xc8, 0xe9）
		dc->Draw3dRect(rc, RGB(0,0,0),RGB(0,0,0));
		rc.DeflateRect(1, 1);
		dc->Draw3dRect(rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DSHADOW));
	}

	rc.DeflateRect(3, 1);
	// 按键的字体颜色和大小
	CFont *pOldFont = dc->SelectObject(&m_TextFont);
	// 设置字体颜色
	dc->SetTextColor(GetSysColor(COLOR_BTNTEXT));
	// 绘制方向键
	textPen.CreatePen(PS_SOLID, 2, GetSysColor(COLOR_BTNTEXT));
	oldPen = dc->SelectObject(&textPen);

	// 功能键键帽文案
	if (key->cNormal == 0x00)
	{
		// 非 F1---F12按键
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
				default:
					break;
			}
		}

		// 不绘制箭头
		if (!special)
		{
			CSize size;
			size = dc->GetTextExtent(label);
			dc->TextOut(((rc.left + rc.right)/2) - (size.cx/2), ((rc.top + rc.bottom)/2) - (size.cy/2), label);
		}
	}
	else
		// 数字或者字母键
	{
		if (key->cShifted >= 'A' && key->cShifted <= 'Z')
		{
			CSize size;
			label.Format("%c", key->cShifted);
			size = dc->GetTextExtent(label);
			dc->TextOut (((rc.left + rc.right)/2) - (size.cx /2), ((rc.top + rc.bottom )/2) - (size.cy/2), label);
		}
		else
			// 数字键
		{
			CSize size;
			if (key->cNormal == '-')
			{
				// 单独画，直接画 ‘-’ 字符太小
				size = dc->GetTextExtent("M");
				int cx = (rc.left + rc.right)/2;
				int cy = (rc.top + rc.bottom)/2;
				int size = (rc.Width()/8);
				dc->MoveTo(cx - size, cy);
				dc->LineTo(cx + size, cy);
			}
			else
			{
				size = dc->GetTextExtent("M");
				label.Format("%c", key->cNormal);
				dc->TextOut (((rc.left + rc.right)/2) - (size.cx /2), ((rc.top + rc.bottom )/2) - (size.cy/2), label);
			}
		}
	}

	dc->SetTextColor(oldColor);
	dc->SelectObject(pOldFont);
	if (oldPen)
	{
		dc->SelectObject(oldPen);
	}

	DeleteObject(textPen);
}

CString CNumberKeyboard::LastInOrDec(CString strInput, int type)
{
	CString strOutput = "";
	double dInput = 0;
	dInput = atof(strInput);
	int iInput = 0;
	double dDecimal = 0.0;
	iInput = (int)dInput;
	dDecimal = ((int)((dInput - iInput) * 1000 + 0.5))/1000.0;
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
		
		// 个位
		dec0 = (int)(dDecimal * 1000)%10;
		// 十位
		dec00 = (int)(dDecimal * 1000)/10%10;
		// 百位
		dec000 = (int)(dDecimal * 1000)/100%10;
		if (dec0)
		{
			strOutput.Format("%.3f", iInput + dDecimal + (index * 0.001));
		}

		if (dec00)
		{
			strOutput.Format("%.3f", iInput + dDecimal + (index * 0.01));
		}

		if (dec000)
		{
			strOutput.Format("%.3f", iInput + dDecimal + (index * 0.1));
		}
	}

	return strOutput;
}

void CNumberKeyboard::SendDicingMsg(CString strMsg)
{
	HWND pwnd = ::FindWindow(m_numberKeyInfo.strProcess, NULL);
	if (pwnd == NULL)
	{
		return;
	}

	CString strMessage = "Keyboard$" + strMsg;
	COPYDATASTRUCT stData;
	stData.cbData = strMessage.GetLength() + 1;
	stData.lpData = strMessage.GetBuffer(stData.cbData);
	::SendMessage(pwnd, WM_COPYDATA, 0, (LPARAM)&stData);
}

void CNumberKeyboard::OnCancel()
{
	SendDicingMsg(m_numberKeyInfo.strCurrent);

	CDialogEx::OnCancel();
}

void CNumberKeyboard::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);

	KeycapDefine *key;
	POSITION pos = m_sumKeysList.GetHeadPosition();
	m_currentKeyState = DescribeKeycapState();
	int state = m_currentKeyState;

	while (pos)
	{
		key = m_sumKeysList.GetNext(pos);
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

void CNumberKeyboard::OnLButtonUp(UINT nFlags, CPoint point)
{

	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode (TRANSPARENT);
	KeycapDefine *key;
	POSITION pos=m_sumKeysList.GetHeadPosition ();
	while(pos)
	{
		key=m_sumKeysList.GetNext (pos);
		if(key->rect.PtInRect (point))
		{
			SendKey(key);
			key->bHighlight =false;
			DrawKeycap(&dc,key);
			return;
		}
	}
}

void CNumberKeyboard::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetDlgItem(IDC_NEWVALUE_EDIT)->SetFocus();
}

void CNumberKeyboard::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnLButtonDown(nFlags,point);
}

int CNumberKeyboard::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return MA_NOACTIVATE;
}

void CNumberKeyboard::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	
	if (nState == WA_CLICKACTIVE && pWndOther != NULL)
	{
		::SetActiveWindow(pWndOther->GetSafeHwnd());
		return;
	}

	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}
