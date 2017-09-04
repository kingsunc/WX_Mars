#pragma once
#include "DuiBaseWindow.h"

// CUpdateDialog 对话框
class CUpdateDialog : public CDuiBaseWindow
{
public:
	CUpdateDialog();
	~CUpdateDialog();

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
};