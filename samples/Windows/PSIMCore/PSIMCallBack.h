#pragma once

class CPSIMCallBack
{
public:
	CPSIMCallBack() {};
	virtual ~CPSIMCallBack() {};

	virtual void OnLoginResponse(const int& iCode, const char* strInfo) = 0;
};

