#ifndef _ADDGROUPUSERIN_CGI_TASK_H_
#define _ADDGROUPUSERIN_CGI_TASK_H_

#include "task/CGITask.h"
#include "mars/boost/weak_ptr.hpp"
#include "json/AddGroupUserResp_Json.h"

class AddGroupUser_Task;

// AddGroupUser任务回调;
class AddGroupUser_Callback
{
public:
	virtual void OnResponse(AddGroupUser_Task* task, AddGroupUserResp_Json& response) = 0;
};

// AddGroupUser任务;
class AddGroupUser_Task : public CGITask
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

	AddGroupUser_Callback* pCallback;
};

#endif