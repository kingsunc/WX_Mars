#pragma once

#ifdef TBASE_EXPORTS
#define TBASE_API  _declspec(dllexport)
#else
#define TBASE_API  _declspec(dllimport)
#endif