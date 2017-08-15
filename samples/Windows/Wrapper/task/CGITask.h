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
*  CGITask.h
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#ifndef _CGI_TASK_H_
#define _CGI_TASK_H_

#include <map>
#include <string>
#include "mars/comm/autobuffer.h"
#include "PSDefs.h"

#define NO_APP_SERVER		// 暂时没有业务服务器;

// 通道类型;
enum ChannelType 
{
	ChannelType_ShortConn				= 1,		// 短连接 http;
	ChannelType_LongConn				= 2,		// 长连接 tcp;
	ChannelType_All						= 3			// 长短连接全支持;
};

// 命令类型;
enum MsgCmd
{
	MSGCMD_BOTH_INVALID					= -2,		// 无效;
	MSGCMD_BOTH_UNKNOWN					= -1,		// 未知;
	MSGCMD_BOTH_PING					= 0,		// 连接保活

	MSGCMD_C2S_LOGIN_REQ				= 1,		// 客户端登录
	MSGCMD_S2C_LOGIN_RESP				= 2,		// 服务器返回登录响应
	MSGCMD_BOTH_LOGIN					= 3,		// 客户端或者服务器退出

	MSGCMD_C2S_CREATE_GROUP_REQ			= 6,		// 请求创建一个群
	MSGCMD_S2C_CREATE_GROUP_RESP		= 7,		// 创建群的响应
	MSGCMD_C2S_DELETE_GROUP_REQ			= 8,		// 请求删除一个群
	MSGCMD_S2C_DELETE_GROUP_RESP		= 9,		// 删除群的响应

	MSGCMD_C2S_ADD_GROUPUSER_REQ		= 10,		// 在group中添加用户的请求
	MSGCMD_S2C_ADD_GROUPUSER_RESP		= 11,		// 在group中添加用户的响应
	MSGCMD_C2S_REMOVE_GROUPUSER_REQ		= 12,		// 在group中移除用户的请求
	MSGCMD_S2C_REMOVE_GROUPUSER_RESP	= 13,		// 在group中移除用户的响应

	MSGCMD_C2S_ADD_SUBGROUP_REQ			= 14,		// 在群中添加子群请求
	MSGCMD_S2C_ADD_SUBGROUP_RESP		= 15,		// 在群中添加子群响应
	MSGCMD_C2S_REMOVE_SUBGROUP_REQ		= 16,		// 移除群中子群请求
	MSGCMD_S2C_REMOVE_SUBGROUP_RESP		= 17,		// 移除群中子群响应

	MSGCMD_C2S_SEND_MESSAGE_REP			= 18,		// 客户端向服务器发送消息的请求
	MSGCMD_S2C_SEND_MESSAGE_RESP		= 19,		// 客户端向服务器发送消息的响应
	MSGCMD_S2C_RECV_MESSAGE_REP			= 20,		// 服务器将消息转发给客户端

	MSGCMD_S2C_HISTORY_INFO				= 23,		// 服务器告知客户端历史信息情况
	MSGCMD_C2S_HISTORY_REQ				= 24,		// 获取历史消息
	MSGCMD_S2C_HISTORY_RESP				= 25,		// 服务器发送历史信息响应

	MSGCMD_C2S_WITHDRAW_REQ				= 34,		// 收回消息请求
	MSGCMD_S2C_WITHDRAW_RESP			= 35,		// 服务器发送收回消息响应
	MSGCMD_S2C_WITHDRAW					= 36,		// 服务器发送收回消息通知

	MSGCMD_C2S_NODISTURB_REQ			= 38,		// 设置免打扰请求
	MSGCMD_S2C_NODISTURB_RESP			= 39,		// 设置免打扰响应

	MSGCMD_BOTH_RECEIPT					= 50,		// 已读回执
	MSGCMD_C2S_PRESENCE_REQ				= 70,		// 用户在线状态查询
	MSGCMD_S2C_PRESENCE_RESP			= 71,		// 用户在线状态查询响应

	MSGCMD_BOTH_HANDSHAKE				= 10000,	// 握手;
	MSGCMD_S2C_PUSH						= 10001		// 服务器推送给客户端;
};

// 任务基类;
class CGITask
{
public:
	CGITask() {};
	virtual ~CGITask() {};
	
	// 请求数据->buff;
	virtual bool Req2Buf(IN uint32_t _taskid, IN void* const _user_context, OUT AutoBuffer& _outbuffer, OUT AutoBuffer& _extend, OUT int& _error_code, IN const int _channel_select) = 0;
	// buff->响应数据;
	virtual int Buf2Resp(IN uint32_t _taskid, IN void* const _user_context, IN const AutoBuffer& _inbuffer, IN const AutoBuffer& _extend, IN int& _error_code, IN const int _channel_select) = 0;

	uint32_t		taskid_;
	ChannelType		channel_select_;
	uint32_t		cmdid_;
	std::string		cgi_;
	std::string		host_;
};

#endif