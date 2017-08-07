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
#include "HelloCGITask.h"
#include "mars/stn/stn_logic.h"
#include "../request/RequestF.h"
#include "../request/Tmtp.h"

using namespace std;

bool HelloCGITask::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	/*string data;
	com::tencent::mars::sample::proto::HelloRequest request;
	request.set_user(user_);
	request.set_text(text_);
	request.SerializeToString(&data);
	_outbuffer.AllocWrite(data.size());
	_outbuffer.Write(data.c_str(), data.size());

	string sendBuffer;
	tars::RequestPacket req;
	req.iVersion = 1;
	req.cPacketType = 2;
	req.iMessageType = 3;
	req.iRequestId = 4;
	req.sServantName = "5";
	req.sFuncName = "6";
	req.sBuffer.push_back('7');
	req.iTimeout = 1000;
	req.context.clear();
	req.status.clear();*/

	//MessageService::LoginReq req;
	//req.appId = "001";
	//req.userId = "001:1";
	//req.userName = "test";
	//req.token = "sdfasldkfasldk21k22212121212121f11212121";
	//req.deviceType = 1;
	//req.deviceToken = "ssdfsd";

	//tars::TarsOutputStream<tars::BufferWriter> os;
	//req.writeTo(os);
	//int iLen = os.getLength();
	//_outbuffer.AllocWrite(iLen);
	//_outbuffer.Write(os.getBuffer(), iLen);

	return true;
}
int HelloCGITask::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	/*com::tencent::mars::sample::proto::HelloResponse response;
	response.ParseFromArray(_inbuffer.Ptr(), _inbuffer.Length());
	if (callback_.lock())
	{
		callback_.lock()->OnResponse(this, response);
	}*/

	//tars::TarsInputStream<tars::BufferReader> is;
	//is.setBuffer((const char*)(_inbuffer.Ptr()), _inbuffer.Length());

	////MessageService::LoginReq req;
	//tars::RequestPacket req;
	//req.readFrom(is);

	return mars::stn::kTaskFailHandleNoError;
}