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
	void MsgLogin(const char* strAppID, const char* strAppToken, const char* strUserID, const char* strUserName, const int iDeviceType, const char* strDeviceToken, Login_Callback* pCallback);
	// 注销
	void MsgLogout();

	//// 客户端请求;
	//void sendChatMsg(const ChatMsg& _chat_msg);
	//void pingServer(const std::string& _name, const std::string& _text, boost::weak_ptr<HelloCGICallback> _callback);
	//void getConversationList(boost::weak_ptr<GetConvListCGICallback> _callback);

protected:
	virtual void OnPush(uint64_t _channel_id, uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend);

private:
	MarsWrapper();
};

#endif