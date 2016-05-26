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
	// Vector�ĵ�������һ��ԭ��ָ�룬��������һ���������������
	// ��ͨ���ػ� struct IteratorTraits<T*>�ķ�ʽ�����
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

			// �˴���Ҫ����������ȡ�����Ż���
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

	// ����ɾ�����ݵ���һ������
	Iterator Erase(Iterator pos)
	{
		// �ƶ�����
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
	Iterator _start;		// ָ�����ݿ�Ŀ�ʼ
	Iterator _finish;		// ָ����Ч���ݵ�β
	Iterator _endOfStorage; // ָ��洢������β
};

// ����Vector��������ʹ��
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

	// ������ʧЧ
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