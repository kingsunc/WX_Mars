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
static const char* g_longlink_host = "172.88.1.192";
static const char* g_shortlink_host = "172.88.1.192";

static const unsigned short g_shortlink_port = 8081;
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
	switch (_cmdid)
	{
	case MSGCMD_S2C_KICKOUT:
		{
			// 被迫下线;
			OnKickOut(_body);
		}
		break;
	case MSGCMD_S2C_RECV_MESSAGE_REP:
		{
			// 接收在线消息;
			OnRecvMessage(_body);
		}
		break;
	case MSGCMD_S2C_HISTORY_INFO:
		{
			// 接收离线消息描述;
			OnGetOffMsgInfoNotice(_body);
		}
		break;
	default:
		{
			printf("cmid: %d OnPush is not handle.", _cmdid);
		}
		break;
	}
}

// 被迫下线;
void MarsWrapper::OnKickOut(const AutoBuffer& _body)
{
	tars::TarsInputStream<tars::BufferReader> inStream;
	inStream.setBuffer((const char*)(_body.Ptr()), _body.Length());

	MessageService::Kickout response;
	response.readFrom(inStream);

	PSKickOutResp resp;
	memset(&resp, 0, sizeof(resp));
	resp.iStatus = response.code;
	switch (resp.iStatus)
	{
	case MessageService::KICKOUT_REASON_REPEAT:
		{
			resp.strMessage = "login_repeat";
		}
		break;
	case MessageService::KICKOUT_REASON_TOKEN_TIMEOUT:
		{
			resp.strMessage = "token_timeout";
		}
		break;
	case MessageService::KICKOUT_REASON_CLIENT_UNNORMAL:
		{
			resp.strMessage = "client_unnormal";
		}
		break;
	case MessageService::KICKOUT_REASON_OUTSIDE:
		{
			resp.strMessage = "outside";
		}
		break;
	default:
		{
			resp.strMessage = "other_error";
		}
		break;
	}

	Exit();

	if (m_pMsgPush)
	{
		m_pMsgPush->OnKickOut(resp);
	}
}

// 接收消息;
void MarsWrapper::OnRecvMessage(const AutoBuffer& _body)
{
	tars::TarsInputStream<tars::BufferReader> inStream;
	inStream.setBuffer((const char*)(_body.Ptr()), _body.Length());

	MessageService::Message response;
	response.readFrom(inStream);

	PSMessageItem msgItem;
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
	// 内容拷贝;
	const int iLen = response.content.size();
	for (int i = 0; i < iLen; i++)
	{
		msgItem.strContent += response.content[i];
	}

	if (m_pMsgPush)
	{
		m_pMsgPush->OnRecvMessage(msgItem);
	}
}

// 接收离线消息通知;
void MarsWrapper::OnGetOffMsgInfoNotice(const AutoBuffer& _body)
{
	tars::TarsInputStream<tars::BufferReader> inStream;
	inStream.setBuffer((const char*)(_body.Ptr()), _body.Length());

	MessageService::OffMsgInfoNotice response;
	response.readFrom(inStream);
	vector<MessageService::OffMsgInfo>& msgInfos = response.msgInfos;

	PSOffMsgInfoNotice offmsgNotice;
	offmsgNotice.iStatus = PSResult_Success;
	offmsgNotice.strMessage = "";
	for (int i = 0; i < msgInfos.size(); i++)
	{
		PSOffMsgInfoNoticeItem offmsgNoticeItem;

		MessageService::MessageQueue& queue = msgInfos[i].queue;
		offmsgNoticeItem.offmsgDesc.strFrom = (char*)queue.from.c_str();
		offmsgNoticeItem.offmsgDesc.strTo = (char*)queue.to.c_str();
		offmsgNoticeItem.offmsgDesc.iSendMode = (PS_SendMode)queue.sendMode;
		offmsgNoticeItem.offmsgDesc.iStartMsgID = msgInfos[i].lastUserMsgId;
		offmsgNoticeItem.offmsgDesc.iEndMsgID = msgInfos[i].lastMsgId;

		vector<MessageService::Message>& messsages = msgInfos[i].messsages;
		for (int j = 0; j < messsages.size(); j++)
		{
			PSMessageItem msgItem;
			msgItem.iMsgId = messsages[j].msgId;
			msgItem.strFrom = (char*)messsages[j].from.c_str();
			msgItem.strTo = (char*)messsages[j].to.c_str();
			msgItem.iSendMode = messsages[j].sendMode;
			msgItem.iType = messsages[j].type;
			msgItem.iPriority = messsages[j].priority;
			msgItem.iHandleOption = messsages[j].handleOption;
			msgItem.strPushInfo = (char*)messsages[j].pushInfo.c_str();
			msgItem.iTimestamp = messsages[j].timestamp;
			msgItem.iExpireTime = messsages[j].expireTime;
			// 内容拷贝;
			const int iLen = messsages[j].content.size();
			for (int iIndex = 0; iIndex < iLen; iIndex++)
			{
				msgItem.strContent += messsages[j].content[iIndex];
			}

			offmsgNoticeItem.vecMessage.push_back(msgItem);
		}
		
		offmsgNotice.vecOffMsgNotice.push_back(offmsgNoticeItem);
	}

	if (m_pMsgPush)
	{
		m_pMsgPush->OnRecvOffMsgNotice(offmsgNotice);
	}
}

