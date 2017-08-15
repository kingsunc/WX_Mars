#include "PSIMDemoCallBack.h"
#include <stdio.h>

CPSIMDemoCallBack::CPSIMDemoCallBack()
{
}

CPSIMDemoCallBack::~CPSIMDemoCallBack()
{
}

void CPSIMDemoCallBack::OnLoginResponse(const int& iCode, const char* strInfo)
{
	printf("CPSIMDemoCallBack::OnLoginResponse: iCode(%d), strInfo(%s) \n", iCode, strInfo);

	// todo
	return;
}

void CPSIMDemoCallBack::OnSendMsgResponse(const int & iCode, const char * strInfo)
{
	printf("CPSIMDemoCallBack::OnSendMsgResponse: iCode(%d), strInfo(%s) \n", iCode, strInfo);

	// todo
	return;
}

void CPSIMDemoCallBack::OnGetOffMsgResponse(const int & iCode, const char * strInfo)
{
	printf("CPSIMDemoCallBack::OnGetOffMsgResponse: iCode(%d), strInfo(%s) \n", iCode, strInfo);

	// todo
	return;
}
