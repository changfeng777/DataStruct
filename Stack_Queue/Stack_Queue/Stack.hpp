/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose:
1：使用动态数组方式实现栈 
2：另外考虑使用顺序表实现适配器模式的栈（这部分在C++模板部分已讲解过）

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
			// 如果T是自定类型的考虑深浅拷贝的问题
			// 当T是string等类型时得用operator=
			//
			memcpy(tmp, _data, _size*sizeof(T));
			_capacity *= 2;

			delete[] _data;
			_data = tmp;
		}
	}

private:
	size_t _size;		// 数据的个数
	size_t _capacity;	// 容量

	T* _data;			// 指向数据块的指针
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