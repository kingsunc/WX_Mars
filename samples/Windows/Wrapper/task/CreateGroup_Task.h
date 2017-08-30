#ifndef _CREATEGROUPIN_CGI_TASK_H_
#define _CREATEGROUPIN_CGI_TASK_H_

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

	std::string		m_strGroupID;				// 群的唯一名称;
	std::string		m_strGroupName;				// 群组名称，此属性为必须的;
	std::string		m_strGroupDesc;				// 群组描述，此属性为必须的;
	bool			m_bPublic;					// 是否是公开群 此属性为必须的;
	int				m_iMaxUsers;				// 群组成员最大数（包括群主） 值为数值类型，默认值200，此属性为可选的;
	std::string		m_strOwner;					// 群组的管理员，此属性为必须的;
	std::vector<std::string>	m_vecAdmins;	// 管理员;
	std::vector<std::string>	m_vecMembers;	// 普通成员，此属性为可选的;

	CreateGroup_Callback* pCallback;
};

#endif