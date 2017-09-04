#include "stdafx.h"
#include "MainWnd.h"
#include "UIApp.h"
#include "UIHelper.h"
#include "Data.h"
#include "ConferenceItemUI.h"

CMainWnd::CMainWnd()
{
	m_pSetMenu = NULL;
}

CMainWnd::~CMainWnd()
{
	if (NULL != m_pSetMenu)
	{
		delete m_pSetMenu;
		m_pSetMenu = NULL;
	}
}

LPCTSTR CMainWnd::GetWindowClassName() const
{
	return _T("MainWnd");
}


CDuiString CMainWnd::GetSkinFile()
{
	return _T("wnd\\Main.xml");
}

void CMainWnd::Init()
{
	CLiveBaseWindow::Init();

	// 添加系统托盘图标;
	/*m_iNotifyID.cbSize = sizeof(NOTIFYICONDATA);
	m_iNotifyID.hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_iNotifyID.hWnd = m_hWnd;
	_stprintf_s(m_iNotifyID.szTip, _T("%s"), EASYLIVE_NAME);
	m_iNotifyID.uCallbackMessage = WM_MAIN_TRAYICON;
	m_iNotifyID.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_iNotifyID.uID = 1000;
	Shell_NotifyIcon(NIM_ADD, &m_iNotifyID);*/

	ShowUserInfo();
}

void CMainWnd::OnFinalMessage(HWND hWnd)
{
	CLiveBaseWindow::OnFinalMessage(hWnd);
	delete this;

	::PostQuitMessage(0);
}

void CMainWnd::Notify(TNotifyUI& msg)
{
	CDuiString strType = msg.sType;
	CDuiString strName = msg.pSender->GetName();
	if (0 == strType.Compare(_T("windowinit")))
	{
		//OnPrepare(msg);
	}
	else if (0 == strType.Compare(DUI_MSGTYPE_CLICK))
	{
		if (0 == strName.Compare(_T("btn_close")))
		{
			OnCloseClicked();
		}
		else if (0 == strName.Compare(_T("btn_set")))
		{
			OnSetMenuClicked();
		}
		else if (0 == strName.Compare(_T("btn_watchlive")))
		{
			// 跳转观看网站;
			//OnWatchLiveClicked();
		}
		else if (0 == strName.Compare(_T("btn_skin")))
		{
			//new CSkinFrame(m_hWnd, msg.pSender);
		}
		else if (0 == strName.Compare(_T("btn_min")))
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (0 == strName.Compare(_T("btn_max")))
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		else if (0 == strName.Compare(_T("btn_restore")))
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		}
	}
	else if (0 == strType.Compare(DUI_MSGTYPE_SELECTCHANGED))
	{
	}
}

void CMainWnd::OnCloseClicked()
{
	exit(0);
}

