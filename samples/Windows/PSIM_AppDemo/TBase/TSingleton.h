#pragma once

/*
*	brief 单例模板类;
*/
template<class T>
class TSingleton
{
public:
	// 模板的话 构造,析构需要public;
	TSingleton(){}
	virtual ~TSingleton(){}

private:
	// 禁止拷贝,赋值;
	TSingleton(const TSingleton&);
	TSingleton& operator = (const TSingleton&);

public:

	static T* GetInstance()
	{
		static T t;
		return &t;
	}
};