#include "stdafx.h"
#include "LoginWnd.h"
#include "UIApp.h"
#include "resource.h"
#include "UIHelper.h"

#define LOGINWND_EDIT_NAME					_T("edt_name")
#define LOGINWND_BTN_REGISTER_NAME			_T("btn_register_name")
#define LOGINWND_EDIT_PWD					_T("edt_pwd")
#define LOGINWND_BTN_RECOVER_PWD			_T("btn_recover_pwd")
#define LOGINWND_BTN_REMEMBER_PWD			_T("btn_remember_pwd")
#define LOGINWND_BTN_AUTO_LOGIN				_T("btn_auto_login")
#define LOGINWND_BTN_LOGIN					_T("btn_login")

#define DEFAULT_PWD							_T("******")

//#define SDK_OLD
#ifdef SDK_OLD
#define SERVER_ADDRESS						_T("test.kaihuibao.cn")
#else
#define SERVER_ADDRESS						_T("video.kaihuibao.net")
#endif
#define SERVER_PORT							_T("18181")

CLoginWnd::CLoginWnd(bool bLoginOut = false) : m_iniConfig("./Config/Info.ini")
{
	m_bLoginOut = bLoginOut;
}

CLoginWnd::~CLoginWnd()
{
}

void CLoginWnd::ShowUserHeader(CDuiString strUserName)
{
	CButtonUI* pHeader = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_header")));
	assert(pHeader);
	CButtonUI* pHeader1 = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_header1")));
	assert(pHeader1);

	CDuiString strOutPath = _A2T(AflGetUIApp()->GetOutPath()).c_str();
	CDuiString strTempName = CDuiString(_T("Temp\\header_")) + strUserName + _T(".png");
	CDuiString strPath = strOutPath + _T("\\Skin\\") + strTempName;
	if (CUIApp::PathstrFileExists(_T2A(strPath.GetData())))
	{
		pHeader->SetBkImage(strTempName);
		pHeader1->SetBkImage(strTempName);
	}
	else
	{
		pHeader->SetBkImage(_T("bkg_header.png"));
		pHeader1->SetBkImage(_T("bkg_header.png"));
	}
}

LPCTSTR CLoginWnd::GetWindowClassName() const
{
	return _T("CLoginWnd");
}


CDuiString CLoginWnd::GetSkinFile()
{
	return _T("wnd\\Login.xml");
}

void CLoginWnd::Init()
{
	CLiveBaseWindow::Init();

	// 添加系统托盘图标;
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hIcon = (HICON)::LoadImage(NULL, _T(".//khb.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_nid.hWnd = GetHWND();
	_stprintf_s(m_nid.szTip, _T("%s"), SOFT_NAME);
	//m_nid.uCallbackMessage = WM_LOGIN_TRAYICON;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uID = 1000;
	Shell_NotifyIcon(NIM_ADD, &m_nid);

	CEditUI* pName = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_NAME));
	assert(pName);
	CEditUI* pPwd = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_PWD));
	assert(pPwd);
	COptionUI* pRememberPwd = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_REMEMBER_PWD));
	assert(pRememberPwd);
	COptionUI* pAutoLogin = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_AUTO_LOGIN));
	assert(pAutoLogin);

	// 载入上次的用户名密码;
	CDuiString strUserName = _A2T(m_iniConfig.GetStringVal("Name", "")).c_str();
	pName->SetText(strUserName.GetData());

	ShowUserHeader(strUserName);

	bool bAutoLogin = m_iniConfig.GetIntVal("AutoLogin", 0) ? true : false;
	bool bRemember = m_iniConfig.GetIntVal("Remember", 0) ? true : false;
	if (bAutoLogin)
	{
		bRemember = true;
	}
	pRememberPwd->Selected(bRemember);
	pAutoLogin->Selected(bAutoLogin);
	if (bRemember)
	{
		CDuiString strUserPwd = _A2T(m_iniConfig.GetStringVal("Pwd", "")).c_str();
		pPwd->SetText(strUserPwd);
		/*if (!strUserPwd.IsEmpty())
		{
			pPwd->SetText(DEFAULT_PWD);
		}*/
	}
	// 解决大写Caps时，设置密码框焦点必须手动设置;
	pPwd->SetPasswordMode(true);

	if ((!m_bLoginOut) && bAutoLogin)
	{
		// 非注销状态 且 记住密码;
		OnLogin();
	}
}

