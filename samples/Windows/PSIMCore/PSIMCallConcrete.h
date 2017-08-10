#pragma once
#include "PSIMCall.h"

// 磐石IMCall的具体实现
class CPSIMCallConcrete: public CPSIMCall
{
private:
	CPSIMCallConcrete();

public:
	CPSIMCallConcrete(CPSIMCallBack* pPSIMCallBack);
	virtual ~CPSIMCallConcrete();

	CPSIMCallBack* GetIMPSCallBack();

	// 初始化;
	virtual bool Init();
	// 反初始化;
	virtual bool UnInit();

	// 登录
	virtual void MsgLogin(const char* strAppID, const char* strAppToken, const char* strUserID, const char* strUserName, const char* strDeviceToken);
	// 注销
	virtual void MsgLogout();

private:
	// Core Back
	CPSIMCallBack*	m_pPSIMCallBack;
};

