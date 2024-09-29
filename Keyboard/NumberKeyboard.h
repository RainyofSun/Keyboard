#pragma once
#include "KeyboardConfig.h"
#include "afxwin.h"

// CNumberKeyboard 对话框

class CNumberKeyboard : public CDialogEx
{
	DECLARE_DYNAMIC(CNumberKeyboard)

public:
	CNumberKeyboard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNumberKeyboard();

// 对话框数据
	enum { IDD = IDD_NUMBER_KEYBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnPaint();

private:
	CBrush m_brush;
	CBrush m_BtBkColor[64];
	HBRUSH m_Brush;
	
	CRect m_numberClient;
	CRect m_funcClient;

	CFont m_dlgFont;
	CFont m_TextFont;

	KeyInfo m_keyInfo;
	KeyInfo m_numberKeyInfo;

	CWnd *numStatic;
	CWnd *funcStatic;
	
	CString m_tempString;

	// 数字或者字母
	CTypedPtrList<CPtrList,KeycapDefine*> m_numKeysList;
	// 功能键
	CTypedPtrList<CPtrList,KeycapDefine*> m_funcKeysList;
	// 所有的按键
	CTypedPtrList<CPtrList,KeycapDefine*> m_sumKeysList;

	int m_pKeycapWidth;
	int m_pKeycapHeight;
	int m_currentKeyState;

private:
	void FreeBkBrushColor();
	void InitTextFont();
	void FillBKBrushColor();
	void AddKey(char pNromal, char pShifted, int pWidth, int list);
	void CalcWidthAndHeight(CWnd *pWnd, int list);
	void CalcKeycapRect(CRect client, int list);
	void SendKey(KeycapDefine *keyDef);
	void DrawKeycap(CDC *dc, KeycapDefine *key);
	void DrawKeyboard(CWnd *pWnd, int list, CRect client);
	void DrawGradientFill(CDC *pdc, CRect *rect);
	int DescribeKeycapState();
	CString LastInOrDec(CString strInput, int type);
	void SendDicingMsg(CString strMsg);

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	CEdit m_CtlNewValueEdit;
};
