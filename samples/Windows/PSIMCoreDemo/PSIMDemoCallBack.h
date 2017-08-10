#pragma once
#include "PSIMCall.h"

class CPSIMDemoCallBack: public CPSIMCallBack
{
public:
	CPSIMDemoCallBack();
	~CPSIMDemoCallBack();

	virtual void OnLoginResponse(const int& iCode, const char* strInfo);
};