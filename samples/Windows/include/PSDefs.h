#pragma once

#ifndef IN
#define IN			// 传入参数;
#endif
#ifndef OUT
#define OUT			// 传出参数;
#endif

typedef long long	int64_ps;
typedef int			int32_ps;

// 设备类型;
enum PS_DeviceType
{
	PS_DeviceType_Ios = 1,
	PS_DeviceType_Android = 2,
	PS_DeviceType_Windows = 3,
	PS_DeviceType_Other = 6
};

// 发送模式
enum PS_SendMode
{
	PS_SendMode_P2P					= 0,
	PS_SendMode_Group				= 1,
	PS_SendMode_P2PS				= 4,
	PS_SendMode_OneOfGroup			= 5,
	PS_SendMode_AppBroadcast		= 7,
	PS_SendMode_SystemBroadcast		= 8,
};

// 发送设置
enum PS_SendOption
{
	PS_SendOption_OfflineSave = 4,
	PS_SendOption_IosPush = 8,
};

// 消息类型
enum PS_MessageType
{
	PS_MessageType_Text = 1,
	PS_MessageType_Image,
	PS_MessageType_Audio,
	PS_MessageType_Video,
	PS_MessageType_File,
	PS_MessageType_Geo,
	PS_MessageType_Custom,
	PS_MessageType_Tip,
	PS_MessageType_Command,
	PS_MessageType_Operate = 80,
	PS_MessageType_Other = 120,
};

// 离线消息信息;
typedef struct PS_OffMsgInfo
{
	char*	strFrom;
	char*	strTo;
	short	sSendMode;
	char*	strContent;
}PS_OffMsgInfo_t;

// 获取离线消息-描述信息
typedef struct PS_OffMsgDesc
{
	char*			strFrom;
	char*			strTo;
	PS_SendMode		iSendMode;
	int64_ps		iStartMsgID;
	int32_ps		iMsgCount;
}PS_OffMsgDesc_t;