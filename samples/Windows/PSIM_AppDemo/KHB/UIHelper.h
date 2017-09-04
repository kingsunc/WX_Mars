#pragma once
#include <wtypes.h>
#include "TSingleton.h"
#include "KHBDefs.h"
#include "LoginWnd.h"
#include "MainWnd.h"

class CUIHelper : public TSingleton<CUIHelper>
{
public:
	CUIHelper();
	~CUIHelper();

	// 登录;
	UINT ShowLoginWnd(bool bLoginOut = false);
	HWND GetLoginHWND();

	// 主界面;
	UINT ShowMainWnd();
	HWND GetMainHWND();

	// 关于;
	UINT ShowAboutWnd();

public:
	CLoginWnd*			m_pLoginWnd;
	CMainWnd*			m_pMainWnd;
};

#define AflGetUIHelper		CUIHelper::GetInstance