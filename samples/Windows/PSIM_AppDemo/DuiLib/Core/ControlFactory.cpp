#include "StdAfx.h"
#include "ControlFactory.h"

namespace DuiLib 
{
	CControlFactory::CControlFactory()
	{
		INNER_REGISTER_DUICONTROL(CControlUI);
		INNER_REGISTER_DUICONTROL(CContainerUI);
		INNER_REGISTER_DUICONTROL(CButtonUI);
		INNER_REGISTER_DUICONTROL(CComboUI);
		INNER_REGISTER_DUICONTROL(CComboBoxUI);
		INNER_REGISTER_DUICONTROL(CDateTimeUI);
		INNER_REGISTER_DUICONTROL(CEditUI);
		INNER_REGISTER_DUICONTROL(CActiveXUI);
		INNER_REGISTER_DUICONTROL(CFlashUI);
		INNER_REGISTER_DUICONTROL(CGifAnimUI);
		INNER_REGISTER_DUICONTROL(CGroupBoxUI);
		INNER_REGISTER_DUICONTROL(CIPAddressUI);
		INNER_REGISTER_DUICONTROL(CLabelUI);
		INNER_REGISTER_DUICONTROL(CListUI);
		INNER_REGISTER_DUICONTROL(CListHeaderUI);
		INNER_REGISTER_DUICONTROL(CListHeaderItemUI);
		INNER_REGISTER_DUICONTROL(CListLabelElementUI);
		INNER_REGISTER_DUICONTROL(CListTextElementUI);
		INNER_REGISTER_DUICONTROL(CListContainerElementUI);
		INNER_REGISTER_DUICONTROL(CMenuUI);
		INNER_REGISTER_DUICONTROL(CMenuElementUI);
		INNER_REGISTER_DUICONTROL(COptionUI);
		INNER_REGISTER_DUICONTROL(CCheckBoxUI);
		INNER_REGISTER_DUICONTROL(CProgressUI);
		INNER_REGISTER_DUICONTROL(CRichEditUI);
		INNER_REGISTER_DUICONTROL(CScrollBarUI);
		INNER_REGISTER_DUICONTROL(CSliderUI);
		INNER_REGISTER_DUICONTROL(CTextUI);
		INNER_REGISTER_DUICONTROL(CTreeNodeUI);
		INNER_REGISTER_DUICONTROL(CTreeViewUI);
		INNER_REGISTER_DUICONTROL(CWebBrowserUI);
		INNER_REGISTER_DUICONTROL(CAnimationTabLayoutUI);
		INNER_REGISTER_DUICONTROL(CChildLayoutUI);
		INNER_REGISTER_DUICONTROL(CHorizontalLayoutUI);
		INNER_REGISTER_DUICONTROL(CTabLayoutUI);
		INNER_REGISTER_DUICONTROL(CTileLayoutUI);
		INNER_REGISTER_DUICONTROL(CVerticalLayoutUI);
	}

	CControlFactory::~CControlFactory()
	{
	}

	CControlUI* CControlFactory::CreateControl(CDuiString strClassName)
	{
		MAP_DUI_CTRATECLASS::iterator iter = m_mapControl.find(strClassName);
		if ( iter == m_mapControl.end()) 
		{
			return NULL;
		}
		else 
		{
			return (CControlUI*) (iter->second());
		}
	}

	void CControlFactory::RegistControl(CDuiString strClassName, CreateClass pFunc)
	{
		m_mapControl.insert(MAP_DUI_CTRATECLASS::value_type(strClassName, pFunc));
	}

	CControlFactory* CControlFactory::GetInstance()  
	{
		static CControlFactory* pInstance = new CControlFactory;
		return pInstance;
	}

	void CControlFactory::Release()
	{
		delete this;
	}

	std::wstring CDynamicClass::S_2_WS(const std::string& src)
	{
		std::locale sys_locale("");

		const char* data_from = src.c_str();
		const char* data_from_end = src.c_str() + src.size();
		const char* data_from_next = 0;

		wchar_t* data_to = new wchar_t[src.size() + 1];
		wchar_t* data_to_end = data_to + src.size() + 1;
		wchar_t* data_to_next = 0;

		wmemset( data_to, 0, src.size() + 1 );

		typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
		mbstate_t in_state = {0};
		auto result = std::use_facet<convert_facet>(sys_locale).in(
			in_state, data_from, data_from_end, data_from_next,
			data_to, data_to_end, data_to_next );
		if( result == convert_facet::ok )
		{
			std::wstring dst = data_to;
			delete[] data_to;
			return dst;
		}
		else
		{
			delete[] data_to;
			return std::wstring(L"");
		}
	}
}