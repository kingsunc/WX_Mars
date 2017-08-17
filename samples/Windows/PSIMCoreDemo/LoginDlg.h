#pragma once
#include "afxwin.h"


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedLogin();

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
	CEdit m_edtAppName;
	CEdit m_edtAppToken;
	CEdit m_edtUserID;
	CEdit m_edtUserName;
	CEdit m_edtDeviceToken;
};
