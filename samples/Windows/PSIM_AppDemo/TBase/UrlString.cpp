#include "UrlString.h"

CUrlString::CUrlString()
{
	m_iParaCount = 0;
}


CUrlString::~CUrlString()
{
}

TString CUrlString::GetUrlString(bool bHasPara)
{
	if (!bHasPara)
	{
		return m_strUrl;
	}

	TString strUrl;
	strUrl.append(m_strUrl);
	strUrl.append(_T("?"));
	strUrl.append(GetParaString());
	return strUrl;
}

TString CUrlString::GetParaString()
{
	return m_strPara;
}

void CUrlString::SetUrl(TString strUrl)
{
	m_strUrl = _T("");
	m_strUrl.append(strUrl);
}

void CUrlString::AddPara(TString strKey, int iValue)
{
	TString strValue = fmt::format(_T("{}"), iValue);
	AddPara(strKey, strValue);
}

void CUrlString::AddPara(TString strKey, TString strValue)
{
	TString strTemp;
	if (m_iParaCount)
	{
		strTemp = _T("&");
	}

	std::string strUtf8 = TStringTool::TString2UTF8(strValue);
	TString strEncode = _A2T(TStringTool::UrlEncode(strUtf8)).c_str();
	TString strPara = fmt::format(_T("{}{}={}"), strTemp.c_str(), strKey.c_str(), strEncode.c_str());

	m_strPara.append(strPara);
	m_iParaCount++;
}