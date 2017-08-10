#pragma once
#include "MarsWrapper.h"
#include "PSIMCallBack.h"

class CPSIMTaskCallback: public Login_Callback
{
private:
	CPSIMTaskCallback();

public:
	~CPSIMTaskCallback();

	static CPSIMTaskCallback* GetInstance();

	static void ReleaseInstance();

protected:
	// 回调处理;
	virtual void OnResponse(Login_Task* task, MessageService::LoginResp& response);


private:
	CPSIMCallBack* GetPSIMCallBack();

private:
	static CPSIMTaskCallback* m_pInstance;
};