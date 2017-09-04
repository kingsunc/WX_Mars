#include "stdafx.h"
#include "MyVersion.h"

CMyVersion::CMyVersion()
{
	memset(m_arrVer, 0, VERSION_COUNT);
}

CMyVersion::CMyVersion(const char* strVesion)
{
	memset(m_arrVer, 0, VERSION_COUNT*sizeof(int) ) ;
	char chTemp[10] = { 0 };

	int iSize = strlen(strVesion);
	int iVerCount = 0;
	int iIndex = 0;
	for (int i = 0; i < iSize; i++)
	{
		if (strVesion[i] == '.')
		{
			m_arrVer[iVerCount++] = atoi(chTemp);
			memset(chTemp, 0, 10*sizeof(char) );
			iIndex = 0;
		}
		else
		{
			chTemp[iIndex++] = strVesion[i];
		}
	}
	m_arrVer[iVerCount++] = atoi(chTemp);
}

CMyVersion::~CMyVersion()
{
}

void CMyVersion::GetFileDescriptionAndProductVersionA(LPCSTR lpstrFilename,
	LPSTR lpoutFileDescription, UINT cbDescSize,
	LPSTR lpoutProductVersion, UINT cbVerSize)

{
	typedef DWORD(WINAPI *pfnGetFileVersionInfoSizeA)(LPCSTR, LPDWORD);
	typedef BOOL(WINAPI *pfnGetFileVersionInfoA)(LPCSTR, DWORD, DWORD, LPVOID);
	typedef BOOL(WINAPI *pfnVerQueryValueA)(const LPVOID, LPCSTR, LPVOID*, PUINT);

	HMODULE hDll = 0;
	DWORD   dwHandle = 0;
	DWORD   dwInfoSize = 0;

	pfnGetFileVersionInfoSizeA   fnGetFileVersionInfoSizeA = 0;
	pfnGetFileVersionInfoA       fnGetFileVersionInfoA = 0;
	pfnVerQueryValueA            fnVerQueryValueA = 0;
	*lpoutFileDescription = 0;
	*lpoutProductVersion = 0;

	// Load system32\version.dll module
	hDll = LoadLibraryA("version.dll");
	if (!hDll)
	{
		return;
	}

	fnGetFileVersionInfoSizeA = (pfnGetFileVersionInfoSizeA)GetProcAddress(hDll, "GetFileVersionInfoSizeA");
	fnGetFileVersionInfoA = (pfnGetFileVersionInfoA)GetProcAddress(hDll, "GetFileVersionInfoA");
	fnVerQueryValueA = (pfnVerQueryValueA)GetProcAddress(hDll, "VerQueryValueA");

	// If failed  to get procdure address
	if (!fnGetFileVersionInfoSizeA || !fnGetFileVersionInfoA || !fnVerQueryValueA)
	{
		FreeLibrary(hDll);
		return;
	}

	dwInfoSize = fnGetFileVersionInfoSizeA(lpstrFilename, &dwHandle);
	if (dwInfoSize > 0)
	{
		void *pvInfo = malloc(dwInfoSize);
		if (!pvInfo)
		{
			exit(-1);   // Out of memory
		}

		if (fnGetFileVersionInfoA(lpstrFilename, 0, dwInfoSize, pvInfo))
		{
			struct LANGANDCODEPAGE 
			{
				WORD wLanguage;
				WORD wCodePage;
			}
			*lpTranslate;

			// Read the list of languages and code pages.
			UINT cbTranslate = 0;
			if (fnVerQueryValueA(pvInfo, "\\VarFileInfo\\Translation", (void**)&lpTranslate, &cbTranslate))
			{
				// ONLY Read the file description for FIRST language and code page.
				if ((cbTranslate / sizeof(struct LANGANDCODEPAGE)) > 0)
				{
					const char *lpBuffer = 0;
					UINT  cbSizeBuf = 0;
					char  szSubBlock[50];

					// Retrieve file description for language and code page 0
					wsprintfA(szSubBlock, "\\StringFileInfo\\%04x%04x\\FileDescription", lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);
					if (fnVerQueryValueA(pvInfo, szSubBlock, (void**)&lpBuffer, &cbSizeBuf))
					{
						//warning4996: strncpy(lpoutFileDescription, lpBuffer, cbDescSize-1);
						strncpy_s(lpoutFileDescription, cbDescSize, lpBuffer, cbDescSize - 1);
						lpoutFileDescription[cbDescSize - 1] = 0;
					}

					// Retrieve file version for language and code page 0
					wsprintfA(szSubBlock, "\\StringFileInfo\\%04x%04x\\ProductVersion", lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);
					if (fnVerQueryValueA(pvInfo, szSubBlock, (void**)&lpBuffer, &cbSizeBuf))
					{
						//warning4996: strncpy(lpoutProductVersion, lpBuffer, cbVerSize-1);
						strncpy_s(lpoutProductVersion, cbVerSize, lpBuffer, cbVerSize - 1);
						lpoutProductVersion[cbVerSize - 1] = 0;
					}

					// Retrieve others for language and code page 0 if you like
					// ...
				}
			}
		}

		// Free memory
		free(pvInfo);
	}

	// Free mudule
	FreeLibrary(hDll);
}

int CMyVersion::Compare(const CMyVersion& otherVer)
{
	for (int i = 0; i < VERSION_COUNT; i++)
	{
		if (m_arrVer[i] == otherVer.m_arrVer[i])
		{
			continue;
		}
		else
		{
			if (m_arrVer[i] <= otherVer.m_arrVer[i])
			{
				return -1;
			} 
			else
			{
				return 1;
			}
		}
	}

	return 0;
}