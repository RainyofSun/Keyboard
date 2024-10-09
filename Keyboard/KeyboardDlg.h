
// KeyboardDlg.h : 头文件
//

#pragma once
#include "NumberKeyboard.h"
#include "StringKeyboard.h"
#include "FullKeyboard.h"

// CKeyboardDlg 对话框
class CKeyboardDlg : public CDialogEx
{
// 构造
public:
	CKeyboardDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
