#include "stdafx.h"
#include "CurlEx.h"
#include <wininet.h>
#include "TStringTool.h"

#define TIME_CURL_TIMEOUT	(6)		// 超时时间设置为6秒;
#define O_UA				"easylive-anchor 1.2 r20160414 (Windows)"

typedef CURL *(*ex_curl_easy_init)(void);
typedef CURLcode(*ex_curl_easy_setopt)(CURL *curl, CURLoption option, ...);
typedef CURLcode(*ex_curl_easy_perform)(CURL *curl);
typedef void(*ex_curl_easy_cleanup)(CURL *curl);
typedef const char *(*ex_curl_easy_strerror)(CURLcode);
typedef CURLcode(*ex_curl_easy_getinfo)(CURL *curl, CURLINFO info, ...);
typedef void(*ex_curl_slist_free_all)(struct curl_slist *);
typedef curl_slist *(*ex_curl_slist_append)(struct curl_slist *, const char *);
typedef curl_slist *(*ex_curl_slist_append)(struct curl_slist *, const char *);
typedef CURLFORMcode *(*ex_curl_formadd)(struct curl_httppost **httppost, struct curl_httppost **last_post, ...);
typedef void *(*ex_curl_formfree)(struct curl_httppost *form);

HINSTANCE hCurlDll = NULL;
ex_curl_easy_init ex_pcurl_easy_init = NULL;
ex_curl_easy_setopt ex_pcurl_easy_setopt = NULL;
ex_curl_easy_perform ex_pcurl_easy_perform = NULL;
ex_curl_easy_cleanup ex_pcurl_easy_cleanup = NULL;
ex_curl_easy_strerror ex_pcurl_easy_strerror = NULL;
ex_curl_easy_getinfo ex_pcurl_easy_getinfo = NULL;
ex_curl_slist_free_all ex_pcurl_slist_free_all = NULL;
ex_curl_slist_append ex_pcurl_slist_append = NULL;
ex_curl_formadd ex_pcurl_formadd = NULL;
ex_curl_formfree ex_pcurl_formfree = NULL;

CCurlEx::CCurlEx()
{
	std::string strExePath;
	char buff[256] = { 0 };
#ifdef _WINDOWS_
	GetModuleFileNameA(NULL, buff, 256);
#else
	readlink("/proc/self/exe", buff, 256);
#endif
	strExePath = buff;
	strExePath = strExePath.substr(0, strExePath.rfind('\\'));

	TString strName = _T("libcurl.dll");
	SetCurrentDirectoryA((strExePath + "\\dll").c_str());
	hCurlDll = LoadLibrary(strName.c_str());
	SetCurrentDirectoryA(strExePath.c_str());
	if (NULL != hCurlDll)
	{
		ex_pcurl_easy_init = (ex_curl_easy_init)GetProcAddress(hCurlDll, "curl_easy_init");
		ex_pcurl_easy_setopt = (ex_curl_easy_setopt)GetProcAddress(hCurlDll, "curl_easy_setopt");
		ex_pcurl_easy_perform = (ex_curl_easy_perform)GetProcAddress(hCurlDll, "curl_easy_perform");
		ex_pcurl_easy_cleanup = (ex_curl_easy_cleanup)GetProcAddress(hCurlDll, "curl_easy_cleanup");
		ex_pcurl_easy_strerror = (ex_curl_easy_strerror)GetProcAddress(hCurlDll, "curl_easy_strerror");
		ex_pcurl_easy_getinfo = (ex_curl_easy_getinfo)GetProcAddress(hCurlDll, "curl_easy_getinfo");
		ex_pcurl_slist_free_all = (ex_curl_slist_free_all)GetProcAddress(hCurlDll, "curl_slist_free_all");
		ex_pcurl_slist_append = (ex_curl_slist_append)GetProcAddress(hCurlDll, "curl_slist_append");
		ex_pcurl_formadd = (ex_curl_formadd)GetProcAddress(hCurlDll, "curl_formadd");
		ex_pcurl_formfree = (ex_curl_formfree)GetProcAddress(hCurlDll, "curl_formfree");
	}
	else
	{
		DWORD dwErr = GetLastError();
	}
}

CCurlEx::~CCurlEx()
{
	if (NULL != hCurlDll)
	{
		FreeLibrary(hCurlDll);
	}
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

bool CCurlEx::UpLoadFile(IN LPCWSTR strUrl, IN LPCWSTR strLocalPath)
{
	CURL* pCurl = NULL;
	try
	{
		CURL* pCurl = NULL;
		struct curl_httppost *formpost = NULL;
		struct curl_httppost *lastptr = NULL;

		/* Fill in the file upload field */
		ex_pcurl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "sendfile",
			CURLFORM_FILE, _T2A(strLocalPath).c_str(),
			CURLFORM_END);

		/* Fill in the filename field */
		ex_pcurl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "filename",
			CURLFORM_COPYCONTENTS, "sign.txt",
			CURLFORM_END);

		/* Fill in the submit field too, even if this is rarely needed */
		ex_pcurl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "submit",
			CURLFORM_COPYCONTENTS, "Submit",
			CURLFORM_END);

		pCurl = ex_pcurl_easy_init();
		/* initalize custom header list (stating that Expect: 100-continue is not wanted */
		if (pCurl) 
		{
			/* what URL that receives this POST */
			ex_pcurl_easy_setopt(pCurl, CURLOPT_URL, _T2A(strUrl).c_str());
			ex_pcurl_easy_setopt(pCurl, CURLOPT_HTTPPOST, formpost);

			// 设置文件读取的回调函数;
			std::string strResult;
			ex_pcurl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, HttpCallback);
			ex_pcurl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strResult);

			/* Perform the request, res will get the return code */
			CURLcode res = ex_pcurl_easy_perform(pCurl);
			/* always cleanup */
			ex_pcurl_easy_cleanup(pCurl);
			/* then cleanup the formpost chain */
			ex_pcurl_formfree(formpost);

			if (res != CURLE_OK)
			{
				ex_pcurl_easy_strerror(res);
				throw false;
			}
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}