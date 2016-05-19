/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose:
ջ�Ͷ��еĳ���������

Author: xjh

Created Time: 2015-8-1
******************************************************************************************/

#pragma once

#include <queue>
#include <stack>
#include <vector>


//
// 1.ʵ��һ��ջ��Ҫ��ʵ��push����ջ����pop����ջ����Min��������Сֵ�Ĳ�������ʱ�临�Ӷ�ΪO(1)
// 2.ʹ������ջʵ��һ������
// 3.ʹ����������ʵ��һ��ջ
// 4.Ԫ�س�ջ����ջ˳��ĺϷ��ԡ�����ջ�����У�1,2,3,4,5������ջ����Ϊ��4,5,3,2,1��
// 5.һ������ʵ������ջ
// 6.�������ʽ����⡣�沨�������ʽ����׺���ʽ��
//


// 1.ʵ��һ��ջ��Ҫ��ʵ��push����ջ����pop����ջ����Min��������Сֵ�Ĳ�������ʱ�临�Ӷ�ΪO(1)

// ˼·һ����ջʵ��
template<class T>
class StackMin1
{
public:
	void push(const T& x)
	{
		if (_s.empty())
		{
			_s.push(x);
			_s.push(x);
			min = x;
		}

		else
		{
			if (min > x)
				min = x;

			_s.push(x);
			_s.push(min);
		}
	}

	void pop()
	{
		_s.pop();
		_s.pop();
	}

	const T& Min()
	{
		return _s.top();
	}

private:
	stack<T> _s;
	T min;
};

// ˼·����˫ջʵ��
template<class T>
class StackMin2
{
public:
	void Push(const T& x)
	{
		if (_sMin.empty())
		{
			_sMin.push(x);
		}
		else
		{
			if (_sMin.top() > x)
			{
				_sMin.push(x);
			}
		}

		_s.push(x);
	}

	void Pop()
	{
		if (_s.top() == _sMin.top())
		{
			_sMin.pop();
		}

		_s.pop();
	}

	const T& Min()
	{
		_sMin.top();
	}

private:
	stack<T> _s;
	stack<T> _sMin;
};

// 1
void TestTopic1()
{
	StackMin1<int> s1;
	s1.push(3);
	s1.push(2);
	s1.push(1);
	s1.push(4);

	cout<<"Min:"<<s1.Min()<<endl;

	s1.pop();
	s1.pop();
	cout<<"Min:"<<s1.Min()<<endl;

	s1.pop();
	cout<<"Min:"<<s1.Min()<<endl;

	StackMin1<int> s2;
	s2.push(3);
	s2.push(2);
	s2.push(1);
	s2.push(4);

	cout<<"Min:"<<s2.Min()<<endl;

	s2.pop();
	s2.pop();
	cout<<"Min:"<<s2.Min()<<endl;

	s2.pop();
	cout<<"Min:"<<s2.Min()<<endl;
}

// 2.ʹ������ջʵ��һ������
template<class T>
class QueueBy2Stack
{
public:
	void Push(const T& x)
	{
		// ps���������ֱ�Ӽ򻯵�
		/*if (_s1.empty())
		{
			while (!_s2.empty())
			{
				_s1.push(_s2.top());
				_s2.pop();
			}
		}*/

		_s1.push(x);
	}

	void Pop()
	{
		if (_s2.empty())
		{
			while (!_s1.empty())
			{
				_s2.push(_s1.top());
				_s1.pop();
			}
		}

		_s2.pop();
	}

private:
	stack<T> _s1;	// �����ݵ�ջ
	stack<T> _s2;	// �����ݵ�ջ
};

// 3.ʹ����������ʵ��һ��ջ
template<class T>
class StackBy2Queue
{
public:
	void Push(const T& x)
	{
		if (!_q1.empty())
			_q1.push(x);
		else
			_q2.push(x);
	}

	void Pop()
	{
		queue<T>* pEmptyQ = &_q1; 
		queue<T>* pNonEmptyQ = &_q2;

		if (!pEmptyQ->empty())
			swap(pEmptyQ, pNonEmptyQ);

		while (pNonEmptyQ->size() > 1)
		{
			pEmptyQ->push(pNonEmptyQ->front());
			pNonEmptyQ->pop();
		}

		pNonEmptyQ->pop();
	}

private:
	queue<T> _q1;
	queue<T> _q2;
};

// 2��3
void TestTopic23()
{
	QueueBy2Stack<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);

	q.Pop();
	q.Pop();

	StackBy2Queue<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);

	s.Pop();
	s.Pop();
}

