#pragma once
#include "TSingleton.h"
#include "KHBDefs.h"
#include <map>

class CUserInfo
{
public:
	CUserInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_iUserID = 0;
		m_iStatus = 0;
		m_iLoginTime = 0;
	}
public:
	int64	m_iUserID;
	int32	m_iStatus;
	int64	m_iLoginTime;
};

class CData : public TSingleton<CData>
{
public:
	CData();
	~CData();

	CUserInfo* GetUserInfo();

	// 注销时 还原清空所有数据;
	void Clear();

private:
	CUserInfo				m_loginInfo;
};

#define AflGetData		CData::GetInstance