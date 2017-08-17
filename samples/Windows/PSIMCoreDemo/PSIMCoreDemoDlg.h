
// PSIMCoreDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPSIMCoreDemoDlg 对话框
class CPSIMCoreDemoDlg : public CDialogEx
{
// 构造
public:
	CPSIMCoreDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PSIMCOREDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonSend();

	void AppendInfo(CString strInfo);

public:
	CEdit m_edtFrom;
	CEdit m_edtTo;
	CEdit m_edtContent;
	CRichEditCtrl m_edtInfo;
};
