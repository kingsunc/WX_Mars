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
#include "task/HelloCGITask.h"
#include "task/ChatCGITask.h"
#include "task/GetConvListCGITask.h"

struct ChatMsg
{
	std::string topic_; 
	std::string from_;
	std::string content_;
};

class ChatMsgObserver
{
public:
	virtual void OnRecvChatMsg(const ChatMsg& msg) = 0;
};

// 业务包装类;
class MarsWrapper : public PushObserver
{
public:
	// 单例 非线程安全;
	static MarsWrapper& Instance();
	// 设置回调类;
	void setChatMsgObserver(IN ChatMsgObserver* _observer);
	void start();

	virtual void OnPush(uint64_t _channel_id, uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend);

	// 客户端请求;
	void sendChatMsg(const ChatMsg& _chat_msg);
	void pingServer(const std::string& _name, const std::string& _text, boost::weak_ptr<HelloCGICallback> _callback);
	void getConversationList(boost::weak_ptr<GetConvListCGICallback> _callback);

protected:
	MarsWrapper();
	ChatMsgObserver* chat_msg_observer_;
};

#endif