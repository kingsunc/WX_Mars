#pragma once
#include "PSDefs.h"

class CPSIMCallBack
{
public:
	CPSIMCallBack() {};
	virtual ~CPSIMCallBack() {};

	// 踢出-回调处理;
	//virtual void OnKickOut(const int& iCode, const char* strInfo) = 0;

	// 登录-回调处理;
	virtual void OnLoginResponse(const int& iCode, const char* strInfo) = 0;

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const PSMsgResp& respMsg) = 0;

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgResponse(const int& iCode, const char* strInfo) = 0;

	virtual void OnRecvMessage(const PSMessageItem& msgItem) = 0;

	// 创建群-回调处理;
	virtual void OnCreateGroupResponse(const CreateGroupResp& respCreateGroup) = 0;

	// 创建群-回调处理;
	virtual void OnAddGroupUserResponse(const BaseResp& respAddGroupUser) = 0;
};