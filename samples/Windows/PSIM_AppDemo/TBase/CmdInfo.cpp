#include "CmdInfo.h"
#include "JsonValueEx.h"
#include <assert.h>

CmdManager* CmdManager::m_pInstance = NULL;
CLiveLockEx CmdManager::m_lockInst;

CmdManager::CmdManager() : m_bStop(true), m_hThCmd(NULL)
{
}

CmdManager::~CmdManager()
{
}

void CmdManager::AddCmd(IN TString& strCmd, IN Curl_CallBack pFunc /*= NULL*/)
{
	CmdItem cmdItem;
	cmdItem.cmdInfo.strCmd = strCmd;
	cmdItem.pFunc = pFunc;
	AddCmd(cmdItem);
}

void CmdManager::AddCmd(IN CmdItem& cmdInfo)
{
	if (NULL == m_hThCmd)
	{
		m_hThCmd = CreateThread(NULL, 0, Th_Cmd, this, 0, &m_dwThreadID); // 创建线程;
		m_bStop = false;
	}
	m_lockList.Lock();
	m_listCmd.push_back(cmdInfo);
	m_lockList.UnLock();
}

void CmdManager::DeInit()
{
	m_bStop = true;
	if (WAIT_TIMEOUT == WaitForSingleObject(m_hThCmd, 20))
	{
		TerminateThread(m_hThCmd, 0x10);
	}
	m_hThCmd = NULL;
}

DWORD WINAPI CmdManager::Th_Cmd(LPVOID lpParam)
{
	CmdManager *pThis = static_cast<CmdManager*>(lpParam);
	assert(pThis);

	CmdList list;
	while ((!pThis->m_bStop) && (pThis->m_hThCmd))
	{
		list.clear();
		pThis->m_lockList.Lock();
		pThis->m_listCmd.swap(list);
		pThis->m_lockList.UnLock();
		if (list.empty())
		{
			Sleep(1);
			continue;
		}

		CmdList::iterator it = list.begin();
		for (; it != list.end(); ++it)
		{
			it->cmdInfo.bSucess = true;
			it->cmdInfo.jsResult.clear();
			it->cmdInfo.iErrorCode = 0;
			it->cmdInfo.strError = _T("");

			CmdItem* pItem = new CmdItem(*it);
			DWORD dwThreadID = 0;
			CreateThread(NULL, 0, Th_Cmd_Excute, (LPVOID)pItem, 0, &dwThreadID); // 创建线程;
		}
	}
	return 0;
}

DWORD CmdManager::Th_Cmd_Excute(LPVOID lpParam)
{
	CmdItem* pItem = static_cast<CmdItem*>(lpParam);
	assert(pItem);
	CCurlEx curlEx;
	if (!curlEx.PostData(pItem->cmdInfo.jsResult, pItem->cmdInfo.strUrl, pItem->cmdInfo.strPara))
	{
		pItem->cmdInfo.bSucess = false;
		//it->cmdInfo.iErrorCode = _ttoi(it->cmdInfo.jsResult["state"].GetTString().c_str());
		pItem->cmdInfo.strError = curlEx.GetErrorInfo();
	}

	if (NULL != pItem->pFunc)
	{
		pItem->pFunc(pItem->cmdInfo);
	}

	delete pItem;
	pItem = NULL;

	return 1;
}

CmdManager* CmdManager::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_lockInst.Lock();
		if (NULL == m_pInstance)
		{
			m_pInstance = new CmdManager();
		}
		m_lockInst.UnLock();
	}
	return m_pInstance;
}

void CmdManager::ReleaseInstance()
{
	if (NULL != m_pInstance)
	{
		m_lockInst.Lock();
		if (NULL != m_pInstance)
		{
			m_pInstance->DeInit();
			delete m_pInstance;
			m_pInstance = NULL;
		}
		m_lockInst.UnLock();
	}
}