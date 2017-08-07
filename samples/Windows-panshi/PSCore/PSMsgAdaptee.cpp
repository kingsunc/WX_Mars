#include "PSMsgAdaptee.h"

CPSMsgAdaptee::CPSMsgAdaptee()
{
	m_pCallBack = nullptr;
}

CPSMsgAdaptee::CPSMsgAdaptee(CPSCoreCallBack*	pCallBack)
{
	m_pCallBack = pCallBack;
}

CPSMsgAdaptee::~CPSMsgAdaptee()
{
}

// 初始化;
bool CPSMsgAdaptee::Init()
{
	return true;
}

// 反初始化;
bool CPSMsgAdaptee::UnInit()
{
	return true;
}