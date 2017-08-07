#include "PSCoreAdapter.h"

CPSCoreAdapter::CPSCoreAdapter()
{
	m_pLiveAdaptee = new CPSLiveAdaptee(nullptr);
	m_pMsgAdaptee = new CPSMsgAdaptee(nullptr);
}

CPSCoreAdapter::CPSCoreAdapter(CPSCoreCallBack* pCallBack)
{
	m_pLiveAdaptee = new CPSLiveAdaptee(pCallBack);
	m_pMsgAdaptee = new CPSMsgAdaptee(pCallBack);
}

CPSCoreAdapter::~CPSCoreAdapter()
{
	if (m_pLiveAdaptee)
	{
		delete m_pLiveAdaptee;
		m_pLiveAdaptee = NULL;
	}

	if (m_pMsgAdaptee)
	{
		delete m_pMsgAdaptee;
		m_pMsgAdaptee = NULL;
	}
}

// 初始化;
bool CPSCoreAdapter::Init()
{
	if (!m_pLiveAdaptee->Init())
	{
		return false;
	}
	if (!m_pMsgAdaptee->Init())
	{
		return false;
	}

	return true;
}

// 反初始化;
bool CPSCoreAdapter::UnInit()
{
	if (!m_pLiveAdaptee->UnInit())
	{
		return false;
	}
	if (!m_pMsgAdaptee->UnInit())
	{
		return false;
	}

	return true;
}