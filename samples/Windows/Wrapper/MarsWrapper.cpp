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
*  MarsWrapper.cpp
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#include "MarsWrapper.h"
#include "mars/comm/md5.h"

//static const char* g_host = "marsopen.cn";

//static const char* g_host = "127.0.0.1";
static const char* g_host = "172.88.1.192";

static const unsigned short g_shortlink_port = 1080;
//static const unsigned short g_longlink_port = 1081;
static const unsigned short g_longlink_port = 20001;

MarsWrapper& MarsWrapper::GetInstance()
{
	static MarsWrapper instance_;
	return instance_;
}

MarsWrapper::MarsWrapper()
{
}

void MarsWrapper::OnPush(uint64_t _channel_id, uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend)
{
	int i = 0;
	/*com::tencent::mars::sample::chat::proto::MessagePush msg;
	msg.ParseFromArray(_body.Ptr(), _body.Length());
	if (chat_msg_observer_)
	{
		ChatMsg chat_msg;
		chat_msg.topic_ = msg.topic();
		chat_msg.from_ = msg.from();
		chat_msg.content_ = msg.content();
		chat_msg_observer_->OnRecvChatMsg(chat_msg);
	}*/
}

void MarsWrapper::Start()
{
	NetworkService::GetInstance().setClientVersion(1);
	NetworkService::GetInstance().setShortLinkDebugIP(g_host, g_shortlink_port);
	NetworkService::GetInstance().setLongLinkAddress(g_host, g_longlink_port, "");
	NetworkService::GetInstance().Start();	
}

void MarsWrapper::MsgLogin(const char* strAppID, const char* strAppToken, const char* strUserID, const char* strUserName, const int iDeviceType, const char* strDeviceToken, Login_Callback* pCallback)
{
	std::string strToken;
#ifdef NO_APP_SERVER
	string strNowTime = std::to_string(time(NULL) + 3600);
	string strPwd = "mypassword";	// psm password
	std::string strInput = strPwd + strAppID + strUserID + strNowTime;

	unsigned char sig[16] = { 0 };
	MD5_buffer(strInput.c_str(), (unsigned int)strInput.length(), sig);
	char strDest[33] = { 0 };
	MD5_sig_to_string((const char*)sig, strDest);

	strToken.append(strDest);
	strToken.append(strNowTime);
#else
	strToken.append(strAppToken);
#endif

	Login_Task* pTask = new Login_Task();
	pTask->strAppID = strAppID;
	pTask->strAppToken = strToken;
	pTask->strUserID = strUserID;
	pTask->strUserName = strUserName;
	pTask->iDeviceType = iDeviceType;
	pTask->strDeviceToken = strDeviceToken;
	pTask->pCallback = pCallback;

	pTask->channel_select_ = ChannelType_LongConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_C2S_LOGIN_REQ;
	pTask->cgi_ = "/psmsg/login";
	pTask->host_ = g_host;
	NetworkService::GetInstance().StartTask(pTask);
}

// ×¢Ïú
void MarsWrapper::MsgLogout()
{

}

//void MarsWrapper::pingServer(const std::string& _name, const std::string& _text, boost::weak_ptr<HelloCGICallback> _callback)
//{
//	HelloCGITask* task = new HelloCGITask();
//	task->user_ = _name;
//	task->text_ = _text;
//	task->callback_ = _callback;
//
//	//task->channel_select_ = ChannelType_All;
//	task->channel_select_ = ChannelType_LongConn;
//	//task->cmdid_ = com::tencent::mars::sample::proto::CMD_ID_HELLO;
//	task->cgi_ = "/mars/hello";
//	task->host_ = g_host;
//	NetworkService::Instance().startTask(task);
//}
//

//void MarsWrapper::sendChatMsg(const ChatMsg& _chat_msg)
//{
//	ChatCGITask* task = new ChatCGITask();
//	task->channel_select_ = ChannelType_LongConn;
//	//task->cmdid_ = com::tencent::mars::sample::proto::CMD_ID_SEND_MESSAGE;
//	task->cgi_ = "/mars/sendmessage";
//	task->host_ = g_host;
//	task->text_ = _chat_msg.content_;
//
//	task->user_ = _chat_msg.from_;
//	task->to_ = "all";
//	task->access_token_ = "123456";
//	task->topic_ = _chat_msg.topic_;
//
//	NetworkService::Instance().startTask(task);
//}
//void MarsWrapper::getConversationList(boost::weak_ptr<GetConvListCGICallback> _callback)
//{
//	GetConvListCGITask* task = new GetConvListCGITask();
//	task->channel_select_ = ChannelType_ShortConn;
//	//task->cmdid_ = com::tencent::mars::sample::proto::CMD_ID_CONVERSATION_LIST;
//	task->cgi_ = "/mars/getconvlist";
//	task->host_ = g_host;
//	task->access_token_ = "";
//	task->callback_ = _callback;
//	NetworkService::Instance().startTask(task);
//}