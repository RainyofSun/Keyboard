#pragma once
#include "KeyboardConfig.h"
#include "afxwin.h"

// CStringKeyboard �Ի���

class CStringKeyboard : public CDialogEx
{
	DECLARE_DYNAMIC(CStringKeyboard)

public:
	CStringKeyboard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStringKeyboard();

// �Ի�������
	enum { IDD = IDD_STRING_KEYBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

private:
	CBrush m_brush;
	HBRUSH m_Brush;
	CBrush m_btBkColor[64];

	CRect m_strClient;
	CRect m_funcClient;

	CString m_tempString;

	CFont m_dlgFont;
	CFont m_textFont;

	int m_currentState;
	int m_keycapWidth;
	int m_keycapHeight;
	int ntype;

	CWnd *strStatic;
	CWnd *funcStatic;
	CWnd *par;

	KeyInfo m_stringkeyInfo;

	CTypedPtrList<CPtrList,KeycapDefine*> m_numKeysList;//���ֻ�����ĸ
	CTypedPtrList<CPtrList,KeycapDefine*> m_ABCKeysList;//���ֻ�����ĸ
	CTypedPtrList<CPtrList,KeycapDefine*> m_abcKeysList;//���ֻ�����ĸ
	CTypedPtrList<CPtrList,KeycapDefine*> m_funcKeysList;//���ܼ�
	CTypedPtrList<CPtrList,KeycapDefine*> m_sumKeysList;//���еİ���

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
	CEdit m_ctlNewValueEdit;
};