void CLoginWnd::OnFinalMessage(HWND hWnd)
{
	CLiveBaseWindow::OnFinalMessage(hWnd);
	delete this;
	AflGetUIHelper()->m_pLoginWnd = NULL;
}

LRESULT CLoginWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		OnLogin();
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		OnCloseClicked();
	}

	return FALSE;
}

LRESULT CLoginWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//switch (uMsg)
	//{
	//case WM_SERVERCONNECT_FAIL:
	//	{
	//		char* pFailed = reinterpret_cast<char*>(wParam);
	//		LOG_ERROR(pFailed);
	//		AflMessageBox(m_hWnd, _T("网络故障"));

	//		CTabLayoutUI *pTab = static_cast<CTabLayoutUI*>(m_pmUI.FindControl(_T("tab_login_area")));
	//		assert(pTab);
	//		pTab->SelectItem(0);
	//	}
	//	break;
	//case WM_SERVERCONNECT_RESULT:
	//	{
	//		int nResult = static_cast<int>(wParam);
	//		switch (nResult)
	//		{
	//		case ERR_NOERROR:
	//			{
	//				LOG_INFO("OnServerConnectResult: ERR_NOERROR");
	//				return 0;
	//			}
	//			break;
	//		case ERR_SERVER_CONNFAIL:
	//			{
	//				LOG_ERROR("OnServerConnectResult: ERR_SERVER_CONNFAIL");
	//				AflMessageBox(m_hWnd, _T("错误的地址端口或服务器未启动"));
	//			}
	//			break;
	//		case ERR_SERVER_AUTHFAIL:
	//			{
	//				LOG_ERROR("OnServerConnectResult: ERR_SERVER_AUTHFAIL");
	//				AflMessageBox(m_hWnd, _T("信令协议版本不匹配"));
	//			}
	//			break;
	//		default:
	//			{
	//				LOG_ERROR("OnServerConnectResult: UNKNOWN");
	//				AflMessageBox(m_hWnd, _T("未知错误"));
	//			}
	//			break;
	//		}
	//		CTabLayoutUI *pTab = static_cast<CTabLayoutUI*>(m_pmUI.FindControl(_T("tab_login_area")));
	//		assert(pTab);
	//		pTab->SelectItem(0);
	//	}
	//	break;
	//case WM_LOGIN_RESULT:
	//	{
	//		int nResult = static_cast<int>(wParam);
	//		switch (nResult)
	//		{
	//		case ERR_NOERROR:
	//			{
	//				LOG_INFO("WM_LOGIN_RESULT: ERR_NOERROR");
	//				return 0;
	//			}
	//			break;
	//		case ERR_INVALID_PASSWORD:
	//			{
	//				LOG_ERROR("WM_LOGIN_RESULT: ERR_INVALID_PASSWORD");
	//				AflMessageBox(m_hWnd, _T("账号密码错误"));
	//			}
	//			break;
	//		case ERR_CONF_LOCKDOG_NORESOURCE:
	//			{
	//				LOG_ERROR("WM_LOGIN_RESULT: ERR_CONF_LOCKDOG_NORESOURCE");
	//				AflMessageBox(m_hWnd, _T("服务器或会议授权数不足"));
	//			}
	//			break;
	//		default:
	//			{
	//				LOG_ERROR("WM_LOGIN_RESULT: UNKNOWN");
	//				AflMessageBox(m_hWnd, _T("未知错误"));
	//			}
	//			break;
	//		}

	//		CTabLayoutUI *pTab = static_cast<CTabLayoutUI*>(m_pmUI.FindControl(_T("tab_login_area")));
	//		assert(pTab);
	//		pTab->SelectItem(0);
	//	}
	//	break;
	//case WM_CONFLIST_REPORT:
	//	{
	//		CEditUI* pName = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_NAME));
	//		assert(pName);
	//		CEditUI* pPwd = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_PWD));
	//		assert(pPwd);
	//		COptionUI* pRememberPwd = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_REMEMBER_PWD));
	//		assert(pRememberPwd);
	//		COptionUI* pAutoLogin = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_AUTO_LOGIN));
	//		assert(pAutoLogin);
	//	
	//		CDuiString strName = pName->GetText();
	//		CDuiString strPwd = pPwd->GetText();
	//		int iAutoLogin = pAutoLogin->IsSelected() ? 1 : 0;
	//		int iRemember = pRememberPwd->IsSelected() ? 1 : 0;

	//		m_iniConfig.SetStringVal("Name", _T2A(strName.GetData()));
	//		m_iniConfig.SetStringVal("Pwd", _T2A(strPwd.GetData()));
	//		m_iniConfig.SetIntVal("AutoLogin", iAutoLogin);
	//		m_iniConfig.SetIntVal("Remember", iRemember);
	//		m_iniConfig.SavedFile();
	//		
	//		// 已获取到会议列表，关闭对话框;
	//		Close(IDOK);
	//	}
	//	break;
	//default:
	//	break;
	//}

	return CLiveBaseWindow::HandleMessage(uMsg, wParam, lParam);
}

