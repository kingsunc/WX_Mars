#pragma once
#include "LiveBaseWindow.h"

// CMainWnd 对话框;
class CMainWnd : public CLiveBaseWindow
{
public:
	CMainWnd();
	~CMainWnd();

protected:
	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();

	virtual void Init();
	virtual void OnFinalMessage(HWND hWnd);

	//virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnClickMenuItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	// 键盘响应;
	//virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	// 显示用户信息;
	void ShowUserInfo();

	void OnCloseClicked();

	void Notify(TNotifyUI& msg);

	// 菜单响应;
	void OnMenuMyInfo();		// 我的资料;
	void OnMenuUpdate();		// 检查更新;
	void OnMenuInstructions();	// 使用说明;
	void OnMenuFeedBack();		// 用户反馈;
	void OnMenuHome();			// 开会宝官网;
	void OnMenuAbout();			// 关于开会宝;
	void OnMenuChanged();		// 更换账号;
	void OnMenuLogout();		// 注销;
	void OnMenuExit();			// 退出;

	void OnSetMenuClicked();	

private:
	LRESULT OnMainTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam);

	NOTIFYICONDATA	m_iNotifyID;	// 系统托盘;
	CMenuWnd*		m_pSetMenu;		// 设置菜单;
};