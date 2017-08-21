#pragma once
#include "PSIMCall.h"

class CPSIMDemoCallBack : public CPSIMCallBack
{
public:
	CPSIMDemoCallBack();
	~CPSIMDemoCallBack();

	// 登录-回调处理;
	virtual void OnLoginResponse(const int& iCode, const char* strInfo);

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const PSMsgResp& msgResp);

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgResponse(const int& iCode, const char* strInfo);

	virtual void OnRecvMessage(const PSMessageItem& msgItem);

	// 创建群-回调处理;
	virtual void OnCreateGroupResponse(const CreateGroupResp& respCreateGroup);

	// 创建群-回调处理;
	virtual void OnAddGroupUserResponse(const BaseResp& respAddGroupUser);
};