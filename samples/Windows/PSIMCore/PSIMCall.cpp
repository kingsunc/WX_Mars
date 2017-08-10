#include "PSIMCall.h"
#include "PSIMCallConcrete.h"

#define PSIM_VERSION		"v1.0.0  2017.08.10"

CPSIMCall* CPSIMCallFactory::m_pInstance = nullptr;

void CPSIMCallFactory::CreateInstance(CPSIMCallBack* pCallBack)
{
	if (!m_pInstance)
	{
		m_pInstance = new CPSIMCallConcrete(pCallBack);
	}
}

CPSIMCall* CPSIMCallFactory::GetInstance()
{
	return m_pInstance;
}

void CPSIMCallFactory::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

const char* CPSIMCallFactory::GetPSIMVersion()
{
	return PSIM_VERSION;
}