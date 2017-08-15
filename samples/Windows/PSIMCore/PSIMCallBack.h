#pragma once
#include "PSDefs.h"

class CPSIMCallBack
{
public:
	CPSIMCallBack() {};
	virtual ~CPSIMCallBack() {};

	// 登录-回调处理;
	virtual void OnLoginResponse(const int& iCode, const char* strInfo) = 0;

	// 发送消息-回调处理;
	virtual void OnSendMsgResponse(const int& iCode, const char* strInfo) = 0;

	// 获取离线消息-回调处理;
	virtual void OnGetOffMsgResponse(const int& iCode, const char* strInfo) = 0;
};