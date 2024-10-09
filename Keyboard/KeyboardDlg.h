
// KeyboardDlg.h : ͷ�ļ�
//

#pragma once
#include "NumberKeyboard.h"
#include "StringKeyboard.h"
#include "FullKeyboard.h"

// CKeyboardDlg �Ի���
class CKeyboardDlg : public CDialogEx
{
// ����
public:
	CKeyboardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNumberKeyboardButton();
	afx_msg void OnBnClickedStringKeyboardButton();
	afx_msg void OnBnClickedBothKeyboardButton();

public:
	CNumberKeyboard *m_numberKeyboard;
	CStringKeyboard *m_stringKeyboard;
	CFullKeyboard	*m_fullyKeyboard;
};
