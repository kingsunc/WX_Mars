#include <mars/comm/windows/projdef.h>
#include "Msg_Task.h"
#include "mars/stn/stn_logic.h"

using namespace std;

bool Msg_Task::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	//printf("send seqid: %d\n", _taskid);
	if (_taskid > 106)
	{
		int i = 0;
	}

	MessageService::Message req;
	req.msgId = msgId;
	req.from = from;
	req.to = to;
	req.sendMode = sendMode;
	req.type = type;
	req.priority = priority;
	req.handleOption = handleOption;
	req.pushInfo = pushInfo;
	req.timestamp = timestamp;
	req.expireTime = expireTime;
	req.content = content;

	tars::TarsOutputStream<tars::BufferWriter> outStream;
	req.writeTo(outStream);
	int iLen = outStream.getLength();
	_outbuffer.AllocWrite(iLen);
	_outbuffer.Write(outStream.getBuffer(), iLen);

	return true;
}

int Msg_Task::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	printf("recv seqid: %d\n", _taskid);

	tars::TarsInputStream<tars::BufferReader> inStream;
	inStream.setBuffer((const char*)(_inbuffer.Ptr()), _inbuffer.Length());

	MessageService::SendMsgResp response;
	response.readFrom(inStream);
	if (pCallback)
	{
		pCallback->OnResponse(this, response);
	}

	return mars::stn::kTaskFailHandleNoError;
}