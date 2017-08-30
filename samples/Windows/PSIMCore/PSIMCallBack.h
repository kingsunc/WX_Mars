#pragma once
#include "PSDefs.h"

class CPSIMCallBack
{
public:
	CPSIMCallBack() {};
	virtual ~CPSIMCallBack() {};

	// 登录-回调处理;
	virtual void OnMsgLoginResponse(const PSMsgLoginResp& resp) = 0;
	// 注销-回调处理;
	virtual void OnMsgLogoutResponse(const PSMsgLoginResp& resp) = 0;
	// 被迫踢出-回调处理;
	virtual void OnKickOutResponse(const PSKickOutResp& resp) = 0;

	// 创建群-回调处理;
	virtual void OnCreateGroupResponse(const PSCreateGroupResp& resp) = 0;
	// 删除群-回调处理;
	virtual void OnDeleteGroupResponse(const PSDeleteGroupResp& resp) = 0;

	// 添加群成员-回调处理;
	virtual void OnAddGroupUsersResponse(const PSAddGroupUsersResp& resp) = 0;
	// 移除群成员-回调处理;
	virtual void OnRemoveGroupUsersResponse(const PSRemoveGroupUsersResp& resp) = 0;

	// 添加子群-回调处理;
	virtual void OnAddGroupChildsResponse(const PSAddGroupChildsResp& resp) = 0;
	// 移除子群-回调处理;
	virtual void OnRemoveGroupChildsResponse(const PSRemoveGroupChildsResp& resp) = 0;

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const PSSendMsgResp& respMsg) = 0;

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgResponse(const PSOffMsgResp& resp) = 0;

	// 接收消息-回调处理;
	virtual void OnRecvMessageResponse(const PSMessageItem& resp) = 0;

	// 接收离线消息描述-回调处理;
	virtual void OnRecvOffMsgNoticeResponse(const PSOffMsgInfoNotice& resp) = 0;
};