#include "JsonObjectBase.h"

CJsonObjectBase::CJsonObjectBase()
{

}

CJsonObjectBase::~CJsonObjectBase()
{

}

string CJsonObjectBase::Serialize()
{
	Json::Value new_item = DoSerialize();
	Json::FastWriter writer;
	std::string out2 = writer.write(new_item);
	return out2;
}

bool CJsonObjectBase::DeSerialize(const char* str)
{
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(str, root))
	{
		return DoDeSerialize(root);
	}
	return false;
}

Json::Value CJsonObjectBase::DoSerialize()
{
	Json::Value new_item;
	int nSize = m_vectorName.size();
	for (int i = 0; i < nSize; ++i)
	{
		void* pAddr = m_vectorPropertyAddr[i];
		switch (m_vectorType[i])
		{
		case asVectorArray:
		case asListArray:
			new_item[m_vectorName[i]] = DoArraySerialize(pAddr, m_vectorType[i], m_vectorListParamType[i]);
			break;
		case asSpecialArray:
			new_item[m_vectorName[i]] = DoSpecialArraySerialize(m_vectorName[i]);
			break;
		case asJsonObj:
			new_item[m_vectorName[i]] = ((CJsonObjectBase*)pAddr)->DoSerialize();
			break;
		case asBool:
			new_item[m_vectorName[i]] = Serialize<bool>(pAddr);
			break;
		case asInt:
			new_item[m_vectorName[i]] = Serialize<INT>(pAddr);
			break;
		case asUInt:
			new_item[m_vectorName[i]] = Serialize<UINT>(pAddr);
			break;
		case asInt64:
			new_item[m_vectorName[i]] = Serialize<LONGLONG>(pAddr);
			break;
		case asUInt64:
			new_item[m_vectorName[i]] = Serialize<ULONGLONG>(pAddr);
			break;
		case asString:
			new_item[m_vectorName[i]] = Serialize<string>(pAddr);
		default:
			//我暂时只支持这几种类型，需要的可以自行添加  
			break;
		}
	}
	return new_item;
}

bool CJsonObjectBase::DoDeSerialize(Json::Value& root)
{
	int nSize = m_vectorName.size();
	for (int i = 0; i < nSize; ++i)
	{
		void* pAddr = m_vectorPropertyAddr[i];

		switch (m_vectorType[i])
		{
		case asListArray:
		case asVectorArray:
		{
			if (root.isNull() || root[m_vectorName[i]].isNull())
			{
				break;
			}
			DoArrayDeSerialize(m_vectorName[i], pAddr, root[m_vectorName[i]], m_vectorType[i], m_vectorListParamType[i]);
		}
		break;
		case asJsonObj:
		{
			if (!root[m_vectorName[i]].isNull())
				((CJsonObjectBase*)pAddr)->DoDeSerialize(root[m_vectorName[i]]);
		}
		break;
		case asBool:
			(*(bool*)pAddr) = root.get(m_vectorName[i], 0).asBool();
			break;
		case asInt:
			(*(INT*)pAddr) = root.get(m_vectorName[i], 0).asInt();
			break;
		case asUInt:
			(*(UINT*)pAddr) = root.get(m_vectorName[i], 0).asUInt();
			break;
		case asInt64:
			(*(LONGLONG*)pAddr) = root.get(m_vectorName[i], 0).asInt64();
			break;
		case asUInt64:
			(*(ULONGLONG*)pAddr) = root.get(m_vectorName[i], 0).asUInt64();
			break;
		case asString:
			(*(string*)pAddr) = root.get(m_vectorName[i], "").asString();
		default:
			// 我暂时只支持这几种类型，需要的可以自行添加;
			break;
		}
	}
	return true;
}

