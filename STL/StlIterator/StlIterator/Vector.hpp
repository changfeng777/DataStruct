#pragma once
#include <assert.h>
#include "StlIterator.hpp"

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ptrdiff_t  DifferenceType;
	typedef ValueType* Pointer;
	typedef ValueType& Reference;

	//
	// Vector的迭代器是一个原生指针，所以是是一个随机迭代器类型
	// 是通过特化 struct IteratorTraits<T*>的方式定义的
	//
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;

	typedef ReverseIterator<Iterator> ReverseIterator;


	Iterator Begin() { return _start; }
	Iterator End() { return _finish; }
	ConstIterator Begin() const { return _start; }
	ConstIterator End() const { return _finish; }

	ReverseIterator RBegin() { return ReverseIterator(End()); }
	ReverseIterator REnd() { return ReverseIterator(Begin()); }

	size_t Size()
	{
		return _finish - _start;
	}

	size_t Capacity()
	{
		return _endOfStorage - _start;
	}

	Vector()
		:_start(NULL)
		,_finish(NULL)
		,_endOfStorage(NULL)
	{}

	void _CheckExpand()
	{
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t capacity = size*2 + 3;
			T* tmp = new T[capacity];

			// 此处需要考虑类型萃取进行优化的
			if (_start)
			{
				//memcpy(tmp, _start, sizeof(T)*size);
				for (size_t i = 0; i < size; ++i)
				{
					tmp[i] = _start[i];
				}
			}
			
			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + capacity;
		}
	}

	void PushBack(const T& x)
	{
		_CheckExpand();

		assert(_finish != _endOfStorage);

		*_finish = x;
		++_finish;
	}

	void PopBack()
	{
		--_finish;
	}

	// 返回删除数据的下一个数据
	Iterator Erase(Iterator pos)
	{
		// 移动数据
		Iterator begin = pos + 1;
		while (begin != _finish)
		{
			*(begin - 1) = *begin;
			++begin;
		}

		--_finish;

		return pos;
	}

private:
	Iterator _start;		// 指向数据块的开始
	Iterator _finish;		// 指向有效数据的尾
	Iterator _endOfStorage; // 指向存储容量的尾
};

// 测试Vector迭代器的使用
void PrintVector1(Vector<int>& v)
{
	Vector<int>::Iterator it = v.Begin();
	for (; it != v.End(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void PrintVector2(const Vector<int>& v)
{
	Vector<int>::ConstIterator it = v.Begin();
	for (; it != v.End(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void PrintVector3(Vector<int>& v)
{
	Vector<int>::ReverseIterator it = v.RBegin();
	for (; it != v.REnd(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void TestVector()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	v1.PushBack(6);
	v1.PushBack(7);
	v1.PushBack(8);

	PrintVector1(v1);

	// 迭代器失效
	Vector<int>::Iterator it = v1.Begin();
	while(it != v1.End())
	{
		if (*it % 2 == 0)
			it = v1.Erase(it);
		else
			++it;
	}
	PrintVector1(v1);
	PrintVector2(v1);
	PrintVector3(v1);
}