//#include <mars/comm/windows/projdef.h>
//#include "RemobeGroupUser_Task.h"
//#include "mars/stn/stn_logic.h"
//
//using namespace std;
//
//bool RemobeGroupUser_Task::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
//{
//	MessageService::RemobeGroupUserReq req;
//	req.appId = strAppID;
//	req.userId = strUserID;
//	req.userName = strUserName;
//	req.token = strAppToken;
//	req.deviceType = iDeviceType;
//	req.deviceToken = strDeviceToken;
//
//	tars::TarsOutputStream<tars::BufferWriter> outStream;
//	req.writeTo(outStream);
//	int iLen = outStream.getLength();
//	_outbuffer.AllocWrite(iLen);
//	_outbuffer.Write(outStream.getBuffer(), iLen);
//
//	return true;
//}
//
//int RemobeGroupUser_Task::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
//{
//	tars::TarsInputStream<tars::BufferReader> inStream;
//	inStream.setBuffer((const char*)(_inbuffer.Ptr()), _inbuffer.Length());
//
//	MessageService::RemobeGroupUserResp response;
//	response.readFrom(inStream);
//
//	if (pCallback)
//	{
//		pCallback->OnResponse(this, response);
//	}
//
//	return mars::stn::kTaskFailHandleNoError;
//}