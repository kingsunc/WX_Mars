#pragma once
#include "curl/curl.h"
#include <string>
#include <vector>
#include "TString/TString.h"
#include "JsonValueEx.h"
#include "LiveLockEx.h"
#include "Log4z.h"
#include "TBaseExport.h"
#include "UrlString.h"

struct CURLHeader
{
	std::string strKey;
	std::string strValue;
};
typedef std::vector<CURLHeader> VecURLHeader;
class JsonValueEx;

class TBASE_API CCurlEx
{
public:
	CCurlEx();
	~CCurlEx();

public:
	static CCurlEx* GetInstance();
	static void ReleaseInstance();

	TString	GetErrorInfo();

public:
	// 网络请求;
	bool PostData(OUT std::string& strResult, IN std::wstring strUrl, IN std::wstring strPara);
	bool PostData(OUT JsonValueEx&  jsResult, IN std::wstring strUrl, IN std::wstring strPara);

	bool GetData(OUT std::string& strResult, IN std::wstring strUrl);
	bool GetData(OUT JsonValueEx&  jsResult, IN std::wstring strUrl, IN bool VerifyRes = true);

	// 上传封面头像;
	bool UploadThumbPic(IN LPCWSTR strUrl, IN LPCWSTR strLocalPath);
	// 文件下载;
	bool DownLoadFile(IN LPCWSTR strUrl, IN LPCWSTR strLocalPath);

protected:
	static size_t HttpCallback(void *pStr, size_t iSize, size_t iCount, void *pOutStr);
	static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

private:
	static CLiveLockEx		m_lock;
	static CCurlEx*			m_pInstance;

	TString					m_strError;					// 错误内容;
};

#define AflGetCurlEx				CCurlEx::GetInstance
#define AflCurlDownLoadFile			AflGetCurlEx()->DownLoadFile