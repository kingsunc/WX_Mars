#pragma once
#include "SkinManager.h"
#include "DuiBaseWindow.h"

namespace DuiLib {

	class UILIB_API CSkinFrame : public CDuiBaseWindow
	{
	public:
		CSkinFrame(HWND hParent, CControlUI *pControl);

	public:
		void Init();

	public:
		LPCTSTR GetWindowClassName() const
		{
			return _T("UISkinFrame"); 
		}

		UINT GetClassStyle() const
		{
			return CS_DBLCLKS;
		}

		void OnFinalMessage(HWND /*hWnd*/)
		{
			delete this;
		}

		virtual CDuiString GetSkinFile()
		{
			return _T("wnd\\skin.xml");
		}

		void Notify(TNotifyUI& msg)
		{
			if (msg.sType == _T("click")) {
				// °´Å¥ÏûÏ¢
				OnLClick(msg.pSender);
			}
		}

		void OnLClick(CControlUI *pControl);

		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	private:
		HWND m_hParent;
		CControlUI* m_pControl;
	};
}