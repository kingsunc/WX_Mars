#pragma once
#include "PSCore.h"
#include "PSLiveAdaptee.h"
#include "PSMsgAdaptee.h"

// 具体的适配器;
class CPSCoreAdapter: public CPSCore
{
private:
	CPSCoreAdapter();
public:
	CPSCoreAdapter(CPSCoreCallBack* pCallBack);
	virtual ~CPSCoreAdapter();

	// 初始化;
	virtual bool Init();
	// 反初始化;
	virtual bool UnInit();

private:
	CPSLiveAdaptee*			m_pLiveAdaptee;
	CPSMsgAdaptee*			m_pMsgAdaptee;
};