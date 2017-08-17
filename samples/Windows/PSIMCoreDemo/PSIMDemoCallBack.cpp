#include "stdafx.h"
#include "PSIMDemoCallBack.h"
#include <stdio.h>

CPSIMDemoCallBack::CPSIMDemoCallBack()
{
}

CPSIMDemoCallBack::~CPSIMDemoCallBack()
{
}

void CPSIMDemoCallBack::OnGetOffMsgResponse(const int & iCode, const char * strInfo)
{
	printf("CPSIMDemoCallBack::OnGetOffMsgResponse: iCode(%d), strInfo(%s) \n", iCode, strInfo);

	// todo
	return;
}