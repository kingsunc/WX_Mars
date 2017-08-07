#pragma once
#include <windows.h>
#include "PSDefs.h"

#ifdef PSCORE_EXPORTS
#define PSCORE_API __declspec(dllexport)
#else
#define PSCORE_API __declspec(dllimport)
#endif

class PSCORE_API CPSCoreCallBack
{
public:
	CPSCoreCallBack();
	virtual ~CPSCoreCallBack();
};