void MarsWrapper::Start()
{
	NetworkService::GetInstance().setClientVersion(1);
	NetworkService::GetInstance().setShortLinkDebugIP(g_shortlink_host, g_shortlink_port);
	NetworkService::GetInstance().setLongLinkAddress(g_longlink_host, g_longlink_port, "");
	NetworkService::GetInstance().Start();	

	NetworkService::GetInstance().SetPushObserver(MSGCMD_S2C_RECV_MESSAGE_REP, this);
	NetworkService::GetInstance().SetPushObserver(MSGCMD_S2C_HISTORY_INFO, this);
	NetworkService::GetInstance().SetPushObserver(MSGCMD_S2C_KICKOUT, this);
}

void MarsWrapper::Exit()
{
	NetworkService::GetInstance().Exit();
}

void MarsWrapper::SetMsgPushObserver(MessagePush* pMsgPush)
{
	m_pMsgPush = pMsgPush;
}

void MarsWrapper::MsgLogin(const char* strAppID, const char* strAppToken, const char* strUserID, const char* strUserName, const int iDeviceType, const char* strDeviceToken, Login_Callback* pCallback)
{
	m_appInfo.strAppID = strAppID;
	m_appInfo.strToken = strAppToken;
	m_appInfo.strUserID = strUserID;

	std::string strToken;
#ifdef NO_APP_SERVER
	string strEffectTime = std::to_string(time(NULL) + 3600);	 // 有效截至时间
	string strPwd = "mypassword";	// psm password
	std::string strInput = strPwd + strAppID + strUserID + strEffectTime;

	unsigned char sig[16] = { 0 };
	MD5_buffer(strInput.c_str(), (unsigned int)strInput.length(), sig);
	char strDest[33] = { 0 };
	MD5_sig_to_string((const char*)sig, strDest);

	strToken.append(strDest);
	strToken.append(strEffectTime);
#else
	strToken.append(strAppToken);
#endif

	Login_Task* pTask = new Login_Task();
	pTask->strAppID = (strAppID ? strAppID : "");
	pTask->strAppToken = strToken;
	pTask->strUserID = (strUserID ? strUserID : "");
	pTask->strUserName = (strUserName ? strUserName : "");
	pTask->iDeviceType = iDeviceType;
	pTask->strDeviceToken = (strDeviceToken ? strDeviceToken : "");
	pTask->pCallback = pCallback;

	pTask->channel_select_ = ChannelType_LongConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_C2S_LOGIN_REQ;
	pTask->cgi_ = "/psmsg/login";
	pTask->host_ = g_shortlink_host;
	NetworkService::GetInstance().StartTask(pTask);
}

// 注销
void MarsWrapper::MsgLogout()
{
	NoBody_Task* pTask = new NoBody_Task();

	pTask->channel_select_ = ChannelType_LongConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_BOTH_LOGOUT;
	pTask->cgi_ = "/psmsg/logout";
	pTask->host_ = g_shortlink_host;
	NetworkService::GetInstance().StartTask(pTask);
}

void MarsWrapper::CreateGroup(IN const PSGroupInfo& groupInfo, IN CreateGroup_Callback* pCallback)
{
	/*if ((!groupInfo.strGroupID) ||
		(0 == strlen(groupInfo.strGroupID)) )
	{
		return false;
	}*/
	char strUrl[256] = { 0 };
	snprintf(strUrl, sizeof(strUrl), "/group/create");

	CreateGroup_Task* pTask = new CreateGroup_Task();
	if (!groupInfo.strGroupID.IsEmpty())
	{
		pTask->m_strGroupID = groupInfo.strGroupID.GetString();
	}
	if (!groupInfo.strGroupName.IsEmpty())
	{
		pTask->m_strGroupName = groupInfo.strGroupName.GetString();
	}
	if (!groupInfo.strGroupDesc.IsEmpty())
	{
		pTask->m_strGroupDesc = groupInfo.strGroupDesc.GetString();
	}
	pTask->m_bPublic = groupInfo.bPublic;
	pTask->m_iMaxUsers = groupInfo.iMaxUsers;
	if (!groupInfo.strGroupOwner.IsEmpty())
	{
		pTask->m_strOwner = groupInfo.strGroupOwner.GetString();
	}
	for (int i = 0; i < groupInfo.vecAdmin.size(); i++)
	{
		pTask->m_vecAdmins.push_back(groupInfo.vecAdmin[i].strUserID.GetString());
	}
	for (int i = 0; i < groupInfo.vecMember.size(); i++)
	{
		pTask->m_vecMembers.push_back(groupInfo.vecMember[i].strUserID.GetString());
	}
	pTask->pCallback = pCallback;

	pTask->headers_[HEADER_APPID] = m_appInfo.strAppID;
	pTask->headers_[HEADER_TOKEN] = m_appInfo.strToken;
	char strSeqID[256] = { 0 };
	snprintf(strSeqID, sizeof(strSeqID), "%d", pTask->taskid_);
	pTask->headers_[HEADER_SEQID] = strSeqID;

	pTask->channel_select_ = ChannelType_ShortConn;
	//pTask->cmdid_ = MsgCmd::MSGCMD_C2S_CREATE_GROUP_REQ;
	pTask->cgi_ = strUrl;
	pTask->host_ = g_shortlink_host;
	NetworkService::GetInstance().StartTask(pTask);
}

