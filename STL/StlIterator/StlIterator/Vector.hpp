#pragma once
#include <assert.h>

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Pointer;
	typedef ValueType* Iterator;
	typedef ValueType& Reference;

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

	void _CheckExpand()
	{
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t capacity = size*2 + 3;
			T* tmp = new T[capacity];
			if (_start)
				memcpy(tmp, _start, sizeof(T)*size);
			
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