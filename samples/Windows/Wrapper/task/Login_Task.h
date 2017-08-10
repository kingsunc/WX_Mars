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
*  HelloCGITask.h
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#ifndef _HELLO_CGI_TASK_H_
#define _HELLO_CGI_TASK_H_

#include "task/CGITask.h"
#include "mars/boost/weak_ptr.hpp"
#include "../idl/tars/request.h"

class Login_Task;

// Login任务回调;
class Login_Callback
{
public:
	virtual void OnResponse(Login_Task* task, MessageService::LoginResp& response) = 0;
};

// Hello任务;
class Login_Task : public CGITask 
{
public:
	virtual bool Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select);
	virtual int Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select);

	std::string strAppID;
	std::string strAppToken;
	std::string strUserID;
	std::string strUserName;
	int iDeviceType;
	std::string strDeviceToken;

	Login_Callback* pCallback;
};

#endif