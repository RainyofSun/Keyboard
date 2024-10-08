
// KeyboardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Keyboard.h"
#include "KeyboardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyboardDlg 对话框




CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyboardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_numberKeyboard = nullptr;
	m_stringKeyboard = nullptr;
	m_fullyKeyboard  = nullptr;
}

void CKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyboardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NUMBER_KEYBOARD_BUTTON, &CKeyboardDlg::OnBnClickedNumberKeyboardButton)
	ON_BN_CLICKED(IDC_STRING_KEYBOARD_BUTTON, &CKeyboardDlg::OnBnClickedStringKeyboardButton)
	ON_BN_CLICKED(IDC_BOTH_KEYBOARD_BUTTON, &CKeyboardDlg::OnBnClickedBothKeyboardButton)
END_MESSAGE_MAP()


// CKeyboardDlg 消息处理程序

BOOL CKeyboardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKeyboardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 数字键盘
void CKeyboardDlg::OnBnClickedNumberKeyboardButton()
{
	if (m_numberKeyboard != nullptr)
	{
		m_numberKeyboard->DestroyWindow();
		delete m_numberKeyboard;
		m_numberKeyboard = nullptr;
	}

	m_numberKeyboard = new CNumberKeyboard;
	m_numberKeyboard->Create(IDD_NUMBER_KEYBOARD_DIALOG);
	m_numberKeyboard->ShowWindow(SW_SHOW);
}

// 字符键盘
void CKeyboardDlg::OnBnClickedStringKeyboardButton()
{
	if (m_stringKeyboard != nullptr)
	{
		m_stringKeyboard->DestroyWindow();
		delete m_stringKeyboard;
		m_stringKeyboard = nullptr;
	}

	m_stringKeyboard = new CStringKeyboard;
	m_stringKeyboard->Create(IDD_STRING_KEYBOARD_DIALOG);
	m_stringKeyboard->ShowWindow(SW_SHOW);
}

// 数字字符键盘
void CKeyboardDlg::OnBnClickedBothKeyboardButton()
{
	if (m_fullyKeyboard != nullptr)
	{
		m_fullyKeyboard->DestroyWindow();
		delete m_fullyKeyboard;
		m_fullyKeyboard = nullptr;
	}

	m_fullyKeyboard = new CFullKeyboard;
	m_fullyKeyboard->Create(IDD_FULL_KEYBOARD_DIALOG);
	m_fullyKeyboard->ShowWindow(SW_SHOW);
}
