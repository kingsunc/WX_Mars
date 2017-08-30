#include <mars/comm/windows/projdef.h>
#include "DeleteGroup_Task.h"
#include "mars/stn/stn_logic.h"

using namespace std;

bool DeleteGroup_Task::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
{

	return true;
}

int DeleteGroup_Task::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	DeleteGroupResp_Json response;
	if (response.DeSerialize((const char*)_inbuffer.Ptr()))
	{
		response.DisplayPropertys();
	}

	if (pCallback)
	{
		pCallback->OnResponse(this, response);
	}

	return mars::stn::kTaskFailHandleNoError;
}