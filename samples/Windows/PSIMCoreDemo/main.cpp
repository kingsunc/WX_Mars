#include <stdio.h>
#include "PSIMDemoCallBack.h"
#include <windows.h>
#include <string>

int main()
{

	CPSIMDemoCallBack* pCallBack = new CPSIMDemoCallBack();
	CPSIMCallFactory::CreateInstance(pCallBack);
	AfxGetPSIMCall()->Init();

	Sleep(2 * 1000);

	AfxGetPSIMCall()->MsgLogin("xes", "token", "100001", "testname", "1111");

	Sleep(2 * 1000);

	int iSeqID = 0;
	std::string strContent = "Hello World";
	AfxGetPSIMCall()->SendTextMessage(iSeqID, PS_SendMode_P2P, "1000", "2000", strContent.c_str(), strContent.length(), "");

	Sleep(2 * 1000);

	const int iDescCount = 3;
	PS_OffMsgDesc_t* pOffMsgDesc = new PS_OffMsgDesc_t[iDescCount];
	memset(pOffMsgDesc, 0, iDescCount * sizeof(PS_OffMsgDesc_t));
	{
		pOffMsgDesc[0].strFrom = "1101";
		pOffMsgDesc[0].strTo = "1102";
		pOffMsgDesc[0].iSendMode = PS_SendMode_P2P;
		pOffMsgDesc[0].iStartMsgID = 10000;
		pOffMsgDesc[0].iMsgCount = 100;

		pOffMsgDesc[1].strFrom = "1101";
		pOffMsgDesc[1].strTo = "1103";
		pOffMsgDesc[1].iSendMode = PS_SendMode_P2P;
		pOffMsgDesc[1].iStartMsgID = 10000;
		pOffMsgDesc[1].iMsgCount = 100;

		pOffMsgDesc[2].strFrom = "1101";
		pOffMsgDesc[2].strTo = "2000";
		pOffMsgDesc[3].iSendMode = PS_SendMode_Group;
		pOffMsgDesc[2].iStartMsgID = 10000;
		pOffMsgDesc[2].iMsgCount = 100;
	}
	AfxGetPSIMCall()->GetOfflineMsgs(pOffMsgDesc, iDescCount);
	delete []pOffMsgDesc;

	getchar();

	AfxGetPSIMCall()->UnInit();
	CPSIMCallFactory::ReleaseInstance();

	return 1;
}