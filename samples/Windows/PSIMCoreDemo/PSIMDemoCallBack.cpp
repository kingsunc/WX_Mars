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

// 删除群-回调处理;
void CPSIMDemoCallBack::OnDeleteGroupResponse(const PSDeleteGroupResp& respDeleteeGroup)
{
	printf("CPSIMDemoCallBack::OnDeleteGroupResponse: iCode(%d), strInfo(%s) \n", respDeleteeGroup.iStatus, respDeleteeGroup.strMessage);
}

// 移除群成员-回调处理;
void CPSIMDemoCallBack::OnRemoveGroupUsersResponse(const PSRemoveGroupUsersResp& respRemoveGroupUsers)
{
	printf("CPSIMDemoCallBack::OnRemoveGroupUsersResponse: iCode(%d), strInfo(%s) \n", respRemoveGroupUsers.iStatus, respRemoveGroupUsers.strMessage);
}

// 添加子群-回调处理;
void CPSIMDemoCallBack::OnAddGroupChildsResponse(const PSAddGroupChildsResp& respAddGroupChilds)
{
	printf("CPSIMDemoCallBack::OnAddGroupChildsResponse: iCode(%d), strInfo(%s) \n", respAddGroupChilds.iStatus, respAddGroupChilds.strMessage);
}

// 移除子群-回调处理;
void CPSIMDemoCallBack::OnRemoveGroupChildsResponse(const PSRemoveGroupChildsResp& respRemoveGroupChilds)
{
	printf("CPSIMDemoCallBack::OnRemoveGroupChildsResponse: iCode(%d), strInfo(%s) \n", respRemoveGroupChilds.iStatus, respRemoveGroupChilds.strMessage);
}