// 4.Ԫ�س�ջ����ջ˳��ĺϷ��ԡ�����ջ�����У�1,2,3,4,5������ջ����Ϊ��4,5,3,2,1����
bool IsVaildStackOrder(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.size() != v2.size())
	{
		return false;
	}

	// 
	// ʹ��һ��ջ��ģ���ջ��ջ˳��
	//
	size_t index1 = 0, index2 = 0;
	stack<int> s;
	while (index2 < v2.size())
	{
		//
		// 1.v1���л���������ջ�����ݲ�����v2����ʱ���򲻶���ջ��
		// 2.ջ�����ݲ�����v2���У���v1��û������ʱ�������зǷ���
		// 3.ջΪ����v1��û�����ݣ�v2�������ݣ������зǷ���
		//
		while(s.empty() || s.top() != v2[index2])
		{
			if (index1 < v1.size())
				s.push(v1[index1++]);
			else
				return false;
		}

		s.pop();
		++index2;
	}

	return true;
}

// 4 
void TestTopic4()
{
	vector<int> v1, v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(3);
	v2.push_back(2);
	v2.push_back(1);

	cout<<"IsVaildOrder����"<<IsVaildStackOrder(v1, v2)<<endl;
}

//
// һ������ʵ������ջ
// ����1:ʹ����żλ�ֱ�洢����ջ
// ����2:ʹ����ͷ���м�����
// �����Ƚ������ַ�������ȱ�㣬���Ǿ�̬�ṹ�Ͷ�̬�ṹѡ���ַ����Ĳ���
//

template<class T, int MaxSize = 10>
class DoubleStack
{
public:
	DoubleStack()
		:_top1(0)
		,_top2(1)
	{}

	void Push(int x, size_t num)
	{
		if (num == 1)
		{
			assert(_top1 < MaxSize);
			_a[_top1] = x;
			_top1+=2;
		}
		else if (num == 2)
		{
			assert(_top2 < MaxSize);
			_a[_top2] = x;
			_top2+=2;
		}
		else
		{
			assert(false);
		}
	}

	void Pop(size_t num)
	{
		if (num == 1)
		{
			assert(_top1 > 0);
			_top1-=2;
		}
		else if (num == 2)
		{
			assert(_top2 > 1);
			_top2-=2;
		}
		else
		{
			assert(false);
		}
	}

	int Top(size_t num)
	{
		if (num == 1)
			return _a[_top1-2];
		else if (num == 2)
			return _a[_top2-2];
		else
			assert(false);
	}

	bool Empty(size_t num)
	{
		assert(num == 1 || num == 2);

		if (num == 1 && _top1 == 0)
			return true;
		else if (num == 2 && _top2 == 1)
			return true;
		
		return false;
	}

private:
	T _a[MaxSize];
	int _top1;
	int _top2;
};

// 5
void TestTopic5()
{
	DoubleStack<int> ds;
	ds.Push(1,1);
	ds.Push(3,1);
	ds.Push(5,1);

	ds.Push(2,2);
	ds.Push(4,2);
	ds.Push(6,2);

	cout<<ds.Top(1)<<endl;
	cout<<ds.Top(2)<<endl;
}

// 6.�������ʽ����⣬�沨�������ʽ����׺���ʽ��
enum Type
{
	ADD,	// ��
	SUB,	// ��
	MUL,	// ��
	DIV,	// ��
	OP_NUM,	// ������
};

struct Cell
{
	Type _symbol;
	int _num;
};

// 12*(3+4)-6+8/2 ==> 12 3 4 + * 6 - 8 2 / +
Cell RPNExp[11] =
{
	OP_NUM, 12,
	OP_NUM, 3,
	OP_NUM, 4,
	ADD, 0,
	MUL, 0,
	OP_NUM, 6,
	SUB, 0,
	OP_NUM, 8,
	OP_NUM, 2,
	DIV, 0,
	ADD, 0,
};

int CountRPN(Cell* exp, int size)
{
	stack<int> s;
	int left, right;
	for (int i = 0; i < size; ++i)
	{
		if (exp[i]._symbol == OP_NUM)
		{
			s.push(exp[i]._num);
			continue;
		}

		right = s.top();
		s.pop();
		left = s.top();
		s.pop();

		switch(exp[i]._symbol)
		{
		case ADD:
			s.push(left+right);
			break;
		case SUB:
			s.push(left-right);
			break;
		case MUL:
			s.push(left*right);
			break;
		case DIV:
			s.push(left/right);
			break;
		}
	}

	return s.top();
}

// 6
void TestTopic6()
{
	cout<<"������:"<<CountRPN(RPNExp, 11)<<endl;
}