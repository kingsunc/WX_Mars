#ifndef _LOGININ_CGI_TASK_H_
#define _LOGININ_CGI_TASK_H_

#include "task/CGITask.h"
#include "mars/boost/weak_ptr.hpp"
#include "tars/access_tars.h"

class Login_Task;

// Login任务回调;
class Login_Callback
{
public:
	virtual void OnResponse(Login_Task* task, MessageService::LoginResp& response) = 0;
};

// Login任务;
class Login_Task : public CGITask 
{
public:
	virtual bool Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select);
	virtual int Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select);

	std::string strAppID;
	std::string strAppToken;
	std::string strUserID;
	std::string strUserName;
	int iDeviceType;
	std::string strDeviceToken;

	Login_Callback* pCallback;
};

#endif