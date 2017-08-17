// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

/*
*  NetworkService.cpp
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#include "NetworkService.h"
#include "mars/comm/windows/projdef.h"
#include "mars/boost/bind.hpp"
#include "mars/baseevent/base_logic.h"
#include "mars/stn/stn_logic.h"
#include "component/stnproto_logic.h"
#include "component/stn_callback.h"
#include "component/app_callback.h"

NetworkService& NetworkService::GetInstance()
{
	static NetworkService instance_;
	return instance_;
}

NetworkService::NetworkService()
{
	Init();
}
NetworkService::~NetworkService()
{
}

void NetworkService::setClientVersion(uint32_t _client_version)
{
	mars::stn::SetClientVersion(_client_version);
}

void NetworkService::setShortLinkDebugIP(const std::string& _ip, unsigned short _port)
{
	mars::stn::SetShortlinkSvrAddr(_port, _ip);
}

void NetworkService::setShortLinkPort(unsigned short _port)
{
	mars::stn::SetShortlinkSvrAddr(_port, "");
}

void NetworkService::setLongLinkAddress(const std::string& _ip, unsigned short _port, const std::string& _debug_ip)
{
	std::vector<uint16_t> ports;
	ports.push_back(_port);
	mars::stn::SetLonglinkSvrAddr(_ip, ports, _debug_ip);
}

void NetworkService::Start()
{
	mars::baseevent::OnForeground(true);
	mars::stn::MakesureLonglinkConnected();
}

void NetworkService::Init()
{
	mars::stn::SetCallback(mars::stn::StnCallBack::Instance());
	mars::app::SetCallback(mars::app::AppCallBack::Instance());
	mars::baseevent::OnCreate();
}

int NetworkService::StartTask(CGITask* task)
{
	mars::stn::Task stnTask(task->taskid_);
	stnTask.cmdid = task->cmdid_;
	stnTask.channel_select = task->channel_select_;
	stnTask.shortlink_host_list.push_back(task->host_);
	stnTask.cgi = task->cgi_;
	stnTask.user_context = (void*)task;
	mars::stn::StartTask(stnTask);
	m_mapTasks[stnTask.taskid] = task;
	return stnTask.taskid;
}

bool NetworkService::Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	auto it = m_mapTasks.find(_taskid);
	if (it == m_mapTasks.end())
	{
		return false;
	}
	// 交给上层业务自己 打包请求数据
	return it->second->Req2Buf(_taskid, _user_context, _outbuffer, _extend, _error_code, _channel_select);
}

int NetworkService::Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select)
{
	auto it = m_mapTasks.find(_taskid);
	if (it == m_mapTasks.end())
	{
		return mars::stn::kTaskFailHandleDefault;
	}
	// 交给上层业务自己 解包响应数据
	return it->second->Buf2Resp(_taskid, _user_context, _inbuffer, _extend, _error_code, _channel_select);
}

int NetworkService::OnTaskEnd(uint32_t _taskid, void* const _user_context, int _error_type, int _error_code)
{
	auto it = m_mapTasks.find(_taskid);
	if (it != m_mapTasks.end())
	{
		delete it->second;
		m_mapTasks.erase(it);
	}
	return 0;
}

void NetworkService::OnPush(uint64_t _channel_id, uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend)
{
	auto it = m_mapObservers.find(_cmdid);
	if (it != m_mapObservers.end() && it->second)
	{
		it->second->OnPush(_channel_id, _cmdid, _taskid, _body, _extend);
	}
}

void NetworkService::SetPushObserver(uint32_t iCmdID, PushObserver* pObserver)
{
	m_mapObservers[iCmdID] = pObserver;
}