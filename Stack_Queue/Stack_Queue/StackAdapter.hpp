/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 栈的使用单链表的适配器模式实现    

Author: xjh

Created Time: 2015-8-1
******************************************************************************************/


#pragma once

#include "SList.hpp"

template<class T>
class Stack
{
public:
	void Push(const T& x);
	void Pop();
	const T& Top();
	size_t Size();
	bool Empty();

private:
	SList<T> _sList;
};

template<class T>
void Stack<T>::Push(const T& x)
{
	_sList.PushBack(x);
}

template<class T>
void Stack<T>::Pop()
{
	_sList.PopBack();
}

template<class T>
const T& Stack<T>::Top()
{
	return _sList.Back();
}

template<class T>
size_t Stack<T>::Size()
{
	return _sList.Size();
}

template<class T>
bool Stack<T>::Empty()
{
	return _sList.Empty();
}