void CLoginWnd::Notify(TNotifyUI& msg)
{
	CDuiString strType = msg.sType;
	CDuiString strName = msg.pSender->GetName();
	if (0 == strType.Compare(_T("windowinit")))
	{
		//OnPrepare(msg);
	}
	else if (0 == strType.Compare(DUI_MSGTYPE_TEXTCHANGED))
	{
		if (0 == strName.Compare(LOGINWND_EDIT_NAME))
		{
			OnNameChanged();
		}
	}
	else if (0 == strType.Compare(DUI_MSGTYPE_CLICK))
	{
		if (0 == strName.Compare(_T("btn_close")))
		{
			OnCloseClicked();
		}
		else if (0 == strName.Compare(_T("btn_min")))
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (0 == strName.Compare(LOGINWND_BTN_REGISTER_NAME))
		{
			OnRegistAccount();
		}
		else if (0 == strName.Compare(LOGINWND_BTN_RECOVER_PWD))
		{
			OnRecoverPwd();
		}
		else if (0 == strName.Compare(LOGINWND_BTN_REMEMBER_PWD))
		{
			OnRememberPwd();
		}
		else if (0 == strName.Compare(LOGINWND_BTN_AUTO_LOGIN))
		{
			OnAutoLogin();
		}
		else if (0 == strName.Compare(LOGINWND_BTN_LOGIN))
		{
			OnLogin();
		}
	}
}

void CLoginWnd::OnNameChanged()
{
	// 若账号变更: 清空密码,取消勾选;
	CEditUI* pName = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_NAME));
	assert(pName);
	CEditUI* pPwd = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_PWD));
	assert(pPwd);
	pPwd->SetText(_T(""));
	COptionUI* pRememberPwd = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_REMEMBER_PWD));
	assert(pRememberPwd);
	pRememberPwd->Selected(false);
	COptionUI* pAutoLogin = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_AUTO_LOGIN));
	assert(pAutoLogin);
	pAutoLogin->Selected(false);

	ShowUserHeader(pName->GetText().GetData());
}

// 登陆响应;
void CLoginWnd::OnLogin()
{
	// 控件失效;
	CTabLayoutUI *pTab = static_cast<CTabLayoutUI*>(m_pmUI.FindControl(_T("tab_login_area")));
	assert(pTab);

	try
	{
		CDuiString strError;
		// 用户名;
		CEditUI* pUIName = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_NAME));
		assert(pUIName);
		CDuiString strName = (pUIName->GetText()).GetData();
		if (strName.IsEmpty())
		{
			strError = _T("用户名不能为空!");
			throw strError;
		}

		// 密码;
		CEditUI * pUIPwd = static_cast<CEditUI*>(m_pmUI.FindControl(LOGINWND_EDIT_PWD));
		assert(pUIPwd);
		CDuiString strPwd = (pUIPwd->GetText()).GetData();
		if (strPwd.IsEmpty())
		{
			strError = _T("用户密码不能为空!");
			throw strError;
		}
		else
		{
			if (0 == strPwd.Compare(DEFAULT_PWD))
			{
				// 若为默认密码，则从注册表读取md5数值;
				strPwd = _A2T(m_iniConfig.GetStringVal("Pwd", "")).c_str();
			}
		}

		// 当焦点在Edit内部时显示有bug 故要切换焦点;
		pTab->SelectItem(1);

