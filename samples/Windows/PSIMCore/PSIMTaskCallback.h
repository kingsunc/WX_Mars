#pragma once
#include "MarsWrapper.h"
#include "PSIMCallBack.h"

class CPSIMTaskCallback: public MessagePush, 
	public Login_Callback, public Msg_Callback, public OffMsg_Callback
{
private:
	CPSIMTaskCallback();

public:
	~CPSIMTaskCallback();

	static CPSIMTaskCallback* GetInstance();

	static void ReleaseInstance();

protected:
	// 接收消息-回调处理;
	virtual void OnRecvMessage(const MessageItem& msgItem);

	// 登录-回调处理;
	virtual void OnResponse(Login_Task* task, MessageService::LoginResp& response);

	// 发送消息-回调处理;
	virtual void OnResponse(Msg_Task* task, MessageService::SendMsgResp& response);

	// 获取离线消息-回调处理;
	virtual void OnResponse(OffMsg_Task* task, MessageService::OfflineMsgResp& response);

	

private:
	CPSIMCallBack* GetPSIMCallBack();

private:
	static CPSIMTaskCallback* m_pInstance;
};