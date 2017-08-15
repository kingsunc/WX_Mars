// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

/*
*  MarsWrapper.h
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#ifndef _MARS_WRAPPER_H_
#define _MARS_WRAPPER_H_

#include "NetworkObserver.h"
#include "NetworkService.h"
#include "task/Login_Task.h"
#include "task/Msg_Task.h"
#include "task/OffMsg_Task.h"

// 业务包装类;
class MarsWrapper
{
public:
	// 单例 非线程安全;
	static MarsWrapper& GetInstance();
	// 启动;
	void Start();

	// 客户端请求;
	// 登录
	void MsgLogin(OUT const char* strAppID, 
		IN const char* strAppToken,
		IN const char* strUserID,
		IN const char* strUserName,
		IN const int iDeviceType,
		IN const char* strDeviceToken,
		IN Login_Callback* pCallback);

	// 注销
	void MsgLogout();

	//// 获取群信息;
	//virtual void GetGroupInfo(const char* strGroupID);

	//// 获取群成员;
	//virtual void GetGroupUsers(const char* strGroupID, const int iPageNum, const int iPageSize);
	//// 添加群成员;
	//virtual void AddGroupUsers(const char* strGroupID);
	//// 添加群成员;
	//virtual void DeleteGroupUsers(const char* strGroupID);

	//// 设置群成员角色
	//virtual void SetGroupUserRole(const char* strGroupID);

	//// 禁言
	//virtual void Shutup(const char* strGroupID);
	//// 解禁
	//virtual void UnShutup(const char* strGroupID);
	//// 获取禁言列表
	//virtual void GetShutupList(const char* strGroupID);

	//// 邀请群成员
	//virtual void InviteGroupUsers(const char* strGroupID);

	// 发送文本消息
	virtual void SendTextMessage(OUT int& iReqID,
		IN const PS_SendMode& eSendMode,
		IN const char* strFrom,
		IN const char* strTo,
		IN const char* strContent,
		IN const int& iContentLen,
		IN const char* strPushInfo,
		IN Msg_Callback* pCallback);

	// 获取离线消息
	virtual void GetOfflineMsgs(OUT std::vector<PS_OffMsgDesc_t>& vecMsgDesc,
		IN OffMsg_Callback* pCallback);

	// 消息撤回
	//virtual void RevokeMsg();

protected:
	virtual void OnPush(uint64_t _channel_id, uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend);

private:
	MarsWrapper();
};

#endif