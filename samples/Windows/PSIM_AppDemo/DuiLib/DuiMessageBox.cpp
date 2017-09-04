#include "stdafx.h"
#include "DuiMessageBox.h"

namespace DuiLib
{
	CDuiMessageBox::CDuiMessageBox()
	{
	}

	CDuiMessageBox::~CDuiMessageBox()
	{
	}

	LPCTSTR CDuiMessageBox::GetWindowClassName() const
	{
		return _T("CDuiMessageBox");
	}

	CDuiString CDuiMessageBox::GetSkinFile()
	{
		return _T("wnd\\MessageBox.xml");
	}

	void CDuiMessageBox::Init()
	{
		CDuiBaseWindow::Init();
	}

	void CDuiMessageBox::OnFinalMessage(HWND hWnd)
	{
		CDuiBaseWindow::OnFinalMessage(hWnd);
		delete this;
	}

	LRESULT CDuiMessageBox::ResponseDefaultKeyEvent(WPARAM wParam)
	{
		if (wParam == VK_RETURN)
		{
			CButtonUI* pBtn1 = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_box1")));
			if (NULL == pBtn1)
			{
				//LOG_ERROR(_T("pBtn1 Is NULL"));
				return FALSE;
			}
			CButtonUI* pBtn2 = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_box2")));
			if (NULL == pBtn2)
			{
				//LOG_ERROR(_T("pBtn2 Is NULL"));
				return FALSE;
			}
			CButtonUI* pBtn3 = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_box3")));
			if (NULL == pBtn3)
			{
				//LOG_ERROR(_T("pBtn3 Is NULL"));
				return FALSE;
			}

			CDuiString strText1 = pBtn1->GetText();
			if (!strText1.IsEmpty())
			{
				CloseMessageBox(strText1);
				return TRUE;
			}
			else
			{
				CDuiString strText2 = pBtn2->GetText();
				if (!strText2.IsEmpty())
				{
					CloseMessageBox(strText2);
					return TRUE;
				}
				else
				{
					CDuiString strText3 = pBtn3->GetText();
					if (!strText3.IsEmpty())
					{
						CloseMessageBox(strText3);
						return TRUE;
					}
				}
			}
		}
		else if (wParam == VK_ESCAPE)
		{
			Close(IDCANCEL);
			return TRUE;
		}

		return FALSE;
	}

	CControlUI* CDuiMessageBox::CreateControl(LPCTSTR pstrClass)
	{
		return NULL;
	}

	void CDuiMessageBox::Notify(TNotifyUI& msg)
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
			else if (0 == strName.Compare(_T("btn_box1")))
			{
				CDuiString strText = msg.pSender->GetText();
				CloseMessageBox(strText);
			}
			else if (0 == strName.Compare(_T("btn_box2")))
			{
				CDuiString strText = msg.pSender->GetText();
				CloseMessageBox(strText);
			}
			else if (0 == strName.Compare(_T("btn_box3")))
			{
				CDuiString strText = msg.pSender->GetText();
				CloseMessageBox(strText);
			}
		}
	}

	LRESULT CDuiMessageBox::OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;	// 屏蔽双击最大化;
		return 0;
	}

	void CDuiMessageBox::SetBoxTex(CDuiString strtBoxText)
	{
		CTextUI* pText = static_cast<CTextUI*>(m_pmUI.FindControl(_T("txt_text")));
		if (NULL != pText)
		{
			pText->SetText(strtBoxText);
		}
	}

	void CDuiMessageBox::SetBoxCaption(CDuiString strtBoxCaption)
	{
		CTextUI* pCaption = static_cast<CTextUI*>(m_pmUI.FindControl(_T("txt_caption")));
		if (NULL != pCaption)
		{
			pCaption->SetText(strtBoxCaption);
		}
	}

	void CDuiMessageBox::SetBoxType(UINT uBoxType)
	{
		// 设置图标;
		CLabelUI* pIcon = static_cast<CLabelUI*>(m_pmUI.FindControl(_T("lab_icon")));
		if (NULL == pIcon)
		{
			//LOG_ERROR(_T("pIcon Is NULL"));
			return;
		}
		/*if (uBoxType & MB_ICONERROR)
		{
			pIcon->SetBkImage(_T("mb_iconerror.png"));
		}
		else if ( uBoxType & MB_ICONQUESTION)
		{
			pIcon->SetBkImage(_T("mb_iconquestion.png"));
		}
		else*/
		{
			// MB_ICONWARNING
			pIcon->SetBkImage(_T("mb_iconwaring.png"));
		}

		// 设置按钮;
		CButtonUI* pBtn1 = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_box1")));
		if (NULL == pBtn1)
		{
			//LOG_ERROR(_T("pBtn1 Is NULL"));
			return;
		}
		CButtonUI* pBtn2 = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_box2")));
		if (NULL == pBtn2)
		{
			//LOG_ERROR(_T("pBtn2 Is NULL"));
			return;
		}
		CButtonUI* pBtn3 = static_cast<CButtonUI*>(m_pmUI.FindControl(_T("btn_box3")));
		if (NULL == pBtn3)
		{
			//LOG_ERROR(_T("pBtn3 Is NULL"));
			return;
		}
		if (uBoxType & MB_OKCANCEL)
		{
			pBtn1->SetVisible(false);
			pBtn2->SetText(_T("确定"));
			pBtn3->SetText(_T("取消"));
		}
		else if (uBoxType & MB_YESNO)
		{
			pBtn1->SetVisible(false);
			pBtn2->SetText(_T("是"));
			pBtn3->SetText(_T("否"));
		}
		else if (uBoxType & MB_YESNOCANCEL)
		{
			pBtn1->SetText(_T("是"));
			pBtn2->SetText(_T("否"));
			pBtn3->SetText(_T("取消"));
		}
		else
		{
			// MB_OK
			pBtn1->SetVisible(false);
			pBtn2->SetVisible(false);
			pBtn3->SetText(_T("确定"));
		}
	}

	void CDuiMessageBox::CloseMessageBox(CDuiString strText)
	{
		if (strText.IsEmpty())
		{
			return;
		}

		if (0 == strText.Compare(_T("是")))
		{
			return Close(IDYES);
		}
		else if (0 == strText.Compare(_T("否")))
		{
			return Close(IDNO);
		}
		else if (0 == strText.Compare(_T("确定")))
		{
			return Close(IDOK);
		}
		else if (0 == strText.Compare(_T("取消")))
		{
			return Close(IDCANCEL);
		}
	}

	int  CDuiMessageBox::DuiMessageBox(HWND hParentWnd /*= NULL*/,
		LPCTSTR lpText /*= _T("")*/,
		LPCTSTR lpCaption /*= _T("提示")*/,
		UINT uType /*= MB_OK | MB_ICONINFORMATION */)
	{
		CDuiString strTemp = _T("");
		if (0 == strTemp.Compare(lpText))
		{
			return 0;
		}

		if (NULL == hParentWnd)
		{
			hParentWnd = ::GetActiveWindow();
		}
		if ((NULL != hParentWnd) && (!::IsWindowVisible(hParentWnd)))
		{
			return 0;
		}

		CDuiMessageBox* pBox = new CDuiMessageBox();
		if (pBox == NULL)
		{
			return 0;
		}

		// 需设置父窗口,使模态效果有效;
		pBox->Create(hParentWnd, lpCaption, UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE, 0, 0, 340, 160);
		pBox->SetBoxTex(lpText);
		pBox->SetBoxCaption(lpCaption);
		pBox->SetBoxType(uType);
		pBox->CenterWindow();

		int iResult = int(pBox->ShowModal());
		return iResult;
	}
}