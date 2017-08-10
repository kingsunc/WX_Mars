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
*  HelloCGITask.cpp
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#include <mars/comm/windows/projdef.h>
#include "Login_Task.h"
#include "mars/stn/stn_logic.h"

using namespace std;

bool Login_Task::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	MessageService::LoginReq req;
	req.appId = strAppID;
	req.userId = strUserID;
	req.userName = strUserName;
	req.token = strAppToken;
	req.deviceType = iDeviceType;
	req.deviceToken = strDeviceToken;

	tars::TarsOutputStream<tars::BufferWriter> outStream;
	req.writeTo(outStream);
	int iLen = outStream.getLength();
	_outbuffer.AllocWrite(iLen);
	_outbuffer.Write(outStream.getBuffer(), iLen);

	return true;
}

int Login_Task::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	tars::TarsInputStream<tars::BufferReader> inStream;
	inStream.setBuffer((const char*)(_inbuffer.Ptr()), _inbuffer.Length());

	MessageService::LoginResp response;
	response.readFrom(inStream);

	if (pCallback)
	{
		pCallback->OnResponse(this, response);
	}

	return mars::stn::kTaskFailHandleNoError;
}