#include "PSCore.h"
#include "PSCoreLock.h"
#include "PSCoreAdapter.h"

CPSCore* CPSCoreFactory::m_pInstance = NULL;
CPSCoreLock		g_lockFactory;

void CPSCoreFactory::CreateInstance(CPSCoreCallBack* pCallBack)
{
	if (NULL == m_pInstance)
	{
		g_lockFactory.Lock();
		if (NULL == m_pInstance)
		{
			m_pInstance = new CPSCoreAdapter(pCallBack);
		}
		g_lockFactory.UnLock();
	}
}

CPSCore* CPSCoreFactory::GetInstance()
{
	return m_pInstance;
}

void CPSCoreFactory::ReleaseInstance()
{
	if (NULL != m_pInstance)
	{
		g_lockFactory.Lock();
		if (NULL != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
		g_lockFactory.UnLock();
	}
}