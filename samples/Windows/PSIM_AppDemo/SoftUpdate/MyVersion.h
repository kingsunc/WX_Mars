#pragma once

#define VERSION_COUNT	4

class CMyVersion
{
public:
	CMyVersion();
	CMyVersion(const char* strVesion);
	~CMyVersion();

	// 根据路径获取文件版本信息;
	static void GetFileDescriptionAndProductVersionA(LPCSTR lpstrFilename,
		LPSTR lpoutFileDescription, UINT cbDescSize,
		LPSTR lpoutProductVersion, UINT cbVerSize);

	// 与otherVer进行比较;
	// 若版本号小于otherVer 则返回-1;
	// 若版本号等于otherVer 则返回0;
	// 若版本号大于otherVer 则返回1;
	int Compare(const CMyVersion& otherVer);

private:
	int		m_arrVer[VERSION_COUNT];
};

