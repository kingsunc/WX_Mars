#ifndef _OFFMSG_CGI_TASK_H_
#define _OFFMSG_CGI_TASK_H_

#include "task/CGITask.h"
#include "mars/boost/weak_ptr.hpp"
#include "tars/offmsg_tars.h"
#include "tars/msg_resp_tars.h"

class OffMsg_Task;

// OffMsg任务回调;
class OffMsg_Callback
{
public:
	virtual void OnResponse(OffMsg_Task* task, MessageService::OfflineMsgResp& response) = 0;
};

// OffMsg任务;
class OffMsg_Task : public CGITask
{
public:
	virtual bool Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select);
	virtual int Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select);

	std::vector<PS_OffMsgDesc_t> vecMsgDesc;

	OffMsg_Callback* pCallback;
};

#endif