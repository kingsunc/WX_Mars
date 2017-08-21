#include "JsonObjectBase.h"

CJsonObjectBase::CJsonObjectBase()
{
}

CJsonObjectBase::~CJsonObjectBase()
{
}

std::string CJsonObjectBase::Serialize()
{
	Json::Value new_item = DoSerialize();
	Json::FastWriter writer;
	std::string strOut = writer.write(new_item);
	return strOut;
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
		case asInt:
			new_item[m_vectorName[i]] = Serialize<INT>(pAddr);
			break;
		case asUInt:
			new_item[m_vectorName[i]] = Serialize<UINT>(pAddr);
			break;
		case asDouble:
			new_item[m_vectorName[i]] = Serialize<double>(pAddr);
			break;
		case asString:
			new_item[m_vectorName[i]] = Serialize<std::string>(pAddr);
		default:
			// 我暂时只支持这几种类型，需要的可以自行添加  
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
				{
					((CJsonObjectBase*)pAddr)->DoDeSerialize(root[m_vectorName[i]]);
				}
			}
			break;
		case asBool:
			{
				(*(bool*)pAddr) = root.get(m_vectorName[i], 0).asBool();
			}
			break;
		case asInt:
			{
				(*(INT*)pAddr) = root.get(m_vectorName[i], 0).asInt();
			}
			break;
		case asUInt:
			{
				(*(UINT*)pAddr) = root.get(m_vectorName[i], 0).asUInt();
			}
			break;
		case asDouble:
			{
				(*(double*)pAddr) = root.get(m_vectorName[i], 0).asDouble();
			}
			break;
		case asString:
			{
				(*(std::string*)pAddr) = root.get(m_vectorName[i], "").asString();
			}
		default:
			//我暂时只支持这几种类型，需要的可以自行添加     
			break;
		}
	}
	return true;
}

void CJsonObjectBase::SetProperty(std::string name, CEnumJsonTypeMap type, void* addr, CEnumJsonTypeMap listParamType )
{
	m_vectorName.push_back(name);
	m_vectorPropertyAddr.push_back(addr);
	m_vectorType.push_back(type);
	m_vectorListParamType.push_back(listParamType);
}

// 有特殊对象需要序列化时，请重载此函数   
Json::Value CJsonObjectBase::DoSpecialArraySerialize(const std::string& propertyName)
{
	return "";
}

//在反序列化时，如果对象中嵌套了列表，并且列表中容纳的内容是其他特殊对象时，需要重载此函数，new出真正的对象  
CJsonObjectBase* CJsonObjectBase::GenerateJsonObjForDeSerialize(const std::string& propertyName)
{
	return NULL;
}

bool CJsonObjectBase::DoArrayDeSerialize(const std::string& propertyName, void* addr, Json::Value& root, CEnumJsonTypeMap listType, CEnumJsonTypeMap paramType)
{
	if (listType == asVectorArray)
	{
		switch (paramType)
		{
		case asJsonObj:
		{
			return DoObjArrayDeSerialize_Wrapper(std::vector, CJsonObjectBase*)(propertyName, addr, root);
		}
		break;
		case asBool:
			//无   
			break;
		case asInt:
			return DoArrayDeSerialize_Wrapper(std::vector, INT)(addr, root);
		case asUInt:
			return DoArrayDeSerialize_Wrapper(std::vector, UINT)(addr, root);
		case asDouble:
			return DoArrayDeSerialize_Wrapper(std::vector, double)(addr, root);
		case asString:
			return DoArrayDeSerialize_Wrapper(std::vector, std::string)(addr, root);
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
			return DoObjArrayDeSerialize_Wrapper(std::list, CJsonObjectBase*)(propertyName, addr, root);
		}
		break;
		case asBool:
			return DoArrayDeSerialize_Wrapper(std::list, bool)(addr, root);
		case asInt:
			return DoArrayDeSerialize_Wrapper(std::list, INT)(addr, root);
		case asUInt:
			return DoArrayDeSerialize_Wrapper(std::list, UINT)(addr, root);
		case asDouble:
			return DoArrayDeSerialize_Wrapper(std::list, double)(addr, root);
		case asString:
			return DoArrayDeSerialize_Wrapper(std::list, std::string)(addr, root);
		default:
			break;
		}
	}

	return true;
}