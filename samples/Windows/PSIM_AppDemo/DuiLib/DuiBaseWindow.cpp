#include "stdafx.h"
#include "DuiBaseWindow.h"

namespace DuiLib
{
	SkinChangedParam	CDuiBaseWindow::m_paraSkin(false, 0, _T("main/0.png"));
	HWND	CDuiBaseWindow::m_hMain = NULL;

	CDuiBaseWindow::CDuiBaseWindow()
	{

	}

	CDuiBaseWindow::~CDuiBaseWindow()
	{

	}

	UINT CDuiBaseWindow::GetClassStyle() const
	{
		return CS_DBLCLKS;
	}

	void CDuiBaseWindow::OnFinalMessage(HWND /*hWnd*/)
	{
		CSkinManager::GetSkinManager()->RemoveReceiver(this);

		m_pmUI.RemovePreMessageFilter(this);
		m_pmUI.RemoveNotifier(this);
		m_pmUI.ReapObjects(m_pmUI.GetRoot());
	}

	void CDuiBaseWindow::Init()
	{
		CSkinManager::GetSkinManager()->AddReceiver(this);

		CControlUI* pRoot = m_pmUI.FindControl(_T("root"));
		if (pRoot != NULL)
		{
			if (m_paraSkin.m_bColor)
			{
				pRoot->SetBkColor(m_paraSkin.m_iBkColor);
				pRoot->SetBkImage(_T(""));
			}
			else
			{
				pRoot->SetBkColor(0);
				pRoot->SetBkImage(m_paraSkin.m_strBkImage);
			}
		}
	}

	LRESULT CDuiBaseWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

#if defined(WIN32) && !defined(UNDER_CE)
	LRESULT CDuiBaseWindow::OnNcActivate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if (::IsIconic(*this))
		{
			bHandled = FALSE;
		}
		return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT CDuiBaseWindow::OnNcCalcSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0;
	}

	LRESULT CDuiBaseWindow::OnNcPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0;
	}

	LRESULT CDuiBaseWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);

		if (!::IsZoomed(*this))
		{
			RECT rcSizeBox = m_pmUI.GetSizeBox();
			if (pt.y < rcClient.top + rcSizeBox.top)
			{
				if (pt.x < rcClient.left + rcSizeBox.left)
				{
					return HTTOPLEFT;
				}
				if (pt.x > rcClient.right - rcSizeBox.right)
				{
					return HTTOPRIGHT;
				}
				return HTTOP;
			}
			else if (pt.y > rcClient.bottom - rcSizeBox.bottom)
			{
				if (pt.x < rcClient.left + rcSizeBox.left)
				{
					return HTBOTTOMLEFT;
				}
				if (pt.x > rcClient.right - rcSizeBox.right)
				{
					return HTBOTTOMRIGHT;
				}
				return HTBOTTOM;
			}

			if (pt.x < rcClient.left + rcSizeBox.left)
			{
				return HTLEFT;
			}
			if (pt.x > rcClient.right - rcSizeBox.right)
			{
				return HTRIGHT;
			}
		}

		RECT rcCaption = m_pmUI.GetCaptionRect();
		if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right
			&&	pt.y >= rcCaption.top && pt.y < rcCaption.bottom)
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_pmUI.FindControl(pt));
			if (pControl &&
				(0 != _tcsicmp(pControl->GetClass(), _T("ButtonUI")))		&&
				(0 != _tcsicmp(pControl->GetClass(), _T("EditUI")))			&&
				(0 != _tcsicmp(pControl->GetClass(), _T("OptionUI")))		&&
				(0 != _tcsicmp(pControl->GetClass(), _T("ScrollBarUI")))	&&
				(0 != _tcsicmp(pControl->GetClass(), _T("ComboUI")))		&&
				(0 != _tcsicmp(pControl->GetClass(), _T("RichEditUI")))		&&
				(0 != _tcsicmp(pControl->GetClass(), _T("ProgressUI")))		&&
				(0 != _tcsicmp(pControl->GetClass(), _T("SliderUI")))		)
			{
				return HTCAPTION;
			}
		}

		return HTCLIENT;
	}

	LRESULT CDuiBaseWindow::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		MONITORINFO Monitor = {};
		Monitor.cbSize = sizeof(Monitor);
		::GetMonitorInfo(::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTOPRIMARY), &Monitor);
		RECT rcWork = Monitor.rcWork;
		if (Monitor.dwFlags != MONITORINFOF_PRIMARY)
		{
			::OffsetRect(&rcWork, -rcWork.left, -rcWork.top);
		}

		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMaxPosition.x = rcWork.left;
		lpMMI->ptMaxPosition.y = rcWork.top;
		lpMMI->ptMaxSize.x = rcWork.right - rcWork.left;
		lpMMI->ptMaxSize.y = rcWork.bottom - rcWork.top;
		lpMMI->ptMinTrackSize.x = m_pmUI.GetMinInfo().cx;
		lpMMI->ptMinTrackSize.y = m_pmUI.GetMinInfo().cy;

		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}
