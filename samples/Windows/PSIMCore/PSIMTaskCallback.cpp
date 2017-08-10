#include "PSIMTaskCallback.h"
#include "PSIMCallConcrete.h"

CPSIMTaskCallback* CPSIMTaskCallback::m_pInstance = nullptr;

CPSIMTaskCallback::CPSIMTaskCallback()
{
}

CPSIMTaskCallback::~CPSIMTaskCallback()
{
}

CPSIMTaskCallback* CPSIMTaskCallback::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CPSIMTaskCallback;
	}
	return m_pInstance;
}

void CPSIMTaskCallback::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

CPSIMCallBack* CPSIMTaskCallback::GetPSIMCallBack()
{
	CPSIMCallConcrete* pConcrete = dynamic_cast<CPSIMCallConcrete*>(AfxGetPSIMCall());
	if (!pConcrete)
	{
		// 异常处理;
		return nullptr;
	}
	return pConcrete->GetIMPSCallBack();
}

void CPSIMTaskCallback::OnResponse(Login_Task* task, MessageService::LoginResp& response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}
	m_pPSIMCallBack->OnLoginResponse(response.code, response.info.c_str());
}