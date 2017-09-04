#pragma once
#include <string>
#include <vector>

#pragma warning(disable:4005)
#pragma warning(disable:4251)

#ifdef UNICODE
typedef std::wstring	TString;
#ifndef _T
#define _T(x) L ## x
#endif
#else
typedef std::string		TString;
#ifndef _T
#define _T(x) x
#endif 
#endif

//#ifdef UNICODE
//typedef std::basic_string<wchar_t> TString;
//#else
//typedef std::basic_string<char> TString;
//#endif 

typedef std::vector<TString> VecTString;