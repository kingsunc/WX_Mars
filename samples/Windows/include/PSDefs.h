#pragma once
#include <stdint.h>
#include <memory.h>
#include "PSVector.h"
#include "PSString.h"

#ifndef IN
#define IN			// 传入参数;
#endif
#ifndef OUT
#define OUT			// 传出参数;
#endif

typedef long long	int64_ps;
typedef int			int32_ps;

enum PSResultCode
{
	PSResult_Success			= 0,
	PSResult_ParaError			= 1,
	MsgResultRepeat = 2,
	MsgResultRedisDBError = 5,
	MsgResultMysqlError = 6,
	MsgResultDBError = 7,
	MsgResultMemNotEnough = 8,
	MsgResultNoPrivilege = 9,
	MsgResultUserOffline = 10,
	MsgResultUserIdNull = 11,
	MsgResultUserIdOverLen = 12,
	MsgResultUserIdErr = 13,
	MsgResultUserNotInGroup = 17,
	MsgResultUserListEmpty = 18,
	MsgResultUserOnline = 19,
	MsgResultGroupIdNull = 20,
	MsgResultGroupIdOverLen = 21,
	MsgResultGroupEpmty = 22,
	MsgResultMsgEmpty = 34,
	MsgResultMsgTooShort = 35,
	MsgResultMsgInvalidFormat = 36,
	MsgResultNoReceiver = 37,
	MsgResultSendHimself = 38,
	MsgResultUnknowMessageType = 39,
	MsgResultTokenInvalid = 40,
	MsgResultTokenExpired = 41,
	MsgResultServiceUnavailable = 50,
	MsgResultBrokerPushErr = 51,
	MsgResultIOSPushErr = 52,
	MsgResultOffserverErr = 53,
	MsgResultAuthserverErr = 54,
	MsgResultExceedLimit = 60,
	MsgResultLoginFailed = 70,
	MsgResultUnlogined = 71,
	MsgResultOtherError = 99,
	MsgResultNotSupport = 200,
};

// 设备类型;
enum PS_DeviceType
{
	PS_DeviceType_Ios				= 1,	// ios
	PS_DeviceType_Android			= 2,	// android
	PS_DeviceType_Windows			= 3,	// windows
	PS_DeviceType_Other				= 6		// 
};

// 发送模式;
enum PS_SendMode
{
	PS_SendMode_P2P					= 0,
	PS_SendMode_Group				= 1,
	PS_SendMode_P2PS				= 4,
	PS_SendMode_OneOfGroup			= 5,
	PS_SendMode_AppBroadcast		= 7,
	PS_SendMode_SystemBroadcast		= 8,
};

// 发送设置;
enum PS_SendOption
{
	PS_SendOption_OfflineSave		= 0x0004,
	PS_SendOption_IosPush			= 0x0008,
};

// 消息类型;
enum PS_MessageType
{
	PS_MessageType_Text				= 1,
	PS_MessageType_Image			= 2,
	PS_MessageType_Audio			= 3,
	PS_MessageType_Video			= 4,
	PS_MessageType_File				= 5,
	PS_MessageType_Geo				= 6,
	PS_MessageType_Custom			= 7,
	PS_MessageType_Tip				= 8,
	PS_MessageType_Command			= 9,
	PS_MessageType_Operate			= 80,
	PS_MessageType_Other			= 120,
};

// 离线消息信息;
typedef struct PSOffMsgInfo
{
	PSString		strFrom;
	PSString		strTo;
	short			sSendMode;
	PSString		strContent;
}PSOffMsgInfo;

// 获取离线消息-描述信息;
typedef struct PSOffMsgDesc
{
	PSString		strFrom;
	PSString		strTo;
	PS_SendMode		iSendMode;
	int64_ps		iStartMsgID;
	int64_ps		iEndMsgID;
}PSOffMsgDesc;

typedef struct PSMessageItem
{
	int64_t			iMsgId;
	PSString		strFrom;
	PSString		strTo;
	int16_t			iSendMode;
	int16_t			iType;
	int8_t			iPriority;
	int16_t			iHandleOption;
	PSString		strPushInfo;
	int32_t			iTimestamp;
	int32_t			iExpireTime;
	PSString		strContent;

}PSMessageItem;

typedef struct PSOffMsgInfoNoticeItem
{
	PSOffMsgDesc offmsgDesc;			// 离线消息描述;

	PSVector<PSMessageItem> vecMessage;	// 最近的历史消息详情;

}PSOffMsgInfoNoticeItem;

// 用户信息;
typedef struct PSUserInfo
{
	PSString		strUserID;
	PSString		strUserName;

}PSUserInfo;

// 群信息;
typedef struct PSGroupInfo
{
	PSString		strGroupID;
	PSString		strGroupName;
	PSString		strGroupOwner;
	PSString		strGroupDesc;
	bool			bPublic;
	int				iMaxUsers;

	PSVector<PSUserInfo>	vecAdmin;
	PSVector<PSUserInfo>	vecMember;

}PSGroupInfo;


// 回调响应基类;
typedef struct PSResp
{
	int				iStatus;
	PSString		strMessage;

}PSResp;

// 登录-回调响应;
typedef struct PSMsgLoginResp : public PSResp
{

}PSMsgLoginResp;

// 注销-回调响应;
typedef struct PSMsgLogoutResp : public PSResp
{

}PSMsgLogoutResp;

// 被迫退出-回调响应;
typedef struct PSKickOutResp : public PSResp
{

}PSKickOutResp;

// 创建群组-回调响应;
typedef struct PSCreateGroupResp : public PSResp
{

}PSCreateGroupResp;

// 删除群组-回调响应;
typedef struct PSDeleteGroupResp : public PSResp
{

}PSDeleteGroupResp;

// 添加群成员-回调响应;
typedef struct PSAddGroupUsersResp : public PSResp
{

}PSAddGroupUsersResp;

// 移除群成员-回调响应;
typedef struct PSRemoveGroupUsersResp : public PSResp
{

}PSRemoveGroupUsersResp;

// 添加子群-回调响应;
typedef struct PSAddGroupChildsResp : public PSResp
{

}PSAddGroupChildsResp;

// 移除子群-回调响应;
typedef struct PSRemoveGroupChildsResp : public PSResp
{

}PSRemoveGroupChildsResp;

// 获取服务器的离线消息通知;
typedef struct PSOffMsgInfoNotice : public PSResp
{
	PSVector<PSOffMsgInfoNoticeItem> vecOffMsgNotice;

}PSOffMsgInfoNotice;

// 获取离线消息后的回调;
typedef struct PSOffMsgResp : public PSResp
{
public:
	PSVector<PSMessageItem> vecMessage;

}PSOffMsgResp;

// 发送消息后的回调;
typedef struct PSSendMsgResp : public PSResp
{
public:
	int32_t		iSeqId;
	int32_t		iTimestamp;

}PSSendMsgResp;

// 获取服务器的在线消息;
typedef struct PSMsgResp : public PSResp
{
public:
	PSVector<PSMessageItem> vecMessage;

}PSMsgResp;
