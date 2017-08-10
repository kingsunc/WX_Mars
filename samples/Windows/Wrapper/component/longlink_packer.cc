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
*  longlink_packer.cc
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#include "longlink_packer.h"

#ifndef _WIN32
#include <arpa/inet.h>
#endif

#ifdef __APPLE__
#include "mars/xlog/xlogger.h"
#else
#include "mars/comm/xlogger/xlogger.h"
#endif
#include "mars/comm/autobuffer.h"
#include "mars/stn/stn.h"

// 通信协议版本号;
static uint32_t sg_client_version = 0;

#pragma pack(push, 1)
#pragma pack(pop)

namespace mars
{
namespace stn
{
longlink_tracker* (*longlink_tracker::Create)()
= []()
{
    return new longlink_tracker;
};
    
void SetClientVersion(uint32_t _client_version) 
{
    sg_client_version = _client_version;
}

static int __unpack_header(const void* _packed, size_t _packed_len, uint32_t& _cmdid, uint32_t& _seq, size_t& _package_len, size_t& _body_len)
{
    __STNetMsgXpHeader st = {0};
    if (_packed_len < sizeof(__STNetMsgXpHeader))
	{
        _package_len = 0;
        _body_len = 0;
        return LONGLINK_UNPACK_CONTINUE;
    }
    
    memcpy(&st, _packed, sizeof(__STNetMsgXpHeader));

#ifndef MY_DATA
    uint32_t head_len = ntohl(st.head_length);
    uint32_t client_version = ntohl(st.client_version);
    if (client_version != sg_client_version)
	{
        _package_len = 0;
        _body_len = 0;
    	return LONGLINK_UNPACK_FALSE;
    }
    _cmdid = ntohl(st.cmdid);
	_seq = ntohl(st.seq);
	_body_len = ntohl(st.body_length);
	_package_len = head_len + _body_len;
#else
	_body_len = ntohl(st.body_length);
	_cmdid = ntohs(st.cmd_id);
	_seq = ntohl(st.seqid);
	uint32_t version = st.version;

	_package_len = sizeof(__STNetMsgXpHeader) + _body_len;
#endif

    if(_package_len > 1024*1024)
	{
		return LONGLINK_UNPACK_FALSE;
	}
    if (_package_len > _packed_len)
	{
		return LONGLINK_UNPACK_CONTINUE;
	}
    
    return LONGLINK_UNPACK_OK;
}

// 打包请求数据 追加头部信息;
void (*longlink_pack)(uint32_t _cmdid, uint32_t _seq, const AutoBuffer& _body, const AutoBuffer& _extension, AutoBuffer& _packed, longlink_tracker* _tracker)
= [](uint32_t _cmdid, uint32_t _seq, const AutoBuffer& _body, const AutoBuffer& _extension, AutoBuffer& _packed, longlink_tracker* _tracker)
{
#ifndef MY_DATA
    __STNetMsgXpHeader st = {0};
    st.head_length = htonl(sizeof(__STNetMsgXpHeader));
    st.client_version = htonl(sg_client_version);
    st.cmdid = htonl(_cmdid);
    st.seq = htonl(_seq);
    st.body_length = htonl(_body.Length());
#else
	__STNetMsgXpHeader st = { 0 };
	st.body_length = htonl(_body.Length());
	st.cmd_id = htons(_cmdid);
	st.version = sg_client_version;
	st.seqid = htonl(_seq);
#endif

    _packed.AllocWrite(sizeof(__STNetMsgXpHeader) + _body.Length());
    _packed.Write(&st, sizeof(st));
    
	if (NULL != _body.Ptr())
	{
		_packed.Write(_body.Ptr(), _body.Length());
	}

#ifdef _DEBUG
	int iLen = _packed.Length();
	printf("send packet Header: %d , Body : %d \n", sizeof(__STNetMsgXpHeader), _body.Length());
	unsigned char* ch = (unsigned char*)_packed.Ptr(0);
	for (int i = 0; i < iLen; i++)
	{
		printf("%02X ", ch[i]);
	}
	printf("\n");
#endif // _DEBUG
    
    _packed.Seek(0, AutoBuffer::ESeekStart);
};

// 解包响应数据 去除头部信息;
int (*longlink_unpack)(const AutoBuffer& _packed, uint32_t& _cmdid, uint32_t& _seq, size_t& _package_len, AutoBuffer& _body, AutoBuffer& _extension, longlink_tracker* _tracker)
= [](const AutoBuffer& _packed, uint32_t& _cmdid, uint32_t& _seq, size_t& _package_len, AutoBuffer& _body, AutoBuffer& _extension, longlink_tracker* _tracker)
{
#ifdef _DEBUG
	int iHeaderLen = sizeof(__STNetMsgXpHeader);
	printf("recv packet Header: %d , Body : %d \n", iHeaderLen, _packed.Length() - iHeaderLen);
	unsigned char* ch = (unsigned char*)(_packed.Ptr());
	for (int i = 0; i < _packed.Length(); i++)
	{
		printf("%02X ", ch[i]);
	}
	printf("\n");
#endif // _DEBUG

   size_t body_len = 0;
   int ret = __unpack_header(_packed.Ptr(), _packed.Length(), _cmdid,  _seq, _package_len, body_len);
   if (LONGLINK_UNPACK_OK != ret)
   {
	   return ret;
   }
    _body.Write(AutoBuffer::ESeekCur, _packed.Ptr(_package_len-body_len), body_len);

    return ret;
};

#define MSGCMD_HANDSHAKE 10000
#define SIGNALKEEP_CMDID 243
#define PUSH_DATA_TASKID 0

uint32_t (*longlink_noop_cmdid)()
= []()
{
	uint32_t cmidid = MSGCMD_HANDSHAKE;
    return cmidid;
};

bool  (*longlink_noop_isresp)(uint32_t _taskid, uint32_t _cmdid, uint32_t _recv_seq, const AutoBuffer& _body, const AutoBuffer& _extend)
= [](uint32_t _taskid, uint32_t _cmdid, uint32_t _recv_seq, const AutoBuffer& _body, const AutoBuffer& _extend)
{
    return Task::kNoopTaskID == _taskid && MSGCMD_HANDSHAKE == _cmdid;
};

uint32_t (*signal_keep_cmdid)()
= []()
{
	uint32_t cmidid = SIGNALKEEP_CMDID;
	return cmidid;
};

void (*longlink_noop_req_body)(AutoBuffer& _body, AutoBuffer& _extend)
= [](AutoBuffer& _body, AutoBuffer& _extend)
{
};
    
void (*longlink_noop_resp_body)(const AutoBuffer& _body, const AutoBuffer& _extend)
= [](const AutoBuffer& _body, const AutoBuffer& _extend)
{
};

uint32_t (*longlink_noop_interval)()
= []()
{
	uint32_t interval = 0;
	return interval;
};

bool (*longlink_complexconnect_need_verify)()
= []()
{
    return false;
};

bool (*longlink_ispush)(uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend)
= [](uint32_t _cmdid, uint32_t _taskid, const AutoBuffer& _body, const AutoBuffer& _extend)
{
	// 确认是否推送消息, 暂时不需要;
	return false;
    //return PUSH_DATA_TASKID == _taskid;
};
    
bool (*longlink_identify_isresp)(uint32_t _sent_seq, uint32_t _cmdid, uint32_t _recv_seq, const AutoBuffer& _body, const AutoBuffer& _extend)
= [](uint32_t _sent_seq, uint32_t _cmdid, uint32_t _recv_seq, const AutoBuffer& _body, const AutoBuffer& _extend)
{
    return _sent_seq == _recv_seq && 0 != _sent_seq;
};

}
}