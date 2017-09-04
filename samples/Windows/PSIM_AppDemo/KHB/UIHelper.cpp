#include "UIHelper.h"
#include "AboutWnd.h"

CUIHelper::CUIHelper()
{
	m_pLoginWnd = NULL;
	m_pMainWnd = NULL;
}

CUIHelper::~CUIHelper()
{
}

UINT CUIHelper::ShowLoginWnd(bool bLoginOut)
{
	HWND hParent = ::GetDesktopWindow();
	CDuiString strTitle = SOFT_NAME;
	m_pLoginWnd = new CLoginWnd(bLoginOut);
	assert(m_pLoginWnd);
	m_pLoginWnd->Create(hParent, strTitle + _T("µÇÂ¼"), UI_WNDSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 0, 0);
	m_pLoginWnd->CenterWindow();
	UINT uiRet = m_pLoginWnd->ShowModal();
	return uiRet;
}

HWND CUIHelper::GetLoginHWND()
{
	if (m_pLoginWnd)
	{
		return m_pLoginWnd->GetHWND();
	}

	return NULL;
}


UINT CUIHelper::ShowMainWnd()
{
	HWND hParent = ::GetDesktopWindow();
	CDuiString strTitle = SOFT_NAME;
	m_pMainWnd = new CMainWnd();
	assert(m_pMainWnd);
	m_pMainWnd->Create(hParent, strTitle, UI_WNDSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 0, 0);
	m_pMainWnd->CenterWindow();
	CDuiBaseWindow::SetMainHwnd(m_pMainWnd->GetHWND());
	CPaintManagerUI::MessageLoop();

	m_pMainWnd = NULL;
	return 1;
}

HWND CUIHelper::GetMainHWND()
{
	if (m_pMainWnd)
	{
		return m_pMainWnd->GetHWND();
	}

	return NULL;
}

UINT CUIHelper::ShowAboutWnd()
{
	HWND hParent = ::GetDesktopWindow();
	if (m_pMainWnd)
	{
		hParent = m_pMainWnd->GetHWND();
	}
	CDuiString strTitle = _T("¹ØÓÚ");
	strTitle += SOFT_NAME;
	CAboutWnd* pAbout = new CAboutWnd();
	assert(pAbout);
	pAbout->Create(hParent, strTitle + _T("µÇÂ¼"), UI_WNDSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 0, 0);
	pAbout->CenterWindow();
	UINT uiRet = pAbout->ShowModal();
	return uiRet;
}
