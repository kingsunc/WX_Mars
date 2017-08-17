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

MarsWrapper::MarsWrapper(): m_pMsgPush(nullptr)
{
}

void MarsWrapper::OnPush(uint64_t _channel_id, uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend)
{
	tars::TarsInputStream<tars::BufferReader> inStream;
	inStream.setBuffer((const char*)(_body.Ptr()), _body.Length());

	MessageService::Message response;
	response.readFrom(inStream);

	MessageItem msgItem;
	msgItem.iMsgId = response.msgId;
	msgItem.strFrom = (char*)response.from.c_str();
	msgItem.strTo = (char*)response.to.c_str();
	msgItem.iSendMode = response.sendMode;
	msgItem.iType = response.type;
	msgItem.iPriority = response.priority;
	msgItem.iHandleOption = response.handleOption;
	msgItem.strPushInfo = (char*)response.pushInfo.c_str();
	msgItem.iTimestamp = response.timestamp;
	msgItem.iExpireTime = response.expireTime;
	{
		const int iLen = response.content.size();
		msgItem.psBuff.pBuff = new char[iLen + 1];
		memset(msgItem.psBuff.pBuff, 0, (iLen + 1) * sizeof(char));
		for (int i = 0; i < iLen; i++)
		{
			msgItem.psBuff.pBuff[i] = response.content[i];
		}
		msgItem.psBuff.iLen = iLen;
	}

	if (m_pMsgPush)
	{
		m_pMsgPush->OnRecvMessage(msgItem);
	}
}

void MarsWrapper::Start()
{
	NetworkService::GetInstance().setClientVersion(1);
	NetworkService::GetInstance().setShortLinkDebugIP(g_host, g_shortlink_port);
	NetworkService::GetInstance().setLongLinkAddress(g_host, g_longlink_port, "");
	NetworkService::GetInstance().Start();	

	NetworkService::GetInstance().SetPushObserver(MSGCMD_S2C_RECV_MESSAGE_REP, this);
}

void MarsWrapper::SetMsgPushObserver(MessagePush* pMsgPush)
{
	m_pMsgPush = pMsgPush;
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
	NoBody_Task* pTask = new NoBody_Task();

	pTask->channel_select_ = ChannelType_LongConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_BOTH_LOGOUT;
	pTask->cgi_ = "/psmsg/logout";
	pTask->host_ = g_host;
	NetworkService::GetInstance().StartTask(pTask);
}

bool MarsWrapper::SendTextMessage(OUT int& iReqID,
	IN const PS_SendMode& eSendMode,
	IN const char* strFrom,
	IN const char* strTo,
	IN const char* strContent,
	IN const int& iContentLen,
	IN const char* strPushInfo,
	IN Msg_Callback* pCallback)
{
	if ((!strFrom) || (!strTo) || (!strContent) ||
		(0 == strlen(strFrom)) || 
		(0 == strlen(strTo)) ||
		(0 == strlen(strContent)) )
	{
		return false;
	}

	Msg_Task* pTask = new Msg_Task();
	pTask->from = strFrom;
	pTask->to = strTo;
	pTask->pushInfo = strPushInfo;
	pTask->sendMode = eSendMode;
	pTask->type = PS_MessageType_Text;
	pTask->priority = 0;
	for (int i = 0; i < iContentLen; i++)
	{
		pTask->content.push_back(strContent[i]);
	}
	pTask->handleOption = PS_SendOption_OfflineSave + PS_SendOption_IosPush;
	pTask->pCallback = pCallback;

	pTask->channel_select_ = ChannelType_LongConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_C2S_SEND_MESSAGE_REP;
	pTask->cgi_ = "/psmsg/msg";
	pTask->host_ = g_host;
	NetworkService::GetInstance().StartTask(pTask);

	iReqID = pTask->taskid_;
	return true;
}

void MarsWrapper::GetOfflineMsgs(OUT std::vector<PS_OffMsgDesc_t>& vecMsgDesc,
	IN OffMsg_Callback* pCallback)
{
	OffMsg_Task* pTask = new OffMsg_Task();
	pTask->vecMsgDesc = vecMsgDesc;
	pTask->pCallback = pCallback;

	pTask->channel_select_ = ChannelType_LongConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_C2S_HISTORY_REQ;
	pTask->cgi_ = "/psmsg/offmsg";
	pTask->host_ = g_host;
	NetworkService::GetInstance().StartTask(pTask);
}