void CJsonObjectBase::SetProperty(string name, CEnumJsonTypeMap type, void* addr, CEnumJsonTypeMap listParamType /*= asInt*/)
{
	m_vectorName.push_back(name);
	m_vectorPropertyAddr.push_back(addr);
	m_vectorType.push_back(type);
	m_vectorListParamType.push_back(listParamType);
}

Json::Value CJsonObjectBase::DoSpecialArraySerialize(const string& propertyName)
{
	return "";
}

CJsonObjectBase* CJsonObjectBase::GenerateJsonObjForDeSerialize(const string& propertyName)
{
	return NULL;
}

bool CJsonObjectBase::DoArrayDeSerialize(const string& propertyName, void* addr, Json::Value& root, CEnumJsonTypeMap listType, CEnumJsonTypeMap paramType)
{
	if (listType == asVectorArray)
	{
		switch (paramType)
		{
		case asJsonObj:
		{
			return DoObjArrayDeSerialize_Wrapper(vector, CJsonObjectBase*)(propertyName, addr, root);
		}
		break;
		case asBool:
			//无   
			break;
		case asInt:
			return DoArrayDeSerialize_Wrapper(vector, INT)(addr, root);
		case asUInt:
			return DoArrayDeSerialize_Wrapper(vector, UINT)(addr, root);
		case asInt64:
			return DoArrayDeSerialize_Wrapper(vector, LONGLONG)(addr, root);
		case asUInt64:
			return DoArrayDeSerialize_Wrapper(vector, ULONGLONG)(addr, root);
		case asString:
			return DoArrayDeSerialize_Wrapper(vector, string)(addr, root);
		default:
			break;
		}
	}
	else if (listType == asListArray)
	{
		switch (paramType)
		{
		case asJsonObj:
		{
			return DoObjArrayDeSerialize_Wrapper(list, CJsonObjectBase*)(propertyName, addr, root);
		}
		break;
		case asBool:
			return DoArrayDeSerialize_Wrapper(list, bool)(addr, root);
		case asInt:
			return DoArrayDeSerialize_Wrapper(list, INT)(addr, root);
		case asUInt:
			return DoArrayDeSerialize_Wrapper(list, UINT)(addr, root);
		case asInt64:
			return DoArrayDeSerialize_Wrapper(list, LONGLONG)(addr, root);
		case asUInt64:
			return DoArrayDeSerialize_Wrapper(list, ULONGLONG)(addr, root);
		case asString:
			return DoArrayDeSerialize_Wrapper(list, string)(addr, root);
		default:
			break;
		}
	}

	return true;
}

Json::Value CJsonObjectBase::DoArraySerialize(void * addr, CEnumJsonTypeMap listType, CEnumJsonTypeMap paramType)
{
	if (listType == asVectorArray)
	{
		switch (paramType)
		{
		case asBool:
			return "";
		case asJsonObj:
			return DoArraySerialize_Wrapper(vector, CJsonObjectBase*);
		case asInt:
			return DoArraySerialize_Wrapper(vector, INT);
		case asUInt:
			return DoArraySerialize_Wrapper(vector, UINT);
		case asInt64:
			return DoArraySerialize_Wrapper(vector, LONGLONG);
		case asUInt64:
			return DoArraySerialize_Wrapper(vector, ULONGLONG);
		case asString:
			return DoArraySerialize_Wrapper(vector, string);
		}
	}
	else
	{
		switch (paramType)
		{
		case asBool:
			return DoArraySerialize_Wrapper(list, bool);
		case asJsonObj:
			return DoArraySerialize_Wrapper(list, CJsonObjectBase*);
		case asInt:
			return DoArraySerialize_Wrapper(list, INT);
		case asUInt:
			return DoArraySerialize_Wrapper(list, UINT);
		case asInt64:
			return DoArraySerialize_Wrapper(list, LONGLONG);
		case asUInt64:
			return DoArraySerialize_Wrapper(list, ULONGLONG);
		case asString:
			return DoArraySerialize_Wrapper(list, string);
		}
	}
	return "";
}