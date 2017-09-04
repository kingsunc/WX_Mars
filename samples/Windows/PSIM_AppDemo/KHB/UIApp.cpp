#include "UIApp.h"
#include "UIHelper.h"
// Duilib;
#include "DuilibProInc.h"
#include <sys\stat.h>
#include "MiniDumper.h"
#include "Data.h"

CUIApp::CUIApp(): CMyThread("KHBApp")
{
	m_iniConfig.LoadFile("./Config/server.ini");
}

CUIApp::~CUIApp()
{
}

void CUIApp::SetMainInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

std::string CUIApp::GetOutPath()
{
	if (m_strOutPath.empty())
	{
		char strExePath[MAX_PATH] = {0};
		GetCurrentDirectoryA(MAX_PATH, strExePath);
		m_strOutPath = strExePath;
	}

	return m_strOutPath;
}

bool CUIApp::PathstrFileExists(std::string strstrFile)
{
	struct _stat strFileStat;
	if ((_stat(strstrFile.c_str(), &strFileStat) == 0) && (strFileStat.st_mode & _S_IFDIR))
	{
		return true;
	}

	return false;
}

std::string CUIApp::GetProFileString(std::string strKey, std::string strDefault)
{
	return m_iniConfig.GetStringVal(strKey, strDefault);
}

int CUIApp::GetProFileInt(std::string strKey, int iDefault)
{
	return m_iniConfig.GetIntVal(strKey, iDefault);
}

void CUIApp::RunThread()
{
	MiniDumper miniDumper(true, GetOutPath());

	InitInstance();

	ExitInstance();
}

bool CUIApp::InitInstance()
{
	LOG_INFO("Enter CUIApp::InitInstance");

	// Log4;
	ILog4zManager::getInstance()->config(".\\Config\\log_config.cfg");
	ILog4zManager::getInstance()->start();

	// Duilib;
	CPaintManagerUI::SetInstance(m_hInstance);
#if USE_ZIP_SKIN
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T(""));
	CPaintManagerUI::SetResourceZip(_T("skin.zip"));
#else
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
#endif

	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	m_pCallBack = new CPSIMDemoCallBack(); // 继承CPSIMCallBack 进行回调处理;
	CPSIMCallFactory::CreateInstance(m_pCallBack); // 创建IMCall的实体对象;
	AfxGetPSIMCall()->Init();	// 获取IMCall的实体对象，进行初始化操作;

	do 
	{
		AflGetData()->Clear();
		UINT iRes = AflGetUIHelper()->ShowLoginWnd();
		if (IDOK == iRes)
		{
			AflGetUIHelper()->ShowMainWnd();
		}
	} while (1);
	
	return true;
}

bool CUIApp::ExitInstance()
{
	LOG_INFO("CUIApp::ExitInstance");

	// Log4退出;
	ILog4zManager::getInstance()->releaseInstance();
	// Duilib退出;
	PostQuitMessage(0);
	CPaintManagerUI::MessageLoop();

	return true;
}