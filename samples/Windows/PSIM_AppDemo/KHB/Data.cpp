#include "Data.h"

CData::CData()
{
}

CData::~CData()
{
}

void CData::Clear()
{
	m_loginInfo.Clear();
}

CUserInfo* CData::GetUserInfo()
{
	return &m_loginInfo;
}