#pragma once
#include <map>
#include "TString/TStringTool.h"
#include "TBaseExport.h"

typedef std::map<std::string, std::string> KVStrMap;	// key-value-string-map
class TBASE_API CIniConfig
{
public:
	CIniConfig();
	CIniConfig(std::string strFile);
	~CIniConfig();

	void LoadFile(std::string strFile);
	void SavedFile(std::string strFile = "");

	bool SetStringVal(std::string strKey, std::string strValue);
	std::string	GetStringVal(std::string strKey, std::string strDefault = "");

	bool SetIntVal(std::string strKey, int iValue);
	int	GetIntVal(std::string strKey, int iDefault = 0);

	bool SetDoubleVal(std::string strKey, double dValue);
	double	GetDoubleVal(std::string strKey, double dDefault = 0.0);

private:
	KVStrMap		m_mapVal;
	std::string		m_strName;
};
