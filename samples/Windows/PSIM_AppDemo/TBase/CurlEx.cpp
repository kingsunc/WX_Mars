#include "CurlEx.h"

#define TIME_CURL_TIMEOUT	(6)							// 超时时间设置为6秒;

typedef CURL *(*ex_curl_easy_init)(void);
typedef CURLcode(*ex_curl_easy_setopt)(CURL *curl, CURLoption option, ...);
typedef CURLFORMcode(*ex_curl_formadd)(curl_httppost **httppost, curl_httppost **last_post, ...);
typedef CURLcode(*ex_curl_easy_perform)(CURL *curl);
typedef void(*ex_curl_easy_cleanup)(CURL *curl);
typedef const char *(*ex_curl_easy_strerror)(CURLcode);
typedef CURLcode(*ex_curl_easy_getinfo)(CURL *curl, CURLINFO info, ...);
typedef void(*ex_curl_slist_free_all)(struct curl_slist *);
typedef curl_slist *(*ex_curl_slist_append)(struct curl_slist *, const char *);
typedef char *(*ex_curl_easy_escape)(CURL *handle,
	const char *string,
	int length);

HINSTANCE hCurlDll = NULL;
ex_curl_easy_init ex_pcurl_easy_init = NULL;
ex_curl_easy_setopt ex_pcurl_easy_setopt = NULL;
ex_curl_formadd ex_pcurl_formadd = NULL;
ex_curl_easy_perform ex_pcurl_easy_perform = NULL;
ex_curl_easy_cleanup ex_pcurl_easy_cleanup = NULL;
ex_curl_easy_strerror ex_pcurl_easy_strerror = NULL;
ex_curl_easy_getinfo ex_pcurl_easy_getinfo = NULL;
ex_curl_slist_free_all ex_pcurl_slist_free_all = NULL;
ex_curl_slist_append ex_pcurl_slist_append = NULL;
ex_curl_easy_escape ex_pcurl_easy_escape = NULL;

CCurlEx* CCurlEx::m_pInstance = NULL;
CLiveLockEx CCurlEx::m_lock;

CCurlEx::CCurlEx()
{
	hCurlDll = ::LoadLibrary(_T("libcurl.dll"));
	if (NULL != hCurlDll)
	{
		ex_pcurl_easy_init = (ex_curl_easy_init)GetProcAddress(hCurlDll, "curl_easy_init");
		ex_pcurl_easy_setopt = (ex_curl_easy_setopt)GetProcAddress(hCurlDll, "curl_easy_setopt");
		ex_pcurl_formadd = (ex_curl_formadd)GetProcAddress(hCurlDll, "curl_formadd");
		ex_pcurl_easy_perform = (ex_curl_easy_perform)GetProcAddress(hCurlDll, "curl_easy_perform");
		ex_pcurl_easy_cleanup = (ex_curl_easy_cleanup)GetProcAddress(hCurlDll, "curl_easy_cleanup");
		ex_pcurl_easy_strerror = (ex_curl_easy_strerror)GetProcAddress(hCurlDll, "curl_easy_strerror");
		ex_pcurl_easy_getinfo = (ex_curl_easy_getinfo)GetProcAddress(hCurlDll, "curl_easy_getinfo");
		ex_pcurl_slist_free_all = (ex_curl_slist_free_all)GetProcAddress(hCurlDll, "curl_slist_free_all");
		ex_pcurl_slist_append = (ex_curl_slist_append)GetProcAddress(hCurlDll, "curl_slist_append");
		ex_pcurl_easy_escape = (ex_curl_easy_escape)GetProcAddress(hCurlDll, "curl_easy_escape");
	}
	else
	{
		DWORD dwErr = GetLastError();
		TString strError;
		//strError.Format(_T("加载网络库文件失败，错误原因：%d"), dwErr);
		//LOG_FATAL(strError);
	}
}

CCurlEx::~CCurlEx()
{
	if (NULL != hCurlDll)
	{
		::FreeLibrary(hCurlDll);
	}
}

CCurlEx* CCurlEx::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_lock.Lock();
		if (NULL == m_pInstance)
		{
			m_pInstance = new CCurlEx();
		}
		m_lock.UnLock();
	}
	return m_pInstance;
}

