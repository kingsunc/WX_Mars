
// PSIMCoreDemo.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "PSIMDemoCallBack.h"

// CPSIMCoreDemoApp: 
// 有关此类的实现，请参阅 PSIMCoreDemo.cpp
//

class CPSIMCoreDemoApp : public CWinApp
{
public:
	CPSIMCoreDemoApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
	CStringA	m_strAppID;
	CStringA	m_strUserID;
private:
	CPSIMDemoCallBack* m_pCallBack;
};

extern CPSIMCoreDemoApp theApp;