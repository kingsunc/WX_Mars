#pragma once
#include "MarsWrapper.h"
#include "PSIMCallBack.h"

class CPSIMTaskCallback
	: public MessagePush
	, public Login_Callback
	, public Msg_Callback, public OffMsg_Callback
	, public CreateGroup_Callback, public DeleteGroup_Callback
	, public AddGroupUser_Callback
{
private:
	CPSIMTaskCallback();

public:
	~CPSIMTaskCallback();

	static CPSIMTaskCallback* GetInstance();

	static void ReleaseInstance();

protected:


	// 登录-回调处理;
	virtual void OnResponse(Login_Task* task, MessageService::LoginResp& response);

	// 发送消息-回调处理;
	virtual void OnResponse(Msg_Task* task, MessageService::SendMsgResp& response);

	// 获取离线消息-回调处理;
	virtual void OnResponse(OffMsg_Task* task, MessageService::OfflineMsgResp& response);

	// 创建群组-回调处理;
	virtual void OnResponse(CreateGroup_Task* task, CreateGroupResp_Json& response);

	// 删除群组-回调处理;
	virtual void OnResponse(DeleteGroup_Task* task, DeleteGroupResp_Json& response);

	// 添加群成员-回调处理;
	virtual void OnResponse(AddGroupUser_Task* task, AddGroupUserResp_Json& response);

	// 被迫下线-回调处理;
	virtual void OnKickOut(const PSKickOutResp& response);

	// 接收消息-回调处理;
	virtual void OnRecvMessage(const PSMessageItem& msgItem);

	// 接收离线消息描述-回调处理;
	virtual void OnRecvOffMsgNotice(const PSOffMsgInfoNotice& offmsgNotice);

private:
	CPSIMCallBack* GetPSIMCallBack();

private:
	static CPSIMTaskCallback* m_pInstance;
};