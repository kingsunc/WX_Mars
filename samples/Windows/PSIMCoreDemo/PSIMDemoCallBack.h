#pragma once
#include "PSIMCall.h"

class CPSIMDemoCallBack : public CPSIMCallBack
{
public:
	CPSIMDemoCallBack();
	~CPSIMDemoCallBack();

	// 登录-回调处理;
	virtual void OnMsgLoginResponse(const PSMsgLoginResp& respMsgLogin);
	// 注销-回调处理;
	virtual void OnMsgLogoutResponse(const PSMsgLoginResp& respMsgLogout);
	// 被迫踢出-回调处理;
	virtual void OnKickOutResponse(const PSKickOutResp& respKickOut);

	// 创建群-回调处理;
	virtual void OnCreateGroupResponse(const PSCreateGroupResp& respCreateGroup);
	// 删除群-回调处理;
	virtual void OnDeleteGroupResponse(const PSDeleteGroupResp& respDeleteeGroup);

	// 添加群成员-回调处理;
	virtual void OnAddGroupUsersResponse(const PSAddGroupUsersResp& respAddGroupUsers);
	// 移除群成员-回调处理;
	virtual void OnRemoveGroupUsersResponse(const PSRemoveGroupUsersResp& respRemoveGroupUsers);

	// 添加子群-回调处理;
	virtual void OnAddGroupChildsResponse(const PSAddGroupChildsResp& respAddGroupChilds);
	// 移除子群-回调处理;
	virtual void OnRemoveGroupChildsResponse(const PSRemoveGroupChildsResp& respRemoveGroupChilds);

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const PSMsgResp& msgResp);

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgResponse(const int& iCode, const char* strInfo);

	virtual void OnRecvMessage(const PSMessageItem& msgItem);
};