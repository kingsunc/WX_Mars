#pragma once
#include "PSCoreCallBack.h"

class CPSMsgAdaptee
{
public:
	CPSMsgAdaptee();
	CPSMsgAdaptee(CPSCoreCallBack*	pCallBack);
	~CPSMsgAdaptee();

	// 初始化;
	bool Init();
	// 反初始化;
	bool UnInit();

private:
	CPSCoreCallBack*	m_pCallBack;
};