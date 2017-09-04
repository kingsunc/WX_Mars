#pragma once

#include <windows.h>
#include "TString.h"
#include <stdint.h>
#include <codecvt>

class TStringTool
{
public:
	//Encode编码(gb2312编码);
	static bool EncodeGB2312(const char* szSrc, char* pBuf, int cbBufLen, bool bUpperCase)
	{
		if (szSrc == NULL || pBuf == NULL || cbBufLen <= 0)
			return false;

		size_t len_ascii = strlen(szSrc);
		if (len_ascii == 0)
		{
			pBuf[0] = 0;
			return true;
		}

		char baseChar = bUpperCase ? 'A' : 'a';

		unsigned char c;
		int cbDest = 0; // 累加;
		unsigned char *pSrc = (unsigned char*)szSrc;
		unsigned char *pDest = (unsigned char*)pBuf;
		while (*pSrc && cbDest < cbBufLen - 1)
		{
			c = *pSrc;
			if (isalpha(c) || isdigit(c) || c == '-' || c == '.' || c == '~')//isalpha判断是否为英文字母，为小写返回2，为大写返回1；isdigit判断是否为0-9
			{
				*pDest = c;
				++pDest;
				++cbDest;
			}
			else if (c == ' ')
			{
				*pDest = '+';
				++pDest;
				++cbDest;
			}
			else
			{
				//检查缓冲区大小是否够用？
				if (cbDest + 3 > cbBufLen - 1)
					break;
				pDest[0] = '%';
				pDest[1] = (c >= 0xA0) ? ((c >> 4) - 10 + baseChar) : ((c >> 4) + '0');
				pDest[2] = ((c & 0xF) >= 0xA) ? ((c & 0xF) - 10 + baseChar) : ((c & 0xF) + '0');
				pDest += 3;
				cbDest += 3;
			}
			++pSrc;
		}
		//null-terminator
		*pDest = '\0';

		return true;
	}

	static std::string UrlEncode(const std::string strSrc)
	{
		char chHex[] = "0123456789ABCDEF";
		std::string strDest;
		for (size_t i = 0; i < strSrc.size(); ++i)
		{
			unsigned char cc = strSrc[i];

			// 绝对不编码的，只有字母、数字、短横线(-)、下划线(_)、点(.)和波浪号(~);
			// 其他字符要视情况而定，所以一般性的urlencode只需保留上述字符不进行编码;
			if (isalnum(cc) ||
				(cc == '-') ||
				(cc == '_') ||
				(cc == '.') ||
				cc == '~')
			{
				strDest += cc;
			}
			else if (cc == ' ')
			{
				strDest += "+";
			}
			else
			{
				strDest += '%';
				strDest += chHex[cc / 16];
				strDest += chHex[cc % 16];
			}
		}
		return strDest;
	}

	static std::string TString2UTF8(TString strValue)
	{
		int  length = 0;
#ifdef _UNICODE  
		length = WideCharToMultiByte(CP_UTF8, 0, strValue.c_str(), -1, NULL, 0, NULL, NULL);
#else  
		return NULL;
#endif  
		if (length <= 0)
		{
			return NULL;
		}

		char *pBuffer = new char[length];
		if (pBuffer == NULL)
		{
			return NULL;
		}
		ZeroMemory(pBuffer, length);

#ifdef _UNICODE  
		WideCharToMultiByte(CP_UTF8, 0, strValue.c_str(), -1, pBuffer, length, NULL, NULL);
#else  
		strcpy_s(pBuffer, length, strValue);
#endif  

		std::string strRes = pBuffer;
		delete[]pBuffer;

		return strRes;
	}

	static std::string UrlDecode(const std::string& strSrc)
	{
		std::string strDest;
		int hex = 0;
		for (size_t i = 0; i < strSrc.length(); ++i)
		{
			switch (strSrc[i])
			{
			case '+':
			{
						strDest += ' ';
			}
				break;
			case '%':
			{
						if (isxdigit(strSrc[i + 1]) && isxdigit(strSrc[i + 2]))
						{
							std::string hexStr = strSrc.substr(i + 1, 2);
							hex = strtol(hexStr.c_str(), 0, 16);
							//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]
							//可以不经过编码直接用于URL
							if (!((hex >= 48 && hex <= 57) || //0-9
								(hex >= 97 && hex <= 122) || //a-z
								(hex >= 65 && hex <= 90) ||  //A-Z
								//一些特殊符号及保留字[$-_.+!*'(),] [$&+,/:;=?@]
								hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
								|| hex == 0x2a || hex == 0x2b || hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
								|| hex == 0x3A || hex == 0x3B || hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
								))
							{
								strDest += char(hex);
								i += 2;
							}
							else strDest += '%';
						}
						else
						{
							strDest += '%';
						}
			}
				break;
			default:
			{
					   strDest += strSrc[i];
			}
				break;
			}
		}
		return strDest;
	}