#endif


	LRESULT CDuiBaseWindow::OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnNcLButtonDbClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SIZE szRoundCorner = m_pmUI.GetRoundCorner();
#if defined(WIN32) && !defined(UNDER_CE)
		if (!::IsIconic(*this)) {
			CDuiRect rcWnd;
			::GetWindowRect(*this, &rcWnd);
			rcWnd.Offset(-rcWnd.left, -rcWnd.top);
			rcWnd.right++; rcWnd.bottom++;
			HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
			::SetWindowRgn(*this, hRgn, TRUE);
			::DeleteObject(hRgn);
		}
#endif
		bHandled = FALSE;
		return 0;
	}


	LRESULT CDuiBaseWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam == SC_CLOSE)
		{
			Close(IDCANCEL);
			bHandled = FALSE;
			return 0;
		}

		BOOL bZoomed = ::IsZoomed(*this);
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		if (::IsZoomed(*this) != bZoomed)
		{
			// 最大化状态变更;
		}

		return lRes;
	}

	LONG CDuiBaseWindow::GetStyle()
	{
		// 所有Duilib窗口一律不采用win32标题栏;
		LONG lStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
		lStyle &= ~WS_CAPTION;

		return lStyle;
	}

	LRESULT CDuiBaseWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::SetWindowLong(m_hWnd, GWL_STYLE, GetStyle() | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		RECT rcClient;
		::GetClientRect(m_hWnd, &rcClient);
		::SetWindowPos(m_hWnd, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);

		m_pmUI.Init(m_hWnd);
		m_pmUI.AddPreMessageFilter(this);

		CDialogBuilder builder;
		CDuiString tstrFileName = GetSkinFile();
		CControlUI* pRoot = builder.Create(tstrFileName.GetData(), (UINT)0, &m_pmUI);
		m_pmUI.AttachDialog(pRoot);
		m_pmUI.AddNotifier(this);

		Init();
		return 0;
	}

	LRESULT CDuiBaseWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		switch (uMsg)
		{
		case WM_CREATE:
			{
				lRes = OnCreate(uMsg, wParam, lParam, bHandled);
			}
			break;
		case WM_CLOSE:
			{
				lRes = OnClose(uMsg, wParam, lParam, bHandled);
			}
			break;
		case WM_DESTROY:		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
#if defined(WIN32) && !defined(UNDER_CE)
		case WM_NCACTIVATE:		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCCALCSIZE:		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		case WM_NCPAINT:		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
		case WM_NCHITTEST:		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		case WM_GETMINMAXINFO:	lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
		case WM_MOUSEWHEEL:		lRes = OnMouseWheel(uMsg, wParam, lParam, bHandled); break;
#endif
		case WM_SIZE:			lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
		case WM_SYSCOMMAND:		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
		case WM_KEYDOWN:		lRes = OnKeyDown(uMsg, wParam, lParam, bHandled); break;
		case WM_KILLFOCUS:		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break;
		case WM_SETFOCUS:		lRes = OnSetFocus(uMsg, wParam, lParam, bHandled); break;
		case WM_LBUTTONUP:		lRes = OnLButtonUp(uMsg, wParam, lParam, bHandled); break;
		case WM_LBUTTONDOWN:	lRes = OnLButtonDown(uMsg, wParam, lParam, bHandled); break;
		case WM_MOUSEMOVE:		lRes = OnMouseMove(uMsg, wParam, lParam, bHandled); break;
		case WM_NCLBUTTONDBLCLK:
			{
				 lRes = OnNcLButtonDbClick(uMsg, wParam, lParam, bHandled);
			}
			break;
		case WM_MENUCLICK:
			{
				lRes = OnClickMenuItem(uMsg, wParam, lParam, bHandled);
			}
			break;
		case WM_TIMER:
			{
				lRes = OnTimer(uMsg, wParam, lParam, bHandled);
			}
			break;
		default:				bHandled = FALSE; break;
		}

		if (bHandled)
		{
			return lRes;
		}

		if (m_pmUI.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	LRESULT CDuiBaseWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/)
	{
		if (uMsg == WM_KEYDOWN)
		{
			switch (wParam)
			{
			case VK_RETURN:
			case VK_ESCAPE:
				return ResponseDefaultKeyEvent(wParam);
			default:
				break;
			}
		}
		return FALSE;
	}

	LRESULT CDuiBaseWindow::ResponseDefaultKeyEvent(WPARAM wParam)
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

	DuiLib::CDuiString CDuiBaseWindow::GetSkinFolder()
	{
		CDuiString strFolder = CPaintManagerUI::GetResourcePath();
		return strFolder;
	}

	LRESULT CDuiBaseWindow::OnClickMenuItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT CDuiBaseWindow::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	CPaintManagerUI& CDuiBaseWindow::GetPaintManagerUI()
	{
		return m_pmUI;
	}

	void CDuiBaseWindow::SetTopMost(bool bIsTopMost, CDuiRect rectWnd)
	{
		if (::IsRectEmpty(&rectWnd))
		{
			::GetWindowRect(m_hWnd, &rectWnd);
		}
		if (bIsTopMost)
		{
			::SetWindowPos(m_hWnd, HWND_TOPMOST, rectWnd.left, rectWnd.top, rectWnd.GetWidth(), rectWnd.GetHeight(), SWP_NOACTIVATE);
		}
		else
		{
			::SetWindowPos(m_hWnd, HWND_NOTOPMOST, rectWnd.left, rectWnd.top, rectWnd.GetWidth(), rectWnd.GetHeight(), SWP_NOACTIVATE);
		}
	}

	LPCTSTR CDuiBaseWindow::QueryControlText(LPCTSTR lpstrId, LPCTSTR lpstrType)
	{
		return NULL;
	}

	BOOL CDuiBaseWindow::Receive(SkinChangedParam param)
	{
		CControlUI* pRoot = m_pmUI.FindControl(_T("root"));
		if (pRoot != NULL)
		{
			if (param.m_bColor)
			{
				pRoot->SetBkColor(param.m_iBkColor);
				pRoot->SetBkImage(_T(""));
			}
			else
			{
				pRoot->SetBkColor(0);
				pRoot->SetBkImage(param.m_strBkImage);
			}
		}
		return true;
	}

	void CDuiBaseWindow::SetSkinParam(SkinChangedParam& param)
	{
		m_paraSkin.m_bColor = param.m_bColor;
		m_paraSkin.m_iBkColor = param.m_iBkColor;
		m_paraSkin.m_strBkImage = param.m_strBkImage;

		if (NULL != m_hMain)
		{
			::SendMessage(m_hMain, WM_SKINPARAM_CHANGED, NULL, NULL);
		}
	}

	void CDuiBaseWindow::SetMainHwnd(HWND hMain)
	{
		if (hMain)
		{
			m_hMain = hMain;
		}
	}
}