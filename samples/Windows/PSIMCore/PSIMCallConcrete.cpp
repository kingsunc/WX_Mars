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
	char strIn[100] = "abcdefghijklmnopqrstuvwxyz";
	char strOut[100] = {0};
	AutoBuffer strBuff;
	strBuff.AllocWrite(strlen(strIn) + 1, true);
	strBuff.Write(strIn);
	strBuff.Seek(0, AutoBuffer::ESeekStart);
	strBuff.Read(10, strOut, 6);

	// init xlog
	std::string logPath = "D://Log";	//use your log path
	std::string pubKey = "aaa";			//use you pubkey for log encrypt						 
#if _DEBUG
	xlogger_SetLevel(kLevelAll);
	appender_set_console_log(true);
#else
	xlogger_SetLevel(kLevelInfo);
	appender_set_console_log(false);
#endif
	appender_open(kAppednerAsync, logPath.c_str(), "Test", pubKey.c_str());

	MarsWrapper::GetInstance().Start();

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

}

// 获取群信息;
void CPSIMCallConcrete::GetGroupInfo(const char* strGroupID)
{

}

// 获取群成员;
void CPSIMCallConcrete::GetGroupUsers(const char* strGroupID, const int iPageNum, const int iPageSize)
{

}

// 添加群成员;
void CPSIMCallConcrete::AddGroupUsers(const char* strGroupID)
{

}

// 添加群成员;
void CPSIMCallConcrete::DeleteGroupUsers(const char* strGroupID)
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
	IN const char* strContent,
	IN const int& iContentLen,
	IN const char* strPushInfo)
{
	MarsWrapper::GetInstance().SendTextMessage(iReqID, eSendMode, strFrom, strTo, strContent, iContentLen, strPushInfo, CPSIMTaskCallback::GetInstance());
}

// 获取离线消息
void CPSIMCallConcrete::GetOfflineMsgs(OUT PS_OffMsgDesc_t* pOffMsgDescs, IN const int & iDescCount)
{
	std::vector<PS_OffMsgDesc_t> vecMsgDesc;
	for (int i = 0; i < iDescCount; i++)
	{
		PS_OffMsgDesc_t OffMsgDesc;
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