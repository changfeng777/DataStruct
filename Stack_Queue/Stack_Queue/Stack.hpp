/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: ʹ�ö�̬���鷽ʽʵ��ջ   

Author: xjh

Created Time: 2015-8-1
******************************************************************************************/

#pragma once

#include <assert.h>

template<class T>
class Stack
{
public:
	Stack()
		:_capacity(3)
		,_size(0)
		,_data(new T[_capacity])
	{}

	~Stack()
	{
		if (_data)
		{
			delete [] _data;
		}
	}

public:
	void Push(const T& x);
	void Pop();
	const T& Top();
	size_t Size();
	bool Empty();

	void Print()
	{
		//for (int i = 0; i < _size; ++i)
		{
			//cout<<_data[i]<<"->";
		}
		cout<<"Stack Top";
	}

private:
	void _CheckExpandCapacity();

private:
	size_t _size;		// ���ݵĸ���
	size_t _capacity;	// ����

	T* _data;			// ָ�����ݿ��ָ��
};

template<class T>
void Stack<T>::_CheckExpandCapacity()
{
	if (_capacity == _size)
	{
		T* tmp = new T[2*_capacity];
		memcpy(tmp, _data, _size*sizeof(T));
		_capacity *= 2;

		delete[] _data;
		_data = tmp;
	}
}


template<class T>
void Stack<T>::Push(const T& x)
{
	_CheckExpandCapacity();

	_data[_size++] = x;
}

template<class T>
void Stack<T>::Pop()
{
	assert(_size > 0);
	--_size;
}

template<class T>
const T& Stack<T>::Top()
{
	assert(_size > 0);
	return _data[_size - 1];
}

template<class T>
size_t Stack<T>::Size()
{
	return _size;
}

template <class T>
bool Stack<T>::Empty()
{
	return _size == 0;
}
