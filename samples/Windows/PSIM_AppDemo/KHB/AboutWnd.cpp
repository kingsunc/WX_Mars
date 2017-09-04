#include "StdAfx.h"
#include "AboutWnd.h"
#include "KHBDefs.h"

CAboutWnd::CAboutWnd()
{
}

CAboutWnd::~CAboutWnd()
{
}

LPCTSTR CAboutWnd::GetWindowClassName() const
{
	return _T("CAboutWnd");
}

CDuiString CAboutWnd::GetSkinFile()
{
	return _T("wnd\\About.xml");
}

void CAboutWnd::Init()
{
	CLiveBaseWindow::Init();

	CTextUI* pName = static_cast<CTextUI*>(m_pmUI.FindControl(_T("txt_name")));
	assert(pName);
	CDuiString stName = SOFT_NAME;
	pName->SetText(stName + _T(" ") + SOFT_VERSION + _T("(") + SOFT_UPDATE + _T(")"));

	CTextUI* pComp = static_cast<CTextUI*>(m_pmUI.FindControl(_T("txt_comp")));
	assert(pComp);
	CDuiString strComp = SOFT_COMPANY;
	pComp->SetText(strComp + _T(" 版权所有"));

	CTextUI* pCopy = static_cast<CTextUI*>(m_pmUI.FindControl(_T("txt_copy")));
	assert(pCopy);
	pCopy->SetText(SOFT_COPYRIGHT);

	CButtonUI* pWeb = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_web")));
	assert(pWeb);
	pWeb->SetText(SOFT_WEB);

	return;
}

void CAboutWnd::OnFinalMessage(HWND hWnd)
{
	CLiveBaseWindow::OnFinalMessage(hWnd);
	delete this;
}

LRESULT CAboutWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		Close(IDCANCEL);
		return TRUE;
	}

	return FALSE;
}

CControlUI* CAboutWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void CAboutWnd::Notify(TNotifyUI& msg)
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
			Close(IDCANCEL);
		}
		else if (0 == strName.Compare(_T("btn_ok")))
		{
			Close(IDOK);
		}
		else if (0 == strName.Compare(_T("btn_web")))
		{
			CButtonUI* pWeb = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_web")));
			assert(pWeb);

			CDuiString strUrl = pWeb->GetText();
			// 默认浏览器打开;
			ShellExecute(NULL, NULL, strUrl, NULL, NULL, NULL);
		}
	}
}