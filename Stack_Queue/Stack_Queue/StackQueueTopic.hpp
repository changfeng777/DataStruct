#pragma once

#include "Queue.hpp"
#include "Stack.hpp"
#include <vector>
//#include "StackAdapter.hpp"


//
// 1.ʵ��һ��ջ��Ҫ��ʵ��Push����ջ����Pop����ջ����Min��������Сֵ�Ĳ�������ʱ�临�Ӷ�ΪO(1)
// 2.ʹ������ջʵ��һ������
// 3.ʹ����������ʵ��һ��ջ
// 4.Ԫ�س�ջ����ջ˳��ĺϷ��ԡ�����ջ�����У�1,2,3,4,5������ջ����Ϊ��4,5,3,2,1��
// 5.һ������ʵ������ջ
// 6.�������ʽ����⡣�沨�������ʽ����׺���ʽ��
//


// 1.ʵ��һ��ջ��Ҫ��ʵ��Push����ջ����Pop����ջ����Min��������Сֵ�Ĳ�������ʱ�临�Ӷ�ΪO(1)

// ˼·һ����ջʵ��
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

// ˼·����˫ջʵ��
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

// 2.ʹ������ջʵ��һ������
template<class T>
class QueueBy2Stack
{
public:
	void Push(const T& x)
	{
		// ps���������ֱ�Ӽ򻯵�
		/*if (_s1.Empty())
		{
			while (!_s2.Empty())
			{
				_s1.Push(_s2.Top());
				_s2.Pop();
			}
		}*/

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
	Stack<T> _s1;	// �����ݵ�ջ
	Stack<T> _s2;	// �����ݵ�ջ
};

// 3.ʹ����������ʵ��һ��ջ
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
	Stack<int> s;
	while (index2 < v2.size())
	{
		//
		// 1.v1���л���������ջ�����ݲ�����v2����ʱ���򲻶���ջ��
		// 2.ջ�����ݲ�����v2���У���v1��û������ʱ�������зǷ���
		// 3.ջΪ����v1��û�����ݣ�v2�������ݣ������зǷ���
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

// һ������ʵ������ջ
// ����1:ʹ����żλ�ֱ�洢����ջ
#define MaxSize 100
int Stack2Array[MaxSize] = {0};
class Stack2
{
public:
	Stack2(int topIndex, int* array = Stack2Array)
		:_array(array)
		,_topIndex(topIndex)
		,_beginIndex(topIndex)
	{}

	void Push(int x)
	{
		assert(_topIndex < MaxSize);

		_array[_topIndex] = x;
		_topIndex += 2;
	}

	void Pop()
	{
		assert(_topIndex > _beginIndex);

		_topIndex -= 2;
	}
	int Top()
	{
		return _array[_topIndex - 2];
	}
	bool Empty()
	{
		return _topIndex == _beginIndex;
	}

private:
	int* _array;
	int _topIndex;
	const int _beginIndex;
};

// ����2:����ջ����żλ˫ջ�Ķ�̬����(��չ)
// ��˽ṹ�����Ϊ�˴ﵽ���Դ��������˫ջʵ��
class Stack2_D
{
public:
	Stack2_D(int*& array, int& capacity, int topIndex)
		:_array(array)
		,_capacity(capacity)
		,_topIndex(topIndex)
		,_beginIndex(topIndex)
	{}

	void Push(int x)
	{
		// ����
		if (_capacity >= _topIndex)
		{
			_capacity=2*_capacity+3;
			_array = (int*)realloc(_array, _capacity);
		}

		_array[_topIndex] = x;
		_topIndex+=2;
	}

	void Pop()
	{
		assert(_topIndex > _beginIndex);
		_topIndex-=2;
	}

	bool Empty()
	{
		return _topIndex == _beginIndex;
	}

	int& Top()
	{
		return _array[_topIndex];
	}

private:
	int*& _array;
	int& _capacity;

	int _topIndex;
	const int _beginIndex;
};

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
	Stack<int> s;
	int left, right;
	for (int i = 0; i < size; ++i)
	{
		switch(exp[i]._symbol)
		{
		case OP_NUM:
			s.Push(exp[i]._num);
			break;
		case ADD:
			right = s.Top();
			s.Pop();
			left = s.Top();
			s.Pop();
			s.Push(left+right);
			break;
		case SUB:
			right = s.Top();
			s.Pop();
			left = s.Top();
			s.Pop();
			s.Push(left-right);
			break;
		case MUL:
			right = s.Top();
			s.Pop();
			left = s.Top();
			s.Pop();
			s.Push(left*right);
			break;
		case DIV:
			right = s.Top();
			s.Pop();
			left = s.Top();
			s.Pop();
			s.Push(left/right);
			break;
		}
	}

	return s.Top();
}

// 1
void TestTopic1()
{
	Stack_Min1<int> s1;
	s1.Push(3);
	s1.Push(2);
	s1.Push(1);
	s1.Push(4);

	cout<<"Min:"<<s1.Min()<<endl;

	s1.Pop();
	s1.Pop();
	cout<<"Min:"<<s1.Min()<<endl;

	s1.Pop();
	cout<<"Min:"<<s1.Min()<<endl;

	Stack_Min1<int> s2;
	s2.Push(3);
	s2.Push(2);
	s2.Push(1);
	s2.Push(4);

	cout<<"Min:"<<s2.Min()<<endl;

	s2.Pop();
	s2.Pop();
	cout<<"Min:"<<s2.Min()<<endl;

	s2.Pop();
	cout<<"Min:"<<s2.Min()<<endl;
}

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

	cout<<"Is Vaild Order����"<<IsVaildStackOrder(v1, v2)<<endl;
}

// 5
void TestTopic5()
{
	Stack2 s1(0);
	Stack2 s2(1);
	s1.Push(0);
	s1.Push(2);
	s1.Push(4);
	s1.Push(6);

	s2.Push(1);
	s2.Push(3);
	s2.Push(5);
	s2.Push(7);

	s1.Pop();
	s2.Pop();

	int* array1 = NULL;
	int capacity1 = 0;
	Stack2_D s3(array1, capacity1, 0);
	Stack2_D s4(array1, capacity1, 1);
	s3.Push(0);
	s3.Push(2);
	s3.Push(4);

	s3.Pop();

	s4.Push(1);
	s4.Push(3);
	s4.Push(5);
	s4.Pop();

	int* array2 = NULL;
	int capacity2 = 0;
	Stack2_D s5(array2, capacity2, 0);
	Stack2_D s6(array2, capacity2, 1);
	s5.Push(0);
	s5.Push(2);
	s5.Push(4);
	s5.Pop();

	s6.Push(1);
	s6.Push(3);
	s6.Push(5);
	s6.Pop();
}

// 6
void TestTopic6()
{
	cout<<"������:"<<CountRPN(RPNExp, 11)<<endl;
}