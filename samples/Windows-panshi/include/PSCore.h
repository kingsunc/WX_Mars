#pragma once
#include "PSCoreCallBack.h"

// client 访问的抽象类;
class CPSCore
{
public:
	CPSCore() {};
	virtual ~CPSCore() {};

	// 初始化;
	virtual bool Init() = 0;
	// 反初始化;
	virtual bool UnInit() = 0;

};

class PSCORE_API CPSCoreFactory
{
public:
	// 创建时,需要传递回调接口;
	static void CreateInstance(CPSCoreCallBack* pCallBack);

	// 获取 m_pInstance;
	static CPSCore* GetInstance();

	// 释放 m_pInstance;
	static void ReleaseInstance();

private:
	static CPSCore* m_pInstance;
};

#define AfxGetPSCore	CPSCoreFactory::GetInstance