void MarsWrapper::DeleteGroup(IN const char* strGroupID, IN DeleteGroup_Callback* pCallback)
{
	/*if ((!strGroupID) ||
		(0 == strlen(strGroupID)))
	{
		return false;
	}*/
	char strUrl[256] = { 0 };
	snprintf(strUrl, sizeof(strUrl), "group/del?group=%s", strGroupID);

	DeleteGroup_Task* pTask = new DeleteGroup_Task();
	pTask->strGroupID = strGroupID;
	pTask->pCallback = pCallback;

	pTask->headers_[HEADER_APPID] = m_appInfo.strAppID;
	pTask->headers_[HEADER_TOKEN] = m_appInfo.strToken;
	char strSeqID[256] = { 0 };
	snprintf(strSeqID, sizeof(strSeqID), "%d", pTask->taskid_);
	pTask->headers_[HEADER_SEQID] = strSeqID;

	pTask->channel_select_ = ChannelType_ShortConn;
	//pTask->cmdid_ = MsgCmd::MSGCMD_C2S_DELETE_GROUP_REQ;
	pTask->cgi_ = strUrl;
	pTask->host_ = g_shortlink_host;
	NetworkService::GetInstance().StartTask(pTask);
}

// 添加群成员;
void MarsWrapper::AddGroupUsers(IN const char* strGroupID, IN const PSUserInfo* userInfo, IN const int iAddCount, IN AddGroupUser_Callback* pCallback)
{
	//if ((!strGroupID) || (0 == strlen(strGroupID)) || 
	//	(!userInfo) || (iAddCount <= 0) )
	//{
	//	return false;
	//}
	std::string strMembers;
	for (int i = 0; i < iAddCount; i++)
	{
		strMembers.append(userInfo[i].strUserID.GetString()).append(",");
	}
	strMembers = strMembers.substr(0, strMembers.length() - 1);
	char strUrl[256] = { 0 };
	snprintf(strUrl, sizeof(strUrl), "/group/user?op=join&users=%s&group=%s", strMembers.c_str(), strGroupID);

	AddGroupUser_Task* pTask = new AddGroupUser_Task();
	/*pTask->strAppID = strAppID;
	pTask->strAppToken = strToken;
	pTask->strUserID = strUserID;
	pTask->strUserName = strUserName;
	pTask->iDeviceType = iDeviceType;
	pTask->strDeviceToken = strDeviceToken;*/
	pTask->pCallback = pCallback;

	pTask->channel_select_ = ChannelType_ShortConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_C2S_ADD_GROUPUSER_REQ;
	pTask->cgi_ = strUrl;
	pTask->host_ = g_shortlink_host;
	NetworkService::GetInstance().StartTask(pTask);
}

// 移除群成员;
void MarsWrapper::RemoveGroupUsers(IN const char* strGroupID, IN const PSUserInfo* userInfo, IN const int iRemoveCount)
{
}

void MarsWrapper::SendTextMessage(OUT int& iReqID,
	IN const PS_SendMode& eSendMode,
	IN const char* strFrom,
	IN const char* strTo,
	IN const char* strContent,
	IN const int& iContentLen,
	IN const char* strPushInfo,
	IN Msg_Callback* pCallback)
{
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
	pTask->host_ = g_shortlink_host;
	NetworkService::GetInstance().StartTask(pTask);

	iReqID = pTask->taskid_;
}

void MarsWrapper::GetOfflineMsgs(OUT std::vector<PSOffMsgDesc>& vecMsgDesc,
	IN OffMsg_Callback* pCallback)
{
	OffMsg_Task* pTask = new OffMsg_Task();
	/*for (int i = 0; i < vecMsgDesc.size(); i++)
	{
		pTask->vecMsgDesc.push_back(vecMsgDesc[i]);
	}*/
	pTask->vecMsgDesc = vecMsgDesc;
	pTask->pCallback = pCallback;

	pTask->channel_select_ = ChannelType_LongConn;
	pTask->cmdid_ = MsgCmd::MSGCMD_C2S_HISTORY_REQ;
	pTask->cgi_ = "/psmsg/offmsg";
	pTask->host_ = g_shortlink_host;
	NetworkService::GetInstance().StartTask(pTask);
}

