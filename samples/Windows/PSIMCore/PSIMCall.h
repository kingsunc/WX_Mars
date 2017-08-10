#pragma once
#include "PSIMCallBack.h"

// 终端SDK 访问的抽象类;
class CPSIMCall
{
public:
	CPSIMCall() {};
	virtual ~CPSIMCall() {};

	// 初始化;
	virtual bool Init() = 0;
	// 反初始化;
	virtual bool UnInit() = 0;

	// 登录
	virtual void MsgLogin(const char* strAppID, const char* strAppToken, const char* strUserID, const char* strUserName, const char* strDeviceToken) = 0;
	// 注销
	virtual void MsgLogout() = 0;
};

class CPSIMCallFactory
{
public:
	// 创建时,需要传递回调接口;
	static void CreateInstance(CPSIMCallBack* pCallBack);

	// 获取 m_pInstance;
	static CPSIMCall* GetInstance();

	static const char* GetPSIMVersion();

	// 释放 m_pInstance;
	static void ReleaseInstance();

private:
	static CPSIMCall* m_pInstance;
};

#define AfxGetPSIMCall	CPSIMCallFactory::GetInstance