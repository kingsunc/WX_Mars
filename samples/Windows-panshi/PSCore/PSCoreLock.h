#pragma once
#include <synchapi.h>

class CPSCoreLock
{
public:

	CPSCoreLock()
	{
		::InitializeCriticalSection(&m_critSec);
	}
	virtual ~CPSCoreLock()
	{
		::DeleteCriticalSection(&m_critSec);
	}

	void Lock()
	{
		::EnterCriticalSection(&m_critSec);
	}
	void UnLock()
	{
		::LeaveCriticalSection(&m_critSec);
	}

private:
	CRITICAL_SECTION	m_critSec;
};