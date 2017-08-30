#include "PSIMCallConcrete.h"
#include "PSIMTaskCallback.h"
#include "xlogger/xlogger.h"
#include "log/appender.h"

CPSIMCallConcrete::CPSIMCallConcrete()
{
}

CPSIMCallConcrete::CPSIMCallConcrete(CPSIMCallBack* pPSIMCallBack)
{
	m_pPSIMCallBack = pPSIMCallBack;
}

CPSIMCallConcrete::~CPSIMCallConcrete()
{
}

CPSIMCallBack* CPSIMCallConcrete::GetIMPSCallBack()
{
	return m_pPSIMCallBack;
}

// 初始化;
bool CPSIMCallConcrete::Init()
{
	// init xlog
	std::string logPath = "D://Log";	//use your log path
	std::string pubKey = "aaa";			//use you pubkey for log encrypt						 

	xlogger_SetLevel(kLevelAll);
	//xlogger_SetLevel(kLevelInfo);
	//xlogger_SetLevel(kLevelWarn);
	appender_set_console_log(true);
	appender_open(kAppednerAsync, logPath.c_str(), "Test", pubKey.c_str());

	MarsWrapper::GetInstance().Start();
	MarsWrapper::GetInstance().SetMsgPushObserver(CPSIMTaskCallback::GetInstance());

	return true;
}

// 反初始化;
bool CPSIMCallConcrete::UnInit()
{
	CPSIMTaskCallback::ReleaseInstance();

	// uninit xlog
	appender_close();

	MarsWrapper::GetInstance().Exit();

	return true;
}

// 登录
void CPSIMCallConcrete::MsgLogin(IN const char* strAppID,
	IN const char* strAppToken,
	IN const char* strUserID,
	IN const char* strUserName,
	IN const int iDeviceType,
	IN const char* strDeviceToken)
{
	try
	{
		PSMsgLoginResp resp;
		resp.iStatus = PSResult_ParaError;
		if (!strAppID)
		{
			resp.strMessage = "appid is null";
			throw resp;
		}
		if (0 == strlen(strAppID))
		{
			resp.strMessage = "appid is empty";
			throw resp;
		}

		if (!strAppToken)
		{
			resp.strMessage = "apptoken is null";
			throw resp;
		}
		if (0 == strlen(strAppToken))
		{
			resp.strMessage = "apptoken is empty";
			throw resp;
		}

		if (!strUserID)
		{
			resp.strMessage = "userid is null";
			throw resp;
		}
		if (0 == strlen(strUserID))
		{
			resp.strMessage = "userid is empty";
			throw resp;
		}

		switch (iDeviceType)
		{
		case PS_DeviceType_Android:
		case PS_DeviceType_Ios:
			{
				if (!strDeviceToken)
				{
					resp.strMessage = "devicetoken is null";
					throw resp;
				}
				if (0 == strlen(strDeviceToken))
				{
					resp.strMessage = "devicetoken is empty";
					throw resp;
				}
			}
			break;
		case PS_DeviceType_Windows:
			break;
		default:
			{
				resp.strMessage = "device type is not support";
				throw resp;
			}
			break;
		}

		MarsWrapper::GetInstance().MsgLogin(strAppID, strAppToken, strUserID, strUserName, iDeviceType, strDeviceToken, CPSIMTaskCallback::GetInstance());
	}
	catch (PSMsgLoginResp& resp)
	{
		if (m_pPSIMCallBack)
		{
			m_pPSIMCallBack->OnMsgLoginResponse(resp);
		}
	}
}

// 注销
void CPSIMCallConcrete::MsgLogout()
{
	MarsWrapper::GetInstance().MsgLogout();
}

// 创建群组;
void CPSIMCallConcrete::CreateGroup(const PSGroupInfo& groupInfo)
{
	MarsWrapper::GetInstance().CreateGroup(groupInfo, CPSIMTaskCallback::GetInstance());
}

// 删除群;
void CPSIMCallConcrete::DeleteGroup(IN const char* strGroupID)
{
	MarsWrapper::GetInstance().DeleteGroup(strGroupID, CPSIMTaskCallback::GetInstance());
}

//void CPSIMCallConcrete::GetGroupUsers(IN const PSGroupInfo& groupUsers)
//{
//
//}

// 获取群成员;
//void CPSIMCallConcrete::GetGroupUsers(const char* strGroupID, const int iPageNum, const int iPageSize)
//{
//
//}

// 添加群成员;
void CPSIMCallConcrete::AddGroupUsers(IN const char* strGroupID, IN const PSUserInfo* pUsers, IN const int iAddCount)
{
	MarsWrapper::GetInstance().AddGroupUsers(strGroupID, pUsers, iAddCount, CPSIMTaskCallback::GetInstance());
}

// 移除群成员;
void CPSIMCallConcrete::RemoveGroupUsers(IN const char* strGroupID, IN const PSUserInfo* pUsers, IN const int iRemoveCount)
{
	//return MarsWrapper::GetInstance().RemoveGroupUsers(strGroupID, pUsers, iRemoveCount, CPSIMTaskCallback::GetInstance());
}

// 添加子群;
void CPSIMCallConcrete::AddGroupChilds(IN const char* strGroupID, IN const PSGroupInfo* pGroups, IN const int iAddCount)
{
}

// 移除子群;
void CPSIMCallConcrete::RemoveGroupUsers(IN const char* strGroupID, IN const PSGroupInfo* pUsers, IN const int iRemoveCount)
{
}

// 设置群成员角色
void CPSIMCallConcrete::SetGroupUserRole(const char* strGroupID)
{
}

// 禁言
void CPSIMCallConcrete::Shutup(const char* strGroupID)
{

}

// 解禁
void CPSIMCallConcrete::UnShutup(const char* strGroupID)
{

}

// 获取禁言列表
void CPSIMCallConcrete::GetShutupList(const char* strGroupID)
{

}

// 邀请群成员
void CPSIMCallConcrete::InviteGroupUsers(const char* strGroupID)
{

}

// 发送文本消息
void CPSIMCallConcrete::SendTextMessage(OUT int& iReqID,
	IN const PS_SendMode& eSendMode,
	IN const char* strFrom,
	IN const char* strTo,
	IN const PSString& strContent,
	IN const char* strPushInfo)
{
	MarsWrapper::GetInstance().SendTextMessage(iReqID, eSendMode, strFrom, strTo, strContent.GetString(), strContent.GetLength(), strPushInfo, CPSIMTaskCallback::GetInstance());
}

// 获取离线消息;
void CPSIMCallConcrete::GetOfflineMsgs(IN const PSVector<PSOffMsgDesc>& vecOffMsgDescs)
{
	try
	{
		PSOffMsgResp resp;
		resp.iStatus = PSResult_ParaError;
		if (vecOffMsgDescs.size() <= 0)
		{
			resp.strMessage = "vecor size is 0";
			throw resp;
		}

		std::vector<PSOffMsgDesc> vecMsgDesc;
		for (int i = 0; i < vecOffMsgDescs.size(); i++)
		{
			vecMsgDesc.push_back(vecOffMsgDescs[i]);
		}
		MarsWrapper::GetInstance().GetOfflineMsgs(vecMsgDesc, CPSIMTaskCallback::GetInstance());
	}
	catch (PSMsgLoginResp& resp)
	{
		if (m_pPSIMCallBack)
		{
			m_pPSIMCallBack->OnMsgLoginResponse(resp);
		}
	}
}

// 消息撤回
void CPSIMCallConcrete::RevokeMsg()
{
}