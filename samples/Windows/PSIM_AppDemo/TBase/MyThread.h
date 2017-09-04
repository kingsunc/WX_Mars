#pragma once
#include <windows.h> 
#include "TBaseExport.h"
#include "TString/TStringTool.h"

class TBASE_API CMyThread
{
public:
	CMyThread(const std::string& strame);
	virtual ~CMyThread();

	void Start();
	void Join();

	bool IsStarted() const { return m_bStarted; }
	const char* GetName() const { return m_strName; }
	static int GetThreadNum() { return m_uiThreadNum; }

private:
	static unsigned int __stdcall StartThread(void* pThis);
	virtual void RunThread() = 0;

	bool			m_bStarted;
	uintptr_t		m_uiThreadId;
	char			m_strName[MAX_PATH];
	static volatile unsigned int m_uiThreadNum;
};