#if 1
		//AflGetXCore()->SetServerAddress(SERVER_ADDRESS);
		//AflGetXCore()->SetServerPort(SERVER_PORT);
		//AflGetXCore()->UserLogin(strName.GetData(), strPwd.GetData());
#else
		CUrlString strCmd;
		TString strUrl = APP_SERVER_URL;
		strUrl.append(_T("/api/account/login2/static/"));
		strCmd.SetUrl(strUrl);
		strCmd.AddPara(_T("kind"), 1);
		strCmd.AddPara(_T("mobile"), _T("13800000000"));
		strCmd.AddPara(_T("password"), _T("123456"));

		CmdItem cmdItem;
		cmdItem.cmdInfo.strUrl = strCmd.GetUrlString();
		cmdItem.cmdInfo.strPara = strCmd.GetParaString();
		cmdItem.cmdInfo.hCallBackWnd = m_hWnd;
		cmdItem.pFunc = CLoginWnd::Login_CallBack;
		AflGetCmdManager()->AddCmd(cmdItem);
#endif
	}
	catch (CDuiString str)
	{
		pTab->SelectItem(0);
		AflMessageBox(m_hWnd, str);
		LOG_ERROR(str);
		return;
	}
	catch (...)
	{
		pTab->SelectItem(0);
		CDuiString strError = _T("登录请求出现未知错误！");
		AflMessageBox(m_hWnd, strError);
		LOG_FATAL(strError);
		return;
	}
}

void CLoginWnd::OnRegistAccount()
{
	std::string strRegisterURL = AflGetUIApp()->GetProFileString("RegisterURL");
	ShellExecute(0, NULL, _A2T(strRegisterURL).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
}

void CLoginWnd::OnRecoverPwd()
{
	std::string strForgotPasswordURL = AflGetUIApp()->GetProFileString("ForgotPasswordURL");
	ShellExecute(0, NULL, _A2T(strForgotPasswordURL).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
}

void CLoginWnd::OnRememberPwd()
{
	COptionUI* pRemKey = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_REMEMBER_PWD));
	if ((NULL != pRemKey) && (pRemKey->IsSelected()))
	{
		COptionUI* pAutoLogin = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_AUTO_LOGIN));
		if ((NULL != pAutoLogin) && (pAutoLogin->IsSelected()))
		{
			pAutoLogin->Selected(false);
		}
	}
}

void CLoginWnd::OnAutoLogin()
{
	COptionUI* pAutoLogin = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_AUTO_LOGIN));
	if ((NULL != pAutoLogin) && (!pAutoLogin->IsSelected()))
	{
		COptionUI* pRemKey = static_cast<COptionUI*>(m_pmUI.FindControl(LOGINWND_BTN_REMEMBER_PWD));
		if ((NULL != pRemKey) && (!pRemKey->IsSelected()))
		{
			pRemKey->Selected(true);
		}
	}
}

LRESULT CLoginWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 删除系统托盘图标;
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	return CLiveBaseWindow::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT CLoginWnd::OnLoginTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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

void CLoginWnd::OnCloseClicked()
{
	exit(0);
}

void CLoginWnd::Login_CallBack(CmdInfo& cmdInfo)
{
#ifdef _DEBUG
	const std::string strResult = cmdInfo.jsResult.toStyledString();
#endif // DEBUG

	if (!cmdInfo.bSucess)
	{
		//::SendMessage(cmdInfo.hCallBackWnd, WM_LOGIN_IN, false, (LPARAM)(cmdInfo.strError.c_str()));
		return;
	}

	// 成功;
	//CUserManage::GetInstance()->SetUser(cmdInfo.jsResult);
}