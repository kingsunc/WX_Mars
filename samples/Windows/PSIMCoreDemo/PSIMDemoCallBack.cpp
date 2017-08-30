#include "stdafx.h"
#include "PSIMDemoCallBack.h"
#include <stdio.h>

CPSIMDemoCallBack::CPSIMDemoCallBack()
{
}

CPSIMDemoCallBack::~CPSIMDemoCallBack()
{
}

// 删除群-回调处理;
void CPSIMDemoCallBack::OnDeleteGroupResponse(const PSDeleteGroupResp& resp)
{
	printf("CPSIMDemoCallBack::OnDeleteGroupResponse: iCode(%d), strInfo(%s) \n", resp.iStatus, resp.strMessage.GetString());
}

// 移除群成员-回调处理;
void CPSIMDemoCallBack::OnRemoveGroupUsersResponse(const PSRemoveGroupUsersResp& resp)
{
	printf("CPSIMDemoCallBack::OnRemoveGroupUsersResponse: iCode(%d), strInfo(%s) \n", resp.iStatus, resp.strMessage.GetString());
}

// 添加子群-回调处理;
void CPSIMDemoCallBack::OnAddGroupChildsResponse(const PSAddGroupChildsResp& resp)
{
	printf("CPSIMDemoCallBack::OnAddGroupChildsResponse: iCode(%d), strInfo(%s) \n", resp.iStatus, resp.strMessage.GetString());
}

// 移除子群-回调处理;
void CPSIMDemoCallBack::OnRemoveGroupChildsResponse(const PSRemoveGroupChildsResp& resp)
{
	printf("CPSIMDemoCallBack::OnRemoveGroupChildsResponse: iCode(%d), strInfo(%s) \n", resp.iStatus, resp.strMessage.GetString());
}