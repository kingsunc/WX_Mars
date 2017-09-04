#include "stdafx.h"
#include "BugReportDialog.h"
#include "Resource.h"

CBugReportDialog::CBugReportDialog()
{
}

CBugReportDialog::~CBugReportDialog()
{
}

LPCTSTR CBugReportDialog::GetWindowClassName() const
{
	return _T("CBugReportDialog");
}


CDuiString CBugReportDialog::GetSkinFile()
{
	return _T("BugReport.xml");
}

void CBugReportDialog::Init()
{
	CDuiBaseWindow::Init();
	SetIcon(IDI_BUGREPORT_ICON);
}

void CBugReportDialog::OnFinalMessage(HWND hWnd)
{
	CDuiBaseWindow::OnFinalMessage(hWnd);
	delete this;
}

LRESULT CBugReportDialog::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}

	return FALSE;
}

LRESULT CBugReportDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDuiBaseWindow::HandleMessage(uMsg, wParam, lParam);
}

void CBugReportDialog::Notify(TNotifyUI& msg)
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
			Close(E_NONE);
		}
		else if (0 == strName.Compare(_T("btn_min")))
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		if (0 == strName.Compare(_T("btn_ok")))
		{
			OnOK();
		}
	}
}

LRESULT CBugReportDialog::OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;	// ÆÁ±ÎË«»÷×î´ó»¯;
	return 0;
}

void CBugReportDialog::OnOK()
{
	int iResult = E_NONE;
	COptionUI* pSend = static_cast<COptionUI*>(m_pmUI.FindControl(_T("btn_send_report")));
	assert(pSend);
	bool bSend = pSend->IsSelected();
	if (bSend)
	{
		iResult |= E_SEND;
	} 
	COptionUI* pReStart = static_cast<COptionUI*>(m_pmUI.FindControl(_T("btn_restart")));
	assert(pReStart);
	bool bReStart = pReStart->IsSelected();
	if (bReStart)
	{
		iResult |= E_RESART;
	}
	Close(iResult);
}