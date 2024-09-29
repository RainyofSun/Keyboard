
// KeyboardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Keyboard.h"
#include "KeyboardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyboardDlg �Ի���




CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyboardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_numberKeyboard = nullptr;
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


// CKeyboardDlg ��Ϣ�������

BOOL CKeyboardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKeyboardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���ּ���
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

// �ַ�����
void CKeyboardDlg::OnBnClickedStringKeyboardButton()
{
	
}

// �����ַ�����
void CKeyboardDlg::OnBnClickedBothKeyboardButton()
{
	
}
