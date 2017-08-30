#include <mars/comm/windows/projdef.h>
#include "CreateGroup_Task.h"
#include "mars/stn/stn_logic.h"
#include "idl/json/reqData.h"

using namespace std;

bool CreateGroup_Task::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	MessageService::GroupData req;
	req.id = m_strGroupID;
	req.name = m_strGroupName;
	req.desc = m_strGroupDesc;
	req.isPublic = m_bPublic;
	req.maxUsers = m_iMaxUsers;
	req.owner = m_strOwner;
	req.admins = m_vecAdmins;
	req.members = m_vecMembers;

	string strReq = req.Serialize();
	int iLen = strReq.length();
	_outbuffer.AllocWrite(iLen);
	_outbuffer.Write(strReq.c_str(), iLen);

	return true;
}

int CreateGroup_Task::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	CreateGroupResp_Json response;
	if ( response.DeSerialize((const char*)_inbuffer.Ptr()) )
	{
		response.DisplayPropertys();
	}

	if (pCallback)
	{
		pCallback->OnResponse(this, response);
	}

	return mars::stn::kTaskFailHandleNoError;
}