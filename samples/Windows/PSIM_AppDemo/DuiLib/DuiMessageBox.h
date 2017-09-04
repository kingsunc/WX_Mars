#pragma once
#include "DuiBaseWindow.h"

namespace DuiLib {

	class UILIB_API CDuiMessageBox : public CDuiBaseWindow
	{
	public:
		CDuiMessageBox();
		~CDuiMessageBox();

		void SetBoxTex(CDuiString strtBoxText);
		void SetBoxCaption(CDuiString strtBoxCaption);
		void SetBoxType(UINT uBoxType);

		static int DuiMessageBox(HWND hParentWnd = NULL,
			LPCTSTR lpText = _T(""),
			LPCTSTR lpCaption = _T("提示"),
			UINT uType = MB_OK | MB_ICONINFORMATION);

	protected:
		LPCTSTR GetWindowClassName() const;

		virtual CDuiString GetSkinFile();

		virtual void Init();
		virtual void OnFinalMessage(HWND hWnd);

		// 键盘响应;
		virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

		virtual CControlUI* CreateControl(LPCTSTR pstrClass);

		// Caption双击事件;
		virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	protected:

		void Notify(TNotifyUI& msg);

		void CloseMessageBox(CDuiString strText);
	};

#define AflMessageBox	CDuiMessageBox::DuiMessageBox
}