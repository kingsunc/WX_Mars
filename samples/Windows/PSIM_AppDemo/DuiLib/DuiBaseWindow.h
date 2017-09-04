#pragma once
#include "UIlib.h"
#include "SkinManager.h"

#define WM_SKINPARAM_CHANGED	(WM_USER + 5000)

enum SceneStatus
{
	SCENE_ADD		= 0,
	SCENE_MODIFY	= 1
};

namespace DuiLib {

	class UILIB_API CDuiBaseWindow : 
		public CWindowWnd, 
		public INotifyUI, 
		public IMessageFilterUI, 
		public SkinChangedReceiver,
		public IQueryControlText
	{
	public:
		CDuiBaseWindow();
		virtual ~CDuiBaseWindow();

		virtual void OnFinalMessage(HWND hWnd);

		virtual UINT GetClassStyle() const;

		virtual void Init();

		CPaintManagerUI& GetPaintManagerUI();

		virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

#if defined(WIN32) && !defined(UNDER_CE)
		virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
#endif

		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		// Caption双击事件;
		virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual LONG GetStyle();

		virtual LRESULT OnClickMenuItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		void SetTopMost(bool bIsTopMost, CDuiRect rectWnd );			// 置顶显示;

		virtual LPCTSTR QueryControlText(LPCTSTR lpstrId, LPCTSTR lpstrType);

		virtual BOOL Receive(SkinChangedParam param);
		static void SetSkinParam(SkinChangedParam& param);
		static void SetMainHwnd(HWND hMain);

	protected:
		virtual CDuiString GetSkinFolder();		// 资源目录;
		virtual CDuiString GetSkinFile() = 0;	// 文件名称;

		virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	protected:
		CPaintManagerUI				m_pmUI;
		static SkinChangedParam		m_paraSkin;
		static HWND					m_hMain;	// 主窗口句柄;
	};
}

using namespace DuiLib;