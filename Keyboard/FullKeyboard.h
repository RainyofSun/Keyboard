#pragma once
#include "KeyboardConfig.h"
#include "afxwin.h"

// CFullKeyboard 对话框

class CFullKeyboard : public CDialogEx
{
	DECLARE_DYNAMIC(CFullKeyboard)

public:
	CFullKeyboard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFullKeyboard();

// 对话框数据
	enum { IDD = IDD_FULL_KEYBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

private:
	CBrush m_brush;
	CBrush m_btBkColor[64];
	CRect m_str123Client;
	CRect m_QWEClient;
	CRect m_ASDClient;
	CRect m_ZXCClient;
	CRect m_SPACEClient;
	CRect m_FunClient;
	CString TempString;

	CFont m_dlgFont;
	CFont m_textFont;

	HBRUSH m_Brush;
	HBRUSH m_BrushBlue;

	CWnd *str123Static;
	CWnd *qweStatic;
	CWnd *asdStatic;
	CWnd *zxcStatic;
	CWnd *spaceStatic;
	CWnd *funcStatic;
	CWnd *par;
	
	int m_keycapWidth;
	int m_keycapHeight;
	int nType;
	int m_currentState;

	KeyInfo m_strkeyInfo;

	CTypedPtrList<CPtrList, KeycapDefine*> m_num123KeysList;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_QWEKeysList;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_ASDKeysList;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_ZXCKeysList;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_SPACEKeysList;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_FuncKeysList;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_sumKeysList;//所有的按键

	CTypedPtrList<CPtrList, KeycapDefine*> m_num123KeysListSf;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_QWEKeysListSf;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_ASDKeysListSf;//
	CTypedPtrList<CPtrList, KeycapDefine*> m_ZXCKeysListSf;//

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
	CButton m_btnOK;
	CButton m_btnCancel;
	afx_msg void OnBnClickedSureButton();
	afx_msg void OnBnClickedCancelButton();
};