	static void  Utf8ToGb2312(IN const char* utf8, OUT char *szGB)//UTF-8到GB2312的转换
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
		len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, wstr, -1, szGB, len, NULL, NULL);
		szGB[len] = '\0';

		delete[] wstr;
	}

	static std::string Utf8ToAnsi(const char *pSrc, int nLen)
	{
		if (nLen == 0)
		{
			return "";
		}

		//计算需要的Unicode字符长度
		int nCount = MultiByteToWideChar(CP_UTF8, 0, pSrc, nLen, NULL, 0);
		std::vector<WCHAR> vecTmp;
		vecTmp.resize(nCount);

		//将UTF-8转为Unicode
		MultiByteToWideChar(CP_UTF8, 0, pSrc, nLen, &vecTmp[0], nCount);

		//计算需要的Ansi字符长度
		nCount = WideCharToMultiByte(CP_ACP, 0, &vecTmp[0], vecTmp.size(), NULL, 0, 0, 0);;
		std::vector<char> vecAnsi;
		vecAnsi.resize(nCount);

		//将Unicode转为Ansi
		WideCharToMultiByte(CP_ACP, 0, &vecTmp[0], vecTmp.size(), &vecAnsi[0], nCount, 0, 0);

		//反馈结果
		std::string strRet;
		strRet.append(&vecAnsi[0], nCount);
		char *pChar = &vecAnsi[0];
		return strRet;
	}

	static std::string AnsiToUtf8(const char *pSrc, int nLen)
	{
		if (nLen == 0)
		{
			return "";
		}

		//计算需要的Unicode字符长度
		int nCount = MultiByteToWideChar(CP_ACP, 0, pSrc, nLen, NULL, 0);
		std::vector<WCHAR> vecTmp;
		vecTmp.resize(nCount);

		//将Ansi转为Unicode
		MultiByteToWideChar(CP_ACP, 0, pSrc, nLen, &vecTmp[0], nCount);

		//计算需要的Utf8字符长度
		nCount = WideCharToMultiByte(CP_UTF8, 0, &vecTmp[0], vecTmp.size(), NULL, 0, 0, 0);;
		std::vector<char> vecAnsi;
		vecAnsi.resize(nCount);

		//将Unicode转为Utf8
		WideCharToMultiByte(CP_UTF8, 0, &vecTmp[0], vecTmp.size(), &vecAnsi[0], nCount, 0, 0);

		//反馈结果
		std::string strRet;
		strRet.append(&vecAnsi[0], nCount);
		char *pChar = &vecAnsi[0];
		return strRet;
	}

	// 多字节转成宽字节;
	static bool MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
	{
		DWORD dwMinSize;
		dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);

		if (dwSize < dwMinSize + 1)
		{
			return false;
		}

		MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
		lpwszStr[dwMinSize] = '\0';
		return true;
	}

	// 宽字节转成多字节;
	static bool WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
	{
		DWORD dwMinSize;
		dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, false);

		if (dwSize < dwMinSize + 1)
		{
			return false;
		}

		WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, false);
		lpszStr[dwMinSize] = '\0';
		return true;
	}

	static std::string WS_2_S(const std::wstring& src)
	{
		std::locale sys_locale("");

		const wchar_t* data_from = src.c_str();
		const wchar_t* data_from_end = src.c_str() + src.size();
		const wchar_t* data_from_next = 0;

		int wchar_size = 4;
		char* data_to = new char[(src.size() + 1) * wchar_size];
		char* data_to_end = data_to + (src.size() + 1) * wchar_size;
		char* data_to_next = 0;

		memset(data_to, 0, (src.size() + 1) * wchar_size);

		typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
		mbstate_t out_state = {0};
		auto result = std::use_facet<convert_facet>(sys_locale).out(
			out_state, data_from, data_from_end, data_from_next,
			data_to, data_to_end, data_to_next);
		if (result == convert_facet::ok)
		{
			std::string dst = data_to;
			delete[] data_to;
			return dst;
		}
		else
		{
			printf("convert error!\n");
			delete[] data_to;
			return std::string("");
		}
	}

	static std::wstring S_2_WS(const std::string& src)
	{
		std::locale sys_locale("");

		const char* data_from = src.c_str();
		const char* data_from_end = src.c_str() + src.size();
		const char* data_from_next = 0;

		wchar_t* data_to = new wchar_t[src.size() + 1];
		wchar_t* data_to_end = data_to + src.size() + 1;
		wchar_t* data_to_next = 0;

		wmemset(data_to, 0, src.size() + 1);

		typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
		mbstate_t in_state = {0};
		auto result = std::use_facet<convert_facet>(sys_locale).in(
			in_state, data_from, data_from_end, data_from_next,
			data_to, data_to_end, data_to_next);
		if (result == convert_facet::ok)
		{
			std::wstring dst = data_to;
			delete[] data_to;
			return dst;
		}
		else
		{
			delete[] data_to;
			return std::wstring(L"");
		}
	}

	static std::string WS_2_UTF8(const std::wstring& src)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		return conv.to_bytes(src);
	}

	static  std::wstring UTF8_2_WS(const std::string& src)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
		return conv.from_bytes(src);
	}

	static std::string BinToHex(const std::string &strBin, bool bIsUpper = true)
	{
		std::string strHex;
		strHex.resize(strBin.size() * 2);
		for (size_t i = 0; i < strBin.size(); i++)
		{
			uint8_t cTemp = strBin[i];
			for (size_t j = 0; j < 2; j++)
			{
				uint8_t cCur = (cTemp & 0x0f);
				if (cCur < 10)
				{
					cCur += '0';
				}
				else
				{
					cCur += ((bIsUpper ? 'A' : 'a') - 10);
				}
				strHex[2 * i + 1 - j] = cCur;
				cTemp >>= 4;
			}
		}

		return strHex;
	}

	static std::string HexToBin(const std::string &strHex)
	{
		if (strHex.size() % 2 != 0)
		{
			return "";
		}

		std::string strBin;
		strBin.resize(strHex.size() / 2);
		for (size_t i = 0; i < strBin.size(); i++)
		{
			uint8_t cTemp = 0;
			for (size_t j = 0; j < 2; j++)
			{
				char cCur = strHex[2 * i + j];
				if (cCur >= '0' && cCur <= '9')
				{
					cTemp = (cTemp << 4) + (cCur - '0');
				}
				else if (cCur >= 'a' && cCur <= 'f')
				{
					cTemp = (cTemp << 4) + (cCur - 'a' + 10);
				}
				else if (cCur >= 'A' && cCur <= 'F')
				{
					cTemp = (cTemp << 4) + (cCur - 'A' + 10);
				}
				else
				{
					return "";
				}
			}
			strBin[i] = cTemp;
		}

		return strBin;
	}

	static bool BinToHex(char* strHex, const char* strBin, size_t iSize, bool bIsUpper = true)
	{
		for (size_t i = 0; i < iSize; i++)
		{
			uint8_t cTemp = strBin[i];
			for (size_t j = 0; j < 2; j++)
			{
				uint8_t cCur = (cTemp & 0x0f);
				if (cCur < 10)
				{
					cCur += '0';
				}
				else
				{
					cCur += ((bIsUpper ? 'A' : 'a') - 10);
				}
				strHex[2 * i + 1 - j] = cCur;
				cTemp >>= 4;
			}
		}

		return true;
	}

	static bool HexToBin(char* strBin, const char* strHex, size_t iSize)
	{
		if (iSize % 2 != 0)
		{
			return "";
		}

		size_t iBinSize = iSize / 2;
		for (size_t i = 0; i < iBinSize; i++)
		{
			uint8_t cTemp = 0;
			for (size_t j = 0; j < 2; j++)
			{
				char cCur = strHex[2 * i + j];
				if (cCur >= '0' && cCur <= '9')
				{
					cTemp = (cTemp << 4) + (cCur - '0');
				}
				else if (cCur >= 'a' && cCur <= 'f')
				{
					cTemp = (cTemp << 4) + (cCur - 'a' + 10);
				}
				else if (cCur >= 'A' && cCur <= 'F')
				{
					cTemp = (cTemp << 4) + (cCur - 'A' + 10);
				}
				else
				{
					return false;
				}
			}
			strBin[i] = cTemp;
		}

		return true;
	}
};

#define _A2W(x) TStringTool::S_2_WS(x)
#define _W2A(x) TStringTool::WS_2_S(x)

#ifdef UNICODE
#define _A2T(x) _A2W(x)
#define _W2T(x) TString(x)
#define _T2A(x) _W2A(x)
#define _T2W(x) std::wstring(x)
#else
#define _A2T(x) TString(x)
#define _W2T(x) _W2A(x)
#define _T2A(x) std::string(x)
#define _T2W(x) _A2W(x)
#endif