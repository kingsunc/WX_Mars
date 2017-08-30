#pragma once
#include "PSIMCall.h"

class CPSIMDemoCallBack : public CPSIMCallBack
{
public:
	CPSIMDemoCallBack();
	~CPSIMDemoCallBack();

	// 登录-回调处理;
	virtual void OnMsgLoginResponse(const PSMsgLoginResp& resp);
	// 注销-回调处理;
	virtual void OnMsgLogoutResponse(const PSMsgLoginResp& resp);
	// 被迫下线-回调处理;
	virtual void OnKickOutResponse(const PSKickOutResp& resp);

	// 创建群-回调处理;
	virtual void OnCreateGroupResponse(const PSCreateGroupResp& resp);
	// 删除群-回调处理;
	virtual void OnDeleteGroupResponse(const PSDeleteGroupResp& resp);

	// 添加群成员-回调处理;
	virtual void OnAddGroupUsersResponse(const PSAddGroupUsersResp& resp);
	// 移除群成员-回调处理;
	virtual void OnRemoveGroupUsersResponse(const PSRemoveGroupUsersResp& resp);

	// 添加子群-回调处理;
	virtual void OnAddGroupChildsResponse(const PSAddGroupChildsResp& resp);
	// 移除子群-回调处理;
	virtual void OnRemoveGroupChildsResponse(const PSRemoveGroupChildsResp& resp);

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const PSSendMsgResp& msgResp);

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgResponse(const PSOffMsgResp& resp);

	// 接收消息-回调处理;
	virtual void OnRecvMessageResponse(const PSMessageItem& resp);

	// 接收离线消息描述-回调处理;
	virtual void OnRecvOffMsgNoticeResponse(const PSOffMsgInfoNotice& resp);
};