LRESULT CMainWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND;
	if (wParam == SC_CLOSE)
	{
		OnCloseClicked();
		bHandled = TRUE;
		return 0;
	}

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 删除系统托盘图标;
	Shell_NotifyIcon(NIM_DELETE, &m_iNotifyID);

	return CLiveBaseWindow::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT CMainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*switch (uMsg)
	{
	default:
		break;
	}*/

	return CLiveBaseWindow::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainWnd::OnClickMenuItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MenuCmd* pMenuCmd = reinterpret_cast<MenuCmd*>(wParam);
	if (NULL != pMenuCmd)
	{
		BOOL bChecked = pMenuCmd->bChecked;
		CDuiString strMenuName = pMenuCmd->szName;
		CDuiString strUserData = pMenuCmd->szUserData;
		CDuiString strText = pMenuCmd->szText;
		m_pmUI.DeletePtr(pMenuCmd);
		if (NULL != m_pSetMenu)
		{
			delete m_pSetMenu;
			m_pSetMenu = NULL;
		}

		if (0 == strMenuName.CompareNoCase(_T("item_myinfo")))
		{
			OnMenuMyInfo();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_update")))
		{
			OnMenuUpdate();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_instructions")))
		{
			OnMenuInstructions();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_feedback")))
		{
			OnMenuFeedBack();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_home")))
		{
			OnMenuHome();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_about")))
		{
			OnMenuAbout();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_changed")))
		{
			OnMenuChanged();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_logout")))
		{
			OnMenuLogout();
		}
		else if (0 == strMenuName.CompareNoCase(_T("item_exit")))
		{
			OnMenuExit();
		}
	}

	return 0;
}

LRESULT CMainWnd::OnMainTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!IsWindowVisible())
	{
		return 0;
	}

	switch (lParam)
	{
	case WM_RBUTTONUP:
		{
			//LPPOINT lpoint = new tagPOINT;
			//::GetCursorPos(lpoint);//得到鼠标位置 
			//CMenu menu;
			//menu.CreatePopupMenu();//声明一个弹出式菜单 
			////增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。 
			//menu.AppendMenu(MF_STRING, WM_DESTROY, "关闭"); //确定弹出式菜单的位置 
			//menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); //资源回收 
			//HMENU hmenu = menu.Detach();
			//menu.DestroyMenu();
			//delete lpoint;
		}
		break;
	case WM_LBUTTONUP:
		{
			ShowWindow(true);
			SetForegroundWindow(m_hWnd);
		}
		break;
	default: break;
	}
	return 0;
}

void CMainWnd::ShowUserInfo()
{
	//CUser *pUser = AflGetUserInfo();
	//assert(pUser);

	CButtonUI* pHeader = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_header")));
	assert(pHeader);
	pHeader->SetBkImage(_T("image/bkg_header.png"));

	CEditUI* pNickNameUI = static_cast<CEditUI*>(m_pmUI.FindControl(_T("lab_nickname")));
	assert(pNickNameUI);

	std::wstring strUserID = fmt::format(_T("{}"), AflGetData()->GetUserInfo()->m_iUserID);
	pNickNameUI->SetText(strUserID.c_str());
}

void CMainWnd::OnSetMenuClicked()
{
	if (m_pSetMenu != NULL)
	{
		delete m_pSetMenu;
		m_pSetMenu = NULL;
	}
	m_pSetMenu = new CMenuWnd();
	CDuiPoint point;
	::GetCursorPos(&point);

	m_pSetMenu->Init(NULL, _T("menu\\SetMenu.xml"), point, &m_pmUI);
}

// 我的资料;
void CMainWnd::OnMenuMyInfo()
{
	std::string strMyInfoURL = AflGetUIApp()->GetProFileString("MyInfoURL");
	ShellExecute(0, NULL, _A2T(strMyInfoURL).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
}

// 检查更新;
void CMainWnd::OnMenuUpdate()
{
	ShellExecute(0, NULL, _T("SoftUpdate.exe"), _T(""), _T(""), SW_SHOWNORMAL);
}

// 使用说明;
void CMainWnd::OnMenuInstructions()
{
	std::string strInstructionsURL = AflGetUIApp()->GetProFileString("InstructionsURL");
	ShellExecute(0, NULL, _A2T(strInstructionsURL).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
}

// 用户反馈;
void CMainWnd::OnMenuFeedBack()
{
	//AflGetUIHelper()->ShowFeedBackWnd();
}

// 开会宝官网;
void CMainWnd::OnMenuHome()
{
	std::string strHomeURL = AflGetUIApp()->GetProFileString("HomeURL");
	ShellExecute(0, NULL, _A2T(strHomeURL).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
}

// 关于开会宝;
void CMainWnd::OnMenuAbout()
{
	AflGetUIHelper()->ShowAboutWnd();
}

// 更换账号;
void CMainWnd::OnMenuChanged()
{
	Close(IDCANCEL);
}

// 注销;
void CMainWnd::OnMenuLogout()
{
	Close(IDCANCEL);
}

// 退出;
void CMainWnd::OnMenuExit()
{
	exit(0);
}