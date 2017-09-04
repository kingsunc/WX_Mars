#ifndef _PS_VERTOR_H
#define _PS_VERTOR_H

template<typename T>
class PSVector
{
public:

	//构造函数，复制构造函数以及析构函数  
	PSVector(int size = 0) :theSize(size), theCapacity(0 + SPACE_CAPACITY)
	{
		objects = new T[theCapacity];
	}
	PSVector(const PSVector& rhs) : objects(NULL)
	{
		operator=(rhs);
	}
	~PSVector()
	{
		delete[] objects;
	}

	// 重载=号操作符  
	const PSVector& operator=(const PSVector& rhs)
	{
		theCapacity = rhs.theCapacity;
		theSize = rhs.theSize;
		objects = new T[this->theCapacity];
		for (int i = 0; i < this->theSize; i++)
		{
			objects[i] = rhs.objects[i];
		}
		return *this;
	}

	//调整size  
	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2 + 1);
		theSize = newSize;
	}

	// 调整预留的空间，也就是实际上申请的内存的大小;
	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
		{
			return;
		}

		T* oldObject = objects;
		objects = new T[newCapacity];
		theCapacity = newCapacity;
		for (int i = 0; i < theSize; i++)
		{
			objects[i] = oldObject[i];
		}
		delete []oldObject;
	}

	//重载[]操作符  
	T& operator[](int index)
	{
		return *(objects + index);
	}
	const T& operator[](int index)const
	{
		return *(objects + index);
	}

	//几个get函数，均为const成员，保证const对象也能调用  
	bool isEmpty() const
	{
		return getSize() == 0;
	}
	int capacity() const
	{
		return theCapacity;
	}
	int size() const
	{
		return theSize;
	}

	// push和pop操作;
	void push_back(T t)
	{
		if (theSize == theCapacity)
		{
			reserve(theCapacity * 2 + 1);
		}
		objects[theSize++] = t;
	}
	void pop_back()
	{
		theSize--;
	}
	T& back()
	{
		return objects[theSize - 1];
	}
	const T& back()const
	{
		return objects[theSize - 1];
	}

	// 迭代器  
	typedef T* iterater;
	typedef const T* const_iterater;

	//begin end 等操作  
	iterater begin()
	{
		return objects;
	}
	const_iterater begin() const
	{
		return objects;
	}
	iterater end()
	{
		return (objects + theSize);
	}
	const_iterater end() const
	{
		return (objects + theSize);
	}
	enum { SPACE_CAPACITY = 16 };

private:
	T* objects;
	int theSize;
	int theCapacity;
};

#endif // _PS_VERTOR_H