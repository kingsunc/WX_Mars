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

void CPSIMTaskCallback::OnKickOut(const PSKickOutResp& response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}
	m_pPSIMCallBack->OnKickOutResponse(response);
}

void CPSIMTaskCallback::OnRecvMessage(const PSMessageItem & msgItem)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}
	m_pPSIMCallBack->OnRecvMessageResponse(msgItem);
}

void CPSIMTaskCallback::OnRecvOffMsgNotice(const PSOffMsgInfoNotice& offmsgNotice)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}
	m_pPSIMCallBack->OnRecvOffMsgNoticeResponse(offmsgNotice);
}

void CPSIMTaskCallback::OnResponse(Login_Task* task, MessageService::LoginResp& response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}

	PSMsgLoginResp resp;
	resp.iStatus = response.code;
	resp.strMessage = (char*)response.info.c_str();
	m_pPSIMCallBack->OnMsgLoginResponse(resp);
}

void CPSIMTaskCallback::OnResponse(Msg_Task * task, MessageService::SendMsgResp & response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}

	PSSendMsgResp msgResp;
	msgResp.iSeqId = task->taskid_;
	msgResp.iStatus = response.code;
	msgResp.strMessage = (char*)response.info.c_str();
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

	PSOffMsgResp offMsgResp;
	offMsgResp.iStatus = response.code;
	offMsgResp.strMessage = (char*)response.info.c_str();
	for (int i = 0; i < response.msgs.size(); i++)
	{
		MessageService::Message& msg = response.msgs[i];
		PSMessageItem msgItem;
		msgItem.iMsgId = msg.msgId;
		msgItem.strFrom = msg.from.c_str();
		msgItem.strTo = msg.to.c_str();
		msgItem.iSendMode = msg.sendMode;
		msgItem.iType = msg.type;
		msgItem.iPriority = msg.priority;
		msgItem.iHandleOption = msg.handleOption;
		msgItem.strPushInfo = msg.pushInfo.c_str();
		msgItem.iTimestamp = msg.timestamp;
		msgItem.iExpireTime = msg.expireTime;
		// 内容拷贝;
		const int iLen = msg.content.size();
		for (int i = 0; i < iLen; i++)
		{
			msgItem.strContent += msg.content[i];
		}

		offMsgResp.vecMessage.push_back(msgItem);
	}
	m_pPSIMCallBack->OnGetOffMsgResponse(offMsgResp);
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

void CPSIMTaskCallback::OnResponse(DeleteGroup_Task* task, DeleteGroupResp_Json& response)
{
	CPSIMCallBack*	m_pPSIMCallBack = GetPSIMCallBack();
	if (!m_pPSIMCallBack)
	{
		// 异常处理;
		return;
	}

	PSDeleteGroupResp respDeleteGroup;
	respDeleteGroup.iStatus = response.m_iStatus;
	respDeleteGroup.strMessage = (char*)(response.m_strMessage.c_str());
	m_pPSIMCallBack->OnDeleteGroupResponse(respDeleteGroup);
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