void CCurlEx::ReleaseInstance()
{
	if (NULL != m_pInstance)
	{
		m_lock.Lock();
		if (NULL != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
		m_lock.UnLock();
	}
}

TString CCurlEx::GetErrorInfo()
{
	return m_strError;
}

bool CCurlEx::PostData(OUT std::string& strResult, IN TString strUrl, IN std::wstring strPara)
{
	/*TString strInfo;
	strInfo.Format(_T("Enter CCurlEx::PostData: %s"), strUrl);
	LOG_TRACE(strInfo);*/

	CURL* pCurl = NULL;
	m_strError = _T("");
	try
	{
		// 检查libcurl;
		if (NULL == ex_pcurl_easy_init)
		{
			m_strError = _T("ex_pcurl_easy_init is null");
			throw false;
		}
		else
		{
			pCurl = ex_pcurl_easy_init();
		}

		std::string strUtf8Url = TStringTool::WS_2_UTF8(strUrl);
		// 设置目标地址;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_URL, strUtf8Url.c_str());
		// 支持zip文件下载;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_ACCEPT_ENCODING, "gzip");
		// 设置UserAgent;
		//ex_pcurl_easy_setopt(pCurl, CURLOPT_USERAGENT, O_UA);
		// 设置超时时间;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_TIMEOUT, TIME_CURL_TIMEOUT);
		// 请求验证;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);
		ex_pcurl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, FALSE);

		CURLcode res = ex_pcurl_easy_setopt(pCurl, CURLOPT_POST, true);

		if (CURLE_OK != res)
		{
			LOG_ERROR(" Failed to set CURLOPT_POST ");
			return false;
		}

		std::string strUtf8Para = TStringTool::WS_2_UTF8(strPara);
		res = ex_pcurl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, strUtf8Para.c_str());
		if (CURLE_OK != res)
		{
			LOG_ERROR(" Failed to set CURLOPT_POSTFIELDS ");
			return false;
		}

		// 设置文件读取的回调函数;
		strResult.clear();
		ex_pcurl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, HttpCallback);
		ex_pcurl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strResult);

		curl_slist* pHeadList = NULL;
		//pHeadList = ex_pcurl_slist_append(pHeadList, "Content-Type:application/x-www-form-urlencoded;charset=UTF-8");
		pHeadList = ex_pcurl_slist_append(pHeadList, "Content-Type: application/x-www-form-urlencoded");
		ex_pcurl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pHeadList);

		//if (bKeepAlive)
		//{
		//	// 长连接;
		//	pHeadList = ex_pcurl_slist_append(pHeadList, "Connection: keep-alive");
		//	ex_pcurl_easy_setopt(m_pCurl, CURLOPT_HTTPHEADER, pHeadList);
		//}

		// 开始下载;
		res = ex_pcurl_easy_perform(pCurl);

		if (NULL != pHeadList)
		{
			ex_pcurl_slist_free_all(pHeadList);
		}
		if (NULL != pCurl)
		{
			ex_pcurl_easy_cleanup(pCurl);
		}
		if (res != CURLE_OK)
		{
			//m_strError = AflGetLiveError(res).c_str();
			throw false;
		}
	}
	catch (...)
	{
		/*if (m_strError.IsEmpty())
		{
		m_strError.Format(_T("%s 请求出现未知错误！"), strUrl);
		}
		TString strError;
		strError.Format(_T("错误原因: %s, 请求URL: %s, 返回数据: %s \n"), m_strError, strUrl, _A2T(strResult).c_str());
		LOG_ERROR(strError);*/
		return false;
	}

	/*strInfo.Format(_T("Leave CCurlEx::PostData: URL(%s), Result(%s)"), strUrl, _A2T(strResult).c_str());
	LOG_TRACE(strInfo);*/
	return true;
}

bool CCurlEx::PostData(OUT JsonValueEx&  jsResult, IN std::wstring strUrl, IN std::wstring strPara)
{
	std::string strResult;
	if (!PostData(strResult, strUrl, strPara))
	{
		return false;
	}

	jsResult.clear();
	if (strResult.size() == 0u)
	{
		return false;
	}

	try
	{
		// 解析反馈;
		Json::Reader reader;
		if (!reader.parse(strResult.c_str(), jsResult))
		{
			//m_strError = AflGetLiveError(LIVEERROR_PARSE).c_str();
			throw false;
		}

		std::string strRetVal = jsResult["status"].GetString();
		if ("ok" != strRetVal)
		{
			//m_strError = jsResult["reterr"].GetTString().c_str();
			throw false;
		}
	}
	catch (...)
	{
		/*TString strError;
		strError.Format(_T("错误原因: %s, 请求URL: %s, 返回数据: %s \n"), m_strError, strUrl, CA2CT(strResult.c_str()));
		LOG_ERROR(strError + _T("\n"));*/
		return false;
	}

	return true;
}

