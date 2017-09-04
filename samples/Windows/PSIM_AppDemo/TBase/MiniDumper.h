//========================================================================
// Minidump.h : This is a crash trapper - similar to a UNIX style core dump
//========================================================================
#pragma once
#include <windows.h>
#include <tchar.h>
#include <dbghelp.h>
#include "TBaseExport.h"
#include <string>
#pragma warning(disable:4251)

class TBASE_API MiniDumper
{
public:
	MiniDumper(bool bSetDump, std::string strOutPath);

protected:
	static LONG WINAPI Handler(struct _EXCEPTION_POINTERS *pExceptionInfo);
	LONG WriteMiniDump(_EXCEPTION_POINTERS *pExceptionInfo);

private:
	static MiniDumper*	g_pDumper;
	std::string			m_strOutPath;	// Êä³öÄ¿Â¼;
};

#define USER_DATA_BUFFER_SIZE (4096)