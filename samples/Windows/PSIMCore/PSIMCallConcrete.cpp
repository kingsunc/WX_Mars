#include "PSIMCallConcrete.h"
#include "PSIMTaskCallback.h"
#include "xlogger/xlogger.h"
#include "log/appender.h"

enum DeviceType
{
	DeviceTypeIos = 1,
	DeviceTypeAndroid = 2,
	DeviceTypeWindows = 3,
	DeviceTypeOther = 6
};

CPSIMCallConcrete::CPSIMCallConcrete()
{
}

CPSIMCallConcrete::CPSIMCallConcrete(CPSIMCallBack* pPSIMCallBack)
{
	m_pPSIMCallBack = pPSIMCallBack;
}

CPSIMCallConcrete::~CPSIMCallConcrete()
{
}

CPSIMCallBack* CPSIMCallConcrete::GetIMPSCallBack()
{
	return m_pPSIMCallBack;
}

// 初始化;
bool CPSIMCallConcrete::Init()
{
	char strIn[100] = "abcdefghijklmnopqrstuvwxyz";
	char strOut[100] = {0};
	AutoBuffer strBuff;
	strBuff.AllocWrite(strlen(strIn) + 1, true);
	strBuff.Write(strIn);
	strBuff.Seek(0, AutoBuffer::ESeekStart);
	strBuff.Read(10, strOut, 6);

	// init xlog
	std::string logPath = "D://Log";	//use your log path
	std::string pubKey = "aaa";			//use you pubkey for log encrypt						 
#if _DEBUG
	xlogger_SetLevel(kLevelAll);
	appender_set_console_log(true);
#else
	xlogger_SetLevel(kLevelInfo);
	appender_set_console_log(false);
#endif
	appender_open(kAppednerAsync, logPath.c_str(), "Test", pubKey.c_str());

	MarsWrapper::GetInstance().Start();

	return true;
}

// 反初始化;
bool CPSIMCallConcrete::UnInit()
{
	CPSIMTaskCallback::ReleaseInstance();

	// uninit xlog
	appender_close();

	return true;
}

// 登录
void CPSIMCallConcrete::MsgLogin(const char* strAppID, const char* strAppToken, const char* strUserID, const char* strUserName, const char* strDeviceToken)
{
	int iDeviceType = DeviceType::DeviceTypeWindows;
	MarsWrapper::GetInstance().MsgLogin(strAppID, strAppToken, strUserID, strUserName, iDeviceType, strDeviceToken, CPSIMTaskCallback::GetInstance());
}

// 注销
void CPSIMCallConcrete::MsgLogout()
{

}