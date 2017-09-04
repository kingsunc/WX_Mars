#pragma once
#include <stdio.h>
#include "PSIMCall.h"

class CPSIMDemoCallBack : public CPSIMCallBack
{
public:
	CPSIMDemoCallBack();
	~CPSIMDemoCallBack();

	// 登录-回调处理;
	virtual void OnMsgLoginResponse(const PSResp& resp) {};
	// 注销-回调处理;
	virtual void OnMsgLogoutResponse(const PSResp& resp) {};
	// 被迫下线-回调处理;
	virtual void OnKickOutResponse(const PSResp& resp) {};

	// 创建群-回调处理;
	virtual void OnCreateGroupResponse(const PSResp& resp) {};
	// 删除群-回调处理;
	virtual void OnDeleteGroupResponse(const PSResp& resp) {};
	// 修改群-回调处理;
	virtual void OnUpdateGroupResponse(const PSResp& resp) {};
	// 查询群-回调处理;
	virtual void OnGetGroupInfoResponse(const PSGetGroupInfoResp& resp) {};

	// 获取群子集-回调处理;
	virtual void OnGetGroupChildrensResponse(const PSGetGroupChildrensResp& resp) {};

	// 添加群成员-回调处理;
	virtual void OnAddGroupUsersResponse(const PSResp& resp) {};
	// 移除群成员-回调处理;
	virtual void OnRemoveGroupUsersResponse(const PSResp& resp) {};

	// 添加子群-回调处理;
	virtual void OnAddGroupChildsResponse(const PSResp& resp);
	// 移除子群-回调处理;
	virtual void OnRemoveGroupChildsResponse(const PSResp& resp);

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const PSSendMsgResp& msgResp) {};

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgsResponse(const PSOffMsgResp& resp) {};

	// 接收消息-回调处理;
	virtual void OnRecvMessageResponse(const PSMessageItem& resp) {};

	// 接收离线消息描述-回调处理;
	virtual void OnRecvOffMsgNoticeResponse(const PSOffMsgDescResp& resp) {};
};