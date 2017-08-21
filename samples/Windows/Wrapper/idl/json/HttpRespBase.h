#pragma once
#include "JsonObjectBase.h"

class CHttpRespBase: public CJsonObjectBase
{
public:
	CHttpRespBase();

	// 子类需要实现此函数，并且将相应的映射关系进行设置;   
	virtual void SetPropertys();

	void DisplayPropertys();

public:
	int				m_iStatus;
	std::string		m_strMessage;
};