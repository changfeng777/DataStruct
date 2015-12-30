/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose:
1��ʹ�ö�̬���鷽ʽʵ��ջ 
2�����⿼��ʹ��˳���ʵ��������ģʽ��ջ���ⲿ����C++ģ�岿���ѽ������

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
	void Push(const T& x)
	{
		_CheckCapacity();
		_data[_size++] = x;
	}

	void Pop()
	{
		assert(_size > 0);
		--_size;
	}

	const T& Top()
	{
		assert(_size > 0);
		return _data[_size - 1];
	}

	size_t Size()
	{
		return _size;
	}

	bool Empty()
	{
		return _size == 0;
	}

	void Print()
	{
		for (int i = 0; i < _size; ++i)
		{
			cout<<_data[i]<<"->";
		}
	}

private:
	void _CheckCapacity()
	{
		if (_capacity == _size)
		{
			T* tmp = new T[2*_capacity];
			//
			// ���T���Զ����͵Ŀ�����ǳ����������
			// ��T��string������ʱ����operator=
			//
			memcpy(tmp, _data, _size*sizeof(T));
			_capacity *= 2;

			delete[] _data;
			_data = tmp;
		}
	}

private:
	size_t _size;		// ���ݵĸ���
	size_t _capacity;	// ����

	T* _data;			// ָ�����ݿ��ָ��
};

void TestStack()
{
	Stack<int> s1;
	cout<<"Stack is Empty:"<<s1.Empty()<<endl;

	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();
	s1.Print();
}