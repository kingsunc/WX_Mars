#pragma once
#include "MyThread.h"
#include "TSingleton.h"
#include "IniConfig.h"
#include "PSIMDemoCallBack.h"

class CUIApp : public CMyThread, public TSingleton<CUIApp>
{
public:
	CUIApp();
	virtual ~CUIApp();

public:
	// 设置 程序hInstance;
	void SetMainInstance(HINSTANCE hInstance);
	// 获取输出目录;
	std::string GetOutPath();

	static bool PathstrFileExists(std::string strstrFile);

	std::string GetProFileString(std::string strKey, std::string strDefault = "");
	int GetProFileInt(std::string strKey, int iDefault = 0);

private:
	virtual void RunThread();

	bool InitInstance();
	bool ExitInstance();

	HINSTANCE			m_hInstance;
	std::string			m_strOutPath;	// 输出目录;
	CIniConfig			m_iniConfig;

	CPSIMDemoCallBack* m_pCallBack;
};

#define AflGetUIApp		CUIApp::GetInstance