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

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

// 通道类型;
enum ChannelType 
{
	ChannelType_ShortConn	= 1,		// 短连接 http;
	ChannelType_LongConn	= 2,		// 长连接 tcp;
	ChannelType_All			= 3			// 长短连接全支持;
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

	uint32_t taskid_;
	ChannelType channel_select_;
	uint32_t cmdid_;
	std::string cgi_;
	std::string host_;
};

#endif