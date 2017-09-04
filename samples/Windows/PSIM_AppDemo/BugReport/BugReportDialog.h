#pragma once
#include "DuiBaseWindow.h"

enum 
{
	E_NONE	= 0x0000,
	E_SEND	= 0x0001,
	E_RESART = 0x0002
};

// CBugReportDialog 对话框
class CBugReportDialog : public CDuiBaseWindow
{
public:
	CBugReportDialog();
	~CBugReportDialog();

protected:

	LPCTSTR GetWindowClassName() const;

	virtual CDuiString GetSkinFile();

	virtual void Init();
	virtual void OnFinalMessage(HWND hWnd);

	// 键盘响应;
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Caption双击事件;
	virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:

	void Notify(TNotifyUI& msg);

	void OnOK();
};