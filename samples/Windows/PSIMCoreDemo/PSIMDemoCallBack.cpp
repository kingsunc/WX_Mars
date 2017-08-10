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
}