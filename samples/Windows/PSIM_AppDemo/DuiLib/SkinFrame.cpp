#include "stdafx.h"
#include "SkinFrame.h"

namespace DuiLib {

	DuiLib::CSkinFrame::CSkinFrame(HWND hParent, CControlUI *pControl)
	{
		m_hParent = hParent;
		m_pControl = pControl;
		Create(NULL, _T("skinframe"), WS_POPUP | WS_VISIBLE, WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
	}

	void CSkinFrame::Init()
	{
		if (m_pControl == NULL) return;

		RECT rcConrol = m_pControl->GetPos();
		SIZE szWnd = m_pmUI.GetInitSize();
		POINT ptWnd = { 0 };
		ptWnd.x = rcConrol.right - szWnd.cx;
		ptWnd.y = rcConrol.bottom;
		::ClientToScreen(m_hParent, &ptWnd);

		SetWindowPos(m_hWnd, NULL, ptWnd.x, ptWnd.y, szWnd.cx, szWnd.cy, SWP_NOSIZE | SWP_NOACTIVATE);
	}

	void CSkinFrame::OnLClick(CControlUI *pControl)
	{
		CDuiString strName = pControl->GetName();
		if (strName.CompareNoCase(_T("skin_image_btn")) == 0)
		{
			SkinChangedParam skin;
			skin.m_bColor = false;
			skin.m_strBkImage = pControl->GetUserData();
			SetSkinParam(skin);
			CSkinManager::GetSkinManager()->Broadcast(skin);
		}
		else if (strName.CompareNoCase(_T("skin_color_btn")) == 0)
		{
			SkinChangedParam skin;
			skin.m_bColor = true;
			skin.m_iBkColor = pControl->GetBkColor();
			SetSkinParam(skin);
			CSkinManager::GetSkinManager()->Broadcast(skin);
		}
		else if (strName.CompareNoCase(_T("skin_color")) == 0)
		{
			CTabLayoutUI *pSkinTab = (CTabLayoutUI*)m_pmUI.FindControl(_T("skin_tab"));
			pSkinTab->SelectItem(1);
		}
		else if (strName.CompareNoCase(_T("skin_image")) == 0)
		{
			CTabLayoutUI *pSkinTab = (CTabLayoutUI*)m_pmUI.FindControl(_T("skin_tab"));
			pSkinTab->SelectItem(0);
		}
	}

	LRESULT CSkinFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		m_pmUI.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("wnd\\skin.xml"), NULL, &m_pmUI);
		ASSERT(pRoot && "Failed to parse XML");
		m_pmUI.AttachDialog(pRoot);
		m_pmUI.AddNotifier(this);

		Init();
		return 0;
	}

	LRESULT CSkinFrame::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		Close(IDCANCEL);
		return 0;
	}
}