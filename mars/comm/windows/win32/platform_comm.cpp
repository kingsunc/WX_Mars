/*  Copyright (c) 2013-2015 Tencent. All rights reserved.  */
/**
 * created on : 2012-11-28
 * author : 叶润桂
 */

#include "platform_comm.h"
#include <string>
#include "xlogger/xlogger.h"
#include "xlogger/loginfo_extract.h"
#include "NetUtil.h"

using namespace std;

bool getProxyInfo(int& port, std::string& strProxy, const std::string& _host)
{
    xverbose_function();
    return getProxyInfoImpl(port, strProxy, _host);
}

bool getCurRadioAccessNetworkInfo(struct RadioAccessNetworkInfo& info)
{
    xverbose_function();
    return false;
}

int getNetInfo()
{
    xverbose_function();
    return isNetworkConnected() ? kWifi : kNoNet;
}

unsigned int getSignal(bool isWifi)
{
    xverbose_function();
    return (unsigned int)0;
}

bool getifaddrs_ipv4_hotspot(std::string& _ifname, std::string& _ip)
{
	return false;
}

bool isNetworkConnected()
{
    return isNetworkConnectedImpl();
}

static const char* const SIMULATOR_NET_INFO = "SIMULATOR";
static const char* const USE_WIRED = "wired";

bool getCurWifiInfo(WifiInfo& wifiInfo)
{
    return false;
}

bool getCurSIMInfo(SIMInfo& bsinfo)
{
    return false;
}

bool getAPNInfo(APNInfo& info)
{
    return false;
}

static const char* sg_arrLevelStrings[] =
{
	"all  ",
	"debug",	// debug
	"info ",	// info
	"warn ",	// warn
	"error",	// error
	"fatal"		// fatal
};

void ConsoleLog(const XLoggerInfo* _info, const char* _log)
{
	char log[16 * 1024] = { 0 };
	if (_info && _log)
	{
		char strFuncName[128] = { 0 };
		ExtractFunctionName(_info->func_name, strFuncName, sizeof(strFuncName));
		const char* file_name = ExtractFileName(_info->filename);
		snprintf(log, sizeof(log), "[%s][%s][%s, %s, %d][%s\n", sg_arrLevelStrings[_info->level], NULL == _info->tag ? "" : _info->tag, file_name, strFuncName, _info->line, _log);
		::OutputDebugStringA(log);
	}
	else
	{
		snprintf(log, sizeof(log), "%s\n", _log);
	}
	
	printf(log);
}