#pragma once
#include "PSCoreCallBack.h"

class CPSLiveAdaptee
{
public:
	CPSLiveAdaptee();
	CPSLiveAdaptee(CPSCoreCallBack*	pCallBack);
	~CPSLiveAdaptee();

	// 初始化;
	bool Init();
	// 反初始化;
	bool UnInit();

private:
	CPSCoreCallBack*	m_pCallBack;
};

