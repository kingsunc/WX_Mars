#ifndef _PS_STRING_H
#define _PS_STRING_H
#include <string.h>

// 自定义PSString类
class PSString
{
public:
	// 默认构造函数,用于创建空字符串;
	PSString()
	{
		m_iLen = 0;
		m_pStr = new char[1];
		m_pStr[0] = '\0';
	}
	// 析构函数;
	~PSString()
	{
		delete[]m_pStr;
		m_iLen = 0;
	}

	// 构造函数,带一个参数用来初始化字符串;
	PSString(const char* const pStr)
	{
		if (pStr == NULL)
		{
			m_iLen = 0;
			m_pStr = new char[1];
			memset(m_pStr, 0, m_iLen + 1);
			if (m_pStr == NULL)
			{
				return;
			}
		}
		else
		{
			m_iLen = strlen(pStr);
			m_pStr = new char[m_iLen + 1];
			memset(m_pStr, 0, m_iLen + 1);
			if (m_pStr == NULL)
			{
				return;
			}
			strncpy(m_pStr, pStr, m_iLen);
		}
	}

	// 构造函数,带一个参数用来初始化字符串;
	PSString(const char ch)
	{
		m_iLen = 1;
		m_pStr = new char[m_iLen+1];
		memset(m_pStr, 0, m_iLen + 1);
		strncpy(m_pStr, &ch, m_iLen);
	}

	// 复制构造函数,默认是浅层复制,需重载;
	PSString(const PSString &rs)
	{
		m_iLen = rs.GetLength();
		m_pStr = new char[m_iLen + 1];
		for (unsigned int i = 0; i < m_iLen; i++)
		{
			m_pStr[i] = rs.m_pStr[i];
		}
		m_pStr[m_iLen] = '\0';
	}
	
	// 重载下标运算符[];
	char& operator[](unsigned int length)
	{
		if (length > m_iLen)
		{
			return m_pStr[m_iLen - 1];
		}
		return m_pStr[length];
	}

	// 重载下标运算符[](const版本);
	char operator[](unsigned int length)const
	{
		if (length > m_iLen)
		{
			return m_pStr[m_iLen - 1];
		}
		return m_pStr[length];
	}
	
	// 重载复制运算符=，用于两个字符串之间的赋值;
	PSString &operator=(const PSString &rs)
	{
		if (this == &rs)
		{
			return *this;
		}

		delete[]m_pStr;
		m_iLen = rs.GetLength();
		m_pStr = new char[m_iLen + 1];
		for (unsigned int i = 0; i < m_iLen; i++)
		{
			m_pStr[i] = rs[i];     //重载下标运算符[]才可使用 
		}
		m_pStr[m_iLen] = '\0';
		return *this;
	}
 
	// 重载加法运算符+;
	PSString operator+(const PSString &rs)
	{
		unsigned int iTotal = m_iLen + rs.GetLength();
		char* pNewStr = new char[iTotal + 1];
		unsigned int i, j;
		for (i = 0; i < m_iLen; i++)
		{
			pNewStr[i] = m_pStr[i];
		}
		for (j = 0; j < rs.GetLength(); j++, i++)
		{
			pNewStr[i] = rs[j];
		}
		pNewStr[iTotal] = '\0';
		delete[]m_pStr;
		m_pStr = pNewStr;
		m_iLen = iTotal;
		return *this;
	}

	// 重载组合运算符+=;
	PSString operator+=(const PSString &rs)
	{
		int iTotal = m_iLen + rs.GetLength();
		char* pNewStr = new char[iTotal + 1];
		unsigned int i, j;
		for (i = 0; i < m_iLen; i++)
		{
			pNewStr[i] = m_pStr[i];
		}
		for (j = 0; j < rs.GetLength(); j++, i++)
		{
			pNewStr[i] = rs[j];
		}
		pNewStr[iTotal] = '\0';
		delete []m_pStr;
		m_pStr = pNewStr;
		m_iLen = iTotal;
		return *this;
	}

	// 重载小于运算符<;
	friend bool operator< (const PSString&str1, const PSString &str2)
	{
		if (strcmp(str1.m_pStr, str2.m_pStr) < 0) return 1;
		else return 0;
	}
	// 重载大于运算符>;
	friend bool operator> (const PSString&str1, const PSString &str2)
	{
		if (strcmp(str1.m_pStr, str2.m_pStr) > 0) return 1;
		else return 0;
	}
	// 重载等于运算符==;
	friend bool operator== (const PSString&str1, const PSString &str2)
	{
		if (strcmp(str1.m_pStr, str2.m_pStr) == 0) return 1;
		else return 0;
	}

	// 获取字符串长度;
	unsigned int PSString::GetLength()const
	{
		return m_iLen;
	}

	// 获取字符串;
	const char*PSString::GetString()const
	{
		return m_pStr;
	}

	// 是否为空串;
	bool IsEmpty() const
	{
		return 0 == GetLength();
	}

private:
	unsigned int	m_iLen;
	char*			m_pStr;
};

#endif // _PS_STRING_H