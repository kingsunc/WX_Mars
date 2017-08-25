#pragma once
#include "PSDefs.h"

class CPSIMCallBack
{
public:
	CPSIMCallBack() {};
	virtual ~CPSIMCallBack() {};

	// 登录-回调处理;
	virtual void OnMsgLoginResponse(const PSMsgLoginResp& respMsgLogin) = 0;
	// 注销-回调处理;
	virtual void OnMsgLogoutResponse(const PSMsgLoginResp& respMsgLogout) = 0;
	// 被迫踢出-回调处理;
	virtual void OnKickOutResponse(const PSKickOutResp& respKickOut) = 0;

	// 创建群-回调处理;
	virtual void OnCreateGroupResponse(const PSCreateGroupResp& respCreateGroup) = 0;
	// 删除群-回调处理;
	virtual void OnDeleteGroupResponse(const PSDeleteGroupResp& respDeleteeGroup) = 0;

	// 添加群成员-回调处理;
	virtual void OnAddGroupUsersResponse(const PSAddGroupUsersResp& respAddGroupUsers) = 0;
	// 移除群成员-回调处理;
	virtual void OnRemoveGroupUsersResponse(const PSRemoveGroupUsersResp& respRemoveGroupUsers) = 0;

	// 添加子群-回调处理;
	virtual void OnAddGroupChildsResponse(const PSAddGroupChildsResp& respAddGroupChilds) = 0;
	// 移除子群-回调处理;
	virtual void OnRemoveGroupChildsResponse(const PSRemoveGroupChildsResp& respRemoveGroupChilds) = 0;

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const PSMsgResp& respMsg) = 0;

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgResponse(const int& iCode, const char* strInfo) = 0;

	virtual void OnRecvMessage(const PSMessageItem& msgItem) = 0;
};