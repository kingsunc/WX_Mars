#pragma once
#include "LiveBaseWindow.h"
#include "IniConfig.h"
#include "CmdInfo.h"

// CLoginWnd 对话框
class CLoginWnd : public CLiveBaseWindow
{
public:
	CLoginWnd(bool bLoginOut);
	~CLoginWnd();

protected:
	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();

	virtual void Init();
	virtual void OnFinalMessage(HWND hWnd);

	// 键盘响应;
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnLoginTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Notify(TNotifyUI& msg);

	void OnNameChanged();	// 账号变更;
	void OnRegistAccount();	// 注册账号;
	void OnRecoverPwd();	// 找回密码;
	void OnRememberPwd();	// 记住密码;
	void OnAutoLogin();		// 自动登录;
	void OnLogin();			// 登陆响应;

	void ShowUserHeader(CDuiString strUserName);

	void OnCloseClicked();

	static void Login_CallBack(CmdInfo& cmdInfo);

private:

	NOTIFYICONDATA	m_nid;			// 系统托盘相关;
	CIniConfig		m_iniConfig;	// 文件配置;
	bool			m_bLoginOut;	// 是否注销;
};