bool CCurlEx::GetData(OUT std::string& strResult, IN TString strUrl)
{
	/*TString strInfo;
	strInfo.Format(_T("Enter CCurlEx::PostData: %s"), strUrl);
	LOG_TRACE(strInfo);*/

	CURL* pCurl = NULL;
	m_strError = _T("");
	try
	{
		// 检查libcurl;
		if (NULL == ex_pcurl_easy_init)
		{
			m_strError = _T("ex_pcurl_easy_init is null");
			throw false;
		}
		else
		{
			pCurl = ex_pcurl_easy_init();
		}

		std::string strUtf8 = TStringTool::WS_2_UTF8(strUrl);
		// 设置目标地址;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_URL, strUtf8.c_str());
		// 支持zip文件下载;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_ACCEPT_ENCODING, "gzip");
		// 设置UserAgent;
		//ex_pcurl_easy_setopt(pCurl, CURLOPT_USERAGENT, O_UA);
		// 设置超时时间;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_TIMEOUT, TIME_CURL_TIMEOUT);
		// 请求验证;
		ex_pcurl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);
		ex_pcurl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, FALSE);

		// 设置文件读取的回调函数;
		strResult.clear();
		ex_pcurl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, HttpCallback);
		ex_pcurl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strResult);

		curl_slist* pHeadList = NULL;
		pHeadList = ex_pcurl_slist_append(pHeadList, "Content-Type:application/x-www-form-urlencoded;charset=UTF-8");
		ex_pcurl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pHeadList);

		//if (bKeepAlive)
		//{
		//	// 长连接;
		//	pHeadList = ex_pcurl_slist_append(pHeadList, "Connection: keep-alive");
		//	ex_pcurl_easy_setopt(m_pCurl, CURLOPT_HTTPHEADER, pHeadList);
		//}

		// 开始下载;
		CURLcode res = ex_pcurl_easy_perform(pCurl);

		if (NULL != pHeadList)
		{
			ex_pcurl_slist_free_all(pHeadList);
		}
		if (NULL != pCurl)
		{
			ex_pcurl_easy_cleanup(pCurl);
		}
		if (res != CURLE_OK)
		{
			//m_strError = AflGetLiveError(res).c_str();
			throw false;
		}
	}
	catch (...)
	{
		/*if (m_strError.IsEmpty())
		{
			m_strError.Format(_T("%s 请求出现未知错误！"), strUrl);
		}
		TString strError;
		strError.Format(_T("错误原因: %s, 请求URL: %s, 返回数据: %s \n"), m_strError, strUrl, _A2T(strResult).c_str());
		LOG_ERROR(strError);*/
		return false;
	}

	/*strInfo.Format(_T("Leave CCurlEx::PostData: URL(%s), Result(%s)"), strUrl, _A2T(strResult).c_str());
	LOG_TRACE(strInfo);*/
	return true;
}

bool CCurlEx::GetData(OUT JsonValueEx& jsResult, IN TString strUrl, IN bool VerifyRes/* = true*/)
{
	std::string strResult;
	if (!GetData(strResult, strUrl))
	{
		return false;
	}

	jsResult.clear();

	if (strResult.size() == 0u)
	{
		return false;
	}

	try
	{
		// 解析反馈;
		Json::Reader reader;
		/*if (strUrl.Find(_T("pay/openredpack")) > -1)
		{
			std::string strAnsi = TStringTool::Utf8ToAnsi(strResult.c_str(), strResult.size());
			if (!reader.parse(strAnsi.c_str(), jsResult))
			{
				m_strError = AflGetLiveError(LIVEERROR_PARSE).c_str();
				throw false;
			}
		}
		else*/
		{
			if (!reader.parse(strResult.c_str(), jsResult))
			{
				//m_strError = AflGetLiveError(LIVEERROR_PARSE).c_str();
				throw false;
			}
		}

		if (!VerifyRes)
		{
			// 有的返回数据不是retval 不进行验证;
			return true;
		}

		std::string strRetVal = jsResult["retval"].GetString();
		if ("ok" != strRetVal)
		{
			m_strError = jsResult["reterr"].GetTString().c_str();
			throw false;
		}
	}
	catch (...)
	{
		/*TString strError;
		strError.Format(_T("错误原因: %s, 请求URL: %s, 返回数据: %s \n"), m_strError, strUrl, CA2CT(strResult.c_str()));
		LOG_ERROR(strError + _T("\n"));*/
		return false;
	}

	return true;
}

size_t CCurlEx::write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
	FILE *fptr = (FILE*)userp;
	fwrite(buffer, size, nmemb, fptr);

	return size * nmemb;
}

size_t CCurlEx::HttpCallback(void *pStr, size_t iSize, size_t iCount, void *pOutStr)
{
	if (NULL != pOutStr)
	{
		std::string &str = *(std::string *)pOutStr;
		str.append((const char *)pStr, iSize * iCount);
	}
	return iSize * iCount;
}
