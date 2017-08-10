#include "PSIMCallConcrete.h"
#include "PSIMTaskCallback.h"

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
	MarsWrapper::GetInstance().Start();

	return true;
}

// 反初始化;
bool CPSIMCallConcrete::UnInit()
{
	CPSIMTaskCallback::ReleaseInstance();

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