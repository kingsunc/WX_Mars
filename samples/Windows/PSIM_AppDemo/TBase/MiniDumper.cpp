//========================================================================
// Minidump.cpp : This is a crash trapper - similar to a UNIX style core dump
//========================================================================
#include <time.h>
#include "MiniDumper.h"
#include <assert.h>
#include "TString/TStringTool.h"
#include <direct.h>

#pragma comment(lib, "version.lib")

// based on dbghelp.h
typedef BOOL(WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess, unsigned long dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType,
	CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
	CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
	CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam
	);

MiniDumper *MiniDumper::g_pDumper = NULL;

// MiniDumper::MiniDumper			
//
MiniDumper::MiniDumper(bool bSetDump, std::string strOutPath) : m_strOutPath(strOutPath)
{
	// Detect if there is more than one MiniDumper.
	assert(!g_pDumper);
	if (!g_pDumper)
	{
		g_pDumper = this;
		if (bSetDump)
		{
			::SetUnhandledExceptionFilter(Handler);
		}
	}
}

// MiniDumper::Handler			
//
LONG MiniDumper::Handler(_EXCEPTION_POINTERS *pExceptionInfo)
{
	LONG retval = EXCEPTION_CONTINUE_SEARCH;
	if (!g_pDumper)
	{
		return retval;
	}

	return g_pDumper->WriteMiniDump(pExceptionInfo);
}

//
// MiniDumper::WriteMiniDump			
//
LONG MiniDumper::WriteMiniDump(_EXCEPTION_POINTERS *pExceptionInfo)
{
	LONG retval = EXCEPTION_CONTINUE_SEARCH;
	// You have to find the right dbghelp.dll. 
	// Look next to the EXE first since the one in System32 might be old (Win2k)

	HMODULE hHelper = NULL;
	hHelper = ::LoadLibraryA("BugHelp.DLL");
	if (NULL == hHelper)
	{
		std::string strDllPath = m_strOutPath + "\\BugHelp.DLL";;
		hHelper = ::LoadLibraryA(strDllPath.c_str());
	}

	LPCTSTR szResult = NULL;
	if (hHelper)
	{
		MINIDUMPWRITEDUMP pMiniDumpWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hHelper, "MiniDumpWriteDump");

		if (pMiniDumpWriteDump)
		{
			TCHAR szScratch[USER_DATA_BUFFER_SIZE];

			SYSTEMTIME timeInfo;
			GetLocalTime(&timeInfo);

			_mkdir(".\\CrashDumps");
			TCHAR strDumpPath[_MAX_PATH];
			wsprintf(strDumpPath, _T("%s\\CrashDumps\\khb_%.4d%.2d%.2d_%.2d%.2d%.2d_%.6d-%s.dmp"), _A2T(m_strOutPath).c_str(), timeInfo.wYear, timeInfo.wMonth, timeInfo.wDay,
				timeInfo.wHour, timeInfo.wMinute, timeInfo.wSecond, timeInfo.wMilliseconds, _T("test"));

			// ask the user if they want to save a dump file
			//_tcssprintf(szScratch, _T("There was an unexpected error:\n\n%s\nWould you like to save a diagnostic file?\n\nFilename: %s"), VGetUserMessage(), m_szDumpPath);
			//wsprintf(szScratch, _T("There was an unexpected error:\n\n%s\nWould you like to save a diagnostic file?\n\nFilename: %s"), VGetUserMessage(), strDumpPath);
			{
				// create the file
				HANDLE hFile = ::CreateFile(strDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL, NULL);

				if (hFile != INVALID_HANDLE_VALUE)
				{
					_MINIDUMP_EXCEPTION_INFORMATION ExInfo;

					ExInfo.ThreadId = ::GetCurrentThreadId();
					ExInfo.ExceptionPointers = pExceptionInfo;
					ExInfo.ClientPointers = NULL;

					// write the dump
					BOOL bOK = pMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
					if (bOK)
					{
						szResult = NULL;
						retval = EXCEPTION_EXECUTE_HANDLER;
					}
					else
					{
						//_tcssprintf( szScratch, _T("Failed to save dump file to '%s' (error %d)"), m_szDumpPath, GetLastError() );
						wsprintf(szScratch, _T("Failed to save dump file to '%s' (error %d)"), strDumpPath, GetLastError());
						szResult = szScratch;
					}
					::MessageBox(NULL, strDumpPath, NULL, NULL);
					::CloseHandle(hFile);
				}
				else
				{
					//_tcssprintf( szScratch, _T("Failed to create dump file '%s' (error %d)"), m_szDumpPath, GetLastError() );
					wsprintf(szScratch, _T("Failed to create dump file '%s' (error %d)"), strDumpPath, GetLastError());
					szResult = szScratch;
				}
			}
		}
		else
		{
			szResult = _T("DBGHELP.DLL too old");
		}
	}
	else
	{
		szResult = _T("DBGHELP.DLL not found");
	}

	FreeLibrary(hHelper);
	TerminateProcess(GetCurrentProcess(), 0);

	// MLM Note: ExitThread will work, and it allows the MiniDumper to kill a crashed thread
	// without affecting the rest of the application. The question of the day:
	//   Is That A Good Idea??? Answer: ABSOLUTELY NOT!!!!!!!
	//
	//ExitThread(0);

	return retval;
}