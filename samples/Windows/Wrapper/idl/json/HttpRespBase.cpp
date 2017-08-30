#include "HttpRespBase.h"

CHttpRespBase::CHttpRespBase()
{
	SetPropertys();
}

void CHttpRespBase::SetPropertys()
{
	SetProperty("status", asInt, &m_iStatus);
	SetProperty("message", asString, &m_strMessage);
}

void CHttpRespBase::DisplayPropertys()
{
	//printf("status : %d \n", m_iStatus);
	//printf("message : %s \n", m_strMessage.c_str());
}