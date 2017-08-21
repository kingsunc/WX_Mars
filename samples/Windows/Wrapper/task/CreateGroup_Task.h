#ifndef _CreateGroupIN_CGI_TASK_H_
#define _CreateGroupIN_CGI_TASK_H_

#include "task/CGITask.h"
#include "mars/boost/weak_ptr.hpp"
#include "json/CreateGroupResp_Json.h"

class CreateGroup_Task;

// CreateGroup任务回调;
class CreateGroup_Callback
{
public:
	virtual void OnResponse(CreateGroup_Task* task, CreateGroupResp_Json& response) = 0;
};

// CreateGroup任务;
class CreateGroup_Task : public CGITask 
{
public:
	virtual bool Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select);
	virtual int Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select);

	//std::string strAppID;
	//std::string strAppToken;
	//std::string strUserID;
	//std::string strUserName;
	//int iDeviceType;
	//std::string strDeviceToken;

	CreateGroup_Callback* pCallback;
};

#endif