#include <mars/comm/windows/projdef.h>
#include "OffMsg_Task.h"
#include "mars/stn/stn_logic.h"

using namespace std;

bool OffMsg_Task::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	MessageService::OfflineMsgReq req;
	for (int i = 0; i < vecMsgDesc.size(); i++)
	{
		MessageService::OffMsgDesc desc;
		desc.queue.from = vecMsgDesc[i].strFrom;
		desc.queue.to = vecMsgDesc[i].strTo;
		desc.queue.sendMode = vecMsgDesc[i].iSendMode;
		desc.startSeqId = vecMsgDesc[i].iStartMsgID;
		desc.count = vecMsgDesc[i].iMsgCount;
		req.reqs.push_back(desc);
	}

	tars::TarsOutputStream<tars::BufferWriter> outStream;
	req.writeTo(outStream);
	int iLen = outStream.getLength();
	_outbuffer.AllocWrite(iLen);
	_outbuffer.Write(outStream.getBuffer(), iLen);

	return true;
}

int OffMsg_Task::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	tars::TarsInputStream<tars::BufferReader> inStream;
	inStream.setBuffer((const char*)(_inbuffer.Ptr()), _inbuffer.Length());

	MessageService::OfflineMsgResp response;
	response.readFrom(inStream);

	if (pCallback)
	{
		pCallback->OnResponse(this, response);
	}

	return mars::stn::kTaskFailHandleNoError;
}