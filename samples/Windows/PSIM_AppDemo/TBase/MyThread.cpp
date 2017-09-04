#include "MyThread.h"
#include <assert.h>  
#include <process.h>  
#include "Log4z.h"

volatile unsigned int CMyThread::m_uiThreadNum = 0;

CMyThread::CMyThread(const std::string& strName)
: m_bStarted(false), m_uiThreadId(0)
{
	memcpy_s(m_strName, MAX_PATH, strName.c_str(), strName.length());
	InterlockedIncrement(&m_uiThreadNum);
}

CMyThread::~CMyThread()
{
}

void CMyThread::Start()
{
	assert(!m_bStarted);
	m_bStarted = true;
	m_uiThreadId = _beginthreadex(NULL, 0, StartThread, this, 0, NULL);
	if (0 == m_uiThreadId)
	{
		LOG_ERROR("create thread fail");
	}
}

void CMyThread::Join()
{
	assert(m_bStarted);
	WaitForSingleObject((HANDLE)m_uiThreadId, INFINITE);
}

unsigned int CMyThread::StartThread(void *obj)
{
	CMyThread* pThis = static_cast<CMyThread*>(obj);
	if (pThis)
	{
		pThis->RunThread();
	}

	return 0;
}