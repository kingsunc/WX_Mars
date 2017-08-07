#include "MarsWrapper.h"
#include "PSLiveAdaptee.h"


CPSLiveAdaptee::CPSLiveAdaptee()
{
	m_pCallBack = nullptr;
}

CPSLiveAdaptee::CPSLiveAdaptee(CPSCoreCallBack*	pCallBack)
{
	m_pCallBack = pCallBack;
}

CPSLiveAdaptee::~CPSLiveAdaptee()
{
}

// 初始化;
bool CPSLiveAdaptee::Init()
{
	MarsWrapper::Instance().start();

	//MarsWrapper::Instance().setChatMsgObserver(this);

	return true;
}

// 反初始化;
bool CPSLiveAdaptee::UnInit()
{
	return true;
}