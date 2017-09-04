#include "PSIMDemoCallBack.h"

CPSIMDemoCallBack::CPSIMDemoCallBack()
{
}

CPSIMDemoCallBack::~CPSIMDemoCallBack()
{
}

// 添加子群-回调处理;
void CPSIMDemoCallBack::OnAddGroupChildsResponse(const PSResp& resp)
{
	printf("CPSIMDemoCallBack::OnAddGroupChildsResponse: iCode(%d), strInfo(%s) \n", resp.iStatus, resp.strMessage.GetString());
}

// 移除子群-回调处理;
void CPSIMDemoCallBack::OnRemoveGroupChildsResponse(const PSResp& resp)
{
	printf("CPSIMDemoCallBack::OnRemoveGroupChildsResponse: iCode(%d), strInfo(%s) \n", resp.iStatus, resp.strMessage.GetString());
}