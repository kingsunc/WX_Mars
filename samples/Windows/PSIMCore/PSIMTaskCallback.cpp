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
		m_pInstance = new CPSIMTaskCallback();
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

void CPSIMTaskCallback::OnRecvMessage(const PSMessageItem & msgItem)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}
	m_pPSIMCallBack->OnRecvMessage(msgItem);
}

void CPSIMTaskCallback::OnResponse(Login_Task* task, MessageService::LoginResp& response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}

	PSMsgLoginResp respMsgLogin;
	respMsgLogin.iStatus = response.code;
	respMsgLogin.strMessage = (char*)response.info.c_str();
	m_pPSIMCallBack->OnMsgLoginResponse(respMsgLogin);
}

void CPSIMTaskCallback::OnResponse(Msg_Task * task, MessageService::SendMsgResp & response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}

	PSMsgResp msgResp;
	msgResp.iSeqId = task->taskid_;
	msgResp.iCode = response.code;
	msgResp.strInfo = (char*)response.info.c_str();
	m_pPSIMCallBack->OnSendMsgResponse(msgResp);
}

void CPSIMTaskCallback::OnResponse(OffMsg_Task * task, MessageService::OfflineMsgResp & response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}
	m_pPSIMCallBack->OnGetOffMsgResponse(response.code, response.info.c_str());
}

void CPSIMTaskCallback::OnResponse(CreateGroup_Task * task, CreateGroupResp_Json& response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}

	PSCreateGroupResp respCreateGroup;
	respCreateGroup.iStatus = response.m_iStatus;
	respCreateGroup.strMessage = (char*)(response.m_strMessage.c_str());
	m_pPSIMCallBack->OnCreateGroupResponse(respCreateGroup);
}

void CPSIMTaskCallback::OnResponse(AddGroupUser_Task * task, AddGroupUserResp_Json & response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}

	PSAddGroupUsersResp respAddGroupUsers;
	respAddGroupUsers.iStatus = response.m_iStatus;
	respAddGroupUsers.strMessage = (char*)(response.m_strMessage.c_str());
	m_pPSIMCallBack->OnAddGroupUsersResponse(respAddGroupUsers);
}
