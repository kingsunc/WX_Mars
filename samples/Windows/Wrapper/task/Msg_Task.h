#ifndef _MSG_CGI_TASK_H_
#define _MSG_CGI_TASK_H_

#include "task/CGITask.h"
#include "mars/boost/weak_ptr.hpp"
#include "tars/msg_tars.h"
#include "tars/msg_resp_tars.h"

class Msg_Task;

// Msg任务回调;
class Msg_Callback
{
public:
	virtual void OnResponse(Msg_Task* task, MessageService::SendMsgResp& response) = 0;
};

// Msg任务;
class Msg_Task : public CGITask
{
public:
	virtual bool Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select);
	virtual int Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select);

	tars::Int64		msgId;
	std::string		from;
	std::string		to;
	tars::Short		sendMode;
	tars::Short		type;
	tars::Char		priority;
	tars::Short		handleOption;
	std::string		pushInfo;
	tars::Int32		timestamp;
	tars::Int32		expireTime;
	vector<tars::Char>	content;

	Msg_Callback* pCallback;
};

#endif