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

	return true;
}

// 登录
void CPSIMCallConcrete::MsgLogin(IN const char* strAppID,
	IN const char* strAppToken,
	IN const char* strUserID,
	IN const char* strUserName,
	IN const char* strDeviceToken)
{
	int iDeviceType = PS_DeviceType_Windows;
	MarsWrapper::GetInstance().MsgLogin(strAppID, strAppToken, strUserID, strUserName, iDeviceType, strDeviceToken, CPSIMTaskCallback::GetInstance());
}

// 注销
void CPSIMCallConcrete::MsgLogout()
{
	MarsWrapper::GetInstance().MsgLogout();
}

// 创建群组
bool CPSIMCallConcrete::CreateGroup(const PSGroupInfo& groupInfo)
{
	return MarsWrapper::GetInstance().CreateGroup(groupInfo, CPSIMTaskCallback::GetInstance());
}

// 删除群;
void CPSIMCallConcrete::DeleteGroup(IN const char* strGroupID)
{

}

// 获取群成员;
//void CPSIMCallConcrete::GetGroupUsers(const char* strGroupID, const int iPageNum, const int iPageSize)
//{
//
//}

// 添加群成员;
bool CPSIMCallConcrete::AddGroupUsers(IN const char* strGroupID, IN const PSUserInfo* pUsers, IN const int iAddCount)
{
	return MarsWrapper::GetInstance().AddGroupUsers(strGroupID, pUsers, iAddCount, CPSIMTaskCallback::GetInstance());
}

// 移除群成员;
bool CPSIMCallConcrete::RemoveGroupUsers(IN const char* strGroupID, IN const PSUserInfo* pUsers, IN const int iRemoveCount)
{
	//return MarsWrapper::GetInstance().RemoveGroupUsers(strGroupID, pUsers, iRemoveCount, CPSIMTaskCallback::GetInstance());
	return true;
}

// 添加子群;
bool CPSIMCallConcrete::AddGroupChilds(IN const char* strGroupID, IN const PSGroupInfo* pGroups, IN const int iAddCount)
{
	return true;
}

// 移除子群;
bool CPSIMCallConcrete::RemoveGroupUsers(IN const char* strGroupID, IN const PSGroupInfo* pUsers, IN const int iRemoveCount)
{
	return true;
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
bool CPSIMCallConcrete::SendTextMessage(OUT int& iReqID,
	IN const PS_SendMode& eSendMode,
	IN const char* strFrom,
	IN const char* strTo,
	IN const char* strContent,
	IN const int& iContentLen,
	IN const char* strPushInfo)
{
	return MarsWrapper::GetInstance().SendTextMessage(iReqID, eSendMode, strFrom, strTo, strContent, iContentLen, strPushInfo, CPSIMTaskCallback::GetInstance());
}

// 获取离线消息
void CPSIMCallConcrete::GetOfflineMsgs(OUT PSOffMsgDesc* pOffMsgDescs, IN const int & iDescCount)
{
	std::vector<PSOffMsgDesc> vecMsgDesc;
	for (int i = 0; i < iDescCount; i++)
	{
		PSOffMsgDesc OffMsgDesc;
		OffMsgDesc.strFrom = pOffMsgDescs[i].strFrom;
		OffMsgDesc.strTo = pOffMsgDescs[i].strTo;
		OffMsgDesc.iSendMode = pOffMsgDescs[i].iSendMode;
		OffMsgDesc.iStartMsgID = pOffMsgDescs[i].iStartMsgID;
		OffMsgDesc.iMsgCount = pOffMsgDescs[i].iMsgCount;
		vecMsgDesc.push_back(OffMsgDesc);
	}
	MarsWrapper::GetInstance().GetOfflineMsgs(vecMsgDesc, CPSIMTaskCallback::GetInstance());
}

// 消息撤回
void CPSIMCallConcrete::RevokeMsg()
{

}