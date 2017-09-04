#pragma once
#include <map>
#include <string>

namespace DuiLib 
{
#ifdef UNICODE
	typedef std::wstring	DuiTString;
#ifndef _T
#define _T(x) L ## x
#endif
#else
	typedef std::string		DuiTString;
#ifndef _T
#define _T(x) x
#endif
#endif 

	typedef CControlUI* (*CreateClass)();
	typedef std::map<CDuiString, CreateClass> MAP_DUI_CTRATECLASS;

	class UILIB_API CControlFactory
	{
	public:
		CControlUI* CreateControl(CDuiString strClassName);
		void RegistControl(CDuiString strClassName, CreateClass pFunc);

		static CControlFactory* GetInstance();
		void Release();

	private:	
		CControlFactory();
		virtual ~CControlFactory();

	private:
		MAP_DUI_CTRATECLASS m_mapControl;
	};

	class UILIB_API CDynamicClass
	{
	public:
		CDynamicClass(const char* chClassName, CreateClass pFunc)
		{
#ifdef UNICODE
			std::string sClassName(chClassName);
			DuiTString strClassName = S_2_WS(sClassName);
#else
			DuiTString strClassName(chClassName);
#endif
			CControlFactory::GetInstance()->RegistControl(strClassName.c_str(), pFunc);
		}

	private:
		std::wstring S_2_WS( const std::string& src );
	};


#define DECLARE_DUICONTROL(class_name)\
public:\
	static CControlUI* CreateControl();

#define IMPLEMENT_DUICONTROL(class_name)\
	CControlUI* class_name::CreateControl()\
	{ return new class_name; }

//#define REGIST_DUICONTROL(class_name)\
//	CControlFactory::GetInstance()->RegistControl(_T(#class_name), (CreateClass)class_name::CreateControl);
#define REGIST_DUICONTROL(class_name)\
	CDynamicClass s_dynamic##class_name(#class_name, (CreateClass) class_name::CreateControl);\

#define INNER_REGISTER_DUICONTROL(class_name)\
	RegistControl(_T(#class_name), (CreateClass)class_name::CreateControl);
}