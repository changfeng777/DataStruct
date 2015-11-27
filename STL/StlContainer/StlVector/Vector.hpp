#pragma once
#include <assert.h>

#include "../Common/Allocator.hpp"
#include "../Common/Uninitialized.hpp"

template<class T, class Allocator = Alloc>
class Vector
{
public:
	// const�汾����Ӧconst��Աʹ��
	typedef T ValueType;
	typedef ptrdiff_t  DifferenceType;
	typedef ValueType* Pointer;
	typedef const ValueType* ConstPointer;
	typedef ValueType& Reference;
	typedef const ValueType& ConstReference;

	//
	// Vector�ĵ�������һ��ԭ��ָ�룬��������һ���������������
	// ��ͨ���ػ� struct IteratorTraits<T*>�ķ�ʽ�����
	//
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;

	// �ض���ռ�����������
	typedef SimpleAlloc<ValueType, Alloc> DataAllocator;

	Iterator Begin() { return _start; }
	Iterator End() { return _finish; }

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

	~Vector()
	{
		// �ͷſռ�
		DataAllocator::Deallocate(_start, _finish - _start);
	}

	void _CheckExpand()
	{
		if (_finish == _endOfStorage)
		{
		/*	size_t size = Size();
			size_t capacity = size*2 + 3;
			T* tmp = new T[capacity];
			if (_start)
				memcpy(tmp, _start, sizeof(T)*size);
		*/
			// ���ÿռ����������䣬��ʵ�ֵĿ����㷨���п�����
			size_t size = Size();
			size_t capacity = size*2 + 3;
			T* tmp = (T*)DataAllocator::Allocate(capacity);
			if (_start)
				UninitializedCopy(_start, _finish, tmp);
			
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
void PrintVector(Vector<int>& v)
{
	Vector<int>::Iterator it = v.Begin();
	for (; it != v.End(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void TestVector1()
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

	PrintVector(v1);

	// ������ʧЧ
	Vector<int>::Iterator it = v1.Begin();
	while(it != v1.End())
	{
		if (*it % 2 == 0)
			it = v1.Erase(it);
		else
			++it;
	}
	PrintVector(v1);
}