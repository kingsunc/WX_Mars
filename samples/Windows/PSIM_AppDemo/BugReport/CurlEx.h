#pragma once
#include "curl/curl.h"
#include "TString.h"

class CCurlEx
{
public:
	CCurlEx();
	~CCurlEx();

	// 文件上传;
	bool UpLoadFile(IN LPCWSTR strUrl, IN LPCWSTR strLocalPath);

protected:
	static size_t HttpCallback(void *pStr, size_t iSize, size_t iCount, void *pOutStr);
};

#define AflGetCurlEx				CCurlEx::GetInstance