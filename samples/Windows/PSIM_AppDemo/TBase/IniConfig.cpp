#include "IniConfig.h"
#include <fstream>
#include <tchar.h>
#include "format.h"

#define MAX_LINE_CHAR 256

CIniConfig::CIniConfig()
{

}

CIniConfig::CIniConfig(std::string strFile)
{
	LoadFile(strFile);
}

void CIniConfig::LoadFile(std::string strFile)
{
	m_strName = strFile;
	m_mapVal.clear();
	char line_content[MAX_LINE_CHAR];
	std::ifstream inFile(strFile.c_str());
	while (inFile)
	{
		inFile.getline(line_content, MAX_LINE_CHAR);
		std::string s = line_content;
		std::string::iterator it = s.begin();
		for (; it != s.end();)
		{
			if ((*it) == ' ' || (*it) == '\t')
			{
				it = s.erase(it);
			}
			else if ((*it) == ';' || (*it) == '#')
			{
				it = s.erase(it, s.end());
			}
			else
			{
				++it;
			}
		}
		int pos = s.find('=');
		if (pos != std::string::npos)
		{
			m_mapVal[s.substr(0, pos)] = s.substr(pos + 1, s.size());
		}
	}
	inFile.close();
}

CIniConfig::~CIniConfig()
{
}

bool CIniConfig::SetStringVal(std::string strKey, std::string strValue)
{
	m_mapVal[strKey] = strValue;
	return true;
}

std::string	CIniConfig::GetStringVal(std::string strKey, std::string strDefault)
{
	if (!m_mapVal.count(strKey))
	{
		return strDefault;
	}

	return m_mapVal[strKey];
}

bool CIniConfig::SetIntVal(std::string strKey, int iValue)
{
	std::string strValue = fmt::format("{}", iValue);
	return SetStringVal(strKey, strValue);
}

int	CIniConfig::GetIntVal(std::string strKey, int iDefault)
{
	if (!m_mapVal.count(strKey))
	{
		return iDefault;
	}

	return atoi(m_mapVal[strKey].c_str());
}

bool CIniConfig::SetDoubleVal(std::string strKey, double dValue)
{
	std::string strValue = fmt::format("{}", dValue);
	return SetStringVal(strKey, strValue);
}

double	CIniConfig::GetDoubleVal(std::string strKey, double dDefault)
{
	if (!m_mapVal.count(strKey))
	{
		return dDefault;
	}

	return atof(m_mapVal[strKey].c_str());
}

void CIniConfig::SavedFile(std::string strFile /*= ""*/)
{
	if (strFile.length() <= 0)
	{
		strFile = m_strName;
	}

	std::ofstream outFile(strFile.c_str());
	for (KVStrMap::iterator it = m_mapVal.begin(); it != m_mapVal.end(); it++)
	{
		std::string str = fmt::format("{} = {} \n", it->first, it->second);
		outFile << str;
	}
	outFile.close();
}


