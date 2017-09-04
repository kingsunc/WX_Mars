#include "stdafx.h"
#include "UpdateDialog.h"

CUpdateDialog::CUpdateDialog()
{
}

CUpdateDialog::~CUpdateDialog()
{
}

LPCTSTR CUpdateDialog::GetWindowClassName() const
{
	return _T("CUpdateDialog");
}


CDuiString CUpdateDialog::GetSkinFile()
{
	return _T("Update.xml");
}

void CUpdateDialog::Init()
{
	CDuiBaseWindow::Init();
}

void CUpdateDialog::OnFinalMessage(HWND hWnd)
{
	CDuiBaseWindow::OnFinalMessage(hWnd);
	delete this;
}

LRESULT CUpdateDialog::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		// Close(IDCANCEL);
		return TRUE;
	}

	return FALSE;
}

LRESULT CUpdateDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//switch (uMsg)
	//{
	//default:
	//	break;
	//}
	return CDuiBaseWindow::HandleMessage(uMsg, wParam, lParam);
}

void CUpdateDialog::Notify(TNotifyUI& msg)
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
		else if (0 == strName.Compare(_T("btn_min")))
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		if (0 == strName.Compare(_T("btn_ok")))
		{
			Close(IDOK);
		}
	}
}

LRESULT CUpdateDialog::OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;	// ÆÁ±ÎË«»÷×î´ó»¯;
	return 0;
}