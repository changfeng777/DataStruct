#pragma once

#include "Queue.hpp"
#include "Stack.hpp"
#include <vector>
//#include "StackAdapter.hpp"

// 1.实现一个栈，要求实现Push（出栈）、Pop（入栈）、Min（返回最小值的操作）的时间复杂度为O(1)

template<class T>
class Stack_Min1
{
public:
	void Push(const T& x)
	{
		if (_s.Empty())
		{
			_s.Push(x);
			_s.Push(x);
			min = x;
		}

		else
		{
			if (min > x)
			{
				min = x;
			}

			_s.Push(x);
			_s.Push(min);
		}
	}

	void Pop()
	{
		_s.Pop();
		_s.Pop();
	}

	const T& Min()
	{
		return _s.Top();
	}

private:
	Stack<T> _s;
	T min;
};

template<class T>
class Stack_Min2
{
public:
	void Push(const T& x)
	{
		if (_sMin.Empty())
		{
			_sMin.Push(x);
		}
		else
		{
			if (_sMin.Top() > x)
			{
				_sMin.Push(x);
			}
		}

		_s.Push(x);
	}

	void Pop()
	{
		if (_s.Top() == _sMin.Top())
		{
			_sMin.Pop();
		}

		_s.Pop();
	}

	const T& Min()
	{
		_sMin.Top();
	}

private:
	Stack<T> _s;
	Stack<T> _sMin;
};

// 2.使用两个栈实现一个队列
template<class T>
class QueueBy2Stack
{
public:
	void Push(const T& x)
	{
		if (_s1.Empty())
		{
			while (!_s2.Empty())
			{
				_s1.Push(_s2.Top());
				_s2.Pop();
			}
		}

		_s1.Push(x);
	}

	void Pop()
	{
		if (_s2.Empty())
		{
			while (!_s1.Empty())
			{
				_s2.Push(_s1.Top());
				_s1.Pop();
			}
		}

		_s2.Pop();
	}

private:
	Stack<T> _s1;
	Stack<T> _s2;
};

// 3.使用两个队列实现一个栈
template<class T>
class StackBy2Queue
{
public:
	void Push(const T& x)
	{
		if (!_q1.Empty())
		{
			_q1.Push(x);
		}
		else
		{
			_q2.Push(x);
		}
	}

	void Pop()
	{
		Queue<T>* pEmptyQ = &_q1; 
		Queue<T>* pNonEmptyQ = &_q2;

		if (!pEmptyQ->Empty())
		{
			swap(pEmptyQ, pNonEmptyQ);
		}

		while (pNonEmptyQ->Size() > 1)
		{
			pEmptyQ->Push(pNonEmptyQ->Front());
			pNonEmptyQ->Pop();
		}

		pNonEmptyQ->Pop();
	}

private:
	Queue<T> _q1;
	Queue<T> _q2;
};

// 4.元素出栈、入栈顺序的合法性。如入栈的序列（1,2,3,4,5），出栈序列为（4,5,3,2,1）。

bool IsVaildStackOrder(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.size() != v2.size())
	{
		return false;
	}

	// 
	// 使用一个栈来模拟出栈入栈顺序
	//
	int index1 = 0, index2 = 0;
	Stack<int> s;
	while (index2 < v2.size())
	{
		//
		// 1.v1序列还有数据且栈顶数据不等于v2序列时，则不断入栈。
		// 2.栈顶数据不等于v2序列，且v1已没有数据时，则序列非法。
		// 3.栈为空且v1已没有数据，v2还有数据，则序列非法。
		//
		while(s.Empty() || s.Top() != v2[index2])
		{
			if (index1 < v1.size())
				s.Push(v1[index1++]);
			else
				return false;
		}

		s.Pop();
		++index2;
	}

	return true;
}