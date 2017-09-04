#pragma once
#include "Json\json.h"
#include "TString\TStringTool.h"
#include <sstream>
#include <windows.h>
#include "TBaseExport.h"

using namespace Json;

class TBASE_API JsonValueEx : public Value
{
public:
	JsonValueEx(ValueType tType = nullValue) : Value(tType)
	{

	}
	JsonValueEx(Int iVal) : Value(iVal)
	{

	}
	JsonValueEx(UInt uiVal) : Value(uiVal)
	{

	}
#ifdef JSON_HAS_INT64
	JsonValueEx(Int64 iVal) : Value(iVal)
	{

	}
	JsonValueEx(UInt64 uiVal) : Value(uiVal)
	{

	}
#endif // if defined(JSON_HAS_INT64)
	JsonValueEx(double dVal) : Value(dVal)
	{

	}
	JsonValueEx(const char* pVal) : Value(pVal)
	{

	}
	JsonValueEx(const char* pBegin, const char* pEnd) : Value(pBegin, pEnd)
	{

	}

	JsonValueEx(const StaticString& strVal) : Value(strVal)
	{

	}
	JsonValueEx(const std::string& strVal) : Value(strVal)
	{

	}
#ifdef JSON_USE_CPPTL
	JsonValueEx(const CppTL::ConstString& strVal) : Value(strVal)
	{

	}
#endif
	JsonValueEx(bool bVal) : Value(bVal)
	{

	}
	JsonValueEx(JsonValueEx& valOther) : Value(valOther)
	{

	}
	~JsonValueEx()
	{

	}

	JsonValueEx& operator=(const JsonValueEx& valOther)
	{
		Value::operator = (valOther);
		return *this;
	}

	JsonValueEx& operator=(int iVal)
	{
		JsonValueEx valOther(iVal);
		Value::operator = (valOther);
		return *this;
	}

	JsonValueEx& operator=(double dVal)
	{
		JsonValueEx valOther(dVal);
		Value::operator = (valOther);
		return *this;
	}

	JsonValueEx& operator=(const char* pVal)
	{
		JsonValueEx valOther(pVal);
		Value::operator = (valOther);
		return *this;
	}

	JsonValueEx& operator=(bool bVal)
	{
		JsonValueEx valOther(bVal);
		Value::operator = (valOther);
		return *this;
	}

	bool operator < (JsonValueEx& valOther) const
	{
		return Value::operator < (valOther);
	}
	bool operator <=(JsonValueEx& valOther) const
	{
		return Value::operator <= (valOther);
	}
	bool operator >=(JsonValueEx& valOther) const
	{
		return Value::operator >= (valOther);
	}
	bool operator > (JsonValueEx& valOther) const
	{
		return Value::operator > (valOther);
	}

	bool operator ==(JsonValueEx& valOther) const
	{
		return Value::operator == (valOther);
	}
	bool operator !=(JsonValueEx& valOther) const
	{
		return Value::operator != (valOther);
	}

	JsonValueEx& operator[](int iIndex)
	{
		//if (iIndex < 0 ||  iIndex > (int)size())
		//{
		//	// 抛出异常并打印日志;
		//	throw std::exception();
		//}

		JsonValueEx* p = static_cast<JsonValueEx*> (&(Value::operator[](iIndex)));
		return *p;
	}
	JsonValueEx& operator[](const char* pKey)
	{
		//if (nullValue == type())
		//{
		//	// 抛出异常并打印日志;
		//	//LOG_WARN(pKey )
		//}

		JsonValueEx* p = static_cast<JsonValueEx*> (&(Value::operator[](pKey)));
		return *p;
	}
	JsonValueEx& operator[](const std::string& strKey)
	{
		//if (nullValue == type())
		//{
		//	// 抛出异常并打印日志;
		//	throw std::exception();
		//}

		JsonValueEx* p = static_cast<JsonValueEx*> (&(Value::operator[](strKey)));
		return *p;
	}
	JsonValueEx& operator[](const StaticString& strKey)
	{
		//if (nullValue == type())
		//{
		//	// 抛出异常并打印日志;
		//	throw std::exception();
		//}

		JsonValueEx* p = static_cast<JsonValueEx*> (&(Value::operator[](strKey)));
		return *p;
	}

	std::string GetOrgString()
	{
		// 获取未转化时的原版字符;
		std::stringstream strStream;
		std::string strResult;
		switch (type())
		{
		case nullValue:		//	'null' value;
			{
								//打印日志或者抛出异常;
			}
			break;
		case intValue:		//	igned integer value;
			{
								strStream << asInt();
								strStream >> strResult;
			}
			break;
		case uintValue:		//	unsigned integer value
			{
								strStream << asUInt();
								strStream >> strResult;
			}
			break;
		case realValue:		//	double value
			{
								long long dValue = (long long)(asDouble());
								strStream << dValue;
								strResult = strStream.str();
			}
			break;
		case stringValue:	//	UTF-8 string value
			{
								strResult = asString();
			}
			break;
		case booleanValue:	//	bool value
			{
								strResult = asBool() ? "1" : "0";
			}
			break;
		case arrayValue:	//	array value (ordered list)
			{
			}
			break;
		case objectValue:	//	object value (collection of name/value pairs).
			{
			}
			break;
		default:
			{
			}
			break;
		};

		return strResult;
	}

	std::string GetString()
	{
		// UTF转化为多字节;
		std::string strUtf8 = GetOrgString();
		std::string strAnsi = TStringTool::Utf8ToAnsi(strUtf8.c_str(), strUtf8.length());
		return strAnsi;
	}

	TString GetTString()
	{
		// UTF转化为宽字节;
		std::string strUtf8 = GetOrgString();
		TString wstrAnsi = TStringTool::UTF8_2_WS(strUtf8);
		return wstrAnsi;
	}

	TString ToStyledTString()
	{
		std::string strVal = toStyledString();
		return _A2T(strVal);
	}
};